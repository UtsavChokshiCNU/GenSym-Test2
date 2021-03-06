/*
 * readbyte.c -  Chestnut Run-Time Library entry for function read_byte
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object chase_input_stream(Object stream);
extern long ilength(Object sequence);
extern Object write_byte(Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object chase_input_stream();
extern long ilength();
extern Object write_byte();

#endif



/* &optional 0 3 */
Object read_byte(input_stream, eof_error_p, eof_value)
    Object input_stream, eof_error_p, eof_value;
{
    Declare_local_temp;
    int c;
    FIXNUM ch;
    Object ostream, string;
    FIXNUM start, end;
    long istart, iend;
    char *istring;

    if (!SUPPLIED_P(eof_value)) eof_value = NIL;

    MVS_2(chase_input_stream(input_stream),input_stream,ostream);
    if (WINDOWP(input_stream)) {
#ifdef GCLISP
	return(wread_char(input_stream));
#else
	error(1, "read-char: not compiled for GCLISP extensions");
#endif
    }
    else if (FILEP(input_stream)) {
	c = fgetc(FILE_STREAM_FP(input_stream));
	if (c == -1)
	    return VALUES_1(eof_value);
        ch = FIX(c);
	if (ostream != NIL)
	    write_byte(ch, ostream);
    }
    else if (STRING_INPUT_STREAMP(input_stream)) {
	string = FIRST(STREAM_OBJ(input_stream));
	start = SECOND(STREAM_OBJ(input_stream));
	end = THIRD(STREAM_OBJ(input_stream));
	iend = end ? IFIX(end) : ilength(string);
	istart = IFIX(start);
	if (istart >= iend)
	    return VALUES_1(eof_value);
	istring = ISTRING(string);
	c = istring[istart];
	if (c == '\0')	/* NULL TERMINATOR ENDS STRING INPUT */
	    return VALUES_1(eof_value);
	ch = FIX(c);
	istart++;
	M_SECOND(STREAM_OBJ(input_stream)) = FIX(istart);
    }
    else {  /* must be interaction stream */
	c = fgetc(INTERACTION_STREAM_FP(input_stream));
	/* for immediate return without waiting for enter key 
	 * c = getch();
 	 * if (c == '\r')
	 *     c = '\n';
	 */
	if (c == -1)
	    return VALUES_1(eof_value);
	ch = FIX(c);
	/* echos automatically to interaction streams by fgetc */
    }
    return VALUES_1(ch);
}
