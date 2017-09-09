/*
 * lreader.c - Lisp Reader functions
 * Copyright (c) 1989-1991 Chestnut Software, Inc.  All rights reserved.
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area;
extern Object Features;
extern Object Kexternal;
extern Object Kread_eof;
extern SI_Area Local_area;
DECLARE_VARIABLE(Package);
extern Object Pkeyword;
extern Object Qbackquote;
extern Object Qbit;
extern Object Qfunction;
extern Object Qkeyword;
extern Object Qquote;
DECLARE_VARIABLE(Read_base);
extern Object Read_suppress;
extern Object Readtable;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern TLS SI_Special_frame *SI_Special_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern int SI_gc_count;
extern SI_Area Static_area;
extern TLS Object T_temp;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object MAKE_FUNCTION(Object (*entry)(), Object env, long variadicp, long nreq, long npos);
extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object SI_cons_with_gc(Object x, Object y);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);
#else
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
#endif
extern Object funcall3(Object func, Object arg1, Object arg2, Object arg3);
extern char *SI_istring(Object o);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object SI_throw(Object tag, Object firstval);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object cdouble_to_double(double a);
extern Object chase_input_stream(Object stream);
extern Object clong_to_bignum(SI_Long a);
extern Object cons(Object,Object);
extern Object digit_char_p(Object,Object);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object eval_run(Object);
extern Object ifind_package(char *name);
extern Object ifind_symbol(char *name, Object pkg);
extern Object iintern(char *name, Object pkg);
extern Object imake_duplicate_string(char *oldstring);
extern Object iname_char(char *iname);
extern Object istring_to_string(char *istring);
extern Object last(Object,Object);
extern Object length(Object);
extern Object list(long,...);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object make_string(Object size, Object initial_element);
extern Object make_symbol(Object);
extern Object member(Object item, Object list, Object test, Object test_not, Object key);
extern Object nreverse(Object);
extern Object parse_namestring(Object thing, Object host, Object defaults, Object start, Object end, Object junk_allowed);
extern void restore_frontier(SI_Segment *seg, void *frontier);
extern Object unread_char(Object,Object);
extern Object copy_readtable(Object from, Object to);

#else

extern Object MAKE_FUNCTION();
extern Object SI_alloc_primitive_vector();
extern Object SI_alloc();
extern Object SI_cons_with_gc();
extern Object (*SI_error_fptr) ();
extern Object SI_internal_funcall();
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall();
#else
extern Object funcall1();
extern Object funcall2();
#endif
extern Object funcall3();
extern char *SI_istring();
extern Object SI_symbol_field();
extern Object SI_throw();
extern Object (*SI_warn_fptr) ();
extern Object cdouble_to_double();
extern Object chase_input_stream();
extern Object clong_to_bignum();
extern Object cons();
extern Object digit_char_p();
extern Object do_setf_aref();
extern Object eval_run();
extern Object ifind_package();
extern Object ifind_symbol();
extern Object iintern();
extern Object imake_duplicate_string();
extern Object iname_char();
extern Object istring_to_string();
extern Object last();
extern Object length();
extern Object list();
extern Object make_array();
extern Object make_string();
extern Object make_symbol();
extern Object member();
extern Object nreverse();
extern Object parse_namestring();
extern void restore_frontier();
extern Object unread_char();
extern Object copy_readtable();

#endif

#include "bigext.h"

#ifndef Platform_Windows
# include <inttypes.h>
#endif

static Object init_reader();

extern long SI_stream_ungetc();
extern long SI_stream_getc();

#define INIT_READER() ( Readtable == UNBOUND ? \
    Readtable = NIL, \
    Readtable = init_reader() : \
    Readtable)

#define STANDARD_READTABLE() ( Standard_readtable == UNBOUND ? \
    Standard_readtable = init_reader() : \
    Standard_readtable)

#define GETC()      (Read_fp ? fgetc(Read_fp) : SI_stream_getc(Read_stream))
#define UNGETC(c) (Read_fp ? \
		   ungetc(c, Read_fp) : \
		   SI_stream_ungetc(c, Read_stream))

#define isletterdigit(c, radix)	(((((c) - 'A') + 10) < (radix)) && \
				 ((((c) - 'A') + 10) >= 0))
#define issign(c)		(((c) == '+') || ((c) == '-'))
#define ismarker(c)		(((c) == 'D') || ((c) == 'E') || \
				 ((c) == 'F') || ((c) == 'L') || ((c) == 'S'))
#define isdot(c)		((c) == '.')
#define isbasedigit(c, radix)	(isdigit(c) || isletterdigit(c, radix))
#define isend(c)		((c) == '\0')
#define isratio(c)		((c) == '/')

#define ILLEGAL		0x00	/* illegal character */
#define WHITESPACE	0x01	/* tab, space, page, newline, etc. */
#define CONSTITUENT	0x02	/* constituent */
#define SINGLE_ESC	0x04	/* single escape */
#define MULTIPLE_ESC	0x08	/* multiple escape */
#define MACRO		0x10	/* macro character */
#define TERMINATING	0x20	/* set=terminating, clear=non-terminating */
#define DISPATCH	0x40	/* set=dispatch, clear=ordinary */
#define NON_TERMINATING_MACRO(s)  (((s) & MACRO) && !((s) & TERMINATING))
#define TERMINATING_MACRO(s)  (((s) & MACRO) && ((s) & TERMINATING))

#define ATT_ILLEGAL	0x0000
#define ATT_ALPHABETIC	0x0001
#define ATT_ALPHADIGIT	0x0002
#define ATT_PACKAGE	0x0004
#define ATT_PLUS_SIGN	0x0008
#define ATT_MINUS_SIGN	0x0010
#define ATT_DOT		0x0020
#define ATT_DECIMAL	0x0040
#define ATT_RATIO	0x0080
#define ATT_DOUBLE_EXP	0x0100
#define ATT_FLOAT_EXP	0x0200
#define ATT_SINGLE_EXP	0x0400
#define ATT_LONG_EXP	0x0800
#define ATT_SHORT_EXP	0x1000


static Object reader();
static Object reader_delimited_list();
static Object read_infix_arg();
static Object parse_number(), parse_symbol();
static Object token_package();
static unsigned int read_bignum_producer();
static int potential_number();
static int read_extended_token();

/* feature expression evaluator variables */
extern Object Pkeyword;
extern Object NEW_SYMBOL();
static Object feature_init  = UNBOUND;
static Object lreader_Kand = UNBOUND;
static Object lreader_Kor  = UNBOUND;
static Object lreader_Knot = UNBOUND;
static void INIT_feature_keys();

extern Object xbignum_normalize();

long SI_requires_escaping_full();
extern long (*SI_requires_escaping_fptr)();

#define MAXCHARS 256
static UCHAR Char_map[MAXCHARS] = {
    0,0,0,0,0,0,0,0,5,1, 		/* 0-9 */
    4,0,3,6,0,0,0,0,0,0,		/* 10-19 */
    0,0,0,0,0,0,0,0,0,0,		/* 20-29 */
    0,0,2,9,10,11,12,13,14,15,		/* 30-39 */
    16,17,18,19,20,21,22,23,24,25,	/* 40-49 */
    26,27,28,29,30,31,32,33,34,35,	/* 50-59 */
    36,37,38,39,40,41,42,43,44,45,	/* 60-69 */
    46,47,48,49,50,51,52,53,54,55,	/* 70-79 */
    56,57,58,59,60,61,62,63,64,65,	/* 80-89 */
    66,67,68,69,70,71,72,73,74,75,	/* 90-99 */
    76,77,78,79,80,81,82,83,84,85,	/* 100-109 */
    86,87,88,89,90,91,92,93,94,95,	/* 110-119 */
    96,97,98,99,100,101,102,7,0,0,	/* 120-129 */
    0,0,0,0,0,0,0,0,0,0,		/* 130-139 */
    0,0,0,0,0,0,0,0,0,0,		/* 140-149 */
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0
};

static Object labelref_dispatch_handler();
static Object quote_dispatch_handler();
static Object oparen_dispatch_handler();
static Object star_dispatch_handler();
static Object plus_dispatch_handler();
static Object minus_dispatch_handler();
static Object dot_dispatch_handler();
static Object colon_dispatch_handler();
static Object eq_dispatch_handler();
static Object a_dispatch_handler();
static Object b_dispatch_handler();
static Object c_dispatch_handler();
static Object o_dispatch_handler();
static Object p_dispatch_handler();
static Object r_dispatch_handler();
static Object s_dispatch_handler();
static Object x_dispatch_handler();
static Object backslash_dispatch_handler();
static Object vertbar_dispatch_handler();

