#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"
static int testExecuted = 0;
static int testFailed = 0;

void testRinit( Boolean result , Boolean expected)
{
  int i = 0;
  char *names[10] = {"Computer Science","Physics","Hello","world",
  NULL,"Chemistry","Biology","Arts","New region","Another region"};
  int sizes[10] = {1024,777,0,-85,560,600,160, 200,24,10};

  for (i =0; i < 10; i++)
  {
    Boolean rc = rinit(names[i], sizes[i]);
    if(names != NULL && sizes > 0 )
    {
      if(rc != true)
      {
        testFailed++;
        printf("%s\n", "Failed to create region");
      }
    }
    else
    {
      if(rc == true)
      {
        testFailed++;
        printf("%s\n", "Created an unexpected region");
      }
    }
  }
  testExecuted++;
}
void testRchoose(Boolean result, Boolean expected)
{
  //Boolean rc = rchoose(region_name);
  //activeRegion = rchosen();
  if(result == expected)
  {
    printf("Success: \n");
  }
  else
  {
    testFailed++;
    printf("Failed: \n");
  }
  testExecuted++;
}
void testRchosen(const char *expected)
{
  const char * result = rchosen();
  if(strcmp(result, expected) == 0)
  {
    printf("Success: \n");
  }
  else
  {
    testFailed++;
    printf("Failed: \n");
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
  if(rchoose(region_name) == false)
  {
    testFailed++;
    printf("Failed to delete the region named : \" %s \"\n", region_name );
  }
  testExecuted++;
}
// this code should run to completion with the output shown
// you must think of additional cases of correct use and misuse for your testing
int main()
{
  Boolean rc;
  int *ia;
  char *ca1, *ca2, *ca3, *ca4;
  //char *fail;
  /*
  rc = rinit("Computer Science",1024);
  testRinit(rc, true); // rinit should return true
  rc = rinit("Physics", 0);
  testRinit(rc, false); // rinit should return false as size is 0
  rc = rinit("Computer Science", 600);
  testRinit(rc, false); // rinit should return false as "Computer Science" is already taken
  rc = rinit("Physics", 796);
  testRinit(rc, true);// rinit should return true
  rc = rchoose("Physics");
  testRchoose(rc, true); // rchoose should return true as there is a region named "Physics".
  testRchosen("Physics"); //rchosen should return "Physics" as it is currently chosen.
  rc = rchoose("PHYSICS");
  testRchoose(rc, false); // rchoose should return false as there is no region named "PHYSICS"(case sensetive).
  rc = rinit("", 800);
  testRinit(rc, true);// rinit should return false as the name is a empty string.
*/
  rc = rchoose("Computer Science");
  testRchoose(rc, true); // rchoose should return true as there is a region named "Computer Science".
  testRchosen("Computer Science");//rchosen should return "Computer Science" as it is currently chosen.
  rc = rchoose("hello");
  testRchoose(rc, false); // there is no region named "hello"
  ca1 = ralloc(sizeof(int) * 32); //passed
  testRalloc(128, ca1);
  ca2 = ralloc(256); //passed
  testRalloc(256, ca2);
  ca3 = ralloc(384); // passed
  testRalloc(384, ca3);
  ia = ralloc(384); //failed
  testRalloc(0,ia);
  rc = rfree(ca1);
  testRfree(ca1);
  ca1 = ralloc(384); // failed no enough contiguous memory
  testRalloc(0, ca1);
  rc = rfree(ca2);
  testRfree(ca2);
  ca1 = ralloc(384); // passed
  testRalloc(384, ca1);
  rc = rchoose("Physics");
  testRchoose(rc, true);
  ca2 = ralloc(797); // passed
  testRalloc(800,ca2);
  ca1 = ralloc(10);
  testRalloc(0,ca1);

  rdump(); // Coputer Science & Physics

  rdestroy("Physics");
  testRdestroy("Physics"); // should destroy

  rc = rfree(ca4 + 24); // not the start of the block
  assert(!rc);
  testRfree(ca4 + 24);
  printf("Chosen: %s\n", rchosen());
  rc = rfree(ca4); // better! but ca4 is null
  assert(!rc);
  testRfree(ca4);

  rdestroy("Computer Science");

  rdump(); // nothing
  printf("Total test executed : %d\n", testExecuted);
  printf("Test Failed: %d\n", testFailed);
  printf("Test passed: %d\n",testExecuted - testFailed);

  fprintf(stderr,"\nEnd of processing.\n");

  return EXIT_SUCCESS;
}
