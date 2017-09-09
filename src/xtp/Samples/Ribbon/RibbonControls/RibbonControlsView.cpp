// RibbonControlsView.cpp : implementation of the CRibbonControlsView class
//

#include "stdafx.h"
#include "RibbonControls.h"

#include "RibbonControlsDoc.h"
#include "RibbonControlsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView

IMPLEMENT_DYNCREATE(CRibbonControlsView, CView)

BEGIN_MESSAGE_MAP(CRibbonControlsView, CView)
	//{{AFX_MSG_MAP(CRibbonControlsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView construction/destruction

CRibbonControlsView::CRibbonControlsView()
{
	// TODO: add construction code here

}

CRibbonControlsView::~CRibbonControlsView()
{
}

BOOL CRibbonControlsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView drawing

void CRibbonControlsView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView printing

BOOL CRibbonControlsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRibbonControlsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRibbonControlsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView diagnostics

#ifdef _DEBUG
void CRibbonControlsView::AssertValid() const
{
	CView::AssertValid();
}

void CRibbonControlsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRibbonControlsDoc* CRibbonControlsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRibbonControlsDoc)));
	return (CRibbonControlsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsView message handlers
