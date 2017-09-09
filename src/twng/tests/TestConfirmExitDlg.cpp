//----------------------------------------------------------------------------
#include "stdafx.h"
#include "TestConfirmExitDlg.h"
#include "ConfirmExitDlg.h"

//----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION(TestConfirmExitDlg);

//----------------------------------------------------------------------------
//  class TestConfirmExitDlgHelper
//
//  Contais functions to set/resert "Don't ask again" checkbox 
//  state into registry.
//  Destructor perform restoring of the registry settings as they were 
//  at time of class instance creation.
class TestConfirmExitDlgHelper
{
public:
	//  Constructor - read state of "Don't ask again" 
	// checkbox from registry and remember it
	TestConfirmExitDlgHelper::TestConfirmExitDlgHelper()
	{	
		// remember current checkbox state
		dontAskAgainOldState = GetDontAskAgain();
	}

	//  Destructor - restores  original value in registry
	TestConfirmExitDlgHelper::~TestConfirmExitDlgHelper()
	{
		AfxGetApp()->WriteProfileInt(ConfirmExitDialog_RegSection, 
			ConfirmExitDialog_DontAskAgain_RegEntry, dontAskAgainOldState);
	}

	//  Read state of "Don't ask again" checkbox from registry
	bool TestConfirmExitDlgHelper::GetDontAskAgain()
	{
		return (AfxGetApp()->GetProfileInt(ConfirmExitDialog_RegSection, 
			ConfirmExitDialog_DontAskAgain_RegEntry, 0) != 0);
	}

	// Set "Don't ask again" checkbox
	void TestConfirmExitDlgHelper::SetDontAskAgain()
	{
		AfxGetApp()->WriteProfileInt(ConfirmExitDialog_RegSection, 
			ConfirmExitDialog_DontAskAgain_RegEntry, 1);
	}

	// Reset "Don't ask again" checkbox
	void TestConfirmExitDlgHelper::ResetDontAskAgain()
	{
		AfxGetApp()->WriteProfileInt(ConfirmExitDialog_RegSection, 
			ConfirmExitDialog_DontAskAgain_RegEntry, 0);
	}
private:
	bool dontAskAgainOldState;				// Hold old checkbox state

};

//----------------------------------------------------------------------------
// static DWORD WINAPI createDialog(LPVOID)
//
// Function for new thread execution.
// As we work with modal dialog, we must to create dialog 
// in new thread for have ability to send messages to it.
//
// Return: 1 - if ConfirmExitDialog_AskToExit() function returns true
//         0 - if ConfirmExitDialog_AskToExit() function returns false
// See comments to ConfirmExitDialog_AskToExit() function.
//
//----------------------------------------------------------------------------
static DWORD WINAPI createDialog(LPVOID)
{
	return ConfirmExitDialog_AskToExit();
}

//----------------------------------------------------------------------------
// TestConfirmExitDlg::TestConfirmExitDlg()
//
// Constructor of TestConfirmExitDlg class
// Save reference to tested dialog window handle
//
//----------------------------------------------------------------------------
TestConfirmExitDlg::TestConfirmExitDlg()
	: dlgHwnd(GetConfirmExitDialogHandle())
{
}

//----------------------------------------------------------------------------
// void TestConfirmExitDlg::testYesButtonCheckBoxOn()
//
// Function verify correctness functionality 
// of ConfirmExitDialog_AskToExit() function 
// in case if "Don't ask again" checkbox checked in some of previous session.
// In this case function return true immediately, without dialog creation.
//
//----------------------------------------------------------------------------
void TestConfirmExitDlg::testReturnTrueImmediately()
{
	TestConfirmExitDlgHelper helper;
	DWORD exitCode;
	HANDLE hThread;

	// change registry
	helper.SetDontAskAgain();

	// and remember changes
	int expected = helper.GetDontAskAgain();

	// create thread (must to terminate at once)
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// dialog must not to create
	CPPUNIT_ASSERT(dlgHwnd == 0);

	// thread must to terminate at once
	DWORD waitResult = WaitForSingleObject(hThread, 1000);
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal true 
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(exitCode);

	// get saved value from registry
	int actual = helper.GetDontAskAgain();

	// not changed after ConfirmExitDialog_AskToExit function exit 
	CPPUNIT_ASSERT_EQUAL(expected, actual);
	CPPUNIT_ASSERT_EQUAL(1, actual);
}


