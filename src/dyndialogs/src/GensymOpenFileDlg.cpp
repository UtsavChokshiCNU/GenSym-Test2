#include "stdafx.h"
#include "FileOpenCommon.h"

//#include "CustCtrls32.h"

#define MAX_LOADSTRING 100

//#pragma comment(lib, "CustCtrls32.Lib")

// user-defined message
static UINT g_uFODRefreshMsgId = 0;

static LPOPENFILEDLGPRIVATE g_pFileOpenDlgPrivate;	// initialized by 'static' keyword
static FILEINFOS g_fileInfos;						// initialized by 'static' keyword

HWND g_hwndFileOpenDlg = NULL;						// file open dialog hwnd; not static since main prog uses this handle

static int CX_ICON = 0;
static int CY_ICON = 0;

static int SHORTCUT_CXICON = 0;
static int SHORTCUT_CYICON = 0;

static UINT g_uAddItemMsgId = 0;		// shortcut bar add item message id
static UINT g_uResetContentMsgId = 0;	// shortcut bar reset content message id

/////////////////////////////////////////////////////////////
// this starts it all
/////////////////////////////////////////////////////////////
HWND ChooseFile(LPCSTR directory, LPCSTR initialFileName, LPCSTR filter, LPBYTE pbShortcuts, int cbShortcuts, LPWSTR title, 
				HWND hwndOwner, BOOL mustExist)
{
	LPOPENFILEDLGINIT pOpenFileDlgInit = Initialize(directory, initialFileName, filter, pbShortcuts, cbShortcuts, title, hwndOwner, mustExist);
	
	g_hwndFileOpenDlg = CreateDialogParam(g_hInst, (LPCSTR)IDD_GENSYM_OPENFILE_DLG, hwndOwner, (DLGPROC)GensymFileOpenDlgProc, (LPARAM)pOpenFileDlgInit);
	
	if (g_hwndFileOpenDlg != NULL)
	{
		// set the initial file name if provided
		if (initialFileName != NULL)
		{
			UpdateFileName(g_hwndFileOpenDlg, initialFileName);
		}

		ShowWindow(g_hwndFileOpenDlg, SW_SHOW);
	}
	else
	{
		MessageBox(hwndOwner, "CreateDialog() returned NULL", "Warning", MB_OK | MB_ICONINFORMATION);
	}

	return g_hwndFileOpenDlg;
}

// general initialization tasks
LPOPENFILEDLGINIT Initialize(LPCSTR directory, LPCSTR initialFileName, LPCSTR filter, LPBYTE pbShortcuts, int cbShortcuts, 
							 LPWSTR title, HWND hwndOwner, BOOL mustExist)
{
	LPOPENFILEDLGINIT lpofdi = new OPENFILEDLGINIT;
	int nSize = sizeof(OPENFILEDLGINIT);

	InitFileOpenStruct(lpofdi, directory, initialFileName, filter, title, hwndOwner, mustExist);
	ParseShortcuts(lpofdi, pbShortcuts, cbShortcuts);

	return lpofdi;
}

void ParseShortcuts(LPOPENFILEDLGINIT lpofdi, LPBYTE pbShortcuts, int cbShortcuts)
{
	//ZeroMemory(lpofdi->_pszShortcuts, sizeof(lpofdi->_pszShortcuts));

	PBYTE ptr = NULL;
	int nCount = sizeof(pbShortcuts);
	int i = 0;
	int idx = 0;
	int nthString = 0;
	bool bLastCharNull = false;
	char szTemp[_MAX_PATH] = {0};

    while (true)
	{
		ptr = &(pbShortcuts[idx]);

		if (*ptr == '\0')
		{
			// is this our second null?
			if (bLastCharNull == true)
			{
				break;
			}

			// allocate and copy string to our global char* array
			lpofdi->_pszShortcuts[nthString] = new char [strlen(szTemp) + 1];
			strcpy(lpofdi->_pszShortcuts[nthString], szTemp);
			ZeroMemory(szTemp, _MAX_PATH);
			bLastCharNull = true;

			// advance to next string
			nthString++;

			// reset i
			i = 0;

		}
		else
		{
			szTemp[i] = *ptr;
			i++;
			if (bLastCharNull == true)
			{
				bLastCharNull = false;
			}
		}

		idx++;
	}
}

void InitFileOpenStruct(LPOPENFILEDLGINIT lpofdi, LPCSTR directory, LPCSTR initialFileName, LPCSTR filter, LPWSTR title, HWND hwndOwner, BOOL mustExist)
{
	// squirrel these away in our global FILEOPEN structure
	ZeroMemory((LPVOID)&(lpofdi->_fileOpen), sizeof(FILEOPEN));

	// initial directory
	lstrcpy((char*)lpofdi->_fileOpen.szDirectory, directory);

	// initial file name
	lstrcpy((char*)lpofdi->_fileOpen.szName, initialFileName);
	
	// filter
	lstrcpy((char*)lpofdi->_fileOpen.szFilter, filter);

	// title
	wcscpy((wchar_t*)lpofdi->_fileOpen.szTitle, title);	

	// hwndOwner
	lpofdi->_fileOpen.hwndOwner = hwndOwner;

	// must exist
	lpofdi->_fileOpen.bMustExist = mustExist;
}

void ChooseFileNotify(HWND hwndDialog, int code, LPSTR result)
{
	char szBuf[_MAX_PATH] = {0};

	if (code == IDCANCEL)
	{
		strcpy(szBuf, "User cancelled");
	}
	else
	{
		sprintf(szBuf, "User selected: %s", result);
	}

	MessageBox(NULL, szBuf, "File Open/Save Dialog", MB_OK);
}

int ListDirectoryAsync(LPCSTR directory, LPCSTR name, ListDirCallback callback, LPARAM lParam)
{
	// NOTES: name is NULL the first time in; in subsequent calls, 'name' contains the name of the folder that was clicked
	// in the dialog's file listview
	SYSTEMTIME sm;
	FILETIME ft;
	GetSystemTime(&sm);

	BOOL bRet = SystemTimeToFileTime(&sm, &ft);

	char szFullPath[MAX_PATH];
	ZeroMemory((LPVOID)szFullPath, MAX_PATH);

	lstrcpy(szFullPath, directory);
	if (name != NULL)
	{
		lstrcat(szFullPath, name);
	}

	// create a test array of FileInfo objects
/*	FileInfo fileInfos[] = 
	{
		{ 0, "chairs.doc", 30, ft},
		{ 0, "one.txt", 50, (ULONG)ft},
		{ 0, "two.pdf", 100, (ULONG)ft},
		{ 1, "Files", 0, (ULONG)ft},
		{ 1, "My Documents", 0, (ULONG)ft}
	};
*/

	FileInfo fileInfos[5] = {0};

	fileInfos[0].type = 0;
	fileInfos[0].name = "chairs.doc";
	fileInfos[0].size = 30;
	fileInfos[0].time = ft;

	fileInfos[1].type = 0;
	fileInfos[1].name = "one.txt";
	fileInfos[1].size = 50;
	fileInfos[1].time = ft;

	fileInfos[2].type = 0;
	fileInfos[2].name = "two.pdf";
	fileInfos[2].size = 100;
	fileInfos[2].time = ft;

	fileInfos[3].type = 1;
	fileInfos[3].name = "Files";
	fileInfos[3].size = 0;
	fileInfos[3].time = ft;

	fileInfos[4].type = 1;
	fileInfos[4].name = "My Documents";
	fileInfos[4].size = 0;
	fileInfos[4].time = ft;


	FileInfo fileInfosMyDocuments[4] = {0};
//	{
//		{ 0, "freddy.doc", 49, ft},
//		{ 0, "Report.doc", 99, ft},
//		{ 0, "Dell.doc", 103, ft},
//		{ 1, "My Projects", 0, ft}
//	};

	fileInfosMyDocuments[0].type = 0;
	fileInfosMyDocuments[0].name = "freddy.doc";
	fileInfosMyDocuments[0].size = 49;
	fileInfosMyDocuments[0].time = ft;

	fileInfosMyDocuments[1].type = 0;
	fileInfosMyDocuments[1].name = "Report.doc";
	fileInfosMyDocuments[1].size = 99;
	fileInfosMyDocuments[1].time = ft;

	fileInfosMyDocuments[2].type = 0;
	fileInfosMyDocuments[2].name = "Dell.doc";
	fileInfosMyDocuments[2].size = 103;
	fileInfosMyDocuments[2].time = ft;

	fileInfosMyDocuments[3].type = 1;
	fileInfosMyDocuments[3].name = "My Projects";
	fileInfosMyDocuments[3].size = 0;
	fileInfosMyDocuments[3].time = ft;


	FileInfo fileInfosMyProjects[4] = {0};
//	{
//		{ 0, "GensymTestHarness.sln", 49, ft},
//		{ 0, "GensymTextHarness.vcproj", 99, ft},
//		{ 0, "Toolbar.h", 103, ft},
//		{ 0, "ShortcutBar.h", 300, ft}
//	};

	fileInfosMyProjects[0].type = 0;
	fileInfosMyProjects[0].name = "GensymTestHarness.sln";
	fileInfosMyProjects[0].size = 49;
	fileInfosMyProjects[0].time = ft;

	fileInfosMyProjects[1].type = 0;
	fileInfosMyProjects[1].name = "GensymTextHarness.vcproj";
	fileInfosMyProjects[1].size = 99;
	fileInfosMyProjects[1].time = ft;

	fileInfosMyProjects[2].type = 0;
	fileInfosMyProjects[2].name = "Toolbar.h";
	fileInfosMyProjects[2].size = 103;
	fileInfosMyProjects[2].time = ft;

	fileInfosMyProjects[3].type = 0;
	fileInfosMyProjects[3].name = "ShortcutBar.h";
	fileInfosMyProjects[3].size = 300;
	fileInfosMyProjects[3].time = ft;


	// sleep to simulate a bit of delay
//	Sleep(500);

	if (strcmp(szFullPath, "Root\\My Documents") == 0)
	{
		callback(fileInfosMyDocuments, 4, 0);
	}
	else if (strcmp(szFullPath, "Root\\My Documents\\My Projects") == 0)
	{
		callback(fileInfosMyProjects, 4, 0);
	}
	else
	{
		callback(fileInfos, 5, 0);
	}

	return 0;
}

