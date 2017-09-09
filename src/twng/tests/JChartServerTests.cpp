#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "JChartServer.h"

class JChartServerTests : public CPPUNIT_NS::TestFixture  
{
  CPPUNIT_TEST_SUITE(JChartServerTests);
    CPPUNIT_TEST(testGetServerPath);
    CPPUNIT_TEST(testGetInstance);
  CPPUNIT_TEST_SUITE_END();

private:
	JChartServer* pServer;

public:
	virtual void setUp()
	{
		pServer = JChartServer::GetInstance();
	}

	void testGetServerPath()
	{
		TCHAR szFileName[MAX_PATH];
		::GetModuleFileName(NULL, szFileName, MAX_PATH);
		CString szModule(szFileName);
		CString szDir = szModule.Left(szModule.ReverseFind(_T('\\')));
		CString szRet;
		szRet.Format(L"cmd /c java -cp %s\\jfree\\jfree-lib.jar;"
			L"%s\\jfree\\jfreechart-1.0.13.jar;"
			L"%s\\jfree\\jcommon-1.0.16.jar gensym.charts.ChartsRunner %d",
			szDir, szDir, szDir, 4000);

		CPPUNIT_ASSERT_EQUAL(szRet, pServer->GetServerPath());
	}

	void testGetInstance()
	{
		CPPUNIT_ASSERT(pServer != NULL);
		CPPUNIT_ASSERT_EQUAL(std::string("localhost"),
			std::string(pServer->getHost()));
		CPPUNIT_ASSERT_EQUAL(4000, pServer->getPort());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(JChartServerTests);
