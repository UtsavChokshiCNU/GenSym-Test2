// GridCellImage.cpp: implementation of the CGridCellImage class.
// 
// Heidi Goddard
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCtrl.h"
#include "GridCellImage.h"
#include "GridExtras.h"
#define ICON_WIDTH 32

IMPLEMENT_DYNCREATE(CGridCellImage, CGridCell)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
// the Draw method is used just to get the rectangle of interest for use in OnClick.
BOOL CGridCellImage::Draw(CDC* pDC, int nRow, int nCol, CRect rect,  BOOL bEraseBkgnd /*=TRUE*/)
{   

	BOOL bResult = CGridCell::Draw(pDC, nRow, nCol, rect, bEraseBkgnd);

	CRect r = rect;
	r.right = rect.left + ICON_WIDTH;
	r.bottom = rect.top + ICON_WIDTH;


	m_IconArea = r; // Save for use in OnClick

	m_rectCell = rect;
	return bResult;
}

// Do't do anythin on edit, just leave
BOOL CGridCellImage::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar)
{
  //    TRACE(_T("Do external edit of this cell\n"));
	m_bEditing = TRUE;
	return TRUE;
}
// if the user clicks in an editable cell on top of the icon, send a message
void CGridCellImage::OnClick(CPoint PointCellRelative)
{
	NM_GRIDVIEW nmgv;
	CGridCtrl *pParentGrid;
	HWND hParentWnd;

	pParentGrid = GetGrid();
 
	hParentWnd = GetParent(pParentGrid->m_hWnd);
   // PointCellRelative is relative to the topleft of the cell. Convert to client coords
    PointCellRelative += m_rectCell.TopLeft();
    CCellID cell = GetGrid()->GetCellFromPt(PointCellRelative);
    if (!GetGrid()->IsCellEditable(cell))		
        return;
 
	if (m_IconArea.PtInRect(PointCellRelative))
	{
	  // TRACE(_T("OnClick Hit!\n"));

		nmgv.iRow         = cell.row;
		nmgv.iColumn      = cell.col;
		nmgv.hdr.hwndFrom = (this->GetGrid())->m_hWnd;
		nmgv.hdr.idFrom   = pParentGrid->GetDlgCtrlID();
		nmgv.hdr.code     = GVN_BN_CLICKED;

		SendMessage(hParentWnd, WM_NOTIFY, pParentGrid->GetDlgCtrlID(), (LPARAM)&nmgv);
		m_bEditing = TRUE;
	}
}


// Cancel the editing.
void CGridCellImage::EndEdit()
{
  // TRACE(_T("End editing (pop-down dialog)\n"));
	m_bEditing = FALSE;
}
