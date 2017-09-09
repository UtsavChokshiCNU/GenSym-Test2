/*
 * fnshtm.c -  Chestnut Run-Time Library entry for function finish_time
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Internal_time_units_per_second;
extern Object Trace_output;

#if SI_USE_PROTOTYPES

extern Object divide(Object a, Object b);
extern Object format(long n, Object destination, char *control_string, ...);
extern Object get_internal_real_time(void);
extern Object get_internal_run_time(void);
extern Object lfloat(Object,Object);
extern Object minus(Object a, Object b);

#else

extern Object divide();
extern Object format();
extern Object get_internal_real_time();
extern Object get_internal_run_time();
extern Object lfloat();
extern Object minus();

#endif



static void print_time_info();

/* This doesn't try to account for the overhead of calling
 * get-internal-real-time and get-internal-run-time. */
Object finish_time(start_run, start_real)
  Object start_run, start_real;
{
    Declare_local_temp;
  Declare_protect(4);
  Object end_run, end_real;

  PROTECT_LOCALS();
  PROTECT_2(start_run, start_real);
  PROTECTI_2(end_run, end_real);

  end_run = get_internal_run_time();
  end_real = get_internal_real_time();

  print_time_info("~&Runtime:  ~D seconds", start_run, end_run);
  print_time_info("~&Realtime: ~D seconds", start_run, end_run);

  UNPROTECT_LOCALS();
  return VALUES_1(NIL);
}

static void print_time_info(str, start, end)
  char *str;
  Object start, end;
{ Declare_protect(1);
  Object temp;

  PROTECT_LOCALS();
  PROTECT_1(end);

  temp = lfloat(start, KOPT);
  temp = minus(end, temp);
  temp = divide(temp, Internal_time_units_per_second);
  (void)format(3, Trace_output, str, temp);
  UNPROTECT_LOCALS();
}
