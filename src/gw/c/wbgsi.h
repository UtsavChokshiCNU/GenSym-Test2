/* wbgsi.h -- Header File for wbgsi.c
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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

extern Object g2int_add_message_header_field(Object,Object,Object);
extern Object g2int_assq_function(Object,Object);
extern Object g2int_built_in_argument_of_fetch_id(Object,Object);
extern Object g2int_cache_command_line_if_necessary(void);
extern Object g2int_cache_toc_namestring(void);
extern Object g2int_call_gsi_callback(int,...);
extern Object g2int_clear_thread_pool(Object);
extern Object g2int_coerce_to_simple_gensym_string(Object);
extern Object g2int_consume_header_if_any(Object);
extern Object g2int_convert_text_to_base64_encoding(Object);
extern Object g2int_copy_out_current_gensym_string(void);
extern Object g2int_copy_resource_plist_value(Object);
extern Object g2int_copy_text_between_marks(Object,Object);
extern Object g2int_delete_gensym_element_1(Object,Object);
extern Object g2int_emit_headers_of_response(Object,Object);
extern Object g2int_encode_weblink_html_text(Object,Object);
extern Object g2int_end_io_wait(void);
extern Object g2int_enqueue_finish_into_reply(Object);
extern Object g2int_enqueue_text_into_reply(Object,Object);
extern Object g2int_enter_resource_into_cache(Object);
extern Object g2int_extend_current_gensym_string(int,...);
extern Object g2int_feed_running_threads(void);
extern Object g2int_filter_data_for_get_line_from_url(Object,Object);
extern Object g2int_g2_stream_close(Object);
extern Object g2int_g2_stream_delete_file(Object);
extern Object g2int_g2_stream_open_for_input(Object);
extern Object g2int_g2_stream_open_for_output(Object);
extern Object g2int_g2_stream_probe_file_for_exist(Object);
extern Object g2int_g2_stream_read_char(Object);
extern Object g2int_g2_stream_read_into_buffer(Object,Object,Object);
extern Object g2int_g2_stream_read_line(Object);
extern Object g2int_g2_stream_terpri(Object);
extern Object g2int_g2_stream_write_char(Object,Object);
extern Object g2int_g2_stream_write_from_buffer(Object,Object,Object);
extern Object g2int_g2_stream_write_line(Object,Object);
extern Object g2int_g2_stream_write_string(Object,Object);
extern Object g2int_generate_resource_cache_name(void);
extern Object g2int_gensym_cons_1(Object,Object);
extern Object g2int_gensym_delete_file(Object);
extern Object g2int_gensym_list_2(Object,Object);
extern Object g2int_gensym_make_pathname_with_copied_components(Object,Object,Object,Object,Object,Object,Object);
extern Object g2int_gensym_namestring(int,...);
extern Object g2int_gensym_string_substring(Object,Object,Object);
extern Object g2int_get_decoded_real_time(void);
extern Object g2int_get_initial_command_line_arguments(void);
extern Object g2int_get_property_of_buffer(Object,Object);
extern Object g2int_get_simple_text_from_last_scan(void);
extern Object g2int_get_value_of_any_simple_type(Object);
extern Object g2int_gsi_current_context_number(void);
extern Object g2int_gsi_error(int,...);
extern Object g2int_init_cache_name_counter(void);
extern Object g2int_initialize_fetch_styles_of_context(void);
extern Object g2int_insert_character_at_mark(Object,Object);
extern Object g2int_insert_subtext_at_mark(Object,Object,Object,Object);
extern Object g2int_install_tender_of_resource(Object,Object,Object);
extern Object g2int_intern_gensym_string(int,...);
extern Object g2int_is_url_in_cacheqm(Object);
extern Object g2int_kick_bridge_tasks(void);
extern Object g2int_lgsi_get_attribute_value(Object,Object);
extern Object g2int_make_gensym_list_1(Object);
extern Object g2int_make_mark_at_start(Object);
extern Object g2int_make_mark_into_new_empty_resource_buffer(void);
extern Object g2int_map_and_validate_charset_name(Object);
extern Object g2int_mark_copy(Object);
extern Object g2int_mark_kill(Object);
extern Object g2int_mark_move(Object,Object);
extern Object g2int_mark_move_to_end(Object);
extern Object g2int_mark_set(Object,Object);
extern Object g2int_mark_tab(Object,Object);
extern Object g2int_mutate_global_property(Object,Object,Object);
extern Object g2int_notify_user_at_console(int,...);
extern Object g2int_obtain_simple_gensym_string(Object);
extern Object g2int_point_max(Object);
extern Object g2int_point_min(Object);
extern Object g2int_postprocess_result_fragments(Object);
extern Object g2int_preflight_cache_directory(void);
extern Object g2int_protect_gsi_api_call_p(void);
extern Object g2int_read_cache_toc(void);
extern Object g2int_read_cache_toc_1(Object);
extern Object g2int_read_cache_toc_count(Object);
extern Object g2int_read_resource_from_file(Object,Object);
extern Object g2int_reclaim_gensym_list_1(Object);
extern Object g2int_reclaim_gensym_pathname(Object);
extern Object g2int_reclaim_gensym_string(Object);
extern Object g2int_reclaim_plist_of_resource_buffer(Object);
extern Object g2int_reclaim_resource_buffer_of_mark(Object);
extern Object g2int_reclaim_text_string(Object);
extern Object g2int_release_from_cache(Object);
extern Object g2int_reload_from_cache_info(Object);
extern Object g2int_remove_url_from_cache(Object,Object);
extern Object g2int_request_url_from_g2(Object,Object);
extern Object g2int_request_url_from_g2_1(Object,Object);
extern Object g2int_return_from_zgw_add_to_url_reply_1(Object,Object);
extern Object g2int_return_from_zgw_configure_bridge_1(Object,Object);
extern Object g2int_return_from_zgw_decline_to_serve_url_1(Object,Object);
extern Object g2int_return_from_zgw_finish_url_reply_1(Object,Object);
extern Object g2int_return_from_zgw_get_attribute_of_request_1(Object,Object,Object);
extern Object g2int_return_from_zgw_kill_bridge_1(Object,Object);
extern Object g2int_return_from_zgw_make_base64_encoded_1(Object,Object,Object);
extern Object g2int_return_from_zgw_ping_1(Object,Object);
extern Object g2int_return_from_zgw_set_header_field_1(Object,Object);
extern Object g2int_return_from_zgw_set_url_reply_charset_1(Object,Object);
extern Object g2int_return_from_zgw_start_http_server_1(Object,Object);
extern Object g2int_return_from_zgw_tender_resources_1(Object,Object);
extern Object g2int_scan_header_line(Object);
extern Object g2int_scan_integer(void);
extern Object g2int_scan_one_or_more_spaces_and_tabs(void);
extern Object g2int_scan_text(Object);
extern Object g2int_scan_to_beginning_of_next_line(void);
extern Object g2int_scan_to_end_of_line(void);
extern Object g2int_set_property_of_buffer(Object,Object,Object);
extern Object g2int_set_simple_value_in_item(Object,Object);
extern Object g2int_shutdown_bridge(void);
extern Object g2int_shutdown_fetch_styles_of_context(void);
extern Object g2int_shutdown_thread_tree(void);
extern Object g2int_signal_from_rpc(Object,Object);
extern Object g2int_startup_bridge(void);
extern Object g2int_startup_http_server(Object);
extern Object g2int_tformat_text_string(int,...);
extern Object g2int_thread_kill(Object);
extern Object g2int_twrite_beginning_of_wide_string(Object,Object);
extern Object g2int_twrite_cache_number(Object,Object);
extern Object g2int_twrite_gensym_characters_from_ascii_string(int,...);
extern Object g2int_twrite_wide_character(Object);
extern Object g2int_validate_fetch_id(Object);
extern Object g2int_write_cache_toc(Object);
extern Object g2int_write_cache_toc_1(Object,Object);
extern Object g2int_write_resource_to_file(Object,Object);

#else

extern Object g2int_add_message_header_field();
extern Object g2int_assq_function();
extern Object g2int_built_in_argument_of_fetch_id();
extern Object g2int_cache_command_line_if_necessary();
extern Object g2int_cache_toc_namestring();
extern Object g2int_call_gsi_callback();
extern Object g2int_clear_thread_pool();
extern Object g2int_coerce_to_simple_gensym_string();
extern Object g2int_consume_header_if_any();
extern Object g2int_convert_text_to_base64_encoding();
extern Object g2int_copy_out_current_gensym_string();
extern Object g2int_copy_resource_plist_value();
extern Object g2int_copy_text_between_marks();
extern Object g2int_delete_gensym_element_1();
extern Object g2int_emit_headers_of_response();
extern Object g2int_encode_weblink_html_text();
extern Object g2int_end_io_wait();
extern Object g2int_enqueue_finish_into_reply();
extern Object g2int_enqueue_text_into_reply();
extern Object g2int_enter_resource_into_cache();
extern Object g2int_extend_current_gensym_string();
extern Object g2int_feed_running_threads();
extern Object g2int_filter_data_for_get_line_from_url();
extern Object g2int_g2_stream_close();
extern Object g2int_g2_stream_delete_file();
extern Object g2int_g2_stream_open_for_input();
extern Object g2int_g2_stream_open_for_output();
extern Object g2int_g2_stream_probe_file_for_exist();
extern Object g2int_g2_stream_read_char();
extern Object g2int_g2_stream_read_into_buffer();
extern Object g2int_g2_stream_read_line();
extern Object g2int_g2_stream_terpri();
extern Object g2int_g2_stream_write_char();
extern Object g2int_g2_stream_write_from_buffer();
extern Object g2int_g2_stream_write_line();
extern Object g2int_g2_stream_write_string();
extern Object g2int_generate_resource_cache_name();
extern Object g2int_gensym_cons_1();
extern Object g2int_gensym_delete_file();
extern Object g2int_gensym_list_2();
extern Object g2int_gensym_make_pathname_with_copied_components();
extern Object g2int_gensym_namestring();
extern Object g2int_gensym_string_substring();
extern Object g2int_get_decoded_real_time();
extern Object g2int_get_initial_command_line_arguments();
extern Object g2int_get_property_of_buffer();
extern Object g2int_get_simple_text_from_last_scan();
extern Object g2int_get_value_of_any_simple_type();
extern Object g2int_gsi_current_context_number();
extern Object g2int_gsi_error();
extern Object g2int_init_cache_name_counter();
extern Object g2int_initialize_fetch_styles_of_context();
extern Object g2int_insert_character_at_mark();
extern Object g2int_insert_subtext_at_mark();
extern Object g2int_install_tender_of_resource();
extern Object g2int_intern_gensym_string();
extern Object g2int_is_url_in_cacheqm();
extern Object g2int_kick_bridge_tasks();
extern Object g2int_lgsi_get_attribute_value();
extern Object g2int_make_gensym_list_1();
extern Object g2int_make_mark_at_start();
extern Object g2int_make_mark_into_new_empty_resource_buffer();
extern Object g2int_map_and_validate_charset_name();
extern Object g2int_mark_copy();
extern Object g2int_mark_kill();
extern Object g2int_mark_move();
extern Object g2int_mark_move_to_end();
extern Object g2int_mark_set();
extern Object g2int_mark_tab();
extern Object g2int_mutate_global_property();
extern Object g2int_notify_user_at_console();
extern Object g2int_obtain_simple_gensym_string();
extern Object g2int_point_max();
extern Object g2int_point_min();
extern Object g2int_postprocess_result_fragments();
extern Object g2int_preflight_cache_directory();
extern Object g2int_protect_gsi_api_call_p();
extern Object g2int_read_cache_toc();
extern Object g2int_read_cache_toc_1();
extern Object g2int_read_cache_toc_count();
extern Object g2int_read_resource_from_file();
extern Object g2int_reclaim_gensym_list_1();
extern Object g2int_reclaim_gensym_pathname();
extern Object g2int_reclaim_gensym_string();
extern Object g2int_reclaim_plist_of_resource_buffer();
extern Object g2int_reclaim_resource_buffer_of_mark();
extern Object g2int_reclaim_text_string();
extern Object g2int_release_from_cache();
extern Object g2int_reload_from_cache_info();
extern Object g2int_remove_url_from_cache();
extern Object g2int_request_url_from_g2();
extern Object g2int_request_url_from_g2_1();
extern Object g2int_return_from_zgw_add_to_url_reply_1();
extern Object g2int_return_from_zgw_configure_bridge_1();
extern Object g2int_return_from_zgw_decline_to_serve_url_1();
extern Object g2int_return_from_zgw_finish_url_reply_1();
extern Object g2int_return_from_zgw_get_attribute_of_request_1();
extern Object g2int_return_from_zgw_kill_bridge_1();
extern Object g2int_return_from_zgw_make_base64_encoded_1();
extern Object g2int_return_from_zgw_ping_1();
extern Object g2int_return_from_zgw_set_header_field_1();
extern Object g2int_return_from_zgw_set_url_reply_charset_1();
extern Object g2int_return_from_zgw_start_http_server_1();
extern Object g2int_return_from_zgw_tender_resources_1();
extern Object g2int_scan_header_line();
extern Object g2int_scan_integer();
extern Object g2int_scan_one_or_more_spaces_and_tabs();
extern Object g2int_scan_text();
extern Object g2int_scan_to_beginning_of_next_line();
extern Object g2int_scan_to_end_of_line();
extern Object g2int_set_property_of_buffer();
extern Object g2int_set_simple_value_in_item();
extern Object g2int_shutdown_bridge();
extern Object g2int_shutdown_fetch_styles_of_context();
extern Object g2int_shutdown_thread_tree();
extern Object g2int_signal_from_rpc();
extern Object g2int_startup_bridge();
extern Object g2int_startup_http_server();
extern Object g2int_tformat_text_string();
extern Object g2int_thread_kill();
extern Object g2int_twrite_beginning_of_wide_string();
extern Object g2int_twrite_cache_number();
extern Object g2int_twrite_gensym_characters_from_ascii_string();
extern Object g2int_twrite_wide_character();
extern Object g2int_validate_fetch_id();
extern Object g2int_write_cache_toc();
extern Object g2int_write_cache_toc_1();
extern Object g2int_write_resource_to_file();

#endif

/* Externally callable routines */

