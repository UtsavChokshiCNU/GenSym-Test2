// g2mfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "g2mfc.h"
#include "g2mfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG2mfcDlg dialog

CG2mfcDlg::CG2mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CG2mfcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CG2mfcDlg)
	m_ConStr = _T("");
	m_State = _T("");
	m_Msg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CG2mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CG2mfcDlg)
	DDX_Control(pDX, IDC_BUTTON2, m_Con);
	DDX_Text(pDX, IDC_EDIT1, m_ConStr);
	DDX_Text(pDX, IDC_EDIT2, m_State);
	DDX_Text(pDX, IDC_EDIT3, m_Msg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CG2mfcDlg, CDialog)
	//{{AFX_MSG_MAP(CG2mfcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CG2mfcDlg message handlers

BOOL CG2mfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	
	// TODO: Add extra initialization here
	m_G2Gateway4.Create("",WS_CHILD,CRect(0,0,0,0),this,IDC_G2GATEWAY1);
	m_ConStr = "localhost:1111";
	m_Msg = "Hello G2";
	UpdateData(false);
	b_State = false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CG2mfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CG2mfcDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CG2mfcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CG2mfcDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
   UpdateData(true);
   if(b_State){
	   		COleVariant msg(m_Msg);
	   
		m_G2Gateway4.PostMessage(&msg);
   }else{
	   ::MessageBox(this->GetSafeHwnd(),"You should first connected to G2 Server","Error",0);
   }
}

BEGIN_EVENTSINK_MAP(CG2mfcDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CG2mfcDlg)
	ON_EVENT(CG2mfcDlg, IDC_G2GATEWAY1, 6 /* RpcStarted */, OnRpcStartedG2gateway1, VTS_BSTR VTS_PVARIANT)
	ON_EVENT(CG2mfcDlg, IDC_G2GATEWAY1, 3 /* G2Connected */, OnG2ConnectedG2gateway1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CG2mfcDlg::OnRpcStartedG2gateway1(LPCTSTR ProcedureName, VARIANT FAR* InputArguments) 
{
	// TODO: Add your control notification handler code here
	CString strProc = ProcedureName;
	CString strProcE = "CYCLELIGHTS";
	if(0 == strProc.Compare(strProcE )){
		m_State = InputArguments->bstrVal;
	}
	UpdateData(false);
}

void CG2mfcDlg::OnG2ConnectedG2gateway1() 
{
	// TODO: Add your control notification handler code here
	
}

void CG2mfcDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
    UpdateData(true);
	if(!b_State){
		m_G2Gateway4.SetG2Location(m_ConStr );
		m_G2Gateway4.Connect(true);
		m_Con.SetWindowText("Disconect");
		b_State = true;
	}else{
		b_State = false;
		m_G2Gateway4.Disconnect();
		m_Con.SetWindowText("Connect");
	}
    UpdateData(false);	
}
