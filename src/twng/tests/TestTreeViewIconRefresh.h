#ifndef _TEST_TREE_VIEW_ICON_REFRESH_H_
#define _TEST_TREE_VIEW_ICON_REFRESH_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestTreeViewIconRefresh : public CPPUNIT_NS::TestFixture  
{

	CPPUNIT_TEST_SUITE(TestTreeViewIconRefresh);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif //
