//
// Type-safe message maps for MFC
// See Q195032 in MSDN. Other macros initially from afmsg_.h
// To be used only with VC6. VS.Net and later already have these
//
#if defined(_MFC_VER) && (_MFC_VER<0x0900) //VS2008 MFC
#if _MFC_VER > 0x0601
#define SS(x) #x
#define SSS(x) SS(x)
#pragma message(__FILE__ ":" SSS(__LINE__) ": Warning: You may need to update these macros for MFC version " SSS(_MFC_VER))
#undef SSS
#undef SS
#endif

#undef ON_COMMAND
#undef ON_COMMAND_RANGE
#undef ON_COMMAND_EX
#undef ON_COMMAND_EX_RANGE
#undef ON_UPDATE_COMMAND_UI
#undef ON_UPDATE_COMMAND_UI_RANGE
#undef ON_NOTIFY
#undef ON_NOTIFY_RANGE
#undef ON_NOTIFY_EX
#undef ON_NOTIFY_EX_RANGE
#undef ON_CONTROL
#undef ON_CONTROL_RANGE
#undef ON_CONTROL_REFLECT
#undef ON_CONTROL_REFLECT_EX
#undef ON_NOTIFY_REFLECT
#undef ON_NOTIFY_REFLECT_EX
#undef ON_UPDATE_COMMAND_UI_REFLECT
#undef ON_WM_CREATE
#undef ON_WM_COPYDATA
#undef ON_WM_DESTROY
#undef ON_WM_MOVE
#undef ON_WM_SIZE
#undef ON_WM_ACTIVATE
#undef ON_WM_SETFOCUS
#undef ON_WM_KILLFOCUS
#undef ON_WM_ENABLE
#undef ON_WM_HELPINFO
#undef ON_WM_PAINT
#undef ON_WM_CLOSE
#undef ON_WM_QUERYENDSESSION
#undef ON_WM_QUERYOPEN
#undef ON_WM_ERASEBKGND
#undef ON_WM_SYSCOLORCHANGE
#undef ON_WM_ENDSESSION
#undef ON_WM_SHOWWINDOW
#undef ON_WM_CTLCOLOR
#undef ON_WM_CTLCOLOR_REFLECT
#undef ON_WM_SETTINGCHANGE
#undef ON_WM_WININICHANGE
#undef ON_WM_DEVMODECHANGE
#undef ON_WM_ACTIVATEAPP
#undef ON_WM_FONTCHANGE
#undef ON_WM_TIMECHANGE
#undef ON_WM_CANCELMODE
#undef ON_WM_SETCURSOR
#undef ON_WM_MOUSEACTIVATE
#undef ON_WM_CHILDACTIVATE
#undef ON_WM_GETMINMAXINFO
#undef ON_WM_ICONERASEBKGND
#undef ON_WM_SPOOLERSTATUS
#undef ON_WM_DRAWITEM
#undef ON_WM_DRAWITEM_REFLECT
#undef ON_WM_MEASUREITEM
#undef ON_WM_MEASUREITEM_REFLECT
#undef ON_WM_DELETEITEM
#undef ON_WM_DELETEITEM_REFLECT
#undef ON_WM_CHARTOITEM
#undef ON_WM_CHARTOITEM_REFLECT
#undef ON_WM_VKEYTOITEM
#undef ON_WM_VKEYTOITEM_REFLECT
#undef ON_WM_QUERYDRAGICON
#undef ON_WM_COMPAREITEM
#undef ON_WM_COMPAREITEM_REFLECT
#undef ON_WM_COMPACTING
#undef ON_WM_NCCREATE
#undef ON_WM_NCDESTROY
#undef ON_WM_NCCALCSIZE
#undef ON_WM_NCHITTEST
#undef ON_WM_NCPAINT
#undef ON_WM_NCACTIVATE
#undef ON_WM_GETDLGCODE
#undef ON_WM_NCMOUSEMOVE
#undef ON_WM_NCLBUTTONDOWN
#undef ON_WM_NCLBUTTONUP
#undef ON_WM_NCLBUTTONDBLCLK
#undef ON_WM_NCRBUTTONDOWN
#undef ON_WM_NCRBUTTONUP
#undef ON_WM_NCRBUTTONDBLCLK
#undef ON_WM_NCMBUTTONDOWN
#undef ON_WM_NCMBUTTONUP
#undef ON_WM_NCMBUTTONDBLCLK
#undef ON_WM_KEYDOWN
#undef ON_WM_KEYUP
#undef ON_WM_CHAR
#undef ON_WM_DEADCHAR
#undef ON_WM_SYSKEYDOWN
#undef ON_WM_SYSKEYUP
#undef ON_WM_SYSCHAR
#undef ON_WM_SYSDEADCHAR
#undef ON_WM_SYSCOMMAND
#undef ON_WM_TCARD
#undef ON_WM_TIMER
#undef ON_WM_HSCROLL
#undef ON_WM_HSCROLL_REFLECT
#undef ON_WM_VSCROLL
#undef ON_WM_VSCROLL_REFLECT
#undef ON_WM_INITMENU
#undef ON_WM_INITMENUPOPUP
#undef ON_WM_MENUSELECT
#undef ON_WM_MENUCHAR
#undef ON_WM_ENTERIDLE
#undef ON_WM_MOUSEMOVE
#undef ON_WM_MOUSEWHEEL
#undef ON_WM_LBUTTONDOWN
#undef ON_WM_LBUTTONUP
#undef ON_WM_LBUTTONDBLCLK
#undef ON_WM_RBUTTONDOWN
#undef ON_WM_RBUTTONUP
#undef ON_WM_RBUTTONDBLCLK
#undef ON_WM_MBUTTONDOWN
#undef ON_WM_MBUTTONUP
#undef ON_WM_MBUTTONDBLCLK
#undef ON_WM_PARENTNOTIFY
#undef ON_WM_PARENTNOTIFY_REFLECT
#undef ON_WM_MDIACTIVATE
#undef ON_WM_RENDERFORMAT
#undef ON_WM_RENDERALLFORMATS
#undef ON_WM_DESTROYCLIPBOARD
#undef ON_WM_DRAWCLIPBOARD
#undef ON_WM_PAINTCLIPBOARD
#undef ON_WM_VSCROLLCLIPBOARD
#undef ON_WM_CONTEXTMENU
#undef ON_WM_SIZECLIPBOARD
#undef ON_WM_ASKCBFORMATNAME
#undef ON_WM_CHANGECBCHAIN
#undef ON_WM_HSCROLLCLIPBOARD
#undef ON_WM_QUERYNEWPALETTE
#undef ON_WM_PALETTECHANGED
#undef ON_WM_PALETTEISCHANGING
#undef ON_WM_DROPFILES
#undef ON_WM_WINDOWPOSCHANGING
#undef ON_WM_WINDOWPOSCHANGED
#undef ON_WM_EXITMENULOOP
#undef ON_WM_ENTERMENULOOP
#undef ON_WM_STYLECHANGED
#undef ON_WM_STYLECHANGING
#undef ON_WM_SIZING
#undef ON_WM_MOVING
#undef ON_WM_CAPTURECHANGED
#undef ON_WM_DEVICECHANGE
#undef ON_MESSAGE
#undef ON_REGISTERED_MESSAGE
#undef ON_THREAD_MESSAGE
#undef ON_REGISTERED_THREAD_MESSAGE

