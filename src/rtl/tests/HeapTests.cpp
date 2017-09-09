#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <setjmp.h>

#include "config.h"
#include "object.h"
#include "core.h"
#include "heap.h"

class HeapTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(HeapTests);
		CPPUNIT_TEST(testAllocateDimensionVector);
	CPPUNIT_TEST_SUITE_END();

public:
	void testAllocateDimensionVector() {
		g2rtl_init_heaps();
		
		SI_PVT_Dimension* array
				= (SI_PVT_Dimension*) g2rtl_SI_alloc_primitive_vector(2,
						SI_DIMENSION_ETYPE);
		array->contents[0] = 1;
		array->contents[1] = 2;
		
		SI_PVT_Dimension* array2
				= (SI_PVT_Dimension*) g2rtl_SI_alloc_primitive_vector(2,
						SI_DIMENSION_ETYPE);
		
		CPPUNIT_ASSERT_EQUAL((SI_Dimension) 1, array->contents[0]);
		CPPUNIT_ASSERT_EQUAL((SI_Dimension) 2, array->contents[1]);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(HeapTests);

