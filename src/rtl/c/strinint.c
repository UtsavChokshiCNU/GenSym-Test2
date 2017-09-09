/*
 * strinint.c - the core string manipulation routines
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

extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_malloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern long ilength(Object sequence);
extern char *isymbol_name(Object sym);
extern Object string(Object);
extern Object make_string(Object size, Object initial_element);
extern Object g2rtl_make_malloced_string();
extern void *SI_array_contents(Object);

#else

extern Object SI_alloc_primitive_vector();
extern Object SI_malloc_primitive_vector();
extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern long ilength();
extern char *isymbol_name();
extern Object string();
extern Object make_string();
extern void *SI_array_contents();

#endif



char *SI_string_base (o)		/* Cf. aref */
  Object o;
{
  extern void g2ext_print_backtrace();
  SI_Dimension i = 0;
  Object arg = o;

  while (!SIMPLE_STRING_P(o)) {
    if (!SI_GENERAL_ARRAY_P(o)) {
      g2ext_print_backtrace();
      (void)error(2, "SI_istring: invalid argument - ~S", arg);
    }
    i += IFIX(SI_DISPLACED_INDEX_OFFSET(o));
    o = SI_GENERAL_ARRAY_DISPLACED_TO(o);
  }
  return &SI_ISCHAR(o, i);
}

/* SI_istring(x) is the same as ISTRING(x), and also the same as
   SI_string_base(string(x)).  Cf. X3J13 issue STRING-COERCION. */

char *SI_istring (o)
  Object o;
{
    Declare_local_temp;
  SI_Dimension i = 0;
  Object arg = o;

  if (!SIMPLE_STRING_P(o)) {
    if (SYMBOLP(o))
      return isymbol_name(o);
    if (CHARACTERP(o))
      o = make_string(FIX(1L), o);
    return (char *)SI_array_contents(o);
  }
  return &SI_ISCHAR(o, i);
}

/* make-string size &key initial-element */

Object make_string (size, initial_element)
    Object size;
    Object initial_element;
{
    Declare_local_temp;
    SI_Dimension len;
    Object result;

    if (!FIXNUMP(size))
	warn(2, "make-string: non-fixnum size - ~S", size);
    len = IFIX(size);
    result = SI_alloc_primitive_vector(len, A_STRING_CHAR);
    if (SUPPLIEDP(initial_element))
	(void)memset(&SI_ISCHAR(result, 0),
		     (int) ICHAR_CODE(initial_element),
		     (int) len);
    return VALUES_1(result);
}    

Object make_malloced_string (len)
    SI_Dimension len;
{

    Object result;
    /*
    fprintf(stderr, "About to call SI_malloc_primitive_vector on length %ld\n",    (long)len);
    */
    result = SI_malloc_primitive_vector(len, A_STRING_CHAR);
    /*
    fprintf(stderr, "SI_malloc_primitive_vector returned %lx\n",    (long)result);
    */
    return VALUES_1(result);
}    

Object make_duplicate_string (oldstring)
    Object oldstring;
{
    Declare_local_temp;
    Object newstring;
    SI_Dimension len;
    char *s;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(oldstring);
    PROTECTI_1(newstring);

    oldstring = STRING(oldstring);
    len = ilength(oldstring);
    newstring = make_string(FIX(len), KOPT);
    s = SI_string_base(oldstring);
    MEMCPY(&SI_ISCHAR(newstring, 0), s, (int)len);
    RESTORE_STACK();
    return VALUES_1(newstring);
}

/* Warning - oldstring had better not point into the array heap. */

Object imake_duplicate_string (oldstring)
    char *oldstring;
{
    Declare_local_temp;
    Object newstring;
    int len = (int)strlen(oldstring);

    newstring = make_string(FIX(len), KOPT);
    MEMCPY(&SI_ISCHAR(newstring, 0), oldstring, len);
    return VALUES_1(newstring);
}

