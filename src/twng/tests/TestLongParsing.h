#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "twng.h"
#include "ScintillaWnd.h"
#include "Editor.h"

class TestLongParsing : public CPPUNIT_NS::TestFixture  
{
	CPPUNIT_TEST_SUITE(TestLongParsing);
		CPPUNIT_TEST(testLongParsing);
		CPPUNIT_TEST(testTokenParsing);
		CPPUNIT_TEST(testSpecialLongParsingCases);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void testLongParsing();
	void testTokenParsing();
	void testSpecialLongParsingCases();

private:
	G2Editor* editor;

};





