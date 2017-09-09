/*
 * macros.c - LISPTOC macros functions
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object cons(Object,Object);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern Object macroexpand(Object form, Object env);
extern Object macroexpand_1(Object form, Object env);

#else

extern Object SI_set_symbol_field();
extern Object SI_symbol_field();
extern Object cons();
extern Object funcall2();
extern Object macroexpand();
extern Object macroexpand_1();

#endif


/* Ignore environment argument for now */
Object macro_function(symbol, environment)
    Object symbol, environment;
{
    Declare_local_temp;
    Object fun = SYMBOL_FUNCTION(symbol);
    if (!CONSP(fun) || (M_CAR(fun) != SI_MACRO_TOKEN))
	return VALUES_1(NIL);
    return VALUES_1(M_CDR(fun));
}

Object set_macro_function(sym, func)
    Object sym, func;
{
    Declare_local_temp;
    SET_SYMBOL_FUNCTION(sym, cons(SI_MACRO_TOKEN, func));
    return VALUES_1(func);
}

Object macroexpand(form, env)
    Object form, env;
{
    Object expansion, flag, change = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(form,env,change);
    PROTECTI_2(expansion,flag);
    MVS_2(macroexpand_1(form, env), expansion, flag);
    while (flag != NIL) {
	change = T;
	form = expansion;
	MVS_2(macroexpand_1(form, env), expansion, flag);
    }
    RESTORE_STACK();
    return VALUES_2(form, flag);
}

Object macroexpand_1(form, env)
    Object form, env;
{
    Declare_local_temp;
    Object probe, flag = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(form, env, flag);
    PROTECTI_1(probe);
    if (CONSP(form))  {
	probe = macro_function(M_CAR(form), env);
	if (probe != NIL) {
	    form = funcall2(probe, form, NIL);
	    flag = T;
	}
    }
    RESTORE_STACK();
    return(VALUES_2(form, flag));
}
