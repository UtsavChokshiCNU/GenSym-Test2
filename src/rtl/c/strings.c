/*
 * strings.c - string functions
 * Bugs:
 * 1. trim functions could be improved a lot.  There is an outline of a better
 *    implementation in a comment preceding their definitions.
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

extern void SI_fatal_error(char *lstr, ...);
extern char *SI_string_base(Object o);
extern long ilength(Object sequence);
extern Object string(Object);

#else

extern void SI_fatal_error();
extern char *SI_string_base();
extern long ilength();
extern Object string();

#endif


#ifndef HAVE_STRICMP
int RTL_stricmp (str1, str2)
    char *str1, *str2;
{
    while (*str1 && (toupper(*str1) == toupper(*str2)))
	str1++, str2++;
    return((int) (toupper(*str1) - toupper(*str2)));
}

int RTL_strnicmp (str1, str2, n)
    char *str1, *str2;
    int n;
{
    while (n && *str1 && (toupper(*str1) == toupper(*str2)))
	n--, str1++, str2++;
    return(n ? ((int) (toupper(*str1) - toupper(*str2))) : 0);
}
#endif /* not HAVE_STRICMP */


/* Coercers */


/* Protect against sizeof(SI_Dimension) > sizeof(int) */

#if (INT_MAX >= IARRAY_TOTAL_SIZE_LIMIT)

#define STRING_CMP(s1, s2, n)	strncmp(s1, s2, (int)(n))
#define STRING_ICMP(s1, s2, n)	strnicmp(s1, s2, (int)(n))

#else

static int STRING_CMP(a, b, len)
  char *a, *b;
  SI_Dimension len;
{ int cmp;

  for ( ; len > INT_MAX; a += INT_MAX, b += INT_MAX, len -= INT_MAX) {
    cmp = strncmp(a, b, INT_MAX);
    if (cmp != 0) return cmp;
  }

  return strncmp(a, b, (int)len);
}

static int STRING_ICMP(a, b, len)
  char *a, *b;
  SI_Dimension len;
{ int cmp;

  for ( ; len > INT_MAX; a += INT_MAX, b += INT_MAX, len -= INT_MAX) {
    cmp = strnicmp(a, b, INT_MAX);
    if (cmp != 0) return cmp;
  }

  return strnicmp(a, b, (int)len);
}

#endif /* INT_MAX >= IARRAY_TOTAL_SIZE_LIMIT */

/* This macro deals with coercing two "string" arguments into actual strings,
 * and fetching pointers to the internal strings, using the coercion rules for
 * the string() function and ensuring that things are GC safe.
 */
#define NORMALIZE_TWO_STRINGS(s1, s2, is1, is2) \
    do { \
      Declare_protect(2); \
      Object NORM2_s1 = s1, NORM2_s2 = s2; \
 \
      PROTECT_LOCALS(); \
      PROTECT_2(NORM2_s1, NORM2_s2); \
 \
      if (!STRINGP(s1)) NORM2_s1 = string(NORM2_s1); \
      s2 = STRINGP(NORM2_s2) ? NORM2_s2 : string(NORM2_s2); \
      s1 = NORM2_s1; \
      is1 = SI_string_base(s1); \
      is2 = SI_string_base(s2); \
 \
      UNPROTECT_LOCALS(); \
    } while (0)

static Object
SI_string_eq (string1, string2, start1, end1, start2, end2, casep)
  Object string1, string2;
  Object start1, end1, start2, end2;
  int casep;
{
    Declare_local_temp;
  char *a, *b;
  SI_Dimension len1, len2;
  SI_Dimension istart1, istart2, iend1, iend2;

  NORMALIZE_TWO_STRINGS(string1, string2, a, b);

  istart1 = UNSUPPLIED_P(start1) ? 0 : IFIX(start1);
  istart2 = UNSUPPLIED_P(start2) ? 0 : IFIX(start2);

  iend1 = (!UNSUPPLIED_P(end1) && TRUEP(end1)) ? IFIX(end1) : ilength(string1);
  iend2 = (!UNSUPPLIED_P(end2) && TRUEP(end2)) ? IFIX(end2) : ilength(string2);

  a += istart1;
  b += istart2;
  len1 = iend1 - istart1;
  len2 = iend2 - istart2;

  if (len1 != len2) return VALUES_1(NIL);
  else if (casep) return VALUES_1(STRING_CMP(a, b, len1) ? NIL : T);
  else return VALUES_1(STRING_ICMP(a, b, len1) ? NIL : T);
}

Object string_eq (string1, string2, start1, end1, start2, end2)
  Object string1, string2;
  Object start1, end1, start2, end2;
{ return SI_string_eq(string1, string2, start1, end1, start2, end2, TRUE); }

Object string_equal (string1, string2, start1, end1, start2, end2)
  Object string1, string2;
  Object start1, end1, start2, end2;
{ return SI_string_eq(string1, string2, start1, end1, start2, end2, FALSE); }



