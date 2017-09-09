/*
 * frcutput.c -  Chestnut Run-Time Library entry for function force_output
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object finish_output(Object);

#else

extern Object finish_output();

#endif




Object force_output (output_stream)
    Object output_stream;
{
    return(finish_output(output_stream));
}
