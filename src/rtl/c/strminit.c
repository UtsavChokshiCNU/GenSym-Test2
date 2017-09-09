/*
 * strminit.c - the Stream sytem global variables and initializer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object STATIC_STRING(char *s);
extern Object cons(Object,Object);

#else

extern void SI_add_external_root();
extern Object SI_alloc();
extern Object STATIC_STRING();
extern Object cons();

#endif


#include "strminit.h"

long SI_init_streams_flag;

DEFINE_VARIABLE(Terminal_io);
DEFINE_VARIABLE(Standard_input);
DEFINE_VARIABLE(Standard_output);
DEFINE_VARIABLE(Error_output);
Object Query_io = UNBOUND;
DEFINE_VARIABLE(Debug_io);
Object Trace_output = UNBOUND;

void SI_INIT_streams()
{
    Object fobj;
    SI_Declare_static_string(in_name, din, "stdin");
    SI_Declare_static_string(out_name, dout, "stdout");
    SI_Declare_static_string(err_name, derr, "stderr");
/* 
    SI_Declare_static_string(prn_name, dprn, "prn");
    SI_Declare_static_string(aux_name, daux, "aux");
*/

    SI_init_streams_flag  = TRUE;

    SI_ALLOC_FILE_OBJECT(fobj, stdin, in_name);
    SI_ALLOC_STREAM(Standard_input, INTERACTION_STREAM, S_INPUT,
		    S_STRING_CHAR, 0, fobj, SI_WRAPPER_interaction_stream);
    SI_ALLOC_FILE_OBJECT(fobj, stdout, out_name);
    SI_ALLOC_STREAM(Standard_output, INTERACTION_STREAM, S_OUTPUT,
		    S_STRING_CHAR, 0, fobj, SI_WRAPPER_interaction_stream);
    SI_ALLOC_FILE_OBJECT(fobj, stderr, err_name);
    SI_ALLOC_STREAM(Error_output, INTERACTION_STREAM, S_OUTPUT,
		    S_STRING_CHAR, 0, fobj, SI_WRAPPER_interaction_stream);
    
    SI_ALLOC_STREAM(Terminal_io,TWO_WAY_STREAM,S_IO,
		    0,0, 
		    cons(Standard_input,Standard_output),
		    SI_WRAPPER_two_way_stream);

    PROTECT_GLOBAL(Standard_input);
    PROTECT_GLOBAL(Standard_output);
    PROTECT_GLOBAL(Terminal_io);
    PROTECT_GLOBAL(Error_output);



    /* All streams need to be fixed to be separate synonym streams */

    PROTECT_GLOBAL(Query_io);
    Query_io = Terminal_io;

    PROTECT_GLOBAL(Debug_io);
    Debug_io = Terminal_io;

    PROTECT_GLOBAL(Trace_output);
    Trace_output = Standard_output;

/* non-standard things
    Default_printer_stream =
	make_interaction_stream(S_OUTPUT, stdprn, prn_name);
    Default_comm_stream =
	make_interaction_stream(S_OUTPUT, stdaux, aux_name);
*/

}

/* end of init */
