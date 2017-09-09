/*
 * pthnmhst.c -  Chestnut Run-Time Library entry for function pathname_host
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object T_temp;

#if SI_USE_PROTOTYPES

extern Object pathname(Object);

#else

extern Object pathname();

#endif


#include "filesys.h"

Object pathname_host (pathnm)
    Object pathnm;
{
    return T_VALUES_1(PATHNAME_HOST(pathname(pathnm)));
}
