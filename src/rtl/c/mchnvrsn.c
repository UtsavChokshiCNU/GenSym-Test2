/*
 * mchnvrsn.c -  Chestnut Run-Time Library entry for function machine_version
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object STATIC_STRING(char *s);

#else

extern Object STATIC_STRING();

#endif




Object machine_version ()
{
    Declare_local_temp;
  SI_Declare_static_string(str, d, "unknown");
  return VALUES_1(str);
}
