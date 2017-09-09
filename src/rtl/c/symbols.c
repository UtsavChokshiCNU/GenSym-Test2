/*
 * symbols.c - LISPTOC symbols functions
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern void SI_fatal_error(char *lstr, ...);
extern Object STATIC_STRING(char *s);
extern Object SI_symbol_field_in_thread(Object sym, enum SI_Symbol_field field, Object thread);

#else

extern void SI_add_external_root();
extern void SI_fatal_error();
extern Object STATIC_STRING();
extern Object SI_symbol_field_in_thread();

#endif




/* The object NIL
 *
 * There are presently two basic representations of NIL provided, based on the
 * value of SI_NIL_IS_ZERO.  If SI_NIL_IS_ZERO then NIL is defined as a
 * preprocessor macro whose value is 0.  Otherwise, NIL is represented as a
 * cons, in order to make CAR, CDR, and similar operations fast.
 *
 * In either case, the values associated with the various symbol accessors are
 * maintained someplace other than as fields in the NIL object.  See
 * symbol_field() and set_symbol_field().
 */

Object SI_Plist_of_nil = UNBOUND;
static Object Name_of_nil = UNBOUND;
static Object Ptr_to_T = UNBOUND;


#if !SI_NIL_IS_ZERO
#if SI_OBJECT_INITIALIZERS_WORK
#if SI_CONSES_HAVE_HEADERS
SI_Cons_constant SI_Nil_untagged = {SI_STATIC_HEADER(NIL_TYPE, 0), NIL, NIL};
#else
SI_Cons_constant SI_Nil_untagged = {SI_STATIC_RELOCATION_INFO NIL, NIL};
#endif /* SI_CONSES_HAVE_HEADERS */
#else
Object NIL = UNBOUND;
#endif /* SI_OBJECT_INITIALIZERS_WORK */
#endif /* !SI_NIL_IS_ZERO */

/* the object T
 *
 * T must be a symbol present in the Lisp package with value T. The
 * name of such an object in RTL is T [with a nickname Qt ]
 *
 * In oder to allow T to appear in static initializers,
 * it is allocated explicitly either statically or dynamically and
 * then interned in the package. The "body" of statically allocated T
 * is SI_T_untagged
 *
 * The approach makes it possible to hide the T magic away from users
 * eyes
 */

#if SI_OBJECT_INITIALIZERS_WORK
SI_Static_T SI_T_untagged = 
    {{SI_STATIC_RELOCATION_INFO {SI_HEADER(EMSYMBOL_TYPE, 0), UNBOUND}, UNBOUND}, {'T', '\0'}};
#else
Object T = UNBOUND;
#endif /* SI_OBJECT_INITIALIZERS_WORK */

void SI_INIT_NIL()		/* This has to be called very early. */
{

# if (!SI_NIL_IS_ZERO && !SI_OBJECT_INITIALIZERS_WORK)
  Declare_area(a);
# endif

  static int initializedp = FALSE;

  if (!initializedp) {
    initializedp = TRUE;
# if (!SI_NIL_IS_ZERO && !SI_OBJECT_INITIALIZERS_WORK)
    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
#   if SI_CONSES_HAVE_HEADERS
     NIL = SI_ALLOC(SI_Cons, NIL_TYPE, SI_SYMBOL_TAG, SI_NORMAL);
#   else
#    if (SI_TAG_WIDTH > 1)
       NIL = SI_cons();
#      include "Tag of Nil needs to be changed to SI_SYMBOL_TAG."
#    else
#      include "SI_INIT_NIL: Invalid configuration."
#    endif /* SI_TAG_WIDTH */
#   endif /* SI_CONSES_HAVE_HEADERS */
    M_CAR(NIL) = NIL;
    M_CDR(NIL) = NIL;
    RESTORE_CURRENT_AREA(a);
# endif
    SI_Plist_of_nil = NIL;
    PROTECT_GLOBAL(SI_Plist_of_nil);
  }
}