typedef Object (*initial_readtable_ptr)();

#define EMPTY ((initial_readtable_ptr) 0)

static initial_readtable_ptr Standard_cdispatchtable[] = {
    EMPTY,			/* 0 illegal */
    EMPTY, 			/* 1 <tab> */
    EMPTY,			/* 2 <space> */
    EMPTY,			/* 3 <page> */
    EMPTY,			/* 4 <newline> */
    EMPTY,			/* 5 <backspace> */
    EMPTY,			/* 6 <return> */
    EMPTY,			/* 7 <rubout> */
    EMPTY,			/* 8 <linefeed> */
    EMPTY,			/* 9 ! */
    EMPTY, 			/* 10 " */
    labelref_dispatch_handler,	/* 11 # */
    EMPTY,			/* $ */
    EMPTY,			/* % */
    EMPTY,			/* & */
    quote_dispatch_handler,	/* 15 ' */
    oparen_dispatch_handler,	/* ( */
    EMPTY, 			/* ) */
    star_dispatch_handler,	/* * */
    plus_dispatch_handler,	/* + */
    EMPTY,			/* 20 , */
    minus_dispatch_handler,	/* - */
    dot_dispatch_handler,	/* . */
    EMPTY,			/* / */
    EMPTY,			/* 0 */
    EMPTY,			/* 1 */
    EMPTY,			/* 2 */
    EMPTY,			/* 3 */
    EMPTY,			/* 4 */
    EMPTY,			/* 5 */
    EMPTY,			/* 6 */
    EMPTY,			/* 7 */
    EMPTY,			/* 8 */
    EMPTY,			/* 9 */
    colon_dispatch_handler,	/* : */
    EMPTY,			/* 35 ; */
    EMPTY,			/* < */
    eq_dispatch_handler,	/* = */
    EMPTY,			/* > */
    EMPTY,			/* ? */
    EMPTY,			/* 40 @ */
    a_dispatch_handler,		/* A */
    b_dispatch_handler,		/* B */
    c_dispatch_handler,		/* C */
    EMPTY,			/* D */
    EMPTY,			/* 45 E */
    EMPTY,			/* F */
    EMPTY,			/* G */
    EMPTY,			/* H */
    EMPTY,			/* I */
    EMPTY,			/* 50 J */
    EMPTY,			/* K */
    EMPTY,			/* L */
    EMPTY,			/* M */
    EMPTY,			/* N */
    o_dispatch_handler,		/* 55 O */
    p_dispatch_handler,		/* P */
    EMPTY,			/* Q */
    r_dispatch_handler,		/* R */
    s_dispatch_handler,		/* S */
    EMPTY,			/* 60 T */
    EMPTY,			/* U */
    EMPTY,			/* V */
    EMPTY,			/* W */
    x_dispatch_handler,		/* X */
    EMPTY,			/* 65 Y */
    EMPTY,			/* Z */
    EMPTY,			/* [ */
    backslash_dispatch_handler,	/* \ */
    EMPTY,			/* ] */
    EMPTY,			/* 70 ^ */
    EMPTY,			/* _ */
    EMPTY,			/* ` */
    a_dispatch_handler,		/* a */
    b_dispatch_handler,		/* b */
    c_dispatch_handler,		/* c */
    EMPTY,			/* d */
    EMPTY,			/* 45 e */
    EMPTY,			/* f */
    EMPTY,			/* g */
    EMPTY,			/* h */
    EMPTY,			/* i */
    EMPTY,			/* 50 j */
    EMPTY,			/* k */
    EMPTY,			/* k */
    EMPTY,			/* m */
    EMPTY,			/* n */
    o_dispatch_handler,		/* 51 o */
    p_dispatch_handler,		/* p */
    EMPTY,			/* q */
    r_dispatch_handler,		/* r */
    s_dispatch_handler,		/* s */
    EMPTY,			/* 60 t */
    EMPTY,			/* u */
    EMPTY,			/* v */
    EMPTY,			/* w */
    x_dispatch_handler,		/* x */
    EMPTY,			/* 65 y */
    EMPTY,			/* z */
    EMPTY,			/* { */
    vertbar_dispatch_handler,	/* 100 | */
    EMPTY,			/* } */
    EMPTY,			/* ~ */
};

extern  Object SI_comma_macro_handler();

static Object dquote_macro_handler();
static Object quote_macro_handler();
static Object oparen_macro_handler();
static Object cparen_macro_handler();
static Object comma_macro_handler();
static Object semicolon_macro_handler();
static Object backquote_macro_handler();

static Object Standard_readtable = UNBOUND;

#define READTABLE_SYNTAX_VECTOR(o) \
    M_CAR(READTABLE_ENTRIES(o))

#define READTABLE_SYNTAX(o) \
    SI_PRIMITIVE_VECTOR_CONTENTS(READTABLE_SYNTAX_VECTOR(o), SI_PVT_Uchar)

#define READTABLE_DISPATCH_VECTOR(o) \
    M_CDR(READTABLE_ENTRIES(o))

#define READTABLE_DISPATCH(o) \
    SI_PRIMITIVE_VECTOR_CONTENTS(READTABLE_DISPATCH_VECTOR(o), SI_PVT_Object)

static UCHAR Standard_syntax[MAXCHARS] =
   {ILLEGAL, 	/* 0 illegal */
    WHITESPACE, 	/* 1 <tab> */
    WHITESPACE, 	/* 2 <space> */
    WHITESPACE, 	/* 3 <page> */
    WHITESPACE, 	/* 4 <newline> */
    WHITESPACE, 	/* 5 <backspace> */
    WHITESPACE, 	/* 6 <return> */
    WHITESPACE, 	/* 7 <rubout> */
    WHITESPACE, 	/* 8 <linefeed> */
    CONSTITUENT, 	/* 9 ! */
    MACRO | TERMINATING,  /* 10 " */
    MACRO | DISPATCH,  /* 11 # */
    CONSTITUENT, 	/* $ */
    CONSTITUENT, 	/* % */
    CONSTITUENT, 	/* & */
    MACRO | TERMINATING,  /* 15 ' */
    MACRO | TERMINATING,  /* ( */
    MACRO | TERMINATING,  /* ) */
    CONSTITUENT, 	/* * */
    CONSTITUENT, 	/* + */
    MACRO | TERMINATING,  /* 20 , */
    CONSTITUENT, 	/* - */
    CONSTITUENT, 	/* . */
    CONSTITUENT, 	/* / */
    CONSTITUENT, 	/* 0 */
    CONSTITUENT, 	/* 25 1 */
    CONSTITUENT, 	/* 2 */
    CONSTITUENT, 	/* 3 */
    CONSTITUENT, 	/* 4 */
    CONSTITUENT, 	/* 5 */
    CONSTITUENT, 	/* 30 6 */
    CONSTITUENT, 	/* 7 */
    CONSTITUENT, 	/* 8 */
    CONSTITUENT, 	/* 9 */
    CONSTITUENT, 	/* : */
    MACRO | TERMINATING,  /* 35 ; */
    CONSTITUENT, 	/* < */
    CONSTITUENT, 	/* = */
    CONSTITUENT, 	/* > */
    CONSTITUENT, 	/* ? */
    CONSTITUENT, 	/* 40 @ */
    CONSTITUENT, 	/* A */
    CONSTITUENT, 	/* B */
    CONSTITUENT, 	/* C */
    CONSTITUENT, 	/* D */
    CONSTITUENT, 	/* 45 E */
    CONSTITUENT, 	/* F */
    CONSTITUENT, 	/* G */
    CONSTITUENT, 	/* H */
    CONSTITUENT, 	/* I */
    CONSTITUENT, 	/* 50 J */
    CONSTITUENT, 	/* K */
    CONSTITUENT, 	/* L */
    CONSTITUENT, 	/* M */
    CONSTITUENT, 	/* N */
    CONSTITUENT, 	/* 55 O */
    CONSTITUENT, 	/* P */
    CONSTITUENT, 	/* Q */
    CONSTITUENT, 	/* R */
    CONSTITUENT, 	/* S */
    CONSTITUENT, 	/* 60 T */
    CONSTITUENT, 	/* U */
    CONSTITUENT, 	/* V */
    CONSTITUENT, 	/* W */
    CONSTITUENT, 	/* X */
    CONSTITUENT, 	/* 65 Y */
    CONSTITUENT, 	/* Z */
    CONSTITUENT, 	/* [ */
    SINGLE_ESC, 	/* \ */
    CONSTITUENT, 	/* ] */
    CONSTITUENT, 	/* 70 ^ */
    CONSTITUENT, 	/* _ */
    MACRO | TERMINATING,  /* ` */
    CONSTITUENT, 	/* a */
    CONSTITUENT, 	/* b */
    CONSTITUENT, 	/* 75 c */
    CONSTITUENT, 	/* d */
    CONSTITUENT, 	/* e */
    CONSTITUENT, 	/* f */
    CONSTITUENT, 	/* g */
    CONSTITUENT, 	/* 80 h */
    CONSTITUENT, 	/* i */
    CONSTITUENT, 	/* j */
    CONSTITUENT, 	/* k */
    CONSTITUENT, 	/* l */
    CONSTITUENT, 	/* 85 m */
    CONSTITUENT, 	/* n */
    CONSTITUENT, 	/* o */
    CONSTITUENT, 	/* p */
    CONSTITUENT, 	/* q */
    CONSTITUENT, 	/* 90 r */
    CONSTITUENT, 	/* s */
    CONSTITUENT, 	/* t */
    CONSTITUENT, 	/* u */
    CONSTITUENT, 	/* v */
    CONSTITUENT, 	/* 95 w */
    CONSTITUENT, 	/* x */
    CONSTITUENT, 	/* y */
    CONSTITUENT, 	/* z */
    CONSTITUENT, 	/* { */
    MULTIPLE_ESC, 	/* 100 | */
    CONSTITUENT, 	/* } */
    CONSTITUENT};       /* ~ */

