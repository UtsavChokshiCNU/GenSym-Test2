/*
 * stderror.c -  Common Lisp RTL Standard error-handling  functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern Object Break_function;
extern Object Break_on_signals;
DECLARE_VARIABLE(Error_output);

#if SI_USE_PROTOTYPES

extern Object (*SI_cerror_fptr)(int n, char *cstr,char *estr, ...);
extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object (*SI_errorn_fptr) (int,...);
extern char *SI_istring(Object o);
extern Object (*SI_warn_fptr) (int n, char *lstr, ...);
extern Object STATIC_STRING(char *s);
extern Object force_output(Object);
extern Object format(int n, Object destination, char *control_string, ...);
extern Object fresh_line(Object);
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);
#else
extern Object funcall0(Object func);
#endif
extern Object lexit(Object code);
extern Object y_or_n_p(int n, char *format_string, ...);
extern Object breakn(int n, ...);
extern Object lbreak(int n, char * lstr, ...);
extern Object extend_string_output_stream(Object);
extern Object lclose(Object stream, Object abort);

#else

extern Object (*SI_cerror_fptr)();
extern Object (*SI_error_fptr) ();
extern Object (*SI_errorn_fptr) ();
extern char *SI_istring();
extern Object (*SI_warn_fptr) ();
extern Object STATIC_STRING();
extern Object force_output();
extern Object format();
extern Object fresh_line();
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall();
#else
extern Object funcall0();
#endif
extern Object lexit();
extern Object y_or_n_p();
extern Object breakn();
extern Object lbreak();
extern Object extend_string_output_stream();
extern Object lclose();

#endif


#undef error
#undef cerror
#undef errorn
#undef warn

#define error  g2rtl_error
#define cerror g2rtl_cerror
#define errorn g2rtl_errorn
#define warn g2rtl_warn

#include "svargs.h"

#if SI_USE_PROTOTYPES

extern Object do_format(int nvar, Object stream, char *lstr,
			Stack_item_ptr vargs);

#else

extern Object do_format();

#endif

/*
 * jh, 4/21/94.  Gensym change.  Replaced calls to lexit() with
 * g2_error_handler() in error(), errorn(), cerror(), breakn(), and lbreak().
 * These functions should call our error handler rather than exiting directly.
 */
extern Object g2int_error_handler();

/* ERROR */ 

extern long notify_type_2_error; /* Gensym modification */

/*VARARGS1*/
static void error_nargs_aux(v, lstr, ap)
    int v; /* number of variables */
    char *lstr;
    VA_LIST ap;
{
    VA_LIST saveap = ap; /* Gensym modification - save the argument pointer */

    format(2, Error_output, "Error: ");
    do_format(v, Error_output, lstr, ap);
    fresh_line(Error_output);
    force_output(Error_output);

    /* Gensym (jh, 10/4/91, entire body following)
     * jh, 9/27/93.  Revised for 3.1 rtl.
     * jh, 12/20/96.  Added notify_type_2_error for bug HQ-396329.
     *
     * This writes the error message to an adjustable string using a translation
     * of with-output-to-string.  Obtained by translating and then hand-editing
     *   (declaim (tx:nonrelocating update-gensym-error-buffer))
     *   (defun update-gensym-error-message-buffer ()
     *     (setf (fill-pointer gensym-error-message-buffer) 0)
     *     (with-output-to-string
     *         (error-buffer-stream gensym-error-message-buffer)
     *       (duplicate-error-formatting-here error-buffer-stream)
     *     nil)
     * Hand-edits are marked with "Gensym hand-edit" below.
     */
    {
     DECLARE_VARIABLE(Gensym_error_message_buffer); /* Gensym hand-edit */
     Object fill_pointer_arg, error_buffer_stream;
     Declare_stack_pointer;
     /* Declare_catch(1); */

     SAVE_STACK();
     fill_pointer_arg = Gensym_error_message_buffer;
     SET_FILL_POINTER(fill_pointer_arg,FIX(0));
     notify_type_2_error = 0;
     error_buffer_stream = 
	     (Object) extend_string_output_stream(Gensym_error_message_buffer);
     notify_type_2_error = 1;
       /* 
        * Gensym hand-edit.  Following three lines duplicate the original code
        * above that formats an error message to standard output.  The
        * difference is that the following lines write to our adjustable error
        * string and do not insert a freshline.  They replace the call to
        * duplicate-error-formatting-here in the translated Lisp template 
        * mentioned above. 
        */
       format(2, error_buffer_stream, "Error: ");
       do_format(v, error_buffer_stream, lstr, saveap);
       force_output(error_buffer_stream);

     /* 
      * Gensym hand-edit.  Beware.  In translated code, lclose() is a macro to
      * reach the actual Common Lisp close function since UNIX has a function by
      * that name too.  The lclose() we use here is different.  It is an actual
      * function that expects a fixed number of args.
      */
     lclose(error_buffer_stream, NIL); 
    }
    lbreak(1, "Error");
}

Object error varargs_2(int, n, char *, lstr)
{
    Declare_va_stack_pointer;
    VA_LIST ap;

    n--;
    VA_START(ap,lstr);
    error_nargs_aux(n, lstr, ap);
    VA_END(ap);
    return g2int_error_handler();
}

