#ifndef ENCODE_H
#define ENCODE_H
#include "build.h"
#include <sys/stat.h>
#include "decode.h"
long getFileSize(const char *filename);

char *searchCode(LeafNodeCode *, char);
int targetFile(LeafNodeCode *, char *, char *);
#endif