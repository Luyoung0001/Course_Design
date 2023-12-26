#include "help.h"
// haffman Code char* to Byte
void saveLeafNodeCode(const char *filename, LeafNodeCode *leafNodeCodes,
                      int numLeafNodes) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("File open error");
        return;
    }

    fwrite(&numLeafNodes, sizeof(int), 1, file); // Write number of nodes first

    for (int i = 0; i < numLeafNodes; ++i) {
        fwrite(&leafNodeCodes[i], sizeof(LeafNodeCode), 1, file);
    }

    fclose(file);
}
LeafNodeCode *loadLeafNodeCode(const char *filename, int *numLeafNodes) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File open error");
        return NULL;
    }

    fread(numLeafNodes, sizeof(int), 1, file); // Read number of nodes first

    LeafNodeCode *leafNodeCodes =
        (LeafNodeCode *)malloc(*numLeafNodes * sizeof(LeafNodeCode));
    if (leafNodeCodes == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *numLeafNodes; ++i) {
        fread(&leafNodeCodes[i], sizeof(LeafNodeCode), 1, file);
    }

    fclose(file);
    return leafNodeCodes;
}

void printHelp() {
    printf("\n");
    printf("HAFF(1)                         User Commands                      "
           "  HAFF(1)\n");
    printf("\n");
    printf("NAME\n");
    printf("       haff - compress or decompress files using Huffman coding\n");
    printf("\n");
    printf("SYNOPSIS\n");
    printf("       haff [-h] [-z source_file_name -o compressed_file_name]\n");
    printf("       haff [-h] [-u compressed_file_name -o "
           "decompressed_file_name]\n");
    printf("\n");
    printf("DESCRIPTION\n");
    printf("       haff is a command-line tool to compress or decompress files "
           "using Huffman coding.\n");
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
    printf("              haff -u compressed_file_name -o "
           "decompressed_file_name\n");
    printf("\n");
    printf("SEE ALSO\n");
    printf("       haff(2), haff(3)\n");
    printf("\n");
}
