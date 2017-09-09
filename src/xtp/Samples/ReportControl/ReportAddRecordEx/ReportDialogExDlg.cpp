// ReportDialogExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportDialogEx.h"
#include "ReportDialogExDlg.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT AFX_CDECL AddRecordsThreadFunc(LPVOID pvParms);

/////////////////////////////////////////////////////////////////////////////
// CReportDialogExDlg dialog

CReportDialogExDlg::CReportDialogExDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CReportDialogExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportDialogExDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReportDialogExDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDialogExDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportDialogExDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CReportDialogExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADD_RECORDS_BUTTON, OnAddRecordsButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDialogExDlg message handlers

BOOL CReportDialogExDlg::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// subclass the report control
	m_wndReportCtrl.SubclassDlgItem(IDC_REPORTCTRL, this);

	//  add sample columns
	for(int i = 0; i < 4; i++)
	{
		CString strName;
		strName.Format(_T("Column %d"), i + 1);
		m_wndReportCtrl.AddColumn(new CXTPReportColumn(i, strName, 280));
	}

	// set the first column as a group column
	m_wndReportCtrl.ShowGroupBy();
	m_wndReportCtrl.GetColumns()->GetGroupsOrder()->Add(m_wndReportCtrl.GetColumns()->GetAt(0));

	// add empty header row
	m_wndReportCtrl.GetHeaderRecords()->Add(new CMessageRecord());
	m_wndReportCtrl.ShowHeaderRows();
	m_wndReportCtrl.HeaderRowsAllowEdit(TRUE);
	m_wndReportCtrl.PopulateHeaderRows();
	m_wndReportCtrl.GetPaintManager()->SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerOutlook);

	// define style attributes for the report control
	m_wndReportCtrl.FocusSubItems(TRUE);
	m_wndReportCtrl.AllowEdit(TRUE);


	// Set control resizing.
	SetResize(IDC_REPORTCTRL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_ADD_RECORDS_BUTTON, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);

	// Load window placement
	LoadPlacement(_T("CReportDialogExDlg"));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReportDialogExDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTPResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReportDialogExDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTPResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReportDialogExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReportDialogExDlg::OnDestroy() 
{
	CXTPResizeDialog::OnDestroy();


	// Save window placement
	SavePlacement(_T("CReportDialogExDlg"));

}

void CReportDialogExDlg::OnAddRecordsButton() 
{
	GetDlgItem(IDC_ADD_RECORDS_BUTTON)->EnableWindow(FALSE);
	
	AfxBeginThread(AddRecordsThreadFunc, (LPVOID)&m_wndReportCtrl, THREAD_PRIORITY_IDLE);
	
	//GetDlgItem(IDC_ADD_RECORDS_BUTTON)->EnableWindow();		
}

BOOL CReportDialogExDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB))
		return FALSE;

	return CXTPResizeDialog::PreTranslateMessage(pMsg);
}


UINT AFX_CDECL AddRecordsThreadFunc(LPVOID pvParms)
{
	CReportControl* pReportCtrl = (CReportControl*)pvParms;
	if(!pReportCtrl)
		return 0;

	int nAddCount = 100;
	for(int i = 0; i < nAddCount; i++)
	{
		CString strItem[4];
		for(int j = 0; j < 4; j++)
		{
			strItem[j].Format(_T("Row - %d, Col - %d"), i + 1, j + 1);
		}
		CMessageRecord* pMsg = new CMessageRecord(strItem[0], strItem[1], strItem[2], strItem[3]);
		// WPARAM = pointer to a report record
		// LPARAM:
		//    LOWORD = record number
		//    HIWORD = records count to add
		if(pMsg)
			pReportCtrl->SendMessage(WM_ADD_RECORD_EX, (WPARAM)pMsg, MAKELPARAM(i, nAddCount));

		if (pReportCtrl->GetParent())
		{
			CString strCaption(_T("Report Sample for AddRecordEx"));
			
			if (i + 1 < nAddCount)
				strCaption.Format(_T("Report Sample for AddRecordEx [%d of %d]"), i+1, nAddCount);

			pReportCtrl->GetParent()->SetWindowText(strCaption);
		}

		Sleep(50);
	}
	pReportCtrl->GetParent()->GetDlgItem(IDC_ADD_RECORDS_BUTTON)->EnableWindow();

	return 0;
}
