#ifndef _TEST_LOCKED_DIALOG_H_
#define _TEST_LOCKED_DIALOG_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <windows.h>

class TestLockedDialog : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestLockedDialog);
		CPPUNIT_TEST(testIsCommandLocked);
		CPPUNIT_TEST(testStartAndLockDialog);
		CPPUNIT_TEST(testLockDialog);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testIsCommandLocked();
	void testStartAndLockDialog();
	void testLockDialog();

private:
	HWND hWnd;
};

#endif //_TEST_APP_EXIT_H_
