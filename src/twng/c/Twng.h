// -*- Mode: C++ -*-

#pragma once
#include "resource.h"
#include "ControlIniter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEFAULT_UI_THEME 2001

#define GENSYM_STATUSBAR 820	/* Click on statusbar */
#define GENSYM_TREE_VIEW 833	/* Tree view notification */
#define GENSYM_HTML_VIEW 834
#define GENSYM_SHORTCUT_BAR 838
#define GENSYM_LOGBOOK_VIEW 840
#define GENSYM_LOGIN_DIALOG 841
#define GENSYM_PROP_GRID 842
#define GENSYM_TABULAR_VIEW 845
#define GENSYM_CHART 839

// Copied from graphcs.h
#define X11_CONTROL_BIT		(1 << 23)
#define X11_ALTERNATE_BIT	(1 << 19)
#define X11_SHIFT_BIT           (1 << 18)
#define X11_DOUBLE_BIT          (1 << 16) /* For double mouse clicks. */

/* Copied from ext/c/msincls.h */
#define WSA_NETEVENT (WM_USER + 1)
#define WM_PARENT_IS_MOVING (WM_USER + 4)
#define WM_PARENT_IS_CLOSING (WM_USER + 8)
#define WM_ICON_CHANGED (WM_USER + 9)
#define WM_SET_NATIVE_ICON (WM_USER + 10)
#define WM_PARENT_CHANGED (WM_USER + 11)
#define WM_GETCOMMANDBARS (WM_USER + 12)
#define WM_QUERY_CLOSE (WM_USER + 13)
#define WM_CLICK_ACTION (WM_USER + 14)

#ifndef VK_OEM_PLUS
#define VK_OEM_PLUS 0xBB	   /* Duplicated in ext/c/msincls.h */
#define VK_OEM_MINUS 0xBD
#endif

// Extended window status codes for panes. Keep in sync with windows4.lisp
#define STATUS_FLOATED   8
#define STATUS_DOCKED    9	// Old. Replaced with DOCKED_<side>
#define STATUS_PINNED   10
#define STATUS_UNKNOWN  11
#define STATUS_EXPANDED 12
#define STATUS_COLLAPSED 13
#define STATUS_CLOSED   14
#define STATUS_ATTACHED   15
#define STATUS_DOCKED_LEFT 16
#define STATUS_DOCKED_TOP 17
#define STATUS_DOCKED_RIGHT 18
#define STATUS_DOCKED_BOTTOM 19
#define STATUS_HIDDEN 20

#define GENSYM_CODE_FOR_LINEBREAK 0x2028

/* Duplicated in ext/c/msincls.h */
#define g2pvt_local_command_p(id) ((id)>=1001 && (id)<=1050)

#define WinSize(w,h) CRect(0,0,max(0,w),max(0,h))

extern ControlIniter gDefaultControlIniter;
extern IControlIniter* gControlIniter;

class CTwngApp : public CWinApp
{
public:
  CMultiDocTemplate* m_pDocTemplateWorkspace;

#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more		
public:
	MSG& get_m_msgCur();
  __declspec( property( get=get_m_msgCur ) ) MSG m_msgCur; // 
#endif

public:
  CTwngApp();
  virtual BOOL InitInstance();	    /* Calls TW's init_app */
  virtual int Run();		    /* Calls into TW's main() */
  BOOL OnIdle(LONG);
  int EventCycle(int opcode, MSG*); /* TW's hook into MFC event processing. */
  virtual BOOL PumpMessage();
  void CleanupDialogs(void);

  // GENSYMCID-1215: twng locks up (workaround). 
  // MWMonitorProc is timer callback procedure for maximized window monitor
  // m_nMWMonitorTimer is the handle of the maximized window monitor timer
  // SetUpMWMonitorTimer is used to set up the maximized window monitor timer
  // MWMonitorTimerID is the ID of the maximized window monitor timer
  void SetUpMWMonitorTimer();
  static void CALLBACK MWMonitorProc(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime);
  UINT_PTR m_nMWMonitorTimer;
  const static int MWMonitorTimerID = 1000;

