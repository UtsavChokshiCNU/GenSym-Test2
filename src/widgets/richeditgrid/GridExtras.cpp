/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      GridExtras.cpp
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2005 - 2006      hgoddard, jv, fmw
+
+ Description:  Gensym wrapper around grid-view control
+               http://www.codeproject.com/miscctrl/gridctrl.asp
+
+ Key:
+   (obsolete)
+
+ File Organization:
+   Section:      INCLUDE FILES
+   Section:      DEFINES
+   Section:      GLOBALS
+   Section:      FUNCTION GROUP
+
+ External Interface:
+   g2pvt_create_rich_edit_grid
+   g2ext_specify_grid_view_cells
+   g2ext_manage_grid_view
+   g2pvt_cell_value_of_last_gv_edit
+   g2pvt_grid_view_check_box_clicked
+   g2pvt_grid_view_on_wm_notify
+
+ Dependencies:
+   g2pvt_gprintf
+   g2pvt_find_dialog_by_id (g2ext_specify_grid_view_cells, g2ext_manage_grid_view)
+   g2pvt_get_control_cwnd (g2ext_manage_grid_view, on_bn_clicked)
+   g2pvt_lookup_control_by_id (g2ext_specify_grid_view_cells)
+   g2pvt_parse_date_time_value (DoTimeCell)
+   g2pvt_get_native_icon (DoIconCell)
+   g2pvt_ddlg_respond (g2pvt_grid_view_on_wm_notify, on_bn_clicked)
+
+ Notes:
+
+ Modifications:
+   usage: All modifications to this file should be listed here, with most
+          recent first. In general, modification comments should merely
+          provide a reference to a detailed modification comment in the
+          appropriate section/function header.
+
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef UNICODE
#  define UNICODE
#endif

#ifndef _UNICODE
#  define _UNICODE
#endif

#include "stdafx.h"
#include "MemDC.h"
#include "GridCtrl.h"
#include "GridCellBase.h"
#include "GridCellCheck.h"
#include "GridCellDuration.h"
#include "GridCellCombo.h"
#include "GridCellCheck.h"
#include "GridCellDateTime.h"
#include "GridCellNumeric.h"
#include "GridCellInteger.h"
#include "GridCellSpinner.h"
#include "GridCellEllipsis.h"
#include "GridCellImage.h"
#include "GridCellFormattedDate.h"

#include "GridExtras.h"
#include "cprim.h"
#include "msincls.h"
#include "dyndlgs.h"

#include "..//..//..//twng//c//PropertyDlg.h"

#include <time.h>

// Copied form ext/c/graphics.h
#define GENSYM_GRID_VIEW 844

// Grid-view event codes. Sync with LISP grid-view-event-name.
#define GRID_VIEW_SELECTION_CHANGED 1

extern "C" XCOLOR XMetaColorArray[];

extern "C" GENSYMDIALOG *g2pvt_find_dialog_by_id (long);
extern "C" HIMAGELIST g2pvt_get_image_list(int);
extern "C" int g2pvt_icon_index(int);
extern "C" CONTROLITEM *g2pvt_lookup_control_by_id (int, GENSYMDIALOG *);
extern "C" long g2pvt_send_user_gesture_to_g2 (HWND hwndParent, CONTROLITEM *pControl,
                                               int row, int col, UINT code, UINT keycode);
extern "C" UINT g2pvt_compute_gensym_keycode(UINT vKey, UINT scanCode);

extern "C" void g2pvt_trace(char *fmt, ...);
extern "C" void g2pvt_printf(char *fmt, ...);
#define PRINTF g2pvt_trace

extern wchar_t *g2pvt_parse_date_time_value (SYSTEMTIME *systime, TCHAR *pszText);
extern void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode);
extern CWnd *g2pvt_get_control_cwnd (long controlId, HWND hwndDlg);
extern wchar_t *g2pvt_g2_to_windows_text(wchar_t *);
extern BOOL g2pvt_is_multiline_string(LPCWSTR string);


static TCHAR *$NumericChars= _T("0123456789");


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef GV_DEBUG
#  define _REPORT_SAFE_STRINGS
#  define GTRACE g2pvt_trace
#else
#  define GTRACE 1 ? (void)0 : printf
#endif

#ifdef _REPORT_SAFE_STRINGS
TCHAR g_szTempBuf[20];
#  define ZERO_MEM_NEG_ERR(ntbl,nltz) zero_mem_neg_num_error(ntbl, nltz)
#  define COPY_NEG_NUM_ERR(ntbl,nltm) copy_neg_num_error(ntbl, nltm)
#  define ZERO_MEM_BUF_ERR(pdb) zero_mem_invalid_buffer(pdb)
#  define COPY_INVALID_PTR_ERR(pdb,psb) copy_invalid_ptr_error(pdb, psb)
#  define COPY_BUFFER_TOO_SMALL_ERR(psb) copy_buffer_too_small_error(psb)
#  define COPY_SUCCEEDED_MSG(psb) copy_succeeded_message(psb)
#else
#  define ZERO_MEM_NEG_ERR(ntbl,nltz)
#  define COPY_NEG_NUM_ERR(ntbl,nltm)
#  define ZERO_MEM_BUF_ERR(pdb)
#  define COPY_INVALID_PTR_ERR(pdb,psb)
#  define COPY_BUFFER_TOO_SMALL_ERR(psb)
#  define COPY_SUCCEEDED_MSG(psb)
#endif


IMPLEMENT_DYNCREATE(CGensymGridCtrl, CGridCtrl)

BEGIN_MESSAGE_MAP(CGensymGridCtrl, CGridCtrl)
 ON_WM_KEYDOWN()
 ON_WM_SYSKEYDOWN()
 ON_WM_CHAR()
END_MESSAGE_MAP()


#ifdef GV_DEBUG1
void output_grid(CGensymGridCtrl *pGrid, CString str)
{
        int i;
        int j;
        int nCol;
        CString DBString;
        TCHAR wColIdx[10];
        CString myString;
    char temp[20];

        OutputDebugString(_T("\n"));

    str =  _T("***") + str;
	str += _T("***");
	OutputDebugString(str);
 	OutputDebugString(_T("\n"));
	OutputDebugString(_T("\n"));

    int nCols = pGrid->GetColumnCount();
        for (i = 0; i < pGrid->GetRowCount(); i++)
        {
            DBString = _T("G2 Row Idx: "); 

        itoa(pGrid->ConvertIdxTwngToG2(i), temp, 10);
        DBString += temp;
                DBString += _T(" ");

            DBString += _T("... Last TWNG Sorted Column: "); 

                nCol = pGrid->GetSortColumn();
                
        _itot(nCol, wColIdx, 10);

                DBString += wColIdx;

                DBString += _T(" value: ");
        
            
                for (j = 0; j < nCols; j++)
                {
                        DBString += _T(" | ");
                
                        myString = pGrid->GetItemText(i, j);
                        if (myString.IsEmpty())
                                myString = _T("nill");
                        DBString += myString;
                }

        DBString += _T("\n");
        DBString += _T(" ");
        DBString += _T("\n");
                OutputDebugString(DBString);
        }
  
}
#endif

#ifdef _REPORT_SAFE_STRINGS
static void zero_mem_neg_num_error (int nTotalBufLen, int nLenToZero)
{
  OutputDebugString(_T("SafeZeroMemory Failed:\n"));
  OutputDebugString(_T("Len <= 0 Len\n"));
  OutputDebugString(_T("total buffer len :"));
  _itow(nTotalBufLen, g_szTempBuf, 10);
  OutputDebugString(g_szTempBuf);
  OutputDebugString(_T("\n"));

  OutputDebugString(_T("nLenToZero :"));
  _itow(nLenToZero, g_szTempBuf, 10);
  OutputDebugString(g_szTempBuf);
  OutputDebugString(_T("\n"));
}

static void copy_neg_num_error (int nTotalBufLen, int nLenToMove)
{
  OutputDebugString(_T("SafeCopy Failed:\n"));
  OutputDebugString(_T("Len <= 0 Len\n"));
  OutputDebugString(_T("total buffer len :"));
  _itow(nTotalBufLen, g_szTempBuf, 10);
  OutputDebugString(g_szTempBuf);
  OutputDebugString(_T("\n"));

  OutputDebugString(_T("nLenToMove :"));
  _itow(nLenToMove, g_szTempBuf, 10);
  OutputDebugString(g_szTempBuf);
  OutputDebugString(_T("\n"));
}

static void zero_mem_invalid_buffer (int pDestBuf)
{
  OutputDebugString(_T("SafeZeroMemory Failed:\n"));

  OutputDebugString(_T("Invalid Pointer\n"));
  OutputDebugString(_T("Destination Buffer :"));

  _itow(pDestBuf, g_szTempBuf, 16);
  OutputDebugString(g_szTempBuf);

  OutputDebugString(_T("\n"));
}

static void copy_invalid_ptr_error (int pDestBuf, int pSrcBuf)
{
  OutputDebugString(_T("SafeCopy Failed:\n"));

  OutputDebugString(_T("Invalid Pointer\n"));
  OutputDebugString(_T("Destination Buffer :"));

  _itow(pDestBuf, g_szTempBuf, 16);
  OutputDebugString(g_szTempBuf);

  OutputDebugString(_T("\n"));
  OutputDebugString(_T("Source Buffer :"));

  _itow(pSrcBuf, g_szTempBuf, 16);
  OutputDebugString(g_szTempBuf);

  OutputDebugString(g_szTempBuf);
  OutputDebugString(_T("\n"));
}

static void copy_buffer_too_small_error (TCHAR *pszSrcBuf)
{
  OutputDebugString(_T("SafeCopy Failed  - String too long:\n"));
  OutputDebugString(pszSrcBuf);
  OutputDebugString(_T("\n"));
}

static void copy_succeeded_message (TCHAR *pszSrcBuf)
{
  OutputDebugString(_T("SafeCopy Succeeded:\n"));
  OutputDebugString(pszSrcBuf);
  OutputDebugString(_T("\n"));
}

#endif


static CList<CGensymGridCtrl*,CGensymGridCtrl*> g_GridViews;

