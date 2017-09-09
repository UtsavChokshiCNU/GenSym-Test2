/*
 * load.c -  Chestnut Run-Time Library entry for function load
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object load_run(Object filename, Object verbose, Object printarg, Object if_does_not_exist);

#else

extern Object load_run();

#endif


#include "filesys.h"

Object load (filename, verbose, printarg, if_does_not_exist)
    Object filename, verbose, printarg, if_does_not_exist;
{
    return(load_run(filename, verbose, printarg, if_does_not_exist));
}


