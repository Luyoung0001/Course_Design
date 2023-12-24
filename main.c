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
    if(argc == 2 && strcmp(argv[1], "-h") == 0){
        // help
        printHelp();
        return 0;
    }
    if (((strcmp(argv[1], "-z") != 0) && (strcmp(argv[1], "-u") != 0)) ||
        strcmp(argv[3], "-o") != 0) {
        printf("Please enter the correct format parameters.\n");
        goto error;
    }
    // printf("arguments is fine.\n");








    return 0;
error:
    return -1;
}