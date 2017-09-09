// G2OpcClientIcon.cpp: implementation of the G2OpcClientIcon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G2OpcClientIcon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G2OpcClientIcon::G2OpcClientIcon()
{

}

G2OpcClientIcon::~G2OpcClientIcon()
{
    RemoveIcon() ;
}

BOOL G2OpcClientIcon::Create(CWindow* pNotifyWnd, UINT uID, LPCTSTR pszTooltipText, HICON hIcon, UINT nNotifyMessage)
{	
	m_pNotificationWnd = pNotifyWnd;
	m_Menu=::LoadMenu(_Module.GetModuleInstance(),MAKEINTRESOURCE(uID));
	_ASSERTE(m_Menu);

	HMENU submenu;
	submenu=::GetSubMenu(m_Menu,0);
//	m_HookWnd.Init(this, pNotifyWnd);
	m_NotifyIconData.cbSize = sizeof(m_NotifyIconData);
	m_NotifyIconData.hWnd = pNotifyWnd->m_hWnd;
	m_NotifyIconData.uID = uID;
	m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_NotifyIconData.uCallbackMessage = nNotifyMessage;
	m_NotifyIconData.hIcon = hIcon;
	_tcscpy(m_NotifyIconData.szTip, pszTooltipText);
	
	BOOL rVal = Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);
	m_bCreated = rVal;
	
	return rVal;
}

void G2OpcClientIcon::SetDefaultMenuItem(UINT uiMenuItem)
{
	m_uiDefaultMenuItem=uiMenuItem;
}

HICON G2OpcClientIcon::LoadIconResource(LPCTSTR lpIconName)
{
  //First try to load the 16*16 icon, if this fails, they fall
  //back on the 32*32 
  HICON hIcon = (HICON) ::LoadImage(_Module.GetModuleInstance(), lpIconName, IMAGE_ICON, 16, 16, 0);
  if (hIcon == NULL)
    hIcon = LoadIcon(_Module.GetModuleInstance(),lpIconName); //AfxGetApp()->LoadIcon(lpIconName);

  //Return the icon handle
  return hIcon;
}

HICON G2OpcClientIcon::LoadIconResource(UINT nIDResource)
{
  return LoadIconResource(MAKEINTRESOURCE(nIDResource));
}

LRESULT G2OpcClientIcon::OnTrayNotification(WPARAM wID, LPARAM lEvent)
{
	
	if (wID != m_NotifyIconData.uID)
		return 0L;
		
	HMENU submenu;

	submenu=::GetSubMenu(m_Menu,0);
	_ASSERTE(submenu);
	if (!submenu) // badly designed resource
		return 0L;
	
	if (lEvent == WM_RBUTTONUP)
	{
		//Clicking with right button brings up a context menu
		// ModifyMenu(submenu);
		
		// Make first menu item the default (bold font)
		::SetMenuDefaultItem(submenu, m_uiDefaultMenuItem, m_uiDefaultMenuItem? FALSE:TRUE); // SAW

		// Disable all three menus except the last one (shutdown) when there is dialog opened.
		if (g_dlg_open) {
			::EnableMenuItem(submenu, 0, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);
			::EnableMenuItem(submenu, 2, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);
			::EnableMenuItem(submenu, 3, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);
		}
		else {
			::EnableMenuItem(submenu, 0, MF_ENABLED | MF_BYPOSITION);
			::EnableMenuItem(submenu, 2, MF_ENABLED | MF_BYPOSITION);
			::EnableMenuItem(submenu, 3, MF_ENABLED | MF_BYPOSITION);
		}
		
		//Display and track the popup menu
		POINT pos;
		GetCursorPos(&pos);
		::SetForegroundWindow(m_NotifyIconData.hWnd);  
		::TrackPopupMenu(submenu, 0, pos.x, pos.y, 0, m_NotifyIconData.hWnd, NULL);

		::PostMessage(m_NotifyIconData.hWnd, WM_NULL, 0, 0);
		
	} 
	else if (lEvent == WM_LBUTTONDBLCLK) 
	{
		// double click received, the default action is to execute first menu item
		::SendMessage(m_NotifyIconData.hWnd, WM_COMMAND, m_uiDefaultMenuItem ? m_uiDefaultMenuItem : GetMenuItemID(submenu, 0), 0); // SAW
	}
	
	return 1; // handled
}

void G2OpcClientIcon::RemoveIcon()
{
    if (m_bCreated)
    {
        m_NotifyIconData.uFlags = 0 ;
        Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData) ;
        m_bCreated = FALSE ;
    }
}