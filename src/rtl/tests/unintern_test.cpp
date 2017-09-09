#include "unintern_test.h"

#define USE_PROTOTYPES
#include <windows.h>
#include "config.h"
#include "librtl.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




extern "C" Object iintern (char*, Object);
extern "C" Object unintern (Object, Object);
extern "C" Object ifind_symbol (char*, Object);
extern "C" Object g2_region_memory_usage(Object);
 


extern "C" Object Package;

CPPUNIT_TEST_SUITE_REGISTRATION(TestUninternSymbol);

void TestUninternSymbol::setUp()
{
}

void TestUninternSymbol::tearDown()
{
}

bool make_random_string(char* buffer, int length)
{
	if (IsBadWritePtr(buffer, length+1))
		return false;

	srand(time(0));   

	int char_length = length/2 + 1;
	int i = 0;

	for(i=0; i<char_length; ++i)
		buffer[i] = rand() % 26 + 65;
	for (i=char_length; i<length; ++i)
		buffer[i] = (rand() % 9) + 48;
	buffer[length] = '\0';

	return true;
}

/* This test should not depend on g2_region_memory_usage, thus commenting for
   the time being
*/
void TestUninternSymbol::Test1()
{
	Object res1, res2, res3, res4;
	SI_Long mem_region1_start, mem_region2_start, mem_region1_end, mem_region2_end;
	char buffer[50];

	make_random_string(buffer, 10);
	res1 = iintern(buffer, Package);

	make_random_string(buffer, 15);
	res2 = iintern(buffer, Package);

	make_random_string(buffer, 20);
	res3 = iintern(buffer, Package);

	make_random_string(buffer, 25);
	res4 = iintern(buffer, Package);

	unintern(res1, Package);
	unintern(res2, Package);
	unintern(res3, Package);
	unintern(res4, Package);

	mem_region1_start = IFIX(g2_region_memory_usage(FIX(1)));
	mem_region2_start = IFIX(g2_region_memory_usage(FIX(2)));

	for (int i=0; i < 1000; ++i)
	{
		make_random_string(buffer, 10);
		res1 = iintern(buffer, Package);

		make_random_string(buffer, 15);
		res2 = iintern(buffer, Package);

		make_random_string(buffer, 20);
		res3 = iintern(buffer, Package);

		make_random_string(buffer, 25);
		res4 = iintern(buffer, Package);

		unintern(res1, Package);
		unintern(res2, Package);
		unintern(res3, Package);
		unintern(res4, Package);
	}

	mem_region1_end = IFIX(g2_region_memory_usage(FIX(1)));
	mem_region2_end = IFIX(g2_region_memory_usage(FIX(2)));

	if (mem_region2_end - mem_region2_start > 0)
		CPPUNIT_ASSERT_MESSAGE("TestUninternSymbol::Test1 ERROR: Memory leak in Region 2", 0);

	if (mem_region1_end - mem_region1_start > 0)
		CPPUNIT_ASSERT_MESSAGE("TestUninternSymbol::Test1 ERROR: Memory leak in Region 1", 0);
}


void TestUninternSymbol::Test2()
{
	Object symbol;
	char* name = "abc123";
	symbol = iintern(name, Package);
	if (!TRUEP(unintern(symbol, Package)) || TRUEP(ifind_symbol(name, Package)))
		CPPUNIT_ASSERT_MESSAGE("TestUninternSymbol::Test2 ERROR: Can not unintern symbol", 0);
}

void TestUninternSymbol::Test3()
{
	Object symbol1, symbol2;
	char* name = "abc123";
	symbol1 = iintern(name, Package);
	symbol2 = iintern(name, Package);

	unintern(symbol1, Package);

	if (TRUEP(ifind_symbol(name, Package)))
		CPPUNIT_ASSERT_MESSAGE("TestUninternSymbol::Test3 ERROR: Symbol should be unintern", 0);
}
