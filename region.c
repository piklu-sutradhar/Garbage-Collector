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
void validateCurrent(const char *region_name)
{
  if(firstNode() != NULL)
  {
    assert(strcmp(region_name, curr->name) == 0);
  }
}
Boolean rinit(const char *region_name, r_size_t region_size)
{
  Boolean rc = false;
  if( region_name != NULL && region_size >0)
  {
    assert(region_name != NULL);
    assert(region_size > 0 );
      if (region_size > 0)
      {
          region_size += 7;
          region_size = region_size - (region_size % 8);
          assert(region_size % 8 == 0);
          if (search(region_name) == false)
          {
              Boolean inserted = insert(region_name, region_size);

              if (inserted == true)
              {
                assert(inserted == true);
                rc = rchoose(region_name);
              }
          }
          else
          {
              //printf("Name \"%s\" is already taken \n", region_name);
              //curr = NULL;
              rc = false;
          }
      }
  }
  else{
    rc = false;
  }
  return rc;
}
Boolean rchoose(const char *region_name)
{
  Boolean rc = false;
  if(region_name != NULL)
  {
    assert(region_name != NULL);
    Node * chosen = firstNode();
    while (chosen != NULL && strcmp(chosen->name, region_name) != 0)
    {
      chosen = nextNode();
    }
    if (chosen != NULL)
    {
      rc = true;
      curr = chosen;
      validateCurrent(region_name);
    }
  }
  return rc;
}
const char *rchosen()
{
    char *name = NULL;
    if (curr != NULL)
    {
      assert(curr != NULL);
      name = curr->name;
      assert(name != NULL);
    }
    return name;
}
void *ralloc(r_size_t block_size)
{
  void * block_start = NULL;
  if(block_size>0 && curr != NULL)
  {
    assert(curr != NULL);
    block_start = find_block(curr, block_size);
  }

   return block_start;
}

r_size_t rsize(void *block_ptr)
{
  r_size_t size = 0;
  if(block_ptr != NULL){
    assert(block_ptr != NULL);
    size = currSize(curr,block_ptr);
  }
  return size;
}
Boolean rfree(void *block_ptr)
{
  Boolean result = false;
  if(block_ptr != NULL && curr != NULL)
  {
    result = freeMemory(curr,block_ptr);
  }
  return result;
}
void rdestroy(const char *region_name)
{
  if(region_name != NULL)
  {
    if(curr != NULL && strcmp(region_name, curr->name) ==0)
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
    else
    {
      if(delete (region_name) == false)
      {
        if(search(region_name) == true)
        {
            printf("There is an error to delete Node with name \"%s\"\n", region_name);
        }
      }
    }
  }
}
void rdump()
{
    Node *toPrint= firstNode();
  if(toPrint != NULL)
  {
    printf("==============================================\n");
    printf("============ Print All Regions ===============\n");
    printf("==============================================\n");
    while (toPrint != NULL)
    {
      assert(toPrint != NULL);
        printf(" *********************************************\n");
        printf(" | The Name of the region: \"%s\"             \n", toPrint->name);
        printf(" | The buffer pointer: %p                    \n", toPrint->memoryRegion);
        printf(" | The size of the buffer: %hu               \n", toPrint->size);
        printBlock(toPrint);
        printf(" *********************************************\n\n");
        toPrint= nextNode();
    }
  }
  else
  {
    printf("==============================================\n");
    printf("============ The list is empty ===============\n");
    printf("==============================================\n");
  }
}
