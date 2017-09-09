/*
 * stat_arr.h - static array allocation generic definition
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

extern Object SI_make_static_array();

#define MAKE_STATIC_ARRAY(type,nargs) \
    Object result; \
    va_list ap; \
    SI_va_start(ap,nargs); \
    result = SI_make_static_array(type,nargs,ap); \
    va_end(ap); \
    return result
    
