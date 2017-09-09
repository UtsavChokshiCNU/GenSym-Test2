
#include "stdafx.h"
#include "JChartView.h"
#include "JChartXML.h"
#include "JChartServer.h"

#include <stdlib.h>

// copied from mdi.c
#define CHART_CREATE 1
#define CHART_DESTROY 2
#define CHART_PRINT 3
#define CHART_UPDATE 4
#define CHART_PARTIAL_UPDATE 5
#define CHART_COPY 6
#define CHART_EXPORT 7


IMPLEMENT_DYNCREATE(G2JChartView, G2ChartView)

BEGIN_MESSAGE_MAP(G2JChartView, G2ChartView)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_CLICK_ACTION, ClickAction)
END_MESSAGE_MAP()

G2JChartView::G2JChartView(int handle)
	: G2ChartView(handle)
{
}

G2JChartView::~G2JChartView()
{
}

long G2JChartView::SetInt(long prop, long i, long j, long value)
{
	if (JChartServer* pServer = JChartServer::GetInstance())
	{
		JChartSetInt xml(m_handle, prop, i, j, value);
		pServer->Send(xml);
	}
	return JCHART_RETURN;
}

long G2JChartView::SetString(long prop, long i, long j, LPWSTR string)
{
	if (JChartServer* pServer = JChartServer::GetInstance())
	{
		JChartSetString xml(m_handle, prop, i, j, string);
		pServer->Send(xml);
	}
	return JCHART_RETURN;
}

long G2JChartView::SetDouble(long prop, long i, long j, double value)
{
	if (JChartServer* pServer = JChartServer::GetInstance())
	{
		JChartSetDouble xml(m_handle, prop, i, j, value);
		pServer->Send(xml);
	}
	return JCHART_RETURN;
}

long G2JChartView::SetDoubleArray(long prop, long start, long count, double *array)
{
	if (JChartServer* pServer = JChartServer::GetInstance())
	{
		JChartSetDoubleArray xml(m_handle, prop, start, count, array);
		pServer->Send(xml);
	}
	return JCHART_RETURN;
}

long G2JChartView::ManageJChartView(long opcode, long width, long height, long format, LPWSTR pathname)
{
	switch(opcode) {
		case CHART_DESTROY:
			if (JChartServer* pServer = JChartServer::GetInstance())
			{
				JChartDestroy xml(m_handle);
				pServer->Send(xml);
			}
			break;

		case CHART_PRINT:
			if (JChartServer* pServer = JChartServer::GetInstance())
			{
				JChartPrint xml(m_handle);
				pServer->Send(xml);
			}
			break;

		case CHART_UPDATE:
		case CHART_PARTIAL_UPDATE:
			if (JChartServer* pServer = JChartServer::GetInstance())
			{
				JChartUpdate xml(m_handle);
				pServer->Send(xml);
			}
			break;

		case CHART_EXPORT:		// Export to client-side bitmap file.
			if (JChartServer* pServer = JChartServer::GetInstance())
			{
				JChartExport xml(m_handle, width, height, format, pathname);
				pServer->Send(xml);
			}
			break;

		case CHART_COPY:		// Export to clipboard
			if (JChartServer* pServer = JChartServer::GetInstance())
			{
				JChartCopy xml(m_handle);
				pServer->Send(xml);
			}
			break;

		default:
			break;
	}
	return JCHART_RETURN;
}

void G2JChartView::CreateChart(long chart_type, LPWSTR title, long x, long y, long width, long height)
{
	if (JChartServer* pServer = JChartServer::GetInstance())
	{
		pServer->testConnect();

		JChartCreate xml(m_handle, chart_type, title, x, y, width, height);
		pServer->Send(xml);

		JChartServer::GetInstance()->AddChartHandle(m_handle, this);
	}
}

void G2JChartView::OnDestroy()
{
	JChartServer::GetInstance()->RemoveChartHandle(m_handle);

	g2pvt_send_window_closed(m_hWnd, m_handle);
	CWnd::OnDestroy();
}

extern "C" void g2pvt_send_event(HWND hwnd, int handle,
                      int eventtype, long x, long y, long width, long height,
                      long key_code, long key_bits, LPWSTR value);
#define CV_EVENT_CLICK 2
#define X11_CONTROL	   11


LRESULT G2JChartView::ClickAction(WPARAM wparam, LPARAM lparam)
{
	double x = ((double*)wparam)[0];
	double y = ((double*)wparam)[1];
	double z = ((double*)wparam)[2];
	int subset = ((double*)wparam)[3];
	int point = ((double*)wparam)[4];
	delete[] (double*)wparam;
	
	wchar_t buf[129];
	size_t num = 128;

	ZeroMemory(&buf, sizeof(buf));
	_snwprintf(buf, num, L"x=%f, y=%f, z=%f", x, y, z);
	
	g2pvt_send_event(GetSafeHwnd(),
					 m_handle,
					 X11_CONTROL,
					 subset,
					 point,
					 0,
					 CV_EVENT_CLICK,	// Event-code
					 GENSYM_CHART,
					 0, 
					 buf);
	return 0;
}

