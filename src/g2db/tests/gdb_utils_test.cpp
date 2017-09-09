//----------------------------------------------------------------------------
#include <stdlib.h> // wchar_t
#include <string.h>
#include <gdb_utils.h>
#include "gdb_utils_test.h"
//----------------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION(GdbUtilsTest);
//----------------------------------------------------------------------------

/*
	Test wstrrepl.
*/
void GdbUtilsTest::test1()
{
	size_t cnt = wstrrepl(0, L'a', L'b');
	CPPUNIT_ASSERT(!cnt);
}
//----------------------------------------------------------------------------

/*
	Test wstrrepl.
*/
void GdbUtilsTest::test2()
{
	wchar_t str[] = L"aAaAaA";
	size_t cnt = wstrrepl(str, L'a', L'A');
	CPPUNIT_ASSERT_EQUAL(3U, cnt);
	CPPUNIT_ASSERT(!wcscmp(L"AAAAAA", str));
}
//----------------------------------------------------------------------------

/*
	Test wstrrepl.
*/
void GdbUtilsTest::test3()
{
	wchar_t str[] = L"123";
	size_t cnt = wstrrepl(str, L'\0', L'4');
	CPPUNIT_ASSERT(!cnt);
	CPPUNIT_ASSERT(!wcscmp(L"123", str));
}
//----------------------------------------------------------------------------

/*
	Test wstrrepl.
*/
void GdbUtilsTest::test4()
{
	wchar_t str[] = L"123";
	size_t cnt = wstrrepl(str, L'1', L'\0');
	CPPUNIT_ASSERT_EQUAL(1U, cnt);
	CPPUNIT_ASSERT(!wcslen(str));
}
//----------------------------------------------------------------------------
