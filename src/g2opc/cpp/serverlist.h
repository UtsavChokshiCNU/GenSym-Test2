// ServerList.h : Declaration of the CServerList

#ifndef __SERVERLIST_H_
#define __SERVERLIST_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CServerList
class CServerList : 
	public CDialogImpl<CServerList>
{
public:
    CServerList()
	{
	}

	~CServerList()
	{
	}

	enum { IDD = IDD_SERVERLIST };

BEGIN_MSG_MAP(CServerList)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(ID_FIND_SERVERS, OnFindServers)
	COMMAND_ID_HANDLER(ID_CLOSE_DLG, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) ;
	LRESULT OnFindServers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) ;
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) ;

    static bool    m_opc1, m_opc2, m_opc3 ;
};

#endif //__SERVERLIST_H_
