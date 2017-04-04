#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "regions.h"

// this code should run to completion with the output shown
// you must think of additional cases of correct use and misuse for your testing
int main(void)
{
    Boolean rc;
     int *ia;
    //char *ca1; *ca2, *ca3, *ca4;
    //char *fail;
    //printf("here I am");
    rc = rinit("hello", 1024);
    assert(rc);

    rc = rinit("world", 798); // 800
    assert(rc);

    // world

    rc = rinit("This", 566); // 800
    assert(rc);

    rc = rinit("new", 958); // 800
    assert(rc);

    printf("Chosen: %s\n", rchosen()); //new

    rc = rchoose("world");

    printf("Chosen: %s\n", rchosen()); // world

    rdestroy("This");
    rc = rchoose("This");

    printf("Chosen: %s\n", rchosen());

    rc = rinit("This", 1000);
    printf("Chosen: %s\n", rchosen()); // This

    rc = rchoose("hello");
    printf("Chosen: %s\n", rchosen()); //hello

    rc = rinit("world", 1056);
     printf("Chosen: %s\n", rchosen()); //null
     rc = rchoose("This");

    printf("Chosen: %s\n", rchosen()); 

    ia = ralloc(sizeof(int) * 32);
    printf("Chosen: %p\n", ia);

    ia = ralloc(sizeof(int) * 32);
    printf("Chosen: %p\n", ia);

    rc = rchoose("hello");

    printf("Chosen: %s\n", rchosen()); 

    ia = ralloc(sizeof(int) * 32);
    printf("Chosen: %p\n", ia);

    ia = ralloc(sizeof(int) * 32);
    printf("Chosen: %p\n", ia);

    ia = ralloc(sizeof(int) * 32);
    printf("Chosen: %p\n", ia);

    ia = ralloc(sizeof(int) * 32);
    printf("Chosen: %p\n", ia);

    //rdump();
    /*
  rc = rchoose("hello");
  assert(rc);
  ia = ralloc(sizeof(int) * 32);
  printf("Size: %d\n", rsize(ia)); // 128
  ca1 = ralloc(256);
  assert(NULL != ca1);
  ca2 = ralloc(384);
  assert(NULL != ca2);
  fail = ralloc(384); // not enough memory
  assert(NULL == fail);
  rc = rfree(ca1);
  assert(rc);
  fail = ralloc(384); // not enough contiguous memory
  assert(NULL == fail);
  rc = rfree(ia);
  assert(rc);
  ca3 = ralloc(384); // now there's enough memory
  assert (NULL != ca3);
  
  rc = rchoose("world");
  assert(rc);
  ca4 = ralloc(796);
  assert(NULL != ca4);
  printf("Size: %d\n", rsize(ca4)); // 800
  
  rdump(); // hello & world
  
  rdestroy("hello");
  
  rc = rfree(ca4 + 24); // not the start of the block
  assert(!rc);
  rc = rfree(ca4); // better!
  assert(rc);
  
  rdestroy("world");

  rdump(); // nothing

  fprintf(stderr,"\nEnd of processing.\n");*/

    return EXIT_SUCCESS;
}