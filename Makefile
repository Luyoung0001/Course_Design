CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I./DecodeOnHaffmanCode -I./EncodeOnHaffmanTree -I./HuffmanTreeBuild -I./Helps

main: main.c
	@$(CC) -o main main.c $(CFLAGS)

.PHONY: clean

clean:
	@rm -f main


.PHONY: help

help:
	@echo "help!"