#ifdef USE_PROTOTYPES

extern void g2int_shared_gsi_reclaim_items(Object);
extern void g2int_shared_gsi_rpc_return_values(Object,SI_Long,Object,SI_Long);
extern void g2int_shared_zgw_add_to_url_reply(Object,SI_Long,Object);
extern void g2int_shared_zgw_configure_bridge(Object,SI_Long,Object);
extern void g2int_shared_zgw_decline_to_serve_url(Object,SI_Long,Object);
extern void g2int_shared_zgw_finish_url_reply(Object,SI_Long,Object);
extern void g2int_shared_zgw_get_attribute_of_request(Object,SI_Long,Object);
extern void g2int_shared_zgw_kill_bridge(Object,SI_Long,Object);
extern void g2int_shared_zgw_make_base64_encoded(Object,SI_Long,Object);
extern void g2int_shared_zgw_ping(Object,SI_Long,Object);
extern void g2int_shared_zgw_set_header_field(Object,SI_Long,Object);
extern void g2int_shared_zgw_set_url_reply_charset(Object,SI_Long,Object);
extern void g2int_shared_zgw_start_http_server(Object,SI_Long,Object);
extern void g2int_shared_zgw_tender_resources(Object,SI_Long,Object);
extern SI_Long gsi_g2_poll(void);
extern SI_Long gsi_get_data(Object,SI_Long);
extern SI_Long gsi_get_tcp_port(void);
DLLEXPORT extern Object gsi_make_items(SI_Long);
extern SI_Long gsi_pause_context(void);
extern SI_Long gsi_receive_deregistrations(Object,SI_Long);
extern SI_Long gsi_receive_message(Object,SI_Long);
extern SI_Long gsi_receive_registration(Object);
extern SI_Long gsi_resume_context(void);
extern SI_Long gsi_set_data(Object,SI_Long);
extern SI_Long gsi_shutdown_context(void);
extern SI_Long gw_error_handler(SI_Long,SI_Long,char *);
extern SI_Long inner_initialize_context(void);
DLLEXPORT extern void zgw_add_to_url_reply(Object,SI_Long,Object);
DLLEXPORT extern void zgw_configure_bridge(Object,SI_Long,Object);
DLLEXPORT extern void zgw_decline_to_serve_url(Object,SI_Long,Object);
DLLEXPORT extern void zgw_finish_url_reply(Object,SI_Long,Object);
DLLEXPORT extern void zgw_get_attribute_of_request(Object,SI_Long,Object);
DLLEXPORT extern void zgw_kill_bridge(Object,SI_Long,Object);
DLLEXPORT extern void zgw_make_base64_encoded(Object,SI_Long,Object);
DLLEXPORT extern void zgw_ping(Object,SI_Long,Object);
DLLEXPORT extern void zgw_set_header_field(Object,SI_Long,Object);
DLLEXPORT extern void zgw_set_url_reply_charset(Object,SI_Long,Object);
DLLEXPORT extern void zgw_start_http_server(Object,SI_Long,Object);
DLLEXPORT extern void zgw_tender_resources(Object,SI_Long,Object);

