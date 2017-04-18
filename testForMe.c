#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"
static int testExecuted = 0;
static int testFailed = 0;

static char *names[5] = {"Computer Science","Physics","Chemistry","Biology","Arts",};
static int sizes[5] = {1024,777,85,560,24};

void testRinit(const char * region_name, r_size_t region_size)
{
  Boolean rc;
    if(rchoose(region_name) == false)
    {
      rc = rinit(region_name, region_size);
      if(region_name != NULL && region_size > 0)
      {
        if(rc != true)
        {
          testFailed++;
          printf("%s : %s\n", "Failed to create region", region_name);
        }
      }
      else
      {
        if(rc == true)
        {
          testFailed++;
          printf("%s : %s\n", "Created an unexpected region", region_name);
        }
      }
    }
    else
    {
      rc = rinit(region_name, region_size);
      if(rc == true)
      {
        testFailed++;
        printf("%s : %s\n", "Created a repeated region", region_name);
      }
    }
    testExecuted++;
}
void testRchoose(const char * region_name, Boolean result)
{
  if(result == true)
  {
    if(strcmp(region_name, rchosen()) != 0)
    {
      testFailed++;
      printf("%s\n","Chosen name is different" );
    }
  }
  testExecuted++;
}

void testRalloc(r_size_t block_size, void * start_block)
{
  r_size_t size = rsize(start_block);
  r_size_t expected = (block_size + 7) - ((block_size + 7)%8);
  if(start_block != NULL)
  {
    if( size != expected)
      {
      testFailed++;
      printf("Failed to allocate a block of proper size \n");
      }
  }
  else
  {
    if( size != 0)
    {
      testFailed++;
      printf("%s\n", "Allocated a block with NULL pointer" );
    }
  }
  testExecuted++;
}

void testRfree(void * block_ptr)
{
  r_size_t size = rsize(block_ptr);
  if(size != 0)
  {
    testFailed++;
    printf("Failed: \n");
  }
  testExecuted++;
}
void testRdestroy(const char *region_name)
{
  //rdestroy(region_name);
    if(rchoose(region_name) == true)
    {
      testFailed++;
      printf("Failed to delete the region named : \" %s \"\n", region_name );
    }
  testExecuted++;
}
int main()
{
  int i;
  Boolean rc;
  void * blocks[5];
  char * ca1, *ca2;

  for(i = 0; i < 5 ; i++)
  {
    testRinit(names[i], sizes[i]);
  }
  testRinit("Not",0);
  testRinit(NULL,400);
  testRinit(names[2],0);

  for(i = 0; i < 5 ; i++)
  {
    rc = rchoose(names[i]);
    testRchoose(names[i], rc);
  }

   rc = rchoose("Not in the list");
   testRchoose("Not in the list",rc);
   testRchoose(NULL, rchoose(NULL));

   rc = rchoose(names[3]);
   testRchoose(names[3],rc);
   for(i = 0; i < 5 ; i++)
   {
     blocks[i] = ralloc(sizeof(int) * 32);
     testRalloc((sizeof(int) * 32),blocks[i]);
   }
   ca1 = ralloc(224);
   testRalloc(224, ca1);
   rfree(blocks[1]);
   testRfree(blocks[1]);
   ca1 = ralloc(224);
   testRalloc(224, ca1);
   rfree(blocks[2]);
   testRfree(blocks[1]);
   ca1 = ralloc(224);
   testRalloc(224, ca1);
   ca2 = ralloc(16);
   testRalloc(224, ca1);
   rfree(blocks[2] + 10);
   testRfree(blocks[1] + 10);
   rc = rchoose(names[2]);
   testRchoose(names[2],rc);
   ca1 = ralloc(sizeof(int) * 22);
   testRalloc(sizeof(int) * 22, ca1);
   ca2 = ralloc( 11);
   testRalloc(11, ca2);

  rdump(); // all regions

  rdestroy(names[2]);
  testRdestroy(names[2]);
  rdestroy(names[3]);
  testRdestroy(names[3]);

  rdump();

  rdestroy("Bad Name");
  testRdestroy("Bad Name");
  rdestroy(NULL);
  testRdestroy(NULL);
  for(i = 0; i < 5 ; i++)
  {
    rdestroy(names[i]);
    testRdestroy(names[i]);
  }

  rdump(); // nothing
  printf("Total test executed : %d\n", testExecuted);
  printf("Test Failed: %d\n", testFailed);
  printf("Test passed: %d\n",testExecuted - testFailed);

  fprintf(stderr,"\nEnd of processing.\n");

  return EXIT_SUCCESS;
}
