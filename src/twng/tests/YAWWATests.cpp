#include "GoogleStyleTest.h"
#include "cppunit_assertion_trait_charp.hpp"

#include "YAWWA.hpp"

#include <string>


struct TestSIZE {
	int cx;
	int cy;
};

class NonProportionalExtents {
public:
	NonProportionalExtents(int width, int height) : d_width(width), d_height(height) {}
	bool operator()(wchar_t const* wcs, int len, TestSIZE *pSize) {
		pSize->cx = len * d_width;
		pSize->cy = d_height;
		return true;
	}
	int width() const { return d_width; }
	int height() const { return d_height; }

private:
	int d_width;
	int d_height;
};

template<typename T>
class PrintToString {
public:
	PrintToString(T &t) : d_t(t), d_call_count(0) {}
	void operator()(int cy, wchar_t const* wcs, int len) {
		CPPUNIT_ASSERT_EQUAL(d_t.height(), cy);
		d_ws.append(wcs, len);
		++d_call_count;
	}
	std::wstring string() const { 
		return d_ws;
	}
	size_t call_count() const {
		return d_call_count;
	}
	void reset() {
		d_ws.clear();
		d_call_count = 0;
	}
private:
	std::wstring d_ws;
	T &d_t;
	size_t d_call_count;
};


TEST(non_proportional_no_wrap)
{
	NonProportionalExtents meter(5, 7);
	wchar_t const *to_wrap = L"simple";
	PrintToString<NonProportionalExtents> printer(meter);
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), 1000, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(1U, printer.call_count());

	to_wrap = L"simple and then some";
	printer.reset();
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), 1000, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(1U, printer.call_count());
}


TEST(non_proportional_simple_wrap)
{
	NonProportionalExtents meter(5, 7);
	wchar_t const *to_wrap = L"simple and then-some";
	PrintToString<NonProportionalExtents> printer(meter);
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 11, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(3U, printer.call_count());

	printer.reset();
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 11 + 1, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(2U, printer.call_count());
}


TEST(non_proportional_simple_newline)
{
	NonProportionalExtents meter(5, 7);
	wchar_t const *to_wrap = L"simple and\nthen-some";
	PrintToString<NonProportionalExtents> printer(meter);
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), 1000, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(2U, printer.call_count());
}


TEST(non_proportional_simple_wrap_and_newline)
{
	NonProportionalExtents meter(5, 7);
	wchar_t const *to_wrap = L"simple and\n";
	PrintToString<NonProportionalExtents> printer(meter);
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 11, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(3U, printer.call_count());

	printer.reset();
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 11 + 1, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(2U, printer.call_count());
}


TEST(non_proportional_simple_longword)
{
	NonProportionalExtents meter(5, 7);
	wchar_t const *to_wrap = L"simple Supercalifragilisticexpialidocious";
	PrintToString<NonProportionalExtents> printer(meter);
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 30, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(2U, printer.call_count());

	printer.reset();
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 20, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(3U, printer.call_count());

	printer.reset();
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 11, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(5U, printer.call_count());

	printer.reset();
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), meter.width() * 11 + 1, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(4U, printer.call_count());
}


TEST(non_proportional_error_report)
{
	NonProportionalExtents meter(10, 11);
	wchar_t const* to_wrap = L"#13   2:20:49 p.m.   Error:\n\n"
L"No item named I0123456789I0123456789I0123456789I0123456789 exists.\n\n"
L"Operation: fetch I0123456789I0123456789I0123456789I0123456789\n"
L"Activity: conclude action\n"
L"Within: POPULATE-ARRAY(CHAR-ARRAY)\n"
L"Local Names:\n"
L"  CHARARRAY: class text-array = CHAR-ARRAY\n"
L"Aborting procedure stack from POPULATE-ARRAY(CHAR-ARRAY).";
	PrintToString<NonProportionalExtents> printer(meter);
	CPPUNIT_ASSERT_EQUAL(0, YAWWA<TestSIZE>(to_wrap, wcslen(to_wrap), 400, meter, printer));
	CPPUNIT_ASSERT_EQUAL(to_wrap, printer.string().c_str());
	CPPUNIT_ASSERT_EQUAL(14U, printer.call_count());
}