Object errorn varargs_1(int, n)
{
    Declare_va_stack_pointer;
    VA_LIST ap;
    char *lstr;
    Object str;

    VA_START(ap,n);
    str = VA_ARG(ap, Object);
    lstr = ISTRING(str);
    error_nargs_aux(n-1, lstr, ap);
    VA_END(ap);
    return g2int_error_handler();
}


/* CERROR */

static Object continue_string = UNBOUND;

#define INITIALIZE_CONTINUE_STRING() \
    if (continue_string == UNBOUND) \
      continue_string = STATIC_STRING("~%Continue? ")


static void cerror_nargs_aux (v, cstr, estr, ap, saveap)
    long v;
    char *cstr, *estr;
    VA_LIST ap, saveap; 
{
    INITIALIZE_CONTINUE_STRING();
    do_format(v, Error_output, estr, ap);
    force_output(Error_output);
    format(2, Error_output, "~&If continue:  ");

    do_format(v, Error_output, cstr, saveap);
    
    if (!TRUEP(y_or_n_p(1, "~%Continue? ")))
	breakn(2, KOPT, NIL);

}

Object cerrorn varargs_1(int, n)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap, saveap;
    Object str;
    char *cstr, *estr;

    VA_START(ap,n);
    VA_START(saveap,n);
    str = VA_ARG(ap, Object);
    cstr = ISTRING(str);
    str = VA_ARG(ap, Object);
    estr = ISTRING(str);
    /* Skip over continue and format strings for continue args.
     * Note that we can't change arglist here to the way its done for cerror().
     * The reason is that this function is the entry for the Lisp funcallable
     * function object, so must match variadic lisp function prototype used by
     * SI_internal_apply(). */
    (void)VA_ARG(saveap, Object);
    (void)VA_ARG(saveap, Object);
    cerror_nargs_aux(n-2, cstr, estr, ap, saveap);
    VA_END(saveap);
    VA_END(ap);
    return(VALUES_1(NIL));
}

/*
 * Gensym modification.  Disallow cerror(), since no errors are continuable.
 * Just pass the error string to error_nargs_aux(), and then call
 * gensym_error_handler().  Gensym has modified the RTL function
 * error_nargs_aux() appropriately.
 */
Object cerror varargs_3(int, n, char *, cstr, char *, estr)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap, saveap;

    n-=2;
    VA_START(ap,estr);
    VA_START(saveap,estr);

/*    cerror_nargs_aux(n, cstr, estr, ap, saveap); */
    error_nargs_aux(n, estr, ap);

    VA_END(saveap);
    VA_END(ap);

/*    return(VALUES_1(NIL)); */
    return g2int_error_handler();
}

/* WARN */

extern Object Break_on_signals;

/*VARARGS1*/

static void warn_nargs_aux (v, lstr, ap)
    long v;
    char *lstr;
    VA_LIST ap;
{
    format(2, Error_output, "Warning: ");
    do_format(v, Error_output, lstr, ap);
    fresh_line(Error_output);
    force_output(Error_output);
    if (Break_on_signals != NIL)
	breakn(2, KOPT, NIL);
}

/*VARARGS1*/
Object warn varargs_2(int, n, char *, lstr)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap;

    n--;
    VA_START(ap,lstr);
    /* fresh_line(Error_output);   - enable this when fresh-line works */
    warn_nargs_aux(n, lstr, ap);
    VA_END(ap);
    return VALUES_1(NIL);
}

Object warnn varargs_1(int, n)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap;
    char *lstr;
    Object str;

    VA_START(ap,n);
    str = VA_ARG(ap,Object);
    lstr = ISTRING(str);
    /* fresh_line(Error_output);   - enable this when fresh-line works */
    warn_nargs_aux(n-1, lstr, ap);
    VA_END(ap);
    return VALUES_1(NIL);
}

#if 0
Object warnr (str, args)
    Object str, args;
{
    Declare_local_temp;
    /* fresh_line(Error_output); */
    format(2, Error_output, "Warning: ");
    formatr(Error_output, str, args);
    fresh_line(Error_output);
    if (Break_on_signals != NIL)
	breakn(2, KOPT, NIL);
    return VALUES_1(NIL);
}
#endif /* SI_SUPPORT_MF */


/* BREAK */

extern Object Break_function;

/*VARARGS1*/
Object breakn varargs_1(int, n)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap;
    char *lstr;
    Object format_string;

    VA_START(ap,n);
    if (UNSUPPLIED_P(format_string = VA_ARG(ap,Object))) {
	lstr = "";
	do_format(n-1, Error_output, lstr, ap);
    }
    VA_END(ap);
    if (Break_function != NIL)
	FUNCALL_0(Break_function);  /* perhaps throw to top-level */
    return VALUES_1(T);
}

/*VARARGS1*/
Object lbreak varargs_2(int, n, char *, lstr)
{
    Declare_local_temp;
    Declare_va_stack_pointer;
    VA_LIST ap;

    n--;
    VA_START(ap,lstr);
    if (lstr) 	do_format(n, Error_output, lstr, ap);
    VA_END(ap);

    if (Break_function != NIL)
	FUNCALL_0(Break_function);  /* perhaps throw to top-level */
    return VALUES_1(T);
}


void SI_INIT_error()
{

    SI_error_fptr = error;
    SI_errorn_fptr = errorn;
    SI_cerror_fptr = cerror;
    SI_warn_fptr = warn;
}
