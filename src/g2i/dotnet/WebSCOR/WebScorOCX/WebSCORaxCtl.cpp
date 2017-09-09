// WebSCORaxCtl.cpp : Implementation of the CWebSCORaxCtrl ActiveX Control class.

#include "stdafx.h"
#include "WebSCORax.h"
#include "WebSCORaxCtl.h"
#include "WebSCORaxPpg.h"
#include "winsock.h"
#include "s2hlib.h"
#include <atlbase.h>
#include "ProxySettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWebSCORaxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWebSCORaxCtrl, COleControl)
	//{{AFX_MSG_MAP(CWebSCORaxCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CWebSCORaxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CWebSCORaxCtrl)
	DISP_PROPERTY_EX(CWebSCORaxCtrl, "ServerPort", GetServerPort, SetServerPort, VT_BSTR)
	DISP_PROPERTY_EX(CWebSCORaxCtrl, "ServerName", GetServerName, SetServerName, VT_BSTR)
	DISP_PROPERTY_EX(CWebSCORaxCtrl, "UserName", GetUserName, SetUserName, VT_BSTR)
	DISP_PROPERTY_EX(CWebSCORaxCtrl, "Password", GetPassword, SetPassword, VT_BSTR)
	DISP_PROPERTY_EX(CWebSCORaxCtrl, "SessionId", GetSessionId, SetSessionId, VT_BSTR)
	DISP_PROPERTY_EX(CWebSCORaxCtrl, "UserMode", GetUserMode, SetUserMode, VT_BSTR)
	DISP_STOCKPROP_READYSTATE()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CWebSCORaxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CWebSCORaxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CWebSCORaxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	EVENT_STOCK_READYSTATECHANGE()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CWebSCORaxCtrl, 1)
	PROPPAGEID(CWebSCORaxPropPage::guid)
END_PROPPAGEIDS(CWebSCORaxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebSCORaxCtrl, "WEBSCORAX.WebSCORaxCtrl.1",
	0xc9acf70c, 0x5532, 0x4ac3, 0x8a, 0xb0, 0xc5, 0x12, 0x77, 0x86, 0xab, 0x50)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CWebSCORaxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DWebSCORax =
		{ 0xc2ba2b0a, 0xdd0f, 0x43c8, { 0xb7, 0xfd, 0xde, 0x4a, 0x64, 0xb1, 0x76, 0xa7 } };
