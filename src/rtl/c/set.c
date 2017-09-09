/*
 * set.c -  Chestnut Run-Time Library entry for function set
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object SI_set_symbol_value_helper();

Object set (symbol,value)
    Object symbol, value;
{
    Declare_local_temp;
  return VALUES_1(SI_set_symbol_value_helper(symbol, value)); 
}
