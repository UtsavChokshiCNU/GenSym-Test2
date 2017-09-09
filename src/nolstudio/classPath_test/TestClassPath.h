// TestClassPath.h: interface for the CTestClassPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCLASSPATH_H__2807B19B_4FF1_4A21_BA6C_9C867EDEE892__INCLUDED_)
#define AFX_TESTCLASSPATH_H__2807B19B_4FF1_4A21_BA6C_9C867EDEE892__INCLUDED_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestClassPath:public CPPUNIT_NS::TestFixture    
{

	CPPUNIT_TEST_SUITE(CTestClassPath);
	CPPUNIT_TEST(test_getJVM);
	CPPUNIT_TEST_SUITE_END();


public:
	CTestClassPath();
	virtual ~CTestClassPath();
	void test_getJVM();

};

#endif // !defined(AFX_TESTCLASSPATH_H__2807B19B_4FF1_4A21_BA6C_9C867EDEE892__INCLUDED_)