static initial_readtable_ptr Standard_ptr[MAXCHARS] =
   {EMPTY,	/* 0 illegal */
    EMPTY,	/* 1 <tab> */
    EMPTY,	/* 2 <space> */
    EMPTY,	/* 3 <page> */
    EMPTY,	/* 4 <newline> */
    EMPTY,	/* 5 <backspace> */
    EMPTY,	/* 6 <return> */
    EMPTY,	/* 7 <rubout> */
    EMPTY,	/* 8 <linefeed> */
    EMPTY,	/* 9 ! */
    dquote_macro_handler, /* 10 " */
    (Object (*)()) Standard_cdispatchtable, /* 11 # */
    EMPTY,	/* $ */
    EMPTY,	/* % */
    EMPTY,	/* & */
    quote_macro_handler, /* 15 ' */
    oparen_macro_handler, /* ( */
    cparen_macro_handler, /* ) */
    EMPTY,	/* * */
    EMPTY,	/* + */
    comma_macro_handler, /* 20 , */
    EMPTY,	/* - */
    EMPTY,	/* . */
    EMPTY,	/* / */
    EMPTY,	/* 0 */
    EMPTY,	/* 25 1 */
    EMPTY,	/* 2 */
    EMPTY,	/* 3 */
    EMPTY,	/* 4 */
    EMPTY,	/* 5 */
    EMPTY,	/* 30 6 */
    EMPTY,	/* 7 */
    EMPTY,	/* 8 */
    EMPTY,	/* 9 */
    EMPTY,	/* : */
    semicolon_macro_handler, /* 35 ; */
    EMPTY,	/* < */
    EMPTY,	/* = */
    EMPTY,	/* > */
    EMPTY,	/* ? */
    EMPTY,	/* 40 @ */
    EMPTY,	/* A */
    EMPTY,	/* B */
    EMPTY,	/* C */
    EMPTY,	/* D */
    EMPTY,	/* 45 E */
    EMPTY,	/* F */
    EMPTY,	/* G */
    EMPTY,	/* H */
    EMPTY,	/* I */
    EMPTY,	/* 50 J */
    EMPTY,	/* K */
    EMPTY,	/* L */
    EMPTY,	/* M */
    EMPTY,	/* N */
    EMPTY,	/* 55 O */
    EMPTY,	/* P */
    EMPTY,	/* Q */
    EMPTY,	/* R */
    EMPTY,	/* S */
    EMPTY,	/* 60 T */
    EMPTY,	/* U */
    EMPTY,	/* V */
    EMPTY,	/* W */
    EMPTY,	/* X */
    EMPTY,	/* 65 Y */
    EMPTY,	/* Z */
    EMPTY,	/* [ */
    EMPTY,	/* \ */
    EMPTY,	/* ] */
    EMPTY,	/* 70 ^ */
    EMPTY,	/* _ */
    backquote_macro_handler, /* ` */
    EMPTY,	/* a */
    EMPTY,	/* b */
    EMPTY,	/* 75 c */
    EMPTY,	/* d */
    EMPTY,	/* e */
    EMPTY,	/* f */
    EMPTY,	/* g */
    EMPTY,	/* 80 h */
    EMPTY,	/* i */
    EMPTY,	/* j */
    EMPTY,	/* k */
    EMPTY,	/* l */
    EMPTY,	/* 85 m */
    EMPTY,	/* n */
    EMPTY,	/* o */
    EMPTY,	/* p */
    EMPTY,	/* q */
    EMPTY,	/* 90 r */
    EMPTY,	/* s */
    EMPTY,	/* t */
    EMPTY,	/* u */
    EMPTY,	/* v */
    EMPTY,	/* 95 w */
    EMPTY,	/* x */
    EMPTY,	/* y */
    EMPTY,	/* z */
    EMPTY,	/* { */
    EMPTY,	/* 100 | */
    EMPTY,	/* } */
    EMPTY};	/* ~ */
    

/* performs lazy initialization for the reader */
static Object init_reader ()
{
    Declare_local_temp;
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = copy_readtable (NIL, KOPT);
    RESTORE_CURRENT_AREA(a);
    
    /* initializes reader state here */
    SI_requires_escaping_fptr = SI_requires_escaping_full;
    return VALUES_1(result);
}

#define MAP(x)	(Char_map[x])

static FILE *Read_fp;
static Object Read_stream;

read_error (c)
    int c;
{
    error(2, "read: illegal character - ~S", CHR(c));
}

read_eof_error( )
{
    error(1, "read: unexpected end of file");
}

read_syntax_error( syntax)
    UCHAR syntax;
{
    error(2, "read: unrecognized syntax in readtable - ~d", FIX(syntax));
}

read_token_error( token)
    char *token;
{
    error(2, "read: invalid token - ~S", istring_to_string(token));
}

/* optional 0 4 */
Object lread (input_stream, eof_error_p, eof_value, recursive_p)
    Object input_stream, eof_error_p, eof_value, recursive_p;
{
    Declare_local_temp;
    Object result, temp1, ostream;
    FILE *save_read_fp;
    Object save_read_stream;
    Catch_buf old_buf_1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(input_stream,eof_error_p,eof_value,recursive_p);
    PROTECTI_4(result,temp1,ostream,save_read_stream);
    save_read_fp = Read_fp;
    save_read_stream = Read_stream;
    CATCH(temp1, Kread_eof, old_buf_1, LABEL1);

    MVS_2(chase_input_stream(input_stream),input_stream,ostream);
    if (FILEP(input_stream)) {
	Read_fp = FILE_STREAM_FP(input_stream);
    }
    else if (STRING_INPUT_STREAMP(input_stream)) {
	Read_fp = NULL;
	Read_stream = input_stream;
    }
    else {  /* must be interaction stream */
	Read_fp = INTERACTION_STREAM_FP(input_stream);
    }
    result = reader(input_stream, NIL);
    if (EQ(result, DOT_TOKEN))
	warn(1, "read: dot context error");
    goto LABEL2;

    LABEL1:
    if (UNSUPPLIED_P(eof_value)) eof_value = NIL;
    if (SUPPLIED_P(eof_error_p) && TRUEP(eof_error_p))
	read_eof_error();
    else
	result = eof_value;
    LABEL2:
    END_CATCH(old_buf_1);
    Read_fp = save_read_fp;
    Read_stream = save_read_stream;
    RESTORE_STACK();
    return VALUES_1(result);
}

