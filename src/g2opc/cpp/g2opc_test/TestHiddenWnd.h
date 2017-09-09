// TestHiddenWnd.h: interface for the CTestHiddenWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTHIDDENWND_H__D976EE2E_20D6_41E1_9C29_44AFA984713F__INCLUDED_)
#define AFX_TESTHIDDENWND_H__D976EE2E_20D6_41E1_9C29_44AFA984713F__INCLUDED_

#include "stdafx.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// CWndRunner class forward declaration
class CWndRunner;

//////////////////////////////////////////////////////////////////////
// CTestHiddenWnd class
// 
//	Test class that is used to test added functionality into
// CG2OpcHiddenWin class:
//
//	* WM_DESTROY message handler OnDestroy()
//		This functionality is tested using both send WM_DESTROY window
//		message to hidden window and call directly OnDestroy()
//		using helper class.
//////////////////////////////////////////////////////////////////////
class CTestHiddenWnd : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CTestHiddenWnd);
	CPPUNIT_TEST(testOnDestroy);
	CPPUNIT_TEST(testOnDestroyMessage);
	CPPUNIT_TEST_SUITE_END();

public:
	CTestHiddenWnd();
	virtual ~CTestHiddenWnd();

	// Set up test data
	virtual void setUp();

	// Free test data
	virtual void tearDown();

	// Test WM_DESTROY message handler calling OnDestroy()
	void testOnDestroy();

	// Test WM_DESTROY message handler sending WM_DESTROY message
	void testOnDestroyMessage();

protected:
	CWndRunner* m_pRunner;
};

#endif // !defined(AFX_TESTHIDDENWND_H__D976EE2E_20D6_41E1_9C29_44AFA984713F__INCLUDED_)
