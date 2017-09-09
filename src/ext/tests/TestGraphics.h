#ifndef _TEST_GRAPHICS_H_
#define _TEST_GRAPHICS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestGraphics : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestGraphics);
		CPPUNIT_TEST(testGetPixel);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testGetPixel();

private:
	void testTextRGB(long rgb);

	int nWindowIndex;
	int nNoWindow;
};

#endif //_TEST_WINDOW_CLOSE_H_
