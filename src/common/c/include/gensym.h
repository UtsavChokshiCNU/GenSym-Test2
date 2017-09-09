
/** Prototypes for C functions called from GSI Lisp/Chestnut files **/

// Called from Interop
#include "g2ss/Interop/dllLink.h"
// Doesn't compile currently due to some weird dependencies in Gensym header files
// #include "g2ss/NativeKBext/Specific/SmartSignal/CountHistoryDatapoints.h"
Object XANALYS_API g2nke_count_history_datapoints_matching_op(
	Object subjVar, // the KB variable subject to history retrieval
	Object valueHistoryCascadedRingBuffer,
	Object valueHistoryRingBufferOrCascade,
	Object valueRequestedBySimulator_qm,
	Object referencingSimulationHistory_qm,
	Object N, 
	Object nStart, 
	Object fellow, // the fellow value to compare to
	Object requiredGoodSize, 
	Object compareOperator);

Object XANALYS_API g2nke_count_history_datapoints_matching_op_and_eventflag(
	Object o_subjVar, // the KB variable subject to history retrieval
	Object o_N, 
	Object o_nStart, 
	Object o_fellow, // the fellow value to compare to
	Object o_eventFlag,
	Object o_eventBitPos,
	Object o_requiredGoodSize, 
	Object o_compareOperator);


/* Statistical procedures */
Object XANALYS_API g2nke_historical_mean(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index);

Object XANALYS_API g2nke_historical_variance(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index);

/* called from USERINIT */
extern void /* g2rtl_ */ SI_INIT_packages_1(/* void */);
extern void /* g2rtl_ */ SI_INIT_numbers(/* void */);
extern void /* g2rtl_ */ SI_INIT_streams(/* void */);
extern void /* g2rtl_ */ SI_INIT_io(/* void */);
extern void /* g2rtl_ */ SI_INIT_print(/* void */);
extern void /* g2rtl_ */ SI_INIT_filesys(/* void */);
extern void /* g2rtl_ */ SI_INIT_misc(/* void */);
extern void /* g2int_ */ usersyms(/* void */);
extern int INIT_names(/* int */);

/* called from LOAD */
extern Object /* g2rtl_ */ adjust_area_target_sizes();

/* called from BOOTSTRAP */
extern long g2ext_get_platform_code(/* void */);

/* called from GLBASICS */
extern void g2ext_exit_from_lisp(/* long */);

/* called from OS-TIME */
extern long g2ext_time_zone(/* long */);

/* called from OS-SETTINGS */
extern long g2ext_return_argv(/* char *, long */);
extern long g2ext_argv_strlen(/* long */);
extern long g2ext_environment_variable_strlen(/* char * */);
extern long g2ext_return_environment_variable(/* char *, char * */);
extern long g2ext_get_user_name(/* char * */);

/* called from PRIMITIVES */
extern long g2ext_get_name_for_function(/* char *, void * */);
extern long g2ext_get_trace_function_name(/* char * */);
extern Gensym_Long g2ext_g2_clock_ticks(/* Gensym_Long */);
extern long g2ext_cause_future_alarm_signal(/* long */);
extern long g2ext_cancel_future_alarm_signal(/* long */);
extern long g2ext_set_file_operation_retry_timeout(/* long seconds */);
extern long g2ext_unix_cmd_with_string_output_mx(/* char *, char *, long */);
extern long g2ext_unix_cmd_with_string_output_and_timeout_mx(/* char *, char *,
							  char *, long, long */);
extern long g2ext_run_program_with_string_output_and_timeout_mx(/* char *,
                                                  char *, char *, long, long */);
extern long g2ext_directory_contains_directory(/* char *, char * */);
extern long g2ext_write_string_to_console(/* char * */);
extern double g2ext_spawn_command_line_process(/* char * */);
extern double g2ext_spawn_command_directly(/* char * */);
extern long g2ext_load_library(/* char *, char *, void ** */);
extern long g2ext_produce_shared_object(/* char *, long, char *, char * */);
extern long g2ext_set_include_directory(/* char * */);
extern long g2ext_substatus_run_command_line(/* char * */);
extern long g2ext_g2_probe_file(/* char * */);
extern long g2ext_g2_probe_file_s16(/* g2chr16_t * */);
extern long g2ext_g2_stream_open(/* char *, long */);
extern long g2ext_g2_stream_open_s16(/* g2chr16_t *, long */);
extern long g2ext_str_write_string(/* char *, long, long */);
extern long g2ext_run_trace(/* char *, int, int */);
extern long g2ext_network_uses_select(/* void */);
extern long g2ext_visible_window_is_present(/* void */);
extern long g2ext_window_is_present(/* void */);
extern long g2ext_g2_clock_ticks_per_second(/* void */);

extern int g2ext_max_threads();
extern int g2ext_number_of_cores();

/* called from UNICODE */
extern void g2ext_write_float_from_c(/* char *, char *, long, double */);

/* called from UTILITIES0 */
#ifdef DEBUG_CONSING
/* g2ext_note_allocate_cons and g2ext_note_reclaim_cons are defined
   in ext/c/trace.c */
extern void g2ext_note_allocate_cons(/* void *, void * */);
extern void g2ext_note_reclaim_cons(/* void *, void * */);
#endif

/* called from UTILITIES3 */
#ifdef USE_PROTOTYPES
extern char*  /* g2rtl_ */ isymbol_name(Object sym);
#else
extern char*  /* g2rtl_ */ isymbol_name();
#endif
extern double g2ext_read_float_from_string(/* char * */);

extern Object g2ext_alloc_g2longint(/*long initial_value*/);
extern void g2ext_free_g2longint(/*g2longint* ptr*/);
extern Object g2ext_sum_g2longints(/*g2longint* a, g2longint* b*/);
extern Object g2ext_sub_g2longints(/*g2longint* a, g2longint* b*/);
extern Object g2ext_convert_string_to_g2longint(/*char* str, long si, long ei*/);
extern long g2ext_convert_g2longint_to_string(/*g2longint* number, char* buffer, long len*/);
extern Object g2ext_mul_g2longints(/*g2longint* a, g2longint* b*/);
extern Object g2ext_div_g2longints(/*g2longint* a, g2longint* b*/);
extern Object g2ext_copy_g2longint(/*g2longint* ptr*/);
extern long g2ext_g2longint_eq(/*g2longint* a, g2longint* b*/);
extern long g2ext_g2longint_gt(/*g2longint* a, g2longint* b*/);
extern double g2ext_convert_g2longint_to_double(/*g2longint* value*/);

/* called from TIMES */
extern long g2ext_decode_unix_time(/* double, unsigned short * */);
extern double g2ext_unix_time_as_float(/* void */);
extern double g2ext_infer_encoded_unix_time(/* double */);
extern double g2ext_get_encoded_unix_time(/* long, long, long, long, long,
					     long */);

/* called from OS-ERROR */
extern long g2ext_str_close(/* long */);
extern long g2ext_establish_signal_handler(/* long */);
extern long g2ext_unestablish_signal_handler(/* long */);
extern long g2ext_inhibit_core_dumping(/* void */);
extern long g2ext_most_recent_signal_code(/* void */);
extern void /* g2rtl_ */ update_gensym_error_buffer(/* void */);
extern long g2ext_establish_launch_sig_handler(/* long */);
extern int g2ext_save_backtrace_into_array(/* void **, int, int */);
extern long g2ext_print_backtrace_into_string(/* char *, void **, int */);

/* called from LAUNCH */
extern void g2ext_maybe_wait_for_return_key(/* void */);
extern void g2ext_initialize_g2pointers(/* void */);
extern void g2ext_initialize_locales(/* void */);
extern void ne_initialize_event_handling(/* void */);

/* called from SCHEDULE */
extern void ne_set_next_timer_event(/* long */);
extern void ne_enqueue_scheduler_event(/* void */);

/* called from NETWORKS */
extern long g2ext_network_connect(/* char * */);
extern long g2ext_network_listen(/* long, char *, long, long, long */);
extern long g2ext_get_connection_pathname(/* long, char *, long */);
extern long g2ext_set_connection_pathname(/* long, char * */);
extern long g2ext_get_network_listener(/* long, char *, long */);
extern long g2ext_g2_gethostname(/* char *, long */);
extern long g2ext_nth_network_address(/* long, char *, long */);
extern long g2ext_set_secure_icp(/* long secure_p, long server_p, char *certificate */);

/* called from INT1 */
extern long g2ext_set_debug_status(/* long, long */);

/* called from NETEVENT */
extern long g2_event_ready(/* void */);
extern long g2_event_cycle(/* long */);
extern void ne_last_error_string(/* long, char * */);
extern long ne_last_error_length(/* long */);
extern long g2ext_network_close(/* long */);
extern long ne_display_events_enabled(/* void */);
extern void ne_disable_display_events(/* void */);
extern void ne_enable_display_events(/* void */);
extern long g2ext_network_read(/* long, char *, long */);
extern long ne_last_error_code(/* long */);
extern long g2ext_network_accept(/* void */);
extern long g2ext_get_waited_period(/* void */);
extern void g2ext_reset_waited_period(/* void */);
/* actually called by VARIABLES, but related to the above two */
extern void g2ext_set_record_waits(/* long */);

/* called from INT2 */
extern long g2ext_network_write(/* long, char *, long, long */);


/* called from INT3A */
extern void g2rtl_copy_widestr_to_icpbuf(/* unsigned short *, long,
					    unsigned char *, long, long */);


/* called from INT3B */
extern long g2ext_foreign_partition_float(/* double, unsigned short */); 
extern double g2ext_foreign_reconstruct_float(/* long, long, long, long */);
extern long g2ext_foreign_partition_long(/* Gensym_Long64, unsigned short */); 
extern Gensym_Long64 g2ext_foreign_reconstruct_long(/* long, long, long, long */);

