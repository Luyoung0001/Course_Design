#ifndef HELP_H
#define HELP_H
#include "build.h"

void saveLeafNodeCode(const char *, LeafNodeCode *, int); // save to the file

LeafNodeCode *loadLeafNodeCode(const char *,
                               int *); // get LeafNodeCode from the file
void printHelp(void);

#endif