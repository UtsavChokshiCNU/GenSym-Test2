/*
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 */

/******************************************************************************
 *
 * Shared support for instance types
 *
 ******************************************************************************
 *
 * Some kinds of stored objects are represented as "subtypes" of "Instance".
 * They share a common pointer tag and all have a type code (in the Header)
 * in a range reserved to them.  Such objects have a specialized header which
 * includes both the normal Header field and an additional field which contains
 * the class-wrapper metaobject for the class of the object.
 *
 * Implementation note:  This is the only place in this file that needs to know
 * about STORED_OBJECT and has any knowledge of about the tagging scheme beyond
 * the existance of type codes for various objects.
 *
 *****************************************************************************/

typedef struct {
    SI_Header h;
#if SI_SUPPORT_CLOS			/* No class wrappers without CLOS. */
    Object wrapper;
#endif
} SI_Instance;

#if (SI_TAG_WIDTH <= 2)

/* The basic idea here is to use properties of unsigned arithmetic to avoid
 * doing multiple type code extractions.  The (unsigned) casts on the arguments
 * to the subtractions are only present because lint complains about arithmetic
 * operations on enums. */

#if ((SI_INSTANCE_TAG == 0) && SI_NIL_IS_ZERO)
#define SI_RANGED_INSTANCEP_HELPER(o, low, high, type_extract) \
    (((o) != NIL) && (SI_TAG_OF(o) == SI_INSTANCE_TAG) && \
     ((unsigned)((unsigned)type_extract(o)-(unsigned)(low)) \
      <= (unsigned)((unsigned)(high)-(unsigned)(low))))
#else
#define SI_RANGED_INSTANCEP_HELPER(o, low, high, type_extract) \
    ((SI_TAG_OF(o) == SI_INSTANCE_TAG) && \
     ((unsigned)((unsigned)type_extract(o)-(unsigned)(low)) \
      <= (unsigned)((unsigned)(high)-(unsigned)(low))))
#endif

/* If tag width is 1 and conses are headerless, use SI_STORED_OBJECT_TYPE() to
 * get the type code, since it is careful to deal with conses correctly.
 * Otherwise just directly access the type field of the header, because the tag
 * comparison in the helper is sufficient to determine that this is safe. */

#if ((SI_TAG_WIDTH == 1) && !SI_CONSES_HAVE_HEADERS)
#define SI_RANGED_INSTANCEP(o, low, high) \
    SI_RANGED_INSTANCEP_HELPER(o, low, high, SI_STORED_OBJECT_TYPE)
#else     
#define SI_RANGED_INSTANCEP(o, low, high) \
    SI_RANGED_INSTANCEP_HELPER(o, low, high,SI_STORED_OBJECT_HEADER_TYPE_FIELD)
#endif

#define SI_INSTANCEP(o) \
    SI_RANGED_INSTANCEP(o, SI_LEAST_INSTANCE_TYPE, SI_GREATEST_INSTANCE_TYPE)

#define SI_TAG_INSTANCE(u)	     SI_TAG_STORED(u, SI_INSTANCE_TAG)
#define SI_TAG_INSTANCE_CONSTANT(u)  SI_TAG_STORED_CONSTANT(u, SI_INSTANCE_TAG)
#define SI_UNTAG_INSTANCE(o,t)	     SI_UNTAG_STORED(o,t)
#define SI_UNTAG_INSTANCE_TYPE       SI_UNTAG_INSTANCE /* used? */
#define SI_INSTANCE_PRED(o,t)	     SI_STORED_OBJECT_TYPEP(o,t)

#else
#if (SI_TAG_WIDTH == 3)

/* This can't be done because the 3bit tagging isn't fully implemented. */
#  include "No definition for SI_INSTANCEP with 3bit tags."

#else

#  include "No definition for SI_INSTANCEP with current tagging scheme."

#endif /* SI_TAG_WIDTH == 3 */
#endif /* SI_TAG_WIDTH <= 2 */

#define SI_INSTANCE_FIELD(o,t,f) SI_STORED_OBJECT_FIELD(o,t,f)

/* See class-wrappers for a description of SI_Initial_built_in_header. */
#if SI_SUPPORT_CLOS

#define INSTANCE_WRAPPER(o)	SI_INSTANCE_FIELD(o, SI_Instance, wrapper)
#ifdef SI_RUNTIME_INTERNAL
#define SI_SET_WRAPPER(o,w)	(INSTANCE_WRAPPER(o) = (w))
#endif

#if SI_OBJECT_INITIALIZERS_WORK
#define SI_INSTANCE_HEADER(type, stuff, wrapper) \
    {SI_HEADER(type, stuff), SI_TAG_CLASS_WRAPPER(&wrapper)}
#endif

#else

#ifdef SI_RUNTIME_INTERNAL
#define SI_SET_WRAPPER(o,w)
#endif

#if SI_OBJECT_INITIALIZERS_WORK
#define SI_INSTANCE_HEADER(type, stuff, wrapper) \
    SI_HEADER(type, stuff)
#endif

#endif