#define ON_COMMAND(id, memberFxn) \
	{ WM_COMMAND, CN_COMMAND, (WORD)id, (WORD)id, AfxSig_vv, (AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(void)>(&memberFxn)) },

#define ON_COMMAND_RANGE(id, idLast, memberFxn) \
	{ WM_COMMAND, CN_COMMAND, (WORD)id, (WORD)idLast, AfxSig_vw, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(UINT)>(&memberFxn)) },

#define ON_COMMAND_EX(id, memberFxn) \
	{ WM_COMMAND, CN_COMMAND, (WORD)id, (WORD)id, AfxSig_bw, \
		(AFX_PMSG)(static_cast<BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT)>(&memberFxn)) },

#define ON_COMMAND_EX_RANGE(id, idLast, memberFxn) \
	{ WM_COMMAND, CN_COMMAND, (WORD)id, (WORD)idLast, AfxSig_bw, \
		(AFX_PMSG)(static_cast<BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT)>(&memberFxn)) },

#define ON_UPDATE_COMMAND_UI(id, memberFxn) \
	{ WM_COMMAND, CN_UPDATE_COMMAND_UI, (WORD)id, (WORD)id, AfxSig_cmdui, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(CCmdUI*)>(&memberFxn)) },

#define ON_UPDATE_COMMAND_UI_RANGE(id, idLast, memberFxn) \
	{ WM_COMMAND, CN_UPDATE_COMMAND_UI, (WORD)id, (WORD)idLast, AfxSig_cmdui, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(CCmdUI*)>(&memberFxn)) },

