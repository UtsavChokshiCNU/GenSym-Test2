/*
 * adjstrry.c -  Chestnut Run-Time Library entry for function adjust_array
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


/*ARGSUSED*/
Object adjust_array (array, new_dimensions, element_type, initial_element,
	initial_contents, fill_pointer, displaced_to, displaced_index_offset)
    Object array, new_dimensions, element_type, initial_element,
	 initial_contents, fill_pointer, displaced_to, displaced_index_offset;
{
    Declare_local_temp;

#if 0
    enum SI_etype etype;
    Object arr;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_8(array, new_dimensions,element_type,initial_element,
	initial_contents, fill_pointer,displaced_to, displaced_index_offset);
    PROTECTI_1(arr);

    if (UNSUPPLIED_P(element_type)) {
	etype = SI_GENERAL_VECTOR_ETYPE(array);
	element_type = SVREF(Element_types, FIX(etype));
    }
    if (UNSUPPLIED_P(fill_pointer) && ARRAY_HAS_FILL_POINTER_P(array))
	fill_pointer = SI_GENERAL_VECTOR_FILL_POINTER(array);
    if (UNSUPPLIED_P(initial_contents)) {
	if (SI_VECTOR_PRIMITIVE_P(array))
	    initial_contents = SI_PRIMITIVE_VECTOR_CONTENTS(array,Object);
	else
	    initial_contents = warn(1, "adjust_array: initial_contents NYI");
    }

    if (SI_GENERAL_ARRAY_P(array)) {
	if (UNSUPPLIED_P(displaced_to))
	    displaced_to = SI_GENERAL_ARRAY_DISPLACED_TO(array);
        if (UNSUPPLIED_P(displaced_index_offset))
	    displaced_index_offset = SI_DISPLACED_INDEX_OFFSET(array);
    }
    arr = make_array (new_dimensions, element_type, initial_element, 
		initial_contents, T, fill_pointer,
		displaced_to, displaced_index_offset);
    /* must assign each of the new parts of arr to old array */
    if (SI_VECTOR_PRIMITIVE_P(array)) {
	SI_PRIMITIVE_VECTOR_CONTENTS(array) = 
		SI_PRIMITIVE_VECTOR_CONTENTS(arr);
	SI_GENERAL_VECTOR_TOTAL_SIZE(array) = 
		SI_GENERAL_VECTOR_TOTAL_SIZE(arr);
	SI_GENERAL_NVARRAY_DIMENSIONS(array) = 
		SI_GENERAL_NVARRAY_DIMENSIONS(arr);
    } else {
	warn(1, "adjust_array: NYI for general arrays");
    }
    RESTORE_STACK();
#endif
    return VALUES_1(array);
}
