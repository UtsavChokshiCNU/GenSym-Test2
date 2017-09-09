/*
 * sngppnd2.c -  Chestnut Run-Time Library entry for function string_append2
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




Object string_append2 (a, b)
    Object	a, b;
{
    Declare_local_temp;
    Object result;
    char *str, tempstr[2];
    long size = 0;
    DECLARE_AREA(prev_area); DECLARE_FRONTIER(prev_pos);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(a,b);
    PROTECTI_1(result);

    BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
    if (CHARACTERP(a))
	size++;
    else
	size += ilength(STRING(a));
    if (CHARACTERP(b))
	size++;
    else
	size += ilength(STRING(b));
    END_LOCAL_ALLOCATION(prev_area, prev_pos);
    result = make_string(FIX(size), KOPT);
    str = ISTRING(result);
    BEGIN_LOCAL_ALLOCATION(prev_area, prev_pos);
    if (CHARACTERP(a)) {
	str[0] = ICHAR_CODE(a);
        str[1] = '\0';
    }
    else {
        strcpy(str, ISTRING(a));
    }
    if (CHARACTERP(b)) {
	tempstr[0] = ICHAR_CODE(b);
        tempstr[1] = '\0';
	strcat(str, tempstr);
    }
    else {
	strcat(str, ISTRING(b));
    }
    END_LOCAL_ALLOCATION(prev_area, prev_pos);
    RESTORE_STACK();
    return VALUES_1(result);
}
