// SampleView.cpp : implementation file
//

#include "stdafx.h"
#include "SkinSDISample.h"
#include "SampleView.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CFormView)

CSampleView::CSampleView()
	: CFormView(CSampleView::IDD)
{
	//{{AFX_DATA_INIT(CSampleView)
	m_nSkin = 0;
	m_nTheme = 1;
	m_strFind = _T("");
	m_bMatchCase = FALSE;
	m_bMatchWord = FALSE;
	m_bFlat = FALSE;
	m_bShowGripper = TRUE;
	//}}AFX_DATA_INIT
}

CSampleView::~CSampleView()
{
}

void CSampleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleView)
	DDX_Radio(pDX, IDC_RADIO_LE5, m_nSkin);
	DDX_Radio(pDX, IDC_RADIO_OFFICE2003, m_nTheme);
	DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
	DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_bMatchCase);
	DDX_Check(pDX, IDC_CHECK_MATCHWORD, m_bMatchWord);
	DDX_Check(pDX, IDC_CHECK_FLAT, m_bFlat);
	DDX_Check(pDX, IDC_CHECK_GRIPPER, m_bShowGripper);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSampleView, CFormView)
	//{{AFX_MSG_MAP(CSampleView)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_COLORDIALOG, OnButtonColordialog)
	ON_BN_CLICKED(IDC_BUTTON_FONTDIALOG, OnButtonFontdialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINTDIALOG, OnButtonPrintdialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENDIALOG, OnButtonOpendialog)
	ON_BN_CLICKED(IDC_RADIO_LE5, OnSkinChanged)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnThemeChanged)
	ON_BN_CLICKED(IDC_CHECK_FLAT, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_ITUNES, OnSkinChanged)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnSkinChanged)
	ON_BN_CLICKED(IDC_RADIO_WINXP, OnThemeChanged)
	ON_EN_CHANGE(IDC_EDIT_FIND, OnChangeEditFind)
	ON_BN_CLICKED(IDC_CHECK_GRIPPER, OnCheckGripper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleView message handlers

void CSampleView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

}


void CSampleView::OnButtonFind() 
{
	UpdateData();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	CRichEditView* pView = (CRichEditView*)pWnd->m_wndSplitter.GetPane(0, 1);	
	
	if (!pView->FindText(m_strFind, m_bMatchCase, m_bMatchWord))
	{
		pView->TextNotFound(m_strFind);
	}
	
}
void CSampleView::OnChangeEditFind() 
{
	UpdateData();

	GetDlgItem(IDC_BUTTON_FIND)->EnableWindow(!m_strFind.IsEmpty());
}


void CSampleView::OnButtonColordialog() 
{
	CColorDialog cd;
	cd.DoModal();
	
}

void CSampleView::OnButtonFontdialog() 
{
	CFontDialog fd;
	fd.DoModal();
	
}

void CSampleView::OnButtonPrintdialog() 
{
	CPrintDialog pd(TRUE);
	pd.DoModal();
	
}

void CSampleView::OnButtonOpendialog() 
{
	CFileDialog fd(TRUE);

	if (XTPSystemVersion()->IsWin2KOrGreater() && sizeof(OPENFILENAME) < 88 && fd.m_ofn.lStructSize < 88)
	{
		// Windows 2000 version of OPENFILENAME has three extra members,
		// this was copied from newer version of commdlg.h...
		
		struct OPENFILENAMEEX
		{
			void*  pvReserved; // 4 bytes
			DWORD  dwReserved; // 4 bytes
			DWORD  FlagsEx;    // 4 bytes
		};
		
		fd.m_ofn.lStructSize += sizeof(OPENFILENAMEEX); // should equal an additional 12 bytes;
	}

	fd.DoModal();
	
}

void CSampleView::OnSkinChanged() 
{
	UpdateData();
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	pWnd->LoadSkin(m_nSkin);	
}

void CSampleView::OnThemeChanged() 
{
	UpdateData();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	pWnd->SetTheme(m_nTheme, m_bFlat);
}

void CSampleView::OnCheckGripper()
{
	UpdateData();
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();

	pWnd->GetCommandBars()->GetAt(0)->SetShowGripper(m_bShowGripper);
	pWnd->GetCommandBars()->GetAt(1)->SetShowGripper(m_bShowGripper);
	pWnd->GetCommandBars()->RedrawCommandBars();
}
 