/*****************************************************************************
* PostNcDestroy
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments:None
*   Returns: None
*   Notes: Cleans up memory leaks. Caller nolonger has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/

void CGensymGridCtrl::PostNcDestroy() 
{
        CGridCtrl::PostNcDestroy();

        delete this;
}


/*****************************************************************************
* CGensymGridCtrl constructor
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CGensymGridCtrl::CGensymGridCtrl(int nScrollRows, int nScrollCols, int nFixedRows,
                                 int nFixedCols): CGridCtrl(nScrollRows, nScrollCols,
                                 nFixedRows, nFixedCols)
{
  lSizeOfReturnBuf = 0;
  m_dialogID = 0;
  m_consumedKey = FALSE;
  g_GridViews.AddTail(this);
}


/*****************************************************************************
* CGensymGridCtrl destructor
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CGensymGridCtrl::~CGensymGridCtrl()
{
  POSITION pos = g_GridViews.Find(this);
  ASSERT(pos);
  if(pos)
	g_GridViews.RemoveAt(pos);
}

//
// Keyboard Events
//

void CGensymGridCtrl::OnKeyDown(UINT vKey, UINT nRepCnt, UINT scanCode)
{
  if(!SendKeyToG2(vKey, scanCode))
    CGridCtrl::OnKeyDown(vKey, nRepCnt, scanCode);
}

void CGensymGridCtrl::OnSysKeyDown(UINT vKey, UINT nRepCnt, UINT scanCode)
{
  if(!SendKeyToG2(vKey, scanCode))
    CGridCtrl::OnSysKeyDown(vKey, nRepCnt, scanCode);
}

void CGensymGridCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  if(!m_consumedKey)
    CGridCtrl::OnChar(nChar, nRepCnt, nFlags);
  m_consumedKey = FALSE;
}

BOOL CGensymGridCtrl::G2WantsKey(UINT vKey, UINT scanCode)
{
  BOOL ctrl = (GetKeyState(VK_CONTROL) < 0);
  BOOL shift = (GetKeyState(VK_SHIFT) < 0);

  // All navigation keys go to the grid view.
  if(vKey==VK_UP || vKey==VK_DOWN || vKey==VK_LEFT || vKey==VK_RIGHT ||
	 vKey==VK_HOME || vKey==VK_END || vKey==VK_TAB || vKey==VK_PRIOR || vKey==VK_NEXT)
	return FALSE;

  // As do clipboard keys
  if((ctrl && !shift && (vKey == 'A' || vKey == 'X' || vKey == 'C' || vKey == 'V')) ||
	 (!ctrl && shift && (vKey == VK_INSERT)))
	return FALSE;

  // All function keys go to G2.
  if((0 <= vKey && vKey <= VK_HELP) ||
     (VK_NUMPAD0 <= vKey && vKey <= VK_F24) ||
     (VK_ATTN <= vKey))
    return TRUE;

  // And printing chars, only if control modifier.
  return ctrl;
}

BOOL CGensymGridCtrl::SendKeyToG2(UINT vKey, UINT scanCode)
{
  UINT g2key;

  if(G2WantsKey(vKey, scanCode) &&
     (g2key = g2pvt_compute_gensym_keycode(vKey, scanCode))) {

	GENSYMDIALOG *pDialog = g2pvt_find_dialog_by_id(m_dialogID);
	if (pDialog == NULL)
	  return FALSE;

	CONTROLITEM *pControl = g2pvt_lookup_control_by_id(GetDlgCtrlID(), pDialog);
	if (pControl == NULL)
	  return FALSE;

    g2pvt_send_user_gesture_to_g2(pDialog->hwnd, pControl,
                                  G2Row(GetFocusCell().row),
                                  G2Column(GetFocusCell().col),
                                  0, g2key);
    m_consumedKey = TRUE;
    return TRUE;
  }
  return FALSE;
}


//
// Misc Utilities
//

void CGensymGridCtrl::SetItemBold(int row, int col, BOOL bold)
{
  const LOGFONT *pLF = GetItemFont(row, col);
  if(!pLF) return;				// Never happens, I think. 
  LOGFONT lf = *pLF;
  lf.lfWeight = bold ? FW_BOLD : FW_NORMAL;
  SetItemFont(row, col, &lf);
}


//
// Dynamic icon support
//

extern "C"
void g2pvt_refresh_grid_view_icon(int native_icon)
{
  POSITION pos;
  for(pos=g_GridViews.GetHeadPosition(); pos; g_GridViews.GetNext(pos))
	g_GridViews.GetAt(pos)->IconChanged(native_icon);
}

#define RefreshImageCell(row, col, iconIndex) \
 if(GetCell(row, col)->GetImage() == iconIndex) InvalidateCellRect(row, col)

void CGensymGridCtrl::IconChanged(int native_icon)
{
  int row, col;
  int iconIndex = g2pvt_icon_index(native_icon);

  CCellID idTopLeft = GetTopleftNonFixedCell();
  int minVisibleRow = idTopLeft.row;
  int minVisibleCol = idTopLeft.col;

  CCellRange VisCellRange = GetVisibleNonFixedCellRange();
  int maxVisibleRow = VisCellRange.GetMaxRow();
  int maxVisibleCol = VisCellRange.GetMaxCol();

  // Fixed rows and columns
  for(row=0; row<GetFixedRowCount(); row++)
	for(col=0; col<GetFixedColumnCount(); col++)
	  RefreshImageCell(row, col, iconIndex);

  // Fixed rows
  for(row=0; row<GetFixedRowCount(); row++)
	for(col=minVisibleCol; col<maxVisibleCol; col++)
	  RefreshImageCell(row, col, iconIndex);

  // Fixed columns
  for(col=0; col<GetFixedColumnCount(); col++)
	for(row=minVisibleRow; row<=maxVisibleRow; row++)
	  RefreshImageCell(row, col, iconIndex);

  // Interior
  for(row=minVisibleRow; row<=maxVisibleRow; row++)
	for(col=minVisibleCol; col<=maxVisibleCol; col++)
	  RefreshImageCell(row, col, iconIndex);
}

//
// Logical/physical row support
//

void CGensymGridCtrl::InitializeRowTags()
{
  int i, nFixed = GetFixedRowCount();
  for(i=nFixed; i<GetRowCount(); i++)
    SetRowTag(i, i-nFixed);
}

int CGensymGridCtrl::G2RowCount()
{
  return GetRowCount() - GetFixedRowCount();
}

int CGensymGridCtrl::PhysicalRow(int G2row)
{
  if(G2row<0 || G2row >= G2RowCount())
    return -1;

  return FindRow(G2row);
}

int CGensymGridCtrl::G2Row(int row)
{
  return GetRowTag(row);
}

int CGensymGridCtrl::PhysicalColumn(int G2col)
{
  if(G2col < 0 || G2col >= G2ColumnCount())
    return -1;
  return G2col + GetFixedColumnCount();
}

int CGensymGridCtrl::G2Column(int col)
{
  if(col < GetFixedColumnCount() || col > GetColumnCount())
    return -1;
  return col - GetFixedColumnCount();
}

int CGensymGridCtrl::G2ColumnCount()
{
  return GetColumnCount() - GetFixedColumnCount();
}

void CGensymGridCtrl::GensymInsertRow(LPCTSTR strHeading, int G2row)
{
  int i, row = PhysicalRow(G2row);

  // Increment all tags above insert point.
  for(i=GetFixedRowCount(); i<GetRowCount(); i++)
    if(G2Row(i) >= G2row)
      SetRowTag(i, G2Row(i)+1);

  row = InsertRow(strHeading, row);
  SetRowTag(row, G2row);
}

BOOL CGensymGridCtrl::GensymDeleteRow(int G2row)
{
  int i, row = PhysicalRow(G2row);

  if(row<0)
    return FALSE;

  if(!DeleteRow(row))
    return FALSE;

  // Decrement all tags above deletion point.
  for(i=GetFixedRowCount(); i<GetRowCount(); i++)
    if(G2Row(i) >= G2row)
      SetRowTag(i, G2Row(i)-1);

  return TRUE;
}

void CGensymGridCtrl::GensymInsertColumn(LPCTSTR strHeading, int G2col)
{
  int col = PhysicalColumn(G2col);
  UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
  col = InsertColumn(strHeading, nFormat, col);
}

BOOL CGensymGridCtrl::GensymDeleteColumn(int G2col)
{
  int col = PhysicalColumn(G2col);

  if(col<0)
    return FALSE;

  if(!DeleteColumn(col))
    return FALSE;

  return TRUE;
}

// Attempt to cast the current selection into a small list of rectangles
// ("Areas") and pack the result into a wide string (yuck) in the form of
// null-terminated a sequence of LTRB values, each 16bits and offset by 1.

// Converting a set of cells into a minimal rectangular cover is apparently
// NP-hard. See, eg,

//  Kumar, Anil VS and Ramesh, H (2003) Covering Rectilinear Polygons with
//  Axis-Parallel Rectangles. SIAM Journal on Computing 32(6):pp. 1509-1541.
//  http://eprints.iisc.ernet.in/archive/00000307/

// So we just handle a few simple cases: a single rectangle, a set of entire
// rows, or a set of entire columns.  The right way to do this is to modify
// CGridCtrl so that we can capture individual restangular selection
// events. -fmw, 7/26/06

static void AppendRect(CString& str, int minrow, int mincol, int maxrow, int maxcol)
{
  str += (WCHAR)(minrow+1);
  str += (WCHAR)(mincol+1);
  str += (WCHAR)(maxrow+1);
  str += (WCHAR)(maxcol+1);
}

void CGensymGridCtrl::GetPackedSelection(int& G2row, int& G2col, CString& str)
{
  int nrows = G2RowCount();
  int ncols = G2ColumnCount();
  int minRow = 65536, maxRow = -1;
  int minCol = 65536, maxCol = -1;
  int gr, gc;
  CArray<int,int> entireRows, entireCols;
  CCellID cell;
  DWORD key;
  POSITION pos;

  entireRows.SetSize(nrows);
  entireCols.SetSize(ncols);

  for(pos = m_SelectedCellMap.GetStartPosition(); pos; ) {
    m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);
    if(IsValid(cell)) {
      gr = G2Row(cell.row);
      gc = G2Column(cell.col);
      if(gr >= 0 && gc >= 0) {
	minRow = min(minRow,gr);
	maxRow = max(maxRow,gr);
	minCol = min(minCol,gc);
	maxCol = max(maxCol,gc);
	entireRows[gr]++;
	entireCols[gc]++;
      }
    }
  }

  // Return the focus cell, if exists, else the left-top-most cell in the
  // selection, if exists, else -1.
  cell = GetFocusCell();
  G2row = cell.row >= 0 ? G2Row(cell.row) : (minRow < 65536) ? minRow : -1;
  G2col = cell.col >= 0 ? G2Column(cell.col) : (minCol < 65536) ? minCol : -1;

  str.Empty();
  if(GetSelectedCount() == 0) {
  } else if(GetSelectedCount() == ((maxRow-minRow+1) * (maxCol-minCol+1))) {
    AppendRect(str, minRow, minCol, maxRow, maxCol);
  } else {
    for(gr=0; gr<entireRows.GetSize(); gr++)
      if(entireRows[gr] == ncols)
	AppendRect(str, gr, 0, gr, ncols-1);

    for(gc=0; gc<entireCols.GetSize(); gc++)
      if(entireCols[gc] == nrows)
	AppendRect(str, 0, gc, nrows-1, gc);

    for(pos = m_SelectedCellMap.GetStartPosition(); pos; ) {
      m_SelectedCellMap.GetNextAssoc(pos, key, (CCellID&)cell);
      if(IsValid(cell)) {
	gr = G2Row(cell.row);
	gc = G2Column(cell.col);
	if(gr >= 0 && gc >= 0 && entireRows[gr] != ncols && entireCols[gc] != nrows)
	  AppendRect(str, gr, gc, gr, gc);
      }
    }
  }
}

BOOL CGensymGridCtrl::SelectionChanged(NM_GRIDVIEW *pGH, int dialogId, int controlId)
{
  GENSYMDIALOG *pDlg = g2pvt_find_dialog_by_id(dialogId);
  int dialogHandle = pDlg ? pDlg->g2_id : 0;
  int G2row, G2col;
  CString packed = "";

  GetPackedSelection(G2row, G2col, packed);

  // NOTE: Really sending a dialog event here.
  g2pvt_fire_control_event(GENSYM_GRID_VIEW, dialogHandle, 
			   GRID_VIEW_SELECTION_CHANGED,
			   controlId, G2row, G2col,
			   (LPCWSTR)packed);
  return TRUE;
}

// GENSYMCID-922: GDU dialog sizing inconsistent within grid view
// Overload methods from CGridCtrl and apply MapDialogRect. --binghe, 2013/01/21

BOOL CGensymGridCtrl::SetRowHeight(int nRow, int height)
{
    CRect r(0, 0, 0, height);
    ::MapDialogRect(GetParent()->GetSafeHwnd(), &r);
    return CGridCtrl::SetRowHeight(nRow, r.Height());
}

BOOL CGensymGridCtrl::SetColumnWidth(int nCol, int width)
{
    CRect r(0, 0, width, 0);
    ::MapDialogRect(GetParent()->GetSafeHwnd(), &r);
    return CGridCtrl::SetColumnWidth(nCol, r.Width());
}

int CGensymGridCtrl::GetScrollPos(int nBar)
{
    return GetScrollPos32(nBar, TRUE);
}

BOOL CGensymGridCtrl::SetScrollPos(int nBar, int nPos)
{
    return SetScrollPos32(nBar, nPos);
}

/*****************************************************************************
* BOOL SafeZeroMemory (TCHAR *pszDestBuf, int nTotalBufLen, int nLenToZero)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL SafeZeroMemory (TCHAR *pszDestBuf, int nTotalBufLen, int nLenToZero)
{
  if ((0 >= nTotalBufLen) || (0 >= nLenToZero))
  {
    ZERO_MEM_NEG_ERR(nTotalBufLen, nLenToZero);
    return FALSE;
  }

  if (0 >= pszDestBuf)
  {
    ZERO_MEM_BUF_ERR(int(pszDestBuf));
    return FALSE;
  }

  _tcsnset(pszDestBuf, 0x00, nLenToZero);
  return TRUE;
}


/*****************************************************************************
* BOOL SafeCopy (TCHAR *pszDestBuf, int nTotalBufLen, TCHAR *pszSrcBuf,
*                int nLenToMove)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL SafeCopy (TCHAR *pszDestBuf, int nTotalBufLen, TCHAR *pszSrcBuf,
                      int nLenToMove)
{
  if ((0 >= nTotalBufLen) || (0 >= nLenToMove))
  {
    COPY_NEG_NUM_ERR(nTotalBufLen, nLenToMove);
    return FALSE;
  }

  if ((0 >= pszDestBuf) || (0 >= pszSrcBuf))
  {
    COPY_INVALID_PTR_ERR(int(pszDestBuf), int(pszSrcBuf));
    return FALSE;
  }

  if (nLenToMove > nTotalBufLen)
  {
    COPY_BUFFER_TOO_SMALL_ERR(pszSrcBuf);
    return FALSE;
  }

  _tcsncpy(pszDestBuf, pszSrcBuf, nLenToMove);
  COPY_SUCCEEDED_MSG(pszSrcBuf);
  return TRUE;
}


/*****************************************************************************
* TCHAR *char_to_TCHAR (char *pInput)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static TCHAR *char_to_TCHAR (char *pInput)
{
  int  nCodePage = CP_ACP;
  DWORD dwFlags  = MB_PRECOMPOSED |MB_ERR_INVALID_CHARS;
  int nRet;
  unsigned short nCount = strlen(pInput);
  static TCHAR GridExtrasTextOutput[MAX_PATH];

  // use static buffer
  memset(GridExtrasTextOutput, 0, sizeof(GridExtrasTextOutput));
  nRet = MultiByteToWideChar(nCodePage, dwFlags, pInput, nCount,
    GridExtrasTextOutput, nCount + SZTL);
  if (0 == nRet)
  {
    GridExtrasTextOutput[0] = 0;
    return GridExtrasTextOutput;
  }
  return GridExtrasTextOutput;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Creating the CRichGridItems
%
% Description: the code in this section is used to instantiate the CRichGridItem
%   objects, and fill them with data, as specified by the strings sent from G2.
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
* COLORREF GetColorVal (TCHAR *lpszColor)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static COLORREF GetColorVal (TCHAR *lpszColor)
{
  int i;
  COLORREF nColorValue = 0;

  for (i=0; i<TOTAL_NUMBER_OF_COLORS; i++)
  {
    if (0 == _tcscmp(lpszColor, char_to_TCHAR(XMetaColorArray[i].szColor)))
    {
      nColorValue = XMetaColorArray[i].rgbColor;
      return nColorValue;
    }
  }
  return nColorValue;
}


/*****************************************************************************
* void DoEllipsisCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description: ctEllipsis
*   Input Arguments:
*   Returns:
*   Notes:
*    The Ellipsis Icon will not display if the grid cell is not as
*     large as it is.
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoEllipsisCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
}


/*****************************************************************************
* void DoTextCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoTextCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
}


/*****************************************************************************
* void DoIconCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description: ctIcon is handled differently.  it is an option already
*                built in to the grid cell.  All we have to do is
*                give the cell the handle to the correct Icon to display
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoIconCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  if(pItem->bIconSet)
	pGrid->SetItemImage(pItem->nCRow, pItem->nCCol, g2pvt_icon_index(pItem->nIconIdx));
}


/*****************************************************************************
* void DoCheckCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoCheckCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  CGridCellCheck *pCell;

  pCell = (CGridCellCheck*) pGrid->GetCell(pItem->nCRow, pItem->nCCol);
  if (pCell)
    pCell->SetCheck(pItem->nValue);

}


/*****************************************************************************
* void DoComboCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoComboCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  TCHAR *pToken;
  CStringArray options;
  CGridCellCombo *pCell;
  TCHAR Delim[2] = {0, 0};
  Delim[0] = $MultiStringDelim;

  pCell = (CGridCellCombo*) pGrid->GetCell(pItem->nCRow, pItem->nCCol);
  if (pCell)
  {
    if (pItem->bTextSet)
    {
      pToken = _tcstok(pItem->m_szText, Delim);

      if (pToken)
      {
        pGrid->SetItemText(pItem->nCRow, pItem->nCCol, pToken);

        while (pToken)
        {
          pToken = _tcstok(NULL, Delim);
          if (pToken)
            options.Add(pToken);
        }

        pCell->SetOptions(options);
      }
    }

	if(pItem->bStyleSet) {
	  pCell->SetStyle(pItem->dwStyle & 0xFFFF);
	  pCell->SetColorCombo((pItem->dwStyle & G2_CBS_COLOR_PICKER) != 0);
	} else {
	  pCell->SetStyle(CBS_DROPDOWN);
	}
  }
}


/*****************************************************************************
* void DoTimeCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoTimeCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  CGridCellDateTime *pCell;

  pCell = (CGridCellDateTime*) pGrid->GetCell(pItem->nCRow,
    pItem->nCCol);
  if (pCell)
  {
    SYSTEMTIME requested_time;
    ::GetSystemTime(&requested_time);
    if (pItem->bTextSet)
    {
      g2pvt_parse_date_time_value(&requested_time, pItem->m_szText);
    }

    pCell->Init(DTS_TIMEFORMAT, pItem->dwStyle);
    pCell->SetTime(requested_time);
    pGrid->RedrawCell(pItem->nCRow, pItem->nCCol);

    // pGrid->SetColumnWidth(pItem->nCCol, 100);
  }
}


/*****************************************************************************
* void DoFormattedDateCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoFormattedDateCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  CGridCellFormattedDate* pCell = (CGridCellFormattedDate*) pGrid->GetCell(pItem->nCRow,
    pItem->nCCol);
  if (pCell)
  {
    SYSTEMTIME requested_date;

    ::GetSystemTime(&requested_date);
    if (pItem->bTextSet)
    {
      g2pvt_parse_date_time_value(&requested_date, pItem->m_szText);
    }

    pCell->SetFormattedDate(requested_date, pItem->dwStyle);

    pGrid->RedrawCell(pItem->nCRow, pItem->nCCol);

    // pGrid->SetColumnWidth(pItem->nCCol, 100);
  }
}


/*****************************************************************************
* void DoDurationCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoDurationCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  CGridCellDuration* pCell = (CGridCellDuration*) pGrid->GetCell(pItem->nCRow,
    pItem->nCCol);
  if (pCell)
  {
    pGrid->RedrawCell(pItem->nCRow, pItem->nCCol);

    // pGrid->SetColumnWidth(pItem->nCCol, 100);
  }
}


/*****************************************************************************
* void DoIntegerCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoIntegerCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  if (pItem->bTextSet)
    pGrid->SetItemText(pItem->nCRow, pItem->nCCol, pItem->m_szText);
}


/*****************************************************************************
* void DoQuantityCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoQuantityCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  if (pItem->bTextSet)
    pGrid->SetItemText(pItem->nCRow, pItem->nCCol, pItem->m_szText);
}


/*****************************************************************************
* void DoSpinnerCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoSpinnerCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  CStringArray options;
  TCHAR Delim[2] = _T("|");
  DWORD dwG2Style = G2_UDS_INTEGERS;
  CString LocalData;
  int index;

  CGridCellSpinner *pCell = (CGridCellSpinner*) pGrid->GetCell(pItem->nCRow,  pItem->nCCol);
  if (pCell)
  {
    if (pItem->bTextSet)
    {
      TCHAR *pTemp = _T("");
      // make sure the initial text is formatted correctly
      // create a temporary object to do the formatting for us
      CSpinButtonCtrlTwng *pSpin;
      pSpin = new CSpinButtonCtrlTwng();
      if (pSpin)
      {
        // the spinners are considered to be in in decimal or scientific notation if any of the input values
        // (min, max, increment or default) are in decimal or scientific notation.  Otherwise, we assume
        // we have integers.
        LocalData = pItem->m_szText;
        index = LocalData.FindOneOf(_T(".e")); // look for decimals
        if (-1 != index)
		  dwG2Style = 0;		// Houston, we have decimals
        pSpin->set_spin(pItem->m_szText, dwG2Style, &pTemp);
        delete pSpin;
      }

	  pCell->m_strSpec = pItem->m_szText; // save origianl spec for later use
      pGrid->SetItemText(pItem->nCRow, pItem->nCCol, pTemp); // set the intial val
    }

    pGrid->RedrawCell(pItem->nCRow, pItem->nCCol);
    // pGrid->SetColumnWidth(pItem->nCCol, 100);
  }

}


/*****************************************************************************
* CRuntimeClass *get_cell_class (int type)
*
*   Description: maps between our ctType constants and class objects.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static CRuntimeClass *get_cell_class (int type)
{
  /* 
   * NOTE: If you add a type here, you must also add it to get_cell_type
   */
  switch(type) {
  case ctComboBox:
    return RUNTIME_CLASS(CGridCellCombo);
  case ctCheck:
    return RUNTIME_CLASS(CGridCellCheck);
  case ctIntegerGridView:
    return RUNTIME_CLASS(CGridCellInteger);
  case ctQuantityGridView:
    return RUNTIME_CLASS(CGridCellNumeric);
  case ctCalendar:
    return RUNTIME_CLASS(CGridCellFormattedDate);
  case ctTimeOfDay:
    return RUNTIME_CLASS(CGridCellDateTime);
  case ctDuration:
    return RUNTIME_CLASS(CGridCellDuration);
  case ctIcon:
    return RUNTIME_CLASS(CGridCellImage);
  case ctSpin:
    return RUNTIME_CLASS(CGridCellSpinner);
  case ctEllipsisGridView:
    return RUNTIME_CLASS(CGridCellEllipsis);
  case ctTextBx:
  default:
    return RUNTIME_CLASS(CGridCell);
  }
}


