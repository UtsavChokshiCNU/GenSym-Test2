/*
 * flnmsrng.c -  Chestnut Run-Time Library entry for function file_namestring
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext); //firt parameter is const char
extern Object istring_to_string(char *istring);
extern Object truename(Object);

#else

extern char *SI_istring();
extern void _splitpath();
extern Object istring_to_string();
extern Object truename();

#endif


#include "filesys.h"

Object file_namestring (pathnm)
    Object pathnm;
{
    Object name;
    char *namepath;
    char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME+_MAX_EXT];
    char ext[_MAX_EXT];

    name = truename(pathnm);
    namepath = name ? ISTRING(name) : "";
    _splitpath(namepath, drive, dir, fname, ext);
    strcat(fname, ext);
    return(istring_to_string(fname));
}
