// ChartView.cpp -- Subclassed PEchart with G2 interface.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ChartView.h"
#include "JChartView.h"

// Temporarily copied from mdi.c until multiwindow mode goes away. -fmw, 4/26/06
#define CHART_DESTROY 2

#define PEWN_CLICKED (WM_USER + 2930)
#define PEWN_CURSORMOVE (WM_USER + 2929)
#define PEWN_KEYDOWN (WM_USER + 2952)
#define PEWN_CUSTOMMENU (WM_USER + 2956)
#define DESTROY_CHART (WM_USER + 4000)

#ifdef TRACE_VIEWS
#define CTRACE(str) PRINTF(str); g2pvt_printf(" [%d] ", m_handle); print_object(this)
#else
#define CTRACE(str)
#endif

IMPLEMENT_DYNCREATE(G2ChartView, CWnd)

BEGIN_MESSAGE_MAP(G2ChartView, CWnd)
 ON_WM_SETFOCUS()
 ON_WM_SIZE()
 ON_WM_DESTROY()
 ON_CONTROL_REFLECT(PEWN_KEYDOWN, OnChartKeyDown)
 ON_CONTROL_REFLECT(PEWN_CLICKED, OnChartClick)
 ON_CONTROL_REFLECT(PEWN_CUSTOMMENU, OnChartMenuChoice)
 ON_CONTROL_REFLECT(PEWN_CURSORMOVE, OnCursorMove)
END_MESSAGE_MAP()

G2ChartView::G2ChartView(int handle)
{
  m_handle = handle;
  m_destroying = FALSE;
  m_update_tick = 0;
  m_data_tick = 0;
  m_g2pointer = -1;
  SAVE_WND();
  CTRACE("Construct");
}

G2ChartView::~G2ChartView()
{
  CTRACE("Destruct");
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
}

void G2ChartView::PostNcDestroy()
{
  CTRACE("PostNcDestroy");
  CWnd::PostNcDestroy();
  //delete this;
}

void G2ChartView::OnSetFocus(CWnd* pOldWnd)
{
  CTRACE("OnSetFocus");

  CWnd::OnSetFocus(pOldWnd);

  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void G2ChartView::OnSize(UINT nType, int cx, int cy)
{
  CTRACE("OnSize");

  BOOL visible = (GetStyle()&WS_VISIBLE) != 0;
  CWnd::OnSize(nType, cx, cy);	// Chart's WM_SIZE handler makes it visible!
  if(!visible)
    ModifyStyle(WS_VISIBLE,0);
  g2pvt_view_sized(this, m_handle);
}

void G2ChartView::OnDestroy()
{
  CTRACE("OnDestroy");

  // Convert this WM_DESTROY into PEdestroy
  if(!m_destroying) 
  {
    m_destroying = TRUE;
    if(m_handle > 0)
	{
      g2pvt_send_window_closed(m_hWnd, m_handle);
	}
	
	g2pvt_pechart_destroy(m_hWnd);
  } 
  else 
  {
    CWnd::OnDestroy();
  }
}

void G2ChartView::OnChartKeyDown()
{
  CTRACE("OnChartKeyDown");
  g2pvt_pechart_keydown(m_hWnd, m_handle);
}

void G2ChartView::OnChartClick()
{
  CTRACE("OnChartClick");
  g2pvt_pechart_click(m_hWnd, m_handle);
}

void G2ChartView::OnChartMenuChoice()
{
  CTRACE("OnChartMenu");
  g2pvt_pechart_menu_choice(m_hWnd, m_handle);
}

void G2ChartView::OnCursorMove()
{
  CTRACE("OnCursorMove");
  g2pvt_pechart_cursormove(m_hWnd, m_handle);
}



/*
 * Lisp Interface
 */


long g2ext_create_chart_view(long handle, LPWSTR title, long chart_type, long style16,
			     long x, long y, long width, long height,
			     long dock, long neighbor, LPWSTR lib, long min_width, long min_height)
{
	CMainFrame *pFrame = GetMainWnd();
	if ( 0 == wmemcmp(L"GIGASOFT", lib, 8) )
	{
	  HWND hPE = g2pvt_create_chart_view(chart_type, WS_CHILD | WS_CLIPSIBLINGS, pFrame->GetSafeHwnd());
	  if(!hPE) return -1;

	  G2ChartView *pCV = new G2ChartView(handle);
	  pCV->SubclassWindow(hPE);
	  pCV->m_g2pointer = SavePtr(hPE);
          CSize min_size(min_width, min_height);
	  if ( CMDIChildWnd *pWnd = pFrame->WrapWnd(pCV, handle, x, y, width, height, dock, neighbor, min_size, title) )
	  {
		  // Chart views, unique among native views, processed init options for state,
		  // resizeable, etc. So we have to repeat that here, until we implement a more
		  // general mechanism. -fmw, 4/26/06
		  g2pvt_process_window_style(pWnd, ((unsigned)style16) << 16);
	  }

	  return pCV->m_g2pointer;
	}
	else
	{
		G2JChartView *pCV = new G2JChartView(handle);
		CWnd* pParent = CWnd::FromHandle(GetMainWnd()->GetSafeHwnd());
		if ( pCV->Create(_T("STATIC"), NULL, WS_CHILD /*| WS_VISIBLE*/, CRect(200, 200, 400, 400), pParent, 1234) )
		{
		//	CMDIChildWnd* pWnd = pFrame->WrapWnd(pCV, handle, x, y, width, height, dock, neighbor, title);
			pCV->CreateChart(chart_type, title, x, y, width, height);
		}
		return 0;

	}
}

long g2ext_manage_chart_view(long handle, long opcode, long width, long height, long format, LPWSTR pathname)
{
  G2ChartView *pCV = FIND_WND(handle,G2ChartView);

  if(!pCV || pCV->ManageJChartView(opcode, width, height, format, pathname)) return 0;

  if(opcode == CHART_DESTROY) {
    DESTROY_WND(handle);
    return 1;
  } else {
    return g2pvt_manage_chart_view(pCV->GetSafeHwnd(), opcode, width, height, format, pathname);
  }
}

/*
 * Overrides
 */

HWND g2pvt_find_pechart(int handle)
{
  G2ChartView *pCV = FIND_WND(handle,G2ChartView);
  return pCV->GetSafeHwnd();
}

BOOL g2pvt_pechart_ticks(HWND hPE, int **update_tick, int **data_tick)
{
  G2ChartView *pCV = DYNAMIC_DOWNCAST(G2ChartView, CWnd::FromHandlePermanent(hPE));
  *update_tick = pCV ? &pCV->m_update_tick : NULL;
  *data_tick   = pCV ? &pCV->m_data_tick : NULL;
  return pCV != NULL;
}

long g2_jchart_set_int(long handle, long prop, long i, long j, long value)
{
	G2ChartView *pCV = FIND_WND(handle, G2ChartView);
	return pCV->SetInt(prop, i, j, value);
}

long g2_jchart_set_string(long handle, long prop, long i, long j, LPWSTR string)
{
	G2ChartView *pCV = FIND_WND(handle, G2ChartView);
	return pCV->SetString(prop, i, j, string);
}

long g2_jchart_set_double(long handle, long prop, long i, long j, double value)
{
	G2ChartView *pCV = FIND_WND(handle, G2ChartView);
	return pCV->SetDouble(prop, i, j, value);
}

long g2_jchart_set_double_array(long handle, long prop, long start, long count, double *array)
{
	G2ChartView *pCV = FIND_WND(handle, G2ChartView);
	return pCV->SetDoubleArray(prop, start, count, array);
}
