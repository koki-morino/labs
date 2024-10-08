CC=gcc
CFLAGS=-Wall
LDFLAGS=
PREFIX=/usr/local
DESTDIR=./dist

EXE=hello

.POSIX:
.SUFFIXES:

all: $(EXE)

install: $(EXE)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	cp -f out/$(EXE) $(DESTDIR)$(PREFIX)/bin
	gzip < $(EXE).1 > $(DESTDIR)$(PREFIX)/share/man/man1/$(EXE).1.gz

uninstall: install
	rm -f $(DESTDIR)$(PREFIX)/bin/$(EXE)
	rm -f $(DESTDIR)$(PREFIX)/share/man/man1/$(EXE).1.gz

$(EXE): $(EXE).o
	mkdir -p out/
	$(CC) $(CFLAGS) -o out/$(EXE) $(EXE).o $(LDFLAGS)

$(EXE).o: $(EXE).S

clean: $(EXE)
	rm -rf out/ *.o

.SUFFIXES: .S .o
.S.o:
	$(CC) $(CFLAGS) -c $<