/*****************************************************************************
* BOOL DoStandardStuff (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: we obtain the return value from SetColumnWidth and SetRowHeight,
*     but don't do anything with them.  (FINDME)
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL DoStandardStuff (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  BOOL bRet;
  int nCol;
  int nRow;

  if (pItem->bWidthSet) {
    if (ROW_HEADER_ID == pItem->nCRow) {
      bRet = pGrid->SetColumnWidth(pItem->nCCol, pItem->nWidth);
    }
  }

  if (pItem->bHeightSet) {
    if (COL_HEADER_ID == pItem->nCCol) {
      bRet = pGrid->SetRowHeight(pItem->nCRow, pItem->nHeight);
    }
  }

  // for anything after this point we better have actual cells
  nCol = pGrid->GetColumnCount();
  nRow = pGrid->GetRowCount();

  if ((0 == nCol) || (0 == nRow)) // we can't set any cell attributes if none have been created yet
    return TRUE; 

  if (! pGrid->SetCellType(pItem->nCRow, pItem->nCCol, get_cell_class(pItem->nType)))
    return FALSE;
  if (pItem->bAlignmentSet)
  {
    pGrid->SetItemFormat(pItem->nCRow, pItem->nCCol, pItem->nAlignment);
  }
  if (pItem->bBoldSet)
  {
    pGrid->SetItemBold(pItem->nCRow, pItem->nCCol, (pItem->nBold == 1));
  }
  if (pItem->bBGColorSet)
    pGrid->SetItemBkColour(pItem->nCRow, pItem->nCCol,
    GetColorVal(pItem->szBGColor));
  if (pItem->bFGColorSet)
    pGrid->SetItemFgColour(pItem->nCRow, pItem->nCCol,
    GetColorVal(pItem->szFGColor));

   if (pItem->bTextSet) {
    // added by SoftServe
	bool bMultiline;
	if (pItem->bMultilineSet) {
		if (pItem->nMultiline) {
			bMultiline = true;
		} else {
			bMultiline = false;
		}
	} else {
		bMultiline = (bool)g2pvt_is_multiline_string(pItem->m_szText);
	}

    if(bMultiline) {
	// end of SoftServe changes
	  LPWSTR str = g2pvt_g2_to_windows_text(pItem->m_szText);
	  pGrid->SetItemFormat(pItem->nCRow, pItem->nCCol,
						   (pGrid->GetItemFormat(pItem->nCRow, pItem->nCCol)
							& ~(DT_SINGLELINE | DT_END_ELLIPSIS)
							| (DT_WORDBREAK | DT_WORD_ELLIPSIS)));
	  pGrid->SetItemText(pItem->nCRow, pItem->nCCol, str);
	  free(str);
	} else {
	  pGrid->SetItemText(pItem->nCRow, pItem->nCCol, pItem->m_szText);
	}
  }

  if (pItem->bEditableSet)
  {
    if (pItem->nEditable)
      pGrid->SetItemState(pItem->nCRow, pItem->nCCol,
						  pGrid->GetItemState(pItem->nCRow, pItem->nCCol) & ~GVIS_READONLY);
    else
      pGrid->SetItemState(pItem->nCRow, pItem->nCCol,
						  pGrid->GetItemState(pItem->nCRow, pItem->nCCol) | GVIS_READONLY);
  }
  if (pItem->bSelectionSet)
  {
    if (pItem->nSelected)
      pGrid->SetItemState(pItem->nCRow, pItem->nCCol,
      pGrid->GetItemState(pItem->nCRow, pItem->nCCol)
      | GVIS_SELECTED);
    else
      pGrid->SetItemState(pItem->nCRow, pItem->nCCol,
      pGrid->GetItemState(pItem->nCRow, pItem->nCCol)
      & ~GVIS_SELECTED);
  }
  if (pItem->bTextFontSet || pItem->bTextFontSizeSet)
  {
    LOGFONT *lfFont = new LOGFONT(*(pGrid->GetItemFont(pItem->nCRow, pItem->nCCol)));
    if (pItem->bTextFontSizeSet)
      lfFont->lfHeight = pItem->nTextFontSize;
    if (pItem->bTextFontSet && _tcslen(pItem->pTextFont) < LF_FACESIZE)
      _tcscpy(lfFont->lfFaceName, pItem->pTextFont);
    pGrid->SetItemFont(pItem->nCRow, pItem->nCCol, lfFont);
  }

  pGrid->Invalidate();

  return TRUE;
}


/*****************************************************************************
* void DoGeneralCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void DoGeneralCell (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  if (DoStandardStuff(pGrid, pItem))
  {
    switch(pItem->nType)
    {
    case ctComboBox:
      DoComboCell(pGrid, pItem);
      break;

    case ctCheck:
      DoCheckCell(pGrid, pItem);
      break;

    case ctIntegerGridView:
      DoIntegerCell(pGrid, pItem);
      break;

    case ctQuantityGridView:
      DoQuantityCell(pGrid, pItem);
      break;

    case ctCalendar:
      DoFormattedDateCell(pGrid, pItem);
      break;

    case ctTimeOfDay:
      DoTimeCell(pGrid, pItem);
      break;

    case ctDuration:
      DoDurationCell(pGrid, pItem);
      break;

    case ctIcon:
      DoIconCell(pGrid, pItem);
      break;

    case ctSpin:
      DoSpinnerCell(pGrid, pItem);
      break;

      /* Efficiency: DoTextCell and DoEllipisCell are no-ops, so don't bother
         calling them.  If they are changed to do something, uncomment this
         code.  -jv, 10/31/05 */
    case ctEllipsisGridView:
      // DoEllipsisCell(pGrid, pItem);    // NOT CALLED!!!
      break;

    case ctTextBx:
    default:
      // DoTextCell(pGrid, pItem);       // NOT CALLED!!!
      break;
    }
  }
}


