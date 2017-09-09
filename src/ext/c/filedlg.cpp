/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      filedlg.cpp
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s): 2004      lk, fmw
 +
 + Description:         Custom file dialog
 +
 + External Interface:  BOOL GetServerFileName(OPENFILENAME *ofn)
 +
 + Dependencies:        filedlg.{h,rc}, updown.bmp
 +
 + Modifications:
 +   4/15/04, fmw: Created from GensymFileOpenDlg.cpp
 +   4/23/04, fmw: Finish implementing: filetypes combo and filtering, sorting on
 +                 size and date, little sort arrows.
 +
 +                 Fix bugs: Reimplement shortcut parsing to fix access violations,
 +                 correct sense of use of bMustExist, correct shortcut pane colors,
 +                 comment-out bogus ListView_SetExtendedListViewStyle call, get
 +                 correct small icon size, get folder icons for LookIn combo
 +                 in a way that works on Win2K, too, fix strcpy of double-NUL
 +                 terminate strings, 
 +
 +                 Remove a bunch of dead code. Update test main.
 +
 +   4/23/04, fmw: Fix/finish views menu: remove unused owner draw code and
 +                 check radio item for current view.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef UNICODE
#  define UNICODE
#endif

#ifndef _UNICODE
#  define _UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#ifdef _WIN32_IE
#  undef _WIN32_IE
#endif
#define _WIN32_IE  0x0400

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <objbase.h>
#include <shellapi.h>
#include <commdlg.h>
#include <dlgs.h>		// edt1, etc.
#include <shlobj.h>		// SHGetSpecialFolderPath

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#define FILEDLG_INTERNAL
#include "filedlg.h"
#include "ddrsc.h"		/* Resource IDs */

/* Random resource and command IDs */
#define IDC_TOOLBAR lst3
#define IDC_PLACESBAR lst4
#define IDC_SUBDIALOG lst5
#define IDM_VIEW_LARGEICONS             32772
#define IDM_VIEW_SMALLICONS             32773
#define IDM_VIEW_LIST                   32774
#define IDM_VIEW_DETAILS                32775
#define IDS_BACK                        104
#define IDM_EXIT                        105
#define IDS_UP                          105
#define IDS_VIEW                        106

// Copy some IE 4.0 defines (we compile for IE 3.0, still)
#ifndef TB_SETEXTENDEDSTYLE
#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#endif

#ifndef TBSTYLE_EX_DRAWDDARROWS
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

#ifndef DFCS_TRANSPARENT
#define DFCS_TRANSPARENT 0x0800
#endif

#define IsWinXP() ((GetVersion() & 0x80000000)==0 && (LOBYTE(LOWORD(GetVersion()))) > 5)

// Save user's view preference over calls.
static int saved_listview_style = LVS_REPORT;

// user-defined message
static UINT g_uFODRefreshMsgId = 0;

static LPOPENFILEDLGPRIVATE g_pFileOpenDlgPrivate;  // initialized by 'static' keyword
static FILEINFOS g_fileInfos;           // initialized by 'static' keyword

static HWND g_hwndFileOpenDlg = NULL;            // file open dialog hwnd

static HINSTANCE g_hInst;	// current instance
static int g_separator;		// Separator character in pathnames (/ or \, no VMS for now)

static OPENFILENAME* g_ofn;	// Saved ofn struct

static int SHORTCUT_CXICON = 0;
static int SHORTCUT_CYICON = 0;

static UINT g_uAddItemMsgId = 0;    // shortcut bar add item message id
static UINT g_uResetContentMsgId = 0; // shortcut bar reset content message id
static NUMBERFMT g_nf;

static void filedlg_initialize(OPENFILENAME *ofn);
static void filedlg_error(DWORD err);
static void filedlg_cleanup(OPENFILENAME *ofn);
static HRESULT NotifyChildDialog(UINT message);
static void DoFileTypeComboSelChange(HWND hwndFilter);
static void SyncViewsMenu(void);
static void filter_listview(HWND hDlg);
static void sort_listview(HWND hDlg);
static BOOL absolute_path_p(TCHAR *path);
static BOOL looks_like_directory_p(TCHAR *path);


static OFNCustomData_s   g_ofn_custom_data;
static OFNCustomData_s*  g_ofn_custom_data_ptr = &g_ofn_custom_data;

extern "C" void g2pvt_request_list_sys_drives();


// listview subclass implements
LRESULT CALLBACK ListViewProc(HWND hWnd, UINT Message, WPARAM wParam,
							  LPARAM lParam);
FARPROC lpfnOldLVWndProc;

extern "C" void g2pvt_trace(const char *fmt, ...);
extern "C" void g2pvt_printf(const char *fmt, ...);
#define PRINTF g2pvt_trace

/* Debugging */
#ifdef TESTMAIN
extern "C" char *notify_code(int code);
extern "C" const char *win32_msg_name(unsigned int code);
#endif



/*
 * Utilities
 */

/* Copy a "double-NUL" string into buf. */
static char *dn_strcpy(char *buf, const char *dn)
{
  char *p;
  const char *q;
  int n;

  for(p=buf, q=dn; *q; p+=n, q+=n) {
    strcpy(p, q);
    n = strlen(q) + 1;
  }
  *p++ = '\0';
  return buf;
}



/*
 * Entry points
 */

static Resizer *g_resizer;

BOOL GetServerFileName(OPENFILENAMEW *ofn)
{  
  filedlg_initialize(ofn);

  int rc = DialogBoxParam(g_hInst, (LPCTSTR)IDD_FILEDLG, ofn->hwndOwner,
			  GensymFileOpenDlgProc, (LPARAM)ofn);
  filedlg_cleanup(ofn);
  if(rc == -1)
    filedlg_error(GetLastError());

  return (rc == IDOK);
}

/*
 * Utilities
 */

static void filedlg_initialize(OPENFILENAME *ofn)
{
  static int done = 0;

  if(ofn->lpstrInitialDir == NULL)
    ofn->lpstrInitialDir = _T("/");	// FIXME: Want the server's root dir -- no way to know.

  /* The rest are once-only initializations */
  if(done) return;

  INITCOMMONCONTROLSEX icex;
  icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icex.dwICC  = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES;
  if(!InitCommonControlsEx(&icex))
    return;

  g_uFODRefreshMsgId = RegisterWindowMessage(FOD_REFRESH_MSG_STR);

  g_hInst = GetModuleHandle(NULL);
  RegisterShortcutBar(g_hInst);

  /* Get a NUMBERFMT for formatting integers. */
  TCHAR buf[5];
  static TCHAR szDecSep[5];
  static TCHAR szThousandsSep[5];

  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, &szDecSep[0], sizeof(szDecSep));
  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, &szThousandsSep[0], sizeof(szThousandsSep));

  g_nf.NumDigits = 0;		// Number of fractional digits
  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILZERO, &buf[0], sizeof(buf));
  g_nf.LeadingZero = _ttoi(buf);
  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SGROUPING, &buf[0], sizeof(buf));
  g_nf.Grouping = _ttoi(buf);
  g_nf.lpDecimalSep = szDecSep;
  g_nf.lpThousandSep = szThousandsSep;
  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_INEGNUMBER, &buf[0], sizeof(buf));
  g_nf.NegativeOrder = _ttoi(buf);

  done=1;
}

static void filedlg_error(DWORD code)
{
  TCHAR buf[256];
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, code, 0, buf, 255, NULL);
  fprintf(stderr, "File dialog error %u: %s\n", code, buf);
}

// FIXME: Broken if szPathDir doesn't have a trailing separator.
static int SplitDirectoryFromPath(LPTSTR szPathDir, LPTSTR szPath, LPTSTR szDirectory)
{
  TCHAR szBuf[_MAX_PATH];
  ZeroMemory((LPVOID)szBuf, _MAX_PATH);
  TCHAR szParentPath[_MAX_PATH];
  ZeroMemory((LPVOID)szParentPath, _MAX_PATH);
  ZeroMemory((LPVOID)szDirectory, _MAX_PATH);
  TCHAR *ptr;
  int chSep = g_separator;
  int nLen = 0;

  // make copy of szPathDir for us to work with
  lstrcpy(szBuf, szPathDir);

  // are we at the root directory?  If the first occurence of chSep is at the end of the string,
  // then it is the root directory
  nLen = _tcslen(szBuf);
  ptr = _tcschr(szBuf, chSep);

  if (ptr != NULL)
  {
    if ((int)(ptr - szBuf + 1) == nLen)
    {
      // this is the root
      _tcscpy(szPath, szBuf);
      szDirectory[0] = _T('\0');
      return 0;
    }
  }
  else
  {
    return -1;
  }

  nLen = _tcslen(szBuf) - 1;   // we want to point to the last '\' so we're not adding 1 to strlen
  szBuf[nLen] = _T('\0');

  for (int i = (nLen - 1); i > -1; i--)
  {
    if (szBuf[i] == chSep)
    {
      // copy off directory
      lstrcpy(szDirectory, (LPTSTR)&szBuf[i+1]);
      // end the string preserving the last '\'
      szBuf[i+1] = _T('\0');

      break;
    }
  }

  lstrcpy(szPath, szBuf);
  return 1;
}

static void GetCurrDir(LPTSTR pszCurrDir, int cchBuffer)
{
  HWND hwndLookIn = GetDlgItem(g_hwndFileOpenDlg, cmb2);
  int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);
  lstrcpy(pszCurrDir, (LPTSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, nCurSel, 0));
}

/* Called asynchronously when the file listing arrives from G2.
 * Hence, we protect ourselves against the dialog being already closed. */
static void PopulateListView(FileInfo *info, int count)
{
  // first, clean out the old
  CleanupFileInfos();		// TODO: keep around as dir cache

  // save items and count in global variables
  g_fileInfos._fileInfos = info;
  g_fileInfos._count = count;

  if(!IsWindow(g_hwndFileOpenDlg)) { // Roc, protect!
    CleanupFileInfos();
    return;
  }

  filter_listview(g_hwndFileOpenDlg);
  sort_listview(g_hwndFileOpenDlg);
  // set the focus rectangle to the first item in the list
  ListView_SetItemState(g_pFileOpenDlgPrivate->_hwndLV, 0, LVIS_FOCUSED, LVIS_FOCUSED);
  EnableWindow(g_hwndFileOpenDlg, TRUE);
}

/* Called asynchronously when the <...> arrives from G2.
 * Hence, we protect ourselves against the dialog being already closed. */
extern "C" void update_remote_sys_drives(LPCSTR strDrives)
{
}



