// TestHiddenWnd.cpp: implementation of the CTestHiddenWnd class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestHiddenWnd.h"
#include "WndRunner.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// g2opc global variables
//
HWND	g_hWnd = 0;	// Handle to hidden main window

//////////////////////////////////////////////////////////////////////
CTestHiddenWnd::CTestHiddenWnd():
	m_pRunner(NULL)
{
}

CTestHiddenWnd::~CTestHiddenWnd()
{
}

//////////////////////////////////////////////////////////////////////
// Simple gesi loop thread routine.
// Waits until g_shutdown_request is true end exits.
//////////////////////////////////////////////////////////////////////
DWORD WINAPI GsiThreadProc(LPVOID lpParameter)
{
	while (!g_shutdown_request)
	{
		Sleep(50);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Set up test data
//////////////////////////////////////////////////////////////////////
void CTestHiddenWnd::setUp()
{
	// Run simple GSI thread
	g_shutdown_request = false;
    g_hGsiThread = CreateThread(NULL, 0, GsiThreadProc, NULL, 0, NULL);

	// Create hidden window
	m_pRunner = new CWndRunner();
	m_pRunner->Run();
	// Wait until hidden window has been created
	m_pRunner->WaitWhileNotCreated();
}

//////////////////////////////////////////////////////////////////////
// Free test data
//////////////////////////////////////////////////////////////////////
void CTestHiddenWnd::tearDown()
{
	delete m_pRunner;

	// Free g_hGsiThread handle
	CloseHandle(g_hGsiThread);
	g_hGsiThread = 0;
}

//////////////////////////////////////////////////////////////////////
// Test WM_DESTROY message handler sending WM_DESTROY message
//////////////////////////////////////////////////////////////////////
void CTestHiddenWnd::testOnDestroyMessage()
{
	// Send WM_DESTROY message to hidden window
	PostMessage(g_hWnd, WM_DESTROY, 0, 0);

	// Wait until hidden window thread shutdown
	m_pRunner->Wait();

	// Test g_shutdown_request
	CPPUNIT_ASSERT(g_shutdown_request);
	CPPUNIT_ASSERT(!m_pRunner->isInTray());
}

// Test WM_DESTROY message handler calling OnDestroy()
void CTestHiddenWnd::testOnDestroy()
{
	// "Call" OnDestroy()
	m_pRunner->callDestroy();

	// Wait until hidden window thread shutdown
	m_pRunner->Wait();

	// Test g_shutdown_request
	CPPUNIT_ASSERT(g_shutdown_request);
	CPPUNIT_ASSERT(!m_pRunner->isInTray());
}

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(CTestHiddenWnd);
