/* methargs.h -- generic function and method arguments.
 *
 * Copyright (c) 1991, Chestnut Software, Inc., All Rights Reserved.
 *
 *
 *
 * Header file for things involved in manipulation of method argument frames.
 */

extern Object METHOD_COMBINATION_KEY_VALUE();
extern Object COPY_METHOD_FRAME();
extern Object METHOD_ARGUMENT_LIST();
extern Object SI_method_frame_list();
extern Object SI_compute_method_frame_rest();
extern Object SI_method_frame_parse_keywords();

/******************************************************************************
 *
 * A method argument frame is implemented as a simple-vector.  If there are n
 * arguments, the length of the vector is n+k, with the arguments in the first
 * n elements.  The last k elements are reserved for various internal values.
 * Frames are normally stack allocated by the generic function discriminator
 * that received the arguments, but under some conditions a heap allocated copy
 * of the frame is allocated and used instead.
 *
 * [Note: At an earlier stage of implementation it appeared that it would be
 * more efficient to access the direct arguments and perform optional argument
 * checking if the arguments were placed first with the special fields placed
 * at the end.  I think this is no longer the case most of the time, since the
 * offsets will be constants that the C compiler will be able to combine at
 * compile time.  Assuming that this is indeed true, then it would be better to
 * put the special fields at the beginning of the frame so that they are at a
 * constant offset into the frame, rather than computing their positions from
 * the vector length and a negative offset.  However, I don't have time now to
 * figure out how difficult it would be do actually make this change and then
 * test it.  It *should* be quite trivial, as long as all code for building
 * method frames uses GENERIC_FUNCTION_CALL_START() and
 * SI_GENERIC_FUNCTION_CALL_END(), which I believe to be true (I certainly
 * *hope* I didn't bypass these anywhere -- one place to check might be
 * SI_internal_funcall()).  Assuming this to be correct, then those two macros
 * plus the macros for referencing the special fields are all that need to be
 * modified to make this change. -- kab, 10/27/91]
 * 
 * The reserved fields at the end of the frame are used for the following
 * purposes:
 *
 * SI_METHOD_FRAME_COPY_OFFSET
 *   A heap allocated copy of the frame, or Nil if such a copy has not been
 *   made.  This field is maintained by COPY_METHOD_FRAME.  A heap allocated
 *   copy of the frame is needed by upward references to CALL-NEXT-METHOD.
 *
 * SI_METHOD_FRAME_LIST_OFFSET
 *   A heap allocated list of all the arguments in the frame, or Nil if such a
 *   list has not been created.  This field is maintained by
 *   METHOD_ARGUMENT_LIST.  There are various circumstances in which a list of
 *   the arguments are required, typically involving calls to apply.  The list
 *   in this field may share toplevel list structure with the list found at
 *   SI_METHOD_FRAME_REST_OFFSET.
 *
 * SI_METHOD_FRAME_REST_OFFSET
 *   A heap allocated list of the non-positional arguments for the generic
 *   function, or Nil if the generic function does not accept non-positional
 *   arguments.  This field is initialized within the discriminator function
 *   for the generic function.  The list in this field may share toplevel list
 *   structure with the list found SI_METHOD_FRAME_LIST_OFFSET.  Note that the
 *   value of this field might not be properly initialized until after the 
 *   appropriate effective method has been located.
 *
 * SI_METHOD_FRAME_KEY_OFFSET
 *   A simple-vector containing the parsed keyword argument values, the the
 *   locations of the values specified by ordered keys vector in the effective
 *   method.  If the effective method does not accept keyword arguments (or the
 *   effective method has not yet been determined) the value of this field is
 *   Nil.  If the frame is stack allocated then the key value vector may be
 *   stack allocated, while if the frame is heap allocated then the key value
 *   vector will also be heap allocated.
 *
 * When the generic function is called, the discriminator function allocates
 * the frame on the stack and places the arguments linearly in the frame.  Once
 * the effective method has been computed, if it indicates that non-positional
 * arguments are permitted then the following steps are performed.
 *
 * 1. A list of the supplied non-positional arguments is collected and stored
 * in the REST_OFFSET field of the frame.  This collection may be performed by
 * using the tail of the value in the LIST_OFFSET field of the frame.
 *
 * 2. If the effective method mentions keywords then a vector for the parsed
 * key values is allocated, with all elements initially being unsupplied
 * markers, and stored in the KEY_OFFSET field of the frame.  The supplied
 * keywords are then parsed using the information from the effective method,
 * with the parsed values being recorded in the vector.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Accessing the arguments in a frame
 *
 * SI_METHOD_FRAME_REF(frame, index)	-- boxed index
 * SI_IMETHOD_FRAME_REF(frame, index)	-- unboxed index
 *   These macros are the basic primitives for accessing entries in a method
 *   argument frame, differing only in the handling of the second argument.
 *   These macros may be used as l-values.
 *
 *****************************************************************************/

