#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class G2TreeView;

class TestG2TreeViewLazyLoad : public CPPUNIT_NS::TestFixture  
{
  CPPUNIT_TEST_SUITE(TestG2TreeViewLazyLoad);
    CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();

};
