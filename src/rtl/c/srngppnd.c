/*
 * srngppnd.c -  Chestnut Run-Time Library entry for function string_append
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area;
extern SI_Area Local_area;
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern long SI_gc_count;

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern long ilength(Object sequence);
extern Object make_string(Object size, Object initial_element);
extern void restore_frontier(SI_Segment *seg, void *frontier);
extern Object string(Object);

#else

extern char *SI_istring();
extern long ilength();
extern Object make_string();
extern void restore_frontier();
extern Object string();

#endif


Object string_appendr (sequences)
    Object sequences;
{
    Declare_local_temp;
    Object result = NIL, temp, seq;
    long size = 0L;
    char tempstr[2];
    DECLARE_AREA(prev_area); DECLARE_FRONTIER(prev_pos);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(sequences,result);
    PROTECTI_2(temp,seq);
    for (temp = sequences; temp; temp = M_CDR(temp)) {
	BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
	seq = M_CAR(temp);
	if (CHARACTERP(seq))
	    size++;
	else
	    size += ilength(STRING(seq));
	END_LOCAL_ALLOCATION(prev_area, prev_pos);
    }
    result = make_string(FIX(size), KOPT);
    for (temp = sequences; temp; temp = M_CDR(temp)) {
	seq = M_CAR(temp);
	if (CHARACTERP(seq)) {
	    tempstr[0] = ICHAR_CODE(seq);
	    tempstr[1] = '\0';
	    strcat(ISTRING(result), tempstr);
	}
	else {
	    BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
	    strcat(ISTRING(result), ISTRING(seq));
	    END_LOCAL_ALLOCATION(prev_area, prev_pos);
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

