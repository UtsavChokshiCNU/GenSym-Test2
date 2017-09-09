/* clos.h -- include for CLOS support.
 *
 * Copyright (C) 1991 Chestnut Software, Inc.  All rights reserved.
 *
 *
 */

#ifndef SI_CLOS_DOT_H
#define SI_CLOS_DOT_H

/* SI_CHANGE_CLASS_INITARGS
 *
 * If true, the generic function change-class accepts initargs.
 *
 * It seems to have been an oversight that change-class does not accept
 * initargs, since update-instance-for-different-class does accept them, and
 * the only way it is supposed to be called is from change-class.  There is a
 * proposal before X3J13 (9/2/91) to fix this, called CHANGE-CLASS-INITARGS.
 */

#ifndef SI_CHANGE_CLASS_INITARGS
#define SI_CHANGE_CLASS_INITARGS	0
#endif

/* This should either be flushed or added to interface and reserved.lisp. */
typedef int Boolean;

#include "wrapper.h"
#include "methargs.h"
#include "initclos.h"
#include "slotv.h"
#include "methcomb.h"

extern Object	Method_combination_effective_method;
extern Object	Generic_function_for_method_combination_errors;
extern Object	Method_combination_for_method_combination_errors;

extern Boolean	class_status_p();
extern Object	register_class_status();
extern void	set_class_status_p();

#define CLASS_TYPEP(o,t)	SI_typep_using_class(o,t)
extern Boolean	SI_typep_using_class();
extern Boolean	SI_subtypep__classes();

#ifdef SI_RUNTIME_INTERNAL

/* SI_BEGIN_STMT
 * SI_END_STMT
 *
 * Syntax:
 *	SI_BEGIN_STMT {statement}* SI_END_STMT;
 *
 * Description:
 *	Wrap these around a block of statements in a macro definition that is
 *	supposed to have single statement semantics.
 *
 * Examples:
 *	#define MUMBLE() \
 *	    SI_BEGIN_STMT \
 *	      begin_mumbling(); \
 *	      do_the_mumbling(); \
 *	      end_mumbling(); \
 *	    SI_END_STMT
 *
 *	MUMBLE();
 *
 * Notes:
 *	The MIT Scheme inspired "do { ... } while (0)" doesn't work for
 *	situations such as the last of the statements in the block being a
 *	return or goto, because the Sun C compiler will issue an unreachable
 *	statement warning for such a situation.  It seems to be more forgiving
 *	when this definition is used.
 */

#define SI_BEGIN_STMT	if (TRUE) {
#define SI_END_STMT	} else (void)0

#define ALLOC_STANDARD_INSTANCE() \
    SI_ALLOC(SI_Standard_instance, SI_STANDARD_INSTANCE_TYPE, \
	     SI_INSTANCE_TAG, SI_UGLY)

#define ALLOC_GENERIC_FUNCTION() \
    SI_ALLOC(SI_Function, SI_FUNCTION_TYPE, SI_INSTANCE_TAG, SI_UGLY)

#define ALLOC_METHOD() \
    SI_ALLOC(SI_Method, SI_METHOD_TYPE, SI_INSTANCE_TAG, SI_UGLY)

/* Spread a list of arguments onto the Lisp stack.
 * n is incremented by the number of arguments spread.
 */
#define SPREAD_ARGUMENTS(args, n) \
    SI_BEGIN_STMT \
      Object SPREAD_args = (args); \
      int SPREAD_n = 0; \
 \
      for (;CONSP(SPREAD_args); SPREAD_args = M_CDR(SPREAD_args), SPREAD_n++) \
	STACK_REF(SPREAD_n) = M_CAR(SPREAD_args); \
      Stack += SPREAD_n; \
      (n) += SPREAD_n; \
    SI_END_STMT

#define INIT_GLOBAL_VAR(var, init) \
    SI_BEGIN_STMT \
      if (var == UNBOUND) { \
	PROTECT_GLOBAL(var); \
	var = init; \
      } \
    SI_END_STMT

#define SI_METHOD(name) \
Object name(em, index, frame, argq) \
  Object em, index, frame, argq;    

