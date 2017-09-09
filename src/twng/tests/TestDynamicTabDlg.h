#ifndef _TEST_DYNAMIC_TAB_DLG_H_
#define _TEST_DYNAMIC_TAB_DLG_H_

#include "stdafx.h"
#include "DynamicTabsDlg.h"
#include "../ext/c/dyndlgs.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CG2TabWidget;

class TestDynamicTabDlg : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDynamicTabDlg);
    CPPUNIT_TEST(testTab);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setup();
    virtual void tearDown();

    void testTab();

private:
	CWnd* pParent;
	CG2TabWidget *pTab;
};
#endif
