/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <stdio.h>
#include "shared.h"
#include "bucket.h"
#include "dprintf.h"


#ifdef WIN32

#include "com_gensym_com_ActiveXProxy.h"

#include <windows.h>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section. 
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#define gszAppName "Bucket"
#define INITIAL_DEBUG_LEVEL 3
#define EXECUTABLE_FOR_DISPATCH L"Excel.Chart"
/* #define EXECUTABLE_FOR_DISPATCH L"Excel.Application" */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
static PNTWOBJ    gpObjList = NULL;         /*  pointer to the object list */
static HANDLE     ghAccTable;               /*  accelerator table */
static POINT      gptInsert;                /*  coords of insertion point */
static HWND       ghwndMain;                /*  main window handle */
static TEXTMETRIC gtmSysFont;               /*  system font metrics */
static HINSTANCE  ghAppInstance;            /*  app instance */
static char       gachFileName[_MAX_PATH];  /*  current file name */
static PRINTDLG   pd;
static PNTWOBJ    currentlySelected;
static PCOMOBJ    TheCalendar = NULL;
static LPDISPATCH application = NULL;

static short column = 1;
static int value = 20;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP
 %
 % Description:
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*****************************************************************************
 * 
 *
 *   Description: 
 *  Process WM_CREATE message
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void BucketCreate(HWND hWnd, LPCREATESTRUCT lpCI)
{

}


/*****************************************************************************
 * 
 *
 *   Description: 
 *     Process WM_SIZE message
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void Size(HWND hWnd, UINT uiW, UINT uiH)
{

}

/*****************************************************************************
 * 
 *
 *   Description: 
 *     Process WM_MOVE message
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void Move(HWND hWnd, UINT uiX, UINT uiY)
{

}



/*****************************************************************************
 * 
 *
 *   Description: 
 *     About box dialog procedure
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
int CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_INITDIALOG:
	break;

    case WM_COMMAND:
	switch (wParam) {
	case IDOK:
	    EndDialog(hDlg, TRUE);
	    break;
	default:
	    break;
	}
	break;

    default:
	return FALSE; /*  say we didn't handle it */
	break;
    }

    return TRUE; /*  say we handled it */
}


/*  Show the about box */
void About(HWND hWnd)
{
    FARPROC fpDlg;

    fpDlg = MakeProcInstance((FARPROC)AboutDlgProc, ghAppInstance);
    DialogBox(ghAppInstance, MAKEINTRESOURCE(IDD_ABOUT), hWnd, (DLGPROC)fpDlg);
    FreeProcInstance(fpDlg);
}


/*  Set the current debug level */
void ChangeDebugLevel(short i)
{
    HMENU hMenu;
    int m;

    hMenu = GetMenu(ghwndMain); 
    for (m=IDM_DEBUG0; m<=IDM_DEBUG4; m++) {
	CheckMenuItem(hMenu, m, MF_UNCHECKED);
    }
    CheckMenuItem(hMenu, i + IDM_DEBUG0, MF_CHECKED);
    C_setDebugLevel(NULL, i);
}



/*  Select an object */
void set_selected(PNTWOBJ pObj)
{
    if (pObj == NULL)
	AlertBox("Cannot select NULL object");
    currentlySelected = pObj;
}

void deselect()
{
    currentlySelected = NULL;
}

PNTWOBJ get_ntwobj_from_comobj(PCOMOBJ pObj)
{
    PNTWOBJ current, answer;

    if (gpObjList == NULL)
	AlertBox("Not going to be able to find much in a null list.");

    answer = NULL;
    for (current=gpObjList; (current != NULL) && (answer == NULL);
	 current=current->pNext) {
	dprintf(4, "Checking ntwobj %x, comobj %x", current, current->comObj);
	if (current->comObj == pObj)
	    answer = current;
    }
    if (answer == NULL)
	dprintf(1, "Could not find matching NTWOBJ for COMOBJ %x", pObj);
    return answer;
}
  


void append_object (PNTWOBJ pObj)
{
    PNTWOBJ current = gpObjList;

    dprintf(2, "Inside append function.  pObj = %x", (int) pObj);

    if (!pObj) {
	AlertBox("Attempting to add NULL to the list");
	deselect();
	return;
    } else
	set_selected(pObj);

    pObj->pNext = NULL;
    if (current) {
	while (current->pNext)
	    current = current->pNext;
	current->pNext = pObj;
    } else
	gpObjList = pObj;

    dprintf(2, "Finished append function.  pObj = %x", (int) pObj);
}


