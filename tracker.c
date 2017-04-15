#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "tracker.h"

static int numBlocks = 0;
//Invariant function.
/*void validateList(Tracker * blocks)
{
  Tracker *current = blocks;
  if(numBlocks == 0)
  {
    assert(current == NULL);
  }
  else if(numBlocks == 1)
  {
    assert (current != NULL);
  }
  else
  {
    assert(current->next != NULL);
  }
}*/

//Invariant to check if the list in order
void isInOrder(Tracker *list)
{
  if(numBlocks > 1)
  {
    Tracker * prev = list;
    Tracker * current = prev->next;
    void * min = list->start;
    while(current != NULL)
    {
      assert(min < current->start);
      min = current->start;
      prev = current;
      current = current->next;
    }
  }
}

//function to add a block with given pointer and size
void add( Tracker **blocks, void *start, r_size_t block_size)
{
  assert(NULL != start);
  assert(block_size > 0);
  Tracker *curr = *blocks;
  //validateList(*blocks);
  Tracker *prev = NULL;
  Tracker *new = (Tracker *) malloc(sizeof(Tracker));
  assert(new != NULL);
  new->start = start;
  assert(NULL != new->start);
  new->size = block_size;
  assert(new->size == block_size);

  //travel through the block list while find a position to place the new block.
  while(curr != NULL &&  curr->start < start )
  {
    assert(curr != NULL);
    prev = curr;
    assert(prev != NULL);
    curr = curr->next;
  }
  //if the new block should be the in the first position
  if(prev == NULL)
  {
    assert(prev == NULL);
    new->next = *blocks;
    assert(new->next == *blocks);
    *blocks = new;
    numBlocks++;
    //validateList(*blocks);
    isInOrder(*blocks);
    assert(*blocks = new);
  }
  //anywhere else in the block list.
  else
  {
    assert(prev != NULL);
    new->next = curr;
    prev->next = new;
    numBlocks++;
    isInOrder(*blocks);
    //validateList(*blocks);
    assert(prev->next != NULL);
  }
}

//function to delete a block.
Boolean delete_block( Tracker **list, void *start){
  Boolean result = false;
    Tracker * curr = *list;
    Tracker * prev = NULL;
    if(curr != NULL)
    {
      //validateList(curr);
      assert(curr != NULL);

      //travel through the block list while find the block with same pointer.
      while(curr != NULL && start != curr->start)
      {
        assert(curr != NULL);
        prev = curr;
        curr = curr->next;
      }
      // to delete the front block
    if (prev == NULL)
    {
      assert(prev == NULL);
      *list = curr->next;
      result = true;
      free(curr);
      numBlocks--;
      curr = NULL;
      assert(curr == NULL);
      //validateList(*list);
    }
    else
    {
      //to delete a block somewhere in the block list
      if(curr != NULL)
      {
        assert(curr != NULL);
        prev->next = curr->next;
        result = true;
        free(curr);
        numBlocks--;
        curr = NULL;
        assert(curr == NULL);
        //validateList(*list);
      }
    }
  }
  return result;
}

//function to return the size of the block with a given pointer.
r_size_t blockSize(Tracker *list, void *start)
{
  r_size_t size = 0;
  Tracker *curr = list;
  //validateList(curr);
  assert(curr != NULL);
  while(curr != NULL && curr->start != start)
  {
    assert(curr != NULL);
    curr = curr->next;
  }
  if(curr != NULL)
  {
    assert(curr != NULL);
    size = curr->size;
  }
  assert( size == 0 || size == curr->size);
  return size;
}
