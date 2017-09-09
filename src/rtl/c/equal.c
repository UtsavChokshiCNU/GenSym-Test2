/*
 * equal.c -  Chestnut Run-Time Library entry for function equal
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object eql(Object,Object);
extern Object string_eq(Object string1, Object string2, Object start1, Object end1, Object start2, Object end2);
extern Object equal(Object,Object);

#else

extern Object eql();
extern Object string_eq();
extern Object equal();

#endif


#include "equal.h"

/* entry name : equal(){} */

static long pathname_equal (a, b)
  Object a, b;
{
    return (TRUEP(equal(PATHNAME_PATH(a), PATHNAME_PATH(b))) &&
	    TRUEP(equal(PATHNAME_HOST(a), PATHNAME_HOST(b))));
}

/* The advantage of using of this helper function is:
   - it operates on bulean values rather on T or NIL;
   - do not sets the values counter, that is important in recursion
   It performs 'equal' test for elements of lists with 
   - optimization of type checking conditionals
   - 'inversion' [precomputation] of type of elements that halps to
     determine mismatch not doing extra function call
*/

static long cons_equal (a, b)
  Object a, b;
{
    Declare_local_temp;
  Object x, y;

LOOP:
  x = M_CAR(a);
  y = M_CAR(b);

  if (!EQ(x, y)) {
    if (CONSP(x)) {
      if (!CONSP(y) || !cons_equal(x, y)) return FALSE;
    }
    else if (IMMEDIATE_P(x) || IMMEDIATE_P(y))
	return FALSE;
    else if (STRINGP(x)) {
      if (!STRINGP(y) || !TRUEP(string_eq(x,y,KOPT,KOPT,KOPT,KOPT)))
	return FALSE;
    }
    else if (PATHNAMEP(x)) {
      if (!PATHNAMEP(y) || !pathname_equal(x, y)) return FALSE;
    }
    else if (!SI_STORED_NUMBER_P(x) || !SI_STORED_NUMBER_P(y) ||
	     !TRUEP(eql(x, y)))
      return FALSE;
  }

  a = M_CDR(a);
  b = M_CDR(b);

  if (EQ(a, b)) return TRUE;
  else if (IMMEDIATE_P(a) || IMMEDIATE_P(b))
      return FALSE;
  else if (CONSP(a)) {
    /* If we trusted the C compiler to turn tail recursion into a loop, this
     * could instead be written as just "return CONSP(b) && cons_equal(a, b);"
     */
    if (CONSP(b)) goto LOOP;
    else return FALSE;
  }
  else if (STRINGP(a))
    return (STRINGP(b) && TRUEP(string_eq(a,b,KOPT,KOPT,KOPT,KOPT)));
  else if (PATHNAMEP(a))
    return (PATHNAMEP(b) && pathname_equal(a, b));
  else 
    return (SI_STORED_NUMBER_P(a) &&
	    SI_STORED_NUMBER_P(b) &&
	    TRUEP(eql(a, b)));
}

Object equal (a, b)
  Object a, b;
{
    Declare_local_temp;
  Object res;

  if (EQ(a, b))
      res = T;
  else if (IMMEDIATE_P(a) || IMMEDIATE_P(b))
      res = NIL;
  else if (CONSP(a))
      res = (CONSP(b) && cons_equal(a, b)) ? T : NIL;
  else if (STRINGP(a))
      res = STRINGP(b) ? string_eq(a,b,KOPT,KOPT,KOPT,KOPT) : NIL;
  else if (PATHNAMEP(a))
      res = (PATHNAMEP(b) && pathname_equal(a, b)) ? T : NIL;
  else if (SI_STORED_NUMBER_P(a) && SI_STORED_NUMBER_P(b))
      res = eql(a, b);
  else
      res = NIL;
  
  return VALUES_1(res);
}