PNTWOBJ ntw_unlink_object (PCOMOBJ pObj)
{
    PNTWOBJ previous, current;

    dprintf(2, "Inside unlink function");

    if (gpObjList == NULL)
	AlertBox("Trying to remove something from a null list.");

    for (previous=NULL, current=gpObjList;
	 current && (current->comObj != pObj);
	 previous=current, current=current->pNext)
	;
    if (!current)
	AlertBox("Error: could not find %x in list", pObj);
    else
	if (previous)
	    previous->pNext = current->pNext;
	else
	    gpObjList = current->pNext;

    return current;
}


PNTWOBJ ntw_set_up_object(PCOMOBJ pObj, int x, int y, int w, int h)
{
    PNTWOBJ newNtwObj;

    newNtwObj = (PNTWOBJ) calloc((sizeof(NTWOBJ)), 1);
    if (!newNtwObj) {
	dprintf(1, "Out of memory allocating NTWOBJ");
	return NULL;
    } else
	dprintf(3, "Created an NTW Obj!!");
    newNtwObj->comObj = pObj;
    newNtwObj->rc.left = x;
    newNtwObj->rc.top = y;
    newNtwObj->rc.right = x + w;
    newNtwObj->rc.bottom = y + h;
    append_object(newNtwObj);

    dprintf(2, "setting up %x as the ntwobj for %x", newNtwObj, pObj);

    return newNtwObj;
}


/*  Bring an object to the top of the display (bottom of list) */
void BringObjToTop(PCOMOBJ pObj)
{
    PNTWOBJ corresponding;

    dprintf(3, "Bring Obj to Top");

    if (gpObjList->comObj == pObj)
	return;

    setDirty(TRUE);

    /*  Remove it from the list */
    corresponding = ntw_unlink_object(pObj);

    /*  Add it to the end of the list */
    append_object(corresponding);
}



void DeleteBucketobject (PCOMOBJ pObj)
{
    LPSTR pData = NULL;
    LPDATAOBJECT pDataObj = NULL;
    PNTWOBJ corresponding;

    dprintf(2, "Delete");

    /* ASSERT(pObj); */

    corresponding = ntw_unlink_object(pObj);
    free(corresponding);
    Java_com_gensym_com_ActiveXProxy_delete_1object(NULL, NULL, (jint) pObj);
    InvalidateRect(ghwndMain, NULL, TRUE);
}


/*  Process a clipboard command */
void ClipCommand(HWND hWnd, WPARAM wParam)
{
    PCOMOBJ selected_obj;

    switch (wParam) {
    case IDM_COPY:
	Java_com_gensym_com_ActiveXProxy_copy_1object(NULL, NULL,
						    (jint) currentlySelected->comObj,
						    currentlySelected->rc.top,
						    currentlySelected->rc.left,
						    currentlySelected->rc.bottom,
						    currentlySelected->rc.right);
	break;
    
    case IDM_CUT:
	selected_obj = currentlySelected->comObj;
	Java_com_gensym_com_ActiveXProxy_copy_1object(NULL, NULL,
						    (jint) selected_obj,
						    currentlySelected->rc.top,
						    currentlySelected->rc.left,
						    currentlySelected->rc.bottom,
						    currentlySelected->rc.right);
	DeleteBucketobject(selected_obj);
	break;

    case IDM_DELETE:
	DeleteBucketobject(currentlySelected->comObj);
	currentlySelected = NULL;
	break;
    
    case IDM_PASTE:
	selected_obj = (PCOMOBJ) paste_object((long) hWnd);
	if (selected_obj) {
	    PNTWOBJ corresponding;

	    setDirty(TRUE);
	    corresponding = ntw_set_up_object(selected_obj, gptInsert.x, gptInsert.y,
					      DEFAULT_OBJ_WIDTH, DEFAULT_OBJ_HEIGHT);
	    InvalidateRect(hWnd, &(corresponding->rc), TRUE); 
	}
	break;

    default:
	break;
    }
}


void Help(HWND hWnd, WORD wParam)
{
    char szHelpFileName[_MAX_PATH];

    lstrcpy(szHelpFileName, gszAppName);
    lstrcat(szHelpFileName, ".HLP");

    switch (wParam) {
    case IDM_HELPCONTENTS:
	WinHelp(hWnd, szHelpFileName, HELP_CONTENTS, (DWORD)0);
	break;

    default:
	break;

    }
}

    
/*  Set the caption of the main window to show the current file name */
/*  Internal only */

void UpdateCaption(void)
{
    char achCaption[_MAX_PATH + 30]; /*  caption */
    char achDrive[_MAX_DRIVE];    /*  drive */
    char achDir[_MAX_DIR];    /*  directory path */
    char achFname[_MAX_PATH];    /*  file name */
    char achExt[_MAX_EXT];    /*  file name extension */

    gachFileName[0] = '\0';
    if (lstrlen(gachFileName)) {
	_splitpath(gachFileName, achDrive, achDir, achFname, achExt);
	lstrcat(achFname, achExt);
    } else {
	lstrcpy(achFname, "(untitled)");
    }

    sprintf(achCaption, "%s - %s", (LPSTR) gszAppName, (LPSTR) achFname);
    SetWindowText(ghwndMain, achCaption);
}



