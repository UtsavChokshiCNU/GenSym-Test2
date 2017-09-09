/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      xwindows.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   10/06/92 - 01/25/96     The Mysterious Mr. AB
 +              02/24/04 - ...          fmw, jv, mhd, dbk, yduj
 +
 + Description:  This file contains some primitives and some stubs used to port
 +               G2 to the X Windows environment, and more specifically X11.
 +
 + Key:
 +   (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP
 +
 +
 + External Interface:
 +
 + Dependencies:
 +
 + Notes:
 +   This file is not compiled on Microsoft Windows platforms.  There is no need
 +   to #ifdef out WIN32; the file will never be seen by the Windows compiler.
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   02/24/04, jv: Reinstate this file, which has been dead for eight years.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "cprim.h"
#include "graphics.h"



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define LPWSTR unsigned short *



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

static long latest_dialog_handle = 0;
extern int No_window;		/* defined in networks.c */

typedef struct {
  struct Tree_node_view_info* next;
  LPWSTR uuid_value;	
  LPWSTR names_value;	
  LPWSTR label_value;
  LPWSTR text_value;
  LPWSTR frame_type_value;
} Tree_node_view_info, *Tree_node_view_info_ptr;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - X11
 %
 % Description:
 %   X11 implementations of generic graphics functions.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


int g2pvt_set_mouse_cursor(int window_index, int cursorID)
{
    GensymXWindow *gwindow;
    Display *display;
    Window window;
    static int shapes[] = {None, XC_arrow, XC_crosshair, XC_hand2, XC_question_arrow, XC_xterm,
			   XC_X_cursor, XC_fleur, XC_bottom_left_corner, XC_sb_v_double_arrow,
			   XC_bottom_right_corner, XC_sb_h_double_arrow, XC_sb_up_arrow,
			   XC_watch};
    static int lastCursorID = 0;
    static Cursor lastCursor = None;

    if (No_window)
      return -1;

    if(cursorID == lastCursorID)
      return -2;

    gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
    display = gwindow->display_ptr;
    window = gwindow->xwindow;

    lastCursorID = cursorID;
    if(lastCursor != None)
      XFreeCursor(display, lastCursor);

    if(cursorID<=0 || cursorID >= sizeof(shapes)/sizeof(int)) {
      lastCursor = None;
      XUndefineCursor(display, window);
    }
    else {
      lastCursor = XCreateFontCursor(display, (unsigned)shapes[cursorID]);
      XDefineCursor(display, window, lastCursor);
    }
    return 1;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - X11 Stubs
 %
 % Description:
 %   These functions are stubs for functionality which only works on Win32.
 % Notes:
 %   Make these functions NOP's for XWINDOWS.
 % Modifications:
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

long g2ext_begin_item_menu() {return -1;}
long g2ext_add_string_to_item_menu(int popup_menu_index, LPWSTR string, long id, long options) {
  return -1;
}
long
g2ext_add_color_string_to_item_menu(long popup_menu_index, LPWSTR string, long id, long options,
                                    long fg, long bg) {
  return -1;
}
long g2ext_add_submenu_to_item_menu(int popup_menu_index, LPWSTR string, long submenu_index, long options) {
  return -1;
}
long g2ext_choose_from_item_menu(int popup_menu_index, long x, long y) {return 0;}  /* 0 means no choice made */
long
g2ext_reclaim_item_menu(long menu_index, int top_level_p) {
  return 0;
}
long g2ext_simple_dialog(int window_index, LPWSTR title_string, LPWSTR message_string,
                         LPWSTR ok_string, long ok_id, LPWSTR cancel_string, long cancel_id,
                         LPWSTR additional_string, long additional_id,
                         long id_of_default) {
  return 0;
}  /* 0 means no choice made */

long g2ext_make_dialog(LPWSTR caption, long size, int nControls,
		       long x, long y, long width, long height,
		       long styleHi, long styleLo,
		       long exstyleHi, long exstyleLo,
		       LPWSTR fontName, long fontSize, long flags)
{return -1;}

long g2ext_add_control(long dlg_index, LPWSTR class, LPWSTR text, long id,
		       long x, long y, long width, long height,
		       long styleHi, long styleLo,
		       long exstyleHi, long exstyleLo,
		       long flags, LPWSTR data)
{return 0;}

long g2ext_post_dialog(long dlg_index, long beep, LPWSTR buf, long buflen)
{ 
  buf[0] = 0;
  return 2;			/* 2==IDCANCEL */
}

long g2ext_list_box(LPWSTR caption, LPWSTR message,
                    long ok_id, long cancel_id,
                    long ncolumns, LPWSTR columns, LPWSTR rows, int icon)
{ return 0;}

long g2ext_get_places_bar(LPWSTR buffer, long buflen) {return 0;}

long
g2ext_file_dialog(long window_index,
                  long flags,                /* 1=Save dialog, 0=Open dialog. */
                  char *title,
                  char *initial_filename,    /* Just the filename.ext portion, or empty string. */
                  char *initial_directory,
                  char *default_extension,   /* Without the dot. Used if user omits extension. */
                  char *filter,              /* NUL-separated set of strings. */
                  char *places,                     /* NUL-separated set of strings. */
                  LPWSTR message,             /* Message to add below. */
                  LPWSTR checkboxes,        /* NUL-separated set of strings. */
                  LPWSTR combobox,             /* NUL-separated set of strings. */
                  char *special,             /* Special filename string for special checkbox */
                  LPWSTR ok_label,
                  LPWSTR cancel_label,
                  LPWSTR response,
                  char *buffer,                     /* Returned pathname */
                  long buflen)                     /* length of buffer */
{ return 0;}


long
g2ext_choose_directory(long opcode, LPWSTR caption, LPWSTR pathname,
		       LPWSTR root, LPWSTR tree, LPWSTR separator,
		       LPWSTR okLabel, LPWSTR cancelLabel) {return -1;}

long g2ext_scroll_window(long window_index, long dx, long dy) {return -1;}

long g2ext_manage_scrollbars(long window_index,
                             long xmin, long xpos, long xmax,
                             long ymin, long ypos, long ymax) {return -1;}

long g2ext_get_system_metric(long code) {return 0;}

long g2ext_mega_refresh() {return 0;}

long g2ext_x11_tell_control_our_session_id(long sessionID) {return -1;}

/* NMS Routines */
long g2ext_nms_create_menu(long popup_p, LPWSTR result) {
  result[0] = result[1] = 0; return -1;}
long g2ext_nms_append_menu(long menu_index, long flags, long id, long submenu_index, long wide,
                           LPWSTR label, long fg, long bg)
                          {return -1;}
long g2ext_nms_destroy_menu(long window_index, long menu_index, long recurse_p) {return -1;}

long g2ext_nms_check_menu_item(long menu_index, long item, long flags) {return -1;}
long g2ext_nms_check_radio_item(long menu_index, long first, long last,
                                long check, long flags)  {return -1;}
long g2ext_nms_enable_menu_item(long menu_index, long item, long flags)  {return -1;}

long g2ext_nms_set_menu(long window_index, long menu_index, long nms_menu_handle) {return -1;}
long g2ext_nms_pop_up_menu(long window_index, long menu_index, long x, long y) {return -1;}
long g2ext_nms_fetch_help_string_result(LPWSTR string) {return -1;}
long g2ext_nms_set_flag(long flag) {return -1;}
long g2ext_nms_width_maintainance_p(void) {return 0;}
long g2ext_nms_set_help(long menu_index, long nID, LPWSTR new_help) {return 0;}
long g2ext_nms_modify_menu_item(long menu_index, long id, long pos, long wide,
                                long new_label_p, LPWSTR new_label, long new_fg, long new_bg,
                                long new_icon) {return -1;}

long g2ext_nms_remove_menu_item(long menu_index, long item) {return -1;}
long g2ext_nms_dismiss(long window_index) {return -1;}
long g2ext_nms_delete_menu_items(long window_index, long menu_index) {return -1;}

long g2ext_html_help(long cmd, char *dir, char *file, char *string, long id, long x, long y, long flags) {return 0;}
long g2ext_print_window(long window_index, LPWSTR jobname) {return -1;}
long g2ext_about_box(long window_index, LPWSTR version, LPWSTR comments) {return -1;}

/* Native toolbars and other controls */
long g2ext_nms_append_control(long menu_index, long control_index, long flags) {return -1;}
long g2ext_nms_manage_control(long control_index, long opcode) {return -1;}
long g2ext_nms_delete_control(long menu_index, long control_index) {return -1;}

long g2ext_nms_create_toolbar(long handle, LPWSTR name, long dock, long n, long e, long b) {return -1;}
long g2ext_nms_create_edit_box(long handle, LPWSTR name, long width, LPWSTR initial) {return -1;}
long g2ext_nms_create_combo_box(long handle, LPWSTR name, long width, LPWSTR initial,
                                LPWSTR choices, long flags,
                                long drop_down_width) {return -1;}

/* Misc stubs */
long g2ext_nms_set_theme(long code) {return -1;}

/*Added by SoftServe */
void g2ext_nms_set_iconsize(long iconsize) {return;}

/* Native Printing routines. */
long g2ext_print_dialog(long window_index, short* title, long flags,
                        char *buf, long buflen, LPWSTR results) {return -1;}
long g2ext_start_doc(long window_index, LPWSTR jobname) {return -1;}
long g2ext_start_page(long page, LPWSTR label,
                      long nrows, long ncolumns,
                      long lm, long tm, long rm, long bm,
                      long scale, long flags) {return -1;}
long g2ext_end_page(void) {return -1;}
long g2ext_end_doc(void) {return -1;}
long g2ext_draw_to_printer(long window_index, long enable) {
  extern int draw_to_printer;
  draw_to_printer = enable&1;
  return draw_to_printer;
}
long g2ext_abort_printing(void) {return -1;}

/* Native icons routines */
long g2ext_x11_manage_native_icons(long window_index, long handle, long width, long height,
                                   long color_pixmap_index, long mask_pixmap_index)
{ return -1; }

long g2ext_note_progress(LPWSTR message, long doneness) {return -1;}

/* Native Dialogs */
long g2ext_message_box (long window_index, LPWSTR caption, LPWSTR message,
                        long style, long icon)
{return -1;}
long g2ext_query_box(long window_index, LPWSTR caption, LPWSTR message,
                     long fontSize, long icon, LPWSTR response, long buflen)
{return -1;}
long g2ext_cancel_modal_dialogs_and_menus(void){return -1;}

long g2ext_manage_notification(long opcode, LPWSTR caption, LPWSTR message,
                               long fontSize, long icon)
{return -1;}

long g2ext_manage_animation(long opcode, LPWSTR caption, LPWSTR message,
                            long fontSize, LPWSTR avi)
{return -1;}

/* Native Image Plane Stubs */
long g2ext_x11_create_window(long type, long parent_hi, long parent_low, long handle,
                             LPWSTR title, long style16, long exStyle,
                             long x, long y, long width, long height) {return -1;}
long g2ext_x11_manage_window(long opcode, long window_index,
                             long x, long y, long width, long height,
                             LPWSTR string) {return -1;}
long g2ext_x11_stack_windows(long opcode, long prev_index, long window_index) {return -1;}


long g2ext_list_directory_response(long opcode, long type, long size,
                                   long hi_time, long low_time, char *name) {return -1;}

void g2ext_lock_dialog (long dialog_id, long locked_p) {  return; }

long g2ext_nms_get_toolkit()
{
  return 0;                        /* X11 */
}

void g2ext_set_mdi_client_background_color(long red, long green, long blue) {}

long g2ext_manage_status_bar(long opcode, long pane, LPWSTR string, long number) {return -1;}

long g2ext_tabbed_mdi_mode(long opcode, long arg) {return -1;}

long g2ext_manage_pane(long opcode, long handle,
                       long x, long y, long width, long height, LPWSTR string)
{return -1;}

long g2ext_create_tree_view(int handle, LPWSTR title,
                            long x, long y, long width, long height,
                            long dock, long neighbor)
{return -1;}

long g2ext_manage_tree_view(long opcode, long handle, LPWSTR string, long flags,
                            long x, long y, long width, long height, long lParam,
                            long parent)
{return -1;}

long g2ext_create_html_view(long handle, LPWSTR title, LPWSTR url,
                            long x, long y, long width, long height, long dock, long neighbor)
{return -1;}

long g2ext_manage_html_view(long opcode, long handle, LPWSTR url)
{return -1;}

long g2ext_create_shortcut_bar(long handle, long style, long obstyle, LPWSTR title,
                               long x, long y, long width, long height,
                               long dock, long neighborID)
{return -1;}

long g2ext_manage_shortcut_bar(long opcode, long handle, LPWSTR string,
                               long nFolder, long icon, long userdata)
{return -1;}

long g2ext_is_message_board_enabled()
{return 1;}

long g2ext_is_operator_logbook_enabled()
{return 1;}

long g2ext_create_logbook(int handle, LPWSTR title,
			    long x, long y, long width, long height,
			    long dock, long neighbor, long logbookType)
{return -1;}
long g2ext_manage_logbook(long opcode, long handle, long msgNum, long date, LPWSTR string)
{return -1;}
long g2ext_manage_extended_logbook(long opcode, long handle, long msgNum, long date, 
                                   LPWSTR string, long message_type,
                                   LPWSTR workspace_uuid, LPWSTR workspace_name,
                                   LPWSTR object_uuid, LPWSTR object_type, LPWSTR object_name, 
                                   long line_number)
{return -1;}

long g2ext_debugger_dialog(int opcode, LPWSTR title, LPWSTR label, LPWSTR proc, LPWSTR env, int line, 
			   int tab_width, unsigned short *bkpts)
{return -1;}


long g2ext_manage_editor(long opcode, long window_index, LPWSTR text, long n1, long n2)
{return -1;}


long g2ext_get_charting_library_version(char *buf, int buflen) { return 0; }
long g2ext_create_chart_view(long handle, LPWSTR title, long chart_type, long style,
                             long left, long top, long width, long height,
			     long dock, long neighbor, LPWSTR lib) {return -1;}
long g2ext_manage_chart_view(long handle, long opcode, long width, long height, long format, LPWSTR pathname)
{return -1;}
long g2ext_chart_set_int   (long handle, long prop, long i, long j, long v) {return -1;}
long g2ext_chart_set_string(long handle, long prop, long i, long j, LPWSTR v) {return -1;}
long g2ext_chart_set_double(long handle, long prop, long i, long j, double v) {return -1;}
long g2ext_chart_set_double_array(long handle, long prop, long start, long n, double *data) {return -1;}
void g2ext_chart_add_long_to_struct(long value){}
void g2ext_chart_add_str_to_struct(LPWSTR value){}
void g2ext_chart_add_double_to_struct(double value){}

long g2ext_chart_set_struct(long handle, long prop){return -1;}
long g2ext_set_move_resize_time_limit(long seconds) { return 0; }

long g2ext_update_system_tray (long icon, char *iconName, LPWSTR tooltip) {return 0;}
long g2ext_noninteractive_service_p(void) {return 0;}

long g2ext_create_property_grid(int handle, LPWSTR title,
                            long x, long y, long width, long height,
                            long dock, long neighbor)
{return -1;}

long g2ext_native_icons_limit() { return 0; }

long g2ext_manage_property_grid(long opcode, long handle, LPWSTR string, long flags,
                            long x, long y, long width, long height, long lParam,
                            long parent)
{return -1;}


long g2ext_create_tabular_view(int handle, LPWSTR title,
			       long x, long y, long width, long height,
			       long dock, long neighbor)
{return -1;}

long g2ext_manage_tabular_view(long opcode, long handle, long rowID, 
			       LPWSTR strValue, long argA, long argB, long argC)
{return -1;}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - XWindows Functions
 %
 % Description:
 %   These functions are for functions which are purely for XWindows
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*****************************************************************************
 * void g2ext_abort_dialog ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
void g2ext_abort_dialog (long pDialog)
{
  /* For these stub functions, we don't actually allocate any memory, so nothing
   * to be done here.
   */
}


/*****************************************************************************
 * void g2ext_accept_dialog ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
void g2ext_accept_dialog (long pDialog)
{
  /* For these stub functions, we don't actually allocate any memory, so nothing
   * to be done here.
   */
}


/*****************************************************************************
 * long g2ext_show_dialog ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_show_dialog (long pDialog, long xPos, long yPos, long mdi_child_p,
                        long dock, long neighbor, long icon, long resizable_p)
{
  return 0L;   /* FAILURE */
}


