/*
 * funcall.h - functional object invocation helper macros
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

/* to be used in SI_internal_funcall() and funcallN() */
extern void SI_bad_funcallable_error();

/* in operator context only */
#define RESOLVE_FUNCALLABLE_OBJECT(original_function, function) \
  /* Resolve function into a functional object. */ \
  function = original_function;				    \
  if (!SI_FUNCTIONP(function)) { \
    if (SYMBOLP(function)) \
      function = SYMBOL_FUNCTION(function); \
    if (!SI_FUNCTIONP(function))  \
	SI_bad_funcallable_error(function, original_function); \
    /*NOTREACHED*/ \
  } \
  /* For closures and generic functions. */ \
  SI_Called_function = function


/* here is how we take unsupplied optional arguments */
#define SI_FEWUA KOPT,KOPT,KOPT,KOPT
#define SI_NEEDS_FEW_UNSUPPLIED(f) (SI_FUNCTION_NARGS(f) < 5L)
#define SI_SUPPLY_UNSUPPLIED_ARGUMENTS() SI_FEWUA
#define SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS() SI_FEWUA,SI_FEWUA,SI_FEWUA,SI_FEWUA
