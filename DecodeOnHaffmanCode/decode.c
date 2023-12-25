#include "decode.h"
// from Haffman Code to a Byte
char *searchPrecode(char *preCode, LeafNodeCode *LeafNodeCodes) {
    for (int i = 0; i < count; i++) {
        if (strcmp(preCode, LeafNodeCodes[i].code) == 0) {
            return &LeafNodeCodes[i].data;
        }
    }
    return NULL;
}
// unzip
void deCode(char *codeFileName, char *decodeFileName,
            LeafNodeCode *LeafNodeCodes) {
    FILE *inFile = fopen(codeFileName, "rb");
    FILE *outFile = fopen(decodeFileName, "wb");
    if (inFile == NULL || outFile == NULL) {
        perror("File open error");
        return;
    }
    // maybe Code
    char preCode[257];
    int byte;
    int tag = -1;
    char value;
    while (1) {
        memset(preCode, '\0', 257);
        int i = -1;
        while ((searchPrecode(preCode, LeafNodeCodes)) == NULL) {
            byte = fgetc(inFile);
            if (byte == EOF) {
                tag = 0;
                break;
            }
            preCode[++i] = byte;
        }
        if (tag == 0) {
            break;
        }
        value = *searchPrecode(preCode, LeafNodeCodes);
        if (fwrite(&value, 1, 1, outFile) <= 0) {
            perror("unzip error");
            return;
        }
    }
    fclose(inFile);
    fclose(outFile);
}