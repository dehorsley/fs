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

#define fatal(msg, s)                                                                              \
	do {                                                                                       \
		fprintf(stderr, "%s:%d (%s) error %s: %s\n", __FILE__, __LINE__, __FUNCTION__,     \
		        msg, s);                                                                   \
		exit(1);                                                                           \
	} while (0)

void inproc_server(void *arg) {
    (void) arg;
    buffered_stream_t *s;
	int rv;

	if ((rv = buffered_stream_open(&s) != 0))
		fatal("unable to set up inproc", nng_strerror(rv));


    if ((rv = buffered_stream_listen(s, PUB_URL, REP_URL) != 0))
		fatal("unable listen", nng_strerror(rv));

    double r = 0.0;

	char buf[254] = {};
	for (uint32_t i = 0;; i++) {
        r += (2.0*rand())/RAND_MAX-1;
        size_t n = snprintf(buf, sizeof(buf), "{\"blag\":%d, \"r\": %f, \"con\": \"constant\"}\n", i, r);
        if ((rv=(buffered_stream_send(s, buf, n)) < 0)) fatal("send", nng_strerror(rv));
		nng_msleep(200);
	}
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

	// This runs forever.  The inproc_thr never exits, so we
	// just block behind its condition variable.
	nng_thread_destroy(inproc_thr);
}
