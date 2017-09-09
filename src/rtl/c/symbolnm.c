/*
 * symbolnm.c -  Chestnut Run-Time Library entry for function symbol_name
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern char *Initial_symbol_names[];
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object istring_to_string(char *istring);

#else

extern Object SI_set_symbol_field();
extern Object SI_symbol_field();
extern Object istring_to_string();

#endif




#define CACHE_SYMBOL_NAMES

Object symbol_name(sym)
  Object sym;
{
    Declare_local_temp;
  Object name;
  char *iname;
  Declare_area(a);

  name = SI_symbol_field(sym, SI_SymName);
  if (name == UNBOUND) {
    switch (ISYMBOL_TYPE(sym)) {
      case MSYMBOL_TYPE:
      case EMSYMBOL_TYPE:
      case MKEYWORD_TYPE:
	iname = MSYMBOL_NAME(sym);
	break;
      default:
	iname = ISYMBOL_NAME(sym);
	break;
    }
#ifdef CACHE_SYMBOL_NAMES
    /* *** This is kind of bogus, since it statically allocates the name
     * *** and field entry for all symbols.  Should probably check symbol
     * *** type and base the consing area on that.
     */
    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);	/* Inhibits GC */
    name = istring_to_string(iname);
    SI_set_symbol_field(sym, name, SI_SymName);
    RESTORE_CURRENT_AREA(a);
#else
    name = istring_to_string(iname);
#endif
  }
  return VALUES_1(name);
}
