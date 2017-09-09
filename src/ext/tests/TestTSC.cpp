
#include "TestTSC.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTSC);

#ifndef USE_PROTOTYPES

	#define USE_PROTOTYPES

#endif

extern "C" {
	unsigned long g2ext_get_new_tick_cell_index();
	long g2ext_get_cpu_ticks_count();
	long g2ext_get_tsc_difference(long cell_index_1, long cell_index_2);
}

void TestTSC::setUp() {

}

void TestTSC::testCellIndex() {
	unsigned long index;
	unsigned long prev_index = 8;
	for(int i = 0; i < 100; i++) {
		index = g2ext_get_new_tick_cell_index();
		CPPUNIT_ASSERT(index >= 0);
		CPPUNIT_ASSERT(index < 5);
		CPPUNIT_ASSERT(index != prev_index);
		prev_index = index;
	}
}

void TestTSC::testTSCHandling() {
#if _WIN32
	long index1, index2, diff;
	index1 = g2ext_get_cpu_ticks_count();
	index2 = g2ext_get_cpu_ticks_count();
	CPPUNIT_ASSERT(index1 != index2);
	diff = abs(g2ext_get_tsc_difference(index1, index2));
	CPPUNIT_ASSERT(diff > 10L);
#endif
}

void TestTSC::tearDown() {

}
