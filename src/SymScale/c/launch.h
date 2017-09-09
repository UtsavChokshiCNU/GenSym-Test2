/* launch.h -- Header File for launch.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */


/* Symbol Definitions */
extern Object Qdouble_float;
extern Object Qunsigned_byte;
extern Object Kupcase;

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

extern Object announce_system_presence(Object);
extern Object c_set_file_operation_timeout(Object);
extern Object c_x11_initialize(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object cache_command_line_if_necessary(void);
extern Object clear_fixnum_time_alarm(void);
extern Object close_log_file(void);
extern Object copy_list_using_streams_conses_function(Object);
extern Object establish_g2_network_listeners(void);
extern Object exit_lisp_process(int,...);
extern Object g2_stream_close(Object);
extern Object get_command_line_flag_argument(int,...);
extern Object get_command_line_keyword_argument(int,...);
extern Object get_command_line_keyword_argument_as_integer(int,...);
extern Object get_decoded_real_time(void);
extern Object get_default_x11_display(void);
extern Object get_frame_window_type(Object);
extern Object get_icon_name_from_command_line_if_any(void);
extern Object get_node_id_for_uuid_1(void);
extern Object get_values_from_x11_parse_geometry(Object);
extern Object get_window_name_from_command_line_if_any(void);
extern Object getfq_function_no_default(Object,Object);
extern Object initialize_system_variables(Object,Object);
extern Object launch_system_process(Object);
extern Object local_gensym_x11_display(void);
extern Object make_native_window(int,...);
extern Object make_or_revise_window_per_native_window(Object,Object);
extern Object maybe_wait_for_return_key(int,...);
extern Object mutate_global_property(Object,Object,Object);
extern Object no_local_window_p(void);
extern Object print_display_error(void);
extern Object reclaim_streams_list_function(Object);
extern Object register_all_signal_handlers_for_launch(void);
extern Object release_all_kb_write_locks(void);
extern Object report_memory_usage(Object);
extern Object run_system_process(Object,Object,Object);
extern Object set_up_lisp_memory_management(Object);
extern Object shut_down_ab_process(int,...);
extern Object shutdown_or_exit(int,...);
extern Object shutdown_system_for_exit(void);
extern Object write_system_version(Object);
extern Object x11_display_specified_p(void);
extern Object x11_preinitialize_if_necessary(void);

#else

extern Object announce_system_presence();
extern Object c_set_file_operation_timeout();
extern Object c_x11_initialize();
extern Object cache_command_line_if_necessary();
extern Object clear_fixnum_time_alarm();
extern Object close_log_file();
extern Object copy_list_using_streams_conses_function();
extern Object establish_g2_network_listeners();
extern Object exit_lisp_process();
extern Object g2_stream_close();
extern Object get_command_line_flag_argument();
extern Object get_command_line_keyword_argument();
extern Object get_command_line_keyword_argument_as_integer();
extern Object get_decoded_real_time();
extern Object get_default_x11_display();
extern Object get_frame_window_type();
extern Object get_icon_name_from_command_line_if_any();
extern Object get_node_id_for_uuid_1();
extern Object get_values_from_x11_parse_geometry();
extern Object get_window_name_from_command_line_if_any();
extern Object getfq_function_no_default();
extern Object initialize_system_variables();
extern Object launch_system_process();
extern Object local_gensym_x11_display();
extern Object make_native_window();
extern Object make_or_revise_window_per_native_window();
extern Object maybe_wait_for_return_key();
extern Object mutate_global_property();
extern Object no_local_window_p();
extern Object print_display_error();
extern Object reclaim_streams_list_function();
extern Object register_all_signal_handlers_for_launch();
extern Object release_all_kb_write_locks();
extern Object report_memory_usage();
extern Object run_system_process();
extern Object set_up_lisp_memory_management();
extern Object shut_down_ab_process();
extern Object shutdown_or_exit();
extern Object shutdown_system_for_exit();
extern Object write_system_version();
extern Object x11_display_specified_p();
extern Object x11_preinitialize_if_necessary();

#endif

/* variables/constants */
extern Object Build_comment_string;
extern Object Build_identification_string;
DECLARE_VARIABLE_WITH_SYMBOL(Current_process_handle, Qcurrent_process_handle);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_name, Qcurrent_system_name);
DECLARE_VARIABLE_WITH_SYMBOL(Current_system_version, Qcurrent_system_version);
extern Object Debug_frame_reference_balance_qm;
DECLARE_VARIABLE_WITH_SYMBOL(Echo_dialog_spec_p, Qecho_dialog_spec_p);
DECLARE_VARIABLE_WITH_SYMBOL(G2_stream_all_open_streams, Qg2_stream_all_open_streams);
DECLARE_VARIABLE_WITH_SYMBOL(Generic_listener_initialized_qm, Qgeneric_listener_initialized_qm);
DECLARE_VARIABLE_WITH_SYMBOL(Inner_abort_level_tag, Qinner_abort_level_tag);
DECLARE_VARIABLE_WITH_SYMBOL(Send_logbook_messages_to_console_p, Qsend_logbook_messages_to_console_p);
DECLARE_VARIABLE_WITH_SYMBOL(Send_messages_to_console_p, Qsend_messages_to_console_p);
DECLARE_VARIABLE_WITH_SYMBOL(Send_messages_to_logbook_p, Qsend_messages_to_logbook_p);
DECLARE_VARIABLE_WITH_SYMBOL(Shutdown_catch_tag, Qshutdown_catch_tag);
extern Object System_icon_title_string_prop;
extern Object System_run_function_prop;
extern Object System_top_level_function_prop;
DECLARE_VARIABLE_WITH_SYMBOL(System_window, Qsystem_window);
extern Object System_window_title_string_prop;
DECLARE_VARIABLE_WITH_SYMBOL(Trace_system_calls_p, Qtrace_system_calls_p);
DECLARE_VARIABLE_WITH_SYMBOL(Within_managed_object_scope, Qwithin_managed_object_scope);
