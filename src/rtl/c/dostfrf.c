/*
 * dostfrf.c -  Chestnut Run-Time Library entry for function do_setf_aref
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern SI_Long integer_to_long(Object n);

#else

extern Object (*SI_error_fptr) ();
extern SI_Long integer_to_long();

#endif




/* (SETF (AREF ...) ...) */

Object do_setf_aref (arr, i, elem)
    Object arr;
    SI_Dimension i;
    Object elem;
{
    //Declare_local_temp;
    enum SI_etype etype;
    Object pv = arr;

    while (!SI_VECTOR_PRIMITIVE_P(pv))
        pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);

    etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

    switch (etype) {
	case A_T:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object)[i] = elem;
	    break;
	case A_STRING_CHAR:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i] = CHR_CODE(elem);
	    break;
	case A_SINGLE_FLOAT:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float)[i]
		= SINGLE_FLOAT_TO_FLOAT(elem);
	    break;
	case A_DOUBLE_FLOAT:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double)[i]
		= DOUBLE_FLOAT_TO_DOUBLE(elem);
	    break;
	case A_BIT:
	    if (FIXNUM_ODDP(elem))
		SI_SBIT_ACCESS(pv,i) |= SI_SBIT_MASK(i);
	    else
		SI_SBIT_ACCESS(pv,i) &= ~SI_SBIT_MASK(i);
	    break;
	case A_BYTE_8:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i] = (char)IFIX(elem);
	    break;
	case A_BYTE_16:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Short)[i] = (short)IFIX(elem);
	    break;
	case A_BYTE_32:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long)[i] = INTEGER_TO_LONG(elem);
	    break;
	case A_BYTE_64:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long64)[i] = INTEGER_TO_INT64(elem);
	    break;
	case A_UNSIGNED_BYTE_8:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar)[i] = (unsigned char)IFIX(elem);
	    break;
	case A_UNSIGNED_BYTE_16:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort)[i] = (unsigned short)IFIX(elem);
	    break;
	case A_UNSIGNED_BYTE_32:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong)[i] =
		INTEGER_TO_LONG(elem);
	    break;
	case A_UNSIGNED_BYTE_64:
	    SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong64)[i] =
		INTEGER_TO_UINT64(elem);
	    break;
	default:
	    error(1, "aset: unknown element type");
	    break;
    }
    return VALUES_1(elem);
}
