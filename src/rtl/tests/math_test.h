
#ifndef _MATH_TEST_INCLUDED_H_
#define _MATH_TEST_INCLUDED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestMath : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestMath);
		CPPUNIT_TEST(Test1);
		CPPUNIT_TEST(Test2);
		CPPUNIT_TEST(Test3);
		CPPUNIT_TEST(Test4);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	TestMath() {}
	virtual ~TestMath() {}

private:
	void Test1();
	void Test2();
	void Test3();
	void Test4();
};

#endif // ifndef _MATH_TEST_INCLUDED_H_
