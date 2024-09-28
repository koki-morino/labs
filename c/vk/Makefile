CC=gcc
CFLAGS=-g -O0 $(shell pkg-config --cflags vulkan)
LIBS=$(shell pkg-config --libs vulkan)

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

EXE = gpu

SHADER_SRC = shader.comp
SHADER = compute.spv

.PHONY: all clean

all: $(EXE) $(SHADER)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SHADER): $(SHADER_SRC)
	glslangValidator -V $< -o $@

clean:
	rm -f $(EXE)* *.o *.spv
