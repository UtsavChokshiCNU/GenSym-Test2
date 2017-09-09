// CppUnitTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestDlg.h"
#include "G2COMTestCase.h"
#include <cppunit/ui/mfc/MfcTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/XmlOutputter.h>
#include "MfcTestRunnerEx/src/MfcTestRunnerEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestApp

BEGIN_MESSAGE_MAP(CCppUnitTestApp, CWinApp)
	//{{AFX_MSG_MAP(CCppUnitTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestApp construction

CCppUnitTestApp::CCppUnitTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCppUnitTestApp object

CCppUnitTestApp theApp;
CPPUNIT_TEST_SUITE_REGISTRATION(CG2COMTestCase);

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestApp initialization

BOOL CCppUnitTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	MfcTestRunnerEx runner;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
    runner.run();    
    // Create stream for writting XML report
    std::ofstream report("unittest.ax-link.cpp.xml");
    // Create XML outputter and write report to stream
    CppUnit::XmlOutputter(&runner.result(), report).write();

    return TRUE;

	/*
	CCppUnitTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
	*/
}
