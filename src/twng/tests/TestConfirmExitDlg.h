#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestConfirmExitDlg : public CPPUNIT_NS::TestFixture  
{
    CPPUNIT_TEST_SUITE(TestConfirmExitDlg);
	CPPUNIT_TEST(testReturnTrueImmediately);
    CPPUNIT_TEST(testYesButtonCheckBoxOn);
    CPPUNIT_TEST(testYesButtonCheckBoxOff);
    CPPUNIT_TEST(testNoButtonCheckBoxOn);
    CPPUNIT_TEST(testNoButtonCheckBoxOff);
    CPPUNIT_TEST(testCancel);
    CPPUNIT_TEST_SUITE_END();

public:
	TestConfirmExitDlg();
	void testReturnTrueImmediately();
	void testYesButtonCheckBoxOn();
	void testYesButtonCheckBoxOff();
	void testNoButtonCheckBoxOn();
	void testNoButtonCheckBoxOff();
	void testCancel();
private:
	const HWND& dlgHwnd;
};
