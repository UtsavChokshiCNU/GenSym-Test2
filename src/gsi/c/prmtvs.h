/* prmtvs.h -- Header File for prmtvs.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qarray;
extern Object Qcons;
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

extern Object g2int_abort(int,...);
extern Object g2int_assq_function(Object,Object);
extern Object g2int_c_directory_contains_directory(Object,Object);
extern Object g2int_c_g2_probe_file(Object);
extern Object g2int_c_g2_probe_file_wide(Object);
extern Object g2int_c_g2_stream_open(Object,Object);
extern Object g2int_c_g2_stream_open_wide(Object,Object);
extern Object g2int_c_g2_stream_write_string(Object,Object,Object);
extern Object g2int_c_get_trace_function_name(Object);
extern Object g2int_c_load_library(Object,Object,Object);
extern Object g2int_c_native_clock_ticks_or_cache(Object,Object);
extern Object g2int_c_produce_shared_object(Object,Object,Object,Object);
extern Object g2int_c_run_program_with_string_output_and_timeout(Object,Object,Object,Object,Object);
extern Object g2int_c_run_trace(Object,Object,Object);
extern Object g2int_c_set_file_operation_timeout(Object);
extern Object g2int_c_set_include_directory(Object);
extern Object g2int_c_spawn_command_line_process(Object);
extern Object g2int_c_spawn_executable_process(Object);
extern Object g2int_c_substatus_run_command_line(Object);
extern Object g2int_c_unix_command_with_string_output(Object,Object,Object);
extern Object g2int_c_unix_command_with_string_output_and_timeout(Object,Object,Object,Object,Object);
extern Object g2int_c_uuid_create(Object);
extern Object g2int_c_write_string_to_console(Object,Object);
extern Object g2int_call_gsi_close_fd_callback(Object);
extern Object g2int_call_gsi_not_writing_fd_callback(Object);
extern Object g2int_call_gsi_open_fd_callback(Object);
extern Object g2int_call_gsi_writing_fd_callback(Object);
extern Object g2int_clear_fixnum_time_alarm(void);
extern Object g2int_close_and_disconnect_all_sockets(void);
extern Object g2int_compute_system_variables(Object);
extern Object g2int_copy_foreign_string_arg_if_appropriate(Object);
extern Object g2int_copy_list_using_icp_conses_function(Object);
extern Object g2int_declare_gsi_api_symbol_1(Object);
extern Object g2int_exit_lisp_process(int,...);
extern Object g2int_fixnum_time_difference_in_seconds(Object,Object);
extern Object g2int_fixnum_time_interval(Object);
extern Object g2int_fixnum_time_interval_protected(Object);
extern Object g2int_float_delta_x_in_window(Object,Object);
extern Object g2int_float_delta_y_in_window(Object,Object);
extern Object g2int_gensym_symbol_name(Object);
extern Object g2int_get_fixnum_time_function(void);
extern Object g2int_get_name_for_function(Object);
extern Object g2int_getfq_function(Object,Object,Object);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_handle_event_internal(Object,Object,Object);
extern Object g2int_initialize_system_variables(Object,Object);
extern Object g2int_intern_gensym_string(int,...);
extern Object g2int_inverse_scalef_function(Object,Object);
extern Object g2int_kill_foreign_image_unconditionally(Object);
extern Object g2int_kill_foreign_images(Object);
extern Object g2int_kill_possibly_leftover_spawned_process(Object);
extern Object g2int_lengthw(Object);
extern Object g2int_load_library(Object,Object,Object);
extern Object g2int_make_named_dynamic_extent_description(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_make_permanent_list(Object);
extern Object g2int_make_symbol_name_from_c_name(Object,Object);
extern Object g2int_managed_float_p_function(Object);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_newline_p(Object);
extern Object g2int_no_operation_function(void);
extern Object g2int_obtain_simple_gensym_string(Object);
extern Object g2int_pctpointer(Object);
extern Object g2int_pm_composite_type_of(Object);
extern Object g2int_pm_describe(Object);
extern Object g2int_pm_elt(Object,Object);
extern Object g2int_pm_frame_type(Object);
extern Object g2int_pm_gensym_type_of(Object);
extern Object g2int_pm_nthcdr(Object,Object);
extern Object g2int_pm_object_id(Object);
extern Object g2int_pm_prin1(Object);
extern Object g2int_pm_princ(Object);
extern Object g2int_pm_print(Object);
extern Object g2int_pm_print_object_id(Object);
extern Object g2int_pm_print_structure(Object,Object);
extern Object g2int_pm_print_substructure(Object,Object,Object);
extern Object g2int_pm_print_wide_string(Object);
extern Object g2int_pm_slot_names(Object);
extern Object g2int_pm_structure_type(Object);
extern Object g2int_pm_type_of(Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_reclaim_icp_list_function(Object);
extern Object g2int_reclaim_sysproc_list_function(Object);
extern Object g2int_reclaim_text_string(Object);
extern Object g2int_record_system_variable(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_run_trace(Object);
extern Object g2int_scalef_function(Object,Object);
extern Object g2int_service_sigalrm_signal(void);
extern Object g2int_set_system_variable_as_appropriate(Object,Object);
extern Object g2int_shift_rule_ordering_heuristics(void);
extern Object g2int_shutdown_system_for_exit(void);
extern Object g2int_text_string_p(Object);
extern Object g2int_tformat_text_string(int,...);
extern Object g2int_visible_window_is_present_p(void);
extern Object g2int_wide_string_to_gensym_string(Object);
extern Object g2int_window_is_present_p(void);

#else

extern Object g2int_abort();
extern Object g2int_assq_function();
extern Object g2int_c_directory_contains_directory();
extern Object g2int_c_g2_probe_file();
extern Object g2int_c_g2_probe_file_wide();
extern Object g2int_c_g2_stream_open();
extern Object g2int_c_g2_stream_open_wide();
extern Object g2int_c_g2_stream_write_string();
extern Object g2int_c_get_trace_function_name();
extern Object g2int_c_load_library();
extern Object g2int_c_native_clock_ticks_or_cache();
extern Object g2int_c_produce_shared_object();
extern Object g2int_c_run_program_with_string_output_and_timeout();
extern Object g2int_c_run_trace();
extern Object g2int_c_set_file_operation_timeout();
extern Object g2int_c_set_include_directory();
extern Object g2int_c_spawn_command_line_process();
extern Object g2int_c_spawn_executable_process();
extern Object g2int_c_substatus_run_command_line();
extern Object g2int_c_unix_command_with_string_output();
extern Object g2int_c_unix_command_with_string_output_and_timeout();
extern Object g2int_c_uuid_create();
extern Object g2int_c_write_string_to_console();
extern Object g2int_call_gsi_close_fd_callback();
extern Object g2int_call_gsi_not_writing_fd_callback();
extern Object g2int_call_gsi_open_fd_callback();
extern Object g2int_call_gsi_writing_fd_callback();
extern Object g2int_clear_fixnum_time_alarm();
extern Object g2int_close_and_disconnect_all_sockets();
extern Object g2int_compute_system_variables();
extern Object g2int_copy_foreign_string_arg_if_appropriate();
extern Object g2int_copy_list_using_icp_conses_function();
extern Object g2int_declare_gsi_api_symbol_1();
extern Object g2int_exit_lisp_process();
extern Object g2int_fixnum_time_difference_in_seconds();
extern Object g2int_fixnum_time_interval();
extern Object g2int_fixnum_time_interval_protected();
extern Object g2int_float_delta_x_in_window();
extern Object g2int_float_delta_y_in_window();
extern Object g2int_gensym_symbol_name();
extern Object g2int_get_fixnum_time_function();
extern Object g2int_get_name_for_function();
extern Object g2int_getfq_function();
extern Object g2int_getfq_function_no_default();
extern Object g2int_handle_event_internal();
extern Object g2int_initialize_system_variables();
extern Object g2int_intern_gensym_string();
extern Object g2int_inverse_scalef_function();
extern Object g2int_kill_foreign_image_unconditionally();
extern Object g2int_kill_foreign_images();
extern Object g2int_kill_possibly_leftover_spawned_process();
extern Object g2int_lengthw();
extern Object g2int_load_library();
extern Object g2int_make_named_dynamic_extent_description();
extern Object g2int_make_permanent_list();
extern Object g2int_make_symbol_name_from_c_name();
extern Object g2int_managed_float_p_function();
extern Object g2int_mutate_global_property();
extern Object g2int_newline_p();
extern Object g2int_no_operation_function();
extern Object g2int_obtain_simple_gensym_string();
extern Object g2int_pctpointer();
extern Object g2int_pm_composite_type_of();
extern Object g2int_pm_describe();
extern Object g2int_pm_elt();
extern Object g2int_pm_frame_type();
extern Object g2int_pm_gensym_type_of();
extern Object g2int_pm_nthcdr();
extern Object g2int_pm_object_id();
extern Object g2int_pm_prin1();
extern Object g2int_pm_princ();
extern Object g2int_pm_print();
extern Object g2int_pm_print_object_id();
extern Object g2int_pm_print_structure();
extern Object g2int_pm_print_substructure();
extern Object g2int_pm_print_wide_string();
extern Object g2int_pm_slot_names();
extern Object g2int_pm_structure_type();
extern Object g2int_pm_type_of();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_reclaim_icp_list_function();
extern Object g2int_reclaim_sysproc_list_function();
extern Object g2int_reclaim_text_string();
extern Object g2int_record_system_variable();
extern Object g2int_run_trace();
extern Object g2int_scalef_function();
extern Object g2int_service_sigalrm_signal();
extern Object g2int_set_system_variable_as_appropriate();
extern Object g2int_shift_rule_ordering_heuristics();
extern Object g2int_shutdown_system_for_exit();
extern Object g2int_text_string_p();
extern Object g2int_tformat_text_string();
extern Object g2int_visible_window_is_present_p();
extern Object g2int_wide_string_to_gensym_string();
extern Object g2int_window_is_present_p();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern SI_Long g2int_close_fd_callback(SI_Long);
extern int g2int_g2int_x_error(int);
extern SI_Long g2int_network_event_handler(SI_Long,SI_Long,SI_Long);
extern SI_Long g2int_not_writing_fd_callback(SI_Long);
extern SI_Long g2int_open_fd_callback(SI_Long);
extern SI_Long g2int_run_trace_function(void);
extern SI_Long g2int_unix_command_callback(void);
extern SI_Long g2int_writing_fd_callback(SI_Long);

#else

extern SI_Long g2int_close_fd_callback();
extern int g2int_g2int_x_error();
extern SI_Long g2int_network_event_handler();
extern SI_Long g2int_not_writing_fd_callback();
extern SI_Long g2int_open_fd_callback();
extern SI_Long g2int_run_trace_function();
extern SI_Long g2int_unix_command_callback();
extern SI_Long g2int_writing_fd_callback();

#endif

/* variables/constants */
extern Object G2int_ab_package_1;
extern Object G2int_abort_level_0_tag;
extern Object G2int_all_external_foreign_function_imagesqm;
extern Object G2int_all_foreign_function_imagesqm;
extern Object G2int_cached_fixnum_timeqm;
extern Object G2int_check_time_on_next_uuid;
extern Object G2int_fixnum_time_bignum_worries_limit;
extern Object G2int_fixnum_time_interval_for_one_second;
extern Object G2int_fixnum_time_units_per_second;
#define G2int_g2_stream_foreign_file_op_failure FIX((SI_Long)-1L)
#define G2int_g2_stream_foreign_file_op_success FIX((SI_Long)0L)
#define G2int_g2_stream_open_mode_for_appending FIX((SI_Long)2L)
#define G2int_g2_stream_open_mode_for_binary_appending FIX((SI_Long)6L)
#define G2int_g2_stream_open_mode_for_binary_input FIX((SI_Long)4L)
#define G2int_g2_stream_open_mode_for_binary_output FIX((SI_Long)5L)
#define G2int_g2_stream_open_mode_for_binary_update FIX((SI_Long)7L)
#define G2int_g2_stream_open_mode_for_input FIX((SI_Long)0L)
#define G2int_g2_stream_open_mode_for_output FIX((SI_Long)1L)
#define G2int_g2_stream_open_mode_for_update FIX((SI_Long)3L)
extern Object G2int_gensym_environment_variable_buffer;
extern Object G2int_global_property_conses;
#define G2int_greatest_magnification FIX((SI_Long)4096L)
extern Object G2int_inner_abort_level_tag;
extern Object G2int_isqrt_of_most_positive_fixnum;
extern Object G2int_known_process_idsqm;
#define G2int_least_magnification FIX((SI_Long)16L)
extern Object G2int_maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation;
extern Object G2int_minus_of_isqrt_of_most_positive_fixnum;
extern Object G2int_minus_one_integer;
#define G2int_most_negative_workspace_coordinate FIX((SI_Long)-16777216L)
#define G2int_most_positive_workspace_coordinate FIX((SI_Long)16777215L)
extern Object G2int_named_dynamic_extent_description_prop;
extern Object G2int_names_of_interesting_system_object_pools;
extern Object G2int_no_saved_initial_value;
#define G2int_number_of_fraction_bits_for_text_widths FIX((SI_Long)8L)
extern Object G2int_object_pool_meters;
extern Object G2int_one_integer;
extern Object G2int_pm_file_names;
extern Object G2int_pm_max_length;
extern Object G2int_pm_slot_names;
extern Object G2int_pm_temp_string;
extern Object G2int_process_initializations_alist;
#define G2int_rpc_s_uuid_local_only FIX((SI_Long)1824L)
extern Object G2int_rpc_s_uuid_local_only_message;
#define G2int_rpc_s_uuid_no_address FIX((SI_Long)1739L)
extern Object G2int_rpc_s_uuid_no_address_message;
extern Object G2int_running_trace_function_p;
#define G2int_scaling_factor_for_text_widths FIX((SI_Long)256L)
extern Object G2int_single_element_string;
extern Object G2int_system_variable_descriptions_prop;
extern Object G2int_time_to_check_network_events;
extern Object G2int_trace_function_p_prop;
extern Object G2int_unix_command_callback_function;
#define G2int_wide_character_code_offset FIX((SI_Long)1000000L)
