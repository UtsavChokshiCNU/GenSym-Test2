/*
 * armmrlmt.c -  Chestnut Run-Time Library entry for function area_memory_limit
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern SI_Area *SI_area_name_to_area(Object area_name);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object cdouble_to_double(double n);

#else

extern SI_Area *SI_area_name_to_area();
extern Object (*SI_warn_fptr) ();
extern Object cdouble_to_double();

#endif



extern SI_Size_type area_total_size();

/* Amount of memory currently allocated.  "limit" is a misnomer. */ 

Object area_memory_limit(area_name)
    Object area_name;
{
    Declare_local_temp;
    Object temp1;
    SI_Area *area = SI_area_name_to_area(area_name);

    if (area != NULL)
	temp1 = VALUES_1(FIX(area_total_size(area)));
    else 
	temp1 = warn(2, "area_memory_limit: unrecognized area - ~S",area_name);
    return(temp1);
}

Object area_memory_limit_as_float(area_name)
    Object area_name;
{
    Declare_local_temp;
    Object temp1;
    SI_Area *area = SI_area_name_to_area(area_name);

    if (area != NULL)
	temp1 = (Object)VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)area_total_size(area)));
    else 
	temp1 = warn(2, "area_memory_limit: unrecognized area - ~S",area_name);
    return(temp1);
}

