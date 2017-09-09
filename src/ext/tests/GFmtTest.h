#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

//adding module interface here as there is no dedicated header file in code base
//function name is g_fmt, but renamed to g2ext_g_fmt in Dtoa.h using preprocess macro
extern "C" {
extern char *g2ext_g_fmt(char * b, double x);
}

class GFmtTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(GFmtTest);
	CPPUNIT_TEST(test_g_fmt_common);
	CPPUNIT_TEST(test_g_fmt_limits);
	CPPUNIT_TEST(test_g_fmt_infinityAndNaN);
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
	void tearDown();
	void test_g_fmt_common();
	void test_g_fmt_limits();
	void test_g_fmt_infinityAndNaN();
};