BOOL SetDirectory(LPOPENFILEDLGINIT lpofdi, LPCSTR szDirectory)
{
	ZeroMemory(lpofdi->_fileOpen.szDirectory, sizeof(lpofdi->_fileOpen.szDirectory));
	lstrcpy((char*)lpofdi->_fileOpen.szDirectory, szDirectory);

	return TRUE;
}

//BOOL SetDirectory(LPOPENFILEDLGINIT lpofdi, LPCSTR szDirectory)
//{
//	ZeroMemory(lpofdi->_fileOpen.szDirectory, sizeof(lpofdi->_fileOpen.szDirectory));
//	lstrcpy((char*)lpofdi->_fileOpen.szDirectory, szDirectory);
//
//	return TRUE;
//}

int SplitDirectoryFromPath(LPSTR szPathDir, LPSTR szPath, LPSTR szDirectory)
{
	char szBuf[_MAX_PATH];
	ZeroMemory((LPVOID)szBuf, _MAX_PATH);
	char szParentPath[_MAX_PATH];
	ZeroMemory((LPVOID)szParentPath, _MAX_PATH);
	ZeroMemory((LPVOID)szDirectory, _MAX_PATH);
	char *ptr;
	int ch = '\\';
	int nLen = 0;

	// make copy of szPathDir for us to work with
	lstrcpy(szBuf, szPathDir);

	// are we at the root directory?  If the first occurence of '\' is at the end of the string,
	// then it is the root directory
	nLen = strlen(szBuf);
	ptr = strchr(szBuf, ch);

	if (ptr != NULL)
	{
		if ((int)(ptr - szBuf + 1) == nLen)
		{
			// this is the root
			strcpy(szPath, szBuf);
			szDirectory[0] = '\0';
			return 0;
		}
	}
	else
	{
		return -1;
	}

	nLen = strlen(szBuf) - 1;		// we want to point to the last '\' so we're not adding 1 to strlen
	szBuf[nLen] = '\0';

	for (int i = (nLen - 1); i > -1; i--)
	{
		if (szBuf[i] == '\\')
		{
			// copy off directory
			lstrcpy(szDirectory, (LPCSTR)&szBuf[i+1]);
			// end the string preserving the last '\'
			szBuf[i+1] = '\0';

			break;
		}
	}

	lstrcpy(szPath, szBuf);

	return 1;
}

void GetCurrDir(LPSTR pszCurrDir, int cchBuffer)
{
	HWND hwndLookIn = GetDlgItem(g_hwndFileOpenDlg, IDC_LOOKIN_COMBO);
	int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);
	lstrcpy(pszCurrDir, (LPSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, nCurSel, 0));
}

// assume szPath has trailing '\'
BOOL RefreshFileList(LPCSTR szPath, LPCSTR szDirectory)
{
	// clean out the file listview
	ResetFileList(g_pFileOpenDlgPrivate->_hwndLV);

	// get new set of files
	ListDirectoryAsync(szPath, szDirectory, PopulateListDir, 0);

	// update our current directory global variable
//	SetDirectory(szPath);

	// populate Lookin with new directory
	HWND hwndLookin = GetDlgItem(g_hwndFileOpenDlg, IDC_LOOKIN_COMBO);

	// concatenate the path plus directory name
	char szPathDir[_MAX_PATH];
	ZeroMemory((LPVOID)szPathDir, _MAX_PATH);
	lstrcpy(szPathDir, szPath);
	lstrcat(szPathDir, szDirectory);

	PopulateLookInCombo(g_hwndFileOpenDlg, szPathDir);

	return TRUE;
}

LPSTR RemoveTrailingSlash(LPSTR szPathName)
{
	// TODO: possible one-byte memory leak here!!
	int n = strlen(szPathName);
	szPathName[n] = (char)'/0';

	return szPathName;
}

// list directory callback
void PopulateListDir(FileInfo *info, int count, LPARAM lParam)
{
	int i = 0;

	// save items and count in global variables

	// first, clean out the old
	CleanupFileInfos();

	// allocate new global fileInfos 
	g_fileInfos._fileInfos = new FileInfo[count];
	ZeroMemory((LPVOID)g_fileInfos._fileInfos, count*sizeof(FileInfo));

	g_fileInfos._count = count;

	// copy data
	for (i = 0; i < count; i++)
	{
		// copy size
		g_fileInfos._fileInfos[i].size = info[i].size;
		// allocate new string for file or folder name and copy
		g_fileInfos._fileInfos[i].name = new char[strlen(info[i].name) + 1];
		strcpy((char*)g_fileInfos._fileInfos[i].name, info[i].name);
		// timestampe
		g_fileInfos._fileInfos[i].time = info[i].time;
		// type, 1 = folder, 0 = other
		g_fileInfos._fileInfos[i].type = info[i].type;
	}

	// for each FileInfo, add it to the list view
	for (i = 0; i < count; i++)
	{
		AddItem(&(g_fileInfos._fileInfos[i]), i);
		//AddListDirItem(info[i], i);
	}
}

void CleanupFileInfos()
{
	if (g_fileInfos._fileInfos != NULL)
	{
		for (int i = 0; i < g_fileInfos._count; i++)
		{
			if (g_fileInfos._fileInfos[i].name != NULL)
			{
				delete [] (LPVOID)(g_fileInfos._fileInfos[i].name);
				g_fileInfos._fileInfos[i].name = NULL;
			}
		}

		delete g_fileInfos._fileInfos;

		g_fileInfos._fileInfos = NULL;
		g_fileInfos._count = 0;
	}
}

void AddListDirItem(FileInfo info, int i)
{
	AddFileListItem(g_pFileOpenDlgPrivate->_hwndLV, i, (LPTSTR)info.name, info.type, info.size);
}

