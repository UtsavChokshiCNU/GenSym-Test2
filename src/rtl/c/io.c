/*
 * io.c - input/output global variables and initializer
 * io.c - LISPTOC Input/Output functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern Object Qsingle_float;

#include "svargs.h"

/* *** to be removed soon */
extern TLS Object SI_First_value;


DEFINE_VARIABLE(Read_base);
Object Read_eval = UNBOUND;
Object Read_suppress = UNBOUND;
DEFINE_VARIABLE(Read_default_float_format);

void SI_INIT_io()
{

    Read_base = FIX(10L);

    Read_default_float_format = Qsingle_float;

    Read_eval = T;

    Read_suppress = NIL;

}




#if !defined(MSDOS) && !defined(_INTELC32_)  && !defined(WIN32)

#if !defined(__ZTC__)
int kbhit()
{
#if defined(linux) || defined(__APPLE__) || defined(Platform_Solaris)
  return FALSE;
#else
#ifdef VMS
    return(((*stdin)->_cnt > 0) ? TRUE : FALSE);
#else
    return((stdin->_cnt > 0) ? TRUE : FALSE);
#endif
#endif
}

int getch()
{
    return(getchar());
}
#endif /* ZTC */


int _splitpath(path,drive,dir,fname,ext)
    char *path, *drive, *dir, *fname, *ext;
{
    register int i;
    int len = strlen(path);

    drive[0] = dir[0] = fname[0] = ext[0] = '\0';
    for (i = len-1; i >= 0; i--) {
	if (path[i] == '/') {
	    /* found end of path */
	    splitfile(&path[i+1], fname, ext);
	    strncpy(dir, path, i);
	    dir[i] = '\0';
	    break;
	}
    }
    if (i < 0)
	splitfile(path, fname, ext);
}

int splitfile(fullname, fname, ext)
    char *fullname, *fname, *ext;
{
    register int i;
    int len;

    fname[0] = ext[0] = '\0';
    len = strlen(fullname);
    for (i = len-1; i >= 0; i--) {
	if (fullname[i] == '.') {
	    strcpy(ext, &fullname[i+1]);
	    strncpy(fname, fullname, i);
	    fname[i] = '\0';
	    break;
	}
    }
    if (i < 0)
	strcpy(fname, fullname);
}	

#if defined(__ZTC__)
#define SI_MAKEPATH_SEP  '\\'
#else /* !ZTC */
#define SI_MAKEPATH_SEP  '/'
#endif /* ZTC */

int _makepath(path, drive, dir, fname, ext)
    char *path, *drive, *dir, *fname, *ext;
{
    char sep = SI_MAKEPATH_SEP;
    if (ext && *ext != '\0') {
	if (*ext == '.') ext++;
	sprintf(path, "%s%c%s.%s", dir, sep, fname, ext);
    }
    else 
	sprintf(path, "%s%c%s", dir, sep, fname);
}

#endif

