
#ifndef _TRACKER_H
#define _TRACKER_H

typedef enum { false, true } Boolean;

typedef unsigned short r_size_t;

typedef struct TRACKER Tracker;
struct TRACKER
{
    void *start;
    r_size_t size;
    Tracker *next;
};

void add( Tracker **blocks,void *start, r_size_t block_size);
Boolean delete_block( Tracker **list, void *start);
r_size_t blockSize(Tracker *list, void *start);
r_size_t allocatedSpace(Tracker **head);
#endif
