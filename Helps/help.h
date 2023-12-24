#ifndef HELP_H
#define HELP_H
#include <stdio.h>
void printHelp() {
    printf("\n");
    printf("HAFF(1)                         User Commands                        HAFF(1)\n");
    printf("\n");
    printf("NAME\n");
    printf("       haff - compress or decompress files using Huffman coding\n");
    printf("\n");
    printf("SYNOPSIS\n");
    printf("       haff [-h] [-z source_file_name -o compressed_file_name]\n");
    printf("       haff [-h] [-u compressed_file_name -o decompressed_file_name]\n");
    printf("\n");
    printf("DESCRIPTION\n");
    printf("       haff is a command-line tool to compress or decompress files using Huffman coding.\n");
    printf("\n");
    printf("OPTIONS\n");
    printf("       -h       Print this help message\n");
    printf("       -z       Compress the source file\n");
    printf("       -u       Decompress the compressed file\n");
    printf("       -o       Specify output file name\n");
    printf("\n");
    printf("EXAMPLES\n");
    printf("       Compress:\n");
    printf("              haff -z source_file_name -o compressed_file_name\n");
    printf("\n");
    printf("       Decompress:\n");
    printf("              haff -u compressed_file_name -o decompressed_file_name\n");
    printf("\n");
    printf("SEE ALSO\n");
    printf("       haff(2), haff(3)\n");
    printf("\n");
}

#endif