  DECLARE_MESSAGE_MAP()
};

extern CTwngApp theApp;

/* Utilities */
extern LPTSTR TStr(LPWSTR str);
extern LPWSTR WStr(LPCTSTR str);
extern int GetCommonControlsVersion();
extern BOOL g2pvt_nms_get_id_enabled(int id);
extern CXTPDockingPane* g2pvt_find_pane(int handle);
extern void g2pvt_refresh_pane_tabs(CXTPDockingPane *pPane);
extern void g2pvt_initialize_scintilla_library(void);
extern LPWSTR g2pvt_to_native_linebreaks(LPWSTR s);
extern char *g2pvt_to_utf8(LPCWSTR ustr);
extern void g2pvt_view_sized(CWnd *pWnd, int handle, int nType = STATUS_UNKNOWN);
extern wchar_t *g2pvt_g2_to_windows_text(wchar_t *pText);

std::wstring Twng_GetWorkspaceViewIconPath();
bool Twng_LogbookDisabled();
bool Twng_MessageBoardDisabled();

#define GetMainWnd() ((CMainFrame*) AfxGetMainWnd())

// In lieu of multiple inheritance.
#define SAVE_WND() GetMainWnd()->SaveWnd(this, m_handle)
#define FIND_WND(handle,Class) (Class*) GetMainWnd()->FindWnd(handle, RUNTIME_CLASS(Class))
#define DESTROY_WND(handle) GetMainWnd()->DestroyWnd(handle)
#define FORGET_WND() GetMainWnd()->ForgetWnd(m_handle)

