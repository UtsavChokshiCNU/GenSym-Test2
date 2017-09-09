/* launch.h -- Header File for launch.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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

extern Object g2int_announce_system_presence(Object);
extern Object g2int_c_x11_initialize(Object,Object,Object,Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_clear_fixnum_time_alarm(void);
extern Object g2int_copy_list_using_streams_conses_function(Object);
extern Object g2int_establish_g2_network_listeners(void);
extern Object g2int_g2_stream_close(Object);
extern Object g2int_get_command_line_flag_argument(int,...);
extern Object g2int_get_command_line_keyword_argument(int,...);
extern Object g2int_get_command_line_keyword_argument_as_integer(int,...);
extern Object g2int_get_decoded_real_time(void);
extern Object g2int_get_default_x11_display(void);
extern Object g2int_get_frame_window_type(Object);
extern Object g2int_get_icon_name_from_command_line_if_any(void);
extern Object g2int_get_values_from_x11_parse_geometry(Object);
extern Object g2int_get_window_name_from_command_line_if_any(void);
extern Object g2int_getfq_function_no_default(Object,Object);
extern Object g2int_initialize_system_variables(Object,Object);
extern Object g2int_launch_system_process(Object);
extern Object g2int_make_native_window(int,...);
extern Object g2int_make_or_revise_window_per_native_window(Object,Object);
extern Object g2int_maybe_wait_for_return_key(int,...);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_reclaim_streams_list_function(Object);
extern Object g2int_register_all_signal_handlers_for_launch(void);
extern Object g2int_run_system_process(Object,Object,Object);
extern Object g2int_shut_down_ab_process(int,...);
extern Object g2int_shutdown_or_exit(int,...);
extern Object g2int_write_system_version(Object);

#else

extern Object g2int_announce_system_presence();
extern Object g2int_c_x11_initialize();
extern Object g2int_clear_fixnum_time_alarm();
extern Object g2int_copy_list_using_streams_conses_function();
extern Object g2int_establish_g2_network_listeners();
extern Object g2int_g2_stream_close();
extern Object g2int_get_command_line_flag_argument();
extern Object g2int_get_command_line_keyword_argument();
extern Object g2int_get_command_line_keyword_argument_as_integer();
extern Object g2int_get_decoded_real_time();
extern Object g2int_get_default_x11_display();
extern Object g2int_get_frame_window_type();
extern Object g2int_get_icon_name_from_command_line_if_any();
extern Object g2int_get_values_from_x11_parse_geometry();
extern Object g2int_get_window_name_from_command_line_if_any();
extern Object g2int_getfq_function_no_default();
extern Object g2int_initialize_system_variables();
extern Object g2int_launch_system_process();
extern Object g2int_make_native_window();
extern Object g2int_make_or_revise_window_per_native_window();
extern Object g2int_maybe_wait_for_return_key();
extern Object g2int_mutate_global_property();
extern Object g2int_reclaim_streams_list_function();
extern Object g2int_register_all_signal_handlers_for_launch();
extern Object g2int_run_system_process();
extern Object g2int_shut_down_ab_process();
extern Object g2int_shutdown_or_exit();
extern Object g2int_write_system_version();

#endif

/* variables/constants */
extern Object G2int_build_comment_string;
extern Object G2int_build_identification_string;
extern Object G2int_current_process_handle;
extern Object G2int_current_system_name;
extern Object G2int_current_system_version;
extern Object G2int_g2_stream_all_open_streams;
extern Object G2int_generic_listener_initializedqm;
extern Object G2int_inner_abort_level_tag;
extern Object G2int_shutdown_catch_tag;
extern Object G2int_system_icon_title_string_prop;
extern Object G2int_system_run_function_prop;
extern Object G2int_system_top_level_function_prop;
extern Object G2int_system_window;
extern Object G2int_system_window_title_string_prop;
extern Object G2int_within_managed_object_scope;
