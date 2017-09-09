/*
 * subtypep.h - include file for subtypep.c
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#define NUMBER_TYPES_LEN 12
static Object * Number_types[NUMBER_TYPES_LEN] = {
    &Qfixnum, &Qbignum,
    &Qinteger,
    &Qrational,
    &Qnumber,
    &Qshort_float, &Qsingle_float, &Qdouble_float, &Qlong_float,
    &Qfloat,
    &Qratio,
    &Qcomplex
};

static Object number_type_p(rtype)
    Object rtype;
{
    Declare_local_temp;
    register long i;

    if (CONSP(rtype))
	rtype = M_CAR(rtype);
    for (i = 0; i < NUMBER_TYPES_LEN; i++)
	if (EQ(rtype, *Number_types[i]))
	    return VALUES_1(T);
    return VALUES_1(NIL);
}

