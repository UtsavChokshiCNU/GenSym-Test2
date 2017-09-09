/*
 * streams.c - LISPTOC stream functions
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 */

#include "runtime.h"

extern Object Qbit;
extern Object Qcharacter;
extern Object Qinteger;
extern Object Qsigned_byte;
extern Object Qstring_char;
extern Object Qunsigned_byte;
DECLARE_VARIABLE(Standard_input);

#if SI_USE_PROTOTYPES

extern void SI_INIT_streams(void);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_warn_fptr) (int n, char *lstr, ...);
extern Object cons(Object,Object);
extern Object fill_pointer(Object);
extern Object length(Object);
extern Object list(long,...);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object setf_fill_pointer(Object arr, Object fillptr);
extern Object subseq(Object,Object,Object);

#else

extern void SI_INIT_streams();
extern Object SI_alloc();
extern Object (*SI_warn_fptr) ();
extern Object cons();
extern Object fill_pointer();
extern Object length();
extern Object list();
extern Object make_array();
extern Object setf_fill_pointer();
extern Object subseq();

#endif

#include "strminit.h"

#if !defined(MSDOS) && !defined(_INTELC32_) && !defined(__ZTC__)
#define stdprn stdout
#define stdaux stderr
#endif

/* if open passed PRN or AUX, pass back the following objects */
/* *** These don't actually seem to be referenced. */
static Object Default_printer_stream = UNBOUND;
static Object Default_comm_stream = UNBOUND;

Object * SI_Stream_etypes[] = {
    &Qstring_char,
/*  Qunsigned_byte_8, Qunsigned_byte_16, Qunsigned_byte_32,
    Qsigned_byte_8, Qsigned_byte_16, Qsigned_byte_32,  */
    NIL, NIL, NIL, NIL, NIL, NIL, /* FIX LATER */
    &Qcharacter, &Qbit, &Qinteger,
    &Qunsigned_byte, &Qsigned_byte,
    &STATIC_VALUE(Standard_input) /* terminator, FIXME: is this address shared by every threads? -- binghe, 2009/5/10 */
};


static Object make_interaction_stream();

/* init stuff */



/* Define ANSI type predicates. */
#undef DEFINE_STREAM_PREDICATE
#define DEFINE_STREAM_PREDICATE(name, stype) \
Object name(x) \
  Object x; \
{ \
    Declare_local_temp; \
  if (STREAMP(x) && (STREAM_STYPE(x) == stype)) \
    return VALUES_1(Qt); \
  else \
    return VALUES_1(NIL); \
}

DEFINE_STREAM_PREDICATE(broadcast_stream_p, BROADCAST_STREAM)
DEFINE_STREAM_PREDICATE(concatenated_stream_p, CONCATENATED_STREAM)
DEFINE_STREAM_PREDICATE(echo_stream_p, ECHO_STREAM)
DEFINE_STREAM_PREDICATE(file_stream_p, FILE_STREAM)
DEFINE_STREAM_PREDICATE(string_input_stream_p, STRING_INPUT_STREAM)
DEFINE_STREAM_PREDICATE(string_output_stream_p, STRING_OUTPUT_STREAM)
DEFINE_STREAM_PREDICATE(synonym_stream_p, SYNONYM_STREAM)
DEFINE_STREAM_PREDICATE(two_way_stream_p, TWO_WAY_STREAM)
DEFINE_STREAM_PREDICATE(interaction_stream_p, INTERACTION_STREAM)

#undef DEFINE_STREAM_PREDICATE

Object string_stream_p(x)
    Object x;
{
    Declare_local_temp;
    if (STREAMP(x) &&
	((STREAM_STYPE(x) == STRING_INPUT_STREAM) ||
	 (STREAM_STYPE(x) == STRING_OUTPUT_STREAM)))
	return VALUES_1(Qt);
    else
	return VALUES_1(NIL);
}


/*ARGSUSED*/	/* wrapper ignored when not SI_SUPPORT_CLOS */
static Object SI_make_stream (stype, dir, etype, closed_p, obj, wrapper)
    short stype, dir, etype, closed_p;
    Object obj, wrapper;
{
    Declare_local_temp;
    Object x;
    Declare_stack_pointer;

    INIT_STREAMS();
    SAVE_STACK();
    PROTECT_1(obj);
    SI_ALLOC_STREAM(x, stype, dir, etype, closed_p, obj, wrapper);
    RESTORE_STACK();
    return VALUES_1(x);
}

static Object make_interaction_stream(dir, file, name)
    int dir;
    FILE *file;
    Object name;
{
    Declare_stack_pointer;
    Object fobj;

    SAVE_STACK();
    PROTECT_1(name);

    INIT_STREAMS();
    SI_ALLOC_FILE_OBJECT(fobj, file, name);
    RESTORE_STACK();
    return SI_MAKE_STREAM(INTERACTION_STREAM,dir,S_STRING_CHAR,0,fobj,
		       SI_WRAPPER_interaction_stream);
}


Object make_synonym_stream (symbol)
    Object symbol;
{   return SI_MAKE_STREAM(SYNONYM_STREAM,0,0,0,symbol,SI_WRAPPER_synonym_stream);
}

Object make_broadcast_stream varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *streams;
    long i;
    Declare_stack_pointer;

    INIT_STREAMS();
    SAVE_STACK();
    SETUP_REST(n,streams);

    for (result = NIL,i = 0; i < n; i++)
	result = SI_MAKE_STREAM(BROADCAST_STREAM,S_OUTPUT,0,0,streams[i],
			     SI_WRAPPER_broadcast_stream);

    RESTORE_STACK();
    return VALUES_1(result);
}

