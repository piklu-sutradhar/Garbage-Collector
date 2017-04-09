#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "linkedlist.h"
#include "tracker.h"

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
            newNode->size = region_size;
            newNode->memoryRegion = malloc(region_size);
            if (newNode->memoryRegion != NULL)
            {
                int i;
                for (i = 0; i < region_size; i++)
                {
                    *(((char *)newNode->memoryRegion) + i) = '0';
                }
                //newNode->metaData = (Tracker *) malloc(sizeof(Tracker));
                //current = newNode->metaData;
                newNode->blocks = NULL;
            }
            else
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
          //currentNode = curr;
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
Boolean delete (char const *const target)
{
    Boolean deleted = false;
    Node *curr = top;
    Node *prev = NULL;

    while (curr != NULL && strcmp(target, curr->name) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL)
    {
        if (prev != NULL)
            prev->next = curr->next;
        else
            top = curr->next;

        free(curr->name);
        free(curr->memoryRegion);

        while(curr->blocks != NULL)
        {
          Tracker *current = curr->blocks;
          curr->blocks = (curr->blocks)->next;
          free(current);
        }
        //free(curr->blocks);
        free(curr);
        deleted = true;
        //numNodes--;
    }

    return deleted;
}
void *find_block(Node *init, r_size_t block_size)
{
  //Boolean found = false;
  void *start_block = NULL;
  r_size_t counter = 0;
  r_size_t hasFree = 0;
  block_size = (block_size + 7) - ((block_size + 7)%8);
  Tracker *current = init->blocks;
  void *inMemory = init->memoryRegion;
  void *nextFree = init->memoryRegion;
  /*if(current == NULL && block_size < init->size){
    add(&init->blocks, nextFree, block_size);
    start_block = nextFree;
  }*/
  //printf("%s\n",inMemory);
  for (counter = 0; counter < init->size && hasFree < block_size;)
  {
    if(current != NULL && inMemory == current->start)
    {

      //printf("%s\n",current->start);
      counter = counter + current->size;
      inMemory = inMemory + current->size;
      nextFree = nextFree + current->size;
      current = current->next;
      hasFree = 0;
    }
    else
    {
      counter++;
      hasFree++;
      inMemory++;
    }
  }
  if(hasFree == block_size)
  {

    //printf("Here before rdestroy\n");
    add(&init->blocks, nextFree, block_size);
    start_block = nextFree;
  }
  return start_block;
}
void printBlock(Node *init)
{
  r_size_t sum = 0;
  double percentage = 0;
  int numBlocks = 0;
  Tracker * current = init->blocks;
  //sum = allocatedSpace(&init->blocks);

  while(current != NULL)
  {
  //  printf("Here before rdestroy");
    sum += current->size;
    numBlocks++;
    printf("|  Block: %d\n",numBlocks);
    printf("|  ------------------------------\n");
    printf("|  | Address: %p\n", current->start);
    printf("|  | Block Size: %d\n", current->size);
    printf("|  ------------------------------\n");
    current = current->next;
  }
  percentage = (double)sum / (double)init->size * 100;
  printf("| %.2f percent memory is free\n", 100.00 - percentage);
}
r_size_t currSize(Node *init, void *block_ptr)
{
  r_size_t size = 0;
  size = blockSize(init->blocks, block_ptr);
  return size;
}
Boolean freeMemory(Node * init, void * start)
{
  return delete_block(&init->blocks, start);
}