//----------------------------------------------------------------------------
// void TestConfirmExitDlg::testYesButtonCheckBoxOn()
//
// Function verify correctness of dialog functionality:
// with the following user actions:
//     - set checkbox
//     - click "Ok"
//
//----------------------------------------------------------------------------
void TestConfirmExitDlg::testYesButtonCheckBoxOn()
{
	TestConfirmExitDlgHelper helper;
	DWORD exitCode;
	HANDLE hThread;

	// change registry (reset checkbox)
	helper.ResetDontAskAgain();

	// create dialog in other thread
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// must be correctly HWND
	CPPUNIT_ASSERT(dlgHwnd != 0);
	// set checkbox
	SendDlgItemMessage(dlgHwnd, IDC_DONTASK_CHECK, BM_SETCHECK, BST_CHECKED, 0);

	// click on "Yes" button
	SendDlgItemMessage(dlgHwnd, IDYES, BM_CLICK, 0, 0);

	// after click dialog shall closed and thread terminated
	DWORD waitResult = WaitForSingleObject(hThread, 2000);
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal true
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(exitCode);

	// get saved value from registry
	int actual = helper.GetDontAskAgain();

	// it must be equal 1 because we set checkbox before click
	CPPUNIT_ASSERT_EQUAL(1, actual);
}

//----------------------------------------------------------------------------
// void TestConfirmExitDlg::testYesButtonCheckBoxOff()
//
// Function verify correctness of dialog functionality
// with the following user actions:
//     - reset checkbox
//     - click "Ok"
//----------------------------------------------------------------------------
void TestConfirmExitDlg::testYesButtonCheckBoxOff()
{
	TestConfirmExitDlgHelper helper;
	DWORD exitCode;
	HANDLE hThread;

	// change registry (reset checkbox)
	helper.ResetDontAskAgain();

	// create dialog in other thread
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// must be correctly HWND
	CPPUNIT_ASSERT(dlgHwnd != 0);
	// reset checkbox
	SendDlgItemMessage(dlgHwnd, IDC_DONTASK_CHECK, BM_SETCHECK, BST_UNCHECKED, 0);

	// emulation of "Yes" button click
	SendDlgItemMessage(dlgHwnd, IDYES, BM_CLICK, 0, 0);
	
	// after click dialog shall to close and thread to terminate
	DWORD waitResult = WaitForSingleObject(hThread, 2000);
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal false
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(exitCode);

	// get saved value from registry
	int actual = helper.GetDontAskAgain();

	// it must be equal 0 because we reset checkbox before click
	CPPUNIT_ASSERT_EQUAL(0, actual);
}


//----------------------------------------------------------------------------
// void TestConfirmExitDlg::testNoButtonCheckBoxOn()
//
// Function verify correctness of dialog functionality
// with the following user actions:
//     - set checkbox
//     - click "No"
//----------------------------------------------------------------------------
void TestConfirmExitDlg::testNoButtonCheckBoxOn()
{
	TestConfirmExitDlgHelper helper;
	DWORD exitCode;
	HANDLE hThread;

	// change registry (reset checkbox)
	helper.ResetDontAskAgain();

	// create dialog in other thread
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// must be correctly HWND
	CPPUNIT_ASSERT(dlgHwnd != 0);

	// set checkbox
	SendDlgItemMessage(dlgHwnd, IDC_DONTASK_CHECK, BM_SETCHECK, BST_CHECKED, 0);

	// emulation of "No" button click
	SendDlgItemMessage(dlgHwnd, IDNO, BM_CLICK, 0, 0);

	// after click dialog shall to close and thread to terminate
	DWORD waitResult = WaitForSingleObject(hThread, 2000);
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal false
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(!exitCode);

	// get saved value from registry
	int actual = helper.GetDontAskAgain();

	// it must be equal 1 because we set checkbox before click
	CPPUNIT_ASSERT_EQUAL(1, actual);

}