void client_file_new (WORD wFlags)
{
    /*  its ok to blow away any existing data now. */
    /*  Nuke the object list */
      
    while (gpObjList)
	DeleteBucketobject(gpObjList->comObj);
    /* Java_com_gensym_com_NativeMethodBroker_clear(NULL, NULL, wFlags); */
    C_setDebugLevel(NULL, INITIAL_DEBUG_LEVEL);
    if (wFlags & FILE_UPDATE_CAPTION)
	UpdateCaption();
    InvalidateRect(ghwndMain, NULL, TRUE);
}


/*
 * DrawShading
 *
 * Purpose:
 *  Shade the object when it is in in-place editing. Borders are drawn
 *  on the object rectangle. The right and bottom edge of the rectangle
 *  are excluded in the drawing.
 *
 * Parameters:
 *  lpRect      Dimensions of Container object
 *  hdc         HDC for drawing
 *  dwFlags-
 *      Exclusive flags
 *          OLEUI_SHADE_FULLRECT    Shade the whole rectangle
 *          OLEUI_SHADE_BORDERIN    Shade cWidth pixels inside rect
 *          OLEUI_SHADE_BORDEROUT   Shade cWidth pixels outside rect
 *      Optional flags
 *          OLEUI_SHADE_USEINVERSE
 *              use PATINVERT instead of the hex value
 *  cWidth      width of border in pixel
 *
 * Return Value: null
 *
 */
STDAPI_(void) DrawShading(LPRECT lpRect, HDC hdc, DWORD dwFlags, UINT cWidth)
{
    HBRUSH  hbr;
    HBRUSH  hbrOld;
    HBITMAP hbm;
    RECT    rc;
    WORD    wHatchBmp[] = {0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88};
    COLORREF cvText;
    COLORREF cvBk;

    hbm = CreateBitmap(8, 8, 1, 1, wHatchBmp);
    hbr = CreatePatternBrush(hbm);
    hbrOld = SelectObject(hdc, hbr);

    rc = *lpRect;

    if (dwFlags == OLEUI_SHADE_FULLRECT) {
	cvText = SetTextColor(hdc, RGB(255, 255, 255));
	cvBk = SetBkColor(hdc, RGB(0, 0, 0));
	PatBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
	       0x00A000C9L /* DPa */ );

    } else {    /*  either inside or outside rect */

	if (dwFlags == OLEUI_SHADE_BORDEROUT)
	    InflateRect((LPRECT)&rc, cWidth - 1, cWidth - 1);

	cvText = SetTextColor(hdc, RGB(255, 255, 255));
	cvBk = SetBkColor(hdc, RGB(0, 0, 0));
	PatBlt(hdc, rc.left, rc.top, rc.right - rc.left,
	       cWidth, 0x00A000C9L /* DPa */);
	PatBlt(hdc, rc.left, rc.top, cWidth, rc.bottom - rc.top,
	       0x00A000C9L /* DPa */);
	PatBlt(hdc, rc.right - cWidth, rc.top, cWidth,
	       rc.bottom - rc.top, 0x00A000C9L /* DPa */);
	PatBlt(hdc, rc.left, rc.bottom - cWidth, rc.right-rc.left,
	       cWidth, 0x00A000C9L /* DPa */);
    }

    SetTextColor(hdc, cvText);
    SetBkColor(hdc, cvBk);
    SelectObject(hdc, hbrOld);
    DeleteObject(hbr);
    DeleteObject(hbm);
}

