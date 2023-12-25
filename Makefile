CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -I./DecodeOnHaffmanCode -I./EncodeOnHaffmanTree -I./HuffmanTreeBuild -I./Helps

OBJ=main.o DecodeOnHaffmanCode/decode.o EncodeOnHaffmanTree/encode.o HuffmanTreeBuild/build.o Helps/help.o

main: $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

DecodeOnHaffmanCode/decode.o: DecodeOnHaffmanCode/decode.c DecodeOnHaffmanCode/decode.h
	$(CC) -c DecodeOnHaffmanCode/decode.c -o DecodeOnHaffmanCode/decode.o $(CFLAGS)

EncodeOnHaffmanTree/encode.o: EncodeOnHaffmanTree/encode.c EncodeOnHaffmanTree/encode.h
	$(CC) -c EncodeOnHaffmanTree/encode.c -o EncodeOnHaffmanTree/encode.o $(CFLAGS)

HuffmanTreeBuild/build.o: HuffmanTreeBuild/build.c HuffmanTreeBuild/build.h
	$(CC) -c HuffmanTreeBuild/build.c -o HuffmanTreeBuild/build.o $(CFLAGS)

Helps/help.o: Helps/help.h
	$(CC) -c Helps/help.h -o Helps/help.o $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(OBJ) main
