CC = gcc
CFLAGS = `pkg-config --libs --cflags gtk+-3.0`

all: gku.c
	gcc -o gku $(CFLAGS) gku.c