static BOOL PushToDirectory(LPTSTR dir, LPTSTR fn)
{
  TCHAR szCurrDir[_MAX_PATH] = {0};
  GetCurrDir(szCurrDir, _MAX_PATH);
  PushBackStack(szCurrDir);
  EnableBackButton(TRUE);
  return RefreshFileList(dir,fn);
}

/* Called on Back, LookIn combo change, double-click on dir, and g_uFODRefreshMsgId */
static BOOL RefreshFileList(LPTSTR szPath, LPTSTR szDirectory)
{
  // clean out the file listview
  ResetFileList(g_pFileOpenDlgPrivate->_hwndLV);

  // Disable window and display message while waiting for listing.
  EnableWindow(g_hwndFileOpenDlg, FALSE);

  // concatenate the path plus directory name
  // assume szPath has trailing separator
  TCHAR szPathDir[_MAX_PATH];
  ZeroMemory((LPVOID)szPathDir, _MAX_PATH);
  lstrcpy(szPathDir, szPath);
  if(szDirectory)
    lstrcat(szPathDir, szDirectory);

  // We borrow the lpTemplateName slot for the directory lister function.
  (*((ListDirFunction)g_ofn->lpTemplateName)) (szPathDir, PopulateListView);

  // populate Lookin with new directory
  HWND hwndLookin = GetDlgItem(g_hwndFileOpenDlg, cmb2);
  PopulateLookInCombo(g_hwndFileOpenDlg, szPathDir);

  return TRUE;
}

static int GetFocusedLVItem(HWND hwndLV)
{
  int iFocused = -1;
  
  while ( (iFocused = ListView_GetNextItem(hwndLV, iFocused, LVNI_FOCUSED)) != -1);
  
  return iFocused;
}

/*
 * File types combo
 */

static int PopulateFileTypes(HWND hwndFileTypes, LPCTSTR pszFilter, 
                             TCHAR *filters[], int nmax)
{
  int n=0, k=1;
  TCHAR buf[100];

  SendMessage(hwndFileTypes, CB_RESETCONTENT, 0, 0);
  for(int p = 0; pszFilter[p]; p+=_tcslen(&pszFilter[p])+1, k++)
    if(k&1)
      SendMessage(hwndFileTypes, CB_ADDSTRING, 0, (LPARAM)&pszFilter[p]);
    else {						// Canonicalize filter string.
      wsprintf(buf,_T("%s"),&pszFilter[p]);		// TODO: We could "compile" the pattern here.
      if(n < nmax)
	    filters[n++] = _tcsdup(buf);
    }

  SendMessage(hwndFileTypes, CB_SETCURSEL, 0, 0);
  return n;
}

// Assuming true iff a Windows file system.
static BOOL case_independent_file_system_p()
{
  return g_separator == _T('\\');
}

static BOOL simple_wildcard_match_p(const TCHAR *string, TCHAR *pattern)
{
  const TCHAR *s = string;
  TCHAR *p = pattern;
  TCHAR *t;
  const TCHAR *q;
  const TCHAR WILD = _T('*');

  while(*p) {
    if(*p != WILD) {		// Pattern begins with literal
      t = _tcschr(p,WILD);
      if(t) *t = 0;		// Yuck
      if(_tcsncmp(s, p, _tcslen(p)) != 0)
	return FALSE;
      s += _tcslen(p);
      p += _tcslen(p);
      if(t) *t = _T('*');		// Yuck

    } else if(!(t=_tcschr(p+1,WILD))) { // Pattern is wildcard [literal]
      p++;
      return _tcslen(s)>=_tcslen(p) && _tcsncmp(s+_tcslen(s)-_tcslen(p), p, _tcslen(p)) == 0;

    } else {			// Pattern is wildcard [literal] wildcard ...
      p++;
      *t = 0;			// Yuck
      q = _tcsstr(s,p);		// Guess the first match here (no backtracking)
      if(q == NULL)
	return FALSE;
      s = q + _tcslen(p);
      p += _tcslen(p);
      *t = _T('*');			// Yuck
    }
  }
  return (*s == 0);
}

// Pattern is of the form, "*.txt;*.kb;". We try to support the same degree of
// wildcard matching that GetOpenFileName does.
static BOOL filter_match_p(FileInfo *fi, TCHAR *pattern)
{
  TCHAR filename[_MAX_PATH];

  if(fi->type == FILETYPE_FOLDER) // Folders always match
    return TRUE;

  if(!pattern)			  // No filter, always match.
    return TRUE;

  if(!_tcscmp(pattern, _T("*.*;")))	  // Universal filter, always match.
    return TRUE;

  _tcscpy(filename, fi->name);
  if(!_tcschr(filename,_T('.')))	  // Ensure dot for filetype is literally present.
    _tcscat(filename, _T("."));

  TCHAR *temp = _tcsdup(pattern);	  // OR over semicolon-delimited patterns
  TCHAR *p, *e;

  if(case_independent_file_system_p()) {
    _tcslwr(filename);
    _tcslwr(temp);
  }

  for(p=temp; *p; p+=_tcslen(p)+1) {
    e = _tcschr(p,_T(';'));
    if(e) *e = 0;
    if(simple_wildcard_match_p(filename, p)) {
      free(temp);
      return TRUE;
    }
  }
  free(temp);
  return FALSE;
}

/* Repopulates listview from cached fileinfo, with filtering. */
static void filter_listview(HWND hDlg)
{
  HWND hwndCombo = GetDlgItem(hDlg,cmb1);
  int nCurSel = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
  TCHAR *filter = nCurSel>=MAX_FILTERS ? _T("*.*;") : g_pFileOpenDlgPrivate->filters[nCurSel];
  FileInfo *fi;

  ResetFileList(g_pFileOpenDlgPrivate->_hwndLV);
  
  for (int i = 0; i < g_fileInfos._count; i++) {
    fi = &g_fileInfos._fileInfos[i];
    if(filter_match_p(fi,filter)) 
      AddItem(fi,i);
  }
}

static void CleanupFileInfos()
{
  if (g_fileInfos._fileInfos == NULL)
    return;

  for (int i = 0; i < g_fileInfos._count; i++)
    if (g_fileInfos._fileInfos[i].name != NULL)
      free((void*)g_fileInfos._fileInfos[i].name);

  g_fileInfos._fileInfos = NULL;
  g_fileInfos._count = 0;
}

// Add up/down bitmap to col, remove from all others.
static void listview_set_sorting_indicator(HWND hwndLV, int direction, int column)
{
  HWND header = ListView_GetHeader(hwndLV);
  HDITEM hi;

  // TODO: On WinXP, use HDF_SORTDOWN/HDF_SORTUP instead of images.

  for(int i=0; i<Header_GetItemCount(header); i++) {
    hi.mask = HDI_FORMAT | HDI_IMAGE;
    Header_GetItem(header, i, &hi);
    if(i==column && direction != 0) {
      hi.fmt |= HDF_BITMAP | HDF_BITMAP_ON_RIGHT | HDF_IMAGE;
      hi.iImage = (direction == +1) ? 0 : 1;
    } else {
      hi.fmt &= ~(HDF_BITMAP | HDF_BITMAP_ON_RIGHT | HDF_IMAGE);
      hi.iImage = 0;
    }
    Header_SetItem(header, i, &hi);
  }
}

static void sort_listview(HWND hDlg)
{
  HWND hwndLV = g_pFileOpenDlgPrivate->_hwndLV;
  listview_set_sorting_indicator(hwndLV, 
				 g_pFileOpenDlgPrivate->_sortDirection,
				 g_pFileOpenDlgPrivate->_sortColumn);

  ListView_SortItems(hwndLV, CompareProc, 0);
}

static void listview_toggle_sorting(HWND hDlg, int column)
{
  int direction = g_pFileOpenDlgPrivate->_sortDirection;
  direction = (direction == 0) ? 1 : -direction;

  g_pFileOpenDlgPrivate->_sortDirection = direction;
  g_pFileOpenDlgPrivate->_sortColumn = column;
  sort_listview(hDlg);
}

