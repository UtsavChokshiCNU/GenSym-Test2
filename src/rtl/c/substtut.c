/*
 * substtut.c -  Chestnut Run-Time Library entry for function substitute
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object copy_seq(Object);
extern Object nsubstitute(Object newitem, Object olditem, Object seq, Object from_end, Object test, Object test_not, Object lstart, Object lend, Object lcount, Object key);

#else

extern Object copy_seq();
extern Object nsubstitute();

#endif


#include "seqmodi.h"

Object substitute (newitem, olditem, seq, from_end, test, test_not,
		   lstart, lend, lcount, key)
    Object newitem, olditem, seq, from_end, test, test_not,
	lstart, lend, lcount, key;
{
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_6(newitem,olditem,seq,test,test_not,key);
    seq = copy_seq(seq);
    RESTORE_STACK();
    return(nsubstitute(newitem,olditem,seq,from_end,test,test_not,
		       lstart,lend,lcount,key));
}
