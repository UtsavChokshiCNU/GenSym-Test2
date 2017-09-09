// TestConsoleHandler.h: interface for the CTestConsoleHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCONSOLEHANDLER_H__3666FB63_3A37_48A9_AAAC_F1453F8C16C2__INCLUDED_)
#define AFX_TESTCONSOLEHANDLER_H__3666FB63_3A37_48A9_AAAC_F1453F8C16C2__INCLUDED_

#include "TestHiddenWnd.h"

//////////////////////////////////////////////////////////////////////
// CTestConsoleHandler class
// 
//	Test class that is used to test ConsoleCtrlHandler() functionality
//////////////////////////////////////////////////////////////////////
class CTestConsoleHandler : public CTestHiddenWnd 
{
	CPPUNIT_TEST_SUITE(CTestConsoleHandler);
	CPPUNIT_TEST(testHandler);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestConsoleHandler();
	virtual ~CTestConsoleHandler();

	// Test ConsoleCtrlHandler()
	void testHandler();
};

#endif // !defined(AFX_TESTCONSOLEHANDLER_H__3666FB63_3A37_48A9_AAAC_F1453F8C16C2__INCLUDED_)
