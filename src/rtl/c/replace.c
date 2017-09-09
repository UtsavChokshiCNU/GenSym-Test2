/*
 * replace.c -  Chestnut Run-Time Library entry for function replace
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object copy_list(Object);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object elt(Object,Object);
extern long ilength(Object sequence);
extern Object set_elt(Object,Object,Object);

#else

extern Object copy_list();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object elt();
extern long ilength();
extern Object set_elt();

#endif


#include "seqmodi.h"

FORWARD_STATIC Object slow_replace ();

/* fast replace  autor: Dmitry N. */
Object replace (sequence1, sequence2, lstart1, lend1, lstart2, lend2)
    Object sequence1, sequence2, lstart1, lend1, lstart2, lend2;
{
    Declare_local_temp;
    long start1, end1, start2, end2, i1, i2;
    Object list1, list2;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(sequence1,sequence2);

    start1 = !UNSUPPLIED_P(lstart1) ? IFIX(lstart1) : 0L;
    start2 = !UNSUPPLIED_P(lstart2) ? IFIX(lstart2) : 0L;

    if (CONSP(sequence1)) {
	i1 = start1;
	list1 = sequence1;
	
	/* set list1 at the starting cons of the list */
	while(i1-- && TRUEP(list1))
	    list1 = M_CDR(list1);
	end1 = (SUPPLIEDP(lend1) && TRUEP(lend1))
	    ? IFIX(lend1) : IMOST_POSITIVE_FIXNUM;
	
	if (CONSP(sequence2)) {
	    end2 = (SUPPLIEDP(lend2) && TRUEP(lend2))
		? IFIX(lend2) : IMOST_POSITIVE_FIXNUM;
	    
	    /* draft version, could be done by nreverse */
	    if (sequence1 == sequence2 && 
		start1 > start2 && start1 < end2) 
		sequence2 = copy_list(sequence2);

	    i2 = start2;
	    list2 = sequence2;
	    while(i2-- && TRUEP(list2))
		list2 = M_CDR(list2);
	    
	    while (TRUEP(list1) && TRUEP(list2) && 
		   start1++ < end1 && start2++ < end2) {
		RPLACA(list1,M_CAR(list2));
		list1 =  M_CDR(list1);
		list2 =  M_CDR(list2);
	    }
	}
	else if (VECTORP(sequence2)) {
	    end2 = (SUPPLIEDP(lend2) && TRUEP(lend2))
		? IFIX(lend2) : SI_VECTOR_LENGTH(sequence2);

	    while (TRUEP(list1) && start1++ < end1 && start2 < end2) {
		RPLACA(list1,do_aref_1(sequence2,start2++));
		list1 = M_CDR(list1);
	    }
		}		
	else 
	    sequence1 = slow_replace (sequence1, sequence2, 
				      lstart1, lend1, lstart2, lend2);
    }
    else if (VECTORP(sequence1)) {
	end1 = (SUPPLIEDP(lend1) && TRUEP(lend1))
	    ? IFIX(lend1) : SI_VECTOR_LENGTH(sequence1);

	if (CONSP(sequence2)) {
	    i2 = start2;
	    list2 = sequence2;
	    while(i2--)
		list2 = M_CDR(list2);
	    
	    end2 = (SUPPLIEDP(lend2) && TRUEP(lend2))
		? IFIX(lend2) : IMOST_POSITIVE_FIXNUM;
	    
	    while(start1 < end1 && TRUEP(list2) && start2++ < end2) {
		do_setf_aref(sequence1,start1++,M_CAR(list2));
		list2 = M_CDR(list2);
	    }
	}
	else if (VECTORP(sequence2)) {
	    end2 = (SUPPLIEDP(lend2) && TRUEP(lend2))
		? IFIX(lend2) : SI_VECTOR_LENGTH(sequence2);
	    
	    if (sequence1 == sequence2 && 
		start1 > start2 && start1 < end2) {
		
		for (i1 = 0; start1++ < end1 && start2++ < end2; i1++);
		while (i1--)
		    do_setf_aref(sequence1,start1--,
				 do_aref_1(sequence2,start2--));
	    }
	    else
		while (start1 < end1 && start2 < end2)
		    do_setf_aref(sequence1,start1++,
				 do_aref_1(sequence2,start2++));
	}
	else 
	    sequence1 = slow_replace (sequence1, sequence2, 
				      lstart1, lend1, lstart2, lend2);
    }
    else 
	sequence1 = slow_replace (sequence1, sequence2, 
				  lstart1, lend1, lstart2, lend2);
    RESTORE_STACK();
    return VALUES_1(sequence1);
}

/* slow implementaion */
static Object slow_replace (sequence1, sequence2, 
			    lstart1, lend1, lstart2, lend2)
    Object sequence1, sequence2, lstart1, lend1, lstart2, lend2;
{
    Declare_local_temp;
    long start1, end1, start2, end2;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(sequence1,sequence2);

    start1 = !UNSUPPLIED_P(lstart1) ? IFIX(lstart1) : 0L;
    end1 = (SUPPLIEDP(lend1) && TRUEP(lend1))
	? IFIX(lend1) : ilength(sequence1);
    start2 = !UNSUPPLIED_P(lstart2) ? IFIX(lstart2) : 0L;
    end2 = (SUPPLIEDP(lend2) && TRUEP(lend2))
	? IFIX(lend2) : ilength(sequence2);

    while ((start1 < end1) && (start2 < end2)) {
	set_elt(sequence1, FIX(start1), elt(sequence2, FIX(start2)));
	start1++;
	start2++;
    }

    RESTORE_STACK();
    return VALUES_1(sequence1);
}