/*  Render an object */
void render_object(HDC hDC_real, PNTWOBJ pObj)
{
    HPEN hpenRed = NULL;
    HPEN hpenOld = NULL;
    jint hDC_address;
    HDC hDC;
    int aspect_ratio, old_ratio;
    IOleInPlaceObject *pIOleIPObject;

    pIOleIPObject = pObj->comObj->pIOleIPObject;

        
    if (!pObj->comObj->insertable) {
	return;
    }
    hDC_address = bucket_GetDC((long) ghwndMain);
    hDC = (HDC) hDC_address;

    old_ratio = (pObj->rc.bottom == pObj->rc.top) ? -1 : 
	(((pObj->rc.right - pObj->rc.left) * 100) / 
	 (pObj->rc.bottom - pObj->rc.top));

    aspect_ratio = Java_com_gensym_com_NativeMethodBroker_getRatio(NULL, NULL,
							     (jint) pObj->comObj);
    if (aspect_ratio == -1)
	dprintf(2, "Could not get ratio");
    else
	if (aspect_ratio > old_ratio)
	    pObj->rc.right = pObj->rc.left +
		((aspect_ratio * (pObj->rc.bottom - pObj->rc.top)) / 100);
	else
	    pObj->rc.bottom = pObj->rc.top +
		(((pObj->rc.right - pObj->rc.left) * 100) / aspect_ratio);

    /*  If its selected, draw a red border around it */
    if (currentlySelected == pObj) {
	hpenRed = CreatePen(PS_SOLID, 2, RGB(255,0,0));
	hpenOld = SelectObject(hDC, hpenRed);

	Rectangle(hDC, 
		  pObj->rc.left-1, pObj->rc.top-1,
		  pObj->rc.right+2, pObj->rc.bottom+2);

	SelectObject(hDC, hpenOld);
	DeleteObject(hpenRed);
    }  

    if (pIOleIPObject) {
      Java_com_gensym_com_ActiveXProxy_resize_1object(NULL, NULL,
						  (jint) pObj->comObj,
						  pObj->rc.top, pObj->rc.left, 
						  pObj->rc.bottom, pObj->rc.right);
    }
    /*  If the object is open in a window, then shade the area */
    /*  to make it obvious */
    else {
     dprintf(2, "Calling render!!! [%d, %d]",
	    pObj->rc.right - pObj->rc.left,
	    pObj->rc.bottom - pObj->rc.top);
    Java_com_gensym_com_ActiveXProxy_render_1object(NULL, NULL,
						  (jint) pObj->comObj,
						  (jint) ghwndMain,
						  pObj->rc.top, pObj->rc.left, 
						  pObj->rc.bottom, pObj->rc.right);
      
      if (pObj->bObjOpenInWindow) {
	DrawShading(&(pObj->rc),
		    hDC,
		    OLEUI_SHADE_FULLRECT,
		    0);
    }
    }
}

void Print(HDC hDC)
{
    RECT rcPrint, rcApp;
    PNTWOBJ current;

    dprintf(2, "Print");

    /*  Set the bounding rectangle */
    rcPrint.left = rcPrint.top = 0;
    rcPrint.right = GetDeviceCaps(hDC, HORZRES);
    rcPrint.bottom = GetDeviceCaps(hDC, VERTRES);
    dprintf(3, " Print rect is %u by %u", rcPrint.right, rcPrint.bottom);

    /*  Do some stuff to set up the mapping mode and
     *  stretch the window image to fit the paper.
     *  This is  not the best we could do but its cheap and easy.
     *  We will us MM_ISOTROPIC to give an arb. scale factor
     *  but keep the aspect ratio the same. */
    SetMapMode(hDC, MM_ISOTROPIC);

    /*  Set the window extent to the size of the application main
     *  window. */
    GetClientRect(ghwndMain, &rcApp);
    SetWindowExtEx(hDC, rcApp.right - rcApp.left, rcApp.bottom - rcApp.top, NULL);

    /*  Set the viewport to the size of the paper */
    SetViewportExtEx(hDC, rcPrint.right, rcPrint.bottom, NULL);

    /*  Set up the printer */
    Escape(hDC, STARTDOC, lstrlen(gszAppName), (LPSTR)gszAppName, NULL);

    /*  Draw the image in the DC */
    current = gpObjList;
    while (current) {
	render_object(hDC, current);
	current = current->pNext;
    }

    /*  Tell the printer its the end of the page */
    Escape(hDC, NEWFRAME, 0, NULL, NULL);

    /*  Tell the printer its the end of the document */
    Escape(hDC, ENDDOC, 0, NULL, NULL);
}


/* Insert an object */
static PCOMOBJ internal_insert_object(CLSID* clsid, HWND hWnd)
{
    PCOMOBJ pObj;
    PNTWOBJ pRep;

    if (!clsid)
	return NULL;

    print_iid_info(NULL, PROGRESS, "clsid = ", clsid);

    pObj = insert_object_from_clsid(NULL, clsid, TRUE);
    if (pObj) {
	/*  Show the final embedded form */
	pRep = ntw_set_up_object(pObj, gptInsert.x, gptInsert.y,
				 DEFAULT_OBJ_WIDTH, DEFAULT_OBJ_HEIGHT);
	dprintf(2, "About to attempt to activate the object %x.", (long) pObj);
	Java_com_gensym_com_ActiveXProxy_activate_1object
	    (NULL, NULL, (jint) pObj, (jint) ghwndMain,
	     pRep->rc.top, pRep->rc.left, pRep->rc.bottom, pRep->rc.right, TRUE);
	dprintf(2, "Finished activating object.");
	InvalidateRect(hWnd, &(gpObjList->rc), TRUE);
	dprintf(2, "Finished with insert object");
    }
    return pObj;
}

