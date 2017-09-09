/* wrmbt.h -- Header File for wrmbt.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qblock;
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

extern Object collect_subclasses(Object);
extern Object complete_warmbooting_after_system_start(Object);
extern Object convert_text_string_to_text(Object);
extern Object copy_constant_wide_string_given_length(Object,Object);
extern Object copy_frame_serial_number(Object);
extern Object copy_gensym_pathname(Object);
extern Object delete_blocks_after_unsquirreling(void);
extern Object delete_frame(Object);
extern Object error_text_p(Object);
extern Object finish_warmbooting(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object get_instance_with_name_if_any(Object,Object);
extern Object get_lookup_slot_value_given_default(Object,Object,Object);
extern Object get_slot_description_of_class_description_function(Object,Object,Object);
extern Object lookup_global_or_kb_specific_property_value(Object,Object);
extern Object lookup_kb_specific_property_value(Object,Object);
extern Object parse_text_for_slot(int,...);
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
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object runnable_p_function(Object);
extern Object schedule_all_cyclic_rules(void);
extern Object set_non_savable_lookup_slot_value(Object,Object,Object);
extern Object simulate_until_consistent_with_gensym_time(void);
extern Object squirrel_away_data_in_block(int,...);
extern Object start_procedure_invocation_in_place(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object system_start(void);
extern Object unsquirrel_data_for_block(Object);
extern Object update_all_indexed_attribute_hash_tables(void);
extern Object warmboot_kb(int,...);

#else

extern Object collect_subclasses();
extern Object complete_warmbooting_after_system_start();
extern Object convert_text_string_to_text();
extern Object copy_constant_wide_string_given_length();
extern Object copy_frame_serial_number();
extern Object copy_gensym_pathname();
extern Object delete_blocks_after_unsquirreling();
extern Object delete_frame();
extern Object error_text_p();
extern Object finish_warmbooting();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object get_instance_with_name_if_any();
extern Object get_lookup_slot_value_given_default();
extern Object get_slot_description_of_class_description_function();
extern Object lookup_global_or_kb_specific_property_value();
extern Object lookup_kb_specific_property_value();
extern Object parse_text_for_slot();
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
extern Object record_system_variable();
extern Object runnable_p_function();
extern Object schedule_all_cyclic_rules();
extern Object set_non_savable_lookup_slot_value();
extern Object simulate_until_consistent_with_gensym_time();
extern Object squirrel_away_data_in_block();
extern Object start_procedure_invocation_in_place();
extern Object system_start();
extern Object unsquirrel_data_for_block();
extern Object update_all_indexed_attribute_hash_tables();
extern Object warmboot_kb();

#endif

/* variables/constants */
extern Object Backtrace_stack_for_internal_error;
extern Object Blocks_to_delete_after_unsquirreling;
extern Object Class_description_gkbprop;
extern Object Create_frames_and_connections_reading_past_qm;
extern Object Current_computation_component_particulars;
extern Object Current_computation_frame;
extern Object Current_frame_serial_number;
extern Object Current_kb_pathname_qm;
extern Object Index_of_top_of_backtrace_stack;
extern Object Initialization_inhibit;
extern Object Instances_specific_to_this_class_kbprop;
extern Object Kb_flags;
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
extern Object No_value;
extern Object Read_kb_buffer;
extern Object Read_kb_buffer_index;
extern Object Read_kb_buffer_length;
extern Object Scope_conses;
extern Object Simulation_no_value;
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
extern Object Some_time_ago;
extern Object System_is_running;
extern Object Timing_parameters;
extern Object Warmbooting_qm;
extern Object Warmbooting_with_catch_up_qm;
