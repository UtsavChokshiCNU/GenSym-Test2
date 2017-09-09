/*
 * defset.h - defset helper macro
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#define DEFSET(name, macro) \
    Object name(tree, newval) \
        Object tree, newval; \
{ \
    Declare_local_temp; \
    macro(tree) = newval; \
	return VALUES_1(newval);  \
}

