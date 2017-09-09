/*
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */
 
#include "runtime.h"

extern Object Pcl;
extern Object Qminus;
extern Object Qplus_plus_plus;
extern Object Qplus_plus;
extern Object Qplus;
extern Object Qslashslashslash;
extern Object Qslashslash;
extern Object Qslash;
extern Object Qstar_star_star;
extern Object Qstar_star;
extern Object Qstar;

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern void SI_set_symbol_value_location(Object symbol, Object *address);

#else

extern void SI_add_external_root();
extern void SI_set_symbol_value_location();

#endif



#if SI_SUPPORT_MF
Object Eval_hook = NIL;
Object Apply_hook = NIL;
#endif
 
Object Star = UNBOUND;			/* "*" */
Object Star_star = UNBOUND;		/* "**" */
Object Star_star_star = UNBOUND;	/* "***" */
Object Plus = UNBOUND;			/* "+" */
Object Plus_plus = UNBOUND;		/* "++" */
Object Plus_plus_plus = UNBOUND;	/* "+++" */
Object Us = UNBOUND;			/* "-" */
Object Sl = UNBOUND;			/* "/" */
Object Sl_sl = UNBOUND;			/* "//" */
Object Sl_sl_sl = UNBOUND;		/* "///" */

extern Object Macroexpand_hook;
 
void SI_INIT_evals ()
{
   extern Object NEW_SYMBOL();
   extern void SI_INIT_packages();

#if SI_SUPPORT_MF
  PROTECT_GLOBAL(Eval_hook);
  Eval_hook = NIL;
#endif

#if SI_SUPPORT_MF
  PROTECT_GLOBAL(Apply_hook);
  Apply_hook = NIL;
#endif

#undef INIT_VAR
#define INIT_VAR(var, sym, name) \
    sym = NEW_SYMBOL(Pcl, name, TRUE);\
    PROTECT_GLOBAL(var); \
    var = NIL; \
    SET_SYMBOL_VALUE_LOCATION(sym, var)


  SI_INIT_packages();
  INIT_VAR(Star, Qstar, "*");
  INIT_VAR(Star_star, Qstar_star, "**");
  INIT_VAR(Star_star_star, Qstar_star_star, "***");
  INIT_VAR(Plus, Qplus, "++");
  INIT_VAR(Plus_plus, Qplus_plus, "++");
  INIT_VAR(Plus_plus_plus, Qplus_plus_plus, "+++");
  INIT_VAR(Us, Qminus, "-");
  INIT_VAR(Sl, Qslash, "/");
  INIT_VAR(Sl_sl, Qslashslash, "//");
  INIT_VAR(Sl_sl_sl, Qslashslashslash, "///");
#undef INIT_VAR

}