/******************************************************************************
 *
 * Class wrappers
 *
 ******************************************************************************
 *
 * Each instantiated class has associated with it a class wrapper.
 *
 * Each instance of a class whose base representation is Instance contains a
 * pointer to the associated class wrapper, which in turn contains a pointer to
 * the class object and various pieces of information used in type testing,
 * generic-function discrimination, and slot access validation.
 *
 * Each instance points to the wrapper in order to provide fast access through
 * the instance to the per-class information contained in the wrapper.
 *
 * This also makes it possible to quickly make all instances obsolete (see
 * MAKE-INSTANCES-OBSOLETE), by setting all the cache numbers to zero (see
 * cache lookup description) and filling the slot name tables with zero
 * (causing name verification to always fail).  This is only relevent to
 * instances which are standard-object-p, since other classes cannot be
 * redefined.  It is also only relevent if MAKE-INSTANCES-OBSOLETE is actually
 * supported.
 *
 *   class		The associated class, a Lisp object.  
 *   cache_number	A table of cache numbers, represented as SI_Long.
 *			These are used for generic function lookup.  The lookup
 *			mechanism requires that they be unboxed even fixnums.
 *   cpl_cache		The class precedence vector.  This is used to do type
 *			tests on the object.  It is equivalent to the result of
 *			coercing the class precedence list of the class to a
 *			simple-vector.
 *   cpv		The class precedence name vector.  This is used to do
 *			type tests on the object.  It is a simple-vector of
 *			type names which includes the names of each class in
 *			the class precedence list of the class, ordered from
 *			most general to most specific.  The entries are
 *			actually shifted one position to allow the type name
 *			for the class to be recorded in entry 0.
 *   read_table_base	These next four entries are the slot-name tables used
 *   write_table_base	to verify read and write accesses.  See below.
 *   read_table
 *   write_table
 *
 * [Note: The cpl_cache and cpv fields are sort of misnamed.  Probably better
 * would have been to name the cpl_cache field "cpv" and name the cpv field
 * "cpvn", or some similar change.  However, the need for two seperate fields
 * was not initially recognized, and rather than doing lots of name changes,
 * the cpl_cache field was simply added.]
 *
 * Slot-name tables are used in the verification of named slot access functions
 * (slot-value and friends).  The entries for a slot-name table are in pairs.
 * The `_base' entry contains a Lisp simple general vector.  The other entry
 * contains a pointer into the middle of the vector.  The read table is used
 * to validate slot reads (slot-value and slot-boundp), while the write table
 * is used to validate slot writes (set-slot-value and slot-makunbound).  To
 * validate a slot access, compare the slot-name with the value found by
 * reading the location determined by adding the slot-name's global index to
 * the pointer into the middle of the appropriate vector.  See the macros
 * VALIDATE_SLOT_READ and VALIDATE_SLOT_WRITE. 
 *
 * [Note that there may eventually be additional slots in this structure which
 * will be used by `spill code' for slot access functions, for use when the
 * fast mechanism fails.] 
 *
 *****************************************************************************/

#if SI_SUPPORT_CLOS		/* No class wrappers without CLOS */

/* The number of class cache numbers associated with each class.
 * Different generic functions use different cache entries in order to reduce
 * the chance of global performance problems due to collisions.
 *
 * Note that the value should be chosen to make the size of a class wrapper
 * work out to a value which makes alignment simple.
 */
#define SI_CACHE_NUMBER_ENTRY_MAX	7

/* The order of fields here is important to the garbage collector.
 * The read/write_table and read/write_table_base fields are handled specially.
 * The table of cache seeds is skipped, since it contains no pointers.
 */
typedef struct {
    SI_Instance	h;
    Object	*read_table;
    Object	*write_table;
    Object	read_table_base;
    Object	write_table_base;
    SI_Long	cache_number[SI_CACHE_NUMBER_ENTRY_MAX];
    Object	class;
    Object	cpv;
    Object	cpl_cache;
} SI_Class_wrapper;

#define CLASS_WRAPPER_P(o)	    SI_INSTANCE_PRED(o, SI_CLASS_WRAPPER_TYPE)
#define SI_TAG_CLASS_WRAPPER(u)	    SI_TAG_INSTANCE(u)

#define SI_WRAPPER_CPV(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,cpv)

#define SI_WRAPPER_READ_TABLE(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,read_table)

#define SI_WRAPPER_WRITE_TABLE(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,write_table)

#define SI_WRAPPER_TABLE_ACCESS(table, index) \
    ((table)[IFIX(index)])

#define SI_VALIDATE_SLOT_ACCESS(slot_name, table, index) \
    EQ(slot_name, SI_WRAPPER_TABLE_ACCESS(table, index))

#define SI_VALIDATE_SLOT_READ(slot_name, wrapper, index) \
    SI_VALIDATE_SLOT_ACCESS(slot_name, SI_WRAPPER_READ_TABLE(wrapper), index)

#define SI_VALIDATE_SLOT_WRITE(slot_name, wrapper, index) \
    SI_VALIDATE_SLOT_ACCESS(slot_name, SI_WRAPPER_WRITE_TABLE(wrapper), index)

#ifdef SI_RUNTIME_INTERNAL

#define SI_WRAPPER_CLASS(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,class)

#define SI_WRAPPER_CPL_CACHE(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,cpl_cache)

#define SI_WRAPPER_CACHE_NUMBER(o,i) \
    (SI_INSTANCE_FIELD(o,SI_Class_wrapper,cache_number)[i])

#define SI_WRAPPER_OBSOLETE_P(o) \
    (SI_WRAPPER_CACHE_NUMBER(o,0) == 0)

