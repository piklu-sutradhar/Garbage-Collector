#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "tracker.h"


void add( Tracker **blocks, void *start, r_size_t block_size)
{
  Tracker *curr = *blocks;
  Tracker *prev = NULL;
  Tracker *new = (Tracker *) malloc(sizeof(Tracker));
  new->start = start;
  new->size = block_size;

  while(curr != NULL &&  curr->start < start )
  {
    prev = curr;
    curr = curr->next;
  }
  if(prev == NULL)
  {
    new->next = *blocks;
    *blocks = new;
  }
  else
  {
    new->next = curr;
    prev->next = new;
  }
  //return start;
}
void delete_block( Tracker *list, void *start){
    Tracker * curr = list;
    Tracker * prev = NULL;
    if(curr != NULL)
    {
      while(curr != NULL && start != curr->start)
      {
        prev = curr;
        curr = curr->next;
      }
    if (prev != NULL)
    {
      list = list->next;
    }
    else
    {
      prev->next = curr->next;
      //free(curr);
    }
    free(curr);
  }
}
r_size_t blockSize(Tracker *list, void *start)
{
  r_size_t size = 0;
  Tracker *curr = list;
  while(curr != NULL && curr->start != start)
  {
    curr = curr->next;
  }
  if(curr != NULL)
  {
    size = curr->size;
  }
  return size;
}