/* -------------------- Defined by TW -------------------- */
extern "C" {
  int g2ext_app_init(HINSTANCE, LPSTR cmdline, LPSTR productName);
  int g2ext_app_set_windows(HWND frame, HWND client);
  int g2ext_app_run(void);
  int g2pvt_frame_wndproc(HWND, UINT, WPARAM, LPARAM);
  int g2pvt_swv_wndproc(HWND, UINT, WPARAM, LPARAM, LRESULT*);
  BOOL g2pvt_syscommand_enabled_p(HWND hwnd, UINT nID);

  int g2pvt_window_handle(HWND hwnd);
  int g2pvt_compute_window_state(HWND hwnd);

  void ClientToWindowEx(RECT *r, DWORD style, DWORD exStyle);

  void g2pvt_send_window_activated(HWND hwnd, int handle);
  void g2pvt_send_window_refresh(HWND hwnd, int handle, RECT *r);
  void g2pvt_send_window_moved(HWND hwnd, int handle, int x, int y);
  void g2pvt_send_window_sized(HWND hwnd, int handle, UINT type, int cx, int cy);
  void g2pvt_send_window_vscroll(HWND hwnd, int handle, int code, int pos, int id);
  void g2pvt_send_window_hscroll(HWND hwnd, int handle, int code, int pos, int id);
  void g2pvt_send_window_closed(HWND hwnd, int handle);
  void g2pvt_send_window_status(HWND hwnd, int handle, int status);

  void g2pvt_fire_control_event(int controlHandle, int controlType,
				int arg1, int arg2, int arg3, int arg4, LPCWSTR string);
  void g2pvt_send_nms_control_event(HWND hwnd, int control, int selection, LPWSTR value);

  int g2pvt_update_menubar(void);
  int g2pvt_update_dynamic_menu(HANDLE menu, int posInParent);
  int g2pvt_nms_menu_unposted(HANDLE menu);
  int g2pvt_fire_nms_selection_callbacks(HANDLE menu, int itemID);
  BOOL g2pvt_local_command_enabled_p(int);

  void g2pvt_on_wm_mouseactivate(HWND hwndMDIChild);

  HIMAGELIST g2pvt_get_image_list(int size);
  HICON g2pvt_get_native_icon(int icon);
  HICON g2pvt_get_native_iconEx(int icon, int size);
  int g2pvt_icon_index(int icon);
  void g2pvt_destroy_native_icon_imagelists(BOOL);
  void g2pvt_refresh_native_icon(int native_icon, int where);
  void g2pvt_set_window_icon(HWND hwnd, int icon);
  void g2pvt_refresh_dialog_icon(int native_icon);
  void g2pvt_refresh_mdi_child_icon(int native_icon);
  void g2pvt_refresh_grid_view_icon(int native_icon);

  void g2pvt_enter_modal_loop(void);
  void g2pvt_exit_modal_loop(void);
  void g2pvt_enqueue_display_event(void);

  //Gensym-562-CC-BF-JIRA-46906-Twng and G2 stops drawing
  BOOL g2pvt_modeless_menu (HWND hwndOwner, HMENU menu, UINT flags, UINT msg, int x, int y);
  //Gensym-562-CC-BF-JIRA-46906-Twng and G2 stops drawing

  typedef long int G2pointer;
  typedef long Cpointer;

  G2pointer g2ext_cache_cpointer(Cpointer);
  void g2ext_decache_g2pointer(G2pointer);
  Cpointer  g2ext_map_g2pointer_to_cpointer(G2pointer);

  UINT g2_keycode_for_virtual_key(UINT vk);
  UINT g2pvt_compute_gensym_keycode(UINT vKey, UINT scanCode);
  UINT g2pvt_compute_gensym_mouse_keycode(UINT message);
  extern BOOL Inside_simple_rpc;

  long g2ext_write_string_to_console(char *);
  BOOL g2pvt_center_window (HWND hwndCentered, HWND hwndPreferredOwner);

  /* Custom Dialogs */
  HWND g2pvt_find_dialog_hwnd_by_handle(int g2_id);
  HWND g2pvt_get_dlg_item_hwnd(HWND hwndDlg, long controlId);
  BOOL g2pvt_replace_control_in_dialog(int dlgID, int ctrlID, CWnd *pWnd);
  HWND g2pvt_frame_window(HWND hwnd);

  extern int g_NoRaiseOnRightClick;
  extern int g_InhibitZorderChanges;
  extern int G2_reshape_in_progress;
  extern int G2_inflate_in_progress;

  extern BOOL Frame_is_embedded;

  HWND g2pvt_create_chart_view(long chart_type, DWORD style, HWND hwndParent);
  int g2pvt_manage_chart_view(HWND hPE, int opcode, long width, long height, long format, LPWSTR pathname);
  HWND g2pvt_find_pechart(int handle);
  BOOL g2pvt_pechart_ticks(HWND hPE, int **update_tick, int **data_tick);
  long g2_jchart_set_int(long handle, long prop, long i, long j, long value);
  long g2_jchart_set_string(long handle, long prop, long i, long j, LPWSTR string);
  long g2_jchart_set_double(long handle, long prop, long i, long j, double value);
  long g2_jchart_set_double_array(long handle, long prop, long start, long count, double *array);
  void g2pvt_pechart_keydown(HWND hPE, int handle);
  void g2pvt_pechart_click(HWND hPE, int handle);
  void g2pvt_pechart_cursormove(HWND hPE, int handle);
  void g2pvt_pechart_menu_choice(HWND hPE, int handle);
  void g2pvt_pechart_destroy(HWND hPE);

  /* Debugging */
  void g2pvt_traceEx(int flags, const char *fmt, ...);
  void g2pvt_trace(const char *fmt, ...);
  void g2pvt_printf(const char *fmt, ...);
  void g2pvt_puts(const char *str);
}


/* -------------------- Overrides defined by TWNG -------------------- */
extern "C" {
  int g2pvt_wait_message(void);
  int g2pvt_peek_message(MSG* pMsg);
  int g2pvt_pump_message(MSG* pMsg);
  HWND g2pvt_create_workspace_view(long handle, HWND client, LPWSTR title, DWORD style, RECT* r);
  void g2pvt_set_workspace_view_background_color(HWND hwnd, COLORREF color);
  HWND g2pvt_bless_mdi_child(HWND hwnd, int handle);
  HWND g2pvt_create_mdi_child_dialog(HWND hwndDlg, int handle, BOOL show_p);
  int g2pvt_show_dialog_in_pane(HWND hwndDlg, int handle,
				int x, int y, int width, int height,
				int dock, int neighborID, int icon);
  void g2pvt_destroy_containing_pane_if_any(HWND hwnd, int handle);
  BOOL g2pvt_set_statusbar_visibility(BOOL visible);
  BOOL g2pvt_tabbed_mdi_mode_p();
  void g2pvt_set_window_closeable(HWND hwnd, BOOL torf);
  void g2pvt_process_window_style(CWnd *pWnd, DWORD style);}