/* String comparisons.
 *
 * string_compare() returns a negative number if the predicate test failed,
 * indicating that the caller should return NIL.  Any non-negative value is the
 * index within the two strings of the first character position at which the
 * strings fail to match.
 */
 
/* Operation codes for string_compare(). */
enum Strcmp_op {
  STRCMP_LT,
  STRCMP_LE,
  STRCMP_GT,
  STRCMP_GE,
  STRCMP_LESSP,
  STRCMP_NOT_GREATERP,
  STRCMP_GREATERP,
  STRCMP_NOT_LESSP,
  STRCMP_NEQ,
  STRCMP_NOT_EQUAL
};

/* DO_STRING_COMPARE()
 *
 * This macro is used to define the ordered string comparison operations.  The
 * way it works is that each operation provides the appropriate definitions for
 * the macros MUNCH() and COMPER() so that the right code will be produced.
 * MUNCH() performs any necessary case conversion of its character argument.
 * COMPER() is used to compare the lengths of the two sequences when compared
 * subsequences match, do determine whether the first substring is a prefix of
 * the second.
 * 
 * By definition, a string A is less than a string B if in the first position
 * in which they differ the character of A is less than the corresponding
 * character of B according to the function char<, or if the string A is a
 * proper prefix of string B (of shorter length and matching in all the
 * characters of A).  So the algorithm is 
 *
 * 1. Find the first non-matching pair in the two substrings.  If the first
 * character is less than the second, return base position + distance into the
 * substring.  Otherwise return -1, indicating predicate is false. 
 *
 * 2. If all characters match up to the length of the shorter substring, then
 * the result depends on whether the predicate specifies strictly less than, or
 * permits equality.  If the operation is strict, then the predicate is false
 * unless length of first substring is less than length of second.  If the
 * operation is not strict, then the predicate is false if the length of the
 * second substring is less than the length of the first.  If the predicate is
 * false (as determined from the lengths) then return -1.  Otherwise, return
 * base position + length of shorter substring.
 */

#define DO_STRING_COMPARE(MUNCH, COMPER) \
    for (i = 0; i < len; i++) { \
      c1 = *a++; MUNCH(c1); \
      c2 = *b++; MUNCH(c2); \
      if (c1 != c2) \
	return (c1 < c2) ? base_start + i : -1; \
    } \
    return COMPER(len1, len2) ? base_start + len1 : -1

#define MUNCH_NONE(c)		(void)(c)
#define MUNCH_UPCASE(c)		((c) = TOUPPER(c))

#define COMPER_LT(l1, l2)	((l1) < (l2))
#define COMPER_LE(l1, l2)	((l1) <= (l2))

static SI_Dimension
string_compare (string1, string2, start1, end1, start2, end2, op)
  Object string1, string2;
  Object start1, end1, start2, end2;
  enum Strcmp_op op;
{ char *a, *b;
  char c1, c2;
  SI_Dimension istart1, istart2, iend1, iend2;
  SI_Dimension len1, len2;
  SI_Dimension base_start, len, i;

  NORMALIZE_TWO_STRINGS(string1, string2, a, b);

  istart1 = UNSUPPLIED_P(start1) ? 0 : IFIX(start1);
  istart2 = UNSUPPLIED_P(start2) ? 0 : IFIX(start2);

  iend1 = (!UNSUPPLIED_P(end1) && TRUEP(end1)) ? IFIX(end1) : ilength(string1);
  iend2 = (!UNSUPPLIED_P(end2) && TRUEP(end2)) ? IFIX(end2) : ilength(string2);

  a += istart1;
  b += istart2;
  len1 = iend1 - istart1;
  len2 = iend2 - istart2;
  len = len1 > len2 ? len2 : len1;

  /* Initialize base_start to istart1.  If operation is implemented via
   * argument reversal, the entry in the switch statement for the operation
   * will set this to istart2.
   */
  base_start = istart1;

  switch (op) {

    case STRCMP_NEQ:
      for (i = 0; i < len; i++)
	if (*a++ != *b++) return base_start + i;
      return (len1 == len2) ? -1 : base_start + i;

    case STRCMP_NOT_EQUAL:
      for (i = 0; i < len; i++) {
	c1 = *a++; c2 = *b++;
	if (TOUPPER(c1) != TOUPPER(c2)) return base_start + i;
      }
      return (len1 == len2) ? -1 : base_start + i;

    case STRCMP_GT:
      /* string> is implemented by doing a string< with arguments reversed, so
       * change base_start to be the corresponding value for the second string
       * and fall through into the handler for string<.
       */
      base_start = istart2;
    case STRCMP_LT:
      DO_STRING_COMPARE(MUNCH_NONE, COMPER_LT);
      /*NOTREACHED*/

    case STRCMP_GE:
      /* string>= is implemented by doing a string<= with arguments reversed,
       * so change base_start to be the corresponding value for the second
       * string and fall through into the handler for string<=.
       */
      base_start = istart2;
    case STRCMP_LE:
      DO_STRING_COMPARE(MUNCH_NONE, COMPER_LE);
      /*NOTREACHED*/

    case STRCMP_GREATERP:
      /* string-greaterp is implemented by doing a string-lessp with arguments
       * reversed, so change base_start to be the corresponding value for the
       * second string and fall through into the handler for string-lessp.
       */
      base_start = istart2;
    case STRCMP_LESSP:
      DO_STRING_COMPARE(MUNCH_UPCASE, COMPER_LT);
      /*NOTREACHED*/

    case STRCMP_NOT_LESSP:
      /* string-not-lessp is implemented by doing a string-not-greaterp with
       * arguments reversed, so change base_start to be the corresponding value
       * for the second string and fall through into the handler for
       * string-not-greaterp.
       */
      base_start = istart2;
    case STRCMP_NOT_GREATERP:
      DO_STRING_COMPARE(MUNCH_UPCASE, COMPER_LE);
      /*NOTREACHED*/

    default:
      SI_fatal_error("Unknown string comparison opcode %d.", op);
      /*NOTREACHED*/
  }
  /*NOTREACHED*/
}