/*****************************************************************************
* BOOL set_item_text (CRichGridItem *pItem, TCHAR *pszText)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL set_item_text (CRichGridItem *pItem, TCHAR *pszText)
{
  int string_length = 0;

  string_length = _tcscspn(pszText, $StringDelimiter);
  if (string_length >= MAX_TEXT_SIZE)
  {
    g2pvt_gprintf(G2PVT_ERROR, "set_item_text: %s\n",
      "text string too long");
    return FALSE;
  }

  if (string_length >= pItem->m_textSize)
  {
    if(pItem->m_textSize > 0)	// Skip message for trivial initial resize
      g2pvt_gprintf(G2PVT_PROGRESS, "warning: set_item_text: %s\n",
		    "resizing buffer");

    pItem->m_textSize = string_length + SZTL;
    delete [] pItem->m_szText;

    pItem->m_szText = new TCHAR[pItem->m_textSize];
  }
  if (pItem->m_szText == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_item_text\n");
    pItem->m_textSize = 0;
    return FALSE;
  }
  else
  {
    SafeZeroMemory(pItem->m_szText, pItem->m_textSize, pItem->m_textSize);
    SafeCopy(pItem->m_szText, pItem->m_textSize, pszText, string_length);
    pItem->m_szText[string_length] = 0;
    pItem->bTextSet = TRUE;
  }

  return TRUE;
}


/*****************************************************************************
* BOOL set_item_bg_color (CRichGridItem *pItem, TCHAR *pszText)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL set_item_bg_color (CRichGridItem *pItem, TCHAR *pszText)
{
  int string_length = 0;

  string_length = _tcscspn(pszText, $StringDelimiter);
  if (string_length >= COLOR_LEN)
  {
    g2pvt_gprintf(G2PVT_ERROR, "set_item_bg_color: %s\n",
      "text string too long");
    return FALSE;
  }
  else
  {
    SafeZeroMemory(pItem->szBGColor, COLOR_LEN, COLOR_LEN);
    SafeCopy(pItem->szBGColor, COLOR_LEN, pszText, string_length);
    pItem->szBGColor[string_length] = 0;
    pItem->bBGColorSet = TRUE;
  }

  return TRUE;
}


/*****************************************************************************
* BOOL set_item_fg_color (CRichGridItem *pItem, TCHAR *pszText)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL set_item_fg_color (CRichGridItem *pItem, TCHAR *pszText)
{
  int string_length = 0;

  string_length = _tcscspn(pszText, $StringDelimiter);
  if (string_length >= COLOR_LEN)
  {
    g2pvt_gprintf(G2PVT_ERROR, "set_item_fg_color: %s\n",
      "text string too long");
    return FALSE;
  }
  else
  {
    SafeZeroMemory(pItem->szBGColor, COLOR_LEN, COLOR_LEN);
    SafeCopy(pItem->szFGColor, COLOR_LEN, pszText, string_length);
    pItem->szFGColor[string_length] = 0;
    pItem->bFGColorSet = TRUE;
  }

  return TRUE;
}

/*****************************************************************************
* BOOL set_item_text_font (CRichGridItem *pItem, TCHAR *pszText)
*
*   GENSYMCID-1525: new g2 release font color/size/type is not working for grid-view control
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL set_item_text_font (CRichGridItem *pItem, TCHAR *pszText)
{
   int string_length = 0;

  string_length = _tcscspn(pszText, $StringDelimiter);
  pItem->pTextFont = new TCHAR[string_length + 1];

  if (pItem->pTextFont == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_item_text_font\n");
    pItem->bTextFontSet = FALSE;
    return FALSE;
  }
  else
  {
    SafeZeroMemory(pItem->pTextFont, string_length, string_length);
    SafeCopy(pItem->pTextFont, string_length, pszText, string_length);
    pItem->pTextFont[string_length] = 0;
    pItem->bTextFontSet = TRUE;
  }

  return TRUE;
}

/*****************************************************************************
* BOOL parse_grid_view_string (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
*
*   Description:
*   Input Arguments:
*   Returns: TRUE on success, FALSE if there was any problem.
*   Notes:
*     jv, 5/04/05: right now, the only type of "problem" we recognize is "out
*     of memory".  Later, we may return FALSE due to a parsing problem.
*
*   (_, n) entire column or row-header column
*   (n, _) entire row or column-header row
*    
*       V  Numeric Value
*       E  Editable
*       C  Control Type
*       Wn width
*       Hn Height
*       Fstr Foreground Color
*       Bstr Background Color
*       Sstr Selection  Color
*       T Text
*       \001 String Marker
*
*    _T("(1, 2)EFaquamarineT133](1, 3)W345(_, 5)H23")]
*
*    row 1 column 2 is editable, has foreground color 45, control type 133
*    row 1 column 3 has width 345, column 5 has height 23
*
*  Note A: This is to fix Bug HQ-5210710, "grid-view: empty cell "inherits"
*  row-header text-value w/ use-row-header: false".  With G2 8.2r0, if the user
*  specified some text for a header cell, but also specified that the header
*  was not being used, G2 would fail to notice the latter fact, and send the
*  header text anyway, like this: "(3,_)TRow 4^A".  We actually have changed
*  G2 8.2r1 to no longer do that; if the header is not in use, then it will
*  not send the text.  But, we also want to work around the problem in G2 8.2r0
*  when TWNG 8.2r1 or greater is used.  This turned out to be slightly more of
*  a hack than I had hoped.  When we parse the "(n,_)" indicator, we treat it
*  as "column 0", and at that point, the information that we are dealing with
*  a header is essentially gone.  All we know is that it is column zero.  So
*  I'm adding two new local variables here to "remember" that the zero we're
*  dealing with came in as a "_".  When we notice that we are being asked to
*  set the text of a zero cell, we check these variables, and if it turns out
*  it is actually a "_" cell, and the header is not in use, we do not actually
*  set the text.  -jv, 2/14/06
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL parse_grid_view_string (CGensymGridCtrl *pGrid, CRichGridItem *pItem)
{
  TCHAR *tokString, *curtok, *prevtok;
  TCHAR lcode;
  size_t len;
  int nchars;
  BOOL no_errors = TRUE;
  BOOL doing_cheader_row = FALSE, doing_hheader_col = FALSE; // see Note A above

  len = _tcslen(pItem->pTokenString) + SZTL;
  tokString = new TCHAR[len];
  if (tokString == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: parse_grid_view_string\n");
    return FALSE;                // out of memory!
  }
  SafeCopy(tokString, len, pItem->pTokenString, len);
  prevtok = tokString;
  curtok = tokString + 1;

  lcode = *prevtok;
  nchars = 0;

  while ((lcode != 0) && (prevtok != curtok) && no_errors) {
    prevtok = curtok;
    switch (lcode)
    {
    case $StartCell:
      if (*curtok == $PerRowOrCol) {
        doing_cheader_row = TRUE;
        pItem->nCRow = ROW_HEADER_ID;
        nchars = 1;
      } else {
        doing_cheader_row = FALSE;
        nchars = _tcsspn(curtok, $NumericChars);
        pItem->nCRow = pGrid->PhysicalRow(_ttoi(curtok));
      }
      break;

    case $Comma:
      if (*curtok == $PerRowOrCol) {
        doing_hheader_col = TRUE;
        pItem->nCCol = COL_HEADER_ID;
        nchars = 1;
      } else {
        doing_hheader_col = FALSE;
        nchars = _tcsspn(curtok, $NumericChars);
        pItem->nCCol = pGrid->PhysicalColumn(_ttoi(curtok));
      }
      break;

    case $EndCell:
      nchars = 0;
      break;

    case $Editable:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nEditable = _ttoi(curtok);
      pItem->bEditableSet = TRUE;
      break;

	// added by SoftServe
	case $MultiLine:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nMultiline = _ttoi(curtok);
      pItem->bMultilineSet = TRUE;
      break;
	// end of SoftServe changes

    case $SelRange:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nSelected = _ttoi(curtok);
      pItem->bSelectionSet = TRUE;
      break;

    case $Value:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nValue = _ttoi(curtok);
      break;

    case $IconIndex:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nIconIdx = _ttoi(curtok);
      pItem->bIconSet = TRUE;
      break;

    case $ControlType:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nType = _ttoi(curtok);
      break;

    case $Width:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nWidth = _ttoi(curtok);
      pItem->bWidthSet = TRUE;
      break;

    case $Height:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nHeight = _ttoi(curtok);
      pItem->bHeightSet = TRUE;
      break;

    case $Text:
      if ((doing_cheader_row && (pGrid->GetFixedRowCount() == 0)) ||
          (doing_hheader_col && (pGrid->GetFixedColumnCount() == 0)))
      {
        nchars = _tcscspn(curtok, $StringDelimiter) + SKIP_CHAR;
      }
      else
      { 
        no_errors = set_item_text(pItem, curtok);
        if (no_errors) {
          // skip final ^A
          nchars = _tcslen(pItem->m_szText) + SKIP_CHAR;
        }
      }
      break;

    case $BGColor:
      no_errors = set_item_bg_color(pItem, curtok);
      if (no_errors) {
        // skip final ^A
        nchars = _tcslen(pItem->szBGColor) + SKIP_CHAR;
      }
      break;

    case $FGColor:
      no_errors = set_item_fg_color(pItem, curtok);
      if (no_errors) {
        // skip final ^A
        nchars = _tcslen(pItem->szFGColor) + SKIP_CHAR;
      }
      break;
    case $TextFont:
      no_errors = set_item_text_font(pItem, curtok);
      if (no_errors) {
        // skip final ^A
        nchars = _tcslen(pItem->pTextFont) + SKIP_CHAR;
      }
      break;
    case $TextFontSize:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->bTextFontSizeSet = TRUE;
      pItem->nTextFontSize = _ttoi(curtok);
      break;
//     case $EndData:
//       nchars = 0;
//       break;

    case $Alignment:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->nAlignment = _ttoi(curtok);
      pItem->bAlignmentSet = TRUE;
      break;

    case $Bold:
      nchars = _tcsspn(curtok, $NumericChars);
	  pItem->nBold = _ttoi(curtok);
      pItem->bBoldSet = TRUE;
      break;

    case $Style:
      nchars = _tcsspn(curtok, $NumericChars);
      pItem->dwStyle = _ttoi(curtok);
      pItem->bStyleSet = TRUE;
      break;

    default:
	  if(lcode == $EndData) {
		nchars = 0;
	  } else {
		g2pvt_gprintf(G2PVT_ERROR, "parse_grid_view_string: %s: \'%c\'\n",
					  "unrecognized letter code", lcode);
		no_errors = FALSE;
	  }
	  break;
    }
    curtok += nchars;
    lcode = *curtok;
    curtok += SKIP_CHAR;
  }

  delete [] tokString;
  return no_errors;
}


/*****************************************************************************
*   TCHAR *new_empty_string ()
*
*   Description: returns a newly allocated empty string.  Does not check for
*      out-of-memory.  If we can't allocate one TCHAR, we're screwed.
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static TCHAR *new_empty_string ()
{
  TCHAR *rval;

  rval = new TCHAR[1];
  rval[0] = 0;
  return rval;
}


/*****************************************************************************
* CRichGridItem constructor
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CRichGridItem::CRichGridItem (TCHAR *token_string)
{
  if (token_string) {
    buf_size = _tcslen(token_string) + SZTL;
    pTokenString = new TCHAR[buf_size];
    if (pTokenString == NULL) {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: CRichGridItem constructor\n");
    } else {
      SafeZeroMemory(pTokenString, buf_size, buf_size);
      SafeCopy(pTokenString, buf_size, token_string, buf_size);
    }
  } else {
    pTokenString = new_empty_string();
  }

  SafeZeroMemory(szFGColor, COLOR_LEN, COLOR_LEN);
  SafeZeroMemory(szBGColor, COLOR_LEN, COLOR_LEN);

  pTextFont = NULL;

  m_szText = NULL;
  m_textSize = 0;

  nWidth = 0;
  nHeight = 0;
  nType = 0;
  nEditable = 0;
  nMultiline = 0; // added by SoftServe
  nCRow = 0;
  nCCol = 0;
  nValue = 0;
  nSelected = 0;
  nIconIdx = 0;
  nAlignment = 0;
  nBold = 0;
  nTextFontSize = 0;
  dwStyle = 0;

  bFGColorSet = FALSE;
  bBGColorSet = FALSE;
  bTextSet = FALSE;
  bWidthSet = FALSE;
  bHeightSet = FALSE;
  bEditableSet = FALSE;
  bMultilineSet = FALSE; // added by SoftServe
  bRowHeaderSet = FALSE;
  bColHeaderSet = FALSE;
  bSelectionSet = FALSE;
  bIconSet = FALSE;
  bAlignmentSet = FALSE;
  bBoldSet = FALSE;
  bStyleSet = FALSE;
  bTextFontSet = FALSE;
  bTextFontSizeSet = FALSE;
}


/*****************************************************************************
* long find_end_data_position (TCHAR *grid_view_spec)
*
*   Description: searches for $EndData in the given string, and returns the
*     position, if found.  We tend to use _tcstok for this purpose, but that
*     wants to mangle the string, which means we make a copy of the string
*     first, which can be fairly inefficient.  _tcstok also takes a whole set
*     of delimiters, and so it may be overkill when we're just looking for a
*     single character.
*   Input Arguments: a string, understood to be a (partial or full) grid-view
*     specification
*   Returns: the position of $EndData if found, -1 otherwise.
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static long find_end_data_position (TCHAR *grid_view_spec)
{
  int pos=0;

  while (grid_view_spec[pos] != 0) {
    if (grid_view_spec[pos] == $EndData) {
      return pos;
    }
    pos++;
  }

  return -1;
}


/*****************************************************************************
* BOOL do_gv_item (CGensymGridCtrl *pGrid, TCHAR *token)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL do_gv_item (CGensymGridCtrl *pGrid, TCHAR *token)
{
  if (token)
  {
    CRichGridItem item(token);
    if (parse_grid_view_string(pGrid, &item))
    {
      DoGeneralCell(pGrid, &item);
      return TRUE;
    }
    g2pvt_gprintf(G2PVT_ERROR, "problem parsing grid_string, aborting\n");
  }
  return FALSE;
}


/*****************************************************************************
* BOOL specify_grid_view_cells (CGensymGridCtrl *pGrid, TCHAR *cells_spec)
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static BOOL specify_grid_view_cells (CGensymGridCtrl *pGrid, TCHAR *cells_spec)
{
  int inLen;
  TCHAR *pszTemp, *pWhere, *token;
  TCHAR $EndElement[2] = {$EndData, NULL};
  BOOL success_p = FALSE;

  // make temp copy of incoming string to mangle with _tcstok
  inLen = _tcslen(cells_spec);
  pszTemp = new TCHAR[inLen + SZTL];
  if (pszTemp == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: specify_grid_view_cells\n");
    return FALSE;                // out of memory!
  }

  SafeZeroMemory(pszTemp, inLen + SZTL, inLen + SZTL);
  SafeCopy(pszTemp, inLen + SZTL, cells_spec, inLen + SZTL);
  pWhere = pszTemp;

  // now fill in all the cell data
  do
  {
    token = _tcstok(pWhere, $EndElement);
    success_p = do_gv_item(pGrid, token);
    pWhere = pWhere + _tcslen(pWhere) + SKIP_CHAR;
  } while (success_p);
 

  // clean up
  delete [] pszTemp;
  pszTemp = NULL;

  return TRUE;
}


/*****************************************************************************
* long g2ext_specify_grid_view_cells (long dlgId, long controlId, LPWSTR cell_spec)
*
*   Description: API to set the value of individual cells
*   Input Arguments:
*   Returns: 
*
*   Notes: 
*     -----
*   Modifications:
*****************************************************************************/
extern "C"
long g2ext_specify_grid_view_cells (long dlgId, long controlId, LPWSTR cell_spec)
{
  GENSYMDIALOG *dialog;
  CONTROLITEM *control;
  EXTRA_TYPE_DATA *gv_extra_data;
  EXTRA_GRID_VIEW_DATA *new_cells;
  size_t spec_len = 0;

  dialog = g2pvt_find_dialog_by_id(dlgId);
  if (!dialog)
  {
    g2pvt_gprintf(G2PVT_ERROR, "g2ext_specify_grid_view_cells: cannot map %d to dialog\n",
                  dlgId);
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  control = g2pvt_lookup_control_by_id(controlId, dialog);
  if (!control)
  {
    g2pvt_gprintf(G2PVT_ERROR, "g2ext_specify_grid_view_cells: cannot map %d to control\n",
                  controlId);
    return DYNAMIC_DIALOG_UPDATE_FAILED;
  }

  gv_extra_data = control->_pExtraTypeData;
  if (gv_extra_data == NULL)
  {
    gv_extra_data = (EXTRA_TYPE_DATA *) malloc(sizeof(EXTRA_TYPE_DATA));
    if (gv_extra_data == NULL)
    {
      g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2ext_specify_grid_view_cells\n");
      return DYNAMIC_DIALOG_UPDATE_FAILED;   // out of memory!
    }
    gv_extra_data->_type = ctGridView;
    gv_extra_data->_pData = NULL;
    control->_pExtraTypeData = gv_extra_data;
  }

  new_cells = (EXTRA_GRID_VIEW_DATA *) malloc(sizeof(EXTRA_GRID_VIEW_DATA));
  if (new_cells == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: g2ext_specify_grid_view_cells\n");
    return DYNAMIC_DIALOG_UPDATE_FAILED;   // out of memory!
  }

  spec_len = wcslen(cell_spec);
  new_cells->spec = new wchar_t[spec_len + SZTL];
  SafeZeroMemory(new_cells->spec, spec_len + SZTL, spec_len + SZTL);
  SafeCopy(new_cells->spec, spec_len + SZTL, cell_spec, spec_len + SZTL);
  new_cells->next = (struct GV_DATA_LINKED_LIST *)gv_extra_data->_pData;
  gv_extra_data->_pData = new_cells;

  return DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Creating the CGensymGridCtrl
%
% Description: the code in this section is used to instantiate the CGensymGridCtrl
%   and set it up, specifically at the higher level.  The code to create the
%   individual cells is not contained in this section, but is called from this
%   section, via function specify_grid_view_cells.
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
* void parse_dimensions (TCHAR *pDimensionsString, SIZE *grid_size)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
* _T("{6, 7}")
*
* the grid is 6X7
*
*     -----
*   Modifications:
*
*   Note:
*   the format of visble row and column is like `V2V4',
*   the number after first `V' indicates the visible row,and
*   the number after second `V' indicates the visible column.
*   the initial value of `pVisible_row' and `pVisible_row' should be `-1'.
*****************************************************************************/
static void parse_dimensions (TCHAR *pDimensionsString, SIZE *grid_size, int *pSortable,
                              COLORREF *pBgColor,
                              int &nHeaderIndicator, int *pVisible_row, int *pVisible_column,
                              int *pTitleRowHeight, int *pTitleColumnWidth,
                              int *pFrozenRowCount, int *pFrozenColumnCount)
{
  size_t len = _tcslen(pDimensionsString) + SZTL;
  TCHAR *pszWork = new TCHAR [len];
  TCHAR *pWorkLoc;
  TCHAR *pszRef = new TCHAR [len];
  TCHAR *pRefLoc;
  TCHAR szDimension [DIM_SIZE];
  BOOL bFlag = TRUE;
  size_t offset = 0;
  TCHAR *pToken;
  TCHAR Delim;
  TCHAR szHeaderIndicator[2];

  if (pszWork == NULL)
  {
    delete [] pszRef;
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: parse_dimensions #1\n");
    return;                // out of memory!
  }
  if (pszRef == NULL)
  {
    delete [] pszWork;
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: parse_dimensions #2\n");
    return;                // out of memory!
  }

  // make temp copies of incoming string to mangle with _tcstok
  SafeZeroMemory(pszWork, len, len);
  SafeCopy(pszWork, len, pDimensionsString, len);
  pWorkLoc = pszWork + 1;

  SafeZeroMemory(pszRef, len, len);
  SafeCopy(pszRef, len, pDimensionsString, len);
  pRefLoc = pszRef;

  // we now have 2 identical buffers, one for working (work buffer) and one to
  // keep track of delims (reference buffer)
  while (bFlag)
  {
    offset = _tcscspn(pRefLoc, $AllDelimiters); // find the next delimiter

    pToken = _tcstok(pWorkLoc, $AllDelimiters); // this will NULL out the delimiter
    Delim = *(pRefLoc+offset); // we've hit a null, we're all done
    if (0==Delim)
    {
      bFlag = FALSE;
      break;
    }
    
    if (NULL == pToken)
    {
      bFlag = FALSE; // we've found the last delimiter
    }

    switch(Delim)
    {
      // The dimensions we receive from Lisp is the count from "our" (the C code's)
      // perspective.  That is, it's the total number of rows and columns, including
      // any headers.  When we receive a row or colum *index*, it does not count the
      // headers, if present; row 0 is the first row of non-header, user data.  But
      // the dimensions are done differently.  -jv, 5/03/05
    case $EndDim:
      // there are no token for this flag.
      pToken = L"";
      break;
    case $Slash:
      SafeCopy(szDimension, DIM_SIZE, pToken, _tcslen(pToken) + SZTL);
      grid_size->cy = _wtoi(szDimension);
      break;
    case $StartDim:
      SafeCopy(szDimension, DIM_SIZE, pToken, _tcslen(pToken) + SZTL);
      grid_size->cx = _wtoi(szDimension);
      break;
    case $Sortable:
      _tcsspn(pToken, $NumericChars);
      *pSortable = _ttoi(pToken);
      break;
    case $VisibleCell:
      _tcsspn(pToken, $NumericChars);
      if (*pVisible_row == -1) {
        *pVisible_row = _ttoi(pToken);
      } else {
        *pVisible_column = _ttoi(pToken);
      }
      break;
    case $TitleRowHeight:
      _tcsspn(pToken, $NumericChars);
      *pTitleRowHeight = _ttoi(pToken);
      break;
    case $TitleColumnWidth:
      _tcsspn(pToken, $NumericChars);
      *pTitleColumnWidth = _ttoi(pToken);
      break;
    case $FrozenRowCount:
      _tcsspn(pToken, $NumericChars);
      *pFrozenRowCount = _ttoi(pToken);
      break;
    case $FrozenColumnCount:
      _tcsspn(pToken, $NumericChars);
      *pFrozenColumnCount = _ttoi(pToken);
      break;
    case $HeaderIndicator:
      SafeCopy(szHeaderIndicator, DIM_SIZE, pToken, _tcslen(pToken) + SZTL);
      nHeaderIndicator = _wtoi(szHeaderIndicator);
      break;

     case $BGColor:
      _tcsspn(pToken, $NumericChars);
      *pBgColor = _ttoi(pToken);
      break;

    default:
      g2pvt_gprintf(G2PVT_ERROR, "%s \'%c\' in parse_dimensions\n",
        "unrecognized token", Delim);
      break;
    }

    // jump  past the delimiter we just processed
    pWorkLoc = pWorkLoc + _tcslen(pToken)  + SKIP_CHAR;
    pRefLoc = pRefLoc + offset + SKIP_CHAR;
  }

  delete [] pszWork;
  delete [] pszRef;

  return;
}


/*****************************************************************************
* CGensymGridCtrl *initial_grid_view (CONTROLITEM *pcontrol, CWnd *pParent,
*                                    RECT *pRect, TCHAR *token, int *visible_row, int *visible_column)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CGensymGridCtrl *initial_grid_view (CONTROLITEM *pcontrol, CWnd *pParent,
                                    RECT *pRect, TCHAR *token, int *visible_row, int *visible_column)
{
  CGensymGridCtrl *pGrid = NULL;

  int nSortable;
  int nHeaderIndicator = HEADER_GOING_ACROSS_AND_DOWN; // default for missing Xn token
  int nFixedRowCount = GRID_VIEW_DEFAULT_NFIXED_ROWS;
  int nFixedColumnCount = GRID_VIEW_DEFAULT_NFIXED_COLS;
  COLORREF bgColor = (COLORREF)-1;
  int title_row_height = -1;
  int title_column_width = -1;
  int frozen_row_count = -1;
  int frozen_column_count = -1;

  if (token)
  {
    SIZE grid_size;

    grid_size.cx = 0L;
    grid_size.cy = 0L;
    nSortable = 0;

    parse_dimensions(token, &grid_size, &nSortable, &bgColor, nHeaderIndicator,
                     visible_row, visible_column,
                     &title_row_height, &title_column_width,
                     &frozen_row_count, &frozen_column_count);

    // The HeaderIndicator processing is very explicit, sacrificing efficiency,
    // because there has been a lot of confusion around what all this means.
    switch(nHeaderIndicator)
    {
    case NO_HEADERS:
      nFixedRowCount = 0;
      nFixedColumnCount = 0;
      break;

    case HEADER_GOING_ACROSS: 
      nFixedRowCount = 1;
      nFixedColumnCount = 0; 
      break;

    case HEADER_GOING_DOWN:
      nFixedRowCount = 0;
      nFixedColumnCount = 1;
      break;

    default:
    case HEADER_GOING_ACROSS_AND_DOWN:
      nFixedRowCount = 1;
      nFixedColumnCount = 1;
      break;
    }

    // FIXME: Why are there FOUR separate calls to new and Create() in here?

    if ((grid_size.cy <= 0) || (grid_size.cx <= 0))
        {
          if (grid_size.cy <= 0) // G2 requests a useless grid with no columns
          {
                #ifdef GV_DEBUG
                OutputDebugString(_T("\n row or column dimension is 0 \n"));
                #endif
                pGrid = new CGensymGridCtrl(grid_size.cx, 0, nFixedRowCount, 0);
                pGrid->Create(*pRect, pParent, pcontrol->_controlId);
          }
          else  // G2 requests a grid with no rows
          {
            #ifdef GV_DEBUG
        OutputDebugString(_T("\n row or column dimension is 0 \n"));
            #endif
        pGrid = new CGensymGridCtrl(0, grid_size.cy , 0, nFixedColumnCount);
            pGrid->Create(*pRect, pParent, pcontrol->_controlId);
          }
        }
    else // rows and columns 
        {
          pGrid = new CGensymGridCtrl(grid_size.cx, grid_size.cy, nFixedRowCount, nFixedColumnCount);
          pGrid->Create(*pRect, pParent, pcontrol->_controlId, pcontrol->_styles);
        }

    // FIXME: This should all be in a method.

    // no need to set the row/column info directly. It's donein the constructor
    pGrid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xFF));

    pGrid->EnableTitleTips(FALSE); // shut off tool tips
    pGrid->SetRowResize(TRUE); // allow resizing
    pGrid->SetColumnResize(TRUE); // allow resizing
    pGrid->SetFixedColumnSelection(TRUE);
    pGrid->SetFixedRowSelection(TRUE);

    pGrid->EnableColumnHide();
    pGrid->m_lastButtonClicked.x = GRID_VIEW_NO_BUTTON_CLICKED;
    pGrid->m_lastButtonClicked.y = GRID_VIEW_NO_BUTTON_CLICKED;
    pGrid->m_lastEdit.x = GRID_VIEW_NO_PENDING_EDIT;
    pGrid->m_lastEdit.y = GRID_VIEW_NO_PENDING_EDIT;
    pGrid->m_nSortable = nSortable;
    if (pGrid->m_nSortable)
      pGrid->SetHeaderSort(TRUE); // the user wants this sortable

    if(bgColor != (COLORREF)-1)
      pGrid->SetGridBkColor(bgColor);

    // FIXME: We want to choose the 16x16 or 32x32 image lists based on space
    // available.
    pGrid->SetImageList(CImageList::FromHandle(g2pvt_get_image_list(32)));
    if (title_row_height != -1) {
      pGrid->SetRowHeight(0, title_row_height);
    }
    if (title_column_width != -1) {
      pGrid->SetColumnWidth(0, title_column_width);
    }
    if (frozen_row_count > 0) {
      pGrid->SetFreezedRowCount(frozen_row_count);
    }
    if (frozen_column_count > 0) {
      pGrid->SetFreezedColumnCount(frozen_column_count);
    }

    // pGrid->SetCompareFunction(CGensymGridCtrl::pfnCellNumericCompare);
  } else {
    pGrid = new CGensymGridCtrl(GRID_VIEW_DEFAULT_NROWS, GRID_VIEW_DEFAULT_NCOLS,
      GRID_VIEW_DEFAULT_NFIXED_ROWS, GRID_VIEW_DEFAULT_NFIXED_COLS);
    pGrid->Create(*pRect, pParent, pcontrol->_controlId);
  }

  pGrid->m_dialogID = pcontrol->_dialogId;
  pGrid->InitializeRowTags();
  return pGrid;
}


/*****************************************************************************
* CGensymGridCtrl *create_grid_view_from_string (CONTROLITEM *pcontrol,
*                                                CWnd *pParent, RECT *pRect)
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CGensymGridCtrl *create_grid_view_from_string (CONTROLITEM *pcontrol,
                                               CWnd *pParent, RECT *pRect)
{
  CGensymGridCtrl *pGrid = NULL;
  TCHAR *dimensions;
  long dimLen;
  int visible_row = -1;
  int visible_column = -1;

  dimLen = find_end_data_position(pcontrol->_mText);
  dimensions = new TCHAR[dimLen + SZTL];
  if (dimensions == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: create_grid_view_from_string\n");
    return NULL;                // out of memory!
  }
  SafeZeroMemory(dimensions, dimLen + SZTL, dimLen + SZTL);
  SafeCopy(dimensions, dimLen, pcontrol->_mText, dimLen);
  dimensions[dimLen] = 0;

  pGrid = initial_grid_view(pcontrol, pParent, pRect, dimensions, &visible_row, &visible_column);
  specify_grid_view_cells(pGrid, (pcontrol->_mText) + dimLen);

  if (visible_row != -1 && visible_column != -1) {
    pGrid->EnsureVisible(visible_row,visible_column);
  }

  delete [] dimensions;
  return pGrid;
}


/*****************************************************************************
* void handle_extra_cell_data (CGensymGridCtrl *pGrid, EXTRA_GRID_VIEW_DATA *cells)
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes: Look!  It's recursive!  Could easily be changed to iterative, if desired.
*
*     -----
*   Modifications:
*****************************************************************************/
static void handle_extra_cell_data (CGensymGridCtrl *pGrid, EXTRA_GRID_VIEW_DATA *cells)
{
  if (cells->next != NULL) {
    handle_extra_cell_data(pGrid, cells->next);
    cells->next = NULL;
  }

  specify_grid_view_cells(pGrid, cells->spec);
  delete [] cells->spec;
  free(cells);
}


/*****************************************************************************
* CGensymGridCtrl *g2pvt_create_rich_edit_grid (CONTROLITEM *pcontrol,
*                                               CWnd *pParent, RECT *pRect)
*
*   Description: API, called from twng/c/DynamicDlg.cpp, to construct the data
*     structures which represent the grid-view.  That procss involves parsing a
*     string of serialized data into rows and columns.  This function just does
*     a sanity check to make sure that some text was supplied, and then calls a
*     static helper function, fill_in_grid_view.
*   Input Arguments:
*   Returns: an instance of a CGensymGridCtrl, with all the data filled in as
*     specified in pcontrol->_mText.
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CGensymGridCtrl *g2pvt_create_rich_edit_grid (CONTROLITEM *pcontrol,
                                              CWnd *pParent, RECT *pRect)
{
  CGensymGridCtrl *pGrid = NULL;

  if (pcontrol->_mText)
  {
    pGrid = create_grid_view_from_string(pcontrol, pParent, pRect);

    if (pcontrol->_pExtraTypeData)
    {
      handle_extra_cell_data(pGrid, (EXTRA_GRID_VIEW_DATA *) pcontrol->_pExtraTypeData->_pData);
      free(pcontrol->_pExtraTypeData);
      pcontrol->_pExtraTypeData = NULL;
    }
  }

  return pGrid;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Building the Control Value String for G2
%
% Description: the code in this section is used to construct the string which
%   is used to notify G2 of the current control-value of the grid-view.
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
 * wchar_t *make_control_value_internal (CGensymGridCtrl *pGrid)
 *
 *   Description: 
 *   Input Arguments:
 *   Returns: Newly malloc'd wide string.
 *   Notes:
 *
 *     -----
 *   Modifications:
 *****************************************************************************/
static wchar_t *make_control_value_internal (CGensymGridCtrl *pGrid)
{
  int row, col, G2row, G2col, rv = 0;
  wchar_t *pOutputStr, *ptr;
  size_t buf_size, len_used = 0;
  CGridCellCheck *pCellCheck;

  row = pGrid->m_lastEdit.x;
  col = pGrid->m_lastEdit.y;
  buf_size = TEMP_BUFFER_SIZE;

  pGrid->SetSizeOfReturnBuf(buf_size);
  pOutputStr = (wchar_t *) malloc(buf_size * sizeof(wchar_t));
  if (pOutputStr == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: make_control_value_internal\n");
    return new_empty_string();                                // out of memory!
  }
  SafeZeroMemory(pOutputStr, buf_size, buf_size);
  ptr = pOutputStr;

  rv = _snwprintf(ptr, buf_size,
                  L"%c%d%c%d%c%c", $StartDim, pGrid->GetRowCount(), $Slash,
                  pGrid->GetColumnCount(), $EndDim, 0);

  if ((row == GRID_VIEW_NO_PENDING_EDIT) ||
      (col == GRID_VIEW_NO_PENDING_EDIT))
  {
    return pOutputStr;
  }

  G2row = pGrid->G2Row(row);
  G2col = pGrid->G2Column(col);
  if ((G2row < ROW_HEADER_ID) || (G2col < COL_HEADER_ID))
  {
    g2pvt_gprintf(G2PVT_ERROR, "Invalid row or column: %d,%d %d,%d\n", row, col, G2row, G2col);
    return pOutputStr;
  }

  len_used = _tcslen(pOutputStr);
  ptr = pOutputStr + len_used;
  rv = _snwprintf(ptr, buf_size - len_used,
                  L"%c%d%c%d%c%c%s%c", $StartCell, G2row, $Comma, G2col, $EndCell,
                  $Text, pGrid->GetItemText(row, col), $StrDelim);

  // Since grid-cell selections are now sent over as they happen, sending
  // selected-p here for just the one last edited cell is redundant, and
  // confuses things. -fmw, 3/6/07
//   if (pGrid->IsCellSelected(row, col))
//   {
//     len_used = _tcslen(pOutputStr);
//     ptr = pOutputStr + len_used;
//     rv = _snwprintf(ptr, buf_size - len_used, L"%c%s", $SelRange, L"1");
//   }

  // This is used solely for ellipsis buttons in cells.
  if ((pGrid->m_lastButtonClicked.x == row) && (pGrid->m_lastButtonClicked.y == col))
  {
    len_used = _tcslen(pOutputStr);
    ptr = pOutputStr + len_used;
    rv = _snwprintf(ptr, buf_size - len_used, L"%c%s", $Clicked, L"1");
  }

  pCellCheck = (CGridCellCheck*)pGrid->GetCell(row, col);
  if (pCellCheck->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
  {
    len_used = _tcslen(pOutputStr);
    ptr = pOutputStr + len_used;
    rv = _snwprintf(ptr, buf_size - len_used, L"%c%s", $Value,
                    (pCellCheck->GetCheck()) ? L"1" : L"0");
  }

  pGrid->m_lastEdit.x = GRID_VIEW_NO_PENDING_EDIT;
  pGrid->m_lastEdit.y = GRID_VIEW_NO_PENDING_EDIT;

  pOutputStr[buf_size - 1] = 0;

  return pOutputStr;
}


/*****************************************************************************
*   TCHAR *g2pvt_cell_value_of_last_gv_edit (HWND hwndControl)
*
*   Description: the function called by the dialog code when G2 needs to obtain
*     the fully up-to-date "control-value" of the grid-view control.
*   Input Arguments:
*   Returns: Newly malloc'd wide string or NULL.
*   Notes: deals with TCHARs, like the rest of this file, but really must return
*     a wide string.  If it doesn't, things will be bad.
*
*     -----
*   Modifications:
*****************************************************************************/
TCHAR *g2pvt_cell_value_of_last_gv_edit (HWND hwndControl)
{
  CGensymGridCtrl *pGrid;
  TCHAR *pOutputStr;

  pGrid = (CGensymGridCtrl *) CWnd::FromHandle(hwndControl);
  if (pGrid == NULL)
  {
    return new_empty_string();
  }

  pOutputStr = make_control_value_internal(pGrid);
  
  return pOutputStr;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Sending Updates to G2
%
% Description: the code in this section is used to notify G2 of changes to the
%   grid-view control.
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
* void g2pvt_grid_view_check_box_clicked (CGridCellCheck *check_box,
*                                         CPoint PointCellRelative)
*
*   Description: sends a WM_NOTIFY message to the grid-view window indicating
*     that a check-box has been clicked.
*   Input Arguments: the check-box data structure, and the point where the user
*     clicked, which we use to 
*   Returns:
*   Notes: the grid control, as originally downloaded, did not send any messages
*      when a check box is checked or unchecked.  We want to intrude minimally
*      on the source code we downloaded, so instead of inlining this code there,
*      we put the implementation here, and just need to add one line of code to
*      the other file.  Then again, maybe that's not so smart; we can't access
*      protected methods from here.  This function essentially does the same
*      thing as CGridCtrl::SendMessageToParent, but that is a protected method
*      which we can't call from here.  Oh, well.  This is pedantic, but pedantic
*      also means transparent, which is nice.
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_grid_view_check_box_clicked (CGridCellCheck *check_box,
                                        CPoint PointCellRelative)
{
  CGridCtrl *parent_grid;
  HWND gridWnd;
  HWND twngWnd;
  long control_id;
  CCellID cell;
  NM_GRIDVIEW nmgv;

  parent_grid = check_box->GetGrid();
  if (parent_grid == NULL)
  {
    g2pvt_gprintf(G2PVT_ERROR, "could not obtain grid from check box\n");
    return;
  }
  gridWnd = parent_grid->GetSafeHwnd();

  if (!IsWindow(gridWnd))
  {
    g2pvt_gprintf(G2PVT_ERROR, "grid-view HWND not a window\n");
    return;
  }

  twngWnd = GetParent(gridWnd);
  if (IsWindow(twngWnd))
  {
    ZeroMemory((PVOID)&nmgv, sizeof(NM_GRIDVIEW));

    control_id = parent_grid->GetDlgCtrlID();
    cell = parent_grid->GetCellFromPt(PointCellRelative);
    // cell.row and cell.col are, of course, the "C version" of the coordinates;
    // they refer to what we call (row-1, col-1) in Lisp,
    nmgv.iRow         = cell.row;
    nmgv.iColumn      = cell.col;
    nmgv.hdr.hwndFrom = gridWnd;
    nmgv.hdr.idFrom   = control_id;
    nmgv.hdr.code     = GVN_BN_CLICKED;

    SendMessage(twngWnd, WM_NOTIFY, control_id, (LPARAM)&nmgv);
  } else {
    g2pvt_gprintf(G2PVT_ERROR, "gridWnd is a window, but parent isn't\n");
  }
}


/*****************************************************************************
* int get_cell_type (CGensymGridCtrl *pGrid, int row, int col)
*
*   Description: returns the type of the given cell, as one of our ctType
*     constants.
*   Input Arguments: the grid and row and column of the cell we want to know
*     the type of
*   Returns: one of our "ctFoo" constants indicating the type (dyndlg.h)
*   Notes: since we don't subclass CGridCellBase, there's nowhere for us to
*     stash this information, so we have to deduce it at run time, using some
*     pretty heavyweight methods.
*
*     -----
*   Modifications:
*****************************************************************************/
static int get_cell_type (CGensymGridCtrl *pGrid, int row, int col)
{
  CGridCellBase *pCell = pGrid->GetCell(row, col);
  if (!pCell)
    return 0;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCombo)))
    return ctComboBox;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)))
    return ctCheck;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellDuration)))
    return ctDuration;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellInteger)))
    return ctIntegerGridView;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellNumeric)))
    return ctQuantityGridView;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellEllipsis)))
    return ctEllipsisGridView;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellImage)))
    return ctIcon;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellSpinner)))
    return ctSpin;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellFormattedDate)))
        return ctCalendar;
  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellDateTime))) {
    CGridCellDateTime *pDateTime;

    pDateTime = (CGridCellDateTime *) pCell;

    // Note, GetExStyle() is a Gensym modification added specifically for this
    // purpose.  We are unable to tell the difference without this. -jv, 5/03/05
    if (pDateTime->GetExStyle() & DTS_TIMEFORMAT) {
      return ctTimeOfDay;
    } else {
      return ctCalendar;
    }
  }

  else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCell)))
    return ctTextBx;
  else
    return 0;
}

/* Returns a modified response code which guarentees that g2pvt_ddlg_respond
 * will actually send an update to G2, without causing too many other side
 * effects. */
static int ensuring_dialog_response(int response)
{
  return response | DLG_RESPOND;
}

/*****************************************************************************
* LRESULT on_bn_clicked (NM_GRIDVIEW *pgvhdr, HWND hwndDlg,
*                        CONTROLITEM *pcontrol)
*
*   Description: called by g2pvt_grid_view_on_wm_notify if the WM_NOTIFY code
*     was GVN_BN_CLICKED.  If all the data is in good order, sends an update
*     to G2.
*   Input Arguments: the "grid-view notify message header", the HWND of the
*     dialog, and the standard "control" data structure used throughout the
*     dialog code.
*   Returns: TRUE if we can locate the grid-view control from the given
*     pointers, in which case an update is sent to G2.  FALSE, otherwise, which
*     should be considered a serious error (indicative of data corruption.)
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static LRESULT on_bn_clicked (NM_GRIDVIEW *pgvhdr, HWND hwndDlg,
                              CONTROLITEM *pcontrol)
{
  CWnd *pWnd;
  CGensymGridCtrl *pGrid;

  pWnd = g2pvt_get_control_cwnd(pcontrol->_controlId, hwndDlg);
  if (!pWnd)
    return FALSE;

  if (!pWnd->IsKindOf(RUNTIME_CLASS(CGensymGridCtrl)))
    return FALSE;

  pGrid = (CGensymGridCtrl *)pWnd;

  if (ctEllipsisGridView == get_cell_type(pGrid, pgvhdr->iRow, pgvhdr->iColumn))
  {
    pGrid->m_lastButtonClicked.x = pgvhdr->iRow;
    pGrid->m_lastButtonClicked.y = pgvhdr->iColumn;
  }

  pGrid->m_lastEdit.x = pgvhdr->iRow;
  pGrid->m_lastEdit.y = pgvhdr->iColumn;
  g2pvt_ddlg_respond(hwndDlg, pcontrol->_controlId, ensuring_dialog_response(pcontrol->_respcode));

  pGrid->m_lastButtonClicked.x = GRID_VIEW_NO_BUTTON_CLICKED;
  pGrid->m_lastButtonClicked.y = GRID_VIEW_NO_BUTTON_CLICKED;
  return TRUE;
}


/*****************************************************************************
* LRESULT g2pvt_grid_view_on_wm_notify (NMHDR *pnmhdr, HWND hwndDlg,
*                                       CONTROLITEM *pcontrol)
*
*   Description: called by the dialog infrastructure code when a WM_NOTIFY
*     message is sent to the grid-view window.  Ending an edit or clicking
*     a button causes us to update G2, if the control has a response-action
*     saying G2 wants to be notified.  Other types of updates do not cause
*     us to notify G2.  We make sure that the notification type is something
*     we recognize, even if it is not something we respond to.
*   Input Arguments: the "notify message header", the dialog's HWND, and the
*     standard "control" data structure used throughout the dialog code.
*   Returns: TRUE if we recognize the code (whether or not we notify G2 of
*     the event); FALSE in the unlikely case that we don't.
*   Notes: open bugs HQ-5090715, "cells in grid view do not always reflect
*     edits" and HQ-4994518, "combo-box on grid-view takes two clicks to
*     drop down" might be related to how we handle WM_NOTIFY.
*     -----
*   Modifications:
*****************************************************************************/
LRESULT g2pvt_grid_view_on_wm_notify (NMHDR *pnmhdr, HWND hwndDlg,
                                      CONTROLITEM *pcontrol)
{
  CWnd *pWnd;
  CGensymGridCtrl *pGrid;

  pWnd = g2pvt_get_control_cwnd(pcontrol->_controlId, hwndDlg);
  if (!pWnd)
    return FALSE;

  if (!pWnd->IsKindOf(RUNTIME_CLASS(CGensymGridCtrl)))
    return FALSE;

  pGrid = (CGensymGridCtrl *)pWnd;

  switch (pnmhdr->code)
  {
  case GVN_ENDLABELEDIT:
    pGrid->m_lastEdit.x = ((NM_GRIDVIEW *)pnmhdr)->iRow;
    pGrid->m_lastEdit.y = ((NM_GRIDVIEW *)pnmhdr)->iColumn;
    g2pvt_ddlg_respond(hwndDlg, pcontrol->_controlId, ensuring_dialog_response(pcontrol->_respcode));
    return TRUE;
    break;

  case GVN_BN_CLICKED:
    return on_bn_clicked((NM_GRIDVIEW *)pnmhdr, hwndDlg, pcontrol);
    break;

  case NM_CLICK:
  case NM_DBLCLK:
  case NM_RCLICK:
    g2pvt_send_user_gesture_to_g2(hwndDlg, pcontrol,
                                  pGrid->G2Row(((NM_GRIDVIEW *)pnmhdr)->iRow),
                                  pGrid->G2Column(((NM_GRIDVIEW *)pnmhdr)->iColumn),
                                  pnmhdr->code, 0);
    return TRUE;
    break;

  case GVN_SELCHANGING:
  case GVN_COLUMNCLICK:
  case GVN_BEGINDRAG:
  case GVN_BEGINLABELEDIT:
  case GVN_BEGINRDRAG:
  case GVN_GETDISPINFO:
  case GVN_ODCACHEHINT:
    return TRUE;

  case GVN_SELCHANGED:
    return pGrid->SelectionChanged((NM_GRIDVIEW *)pnmhdr, pcontrol->_dialogId, pcontrol->_controlId);

  default:
    g2pvt_gprintf(G2PVT_ERROR, "unrecognized notify message: %d\n", pnmhdr->code);
    break;
  }

  return FALSE;
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP - Modifying Existing Grid-Views
%
% Description: the code in this section is used to implement the functionality
%   offered through %manage-grid-view, i.e., modifying grid-views after they've
%   been posted.
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

#define GRID_VIEW_REFRESH 0        // Keep in sync with lisp/dialogs.lisp
#define GRID_VIEW_DELETE_ROW 1
#define GRID_VIEW_INSERT_ROW 2
#define GRID_VIEW_BACKGROUND_COLOR 3
#define GRID_VIEW_TEXT_COLOR 4
#define GRID_VIEW_CELL_VALUE 5
#define GRID_VIEW_CELL_TYPE 6
#define GRID_VIEW_READ_ONLY 7
#define GRID_VIEW_ROW_HEIGHT 8
#define GRID_VIEW_COLUMN_WIDTH 9
#define GRID_VIEW_COUNT_ROWS 10
#define GRID_VIEW_COUNT_COLUMNS 11
#define GRID_VIEW_CELL_ALIGNMENT 12
#define GRID_VIEW_CELL_SELECTED 13
#define GRID_VIEW_DELETE_COLUMN 14
#define GRID_VIEW_INSERT_COLUMN 15
#define GRID_VIEW_CELL_BOLD 16
#define GRID_VIEW_CELL_IS_MULTILINE 17
#define GRID_VIEW_INSERT_ROW_WITH_INTEGER_LABEL 18
#define GRID_VIEW_GET_HSCROLL_POSITION 19
#define GRID_VIEW_SET_HSCROLL_POSITION 20
#define GRID_VIEW_GET_VSCROLL_POSITION 21
#define GRID_VIEW_SET_VSCROLL_POSITION 22

#ifdef GV_DEBUG
static char *opcodes[] =
{
  "refresh",
    "delete-row",
    "insert-row",
    "background-color",
    "text-color",
    "cell-value",
    "cell-type",
    "read-only",
    "row-height",
    "column-width",
    "count-rows",
    "count-columns"
};
#endif


/*****************************************************************************
* void grid_view_set_cell_type (CGensymGridCtrl *pGrid, int row, int col, int type)
*
*   Description: function to change the type of a cell after the grid-view has
*     already been posted.
*   Input Arguments: the grid, the row and column of the cell, and the new type
*   Returns: nothing
*   Notes:
*     We're using DoGeneralCell here only to get additional value-independent
*     initializations in DoTimeCell, etc. Otherwise, we could do simply:
*       pGrid->SetCellType(row, col, get_cell_class(type))
*
*     -----
*   Modifications:
*****************************************************************************/
static void grid_view_set_cell_type (CGensymGridCtrl *pGrid, int row, int col, int type)
{
  CRichGridItem item(NULL);

  GTRACE("  Setcelltype(%d, %d) = %d\n", row, col, type);

  item.nType = type;
  item.nCRow = row;
  item.nCCol = col;
  item.bEditableSet = FALSE;
  DoGeneralCell(pGrid, &item);
}


/*****************************************************************************
* void grid_view_set_cell_value (CGensymGridCtrl *pGrid, int row, int col,
*                                TCHAR *value)
*
*   Description: function to change the value of a cell after the grid-view has
*     already been posted.
*   Input Arguments: the grid, the row and column of the cell in question, and
*     the new value for the cell, as a string.  This string is the standard,
*     serialized "cell-value" we use in the initial creation of the grid.
*   Returns: nothing
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
static void grid_view_set_cell_value (CGensymGridCtrl *pGrid, int row, int col,
                                      TCHAR *value)
{
  GTRACE("  grid_view_set_cell_value(%d, %d) = \"%ls\"\n", row, col, value);

  CRichGridItem item(value);
  item.nType = get_cell_type(pGrid, row, col);
  item.nCRow = row;
  item.nCCol = col;
  item.bEditableSet = FALSE;

  if (parse_grid_view_string(pGrid, &item)) {
    DoGeneralCell(pGrid, &item);
  } else {
    g2pvt_gprintf(G2PVT_ERROR, "unable to parse incoming cell value: %S\n", value);
  }
}


/*****************************************************************************
* void grid_view_set_read_only (CGensymGridCtrl *pGrid, int row, int col,
*                               BOOL readonly)
*
*   Description: function to change the read-only status of a cell.  Used when
*     modifying a grid-view which has already been posted.  
*   Input Arguments: the grid, the row and column of the cell, and whether
*     read-only should be turned on or off.
*   Returns: nothing
*   Notes: sort of duplicates what may be done in DoStandardStuff, above
*
*     -----
*   Modifications:
*****************************************************************************/
static void grid_view_set_read_only (CGensymGridCtrl *pGrid, int row, int col,
                                     BOOL readonly)
{
  int state = pGrid->GetItemState(row, col);
  pGrid->SetItemState(row, col, readonly ? (state|GVIS_READONLY) : (state&~GVIS_READONLY));
}

/* Similar for selection selected state */
static void grid_view_set_selected (CGensymGridCtrl *pGrid, int row, int col, BOOL selected)
{
  DWORD state = pGrid->GetItemState(row, col);
  BOOL wasSelected = (state & GVIS_SELECTED) != 0;
  if(selected)
    pGrid->SetItemState(row, col, state | GVIS_SELECTED);
  else
    pGrid->SetItemState(row, col, state & ~GVIS_SELECTED);
  if(selected != wasSelected)
    pGrid->RedrawCell(row, col);
}


/*****************************************************************************
 * long g2ext_manage_grid_view (long opcode, long dlgId, long controlId,
 *                              long row, long col,
 *                              long intParam, LPWSTR stringParam)
 *
 *   Description: an API for system procedures to modify the grid-view after it
 *     has posted.
 *   Input Arguments:
 *   Returns: depends on the opcode
 *
 *   Notes: The row and col number here are 0-based, relative to the user's
 *     supplied data.  If the grid has headers, then we want the user's data to
 *     appear inside of them, and so the row and col used in calls to the grid
 *     API must be incremented by 1.
 *     -----
 *   Modifications:
 *****************************************************************************/

clock_t most_recent_update_grid_cell_type = 0;
int most_recent_update_grid_cell_G2row = -1;
int most_recent_update_grid_cell_G2col = -1;

extern "C"
long g2ext_manage_grid_view (long opcode, long dlgId, long controlId,
                             long G2row, long G2col,
                             long intParam, LPWSTR stringParam)
{
  static CPropertyDlg propDlg; // to enter new ID and Description manually
  static int wasInserted = 0;
  static int lastSortColumn, lastSortAscending;

  GENSYMDIALOG *dialog;
  CGensymGridCtrl *pGrid;
  int row, col;
  WCHAR szTmp[65];
  clock_t current_time;

  dialog = g2pvt_find_dialog_by_id(dlgId);
  if (!dialog)
    return DYNAMIC_DIALOG_UPDATE_FAILED;

  pGrid = DYNAMIC_DOWNCAST(CGensymGridCtrl, g2pvt_get_control_cwnd(controlId, dialog->hwnd));
  if(!pGrid)
    return DYNAMIC_DIALOG_UPDATE_FAILED;

#ifdef GV_DEBUG1
  output_grid(pGrid, _T("beginning g2_ext_manage_grid_view"));
#endif

  row = pGrid->PhysicalRow(G2row);
  col = pGrid->PhysicalColumn(G2col);

#ifdef GV_DEBUG
  GTRACE("GRID (%d,%d)->(%d,%d) %dx%d %-12s i=%d s=\"%ls\"\n",
     G2row, G2col, row, col, pGrid->GetRowCount(), pGrid->GetColumnCount(),
     opcodes[opcode], intParam, stringParam);
#endif

  if (pGrid->GetSortColumn() != -1) { //remember last proper sorting
    lastSortColumn = pGrid->GetSortColumn();
    lastSortAscending = pGrid->GetSortAscending();
  }

  switch(opcode) {
   case GRID_VIEW_REFRESH:
     pGrid->Invalidate();
     break;

   case GRID_VIEW_INSERT_ROW:
       pGrid->SetNumericHeader(FALSE);
       pGrid->GensymInsertRow(stringParam, G2row);
       // GENSYMINT-489: delete the line: wasInserted = 2;
       // because after we check the GensymInsertRow function,
       // we found there are no column have been inserted.
     break;
   case GRID_VIEW_INSERT_ROW_WITH_INTEGER_LABEL:    
        _ltow(intParam, szTmp, 10);  
        pGrid->GensymInsertRow(szTmp, G2row);
        wasInserted = 2;
     break;

   case GRID_VIEW_DELETE_ROW:
     pGrid->GensymDeleteRow(G2row);
     break;

   case GRID_VIEW_INSERT_COLUMN:
     pGrid->GensymInsertColumn(stringParam, G2col);
     break;

   case GRID_VIEW_DELETE_COLUMN:
     pGrid->GensymDeleteColumn(G2col);
     break;

   case GRID_VIEW_BACKGROUND_COLOR:
     pGrid->SetItemBkColour(row, col, (COLORREF)intParam);
     break;

   case GRID_VIEW_TEXT_COLOR:
     pGrid->SetItemFgColour(row, col, (COLORREF)intParam);
     break;

   case GRID_VIEW_CELL_VALUE:
     if (wasInserted > 0) {
         LPCTSTR ps = _T("");
         CString ts("T");
         if (col == 1) {
            ps = ts + propDlg.m_id + $StrDelim;
         } else if (col == 2) {
            ps = ts + propDlg.m_description + $StrDelim;
         }
         wasInserted--;
         grid_view_set_cell_value(pGrid, row, col, (unsigned short *)ps);
     } else {
         grid_view_set_cell_value(pGrid, row, col, stringParam);
     }
     break;

   case GRID_VIEW_READ_ONLY:
     grid_view_set_read_only(pGrid, row, col, intParam != 0);
     break;

   case GRID_VIEW_CELL_TYPE:
     current_time = clock();
     if (current_time<most_recent_update_grid_cell_type+30 &&
         most_recent_update_grid_cell_G2row == row &&
     most_recent_update_grid_cell_G2col == col) break;
     most_recent_update_grid_cell_type = clock();
     most_recent_update_grid_cell_G2row = row;
     most_recent_update_grid_cell_G2col = col;
     grid_view_set_cell_type(pGrid, row, col, intParam);
     break;

   case GRID_VIEW_CELL_ALIGNMENT:
     pGrid->SetItemFormat(row, col, intParam);
     break;

   case GRID_VIEW_CELL_BOLD:
     pGrid->SetItemBold(row, col, intParam==1);
     break;

   case GRID_VIEW_CELL_SELECTED:
     grid_view_set_selected(pGrid, row, col, intParam != 0);
     break;

   case GRID_VIEW_ROW_HEIGHT:
     pGrid->SetRowHeight(row, intParam);
     break;

   case GRID_VIEW_COLUMN_WIDTH:
     pGrid->SetColumnWidth(col, intParam);
     break;

   case GRID_VIEW_CELL_IS_MULTILINE:
     // Not implemented by Softserve. --binghe
     break;

   case GRID_VIEW_COUNT_ROWS:
     return pGrid->GetRowCount(); // Note that this is the physical row count, including fixed rows.

   case GRID_VIEW_COUNT_COLUMNS:
     return pGrid->GetColumnCount(); // Ditto for columns

   case GRID_VIEW_GET_HSCROLL_POSITION:
     return pGrid->GetScrollPos(SB_HORZ);

   case GRID_VIEW_SET_HSCROLL_POSITION:
     pGrid->SetScrollPos(SB_HORZ, intParam);
     break;

   case GRID_VIEW_GET_VSCROLL_POSITION:
     return pGrid->GetScrollPos(SB_VERT);

   case GRID_VIEW_SET_VSCROLL_POSITION:
     pGrid->SetScrollPos(SB_VERT, intParam);
     break;
  }
  return 0;
}


/*****************************************************************************
 * BOOL g2pvt_use_numeric_sort_on_gv_col (CGridCtrl *grid, int nCol)
 *
 *   Description: determines whether the data in a given column is numeric
 *   Input Arguments: a grid and a column index to check
 *   Returns: whether or not the column contains exclusively numeric data
 *   Notes: the criterion for sorting a column numerically is that every cell
 *     in the column is typed as one of the two existing numeric cell-types.
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL g2pvt_use_numeric_sort_on_gv_col (CGridCtrl *pGrid, int nCol)
{
  int row, cell_type;

  for (row = pGrid->GetFixedRowCount();
       row < pGrid->GetRowCount();
       row++)
  {
    cell_type = get_cell_type((CGensymGridCtrl *)pGrid, row, nCol);
    if ((cell_type != ctIntegerGridView) && (cell_type != ctQuantityGridView))
      return FALSE;
  }

  return TRUE;
}
