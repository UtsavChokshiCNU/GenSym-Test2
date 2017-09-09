/*
 * fillngth.c -  Chestnut Run-Time Library entry for function filelength
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object clong_to_bignum(SI_Long a);

#else

extern Object (*SI_error_fptr) ();
extern Object clong_to_bignum();

#endif


#include "filesys.h"

    
 /* 10/6/93, mpc:  Windows NT provides this call, but only with the
  *       preceding '_' on the function name. To further complicate
  *       matters, the NT compilers also define (_MSC_VER), which
  *       causes the linker to search for a nonexistant function
  *       so we add the extra layer of ifdefs.
  */
#if defined(WIN32)
        extern long _filelength(/* int fd */);
#      define filelength(a)  _filelength(a)
#else    
#if defined(_MSC_VER) || defined(_INTELC32_) || defined(__ZTC__)
  extern long filelength(/* int fd */);
#else
static long filelength (fd)
    long fd;
{
    struct stat stbuf;

    fstat(fd, &stbuf);
    return((long) stbuf.st_size);
}
#endif
#endif 

#ifndef _MSC_VER
#define _fileno fileno
#endif

Object file_length (file_stream)
    Object file_stream;
{
    long length;
    if (!FILEP(file_stream) || STREAM_CLOSED_P(file_stream))
	error(2, "file_length: not an open file-stream - ~s", file_stream);
    length = filelength(_fileno(FILE_STREAM_FP(file_stream))); //fileno is old function
    return (MAKE_INTEGER(length));
}