/* called from INT4 */
extern long ne_connected_p(/* long */);
extern long g2ext_network_listener_count(/* void */);
extern long ne_get_listener_handle(/* long */);

/* called from SOCKET2 */
extern int g2ext_secure_socket_p(/* long */);
extern long g2ext_icmp_open(/* char *, char *, int */);
extern long g2ext_icmp_read(/* G2pointer, char*, long, char*, long, short* */);
extern long g2ext_icmp_write(/* G2pointer, int, ,int, int, char*, long, long */);
extern long g2ext_mqtt_log_topic_data(/* G2pointer, int */);
extern long g2ext_mqtt_log_packet_data(/* G2pointer, int */);

/* called from GSI-COMMON */
extern int g2ext_w16strlen(/* short * */);

/* called from GSI */
extern void ne_set_polling_interval_maybe(/* long */);
extern long g2ext_network_get_listener_fd(/* void */);
extern long g2ext_network_get_fd_from_handle(/* long */);
extern void g2_event_wait(/* void */);

/* called from GSI, defined in gsiannex.c */
extern void internal_gsi_start(/* void */);  
extern void gsi_log_command_line(/* int, char[] * */);

/* called from weblink */
extern int g2ext_get_peer_hostname(/* int socket, char *buffer, int buflen */);
extern int g2ext_get_peer_address_string(/* int socket, char *buffer, int buflen */);
extern void lgsi_rpc_declare_remote_1(/* char *function_name, int number_of_args, int number_of_return_values */);
extern long g2pvt_tcpip_listen(/* long port_number */);
extern long g2ext_tcpip_accept_internals(/* long listener_socket */);
extern int gw_socket_poll_status(/* int socket */);
extern void gsi_watch_fd(/* long file_descriptor */);
extern long g2pvt_tcpip_set_nodelay(/* long listener_socket */);
extern void gsi_unwatch_fd(/* long file_descriptor */);
extern long g2pvt_tcpip_close(/* int external_socket */);
extern int gw_socket_write(/* int sock, char *buf, int start, int end */);
extern int gw_fetch_errno();
extern void rpc_start_for_gw_request_for_url();
extern long g2pvt_tcpip_connect(/* char *host, long port */);
extern long gw_tcpip_connection_check(/* int connect_socket */);
extern int gw_socket_read(/* int sock, char *buf, int n */);
extern int gw_socket_data_available_p(/* int sock */);


/** Functions called from TW, not called from GSI **/

/* called from PRIMITIVES */
extern long g2ext_shift_rule_ordering(/* void */);

/* called from PLATFORMS */
extern long g2ext_read_clipboards(/* long, char *, long, long, char *, long,
			long, unsigned short *, long, long, unsigned short * */);
extern long g2ext_write_clipboards(/* long, char *, long, char *, long,
				      unsigned short *, long */);
extern int g2ext_x11_clipboard_x_targets_p(/* int */);
/* 
 * Return type of g2ext_x11_raise_window() was void, contradicting the
 * def-gensym-c-function in PLATFORMS, which expects a :fixnum-int (i.e., a C
 * long -- see above note for why :fixnum-int equates to C long).
 */
extern long g2ext_x11_raise_window(/* long */); 
extern long g2ext_x11_read_cut_buffer(/* long, char *, long */);
extern long g2ext_x11_write_cut_buffer(/* long, char * */);
extern long g2ext_x11_file_descriptor_for_window(/* long */);
/*
 * jh, 7/8/94.  The mswindow.c version of g2ext_x11_preinitialize() takes a
 * single argument, while the xwindows.c version takes two.  So far, this has
 * caused no harm.
 */
extern void g2ext_x11_preinitialize(/* long, long */);
extern long g2ext_x11_initialize(/* char *, char *, char *, long, long, long,
				    long */);
extern long g2ext_get_pixel(/* long, char * */);
extern void g2ext_p_fill_clipped_polygon(/* long, unsigned char *, long, long,
					    long, long, long, long */);
extern int g2ext_w_draw_string_with_clipping(/* long, long, long, long, long,
						long, long, long, long,
						char *, char *, long */);
extern int g2ext_draw_string_in_font(/* long, long, long, long, long, long,
					char *, long */);
extern int g2ext_draw_string_in_font_with_clipping(/* long, long, long, long,
						      long, long, long, long,
						      long, char *, char *,
						      long */);
extern int g2ext_allocate_x_font(/* long, char * */);
extern int g2ext_x11_parse_geometry_x(/* void */);
extern int g2ext_x11_parse_geometry_y(/* void */);
extern int g2ext_x11_parse_geometry_width(/* void */);
extern int g2ext_x11_parse_geometry_height(/* void */);
extern void g2ext_x11_parse_geometry(/* char * */);
extern long g2ext_x11_last_window_x(/* long */);
extern long g2ext_x11_last_window_y(/* long */);
extern long g2ext_x11_last_window_width(/* long */);
extern long g2ext_x11_last_window_height(/* long */);
extern long g2ext_get_event(/* long */);
extern long g2ext_x11_last_mouse_x_position(/* long */);
extern long g2ext_x11_last_mouse_y_position(/* long */);
extern long g2ext_x11_last_event_time(/* long */);
extern long g2ext_x11_last_event_window_handle(/* long */);
extern long g2ext_x11_last_expose_x_position(/* long */);
extern long g2ext_x11_last_expose_y_position(/* long */);
extern long g2ext_x11_last_expose_width(/* long */);
extern long g2ext_x11_last_expose_height(/* long */);
extern void g2ext_x11_move_pointer(/* long, long, long */);
/* 
 * jh, 7/8/94.  No x11_get_mouse_y_position() is called from G2/TW (see note in
 * xwindows.c above g2ext_x11_get_mouse_x_position().  This also had an unused
 * "long position[];" argument, which I removed.
 */
extern long g2ext_x11_get_mouse_x_position(/* long */);
extern void g2ext_start_tracking_mouse(/* long */);
extern void g2ext_stop_tracking_mouse(/* long */);
extern long g2ext_x11_screen_depth(/* long */);
extern double g2ext_get_process_identifier(/* void */);
extern long g2ext_uuid_create(/* unsigned short * */);

/* called from LAUNCH */
extern void g2ext_verify_operating_system(/* long */);

/* called from STREAMS */
extern long g2ext_str_eof_p(/* long */);
extern long g2ext_g2_stream_get_error_number(/* void */);
extern long g2ext_str_sync(/* long */);
extern long g2ext_str_flush(/* long */);
extern long g2ext_str_flip_bidir_mode(/* long */);
extern long g2ext_str_read_char(/* long */);
extern long g2ext_str_read_non_cr_char(/* long */);
extern long g2ext_g2_stream_read_string(/* long, char *, long, long */);
extern long g2ext_g2_stream_read_wide_buffer(/* long, unsigned short *, long,
						long */);
extern long g2ext_g2_stream_read_octets_wide(/* long, unsigned short[], long,
						long */);
extern long g2ext_str_write_char(/* long, char * */);
extern long g2ext_g2_stream_write_buffer(/* long, char *, long, long */);
extern long g2ext_g2_stream_write_wide_buffer(/* long, unsigned short *, long,
						 long */);
extern long g2ext_str_delete_file(/* char */);
extern long g2ext_str_delete_file_s16(/* g2chr16_t */);
extern long g2ext_str_rename_file(/* char *, char * */);
extern long g2ext_str_rename_file_s16(/* g2chr16_t *, g2chr16_t * */);
extern long g2ext_str_copy_file(/* char *, char * */);
extern long g2ext_str_copy_file_s16(/* g2chr16_t *, g2chr16_t * */);
extern long g2ext_make_unique_filename(/* char *, long, char * */);
extern long g2ext_str_opendir(/* char *, char * */);
extern long g2ext_str_readdir(/* char *, long, long */);
extern long g2ext_str_read_subdirs(/* char *, long */);
extern long g2ext_str_initdir(/* void */);
extern long g2ext_str_closedir(/* void */);
extern long g2ext_str_get_next_device(/* char * */);
extern long g2ext_str_open_device_list(/* void */);
extern long g2ext_str_directory_p(/* char * */);
extern long g2ext_str_get_default_dir(/* char * */);
extern long g2ext_str_change_default_dir(/* char */);
extern long g2ext_str_file_length(/* long */);
extern long g2ext_str_file_non_empty(/* long */);
extern long g2ext_str_set_file_position(/* long, long, long */);
extern long g2ext_str_get_file_position(/* long */);
extern long g2ext_str_get_version(/* char */);
extern long g2ext_str_get_device(/* char *, char * */);
extern SI_Long g2ext_str_avail_disk_space(/* char * */);
extern double g2ext_str_file_timestamp(/* char *, long */);
extern long g2ext_str_file_access_check(/* char *, long */);
extern long g2ext_str_get_write_lock(/* char *, char *, char * */);
extern long g2ext_str_release_write_lock(/* char *, char * */);
extern long g2ext_str_logical_name_p(/* char * */);
extern long g2ext_str_max_filename(/* char * */);
extern long g2ext_create_directory(/* char *, long, char * */);

/* called from NETEVENT */
extern int g2ext_invokation_updates_needed(/* void */);
extern long g2ext_cache_deferred_rules(/* void */);
extern void g2ext_note_null_write_callbacks();

/* called from WINDOWS1 */
extern void g2ext_x11_close(/* long */);
extern void g2ext_x11_set_debug_mode(/* int */);
extern void g2ext_x11_clear_debug_mode(/* int */);
extern void g2ext_x11_flush(/* long */);
extern int g2ext_create_pixmap(/* int, int, int, int */);
extern void g2ext_reclaim_pixmap(/* long */);
extern long g2ext_x11_bell(/* long, long */);
extern void g2ext_x11_make_xwindow_visible(/* long */);
extern void g2ext_update_g2_MD5_context(/* int, const char * */);
extern void g2ext_finalize_g2_MD5_context(/* int, unsigned char * */);
extern void g2ext_x11_initialize_after_connection(/* long, long, long */);
extern void g2ext_x11_sync(/* int */);

