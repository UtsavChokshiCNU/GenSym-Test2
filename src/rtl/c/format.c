/*
   format.c - LISPTOC Format/Write functions
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object Kcapitalize;
extern Object Kdowncase;
extern Object Kupcase;
DECLARE_VARIABLE(Print_array);
DECLARE_VARIABLE(Print_base);
DECLARE_VARIABLE(Print_case);
DECLARE_VARIABLE(Print_circle);
DECLARE_VARIABLE(Print_escape);
DECLARE_VARIABLE(Print_gensym);
DECLARE_VARIABLE(Print_length);
DECLARE_VARIABLE(Print_level);
DECLARE_VARIABLE(Print_pretty);
DECLARE_VARIABLE(Print_radix);
DECLARE_VARIABLE(Print_readably);
extern Object Qforeign_type;
extern TLS SI_Catch_frame *SI_Catch_stack;
#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern TLS SI_Special_frame *SI_Special_stack;
DECLARE_VARIABLE(Standard_output);
#include <math.h>

#ifndef Platform_Windows
# define _strupr strupr
# define _strlwr strlwr
# include <inttypes.h>
#endif

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);
extern char *SI_istring(Object o);
extern long SI_re_throw(void);
extern char *SI_string_base(Object o);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object (*SI_warn_fptr) (int n, char *lstr, ...);
extern Object adjust_array(Object array, Object new_dimensions, Object element_type, Object initial_element, Object initial_contents, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object array_dimensions(Object);
extern Object array_element_type(Object);
extern Object chase_write_stream(Object stream);
extern Object do_aref_1(Object arr, long i);
extern Object eql(Object,Object);
extern long ilength(Object sequence);
extern Object istring_to_string(char *istring);
extern char *isymbol_name(Object sym);
extern Object make_string(Object size, Object initial_element);
extern double object_to_cdouble(Object n);
extern Object setf_fill_pointer(Object arr, Object fillptr);
extern char *strlwr(char *str);
extern char *strupr(char *str);
extern Object type_of(Object);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_internal_funcall();
extern char *SI_istring();
extern int SI_re_throw();
extern char *SI_string_base();
extern Object SI_symbol_field();
extern Object (*SI_warn_fptr) ();
extern Object adjust_array();
extern Object array_dimensions();
extern Object array_element_type();
extern Object chase_write_stream();
extern Object do_aref_1();
extern Object eql();
extern long ilength();
extern Object istring_to_string();
extern char *isymbol_name();
extern Object make_string();
extern double object_to_cdouble();
extern Object setf_fill_pointer();
extern char *strlwr();
extern char *strupr();
extern Object type_of();

#endif

#include "bigext.h"

#include "format.h"

#if SI_SUPPORT_CLOS

#define print_object(a0,a1) \
    GENERIC_FUNCTION_CALL_2(Fprint_object,a0,a1)
#define Fprint_object SYMBOL_FUNCTION(Qprint_object)
extern TLS Object SI_Called_function;
extern Object SI_symbol_field();
extern Object Qprint_object;
extern SI_Primitive_vector_constant SI_Stack_vector_header;

#endif

/* Thread-Local Storage. binghe, 2009/4/18 */
static TLS char *Work;
static TLS long Worklen;
DEFINE_STATIC_VARIABLE(Object, Current_print_level, ZERO);

DECLARE_VARIABLE(SI_Format_stream);
extern long (*SI_requires_escaping_fptr)();
extern Object (*SI_find_structure_print_function_fptr)(/*name*/);

/* Forward references */
static void prints();
static long do_format_1();
static void prints_str();
static void prints_string(), prints_number(), prints_double();
static void prints_bignum();
static void prints_structure();
static void flush_work();
static void lwrite_get_space();
static void do_format_get_space();
FORWARD_STATIC void print_bignum_consumer();

#if SI_USE_PROTOTYPES

extern Object do_format(long nvar, Object stream, char *lstr,
			Stack_item_ptr vargs);

#else

extern Object do_format();

#endif

static char *Stream_types[] = {
    "AUX-STREAM",
    "BROADCAST-STREAM",
    "CONCATENATED-STREAM",
    "ECHO-STREAM",
    "FILE-STREAM",
    "SYNONYM-STREAM",
    "TWO-WAY-STREAM",
    "STRING-INPUT-STREAM",
    "STRING-OUTPUT-STREAM",
    "INTERACTION-STREAM"
};

Object lwrite (object, stream, pescape, pradix, pbase, pcircle, ppretty,
	       plevel, plength, pcase, pgensym, parray)
    Object object;
    Object stream, pescape, pradix, pbase, pcircle, ppretty, plevel, plength;
    Object pcase, pgensym, parray;
{
    Declare_special(10);
    Declare_protect(1);
    Object newstream;
    long bound_specials;

    PROTECT_LOCALS();
    PROTECT_1(object);

    /* Re-bind all the printer control variables. */
    SI_PUSH_SPECIAL_DFLTD(Print_escape, pescape, 0);
    SI_PUSH_SPECIAL_DFLTD(Print_radix, pradix, 1);
    SI_PUSH_SPECIAL_DFLTD(Print_base, pbase, 2);
    SI_PUSH_SPECIAL_DFLTD(Print_circle, pcircle, 3);
    SI_PUSH_SPECIAL_DFLTD(Print_pretty, ppretty, 4);
    SI_PUSH_SPECIAL_DFLTD(Print_level, plevel, 5);
    SI_PUSH_SPECIAL_DFLTD(Print_length, plength, 6);
    SI_PUSH_SPECIAL_DFLTD(Print_case, pcase, 7);
    SI_PUSH_SPECIAL_DFLTD(Print_gensym, pgensym, 8);
    SI_PUSH_SPECIAL_DFLTD(Print_array, parray, 9);
    /* *** There are missing printer control variables from ANSI */
    bound_specials = 10;

    newstream = chase_write_stream(stream);

    if (newstream != SI_Format_stream) 
        lwrite_get_space(object,newstream);
    else
	prints(object);

    /* Restore all the printer control variables. */
    while (bound_specials--) POP_SPECIAL();
    UNPROTECT_LOCALS();
    return VALUES_1(object);
}

static void lwrite_get_space(object, newstream)
     Object object;
     Object newstream;
{
    Declare_special(2);
    Declare_catch(1);
    char *savework;
    long saveworklen;
    char workspace[MAXFMTSTR+10];

    PUSH_SPECIAL(SI_Format_stream, newstream, 0);
    PUSH_SPECIAL(Current_print_level, ZERO, 1);
    saveworklen = Worklen;
    savework = Work;
    if (PUSH_UNWIND_PROTECT(0)) {
      Work = workspace;
      Work[0] = Work[MAXFMTSTR] = '\0';
      Worklen = 0;
      prints(object);
      flush_work();
    }
    POP_UNWIND_PROTECT(0);
    Worklen = saveworklen;
    Work = savework;
    CONTINUE_UNWINDING(0);
    POP_SPECIAL();
    POP_SPECIAL();
}

