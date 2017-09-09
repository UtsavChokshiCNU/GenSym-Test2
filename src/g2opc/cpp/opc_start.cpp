// G2OPC.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <gsi_main.h>
#include <shellapi.h>

/****************************************************************** */
// In order for a C++ client to make use of
// ATL event helpers, we need to include the 
// following files:
#include <atlbase.h> 

// We need to 'fool' ATL into thinking we are creating a COM server:
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

#include <atlcom.h>

/****************************************************************** */

#define MAX_LOADSTRING 100

// Global Variables:
NOTIFYICONDATA      g_iconData;	// Tray icon structure
HICON               g_hIcon;	// Tray icon handle
HINSTANCE           g_hInst;    // Application instance
HMENU               g_hMenu;	// Handle to tray popup menu
HWND                g_hWnd;     // Handle to hidden main window
TCHAR               szWindowClass[MAX_LOADSTRING];  // The title bar text
BOOL                haveVer ;
DWORD               dwMajor ;
short               g_license_status = 0 ;
HANDLE				g_hGsiThread;	// GsiLoop thread handle


// ========================================================================== //
//                                                                            //
//                               O P C L I N K                                //
//                                                                            //
//                   Program Initialization & Message Loop                    //
//                                                                            //
// ========================================================================== //
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(NULL) ;
    _Module.Init(NULL,hInstance) ;
    CG2OpcHiddenWin win ;

    // Create hidden window and initialize g_hWnd
    g_hWnd = win.Create() ;

    MSG msg;
    HACCEL hAccelTable;

    g_shutdown_request = false ;
    hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_G2OPC);


    // Start the GSI thread
    // --------------------
    DWORD   dwGsiThreadId, dwErrorCode = 0 ;

    g_hGsiThread = CreateThread(NULL, 0, 
        (LPTHREAD_START_ROUTINE)GsiLoop, (LPVOID)lpCmdLine,
        0, &dwGsiThreadId) ;

    if (g_hGsiThread == 0)
    {
        dwErrorCode = GetLastError() ;
        log_message(TL_CRITICAL,L"GSI thread failed to start.") ;
        win.DestroyWindow() ;
        _Module.Term() ;
        return dwErrorCode ;
    }
    while(!g_license_status)
        Sleep(50) ;


    // Main message loop:
    // ------------------
    if (g_license_status > 0)
        while (GetMessage(&msg, NULL, 0, 0)) 
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    win.DestroyWindow() ;
    _Module.Term() ;
    CloseLogFile();

    return (g_license_status > 0) ? msg.wParam : -1 ;
}
