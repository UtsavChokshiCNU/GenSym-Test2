/*******************************************************************************

File name:               pools.c
Owner:                   Peter Fandel

Purpose:                 This file contains functions which implement the
                         "managed array" feature used for array and longstring
                         passing in ICP extensions.

Contents:                One function to allocate a managed array (blob), and
                         a function to reclaim all blobs currently in use.

This file depends on:    icp_pvt.h, icp.h, pools.h

Dependent files:         icp.c, gsi.c, rpc.c more?

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 See individual function headers.

Header files:            The following are include files required by this file.
                         The constant EXTERN_DEFINED is set to TRUE so as to
                         prevent some externs from being defined twice.       */

#define                  EXTERNS_DEFINED TRUE  /* Turn off part of icp.h.     */
#include                "gensym-features.h"  /* Machine dependent stuff.    */
#include                "cprim.h"
#include                "icp.h"              /* Stuff required by all ICP
                                                  extension code.             */
#include                "icp_pvt.h"          /* Stuff required by all ICP
                                                  extensions internal code.   */
#include                "pools.h"            /* Stuff required for managed
                                                  array pools.

Functions by category:   All categories
                         --------------                                      */
                icp_int  allocate_blob();
                icp_int  reclaim_used_blobs();

extern void ext_error(icp_int error, char *circumstance, icp_int data, icp_int send);


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION allocate_blob:                Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will find or create a "blob" of memory that meets or exceeds
:  the requirements specified by the array_size argument.  Most of the time,
:  an existing blob will be found in the memory pool.  If none are available
:  in the correct size category, a new one is created.
:
:  Once a blob is found (or created), it is inserted into a linked list of the
:  blobs currently in use, and the ptr_ptr argument is set such that its
:  contents reference the blob.
:
:  A blob always has an associated blob header which points to the blob, records
:  the blob's size and the pool index that corresponds to the size category, and 
:  points to the next blob header (either in the pool or in the blobs_in_use
:  list).
:
:  Arguments:        array_size  Size of memory space required.
:                    ptr_ptr     Address of pointer which shall reference the 
:                                blob once it is found or created.
:  Return Behavior:  ICP_FAILURE if we run out of memory.  Otherwise ICP_SUCCESS.
:  Users:            ??
:  Memory Impact:    Direct -- malloc may be called twice or not at all.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int allocate_blob(array_size,ptr_ptr)
    icp_int   array_size;
    char    **ptr_ptr;
{
    icp_int            i;
    blob_header_type  *bh_ptr;

#ifdef DEBUG
    strcpy(where_in_extension,"allocate_blob");
    printf("          %s\n",where_in_extension);
#endif

/*  Determine pool index based on array size and available blob sizes.
    Check against mid sized blob first to reduce worst case search time.
    ---------------------------------------------------------------------*/
    if (array_size > pool[MID_WAY].blob_size)
        for (i=MID_WAY+1; (i<MAX_POOLS) && (array_size>pool[i].blob_size); i++);
    else
        for (i=0; (i<MID_WAY) && (array_size>pool[i].blob_size); i++);

    if (i >= MAX_POOLS) {
      return ICP_FAILURE;
    }
/*  If available, take the first "blob and blob header" combination
    from the linked list hanging off of this pool location.  Otherwise,
    create and initialize a new "blob header and blob" combination.
    -----------------------------------------------------------------*/
    if (pool[i].bh_ptr != NULL_PTR) {
        bh_ptr = pool[i].bh_ptr;
        pool[i].bh_ptr = bh_ptr->next; }
    else {
        bh_ptr = (blob_header_type *) malloc(sizeof(blob_header_type));
        if (bh_ptr == NULL) {
            ext_error(NO_MORE_MEMORY,"allocate_blob(header)",NO_DATA,NO_SEND);
            return(ICP_FAILURE); }
        bh_ptr->blob_size = pool[i].blob_size;
        bh_ptr->pool_index = i;
        bh_ptr->blob_ptr = malloc(bh_ptr->blob_size);
        if (bh_ptr->blob_ptr == NULL_PTR) {
	    free(bh_ptr);
            ext_error(NO_MORE_MEMORY,"allocate_blob(blob)",NO_DATA,NO_SEND);
            return(ICP_FAILURE); }
    } /* end else */

/*  We now have a blob header with a connected blob that meets
    our needs.  Link the blob header at the head of the linked
    list of blobs in use, and set the contents of the pointer
    pointer argument to reference the blob just allocated.
    ---------------------------------------------------------*/
    bh_ptr->next = blobs_in_use;
    blobs_in_use = bh_ptr;
    *ptr_ptr = bh_ptr->blob_ptr;

    return(ICP_SUCCESS);

} /* end allocate_blob */


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:
:  FUNCTION reclaim_used_blobs:           Copyright (C) 1986-2017 Gensym Corporation
:
:  This function will move all the blob header and blob combinations from the
:  blobs in use list to the pool where they may be allocated anew.
:
:  Note, the blob associated with each blob header will always follow and need
:  not be bothered with directly.
:
:  Arguments:        None.
:  Return Behavior:  ICP_SUCCESS is always returned.
:  Users:            ??
:  Memory Impact:    None.
:
:  Rev  Date     Author     Notes
:  xxx  xxxxxxxx xxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxx
:.............................................................................*/
icp_int reclaim_used_blobs()
{
    blob_header_type  *bh_ptr;
    
#ifdef DEBUG
    strcpy(where_in_extension,"reclaim_used_blobs");
    printf("          %s\n",where_in_extension);
#endif

/*  Iterate through the blobs_in_use linked list.  Each iteration
    removes a blob header from the head of the list, determines
    in which of the pool's linked lists the blob header belongs,
    and inserts it at the head of that linked list.
    ---------------------------------------------------------------*/
    while (blobs_in_use != NULL_PTR) {
        bh_ptr = blobs_in_use;
        blobs_in_use = bh_ptr->next;
        bh_ptr->next = pool[bh_ptr->pool_index].bh_ptr;
        pool[bh_ptr->pool_index].bh_ptr = bh_ptr; }

    return(ICP_SUCCESS);

} /* end reclaim_used_blobs */
