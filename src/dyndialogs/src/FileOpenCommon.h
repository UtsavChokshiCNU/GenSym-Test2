#pragma once

// C RunTime Header Files
#include <shellapi.h>
#include "ddrsc.h"

// some re-defines
#define DWORD_PTR		DWORD
#define BTNS_DROPDOWN	TBSTYLE_DROPDOWN
#define BTNS_BUTTON		TBSTYLE_BUTTON

// maximums and minimums
#define STACKSIZE			20
#define MIN_TBCX			125 
#define MIN_COMBOCX			75 
#define MIN_COMBOCY			42
#define MIN_CY				50

#define MAX_FILTER_LEN		20
#define MAX_TITLE_LEN		30

// command ids for Views toolbar dropdown menu
#define ID_LARGEICONS	0
#define ID_SMALLICONS	1
#define ID_LIST			2
#define ID_DETAILS		3

// file open dialog refresh message
#define FOD_REFRESH_MSG_STR	"FileOpenDlg.Refresh"

// shortcut bar
#define SHORTCUTBARCLASS           "ShortcutBar"
#define SB_ADDITEM_MSG_STR "ShortcutBar.AddItem"	// to generate unique window message id
#define SB_RESETCONTENT_MSG_STR "ShortcutBar.ResetContent"
#define MAX_LEN						255				// maximum item text length
#define MAX_ITEMS					20				// maximum number of items

// toolbar
#define GENSYM_FILEOPEN_TOOLBAR "GensymFileOpenToolbar"

// structures
typedef struct tag_FileInfo
{
	int type;			// 1 = folder, 0 = other
	LPCSTR name;		// the file name not including the path
	long size;			// in bytes
	FILETIME time;		// modification time
} FileInfo;

// holds the FileInfo* structures passed to us in our ListDirectoryAsync callback
typedef struct tag_FILEINFOS
{
	int _count;
	FileInfo *_fileInfos;
} FILEINFOS, *LPFILEINFOS;

// what we get when we're first called; passed as a parameter via CreateDialogParam()
typedef struct tag_FILEOPEN
{
	BOOL bMustExist;						// if TRUE, post as 'open' style dialog else post as 'save' style dialog
	char szFilter[MAX_FILTER_LEN];
	char szDirectory[_MAX_PATH];
	char szName[_MAX_PATH];
	wchar_t szTitle[MAX_TITLE_LEN*sizeof(wchar_t)];
	HWND hwndOwner;
} FILEOPEN, *LPFILEOPEN;

// used by the ShortcutBar as item data
typedef struct tag_SHORTCUTBARITEMSTRUCT
{
	int cbSize;
	char szPath[_MAX_PATH];
	char szDir[_MAX_PATH];
	int iBitmap;			// reserved for future use
} SHORTCUTBARITEMSTRUCT, *LPSHORTCUTBARITEMSTRUCT;

// Views dropdown menu item data
typedef struct tag_ViewsMenuItem
{
	HBITMAP hbm;
	char *pszText;
	int cchItemText;
	UINT nCmdId;
} VIEWSMENUITEM, *LPVIEWSMENUITEM;

// stack structure for the back button
typedef struct tag_Stack
{
	int top;
	char *pszFolders[STACKSIZE];
} STACK, *LPSTACK;

// for open file dialog initialization
typedef struct tag_OpenFileDlgInit
{
	FILEOPEN _fileOpen;						// incoming settings
	char *_pszShortcuts[MAX_ITEMS];			// holds shortcut bar items until they can be added to the ShortcutBar control

} OPENFILEDLGINIT, *LPOPENFILEDLGINIT;

// collection of various resizing attributes
typedef struct tag_OpenFileDlgResize
{
	// resize anchors
	RECT _rectMinSize;						// minimum dialog box size
	SIZE _szOpenBtnAnchor;					// Open button anchor
	SIZE _szCancelBtnAnchor;				// Cancel button anchor
	SIZE _szListViewBRAnchor;				// file listview bottom right anchor
	SIZE _szListViewTLAnchor;				// file listview top left anchor
	SIZE _szFileLookinBRAnchor;				// lookin combobox
	SIZE _szFileNameBRAnchor;				// filename combobox
	SIZE _szFileTypesBRAnchor;				// filetypes combobox
	SIZE _szFileNameStaticBRAnchor;			// filename static text
	SIZE _szFileTypesStaticBRAnchor;		// filetypes static text
	SIZE _szToolbarBRAnchor;				// toolbar anchor

} OPENFILERESIZE, *LPOPENFILERESIZE;

