/*
 * doaref1.c -  Chestnut Run-Time Library entry for function do_aref_1
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object cdouble_to_double(double a);
extern Object cint64_to_int64(SI_int64 a);
extern Object clong_to_bignum(SI_Long a);

#else

extern Object (*SI_error_fptr) ();
extern Object cdouble_to_double();
extern Object cint64_to_int64();
extern Object clong_to_bignum();

#endif




/* (AREF ...) */

Object do_aref_1 (arr, i)	/* This is CLtL II's ROW-MAJOR-AREF */
    Object arr;
    long i;
{
    Declare_local_temp;
    Object pv = arr;
    Object result = NIL;
    long iresult;
    unsigned long uresult;
    SI_int64 i64result;
    enum SI_etype etype;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(arr, pv, result);

    while (!SI_VECTOR_PRIMITIVE_P(pv))
        pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);
    etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

    switch (etype) {
	case A_T:
	    result = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object)[i];
	    break;
	case A_STRING_CHAR:
	    result = MAKE_CHR(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i], 0);
	    break;
	case A_SINGLE_FLOAT:
	    result = cdouble_to_double((double) SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float)[i]);
	    break;
	case A_DOUBLE_FLOAT:
	    result =
		cdouble_to_double(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double)[i]);
	    break;
	case A_BIT:
	    result = (SI_SBIT_ACCESS(pv,i) & SI_SBIT_MASK(i)) ? FIX(1) : ZERO;
	    break;
	case A_BYTE_8:
	    iresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i];
	    result = FIX(iresult);
	    break;
	case A_BYTE_16:
	    iresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Short)[i];
	    result = FIX(iresult);
	    break;
	case A_BYTE_32:
	    iresult = (SI_Long)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long)[i];
	    result = MAKE_INTEGER(iresult);
	    break;
	case A_BYTE_64:
	    i64result = (SI_int64)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long64)[i];
	    result = INT64_TO_INTEGER(i64result);
	    break;
	case A_UNSIGNED_BYTE_8:
	    uresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar)[i];
	    result = FIX(uresult);
	    break;
	case A_UNSIGNED_BYTE_16:
	    uresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort)[i];
	    result = MAKE_INTEGER((long)uresult);
	    break;
	case A_UNSIGNED_BYTE_32:
	    uresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong)[i];
	    /* Fix later */
	    result = MAKE_INTEGER((SI_Long)uresult);
	    break;
	case A_UNSIGNED_BYTE_64:
	    i64result = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong64)[i];
            /* Fix later (uint64 is not supported yet) */
	    result = INT64_TO_INTEGER((SI_int64)i64result);
	    break;
	default:
	    error(1, "aref: unknown element type");
	    result = NIL;
	    break;
    }

    RESTORE_STACK();
    return VALUES_1(result);
}
