#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/supplemental/http/http.h>
#include <nng/supplemental/util/platform.h>

#include "stream.h"

#define PUB_URL "ws://localhost:8888/socks/pub"
#define REP_URL "ws://localhost:8888/socks/rep"
#define URL "http://localhost:8888/"

void fatal(const char *what, int rv) {
	fprintf(stderr, "%s: %s\n", what, nng_strerror(rv));
	exit(1);
}

void inproc_server(void *arg) {
    (void) arg;
    buffered_stream_t *s;
	int rv;

	if ((rv = buffered_stream_open(&s) != 0))
		fatal("unable to set up inproc", rv);


    if ((rv = buffered_stream_listen(s, PUB_URL, REP_URL) != 0))
		fatal("unable listen", rv);

	char buf[254] = {};
	for (uint32_t i = 0;; i++) {
        size_t n = snprintf(buf, sizeof(buf), "%d\n", i);
        if ((rv=(buffered_stream_send(s, buf, n)) < 0)) fatal("send", rv);
		nng_msleep(200);
	}
}

int main(int argc, char **argv) {
	int rv;
	nng_thread *inproc_thr;

	nng_http_server *server;
	nng_http_handler *handler;
	nng_url *url;

	if ((rv = nng_url_parse(&url, URL)) != 0) {
		fatal("nng_url_parse", rv);
	}

	printf("listening on %s\n", URL);
	// Get a suitable HTTP server instance.  This creates one
	// if it doesn't already exist.
	if ((rv = nng_http_server_hold(&server, url)) != 0) {
		fatal("nng_http_server_hold", rv);
	}

	rv = nng_http_handler_alloc_file(&handler, "/", "./web/index.html");
	if (rv != 0) {
		fatal("nng_http_handler_alloc", rv);
	}
	if ((rv = nng_http_server_add_handler(server, handler)) != 0) {
		fatal("nng_http_handler_add_handler", rv);
	}

	rv = nng_http_handler_alloc_directory(&handler, "/node_modules", "./web/node_modules/");
	if (rv != 0) {
		fatal("nng_http_handler_alloc", rv);
	}

	if ((rv = nng_http_server_add_handler(server, handler)) != 0) {
		fatal("nng_http_handler_add_handler", rv);
	}

	if ((rv = nng_http_server_start(server)) != 0) {
		fatal("nng_http_server_start", rv);
	}

	nng_url_free(url);

	rv = nng_thread_create(&inproc_thr, inproc_server, NULL);
	if (rv != 0) {
		fatal("cannot start inproc server", rv);
	}

	// This runs forever.  The inproc_thr never exits, so we
	// just block behind its condition variable.
	nng_thread_destroy(inproc_thr);
}
