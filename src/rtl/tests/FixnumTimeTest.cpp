#include "FixnumTimeTest.h"

#include <windows.h>

#define USE_PROTOTYPES
#define SI_RUNTIME_INTERNAL
#include "config.h"
#include "librtl.h"
#include "object.h"
#include "instance.h"
#include "ltime.h"

extern "C" Object get_internal_real_time();

CPPUNIT_TEST_SUITE_REGISTRATION(FixnumTimeTest);

unsigned long constant_time = 0L;
unsigned long __stdcall return_constant_time() {return constant_time;}


FixnumTimeTest::FixnumTimeTest() {
	g_real_time_provider = &return_constant_time;
	this->initial_time = IFIX(get_internal_real_time());
}


void FixnumTimeTest::setUp() {
}


void FixnumTimeTest::tearDown() {
}

void FixnumTimeTest::TestGetInternalRealTimeInitialValue() {
	CPPUNIT_ASSERT_EQUAL(0UL, this->initial_time);
}


void FixnumTimeTest::TestGetInternalRealTimeCommonValue() {
	Object fixnum_time;

	g_real_time_base_value = 1000L;
	constant_time = 3135L;
	fixnum_time = get_internal_real_time();
	CPPUNIT_ASSERT_EQUAL(static_cast<SI_Long>(2135), IFIX(fixnum_time));
}

void FixnumTimeTest::TestGetInternalRealTimeRollback() {
	Object fixnum_time;

	g_real_time_base_value = 100L;
	constant_time = 0xFFFFFFF0;
	fixnum_time = get_internal_real_time();
	SI_Long fixnum = IFIX(fixnum_time);
#ifdef Platform_32bit
	CPPUNIT_ASSERT_EQUAL(
	    static_cast<SI_Long>(0x1FFFFF8C), 
		fixnum); //win32
#else
	CPPUNIT_ASSERT_EQUAL(
	    static_cast<SI_Long>(0xFFFFFF8C), 
		fixnum); //win32
#endif
}