extern "C" {
  void g2pvt_menu_size(int menu_size); //HQ-5476610 New API to set menu font size; currently supported only in Twng - Ravindra Nov/19/2008
  long g2ext_begin_item_menu(void);
  long g2ext_add_string_to_item_menu(long popup_menu_index, LPWSTR string, long id, long options);
  long g2ext_add_color_string_to_item_menu(long popup_menu_index, LPWSTR string, long id, 
					   long options, long fg, long bg);
  long g2ext_add_submenu_to_item_menu(long popup_menu_index, LPWSTR string,
				      long submenu_index, long options);
  long g2ext_choose_from_item_menu(long window_index, long popup_menu_index, long x, long y);
  long g2ext_reclaim_item_menu(long menu_index, long top_level_p);
}

extern "C" {

  long g2ext_nms_create_menu(long popup_p, unsigned short *result);
  long g2ext_nms_append_menu(long menu_index, long flags, long id, long submenu_index,
			     long wide, LPWSTR label, long fg, long bg);
  long g2ext_nms_destroy_menu(long window_index, long menu_index, long recurse_p);
  long g2ext_nms_check_menu_item(long menu_index, long item, long flags);
  long g2ext_nms_check_radio_item(long menu_index, long first, long last,
				  long check, long flags);
  long g2ext_nms_enable_menu_item(long menu_index, long item, long flags);
  long g2ext_nms_set_menu(long window_index, long menu_index, long nms_menu_handle);
  long g2ext_nms_pop_up_menu(long window_index, long menu_handle, long menu_index, 
			     long x, long y);
  long g2ext_nms_width_maintainance_p(void);
  long g2ext_nms_set_help(long menu_index, long nID, LPWSTR help);
  long g2ext_nms_modify_menu_item(long menu_index, long nId, long pos, long wide,
				  long new_label_p, LPWSTR new_label, long new_fg, long new_bg,
				  long new_icon);
  long g2ext_nms_remove_menu_item(long menu_index, long item);
  long g2ext_nms_dismiss(long window_index);
  long g2ext_nms_delete_menu_items(long window_index, long menu_index);


  void g2ext_nms_set_iconsize(long icon_size);
  LPWSTR g2pvt_nms_help_string(int nId); /* Get help string for menu item id */
}