#define SI_METHOD_FRAME_REF(frame, index)	SVREF(frame, index)
#define SI_IMETHOD_FRAME_REF(frame, index)	SI_ISVREF(frame, index)

/******************************************************************************
 *
 * Accessing the internal fields of a frame.
 *
 * SI_METHOD_FRAME_LAST(frame)
 * SI_METHOD_FRAME_COPY(frame)
 * SI_METHOD_FRAME_LIST(frame)
 * SI_METHOD_FRAME_REST(frame)
 * SI_METHOD_FRAME_KEY(frame)
 *   These macros return the corresponding fields from the frame.  They may be
 *   used as l-values.
 *
 *****************************************************************************/

enum {
    SI_METHOD_FRAME_LAST_OFFSET	= -5L,	/* position of last argument */
    SI_METHOD_FRAME_COPY_OFFSET,
    SI_METHOD_FRAME_LIST_OFFSET,
    SI_METHOD_FRAME_REST_OFFSET,
    SI_METHOD_FRAME_KEY_OFFSET
};

/* Number of internal fields.
 * This ought to be something like
 *    (-(SI_METHOD_FRAME_LAST_OFFSET + 1))
 * but I want the C preprocessor to be able to fully expand this definition,
 * and cpp doesn't process enums.
 */
#define SI_METHOD_FRAME_INTERNAL_FIELDS	4L

#define SI_METHOD_FRAME_INTERNAL_FIELD(frame, offset) \
    SI_IMETHOD_FRAME_REF(frame, \
			 SI_PRIMITIVE_VECTOR_LENGTH(frame)+(SI_Long)offset)

#define SI_METHOD_FRAME_LAST(frame) \
    SI_METHOD_FRAME_INTERNAL_FIELD(frame, SI_METHOD_FRAME_LAST_OFFSET)

#define SI_METHOD_FRAME_COPY(frame) \
    SI_METHOD_FRAME_INTERNAL_FIELD(frame, SI_METHOD_FRAME_COPY_OFFSET)

#define SI_METHOD_FRAME_LIST(frame) \
    SI_METHOD_FRAME_INTERNAL_FIELD(frame, SI_METHOD_FRAME_LIST_OFFSET)

#define SI_METHOD_FRAME_REST(frame) \
    SI_METHOD_FRAME_INTERNAL_FIELD(frame, SI_METHOD_FRAME_REST_OFFSET)

#define SI_METHOD_FRAME_KEY(frame) \
    SI_METHOD_FRAME_INTERNAL_FIELD(frame, SI_METHOD_FRAME_KEY_OFFSET)

#define SI_METHOD_FRAME_INTERNAL_FIELD_INIT	ZERO
#define SI_METHOD_FRAME_INTERNAL_FIELD_INITIALIZED(v) \
    ((v) != SI_METHOD_FRAME_INTERNAL_FIELD_INIT)

/******************************************************************************
 *
 * Accessing arguments in the frame.
 *
 * METHOD_ARGUMENT(frame, index)	-- boxed index
 * IMETHOD_ARGUMENT(frame, index)	-- unboxed index
 *   These macros are used to access arguments within the frame, differing only
 *   in the handling of the second argument.  The index argument specifies the
 *   argument position to be accessed.  These macros may be used as l-values.
 *
 *****************************************************************************/

#define METHOD_ARGUMENT(frame, index)	SI_METHOD_FRAME_REF(frame, index)
#define IMETHOD_ARGUMENT(frame, index)	SI_IMETHOD_FRAME_REF(frame, index)

