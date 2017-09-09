// TestConsoleHandler.cpp: implementation of the CTestConsoleHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "TestConsoleHandler.h"
#include "WndRunner.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestConsoleHandler::CTestConsoleHandler()
{
}

CTestConsoleHandler::~CTestConsoleHandler()
{
}

//////////////////////////////////////////////////////////////////////
// Test ConsoleCtrlHandler()
//////////////////////////////////////////////////////////////////////
void CTestConsoleHandler::testHandler()
{
	ConsoleCtrlHandler(0);
	// Wait until hidden window thread shutdown
	m_pRunner->Wait();

	// Test g_shutdown_request
	CPPUNIT_ASSERT(g_shutdown_request);
	CPPUNIT_ASSERT(!m_pRunner->isInTray());
}

CPPUNIT_TEST_SUITE_REGISTRATION(CTestConsoleHandler);