#include "remove_warning_test.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "runtime.h"

extern "C" Object do_setf_aref(Object, SI_Dimension, Object);
extern "C" Object SI_fill_primitive_vector(Object, Object);
extern "C" Object SI_malloc_primitive_vector(SI_Dimension ,enum SI_gcls etype);
extern "C" Object make_malloced_array(long);
extern "C" Object do_aref_1(Object, long);
extern "C" long integer_to_long(Object);
extern "C" bignum_type bignum_quotient(bignum_type, bignum_type);
extern "C" Object long_to_bignum(long);
extern "C" long bignum_to_long(Object);
extern "C" bignum_type bignum_remainder(bignum_type, bignum_type);
extern "C" Object clong_to_bignum(long);
extern "C" enum bignum_comparison SI_bignum_compare_s(Object, Object);
extern "C" unsigned long SI_next_prime(unsigned long);
extern "C" void SI_INIT_new_bignums();
extern "C" Object ltimes(Object, Object);
extern "C" Object sub1(Object);
extern "C" SI_int64 integer_to_int64(Object);
extern "C" Object cint64_to_int64(SI_int64);
extern "C" Object negate(Object);

CPPUNIT_TEST_SUITE_REGISTRATION(TestRemoveWarning);

void TestRemoveWarning::setUp()
{
    SI_INIT_new_bignums();
}

void TestRemoveWarning::tearDown()
{

}

//SI_long_to_bignum_s and SI_bignum_compare_s test
void TestRemoveWarning::Test1()
{	
	Object x;
	// enum bignum_comparison result;

	x = clong_to_bignum(55);
	CPPUNIT_ASSERT(x != Nil);
}

//bignum_quotient test
void TestRemoveWarning::Test2()
{	
	Object x, y, result;	
	long nval = 0;

	x = long_to_bignum(55);
	y = long_to_bignum(39);
	result = bignum_quotient(x,y);
	nval = bignum_to_long(result);
	CPPUNIT_ASSERT(nval == 1);

	x = long_to_bignum(296);
	y = long_to_bignum(41);
	result = bignum_quotient(x,y);
	nval = bignum_to_long(result);
	CPPUNIT_ASSERT(nval == 7);
}

//bignum_remainder test
void TestRemoveWarning::Test3()
{	
	Object x, y, result;	
	long nval = 0;

	x = long_to_bignum(55);
	y = long_to_bignum(39);
	result = bignum_remainder(x,y);
	nval = bignum_to_long(result);
	CPPUNIT_ASSERT(nval == 16);

	x = long_to_bignum(296);
	y = long_to_bignum(41);
	result = bignum_remainder(x,y);
	nval = bignum_to_long(result);
	CPPUNIT_ASSERT(nval == 9);
}

//do_setf_aref test
void TestRemoveWarning::Test4()
{	
	Object x,y,result;
	
	result = make_malloced_array(6); //A_UNSIGNED_BYTE_16
	x = FIX(32);
	y = do_setf_aref(result, (SI_Dimension)2, x);
	CPPUNIT_ASSERT(y == x);

    Object arr = NULL;
    enum SI_etype etype = A_BYTE_8;    
    arr = SI_malloc_primitive_vector((long)8, etype);
	SI_fill_primitive_vector(arr, (Object)ZERO);
	x = FIX(128);
	y = do_setf_aref(arr, (SI_Dimension)0, x);
	CPPUNIT_ASSERT(y == x);

    etype = A_BYTE_16;    
    arr = SI_malloc_primitive_vector((long)8, etype);
	SI_fill_primitive_vector(arr, (Object)ZERO);
	x = FIX(63000);
	y = do_setf_aref(arr, (SI_Dimension)0, x);
	CPPUNIT_ASSERT(y == x);
}

//do_aref_1 test
void TestRemoveWarning::Test5()
{
	Object x,y;
	Object arr = NULL;
    enum SI_etype etype = A_BYTE_32;   

    arr = SI_malloc_primitive_vector((long)8, etype);
	SI_fill_primitive_vector(arr, (Object)ZERO);
	long lval = 76000;
	x = FIX(lval);
	do_setf_aref(arr, (SI_Dimension)0, x);
	y = do_aref_1(arr, 0);
	CPPUNIT_ASSERT(IINTEGER(y) == lval);
}

//ltimes test
void TestRemoveWarning::Test6()
{	
	unsigned long nVal = 0;

	nVal = SI_next_prime(12);
	CPPUNIT_ASSERT(nVal == 13);

	nVal = SI_next_prime(20);
	CPPUNIT_ASSERT(nVal == 23);
}

// create most-positive-int64 test
void TestRemoveWarning::Test7()
{
    Object temp1 = ltimes(FIX((SI_Long)2097152L),FIX((SI_Long)2097152L));
    Object temp2 = ltimes(FIX((SI_Long)2097152L),temp1);
    Object integer = sub1(temp2);
    SI_int64 long_1 = INTEGER_TO_INT64(integer);
    CPPUNIT_ASSERT(long_1 == (SI_int64)9223372036854775807L);

    Object Most_positive_int64 = INT64_TO_INTEGER(long_1);
    Object temp3 = negate(Most_positive_int64);
    Object Most_negative_int64 = sub1(temp3);
    SI_int64 long_2 = INTEGER_TO_INT64(Most_negative_int64);
    CPPUNIT_ASSERT(long_2 == (SI_int64)-9223372036854775808L);
}
