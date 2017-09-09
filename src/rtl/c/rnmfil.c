/*
 * rnmfil.c -  Chestnut Run-Time Library entry for function rename_file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object merge_pathnames(Object,Object,Object);
extern Object probe_file(Object);
extern Object truename(Object);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object merge_pathnames();
extern Object probe_file();
extern Object truename();

#endif

#include "filesys.h"

Object rename_file (file, new_name)
    Object file, new_name;
{
    Object newpath, truefile, truenewpath;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(file,new_name);
    PROTECTI_3(newpath,truefile,truenewpath);
    file = merge_pathnames(file,KOPT,KOPT);
    truefile = truename(file);
    newpath = merge_pathnames(new_name, file, KOPT);
    truenewpath = truename(newpath);

    if (probe_file(truenewpath))
	error(2, "rename_file: ~s already exists!", truenewpath);
    if (rename(ISTRING(truefile), ISTRING(truenewpath)))
	error(3, "rename_file: unable to rename ~s to ~s", file, new_name);
    RESTORE_STACK();
    return(VALUES_3(newpath, truefile, truenewpath));
}