// we'll use one of these declared statically to hold things we need during the course of the dialog box's lifetime
typedef struct tag_OpenFileDlgPrivate
{
	// resizing info
	OPENFILERESIZE _openFileResize;			

	// image lists
	HIMAGELIST _hImageListSmall;			// global image list for file dir list view - small
	HIMAGELIST _hImageListLarge;			// image list for file dir list view - large
	HIMAGELIST _hilViews;					// image list for views
	HIMAGELIST _hilLookin;					// image list for lookin combobox

	// global handles
	HMENU _hViewsMenu;						// global views menu handle
	HWND _hwndLV;							// handle of the file dir list view
	HWND _hwndToolbar;						// toolbar hwnd
	HWND _hwndShortcutBar;					// shortcut bar hwnd

	// listview sorting
	int _ColSort[4];						// column sort flags - ASC or DESC

	// lookin combobox
	char _szCurrLookinData[_MAX_PATH];		// current lookin combobox itemdata; used in BACK functionality
	char _szCurrDirectory[_MAX_PATH];		// current directory; used for updated whenever new directory is selected  TODO:
	LPSTACK _pbackStack;					// stack for the Back button


} OPENFILEDLGPRIVATE, *LPOPENFILEDLGPRIVATE;

// used by the ShortcutBar
typedef struct tag_ShortcutBtn
{
	char *pszText;
	bool bHasFocus;
} ShortcutBtn;

extern LPOPENFILEDLGPRIVATE g_pFileOpenDlgPrivate;
extern FILEINFOS g_fileInfos;

// user-defined messages
// file open dialog
extern UINT g_uFODRefreshMsgId;					// refresh dialog

// shortcut bar
extern UINT g_uAddItemMsgId;					// add item message id
extern UINT g_uResetContentMsgId;				// reset content id

#define ASC		0
#define	DESC	1

extern HINSTANCE g_hInst;						// current instance
extern HWND g_hwndFileOpenDlg;					// file open dialog hwnd
//extern char achTemp[256];						// temporary buffer

extern int CX_ICON;
extern int CY_ICON;

// file open callback signature
typedef void (*ListDirCallback) (FileInfo *info, int count, LPARAM lParam);

// initialization and cleanup functions
void ChooseFileNotify(HWND hwndDialog, int code, LPSTR result);
HWND ChooseFile(LPCSTR directory, LPCSTR initialFileName, LPCSTR filter, LPBYTE pbShortcuts, int cbShortcuts, LPWSTR title, HWND hwndOwner, BOOL mustExist);
LPOPENFILEDLGINIT Initialize(LPCSTR directory, LPCSTR initialFileName, LPCSTR filter, LPBYTE pbShortcuts, int cbShortcuts, LPWSTR title, HWND hwndOwner, BOOL mustExist);
void ParseShortcuts(LPOPENFILEDLGINIT lpofdi, LPBYTE pbShortcuts, int cbShortcuts);
void InitFileOpenStruct(LPOPENFILEDLGINIT lpofdi, LPCSTR directory, LPCSTR initialFileName, LPCSTR filter, LPWSTR title, HWND hwndOwner, BOOL mustExist);
BOOL PopulateFileTypes(HWND hdlg, LPCSTR pszFilter);
BOOL UpdateFileName(HWND hdlg, LPCSTR pszFileName);
void AddColumns(HWND hwnd);
void AddListDirItem(FileInfo info, int i);
void SetView(DWORD dwViewStyle);
void SetListViewImageList(HWND hwndLV, HIMAGELIST &hilSmall, HIMAGELIST &hilLarge);
void GetSystemImageLists(HIMAGELIST &hilSmall, HIMAGELIST &hilLarge);
void SetViewsImageList(HIMAGELIST &hilViews);
HMENU CreatePopupMenuItems(HWND hwnd);
void SetChildControlRects(HWND hwnd);

