#include "integer_length_test.h"

//#define USE_PROTOTYPES
//#define SI_RUNTIME_INTERNAL
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "runtime.h"

extern "C" Object integer_length(Object);

CPPUNIT_TEST_SUITE_REGISTRATION(TestIntegerLength);

void TestIntegerLength::setUp()
{
}

void TestIntegerLength::tearDown()
{
}


void TestIntegerLength::Test()
{
	long i;
	long j = 1;
	Object len;

	for (i = 0; i < 29; i++) {
		len = integer_length(FIX(j));
		j *= 2;
		CPPUNIT_ASSERT(IFIX(len) == (i + 1));
	}

	CPPUNIT_ASSERT(true);


}
