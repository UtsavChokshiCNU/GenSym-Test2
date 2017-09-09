#include "gensym-features.h"

#ifndef vms
#include "errno.h"
#endif /* ndef vms */

#if (defined(__STDC__) || defined(_MSC_VER))
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include "gsi_main.h"
#include "gsiannex.h"

#define BUILD_ID_DAY_OFFSET   0
#define BUILD_ID_MONTH_OFFSET 5
#define BUILD_ID_YEAR_OFFSET  10

#define BUILD_ID_YEAR_MASK  31
#define BUILD_ID_MONTH_MASK 31
#define BUILD_ID_DAY_MASK   31

#define OFFSET_TO_UPPER_CASE_CHAR(o2ucc) (o2ucc + 'A' - 1)

/******************************************************************
 *
 *   Implement version consistency feature
 *
 *****************************************************************/

extern void gsi_init_standard_callbacks();

/***************************************************************************
 * void gsi_version_consistency_check()
 *
 *   Purpose: 
 *     If desired to compare versions of libraries versus
 *     include files, compare them using major, minor and rev
 *     (e.g. 5.0 rev. 3: major = 5, minor = 0). If inconsistency,
 *     exit, except in the case of upgrading from 5.0r0, whose
 *     only problem was not having a rev number. In that case,
 *     don't exit, allow easy upgrade. Just print warning
 *     message. 
 *   Input Arguments: none
 *   Returns: nothing
 *   Comments:
 ***************************************************************************/

gsi_int gsi_include_file_major_version = -1;
gsi_int gsi_include_file_minor_version = -1;
gsi_int gsi_include_file_revision_version = -1;

void gsi_version_consistency_check()
{
  int exit_flag = FALSE;
  if (gsi_include_file_major_version != -1) {
    if ((gsi_include_file_major_version != GSI_INCLUDE_MAJ_VER_NUM) ||
        (gsi_include_file_minor_version != GSI_INCLUDE_MIN_VER_NUM) ||
	(gsi_include_file_revision_version != GSI_INCLUDE_REV_VER_NUM)) {
      printf("\nVersion inconsistency warning:\n");
      printf("  GSI libraries    %d.%d rev %d\n",
	     GSI_INCLUDE_MAJ_VER_NUM,
	     GSI_INCLUDE_MIN_VER_NUM,
	     GSI_INCLUDE_REV_VER_NUM);
      if (gsi_include_file_revision_version == -1) {
	printf("  GSI include file %d.%d\n",
	       gsi_include_file_major_version,
	       gsi_include_file_minor_version);
	if ((gsi_include_file_major_version != GSI_INCLUDE_MAJ_VER_NUM) ||
	    (gsi_include_file_minor_version != GSI_INCLUDE_MIN_VER_NUM)) {
	  exit_flag = TRUE;
	} else {
 	  printf("  (GSI 5.0 requires a revision version,"); 
 	  printf(" as well as a major and minor version)\n");
	}
      } else {
	printf("  GSI include file %d.%d rev %d\n",
	       gsi_include_file_major_version,
	       gsi_include_file_minor_version,
	       gsi_include_file_revision_version);
	exit_flag = TRUE;
      }
    }
  }
  if (exit_flag) {
#ifdef WIN32
    g2ext_maybe_wait_for_return_key();
#endif
    exit(1);
  }

}

DLLEXPORT void gsi_set_include_file_version(majr,minr,rev)
    gsi_int majr, minr, rev;
{
  gsi_include_file_major_version = majr;
  gsi_include_file_minor_version = minr;
  gsi_include_file_revision_version = rev;
}