long g2ext_set_dialog_background_property (long pDialog, LPWSTR pBackgroundColor)
{
  return 0L;   /* FAILURE */
}


/*****************************************************************************
 * long g2ext_add_dialog_component ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_add_to_dialog (long pDialogId, long pControlId,
                          long pParentControlId, LPWSTR pParentControlText,
                          long pHeight, long pWidth, long pLeft, long pTop,
                          long pType, LPWSTR pText,
                          long pStylesHi, long pStylesLo, long pResponse,
                          long pG2Styles)
{
  return 0L;   /* FAILURE */
}


/*****************************************************************************
 * long g2ext_start_dialog ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_start_dialog (long g2_id, long guess_ncontrols, long width, long height,
                         long type, LPWSTR pTitle)
{
  long handle = ++latest_dialog_handle;

  return handle;
}


/*****************************************************************************
 * void g2ext_abort_dialog_query ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
void g2ext_abort_dialog_query (long pDialog, long pQuery)
{
  /* For these stub functions, we don't actually allocate any memory, so nothing
   * to be done here.
   */
}


/*****************************************************************************
 * long g2ext_finish_dialog_query ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_finish_dialog_query (long pDialog, long pQuery)
{
  return 0L;   /* FAILURE */
}


/*****************************************************************************
 * long g2ext_add_to_dialog_query ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_add_to_dialog_query (long pDialogId, long pQuery, long pControlId)
{
  return 0L;   /* FAILURE */
}


