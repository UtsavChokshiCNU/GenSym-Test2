// ProxySettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TelewindowsAx.h"
#include "ProxySettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProxySettingsDlg dialog


CProxySettingsDlg::CProxySettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProxySettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProxySettingsDlg)
	m_password = _T("");
	m_domain = _T("");
	m_username = _T("");
	m_script = _T("");
	m_proxyserver = _T("");
	m_useauthentication = FALSE;
	m_useautoconfig = FALSE;
	m_useproxy = FALSE;
	m_port = _T("");
	//}}AFX_DATA_INIT
}

#define BUFFER_SIZE 2000

int CProxySettingsDlg::loadFromFile(CString filename)
{
	CFile proxyFile;
	CFileException fileException;
	char buffer[BUFFER_SIZE]; // this is horrible
	char key[100];
	char val[100];
	CString keyString;
	int nActual;

	AfxMessageBox(CString("start"), MB_OK, 0);
	if (!proxyFile.Open(filename, CFile::modeRead, &fileException)) {
		// something bad happened
		AfxMessageBox(CString("something bad with file"), MB_OK, 0);
		return -1;
	} else {
		nActual = proxyFile.Read(buffer, BUFFER_SIZE);
		if (nActual >= BUFFER_SIZE) {
			// something bad happened
			AfxMessageBox(CString("something bad with amount read"), MB_OK, 0);
		} else {
			AfxMessageBox(CString("start else"), MB_OK, 0);
			int start = -1, equalpos = -1;
			int i = 0;
			int j;
			// need start of the line, where the equal is, end of the line
			while (i < nActual) {
				if (buffer[i] == ';') {
					if (start < 0) {
						start = i+1; 
					} else {
						// do stuff here
						if (equalpos != -1) {
							for (j = start; j <= equalpos-1; j++) {
								key[j - start] = buffer[j];
							}
							key[equalpos-1 - start + 1] = 0;		
	
							for (j = equalpos+1; j<= i-1; j++) {
								val[j - (equalpos + 1)] = buffer[j];	
							}
							val[i-1 - (equalpos-1) + 1 -2] = 0;
							AfxMessageBox("key: " + CString(key), MB_OK, 0);
							AfxMessageBox("val: " + CString(val), MB_OK, 0);


							keyString = CString(key);
							if (keyString == CString("USEAUTOCONFIG")) {
								m_useautoconfig = (CString("TRUE") == CString(val));
							} else if (keyString == CString("USEAUTHENTICATION")) {
								m_useauthentication = (CString("TRUE") == CString(val));
							} else if (keyString == CString("USEPROXY")) {
								m_useproxy = (CString("TRUE") == CString(val));
							} else if (keyString == CString("PROXYSERVER")) {
								m_proxyserver = CString(val);
							} else if (keyString == CString("PORT")) {
								m_port = CString(val);
							} else if (keyString == CString("SCRIPT")) {
								m_script = CString(val);
							} else if (keyString == CString("USERNAME")) {
								m_username = CString(val);
							} else if (keyString == CString("PASSWORD")) {
								m_password = CString(val);
							} else if (keyString == CString("DOMAIN")) {
								m_domain = CString(val);
							} else {
								AfxMessageBox("UNKNOWN KEY: " + keyString, MB_OK, 0);
							}

							start = -1;
							equalpos = -1;
						} else {
							AfxMessageBox("weird equalpos", MB_OK, 0);

						}
					}
				} else if (buffer[i] == '=') {
					equalpos = i;
				}
				i++;
			}
		}
	}

	proxyFile.Close();

	return -1;
}

int CProxySettingsDlg::writeToFile(CString filename)
{
	CFile proxyFile;
	CFileException fileException;

	if (!proxyFile.Open(filename, CFile::modeCreate | CFile::modeReadWrite, &fileException)) {
		AfxMessageBox("broke writing", MB_OK, 0);
	} else {
		CString temp;
		
		temp = (m_useautoconfig) ? CString(";USEAUTOCONFIG=TRUE;\n") :
								   CString(";USEAUTOCONFIG=FALSE;\n");
		proxyFile.Write(temp, temp.GetLength());

		temp = (m_useauthentication) ? CString(";USEAUTHENTICATION=TRUE;\n") :
									   CString(";USEAUTHENTICATION=FALSE;\n");
		proxyFile.Write(temp, temp.GetLength());

		temp = (m_useproxy) ? CString(";USEPROXY=TRUE;\n") :
							  CString(";USEPROXY=FALSE;\n");
		proxyFile.Write(temp, temp.GetLength());

		temp = ";PROXYSERVER=" + m_proxyserver + ";\n";
		proxyFile.Write(temp, temp.GetLength());

		temp = ";PORT=" + m_port + ";\n";
		proxyFile.Write(temp, temp.GetLength());

		temp = ";SCRIPT=" + m_script + ";\n";
		proxyFile.Write(temp, temp.GetLength());

		temp = ";USERNAME=" + m_username + ";\n";
		proxyFile.Write(temp, temp.GetLength());

		temp = ";PASSWORD=" + m_password + ";\n";
		proxyFile.Write(temp, temp.GetLength());

		temp = ";DOMAIN=" + m_domain + ";\n";
		proxyFile.Write(temp, temp.GetLength());
	}

	proxyFile.Close();
	return -1;
}

void CProxySettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProxySettingsDlg)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_DOMAIN, m_domain);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDX_Text(pDX, IDC_EDIT_SCRIPT, m_script);
	DDX_Text(pDX, IDC_EDIT_PROXY, m_proxyserver);
	DDX_Check(pDX, IDC_CHECK_USEAUTHENTICATION, m_useauthentication);
	DDX_Check(pDX, IDC_CHECK_USEAUTOCONFIG, m_useautoconfig);
	DDX_Check(pDX, IDC_CHECK_USEPROXY, m_useproxy);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProxySettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CProxySettingsDlg)
	ON_BN_CLICKED(IDC_CHECK_USEAUTHENTICATION, OnCheckUseauthentication)
	ON_BN_CLICKED(IDC_CHECK_USEAUTOCONFIG, OnCheckUseautoconfig)
	ON_BN_CLICKED(IDC_CHECK_USEPROXY, OnCheckUseproxy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProxySettingsDlg message handlers

void CProxySettingsDlg::OnCheckUseauthentication() 
{
	// TODO: Add your control notification handler code here	

}

void CProxySettingsDlg::OnCheckUseautoconfig() 
{
	// TODO: Add your control notification handler code here
	
}

void CProxySettingsDlg::OnCheckUseproxy() 
{
	// TODO: Add your control notification handler code here
	
}
