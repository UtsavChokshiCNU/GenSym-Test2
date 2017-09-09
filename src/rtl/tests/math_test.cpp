#include "math_test.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "runtime.h"


extern "C" Object ltimes(Object, Object);
extern "C" Object cdouble_to_double(double);
extern "C" double object_to_cdouble(Object);
extern "C" Object get_internal_real_time();
extern "C" Object zerop(Object);
extern "C" Object plusp(Object);
extern "C" Object logand(Object, Object);



extern "C" Object Package;

CPPUNIT_TEST_SUITE_REGISTRATION(TestMath);

void TestMath::setUp()
{
	
}

void TestMath::tearDown()
{

}

//ltimes test
void TestMath::Test1()
{	
	Object result;

	//FIXNUMS
	Object zero_arg = FIX(0);
	Object positive_arg = FIX(12345);
	Object negative_arg = FIX(-12345);
	
	//  zero * zero
	result = ltimes(zero_arg, zero_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 0L);

	// pos * zero
	result = ltimes(positive_arg, zero_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 0L);


	// zero * pos
	result = ltimes(zero_arg, positive_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 0L);

	// neg * zero
	result = ltimes(negative_arg, zero_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 0L);


	// zero * neg
	result = ltimes(zero_arg, negative_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 0L);


	// pos * pos
	result = ltimes(positive_arg, positive_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 152399025L);

	// neg * neg
	result = ltimes(negative_arg, negative_arg); 
	CPPUNIT_ASSERT(IFIX(result) == 152399025L);

	// neg * pos 
	result = ltimes(negative_arg, positive_arg); 
	CPPUNIT_ASSERT(IFIX(result) == -152399025L);
	
	// pos * neg
	result = ltimes(positive_arg, negative_arg); 
	CPPUNIT_ASSERT(IFIX(result) == -152399025L);


	//DOUBLES
	Object zero_double = cdouble_to_double(0.0);
	Object positive_double = cdouble_to_double(123.45);
	Object negative_double = cdouble_to_double(-123.45);
	
	//  zero * zero
	result = ltimes(zero_double, zero_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 0.0);

	// pos * zero
	result = ltimes(positive_double, zero_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 0.0);


	// zero * pos
	result = ltimes(zero_double, positive_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 0.0);

	// neg * zero
	result = ltimes(negative_double, zero_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 0.0);


	// zero * neg
	result = ltimes(zero_double, negative_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 0.0);


	// pos * pos
	result = ltimes(positive_double, positive_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 15239.9025);

	// neg * neg
	result = ltimes(negative_double, negative_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 15239.9025);

	// neg * pos 
	result = ltimes(negative_double, positive_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == -15239.9025);
	
	// pos * neg
	result = ltimes(positive_double, negative_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == -15239.9025);
	
	//FIXNUMS vs DOUBLES

	// pos_fixnum * pos_double
	result = ltimes(positive_arg, positive_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 1523990.25);
	
	// pos_double * pos_fixnum
	result = ltimes(positive_double, positive_arg); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 1523990.25);

	// neg_fixnum * neg_double
	result = ltimes(negative_arg, negative_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 1523990.25);
	
	// neg_double * neg_fixnum
	result = ltimes(negative_double, negative_arg); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == 1523990.25);

	// neg_fixnum * pos_double
	result = ltimes(negative_arg, positive_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == -1523990.25);
	
	// pos_double * neg_fixnum
	result = ltimes(positive_double, negative_arg); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == -1523990.25);

	// pos_fixnum * neg_double
	result = ltimes(positive_arg, negative_double); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == -1523990.25);
	
	// neg_double * pos_fixnum
	result = ltimes(negative_double, positive_arg); 
	CPPUNIT_ASSERT(object_to_cdouble(result) == -1523990.25);
}

//get_internal_real_time test
void TestMath::Test2()
{
	Object result;
	Object prev_result = get_internal_real_time();
	int i;
	for (i = 0; i < 10000; i++) {
		result = get_internal_real_time();
		CPPUNIT_ASSERT(IFIX(result) >= IFIX(prev_result));
		prev_result = result;
	}
}

//zerop and plusp test
void TestMath::Test3()
{
	Object result;
	Object zero_fixnum = FIX(0L);
	Object zero_double = cdouble_to_double(0.0);
	
	result = zerop(zero_fixnum);
	CPPUNIT_ASSERT(!EQ(result, Nil));
	
	result = zerop(zero_double);
	CPPUNIT_ASSERT(!EQ(result, Nil));

	Object positive_arg = FIX(12345);
	Object negative_arg = FIX(-12345);
	
	result = plusp(positive_arg);
	CPPUNIT_ASSERT(!EQ(result, Nil));

	result = plusp(negative_arg);
	CPPUNIT_ASSERT(EQ(result, Nil));

	Object positive_double = cdouble_to_double(123.45);
	Object negative_double = cdouble_to_double(-123.45);

	result = plusp(positive_double);
	CPPUNIT_ASSERT(!EQ(result, Nil));

	result = plusp(negative_double);
	CPPUNIT_ASSERT(EQ(result, Nil));

}

//logand
void TestMath::Test4()
{
	Object result;
	Object zero_fixnum = FIX(0L);
	Object fixnum = FIX(255L);
	
	result = logand(zero_fixnum, fixnum);
	CPPUNIT_ASSERT(IFIX(result) == 0L);

	result = logand(fixnum, zero_fixnum);
	CPPUNIT_ASSERT(IFIX(result) == 0L);
	
	Object fixnum1 = FIX(2863311530L); //10101010101010101010101010101010
	Object fixnum2 = FIX(1431655765L); //01010101010101010101010101010101

	result = logand(fixnum1, fixnum2);
	CPPUNIT_ASSERT(IFIX(result) == 0L);

	result = logand(fixnum2, fixnum1);
	CPPUNIT_ASSERT(IFIX(result) == 0L);

	result = logand(FIX(53687091L), FIX(53687091L));
	CPPUNIT_ASSERT(IFIX(result) == 53687091L);
	
}
