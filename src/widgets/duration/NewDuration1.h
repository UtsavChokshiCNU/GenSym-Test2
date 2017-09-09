// NewDuration1.h : header file
//

#pragma once

#define ID_BUT   100
#define ID_EDIT  101
#define ID_BUT2  200
#define ID_EDIT2 201
#define ID_EDIT3 3001

#define EDIT_MULTIPLIER       3
#define DATETIME_MULTIPLIER   4
#define UPDOWN_DENOMINATOR    4

#include "MySpinButton.h"
#include "MyCDateTime.h"
#include <afxdtctl.h>

class CNewDuration : public CWnd
{
  DECLARE_DYNAMIC(CNewDuration)

public:
  BOOL IsInitializing ();

  CMySpinButton *pButton;
  CMyCEdit *pEdit;
  CMyCDateTime *pDateTime;

  CMySpinButton *pButton2;
  CMyCEdit *pEdit2;

public:
  void SetCurrentDurationValue (LPCTSTR pTextValue);
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd *pParentWnd, UINT nID);
  void ReComputeWindowText(CString& str);

public:
  virtual ~CNewDuration ();

protected:
  virtual void PostNcDestroy();

protected:
  afx_msg void OnEnable (BOOL bEnable);
  DECLARE_MESSAGE_MAP()

  void SetInitializing ();
  void ClearInitializing ();
  void SetToolTip ();

private:
  BOOL m_bIsInitializing;
};