void test_dispatch_stuff()
{
    PCOMOBJ pComObj;
    CLSID return_clsid;
    HRESULT hr;

    /* L"{8e27c92b-1264-101c-8a2f-040224009c02}" */
    /* L"{00020820-0000-0000-c000-000000000046}" */
    hr = CLSIDFromProgID(L"Excel.Chart", &return_clsid);
    if (FAILED(hr)) {
	AlertBox("Failed to get clsid from progid");
	return;
    }
    pComObj = internal_insert_object(&return_clsid, ghwndMain);
    update_cell(NULL, pComObj, 2, 2, 100);
}

/*  Process WM_COMMAND messages */
static void BucketCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) 
{
    switch (wParam) {
    case IDM_NEW:
	client_file_new(3);
	break;

    case IDM_OPEN:
	open_file(NULL);
	break;

    case IDM_SAVE:
	save();
	break;

    case IDM_SAVEAS:
	save_as();
	break;

    case IDM_PRINT:
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner = hWnd;
	pd.Flags = PD_RETURNDC;
	if (PrintDlg(&pd)) {
	    Print(pd.hDC);
	}
	DeleteDC(pd.hDC);
	if (pd.hDevMode) GlobalFree(pd.hDevMode);
	if (pd.hDevNames) GlobalFree(pd.hDevNames);
	break;

    case IDM_PRINTSETUP:
	memset(&pd, 0, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner = hWnd;
	pd.Flags = PD_PRINTSETUP;
	PrintDlg(&pd);
	break;

    case IDM_EXIT:
	PostMessage(hWnd, WM_CLOSE, 0, 0l);
	break;

    case IDM_CUT:
    case IDM_COPY:
    case IDM_PASTE:
    case IDM_DELETE:
	ClipCommand(hWnd, wParam);
	break;

    case IDM_INSERT_OBJECT:
	internal_insert_object(get_clsid_from_user((long) hWnd), hWnd);
	break;

    case IDM_DISPATCH_METHOD:
	test_dispatch_stuff();
	break;

    case IDM_BROWSE_LIBRARY:
	if (currentlySelected) {
	    /* Java_com_gensym_com_NativeMethodBroker_beanify_1object
		(NULL, NULL, (jint) currentlySelected->comObj); */
	} else {
	    Java_com_gensym_com_NativeMethodBroker_browse_1default_1library(NULL, NULL);
	}
	break;

    case IDM_HELPCONTENTS:
	Help(hWnd, (WORD) wParam);
	break;

    case IDM_ABOUT:
	About(hWnd);
	break;

#ifdef DEBUG
    case IDM_DEBUG0:
    case IDM_DEBUG1:
    case IDM_DEBUG2:
    case IDM_DEBUG3:
    case IDM_DEBUG4:
	ChangeDebugLevel((short)(wParam - IDM_DEBUG0));
	break;

    case IDM_DEBUGCLEAR:
	ClearDebugHistory();
	break;
#endif

    default:
	break;
    }
}

/*  Process WM_DRAWITEM and WM_MEASUREITEM messages */

static void MeasureItem(HWND hWnd, UINT uiCtl, LPMEASUREITEMSTRUCT lpMI)
{
    switch (uiCtl) {

    default:

	/*  Return the height of the system font */
	lpMI->itemHeight = gtmSysFont.tmHeight;
	break;
    }
}

static void DrawItem(HWND hWnd, UINT uiCtl, LPDRAWITEMSTRUCT lpDI)
{
    switch (uiCtl) {

    default:
	break;
    }
}

/*  Set the state of the edit menu items */
void InitClipMenu(HMENU hmenuPopup)
{
    BOOL bSel = FALSE;

    /*  See if there is anything we have that we might want the
     *  user to be able to copy to the clipboard */
    dprintf(3, "Inside InitClipMenu");
    bSel = !(!currentlySelected);

    if (bSel) {
	EnableMenuItem(hmenuPopup, IDM_CUT, MF_ENABLED);
	EnableMenuItem(hmenuPopup, IDM_COPY, MF_ENABLED);
	EnableMenuItem(hmenuPopup, IDM_DELETE, MF_ENABLED);
    } else {
	EnableMenuItem(hmenuPopup, IDM_CUT, MF_GRAYED);
	EnableMenuItem(hmenuPopup, IDM_COPY, MF_GRAYED);
	EnableMenuItem(hmenuPopup, IDM_DELETE, MF_GRAYED);
    }

    /*  See if there is anything in the Clipboard which
     *  we are capable of pasting */
    if (is_clipboard_format_available()) {
	ModifyMenu(hmenuPopup, IDM_PASTE, MF_BYCOMMAND, IDM_PASTE, "&Paste");
	EnableMenuItem(hmenuPopup, IDM_PASTE, MF_ENABLED);
    } else {
	/*  Nothing available so gray it out */
	ModifyMenu(hmenuPopup, IDM_PASTE, MF_BYCOMMAND, IDM_PASTE, "&Paste");
	EnableMenuItem(hmenuPopup, IDM_PASTE, MF_GRAYED);
    }
    dprintf(3, "Done with InitClipMenu");
}

/*  Process WM_INITMENUPOPUP messages */
static void InitMenuPopup(HMENU hmenuPopup, UINT uiIndex, BOOL bSystem)
{
    /*  See if there is anything in the clipboard which
     *  we should enable the Paste item for */

    InitClipMenu(hmenuPopup);
}


/*  Process WM_DROPFILES messages */
static void DropFiles(HWND hWnd, HDROP hDrop)
{
    UINT ui;
    char szName[_MAX_PATH];

    dprintf(2, "DropFiles");

    ui = DragQueryFile(hDrop, 0xFFFF, NULL, 0);
    if (ui == 0) {
	DragFinish(hDrop);
	return;
    }
    if (ui > 1)
	AlertBox("Only the first file will be opened");

    ui = DragQueryFile(hDrop, 0, szName, sizeof(szName));
    if (ui) {
	dprintf(3, "File: %s", (LPSTR)szName);
	open_file(szName);
    }
    DragFinish(hDrop);
}


/*  Draw a rubber band on a window */
static void DrawBand(HWND hWnd, LPRECT prc)
{
    HDC hDC;
    HBRUSH hbrNull, hbrOld;

    hDC = GetDC(hWnd);
    hbrNull = GetStockObject(NULL_BRUSH);
    hbrOld = SelectObject(hDC, hbrNull);
    SetROP2(hDC, R2_NOT);
    Rectangle(hDC,
	      prc->left, 
	      prc->top,
	      prc->right,
	      prc->bottom);
    SelectObject(hDC, hbrOld);
    ReleaseDC(hWnd, hDC);
}


/*  Test for a hit in an object
 *  We want the last one that hits in the list since this
 *  is the one most in front */
PNTWOBJ HitTestObj(int x, int y)
{
    PNTWOBJ pHitObj = NULL;
    PNTWOBJ current;
    POINT pt;

    pt.x = x;
    pt.y = y;
    current = gpObjList;
    while (current) {
	if (PtInRect(&(current->rc), pt)) {
	    pHitObj = current;
	}
	current = current->pNext;
    }

    return pHitObj;
}



/*  test for a hit in the size border */
UINT SizeBorderHitTestObj(int x, int y)
{
    PCOMOBJ pObj;
    PNTWOBJ pRep;

    pRep = HitTestObj(x, y);
    if (!pRep)
	return SB_HIT_NONE;
    else
	pObj = pRep->comObj;

    if (currentlySelected  != pRep)
	return SB_HIT_NONE;

    if ((x > pRep->rc.left) && (x < pRep->rc.left + SB_WIDTH)) return SB_HIT_LEFT;
    if ((x < pRep->rc.right) && (x > pRep->rc.right - SB_WIDTH)) return SB_HIT_RIGHT;

    if ((y > pRep->rc.top) && (y < pRep->rc.top + SB_WIDTH)) return SB_HIT_TOP;
    if ((y < pRep->rc.bottom) && (y > pRep->rc.bottom - SB_WIDTH)) return SB_HIT_BOTTOM;

    return SB_HIT_NONE;
}


void ntw_set_open(PCOMOBJ pObj)
{
    PNTWOBJ pRep;

    dprintf(3, "ntw set open");

    pRep = get_ntwobj_from_comobj(pObj);
    if (!pRep)
	AlertBox("Couldn't find matching object");
    else {
	dprintf(3, "Setting OpenInWindow of %x to %d", pRep, 1);
	pRep->bObjOpenInWindow = 1;
    }
}

void ntw_clear_open(PCOMOBJ pObj)
{
    PNTWOBJ pRep;

    dprintf(3, "ntw clear open");

    pRep = get_ntwobj_from_comobj(pObj);
    if (!pRep)
	AlertBox("Couldn't find matching object");
    else {
	dprintf(3, "Setting OpenInWindow of %x to %d", pRep, 0);
	pRep->bObjOpenInWindow = 0;
    }
}

void ntw_force_redraw(PCOMOBJ pObj)
{
    dprintf(3, "ntw force redraw");

    InvalidateRect(ghwndMain, &(get_ntwobj_from_comobj(pObj)->rc), TRUE);
}



void Paint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
    PNTWOBJ current;

    /*  Walk down the object list, rendering the objects */
    current = gpObjList;
    while (current) {
	dprintf(4, "Rendering object %x", (int) current);
	render_object(lpPS->hdc, current);
	current = current->pNext;
    }

    /*  Show where the insertion point is */
    SetROP2(lpPS->hdc, R2_NOT);
    MoveToEx(lpPS->hdc, gptInsert.x - 10, gptInsert.y, NULL);
    LineTo(lpPS->hdc, gptInsert.x + 10, gptInsert.y);
    MoveToEx(lpPS->hdc, gptInsert.x, gptInsert.y - 10, NULL);
    LineTo(lpPS->hdc, gptInsert.x, gptInsert.y + 10);

}



LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    static PCOMOBJ pDragObj;
    static PNTWOBJ pDragRep;
    static BOOL bCaptured;
    static RECT rcBand;
    static int dx, dy;
    static UINT uiBorderHit;
    static HCURSOR hcurOld = NULL;
    HCURSOR hcurSize;

    switch(msg) {
    case WM_CLOSE:
	if (PromptToSave())
	    DestroyWindow(ghwndMain);
	return 0; /*  say we handled the message */

    case WM_DESTROY:
	Java_com_gensym_com_ActiveXProxy_shut_1down(NULL, NULL);
	/* Java_com_gensym_com_NativeMethodBroker_terminate(NULL, NULL, (jint) ghwndMain); */
	PostQuitMessage(0);
	break;

    case WM_CREATE:
	BucketCreate(hWnd, (LPCREATESTRUCT)lParam);
	break;

    case WM_MOVE:
	Move(hWnd, LOWORD(lParam), HIWORD(lParam));
	break;

    case WM_SIZE:
	Size(hWnd, LOWORD(lParam), HIWORD(lParam));
	break;

    case WM_COMMAND:
	BucketCommand(hWnd, wParam, lParam); 
	break;

    case WM_MEASUREITEM:
	MeasureItem(hWnd, (UINT)wParam, (LPMEASUREITEMSTRUCT)lParam);
	return (LRESULT) TRUE;

    case WM_DRAWITEM:
	DrawItem(hWnd, (UINT)wParam, (LPDRAWITEMSTRUCT) lParam);
	break;

    case WM_LBUTTONDOWN:

	/*  See if we hit an object and if we did then  */
	/*  bring the object to the top, select it */
	/*  and set up the rubber band for a drag or resize operation */
	pDragRep = HitTestObj(LOWORD(lParam), HIWORD(lParam));
	if (pDragRep) {
	    pDragObj = pDragRep->comObj;
	    set_selected(pDragRep);
	    dprintf(2, "COMOBJ hit");
	    SetCapture(hWnd);
	    bCaptured = TRUE;
	    BringObjToTop(pDragObj);
	    rcBand = pDragRep->rc;
	    dx = LOWORD(lParam) - rcBand.left;
	    dy = HIWORD(lParam) - rcBand.top;
	    DrawBand(hWnd, &rcBand);
	} else
	    deselect();
	/*  drop throughbreak; */

    case WM_MOUSEMOVE:
	if (!bCaptured) {
    	    /*  Test to see if mouse is over a resize region */
	    uiBorderHit = SizeBorderHitTestObj(LOWORD(lParam), 
					       HIWORD(lParam));
	}

	switch (uiBorderHit) {
	case SB_HIT_TOP:
	case SB_HIT_BOTTOM:
	    hcurSize = LoadCursor(NULL, IDC_SIZENS);
	    hcurOld = SetCursor(hcurSize);
	    break;
	case SB_HIT_LEFT:
	case SB_HIT_RIGHT:
	    hcurSize = LoadCursor(NULL, IDC_SIZEWE);
	    hcurOld = SetCursor(hcurSize);
	    break;
	default:
	    if (hcurOld) {
		SetCursor(hcurOld);
		hcurOld = NULL;
	    }
	}
	if (bCaptured) {
	    int w, h;

	    DrawBand(hWnd, &rcBand);
	    switch (uiBorderHit) {
	    case SB_HIT_LEFT:
		rcBand.left = LOWORD(lParam);
		break;
	    case SB_HIT_RIGHT:
		rcBand.right = LOWORD(lParam);
		break;
	    case SB_HIT_TOP:
		rcBand.top = HIWORD(lParam);
		break;
	    case SB_HIT_BOTTOM:
		rcBand.bottom = HIWORD(lParam);
		break;
	    default:
		w = rcBand.right - rcBand.left;
		rcBand.left = LOWORD(lParam) - dx;
		rcBand.right = rcBand.left + w;
		h = rcBand.bottom - rcBand.top;
		rcBand.top = HIWORD(lParam) - dy;
		rcBand.bottom = rcBand.top + h;
		break;
	    }
	    DrawBand(hWnd, &rcBand);
	}
	break;

    case WM_LBUTTONUP:

	/*  Set the insertion point to where the mouse click occured */
	/*  If we are in the captured state, update the object */
	/*  position and release the capture. Then redraw everything */
	
	gptInsert.x = LOWORD(lParam);
	gptInsert.y = HIWORD(lParam);

	if (bCaptured) {
	    ReleaseCapture();
	    bCaptured = FALSE;
	    pDragRep->rc = rcBand;
	}
	InvalidateRect(hWnd, NULL, TRUE);

	break;

    case WM_LBUTTONDBLCLK:
    {
	PNTWOBJ pHitObj;

	pHitObj = HitTestObj(LOWORD(lParam), HIWORD(lParam));
	if (pHitObj) {
	    Java_com_gensym_com_ActiveXProxy_activate_1object
		(NULL, NULL, (jint) pHitObj->comObj, (jint) ghwndMain,
		 pHitObj->rc.top, pHitObj->rc.left, pHitObj->rc.bottom,
		 pHitObj->rc.right, JNI_TRUE);
	}
    }
    break;

    case WM_PAINT:
	BeginPaint(hWnd, &ps);
	Paint(hWnd, &ps);
	EndPaint(hWnd, &ps);
	break;

    case WM_INITMENUPOPUP:
	InitMenuPopup((HMENU)wParam, LOWORD(lParam), (BOOL)HIWORD(lParam));
	break;

    case WM_DROPFILES:
	DropFiles(hWnd, (HDROP)wParam);
	break;

    default:
	return DefWindowProc(hWnd, msg, wParam, lParam);
	break;
    }
    /*  dprintf(4, "Finished callback function"); */
    return (LRESULT) NULL;
}

