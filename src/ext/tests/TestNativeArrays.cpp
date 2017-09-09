#include "TestNativeArrays.h"
#include "g2gpubridge.h"

void CTestNativeArrays::setUp () {

}

void CTestNativeArrays::tearDown() {

}

void CTestNativeArrays::testIntegerArrays() {
#ifdef PACKAGING_G2_ENTERPRISE
	int i,j;
	int handle = 0;
	for(j = 0; j < 50; j++) {
		for (i = 0; i < 1024; i++) {
			handle = g2ext_alloc_native_int_array(8192);
			CPPUNIT_ASSERT(handle != 0);
			g2ext_free_native_int_array(handle);
		}
	}
	handle = g2ext_alloc_native_int_array(8192);
	for (i = 0; i < 8192; i++) {
		g2ext_set_native_int_at(handle, i, i*i);
	}
	for (i = 0; i < 8192; i++) {
		j = g2ext_get_native_int_at(handle, i);
		CPPUNIT_ASSERT(j == i*i);
	}
	g2ext_free_native_int_array(handle);
#else
	CPPUNIT_ASSERT_EQUAL(0, g2ext_alloc_native_int_array(8192));
#endif
}

void CTestNativeArrays::testFloatArrays() {
#ifdef PACKAGING_G2_ENTERPRISE
	int i,j;
	double v;
	int handle = 0;
	for(j = 0; j < 1; j++) {
		for (i = 0; i < 1024; i++) {
			handle = g2ext_alloc_native_float_array(8192);
			CPPUNIT_ASSERT(handle != 0);
			g2ext_free_native_float_array(handle);
		}
	}
	handle = g2ext_alloc_native_float_array(8192);
	for (i = 0; i < 8192; i++) {
		g2ext_set_native_float_at(handle, i, i/43.0);
	}
	for (i = 0; i < 8192; i++) {
		v = g2ext_get_native_float_at(handle, i);
		CPPUNIT_ASSERT(v == i/43.0);
	}
	g2ext_free_native_float_array(handle);
#else
	CPPUNIT_ASSERT_EQUAL(0, g2ext_alloc_native_float_array(8192));
#endif
}

CPPUNIT_TEST_SUITE_REGISTRATION(CTestNativeArrays);