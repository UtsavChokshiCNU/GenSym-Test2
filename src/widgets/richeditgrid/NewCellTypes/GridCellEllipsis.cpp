// GridCellEllipsis.cpp: implementation of the CGridCellEllipsis class.
// 
// Heidi Goddard
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCellEllipsis.h"
#include "GridExtras.h"
#define ICON_WIDTH 16

IMPLEMENT_DYNCREATE(CGridCellEllipsis, CGridCell)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CGridCellEllipsis::ProcessClickMessage(CPoint PointCellRelative)
{
	NM_GRIDVIEW nmgv;
	CGridCtrl *pParentGrid;
	HWND hParentWnd;
    TRACE(_T("Inside GridCellEllipsis::OnProcessClickMessage \n"));

	pParentGrid = GetGrid();
 
	hParentWnd = GetParent(pParentGrid->m_hWnd);
   // PointCellRelative is relative to the topleft of the cell. Convert to client coords
    PointCellRelative += m_rectCell.TopLeft();
    CCellID cell = GetGrid()->GetCellFromPt(PointCellRelative);
    if (!GetGrid()->IsCellEditable(cell))		
        return;
	if (m_IconArea.PtInRect(PointCellRelative))
	{
		TRACE(_T("OnClick Hit!\n"));

		nmgv.iRow         = cell.row;
		nmgv.iColumn      = cell.col;
		nmgv.hdr.hwndFrom = (this->GetGrid())->m_hWnd;
		nmgv.hdr.idFrom   = pParentGrid->GetDlgCtrlID();
		nmgv.hdr.code     = GVN_BN_CLICKED;

		SendMessage(hParentWnd, WM_NOTIFY, pParentGrid->GetDlgCtrlID(), (LPARAM)&nmgv);
		m_bEditing = TRUE;
	}
}

// Create a control to do the editing
BOOL CGridCellEllipsis::Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar)
{
    TRACE(_T("Do external edit of this cell\n"));
	m_bEditing = TRUE;
	ProcessClickMessage(point);
	return TRUE;
}

void CGridCellEllipsis::OnClick(CPoint PointCellRelative)
{
	ProcessClickMessage(PointCellRelative);
}


// Cancel the editing.
void CGridCellEllipsis::EndEdit()
{
    TRACE(_T("End editing (pop-down dialog)\n"));
	m_bEditing = FALSE;

}

// Override draw 
BOOL CGridCellEllipsis::Draw(CDC* pDC, int nRow, int nCol, CRect rect,  BOOL bEraseBkgnd /*=TRUE*/)
{   

	BOOL bResult = CGridCell::Draw(pDC, nRow, nCol, rect, bEraseBkgnd);

	CRect r = rect;
	r.left = rect.right - ICON_WIDTH;
	r.bottom = rect.top + ICON_WIDTH;


	m_IconArea = r; // Save for use in OnClick

	m_rectCell = rect;
	// Draw this only if it fits. Otherwise, it will spill over the cell's gird lines */
	if ( ((rect.right - rect.left) > ICON_WIDTH) && ((rect.bottom -rect.top) > ICON_WIDTH ))
	{

		HINSTANCE hInst = AfxGetInstanceHandle();
        HICON hIcon = (HICON)LoadImage(hInst, _T("ELLIPSIS"), IMAGE_ICON, 16, 16, 0);
        DrawIconEx(pDC->m_hDC, r.left, r.top, hIcon, 16, 16, 0, NULL, DI_NORMAL);
		//Gensym-170-HQ-5699700-TWNG GDI leak
		DestroyIcon(hIcon);
		//Gensym-170-HQ-5699700-TWNG GDI leak
  
	}
    return bResult;

}
 

