
#include "stdafx.h"

#include "Int64SupportTest.h"



CPPUNIT_TEST_SUITE_REGISTRATION(Int64SupportTest);

void Int64SupportTest::setUp() 
{
	i1 = 987659876588876876;
	i2 = -896346821916798539;
	u1 = 7519875715705723576;
	u2 = 9283752757287675783;
}

void Int64SupportTest::tearDown()
{
	g2int_reclaim_int64_structure(v1);
	g2int_reclaim_int64_structure(v2);
}

void Int64SupportTest::testSignedInt64Conversion () {
	v1 = convert_int64t_to_int64struct(i1);
	ri1 = convert_int64struct_to_int64(v1);
	CPPUNIT_ASSERT(i1 == ri1);
	v2 = convert_int64t_to_int64struct(i2);
	ri2 = convert_int64struct_to_int64(v2);
	CPPUNIT_ASSERT(i2 == ri2);
}

void Int64SupportTest::testUnsignedInt64Conversion() {
	v1 = convert_uint64t_to_int64struct(u1);
	ru1 = convert_int64struct_to_uint64(v1);
	CPPUNIT_ASSERT(u1 == ru1);
	v2 = convert_uint64t_to_int64struct(u2);
	ru2 = convert_int64struct_to_uint64(v2);
	CPPUNIT_ASSERT(u2 == ru2);
}




