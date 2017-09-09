
#ifndef _DELETE_SYMBOL_TEST_INCLUDED_H_
#define _DELETE_SYMBOL_TEST_INCLUDED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestDeleteSymbol : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestDeleteSymbol);
		//CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	TestDeleteSymbol() {}
	virtual ~TestDeleteSymbol() {}

private:
	void Test();
};

#endif // ifndef _DELETE_SYMBOL_TEST_INCLUDED_H_
