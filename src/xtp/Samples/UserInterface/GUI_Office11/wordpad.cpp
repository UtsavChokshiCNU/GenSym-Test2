// wordpad.cpp : Defines the class behaviors for the application.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "wordpad.h"
#include "mainfrm.h"
#include "wordpdoc.h"
#include "wordpvw.h"
#include "strings.h"
#include "key.h"
#include "filenewd.h"
#include <locale.h>
#include <winnls.h>
#include <winreg.h>

#include "AboutDlg.h"


extern BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);
static BOOL RegisterHelper(LPCTSTR* rglpszRegister, LPCTSTR* rglpszSymbols,
	BOOL bReplace);

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CLIPFORMAT cfEmbeddedObject;
CLIPFORMAT cfRTF;
CLIPFORMAT cfRTO;

int CWordPadApp::m_nOpenMsg = RegisterWindowMessage(_T("WordPadOpenMessage"));
int CWordPadApp::m_nPrinterChangedMsg = RegisterWindowMessage(_T("WordPadPrinterChanged"));

const int CWordPadApp::m_nPrimaryNumUnits = 4;
const int CWordPadApp::m_nNumUnits = 7;

CUnit CWordPadApp::m_units[7] =
{
//  TPU,    SmallDiv,   MedDiv, LargeDiv,   MinMove,    szAbbrev,           bSpace
CUnit(1440, 180,        720,    1440,       90,         IDS_INCH1_ABBREV,   FALSE),//inches
CUnit(568,  142,        284,    568,        142,        IDS_CM_ABBREV,      TRUE),//centimeters
CUnit(20,   120,        720,    720,        100,        IDS_POINT_ABBREV,   TRUE),//points
CUnit(240,  240,        1440,   1440,       120,        IDS_PICA_ABBREV,    TRUE),//picas
CUnit(1440, 180,        720,    1440,       90,         IDS_INCH2_ABBREV,   FALSE),//in
CUnit(1440, 180,        720,    1440,       90,         IDS_INCH3_ABBREV,   FALSE),//inch
CUnit(1440, 180,        720,    1440,       90,         IDS_INCH4_ABBREV,   FALSE)//inches
};

