#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "linkedlist.h"
#include "tracker.h"

static Node *top = NULL;
static Node *traverseNode = NULL;
static int numNodes = 0;

//Invariant
void validateLinkedlist()
{
  if(numNodes == 0)
  {
    assert(top == NULL);
  }
  else if(numNodes == 1)
  {
    assert (top != NULL);
  }
  else
  {
    assert(top->next != NULL);
  }
}
void validateRalloc(Node * init, void * start_block, r_size_t block_size)
{
  r_size_t counter = 0;
  assert(start_block != NULL);
  assert(block_size > 0 && block_size <= init->size);
  assert(start_block + block_size <= init->memoryRegion + init->size);
  for(counter = 0; counter < block_size; counter++)
  {
    //*((char *)(start_block+counter)) = '0';
    assert(*((char *)(start_block+counter)) == '0');
  }
}
//function to add a new region
Boolean insert(const char *region_name, r_size_t region_size)
{
  Boolean rc = false;
  if(region_name != NULL && region_size >0)
  {
    Node *newNode = NULL;
    assert(newNode == NULL);
    validateLinkedlist();
    newNode = (Node *)malloc(sizeof(Node));
    assert(newNode);
    if (newNode)
    {
        newNode->next = top;
        top = newNode;
        assert(top != NULL);
        newNode->name = (char *)malloc(strlen(region_name) + 1);
        assert(newNode->name != NULL);
        if (newNode->name != NULL)
        {
            strcpy(newNode->name, region_name);
            assert(strcmp(newNode->name, region_name) == 0);
            assert(strlen(region_name) == strlen(newNode->name));
            newNode->size = region_size;
            assert(newNode->size == region_size);
            newNode->memoryRegion = malloc(region_size);
            assert(newNode->memoryRegion != NULL);
            if (newNode->memoryRegion != NULL)
            {
                newNode->blocks = NULL;
                numNodes++;
                rc = true;
                validateLinkedlist();
            }
            else
            {
                free(newNode->name);
                newNode->name = NULL;
                assert(newNode->name == NULL);
                free(newNode);
                newNode = NULL;
                assert(newNode == NULL);
                assert(!rc);
            }
        }
    }
  }
  return rc;
}
Boolean search(char const *const target)
{
  validateLinkedlist();
    Boolean found = false;
    assert(target != NULL);
    if(strlen(target)>0)
    {
      Node *curr = top;
      while (curr != NULL && !found)
      {
        assert(curr != NULL);
          if (strcmp(target, curr->name) == 0)
          {
            assert(strlen(target) == strlen(curr->name));
            found = true;
            assert(found == true);
          }
          else
          {
              curr = curr->next;
          }
      }
    }

    return found;
}
// starts a list traversal by getting the data at top
Node *firstNode()
{
  validateLinkedlist();
    if (top != NULL)
    {
      assert(top != NULL);
        traverseNode = top->next;
    }
    return top;
}

// gets the data at the current traversal node and increments the traversal
Node *nextNode()
{
  validateLinkedlist();
    Node *current = NULL;
    if (traverseNode != NULL)
    {
      assert(traverseNode != NULL);
        current = traverseNode;
        traverseNode = traverseNode->next;
    }
    return current;
}
Boolean delete (char const *const target)
{
  validateLinkedlist();
    Boolean deleted = false;
    Node *curr = top;
    Node *prev = NULL;
    assert(target != NULL);
    while (curr != NULL && strcmp(target, curr->name) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL)
    {
        if (prev != NULL)
        {
            prev->next = curr->next;
            numNodes--;
            validateLinkedlist();
        }
        else
        {
          top = curr->next;
          numNodes--;
          validateLinkedlist();
        }
        free(curr->name);
        curr->name = NULL;
        assert(curr->name == NULL);
        free(curr->memoryRegion);
        curr->memoryRegion = NULL;
        assert(curr->memoryRegion == NULL);
        while(curr->blocks != NULL)
        {
          assert(curr->blocks != NULL);
          Tracker *current = curr->blocks;
          assert(current != NULL);
          curr->blocks = (curr->blocks)->next;
          free(current);
          current = NULL;
          assert(current == NULL);
        }
        free(curr);
        curr = NULL;
        assert(curr == NULL);
        deleted = true;
        assert(deleted == true);
    }
    validateLinkedlist();
    return deleted;
}
void *find_block(Node *init, r_size_t block_size)
{
  validateLinkedlist();
  assert(init != NULL);
  void *start_block = NULL;
  r_size_t counter = 0;
  r_size_t hasFree = 0;
  block_size = (block_size + 7) - ((block_size + 7)%8);
  assert(block_size > 0 && block_size <= init->size);
  assert(block_size % 8 == 0);
  Tracker *current = init->blocks;
  void *inMemory = init->memoryRegion;
  assert(inMemory != NULL);
  void *nextFree = init->memoryRegion;
  assert(nextFree != NULL);

  while(counter < init->size && hasFree < block_size)
  {
    if(current != NULL && (inMemory + counter == current->start))
    {

      counter = counter + current->size;
      assert(counter <= init->size);
      nextFree = inMemory + counter;
      assert(nextFree <= (init->memoryRegion + init->size));
      current = current->next;
      hasFree = 0;
    }
    else
    {

      assert(counter <= init->size);
      counter++;
      assert(hasFree < block_size);
      hasFree++;
      assert(hasFree <= block_size);
    }
  }

  if(hasFree == block_size && (nextFree + block_size <= init->memoryRegion + init->size))
  {
    assert(hasFree == block_size);
    for(counter = 0; counter < block_size; counter++)
    {
      *((char *)(nextFree+counter)) = '0';
      //assert(*((char *)(nextFree+counter)) == '0');
    }
    start_block = nextFree;
    assert(start_block != NULL);
    validateRalloc(init,start_block,block_size);
    add(&init->blocks, start_block, block_size);
    }
  return start_block;
}
void printBlock(Node const *const init)
{
  assert(init != NULL);
  r_size_t sum = 0;
  double percentage = 0;
  int numBlocks = 0;
  Tracker * current = init->blocks;
  while(current != NULL)
  {
    assert(current != NULL);
    assert(current->size > 0);
    sum += current->size;
    numBlocks++;
    printf(" |  Block: %d\n",numBlocks);
    printf(" |  ------------------------------\n");
    printf(" |  | Address: %p\n", current->start);
    printf(" |  | Block Size: %d\n", current->size);
    printf(" |  ------------------------------\n");
    current = current->next;
  }
  percentage = (double)sum / (double)init->size * 100;
  printf(" | %.2f%c percent memory is free\n", 100.00 - percentage,37);
}
r_size_t currSize(Node *init, void *block_ptr)
{
  r_size_t size = 0;
  if(init != NULL && block_ptr != NULL)
  {
    assert(init != NULL);
    assert(block_ptr != NULL);
    size = blockSize(init->blocks, block_ptr);
  }
  return size;
}
Boolean freeMemory(Node * init, void * start)
{
  Boolean rc = false;
  if(init != NULL && start != NULL)
  {
    assert(init != NULL);
    assert(start != NULL);
    rc = delete_block(&init->blocks, start);
  }
  return rc;
}
