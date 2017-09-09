#include "stdafx.h"
#include "FileOpenCommon.h"

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
	TCHAR szTmp[40];
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
	int nNumItems = g_fileInfoCount;
	int nInsertPos = (nPos >= 0 && nPos <= nNumItems)?nPos : nNumItems;

	LV_ITEM item;
	item.lParam = (LPARAM) pFileInfo;
	item.pszText = LPSTR_TEXTCALLBACK;
	item.mask = LVIF_TEXT | LVIF_PARAM;
	item.iItem = nInsertPos;
	item.iSubItem = 0;

	if (ListView_InsertItem(g_hwndLV, &item) < 0)
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
				if (g_ColSort[lParamSort] == ASC)
				{
					//g_ColSort[lParamSort] = DESC;
					return(strcmp(pFileInfo1->name, pFileInfo2->name));
				}
				else
				{
					//g_ColSort[lParamSort - 1] = ASC;
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

				if (g_ColSort[lParamSort] == ASC)
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
}

