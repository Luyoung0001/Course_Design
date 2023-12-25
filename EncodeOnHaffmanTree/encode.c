#include "encode.h"
#include "../HuffmanTreeBuild/build.h"
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
    FILE *fileTarget = fopen(fileTargetName, "w");
    if (fileSource == NULL || fileTarget == NULL) {
        perror("zip failed!\n");
        return -1;
    }

    int byte;
    while ((byte = fgetc(fileSource)) != EOF) {
        fprintf(fileTarget, "%s", searchCode(leafNodeCodes, byte));
    }
    fclose(fileSource);
    fclose(fileTarget);
    return 0;
}