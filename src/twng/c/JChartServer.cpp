
#include "stdafx.h"

#include "JChartServer.h"
#include "JChartXML.h"
#include "JMessageFactory.h"
#include "JChartView.h"
#include "CommandLineRunner.h"


const CString JChartServer::m_szFormatTemplate = _T("cmd /c java -cp %s\\jfree\\jfree-lib.jar;%s\\jfree\\jfreechart-1.0.13.jar;%s\\jfree\\jcommon-1.0.16.jar gensym.charts.ChartsRunner %d");

DWORD WINAPI RunListener(LPVOID lpParameter)
{
	JChartServer::GetInstance()->Listen();
	return 0;
}

//Returns first free port from diapason [startPortToScan;endPortToScan] or -1 if all ports are busy.
int GetFreePort()
{
	unsigned short startPortToScan = 4000;
	const unsigned short endPortToScan = 6000;

	while (startPortToScan <= endPortToScan)
	{
		SOCKET socket_ = socket(AF_INET,SOCK_STREAM, 0);
		hostent *he = gethostbyname("localhost");
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr = *((in_addr *)he->h_addr);
		addr.sin_port = htons(startPortToScan);

		memset(&(addr.sin_zero), 0, 8); 
		u_long iMode = 0;
		ioctlsocket(socket_, FIONBIO, &iMode);

		bool connected = ::connect(socket_, (sockaddr *) &addr, sizeof(sockaddr)) == 0;
		closesocket(socket_);
		if (!connected)
			return startPortToScan;
		++startPortToScan;
	}
	return -1;
}


void JChartServer::testConnect()
{
	m_nLastError = 0;
	if (IsConnectionLost())
	{
		Start();
	}
}

JChartServer* JChartServer::GetInstance()
{
	static JChartServer instance(GetFreePort(), "localhost");

	return &instance;
}

class CAutoCliticalSection
{
public:
	CAutoCliticalSection(CRITICAL_SECTION& cs)
		: m_cs(cs)
	{
		EnterCriticalSection(&m_cs);
	}

	~CAutoCliticalSection()
	{
		LeaveCriticalSection(&m_cs);
	}

private:
	CRITICAL_SECTION& m_cs;
};

void JChartServer::AddChartHandle(int nHandle, G2JChartView* pView)
{
	CAutoCliticalSection cs(m_csCharts);
	m_sCharts.SetAt(nHandle, pView);
}

void JChartServer::RemoveChartHandle(int nHandle)
{
	bool isEmpty = false;
	{
		CAutoCliticalSection cs(m_csCharts);
		m_sCharts.RemoveKey(nHandle);
		isEmpty = m_sCharts.GetCount() == 0;
	}

	if (isEmpty)
	{
		GetInstance()->StopServer();
	}
}

void JChartServer::FreeHandlesMap()
{
	CAutoCliticalSection cs(m_csCharts);

	int key = 0;
	G2JChartView* pView = NULL;
	for (POSITION pos = m_sCharts.GetStartPosition(); pos != NULL; m_sCharts.GetNextAssoc(pos, key, pView))
	{
		if (pView != NULL)
		{
			pView->PostMessage(WM_DESTROY);
		}
	}
}

G2JChartView* JChartServer::FindChartByHandle(int nHandle)
{
	CAutoCliticalSection cs(m_csCharts);
	
	G2JChartView* pChart = NULL;
	m_sCharts.Lookup(nHandle, pChart);

	return pChart;
}

void JChartServer::StopServer()
{
	closesocket(m_nSocket);
	m_nSocket = NULL;
	
	// Wait till the end of JChartServer::Listen() function
	WaitForSingleObject(m_hThreadHandle, INFINITE);

	CloseHandle(m_hThreadHandle);
	m_hThreadHandle = NULL;
}


JChartServer::JChartServer(int nPort, const char* szHost)
	: m_nPort(nPort)
	, m_szHostName(szHost)
	, m_nLastError(0)
	, m_nSocket(0)
	, m_csCharts()
	, m_sCharts()
	, m_hThreadHandle(0)
{
	InitializeCriticalSection(&m_csCharts);
	m_nSocket = socket(AF_INET, SOCK_STREAM, 0);
}

JChartServer::~JChartServer()
{
	StopServer();
	DeleteCriticalSection(&m_csCharts);
}

bool JChartServer::IsConnectionLost()
{
	JChartConnectionTest xml;
	return !Send(xml) || m_nLastError != 0;
}

