// GensymTestHarness.cpp : Defines the entry point for the application.
//

#define UNICODE
#define _UNICODE

#include "stdafx.h"
#include "dyndlgs.h"
#include "testharness.h"
#include "ddrsc.h"

#include "GensymTestHarness.h"

#define MAX_LOADSTRING 100

// Global Variables:
TCHAR szTitle[MAX_LOADSTRING];                     // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];               // the main window class name
extern "C" HANDLE hInst;
extern "C" HWND hwndFrame;
extern HWND g_hwndFileOpenDlg;                     // file open dialog hwnd
HWND g_UpdateGridDlg;                              // update grid dialog hwnd

// Forward declarations of functions included in this code module:
int test_harness_main(HINSTANCE hInstance, LPTSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK  About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK GridDemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
VOID CALLBACK GridUpdateTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

// External functions
extern "C" long g2pvt_start_replace_grid_row(long dialogid, long controlid, 
                                             long key, long bgcolor, long textcolor);
extern "C" long g2pvt_end_replace_grid_row(long dialogid, long controlid, long key);
extern void g2ext_cleanup_dynamic_dialog();
extern "C" long g2ext_show_dialog(long, long, long, long);
extern "C" int g2ext_build_dynamic_dialog_1();
extern "C" int g2ext_build_dynamic_dialog_2();
extern "C" int g2ext_build_dynamic_dialog_3();
extern "C" int g2ext_build_dynamic_dialog_4();
extern "C" int g2ext_build_message_browser();
extern "C" void g2ext_initialize_g2pointers();
extern "C" long  g2pvt_update_dialog(GENSYMDIALOG*, CONTROLITEM*, int);
extern "C" GENSYMDIALOG* list_of_dialogs;
extern "C" long g2pvt_update_grid_cell (GENSYMDIALOG* pdialog, long controlId,
                                        long key, long col, LPCTSTR value, 
                                        long bgcolor, long textcolor);
extern "C" long g2pvt_delete_grid_row_by_key(GENSYMDIALOG* pdialog, long controlId,
                                             long key);
extern "C" long g2ext_start_add_grid_row(int dlgid, int ctrlid, long key, long bgcolor, long textcolor);
extern "C" long g2ext_add_grid_cell(int dlgid, int ctrlid, long key, 
                                    TCHAR *text, long bgcolor, long textcolor);
extern "C" long g2ext_end_add_grid_row(long dialogid, long controlid, long key);
extern "C" long g2pvt_get_grid_cell_value(long dialogid, long controlid, long key, long column, 
                                          TCHAR *text, int cchTextMax);
extern "C" void g2pvt_get_control_value (HWND hwndDlg, int id, LPSTR pszValue, long cchTextMax);
extern "C" long g2pvt_bring_dialog_to_top(long dialogid);
extern "C" long g2pvt_show_dialog(long dialogid, BOOL bShow);

extern "C" long g2pvt_delete_all_grid_rows(long dialogid, long controlid);

extern long g2pvt_delete_all_grid_selected_rows(long dialogid, long controlid);
extern long g2ext_get_grid_selected_row_count(long dialogid, long controlid);
extern long g2ext_get_grid_selected_row_index(long dialogid, long controlid, int start);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
  return test_harness_main(hInstance, lpCmdLine, nCmdShow);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
static ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wcex;
  
  wcex.cbSize = sizeof(WNDCLASSEX); 
  
  wcex.style      = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc  = (WNDPROC)WndProc;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = 0;
  wcex.hInstance    = hInstance;
  wcex.hIcon      = NULL; //LoadIcon(hInstance, (LPCTSTR)IDI_GENSYMTESTHARNESS);
  wcex.hCursor    = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName  = (LPCTSTR)IDC_GENSYMTESTHARNESS;
  wcex.lpszClassName  = szWindowClass;
  wcex.hIconSm    = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
  
  return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
static BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  
  hInst = (HANDLE) hInstance; // Store instance handle in our global variable
  
  // initialize COM because the Shell32 library requires it
  CoInitialize(NULL);
  
  
  // Initialize Gensym's g2pointers facility
  g2ext_initialize_g2pointers();
  
  // initialize the common controls library
  INITCOMMONCONTROLSEX icex;
  icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
  
  icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES | ICC_TAB_CLASSES;
  InitCommonControlsEx(&icex);
  
  hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
  
  if (!hWnd)
  {
    return FALSE;
  }
  
  hwndFrame = hWnd;
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
  return TRUE;
}

