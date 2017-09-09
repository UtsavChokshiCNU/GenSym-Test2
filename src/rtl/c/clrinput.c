/*
 * clrinput.c -  Chestnut Run-Time Library entry for function clear_input
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object chase_input_stream(Object stream);

#else

extern Object chase_input_stream();

#endif


/* &optional 0 1 */
Object clear_input (input_stream)
    Object input_stream;
{
    Declare_local_temp;
    Object ostream;
    FILE *fp;

    MVS_2(chase_input_stream(input_stream), input_stream, ostream);
    switch (STREAM_STYPE(input_stream)) {
	case INTERACTION_STREAM:
/* flush input buffer--see ioctrl in a portable way */
	    fp = INTERACTION_STREAM_FP(input_stream);
	    while (feof(stdin))
		getc(stdin);
	    break;
	default:
	    break;
    }
    return VALUES_1(NIL);
}
