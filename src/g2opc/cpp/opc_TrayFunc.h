#if !defined(__TRAYFUNC_H__)
#define __TRAYFUNC_H__

namespace TrayFunc
{
	void OnCommand(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void OnDestroy(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void OnTray(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void ShowPopupMenu(HWND hWnd);
	void TrayMessageHandler(HWND hWnd, UINT uMessageID);
}
#endif