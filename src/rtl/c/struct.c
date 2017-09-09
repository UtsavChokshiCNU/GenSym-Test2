/* struct.c -- defstruct support
 *
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 *
 */

#include "runtime.h"

#if SI_SUPPORT_CLOS
#include "externs.h"
#else

extern Object Kdefault;
extern Object Kinclude;
extern Object Ktest;
extern Object Qeq;
extern Object Qstructure_object;
#include <assert.h>

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_make_hash_table_n (long,...);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object append2(Object list1, Object list2);
extern Object cons(Object,Object);
extern Object format(long n, Object destination, char *control_string, ...);
extern Object gethash(Object,Object,Object);
extern Object make_vector(Object size, Object initial_element);
extern Object nreverse(Object);
extern Object set_gethash(Object,Object,Object);
extern Object SI_find_structure_print_function(Object str);
extern Object SI_find_structure_header(Object name);
extern void SI_INIT_structure_class(void);

#else

extern void SI_add_external_root();
extern Object (*SI_error_fptr) ();
extern Object SI_make_hash_table_n ();
extern Object STATIC_FUNCTION1();
extern Object append2();
extern Object cons();
extern Object format();
extern Object gethash();
extern Object make_vector();
extern Object nreverse();
extern Object set_gethash();
extern Object SI_find_structure_print_function();
extern Object SI_find_structure_header();
extern void SI_INIT_structure_class();

#endif
#endif



extern Object (*SI_find_structure_print_function_fptr)();
extern Object (*SI_find_structure_header_fptr)();
extern Object (*SI_find_structure_constructor_fptr)();
extern Object SI_find_structure_constructor();

/* Hash table mapping from structure type names to INFO structure. */
static Object Structure_info = UNBOUND;

#define INIT_STRUCTURE_INFO() if (Structure_info == UNBOUND) initialize()

static void initialize() { 
    PROTECT_GLOBAL(Structure_info); 
    Structure_info = SI_make_hash_table_n(2, Ktest, Qeq); 
    SI_INIT_structure_class();
    SI_find_structure_print_function_fptr =
	SI_find_structure_print_function;
    SI_find_structure_header_fptr = 
	SI_find_structure_header;
    SI_find_structure_constructor_fptr =
	SI_find_structure_constructor;
}

/* INFO structures.
 * Implemented as SIMPLE-VECTORs with the following fields:
 * * NAME: The name of the structure type.  A symbol.
 * * SUPER: The INFO structure for the direct supertype of the named type.
 * * DEPTH: The depth at which the named type appears in the class hierarchy.
 *	A fixnum.  The type T has depth 0, STRUCTURE-OBJECT has depth 1, direct
 *	subclasses of STRUCTURE-OBJECT have depth 2, and so on.
 * * HEADER: There are two cases for this.  When supporting CLOS, this is the
 *      class wrapper for the class.  Otherwise, it is the class precedence
 *      name vector for the named type.  This is a SIMPLE-VECTOR with length at
 *      least one greater than the DEPTH of the structure.  The zero element of
 *      the vector contains the type name. Following elements contain the names
 *      of the types in the class precedence list for the type, in most general
 *      to most specific order.  Thus, if a type name appears at element I of
 *      the vector, its DEPTH must be I-1.  The minimum length of this vector
 *      is 1+MINIMUM_CPV_SIZE.  This field is computed lazily.  (This
 *      description is the same as for the cpv field in a class wrapper).
 * * DIRECT_SLOTS: A list of keywords for the local slot names added by the
 *	named structure type, in the order in which they are assigned to
 *	fields.
 * * SLOTS: A list of keywords for all the slot names for structures of the
 *	specified type, in the order in which they are assigned to fields.
 *	This slot is computed lazily.
 * * PRINT_FUNCTION: The function to call to print an object of the specified
 *	type.  Instead of a function, the value may also be one of the keywords
 *	:DEFAULT or :INCLUDE.
 *
 * Some of the information in here is duplicated by the information in the
 * class object when CLOS is supported.
 */

