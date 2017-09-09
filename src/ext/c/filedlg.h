/* -*- Mode: C++ -*-
 *
 * Module:      FILEDLG.H
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Author(s): 2004      lk, fmw
 *
 * DESCRIPTION: Internal and external header for custom file dialog.
 *
 * Modifications:
 *   4/15/04, fmw: Created from FileOpenCommon.h
 */

#ifdef WIN32
#pragma once

#include "resizer.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Public interface
 */

/* Entry points */
extern BOOL GetServerFileName(OPENFILENAMEW *ofn);
extern BOOL BrowseForFolder(HWND hwndOwner, LPWSTR caption, LPWSTR pathname, LPWSTR root,
			    LPWSTR okLabel, LPWSTR cancelLabel);
extern HIMAGELIST CreateFolderImageList();

#define FILETYPE_LEAF 0
#define FILETYPE_FOLDER 1
#define SYSTEM_FOLDERS_MAX 5
typedef struct {
  int type;			// 1 = folder, 0 = other
  unsigned long size;		// in bytes
  time_t time;			// modification time (unix format)
  LPWSTR name;			// the file name (sans-directory)
} FileInfo;

#define STR_SIZE 256
typedef struct {
	WCHAR shortcuts[5*STR_SIZE];
	WCHAR shortcut_names[5*STR_SIZE];
	WCHAR drives[STR_SIZE];
} OFNCustomData_s;



typedef void (*ListDirCallback) (FileInfo *info, int count);
typedef void (*ListDirFunction) (LPTSTR directory, ListDirCallback callback);

extern long g2ext_get_places_bar(LPWSTR buffer, long buflen);


WCHAR* strlist_copy(WCHAR* dst, WCHAR* src);

#ifdef __cplusplus
}
#endif


/*
 * Internal interfaces
 */

#ifdef FILEDLG_INTERNAL

// C RunTime Header Files
#include <shellapi.h>

// some re-defines
#define DWORD_PTR   DWORD
#define BTNS_DROPDOWN TBSTYLE_DROPDOWN
#define BTNS_BUTTON   TBSTYLE_BUTTON

// maximums and minimums
#define STACKSIZE     20
#define MIN_TBCX      125 
#define MIN_COMBOCX     75 
#define MIN_COMBOCY     42
#define MIN_CY        50

#define MAX_FILTERS 20

#define MAX_FILTER_LEN    256
#define MAX_TITLE_LEN   256

// command ids for Views toolbar dropdown menu
#define ID_LARGEICONS 0
#define ID_SMALLICONS 1
#define ID_LIST     2
#define ID_DETAILS    3

// file open dialog refresh message
#define FOD_REFRESH_MSG_STR     _T("FileOpenDlg.Refresh")

// shortcut bar
#define SHORTCUTBARCLASS        _T("ShortcutBar")
#define SB_ADDITEM_MSG_STR      _T("ShortcutBar.AddItem")  // to generate unique window message id
#define SB_RESETCONTENT_MSG_STR _T("ShortcutBar.ResetContent")
#define MAX_LEN           255       // maximum item text length
#define MAX_ITEMS         20        // maximum number of items

// holds the FileInfo* structures passed to us from g2pvt_ListDirectoryAsync's callback
typedef struct tag_FILEINFOS
{
  int _count;
  FileInfo *_fileInfos;
} FILEINFOS, *LPFILEINFOS;

// what we get when we're first called; passed as a parameter via CreateDialogParam()
typedef struct tag_FILEOPEN
{
  BOOL bMustExist;            // if TRUE, post as 'open' style dialog else post as 'save' style dialog
  char szFilter[MAX_FILTER_LEN];
  char szDirectory[_MAX_PATH];
  char szName[_MAX_PATH];
  char szTitle[MAX_TITLE_LEN];
//  wchar_t szTitle[MAX_TITLE_LEN*sizeof(wchar_t)];
  HWND hwndOwner;
} FILEOPEN, *LPFILEOPEN;

// used by the ShortcutBar as item data
typedef struct tag_SHORTCUTBARITEMSTRUCT
{
  int cbSize;
  TCHAR szName[_MAX_PATH];
  TCHAR szPath[_MAX_PATH];
  TCHAR szDir[_MAX_PATH];
  int iBitmap;      // reserved for future use
} SHORTCUTBARITEMSTRUCT, *LPSHORTCUTBARITEMSTRUCT;

// stack structure for the back button
typedef struct tag_Stack
{
  int top;
  TCHAR *pszFolders[STACKSIZE];
} STACK, *LPSTACK;

// we'll use one of these declared statically to hold things we need during the
// course of the dialog box's lifetime
typedef struct tag_OpenFileDlgPrivate
{
  // image lists
  HIMAGELIST _hImageListSmall;   // global image list for file dir list view - small
  HIMAGELIST _hImageListLarge;   // image list for file dir list view - large
  HIMAGELIST _hilLookin;	 // image list for lookin combobox

  // global handles
  HMENU _hViewsMenu;		 // global views menu handle
  HWND _hwndLV;			 // handle of the file dir list view
  HWND _hwndToolbar;		 // toolbar hwnd
  HWND _hwndShortcutBar;	 // shortcut bar hwnd
  HWND _hwndChild;		 // Child dialog, if any

  // listview sorting
  int _sortDirection;	         // 1=ascending, -1=descending, 0=unsorted
  int _sortColumn;		 // Column index

  // listview filtering
  TCHAR *filters[MAX_FILTERS]; // Parsed filter strings: each is "*.type; ... *.type;"
  int nfilters;

  // lookin combobox
  TCHAR _szCurrLookinData[_MAX_PATH];    // current lookin combobox itemdata; used in BACK functionality
  TCHAR _szCurrDirectory[_MAX_PATH];   // current directory; used for updated whenever new directory is selected  TODO:
  LPSTACK _pbackStack;          // stack for the Back button
} OPENFILEDLGPRIVATE, *LPOPENFILEDLGPRIVATE;