extern "C" {
  BOOL g2pvt_tw_workspace_view_p(HWND hwnd);
  BOOL g2pvt_workspace_view_p(HWND hwnd);
  long g2ext_nms_create_toolbar(long handle, LPWSTR name, long dock, long neighbor,
				long flags, long default_button_style);
  long g2ext_nms_append_control(long menu_index, long control_index, long flags);
  long g2ext_nms_manage_control(long control_index, long opcode, long i, LPWSTR s);
  long g2ext_nms_delete_control(long menu_index, long control_index);
  long g2ext_nms_create_edit_box(long handle, LPWSTR name, long width, LPWSTR initial_contents);
  long g2ext_nms_create_combo_box(long handle, LPWSTR name, long width,
				  LPWSTR initial, LPWSTR choices, 
				  long flags, long drop_down_width);
  long g2ext_nms_set_theme(long code);
  long g2ext_nms_get_toolkit(void);
  long g2ext_manage_status_bar(long opcode, long paneID, LPCWSTR strValue, long intValue);

  long g2ext_tabbed_mdi_mode(long opcode, long arg);

  long g2ext_manage_pane(long opcode, long handle, 
			 long x, long y, long width, long height, LPWSTR string);

  long g2ext_create_tree_view(int handle, LPWSTR title,
			      long x, long y, long width, long height,
			      long dock, long neighbor, long min_width, long min_height);
  long g2ext_manage_tree_view(long opcode, long handle, long lParam, LPWSTR string, long flags,
			      long iconHandle, long iconHandleSel, long parent);

  long g2ext_create_property_grid(int handle, LPWSTR title,
				  long x, long y, long width, long height,
				  long dock, long neighbor);
  long g2ext_manage_property_grid(long opcode, long handle, 
				  long node, long type, long parent,
				  LPWSTR caption, LPWSTR strValue, long intValue, double floatValue);

  long g2ext_create_html_view(long handle, LPWSTR title, LPWSTR url,
			      long x, long y, long width, long height,
			      long dock, long neighbor, long min_width, long min_height);
  long g2ext_manage_html_view(long opcode, long handle, LPWSTR url);

  long g2ext_create_shortcut_bar(long handle, long style, long obstyle, LPWSTR title,
				 long x, long y, long width, long height,
				 long dock, long neighborID, long min_width, long min_height);
  long g2ext_manage_shortcut_bar(long opcode, long handle, LPWSTR string, 
				 long nFolder, long icon, LPWSTR tooltip);

  long g2ext_is_operator_logbook_enabled();
  long g2ext_is_message_board_enabled();

  long g2ext_create_logbook(int handle, LPWSTR title,
			    long x, long y, long width, long height,
			    long dock, long neighbor, long logbookType);
  long g2ext_manage_logbook(long opcode, long handle, long msgNum, long date, LPWSTR wstr);
  long g2ext_manage_extended_logbook(long opcode, long handle, long msgNum, long date, 
                                     LPWSTR string, long message_type,
                                     LPWSTR workspace_uuid, LPWSTR workspace_name,
                                     LPWSTR object_uuid, LPWSTR object_type, LPWSTR object_name, 
                                     long line_number);

  long g2ext_create_chart_view(long handle, LPWSTR title, long chart_type, long style16,
			       long x, long y, long width, long height,
			       long dock, long neighbor, LPWSTR lib, long min_width, long min_height);
  long g2ext_manage_chart_view(long handle, long opcode, long width, long height,
			       long format, LPWSTR pathname);

  long g2ext_create_tabular_view(int handle, LPWSTR title,
			       long x, long y, long width, long height,
			       long dock, long neighbor,
				   int sortColumn, BOOL sortAscending);

  long g2ext_manage_tabular_view(long opcode, long handle, long rowID,
				 LPWSTR strValue, long argA, long argB, long argC);

  long g2ext_manage_workspace_view(long opcode, long handle, long color);

  long g2ext_manage_editor(long opcode, long handle, LPWSTR string, long number, long n2);
  // TODO: remove this one.
  HWND g2pvt_create_editor(long handle, LPWSTR title, DWORD style, DWORD exStyle, RECT* pRect, BOOL topLevel);

  long g2ext_debugger_dialog(int opcode, LPWSTR title, LPWSTR label, LPWSTR proc, 
			     LPWSTR env, int flags, int line, int tab_width,
			     unsigned short *bkpts);

  void g2pvt_clear_pane_icons(void);
  void g2pvt_destroy_native_icons(BOOL);
  int g2pvt_icon_resource_id(int native_icon);

  long g2ext_note_progress(LPWSTR message, long doneness);
  void g2pvt_set_indicator_icon(BOOL enable, LPCSTR szIcon, LPCSTR tooltip);
}

extern "C" {
  // GENSYMCID-1215: twng locks up (workaround)
  void fixing_twng_locks_up();
}

/* Used by cjmenu */
#define CloneOfControl(pControl) ((CXTPControl*)((pControl)->GetUserData()))
#define CloneOfBar(pBar) ((CXTPCommandBar*)((pBar)->GetCommandBarData()))

/* Convenience */
#define GetPtr(type,index) ((type*)g2ext_map_g2pointer_to_cpointer(index))
#define SavePtr(ptr) g2ext_cache_cpointer((Cpointer)(ptr))
#define GetHandleOfType(type,index) ((type)g2ext_map_g2pointer_to_cpointer(index))

