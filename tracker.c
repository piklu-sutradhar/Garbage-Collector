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
r_size_t allocatedSpace(Tracker **head)
{
        Tracker *curr = *head;

        r_size_t totalSize = 0;

        while ( curr != NULL )
        {
                totalSize += curr->size;
                curr = curr->next;
        }
        return totalSize;
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
