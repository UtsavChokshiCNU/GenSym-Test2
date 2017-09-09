/* slotv.h -- Macros for slot accesses.
 *
 * Copyright (C) 1991 Chestnut Software, Inc.  All rights reserved.
 *
 */

/******************************************************************************
 *
 * Helper functions.
 *
 * There are several helper functions that are called when the optimizations
 * for slot accesses are inhibited.  These functions are called when
 * appropriate by the optimized versions of the corresponding functions, and
 * are not intended to be called directly.
 *
 * These functions provide the link between the slot access functions and the
 * underlying generic functions.  They first determine the class of the object
 * (as if by class-of), and then search the effective slots of the class for a
 * slot definition with the specified name.  If a matching slot definition
 * object is found, the corresponding generic function is called with the class
 * and slot definition provided as arguments.  If no matching slot definition
 * is found, the function slot-missing is called instead.
 *
 * The correspondences between slot access function and unoptimized helper
 * function are as follows: 
 *
 *	slot-boundp		SI_slot_boundp
 *	slot-makunbound		SI_slot_makunbound
 *	slot-value		SI_slot_value
 *	set-slot-value		SI_set_slot_value
 *
 * In addition, there is a function that provides the link between slot-value
 * and slot-unbound, called SI_slot_value_unbound
 *
 *****************************************************************************/

extern Object	SI_set_slot_value();
extern Boolean	SI_slot_boundp();
extern void	SI_slot_makunbound();
extern Object	SI_slot_value();
extern Object	SI_slot_value_unbound();

extern void	SI_init_slot_index();
extern void	SI_init_slot_table();

/******************************************************************************
 *
 * Built-in method definitions.
 *
 * These internal functions define the behavior of the slot access generic
 * functions for internal-standard-class.  The corresponding generic functions
 * should be initialized with methods that use these functions and have the
 * appropriate specializations.
 *
 *****************************************************************************/

extern Object	SI_SETF_slot_value_using_class();
extern Object	SI_SETF_slot_value_using_class_local();
extern Object	SI_SETF_slot_value_using_class_shared();

extern Object	SI_slot_boundp_using_class();
extern Object	SI_slot_boundp_using_class_local();
extern Object	SI_slot_boundp_using_class_shared();

extern Object	SI_slot_makunbound_using_class();
extern Object	SI_slot_makunbound_using_class_local();
extern Object	SI_slot_makunbound_using_class_shared();

extern Object	SI_slot_value_using_class();
extern Object	SI_slot_value_using_class_local();
extern Object	SI_slot_value_using_class_shared();

extern Object	SI_slot_missing();
extern Object	SI_slot_unbound();

extern Object	SI_standard_reader_method();
extern Object	SI_standard_writer_method();

extern Object	SI_optimize_slot_accesses();
extern Object	SI_optimize_slot_access();
extern Object	SI_optimize_slot_access__local();
extern Object	SI_elide_access_method_p();
extern Object	SI_elide_access_method_p__local();

/******************************************************************************
 *
 * Mapping from slot names to slot indices.
 *
 * SI_global_slot_index(slot_name, default)
 *   Get the global index for the slot name.
 *   If no index specified for the name, return the default value.
 *
 * ASSIGN_SLOT_INDEX(slot_name, slot_index)
 *   Set the global index for the specified slot name.
 *
 *****************************************************************************/

extern void	ASSIGN_SLOT_INDEX();

#ifdef SI_RUNTIME_INTERNAL
extern Object SI_global_slot_index();
#endif

/******************************************************************************
 *
 * Shared slots
 *
 ******************************************************************************
 *
 * Shared slot locations are implemented as cons cells which are stored in the
 * LOCATION slot of each of the effective slot definition objects derived from
 * a single direct slot definition specifying a shared slot.
 *
 * The cells are also collected in an alist in the defining class, so that all
 * subclasses can find them.
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL
#define MAKE_SHARED_SLOT_LOCATION(name)		cons(name, UNBOUND)
#define SHARED_SLOT_LOCATION_VALUE(location)	M_CDR(location)
#define SHARED_SLOT_LOCATION_NAME(location)	M_CAR(location)
#define SHARED_SLOT_LOCATION_BOUNDP(location) \
    (SHARED_SLOT_LOCATION_VALUE(location) != UNBOUND)
#define SHARED_SLOT_LOCATION_MAKUNBOUND(location) \
    (SHARED_SLOT_LOCATION_VALUE(location) = UNBOUND)
#define ADD_SHARED_SLOT_LOCATION(new, locations) cons(new, locations)
#define DELETE_SHARED_SLOT_LOCATION(old, locations) \
    delete_eq(old, locations)
#define FIND_SHARED_SLOT_LOCATION(name, locations) \
    assoc_eq(name, locations)
#endif

/******************************************************************************
 *
 * Slot accessor info
 *
 * Slot accessors such as the reader and writer method functions use this stuff
 * when manipulating the info recorded by the constructor of the method.
 *
 *****************************************************************************/