void g2ext_cleanup_dynamic_dialog()
{
  GENSYMDIALOG *iterator;
  
  // clean up list of dialog responses
  if (list_of_dialogs == NULL) {
    return;
  }
  
  for (iterator = list_of_dialogs;
  iterator != NULL;
  iterator = iterator->next) {
    delete iterator->mResponse;
  }
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT  - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  
  switch (message) 
  {
    HANDLE_MSG(hWnd, WM_COMMAND, GensymTestHarness_OnCommand);
  }
  
  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    // TODO: Add any drawing code here...
    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    g2ext_cleanup_dynamic_dialog();
    PostQuitMessage(0);
    break;
  case WM_QUIT:
    CoUninitialize();
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

static int BuildDynamicDlgData(UINT id)
{
  switch (id)
  {
  case IDM_DYNAMIC_DIALOG1:
    return g2ext_build_dynamic_dialog_1();
    break;
    
  case IDM_DYNAMIC_DIALOG2:
    return g2ext_build_dynamic_dialog_2();
    break;
    
  case IDM_DYNAMIC_DIALOG3:
    return g2ext_build_dynamic_dialog_3();
    break;
    
  case IDM_DD_GRIDDLG:
    return g2ext_build_dynamic_dialog_4();
    break;
    
  case IDM_DYNDLGS_MSG_BROWSER:
    return g2ext_build_message_browser();
    break;
    
  default:
    break;
  }
  return NULL;
}

static void GensymTestHarness_OnCommand(HWND hWnd, int id, HWND hctl, UINT codeNotify)
{
  int hdialog;
  CONTROLITEM *pcontrol = new CONTROLITEM;
  TCHAR szVal[] = _T("updated");
  TCHAR szBuf[MAX_PATH] = {0};
  
  // dynamic dialogs
  // heap-based structure containing array of pointers to CONTROLITEM structs and its count
  // passed to the dynamic dialog as a parameter which is then responsible for destroying it
  
  switch (id)
  {
    
  case IDM_DYNAMIC_DIALOG1:
    hdialog = BuildDynamicDlgData(id);
    g2ext_show_dialog(hdialog, GPD_DESKTOP_CTR, GPD_DESKTOP_CTR, 0);
    break;
    
  case IDM_DYNAMIC_DIALOG2:
    hdialog = BuildDynamicDlgData(id);
    g2ext_show_dialog(hdialog, 20, 20, 0);
    break;
    
  case IDM_DYNAMIC_DIALOG3:
    hdialog = BuildDynamicDlgData(id);
    g2ext_show_dialog(hdialog, GPD_CENTER, GPD_CENTER, 0);
    break;
    
  case IDM_DYNDLGS_MSG_BROWSER:
    hdialog = BuildDynamicDlgData(id);
    g2ext_show_dialog(hdialog, GPD_CENTER, GPD_CENTER, 0);
    break;
    
  case IDM_UPDATE_DLG:
    pcontrol->_controlId = IDC_COMBO1;
    pcontrol->_mText = new TCHAR[_tcslen(szVal)+1];                // temp test code
    _tcscpy(pcontrol->_mText, _T("Medium"));
    pcontrol->_type = ctComboBox;
    
    g2pvt_update_dialog(list_of_dialogs, pcontrol, ADD);
    //g2pvt_update_dialog(list_of_dialogs, pcontrol, REPLACE, TRUE);
    //g2pvt_update_dialog(0, IDC_COMBO1, "Medium", ADD);
    //g2pvt_update_dialog(0, IDOK, "Okey Dokey!", REPLACE);
    break;
    
  case IDM_DD_GRIDDLG:
    hdialog = BuildDynamicDlgData(id);
    g2ext_show_dialog(hdialog, 0, 0, 0);
    break;
    
  case IDM_DYNDLGS_GRID_DEMO:
    DialogBox((HINSTANCE) hInst, (LPCTSTR)IDD_GRID_DEMO_DLG, hWnd, (DLGPROC)GridDemoDlgProc);
    break;
    
  case IDM_QUERY_DLG_ITEM:                                      // temp test code
    //g2pvt_get_grid_cell_value(0, IDC_LIST_MSG_BROWSE, 1, 1, szBuf, MAX_PATH);
    //itoa(g2ext_get_grid_selected_row_count(0, IDC_LIST_MSG_BROWSE), szBuf, 10);      
    //g2pvt_get_control_value(0, IDC_EDIT1, szBuf, MAX_PATH);
    _itot(g2ext_get_grid_selected_row_index(0, IDC_LIST_MSG_BROWSE, -1), szBuf, 10);
    
    MessageBox(NULL, szBuf, _T("Query Result"), MB_OK);
    break;
    
  case IDM_ABOUT:
    DialogBox((HINSTANCE) hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
    break;
    
  case IDM_EXIT:
    // TODO: we need to check to see if the Open File modeless dialog is running; if so, destroy it first
    
    DestroyWindow(hWnd);
    return;
  }
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:
    return TRUE;
    
  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
    {
      EndDialog(hDlg, LOWORD(wParam));
      return TRUE;
    }
    break;
  }
  return FALSE;
}

// Message handler for grid demo dialog
LRESULT CALLBACK GridDemoDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  int *intarr = NULL;
  long nRet = 0;
  int nCol = 0;
  int nKey = 0;
  TCHAR szBuf[MAX_TEXT] = {0};
  TCHAR szCol[3] = {0};
  TCHAR szKey[3] = {0};
  static UINT nTimerId;
  int nSelRowCount = 0;
  int i = 0;
  int nNext = 0;
  TCHAR szNext[MAX_TEXT] = {0};
  
  switch (message)
  {
  case WM_INITDIALOG:
    
    // set global hwnd
    g_UpdateGridDlg = hDlg;
    
    // initialize the spin control
    // set position
    SendMessage(GetDlgItem(hDlg, IDC_SPIN_COL), UDM_SETPOS, 0, (LPARAM) MAKELONG (1, 0)); 
    
    // set range 
    SendMessage(GetDlgItem(hDlg, IDC_SPIN_COL), UDM_SETRANGE, 0, 2);
    
    
    return TRUE;
    
  case WM_COMMAND:
    switch (LOWORD(wParam)) {
    case IDOK:
    case IDCANCEL:
      KillTimer(NULL, nTimerId);
      EndDialog(hDlg, LOWORD(wParam));
      return TRUE;
      
    case IDC_BTN_DELETE:
      // use helper function
      g2pvt_delete_all_grid_selected_rows(0L, IDC_LIST_MSG_BROWSE);
      break;
      
    case IDC_BTN_GET_SELS:
      nSelRowCount = g2ext_get_grid_selected_row_count(0L, IDC_LIST_MSG_BROWSE);
      _tcscpy(szBuf, _T("Selected rows: "));
      nNext = -1;
      for (i = 0; i < nSelRowCount; i++) {
        nNext = g2ext_get_grid_selected_row_index(0L, IDC_LIST_MSG_BROWSE, nNext);
        ZeroMemory(szNext, sizeof(szNext));
        
        _itot(nNext, szNext, 10);
        _tcscat(szBuf, szNext);
        _tcscat(szBuf, _T("\n"));
      }
      MessageBox(NULL, szBuf, _T("Selected Rows"), MB_OK);
      break;
      
    case IDC_BTN_APPLY:
      
      Sleep(1000);
      
      g2pvt_bring_dialog_to_top(0L);
      
      Sleep(1000);
      
      // set timer for updates
      nTimerId = SetTimer(NULL, 0, 1000, (TIMERPROC)GridUpdateTimerProc);
      
      //nRet = update_grid_cell(list_of_dialogs, IDC_LIST_MSG_BROWSE, 
      //  1, 1, "updated!");
      //nRet = delete_grid_row(list_of_dialogs, IDC_LIST_MSG_BROWSE, 0);
      /*
      SendMessage(GetDlgItem(hDlg, IDC_EDIT4), WM_GETTEXT, MAX_TEXT, (LPARAM)szBuf);
      SendMessage(GetDlgItem(hDlg, IDC_EDIT_COL), WM_GETTEXT, 3, (LPARAM)szCol);
      SendMessage(GetDlgItem(hDlg, IDC_EDIT3), WM_GETTEXT, 3, (LPARAM)szKey);
      nRet = update_grid_cell(list_of_dialogs, IDC_LIST_MSG_BROWSE, atol(szKey), atol(szCol), szBuf);
      */
      break;
    }
    break;
  }
  return FALSE;
}

