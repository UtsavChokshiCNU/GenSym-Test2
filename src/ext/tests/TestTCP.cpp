#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include "TestTCP.h"

#define USE_PROTOTYPES

extern "C" {
	int g2_send(SOCKET s, char* buf, int len, int flags);
	long g2pvt_tcpip_connect(char* host, int port);
	long g2ext_tcpip_accept_internals(long listener_socket);
	long g2pvt_tcpip_listen(long port_number);

	extern int g2ext_max_number_of_sockets;
	extern int socket_buffer_size;
}

CPPUNIT_TEST_SUITE_REGISTRATION(TestTCP);

class IThread
{
public:
	IThread() : my_hThread(NULL), my_FailureMessage() {}

	virtual ~IThread()
	{
		Wait();
		CloseHandle(my_hThread);
	}

	virtual void Exec() = 0;

	void Start()
	{
		my_hThread = CreateThread(NULL, 0, ThreadProc, this, 0, NULL);
	}

	bool isRunning() const
	{
		return (WaitForSingleObject(my_hThread, 0) == WAIT_TIMEOUT);
	}

	void Wait()
	{
		WaitForSingleObject(my_hThread, INFINITE);
	}

	static DWORD WINAPI ThreadProc(LPVOID lpParameter)
	{
		IThread* thread = (IThread*) lpParameter;

		try
		{
			thread->Exec();
		}
		catch (const ThreadException&)
		{
			// ignore exception
		}
		catch (const std::exception& e)
		{
			thread->my_FailureMessage = e.what();
		}
		catch (...)
		{
			thread->my_FailureMessage = "Unknown exception in thread proc.";
		}

		thread->OnEndThread();

		return 0;
	}

	virtual void OnEndThread() = 0;

	// Called from thread proc
	void TestAssertion(bool assertion, const char* msg)
	{
		if (!assertion)
		{
			my_FailureMessage = msg;
			throw ThreadException();
		}
	}

	// Called from test proc
	void TestAssert() const
	{
		CPPUNIT_ASSERT_MESSAGE(my_FailureMessage, my_FailureMessage.empty());
	}

protected:
	class ThreadException {};
	std::string my_FailureMessage;

private:
	HANDLE my_hThread;
};

#define THREAD_ASSERT(assertion) TestAssertion(assertion, #assertion)



static char* message = "Hello World";

class ServerThread : public IThread
{
public:
	ServerThread(int port) : IThread(), my_socket(0), my_port(port)
	{
		my_hStarted = CreateEvent(NULL, TRUE, FALSE, NULL);
		my_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);
		my_hWait = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	~ServerThread()
	{
		SetEvent(my_hStop);
		Wait();

		CloseHandle(my_hStarted);
		CloseHandle(my_hStop);
		CloseHandle(my_hWait);

		if (my_socket != 0)
		{
			closesocket(my_socket);
		}
	}

	virtual void OnEndThread()
	{
		SetEvent(my_hStarted);
	}

	void CreateListener()
	{
		my_socket = (SOCKET) g2pvt_tcpip_listen(my_port);

		THREAD_ASSERT(my_socket >= 0);

		// make non-blocking
		int nonblocking_flag = 1;
		ioctlsocket(my_socket, FIONBIO, (unsigned long *) &(nonblocking_flag));
	}

	int WaitForConnection()
	{
		int accepted = -1;
		listen(my_socket, 1);

		while (accepted < 0)
		{
			if (WaitForSingleObject(my_hStop, 0) == WAIT_OBJECT_0)
			{
				break;
			}

			accepted = (int) g2ext_tcpip_accept_internals(my_socket);

			if (accepted < 0 && WSAGetLastError() != WSAEWOULDBLOCK)
			{
				break;
			}
		}

		return accepted;
	}

	virtual void DoWork(int socket)	{}

	virtual void Exec()
	{
		CreateListener();
		SetEvent(my_hStarted);

		int accepted = WaitForConnection();
		THREAD_ASSERT(accepted >= 0);

		DoWork(accepted);

		SetEvent(my_hStarted);
		WaitForSingleObject(my_hWait, INFINITE);
		closesocket(accepted);
	}

