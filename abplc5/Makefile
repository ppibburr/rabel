
AR=ar crs
RAN=ranlib
CC=gcc
LD=gcc
RM=rm -f
INSTALL=install
srcdir = src
libdir = lib
FILENAME = abplc5v`cat /abplc5/.version`.tar.gz
BETANAME = abplc5v`cat /abplc5/.version`b.tar.gz

INCLUDE = -I. -I.. -I./$(srcdir) -I./$(libdir)
CFLAGS=-Wall -O2 -I. -I./lib
LFLAGS= -labplc5
LIBSUBDIRS = lib
UTILSUBDIRS = src
DOCSDIR = docs

all:  
	@for subdir in $(LIBSUBDIRS) $(UTILSUBDIRS); do \
	echo "Making $@ in $$subdir"; \
	(cd $$subdir && make $@) || exit 1; \
	done

utils:
	@for subdir in $(UTILSUBDIRS); do \
	echo "Making $@ in $$subdir"; \
	(cd $$subdir && make $@) || exit 1; \
	done

beta:   clean
	cd /; \
	$(RM) abplc5.tar $(BETANAME); \
	tar czvf  $(BETANAME) abplc5; \
	chown ron:users /$(BETANAME)

release:   clean
	awk -f release.awk -- .version > .newversion
	mv .newversion .version
	cd /; \
	$(RM) abplc5.tar $(FILENAME); \
	tar czvf  $(FILENAME) abplc5; \
	chown ron:users /$(FILENAME)

major:   clean
	awk -f major.awk -- .version > .newversion
	mv .newversion .version
	cd /; \
	$(RM) abplc5.tar $(FILENAME); \
	tar czvf  $(FILENAME) abplc5; \
	chown ron:users /$(FILENAME)
	

clean:  
	@for subdir in $(LIBSUBDIRS) $(UTILSUBDIRS) $(DOCSDIR); do \
	echo "Making $@ in $$subdir"; \
	(cd $$subdir && make $@) || exit 1; \
	done
	$(RM) abtypedread abtypedwrite abwordread abwordwrite abstat abupload \
slcread slcwrite stress absetmode section name *~



