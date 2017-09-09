/*
 * special.c -  Chestnut Run-Time Library entry for special variable definitions
 *
 * Author :  Chun Tian (binghe) <binghe.lisp@gmail.com>
 * Date   :  26 Jun 2009
 *
 * Copyright (c) 2009 Versata Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Versata Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_SUPPORT_THREAD

TLS struct SI_Tls_data  *SI_Special_data;
TLS struct SI_Tls_count *SI_Special_count;

static SI_Size_type SI_Special_data_size = 0;
static SI_Size_type SI_Special_count_size = 0;

struct SI_Tls_data* SI_init_tls_data(SI_Size_type size)
{
    void *result;

    /* Main thread only, set the real size of TLS block */
    if (!SI_Special_data_size)
        SI_Special_data_size = size;

    result = malloc(SI_Special_data_size);

    if (result)
        memset(result, 0, SI_Special_data_size);
    else {
        fprintf(stdout, "SI_init_tls_data: not enough memory for SI_Special_data\n");
        (void)exit(1);
    }

    return (struct SI_Tls_data*) result;
}

struct SI_Tls_count* SI_init_tls_count(SI_Size_type size)
{
    void *result;

    /* Main thread only, set the real size of TLS block */
    if (!SI_Special_count_size)
        SI_Special_count_size = size;

    result = malloc(SI_Special_count_size);

    if (result)
        memset(result, 0, SI_Special_count_size);
    else {
        fprintf(stdout, "SI_init_tls_cnout: not enough memory for SI_Special_count\n");
        (void)exit(1);
    }

    return (struct SI_Tls_count*) result;
}

/* NOTE: add SYMBOL_VALUE_IN_THREAD here! -- binghe, 2009/9/18 */

#endif