static INT_PTR CALLBACK GensymFileOpenDlgProc(HWND hDlg, UINT message,
										   WPARAM wParam, LPARAM lParam)
{
  int iSelected = 0;
  TCHAR szCurrDir[_MAX_PATH] = {0};
  TCHAR szSelectedFile[_MAX_PATH] = {0};
  LPNMLVKEYDOWN lpnkd;
  DWORD rc;

  if (message == g_uFODRefreshMsgId) {
    PushToDirectory((LPTSTR)lParam, (LPTSTR)wParam);
    return TRUE;    
  }

  if(g2pvt_resizer_dlgproc(g_resizer, &rc, hDlg, message, wParam, lParam))
    return rc;

  switch (message) {
   case WM_INITDIALOG:
     return (BOOL)HANDLE_WM_INITDIALOG(hDlg, wParam, lParam, GensymOpenFileDlg_OnInitDialog);

   case CDM_SETCONTROLTEXT:	// One of several special GetOpenFileName msgs
     {
       HWND control = GetDlgItem(hDlg,wParam);
       if(control) SetWindowText(control,(LPCTSTR)lParam);
     }

   case WM_NOTIFY:


#ifdef TESTMAIN
     {
       int ctrl = LOWORD(wParam);
       int code = ((LPNMHDR)lParam)->code;
       if(!(ctrl == lst1 && code == LVN_GETDISPINFO))
	 g2pvt_trace("WM_NOTIFY ctrl %d code %08X %4d %s\n",
		     ctrl, code, code, notify_code(code));
     }
#endif
     switch (LOWORD(wParam)) {
      case IDC_TOOLBAR:
	DoToolbarNotify(hDlg, message, wParam, lParam);
	break;

      case lst1:
	switch (((LPNMHDR) lParam)->code) {
	 case LVN_ITEMCHANGED:
	   { NMLISTVIEW *nmlv = (NMLISTVIEW*)lParam;
	     LPTSTR filename = GetSelectedFile(g_pFileOpenDlgPrivate->_hwndLV,
					       nmlv->iItem, szSelectedFile, _MAX_PATH);
	     if (filename)	// NULL if a folder
	       UpdateFileName(hDlg, filename);
	   }
	   break;

	 case NM_DBLCLK:
	   FileListView_DoubleClick(g_pFileOpenDlgPrivate->_hwndLV);
	   break;

	 case LVN_GETDISPINFO:
	   ListView_OnDispInfo((LPNMHDR)lParam, NULL);
	   break;

	 case LVN_COLUMNCLICK:
	   listview_toggle_sorting(g_pFileOpenDlgPrivate->_hwndLV,
				   ((LPNMLISTVIEW)lParam)->iSubItem);
	   break;

	 case NM_RETURN: // FIXME: Why don't we get this notification??  FIXED: Subclass the listview control
	   // to handle WM_GETDLGCODE and return DLGC_WANTALLKEYS when the ENTER key is pressed.  
	   // Note this applies to listview controls contained in dialog boxes only.
	   
	   // only do this if something is actually selected (as opposed to having focus w/o being selected)
	   iSelected = ListView_GetNextItem(g_pFileOpenDlgPrivate->_hwndLV, -1, LVNI_SELECTED);

	   if (iSelected > -1) {
	     // perform same action as double-clicking
	     FileListView_DoubleClick(g_pFileOpenDlgPrivate->_hwndLV);
	   }
	   break;

	 case LVN_KEYDOWN:
	   // backspace?
	   lpnkd = (LPNMLVKEYDOWN)lParam;
	   if (lpnkd->wVKey == VK_BACK) {
	     DoToolbarUpBtn(hDlg, message, wParam, lParam);
	   }
	   break;
	}
	break;
     }
     break;


   case WM_COMMAND:
     switch (LOWORD(wParam)) {
      case IDOK:
	// Get directory and filename.
	GetCurrDir(szCurrDir, _MAX_PATH);
	SendMessage(GetDlgItem(hDlg,edt1), WM_GETTEXT, _MAX_PATH, (LPARAM)szSelectedFile);

	// If the path is a directory, we want to switch to that directory
	// without exiting the dialog. Unfortunately, only G2 knows what is or
	// is not directory, so we approximate and assume a directory iff there
	// is a trailing separator in the pathname. -fmw, 4/6/05

	if(looks_like_directory_p(szSelectedFile)) {
	  if(absolute_path_p(szSelectedFile))
	    PushToDirectory(szSelectedFile, NULL);
	  else
	    PushToDirectory(szCurrDir, szSelectedFile);
	  SendMessage(GetDlgItem(hDlg,edt1), EM_SETSEL, 0, -1); // Matches Windows behavior.
	  break;		// Don't exit dialog!
	}
	else if (absolute_path_p(szSelectedFile)) { // did we enter absolute path?
	  _tcscpy(g_ofn->lpstrFile, szSelectedFile);
	}
	else {
	  // Copy to user's structure.
	  _tcscpy(g_ofn->lpstrFile, szCurrDir); // TODO: check g_ofn->nMaxFile.
	  _tcscat(g_ofn->lpstrFile, szSelectedFile);
	}

	// Append default extension, if needed.
	if(g_ofn->lpstrDefExt != NULL && _tcschr(szSelectedFile,_T('.')) == NULL) {
	  _tcscat(g_ofn->lpstrFile, _T("."));
	  _tcscat(g_ofn->lpstrFile, g_ofn->lpstrDefExt);
	}
	saved_listview_style = GetViewStyle();
	NotifyChildDialog(CDN_FILEOK);          // Only notification twpro.c actually uses
	EndDialog(hDlg,IDOK);
	return TRUE;

      case IDCANCEL:
	saved_listview_style = GetViewStyle();
	EndDialog(hDlg,IDCANCEL);
	return TRUE;

      case cmb1:
	switch (HIWORD(wParam)) {
	 case CBN_SELCHANGE:
	   filter_listview(g_hwndFileOpenDlg);
	   sort_listview(g_hwndFileOpenDlg);
	   // set the focus rectangle to the first item in the list
	   ListView_SetItemState(g_pFileOpenDlgPrivate->_hwndLV, 0, LVIS_FOCUSED, LVIS_FOCUSED);
	   break;
	}
	break;

      case cmb2:
	switch (HIWORD(wParam)) {
	 case CBN_SELCHANGE:
	   DoLookinComboSelChange(GetDlgItem(hDlg,cmb2));
	   break;
	}
	break;

      case IDM_VIEW_LARGEICONS:
	SetView(LVS_ICON);
	break;
      case IDM_VIEW_SMALLICONS:
	SetView(LVS_SMALLICON);
	break;
      case IDM_VIEW_LIST:
	SetView(LVS_LIST);
	break;
      case IDM_VIEW_DETAILS:
	SetView(LVS_REPORT);
	break;
      case IDS_VIEW:
	SetView(NextViewStyle());
	break;
      case IDS_BACK:
	return DoToolbarBackBtn(hDlg, message, wParam, lParam);
      case IDS_UP:
	DoToolbarUpBtn(hDlg, message, wParam, lParam);
	break;
     }
     break;
  }
  return FALSE;
}



static HMENU CreateViewsMenu()
{
  HMENU hmenu = CreatePopupMenu();
  AppendMenu(hmenu, MF_STRING, IDM_VIEW_LARGEICONS, _T("Large Icons"));
  AppendMenu(hmenu, MF_STRING, IDM_VIEW_SMALLICONS, _T("Small Icons"));
  AppendMenu(hmenu, MF_STRING, IDM_VIEW_LIST,       _T("List"));
  AppendMenu(hmenu, MF_STRING, IDM_VIEW_DETAILS,    _T("Details"));
  return hmenu;
}

static void filedlg_cleanup(OPENFILENAME *ofn)
{
  int i=0;

  if(g_pFileOpenDlgPrivate == NULL) // If we failed to even create the dialog.
    return;

  if (g_pFileOpenDlgPrivate->_hViewsMenu != NULL) {
    DestroyMenu(g_pFileOpenDlgPrivate->_hViewsMenu);
    g_pFileOpenDlgPrivate->_hViewsMenu = NULL;
  }

  // file types
  for(i=0; i<g_pFileOpenDlgPrivate->nfilters; i++)
    free(g_pFileOpenDlgPrivate->filters[i]);

  // back STACK global
  for (i = 0; i < g_pFileOpenDlgPrivate->_pbackStack->top; i++) {
    delete [] g_pFileOpenDlgPrivate->_pbackStack->pszFolders[i];
    g_pFileOpenDlgPrivate->_pbackStack->pszFolders[i] = NULL;
  }

  if (g_pFileOpenDlgPrivate->_pbackStack != NULL)
    delete g_pFileOpenDlgPrivate->_pbackStack;

  CleanupFileInfos();

  // our private structure
  if (g_pFileOpenDlgPrivate != NULL) {
    delete g_pFileOpenDlgPrivate;
    g_pFileOpenDlgPrivate = NULL;
  }

  if(g_resizer)
    g2pvt_resizer_free(g_resizer);
  g_resizer = NULL;

  g_hwndFileOpenDlg = NULL;
  g_ofn = NULL;
}

// Our wrapper dialog proc for the user-specified child dialog, if any.
static INT_PTR CALLBACK ChildDialogProc(HWND hDlg, UINT message, WPARAM wParam,
										LPARAM lParam)
{
  if(message == WM_INITDIALOG)
    lParam = (LPARAM)g_ofn;
  return CallWindowProc((WNDPROC)g_ofn->lpfnHook, hDlg, message, wParam, lParam);
}

// Send a notification message to our child dialog, if any.
static HRESULT NotifyChildDialog(UINT message)
{
  HWND child = g_pFileOpenDlgPrivate->_hwndChild;
  if(!child) return 0;

  OFNOTIFY ofn;
  ofn.hdr.hwndFrom = GetParent(child);
  ofn.hdr.idFrom = 0;
  ofn.hdr.code = message;
  ofn.lpOFN = g_ofn;
  ofn.pszFile = NULL;
  return SendMessage(child, WM_NOTIFY, (WPARAM)0, (LPARAM)&ofn);
}

static int ParseShortcuts(LPTSTR pbShortcuts, TCHAR *pszShortcuts[])
{
  int n=0;
  for(LPTSTR p = pbShortcuts; p && *p; p+=_tcslen(p)+1)
    pszShortcuts[n++] = _tcsdup(p);
  return n;
}

INT_PTR CALLBACK DummyDlgProc(
    HWND hwndDlg,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
	return 0;
}



