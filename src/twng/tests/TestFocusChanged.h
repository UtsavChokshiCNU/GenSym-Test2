#ifndef _TEST_FOCUSCHANGED_H_
#define _TEST_FOCUSCHANGED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "dyndlgs.h"

/*
 * Class that contains TWNG focus-changed test
 */

class TestFocusChanged : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestFocusChanged);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	void test();
private:
	HWND hWnd;
	CONTROLITEM *pTab;
	CONTROLITEM *pTextBox;
	GENSYMDIALOG *dialog;
	CONTROLITEM** pControls;
};

#endif