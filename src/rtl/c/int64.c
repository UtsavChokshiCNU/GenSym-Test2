/*
 * int64.c -  Chestnut Run-Time Library entry for INT64 functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Local_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern int bignum_fits_in_word_p (bignum_type, long word_length, int twos_complement_p);
extern SI_int64 bignum_to_int64 (bignum_type);

#else

extern Object SI_alloc();
extern Object (*SI_warn_fptr) ();
extern int bignum_fits_in_word_p ();
extern SI_int64 bignum_to_int64 ();

#endif

Object clong_to_int64 (a)
    SI_Long a;
{
    Object result;
    Declare_area(area);

    SAVE_CURRENT_AREA(area);
    SET_CURRENT_AREA(Local_area);

    result = SI_ALLOC(SI_Long64_integer, LONG64_TYPE, SI_NUMBER_TAG, SI_BORING);

    RESTORE_CURRENT_AREA(area);
    SI_UNTAG_LONG64(result) = (SI_int64) a;

    return result;
}

Object cint64_to_int64 (a)
    SI_int64 a;
{
    Object result;
    Declare_area(area);

    SAVE_CURRENT_AREA(area);
    SET_CURRENT_AREA(Local_area);

    result = SI_ALLOC(SI_Long64_integer, LONG64_TYPE, SI_NUMBER_TAG, SI_BORING);

    RESTORE_CURRENT_AREA(area);
    SI_UNTAG_LONG64(result) = (SI_int64) a;

    return result;
}

SI_int64 integer_to_int64 (n)
    Object n;
{
    SI_int64 i64;

    if (FIXNUMP(n)) {
	i64 = (SI_int64) IFIX(n);
        return i64;
    } else {
	switch (SI_STORED_OBJECT_TYPE(n)) {
	case OBIGNUM_TYPE:
	    return BIGNUM_VALUE(n);
	case XBIGNUM_TYPE:
	    if (!bignum_fits_in_word_p(n, 64, 1))
		goto LOSE;
	    i64 = bignum_to_int64(n);
	    return i64;
	case LONG64_TYPE:
	    i64 = ILONG64(n);
	    return i64;
	}
    }
 LOSE:
    warn(2, "integer_to_int64: invalid argument - ~S", n);
    return 0L; // (SI_int64) -9223372036854775808L;
}
