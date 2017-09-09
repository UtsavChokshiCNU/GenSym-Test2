#include "stdafx.h"
#include "CTestHLA.h"
#include "gsi_main.h"
#include "TestConstants.h"

void G2_createAndJoinFederation(gsi_item args[], gsi_int count, gsi_int call_index);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestHLA::CTestHLA()
{
}

CTestHLA::~CTestHLA()
{
}

//////////////////////////////////////////////////////////////////////
// Set up test
//////////////////////////////////////////////////////////////////////
void CTestHLA::setUp()
{

}

//////////////////////////////////////////////////////////////////////
// Free test resources
//////////////////////////////////////////////////////////////////////
void CTestHLA::tearDown()
{
}

//////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////
void CTestHLA::testHLA1()
{
	G2_joined_Federation = FALSE;
	createIsOk = true;
	joinIsOk = true;

	G2_createAndJoinFederation(arguments, 2, 1);

	CPPUNIT_ASSERT(!isErrorResult);
	CPPUNIT_ASSERT(G2_joined_Federation == TRUE);
}

void CTestHLA::testHLA2()
{
	G2_joined_Federation = FALSE;
	createIsOk = true;
	joinIsOk = false;

	G2_createAndJoinFederation(arguments, 2, 1);

	CPPUNIT_ASSERT(isErrorResult);
	CPPUNIT_ASSERT(G2_joined_Federation == FALSE);
}

void CTestHLA::testHLA3()
{
	G2_joined_Federation = FALSE;
	createIsOk = false;
	joinIsOk = true;

	G2_createAndJoinFederation(arguments, 2, 1);

	CPPUNIT_ASSERT(isErrorResult);
	CPPUNIT_ASSERT(G2_joined_Federation == FALSE);
}

void CTestHLA::testHLA4()
{
	G2_joined_Federation = FALSE;
	createIsOk = false;
	joinIsOk = false;

	G2_createAndJoinFederation(arguments, 2, 1);

	CPPUNIT_ASSERT(isErrorResult);
	CPPUNIT_ASSERT(G2_joined_Federation == FALSE);
}

void CTestHLA::testHLA5()
{
	G2_joined_Federation = TRUE;
	createIsOk = true;
	joinIsOk = true;

	G2_createAndJoinFederation(arguments, 2, 1);

	CPPUNIT_ASSERT(isErrorResult);
	CPPUNIT_ASSERT(G2_joined_Federation == TRUE);
}

// Register test suite
CPPUNIT_TEST_SUITE_REGISTRATION(CTestHLA);
