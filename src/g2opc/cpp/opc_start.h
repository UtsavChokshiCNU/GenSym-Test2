
#if !defined(AFX_G2OPC_H__51C409DD_D742_4771_B5EF_A712DCFCA992__INCLUDED_)
#define AFX_G2OPC_H__51C409DD_D742_4771_B5EF_A712DCFCA992__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#define WM_TRAY				(WM_APP + 1)
#define ID_TRAY				5000
#define ID_TRAY_ABOUT       6000
#define ID_TRAY_FINDSERVERS 6001
#define ID_TRAY_CTRL_PANEL  6002
#define ID_TRAY_EXIT		6003

/* typedef struct _DllVersionInfo
{
    DWORD cbSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformID;
}DLLVERSIONINFO; */

extern HWND		g_hWnd;			// Handle to hidden main window
extern HANDLE	g_hGsiThread;	// GsiLoop thread handle

#endif // !defined(AFX_G2OPC_H__51C409DD_D742_4771_B5EF_A712DCFCA992__INCLUDED_)