static Object reader (stream, recursive_p)
    Object stream, recursive_p;
{
    Declare_local_temp;
    register int x, y, z;
    char token[256];
    int tokenlen = 0;
    int colon_position = -1;
    int esc_found = FALSE;
    int subchar;
    UCHAR syntax;
    Object expr, arg, dispatch_func;
    Object temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(stream,recursive_p);
    PROTECTI_3(expr,arg,temp);

    (void)INIT_READER();
    FOREVER {
	x = GETC();
	/* 1. If at EOF, perform EOF processing.  Otherwise, dispatch
	 *	according to steps 2-7
	 */
	if (x == -1) {
	    SI_throw(Kread_eof, NIL);
	}
	syntax = READTABLE_SYNTAX(Readtable)[x];

	/* 2. if x is an illegal character, signal an error */
	if (!syntax) {
	    read_error( x);	/* illegal character */
	}

	/* 3. if x is a whitespace character, then discard it and go
	 *	back to step 1  (What about read-preserving-whitespace?)
	 */
	if (syntax & WHITESPACE) {
	    continue;
	}

	/* 4. if x is a macro character, execute the function associated
	 *	with x (note: the function may return zero or one value)
	 *    if x is a dispatch macro character, execute dispatch function
	 */
	if (syntax & MACRO) {
	    if (syntax & DISPATCH) {
		arg = read_infix_arg(&subchar);
		dispatch_func = ISVREF(READTABLE_DISPATCH(Readtable)[x],
				       subchar);
		if (!TRUEP(dispatch_func))
		    error(2, "read: undefined macro dispatch character - ~C",
			  CHR(subchar));
		expr = (Object)funcall3(dispatch_func, stream, CHR(subchar), arg);
		if (Values_count) {
		    RESTORE_STACK();
		    return expr;
		}
		continue;
	    }
	    else {
	        expr = (Object)funcall2(READTABLE_DISPATCH(Readtable)[x],
				stream, CHR(x));
	        if (Values_count) {
		    RESTORE_STACK();
		    return expr;
		}
	        continue;
	   }
	}

	/* 5. If x is a single escape character (normally \), then read
	 *	the next character and call it y (EOF signals an error).
	 */
	if (syntax & SINGLE_ESC) {
	    y = GETC();
	    if (y == -1)
		SI_throw(Kread_eof, NIL);
	    esc_found = TRUE;
	    token[0] = y;
	    tokenlen = 1;
	    goto STEP8;
	}

	/* 6. If x is a multiple escape character (normally |), then begin
	 *	a token (initially containing no chars) and goto step 9.
	 */
	if (syntax & MULTIPLE_ESC) {
	    esc_found = TRUE;
	    goto STEP9;
	}

	/* 7. If x is a contituent character, then it begins an extended token.
	 *	If x is lowercase, replace it with the corresponding uppercase
	 *	character.  Use x to begin a token and goto step 8.
	 */
	if (syntax & CONSTITUENT) {
	    token[0] = TOUPPER(x);
	    tokenlen = 1;
	    if (x == (int)':') colon_position = 0;	      
	    goto STEP8;
	}
	read_syntax_error( syntax);

	/* 8. accumulate token, an even number of multiple escape characters
	 *	have been encountered.  If at EOF, goto step 10. Otherwise,
	 *	read a character (call it y)
	 */
	STEP8:
	FOREVER {
	    y = GETC();
	    if (y == -1)
		goto STEP10;
	    syntax = READTABLE_SYNTAX(Readtable)[y];
	    if ((syntax & CONSTITUENT) || NON_TERMINATING_MACRO(syntax)) {
		token[tokenlen] = TOUPPER(y);
		if (y == (int)':') colon_position = tokenlen;
		tokenlen++;
	    }
	    else if (syntax & SINGLE_ESC) {
		z = GETC();
		if (z == -1)
		    SI_throw(Kread_eof, NIL);
		/* pretend z is a constituent whose only attr is alphabetic */
		esc_found = TRUE;
		token[tokenlen] = z;
		tokenlen++;
	    }
	    else if (syntax & MULTIPLE_ESC) {
		esc_found = TRUE;
		goto STEP9;
	    }
	    else if (!syntax) {
		read_error( y);
	    }
	    else if (TERMINATING_MACRO(syntax)) {
		UNGETC(y);
		goto STEP10;
	    }
	    else if (syntax & WHITESPACE) {
		UNGETC(y);
		goto STEP10;
	    }
	    else {
		read_syntax_error( syntax);
	    }
	}

	/* 9. A token is being accumulated, and an odd numbero of multiple
	 *	escape characters have been encountered.
	 */
	STEP9:
	FOREVER {
	    y = GETC();
	    if (y == -1)
		SI_throw(Kread_eof, NIL);
	    syntax = READTABLE_SYNTAX(Readtable)[y];
	    if ((syntax & CONSTITUENT) || (syntax & MACRO) ||
		(syntax & WHITESPACE)) {
		token[tokenlen] = y;
		tokenlen++;
	    }
	    else if (syntax & SINGLE_ESC) {
		z = GETC();
		if (z == -1)
		    SI_throw(Kread_eof, NIL);
		/* pretend z is a constituent whose only attr is alphabetic */
		esc_found = TRUE;
		token[tokenlen] = z;
		tokenlen++;
	    }
	    else if (syntax & MULTIPLE_ESC) {
		esc_found = TRUE;
		goto STEP8;
	    }
	    else if (!syntax) {
		read_error( y);
	    }
	    else {
		read_syntax_error( syntax);
	    }
	}

	/* 10. An entire token has been accumulated.  Interpret it as
	 *	representing a Lisp object and return that object as the
	 *	result of the read operation, or signal an error if
	 *	the token is not of legal syntax
	 */
	STEP10:
	token[tokenlen] = '\0';
	if (TRUEP(Read_suppress)) {
	    RESTORE_STACK();
	    return VALUES_1(NIL);
	}
	else if (!esc_found && potential_number(token, tokenlen)) {
            temp = parse_number(token, tokenlen, (int)IFIX(Read_base));
	    RESTORE_STACK();
            return VALUES_1(temp);
	}
	else {
	    RESTORE_STACK();
	    if (!esc_found && !strcmp(token, "."))
		return VALUES_1(DOT_TOKEN);
	    return parse_symbol(token, tokenlen, colon_position);
	}
    }
}

static int read_extended_token (token, tokenlen, esc_found)
    char *token;
    int tokenlen, *esc_found;
{
    int y, z;
    UCHAR syntax;
      
    (void) INIT_READER();
 STEP8:
    FOREVER {
	y = GETC();
	if (y == -1)
	    goto STEP10;
	syntax = READTABLE_SYNTAX(Readtable)[y];
	if ((syntax & CONSTITUENT) || NON_TERMINATING_MACRO(syntax))
	    token[tokenlen++] = TOUPPER(y);
	else if (syntax & SINGLE_ESC) {
	    z = GETC();
	    if (z == -1)
		SI_throw(Kread_eof, NIL);
	    /* pretend z is a constituent whose only attr is alphabetic */
	    *esc_found = TRUE;
	    token[tokenlen++] = z;
	}
	else if (syntax & MULTIPLE_ESC) {
	    *esc_found = TRUE;
	    goto STEP9;
	}
	else if (!syntax) {
	    read_error( y);
	}
	else if (TERMINATING_MACRO(syntax)) {
	    UNGETC(y);
	    goto STEP10;
	}
	else if (syntax & WHITESPACE) {
	    UNGETC(y);
	    goto STEP10;
	}
	else {
	    read_syntax_error( syntax);
	}
    }
    /* 9. A token is being accumulated, and an odd numbero of multiple
     *	escape characters have been encountered.
     */
 STEP9:
    FOREVER {
	y = GETC();
	if (y == -1)
	    SI_throw(Kread_eof, NIL);
	syntax = READTABLE_SYNTAX(Readtable)[y];
	if ((syntax & CONSTITUENT) || (syntax & MACRO) ||
	    (syntax & WHITESPACE)) {
	    token[tokenlen++] = y;
	}
	else if (syntax & SINGLE_ESC) {
	    z = GETC();
	    if (z == -1)
		SI_throw(Kread_eof, NIL);
	    /* pretend z is a constituent whose only attr is alphabetic */
	    *esc_found = TRUE;
	    token[tokenlen++] = z;
	}
	else if (syntax & MULTIPLE_ESC) {
	    *esc_found = TRUE;
	    goto STEP8;
	}
	else if (!syntax) {
	    read_error( y);
	}
	else {
	    read_syntax_error( syntax);
	}
    }

    /* 10. An entire token has been accumulated.  Interpret it as
     *	representing a Lisp object and return that object as the
     *	result of the read operation, or signal an error if
     *	the token is not of legal syntax
     */
 STEP10:
    token[tokenlen] = '\0';
    return tokenlen;
}

