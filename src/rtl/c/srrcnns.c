/*
 * srrcnns.c -  Chestnut Run-Time Library entry for function SI_array_contents
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif




void *SI_array_contents (arr)     /* WARNING: SI_DISPLACED_INDEX_OFFSET */
    Object arr;
{
    Object pv = arr;
    void *result;
    enum SI_etype etype;

	if (!pv) return (void *)NULL;
    while (!SI_VECTOR_PRIMITIVE_P(pv))
        pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);
    etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

    switch (etype) {
	case A_T:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object);
	    break;
	case A_STRING_CHAR:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char);
	    break;
	case A_SINGLE_FLOAT:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float);
	    break;
	case A_DOUBLE_FLOAT:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double);
	    break;
	case A_BIT:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Bits);
	    break;
	case A_BYTE_8:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char);
	    break;
	case A_BYTE_16:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Short);
	    break;
	case A_BYTE_32:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long);
	    break;
	case A_UNSIGNED_BYTE_8:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar);
	    break;
	case A_UNSIGNED_BYTE_16:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort);
	    break;
	case A_UNSIGNED_BYTE_32:
	    result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong);
	    break;
	default:
	    error(1, "aref: unknown element type");
	    result = (void *)NULL;
	    break;
    }

    return (result);
}