/* called from WINDOWS2 */
extern void g2ext_p_stipple_rect(/* long, long, long, long, long, long */);
extern void g2ext_p_fill_rect(/* long, long, long, long, long, long */);
extern void g2ext_p_draw_point(/* long, long, long, long */);
extern void g2ext_p_fill_triangle(/* long, long, long, long, long, long, long,
				     long */);
extern void g2ext_p_draw_line(/* long, long, long, long, long, long */);
extern void g2ext_p_draw_wide_line(/* long, long, long, long, long, long,
				      long */);
extern void g2ext_p_fill_arc(/* long, long, long, long, long, long, long,
				long */);
extern void g2ext_p_draw_arc(/* long, long, long, long, long, long, long,
				long */);
extern void g2ext_copy_bitmap_to_bitmap(/* long, long, long, long, long, long,
					   long, long, long */);
extern void g2ext_x11_initialize_tile(/* long, long, long, long */);
extern void g2ext_set_mdi_client_background_color(/*long red, long green, long blue*/);

/* called from WINDOWS3 */
extern void g2ext_w_fill_rect(/* long, long, long, long, long, long, long */);
extern void g2ext_w_draw_line_with_clipping(/* long, long, long, long, long,
					  long, long, long, long, long, long */);
extern void g2ext_w_draw_wide_polyline(/* long, short *, long, long, long, long,
					  long, long, long, long, short *, long,
					  long */);
extern void g2ext_w_draw_polygon();
extern void g2ext_w_draw_ellipse();

extern void g2ext_x11_tile(/* long, long, long, long, long */);
extern void g2ext_scroll_rectangle(/* int, int, int, int, int, int, int */);
extern void g2ext_copy_pixmap_to_window(/* long, long, long, long, long, long,
					   long, long, long, long */);
extern long g2ext_offscreen(/* long, long, long */);
extern void g2ext_x11_draw_pixmap(/* long, long, long, long, long, long, long,
				     long, long */);
extern void g2ext_x11_draw_mask_pixmap(/* long, long, long, long, long, long, long,
				     long, long */);

/* called from WINDOWS3A */
extern void g2ext_copy_polychrome_pixmap_to_window(/* long, long, long, long,
						      long, long, long, long */);

/* called from WINDOWS4 */
extern long g2ext_x11_create_window(/* long, unsigned short *, long, long,
				       long, long, long */);
extern long g2ext_x11_manage_window(/* long, long, long, long, long, long,
				       unsigned short * */);
extern long g2ext_x11_stack_windows(/*long, long, long */);
extern long g2ext_redirect_window(/* long, long, long */);
extern long g2ext_scroll_window(/* long, long, long */);
extern long g2ext_manage_scrollbars(/* long, long, long, long, long, long, long,
				       long */);
extern long g2ext_get_system_metric(/* long */);
extern long g2ext_mega_refresh();
extern long g2ext_window_width(/*long */);
extern long g2ext_window_height(/*long */);

/* called from IMAGES */
extern long g2ext_open_image_stream(/* char *, long */);
extern long g2ext_image_stream_format(/* long */);
extern long g2ext_image_stream_error(/* G2pointer, char *, long */);
extern long g2ext_image_stream_width(/* long */);
extern long g2ext_image_stream_height(/* long */);
extern long g2ext_image_stream_depth(/* long */);
extern long g2ext_image_stream_ncolors(/* long */);
extern long g2ext_image_stream_transparentindex(/* G2pointer */);
extern long g2ext_image_stream_color_map(/* long, long */);
extern long g2ext_read_image_row(/* long, unsigned char * */);
extern long g2ext_close_image_stream(/* long */);
extern int g2ext_free_extended_colors(/* int */);
extern void g2ext_x11_put_image(/* long, long, long, long, long, long, long,
				   unsigned char * */);
extern void g2ext_stretch_bits(/* long, long, long, long, long, long, long,
				  long, long, long, long, RGBQUAD *, long,
				  unsigned char *, long*/);
extern void g2ext_w_draw_tiles(/* long, long, long, long, long, long, long,
				  long, long, long */);

/* called from FONTS */
extern int g2fnt_fontrip_bitmap_value(/* int, int */);
extern long g2fnt_load_built_in_outline_font(/* long */);
extern long g2fnt_get_bbox_width_and_height(/* long, long, long, long, long */);
extern long g2fnt_make_outline_character_raster(/* long, long, long, long, long,
						   long */);
extern long g2fnt_get_textx_offset_for_cur_raster(/* void */);
extern long g2fnt_get_y_offset_for_cur_raster(/* void */);
extern long g2fnt_get_current_raster_text_width(/* void */);
extern long g2fnt_load_outline_font(/* char *, long */);

/* called from SEQUENCES1 */
extern long g2ext_update_callback_frames(/* char *, char * */);
extern long g2ext_frequently_typed_chars(/* char *, char * */);
extern long g2ext_nsleep(/* char * */);
extern long g2ext_nsleep_next(/* char * */);
extern long g2ext_reduce_sleep_tolerance(/* void */);
extern void g2ext_init_g2_MD5_context(/* int */);

/* called from TELESTUBS */
extern long g2ext_x11_clipboard_has_text(/* long */);
extern long g2ext_x11_last_event_bits(/* long */);
extern long g2ext_choose_from_item_menu(/* unknown */);
extern long g2ext_reclaim_item_menu(/* unknown */);
extern long g2ext_begin_item_menu(/* unknown */);
extern long g2ext_add_submenu_to_item_menu(/* unknown */);
extern long g2ext_add_color_string_to_item_menu(/* unknown */);
extern long g2ext_add_string_to_item_menu(/* unknown */);
extern long g2ext_simple_dialog(/* unknown */);
extern long g2ext_list_box(/* unknown */);
extern long g2ext_message_box(/* unknown */);
extern long g2ext_query_box(/* unknown */);
extern long g2ext_manage_notification(/* unknown */);
extern long g2ext_manage_animation(/* unknown */);
extern long g2ext_cancel_modal_dialogs_and_menus(/* unknown */);
extern long g2ext_note_progress(/* unknown */);
extern long g2ext_file_dialog(/* unknown */);
extern long g2ext_choose_directory(/* unknown */);
extern long g2ext_print_window(/* unknown */);
extern long g2ext_print_dialog(/* unknown */);
extern long g2ext_start_doc(/* unknown */);
extern long g2ext_end_page(/* unknown */);
extern long g2ext_end_doc(/* unknown */);
extern long g2ext_draw_to_printer(/* unknown */);
extern long g2ext_abort_printing(/* unknown */);
extern long g2ext_start_page(/* unknown */);
extern long g2ext_set_icon_offsets(/* unknown */);
extern void g2ext_w_draw_string(/* unknown */);
extern long g2ext_about_box(/* unknown */);
extern long g2ext_html_help(/* unknown */);
extern long g2ext_x11_set_scroll_info(/* unknown */);
extern long g2ext_x11_set_window_title(/* unknown */);
extern long g2ext_offscreen(/* unknown */);
extern long g2ext_x11_manage_native_icons(/* unknown */);
extern long g2ext_nms_remove_menu_item(/* unknown */);
extern long g2ext_nms_delete_menu_items(/* unknown */);
extern long g2ext_nms_destroy_menu(/* unknown */);
extern long g2ext_nms_create_menu(/* unknown */);
extern long g2ext_nms_append_menu(/* unknown */);
extern long g2ext_nms_dismiss(/* unknown */);
extern long g2ext_nms_check_menu_item(/* unknown */);
extern long g2ext_nms_check_radio_item(/* unknown */);
extern long g2ext_nms_enable_menu_item(/* unknown */);
extern long g2ext_nms_set_help(/* */);
extern long g2ext_nms_modify_menu_item(/* unknown */);
extern long g2ext_nms_set_menu(/* unknown */);
extern long g2ext_nms_pop_up_menu(/* unknown */);
extern long g2ext_nms_set_flag(/* unknown */);
extern long g2ext_nms_fetch_help_string_result(/* unknown */);
extern long g2ext_nms_width_maintainance_p(/* void */);
extern long g2ext_nms_create_toolbar(/* void */);
extern long g2ext_x11_get_mouse_x_position(/* unknown */);
extern long g2ext_start_dialog(/* long, long, long, long, LPWSTR */);
extern long g2ext_add_to_dialog(/* long, long, long, LPWSTR, long, long, long, 
				   long, long, LPWSTR, long, long, long */);
extern long g2ext_show_dialog(/* long */);
extern void g2ext_abort_dialog(/* long */);
extern void g2ext_accept_dialog(/* long */);
extern void g2ext_abort_dialog_query(/* long, long */);
extern long g2ext_finish_dialog_query(/* long, long */);
extern long g2ext_add_to_dialog_query(/* long, long, long */);
extern long g2ext_start_dialog_query(/* long, long, long */);
extern long g2ext_start_dialog_update(/*long */);
extern long g2ext_end_dialog_update(/* long */);
extern long g2ext_abort_dialog_update(/* long */);
extern long g2ext_dialog_component_update(/* long, long, LPWSTR, long */);
extern void g2ext_lock_dialog(/* long, long*/);

extern long g2ext_manage_grid_view (/*long opcode, long dlgId, long controlId,
				      long row, long col, long intParam, LPWSTR stringParam*/);
extern long g2ext_specify_grid_view_cells (/* long dlgId, long controlId, LPWSTR cell_spec */);
extern void g2ext_specify_text_box_extensions (/* long dlgId */);

extern long g2ext_list_directory_response(/*long opcode, long type, long size,
					    long hi_time, long low_time, LPCSTR name*/);

