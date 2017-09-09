/*
 * mkvctor.c -  Chestnut Run-Time Library entry for function make_vector
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object make_array();

#endif




/* extension */
Object make_vector (size, initial_element)
    Object size, initial_element;
{
    return(make_array(size,T,initial_element,KOPT,KOPT,KOPT,KOPT,KOPT));
}
