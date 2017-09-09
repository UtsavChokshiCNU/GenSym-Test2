/*
 * dcnmsng.c -  Chestnut Run-Time Library entry for function directory_namestring
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object pathname_directory(Object);

#else

extern Object pathname_directory();

#endif


#include "filesys.h"

Object directory_namestring (pathnm)
    Object pathnm;
{
    return(pathname_directory(pathnm));
}
