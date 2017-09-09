/*

  Module allegro.c - C callbacks for Allegro Lisp (#+development only)
  Author: Dave Bakhash (consultant)
  Copyright (C) 1986-2017 Gensym Corporation.

  This file has no corresponding header file.  Its purpose in life is 
  to make callbacks into Lisp work, particularly with Allegro Common
  Lisp (ACL).

  This code is a total rewrite and is based on the most recent ACL
  documentation on the foreign function interface.

  The file containing this documentation is at:
  <acl_home>/doc/cl/foreign_functions.htm

  The Lisp file corresponding to this file, which handles the the
  callback overhead for ACL on the Lisp side is found in:
  %SRCBOX%/lisp/allegro.lisp

  --dbakhash 6/8/00

*/

#include <stdio.h>

/* defined in the ACL shared library */
extern void *lisp_call_address(int index);

/* This might not actually be necessary; see comments around main(), below */
extern void g2ext_heap_command_line (int, char **);

/* 
  So, as of 1/17/03, our ext code relies on a _variable_ defined in Lisp.  I'm
  not sure how to export a variable from Allegro, and it might be worthwhile to
  point out that we don't really worry about how to export it from Lucid.  The
  variable is only accessed by Windows-specific C code, so it never gets loaded
  into Lucid.  I might ask Fred to turn the usage into a function call, but it
  seems to be used in a time-critical place.  However, it is actually pretty
  rare that the value will ever be non-zero at the point we check it, and we can
  just let it always be zero as we work on porting to Allegro.  -jv, 12/28/03
 */

int Inside_handle_event = 0;


/*
  To build twfranz.dll, there must be NO unresolved symbols.  Well, WinMain() in
  msmain calls main(), which is defined in tw/c/main.c, and we're not about to
  bring tw/c/main.c into the dll.  We actually don't need WinMain in twfranz.dll
  but I want the diffs to the main sources to be minimal, so anything I can fix
  in Allegro-specific files, I will.  So, stub out main() here.  -jv, 12/30/03
 */

int main (int argc, char **argv)
{
  /* I'm really nowhere close to the point of expecting this to work, but may
   * as well be close to what our real main() does.  Here's essentially the
   * first thing it does:
   */
  g2ext_heap_command_line(argc, argv);

  /* It then does the following, none of which will work here:
     init_top_level();
     userinit();
     launch_telewindows();
  */

  return 0;
}


/*

  The following code sets up the global callback handles and the
  exported C functions which will be defined as foreign functions in
  [Allegro] Common Lisp.  These are used in the initialization steps
  where Lisp sets up for callbacks.

  o The first form in each group defines the global callback handle.
  o The second form of each group defines the C init function called by
    Lisp.
  o The third form of each group defines the actual C interface to the 
    Lisp call.

*/

/*
 * G2INT-X-ERROR
 */
static int g2int_x_error_call_handle = -1;

extern void g2int_x_error_init_handle(int index) {
  g2int_x_error_call_handle = index;
}

extern long g2int_x_error(long error_code) {
  return ((long(*)())lisp_call_address(g2int_x_error_call_handle))(error_code);
}


/*
 * G2INT-SERVICE-SIGALRM-SIGNAL
 */
static int g2int_service_sigalrm_signal_call_handle = -1;

extern void g2int_service_sigalrm_signal_init_handle(int index) {
  g2int_service_sigalrm_signal_call_handle = index;
}

extern long g2int_service_sigalrm_signal() {
  return ((long(*)())lisp_call_address(g2int_service_sigalrm_signal_call_handle))();
}


/*
 * G2INT-SIGNAL-HANDLER
 */
static int g2int_signal_handler_call_handle = -1;

extern void g2int_signal_handler_init_handle(int index) {
  g2int_signal_handler_call_handle = index;
}

extern long g2int_signal_handler() {
  return ((long(*)())lisp_call_address(g2int_signal_handler_call_handle))();
}


/*
 * G2INT-SIGNAL-HANDLER-FOR-LAUNCH
 */
static int g2int_signal_handler_for_launch_call_handle = -1;

extern void g2int_signal_handler_for_launch_init_handle(int index) {
  g2int_signal_handler_for_launch_call_handle = index;
}

extern long g2int_signal_handler_for_launch() {
  return ((long(*)())lisp_call_address(g2int_signal_handler_for_launch_call_handle))();
}


