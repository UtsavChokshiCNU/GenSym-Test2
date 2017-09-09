/*
 * sbstttf.c -  Chestnut Run-Time Library entry for function substitute_if
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object copy_seq(Object);
extern Object nsubstitute_if(Object newitem, Object test, Object seq, Object from_end, Object lstart, Object lend, Object lcount, Object key);

#else

extern Object copy_seq();
extern Object nsubstitute_if();

#endif


#include "seqmodi.h"

Object substitute_if (newitem, test, seq, from_end, start, end, count, key)
    Object newitem, test, seq, from_end, start, end, count, key;
{
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(newitem,seq,test,key);
    seq = copy_seq(seq);
    RESTORE_STACK();
    return(nsubstitute_if(newitem,test,seq,from_end,
		       start,end,count,key));
}