BOOL InitInstance(HANDLE hInstance, int cmdShow)
{
    HDC hDC;
    WNDCLASS wc;


    dprintf(3, "InitInstance");
    
    /*  define the class of window we want to register */
    wc.lpszClassName    = gszAppName;
    wc.style            = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APP));
    wc.lpszMenuName     = "Menu";
    wc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = MainWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    
    if (!RegisterClass(&wc)) {
	return FALSE;
    }

    /*  Get any system metrics we use a lot */
    hDC = GetDC(NULL);  /*  get a DC */
    GetTextMetrics(hDC, &gtmSysFont);
    ReleaseDC(NULL, hDC);

    /*  Create the main window */
    ghwndMain = CreateWindow(gszAppName,
			     gszAppName,
			     WS_OVERLAPPEDWINDOW,
			     CW_USEDEFAULT,
			     0,
			     GetSystemMetrics(SM_CXSCREEN) / 2,
			     GetSystemMetrics(SM_CYSCREEN) / 2,
			     (HWND)NULL,
			     (HMENU)NULL,
			     hInstance,
			     (LPSTR)NULL);
    
    if (!ghwndMain) {
	return FALSE;
    }
    ShowWindow(ghwndMain, cmdShow);
    UpdateWindow(ghwndMain);

    set_up_container_callbacks(&ntw_set_open, &ntw_clear_open, &ntw_force_redraw,
			       (long) ghwndMain);
    container_setup(NULL, gszAppName, (long) ghAppInstance);
    client_file_new(3);
    Java_com_gensym_com_ActiveXProxy_start_1up(NULL, NULL);
    return TRUE;
}


