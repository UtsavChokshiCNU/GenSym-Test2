/*
 * ctrlvars.c - various control global variables
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

/*
Object Call_arguments_limit = CALL_ARGUMENTS_LIMIT;
Object Multiple_values_limit = CALL_ARGUMENTS_LIMIT;
*/
Object Lambda_parameters_limit = CALL_ARGUMENTS_LIMIT;

TLS Object SI_Called_function = NIL;

TLS int Values_count = 1;
TLS Object Values[MAXARGS];		/* values stack for multiple-value functions */
TLS Object SI_First_value = NIL;	/* same as "result" */

TLS Object Temp1 = NIL;  		/* dummy variable */
TLS Object T_temp = NIL;  		/* dummy variable */
TLS UCHAR Tempu = 0;			/* dummy variable */

/* Temp variables used by FLI */
TLS SI_Ulong UL_temp = 0;
TLS SI_Long L_temp = 0;
TLS SI_Long L_temp1 = 0;

#ifdef KLUDGE_DOUBLE_FLOATS
Double_float_kludge_union SI_Double_float_kludge_temp;
Double_float_kludge_union SI_Double_float_kludge_temp1;
#endif

TLS SI_Special_frame *SI_Special_stack = NULL;      /* TLSed by binghe, 2009/4/18 */
TLS SI_Catch_frame *SI_Catch_stack = NULL;          /* TLSed by binghe, 2009/4/18 */
TLS SI_Frontier_frame *SI_Frontier_stack = NULL;    /* TLSed by binghe, 2009/8/25 */

void SI_ctrlvars_ENSURE() { }
