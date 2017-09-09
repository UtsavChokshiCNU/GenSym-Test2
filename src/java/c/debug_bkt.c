#include <stdio.h>
#include <stdarg.h>
#include "shared.h"
#include "dprintf.h"
#include "javaString.h"


#ifdef WIN32

#define NOASSERT

#if !defined( _DBGTRACE )
#define _DEBUGLEVEL 2
#else
#define _DEBUGLEVEL _DBGTRACE
#endif



DWORD   __dwEval;


/*  */
/*  Constants */
/*  */

#define MAXLISTLINES    10000     /*  max list lines we keep */
#define IDC_LIST        1         /*  listbox id */
#define ERRSTRM         stdout

/*  */
/*  local data */
/*  */

HWND hwndDebug;
HWND hwndDebugList;
HWND ghwndMain = NULL;
HINSTANCE ghAppInstance;            /*  app instance */

static short __iDebugLevel = 0;

/*  function to add a string to the end of the debug list */
void cdecl DbgOut(LPSTR lpFormat, ...) 
{
    int i;
    char buf[256];
    va_list args;

    /*  */
    /*  See if we have a debug window or not. */
    /*  If not then try to create one. */
    /*  */

    if (!hwndDebug) {

      sprintf(buf, "Bucket - Debug");
      hwndDebug = CreateWindow("Debug",
			       buf,
			       WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
			       | WS_BORDER | WS_THICKFRAME | WS_MINIMIZEBOX,
			       /* x, y, width, height */
			       (int) ((float)GetSystemMetrics(SM_CXSCREEN) / 1.5), 
			       GetSystemMetrics(SM_CYSCREEN) / 10,
			       (int) ((float) GetSystemMetrics(SM_CXSCREEN) / 3),
			       (int) ((float) GetSystemMetrics(SM_CYSCREEN) / 1.5),
			       (HWND)NULL,
			       (HMENU)NULL,
			       ghAppInstance,
			       (LPSTR)NULL
			       );

      if (!hwndDebug) return;
    }

    /*  */
    /*  format the string */
    /*  */

    va_start(args, lpFormat);
    vswprintf(buf, lpFormat, args);

    /*  */
    /*  get the item count */
    /*  */

    i = (int) SendMessage(hwndDebugList, LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0);
    if (i == LB_ERR) i = 0;

    /*  */
    /*  scrub a few if we have too many */
    /*  */

    while (i >= MAXLISTLINES) {
        SendMessage(hwndDebugList, LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
        i--;
    }

    /*  */
    /*  add the new one on at the end and scroll it into view */
    /*  */

    i = (int) SendMessage(hwndDebugList, LB_ADDSTRING, (WPARAM) 0, (LPARAM) (LPSTR) buf);
    SendMessage(hwndDebugList, LB_SETCURSEL, (WPARAM) i, (LPARAM) 0);

}

void cdecl dprintf(short debugLevel, LPSTR lpFormat, ...) 
{
    char buf[256];
    va_list args;

    if (DebugLevel() < debugLevel) return;
    /*  format the string */
    va_start(args, lpFormat);
    vsprintf(buf, lpFormat, args);
    DbgOut("%s", buf);
}

void cdecl jprintf(JNIEnv * env, short debugLevel, LPSTR lpFormat, ...) {
	
    char buf[256];
    va_list args;

    if (DebugLevel() < debugLevel) return;
    /*  format the string */
    va_start(args, lpFormat);
    vsprintf(buf, lpFormat, args);
    DbgOut("%s", buf);
}



void cdecl debug_print_char(char c)
{
    int i;
    char buf[2];

    if (!hwndDebug) {
      DbgOut("Bucket - Debug");
    }

    buf[0] = c;
    buf[1] = 0;

    i = (int) SendMessage(hwndDebugList, LB_GETCOUNT, (WPARAM) 0, (LPARAM) 0);
    if (i == LB_ERR) i = 0;

    while (i >= MAXLISTLINES) {
        SendMessage(hwndDebugList, LB_DELETESTRING, (WPARAM) 0, (LPARAM) 0);
        i--;
    }

    i = (int) SendMessage(hwndDebugList, LB_ADDSTRING, (WPARAM) 0, (LPARAM) (LPSTR) buf);
    SendMessage(hwndDebugList, LB_SETCURSEL, (WPARAM) i, (LPARAM) 0);
}


/*  */
/*  Show a message box with assertion failure info in it */
/*  */

void __AssertMsg(LPSTR exp, LPSTR file, int line)
{
    char buf[256];
    int i;

    sprintf(buf, 
             "Exp: %s\nFile: %s, Line %d",
             (LPSTR)exp,
             (LPSTR)file,
             line);
    DbgOut("ASSERT: Exp: %s", (LPSTR)exp);
    DbgOut(" File: %s, Line %d", (LPSTR)file, line);
    i = MessageBox(ghwndMain,
                   buf,
                   "Assertion failure", 
                   MB_OK | MB_ICONEXCLAMATION);
}

/*  */
/*  Measure an item in our debug listbox */
/*  */

static void MeasureDebugItem(HWND hWnd, LPMEASUREITEMSTRUCT lpMIS)
{
    TEXTMETRIC tm;
    HDC hDC;


    hDC = GetDC(hWnd);
    GetTextMetrics(hDC, &tm);
    ReleaseDC(hWnd, hDC);
    lpMIS->itemHeight = tm.tmHeight;
}

/*  */
/*  Display an item in our debug listbox */
/*  */

void DrawDebugItem(HWND hWnd, LPDRAWITEMSTRUCT lpDI)
{
    HBRUSH hbrBkGnd;
    RECT rc;
    HDC hDC;
    char buf[256];
    
    hDC = lpDI->hDC;
    rc = lpDI->rcItem;

    switch (lpDI->itemAction) {

    case ODA_SELECT:
    case ODA_DRAWENTIRE:

        /*  */
        /*  erase the rectangle */
        /*  */

        hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        FillRect(hDC, &rc, hbrBkGnd);
        DeleteObject(hbrBkGnd);

            /*  */
            /*  show the text in our standard font */
            /*  */
    
            SetBkMode(hDC, TRANSPARENT);
    
            SendMessage(lpDI->hwndItem, 
                        LB_GETTEXT, 
                        lpDI->itemID, 
                        (LPARAM)(LPSTR)buf);

            ExtTextOut(hDC, 
                       rc.left+2, rc.top,
                       ETO_CLIPPED,
                       &rc, 
                       buf,
                       lstrlen(buf), 
                       NULL);
    
        break;
    
    }
}


/*  */
/*  Window procedure for debug window */
/*  */

LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch(msg) {
    case WM_CREATE:

        /*  */
        /*  Create the listbox  */
        /*  */

        hwndDebugList = CreateWindow("Listbox",
                            "",
                            WS_CHILD | WS_VISIBLE | WS_VSCROLL
                             | LBS_DISABLENOSCROLL
                             | LBS_HASSTRINGS | LBS_OWNERDRAWFIXED
                             | LBS_NOINTEGRALHEIGHT,
                            0,
                            0,
                            0,
                            0,
                            hWnd,
                            (HMENU)IDC_LIST,
                            ghAppInstance,
                            (LPSTR)NULL
                            );

        break;

    case WM_SIZE:
        SetWindowPos(hwndDebugList,
                     NULL,
                     0, 0,
                     LOWORD(lParam), HIWORD(lParam),
                     SWP_NOZORDER);
        break;

    case WM_SETFOCUS:
        SetFocus(hwndDebugList);
        break;

    case WM_MEASUREITEM:
        MeasureDebugItem(hWnd, (LPMEASUREITEMSTRUCT)lParam);
        return (LRESULT) TRUE;

    case WM_DRAWITEM:
        DrawDebugItem(hWnd, (LPDRAWITEMSTRUCT) lParam);
        break;

    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        hwndDebug = NULL;
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
        break;
    }
    return (LRESULT) NULL;
}