static Object read_infix_arg (subchar)
    int *subchar;
{
    Declare_local_temp;
    int y, founddigit = FALSE;
    long num = 0L;

    FOREVER {
	y = GETC();
	if (y == EOF)
	    read_eof_error( );
	if (!isdigit(y)) {
	    *subchar = y;
	    break;
	}
	num = (num * 10L) + (y - '0');
	founddigit = TRUE;
    }
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    if (founddigit)
	return MAKE_INTEGER(num);
    return VALUES_1(NIL);
}

static Object reader_delimited_list (stream, recursive_p, c)
    Object stream, recursive_p;
    int c;
{
    Declare_local_temp;
    register int x;
    int subchar;
    UCHAR syntax;
    Object result = NIL;
    Object expr, arg, dispatch_func;
    char found_dot = FALSE, found_dotcdr = FALSE;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(stream,recursive_p,result);
    PROTECTI_2(expr,arg);

    (void) INIT_READER();
    FOREVER {
	x = GETC();
	/* 1. If at EOF, perform EOF processing.  Otherwise, dispatch
	 *	according to steps 2-7
	 */
	if (x == -1) {
	    read_eof_error( );
	}
	if (x == c) {
	    if (found_dot) {
		if (found_dotcdr) {
		    RESTORE_STACK();
		    return VALUES_1(result);
		}
		else
		    error(1, "read: dot context error");
	    }
	    RESTORE_STACK();
	    return nreverse(result);
	}

	syntax = READTABLE_SYNTAX(Readtable)[x];

	/* 2. if x is an illegal character, signal an error */
	if (!syntax) {
	    read_error( x);	/* illegal character */
	}

	/* 3. if x is a whitespace character, then discard it and go
	 *	back to step 1  (What about read-preserving-whitespace?)
	 */
	else if (syntax & WHITESPACE) {
	    ;
	}

	/* 4. if x is a macro character, execute the function associated
	 *	with x (note: the function may return zero or one value
	 */
	else if (syntax & MACRO) {
	    if (syntax & DISPATCH) {
		arg = read_infix_arg(&subchar);
		dispatch_func = ISVREF(READTABLE_DISPATCH(Readtable)[x],
				       subchar);
		if (!TRUEP(dispatch_func))
		    error(2, "read: undefined macro dispatch character - ~C",
			  CHR(subchar));
		expr = (Object)funcall3(dispatch_func, stream, CHR(subchar), arg);
		if (Values_count)
		    goto USEEXPR;
	    }
	    else {
		expr = (Object)funcall2(READTABLE_DISPATCH(Readtable)[x],
				stream, CHR(x));
		if (Values_count)
		    goto USEEXPR;
	    }
	}

	/* 5. If x is a single escape character (normally \), then read
	 *	the next character and call it y (EOF signals an error).
	 */
	else if ((syntax & CONSTITUENT) ||
		 (syntax & SINGLE_ESC) ||
		 (syntax & MULTIPLE_ESC)) {
	    UNGETC(x);
	    expr = reader(stream, T);
	    USEEXPR:
	    if (found_dotcdr)
		error(1, "read: dot context error");
	    if (EQ(expr, DOT_TOKEN)) {
		if (!result || found_dot)
		    error(1, "read: dot context error");
		found_dot = TRUE;
	    }
	    else if (found_dot) {
	        result = nreverse(result);
	        M_CDR(last(result, KOPT)) = expr;
		found_dotcdr = TRUE;
	    }
	    else {
	        result = cons(expr, result);
	    }
	}
	else {
	    read_syntax_error( READTABLE_SYNTAX(Readtable)[x]);
	}
    }
}

static Object parse_number (token, tokenlen, radix)
    char *token;
    int tokenlen, radix;
{
    register int i = 0;
    int c;
    extern Object read_integer(), read_rational(), read_floating_point();

/* printf("parse_number: token=%s, tokenlen=%d\n", token, tokenlen); */
    /* Start */
    if (i >= tokenlen)
	goto REJECTSTATE;
    c = token[i++];
    if (issign(c))
	goto STATE2;
    if (isbasedigit(c, radix))
	goto STATE3;
    if (isdot(c))
	goto STATE5;
    goto REJECTSTATE;

 STATE2:	/* sign */
    if (i >= tokenlen)
	goto REJECTSTATE;
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE3;
    if (isdot(c))
	goto STATE5;
    goto REJECTSTATE;

 STATE3:	/* [sign] digit+ */
    if (i >= tokenlen)
	return read_integer(token, tokenlen, radix);
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE3;
    if (isdot(c))
	goto STATE4;
    if (ismarker(c))
	goto STATE9;
    if (isratio(c))
	goto STATE6;
    goto REJECTSTATE;

 STATE4:	/* [sign] digit+ . */
    if (i >= tokenlen)
	return read_integer(token, tokenlen, radix);
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE8;
    if (ismarker(c))
	goto STATE9;
    goto REJECTSTATE;

 STATE5:	/* [sign] . */
    if (i >= tokenlen)
	goto REJECTSTATE;
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE8;
    goto REJECTSTATE;

 STATE6:	/* [sign] digit+ / */
    if (i >= tokenlen)
	goto REJECTSTATE;
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE7;
    goto REJECTSTATE;

 STATE7:	/* [sign] digit+ / digit+ */
    if (i >= tokenlen)
	return read_rational(token, tokenlen, radix);
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE7;
    goto REJECTSTATE;

 STATE8:	/* [sign] digit* . digit+ */
    if (i >= tokenlen)
	return read_floating_point(token);
    c = token[i++];
    if (isdigit(c))
	goto STATE8;
    if (ismarker(c))
	goto STATE9;
    goto REJECTSTATE;

 STATE9:	/* ... exponent-marker */
    if (i >= tokenlen)
	goto REJECTSTATE;
    c = token[i++];
    if (issign(c))
	goto STATE10;
    if (isbasedigit(c, radix))
	goto STATE11;
    goto REJECTSTATE;

 STATE10:	/* ... exponent-marker sign */
    if (i >= tokenlen)
	goto REJECTSTATE;
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE11;
    goto REJECTSTATE;

 STATE11:	/* ... exponent-marker [sign] digit+ */
    c = token[i++];
    if (isbasedigit(c, radix))
	goto STATE11;
    if (isend(c)) {
	return read_floating_point(token);
    }

 REJECTSTATE:
    read_token_error( token);

    /* where "..." stands for:
     *	  [sign] digit* . digit+
     * or [sign] digit+ [. digit*]
     */
#ifdef lint
    return NIL;
#endif
	return NULL; //this function return somthing
}

#define isdigitchar(c, iradix)   (digit_char_p(CHR(c), FIX(iradix)))

Object read_integer (token, len, radix)
    char *token;
    int len;
    int radix;
{
    long templong;
    char *scanstring;
    Object result = NIL;
    char c;

#ifdef NEW_BIGNUMS
    /* assume radix <= 16 */
    if (len >= (radix > 10 ? 8 : 9)) {
	Object bignum;
	char *p = token;
	int negative_p = 0;

	if (*p == '+') {
	    ++p;
	    --len;
	} else if (*p == '-') {
	    negative_p = 1;
	    ++p;
	    --len;
	}
	bignum = digit_stream_to_bignum(len,
					read_bignum_producer,
					(bignum_procedure_context) (&p),
					radix,
					negative_p);
	result = xbignum_normalize(bignum);
    }
#else
    if (strlen(token) > (radix > 10 ? 10 : 11))
	warn(1, "read_integer: integer token too long");
#endif
    else {
	if (isdigitchar(c = token[len], radix))
	    /* KLUDGE!  Temporarily store a null at end of substring. */
	    token[len] = '\0';
	else
	    c = '\0';

	switch (radix) {
	case 8:
	    scanstring = "%lo";
	    break;
	default:
	    warn(2, "read_integer: unimplemented radix ~d; substituting 10",
		 FIX(radix));
	    /* Fall through */
	case 10:
	    scanstring = "%ld";
	    break;
	case 16:
	    scanstring = "%lx";
	    break;
	}
	sscanf(token, scanstring, &templong);
	if (c)
	    token[len] = c;
	result = MAKE_INTEGER(templong);
    }
    return result;
}

