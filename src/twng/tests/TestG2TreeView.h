#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class G2TreeView;

class TestG2TreeView : public CPPUNIT_NS::TestFixture  
{
  CPPUNIT_TEST_SUITE(TestG2TreeView);
    CPPUNIT_TEST(testDestroyTime);
    CPPUNIT_TEST(testOnDestroyOfBaseClassIsCalled);
    CPPUNIT_TEST(testPostDestroyMessageOnAddItem);
    CPPUNIT_TEST(testShowToolTip);
	CPPUNIT_TEST(testPaint);
  CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testDestroyTime();
	void testOnDestroyOfBaseClassIsCalled();
	void testPostDestroyMessageOnAddItem();
	void testShowToolTip();
	void testPaint();

private:
	G2TreeView* view;
	CWnd* mainWindow;
};
