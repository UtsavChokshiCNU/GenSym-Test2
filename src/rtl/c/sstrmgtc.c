/*
 * sstrmgtc.c -  Chestnut Run-Time Library entry for function SI_stream_getc
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

int SI_stream_getc(input_stream)
    Object input_stream;
{
    Declare_local_temp;
    int c;
    Object ostream;
    Object string;
    FIXNUM start, end;
    long istart, iend;
    char *istring;

    MVS_2(chase_input_stream(input_stream), input_stream, ostream);
    if (FILEP(input_stream)) {
	c = fgetc(FILE_STREAM_FP(input_stream));
    }
    else if (STRING_INPUT_STREAMP(input_stream)) {
	string = FIRST(STREAM_OBJ(input_stream));
	start = SECOND(STREAM_OBJ(input_stream));
	end = THIRD(STREAM_OBJ(input_stream));
	iend = !end ? ilength(string) : IFIX(end);
	istart = IFIX(start);
	if (istart >= iend) {
	    c = EOF;
	}
	else {
	    istring = ISTRING(string);
	    c = istring[istart];
	    if (c == '\0') {	/* NULL TERMINATOR ENDS STRING INPUT */
	        c = EOF;
	    }
	    else {
		istart++;
		M_SECOND(STREAM_OBJ(input_stream)) = FIX(istart);
	    }
	}
    }
    else {  /* must be interaction stream */
	c = fgetc(INTERACTION_STREAM_FP(input_stream));
    }
    return(c);
}

int SI_stream_ungetc(c,input_stream)
    int c;
    Object input_stream;
{
    int istart;

    /* assume input_stream is chased */
    if (STRING_INPUT_STREAMP(input_stream)) {
	istart = IFIX(SECOND(STREAM_OBJ(input_stream)));
        if (istart > 0)
            M_SECOND(STREAM_OBJ(input_stream)) = FIX(istart-1);
    }

    return c;
}