#define SI_WRAPPER_READ_TABLE_BASE(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,read_table_base)

#define SI_WRAPPER_WRITE_TABLE_BASE(o) \
    SI_INSTANCE_FIELD(o,SI_Class_wrapper,write_table_base)

#define SI_WRAPPER_SET_VALIDATION(table, index, value) \
    ((table)[IFIX(index)] = value)

#define SI_WRAPPER_SET_READ_VALIDATION(wrapper, index, value) \
    SI_WRAPPER_SET_VALIDATION(SI_WRAPPER_READ_TABLE(wrapper), index, value)

#define SI_WRAPPER_SET_WRITE_VALIDATION(wrapper, index, value) \
    SI_WRAPPER_SET_VALIDATION(SI_WRAPPER_WRITE_TABLE(wrapper), index, value)

#endif /* ifdef SI_RUNTIME_INTERNAL */

#endif				/* No wrappers without CLOS. */

/* The class precedence vector will always have at least SI_MINIMUM_CPV_SIZE 
 * entries allocated, with unused entries containing zeros.  This allows 
 * the type check for structure objects to eliminate the range test when 
 * the depth of the desired class in the tree is sufficiently small.
 *
 * [The translator must also know the value of this constant.]
 */

#define SI_MINIMUM_CPV_SIZE	10

/******************************************************************************
 *
 * Structures (defstructs)
 *
 ******************************************************************************
 *
 * This is the object representation used by the metaclass STRUCTURE-CLASS.
 *
 * Structures are represented as subtypes of "Instance".  They consist of the
 * basic header immediately followed by a (C) vector of the slots.
 *
 *****************************************************************************/

typedef struct {
    SI_Instance h;
#if !SI_SUPPORT_CLOS
    Object cpv;
#endif
} SI_Structure;

/* All objects <x> for which (typep <x> 'structure-object) is true have a
 * representation as Structure.  Perhaps the name SI_Structure should be
 * phased out in favor of Structure_object?
 */

typedef SI_Structure Structure_object;

#define STRUCTURE_OBJECT_P(o)	SI_INSTANCE_PRED(o, SI_STRUCTURE_TYPE)
#define SI_TAG_STRUCTURE(u)	SI_TAG_INSTANCE(u)

#if SI_SUPPORT_CLOS
#define SI_STRUCTURE_OBJECT_CPV(o) \
    SI_WRAPPER_CPV(INSTANCE_WRAPPER(o))
#else
#define SI_STRUCTURE_OBJECT_CPV(o) \
    SI_INSTANCE_FIELD(o,SI_Structure,cpv)
#endif

#ifdef SI_RUNTIME_INTERNAL
#if SI_SUPPORT_CLOS
#define SI_STRUCTURE_HEADER(o)	INSTANCE_WRAPPER(o)
#else
#define SI_STRUCTURE_HEADER(o)	SI_STRUCTURE_OBJECT_CPV(o)
#endif /* else SI_SUPPORT_CLOS */
#endif /* def SI_RUNTIME_INTERNAL */

#define SI_STRUCTURE_NAME(o)    SI_ISVREF(SI_STRUCTURE_OBJECT_CPV(o),0)

/* Primitive accessors on structures.
 * STRUCTURE_FIELD provides named access to fields using the type.
 * STRUCTURE_ELEMENT provides indexed access to fields.
 */

#define STRUCTURE_FIELD(o,t,f)	SI_INSTANCE_FIELD(o,t,f)

#if (SI_SUPPORT_MF || defined(SI_RUNTIME_INTERNAL))

#define SI_Type_for_structure(n) \
    struct {SI_Structure s; Object slots[n ? n : 1];}

#define SI_STRUCTURE_SLOTS(o) \
    SI_INSTANCE_FIELD(o, SI_Type_for_structure(1), slots)

#define STRUCTURE_ELEMENT(o, i)		SI_STRUCTURE_SLOTS(o)[i]

#endif /* (SI_SUPPORT_MF || defined(SI_RUNTIME_INTERNAL)) */

/* Predicates for subtypes of structure-object work by doing a lookup on the
 * type name in the class precedence vector of the class wrapper in the object.
 * The offset of the name in this vector is a constant that can be determined
 * at compile time.
 *
 * The size of the class precedence vector varies but is guaranteed to be at
 * least MINIMUM_CPV_SIZE.  This means that for the common cases where the type
 * hierarchy is fairly shallow, we don't have to test the size of the class
 * precedence vector before doing the lookup either.
 *
 * These macros assume that the object has already been verified to be a
 * structure-object.
 */

#define STRUCTURE_OBJECT_TYPEP(o,i,t) \
    (SI_ISVREF(SI_STRUCTURE_OBJECT_CPV(o),i+1) == t)

#define STRUCTURE_OBJECT_COMPLEX_TYPEP(o,i,t) \
    ((SI_PRIMITIVE_VECTOR_LENGTH(SI_STRUCTURE_OBJECT_CPV(o)) > i+1L) && \
     STRUCTURE_OBJECT_TYPEP(o,i,t))

#if (SI_SUPPORT_SF || defined(SI_RUNTIME_INTERNAL))
#define MAKE_STRUCTURE(name, c_type) \
    SI_make_structure(name, (SI_Size_type)sizeof(c_type), \
		      SI_ALIGNMENT_FOR(c_type))
#endif

