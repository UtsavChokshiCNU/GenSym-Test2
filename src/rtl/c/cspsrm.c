/*
 * cspsrm.c -  Chestnut Run-Time Library entry for function chase_output_stream
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

DECLARE_VARIABLE(Standard_output);
DECLARE_VARIABLE(Terminal_io);

#if SI_USE_PROTOTYPES

extern void SI_INIT_streams(void);

#else

extern void SI_INIT_streams();

#endif


#include "strminit.h"

/* &optional 0 1 */
Object chase_output_stream(stream) /* Probably should be static */
    Object stream;
{
    Declare_local_temp;

    INIT_STREAMS();
    STARTCHASEO:

    if (!SUPPLIED_P(stream)) stream = NIL;
    if (stream == NIL) stream = Terminal_io;
    if (EQ(stream, T))
	stream = Standard_output;

    switch (STREAM_STYPE(stream)) {
	case INTERACTION_STREAM:
	case FILE_STREAM:
	case STRING_OUTPUT_STREAM:
	    break;
	case BROADCAST_STREAM:
	    stream = STREAM_OBJ(stream);
	    break;
	case ECHO_STREAM:
	    stream = CDR(STREAM_OBJ(stream));
	    goto STARTCHASEO;
	case SYNONYM_STREAM:
	    stream = STREAM_OBJ(stream);
	    goto STARTCHASEO;
	case TWO_WAY_STREAM:
	    stream = CDR(STREAM_OBJ(stream));
	    goto STARTCHASEO;
	default:
	    break;
    }
    return VALUES_1(stream);
}