#ifdef SI_RUNTIME_INTERNAL
#define SI_MAKE_SLOT_ACCESSOR_INFO(name, index)	cons(name, index)
#define SI_SLOT_ACCESSOR_INFO_NAME(info)	M_CAR(info)
#define SI_SLOT_ACCESSOR_INFO_INDEX(info)	M_CDR(info)
#endif

/******************************************************************************
 *
 * Slot access type test
 *
 * This macro performs the type test needed by the (safe) indexed slot access
 * macros.  It is implemented in terms of SI_INSTANCEP() rather than
 * STANDARD_OBJECT_P() because the wrapper validation mechanism will screen out
 * anything that isn't a standard object by getting a validation miss, while
 * SI_INSTANCEP() has a more efficient impementation when using 3bit tagging
 * (just a tag comparison, rather than a range test on the type code stored in
 * the header).
 *
 *****************************************************************************/

#define SI_SLOT_ACCESS_TYPE_CHECK(o)	SI_INSTANCEP(o)

/******************************************************************************
 *
 * SLOT_VALUE
 *
 * Calls to slot-value may be transformed into calls to this macro within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, the
 * slot-name is a compile-time constant with a known global index, and the slot
 * location is statically determinable at compile-time.
 *
 * The object argument might be evaluated more than once.
 * The slot_name argument might not be evaluated.
 *
 * The object argument must be a Standard_object.
 * The slot_name argument must be a symbol.
 * The index argument must be a fixnum.
 *
 *****************************************************************************/

/* Obsolete: Users of the macros must include Declare_slot_value.
 * extern Object SI_Slot_value_temp;
 */

#define Declare_slot_value	register Object SI_Slot_value_temp

#define SLOT_VALUE(object, slot_name, index)				\
    (EQ(SI_Slot_value_temp = STANDARD_OBJECT_REF(object, index), UNBOUND) \
	? SI_slot_value_unbound(object, slot_name)			\
	: SI_Slot_value_temp)

/******************************************************************************
 *
 * SLOT_VALUE_USING_WRAPPER
 *
 * Calls to slot-value may be transformed into calls to this function within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, and the
 * slot-name is a compile-time constant with a known slot name index.  The idea
 * is that the method body will read out the wrapper once up front, and then
 * pass it to this function.
 *
 * The object argument is evaluated out of order.
 * The slot_name argument is evaluated more than once.
 * The index argument might be evaluated more than once.
 *
 * The object argument must be a Standard_object.
 * The slot_name argument must be a symbol.
 * The wrapper argument must be a class-wrapper.
 * The index argument must be a fixnum.
 *
 *****************************************************************************/

#define SLOT_VALUE_USING_WRAPPER(object, slot_name, wrapper, index)	\
    (SI_VALIDATE_SLOT_READ(slot_name, wrapper, index) ?			\
     SLOT_VALUE(object, slot_name, index) :				\
     SI_slot_value(object, slot_name))

/******************************************************************************
 *
 * SLOT_VALUE_INDEXED
 *
 * Calls to slot-value may be transformed into calls to this function when the
 * slot-name is a compile-time constant with a known slot-name index.
 *
 * The object argument is evaluated more than once.
 * The slot_name argument is evaluated more than once.
 * The index argument might be evaluated more than once.
 *
 * The slot_name argument must be a symbol.
 * The index argument must be a fixnum.
 *
 *****************************************************************************/

#define SLOT_VALUE_INDEXED(object, slot_name, index) \
    ((SI_SLOT_ACCESS_TYPE_CHECK(object) && \
      SI_VALIDATE_SLOT_READ(slot_name, INSTANCE_WRAPPER(object), index)) \
	? SLOT_VALUE(object, slot_name, index) \
	: SI_slot_value(object, slot_name))

/******************************************************************************
 *
 * SLOT_BOUNDP
 *
 * Calls to slot-boundp may be transformed into calls to this macro within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, the
 * slot-name is a compile-time constant with a known global index, and the slot
 * location is statically determinable at compile-time.
 *
 * The object argument must be a Standard_object.
 * The index argument must be a fixnum.
 *
 * The return value is an unboxed boolean.
 *
 *****************************************************************************/

#define SLOT_BOUNDP(object, index)	\
    (!EQ(STANDARD_OBJECT_REF(object, index), UNBOUND))

