#ifndef _TEST_MASK_BITMAP_H_
#define _TEST_MASK_BITMAP_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestMaskBitmap : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestMaskBitmap);
		CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

public:
	void test();
};

#endif //_TEST_APP_EXIT_H_