#define ON_NOTIFY(wNotifyCode, id, memberFxn) \
	{ WM_NOTIFY, (WORD)(int)wNotifyCode, (WORD)id, (WORD)id, AfxSig_vNMHDRpl, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(NMHDR*, LRESULT*)>(&memberFxn)) },

#define ON_NOTIFY_RANGE(wNotifyCode, id, idLast, memberFxn) \
	{ WM_NOTIFY, (WORD)(int)wNotifyCode, (WORD)id, (WORD)idLast, AfxSig_vwNMHDRpl, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(UINT, NMHDR*, LRESULT*)>(&memberFxn)) },

#define ON_NOTIFY_EX(wNotifyCode, id, memberFxn) \
	{ WM_NOTIFY, (WORD)(int)wNotifyCode, (WORD)id, (WORD)id, AfxSig_bwNMHDRpl, \
		(AFX_PMSG)(static_cast<BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT, NMHDR*, LRESULT*)>(&memberFxn)) },

#define ON_NOTIFY_EX_RANGE(wNotifyCode, id, idLast, memberFxn) \
	{ WM_NOTIFY, (WORD)(int)wNotifyCode, (WORD)id, (WORD)idLast, AfxSig_bwNMHDRpl, \
		(AFX_PMSG)(static_cast<BOOL (AFX_MSG_CALL CCmdTarget::*)(UINT, NMHDR*, LRESULT*)>(&memberFxn)) },

#define ON_CONTROL(wNotifyCode, id, memberFxn) \
	{ WM_COMMAND, (WORD)wNotifyCode, (WORD)id, (WORD)id, AfxSig_vv, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(void)>(&memberFxn)) },

#define ON_CONTROL_RANGE(wNotifyCode, id, idLast, memberFxn) \
	{ WM_COMMAND, (WORD)wNotifyCode, (WORD)id, (WORD)idLast, AfxSig_vw, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(UINT)>(&memberFxn)) },

#define ON_CONTROL_REFLECT(wNotifyCode, memberFxn) \
	{ WM_COMMAND+WM_REFLECT_BASE, (WORD)wNotifyCode, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(void)>(&memberFxn)) },

#define ON_CONTROL_REFLECT_EX(wNotifyCode, memberFxn) \
	{ WM_COMMAND+WM_REFLECT_BASE, (WORD)wNotifyCode, 0, 0, AfxSig_bv, \
		(AFX_PMSG)(static_cast<BOOL (AFX_MSG_CALL CCmdTarget::*)()>(&memberFxn)) },

#define ON_NOTIFY_REFLECT(wNotifyCode, memberFxn) \
	{ WM_NOTIFY+WM_REFLECT_BASE, (WORD)(int)wNotifyCode, 0, 0, AfxSig_vNMHDRpl, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(NMHDR*, LRESULT*)>(&memberFxn)) },

#define ON_NOTIFY_REFLECT_EX(wNotifyCode, memberFxn) \
	{ WM_NOTIFY+WM_REFLECT_BASE, (WORD)(int)wNotifyCode, 0, 0, AfxSig_bNMHDRpl, \
		(AFX_PMSG)(static_cast<BOOL (AFX_MSG_CALL CCmdTarget::*)(NMHDR*, LRESULT*)>(&memberFxn)) },

#define ON_UPDATE_COMMAND_UI_REFLECT(memberFxn) \
	{ WM_COMMAND+WM_REFLECT_BASE, (WORD)CN_UPDATE_COMMAND_UI, 0, 0, AfxSig_cmdui, \
		(AFX_PMSG)(static_cast<void (AFX_MSG_CALL CCmdTarget::*)(CCmdUI*)>(&memberFxn)) },

/////////////////////////////////////////////////////////////////////////////
// Message map tables for Windows messages

#define ON_WM_CREATE() \
	{ WM_CREATE, 0, 0, 0, AfxSig_is, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(LPCREATESTRUCT)>(&OnCreate)) },
#define ON_WM_COPYDATA() \
	{ WM_COPYDATA, 0, 0, 0, AfxSig_bWCDS, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(CWnd*, COPYDATASTRUCT*)>(&OnCopyData)) },
#define ON_WM_DESTROY() \
	{ WM_DESTROY, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnDestroy)) },
#define ON_WM_MOVE() \
	{ WM_MOVE, 0, 0, 0, AfxSig_vvii, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(int, int)>(&OnMove)) },
#define ON_WM_SIZE() \
	{ WM_SIZE, 0, 0, 0, AfxSig_vwii, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, int, int)>(&OnSize)) },
