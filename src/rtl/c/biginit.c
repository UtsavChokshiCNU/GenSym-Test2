/*
 * biginit.c - The core interface to bignum-handling module
 *             (gloal variables, configurable handlers)
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


#include "bignmint.h"

/* this file belongs in the core */

Object SI_static_bignum_zero = UNBOUND;
Object SI_static_bignum_one = UNBOUND;
Object SI_static_bignum_negative_one = UNBOUND;

Object SI_long_to_bignum_s (a)
    SI_Long a;
{
    (void) error(1, "The code requires bignums linked in.");
	return VALUES_1(NIL);
    /*NOTREACHED*/
}

/*ARGSUSED*/
enum bignum_comparison SI_bignum_compare_s (x, y)
    Object x, y;
{
    (void) error(1, "Bignum comparizon: bignums are not initialized");
	return bignum_comparison_equal;
    /*NOTREACHED*/
}

/* Lazily initialized, run time rebindable  bignum handlers.
 * In the current run-time system, it is guaranteed that a bignum could be
 *  created by calling or
 *  (1)  (*SI_long_to_bignum)() or
 *  (2)  clong_to_bignum() 
 */
Object (*SI_long_to_bignum)(/*SI_Long l*/) = 
	SI_long_to_bignum_s;

enum bignum_comparison (*SI_bignum_compare)(/*Object x, Object y*/) = 
	SI_bignum_compare_s;

Object clong_to_bignum (a)
    SI_Long a;
{
    return (*SI_long_to_bignum)(a);

}

int
bignum_fits_in_word_p (bignum, word_length, twos_complement_p)
     bignum_type bignum;
     long word_length;
     int twos_complement_p;
{
  unsigned int n_bits = (twos_complement_p ? (word_length - 1) : word_length);
  BIGNUM_ASSERT (n_bits > 0);
  {
    fast bignum_length_type length = (BIGNUM_LENGTH (bignum));
    fast unsigned int max_digits = (BIGNUM_BITS_TO_DIGITS (n_bits));
    bignum_digit_type msd, max;
    return
      ((length < (bignum_length_type)max_digits) ||
       ((length == max_digits) &&
	((((msd = (BIGNUM_REF (bignum, (length - 1)))) <
	   (max = ((SI_Long)1 << (n_bits - ((length - 1) * BIGNUM_DIGIT_LENGTH))))) ||
	  (twos_complement_p &&
	   (msd == max) &&
	   (BIGNUM_NEGATIVE_P (bignum)))))));
  }
}

SI_Long
bignum_to_long (bignum)
     bignum_type bignum;
{
  if (BIGNUM_ZERO_P (bignum))
    return (0);
  {
    fast SI_Ulong accumulator = 0;
    fast bignum_digit_type * start = (BIGNUM_START_PTR (bignum));
    fast bignum_digit_type * scan = (start + (BIGNUM_LENGTH (bignum)));
    while (start < scan)
      accumulator = (SI_Ulong)((accumulator << BIGNUM_DIGIT_LENGTH) + (*--scan));
    return ((BIGNUM_NEGATIVE_P (bignum)) ? (0 - accumulator) : accumulator);
  }
}

SI_int64
bignum_to_int64 (bignum)
     bignum_type bignum;
{
  if (BIGNUM_ZERO_P (bignum))
    return (0);
  {
    SI_int64 result;
    fast SI_uint64 accumulator = 0;
    fast bignum_digit_type * start = (BIGNUM_START_PTR (bignum));
    fast bignum_digit_type * scan = (start + (BIGNUM_LENGTH (bignum)));
    while (start < scan)
      accumulator = (SI_uint64)((accumulator << BIGNUM_DIGIT_LENGTH) + (*--scan));
    result = ((BIGNUM_NEGATIVE_P (bignum)) ? (0 - accumulator) : accumulator);
    return result;
  }
}

SI_Ulong
bignum_to_unsigned_long (bignum)
     bignum_type bignum;
{
  if (BIGNUM_ZERO_P (bignum))
    return (0);
  {
    fast SI_Ulong accumulator = 0;
    fast bignum_digit_type * start = (BIGNUM_START_PTR (bignum));
    fast bignum_digit_type * scan = (start + (BIGNUM_LENGTH (bignum)));
    while (start < scan)
      accumulator = (SI_Ulong)((accumulator << BIGNUM_DIGIT_LENGTH) + (*--scan));
    return accumulator;
  }
}

SI_uint64
bignum_to_uint64 (bignum)
     bignum_type bignum;
{
  if (BIGNUM_ZERO_P (bignum))
    return (0);
  {
    fast SI_uint64 accumulator = 0;
    fast bignum_digit_type * start = (BIGNUM_START_PTR (bignum));
    fast bignum_digit_type * scan = (start + (BIGNUM_LENGTH (bignum)));
    while (start < scan)
      accumulator = (SI_uint64)((accumulator << BIGNUM_DIGIT_LENGTH) + (*--scan));
    return accumulator;
  }
}
