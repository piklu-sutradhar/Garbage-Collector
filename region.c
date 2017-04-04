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
        if (search(region_name) == false)
        {
            Boolean inserted = insert(region_name, region_size);
            if (inserted == true)
            {
                rc = rchoose(region_name);
            }
        }
        else
        {
            printf("Name \"%s\" is already taken \n", region_name);
            curr = NULL;
            rc = false;
        }
    }

    return rc;
}
Boolean rchoose(const char *region_name)
{
    Boolean rc = false;
    curr = firstNode();
    while (curr != NULL && strcmp(curr->name, region_name) != 0)
    {
        curr = nextNode();
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
    }
    return name;
}
/*
void *ralloc(r_size_t block_size)
{
    S
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
    delete (region_name);
    // return rc;
}
void rdump()
{
    Node *curr = firstNode();
    while (curr != NULL)
    {
        printf("****************************\n");
        printf("The Name of the region: %s\n", curr->name);
        printf("The buffer pointer: %p\n", curr->memoryRegion);
        printf("The size of the buffer: %hu\n", curr->size);
        printf("****************************\n");
        curr = nextNode();
    }
}