bool send(const char* msg, SOCKET socket, int& error)
{
	bool result = send(socket, msg, strlen(msg), 0) != SOCKET_ERROR;
	if (!result)
	{
		error = WSAGetLastError();
	}
	return result;
}

bool JChartServer::Send(const JServerMessage& jMessage)
{
	m_nLastError = 0;

	JString szMessage(jMessage);

	return send(szMessage, m_nSocket, m_nLastError) && send("\n", m_nSocket, m_nLastError);
}

class CSocketReader
{
public:
	CSocketReader(SOCKET socket, int bufferSize = 0x100)
		: m_Socket(socket)
		, m_nBufferSize(bufferSize)
		, m_pBuffer(new char[bufferSize])
		, m_nBufferPos(0)
		, m_nBufferReaded(0)
	{
	}

	~CSocketReader()
	{
		delete[] m_pBuffer;
	}

	bool readLine(CString& str, int& error)
	{
		USES_CONVERSION;
		char buffer[0x100];
		int pos = 0;
		buffer[sizeof(buffer) - 1] = 0;

		str.Empty();
		char ch = 0;
		bool ok = readChar(ch, error);
		while (ok && ch != '\n')
		{
			buffer[pos++] = ch;
			if (pos == sizeof(buffer) - 1)
			{
				pos = 0;
				str += A2T(buffer);
			}

			ok = readChar(ch, error);
		}

		if (pos > 0)
		{
			buffer[pos] = 0;
			str += A2T(buffer);
		}

		return ok;
	}

	bool readChar(char& ch, int& error)
	{
		bool result = readIfNecessary(error);

		if (result)
		{
			ch = m_pBuffer[m_nBufferPos++];
		}

		return result;
	}

private:
	bool readIfNecessary(int& error)
	{
		error = 0;

		if (m_nBufferPos >= m_nBufferReaded)
		{
			m_nBufferPos = 0;
			m_nBufferReaded = recv(m_Socket, m_pBuffer, m_nBufferSize, 0);
			if (m_nBufferReaded <= 0)
			{
				error = WSAGetLastError();
			}
		}
		return m_nBufferPos < m_nBufferReaded;
	}

	SOCKET m_Socket;
	char* m_pBuffer;
	int m_nBufferSize;
	int m_nBufferPos;
	int m_nBufferReaded;
};

void JChartServer::Listen()
{
	CSocketReader reader(m_nSocket);
	CString xml;
	CString line;
	for(;;)
	{
		if (reader.readLine(line, m_nLastError))
		{
			if (!line.IsEmpty())
			{
				xml += line;
				if (JMessageFactory::GetInstance()->ProcessMessage(xml))
				{
					xml.Empty();
				}
			}
		}
		else if (IsConnectionLost())
		{
			FreeHandlesMap();
			break;
		}
	}
}

bool JChartServer::Start()
{
	StopServer();

	if (RunServer())
	{
		for (int i = 0; i < 10; i++)
		{
			if (TryToConnect()) 
			{
				m_hThreadHandle = CreateThread(NULL, 0, &RunListener, NULL, 0, NULL);
				return true;
			}
		}
	}

	return false;
}

bool JChartServer::TryToConnect()
{
	m_nLastError = 0;

	if (0 == m_nSocket)
	{
		m_nSocket = socket(AF_INET,SOCK_STREAM, 0);
	}

	hostent *he = gethostbyname(m_szHostName);
			
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_nPort);
	addr.sin_addr = *((in_addr *)he->h_addr);
	memset(&(addr.sin_zero), 0, 8); 

	u_long iMode = 0;
	ioctlsocket(m_nSocket, FIONBIO, &iMode);

	bool connected = ::connect(m_nSocket, (sockaddr *) &addr, sizeof(sockaddr)) == 0;
	if (!connected)
	{
		m_nLastError = WSAGetLastError();
	}
	return connected;
}

bool JChartServer::RunServer()
{
	LPTSTR szCmdline = _tcsdup(GetServerPath());
	CommandLineRunner runner;
	return runner.run(szCmdline);
}

CString JChartServer::GetServerPath() const
{
	CString szRet;

	//Gensym-789-TAM1-CH-BF-JIRA-46862-JCharts do not work until restart TWNG
	TCHAR szFileName[MAX_PATH];
	::GetModuleFileName(NULL,szFileName,MAX_PATH);
	CString szMoudle = CString(szFileName);
	CString szDir = szMoudle.Left(szMoudle.ReverseFind(_T('\\')));

	szRet.Format(m_szFormatTemplate,szDir, szDir, szDir, m_nPort);
	return szRet;
}