VOID CALLBACK GridUpdateTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
  static int i = 0;
  int j = 0;
  long nRet = 0;
  long lCol = 0;
  long lKey = 0;
  TCHAR szBuf[MAX_TEXT] = {0};
  TCHAR szCol[3] = {0};
  TCHAR szKey[3] = {0};
  int color = 0;
  
  i++;
  _itot(i, szBuf, 10);
  
#if 0
  
  SendMessage(GetDlgItem(g_UpdateGridDlg, IDC_EDIT_COL), WM_GETTEXT, 3, (LPARAM)szCol);
  SendMessage(GetDlgItem(g_UpdateGridDlg, IDC_EDIT3), WM_GETTEXT, 3, (LPARAM)szKey);
  color = 50+(i*20);
  
  lKey = _ttol(szKey);
  lCol = _ttol(szCol);
  
  // replace row sequence
  g2pvt_start_replace_grid_row(0, IDC_LIST_MSG_BROWSE, lKey, DEFAULT_COLOR, DEFAULT_COLOR); //RGB(50, color, 100));
  nRet = g2pvt_update_grid_cell(list_of_dialogs, IDC_LIST_MSG_BROWSE, lKey, 0, szBuf, RGB(200, 120, color), RGB(50, color, 100));
  nRet = g2pvt_update_grid_cell(list_of_dialogs, IDC_LIST_MSG_BROWSE, lKey, 1, szBuf, NO_REPLACE, DEFAULT_COLOR);
  nRet = g2pvt_update_grid_cell(list_of_dialogs, IDC_LIST_MSG_BROWSE, lKey, 2, _T("hey hey"), DEFAULT_COLOR/*RGB(75, 75, 78)*/, RGB(30, 150, 200));
  g2pvt_end_replace_grid_row(0, IDC_LIST_MSG_BROWSE, lKey);
