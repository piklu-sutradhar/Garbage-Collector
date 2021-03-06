#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include "tracker.h"

typedef struct NODE Node;

struct NODE
{
    char *name;
    r_size_t size;
    void *memoryRegion;
    Tracker *blocks;
    Node *next;
};

void *find_block(Node *init, r_size_t block_size);
Boolean insert(const char *region_name, r_size_t region_size);
Boolean search(char const *const target);
Node *firstNode();
Node *nextNode();
Boolean delete (char const *const target);
void printBlock(Node const *const init);
r_size_t currSize(Node *init, void *block_ptr);
Boolean freeMemory(Node * init, void * start);
#endif
