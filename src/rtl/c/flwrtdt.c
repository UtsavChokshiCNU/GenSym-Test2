/*
 * flwrtdt.c -  Chestnut Run-Time Library entry for function file_write_date
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object probe_file(Object);
extern bignum_type unsigned_long_to_bignum (SI_Ulong);

#else

extern char *SI_istring();
extern Object probe_file();
extern bignum_type unsigned_long_to_bignum ();

#endif


#include "filesys.h"

/* Before ANSI C, there is no reliable way to specify an unsigned long
 * constant, according to Harbison and Steele. */
#define IUNIX_EPOCH ((unsigned long)2147483647L+(unsigned long)61505153L)


Object file_write_date (file)
    Object file;
{
    Declare_local_temp;
    long result;
    struct stat buf;
    Object truefile;
    SI_Ulong fwd;

    if (truefile = probe_file(file)) {
	/* 0 means success, -1 failure */
	result = stat(ISTRING(truefile), &buf);
	/* The st_ctime field has type time_t.  We cheat and assume this
	   is type is the same as long.  The value is seconds since the
	   "epoch", which is 00:00 GMT, January 1, 1970.  Common Lisp
	   specifies its own universal time format, which is seconds since
	   00:00:00 January 1, 1900 GMT. */

	if (result == 0) {
	  fwd = (SI_Ulong)buf.st_ctime + IUNIX_EPOCH;
	  return VALUES_1(UNSIGNED_LONG_TO_INTEGER(fwd));
	}
    }
    return VALUES_1(NIL);
}
