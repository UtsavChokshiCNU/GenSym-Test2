/*
 * mkpthnm.c -  Chestnut Run-Time Library entry for function make_pathname
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Default_pathname_defaults;
extern Object Kunspecific;

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
extern void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);
extern Object imake_duplicate_string(char *oldstring);
extern Object pathname(Object);
extern Object string(Object);
extern Object truename(Object);

#else

extern char *SI_istring();
extern void _makepath();
extern void _splitpath();
extern Object imake_duplicate_string();
extern Object pathname();
extern Object string();
extern Object truename();

#endif


#include "filesys.h"

#define FIELD_STRING(f) \
  ((TRUEP(f) && (f != Kunspecific)) ? ISTRING(STRING(f)) : "")

Object make_pathname (host, device, directory, name, type, version, defaults)
    Object host, device, directory, name, type, version, defaults;
{
    Object defname, result;
    char *defpath;
    char path[_MAX_PATH];
    char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_7(host, device, directory, name, type, version, defaults);
    PROTECTI_1(defname);
    if (UNSUPPLIED_P(defaults)) 
       defaults = "";  /* Host only pathname */
    else {
       defname = truename(defaults);
       defpath = ISTRING(defname);
    }
    _splitpath(defpath, drive, dir, fname, ext);
    if (SUPPLIEDP(device))
      	strcpy(drive, FIELD_STRING(device));
    if (SUPPLIEDP(directory))
	strcpy(dir, FIELD_STRING(directory));
    if (SUPPLIEDP(name))
	strcpy(fname, FIELD_STRING(name));
    if (SUPPLIEDP(type))
	strcpy(ext, FIELD_STRING(type));
    _makepath(path, drive, dir, fname, ext);
    result = pathname(imake_duplicate_string(path));
    RESTORE_STACK();
    return(result);
}
