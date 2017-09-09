#include "TestChartProperties.h"
#include <windows.h>

#define BOOL int

#define PEP_bALLOWLINE 3279 // copied from PE header
#define NEW_PROPERTY   10001
#define CHART_SUCCESS  0    // copied from mdi.c

CPPUNIT_TEST_SUITE_REGISTRATION(TestChartProperties);

extern "C" {
	BOOL isNewChartLibProperty(long prop);
	long int g2ext_chart_set_int(long handle, long prop, long i, long j, long value);
}

void TestChartProperties::testNewChartLibProperty()
{
    BOOL bIsNewProp = isNewChartLibProperty(PEP_bALLOWLINE);
	CPPUNIT_ASSERT(bIsNewProp == FALSE);

    bIsNewProp = isNewChartLibProperty(NEW_PROPERTY);
	CPPUNIT_ASSERT(bIsNewProp != FALSE);
}

void TestChartProperties::testHandleNewChartLibProperty()
{
    long lChartResult = g2ext_chart_set_int(0, PEP_bALLOWLINE, 0, 0, 1);
	CPPUNIT_ASSERT(lChartResult != CHART_SUCCESS);

    lChartResult = g2ext_chart_set_int(0, NEW_PROPERTY, 0, 0, 1);
	CPPUNIT_ASSERT(lChartResult == CHART_SUCCESS);
}

void TestChartProperties::setUp()
{
}

void TestChartProperties::tearDown()
{
}
