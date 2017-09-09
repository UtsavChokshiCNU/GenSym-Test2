/* frms2b.h -- Header File for frms2b.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qsequence;
extern Object Qsymbol;

extern Object Pclos;
extern Object Pclos_run;
extern Object Pclosx;
extern Object Pcl;
extern Object Pcl_user;
extern Object Pkeyword;
extern Object Ptrun;
extern Object Ptx;

/* function declarations */

#ifdef USE_PROTOTYPES

extern Object add_class_to_environment(int,...);
extern Object add_virtual_attribute(Object,Object,Object,Object,Object,Object,Object);
extern Object alias_slot_name(int,...);
extern Object allocate_evaluation_sequence(Object);
extern Object assq_function(Object,Object);
extern Object block_p_function(Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object clear_optimized_constants(void);
extern Object compilations_up_to_date_p(Object);
extern Object copy_list_using_eval_conses_1(Object);
extern Object define_type_specification_explicit_complex_type(Object,Object);
extern Object delete_frame(Object);
extern Object evaluation_sequence_aref(Object,Object);
extern Object framep_function(Object);
extern Object get_class(Object);
extern Object get_foundation_class(Object);
extern Object get_property_value_function(int,...);
extern Object get_symbol_properties_function(Object);
extern Object initial_class(Object);
extern Object initial_foundation_class(Object);
extern Object is_block_p(Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_frame_with_compilation_removed(Object);
extern Object phrase_cons(Object,Object);
extern Object push_optimized_constant(Object);
extern Object put_cell_array(Object,Object,Object);
extern Object rebuild_backpointers_of_g2_cell_array(Object,Object);
extern Object reclaim_cell_array_value(Object,Object);
extern Object reclaim_invocation_locking_this_object_value(Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object release_lock(Object);
extern Object remove_compilations_from_obsolete_cell_array(Object);
extern Object set_evaluation_value_to_category_function(Object,Object);
extern Object set_lookup_slot_value_1(Object,Object,Object);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_slot_value_to_evaluation_value_function(Object,Object);
extern Object type_error_in_setter(Object,Object,Object,Object,Object,Object,Object);
extern Object type_specification_type_p__with_explanation(Object,Object);
extern Object update_frame_status(Object,Object,Object);
extern Object validate_item_or_evaluation_value(Object,Object,Object);

#else

extern Object add_class_to_environment();
extern Object add_virtual_attribute();
extern Object alias_slot_name();
extern Object allocate_evaluation_sequence();
extern Object assq_function();
extern Object block_p_function();
extern Object check_if_superior_classes_are_defined();
extern Object clear_optimized_constants();
extern Object compilations_up_to_date_p();
extern Object copy_list_using_eval_conses_1();
extern Object define_type_specification_explicit_complex_type();
extern Object delete_frame();
extern Object evaluation_sequence_aref();
extern Object framep_function();
extern Object get_class();
extern Object get_foundation_class();
extern Object get_property_value_function();
extern Object get_symbol_properties_function();
extern Object initial_class();
extern Object initial_foundation_class();
extern Object is_block_p();
extern Object lookup_global_or_kb_specific_property_value();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object note_frame_with_compilation_removed();
extern Object phrase_cons();
extern Object push_optimized_constant();
extern Object put_cell_array();
extern Object rebuild_backpointers_of_g2_cell_array();
extern Object reclaim_cell_array_value();
extern Object reclaim_invocation_locking_this_object_value();
extern Object regenerate_optimized_constant();
extern Object release_lock();
extern Object remove_compilations_from_obsolete_cell_array();
extern Object set_evaluation_value_to_category_function();
extern Object set_lookup_slot_value_1();
extern Object set_non_savable_lookup_slot_value();
extern Object set_property_value_function();
extern Object set_slot_value_to_evaluation_value_function();
extern Object type_error_in_setter();
extern Object type_specification_type_p__with_explanation();
extern Object update_frame_status();
extern Object validate_item_or_evaluation_value();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(All_virtual_attributes, Qall_virtual_attributes);
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Block_class_description, Qblock_class_description);
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Context_of_type_failure, Qcontext_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Current_block_of_dependent_frame, Qcurrent_block_of_dependent_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_frame_class_description, Qkb_frame_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Last_slot_checked_of_type_failure, Qlast_slot_checked_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Loading_kb_p, Qloading_kb_p);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Reason_for_type_failure, Qreason_for_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Type_at_type_failure, Qtype_at_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Value_at_type_failure, Qvalue_at_type_failure);
