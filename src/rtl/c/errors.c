/* 
 * errors.c - sturtup and lightweight error-reporting  functions
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 */
 
#include "runtime.h"

#if SI_USE_PROTOTYPES

extern Object lexit(Object code);
extern char *SI_istring(Object o);

#else

extern Object lexit();
extern char *SI_istring();

#endif

/*
 * jh, 4/21/94.  Gensym change.  Replaced calls to lexit() with
 * g2_error_handler() in SI_error(), SI_errorn(), and cerror_nargs_aux().  These
 * functions should call our error handler rather than exiting directly.
 */
extern Object g2int_error_handler();

Object Break_function = NIL;


/* To be a part of the condition system */
Object Break_on_signals = UNBOUND;
Object Debugger_hook  = UNBOUND;

static char Work[200];
static char *wptr = Work;

#define STDERR  stderr
/* on SUN, sprintf is declared  not as 'extern int sprintf();'  */
#define SPRINTF sprintf
#define ADVANCE() for(;*wptr;++wptr) /* introduces because sprintf is not
				     portably counts number of chars */
#define wputch(ch) (*wptr++ = (ch))

/* somewhat vfprintf does but with ~-directives  allowed in sptr */

/*VARARGS1*/
static void error_nargs_aux(prefix, sptr, ap)
    char *prefix, *sptr;
    va_list ap;
{
    Object val;

    wputch('\n');
    SPRINTF(wptr, prefix);
    ADVANCE();
    for  (; *sptr; sptr++)
	if (*sptr == '~')   /* some format skills */
	    if (*++sptr == '%')  wputch('\n');
	    else if (*sptr) {
		if (FIXNUMP(val =  va_arg(ap, Object)))
		    SPRINTF(wptr, "#<FIXNUM  %d >", IFIX(val));
		else if (SI_IMMEDIATEP(val)) {
		    if (val == NIL)
			SPRINTF(wptr, " NIL");
		    else if (CHARACTERP(val)) 
			SPRINTF(wptr, "#\\%c >", ICHAR_CODE(val));
		    else 
			SPRINTF(wptr, "#<IMMEDIATE  %p >", val);
		}
		else /* type name would be desirable */
		    SPRINTF(wptr, "#<OBJECT  %p type=%d>", val,
			    SI_STORED_OBJECT_TYPE(val));
		ADVANCE();
	    }
	    else break;
	else wputch(*sptr);
    wputch('\0');
    fputs(wptr = Work, STDERR);
    fflush(STDERR);
}

/* 
 * jh, 4/10/95.  Gensym addition.  We want to excise standard error handling for
 * the GSI size-reduction project.  We have excised all explicit calls to error
 * and friends from GSI code.  Such calls would force us to use standard error
 * handling no matter what we do here, since they depend on SI_error_fptr being
 * set to error(), SI_cerror_fptr being set to cerror(), and so on.
 *
 * Once we have excised explicit calls to error and friends, we still must deal
 * with getting meaningful error messages out of calls made to error by the
 * Chestnut runtime library.  These calls are made indirectly, through
 * SI_error_fptr and friends, which in turn call error_nargs_aux().  The C
 * string Work is used by error_nargs_aux() to format the error meesage from an
 * error in the Chestnut run time library.  So the function
 * update_gensym_error_buffer() copies Work into Gensym_error_message_buffer,
 * where it is accessible to our error-reporting machianism.  This function is
 * only called in GSI, only in g2_error_handler(), immediately after Work has
 * been modified by error_nargs_aux().
 */
extern void
update_gensym_error_buffer()
{
 DECLARE_VARIABLE(Gensym_error_message_buffer);
 char           *chestnut_buffer_c_string = Work;
 char           *gensym_buffer_c_string = (char *)ISTRING(Gensym_error_message_buffer);

 SET_FILL_POINTER(Gensym_error_message_buffer, FIX(strlen(Work)));
 while (*gensym_buffer_c_string++ = *chestnut_buffer_c_string++); 
}

/*VARARGS1*/    
static Object SI_error varargs_2(int, n,  char *, lstr)
{
    va_list ap;

    SI_va_start(ap,n);
    error_nargs_aux("Error:    ", lstr, ap);
    putc('\n', STDERR);
    va_end(ap);
    return g2int_error_handler();
}

