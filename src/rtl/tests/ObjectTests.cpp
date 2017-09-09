#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <setjmp.h>

#include "config.h"
#include "object.h"

class ObjectTests: public CPPUNIT_NS::TestFixture {

	CPPUNIT_TEST_SUITE(ObjectTests);
		CPPUNIT_TEST(testSI_Double_float_size);
		CPPUNIT_TEST(testSI_PVT_Dimension_size);
	CPPUNIT_TEST_SUITE_END();

public:
	void testSI_PVT_Dimension_size() {
		SI_PVT_Long longVector;
		SI_PVT_Dimension dimensionVector;
		size_t size1 = sizeof(dimensionVector.contents);
		size_t size2 = sizeof(longVector.contents);
		// according to object.h, SI_Dimention is always 32-bit (length: 4)
		CPPUNIT_ASSERT(!(size2 % size1));
	}

	void testSI_Double_float_size() {
		CPPUNIT_ASSERT(!(sizeof(SI_Double_float) % sizeof(Object)));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ObjectTests);