extern LPOPENFILEDLGPRIVATE g_pFileOpenDlgPrivate;
extern FILEINFOS g_fileInfos;

// user-defined messages
// file open dialog
extern UINT g_uFODRefreshMsgId;         // refresh dialog

// shortcut bar
extern UINT g_uAddItemMsgId;          // add item message id
extern UINT g_uResetContentMsgId;       // reset content id

extern HWND g_hwndFileOpenDlg;          // file open dialog hwnd
//extern char achTemp[256];           // temporary buffer

extern int CX_ICON;
extern int CY_ICON;

// initialization and cleanup functions
static int PopulateFileTypes(HWND hdlg, LPCTSTR pszFilter, TCHAR *filters[], int n);
static void UpdateFileName(HWND hdlg, LPTSTR pszFileName);
static void AddColumns(HWND hwnd);
static void AddListDirItem(FileInfo info, int i);
static int GetViewStyle(void);
static void SetView(DWORD dwViewStyle);
static void SetListViewImageList(HWND hwndLV, HIMAGELIST &hilSmall, HIMAGELIST &hilLarge);
static void GetSystemImageLists(HIMAGELIST &hilSmall, HIMAGELIST &hilLarge);

// cleanup functions
static void CleanupFileInfos();
static void Cleanup();

// dialog proc and helper functions
static INT_PTR CALLBACK GensymFileOpenDlgProc(HWND hDlg, UINT message,
											  WPARAM wParam, LPARAM lParam);
static BOOL GensymOpenFileDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
static void GensymOpenFileDlg_OnPaint(HWND hwnd);
static UINT GensymOpenFileDlg_OnNcHitTest(HWND hwnd, int x, int y);

// Lookin combobox functions
static void ResetLookinCombobox(HWND hwndLookIn);
static void DoLookinComboSelChange(HWND hwndLookIn);

static void PopulateListView(FileInfo *info, int count);
static BOOL PopulateLookInCombo(HWND hdlg, LPTSTR pszDirectory);

// global file open struct functions
static void GetCurrDir(LPTSTR pszCurrDir, int cchBuffer);

// general operations
static BOOL RefreshFileList(LPTSTR szPath, LPTSTR szDirectory);
// given szPathDir, return separate path\ and directory strings
static int SplitDirectoryFromPath(LPTSTR szPathDir, LPTSTR szPath, LPTSTR szDirectory);

// listview
static LPTSTR GetSelectedFile(HWND hwndLV, int i, TCHAR *buf, int buflen);
static TCHAR* GetTypeName (TCHAR *buf, FileInfo *fi);
static void SetImageList(HWND hdlg, HWND hwndLV, HIMAGELIST hImageList);
static int GetIconIndex (LPTSTR strFPath, int nType);
static void FileListView_DoubleClick(HWND hwndLV);
static void ListView_OnDispInfo(NMHDR *pNMHDR, LRESULT *pResult);
static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
static BOOL AddItem(FileInfo* pFileInfo, int nPos);
static void ResetFileList(HWND hwndLV);

// toolbar
static HWND CreateToolbar(HWND hwndParent, int x, int y);
static BOOL DoToolbarNotify(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static BOOL DoToolbarBackBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static BOOL DoToolbarUpBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static void EnableUpButton(BOOL bShow);
static void EnableBackButton(BOOL bShow);
static int NextViewStyle();

// back button stack operations
static void InitializeBackStack();
static BOOL PushBackStack(LPTSTR pszDirectory);
static BOOL BackStackEmpty();
static BOOL PopBackStack(LPTSTR pszPathDir);

// shortcut bar
static HICON GetLargeFolderIcon();
static ATOM RegisterShortcutBar(HINSTANCE hInst);

class ShortcutBar
{
public:
  ShortcutBar(HWND hwnd);
  ~ShortcutBar();

  // message handlers
  LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
  LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
  LRESULT OnSize(WPARAM wParam, LPARAM lParam);
  LRESULT OnCommand(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
  LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
  LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
  LRESULT OnAddItem(WPARAM wParam, LPARAM lParam);
  LRESULT OnResetContent(WPARAM wParam, LPARAM lParam);

  void ClearItems();

  // static window procedure
  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  HWND Hwnd () const { return _hwnd; }
  HWND ButtonHwnd() { return _hwndBtn; }
  void ButtonHwnd(HWND hwndBtn) { _hwndBtn = hwndBtn; }
  void DrawButton(HDC hdc, RECT r, TEXTMETRIC tm, int index);

  void SetLargeFolderIcon(HICON largeFolderIcon);

private:
  HWND _hwnd;
  int _btnHeight;
  HWND _hwndBtn;
  RECT _rect;
  HICON _largeFolderIcon;
  int _systemFolderIcons[SYSTEM_FOLDERS_MAX];
  BOOL _bMouseIn;
  int _nItemCount;
  LPSHORTCUTBARITEMSTRUCT _shortcutItems[MAX_ITEMS];
};

#endif /* FILEDLG_INTERNAL */

#endif /* WIN32 */