void ClearDebugHistory()
{
    if (hwndDebugList) {
        SendMessage(hwndDebugList, LB_RESETCONTENT, 0, 0);
    }
}

void start_up_debug_window(HANDLE hInstance)
{
    WNDCLASS wc;

    ghAppInstance = hInstance;

    wc.lpszClassName    = "Debug";
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(hInstance,"Icon");
    wc.lpszMenuName     = NULL;
    wc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = DebugWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    
    RegisterClass(&wc);
}


short DebugLevel()
{
  return __iDebugLevel;
}


void C_setDebugLevel(JNIEnv * env, short newDebugLevel)
{
  dprintf(1, "Setting idebug to %d", newDebugLevel);
  __iDebugLevel = newDebugLevel;
}


/*  Show a message box */
UINT cdecl AlertBox(LPSTR lpFormat, ...) 
{
  char buf[256];
  va_list args;

  va_start(args, lpFormat);
  vsprintf(buf, lpFormat, args);
  /*  MessageBeep(MB_ICONEXCLAMATION); */
  return (UINT) MessageBox(NULL, 
			   buf, 
			   "Bucket",
			   MB_OK|MB_ICONEXCLAMATION);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void print_iid_info(JNIEnv * env, short debug_level, char *intro_string, 
		    const struct _GUID *iid)
{
    dprintf(debug_level, "%s %08x-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
	  intro_string, iid->Data1, iid->Data2, iid->Data3, 
	  iid->Data4[0], iid->Data4[1], iid->Data4[2], iid->Data4[3],
	  iid->Data4[4], iid->Data4[5], iid->Data4[6], iid->Data4[7]);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void print_iid_info_the_normal_way(char *intro_string, const struct _GUID *iid)
{
  OLECHAR FAR* psz;
  HRESULT hr;

  hr = StringFromCLSID((CLSID *)iid, &psz);
  if (SUCCEEDED(hr))
    dprintf(2, "%s %ls", intro_string, psz);
  else
    dprintf(1, "%s (could not get result)", intro_string);
}


#else /* WIN32 */

CONTAINAPI UINT cdecl AlertBox(LPSTR lpFormat, ...) {}
JNIEXPORT void JNICALL Java_com_gensym_com_NativeMethodBroker_setDebugLevel (JNIEnv *env, jobject this, short newDebugLevel) {}

#endif


