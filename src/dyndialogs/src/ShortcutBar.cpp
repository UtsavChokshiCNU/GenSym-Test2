#include "stdafx.h"
#include "FileOpenCommon.h"
#include <tchar.h>

int SHORTCUT_CXICON = 0;
int SHORTCUT_CYICON = 0;

UINT g_uAddItemMsgId = 0;		// shortcut bar add item message id
UINT g_uResetContentMsgId = 0;	// shortcut bar reset content message id

static const char _szName[] = "Icon Name";

//static TCHAR szClassName[] = _T("ShortcutBar32");
//
// Get ShortcutBar instance from the specified window
//
static ShortcutBar * GetShortcutBar(HWND hwnd)
{
    return (ShortcutBar *)GetWindowLong(hwnd, 0);
}

//
// Set ShortcutBar instance for the specified window
//
void SetShortcutBar(HWND hwnd, ShortcutBar *psb)
{
    SetWindowLong(hwnd, 0, (LONG)psb);
}

ShortcutBar::ShortcutBar(HWND hwnd)
{
	_hwnd = hwnd;
	_btnHeight = 60;
	_largeFolderIcon = NULL;
	_buttons = NULL;
	_bMouseIn = FALSE;
	ZeroMemory(_items, MAX_ITEMS*sizeof(SHORTCUTBARITEMSTRUCT));
	_nItemCount = 0;
}

ShortcutBar::~ShortcutBar()
{
}

void ShortcutBar::SetLargeFolderIcon(HICON largeFolderIcon)
{
	_largeFolderIcon = largeFolderIcon;
}

LRESULT
ShortcutBar::OnResetContent(WPARAM wParam, LPARAM lParam)
{
	// we don't have anything on the heap, so just zero out the array of structures and the item count
	ZeroMemory((LPVOID)&_items, sizeof(_items));
	_nItemCount = 0;

	return 0;
}

LRESULT 
ShortcutBar::OnAddItem(WPARAM wParam, LPARAM lParam)
{
	// lParam contains pointer to SHORTCUTBARITEMSTRUCT
	LPSHORTCUTBARITEMSTRUCT lpsbi = (LPSHORTCUTBARITEMSTRUCT)lParam;

	if (_nItemCount >= MAX_ITEMS)
	{
		// TODO: let caller know they've reached the limit
		return 0;
	}

	// increment item count
	CopyMemory((LPVOID)&(_items[_nItemCount]), (LPVOID)lpsbi, sizeof(SHORTCUTBARITEMSTRUCT));
	_nItemCount++;

	return 0;
}

LRESULT 
ShortcutBar::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	RECT cr;
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = Hwnd();

	if (_bMouseIn == FALSE)
	{
		_bMouseIn = TRUE;
		TrackMouseEvent(&tme);
	}

	GetWindowRect(Hwnd(), &cr);
	ScreenToClient(_hwnd, LPPOINT(&cr.left));
	ScreenToClient(_hwnd, LPPOINT(&cr.right));

	InvalidateRect(Hwnd(), &cr, TRUE);
	UpdateWindow(Hwnd());

	return 0L;
}

LRESULT
ShortcutBar::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	RECT cr;
	_bMouseIn = FALSE;

	GetWindowRect(Hwnd(), &cr);
	ScreenToClient(_hwnd, LPPOINT(&cr.left));
	ScreenToClient(_hwnd, LPPOINT(&cr.right));

	InvalidateRect(Hwnd(), &cr, TRUE);
	UpdateWindow(Hwnd());

	return 0L;
}

LRESULT 
ShortcutBar::OnPaint(WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rect;
	HDC hdc;
	int nSections = 0;
	int y = 0;
	POINT ptBegin, ptEnd;
	int cxClient;
	int cyClient;
	int cxText;
	TEXTMETRIC tm;
	COLORREF crBkgnd;
	int iBkgndColor;
	POINT pt;
	RECT rectSelect;

	GetClientRect(_hwnd, &rect);
	cxClient = rect.right;
	cyClient = rect.bottom;

	InvalidateRect(_hwnd, &rect, TRUE);

	// get the device context
	hdc = BeginPaint(_hwnd, &ps);

	// select a font
	SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT));
	SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));

	// measure the text
	GetTextMetrics(hdc, &tm);
	// calculate text begin
	cxText = 20;//(cyClient / 2) - ((tm.tmAveCharWidth * strlen(_szName)) / 2);

	ptBegin.x = ptBegin.y = 0; //5;
	ptEnd.x = rect.right; ptEnd.y = 0;

	//nSections = (cyClient / _btnHeight);	

	// draw the sections
	for (int i = 0; i < _nItemCount; i++)
	{
		y = ptBegin.y;

		// make a rectangle of our window area
		rectSelect.bottom = y + 60; //SHORTCUT_CYICON + 2 + tm.tmHeight;
		rectSelect.left = 0;
		rectSelect.right = cxClient;
		rectSelect.top = y;

		//MoveToEx(hdc, ptBegin.x, ptBegin.y, NULL);
		//LineTo(hdc, ptBegin.x + cyClient, ptBegin.y);

		iBkgndColor = COLOR_WINDOW;
		if (_bMouseIn == TRUE)
		{
			// figure out which quadrant we are in
			GetCursorPos(&pt);
			// convert to client coordinates
			ScreenToClient(_hwnd, &pt);

			if ((pt.y > y) && (pt.y < y + _btnHeight) )
			{
				iBkgndColor = COLOR_HIGHLIGHT;
			}
		}

		crBkgnd = GetSysColor(iBkgndColor);
		SetBkColor(hdc, crBkgnd);
		SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT));
		ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rectSelect, NULL, 0, NULL);
		//SetBkMode(hdc, TRANSPARENT);

		// calculate origin
		int xOffset = (ptEnd.x / 2) - (SHORTCUT_CXICON / 2);
		y += 2;
		// draw folder icon
		DrawIconEx(hdc, xOffset, y, _largeFolderIcon, SHORTCUT_CXICON, SHORTCUT_CYICON, 0, NULL, DI_NORMAL | DI_COMPAT);

		y += SHORTCUT_CYICON + 2;

		RECT r;
		r.top = y;
		r.bottom = y + tm.tmHeight;
		r.right = (strlen(_items[i].szDir) * tm.tmAveCharWidth) + 25;
		r.left = cxText;

		ExtTextOut(
			hdc, 
			cxText, 
			y, 
			ETO_CLIPPED | ETO_OPAQUE, 
			&r, 
			_items[i].szDir, 
			strlen(_items[i].szDir), 
			NULL);

		// adjust
		ptBegin.y += _btnHeight;
	}

	EndPaint(Hwnd(), &ps);

	return 0;
}

