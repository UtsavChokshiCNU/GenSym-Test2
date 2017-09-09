#include <windows.h>
#include "dyndlgs.h"

#ifdef CODEJOCK

extern "C" {

	int g2pvt_pump_message(MSG* pMsg) { return 0;}

	int g2pvt_peek_message(MSG* pMsg) { return 0;}

	int g2pvt_wait_message() {return 0;}

	void g2pvt_refresh_native_icon(int handle, int where) {}

	void g2pvt_destroy_native_icons(BOOL destroy) {}

	long g2ext_nms_set_theme(long code) {return 0;}

	BOOL g2pvt_set_indicator_icon(BOOL enable, LPCSTR iconName, LPCSTR tooltip)
	{
		return FALSE;
	}

	BOOL g2pvt_workspace_view_p(HWND hwnd) { return FALSE;}

	int g2pvt_show_dialog_in_pane(HWND hwndDlg, int handle,
					  int x, int y, int width, int height,
					  int dock, int neighborID, int icon) {
		return 0;
	}

	HWND g2pvt_create_dialogMFC(DIALOGINFO *dlgInfo, int handle) { return 0;}

	void g2pvt_menu_size(int menu_size) {}

	HWND g2pvt_create_workspace_view(long handle, HWND client, LPWSTR title,
									 DWORD style, RECT* r) {
		return 0;
	}

	HWND g2pvt_create_editor(long handle, LPWSTR title, DWORD style,
			DWORD exStyle, RECT* pRect, BOOL topLevel) {
		return 0;
	}

	void g2pvt_set_workspace_view_background_color(HWND hwnd, COLORREF color) {}

	void g2pvt_set_window_closeable(HWND hwnd, BOOL torf) {}

	BOOL g2pvt_tabbed_mdi_mode_p() { return FALSE;}

	HWND g2pvt_bless_mdi_child(HWND hwnd, int handle) { return 0;}

	BOOL g2pvt_pechart_ticks(HWND hPE, int **update_tick, int **data_tick) {
		return FALSE;
	}

	HWND g2pvt_find_pechart(int handle) { return 0;}

	long g2_jchart_set_int(long handle, long prop, long i, long j, long value) {
		return 0;
	}

	long g2_jchart_set_string(long handle, long prop, long i, long j,
			LPWSTR string)
	{
		return 0;
	}

	long g2_jchart_set_double(long handle, long prop, long i, long j,
			double value)
	{
		return 0;
	}

	long g2_jchart_set_double_array(long handle, long prop, long start,
			long count,	double *array)
	{
		return 0;
	}

} // End of extern "C"

wchar_t* g2pvt_control_value_of_combo_tree_view(HWND hwndControl) {
	return 0;
}

void g2pvt_set_duration_value(CONTROLITEM *pcontrol, HWND hwndCtrl,
							   HWND hwndDlg) {
}

void g2pvt_set_twng_spin(CONTROLITEM *pctrl, HWND hwndCtrl, HWND hwndDlg) {}

long g2pvt_modify_mfc_control(CONTROLITEM *pcontrol, HWND hwndCtrl,
							   HWND hwndDlg, unsigned short *value,
							   int updateType) {
	return 0;
}

long g2pvt_modify_twng_color_picker(HWND hwndCtrl, CONTROLITEM *pcontrol,
									 unsigned short *new_value, int updateType)
{
	return 0;
}

void g2pvt_mfc_control_created_hook(HWND hwndParent, CONTROLITEM *pcontrol,
									 TABITEM *ptabitem) {
}

BOOL g2pvt_create_mfc_control(HWND hwndParent, CONTROLITEM *pcontrol,
							   TABITEM *ptabitem) {
	return FALSE;
}

void g2pvt_init_G2TabWidget_resizable_child_dialog(HWND hwndTabCtrl,
												   DIALOGINFO *dlgInfo) {
}

wchar_t *g2pvt_control_value_of_advanced_color(HWND hwndControl) { return 0;}

wchar_t *g2pvt_cell_value_of_last_gv_edit(HWND hwndControl) { return 0;}

wchar_t *g2pvt_tabular_view_value(HWND hwndControl) { return 0;}

wchar_t *g2pvt_control_value_of_duration(HWND hwndControl) { return 0;}

wchar_t *g2pvt_get_contents_of_gensym_edit_control(HWND hwndControl,
											 CONTROLITEM *pitem) {
	return 0;
}

wchar_t *g2pvt_control_value_of_twng_spinner(HWND hwndControl) { return 0;}

wchar_t *g2pvt_control_value_of_check_listbox(HWND hwndControl,
											 CONTROLITEM *pitem) {
	return 0;
}

wchar_t *g2pvt_get_contents_of_G2TabWidget_control(HWND hwndControl,
											 CONTROLITEM *pitem) {
	return 0;
}

LRESULT g2pvt_grid_view_on_wm_notify(NMHDR *pnmhdr, HWND hwndDlg, 
									 CONTROLITEM *pcontrol) {
	return 0;
}

void g2pvt_cleanup_tab_pages(DIALOGINFO *pDialogInfo) {}

void g2pvt_clear_mfc_control_data(CONTROLITEM *pcontrol) {}

void g2pvt_process_advanced_color (WPARAM, HWND hWndDlg, CONTROLITEM *pControl) 
{
}

BOOL g2pvt_check_list_box_wm_command (HWND hwndDlg, long controlId,
									  CONTROLITEM *pcontrol, int notifyCode) {
	return FALSE;
}

#endif
