// MySpinButton.h : header file
//

#pragma once

#include "MyCEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CMySpinButton window

class CMySpinButton : public CSpinButtonCtrl
{
public:
  CMySpinButton ();
  virtual ~CMySpinButton ();

public:
  void SetBuddy (CMyCEdit *edit);

protected:
	virtual void PostNcDestroy();

protected:
  afx_msg void OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult);
  DECLARE_MESSAGE_MAP()
};