#endif
  
  const TCHAR sz11[] = _T("4");
  const TCHAR sz12[] = _T("Pending");
  const TCHAR sz13[] = _T("NONE");
  
  const TCHAR sz21[] = _T("5");
  const TCHAR sz22[] = _T("Closed");
  const TCHAR sz23[] = _T("NONE");
  
  // allocate and populate an array of strings
  TCHAR ** ppvals = (TCHAR**)malloc(3);
  TCHAR ** ppvals2 = (TCHAR**)malloc(3);
  
  ZeroMemory((LPVOID)ppvals, 3*sizeof(TCHAR*));
  
  ppvals[0] = (TCHAR*)malloc(3);
  _tcscpy(ppvals[0], sz11);
  
  ppvals[1] = (TCHAR*)malloc(3);
  _tcscpy(ppvals[1], sz12);
  
  ppvals[2] = (TCHAR*)malloc(3);
  _tcscpy(ppvals[2], sz13);
  
  ZeroMemory((LPVOID)ppvals2, 3*sizeof(TCHAR*));
  
  ppvals2[0] = (TCHAR*)malloc(3);
  _tcscpy(ppvals2[0], sz21);
  
  ppvals2[1] = (TCHAR*)malloc(3);
  _tcscpy(ppvals2[1], sz22);
  
  ppvals2[2] = (TCHAR*)malloc(3);
  _tcscpy(ppvals2[2], sz23);
  
  if (i == 7) {
    g2ext_start_add_grid_row(
      0,                          // dialog id
      IDC_LIST_MSG_BROWSE,        // control id
      3,                          // key
      RGB(30, 150, 200),          // row background color
      RGB(255, 0, 0));            // row text color
    
    for (j = 0; j < 3; j++) {
      g2ext_add_grid_cell(0, IDC_LIST_MSG_BROWSE, 3, (TCHAR*)ppvals[j], RGB(125, 150, 150), RGB(255, 255, 255));
    }
    
    g2ext_end_add_grid_row(0, IDC_LIST_MSG_BROWSE, 3);
    
  }
  
  if (i == 13) {
    g2ext_start_add_grid_row(
      0,                          // dialog id
      IDC_LIST_MSG_BROWSE,        // control id
      4,                          // key
      RGB(220, 100, 50),          // row background color
      RGB(255, 0, 0));            // row text color
    
    for (j = 0; j < 3; j++) {
      g2ext_add_grid_cell(0, IDC_LIST_MSG_BROWSE, 4, (TCHAR*)ppvals2[j], RGB(150, 150, 150), RGB(255, 255, 255));
    }
    
    g2ext_end_add_grid_row(0, IDC_LIST_MSG_BROWSE, 4);
    
  }
  
}

static int test_harness_main(HINSTANCE hInstance,
                             LPTSTR    lpCmdLine,
                             int       nCmdShow)
{
  MSG msg;
  HACCEL hAccelTable;
  
  // Initialize global strings
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_GENSYMTESTHARNESS, szWindowClass, MAX_LOADSTRING);
  
  MyRegisterClass(hInstance);
  
  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow)) {
    return FALSE;
  }
  
  hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_GENSYMTESTHARNESS);
  
  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0)) {
    
    HWND hActive = GetActiveWindow();
    
    if (GetWindowLong(hActive, GWL_EXSTYLE) & WS_EX_CONTROLPARENT) {
      if (IsDialogMessage(hActive, &msg) ) {
        continue;  // restart while loop
      }
      
      // fall through
    }
    
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  
  return (int) msg.wParam;
}
