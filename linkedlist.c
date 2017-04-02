#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct NODE Node;

struct NODE
{
    char *name;
    r_size_t size;
    void *memoryRegion;
    Node *next;
}

static Node *top = NULL;
static Node *traverseNode = NULL;

Boolean insert(const char *region_name, r_size_t region_size)
{
    Boolean rc = true;
    Node *newNode = NULL;

    newNode = (Node *)malloc(sizeof(Node));
    assert(newNode);
    if (newNode)
    {
        newNode->next = top;
        top = newNode;
        newNode->name = (char *)malloc(strlen(region_name) + 1);
        assert(newNode->name != NULL) if (newNode->name != NULL)
        {
            strcpy(newNode->name, region_name);
            assert(strcmp(newNode->name, region_name) == 0);
            region_size += 7;
            region_size = region_size - (region_size % 8);
            newNode->memoryRegion = malloc(region_size);
            if (newNode->memoryRegion == NULL)
            {
                free(newNode->name);
                free(newNode);
                rc = false;
            }
        }
    }
    return rc;
}
Boolean search( char const * const target )
{
  Boolean found = false;
  Node *curr = top;
  
  while ( curr != NULL && !found )
  {
    if ( strcmp( target, curr->string ) == 0 )
    {
      found = true;
    }
    
    else
    {
      curr = curr->next;
    }
  }
  
  return found;
}
// starts a list traversal by getting the data at top
char * firstItem()
{
  traverseNode = top->next;
  
  return top->string;
}


// gets the data at the current traversal node and increments the traversal
char * nextItem()
{
  char *item = NULL;
  
  // no need to go past the end of the list...
  if ( traverseNode != NULL )
  {
    item = traverseNode->string;
    traverseNode = traverseNode->next;
  }
  
  return item;
}