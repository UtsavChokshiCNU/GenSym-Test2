#ifndef _TEST_CHART_PROPERTIES_H_
#define _TEST_CHART_PROPERTIES_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestChartProperties : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestChartProperties);
		CPPUNIT_TEST(testNewChartLibProperty);
		CPPUNIT_TEST(testHandleNewChartLibProperty);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testNewChartLibProperty();
	void testHandleNewChartLibProperty();
};

#endif // _TEST_CHART_PROPERTIES_H_