#define ON_WM_ACTIVATE() \
	{ WM_ACTIVATE, 0, 0, 0, AfxSig_vwWb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CWnd*, BOOL)>(&OnActivate)) },
#define ON_WM_SETFOCUS() \
	{ WM_SETFOCUS, 0, 0, 0, AfxSig_vW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*)>(&OnSetFocus)) },
#define ON_WM_KILLFOCUS() \
	{ WM_KILLFOCUS, 0, 0, 0, AfxSig_vW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*)>(&OnKillFocus)) },
#define ON_WM_ENABLE() \
	{ WM_ENABLE, 0, 0, 0, AfxSig_vb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL)>(&OnEnable)) },
#define ON_WM_HELPINFO() \
	{ WM_HELP, 0, 0, 0, AfxSig_bHELPINFO, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(HELPINFO*)>(&OnHelpInfo)) },
#define ON_WM_PAINT() \
	{ WM_PAINT, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnPaint)) },
#define ON_WM_CLOSE() \
	{ WM_CLOSE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnClose)) },
#define ON_WM_QUERYENDSESSION() \
	{ WM_QUERYENDSESSION, 0, 0, 0, AfxSig_bv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(void)>(&OnQueryEndSession)) },
#define ON_WM_QUERYOPEN() \
	{ WM_QUERYOPEN, 0, 0, 0, AfxSig_bv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(void)>(&OnQueryOpen)) },
#define ON_WM_ERASEBKGND() \
	{ WM_ERASEBKGND, 0, 0, 0, AfxSig_bD, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(CDC*)>(&OnEraseBkgnd)) },
#define ON_WM_SYSCOLORCHANGE() \
	{ WM_SYSCOLORCHANGE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnSysColorChange)) },
#define ON_WM_ENDSESSION() \
	{ WM_ENDSESSION, 0, 0, 0, AfxSig_vb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL)>(&OnEndSession)) },
#define ON_WM_SHOWWINDOW() \
	{ WM_SHOWWINDOW, 0, 0, 0, AfxSig_vbw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL, UINT)>(&OnShowWindow)) },
#define ON_WM_CTLCOLOR() \
	{ WM_CTLCOLOR, 0, 0, 0, AfxSig_hDWw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<HBRUSH (AFX_MSG_CALL CWnd::*)(CDC*, CWnd*, UINT)>(&OnCtlColor)) },
#define ON_WM_CTLCOLOR_REFLECT() \
	{ WM_CTLCOLOR+WM_REFLECT_BASE, 0, 0, 0, AfxSig_hDw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<HBRUSH (AFX_MSG_CALL CWnd::*)(CDC*, UINT)>(CtlColor)) },
#if (WINVER >= 0x0400)
#define ON_WM_SETTINGCHANGE() \
	{ WM_SETTINGCHANGE, 0, 0, 0, AfxSig_vws, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPCTSTR)>(&OnSettingChange)) },
#endif
#define ON_WM_WININICHANGE() \
	{ WM_WININICHANGE, 0, 0, 0, AfxSig_vs, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(LPCTSTR)>(&OnWinIniChange)) },
#define ON_WM_DEVMODECHANGE() \
	{ WM_DEVMODECHANGE, 0, 0, 0, AfxSig_vs, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(LPTSTR)>(&OnDevModeChange)) },
#define ON_WM_ACTIVATEAPP() \
	{ WM_ACTIVATEAPP, 0, 0, 0, AfxSig_vbh, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL, HTASK)>(&OnActivateApp)) },
#define ON_WM_FONTCHANGE() \
	{ WM_FONTCHANGE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnFontChange)) },
#define ON_WM_TIMECHANGE() \
	{ WM_TIMECHANGE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnTimeChange)) },
#define ON_WM_CANCELMODE() \
	{ WM_CANCELMODE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnCancelMode)) },
#define ON_WM_SETCURSOR() \
	{ WM_SETCURSOR, 0, 0, 0, AfxSig_bWww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(CWnd*, UINT, UINT)>(&OnSetCursor)) },
#define ON_WM_MOUSEACTIVATE() \
	{ WM_MOUSEACTIVATE, 0, 0, 0, AfxSig_iWww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(CWnd*, UINT, UINT)>(&OnMouseActivate)) },
#define ON_WM_CHILDACTIVATE() \
	{ WM_CHILDACTIVATE, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnChildActivate)) },
#define ON_WM_GETMINMAXINFO() \
	{ WM_GETMINMAXINFO, 0, 0, 0, AfxSig_vs, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(MINMAXINFO*)>(&OnGetMinMaxInfo)) },
