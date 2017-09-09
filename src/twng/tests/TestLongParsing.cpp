#include "stdafx.h"

#include "TestLongParsing.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestLongParsing);

void TestLongParsing::setUp() {
	editor = new G2Editor(0);
}

void TestLongParsing::tearDown() {
	delete editor;
}

void TestLongParsing::testTokenParsing() {
	CPPUNIT_ASSERT(editor != 0);
	CPPUNIT_ASSERT(editor->ClassifyToken("737L", 0) == G2S_NUMBER);
	CPPUNIT_ASSERT(editor->ClassifyToken("-9283775L", 0) == G2S_NUMBER);
}

void TestLongParsing::testLongParsing() {
	CPPUNIT_ASSERT(editor != 0);
	CPPUNIT_ASSERT(g2pvt_is_long_number("9284653L") == TRUE);
	CPPUNIT_ASSERT(g2pvt_is_long_number("-9347535473L") == TRUE);
	CPPUNIT_ASSERT(g2pvt_is_long_number("9284653") == FALSE);
	CPPUNIT_ASSERT(g2pvt_is_long_number("-10948276") == FALSE);
	CPPUNIT_ASSERT(g2pvt_is_long_number("9284653K") == FALSE);
	CPPUNIT_ASSERT(g2pvt_is_long_number("9833683a") == FALSE);

}

void TestLongParsing::testSpecialLongParsingCases() {
	CPPUNIT_ASSERT(g2pvt_is_long_number("+") == FALSE);
	CPPUNIT_ASSERT(g2pvt_is_long_number("-") == FALSE);
	CPPUNIT_ASSERT(g2pvt_is_long_number(NULL) == FALSE);
}