#define NAMED_LIST_P(o, i, t)  \
    (CONSP(o) && nth(FIX(i),o) == t)

#define NAMED_SIMPLE_VECTOR_P(o, i, t) \
    (SIMPLE_VECTOR_P(o) && i < ilength(o) && SI_ISVREF(o,i) == t)

/******************************************************************************
 *
 * Effective methods
 *
 ******************************************************************************
 *
 * A Effective_method is a data structure used to represent effective methods.
 *
 * Slots with the suffix `_table' form a parallel set of vectors, indexed by
 * the method index for a method.
 *
 *  generic_function	The generic-function this effective method is for.
 *  methods		The list of applicable methods, as returned by
 *			compute-applicable-methods. 
 *  method_table	A simple-vector of the actual method objects.
 *  next_method_table	A simple_bit_vector, with 1's indicating that a
 *			next-method is available for the method, 0's meaning
 *			there isn't one. 
 *  key_table		A simple-vector of keyword permutation vectors for the
 *			corresponding methods, or Nil if none of the applicable
 *			methods that make up this effective method specify any
 *			keyword parameters.
 *  keys		A simple-vector of keywords, specifying the canonical
 *			location of all the keywords explicitly accepted by the
 *			applicable methods making up the effective method.  The
 *			position of a keyword in this table specifies the
 *			position where the value (if supplied) will appear in
 *			the method argument frame.  If no keywords are
 *			explicitly accepted, the value of this slot is Nil.
 *  start		The index for the initial method to call when the
 *			effective method is called from the generic-function.
 *  argument-info	Encoded argument information.  This is a fixnum, with
 *			the following information encoded in it: the number of
 *			required arguments, the number of positional arguments,
 *			accepts non-positional arguments, keyword arguments,
 *			allow other keys.
 *
 * All of these slots are read-only as far as Lisp is concerned.
 *
 *****************************************************************************/

#if SI_SUPPORT_CLOS			/* No effective-methods without CLOS */

typedef struct {
    SI_Instance    h;
    Object	generic_function;	/* generic-function		*/
    Object	methods;		/* list				*/
    Object	method_table;		/* simple-vector		*/
    Object	next_method_table;	/* simple-bit-vector		*/
    Object	key_table;		/* (or null simple-vector)	*/
    Object	keys;			/* (or null simple-vector)	*/
    Object	start;			/* fixnum			*/
    Object	argument_info;		/* lambda-list encoding		*/
} SI_Effective_method;

#define EFFECTIVE_METHOD_P(o)	   SI_INSTANCE_PRED(o,SI_EFFECTIVE_METHOD_TYPE)
#define SI_TAG_EFFECTIVE_METHOD(u) SI_TAG_INSTANCE(u)

/* Initialize all fields to a gc-safe value. */
#define SI_INIT_EFFECTIVE_METHOD_FIELDS(cm) \
    SI_EFFECTIVE_METHOD_GENERIC_FUNCTION(cm) = \
     SI_EFFECTIVE_METHOD_APPLICABLE_METHODS(cm) = \
      SI_EFFECTIVE_METHOD_METHOD_TABLE(cm) = \
       SI_EFFECTIVE_METHOD_NEXT_METHOD_TABLE(cm) = \
        SI_EFFECTIVE_METHOD_KEY_TABLE(cm) = \
         SI_EFFECTIVE_METHOD_KEYS(cm) = \
          SI_EFFECTIVE_METHOD_START(cm) = \
           SI_EFFECTIVE_METHOD_ARGUMENT_INFO(cm) = NIL

/* Slot accessors for Effective_methods. */

#define SI_EFFECTIVE_METHOD_GENERIC_FUNCTION(cm)		\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,generic_function)

#define SI_EFFECTIVE_METHOD_APPLICABLE_METHODS(cm)	\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,methods)

#define SI_EFFECTIVE_METHOD_METHOD_TABLE(cm)		\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,method_table)

#define SI_EFFECTIVE_METHOD_NEXT_METHOD_TABLE(cm)	\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,next_method_table)

#define SI_EFFECTIVE_METHOD_KEY_TABLE(cm)		\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,key_table)

#define SI_EFFECTIVE_METHOD_KEYS(cm)			\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,keys)

#define SI_EFFECTIVE_METHOD_START(cm)			\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,start)

#define SI_EFFECTIVE_METHOD_ARGUMENT_INFO(cm)		\
    SI_INSTANCE_FIELD(cm,SI_Effective_method,argument_info)

#endif /* SI_SUPPORT_CLOS */

/******************************************************************************
 *
 * Method combination instances
 *
 ******************************************************************************
 *
 * This is the object representation used for method combination metaobjects.
 *
 * The name is a symbol, and is the "type" of method combination specified by
 * this metaobject.  The function slot holds the combining function called by
 * compute-effective-method.  The options slot is a list of options from the
 * generic function defining form that created this metaobject.
 *
 * Implementation note: Since the function is completely determined by the
 * name, the function slot could be elided, instead looking up the function via
 * the accessors on method combination type information.  Seems better to have
 * it immediately available for quick access though.
 *
 *****************************************************************************/

#if SI_SUPPORT_CLOS		/* No method-combination without CLOS */

typedef struct {
    SI_Instance h;
    Object name;
    Object function;
    Object options;
} SI_Method_combination;

