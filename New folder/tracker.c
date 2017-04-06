#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "tracker.h"

static Tracker *topTracker = NULL;
static Tracker *traverseTrack = NULL;

Boolean build_block(void *start_of_block, r_size_t block_size)
{
    Boolean built = false;
    Tracker *curr = topTracker;
    Tracker *prev = NULL;
    Tracker *new = (Tracker *) malloc(sizeof(Tracker));
    //printf("Here in buildBlock\n");
    new->start_of_block = start_of_block;
    new->size = block_size;
    //printf("Here in buildBlock\n");
    while (curr != NULL && start_of_block < curr->start_of_block)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL)
    {
        new->next = curr;
        topTracker = new;
        built = true;
    }
    else
    {
       new->next = curr;
       prev->next = new;
       built = true;
    }
    return built;
}
Boolean delete_block(void *start_of_block)
{
    Boolean rc = false;
    Tracker *curr = topTracker;
    Tracker *prev = NULL;
     while (curr != NULL && start_of_block != curr->start_of_block)
    {
        prev = curr;
        curr = curr->next;
    }
    if(prev == NULL)
    {
        topTracker = topTracker->next;
        rc = true;
    }
    else
    {
        if(curr != NULL)
        {
            prev->next = curr->next;
            rc = true;
        }
    }
    return rc;
}
Tracker *firstTrack()
{
    if (topTracker != NULL)
    {
        traverseTrack = topTracker->next;
    }
    return topTracker;
}

// gets the data at the current traversal node and increments the traversal
Tracker *nextTrack()
{


    //char *item = NULL;

    Tracker *current = NULL;
    // no need to go past the end of the list...
    if (traverseTrack != NULL)
    {

        current = traverseTrack;
        //item = traverseNode->string;
        traverseTrack = traverseTrack->next;
    }
//printf("Here in track\n");
    return current;
}