#ifdef NEW_BIGNUMS
static unsigned int read_bignum_producer (context)
    bignum_procedure_context context;
{
    char **z = (char **)context;
    char digit;
    unsigned int d;

    digit = *(*z)++;
    if (isalpha(digit))
	d = tolower(digit) - 'a';
    else if (isdigit(digit))
	d = digit - '0';
    else
	warn(1, "read_integer: this shouldn't happen");
    return d;
}
#endif

Object read_rational (token, len, radix)
    char *token;
    int len, radix;
{
    char *p;
    Object num, den, result;
    int pos;
    extern Object xmake_canonical_rational();
    Declare_stack_pointer;

    p = strchr(token, '/');
    if (p == NULL)
	return read_integer(token, len, radix);

    SAVE_STACK();
    PROTECTI_3(num, den, result);
    pos = p - token;
    num = read_integer(token, pos, radix);
    ++p;
    den = read_integer(p, len - pos - 1, radix);
    result = xmake_canonical_rational(num, den);
    RESTORE_STACK();
    return result;
}

Object read_floating_point (token)
    char *token;
{
    double tempdouble;

    /*** must handle ALL markers: e,s,f,d,l,E,S,F,D,L ***/
    sscanf(token, "%lf", &tempdouble);
    return cdouble_to_double(tempdouble);
}

static Object parse_symbol (token, tokenlen, colon_position)
    char *token;
    int tokenlen, colon_position;
{
    Object sym, pkg, status;

    if (colon_position == 0) {
	/* intern :xxxxx into keyword package if not a number */
	if (potential_number(&token[1], tokenlen-1))
	    read_token_error( token);
	sym = iintern(&token[1], Qkeyword);

    }
    else if (colon_position > 0) {
	if (token[colon_position-1] == ':') {
	    /* a (possibly internal) symbol ppppp::xxxxx in the ppppp pkg */
	    token[colon_position-1] = '\0';   /* make token_package happy */
	    pkg = token_package(token);
	    sym = iintern(&token[colon_position+1], pkg);
	}
	else {
	    /* an external symbol ppppp:xxxxx in the ppppp package */
	    token[colon_position] = '\0';   /* make token_package happy */
	    pkg = token_package(token);
	    MVS_2(ifind_symbol(&token[colon_position+1], pkg), sym, status);
	    if (!TRUEP(sym))
		error(3, "symbol ~S does not exist in package ~S",
		      istring_to_string(&token[colon_position+1]), pkg);
	    else if (status != Kexternal)
		error(3, "symbol ~S is not external in ~S", sym, pkg);
	}
    }
    else {
	/* intern xxxxx into the current package */
	sym = iintern(token, Package);
    }
    return sym;
}

static Object token_package (token)
    char *token;
{
    Declare_local_temp;
    Object pkg;
    DECLARE_AREA(prev_area); DECLARE_FRONTIER(prev_pos);

    pkg = ifind_package(token);
    if (!pkg) {
	BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
	warn(3, "read: package ~A not found; using ~s instead",
	     istring_to_string(token), Package);
	END_LOCAL_ALLOCATION(prev_area, prev_pos);
	pkg = Package;
    }
    return VALUES_1(pkg);
}

static int potential_number (token, tokenlen)
    char *token;
    int tokenlen;
{
    register int i;
    int prevletter = FALSE, founddigit = FALSE;
    int dotfound = FALSE, alldots = TRUE;
    int c;
    int radix = IFIX(Read_base);

    if (!tokenlen)
	return FALSE;

    c = token[tokenlen-1];
    if (issign(c))
	return FALSE;

    for (i = 0; i < tokenlen; i++) {
	if (token[i] == '.')
	    dotfound = TRUE;
	else
	    alldots = FALSE;
    }
    if (alldots) {
	if (tokenlen > 1)
	    error(1, "read: dot context error");
	else
	    return FALSE;
    }

    c = TOUPPER(token[0]);
    if (!(isdigit(c) || issign(c) || (!dotfound && isletterdigit(c, radix))))
	return FALSE;

    for (; tokenlen; tokenlen--, token++) {
	c = *token;
	if (isdigit(c)) {
	    founddigit = TRUE;
	    prevletter = FALSE;
	}
	else if (issign(c) || (c == '/') || (c == '.') || (c == '^') ||
		(c == '_')) {
	    prevletter = FALSE;
	}
	else if (isalpha(c)) {
	    c = TOUPPER(c);
	    if (!dotfound && isletterdigit(c, radix)) {
		founddigit = TRUE;
	    }
	    else if (ismarker(c)) {
	        if (prevletter || ((tokenlen > 1) && isalpha(*(token+1))))
		    return FALSE;
	    }
	    else {
		return FALSE;
	    }
	    prevletter = TRUE;
	}
    }
    if (!founddigit)
	return FALSE;
    return TRUE;
}    

Object read_preserving_whitespace (input_stream, eof_error_p, eof_value,
				  recursive_p)
    Object input_stream, eof_error_p, eof_value, recursive_p;
{
    if (recursive_p)
	return lread(input_stream, eof_error_p, eof_value, recursive_p);
    /* future release:  preserve the whitespace */
    return lread(input_stream, eof_error_p, eof_value, recursive_p);
}

/* &optional 1 2 */
/*ARGSUSED*/
Object read_delimited_list (ch, input_stream, recursive_p)
    Object ch, input_stream, recursive_p;
{
    /* future release */

    return error(1, "read_delimited_list: not yet implemented");
/*    Object result;
    result = (lread(input_stream, NIL, NIL, recursive_p));
    return result; */
}

/*ARGSUSED*/
static Object dquote_macro_handler(stream, ch)
    Object stream, ch;
{
    Declare_local_temp;
    int x, len = 0;
    char str[513];
    Object newstring;
  
    (void) INIT_READER();
    FOREVER {
	x = GETC();
	if (x == EOF)
	    SI_throw(Kread_eof, NIL);
	if (x == '\"') {
	    str[len] = '\0';
	    newstring = make_string(FIX(len), NIL);
	    MEMCPY(ISTRING(newstring), str, len);
	    return VALUES_1(newstring);
	}
	if (len == 512)
	    error(2, "read: maximum string size (~d) exceeded", FIX(512));
	if (READTABLE_SYNTAX(Readtable)[x] & SINGLE_ESC) {
	    x = GETC();
	    if (x == EOF)
	        SI_throw(Kread_eof, NIL);
	}
	str[len] = x;
	len++;
    }
}

/*ARGSUSED*/
static Object quote_macro_handler(stream, ch)
    Object stream, ch;
{
    return T_VALUES_1(LIST_2(Qquote, reader(stream, T)));
}

/*ARGSUSED*/
static Object oparen_macro_handler(stream, ch)
    Object stream, ch;
{
    return reader_delimited_list(stream, NIL, ')');
}

/*ARGSUSED*/
static Object cparen_macro_handler(stream, ch)
    Object stream, ch;
{
    warn(1, "read: close parenthesis encountered at top level");
    return VALUES_0();
}

/*ARGSUSED*/
static Object semicolon_macro_handler(stream, ch)
    Object stream, ch;
{
    int c;

    FOREVER {
	c = GETC();
	if ((c == EOF) || (c == '\n'))
	    return VALUES_0();	/* return zero values */
    }
}

/*ARGSUSED*/
static Object backquote_macro_handler(stream, ch)
    Object stream, ch;
{
    Object form;

    form = reader(stream, T);
    form = list(2, Qbackquote, form);
    return VALUES_1(form);
}

/*ARGSUSED*/
static Object comma_macro_handler(stream, ch)
    Object stream, ch;
{
 Object handler;
    int c;

    c = GETC();
    if (c == EOF)
	read_eof_error( );
    else {
	if (c != '@' && c != '.') 
	    UNGETC(c);
	handler = reader(stream, T);
	handler = list(2, NIL, handler);
	return SI_comma_macro_handler(c, handler);
    }
	return NULL; //this return somthing
}

/*ARGSUSED*/
static Object labelref_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return warn(1, "#n# is not yet implemented");
}

/*ARGSUSED*/
static Object quote_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    return T_VALUES_1(LIST_2(Qfunction, reader(stream,T)));
}

/*ARGSUSED*/
static Object oparen_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    Object contents, size, initial_elem;

    contents = reader_delimited_list(stream, NIL, ')');
    size = length(contents);
    initial_elem = NIL;
    if (arg != NIL) {
	if (FIXNUM_GT(size, arg))
	    error(1, "read: too many objects in #n(...) form");
	if (FIXNUM_LT(size, arg))
	    initial_elem = CAR(last(contents, KOPT));
	size = arg;
    }
    return make_array(size, T, initial_elem, contents, KOPT, KOPT, KOPT, KOPT);
}