/* Internal slot accessor macros. */
#ifdef SI_BOOTSTRAP_CLOS

#define SI_SLOT_VALUE_INDEXED(object, slot_name, index) \
    STANDARD_OBJECT_REF(object, index)

#define SI_SLOT_BOUNDP_INDEXED(object, slot_name, index) \
    (STANDARD_OBJECT_REF(object, index) == UNBOUND)

#define SI_SET_SLOT_VALUE_INDEXED(object, slot_name, value, index) \
    (STANDARD_OBJECT_REF(object, index) = (value))

#else

#define SI_SLOT_VALUE_INDEXED(object, slot_name, index) \
    (SI_Validation_tables_initialized \
	? SLOT_VALUE_INDEXED(object, slot_name, index) \
	: SLOT_VALUE(object, slot_name, index))

#define SI_SLOT_BOUNDP_INDEXED(object, slot_name, index) \
    (SI_Validation_tables_initialized \
	? SLOT_BOUNDP_INDEXED(object, slot_name, index) \
	: SLOT_BOUNDP(object, index))

#define SI_SET_SLOT_VALUE_INDEXED(object, slot_name, value, index) \
    (SI_Validation_tables_initialized \
	? SET_SLOT_VALUE_INDEXED(object, slot_name, value, index) \
	: SET_SLOT_VALUE(object, value, index))

#endif /* defined(SI_BOOTSTRAP_CLOS) */

/* Stuff used or set up at initialization time. */
extern Boolean	SI_Check_initargs;
extern Boolean	SI_Generic_functions_bootstrapped;
extern Boolean	SI_Validation_tables_initialized;
extern Object	SI_Initial_class_info;
extern Object	SI_Initial_generic_function_info;
extern Object	SI_Make_instances_obsolete_slots_to_flush;
extern void	SI_INIT_clos_bootstrap_info();
extern void	SI_INIT_method_combination();
extern void	SI_alloc_early_class_wrappers();
extern void	SI_make_wrapper_class_associations();
extern void	SI_bootstrap_clos();
extern void	SI_record_early_class();
extern Object	SI_WRAPPER_early_generic_function;
extern void	SI_init_slot_index_table();

/* Generic function dispatching. */
extern Object	SI_uncached_discriminator();
extern Object	SI_empty_cache_discriminator();
extern Object	SI_caching_discriminator();
extern Object	SI_uninitialized_generic_function();
extern Object	SI_eql_caching_discriminator();
extern void	SI_display_cache_statistics();

/* Error signaling helper functions. */
extern void	SI_documentation_extraneous_type_error();
extern void	SI_odd_length_keylist_error();
extern void	SI_unexpected_keyword_argument_error();
extern void	SI_too_few_arguments_error();
extern void	SI_too_many_arguments_error();
extern void	SI_index_bound_error();

extern Object	SI_coerce_to_class();
extern Object	SI_make_class_wrapper();
extern void	SI_make_wrapper_obsolete();
extern Object	SI_find_forward_referenced_class();

/* Lambda list manipulation functions. */
extern Boolean SI_parse_lambda_list();
struct SI_lambda_parser {
  void (*required)();
  void (*optional)();
  void (*rest)();
  void (*keyp)();
  void (*key)();
  void (*alwkyp)();
  void (*aux)();
};
extern Object	SI_encode_lambda_list();
extern Object	SI_make_encoded_lambda_list();
extern Boolean	SI_congruent_lambda_list_encodings_p();
extern Object	SI_compute_argument_precedence_map();
extern Object	SI_collect_required_arguments();

extern Object	SI_compute_applicable_methods_using_classes();
extern Object	SI_collect_direct_slot_definitions();
extern Object	SI_compute_class_precedence_vector();
extern Object	SI_compute_class_slots_alist();

extern void	SI_forget_effective_methods();
extern Object	SI_add_reader_method();
extern Object	SI_add_writer_method();

extern Object	SI_allocate_instance__early_dispatcher();
extern Object	SI_copy_instance__standard_class();
extern Object	SI_copy_instance__funcallable_standard_class();
extern Object	SI_copy_instance__method_class();