#else

extern void g2int_shared_gsi_reclaim_items();
extern void g2int_shared_gsi_rpc_return_values();
extern void g2int_shared_zgw_add_to_url_reply();
extern void g2int_shared_zgw_configure_bridge();
extern void g2int_shared_zgw_decline_to_serve_url();
extern void g2int_shared_zgw_finish_url_reply();
extern void g2int_shared_zgw_get_attribute_of_request();
extern void g2int_shared_zgw_kill_bridge();
extern void g2int_shared_zgw_make_base64_encoded();
extern void g2int_shared_zgw_ping();
extern void g2int_shared_zgw_set_header_field();
extern void g2int_shared_zgw_set_url_reply_charset();
extern void g2int_shared_zgw_start_http_server();
extern void g2int_shared_zgw_tender_resources();
extern SI_Long gsi_g2_poll();
extern SI_Long gsi_get_data();
extern SI_Long gsi_get_tcp_port();
DLLEXPORT extern Object gsi_make_items();
extern SI_Long gsi_pause_context();
extern SI_Long gsi_receive_deregistrations();
extern SI_Long gsi_receive_message();
extern SI_Long gsi_receive_registration();
extern SI_Long gsi_resume_context();
extern SI_Long gsi_set_data();
extern SI_Long gsi_shutdown_context();
extern SI_Long gw_error_handler();
extern SI_Long inner_initialize_context();
DLLEXPORT extern void zgw_add_to_url_reply();
DLLEXPORT extern void zgw_configure_bridge();
DLLEXPORT extern void zgw_decline_to_serve_url();
DLLEXPORT extern void zgw_finish_url_reply();
DLLEXPORT extern void zgw_get_attribute_of_request();
DLLEXPORT extern void zgw_kill_bridge();
DLLEXPORT extern void zgw_make_base64_encoded();
DLLEXPORT extern void zgw_ping();
DLLEXPORT extern void zgw_set_header_field();
DLLEXPORT extern void zgw_set_url_reply_charset();
DLLEXPORT extern void zgw_start_http_server();
DLLEXPORT extern void zgw_tender_resources();