#define METHOD_COMBINATION_P(o) \
    SI_INSTANCE_PRED(o, SI_METHOD_COMBINATION_TYPE)
#define SI_TAG_METHOD_COMBINATION(u)	SI_TAG_INSTANCE(u)

#define METHOD_COMBINATION_NAME(o) \
    SI_INSTANCE_FIELD(o,SI_Method_combination,name)

#define METHOD_COMBINATION_FUNCTION(o) \
    SI_INSTANCE_FIELD(o,SI_Method_combination,function)

#define METHOD_COMBINATION_OPTIONS(o) \
    SI_INSTANCE_FIELD(o,SI_Method_combination,options)

#endif /* SI_SUPPORT_CLOS */

/******************************************************************************
 *
 * Standard instances
 *
 ******************************************************************************
 *
 * This is the object representation used by the metaclass STANDARD-CLASS.
 *
 * Standard-instances are represented as subtypes of "Instance".  They consist
 * of the basic header followed by a pointer to the slot-vector and a pointer
 * into the middle of the slot-vector.  Having a pointer into the middle of the
 * slot-vector provides support for the two-directional slot layout mechanism,
 * in which some slots are given negative offsets.  The garbage collector knows
 * enough to preserve the offset between the two pointers.
 *
 *****************************************************************************/

#if !SI_SUPPORT_CLOS
CONFIG_REQUIRES(SI_config_not_support_clos, local_support_closp)

/* If not supporting CLOS, make Standard_instance just be a synonym for
 * Instance, so that other structs can include Standard_instance without
 * further conditionalization.
 *
 * Also, define standard-object-p always be false.
 */

typedef SI_Instance SI_Standard_instance;
#define STANDARD_OBJECT_P(o)	FALSE

#define SI_SET_STANDARD_OBJECT_SLOT_VECTOR(o,v,i) /* No-op */

#else /* if SI_SUPPORT_CLOS */
CONFIG_REQUIRES(SI_config_support_clos, local_support_closp)

typedef struct {
    SI_Instance h;
    Object *slots;
    Object slot_vector;
} SI_Standard_instance;

#define SI_STANDARD_INSTANCE_P(o) \
    SI_INSTANCE_PRED(o, SI_STANDARD_INSTANCE_TYPE)
#define SI_TAG_STANDARD_INSTANCE(u)	SI_TAG_INSTANCE(u)

/* All objects <x> for which (typep <x> 'standard-object) is true have a
 * representation as either SI_Standard_instance, SI_Function, or SI_Method.
 * The following accessors work on objects based on any of these representation
 * types.  The predicate assumes that the corresponding type codes are defined
 * contiguously. 
 */

#define SI_STANDARD_OBJECT_SLOTS(o) \
    SI_INSTANCE_FIELD(o, SI_Standard_instance, slots)

#ifdef SI_RUNTIME_INTERNAL

#define SI_STANDARD_OBJECT_SLOT_VECTOR(o) \
    SI_INSTANCE_FIELD(o, SI_Standard_instance, slot_vector)

#define SI_STANDARD_OBJECT_SLOT_DISPLACEMENT(o) \
    (SI_STANDARD_OBJECT_SLOTS(o) \
      - &SI_ISVREF(SI_STANDARD_OBJECT_SLOT_VECTOR(o), 0))

#define SI_SET_STANDARD_OBJECT_SLOT_VECTOR(o,v,i) \
    do { \
      SI_STANDARD_OBJECT_SLOT_VECTOR(o) = v; \
      SI_STANDARD_OBJECT_SLOTS(o) = &SI_ISVREF(v, i); \
    } while (0)

#endif

#define STANDARD_OBJECT_REF(o,i) \
    (SI_STANDARD_OBJECT_SLOTS(o)[IFIX(i)])

#define STANDARD_OBJECT_P(o)				\
    SI_RANGED_INSTANCEP(o,				\
			SI_LEAST_STANDARD_OBJECT_TYPE,	\
			SI_GREATEST_STANDARD_OBJECT_TYPE)

#endif /* SI_SUPPORT_CLOS */

/******************************************************************************
 *
 * Functions
 *
 ******************************************************************************
 *
 * This is the object representation used by the metaclass
 * FUNCALLABLE-STANDARD-CLASS. 
 *
 * Functions are represented as subtypes of standard-instances.  In addition to
 * the fields provided by standard-instances, two additional fields exist in a
 * function.  The entry field contains a pointer to the C function for
 * executing the function.  The env field contains a closure binding object for
 * use by the function.  Other pieces of information about the function (like
 * its name, lambda-list, etc.) might be stored in the instance slots.
 *
 *****************************************************************************/

typedef struct {
    SI_Standard_instance h;
    Object (*entry)();
    Object env;
} SI_Function;

typedef struct {
    SI_Declare_static_relocation_field /* no semicolon */
    SI_Standard_instance h;
    Object (*entry)();
    Object env;
} SI_Function_constant;

#define SI_FUNCTIONP(o)		SI_INSTANCE_PRED(o, SI_FUNCTION_TYPE)
#define SI_TAG_FUNCTION(u)	SI_TAG_INSTANCE(u)

#define SI_FUNCTION_ENTRY(o)	SI_INSTANCE_FIELD(o,SI_Function,entry)
#define SI_FUNCTION_ENV(o)	SI_INSTANCE_FIELD(o,SI_Function,env)
#define SI_FUNCTION_STUFF(o)	SI_INSTANCE_FIELD(o,SI_Header,stuff)

