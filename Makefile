CC=gcc
CFLAGS=-Wall -g

seashell: main.c
	$(CC) $(CFLAGS) -o seashell main.c

tokenizer: tokenizer.c
	$(CC) $(CFLAGS) -o tokenizer tokenizer.c