const IID BASED_CODE IID_DWebSCORaxEvents =
		{ 0x4d5a7878, 0x4420, 0x472d, { 0xa2, 0x18, 0x23, 0x17, 0x72, 0x91, 0xd1, 0xe6 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwWebSCORaxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CWebSCORaxCtrl, IDS_WEBSCORAX, _dwWebSCORaxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::CWebSCORaxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebSCORaxCtrl

BOOL CWebSCORaxCtrl::CWebSCORaxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister) {
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_WEBSCORAX,
			IDB_WEBSCORAX,
			afxRegApartmentThreading, 
			_dwWebSCORaxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	} else {
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::CWebSCORaxCtrl - Constructor

CWebSCORaxCtrl::CWebSCORaxCtrl()
{
	InitializeIIDs(&IID_DWebSCORax, &IID_DWebSCORaxEvents);

	m_lReadyState = READYSTATE_LOADING;

	m_bDidRunCode = false;
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::~CWebSCORaxCtrl - Destructor

CWebSCORaxCtrl::~CWebSCORaxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::OnDraw - Drawing function

void CWebSCORaxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!m_bDidRunCode)
	{
		Run ();
		m_bDidRunCode = true;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::DoPropExchange - Persistence support

void CWebSCORaxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_DataPath(pPX, _T("ServerName"), ServerName);
	PX_DataPath(pPX, _T("ServerPort"), ServerPort);
	PX_DataPath(pPX, _T("UserName"), UserName);
	PX_DataPath(pPX, _T("Password"), Password);
	PX_DataPath(pPX, _T("SessionId"), SessionId);
	PX_DataPath(pPX, _T("UserMode"), UserMode);
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::GetControlFlags -
// Flags to customize MFC's implementation of ActiveX controls.
//
// For information on using these flags, please see MFC technical note
// #nnn, "Optimizing an ActiveX Control".
DWORD CWebSCORaxCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// The control can activate without creating a window.
	// TODO: when writing the control's message handlers, avoid using
	//		the m_hWnd member variable without first checking that its
	//		value is non-NULL.
	dwFlags |= windowlessActivate;
	return dwFlags;
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::OnResetState - Reset control to default state

void CWebSCORaxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl::AboutBox - Display an "About" box to the user

void CWebSCORaxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_WEBSCORAX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxCtrl message handlers

BSTR CWebSCORaxCtrl::GetServerPort() 
{
	CString strResult;
    strResult = ServerPort.GetPath();
    return strResult.AllocSysString();
}

void CWebSCORaxCtrl::SetServerPort(LPCTSTR lpszNewValue) 
{
	Load(lpszNewValue, ServerPort);
	SetModifiedFlag();
}

BSTR CWebSCORaxCtrl::GetServerName() 
{
	CString strResult;
	strResult = ServerName.GetPath();
	return strResult.AllocSysString();
}

void CWebSCORaxCtrl::SetServerName(LPCTSTR lpszNewValue) 
{
	Load(lpszNewValue, ServerName);
	SetModifiedFlag();
}

// Function name	: sendAll
// Description	    : 
// Return type		: int 
// Argument         : SOCKET sd
// Argument         : const char * buf
// Argument         : int len
int sendAll(SOCKET sd, const char * buf, int len)
{
	int curr_pos =0;
	while(curr_pos < len)
	{
		
		int rc1 = ::send(sd, buf+curr_pos, len-curr_pos, 0);
		if (rc1 < 0)
			return rc1;
		
		curr_pos += rc1;
	}
	
	return curr_pos;
}



// Function name	: receiveAll
// Description	    : 
// Return type		: string 
// Argument         : SOCKET sd
void receiveAll(SOCKET sd)
{
	//CString s=new CString("");
	char buf[1024];
	
	
	while (true)
	{
		int rc = recv(sd, buf, sizeof(buf),0);
		if (rc <= 0)
			break;
		
		//s += string(buf, rc);
	}
	
	//return s;
	
}

int ConnectToSleeper()
{
	WORD sockVersion;
	WSADATA wsaData;

	sockVersion = MAKEWORD(1, 1);
	WSAStartup(sockVersion, &wsaData);
	LPHOSTENT hostEntry = gethostbyname("www.totalrc.net");

	if (!hostEntry)
		return -1;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		return -2;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = 80;

	int nret = connect(s,
					   (LPSOCKADDR)&serverInfo,
					   sizeof(struct sockaddr));

	if (nret == SOCKET_ERROR) {
		return -3;
	}

	
	CString request("GET / HTTP/1.0\r\n\r\n");
	// send request
	int rc = sendAll(s, request, strlen(request));

	// receive response
	receiveAll(s);

	return 0;
	//closesocket(s);
}

int CWebSCORaxCtrl::Ping(LPCTSTR server, LPCTSTR port)
{
	// "ping" a server to see if there are any firewalls blocking the connection
	WORD sockVersion;
	WSADATA wsaData;

	sockVersion = MAKEWORD(1, 1);
	WSAStartup(sockVersion, &wsaData);
	LPHOSTENT hostEntry = gethostbyname(server);

	if (!hostEntry)
		return -1;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		return -2;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(_ttoi(port));

	int nret = connect(s,
					   (LPSOCKADDR)&serverInfo,
					   sizeof(struct sockaddr));

	if (nret == SOCKET_ERROR) {
		return -3;
	}

	closesocket(s);

	return 0;
}

CString ExecuteExternalFile(CString csExeName, CString csArguments)
{
  CString csExecute;
  csExecute=csExeName + " " + csArguments;
  
  SECURITY_ATTRIBUTES secattr; 
  ZeroMemory(&secattr,sizeof(secattr));
  secattr.nLength = sizeof(secattr);
  secattr.bInheritHandle = TRUE;

  HANDLE rPipe, wPipe;

  //Create pipes to write and read data
  CreatePipe(&rPipe,&wPipe,&secattr,0);
  //
  STARTUPINFO sInfo; 
  ZeroMemory(&sInfo,sizeof(sInfo));
  PROCESS_INFORMATION pInfo; 
  ZeroMemory(&pInfo,sizeof(pInfo));
  sInfo.cb=sizeof(sInfo);
  sInfo.dwFlags=STARTF_USESTDHANDLES;
  sInfo.hStdInput=NULL; 
  sInfo.hStdOutput=wPipe; 
  sInfo.hStdError=wPipe;
  char command[1024]; strcpy(command,  
          csExecute.GetBuffer(csExecute.GetLength()));

  //Create the process here.
  CreateProcess(0, command,0,0,TRUE,
          NORMAL_PRIORITY_CLASS|CREATE_NO_WINDOW,0,0,&sInfo,&pInfo);
  CloseHandle(wPipe);

  //now read the output pipe here.
  char buf[100];
  DWORD reDword; 
  CString m_csOutput,csTemp;
  BOOL res;
  do
  {
                  res=::ReadFile(rPipe,buf,100,&reDword,0);
                  csTemp=buf;
                  m_csOutput+=csTemp.Left(reDword);
  }while(res);
  return m_csOutput;
}

CString GetRegVal( const HKEY & hRootKey, const char * szSubKeyPath, const char * szValName, char * szValData )
{
	CString strRetMsg;
	HKEY hKey;
	DWORD dwCount = -1;
	if ( RegCreateKey( hRootKey, szSubKeyPath, &hKey ) != ERROR_SUCCESS ) {
		strRetMsg.Format( "Error Opening Key (%s)", szSubKeyPath );
		return strRetMsg;
	}
	CRegKey regKey;
	regKey.Attach( hKey );
	if ( regKey.QueryValue( szValData, szValName, &dwCount ) != ERROR_SUCCESS ) {
		strRetMsg.Format( "Error Querrying Value (%s)", szValName );
	}
	return strRetMsg;
}

CString GetRegVal( const HKEY & hRootKey, const char * szSubKeyPath, const char * szValName, DWORD & dwValData )
{
	CString strRetMsg;
	HKEY hKey;
	AfxMessageBox(CString("PROC: start"), MB_OK, 0);
	if ( RegCreateKey( hRootKey, szSubKeyPath, &hKey ) != ERROR_SUCCESS ) {
		strRetMsg.Format( "Error Opening Key (%s)", szSubKeyPath );
		AfxMessageBox(CString("PROC: first if problem"), MB_OK, 0);
		return strRetMsg;
	}
	CRegKey regKey;
	regKey.Attach( hKey );
	if ( regKey.QueryValue( dwValData, szValName ) != ERROR_SUCCESS ) {
		AfxMessageBox(CString("PROC: second if problem"), MB_OK, 0);
		strRetMsg.Format( "Error Querrying Value (%s)", szValName );
	}
	return strRetMsg;
}

void configureSocksFromDlg(CProxySettingsDlg* dlg)
{
	setSystemOption("http.proxy.authentication","yyÂ");
	setSystemOption("http.proxy.authenticationtype","");

	if (dlg->m_useautoconfig) {
		setSystemOption("http.proxy.type", "2");
		setSystemOption("http.proxy.script", dlg->m_script);
	}

	if (dlg->m_useproxy) {
		setSystemOption("http.proxy.type", "1");
		setSystemOption("http.proxy.server", dlg->m_proxyserver);
		setSystemOption("http.proxy.port", dlg->m_port);
	}

	if (dlg->m_useauthentication) {
		setSystemOption("http.proxy.domain", dlg->m_domain);
		setSystemOption("http.proxy.user", dlg->m_username);
		setSystemOption("http.proxy.password", dlg->m_password);
	}

}

void CWebSCORaxCtrl::Run()

{
	boolean cancelled = false;
	CString strCommand;
	CString path = GetProgramDir();
    int x = Ping(ServerName.GetPath(), ServerPort.GetPath());


	//AfxMessageBox("Server: " + ServerName.GetPath(), MB_OK, 0);
	//AfxMessageBox("Port: " + ServerPort.GetPath(), MB_OK, 0);


	if (x == 0) {
		//AfxMessageBox(CString("Worked without tunneling"), MB_OK, 0);
		strCommand = ServerName.GetPath();
	} else {
		strCommand = "localhost";

		//AfxMessageBox(CString("Need to tunnel"), MB_OK, 0);
		// configure all the s2h info

		loadConfigFromIniFile(path + "\\s2h.ini");
		setSystemOption("trc.http.host","216.248.198.144");
		setSystemOption("trc.http.port","80");
		setSystemOption("trc.http.servlet","/servlets/http2tcp");
		setSystemOption("trc.worker.servlet","/servlets/http2tcp");
		setSystemOption("trc.worker.sslport","443");

		setSystemOption("PERSONAL_GATEWAY","1");
		setSystemOption("VALID_USER","test");
		setSystemOption("SOCKS_PORT", "1080");
		setSystemOption("USER_AGENT", "");
		setSystemOption("PROBE_TUNNELING_METHOD", "0");
		setSystemOption("TUNNELING_METHOD","POSTRECV");
		setSystemOption("RECONNECT_ATTEMPTS","5");

#if 0
		setSystemOption("trc.http.host","207.44.178.212");
		setSystemOption("trc.http.port","80");
		setSystemOption("trc.http.servlet","/servlets/http2tcp");
		setSystemOption("trc.worker.servlet","/servlets/http2tcp");
		setSystemOption("trc.worker.sslport","443");

		setSystemOption("PERSONAL_GATEWAY","0");
		setSystemOption("VALID_USER","pprintz@gensym.com55262b903eb9c310b1d94ca3d8be141c");
		setSystemOption("SOCKS_PORT", "1080");
		setSystemOption("USER_AGENT", "");
		setSystemOption("PROBE_TUNNELING_METHOD", "0");
		setSystemOption("TUNNELING_METHOD","CONNECTGATEWAYNCONNECT");
		setSystemOption("RECONNECT_ATTEMPTS","5");
#endif

		//setSystemOption("closeconnection.timeout.tcp","");
		//setSystemOption("connection.timeout.tcp","");
		//setSystemOption("connection.timeout.udp","");

		// stuff needed to make it work, not sure what it all means
		setSystemOption("gateway.locator","http://www.totalrc.net/gateway.txt");
		setSystemOption("gateway.type","0");
		setSystemOption("probing.host","www.yahoo.com");
		setSystemOption("probing.port","80");
		setSystemOption("trc.worker.host","");
		setSystemOption("trc.worker.port","");

		// save all the saved proxy info in case we need it later
		CString proxytype = getSystemOption("http.proxy.type");
		CString proxyport = getSystemOption("http.proxy.port");
		CString proxyauthentication = getSystemOption("http.proxy.authentication");
		CString proxyauthenticationtype = getSystemOption("http.proxy.authenticationtype");
		CString proxydomain = getSystemOption("http.proxy.domain");
		CString proxyscript = getSystemOption("http.proxy.script");
		CString proxyserver = getSystemOption("http.proxy.server");
		CString proxyuser = getSystemOption("http.proxy.user");
		CString proxypassword = getSystemOption("http.proxy.password");

		// proxy related things
		setSystemOption("http.proxy.type","0"); // set to 3 for autodiscovery, 1 for server/ip, 2 for script

#if 0
		// eventually stop logging
		setConfigOption("DBGLOG","C:\\log.txt");
		setConfigOption("LOGLEVEL","100000");
#endif

		startS2H();
		setConfigOption("map." + ServerPort.GetPath() + ".host", ServerName.GetPath());
		setConfigOption("map." + ServerPort.GetPath() + ".port", ServerPort.GetPath());
		
		startPM(_ttoi(ServerPort.GetPath()), "TCP");

#if 0
		AfxMessageBox(proxytype, MB_OK, 0);
		AfxMessageBox(proxyport, MB_OK, 0);
		AfxMessageBox(proxyauthentication, MB_OK, 0);
		AfxMessageBox(proxyauthenticationtype, MB_OK, 0);
		AfxMessageBox(proxydomain, MB_OK, 0);
		AfxMessageBox(proxyscript, MB_OK, 0);
		AfxMessageBox(proxyserver, MB_OK, 0);
		AfxMessageBox(proxyuser, MB_OK, 0);
		AfxMessageBox(proxypassword, MB_OK, 0);


		saveConfigToIniFile("c:\\test.ini");
#endif


		// now try pinging the server through socks
		// CHANGE THIS BACK TO 0 TO MAKE IT WORK!!!
		if (Ping("localhost",ServerPort.GetPath()) == 0) {
			// worked
			//AfxMessageBox(CString("Worked without proxy server settings"), MB_OK, 0);
		} else {
			stopS2H();
			// See if there's a file we can load with proxy info and try that
			CString settingsFileName = path + "\\proxysettings.dat";

			CProxySettingsDlg dlg;
			dlg.loadFromFile(path + CString("\\proxysettings.dat"));
			configureSocksFromDlg(&dlg);
			startS2H();

			if (Ping("localhost", ServerPort.GetPath()) == 0) {
				// worked with saved user settings in .dat file, nothing more to do
				// deliberately don't save data back, because the settings in
				// the file already work!
			} else {
				// the settings didn't work, so open a dialog
				if (dlg.DoModal() == IDOK) {
					// values
					// call function to parse dlg member data into s2hlib data
					stopS2H();
					configureSocksFromDlg(&dlg);
					startS2H();
					if (Ping("localhost", ServerPort.GetPath()) == 0) {
						// worked, let's store the values they entered
						dlg.writeToFile(settingsFileName);
					} else {
						AfxMessageBox("Unable to connect; try again or contact Gensym Customer Support", MB_OK, 0);
					}
		
				} else {
					// hmm, what to do when someone cancels?
					cancelled = true;
				}

			}
		}
	}

	if (!cancelled) {
		strCommand = strCommand + " " + ServerPort.GetPath();
		strCommand = strCommand + " -user-name " + UserName.GetPath() + " -password " + Password.GetPath();
		strCommand = strCommand + " -init-string " + SessionId.GetPath() + " -user-mode " + UserMode.GetPath();
		
		path += "\\twng.exe";

		//AfxMessageBox(path + " " + strCommand, MB_OK, 0);
		CString err;

		HINSTANCE ret = ShellExecute(NULL, NULL, path, strCommand, NULL, SW_SHOWNORMAL);
		switch (((int)ret))
		{
			case 0:
				err = "The operating system is out of memory or resources.";
				break;
			case ERROR_FILE_NOT_FOUND:
				err = "The specified file was not found.";
				break;
			case ERROR_PATH_NOT_FOUND:
				err = "The specified path was not found.";
				break;
			case ERROR_BAD_FORMAT:
				err = "The .exe file is invalid (non-Microsoft Win32 .exe or error in .exe image).";
				break;
			case SE_ERR_ACCESSDENIED:
				err = "The operating system denied access to the specified file.";
				break;
			case SE_ERR_ASSOCINCOMPLETE:
				err = "The file name association is incomplete or invalid.";
				break;
			case SE_ERR_DDEBUSY:
				err = "The Dynamic Data Exchange (DDE) transaction could not be completed because other DDE transactions were being processed.";
				break;
			case SE_ERR_DDEFAIL:
				err = "The DDE transaction failed.";
				break;
			case SE_ERR_DDETIMEOUT:
				err = "The DDE transaction could not be completed because the request timed out.";
				break;
			case SE_ERR_DLLNOTFOUND:
				err = "The specified dynamic-link library (DLL) was not found.";
				break;
			case SE_ERR_NOASSOC:
				err = "There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.";
				break;
			case SE_ERR_OOM:
				err = "There was not enough memory to complete the operation.";
				break;
			case SE_ERR_SHARE:
				err = "	A sharing violation occurred.";
				break;
		}
	
		if (((int)ret) <= 32)
			AfxMessageBox(err, MB_ICONEXCLAMATION|MB_OK);
	}
}

BSTR CWebSCORaxCtrl::GetUserName() 
{
	CString strResult;
    strResult = UserName.GetPath();
	return strResult.AllocSysString();
}

void CWebSCORaxCtrl::SetUserName(LPCTSTR lpszNewValue) 
{
	Load(lpszNewValue, UserName);
	SetModifiedFlag();
}

BSTR CWebSCORaxCtrl::GetPassword() 
{
	CString strResult;
    strResult = Password.GetPath();
	return strResult.AllocSysString();
}

void CWebSCORaxCtrl::SetPassword(LPCTSTR lpszNewValue) 
{
	Load(lpszNewValue, Password);
	SetModifiedFlag();
}

BSTR CWebSCORaxCtrl::GetSessionId() 
{
	CString strResult;
	strResult = SessionId.GetPath();
	return strResult.AllocSysString();
}

void CWebSCORaxCtrl::SetSessionId(LPCTSTR lpszNewValue) 
{
	Load(lpszNewValue, SessionId);
	SetModifiedFlag();
}

BSTR CWebSCORaxCtrl::GetUserMode() 
{
	CString strResult;
    strResult = UserMode.GetPath();
	return strResult.AllocSysString();
}

void CWebSCORaxCtrl::SetUserMode(LPCTSTR lpszNewValue) 
{
	Load(lpszNewValue, UserMode);
	SetModifiedFlag();
}

CString CWebSCORaxCtrl::GetProgramDir()
{
    CString RtnVal;
#ifdef  UNICODE
	WCHAR   FileName[MAX_PATH];
#else
    char    FileName[MAX_PATH];
#endif

    GetModuleFileName(AfxGetInstanceHandle(), FileName, MAX_PATH);
    RtnVal = FileName;
    RtnVal = RtnVal.Left(RtnVal.ReverseFind('\\'));
    return RtnVal;
}
