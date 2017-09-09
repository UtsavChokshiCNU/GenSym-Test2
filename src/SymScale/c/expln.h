/* expln.h -- Header File for expln.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qunsigned_byte;

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

extern Object add_to_workspace(int,...);
extern Object allocate_byte_vector_16(Object);
extern Object backward_chaining_display_children(Object,Object);
extern Object backward_chaining_display_hash(Object);
extern Object backward_chaining_display_short_rep(Object);
extern Object backward_chaining_display_structure_memory_usage(void);
extern Object backward_chaining_displays_of_variable(Object);
extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object collect_all_rules_for_forward_chaining(Object);
extern Object collect_generic_formulas_for_variable(Object);
extern Object collect_rules_for_backward_chaining(Object,Object);
extern Object connect_superior_and_kid_frames(Object,Object,Object,Object,Object,Object);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object copy_out_current_wide_string(void);
extern Object delete_backward_chaining_display(Object);
extern Object delete_backward_chaining_display_if_any_for_variable(Object);
extern Object delete_frame(Object);
extern Object delete_gensym_element_1(Object,Object);
extern Object describe_backward_chaining_short_reps(Object);
extern Object describe_forward_chaining_short_reps(Object);
extern Object direct_structure_method(Object,Object);
extern Object eval_cons_1(Object,Object);
extern Object force_process_drawing(void);
extern Object gensym_cons_1(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object graph_frame_hierarchy_function(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_attributes_table(int,...);
extern Object make_backward_chaining_display(Object);
extern Object make_explanation_table(int,...);
extern Object make_permanent_backward_chaining_display_structure_internal(void);
extern Object make_raw_backward_chaining_display_1(Object);
extern Object make_short_representation(int,...);
extern Object make_static_chaining_display(Object);
extern Object make_thread_array(Object);
extern Object make_workspace(int,...);
extern Object memq_function(Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object outstanding_backward_chaining_display_count(void);
extern Object print_var_spot_for_stack_using_name_and_description(int,...);
extern Object proc_list_2(Object,Object);
extern Object push_optimized_constant(Object);
extern Object put_workspace_on_pane_function(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object reclaim_backward_chaining_display_1(Object);
extern Object reclaim_eval_list_1(Object);
extern Object reclaim_eval_tree_1(Object);
extern Object reclaim_graph_display_1(Object);
extern Object reclaim_proc_list_1(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object remove_backward_chaining_display(Object);
extern Object represented_in_graph_display_p(Object,Object);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object static_display_maximum_height(Object);
extern Object static_display_total_width(Object,Object);
extern Object tformat(int,...);
extern Object type_specification_of_variable_or_parameter_value(Object);
extern Object update_backward_chaining_displays_function(Object);
extern Object update_graph_display(Object);
extern Object update_object_pool_meters_list(Object);
extern Object var_count(Object);
extern Object warn_of_undefined_data_server(Object,Object);
extern Object write_stored_value(Object);

#else

extern Object add_to_workspace();
extern Object allocate_byte_vector_16();
extern Object backward_chaining_display_children();
extern Object backward_chaining_display_hash();
extern Object backward_chaining_display_short_rep();
extern Object backward_chaining_display_structure_memory_usage();
extern Object backward_chaining_displays_of_variable();
extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object collect_all_rules_for_forward_chaining();
extern Object collect_generic_formulas_for_variable();
extern Object collect_rules_for_backward_chaining();
extern Object connect_superior_and_kid_frames();
extern Object copy_constant_wide_string_given_length();
extern Object copy_out_current_wide_string();
extern Object delete_backward_chaining_display();
extern Object delete_backward_chaining_display_if_any_for_variable();
extern Object delete_frame();
extern Object delete_gensym_element_1();
extern Object describe_backward_chaining_short_reps();
extern Object describe_forward_chaining_short_reps();
extern Object direct_structure_method();
extern Object eval_cons_1();
extern Object force_process_drawing();
extern Object gensym_cons_1();
extern Object get_lookup_slot_value_given_default();
extern Object graph_frame_hierarchy_function();
extern Object load_and_initialize_type_description();
extern Object lookup_kb_specific_property_value();
extern Object make_attributes_table();
extern Object make_backward_chaining_display();
extern Object make_explanation_table();
extern Object make_permanent_backward_chaining_display_structure_internal();
extern Object make_raw_backward_chaining_display_1();
extern Object make_short_representation();
extern Object make_static_chaining_display();
extern Object make_thread_array();
extern Object make_workspace();
extern Object memq_function();
extern Object mutate_global_property();
extern Object outstanding_backward_chaining_display_count();
extern Object print_var_spot_for_stack_using_name_and_description();
extern Object proc_list_2();
extern Object push_optimized_constant();
extern Object put_workspace_on_pane_function();
extern Object reclaim_backward_chaining_display_1();
extern Object reclaim_eval_list_1();
extern Object reclaim_eval_tree_1();
extern Object reclaim_graph_display_1();
extern Object reclaim_proc_list_1();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object remove_backward_chaining_display();
extern Object represented_in_graph_display_p();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object static_display_maximum_height();
extern Object static_display_total_width();
extern Object tformat();
extern Object type_specification_of_variable_or_parameter_value();
extern Object update_backward_chaining_displays_function();
extern Object update_graph_display();
extern Object update_object_pool_meters_list();
extern Object var_count();
extern Object warn_of_undefined_data_server();
extern Object write_stored_value();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Backward_chaining_display_count, Qbackward_chaining_display_count);
DECLARE_VARIABLE_WITH_SYMBOL(Backward_chaining_displays, Qbackward_chaining_displays);
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_backward_chaining_displays, Qchain_of_available_backward_chaining_displays);
extern Object Chain_of_available_backward_chaining_displays_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_twriting_output_type, Qcurrent_twriting_output_type);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string, Qcurrent_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Current_wide_string_list, Qcurrent_wide_string_list);
DECLARE_VARIABLE_WITH_SYMBOL(Current_workstation_detail_pane, Qcurrent_workstation_detail_pane);
extern Object Data_server_or_alias_qm_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Debugging_parameters, Qdebugging_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Fill_pointer_for_current_wide_string, Qfill_pointer_for_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Links_and_objects, Qlinks_and_objects);
#define Managed_array_index_offset FIX((SI_Long)2L)
extern Object Maximum_in_place_array_size;
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
extern Object The_type_description_of_backward_chaining_display;
DECLARE_VARIABLE_WITH_SYMBOL(Total_length_of_current_wide_string, Qtotal_length_of_current_wide_string);
DECLARE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);
