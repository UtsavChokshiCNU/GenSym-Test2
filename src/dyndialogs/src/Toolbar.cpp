#include "stdafx.h"
#include "FileOpenCommon.h"

void InitializeBackStack()
{
	// initialize stack data structure used by the Back button
	g_pbackStack = new STACK;
	ZeroMemory((LPVOID)g_pbackStack, sizeof(STACK));
	g_pbackStack->top = -1;
}

BOOL BackStackEmpty()
{
	if (g_pbackStack->top < 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL PushBackStack(LPCSTR pszDirectory)
{
	g_pbackStack->top++;
	strcpy(g_pbackStack->szFolders[g_pbackStack->top], pszDirectory);

	return TRUE;
}

BOOL PopBackStack(LPSTR pszPathDir)
{
	if (pszPathDir == NULL)
	{
		return FALSE;
	}

	// copy string
	lstrcpy(pszPathDir, g_pbackStack->szFolders[g_pbackStack->top]);

	// zero original
	ZeroMemory((LPVOID)&g_pbackStack->szFolders[g_pbackStack->top], _MAX_PATH);

	// decrement top
	g_pbackStack->top--;

	return TRUE;
}

void EnableBackButton(BOOL bShow)
{
	SendMessage(g_hwndToolbar, TB_ENABLEBUTTON, IDS_BACK, MAKELONG(bShow, 0));
}

void EnableUpButton(BOOL bShow)
{
	SendMessage(g_hwndToolbar, TB_ENABLEBUTTON, IDS_UP, MAKELONG(bShow, 0));
}

HWND CreateToolbar(HWND hwndParent, int x, int y)
{
	REBARBANDINFO rbBand;

	TBADDBITMAP tbab;
	TBBUTTON tbb[3];
	int stdidx = 0;
	int index = 0;

	TBBUTTON tbButtons[] = {
		{ HIST_BACK, IDS_BACK, 0, BTNS_BUTTON, 0L, 0 },
		{ VIEW_PARENTFOLDER, IDS_UP, TBSTATE_ENABLED, BTNS_BUTTON, 0L, 0 },
		{ VIEW_LIST /*VIEWMENU*/, IDS_VIEW, TBSTATE_ENABLED, BTNS_DROPDOWN, 0L, 0 }
	};

	HWND hwndTB = CreateWindowEx(
		0, 
		TOOLBARCLASSNAME, 
		(LPSTR) NULL, 
        WS_CHILD | TBSTYLE_FLAT | WS_CLIPSIBLINGS | CCS_NODIVIDER | WS_VISIBLE | CCS_NOPARENTALIGN | CS_VREDRAW | CCS_NORESIZE | WS_CLIPCHILDREN, 	
		375, //x,		// TODO: lose the magic numbers!
		7, //y + 5,		// TODO: ditto!
		100,
		30,
		hwndParent,
		(HMENU) ID_TOOLBAR,
		g_hInst, 
		NULL);

	// pass the size of the TBBUTTON structure to the toolbar
	SendMessage(hwndTB, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0);

	// back button
	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_HIST_SMALL_COLOR;
	stdidx = SendMessage(hwndTB, TB_ADDBITMAP, 0, (LPARAM)&tbab);

	tbButtons[0].iBitmap += stdidx;
	SendMessage(hwndTB, TB_ADDBUTTONS, 1, (LONG)&tbButtons[0]);

	// up and views buttons
	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_VIEW_SMALL_COLOR;
	stdidx = SendMessage(hwndTB, TB_ADDBITMAP, 0, (LPARAM)&tbab);

	tbButtons[1].iBitmap += stdidx;
	tbButtons[2].iBitmap += stdidx;
	SendMessage(hwndTB, TB_ADDBUTTONS, 2, (LONG)&tbButtons[1]);

	SendMessage(hwndTB, TB_SETEXTENDEDSTYLE, 0, (LPARAM) (DWORD) TBSTYLE_EX_DRAWDDARROWS);
	SendMessage(hwndTB, TB_AUTOSIZE, 0, 0);

	// save off the toolbar width for later use

	ShowWindow(hwndTB, SW_SHOW);

	return hwndTB;
}

BOOL DoToolbarBackBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char szPath[_MAX_PATH];
	ZeroMemory((LPVOID)szPath, _MAX_PATH);
	char szDir[_MAX_PATH];
	ZeroMemory((LPVOID)szDir, _MAX_PATH);
	char szPathDir[_MAX_PATH] = {0};
	BOOL bRet = FALSE;

	// pop the back button history list for previously saved directory
	if (!PopBackStack(szPathDir))	// caller is responsible for deleting returned string
	{
		return FALSE;
	}

	if (BackStackEmpty())
	{
		// disable toolbar Back button
		EnableBackButton(FALSE);
	}

	if (SplitDirectoryFromPath(szPathDir, szPath, szDir) < 0)
	{
		bRet = FALSE;
	}
	else
	{
        bRet = RefreshFileList(szPath, szDir);
	}

	return bRet;
}

BOOL DoToolbarUpBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndLookIn = GetDlgItem(g_hwndFileOpenDlg, IDC_LOOKIN_COMBO);

	// get the current selected index
	int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);
	if (nCurSel == 0)
	{
		// don't do anything, we're already at the top
		return TRUE;
	}

	nCurSel--;
	LockWindowUpdate(hwndLookIn);
	SendMessage(hwndLookIn, CB_SETCURSEL, nCurSel, 0);

	DoLookinComboSelChange(hwndLookIn);
	LockWindowUpdate(NULL);

	return TRUE;
}


