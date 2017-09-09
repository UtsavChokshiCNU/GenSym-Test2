/*
 * flpstn.c -  Chestnut Run-Time Library entry for function file_position
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kstart;
extern TLS SI_Long L_temp;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object clong_to_bignum(SI_Long a);
extern SI_Long integer_to_long(Object n);

#else

extern Object (*SI_error_fptr) ();
extern Object clong_to_bignum();
extern SI_Long integer_to_long();

#endif


#include "filesys.h"

/* &optional 1 1  */
Object file_position (file_stream, position)
    Object file_stream, position;
{
    Declare_local_temp;
    long err;
    FILE *fp;

    if (!FILEP(file_stream))
	error(2, "file_position: not a file-stream - ~s", file_stream);
    fp = FILE_STREAM_FP(file_stream);
    if (SUPPLIED_P(position) && position != NIL) {
	if (EQ(position, Kstart))
	    err = fseek(fp, 0L, SEEK_SET);  /* fseek returns 0 if successful */
	else if (EQ(position, Kend))
	    err = fseek(fp, 0L, SEEK_END);
	else if (INTEGERP(position))
	    err = fseek(fp, integer_to_long(position), SEEK_SET);
	else
	    err = TRUE;
	return VALUES_1(err ? NIL : T);
    }
    else {
	return (T_MAKE_INTEGER(ftell(fp)));
    }
}
