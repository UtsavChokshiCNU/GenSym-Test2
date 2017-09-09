/*
 * sort.c -  Chestnut Run-Time Library entry for function sort
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

 
/* Common Lisp functions:
 *	Object sort () { }
 *	Object stable_sort () { }
 *      ^this gives the right names to librarian - D.N.
 */

#include "runtime.h"

extern Object Kkey;
extern Object Qsequence;
extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern void SI_type_error(Object datum, Object expected_type);
extern Object cons(Object,Object);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);
#else
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
#endif
extern long ilength(Object sequence);
extern Object last(Object,Object);
extern Object nthcdr(Object,Object);

#else

extern Object SI_obtain_rest_list();
extern void SI_type_error();
extern Object cons();
extern Object do_aref_1();
extern Object do_setf_aref();
#if SI_SUPPORT_CLOS
extern Object SI_internal_funcall();
#else
extern Object funcall1();
extern Object funcall2();
#endif
extern long ilength();
extern Object last();
extern Object nthcdr();

#endif



FORWARD_STATIC Object sort_nil();
FORWARD_STATIC Object sort_list();
FORWARD_STATIC Object stable_sort_vector();

#define DEFINE_SORT(entry, kentry, lsort, svsort, vsort) \
Object entry(seq, pred, key) \
  Object seq, pred, key; \
{ \
    Declare_local_temp; \
  Declare_protect(3); \
  Object (*sorter)(); \
 \
  PROTECT_LOCALS(); \
  PROTECT_3(seq, pred, key); \
 \
  if (UNSUPPLIED_P(key)) key = NIL; \
  if (!TRUEP(seq)) sorter = sort_nil; \
  else if (CONSP(seq)) sorter = lsort; \
  else if (SIMPLE_VECTOR_P(seq)) sorter = svsort; \
  else if (VECTORP(seq)) sorter = vsort; \
  else { \
    SI_type_error(seq, Qsequence); \
    /*NOTREACHED*/ \
  } \
  UNPROTECT_LOCALS(); \
  return (*sorter)(seq, pred, key); \
} \
 \
/*VARARGS*/ \
Object kentry varargs_1(int, n) \
{ XDeclare_varargs; \
  Object seq, pred, key; \
 \
  BEGIN_ARGS(n); \
    REQUIRED_ARGS_2(seq, pred); \
    KEYWORD_ARGS_1(Kkey, key); \
  END_ARGS(); \
  return entry(seq, pred, key); \
}

/* *** At some point when somebody gets around to writing better sort methods
 * *** for simple-vectors and other vectors, the vector entries in these calls
 * *** should be changed.
 *
 * *** Someday the names being used here will be reversed, with the positional
 * *** function having the SI_ prefix and the keyword driven function having
 * *** the "normal" name.
 */

DEFINE_SORT(sort, SI_sort_n,
	    sort_list,
	    stable_sort_vector,
	    stable_sort_vector)

DEFINE_SORT(stable_sort, SI_stable_sort_n,
	    sort_list,
	    stable_sort_vector,
	    stable_sort_vector)

/* Object sort_nil(seq, pred, key)
 *   Object seq, pred, key;
 *
 *   Seq is Nil.  Just return it.
 */

/*ARGSUSED*/
static Object sort_nil(seq, pred, key)
  Object seq, pred, key;
{
    Declare_local_temp;
  return VALUES_1(NIL); 
}

/* Object sort_list(seq, pred, key)
 *   Object seq, pred, key;
 *
 *   seq -- A list.
 *   pred -- Function designator of two arguments.
 *   key -- Function designator or unsupplied.
 *
 *   Merge-sort implementation, based on the CMU Lisp implementation.
 *
 *   The idea here is to collect the elements into sorted pairs, then merge
 *   pairs of pairs, pairs of quads, pairs of octets, &etc.
 *
 *   Note that this method is stable, so a seperate stable-sort-list is not
 *   needed. 
 */

FORWARD_STATIC Object merge_lists_to_list();

static Object sort_list(seq,pred,key)
  Object seq, pred, key;
{
    Declare_local_temp;
  Object head, i, unsorted, list_1, tail, i_1, temp, list_2;
  Object merged_head, merged_last;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_3(seq,pred,key);
  PROTECTI_8(head,unsorted,list_1,tail,temp,list_2,merged_head,merged_last);

  head = cons(NIL,seq);
  i = FIX(1);
  for (;;) {
    unsorted = M_CDR(head);
    tail = head;
    i_1 = FIXNUM_SUB1(i);
    for (;;) {
      list_1 = unsorted;
      temp = nthcdr(i_1,list_1);
      if (TRUEP(temp)) {
	list_2 = M_CDR(temp);
	M_CDR(temp) = NIL;
	temp = nthcdr(i_1,list_2);
	if (TRUEP(temp)) {
	  unsorted = M_CDR(temp);
	  M_CDR(temp) = NIL;
	}
	else
	  unsorted = NIL;
	temp = merge_lists_to_list(list_1,list_2,pred,key);
	MVS_2(temp,merged_head,merged_last);
	M_CDR(tail) = merged_head;
	tail = merged_last;
	if (!TRUEP(unsorted)) break;
      }
      else {
	M_CDR(tail) = list_1;
	break;
      }
    }
    i = FIXNUM_ADD(i,i);
    if (EQ(list_1,CDR(head))) {
      RESTORE_STACK();
      return VALUES_1(list_1);
    }
  }
}

