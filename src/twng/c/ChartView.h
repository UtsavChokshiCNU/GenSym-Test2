// -*- Mode: C++ -*-

#pragma once

#include "Twng.h"

#define JCHART_RETURN 1
#define GIGASOFT_RETURN 0

class G2ChartView : public CWnd
{
public:
  G2pointer m_g2pointer;

protected:
  int m_handle;					// Control handle (G2-assigned)
  BOOL m_destroying;

public:
  int m_update_tick;
  int m_data_tick;

public:
  DECLARE_DYNCREATE(G2ChartView)
  G2ChartView(int handle = 0);
  virtual ~G2ChartView();
  virtual int GetHandle() {return m_handle;}

  virtual long SetInt(long prop, long i, long j, long value)
  {
	return GIGASOFT_RETURN;
  }
  virtual long SetString(long prop, long i, long j, LPWSTR string)
  {
	return GIGASOFT_RETURN;
  }
  virtual long SetDouble(long prop, long i, long j, double value)
  {
	return GIGASOFT_RETURN;
  }
  virtual long SetDoubleArray(long prop, long start, long count, double *array)
  {
	return GIGASOFT_RETURN;
  }
  virtual long ManageJChartView(long opcode, long width, long height, long format, LPWSTR pathname)
  {
	return GIGASOFT_RETURN;
  }

public:
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
  afx_msg void OnChartKeyDown();
  afx_msg void OnChartClick();
  afx_msg void OnChartMenuChoice();
  afx_msg void OnCursorMove();

protected:
  virtual void PostNcDestroy();
  DECLARE_MESSAGE_MAP()
};
