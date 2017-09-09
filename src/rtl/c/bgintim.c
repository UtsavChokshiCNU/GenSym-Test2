/*
 * bgintim.c -  Chestnut Run-Time Library entry for function begin_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object get_internal_real_time(void);
extern Object get_internal_run_time(void);

#else

extern Object get_internal_real_time();
extern Object get_internal_run_time();

#endif




Object begin_time()
{ Declare_protect(1);
  Object run, real;

  PROTECT_LOCALS();
  PROTECTI_1(run);

  run = get_internal_run_time();
  real = get_internal_real_time();

  UNPROTECT_LOCALS();
  return VALUES_2(run, real);
}
