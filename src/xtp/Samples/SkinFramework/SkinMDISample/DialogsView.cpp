// DialogsView.cpp : implementation file
//

#include "stdafx.h"
#include "skinmdisample.h"
#include "DialogsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogsView

IMPLEMENT_DYNCREATE(CDialogsView, CFormView)

CDialogsView::CDialogsView()
	: CFormView(CDialogsView::IDD)
{
	//{{AFX_DATA_INIT(CDialogsView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDialogsView::~CDialogsView()
{
}

void CDialogsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogsView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogsView, CFormView)
	//{{AFX_MSG_MAP(CDialogsView)
	ON_BN_CLICKED(IDC_BUTTON_COLORDIALOG, OnButtonColordialog)
	ON_BN_CLICKED(IDC_BUTTON_FONTDIALOG, OnButtonFontdialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINTDIALOG, OnButtonPrintdialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENDIALOG, OnButtonOpendialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogsView diagnostics

#ifdef _DEBUG
void CDialogsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDialogsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDialogsView message handlers

void CDialogsView::OnButtonColordialog() 
{
	CColorDialog cd;
	cd.DoModal();
	
}

void CDialogsView::OnButtonFontdialog() 
{
	CFontDialog fd;
	fd.DoModal();
	
}

void CDialogsView::OnButtonPrintdialog() 
{
	CPrintDialog pd(TRUE);
	pd.DoModal();
	
}

void CDialogsView::OnButtonOpendialog() 
{
	CFileDialog fd(TRUE);
	fd.DoModal();
	
}

void CDialogsView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	ResizeParentToFit();
}
