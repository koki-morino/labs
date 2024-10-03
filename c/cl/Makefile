CC=gcc
CFLAGS=-g -O0 $(shell pkg-config --cflags OpenCL)
LIBS=$(shell pkg-config --libs OpenCL)

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

EXE = cl

.PHONY: clean all

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXE)* *.o