static BOOL GensymOpenFileDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
  OPENFILENAME *ofn = (OPENFILENAME *)lParam;
  HWND child = NULL;
  static int once = 1;

  g_separator = (ofn->lpstrInitialDir[0] == _T('/')) ? _T('/') : _T('\\');   // Unix-Windows test
  g_hwndFileOpenDlg = hwnd;
  g_resizer = g2pvt_resizer_create(hwnd,20);
  g_ofn = ofn;


  OFNCustomData_s* ofn_custdata_src_ptr = (OFNCustomData_s*)ofn->lCustData;
  strlist_copy(g_ofn_custom_data_ptr->shortcuts, ofn_custdata_src_ptr->shortcuts);
  //strlist_copy(g_ofn_custom_data_ptr->shortcut_names, ofn_custdata_src_ptr->shortcut_names);
  strlist_copy(g_ofn_custom_data_ptr->drives, ofn_custdata_src_ptr->drives);

  // allocate our private structure
  g_pFileOpenDlgPrivate = new OPENFILEDLGPRIVATE;
  ZeroMemory(g_pFileOpenDlgPrivate, sizeof(OPENFILEDLGPRIVATE));

  g_pFileOpenDlgPrivate->_sortColumn = 0; // Default is ascending by name
  g_pFileOpenDlgPrivate->_sortDirection = 1;

  /////////////////////////////////////////////////////////////////////
  // are we save or open file dialog
  /////////////////////////////////////////////////////////////////////
  if((ofn->Flags & (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST)) == 0) {
    // TODO: translations
    SetDlgItemText(hwnd, IDOK, _T("&Save"));
    SetDlgItemText(hwnd, stc4, _T("Save &in:"));
    SetDlgItemText(hwnd, stc2, _T("Save as type:"));
  }

  // TODO Unicode
  SetWindowText(hwnd,ofn->lpstrTitle);

  // set initial focus to the File Name edit control
  SetFocus(GetDlgItem(hwnd, edt1));

  /////////////////////////////////////////////////////////////////////
  // toolbar
  /////////////////////////////////////////////////////////////////////
  g_pFileOpenDlgPrivate->_hwndToolbar = CreateToolbar(hwnd, 300, 18);

  // initialize the back button stack
  InitializeBackStack();

  // create the views toolbar button dropdown menu
  g_pFileOpenDlgPrivate->_hViewsMenu = CreateViewsMenu();
  
  /////////////////////////////////////////////////////////////////////
  // Filename edit/combo box
  /////////////////////////////////////////////////////////////////////
  if (ofn->lpstrFile != NULL)
    UpdateFileName(hwnd, ofn->lpstrFile);

  /////////////////////////////////////////////////////////////////////
  // Filetypes (filter) combo box
  /////////////////////////////////////////////////////////////////////
  g_pFileOpenDlgPrivate->nfilters =
    PopulateFileTypes(GetDlgItem(hwnd,cmb1),
		      ofn->lpstrFilter,
		      &g_pFileOpenDlgPrivate->filters[0], MAX_FILTERS);

  /////////////////////////////////////////////////////////////////////
  // listview
  /////////////////////////////////////////////////////////////////////
  // set the list view global hwnd
  HWND hwndLV = GetDlgItem(hwnd, lst1);
  g_pFileOpenDlgPrivate->_hwndLV = hwndLV;

  // subclass list view to properly handle ENTER key
  lpfnOldLVWndProc = (FARPROC)SetWindowLongPtr(hwndLV, GWLP_WNDPROC,
	  (DWORD)ListViewProc);

  // set file list view image list
  SetListViewImageList(hwndLV, g_pFileOpenDlgPrivate->_hImageListSmall, 
		       g_pFileOpenDlgPrivate->_hImageListLarge);

  // Set the header image list (for sorting indicators)
  HIMAGELIST himl = ImageList_LoadImage(g_hInst, _T("UPDOWN"), 16, 0, CLR_DEFAULT, 
					IMAGE_BITMAP, LR_LOADMAP3DCOLORS);
  Header_SetImageList(ListView_GetHeader(hwndLV), himl);

  // add listview columns
  AddColumns(hwndLV);

  // Request initial file listing
  TCHAR tempInitialDir[200];
  _tcsncpy(tempInitialDir, ofn->lpstrInitialDir, min(199, _tcslen(ofn->lpstrInitialDir)));
  tempInitialDir[min(199, wcslen(ofn->lpstrInitialDir))] = _T('\0');
  RefreshFileList(tempInitialDir, NULL);

  // Get small folder icon for LookIn combo
  HWND hwndLookIn = GetDlgItem(hwnd,cmb2);
  SendMessage(hwndLookIn, CBEM_SETIMAGELIST, 0, (LPARAM)CreateFolderImageList());

  PopulateLookInCombo(hwnd, tempInitialDir);
  SetView(saved_listview_style); // Saved user preference
  SyncViewsMenu();

  ////////////////////////////////////////////////////////////////////////////////
  //  Create the ShortcutBar, placing it even with the top of the file listview
  ////////////////////////////////////////////////////////////////////////////////

  // 1. get the position and bounding rectangle of the file listview
  RECT rc;
  HWND hwndFileList = GetDlgItem(hwnd,lst1);
  GetWindowRect(hwndFileList, &rc);
  // convert to dialog's coordinates
  ScreenToClient(hwnd, LPPOINT(&rc.left));
  ScreenToClient(hwnd, LPPOINT(&rc.right));

  // 2. calculate the width and height of the ShortcutBar
  RECT dlgRect;
  // get the client rectangle of the dialog
  GetClientRect(hwnd, &dlgRect);
  int width = 87;		// hard-coded width for now
  // height is from the top of the file listview to the bottom of the dialog
  int height = dlgRect.bottom - rc.top; 

  // 3. create ShortcutBar and position even with the top of file listview
  g_pFileOpenDlgPrivate->_hwndShortcutBar = 
    CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE, 
		   SHORTCUTBARCLASS, 
		   _T("ShortcutBar"), 
		   WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		   dlgRect.left + 5, 
		   rc.top,  
		   width, 
		   height - 2, 
		   hwnd, 
		   (HMENU)IDC_PLACESBAR,
		   NULL, 
		   NULL);


	// L10n
	const size_t str_sz = 256;
	TCHAR str[str_sz];
	const size_t NamesIds_sz = 5;
	int NamesIds[NamesIds_sz] = { 12691, 4162, 9227, 9216, 9217 }; 

	HMODULE hModule = ::GetModuleHandle(_T("shell32.dll"));
	if ( hModule ) {
		TCHAR* str_ptr = g_ofn_custom_data_ptr->shortcut_names;
		for ( int ind = 0; ind < NamesIds_sz; ++ind )
			if ( LoadString( hModule, NamesIds[ind], str, str_sz) > 0 ) {
				  _tcscpy(str_ptr, str);
				  str_ptr += _tcslen(str)+1;
			}
		*str_ptr++ = '\0';
	}

  
  // get our items we saved earlier
  TCHAR szPath[_MAX_PATH] = {0};
  TCHAR szDir[_MAX_PATH] = {0};
  int nRet = 0;

  SHORTCUTBARITEMSTRUCT sbis;
  ZeroMemory((LPVOID)&sbis, sizeof(SHORTCUTBARITEMSTRUCT));
  sbis.cbSize = sizeof(SHORTCUTBARITEMSTRUCT);
  sbis.iBitmap = 0;

  TCHAR *pszShortcuts[MAX_ITEMS];
  int nShortcuts = ParseShortcuts(g_ofn_custom_data_ptr->shortcuts, pszShortcuts);
  
  TCHAR* names = g_ofn_custom_data_ptr->shortcut_names;
  for (int i = 0; i < nShortcuts; i++)
    if ((nRet = SplitDirectoryFromPath(pszShortcuts[i], szPath, szDir)) > -1)
    {
      _tcscpy(sbis.szPath, szPath);
      _tcscpy(sbis.szDir,  szDir);
	  _tcscpy(sbis.szName, names);
	  names += _tcslen(names)+1;
	  SendMessage(g_pFileOpenDlgPrivate->_hwndShortcutBar, g_uAddItemMsgId, 0, (LPARAM)&sbis);
    }

  // Create user-specified subdialog, if any.
  // TODO: Other cases to handle, but not used by G2.

  if(ofn->Flags & OFN_ENABLETEMPLATEHANDLE) {
    child = CreateDialogIndirectParam(g_hInst, (DLGTEMPLATE*)ofn->hInstance,
					   hwnd, ChildDialogProc, (LPARAM)0);
    if(child) {
      ShowWindow(child,SW_SHOW);
      g_pFileOpenDlgPrivate->_hwndChild = child;

      // Child goes below main dialog, left-justified, per Windows.
      // Make it as wide as our dialog, except leaving space for the
      // sizing grip.
      RECT r,c,s;
      GetWindowRect(hwnd,&r);
      GetWindowRect(child,&c);
      GetSizeGripRect(hwnd,&s);

      // Grow our height to fit child.
      SetWindowPos(hwnd, NULL, 0,0, RectWidth(r), RectHeight(r) + RectHeight(c),
		   SWP_NOMOVE | SWP_NOZORDER);

      // Position child below us, and fit width.
      int x = 5;
      int y = rc.top + height;
      GetClientRect(hwnd,&r);
      SetWindowPos(child,NULL,x,y, RectWidth(r)-x-RectWidth(s), RectHeight(c), SWP_NOZORDER);

      SetWindowLong(child, GWL_ID, IDC_SUBDIALOG);
      NotifyChildDialog(CDN_INITDONE); // Note: Windows sends some additional notifications.
    }
  }

  // Define the resize behavior. Ideally, this would be part of the dlg resource.
  g2pvt_resizer_add(g_resizer, stc4,          ANCHOR_LEFT|ANCHOR_TOP);
  g2pvt_resizer_add(g_resizer, cmb2,          ANCHOR_LEFT|ANCHOR_TOP|ANCHOR_RIGHT);
  g2pvt_resizer_add(g_resizer, IDC_TOOLBAR,   ANCHOR_RIGHT|ANCHOR_TOP);
  g2pvt_resizer_add(g_resizer, IDC_PLACESBAR, ANCHOR_LEFT|ANCHOR_TOP|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, lst1,          ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_TOP|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, stc3,          ANCHOR_LEFT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, edt1,          ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, stc2,          ANCHOR_LEFT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, cmb1,          ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, IDOK,          ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(g_resizer, IDCANCEL,      ANCHOR_RIGHT|ANCHOR_BOTTOM);
  if(child)
    g2pvt_resizer_add(g_resizer, IDC_SUBDIALOG, ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_lock(g_resizer);

  // maintain full selection of contents
  SendMessage(GetDlgItem(hwnd, edt1), EM_SETSEL, 0, -1);

  return TRUE;
}

static void SetListViewImageList(HWND hwndLV, HIMAGELIST &hilSmall, HIMAGELIST &hilLarge)
{
  // Retrieve the system image list
  GetSystemImageLists(hilSmall, hilLarge);

  if (hilSmall)
    ListView_SetImageList(hwndLV, hilSmall, LVSIL_SMALL);

  if (hilLarge)
    ListView_SetImageList(hwndLV, hilLarge, LVSIL_NORMAL);
}

static void GetSystemImageLists(HIMAGELIST &hilSmall, HIMAGELIST &hilLarge)
{
  SHFILEINFO sfi;
  memset(&sfi, 0, sizeof(sfi));

  TCHAR lpBuf[MAX_PATH];
  GetWindowsDirectory(lpBuf, MAX_PATH);

  hilSmall = reinterpret_cast<HIMAGELIST> (
    SHGetFileInfo (
      lpBuf, 
      0, 
      &sfi, 
      sizeof(sfi), 
      SHGFI_SYSICONINDEX | SHGFI_SMALLICON)
  );

  hilLarge = reinterpret_cast<HIMAGELIST> (
    SHGetFileInfo (
    lpBuf,
    0,
    &sfi,
    sizeof(sfi),
    SHGFI_SYSICONINDEX | SHGFI_ICON)
  );
}

static void AddColumns(HWND hwnd)
{
  // name
  LV_COLUMN lvCol = {0};
  lvCol.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_FMT|LVCF_SUBITEM;
  lvCol.fmt = LVCFMT_LEFT | LVCFMT_COL_HAS_IMAGES;
  lvCol.pszText = _T("Name");
  lvCol.cx = 150;
  lvCol.iSubItem = 0;
  ListView_InsertColumn(hwnd, 0, &lvCol);

  // type
  lvCol.pszText = _T("Type");	// TODO: Translations
  lvCol.fmt = LVCFMT_LEFT;
  lvCol.cx = 100;
  lvCol.iSubItem = 1;
  ListView_InsertColumn(hwnd, 1, &lvCol);

  // size
  lvCol.pszText = _T("Size");
  lvCol.fmt = LVCFMT_RIGHT;
  lvCol.cx = 75;
  lvCol.iSubItem = 2;
  ListView_InsertColumn(hwnd, 2, &lvCol);

  // date
  lvCol.pszText = _T("Modified");
  lvCol.fmt = LVCFMT_LEFT;
  lvCol.cx = 110;
  lvCol.iSubItem = 3;
  ListView_InsertColumn(hwnd, 3, &lvCol);

  SendMessage(hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
	      LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);
}

// TODO: Combo + history
static void UpdateFileName(HWND hdlg, LPTSTR pszFileName)
{
  SetDlgItemText(hdlg,edt1,pszFileName);
}

static void GetSmallFolderIcons(HICON *closed, HICON *open)
{
  SHFILEINFO sfi;
  memset(&sfi, 0, sizeof(sfi));
  DWORD flags = SHGFI_SMALLICON | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES;

  SHGetFileInfo (_T("dummy"), FILE_ATTRIBUTE_DIRECTORY, &sfi, sizeof(sfi), flags);
  *closed = sfi.hIcon;

  SHGetFileInfo (_T("dummy"), FILE_ATTRIBUTE_DIRECTORY, &sfi, sizeof(sfi), flags | SHGFI_OPENICON);
  *open = sfi.hIcon;
}

// Return a new imagelist containing two images: the small closed and open
// folder icons, in that order.
HIMAGELIST CreateFolderImageList()
{
  HIMAGELIST himl;
  HICON hClosedIcon, hOpenIcon;
  int cx_icon = ::GetSystemMetrics(SM_CXSMICON);
  int cy_icon = ::GetSystemMetrics(SM_CXSMICON);

  himl = ImageList_Create(cx_icon, cy_icon, ILC_COLOR24|ILC_MASK, 2, 1);

  GetSmallFolderIcons(&hClosedIcon, &hOpenIcon);
  ImageList_AddIcon(himl, hClosedIcon);
  ImageList_AddIcon(himl, hOpenIcon);
  DestroyIcon(hClosedIcon);
  DestroyIcon(hOpenIcon);
  return himl;
}

static int GetViewStyle(void)
{
  return GetWindowLong(g_pFileOpenDlgPrivate->_hwndLV, GWL_STYLE) & LVS_TYPEMASK;
}

static void SyncViewsMenu(void)
{
  int check = IDM_VIEW_DETAILS;
  switch(GetViewStyle()) {
    case LVS_ICON: check = IDM_VIEW_LARGEICONS; break;
    case LVS_SMALLICON: check = IDM_VIEW_SMALLICONS; break;
    case LVS_LIST: check = IDM_VIEW_LIST; break;
    case LVS_REPORT: check = IDM_VIEW_DETAILS; break;
  }
  CheckMenuRadioItem(g_pFileOpenDlgPrivate->_hViewsMenu,
		     IDM_VIEW_LARGEICONS, IDM_VIEW_DETAILS, check, MF_BYCOMMAND);
}

static void SetView(DWORD dwViewStyle)
{
  DWORD style = GetWindowLong(g_pFileOpenDlgPrivate->_hwndLV, GWL_STYLE);
  SetWindowLong(g_pFileOpenDlgPrivate->_hwndLV, GWL_STYLE, (style &~LVS_TYPEMASK) | dwViewStyle);
  SyncViewsMenu();
}

static int NextViewStyle()
{
  switch(GetViewStyle()) {
    case LVS_ICON: return LVS_SMALLICON;
    case LVS_SMALLICON: return LVS_LIST;
    case LVS_LIST: return LVS_REPORT;
    case LVS_REPORT: return LVS_ICON;
    default: return LVS_REPORT;
  }
}

///////////////////////////////////////////////////////////////
// Populates the Look in: combobox.
//
// Input:
//    HWND hdlg - handle to the dialog window
//    LPCSTR pszPathDir - this is the full path string
//      e.g. 'My Documents\My Projects\'
///////////////////////////////////////////////////////////////
static BOOL PopulateLookInCombo(HWND hdlg, LPTSTR pszPathDir)
{
  int nSel = -1;      // used for combobox selection index
  TCHAR *token = NULL;
  TCHAR seps[] = {g_separator,0};
  LONG lResult = 0;
  BOOL hack = FALSE;
  TCHAR pszParentPath[_MAX_PATH];  
  TCHAR pszPathDirCopy[_MAX_PATH];

  ZeroMemory((LPVOID)pszParentPath, _MAX_PATH);
  ZeroMemory((LPVOID)pszPathDirCopy, _MAX_PATH);

  COMBOBOXEXITEM cbei;
  ZeroMemory((LPVOID)&cbei, sizeof(cbei));
  int iCnt = 0;

  // the text, indent, image, and lparam fields are valid
  cbei.mask = CBEIF_TEXT | CBEIF_INDENT | CBEIF_IMAGE | CBEIF_LPARAM | CBEIF_SELECTEDIMAGE;
  // always add to the end
  cbei.iItem = -1;
  cbei.iImage = 0;		// Closed folder icon for all but the leaf
  cbei.iSelectedImage = 0;

  // copy off pszPathDir for us to mangle with strtok
  if(pszPathDir[0] == g_separator) {
    // Horrible hack for root: since strtok skips initial separators, prepend
    // some text, which we turn back into seps in the combo text. This will do
    // until we rewrite this mess.
    _tcscat(pszPathDirCopy, _T("X"));
    hack = TRUE;
  }
  _tcscat(pszPathDirCopy, pszPathDir);

  // get the handle to the Look in: combobox
  HWND hwndLookIn = GetDlgItem(hdlg,cmb2);

  // clear
  ResetLookinCombobox(hwndLookIn);

  // parse to acquire each containing folder name to display in the combobox
  token = _tcstok(pszPathDirCopy, seps);
  if(hack)
    token = seps;
  else
    _tcscpy(pszParentPath, token);
  _tcscat(pszParentPath, seps);
  
  // Another hack to append the \ to drive name at root, on Windows.
  if(g_separator == _T('\\') && _tcslen(token) == 2 && isalpha(token[0]) && token[1] == _T(':'))
    token = pszParentPath;

  while (token != NULL) {
    // add string.
    cbei.pszText = token;

    // set item data to our accumulated path
    TCHAR *szBuf = new TCHAR[_tcslen(pszParentPath) + 1];
    _tcscpy(szBuf, pszParentPath);
    cbei.lParam = (LPARAM)szBuf;
    cbei.iIndent = iCnt;

    if (SendMessage(hwndLookIn, CBEM_INSERTITEM, 0, (LPARAM)&cbei) == -1)
      return FALSE;

    nSel++;
    iCnt++;

    token = _tcstok(NULL, seps);
    if (token != NULL) {
      _tcscat(pszParentPath, token); // append to accumulated path
      _tcscat(pszParentPath, seps);
    }
  }



  // Add drives
  TCHAR *pszText = new TCHAR[_MAX_PATH];
  ZeroMemory((LPVOID)&cbei, sizeof(cbei));
  cbei.mask       = CBEIF_TEXT;
  cbei.iItem      = 0;
  cbei.cchTextMax = _MAX_PATH;
  cbei.pszText    = pszText;
  SendMessage(hwndLookIn, CBEM_GETITEM, 0, (LPARAM)&cbei);

  size_t text_len = _tcslen(cbei.pszText);
  _tcsncpy(pszText, cbei.pszText, text_len);

  ZeroMemory((LPVOID)&cbei, sizeof(cbei));
  // the text, indent, image, and lparam fields are valid
  cbei.mask = CBEIF_TEXT | CBEIF_INDENT | CBEIF_IMAGE | CBEIF_LPARAM | CBEIF_SELECTEDIMAGE;
  cbei.iImage = 0;		// Closed folder icon for all but the leaf
  cbei.iSelectedImage = 0;

  TCHAR *pszDrive = (TCHAR*)g_ofn_custom_data_ptr->drives;
  TCHAR* tok = _tcstok(pszDrive, _T("\0"));
  int ind = 0;
  while (tok != NULL) {
    size_t tok_len = _tcslen(tok)+1;

    if ( tok[0] != pszText[0] ) {
      // add drive
	  TCHAR *szBuf = new TCHAR[tok_len+1];
	  _tcsncpy(szBuf, tok, tok_len);
	  
	  if ( tok[0] < pszText[0] ) {
        cbei.iItem = ind++;
		++nSel;
	  }
	  else
		cbei.iItem = -1;
	  cbei.pszText = tok;
	  cbei.lParam  = (LPARAM)szBuf;
	  cbei.iIndent = 0;
	  
	  SendMessage(hwndLookIn, CBEM_INSERTITEM, 0, (LPARAM)&cbei);
	}

	pszDrive += tok_len;
	tok = _tcstok(pszDrive, _T("\0"));
  }




  // Use an open folder icon for selected item.
  cbei.mask = CBEIF_IMAGE | CBEIF_SELECTEDIMAGE;
  cbei.iItem = nSel;
  cbei.iImage = 1;		// Open folder icon
  cbei.iSelectedImage = 1;
  SendMessage(hwndLookIn, CBEM_SETITEM, 0, (LPARAM)&cbei);

  // default selection
  SendMessage(hwndLookIn, CB_SETCURSEL, nSel, 0);

  // save current selection itemdata to global; used for BACK functionality
  lstrcpy(g_pFileOpenDlgPrivate->_szCurrLookinData,
	  (LPTSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, (WPARAM) nSel, 0));

  EnableUpButton(iCnt >= 2);
  UpdateWindow(hwndLookIn);

  return TRUE;
}

static void ResetLookinCombobox(HWND hwndLookIn)
{
  int count = SendMessage(hwndLookIn, CB_GETCOUNT, 0, 0);

  for (int i = 0; i < count; i++)
    {
      char *pszBuf = (LPSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, i, 0);
      delete [] pszBuf;
      pszBuf = NULL;
    }

  SendMessage(hwndLookIn, CB_RESETCONTENT, 0, 0);
}

static void DoLookinComboSelChange(HWND hwndLookIn)
{
  TCHAR szPathDir[_MAX_PATH];
  ZeroMemory((LPVOID)szPathDir, _MAX_PATH);
  TCHAR szPath[_MAX_PATH];
  ZeroMemory((LPVOID)szPath, _MAX_PATH);
  TCHAR szDir[_MAX_PATH];
  ZeroMemory((LPVOID)szDir, _MAX_PATH);
  int nLen = 0;

  // get the index of the current selection
  int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);

  // get the associated itemdata
  lstrcpy(szPathDir, (LPTSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, nCurSel, 0));

  if (SplitDirectoryFromPath(szPathDir, szPath, szDir) < 0)
    return;

  if (_tcslen(g_pFileOpenDlgPrivate->_szCurrLookinData) > 0)
    {
      // push previous selection onto BACK stack
      PushBackStack(g_pFileOpenDlgPrivate->_szCurrLookinData);
      // update current selection global
      lstrcpy(g_pFileOpenDlgPrivate->_szCurrLookinData, szPathDir);
    }

  RefreshFileList(szPath, szDir);
}



