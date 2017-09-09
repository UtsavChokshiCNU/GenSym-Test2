// ReportItemControlsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportItemControls.h"
#include "ReportItemControlsDlg.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_COLUMN 3
#define MAX_ROW 20

/////////////////////////////////////////////////////////////////////////////
// CReportItemControlsDlg dialog

CReportItemControlsDlg::CReportItemControlsDlg(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CReportItemControlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportItemControlsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReportItemControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportItemControlsDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportItemControlsDlg, CXTPResizeDialog)
	//{{AFX_MSG_MAP(CReportItemControlsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY(XTP_NM_REPORT_ITEMBUTTONCLICK, IDC_REPORTCTRL, OnItemButtonClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportItemControlsDlg message handlers

BOOL CReportItemControlsDlg::OnInitDialog()
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

	// subclass the report control.
	m_wndReportCtrl.SubclassDlgItem(IDC_REPORTCTRL, this);

	CBitmap bitmap;
	VERIFY(bitmap.LoadBitmap(IDB_BMREPORT));

	// create the image list used by the report control.
	if (!m_ilIcons.Create(16, 15, ILC_COLOR24 | ILC_MASK, 0, 1))
		return -1;

	// load the image bitmap and set the image list for the 
	// report control.
	m_ilIcons.Add(&bitmap, RGB(255, 0, 255));
	m_wndReportCtrl.SetImageList(&m_ilIcons);

	int i, j;

	//  add sample columns
	for (i = 0; i < MAX_COLUMN; i++)
	{
		CString strName;
		strName.Format(_T("Column %d"), i + 1);
		m_wndReportCtrl.AddColumn(new CXTPReportColumn(i, strName, 280));
	}

	// add records
	for (i = 0; i < MAX_ROW; i++)
	{
		CString strItem[MAX_COLUMN];
		for (j = 0; j < MAX_COLUMN; j++)
		{
			strItem[j].Format(_T("Row - %d, Col - %d"), i + 1, j + 1);
		}
		CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord(new CMessageRecord(strItem[0], strItem[1], strItem[2]));
		if(!pRecord)
			continue;
		for (j = 0; j < MAX_COLUMN; j++)
		{
			CXTPReportRecordItem* pItem = pRecord->GetItem(j);
			if(!pItem)
				continue;
			CXTPReportRecordItemControl* pButton = pItem->GetItemControls()->AddControl(xtpItemControlTypeButton);
			if(!pButton)
				continue;
			pButton->SetAlignment(xtpItemControlLeft);
			pButton->SetIconIndex(PBS_NORMAL, 0);
			pButton->SetIconIndex(PBS_PRESSED, 1);
			pButton->SetSize(CSize(22, 0));
			pButton = pItem->GetItemControls()->AddControl(xtpItemControlTypeButton);
			if(!pButton)
				continue;
			pButton->SetAlignment(xtpItemControlRight);
			pButton->SetIconIndex(PBS_NORMAL, 4);
			pButton->SetIconIndex(PBS_PRESSED, 5);
			pButton->SetSize(CSize(22, 0));
			pButton = pItem->GetItemControls()->AddControl(xtpItemControlTypeButton);
			if(!pButton)
				continue;
			pButton->SetAlignment(xtpItemControlRight);
			pButton->SetIconIndex(0, 3);
			pButton->SetSize(CSize(22, 0));
		}
	}

	// define style attributes for the report control.
	m_wndReportCtrl.FocusSubItems(TRUE);
	m_wndReportCtrl.AllowEdit(TRUE);

	// after columns and data have been added call Populate to 
	// populate all of the date for the control.
	m_wndReportCtrl.Populate();


	// Set control resizing.
	SetResize(IDC_REPORTCTRL, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);

	// Load window placement
	LoadPlacement(_T("CReportItemControlsDlg"));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReportItemControlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReportItemControlsDlg::OnPaint() 
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
HCURSOR CReportItemControlsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReportItemControlsDlg::OnDestroy() 
{
	CXTPResizeDialog::OnDestroy();


	// Save window placement
	SavePlacement(_T("CReportItemControlsDlg"));

}

BOOL CReportItemControlsDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB))
		return FALSE;

	return CXTPResizeDialog::PreTranslateMessage(pMsg);
}

void CReportItemControlsDlg::OnItemButtonClick(NMHDR * pNotifyStruct, LRESULT*)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	if(!(pItemNotify->pRow && pItemNotify->pItem && pItemNotify->pItemControl))
		return;

	switch(pItemNotify->pItemControl->GetIndex())
	{
	    // button "Alignment"
		case 0 :
		{
			int nIcon = pItemNotify->pItemControl->GetIconIndex(PBS_NORMAL);
			if(++nIcon > 2)
				nIcon = 0;
			pItemNotify->pItemControl->SetIconIndex(PBS_NORMAL, nIcon);
			if(++nIcon > 2)
				nIcon = 0;
			pItemNotify->pItemControl->SetIconIndex(PBS_PRESSED, nIcon);
			switch(pItemNotify->pItemControl->GetIconIndex(PBS_NORMAL))
			{
				case 0 :
					pItemNotify->pItem->SetAlignment(xtpColumnTextLeft);
					break;
				case 1 :
					pItemNotify->pItem->SetAlignment(xtpColumnTextCenter);
					break;
				case 2 :
					pItemNotify->pItem->SetAlignment(xtpColumnTextRight);
					break;
			}
			break;
		}
	    // button "Color"
		case 1 :
		{
			int nIcon = pItemNotify->pItemControl->GetIconIndex(PBS_NORMAL);
			if(++nIcon > 6)
				nIcon = 4;
			pItemNotify->pItemControl->SetIconIndex(PBS_NORMAL, nIcon);
			if(++nIcon > 6)
				nIcon = 4;
			pItemNotify->pItemControl->SetIconIndex(PBS_PRESSED, nIcon);
			switch(pItemNotify->pItemControl->GetIconIndex(PBS_NORMAL))
			{
				case 4 :
					pItemNotify->pItem->SetTextColor(RGB(0, 0, 0));
					break;
				case 5 :
					pItemNotify->pItem->SetTextColor(RGB(0, 0, 255));
					break;
				case 6 :
					pItemNotify->pItem->SetTextColor(RGB(255, 0, 0));
					break;
			}
			break;
		}
	    // button "Bold"
		case 2 :
		{
			pItemNotify->pItem->SetBold(!pItemNotify->pItem->IsBold());
			break;
		}
	}
}
