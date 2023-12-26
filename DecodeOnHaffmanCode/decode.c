#include "decode.h"

// print the process of unzipping
void printProcess(double percent) {
    static time_t lastPrintTime = 0;
    time_t currentTime = time(NULL);
    double interval = 0.5; // time break

    if (difftime(currentTime, lastPrintTime) >= interval) {
        printf("Unzipping progress: [");
        int width = 50; // size of process bar
        int progress = (int)(percent * width);

        for (int i = 0; i < width; ++i) {
            if (i < progress) {
                printf("=");
            } else {
                printf(" ");
            }
        }

        printf("] %.2f%%\r", percent * 100);
        fflush(stdout); // show the process now

        lastPrintTime = currentTime; // update the last time for printing
    }
}

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
void deCode(char *codeFileName, char *decodeFileName) {
    FILE *inFile = fopen(codeFileName, "rb");
    FILE *outFile = fopen(decodeFileName, "wb");
    if (inFile == NULL || outFile == NULL) {
        perror("File open error");
        return;
    }

    // modified here!

    // check magic number
    uint32_t magicNo = 0;
    fread(&magicNo, sizeof(uint32_t), 1,
          inFile); // Read magic number at the begining of the file first
    if (ntohl(magicNo) != 0xdeadbeef) {
        printf("the decoding file is not a zipped file.\n");
        return;
    }

    // Haffman Code
    int numLeafNodes = 0;
    fread(&numLeafNodes, sizeof(int), 1, inFile); // Read number of nodes first

    LeafNodeCode *leafNodeCodes =
        (LeafNodeCode *)malloc(numLeafNodes * sizeof(LeafNodeCode));
    if (leafNodeCodes == NULL) {
        perror("Memory allocation error");
        fclose(inFile);
        return;
    }

    for (int i = 0; i < numLeafNodes; ++i) {
        fread(&leafNodeCodes[i], sizeof(LeafNodeCode), 1, inFile);
    }

    long sizeOfFile = 0; // the size of file
    fread(&sizeOfFile, sizeof(sizeOfFile), 1, inFile);

    // coded file
    uint8_t buffer = 0;  // buffer for 1 Bytes
    char BUFF[16] = {0}; // Code cache
    int len = 0;         // the length of BUFF
    char *value = 0;     // HaffmanCode to Byte
    int result = 0;      // bit
    int Nwrite = 0;      // already written in the file
    int n = 0;           // nums of fread()
    int i = 0;           // a pointer

    printf("file: %s is unzipping!\n",
           codeFileName); // some info of the unzipping file

    while (1) {
        n = fread(&buffer, sizeof(buffer), 1,
                  inFile); // load 1 Byte once a time
        if (n < 1) {
            // end of the file
            break;
        }
        for (i = 0; i < 8; i++) {
            result = buffer & (1 << (7 - i));
            if (result == 0) {
                BUFF[len++] = '0';
            } else {
                BUFF[len++] = '1';
            }
            value = searchPrecode(BUFF, leafNodeCodes);
            if (value == NULL) {
                continue;
            } else {
                // write in
                if (fwrite(value, 1, 1, outFile) <= 0) {
                    perror("unzip error");
                    return;
                } else {
                    // recover
                    Nwrite++;
                    memset(BUFF, '\0', 16);
                    len = 0;
                }
            }
            double percentage = Nwrite / (sizeOfFile * 1.0);
            printProcess(percentage);

            if (Nwrite == sizeOfFile) {
                goto finished;
            }
        }
    }

    fclose(inFile);
    fclose(outFile);

finished:
    printf("file: %s unzip successed!\n", codeFileName);
    fclose(inFile);
    fclose(outFile);
}