/*VARARGS1*/
static Object SI_errorn varargs_1(int, n)
{
    va_list ap;
    char *lstr;
    Object str;

    SI_va_start(ap,n);
    str = va_arg(ap, Object);
    /* extract the string */
    lstr = " ";
    if (!SIMPLE_STRING_P(str)) {
	if (SYMBOLP(str)) {
	    switch (ISYMBOL_TYPE(str)) {
	    case MSYMBOL_TYPE:
	    case EMSYMBOL_TYPE:
	    case MKEYWORD_TYPE:
		return MSYMBOL_NAME(str);
	    default:
		;
	    }
	}
    }
    else  lstr =  &SI_ISCHAR(str, 0);

    error_nargs_aux("Error:    ", lstr, ap);
    putc('\n', STDERR);
    va_end(ap);
    return g2int_error_handler();
}

/*VARARGS1*/
static void cerror_nargs_aux (v, cstr, estr, ap, saveap)
    long v;
    char *cstr, *estr;
    va_list ap, saveap;
{
    error_nargs_aux("", estr, ap);
    error_nargs_aux("If continue:  ", cstr, saveap);
          
    /* try not to include the reader in the image */
    { 
	char ch;
	while (TRUE) {
	    printf("\nContinue ? (Y or N )");
	    ch = getc(stdin); 
	    if (ch == 'Y' || ch == 'y') {
		break;
	    }
	    else if (ch == 'N' || ch == 'n'|| ch == EOF) g2int_error_handler();
	    else printf("\nPlease type one of Y or N.\n");
	    while (ch > '\n') ch = getc(stdin);
	}
    }
}
 
/*VARARGS1*/
static Object SI_cerror varargs_3(int, n, char *, cstr, char *, estr)
{
    Declare_local_temp;
    va_list ap, saveap;

    SI_va_start(ap,estr);
    SI_va_start(saveap,estr);
    cerror_nargs_aux(n, cstr, estr, ap, saveap);
    va_end(saveap);
    va_end(ap);
    return(VALUES_1(NIL));
}

/*VARARGS1*/
static void warn_nargs_aux (v, lstr, ap)
    long v;
    char *lstr;
    va_list ap;
{
    error_nargs_aux("Warning:  ", lstr, ap);
    /* never break on these warnings */
}

/*VARARGS1*/
static Object SI_warn varargs_2(int, n, char *, lstr)
{
    Declare_local_temp;
    va_list ap;

    n--;
    SI_va_start(ap,lstr);
    warn_nargs_aux(n, lstr, ap);
    va_end(ap);
    return VALUES_1(NIL);
}


#if 1
void default_structure_print_aux (stream, name, info)
  Object stream, name, info;
{
    /* call printer here */
}

#else 
void default_structure_print_aux (stream, name, info)
  Object stream, name, info;
{
  (void)format(4, stream, "#S(~S~{ ~S~})", name, info);

}
#endif


/* Error system handles */

#if SI_USE_PROTOTYPES

Object (*SI_error_fptr) (int n, char *lstr, ...) =
     SI_error;

Object (*SI_errorn_fptr)(int,...) =
     SI_errorn;

Object (*SI_cerror_fptr)(int n, char *cstr,char *estr, ...) =
     SI_cerror;

Object (*SI_warn_fptr)  (int n, char *lstr, ...) =
     SI_warn;

#else

Object (*SI_error_fptr) () =
     SI_error;

Object (*SI_errorn_fptr)() =
     SI_errorn;

Object (*SI_cerror_fptr)() =
     SI_cerror;

Object (*SI_warn_fptr)  () =
     SI_warn;

#endif

void SI_errors_ENSURE() {}

extern TLS Object Values[];

void bytecode_mvs_2(a1)
  void **a1;
{
  *a1 = Values_count > 1 ? Values[0] : NIL;
}

void bytecode_mvs_3(a1,a2)
  void **a1,**a2;
{
  *a1 = Values_count > 1 ? Values[0] : NIL;
  *a2 = Values_count > 2 ? Values[1] : NIL;
}
