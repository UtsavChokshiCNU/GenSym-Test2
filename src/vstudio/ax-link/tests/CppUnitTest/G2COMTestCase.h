// G2COMTestCase.h: interface and implementation of the CG2COMTestCase class.
//
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <atlbase.h>
#include "CppUnitTestDlg.h"

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>


class CG2COMTestCase : 
	public CppUnit::TestCase
{
public:
	CG2COMTestCase()
	{

	}
	virtual ~CG2COMTestCase()
	{

	}
public:
	
	CPPUNIT_TEST_SUITE(CG2COMTestCase);
		CPPUNIT_TEST(connectTest);
		CPPUNIT_TEST(disconnectTest);
		CPPUNIT_TEST(postMessageTest);
		CPPUNIT_TEST(callTest);
		CPPUNIT_TEST(callDeferredTest);
		CPPUNIT_TEST(startTest);
	CPPUNIT_TEST_SUITE_END();

public:
	CCppUnitTestDlg* pObj;
	void setUp()
	{
		pObj = new CCppUnitTestDlg();
		pObj->Create(IDD_CPPUNITTEST_DIALOG);
		pObj->ShowWindow(SW_HIDE);
	}
	void tearDown()
	{
		pObj->DestroyWindow();
		delete pObj;
	}

public:
	void connectTest()
	{
		/*
		We check to make sure that a successful connection causes 
		two events (Connected and RunStateKnown), and changes state of G2COM Gateway from
		Not Connected to Connected
		*/
		CPPUNIT_ASSERT(pObj!=NULL);
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==FALSE);
		CPPUNIT_ASSERT(pObj->Connect()==TRUE);
		CPPUNIT_ASSERT(pObj->m_bConnectedEventFired==TRUE);
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Running()==TRUE);
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==TRUE);
		CCppUnitTestDlg::WaitUntilTRUE(&pObj->m_bRunStateKnownEventFired,1000);
		CPPUNIT_ASSERT(pObj->m_bRunStateKnownEventFired==TRUE);
		pObj->Disconnect();
	}

	void disconnectTest()
	{
		/*
		We check to make sure the Disconnect method causes that state of G2COM Gateway changes
		from Connected to Not Connected, and fires the event Disconnected
		*/
		CPPUNIT_ASSERT(pObj!=NULL);
		pObj->Connect();
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==TRUE);
		CPPUNIT_ASSERT(pObj->Disconnect()==TRUE);
		CPPUNIT_ASSERT(pObj->m_bDisconnectedEventFired==TRUE);
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==FALSE);
	}

	void postMessageTest()
	{
		/*
		We check to make sure the PostMessage method works fine - don't cause any errors
		*/

		CPPUNIT_ASSERT(pObj!=NULL);
		pObj->Connect();
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==TRUE);
		CPPUNIT_ASSERT(pObj->PostMessage()==TRUE);		
		pObj->Disconnect();
		
	}

	void callTest()
	{
		/*
		We check to make sure that the Call method works fine,
		- don't cause any errors
		*/
		CPPUNIT_ASSERT(pObj!=NULL);
		pObj->Connect();
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==TRUE);
		CPPUNIT_ASSERT(pObj->Call()==TRUE);
		pObj->Disconnect();
	}

	void callDeferredTest()
	{
		/*
		We check to make sure that the CallDeferred method works fine,
		- it causes the event RpcReturned, and no errors
		*/
		CPPUNIT_ASSERT(pObj!=NULL);
		pObj->Connect();
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==TRUE);
		CPPUNIT_ASSERT(pObj->CallDeferred()==TRUE);
		CCppUnitTestDlg::WaitUntilTRUE(&pObj->m_bRpcReturnedEventFired,1000);
		pObj->Disconnect();
	}

	void startTest()
	{
		/*
		We check to make sure that the start method works fine,
		- it causes the event RpcReturned, and no errors
		*/

		CPPUNIT_ASSERT(pObj!=NULL);
		pObj->Connect();
		CPPUNIT_ASSERT(pObj->m_g2g.GetIsG2Connected()==TRUE);
		CPPUNIT_ASSERT(pObj->Start()==TRUE);
		CCppUnitTestDlg::WaitUntilTRUE(&pObj->m_bRpcReturnedEventFired,1000);
		pObj->Disconnect();

	}
};
