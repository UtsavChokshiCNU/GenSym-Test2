/*
 * filesys.c - file manipulation global variables and initialization functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext); //2, 3, 4, 5 parameters is const char
extern Object imake_duplicate_string(char *oldstring);

#else

extern void SI_add_external_root();
extern Object SI_alloc();
extern void _makepath();
extern Object imake_duplicate_string();

#endif


#include "filesys.h"

#ifdef WIN32
extern char *_getcwd(char *buffer, int maxlen);
#endif


#if defined(_MSC_VER) || defined(_INTELC32_) || defined(__ZTC__)
char Default_ext[] = ".LSP";
#else
static long filelength();
char Default_ext[] = ".lisp";
#endif

Object Default_pathname_defaults = UNBOUND;

DEFINE_VARIABLE(Load_pathname);
DEFINE_VARIABLE(Load_print);
DEFINE_VARIABLE(Load_truename);
DEFINE_VARIABLE(Load_verbose);

Object Compile_file_pathname = UNBOUND;
Object Compile_print = UNBOUND;
Object Compile_file_truename = UNBOUND;
Object Compile_verbose = UNBOUND;


void SI_INIT_filesys()
{   Declare_protect(1);
    char dir[_MAX_DIR];
    char string[_MAX_PATH];
    Object defaults;

    PROTECT_LOCALS();
    PROTECTI_1(defaults);

#ifdef WIN32
    _getcwd(dir, _MAX_DIR);
#else
    getcwd(dir, _MAX_DIR);
#endif

#if defined(_MSC_VER) || defined(_INTELC32_) || defined(__ZTC__)
    _makepath(string, NULL, dir, "FOO", Default_ext);
#else
    _makepath(string, NULL, dir, "foo", Default_ext);
#endif

    defaults = imake_duplicate_string(string);
    PROTECT_GLOBAL(Default_pathname_defaults);
    Default_pathname_defaults =
	SI_ALLOC(SI_Pathname, PATHNAME_TYPE, SI_INSTANCE_TAG, SI_NORMAL);
    SI_SET_WRAPPER(Default_pathname_defaults, SI_WRAPPER_pathname);
    PATHNAME_PATH(Default_pathname_defaults) = defaults;
    PATHNAME_HOST(Default_pathname_defaults) = NIL;

#define INIT_VAR(var, sym) \
    PROTECT_GLOBAL(var); \
    var = NIL

    INIT_VAR(Load_pathname, Qload_pathname);
    INIT_VAR(Load_print, Qload_print);
    INIT_VAR(Load_truename, Qload_truename);
    INIT_VAR(Load_verbose, Qload_verbose);

    INIT_VAR(Compile_file_pathname, Qcompile_file_pathname);
    INIT_VAR(Compile_print, Qcompile_print);
    INIT_VAR(Compile_file_truename, Qcompile_file_truename);
    INIT_VAR(Compile_verbose, Qcompile_verbose);

#undef INIT_VAR
    UNPROTECT_LOCALS();
}

