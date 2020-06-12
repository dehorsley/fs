#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <jansson.h>

enum { JSONRPC_STATUS_PARSE_ERROR      = -32700,
       JSONRPC_STATUS_INVALID_REQUEST  = -32600,
       JSONRPC_STATUS_METHOD_NOT_FOUND = -32601,
       JSONRPC_STATUS_INVALID_PARAMS   = -32702,
       JSONRPC_STATUS_INTERNAL_ERROR   = -32703,
};


#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/supplemental/http/http.h>
#include <nng/supplemental/util/platform.h>

#include "stream.h"

#define PUB_URL "ws://localhost:8888/socks/pub"
#define REP_URL "ws://localhost:8888/socks/rep"
#define CMD_URL "ws://localhost:8888/cmd"
#define URL "http://localhost:8888/"

#define fatal(msg, s)                                                                              \
	do {                                                                                       \
		fprintf(stderr, "%s:%d (%s) error %s: %s\n", __FILE__, __LINE__, __FUNCTION__,     \
		        msg, s);                                                                   \
		exit(1);                                                                           \
	} while (0)

double r = 0.0;

void inproc_server(void *arg) {
    (void) arg;
    buffered_stream_t *s;
	int rv;

	if ((rv = buffered_stream_open(&s) != 0))
		fatal("unable to set up inproc", nng_strerror(rv));


    if ((rv = buffered_stream_listen(s, PUB_URL, REP_URL) != 0))
		fatal("unable listen", nng_strerror(rv));

	char buf[254] = {};
	for (uint32_t i = 0;; i++) {
        r += (2.0*rand())/RAND_MAX-1;
        size_t n = snprintf(buf, sizeof(buf), "{\"blag\":%d, \"r\": %f, \"con\": \"constant\"}\n", i, r);
        if ((rv=(buffered_stream_send(s, buf, n)) < 0)) fatal("send", nng_strerror(rv));
		nng_msleep(200);
	}
}

struct cmd {
	const char *name;
	void (*cmd)(json_t *, json_t *);
};

void log_cmd(json_t* reply, json_t* params) {
	if ((1.0*rand())/RAND_MAX > 0.5) {
		json_object_set(reply, "error", params);
        return;
	} 
    json_object_set_new(reply, "result", json_string("station"));
}

void ints_cmd(json_t* reply, json_t* params) {
    json_t* value  = json_array_get(params, 0);
    if (!value || !json_is_string(value)) {
		json_object_set_new(reply, "error", json_string("invalid params"));
        return;
    }

    int i = 0;
    i = atoi(json_string_value(value));
    if (i <= 0) {
		json_object_set_new(reply, "error", json_string("invalid params"));
        return;
    }

    json_t *array = json_array();

    for (int j = 0; j < i; j++) {
        json_array_append(array, json_integer(j));
    }

    json_object_set_new(reply, "result", array);

}

void hello_cmd(json_t* reply, json_t* params) {
	if ((1.0*rand())/RAND_MAX > 0.5) {
		json_object_set(reply, "error", params);
        return;
	} 

    json_object_set_new(reply, "result", json_string("station"));
}

void reset_cmd(json_t* reply, json_t* params) {
    r = 0.0;
    json_object_set_new(reply, "result", json_null());
}

static const struct cmd commands[] = {
    {"log", log_cmd},
    {"ints", ints_cmd},
    {"hello", hello_cmd},
    {"reset", reset_cmd},
    {NULL, NULL},
};


/*
 * ret -1 indicates internal error
 * return > 0 inidcates the command returned an error
 *
 */
void call_cmd(json_t* reply, const char *method, json_t *params) {
	const struct cmd *ptr;
	for (ptr = commands; ptr->name; ptr++) {
		if (strcmp(ptr->name, method) == 0) {
			ptr->cmd(reply, params);
            return;
		}
	}
    
    json_t *error = json_object();
    json_object_set_new(error, "message", json_string("method not found"));
    json_object_set_new(error, "code", json_integer(JSONRPC_STATUS_METHOD_NOT_FOUND));
    json_object_set_new(reply, "error", error);
	return;
}



nng_socket cmd_sock;

