/*
 * nmstring.c -  Chestnut Run-Time Library entry for function namestring
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object truename(Object);

#else

extern Object truename();

#endif


#include "filesys.h"

Object namestring (pathnm)
    Object pathnm;
{
    return(truename(pathnm));
}
