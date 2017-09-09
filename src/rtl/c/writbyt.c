/*
 * writbyt.c -  Chestnut Run-Time Library entry for function write_byte
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object chase_write_stream(Object stream);
extern SI_Long integer_to_long(Object n);
extern Object vector_push_extend(Object,Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern Object chase_write_stream();
extern SI_Long integer_to_long();
extern Object vector_push_extend();

#endif


/* &optional 1 1 */
Object write_byte(integer, output_stream)
    Object integer;
    Object output_stream;
{
    Declare_local_temp;
    SI_Long n = IINTEGER(integer);
    output_stream = chase_write_stream(output_stream);

    if (STREAMP(output_stream)) {
	switch(STREAM_STYPE(output_stream)) {
	    case INTERACTION_STREAM:
	        fputc((int) n, INTERACTION_STREAM_FP(output_stream));
		break;
	    case FILE_STREAM:
	        fputc((int) n, FILE_STREAM_FP(output_stream));
		break;
	    case STRING_OUTPUT_STREAM:
		vector_push_extend(CHR((int) n), STREAM_OBJ(output_stream),
				   KOPT);
		break;
	    default:
		error(2, "write_byte:  invalid stream=~s", output_stream);
	}
    }
    return VALUES_1(integer);
}
