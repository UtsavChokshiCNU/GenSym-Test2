/*
 * probfil.c -  Chestnut Run-Time Library entry for function probe_file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object merge_pathnames(Object,Object,Object);
extern Object truename(Object);

#else

extern char *SI_istring();
extern Object merge_pathnames();
extern Object truename();

#endif


#include "filesys.h"

#ifdef WIN32
extern int _access(const char *path, int mode);
#endif


Object probe_file (file)
    Object file;
{
    Declare_local_temp;
    Object truefile;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(file);
    PROTECTI_1(truefile);
    truefile = truename(merge_pathnames(file,KOPT,KOPT));
    RESTORE_STACK();

#if defined(WIN32)
    return VALUES_1(_access(ISTRING(truefile), 0) ? NIL : truefile);
#else
    return VALUES_1(access(ISTRING(truefile), 0) ? NIL : truefile);
#endif
}



