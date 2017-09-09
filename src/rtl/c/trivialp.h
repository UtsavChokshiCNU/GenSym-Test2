/*--rth-h-start--
  * trivialp.h - generic templetes for domain-converters
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#define TRIVIALP_1(fname, mname) \
    Object fname(x) Object x; \
{ \
    Declare_local_temp; \
    return VALUES_1(mname(x) ? T : NIL);  \
}