static void flush_work()
{
    register long i;
    char *dst, *src;
    Object oldstr, fillptr, needed_size, total_size, avail_size;
    Declare_stack_pointer;

    if (STREAMP(SI_Format_stream)) {
	switch(STREAM_STYPE(SI_Format_stream)) {
	case INTERACTION_STREAM:
	    fwrite(Work, Worklen, 1, INTERACTION_STREAM_FP(SI_Format_stream));
	    fflush(INTERACTION_STREAM_FP(SI_Format_stream));
	    break;
	case FILE_STREAM:
	    fwrite(Work, Worklen, 1, FILE_STREAM_FP(SI_Format_stream));
	    fflush(FILE_STREAM_FP(SI_Format_stream));
	    break;
	case STRING_OUTPUT_STREAM:
	    SAVE_STACK();
	    PROTECT_3(oldstr,fillptr,needed_size);
	    PROTECTI_2(total_size, avail_size);
	    oldstr = STREAM_OBJ(SI_Format_stream);
	    fillptr = SI_GENERAL_VECTOR_FILL_POINTER(oldstr);
	    needed_size = FIX(Worklen);
	    total_size = FIX(SI_GENERAL_VECTOR_TOTAL_SIZE(oldstr));
	    avail_size = FIXNUM_MINUS(total_size, fillptr);
	    if (FIXNUM_LT(avail_size, needed_size)) {
		oldstr = adjust_array(oldstr,
		  FIXNUM_ADD(total_size, FIXNUM_MAX(needed_size,FIX(128))),
		  KOPT, KOPT, KOPT, KOPT, KOPT, KOPT);
	    }
	    dst = (char *) (ISTRING(oldstr)+IFIX(fillptr));
	    src = (char *) Work;
	    for (i = 0; i < Worklen; i++)
		*dst++ = *src++;
	    setf_fill_pointer(oldstr, FIXNUM_ADD(fillptr, needed_size));
	    RESTORE_STACK();
	    break;
	default:
	    error(2, "unknown stream type - ~s", SI_Format_stream);
	}
    }
    else {
	error(2, "invalid stream - ~s", SI_Format_stream);
    }
    Work[0] = '\0';
    Worklen = 0;
}
 
Object write_to_string (object, pescape, pradix, pbase, pcircle, ppretty,
			plevel, plength, pcase, pgensym, parray)
    Object object;
    Object pescape, pradix, pbase, pcircle, ppretty, plevel, plength;
    Object pcase, pgensym, parray;
{
    Declare_local_temp;
    Declare_special(12);
    Declare_catch(1);
    Declare_protect(1);

    Object newstring;
    char *savework, *str;
    long saveworklen;
    char workspace[MAXFMTSTR+10];
    long bound_specials;

    PROTECT_LOCALS();
    PROTECTI_1(newstring);

    /* Re-bind all the printer control variables. */
    SI_PUSH_SPECIAL_DFLTD(Print_escape, pescape, 0);
    SI_PUSH_SPECIAL_DFLTD(Print_radix, pradix, 1);
    SI_PUSH_SPECIAL_DFLTD(Print_base, pbase, 2);
    SI_PUSH_SPECIAL_DFLTD(Print_circle, pcircle, 3);
    SI_PUSH_SPECIAL_DFLTD(Print_pretty, ppretty, 4);
    SI_PUSH_SPECIAL_DFLTD(Print_level, plevel, 5);
    SI_PUSH_SPECIAL_DFLTD(Print_length, plength, 6);
    SI_PUSH_SPECIAL_DFLTD(Print_case, pcase, 7);
    SI_PUSH_SPECIAL_DFLTD(Print_gensym, pgensym, 8);
    SI_PUSH_SPECIAL_DFLTD(Print_array, parray, 9);
    /* *** There are missing printer control variables from ANSI */

    PUSH_SPECIAL(SI_Format_stream, NIL, 10);
    PUSH_SPECIAL(Current_print_level, ZERO, 11);
    bound_specials = 12;

    saveworklen = Worklen;
    savework = Work;
    if (PUSH_UNWIND_PROTECT(0)) {
	Work = workspace;
	Work[0] = Work[MAXFMTSTR] = '\0';
	Worklen = 0;
	prints(object);
	newstring = make_string(FIX(Worklen), KOPT);
	str = &SI_ISCHAR(newstring, 0);
	MEMCPY(str, Work, (SI_Size_type)SI_PRIMITIVE_VECTOR_LENGTH(newstring));
    }
    POP_UNWIND_PROTECT(0);
    Worklen = saveworklen;
    Work = savework;
    CONTINUE_UNWINDING(0);

    /* Restore all the bound specials. */
    while (bound_specials--) POP_SPECIAL();
    UNPROTECT_LOCALS();
    return VALUES_1(newstring);
}

static void prints_ch (ch)
    char ch;
{
    if (Worklen < MAXFMTSTR) {
	Work[Worklen] = ch;
	Worklen++;
	Work[Worklen] = '\0';
	if (TRUEP(SI_Format_stream)) {
	    if ((ch == '\n') || (ch == '\r'))
	        STREAM_CURRPOS(SI_Format_stream) = 0;
	    else
	        STREAM_CURRPOS(SI_Format_stream) += 1;
	}
    }
}

static void prints_character (c)
    Object c;
{
    long bits = ICHAR_BITS(c),
	code = ICHAR_CODE(c);
    char buffer[256];
    char *p = buffer;
    extern long ichar_name();

    p[0] = '\0';

    if (bits & ICHAR_CONTROL_BIT)
	strcat(p, "Control-");
    if (bits & ICHAR_META_BIT)
	strcat(p, "Meta-");
    if (bits & ICHAR_SUPER_BIT)
	strcat(p, "Super-");
    if (bits & ICHAR_HYPER_BIT)
	strcat(p, "Hyper-");

    p = &buffer[strlen(buffer)];
    if (ichar_name(CHR(code), p) < 0) {
	p[0] = (char)code; //add "(char)" mayby lost data
	p[1] = '\0';
    }

    prints_str(buffer, strlen(buffer));
}

static void prints_str(str, len)
    char *str;
    long len;
{
    if ((Worklen + len) <= MAXFMTSTR) {
	MEMCPY(&Work[Worklen], str, (SI_Size_type)len);
	Worklen += len;
	if (TRUEP(SI_Format_stream))
	    STREAM_CURRPOS(SI_Format_stream) += (short)len; //add "(short)" maby lost date
    }
}

static void prints_addr(arg)
    Object arg;
{
    char tempbuf[50];

#ifdef MSDOS
    sprintf(tempbuf, "%x:%x", FP_SEG(arg), FP_OFF(arg));
#else
    sprintf(tempbuf, "%lx", (long) arg);
#endif
    prints_ch(' ');
    prints_str(tempbuf, strlen(tempbuf));
}
	
static void prints_name(str, len)
    char *str;
    long len;
{
    if ((Worklen + (len-1)) < MAXFMTSTR) {
	strcpy(&Work[Worklen], str);
	if (EQ(Print_case, Kupcase));
	else if (EQ(Print_case, Kdowncase))
	  _strlwr(&Work[Worklen]); //strlwr is old function
	else if (EQ(Print_case, Kcapitalize))
	  {char *p = &Work[Worklen];
	   int beginflag = TRUE;
	   char c;

	   while ('\0' != (c = *p)) {
	     if (isalnum(c)) {
	       if (beginflag) {
		 *p = TOUPPER(c);
		 beginflag = FALSE;
	       }
	       else
		 *p = TOLOWER(c);
	     }
	      else
		beginflag = TRUE;
	     p++;
	   }
	 }
	Worklen += len;
	if (TRUEP(SI_Format_stream))
	    STREAM_CURRPOS(SI_Format_stream) += (short)len; //add "(short)" maby lost date
    }
}