extern long g2ext_nms_get_toolkit(/*void*/);
extern long g2ext_nms_set_theme(/* long code */);
extern long g2ext_set_ui_property(/* long window_index, long property, long value */);
extern long g2ext_nms_append_control(/* long menu_index, long control_index */);
extern long g2ext_nms_manage_control(/*long control_index, long opcode*/);
extern long g2ext_nms_delete_control(/* long menu_index, long control_index */);
extern long g2ext_nms_create_toolbar(/* long handle, LPWSTR name, long dock */);
extern long g2ext_nms_create_edit_box(/* long handle, LPWSTR name, long width,
					 LPWSTR initial */);
extern long g2ext_nms_create_combo_box(/* long handle, LPWSTR name, long width,
					  LPWSTR initial, LPWSTR choices,
					  long flags, long drop_down_width */);
extern  void g2ext_nms_set_iconsize(/*long iconsize*/);

extern long g2ext_manage_status_bar(/*long opcode, LPWSTR string */);

extern long g2ext_tabbed_mdi_mode(/*long opcode, long arg*/);

extern long g2ext_manage_pane(/*long opcode, long handle, long x, long y, long w, long h, LPWSTR s*/);

extern long g2ext_create_tree_view(/* int handle, LPWSTR title, long x, long y, long width, long height,
			             long dock, long neighbor */);
extern long g2ext_manage_tree_view(/*long opcode, long tree, LPWSTR string, long icon, long parent*/);

extern long g2ext_create_html_view(/*long handle, LPWSTR title, LPWSTR url, long x, long y, long width, long height*/);
extern long g2ext_manage_html_view(/*long opcode, long handle, LPWSTR str*/);

extern long g2ext_create_shortcut_bar(/*long handle, LPWSTR title,
			      long x, long y, long width, long height,
			      long dock, long neighborID*/);
extern long g2ext_manage_shortcut_bar(/*long opcode, long handle, LPWSTR string, 
			      long nFolder, long icon, long userdata*/);

extern long g2ext_create_logbook(/*int handle, LPWSTR title,
				 long x, long y, long width, long height,
				 long dock, long neighbor*/);
extern long g2ext_manage_logbook(/*long opcode, long handle, long msgNum, LPWSTR string*/);
extern long g2ext_manage_extended_logbook(/*long opcode, long handle, long msgNum, long date, 
	                                   LPWSTR string, long message_type,
        	                           LPWSTR workspace_uuid, LPWSTR workspace_name,
                	                   LPWSTR object_uuid, LPWSTR object_type, LPWSTR object_name, 
                        	           long line_number*/);

extern long g2ext_get_charting_library_version(/*char *buf, int buflen*/);
extern long g2ext_create_chart_view(/*long handle, long style, long chart_type,
				      LPWSTR title, long left, long top, long width, long height*/);
extern long g2ext_manage_chart_view(/*long opcode, long handle*/);
extern long g2ext_chart_set_int(/*long handle, long prop, long i, long j, long v*/);
extern long g2ext_chart_set_string(/*long handle, long prop, long i, long j, char *v */);
extern long g2ext_chart_set_double(/*long handle, long prop, long i, long j, double v*/);
extern long g2ext_chart_set_double_array(/*long handle, long prop, double *data, long n*/);

void g2ext_chart_add_long_to_struct(/*long value*/);
void g2ext_chart_add_str_to_struct(/*LPWSTR value*/);
void g2ext_chart_add_double_to_struct(/*double value*/);
long g2ext_chart_set_struct(/*long handle, long prop*/);

extern long g2ext_manage_editor(/* long opcode, long window_index, LPWSTR string, long flags, long caret, long arg3, long arg4 */);

extern long g2ext_debugger_dialog(/*int opcode, LPWSTR title, LPWSTR label, LPWSTR proc, LPWSTR env, int line*/);

extern long g2ext_make_dialog();
extern long g2ext_add_control();
extern long g2ext_post_dialog();

extern long g2ext_x11_last_event_value(/* long window_index,
					  unsigned short *buffer,
					  long buflen */);
extern long g2ext_get_places_bar(/* LPWSTR buffer, long buflen */);

extern long g2ext_set_move_resize_time_limit(/*long seconds*/);

extern long g2ext_update_system_tray (/*long icon, char *iconName, LPWSTR tooltip*/);
extern long g2ext_noninteractive_service_p();

extern long g2ext_create_property_grid();
extern long g2ext_manage_property_grid();

extern long g2ext_create_tabular_view();
extern long g2ext_manage_tabular_view();

/* called from TELEWINDOWS */
extern long g2ext_set_tcp_connect_retry(/* long */);
extern void g2ext_x11_set_window_is_connected(/* long */);
extern int g2ext_process_exists(/* double */);
extern long g2ext_kill_spawned_command_line(/* double */);
extern long g2ext_x11_tell_control_our_session_id(/* long */);
extern long g2ext_native_icons_limit();

/* called from MAIN */
extern void /* g2int_ */ init_top_level(/* void */);
extern void /* g2int_ */ userinit(/* void */);

/** Functions called from G2, not called from GSI or TW **/

/* called from USERINIT */
extern void /* g2rtl_ */ SI_INIT_structure_class(/* void */);

/* called from UTILITIES4 */
extern char *g2ext_g_fmt(/* char *, double */);

/* called from PRINTING */
extern long g2ext_reverse_bits_in_byte(/* long */);
extern long g2ext_create_bigmap(/*long window_index, int width, int height, int depth*/);
extern long g2ext_compress_image(/*long stream_index, long pixmap_index, int cx, int cy, int quality*/);

/* called from KB-LOAD2 */
extern long g2ext_show_function_address(/* void * */);

/* called from KB-SAVE3 */
extern long g2ext_sys_sleep(/* long */);

/* called from KB-SAVE4 */
extern void g2ext_update_g2_MD5_context_wide(/* int, unsigned short *, int */);

/* called from FILE-SYSPROC */
extern double g2ext_local_time_as_float(/* void */);
extern long g2ext_is_dst_used();

/* called from FILTERS */
extern long g2ext_set_inherit_stdio_handles(/* long */);

/* called from CYCLES */
extern void g2ext_network_io_trace_note(/* char * */);

/* called from STACK-KERN */
extern void /* g2rtl_ */ bytecode_mvs_2(/* void ** */);
extern void /* g2rtl_ */ bytecode_mvs_3(/* void **, void ** */);

/* called from SAX */
/* long int is the same type as long; the functions declared to return long int
   actually return G2pointers. */
extern long g2xml_get_event_callback_type(/* G2pointer */);
extern long g2xml_events_ready(/* G2pointer */);
extern long int g2xml_get_event_callback_data(/* G2pointer */);
extern void g2xml_dispose_event_callback_data(/* G2pointer */);
extern void g2xml_dispose_event(/* G2pointer */);
extern long g2xml_element_name_size(/* G2pointer */);
extern long g2xml_start_element_atts_num(/* G2pointer */);
extern long g2xml_start_element_att_size(/* G2pointer, long */);
extern long g2xml_fill_element_name_buffer(/* G2pointer, char *, long, long */);
extern long g2xml_fill_start_element_att_buffer(/* G2pointer, char *,
						   long, long */);
extern long g2xml_characters_or_comment_size(/* G2pointer */);
extern long g2xml_fill_characters_or_comment_buffer(/* G2pointer, char *, long, long */);
extern long g2xml_error_size(/* G2pointer */);
extern long g2xml_fill_error_buffer(/* G2pointer, char *, long, long  */);
extern long int g2xml_make_parser_context(/* void */);
extern long g2xml_parse_chunk(/* G2pointer, char *, long, long */);
extern long g2xml_parse_file(/* G2pointer, const char * */);
extern long int g2xml_first_sax_event(/* G2pointer */);
extern void g2xml_cleanup_parser(/* G2pointer */);

/* the rest of the Lisp-XML API -- many called from DOM */
extern long g2xml_attr_get_name_size ( /* G2pointer attr */ );
extern void g2xml_element_get_attribute_in_buffer ( /* ... */ );
extern long g2xml_element_get_attribute_size ( /* G2pointer element, char *name */ );
extern long g2xml_element_has_attribute_p ( /* G2pointer element, char *name */ );
extern long g2xml_node_local_name_size ( /* G2pointer node */ );
extern long g2xml_get_content_size ( /* G2pointer node */ );
extern long g2xml_get_line ( /* G2pointer node */ );
extern long int g2xml_node_namespace ( /* G2pointer node */ );
extern void g2xml_node_set_namespace ( /* G2pointer node, G2pointer ns */ );
extern long int g2xml_node_lookup_namespace ( /* G2pointer node, char *prefix */ );
extern long g2xml_namespace_get_prefix_size ( /* G2pointer xml_namespace */ );
extern long g2xml_namespace_get_uri_size ( /* G2pointer xml_namespace */ );
extern long g2xml_namespace_list_length ( /* G2pointer namespace_list */ );
extern long int g2xml_node_child_nodes ( /* G2pointer node */ );
extern long g2xml_node_has_attributes_p ( /* G2pointer node */ );
extern long g2xml_node_has_child_nodes_p ( /* G2pointer node */ );
extern long int g2xml_node_last_child ( /* G2pointer node */ );
extern long g2xml_node_list_length ( /* G2pointer node_list */ );
extern long int g2xml_node_next_sibling ( /* G2pointer node */ );
extern long int g2xml_node_parent_node ( /* G2pointer node */ );
extern long int g2xml_node_previous_sibling ( /* G2pointer node */ );
extern long g2xml_node_type ( /* G2pointer node */ );
extern long g2xml_write_file ( /* G2pointer doc, char *path */ );
extern long int g2xml_write_buffer ( /* G2pointer doc */ );
extern long g2xml_buffer_get_content_size ( /* G2pointer buf */ );
extern void g2xml_buffer_get_content_in_buffer ( /* G2pointer buf, char *buffer,
						    long size, long start */ );
