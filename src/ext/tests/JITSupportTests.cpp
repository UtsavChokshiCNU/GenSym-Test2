#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "jit_support.h"
// object.h must go after winnt.h not to have 
// "C:\Program Files\Microsoft SDKs\Windows\v6.0A\include\winnt.h(963) 
// : error C2143: syntax error : missing ',' before 'constant'"
// This is because object.h defines T which is used as a parameter in templates
#include "config.h"
#include "object.h"

class JITSupportTests: public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE(JITSupportTests);
	CPPUNIT_TEST(test_g2ext_jit_get_sym_val_addr);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_g2ext_jit_get_sym_val_addr() {
		int addr = 0;
		SI_Cons cons1, cons2, cons3, cons4;
		cons1.car = (Object) &cons2;
		cons2.cdr = (Object) &cons3;
		cons3.car = (Object) &cons4;
		cons4.car = (Object) &addr;
		CPPUNIT_ASSERT_EQUAL(reinterpret_cast<void*>(&addr),
			g2ext_jit_get_sym_val_addr(&cons1));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(JITSupportTests);
