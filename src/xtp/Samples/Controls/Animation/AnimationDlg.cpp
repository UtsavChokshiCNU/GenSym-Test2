// AnimationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Animation.h"
#include "AnimationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlg dialog

CAnimationDlg::CAnimationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimationDlg)
	m_nAnimationDelay = m_staticGear.GetAnimationDelay();
	m_nAnimationType = m_staticGear.GetAnimationType();
	m_nAnimationSteps = m_staticGear.GetAnimationSteps();
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimationDlg)
	DDX_Control(pDX, IDC_EDIT_STEPS, m_editSteps);
	DDX_Control(pDX, IDC_EDIT_DELAY, m_editDelay);
	DDX_Control(pDX, IDC_BMP_GEAR, m_staticGear);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_nAnimationDelay);
	DDV_MinMaxInt(pDX, m_nAnimationDelay, 1, 1000);
	DDX_Radio(pDX, IDC_RADIO_ANIMATION, m_nAnimationType);
	DDX_Text(pDX, IDC_EDIT_STEPS, m_nAnimationSteps);
	DDV_MinMaxInt(pDX, m_nAnimationSteps, 1, 100);
	DDX_Control(pDX, IDC_STATIC_DELAY, m_staticDelay);
	DDX_Control(pDX, IDC_STATIC_STEPS, m_staticSteps);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnimationDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ANIMATE, OnAnimate)
	ON_EN_CHANGE(IDC_EDIT_DELAY, OnChangeEditDelay)
	ON_EN_CHANGE(IDC_EDIT_STEPS, OnChangeEditSteps)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_ANIMATION, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO7, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO8, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO9, OnBnClickedRadio)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlg message handlers

BOOL CAnimationDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAnimationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAnimationDlg::OnPaint() 
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
HCURSOR CAnimationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAnimationDlg::OnAnimate() 
{
	UpdateData();

	// set animation properties
	m_staticGear.SetAnimationDelay(m_nAnimationDelay);
	m_staticGear.SetAnimationType(m_nAnimationType);
	m_staticGear.SetAnimationSteps(m_nAnimationSteps);

	// draw animation
	m_staticGear.Animate();
}

void CAnimationDlg::OnChangeEditDelay() 
{
	UpdateData();

	if (m_nAnimationDelay < 1 || m_nAnimationDelay > 1000)
	{
		m_nAnimationDelay = m_staticGear.GetAnimationDelay();
		UpdateData(FALSE);
		m_editDelay.SetSel(0,-1);
	}
}

void CAnimationDlg::OnChangeEditSteps() 
{
	UpdateData();

	if (m_nAnimationSteps < 1 || m_nAnimationSteps > 100)
	{
		m_nAnimationSteps = m_staticGear.GetAnimationSteps();
		UpdateData(FALSE);
		m_editSteps.SetSel(0,-1);
	}
}

void CAnimationDlg::OnBnClickedRadio()
{
	UpdateData();

	m_editDelay.EnableWindow(m_nAnimationType <= 5);
	m_staticDelay.EnableWindow(m_nAnimationType <= 5);
	m_editSteps.EnableWindow(m_nAnimationType <= 5);
	m_staticSteps.EnableWindow(m_nAnimationType <= 5);
}
