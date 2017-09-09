#ifndef _TEST_GET_TW_CMD_LINE_H_
#define _TEST_GET_TW_CMD_LINE_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

/*
 *  The function we will test in twng.cpp 
 */
extern char *get_tw_cmdline(void);

class TestGetTWCmdLine: public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestGetTWCmdLine);
	CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();

private:
	char *szTestCmdLine_1, *szTestCmdLine_2;
	char *szTestRightRet_1, *szTestRightRet_2;
};

#endif