#endif

/* variables/constants */
extern Object G2int_abort_level_0_tag;
extern Object G2int_cache_name_counter;
extern Object G2int_command_line_arguments;
extern Object G2int_count_of_gw_configure_bridge;
extern Object G2int_count_of_gw_fetch_url_contents;
extern Object G2int_count_of_gw_install_fetch_style;
extern Object G2int_count_of_gw_ping;
extern Object G2int_count_of_url_requests_upon_g2;
extern Object G2int_current_foreign_string_pad;
extern Object G2int_current_gensym_string;
extern Object G2int_current_left_of_parsing;
extern Object G2int_current_right_of_parsing;
extern Object G2int_current_rpc_call_handle;
extern Object G2int_current_thread;
extern Object G2int_current_twriting_output_type;
extern Object G2int_fill_pointer_for_current_gensym_string;
#define G2int_gsi_bad_magic_number FIX((SI_Long)23L)
#define G2int_gsi_magic_offset FIX((SI_Long)1L)
#define G2int_gsi_run_state_change FIX((SI_Long)16L)
#define G2int_gsi_run_state_direction_entering_gsi FIX((SI_Long)1L)
#define G2int_gsi_run_state_direction_leaving_gsi FIX((SI_Long)2L)
#define G2int_gsi_run_state_type_api FIX((SI_Long)1L)
#define G2int_gsi_success FIX((SI_Long)0L)
extern Object G2int_in_recursive_gsi_context;
extern Object G2int_in_unprotected_gsi_api_call_p;
extern Object G2int_items_in_resource_cache;
extern Object G2int_max_of_foreign_string_pad;
extern Object G2int_number_of_running_threads;
extern Object G2int_root_thread;
extern Object G2int_shutdown_catch_tag;
extern Object G2int_shutdown_requested;
extern Object G2int_statistic_counters;
extern Object G2int_the_bridge_configuration_info;
extern Object G2int_the_http_server_threadqm;
extern Object G2int_the_state_of_g2;
extern Object G2int_top_level_error_catcher_tag;
extern Object G2int_total_length_of_current_gensym_string;