#define ON_WM_ICONERASEBKGND() \
	{ WM_ICONERASEBKGND, 0, 0, 0, AfxSig_vD, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CDC*)>(&OnIconEraseBkgnd)) },
#define ON_WM_SPOOLERSTATUS() \
	{ WM_SPOOLERSTATUS, 0, 0, 0, AfxSig_vww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT)>(&OnSpoolerStatus)) },
#define ON_WM_DRAWITEM() \
	{ WM_DRAWITEM, 0, 0, 0, AfxSig_vOWNER, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(int, LPDRAWITEMSTRUCT)>(&OnDrawItem)) },
#define ON_WM_DRAWITEM_REFLECT() \
	{ WM_DRAWITEM+WM_REFLECT_BASE, 0, 0, 0, AfxSig_vs, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(LPDRAWITEMSTRUCT)>(DrawItem)) },
#define ON_WM_MEASUREITEM() \
	{ WM_MEASUREITEM, 0, 0, 0, AfxSig_vOWNER, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(int, LPMEASUREITEMSTRUCT)>(&OnMeasureItem)) },
#define ON_WM_MEASUREITEM_REFLECT() \
	{ WM_MEASUREITEM+WM_REFLECT_BASE, 0, 0, 0, AfxSig_vs, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(LPMEASUREITEMSTRUCT)>(MeasureItem)) },
#define ON_WM_DELETEITEM() \
	{ WM_DELETEITEM, 0, 0, 0, AfxSig_vOWNER, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(int, LPDELETEITEMSTRUCT)>(&OnDeleteItem)) },
#define ON_WM_DELETEITEM_REFLECT() \
	{ WM_DELETEITEM+WM_REFLECT_BASE, 0, 0, 0, AfxSig_vs, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(LPDELETEITEMSTRUCT)>(DeleteItem)) },
#define ON_WM_CHARTOITEM() \
	{ WM_CHARTOITEM, 0, 0, 0, AfxSig_iwWw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(UINT, CListBox*, UINT)>(&OnCharToItem)) },
#define ON_WM_CHARTOITEM_REFLECT() \
	{ WM_CHARTOITEM+WM_REFLECT_BASE, 0, 0, 0, AfxSig_iww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(UINT, UINT)>(CharToItem)) },
#define ON_WM_VKEYTOITEM() \
	{ WM_VKEYTOITEM, 0, 0, 0, AfxSig_iwWw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(UINT, CListBox*, UINT)>(&OnVKeyToItem)) },
#define ON_WM_VKEYTOITEM_REFLECT() \
	{ WM_VKEYTOITEM+WM_REFLECT_BASE, 0, 0, 0, AfxSig_iww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(UINT, UINT)>(VKeyToItem)) },
#define ON_WM_QUERYDRAGICON() \
	{ WM_QUERYDRAGICON, 0, 0, 0, AfxSig_hv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<HCURSOR (AFX_MSG_CALL CWnd::*)()>(&OnQueryDragIcon)) },
#define ON_WM_COMPAREITEM() \
	{ WM_COMPAREITEM, 0, 0, 0, AfxSig_iis, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(int, LPCOMPAREITEMSTRUCT)>(&OnCompareItem)) },
#define ON_WM_COMPAREITEM_REFLECT() \
	{ WM_COMPAREITEM+WM_REFLECT_BASE, 0, 0, 0, AfxSig_is, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(LPCOMPAREITEMSTRUCT)>(CompareItem)) },
#define ON_WM_COMPACTING() \
	{ WM_COMPACTING, 0, 0, 0, AfxSig_vw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT)>(&OnCompacting)) },
#define ON_WM_NCCREATE() \
	{ WM_NCCREATE, 0, 0, 0, AfxSig_is, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(LPCREATESTRUCT)>(&OnNcCreate)) },
#define ON_WM_NCDESTROY() \
	{ WM_NCDESTROY, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnNcDestroy)) },
#define ON_WM_NCCALCSIZE() \
	{ WM_NCCALCSIZE, 0, 0, 0, AfxSig_vCALC, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL, NCCALCSIZE_PARAMS*)>(&OnNcCalcSize)) },
#define ON_WM_NCHITTEST() \
	{ WM_NCHITTEST, 0, 0, 0, AfxSig_wp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<UINT (AFX_MSG_CALL CWnd::*)(CPoint)>(&OnNcHitTest)) },
#define ON_WM_NCPAINT() \
	{ WM_NCPAINT, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnNcPaint)) },
