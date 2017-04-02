#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "regions.h"
#include "linkedlist.h"

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
    if (region > 0)
    {
        region_size += 7;
        region_size = region_size - (region_size % 8);

        if (search(region_name) == false)
        {
            insert(region_name, region_size);
            curr = firstNode();
            rc = true;
        }
    }
    return rc;
}
Boolean rchoose(const char *region_name)
{
}
const char *rchosen()
{
}
void *ralloc(r_size_t block_size)
{
}
r_size_t rsize(void *block_ptr)
{
}
Boolean rfree(void *block_ptr)
{
}
void rdestroy(const char *region_name)
{
}
void rdump()
{
}