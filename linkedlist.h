typedef enum { false, true } Boolean;

typedef unsigned short r_size_t;
typedef struct NODE Node;

struct NODE
{
    char *name;
    r_size_t size;
    void *memoryRegion;
    Node *next;
};
Boolean insert(const char *region_name, r_size_t region_size);
Boolean search( char const * const target );

Node *firstNode();
Node * nextNode();
Boolean delete( char const * const target );