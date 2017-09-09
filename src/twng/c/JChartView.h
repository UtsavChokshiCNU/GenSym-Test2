#pragma once

#include "ChartView.h"

class G2JChartView: public G2ChartView
{
public:
  DECLARE_DYNCREATE(G2JChartView)
  
  G2JChartView(int handle = 0);
  virtual ~G2JChartView();

  afx_msg void OnDestroy();

  virtual long SetInt(long prop, long i, long j, long value);
  virtual long SetString(long prop, long i, long j, LPWSTR string);
  virtual long SetDouble(long prop, long i, long j, double value);
  virtual long SetDoubleArray(long prop, long start, long count, double *array);
  virtual long ManageJChartView(long opcode, long width, long height, long format, LPWSTR pathname);
  void CreateChart(long chart_type, LPWSTR title, long x, long y, long width, long height);
  LRESULT ClickAction(WPARAM wparam, LPARAM lparam);

protected:
  DECLARE_MESSAGE_MAP()

};