/******************************************************************************
 *
 * Testing for the presence of optional arguments.
 *
 * METHOD_OPTIONAL_ARGUMENT_P(argq, index)	-- boxed index
 * IMETHOD_OPTIONAL_ARGUMENT_P(argq, index)	-- unboxed index
 *   These macros test whether a specified optional argument was supplied.
 *   This test is performed by comparing the argument position with the number
 *   of method arguments actually received.  The result of these macros is an
 *   unboxed boolean which is true if the argument was supplied and false
 *   otherwise. 
 *
 * Note: Box index rather than unboxing argq, since argq is invariably a
 * variable while index is typically a constant, which will permit the C
 * compiler to constant fold the boxing operation.
 *
 *****************************************************************************/

#define METHOD_OPTIONAL_ARGUMENT_P(argq, index)	  FIXNUM_GT(argq, index)
#define IMETHOD_OPTIONAL_ARGUMENT_P(argq, index)  FIXNUM_GT(argq, FIX(index))

/******************************************************************************
 *
 * Accessing the &REST list.
 *
 * Declare_method_rest
 *   Declare local temp used by METHOD_REST_LIST.
 *
 * METHOD_REST_LIST(em, frame, argq)
 *   Access the list of non-positional arguments in the frame.  A
 *   Declare_method_rest declaration must be visible in the scope where this
 *   macro is used.
 *
 *****************************************************************************/

#define Declare_method_rest	Object SI_Method_rest_value

#define METHOD_REST_LIST(em, frame, argq) \
    (SI_Method_rest_value = SI_METHOD_FRAME_REST(frame), \
     SI_METHOD_FRAME_INTERNAL_FIELD_INITIALIZED(SI_Method_rest_value) \
	? SI_Method_rest_value \
	: SI_compute_method_frame_rest(em, frame, argq))

/******************************************************************************
 *
 * Accessing and testing for &KEY arguments.
 *
 * METHOD_KEY_VALUE(frame, key_table, key_index)
 *   This macro gets the value associated with a keyword from the frame.  The
 *   value for each keyword mentioned by any method in the effective method is
 *   placed in a canonical location in the frame.  Each method has associated
 *   with it a permutation vector that maps from the ordered set of keywords
 *   mentioned by the method onto the canonical positions for the effective
 *   method.  The key_index is an unboxed fixnum.
 *
 * Note: This function currently receives the frame rather than the key value
 * table directly.  This is because at one time the values were stored directly
 * in the frame, rather than being indirected as they are now.  In order to
 * change this the translated code would have to be modified somewhat.  Since
 * some of this design is still not definitely finalized, I decided to leave
 * the extra indirection rather than change the translation code.  This may
 * change at some future date.
 *
 * METHOD_KEY_P(value)
 *   This macro is a predicate which returns an unboxed boolean value.  It
 *   returns true if the value is not an unsupplied marker.
 *
 * These two macros are used in combination in the processing of keyword
 * arguments.  The value for the keyword is obtained from the frame by calling
 * METHOD_KEY_VALUE.  That value is tested using METHOD_KEY_P.  If the test
 * returns true, then the variable associated with the keyword is bound to the
 * value.  Otherwise, the variable is bound to the result of evaluating its
 * associated initform.
 *
 *****************************************************************************/

#define METHOD_KEY_VALUE(frame, key_table, key_index) \
    SVREF(SI_METHOD_FRAME_KEY(frame), SI_ISVREF(key_table, key_index))

#define METHOD_KEY_P(value)	!EQ(value, _)

/******************************************************************************
 *
 * void SI_ADJUST_METHOD_FRAME_ARGQ(frame, n)
 *   Object frame;
 *   int n;
 *
 *   Adjust the value of n to be the number of actual arguments in the frame.
 *   This may differ from the value determined by simply subtracting the number
 *   of internal fields from the length of the frame, due to the presence of
 *   trailing unsupplied markers.
 *
 *****************************************************************************/

#define SI_ADJUST_METHOD_FRAME_ARGQ(frame, n) \
    do { \
      Object SI_frame = (frame); \
      int SI_n = (n); \
 \
      while (0 < SI_n--) \
	if (IMETHOD_ARGUMENT(SI_frame, SI_n) != KOPT) break; \
      (n) = SI_n+1; \
    } while (0)

