/*
 * mchintyp.c -  Chestnut Run-Time Library entry for function machine_type
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




Object machine_type ()
{
    Declare_local_temp;
#ifdef MSDOS
    SI_Declare_static_string(str, d, "IBM PC");
#else
#ifdef sparc
    SI_Declare_static_string(str, d, "SPARC");
#else
    SI_Declare_static_string(str, d, "C");
#endif
#endif
    return VALUES_1(str);
}
