/*
 * peekchar.c -  Chestnut Run-Time Library entry for function peek_char
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object read_char(Object,Object,Object,Object);
extern Object unread_char(Object,Object);

#else

extern Object read_char();
extern Object unread_char();

#endif


/* &optional 0 5 */    
Object peek_char (peek_type, input_stream, eof_error_p, eof_value, recursive_p)
    Object peek_type, input_stream, eof_error_p, eof_value, recursive_p;
{
    Declare_local_temp;
    Object ch;

    if (!SUPPLIED_P(peek_type)) peek_type = NIL; 
    do {
	ch = read_char(input_stream, eof_error_p, eof_value, recursive_p);
    } while ((EQ(peek_type, T) && WHITESPACE_CHAR_P(ch)) ||
	     (CHARACTERP(peek_type) && !CHAR_EQ(peek_type, ch)));
    unread_char(ch, input_stream);
    return VALUES_1(ch);
}
