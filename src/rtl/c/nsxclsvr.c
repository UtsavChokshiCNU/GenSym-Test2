/*
 * nsxclsvr.c -  Chestnut Run-Time Library entry for function nset_exclusive_or
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object SI_fp_eql_1;

#if SI_USE_PROTOTYPES

extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern Object nconc2(Object list1, Object list2);

#else

extern Object STATIC_FUNCTION1();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern Object nconc2();

#endif


#include "lists.h"

Object nset_exclusive_or (list1, list2, test, test_not, key)
    Object list1, list2, test, test_not, key;
{
    Declare_local_temp;
    Object result, bag, lastcdr1, lastcdr2;
    Object temp1, temp2, tempb, elem1, elem2, elemb;
    long flag;
    long testp = !UNSUPPLIED_P(test);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(list1,list2,test,test_not,key);
    PROTECTI_4(result,bag,lastcdr1,lastcdr2);
    PROTECTI_6(temp1,temp2,tempb,elem1,elem2,elemb);
    if (UNSUPPLIED_P(key)) key = NIL;

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

/* bag=NIL;
 * for each element elem1 of list1
 *   flag = false
 *   for each element elem2 of bag while (not flag)
 *     if test(elem1,elem2)
 *       flag = true
 *   for each element elem2 of list2
 *     If test(elem1,elem2)
 *       flag = true
 *       splice elem2 out of list2 and into bag
 *   if flag
 *      splice elem1 out of list1
 */
    bag = NIL;
    lastcdr1 = NIL;
    temp1 = list1;
    while (TRUEP(temp1)) {
	flag = FALSE;
	elem1 = M_CAR(temp1);
	if (TRUEP(key))
	    elem1 = funcall1(key,elem1);
	for (tempb = bag; TRUEP(tempb); tempb = M_CDR(tempb)) {
	    elemb = M_CAR(tempb);
	    if (TRUEP(key))
		elemb = funcall1(key, elemb);
	    if (SATISFIESP(testp, test, test_not,elem1,elemb)) {
		flag = TRUE;
		break;
	    }
	}
	/* for each elem2 of list2 */
	temp2 = list2;
	lastcdr2 = NIL;
	while (TRUEP(temp2)) {
	    elem2 = M_CAR(temp2);
	    if (TRUEP(key))
		elem2 = funcall1(key, elem2);
	    if (SATISFIESP(testp, test, test_not,elem1,elem2)) {
		/* splice item2 out of list2 and into bag */
		flag = TRUE;
		if (ENDP(lastcdr2)) {
		    list2 = M_CDR(list2);
		    bag = RPLACD(temp2,bag);
		    temp2=list2;
		}
		else {
		    RPLACD(lastcdr2, M_CDR(temp2));
		    bag = RPLACD(temp2,bag);
		    temp2 = M_CDR(lastcdr2);
		}
	    }
	    else {
		lastcdr2 = temp2;
		temp2 = M_CDR(temp2);
	    }
	}
	if (flag) {
	    /* splice item1 out of list1 */
	    temp1 = M_CDR(temp1);
	    if (ENDP(lastcdr1))
		list1 = M_CDR(list1);
	    else
		RPLACD(lastcdr1, temp1);
	}
	else {
	    lastcdr1 = temp1;
	    temp1 = M_CDR(temp1);
	}
    }
    /* result is remaining items in list1 and list2 */
    result = nconc2(list1, list2);
    RESTORE_STACK();
    return VALUES_1(result);
}
