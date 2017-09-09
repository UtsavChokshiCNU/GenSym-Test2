#include "runtime.h"

Object Inside_handle_event = UNBOUND;

long g2int_close_fd_callback(long fd) { return 0L;}

long g2int_open_fd_callback(long fd) { return 0L;}

long g2int_network_event_handler(long event_code, long event_socket_handle,
								 long event_status_code) {
	return 0L;
}

long nms_fetch_help_string(long native_window, long item_id) {
	return 0L;
}

long g2int_run_trace_function() { return 0L;}

long g2int_writing_fd_callback(long fd) { return 0L;}

long g2int_not_writing_fd_callback(long fd) { return 0L;}

long nms_handle_if_flag_bit(long hmenu_high, long hmenu_low, long flag) {
	return 0L;
}

long nms_id_for_menu(long hmenu_high, long hmenu_low) { return 0L;}

long g2int_unix_command_callback() { return 0L;}

long g2int_x_error(long error) { return 0L; }

Object g2int_signal_handler() { return 0;}

Object g2int_signal_handler_for_launch() { return 0;}

Object g2int_service_sigalrm_signal() { return 0;}
