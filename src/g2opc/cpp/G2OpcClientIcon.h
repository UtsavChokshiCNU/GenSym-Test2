// G2OpcClientIcon.h: interface for the G2OpcClientIcon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G2OPCCLIENTICON_H__876147FA_DF02_4AFB_B4BE_9807B1731E67__INCLUDED_)
#define AFX_G2OPCCLIENTICON_H__876147FA_DF02_4AFB_B4BE_9807B1731E67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

class G2OpcClientIcon  
{
public:
	//Constructor & Destructor
	G2OpcClientIcon();
	virtual ~G2OpcClientIcon();
	
	BOOL    Create(CWindow* pNotifyWnd, UINT uID, LPCTSTR pszTooltipText, HICON hIcon, UINT nNotifyMessage);                  
    void    SetDefaultMenuItem(UINT uiMenuItem) ;
    LRESULT OnTrayNotification(WPARAM wID, LPARAM lEvent) ;
    void    RemoveIcon() ;

	//Helper functions to load tray icon from resources
	static HICON LoadIconResource(LPCTSTR lpIconName);
	static HICON LoadIconResource(UINT nIDResource);

protected:
	NOTIFYICONDATA        m_NotifyIconData;
	BOOL                  m_bCreated;
	BOOL				  m_bHidden;
	CWindow*			  m_pNotificationWnd;
	HMENU                 m_Menu;
	UINT                  m_uiDefaultMenuItem ;
};

#endif // !defined(AFX_G2OPCCLIENTICON_H__876147FA_DF02_4AFB_B4BE_9807B1731E67__INCLUDED_)