char *construct_build_id (build_id_integer, rval)
  gsi_int build_id_integer;
  char *rval;
{
  int year_offset, month_offset, day;

  year_offset = (build_id_integer >> BUILD_ID_YEAR_OFFSET) & BUILD_ID_YEAR_MASK;
  month_offset = (build_id_integer >> BUILD_ID_MONTH_OFFSET) & BUILD_ID_MONTH_MASK;
  day = (build_id_integer >> BUILD_ID_DAY_OFFSET) & BUILD_ID_DAY_MASK;
  sprintf(rval, "%c%c%d", OFFSET_TO_UPPER_CASE_CHAR(year_offset),
	  OFFSET_TO_UPPER_CASE_CHAR(month_offset), day);
  return rval;
}

DLLEXPORT gsi_int gsi_version_information(v_id)
  gsi_version_id *v_id;
{
  v_id->major_version = gsi_major_version();
  v_id->minor_version = gsi_minor_version();
  v_id->revision_number = gsi_revision_number();
  v_id->release_quality = gsi_release_quality();
  construct_build_id(gsi_build_id_integer(), v_id->build_id);

  return (gsi_int) 0;
}

static int gsi_log_command_line_called = FALSE;

/*****************************************************************************
 * void gsi_log_command_line (argc, argv)
 *
 *   Description: 
 *     Process the command line and do one of the following:
 *      1) Look for a "help" request and if found print help and exit(!).
 *      2) Copy the command line arguments to an internal array for future
 *         access.
 *   Input Arguments:
 *     argc: number of args passed in
 *     argv: array of args passed
 *   Returns:
 *     return value: 0
 *   Notes:
 *     This functions gets called directly from main(). It calls
 *     some functions which are also called by G2/TW, for
 *     consistency of arg handling and help. This function basically matches
 *     heap_command_line() in cprim.c (used by G2/TW). See further
 *     notes in cprim.c.
 *
 *     IMPORTANT: Be sure any changes here are matched in heap_command_line().
 *
 *****************************************************************************/

DLLEXPORT void gsi_log_command_line(argc,argv)
    int argc;
    char *argv[];
{
    int arg_index = argc - 1;

    if ((arg_index > 0) &&
	((strcmp(argv[1],      "-help") == 0)  /* 0 when identical */
	 || (strcmp(argv[1],   "-HELP") == 0) 
	 || (strcmp(argv[arg_index],"-help") == 0) 
	 || (strcmp(argv[arg_index],"-HELP") == 0)))
      {
	g2ext_set_gensym_product("GSI");
	g2ext_print_command_line_usage();
	exit(0);
      }
    else {
#if !defined(WIN32)
      /* Windows handles its log file differently than Unix. */
      g2ext_check_for_logfile(argc, argv);
#endif
      g2ext_create_argument_list(argc, argv);
    }
    gsi_log_command_line_called = TRUE;
}

static int ran_internal_gsi_start = FALSE;

void internal_gsi_start()
{
#ifdef WIN32
  /* Should check variable g2pvt_win32_initialized_p here.
   * HQ-4951692 "GSI on Win32 should not start if not initialized"
   */
#endif
  if (!ran_internal_gsi_start) {
    ran_internal_gsi_start = TRUE;
    gsi_version_consistency_check();
    g2rtl_gsi_initialize_region_increments();
    g2int_init_top_level();
    g2int_userinit();
    launch_gsi(); /* enable-run-gsi is NIL, so we will exit soon */
    gsi_init_standard_callbacks();
  }
}

extern int g2ext_gsi_print_backtrace_flag;

DLLEXPORT void gsi_print_backtrace()
{
  g2ext_gsi_print_backtrace_flag = TRUE;
  g2ext_print_backtrace();
}

/* obsolete */
typedef void gsi_wait_handler_type GSI_API_PROTO(( gsi_int ));
gsi_wait_handler_type *gsi_wait_handler = (gsi_wait_handler_type *)0;

static void gsi_run_state_wait_handler(change_direction,change_type,name)
   gsi_int change_direction, change_type;
   char *name;
{
  if ( 0 != gsi_wait_handler && change_type == GSI_RUN_STATE_TYPE_WAIT )
     (*gsi_wait_handler)((change_direction == GSI_RUN_STATE_DIRECTION_ENTERING_GSI) ?
			 0 : 1);
}  