static UINT _cdecl DoRegistry(LPVOID lpv)
{
	ASSERT(lpv != NULL);
	((CWordPadApp*)lpv)->UpdateRegistry();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadApp

BEGIN_MESSAGE_MAP(CWordPadApp, CWinApp)
	//{{AFX_MSG_MAP(CWordPadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CWordPadCommandLineInfo::ParseParam(const char* pszParam,BOOL bFlag,BOOL bLast)
{
	if (bFlag)
	{
		if (lstrcmpA(pszParam, "t") == 0)
		{
			m_bForceTextMode = TRUE;
			return;
		}
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadApp construction

CWordPadApp::CWordPadApp() : m_optionsText(0), m_optionsRTF(1),
	m_optionsWord(2), m_optionsWrite(2), m_optionsIP(2), m_optionsNull(0)  //
{
	_tsetlocale(LC_ALL, _T(""));

	m_nFilterIndex = 1;
	DWORD dwVersion = ::GetVersion();
	m_bWin4 = (BYTE)dwVersion >= 4;
#ifndef _UNICODE
	m_bWin31 = (dwVersion > 0x80000000 && !m_bWin4);
#endif
	m_nDefFont = (m_bWin4) ? DEFAULT_GUI_FONT : ANSI_VAR_FONT;
	m_dcScreen.Attach(::GetDC(NULL));
	m_bLargeIcons = m_dcScreen.GetDeviceCaps(LOGPIXELSX) >= 120;
	m_bForceOEM = FALSE;
}

CWordPadApp::~CWordPadApp()
{
	if (m_dcScreen.m_hDC != NULL)
		::ReleaseDC(NULL, m_dcScreen.Detach());
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWordPadApp object

CWordPadApp theApp;

// Register the application's document templates.  Document templates
//  serve as the connection between documents, frame windows and views.
static CSingleDocTemplate DocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWordPadDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWordPadView));

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.
static const CLSID BASED_CODE clsid =
{ 0x73FDDC80L, 0xAEA9, 0x101A, { 0x98, 0xA7, 0x00, 0xAA, 0x00, 0x37, 0x49, 0x59} };

/////////////////////////////////////////////////////////////////////////////
// CWordPadApp initialization

BOOL CWordPadApp::InitInstance()
{
	ParseCommandLine(cmdInfo);

	if (::FindWindow(szWordPadClass, NULL) && IsDocOpen(cmdInfo.m_strFileName))
		return FALSE;

	SetRegistryKey(_T("Codejock Software Sample Applications"));
	LoadOptions();

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
	Enable3dControls();
#endif
	CSplashWnd splash;
	BOOL bSplash = cmdInfo.m_bShowSplash;
	if (!cmdInfo.m_bRunEmbedded)
	{
		switch (m_nCmdShow)
		{
			case SW_HIDE:
			case SW_SHOWMINIMIZED:
			case SW_MINIMIZE:
			case SW_SHOWMINNOACTIVE:
				bSplash = FALSE;
				break;
			case SW_RESTORE:
			case SW_SHOW:
			case SW_SHOWDEFAULT:
			case SW_SHOWNA:
			case SW_SHOWNOACTIVATE:
			case SW_SHOWNORMAL:
			case SW_SHOWMAXIMIZED:
				if (m_bMaximized)
					m_nCmdShow = SW_SHOWMAXIMIZED;
				break;
		}
	}
	else
	{
		//Excel 4 will start OLE servers minimized
		m_nCmdShow = SW_SHOWNORMAL;
	}
	int nCmdShow = m_nCmdShow;

	if (bSplash)
	{
		// only show splash if not embedded
		splash.Create(NULL);
		splash.ShowWindow(SW_SHOW);
		splash.UpdateWindow();
	}

	LoadAbbrevStrings();

	m_hDevNames = CreateDevNames();
	NotifyPrinterChanged((m_hDevNames == NULL));

	free((void*)m_pszHelpFilePath);
	m_pszHelpFilePath = _T("WORDPAD.HLP");

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	RegisterFormats();

	// Initialize RichEdit control
	if (LoadLibrary(_T("RICHED32.DLL")) == NULL)
	{
		AfxMessageBox(IDS_RICHED_LOAD_FAIL, MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	DocTemplate.SetContainerInfo(IDR_CNTR_INPLACE);
	/*DocTemplate.SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));*/

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, &DocTemplate, TRUE);
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
		AfxOleSetUserCtrl(FALSE);

		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// make sure the main window is showing
	m_bPromptForType = FALSE;
	OnFileNew();
	m_bPromptForType = TRUE;
	// destroy splash window
	if (cmdInfo.m_bShowSplash)
		splash.DestroyWindow();
	m_nCmdShow = -1;
	if (m_pMainWnd == NULL) // i.e. OnFileNew failed
		return FALSE;

	if (!cmdInfo.m_strFileName.IsEmpty())   // open an existing document
		m_nCmdShow = nCmdShow;
	// Dispatch commands specified on the command line
	if (cmdInfo.m_nShellCommand != CCommandLineInfo::FileNew &&
		!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	// Enable File Manager drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

BOOL CWordPadApp::IsDocOpen(LPCTSTR lpszFileName)
{
	if (lpszFileName[0] == NULL)
		return FALSE;
	TCHAR szPath[_MAX_PATH];
	AfxFullPath(szPath, lpszFileName);
	ATOM atom = GlobalAddAtom(szPath);
	ASSERT(atom != NULL);
	if (atom == NULL)
		return FALSE;
	EnumWindows(StaticEnumProc, (LPARAM)&atom);
	if (atom == NULL)
		return TRUE;
	DeleteAtom(atom);
	return FALSE;
}

BOOL CALLBACK CWordPadApp::StaticEnumProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szClassName[30];
	GetClassName(hWnd, szClassName, 30);
	if (lstrcmp(szClassName, szWordPadClass) != 0)
		return TRUE;

	ATOM* pAtom = (ATOM*)lParam;
	ASSERT(pAtom != NULL);
	DWORD_PTR dw = NULL;
	::SendMessageTimeout(hWnd, m_nOpenMsg, NULL, (LPARAM)*pAtom,
		SMTO_ABORTIFHUNG, 500, &dw);
	if (dw)
	{
		::SetForegroundWindow(hWnd);
		DeleteAtom(*pAtom);
		*pAtom = NULL;
		return FALSE;
	}
	return TRUE;
}

void CWordPadApp::RegisterFormats()
{
	cfEmbeddedObject = (CLIPFORMAT)::RegisterClipboardFormat(_T("Embedded Object"));
	cfRTF = (CLIPFORMAT)::RegisterClipboardFormat(CF_RTF);
	cfRTO = (CLIPFORMAT)::RegisterClipboardFormat(CF_RETEXTOBJ);
}

CDocOptions& CWordPadApp::GetDocOptions(int nDocType)
{
	switch (nDocType)
	{
		case RD_WINWORD6:
		case RD_WORDPAD:
			return m_optionsWord;
		case RD_RICHTEXT:
			return m_optionsRTF;
		case RD_TEXT:
		case RD_OEMTEXT:
			return m_optionsText;
		case RD_WRITE:
			return m_optionsWrite;
		case RD_EMBEDDED:
			return m_optionsIP;
	}
	ASSERT(FALSE);
	return m_optionsNull;
}

CDockState& CWordPadApp::GetDockState(int nDocType, BOOL bPrimary)
{
	return GetDocOptions(nDocType).GetDockState(bPrimary);
}

void CWordPadApp::SaveOptions()
{
	WriteProfileInt(szSection, szWordSel, m_bWordSel);
	WriteProfileInt(szSection, szUnits, GetUnits());
	WriteProfileInt(szSection, szMaximized, m_bMaximized);
	WriteProfileBinary(szSection, szFrameRect, (BYTE*)&m_rectInitialFrame,
		sizeof(CRect));
	WriteProfileBinary(szSection, szPageMargin, (BYTE*)&m_rectPageMargin,
		sizeof(CRect));
	m_optionsText.SaveOptions(szTextSection);
	m_optionsRTF.SaveOptions(szRTFSection);
	m_optionsWord.SaveOptions(szWordSection);
	m_optionsWrite.SaveOptions(szWriteSection);
	m_optionsIP.SaveOptions(szIPSection);
}

void CWordPadApp::LoadOptions()
{
	BYTE* pb = NULL;
	UINT nLen = 0;

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	if (hFont == NULL)
		hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
	VERIFY(GetObject(hFont, sizeof(LOGFONT), &m_lf));

	m_bWordSel = GetProfileInt(szSection, szWordSel, TRUE);
	TCHAR buf[2];
	buf[0] = NULL;
	GetLocaleInfo(GetUserDefaultLCID(), LOCALE_IMEASURE, buf, 2);
	int nDefUnits = buf[0] == '1' ? 0 : 1;
	SetUnits(GetProfileInt(szSection, szUnits, nDefUnits));
	m_bMaximized = GetProfileInt(szSection, szMaximized, (int)FALSE);

	if (GetProfileBinary(szSection, szFrameRect, &pb, &nLen))
	{
		ASSERT(nLen == sizeof(CRect));
		MEMCPY_S(&m_rectInitialFrame, pb, sizeof(CRect));
		delete pb;
	}
	else
		m_rectInitialFrame.SetRect(0,0,0,0);

	CRect rectScreen(0, 0, GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN));
	CRect rectInt;
	rectInt.IntersectRect(&rectScreen, &m_rectInitialFrame);
	if (rectInt.Width() < 10 || rectInt.Height() < 10)
		m_rectInitialFrame.SetRect(0, 0, 0, 0);

	if (GetProfileBinary(szSection, szPageMargin, &pb, &nLen))
	{
		ASSERT(nLen == sizeof(CRect));
		MEMCPY_S(&m_rectPageMargin, pb, sizeof(CRect));
		delete pb;
	}
	else
		m_rectPageMargin.SetRect(1800, 1440, 1800, 1440);

	m_optionsText.LoadOptions(szTextSection);
	m_optionsRTF.LoadOptions(szRTFSection);
	m_optionsWord.LoadOptions(szWordSection);
	m_optionsWrite.LoadOptions(szWriteSection);
	m_optionsIP.LoadOptions(szIPSection);
}

void CWordPadApp::LoadAbbrevStrings()
{
	for (int i=0;i<m_nNumUnits;i++)
		m_units[i].m_strAbbrev.LoadString(m_units[i].m_nAbbrevID);
}

BOOL CWordPadApp::ParseMeasurement(LPTSTR buf, int& lVal)
{
	TCHAR* pch;
	if (buf[0] == NULL)
		return FALSE;
	float f = (float)_tcstod(buf,&pch);

	// eat white space, if any
	while (isspace(*pch))
		pch++;

	if (pch[0] == NULL) // default
	{
		lVal = (f < 0.f) ? (int)(f*GetTPU()-0.5f) : (int)(f*GetTPU()+0.5f);
		return TRUE;
	}
	for (int i=0;i<m_nNumUnits;i++)
	{
		if (lstrcmpi(pch, GetAbbrev(i)) == 0)
		{
			lVal = (f < 0.f) ? (int)(f*GetTPU(i)-0.5f) : (int)(f*GetTPU(i)+0.5f);
			return TRUE;
		}
	}
	return FALSE;
}

void CWordPadApp::PrintTwips(TCHAR* buf, int nValue, int nDec)
{
	ASSERT(nDec == 2);
	int div = GetTPU();
	int lval = nValue;
	BOOL bNeg = FALSE;

	int* pVal = new int[nDec+1];

	if (lval < 0)
	{
		bNeg = TRUE;
		lval = -lval;
	}
	int i;
	for (i=0;i<=nDec;i++)
	{
		pVal[i] = lval/div; //integer number
		lval -= pVal[i]*div;
		lval *= 10;
	}
	i--;
	if (lval >= div/2)
		pVal[i]++;

	while ((pVal[i] == 10) && (i != 0))
	{
		pVal[i] = 0;
		pVal[--i]++;
	}

	while (nDec && pVal[nDec] == 0)
		nDec--;

#if (_MSC_VER > 1310) // VS2005
	_stprintf_s(buf, 64, _T("%.*f"), nDec, (float)nValue/(float)div);
#else
	_stprintf(buf, _T("%.*f"), nDec, (float)nValue/(float)div);
#endif

	if (m_units[m_nUnits].m_bSpaceAbbrev)
		lstrcat(buf, _T(" "));
	lstrcat(buf, GetAbbrev());
	delete []pVal;
}

/////////////////////////////////////////////////////////////////////////////
// CWordPadApp commands

void CWordPadApp::OnAppAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

int CWordPadApp::ExitInstance()
{
	m_pszHelpFilePath = NULL;

	FreeLibrary(GetModuleHandle(_T("RICHED32.DLL")));
	SaveOptions();

	return CWinApp::ExitInstance();
}

void CWordPadApp::OnFileNew()
{
	int nDocType = -1;
	if (!m_bPromptForType)
	{
		if (cmdInfo.m_bForceTextMode)
			nDocType = RD_TEXT;
		else if (!cmdInfo.m_strFileName.IsEmpty())
		{
			CFileException fe;
			nDocType = GetDocTypeFromName(cmdInfo.m_strFileName, fe);
		}
		if (nDocType == -1)
			nDocType = RD_DEFAULT;
	}
	else
	{
		CFileNewDialog dlg;
		if (dlg.DoModal() == IDCANCEL)
			return;

		nDocType = (dlg.m_nSel == 0) ? RD_DEFAULT:  //Word 6
					(dlg.m_nSel == 1) ? RD_RICHTEXT :   //RTF
					RD_TEXT ;                   //text

		if (nDocType != RD_TEXT)
			cmdInfo.m_bForceTextMode = FALSE;
	}
	m_nNewDocType = nDocType;
	DocTemplate.OpenDocumentFile(NULL);
		// if returns NULL, the user has already been alerted
}

// prompt for file name - used for open and save as
// static function called from app
BOOL CWordPadApp::PromptForFileName(CString& fileName, UINT nIDSTitle,
	DWORD dwFlags, BOOL bOpenFileDialog, int* pType)
{
	ScanForConverters();
	CFileDialog dlgFile(bOpenFileDialog);
	CString title;

	VERIFY(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= dwFlags;
//  dlgFile.m_ofn.Flags &= ~OFN_SHOWHELP;

	int nIndex = m_nFilterIndex;
	if (!bOpenFileDialog)
	{
		int nDocType = (pType != NULL) ? *pType : RD_DEFAULT;
		nIndex = GetIndexFromType(nDocType, bOpenFileDialog);
		if (nIndex == -1)
			nIndex = GetIndexFromType(RD_DEFAULT, bOpenFileDialog);
		if (nIndex == -1)
			nIndex = GetIndexFromType(RD_NATIVE, bOpenFileDialog);
		ASSERT(nIndex != -1);
		nIndex++;
	}
	dlgFile.m_ofn.nFilterIndex = nIndex;
	// strDefExt is necessary to hold onto the memory from GetExtFromType
	CString strDefExt = GetExtFromType(GetTypeFromIndex(nIndex-1, bOpenFileDialog));
	dlgFile.m_ofn.lpstrDefExt = strDefExt;


	CString strFilter = GetFileTypes(bOpenFileDialog);
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bRet = (dlgFile.DoModal() == IDOK) ? TRUE : FALSE;
	fileName.ReleaseBuffer();
	if (bRet)
	{
		if (bOpenFileDialog)
			m_nFilterIndex = dlgFile.m_ofn.nFilterIndex;
		if (pType != NULL)
		{
			int nIndex = (int)dlgFile.m_ofn.nFilterIndex - 1;
			ASSERT(nIndex >= 0);
			*pType = GetTypeFromIndex(nIndex, bOpenFileDialog);
		}
	}
	return bRet;
}

void CWordPadApp::OnFileOpen()
{
	// prompt the user (with all document templates)
	CString newName;
	int nType = RD_DEFAULT;
	if (!PromptForFileName(newName, AFX_IDS_OPENFILE,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, &nType))
		return; // open cancelled

	if (nType == RD_OEMTEXT)
		m_bForceOEM = TRUE;
	OpenDocumentFile(newName);
	m_bForceOEM = FALSE;
	// if returns NULL, the user has already been alerted
}

BOOL CWordPadApp::OnDDECommand(LPTSTR /*lpszCommand*/)
{
	return FALSE;
}


void CWordPadApp::UpdateRegistry()
{
}
void CWordPadApp::WinHelp(DWORD dwData, UINT nCmd)
{
	if (nCmd == HELP_INDEX || nCmd == HELP_CONTENTS)
		nCmd = HELP_FINDER;
	CWinApp::WinHelp(dwData, nCmd);
}

BOOL CWordPadApp::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_PAINT)
		return FALSE;
	// CWinApp::PreTranslateMessage does nothing but call base
	return CWinThread::PreTranslateMessage(pMsg);
}

void CWordPadApp::NotifyPrinterChanged(BOOL bUpdatePrinterSelection)
{
	if (bUpdatePrinterSelection)
		UpdatePrinterSelection(FALSE);
	POSITION pos = m_listPrinterNotify.GetHeadPosition();
	while (pos != NULL)
	{
		HWND hWnd = m_listPrinterNotify.GetNext(pos);
		::SendMessage(hWnd, m_nPrinterChangedMsg, 0, 0);
	}
}

BOOL CWordPadApp::IsIdleMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_NCMOUSEMOVE)
		return FALSE;
	return CWinApp::IsIdleMessage(pMsg);
}

