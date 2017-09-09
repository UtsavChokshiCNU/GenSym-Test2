/*
 * concatnt.h - concatenation helper macro: place arguments onto the Stack
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#define SPREAD_ARGS(n, ap, ptr)  \
    do {                 \
        long _rest_index;                      \
        ptr = (Object *)Stack;               \
        Stack += n;                      \
        for(_rest_index = 0; _rest_index < n; ++_rest_index) \
            ptr[_rest_index]                 \
                = va_arg(ap, Object);        \
    } while(0)

