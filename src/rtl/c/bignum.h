/* -*-C-*-

Copyright (c) 1989 Massachusetts Institute of Technology

This material was developed by the Scheme project at the Massachusetts
Institute of Technology, Department of Electrical Engineering and
Computer Science.  Permission to copy this software, to redistribute
it, and to use it for any purpose is granted, subject to the following
restrictions and understandings.

1. Any copy made of this software must include this copyright notice
in full.

2. Users of this software agree to make their best efforts (a) to
return to the MIT Scheme project any improvements or extensions that
they make, so that these may be included in future releases; and (b)
to inform MIT of noteworthy uses of this software.

3. All materials developed as a consequence of the use of this
software shall duly acknowledge such use, in accordance with the usual
standards of acknowledging credit in academic research.

4. MIT has made no warrantee or representation that the operation of
this software will be error-free, and MIT is under no obligation to
provide any services, by way of maintenance, update, or otherwise.

5. In conjunction with products arising from the use of this material,
there shall be no use of the name of the Massachusetts Institute of
Technology nor of any adaptation thereof in any advertising,
promotional, or sales literature without prior written consent from
MIT in each case. */

/* External Interface to Bignum Code */

/* The `unsigned long' type is used for the conversion procedures
   `bignum_to_long' and `long_to_bignum'.  Older implementations of C
   don't support this type; if you have such an implementation you can
   disable these procedures using the following flag (alternatively
   you could write alternate versions that don't require this type). */
/* #define BIGNUM_NO_ULONG */



enum bignum_comparison
{
  bignum_comparison_equal, bignum_comparison_less, bignum_comparison_greater
};


#ifdef MIT_SCHEME

typedef SCHEME_OBJECT bignum_type;
#define BIGNUM_OUT_OF_BAND SHARP_F

#else /* not MIT_SCHEME */
#ifdef CHESTNUT

typedef Object bignum_type;
#define BIGNUM_OUT_OF_BAND NIL

#else /* not MIT_SCHEME or CHESTNUT */

typedef long * bignum_type;
#define BIGNUM_OUT_OF_BAND ((bignum_type) 0)

#endif
#endif

/* the rest of the externs now appear at the end of externs.h */
