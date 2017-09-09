/*
 * dltfil.c -  Chestnut Run-Time Library entry for function delete_file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object lclose(Object stream, Object abort);
extern Object merge_pathnames(Object,Object,Object);
extern Object string(Object);
extern Object truename(Object);

#else

extern char *SI_istring();
extern Object lclose();
extern Object merge_pathnames();
extern Object string();
extern Object truename();

#endif


#include "filesys.h"

/* How does one delete a file on VMS? */
#ifdef VMS
#define _unlink delete
#endif

#ifndef _unlink
#define _unlink unlink
#endif

Object delete_file (file)
    Object file;
{
    Declare_local_temp;
    Object truefile;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(file);
    PROTECTI_1(truefile);
    if (STREAMP(file) && !STREAM_CLOSED_P(file))
	lclose(file,_);
    truefile = truename(merge_pathnames(file,KOPT,KOPT));
    _unlink(ISTRING(STRING(truefile)));
    RESTORE_STACK();
    return VALUES_1(truefile);
}
