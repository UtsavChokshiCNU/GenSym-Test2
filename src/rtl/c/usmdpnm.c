/*
 * usmdpnm.c -  Chestnut Run-Time Library entry for function user_homedir_pathname
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "filesys.h"

Object user_homedir_pathname (host)
    Object host;
{
    Declare_local_temp;
    return VALUES_1(NIL);
}