static void prints_symbol_name (iname)
     char *iname;
{
    size_t len = strlen(iname);

    if (TRUEP(Print_escape) && (*SI_requires_escaping_fptr)(iname, len)) {
	     prints_ch('|');
	     prints_str(iname, len);
	     prints_ch('|');
     } else
	prints_name(iname, len);
}

static void prints (arg)
    Object	arg;
{
    Declare_local_temp;
    Declare_special(1);
    long	stype;
    char *iname, tempbuf[50];
    long i, bitlen, arrlen;
    Object temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(arg);
    PROTECTI_1(temp);
    if (FIXNUMP(Print_level) && FIXNUM_PLUSP(Print_level) &&
	FIXNUM_GT(Current_print_level, Print_level)) {
	prints_ch('#');
	RESTORE_STACK();
	return;
    }
    PUSH_SPECIAL(Current_print_level, FIXNUM_ADD1(Current_print_level), 0);

    if (SI_IMMEDIATEP(arg)) {
	if (arg == NIL)
	    prints_name("NIL", 3);
	else if (FIXNUMP(arg))
	    prints_number(arg, (int)IFIX(Print_base));
	else if (CHARACTERP(arg)) {
	    if (TRUEP(Print_escape)) {
		prints_str("#\\", 2);
		prints_character(arg);
	    }
	    else
		prints_ch(ICHAR_CODE(arg));
	} else if (arg == UNBOUND)
	    prints_str("#<Unbound>", 10);
	else {
	    sprintf(tempbuf, "#<Immediate %lx>", (long) arg);
	    prints_str(tempbuf, strlen(tempbuf));
	}
    }
    else if (ARRAYP(arg)) {
	if (!VECTORP(arg)) {
	    if (SIMPLE_ARRAY_P(arg))
		prints_str("#<Simple-Array ", 15);
	    else
		prints_str("#<Array ", 8);
	    prints(array_element_type(arg));
	    prints_ch(' ');
	    prints(array_dimensions(arg));
	    prints_ch('>');
	} else if (STRINGP(arg)) {
	    if (TRUEP(Print_escape))
		prints_string(arg);
	    else {
		iname = ISTRING(arg);
		prints_str(iname, strlen(iname));
	    }
	} else if (BIT_VECTOR_P(arg)) {
	    prints_str("#*", 2);
	    bitlen = ilength(arg);
	    for (i = 0; i < bitlen; i++)
		prints(do_aref_1(arg, (i)));
	} else if (TRUEP(Print_array)) {
	    prints_str("#(", 2);
	    arrlen = ilength(arg);
	    for (i = 0; i < arrlen; i++) {
		prints(do_aref_1(arg, i));
		if (i < (arrlen-1))
		    prints_ch(' ');
	    }
	    prints_ch(')');
	} else {
	    /* Simple-vector would be misleading, since that implies
	       element type T *** that's not correct (ex: fixnum) */
	    if (SIMPLE_ARRAY_P(arg))
		prints_str("#<Simple-Vector ", 16);
	    else 
		prints_str("#<Vector ", 9);
	    prints(array_element_type(arg));
	    prints_ch(' ');
	    prints(array_dimensions(arg));
	    prints_ch('>');
	}
    } else if (SYMBOLP(arg)) {
	switch (ISYMBOL_TYPE(arg)) {
	case USYMBOL_TYPE:
	    temp = USYMBOL_NAME(arg);
	    iname = ISTRING(temp);
	    if (TRUEP(Print_escape))
		prints_str("#:", 2);
	    prints_symbol_name(iname);
	    break;
	case KEYWORD_TYPE:
	case MKEYWORD_TYPE:
	    if (TRUEP(Print_escape))
		prints_ch(':');
	    prints_symbol_name(isymbol_name(arg));
	    break;
	default:
	    prints_symbol_name(isymbol_name(arg));
	    break;
	}
    } else {
	switch(SI_STORED_OBJECT_TYPE(arg)) {
	case CONS_TYPE:
	    prints_ch('(');
	    while(CONSP(arg)) {
		prints(M_CAR(arg));
		if (M_CDR(arg) != NIL)
		    prints_ch(' ');
		arg = M_CDR(arg);
	    }
	    if (arg != NIL) {
		prints_str(". ", 2);
		prints(arg);
	    }
	    prints_ch(')');
	    break;
	case OBIGNUM_TYPE:
	case XBIGNUM_TYPE:
        case LONG64_TYPE:
	    prints_number(arg, (int)IFIX(Print_base));
	    break;
	case DOUBLE_TYPE:
	    {
	      double darg = IDOUBLE(arg);
	      double abs_darg = ABS(darg);
	      if(abs_darg == 0.0 || 
		 (1e-3 <= abs_darg && abs_darg <= 1e7))
		prints_double(arg, "%f");
	      else
		prints_double(arg, "%e");
	    }
	    break;
	case RATIO_TYPE:
	    prints_number(RATIO_NUMERATOR(arg), (int)IFIX(Print_base));
	    prints_ch('/');
	    prints_number(RATIO_DENOMINATOR(arg), (int)IFIX(Print_base));
	    break;
	case COMPLEX_TYPE:
	    prints_str("#C(", 3);
	    prints_number(COMPLEX_REAL(arg), (int)IFIX(Print_base));
	    prints_ch(' ');
	    prints_number(COMPLEX_IMAG(arg), (int)IFIX(Print_base));
	    prints_ch(')');
	    break;

	case SI_FUNCTION_TYPE:
#if SI_SUPPORT_CLOS
	    if (SI_FUNCTION_GENERIC_P(arg)) {
		print_object(arg, SI_Format_stream);
		break;
	    }
#endif /* SI_SUPPORT_CLOS */

#ifdef MSDOS
	    sprintf(tempbuf, "#<Function %x:%x>",
		    FP_SEG(IFUNC(arg)),
		    FP_OFF(IFUNC(arg)));
#else
	    sprintf(tempbuf, "#<Function %lx>",
		    (long) IFUNC(arg));
#endif /* MSDOS */
	    prints_str(tempbuf, strlen(tempbuf));
	    break;

	case SI_STRUCTURE_TYPE:
	    if(FOREIGN_TYPE_P(arg)) {
	      prints_str("#<Foreign-Type ", 15);
	      prints(FOREIGN_TYPE_NAME(arg));
	      prints_addr(arg);
	      prints_ch('>');
	    }
	    else
	      prints_structure(arg);
	    break;
	case PACKAGE_TYPE:
	    prints_str("#<Package ", 10);
	    prints_str(PACKAGE_NAME(arg), strlen(PACKAGE_NAME(arg)));
	    prints_addr(arg);
	    prints_ch('>');
	    break;
	case HASH_TABLE_TYPE:
	    prints_str("#<Hash-Table", 12);
	    prints_addr(arg);
	    prints_ch('>');
	    break;
	case RANDOM_STATE_TYPE:
	    prints_str("#<Random-State", 14);
	    prints_addr(arg);
	    prints_ch('>');
	    break;
	case READTABLE_TYPE:
	    prints_str("#<Readtable", 11);
	    prints_addr(arg);
	    prints_ch('>');
	    break;
	case PATHNAME_TYPE:
	    if (TRUEP(Print_escape))
		prints_str("#P", 2);
	    prints(PATHNAME_PATH(arg));
	    break;
	case STREAM_TYPE:
	    prints_str("#<Stream ", 9);
	    stype = (STREAM_STYPE(arg) >> 4) & 0xf;
	    prints_str(Stream_types[stype], strlen(Stream_types[stype]));
	    prints_addr(arg);
	    prints_ch('>');
	    break;
#if SI_SUPPORT_THREAD
	case SI_THREAD_TYPE:
	    prints_str("#<Thread \"", 10);
	    prints(SI_THREAD_NAME(arg));
	    prints_ch('\"');
	    prints_addr(arg);
	    prints_ch('>');
	    break;
        case SI_LOCK_TYPE:
	    prints_str("#<Lock \"", 8);
	    prints(SI_LOCK_NAME(arg));
	    prints_ch('\"');
	    prints_addr(arg);
	    prints_ch('>');
	    break;
#endif
	case COBJECT_TYPE:
	    prints_str("#<Foreign-Pointer", 17);
	    prints_addr((Object)FOREIGN_POINTER_ADDRESS(arg));
	    prints_ch(' ');
	    if(FOREIGN_TYPE_P(FOREIGN_POINTER_TYPE(arg))) {
	      prints(FOREIGN_TYPE_NAME(FOREIGN_POINTER_TYPE(arg)));
	    }
	    prints_ch('>');
	    break;
	case WINDOW_TYPE:
	    sprintf(tempbuf, "#<Window %d %d %d %d>",
		    SI_UNTAG_WINDOW(arg)->left,
		    SI_UNTAG_WINDOW(arg)->top,
		    SI_UNTAG_WINDOW(arg)->height,
		    SI_UNTAG_WINDOW(arg)->width);
	    prints_str(tempbuf, strlen(tempbuf));
	    break;
	default:
#if SI_SUPPORT_CLOS
	    print_object(arg, SI_Format_stream);
	    break;
#else
	    sprintf(tempbuf, "#<Random %lx type=%d>",
		    (long) arg, SI_STORED_OBJECT_TYPE(arg));
	    prints_str(tempbuf, strlen(tempbuf));
	    break;
#endif /* SI_SUPPORT_CLOS */
	}
    }
    POP_SPECIAL();		/* Current_print_level */
    RESTORE_STACK();
}

