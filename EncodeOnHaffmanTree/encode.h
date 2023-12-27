#ifndef ENCODE_H
#define ENCODE_H
#include "build.h"
#include <sys/stat.h>
#include "decode.h"

#define MASKCODE 0xff
#define ZERO 0x00
long getFileSize(const char *filename);

char *searchCode(LeafNodeCode *, char);
int targetFile(LeafNodeCode *, char *, char *);
#endif