#define ON_WM_NCACTIVATE() \
	{ WM_NCACTIVATE, 0, 0, 0, AfxSig_bb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(BOOL)>(&OnNcActivate)) },
#define ON_WM_GETDLGCODE() \
	{ WM_GETDLGCODE, 0, 0, 0, AfxSig_wv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<UINT (AFX_MSG_CALL CWnd::*)(void)>(&OnGetDlgCode)) },
#define ON_WM_NCMOUSEMOVE() \
	{ WM_NCMOUSEMOVE, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcMouseMove)) },
#define ON_WM_NCLBUTTONDOWN() \
	{ WM_NCLBUTTONDOWN, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcLButtonDown)) },
#define ON_WM_NCLBUTTONUP() \
	{ WM_NCLBUTTONUP, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcLButtonUp)) },
#define ON_WM_NCLBUTTONDBLCLK() \
	{ WM_NCLBUTTONDBLCLK, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcLButtonDblClk)) },
#define ON_WM_NCRBUTTONDOWN() \
	{ WM_NCRBUTTONDOWN, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcRButtonDown)) },
#define ON_WM_NCRBUTTONUP() \
	{ WM_NCRBUTTONUP, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcRButtonUp)) },
#define ON_WM_NCRBUTTONDBLCLK() \
	{ WM_NCRBUTTONDBLCLK, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcRButtonDblClk)) },
#define ON_WM_NCMBUTTONDOWN() \
	{ WM_NCMBUTTONDOWN, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcMButtonDown)) },
#define ON_WM_NCMBUTTONUP() \
	{ WM_NCMBUTTONUP, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcMButtonUp)) },
#define ON_WM_NCMBUTTONDBLCLK() \
	{ WM_NCMBUTTONDBLCLK, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnNcMButtonDblClk)) },
#define ON_WM_KEYDOWN() \
	{ WM_KEYDOWN, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnKeyDown)) },
#define ON_WM_KEYUP() \
	{ WM_KEYUP, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnKeyUp)) },
#define ON_WM_CHAR() \
	{ WM_CHAR, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnChar)) },
#define ON_WM_DEADCHAR() \
	{ WM_DEADCHAR, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnDeadChar)) },
#define ON_WM_SYSKEYDOWN() \
	{ WM_SYSKEYDOWN, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnSysKeyDown)) },
#define ON_WM_SYSKEYUP() \
	{ WM_SYSKEYUP, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnSysKeyUp)) },
#define ON_WM_SYSCHAR() \
	{ WM_SYSCHAR, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnSysChar)) },
#define ON_WM_SYSDEADCHAR() \
	{ WM_SYSDEADCHAR, 0, 0, 0, AfxSig_vwww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, UINT)>(&OnSysDeadChar)) },
#define ON_WM_SYSCOMMAND() \
	{ WM_SYSCOMMAND, 0, 0, 0, AfxSig_vwl, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPARAM)>(&OnSysCommand)) },
#define ON_WM_TCARD() \
	{ WM_TCARD, 0, 0, 0, AfxSig_vwl, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, DWORD)>(&OnTCard)) },
#define ON_WM_TIMER() \
	{ WM_TIMER, 0, 0, 0, AfxSig_vw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT)>(&OnTimer)) },
#define ON_WM_HSCROLL() \
	{ WM_HSCROLL, 0, 0, 0, AfxSig_vwwW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, CScrollBar*)>(&OnHScroll)) },
#define ON_WM_HSCROLL_REFLECT() \
	{ WM_HSCROLL+WM_REFLECT_BASE, 0, 0, 0, AfxSig_vwwx, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT)>(HScroll)) },
#define ON_WM_VSCROLL() \
	{ WM_VSCROLL, 0, 0, 0, AfxSig_vwwW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, CScrollBar*)>(&OnVScroll)) },
#define ON_WM_VSCROLL_REFLECT() \
	{ WM_VSCROLL+WM_REFLECT_BASE, 0, 0, 0, AfxSig_vwwx, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT)>(VScroll)) },
#define ON_WM_INITMENU() \
	{ WM_INITMENU, 0, 0, 0, AfxSig_vM, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CMenu*)>(&OnInitMenu)) },
#define ON_WM_INITMENUPOPUP() \
	{ WM_INITMENUPOPUP, 0, 0, 0, AfxSig_vMwb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CMenu*, UINT, BOOL)>(&OnInitMenuPopup)) },
#define ON_WM_MENUSELECT() \
	{ WM_MENUSELECT, 0, 0, 0, AfxSig_vwwh, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, UINT, HMENU)>(&OnMenuSelect)) },