/* The stuff field holds flags and the sum of the numbers of
   required and optional arguments. */
#define SI_FUNCTION_FLAGS_WIDTH 3

#define SI_FUNCTION_NARGS(o) \
    (SI_FUNCTION_STUFF(o) >> SI_FUNCTION_FLAGS_WIDTH)

/*** If SI_SUPPORT_CLOS, we should initialize the CLOS fields as well ***/
#define SI_INIT_FUNCTION(o,flags,nreq,npos) \
    (SI_FUNCTION_STUFF(o) = \
      ((npos) << SI_FUNCTION_FLAGS_WIDTH) | (flags))

#define COMPILED_FUNCTION_P(o)  SI_FUNCTIONP(o)

#if SI_SUPPORT_MF
#define FUNCTIONP(o)		functionp(o)
#else
#define FUNCTIONP(o)            SI_FUNCTIONP(o)
#endif

/* Function bit flags */

#define SI_VARIADIC_FLAG	1  /* Uses varargs protocol */
#define SI_OPTIONAL_FLAG	2  /* Pass _ for unsupplied optionals */
#if SI_SUPPORT_CLOS
#define SI_GENERIC_FLAG		4  /* generic function -- use sep. protocol */
#endif

/* The following four must be mutually exclusive */
#define SI_FUNCTION_VARIADIC_P(o) \
    (SI_FUNCTION_STUFF(o) & SI_VARIADIC_FLAG)
#define SI_FUNCTION_OPTIONAL_P(o) \
    (SI_FUNCTION_STUFF(o) & SI_OPTIONAL_FLAG)
#define SI_FUNCTION_SIMPLE_P(o) \
    (!(SI_FUNCTION_STUFF(o) & ((1L << SI_FUNCTION_FLAGS_WIDTH) - 1)))
#if SI_SUPPORT_CLOS
#define SI_FUNCTION_GENERIC_P(o) \
    (SI_FUNCTION_STUFF(o) & SI_GENERIC_FLAG)
#endif

/* ... Other properties of functions belong here: interpreted,
   generic, etc. ... */

/* Medfly-only bits */
#define OPT_FLAG		SI_OPTIONAL_FLAG
#define FUNC_OPT_P(o)		(SI_FUNCTION_STUFF(o) & OPT_FLAG)
#define REST_FLAG     		4  /* Takes rest parameter as list */
#define FUNC_REST_P(o)		(SI_FUNCTION_STUFF(o) & REST_FLAG)

#if defined(hp9000s800) && !defined(__hp9000s700)

#define STATIC_FUNCTION(entry,env,variadicp,nreq,npos) \
  STATIC_FUNCTION1(entry,env,variadicp,nreq,npos)

#else


#define STATIC_FUNCTION(entry,env,variadicp,nreq,npos) \
  STATIC_FUNCTION1((Object(*)())(entry),env,variadicp,nreq,npos)

#endif

/* C initializer for compiled functions */

#if SI_OBJECT_INITIALIZERS_WORK
#if SI_SUPPORT_CLOS

struct SI_Function_slot_vector_struct {
    SI_Type_for_primitive_vector_constant(Object, 0) h;
};

#define CONSTANT_COMPILED_FUNCTION(id, req, opt, flags, fun) \
    static SI_Function_constant id = \
	{SI_STATIC_RELOCATION_INFO \
	 {SI_INSTANCE_HEADER(SI_FUNCTION_TYPE, \
			     (((req)+(opt)) << SI_FUNCTION_FLAGS_WIDTH) | \
			     (flags) | ((opt) ? SI_OPTIONAL_FLAG : 0), \
			     SI_Function_wrapper), \
	  &((SI_Function_slot_vector.h.contents)[0]), \
	  TAG_VECTOR(SI_Function_slot_vector)}, \
	 fun,  /* entry */ \
	 NIL   /* env */ }

#else /* if !SI_SUPPORT_CLOS */

#define CONSTANT_COMPILED_FUNCTION(id, req, opt, flags, fun) \
    static SI_Function_constant id = \
        {SI_STATIC_RELOCATION_INFO \
	 SI_INSTANCE_HEADER(SI_FUNCTION_TYPE, \
			    (((req)+(opt)) << SI_FUNCTION_FLAGS_WIDTH) | \
			    (flags) | ((opt) ? SI_OPTIONAL_FLAG : 0), \
			    SI_Function_wrapper), \
	 fun,  /* entry */ \
	 NIL   /* env */ }

#endif

#define TAG_COMPILED_FUNCTION(id) SI_TAG_INSTANCE_CONSTANT(&id)
#endif

/* Obsolescent */
#define IFUNC			SI_FUNCTION_ENTRY
#define VARIADIC_FLAG		SI_VARIADIC_FLAG

/******************************************************************************
 *
 * Methods
 *
 ******************************************************************************
 *
 * This is the object representation used by the metaclass METHOD-CLASS. 
 *
 * Methods are represented as subtypes of Function.  The only difference is the
 * type code.  Note however that Methods are not functionp.
 *
 *****************************************************************************/

#if SI_SUPPORT_CLOS			/* No methods without CLOS */

typedef struct {
    SI_Function h;
} SI_Method;