Object make_concatenated_stream varargs_1(int, n)
{
    Declare_local_temp;
    Object result, *streams;
    long i;
    Declare_stack_pointer;

    INIT_STREAMS();
    SAVE_STACK();
    SETUP_REST(n,streams);

    for (result = NIL,i = 0; i < n; i++)
	result = SI_MAKE_STREAM(CONCATENATED_STREAM,S_OUTPUT,0,0,streams[i],
			     SI_WRAPPER_concatenated_stream);

    RESTORE_STACK();
    return VALUES_1(result);
}

Object make_two_way_stream (input_stream, output_stream)
    Object input_stream, output_stream;
{
    Object result = cons(input_stream,output_stream);

    return
	SI_MAKE_STREAM(TWO_WAY_STREAM,S_IO,0,0,result,SI_WRAPPER_two_way_stream);
}

Object make_echo_stream (input_stream, output_stream)
    Object input_stream, output_stream;
{
    Object result = cons(input_stream,output_stream);

    return SI_MAKE_STREAM(ECHO_STREAM,S_IO,0,0,result,SI_WRAPPER_echo_stream);
}

/* &optional 1 2 */
Object make_string_input_stream (string, start, end)
    Object string, start, end;
{
    Declare_local_temp;
    Object result;
    Object args;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(string,start,end);
    if (UNSUPPLIED_P(start)) start = ZERO;
    if (UNSUPPLIED_P(end) || !TRUEP(end)) end = length(string);
    args = LIST_3(string, start, end);
    result = SI_MAKE_STREAM(STRING_INPUT_STREAM,S_INPUT,S_STRING_CHAR,FALSE,args,
			 SI_WRAPPER_string_input_stream);
    RESTORE_STACK();
    return VALUES_1(result);
}

Object make_string_output_stream ()
{
    Object arr;

    arr = make_array (FIX(128), Qstring_char, KOPT,
			KOPT, T, ZERO, KOPT, KOPT);
    return
	SI_MAKE_STREAM(STRING_OUTPUT_STREAM,S_OUTPUT,S_STRING_CHAR,FALSE,arr,
		    SI_WRAPPER_string_output_stream);
}

Object string_stream_index(string_input_stream)
    Object string_input_stream;
{
    return(fill_pointer(STREAM_OBJ(string_input_stream)));
}

/* extend_string_output_stream is used by the macro WITH-OUTPUT-TO-STRING */
Object extend_string_output_stream(string)
    Object string;
{
    return
	SI_MAKE_STREAM(STRING_OUTPUT_STREAM,S_OUTPUT,S_STRING_CHAR,FALSE,string,
		    SI_WRAPPER_string_output_stream);
}

Object get_output_stream_string (string_output_stream)
    Object string_output_stream;
{
    Declare_local_temp;
    Object oldstr = STREAM_OBJ(string_output_stream);
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(oldstr);
    PROTECTI_1(result);
    result = subseq(oldstr,ZERO,fill_pointer(oldstr));
    setf_fill_pointer(oldstr, ZERO);
    RESTORE_STACK();
    return VALUES_1(result);
}

Object input_stream_p (stream)
    Object stream;
{
    Declare_local_temp;
    short dir = STREAM_DIR(stream);

    FOREVER {
	dir = STREAM_DIR(stream);
	if ((dir == S_INPUT) || (dir == S_IO))
	    return VALUES_1(T);
	else if (STREAM_STYPE(stream) == SYNONYM_STREAM)
	    stream = STREAM_OBJ(stream);
	else
	    return VALUES_1(NIL);
    }
}

Object output_stream_p (stream)
    Object stream;
{
    Declare_local_temp;
    short dir;

    FOREVER {
	dir = STREAM_DIR(stream);
	if ((dir == S_OUTPUT) || (dir == S_IO))
	    return VALUES_1(T);
	else if (STREAM_STYPE(stream) == SYNONYM_STREAM)
	    stream = STREAM_OBJ(stream);
	else
	    return VALUES_1(NIL);
    }
}

Object stream_element_type (stream)
    Object stream;
{
    Declare_local_temp;
    return VALUES_1(*SI_Stream_etypes[STREAM_ETYPE(stream)]);
}

element_type_to_etype(element_type)
    Object element_type;
{
    register int i;

    for (i = 0; SI_Stream_etypes[i] == &Standard_input; i++) {
	if (EQ(element_type, *SI_Stream_etypes[i]))
	    return(i);
    }
    return(0);  /* default is string_char */
}

Object lclose (stream, abort)
    Object stream, abort;
{
    Declare_local_temp;
    short stype;
    Object obj;

    if (!STREAMP(stream))
	return warn(2, "close: invalid argument - ~S", stream);
    STREAM_INFO(stream) |= S_CLOSED_P;
    stype = STREAM_STYPE(stream);
    obj = STREAM_OBJ(stream);
    switch(stype) {
	case AUX_STREAM:
	    break;
	case BROADCAST_STREAM:
	    break;
	case CONCATENATED_STREAM:
	    break;
	case ECHO_STREAM:
	case TWO_WAY_STREAM:
	    break;
	case INTERACTION_STREAM:
	    fclose((FILE *) obj);
	    break;
	case FILE_STREAM:
	    fclose((FILE *) COBJECT_OBJ(obj));
	    break;
	case SYNONYM_STREAM:
	    break;
	case STRING_INPUT_STREAM:
	case STRING_OUTPUT_STREAM:
	    break;
	default:
	    break;
    }
    return VALUES_1(NIL);
}



