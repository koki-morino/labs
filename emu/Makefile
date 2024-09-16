OBJS = main.o

CC = gcc
LD = ld
AS = nasm
CFLAGS += -Wall -fno-asynchronous-unwind-tables -g -fno-stack-protector
LDFLAGS += --entry=func --oformat=binary

.PHONY: all
all : helloworld.bin px86.exe

px86.exe : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c $<

helloworld.bin : helloworld.asm
	$(AS) -f bin -o $@ $<