DLLEXPORT void gsi_install_wait_handler(wait_handler)
  gsi_wait_handler_type *wait_handler;
{
  gsi_wait_handler = wait_handler;
  gsi_install_run_state_change(gsi_run_state_wait_handler);
}

DLLEXPORT void gsi_initialize_callbacks 
#if GSI_USE_PROTOTYPES
       ( void *name1, ... )
#else
       ( name1, va_alist )
    void *name1;
#endif
{
  int firstp = TRUE, errorp = FALSE;
  void *name;
  void *fn;
  va_list ap;

#if GSI_USE_PROTOTYPES
  va_start(ap,name1);
#else
  va_start(ap);
#endif
  while ((void *)NULL != (name=(firstp?name1:va_arg(ap,void *)))) {
    firstp = FALSE;
    errorp = FALSE;
    fn = va_arg(ap,void *);
    gsi_initialize_callback(name,fn);
  }
}

DLLEXPORT void gsi_watch_fd(file_descriptor)
   long file_descriptor;
{
  extern void g2ext_network_watch_fd();
  g2ext_network_watch_fd(file_descriptor);
}

DLLEXPORT void gsi_unwatch_fd(file_descriptor)
   long file_descriptor;
{
  extern void g2ext_network_unwatch_fd();
  g2ext_network_unwatch_fd(file_descriptor);
}


DLLEXPORT void gsi_watch_fd_for_writing(file_descriptor)
   long file_descriptor;
{
  extern void g2ext_network_watch_fd_for_writing();
  g2ext_network_watch_fd_for_writing(file_descriptor);
}

DLLEXPORT void gsi_unwatch_fd_for_writing(file_descriptor)
   long file_descriptor;
{
  extern void g2ext_network_unwatch_fd_for_writing();
  g2ext_network_unwatch_fd_for_writing(file_descriptor);
}


#ifdef unix
#define GSI_SIGCHLD SIGCHLD
#else
#define GSI_SIGCHLD 18
#endif
 
DLLEXPORT void gsi_signal_handler(signal_code)
int signal_code;
{
# if !defined(WIN32) && !defined(__WATCOMC__) && !defined(vms)
  if (signal_code == SIGALRM) 
    {g2ext_gensym_SIGALRM_handler(signal_code); return;}
# endif
  if (signal_code == GSI_SIGCHLD) return;
  /* The run state callback is inside c_gensym_signal_handler */
  g2ext_gensym_signal_handler(signal_code);
}

typedef void void_fn_type();