/*****************************************************************************
 * long g2ext_start_dialog_query ()
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_start_dialog_query (long pDialogId, long pQuery, long options)
{
  return pQuery;
}


/*****************************************************************************
 * long g2ext_send_dialog_control_update (long dlgId, long control_id)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_send_dialog_control_update (long dlgId, long control_id)
{
  return 0L;
}


/*****************************************************************************
 * long g2ext_start_dialog_update(long)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_start_dialog_update(long dlgId)
{
  return 0L;
}


/*****************************************************************************
 *   long g2ext_dialog_component_update(long,long,LPWSTR,long,long)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_dialog_component_update(long dlgId,
                                   long controlId,
                                   LPWSTR pControlValue,
                                   long updateType)
{
  return 0L;
}


/*****************************************************************************
 * long g2ext_end_dialog_update(long)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_end_dialog_update(long dlgId)
{
  return 0L;
}


/*****************************************************************************
 *  long g2ext_abort_dialog_update(long)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
long g2ext_abort_dialog_update(long dlgId)
{
  return 0L;
}


/*****************************************************************************
* long g2ext_manage_grid_view (long opcode, long dlgId, long controlId,
*                              long row, long col,
*                              long intParam, LPWSTR stringParam)
*
*   Description: an API for system procedures to modify the grid-view after it
*     has posted.
*   Input Arguments:
*   Returns: 
*
*   Notes: 
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_manage_grid_view (long opcode, long dlgId, long controlId,
                             long row, long col, long parm, LPWSTR string)
{
  return -1;
}


/*****************************************************************************
* long g2ext_specify_grid_view_cells (long dlgId, long controlId, LPWSTR cell_spec)
*
*   Description: 
*   Input Arguments:
*   Returns: 
*
*   Notes: 
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_specify_grid_view_cells (long dlgId, long controlId, LPWSTR cell_spec)
{
  return -1;
}


/*****************************************************************************
* void g2ext_specify_text_box_extensions (long dlgId)
*
*   Description: 
*   Input Arguments:
*   Returns: 
*
*   Notes: 
*     -----
*   Modifications:
*****************************************************************************/
void g2ext_specify_text_box_extensions (long dlgId)
{
  return;
}