static void prints_structure(arg)
  Object arg;
{ Declare_protect(1);
  Object func;

  PROTECT_LOCALS();
  PROTECT_1(arg);

  func = (*SI_find_structure_print_function_fptr)(arg);

  UNPROTECT_LOCALS();
  FUNCALL_3(func, arg, SI_Format_stream, Current_print_level);
}

#if 0
static void prints_structure(arg)
    Object arg;
{
    Object struct_name = SI_STRUCTURE_NAME(arg);
    Object func;
 /* int i, size; */

    if (TRUEP(func = get(struct_name, Qprint_function, NIL))) {
	/*
	  -- This isn't needed, because the entire PRINT does
	     local allocation...
	  BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
	  struct_arg = FUNCALL_3(func,
	      arg,NIL,Current_print_level);
	  prints_str(ISTRING(struct_arg), ISSIZE(struct_arg));
	  END_LOCAL_ALLOCATION(prev_area, prev_pos);
	  */
	FUNCALL_3(func, arg, SI_Format_stream, Current_print_level);
    }
    else {
	prints_str("#S(", 3);
	prints(struct_name);
	prints_str(" ...)", 5);

     /* Old crufty version.  Do this properly later.
	size = SI_STRUCTURE_SIZE(arg);
	for (i = 0; i < size; i++) {
	    prints_ch(' ');
	    prints(STRUCTURE_ELEMENT(arg, i));
	}
	prints_ch(')');
      */
    }
}
#endif

static void prints_string(arg)
    Object arg;
{
    long len = SI_VECTOR_LENGTH(arg);
    char *p = SI_string_base(arg);
    char *end = p + len;
    char *q;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(arg);

    prints_ch('\"');
    while ((q = strpbrk(p, "\"\\")) != NULL && q < end) {
	prints_str(p, q - p);
	prints_ch('\\');
	prints_ch(*q);
	p = q + 1;
    }
    prints_str(p, end - p);
    prints_ch('\"');

    RESTORE_STACK();
} 

static void prints_number(arg, base)
    Object arg;
    int base;
{
#   define PRINTS_NUMBER_LENGTH 100    
    char buf[PRINTS_NUMBER_LENGTH];
    int etype = 0;
    SI_int64 n;
    char *fmt;
    Declare_stack_pointer;

    buf[0] = '\0';
    if (FIXNUMP(arg)) {
	n = IFIX(arg);
PRINT_LONG:
	switch(base) {
#ifdef Platform_Windows
	case 8:  fmt = "%I64o"; break;
	case 16: fmt = "%I64x"; break;
	case 10: fmt = "%I64d"; break;
#else
	case 8:  fmt = "%" PRIo64; break;
	case 16: fmt = "%" PRIx64; break;
	case 10: fmt = "%" PRId64; break;
#endif
	default:
	    {	int digit;
		int i= PRINTS_NUMBER_LENGTH;
		int minusp = n<0;
		
		buf[--i] = '\0';
		if (minusp) n = -n;
		do {
		    digit  =  n % base;
		    n /= base;
		    buf[--i]= (digit > 9 ? 'a'-10 : '0' ) + digit;
		} while(n) ;
		if (minusp) buf[--i]='-';
		prints_str(buf+i, strlen(buf+i));
		return;
	    }
	}
	sprintf(buf, fmt, n); 
	prints_str(buf, strlen(buf));
    } else {
	SAVE_STACK();
	PROTECT_1(arg);
        etype = SI_STORED_OBJECT_TYPE(arg);
	switch(etype) {
	case XBIGNUM_TYPE:
	    prints_bignum(arg, base);
	    return;
	case DOUBLE_TYPE:
	    sprintf(buf, "%f", IDOUBLE(arg));
	    break;
        case LONG64_TYPE:
            n = ILONG64(arg);
            goto PRINT_LONG;
	case OBIGNUM_TYPE:
	    n = BIGNUM_VALUE(arg);
	    goto PRINT_LONG;
	default:
	    sprintf(buf, "#<Non-number %lx>", (long) arg);
	    break;
	}
	RESTORE_STACK();
	prints_str(buf, strlen(buf));
    }
}

static void prints_bignum(n, base)
    bignum_type n;
    int base;
{
    double log_2 = (base == 10 ? 0.3010300 : (log(2.0) / log((double) base)));
    SI_Ulong buffer_size;
    char *buffer, *p, *end;
    SI_Long len;
    Object temp_string;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(n);

    len = bignum_length_in_bits(n);
    buffer_size = (unsigned long)(len * log_2) + 2; //add "(unsigned long)" maby lost date

    temp_string = make_string(FIX(buffer_size), NIL);
    buffer = ISTRING(temp_string);
    if (buffer == NULL) {
	warn(1, "not enough memory to print bignum");
	return;
    }
    p = end = buffer + (buffer_size - 1);
    *end = '\0';
    bignum_to_digit_stream(n, base, print_bignum_consumer,
			   (bignum_procedure_context) &p);
    if (bignum_test(n) == bignum_comparison_less)
	*--p = '-';
    prints_str(p, end - p);
    RESTORE_STACK();
}

static void print_bignum_consumer(context, digit)
    bignum_procedure_context context;
    unsigned int digit;
{
    char **z = (char **)context;
    *--*z = (char)digit + (digit >= 10 ? 'a'-10 : '0');
}

