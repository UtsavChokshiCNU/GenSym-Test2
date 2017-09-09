// CppUnitTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestDlg.h"
#include <atlbase.h>
#import "../../Release/G2Com.dll" no_namespace named_guids

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestDlg dialog

CCppUnitTestDlg::CCppUnitTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCppUnitTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCppUnitTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCppUnitTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCppUnitTestDlg)
	DDX_Control(pDX, IDC_G2GATEWAY1, m_g2g);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCppUnitTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCppUnitTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestDlg message handlers

BOOL CCppUnitTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCppUnitTestDlg::OnPaint() 
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
HCURSOR CCppUnitTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CCppUnitTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CCppUnitTestDlg)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 3 /* G2Connected */, OnG2ConnectedG2gateway1, VTS_NONE)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 4 /* G2Disconnected */, OnG2DisconnectedG2gateway1, VTS_NONE)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 12 /* G2RunStateKnown */, OnG2RunStateKnownG2gateway1, VTS_NONE)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 5 /* RpcCalled */, OnRpcCalledG2gateway1, VTS_BSTR VTS_PVARIANT VTS_PVARIANT)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 7 /* RpcReturned */, OnRpcReturnedG2gateway1, VTS_BSTR VTS_PVARIANT VTS_PVARIANT)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 1 /* G2Paused */, OnG2PausedG2gateway1, VTS_NONE)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 10 /* G2Reset */, OnG2ResetG2gateway1, VTS_NONE)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 2 /* G2Resumed */, OnG2ResumedG2gateway1, VTS_NONE)
	ON_EVENT(CCppUnitTestDlg, IDC_G2GATEWAY1, 11 /* G2Started */, OnG2StartedG2gateway1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCppUnitTestDlg::OnG2ConnectedG2gateway1() 
{
	// TODO: Add your control notification handler code here
	m_bConnectedEventFired=TRUE;
}

void CCppUnitTestDlg::OnG2RunStateKnownG2gateway1() 
{
	// TODO: Add your control notification handler code here
	m_bRunStateKnownEventFired=TRUE;
	
}

void CCppUnitTestDlg::OnG2DisconnectedG2gateway1() 
{
	// TODO: Add your control notification handler code here
	m_bDisconnectedEventFired=TRUE;
	
}


void CCppUnitTestDlg::OnRpcCalledG2gateway1(LPCTSTR ProcedureName, VARIANT FAR* InputArguments, VARIANT FAR* ReturnArguments) 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("OnRpcCalledG2gateway1");
}

void CCppUnitTestDlg::OnRpcReturnedG2gateway1(LPCTSTR ProcedureName, VARIANT FAR* ReturnArguments, VARIANT FAR* DeferredCallIdentifier) 
{
	// TODO: Add your control notification handler code here
	m_bRpcReturnedEventFired=TRUE;
}

void CCppUnitTestDlg::OnG2PausedG2gateway1() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("OnG2PausedG2gateway1");
}

void CCppUnitTestDlg::OnG2ResetG2gateway1() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("OnG2ResetG2gateway1");
}

void CCppUnitTestDlg::OnG2ResumedG2gateway1() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("OnG2ResumedG2gateway1");
}

void CCppUnitTestDlg::OnG2StartedG2gateway1() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("OnG2StartedG2gateway1");
	
}

BOOL CCppUnitTestDlg::Connect()
{
	try
	{
		m_bConnectedEventFired=FALSE;
		m_bRunStateKnownEventFired=FALSE;
		m_g2g.SetG2Location("localhost:1111");
		if(S_OK!=m_g2g.Connect(TRUE))
			return FALSE;
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CCppUnitTestDlg::Disconnect()
{
	try
	{
		m_bDisconnectedEventFired=FALSE;
		m_g2g.Disconnect();
		m_g2g.OnEndPage();
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CCppUnitTestDlg::PostMessage()
{

	try
	{
		COleVariant msg("Hello G2 Server!");
		m_g2g.PostMessage(&msg);
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CCppUnitTestDlg::Call()
{
	try
	{
		CComPtr<IUnknown> pUnk= m_g2g.GetControlUnknown();
		if(!pUnk)
			return FALSE;
		CComQIPtr<IG2Gateway> pG2G;
		if(S_OK!=pUnk.QueryInterface(&pG2G))
			return FALSE;
		//
		SAFEARRAY *arr = ::SafeArrayCreateVector(VT_VARIANT, 0, 3);
		VARIANT HUGEP *pbstr; //Pointer to safearray elements	
		HRESULT hr = SafeArrayAccessData(arr, (void HUGEP**)&pbstr);
		_bstr_t txt("Wellcome!");
		_variant_t varText(txt);
		pbstr[0] = pbstr[1]=pbstr[2]=varText;
		SafeArrayUnaccessData(arr);
		//
		_variant_t result = pG2G->Call(_bstr_t("CAB_TEST_PROC"), &arr);
		::SafeArrayDestroy(arr);
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CCppUnitTestDlg::CallDeferred()
{
	try
	{
		m_bRpcReturnedEventFired=FALSE;
		CComPtr<IUnknown> pUnk= m_g2g.GetControlUnknown();
		if(!pUnk)
			return FALSE;
		CComQIPtr<IG2Gateway> pG2G;
		if(S_OK!=pUnk.QueryInterface(&pG2G))
			return FALSE;
		//
		SAFEARRAY *arr = ::SafeArrayCreateVector(VT_VARIANT, 0, 3);
		VARIANT HUGEP *pbstr; //Pointer to safearray elements	
		HRESULT hr = SafeArrayAccessData(arr, (void HUGEP**)&pbstr);
		_bstr_t txt("Wellcome!");
		_variant_t varText(txt);
		pbstr[0] = pbstr[1]=pbstr[2]=varText;
		SafeArrayUnaccessData(arr);
		COleVariant id1((long)1);
		//
		_variant_t result = pG2G->CallDeferred(_bstr_t("CAB_TEST_PROC"),&id1, &arr);
		::SafeArrayDestroy(arr);
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CCppUnitTestDlg::Start()
{
	try
	{
		m_bRpcReturnedEventFired=FALSE;
		CComPtr<IUnknown> pUnk= m_g2g.GetControlUnknown();
		if(!pUnk)
			return FALSE;
		CComQIPtr<IG2Gateway> pG2G;
		if(S_OK!=pUnk.QueryInterface(&pG2G))
			return FALSE;
		//
		SAFEARRAY *arr = ::SafeArrayCreateVector(VT_VARIANT, 0, 3);
		VARIANT HUGEP *pbstr; //Pointer to safearray elements	
		HRESULT hr = SafeArrayAccessData(arr, (void HUGEP**)&pbstr);
		_bstr_t txt("Wellcome!");
		_variant_t varText(txt);
		pbstr[0] = pbstr[1]=pbstr[2]=varText;
		SafeArrayUnaccessData(arr);
		COleVariant id1((long)1);
		//
		_variant_t result = pG2G->Start(_bstr_t("CAB_TEST_PROC"),&arr);
		::SafeArrayDestroy(arr);
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

BOOL CCppUnitTestDlg::WaitUntilTRUE(BOOL* bVar, DWORD dwMilliseconds)
{
	MSG msg;
	DWORD dwStart = GetTickCount();
	while(TRUE)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(*bVar)
			return TRUE;
		if(GetTickCount()-dwStart>dwMilliseconds)
			return FALSE;
	}
	return TRUE;
}

