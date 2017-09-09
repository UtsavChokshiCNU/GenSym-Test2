// CTestLogMessage.h: interface for the CTestLogMessage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TEST_G2LOGMESSAGE_H_
#define _TEST_G2LOGMESSAGE_H_

#include "stdafx.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////
// CTestLogMessage class
// 
//	Test class that is used to test log_message_ds() functionality
//////////////////////////////////////////////////////////////////////
class CTestLogMessage : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CTestLogMessage);
	CPPUNIT_TEST(testLogMessage);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestLogMessage();
	virtual ~CTestLogMessage();

	void testLogMessage();
};

#endif // !defined(_TEST_G2LOGMESSAGE_H_)