/*
 * G2INT-NETWORK-EVENT-HANDLER
 */
static int g2int_network_event_handler_call_handle = -1;

extern void g2int_network_event_handler_init_handle(int index) {
  g2int_network_event_handler_call_handle = index;
}

extern long g2int_network_event_handler(long event_code, long event_socket_handle, long event_status_code) {
  return ((long(*)())lisp_call_address(g2int_network_event_handler_call_handle))(event_code, event_socket_handle, event_status_code);
}


/*
 * G2INT-OPEN-FD-CALLBACK
 */
static int g2int_open_fd_callback_call_handle = -1;

extern void g2int_open_fd_callback_init_handle(int index) {
  g2int_open_fd_callback_call_handle = index;
}

extern long g2int_open_fd_callback(long fd) {
  return ((long(*)())lisp_call_address(g2int_open_fd_callback_call_handle))(fd);
}


/*
 * G2INT-CLOSE-FD-CALLBACK
 */
static int g2int_close_fd_callback_call_handle = -1;

extern void g2int_close_fd_callback_init_handle(int index) {
  g2int_close_fd_callback_call_handle = index;
}

extern long g2int_close_fd_callback(long fd) {
  return ((long(*)())lisp_call_address(g2int_close_fd_callback_call_handle))(fd);
}


/*
 * G2INT-WRITING-FD-CALLBACK
 */
static int g2int_writing_fd_callback_call_handle = -1;

extern void g2int_writing_fd_callback_init_handle(int index) {
  g2int_writing_fd_callback_call_handle = index;
}

extern long g2int_writing_fd_callback(long fd) {
  return ((long(*)())lisp_call_address(g2int_writing_fd_callback_call_handle))(fd);
}


/*
 * G2INT-NOT-WRITING-FD-CALLBACK
 */
static int g2int_not_writing_fd_callback_call_handle = -1;

extern void g2int_not_writing_fd_callback_init_handle(int index) {
  g2int_not_writing_fd_callback_call_handle = index;
}

extern long g2int_not_writing_fd_callback(long fd) {
  return ((long(*)())lisp_call_address(g2int_not_writing_fd_callback_call_handle))(fd);
}


/*
 * G2INT-RUN-TRACE-FUNCTION
 */
static int g2int_run_trace_function_call_handle = -1;

extern void g2int_run_trace_function_init_handle(int index) {
  g2int_run_trace_function_call_handle = index;
}

extern long g2int_run_trace_function() {
  return ((long(*)())lisp_call_address(g2int_run_trace_function_call_handle))();
}


/*
 * G2INT-UNIX-COMMAND-CALLBACK
 */
static int g2int_unix_command_callback_call_handle = -1;

extern void g2int_unix_command_callback_init_handle(int index) {
  g2int_unix_command_callback_call_handle = index;
}

extern long g2int_unix_command_callback() {
  return ((long(*)())lisp_call_address(g2int_unix_command_callback_call_handle))();
}


/*
 * NMS-FETCH-HELP-STRING
 */
static int nms_fetch_help_string_call_handle = -1;

extern void nms_fetch_help_string_init_handle(int index) {
  nms_fetch_help_string_call_handle = index;
}

extern long nms_fetch_help_string(long native_window, long item_id) {
  return ((long(*)())lisp_call_address(nms_fetch_help_string_call_handle))(native_window, item_id);
}


/*
 * NMS-HANDLE-IF-FLAG-BIT
 */
static int nms_handle_if_flag_bit_call_handle = -1;

extern void nms_handle_if_flag_bit_init_handle(int index) {
  nms_handle_if_flag_bit_call_handle = index;
}

extern long nms_handle_if_flag_bit(long hmenu_high, long hmenu_low, long flag) {
  return ((long(*)())lisp_call_address(nms_handle_if_flag_bit_call_handle))(hmenu_high, hmenu_low, flag);
}


/*
 * NMS-ID-FOR-MENU
 */
static int nms_id_for_menu_call_handle = -1;

extern void nms_id_for_menu_init_handle(int index) {
  nms_id_for_menu_call_handle = index;
}

extern long nms_id_for_menu(long hmenu_high, long hmenu_low) {
  return ((long(*)())lisp_call_address(nms_id_for_menu_call_handle))(hmenu_high, hmenu_low);
}
