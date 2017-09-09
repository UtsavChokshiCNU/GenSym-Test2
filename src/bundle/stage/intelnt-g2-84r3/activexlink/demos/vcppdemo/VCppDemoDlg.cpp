// VCppDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "G2Com.h"
#include "G2Com_i.c"
#include "VCppDemo.h"
#include "VCppDemoDlg.h"

#ifdef _DEBUG
// #define new DEBUG_NEW
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

BEGIN_EVENTSINK_MAP(CVCppDemoDlg, CDialog)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY, 1, OnG2Paused,       VTS_NONE)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY, 2, OnG2Resumed,      VTS_NONE)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY, 3, OnG2Connected,    VTS_NONE)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY, 4, OnG2Disconnected, VTS_NONE)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY, 5, OnRpcCalled,      VTS_BSTR VTS_PVARIANT VTS_PVARIANT)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY, 6, OnRpcStart,       VTS_BSTR VTS_PVARIANT)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY,10, OnG2Reset,        VTS_NONE)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY,11, OnG2Started,      VTS_NONE)
  ON_EVENT(CVCppDemoDlg, ID_G2GATEWAY,12, OnG2StateKnown,   VTS_NONE)
END_EVENTSINK_MAP()

void CVCppDemoDlg::OnG2Paused()
{
	m_g2RunState = g2Paused ;
    RedrawWindow() ;
}

void CVCppDemoDlg::OnG2Resumed()
{
	m_g2RunState = g2Running ;
    RedrawWindow() ;
}

void CVCppDemoDlg::OnG2Reset()
{
	m_g2RunState = g2Reset ;
    RedrawWindow() ;
}

void CVCppDemoDlg::OnG2Started()
{
	m_g2RunState = g2Running ;
    RedrawWindow() ;
}

void CVCppDemoDlg::OnG2StateKnown()
{
    HRESULT hr = m_pIG2Gateway->get_G2RunState(&m_g2RunState);
    RedrawWindow() ;
}

void CVCppDemoDlg::OnG2Connected()
{
//  CRect   indy(3,3,13,13) ;

	m_g2Connected = true ;
    RedrawWindow() ;
}

void CVCppDemoDlg::OnG2Disconnected()
{
//  CRect   indy(3,3,13,13) ;

	m_g2Connected = false ;
    RedrawWindow() ;
}
/////////////////////////////////////////////////////////////////////////////
// CVCppDemoDlg dialog

