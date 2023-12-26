#ifndef BUILD_H
#define BUILD_H
#define MAXSIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Haffman tree node
typedef struct Node {
    char data; // byte
    int freq;  // frequecy
    struct Node *left;
    struct Node *right;
} Node;

// PriorityQueue queue structure
typedef struct PriorityQueue {
    Node **nodes;
    int size;
} PriorityQueue;

// Haffman code
typedef struct {
    char data;      // Byte
    char code[16]; // a code for each Byte
} LeafNodeCode;

extern int count;            // number of type of bytes
extern int Array[256];       // freq of bytes
extern Node **priorityQueue; // priorityQueue
extern int numLeafNodes; // nums of leafs

Node *createNode(char, int);
int getArray(char *);
void init(void);
void getPriorityQueue(void);
void sortPriorityQueue(void);
PriorityQueue *createPriorityQueue(int);
void insert(PriorityQueue *, Node *);
Node *pop(PriorityQueue *);
Node *buildHuffmanTree(Node **, int);
void printHuffmanTree(Node *);
void generateLeafNodeCodes(Node *, char *, LeafNodeCode *, int *);
LeafNodeCode *getLeafNodeCodes(Node *);

#endif