/*
 * artrgtsz.c -  Chestnut Run-Time Library entry for function area_target_size
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



/* Size to which area will grow before warning or GC. */

Object area_target_size(area_name)
    Object area_name;
{
    Declare_local_temp;
    Object temp1;
    SI_Area *area = SI_area_name_to_area(area_name);

    if (area != NULL)
	temp1 = VALUES_1(FIX(area->target_size));
    else 
	temp1 = warn(2, "area_target_size: unrecognized area - ~S",area_name);
    return(temp1);
}

Object area_target_size_as_float(area_name)
    Object area_name;
{
    Declare_local_temp;
    Object temp1;
    SI_Area *area = SI_area_name_to_area(area_name);

    if (area != NULL)
	temp1 = (Object)VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)(area->target_size)));
    else 
	temp1 = warn(2, "area_target_size: unrecognized area - ~S",area_name);
    return(temp1);
}
