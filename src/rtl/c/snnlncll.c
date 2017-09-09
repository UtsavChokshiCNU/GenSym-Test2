/*
 * snnlncll.c -  Chestnut Run-Time Library entry for function SI_internal_funcall
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object SI_Called_function;

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object (*SI_errorn_fptr) (long,...);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object cons(Object,Object);
extern Object istring_to_string(char *istring);
extern Object string_append2(Object a, Object b);

#else

extern void SI_add_external_root();
extern Object (*SI_errorn_fptr) ();
extern Object SI_symbol_field();
extern Object cons();
extern Object istring_to_string();
extern Object string_append2();

#endif


#include "funcall.h"

FORWARD_STATIC void unsupported_number_of_arguments_error();

Object SI_internal_funcall (original_function, args_on_stack, arglist)
  Object original_function, arglist;
  long args_on_stack;
{
    Declare_local_temp;
  Object *argp = &STACK_REF(-args_on_stack);
  Object function, env, value;
  Object (*fpoint)();
  long arg_count, fixed_vc = -1;
  extern Object apply_lambda();
  
  /* Stack remaining arguments. */
  for ( ; CONSP(arglist); args_on_stack++, arglist = M_CDR(arglist))
    STACK_PUSH(M_CAR(arglist));

  RESOLVE_FUNCALLABLE_OBJECT(original_function, function);

#if SI_SUPPORT_CLOS
  if (SI_FUNCTION_GENERIC_P(function)) {
    /* Open a generic function call frame. */
    GENERIC_FUNCTION_CALL_START();
    /* Copy stacked arguments into the frame. */
    (void)MEMCPY((char *)&STACK_REF(0),
		 (char *)argp,
		 args_on_stack * sizeof(Object));
    Stack += args_on_stack;
    SI_GENERIC_FUNCTION_CALL_END();
    /* Invoke discriminator on the frame.  Pass in argp so discriminator can
     * clean up stack, removing arguments stacked before the frame. */
    return SI_GENERIC_FUNCTION_CALL(function, args_on_stack, argp);
  }
