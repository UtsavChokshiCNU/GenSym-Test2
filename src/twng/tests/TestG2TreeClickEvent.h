#ifndef _TEST_G2_TREE_CLICK_EVENT_H_
#define _TEST_G2_TREE_CLICK_EVENT_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestG2TreeClickEvent : public CPPUNIT_NS::TestFixture  
{

	CPPUNIT_TEST_SUITE(TestG2TreeClickEvent);
	CPPUNIT_TEST(testClickEvent);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testClickEvent();
};

#endif //
