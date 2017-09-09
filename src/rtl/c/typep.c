/*
 * typep.c -  Chestnut Run-Time Library entry for function typep
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qarray;
extern Object Qsigned_byte;
extern Object Qsimple_array;
extern Object Qsimple_vector;
extern Object Qvector;

#if SI_USE_PROTOTYPES

extern Object SI_structure_type_specifier_p(Object symbol);
extern long SI_structure_typep(Object thing, Object info);
extern Object array_element_type(Object);
extern Object subtypep(Object,Object,Object);
extern Object type_of(Object);
extern Object upgraded_array_element_type(Object,Object);

#else

extern Object SI_structure_type_specifier_p();
extern int SI_structure_typep();
extern Object array_element_type();
extern Object subtypep();
extern Object type_of();
extern Object upgraded_array_element_type();

#endif




Object typep (object, type, environment)
    Object object, type, environment;
/* Ignore environment argument for now */

{
    Declare_local_temp;
    Declare_protect(5);
    Object result, elemtype, obj_type, type_structure_info;

    PROTECT_LOCALS();
    PROTECT_2(object, type);
    PROTECTI_3(elemtype, obj_type, type_structure_info);

    obj_type = type_of(object);

    if (EQ(obj_type,type))
	result = T;
    else if (type == NIL)
        result = NIL;
    else if (STRUCTURE_OBJECT_P(object) &&
	     TRUEP(type_structure_info = 
                   SI_structure_type_specifier_p(type)) &&
	     SI_structure_typep(object, type_structure_info))
	result = T;
    else if (subtypep(obj_type, type, environment) != NIL)
	result = T;
    else if (CONSP(type)) {
	if (EQ(M_CAR(type),Qvector) ||
	    EQ(M_CAR(type),Qarray) ||
	    EQ(M_CAR(type),Qsimple_array)) {
	    if (subtypep(obj_type, M_CAR(type), environment) != NIL) {
		elemtype = array_element_type(object);
		/* Should check dimensions as well! */
		result = EQ(upgraded_array_element_type
				  (M_SECOND(type), environment),
				  elemtype) ? T : NIL;
	    } else
		result = NIL;
	} else if (EQ(M_CAR(type),Qsimple_vector))
	    result = (SIMPLE_VECTOR_P(object) &&
		      (!FIXNUMP(M_CADR(type)) ||
		       (VECTOR_SIZE(object) == IFIX(M_CADR(type)))))
		? T : NIL;
	else if (EQ(M_CAR(type),Qsigned_byte))
            result = (LONG64P(object) && FIXNUM_EQ(M_SECOND(type), FIX(64)))
                ? T : NIL;
        else
	    result = NIL;
    }
    /* Qatom isn't in symbols.h */
    else
	result = NIL;

    UNPROTECT_LOCALS();
    return VALUES_1(result);
}