BOOL DoToolbarNotify(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#define lpnm   ((LPNMHDR)lParam)
#define lpnmTB ((LPNMTOOLBAR)lParam)

   RECT      rc;
   TPMPARAMS tpm;
   HMENU     hPopupMenu = NULL;
   HMENU     hMenuLoaded;
   BOOL      bRet = FALSE;

   switch(lpnm->code){
      case TBN_DROPDOWN:
         SendMessage(lpnmTB->hdr.hwndFrom, TB_GETRECT, (WPARAM)lpnmTB->iItem, (LPARAM)&rc);

         MapWindowPoints(lpnmTB->hdr.hwndFrom, HWND_DESKTOP, (LPPOINT)&rc, 2);                         

         tpm.cbSize = sizeof(TPMPARAMS);
         tpm.rcExclude = rc;
         //hMenuLoaded = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_POPUP)); 
         //hPopupMenu = GetSubMenu(LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_POPUP)),0);

//         TrackPopupMenuEx(hPopupMenu,
         TrackPopupMenuEx(g_hViewsMenu,
            TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,               
            rc.left, rc.bottom, g_hwndFileOpenDlg, &tpm); 		 

//         DestroyMenu(hMenuLoaded);

      return (FALSE);
   }

   return FALSE;
}

BOOL DrawViewsMenuItem(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpdis;
	HINSTANCE hInst;
	DWORD wCheckX;
	int nTextX, nTextY;
	COLORREF clrPrevText, clrPrevBkgnd;
	nTextX = nTextY = 0;
	int x, y;
	x = y = 0;

	lpdis = (LPDRAWITEMSTRUCT)lParam;
	if (lpdis == NULL)
	{
		return FALSE;
	}

	if (lpdis->itemState & ODS_SELECTED)
	{
		clrPrevText = SetTextColor(lpdis->hDC,
			GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrPrevBkgnd = SetBkColor(lpdis->hDC,
			GetSysColor(COLOR_HIGHLIGHT));
	}
	else
	{
		clrPrevText = SetTextColor(lpdis->hDC,
			GetSysColor(COLOR_MENUTEXT));
		clrPrevBkgnd = SetBkColor(lpdis->hDC,
			GetSysColor(COLOR_MENU));
	}

    wCheckX = GetSystemMetrics(SM_CXMENUCHECK); 

	x = lpdis->rcItem.left;
	y = lpdis->rcItem.top;
	x += wCheckX + 10;	// TEMP

	// Remember to leave space in the menu item for the 
	// bitmap. Retrieve the width of the bitmap 
	// and add it to the width of the menu item. 
    //nTextX = wCheckX + lpdis->rcItem.left; 
    //nTextY = lpdis->rcItem.top; 

 	LPVIEWSMENUITEM pvmi = (LPVIEWSMENUITEM)lpdis->itemData;
	ExtTextOut(lpdis->hDC, x, y + 4, ETO_OPAQUE, &lpdis->rcItem, pvmi->pszText, strlen(pvmi->pszText), NULL); 

	int nImageId = 0;
	switch (lpdis->itemID)
	{
	case IDM_VIEW_LARGEICONS:
		nImageId = 1;
		break;
	case IDM_VIEW_SMALLICONS:
		nImageId = 2;
		break;
	case IDM_VIEW_LIST:
		nImageId = 0;
		break;
	case IDM_VIEW_DETAILS:
		nImageId = 3;
		break;
	}

	BOOL bRet = ImageList_Draw(g_hilViews, nImageId, lpdis->hDC, lpdis->rcItem.left + 3, lpdis->rcItem.top + 3, ILD_NORMAL);

	// restore original colors
	SetTextColor(lpdis->hDC, clrPrevText);
	SetTextColor(lpdis->hDC, clrPrevBkgnd);

    return TRUE; 
}

BOOL MeasurePopupMenuItem(HWND hDlg, WPARAM wParam, LPARAM lParam)
{	
	LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
	LPVIEWSMENUITEM pvmi = (LPVIEWSMENUITEM) lpmis->itemData;

	HDC hdc = GetDC(hDlg);
	SIZE size;

	GetTextExtentPoint32(hdc, pvmi->pszText, strlen(pvmi->pszText) + 1, &size);

	lpmis->itemWidth = size.cx + 20;	// TEMP - + 20
	lpmis->itemHeight = size.cy + 4;	// TEMP - + 4

	ReleaseDC(hDlg, hdc);

	return TRUE;
}
