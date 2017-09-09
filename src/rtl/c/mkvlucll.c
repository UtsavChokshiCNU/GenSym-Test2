/*
 * mkvlucll.c -  Chestnut Run-Time Library entry for function make_value_cell
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Dynamic_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
#include <assert.h>

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);

#else

extern void SI_add_external_root();
extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern Object SI_set_symbol_field();
extern Object SI_symbol_field();

#endif




/* SI_set_symbol_value_location() is used by the SET_SYMBOL_VALUE_LOCATION
 * macro, which is generated in initsyms.c and in user toplevel forms in order
 * to establish the correspondence between a symbol and the address of the
 * global variable that holds its value.
 *
 * There is a bit of hair here because it may be called multiple times and may
 * be called after a value has been assigned directly to the *symbol*.  The
 * translator arranges for a call to this to occur before any possible
 * references to the C variable by emitting calls on a per file basis.
 * However, if a previous file called (say) SET with a computed argument, then
 * the symbol would already have a value, which must be installed in the C
 * variable by this function.  Unfortunately, this means that this function has
 * to have low level knowledge about how the value cell is found, which
 * violates the abstraction introduced by SI_symbol_field().  To fix this, we
 * introduce a new field code called SI_SymValLoc, just for use by this guy.
 */

static Object make_value_cell(symbol, address)
  Object symbol;
  Object *address;
{ Declare_area(a);
  Object vcell;
#if SI_SUPPORT_THREAD
  int i;
#endif

  /* Allocate the value cell in space determined by the symbol type. */
  SAVE_CURRENT_AREA(a);
  if (Current_area != &Static_area) {
    if (USYMBOLP(symbol))
      SET_CURRENT_AREA(Dynamic_area);
    else
      SET_CURRENT_AREA(Static_area);
  }

#if SI_VISIT_EXACTLY_ONCE

  /* *** Wrong tag here. *** */
  vcell = SI_ALLOC(SI_Value_cell, VALUE_CELL_TYPE,
		   SI_INSTANCE_TAG, SI_BORING);
  /* To provide VISIT_EXACTLY_ONCE guarantees to the garbage collector,
     we protect all globals directly as external roots, and not via
     value cells (which therefore become boring). */
  SI_add_external_root(address);

#else /* !SI_VISIT_EXACTLY_ONCE */

  /* *** Wrong tag here. *** */
  vcell = SI_ALLOC(SI_Value_cell, VALUE_CELL_TYPE,
		   SI_INSTANCE_TAG, SI_UGLY);

#endif /* !SI_VISIT_EXACTLY_ONCE */

  VALUE_CELL_LOCATION(vcell) = address;

#if SI_SUPPORT_THREAD
  for (i = 0; i < VALUE_CELL_SLOTS; ++i) {
      VALUE_CELL_LOCAL_COUNT(vcell, i) = 0;
  }
#endif

  RESTORE_CURRENT_AREA(a);
  return vcell;
}


void SI_set_symbol_value_location(symbol, address)
  Object symbol;
  Object *address;
{
    Declare_local_temp;
  Declare_protect(2);
  Object vcell, loc;

  PROTECT_LOCALS();
  PROTECT_1(symbol);
  PROTECTI_1(loc);

  if (symbol == NIL) error(2,"attempt to set location for symbol ~S", symbol);

  loc = SI_symbol_field(symbol, SI_SymValLoc);
  if (loc == NIL) {
    vcell = make_value_cell(symbol, address);
    SI_set_symbol_field(symbol, vcell, SI_SymValLoc);
  }
  else if (CONSP(loc)) {
    vcell = make_value_cell(symbol, address);
    *address = M_CAR(loc);
    M_CAR(loc) = vcell;
  }
  else 
    assert(VALUE_CELL_P(loc));
  UNPROTECT_LOCALS();
}      

void SI_set_symbol_function_location(symbol, address)
  Object symbol;
  Object *address;
{
    Declare_local_temp;
  Declare_protect(2);
  Object vcell, loc;

  PROTECT_LOCALS();
  PROTECT_1(symbol);
  PROTECTI_1(loc);

  if (symbol == NIL) error(2,"attempt to set location for symbol ~S", symbol);

  loc = SI_symbol_field(symbol, SI_SymFnLoc);
  if (loc == NIL) {
    vcell = make_value_cell(symbol, address);
    SI_set_symbol_field(symbol, vcell, SI_SymFnLoc);
  }
  else if (CONSP(loc)) {
    vcell = make_value_cell(symbol, address);
    *address = M_CAR(loc);
    M_CAR(loc) = vcell;
  }
  else 
    assert(VALUE_CELL_P(loc));
  UNPROTECT_LOCALS();
}      