LRESULT
ShortcutBar::OnSize(WPARAM wParam, LPARAM lParam)
{
	return 0;	
}

LRESULT 
ShortcutBar::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	// where are we?
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	char szNthRect[30] = {0};

	int cxClient, cyClient;
	int x, y;
	RECT rectClick;
	RECT rect;

	// get client rectangle of our window
	GetClientRect(_hwnd, &rect);
	// width
	cxClient = rect.right;
	// height
	cyClient = rect.bottom;

	x = y = 0;

	for (int i = 0; i < _nItemCount; i++)
	{
		// make a rectangle of our window area
		rectClick.bottom = y + 60; 
		rectClick.left = 0;
		rectClick.right = cxClient;
		rectClick.top = y;

		if (PtInRect(&rectClick, pt))
		{
			PostMessage(g_hwndFileOpenDlg, g_uFODRefreshMsgId, (WPARAM) _items[i].szDir, (LPARAM) _items[i].szPath);
			break;
		}

		y += 60;
	}


//	HWND hwndLookin = GetDlgItem(g_hwndFileOpenDlg, IDC_LOOKIN_COMBO);
//	int nIdx = SendMessage(hwndLookin, CB_FINDSTRINGEXACT, -1, (LPARAM)(_items[i].szText));
//	SendMessage(hwndLookin, CB_SETCURSEL, nIdx, 0);

	return 0L;
}

LRESULT 
ShortcutBar::OnCommand(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0L;
}

LRESULT CALLBACK 
ShortcutBar::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve the custom structure POINTER for THIS window
	ShortcutBar *pShortcutBar = GetShortcutBar(hwnd);
	static HWND hBtn;
	HICON hiconLargeFolder = NULL;

	// user window message unique to the system; assume that we will 
	// never receive this message before all others
	g_uAddItemMsgId = RegisterWindowMessage(SB_ADDITEM_MSG_STR);
	g_uResetContentMsgId = RegisterWindowMessage(SB_RESETCONTENT_MSG_STR);

	// process user message(s)
	if (msg == g_uAddItemMsgId)		
	{
		return pShortcutBar->OnAddItem(wParam, lParam);
	}
	else if (msg == g_uResetContentMsgId)
	{
		return pShortcutBar->OnResetContent(wParam, lParam);
	}

	switch (msg)
	{
	case WM_NCCREATE:

		// allocate a new ShortcutBar instance
		pShortcutBar = new ShortcutBar(hwnd);
		::SetShortcutBar(hwnd, pShortcutBar);
	
		hiconLargeFolder = ::GetLargeFolderIcon();
		pShortcutBar->SetLargeFolderIcon(hiconLargeFolder);

		return (pShortcutBar != NULL);

	case WM_NCDESTROY:
		delete pShortcutBar;

		break;

	//case WM_SIZE:
	//	return pShortcutBar->OnSize(wParam, lParam);

	case WM_PAINT:
		return pShortcutBar->OnPaint(wParam, lParam);

	case WM_LBUTTONDOWN:
		return pShortcutBar->OnLButtonDown(wParam, lParam);

	case WM_MOUSEMOVE:
		return pShortcutBar->OnMouseMove(wParam, lParam);

	case WM_MOUSELEAVE:
		return pShortcutBar->OnMouseLeave(wParam, lParam);

	case WM_COMMAND:
		return pShortcutBar->OnCommand(hwnd, msg, wParam, lParam);

	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

HICON GetLargeFolderIcon()
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	DWORD_PTR pdw = SHGetFileInfo (
		"dummy", 
		FILE_ATTRIBUTE_DIRECTORY, 
		&sfi, 
		sizeof(sfi), 
		SHGFI_LARGEICON | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES
	);
	
	SHORTCUT_CXICON = ::GetSystemMetrics(SM_CXICON);
	SHORTCUT_CYICON = ::GetSystemMetrics(SM_CXICON);
	
	return sfi.hIcon;
}

ATOM RegisterShortcutBar(HINSTANCE hInst)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)ShortcutBar::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= sizeof(ShortcutBar*);
	wcex.hInstance		= (HINSTANCE)hInst;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);//(HBRUSH)GetStockObject(BLACK_BRUSH); 
	wcex.lpszMenuName	= (LPCTSTR)NULL;
	wcex.lpszClassName	= SHORTCUTBARCLASS;
	wcex.hIconSm		= NULL; //LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}
