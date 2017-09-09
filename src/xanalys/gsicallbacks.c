/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      xanalys/gsicallbacks.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Carl Shapiro, John Valente
 +
 + Description: This module contains the glue code used to allow our C libraries
 +              call into Lispworks
 +
 +
 + Dependencies:
 +      Depends on the Lisp files which define the actual functions
 +
 + Notes:
 +
 + Modifications:
 +   2001/10/17, css: added ext/c/callbacks.c to LISPWORKS_BRANCH
 +     (jv writing comment)
 +   2007/06/27, jv: took old callbacks.c file, included <windows.h>, added
 +      DllMain(), unfortunately added main(), moved the file into the xanalys
 +      directory, and renamed it to include tw.  We will have different
 *      callback files for different systems.
 +   2008/01/21, jv: created gsicallbacks.c from twcallbacks.c
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdio.h>

#ifdef WIN32
#  include <windows.h>
#  define DLLEXPORT __declspec( dllexport )

/* This is the one Lisp *variable* depended on by C.  I haven't figured out
 * how to export it.  For now, it will always be zero.  Fortunately, its use
 * by TW is very limited.  I'll figure out how to export it properly before
 * too long.  -jv, 7/27/07
 */
int Inside_handle_event = 0;
#else
#  define DLLEXPORT
#endif

#ifdef WIN32
BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpvReserved)
{
  switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_DETACH:
      return TRUE;

    default:
      return FALSE;
    }
}


/* This should not be necessary, but g2ext_app_run() in msmain.c calls it.
 * We want to be able to use the standard libraries as built for the C exe,
 * packaged into a DLL, in Lisp.  So we need to stub this out.  There's nothing
 * wrong with having a stub at the point where we essentially start up Chestnut,
 * but it's unfortunate that the stub has to be called "main".  Perhaps
 * g2ext_app_run (which does nothing but call main) could be moved out of
 * libcprim, and *that* could be the function we stub out.  -jv, 7/03/07
 */
int main (int argc, char **argv)
{
  return 0L;
}
#endif

/*
 * G2INT-X-ERROR
 */
static long (*g2int_x_error_call_handle)(long);

DLLEXPORT void g2int_x_error_init_call_handle (long (*fn)(long))
{
  g2int_x_error_call_handle = fn;
}