/******************************************************************************
 *
 * Stack allocation of method frames.
 * 
 * void GENERIC_FUNCTION_CALL_START()
 *   Reserves sufficient space on the Lisp stack for a simple-vector header,
 *   along with any necessary alignment.  The alignment word used is special
 *   for this purpose (SI_METHOD_FRAME_ALIGN_MARKER) so that it can be
 *   specifically recognized when removing the frame.
 *
 * void GENERIC_FUNCTION_CALL_ARG(o)
 * Object o;
 *   Pushes an argument onto the Lisp stack.  It will become an element in the
 *   method frame being built.
 *
 * Object SI_GENERIC_FUNCTION_CALL_END(nargs)
 * int nargs;
 *   Initialize internal fields of the method frame being built.
 *
 * Object SI_GENERIC_FUNCTION_CALL_USING_FRAME(fn, nargs, frame, sp)
 * Object fn, frame;
 * int nargs;
 * SI_Stack_item *sp;
 *
 * Object SI_GENERIC_FUNCTION_CALL(fn, nargs, sp)
 * Object fn;
 * int nargs;
 * SI_Stack_item *sp;
 *
 * Object GENERIC_FUNCTION_CALL(fn, nargs)
 * Object fn;
 * int nargs;
 *   Calls the specified Lisp function object with two arguments, the number of
 *   arguments (nargs) and the method frame currently on the top of the Lisp
 *   stack.  The number of arguments and the current stack pointer are used to
 *   find the start of the method frame.
 *
 * void SI_REMOVE_METHOD_FRAME(frame, sp)
 * Object f;
 * Stack_item sp;
 *   Sets the current stack pointer to remove the frame from the stack, and
 *   additionally removes any immediately preceeding method alignment marker.
 *
 *****************************************************************************/

#define GENERIC_FUNCTION_CALL_START()	SI_START_PUSHING_OBJECT_VECTOR()
#define GENERIC_FUNCTION_CALL_ARG(o)	STACK_PUSH(o)

#ifdef SI_RUNTIME_INTERNAL
#define SI_REMOVE_METHOD_FRAME(f,sp) \
    if (sp == (SI_Stack_item *)NULL) SI_POP_OBJECT_VECTOR(f); \
    else Stack = sp
#endif

/* Note that the number of extra pushes here is hard-wired to the value of
 * SI_METHOD_FRAME_INTERNAL_FIELDS.
 */
#if (SI_METHOD_FRAME_INTERNAL_FIELDS != 4)
#  include "Mismatch on number of internal fields in method frame."
#endif

#define SI_GENERIC_FUNCTION_CALL_END() \
    (STACK_REF(0) = STACK_REF(1) = STACK_REF(2) = STACK_REF(3) = \
         SI_METHOD_FRAME_INTERNAL_FIELD_INIT, \
     Stack += SI_METHOD_FRAME_INTERNAL_FIELDS)

#define SI_GENERIC_FUNCTION_CALL_FRAME(n) \
    (SI_FINISH_PUSHING_OBJECT_VECTOR((n)+SI_METHOD_FRAME_INTERNAL_FIELDS))

#define SI_GENERIC_FUNCTION_CALL_USING_FRAME(f, n, frame, sp) \
    (SI_FUNCTION_ENTRY(SI_Called_function = (f)))(n, frame, sp)

#define SI_GENERIC_FUNCTION_CALL(f,n,sp) \
    SI_GENERIC_FUNCTION_CALL_USING_FRAME(f, n,\
					 SI_GENERIC_FUNCTION_CALL_FRAME(n), \
					 sp)

#define GENERIC_FUNCTION_CALL(f, n) \
    (SI_GENERIC_FUNCTION_CALL_END(), \
     SI_GENERIC_FUNCTION_CALL(f, n, (SI_Stack_item *)NULL))

/* This could be made smaller if we could depend on "fn" not consing.
 * Unfortunately, the current implementation for the F macros for SETF
 * functions may cons, so we have to make sure that the arguments have been put
 * someplace visible to the gc before executing "fn".  An advantage of this
 * definition over one which passes a va_list pointer to the discriminator is
 * that this version can tail to the discriminator, whereas a va_list pointer
 * passing version would have to receive the values, call va_end(), and then
 * return the received values.  Also, by having the argument stacking done here
 * we can reduce the number of discriminator functions needed.
 */
