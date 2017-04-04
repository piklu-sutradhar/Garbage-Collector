#include "tracker.h"


typedef struct NODE Node;


struct NODE
{
    char *name;
    r_size_t size;
    void *memoryRegion;
    Tracker *metaData;
    Node *next;
};
Boolean insert(const char *region_name, r_size_t region_size);
Boolean search(char const *const target);

Node *firstNode();
Node *nextNode();
Boolean delete (char const *const target);
Boolean createBlock(Node *init, r_size_t block_size);
void *currPointer();