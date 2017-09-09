// G2OpcHiddenWin.cpp: implementation of the CG2OpcHiddenWin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2OpcHiddenWin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CG2OpcHiddenWin::CG2OpcHiddenWin()
{

}

CG2OpcHiddenWin::~CG2OpcHiddenWin()
{

}

HWND CG2OpcHiddenWin::Create()
{
	RECT rc;
	memset(&rc,0,sizeof(RECT));
	m_hwnd = CWindowImpl<CG2OpcHiddenWin>::Create(NULL,rc,_T("G2-OPC Client Hidden Notification Window"),WS_OVERLAPPEDWINDOW,0);
    CServerList::m_opc1 = true ;
    CServerList::m_opc2 = true ;
    CServerList::m_opc3 = true ;
    return m_hwnd ;
}


/* ========================================================================== */
/*                                                                            */
/*             Create the hidden window that will process messages.           */
/*                    Put an icon in the notification tray.                   */
/*                                                                            */
/* ========================================================================== */
LRESULT CG2OpcHiddenWin::OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
    m_hIcon = m_trayIcon.LoadIconResource(IDI_SMALL) ;
	m_trayIcon.Create(this, IDC_G2OPC, _T("G2-OPC Client Bridge"), m_hIcon, WM_TRAYNOTIFY);
    m_trayIcon.SetDefaultMenuItem(IDM_ABOUT);

    // Configure the program from "cfgfile.ini"
    // ----------------------------------------
    if (FAILED(OpcUtils::InitializeFromIniFile(INI_FILE)))
        log_message(TL_ERRORS, L"Failed to initialize from configfile.ini");

	bHandled=TRUE;
	return 0L;
}


LRESULT CG2OpcHiddenWin::OnTrayNotification(UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	return !m_trayIcon.OnTrayNotification(wParam,lParam); // invert the output
}

LRESULT CG2OpcHiddenWin::OnCtrlPanel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    if (g_dlg_open)
        return 1 ;
    CCtrlPanel dlg ;
    dlg.DoModal() ;
    return 0L ;
}

LRESULT CG2OpcHiddenWin::OnAutoDiscovery(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    if (g_dlg_open)
        return 1 ;
    CServerList dlg ;
    dlg.DoModal() ;
    return 0L ;
}

LRESULT CG2OpcHiddenWin::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    if (g_dlg_open)
        return 1 ;
    g_dlg_open = TRUE ;
    CSimpleDialog<IDD_ABOUTBOX> dlg ;
    dlg.DoModal() ;
    g_dlg_open = FALSE ;
    bHandled = TRUE ;
    return 0L ;
}


LRESULT CG2OpcHiddenWin::OnExit(WORD, WORD, HWND, BOOL& bHandled)
{
    log_message(TL_INFO,L"Operator Request to Shutdown G2-OPC Client Bridge Received.") ;
    g_shutdown_request = true ;
    while (g_shutdown_request)
        Sleep(50) ;
	PostMessage(WM_QUIT);
	bHandled=TRUE;
	return 0L;
}

LRESULT CG2OpcHiddenWin::OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled)
{
	// Remove icon from trey
	m_trayIcon.RemoveIcon();

	// Stop running of GsiLoop thread
	// -------------------
	g_shutdown_request = true;

	// Wait until GsiLoop thread has finished
	WaitForSingleObject(g_hGsiThread, INFINITE);

	// Post WM_QUIT message to quit
	PostMessage(WM_QUIT);

	bHandled = TRUE;
	return 0L;
}
