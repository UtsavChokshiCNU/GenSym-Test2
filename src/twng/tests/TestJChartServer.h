#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "JChartServer.h"
#include "JChartView.h"

class TestObj;

class TestJChartServer: public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(TestJChartServer);
  CPPUNIT_TEST(Test);
  CPPUNIT_TEST_SUITE_END();
  
public:
  void Test();
	
};

// Wrapper of JChartServer
class JTestServer: public JChartServer
{
public:
	JTestServer(int nPort, const char* szHost): JChartServer(nPort, szHost) {}
	friend class TestObj;

};

// Wrapper of G2JChartView
class JTestView: public G2JChartView
{
public:
	DECLARE_DYNCREATE(JTestView)
	JTestView(int handle = 0): G2JChartView(handle), flag(false) {}

	afx_msg void OnDestroy();

	friend class TestObj;

protected:
  DECLARE_MESSAGE_MAP()

protected:
	bool flag;

};

// This class tests G2JChartView, JChartServer, JMessageFactory, JClientMessage, 
// JClientEvent and JString class.
// The root of the testing is creating fake server which send chart event with "closed" id.
// "JChartServer" process this message by using factory, then "WM_DESTROY" will be sent 
// to the JTestView (child of the real JTestView).
class TestObj
{
public:
	TestObj(int handle, int port, const char* host);
	~TestObj();

	bool TestSend();
	bool RunServer();
	bool RunListener();
	bool TestGotMessage() const;

	int GetPort() const;
	int GetHandle() const;

	void Stop();
	void DoEvents();
	void Listen();

public:
	HANDLE hStarted1;		// Event for m_hServerThread thread, TRUE if started
	HANDLE hStopServer;		// Event for m_hServerThread thread, TRUE if need to stop server
	HANDLE hStarted2;		// Event for m_hListenThread thread, TRUE if started

protected:
	HANDLE m_hServerThread;
	HANDLE m_hListenThread;	

	JTestView* m_pJView;
	JTestServer m_Server;
};
