/*
 * fptrs.c - standard functional objects EQ, EQL, EQUAL
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

/* used by FP_EQx macros */
Object SI_fp_eql_1 = UNBOUND;
Object SI_fp_eq_1  = UNBOUND;
Object SI_fp_eq_2 = UNBOUND;


void SI_fptrs_ENSURE()  {}
