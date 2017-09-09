#include "stdafx.h"
#include <shellapi.h>

	extern HMENU			g_hMenu;	// Handle to tray popup menu
	extern NOTIFYICONDATA	g_iconData;	// Tray icon structure

void TrayFunc::ShowPopupMenu(HWND hWnd)
{
	POINT pt;

	// Display the popup menu at the current cursor location
	// -----------------------------------------------------
	GetCursorPos(&pt);
	SetForegroundWindow(hWnd);
	TrackPopupMenu(g_hMenu, 0, pt.x, pt.y, 0, hWnd, 0);
	PostMessage(g_hWnd, WM_DESTROY, 0, 0);
}

void TrayFunc::TrayMessageHandler(HWND hWnd, UINT uMessageID)
{
	switch (uMessageID)
	{
	case ID_TRAY_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_TRAY_FINDSERVERS:
		break ;
	}
}

void TrayFunc::OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TrayMessageHandler(hWnd, LOWORD(wParam));
}

void TrayFunc::OnDestroy(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	DestroyMenu(g_hMenu);
	Shell_NotifyIcon(NIM_DELETE, &g_iconData);
	PostQuitMessage(0);
}

void TrayFunc::OnTray(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_RBUTTONDOWN == lParam)
	{
		ShowPopupMenu(hWnd);
	}
	else if (WM_LBUTTONDBLCLK == lParam)
	{
		TrayMessageHandler(hWnd, ID_TRAY_FINDSERVERS);
	}
}
