// CtrlPanel.h : Declaration of the CCtrlPanel

#ifndef __CTRLPANEL_H_
#define __CTRLPANEL_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CCtrlPanel
class CCtrlPanel : 
	public CDialogImpl<CCtrlPanel>
{
public:
    CCtrlPanel()
	{
	}

	~CCtrlPanel()
	{
	}

	enum { IDD = IDD_CTRLPANEL };

BEGIN_MSG_MAP(CCtrlPanel)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) ;
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) ;

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
        g_dlg_open = false ;
		return 0;
	}
protected:
    static long radioButtons[] ;
};

#endif //__CTRLPANEL_H_
