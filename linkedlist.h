typedef struct NODE Node;

struct NODE
{
    char *name;
    r_size_t size;
    void *memoryRegion;
    Node *next;
}
Boolean insert(const char *region_name, r_size_t region_size);
Boolean search( char const * const target );
Node * firstItem();
Node * nextItem();