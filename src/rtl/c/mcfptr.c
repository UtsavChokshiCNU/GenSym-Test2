/*
 * mcfptr.c -  Chestnut Run-Time Library entry for function malloc_foreign_pointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kalignment;
extern Object Ktype;
extern Object Qforeign_type;
extern Object Qpointer_foreign_type;

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (int n, char *lstr, ...);
extern Object SI_keyword_arg_p(Object key, Object *args, long n);
extern Object get_foreign_type(Object,Object);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object SI_keyword_arg_p();
extern Object get_foreign_type();

#endif


Object malloc_foreign_pointer varargs_1(int, n)
{
    Object type_p, type, alignment_p;
    Object result = UNBOUND;
    long alignment;
    char *address;
    Declare_varargs;
    Declare_stack_pointer;

    SAVE_STACK();
    INIT_ARGS();
    SAVE_ARGS();
    type_p = KEYWORD_ARG_P(Ktype);
    type = type_p ? KEYWORD_ARG(type_p) : Nil;
    alignment_p = KEYWORD_ARG_P(Kalignment);
    alignment = alignment_p ? IFIX(KEYWORD_ARG(alignment_p)) : 1;
    PROTECT_1(type);
    if ( TRUEP(type) )
      type = FOREIGN_TYPE(type);
    else
      error(1,"malloc-foreign-pointer: :type is unspecified or nil");
    if ( !POINTER_FOREIGN_TYPE_P(type) )
      error(2,"malloc_foreign_pointer: ~S is not a :pointer type",type);
    {
      Object to_type = POINTER_FOREIGN_TYPE_TO_TYPE(type);
      unsigned long size = FOREIGN_TYPE_SIZE(to_type);
      unsigned short modulus = (unsigned short)FOREIGN_TYPE_MODULUS(to_type);
      unsigned short remainder = (unsigned short)FOREIGN_TYPE_REMAINDER(to_type);
      long align,diff;
      char *malloc_ptr,*mem_ptr;

      /* Bug: alignment and modulus must be powers of 2 */
      align = MAX(alignment,modulus);
      malloc_ptr = malloc(size + 2 + align);
      mem_ptr = malloc_ptr + 2 + align;
      address = (char *) (((unsigned long)mem_ptr) & ~(align - 1) + remainder);
      diff = (int)((unsigned long)address - ((unsigned long)malloc_ptr + 2));
      address[-2]=(char)(diff & 0xff);
      address[-1]=(char)(diff >> 8);
    }

    MAKE_FOREIGN_POINTER(result,(unsigned long)address,type);

    RESTORE_STACK();
    return VALUES_1(result);
}