#define INFO_NAME(x)		SI_ISVREF(x,0)
#define INFO_SUPER(x)		SI_ISVREF(x,1)
#define INFO_DEPTH(x)		SI_ISVREF(x,2)
#define INFO_HEADER(x)		SI_ISVREF(x,3)
#define INFO_DIRECT_SLOTS(x)	SI_ISVREF(x,4)
#define INFO_SLOTS(x)		SI_ISVREF(x,5)
#define INFO_PRINT_FUNCTION(x)	SI_ISVREF(x,6)
#define INFO_CONSTRUCTOR(x)	SI_ISVREF(x,7)


#if SI_SUPPORT_CLOS
#define INFO_HEADER_CPV(h)	SI_WRAPPER_CPV(h)
#else
#define INFO_HEADER_CPV(h)	(h)
#endif

/* Maybe this should be allocated in static space? */
#define ALLOC_STRUCTURE_INFO()	make_vector(FIX(8), UNBOUND);

/* Return the INFO structure associated with name.  If none found then signal
 * an error if errorp is true, otherwise returning Nil.
 */
static Object find_structure_info(name, errorp)
  Object	name;
  int		errorp;
{
    Declare_local_temp;
  Declare_protect(1);
  Object	info;

  PROTECT_LOCALS();
  PROTECT_1(name);

  INIT_STRUCTURE_INFO();
  assert(SYMBOLP(name));
  info = gethash(name, Structure_info, NIL);
  if (errorp && (info == NIL))
    error(2, "~S not defined with DEFSTRUCT.", name);
  UNPROTECT_LOCALS();
  return info;
}

static Object Default_structure_print = UNBOUND;
static Object default_structure_print();

#define INIT_DEFAULT_PRINT() \
    if (Default_structure_print == UNBOUND) \
      Default_structure_print = \
	STATIC_FUNCTION(default_structure_print, NIL, FALSE, 3, 3)

static Object find_print_function(info)
  Object	info;
{ Object	res;

  res = INFO_PRINT_FUNCTION(info);
  if (res == Kdefault) {
    INIT_DEFAULT_PRINT();
    return (INFO_PRINT_FUNCTION(info) = Default_structure_print);
  }
  else if (res == Kinclude)
    return (INFO_PRINT_FUNCTION(info) = find_print_function(INFO_SUPER(info)));
  else
    return res;
}

Object SI_find_structure_print_function(str)
  Object	str;
{ Object	temp;

  temp = SI_STRUCTURE_NAME(str);
  temp = find_structure_info(temp, TRUE);
  return find_print_function(temp);
}

Object SI_find_structure_constructor(name)
  Object	name;
{ Object	temp;

  temp = find_structure_info(name, TRUE);
  return INFO_CONSTRUCTOR(temp);
}

static Object find_structure_slots(info)
  Object	info;
{ Declare_protect(1);
  Object	slots, super;

  PROTECT_LOCALS();
  PROTECT_1(info);

  slots = INFO_SLOTS(info);
  if (slots == UNBOUND) {
    slots = INFO_DIRECT_SLOTS(info);
    super = INFO_SUPER(info);
    while (super != NIL) {
      slots = append2(INFO_DIRECT_SLOTS(super), slots);
      super = INFO_SUPER(super);
    }
    INFO_SLOTS(info) = slots;
  }
  UNPROTECT_LOCALS();
  return slots;
}

/* Used by default print and describe to get plist of slot names and values. */
static Object structure_slot_plist(structure, info)
  Object	structure, info;
{
    Declare_local_temp;
  Declare_protect(2);
  Object	plist;
  SI_Dimension	index;

  PROTECT_LOCALS();
  PROTECT_2(structure, info);

  info = find_structure_slots(info);
  plist = NIL;
  for (index = 0; CONSP(info); index++, info = M_CDR(info)) {
    plist = cons(M_CAR(info), plist);
    plist = cons(STRUCTURE_ELEMENT(structure, index), plist);
  }
  UNPROTECT_LOCALS();
  return nreverse(plist);
}

