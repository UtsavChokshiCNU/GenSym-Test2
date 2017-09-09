#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


#include "..\..\gsi\c\gsi_main.h"

#include "config.h"
#include "object.h"

extern "C" Object convert_int64t_to_int64struct(int64_t x);
extern "C" Object convert_uint64t_to_int64struct(uint64_t x);
extern "C" int64_t convert_int64struct_to_int64(Object x);
extern "C" uint64_t convert_int64struct_to_uint64(Object x);
extern "C" Object g2int_reclaim_int64_structure(Object x);



/*
 * Class that contains tests for the int64_support.c file of GSI.
 */

class Int64SupportTest:public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(Int64SupportTest);
        CPPUNIT_TEST(testSignedInt64Conversion);
		CPPUNIT_TEST(testUnsignedInt64Conversion);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual void setUp();
    virtual void tearDown();
    Int64SupportTest() {}
    virtual ~Int64SupportTest() {}

    void testSignedInt64Conversion();
	void testUnsignedInt64Conversion();
private:
	Object v1, v2;
	int64_t i1, i2, ri1, ri2;
	uint64_t u1, u2, ru1, ru2;
};




