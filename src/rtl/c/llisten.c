/*
 * llisten.c -  Chestnut Run-Time Library entry for function llisten
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object chase_input_stream(Object stream);
extern long ilength(Object sequence);

#else

extern char *SI_istring();
extern Object chase_input_stream();
extern long ilength();

#endif


Object llisten (input_stream)
    Object input_stream;
{
    Declare_local_temp;
    Object stream, ostream, eof_p, string;
    FIXNUM start, end;
    long istart, iend;
    FILE *fp;

    MVS_2(chase_input_stream(input_stream), stream, ostream);
    switch (STREAM_STYPE(stream)) {
	case INTERACTION_STREAM:
	    fp = INTERACTION_STREAM_FP(stream);
	    if (feof(fp))
		eof_p = T;
	    else
		eof_p = NIL;
	    break;
	case FILE_STREAM:
	    fp = FILE_STREAM_FP(stream);
	    if (feof(fp))
		eof_p = T;
	    else
		eof_p = NIL;
	    break;
	case STRING_INPUT_STREAM:
	    /* read from string into str[] */
	    string = FIRST(STREAM_OBJ(stream));
	    start = SECOND(STREAM_OBJ(stream));
	    end = THIRD(STREAM_OBJ(stream));
	    iend = end ? IFIX(end) : ilength(string);
	    istart = IFIX(start);
	    if (istart >= iend)
		eof_p = T;
	    else if (ISTRING(string)[istart] == '\0')	/* NULL TERMINATOR ENDS STRING INPUT */
	        eof_p = T;
	    else
		eof_p = NIL;
	    break;
	default:
	    eof_p = T;
	    break;
    }
    return VALUES_1(eof_p);
}
