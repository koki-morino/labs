CC=gcc
CFLAGS=-g -O0 $(shell pkg-config --cflags vulkan)
LIBS=
ifeq ($(OS),Windows_NT)
    LIBS+=$(shell echo "\"${USERPROFILE}\scoop\apps\msys2\current\ucrt64\lib\libvulkan-1.dll.a\"")
else
    LIBS+=$(shell pkg-config --libs vulkan)
endif

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
