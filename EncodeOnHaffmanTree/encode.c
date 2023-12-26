#include "encode.h"
#include "../HuffmanTreeBuild/build.h"
#define MASKCODE 0x000000ff
#define ZERO 0x00

// get the size of a file
long getFileSize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

// search: from a Byte to a Haffman Code
char *searchCode(LeafNodeCode *leafNodeCodes, char data) {
    for (int i = 0; i < count; i++) {
        if (leafNodeCodes[i].data == data) {
            return leafNodeCodes[i].code;
        }
    }
    return 0;
}
// zip
int targetFile(LeafNodeCode *leafNodeCodes, char *fileSourceName,
               char *fileTargetName) {
    FILE *fileSource = fopen(fileSourceName, "rb");
    FILE *fileTarget = fopen(fileTargetName, "wb");
    if (fileSource == NULL || fileTarget == NULL) {
        perror("zip failed!\n");
        return -1;
    }
    // info
    printf("file: %s is zipping now!\n", fileSourceName);

    // modify here

    // magic number
    char magicNumber[] = {0xde, 0xad, 0xbe, 0xef}; // magic number: 0xdeadbeef
    fwrite(magicNumber, sizeof(char), sizeof(magicNumber), fileTarget);

    // Haffman Code
    fwrite(&numLeafNodes, sizeof(int), 1, fileTarget);
    for (int i = 0; i < numLeafNodes; ++i) {
        fwrite(&leafNodeCodes[i], sizeof(LeafNodeCode), 1, fileTarget);
    }

    // the size of the file
    long sizeOfFile = getFileSize(fileSourceName);
    fwrite(&sizeOfFile, sizeof(long), 1, fileTarget);

    // file code
    long Nwrite = 0;        // how many Bytes already been written in the file
    uint32_t buffer = 0;    // buffer for 4 Bytes
    int lengthOfBUffer = 0; // length of buffer
    int byte;               // Byte from the source file
    int lenOfHaffmanCode = 0;
    while ((byte = fgetc(fileSource)) != EOF) {
        char *haffman_code = searchCode(leafNodeCodes, byte);
        lenOfHaffmanCode = strlen(haffman_code);

        for (int i = 0; i < lenOfHaffmanCode; i++) {
            if (haffman_code[i] == '1') {
                buffer ^= (uint32_t)1;
            } else {
                buffer ^= (uint32_t)0;
            }
            lengthOfBUffer++;

            if (lengthOfBUffer == 8) {

                // get the lowest Byte
                // write the Byte to the file
                unsigned char key = buffer & MASKCODE;
                fprintf(fileTarget, "%c", key);
                lengthOfBUffer -= 8;

                // show the process
                double percent = (Nwrite++) / (sizeOfFile * 1.0);
                printProcess(percent);
            }
            buffer <<= 1;
        }
    }
    // check
    if (lengthOfBUffer == 0) {
        unsigned char key = ZERO;
        fprintf(fileTarget, "%c", key);
    } else {
        // recover
        buffer >>= 1;
        int numsOfBit0 = 8 - lengthOfBUffer;
        buffer <<= numsOfBit0;

        // write last code
        unsigned char key = buffer & MASKCODE;
        fprintf(fileTarget, "%c", key);
    }
    fclose(fileSource);
    fclose(fileTarget);
    printf("file: %s zipped successed!\n", fileSourceName);

    // print info:
    long sizeOfSource = getFileSize(fileSourceName);
    long sizeOfTarget = getFileSize(fileTargetName);

    printf("the rate of the zip is %.5f\n",
           sizeOfTarget / (sizeOfSource * 1.0));
    return 0;
}