/*ARGSUSED*/
static Object star_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    register SI_Dimension i;
    int esc_found = FALSE;
    char token[256];
    SI_Dimension tokenlen;
    Object size;
    Object result, initial_elem;

    tokenlen = read_extended_token(token, 0, &esc_found);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    if (arg != NIL) {
	if (tokenlen > IFIX(arg))
	    error(1, "read: too many bits in #n*... form");
	if (tokenlen < IFIX(arg))
	    initial_elem = FIX(token[tokenlen-1] - '0');
	size = arg;
    }
    else {
	size = FIX(tokenlen);
	initial_elem = ZERO;
    }
    result = make_array(size, Qbit, initial_elem, 
			KOPT, KOPT, KOPT, KOPT, KOPT);
    for (i = 0; i < tokenlen; i++) {
	if (token[i] == '1')
	    do_setf_aref(result, i, FIX(1L));
	else if (token[i] != '0')
	    error(2, "read: invalid bit in #*... - ~s", CHR(token[i]));
    }
    return VALUES_1(result);
}

check_feature(feat)
    Object feat;
{
    Declare_local_temp;
    Object formcar, temp;

    if (CONSP(feat)) {
	formcar = M_CAR(feat);
	if (EQ(formcar, lreader_Kor)) {
	    for (temp = M_CDR(feat); TRUEP(temp); temp = M_CDR(temp)) {
		if (check_feature(M_CAR(temp)))
		    return TRUE;
	    }
	    return FALSE;
	}
	else if (EQ(formcar, lreader_Kand)) {
	    for (temp = M_CDR(feat); TRUEP(temp); temp = M_CDR(temp)) {
		if (!check_feature(M_CAR(temp)))
		    return FALSE;
	    }
	    return TRUE;
	}
	else if (EQ(formcar, lreader_Knot)) {
	    if (!check_feature(SECOND(feat)))
		return TRUE;
	    return FALSE;
	}
	else {
	    error(2, "read: bad form for #+... - ~s", feat);
	    /*NOTREACHED*/
	}
    }
    else {
	if (TRUEP(member(feat, Features,_,_,_)))
	    return TRUE;
	return FALSE;
    }
	return 0; //return somthing
}

/*ARGSUSED*/
static Object plus_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Object prev_read_suppress;
    Object context;
    int  test;

    context = Package;
    Package = Pkeyword;
    if (feature_init == UNBOUND) INIT_feature_keys();
    test =  (check_feature(reader(stream,T)));
    Package = context;
    if (test) return reader(stream,T);
    prev_read_suppress = Read_suppress;
    Read_suppress = T;
    reader(stream,T);
    Read_suppress = prev_read_suppress;
    return VALUES_0();
}

/*ARGSUSED*/
static Object minus_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Object prev_read_suppress;
    Object context;
    int  test;

    context = Package;
    Package = Pkeyword;
    if (feature_init == UNBOUND) INIT_feature_keys();
    test =  (check_feature(reader(stream,T)));
    Package = context;
    if (!test) return reader(stream,T);

    prev_read_suppress = Read_suppress;
    Read_suppress = T;
    reader(stream,T);
    Read_suppress = prev_read_suppress;
    return VALUES_0();
}

/*ARGSUSED*/
static Object dot_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    return(eval_run(reader(stream,T)));
}

/*ARGSUSED*/
static Object colon_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    int esc_found = FALSE;
    char token[256];

    if (read_extended_token(token, 0, &esc_found))
	return(make_symbol(imake_duplicate_string(token)));
    return VALUES_0();
}

/*ARGSUSED*/
static Object eq_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return warn(1, "#= is not yet implemented");
}

/*ARGSUSED*/
static Object a_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return warn(1, "#A is not yet implemented");
}

/*ARGSUSED*/
static Object c_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return warn(1, "#C is not yet implemented");
}

/*ARGSUSED*/
static Object b_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    int esc_found = FALSE;
    char token[256];
    int tokenlen;

    tokenlen = read_extended_token(token, 0, &esc_found);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return VALUES_1(parse_number(token, tokenlen, 2));
}

/*ARGSUSED*/
static Object o_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    int esc_found = FALSE;
    char token[256];
    int tokenlen;

    tokenlen = read_extended_token(token, 0, &esc_found);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return VALUES_1(parse_number(token, tokenlen, 8));
}

/*ARGSUSED*/
static Object x_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    int esc_found = FALSE;
    char token[256];
    int tokenlen;
 
    tokenlen = read_extended_token(token, 0, &esc_found);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return VALUES_1(parse_number(token, tokenlen, 16));
}

/*ARGSUSED*/
static Object r_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    int esc_found = FALSE;
    char token[256];
    int tokenlen;
 
    tokenlen = read_extended_token(token, 0, &esc_found);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return VALUES_1(parse_number(token, tokenlen, (int)IFIX(arg)));
}

/*ARGSUSED*/
static Object p_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    Object name;
    name = reader(stream, T);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    return parse_namestring(name, KOPT, KOPT, KOPT, KOPT, KOPT);
}

extern Object (*SI_find_structure_constructor_fptr)(/*Object name*/);
extern void  SI_standard_structure_constructor_error(/*Object name*/);

/*ARGSUSED*/
static Object s_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    Object s_form, make_form, key, ctor;

    PROTECT_4(s_form, make_form, key, ctor);

    s_form = reader(stream, T);
    if (TRUEP(Read_suppress))
	return VALUES_1(NIL);
    ctor = (*SI_find_structure_constructor_fptr)(M_CAR(s_form));

    if(!TRUEP(ctor)) 
	SI_standard_structure_constructor_error(M_CAR(s_form));

    for (make_form = NIL,s_form = M_CDR(s_form); CONSP(CDR(s_form));) {
	key = iintern(SI_istring(M_CAR(s_form)), Pkeyword);
	make_form = CONS(key, make_form);
	s_form = M_CDR(s_form);
	make_form = CONS(M_CAR(s_form), make_form);
	s_form = M_CDR(s_form);
    }
    if (TRUEP(s_form))
       error(2, "misformed #s-form: ~s", s_form);
    make_form = nreverse(make_form);
    funcall1(ctor,make_form);

	return NULL; //this function return somthing
}

/*
 * CLtL 1 says to interpret arg as a font number, to become the font
 * attribute of the character object.  This is eliminated by CLtL 2.
 */
/*ARGSUSED*/
static Object backslash_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    Declare_local_temp;
    int esc_found = FALSE;
    char token[256], *p, *q;
    int tokenlen;
    int bits = 0, code;
    Object temp;

    code = GETC();
    if (isalpha(code)) {
	UNGETC(code);
	tokenlen = read_extended_token(token, 0, &esc_found);
	if (TRUEP(Read_suppress))
	    return VALUES_1(NIL);
	if (tokenlen > 1) {
	    p = token;
	    while ((q = strchr(p, '-')) && q[1] != '\0') {
		*q = '\0';
		if (!strcmp(p, "Control")) //stricmp is old function
		    bits |= ICHAR_CONTROL_BIT;
		else if (!strcmp(p, "Meta")) //stricmp is old function
		    bits |= ICHAR_META_BIT;
		else if (!strcmp(p, "Super")) //stricmp is old function
		    bits |= ICHAR_SUPER_BIT;
		else if (!strcmp(p, "Hyper")) //stricmp is old function
		    bits |= ICHAR_HYPER_BIT;
		else {
		    *p = '-';
		    break;
		}
		*q = '-';
		p = q + 1;
	    }
	    if (p[1] == '\0')
		code = p[0];
	    else {
		if ((temp = iname_char(p)) == NIL)
		    return warn(2, "read: unrecognized character - #\\~a",
				istring_to_string(token));
		code = CHR_CODE(temp);
	    }
	}
    }
    return VALUES_1(MAKE_CHR(code, bits));
}

/*ARGSUSED*/
static Object vertbar_dispatch_handler(stream, subchar, arg)
    Object stream, subchar, arg;
{
    int x, y, level = 0;

    FOREVER {
	x = GETC();
	if (x == EOF)
	    read_eof_error();
	if (x == '|') {
	    y = GETC();
	    if (y == EOF)
		read_eof_error();
	    else if (y == '#') {
		if (!level)
		    return VALUES_0();
		level--;
	    }
	    else {
		UNGETC(y);
	    }
	}
	else if (x == '#') {
	    y = GETC();
	    if (y == EOF)
		read_eof_error();
	    else if (y == '|')
		level++;
	    else {
		if (Read_fp)
		    ungetc(y, Read_fp);
		else
		    unread_char(CHR(y), Read_stream);
	    }
	}
    }
}

