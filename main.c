#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"
static int testExecuted = 0;
static int testFailed = 0;
/*
void buildRegion(char * region_name, r_size_t region_size)
{
  Boolean rc;
  if(strlen(region_name) > 0 && region_size > 0)
  {

    rc = rinit(region_name, region_size);
    assert(rc);
    if(rc != true)
    {

      testFailed++;
      printf("Failed to creat rgion with name = %s and size = %hu\n",region_name,region_size );
    }
  }
  else
  {
    rc = rinit(region_name, region_size);
    assert(!rc);
    if(rc == true)
      {
          printf("here\n");
        testFailed++;
        printf("It created rgion with name = %s and size = %hu\n",region_name,region_size );
      }
    }
    testExecuted++;
}
void checkRchoose(char * region_name)
{
  const char * activeRegion = NULL;
  rchoose(region_name);
  activeRegion = rchosen();
  if(strcmp(activeRegion,region_name) != 0)
  {
    testFailed++;
    printf("Chosen region is different then \"%s\"\n",region_name);
  }
  testExecuted++;
}
void * checkRalloc(r_size_t block_size)
{
  void * ra = ralloc(block_size);
  r_size_t size = rsize(ra);
  if(ra!= NULL && size != block_size)
  {
    testFailed++;
    printf("It falied to allocate exact memory\n");
  }
  else if(ra == NULL && size !=0)
  {
    testFailed++;
    printf("It falied to allocate exact memory\n");
  }
  testExecuted++;
  return ra;
}
void checkRfree(void * block_ptr)
{
  rfree(block_ptr);
  r_size_t size = rsize(block_ptr);
  if(size != 0)
  {
    testFailed++;
    printf("It falied to free memory\n");
  }
  testExecuted++;
}*/

// this code should run to completion with the output shown
// you must think of additional cases of correct use and misuse for your testing
int main()
{
  Boolean rc;
  int *ia;
  char *ca1, *ca2, *ca3, *ca4;
  char *fail;

  //buildRegion("hello", 1024);

  //buildRegion("world", 0);
  printf("here\n");
  //buildRegion("world", 796);
  //printf("here");
  //checkRchoose("hello");
  //checkRchoose("world");
  /*ca1 = checkRalloc(sizeof(int) * 32);
  ca2 = checkRalloc(256);
  ca3 = checkRalloc(384);
  ca4 = checkRalloc(384);
  checkRfree(ca1);
  ca1 = checkRalloc(384);
  checkRfree(ca2);
  ca1 = checkRalloc(384);
  checkRchoose("world");
  ca2 = checkRalloc(797);

  */
  rc = rinit("world", 0);
  rc = rinit("hello", 1024);
  assert(rc);
  rc = rinit("world", 0); // 800
  //printf("Chosen: %d\n", rc);
  assert(!rc);

  printf("Chosen: %s\n", rchosen()); // world

  rc = rchoose("hello");
  assert(rc);
  printf("Chosen: %s\n", rchosen());
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
  assert(!rc);
  ca4 = ralloc(796);
  assert(NULL == ca4);
  printf("Size: %d\n", rsize(ca4)); // 800
  rc = rinit("world", 450); // 800
  //printf("Chosen: %d\n", rc);
  assert(rc);

  rdump(); // hello & world

  rdestroy("hello");
  //rdestroy("hello");

  rc = rfree(ca4 + 24); // not the start of the block
  assert(!rc);
  rc = rfree(ca4); // better!
  assert(!rc);

  rdestroy("world");

  rdump(); // nothing

  fprintf(stderr,"\nEnd of processing.\n");

  return EXIT_SUCCESS;
}