// cleanup functions
void CleanupFileInfos();
void Cleanup();
void CleanupFileOpenDlgInitStruct(LPOPENFILEDLGINIT lpofdi);

// dialog proc and helper functions
LRESULT CALLBACK GensymFileOpenDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
static BOOL GensymOpenFileDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
static void GensymOpenFileDlg_OnPaint(HWND hwnd);
static void GensymOpenFileDlg_OnSize(HWND hwnd, UINT state, int cx, int cy);
static void GensymOpenFileDlg_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpmmi);
static UINT GensymOpenFileDlg_OnNcHitTest(HWND hwnd, int x, int y);

void GetSizeGripRect(HWND hwnd, LPRECT lpRect);

// move functions
static void MoveButton(HWND hwnd, HDWP hdwp, UINT id, SIZE szBtnAnchor);
static void MoveListView(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight);
static void ResizeCombobox(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight);
static void MoveCombobox(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight);
static void MoveToolbar(HWND hwnd, HDWP hdwp, SIZE szBottomRight);
static void ResizeShortcutBar(HWND hwnd, HDWP hdwp);
static void MoveStatic(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight);

// Lookin combobox functions
void ResetLookinCombobox(HWND hwndLookIn);
void DoLookinComboSelChange(HWND hwndLookIn);

void PopulateListDir(FileInfo *info, int count, LPARAM lParam);
BOOL PopulateLookInCombo(HWND hdlg, LPCSTR pszDirectory);

// global file open struct functions
BOOL SetDirectory(LPOPENFILEDLGINIT lpofdi, LPCSTR szDirectory);
void GetCurrDir(LPSTR pszCurrDir, int cchBuffer);

// general operations
BOOL RefreshFileList(LPCSTR szPath, LPCSTR szDirectory);
LPSTR RemoveTrailingSlash(LPSTR szPathName);
// given szPathDir, return separate path\ and directory strings
int SplitDirectoryFromPath(LPSTR szPathDir, LPSTR szPath, LPSTR szDirectory);

// listview
LPSTR FileListSelect(HWND hDlg, HWND hwndLV);
void AddFileListItem(HWND hwnd, INT nItem, LPCSTR pszName, int nType, INT nSize);
TCHAR* GetTypeName (LPSTR strFPath);
void SetImageList(HWND hdlg, HWND hwndLV, HIMAGELIST hImageList);
int GetIconIndex (LPSTR strFPath, int nType);
void FileListView_DoubleClick(HWND hwndLV);
void ListView_OnDispInfo(NMHDR *pNMHDR, LRESULT *pResult);
int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
BOOL AddItem(FileInfo* pFileInfo, int nPos);
void ResetFileList(HWND hwndLV);

// toolbar
HWND CreateToolbar(HWND hwndParent, int x, int y);
BOOL DoToolbarNotify(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL DrawViewsMenuItem(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL MeasurePopupMenuItem(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL DoToolbarBackBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL DoToolbarUpBtn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void EnableUpButton(BOOL bShow);
void EnableBackButton(BOOL bShow);
void NextView();

// back button stack operations
void InitializeBackStack();
BOOL PushBackStack(LPCSTR pszDirectory);
BOOL BackStackEmpty();
BOOL PopBackStack(LPSTR pszPathDir);

// shortcut bar
HICON GetLargeFolderIcon();
ATOM RegisterShortcutBar(HINSTANCE hInst);

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

	void SetLargeFolderIcon(HICON largeFolderIcon);

private:
	HWND _hwnd;
	int _btnHeight;
	HWND _hwndBtn;
	RECT _rect;
	HICON _largeFolderIcon;
	ShortcutBtn *_buttons;
	BOOL _bMouseIn;
	int _nItemCount;
	LPSHORTCUTBARITEMSTRUCT _shortcutItems[MAX_ITEMS];
};