/* Used by only full printer  */
long SI_requires_escaping_full(iname, len)
    char *iname;
    int len;
{
    int syntax;
    char *p = iname, c;
    UCHAR *syntax_array;

    (void) INIT_READER();
    /* if Readtable doesn't exist, always return FALSE */
    if (!READTABLEP(Readtable)) return FALSE;

    syntax_array = READTABLE_SYNTAX(Readtable);
    if (len == 0 || potential_number(iname, len))
	return TRUE;
    while (c = *p++) {
	if (islower(c))
	    return TRUE;
	syntax = syntax_array[c];
	if (!(syntax & CONSTITUENT))
	    return TRUE;
    }
    return FALSE;
}


/* Readtable support */

static Object make_readtable ()	/* Returns uninitialized readtable */
{
    Declare_local_temp;
    Object syntax_tab, dispatch_tab, new, tab;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECTI_4(syntax_tab, dispatch_tab, tab, new);

    syntax_tab = SI_alloc_primitive_vector(MAXCHARS, A_UNSIGNED_BYTE_8);
    dispatch_tab = SI_alloc_primitive_vector(MAXCHARS, A_T);
    tab = CONS(syntax_tab, dispatch_tab);
    new = SI_ALLOC(SI_Readtable, READTABLE_TYPE, SI_INSTANCE_TAG, SI_NORMAL);
    SI_SET_WRAPPER(new, SI_WRAPPER_readtable);
    READTABLE_ENTRIES(new) = tab;

    RESTORE_STACK();
    return VALUES_1(new);
}


Object copy_readtable (from, to)
    Object from, to;
{
    Declare_local_temp;
    UCHAR *from_syntax, *to_syntax;
    Object from_dispatch_vector, to_dispatch_vector;
    Object from_dispatch, to_dispatch;
    int i,j;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(from,to);
    PROTECTI_1(to_dispatch);


    INIT_READER();
    if (UNSUPPLIED_P(to))
	to = make_readtable();
    if (!SUPPLIEDP(from))
	from = Readtable;

    to_syntax = READTABLE_SYNTAX(to);
    if (from == NIL) {
      for (i = 0; i < MAXCHARS; i++)
	to_syntax[i] = Standard_syntax[MAP(i)];
    }
    else {
      from_syntax = READTABLE_SYNTAX(from);
      for (i = 0; i < MAXCHARS; i++)
	to_syntax[i] = from_syntax[i];
    }

    if (from != NIL)
      from_dispatch_vector = READTABLE_DISPATCH_VECTOR(from);
    to_dispatch_vector = READTABLE_DISPATCH_VECTOR(to);

    for (i = 0; i < MAXCHARS; i++) {
      if ( to_syntax[i] & DISPATCH ) {
	to_dispatch = SI_alloc_primitive_vector(MAXCHARS, A_T);
	if (from == NIL) {
	  initial_readtable_ptr *from_vector = 
	    (initial_readtable_ptr *)(Standard_ptr[MAP(i)]);
	  initial_readtable_ptr from_entry;

	  for (j = 0; j < MAXCHARS; j++) {
	    from_entry = from_vector[MAP(j)];
	    ISVREF(to_dispatch,j) = 
	      ((EMPTY == from_entry) ?
	       NIL : 
	       MAKE_FUNCTION(from_entry, NIL, FALSE, 3, 3));
	  }
	}
	else {
	  from_dispatch = ISVREF(from_dispatch_vector,i);
	  for (j = 0; j < MAXCHARS; j++)
	    ISVREF(to_dispatch,j) = ISVREF(from_dispatch,j);
	}
      }
      else if (from == NIL) 
	to_dispatch = 
	  ((EMPTY == Standard_ptr[MAP(i)]) ?
	   NIL : 
	   MAKE_FUNCTION(Standard_ptr[MAP(i)], NIL, FALSE, 2, 2));
      else
	to_dispatch = ISVREF(from_dispatch_vector,i);

      ISVREF(to_dispatch_vector,i) = to_dispatch;
    }

    RESTORE_STACK();
    return VALUES_1(to);
}

Object readtablep (obj)
    Object obj;
{
    Declare_local_temp;
    return VALUES_1(READTABLEP(obj) ? T : NIL);
}

Object set_syntax_from_char (tochar, fromchar, to, from)
    Object tochar, fromchar, to, from;
{
    UCHAR *from_syntax, *to_syntax;
    Object *from_dispatch, *to_dispatch;
    Declare_local_temp;
 
    (void) INIT_READER();
    if (UNSUPPLIED_P(to))
	to = Readtable;
    if (UNSUPPLIED_P(from))
	from = STANDARD_READTABLE();

    from_syntax = READTABLE_SYNTAX(from);
    from_dispatch = READTABLE_DISPATCH(from);
    to_syntax = READTABLE_SYNTAX(to);
    to_dispatch = READTABLE_DISPATCH(to);
    to_syntax[ICHAR_CODE(tochar)] = from_syntax[ICHAR_CODE(fromchar)];
    to_dispatch[ICHAR_CODE(tochar)] = from_dispatch[ICHAR_CODE(fromchar)];

    return VALUES_1(T);
}

Object get_macro_character (ch, readtable)
    Object ch, readtable;
{
    int c;
    Object nonterm_p;
    Object function;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(readtable);

    (void) INIT_READER();
    
    if (!SUPPLIEDP(readtable)) readtable = Readtable;

    if (readtable == NIL)
	readtable = STANDARD_READTABLE();

    c = CHR_CODE(ch);
    function = READTABLE_DISPATCH(readtable)[c];
    nonterm_p = ((function != NIL) &&
		 (READTABLE_SYNTAX(readtable)[c] & TERMINATING)) ?
		   T : NIL;
    RESTORE_STACK();
    return VALUES_2(function, nonterm_p);
}

Object set_macro_character (ch, function, nonterm_p, readtable)
    Object ch, function, nonterm_p, readtable;
{
    Declare_local_temp;
    int c;

    (void) INIT_READER();
    if (UNSUPPLIED_P(nonterm_p)) nonterm_p = NIL;
    if (UNSUPPLIED_P(readtable)) readtable = Readtable;

    if (TRUEP(function) && SYMBOLP(function))
      function = SYMBOL_FUNCTION(function);
    c = CHR_CODE(ch);
    READTABLE_SYNTAX(readtable)[c] = 
      MACRO | (TRUEP(nonterm_p) ? 0 : TERMINATING);
    READTABLE_DISPATCH(readtable)[c] = function;
    return VALUES_1(T);
}

Object get_dispatch_macro_character (disp_char, sub_char, readtable)
    Object disp_char, sub_char, readtable;
{
    Declare_local_temp;
    Object dispatch, function;
    int dispc, subc;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(readtable);

    if (!SUPPLIEDP(readtable)) readtable = Readtable;

    if (readtable == NIL)
	readtable = STANDARD_READTABLE();

    dispc = CHR_CODE(disp_char);
    subc = CHR_CODE(sub_char);

/* should add error check for table and dispatch table */

    dispatch = READTABLE_DISPATCH(readtable)[dispc];
    function = ISVREF(dispatch,subc);

    RESTORE_STACK();
    return VALUES_1(function);
}

Object set_dispatch_macro_character (disp_char, sub_char, function, readtable)
    Object disp_char, sub_char, function, readtable;
{
    Declare_local_temp;
    int dispc, subc;

    if (UNSUPPLIED_P(readtable)) readtable = Readtable;
    /* must add error check for table and dispatch table */

    dispc = CHR_CODE(disp_char);
    subc = CHR_CODE(sub_char);
    if (TRUEP(function) && SYMBOLP(function))
      function = SYMBOL_FUNCTION(function);
    ISVREF(READTABLE_DISPATCH(readtable)[dispc],subc) = function;
    return VALUES_1(T);
}

void SI_INIT_reader() {
    (void)INIT_READER();
}

static void INIT_feature_keys()
{

    lreader_Kand = NEW_SYMBOL(Pkeyword,"AND",TRUE);
    lreader_Kor = NEW_SYMBOL(Pkeyword,"OR",TRUE);
    lreader_Knot = NEW_SYMBOL(Pkeyword,"NOT",TRUE);

    feature_init = NIL; /* done */

}