static void prints_double(arg, fmt)
    Object	arg;
    char	*fmt;
{
    char buf[400]; /* big enough to represent max. float */
    Declare_stack_pointer;

    buf[0] = '\0';
    if (DOUBLEP(arg))
	sprintf(buf, fmt, IDOUBLE(arg));
    else {
	SAVE_STACK();
	PROTECT_1(arg);
	sprintf(buf, fmt, object_to_cdouble(arg));
	RESTORE_STACK();
    }
    prints_str(buf, strlen(buf));
}
 

 

static long get_iterstr(lstr, llen, lpos, startc, endc, iterstr)
    char *lstr;  /* input string */
    long llen;
    long lpos;  /* current pos in lstr to start looking */
    long startc, endc;
    char *iterstr;  /* buffer for returned iteration string */
{
    register long i;
    long level;

    iterstr[0] = '\0';
    for (i = 0, level=0; (lpos+1 < llen); i++) {
	if (lstr[lpos] == '~') {
	    if (lstr[lpos+1] == startc) {
		level++;
	    }
	    else if (lstr[lpos+1] == endc) {
		if (level == 0)
		    break;
		else
		    level--;
	    }
	}
	iterstr[i] = lstr[lpos];
	lpos++;
    }
    iterstr[i] = '\0';
    lpos++;
    return(lpos);
}

Object formatn varargs_1(int, n)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap;
    Object result;
    Object destination;
    Object cs;
    char *control_string;

    VA_START(ap,n);
    destination = VA_ARG(ap,Object);
    cs = VA_ARG(ap,Object);
    /* ISTRING can cons!  We *must* avoid that, somehow. */
     control_string = ISTRING(cs); 
    result = do_format(n-2, destination, control_string, ap);
    VA_END(ap);
    return VALUES_1(result);
}

Object format varargs_3(int, n, Object, destination, char *, control_string)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap;
    Object result;
 
    n-=2;
    VA_START(ap,control_string);
    result = do_format(n, destination, control_string, ap);
    VA_END(ap);
    return VALUES_1(result);
}

/* *** This DO_FORMAT_BUF_SIZE stuff is junk.  I'm just making the existing
 * *** code a bit more robust, rather than actually fixing the problem.  Dmitry
 * *** says he will deal with this later. -- kab, 8/26/91 */

/* 
 * jh, 11/10/94.  (Gensym modification) Increasing DO_FORMAT_BUF_SIZE from 200
 * to 500 to accomodate system-time-too-early-goodbye-message.
 */
#define DO_FORMAT_BUF_SIZE	500

#define DO_FORMAT_BUF_SIZE_ERROR(len) \
    (void)error(2, \
  "Format string too long.  Increase DO_FORMAT_BUF_SIZE to at least ~D.", \
		FIX(len))

Object do_format (nvar, stream, lstr, vargs)
    long nvar;  /* number of variables */
    Object stream;
    char *lstr;
    VA_LIST vargs;
{
    char str[DO_FORMAT_BUF_SIZE];
    size_t len;
    Object newstream, value;

    len = strlen(lstr);
    if (len < DO_FORMAT_BUF_SIZE-1)	/* -1 to leave room for null byte */
	strncpy(str, lstr, len+1);	/* include null byte in copy */
    else {
	DO_FORMAT_BUF_SIZE_ERROR(len);
	/*NOTREACHED*/
    }

    if (stream == NIL)
	newstream = NIL;
    else {
      if (EQ(stream, T))
	newstream = Standard_output;
      newstream = chase_write_stream(stream);
    }

    value = NIL;

    if (newstream != SI_Format_stream) 
        do_format_get_space (nvar, newstream, str, vargs, &value);
    else
	do_format_1(str, vargs, nvar, 0);

    return VALUES_1(value);
}

static void do_format_get_space (nvar, newstream, lstr, vargs, value_ptr)
    long nvar;
    Object newstream;
    char *lstr;
    VA_LIST vargs;
    Object *value_ptr;
{
    Declare_special(2);
    Declare_catch(1);

    char workspace[MAXFMTSTR+10];
    char *savework;
    long saveworklen;

    PUSH_SPECIAL(SI_Format_stream, newstream, 0);
    PUSH_SPECIAL(Current_print_level, FIXNUM_ADD1(Current_print_level), 1);
    saveworklen = Worklen;
    savework = Work;
    if (PUSH_UNWIND_PROTECT(0)) {
	 Work = workspace;
	 Work[0] = Work[MAXFMTSTR] = '\0';
	 Worklen = 0;

	 do_format_1(lstr, vargs, nvar, 0);

	 if (SI_Format_stream != NIL)
	   flush_work();
	 else {
	   Object value = make_string(FIX(Worklen), KOPT);
	   MEMCPY(ISTRING(value), Work, (SI_Size_type)ISSIZE(value));
	   *value_ptr = value;
	 }
       }
    POP_UNWIND_PROTECT(0);
    Worklen = saveworklen;
    Work = savework;
    CONTINUE_UNWINDING(0);
    POP_SPECIAL();
    POP_SPECIAL();
}