#define ON_WM_MENUCHAR() \
	{ WM_MENUCHAR, 0, 0, 0, AfxSig_lwwM, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<LRESULT (AFX_MSG_CALL CWnd::*)(UINT, UINT, CMenu*)>(&OnMenuChar)) },
#define ON_WM_ENTERIDLE() \
	{ WM_ENTERIDLE, 0, 0, 0, AfxSig_vwW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CWnd*)>(&OnEnterIdle)) },
#define ON_WM_MOUSEMOVE() \
	{ WM_MOUSEMOVE, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnMouseMove)) },
#define ON_WM_MOUSEWHEEL() \
	{ WM_MOUSEWHEEL, 0, 0, 0, AfxSig_bwsp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(UINT, short, CPoint)>(&OnMouseWheel)) },
#define ON_WM_LBUTTONDOWN() \
	{ WM_LBUTTONDOWN, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnLButtonDown)) },
#define ON_WM_LBUTTONUP() \
	{ WM_LBUTTONUP, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnLButtonUp)) },
#define ON_WM_LBUTTONDBLCLK() \
	{ WM_LBUTTONDBLCLK, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnLButtonDblClk)) },
#define ON_WM_RBUTTONDOWN() \
	{ WM_RBUTTONDOWN, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnRButtonDown)) },
#define ON_WM_RBUTTONUP() \
	{ WM_RBUTTONUP, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnRButtonUp)) },
#define ON_WM_RBUTTONDBLCLK() \
	{ WM_RBUTTONDBLCLK, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnRButtonDblClk)) },
#define ON_WM_MBUTTONDOWN() \
	{ WM_MBUTTONDOWN, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnMButtonDown)) },
#define ON_WM_MBUTTONUP() \
	{ WM_MBUTTONUP, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnMButtonUp)) },
#define ON_WM_MBUTTONDBLCLK() \
	{ WM_MBUTTONDBLCLK, 0, 0, 0, AfxSig_vwp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, CPoint)>(&OnMButtonDblClk)) },
#define ON_WM_PARENTNOTIFY() \
	{ WM_PARENTNOTIFY, 0, 0, 0, AfxSig_vwl, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPARAM)>(&OnParentNotify)) },
#define ON_WM_PARENTNOTIFY_REFLECT() \
	{ WM_PARENTNOTIFY+WM_REFLECT_BASE, 0, 0, 0, AfxSig_vwl, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPARAM)>(ParentNotify)) },
#define ON_WM_MDIACTIVATE() \
	{ WM_MDIACTIVATE, 0, 0, 0, AfxSig_vbWW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL, CWnd*, CWnd*)>(&OnMDIActivate)) },
#define ON_WM_RENDERFORMAT() \
	{ WM_RENDERFORMAT, 0, 0, 0, AfxSig_vw, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT)>(&OnRenderFormat)) },
#define ON_WM_RENDERALLFORMATS() \
	{ WM_RENDERALLFORMATS, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnRenderAllFormats)) },
#define ON_WM_DESTROYCLIPBOARD() \
	{ WM_DESTROYCLIPBOARD, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnDestroyClipboard)) },
#define ON_WM_DRAWCLIPBOARD() \
	{ WM_DRAWCLIPBOARD, 0, 0, 0, AfxSig_vv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)>(&OnDrawClipboard)) },
#define ON_WM_PAINTCLIPBOARD() \
	{ WM_PAINTCLIPBOARD, 0, 0, 0, AfxSig_vWh, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*, HGLOBAL)>(&OnPaintClipboard)) },
#define ON_WM_VSCROLLCLIPBOARD() \
	{ WM_VSCROLLCLIPBOARD, 0, 0, 0, AfxSig_vWww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*, UINT, UINT)>(&OnVScrollClipboard)) },
#define ON_WM_CONTEXTMENU() \
	{ WM_CONTEXTMENU, 0, 0, 0, AfxSig_vWp, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*, CPoint)>(&OnContextMenu)) },
#define ON_WM_SIZECLIPBOARD() \
	{ WM_SIZECLIPBOARD, 0, 0, 0, AfxSig_vWh, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*, HGLOBAL)>(&OnSizeClipboard)) },
#define ON_WM_ASKCBFORMATNAME() \
	{ WM_ASKCBFORMATNAME, 0, 0, 0, AfxSig_vwl, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPTSTR)>(&OnAskCbFormatName)) },
#define ON_WM_CHANGECBCHAIN() \
	{ WM_CHANGECBCHAIN, 0, 0, 0, AfxSig_vhh, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(HWND, HWND)>(&OnChangeCbChain)) },
