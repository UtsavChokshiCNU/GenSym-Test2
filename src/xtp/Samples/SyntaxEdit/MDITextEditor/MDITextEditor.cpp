// MDITextEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MDITextEditor.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MDITextEditorDoc.h"
#include "MDITextEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorApp

BEGIN_MESSAGE_MAP(CMDITextEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CMDITextEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVEALL, OnFileSaveAll)
	ON_COMMAND(ID_FILE_CLOSEALL, OnFileCloseAll)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorApp construction

CMDITextEditorApp::CMDITextEditorApp()
: m_hMutex(NULL)
, m_pMainFrame(0)
, m_pDocTemplate(0)
, m_nFilterIndex(0)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CMDITextEditorApp::~CMDITextEditorApp()
{
	WriteProfileInt(XTP_EDIT_REG_SETTINGS,
		_T("FilterIndex"), m_nFilterIndex);

	WriteProfileString(XTP_EDIT_REG_SETTINGS,
		_T("InitialDir"), m_csInitialDir);

	if (m_hMutex)
	{
		::ReleaseMutex(m_hMutex);
		m_hMutex = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMDITextEditorApp object

CMDITextEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorApp initialization

BOOL CMDITextEditorApp::InitInstance()
{
	// only allow one instance of this application
	if (!CreateSingleInstance())
		return FALSE;

	AfxEnableControlContainer();
	CXTPWinDwmWrapper().SetProcessDPIAware();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	OleInitialize(NULL);

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock Software Sample Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplate(
		IDR_MDITEXTYPE,
		RUNTIME_CLASS(CMDITextEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMDITextEditorView));
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	m_pMainFrame = new CMainFrame;
	if (!m_pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = m_pMainFrame;
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
	{
		// Process files list 
		for (int i = 1; i < __argc; i++)
			OpenDocumentFile(__targv[i]);
	}
	else
	{
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}
	// The main window has been initialized, so show and update it.
	m_pMainFrame->ShowWindow(m_nCmdShow);
	m_pMainFrame->UpdateWindow();

	// restore file open filter index.
	m_nFilterIndex = GetProfileInt(XTP_EDIT_REG_SETTINGS,
		_T("FilterIndex"), m_nFilterIndex);

	m_csInitialDir = GetProfileString(XTP_EDIT_REG_SETTINGS,
		_T("InitialDir"), m_csInitialDir);

	return TRUE;
}

// App command to run the dialog
void CMDITextEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorApp message handlers

BOOL CMDITextEditorApp::RegisterWindowClass()
{
	WNDCLASS wndcls;

	if (!(::GetClassInfo(m_hInstance, CLASSNAME_APPINSTANCE, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style = CS_DBLCLKS;
		wndcls.lpfnWndProc = AfxWndProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = m_hInstance;
		wndcls.hIcon = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
		wndcls.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wndcls.hbrBackground = NULL;
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = CLASSNAME_APPINSTANCE;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CMDITextEditorApp::CreateSingleInstance()
{
	// make the application a single instance, if the
	// mutex does not already exist register the window class
	// and open the first instance.
	m_hMutex = ::CreateMutex(NULL, FALSE, CLASSNAME_APPINSTANCE);
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// Reset our mutext handle (just in case)
		m_hMutex = 0;
		
		// The mutex already exists, which means an instance is already
		// running, get the window handle and bring it to the foreground. If
		// we could not find a valid handle, open the second instance.
		HWND hWnd = ::FindWindowEx(NULL, NULL, CLASSNAME_APPINSTANCE, NULL);
		if (::IsWindow(hWnd))
		{
			::ShowWindow(hWnd, SW_RESTORE);
			::BringWindowToTop(hWnd);
			::SetForegroundWindow(hWnd);
			
			TCHAR szSharedData[_MAX_PATH];

			COPYDATASTRUCT copyData;
			copyData.dwData = cdwData_FileName;
			copyData.lpData = szSharedData;
			copyData.cbData = sizeof(szSharedData);

			// parse command line arguments.
			for (int i = 1; i < __argc; i++)
			{
				STRCPY_S(szSharedData, sizeof(szSharedData), __targv[i]);
				szSharedData[_MAX_PATH-1] = 0;

				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)0, (LPARAM)&copyData);
			}
		}
		
		return FALSE; // Return failure
	}

	return RegisterWindowClass();
}

void CMDITextEditorApp::UpdateAllViews(CView* pSender/*=NULL*/)
{
	for (POSITION posDoc = m_pDocTemplate->GetFirstDocPosition(); posDoc;)
	{
		CXTPSyntaxEditDoc* pDoc = DYNAMIC_DOWNCAST(
			CXTPSyntaxEditDoc, m_pDocTemplate->GetNextDoc(posDoc));
		
		if (pDoc)
			pDoc->UpdateAllViews(pSender, xtpEditHintInitView);
	}
}

BOOL CMDITextEditorApp::ActivateExisting(const CString& csFilePath)
{
	// try to find the document among existing ones
	POSITION posDoc = m_pDocTemplate->GetFirstDocPosition();
	while(posDoc)
	{
		// iterate next open document
		CDocument *pDoc = m_pDocTemplate->GetNextDoc(posDoc);

		// if docs names are the same
		if (pDoc && csFilePath.CompareNoCase(pDoc->GetPathName()) == 0)
		{
			// make existing view as active
			POSITION posView = pDoc->GetFirstViewPosition();
			if (posView)
			{
				CView *pView = pDoc->GetNextView(posView);
				if (pView)
				{
					CFrameWnd* pFrame = pView->GetParentFrame();
					if (pFrame)
					{
						pFrame->ActivateFrame();
					}
				}
			}
			
			return TRUE; // document found, end iteration
		}
	}

	return FALSE;
}

AFX_STATIC int AFX_CDECL GetStructSize()
{
	OSVERSIONINFO ovi;
	::ZeroMemory(&ovi, sizeof(OSVERSIONINFO));
	ovi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	::GetVersionEx(&ovi);

	// Windows 2000 or newer OS, we can use newer file open dialog.
	if ((ovi.dwPlatformId >= VER_PLATFORM_WIN32_NT) && (ovi.dwMajorVersion >= 5))
		return sizeof(OPENFILENAME) + 12;

	// Use standard file open dialog.
	return sizeof(OPENFILENAME);
}

void CMDITextEditorApp::OnFileOpen() 
{
	CString csFilter;
	csFilter.LoadString(IDS_FILE_OPEN_FILTER);

	DWORD dwOpenFlags = 
		OFN_HIDEREADONLY | 
		OFN_ALLOWMULTISELECT |
		OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_ENABLESIZING;

	CFileDialog dlg(TRUE, NULL, NULL, dwOpenFlags, csFilter, NULL);
	dlg.m_ofn.lStructSize		= GetStructSize();
	dlg.m_ofn.nFilterIndex		= m_nFilterIndex;
	dlg.m_ofn.lpstrInitialDir	= m_csInitialDir;

	if (dlg.DoModal() == IDOK)
	{
		for (POSITION pos = dlg.GetStartPosition(); pos;)
		{
			CString csFilePath(dlg.GetNextPathName(pos));

			if (!ActivateExisting(csFilePath))
				m_pDocTemplate->OpenDocumentFile(csFilePath);
		}
		m_nFilterIndex = dlg.m_ofn.nFilterIndex;
		m_csInitialDir = dlg.m_ofn.lpstrInitialDir;
	}
}

void CMDITextEditorApp::OnFileSaveAll() 
{
	POSITION posDoc = m_pDocTemplate->GetFirstDocPosition();
	while (posDoc)
	{
		CDocument* pDoc = m_pDocTemplate->GetNextDoc(posDoc);
		if (pDoc->IsModified())
		{
			if (!pDoc->DoFileSave()) // error.
				break;
		}
	}
}

void CMDITextEditorApp::OnFileCloseAll() 
{
	POSITION posDoc = m_pDocTemplate->GetFirstDocPosition();
	while (posDoc)
	{
		CDocument* pDoc = m_pDocTemplate->GetNextDoc(posDoc);
		if (pDoc->IsModified())
		{
			if (!pDoc->SaveModified()) // user canceled.
				break;
		}
		pDoc->OnCloseDocument();
	}
}
