/*
 * delete_eq.h - list manipulation helper macros
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#undef DEFINE_LIST_DELETE
#define DEFINE_LIST_DELETE(name, pred, f_pred) \
Object name(item, list) \
  Object item, list; \
{ \
    Declare_local_temp; \
  Object last, tail, elem; \
 \
  if (!LISTP(list)) \
    return (ldelete(item, list, KOPT, f_pred, \
		    KOPT, KOPT, KOPT, KOPT, KOPT)); \
  for ( ; CONSP(list); list = M_CDR(list)) { \
    elem = M_CAR(list); \
    if (!pred(item, elem)) { \
      last = list; tail = M_CDR(last); \
      for ( ; CONSP((tail)); tail = M_CDR(tail)) { \
	elem = M_CAR(tail); \
	if (pred(item, elem)) \
	  M_CDR(last) = M_CDR(tail); \
	else \
	  last = M_CDR(last); \
      } \
      break; \
    } \
  } \
  return VALUES_1(list); \
}

