/*
 * pthnmnm.c -  Chestnut Run-Time Library entry for function pathname_name
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern void _splitpath(char *path, char *drive, char *dir, char *fname, char *ext);
extern Object istring_to_string(char *istring);
extern Object truename(Object);

#else

extern char *SI_istring();
extern void _splitpath();
extern Object istring_to_string();
extern Object truename();

#endif


#include "filesys.h"

Object pathname_name (pathnm)
    Object pathnm;
{
    Object name;
    char *namepath;
    char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

    name = truename(pathnm);
    namepath = name ? ISTRING(name) : "";
    _splitpath(namepath, drive, dir, fname, ext);
    return(istring_to_string(fname));
}
