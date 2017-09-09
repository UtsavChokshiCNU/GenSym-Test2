/*
 * engnmsng.c -  Chestnut Run-Time Library entry for function enough_namestring
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Default_pathname_defaults;

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
extern void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
extern Object imake_duplicate_string(char *oldstring);
extern Object pathname(Object);
extern Object truename(Object);

#else

extern char *SI_istring();
extern void _makepath();
extern void _splitpath();
extern Object imake_duplicate_string();
extern Object pathname();
extern Object truename();

#endif


#include "filesys.h"

/* &optional 1 1  */
Object enough_namestring (pathnm, defaults)
    Object pathnm, defaults;
{
    Object name, defname, result;
    char *namepath, *defpath;
    char path[_MAX_PATH];
    char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
    char ddrive[_MAX_DRIVE], ddir[_MAX_DIR], dfname[_MAX_FNAME],dext[_MAX_EXT];
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(pathnm,defaults);
    PROTECTI_2(name,defname);
    if (UNSUPPLIED_P(defaults)) defaults = Default_pathname_defaults;
    name = truename(pathnm);
    namepath = name != NIL ? ISTRING(name) : "";
    defname = truename(defaults);
    defpath = defname != NIL ? ISTRING(defname) : "";

    _splitpath(namepath, drive, dir, fname, ext);
    _splitpath(defpath, ddrive, ddir, dfname, dext);
    if (!_stricmp(drive, ddrive))
	drive[0] = '\0';
    if (!_stricmp(dir, ddir))
	dir[0] = '\0';
    if (!_stricmp(fname, dfname))
	fname[0] = '\0';
    if (!_stricmp(ext, dext))
	ext[0] = '\0';
    _makepath(path, drive, dir, fname, ext);
    result = pathname(imake_duplicate_string(path));
    RESTORE_STACK();
    return(result);
}