LRESULT CALLBACK GensymFileOpenDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPMEASUREITEMSTRUCT lpmis = NULL;
	LPDRAWITEMSTRUCT lpdis = NULL;
	int iSelected = 0;
	LPSTR pszSelectedFileName = NULL;
	static RECT rectGrip;
	char szCurrDir[_MAX_PATH] = {0};
	char szSelectedFile[_MAX_PATH] = {0};
	char szPath[_MAX_PATH] = {0};

	//static HBRUSH hbrBackground;


	if (message == g_uFODRefreshMsgId)
	{
		// push the current directory onto the Back button stack
		GetCurrDir(szCurrDir, _MAX_PATH);
		PushBackStack(szCurrDir);

		// enable 'back' toolbar button
		EnableBackButton(TRUE);

		RefreshFileList((LPCSTR)lParam, (LPCSTR)wParam);


		return TRUE;		
	}

	switch (message)
	{		
	case WM_INITDIALOG:
		//hbrBackground = CreateSolidBrush(RGB(255, 10, 10));
		return (BOOL)HANDLE_WM_INITDIALOG(hDlg, wParam, lParam, GensymOpenFileDlg_OnInitDialog);

//	case WM_CTLCOLORDLG:
//		return (LONG)hbrBackground;

	case WM_NCHITTEST:
		return HANDLE_WM_NCHITTEST(hDlg, wParam, lParam, GensymOpenFileDlg_OnNcHitTest);

	case WM_PAINT:
		return (LRESULT)HANDLE_WM_PAINT(hDlg, wParam, lParam, GensymOpenFileDlg_OnPaint);

	// use to limit resizing
	case WM_GETMINMAXINFO:	
		return (BOOL)HANDLE_WM_GETMINMAXINFO(hDlg, wParam, lParam, GensymOpenFileDlg_OnGetMinMaxInfo);
		
	case WM_SIZE:
		return (LRESULT)HANDLE_WM_SIZE(hDlg, wParam, lParam, GensymOpenFileDlg_OnSize);

	case WM_NOTIFY:
		switch (LOWORD(wParam))
		{
		case ID_TOOLBAR:
			DoToolbarNotify(hDlg, message, wParam, lParam);
			break;

		case IDC_FILE_LIST:
			switch (((LPNMHDR) lParam)->code)
			{
				case NM_CLICK:
					pszSelectedFileName = FileListSelect(hDlg, g_pFileOpenDlgPrivate->_hwndLV);	
					if (pszSelectedFileName != NULL)
					{
						UpdateFileName(hDlg, pszSelectedFileName);

						delete [] pszSelectedFileName;	// we're done with it
					}
					break;

				case NM_DBLCLK:
					FileListView_DoubleClick(g_pFileOpenDlgPrivate->_hwndLV);
					break;

				case LVN_GETDISPINFO:
					ListView_OnDispInfo((LPNMHDR)lParam, NULL);
					break;

				case LVN_COLUMNCLICK:
					// TODO: change sort bitmap here
					// update the image for the column: ListView_SetColumn() & LVCFMT_IMAGE
					// 

					ListView_SortItems(g_pFileOpenDlgPrivate->_hwndLV, CompareProc, ((LPNMLISTVIEW)lParam)->iSubItem);
					if (g_pFileOpenDlgPrivate->_ColSort[((LPNMLISTVIEW)lParam)->iSubItem] == ASC)
					{
						g_pFileOpenDlgPrivate->_ColSort[((LPNMLISTVIEW)lParam)->iSubItem] = DESC;
					}
					else
					{
						g_pFileOpenDlgPrivate->_ColSort[((LPNMLISTVIEW)lParam)->iSubItem] = ASC;
					}
					
					break;
				default:
					break;
			}
			break;

		default:
			break;
		}

		break;

	case WM_MEASUREITEM:
		// sent by a menu
		MeasurePopupMenuItem(hDlg, wParam, lParam);

		break;

	case WM_DRAWITEM:
		DrawViewsMenuItem(hDlg, wParam, lParam);

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
			// get the selected file
			SendMessage(GetDlgItem(hDlg, IDC_FILENAME_COMBO), WM_GETTEXT, _MAX_PATH, (LPARAM)szSelectedFile);
			// get the selected file's path
			GetCurrDir(szCurrDir, _MAX_PATH);
			// concat
			strcpy(szPath, szCurrDir);
			strcat(szPath, szSelectedFile);

			// tell our caller what the user selected
			ChooseFileNotify(hDlg, IDOK, szPath);

			// we're closing
			DestroyWindow(hDlg);
			return TRUE;

		case IDCANCEL:
			// tell our caller the user canceled
			ChooseFileNotify(hDlg, IDCANCEL, NULL);

			// we're closing
			DestroyWindow(hDlg);
			return TRUE;

		case IDC_LOOKIN_COMBO:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				DoLookinComboSelChange(GetDlgItem(hDlg, IDC_LOOKIN_COMBO));
				break;
			//case CBN_SELENDOK:
			//	MessageBox(NULL, "CBN_SELENDOK", "", MB_OK);
			//	break;
			//case CBN_SELENDCANCEL:
			//	MessageBox(NULL, "CBN_SELENDCANCEL", "", MB_OK);
			//	break;
			default:
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
			NextView();
			break;
		case IDS_BACK:
			return DoToolbarBackBtn(hDlg, message, wParam, lParam);
//				break;
		case IDS_UP:
			DoToolbarUpBtn(hDlg, message, wParam, lParam);
			break;

		// process other menu commands
		default:
			break;
		}
		break;

	case WM_DESTROY:
		
		// free the bitmap resources (can this be done in Cleanup()?  check the timing...
		Cleanup();
		break;
	}
	return FALSE;
}

UINT
GensymOpenFileDlg_OnNcHitTest(HWND hwnd, int x, int y)
{
	RECT r;
	POINT pt;
	pt.x = x;
	pt.y = y;

	GetSizeGripRect(hwnd, &r);

	ClientToScreen(hwnd, (LPPOINT)&r.left);
	ClientToScreen(hwnd, (LPPOINT)&r.right);

	if (PtInRect(&r, pt)) {

		// since we're inside a dialog box procedure, we must
		// return the message result this-a-way
		SetWindowLong(hwnd, DWL_MSGRESULT, HTBOTTOMRIGHT);
		
		return HTBOTTOMRIGHT;
	}

	return 0;
}

void GetSizeGripRect(HWND hwnd, LPRECT lpRect)
{
	GetClientRect(hwnd, lpRect);
	lpRect->left = lpRect->right - ::GetSystemMetrics(SM_CXHSCROLL);
	lpRect->top = lpRect->bottom - ::GetSystemMetrics(SM_CYVSCROLL);
}

void GensymOpenFileDlg_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT rectGrip;
	RECT rectClient;

	if (state == SIZE_MINIMIZED)
	{
		return;
	}

	// get the previous grip position erased
	InvalidateRect(hwnd, &rectGrip, FALSE);

	// calculate the new position of the size grip
	rectGrip.right = cx;
	rectGrip.bottom = cy;
	rectGrip.top = rectGrip.bottom - GetSystemMetrics(SM_CYHSCROLL);
	rectGrip.left = rectGrip.right - GetSystemMetrics(SM_CXVSCROLL);

	// have the re-size grip repainted
	InvalidateRect(hwnd, &rectGrip, TRUE);

	// move the Open and Cancel buttons so they remain flush against the right
	// edge of the window

	HDWP hdwp = BeginDeferWindowPos(10);		// prevents flickering when moving controls

	MoveButton(hwnd, hdwp, IDOK, g_pFileOpenDlgPrivate->_openFileResize._szOpenBtnAnchor);
	MoveButton(hwnd, hdwp, IDCANCEL, g_pFileOpenDlgPrivate->_openFileResize._szCancelBtnAnchor);
	MoveListView(hwnd, hdwp, IDC_FILE_LIST, g_pFileOpenDlgPrivate->_openFileResize._szListViewBRAnchor);
	ResizeCombobox(hwnd, hdwp, IDC_LOOKIN_COMBO, g_pFileOpenDlgPrivate->_openFileResize._szFileLookinBRAnchor);
	MoveToolbar(hwnd, hdwp, g_pFileOpenDlgPrivate->_openFileResize._szToolbarBRAnchor);
	MoveCombobox(hwnd, hdwp, IDC_FILENAME_COMBO, g_pFileOpenDlgPrivate->_openFileResize._szFileNameBRAnchor);
	MoveCombobox(hwnd, hdwp, IDC_FILETYPES_COMBO, g_pFileOpenDlgPrivate->_openFileResize._szFileTypesBRAnchor);
	MoveStatic(hwnd, hdwp, IDC_STATIC1, g_pFileOpenDlgPrivate->_openFileResize._szFileNameStaticBRAnchor);
	MoveStatic(hwnd, hdwp, IDC_STATIC2, g_pFileOpenDlgPrivate->_openFileResize._szFileTypesStaticBRAnchor);
	ResizeShortcutBar(hwnd, hdwp);

	GetClientRect(hwnd, &rectClient);
	InvalidateRect(hwnd, &rectClient, TRUE);
	UpdateWindow(hwnd);

	EndDeferWindowPos(hdwp);

}

void MoveStatic(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight)
{
	RECT client;
	RECT r;

	GetClientRect(hwnd, &client);
	GetWindowRect(GetDlgItem(hwnd, id), &r);

	// convert the window coordinates of the listview to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);

	DeferWindowPos(hdwp,
				   GetDlgItem(hwnd, id), 
				   0, 
			       r.left,
				   client.bottom - szBottomRight.cy - (r.bottom - r.top),
				   r.right - r.left,
				   r.bottom - r.top,
				   SWP_NOZORDER);

/*	MoveWindow(GetDlgItem(hwnd, id),
		r.left,
		client.bottom - szBottomRight.cy - (r.bottom - r.top),
		r.right - r.left,
		r.bottom - r.top,
		TRUE);
*/
}

void MoveToolbar(HWND hwnd, HDWP hdwp, SIZE szToolbarPoints)
{
	RECT rectToolbar;
	RECT rectClient;

	int width = 0;

	if (g_pFileOpenDlgPrivate->_hwndToolbar != NULL)
	{
		// move in relation to client rect
		GetClientRect(hwnd, &rectClient);

//		SendMessage(g_pFileOpenDlgPrivate->_hwndToolbar, TB_AUTOSIZE, 0, 0);

		GetWindowRect(g_pFileOpenDlgPrivate->_hwndToolbar, &rectToolbar);
		ScreenToClient(hwnd, (LPPOINT)&rectToolbar.left);
		ScreenToClient(hwnd, (LPPOINT)&rectToolbar.right);

		width = rectToolbar.right - rectToolbar.left;

		DeferWindowPos(hdwp,
					   g_pFileOpenDlgPrivate->_hwndToolbar,
					   0,
					   rectClient.right - szToolbarPoints.cx - width, 
					   szToolbarPoints.cy,
					   width,
					   rectToolbar.bottom - rectToolbar.top,
					   SWP_NOZORDER);
/*
		MoveWindow(g_pFileOpenDlgPrivate->_hwndToolbar,
			rectLookin.right + szToolbarPoints.cx, 
			szToolbarPoints.cy,
			rectToolbar.right - rectToolbar.left,
			rectToolbar.bottom - rectToolbar.top,
			TRUE);
*/
	}
}

