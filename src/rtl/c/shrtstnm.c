/*
 * shrtstnm.c -  Chestnut Run-Time Library entry for function short_site_name
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


/* If you want to set up a site name, a good place to do so would be in
   main.c.  For example, the following would extract site names from the
   Unix process environment:

    extern Object Short_site_name_string, Long_site_name_string;
    extern Object istring_to_string();
    char *p;

    p = getenv("SHORT_SITE_NAME");
    if (p != NULL)
        Short_site_name_string = istring_to_string(p);
    p = getenv("LONG_SITE_NAME");
    if (p != NULL)
        Long_site_name_string = istring_to_string(p);

   See also SI_INIT_misc() for part of their initialization.
 */

Object Short_site_name_string = UNBOUND;
Object Long_site_name_string = UNBOUND;

Object short_site_name ()
{
    Declare_local_temp;
    return VALUES_1(Short_site_name_string);
}

Object long_site_name ()
{
    Declare_local_temp;
    return VALUES_1(Long_site_name_string);
}

