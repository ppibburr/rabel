
LD=gcc -shared -o
AR=ar cr
RAN=ranlib
CC=gcc
RM=rm -f
INSTALL=install -d -m 755
LDCONFIG=ldconfig

INCLUDE=
CFLAGS=-Wall -O2 -I./ -fPIC
LFLAGS=  -shared
sources = *.c

all:  libabplc5

libabplc5: 
	@for file in $(sources); do \
	echo "Building $$file"; \
	$(CC) $(CFLAGS) -c $$file; \
	done
	$(LD) libabplc5.so *.o
	$(AR) libabplc5.a *.o
	$(RAN) libabplc5.a
	cp libabplc5.so /usr/local/lib
	cp libabplc5.a /usr/local/lib
	cp libabplc5.h /usr/local/include
	chmod 755 /usr/local/lib/libabplc5.*
	$(LDCONFIG)

clean:
	$(RM) *~ core *.o *.a *.so
dist:

