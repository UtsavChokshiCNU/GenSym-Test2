/*
 * mkarrlt.c -  Chestnut Run-Time Library entry for function SI_make_array_lite
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kelement_type;
extern Object Kinitial_element;
extern Object Qdouble_float;
extern Object Qsingle_float;
#ifdef KLUDGE_DOUBLE_FLOATS
extern Double_float_kludge_union SI_Double_float_kludge_temp;
#endif

#if SI_USE_PROTOTYPES

extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);

#else

extern Object SI_alloc_primitive_vector();
extern Object SI_obtain_rest_list();

#endif



Object SI_single_float_make_array_1(size, init_elt)
    SI_Dimension size;
    float init_elt; 
{   Object temp;
    long i;

 temp = SI_alloc_primitive_vector(size, A_SINGLE_FLOAT);
 for (i = 0; i < size; i++) {
     SI_PRIMITIVE_VECTOR_CONTENTS(temp, SI_PVT_Float)[i] = (float)init_elt;
 }
    return temp;
}

Object SI_double_float_make_array_1(size, init_elt)
    SI_Dimension size;
    double init_elt; 
{   Object temp;
    long i;

 temp = SI_alloc_primitive_vector(size, A_DOUBLE_FLOAT);
 for (i = 0; i < size; i++) {
     SI_PRIMITIVE_VECTOR_CONTENTS(temp, SI_PVT_Double)[i] = init_elt;
 }
    return temp;
}

Object SI_T_make_array_1(size, init_elt)
    SI_Dimension size;
    Object init_elt;
{   Object temp;
    long i;

 temp = SI_alloc_primitive_vector(size, A_T);
 for (i = 0; i < size; i++) {
     SI_PRIMITIVE_VECTOR_CONTENTS(temp, SI_PVT_Object)[i] = init_elt;
 }
    return temp;
}

Object SI_make_array_lite varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
    KEYWORD_ARGS_2(Kelement_type, k1, Kinitial_element, k2);
    END_ARGS();
    if (k1 == Qsingle_float)
	return SI_single_float_make_array_1(IFIX(r1),SUPPLIEDP(k2)?
					     IDOUBLE(k2): 0.0 );
    else  if (k1 == Qdouble_float)
	return SI_double_float_make_array_1(IFIX(r1),SUPPLIEDP(k2)?
					     (double)IDOUBLE(k2) :(double)0.0);
    else
	return SI_T_make_array_1(IFIX(r1),SUPPLIEDP(k2)?k2:NIL);
}

