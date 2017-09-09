// CTestLogMessage.cpp: implementation of the CTestLogMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "TestG2LogMessage.h"
#include "WndRunner.h"

extern wchar_t*  g_pServerNameW ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLogMessage::CTestLogMessage()
{
}

CTestLogMessage::~CTestLogMessage()
{
}

//////////////////////////////////////////////////////////////////////
// Test ConsoleCtrlHandler()
//////////////////////////////////////////////////////////////////////
void CTestLogMessage::testLogMessage()
{
	wchar_t *combinedMsg = new wchar_t [1024] ;
	swprintf(combinedMsg, L"Unable to register item with handle %ld.  Context is not connected to an OPCServer [%s].",
					5, L"OPC Server NAME") ;

	// Test g_pServerNameW
	//CPPUNIT_ASSERT(g_pServerNameW);

	delete [] combinedMsg;
}

CPPUNIT_TEST_SUITE_REGISTRATION(CTestLogMessage);