#define GSI_API_FUNCTION_POINTER_LIST \
(void_fn_type *)gsi_convert_str_to_ustr,\
(void_fn_type *)gsi_convert_ustr_to_str,\
(void_fn_type *)gsi_convert_ustr_to_wstr,\
(void_fn_type *)gsi_convert_wstr_to_ustr,\
(void_fn_type *)gsi_attr_count_of,\
(void_fn_type *)gsi_attr_is_transient,\
(void_fn_type *)gsi_attr_name_is_qualified,\
(void_fn_type *)gsi_attr_name_of,\
(void_fn_type *)gsi_attrs_of,\
(void_fn_type *)gsi_class_name_of,\
(void_fn_type *)gsi_class_qualifier_of,\
(void_fn_type *)gsi_class_type_of,\
(void_fn_type *)gsi_clear_item,\
(void_fn_type *)gsi_clear_last_error,\
(void_fn_type *)gsi_close_listeners,\
(void_fn_type *)gsi_context_received_data,\
(void_fn_type *)gsi_context_socket,\
(void_fn_type *)gsi_context_user_data,\
(void_fn_type *)gsi_current_context,\
(void_fn_type *)gsi_decode_timestamp,\
(void_fn_type *)gsi_element_count_of,\
(void_fn_type *)gsi_elements_of,\
(void_fn_type *)gsi_encode_timestamp,\
(void_fn_type *)gsi_error_message,\
(void_fn_type *)gsi_establish_listener,\
(void_fn_type *)gsi_extract_history,\
(void_fn_type *)gsi_extract_history_spec,\
(void_fn_type *)gsi_flt_array_of,\
(void_fn_type *)gsi_flt_list_of,\
(void_fn_type *)gsi_flt_of,\
(void_fn_type *)gsi_flush,\
(void_fn_type *)gsi_handle_of,\
(void_fn_type *)gsi_history_count_of,\
(void_fn_type *)gsi_initialize_callbacks,\
(void_fn_type *)gsi_initialize_error_variable,\
(void_fn_type *)gsi_initiate_connection,\
(void_fn_type *)gsi_initiate_connection_w_u_d,\
(void_fn_type *)gsi_int_array_of,\
(void_fn_type *)gsi_int_list_of,\
(void_fn_type *)gsi_int_of,\
(void_fn_type *)gsi_interval_of,\
(void_fn_type *)gsi_is_item,\
(void_fn_type *)gsi_item_append_flag,\
(void_fn_type *)gsi_item_of_attr,\
(void_fn_type *)gsi_item_of_attr_by_name,\
(void_fn_type *)gsi_item_of_identifying_attr_of,\
(void_fn_type *)gsi_item_of_registered_item,\
(void_fn_type *)gsi_item_reference_flag,\
(void_fn_type *)gsi_kill_context,\
(void_fn_type *)gsi_last_error,\
(void_fn_type *)gsi_last_error_call_handle,\
(void_fn_type *)gsi_last_error_message,\
(void_fn_type *)gsi_listener_socket,\
(void_fn_type *)gsi_log_array_of,\
(void_fn_type *)gsi_log_list_of,\
(void_fn_type *)gsi_log_of,\
(void_fn_type *)gsi_make_array,\
(void_fn_type *)gsi_make_attrs,\
(void_fn_type *)gsi_make_attrs_with_items,\
(void_fn_type *)gsi_make_item,\
(void_fn_type *)gsi_make_items,\
(void_fn_type *)gsi_make_registered_items,\
(void_fn_type *)gsi_make_symbol,\
(void_fn_type *)gsi_name_of,\
(void_fn_type *)gsi_option_is_set,\
(void_fn_type *)gsi_owner_of,\
(void_fn_type *)gsi_pause,\
(void_fn_type *)gsi_reclaim_array,\
(void_fn_type *)gsi_reclaim_attrs,\
(void_fn_type *)gsi_reclaim_attrs_with_items,\
(void_fn_type *)gsi_reclaim_item,\
(void_fn_type *)gsi_reclaim_items,\
(void_fn_type *)gsi_reclaim_registered_items,\
(void_fn_type *)gsi_registration_of_handle,\
(void_fn_type *)gsi_registration_of_item,\
(void_fn_type *)gsi_reset_option,\
(void_fn_type *)gsi_return_attrs,\
(void_fn_type *)gsi_return_message,\
(void_fn_type *)gsi_return_timed_attrs,\
(void_fn_type *)gsi_return_timed_values,\
(void_fn_type *)gsi_return_values,\
(void_fn_type *)gsi_rpc_call,\
(void_fn_type *)gsi_rpc_call_with_count,\
(void_fn_type *)gsi_rpc_declare_local_plain,\
(void_fn_type *)gsi_rpc_declare_remote_plain,\
(void_fn_type *)gsi_rpc_return_error_values,\
(void_fn_type *)gsi_rpc_return_values,\
(void_fn_type *)gsi_rpc_start,\
(void_fn_type *)gsi_rpc_start_with_count,\
(void_fn_type *)gsi_run_loop,\
(void_fn_type *)gsi_set_attr_count,\
(void_fn_type *)gsi_set_attr_is_transient,\
(void_fn_type *)gsi_set_attr_name,\
(void_fn_type *)gsi_set_attrs,\
(void_fn_type *)gsi_set_class_name,\
(void_fn_type *)gsi_set_class_qualifier,\
(void_fn_type *)gsi_set_context_limit,\
(void_fn_type *)gsi_set_context_user_data,\
(void_fn_type *)gsi_set_element_count,\
(void_fn_type *)gsi_set_elements,\
(void_fn_type *)gsi_set_flt,\
(void_fn_type *)gsi_set_flt_array,\
(void_fn_type *)gsi_set_flt_list,\
(void_fn_type *)gsi_set_handle,\
(void_fn_type *)gsi_set_history,\
(void_fn_type *)gsi_set_include_file_version,\
(void_fn_type *)gsi_set_int,\
(void_fn_type *)gsi_set_int_array,\
(void_fn_type *)gsi_set_int_list,\
(void_fn_type *)gsi_set_interval,\
(void_fn_type *)gsi_set_item_append_flag,\
(void_fn_type *)gsi_set_item_of_attr,\
(void_fn_type *)gsi_set_item_of_attr_by_name,\
(void_fn_type *)gsi_set_item_reference_flag,\
(void_fn_type *)gsi_set_log,\
(void_fn_type *)gsi_set_log_array,\
(void_fn_type *)gsi_set_log_list,\
(void_fn_type *)gsi_set_name,\
(void_fn_type *)gsi_set_option,\
(void_fn_type *)gsi_set_pause_timeout,\
(void_fn_type *)gsi_set_rpc_remote_return_v_k,\
(void_fn_type *)gsi_set_run_loop_timeout,\
(void_fn_type *)gsi_set_status,\
(void_fn_type *)gsi_set_str,\
(void_fn_type *)gsi_set_str_array,\
(void_fn_type *)gsi_set_str_list,\
(void_fn_type *)gsi_set_string_conversion_style,\
(void_fn_type *)gsi_set_sym,\
(void_fn_type *)gsi_set_sym_array,\
(void_fn_type *)gsi_set_sym_list,\
(void_fn_type *)gsi_set_symbol_user_data,\
(void_fn_type *)gsi_set_timestamp,\
(void_fn_type *)gsi_set_type,\
(void_fn_type *)gsi_set_unqualified_attr_name,\
(void_fn_type *)gsi_set_update_items_flag,\
(void_fn_type *)gsi_set_user_data,\
(void_fn_type *)gsi_set_usv,\
(void_fn_type *)gsi_signal_error,\
(void_fn_type *)gsi_signal_handler,\
(void_fn_type *)gsi_simple_content_copy,\
(void_fn_type *)gsi_start,\
(void_fn_type *)gsi_status_of,\
(void_fn_type *)gsi_str_array_of,\
(void_fn_type *)gsi_str_list_of,\
(void_fn_type *)gsi_str_of,\
(void_fn_type *)gsi_string_conversion_style,\
(void_fn_type *)gsi_sym_array_of,\
(void_fn_type *)gsi_sym_list_of,\
(void_fn_type *)gsi_sym_of,\
(void_fn_type *)gsi_symbol_name,\
(void_fn_type *)gsi_symbol_user_data,\
(void_fn_type *)gsi_timestamp_of,\
(void_fn_type *)gsi_type_of,\
(void_fn_type *)gsi_unqualified_attr_name_of,\
(void_fn_type *)gsi_update_items_flag,\
(void_fn_type *)gsi_user_data_of,\
(void_fn_type *)gsi_usv_of,\
(void_fn_type *)gsi_wakeup,\
(void_fn_type *)gsi_watchdog,\
(void_fn_type *)0

void_fn_type (*gsi_api_function_array[]) = 
  {GSI_API_FUNCTION_POINTER_LIST};