#define ON_WM_HSCROLLCLIPBOARD() \
	{ WM_HSCROLLCLIPBOARD, 0, 0, 0, AfxSig_vWww, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*, UINT, UINT)>(&OnHScrollClipboard)) },
#define ON_WM_QUERYNEWPALETTE() \
	{ WM_QUERYNEWPALETTE, 0, 0, 0, AfxSig_bv, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(void)>(&OnQueryNewPalette)) },
#define ON_WM_PALETTECHANGED() \
	{ WM_PALETTECHANGED, 0, 0, 0, AfxSig_vW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*)>(&OnPaletteChanged)) },

#define ON_WM_PALETTEISCHANGING() \
	{ WM_PALETTEISCHANGING, 0, 0, 0, AfxSig_vW, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*)>(&OnPaletteIsChanging)) },
#define ON_WM_DROPFILES() \
	{ WM_DROPFILES, 0, 0, 0, AfxSig_vh, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(HDROP)>(&OnDropFiles)) },
#define ON_WM_WINDOWPOSCHANGING() \
	{ WM_WINDOWPOSCHANGING, 0, 0, 0, AfxSig_vPOS, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(WINDOWPOS*)>(&OnWindowPosChanging)) },
#define ON_WM_WINDOWPOSCHANGED() \
	{ WM_WINDOWPOSCHANGED, 0, 0, 0, AfxSig_vPOS, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(WINDOWPOS*)>(&OnWindowPosChanged)) },

#define ON_WM_EXITMENULOOP() \
	{ WM_EXITMENULOOP, 0, 0, 0, AfxSig_vb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL)>(&OnExitMenuLoop)) },
#define ON_WM_ENTERMENULOOP() \
	{ WM_ENTERMENULOOP, 0, 0, 0, AfxSig_vb, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(BOOL)>(&OnEnterMenuLoop)) },

#define ON_WM_STYLECHANGED() \
	{ WM_STYLECHANGED, 0, 0, 0, AfxSig_viSS, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(int, LPSTYLESTRUCT)>(&OnStyleChanged)) },
#define ON_WM_STYLECHANGING() \
	{ WM_STYLECHANGING, 0, 0, 0, AfxSig_viSS, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(int, LPSTYLESTRUCT)>(&OnStyleChanging)) },
#define ON_WM_SIZING() \
	{ WM_SIZING, 0, 0, 0, AfxSig_vwSIZING, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPRECT)>(&OnSizing)) },
#define ON_WM_MOVING() \
	{ WM_MOVING, 0, 0, 0, AfxSig_vwMOVING, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, LPRECT)>(&OnMoving)) },
#define ON_WM_CAPTURECHANGED() \
	{ WM_CAPTURECHANGED, 0, 0, 0, AfxSig_vW2, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(CWnd*)>(&OnCaptureChanged)) },
#define ON_WM_DEVICECHANGE() \
	{ WM_DEVICECHANGE, 0, 0, 0, AfxSig_bwl, \
		(AFX_PMSG)(AFX_PMSGW)(static_cast<BOOL (AFX_MSG_CALL CWnd::*)(UINT, DWORD)>(&OnDeviceChange)) },

/////////////////////////////////////////////////////////////////////////////
// User extensions for message map entries

#define ON_MESSAGE(message, memberFxn) \
    { message, 0, 0, 0, AfxSig_lwl, \
        (AFX_PMSG)(AFX_PMSGW) (static_cast<LRESULT (AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)>(&memberFxn)) },
 
#define ON_REGISTERED_MESSAGE(nMessageVariable, memberFxn) \
   { 0xC000, 0, 0, 0, (UINT)(UINT*)(&nMessageVariable), \
      (AFX_PMSG)(AFX_PMSGW)(static_cast<LRESULT (AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)>(&memberFxn)) },
 
#define ON_THREAD_MESSAGE(message, memberFxn) \
   { message, 0, 0, 0, AfxSig_vwl, \
      (AFX_PMSG)(AFX_PMSGT)(static_cast<void (AFX_MSG_CALL CWinThread::*)(WPARAM, LPARAM)>(&memberFxn)) },
 
#define ON_REGISTERED_THREAD_MESSAGE(nMessageVariable, memberFxn) \
   { 0xC000, 0, 0, 0, (UINT)(UINT*)(&nMessageVariable), \
      (AFX_PMSG)(AFX_PMSGT)(static_cast<void (AFX_MSG_CALL WinThread::*)(WPARAM, LPARAM)>(&memberFxn)) },
#endif