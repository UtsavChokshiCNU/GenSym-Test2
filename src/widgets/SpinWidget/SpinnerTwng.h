// -*- Mode: C++ -*-
// SpinnerTwng.h : header file
//

#pragma once

#include "dyndlgs.h"
#include "cprim.h"
#include <math.h>                         // floating point ops for spin control

#define ID_BUT   100
#define ID_EDIT  101

#define SIZE_OF_SPINNER_STRING 256 // old value (128) is too small for holding 3 double floats
#define EPSILON 1.0e-7
#define MINIMUM_INCREMENT 1.0e-4

#define DUMMY_LOW_VALUE_FOR_OWNER_HANDLED_SPINNER  0
#define DUMMY_HIGH_VALUE_FOR_OWNER_HANDLED_SPINNER 1000

extern "C" CONTROLITEM *g2pvt_lookup_control_by_hwnd (int controlId, HWND hwnd);
extern void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode);
extern CWnd *g2pvt_get_control_cwnd (long controlId, HWND hwndDlg);

typedef union        // Declare a union that can hold the following:
{
  long        lValue;  // long value
  double      dValue;  // double value
} NumericType;


class CSpinnerTwng;
class CSpinButtonCtrlTwng;

/////////////////////////////////////////////////////////////////////////////
// CSpinEditTwng window

class CSpinEditTwng : public CEdit
{
  // Construction, Destruction
public:
  CSpinEditTwng ();
  virtual ~CSpinEditTwng ();

  // Operations
protected:
  virtual void PostNcDestroy ();

  // Generated message map functions
protected:
  //{{AFX_MSG(CSpinEditTwng)
  afx_msg void OnChange ();
  afx_msg void OnKillFocus(CWnd *pNewWnd);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP ()

  // Attributes
private:
  CString m_strPrev; //previous value of the spinner before the edit
  CString m_strOrig; // stores the value of the control - used to determine if
                     // the value has changed during editing
  BOOL m_valid;

  // Implementation
public:
  CSpinnerTwng *GetSpinner();
  CSpinButtonCtrlTwng *GetButtonCtrl();
  void set_and_get_text (wchar_t *szBuf);

private:
  BOOL process_entered_contents ();
};



/////////////////////////////////////////////////////////////////////////////
// CSpinButtonCtrlTwng window

class CSpinButtonCtrlTwng : public CSpinButtonCtrl
{
  // Construction, Destruction
public:
  CSpinButtonCtrlTwng ();
  virtual ~CSpinButtonCtrlTwng ();

  // Operations
protected:
  virtual void PostNcDestroy ();

  // Generated message map functions
protected:
  //{{AFX_MSG(CSpinButtonCtrlTwng)
  afx_msg void OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP ()

  // Implementation
public:
  CSpinEditTwng *m_pSpinEditTwng;

  void set_spin (LPCTSTR pText, DWORD g2styles, TCHAR **new_text);
  BOOL spinner_contents_are_valid (LPCTSTR pTextBuf);
  wchar_t *get_control_value ();
  wchar_t *spin_value_as_text ();

private:
  CDialog hwndDialog;

  // The spinners are considered to be in in decimal or scientific notation if
  // any of the input values (min, max, increment or default) are in decimal or
  // scientific notation.  Otherwise, we assume we have integers.
  NumericType spin_min;
  NumericType spin_max;
  NumericType increment;
  NumericType defaultval;
  NumericType current_value;
  long spinner_styles;
  // these two fields are not used for integer spinners
  int left_of_decimal; // maximum number digits to the left of the decimal
                       // before we switch to scientific notation
  int right_of_decimal; // number of digits to the right of decimal

  void parse_spin_integer_value (wchar_t *pszTemp);
  void parse_spin_float_value (wchar_t *pszTemp);
  int number_of_decimal_places (double dbl);
};


/////////////////////////////////////////////////////////////////////////////
// CSpinnerTwng window

// This is the class which is actually instantiated for a spinner control.
// Inside is m_pSpinButtonCtrlTwng, which is the 'brains' of the whole thing.  A
// CEdit control, m_pSpinButtonCtrlTwng->m_pSpinEditTwng is buddied up with the
// spinner.

class CSpinnerTwng : public CWnd
{
public:
  CSpinButtonCtrlTwng *m_pSpinButtonCtrl;

public:
  CSpinnerTwng ();
  virtual ~CSpinnerTwng ();

protected:
  virtual void PostNcDestroy ();

protected:
  afx_msg void OnSetFocus(CWnd *pOldWnd);
  afx_msg void OnEnable(BOOL bEnable);
  afx_msg void OnWindowPosChanging(WINDOWPOS* pWndPos);
  afx_msg void OnWindowPosChanged(WINDOWPOS* pWndPos);
  DECLARE_MESSAGE_MAP ()

public:
  BOOL Create(DWORD dwStyle, DWORD dwEditStyle, const RECT& rect, CWnd *pParent, UINT nID);
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd *pParent, UINT nID);
  CSpinEditTwng *GetEditCtrl() { return m_pSpinButtonCtrl ? m_pSpinButtonCtrl->m_pSpinEditTwng : NULL; }
  void RecalcLayout();
};
