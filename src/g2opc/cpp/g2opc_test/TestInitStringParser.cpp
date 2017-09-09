// CTestInitStringParser.cpp: implementation of the CTestInitStringParser class.
//
//////////////////////////////////////////////////////////////////////

#include "TestInitStringParser.h"
#include "WndRunner.h"
#include "string.h"
#include "wchar.h"

void parse_server_and_machine_names(wchar_t* pWholeStrW, wchar_t **pMachineNameW, wchar_t **pServerNameW);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestInitStringParser::CTestInitStringParser()
{
}

CTestInitStringParser::~CTestInitStringParser()
{
}

//////////////////////////////////////////////////////////////////////
// Test for init string without host
//////////////////////////////////////////////////////////////////////
void CTestInitStringParser::testParser_localhost()
{
	wchar_t         *pWholeStrW = L"Matrikon.OPC.Simulation.1";
    wchar_t         *pMachineNameW, *pServerNameW ;
    
	parse_server_and_machine_names(pWholeStrW, &pMachineNameW, &pServerNameW);


	CPPUNIT_ASSERT(wcscmp(pMachineNameW, L"localhost") == 0);
	CPPUNIT_ASSERT(pServerNameW == pWholeStrW);

	
}

// Test for init string with host

void CTestInitStringParser::testParser_remote_host()
{
	wchar_t         *pWholeStrW = L"HP-DEV:Matrikon.OPC.Simulation.1";
    wchar_t         *pMachineNameW, *pServerNameW ;
    
	parse_server_and_machine_names(pWholeStrW, &pMachineNameW, &pServerNameW);


	CPPUNIT_ASSERT(wcscmp(pServerNameW, L"Matrikon.OPC.Simulation.1") == 0);
	CPPUNIT_ASSERT(pMachineNameW == pWholeStrW);

	
}

// Test for init string with tunnel

void CTestInitStringParser::testParser_tunnel()
{
	wchar_t         *pWholeStrW = L"Tunneller:HP-DEV:Matrikon.OPC.Simulation.1";
    wchar_t         *pMachineNameW, *pServerNameW ;
    
	parse_server_and_machine_names(pWholeStrW, &pMachineNameW, &pServerNameW);


	CPPUNIT_ASSERT(pMachineNameW == pWholeStrW);
	CPPUNIT_ASSERT(pServerNameW == pWholeStrW);

	
}

CPPUNIT_TEST_SUITE_REGISTRATION(CTestInitStringParser);