void SI_INIT_T()
{

#if !SI_OBJECT_INITIALIZERS_WORK
  Declare_area(a);
  SI_Size_type nextlen;

    SAVE_CURRENT_AREA(a);

    SET_CURRENT_AREA(Static_area);
    nextlen = sizeof(SI_Noninitial_symbol) + strlen("T") + 1;
    T = SI_alloc(nextlen,
		      SI_ALIGNMENT_FOR(SI_Noninitial_symbol),
		      EMSYMBOL_TYPE,
		      SI_SYMBOL_TAG,
		      SI_UGLY);
    RESTORE_CURRENT_AREA(a);
    MSYMBOL_NAME(T) = "T";
#else
    /* SI_T_untagged  alredy allocated statically, T points on it  */
#endif

    Ptr_to_T = T;
    SI_SYMBOL_PLIST(T) = NIL; /* NIL alredy exists */
    PROTECT_GLOBAL(Ptr_to_T);

}

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
Object SI_symbol_field(sym, field)
  Object sym;
  enum SI_Symbol_field field;
{
    return SI_symbol_field_in_thread(sym, field, SI_current_thread());
}

Object SI_symbol_field_in_thread(sym, field, thread)
  Object thread;
#else
Object SI_symbol_field(sym, field)
#endif
  Object sym;
  enum SI_Symbol_field field;
{
    Declare_local_temp;
  Object res, key, tail;

  if (sym == NIL)
    switch (field) {
      case SI_SymFn:		return UNBOUND;
      case SI_SymFbnd:		return NIL;
      case SI_SymSetfFn:	return UNBOUND;
      case SI_SymSetfFbnd:	return NIL;
      case SI_SymVal:		return NIL;
      case SI_SymBnd:		return T;
      case SI_SymPlist: 	return SI_Plist_of_nil;
      case SI_SymName:
	if (Name_of_nil == UNBOUND) Name_of_nil = STATIC_STRING("NIL");
	return Name_of_nil;
      case SI_SymValLoc:
        SI_fatal_error("Don't indirect NIL via value cell!");
        /*NOTREACHED*/
      default:
	SI_fatal_error("Invalid symbol_field indicator %d.", (int)field);
        /*NOTREACHED*/
    }
  else { /* sym != NIL */

    if (field == SI_SymPlist) {
	for (tail = SI_SYMBOL_PLIST(sym); CONSP(tail); tail = M_CDDR(tail)) {
	    key = M_CAR(tail);
            if (key != FUNCTION_INDICATOR &&
		key != VALUE_INDICATOR &&
		key != SETF_FUNCTION_INDICATOR &&	
		key != NAME_INDICATOR)
		break;
	}
	return tail;
    }

#undef SEARCH_PLIST

#define SEARCH_PLIST() \
    res = UNBOUND; \
    for (tail = SI_SYMBOL_PLIST(sym); CONSP(tail); tail = M_CDDR(tail)) \
      if (EQ(M_CAR(tail), key)) { res = M_CADR(tail); break; }

    switch (field) {
      case SI_SymFn:
      case SI_SymFbnd:
	/* Currently, the function is always stored as a property. */
	key = FUNCTION_INDICATOR;
	break;
      case SI_SymVal:
      case SI_SymBnd:
	/* Currently, the value is always stored as a property. */
	key = VALUE_INDICATOR;
	break;
      case SI_SymSetfFn:
      case SI_SymSetfFbnd:
	key = SETF_FUNCTION_INDICATOR;
	break;
      case SI_SymValLoc:
	key = VALUE_INDICATOR;
	SEARCH_PLIST();
	if (res == UNBOUND) return NIL;
	else if (VALUE_CELL_P(res)) return res;
	else return M_CDR(tail);
      case SI_SymName:
	if (USYMBOLP(sym)) return USYMBOL_NAME(sym);
	else {
	  key = NAME_INDICATOR;
	  SEARCH_PLIST();
	  return res;
	}
      default:
	SI_fatal_error("Invalid symbol_field indicator %d.", (int)field);
    }
    SEARCH_PLIST();
    if (VALUE_CELL_P(res)) {
#if SI_SUPPORT_THREAD
        short index;
        index = SI_THREAD_INDEX(thread);
        if (VALUE_CELL_LOCAL_COUNT(res, index))
            res = *(VALUE_CELL_LOCAL_LOCATION(res, index));
        else
            res = *VALUE_CELL_LOCATION(res);
#else
        res = *VALUE_CELL_LOCATION(res);
#endif
    }
    switch (field) {
      case SI_SymBnd:
        return (res != UNBOUND || EQ(sym, T) || KEYWORDP(sym)) ? T : NIL;
      case SI_SymVal:
        return (res == UNBOUND && (EQ(sym, T) || KEYWORDP(sym))) ? sym : res;
      default:
        if (SI_ENUM_LE(field, SI_SymFldBnd)) return (res == UNBOUND) ? NIL : T;
	else return res;
    }
#undef SEARCH_PLIST
  }
  /*NOTREACHED*/
}
