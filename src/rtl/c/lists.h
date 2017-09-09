/*
 * lists.h - list processing helper macros
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */
 
extern Object SI_fp_eql_1;
#define FP_EQL \
    (SI_fp_eql_1 == UNBOUND ? \
        SI_fp_eql_1 = STATIC_FUNCTION(eql, NIL, FALSE, 2, 2) : \
        SI_fp_eql_1)

/*
 * p : test function t vs. test function n flag
 * t : a function object of 2 arguments
 * n : a function object of 2 arguments
 * i : first argument for t or n
 * e : second argument
 *
 */
#define SATISFIESP(p,t,n,i,e) \
    (p ? TRUEP(funcall2(t,i,e)) : !TRUEP(funcall2(n,i,e)))

