typedef enum { false,
               true } Boolean;

typedef unsigned short r_size_t;
typedef struct TRACKER Tracker;
struct TRACKER
{
    void *start_of_block;
    //void *end_of_block;
    r_size_t size;
    Tracker *next;
};
Tracker *build_block(void *start_of_block, r_size_t block_size);
Boolean delete_block(void *start_of_block);
Tracker *firstTrack();
Tracker *nextTrack();