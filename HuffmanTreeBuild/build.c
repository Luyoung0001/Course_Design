#include "build.h"

int count = 0;              // number of type of bytes
int Array[256] = {0};       // freq of bytes
Node **priorityQueue = {0}; // priorityQueue
int numLeafNodes = 0;       // nums of leafs

// iniy
void init() {
    count = 0;
    for (int i = 0; i < 256; i++) {
        Array[i] = 0;
    }
}

// create a Haffman-Tree node
Node *createNode(char data, int freq) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// where the freq of Bytes lie
int getArray(char *fileName) {
    FILE *file = fopen(fileName, "rb"); // "rb" bini-read mode

    if (file == NULL) {
        perror("File open error");
        return -1;
    }

    unsigned char byte; // must be unsigned
    while (fread(&byte, 1, 1, file) > 0) {
        Array[byte]++;
    }
    fclose(file);
    // counts for the num of Bytes
    for (int i = 0; i < 256; i++) {
        if (Array[i] != 0) {
            count++;
        }
    }
    return count;
}

// create the order queue
void getPriorityQueue() {
    int k = -1;
    priorityQueue = (Node **)malloc(count * sizeof(Node *));
    for (int i = 0; i <= 255; i++) {
        if (Array[i] != 0) {
            k++;
            priorityQueue[k] = createNode(i, Array[i]);
        }
    }
    // test
    // printf("Byte value---the freq of it\n");
    // for (int i = 0; i < 256; i++) {
    //     printf("%d: %d\n", i, Array[i]);
    // }
}
// sort the order queue
void sortPriorityQueue() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (priorityQueue[j]->freq > priorityQueue[j + 1]->freq) {
                Node *temp = priorityQueue[j];
                priorityQueue[j] = priorityQueue[j + 1];
                priorityQueue[j + 1] = temp;
            }
        }
    }
    // test
    // for (int i = 0; i < count; i++) {
    //     printf("%d: %d\n", priorityQueue[i]->data, priorityQueue[i]->freq);
    // }
}

// create empty priorityQueue
PriorityQueue *createPriorityQueue(int capacity) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->nodes = (Node **)malloc(sizeof(Node *) * capacity);
    queue->size = 0;
    return queue;
}

// insert node to the priorityQueue
void insert(PriorityQueue *queue, Node *node) {
    int i = queue->size;
    while (i > 0 && node->freq < queue->nodes[(i - 1) / 2]->freq) {
        queue->nodes[i] = queue->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->nodes[i] = node;
    queue->size++;
}

// pop the smallest freq node
Node *pop(PriorityQueue *queue) {
    if (queue->size <= 0) {
        return NULL;
    }
    Node *minNode = queue->nodes[0];
    queue->size--;

    Node *lastNode = queue->nodes[queue->size];
    int i = 0;
    while (i * 2 + 1 < queue->size) {
        int child = i * 2 + 1;
        if (child + 1 < queue->size &&
            queue->nodes[child + 1]->freq < queue->nodes[child]->freq) {
            child++;
        }
        if (lastNode->freq <= queue->nodes[child]->freq) {
            break;
        }
        queue->nodes[i] = queue->nodes[child];
        i = child;
    }
    queue->nodes[i] = lastNode;

    return minNode;
}

// create Haffman tree
Node *buildHuffmanTree(Node **nodes, int size) {
    if (size <= 0) {
        return NULL;
    }

    // with a PriorityQueue
    PriorityQueue *queue = createPriorityQueue(size);
    for (int i = 0; i < size; i++) {
        insert(queue, nodes[i]);
    }

    // tree building...
    while (queue->size > 1) {
        Node *left = pop(queue);
        Node *right = pop(queue);
        Node *parent = createNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        insert(queue, parent);
    }

    Node *root = pop(queue);
    free(queue->nodes);
    free(queue);

    return root;
}
// print the Haffman Tree
void printHuffmanTree(Node *root) {
    if (root == NULL) {
        return;
    }
    // printf("%d - %d\n", root->data, root->freq);
    printHuffmanTree(root->left);
    printHuffmanTree(root->right);
}

// generate Haffman code
void generateLeafNodeCodes(Node *node, char *currentCode,
                           LeafNodeCode *leafNodeCodes, int *index) {
    if (node == NULL) {
        return;
    }
    // go left +0
    char leftCode[256];
    strcpy(leftCode, currentCode);
    strcat(leftCode, "0");
    generateLeafNodeCodes(node->left, leftCode, leafNodeCodes, index);

    // go right +1
    char rightCode[256];
    strcpy(rightCode, currentCode);
    strcat(rightCode, "1");
    generateLeafNodeCodes(node->right, rightCode, leafNodeCodes, index);

    if (node->left == NULL && node->right == NULL) {
        // find the leaf node, save the complete code
        leafNodeCodes[*index].data = node->data;
        strcpy(leafNodeCodes[*index].code, currentCode);
        (*index)++;
    }
}

// create LeafNodeCode[]
LeafNodeCode *getLeafNodeCodes(Node *root) {
    numLeafNodes = count;

    LeafNodeCode *leafNodeCodes =
        (LeafNodeCode *)malloc(numLeafNodes * sizeof(LeafNodeCode));

    int index = 0;
    char currentCode[256] = "";

    // generate leaf code
    generateLeafNodeCodes(root, currentCode, leafNodeCodes, &index);

    return leafNodeCodes;
}