/*  Entry point */
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;

    (void) lpszCmdLine;

    ghAppInstance = hInstance;

    C_setDebugLevel(NULL, 4);
    dprintf(2, "Starting bucket: cmdShow = %d", cmdShow);

    /*  Do the per instance initialization */
    if (!InitInstance(hInstance, cmdShow))
	return 1;

    /*  Load the accelerator table */
    dprintf(2, "About to try to load accelerators");
    ghAccTable = LoadAccelerators(hInstance, "AccTable");
    if (!ghAccTable) {
	dprintf(2, "Error: Could not load accelerator table.");
	return FALSE;
    }
    gptInsert.x = 20;
    gptInsert.y = 10;

    /* Start by inserting an object (hack to expedite testing) */
    test_dispatch_stuff();

    /*  Check for messages from Windows and process them.
     *  If we have nothing else to do, maybe perform some idle function
     */
    do {
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
	    /*  got a message to process
	     * 
	     *  dprintf(4, "Got a message to process."); 
	     */
	    if (msg.message == WM_QUIT) {
		dprintf(3, "Got a WM_QUIT message");
		break;
	    }
	    /*  Do the accelerator thing */
	    if (!TranslateAccelerator(ghwndMain, ghAccTable, &msg)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	    }
	} else {
	    /*  perform some idle routine or just give up so Windows
	     *  can run till our next message.
	     */
	    WaitMessage();
	}
    } while (1);
    return (msg.wParam);
}



#else /* WIN32 */

int main (int argc, char **argv) {}

#endif /* WIN32 */
