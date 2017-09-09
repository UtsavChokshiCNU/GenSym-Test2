#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
typedef long icp_int;
#define ICP_SUCCESS       1L
#define ICP_FAILURE       0L
extern icp_int allocate_blob(icp_int array_size, char **ptr_ptr);
extern icp_int reclaim_used_blobs();
}

class PoolsTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(PoolsTest);
	CPPUNIT_TEST(test_allocate_use);
	CPPUNIT_TEST(test_reclaim_use);
	CPPUNIT_TEST(test_allocate_load);
	CPPUNIT_TEST(test_allocate_limit);
	CPPUNIT_TEST_SUITE_END();

private:

public:
	void setUp();
	void tearDown();
	void test_allocate_use();
	void test_reclaim_use();
	void test_allocate_load();
	void test_allocate_limit();
};
 