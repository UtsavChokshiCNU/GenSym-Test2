
#pragma once
#include "stdafx.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////
// CTestInitStringParser class
// 
//	Test class that is used to test initialization string parser functionality
//////////////////////////////////////////////////////////////////////
class CTestInitStringParser : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CTestInitStringParser);
	CPPUNIT_TEST(testParser_localhost);
	CPPUNIT_TEST(testParser_remote_host);
	CPPUNIT_TEST(testParser_tunnel);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestInitStringParser();
	virtual ~CTestInitStringParser();

	void testParser_localhost();
	void testParser_remote_host();
	void testParser_tunnel();
};