#endif /* SI_SUPPORT_CLOS */

  if(FIXNUMP(env = SI_FUNCTION_ENV(function)))
    fixed_vc = IFIX(env);

  if (SI_FUNCTION_VARIADIC_P(function)) {
    fpoint = SI_FUNCTION_ENTRY(function);
    Stack -= args_on_stack;
    /* Implementation note: For large numbers of arguments, the actual number
     * of arguments passed to the function may be more than the number
     * indicated by args_on_stack, with the values of the extra arguments being
     * garbage from the stack.  This is ok from the point of view of the GC,
     * since the count argument controls how many items are going to be
     * extracted from the varargs buffer by the receiver, so the extra garbage
     * arguments will just be ignored.  There is however a small danger here in
     * that if we are near the end of the stack and the end of the stack is
     * near some system boundary (like the end of the address space), then the
     * accesses to the bogus values could cause hardware traps and the like.
     * The chances of this occuring seem pretty small though.  The alternative
     * is to have more exact cases.  Hm.. In the time it's taken me to write
     * this comment I could have added many more exact cases.  Oh well. */
    if(fixed_vc<0 && args_on_stack<=6) {
      switch (args_on_stack) {
      case 0:
	return (*fpoint)(0);
      case 1:
	return (*fpoint)(1,argp[0]);
      case 2:
	return (*fpoint)(2,argp[0],argp[1]);
      case 3:
	return (*fpoint)(3,argp[0],argp[1],argp[2]);
      case 4:
	return (*fpoint)(4,argp[0],argp[1],argp[2],argp[3]);
      case 5:
	return (*fpoint)(5,argp[0],argp[1],argp[2],argp[3],argp[4]);
      case 6:
	return (*fpoint)(6,argp[0],argp[1],argp[2],argp[3],argp[4],argp[5]);
      }
    }
    else {
      switch (args_on_stack) {
      case 0:
	value = (*fpoint)(0);
	break;
      case 1:
	value = (*fpoint)(1,argp[0]);
	break;
      case 2:
	value = (*fpoint)(2,argp[0],argp[1]);
	break;
      case 3:
	value = (*fpoint)(3,argp[0],argp[1],argp[2]);
	break;
      case 4:
	value = (*fpoint)(4,argp[0],argp[1],argp[2],argp[3]);
	break;
      case 5:
	value = (*fpoint)(5,argp[0],argp[1],argp[2],argp[3],argp[4]);
	break;
      case 6:
	value = (*fpoint)(6,argp[0],argp[1],argp[2],argp[3],argp[4],argp[5]);
	break;
      case 7:
	value = (*fpoint)(7,argp[0],argp[1],argp[2],argp[3],argp[4],argp[5],
		  argp[6]);
	break;
      case 8:
	value = (*fpoint)(8,argp[0],argp[1],argp[2],argp[3],argp[4],argp[5],
		  argp[6],argp[7]);
	break;
      case 9:
	value = (*fpoint)(9,argp[0],argp[1],argp[2],argp[3],argp[4],argp[5],
		  argp[6],argp[7],argp[8]);
	break;
      case 10:
	value = (*fpoint)(10,argp[0],argp[1],argp[2],argp[3],argp[4],argp[5],
		  argp[6],argp[7],argp[8],argp[9]);
	break;
      case 11: case 12: case 13: case 14: case 15:
	value = (*fpoint)(args_on_stack,
		  argp[0],argp[1],argp[2],argp[3],argp[4],
		  argp[5],argp[6],argp[7],argp[8],argp[9],
		  argp[10],argp[11],argp[12],argp[13],argp[14]);
	break;
      case 16: case 17: case 18: case 19: case 20:
	value = (*fpoint)(args_on_stack,
		  argp[0],argp[1],argp[2],argp[3],argp[4],
		  argp[5],argp[6],argp[7],argp[8],argp[9],
		  argp[10],argp[11],argp[12],argp[13],argp[14],
		  argp[15],argp[16],argp[17],argp[18],argp[19]);
	break;
      case 21: case 22: case 23: case 24: case 25:
      case 26: case 27: case 28: case 29: case 30:
	value = (*fpoint)(args_on_stack,
		  argp[0],argp[1],argp[2],argp[3],argp[4],
		  argp[5],argp[6],argp[7],argp[8],argp[9],
		  argp[10],argp[11],argp[12],argp[13],argp[14],
		  argp[15],argp[16],argp[17],argp[18],argp[19],
		  argp[20],argp[21],argp[22],argp[23],argp[24],
		  argp[25],argp[26],argp[27],argp[28],argp[29]);
	break;
      case 31: case 32: case 33: case 34: case 35:
      case 36: case 37: case 38: case 39: case 40:
	value = (*fpoint)(args_on_stack,
		  argp[0],argp[1],argp[2],argp[3],argp[4],
		  argp[5],argp[6],argp[7],argp[8],argp[9],
		  argp[10],argp[11],argp[12],argp[13],argp[14],
		  argp[15],argp[16],argp[17],argp[18],argp[19],
		  argp[20],argp[21],argp[22],argp[23],argp[24],
		  argp[25],argp[26],argp[27],argp[28],argp[29],
		  argp[30],argp[31],argp[32],argp[33],argp[34],
		  argp[35],argp[36],argp[37],argp[38],argp[39]);
	break;
      default:
	unsupported_number_of_arguments_error(args_on_stack,original_function);
	/*NOTREACHED*/
      }
      if(fixed_vc>0)
	Values_count = fixed_vc;
      return value;
    }
  }

  if (!SI_FUNCTION_SIMPLE_P(function)) {
    arg_count = SI_FUNCTION_NARGS(function);
    /* Push unsupplied markers for unsupplied positional arguments. */
    for ( ; args_on_stack < arg_count; args_on_stack++) STACK_PUSH(KOPT);

#if SI_SUPPORT_MF
    if (FUNC_REST_P(function)) {
      arglist = NIL;
      while (args_on_stack-- > arg_count) {
	Object arg = STACK_POP();
	arglist = cons(arg, arglist);
      }
      STACK_PUSH(arglist);
      args_on_stack++;
      function = SI_Called_function;	/* In case function moved by GC. */
    }
#endif /* SI_SUPPORT_MF */
  }

  /* Now do the call. */
  fpoint = SI_FUNCTION_ENTRY(function);
  Stack -= args_on_stack;
  if( fixed_vc<0 && args_on_stack<=6 ) {
    switch (args_on_stack) {
    case 0:
      return (*fpoint)();
    case 1:
      return (*fpoint)(argp[0]);
    case 2:
      return (*fpoint)(argp[0],argp[1]);
    case 3:
      return (*fpoint)(argp[0],argp[1],argp[2]);
    case 4:
      return (*fpoint)(argp[0],argp[1],argp[2],argp[3]);
    case 5:
      return (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4]);
    case 6:
      return (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],argp[5]);
    }
  }
  else {
    switch (args_on_stack) {
    case 0:
      value = (*fpoint)();
      break;
    case 1:
      value = (*fpoint)(argp[0]);
      break;
    case 2:
      value = (*fpoint)(argp[0],argp[1]);
      break;
    case 3:
      value = (*fpoint)(argp[0],argp[1],argp[2]);
      break;
    case 4:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3]);
      break;
    case 5:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4]);
      break;
    case 6:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],argp[5]);
      break;
    case 7:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6]);
      break;
    case 8:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7]);
      break;
    case 9:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8]);
      break;
    case 10:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9]);
      break;
    case 11:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10]);
      break;
    case 12:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11]);
      break;
    case 13:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12]);
      break;
    case 14:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13]);
      break;
    case 15:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13],argp[14]);
      break;
    case 16:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13],argp[14],
			argp[15]);
      break;
    case 17:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13],argp[14],
			argp[15],argp[16]);
      break;
    case 18:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13],argp[14],
			argp[15],argp[16],argp[17]);
      break;
    case 19:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13],argp[14],
			argp[15],argp[16],argp[17],argp[18]);
      break;
    case 20:
      value = (*fpoint)(argp[0],argp[1],argp[2],argp[3],argp[4],
			argp[5],argp[6],argp[7],argp[8],argp[9],
			argp[10],argp[11],argp[12],argp[13],argp[14],
			argp[15],argp[16],argp[17],argp[18],argp[19]);
      break;
    default:
      unsupported_number_of_arguments_error(args_on_stack, original_function);
      /*NOTREACHED*/
    }
    if(fixed_vc>0)
      Values_count = fixed_vc;
    return value;
  }
  return NULL; //this function return somthing
}

