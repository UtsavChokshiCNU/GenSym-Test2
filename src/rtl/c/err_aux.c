/*
 * err_aux.c - error-handling aux. functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern Object Qlist;

#if SI_USE_PROTOTYPES

extern Object (*SI_errorn_fptr) (long,...);
extern Object STATIC_STRING(char *s);

#else

extern Object (*SI_errorn_fptr) ();
extern Object STATIC_STRING();

#endif

#include "errors.h"

/******************************************************************************
 *
 * void SI_type_error(datum, expected_type)
 * Object datum;
 * Object expected_type;
 *  Helper function, for signaling type errors.
 *
 *****************************************************************************/

#if SI_SIGNAL_CONDITIONS

extern Object Qtype_error;
extern Object Kdatum;
extern Object Kexpected_type;

void SI_type_error (datum, expected_type)
  Object	datum, expected_type;
{ (void)errorn(5, Qtype_error, Kdatum, datum, Kexpected_type, expected_type);
  /*NOTREACHED*/
}

extern Object Qundefined_function;
extern Object Kname;

void SI_undefined_function_error (name)
  Object	name;
{ (void)errorn(3, Qundefined_function, Kname, name);
  /*NOTREACHED*/
}

extern Object Qunbound_variable;

void SI_ubound_variable_error (name)
  Object	name;
{ (void)errorn(3, Qunbound_variable, Kname, name);
  /*NOTREACHED*/
}

#else

void SI_type_error (datum, expected_type)
  Object	datum, expected_type;
{ SI_Declare_static_string(estr, d, "~S is not of type ~S.");

  (void)errorn(3, estr, datum, expected_type);
  /*NOTREACHED*/
}

void SI_undefined_function_error (name)
  Object	name;
{ SI_Declare_static_string(estr, d, "~S does not have a function definition.");

  (void)errorn(2, estr, name);
  /*NOTREACHED*/
}

void SI_unbound_variable_error (name)
  Object	name;
{ SI_Declare_static_string(estr, d, "~S is unbound.");

  (void)errorn(2, estr, name);
  /*NOTREACHED*/
}

#endif

Object list_error (obj)
  Object obj;
{
    Declare_local_temp;
  SI_type_error(obj, Qlist /* should be Qlist */);
  /*NOTREACHED*/
  return VALUES_1(NIL);
}

/* TRUN:EXIT - Chestnut extension. */

/*
 * Gensym modification (jh, 9/29/93).  Changed lexit() to call the function
 * g2_error_handler(), which is translated from the Lisp module OS-ERROR.  This
 * function throws to a Lisp catchpoint that invokes the error handlers we want
 * to run for a given Gensym product.  This change was brought forward from 
 * our previous modification to the old Chestnut 1.7 runtime library in 
 * /bt/ab/runtime/c/errors.c
 *
 * jh, 4/21/94.  Per jra, restored lexit() to its original behavior, which was
 * simply to call the C library function exit().  This will help profilers work
 * better, especially on the HP.  The call to g2_error_handler() that used to
 * reside in lexit() has been moved to all the places lexit() was formerly
 * called, except the call in the automatically generated main.c file, which is
 * the only time we really want to exit without trying to handle the error.
 */
Object lexit (code)
    Object code;
{
    extern Object     g2_error_handler();
    Declare_local_temp;

    /* Chestnut comments: */
    /* Ought to execute unwind protections here */
    /* add application specific code here such as turn_on_cursor */

    (void)exit((long) IFIX(code));

    /*NOTREACHED*/
    return VALUES_1(NIL);
}


/* g2rtl_exit_long is a Gensym addition.  It just exists so that code which
 * does not bring in all of rtl (i.e., code in ext/c) can easily call lexit,
 * without having to pass an Object.  g2rtl_exit_long takes a plain old long,
 * and converts to an Object itself.  -jv, 1/14/04
 */
void g2rtl_exit_long (code)
    long code;
{
  lexit(FIX(code));

  /*NOTREACHED*/
}


/* void SI_fatal_error(char *string, ...)
 *   Prints a message on STDERR using the arguments to produce formated output
 *   (as for printf), and then calls exit to indicate failure.
 */

/*VARARGS1*/
void SI_fatal_error varargs_1(char *, lstr)
{ va_list	ap;

  SI_va_start(ap,lstr);
  if (fprintf(STDERR, "\nFATAL ERROR: ") != EOF)
    (void)vfprintf(STDERR, lstr, ap);
  (void)exit(1);		/* EXIT_FAILURE in ANSI */
  /*NOTREACHED*/
}

