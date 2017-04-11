#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "tracker.h"


void add( Tracker **blocks, void *start, r_size_t block_size)
{
  assert(NULL != start);
  assert(block_size > 0);
  Tracker *curr = *blocks;
  Tracker *prev = NULL;
  Tracker *new = (Tracker *) malloc(sizeof(Tracker));
  assert(new != NULL);
  new->start = start;
  assert(NULL != new->start);
  new->size = block_size;
  assert(new->size == block_size);
  while(curr != NULL &&  curr->start < start )
  {
    assert(curr != NULL);
    prev = curr;
    assert(prev != NULL);
    curr = curr->next;
  }
  if(prev == NULL)
  {
    assert(prev == NULL);
    new->next = *blocks;
    assert(new->next == *blocks);
    *blocks = new;
    assert(*blocks = new);
  }
  else
  {
    assert(prev != NULL);
    new->next = curr;
    prev->next = new;
    assert(prev->next != NULL);
  }
}
Boolean delete_block( Tracker **list, void *start){
  Boolean result = false;
    Tracker * curr = *list;

    Tracker * prev = NULL;
    if(curr != NULL)
    {
      assert(curr != NULL);
      while(curr != NULL && start != curr->start)
      {
        assert(curr != NULL);
        prev = curr;
        curr = curr->next;
      }
    if (prev == NULL)
    {
      assert(prev == NULL);
      *list = curr->next;
      result = true;
      free(curr);
      curr = NULL;
      assert(curr == NULL);
    }
    else
    {
      if(curr != NULL)
      {
        assert(curr != NULL);
        prev->next = curr->next;
        result = true;
        free(curr);
        curr = NULL;
        assert(curr == NULL);
      }
    }
  }
  return result;
}
r_size_t blockSize(Tracker *list, void *start)
{
  r_size_t size = 0;
  Tracker *curr = list;
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
