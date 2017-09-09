/*
 * gensym.c -  Chestnut Run-Time Library entry for function gensym
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object imake_duplicate_string(char *oldstring);
extern SI_Long integer_to_long(Object n);
extern SI_Ulong integer_to_unsigned_long(Object n);
extern Object make_symbol(Object);
extern bignum_type unsigned_long_to_bignum (SI_Ulong);

#else

extern char *SI_istring();
extern Object imake_duplicate_string();
extern SI_Long integer_to_long();
extern SI_Ulong integer_to_unsigned_long();
extern Object make_symbol();
extern bignum_type unsigned_long_to_bignum ();

#endif

Object Gensym_counter = FIX(1L);

#define MAXGENSYM 50

static short	gensym_prefix_len = 1;
static char	gensym_name[MAXGENSYM+1] = "G";

Object gensym (reset)
    Object reset;	/* &optional number or string */
{
    Object name;
    SI_Ulong gensym_counter = 
      INTEGER_TO_UNSIGNED_LONG(Gensym_counter);

    if (SUPPLIEDP(reset)) {
	if (STRINGP(reset)) {
	    (void)strcpy(gensym_name, ISTRING(reset));
	    gensym_prefix_len = (short)ISSIZE(reset);
	}
	else if (NUMBERP(reset)) {
	    gensym_counter = IINTEGER(reset);
	}
    }
    (void)sprintf(&gensym_name[gensym_prefix_len], "%ld", gensym_counter);
    gensym_counter++;
    Gensym_counter = UNSIGNED_LONG_TO_INTEGER(gensym_counter);
    name = imake_duplicate_string(gensym_name);
    return make_symbol(name);
}




/*
 * g2rtl_copy_widestr_to_icpbuf(): is a kind of memcpy(), needed especially for
 * little-endian platforms for copying wide strings to ICP buffers, where
 * memcpy() may not be used.
 *
 * The ICP 16-bit bytes in the source array (s) are copied as 8-bit bytes to the
 * destination array (t) in big-endian order, i.e., with the most significant
 * (big) byte first, which is the required "network byte order" for ICP.
 *
 *   Args: s: an array of 16-bit bytes (type: unsigned short *)
 *         si: an integer index of the first byte of s to copy (type: long)
 *         t: an array of 8-bit bytes (type: unsigned char *)
 *         ti: an integer index of the first byte to replace in t (type: long)
 *         c: an integer count of the number of elements of s to copy
 *
 * This is intended to be a the back end for the non-big-endian case of the
 * macro inline_copy_widestr_to_icpbuf() in rtl/c/gensym.h.  In the case where
 * the endianness of the target platform matches ICP's network byte order, i.e.,
 * big-endian, memcpy() can simply be used.  (MHD 3/1/04) */

void
g2rtl_copy_widestr_to_icpbuf(s, si, t, ti, c)
    unsigned short *s;
    unsigned char *t;
    long si, ti, c;
{
  unsigned short *ss;
  unsigned char *tt;
  register int n;
  for (ss = ((s)+(si)), tt = ((t)+((ti)*2)), n = (c); n > 0; n--) {
    *tt = (unsigned char)(*ss >> 8);
    tt++;
    *tt = (unsigned char)(*ss & 0xff);
    tt++;
    ss++;
  }
}