#define SI_METHODP(o)		SI_INSTANCE_PRED(o, SI_METHOD_TYPE)
#define SI_TAG_METHOD(u)	SI_TAG_INSTANCE(u)

#define SI_METHOD_ENTRY(o)	SI_FUNCTION_ENTRY(o)
#define SI_METHOD_ENV(o)	SI_FUNCTION_ENV(o)

#endif

/******************************************************************************
 *
 * Pathnames
 *
 *****************************************************************************/

#if (defined(SI_RUNTIME_INTERNAL) || SI_SUPPORT_MF)
typedef struct {
    SI_Instance h;
    Object path;		/* full pathname string */
    Object host;		/* Host + system-dependent stuff linked list */
} SI_Pathname;

#define PATHNAME_HOST(o)	SI_INSTANCE_FIELD(o, SI_Pathname, host)
#endif

#define PATHNAMEP(o)		SI_INSTANCE_PRED(o, PATHNAME_TYPE)

/******************************************************************************
 *
 * Packages
 *
 *****************************************************************************/

typedef struct {
    SI_Instance h;
    short *hashtab;		/* pointer to hash array */
    SI_Initial_symbol *symtab;	/* pointer to array of symbols */
    short symbol_count;		/* size of initial symbol table */
    Object *mhashtab;		/* MSYMBOL hash array */
    char *name; 		/* name of package */
    Object nicknames;		/* list of strings */
    Object use_list;		/* list of packages */
    Object used_by_list;	/* list of packages */
    Object shadowing_symbols;	/* list of symbols */
} SI_ALIGNED_TYPE SI_Package;

typedef struct {
    SI_Declare_static_relocation_field /* no semicolon */
    SI_Instance h;
    short *hashtab;		/* pointer to hash array */
    SI_Initial_symbol *symtab;	/* pointer to array of symbols */
    short symbol_count;		/* size of initial symbol table */
    Object *mhashtab;		/* MSYMBOL hash array */
    char *name; 		/* name of package */
    Object nicknames;		/* list of strings */
    Object use_list;		/* list of packages */
    Object used_by_list;	/* list of packages */
    Object shadowing_symbols;	/* list of symbols */
} SI_ALIGNED_TYPE SI_Package_constant;

#define PACKAGEP(o)		SI_INSTANCE_PRED(o, PACKAGE_TYPE)

#if (defined(SI_RUNTIME_INTERNAL) || SI_SUPPORT_MF)

#define PACKAGE_NAME(o)		SI_INSTANCE_FIELD(o, SI_Package, name)
#define PACKAGE_NICKNAMES(o)	SI_INSTANCE_FIELD(o, SI_Package,nicknames)
#define PACKAGE_USE_LIST(o)	SI_INSTANCE_FIELD(o, SI_Package, use_list)
#define PACKAGE_USED_BY_LIST(o) \
    SI_INSTANCE_FIELD(o, SI_Package, used_by_list)
#define PACKAGE_SHADOWING_SYMBOLS(o) \
    SI_INSTANCE_FIELD(o, SI_Package, shadowing_symbols)

#endif

#ifdef SI_RUNTIME_INTERNAL

#define PACKAGE_HASHTAB(o)	SI_INSTANCE_FIELD(o, SI_Package, hashtab)
#define PACKAGE_SYMTAB(o)	SI_INSTANCE_FIELD(o, SI_Package, symtab)
#define PACKAGE_SYMBOL_COUNT(o)	\
    SI_INSTANCE_FIELD(o, SI_Package, symbol_count)
#define PACKAGE_MHASHTAB(o)	SI_INSTANCE_FIELD(o, SI_Package, mhashtab)

#endif

#if SI_OBJECT_INITIALIZERS_WORK
#define INITIAL_PACKAGE(id, name, hashtab, symtab, symtab_size) \
    extern SI_Initial_symbol symtab[]; \
    SI_Package_constant id = \
                    {SI_STATIC_RELOCATION_INFO \
	             SI_INSTANCE_HEADER(PACKAGE_TYPE, 0, SI_Package_wrapper), \
		     hashtab, symtab, symtab_size, (Object *)NULL, \
		     name, NIL, NIL, NIL, NIL}; \
    SI_Initial_symbol symtab[(symtab_size)+1] = { \
        {SI_STATIC_RELOCATION_INFO \
	 {SI_HEADER(SI_PRECEDES_ISYMBOLS, 0), /* see symbol_package */ \
	  TAG_PACKAGE(id)}, \
	 0, 0, 0},
#define END_INITIAL_PACKAGE() }

#define DEFINE_PACKAGE(id, name, symtab, inittab, symtab_size) \
    SI_Initial_symbol symtab[symtab_size+1]; \
    extern SI_Long inittab[]; \
    SI_Package_constant id = \
                    {SI_STATIC_RELOCATION_INFO \
	             SI_INSTANCE_HEADER(PACKAGE_TYPE, 0, SI_Package_wrapper), \
		     NULL, symtab, symtab_size, (Object *)inittab, \
		     name, NIL, NIL, NIL, NIL}; \
    SI_Long  inittab[symtab_size+1] = { \
	    (symtab_size) 

#define END_DEFINE_PACKAGE() }




#define TAG_PACKAGE(id) 	SI_TAG_INSTANCE_CONSTANT(&id)
#endif

#if SI_SUPPORT_MF
typedef SI_Package_constant PACKAGE;	/* heap.c */
#endif

/******************************************************************************
 *
 * Hash-tables
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL

typedef struct {
    SI_Instance h;
    short size;			/* absolute or % increase for each resizing */
    UCHAR method;		/* equal/eql/eq (3 bits) fixed/% (1 bit) */
    UCHAR threshold;		/* % full before resizing occurs */
    Object hash_array;
} SI_Hashtable;
#define UNTAG_HASHTABLE(o)	SI_UNTAG_INSTANCE(o, SI_Hashtable)

#define HASH_METHOD(o)		UNTAG_HASHTABLE(o)->method
#define HASH_SIZE(o)		((long) SI_VECTOR_LENGTH(HASH_ARRAY(o)))
#define HASH_REHASH_SIZE(o)	UNTAG_HASHTABLE(o)->size
#define HASH_THRESHOLD(o)	UNTAG_HASHTABLE(o)->threshold
#define HASH_ARRAY(o)		UNTAG_HASHTABLE(o)->hash_array
#define HASH_TEST_METHOD(o)	(HASH_METHOD(o) & HASH_TEST)
#define HASH_SIZE_METHOD(o)	(HASH_METHOD(o) & HASH_PERCENT)

#endif /* SI_RUNTIME_INTERNAL */

/******************************************************************************
 *
 * Readtables
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL

typedef struct {
    SI_Instance h;
    Object entries;
} SI_Readtable;

#define READTABLE_ENTRIES(o) \
    SI_INSTANCE_FIELD(o, SI_Readtable, entries)

#endif /* SI_RUNTIME_INTERNAL */

/******************************************************************************
 *
 * Random states
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL

typedef struct {
    SI_Instance h;
    SI_Ulong seed;		/* Random number generator seed */
} SI_Random_state;

