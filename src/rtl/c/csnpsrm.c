/*
 * csnpsrm.c -  Chestnut Run-Time Library entry for function chase_input_stream
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

DECLARE_VARIABLE(Standard_input);
DECLARE_VARIABLE(Terminal_io);
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern void SI_INIT_streams(void);
extern Object chase_output_stream(Object stream);

#else

extern void SI_INIT_streams();
extern Object chase_output_stream();

#endif


#include "strminit.h"


/* &optional 0 1 */
Object chase_input_stream(stream)
    Object stream;
{
    Declare_local_temp;
    Object ostream = NIL;

    INIT_STREAMS();
    STARTCHASEI:

    if (!SUPPLIED_P(stream)) stream = NIL;
    if (stream == NIL) stream = Terminal_io;
    if (EQ(stream, T))
	stream = Standard_input;

    switch (STREAM_STYPE(stream)) {
	case INTERACTION_STREAM:
	case FILE_STREAM:
	case STRING_INPUT_STREAM:
	case CONCATENATED_STREAM:
	    break;
	case ECHO_STREAM:
	    ostream = chase_output_stream(CDR(STREAM_OBJ(stream)));
	    stream = CAR(STREAM_OBJ(stream));
	    goto STARTCHASEI;
	case SYNONYM_STREAM:
	    stream = STREAM_OBJ(stream);
	    goto STARTCHASEI;
	case TWO_WAY_STREAM:
	    stream = CAR(STREAM_OBJ(stream));
	    goto STARTCHASEI;
	default:
	    break;
    }
    return(VALUES_2(stream, ostream));
}
