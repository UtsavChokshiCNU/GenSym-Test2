/*
 * biginit2.c -  Bignum initialization routines
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
extern SI_Area Local_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc_bignum(SI_Dimension length);
extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_alloc(SI_Size_type size, int align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern enum bignum_comparison (*SI_bignum_compare)();
extern Object (*SI_long_to_bignum)();
extern enum bignum_comparison bignum_compare (bignum_type, bignum_type);
extern bignum_type long_to_bignum (SI_Long);
extern Object SI_alloc_bignum_vector(SI_Dimension numelems, enum SI_etype etype);

#else

extern Object SI_alloc_bignum();
extern Object SI_alloc_primitive_vector();
extern Object SI_alloc();
extern enum bignum_comparison (*SI_bignum_compare)();
extern Object (*SI_long_to_bignum)();
extern enum bignum_comparison bignum_compare ();
extern bignum_type long_to_bignum ();
extern Object SI_alloc_bignum_vector();

#endif


#include "bignmint.h"

bignum_type
bignum_make_zero ()
{
  fast bignum_type result = (BIGNUM_ALLOCATE (0));
  BIGNUM_SET_HEADER (result, 0, 0);
  return (result);
}
 
bignum_type
bignum_make_one (negative_p)
     int negative_p;
{
  fast bignum_type result = (BIGNUM_ALLOCATE (1));
  BIGNUM_SET_HEADER (result, 1, negative_p);
  (BIGNUM_REF (result, 0)) = 1;
  return (result);
}

void SI_INIT_new_bignums()
{ Declare_area(a);

  /* set up the handlers */
  SI_long_to_bignum = long_to_bignum;
  SI_bignum_compare = bignum_compare;
  
  SAVE_CURRENT_AREA(a);
  SET_CURRENT_AREA(Static_area);
  SI_static_bignum_zero = bignum_make_zero();
  SI_static_bignum_one = bignum_make_one(0);
  SI_static_bignum_negative_one = bignum_make_one(1);
  RESTORE_CURRENT_AREA(a);
}
 
/*
 * Chestnut comment
 * used only by SI_alloc_bignum() in bignums.c that do not include "runtime.h"
 */
/*
 * jh, 4/22/94.  Modified SI_allocate_bignum() to call the newly-minted
 * SI_alloc_bignum_vector() instead of SI_alloc_primitive_vector().  These
 * functions are identical except that SI_alloc_bignum_vector() does not warn if
 * it is called inside a temporary area, since Gensym code expects to do that
 * from time to time.
 */
Object SI_allocate_bignum (length)
    SI_Dimension length;
{
    Object digits, num;
    Declare_stack_pointer;
    Declare_area(area);

    SAVE_STACK();

    SAVE_CURRENT_AREA(area);
    SET_CURRENT_AREA(Local_area);
    /* Gensym modification */
    digits = (Object)SI_alloc_bignum_vector(length, A_BYTE_32);
    PROTECT_1(digits); /* now that digits is initialized */

    num = SI_ALLOC(SI_Bignum, XBIGNUM_TYPE, SI_NUMBER_TAG, SI_NORMAL);
    SI_STORED_OBJECT_FIELD(num, SI_Bignum, digits) = digits;
    SI_STORED_OBJECT_FIELD(num, SI_Bignum, length) = FIX(length);
    RESTORE_CURRENT_AREA(area);

    RESTORE_STACK();
    return num;
}