#define RANDOM_SEED(o) \
    SI_INSTANCE_FIELD(o, SI_Random_state, seed)

#endif /* SI_RUNTIME_INTERNAL */

/******************************************************************************
 *
 * Cobject, Foreign_Pointer
 *
 *****************************************************************************/

typedef struct {
    SI_Instance h;
    char *cobj;			/* arbitrary C object, not GC'ed */
    Object name;		/* COBJECT: name of object */
                                /* FOREIGN_POINTER: foreign_type struct */
} SI_Cobject;

#define COBJECT_NAME(o)		SI_STORED_OBJECT_FIELD(o,SI_Cobject,name)
#define COBJECT_OBJ(o)		SI_STORED_OBJECT_FIELD(o,SI_Cobject,cobj)
#define COBJECTP(o)		SI_INSTANCE_PRED(o,COBJECT_TYPE)

#define FOREIGN_POINTER_TYPE(o) COBJECT_NAME(o)
#define FOREIGN_POINTER_ADDRESS(o) (*(unsigned long *)&(COBJECT_OBJ(o)))
#define FOREIGN_POINTER_TYPE_P(o) COBJECTP(o)
#define FOREIGN_POINTER_P(o) \
   (FOREIGN_POINTER_TYPE_P(o) && \
    POINTER_FOREIGN_TYPE_P(FOREIGN_POINTER_TYPE(o)))

#define MAKE_FOREIGN_POINTER(result,address,type) \
  {result=SI_ALLOC(SI_Cobject,COBJECT_TYPE,SI_INSTANCE_TAG,SI_UGLY); \
   SI_SET_WRAPPER(result,SI_WRAPPER_foreign_pointer); \
   FOREIGN_POINTER_ADDRESS(result) = address; \
   FOREIGN_POINTER_TYPE(result) = type;}

/******************************************************************************
 *
 * Streams
 *
 ******************************************************************************
 *
 * *** This should probably all be redone differently.
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL

typedef struct {
    SI_Instance h;
    short info;			/* stream info, bits:
				 * 0-3	element-type
				 * 4-7	stream type (broadcast, two-way, etc.)
				 * 8-10 direction (:input,:output,:io,:probe)
				 * 1	closed-p (1=closed,0=open)
				 */
    short currpos;		/* current column position, starts at 0 */
    Object obj;
} SI_Stream;
#define UNTAG_STREAM(o)		SI_UNTAG_INSTANCE(o, SI_Stream)

#define STREAM_INFO(o)		UNTAG_STREAM(o)->info
#define STREAM_CURRPOS(o)	UNTAG_STREAM(o)->currpos
#define STREAM_ETYPE(o)		(STREAM_INFO(o) & 0x00f)
#define STREAM_STYPE(o)		(STREAM_INFO(o) & 0x0f0)
#define STREAM_DIR(o)		(STREAM_INFO(o) & 0x700)
#define STREAM_CLOSED_P(o)	(STREAM_INFO(o) & 0x800)
#define STREAM_OBJ(o)		UNTAG_STREAM(o)->obj
#define STRING_INPUT_STREAMP(o)	\
    (STREAMP(o) && (STREAM_STYPE(o) == STRING_INPUT_STREAM))
#define FILE_STREAM_FP(o)	((FILE *) COBJECT_OBJ(STREAM_OBJ(o)))
#define FILE_STREAM_NAME(o)	COBJECT_NAME(STREAM_OBJ(o))
#define INTERACTION_STREAM_FP(o) ((FILE *) COBJECT_OBJ(STREAM_OBJ(o)))

#endif /* SI_RUNTIME_INTERNAL */