static long do_format_1 (lstr, args_ptr, arg_n, arg_i)
    char *lstr;
    VA_LIST args_ptr;
    long  arg_n, arg_i; /* number of arguments and start index*/
{   Declare_special(1);
    register long lpos, i;
    size_t llen = strlen(lstr);
	short n;
	long curcol, d;
    long prevworklen;
    long pp[NUMBER_OF_PREFIXES]; /* prefix parameters */
    char iterstr[100], fmtbuf[40], *s;
    Object temp, prevarg;
    Declare_fa_frame;
    long newarg_i, newarg_n;

    for (lpos = 0; lpos < llen; lpos++) {
	if (lstr[lpos] == '~') {
	    lpos++;
	    
	    /* get prefix parameters */
	    INIT_PREFIXES(pp);
	    for (n = 0; n < NUMBER_OF_PREFIXES; n++) {
		if (isdigit(lstr[lpos])) {
		    /* get numeric prefix [modifier] */
		    
		    pp[n] = lstr[lpos] - '0';
		    while (isdigit(lstr[++lpos])) {
			pp[n] = (pp[n] * 10) + (lstr[lpos] - '0');
		    }
		}
		else if (lstr[lpos] == '#') {
		    /* take number of remaining arguments */
		    
		    pp[n] = (short)(arg_n - arg_i); //add "(short)" maby lost date
		    lpos++;
		}
		else if (lstr[lpos] == 'V' ||
			 lstr[lpos] == 'v') {
		    /* take a value of the afgument */
		    
		    pp[n] = (short)IFIX(FA_ARG()); //add "(short)" maby lost date
		    lpos++;
		}
		else if (lstr[lpos] == '\'') {
		    lpos++;
		    pp[n] = lstr[lpos++];
		}

		if (lstr[lpos] == ',')
		    lpos++;
		else break; /* means: "the next character is a directive" */
	    }
	    n = 1;
	    switch(lstr[lpos]) {
	    case 'S':
	    case 's':
		/* any object */
	        PUSH_SPECIAL(Print_escape, T, 0);
		prevworklen = Worklen;
		prints(prevarg = FA_ARG());
		POP_SPECIAL();
		if (S_MINCOL != PREFIX_DEFAULT &&
		    (Worklen - prevworklen) < S_MINCOL)
		  d = (short)(S_MINCOL - (Worklen - prevworklen)); //add "(short)" maby lost date
		else
		  d = 0;
		for (i = 0; (i < d) &&
		     (Worklen < MAXFMTSTR); i++) {
		  Work[Worklen] = ' ';
		  Worklen++;
		}
		break;
	    case 'A': 
	    case 'a':
		/* any object */
		PUSH_SPECIAL(Print_escape, NIL, 0);
		prevworklen = Worklen;
		prints(prevarg = FA_ARG());
		POP_SPECIAL();
		if (S_MINCOL != PREFIX_DEFAULT &&
		    (Worklen - prevworklen) < S_MINCOL)
		  d = (short)(S_MINCOL - (Worklen - prevworklen)); //add "(short)" maby lost date
		else
		  d = 0;
		for (i = 0; (i < d) &&
		     (Worklen < MAXFMTSTR); i++) {
		  Work[Worklen] = ' ';
		  Worklen++;
		}
		break;
	    case 'C':
	    case 'c':
		prints_character(prevarg = FA_ARG());
		break;
	    case 'd':
	    case 'D':
		prints_number(prevarg = FA_ARG(),
			      10);
		break;
	    case 'o':
	    case 'O':
		prints_number(prevarg = FA_ARG(),
			      8);
		break;
	    case 'P':
	    case 'p':
		if (!eql(prevarg = FA_ARG(), FIX(1)))
		    prints_ch('s');
		Work[Worklen] = '\0';
		break;
	    case 'x':
	    case 'X':
		prints_number(prevarg = FA_ARG(), 16);
		break;
	    case 'F':
	    case 'f': /* not supported yet */
		if (1 /*d < 0*/)
		    strcpy(fmtbuf, "%f");
		else
		    sprintf(fmtbuf, "%%%d.%df", n, d);
		prints_double(prevarg = FA_ARG(),
			      fmtbuf);
		break;
	    case '%':
		for (i = 0; i < n; i++)
		    prints_ch('\n');
		Work[Worklen] = '\0';
		break;
	    case '&':
		if (SI_Format_stream == NIL || STREAM_CURRPOS(SI_Format_stream)){
		    /* if (Worklen && (Work[Worklen-1] != '\n')) { */
		    prints_ch('\n');
		    Work[Worklen] = '\0';
		}
		for (i = 1; i < n; i++)
		    prints_ch('\n');
		Work[Worklen] = '\0';
		break;
	    case '|':
		for (i = 0; i < n; i++)
		    prints_ch('\f');
		Work[Worklen] = '\0';
		break;
	    case '~':
		prints_ch('~');
		Work[Worklen] = '\0';
		break;
	    case '*':
		for (i = 0; i < n; i++)
		    prevarg = FA_ARG();
		break;
	    case 'T': 
	    case 't':
		SET_DEFAULT(T_COLNUM,1); 
		SET_DEFAULT(T_COLINC,1);
		curcol = (short)((SI_Format_stream == NIL) 
		    ? Worklen+1 
		    : STREAM_CURRPOS(SI_Format_stream)); //add "(short)" maby lost date
		if (T_COLNUM > curcol) {
		    for (i = 0; i < T_COLNUM-curcol &&
			 Worklen < MAXFMTSTR; i++) {
			Work[Worklen] = ' ';
			Worklen++;
		    }
		}
		else if (T_COLINC) {
		    for (i = 0; i < T_COLINC-curcol%T_COLINC &&
			Worklen < MAXFMTSTR; i++) {
			Work[Worklen] = ' ';
			Worklen++;
		    }
		}
		if (SI_Format_stream != NIL)
		    STREAM_CURRPOS(SI_Format_stream) += (short)i; //add "(short)" maby lost date
		Work[Worklen] = '\0';
		break;
	    case '(':
		lpos++;
		lpos = get_iterstr(lstr,llen,lpos,'(',')',iterstr);
		temp = prevarg = FA_ARG();
		if (TRUEP(temp)) {
		    prevworklen = Worklen;
		    FA_UNGET();
		    arg_i = FA_USING_CONTROL(iterstr);
		    _strupr(&Work[prevworklen]); //strupr is old function
		    Work[prevworklen] = toupper(Work[prevworklen]);
		}
		break;
	    case '[':
		lpos++;
		lpos = get_iterstr(lstr,llen,lpos,'[',']',iterstr);
		temp = prevarg = FA_ARG();
		/* warn: ignores nesting!! */
		for (i = IFIX(temp), s = iterstr; i; i--)
		    SKIP_OVER(s,';');
		arg_i = FA_USING_CONTROL(s);
		break;
	    case '{':
		/* iterate through arg(s),using control-string before ~} */
		lpos++;
		
		BEGIN_FA_LIST(FA_ARG()); 
		lpos = get_iterstr(lstr, llen, lpos, '{', '}', iterstr);
		newarg_i = FA_ARG_INDEX();
		newarg_n = FA_ARG_NUMBER();
		while (newarg_i < newarg_n)
		    newarg_i = 
			do_format_1(iterstr, FA_ARGS(),newarg_n, newarg_i);
		END_FA_LIST();
		break;
	    case '?':
		FA_CONTROL_ARG(iterstr);
		BEGIN_FA_LIST(FA_ARG()); 
		newarg_i = FA_ARG_INDEX();
		newarg_n = FA_ARG_NUMBER();
		do_format_1(iterstr, FA_ARGS(),newarg_n, newarg_i);
		END_FA_LIST();
		break;
	    case '@':
		lpos++;
		switch(lstr[lpos]) {
		case 'S':
		case 's':
		  /* any object */
		  PUSH_SPECIAL(Print_escape, T, 0);
		  if (S_MINCOL != PREFIX_DEFAULT) {
		    for (i = 0; (i < S_MINCOL) &&
			 (Worklen < MAXFMTSTR); i++) {
		      Work[Worklen] = ' ';
		      Worklen++;
		    }
		    prevworklen = Worklen;
		    prints(prevarg = FA_ARG());
		    { 
		      int len, d;
		      if ((Worklen - prevworklen) < S_MINCOL)
			len = Worklen - prevworklen;
		      else 
			len = S_MINCOL;
		      for (d = prevworklen; d < Worklen; d++)
			Work[d-len] = Work[d];
		      Worklen -=len;
		    }
		  }
		  else
		    prints(prevarg = FA_ARG());
		  POP_SPECIAL();
		  break;
		case 'A': 
		case 'a':
		  /* any object */
		  PUSH_SPECIAL(Print_escape, NIL, 0);
		  if (S_MINCOL != PREFIX_DEFAULT) {
		    for (i = 0; (i < S_MINCOL) &&
			 (Worklen < MAXFMTSTR); i++) {
		      Work[Worklen] = ' ';
		      Worklen++;
		    }
		    prevworklen = Worklen;
		    prints(prevarg = FA_ARG());
		    { 
		      int len, d;
		      if ((Worklen - prevworklen) < S_MINCOL)
			len = Worklen - prevworklen;
		      else 
			len = S_MINCOL;
		      for (d = prevworklen; d < Worklen; d++)
			Work[d-len] = Work[d];
		      Worklen -=len;
		    }
		  }
		  else
		    prints(prevarg = FA_ARG());
		  POP_SPECIAL();
		  break;
		case '[':
		    lpos++;
		    lpos = get_iterstr(lstr,llen,lpos,'[',']',iterstr);
		    temp = prevarg = FA_ARG();
		    if (TRUEP(temp)) {
			FA_UNGET();
			arg_i = FA_USING_CONTROL(iterstr);
		    }
		    break;
		case '?':
		    FA_CONTROL_ARG(iterstr);
		    arg_i = FA_USING_CONTROL(iterstr);
		    break;
		case '{':
		    lpos++;
		    lpos = get_iterstr(lstr, llen, lpos, '{', '}', iterstr);
		    while (arg_i < arg_n)
			arg_i = FA_USING_CONTROL(iterstr);
		    break;
		case 'T': 
		case 't':
		    SET_DEFAULT(T_COLREL,1); 
		    SET_DEFAULT(T_COLINC,1);
		    curcol = (short)((SI_Format_stream == NIL) 
			? Worklen+1 
			: STREAM_CURRPOS(SI_Format_stream)); //add "(short)" maby lost date
                    {
			for (i = 0; i < T_COLREL &&
			     Worklen < MAXFMTSTR; i++) {
			    Work[Worklen] = ' ';
			    Worklen++;
			}
		    }
		    if (T_COLINC) {
			for (i = 0; i < T_COLINC - curcol%T_COLINC &&
			     Worklen < MAXFMTSTR; i++) {
			    Work[Worklen] = ' ';
			    Worklen++;
			}
		    }
		    if (SI_Format_stream != NIL)
			STREAM_CURRPOS(SI_Format_stream) += (short)i; //add "(short)" maby lost date	      
		    Work[Worklen] = '\0';
		    break;
		case '(':
		    lpos++;
		    lpos = get_iterstr(lstr,llen,lpos,'(',')',iterstr);
		    temp = prevarg = FA_ARG();
		    if (TRUEP(temp)) {
			prevworklen = Worklen;
			FA_UNGET();
			arg_i = FA_USING_CONTROL(iterstr);
			_strlwr(&Work[prevworklen]); //strlwr is old function
			Work[prevworklen] = toupper(Work[prevworklen]);
		    }
		    break;
		case '\n':
		    /* keep newline, but ignore following whitespace */
		    prints_ch('\n');
		    Work[Worklen] = '\0';
		    while(isspace(lstr[++lpos]))
			;
		    lpos--;
		    break;
		case 'P':
		case 'p':
		    if (eql(prevarg = FA_ARG(), FIX(1)))
			prints_ch('y');
		    else {
			prints_ch('i');
			prints_ch('e');
			prints_ch('s');
                    }			
		    Work[Worklen] = '\0';
		    break;
		case 'R':
		    error(1, "format: roman numerals not supported");
		default:
		    error(2, "format: bad directive - ~A",
			  istring_to_string(lstr));
		    break;
		}
		break;
	    case '<':
		/* do not support justification */
		lpos++;
		lpos = get_iterstr(lstr,llen,lpos,'<','>',iterstr);
		arg_i = FA_USING_CONTROL(iterstr);
		break;
	    case ':':
		lpos++;
		switch(lstr[lpos]) {
		case '@':
		    lpos++;
		    switch(lstr[lpos]) {

		    case 'P':
		    case 'p':
			if (eql(prevarg, FIX(1)))
			prints_ch('y');
		    else {
			prints_ch('i');
			prints_ch('e');
			prints_ch('s');
                    }			
		    Work[Worklen] = '\0';
		    break;


		    default:
			error(2, "format: bad directive - ~A",
			      istring_to_string(lstr));
			break;
		    }
		    break;
		case '*':
		    for (i = 0; i < n; i++)
			FA_UNGET();
		    break;
		case '{':
		    lpos++;
		    lpos = get_iterstr(lstr,llen,lpos,'{', '}',iterstr);
		    temp = FA_ARG();
		    while(TRUEP(temp)) {
			BEGIN_FA_LIST(M_CAR(temp)); 
			newarg_i = FA_ARG_INDEX();
			newarg_n = FA_ARG_NUMBER();
			do_format_1(iterstr, FA_ARGS(),newarg_n, newarg_i);
			END_FA_LIST();
			temp = M_CDR(temp);
		    }
		    break;
		case '[':
		    lpos++;
		    lpos = get_iterstr(lstr,llen,lpos,'[',']',s = iterstr);
		    temp = prevarg = FA_ARG();
		    if (TRUEP(temp))
			SKIP_OVER(s,';');
		    arg_i = FA_USING_CONTROL(s);
		    break;
		case '(':
		    lpos++;
		    lpos = get_iterstr(lstr,llen,lpos,'(',')',iterstr);
		    temp = prevarg = FA_ARG();
		    if (TRUEP(temp)) {
			prevworklen = Worklen;
			FA_UNGET();
			arg_i = FA_USING_CONTROL(iterstr);
			_strlwr(&Work[prevworklen]); //strlwr is old function
			Work[prevworklen] = toupper(Work[prevworklen]);
			while (++prevworklen < Worklen) {
			    if (!isalpha(Work[prevworklen])) {
				/* skip non-letters */
				while(!isalpha(Work[++prevworklen]));
				Work[prevworklen] = toupper(Work[prevworklen]);
			    }
			}
		    }
		    break;
		case '\n':
		    /* ignore the newline, leave whitespace in place */
		    break;
		case 'P':
		case 'p':
		    if (!eql(prevarg, FIX(1)))
			prints_ch('s');
		    Work[Worklen] = '\0';
		    break;
		default:
		    error(2, "format: bad directive - ~A",
			  istring_to_string(lstr));
		    break;
		}
		break;
	    case ';':
		return (arg_i);
	    case '^':
		if (!(arg_i < arg_n)) return (arg_i);
		break;
	    case '\n':
		/* ignore both newline and following whitespace */
		while (isspace(lstr[++lpos]))
		    ;
		lpos--;
		break;
	    default:
		error(2, "format: bad directive - ~A",
		      istring_to_string(lstr));
		break;
	    }
	}
	else if (Worklen < MAXFMTSTR) {
	    Work[Worklen] = lstr[lpos];
	    Worklen++;
	    Work[Worklen] = '\0';
	    if (TRUEP(SI_Format_stream))
		STREAM_CURRPOS(SI_Format_stream) += 1;
	}
	else {
	    warn(1, "format: 2K buffer size exceeded");
	}
    }
    return (arg_i);
}