//////////////////////////////////////////////////////////////////////////////////
// File Listview
//////////////////////////////////////////////////////////////////////////////////

static LPTSTR GetSelectedFile(HWND hwndLV, int i, TCHAR *buf, int buflen)
{
  FileInfo* pFileInfo = NULL;

  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.mask = LVIF_TEXT | LVIF_PARAM;
  lvi.iItem = i;
  lvi.iSubItem = 0;
  lvi.pszText = buf;
  lvi.cchTextMax = buflen;

  ListView_GetItem(hwndLV, &lvi);

  // is the item actually selected?
  int state = ListView_GetItemState(hwndLV, i, LVIS_SELECTED);

  if (state == LVIS_SELECTED) {

    pFileInfo = (FileInfo*)lvi.lParam;

    if (pFileInfo->type == FILETYPE_FOLDER)
      return NULL;    // it's a folder, so return NULL
    else
      return lvi.pszText;
  }
  else {
    return NULL;
  }
}

static int GetIconIndex (LPTSTR strFPath, int nType)
{
  static int _nDirIconIdx = -1;
  SHFILEINFO sfi;
  memset(&sfi, 0, sizeof(sfi));

  if (nType == 1) // it's a directory
  {
    if (_nDirIconIdx == -1)
    {
      SHGetFileInfo (
        strFPath, 
        FILE_ATTRIBUTE_DIRECTORY, 
        &sfi, 
        sizeof(sfi), 
        SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES
      );
      // Cache the index for the directory icon
      _nDirIconIdx = sfi.iIcon;
    }

    return _nDirIconIdx;
  }
  else
  {
    SHGetFileInfo (
      strFPath, 
      FILE_ATTRIBUTE_NORMAL, 
      &sfi, 
      sizeof(sfi), 
      SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES
    );

    return sfi.iIcon;
  }

  return -1;
}

