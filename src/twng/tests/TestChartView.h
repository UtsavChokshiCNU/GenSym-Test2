#ifndef _TEST_CHART_VIEW_H_
#define _TEST_CHART_VIEW_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestChartView : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestChartView);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void test();
};

#endif //_TEST_CHART_VIEW_H_
