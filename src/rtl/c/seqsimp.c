/*
 * seqsimp.c - Simple Sequence manipulation functions
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

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object do_aref_1(Object arr, long i);
extern Object m_nthcdr(long n, Object list);
extern Object nth(Object,Object);
extern Object set_aref1(Object a, Object i, Object v);

#else

extern Object (*SI_error_fptr) ();
extern Object do_aref_1();
extern Object m_nthcdr();
extern Object nth();
extern Object set_aref1();

#endif




Object elt (seq, index)
    Object seq, index;
{
    Declare_local_temp;
    return(LISTP(seq) ? nth(index, seq) : do_aref_1(seq, IFIX(index)));
}

Object set_elt (seq, index, value)
    Object seq, index, value;
{
    Declare_local_temp;
    if (CONSP(seq))
	return VALUES_1(M_NTH(index, seq) = value);
    else
	return(set_aref1(seq, index, value));
}


long ilength (sequence)
    Object sequence;
{
    Declare_local_temp;
    long len = 0L;

    if (sequence == NIL)
	len = 0;
    else if (VECTORP(sequence))
	len = SI_VECTOR_LENGTH(sequence);
    else if (CONSP(sequence))
	do {
	    len++;
	    sequence = M_CDR(sequence);
	} while(CONSP(sequence));
    else
	error(2, "length: invalid argument - ~S", sequence);
    return len;
}

Object length (sequence)
    Object sequence;
{
    Declare_local_temp;
    long ilen;
    Object len;

    ilen = ilength(sequence);
    len = FIX(ilen);
    return VALUES_1(len);
}

