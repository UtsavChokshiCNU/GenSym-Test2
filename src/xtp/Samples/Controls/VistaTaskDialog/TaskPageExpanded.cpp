// TaskPageExpanded.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"
#include "TaskSheetProperties.h"
#include "TaskPageExpanded.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPageExpanded property page

IMPLEMENT_DYNCREATE(CTaskPageExpanded, CPropertyPage)

CTaskPageExpanded::CTaskPageExpanded() : CPropertyPage(CTaskPageExpanded::IDD)
{
	//{{AFX_DATA_INIT(CTaskPageExpanded)
	m_bByDefault = FALSE;
	m_bFooterArea = FALSE;
	m_strCollapsedControlText = _T("Details");
	m_strExpandedControlText = _T("Hide Details");
	m_strExpandedInformation = _T("Details:      C:\\Program Files\\Codejock Software\\Xtreme ToolkitPro");
	//}}AFX_DATA_INIT

	//m_strExpandedInformation.LoadString(IDS_EXPANDEDINFORMATION);
}

CTaskPageExpanded::~CTaskPageExpanded()
{
}

void CTaskPageExpanded::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskPageExpanded)
	DDX_Check(pDX, IDC_CHK_BYDEFAULT, m_bByDefault);
	DDX_Check(pDX, IDC_CHK_FOOTERAREA, m_bFooterArea);
	DDX_Text(pDX, IDC_EDIT_COLLAPSEDCONT, m_strCollapsedControlText);
	DDX_Text(pDX, IDC_EDIT_EXPANDEDCONT, m_strExpandedControlText);
	DDX_Text(pDX, IDC_EDIT_EXPANDEDINFO, m_strExpandedInformation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskPageExpanded, CPropertyPage)
	//{{AFX_MSG_MAP(CTaskPageExpanded)
	ON_EN_CHANGE(IDC_EDIT_EXPANDEDINFO, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_EXPANDEDCONT, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_COLLAPSEDCONT, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_BYDEFAULT, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_FOOTERAREA, OnUpdateData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPageExpanded message handlers

void CTaskPageExpanded::OnUpdateData()
{
	UpdateData();
}

BOOL CTaskPageExpanded::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, GetParent());
	ASSERT_VALID(m_pDlgParent);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTaskPageExpanded::OnSetActive()
{
	if (!CPropertyPage::OnSetActive())
		return FALSE;

	return TRUE;
}
