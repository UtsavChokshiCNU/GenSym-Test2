
#include "stdafx.h"
#include "MainFrm.h"
#include "TestJChartServer.h"
#include "JString.h"

#include <winsock2.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestJChartServer);


// -------+++++++------- TestJChartServer class -------+++++++------- //
void TestJChartServer::Test()
{	
	int firstFreePort = GetFreePort();
	TestObj server(333, firstFreePort, "localhost");
	server.RunServer();
	int secondFreePort = GetFreePort();
	CPPUNIT_ASSERT(firstFreePort != secondFreePort);
	server.Stop();
	int thirdFreePort = GetFreePort();
	CPPUNIT_ASSERT(firstFreePort == thirdFreePort);

	TestObj obj(222, 4444, "localhost");
	
	CPPUNIT_ASSERT(obj.RunServer());
	CPPUNIT_ASSERT(obj.TestSend()); 
	CPPUNIT_ASSERT(obj.RunListener());
	
	obj.Stop();
	obj.DoEvents();

	CPPUNIT_ASSERT(obj.TestGotMessage());

}

// -------+++++++------- JTestView class -------+++++++------- //
IMPLEMENT_DYNCREATE(JTestView, G2JChartView)

BEGIN_MESSAGE_MAP(JTestView, G2JChartView)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void JTestView::OnDestroy()
{
	flag = true;
	G2JChartView::OnDestroy();
}

// -------+++++++------- TestObj class -------+++++++------- //
DWORD WINAPI RunTestServer(LPVOID);
DWORD WINAPI RunTestListener(LPVOID);

TestObj::TestObj(int handle, int port, const char* host)
	: m_pJView( new JTestView(handle) )
	, m_Server( port, host )
	, m_hServerThread( NULL )
	, m_hListenThread( NULL )
	, hStarted1( CreateEvent(NULL, TRUE, FALSE, NULL) )
	, hStarted2( CreateEvent(NULL, TRUE, FALSE, NULL) )
	, hStopServer( CreateEvent(NULL, TRUE, FALSE, NULL) )
{
	m_pJView->Create(_T("STATIC"), NULL, WS_CHILD, CRect(200, 200, 400, 400), 
		CWnd::FromHandle(GetMainWnd()->GetSafeHwnd()), 11);
	JChartServer::GetInstance()->AddChartHandle(handle, m_pJView);
}

TestObj::~TestObj()
{
	CloseHandle(m_hServerThread);
	CloseHandle(hStarted1);
	CloseHandle(hStopServer);
	CloseHandle(m_hListenThread);
	CloseHandle(hStarted2);

	delete m_pJView;
	m_pJView = NULL;
}

bool TestObj::TestSend()
{
	return m_Server.TryToConnect() && !m_Server.IsConnectionLost();
}

bool TestObj::RunServer()
{
	bool res = false;
	m_hServerThread = CreateThread(NULL, 0, &RunTestServer, this, 0, NULL);
	if ( m_hServerThread )
	{
		WaitForSingleObject(hStarted1, INFINITE);
		res = true;
	}
	return res;
}

bool TestObj::RunListener()
{
	bool res = false;
	m_hListenThread = CreateThread(NULL, 0, &RunTestListener, this, 0, NULL);
	if ( m_hListenThread )
	{
		// wait till started
		WaitForSingleObject(hStarted2, INFINITE);
		Sleep(100);
		res = true;
	}
	return res;
}

void TestObj::Stop()
{
	SetEvent(hStopServer); // Stop Server signal
	WaitForSingleObject(m_hServerThread, INFINITE);
	WaitForSingleObject(m_hListenThread, INFINITE);	
}

void TestObj::DoEvents()
{
	// need to process WM_DESTROY
	MSG dispatch;
	while (::PeekMessage( &dispatch, NULL, 0, 0, PM_NOREMOVE))
	{
		GetMessage(&dispatch, 0, 0, 0);
		DispatchMessage(&dispatch);
	}	
}

void TestObj::Listen()
{
	m_Server.Listen();
}

int TestObj::GetPort() const
{
	return m_Server.m_nPort;
}

int TestObj::GetHandle() const
{
	return m_pJView->m_handle;
}

bool TestObj::TestGotMessage() const
{
	return m_pJView->flag;
}

// -------+++++++------- Threads -------+++++++------- //
JString GetResponseMessage(TestObj* pTest)
{
	static const CString respTempl = _T("<?xml version=\"1.0\" encoding=\"UTF-8\"?><message><handle>%d</handle><action>ChartEvent</action><id>closed</id></message>\n");
	CString str;
	str.Format(respTempl, pTest->GetHandle());
	return JString(str);
}

const int buffLen = 0x0100;
char buff[buffLen];

DWORD WINAPI RunTestServer(LPVOID lpParameter)
{
	TestObj* pTest = reinterpret_cast<TestObj*>(lpParameter);
	WSADATA wsa_data;
	if (WSAStartup(0x101,&wsa_data) == 0)
	{
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		if (s != INVALID_SOCKET)
		{			
			sockaddr_in addr;
			memset(&addr, 0, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
			addr.sin_port = htons(pTest->GetPort());

			if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == 0 && listen(s, 1) != SOCKET_ERROR)
			{
				sockaddr_in client_addr; 
				int from_len = sizeof(client_addr);
				SetEvent(pTest->hStarted1); // Server started and ready for client
				SOCKET client_socket = accept(s, (LPSOCKADDR)&client_addr, &from_len);	
				
				// client connected
				if ( SOCKET_ERROR != recv(client_socket, buff, buffLen, 0) )
				{
					JString response = GetResponseMessage(pTest);
					send(client_socket, response, strlen(response), 0);
				}

				WaitForSingleObject(pTest->hStopServer, INFINITE); // Wait till STOP Server signal
				closesocket(client_socket);
			}
		}
		closesocket(s);
	}
	SetEvent(pTest->hStarted1);
	return 0;
}

DWORD WINAPI RunTestListener(LPVOID lpParameter)
{
	TestObj* pTest = reinterpret_cast<TestObj*>(lpParameter);
	SetEvent(pTest->hStarted2);
	pTest->Listen();
	return 0;
}
