/*
 * Input file:  C:\LISPTOC\EVALS.LSP
 * Translated on 12/07/89    6:45:34 pm
 * Copyright (C) 1989-1991 Chestnut Software, Inc.  All Rights Reserved.
 */

#include "runtime.h"

extern Object Apply_hook;
extern TLS SI_Area *Current_area;
extern Object Eval_hook;
extern Object Qquote;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern TLS SI_Special_frame *SI_Special_stack;

#if SI_USE_PROTOTYPES

extern long SI_re_throw(void);
extern Object eval_run(Object);

#else

extern int SI_re_throw();
extern Object eval_run();

#endif


Object evalhook(form,evalhookfn,applyhookfn,env)
    Object form;
    Object evalhookfn;
    Object applyhookfn;
    Object env;
{
    Object prev_evalhook;
    Object prev_applyhook;
    Object throw_p;
    Object temp1;
    extern Object Eval_hook;
    extern Object Apply_hook;
    Catch_buf old_env_1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(form,evalhookfn,applyhookfn,env);
    PROTECTI_4(prev_evalhook,prev_applyhook,throw_p,temp1);
    prev_evalhook = Eval_hook;
    prev_applyhook = Apply_hook;
    UNWIND_PROTECT(throw_p, old_env_1, LABEL1);
    Eval_hook = evalhookfn;
    Apply_hook = applyhookfn;
    temp1 = eval_run(form);
    BEGIN_UNWIND_PROTECT(old_env_1, LABEL1);
    Eval_hook = prev_evalhook;
    Apply_hook = prev_applyhook;
    END_UNWIND_PROTECT(throw_p, old_env_1);
    RESTORE_STACK();
    return(temp1);
}

Object applyhook(function,args,evalhookfn,applyhookfn,env)
    Object function;
    Object args;
    Object evalhookfn;
    Object applyhookfn;
    Object env;
{
#if 0
    Object prev_evalhook;
    Object prev_applyhook;
    Object temp1;
    extern Object Eval_hook;
    extern Object Apply_hook;
    Catch_buf old_env_1;

    prev_evalhook = Eval_hook;
    prev_applyhook = Apply_hook;
    UNWIND_PROTECT(throw_p, old_env_1, LABEL1);
    Eval_hook = evalhookfn;
    Apply_hook = applyhookfn;
    BEGIN_UNWIND_PROTECT(old_env_1, LABEL1);
    Eval_hook = prev_evalhook;
    Apply_hook = prev_applyhook;
    END_UNWIND_PROTECT(invisible_throw_p, old_env_1);
    return(temp1);
#else
    return VALUES_1(NIL);
#endif
}

/* Ignore environment argument for now */
Object constantp(obj, environment)
  Object obj, environment;
{
    Declare_local_temp;
  Object value;

  if (EQ(obj, NIL))
    value = T;
  else if (CONSP(obj))
    /* Minimal level of required support.  Implementations are permited to do
     * much more here, but we don't bother (see X3J13 CONSTANTP-DEFINITION). */
    value = EQ(M_CAR(obj), Qquote) ? T : NIL;
  else if (!SYMBOLP(obj))
    value = T;
  else {
    if (EQ(obj, T)) value = T;
    /* *** This is clearly wrong.
     * *** Need some way to recognize named constants. */
    else value = NIL;
  }
  return VALUES_1(value);
}
