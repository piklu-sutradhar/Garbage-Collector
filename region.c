#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "regions.h"
//#include "linkedlist.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
static Node *curr = NULL;
//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
Boolean rinit(const char *region_name, r_size_t region_size)
{
    Boolean rc = false;
    if (region_size > 0)
    {
        region_size += 7;
        region_size = region_size - (region_size % 8);
        //printf("%s\n", region_name);

       // Boolean found = search(region_name);
        if (search(region_name) == false)
        {
           // printf("%d\n", found);
            Boolean inserted = insert(region_name, region_size);
            if (inserted == true)
            {
               // printf("%d\n", inserted);
                //rc = true;
                rc = rchoose(region_name);
            }
        }
    }

    return rc;
}
Boolean rchoose(const char *region_name)
{
    Boolean rc = false;
    curr = firstNode();
    /*if(curr != NULL){
        printf("%s\n",curr->name);
    }*/
    while (curr != NULL && strcmp(curr->name, region_name) != 0)
    {
        curr = nextNode();
        //printf("%s\n",curr->name);
    }
    if (curr != NULL)
    {
        rc = true;
    }
    return rc;
}
const char *rchosen()
{
    char *name = NULL;
    if (curr != NULL)
    {
        name = curr->name;
        //strcpy(curr->name, name);
    }
    return name;
}
/*
void *ralloc(r_size_t block_size)
{
}
r_size_t rsize(void *block_ptr)
{
}
Boolean rfree(void *block_ptr)
{
}*/
void rdestroy(const char *region_name)
{
    //Boolean rc = false;
    delete(region_name);
   // return rc;
}
/*
void rdump()
{
}

int main(void)
{
    Boolean rc;
    // int *ia;
    //char *ca1, *ca2, *ca3, *ca4;
    //char *fail;
    printf("here I am\n");
    rc = rinit("hello", 1024);
    assert(rc);

    rc = rinit("world", 798); // 800
    assert(rc);
    printf("Chosen: %s\n", rchosen());
    rc = rchoose("hello");
    assert(rc);
    printf("Chosen: %s\n", rchosen()); // world

    return 0;
}*/