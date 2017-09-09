/*
 * drmfrrr.c -  Chestnut Run-Time Library entry for function do_remf_error
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif




static void do_remf_error(list)
  Object	list;
{ (void)error(2, "Ill-formed property list: ~S.", list); }


Object do_remf(list, indicator)
  Object	list, indicator;
{
    Declare_local_temp;
  Object	head, tail, key;

  head = NIL;
  tail = list;
  while (CONSP(tail)) {
    key = M_CAR(tail), tail = M_CDR(tail);
    if (!CONSP(tail)) { do_remf_error(list); /*NOTREACHED*/ }
    else if (!EQ(key, indicator)) head = tail, tail = M_CDR(tail);
    else if (head == NIL) return VALUES_1(M_CDR(tail));
    else { M_CDR(head) = M_CDR(tail); return VALUES_1(list); }
  }
  if (tail != NIL) do_remf_error(list);
  return VALUES_1(T);
  /*NOTREACHED*/
}