extern void g2xml_dispose_buffer ( /* G2pointer buf */ );
extern long int g2xml_create_document ( /*  */ );
extern long int g2xml_element_get_attribute_node ( /* G2pointer element, char *name */ );
extern long int g2xml_element_get_namespace_list ( /* ... */ );
extern long int g2xml_namespace_list_item ( /* G2pointer namespace_list, long index */ );
extern long int g2xml_next_sax_event ( /* G2pointer event_index */ );
extern long int g2xml_node_attributes ( /* G2pointer node */ );
extern long int g2xml_node_list_item ( /* G2pointer node_list, long index */ );
extern long int g2xml_node_new_child ( /* ... */ );
extern long int g2xml_element_new_namespace ( /* ... */ );
extern long int g2xml_peek_first_sax_event ( /* G2pointer wrapper_index */ );
extern long int g2xml_read_file ( /* char *path */ );
extern long int g2xml_read_string ( /* char *string, int len */ );
extern long int g2xml_next_error ( /* void */ );
extern long g2xml_error_get_message_size ( /* G2pointer error */ );
extern void g2xml_error_get_message_in_buffer ( /* G2pointer error, ... */ );
extern long g2xml_error_get_filename_size ( /* G2pointer error */ );
extern void g2xml_error_get_filename_in_buffer ( /* G2pointer error, ... */ );
extern long g2xml_error_get_line_number ( /* G2pointer error */ );
extern long g2xml_error_get_column_number ( /* G2pointer error */ );
extern void g2xml_dispose_error ( /* G2pointer error */ );
extern void g2xml_attr_get_name_in_buffer ( /* ... */ );
extern void g2xml_cleanup_all_sax_parsers ( /* void */ );
extern void g2xml_dispose_document ( /* G2pointer doc */ );
extern void g2xml_dispose_pointer ( /* G2pointer pointer */ );
extern void g2xml_element_set_attribute ( /* ... */ );
extern void g2xml_node_local_name_in_buffer ( /* ... */ );
extern void g2xml_get_content_in_buffer ( /* ... */ );
extern void g2xml_init_sax ( /* void */ );
extern void g2xml_keep_blanks_default ( /* long x */ );
extern void g2xml_namespace_get_prefix_in_buffer ( /* ... */ );
extern void g2xml_namespace_get_uri_in_buffer ( /* ... */ );
extern void g2xml_node_add_content ( /* ... */ );
extern void g2xml_node_add_comment ( /* ... */ );
extern void g2xml_test_version ( /* void */ );
extern long g2xml_document_validate ( /* G2pointer doc,G2pointer schema_doc */);
extern long g2xml_validate ( /* long */);

/* called from DEBUG */
extern void g2ext_puts ( /* char * */ );
extern long g2ext_performance_frequency ( /* long */ );
extern double g2ext_emit_performance_counter ( /* unsigned short, long */ );
extern double g2ext_report_performance_counter ( /* void */ );

/* called from CONTROLS */
extern long g2ext_run_telewindows_here ();

/* called from COMMANDS2 */
extern long g2ext_get_pixmap_bits(/* long, long, long, long, unsigned char* */);
extern long g2ext_get_truecolor_pixel(/* unsigned short *wide_string, long x, long y, long stride */);
extern int g2ext_memcmp(/* const void* buf1, const void* buf2, size_t count */);
extern long g2ext_get_root_window(/*void*/);


/* called from SQNCS2 */
extern long g2_check_authentification_ldap( /* char *login, char *mode */ );
extern long g2_check_user_ldap( /* char *defaultUser, char *login, char *password */ );
extern long g2_check_ldap_mode();

/* called from KB-LOAD2 */
extern long g2ext_characters_cipher(long code, long refvar, long direction);
extern long g2ext_eval_base_ref_val(long intial_value);

/* called from VIEWS */
extern int g2ext_get_hbu ();
extern int g2ext_get_vbu ();

#ifdef FUNCTION_TRACE
#define x_note_fn_call(file_index,fn_index) x_note_fn_call_1((file_index<<16)+fn_index)
extern void x_note_fn_call_1();
extern void x_note_fn_table_size();  /* called from names.c */
#else
#define x_note_fn_call(file_index,fn_index)
#define x_note_fn_table_size(size)
#endif

#if defined(WIN32)
#define DLLEXPORT __declspec( dllexport )
#else
#define DLLEXPORT
#endif

#if defined(WIN32)
/* On Windows, some of the macros in <ctype.h> expand into code which doesn't
 * work with the MFC version of libc.  We want to be able to link against MFC
 * or non-MFC, without having to recompile.  Defining _CTYPE_DISABLE_MACROS
 * achieves that goal.  -jv, 2/12/04
 */
#ifndef _CTYPE_DISABLE_MACROS
#  define _CTYPE_DISABLE_MACROS
#endif

/* warning C4102: '...' : unreferenced label
 *   These warnings come up because of how loop is implemented in Lisp.  There's
 *   really nothing Chestnut could do about it, and it would be extraordinarily
 *   pointless to try to change our implementation of loop to avoid it.  This
 *   is a completely harmless warning
 */
#  pragma warning( disable : 4102 )

/* warning C4554: '..' : check operator precedence for possible error;
 *                       use parentheses to clarify precedence
 *   I'm sympathetic to this warning; I agree, it's good practice to use
 *   parentheses rather than rely on ones own knowledge of the seventeen levels
 *   of precedence in C.  But this is generated code that's been tested for
 *   many years.  I'm quite sure Chestnut gets it right.
 */
#  pragma warning( disable : 4554 )

/* warning C4244: '=' : conversion from '... ' to '...', possible loss of data
 *   I'm still not sure exactly what Lisp code generates C code which causes
 *   these warnings, but I am sure that we're not worried about them.
 */
#  pragma warning( disable : 4244 )

/* warning C4715: '...' : not all control paths return a value
 * warning C4716: '...' : must return a value
 *   Generally, these are valuable warnings.  If a C function is declared to
 *   return a value, and it doesn't, or might not, that could be a serious
 *   problem.  A caller of such a function might be getting garbage out of the
 *   return value register.  However, this is Lisp, and Gensym Lisp at that.
 *   Our Lisp functions _always_ return a value.  I believe the only instances
 *   in which we see these warnings are where we do throws.  "throw" is
 *   implemented as a longjmp in rtl, and if the compiler knew we were doing a
 *   longjmp it wouldn't complain, but it doesn't know.  I feel pretty confident
 *   in saying that these warnings in translated Lisp code are irrelevant.
 */
#  pragma warning( disable : 4715 4716 )

/* warning C4101: '...' : unreferenced local variable
 *   This also comes up due to loop sometimes.  Yet, there are other reasons why
 *   we get this warning.  I'm not so sure we should *always* ignore it.
 *   However, we *have* been always ignoring it, so there's no point in having
 *   it clutter up the output.  For now, turn it off.
 */
#  pragma warning( disable : 4101 )

/* warning C4013: '...' undefined; assuming extern returning int
 *   These are irritating and clutter up our output.  Nevertheless, they can
 *   be quite important.  If the function it's assuming returns int actually
 *   returns a float, things can break in a very bad way which is difficult
 *   to track down.  We must provide explicit declarations in this file for all
 *   hand-written C files called from translated C files.  In fact, once we
 *   have all the prototypes committed, we should probably go in the other
 *   direction and treat this particular warning as an error.  To reiterate:
 *
 *   WE DO NOT IGNORE THIS WARNING!!!
 */
#  pragma warning( default : 4013 )
#endif


extern Area Temporary_area;
extern Object Plist_of_nil;

#ifdef _INTELC32_
#define sleep(a) (a)
#endif