#if 0


Object formatr(stream, str, args)
Object stream;
Object str;
Object args;
{
    Declare_local_temp;
    char workspace[MAXFMTSTR+10];
    char *savework;
    int saveworklen;
    Object result, savestream, saveprintlevel;
#if !SI_SUPPORT_CLOS
    DECLARE_FRONTIER(prev_pos); DECLARE_AREA(prev_area);
#endif
    
    saveprintlevel = Current_print_level;
    saveworklen = Worklen;
    savework = Work;
    savestream = SI_Format_stream;
    if (FIXNUM_PLUSP(Print_level))
	Current_print_level = ZERO;
    
#if !SI_SUPPORT_CLOS
    BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
#endif

    Work = workspace;
    Work[0] = Work[MAXFMTSTR] = '\0';
    Worklen = 0;
    
    if (stream == NIL)
	SI_Format_stream = NIL;
    else {
	if (EQ(stream, T)) {
	    stream = Standard_output;
	}
	SI_Format_stream = chase_write_stream(stream);
    }
    
    do_formatr(ISTRING(str), args);
    
#if !SI_SUPPORT_CLOS
    END_LOCAL_ALLOCATION(prev_area, prev_pos);
#endif

    if (SI_Format_stream == NIL) {
	result = make_string(FIX(Worklen), NIL);
	MEMCPY(ISTRING(result), Work, (SI_Size_type)ISSIZE(result));
	Current_print_level = saveprintlevel;
        Worklen = saveworklen;
	Work = savework;
	SI_Format_stream = savestream;
	return VALUES_1(result);
    }
    else
	flush_work();
    Current_print_level = saveprintlevel;
    Worklen = saveworklen;
    Work = savework;
    SI_Format_stream = savestream;
    return VALUES_1(NIL);
}
/* *** It will die very soon. do_format_1 not uses it any more, 
that means it can be flashed with the rest of 'r versions */

