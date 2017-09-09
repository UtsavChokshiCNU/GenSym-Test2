/*
 * seqmodi.h - helper macros for sequence modification functions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "lists.h"

extern Object init_sequence_fn();

extern Object SI_fp_eq_1;
extern Object SI_fp_eq_2;

#define FP_EQ \
    (SI_fp_eq_1 == UNBOUND ? \
        SI_fp_eq_1 = STATIC_FUNCTION(eq, NIL, FALSE, 2, 2) : \
        SI_fp_eq_1)

#define FP_EQUAL \
    (SI_fp_eq_2 == UNBOUND ? \
        SI_fp_eq_2 = STATIC_FUNCTION(equal, NIL, FALSE, 2, 2) : \
        SI_fp_eq_2)

#define with_shorten_vector() \
static void shorten_vector(v, len) \
    Object v;\
    long len;\
{\
    if (SI_VECTOR_PRIMITIVE_P(v)) {\
	SI_shorten_primitive_vector(v, len);\
    }\
    else {\
	SI_GENERAL_VECTOR_FILL_POINTER(v) = FIX(len);\
    }\
}