/*****************************************************************************
* long g2ext_run_telewindows_here ()
*
*   Description: 
*   Input Arguments:
*   Returns: 
*
*   Notes: 
*     -----
*   Modifications:
*****************************************************************************/
long g2ext_run_telewindows_here ()
{
  return -1;
}

long g2ext_get_sys_drives_list_as_string(void* strDrives, long buflen) {
    return -1;
}

void* g2ext_add_debug_info(void* info_pointer, void* proc_name, void* args, void* env) {
     return NULL;
}

long g2ext_debug_info_received(void* info_pointer) {
    return -1;
}

long g2ext_genflex_debugger_step(long g2_handle, long line, void* proc_code, void* env) {
    return -1;
}

long g2ext_get_system_special_folders(void* strSpecialFolders, long buflen) {
    return -1;
}

void g2ext_list_sys_drives_response(void* name) {

}

Tree_node_view_info_ptr g2ext_add_tree_node_view_info(Tree_node_view_info_ptr info_pointer, LPWSTR uuid_value, LPWSTR names_value, LPWSTR label_value, LPWSTR text_value, LPWSTR frame_type_value) {
    return NULL;
}


long g2ext_tree_node_view_info_received(Tree_node_view_info_ptr info_pointer)
{
  return -1;
}


int g2ext_remove_tree_nodes_range(LPWSTR UUID_value){
  return -1;
}

Tree_node_view_info_ptr g2ext_add_tree_node_range_info(Tree_node_view_info_ptr info_pointer, LPWSTR uuid_value, LPWSTR names_value, LPWSTR label_value, LPWSTR text_value, LPWSTR frame_type_value, LPWSTR parent_uuid_value) {
   return NULL;
}

long g2ext_add_tree_node_range_received(Tree_node_view_info_ptr info_pointer) {
   return -1;
}