//----------------------------------------------------------------------------
// void TestConfirmExitDlg::testNoButtonCheckBoxOff()
//
// Function verify correctness of dialog functionality
// with the following user actions:
//     - reset checkbox
//     - click "No"
//----------------------------------------------------------------------------
void TestConfirmExitDlg::testNoButtonCheckBoxOff()
{
	TestConfirmExitDlgHelper helper;
	DWORD exitCode;
	HANDLE hThread;

	// change registry (reset checkbox)
	helper.ResetDontAskAgain();

	// create dialog in other thread
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// must be correctly HWND
	CPPUNIT_ASSERT(dlgHwnd != 0);

	// reset checkbox
	SendDlgItemMessage(dlgHwnd, IDC_DONTASK_CHECK, BM_SETCHECK, BST_UNCHECKED, 0);

	// emulation of "No" button click
	SendDlgItemMessage(dlgHwnd, IDNO, BM_CLICK, 0, 0);
	
	// after click dialog shall to close and thread to terminate
	DWORD waitResult = WaitForSingleObject(hThread, 2000);
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal false
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(!exitCode);

	// get saved value from registry
	int actual = helper.GetDontAskAgain();

	// it must be equal 0 because we set checkbox before click
	CPPUNIT_ASSERT_EQUAL(0, actual);
}

//----------------------------------------------------------------------------
// void TestConfirmExitDlg::testNoButtonCheckBoxOff()
//
// Function verify correctness of dialog functionality
// with the following user actions:
//     - press Escape key
//----------------------------------------------------------------------------
void TestConfirmExitDlg::testCancel()
{
	TestConfirmExitDlgHelper helper;
	DWORD exitCode;
	HANDLE hThread; 
	DWORD waitResult;
	int expected;
	int actual;
	UINT scan;

	// change registry (reset checkbox)
	helper.ResetDontAskAgain();

	// get current value from registry
	expected = helper.GetDontAskAgain();

	// create dialog in other thread
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// must be correctly HWND
	CPPUNIT_ASSERT(dlgHwnd != 0);

	// set checkbox
 	SendDlgItemMessage(dlgHwnd, IDC_DONTASK_CHECK, BM_SETCHECK, BST_CHECKED, 0);

	// then press "Escape" key
	SetForegroundWindow(dlgHwnd);
	scan = MapVirtualKey(VK_ESCAPE, 0);
	keybd_event(VK_ESCAPE, scan, 0 ,0);
	Sleep(100);
	keybd_event(VK_ESCAPE, scan, KEYEVENTF_KEYUP, 0);

	// after click dialog shall to close and thread to terminate
	waitResult = WaitForSingleObject(hThread, 8000);
	// we had a lot of timeouts here, so, let's check explicitly
	// for better identification of the problem from the test log
	CPPUNIT_ASSERT_MESSAGE("Check there was no timeout", waitResult != WAIT_TIMEOUT);
	// because on timeout the following would produce "expected 0, got 258"
	// so you would need to lookup what "258" means (unless you're so weird
	// to know that `WAIT_TIMEOUT == 258`)
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal false
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(!exitCode);

	// get current value from registry
	actual = helper.GetDontAskAgain();

	// values actual and expected must be same 
	CPPUNIT_ASSERT_EQUAL(expected, actual);

	// now repeat previous actions but reset checkbox instead of set

	// create dialog in other thread
	hThread = CreateThread(0, 0, createDialog, 0, 0, 0);
	Sleep(1000);

	// must be correctly HWND
	CPPUNIT_ASSERT(dlgHwnd != 0);

	// now reset checkbox
	SendDlgItemMessage(dlgHwnd, IDC_DONTASK_CHECK, BM_SETCHECK, BST_UNCHECKED, 0);

	// then press "Escape" key
	SetForegroundWindow(dlgHwnd);
	scan = MapVirtualKey(VK_ESCAPE, 0);
	keybd_event(VK_ESCAPE, scan, 0 ,0);
	Sleep(100);
	keybd_event(VK_ESCAPE, scan, KEYEVENTF_KEYUP, 0);
	
	// after click dialog shall to close and thread to terminate
	waitResult = WaitForSingleObject(hThread, 2000);
	CPPUNIT_ASSERT_EQUAL(WAIT_OBJECT_0, waitResult);

	// exit code of thread must be equal false
	GetExitCodeThread(hThread, &exitCode);
	CPPUNIT_ASSERT(!exitCode);

	// get current value from registry
	actual = helper.GetDontAskAgain();

	// values actual and expected must be same 
	CPPUNIT_ASSERT_EQUAL(expected, actual);
}
