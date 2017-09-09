/*
 * Copyright (C) 1989-1991 Chestnut Software, Inc.  All Rights Reserved.
 */

#include "runtime.h"

extern Object Pcl;
extern Object Qand_allow_other_keys;
extern Object Qand_aux;
extern Object Qand_body;
extern Object Qand_environment;
extern Object Qand_key;
extern Object Qand_optional;
extern Object Qand_rest;
extern Object Qand_whole;
extern Object Qlambda_list_keywords;

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern void SI_set_symbol_value_location(Object symbol, Object *address);
extern Object list(long,...);

#else

extern void SI_add_external_root();
extern void SI_set_symbol_value_location();
extern Object list();

#endif



#ifndef LAZILY_INITIALIZED_PACKAGES

extern Object SI_NEW_SYMBOL(/* Object *package, char *name, int externalp */);
#undef NEW_SYMBOL
#define NEW_SYMBOL(pkg, name, externalp) SI_NEW_SYMBOL(&pkg, name, externalp)

#endif

Object Lambda_list_keywords = UNBOUND;

/* must be called in static space context */
void SI_INIT_lambda_lists ()
{
  Qand_optional = NEW_SYMBOL(Pcl,"&OPTIONAL",TRUE);
  Qand_rest = NEW_SYMBOL(Pcl,"&REST",TRUE);
  Qand_key = NEW_SYMBOL(Pcl,"&KEY",TRUE);
  Qand_allow_other_keys = NEW_SYMBOL(Pcl,"&ALLOW-OTHER-KEYS",TRUE);
  Qand_aux = NEW_SYMBOL(Pcl,"&AUX",TRUE);
  Qand_body = NEW_SYMBOL(Pcl,"&BODY",TRUE);
  Qand_environment = NEW_SYMBOL(Pcl,"&ENVIRONMENT",TRUE);
  Qlambda_list_keywords = NEW_SYMBOL(Pcl,"LAMBDA-LIST-KEYWORDS",TRUE);
  PROTECT_GLOBAL(Lambda_list_keywords);
  Lambda_list_keywords =
    list(8, Qand_optional, Qand_rest, Qand_key, Qand_allow_other_keys,
	 Qand_aux, Qand_whole, Qand_body, Qand_environment);
  SET_SYMBOL_VALUE_LOCATION(Qlambda_list_keywords, Lambda_list_keywords);
}

