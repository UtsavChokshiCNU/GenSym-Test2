/*
 * fnshtpt.c -  Chestnut Run-Time Library entry for function finish_output
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object chase_write_stream(Object stream);

#else

extern Object chase_write_stream();

#endif




Object finish_output (output_stream)
    Object output_stream;
{
    Declare_local_temp;
    output_stream = chase_write_stream(output_stream);

    if (STREAMP(output_stream)) {
	switch(STREAM_STYPE(output_stream)) {
	    case INTERACTION_STREAM:
		fflush(INTERACTION_STREAM_FP(output_stream));
		break;
	    case FILE_STREAM:
		fflush(FILE_STREAM_FP(output_stream));
		break;
	    default:
		break;
	}
    }
    return VALUES_1(NIL);
}
