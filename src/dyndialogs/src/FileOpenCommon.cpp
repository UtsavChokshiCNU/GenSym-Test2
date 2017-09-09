#include "stdafx.h"
#include "FileOpenCommon.h"

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
	char szDir[_MAX_PATH];
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
	szPathName[n] = '/0';

	return szPathName;
}
