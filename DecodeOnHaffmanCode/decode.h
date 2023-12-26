#ifndef DECODE_H
#define DECODE_H
#include "../HuffmanTreeBuild/build.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void printProcess(double);
char *searchPrecode(char *, LeafNodeCode *);
void deCode(char *, char *);

#endif