long g2int_x_error(long error_code)
{
  if (g2int_x_error_call_handle) {
    return (*g2int_x_error_call_handle)(error_code);
  } else {
    fprintf(stderr, "g2int_x_error_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-SERVICE-SIGALRM-SIGNAL
 */
static long (*g2int_service_sigalrm_signal_call_handle)();

DLLEXPORT void g2int_service_sigalrm_signal_init_call_handle (long (*fn)())
{
  g2int_service_sigalrm_signal_call_handle = fn;
}

long g2int_service_sigalrm_signal()
{
  if (g2int_service_sigalrm_signal_call_handle) {
    return (*g2int_service_sigalrm_signal_call_handle)();
  } else {
    fprintf(stderr, "g2int_service_sigalrm_signal_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-SIGNAL-HANDLER
 */
static long (*g2int_signal_handler_call_handle)();

DLLEXPORT void g2int_signal_handler_init_call_handle (long (*fn)())
{
  g2int_signal_handler_call_handle = fn;
}

long g2int_signal_handler()
{
  if (g2int_signal_handler_call_handle) {
    return (*g2int_signal_handler_call_handle)();
  } else {
    fprintf(stderr, "g2int_signal_handler_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-SIGNAL-HANDLER-FOR-LAUNCH
 */
static long (*g2int_signal_handler_for_launch_call_handle)();

DLLEXPORT void g2int_signal_handler_for_launch_init_call_handle (long (*fn)())
{
  g2int_signal_handler_for_launch_call_handle = fn;
}

long g2int_signal_handler_for_launch()
{
  if (g2int_signal_handler_for_launch_call_handle) {
    return (*g2int_signal_handler_for_launch_call_handle)();
  } else {
    fprintf(stderr, "g2int_signal_handler_for_launch_call_handle is still unbound\n");
    return -1L;
  }
}


/*
 * G2INT-NETWORK-EVENT-HANDLER
 */
static long (*g2int_network_event_handler_call_handle)(long, long, long);

DLLEXPORT void g2int_network_event_handler_init_call_handle (long (*fn)(long, long, long))
{
  g2int_network_event_handler_call_handle = fn;
}

long g2int_network_event_handler(long event_code, long event_socket_handle, long event_status_code)
{
  if (g2int_network_event_handler_call_handle) {
    return (*g2int_network_event_handler_call_handle)(event_code, event_socket_handle, event_status_code);
  } else {
    fprintf(stderr, "g2int_network_event_handler_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-OPEN-FD-CALLBACK
 */
static long (*g2int_open_fd_callback_call_handle)(long);

DLLEXPORT void g2int_open_fd_callback_init_call_handle (long (*fn)(long))
{
  g2int_open_fd_callback_call_handle = fn;
}

long g2int_open_fd_callback(long fd)
{
  if (g2int_open_fd_callback_call_handle) {
    return (*g2int_open_fd_callback_call_handle)(fd);
  } else {
    fprintf(stderr, "g2int_open_fd_callback_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-CLOSE-FD-CALLBACK
 */
static long (*g2int_close_fd_callback_call_handle)(long);

DLLEXPORT void g2int_close_fd_callback_init_call_handle (long (*fn)(long))
{
  g2int_close_fd_callback_call_handle = fn;
}

long g2int_close_fd_callback(long fd)
{
  if (g2int_close_fd_callback_call_handle) {
    return (*g2int_close_fd_callback_call_handle)(fd);
  } else {
    fprintf(stderr, "g2int_close_fd_callback_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-WRITING-FD-CALLBACK
 */
static long (*g2int_writing_fd_callback_call_handle)(long);

DLLEXPORT void g2int_writing_fd_callback_init_call_handle (long (*fn)(long))
{
  g2int_writing_fd_callback_call_handle = fn;
}

long g2int_writing_fd_callback(long fd)
{
  if (g2int_writing_fd_callback_call_handle) {
    return (*g2int_writing_fd_callback_call_handle)(fd);
  } else {
    fprintf(stderr, "g2int_writing_fd_callback_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-NOT-WRITING-FD-CALLBACK
 */
static long (*g2int_not_writing_fd_callback_call_handle)(long);

DLLEXPORT void g2int_not_writing_fd_callback_init_call_handle (long (*fn)(long))
{
  g2int_not_writing_fd_callback_call_handle = fn;
}

long g2int_not_writing_fd_callback(long fd)
{
  if (g2int_not_writing_fd_callback_call_handle) {
    return (*g2int_not_writing_fd_callback_call_handle)(fd);
  } else {
    fprintf(stderr, "g2int_not_writing_fd_callback_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-RUN-TRACE-FUNCTION
 */
static long (*g2int_run_trace_function_call_handle)();

DLLEXPORT void g2int_run_trace_function_init_call_handle (long (*fn)())
{
  g2int_run_trace_function_call_handle = fn;
}

long g2int_run_trace_function()
{
  if (g2int_run_trace_function_call_handle) {
    return (*g2int_run_trace_function_call_handle)();
  } else {
    fprintf(stderr, "g2int_run_trace_function_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * G2INT-UNIX-COMMAND-CALLBACK
 */
static long (*g2int_unix_command_callback_call_handle)();

DLLEXPORT void g2int_unix_command_callback_init_call_handle (long (*fn)())
{
  g2int_unix_command_callback_call_handle = fn;
}

long g2int_unix_command_callback()
{
  if (g2int_unix_command_callback_call_handle) {
    return (*g2int_unix_command_callback_call_handle)();
  } else {
    fprintf(stderr, "g2int_unix_command_callback_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * NMS-FETCH-HELP-STRING
 */
static long (*nms_fetch_help_string_call_handle)(long, long);

DLLEXPORT void nms_fetch_help_string_init_call_handle (long (*fn)(long, long))
{
  nms_fetch_help_string_call_handle = fn;
}

long nms_fetch_help_string(long native_window, long item_id)
{
  if (nms_fetch_help_string_call_handle) {
    return (*nms_fetch_help_string_call_handle)(native_window, item_id);
  } else {
    fprintf(stderr, "nms_fetch_help_string_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * NMS-HANDLE-IF-FLAG-BIT
 */
static long (*nms_handle_if_flag_bit_call_handle)(long, long, long);

DLLEXPORT void nms_handle_if_flag_bit_init_call_handle (long (*fn)(long, long, long))
{
  nms_handle_if_flag_bit_call_handle = fn;
}

long nms_handle_if_flag_bit(long hmenu_high, long hmenu_low, long flag)
{
  if (nms_handle_if_flag_bit_call_handle) {
    return (*nms_handle_if_flag_bit_call_handle)(hmenu_high, hmenu_low, flag);
  } else {
    fprintf(stderr, "nms_handle_if_flag_bit_call_handle is still unbound\n");
    return -1L;
  }
}

/*
 * NMS-ID-FOR-MENU
 */
static long (*nms_id_for_menu_call_handle)(long, long);

DLLEXPORT void nms_id_for_menu_init_call_handle (long (*fn)(long, long))
{
  nms_id_for_menu_call_handle = fn;
}

long nms_id_for_menu(long hmenu_high, long hmenu_low)
{
  if (nms_id_for_menu_call_handle) {
    return (*nms_id_for_menu_call_handle)(hmenu_high, hmenu_low);
  } else {
    fprintf(stderr, "nms_id_for_menu_call_handle is still unbound\n");
    return -1L;
  }
}