static Object default_structure_print(structure, stream, depth)
  Object structure, stream, depth;
{
    Declare_local_temp;
  Declare_protect(5);
  Object name, info;

  PROTECT_LOCALS();
  PROTECT_3(structure, stream, depth);
  PROTECTI_2(name, info);

  /* It may be necessary to bind some printer control variables here. */
  name = SI_STRUCTURE_NAME(structure);
  info = find_structure_info(name, TRUE);
  info = structure_slot_plist(structure, info);
  (void)format(4, stream, "#S(~S~{ ~S~})", name, info);
  UNPROTECT_LOCALS();
  return VALUES_1(structure);
}

#if SI_SUPPORT_CLOS

static Object Structure_class = UNBOUND;

static Object compute_header(info)
  Object info;
{ Declare_slot_value;
  Declare_protect(3);
  Object name, class, value;

  PROTECT_LOCALS();
  PROTECT_1(info);
  PROTECT_2(name, class);

  INIT_GLOBAL_VAR(Structure_class, find_class(Qstructure_class, T, NIL));

  name = INFO_NAME(info);
  class = find_class(name, T, NIL);
  value = class_of(class);
  if (value != Structure_class) {
    (void)error(2, "~S is not the name of an untyped defstruct.", name);
    /*NOTREACHED*/
  }
  else if (!TRUEP(class_finalized_p(class)))
    (void)finalize_inheritance(class);

  value = SI_CLASS_WRAPPER(class);
  assert(CLASS_WRAPPER_P(value));
  INFO_HEADER(info) = value;
  UNPROTECT_LOCALS();
  return value;
}

static void add_structure_class(name, super, doc)
  Object name, super;
{ Declare_protect(1);
  Object supers;
  
  PROTECT_LOCALS();
  PROTECT_1(name);

  supers = cons(super, NIL);
  UNPROTECT_LOCALS();
  (void)add_named_class(5, name,
			Kmetaclass, Qstructure_class,
			Kdirect_superclasses, supers,
			Kdocumentation, doc);
}

#else

static SI_Dimension fill_cpv(cpv, info)
  Object	cpv, info;
{ Object	temp;
  SI_Dimension	index;

  temp = INFO_SUPER(info);
  if (temp == NIL) index = 1;
  else index = fill_cpv(cpv, temp);
  SI_ISVREF(cpv, index) = INFO_NAME(info);
  return index+1;
}

static Object compute_header(info)
  Object	info;
{ Declare_protect(1);
  Object	res;

  PROTECT_LOCALS();
  PROTECT_1(info);

  res = INFO_DEPTH(info);
  res = FIXNUM_ADD1(res);
  if (FIXNUM_LT(res, FIX(SI_MINIMUM_CPV_SIZE+1)))
    res = FIX(SI_MINIMUM_CPV_SIZE+1);
  /* Maybe this should be allocated in static space? */
  res = make_vector(res, NIL);
  SI_ISVREF(res, 0) = INFO_NAME(info);
  (void)fill_cpv(res, info);
  INFO_HEADER(info) = res;
  UNPROTECT_LOCALS();
  return res;
}

#endif /* SI_SUPPORT_CLOS */

Object SI_find_structure_header(name)
  Object	name;
{ Declare_protect(2);
  Object	info, res;

  PROTECT_LOCALS();
  PROTECT_1(name);
  PROTECTI_1(info);

  info = find_structure_info(name, TRUE);
  res = INFO_HEADER(info);
  UNPROTECT_LOCALS();
  if (res != UNBOUND) return res;
  return compute_header(info);
}

