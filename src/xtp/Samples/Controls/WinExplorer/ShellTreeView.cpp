// ShellTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "WinExplorer.h"
#include "ShellTreeView.h"
#include "ShellListView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView

IMPLEMENT_DYNCREATE(CShellTreeView, CXTPShellTreeView)

CShellTreeView::CShellTreeView()
{
	m_pListView = 0;
}

CShellTreeView::~CShellTreeView()
{
}


BEGIN_MESSAGE_MAP(CShellTreeView, CXTPShellTreeView)
	//{{AFX_MSG_MAP(CShellTreeView)
 	ON_WM_NCCALCSIZE()
 	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView drawing

void CShellTreeView::OnDraw(CDC* /*pDC*/)
{
}


void CShellTreeView::OnInitialUpdate()
{
	CXTPShellTreeView::OnInitialUpdate();

	SetExplorerStyle();
}

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView diagnostics

#ifdef _DEBUG
void CShellTreeView::AssertValid() const
{
	CXTPShellTreeView::AssertValid();
}

void CShellTreeView::Dump(CDumpContext& dc) const
{
	CXTPShellTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShellTreeView message handlers

void CShellTreeView::SelectParentItem()
{
    if (::IsWindow(GetTreeCtrl().m_hWnd))
    {
        HTREEITEM htItem = GetTreeCtrl().GetSelectedItem();
        if (htItem != GetTreeCtrl().GetRootItem())
        {
            GetTreeCtrl().SelectItem(GetTreeCtrl().GetParentItem(htItem));
            GetTreeCtrl().SetFocus();
        }
    }
}

BOOL CShellTreeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CXTPShellTreeView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_STATICEDGE;
	
	return TRUE;
}

int CShellTreeView::GetHeaderHeight() const
{
	if (m_pListView)
	{
		CListCtrl* pListCtrl = &m_pListView->GetListCtrl();
		if (::IsWindow(pListCtrl->GetSafeHwnd()))
		{
			CHeaderCtrl* pHeader = pListCtrl->GetHeaderCtrl();
			if (::IsWindow(pHeader->GetSafeHwnd()))
			{
				CRect rc;
				pHeader->GetWindowRect(&rc);
				return rc.Height();
			}
		}
	}
	return 19; // default size.
}

void CShellTreeView::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc[0].top = GetHeaderHeight() + 3;
	CXTPShellTreeView::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CShellTreeView::OnNcPaint() 
{
	// code block: paint scrollbars first.
	{
		Default();
	}

	CWindowDC dc(this);

	CXTPWindowRect rWindow(this);
	rWindow.OffsetRect(-rWindow.TopLeft());

	dc.Draw3dRect(&rWindow, GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHIGHLIGHT));

	// draw psudo caption.
	rWindow.DeflateRect(1, 1);
	rWindow.bottom = rWindow.top + GetHeaderHeight();

	dc.FillSolidRect(rWindow.left, rWindow.bottom, rWindow.Width(), 1, GetXtremeColor(COLOR_WINDOW));

	CXTPBufferDC memDC(dc, rWindow);

	memDC.FillSolidRect(rWindow, GetXtremeColor(COLOR_3DFACE));	
	memDC.Draw3dRect(&rWindow, GetXtremeColor(COLOR_3DHIGHLIGHT), GetXtremeColor(COLOR_3DSHADOW));

	CXTPFontDC fontDC(&memDC, &XTPAuxData().font);

	rWindow.DeflateRect(4,2);
	memDC.SetBkMode(TRANSPARENT);
	memDC.DrawText(_T("Folders"), &rWindow, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
}
