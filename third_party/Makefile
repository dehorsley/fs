all: lib/libnng.a lib/libjansson.a

export PREFIX = $(shell pwd)


JANSSON_VERSION = 2.13.1

lib/libnng.a: src/nng-1.3.0.tar.gz
	$(MAKE) -C src -f nng.make install

lib/libjansson.a: src/jansson-$(JANSSON_VERSION).tar.gz
	cd src &&\
	tar xzf jansson-$(JANSSON_VERSION).tar.gz  &&\
	cd jansson-$(JANSSON_VERSION) &&\
	./configure -q --enable-static --disable-shared --prefix=$(PREFIX) &&\
	make install

clean: 
	@rm -rf include
	@rm -rf lib
	@rm -rf src/jansson-$(JANSSON_VERSION)
	$(MAKE) -C src -f  nng.make clean
