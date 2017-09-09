#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {

extern char *g2ext_dtoa(double d, int mode, int ndigits, int *decpt, int *sign, char **rve);		
extern double strtod(const char *s00, char **se);
extern void g2ext_freedtoa(char *s);

}

class DtoaTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(DtoaTest);
	CPPUNIT_TEST(test_strtod);
	CPPUNIT_TEST(test_g2ext_dtoa);	
	CPPUNIT_TEST(test_reversibility);	
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
	void tearDown();
	void test_strtod();
	void test_g2ext_dtoa();	
	void test_reversibility();	
};