Object do_formatr (lstr, args)
char *lstr;
Object args;
{
    Declare_local_temp;
    register int lpos, i;
    short llen = strlen(lstr), n, curcol, d;
    char iterstr[100], fmtbuf[20];
    Object temp, prev_escape;
    
    for (lpos = 0; lpos < llen; lpos++) {
	n = 1;
	d = -1;
	if (lstr[lpos] == '~') {
	    lpos++;
	    if (isdigit(lstr[lpos])) {
		n = lstr[lpos] - '0';
		while (isdigit(lstr[++lpos])) {
		    n = (n * 10) + (lstr[lpos] - '0');
		}
		if (lstr[lpos] == ',') {
		    lpos++;
		    d = lstr[lpos] - '0';
		    while (isdigit(lstr[++lpos]))
			d = (d * 10) + (lstr[lpos] - '0');
		}
	    }
	    switch(lstr[lpos]) {
	    case 'S':
	    case 's':
		/* any object */
		prev_escape = Print_escape;
		Print_escape = T;
		prints(CAR(args));
		args = CDR(args);
		Print_escape = prev_escape;
		break;
	    case 'A':
	    case 'a':
		/* any object */
		prev_escape = Print_escape;
		Print_escape = NIL;
		prints(CAR(args));
		args = CDR(args);
		Print_escape = prev_escape;
		break;
	    case 'C':
	    case 'c':
		prints_character(CAR(args));
		args = CDR(args);
		break;
	    case 'd':
	    case 'D':
		prints_number(CAR(args), 10);
		args = CDR(args);
		break;
	    case 'o':
	    case 'O':
		prints_number(CAR(args), 8);
		args = CDR(args);
		break;
	    case 'x':
	    case 'X':
		prints_number(CAR(args), 16);
		args = CDR(args);
		break;
	    case 'F':
	    case 'f':
		if (d < 0)
		    strcpy(fmtbuf, "%f");
		else
		    sprintf(fmtbuf, "%%%d.%df", n, d);
		prints_double(CAR(args), fmtbuf);
		break;
	    case '%':
		for (i = 0; i < n; i++)
		    prints_ch('\n');
		Work[Worklen] = '\0';
		break;
	    case '&':
		if (SI_Format_stream == NIL|| STREAM_CURRPOS(SI_Format_stream)) {
		    prints_ch('\n');
		    Work[Worklen] = '\0';
		}
		for (i = 1; i < n; i++)
		    prints_ch('\n');
		Work[Worklen] = '\0';
		break;
	    case '|':
		for (i = 0; i < n; i++)
		    prints_ch('\f');
		Work[Worklen] = '\0';
		break;
	    case '~':
		prints_ch('~');
		Work[Worklen] = '\0';
		break;
	    case '*':
		for (i = 0; i < n; i++)
		    args = CDR(args);
		break;
	    case 'T':
	    case 't':
		curcol = (SI_Format_stream == NIL) 
		    ? 1 : STREAM_CURRPOS(SI_Format_stream) + 1;
		for (i = curcol; (i < n) && (Worklen < MAXFMTSTR); i++) {
		    Work[Worklen] = ' ';
		    Worklen++;
		}
		Work[Worklen] = '\0';
		break;
	    case '{':
		/* iterate through arg, passing control-string before ~} */
		lpos++;
		lpos = get_iterstr(lstr,llen,lpos,'{','}',iterstr);
		temp = CAR(args);
		while (temp != NIL) {
		    temp = do_formatr(iterstr, temp);
		}
		args = CDR(args);
		break;
	    case '?':
		do_formatr(FIRST(args), SECOND(args));
		args = CDDR(args);
		break;
	    case '@':
		lpos++;
		switch(lstr[lpos]) {
		case '[':
		    lpos++;
		    lpos = get_iterstr(lstr,llen,lpos,'[',']',iterstr);
		    if (TRUEP(CAR(args))) {
			args = do_formatr(iterstr, args);
		    }
		    else {
			args = CDR(args);
		    }
		    break;
		default:
		    error(2, "format: invalid directive - ~A",
			  istring_to_string(lstr));
		    break;
		}
		break;
	    case '<':
		lpos++;
		lpos = get_iterstr(lstr,llen,lpos,'<','>',iterstr);
		args = do_formatr(iterstr, args);
		break;
	    case ':':
		if (lstr[lpos+1] == ';')
		    lpos++;
		break;
	    case '^':
		/* terminate format if no more args */
		if (ENDP(args)) {
		    return VALUES_1(NIL);
		}
		break;
	    case '\n':
		/* ignore whitespace, control string broken up */
		while (isspace(lstr[++lpos]))
		    ;
		lpos--;
		break;
	    default:
		error(2, "format: invalid directive - ~A",
		      istring_to_string(lstr));
		break;
	    }
	}
	else if (Worklen < MAXFMTSTR) {
	    Work[Worklen] = lstr[lpos];
	    Worklen++;
	    Work[Worklen] = '\0';
	    if (TRUEP(SI_Format_stream))
		STREAM_CURRPOS(SI_Format_stream) += 1;
	}
	else {
	    warn(1, "format: 2K buffer size exceeded");
	}
    }
    return VALUES_1(args);
}

#endif 

static void print_not_readable_error(object)
  Object object;
{ Declare_special(1);

  PUSH_SPECIAL(Print_readably, NIL, 0);
  
#if SI_SIGNAL_CONDITIONS
  (void)errorn(3, Qprint_not_readable, Kobject, object);
#else
  (void)error(2, "Attempted to print unreadable object ~S.", object);
#endif

  POP_SPECIAL();
}

Object begin_print_unreadable_object(object, stream, type_p, id_p, body_p)
  Object object, stream, type_p, id_p, body_p;
{
    Declare_local_temp;
  Declare_protect(2);
  Object type, spacep;
  long flags = 0;

  PROTECT_LOCALS();
  PROTECT_2(object, stream);

  if (TRUEP(type_p)) flags |= 1L;
  if (TRUEP(id_p) || TRUEP(body_p)) flags |= 2L;

  if (TRUEP(Print_readably)) print_not_readable_error(object);

  if (flags & 1L) type = type_of(object);
  else type = NIL;

  /* Print a space if printing type and either body exists or printing id. */
  if (!(flags ^ 3L)) spacep = T;
  else spacep = NIL;

  (void)format(4, stream, "#<~@[~S~]~:[~; ~]", type, spacep);

  UNPROTECT_LOCALS();
  return VALUES_1(NIL);
}

Object finish_print_unreadable_object(object, stream, identity, spacep)
  Object object, stream, identity, spacep;
{
    Declare_local_temp;
  if (TRUEP(identity))
    identity = FIX((SI_Long)object);
  else
    spacep = NIL;
  
  (void)format(4, stream, "~:[~; ~]~@[#x~X~]>", spacep, identity);
  return VALUES_1(NIL);
}

