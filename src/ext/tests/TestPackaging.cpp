#include "TestPackaging.h"
#include "packaging.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestPackaging);

TestPackaging::TestPackaging(void)
{
}

TestPackaging::~TestPackaging(void)
{
}

void TestPackaging::testIsG2Enterprise()
{
	#ifdef PACKAGING_G2_ENTERPRISE
		CPPUNIT_ASSERT(isG2Enterprise());
	#else
		CPPUNIT_ASSERT(! isG2Enterprise());
	#endif
}
