// TaskPageGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"
#include "TaskSheetProperties.h"
#include "TaskPageGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR SAMPLE_TEXT[] = _T("Xxxx ");

/////////////////////////////////////////////////////////////////////////////
// CTaskPageGeneral property page

IMPLEMENT_DYNCREATE(CTaskPageGeneral, CPropertyPage)

CTaskPageGeneral::CTaskPageGeneral() : CPropertyPage(CTaskPageGeneral::IDD)
{
	//{{AFX_DATA_INIT(CTaskPageGeneral)
	m_bAllowCancel = TRUE;
	m_bHyperLinks = TRUE;
	m_bMarquee = FALSE;
	m_bPosition = FALSE;
	m_bProgress = FALSE;
	m_bRtl = FALSE;
	m_bVerify = FALSE;
	m_bWidth = TRUE;
	m_strContent = _T("Content");
	m_strFooter = _T("Footer");
	m_strMainInstruction = _T("Main Instruction");
	m_strWindowTitle = _T("Window Title");
	m_strVerificationText = _T("");
	m_nCount = 5;
	m_nWidth = 430;
	//}}AFX_DATA_INIT

	m_strWindowTitle.LoadString(IDS_WINDOWTITLE);
	m_strMainInstruction.LoadString(IDS_MAININSTRUCTION);
	m_strContent.LoadString(IDS_CONTENT);
	m_strFooter.LoadString(IDS_FOOTER);
	//m_strVerificationText.LoadString(IDS_EDIT_VERIFY);

	//m_strContent = _T("How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? How much do you like TaskDialogs? ");
	//m_strMainInstruction.Empty();

	//for (int i = 0; i < m_nCount; i += 5)
	//{
	//	m_strMainInstruction += SAMPLE_TEXT; 
	//}
}

CTaskPageGeneral::~CTaskPageGeneral()
{
}

void CTaskPageGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskPageGeneral)
	DDX_Check(pDX, IDC_CHK_ALLOWCANCEL, m_bAllowCancel);
	DDX_Check(pDX, IDC_CHK_HYPERLINKS, m_bHyperLinks);
	DDX_Check(pDX, IDC_CHK_MARQUEE, m_bMarquee);
	DDX_Check(pDX, IDC_CHK_POSITION, m_bPosition);
	DDX_Check(pDX, IDC_CHK_PROGRESS, m_bProgress);
	DDX_Check(pDX, IDC_CHK_RTL, m_bRtl);
	DDX_Check(pDX, IDC_CHK_VERIFY, m_bVerify);
	DDX_Check(pDX, IDC_CHK_WIDTH, m_bWidth);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT_FOOTER, m_strFooter);
	DDX_Text(pDX, IDC_EDIT_MAIN, m_strMainInstruction);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strWindowTitle);
	DDX_Text(pDX, IDC_EDIT_VERIFY, m_strVerificationText);
	DDX_Text(pDX, IDC_TXT_COUNTBYFIVE, m_nCount);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskPageGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CTaskPageGeneral)
	ON_EN_CHANGE(IDC_EDIT_TITLE, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_MAIN, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_CONTENT, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_FOOTER, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_VERIFY, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_VERIFY, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_WIDTH, OnUpdateData)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_HYPERLINKS, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_ALLOWCANCEL, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_POSITION, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_PROGRESS, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_MARQUEE, OnUpdateData)
	ON_BN_CLICKED(IDC_CHK_RTL, OnUpdateData)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ADDFIVE, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SUBFIVE, OnBnClickedBtnSub)
END_MESSAGE_MAP()

void CTaskPageGeneral::OnUpdateData()
{
	UpdateData();

	GetDlgItem(IDC_CHK_VERIFY)->EnableWindow(!m_strVerificationText.IsEmpty());
	GetDlgItem(IDC_EDIT_WIDTH)->EnableWindow(m_bWidth);

	GetDlgItem(IDC_CHK_MARQUEE)->EnableWindow(m_bProgress);

}

BOOL CTaskPageGeneral::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, GetParent());
	ASSERT_VALID(m_pDlgParent);

	GetDlgItem(IDC_CHK_VERIFY)->EnableWindow(!m_strVerificationText.IsEmpty());
	GetDlgItem(IDC_BTN_ADDFIVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_SUBFIVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TXT_COUNTBYFIVE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT_WIDTH)->EnableWindow(m_bWidth);
	GetDlgItem(IDC_CHK_MARQUEE)->EnableWindow(m_bProgress);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTaskPageGeneral::OnSetActive()
{
	if (!CPropertyPage::OnSetActive())
		return FALSE;

	return TRUE;
}

void CTaskPageGeneral::OnBnClickedBtnAdd()
{
	m_nCount += 25;

	m_strMainInstruction.Empty();
	for (int i = 0; i < m_nCount; i += 5)
	{
		m_strMainInstruction += SAMPLE_TEXT; 
	}

	UpdateData(FALSE);
}

void CTaskPageGeneral::OnBnClickedBtnSub()
{
	m_nCount -= 25;

	m_strMainInstruction.Empty();
	for (int i = 0; i < m_nCount; i += 5)
	{
		m_strMainInstruction += SAMPLE_TEXT; 
	}

	UpdateData(FALSE);
}
