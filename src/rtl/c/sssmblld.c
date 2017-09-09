/*
 * sssmblld.c -  Chestnut Run-Time Library entry for function SI_set_symbol_field
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

#if SI_USE_PROTOTYPES

extern Object SI_cons(void);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern void SI_fatal_error(char *lstr, ...);
extern Object SI_set_symbol_field_in_thread(Object sym, Object value, enum SI_Symbol_field field, Object thread);

#else

extern Object SI_cons();
extern Object (*SI_error_fptr) ();
extern void SI_fatal_error();
extern Object SI_set_symbol_field_in_thread();

#endif



extern Object SI_Plist_of_nil;

/* Object SI_symbol_field(symbol, field)
 * Object symbol;
 * enum SI_Symbol_field field;
 *
 * Object SI_set_symbol_field(symbol, value, field)
 * Object symbol, value;
 * enum SI_Symbol_field field;
 *
 * These functions provide a level of abstraction on the access to fields of
 * symbols.  These functions must not modify the values count.  There are a
 * couple of reasons for these.  First, the representation of NIL as a symbol
 * is hidden here, so the actual representation doesn't affect symbol accesses.
 * Second, the accesses to fields is centralized in these two functions so we
 * can provide different implementation strategies for the fields, without
 * having lots of code affected by the differences between such strategies.
 */

#define VALUE_INDICATOR	     	SI_MAKE_TOKEN(SI_TOKEN_ID_VALUE)
#define FUNCTION_INDICATOR     	SI_MAKE_TOKEN(SI_TOKEN_ID_FUNCTION)
#define SETF_FUNCTION_INDICATOR SI_MAKE_TOKEN(SI_TOKEN_ID_SETF_FUNCTION)
#define NAME_INDICATOR		SI_MAKE_TOKEN(SI_TOKEN_ID_NAME)

#if SI_SUPPORT_THREAD
Object SI_set_symbol_field(sym, value, field)
  Object sym, value;
  enum SI_Symbol_field field;
{
    return SI_set_symbol_field_in_thread(sym, value, field, SI_current_thread());
}

Object SI_set_symbol_field_in_thread(sym, value, field, thread)
  Object thread;
#else
Object SI_set_symbol_field(sym, value, field)
#endif
  Object sym, value;
  enum SI_Symbol_field field;
{
    Declare_local_temp;
  Declare_protect(3);
  Declare_area(a);
  Object key, tail, temp, prev;

  PROTECT_LOCALS();
  PROTECT_2(sym, value);
  PROTECTI_1(key);

  if (sym == NIL)

#if 1
    switch (field) {
      case SI_SymFn:
      case SI_SymFbnd:
	(void)error(1, "Attempt to modify the function of NIL.");
	/*NOTREACHED*/
      case SI_SymVal:
      case SI_SymBnd:
	(void)error(1, "Attempt to modify the value of NIL.");
	/*NOTREACHED*/
      case SI_SymSetfFn:
      case SI_SymSetfFbnd:
	(void)error(1, "Attempt to modify the SETF function of NIL.");
	/*NOTREACHED*/
      case SI_SymPlist:
	UNPROTECT_LOCALS();
	return SI_Plist_of_nil = value;
      case SI_SymName:
	(void)error(1, "Attempt to modify the name of NIL.");
	/*NOTREACHED*/
      case SI_SymValLoc:
      case SI_SymFnLoc:
        SI_fatal_error("Don't indirect NIL via value cell!");
        /*NOTREACHED*/
      default:
	SI_fatal_error("Invalid set_symbol_field indicator %d.", (int)field);
	/*NOTREACHED*/
    }
#else
  /* *** a space-saving alternative *** */
  printf("\nSI_set_s_field: %d ( %p ) is NULL ", &sym, &sym);
#endif


  else { /* sym != NIL */

    if (field == SI_SymPlist) {
	prev = Nil;
	for (tail = SI_SYMBOL_PLIST(sym); CONSP(tail);
	     prev = M_CDR(tail), tail = M_CDR(prev)) {
	    key = M_CAR(tail);
            if (key != FUNCTION_INDICATOR &&
		key != VALUE_INDICATOR &&
		key != SETF_FUNCTION_INDICATOR &&	
		key != NAME_INDICATOR)
		break;
	}
	if (TRUEP(prev)) {
	    RPLACD(prev, value);
	    UNPROTECT_LOCALS();	
	    return value;
	}
	else {
	    UNPROTECT_LOCALS();
	    return SI_SYMBOL_PLIST(sym) = value;	    
	}
    }

#define SEARCH_PLIST() \
    for (tail = SI_SYMBOL_PLIST(sym); CONSP(tail); tail = M_CDDR(tail)) \
      if (EQ(M_CAR(tail), key)) { tail = M_CDR(tail); break; }

    switch (field) {
      case SI_SymFn:
      case SI_SymFbnd:
	key = FUNCTION_INDICATOR;
	break;
      case SI_SymVal:
      case SI_SymBnd:
	key = VALUE_INDICATOR;
	break;
      case SI_SymSetfFn:
      case SI_SymSetfFbnd:
	key = SETF_FUNCTION_INDICATOR;
	break;
      case SI_SymName:
	key = NAME_INDICATOR;
	break;
      case SI_SymValLoc:
	key = VALUE_INDICATOR;
	tail = NIL;		/* assume only called if no entry present. */
	goto skip_search;
      case SI_SymFnLoc:
	key = FUNCTION_INDICATOR;
	tail = NIL;		/* assume only called if no entry present. */
	goto skip_search;
      default:
	SI_fatal_error("Invalid set_symbol_field indicator %d.", (int)field);
	/*NOTREACHED*/
    }
    SEARCH_PLIST();
skip_search:
    if (CONSP(tail)) {
      key = M_CAR(tail);
      if (VALUE_CELL_P(key)) {
#if SI_SUPPORT_THREAD
          short index;
          index = SI_THREAD_INDEX(thread);
          if (VALUE_CELL_LOCAL_COUNT(key, index))
              *(VALUE_CELL_LOCAL_LOCATION(key, index)) = value;
          else
              *(VALUE_CELL_LOCATION(key)) = value;
#else
          *(VALUE_CELL_LOCATION(key)) = value;
#endif
      }
      else M_CAR(tail) = value;
    }
    /* When no entry present, (f)makunbound is done. */
    else if (SI_ENUM_GT(field, SI_SymFldBnd)) {
      SAVE_CURRENT_AREA(a);
      if (Current_area != &Static_area) {
	if (USYMBOLP(sym))
	  SET_CURRENT_AREA(Dynamic_area);
	else
	  SET_CURRENT_AREA(Static_area);
      }
      /* Don't use cons(), since that would set values count. */
      temp = SI_cons();
      M_CAR(temp) = value;
      M_CDR(temp) = SI_SYMBOL_PLIST(sym);
      tail = SI_cons();
      M_CAR(tail) = key;
      M_CDR(tail) = temp;
      RESTORE_CURRENT_AREA(a);
      SI_SYMBOL_PLIST(sym) = tail;
    }
  }
  UNPROTECT_LOCALS();
  return value;

#undef SEARCH_PLIST
}
