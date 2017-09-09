/*
 * rmvdplcs.c -  Chestnut Run-Time Library entry for function remove_duplicates
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object copy_seq(Object);
extern Object delete_duplicates(Object seq, Object from_end, Object test, Object test_not, Object lstart, Object lend, Object key);
extern Object funcall1(Object func, Object arg);
extern long ilength(Object sequence);
extern Object member_se(Object item, Object list, Object test, Object test_not, Object key, Object start, Object end);
extern Object member(Object item, Object list, Object test, Object test_not, Object key);
extern Object nreverse(Object);
extern Object nthcdr(Object,Object);

#else

extern Object cons();
extern Object copy_seq();
extern Object delete_duplicates();
extern Object funcall1();
extern long ilength();
extern Object member_se();
extern Object member();
extern Object nreverse();
extern Object nthcdr();

#endif


#include "seqmodi.h"

Object remove_duplicates (seq, from_end, test, test_not, lstart, lend, key)
    Object seq, from_end, test, test_not, lstart, lend, key;
{
    Declare_local_temp;
    Object result = NIL, item, elem, temp1, saveend;
    long i, len, start, end;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(seq,test,test_not,key,result);
    PROTECTI_4(item,elem,temp1,saveend);

    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    if (UNSUPPLIED_P(key)) key = NIL;


    if (VECTORP(seq) || (SUPPLIED_P(from_end) && TRUEP(from_end))) {
	result = delete_duplicates(copy_seq(seq), from_end, test,
				   test_not, lstart, lend, key);
    }
    else {
	saveend = (SUPPLIEDP(lend) && TRUEP(lend))
	    ? nthcdr(FIX(end),seq) : NIL;
	for (i = 0L; TRUEP(seq) && (i < start); seq = M_CDR(seq), i++) {
	    result = cons(M_CAR(seq), result);
	}
	for (; TRUEP(seq) && (i < end); seq = M_CDR(seq), i++) {
	    item = elem = M_CAR(seq);
	    if (TRUEP(key))
		item = FUNCALL_1(key, item);
	    if ((TRUEP(saveend) &&
		 !TRUEP(member_se(item,M_CDR(seq),test,
				  test_not,key,_,saveend))) ||
		(!TRUEP(saveend) &&
		 !TRUEP(member(item,M_CDR(seq),test,test_not,key)))) {
		result = cons(elem,result);
	    }
	}
	while (TRUEP(seq)) {
	    result = cons(M_CAR(seq), result);
	    seq = M_CDR(seq);
	}
	result = nreverse(result);
    }
    RESTORE_STACK();
   return VALUES_1(result);
}