/* Object merge_lists_to_list(list_1, list_2, pred, key)
 *   Object list_1, list_2, pred, key;
 *
 *   list_1 -- A list.
 *   list_2 -- A list
 *   pred -- A function designator of two arguments.
 *   key -- A function designator or unsupplied.
 *
 *   Merge two sorted lists together into a new sorted list, using the cells of
 *   the argument lists to construct the result.  This method is stable.
 *
 *   *** This is currently only used by sort_list(), but obviously could be
 *   *** used as a helper for merge() as well.
 */

static Object merge_lists_to_list(list_1,list_2,pred,key)
  Object list_1, list_2, pred, key;
{
    Declare_local_temp;
  Object value, p, e1, e2;
  Object temp_1, temp_2;
  Declare_stack_pointer;

  SAVE_STACK();
  PROTECT_4(list_1,list_2,pred,key);
  PROTECTI_5(value,p,e1,e2,temp_1);
  value = NIL;
  p = NIL;
  if (CONSP(list_1) && CONSP(list_2)) {
    e1 = M_CAR(list_1);
    e2 = M_CAR(list_2);
    if (!TRUEP(key)) {
      if (TRUEP(FUNCALL_2(pred,e2,e1))) {
	p = list_2;
	list_2 = M_CDR(p);
      }
      else {
	p = list_1;
	list_1 = M_CDR(p);
      }
    }
    else {
      temp_1 = FUNCALL_1(key,e2);
      temp_2 = FUNCALL_1(key,e1);
      if (TRUEP(FUNCALL_2(pred,temp_1,temp_2))) {
	p = list_2;
	list_2 = M_CDR(p);
      }
      else {
	p = list_1;
	list_1 = M_CDR(p);
      }
    }
    value = p;
    if (CONSP(list_1) && CONSP(list_2)) {
      e1 = M_CAR(list_1);
      e2 = M_CAR(list_2);

#undef UPDATE
#define UPDATE(l,e) \
    if (TRUE) { \
      M_CDR(p) = l; \
      p = l; \
      l = M_CDR(l); \
      if (CONSP(l)) e = M_CAR(l); \
      else break; \
      } \
    else (void)0

      if (!TRUEP(key))
	for (;;) {
	  if (TRUEP(FUNCALL_2(pred,e2,e1)))
	    UPDATE(list_2, e2);
	  else
	    UPDATE(list_1, e1);
	}
      else
	for (;;) {
	  temp_1 = FUNCALL_1(key,e2);
	  temp_2 = FUNCALL_1(key,e1);
	  if (TRUEP(FUNCALL_2(pred,temp_1,temp_2)))
	    UPDATE(list_2, e2);
	  else
	    UPDATE(list_1, e1);
	}
#undef UPDATE
    }
  }
  if (ATOM(list_1)) {
    if (!TRUEP(p)) {
      value = list_2;
      p = value;
    }
    else
      M_CDR(p) = list_2;
  }
  else if (!TRUEP(p)) {
    value = list_1;
    p = value;
  }
  else
    M_CDR(p) = list_1;
  temp_2 = last(p,_);
  RESTORE_STACK();
  return VALUES_2(value,temp_2);
}

static Object stable_sort_vector(seq, pred, key)
    Object seq, pred, key;
{
    Declare_local_temp;
    Object x1, x2, e1, e2;
    long front, back;
    int swaps;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(seq,pred,key);
    PROTECTI_4(x1,x2,e1,e2);

    /* bubble sort */
    if (UNSUPPLIED_P(key)) key = NIL;
    back = ilength(seq);
    do {
	for (back--, front = 0L, swaps = FALSE; front < back; front++) {
	    x1 = do_aref_1(seq, front);
	    e1 = TRUEP(key) ? funcall1(key, x1) : x1;
	    x2 = do_aref_1(seq, front+1);
	    e2 = TRUEP(key) ? funcall1(key, x2) : x2;
	    if (TRUEP(funcall2(pred,e2, e1))) {
		do_setf_aref(seq, front, x2);
		do_setf_aref(seq, front+1, x1);
		swaps = TRUE;
	    }
	}
    } while (swaps);

    RESTORE_STACK();
    return VALUES_1(seq);
}

