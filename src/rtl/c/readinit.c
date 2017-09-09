/*
 * readinit.c - the Reader initialization file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

Object Readtable  = UNBOUND;

Object Macroexpand_hook = NIL;

/*int    SI_init_reader_flag = FALSE; */

SI_readinit_ENSURE() {}