static void SetImageList(HWND hdlg, HWND hwndLV, HIMAGELIST hImageList)
{ 
  ListView_SetImageList(hwndLV, hImageList, LVSIL_SMALL);
}

static TCHAR* GetTypeName(TCHAR *buf, FileInfo *fi)
{
  if(fi->type == FILETYPE_FOLDER)
    return lstrcpy(buf, _T("File Folder"));

  SHFILEINFO sfi;
  memset(&sfi, 0, sizeof(sfi));

  SHGetFileInfo(fi->name, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES);

  if(sfi.szTypeName[0] == _T('\0'))
    return lstrcpy(buf, _T("File"));

  return lstrcpy(buf, sfi.szTypeName);
}

static void ResetFileList(HWND hwndLV)
{
  ListView_DeleteAllItems(hwndLV);
}

static void FileListView_DoubleClick(HWND hwndLV)
{
  BOOL bRet = FALSE;
  HWND hwndLookIn;
  TCHAR szParentPath[_MAX_PATH];
  ZeroMemory((LPVOID)szParentPath, _MAX_PATH);
  TCHAR szDirectory[_MAX_PATH];
  ZeroMemory((LPVOID)szDirectory, _MAX_PATH);

  TCHAR szCurrDir[_MAX_PATH];
  ZeroMemory((LPVOID)szCurrDir, _MAX_PATH);

  int iSelected = SendMessage(hwndLV, LVM_GETNEXTITEM, (WPARAM)-1, LVNI_SELECTED);

  LVITEM lvi;
  memset(&lvi, 0, sizeof(lvi));

  lvi.mask = LVIF_TEXT | LVIF_PARAM;
  lvi.iSubItem = 0;
  lvi.pszText = szDirectory;
  lvi.cchTextMax = 256;
  lvi.iItem = iSelected;

  if(! ListView_GetItem(hwndLV, &lvi))
    return;

  FileInfo* pFileInfo = (FileInfo*)lvi.lParam;

  if (pFileInfo->type == FILETYPE_FOLDER)
  {
    // we double-clicked on a folder, get new file list

    // get the parent path
    hwndLookIn = GetDlgItem(g_hwndFileOpenDlg,cmb2);

    // get the index of the current selection
    int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);

    // get the associated itemdata
    lstrcpy(szParentPath, (LPTSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, nCurSel, 0));

    bRet = PushToDirectory(szParentPath, szDirectory);
  }
  else
  {
    // copy text to the file name combo and send IDOK msg
    UpdateFileName(g_hwndFileOpenDlg, pFileInfo->name);
    SendMessage(g_hwndFileOpenDlg, WM_COMMAND, (WPARAM)IDOK, 0L);
  }
}

static BOOL AddItem(FileInfo* pFileInfo, int nPos)
{
  int nNumItems = g_fileInfos._count;
  int nInsertPos = (nPos >= 0 && nPos <= nNumItems)?nPos : nNumItems;

  LV_ITEM item;
  item.lParam = (LPARAM) pFileInfo;
  item.pszText = LPSTR_TEXTCALLBACK;
  item.mask = LVIF_TEXT | LVIF_PARAM;
  item.iItem = nInsertPos;
  item.iSubItem = 0;

  if (ListView_InsertItem(g_pFileOpenDlgPrivate->_hwndLV, &item) < 0)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

/* From MSDN */
static void UnixTimeToFileTime(time_t t, LPFILETIME pft)
{
  LONGLONG lt;
  lt = Int32x32To64(t,10000000) + 116444736000000000;
  pft->dwLowDateTime = (DWORD)(lt & 0xFFFFFFFF);
  pft->dwHighDateTime = (DWORD)(lt >> 32);
} 

static LPTSTR time_to_string(time_t t)
{
  TCHAR szDate[15] = {0};
  TCHAR szTime[15] = {0};
  FILETIME ft;
  SYSTEMTIME sm, st;
  static TCHAR szDateTime[30] = {0};

  UnixTimeToFileTime(t,&ft);
  FileTimeToSystemTime(&ft, &sm);
  SystemTimeToTzSpecificLocalTime(NULL, &sm, &st);
  GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, szDate, sizeof(szDate));
  GetTimeFormat(LOCALE_USER_DEFAULT, TIME_NOSECONDS, &st, NULL, szTime, sizeof(szTime));
  wsprintf(szDateTime, _T("%s %s"), szDate, szTime);
  return szDateTime;
}

static void ListView_OnDispInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
  LV_DISPINFO *pDispInfo = (LV_DISPINFO*) pNMHDR;
  FileInfo *pFileInfo;
  static TCHAR buf[_MAX_PATH];

  switch (pDispInfo->hdr.code) {
    case LVN_GETDISPINFO:
      pFileInfo = (FileInfo*)pDispInfo->item.lParam;
      
      switch (pDispInfo->item.iSubItem) {
	case 0:			// file name
	  pDispInfo->item.mask |= LVIF_IMAGE;
	  pDispInfo->item.pszText = (LPTSTR)pFileInfo->name;
	  pDispInfo->item.iImage = GetIconIndex((LPTSTR)pFileInfo->name, pFileInfo->type);
	  break;
	  
	case 1:			// file type
	  pDispInfo->item.pszText = GetTypeName(buf,pFileInfo);
	  break;

	case 2:			// file size
	  if (pFileInfo->size != 0) {
	    int kb = (pFileInfo->size+1023)/1024;
	    TCHAR bufA[64];
	    wsprintf(buf, _T("%d"), kb);
	    GetNumberFormat(LOCALE_USER_DEFAULT, 0, buf, &g_nf, bufA, sizeof(bufA));
	    wsprintf(buf, _T("%s KB"), bufA);

	    pDispInfo->item.mask = LVIF_TEXT;
	    pDispInfo->item.iSubItem = 2;
	    pDispInfo->item.pszText = buf;
	  }
	  break;
	  
	case 3:			// file timestamp
	  pDispInfo->item.pszText = time_to_string(pFileInfo->time);
	  break;
      }
      break;
  }
}

#define COMPARE(x,y) ((x)<(y) ? -1 : (x)==(y) ? 0 : +1)