CVCppDemoDlg::CVCppDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCppDemoDlg::IDD, pParent), m_g2Connected(false), 
      m_g2RunState(g2UnknownState)
{
	//{{AFX_DATA_INIT(CVCppDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVCppDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCppDemoDlg)
	DDX_Control(pDX, IDC_CYCLE_BUTTON, c_BtnCycle);
	DDX_Control(pDX, IDC_BUTTON_CALLG2, c_BtnCallG2);
	DDX_Control(pDX, IDC_MSG, c_EditMsg);
	DDX_Control(pDX, IDC_G2LOCATION, c_EditG2Location);
	DDX_Control(pDX, IDC_CALL_ITEM, c_EditSeed);
	DDX_Control(pDX, IDC_CALL_ITEM_RES, c_EditResult);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCppDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CVCppDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnPostMessageButton)
	ON_BN_CLICKED(IDC_BUTTON_CALLG2, OnButtonCallg2)
	ON_BN_CLICKED(IDC_CYCLE_BUTTON, OnCycleButton)
	ON_BN_CLICKED(IDBTN_DISCON, OnBtnDiscon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCppDemoDlg message handlers

BOOL CVCppDemoDlg::OnInitDialog()
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
	BOOL m_bG2CreateSucceeded = FALSE;

	RECT lrc;
	lrc.bottom = 214;
	lrc.left = 49;
	lrc.right = 455;
	lrc.top = 61;

	// Create the ActiveX control
	m_G2Gateway1.CreateControl(CLSID_G2Gateway,NULL,WS_TABSTOP|WS_VISIBLE,lrc,this,ID_G2GATEWAY);

	// Get the IUnknow Interface of ActiveX control
	LPUNKNOWN	m_pIUnknown;
	m_pIUnknown = m_G2Gateway1.GetControlUnknown( );

	// Query the needed interface
	m_pIUnknown ->QueryInterface( IID_IG2Gateway3, (void **)&m_pIG2Gateway);

	BSTR bstrG2;

	bstrG2=SysAllocString(L"localhost:1111");
	m_pIG2Gateway->put_G2Location(bstrG2);
	SysFreeString(bstrG2);

	bstrG2=SysAllocString(L"VBDEMO-INTERFACE");
	m_pIG2Gateway->put_InterfaceClass(bstrG2);
	SysFreeString(bstrG2);

	m_csNextMode = "slow";
	m_csMode = "STOP";
	c_EditMsg.SetWindowText("VC++ says hello to G2!");
	c_EditSeed.SetWindowText("101");
	c_EditG2Location.SetWindowText("localhost:1111");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVCppDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVCppDemoDlg::OnPaint() 
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

		CPaintDC dc(this); // device context for painting

		// Circle size and position
		int left = 120;
		int top = 135;
		int size = 30;
		int buf = 2;
		CRect rect(left,top,left+size,top+size);	// l,t,r,b
   
        CBrush  brBlack ;
        CBrush  brRed ;
        CBrush  brYellow ;
        CBrush  brGreen ;
        CBrush  brBlue ;
        CBrush  brushErase ;

        brBlack.CreateSolidBrush(RGB(0,0,0)) ;
        brRed.CreateSolidBrush(RGB(255,0,0)) ;
        brYellow.CreateSolidBrush(RGB(255,255,0)) ;
        brGreen.CreateSolidBrush(RGB(64,255,0)) ;
        brBlue.CreateSolidBrush(RGB(64,0,255)) ;
        brushErase.CreateSysColorBrush(COLOR_BTNFACE) ;

//		CDialog::OnPaint();

		// Black pen
		CPen	pen(PS_SOLID, 0, RGB(0,0,0));
		CPen* pOldPen = dc.SelectObject(&pen);

        // Draw the traffic signal

		// Red light
        // ---------
        CBrush* pOldBrush = (m_csMode=="STOP") ? dc.SelectObject(&brRed) :
                                                 dc.SelectObject(&brBlack) ;        
		dc.Ellipse(&rect);

		// Yellow light
        // ------------
		rect.top += size+buf;
		rect.bottom = rect.top+size;
        if (m_csMode=="SLOW")
            dc.SelectObject(&brYellow) ;
        else
            dc.SelectObject(&brBlack) ;        
		dc.Ellipse(&rect);

		// Green light
        // -----------
		rect.top += size+buf;
		rect.bottom = rect.top+size;
        if (m_csMode=="PROCEED")
            dc.SelectObject(&brGreen) ;
        else
            dc.SelectObject(&brBlack) ;        
		dc.Ellipse(&rect);

        // Display indicator showing whether or not we are connected to G2
        // ---------------------------------------------------------------
        CBrush  brushCon ;

        rect.top = 3 ;
        rect.bottom = 13 ;
        rect.left = 3 ;
        rect.right = 13 ;
        if (m_g2Connected)
            brushCon.CreateSolidBrush(RGB(64,255,0)) ;
        else
            brushCon.CreateSolidBrush(RGB(255,0,0)) ;
        dc.SelectObject(&brushCon) ;
        dc.Ellipse(&rect) ;

        // Display the run state indicators
        // --------------------------------
        CRect   rectInd(180,30,192,42) ;

        dc.SelectObject((m_g2Connected && m_g2RunState == g2Running) ?
                            &brGreen : &brushErase) ;
        dc.Rectangle(rectInd.left, rectInd.top, rectInd.right, rectInd.bottom) ;
            
        rectInd.top += 24 ;
        rectInd.bottom += 24 ;
        dc.SelectObject((m_g2Connected && m_g2RunState == g2Paused) ?
                            &brYellow : &brushErase) ;
        dc.Rectangle(rectInd.left, rectInd.top, rectInd.right, rectInd.bottom) ;

        rectInd.top += 24 ;
        rectInd.bottom += 24 ;
        dc.SelectObject((m_g2Connected && m_g2RunState == g2Reset) ?
                            &brRed : &brushErase) ;
        dc.Rectangle(rectInd.left, rectInd.top, rectInd.right, rectInd.bottom) ;

        rectInd.top += 24 ;
        rectInd.bottom += 24 ;
        dc.SelectObject((!m_g2Connected || m_g2RunState == g2UnknownState) ?
                            &brBlue : &brushErase) ;
        dc.Rectangle(rectInd.left, rectInd.top, rectInd.right, rectInd.bottom) ;




		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCppDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVCppDemoDlg::OnRpcCalled(LPCTSTR Name, VARIANT FAR* InArgs, VARIANT FAR* OutArgs)
{
	TRACE("OnRpcCalled\n");
}

void CVCppDemoDlg::OnRpcStart(LPCTSTR Name, VARIANT FAR* InArgs)
{
	CString csTest("CYCLELIGHTS");
	if (Name == csTest)
	{
		m_csMode = InArgs->bstrVal;
		TRACE("OnRpcStart %s\n", m_csMode);
		InvalidateRect( NULL, TRUE );
	}

}

void CVCppDemoDlg::OnPostMessageButton() 
{
	// Point ActiveXLink to G2
    // -----------------------
	CString     csG2Location;
	c_EditG2Location.GetWindowText(csG2Location);
	BSTR bstrG2=csG2Location.AllocSysString();
	m_pIG2Gateway->put_G2Location(bstrG2);
	SysFreeString(bstrG2);

	// Package the message in a Variant
    // --------------------------------
	CString     csMsg;
	VARIANT     varMessage;

	c_EditMsg.GetWindowText(csMsg);
	VariantInit(&varMessage);
	varMessage.vt = VT_BSTR;
	varMessage.bstrVal = csMsg.AllocSysString();

	// Send the message to G2.
    // We will be automatically connected to G2, if needed.
    // ----------------------------------------------------
	HRESULT hr = m_pIG2Gateway->PostMessage(&varMessage);

    if (FAILED(hr))
		TRACE("PostMessage() failed returned 0x%08.8lX\n", hr);
	else
		TRACE("PostMessage succeeded\n");

	VariantClear(&varMessage);

	// Enable Call G2  and Cycle Lights Buttons
	c_BtnCallG2.EnableWindow(TRUE);
	c_BtnCycle.EnableWindow(TRUE);
}

void CVCppDemoDlg::OnButtonCallg2() 
{
	// Point ActiveXLink to G2
    // -----------------------
	CString     csG2Location;
	c_EditG2Location.GetWindowText(csG2Location);
	BSTR bstrG2=csG2Location.AllocSysString();
	m_pIG2Gateway->put_G2Location(bstrG2);
	SysFreeString(bstrG2);

    // Create a new 1-D array of VARIANTS for input arguments of Call()
	// Equivalent to Visual Basic statement: Dim a(1 To 1) As Variant
    // ----------------------------------------------------------------
	SAFEARRAY       *psa; 
	SAFEARRAYBOUND  aDim[1];	// Just 1 dimension

	aDim[0].lLbound = 1;		// Lower bound of 1
	aDim[0].cElements = 1;		// 1 element
	psa = SafeArrayCreate(VT_VARIANT, 1, aDim);
	if (psa == NULL) throw ERROR_NOT_ENOUGH_MEMORY;


    // Get seed number from user and pack into the SafeArray
    // -----------------------------------------------------
	CString csInput;
    VARIANT varSeed ;
    long    ix[1];

	c_EditSeed.GetWindowText(csInput);	// Get seed number from user
	VariantInit(&varSeed);
	varSeed.vt = VT_R4;
	varSeed.fltVal = (float)atof(csInput);
	ix[0] = 1;
	SafeArrayPutElement(psa, ix, &varSeed);

    // Call RandomGenerator, passing it the seed via the SafeArray
    // -----------------------------------------------------------
	VARIANT     varRet;		// Random number returned from G2

	bstrG2=SysAllocString(L"G2RANDOMGENERATOR");
	HRESULT hr = m_pIG2Gateway->Call(bstrG2, &psa, &varRet);
	if (FAILED(hr))
		TRACE("Call('G2RANDOMGENERATOR') failed returned 0x%08.8lX\n", hr);
	else
		TRACE("Call('G2RANDOMGENERATOR') succeeded\n");

    // Display the returned value
    // --------------------------
	CString     csRet("  ");
	if (varRet.vt == VT_R4)
	{
		csRet.Format("%8.3f",varRet.fltVal);
		csRet.TrimLeft();
	}
	else if (varRet.vt == VT_R8)
	{
		csRet.Format("%8.3f",varRet.dblVal);
		csRet.TrimLeft();
	}
	c_EditResult.SetWindowText(csRet);

    // Free up the memory that we have used
    // ------------------------------------
	SysFreeString(bstrG2);
	VariantClear(&varSeed);
	VariantClear(&varRet);
	SafeArrayDestroy(psa);
}

void CVCppDemoDlg::OnCycleButton() 
{
	// Point ActiveXLink to G2
    // -----------------------
	CString     csG2Location;
	c_EditG2Location.GetWindowText(csG2Location);
	BSTR bstrG2=csG2Location.AllocSysString();
	m_pIG2Gateway->put_G2Location(bstrG2);
	SysFreeString(bstrG2);

    // Create a new 1-D array of VARIANTS for input arguments of Call()
	SAFEARRAY* psa; 
	SAFEARRAYBOUND aDim[1];		// Just 1 dimension
	aDim[0].lLbound = 1;		// Lower bound of 1
	aDim[0].cElements = 1;		// 1 element

	// Equivalent to Visual Basic statement: Dim a(1 To 1) As Variant
	psa = SafeArrayCreate(VT_VARIANT, 1, aDim);
	if (psa == NULL) throw ERROR_NOT_ENOUGH_MEMORY;

	VARIANT varMode;	// Seed for random number generator
	VariantInit(&varMode);
	varMode.vt = VT_BSTR;
	varMode.bstrVal = m_csNextMode.AllocSysString();
    long ix[1];
	ix[0] = 1;
	SafeArrayPutElement(psa, ix, &varMode);

	bstrG2=SysAllocString(L"CHANGE-SIGNAL");
	HRESULT hres = m_pIG2Gateway->Start(bstrG2, &psa);
	if (FAILED(hres))
		TRACE("Call('CHANGE-SIGNAL') failed returned 0x%08.8lX\n", hres);
	else
		TRACE("Call('CHANGE-SIGNAL') succeeded\n");

	SysFreeString(bstrG2);
	VariantClear(&varMode);

	SafeArrayDestroy(psa);
	if (m_csNextMode == "stop")
		m_csNextMode = "slow";
	else if (m_csNextMode == "slow")
		m_csNextMode = "proceed";
	else
		m_csNextMode = "stop";
}

void CVCppDemoDlg::OnBtnDiscon() 
{
    m_pIG2Gateway->Disconnect() ;	
}
