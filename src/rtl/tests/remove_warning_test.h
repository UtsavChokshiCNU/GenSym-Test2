
#ifndef _REMOVE_WARNING_TEST_INCLUDED_H_
#define _REMOVE_WARNING_TEST_INCLUDED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestRemoveWarning : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestRemoveWarning);
		CPPUNIT_TEST(Test1);
		CPPUNIT_TEST(Test2);
		CPPUNIT_TEST(Test3);
		CPPUNIT_TEST(Test4);
		CPPUNIT_TEST(Test5);
		CPPUNIT_TEST(Test6);
		CPPUNIT_TEST(Test7);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	TestRemoveWarning() {}
	virtual ~TestRemoveWarning() {}

private:
	void Test1();
	void Test2();
	void Test3();
	void Test4();
	void Test5();
	void Test6();
	void Test7();
};

#endif // ifndef _REMOVE_WARNING_TEST_INCLUDED_H_
