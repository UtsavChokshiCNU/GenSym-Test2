/* rltns.h -- Header File for rltns.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qand;
extern Object Qblock;
extern Object Qeq;
extern Object Qmember;
extern Object Qquote;
extern Object Qsequence;
extern Object Qsymbol;
extern Object Qunsigned_byte;
extern Object Qvector;

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
extern Object add_frame_note(int,...);
extern Object add_grammar_rules_function(Object);
extern Object add_to_directory_of_names(Object,Object);
extern Object add_to_relation(Object,Object,Object,Object,Object,Object);
extern Object add_virtual_attribute(Object,Object,Object,Object,Object,Object,Object);
extern Object alias_slot_name(int,...);
extern Object allocate_byte_vector_16(Object);
extern Object allocate_evaluation_sequence(Object);
extern Object allocate_evaluation_structure(Object);
extern Object allocate_managed_simple_vector_for_skip_list(Object);
extern Object assq_function(Object,Object);
extern Object block_relation_instances_violate_class_type_p(Object);
extern Object break_out_of_debug_messages(void);
extern Object bytes_per_simple_vector(Object);
extern Object change_primary_name_of_frame(Object,Object,Object);
extern Object change_relation_name_or_inverse_for_relation_instances(Object,Object,Object,Object);
extern Object change_secondary_name_of_frame(Object,Object,Object);
extern Object change_subject_or_object_class_for_relation_instances(Object,Object,Object,Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object classes_for_block_containing_relation(Object);
extern Object classes_for_other_blocks_in_relation(Object);
extern Object cleanup_for_relation(Object);
extern Object clear_optimized_constants(void);
extern Object clear_related_item_tree_skip_list(Object);
extern Object clear_relation_instance_tree_skip_list(Object);
extern Object collect_subclasses(Object);
extern Object compile_oneness_type_for_slot(int,...);
extern Object compile_relation_name_qm_for_slot(int,...);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object copy_for_slot_value(Object);
extern Object copy_list_of_relation_instance(Object);
extern Object copy_list_of_relation_instances(Object);
extern Object copy_out_current_wide_string(void);
extern Object copy_related_items(Object);
extern Object copy_text_string(Object);
extern Object define_type_specification_explicit_complex_type(Object,Object);
extern Object delete_frame_note_if_any(Object,Object);
extern Object delete_from_directory_of_names(Object,Object);
extern Object delete_skip_list_entry(Object,Object,Object,Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object estructure_slot(Object,Object,Object);
extern Object eval_cons_1(Object,Object);
extern Object eval_list_2(Object,Object);
extern Object evaluation_truth_value_is_true_p(Object);
extern Object frame_cons_1(Object,Object);
extern Object frame_list_4(Object,Object,Object,Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_3(Object,Object,Object);
extern Object get_instance_with_name_if_any(Object,Object);
extern Object get_item_or_item_list_for_uuid(Object);
extern Object get_items_in_this_relation(Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_property_value_function(int,...);
extern Object get_relation_instance_function(Object,Object);
extern Object get_relationships(Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object get_slot_description_value(Object,Object);
extern Object get_symbol_properties_function(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object give_warning_1(int,...);
extern Object initial_items_in_this_relation(Object);
extern Object initial_relationships(Object);
extern Object intern_text_string(int,...);
extern Object invoke_rules_for_relation_chaining(Object,Object,Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_permanent_relation_instance_structure_internal(void);
extern Object make_related_item_tree_skip_list_sentinel(Object,Object);
extern Object make_relation_instance(Object,Object,Object);
extern Object make_relation_instance_structure_1(Object,Object,Object);
extern Object make_relation_instance_tree_skip_list_sentinel(Object,Object);
extern Object make_skip_list_element_1(Object,Object,Object,Object);
extern Object make_symbol_properties_hash_table_skip_list_sentinel(Object,Object);
extern Object make_thread_array(Object);
extern Object memq_function(Object,Object);
extern Object more_than_one_related_item_p(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object no_change_while_running(void);
extern Object note_change_or_deletion(Object,Object);
extern Object note_change_to_all_related_items(Object);
extern Object note_change_to_runtime_data_for_block_1(Object);
extern Object notify_user_1(Object);
extern Object only_one_related_item_p(Object);
extern Object outstanding_relation_instance_count(void);
extern Object push_optimized_constant(Object);
extern Object put_class_of_object(Object,Object,Object);
extern Object put_class_of_subject(Object,Object,Object);
extern Object put_inverse_of_relation(Object,Object,Object);
extern Object put_relation_is_symetric_where_slot_is_absent(Object,Object);
extern Object put_relation_is_symmetric(Object,Object,Object);
extern Object put_relation_name(Object,Object,Object);
extern Object put_type_of_relation(Object,Object,Object);
extern Object reclaim_frame_list_1(Object);
extern Object reclaim_frame_tree_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_tree_1(Object);
extern Object reclaim_inverse_of_relation_value(Object,Object);
extern Object reclaim_list_of_block_snapshots(Object);
extern Object reclaim_related_item_tree_nodes(Object,Object);
extern Object reclaim_relation_instance(Object);
extern Object reclaim_relation_instance_structure_1(Object);
extern Object reclaim_relation_instance_tree_nodes(Object,Object);
extern Object reclaim_relation_instances(Object);
extern Object reclaim_relation_name_value(Object,Object);
extern Object reclaim_skip_list_element(Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_slot_value_list_1(Object);
extern Object reclaim_slot_value_tree_1(Object);
extern Object reclaim_text_string(Object);
extern Object record_block_for_tformat(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object relation_instance_structure_memory_usage(void);
extern Object relation_instances_empty_p(Object);
extern Object relation_violates_class_or_permanency_constraints_p(Object,Object,Object,Object);
extern Object remove_all_relations_instances_for_relation(Object,Object);
extern Object remove_from_relation(Object,Object,Object,Object,Object,Object);
extern Object remove_invalid_relation_instances(Object);
extern Object remove_relations_instances_for_object_of_relation(Object,Object,Object);
extern Object remove_transient_relation_instances(Object,Object);
extern Object replenish_lookup_cons_pool(void);
extern Object savable_block_p(Object);
extern Object scope_cons(Object,Object);
extern Object serve_item_p(Object);
extern Object set_evaluation_value_to_category_function(Object,Object);
extern Object set_property_value_function(Object,Object,Object);
extern Object set_relationships(Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object set_slot_value_to_evaluation_value_function(Object,Object);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object supply_a_or_an(Object);
extern Object text_string_p(Object);
extern Object tformat(int,...);
extern Object tformat_text_string(int,...);
extern Object twrite(Object);
extern Object twrite_beginning_of_wide_string(Object,Object);
extern Object twrite_general_string(Object);
extern Object type_error_in_setter(Object,Object,Object,Object,Object,Object,Object);
extern Object type_specification_type_p__with_explanation(Object,Object);
extern Object uniqueness_message(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object update_frame_notes_for_duplicate_uuids(Object);
extern Object update_object_pool_meters_list(Object);
extern Object update_relation_instances_if_necessary(Object,Object,Object,Object);
extern Object update_relation_inverse_name_for_relation_instances(Object,Object,Object);
extern Object update_relation_is_symmetric_for_relation_instances(Object,Object,Object);
extern Object update_relation_name_for_relation_instances(Object,Object,Object);
extern Object update_relation_object_class_for_relation_instances(Object,Object,Object);
extern Object update_relation_subject_class_for_relation_instances(Object,Object,Object);
extern Object update_representations_of_slot_value(int,...);
extern Object update_subscriptions_from_virtual_attribute_change(Object,Object,Object);
extern Object update_type_of_relation_for_relation_instances(Object,Object,Object);
extern Object upgrade_relation_instance(Object);
extern Object upgrade_relation_instance_internal(Object,Object);
extern Object upgrade_relation_instances(Object);
extern Object valid_relation_instance_classes_p(Object,Object);
extern Object validate_item_or_evaluation_value(Object,Object,Object);
extern Object validate_items_in_all_relations(Object,Object);
extern Object validate_relations_for_class(Object);
extern Object write_oneness_type_from_slot(Object,Object);
extern Object write_relation_summary_from_slot(Object,Object);
extern Object write_relation_yes_or_no_qm_from_slot(Object,Object);
extern Object write_symbol_from_slot(Object,Object);
extern Object write_warning_message_header(Object);

#else

extern Object add_class_to_environment();
extern Object add_frame_note();
extern Object add_grammar_rules_function();
extern Object add_to_directory_of_names();
extern Object add_to_relation();
extern Object add_virtual_attribute();
extern Object alias_slot_name();
extern Object allocate_byte_vector_16();
extern Object allocate_evaluation_sequence();
extern Object allocate_evaluation_structure();
extern Object allocate_managed_simple_vector_for_skip_list();
extern Object assq_function();
extern Object block_relation_instances_violate_class_type_p();
extern Object break_out_of_debug_messages();
extern Object bytes_per_simple_vector();
extern Object change_primary_name_of_frame();
extern Object change_relation_name_or_inverse_for_relation_instances();
extern Object change_secondary_name_of_frame();
extern Object change_subject_or_object_class_for_relation_instances();
extern Object check_if_superior_classes_are_defined();
extern Object classes_for_block_containing_relation();
extern Object classes_for_other_blocks_in_relation();
extern Object cleanup_for_relation();
extern Object clear_optimized_constants();
extern Object clear_related_item_tree_skip_list();
extern Object clear_relation_instance_tree_skip_list();
extern Object collect_subclasses();
extern Object compile_oneness_type_for_slot();
extern Object compile_relation_name_qm_for_slot();
extern Object copy_constant_wide_string_given_length();
extern Object copy_for_slot_value();
extern Object copy_list_of_relation_instance();
extern Object copy_list_of_relation_instances();
extern Object copy_out_current_wide_string();
extern Object copy_related_items();
extern Object copy_text_string();
extern Object define_type_specification_explicit_complex_type();
extern Object delete_frame_note_if_any();
extern Object delete_from_directory_of_names();
extern Object delete_skip_list_entry();
extern Object direct_structure_method();
extern Object estructure_slot();
extern Object eval_cons_1();
extern Object eval_list_2();
extern Object evaluation_truth_value_is_true_p();
extern Object frame_cons_1();
extern Object frame_list_4();
extern Object gensym_cons_1();
extern Object gensym_list_3();
extern Object get_instance_with_name_if_any();
extern Object get_item_or_item_list_for_uuid();
extern Object get_items_in_this_relation();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_property_value_function();
extern Object get_relation_instance_function();
extern Object get_relationships();
extern Object get_slot_description_of_class_description_function();
extern Object get_slot_description_value();
extern Object get_symbol_properties_function();
extern Object getfq_function_no_default();
extern Object give_warning_1();
extern Object initial_items_in_this_relation();
extern Object initial_relationships();
extern Object intern_text_string();
extern Object invoke_rules_for_relation_chaining();
extern Object load_and_initialize_type_description();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_permanent_relation_instance_structure_internal();
extern Object make_related_item_tree_skip_list_sentinel();
extern Object make_relation_instance();
extern Object make_relation_instance_structure_1();
extern Object make_relation_instance_tree_skip_list_sentinel();
extern Object make_skip_list_element_1();
extern Object make_symbol_properties_hash_table_skip_list_sentinel();
extern Object make_thread_array();
extern Object memq_function();
extern Object more_than_one_related_item_p();
extern Object mutate_global_property();
extern Object no_change_while_running();
extern Object note_change_or_deletion();
extern Object note_change_to_all_related_items();
extern Object note_change_to_runtime_data_for_block_1();
extern Object notify_user_1();
extern Object only_one_related_item_p();
extern Object outstanding_relation_instance_count();
extern Object push_optimized_constant();
extern Object put_class_of_object();
extern Object put_class_of_subject();
extern Object put_inverse_of_relation();
extern Object put_relation_is_symetric_where_slot_is_absent();
extern Object put_relation_is_symmetric();
extern Object put_relation_name();
extern Object put_type_of_relation();
extern Object reclaim_frame_list_1();
extern Object reclaim_frame_tree_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_tree_1();
extern Object reclaim_inverse_of_relation_value();
extern Object reclaim_list_of_block_snapshots();
extern Object reclaim_related_item_tree_nodes();
extern Object reclaim_relation_instance();
extern Object reclaim_relation_instance_structure_1();
extern Object reclaim_relation_instance_tree_nodes();
extern Object reclaim_relation_instances();
extern Object reclaim_relation_name_value();
extern Object reclaim_skip_list_element();
extern Object reclaim_slot_value();
extern Object reclaim_slot_value_list_1();
extern Object reclaim_slot_value_tree_1();
extern Object reclaim_text_string();
extern Object record_block_for_tformat();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object relation_instance_structure_memory_usage();
extern Object relation_instances_empty_p();
extern Object relation_violates_class_or_permanency_constraints_p();
extern Object remove_all_relations_instances_for_relation();
extern Object remove_from_relation();
extern Object remove_invalid_relation_instances();
extern Object remove_relations_instances_for_object_of_relation();
extern Object remove_transient_relation_instances();
extern Object replenish_lookup_cons_pool();
extern Object savable_block_p();
extern Object scope_cons();
extern Object serve_item_p();
extern Object set_evaluation_value_to_category_function();
extern Object set_property_value_function();
extern Object set_relationships();
extern Object set_skip_list_entry();
extern Object set_slot_value_to_evaluation_value_function();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object supply_a_or_an();
extern Object text_string_p();
extern Object tformat();
extern Object tformat_text_string();
extern Object twrite();
extern Object twrite_beginning_of_wide_string();
extern Object twrite_general_string();
extern Object type_error_in_setter();
extern Object type_specification_type_p__with_explanation();
extern Object uniqueness_message();
extern Object update_frame_notes_for_duplicate_uuids();
extern Object update_object_pool_meters_list();
extern Object update_relation_instances_if_necessary();
extern Object update_relation_inverse_name_for_relation_instances();
extern Object update_relation_is_symmetric_for_relation_instances();
extern Object update_relation_name_for_relation_instances();
extern Object update_relation_object_class_for_relation_instances();
extern Object update_relation_subject_class_for_relation_instances();
extern Object update_representations_of_slot_value();
extern Object update_subscriptions_from_virtual_attribute_change();
extern Object update_type_of_relation_for_relation_instances();
extern Object upgrade_relation_instance();
extern Object upgrade_relation_instance_internal();
extern Object upgrade_relation_instances();
extern Object valid_relation_instance_classes_p();
extern Object validate_item_or_evaluation_value();
extern Object validate_items_in_all_relations();
extern Object validate_relations_for_class();
extern Object write_oneness_type_from_slot();
extern Object write_relation_summary_from_slot();
extern Object write_relation_yes_or_no_qm_from_slot();
extern Object write_symbol_from_slot();
extern Object write_warning_message_header();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(All_virtual_attributes, Qall_virtual_attributes);
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
extern Object Bad_phrase;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_relation_instances, Qchain_of_available_relation_instances);
extern Object Chain_of_available_relation_instances_vector;
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Context_of_type_failure, Qcontext_of_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Debugging_reset, Qdebugging_reset);
DECLARE_VARIABLE_WITH_SYMBOL(Defer_notifications_qm, Qdefer_notifications_qm);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Grammar_categories_getting_yes_no_feature, Qgrammar_categories_getting_yes_no_feature);
DECLARE_VARIABLE_WITH_SYMBOL(In_write_module_as_clear_text_p, Qin_write_module_as_clear_text_p);
DECLARE_VARIABLE_WITH_SYMBOL(Initializing_clear_text_p, Qinitializing_clear_text_p);
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Last_slot_checked_of_type_failure, Qlast_slot_checked_of_type_failure);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object No_specific_property_value;
DECLARE_VARIABLE_WITH_SYMBOL(Note_blocks_in_tformat, Qnote_blocks_in_tformat);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Reason_for_type_failure, Qreason_for_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Relation_class_description, Qrelation_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Relation_instance_count, Qrelation_instance_count);
DECLARE_VARIABLE_WITH_SYMBOL(Releasing_kb_qm, Qreleasing_kb_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Resolving_definitional_name_conflicts_qm, Qresolving_definitional_name_conflicts_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Snapshots_of_related_blocks, Qsnapshots_of_related_blocks);
extern Object Symbol_properties_table;
extern Object The_type_description_of_relation_instance;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Type_at_type_failure, Qtype_at_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Value_at_type_failure, Qvalue_at_type_failure);
DECLARE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);