HGLOBAL CWordPadApp::CreateDevNames()
{
	HGLOBAL hDev = NULL;
	if (!cmdInfo.m_strDriverName.IsEmpty() && !cmdInfo.m_strPrinterName.IsEmpty() &&
		!cmdInfo.m_strPortName.IsEmpty())
	{
		hDev = GlobalAlloc(GPTR, 4*sizeof(WORD)+
			cmdInfo.m_strDriverName.GetLength() + 1 +
			cmdInfo.m_strPrinterName.GetLength() + 1 +
			cmdInfo.m_strPortName.GetLength()+1);
		LPDEVNAMES lpDev = (LPDEVNAMES)GlobalLock(hDev);
		lpDev->wDriverOffset = sizeof(WORD)*4;
		lstrcpy((TCHAR*)lpDev + lpDev->wDriverOffset, cmdInfo.m_strDriverName);

		lpDev->wDeviceOffset = (WORD)(lpDev->wDriverOffset + cmdInfo.m_strDriverName.GetLength()+1);
		lstrcpy((TCHAR*)lpDev + lpDev->wDeviceOffset, cmdInfo.m_strPrinterName);

		lpDev->wOutputOffset = (WORD)(lpDev->wDeviceOffset + cmdInfo.m_strPrinterName.GetLength()+1);
		lstrcpy((TCHAR*)lpDev + lpDev->wOutputOffset, cmdInfo.m_strPortName);

		lpDev->wDefault = 0;
	}
	return hDev;
}
