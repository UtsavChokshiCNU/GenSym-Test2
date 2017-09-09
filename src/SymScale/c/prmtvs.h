/* prmtvs.h -- Header File for prmtvs.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qarray;
extern Object Qcons;
extern Object Qdouble_float;
extern Object Qmember;
extern Object Qnull;
extern Object Qquote;
extern Object Kstart1;
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

extern Object abort_g2(int,...);
extern Object assq_function(Object,Object);
extern Object back_off(void);
extern Object c_directory_contains_directory(Object,Object);
extern Object c_g2_probe_file(Object);
extern Object c_g2_stream_open(Object,Object);
extern Object c_g2_stream_write_string(Object,Object,Object);
extern Object c_get_trace_function_name(Object);
extern Object c_load_library(Object,Object,Object);
extern Object c_native_clock_ticks_or_cache(Object,Object);
extern Object c_produce_shared_object(Object,Object,Object,Object);
extern Object c_run_program_with_string_output_and_timeout(Object,Object,Object,Object,Object);
extern Object c_run_trace(Object,Object,Object);
extern Object c_set_file_operation_timeout(Object);
extern Object c_set_include_directory(Object);
extern Object c_spawn_command_line_process(Object);
extern Object c_spawn_executable_process(Object);
extern Object c_substatus_run_command_line(Object);
extern Object c_unix_command_with_string_output(Object,Object,Object);
extern Object c_unix_command_with_string_output_and_timeout(Object,Object,Object,Object,Object);
extern Object c_uuid_create(Object);
extern Object c_write_string_to_console(Object,Object);
extern Object clear_fixnum_time_alarm(void);
extern Object close_and_disconnect_all_sockets(void);
extern Object close_native_window(void);
extern Object compute_system_variables(Object);
extern Object convert_any_number_to_text_width(Object);
extern Object convert_any_number_to_text_width_at_compile_time(Object);
extern Object convert_magnification_to_factor(Object);
extern Object convert_to_magnification(Object);
extern Object convert_to_magnification_at_compile_time(Object);
extern Object copy_foreign_string_arg_if_appropriate(Object);
extern Object copy_list_using_icp_conses_function(Object);
extern Object copy_null_terminated_string_as_text_string(Object);
extern Object declare_gsi_api_symbol_1(Object);
extern Object exit_lisp_process(int,...);
extern Object fixnum_time_difference_in_seconds(Object,Object);
extern Object fixnum_time_interval(Object);
extern Object fixnum_time_interval_protected(Object);
extern Object float_delta_x_in_window(Object,Object);
extern Object float_delta_y_in_window(Object,Object);
extern Object g2_random(Object);
extern Object g2int_service_sigalrm_signal(void);
extern Object gensym_probe_file(Object);
extern Object gensym_symbol_name(Object);
extern Object get_fixnum_time_function(void);
extern Object get_name_for_function(Object);
extern Object getfq_function(Object,Object,Object);
extern Object getfq_function_no_default(Object,Object);
extern Object handle_event_internal(Object,Object,Object);
extern Object initialize_system_variables(Object,Object);
extern Object install_system_table(Object);
extern Object intel_inside_p(void);
extern Object intern_gensym_string(int,...);
extern Object inverse_magnify(Object,Object);
extern Object inverse_scalef_function(Object,Object);
extern Object kill_foreign_image_unconditionally(Object);
extern Object kill_foreign_images(Object);
extern Object kill_possibly_leftover_spawned_process(Object);
extern Object lengthw(Object);
extern Object load_library(Object,Object,Object);
extern Object make_dynamic_list(Object);
extern Object make_named_dynamic_extent_description(Object,Object,Object,Object,Object,Object,Object);
extern Object make_permanent_integer(Object);
extern Object make_permanent_list(Object);
extern Object make_symbol_name_from_c_name(Object,Object);
extern Object make_system_frame(Object);
extern Object make_thread_array(Object);
extern Object managed_float_p_function(Object);
extern Object mutate_global_property(Object,Object,Object);
extern Object newline_p(Object);
extern Object no_operation_function(void);
extern Object obtain_simple_gensym_string(Object);
extern Object pct_pointer(Object);
extern Object pm_composite_type_of(Object);
extern Object pm_describe(Object);
extern Object pm_elt(Object,Object);
extern Object pm_frame_type(Object);
extern Object pm_gensym_type_of(Object);
extern Object pm_nthcdr(Object,Object);
extern Object pm_object_id(Object);
extern Object pm_prin1(Object);
extern Object pm_princ(Object);
extern Object pm_print(Object);
extern Object pm_print_object_id(Object);
extern Object pm_print_structure(Object,Object);
extern Object pm_print_substructure(Object,Object,Object);
extern Object pm_print_wide_string(Object);
extern Object pm_slot_names(Object);
extern Object pm_structure_type(Object);
extern Object pm_type_of(Object);
extern Object pool_entry_data_type(Object);
extern Object pool_entry_memory_usage_in_bytes(Object);
extern Object pool_entry_name(Object);
extern Object pool_entry_object_count(Object);
extern Object pool_entry_outstanding_object_count(Object);
extern Object reclaim_gensym_string(Object);
extern Object reclaim_icp_list_function(Object);
extern Object reclaim_sysproc_list_function(Object);
extern Object reclaim_text_string(Object);
extern Object record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object run_trace(Object);
extern Object scale_scale(Object,Object,Object);
extern Object scalef_function(Object,Object);
extern Object set_system_variable_as_appropriate(Object,Object);
extern Object shutdown_system_for_exit(void);
extern Object text_string_p(Object);
extern Object tformat_text_string(int,...);
extern Object total_pool_memory_usage(void);
extern Object total_pool_object_count(void);
extern Object total_pool_outstanding_object_count(void);
extern Object unix_command_output_as_string(Object);
extern Object unix_command_output_as_string_with_timeout_callback(Object,Object,Object,Object);
extern Object update_object_pool_meters_list(Object);
extern Object visible_window_is_present_p(void);
extern Object wide_string_to_gensym_string(Object);
extern Object window_is_present_p(void);

#else

extern Object abort_g2();
extern Object assq_function();
extern Object back_off();
extern Object c_directory_contains_directory();
extern Object c_g2_probe_file();
extern Object c_g2_stream_open();
extern Object c_g2_stream_write_string();
extern Object c_get_trace_function_name();
extern Object c_load_library();
extern Object c_native_clock_ticks_or_cache();
extern Object c_produce_shared_object();
extern Object c_run_program_with_string_output_and_timeout();
extern Object c_run_trace();
extern Object c_set_file_operation_timeout();
extern Object c_set_include_directory();
extern Object c_spawn_command_line_process();
extern Object c_spawn_executable_process();
extern Object c_substatus_run_command_line();
extern Object c_unix_command_with_string_output();
extern Object c_unix_command_with_string_output_and_timeout();
extern Object c_uuid_create();
extern Object c_write_string_to_console();
extern Object clear_fixnum_time_alarm();
extern Object close_and_disconnect_all_sockets();
extern Object close_native_window();
extern Object compute_system_variables();
extern Object convert_any_number_to_text_width();
extern Object convert_any_number_to_text_width_at_compile_time();
extern Object convert_magnification_to_factor();
extern Object convert_to_magnification();
extern Object convert_to_magnification_at_compile_time();
extern Object copy_foreign_string_arg_if_appropriate();
extern Object copy_list_using_icp_conses_function();
extern Object copy_null_terminated_string_as_text_string();
extern Object declare_gsi_api_symbol_1();
extern Object exit_lisp_process();
extern Object fixnum_time_difference_in_seconds();
extern Object fixnum_time_interval();
extern Object fixnum_time_interval_protected();
extern Object float_delta_x_in_window();
extern Object float_delta_y_in_window();
extern Object g2_random();
extern Object g2int_service_sigalrm_signal();
extern Object gensym_probe_file();
extern Object gensym_symbol_name();
extern Object get_fixnum_time_function();
extern Object get_name_for_function();
extern Object getfq_function();
extern Object getfq_function_no_default();
extern Object handle_event_internal();
extern Object initialize_system_variables();
extern Object install_system_table();
extern Object intel_inside_p();
extern Object intern_gensym_string();
extern Object inverse_magnify();
extern Object inverse_scalef_function();
extern Object kill_foreign_image_unconditionally();
extern Object kill_foreign_images();
extern Object kill_possibly_leftover_spawned_process();
extern Object lengthw();
extern Object load_library();
extern Object make_dynamic_list();
extern Object make_named_dynamic_extent_description();
extern Object make_permanent_integer();
extern Object make_permanent_list();
extern Object make_symbol_name_from_c_name();
extern Object make_system_frame();
extern Object make_thread_array();
extern Object managed_float_p_function();
extern Object mutate_global_property();
extern Object newline_p();
extern Object no_operation_function();
extern Object obtain_simple_gensym_string();
extern Object pct_pointer();
extern Object pm_composite_type_of();
extern Object pm_describe();
extern Object pm_elt();
extern Object pm_frame_type();
extern Object pm_gensym_type_of();
extern Object pm_nthcdr();
extern Object pm_object_id();
extern Object pm_prin1();
extern Object pm_princ();
extern Object pm_print();
extern Object pm_print_object_id();
extern Object pm_print_structure();
extern Object pm_print_substructure();
extern Object pm_print_wide_string();
extern Object pm_slot_names();
extern Object pm_structure_type();
extern Object pm_type_of();
extern Object pool_entry_data_type();
extern Object pool_entry_memory_usage_in_bytes();
extern Object pool_entry_name();
extern Object pool_entry_object_count();
extern Object pool_entry_outstanding_object_count();
extern Object reclaim_gensym_string();
extern Object reclaim_icp_list_function();
extern Object reclaim_sysproc_list_function();
extern Object reclaim_text_string();
extern Object record_system_variable();
extern Object run_trace();
extern Object scale_scale();
extern Object scalef_function();
extern Object set_system_variable_as_appropriate();
extern Object shutdown_system_for_exit();
extern Object text_string_p();
extern Object tformat_text_string();
extern Object total_pool_memory_usage();
extern Object total_pool_object_count();
extern Object total_pool_outstanding_object_count();
extern Object unix_command_output_as_string();
extern Object unix_command_output_as_string_with_timeout_callback();
extern Object update_object_pool_meters_list();
extern Object visible_window_is_present_p();
extern Object wide_string_to_gensym_string();
extern Object window_is_present_p();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern SI_Long g2int_close_fd_callback(SI_Long);
extern SI_Long g2int_network_event_handler(SI_Long,SI_Long,SI_Long);
extern SI_Long g2int_not_writing_fd_callback(SI_Long);
extern SI_Long g2int_open_fd_callback(SI_Long);
extern SI_Long g2int_run_trace_function(void);
extern SI_Long g2int_unix_command_callback(void);
extern SI_Long g2int_writing_fd_callback(SI_Long);
extern int g2int_x_error(int);

#else

extern SI_Long g2int_close_fd_callback();
extern SI_Long g2int_network_event_handler();
extern SI_Long g2int_not_writing_fd_callback();
extern SI_Long g2int_open_fd_callback();
extern SI_Long g2int_run_trace_function();
extern SI_Long g2int_unix_command_callback();
extern SI_Long g2int_writing_fd_callback();
extern int g2int_x_error();

#endif

/* variables/constants */
DECLARE_VARIABLE_WITH_SYMBOL(Ab_package_1, Qab_package_1);
DECLARE_VARIABLE_WITH_SYMBOL(Abort_level_0_tag, Qabort_level_0_tag);
DECLARE_VARIABLE_WITH_SYMBOL(All_external_foreign_function_images_qm, Qall_external_foreign_function_images_qm);
DECLARE_VARIABLE_WITH_SYMBOL(All_foreign_function_images_qm, Qall_foreign_function_images_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Backoff_limit, Qbackoff_limit);
extern Object Backoff_max_delay;
extern Object Backoff_min_delay;
DECLARE_VARIABLE_WITH_SYMBOL(Cached_fixnum_time_qm, Qcached_fixnum_time_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Check_time_on_next_uuid, Qcheck_time_on_next_uuid);
DECLARE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);
extern Object Fixnum_time_bignum_worries_limit;
DECLARE_VARIABLE_WITH_SYMBOL(Fixnum_time_interval_for_one_second, Qfixnum_time_interval_for_one_second);
extern Object Fixnum_time_units_per_second;
extern Object G2_max_threads;
#define G2_stream_foreign_file_op_failure FIX((SI_Long)-1L)
#define G2_stream_foreign_file_op_success FIX((SI_Long)0L)
#define G2_stream_open_mode_for_appending FIX((SI_Long)2L)
#define G2_stream_open_mode_for_binary_appending FIX((SI_Long)6L)
#define G2_stream_open_mode_for_binary_input FIX((SI_Long)4L)
#define G2_stream_open_mode_for_binary_output FIX((SI_Long)5L)
#define G2_stream_open_mode_for_binary_update FIX((SI_Long)7L)
#define G2_stream_open_mode_for_input FIX((SI_Long)0L)
#define G2_stream_open_mode_for_output FIX((SI_Long)1L)
#define G2_stream_open_mode_for_update FIX((SI_Long)3L)
DECLARE_VARIABLE_WITH_SYMBOL(Gensym_environment_variable_buffer, Qgensym_environment_variable_buffer);
extern Object Global_property_conses;
#define Greatest_magnification FIX((SI_Long)4096L)
DECLARE_VARIABLE_WITH_SYMBOL(In_clear_kb_p, Qin_clear_kb_p);
DECLARE_VARIABLE_WITH_SYMBOL(Inner_abort_level_tag, Qinner_abort_level_tag);
extern Object Isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Known_process_ids_qm, Qknown_process_ids_qm);
#define Least_magnification FIX((SI_Long)16L)
extern Object Max_number_of_cores;
extern Object Maximum_gensym_environment_variable_length;
extern Object Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation;
extern Object Minus_of_isqrt_of_most_positive_fixnum;
DECLARE_VARIABLE_WITH_SYMBOL(Minus_one_integer, Qminus_one_integer);
#define Most_negative_workspace_coordinate FIX((SI_Long)-16777216L)
#define Most_positive_workspace_coordinate FIX((SI_Long)16777215L)
extern Object Named_dynamic_extent_description_prop;
extern Object Names_of_interesting_system_object_pools;
DECLARE_VARIABLE_WITH_SYMBOL(No_saved_initial_value, Qno_saved_initial_value);
extern Object Number_of_all_threads;
#define Number_of_fraction_bits_for_text_widths FIX((SI_Long)8L)
DECLARE_VARIABLE_WITH_SYMBOL(Object_pool_meters, Qobject_pool_meters);
DECLARE_VARIABLE_WITH_SYMBOL(One_integer, Qone_integer);
extern Object Pm_file_names;
DECLARE_VARIABLE_WITH_SYMBOL(Pm_max_length, Qpm_max_length);
DECLARE_VARIABLE_WITH_SYMBOL(Pm_slot_names, Qpm_slot_names);
DECLARE_VARIABLE_WITH_SYMBOL(Pm_temp_string, Qpm_temp_string);
DECLARE_VARIABLE_WITH_SYMBOL(Process_initializations_alist, Qprocess_initializations_alist);
#define Rpc_s_uuid_local_only FIX((SI_Long)1824L)
extern Object Rpc_s_uuid_local_only_message;
#define Rpc_s_uuid_no_address FIX((SI_Long)1739L)
extern Object Rpc_s_uuid_no_address_message;
DECLARE_VARIABLE_WITH_SYMBOL(Running_trace_function_p, Qrunning_trace_function_p);
#define Scaling_factor_for_text_widths FIX((SI_Long)256L)
DECLARE_VARIABLE_WITH_SYMBOL(Single_element_string, Qsingle_element_string);
extern Object System_variable_descriptions_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Time_to_check_network_events, Qtime_to_check_network_events);
extern Object Trace_function_p_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Unix_command_callback_function, Qunix_command_callback_function);
#define Wide_character_code_offset FIX((SI_Long)1000000L)
