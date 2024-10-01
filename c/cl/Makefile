CC=gcc
CFLAGS=-g -O0 $(shell pkg-config --cflags opencl)
LIBS=$(shell pkg-config --libs opencl)

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

EXE = cl

.PHONY: clean all

all: $(EXE) $(SHADER)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXE)* *.o
