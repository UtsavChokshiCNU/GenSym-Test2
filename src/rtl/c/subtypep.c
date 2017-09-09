/*
 * subtypep.c -  Chestnut Run-Time Library entry for function subtypep
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qfixnum;
extern Object Qbignum;
extern Object Qinteger;
extern Object Qrational;
extern Object Qnumber;
extern Object Qshort_float;
extern Object Qsingle_float;
extern Object Qsingle_float;
extern Object Qdouble_float;
extern Object Qlong_float;
extern Object Qfloat;
extern Object Qratio;
extern Object Qcomplex;
extern Object Qstring;
extern Object Qsimple_string;
extern Object Qbit_vector;
extern Object Qsimple_bit_vector;
extern Object Qarray;
extern Object Qvector;
extern Object Qsimple_vector;
extern Object Qsequence;
extern Object Qsymbol;
extern Object Qnull;
extern Object Qlist;
extern Object Qcons;
extern Object Qfunction;
extern Object Qcompiled_function;
extern Object Qsimple_array;
extern TLS Object Values[];
extern Object sequence_type_p();

#include "subtypep.h"

/* Ignore environment argument for now */
Object subtypep (type1, type2, environment)
    Object type1, type2, environment;
{
    Object result, certainty;

    result = NIL;
    certainty = NIL;

    if (EQ(type1, type2)) {
	result = certainty = T;
    }
    else if (EQ(type2, Qinteger)) {
	if (EQ(type1, Qfixnum) || EQ(type1, Qbignum))
	    result = certainty = T;
    }
    else if (EQ(type2, Qstring)) {
	if (EQ(type1, Qsimple_string))
	    result = certainty = T;
    }
    else if (EQ(type2, Qbit_vector)) {
	if (EQ(type1, Qsimple_bit_vector))
	    result = certainty = T;
    }
    else if (EQ(type2, Qarray)) {
	if (EQ(type1, Qvector) || EQ(type1, Qsimple_vector) ||
	    EQ(type1, Qstring) || EQ(type1, Qsimple_string) ||
	    EQ(type1, Qbit_vector) ||
	    EQ(type1, Qsimple_bit_vector))
	    result = certainty = T;
    }
    else if (EQ(type2, Qsequence)) {
	if (sequence_type_p(type1))
	    result = certainty = T;
    }
    else if (EQ(type2, Qvector)) {
	if (EQ(type1, Qvector)
	    || EQ(type1, Qsimple_vector) ||
	    EQ(type1, Qstring)
	    || EQ(type1, Qsimple_string) ||
	    EQ(type1, Qbit_vector) ||
	    EQ(type1, Qsimple_bit_vector))
	result = certainty = T;
    }
    else if (EQ(type2, Qnumber)) {
	if (number_type_p(type1))
	    result = certainty = T;
    }
    else if (EQ(type2, Qfloat)) {
	if (EQ(type1, Qdouble_float) ||
	    EQ(type1, Qsingle_float) ||
	    EQ(type1, Qshort_float) ||
	    EQ(type1, Qlong_float))
	    result = certainty = T;
    }
    else if (EQ(type2, Qrational)) {
	if (EQ(type1, Qfixnum) ||
	    EQ(type1, Qbignum) ||
	    EQ(type1, Qinteger) ||
	    EQ(type1, Qratio))
	    result = certainty = T;
    }
    else if (EQ(type2, Qsymbol)) {
	if (EQ(type1, Qnull))
	    result = certainty = T;
    }
    else if (EQ(type2, Qlist)) {
	if (EQ(type1, Qnull) || EQ(type1, Qcons))
	    result = certainty = T;
    }
    else if (EQ(type2, Qfunction)) {
	if (EQ(type1, Qcompiled_function))
	    result = certainty = T;
    }
    /* because currently we have no separate SI_type for
       compiled functions */
    else if (EQ(type1, Qfunction)) {
	if (EQ(type2, Qcompiled_function))
	    result = certainty = T;
    }
    else if (EQ(type2, Qt))
	result = certainty = T;
    else if (EQ(type2, NIL)) {
	result = NIL; certainty = T;
    }
#if SI_SUPPORT_CLOS 
    else {
	Declare_protect(4);
	Object t1,t2;
	Object class1, class2;

	PROTECT_LOCALS();
	PROTECTI_2(t1,t2);
	PROTECTI_2(class1, class2);

	t1 = type1;
	t2 = type2;
	/* t1: even knowing C compilers do && from left to right... */
	if (TRUEP(class1 = find_class(t1,NIL,NIL)) &&
	    TRUEP(class2 = find_class(t2,NIL,NIL)))
	    result = certainty = SI_subtypep__classes(class1, class2)?T:NIL;
	UNPROTECT_LOCALS();
    }
#endif
    return(VALUES_2(result, certainty));
}

Object sequence_type_p (rtype)
    Object rtype;
{
    Declare_local_temp;
    if (CONSP(rtype))
	/* (simple-vector size) */
	/* (vector etype size) */
	/* ([simple-]{string, bit-vector} size) */
	/* *** seems like to specific ([simple-]array etype (size)) */
	/* now [simple] array etype [(size] */
	if (EQ(M_CAR(rtype), Qvector) ||
	    EQ(M_CAR(rtype), Qsimple_vector) ||
	    EQ(M_CAR(rtype), Qstring) ||
	    EQ(M_CAR(rtype), Qsimple_string) ||
	    EQ(M_CAR(rtype), Qbit_vector) ||
	    EQ(M_CAR(rtype), Qsimple_bit_vector) ||
	    EQ(M_CAR(rtype), Qarray) ||
	    EQ(M_CAR(rtype), Qsimple_array))
/*	    ((EQ(M_CAR(rtype), Qarray) ||
	      EQ(M_CAR(rtype), Qsimple_array)) &&
	     M_CDR(rtype) != NIL &&
	     M_CDDR(rtype) != NIL &&
	     CONSP(M_CADDR(rtype)) &&
	     M_CDR(M_CADDR(rtype)) == NIL))
*/	
	    return VALUES_1(T);
	else
	    return VALUES_1(NIL);
    if (EQ(rtype, Qarray) ||
	EQ(rtype, Qstring) || EQ(rtype, Qvector) ||
	EQ(rtype, Qlist) ||
	EQ(rtype, Qcons) ||
	EQ(rtype, Qnull) ||
	EQ(rtype, Qbit_vector) || EQ(rtype, Qsequence) ||
	EQ(rtype, Qsimple_vector) ||
	EQ(rtype, Qsimple_string) ||
	EQ(rtype, Qsimple_bit_vector))
	return VALUES_1(T);
    return VALUES_1(NIL);
}


