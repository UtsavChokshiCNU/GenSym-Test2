/*
 * bit_arrs.c - Bit-array manipulation routines
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
extern Object array_dimensions(Object);
extern Object array_total_size(Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object (*SI_error_fptr) ();
extern Object array_dimensions();
extern Object array_total_size();
extern Object make_array();

#endif



static Object do_bit();
static Object set_bit_result();

extern Object SI_Etypes_var;
extern Object SI_initialize_array_element_types();
#define Element_types \
    (SI_Etypes_var == UNBOUND ? SI_initialize_array_element_types() : SI_Etypes_var)

enum optype {
    BIT_AND,
    BIT_IOR,
    BIT_XOR,
    BIT_EQV,
    BIT_NAND,
    BIT_NOR,
    BIT_ANDC1,
    BIT_ANDC2,
    BIT_ORC1,
    BIT_ORC2,
    BIT_NOT
};

/*ARGSUSED*/
static Object do_bit (optype, bit_array1, bit_array2, result_bit_array)
    enum optype optype;
    Object bit_array1, bit_array2, result_bit_array;
{
    Declare_local_temp;

    Object size;
    long i, nelems;
    UCHAR *p1, *p2;
    UCHAR *p3;

    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(bit_array1, bit_array2, result_bit_array);
    PROTECTI_1(size);

    if (!SI_PRIMITIVE_VECTOR_P(bit_array1) || !SI_PRIMITIVE_VECTOR_P(bit_array1))
	return error(1, "bit operations on non-vectors not implemented yet");

    p1 = SI_PRIMITIVE_VECTOR_CONTENTS(bit_array1, SI_PVT_Uchar);
    p2 = SI_PRIMITIVE_VECTOR_CONTENTS(bit_array2, SI_PVT_Uchar);


    size = array_total_size(bit_array1);
    nelems = (IFIX(size) + 7) >> 3;
    result_bit_array = set_bit_result(bit_array1,bit_array2,result_bit_array);
    p3 = SI_PRIMITIVE_VECTOR_CONTENTS(result_bit_array, SI_PVT_Uchar);

    switch (optype) {
	case BIT_AND:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = *(p1+i) & *(p2+i);
	    }
	    break;
	case BIT_IOR:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = *(p1+i) | *(p2+i);
	    }
	    break;
	case BIT_XOR:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = *(p1+i) ^ *(p2+i);
	    }
	    break;
	case BIT_EQV:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = ~(*(p1+i) ^ *(p2+i));
	    }
	    break;
	case BIT_NAND:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = ~(*(p1+i) & *(p2+i));
	    }
	    break;
	case BIT_NOR:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = ~(*(p1+i) | *(p2+i));
	    }
	    break;
	case BIT_ANDC1:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = (~(*(p1+i)) & *(p2+i));
	    }
	    break;
	case BIT_ANDC2:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = (*(p1+i) & ~(*(p2+i)));
	    }
	    break;
	case BIT_ORC1:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = (~(*(p1+i)) | *(p2+i));
	    }
	    break;
	case BIT_ORC2:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = (*(p1+i) | ~(*(p2+i)));
	    }
	    break;
	case BIT_NOT:
	    for (i = 0; i < nelems; i++) {
		*(p3+i) = ~(*(p1+i));
	    }
	    break;
	default:
	    break;
    }
    RESTORE_STACK();
    return VALUES_1(result_bit_array);
}

static Object set_bit_result (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    Declare_local_temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(bit_array1, bit_array2, result_bit_array);
    if (UNSUPPLIED_P(result_bit_array))
	result_bit_array =
	    make_array(array_dimensions(bit_array1),
		       SVREF(Element_types, FIX(A_BIT)),
		       KOPT,KOPT,KOPT,KOPT,KOPT,KOPT);
    else if (EQ(result_bit_array, T))
	result_bit_array = bit_array1;
    RESTORE_STACK();
    return VALUES_1(result_bit_array);
}

Object bit_and (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_AND, bit_array1, bit_array2, result_bit_array));
}

Object bit_ior (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_IOR, bit_array1, bit_array2, result_bit_array));
}

Object bit_xor (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_XOR, bit_array1, bit_array2, result_bit_array));
}

Object bit_eqv (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_EQV, bit_array1, bit_array2, result_bit_array));
}

Object bit_nand (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_NAND, bit_array1, bit_array2, result_bit_array));
}

Object bit_nor (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_NOR, bit_array1, bit_array2, result_bit_array));
}

Object bit_andc1 (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_ANDC1, bit_array1, bit_array2, result_bit_array));
}

Object bit_andc2 (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_ANDC2, bit_array1, bit_array2, result_bit_array));
}

Object bit_orc1 (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_ORC1, bit_array1, bit_array2, result_bit_array));
}

Object bit_orc2 (bit_array1, bit_array2, result_bit_array)
    Object bit_array1, bit_array2, result_bit_array;
{
    return(do_bit(BIT_ORC2, bit_array1, bit_array2, result_bit_array));
}

Object bit_not (bit_array1, result_bit_array)
    Object bit_array1, result_bit_array;
{
    return(do_bit(BIT_NOT, bit_array1, NIL, result_bit_array));
}