#define DEFINE_NORMAL_STRING_COMPARE(name, op) \
Object name (string1, string2, start1, end1, start2, end2) \
      Object string1, string2; \
      Object start1, end1, start2, end2; \
{ \
    Declare_local_temp; \
  SI_Dimension pos =  \
        string_compare(string1, string2, start1, end1, start2, end2, op); \
      return VALUES_1(pos < 0 ? NIL : FIX(pos)); \
}

#define DEFINE_INVERT_STRING_COMPARE(name, op) \
Object name (string1, string2, start1, end1, start2, end2) \
      Object string1, string2; \
      Object start1, end1, start2, end2; \
{ \
    Declare_local_temp; \
  SI_Dimension pos =  \
        string_compare(string2, string1, start2, end2, start1, end1, op); \
      return VALUES_1(pos < 0 ? NIL : FIX(pos)); \
}

DEFINE_NORMAL_STRING_COMPARE(string_lt, STRCMP_LT)
DEFINE_INVERT_STRING_COMPARE(string_gt, STRCMP_GT)
DEFINE_NORMAL_STRING_COMPARE(string_le, STRCMP_LE)
DEFINE_INVERT_STRING_COMPARE(string_ge, STRCMP_GE)

DEFINE_NORMAL_STRING_COMPARE(string_lessp, STRCMP_LESSP)
DEFINE_INVERT_STRING_COMPARE(string_greaterp, STRCMP_GREATERP)
DEFINE_NORMAL_STRING_COMPARE(string_not_greaterp, STRCMP_NOT_GREATERP)
DEFINE_INVERT_STRING_COMPARE(string_not_lessp, STRCMP_NOT_LESSP)

DEFINE_NORMAL_STRING_COMPARE(string_ne, STRCMP_NEQ)
DEFINE_NORMAL_STRING_COMPARE(string_not_equal, STRCMP_NOT_EQUAL)

#undef DEFINE_NORMAL_STRING_COMPARE
#undef DEFINE_INVERT_STRING_COMPARE

/* Use these to define keyword versions of the string comparison functions. */
#if 0
#define DEFINE_NORMAL_STRING_COMPARE(name, op) \
Object name varargs_1(int, n); \
      va_dcl \
{ \
    Declare_local_temp; \
  XDeclare_varargs; \
      Object string1, string2; \
      Object start1, start2, end1, end2; \
      SI_Dimension pos; \
 \
      BEGIN_ARGS(n); \
	REQUIRED_ARGS_2(string1, string2); \
	KEYWORD_ARGS_4(Kstart1, start1, Kstart2, start2, \
		       Kend1, end1, Kend2, end2); \
      END_ARGS(); \
 \  
      pos = string_compare(string1, string2, start1, end1, start2, end2, op); \
      return VALUES_1(pos < 0 ? NIL : FIX(pos)); \
}

#define DEFINE_INVERT_STRING_COMPARE(name, op) \
Object name varargs_1(int, n); \
      va_dcl \
{ \
    Declare_local_temp; \
  XDeclare_varargs; \
      Object string1, string2; \
      Object start1, start2, end1, end2; \
      SI_Dimension pos; \
 \
      BEGIN_ARGS(n); \
	REQUIRED_ARGS_2(string1, string2); \
	KEYWORD_ARGS_4(Kstart1, start1, Kstart2, start2, \
		       Kend1, end1, Kend2, end2); \
      END_ARGS(); \
 \     
      pos = string_compare(string2, string1, start2, end2, start1, end1, op); \
      return VALUES_1(pos < 0 ? NIL : FIX(pos)); \
}
#endif

#ifndef MSDOS
char *strupr (str)
    char *str;
{
    char c, *origstr = str;

    while ((c = *str)) {
	if (islower(c))
	    *str = TOUPPER(c);
	str++;
    }
    return(origstr);
}

char *strlwr (str)
    char *str;
{
    char c, *origstr = str;

    while ((c = *str)) {
	if (isupper(c))
	    *str = TOLOWER(c);
	str++;
    }
    return(origstr);
}
#endif