extern Object	SI_shared_initialize__early_dispatcher();

extern Object	SI_compute_class_prototype__early_dispatcher();

/* Convenient variables for some frequently used class metaobject. */

extern Object   SI_The_class_T;
extern Object   SI_The_class_Standard_class;
extern Object   SI_The_class_Funcallable_standard_class;
extern Object   SI_The_class_Method_class;
extern Object   SI_The_class_Standard_object;
extern Object   SI_The_class_Standard_generic_function;
extern Object   SI_The_class_Standard_method;
extern Object   SI_The_class_Standard_reader_method;
extern Object   SI_The_class_Standard_writer_method;
extern Object	SI_The_class_Standard_direct_slot_definition;
extern Object	SI_The_class_Standard_effective_local_slot_definition;

#define INIT_GLOBAL_CLASS_VAR(var, name) \
    INIT_GLOBAL_VAR(var, find_class(name, T, NIL))

#define INIT_THE_CLASS_T() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_T, Qt)

#define INIT_THE_CLASS_STANDARD_CLASS() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_class, Qstandard_class)

#define INIT_THE_CLASS_FUNCALLABLE_STANDARD_CLASS() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Funcallable_standard_class, \
			  Qfuncallable_standard_class)

#define INIT_THE_CLASS_METHOD_CLASS() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Method_class, Qmethod_class)

#define INIT_THE_CLASS_STANDARD_OBJECT() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_object, Qstandard_object)

#define INIT_THE_CLASS_STANDARD_GENERIC_FUNCTION() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_generic_function, \
			  Qstandard_generic_function)

#define INIT_THE_CLASS_STANDARD_METHOD() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_method, Qstandard_method)

#define INIT_THE_CLASS_STANDARD_READER_METHOD() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_reader_method, \
			  Qstandard_reader_method)

#define INIT_THE_CLASS_STANDARD_WRITER_METHOD() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_writer_method, \
			  Qstandard_writer_method)

#define INIT_THE_CLASS_STANDARD_DIRECT_SLOT_DEFINITION() \
    INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_direct_slot_definition, \
			  Qstandard_direct_slot_definition)

#define INIT_THE_CLASS_STANDARD_EFFECTIVE_LOCAL_SLOT_DEFINITION() \
 INIT_GLOBAL_CLASS_VAR(SI_The_class_Standard_effective_local_slot_definition, \
		       Qstandard_effective_local_slot_definition)