/* If application requires it, the cases that call this can be augmented up to
 * CALL-ARGUMENTS-LIMIT.  Note however that ANSI C only guarantees support for
 * up to 31 arguments. */

/* Some compilers don't support ANSI string concatenation.  Using line
 * continuations in strings screws up some source level debuggers.  Seems
 * like you just can't win. */
static Object Unsupported_argq_error_string = UNBOUND;
static char *Unsupported_argq_error_cstrings[2] =
  { "Internal error: Attempt to APPLY or FUNCALL ~S with more arguments\n",
    "than supported by the Translator.  Please contact Technical Support." };

/*ARGSUSED*/
static void unsupported_number_of_arguments_error(args_on_stack, function)
  long args_on_stack;
  Object function;
{
  if (Unsupported_argq_error_string == UNBOUND) {
    Object temp;

    PROTECT_GLOBAL(Unsupported_argq_error_string);
    Unsupported_argq_error_string =
      istring_to_string(Unsupported_argq_error_cstrings[0]);
    temp = istring_to_string(Unsupported_argq_error_cstrings[1]);
    Unsupported_argq_error_string =
      string_append2(Unsupported_argq_error_string, temp);
  }

  (void)errorn(2, Unsupported_argq_error_string, function);
  /*NOTREACHED*/
}
