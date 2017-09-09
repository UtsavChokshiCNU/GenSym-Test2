// G2OpcHiddenWin.h: interface for the CG2OpcHiddenWin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G2OPCHIDDENWIN_H__9F986B19_3500_4248_BB9C_E4BA80A44885__INCLUDED_)
#define AFX_G2OPCHIDDENWIN_H__9F986B19_3500_4248_BB9C_E4BA80A44885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

#define WM_TRAYNOTIFY WM_USER + 100

class CG2OpcHiddenWin : public CWindowImpl<CG2OpcHiddenWin>  
{
public:
	CG2OpcHiddenWin();
	virtual ~CG2OpcHiddenWin();

    HWND    Create() ;

protected:
	BEGIN_MSG_MAP(CTrayIconProcessingWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_TRAYNOTIFY, OnTrayNotification)
		COMMAND_HANDLER(ID_CONTROLPANEL, 0, OnCtrlPanel)
		COMMAND_HANDLER(ID_AUTODISCOVERY, 0, OnAutoDiscovery)
		COMMAND_HANDLER(ID_APP_EXIT, 0, OnExit)
		COMMAND_HANDLER(IDM_ABOUT, 0, OnAbout)
	END_MSG_MAP()

	// MessageHandler
	LRESULT OnCreate(UINT uMsg,WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg,WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTrayNotification(UINT uMsg,WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCtrlPanel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAutoDiscovery(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

    HICON           m_hIcon ;
    G2OpcClientIcon m_trayIcon;
    HWND            m_hwnd ;
};

#endif // !defined(AFX_G2OPCHIDDENWIN_H__9F986B19_3500_4248_BB9C_E4BA80A44885__INCLUDED_)