#define DEFINE_VARIADIC_GENERIC_FUNCTION(entry, fn) \
/*VARARGS*/ \
Object entry varargs_1(long, SI_n) \
{ static Object SI_function = UNBOUND; \
  va_list SI_ap; \
  long SI_i; \
  SI_Stack_item *SI_sp = Stack; \
 \
  GENERIC_FUNCTION_CALL_START(); \
  /* Increment stack once up front, rather than in loop. */ \
  SI_va_start(SI_ap,SI_n); \
  for (SI_i = 0; SI_i < SI_n; SI_i++) \
    STACK_REF(SI_i) = va_arg(SI_ap, Object); \
  va_end(SI_ap); \
  Stack += SI_i; \
  SI_GENERIC_FUNCTION_CALL_END(); \
  /* Only evaluate fn once on first time through. */ \
  if (SI_function == UNBOUND) { \
    PROTECT_GLOBAL(SI_function); \
    SI_function = fn; \
  } \
  return SI_GENERIC_FUNCTION_CALL(SI_function, SI_n, SI_sp); \
}
      
/*** These should be generated by a program! ***/

#define GENERIC_FUNCTION_CALL_1(fn,a) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL(fn,1))

#define GENERIC_FUNCTION_CALL_2(fn,a,b) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL(fn,2))

#define GENERIC_FUNCTION_CALL_3(fn,a,b,c) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL(fn,3))

#define GENERIC_FUNCTION_CALL_4(fn,a,b,c,d) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL(fn,4))

#define GENERIC_FUNCTION_CALL_5(fn,a,b,c,d,e) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL_ARG(e), \
     GENERIC_FUNCTION_CALL(fn,5))

#define GENERIC_FUNCTION_CALL_6(fn,a,b,c,d,e,f) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL_ARG(e), \
     GENERIC_FUNCTION_CALL_ARG(f), \
     GENERIC_FUNCTION_CALL(fn,6))

#define GENERIC_FUNCTION_CALL_7(fn,a,b,c,d,e,f,g) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL_ARG(e), \
     GENERIC_FUNCTION_CALL_ARG(f), \
     GENERIC_FUNCTION_CALL_ARG(g), \
     GENERIC_FUNCTION_CALL(fn,7))

#define GENERIC_FUNCTION_CALL_8(fn,a,b,c,d,e,f,g,h) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL_ARG(e), \
     GENERIC_FUNCTION_CALL_ARG(f), \
     GENERIC_FUNCTION_CALL_ARG(g), \
     GENERIC_FUNCTION_CALL_ARG(h), \
     GENERIC_FUNCTION_CALL(fn,8))

#define GENERIC_FUNCTION_CALL_9(fn,a,b,c,d,e,f,g,h,i) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL_ARG(e), \
     GENERIC_FUNCTION_CALL_ARG(f), \
     GENERIC_FUNCTION_CALL_ARG(g), \
     GENERIC_FUNCTION_CALL_ARG(h), \
     GENERIC_FUNCTION_CALL_ARG(i), \
     GENERIC_FUNCTION_CALL(fn,9))

#define GENERIC_FUNCTION_CALL_10(fn,a,b,c,d,e,f,g,h,i,j) \
    (GENERIC_FUNCTION_CALL_START(), \
     GENERIC_FUNCTION_CALL_ARG(a), \
     GENERIC_FUNCTION_CALL_ARG(b), \
     GENERIC_FUNCTION_CALL_ARG(c), \
     GENERIC_FUNCTION_CALL_ARG(d), \
     GENERIC_FUNCTION_CALL_ARG(e), \
     GENERIC_FUNCTION_CALL_ARG(f), \
     GENERIC_FUNCTION_CALL_ARG(g), \
     GENERIC_FUNCTION_CALL_ARG(h), \
     GENERIC_FUNCTION_CALL_ARG(i), \
     GENERIC_FUNCTION_CALL_ARG(j), \
     GENERIC_FUNCTION_CALL(fn,10))

