#ifndef _TEST_OPC_PROPERTIES_H_
#define _TEST_OPC_PROPERTIES_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////
// TestOPCProperties class
// 
//	Test class that tests GetItemProperties() functionality
//////////////////////////////////////////////////////////////////////
class CTestOPCProperties : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE(CTestOPCProperties);
	CPPUNIT_TEST(testUsingIOPCBrowse);
	CPPUNIT_TEST(testUsingIOPCItemProperties);
	CPPUNIT_TEST_SUITE_END();

public:
	void testUsingIOPCBrowse();
	void testUsingIOPCItemProperties();

	// Test function that tests GetItemProperties() by using
	//  IOPCBrowse (if bUseDAv3 is true) or IOPCItemProperties interfaces
	void testItemProperties(bool bUseDAv3);
};

#endif