/******************************************************************************
 *
 * SLOT_BOUNDP_USING_WRAPPER
 *
 * Calls to slot-boundp may be transformed into calls to this function within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, and the
 * slot-name is a compile-time constant with a known slot name index.  The idea
 * is that the method body will read out the wrapper once up front, and then
 * pass it to this function.
 *
 * The object argument is evaluated more than once.
 * The slot_name argument is evaluated more than once.
 * The index argument might be evaluated more than once.
 *
 * The object argument must be a Standard_object.
 * The slot_name argument must be a symbol.
 * The wrapper argument must be a class-wrapper.
 * The index argument must be a fixnum.
 *
 * The result is an unboxed boolean.
 *
 *****************************************************************************/

#define SLOT_BOUNDP_USING_WRAPPER(object, slot_name, wrapper, index)	\
    (SI_VALIDATE_SLOT_READ(slot_name, wrapper, index) ?			\
     SLOT_BOUNDP(object, index) :					\
     SI_slot_boundp(object, slot_name))

/******************************************************************************
 *
 * SLOT_BOUNDP_INDEXED
 *
 * Calls to slot-boundp may be transformed into calls to this function when the
 * slot-name is a compile-time constant with a known slot-name index.
 *
 * The object argument is evaluated more than once.
 * The slot_name argument is evaluated more than once.
 * The index argument might be evaluated more than once.
 *
 * The slot_name argument must be a symbol.
 * The index argument must be a fixnum.
 *
 * The result is an unboxed boolean.
 *
 *****************************************************************************/

#define SLOT_BOUNDP_INDEXED(object, slot_name, index) \
    ((SI_SLOT_ACCESS_TYPE_CHECK(object) && \
      SI_VALIDATE_SLOT_READ(slot_name, INSTANCE_WRAPPER(object), index)) \
	? SLOT_BOUNDP(object, index) \
	: SI_slot_boundp(object, slot_name))

/******************************************************************************
 *
 * SET_SLOT_VALUE
 *
 * Calls to set-slot-value may be transformed into calls to this macro within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, the
 * slot-name is a compile-time constant with a known global index, and the slot
 * location is statically determinable at compile-time.
 *
 * *** I'm not even sure what the order of evaluation is here.
 *
 * The object argument must be a Standard_object.
 * The index argument must be a fixnum.
 *
 *****************************************************************************/

#define SET_SLOT_VALUE(object, value, index)		\
    (STANDARD_OBJECT_REF(object, index) = (value))

/******************************************************************************
 *
 * SET_SLOT_VALUE_USING_WRAPPER
 *
 * Calls to (setf slot-value) may be transformed into calls to this function
 * within method bodies which are specialized on the object, the type of the
 * object is known to use Standard_instance as its base representation type,
 * and the slot-name is a compile-time constant with a known slot name index.
 * The idea is that the method body will read out the wrapper once up front,
 * and then pass it to this function.
 *
 * The object argument is evaluated out of order.
 * The slot_name argument may be evaluated more than once.
 * The value argument may be evaluated out of order.
 * The index argument is evaluated more than once.
 *
 * The object argument must be a Standard_object.
 * The slot_name argument must be a symbol.
 * The wrapper argument must be a class-wrapper.
 * The index argument must be a fixnum.
 *
 *****************************************************************************/

#define SET_SLOT_VALUE_USING_WRAPPER(object,slot_name,value,wrapper,index) \
    (SI_VALIDATE_SLOT_WRITE(slot_name, wrapper, index) ?		\
     SET_SLOT_VALUE(object, value, index) :				\
     SI_set_slot_value(object, slot_name, value))

/******************************************************************************
 *
 * SET_SLOT_VALUE_INDEXED
 *
 * Calls to (setf slot-value) may be transformed into calls to this function
 * when the slot-name is a compile-time constant with a known slot-name index.
 *
 * The slot_name argument must be a symbol.
 * The index argument must be a fixnum.
 *
 *****************************************************************************/

#define SET_SLOT_VALUE_INDEXED(object, slot_name, value, index) \
    ((SI_SLOT_ACCESS_TYPE_CHECK(object) && \
      SI_VALIDATE_SLOT_WRITE(slot_name, INSTANCE_WRAPPER(object), index)) \
	? SET_SLOT_VALUE(object, value, index) \
	: SI_set_slot_value(object, slot_name, value))

/******************************************************************************
 *
 * SLOT_MAKUNBOUND
 *
 * Calls to slot-makunbound may be transformed into calls to this macro within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, the
 * slot-name is a compile-time constant with a known global index, and the slot
 * location is statically determinable at compile-time.
 *
 * The object argument must be a Standard_object.
 * The index argument must be a fixnum.
 *
 * This does not completely implement the high-level function, since this does
 * not return the object as the result.  Arranging for the proper return value
 * is the responsibility of the caller.
 *
 *****************************************************************************/

