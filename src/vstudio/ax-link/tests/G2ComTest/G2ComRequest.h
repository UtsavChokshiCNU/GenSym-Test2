#ifndef _G2COMREQUEST_H_
#define _G2COMREQUEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Class that contains tests for Connect(VARIANT_BOOL bWaitflag,long* pReVal)
 * functions of Gateway.cpp file of G2Com.
 */

class G2ComRequestTestCase : public CppUnit::TestCase 
{
public:
	G2ComRequestTestCase();
	virtual ~G2ComRequestTestCase();

	CPPUNIT_TEST_SUITE(G2ComRequestTestCase);
		CPPUNIT_TEST(RequestLenTest);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();	

	//  Tests Connect(VARIANT_BOOL bWaitflag,long* pReVal) function
	void RequestLenTest();
private:
};

#endif