Object make_structure_class(name, super, slots, printer, constructor, doc)
  Object	name, super, slots, printer, constructor, doc;
{
    Declare_local_temp;
  Declare_protect(5);
  Object	info;

  PROTECT_LOCALS();
  PROTECT_5(name, super, slots, printer, doc);

  /* Default super is STRUCTURE-OBJECT. */
  if (super == NIL)   super = Qstructure_object;
  info = find_structure_info(super, FALSE);
  if (info == NIL)
    error(3, "The supertype ~S of ~S not defined using DEFSTRUCT.", super, name);
  else super = info;
  info = find_structure_info(name, FALSE);
  /* For now, make redefinition be an error. */
  if (info != NIL)
    error(2, "Attempt to redefine structure type ~S.", name);
  info = ALLOC_STRUCTURE_INFO();
  INFO_NAME(info) = name;
  INFO_SUPER(info) = super;
  INFO_DEPTH(info) = FIXNUM_ADD1(INFO_DEPTH(super));
  INFO_DIRECT_SLOTS(info) = slots;
  INFO_PRINT_FUNCTION(info) = printer;
  INFO_CONSTRUCTOR(info) = constructor;
  (void)set_gethash(name, Structure_info, info);
#if SI_SUPPORT_CLOS
  add_structure_class(name, INFO_NAME(super), doc);
#endif

  UNPROTECT_LOCALS();
  return VALUES_1(name);
}


void  SI_standard_structure_constructor_error(name)
    Object name;
{
    error(2," ~a is not a structure type with a keyword constructor",name);
}


void SI_INIT_structure_class()
{ Declare_protect(1);
  Object	tinfo, sinfo;

  PROTECT_LOCALS();
  PROTECTI_1(tinfo);

  INIT_STRUCTURE_INFO();

  tinfo = ALLOC_STRUCTURE_INFO();
  INFO_NAME(tinfo) = Qt;
  INFO_SUPER(tinfo) = NIL;
  INFO_DEPTH(tinfo) = FIX(0);
  INFO_DIRECT_SLOTS(tinfo) = NIL;
  INFO_PRINT_FUNCTION(tinfo) = NIL;
  INFO_CONSTRUCTOR(tinfo) =  NIL;

  sinfo = ALLOC_STRUCTURE_INFO();
  INFO_NAME(sinfo) = Qstructure_object;
  INFO_SUPER(sinfo) = tinfo;
  INFO_DEPTH(sinfo) = FIX(1);
  INFO_DIRECT_SLOTS(sinfo) = NIL;
  INFO_PRINT_FUNCTION(sinfo) = Kdefault;
  INFO_CONSTRUCTOR(sinfo) = NIL;
 
  (void)set_gethash(Qstructure_object, Structure_info, sinfo);
  UNPROTECT_LOCALS();
}

/* If symbol is defined as a structure type, returns a value which can be
 * used as an info argument for SI_structure_typep or SI_structure_subtypep.
 * Otherwise, returns NIL.
 */
Object SI_structure_type_specifier_p(symbol)
  Object	symbol;
{ return find_structure_info(symbol, FALSE); }

/* info is the result of a call to SI_structure_type_specifier_p(). */
long SI_structure_typep(thing, info)
  Object	thing, info;
{ return
     (STRUCTURE_OBJECT_P(thing) &&
      STRUCTURE_OBJECT_COMPLEX_TYPEP(thing, IFIX(INFO_DEPTH(info)),
				     INFO_NAME(info)));
}

/* info1 & info2 are results of calls to SI_structure_type_specifier_p(). */
long SI_structure_subtypep(info1, info2)
  Object	info1, info2;
{ Declare_protect(2);
  Object	d1, d2, temp;
  long		res;

  PROTECT_LOCALS();
  PROTECT_2(info1, info2);

  d1 = INFO_DEPTH(info1);
  d2 = INFO_DEPTH(info2);
  /* If 2 is deeper than 1, then 1 can't be subtype of 2. */
  if (FIXNUM_LT(d1, d2)) res = FALSE;
  else {
    temp = INFO_HEADER(d1);
    if (temp == UNBOUND) temp = compute_header(info1);
    temp = INFO_HEADER_CPV(temp);
    res = (INFO_NAME(info2) == SVREF(temp, FIXNUM_ADD1(d2)));
  }
  UNPROTECT_LOCALS();
  return res;
}


