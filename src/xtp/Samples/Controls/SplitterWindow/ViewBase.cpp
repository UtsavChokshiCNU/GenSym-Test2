// ViewBase.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplitterWindow.h"
#include "ViewBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewBase

IMPLEMENT_DYNCREATE(CViewBase, CView)

CViewBase::CViewBase()
{
	LOGFONT lf;
	XTPAuxData().fontBold.GetLogFont(&lf);
	lf.lfHeight = -72;
	m_font.CreateFontIndirect(&lf);
}

CViewBase::~CViewBase()
{
}

BEGIN_MESSAGE_MAP(CViewBase, CView)
	//{{AFX_MSG_MAP(CViewBase)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewBase drawing

void CViewBase::OnDraw(CDC* pDC)
{
	CXTPFontDC fontDC(pDC, &m_font);

	CRect rc;
	GetClientRect(&rc);
	pDC->DrawText(m_strView, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/////////////////////////////////////////////////////////////////////////////
// CViewBase diagnostics

#ifdef _DEBUG
void CViewBase::AssertValid() const
{
	CView::AssertValid();
}

void CViewBase::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewBase message handlers

void CViewBase::OnPaint()
{
	CPaintDC dc(this);

	// Get the client rect.
	CRect rectClient;
	GetClientRect(&rectClient);

	// Paint to a memory device context to reduce screen flicker.
	CXTPBufferDC memDC(dc, rectClient);
	memDC.FillSolidRect(rectClient, GetXtremeColor(COLOR_WINDOW));

	OnPrepareDC(&memDC);
	OnDraw(&memDC);
}

BOOL CViewBase::OnEraseBkgnd(CDC* pDC)
{
	UNUSED_ALWAYS(pDC);
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CView1

IMPLEMENT_DYNCREATE(CView1, CViewBase)

CView1::CView1()
{
	m_strView = _T("1");
}

CView1::~CView1()
{
}

/////////////////////////////////////////////////////////////////////////////
// CView2

IMPLEMENT_DYNCREATE(CView2, CViewBase)

CView2::CView2()
{
	m_strView = _T("2");
}

CView2::~CView2()
{
}

/////////////////////////////////////////////////////////////////////////////
// CView3

IMPLEMENT_DYNCREATE(CView3, CViewBase)

CView3::CView3()
{
	m_strView = _T("3");
}

CView3::~CView3()
{
}

/////////////////////////////////////////////////////////////////////////////
// CView4

IMPLEMENT_DYNCREATE(CView4, CViewBase)

CView4::CView4()
{
	m_strView = _T("4");
}

CView4::~CView4()
{
}

/////////////////////////////////////////////////////////////////////////////
// CView5

IMPLEMENT_DYNCREATE(CView5, CViewBase)

CView5::CView5()
{
	m_strView = _T("5");
}

CView5::~CView5()
{
}
