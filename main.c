#include "build.h"
#include "decode.h"
#include "encode.h"
#include "help.h"
#include <string.h>

int main(int argc, char *argv[]) {
    // Security check
    if (argc < 2) {
        printf("too few arguments.\n");
        goto error;
    }
    if (argc != 2 && argc != 5) {
        printf("Please enter the correct number of parameters.\n");
        goto error;
    }
    if (((strcmp(argv[1], "-z") != 0) && (strcmp(argv[1], "-u") != 0)) ||
        strcmp(argv[3], "-o") != 0) {
        printf("Please enter the correct format parameters.\n");
        goto error;
    }
    // haff -h
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printHelp();
        return 0;
    }
    // prepare for zip and unzip

    // get the being zipped source file, and get the Array
    if (getArray(argv[2]) == -1) {
        printf("being zipped file open failed.\n");
        goto error;
    }

    // when it come to unzip,it needs to load to the leafNodeCodes

     // unzip
    if (strcmp(argv[1], "-u") == 0) {
        // zip -u sourcecode -o targetfile
        LeafNodeCode *leafNodeCodes = loadLeafNodeCode(".haffmancode",&count);
        deCode(argv[2], argv[4], leafNodeCodes);
        return 0;
    }

    // create oder nodes[]
    getPriorityQueue();
    // sort the order nodes[]
    sortPriorityQueue();
    // build the Haffman tree
    Node *root = buildHuffmanTree(priorityQueue, count);
    // print the Haffman tree
    // printHuffmanTree(root);
    // get Haffman Code for each leaf
    LeafNodeCode *leafNodeCodes = getLeafNodeCodes(root);

    // save the leafNodeCodes into a file, when it needs to unzip a file, it
    // must get the leafNodeCodes from the file
    saveLeafNodeCode(".haffmancode", leafNodeCodes, count);
    // print Byte: Haffman Code
    for (int i = 0; i < count; i++) {
        printf("Character: %d, Huffman Code: %s\n", leafNodeCodes[i].data,
               leafNodeCodes[i].code);
    }
    // zip process
    if (strcmp(argv[1], "-z") == 0) {
        // zip -z sourcefile -o codefile
        if (targetFile(leafNodeCodes, argv[2], argv[4]) == -1) {
            printf("zip error!\n");
            goto error;
        }
    }
    return 0;
    
error:
    return -1;
}