// Sync with LISP random-lisp-enums
enum {
  LK_FALSE=0,			// nil
  LK_TRUE=1,			// t
  LK_TOP=2,
  LK_BOTTOM=3,
  LK_LEFT=4,
  LK_RIGHT=5,
  LK_AUTOMATIC=6,
  LK_SIZE_TO_FIT=7,
  LK_FIXED=8,
  LK_COMPRESSED=9
};

#define DOCK_TOP 1		// Sync with dock-code-top, etc.
#define DOCK_BOTTOM 2
#define DOCK_LEFT 3
#define DOCK_RIGHT 4
#define DOCK_FLOAT 5
#define DOCK_WITHIN 6
#define DOCK_MDI_CHILD 7	// Extended dock codes, which mean to not dock at all.
#define DOCK_TOP_LEVEL 8
#define DOCK_EMBEDDED 9		// Embedded in a custom dialog.

// Special G2 value, since CW_USEDEFAULT isn't a fixnum.
#define DEFAULT_DIM (-30000)	// Keep in sync with LISP cw-usedefault
#define DefDim(u,default) (((u)==DEFAULT_DIM) ? default : (u))

// Generic pane opcodes.
#define PANE_DESTROY 2
#define PANE_HIDE 3		// Autohide
#define PANE_SELECT 4
#define PANE_FLOAT 5
#define PANE_DOCK 6
#define PANE_SHOW 7
#define PANE_SET_TITLE 8
#define PANE_SET_ICON 9
#define PANE_CLOSE 10		// Completely hide
#define PANE_REDOCK 11
#define PANE_TOGGLE_DOCKING 12
#define PANE_FILL 13

#define PANE_SET_CLOSEABLE 101
#define PANE_SET_AUTOHIDEABLE 102
#define PANE_SET_FLOATABLE 103
#define PANE_SET_DRAGGABLE 104
#define PANE_SET_VISIBLE_CAPTION 105
#define PANE_SET_HIDE_ON_CLOSE 106

// Stock icon indices in toolbar.bmp. Used by treeview and listbar.
#define STOCK_ICON_FLAG (1<<20)	// Keep in sync with twpro.c
#define GMS_CUT_ICON 0
#define GMS_COPY_ICON 1
#define GMS_PASTE_ICON 2
#define GMS_UNDO_ICON 3
#define GMS_REDO_ICON 4
#define GMS_DELETE_ICON 5
#define GMS_FILE_ICON 6
#define GMS_FOLDER_ICON 7
#define GMS_SAVE_ICON 8
#define GMS_PRINT_PREVIEW_ICON 9
#define GMS_PROPERTIES_ICON 10
#define GMS_HELP_ICON 11
#define GMS_FIND_ICON 12
#define GMS_REPLACE_ICON 13
#define GMS_PRINT_ICON 14
#define GMS_GENSYM_ICON 15
#define GMS_BINOCULARS_ICON 16
#define GMS_SAVE_ALL_ICON 17
#define GMS_CLOSED_FOLDER_ICON 18
#define GMS_OPEN_FOLDER_ICON 19
#define GMS_DROP_DOCUMENT_ICON 20
#define GMS_DOCUMENT_ICON 21
#define GMS_FUNNEL_ICON 22
#define GMS_TOOLBOX_ICON 23

/* Debugging */

#define PRINTF g2pvt_trace
#define WARNF g2pvt_trace
#define NOPRINTF 1 ? (void)0 : g2pvt_trace
#define MTRACE NOPRINTF

#if defined(_DEBUG) | defined(DEBUG_VIEWS) | defined(TRACE_VIEWS)
extern void print_object(CObject* pObject);
extern void print_control(CXTPControl* pControl);
extern void g2pvt_print_cmdbar(CXTPCommandBar* pBar);
extern void g2pvt_describe_cmdbar(CXTPCommandBar* pBar);
#endif

#ifdef TRACE_VIEWS
#define VTRACE PRINTF
#define POB(x) print_object(x)
#else
#define VTRACE NOPRINTF
#define POB(x) 0
#endif