#define SLOT_MAKUNBOUND(object, index)	\
    ((void)SET_SLOT_VALUE(object, UNBOUND, index))

/******************************************************************************
 *
 * SLOT_MAKUNBOUND_USING_WRAPPER
 *
 * Calls to slot-makunbound may be transformed into calls to this function
 * within method bodies which are specialized on the object, the type of the
 * object is known to use Standard_instance as its base representation type,
 * and the slot-name is a compile-time constant with a known slot name index.
 * The idea is that the method body will read out the wrapper once up front,
 * and then pass it to this function.
 *
 * The object argument must be a Standard_object.
 * The slot_name argument must be a symbol.
 * The wrapper argument must be a class-wrapper.
 * The index argument must be a fixnum.
 *
 * This does not completely implement the high-level function, since this does
 * not return the object as the result.  Arranging for the proper return value
 * is the responsibility of the caller.
 *
 *****************************************************************************/

/* *** This stuff with returning "0" from both sides of the : operator appears
 * *** to be necessary to keep Sun cc from barfing over type mismatch for the
 * *** operators.  Note that no amount of void casts seemed to fix it.  Looks
 * *** like a bug to me.
 */
#define SLOT_MAKUNBOUND_USING_WRAPPER(object, slot_name, wrapper, index) \
    ((void)(SI_VALIDATE_SLOT_WRITE(slot_name, wrapper, index) ? \
	      (SLOT_MAKUNBOUND(object, index), 0) : \
	      (SI_slot_makunbound(object, slot_name), 0)))

/******************************************************************************
 *
 * SLOT_MAKUNBOUND_INDEXED
 *
 * Calls to slot_makunbound may be transformed into calls to this function
 * when the slot-name is a compile-time constant with a known slot-name index.
 *
 * The slot_name argument must be a symbol.
 * The index argument must be a fixnum.
 *
 * This does not completely implement the high-level function, since this does
 * not return the object as the result.  Arranging for the proper return value
 * is the responsibility of the caller.
 *
 *****************************************************************************/

/* *** This stuff with returning "0" from both sides of the : operator appears
 * *** to be necessary to keep Sun cc from barfing over type mismatch for the
 * *** operators.  Note that no amount of void casts seemed to fix it. */

#define SLOT_MAKUNBOUND_INDEXED(object, slot_name, index) \
    ((void)((SI_SLOT_ACCESS_TYPE_CHECK(object) && \
	     SI_VALIDATE_SLOT_WRITE(slot_name, \
				    INSTANCE_WRAPPER(object), index)) \
		? (SLOT_MAKUNBOUND(object, index), 0) \
		: (SI_slot_makunbound(object, slot_name), 0)))

/******************************************************************************
 *
 * SLOT_EXISTS_P
 *
 * No C definition needed here, since the result is always T.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * SLOT_EXISTS_P_USING_WRAPPER
 *
 * Calls to slot-exists-p may be transformed into calls to this function within
 * method bodies which are specialized on the object, the type of the object is
 * known to use Standard_instance as its base representation type, and the
 * slot-name is a compile-time constant with a known slot name index.  The idea
 * is that the method body will read out the wrapper once up front, and then
 * pass it to this function.
 *
 * The object argument must be a Standard_object.
 * The slot_name argument must be a symbol.
 * The wrapper argument must be a class-wrapper.
 * The index argument must be a fixnum.
 *
 * The result is an unboxed boolean.
 *
 *****************************************************************************/

#define SLOT_EXISTS_P_USING_WRAPPER(object, slot_name, wrapper, index)	\
    (SI_VALIDATE_SLOT_READ(slot_name, wrapper, index) ||		\
     SI_VALIDATE_SLOT_WRITE(slot_name, wrapper, index) ||		\
     TRUEP(slot_exists_p(object, slot_name)))

/******************************************************************************
 *
 * SLOT_EXISTS_P_INDEXED
 *
 * Calls to slot-exists-p may be transformed into calls to this function
 * when the slot-name is a compile-time constant with a known slot-name index.
 *
 * The slot_name argument must be a symbol.
 * The index argument must be a fixnum.
 *
 * The result is an unboxed boolean.
 *
 *****************************************************************************/

#define SLOT_EXISTS_P_INDEXED(object, slot_name, index) \
    ((SI_SLOT_ACCESS_TYPE_CHECK(object) \
      && (SI_VALIDATE_SLOT_READ(slot_name, \
				INSTANCE_WRAPPER(object), \
				index) \
	  || SI_VALIDATE_SLOT_WRITE(slot_name, \
				    INSTANCE_WRAPPER(object), \
				    index))) \
     || TRUEP(slot_exists_p(object, slot_name)))
