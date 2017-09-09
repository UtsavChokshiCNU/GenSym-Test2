#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "cprim.h"
extern void 		g2ext_initialize_g2pointers();
extern Cpointer		g2ext_map_g2pointer_to_cpointer(G2pointer g2pointer);
extern G2pointer	g2ext_cache_cpointer(Cpointer cpointer);
extern void 		g2ext_decache_g2pointer(G2pointer g2pointer);
}

class G2ptrsTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(G2ptrsTest);
	CPPUNIT_TEST(test_g2ext_g2pointers_caching_decaching);
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
	void tearDown();
	void test_g2ext_g2pointers_caching_decaching();
};






 