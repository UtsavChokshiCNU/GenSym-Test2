// MyCDateTime.h : header file
//

#pragma once

#include <afxdtctl.h>

class CMyCDateTime : public CDateTimeCtrl
{
public:
  CMyCDateTime();
  virtual ~CMyCDateTime ();

protected:
  virtual void PostNcDestroy();

protected:
  afx_msg void OnDatetimechange(NMHDR* pNMHDR, LRESULT* pResult);
  DECLARE_MESSAGE_MAP()
};
