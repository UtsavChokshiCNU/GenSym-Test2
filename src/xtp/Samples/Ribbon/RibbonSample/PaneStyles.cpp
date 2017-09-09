// PaneStyles.cpp : implementation file
//

#include "stdafx.h"
#include "ribbonsample.h"
#include "PaneStyles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPaneStyles dialog


CPaneStyles::CPaneStyles(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CPaneStyles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaneStyles)
	//}}AFX_DATA_INIT
}


void CPaneStyles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaneStyles)
	DDX_Control(pDX, IDC_LIST_STYLES, m_lstStyles);
	DDX_Control(pDX, IDC_CHECK_LINKEDSTYLE, m_chkLinkedStyle);
	DDX_Control(pDX, IDC_CHECK_PREVIEW, m_chkPreview);
	DDX_Control(pDX, IDC_BUTTON_STYLEINSPECTOR, m_btnStyleInspector);
	DDX_Control(pDX, IDC_BUTTON_NEWSTYLE, m_btnNewStyle);
	DDX_Control(pDX, IDC_BUTTON_MANAGESTYLES, m_btnManageStyles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaneStyles, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CPaneStyles)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneStyles message handlers

void CPaneStyles::OnCancel()
{
}

void CPaneStyles::OnOK()
{
}

HBRUSH CPaneStyles::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	return m_brush;
}

BOOL CPaneStyles::OnInitDialog() 
{
	CXTPResizeDialog::OnInitDialog();
	
	SetResize(IDC_LIST_STYLES,       XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);

	SetResize(IDC_CHECK_PREVIEW,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_CHECK_LINKEDSTYLE,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_NEWSTYLE,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_STYLEINSPECTOR,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_BUTTON_MANAGESTYLES,     XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);

	m_lstStyles.AddString(_T("Clear All"));
	m_lstStyles.AddString(_T("Normal"));
	m_lstStyles.AddString(_T("No Spacing"));
	m_lstStyles.AddString(_T("Heading 1"));
	m_lstStyles.AddString(_T("Heading 2"));
	m_lstStyles.AddString(_T("Heading 3"));
	m_lstStyles.AddString(_T("Title"));
	m_lstStyles.AddString(_T("Subtitle"));


	CXTPImageManagerIconHandle ih;
	CXTPImageManagerIconHandle ihh;
	
	ih = CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_NEWSTYLE), NULL);
	m_btnNewStyle.SetIcon(CSize(16, 16), ih, ihh);

	ih = CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_MANAGESTYLES), NULL);
	m_btnManageStyles.SetIcon(CSize(16, 16), ih, ihh);

	ih = CXTPImageManagerIcon::LoadBitmapFromResource(MAKEINTRESOURCE(IDC_BUTTON_STYLEINSPECTOR), NULL);
	m_btnStyleInspector.SetIcon(CSize(16, 16), ih, ihh);

	RefreshMetrics(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaneStyles::RefreshMetrics(BOOL bOffice2007)
{
	m_brush.DeleteObject();

	if (bOffice2007)
	{
		COLORREF clr = XTPResourceImages()->GetImageColor(_T("DockingPane"), _T("WordPaneBackground"));
		m_brush.CreateSolidBrush(clr);

		m_chkLinkedStyle.SetTheme(xtpControlThemeResource);
		m_chkPreview.SetTheme(xtpControlThemeResource);
		m_btnStyleInspector.SetTheme(xtpControlThemeResource);
		m_btnNewStyle.SetTheme(xtpControlThemeResource);
		m_btnManageStyles.SetTheme(xtpControlThemeResource);

		m_lstStyles.SetListStyle(xtpListBoxOffice2007);

	}
	else
	{
		m_brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

		m_chkLinkedStyle.SetTheme(xtpControlThemeOfficeXP);
		m_chkPreview.SetTheme(xtpControlThemeOfficeXP);
		m_btnStyleInspector.SetTheme(xtpControlThemeOfficeXP);
		m_btnNewStyle.SetTheme(xtpControlThemeOfficeXP);
		m_btnManageStyles.SetTheme(xtpControlThemeOfficeXP);

		m_lstStyles.SetListStyle(xtpListBoxOfficeXP);
	}
}

