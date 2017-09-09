
#ifndef _UNINTERN_TEST_INCLUDED_H_
#define _UNINTERN_TEST_INCLUDED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestUninternSymbol : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestUninternSymbol);
		//CPPUNIT_TEST(Test1);
		//CPPUNIT_TEST(Test2);
		//CPPUNIT_TEST(Test3);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	TestUninternSymbol() {}
	virtual ~TestUninternSymbol() {}

private:
	void Test1();
	void Test2();
	void Test3();
};

#endif // ifndef _UNINTERN_TEST_INCLUDED_H_
