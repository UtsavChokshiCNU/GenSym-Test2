/* wrmbt.h -- Header File for wrmbt.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
extern Object Qcons;
extern Object Qgentemp;
extern Object Qlist;
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

extern Object clear_optimized_constants(void);
extern Object collect_subclasses(Object);
extern Object complete_warmbooting_after_system_start(Object);
extern Object convert_text_string_to_text(Object);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_gensym_pathname(Object);
extern Object copy_list_using_warmboot_conses_1(Object);
extern Object copy_tree_using_warmboot_conses_1(Object);
extern Object delete_blocks_after_unsquirreling(void);
extern Object delete_frame(Object);
extern Object delete_warmboot_cons_1(Object,Object);
extern Object delete_warmboot_element_1(Object,Object);
extern Object error_text_p(Object);
extern Object finish_warmbooting(Object);
extern Object get_instance_with_name_if_any(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object make_warmboot_list_1(Object);
extern Object outstanding_warmboot_conses(void);
extern Object parse_text_for_slot(int,...);
extern Object push_optimized_constant(Object);
extern Object read_array_data(Object);
extern Object read_element_for_kb(Object);
extern Object read_element_for_kb_with_temporary_floats(Object);
extern Object read_hash_table_data(Object);
extern Object read_history_buffer_and_location_for_block(void);
extern Object read_history_buffer_for_block(int,...);
extern Object read_kb(Object,Object,Object,Object,Object,Object,Object);
extern Object read_list_data(Object);
extern Object read_next_char_for_kb_from_refilled_buffer(void);
extern Object read_past_element_for_kb(Object);
extern Object read_past_history_buffer_and_location_for_block(Object);
extern Object read_past_history_buffer_for_block(Object);
extern Object read_past_runtime_data_for_block(Object);
extern Object read_runtime_data_for_block(Object);
extern Object reclaim_frame_serial_number(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_pathname(Object);
extern Object reclaim_warmboot_cons_1(Object);
extern Object reclaim_warmboot_list_1(Object);
extern Object reclaim_warmboot_list_star_1(Object);
extern Object reclaim_warmboot_tree_1(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object replenish_warmboot_cons_pool(void);
extern Object replenish_warmboot_list_pool(Object);
extern Object runnable_p_function(Object);
extern Object schedule_all_cyclic_rules(void);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object simulate_until_consistent_with_gensym_time(void);
extern Object slot_value_cons_1(Object,Object);
extern Object slot_value_list_2(Object,Object);
extern Object squirrel_away_data_in_block(int,...);
extern Object start_procedure_invocation_in_place(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object system_start(void);
extern Object unsquirrel_data_for_block(Object);
extern Object update_all_indexed_attribute_hash_tables(void);
extern Object update_object_pool_meters_list(Object);
extern Object warmboot_cons_1(Object,Object);
extern Object warmboot_cons_memory_usage(void);
extern Object warmboot_kb(int,...);
extern Object warmboot_list_2(Object,Object);
extern Object warmboot_list_3(Object,Object,Object);
extern Object warmboot_list_4(Object,Object,Object,Object);
extern Object warmboot_list_trace_hook(Object);

#else

extern Object clear_optimized_constants();
extern Object collect_subclasses();
extern Object complete_warmbooting_after_system_start();
extern Object convert_text_string_to_text();
extern Object copy_constant_wide_string_given_length();
extern Object copy_frame_serial_number();
extern Object copy_gensym_pathname();
extern Object copy_list_using_warmboot_conses_1();
extern Object copy_tree_using_warmboot_conses_1();
extern Object delete_blocks_after_unsquirreling();
extern Object delete_frame();
extern Object delete_warmboot_cons_1();
extern Object delete_warmboot_element_1();
extern Object error_text_p();
extern Object finish_warmbooting();
extern Object get_instance_with_name_if_any();
extern Object get_lookup_slot_value_given_default();
extern Object get_slot_description_of_class_description_function();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object make_warmboot_list_1();
extern Object outstanding_warmboot_conses();
extern Object parse_text_for_slot();
extern Object push_optimized_constant();
extern Object read_array_data();
extern Object read_element_for_kb();
extern Object read_element_for_kb_with_temporary_floats();
extern Object read_hash_table_data();
extern Object read_history_buffer_and_location_for_block();
extern Object read_history_buffer_for_block();
extern Object read_kb();
extern Object read_list_data();
extern Object read_next_char_for_kb_from_refilled_buffer();
extern Object read_past_element_for_kb();
extern Object read_past_history_buffer_and_location_for_block();
extern Object read_past_history_buffer_for_block();
extern Object read_past_runtime_data_for_block();
extern Object read_runtime_data_for_block();
extern Object reclaim_frame_serial_number();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_pathname();
extern Object reclaim_warmboot_cons_1();
extern Object reclaim_warmboot_list_1();
extern Object reclaim_warmboot_list_star_1();
extern Object reclaim_warmboot_tree_1();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object replenish_warmboot_cons_pool();
extern Object replenish_warmboot_list_pool();
extern Object runnable_p_function();
extern Object schedule_all_cyclic_rules();
extern Object set_non_savable_lookup_slot_value();
extern Object simulate_until_consistent_with_gensym_time();
extern Object slot_value_cons_1();
extern Object slot_value_list_2();
extern Object squirrel_away_data_in_block();
extern Object start_procedure_invocation_in_place();
extern Object system_start();
extern Object unsquirrel_data_for_block();
extern Object update_all_indexed_attribute_hash_tables();
extern Object update_object_pool_meters_list();
extern Object warmboot_cons_1();
extern Object warmboot_cons_memory_usage();
extern Object warmboot_kb();
extern Object warmboot_list_2();
extern Object warmboot_list_3();
extern Object warmboot_list_4();
extern Object warmboot_list_trace_hook();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Available_warmboot_conses, Qavailable_warmboot_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Available_warmboot_conses_tail, Qavailable_warmboot_conses_tail);
extern Object Available_warmboot_conses_tail_vector;
extern Object Available_warmboot_conses_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
DECLARE_VARIABLE_WITH_SYMBOL(Blocks_to_delete_after_unsquirreling, Qblocks_to_delete_after_unsquirreling);
extern Object Bytes_per_rtl_ptr;
extern Object Class_description_gkbprop;
extern Object Cons_pool_conses_to_make_at_a_time;
DECLARE_VARIABLE_WITH_SYMBOL(Create_frames_and_connections_reading_past_qm, Qcreate_frames_and_connections_reading_past_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_component_particulars, Qcurrent_computation_component_particulars);
DECLARE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);
DECLARE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number, Qcurrent_frame_serial_number);
DECLARE_VARIABLE_WITH_SYMBOL(Current_kb_pathname_qm, Qcurrent_kb_pathname_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
DECLARE_VARIABLE_WITH_SYMBOL(Initialization_inhibit, Qinitialization_inhibit);
extern Object Instances_specific_to_this_class_kbprop;
DECLARE_VARIABLE_WITH_SYMBOL(Kb_flags, Qkb_flags);
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
DECLARE_VARIABLE_WITH_SYMBOL(No_value, Qno_value);
DECLARE_VARIABLE_WITH_SYMBOL(Read_kb_buffer, Qread_kb_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Read_kb_buffer_index, Qread_kb_buffer_index);
DECLARE_VARIABLE_WITH_SYMBOL(Read_kb_buffer_length, Qread_kb_buffer_length);
DECLARE_VARIABLE_WITH_SYMBOL(Scope_conses, Qscope_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Simulation_no_value, Qsimulation_no_value);
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object Some_time_ago;
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
DECLARE_VARIABLE_WITH_SYMBOL(Timing_parameters, Qtiming_parameters);
DECLARE_VARIABLE_WITH_SYMBOL(Warmboot_cons_counter, Qwarmboot_cons_counter);
extern Object Warmboot_cons_counter_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Warmbooting_qm, Qwarmbooting_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Warmbooting_with_catch_up_qm, Qwarmbooting_with_catch_up_qm);
