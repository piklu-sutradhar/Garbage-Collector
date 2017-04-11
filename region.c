#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "regions.h"
#include "linkedlist.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
static Node *curr = NULL;
//static Tracker *currentTrack = NULL;
//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
Boolean rinit(const char *region_name, r_size_t region_size)
{
    Boolean rc = false;
    if (region_size > 0)
    {
        region_size += 7;
        region_size = region_size - (region_size % 8);
        if (search(region_name) == false)
        {
            Boolean inserted = insert(region_name, region_size);
            if (inserted == true)
            {
                rc = rchoose(region_name);
            }
        }
        else
        {
            printf("Name \"%s\" is already taken \n", region_name);
            curr = NULL;
            rc = false;
        }
    }

    return rc;
}
Boolean rchoose(const char *region_name)
{
    Boolean rc = false;
    curr = firstNode();
    while (curr != NULL && strcmp(curr->name, region_name) != 0)
    {
        curr = nextNode();
    }
    if (curr != NULL)
    {
        rc = true;
    }
    return rc;
}
const char *rchosen()
{
    char *name = NULL;
    if (curr != NULL)
    {
        name = curr->name;
    }
    return name;
}
void *ralloc(r_size_t block_size)
{
  assert(curr != NULL);
  void * allocated = find_block(curr, block_size);
  //printf("choosen buffer: %p\n", allocated);
   return allocated;
}

r_size_t rsize(void *block_ptr)
{
  return currSize(curr,block_ptr);
}
Boolean rfree(void *block_ptr)
{
  return freeMemory(curr,block_ptr);
}
void rdestroy(const char *region_name)
{
    if(delete (region_name) == true)
    {
      curr = firstNode();
    }
    else
    {
      printf("There is an error to delete Node with name \"%s\"\n", region_name);
    }
}
void rdump()
{
    Node *toPrint= firstNode();
    while (toPrint != NULL)
    {
      assert(toPrint != NULL);
        printf("*********************************************\n");
        printf("| The Name of the region: %s                \n", toPrint->name);
        printf("| The buffer pointer: %p                    \n", toPrint->memoryRegion);
        printf("| The size of the buffer: %hu               \n", toPrint->size);
        printBlock(toPrint);
        printf("*********************************************\n\n");
        toPrint= nextNode();
    }
}
