// TestGsiLoop.cpp: implementation of the CTestGsiLoop class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TestGsiLoop.h"


//////////////////////////////////////////////////////////////////////
// g2opc global variables
//////////////////////////////////////////////////////////////////////
HANDLE	g_hGsiThread = 0;	// GsiLoop thread handle
short	g_license_status = 0;

extern LPSTR g_lpCmdLine;	// Application command line

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestGsiLoop::CTestGsiLoop()
{
}

CTestGsiLoop::~CTestGsiLoop()
{
}

//////////////////////////////////////////////////////////////////////
// Set up test
//////////////////////////////////////////////////////////////////////
void CTestGsiLoop::setUp()
{
    // Start the GSI loop thread
	g_shutdown_request = false;
    g_hGsiThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) GsiLoop, g_lpCmdLine, 0, NULL);

	// Wait license status
    while (g_hGsiThread && !g_license_status)
	{
        Sleep(50);
	}
}

//////////////////////////////////////////////////////////////////////
// Free test resources
//////////////////////////////////////////////////////////////////////
void CTestGsiLoop::tearDown()
{
	// Test if GsiLoop thread is down
	if (WaitForSingleObject(g_hGsiThread, 0) == WAIT_TIMEOUT)
	{
		// There are happened errors in some test
		// Terminating gsi loop thread is needed
		TerminateThread(g_hGsiThread, -1);
	}

	// Fre GsiLoop thread handle
	CloseHandle(g_hGsiThread);
	g_hGsiThread = 0;
}

//////////////////////////////////////////////////////////////////////
// Test GsiLoop() function
//////////////////////////////////////////////////////////////////////
void CTestGsiLoop::testGsiLoop()
{
	// Test Gsi Loop
	CPPUNIT_ASSERT(g_hGsiThread != 0);
	CPPUNIT_ASSERT(g_license_status > 0);
	CPPUNIT_ASSERT(!g_shutdown_request);

	// Test GsiLoop shutdown
	g_shutdown_request = true;
	// Wait until GsiLoop thread has finished
	WaitForSingleObject(g_hGsiThread, INFINITE);
	CPPUNIT_ASSERT(!g_shutdown_request);

	// Test SetProcessShutdownParameters() call in gsi loop
	// -----------------------------------------
	DWORD level = 0;
	DWORD flags = 0;
	CPPUNIT_ASSERT(GetProcessShutdownParameters(&level, &flags));
	CPPUNIT_ASSERT(level == 0x280); // default level
	CPPUNIT_ASSERT(flags == SHUTDOWN_NORETRY);
}

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(CTestGsiLoop);
