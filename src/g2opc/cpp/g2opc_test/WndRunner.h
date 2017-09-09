// WndRunner.h: interface for the CWndRunner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDRUNNER_H__E861B33F_21C2_43B2_BA5B_77C09EF8E3B9__INCLUDED_)
#define AFX_WNDRUNNER_H__E861B33F_21C2_43B2_BA5B_77C09EF8E3B9__INCLUDED_

#include "stdafx.h"

// CMyHiddenWin class forward declaration
class CMyHiddenWin;

//////////////////////////////////////////////////////////////////////
//
// CWndRunner class
//
//	Creates a CG2OpcHiddenWin object in separated thread and runs
// his message loop to test functionality added into CG2OpcHiddenWin.
//
//////////////////////////////////////////////////////////////////////

class CWndRunner
{
public:
	CWndRunner();
	~CWndRunner();

	// Creates thread and runs CG2OpcHiddenWin message loop
	void Run();

	// Wait until created thread has stopped
	void Wait();

	// Wait until g_hWnd handle to hidden window not created
	// Call WaitWhileNotCreated() only after Run() has been called
	void WaitWhileNotCreated();

	// Stop thread
	void Stop();

	// Test thread state
	bool isRunning() const;

	// Calls CG2OpcHiddenWin::OnDestroy() directly
	void callDestroy();

	// Test Tray Icon state
	bool isInTray() const;

private:

	// Thread routine
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	
	// Pointer to hidden window object that is created on thread
	static CMyHiddenWin* hiddenWnd;

	HANDLE m_hThread;		// Thread handle
	HANDLE m_hStopEvent;	// Stop event handle
	HANDLE m_hCreatedEvent;	// "Create hidden window" event handle
};

#endif // !defined(AFX_WNDRUNNER_H__E861B33F_21C2_43B2_BA5B_77C09EF8E3B9__INCLUDED_)