void MoveCombobox(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight)
{
	RECT client;
	RECT r;
	SIZE sz;

	GetClientRect(hwnd, &client);
	GetWindowRect(GetDlgItem(hwnd, id), &r);

	// convert the window coordinates of the listview to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);

	// new combobox width
	sz.cx = client.right - r.left - szBottomRight.cx;
	sz.cy = r.bottom - r.top;

	DeferWindowPos(hdwp,
		GetDlgItem(hwnd, id),
		0,
		r.left,
		client.bottom - szBottomRight.cy - sz.cy,
		sz.cx,
		sz.cy,
		SWP_NOZORDER);
/*
	MoveWindow(GetDlgItem(hwnd, id),
		r.left,
		client.bottom - szBottomRight.cy - sz.cy,
		sz.cx,
		sz.cy,
		TRUE);
*/
}

void ResizeCombobox(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight)
{
	RECT client;
	RECT r;
	SIZE sz;

	GetClientRect(hwnd, &client);
	GetWindowRect(GetDlgItem(hwnd, id), &r);

	// convert the window coordinates of the listview to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);

	// new combobox width
	sz.cx = client.right - r.left - szBottomRight.cx;
	sz.cy = r.bottom - r.top;

	DeferWindowPos(hdwp,
		GetDlgItem(hwnd, id),
		0,
		r.left,
		r.top,
		sz.cx,
		sz.cy,
		SWP_NOZORDER);
/*
	MoveWindow(GetDlgItem(hwnd, id),
		r.left,
		r.top,
		sz.cx,
		sz.cy,
		TRUE);
*/
}

void MoveListView(HWND hwnd, HDWP hdwp, UINT id, SIZE szBottomRight)
{
	RECT client;
	RECT r;
	SIZE sz;

	GetClientRect(hwnd, &client);
	GetWindowRect(GetDlgItem(hwnd, id), &r);

	// convert the window coordinates of the listview to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);

	// new listview width
	sz.cx = client.right - r.left - szBottomRight.cx;
	// new listview height
	sz.cy = client.bottom - r.top - szBottomRight.cy;

	DeferWindowPos(hdwp,
		GetDlgItem(hwnd, id),
		0,
		r.left,
		r.top,
		sz.cx,
		sz.cy,
		SWP_NOZORDER);
/*
	MoveWindow(GetDlgItem(hwnd, id),
		r.left,
		r.top,
		sz.cx,
		sz.cy,
		TRUE);
*/
}

void MoveButton(HWND hwnd, HDWP hdwp, UINT id, SIZE szBtnAnchor)
{
	RECT client;
	RECT r;
	SIZE sz;

	GetClientRect(hwnd, &client);
	GetWindowRect(GetDlgItem(hwnd, id), &r);

	// convert the window coordinates of the button to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);

	sz.cx = r.right - r.left;
	sz.cy = r.bottom - r.top;

	DeferWindowPos(hdwp,
		GetDlgItem(hwnd, id),
		0,
		client.right - szBtnAnchor.cx - sz.cx,
		client.bottom - szBtnAnchor.cy - sz.cy,
		sz.cx,
		sz.cy,
		SWP_NOZORDER);
/*
	MoveWindow(GetDlgItem(hwnd, id),
		client.right - szBtnAnchor.cx - sz.cx,
		client.bottom - szBtnAnchor.cy - sz.cy,
		sz.cx,
		sz.cy,
		TRUE);
*/
}

void ResizeShortcutBar(HWND hwnd, HDWP hdwp)
{
	RECT client;
	RECT r;
	SIZE sz;

	GetClientRect(hwnd, &client);
	GetWindowRect(g_pFileOpenDlgPrivate->_hwndShortcutBar, &r);

	// convert to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);

	sz.cx = r.right - r.left;
	sz.cy = client.bottom - r.top - 2;

	DeferWindowPos(hdwp,
		g_pFileOpenDlgPrivate->_hwndShortcutBar,
		0,
		r.left,
		r.top,
		sz.cx,
		sz.cy,
		SWP_NOZORDER);
/*
	MoveWindow(g_pFileOpenDlgPrivate->_hwndShortcutBar,
		r.left,
		r.top,
		sz.cx,
		sz.cy,
		TRUE);
*/
}

void GensymOpenFileDlg_OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hwnd, &ps);

	// calc the position of the size grip
	RECT r;
	GetClientRect(hwnd, &r);
	r.top = r.bottom - GetSystemMetrics(SM_CYHSCROLL);
	r.left = r.right - GetSystemMetrics(SM_CXVSCROLL);

	// draw the grip
	DrawFrameControl(hdc, &r, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);

	EndPaint(hwnd, &ps);
}

HMENU CreatePopupMenuItems(HWND hwnd)
{
	HMENU hmenu = CreatePopupMenu();
	//HMENU hmenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_POPUP));
	char szLargeIcons[] = "Large Icons";
	char szSmallIcons[] = "Small Icons";
	char szList[] = "List";
	char szDetails[] = "Details";
	
	// TODO: de-allocate these strings
	LPVIEWSMENUITEM vmi[4];
	memset(vmi, 0, sizeof(vmi));

	//vmi[0] = new VIEWSMENUITEM;
	vmi[0] = (LPVIEWSMENUITEM) LocalAlloc(LMEM_FIXED, sizeof(VIEWSMENUITEM));
	memset(vmi[0], 0, sizeof(vmi));
	vmi[0]->nCmdId = IDM_VIEW_LARGEICONS;
	vmi[0]->pszText = new char[strlen(szLargeIcons) + 1];
	memset(vmi[0]->pszText, 0, strlen(szLargeIcons) + 1);
	strcpy(vmi[0]->pszText, szLargeIcons);

	vmi[1] = (LPVIEWSMENUITEM) LocalAlloc(LMEM_FIXED, sizeof(VIEWSMENUITEM));
	//vmi[1] = new VIEWSMENUITEM;
	memset(vmi[1], 0, sizeof(vmi));
	vmi[1]->nCmdId = IDM_VIEW_SMALLICONS;
	vmi[1]->pszText = new char[strlen(szSmallIcons) + 1];
	memset(vmi[1]->pszText, 0, strlen(szSmallIcons) + 1);
	strcpy(vmi[1]->pszText, szSmallIcons);

	vmi[2] = (LPVIEWSMENUITEM) LocalAlloc(LMEM_FIXED, sizeof(VIEWSMENUITEM));
	//vmi[2] = new VIEWSMENUITEM;
	memset(vmi[2], 0, sizeof(vmi));
	vmi[2]->nCmdId = IDM_VIEW_LIST;
	vmi[2]->pszText = new char[strlen(szList) + 1];
	memset(vmi[2]->pszText, 0, strlen(szList) + 1);
	strcpy(vmi[2]->pszText, szList);

	vmi[3] = (LPVIEWSMENUITEM) LocalAlloc(LMEM_FIXED, sizeof(VIEWSMENUITEM));
	//vmi[3] = new VIEWSMENUITEM;
	memset(vmi[3], 0, sizeof(vmi));
	vmi[3]->nCmdId = IDM_VIEW_DETAILS;
	vmi[3]->pszText = new char[strlen(szDetails) + 1];
	memset(vmi[3]->pszText, 0, strlen(szDetails) + 1);
	strcpy(vmi[3]->pszText, szDetails);

	AppendMenu(hmenu, MF_BYCOMMAND | MF_OWNERDRAW, IDM_VIEW_LARGEICONS, (LPCTSTR)vmi[0]);
	AppendMenu(hmenu, MF_BYCOMMAND | MF_OWNERDRAW, IDM_VIEW_SMALLICONS, (LPCTSTR)vmi[1]);
	AppendMenu(hmenu, MF_BYCOMMAND | MF_OWNERDRAW, IDM_VIEW_LIST, (LPCTSTR)vmi[2]);
	AppendMenu(hmenu, MF_BYCOMMAND | MF_OWNERDRAW, IDM_VIEW_DETAILS, (LPCTSTR)vmi[3]);

	DrawMenuBar(hwnd);

	return hmenu;
}

void Cleanup()
{
	// cleanup after our views popup menu
	LPVIEWSMENUITEM pvmi;
	MENUITEMINFO mii;
	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);
	HMENU hmenuPopup = NULL;
	int nRet = 0;

	if (g_pFileOpenDlgPrivate->_hViewsMenu != NULL)
	{
		for (int i = IDM_VIEW_LARGEICONS; i <= IDM_VIEW_DETAILS; i++)
		{
			mii.fMask = MIIM_DATA | MIIM_ID | MIIM_STATE;

			nRet = GetMenuItemInfo(g_pFileOpenDlgPrivate->_hViewsMenu, i, FALSE, &mii);
			if (nRet == 0)
			{
				break;
			}
			pvmi = (LPVIEWSMENUITEM) mii.dwItemData;

			// free text memory
			delete [] pvmi->pszText;
			// free item structure
			//delete pvmi;
			LocalFree(pvmi);
		}

		DestroyMenu(g_pFileOpenDlgPrivate->_hViewsMenu);
		g_pFileOpenDlgPrivate->_hViewsMenu = NULL;
	}

	// image lists cleanup
	ImageList_Destroy(g_pFileOpenDlgPrivate->_hilViews);

	// toolbar cleanup
	
	g_pFileOpenDlgPrivate->_hilViews = NULL;

	g_hwndFileOpenDlg = NULL;

	// back STACK global
	for (int i = 0; i < g_pFileOpenDlgPrivate->_pbackStack->top; i++)
	{
		delete [] g_pFileOpenDlgPrivate->_pbackStack->pszFolders[i];
		g_pFileOpenDlgPrivate->_pbackStack->pszFolders[i] = NULL;
	}

	if (g_pFileOpenDlgPrivate->_pbackStack != NULL)
	{
		delete g_pFileOpenDlgPrivate->_pbackStack;
	}

	CleanupFileInfos();

	// our private structure
	if (g_pFileOpenDlgPrivate != NULL)
	{
		delete g_pFileOpenDlgPrivate;
		g_pFileOpenDlgPrivate = NULL;
	}
}