void server_cmd_cb(void *arg) {
    int rv;
    assert(arg != NULL);
    nng_aio *aio = *(nng_aio **)arg;
    assert(aio != NULL);
	if (nng_aio_result(aio) != 0)
		return;

	nng_msg *msg, *reply_msg;
	msg = nng_aio_get_msg(aio);

	rv = nng_msg_alloc(&reply_msg, 0);
	if (rv != 0) {
		exit(1);
	}

	json_t *method  = NULL;
	json_t *params  = NULL;
	json_t *request = NULL;
	json_t *error   = NULL;

	json_t *reply = json_object();
	json_object_set_new(reply, "jsonrpc", json_string("2.0"));
	json_object_set_new(reply, "id", json_null());

	json_error_t err;
	request = json_loadb(nng_msg_body(msg), nng_msg_len(msg), 0, &err);
	nng_msg_free(msg);

	if (!request) {
		error = json_object();
		json_object_set_new(error, "message", json_string(err.text));
		json_object_set_new(error, "code", json_integer(JSONRPC_STATUS_PARSE_ERROR));
		goto error;
	}

	if (!json_is_object(request)) {
		error = json_object();
		json_object_set_new(error, "message", json_string("request must be an object"));
		json_object_set_new(error, "code", json_integer(JSONRPC_STATUS_INVALID_REQUEST));
		goto error;
	}

	json_t *id = json_object_get(request, "id");
	if (!id || json_is_null(id)) {
		error = json_object();
		json_object_set_new(error, "message",
		                    json_string("Invalid Request: id not speficied"));
		json_object_set_new(error, "code", json_integer(JSONRPC_STATUS_INVALID_REQUEST));
		goto error;
	}
	json_object_set(reply, "id", id);

	method = json_object_get(request, "method");
	if (!json_is_string(method)) {
		error = json_object();
		json_object_set_new(error, "message",
		                    json_string("Invalid Request: method not a string"));
		json_object_set_new(error, "code", json_integer(JSONRPC_STATUS_INVALID_REQUEST));
		goto error;
	}

	params = json_object_get(request, "params");

	call_cmd(reply, json_string_value(method), params);
    char *reply_str;

end:
	reply_str = json_dumps(reply, 0);
	nng_msg_append(reply_msg, reply_str, strlen(reply_str));
	free(reply_str);
	json_decref(reply);
	rv = nng_sendmsg(cmd_sock, reply_msg, 0);
	if (rv != 0) {
		nng_msg_free(reply_msg);
		return;
	}

	json_decref(request);
	nng_recv_aio(cmd_sock, aio);
	return;

error:
    json_object_set_new(reply, "error", error);
    goto end;
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

	int rv;
	nng_thread *inproc_thr;

	nng_http_server *server;
	nng_http_handler *handler;
	nng_url *url;


	if ((rv = nng_url_parse(&url, URL)) != 0) {
		fatal("nng_url_parse", nng_strerror(rv));
	}

	printf("listening on %s\n", URL);
	// Get a suitable HTTP server instance.  This creates one
	// if it doesn't already exist.
	if ((rv = nng_http_server_hold(&server, url)) != 0) {
		fatal("nng_http_server_hold", nng_strerror(rv));
	}

	rv = nng_http_handler_alloc_directory(&handler, "/", "./web/public/");
	if (rv != 0) {
		fatal("nng_http_handler_alloc", nng_strerror(rv));
	}
	if ((rv = (nng_http_handler_set_tree(handler)) != 0)) {
		fatal("nng_http_handler_add_handler", nng_strerror(rv));
	}
	if ((rv = nng_http_server_add_handler(server, handler)) != 0) {
		fatal("nng_http_handler_add_handler", nng_strerror(rv));
	}

	if ((rv = nng_http_server_start(server)) != 0) {
		fatal("nng_http_server_start", nng_strerror(rv));
	}

	nng_url_free(url);

	rv = nng_thread_create(&inproc_thr, inproc_server, NULL);
	if (rv != 0) {
		fatal("cannot start inproc server", nng_strerror(rv));
	}

    nng_aio *aio;
    rv = nng_aio_alloc(&aio, server_cmd_cb, &aio);
	if (rv != 0) {
        fatal("allocating aio", nng_strerror(rv));
	}
	rv = nng_rep0_open(&cmd_sock);
	if (rv != 0) {
        fatal("rep open", nng_strerror(rv));
	}
	rv = nng_listen(cmd_sock, CMD_URL, NULL, 0);
    if (rv != 0) {
        fatal("rep listen", nng_strerror(rv));
	}
	nng_recv_aio(cmd_sock, aio);

	// This runs forever.  The inproc_thr never exits, so we
	// just block behind its condition variable.
	nng_thread_destroy(inproc_thr);
}