static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
  FileInfo *fiA = (FileInfo*)lParam1;
  FileInfo *fiB = (FileInfo*)lParam2;
  int signum = g_pFileOpenDlgPrivate->_sortDirection;
  int col = g_pFileOpenDlgPrivate->_sortColumn;
  TCHAR bufA[64],bufB[64];

  if(fiA->type < fiB->type)    // Directories are always less than files.
    return signum;
  else if (fiA->type > fiB->type)
    return -signum;

  switch (col) {
    case 0: return signum * lstrcmpi(fiA->name, fiB->name);
    case 1: return signum * lstrcmpi(GetTypeName(bufA,fiA), GetTypeName(bufB,fiB));
    case 2: return signum * COMPARE(fiA->size,fiB->size);
    case 3: return signum * COMPARE(fiA->time,fiB->time);
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
// Toolbar
////////////////////////////////////////////////////////////////////////////////////////
static void InitializeBackStack()
{
  // initialize stack data structure used by the Back button
  g_pFileOpenDlgPrivate->_pbackStack = new STACK;
  
  int nSize = sizeof(STACK);

  //g_pbackStack = (LPSTACK)malloc(sizeof(STACK));
  ZeroMemory((LPVOID)g_pFileOpenDlgPrivate->_pbackStack, sizeof(STACK));
  g_pFileOpenDlgPrivate->_pbackStack->top = -1;
}

static BOOL BackStackEmpty()
{
  if (g_pFileOpenDlgPrivate->_pbackStack->top < 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

static BOOL PushBackStack(LPTSTR pszDirectory)
{
  g_pFileOpenDlgPrivate->_pbackStack->top++;
  // allocate new string
  TCHAR *pszBuf = new TCHAR[_tcslen(pszDirectory) + 1];
  _tcscpy(pszBuf, pszDirectory);

  g_pFileOpenDlgPrivate->_pbackStack->pszFolders[g_pFileOpenDlgPrivate->_pbackStack->top] = pszBuf;

  return TRUE;
}

static BOOL PopBackStack(LPTSTR pszPathDir)
{
  TCHAR *pszBuf;

  if (pszPathDir == NULL)
  {
    return FALSE;
  }

  // notational convenience
  pszBuf = g_pFileOpenDlgPrivate->_pbackStack->pszFolders[g_pFileOpenDlgPrivate->_pbackStack->top];

  // copy string
  lstrcpy(pszPathDir, pszBuf);

  // delete original
  //ZeroMemory((LPVOID)&g_pFileOpenDlgPrivate->_pbackStack->szFolders[g_pFileOpenDlgPrivate->_pbackStack->top], _MAX_PATH);
  delete [] pszBuf;
  pszBuf = NULL;

  // decrement top
  g_pFileOpenDlgPrivate->_pbackStack->top--;

  return TRUE;
}

static void EnableBackButton(BOOL bShow)
{
  SendMessage(g_pFileOpenDlgPrivate->_hwndToolbar, TB_ENABLEBUTTON, IDS_BACK, MAKELONG(bShow, 0));
}

static void EnableUpButton(BOOL bShow)
{
  SendMessage(g_pFileOpenDlgPrivate->_hwndToolbar, TB_ENABLEBUTTON, IDS_UP, MAKELONG(bShow, 0));
}

// TODO: This should be in the dialog resource.
static HWND CreateToolbar(HWND hwndParent, int x, int y)
{
  TBADDBITMAP tbab;
  int stdidx = 0;
  int index = 0;

  TBBUTTON tbButtons[] = {
    { HIST_BACK, IDS_BACK, 0, BTNS_BUTTON, 0L, 0 },
    { VIEW_PARENTFOLDER, IDS_UP, TBSTATE_ENABLED, BTNS_BUTTON, 0L, 0 },
    { VIEW_LIST /*VIEWMENU*/, IDS_VIEW, TBSTATE_ENABLED, BTNS_DROPDOWN, 0L, 0 }
  };

  HWND hwndTB = CreateWindowEx(0, 
			       TOOLBARCLASSNAME, 
			       (LPTSTR) NULL, 
			       WS_CHILD | TBSTYLE_FLAT | WS_CLIPSIBLINGS | CCS_NODIVIDER |
			       WS_VISIBLE | CCS_NOPARENTALIGN | CS_VREDRAW | CCS_NORESIZE |
			       WS_CLIPCHILDREN,   
			       375, //x,   // TODO: lose the magic numbers!
			       7, //y + 5,   // TODO: ditto!
			       100,
			       30,
			       hwndParent,
			       (HMENU) IDC_TOOLBAR,
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

static BOOL DoToolbarBackBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  TCHAR szPath[_MAX_PATH];
  ZeroMemory((LPVOID)szPath, _MAX_PATH);
  TCHAR szDir[_MAX_PATH];
  ZeroMemory((LPVOID)szDir, _MAX_PATH);
  TCHAR szPathDir[_MAX_PATH] = {0};
  BOOL bRet = FALSE;

  // pop the back button history list for previously saved directory
  if (!PopBackStack(szPathDir)) // caller is responsible for deleting returned string
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

static BOOL DoToolbarUpBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  HWND hwndLookIn = GetDlgItem(g_hwndFileOpenDlg,cmb2);

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


static BOOL DoToolbarNotify(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#define lpnm   ((LPNMHDR)lParam)
#define lpnmTB ((LPNMTOOLBAR)lParam)

   RECT      rc;
   TPMPARAMS tpm;
   HMENU     hPopupMenu = NULL;
   BOOL      bRet = FALSE;

   switch(lpnm->code){
      case TBN_DROPDOWN:
         SendMessage(lpnmTB->hdr.hwndFrom, TB_GETRECT, (WPARAM)lpnmTB->iItem, (LPARAM)&rc);

         MapWindowPoints(lpnmTB->hdr.hwndFrom, HWND_DESKTOP, (LPPOINT)&rc, 2);                         

         tpm.cbSize = sizeof(TPMPARAMS);
         tpm.rcExclude = rc;

         TrackPopupMenuEx(g_pFileOpenDlgPrivate->_hViewsMenu,
            TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,               
            rc.left, rc.bottom, g_hwndFileOpenDlg, &tpm);      

      return (FALSE);
   }

   return FALSE;
}



///////////////////////////////////////////////////////////////////////////////////////
// Shortcut Bar
///////////////////////////////////////////////////////////////////////////////////////

//
// Get ShortcutBar instance from the specified window
//
static ShortcutBar * GetShortcutBar(HWND hwnd)
{
  return (ShortcutBar *)GetWindowLongPtr(hwnd,GWLP_USERDATA);
}

//
// Set ShortcutBar instance for the specified window
//
static void SetShortcutBar(HWND hwnd, ShortcutBar *psb)
{
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)psb);
}

ShortcutBar::ShortcutBar(HWND hwnd)
{
  _hwnd = hwnd;
  _btnHeight = 60;
  _largeFolderIcon = NULL;
  _bMouseIn = FALSE;
  ZeroMemory(_shortcutItems, MAX_ITEMS*sizeof(LPSHORTCUTBARITEMSTRUCT));
  _nItemCount = 0;
  _systemFolderIcons[0] =  20; // My Recent Documents
  _systemFolderIcons[1] =  34; // Desktop
  _systemFolderIcons[2] = 126; // My Documents
  _systemFolderIcons[3] =  15; // My Computer
  _systemFolderIcons[4] =  17; // My Network Places
}

ShortcutBar::~ShortcutBar()
{
  ClearItems();
}

void ShortcutBar::ClearItems()
{
  for (int i = 0; i < _nItemCount; i++)
  {
    if (_shortcutItems[i] != NULL)
    {
      delete _shortcutItems[i];
      _shortcutItems[i] = NULL;
    }
  }

  _nItemCount = 0;
}

void ShortcutBar::SetLargeFolderIcon(HICON largeFolderIcon)
{
  _largeFolderIcon = largeFolderIcon;
}

LRESULT
ShortcutBar::OnResetContent(WPARAM wParam, LPARAM lParam)
{
  ClearItems();

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

  _shortcutItems[_nItemCount] = new SHORTCUTBARITEMSTRUCT;
  CopyMemory((LPVOID)(_shortcutItems[_nItemCount]), (LPVOID)lpsbi, sizeof(SHORTCUTBARITEMSTRUCT));

  // increment item count
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
      _TrackMouseEvent(&tme);
    }

  GetWindowRect(Hwnd(), &cr);
  ScreenToClient(_hwnd, LPPOINT(&cr.left));
  ScreenToClient(_hwnd, LPPOINT(&cr.right));

  InvalidateRect(Hwnd(), &cr, FALSE);//TRUE);
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

  InvalidateRect(Hwnd(), &cr, FALSE); //TRUE);
  UpdateWindow(Hwnd());

  return 0L;
}

LRESULT 
ShortcutBar::OnPaint(WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  RECT rect;
  HDC hdc;
  HDC hdcCompat;
  int nSections = 0;
  POINT ptBegin, ptEnd;
  int cxClient;
  int cyClient;
  int y = 0;
  TEXTMETRIC tm;
  RECT rectSelect;
  HBITMAP hbmDraw;
  HBITMAP hbmOld;


  GetClientRect(_hwnd, &rect);
  cxClient = rect.right;
  cyClient = rect.bottom;

  InvalidateRect(_hwnd, &rect, FALSE);//TRUE);

  // get the device context
  hdc = BeginPaint(_hwnd, &ps);
  hdcCompat = CreateCompatibleDC(hdc); 

  hbmDraw = CreateCompatibleBitmap(hdc, cxClient, cyClient);
  hbmOld = (HBITMAP)SelectObject(hdcCompat, hbmDraw);

  // select a font
  SetTextColor(hdcCompat, GetSysColor(COLOR_BTNTEXT));
  SelectObject(hdcCompat, GetStockObject(ANSI_VAR_FONT));

  // measure the text
  GetTextMetrics(hdcCompat, &tm);
  // calculate text begin
  //cxText = 0; //20;//(cyClient / 2) - ((tm.tmAveCharWidth * strlen(_szName)) / 2);

  ptBegin.x = ptBegin.y = 0; //5;
  ptEnd.x = rect.right; ptEnd.y = 0;

  // draw the sections
  for (int i = 0; i < _nItemCount; i++)
  {
    y = ptBegin.y;

    // make a rectangle of our window area
    rectSelect.bottom = y + 60; 
    rectSelect.left = 0;
    rectSelect.right = cxClient;
    rectSelect.top = y;

    DrawButton(hdcCompat, rectSelect, tm, i);

    // adjust
    ptBegin.y += _btnHeight;

  }

  BitBlt(hdc, 
    0, 
    0, 
    cxClient,
    ptBegin.y, 
    hdcCompat,
    0,
    0,
    SRCCOPY);

  SelectObject(hdcCompat, hbmOld);
  DeleteObject(hbmDraw);
  DeleteDC(hdcCompat);

  EndPaint(Hwnd(), &ps);

  return 0;
}

void ShortcutBar::DrawButton(HDC hdc, RECT r, TEXTMETRIC tm, int index)
{
  UINT grfEdge;
  UINT grfFlags;
  int iBkgndColor;
  COLORREF crBkgnd;
  POINT pt;
  int cxText = 0;

  iBkgndColor = COLOR_3DSHADOW; // COLOR_WINDOW;
  grfEdge = BDR_SUNKENOUTER; 
  grfFlags = BF_FLAT; 

  if (_bMouseIn == TRUE)
  {
    // figure out which quadrant we are in
    GetCursorPos(&pt);
    // convert to client coordinates
    ScreenToClient(_hwnd, &pt);

    if ((pt.y > r.top) && (pt.y < r.top + _btnHeight) )
    {
      //      iBkgndColor = COLOR_WINDOW; //COLOR_HIGHLIGHT;
      grfFlags = BF_RECT | BF_SOFT; 
      grfEdge = EDGE_RAISED; 
    }
  }

  crBkgnd = GetSysColor(iBkgndColor);
  SetBkColor(hdc, crBkgnd);
  SetTextColor(hdc, GetSysColor(COLOR_WINDOW)); // COLOR_BTNTEXT
  ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &r, NULL, 0, NULL);

  // draw our 3D 'button'
  RECT rc2 = r;
  //InflateRect(&rc2, -1, -1);
  DrawEdge(hdc, &rc2, grfEdge, grfFlags);

  // calculate origin
  int xOffset = (r.right / 2) - (SHORTCUT_CXICON / 2);
  r.top += 2;
  // draw folder icon
  //DrawIconEx(hdc, xOffset, r.top, _largeFolderIcon, SHORTCUT_CXICON, SHORTCUT_CYICON, 0, NULL, DI_NORMAL | DI_COMPAT);


  if ( index >= 0 && index < 5 ) {
    HICON hIcon = NULL;
    ExtractIconEx(_T("shell32.dll"), _systemFolderIcons[index], &hIcon, NULL, 1);
    DrawIconEx(hdc, xOffset, r.top, hIcon, SHORTCUT_CXICON, SHORTCUT_CYICON, 0, NULL, DI_NORMAL | DI_COMPAT);
  //DestroyIcon
  }

  r.top += SHORTCUT_CYICON + 2;

  RECT rectText;
  rectText.top = r.top;
  rectText.bottom = r.top + tm.tmHeight;
  rectText.right = r.right; 
  rectText.left = cxText;

  DrawText(hdc,
    _shortcutItems[index]->szName,
    -1, // automatically calculates length for null-terminated string in 2nd parameter
    &rectText,
    DT_CENTER | DT_WORD_ELLIPSIS);

}

LRESULT
ShortcutBar::OnSize(WPARAM wParam, LPARAM lParam)
{
  return 0L;  
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
      PostMessage(g_hwndFileOpenDlg, g_uFODRefreshMsgId, (WPARAM) _shortcutItems[i]->szDir, (LPARAM) _shortcutItems[i]->szPath);
      break;
    }

    y += 60;
  }

