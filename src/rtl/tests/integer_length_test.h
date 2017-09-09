
#ifndef _INTEGER_LENGTH_TEST_INCLUDED_H_
#define _INTEGER_LENGTH_TEST_INCLUDED_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#define g2rtl_string string
#define g2rtl_get get


class TestIntegerLength : public CPPUNIT_NS::TestFixture  
{

    CPPUNIT_TEST_SUITE(TestIntegerLength);
		CPPUNIT_TEST(Test);
    CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();
	virtual ~TestIntegerLength() {}

private:
	void Test();
};

#endif // ifndef _INTEGER_LENGTH_TEST_INCLUDED_H_
