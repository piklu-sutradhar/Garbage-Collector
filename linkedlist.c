#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "linkedlist.h"

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
        assert(newNode->name != NULL);
        if (newNode->name != NULL)
        {
            strcpy(newNode->name, region_name);
            assert(strcmp(newNode->name, region_name) == 0);
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
Boolean search(char const *const target)
{
    Boolean found = false;
    Node *curr = top;

    while (curr != NULL && !found)
    {
        if (strcmp(target, curr->name) == 0)
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
Node *firstNode()
{
    if (top != NULL)
    {
        traverseNode = top->next;
    }
    return top;
}

// gets the data at the current traversal node and increments the traversal
Node *nextNode()
{
    //char *item = NULL;
    Node *current = NULL;
    // no need to go past the end of the list...
    if (traverseNode != NULL)
    {
        current = traverseNode;
        //item = traverseNode->string;
        traverseNode = traverseNode->next;
    }

    return current;
}
Boolean delete( char const * const target )
{
  Boolean deleted = false;
  Node *curr = top;
  Node *prev = NULL;
  
  while ( curr != NULL && strcmp( target, curr->name ) != 0 )
  {
    prev = curr;
    curr = curr->next;
  }

  if ( curr != NULL )
  {
    if ( prev != NULL )
      prev->next = curr->next;
    else
      top = curr->next;
    
    free( curr->name );
    free( curr->memoryRegion);
    free( curr );
    deleted = true;
    //numNodes--;
  }
  
  return deleted;
}