//  HWND hwndLookin = GetDlgItem(g_hwndFileOpenDlg,cmb2);
//  int nIdx = SendMessage(hwndLookin, CB_FINDSTRINGEXACT, -1, (LPARAM)(_items[i].szText));
//  SendMessage(hwndLookin, CB_SETCURSEL, nIdx, 0);

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

  case WM_SIZE:
    return pShortcutBar->OnSize(wParam, lParam);

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

static HICON GetLargeFolderIcon()
{
  SHFILEINFO sfi;
  memset(&sfi, 0, sizeof(sfi));

  DWORD_PTR pdw = SHGetFileInfo (
    _T("dummy"), 
    FILE_ATTRIBUTE_DIRECTORY, 
    &sfi, 
    sizeof(sfi), 
    SHGFI_LARGEICON | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES
  );
  
  SHORTCUT_CXICON = ::GetSystemMetrics(SM_CXICON);
  SHORTCUT_CYICON = ::GetSystemMetrics(SM_CXICON);
  
  return sfi.hIcon;
}

static ATOM RegisterShortcutBar(HINSTANCE hInst)
{
  WNDCLASSEX wcex;
  
  g_uAddItemMsgId = RegisterWindowMessage(SB_ADDITEM_MSG_STR);
  g_uResetContentMsgId = RegisterWindowMessage(SB_RESETCONTENT_MSG_STR);

  wcex.cbSize = sizeof(WNDCLASSEX); 

  wcex.style      = 0; 
  wcex.lpfnWndProc  = (WNDPROC)ShortcutBar::WndProc;
  wcex.cbClsExtra   = 0;
  wcex.cbWndExtra   = sizeof(ShortcutBar*);
  wcex.hInstance    = (HINSTANCE)hInst;
  wcex.hIcon      = NULL;
  wcex.hCursor    = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_3DSHADOW+1);
  wcex.lpszMenuName = (LPCTSTR)NULL;
  wcex.lpszClassName  = SHORTCUTBARCLASS;
  wcex.hIconSm    = NULL; //LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

  return RegisterClassEx(&wcex);
}

// subclass listview to enact proper RETURN key behavior
LRESULT CALLBACK ListViewProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) {
    case WM_GETDLGCODE:

      // when the focus is in a listview control inside a dialog box,
      // the default ENTER key action will not occur

      // we want the ENTER key
      if ( (wParam == VK_RETURN) || (wParam == VK_BACK) ) {
        return DLGC_WANTALLKEYS;
      }

      break;

    case WM_SETFOCUS:
      if (GetFocusedLVItem(g_pFileOpenDlgPrivate->_hwndLV) == -1) {
        // set the focus rectangle to the first item in the list
        ListView_SetItemState(g_pFileOpenDlgPrivate->_hwndLV, 0, LVIS_FOCUSED, LVIS_FOCUSED);
      }
      
      break;

    case WM_DESTROY:
      // remove the subclass for the listview control
      SetWindowLongPtr(hwnd, GWLP_WNDPROC, (DWORD)lpfnOldLVWndProc);

      break;

    default:
      break;

  }

  return CallWindowProc((WNDPROC)lpfnOldLVWndProc, hwnd, msg, wParam, lParam);
}

static BOOL absolute_path_p(TCHAR *path)
{
  if (path[0] == g_separator)
    return TRUE;

  // Check for Windows drive letter.
  else if (g_separator == _T('\\') && _tcslen(path) >= 3 &&
           isalpha(path[0]) && path[1] == _T(':') && path[2] == g_separator)
    return TRUE;

  else
    return FALSE;
}

static BOOL looks_like_directory_p(TCHAR *path)
{
  int n = _tcslen(path);
  return n>0 && path[n-1] == g_separator;
}



/*
 * g2ext_get_places_bar
 *
 * Computes a double-NUL terminated string of pathnames of the directories which
 * would appear in the "places bar" in the built-in file dialog. We use these
 * to fill-in the places bar of our homegrown file dialog.
 *
 * The places bar is not available on NT 4.0 (nor is SHGetSpecialFolderPath).
 *
 * Returns the number of directories placed into buffer. */

long g2ext_get_places_bar(LPWSTR buffer, long buflen)
{
  DWORD default_places[] = {CSIDL_RECENT,		// History
                            CSIDL_DESKTOPDIRECTORY,	// Desktop
                            CSIDL_PERSONAL,		// My Documents
                            CSIDL_DRIVES,		// My Computer
                            CSIDL_APPDATA};		// (can't handle CSIDL_NETWORK)
  int i,n;
  HKEY hkey;
  DWORD type, len;
  LPWSTR ptr;
  WCHAR name[20], value[MAX_PATH], tem[MAX_PATH];

  n=0;
  buffer[0] = _T('\0');
  ptr = buffer;

  hkey=NULL;
  RegOpenKeyEx(HKEY_CURRENT_USER,
               _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\ComDlg32\\PlacesBar"),
               0, KEY_QUERY_VALUE, &hkey);

  for(i=0; i<5; i++) {
    wsprintf(name, _T("Place%d"), i);
    len = sizeof(value);				// bytes
    ZeroMemory(value,len);

    if(hkey == NULL ||
       RegQueryValueEx(hkey, name, NULL, &type, (LPBYTE)value, &len) != ERROR_SUCCESS) {
      type = REG_DWORD;
      *((DWORD*)value) = default_places[i];
    }

    tem[0] = '\0';
    switch(type) {
     case REG_DWORD:
#ifdef BREAK_THE_ET_ON_NTL
       SHGetSpecialFolderPath(NULL, tem, *((DWORD*)value), FALSE);
#endif
       break;
     case REG_SZ:
       wcscat(tem, value);
       break;
     case REG_EXPAND_SZ:
       ExpandEnvironmentStrings(value, tem, MAX_PATH-1);
       break;
    }

    len = wcslen(tem);					// tchars
    if(0 < len && len < (DWORD)((buffer + buflen - 2) - ptr)) {
      wcscpy(ptr, tem);
      ptr += len + 1;
      n++;
    }
  }
  if(hkey)
    RegCloseKey(hkey);
  *ptr++ = '\0';
  return n;
}



/*
 * Choose (Client-Side) Directory
 */

typedef struct {
  LPWSTR pathname;
  LPWSTR okLabel;
  LPWSTR cancelLabel;
} Stuff;

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT message, LPARAM lParam, LPARAM pData) 
{
  switch(message) {
   case BFFM_INITIALIZED: 
     if(pData) {
       Stuff *pStuff = (Stuff *)pData;
       if(pStuff->pathname && pStuff->pathname[0])
	 SendMessage(hwnd, BFFM_SETSELECTIONW, TRUE, (LPARAM)pStuff->pathname);

       if(pStuff->okLabel && pStuff->okLabel[0])
	 if(IsWinXP())
	   SendMessage(hwnd, BFFM_SETOKTEXT, 0, (LPARAM)pStuff->okLabel); // Only works on XP.
	 else
	   SetDlgItemText(hwnd, IDOK, pStuff->okLabel);

       if(pStuff->cancelLabel && pStuff->cancelLabel[0])
	 SetDlgItemText(hwnd, IDCANCEL, pStuff->cancelLabel);
     }
     break;
  }
  return 0;
}

static LPITEMIDLIST GetIDListFromPath(LPWSTR pathname)
{
  IShellFolder *pDesktopFolder;
  LPITEMIDLIST pIDL = 0;

  if(pathname && pathname[0] && SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder))) {
    pDesktopFolder->ParseDisplayName(NULL, NULL, pathname, NULL, &pIDL, NULL);
    pDesktopFolder->Release();
  }
  return pIDL;
}

// The pathname buffer must be at least MAX_PATH characters long.
BOOL BrowseForFolder(HWND hwndOwner, LPWSTR caption, LPWSTR pathname, LPWSTR root,
		     LPWSTR okLabel, LPWSTR cancelLabel)
{
  BROWSEINFO bi = {0};
  LPITEMIDLIST pIDL = 0;
  LPITEMIDLIST pidlRoot = GetIDListFromPath(root);
  IMalloc *iMalloc = 0;
  BOOL rc = FALSE;
  Stuff stuff = {pathname, okLabel, cancelLabel};

  bi.hwndOwner = hwndOwner;
  bi.pidlRoot = pidlRoot;
  bi.lpszTitle = caption;
  bi.pszDisplayName = pathname;
  bi.ulFlags = BIF_RETURNONLYFSDIRS;
  bi.lpfn = BrowseCallbackProc;
  bi.lParam = (LPARAM)&stuff;
  pIDL = SHBrowseForFolder(&bi);

  if(pIDL) {
    pathname[0] = L'\0';
    if(SHGetPathFromIDList(pIDL, pathname))
      rc = TRUE;
  }

  if(SUCCEEDED(SHGetMalloc(&iMalloc))) {
    if(pIDL)
      iMalloc->Free(pIDL);
    if(pidlRoot)
      iMalloc->Free(pidlRoot);
    iMalloc->Release();
  }
  return rc;
}


/*
 * String list is a list where elements are separated by NULL with double NULL ending.
 * Copy a "double-NUL" string.
 */
WCHAR* strlist_copy(WCHAR* dst, WCHAR* src)
{
	WCHAR* src_ptr = src;
	WCHAR* dst_ptr = dst;
	size_t len = 0;
	
	while ( src_ptr && *src_ptr ) {
		_tcscpy( dst_ptr, src_ptr );
		len = _tcslen(src_ptr)+1;
		src_ptr += len;
		dst_ptr += len;
	}
	*dst_ptr++ = _T('\0');
	
	return dst;
}
