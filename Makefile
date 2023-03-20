CC = gcc
PKGS = gtk+-3.0
LIBS = `pkg-config --libs $(PKGS)`
CFLAGS = `pkg-config --cflags $(PKGS)` -Wall -Wextra -pedantic
SRC = gku.c


all: gku.c
	$(CC) -o gku $(CFLAGS) $(LIBS) $(SRC)
