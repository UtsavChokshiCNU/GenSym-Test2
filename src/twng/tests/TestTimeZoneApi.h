#ifndef _TEST_TIME_ZONE_API_H_
#define _TEST_TIME_ZONE_API_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestTimeZoneApi : public CPPUNIT_NS::TestFixture  
{

CPPUNIT_TEST_SUITE(TestTimeZoneApi);
  CPPUNIT_TEST(testGetTimeZoneInfo);
CPPUNIT_TEST_SUITE_END();

public:
	void testGetTimeZoneInfo();

	virtual void setUp();
	virtual void tearDown();
};

#endif
