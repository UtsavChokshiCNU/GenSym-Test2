/*
 * cswrsrm.c -  Chestnut Run-Time Library entry for function chase_write_stream
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
extern Object chase_output_stream(Object stream);

#else

extern void SI_INIT_streams();
extern Object chase_output_stream();

#endif


#include "strminit.h"

/* &optional 0 1 */
Object chase_write_stream(stream)
    Object stream;
{
    Declare_local_temp;

    INIT_STREAMS();
    
    if (EQ(stream, T))
	stream = Terminal_io;
    else if (!SUPPLIED_P(stream) || stream == NIL)
	stream = Standard_output;
    stream = chase_output_stream(stream);
    return VALUES_1(stream);
}
