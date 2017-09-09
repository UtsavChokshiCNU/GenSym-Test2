/* int3a.h -- Header File for int3a.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qcharacter;
extern Object Qerror;
extern Object Qfixnum;
extern Object Qinteger;
extern Object Qintern;
extern Object Qlist;
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

extern Object ab_assoc_equal(Object,Object);
extern Object add_icp_message_handler(Object,Object);
extern Object allocate_managed_long_box(void);
extern Object allocate_managed_simple_vector(Object);
extern Object assign_corresponding_icp_object_index(Object,Object,Object);
extern Object assign_index_in_index_space(Object);
extern Object assq_function(Object,Object);
extern Object bytes_per_simple_vector(Object);
extern Object clear_optimized_constants(void);
extern Object constant_queue_next(Object,Object);
extern Object constant_queue_pop_left(int,...);
extern Object constant_queue_push_right(Object,Object);
extern Object copy_illegal_gensym_string_without_bad_characters(Object);
extern Object copy_text_string(Object);
extern Object copy_tree_for_interned_list(Object);
extern Object copy_widestr_to_icpbuf(Object,Object,Object,Object,Object);
extern Object current_icp_read_task_resumable_p(void);
extern Object deassign_index_in_index_space(Object,Object);
extern Object direct_structure_method(Object,Object);
extern Object emit_icp_read_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object emit_icp_write_trace(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object end_icp_message_group(void);
extern Object enlarge_index_space(Object,Object);
extern Object enqueue_icp_write_task(Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object ensure_icp_write_callback(Object);
extern Object ensure_next_icp_message_series(void);
extern Object establish_new_object_index_for_interned_list(int,...);
extern Object establish_new_object_index_for_symbol(int,...);
extern Object export_text_string(int,...);
extern Object fixnum_length_in_icp_bytes(Object);
extern Object frame_serial_number_function(Object);
extern Object frame_serial_number_to_item_table(Object);
extern Object gensym_cons_1(Object,Object);
extern Object gensym_list_2(Object,Object);
extern Object gensym_string_length_in_icp_bytes(Object);
extern Object gensym_string_substring(Object,Object,Object);
extern Object gensym_string_to_wide_string(Object);
extern Object get_corresponding_icp_object(Object);
extern Object get_from_icp_port(Object,Object,Object);
extern Object get_from_icp_port_if_any(Object,Object,Object);
extern Object get_icp_object_index_for_interned_list(Object,Object);
extern Object get_icp_object_index_for_symbol(Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_icp_abort_icp_task(void);
extern Object handle_icp_abort_icp_task__body(Object);
extern Object handle_icp_add_to_list_of_symbols(void);
extern Object handle_icp_add_to_list_of_symbols__body(Object,Object,Object);
extern Object handle_icp_intern(void);
extern Object handle_icp_intern__body(Object,Object);
extern Object handle_icp_intern_keyword(void);
extern Object handle_icp_intern_keyword__body(Object,Object);
extern Object handle_icp_intern_list(void);
extern Object handle_icp_intern_list__body(Object,Object);
extern Object handle_icp_resume_icp_task(void);
extern Object handle_icp_resume_icp_task__body(Object,Object);
extern Object handle_icp_start_icp_task(void);
extern Object handle_icp_start_icp_task__body(Object,Object,Object);
extern Object handler_for_enlarge_corresponding_icp_object_index_space(Object,Object);
extern Object icp_connection_being_shutdown_qm(Object);
extern Object icp_connection_open_p(Object);
extern Object icp_cons_1(Object,Object);
extern Object icp_error_internal(Object,Object,Object,Object,Object);
extern Object icp_list_2(Object,Object);
extern Object icp_out_of_synch(int,...);
extern Object icp_read_task_priority_function(Object);
extern Object icp_read_task_structure_memory_usage(void);
extern Object icp_write_task_not_allowed_to_write_p(Object,Object);
extern Object icp_write_task_structure_memory_usage(void);
extern Object import_text_string(int,...);
extern Object info_for_write_icp_symbol_as_value_type(Object);
extern Object initialize_icp_object_type(Object,Object,Object,Object);
extern Object initialize_icp_object_type_compile(Object,Object,Object);
extern Object instantaneous_icp_reader_byte_count(void);
extern Object instantaneous_icp_writer_byte_count(void);
extern Object integer_length_in_icp_bytes(Object);
extern Object intern_list(Object);
extern Object intern_text_string(int,...);
extern Object intern_text_string_for_icp(Object,Object);
extern Object interned_list_cons(Object,Object);
extern Object interned_list_p_function(Object);
extern Object interned_list_structure_memory_usage(void);
extern Object item_index_space(Object);
extern Object kill_current_icp_read_task(void);
extern Object large_integer_length_in_icp_bytes(Object);
extern Object lengthw(Object);
extern Object load_and_initialize_type_description(Object,Object);
extern Object make_corresponding_icp_interned_list(Object);
extern Object make_corresponding_icp_symbol(Object);
extern Object make_empty_constant_queue(void);
extern Object make_icp_object_index_space(Object);
extern Object make_icp_read_task_1(Object);
extern Object make_icp_write_task_1(Object,Object,Object,Object,Object,Object,Object);
extern Object make_index_space_1(Object,Object);
extern Object make_interned_list_1(Object);
extern Object make_permanent_icp_read_task_structure_internal(void);
extern Object make_permanent_icp_write_task_structure_internal(void);
extern Object make_permanent_interned_list_structure_internal(void);
extern Object make_permanent_schedule_task_structure_internal(void);
extern Object make_permanent_symbol_tree_structure_internal(void);
extern Object make_resumable_icp_output_task_queue_vector(void);
extern Object make_symbol_tree_1(void);
extern Object make_thread_array(Object);
extern Object maybe_finish_current_icp_read_task(void);
extern Object memq_function(Object,Object);
extern Object mutate_gensym_plist(Object,Object,Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object mutate_icp_plist(Object,Object,Object);
extern Object notify_user(int,...);
extern Object obtain_long_enough_adjustable_gensym_string(Object);
extern Object obtain_simple_gensym_string(Object);
extern Object obtain_text_string(Object);
extern Object outstanding_icp_read_task_count(void);
extern Object outstanding_icp_write_task_count(void);
extern Object outstanding_interned_list_count(void);
extern Object outstanding_symbol_tree_count(void);
extern Object peek_icp_byte(void);
extern Object position_of_two_colons(Object);
extern Object push_optimized_constant(Object);
extern Object read_icp_boolean(void);
extern Object read_icp_byte(void);
extern Object read_icp_character(void);
extern Object read_icp_corresponding_object_index(void);
extern Object read_icp_filtered_text_string(void);
extern Object read_icp_fixnum(void);
extern Object read_icp_gensym_string(void);
extern Object read_icp_icp_task_resumable_p(void);
extern Object read_icp_icp_tree(void);
extern Object read_icp_improper_list(void);
extern Object read_icp_improper_list_element(void);
extern Object read_icp_integer(void);
extern Object read_icp_interned_list_as_value_type(void);
extern Object read_icp_large_integer(Object);
extern Object read_icp_list(void);
extern Object read_icp_list_element(void);
extern Object read_icp_list_of_integers_using_function(void);
extern Object read_icp_list_of_unsigned_integers_using_function(void);
extern Object read_icp_managed_double_float(void);
extern Object read_icp_managed_long(void);
extern Object read_icp_raw_gensym_string_using_function(void);
extern Object read_icp_suspend(void);
extern Object read_icp_symbol_as_value_type(void);
extern Object read_icp_text_string(void);
extern Object read_icp_unsigned_integer(void);
extern Object read_icp_unsigned_integer_qm(void);
extern Object read_icp_wide_string(void);
extern Object reclaim_constant_queue(Object);
extern Object reclaim_gensym_cons_1(Object);
extern Object reclaim_gensym_list_1(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_icp_list_1(Object);
extern Object reclaim_icp_list_element(Object);
extern Object reclaim_icp_object_map(Object,Object,Object);
extern Object reclaim_icp_object_map_for_interned_list(Object);
extern Object reclaim_icp_object_map_for_symbol(Object);
extern Object reclaim_icp_port_entry(Object,Object,Object,Object);
extern Object reclaim_icp_port_entry_for_interned_list(Object,Object);
extern Object reclaim_icp_port_entry_for_symbol(Object,Object);
extern Object reclaim_icp_read_task_1(Object);
extern Object reclaim_icp_tree_1(Object);
extern Object reclaim_icp_tree_value(Object);
extern Object reclaim_icp_write_task_1(Object);
extern Object reclaim_if_text_or_gensym_string_function(Object);
extern Object reclaim_interned_list_1(Object);
extern Object reclaim_managed_simple_float_array_of_length_1(Object);
extern Object reclaim_managed_simple_vector(Object);
extern Object reclaim_resumable_icp_output_task_queue_vector(Object);
extern Object reclaim_schedule_task_args(Object);
extern Object reclaim_symbol_tree_1(Object);
extern Object reclaim_text_or_gensym_string(Object);
extern Object reclaim_text_string(Object);
extern Object record_direct_structure_method(Object,Object,Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object regenerate_optimized_constant(Object);
extern Object register_icp_write_callback(Object,Object);
extern Object resumable_icp_pop(void);
extern Object resumable_icp_pop_list_if_end_marker(void);
extern Object resumable_icp_push(Object);
extern Object resumable_icp_write_callback(Object,Object);
extern Object resume_icp_task_1(Object);
extern Object run_resumable_icp_write_task(Object,Object);
extern Object send_icp_abort_icp_task(Object);
extern Object send_icp_add_to_list_of_symbols(Object,Object,Object);
extern Object send_icp_enlarge_corresponding_icp_object_index_space(Object,Object);
extern Object send_icp_intern(Object,Object);
extern Object send_icp_intern_keyword(Object,Object);
extern Object send_icp_intern_list(Object,Object);
extern Object send_icp_resume_icp_task(Object,Object);
extern Object send_icp_start_icp_task(Object,Object,Object);
extern Object send_or_enqueue_icp_write_task(Object,Object,Object,Object,Object,Object);
extern Object set_access_form_for_interned_list(Object,Object);
extern Object set_access_form_for_symbol(Object,Object);
extern Object set_icp_object_index_for_interned_list(Object,Object,Object);
extern Object set_icp_object_index_for_symbol(Object,Object,Object);
extern Object set_in_icp_port(Object,Object,Object,Object);
extern Object set_up_icp_object_index_space(Object);
extern Object start_writing_icp_message(Object);
extern Object store_corresponding_icp_object(Object,Object);
extern Object store_corresponding_item(Object,Object);
extern Object symbol_name_text_string(Object);
extern Object symbol_tree_structure_memory_usage(void);
extern Object text_string_p(Object);
extern Object text_string_substring(Object,Object,Object);
extern Object time_slice_expired_p(void);
extern Object update_object_pool_meters_list(Object);
extern Object wide_string_length_in_icp_bytes(Object);
extern Object wide_string_to_gensym_string(Object);
extern Object write_get_new_buffer(void);
extern Object write_icp_boolean(Object);
extern Object write_icp_byte(Object);
extern Object write_icp_character(Object);
extern Object write_icp_corresponding_object_index(Object);
extern Object write_icp_filtered_text_string(Object);
extern Object write_icp_fixnum(Object);
extern Object write_icp_gensym_string(Object);
extern Object write_icp_icp_task_resumable_p(Object);
extern Object write_icp_icp_tree(Object);
extern Object write_icp_improper_list(Object);
extern Object write_icp_improper_list_element(Object);
extern Object write_icp_integer(Object);
extern Object write_icp_interned_list_as_value_type(Object);
extern Object write_icp_large_integer(Object);
extern Object write_icp_list(Object);
extern Object write_icp_list_element(Object);
extern Object write_icp_list_of_integers(Object);
extern Object write_icp_list_of_unsigned_integers(Object);
extern Object write_icp_managed_double_float(Object);
extern Object write_icp_managed_long(Object);
extern Object write_icp_maybe_suspend(void);
extern Object write_icp_raw_gensym_string_using_function(Object);
extern Object write_icp_symbol_as_value_type(Object);
extern Object write_icp_text_string(Object);
extern Object write_icp_unsigned_integer(Object);
extern Object write_icp_unsigned_integer_qm(Object);
extern Object write_icp_wide_string(Object);

#else

extern Object ab_assoc_equal();
extern Object add_icp_message_handler();
extern Object allocate_managed_long_box();
extern Object allocate_managed_simple_vector();
extern Object assign_corresponding_icp_object_index();
extern Object assign_index_in_index_space();
extern Object assq_function();
extern Object bytes_per_simple_vector();
extern Object clear_optimized_constants();
extern Object constant_queue_next();
extern Object constant_queue_pop_left();
extern Object constant_queue_push_right();
extern Object copy_illegal_gensym_string_without_bad_characters();
extern Object copy_text_string();
extern Object copy_tree_for_interned_list();
extern Object copy_widestr_to_icpbuf();
extern Object current_icp_read_task_resumable_p();
extern Object deassign_index_in_index_space();
extern Object direct_structure_method();
extern Object emit_icp_read_trace();
extern Object emit_icp_write_trace();
extern Object end_icp_message_group();
extern Object enlarge_index_space();
extern Object enqueue_icp_write_task();
extern Object ensure_icp_write_callback();
extern Object ensure_next_icp_message_series();
extern Object establish_new_object_index_for_interned_list();
extern Object establish_new_object_index_for_symbol();
extern Object export_text_string();
extern Object fixnum_length_in_icp_bytes();
extern Object frame_serial_number_function();
extern Object frame_serial_number_to_item_table();
extern Object gensym_cons_1();
extern Object gensym_list_2();
extern Object gensym_string_length_in_icp_bytes();
extern Object gensym_string_substring();
extern Object gensym_string_to_wide_string();
extern Object get_corresponding_icp_object();
extern Object get_from_icp_port();
extern Object get_from_icp_port_if_any();
extern Object get_icp_object_index_for_interned_list();
extern Object get_icp_object_index_for_symbol();
extern Object getfq_function_no_default();
extern Object handle_icp_abort_icp_task();
extern Object handle_icp_abort_icp_task__body();
extern Object handle_icp_add_to_list_of_symbols();
extern Object handle_icp_add_to_list_of_symbols__body();
extern Object handle_icp_intern();
extern Object handle_icp_intern__body();
extern Object handle_icp_intern_keyword();
extern Object handle_icp_intern_keyword__body();
extern Object handle_icp_intern_list();
extern Object handle_icp_intern_list__body();
extern Object handle_icp_resume_icp_task();
extern Object handle_icp_resume_icp_task__body();
extern Object handle_icp_start_icp_task();
extern Object handle_icp_start_icp_task__body();
extern Object handler_for_enlarge_corresponding_icp_object_index_space();
extern Object icp_connection_being_shutdown_qm();
extern Object icp_connection_open_p();
extern Object icp_cons_1();
extern Object icp_error_internal();
extern Object icp_list_2();
extern Object icp_out_of_synch();
extern Object icp_read_task_priority_function();
extern Object icp_read_task_structure_memory_usage();
extern Object icp_write_task_not_allowed_to_write_p();
extern Object icp_write_task_structure_memory_usage();
extern Object import_text_string();
extern Object info_for_write_icp_symbol_as_value_type();
extern Object initialize_icp_object_type();
extern Object initialize_icp_object_type_compile();
extern Object instantaneous_icp_reader_byte_count();
extern Object instantaneous_icp_writer_byte_count();
extern Object integer_length_in_icp_bytes();
extern Object intern_list();
extern Object intern_text_string();
extern Object intern_text_string_for_icp();
extern Object interned_list_cons();
extern Object interned_list_p_function();
extern Object interned_list_structure_memory_usage();
extern Object item_index_space();
extern Object kill_current_icp_read_task();
extern Object large_integer_length_in_icp_bytes();
extern Object lengthw();
extern Object load_and_initialize_type_description();
extern Object make_corresponding_icp_interned_list();
extern Object make_corresponding_icp_symbol();
extern Object make_empty_constant_queue();
extern Object make_icp_object_index_space();
extern Object make_icp_read_task_1();
extern Object make_icp_write_task_1();
extern Object make_index_space_1();
extern Object make_interned_list_1();
extern Object make_permanent_icp_read_task_structure_internal();
extern Object make_permanent_icp_write_task_structure_internal();
extern Object make_permanent_interned_list_structure_internal();
extern Object make_permanent_schedule_task_structure_internal();
extern Object make_permanent_symbol_tree_structure_internal();
extern Object make_resumable_icp_output_task_queue_vector();
extern Object make_symbol_tree_1();
extern Object make_thread_array();
extern Object maybe_finish_current_icp_read_task();
extern Object memq_function();
extern Object mutate_gensym_plist();
extern Object mutate_global_property();
extern Object mutate_icp_plist();
extern Object notify_user();
extern Object obtain_long_enough_adjustable_gensym_string();
extern Object obtain_simple_gensym_string();
extern Object obtain_text_string();
extern Object outstanding_icp_read_task_count();
extern Object outstanding_icp_write_task_count();
extern Object outstanding_interned_list_count();
extern Object outstanding_symbol_tree_count();
extern Object peek_icp_byte();
extern Object position_of_two_colons();
extern Object push_optimized_constant();
extern Object read_icp_boolean();
extern Object read_icp_byte();
extern Object read_icp_character();
extern Object read_icp_corresponding_object_index();
extern Object read_icp_filtered_text_string();
extern Object read_icp_fixnum();
extern Object read_icp_gensym_string();
extern Object read_icp_icp_task_resumable_p();
extern Object read_icp_icp_tree();
extern Object read_icp_improper_list();
extern Object read_icp_improper_list_element();
extern Object read_icp_integer();
extern Object read_icp_interned_list_as_value_type();
extern Object read_icp_large_integer();
extern Object read_icp_list();
extern Object read_icp_list_element();
extern Object read_icp_list_of_integers_using_function();
extern Object read_icp_list_of_unsigned_integers_using_function();
extern Object read_icp_managed_double_float();
extern Object read_icp_managed_long();
extern Object read_icp_raw_gensym_string_using_function();
extern Object read_icp_suspend();
extern Object read_icp_symbol_as_value_type();
extern Object read_icp_text_string();
extern Object read_icp_unsigned_integer();
extern Object read_icp_unsigned_integer_qm();
extern Object read_icp_wide_string();
extern Object reclaim_constant_queue();
extern Object reclaim_gensym_cons_1();
extern Object reclaim_gensym_list_1();
extern Object reclaim_gensym_string();
extern Object reclaim_icp_list_1();
extern Object reclaim_icp_list_element();
extern Object reclaim_icp_object_map();
extern Object reclaim_icp_object_map_for_interned_list();
extern Object reclaim_icp_object_map_for_symbol();
extern Object reclaim_icp_port_entry();
extern Object reclaim_icp_port_entry_for_interned_list();
extern Object reclaim_icp_port_entry_for_symbol();
extern Object reclaim_icp_read_task_1();
extern Object reclaim_icp_tree_1();
extern Object reclaim_icp_tree_value();
extern Object reclaim_icp_write_task_1();
extern Object reclaim_if_text_or_gensym_string_function();
extern Object reclaim_interned_list_1();
extern Object reclaim_managed_simple_float_array_of_length_1();
extern Object reclaim_managed_simple_vector();
extern Object reclaim_resumable_icp_output_task_queue_vector();
extern Object reclaim_schedule_task_args();
extern Object reclaim_symbol_tree_1();
extern Object reclaim_text_or_gensym_string();
extern Object reclaim_text_string();
extern Object record_direct_structure_method();
extern Object record_system_variable();
extern Object regenerate_optimized_constant();
extern Object register_icp_write_callback();
extern Object resumable_icp_pop();
extern Object resumable_icp_pop_list_if_end_marker();
extern Object resumable_icp_push();
extern Object resumable_icp_write_callback();
extern Object resume_icp_task_1();
extern Object run_resumable_icp_write_task();
extern Object send_icp_abort_icp_task();
extern Object send_icp_add_to_list_of_symbols();
extern Object send_icp_enlarge_corresponding_icp_object_index_space();
extern Object send_icp_intern();
extern Object send_icp_intern_keyword();
extern Object send_icp_intern_list();
extern Object send_icp_resume_icp_task();
extern Object send_icp_start_icp_task();
extern Object send_or_enqueue_icp_write_task();
extern Object set_access_form_for_interned_list();
extern Object set_access_form_for_symbol();
extern Object set_icp_object_index_for_interned_list();
extern Object set_icp_object_index_for_symbol();
extern Object set_in_icp_port();
extern Object set_up_icp_object_index_space();
extern Object start_writing_icp_message();
extern Object store_corresponding_icp_object();
extern Object store_corresponding_item();
extern Object symbol_name_text_string();
extern Object symbol_tree_structure_memory_usage();
extern Object text_string_p();
extern Object text_string_substring();
extern Object time_slice_expired_p();
extern Object update_object_pool_meters_list();
extern Object wide_string_length_in_icp_bytes();
extern Object wide_string_to_gensym_string();
extern Object write_get_new_buffer();
extern Object write_icp_boolean();
extern Object write_icp_byte();
extern Object write_icp_character();
extern Object write_icp_corresponding_object_index();
extern Object write_icp_filtered_text_string();
extern Object write_icp_fixnum();
extern Object write_icp_gensym_string();
extern Object write_icp_icp_task_resumable_p();
extern Object write_icp_icp_tree();
extern Object write_icp_improper_list();
extern Object write_icp_improper_list_element();
extern Object write_icp_integer();
extern Object write_icp_interned_list_as_value_type();
extern Object write_icp_large_integer();
extern Object write_icp_list();
extern Object write_icp_list_element();
extern Object write_icp_list_of_integers();
extern Object write_icp_list_of_unsigned_integers();
extern Object write_icp_managed_double_float();
extern Object write_icp_managed_long();
extern Object write_icp_maybe_suspend();
extern Object write_icp_raw_gensym_string_using_function();
extern Object write_icp_symbol_as_value_type();
extern Object write_icp_text_string();
extern Object write_icp_unsigned_integer();
extern Object write_icp_unsigned_integer_qm();
extern Object write_icp_wide_string();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Ab_package_1, Qab_package_1);
DECLARE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Backtrace_stack_for_internal_error, Qbacktrace_stack_for_internal_error);
DECLARE_VARIABLE_WITH_SYMBOL(Buffer_of_resumable_p, Qbuffer_of_resumable_p);
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_read_tasks, Qchain_of_available_icp_read_tasks);
extern Object Chain_of_available_icp_read_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_icp_write_tasks, Qchain_of_available_icp_write_tasks);
extern Object Chain_of_available_icp_write_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_interned_lists, Qchain_of_available_interned_lists);
extern Object Chain_of_available_interned_lists_vector;
extern Object Chain_of_available_schedule_tasks_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Chain_of_available_symbol_trees, Qchain_of_available_symbol_trees);
extern Object Chain_of_available_symbol_trees_vector;
extern Object Constant_in_large_integer_length_in_icp_bytes;
extern Object Corresponding_icp_object_map_for_symbol_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_buffer, Qcurrent_icp_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_port, Qcurrent_icp_port);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_read_trace_level, Qcurrent_icp_read_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_socket, Qcurrent_icp_socket);
DECLARE_VARIABLE_WITH_SYMBOL(Current_icp_write_trace_level, Qcurrent_icp_write_trace_level);
DECLARE_VARIABLE_WITH_SYMBOL(Current_read_icp_byte_position, Qcurrent_read_icp_byte_position);
DECLARE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);
DECLARE_VARIABLE_WITH_SYMBOL(Current_resumable_icp_read_task, Qcurrent_resumable_icp_read_task);
DECLARE_VARIABLE_WITH_SYMBOL(Current_standard_icp_object_index_space, Qcurrent_standard_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
extern Object Current_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Current_temporary_icp_object_index_space, Qcurrent_temporary_icp_object_index_space);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
DECLARE_VARIABLE_WITH_SYMBOL(Current_write_icp_byte_position, Qcurrent_write_icp_byte_position);
extern Object Deferred_task_queue_vector;
DECLARE_VARIABLE_WITH_SYMBOL(Disable_resumability, Qdisable_resumability);
#define Gsi_64bit_float_array_type_tag FIX((SI_Long)22L)
#define Gsi_64bit_float_list_type_tag FIX((SI_Long)38L)
#define Gsi_64bit_float_type_tag FIX((SI_Long)6L)
#define Gsi_end_type_tag FIX((SI_Long)59L)
#define Gsi_float_type_tag FIX((SI_Long)2L)
#define Gsi_gensym_string_type_tag FIX((SI_Long)68L)
#define Gsi_integer_array_type_tag FIX((SI_Long)17L)
#define Gsi_integer_list_type_tag FIX((SI_Long)33L)
#define Gsi_integer_type_tag FIX((SI_Long)1L)
#define Gsi_item_array_type_tag FIX((SI_Long)23L)
#define Gsi_item_handle_type_tag FIX((SI_Long)9L)
#define Gsi_item_list_type_tag FIX((SI_Long)39L)
#define Gsi_item_or_value_array_type_tag FIX((SI_Long)25L)
#define Gsi_item_or_value_list_type_tag FIX((SI_Long)41L)
#define Gsi_item_type_tag FIX((SI_Long)7L)
#define Gsi_largest_unary_type_number FIX((SI_Long)11L)
#define Gsi_logical_array_type_tag FIX((SI_Long)21L)
#define Gsi_logical_list_type_tag FIX((SI_Long)37L)
#define Gsi_logical_type_tag FIX((SI_Long)5L)
#define Gsi_long_type_tag FIX((SI_Long)51L)
#define Gsi_null_type_tag FIX((SI_Long)0L)
#define Gsi_quantity_array_type_tag FIX((SI_Long)26L)
#define Gsi_quantity_list_type_tag FIX((SI_Long)42L)
#define Gsi_quantity_type_tag FIX((SI_Long)10L)
DECLARE_VARIABLE_WITH_SYMBOL(Gsi_reclaim_list_qm, Qgsi_reclaim_list_qm);
#define Gsi_sequence_type_tag FIX((SI_Long)49L)
#define Gsi_string_array_type_tag FIX((SI_Long)20L)
#define Gsi_string_list_type_tag FIX((SI_Long)36L)
#define Gsi_string_type_tag FIX((SI_Long)4L)
#define Gsi_structure_type_tag FIX((SI_Long)50L)
#define Gsi_symbol_array_type_tag FIX((SI_Long)19L)
#define Gsi_symbol_list_type_tag FIX((SI_Long)35L)
#define Gsi_symbol_type_tag FIX((SI_Long)3L)
#define Gsi_typed_sequence_type_tag FIX((SI_Long)67L)
#define Gsi_unsigned_short_vector_type_tag FIX((SI_Long)11L)
#define Gsi_value_array_type_tag FIX((SI_Long)24L)
#define Gsi_value_list_type_tag FIX((SI_Long)40L)
#define Gsi_value_type_tag FIX((SI_Long)8L)
#define Gsi_wide_string_type_tag FIX((SI_Long)69L)
#define Highest_system_priority FIX((SI_Long)0L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm, Qicp_buffer_of_start_of_message_series_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_buffers_for_message_group, Qicp_buffers_for_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm, Qicp_byte_position_of_start_of_message_series_qm);
#define Icp_cons_type_tag FIX((SI_Long)80L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_error_suspend_p, Qicp_error_suspend_p);
#define Icp_list_nil_terminator_type_tag FIX((SI_Long)82L)
#define Icp_list_non_nil_terminator_type_tag FIX((SI_Long)83L)
#define Icp_list_type_tag FIX((SI_Long)81L)
#define Icp_new_keyword_symbol_type_tag FIX((SI_Long)75L)
#define Icp_new_symbol_expanding_index_space_type_tag FIX((SI_Long)72L)
#define Icp_new_symbol_type_tag FIX((SI_Long)71L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_task_count, Qicp_read_task_count);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_read_trace_cutoff_level_qm, Qicp_read_trace_cutoff_level_qm);
#define Icp_standard_index_space_type_tag FIX((SI_Long)70L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_suspend, Qicp_suspend);
#define Icp_temporary_index_space_type_tag FIX((SI_Long)73L)
#define Icp_tree_interned_list_type_tag FIX((SI_Long)90L)
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_task_count, Qicp_write_task_count);
DECLARE_VARIABLE_WITH_SYMBOL(Icp_write_trace_cutoff_level_qm, Qicp_write_trace_cutoff_level_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_resumable_p_in_icp_buffer, Qindex_of_resumable_p_in_icp_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Index_of_top_of_backtrace_stack, Qindex_of_top_of_backtrace_stack);
#define Index_space_remote_procedure_name FIX((SI_Long)91L)
DECLARE_VARIABLE_WITH_SYMBOL(Inhibit_corresponding_icp_object_making, Qinhibit_corresponding_icp_object_making);
DECLARE_VARIABLE_WITH_SYMBOL(Interned_list_conses, Qinterned_list_conses);
DECLARE_VARIABLE_WITH_SYMBOL(Interned_list_conses_in_use, Qinterned_list_conses_in_use);
DECLARE_VARIABLE_WITH_SYMBOL(Interned_list_count, Qinterned_list_count);
DECLARE_VARIABLE_WITH_SYMBOL(Interned_list_nil, Qinterned_list_nil);
DECLARE_VARIABLE_WITH_SYMBOL(Interned_list_non_symbol_root, Qinterned_list_non_symbol_root);
DECLARE_VARIABLE_WITH_SYMBOL(Interned_list_symbols, Qinterned_list_symbols);
extern Object Interned_list_table_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Keyword_package_1, Qkeyword_package_1);
#define List_element_cons_type_tag FIX((SI_Long)5L)
#define List_element_integer_type_tag FIX((SI_Long)1L)
#define List_element_list_type_tag FIX((SI_Long)4L)
#define List_element_null_type_tag FIX((SI_Long)0L)
#define List_element_symbol_type_tag FIX((SI_Long)2L)
#define List_element_text_type_tag FIX((SI_Long)3L)
#define Lowest_system_priority FIX((SI_Long)11L)
extern Object Maximum_index_in_backtrace_stack_for_internal_error;
#define Maximum_length_for_user_gensym_strings FIX((SI_Long)400000000L)
#define Maximum_length_for_user_text_strings FIX((SI_Long)100000000L)
extern Object Maximum_suggested_length_for_simple_gensym_strings;
#define Minimum_message_series_size_before_suspending FIX((SI_Long)8000L)
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_for_message_series, Qnumber_of_icp_bytes_for_message_series);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_in_message_group, Qnumber_of_icp_bytes_in_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_ready_to_read, Qnumber_of_icp_bytes_ready_to_read);
DECLARE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer, Qnumber_of_icp_bytes_to_fill_buffer);
DECLARE_VARIABLE_WITH_SYMBOL(Object_map_plist_for_icp_tree, Qobject_map_plist_for_icp_tree);
DECLARE_VARIABLE_WITH_SYMBOL(Partition_long_union, Qpartition_long_union);
DECLARE_VARIABLE_WITH_SYMBOL(Priority_of_next_task, Qpriority_of_next_task);
DECLARE_VARIABLE_WITH_SYMBOL(Profiling_enabled_qm, Qprofiling_enabled_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Resumable_icp_state, Qresumable_icp_state);
DECLARE_VARIABLE_WITH_SYMBOL(Roman_font_special_character_code_map, Qroman_font_special_character_code_map);
#define Rpc_existing_item_copy FIX((SI_Long)64L)
#define Rpc_handle_for_new_sending_side_object_type_tag FIX((SI_Long)62L)
#define Rpc_handle_for_receiving_side_object_handle_type_tag FIX((SI_Long)61L)
#define Rpc_handle_for_sending_side_object_type_tag FIX((SI_Long)60L)
#define Rpc_handle_for_temporary_object_handle_type_tag FIX((SI_Long)74L)
#define Rpc_new_item_copy FIX((SI_Long)65L)
#define Rpc_new_item_copy_with_handle FIX((SI_Long)66L)
#define Rpc_new_item_copy_with_reference FIX((SI_Long)63L)
#define Rpc_object_handle_type_tag FIX((SI_Long)8L)
#define Rpc_object_type_tag FIX((SI_Long)7L)
#define Rpc_unknown_type_tag FIX((SI_Long)0L)
#define Size_of_basic_backtrace_information FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);
DECLARE_VARIABLE_WITH_SYMBOL(Symbol_tree_count, Qsymbol_tree_count);
DECLARE_VARIABLE_WITH_SYMBOL(System_is_running, Qsystem_is_running);
extern Object The_type_description_of_icp_read_task;
extern Object The_type_description_of_icp_write_task;
extern Object The_type_description_of_interned_list;
extern Object The_type_description_of_symbol_tree;
DECLARE_VARIABLE_WITH_SYMBOL(Use_new_message_group_for_send_icp_enlarge_index_space_p, Quse_new_message_group_for_send_icp_enlarge_index_space_p);
#define Wide_strings_icp_version FIX((SI_Long)6L)
extern Object Write_icp_large_integer_constant;
DECLARE_VARIABLE_WITH_SYMBOL(Writing_icp_message_group, Qwriting_icp_message_group);
DECLARE_VARIABLE_WITH_SYMBOL(Writing_resumable_icp_messages_p, Qwriting_resumable_icp_messages_p);
