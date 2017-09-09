/*
 * unredchr.c -  Chestnut Run-Time Library entry for function unread_char
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


/* &optional 1 1 */
Object unread_char (ch, input_stream)
    Object ch, input_stream;
{
    Declare_local_temp;
    Object ostream;
    int c;
    Object string;
    FIXNUM start, end;
    long istart, iend;
    char *istring;

    if (!SUPPLIED_P(input_stream)) input_stream = NIL;

    MVS_2(chase_input_stream(input_stream), input_stream, ostream);
    c = ICHAR_CODE(ch);
    if (WINDOWP(input_stream)) {
	ungetc(c, stdin);
    }
    else if (FILEP(input_stream)) {
	ungetc(c, FILE_STREAM_FP(input_stream));
    }
    else if (STRING_INPUT_STREAMP(input_stream)) {
	string = FIRST(STREAM_OBJ(input_stream));
	start = SECOND(STREAM_OBJ(input_stream));
	end = THIRD(STREAM_OBJ(input_stream));
	iend = end ? IFIX(end) : ilength(string);
	istart = IFIX(start);
	istring = ISTRING(string);
	if (istart > 0)
	    istart--;
	istring[istart] = c;
	M_SECOND(STREAM_OBJ(input_stream)) = FIX(istart);
    }
    else {  /* must be interaction stream */
	ungetc(c, INTERACTION_STREAM_FP(input_stream));
    }
    return VALUES_1(NIL);
}
