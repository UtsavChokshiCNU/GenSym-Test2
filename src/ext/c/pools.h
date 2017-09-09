/*******************************************************************************

File name:               pools.h
Owner:                   Peter Fandel

Purpose:                 This include file has defines and typedefs required by 
                         extensions to implement the memory pool mechanism.

This file depends on:    Nothing.

Dependent files:         pools.c

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.

History:                 11nov92  PAF  Created
                          4jan95  PAF  Made pool a static variable to prevent
                                       name collisions.  This was possible 
                                       because this include file is used only
                                       by pools.c

*******************************************************************************/

#define MAX_POOLS   20L /* Max number of pools for chosen allocation scheme. */
#define MID_WAY      8L /* Used to reduce worst case search time.            */

typedef struct bh {
    icp_int    blob_size;
    icp_int    pool_index;
    char      *blob_ptr;
    struct bh *next;
} blob_header_type;

typedef struct {
    icp_int           blob_size;
    blob_header_type *bh_ptr;
} pool_cell;

static pool_cell  pool[MAX_POOLS] = {   0x40L, NULL_PTR,     /*    64 */
                                        0x80L, NULL_PTR,     /*   128 */
                                        0xC0L, NULL_PTR,     /*   192 */
                                       0x100L, NULL_PTR,     /*   256 */
                                       0x180L, NULL_PTR,     /*   384 */
                                       0x200L, NULL_PTR,     /*   512 */
                                       0x300L, NULL_PTR,     /*   768 */
                                       0x400L, NULL_PTR,     /*  1024 */
                                       0x600L, NULL_PTR,     /*  1536 */
                                       0x800L, NULL_PTR,     /*  2048 */
                                       0xC00L, NULL_PTR,     /*  3072 */
                                      0x1000L, NULL_PTR,     /*  4096 */
                                      0x1800L, NULL_PTR,     /*  6144 */
                                      0x2000L, NULL_PTR,     /*  8192 */
                                      0x3000L, NULL_PTR,     /* 12288 */
                                      0x4000L, NULL_PTR,     /* 16384 */
                                      0x6000L, NULL_PTR,     /* 24576 */
                                      0x8000L, NULL_PTR,     /* 32768 */
                                      0xC000L, NULL_PTR,     /* 49152 */
                                     0x10000L, NULL_PTR   }; /* 65536 */

blob_header_type  *blobs_in_use = NULL_PTR;
