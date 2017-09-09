#define G2_51

#ifndef G2_51
#define g2ext_backtrace_frame_base backtrace_frame_base
#define g2ext_backtrace_frame_full_name backtrace_frame_full_name
#define g2ext_backtrace_frame_name backtrace_frame_name
#define g2ext_ci_array ci_array
#define g2ext_disable_network_io_trace disable_network_io_trace
#define g2ext_enable_consing_trace enable_consing_trace
#define g2ext_enable_network_io_backtrace enable_network_io_backtrace
#define g2ext_enable_network_io_trace enable_network_io_trace
#define g2ext_finish_trace_control_handler finish_trace_control_handler
#define g2ext_g2_clock_ticks g2_clock_ticks
#define g2ext_gensym_SIGVTALRM_handler gensym_SIGVTALRM_handler
#define g2ext_get_name_for_function get_name_for_function
#define g2ext_get_trace_function_name get_trace_function_name
#define g2ext_gsi_print_backtrace_flag gsi_print_backtrace_flag
#define g2ext_kept_cons_backtrace_limit kept_cons_backtrace_limit
#define g2ext_lookup_backtrace_frame_index lookup_backtrace_frame_index
#define g2ext_map_g2pointer_to_cpointer map_g2pointer_to_cpointer
#define g2ext_network_io_backtrace_interval network_io_backtrace_interval
#define g2ext_network_io_backtrace_used_p network_io_backtrace_used_p
#define g2ext_network_io_find_leaks network_io_find_leaks
#define g2ext_network_io_one_line_backtrace_p network_io_one_line_backtrace_p
#define g2ext_network_io_print_backtrace network_io_print_backtrace
#define g2ext_network_io_trace_backtrace network_io_trace_backtrace
#define g2ext_network_io_trace_begin network_io_trace_begin
#define g2ext_network_io_trace_enabled_p network_io_trace_enabled_p
#define g2ext_network_io_trace_end network_io_trace_end
#define g2ext_network_io_trace_note network_io_trace_note
#define g2ext_network_io_trace_note_d network_io_trace_note_d
#define g2ext_network_io_trace_note_dd network_io_trace_note_dd
#define g2ext_network_io_trace_note_ddd network_io_trace_note_ddd
#define g2ext_network_io_trace_note_f network_io_trace_note_f
#define g2ext_network_io_trace_note_s network_io_trace_note_s
#define g2ext_network_io_trace_p network_io_trace_p
#define g2ext_note_allocate_cons note_allocate_cons
#define g2ext_note_network_event note_network_event
#define g2ext_note_reclaim_cons note_reclaim_cons
#define g2ext_pc_at_c_gensym_signal_handler pc_at_c_gensym_signal_handler
#define g2ext_print_backtrace_into_string print_backtrace_into_string
#define g2ext_read_function_address_file read_function_address_file
#define g2ext_reset_network_io_trace reset_network_io_trace
#define g2ext_run_command_line cc_run_command_line
#define g2ext_save_backtrace_into_array save_backtrace_into_array
#define g2ext_save_network_io_trace save_network_io_trace
#define g2ext_saved_backtrace_array saved_backtrace_array
#define g2ext_saved_backtrace_array_fcount saved_backtrace_array_fcount
#define g2ext_saved_backtrace_array_fsize saved_backtrace_array_fsize
#define g2ext_start_trace_control_handler start_trace_control_handler
#define g2ext_use_virtual_alarm_p use_virtual_alarm_p
#define g2ext_write_cons_summary write_cons_summary
#define g2ext_write_network_io_trace write_network_io_trace
#define g2int_run_trace_function run_trace_function
#endif

#define TRACE_NETWORK_IO

#define TRACE_READ_BEGIN 2L
#define TRACE_WRITE_BEGIN 3L
#define TRACE_READ_END 4L
#define TRACE_WRITE_END 5L

#ifdef TRACE_NETWORK_IO

#define network_io_trace_begin_read(handle,fd,length) \
   g2ext_network_io_trace_begin(TRACE_READ_BEGIN,handle,fd,length)
#define network_io_trace_begin_write(handle,fd,length) \
   g2ext_network_io_trace_begin(TRACE_WRITE_BEGIN,handle,fd,length)
#define network_io_trace_end_read(handle,fd,read_result,buffer) \
   g2ext_network_io_trace_end(TRACE_READ_END,handle,fd,read_result,buffer)
#define network_io_trace_end_write(handle,fd,write_result,buffer) \
   g2ext_network_io_trace_end(TRACE_WRITE_END,handle,fd,write_result,buffer)

#else

#define network_io_trace_begin_read(handle,fd,length)
#define network_io_trace_begin_write(handle,fd,length)
#define network_io_trace_end_read(handle,fd,read_result,buffer)
#define network_io_trace_end_write(handle,fd,write_result,buffer)

#endif

#if defined(__STDC__) || defined(_MSC_VER)

extern void g2ext_network_io_trace_begin(long type, long handle, long fd, long length);
extern void g2ext_network_io_trace_end(long type, long handle, long fd, long io_result, char *buffer);

extern void g2ext_network_io_trace_note(char *note_string);
extern void g2ext_network_io_trace_note_d(char *note_string,long arg);
extern void g2ext_network_io_trace_note_dd(char *note_string,long arg1,long arg2);
extern void g2ext_network_io_trace_note_ddd(char *note_string,long arg1,long arg2,long arg3);
extern void g2ext_network_io_trace_note_f(char *note_string,double arg);
extern void g2ext_note_network_event(long ecode, long socket_handle);

extern void g2ext_network_io_trace_backtrace(void);
extern void g2ext_reset_network_io_trace(void);

#else

extern void g2ext_network_io_trace_begin();
extern void g2ext_network_io_trace_end();

extern void g2ext_network_io_trace_note();
extern void g2ext_network_io_trace_note_d();
extern void g2ext_network_io_trace_note_dd();
extern void g2ext_network_io_trace_note_f();
extern void g2ext_network_io_trace_note_s();
extern void g2ext_note_network_event();

extern void g2ext_network_io_trace_backtrace();
extern void g2ext_reset_network_io_trace();

#endif

#define SAVED_BACKTRACE_ARRAY_SIZE 20

#if defined(__STDC__) || defined(_MSC_VER)

extern int g2ext_save_backtrace_into_array(void **array, int size, int frames_to_skip);
extern long g2ext_print_backtrace_into_string(char *string, void **array, int frame_count);

#else

extern int g2ext_save_backtrace_into_array();
extern long g2ext_print_backtrace_into_string();

#endif

extern void g2ext_start_trace_control_handler();


/* 
 * Yet Another Tracing Facility
 */

extern void g2pvt_notify_user(const char *fmt, ...);
extern void g2pvt_trace(const char *fmt, ...);
extern void g2pvt_printf(const char *fmt, ...);
extern void g2pvt_puts(const char *str);
