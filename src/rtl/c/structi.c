/*
 * structi.c - lazily initialized handlers for dynamic structures.
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

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif



/* Interface to the trivial (empty) structure system 
 * Any of the handlers, if called, indicate a setup/translation error */


Object SI_find_structure_print_function_short(str)
  Object	str;
{ 
  /* the situation should never happen. Indicates a bug */
  (void)error(1,"No structure object created yet.Can't get a print function");
  /*NONREACHED*/
  return NIL;
}

Object SI_find_structure_constructor_short(str)
  Object	str;
{ 
  /* the situation should never happen. Indicates a bug */
  (void)error(1,"No structure object created yet.Can't get a constructor");
  /*NONREACHED*/
  return NIL;
}

Object SI_find_structure_header_short(str)
  Object	str;
{ 
  /* the situation should never happen. Indicates a bug */
  (void)error(1, "No structure object created yet. Cannot get a header");
  /*NONREACHED*/
  return NIL;
}

Object (*SI_find_structure_print_function_fptr)(/*Object name*/) = 
	SI_find_structure_print_function_short;
Object (*SI_find_structure_constructor_fptr)(/*Object name*/) = 
	SI_find_structure_constructor_short;
Object (*SI_find_structure_header_fptr)(/*Object name*/) = 
	SI_find_structure_header_short;


/* actual interface to the full (hash-based) struct system (file struct.c):

reader: Object SI_find_structure_constructor(str) 
printer: Object SI_find_structure_print_function(str) 
heap: Object SI_find_structure_header(name)
user code: Object make_structure_class(name, super, slots, printer, doc)
old init.c: void SI_INIT_structure_class()

the following are hooks for the full type system:
Object SI_structure_type_specifier_p(symbol)
int SI_structure_typep(thing, info)
int SI_structure_subtypep(info1, info2)
*/

void SI_structi_ENSURE() {}
