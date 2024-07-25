CC=gcc
CFLAGS=-Wall -g

seashell: main.c
	$(CC) $(CFLAGS) -o seashell main.c
