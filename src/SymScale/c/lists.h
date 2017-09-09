/* lists.h -- Header File for lists.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qcons;
extern Object Qeq;
extern Object Qequal;
extern Object Qfloat;
extern Object Kinitial_element;
extern Object Qinteger;
extern Object Qnumber;
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

extern Object activate_subclass_of_entity_for_g2_list(Object);
extern Object add_class_to_environment(int,...);
extern Object add_to_list_elements_for_item(Object,Object);
extern Object alias_slot_name(int,...);
extern Object align_blocks(Object,Object);
extern Object ancestor_p(Object,Object);
extern Object back_off(void);
extern Object block_can_be_dependent_p(Object);
extern Object blocks_transferable_p(Object);
extern Object bytes_per_typed_simple_array(Object,Object);
extern Object check_if_superior_classes_are_defined(Object,Object);
extern Object clear_duplicates_check_hash_table(Object);
extern Object clear_duplicates_check_hash_table_tree(Object);
extern Object clear_g2_list(Object);
extern Object clear_optimized_constants(void);
extern Object clone_connections_for_block(Object,Object,Object);
extern Object clone_frame(int,...);
extern Object collect_subclasses(Object);
extern Object convert_permanent_list_structure_for_saving(Object);
extern Object convert_saved_list_values_to_g2_list_structure(void);
extern Object copy_evaluation_value_1(Object);
extern Object copy_for_slot_value(Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_list_using_g2_list_conses_1(Object);
extern Object copy_tree_using_g2_list_conses_1(Object);
extern Object create_empty_g2_list_structure(void);
extern Object create_list_element(Object,Object);
extern Object datum_ok_for_g2_list_or_array_p(Object,Object);
extern Object deactivate_subclass_of_entity_for_g2_list(Object);
extern Object delete_connection_to_stub(Object);
extern Object delete_external_connections_of_blocks(Object);
extern Object delete_from_list_elements_for_item(int,...);
extern Object delete_g2_list(Object);
extern Object delete_g2_list_cons_1(Object,Object);
extern Object delete_g2_list_element_1(Object,Object);
extern Object distribute_blocks(Object,Object);
extern Object dragging_cons_1(Object,Object);
extern Object dragging_list_2(Object,Object);
extern Object duplicates_check_hash_table_hash_vector_50021_vector_memory_usage(void);
extern Object eval_cons_1(Object,Object);
extern Object evaluation_truth_value_true_p(Object);
extern Object evaluation_value_eq(Object,Object);
extern Object evaluation_value_of_type_p(Object,Object);
extern Object exceptional_float_p(Object);
extern Object find_exceptional_float_in_g2_list(Object,Object);
extern Object find_frame_for_denotation(int,...);
extern Object find_g2_list_element_structure(Object,Object,Object,Object);
extern Object find_g2_list_element_structure_at_position(Object,Object);
extern Object flatten_binary_tree(Object);
extern Object flatten_duplicates_check_hash_table(Object);
extern Object g2_align_list_contents(Object,Object);
extern Object g2_clone_list_contents(Object,Object,Object,Object);
extern Object g2_distribute_list_contents(Object,Object);
extern Object g2_items_in_area(Object,Object,Object,Object,Object,Object);
extern Object g2_list_cons_1(Object,Object);
extern Object g2_list_cons_memory_usage(void);
extern Object g2_list_elements(int,...);
extern Object g2_list_empty_p(Object);
extern Object g2_list_first(Object,Object,Object);
extern Object g2_list_insert_after(Object,Object,Object,Object);
extern Object g2_list_insert_at_beginning(Object,Object);
extern Object g2_list_insert_at_end(int,...);
extern Object g2_list_insert_before(Object,Object,Object,Object);
extern Object g2_list_last(Object,Object,Object);
extern Object g2_list_length(Object);
extern Object g2_list_list_2(Object,Object);
extern Object g2_list_list_3(Object,Object,Object);
extern Object g2_list_list_4(Object,Object,Object,Object);
extern Object g2_list_list_trace_hook(Object);
extern Object g2_list_member_p(Object,Object);
extern Object g2_list_next_to_last(Object,Object,Object);
extern Object g2_list_or_array_class_element_type(Object,Object);
extern Object g2_list_or_array_class_for_element_type(Object,Object);
extern Object g2_list_or_array_datum_subtype_p(Object,Object);
extern Object g2_list_or_array_element_ok_p(Object,Object);
extern Object g2_list_or_array_element_type(Object);
extern Object g2_list_or_array_element_type_may_contain_item_p(Object);
extern Object g2_list_or_array_item_subtype_p(Object,Object);
extern Object g2_list_or_array_type_ok_p(Object,Object,Object);
extern Object g2_list_remove(Object,Object,Object);
extern Object g2_list_remove_first(int,...);
extern Object g2_list_remove_last(int,...);
extern Object g2_list_second(Object,Object,Object);
extern Object g2_list_structure_clear(Object);
extern Object g2_list_structure_delete(int,...);
extern Object g2_list_structure_insert_element_after(Object,Object,Object);
extern Object g2_list_structure_insert_element_before(Object,Object,Object);
extern Object g2_list_structure_next(Object,Object);
extern Object g2_list_structure_previous(Object,Object);
extern Object g2_list_structure_push_left(Object,Object,Object);
extern Object g2_list_structure_push_right(Object,Object,Object);
extern Object g2_move_list_contents(int,...);
extern Object g2_transfer_list_contents(int,...);
extern Object gensym_cons_1(Object,Object);
extern Object get_block_at_other_end_of_connection(Object,Object);
extern Object get_blocks_valid_for_group_operation(Object);
extern Object get_list_contents_as_sequence(Object);
extern Object get_lookup_slot_value(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_module_block_is_in(Object);
extern Object get_primary_name_for_frame_if_any(Object);
extern Object get_workspace_if_any(Object);
extern Object getfq_function_no_default(Object,Object);
extern Object help_insert_list_node(Object,Object);
extern Object in_order_p(Object);
extern Object item_currently_contains_compiled_value(Object);
extern Object item_ok_for_g2_list_or_array_p(Object,Object);
extern Object item_uuid(Object);
extern Object list_blocks_within_area_of_workspace(Object,Object,Object,Object,Object,Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_duplicates_check_hash_table(void);
extern Object make_duplicates_check_hash_table_hash_vector(void);
extern Object make_g2_list_list_1(Object);
extern Object make_permanent_duplicates_check_hash_table_hash_vector_50021_vector_internal(void);
extern Object make_symbol_properties_hash_table_skip_list_sentinel(Object,Object);
extern Object make_thread_array(Object);
extern Object make_transient_item(Object);
extern Object map_to_image_plane(Object,Object);
extern Object map_to_image_plane_or_stack_error(Object,Object);
extern Object memq_function(Object,Object);
extern Object move_blocks_with_their_external_connections(Object,Object,Object,Object);
extern Object move_items_to_mouse_of_window(Object,Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object note_change_to_block_1(Object,Object);
extern Object note_change_to_runtime_data_for_block_1(Object);
extern Object nth_from_end_g2_list_element(Object,Object,Object,Object);
extern Object nth_g2_list_element(Object,Object,Object,Object);
extern Object nth_g2_list_item_or_evaluation_value(Object,Object,Object);
extern Object out_duplicates_check_hash_table_hash_vector_50021_vectors(void);
extern Object outstanding_g2_list_conses(void);
extern Object pop_g2_list(Object);
extern Object preflight_check_dragging_list_of_blocks_for_transfer(int,...);
extern Object push_optimized_constant(Object);
extern Object put_insert_duplicate_elements_qm(Object,Object,Object);
extern Object put_list_type(Object,Object,Object);
extern Object raw_stack_error_named_error(Object,Object);
extern Object read_element_for_kb(Object);
extern Object read_g2_list_or_array_element_for_kb(Object,Object);
extern Object read_list_data(Object);
extern Object reclaim_binary_tree_element_1(Object);
extern Object reclaim_dragging_list_1(Object);
extern Object reclaim_duplicates_check_hash_table(Object);
extern Object reclaim_duplicates_check_hash_table_hash_vector(Object);
extern Object reclaim_duplicates_check_hash_table_tree_for_hash_leaves(Object);
extern Object reclaim_eval_list_function(Object);
extern Object reclaim_evaluation_sequence(Object);
extern Object reclaim_evaluation_value(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_g2_list_cons_1(Object);
extern Object reclaim_g2_list_list_1(Object);
extern Object reclaim_g2_list_list_star_1(Object);
extern Object reclaim_g2_list_tree_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_if_evaluation_value_1(Object);
extern Object reclaim_list_structure_value(Object,Object);
extern Object reclaim_slot_value(Object);
extern Object reclaim_slot_value_tree_1(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object release_list_node(Object);
extern Object remove_element_from_all_g2_lists(Object,Object);
extern Object remove_g2_list_duplicate_elements(Object);
extern Object remove_g2_list_element_structure(Object,Object,Object,Object,Object);
extern Object replenish_g2_list_cons_pool(void);
extern Object replenish_g2_list_list_pool(Object);
extern Object replenish_lookup_cons_pool(void);
extern Object replenish_vector_pool_cons_pool(void);
extern Object required_datum_type_ok_for_g2_list_or_array_p(Object,Object,Object);
extern Object required_item_type_ok_for_g2_list_or_array_p(Object,Object,Object);
extern Object reverse_list_using_dragging_conses(Object);
extern Object scope_cons(Object,Object);
extern Object send_ws_representations_item_insert_as_subblock(Object,Object,Object);
extern Object send_ws_representations_item_moved(Object,Object,Object);
extern Object set_balanced_binary_tree_entry(Object,Object,Object,Object,Object,Object,Object);
extern Object set_neither_permanent_nor_transient_and_propagate(Object,Object);
extern Object set_skip_list_entry(Object,Object,Object,Object,Object,Object,Object,Object);
extern Object shift_blocks_with_their_external_connections(int,...);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object sxhashw(Object);
extern Object symbolic_type_specification_subtype_p(Object,Object);
extern Object tformat_stack_error_text_string(int,...);
extern Object transfer_items_to_mouse_of_window(int,...);
extern Object transfer_workspace_subblock(Object,Object,Object);
extern Object type_specification_for_user_or_datum_type(Object);
extern Object type_specification_subtype_p(Object,Object);
extern Object unsquirrel_list_data(Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object update_representations_of_slot_value(int,...);
extern Object update_subscriptions_for_add_item_to_workspace(Object,Object);
extern Object valid_datum_type_specification_p(Object);
extern Object validate_all_item_lists(Object,Object);
extern Object validate_and_fix_g2_item_list_elements(Object);
extern Object validate_item_or_evaluation_value(Object,Object,Object);
extern Object write_char_for_kb(Object);
extern Object write_element_for_kb(Object);
extern Object write_evaluation_value_for_kb(Object);
extern Object write_fixnum_for_kb(Object);
extern Object write_g2_list_data_for_kb(Object);
extern Object write_g2_list_or_array_element_for_kb(Object,Object);

#else

extern Object activate_subclass_of_entity_for_g2_list();
extern Object add_class_to_environment();
extern Object add_to_list_elements_for_item();
extern Object alias_slot_name();
extern Object align_blocks();
extern Object ancestor_p();
extern Object back_off();
extern Object block_can_be_dependent_p();
extern Object blocks_transferable_p();
extern Object bytes_per_typed_simple_array();
extern Object check_if_superior_classes_are_defined();
extern Object clear_duplicates_check_hash_table();
extern Object clear_duplicates_check_hash_table_tree();
extern Object clear_g2_list();
extern Object clear_optimized_constants();
extern Object clone_connections_for_block();
extern Object clone_frame();
extern Object collect_subclasses();
extern Object convert_permanent_list_structure_for_saving();
extern Object convert_saved_list_values_to_g2_list_structure();
extern Object copy_evaluation_value_1();
extern Object copy_for_slot_value();
extern Object copy_frame_serial_number();
extern Object copy_list_using_g2_list_conses_1();
extern Object copy_tree_using_g2_list_conses_1();
extern Object create_empty_g2_list_structure();
extern Object create_list_element();
extern Object datum_ok_for_g2_list_or_array_p();
extern Object deactivate_subclass_of_entity_for_g2_list();
extern Object delete_connection_to_stub();
extern Object delete_external_connections_of_blocks();
extern Object delete_from_list_elements_for_item();
extern Object delete_g2_list();
extern Object delete_g2_list_cons_1();
extern Object delete_g2_list_element_1();
extern Object distribute_blocks();
extern Object dragging_cons_1();
extern Object dragging_list_2();
extern Object duplicates_check_hash_table_hash_vector_50021_vector_memory_usage();
extern Object eval_cons_1();
extern Object evaluation_truth_value_true_p();
extern Object evaluation_value_eq();
extern Object evaluation_value_of_type_p();
extern Object exceptional_float_p();
extern Object find_exceptional_float_in_g2_list();
extern Object find_frame_for_denotation();
extern Object find_g2_list_element_structure();
extern Object find_g2_list_element_structure_at_position();
extern Object flatten_binary_tree();
extern Object flatten_duplicates_check_hash_table();
extern Object g2_align_list_contents();
extern Object g2_clone_list_contents();
extern Object g2_distribute_list_contents();
extern Object g2_items_in_area();
extern Object g2_list_cons_1();
extern Object g2_list_cons_memory_usage();
extern Object g2_list_elements();
extern Object g2_list_empty_p();
extern Object g2_list_first();
extern Object g2_list_insert_after();
extern Object g2_list_insert_at_beginning();
extern Object g2_list_insert_at_end();
extern Object g2_list_insert_before();
extern Object g2_list_last();
extern Object g2_list_length();
extern Object g2_list_list_2();
extern Object g2_list_list_3();
extern Object g2_list_list_4();
extern Object g2_list_list_trace_hook();
extern Object g2_list_member_p();
extern Object g2_list_next_to_last();
extern Object g2_list_or_array_class_element_type();
extern Object g2_list_or_array_class_for_element_type();
extern Object g2_list_or_array_datum_subtype_p();
extern Object g2_list_or_array_element_ok_p();
extern Object g2_list_or_array_element_type();
extern Object g2_list_or_array_element_type_may_contain_item_p();
extern Object g2_list_or_array_item_subtype_p();
extern Object g2_list_or_array_type_ok_p();
extern Object g2_list_remove();
extern Object g2_list_remove_first();
extern Object g2_list_remove_last();
extern Object g2_list_second();
extern Object g2_list_structure_clear();
extern Object g2_list_structure_delete();
extern Object g2_list_structure_insert_element_after();
extern Object g2_list_structure_insert_element_before();
extern Object g2_list_structure_next();
extern Object g2_list_structure_previous();
extern Object g2_list_structure_push_left();
extern Object g2_list_structure_push_right();
extern Object g2_move_list_contents();
extern Object g2_transfer_list_contents();
extern Object gensym_cons_1();
extern Object get_block_at_other_end_of_connection();
extern Object get_blocks_valid_for_group_operation();
extern Object get_list_contents_as_sequence();
extern Object get_lookup_slot_value();
extern Object get_lookup_slot_value_given_default();
extern Object get_module_block_is_in();
extern Object get_primary_name_for_frame_if_any();
extern Object get_workspace_if_any();
extern Object getfq_function_no_default();
extern Object help_insert_list_node();
extern Object in_order_p();
extern Object item_currently_contains_compiled_value();
extern Object item_ok_for_g2_list_or_array_p();
extern Object item_uuid();
extern Object list_blocks_within_area_of_workspace();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_duplicates_check_hash_table();
extern Object make_duplicates_check_hash_table_hash_vector();
extern Object make_g2_list_list_1();
extern Object make_permanent_duplicates_check_hash_table_hash_vector_50021_vector_internal();
extern Object make_symbol_properties_hash_table_skip_list_sentinel();
extern Object make_thread_array();
extern Object make_transient_item();
extern Object map_to_image_plane();
extern Object map_to_image_plane_or_stack_error();
extern Object memq_function();
extern Object move_blocks_with_their_external_connections();
extern Object move_items_to_mouse_of_window();
extern Object mutate_global_property();
extern Object note_change_to_block_1();
extern Object note_change_to_runtime_data_for_block_1();
extern Object nth_from_end_g2_list_element();
extern Object nth_g2_list_element();
extern Object nth_g2_list_item_or_evaluation_value();
extern Object out_duplicates_check_hash_table_hash_vector_50021_vectors();
extern Object outstanding_g2_list_conses();
extern Object pop_g2_list();
extern Object preflight_check_dragging_list_of_blocks_for_transfer();
extern Object push_optimized_constant();
extern Object put_insert_duplicate_elements_qm();
extern Object put_list_type();
extern Object raw_stack_error_named_error();
extern Object read_element_for_kb();
extern Object read_g2_list_or_array_element_for_kb();
extern Object read_list_data();
extern Object reclaim_binary_tree_element_1();
extern Object reclaim_dragging_list_1();
extern Object reclaim_duplicates_check_hash_table();
extern Object reclaim_duplicates_check_hash_table_hash_vector();
extern Object reclaim_duplicates_check_hash_table_tree_for_hash_leaves();
extern Object reclaim_eval_list_function();
extern Object reclaim_evaluation_sequence();
extern Object reclaim_evaluation_value();
extern Object reclaim_frame_serial_number();
extern Object reclaim_g2_list_cons_1();
extern Object reclaim_g2_list_list_1();
extern Object reclaim_g2_list_list_star_1();
extern Object reclaim_g2_list_tree_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_if_evaluation_value_1();
extern Object reclaim_list_structure_value();
extern Object reclaim_slot_value();
extern Object reclaim_slot_value_tree_1();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object release_list_node();
extern Object remove_element_from_all_g2_lists();
extern Object remove_g2_list_duplicate_elements();
extern Object remove_g2_list_element_structure();
extern Object replenish_g2_list_cons_pool();
extern Object replenish_g2_list_list_pool();
extern Object replenish_lookup_cons_pool();
extern Object replenish_vector_pool_cons_pool();
extern Object required_datum_type_ok_for_g2_list_or_array_p();
extern Object required_item_type_ok_for_g2_list_or_array_p();
extern Object reverse_list_using_dragging_conses();
extern Object scope_cons();
extern Object send_ws_representations_item_insert_as_subblock();
extern Object send_ws_representations_item_moved();
extern Object set_balanced_binary_tree_entry();
extern Object set_neither_permanent_nor_transient_and_propagate();
extern Object set_skip_list_entry();
extern Object shift_blocks_with_their_external_connections();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object sxhashw();
extern Object symbolic_type_specification_subtype_p();
extern Object tformat_stack_error_text_string();
extern Object transfer_items_to_mouse_of_window();
extern Object transfer_workspace_subblock();
extern Object type_specification_for_user_or_datum_type();
extern Object type_specification_subtype_p();
extern Object unsquirrel_list_data();
extern Object update_object_pool_meters_list();
extern Object update_representations_of_slot_value();
extern Object update_subscriptions_for_add_item_to_workspace();
extern Object valid_datum_type_specification_p();
extern Object validate_all_item_lists();
extern Object validate_and_fix_g2_item_list_elements();
extern Object validate_item_or_evaluation_value();
extern Object write_char_for_kb();
extern Object write_element_for_kb();
extern Object write_evaluation_value_for_kb();
extern Object write_fixnum_for_kb();
extern Object write_g2_list_data_for_kb();
extern Object write_g2_list_or_array_element_for_kb();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Align_selection_command_operations, Qalign_selection_command_operations);
DECLARE_VARIABLE_WITH_SYMBOL(Available_duplicates_check_hash_table_hash_vector_50021_vectors, Qavailable_duplicates_check_hash_table_hash_vector_50021_vectors);
extern Object Available_duplicates_check_hash_table_hash_vector_50021_vectors_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Available_g2_list_conses, Qavailable_g2_list_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_g2_list_conses_tail, Qavailable_g2_list_conses_tail);
extern Object Available_g2_list_conses_tail_vector;
extern Object Available_g2_list_conses_vector;
extern Object Available_lookup_conses_tail_vector;
extern Object Available_lookup_conses_vector;
extern Object Available_vector_pool_conses_tail_vector;
extern Object Available_vector_pool_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backoff_limit, Qbackoff_limit);
extern Object Backoff_min_delay;
extern Object Bytes_per_rtl_ptr;
DECLARE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);
extern Object Chain_of_available_g2_list_elements_vector;
extern Object Class_description_gkbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Connection_class_description, Qconnection_class_description);
extern Object Cons_pool_conses_to_make_at_a_time;
DECLARE_VARIABLE_WITH_SYMBOL(Count_of_duplicates_check_hash_table_hash_vector_50021_vectors, Qcount_of_duplicates_check_hash_table_hash_vector_50021_vectors);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_save, Qcurrent_kb_save);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_specific_property_list_property_name, Qcurrent_kb_specific_property_list_property_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_saving_context, Qcurrent_saving_context);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Datum_type, Qdatum_type);
DECLARE_VARIABLE_WITH_SYMBOL(Defined_evaluation_value_types, Qdefined_evaluation_value_types);
DECLARE_VARIABLE_WITH_SYMBOL(Distribute_selection_command_operations, Qdistribute_selection_command_operations);
DECLARE_VARIABLE_WITH_SYMBOL(Duplicates_check_hash, Qduplicates_check_hash);
extern Object Evaluation_false_value;
extern Object Evaluation_true_value;
#define Falsity FIX((SI_Long)-1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Float_array_class_description, Qfloat_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Float_list_class_description, Qfloat_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_array_class_description, Qg2_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_has_v5_mode_windows_p, Qg2_has_v5_mode_windows_p);
DECLARE_VARIABLE_WITH_SYMBOL(G2_list_class_description, Qg2_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(G2_list_cons_counter, Qg2_list_cons_counter);
extern Object G2_list_cons_counter_vector;
extern Object G2_list_structure_marker;
DECLARE_VARIABLE_WITH_SYMBOL(G2_window_class_description, Qg2_window_class_description);
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Integer_array_class_description, Qinteger_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Integer_list_class_description, Qinteger_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Item_array_class_description, Qitem_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Item_list_class_description, Qitem_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Junction_blocks_not_to_be_deleted, Qjunction_blocks_not_to_be_deleted);
DECLARE_VARIABLE_WITH_SYMBOL(Kb_workspace_class_description, Qkb_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Left_braket_written_qm, Qleft_braket_written_qm);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_once_only_switched_post_loading_functions, Qlist_of_once_only_switched_post_loading_functions);
DECLARE_VARIABLE_WITH_SYMBOL(List_of_switched_and_module_post_loading_functions, Qlist_of_switched_and_module_post_loading_functions);
DECLARE_VARIABLE_WITH_SYMBOL(Loose_end_class_description, Qloose_end_class_description);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
extern Object No_specific_property_value;
DECLARE_VARIABLE_WITH_SYMBOL(Non_kb_workspace_class_description, Qnon_kb_workspace_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Partition_float_union, Qpartition_float_union);
DECLARE_VARIABLE_WITH_SYMBOL(Quantity_array_class_description, Qquantity_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Quantity_list_class_description, Qquantity_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Saved_position_or_next_lower_thing, Qsaved_position_or_next_lower_thing);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Symbol_array_class_description, Qsymbol_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Symbol_list_class_description, Qsymbol_list_class_description);
extern Object Symbol_properties_table;
DECLARE_VARIABLE_WITH_SYMBOL(Text_array_class_description, Qtext_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Text_list_class_description, Qtext_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Transfer_in_progress, Qtransfer_in_progress);
#define Truth FIX((SI_Long)1000L)
DECLARE_VARIABLE_WITH_SYMBOL(Truth_value_array_class_description, Qtruth_value_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Truth_value_list_class_description, Qtruth_value_list_class_description);
extern Object Type_specification_for_item;
DECLARE_VARIABLE_WITH_SYMBOL(Value_array_class_description, Qvalue_array_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Value_list_class_description, Qvalue_list_class_description);
DECLARE_VARIABLE_WITH_SYMBOL(Warmbooting_qm, Qwarmbooting_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Workspace_class_description, Qworkspace_class_description);
