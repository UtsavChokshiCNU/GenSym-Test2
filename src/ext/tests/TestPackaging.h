#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestPackaging :
	public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPackaging);
		CPPUNIT_TEST(testIsG2Enterprise);
    CPPUNIT_TEST_SUITE_END();

public:
	TestPackaging(void);
	~TestPackaging(void);

private:
	void testIsG2Enterprise();
};
