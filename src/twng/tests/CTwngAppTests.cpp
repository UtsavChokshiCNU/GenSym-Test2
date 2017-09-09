#include "stdafx.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Twng.h"

class CTwngAppTests: public CPPUNIT_NS::TestFixture  
{

	CPPUNIT_TEST_SUITE(CTwngAppTests);
		CPPUNIT_TEST(test_m_msgCurAccess);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_m_msgCurAccess() {
		MSG* msg = &theApp.m_msgCur;
		msg->hwnd = (HWND) 1;
		CPPUNIT_ASSERT_EQUAL(msg->hwnd, theApp.m_msgCur.hwnd);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CTwngAppTests);
