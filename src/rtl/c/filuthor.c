/*
 * filuthor.c -  Chestnut Run-Time Library entry for function file_author
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "filesys.h"

Object file_author (file)
    Object file;
{
    Declare_local_temp;
    return VALUES_1(NIL);  /* change this function if author name available */
}