#define inline_c_call_8(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8) \
  (*((Object(*)())fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)


#define GENSYM_HEADER_SIZE 3
#define inline_funcall_0(fptr) (*SI_FUNCTION_ENTRY(fptr))()
#define inline_funcall_1(fptr,arg1) (*SI_FUNCTION_ENTRY(fptr))(arg1)
#define inline_funcall_2(fptr,arg1,arg2)(*SI_FUNCTION_ENTRY(fptr))(arg1,arg2)
#define inline_funcall_3(fptr,arg1,arg2,arg3)(*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3)
#define inline_funcall_4(fptr,arg1,arg2,arg3,arg4)(*SI_FUNCTION_ENTRY(fptr)) \
  (arg1,arg2,arg3,arg4)
#define inline_funcall_5(fptr,arg1,arg2,arg3,arg4,arg5)(*SI_FUNCTION_ENTRY(fptr)) \
  (arg1,arg2,arg3,arg4,arg5)
#define inline_funcall_6(fptr,arg1,arg2,arg3,arg4,arg5,arg6) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6)
#define inline_funcall_7(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7)
#define inline_funcall_8(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
#define inline_funcall_9(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
#define inline_funcall_10(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10)
#define inline_funcall_11(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11)
#define inline_funcall_12(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12) \
  (*SI_FUNCTION_ENTRY(fptr))(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12)
#define inline_funcall_13(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13) \
  (*SI_FUNCTION_ENTRY(fptr)) \
  (arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13)
#define inline_funcall_14(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14) \
  (*SI_FUNCTION_ENTRY(fptr)) \
  (arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14)
#define inline_funcall_15(fptr,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15) \
  (*SI_FUNCTION_ENTRY(fptr)) \
  (arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15)




/* The following macro is called from glbasics, and is used to fool the
 * translator into allowing us to return from a function without setting the
 * Values_count variable.  This should be removed when Chestnut gives us this
 * functionality built-in to the translator.  -jra 11/4/93 */ 

#define GENSYM_RETURN_ONE(x) return (x)




/* The following macro is used to produce a long which is the hash number for a
 * symbol.  Since we have turned off the garbage collectors, we never relocate
 * symbols, and therefore we can base a hash number on the address of the
 * symbol.  Note that Chestnut symbol addresses are always multiples of 8
 * because of the alignment settings we have chosen.  Further note that pointers
 * and longs have a greater range than fixnums, so this value must be masked
 * with most positive fixnum before it can be used.  This is done from the
 * caller of this operation, sxhash-symbol, on the Lisp side.  -jra 11/4/93 */

#define SXHASH_SYMBOL_1(x) ((SI_Long)(x) >> 3)



/* This macro is used to gain access to the Chestnut library function PCTpointer
 * (%pointer), which returns the address of a lisp object as an integer, possibly
 * a bignum.  It is needed by the click tricks in glbasics. -fmw, 8/19/94 */

#define PCT_POINTER_1(x) (PCTpointer(x))



/* The following macro implements an inline fetch of the property list of
 * symbols.  Note that this must be called with an argument that can be
 * evaluated more than once.  See the documentation for symbol-plist-for-lookup
 * for details of why we had to reimplement this operation.  -jra 12/3/93
 */

#define INLINE_SYMBOL_PLIST(symbol) ((symbol) == NIL ? SI_Plist_of_nil : SI_SYMBOL_PLIST(symbol))
extern Object SI_Plist_of_nil;


#define INLINE_CACHED_SYMBOL_NAME(symbol) SI_symbol_field(symbol, SI_SymName)


/* The following macro implements an inline type check of whether or not the
 * given item is a simple-array of double-floats.  This is used for the
 * implementation of float-vector-p, used often as part of the check for
 * managed-float-p.  -jra & ghw 4/12/95
 */

#define INLINE_DOUBLE_FLOAT_VECTOR_P(symbol) \
    (SIMPLE_ARRAY_ANY_1_P(symbol) && ((int)SI_ARRAY_ETYPE(symbol) == A_DOUBLE_FLOAT))

#define INLINE_LONG_VECTOR_P(symbol) \
    (SIMPLE_ARRAY_ANY_1_P(symbol) && ((int)SI_ARRAY_ETYPE(symbol) == A_BYTE_64))

#define INLINE_LONG_P(symbol) LONG64P(symbol)

/* The follwoing macro implements an inline type check for (simple-array
   (unsigned-byte 16)), used as the implementation of wide-string-p.  -jra
   5/24/96 */

#define INLINE_UNSIGNED_BYTE_16_VECTOR_P(symbol) \
    (SIMPLE_ARRAY_ANY_1_P(symbol) && ((int)SI_ARRAY_ETYPE(symbol) == A_UNSIGNED_BYTE_16))

/* The following macro implements an inlined copy optimization for double-byte
 * vectors.  This is used by the byte-vector-16 facility in UTILITIES0.  -jra
 * 5/25/96
 *
 * GENSYMCID-1852: Regression test suite (corrupt-test.kb) failed on Linux
 *
 * The macro may be used on overlapping areas, but `memcpy' doesn't support that.
 * On Linux with glibc version >= 2.13 this became a real issue, and the solution
 * (at C side) is to use (slower but safe) memmove() instead. The Lisp version
 * (used when G2 is running directly in Lisp environments) is fixed too.
 * 
 * -- Srdjan, Denis and Chun, Aug 2, 2016.
 */

#define INLINE_COPY_BYTE_VECTOR_16_PORTION(s,si,t,ti,c) \
  memmove((void *)&(t[ti]),(void *)&(s[si]),(c)*2)

/* The following macro is a variant of the above macro. It's declared in Lisp in
   GSI-COMMON via def-inlined-pseudo-function.  What's special about it is that
   the source string s is already expected to be a C wide string, and the
   calling framework (def-inlined-pseudo-function) will not have wrapped any
   modifying or casting code around it, though it will have done so to fix all
   the other arguments. This then will just cast the source argument s to
   (unsigned short *) to keep the compiler happy.

   This was recently added to GSI-COMMON to optimize
   c-wide-string-to-text-string, which is at the heart of the very heavily used
   gsi_set_str() GSI API function.  (MHD 2/27/04) */

#define inline_copy_byte_vector_16_portion_c_to_lisp(s,si,t,ti,c) \
  memcpy((void *)&(t[ti]), \
	 (void *)&(((unsigned short *)s)[si]), \
	 (c)*2)



/* The following macro is a variant of the above macro.  It's for copying wide
   strings efficiently into 8-bit-byte arrays.  ICP buffers require ICP bytes to
   be stored in big-endian order.  If this platform is big-endian, then we can
   use memcpy to efficiently copy the bytes using a low-level memory move
   operation.  Otherwise, we use the function g2rtl_copy_widestr_to_icpbuf(),
   defined in rtl/c/gensym.c, to copy the 16-bit values as 8-bit bytes in the
   proper sequence.  Note that the code that uses this is the ICP writer for
   wide-string, defined in INT3A (lisp/int3a.lisp).

   The non-big-endian version defined below has an unused reference version in
   ext/c/cprim.c: g2ext_copy_widestr_to_icpbuf(), which can be used for testing,
   or some other purpose. (MHD 3/1/04) */

#if RTL_BIG_ENDIAN
#define inline_copy_widestr_to_icpbuf(s,si,t,ti,c) \
  memcpy((void *)&(t[ti*2]),(void *)&(s[si]),(c)*2)
#else
#define inline_copy_widestr_to_icpbuf(s,si,t,ti,c) \
  g2rtl_copy_widestr_to_icpbuf((s), (si), (t), (ti), (c))
#endif





/* The following macro implements an inlined compare optimization for double-byte
 * vectors.  This is used by the byte-vector-16 facility in UTILITIES0.  -mhd
 * 6/27/96
 */

#define INLINE_COMPARE_BYTE_VECTOR_16_PORTION(s,si,t,ti,c) \
  memcmp((void *)&(t[ti]),(void *)&(s[si]),(c)*2)

#ifdef DEBUG_CONSING
#define inline_note_allocate_cons(cons,pool) g2ext_note_allocate_cons(cons,pool)
#define inline_note_reclaim_cons(cons,pool) g2ext_note_reclaim_cons(cons,pool)
#define inline_debugging_consing() 1
#else
#define inline_note_allocate_cons(cons,pool)
#define inline_note_reclaim_cons(cons,pool)
#define inline_debugging_consing() 0
#endif

/*
 * The following macros support GSI API and call-in functions.
 */

#ifdef USE_PROTOTYPES
#define GSI_CALLBACK_PROTO(proto) proto
#else
#define GSI_CALLBACK_PROTO(proto) ()
#endif

#define inline_call_gsi_set_up(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_get_tcp_port(fn) \
 (((long (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_pause_context(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_resume_context(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_start_context(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_reset_context(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_shutdown_context(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_g2_poll(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_watchdog_function(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())
#define inline_call_gsi_idle(fn) \
 (((void (*)GSI_CALLBACK_PROTO((void)))(fn))())

#define inline_call_gsi_read_callback(fn,context,state) \
 (((void (*)GSI_CALLBACK_PROTO((long, long)))(fn))(context,state))
#define inline_call_gsi_write_callback(fn,context,state) \
 (((void (*)GSI_CALLBACK_PROTO((long, long)))(fn))(context,state))
#define inline_call_gsi_open_fd(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long)))(fn))(fd))
#define inline_call_gsi_close_fd(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long)))(fn))(fd))
#define inline_call_gsi_writing_fd(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long)))(fn))(fd))
#define inline_call_gsi_not_writing_fd(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long)))(fn))(fd))
#define inline_call_gsi_initialize_context(fn,rpis,length) \
 (((long (*)GSI_CALLBACK_PROTO((Object,long)))(fn))(rpis,length))
#define inline_call_gsi_receive_registration(fn,reg) \
 (((void (*)GSI_CALLBACK_PROTO((Object)))(fn))(reg))
#define inline_call_gsi_receive_deregistrations(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object, long)))(fn))(regis,count))
#define inline_call_gsi_get_data(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object, long)))(fn))(regis,count))
#define inline_call_gsi_set_data(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object, long)))(fn))(regis,count))
#define inline_call_gsi_receive_message(fn,message,length) \
 (((void (*)GSI_CALLBACK_PROTO((Object, long)))(fn))(message,length))
#define inline_call_gsi_run_state_change(fn,direction,type,name) \
 (((void (*)GSI_CALLBACK_PROTO((long, long, Object)))(fn))(direction,type,name))
#define inline_call_gsi_error_handler(fn,context,code,message) \
 (((void (*)GSI_CALLBACK_PROTO((long, long, Object)))(fn))(context,code,message))
#define inline_call_gsi_missing_procedure_handler(fn,name) \
 (((void (*)GSI_CALLBACK_PROTO((Object)))(fn))(name))

/*
#define inline_call_gsi_read_callback_non_c(fn,context,state) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *)))(fn))((long *)&context,(long *)&state))
#define inline_call_gsi_write_callback_non_c(fn,context,state) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *)))(fn))((long *)&context,(long *)&state))
#define inline_call_gsi_open_fd_non_c(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long *)))(fn))((long *)&fd))
#define inline_call_gsi_close_fd_non_c(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long *)))(fn))((long *)&fd))
#define inline_call_gsi_initialize_context_non_c(fn,rpis,length) \
 (((long (*)GSI_CALLBACK_PROTO((Object *,long *)))(fn))(&rpis,(long *)&length))
#define inline_call_gsi_receive_registration_non_c(fn,reg) \
 (((void (*)GSI_CALLBACK_PROTO((Object *)))(fn))(&reg))
#define inline_call_gsi_receive_deregistrations_non_c(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(&regis,(long *)&count))
#define inline_call_gsi_get_data_non_c(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(&regis,(long *)&count))
#define inline_call_gsi_set_data_non_c(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(&regis,(long *)&count))
#define inline_call_gsi_receive_message_non_c(fn,message,length) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(&message,(long *)&length))
#define inline_call_gsi_run_state_change_non_c(fn,direction,type,name) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *, Object *)))(fn))((long *)&direction,(long *)&type,&name))
#define inline_call_gsi_error_handler_non_c(fn,context,code,message) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *, Object *)))(fn))((long *)&context,(long *)&code,&message))
#define inline_call_gsi_missing_procedure_handler_non_c(fn,name) \
 (((void (*)GSI_CALLBACK_PROTO((Object *)))(fn))(name))
 */

#define inline_call_gsi_read_callback_non_c(fn,context,state) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *)))(fn))((long *)context,(long *)state))
#define inline_call_gsi_write_callback_non_c(fn,context,state) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *)))(fn))((long *)context,(long *)state))
#define inline_call_gsi_open_fd_non_c(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long *)))(fn))((long *)fd))
#define inline_call_gsi_close_fd_non_c(fn,fd) \
 (((void (*)GSI_CALLBACK_PROTO((long *)))(fn))((long *)fd))
#define inline_call_gsi_initialize_context_non_c(fn,rpis,length) \
 (((long (*)GSI_CALLBACK_PROTO((Object *,long *)))(fn))(rpis,(long *)length))
#define inline_call_gsi_receive_registration_non_c(fn,reg) \
 (((void (*)GSI_CALLBACK_PROTO((Object *)))(fn))(reg))
#define inline_call_gsi_receive_deregistrations_non_c(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(regis,(long *)count))
#define inline_call_gsi_get_data_non_c(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(regis,(long *)count))
#define inline_call_gsi_set_data_non_c(fn,regis,count) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(regis,(long *)count))
#define inline_call_gsi_receive_message_non_c(fn,message,length) \
 (((void (*)GSI_CALLBACK_PROTO((Object *, long *)))(fn))(message,(long *)length))
#define inline_call_gsi_run_state_change_non_c(fn,direction,type,name) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *, Object *)))(fn))((long *)direction,(long *)type,name))
#define inline_call_gsi_error_handler_non_c(fn,context,code,message) \
 (((void (*)GSI_CALLBACK_PROTO((long *, long *, Object *)))(fn))((long *)context,(long *)code,message))
#define inline_call_gsi_missing_procedure_handler_non_c(fn,name) \
 (((void (*)GSI_CALLBACK_PROTO((Object *)))(fn))(name))


/* Conversion between fixnums and longs:
 */

#define inline_get_long_from_fixnum(fixnum) ((Object)(IFIX(fixnum)))

/* Pointer manipulation:
 */

#define inline_dereference_c_pointer(pointer) \
    ( (Object) *((Object *)pointer) )

#define inline_increment_c_pointer(pointer) \
    ( (Object *)((char *)(pointer) + (sizeof(Object)) ) ) 

#define inline_assign_value_to_c_pointer(c_pointer, value) \
    ((*((Object *)c_pointer)) = (value))

#define inline_assign_fixnum_to_c_pointer(c_pointer, value) \
    ((*((SI_Long *)c_pointer)) = ((SI_Long)(IFIX(value)))  )

#define inline_assign_double_to_c_pointer(double_pointer, double_float_value) \
    ((*((double *)double_pointer)) = IDOUBLE(double_float_value))

#define inline_displace_to_slot(pointer,slot_count) \
    ((Object *)((char *)(pointer) + \
                ((GENSYM_HEADER_SIZE+IFIX(slot_count)) * sizeof(Object) )))

#define inline_get_address_of_object(object) (&(object))

/* jh, 5/24/96.  Not used yet, but may come in handy someday. */
#define inline_deref_object(object) (*((SI_Long *) object)) 

#define inline_identity(object) (object)

#define inline_assign_ref(ref, new_value) ((* ((SI_Long *) ref)) = (new_value))

/* Array-accessing functions:
 */

/* new (corrected) streamlined version of the inline-extract-c-array fn
 * from Rick @ Chestnut. 
 */
#define inline_extract_c_array(lisp_array, magic_header_offset) \
    ((Object *)SI_array_contents(lisp_array) + IFIX(magic_header_offset))

#define inline_extract_c_long_array(lisp_array) \
    ((Object)SI_array_contents(lisp_array))

#define inline_extract_c_double_array(lisp_array) \
    ((Object)SI_array_contents(lisp_array))

#define inline_extract_c_string(lisp_string) \
    (Object)SI_array_contents(lisp_string)

#define inline_extract_c_wide_string(lisp_string) \
    (Object)SI_array_contents(lisp_string)

static SI_PVT_Object prototype;

#define inline_get_array_from_c(c_array, magic_header_offset) \
    ( SI_SET_TAG((char *)c_array -  \
       ( ((char *)&prototype.contents - (char *)&prototype) + \
	( IFIX(magic_header_offset) * sizeof(Object) )), SI_ARRAY_TAG ) )

#define inline_get_c_long_element(c_array, index) \
    (((long *)(c_array))[index])

#define inline_get_c_double_element(c_array, index) \
    (((double *)(c_array))[index])

#define inline_gsi_get_magic_header(c_array)  \
    *((Object *)((char *)(c_array) - sizeof(Object)))

/* String access functions:
 */

static SI_PVT_Char   SI_lisp_gensym_string_prototype;
static SI_PVT_Ushort SI_lisp_wide_string_prototype;

#define inline_restore_lisp_gensym_string(c_string) \
    (Object) ( (char *)c_string - \
               ((char *)&SI_lisp_gensym_string_prototype.contents - \
                (char *)&SI_lisp_gensym_string_prototype) )

#define inline_restore_lisp_text_string(c_wide_string) \
    (Object) ( (char *)c_wide_string - \
               ((char *)&SI_lisp_wide_string_prototype.contents - \
                (char *)&SI_lisp_wide_string_prototype) )

#define inline_get_c_string_element(c_string, index) \
    CHAR_TO_CHARACTER(((char *)(c_string))[FIXNUM_TO_LONG(index)])

#define inline_get_c_wide_string_element(c_string, index) \
    FIX(((short *)(c_string))[FIXNUM_TO_LONG(index)])

#define inline_get_c_char_ptr_element(c_array, index) \
    ((Object)((char **)(c_array))[FIXNUM_TO_LONG(index)])

#define inline_get_c_wide_char_ptr_element(c_array, index) \
    ((Object)((short **)(c_array))[FIXNUM_TO_LONG(index)])

#define inline_get_length_of_c_string(c_string) \
    FIX((SI_Long)(strlen((char *)(c_string))))

#define inline_get_length_of_c_wide_string(c_wide_string) \
    FIX((SI_Long)(g2ext_w16strlen((short *)(c_wide_string))))

typedef struct {
    SI_Header h;
    Object *location;
#if SI_SUPPORT_THREAD
    short local_count[VALUE_CELL_SLOTS];
    Object *local_location[VALUE_CELL_SLOTS];
#endif
} SI_Value_cell;

#define VALUE_CELL_LOCATION(a)  SI_STORED_OBJECT_FIELD(a, SI_Value_cell, location)

#if SI_SUPPORT_THREAD
#define VALUE_CELL_LOCAL_COUNT(a, index) \
    SI_STORED_OBJECT_FIELD(a, SI_Value_cell, local_count)[index]
#define VALUE_CELL_LOCAL_LOCATION(a, index) \
    SI_STORED_OBJECT_FIELD(a, SI_Value_cell, local_location)[index]
#endif

#define inline_symbol_value_location(symbol) \
    (Object)(SI_symbol_field(symbol, SI_SymValLoc)?\
             VALUE_CELL_LOCATION(SI_symbol_field(symbol, SI_SymValLoc)) : Nil)

#define inline_symbol_function_location(symbol) \
    (Object)((SI_symbol_field(symbol, SI_SymFn)!= UNBOUND)?\
             (Object) SI_FUNCTION_ENTRY(SI_symbol_field(symbol, SI_SymFn)) : Nil)

#define inline_get_run_time_function_array_size() 6

#define inline_get_run_time_function(i) \
 (i==0?(Object)cdouble_to_double:\
 (i==1?(Object)length:\
 (i==2?(Object)SI_Plist_of_nil:\
 (i==3?(Object) /* g2rtl_ */ bytecode_mvs_3:\
 (i==4?(Object)funcall2:\
 (i==5?(Object) /* g2rtl_ */ bytecode_mvs_2:\
 0))))))

extern Object gsi_api_function_array;

#define inline_gsi_api_function_array() gsi_api_function_array


/* GSI RPC support:
 */

#if defined(__STDC__) && !defined(_IBMR2)
#define GSI_API_PROTO(args) args
#else
#define GSI_API_PROTO(args) ()
#endif

typedef void (*gsi_rpc_local_fn_type) 
   GSI_API_PROTO(( Object rpc_arguments, long count, Object call_handle ));

#define inline_c_function_call(function, arguments, count, call_handle) \
    ((gsi_rpc_local_fn_type)(function))(arguments, count, call_handle)

typedef void (*gsi_rpc_receiver_fn_type) 
   GSI_API_PROTO(( Object rpc_arguments, long count ));

#define inline_c_return_function_call(function, arguments, count) \
    ((gsi_rpc_receiver_fn_type)(function))(arguments, count)

typedef void (*gsi_rpc_receiver_with_call_index_fn_type) 
   GSI_API_PROTO(( Object rpc_arguments, long count, long call_index ));

#define inline_c_return_function_call_with_index(function, arguments, count, call_index) \
    ((gsi_rpc_receiver_with_call_index_fn_type)(function))(arguments, count, (long)(call_index))


typedef void (*gsi_rpc_local_fn_ud_type) 
   GSI_API_PROTO(( Object user_data, Object rpc_arguments, long count, Object call_handle ));

#define inline_c_function_call_user_data(function, user_data, arguments, count, call_handle) \
    ((gsi_rpc_local_fn_ud_type)(function))(user_data, arguments, count, call_handle)

typedef void (*gsi_rpc_receiver_fn_ud_type) 
   GSI_API_PROTO(( Object user_data, Object rpc_arguments, long count ));

#define inline_c_return_function_call_user_data(function, user_data, arguments, count) \
    ((gsi_rpc_receiver_fn_ud_type)(function))(user_data, arguments, count)

typedef void (*gsi_rpc_receiver_with_call_index_fn_ud_type) 
   GSI_API_PROTO(( Object user_data, Object rpc_arguments, long count, long call_index ));

#define inline_c_return_function_call_with_index_and_user_data(function, user_data, arguments, count, call_index) \
    ((gsi_rpc_receiver_with_call_index_fn_ud_type)(function))(user_data, arguments, count, (long)(call_index))

#define inline_get_c_rpc_receiver_function(fn) ((Object)(SI_FUNCTION_ENTRY(fn)))

#define inline_get_function_address(fn) ((SI_Long)(SI_FUNCTION_ENTRY(fn)))

/***********************************************************************
 *
 *   Float conversion for VAX platform is implemented below.  Where no
 *   conversion is appropriate, the macros do nothing.  -paf! 19apr95
 *
 *   See ext/c/cprim.c for the conversion functions.-rh 12jan96
 *
 ***********************************************************************/

/* For testing */
#define SUPPORT_ALPHA_VMS_GFLOATS

#define inline_convert_to_local_float_format(double_float,use_gfloats_p)   \
     double_float
#define inline_convert_from_local_float_format(double_float,use_gfloats_p)   \
     double_float
#define inline_maybe_swap_float_bytes_for_alpha_gfloats(double_float,use_gfloats_p) \
     double_float


#if defined(WIN32)
#  include <float.h>
#  include <string.h>
#  define inline_nanp_for_comparison(arg) _isnan(arg)
#else
#  if 0
#    define inline_nanp_for_comparison(arg) isnan(arg)
#  else
/* not needed for platforms that have compilers that handle nans as args to comparitors */
#    define inline_nanp_for_comparison(arg) 0
#  endif
#endif

#define format_lite_printf_0(str) ((Object)printf(str))
#define format_lite_printf_1(str,a1) ((Object)printf(str,a1))
#define format_lite_printf_2(str,a1,a2) ((Object)printf(str,a1,a2))
#define format_lite_printf_3(str,a1,a2,a3) ((Object)printf(str,a1,a2,a3))
#define format_lite_printf_4(str,a1,a2,a3,a4) ((Object)printf(str,a1,a2,a3,a4))
#define format_lite_printf_5(str,a1,a2,a3,a4,a5) \
  ((Object)printf(str,a1,a2,a3,a4,a5))
#define format_lite_printf_6(str,a1,a2,a3,a4,a5,a6) \
  ((Object)printf(str,a1,a2,a3,a4,a5,a6))
#define format_lite_printf_7(str,a1,a2,a3,a4,a5,a6,a7) \
  ((Object)printf(str,a1,a2,a3,a4,a5,a6,a7))
#define format_lite_printf_8(str,a1,a2,a3,a4,a5,a6,a7,a8) \
  ((Object)printf(str,a1,a2,a3,a4,a5,a6,a7,a8))
#define format_lite_printf_9(str,a1,a2,a3,a4,a5,a6,a7,a8,a9) \
  ((Object)printf(str,a1,a2,a3,a4,a5,a6,a7,a8,a9))
#define format_lite_printf_10(str,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) \
  ((Object)printf(str,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10))

#define force_output_for_format_lite() fflush(stdout)



/* The following macro implements Chestnut's missing ffloor operation, this one
 * returning just the first value. */

#define inline_ffloor_1(a) floor(a)

/* The macro inline_floor_1 takes a double and floors it to a long. */

#define inline_floor_1(a) ((SI_Long)floor(a))

/* The macro inline_fceiling_1 takes a double and returns the ceiling'ed double. */

#define inline_fceiling_1(a) ceil(a)

/* The macro inline_ceiling_1 takes a double and returns the ceiling'ed long. */

#define inline_ceiling_1(a) ((SI_Long)ceil(a))

/* The following macro implements a type coercion from fixnums to raw C doubles.
 * This is called from coerce-to-gensym-float.  -jra 1/26/92 */

#define inline_double_from_fix(x) ((double)IFIX(x))



#ifdef vms
#define g2ext_unix_cmd_with_string_output g2ext_unix_cmd_with_strout
#define g2ext_unix_cmd_with_string_output_and_timeout_callback g2ext_unix_cmd_with_strouttim
#endif


#ifdef labs
#undef labs
#endif

#define labs chestnut_labs
#define G2_defstruct_structure_name_symtab G2_destruct_symtab


/* 
 * jh, 11/11/93.  The new Chestnut translator no longer emits externs for our
 * foreign functions.  (Chestnut's rationale is that it is now possible to
 * declare a C macro as a foreign function and in that case externs wouldn't
 * work.)  So until Chestnut can fix this problem, we will extern all our
 * foreign functions by hand.
 */

/*
 * jh, 7/8/94.  Reviewed that the arguments and return types of all foreign
 * functions have the correct declaration in C.  This is in pursuit of
 * BUG-019-6016, "Chestnut foreign functions shoud take fixnum-long instead of
 * :fixnum-int".  This is important on platforms where ints are not 4 bytes,
 * such as Windows and the AlphaOSF.  
 *
 * Some functions encountered in this review were "opaque", meaning that I did
 * not understand their inner workings well enough to risk a simple textual
 * substitution of "long" for "int".  Opaque functions do things like pass their
 * arguments along to system or X library calls, and for all I know, these calls
 * care a whole lot about the precise size, packing, or layout of their
 * arguments.  The opposite of "opaque" is "transparent".
 *
 * (On the other hand, if the call is goverened by an ANSI argument prototype,
 * the C compiler is required to cast from long to int implicitly, according to
 * Harbison & Steele, 3rd ed, p 252.  But it would be a lot of work to verify or
 * supply a prototype for every platform and for every system call we make.)
 *
 * For each opaque function that had mismatched argument types, (ints vs longs
 * was the only type mismatch I ecountered) I added a block wrapped around the
 * original body of the function that explicitly made the proper casts.  Owners
 * of each function may want to remove this wrapper if they can establish that
 * longs will do as well as ints there.
 *
 * For transparent functions, I simply substituted "long" for "int" argument
 * types.
 *
 * According to Harbison & Steele, 3rd ed., p 253 & 159, it is not necessary to
 * cast the return type explicitly to long in the body of the function doing the
 * return.  Declaring the function to return long is enough.  So I did this for
 * both opaque and tranparent functions.
 *
 * Note that the Lisp side of the foreign function call is properly configured
 * for the "ints vs longs" problem.  The relevant def-gensym-c-function sites
 * use the type keyword :fixnum-int, which gets substituted for the :fixnum
 * keyword in the expansion into Chestnut's tx:def-foreign-function.  And
 * according to the Chestnut 3.1 User Guide, p 94, this keyword expects a long.
 * (All of this despite the "int" in "fixnum-int"!)  
 *
 * So the Lisp side is exonerated from the nagging suspicion that we are
 * promising ints yet delivering longs, and causing unspecified trouble in the
 * bowels of some C function because of it.
 *
 * Incidentally, def-gensym-c-function also substitutes :fixnum for :pointer,
 * thereby explaining all the :pointer arguments in PLATFORMS that are actually
 * fixnums destined to be passed as longs to g2ext_map_g2pointer_to_cpointer().
 *
 * "Intra-ext" references are functions in the /bt/ab/ext/c directory that call
 * one another across file boundaries, as opposed to foreign functions called
 * from the /bt/ab/g2/c directory.  In order to handle intra-ext references
 * properly, I had to add externs to cprim.h, graphics.h. and icp_pvt.h, as well
 * as special-case externs to ripdemo.c, cc_client.c, images.c, and mswindow.c
 *
 * While I was at it, I added commented-out argument prototypes for the foreign
 * functions listed here, in case we ever want to go totally ANSI. */

#if defined(__STDC__)

extern void g2ext_network_io_trace_note(char *note_string);

#else

extern void g2ext_network_io_trace_note();

#endif

#define inline_network_io_trace_note(note) \
  {if(g2ext_network_io_trace_p)g2ext_network_io_trace_note(note);}

extern void *g2ext_saved_backtrace_array[];
extern int g2ext_saved_backtrace_array_fcount;
extern int g2ext_saved_backtrace_array_fsize;
extern int g2ext_network_io_trace_p;
extern int function_tracing_enabled;

#define inline_get_backtrace() \
  function_tracing_enabled = FALSE; \
  g2ext_saved_backtrace_array_fcount = \
    g2ext_save_backtrace_into_array(g2ext_saved_backtrace_array,g2ext_saved_backtrace_array_fsize,0)

#define inline_print_backtrace_into_string(string,offset) \
  g2ext_print_backtrace_into_string((string)+(offset),g2ext_saved_backtrace_array,g2ext_saved_backtrace_array_fcount)

#define MAKE_ATOMIC_REF(o, m)    SI_STAMP(o, m)
#define ATOMIC_REF_OBJECT(r)     SI_UNSTAMP(r)
#define ATOMIC_REF_STAMP(r)      SI_GET_STAMP(r)

#define CAS_SYMBOL(symbol,compare,new_value) \
    compare_and_swap_symval(symbol,compare,new_value)
#define CAS_CAR(cons,compare,new_value) \
    compare_and_swap_car(cons,compare,new_value)
#define CAS_CDR(cons,compare,new_value) \
    compare_and_swap_cdr(cons,compare,new_value)
#define CAS_SVREF(vector,index,compare,new_value) \
    compare_and_swap_svslot(vector,index,compare,new_value)

extern void g2ext_decache_g2pointer();
