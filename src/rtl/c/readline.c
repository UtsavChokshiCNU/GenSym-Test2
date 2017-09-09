/*
 * readline.c -  Chestnut Run-Time Library entry for function read_line
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
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object chase_input_stream(Object stream);
extern long ilength(Object sequence);
extern Object make_string(Object size, Object initial_element);

#else

extern char *SI_istring();
extern Object (*SI_warn_fptr) ();
extern Object chase_input_stream();
extern long ilength();
extern Object make_string();

#endif


/* &optional 0 4 */
Object read_line(stream, eof_error_p, eof_value, recursive_p)
    Object	stream, eof_error_p, eof_value, recursive_p;
{
    Declare_local_temp;
    register int i;
    char str[256], *p, *istring;
    size_t len;
    Object newnode = NIL, eof_p = NIL, string, ostream;
    FIXNUM start, end;
    long istart, iend;
    FILE *fp, *ofp = NULL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(stream,eof_value,newnode);
    PROTECTI_2(string,ostream);

    if (!SUPPLIED_P(eof_value)) eof_value = NIL;
/*    if (!SUPPLIED_P(recursive_p)) recursive_p = NIL; */
/*    if (!SUPPLIED_P(eof_error_p)) eof_error_p = NIL; */

    MVS_2(chase_input_stream(stream), stream, ostream);

    str[0] = '\0';
    switch (STREAM_STYPE(stream)) {
	case INTERACTION_STREAM:
	    fp = INTERACTION_STREAM_FP(stream);
	    p = fgets(str, 255, fp);
	    if (!p) {
		RESTORE_STACK();
		return VALUES_2(eof_value,T);
	    }
	    while ((p = strchr(str, '\r')) || (p = strchr(str, '\n')))
		*p = '\0';
	    if (feof(fp))
		eof_p = T;
	    else
		eof_p = NIL;
	    break;
	case FILE_STREAM:
	    fp = FILE_STREAM_FP(stream);
	    p = fgets(str, 255, fp);
	    if (!p) {
		RESTORE_STACK();
		return VALUES_2(eof_value,T);
	    }
	    while ((p = strchr(str, '\r')) || (p = strchr(str, '\n')))
		*p = '\0';
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
	    istring = ISTRING(string);
	    for (i = 0; (istart < iend) && (i < 255) && (str[i] != '\n') &&
		 (str[i] != '\0'); istart++, i++) {
		str[i] = istring[istart];
	    }
	    str[i] = '\0';
	    break;
	default:
	    warn(1, "read_line: other stream type");
	    /* GENSYMCID-453: Fix all LSB compatibility issues of the Gensym Linux bundle */
	    p = fgets(str, 255, stdin); /* OLD: gets(str) */
	    if (!p) {
		RESTORE_STACK();
		return(VALUES_2(eof_value,T));
	    }
	    while ((p = strchr(str, '\r')) || (p = strchr(str, '\n')))
		*p = '\0';
	    eof_p = NIL;
	    break;
    }
    len = strlen(str);
    newnode = make_string(FIX(len), NIL);
    strcpy(ISTRING(newnode), str);
    RESTORE_STACK();
    return(VALUES_2(newnode, eof_p));
}
