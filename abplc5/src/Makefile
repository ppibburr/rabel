
AR=ar crs
RAN=ranlib
CC=gcc 
LD=gcc 
RM=rm -f
INSTALL=install
srcdir = src
libdir = lib

INCLUDE = -I. -I.. -I../$(srcdir) -I../$(libdir)
CFLAGS=-Wall -O2 
LFLAGS= -L../lib -labplc5
LIBSUBDIRS = lib
UTILSUBDIRS = src
sources = abtypedread abtypedwrite abwordread abwordwrite abstat absetmode abupload \
name section slcread slcwrite stress


all:  utils

utils:
	@for file in $(sources); do \
	echo "Building $$file"; \
	$(CC) $(INCLUDE) $(CFLAGS) -c $$file.c; \
	$(CC) $$file.o $(LFLAGS) -o ../$$file ; \
	done


install:
	$(INSTALL) -m 755 $(MTARGET) /usr/local/bin

clean:
	$(RM) *~ core *.o 


dist:  clean
	$(RM) /abplc5.tar
	tar -c -f /abplc5.tar /abplc5
	gzip -c /abplc5.tar > /abplc5.tar.gz
	$(RM) /abplc5.tar
	chown ron /abplc5.tar.gz
	chgrp users /abplc5.tar.gz 