static void GensymOpenFileDlg_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO mmi)
{
	POINT limit;

	// don't want the window to be any narrower than the shortcut bar plus 
	// the file listview, and any shorter than the lookin combobox plus
	// the file listview plus the file name and files of type comboboxes
	// see page 788 of Rector & Newcomer for sample
	limit.x = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right;
	limit.y = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom;

	limit.y += 2 * GetSystemMetrics(SM_CYBORDER) + 
		GetSystemMetrics(SM_CYCAPTION) +
		2 * GetSystemMetrics(SM_CYFRAME);

	mmi->ptMinTrackSize = limit;
}

static BOOL GensymOpenFileDlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	LPOPENFILEDLGINIT lpofdi = LPOPENFILEDLGINIT(lParam);

	// register user message with Windows
	g_uFODRefreshMsgId = RegisterWindowMessage(FOD_REFRESH_MSG_STR);

	// allocate our private structure
	g_pFileOpenDlgPrivate = new OPENFILEDLGPRIVATE;
	ZeroMemory(g_pFileOpenDlgPrivate, sizeof(OPENFILEDLGPRIVATE));

	int nSize = sizeof(OPENFILEDLGPRIVATE);

	// initialize column sort flags
	g_pFileOpenDlgPrivate->_ColSort[0] = ASC;
	g_pFileOpenDlgPrivate->_ColSort[1] = ASC;
	g_pFileOpenDlgPrivate->_ColSort[2] = ASC;
	g_pFileOpenDlgPrivate->_ColSort[3] = ASC;

/////////////////////////////////////////////////////////////////////
// are we save or open file dialog
/////////////////////////////////////////////////////////////////////
	HWND hwndOKBtn = GetDlgItem(hwnd, IDOK);
	if (lpofdi->_fileOpen.bMustExist == TRUE)
	{
		// 'Save'
		SendMessage(hwndOKBtn, WM_SETTEXT, 0, (LPARAM)"&Save");
	}

	// convert title to MBCS
	int nLen = WideCharToMultiByte(CP_ACP, 0, lpofdi->_fileOpen.szTitle, -1, NULL, NULL, NULL, NULL);
	char *pszTitle = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, lpofdi->_fileOpen.szTitle, -1, pszTitle, nLen, NULL, NULL);

	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)pszTitle);

	delete [] pszTitle;
	pszTitle = NULL;

	// default is 'Open'

/////////////////////////////////////////////////////////////////////
// toolbar
/////////////////////////////////////////////////////////////////////
	g_pFileOpenDlgPrivate->_hwndToolbar = CreateToolbar(hwnd, 300, 18);

	// initialize the back button stack
	InitializeBackStack();

	// create the views toolbar button dropdown menu
	g_pFileOpenDlgPrivate->_hViewsMenu = CreatePopupMenuItems(hwnd);
	
	// set views image list
	SetViewsImageList(g_pFileOpenDlgPrivate->_hilViews);

/////////////////////////////////////////////////////////////////////
// listview
/////////////////////////////////////////////////////////////////////
	// set the list view global hwnd
	g_pFileOpenDlgPrivate->_hwndLV = GetDlgItem(hwnd, IDC_FILE_LIST);

	// set file list view image list
	SetListViewImageList(g_pFileOpenDlgPrivate->_hwndLV, g_pFileOpenDlgPrivate->_hImageListSmall, g_pFileOpenDlgPrivate->_hImageListLarge);

	// add listview columns
	AddColumns(g_pFileOpenDlgPrivate->_hwndLV);

	// retrieve the file info structures from the application
	ListDirectoryAsync(lpofdi->_fileOpen.szDirectory, NULL, PopulateListDir, 0); //lParam);

	PopulateFileTypes(hwnd, lpofdi->_fileOpen.szFilter);
	PopulateLookInCombo(hwnd, lpofdi->_fileOpen.szDirectory);

////////////////////////////////////////////////////////////////////////////////
//	Create the ShortcutBar, placing it even with the top of the file listview
////////////////////////////////////////////////////////////////////////////////
	// 0. register the shortcut bar
	RegisterShortcutBar(g_hInst);

    // 1. get the position and bounding rectangle of the file listview
	RECT rc;
	HWND hwndFileList = GetDlgItem(hwnd, IDC_FILE_LIST);
	GetWindowRect(hwndFileList, &rc);
	// convert to dialog's coordinates
	ScreenToClient(hwnd, LPPOINT(&rc.left));
	ScreenToClient(hwnd, LPPOINT(&rc.right));

	// 2. calculate the width and height of the ShortcutBar
	RECT dlgRect;
	// get the client rectangle of the dialog
	GetClientRect(hwnd, &dlgRect);
	// hard-coded width for now
	int width = 80; //(rect.right - rect.left) / 3;
	// height is from the top of the file listview to the bottom of the dialog
	int height = dlgRect.bottom - rc.top; 
	POINT origin;
	origin.x = dlgRect.left;
	origin.y = dlgRect.top;

	// 3. create ShortcutBar and position even with the top of file listview
	g_pFileOpenDlgPrivate->_hwndShortcutBar = CreateWindowEx(
		WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE, 
		SHORTCUTBARCLASS, 
		"ShortcutBar", 
		WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CS_VREDRAW | CS_HREDRAW,  
		origin.x + 2, 
		rc.top,  
		width, 
		height - 2, 
		hwnd, 
		NULL, 
		NULL, 
		NULL);
 
	// get our items we saved earlier
	char szPath[_MAX_PATH] = {0};
	char szDir[_MAX_PATH] = {0};
	int nRet = 0;

	SHORTCUTBARITEMSTRUCT sbis;
	ZeroMemory((LPVOID)&sbis, sizeof(SHORTCUTBARITEMSTRUCT));
	sbis.cbSize = sizeof(SHORTCUTBARITEMSTRUCT);
	sbis.iBitmap = 0;

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (lpofdi->_pszShortcuts[i] == NULL)
		{
			break;
		}

		
		if ((nRet = SplitDirectoryFromPath(lpofdi->_pszShortcuts[i], szPath, szDir)) > -1)
		{
			strcpy(sbis.szPath, szPath);
			strcpy(sbis.szDir, szDir);
			SendMessage(g_pFileOpenDlgPrivate->_hwndShortcutBar, g_uAddItemMsgId, 0, (LPARAM)&sbis);

			// we're done with this
			delete [] lpofdi->_pszShortcuts[i];
		}
	}

	CleanupFileOpenDlgInitStruct(lpofdi);

	// once all child controls have been created, set our anchors for resizing
	SetChildControlRects(hwnd);

	return TRUE;
}

void CleanupFileOpenDlgInitStruct(LPOPENFILEDLGINIT lpofdi)
{
	delete lpofdi;
	lpofdi = NULL;
}

