/*
 * mkfptr.c -  Chestnut Run-Time Library entry for function make_foreign_pointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object Kaddress;
extern Object Kalignment;
extern Object Kstatic;
extern Object Ktype;
extern Object Qforeign_type;
extern Object Qpointer_foreign_type;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern void *SI_array_contents(Object array);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_keyword_arg_p(Object key, Object *args, long n);
extern Object get_foreign_type(Object,Object);
extern SI_Ulong integer_to_unsigned_long(Object n);
extern Object malloc_foreign_pointer(int,...);

#else

extern Object SI_alloc_primitive_vector();
extern Object SI_alloc();
extern void *SI_array_contents();
extern Object (*SI_error_fptr) ();
extern Object SI_keyword_arg_p();
extern Object get_foreign_type();
extern SI_Ulong integer_to_unsigned_long();
extern Object malloc_foreign_pointer();

#endif



Object make_foreign_pointer varargs_1(int, n)
{
    Object address, address_p, type_p, type, static_p, alignment_p;
    Object result = UNBOUND;
    long alignment;
    char *addr;
    Declare_varargs;
    Declare_stack_pointer;
    Declare_area(a);

    SAVE_STACK();
    INIT_ARGS();
    SAVE_ARGS();
    address_p = KEYWORD_ARG_P(Kaddress);
    address = address_p ? KEYWORD_ARG(address_p) : FIX(0);
    type_p = KEYWORD_ARG_P(Ktype);
    type = type_p ? KEYWORD_ARG(type_p) : Nil;
    static_p = KEYWORD_ARG_P(Kstatic);
    alignment_p = KEYWORD_ARG_P(Kalignment);
    alignment = alignment_p ? IFIX(KEYWORD_ARG(alignment_p)) : 1;
    PROTECT_1(type);
    addr = (char *)INTEGER_TO_UNSIGNED_LONG(address);
    if ( TRUEP(type) ) {
      type = FOREIGN_TYPE(type);
      if ( !POINTER_FOREIGN_TYPE_P(type) )
	error(2,"make_foreign_pointer: ~S is not a :pointer type",type);
    }
    if ( !address_p ) {
      if ( !TRUEP(type) )
	error(1,"make-foreign-pointer: neither :type nor :address supplied");
      {
	Object to_type = POINTER_FOREIGN_TYPE_TO_TYPE(type);
	unsigned long size = FOREIGN_TYPE_SIZE(to_type);
	unsigned short modulus = (unsigned short)FOREIGN_TYPE_MODULUS(to_type);
	//unsigned short remainder = FOREIGN_TYPE_REMAINDER(to_type);
	long align;
	Object vector;

	/* Bug: supposed to use least common multiple here, not max */
	/* both are probably powers of 2, and it works in that case */
	align = MAX(alignment,modulus);
	switch (align)
	  { case 1:
	    case 2:
	    case 4:
	       break;
	     default:
	       RESTORE_STACK();
	       return malloc_foreign_pointer(4,Ktype,type,
					     Kalignment,alignment);
	     }
	      
	SAVE_CURRENT_AREA(a);
	SET_CURRENT_AREA(Static_area);
	vector = SI_alloc_primitive_vector (size,A_BYTE_8);
	addr = ((char *)SI_array_contents(vector));
        RESTORE_CURRENT_AREA(a);
      }
    }

    MAKE_FOREIGN_POINTER(result,(unsigned long)addr,type);

    RESTORE_STACK();
    return VALUES_1(result);
}
