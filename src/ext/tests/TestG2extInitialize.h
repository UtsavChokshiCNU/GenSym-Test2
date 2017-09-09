#ifndef _TEST_G2_EXT_INITIALIZE_H_
#define _TEST_G2_EXT_INITIALIZE_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestG2extInitialize : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestG2extInitialize);
		CPPUNIT_TEST(testWindowClassCreation);
		CPPUNIT_TEST(testNtEventsAreUsed);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	void testWindowClassCreation();
	void testNtEventsAreUsed();
};

#endif //_TEST_G2_EXT_INITIALIZE_H_
