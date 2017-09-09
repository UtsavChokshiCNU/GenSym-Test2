#ifndef _TEST_TEMP_ICONS_H_
#define _TEST_TEMP_ICONS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestTempIcons : public CPPUNIT_NS::TestFixture  
{

CPPUNIT_TEST_SUITE(TestTempIcons);
  CPPUNIT_TEST(testTempIcon);
  CPPUNIT_TEST(testIconControl);
CPPUNIT_TEST_SUITE_END();

public:
	void testTempIcon();
	void testIconControl();

	virtual void setUp();
	virtual void tearDown();

private:
	void test(void (TestTempIcons::*func)());
	void testTempIconFunc();
	void testIconControlFunc();

	long m_nPixmap;
	long m_nPixmapMask;
	int m_nTmpWindow;
	long m_nIcon;
};

#endif