	void WaitUntilStart()
	{
		WaitForSingleObject(my_hStarted, INFINITE);
		ResetEvent(my_hStarted);
	}

	void Continue()
	{
		SetEvent(my_hWait);
	}

private:
	SOCKET my_socket;
	HANDLE my_hStarted;
	HANDLE my_hStop;
	HANDLE my_hWait;

	int my_port;
};

class CSendTestServer : public ServerThread
{
public:
	CSendTestServer(int port) : ServerThread(port) {}

	virtual void DoWork(int socket)
	{
		// send message
		int count = g2_send(socket, message, strlen(message), 0);
		THREAD_ASSERT(count == strlen(message));
	}
};

class CAcceptBuffersTestServer : public ServerThread
{
public:
	CAcceptBuffersTestServer(int port) : ServerThread(port) {}

	virtual void DoWork(int socket)
	{
		// save buffers size
		int size = sizeof(int);
		int s_size = 0;
		int r_size = 0;

		getsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *) &s_size, &size);
		getsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *) &r_size, &size);

		THREAD_ASSERT(s_size == socket_buffer_size);
		THREAD_ASSERT(r_size == socket_buffer_size);
	}
};

class CAcceptHandleTestServer : public ServerThread
{
public:
	CAcceptHandleTestServer(int port) : ServerThread(port) {}

	virtual void DoWork(int socket)
	{
		DWORD flags = 0;
		THREAD_ASSERT(GetHandleInformation((HANDLE) socket, &flags) != FALSE);
		THREAD_ASSERT((flags & HANDLE_FLAG_INHERIT) == 0);
	}
};

////////////////////////////////////////////////////////////////////////

const int TestTCP::port = 1212;

void TestTCP::StartServer(ServerThread* pServer)
{
	my_server = pServer;
	my_server->Start();

	WaitServer();
	CPPUNIT_ASSERT(my_server->isRunning());
}

void TestTCP::WaitServer()
{
	my_server->WaitUntilStart();
	my_server->TestAssert();
}

SOCKET TestTCP::Connect()
{
	SOCKET client = g2pvt_tcpip_connect("localhost", port);
	CPPUNIT_ASSERT(client > 0);

	WaitServer();

	return client;
}

////////////////////////////////////////////////////////////////////////

void TestTCP::testAcceptBuffers()
{
	StartServer(new CAcceptBuffersTestServer(port));

	SOCKET client = Connect();
	
	// test connect
	int size = sizeof(int);
	int s_size = 0;
	int r_size = 0;
	getsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *) &s_size, &size);
	getsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *) &r_size, &size);

	CPPUNIT_ASSERT(s_size == socket_buffer_size);
	CPPUNIT_ASSERT(r_size == socket_buffer_size);

	closesocket(client);
}

void TestTCP::testConnect()
{
	StartServer(new ServerThread(port));

	closesocket(Connect());
}

void TestTCP::testSend()
{
	StartServer(new CSendTestServer(port));

	SOCKET client = Connect();

	// read
	char buff[100];
	memset(buff, 0, sizeof(buff));

	int length = strlen(message);
	int readed = 0;
	int count = 10;

	while (readed < length && count-- > 0)
	{
		int res = recv(client, &buff[0] + readed, sizeof(buff) - readed, 0);
		if (res == SOCKET_ERROR)
		{
			int err = WSAGetLastError();
			if (err != WSAEWOULDBLOCK)
			{
				break;
			}
		}
		else
		{
			readed += res;
		}

		// sleep before next iteration
		if (readed < length)
		{
			Sleep(1000);
		}
	}

	closesocket(client);
}

void TestTCP::testAcceptHandle()
{
	StartServer(new CAcceptHandleTestServer(port));

	closesocket(Connect());
}

void TestTCP::setUp()
{
	my_server = NULL;
}

void TestTCP::tearDown()
{
	if (my_server != NULL)
	{
		my_server->Continue();
	}
	delete my_server;
}
