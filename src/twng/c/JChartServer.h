#pragma once
#include <afxwin.h>
#include <afxtempl.h>
#include <winsock2.h>

class JServerMessage;
class G2JChartView;
int GetFreePort();

class JChartServer
{
public:
	static JChartServer* GetInstance();
	
	void StopServer();

	void AddChartHandle(int nHandle, G2JChartView* pView);
	void RemoveChartHandle(int nHandle);

	G2JChartView* FindChartByHandle(int nHandle);

	bool Send(const JServerMessage& jMessage);
	void Listen();

	void testConnect();

	~JChartServer();
	CString GetServerPath() const;
	const char* getHost() const { return m_szHostName;}
	int getPort() const {return m_nPort;}

protected:
	JChartServer(int nPort, const char* szHost);

	bool TryToConnect();
	bool Start();
	bool RunServer();
	bool IsConnectionLost();

	void FreeHandlesMap();

	// critical section for m_sCharts
	CRITICAL_SECTION m_csCharts;

	// handles Map of the G2JChartView's
	typedef CMap<int, int, G2JChartView*, G2JChartView*> ChartsMap;
	ChartsMap m_sCharts;

	// HANDLE of the ListenerThread
	HANDLE m_hThreadHandle;

	// Template for running server
	static const CString m_szFormatTemplate;

	// Socket of the client
	SOCKET m_nSocket;

	// SOCKECT port
	size_t m_nPort;

	// Last Error (Only for debug)
	int m_nLastError;

	// Host name, now it's localhost
	const char* m_szHostName;

};
