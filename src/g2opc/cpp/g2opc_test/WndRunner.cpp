// WndRunner.cpp: implementation of the CWndRunner class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "WndRunner.h"
#include "G2OpcHiddenWin.h"
#include "G2OpcClientIcon.h"

//////////////////////////////////////////////////////////////////////
// Helper class that used to directly call CG2OpcHiddenWin::OnDestroy()
//////////////////////////////////////////////////////////////////////
class CMyHiddenWin: public CG2OpcHiddenWin
{
public:
	void callDestroy()
	{
		BOOL handled = FALSE;
		OnDestroy(0, 0, NULL, handled);
	}

	const G2OpcClientIcon& GetIcon() const
	{
		return m_trayIcon;
	}
};

//////////////////////////////////////////////////////////////////////
// Helper class that used to have access to G2OpcClientIcon::m_bCreated
//////////////////////////////////////////////////////////////////////
class CMyClientIcon : public G2OpcClientIcon
{
public:
	CMyClientIcon(const G2OpcClientIcon& icon):
		G2OpcClientIcon(icon)
	{
	}

	bool isCreated() const
	{
		return m_bCreated ? true : false;
	}
};

//////////////////////////////////////////////////////////////////////
// CWndRunner::hiddenWnd definition and initialization
//////////////////////////////////////////////////////////////////////
CMyHiddenWin* CWndRunner::hiddenWnd = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndRunner::CWndRunner():
	m_hThread(0),
	m_hStopEvent(0),
	m_hCreatedEvent(0)
{
	// Create events
	m_hStopEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	m_hCreatedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

CWndRunner::~CWndRunner()
{
	// Stop thread if it is running
	Stop();

	// Close handles
	CloseHandle(m_hThread);
	CloseHandle(m_hStopEvent);
	CloseHandle(m_hCreatedEvent);
}

//////////////////////////////////////////////////////////////////////
// Creates thread and runs CG2OpcHiddenWin message loop
//////////////////////////////////////////////////////////////////////
void CWndRunner::Run()
{
	// Return if thread has been already running
	if (isRunning())
	{
		return;
	}

	CloseHandle(m_hThread);
	ResetEvent(m_hCreatedEvent);

	// Create thread
	m_hThread = CreateThread(NULL, 0, ThreadProc, this, 0, NULL);
}

//////////////////////////////////////////////////////////////////////
// Wait until created thread has stopped
//////////////////////////////////////////////////////////////////////
void CWndRunner::Wait()
{
	WaitForSingleObject(m_hThread, INFINITE);
}

//////////////////////////////////////////////////////////////////////
// Wait until g_hWnd handle to hidden window not created
// Call WaitWhileNotCreated() only after Run() has been called
//////////////////////////////////////////////////////////////////////
void CWndRunner::WaitWhileNotCreated()
{
	if (isRunning())
	{
		WaitForSingleObject(m_hCreatedEvent, INFINITE);
	}
}

//////////////////////////////////////////////////////////////////////
// Stop thread
//////////////////////////////////////////////////////////////////////
void CWndRunner::Stop()
{
	if (isRunning())
	{
		SetEvent(m_hStopEvent);

		// wait until stopped
		Wait();
	}
}

//////////////////////////////////////////////////////////////////////
// Test thread state
//////////////////////////////////////////////////////////////////////
bool CWndRunner::isRunning() const
{
	return (WaitForSingleObject(m_hThread, 0) == WAIT_TIMEOUT);
}

//////////////////////////////////////////////////////////////////////
// Thread routine
//////////////////////////////////////////////////////////////////////
DWORD WINAPI CWndRunner::ThreadProc(LPVOID lpParameter)
{
	CoInitialize(NULL);

	// Get CWndRunner object from parameter
	CWndRunner *runner = (CWndRunner*) lpParameter;

	// Reset stop event
	ResetEvent(runner->m_hStopEvent);

	// Create hidden window and initialize g_hWnd
	CMyHiddenWin win;
    g_hWnd = win.Create();

	// Initialize hiddenWnd
	hiddenWnd = &win;

	// Set "created" event
	SetEvent(runner->m_hCreatedEvent);

    // Main message loop:
    // ------------------
    MSG msg;

	for (;;)
	{
		// Exit from loop if stop event is set
		if (WaitForSingleObject(runner->m_hStopEvent, 0) != WAIT_TIMEOUT)
		{
			break;
		}

		// Hidden window messages
		if (GetMessage(&msg, NULL, 0, 0)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			break;
		}
	}

	// Change events states
	ResetEvent(runner->m_hCreatedEvent);
	SetEvent(runner->m_hStopEvent);

	// Uninitialize hiddenWnd
	hiddenWnd = NULL;

	// Destroy hidden window
    win.DestroyWindow();

	CoUninitialize();
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Calls CG2OpcHiddenWin::OnDestroy() directly
//////////////////////////////////////////////////////////////////////
void CWndRunner::callDestroy()
{
	if (isRunning() && hiddenWnd)
	{
		hiddenWnd->callDestroy();
	}
}

//////////////////////////////////////////////////////////////////////
// Test Tray Icon state
//////////////////////////////////////////////////////////////////////
bool CWndRunner::isInTray() const
{
	bool result = false;

	if (isRunning() && hiddenWnd)
	{
		CMyClientIcon icon(hiddenWnd->GetIcon());
		result = icon.isCreated();
	}

	return result;
}