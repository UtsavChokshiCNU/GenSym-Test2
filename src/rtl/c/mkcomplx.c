/*
 * mkcomplx.c -  Chestnut Run-Time Library entry for function make_complex
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);

#else

extern Object SI_alloc();

#endif



/* This is purely an allocator.
 * It does not deal with complex canonicalization.
 * Perhaps it should have an SI_ prefix.
 */
Object make_complex (r, i)
    Object r, i;
{
    Declare_local_temp;
    Object num;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(r,i);
    num = SI_ALLOC(SI_Complex, COMPLEX_TYPE, SI_NUMBER_TAG, SI_NORMAL);
    COMPLEX_REAL(num) = r;
    COMPLEX_IMAG(num) = i;
    RESTORE_STACK();
    return VALUES_1(num);
}
