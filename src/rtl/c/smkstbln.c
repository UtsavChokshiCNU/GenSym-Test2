/*
 * smkstbln.c -  Chestnut Run-Time Library entry for function SI_make_hash_table_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */


#include "runtime.h"

extern Object Krehash_size;
extern Object Krehash_threshold;
extern Object Ksize;
extern Object Ktest;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object make_hash_table(Object test, Object size, Object rehash_size, Object rehash_threshold);

#else

extern Object SI_obtain_rest_list();
extern Object make_hash_table();

#endif



/*VARARGS*/
Object SI_make_hash_table_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_0();
        KEYWORD_ARGS_4(Ktest, k1, Ksize, k2, Krehash_size, k3, Krehash_threshold, k4);
    END_ARGS();
    return make_hash_table(k1, k2, k3, k4);
}