/* Pre-defined method declarations. */
extern Object	SI_add_direct_subclass();
extern Object	SI_add_direct_subclass__around();
extern Object	SI_add_direct_subclass__before();
extern Object	SI_add_direct_subclass__after__forward_class();
extern Object	SI_add_method();
extern Object	SI_add_method__before();
extern Object	SI_add_method__after__change_class();
extern Object	SI_add_method__after__creation();
extern Object	SI_add_method__after__reinitialization();
extern Object	SI_allocate_instance__funcallable_standard_class();
extern Object	SI_allocate_instance__method_class();
extern Object	SI_allocate_instance__standard_class();
extern Object	SI_change_class();
extern Object	SI_change_class__t_symbol();
extern Object	SI_change_class__around__t_class();
extern Object	SI_change_class__around__metaobject();
extern Object	SI_change_class__around__class();
extern Object	SI_class_default_initargs();
extern Object	SI_class_default_superclasses__funcallable_standard_class();
extern Object	SI_class_default_superclasses__method_class();
extern Object	SI_class_default_superclasses__standard_class();
extern Object	SI_class_default_superclasses__structure_class();
extern Object	SI_class_finalized_p();
extern Object	SI_class_fully_defined_p();
extern Object	SI_class_fully_defined_p__forward_class();
extern Object	SI_class_slots();
extern Object	SI_class_precedence_list();
extern Object	SI_class_prototype();
extern Object	SI_compute_applicable_methods();
extern Object	SI_compute_class_default_initargs();
extern Object	SI_compute_class_precedence_list();
extern Object	SI_compute_class_prototype__before();
extern Object	SI_compute_class_prototype__funcallable_standard_class();
extern Object	SI_compute_class_prototype__method_class();
extern Object	SI_compute_class_prototype__standard_class();
extern Object	SI_compute_effective_method();
extern Object	SI_compute_effective_slot_definition();
extern Object	SI_compute_effective_slot_definition_initargs();
extern Object	SI_compute_slot_definition_location();
extern Object	SI_compute_slot_definition_location__local();
extern Object	SI_compute_slot_definition_location__shared();
extern Object	SI_compute_slot_definition_locations();
extern Object	SI_compute_slot_definition_locations__structure();
extern Object	SI_compute_slots();
extern Object	SI_compute_valid_change_class_initargs();
extern Object	SI_compute_valid_creation_initargs();
extern Object	SI_compute_valid_reinitialization_initargs();
extern Object	SI_default_initargs();
extern Object	SI_direct_slot_definition_class();
extern Object	SI_direct_slot_definition_class__structure();
extern Object	SI_effective_slot_definition_class();
extern Object	SI_effective_slot_definition_class__structure();
extern Object	SI_finalize_inheritance();
extern Object	SI_finalize_inheritance__before();
extern Object	SI_finalize_inheritance__around();
extern Object	SI_find_method();
extern Object	SI_function_keywords();
extern Object	SI_initialize_instance();
extern Object	SI_initialize_instance__after__class();
extern Object	SI_initialize_instance__after__function();
extern Object	SI_initialize_instance__after__method();
extern Object	SI_local_slot_definition_p();
extern Object	SI_local_slot_definition_p__default();
extern Object	SI_local_slot_definition_p__local();
extern Object	SI_local_slot_definition_p__shared();
extern Object	SI_make_instance();
extern Object	SI_make_instance__symbol();
extern Object	SI_make_instances_obsolete();
extern Object	SI_method_function();
extern Object	SI_no_applicable_method();
extern Object	SI_no_next_method();
extern Object	SI_no_primary_method();
extern Object	SI_permit_metaobject_reinitialization();
extern Object	SI_permit_metaobject_reinitialization__forward_class();
extern Object	SI_permit_metaobject_reinitialization__function();
extern Object	SI_permit_metaobject_reinitialization__standard_class();
extern Object	SI_print_object();
extern Object	SI_print_object__class_wrapper();
extern Object	SI_print_object__effective_method();
extern Object	SI_print_object__metaobject();
extern Object	SI_print_object__method_combination();
extern Object	SI_reinitialize_instance();
extern Object	SI_reinitialize_instance__around__metaobject();
extern Object	SI_reinitialize_instance__around__class();
extern Object	SI_reinitialize_instance__before__class();
extern Object	SI_reinitialize_instance__after__class();
extern Object	SI_remove_direct_subclass();
extern Object	SI_remove_method();
extern Object	SI_remove_method__after__change_class();
extern Object	SI_remove_method__after__creation();
extern Object	SI_remove_method__after__reinitialization();
extern Object	SI_set_class_finalized_p();
extern Object	SI_set_class_fully_defined_p();
extern Object	SI_set_class_fully_defined_p__around__forward_class();
extern Object	SI_shared_initialize();
extern Object	SI_shared_initialize__after__standard_generic_function();
extern Object	SI_shared_slot_definition_p();
extern Object	SI_shared_slot_definition_p__default();
extern Object	SI_shared_slot_definition_p__local();
extern Object	SI_shared_slot_definition_p__shared();
extern Object	SI_update_instance_for_different_class();
extern Object	SI_update_instance_for_different_class__before__class();
extern Object	SI_update_instance_for_different_class__after__class();
extern Object	SI_valid_change_class_initargs();
extern Object	SI_valid_creation_initargs();
extern Object	SI_valid_reinitialization_initargs();
extern Object	SI_validate_superclass();
extern Object	SI_validate_superclass__forward();
extern Object	SI_validate_superclass__funcallable();
extern Object	SI_validate_superclass__method();
extern Object	SI_validate_superclass__standard();
extern Object	SI_validate_superclass__structure();

#endif /* defined(SI_RUNTIME_INTERNAL) */

#endif /* !defined(SI_CLOS_DOT_H) */