// save off child control window rects for resizing
void SetChildControlRects(HWND hwnd)
{
	RECT rectClient;
	RECT r;

	// set the minimum size
	GetWindowRect(hwnd, &(g_pFileOpenDlgPrivate->_openFileResize._rectMinSize));

	// save various window coordinates for resizing
	GetClientRect(hwnd, &rectClient);
//	ScreenToClient(hwnd, (LPPOINT)&rectClient.left);
//	ScreenToClient(hwnd, (LPPOINT)&rectClient.right);

	// right, bottom Cancel button anchor
	GetWindowRect(GetDlgItem(hwnd, IDCANCEL), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szCancelBtnAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szCancelBtnAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// right, bottom Open button anchor
	GetWindowRect(GetDlgItem(hwnd, IDOK), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szOpenBtnAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szOpenBtnAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// right, bottom File listview anchor
	GetWindowRect(GetDlgItem(hwnd, IDC_FILE_LIST), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szListViewBRAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szListViewBRAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// right, bottom Lookin combobox anchor
	GetWindowRect(GetDlgItem(hwnd, IDC_LOOKIN_COMBO), &r);
    g_pFileOpenDlgPrivate->_openFileResize._szFileLookinBRAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szFileLookinBRAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;
	int lookinComboRight = r.right;

	// right, bottom File Name combobox anchor
	GetWindowRect(GetDlgItem(hwnd, IDC_FILENAME_COMBO), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szFileNameBRAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szFileNameBRAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// right, bottom File Types combobox anchor
	GetWindowRect(GetDlgItem(hwnd, IDC_FILETYPES_COMBO), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szFileTypesBRAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szFileTypesBRAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// right, bottom File Name static text
	GetWindowRect(GetDlgItem(hwnd, IDC_STATIC1), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szFileNameStaticBRAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szFileNameStaticBRAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// right, bottom File Name static text
	GetWindowRect(GetDlgItem(hwnd, IDC_STATIC2), &r);
	g_pFileOpenDlgPrivate->_openFileResize._szFileTypesStaticBRAnchor.cx = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right;
	g_pFileOpenDlgPrivate->_openFileResize._szFileTypesStaticBRAnchor.cy = g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.bottom - r.bottom;

	// convert to client coordinates
	ScreenToClient(hwnd, (LPPOINT)&g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.left);
	ScreenToClient(hwnd, (LPPOINT)&g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right);

	// right, top toolbar anchor
	GetWindowRect(g_pFileOpenDlgPrivate->_hwndToolbar, &r);
	ScreenToClient(hwnd, (LPPOINT)&r.left);
	ScreenToClient(hwnd, (LPPOINT)&r.right);
	g_pFileOpenDlgPrivate->_openFileResize._szToolbarBRAnchor.cx = 
		(g_pFileOpenDlgPrivate->_openFileResize._rectMinSize.right - r.right);
	g_pFileOpenDlgPrivate->_openFileResize._szToolbarBRAnchor.cy = r.top;

}

void SetViewsImageList(HIMAGELIST &hilViews)
{
	HBITMAP hbmp = NULL;

	hilViews = ImageList_Create(16, 16, ILC_COLOR, 5, 0);

	// load the bitmap resources and add them to the image list
	hbmp = (HBITMAP) LoadImage(g_hInst, MAKEINTRESOURCE(IDB_VIEWS_BITMAP), IMAGE_BITMAP, 0, 0, LR_LOADTRANSPARENT | LR_DEFAULTSIZE); 
	int nRet = ImageList_Add(hilViews, hbmp, NULL);
}

void SetListViewImageList(HWND hwndLV, HIMAGELIST &hilSmall, HIMAGELIST &hilLarge)
{
	// Retrieve the system image list
	GetSystemImageLists(hilSmall, hilLarge);

	if (hilSmall)
	{
		ListView_SetImageList(hwndLV, hilSmall, LVSIL_SMALL);
	}

	if (hilLarge)
	{
		ListView_SetImageList(hwndLV, hilLarge, LVSIL_NORMAL);
	}
}

void GetSystemImageLists(HIMAGELIST &hilSmall, HIMAGELIST &hilLarge)
{
	//ASSERT(hilSmall == NULL);
	//ASSERT(hilLarge == NULL);

	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	char lpBuf[MAX_PATH];
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

void AddColumns(HWND hwnd)
{
	// to use triangles
	//col.fmt &= ~(LVCFMT_IMAGE | LVCFMT_BITMAP_ON_RIGHT);
	//rc = ListView_SetColumn(m_hWnd, iSortCol, &col);

	// name
	LV_COLUMN lvCol = {0};
	lvCol.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_FMT|LVCF_SUBITEM;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.pszText = "Name";
	lvCol.cx = 150;
	lvCol.iSubItem = 0;
	ListView_InsertColumn(hwnd, 0, &lvCol);

	// type
	lvCol.pszText = "Type";
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 50;
	lvCol.iSubItem = 1;
	ListView_InsertColumn(hwnd, 1, &lvCol);

	// size
	lvCol.pszText = "Size";
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 100;
	lvCol.iSubItem = 2;
	ListView_InsertColumn(hwnd, 2, &lvCol);

	// date
	lvCol.pszText = "Date";
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 50;
	lvCol.iSubItem = 3;
	ListView_InsertColumn(hwnd, 3, &lvCol);

	ListView_SetExtendedListViewStyle(hwnd, (LVS_SHAREIMAGELISTS | LVS_AUTOARRANGE) & (LVS_EX_TWOCLICKACTIVATE) );
}

BOOL PopulateFileTypes(HWND hdlg, LPCSTR pszFilter)
{
	HWND hwndFileTypes = GetDlgItem(hdlg, IDC_FILETYPES_COMBO);

	// clear
	SendMessage(hwndFileTypes, CB_RESETCONTENT, 0, 0);

	// populate
	SendMessage(hwndFileTypes, CB_ADDSTRING, 0, (LPARAM) (LPCSTR) pszFilter);
	// default selection
	SendMessage(hwndFileTypes, CB_SETCURSEL, 0, 0);

	return TRUE;
}

BOOL UpdateFileName(HWND hdlg, LPCSTR pszFileName)
{
	HWND hwndFileName = GetDlgItem(hdlg, IDC_FILENAME_COMBO);

	// TODO: just clear the edit box
	// What about a history list?
	// clear
	SendMessage(hwndFileName, CB_RESETCONTENT, 0, 0);

	// populate
	SendMessage(hwndFileName, CB_ADDSTRING, 0, (LPARAM) (LPCSTR) pszFileName);
	// default selection
	SendMessage(hwndFileName, CB_SETCURSEL, 0, 0);

	return TRUE;
}

HICON GetFolderIconHandle()
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	DWORD_PTR pdw = SHGetFileInfo (
		"dummy", 
		FILE_ATTRIBUTE_DIRECTORY, 
		&sfi, 
		sizeof(sfi), 
		SHGFI_SMALLICON | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES
	);
	
	CX_ICON = ::GetSystemMetrics(SM_CXICON);
	CY_ICON = ::GetSystemMetrics(SM_CXICON);
	
	// for COMBOBOXEX
	g_pFileOpenDlgPrivate->_hilLookin = ImageList_Create(16, 16, ILC_COLOR, 1, 0);
	ImageList_AddIcon(g_pFileOpenDlgPrivate->_hilLookin, sfi.hIcon);

	return sfi.hIcon;
}

void SetView(DWORD dwViewStyle)
{
	SetWindowLong(g_pFileOpenDlgPrivate->_hwndLV, GWL_STYLE, (GetWindowLong(g_pFileOpenDlgPrivate->_hwndLV, GWL_STYLE) &~LVS_TYPEMASK) | dwViewStyle);
}

void NextView()
{
	DWORD dwStyle = GetWindowLong(g_pFileOpenDlgPrivate->_hwndLV, GWL_STYLE) & LVS_TYPEMASK;
	DWORD dwNextStyle = 0;

	switch(dwStyle)
	{
	case LVS_ICON:
		dwNextStyle = LVS_SMALLICON;
		break;
	case LVS_SMALLICON:
		dwNextStyle = LVS_LIST;
		break;
	case LVS_LIST:
		dwNextStyle = LVS_REPORT;
		break;
	case LVS_REPORT:
		dwNextStyle = LVS_ICON;
		break;
	}

	SetView(dwNextStyle);
}

///////////////////////////////////////////////////////////////
// Populates the Look in: combobox.
//
// Input:
//		HWND hdlg - handle to the dialog window
//		LPCSTR pszPathDir - this is the full path string
//			e.g. 'My Documents\My Projects\'
///////////////////////////////////////////////////////////////
BOOL PopulateLookInCombo(HWND hdlg, LPCSTR pszPathDir)
{
	int nSel = -1;			// used for combobox selection index
	char *token = NULL;
	char seps[] = "\\";
	char *pszParentPath = new char[_MAX_PATH];	
	ZeroMemory((LPVOID)pszParentPath, _MAX_PATH);
	LONG lResult = 0;

	COMBOBOXEXITEM cbei;
	ZeroMemory((LPVOID)&cbei, sizeof(cbei));
	int iCnt = 0;

	// the text, indent, image, and lparam fields are valid
	cbei.mask = CBEIF_TEXT | CBEIF_INDENT | CBEIF_IMAGE | CBEIF_LPARAM | CBEIF_SELECTEDIMAGE;
	// always add to the end
	cbei.iItem = -1;
	// these are always going to be the same
	cbei.iImage = 4;	// TODO: '4' is the folder icon - need to find out where this is defined and use the #define value
	cbei.iSelectedImage = 4;

	// copy off pszPathDir for us to mangle with strtok
	char *pszPathDirCopy = new char[strlen(pszPathDir) + 1];
	ZeroMemory((LPVOID)pszPathDirCopy, strlen(pszPathDir) + 1);
	lstrcpy(pszPathDirCopy, pszPathDir);

	// get the handle to the Look in: combobox
	HWND hwndLookIn = GetDlgItem(hdlg, IDC_LOOKIN_COMBO);

	// clear
	ResetLookinCombobox(hwndLookIn);

	// parse to acquire each containing folder name to display in the combobox
	token = strtok(pszPathDirCopy, seps);
	strcpy(pszParentPath, token);
	strcat(pszParentPath, "\\");

	while (token != NULL)
	{
		// add string
		cbei.pszText = token;
		//lResult = SendMessage(hwndLookIn, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)token);

		// set item data to our accumulated path
		char *szBuf = new char[strlen(pszParentPath) + 1];
		strcpy(szBuf, pszParentPath);
		cbei.lParam = (LPARAM)szBuf;
		//SendMessage(hwndLookIn, CB_SETITEMDATA, lResult, (LPARAM)(DWORD)szBuf);
		nSel++;

		token = strtok(NULL, seps);
		if (token != NULL)
		{
			// append to accumulated path
			strcat(pszParentPath, token);
			strcat(pszParentPath, "\\");
		}

		// indentation
		cbei.iIndent = iCnt;

		if (SendMessage(hwndLookIn, CBEM_INSERTITEM, 0, (LPARAM)&cbei) == -1)
		{
			return FALSE;
		}

		iCnt++;
	}

	// assign existing image list to the comboboxex control
	SendMessage(hwndLookIn, CBEM_SETIMAGELIST, 0, (LPARAM)g_pFileOpenDlgPrivate->_hImageListSmall);

	// we're done with this
	delete [] pszPathDirCopy;
	pszPathDirCopy = NULL;

	// default selection
	SendMessage(hwndLookIn, CB_SETCURSEL, nSel, 0);
	// save current selection itemdata to global; used for BACK functionality
	lstrcpy(g_pFileOpenDlgPrivate->_szCurrLookinData, (LPSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, (WPARAM) nSel, 0));

	if (iCnt < 2)
	{
		EnableUpButton(FALSE);
	}
	else
	{
		EnableUpButton(TRUE);
	}

	UpdateWindow(hwndLookIn);

	return TRUE;
}

//BOOL PopulateLookInCombo(HWND hdlg, LPCSTR pszPathDir)
//{
//	int nSel = -1;			// used for combobox selection index
//	char *token = NULL;
//	char seps[] = "\\";
//	char *pszParentPath = new char[_MAX_PATH];	
//	ZeroMemory((LPVOID)pszParentPath, _MAX_PATH);
//	LONG lResult = 0;
//
//	// copy off pszPathDir for us to mangle with strtok
//	char *pszPathDirCopy = new char[strlen(pszPathDir) + 1];
//	ZeroMemory((LPVOID)pszPathDirCopy, strlen(pszPathDir) + 1);
//	lstrcpy(pszPathDirCopy, pszPathDir);
//
//	// get the handle to the Look in: combobox
//	HWND hwndLookIn = GetDlgItem(hdlg, IDC_LOOKIN_COMBO);
//
//	// clear
//	ResetLookinCombobox(hwndLookIn);
//
//	// parse to acquire each containing folder name to display in the combobox
//	token = strtok(pszPathDirCopy, seps);
//	strcpy(pszParentPath, token);
//	strcat(pszParentPath, "\\");
//
//	while (token != NULL)
//	{
//		// add string
//		lResult = SendMessage(hwndLookIn, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)token);
//
//		// set item data to our accumulated path
//		char *szBuf = new char[strlen(pszParentPath) + 1];
//		strcpy(szBuf, pszParentPath);
//		SendMessage(hwndLookIn, CB_SETITEMDATA, lResult, (LPARAM)(DWORD)szBuf);
//		nSel++;
//
//		token = strtok(NULL, seps);
//		if (token != NULL)
//		{
//			// append to accumulated path
//			strcat(pszParentPath, token);
//			strcat(pszParentPath, "\\");
//		}
//	}
//
//	// we're done with this
//	delete [] pszPathDirCopy;
//	pszPathDirCopy = NULL;
//
//	// default selection
//	SendMessage(hwndLookIn, CB_SETCURSEL, nSel, 0);
//
//	UpdateWindow(hwndLookIn);
//
//	return TRUE;
//}

void ResetLookinCombobox(HWND hwndLookIn)
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

void DoLookinComboSelChange(HWND hwndLookIn)
{
	char szPathDir[_MAX_PATH];
	ZeroMemory((LPVOID)szPathDir, _MAX_PATH);
	char szPath[_MAX_PATH];
	ZeroMemory((LPVOID)szPath, _MAX_PATH);
	char szDir[_MAX_PATH];
	ZeroMemory((LPVOID)szDir, _MAX_PATH);
	int ch = '\\';
	int nLen = 0;

	// get the index of the current selection
	int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);

	// get the associated itemdata
	lstrcpy(szPathDir, (LPSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, nCurSel, 0));

	if (SplitDirectoryFromPath(szPathDir, szPath, szDir) < 0)
	{
		return;
	}
	else
	{
		if (strlen(g_pFileOpenDlgPrivate->_szCurrLookinData) > 0)
		{
			// push previous selection onto BACK stack
			PushBackStack(g_pFileOpenDlgPrivate->_szCurrLookinData);
			// update current selection global
			lstrcpy(g_pFileOpenDlgPrivate->_szCurrLookinData, szPathDir);
		}

        RefreshFileList(szPath, szDir);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File Listview
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPSTR FileListSelect(HWND hDlg, HWND hwndLV)
{
	char *pszText = new char[255];
	memset(pszText, 0, sizeof(pszText) + 1);
	FileInfo* pFileInfo = NULL;

	int iSelected = SendMessage(hwndLV, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

	if (iSelected == -1)
	{
		return NULL;
	}

	LVITEM lvi;
	memset(&lvi, 0, sizeof(lvi));

	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iSubItem = 0;
	lvi.pszText = pszText;
	lvi.cchTextMax = 256;
	lvi.iItem = iSelected;

	ListView_GetItem(hwndLV, &lvi);

	pFileInfo = (FileInfo*)lvi.lParam;
	if (pFileInfo->type == 1)
	{
		// it's a folder, so return NULL
		return NULL;
	}
	else
	{
		return pszText;
	}
}

void AddFileListItem(HWND hwnd, INT nItem, LPCSTR pszName, int nType, INT nSize)
{
	LVITEM lvi;
	TCHAR szType[20] = {0};

	// fill in the first column
	lvi.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.pszText = (LPSTR)pszName;
	lvi.lParam = nType;
	lvi.iImage = GetIconIndex((LPSTR)pszName, nType);
	ListView_InsertItem(hwnd, &lvi);

	// subitem 1 - type
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 1;
	lvi.pszText = GetTypeName((LPSTR)pszName);
	BOOL bSent = ListView_SetItem(hwnd, &lvi);

	// subitem 2 - size
	if (nSize != 0)
	{
		// convert to string
		char szSize[10];
		ZeroMemory((LPVOID)szSize, 10);
		_itoa(nSize, szSize, 10);

		lvi.mask = LVIF_TEXT;
		lvi.iSubItem = 2;

		lvi.pszText = szSize;
		bSent = ListView_SetItem(hwnd, &lvi);
	}
}

int GetIconIndex (LPSTR strFPath, int nType)
{
	static int _nDirIconIdx = -1;
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	if (nType == 1)	// it's a directory
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

void SetImageList(HWND hdlg, HWND hwndLV, HIMAGELIST hImageList)
{	
	ListView_SetImageList(hwndLV, hImageList, LVSIL_SMALL);
}

TCHAR* GetTypeName (LPSTR strFPath)
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	static TCHAR lpBuff[MAX_PATH];
	lpBuff[0] = TCHAR ('\0');

	SHGetFileInfo (
		strFPath, 
		0, 
		&sfi, 
		sizeof(sfi), 
		SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES
	);

	lstrcpy(lpBuff, sfi.szTypeName);
	if (lpBuff[0] == TCHAR('\0'))
	{
		//int nDotIdx = strFPath.ReverseFind (TCHAR('.'));
		//int nBSIdx = strFPath.ReverseFind (TCHAR('\\'));
		//if (nDotIdx > nBSIdx)
		//{
		//	strFPath = strFPath.Mid(nDotIdx+1);
		//	strFPath.MakeUpper();
		//	lstrcpy (lpBuff, strFPath + TCHAR (' '));
		//}

		lstrcat (lpBuff, _T("File"));
	}

	return lpBuff;
}

void ResetFileList(HWND hwndLV)
{
	ListView_DeleteAllItems(hwndLV);
}

void FileListView_DoubleClick(HWND hwndLV)
{
	BOOL bRet = FALSE;
	HWND hwndLookIn;
	char szParentPath[_MAX_PATH];
	ZeroMemory((LPVOID)szParentPath, _MAX_PATH);
	char szDirectory[_MAX_PATH];
	ZeroMemory((LPVOID)szDirectory, _MAX_PATH);

	char szCurrDir[_MAX_PATH];
	ZeroMemory((LPVOID)szCurrDir, _MAX_PATH);

	int iSelected = SendMessage(hwndLV, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

	LVITEM lvi;
	memset(&lvi, 0, sizeof(lvi));

	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.iSubItem = 0;
	lvi.pszText = szDirectory;
	lvi.cchTextMax = 256;
	lvi.iItem = iSelected;

	ListView_GetItem(hwndLV, &lvi);

	FileInfo* pFileInfo = (FileInfo*)lvi.lParam;

	if (pFileInfo->type == 1)
	{
		// we double-clicked on a folder, get new file list

		// push the current directory onto the Back button stack
		GetCurrDir(szCurrDir, _MAX_PATH);
		PushBackStack(szCurrDir);

		// get the parent path
		hwndLookIn = GetDlgItem(g_hwndFileOpenDlg, IDC_LOOKIN_COMBO);

		// get the index of the current selection
		int nCurSel = SendMessage(hwndLookIn, CB_GETCURSEL, 0, 0);

		// get the associated itemdata
		lstrcpy(szParentPath, (LPSTR)SendMessage(hwndLookIn, CB_GETITEMDATA, nCurSel, 0));

		bRet = RefreshFileList(szParentPath, szDirectory);

		// enable 'back' toolbar button
		EnableBackButton(TRUE);
	}
	else
	{
		// copy text to the file name combo and send IDOK msg
		if (UpdateFileName(g_hwndFileOpenDlg, pFileInfo->name))
		{
			// close the dialog and return the selected file
			SendMessage(g_hwndFileOpenDlg, WM_COMMAND, (WPARAM)IDOK, 0L);
		}
	}
}

BOOL AddItem(FileInfo* pFileInfo, int nPos)
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

void ListView_OnDispInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LV_DISPINFO *pDispInfo = (LV_DISPINFO*) pNMHDR;
	FileInfo *pFileInfo;
	char szSize[10] = {0};
	char szDateTime[30] = {0};
	char szDate[15] = {0};
	char szTime[15] = {0};
	SYSTEMTIME sm;
	char szDateFormat[] = "MM'/'dd'/'yy";
	char szTimeFormat[] = "hh':'mm tt";

	switch (pDispInfo->hdr.code)
	{
		case LVN_GETDISPINFO:
			pFileInfo = (FileInfo*)pDispInfo->item.lParam;
			
			switch (pDispInfo->item.iSubItem)
			{

					// file name
			case 0:
					pDispInfo->item.mask |= LVIF_IMAGE;
					pDispInfo->item.pszText = (LPSTR)pFileInfo->name;
					pDispInfo->item.iImage = GetIconIndex((LPSTR)pFileInfo->name, pFileInfo->type);
					break;

					// file type
				case 1:
					pDispInfo->item.pszText = GetTypeName((LPSTR)pFileInfo->name);
					break;

					// file size
				case 2:
					if (pFileInfo->size != 0)
					{
						// convert to string
						ZeroMemory((LPVOID)szSize, 10);
						_itoa(pFileInfo->size, szSize, 10);

						pDispInfo->item.mask = LVIF_TEXT;
						pDispInfo->item.iSubItem = 2;

						pDispInfo->item.pszText = szSize;
					}

					break;

					// file timestamp
				case 3:
					FileTimeToSystemTime(&(pFileInfo->time), &sm);
					// get formatted date
					GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &sm, szDateFormat, szDate, sizeof(szDate));
					// get formatted time
					GetTimeFormat(LOCALE_SYSTEM_DEFAULT, 0, &sm, szTimeFormat, szTime, sizeof(szTime));
					// concatenate the two
					sprintf(szDateTime, "%s %s", szDate, szTime);
					pDispInfo->item.pszText = szDateTime;
					break;
				default:
					break;
			}
			break;

		default:
			break;
	}
}

int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	static LV_FINDINFO fi;
	static int         nItem1, nItem2;
	static char        szBuf1[30], szBuf2[30];

	FileInfo *pFileInfo1 = (FileInfo*)lParam1;
	FileInfo *pFileInfo2 = (FileInfo*)lParam2;

	LONG lTimeDiff = 0;

	//// Determine the items that we are comparing.
	//fi.flags  = LVFI_PARAM;
	//fi.lParam = lParam1;
	//nItem1 = ListView_FindItem(hWndList, -1, &fi);

	//fi.lParam = lParam2;
	//nItem2 = ListView_FindItem(hWndList, -1, &fi);

	//// Retrieve the item text so we can compare it.
	//ListView_GetItemText(hWndList, nItem1, lParamSort, szBuf1, sizeof(szBuf1));
	//ListView_GetItemText(hWndList, nItem2, lParamSort, szBuf2, sizeof(szBuf2));

	switch (lParamSort)
	{
		// name
		case 0:
			{
				// Return the comparison results.
				if (g_pFileOpenDlgPrivate->_ColSort[lParamSort] == ASC)
				{
					return(strcmp(pFileInfo1->name, pFileInfo2->name));
				}
				else
				{
					return(strcmp(pFileInfo1->name, pFileInfo2->name) * -1);
				}
			}
			break;

		// type
		case 1:
			{
				ZeroMemory((LPVOID)szBuf1, 30);
				ZeroMemory((LPVOID)szBuf2, 30);

				strcpy(szBuf1, GetTypeName((LPSTR)pFileInfo1->name));
				strcpy(szBuf2, GetTypeName((LPSTR)pFileInfo2->name));

				if (g_pFileOpenDlgPrivate->_ColSort[lParamSort] == ASC)
				{
					return (strcmp(szBuf1, szBuf2));
				}
				else
				{
					return (strcmp(szBuf1, szBuf2) * -1);
				}
			}
		// size
		case 2:
			break;

		case 3:
			lTimeDiff = CompareFileTime(&(pFileInfo1->time), &(pFileInfo2->time));
			break;

		default:
			break;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
// Toolbar
////////////////////////////////////////////////////////////////////////////////////////
void InitializeBackStack()
{
	// initialize stack data structure used by the Back button
	g_pFileOpenDlgPrivate->_pbackStack = new STACK;
	
	int nSize = sizeof(STACK);

	//g_pbackStack = (LPSTACK)malloc(sizeof(STACK));
	ZeroMemory((LPVOID)g_pFileOpenDlgPrivate->_pbackStack, sizeof(STACK));
	g_pFileOpenDlgPrivate->_pbackStack->top = -1;
}

BOOL BackStackEmpty()
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

BOOL PushBackStack(LPCSTR pszDirectory)
{
	g_pFileOpenDlgPrivate->_pbackStack->top++;
	// allocate new string
	char *pszBuf = new char[strlen(pszDirectory) + 1];
	strcpy(pszBuf, pszDirectory);

	g_pFileOpenDlgPrivate->_pbackStack->pszFolders[g_pFileOpenDlgPrivate->_pbackStack->top] = pszBuf;

	return TRUE;
}

BOOL PopBackStack(LPSTR pszPathDir)
{
	char *pszBuf;

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

void EnableBackButton(BOOL bShow)
{
	SendMessage(g_pFileOpenDlgPrivate->_hwndToolbar, TB_ENABLEBUTTON, IDS_BACK, MAKELONG(bShow, 0));
}

void EnableUpButton(BOOL bShow)
{
	SendMessage(g_pFileOpenDlgPrivate->_hwndToolbar, TB_ENABLEBUTTON, IDS_UP, MAKELONG(bShow, 0));
}

HWND CreateToolbar(HWND hwndParent, int x, int y)
{
	TBADDBITMAP tbab;
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
         TrackPopupMenuEx(g_pFileOpenDlgPrivate->_hViewsMenu,
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

	BOOL bRet = ImageList_Draw(g_pFileOpenDlgPrivate->_hilViews, nImageId, lpdis->hDC, lpdis->rcItem.left + 3, lpdis->rcItem.top + 3, ILD_NORMAL);

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

///////////////////////////////////////////////////////////////////////////////////////
// Shortcut Bar
///////////////////////////////////////////////////////////////////////////////////////

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
	ZeroMemory(_shortcutItems, MAX_ITEMS*sizeof(LPSHORTCUTBARITEMSTRUCT));
	_nItemCount = 0;
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
		TrackMouseEvent(&tme);
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
	cxText = 0; //20;//(cyClient / 2) - ((tm.tmAveCharWidth * strlen(_szName)) / 2);

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
		SetBkColor(hdcCompat, crBkgnd);
		SetTextColor(hdcCompat, GetSysColor(COLOR_BTNTEXT));
		ExtTextOut(hdcCompat, 0, 0, ETO_OPAQUE, &rectSelect, NULL, 0, NULL);

		// calculate origin
		int xOffset = (ptEnd.x / 2) - (SHORTCUT_CXICON / 2);
		y += 2;
		// draw folder icon
		DrawIconEx(hdcCompat, xOffset, y, _largeFolderIcon, SHORTCUT_CXICON, SHORTCUT_CYICON, 0, NULL, DI_NORMAL | DI_COMPAT);

		y += SHORTCUT_CYICON + 2;

		RECT r;
		r.top = y;
		r.bottom = y + tm.tmHeight;
		//r.right = (strlen(_items[i].szDir) * tm.tmAveCharWidth) + 25;
		r.right = cxClient; //(strlen(_shortcutItems[i]->szDir) * tm.tmAveCharWidth) + 25;
		r.left = cxText;

		DrawText(hdcCompat,
			_shortcutItems[i]->szDir,
			-1,	// automatically calculates length for null-terminated string in 2nd parameter
			&r,
			DT_CENTER | DT_WORD_ELLIPSIS);

/*
		ExtTextOut(
			hdc, 
			cxText, 
			y, 
			ETO_CLIPPED | ETO_OPAQUE, 
			&r, 
			_shortcutItems[i]->szDir, //_items[i].szDir, 
			strlen(_shortcutItems[i]->szDir), //    _items[i].szDir), 
			NULL);
*/

		// adjust
		ptBegin.y += _btnHeight;
	}

	BitBlt(hdc, 
		0, 
		0, 
		cxClient,
		ptBegin.y, //cyClient,
		hdcCompat,
		0,
		0,
		SRCCOPY);

	SelectObject(hdcCompat, hbmOld);
	DeleteDC(hdcCompat);
	EndPaint(Hwnd(), &ps);

	return 0;
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
	MEMORYSTATUS ms;
	
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

	int nSize = 0;

	switch (msg)
	{
	case WM_NCCREATE:

		// allocate a new ShortcutBar instance
		GlobalMemoryStatus(&ms);
		nSize = sizeof(ShortcutBar);
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









