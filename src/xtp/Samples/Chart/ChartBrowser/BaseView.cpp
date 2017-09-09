// BaseView.cpp : implementation file
//

#include "stdafx.h"
#include "ChartBrowser.h"
#include "BaseView.h"



/////////////////////////////////////////////////////////////////////////////
// CResizeGroupBox

CResizeGroupBox::CResizeGroupBox()
{
}

CResizeGroupBox::~CResizeGroupBox()
{
}

IMPLEMENT_DYNAMIC(CResizeGroupBox, CXTPButton)

BEGIN_MESSAGE_MAP(CResizeGroupBox, CXTPButton)
//{{AFX_MSG_MAP(CResizeGroupBox)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeGroupBox message handlers

void CResizeGroupBox::Exclude(CDC* pDC, CRect& rcClient)
{
	// get a pointer to the parent.
	CWnd* pWndParent = GetParent();
	if (!pWndParent)
		return;
	
	// get a pointer to the parents first child.
	CWnd* pWnd = pWndParent->GetWindow(GW_CHILD);
	if (pWnd == NULL)
		return;
	
	// iterate thru all children and exclude those children that
	// are located inside the group box.
	CWnd* pChildWnd = pWnd->GetWindow(GW_HWNDFIRST);
	while (pChildWnd != NULL)
	{
		// make sure we do not exclude ourself
		if (pChildWnd != this && pChildWnd->IsWindowVisible())
		{
			CRect rc;
			pChildWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			
			// if the parent's child is located in our group box, exclude
			// it from painting.
			if (rcClient.PtInRect(rc.TopLeft()) ||
				rcClient.PtInRect(rc.BottomRight()))
			{
				pDC->ExcludeClipRect(&rc);
			}
		}
		
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CResizeGroupBox::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CResizeGroupBox::OnPaint()
{
	CPaintDC dc(this);
	
	// get the client area size.
	CRect rcClient;
	GetClientRect(&rcClient);
	
	// exclude controls that we "group"
	Exclude(&dc, rcClient);
	
	// Paint to a memory device context to help
	// eliminate screen flicker.
	CXTPBufferDC memDC(dc);
	
	HBRUSH hBrush = (HBRUSH)GetParent()->SendMessage(WM_CTLCOLORBTN, (WPARAM)memDC.GetSafeHdc(), (LRESULT)m_hWnd);
	if (hBrush)
	{
		::FillRect(memDC, rcClient, hBrush);
	}
	else
	{
		memDC.FillSolidRect(rcClient, GetSysColor(COLOR_3DFACE));
	}
	
#ifdef _XTP_INCLUDE_TOOLKIT
	OnDraw(&memDC);
#else
	// Let the window do its default painting...
	CButton::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);
#endif
}


// CBaseView

IMPLEMENT_DYNAMIC(CBaseView, CFormView)

CBaseView::CBaseView(const UINT nID)	: CFormView(nID)
{
#ifdef _XTP_INCLUDE_TOOLKIT
	m_hBrush.CreateSolidBrush(RGB(227,239,255));
#else
	m_hBrush.CreateSolidBrush(RGB(255, 255, 255));
#endif

}

CBaseView::~CBaseView()
{
}

void CBaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseView, CFormView)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CBaseView diagnostics

#ifdef _DEBUG
void CBaseView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseView message handlers

BOOL CBaseView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CFormView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

void CBaseView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	m_wndGroupBoxLabels.SubclassDlgItem(IDC_STATIC_LABELS, this);	


	CXTPWindowRect rc(m_wndChartControl);
	ScreenToClient(rc);
	m_nTopGap = rc.top;
	m_nLeftGap = rc.left;

	
#ifdef _XTP_INCLUDE_TOOLKIT
	m_wndGroupBoxLabels.SetTheme(xtpControlThemeResource);
#endif


}


HBRUSH CBaseView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_hBrush;
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CBaseView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);


	if (!m_wndGroupBoxLabels.GetSafeHwnd())
		return;

	CXTPWindowRect rc(m_wndGroupBoxLabels);

	int nWidth = max(m_totalDev.cx, cx);


	m_wndGroupBoxLabels.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, rc.Height(), SWP_NOMOVE | SWP_NOZORDER);

	int nHeight = max(m_totalDev.cy, cy);

	m_wndChartControl.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, nHeight - m_nTopGap - m_nLeftGap, SWP_NOMOVE | SWP_NOZORDER);
}

BOOL CBaseView::OnEraseBkgnd(CDC* pDC)
{
	return CFormView::OnEraseBkgnd(pDC);
}