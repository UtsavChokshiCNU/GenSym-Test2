/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      SpinnerTwng.cpp
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2005 - 2006      hjg, jv
+
+ Description:  TWNG Spinner Native Custom Dialog Component
+
+
+ Key:
+   (obsolete)
+
+ File Organization:
+   Section:      INCLUDE FILES
+   Section:      GLOBALS
+   Section:      FUNCTION GROUP
+
+ External Interface:
+
+ Dependencies:
+
+ Notes:
+
+ Modifications:
+   usage: All modifications to this file should be listed here, with most
+          recent first. In general, modification comments should merely
+          provide a reference to a detailed modification comment in the
+          appropriate section/function header.
+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

///////////////////////////////////////////////////////////////////////////////
//
// Overview
//
// Three window subclasses are defined in this file. They are all autodeleting
// (have PostNcDestroy methods), and so can't be used as member variables.

// (1) CSpinnerTwng, a subclass of CWnd.
// This is the top-level class. It what is actually instantiated when you ask
// for a spinner in a dialog.
//
// There was no reason for it to be a subclass of CEdit. That was done, I think,
// due to a misperception that all in-place editors for the grid control had to be
// subclasses of CEdit, which isn't true. Changed to base on CWnd -fmw, 10/2/06
//
// This window creates two child windows, a CSpinButtonCtrlTwng and a
// CSpinEditTwng, although it maintains a pointer only to the spin button,
// which in turn has the pointer to the spin edit control (weird).

// (2) CSpinEditTwng, a subclass of CEdit.
// This is the what displays the current value of the spinner, and which lets
// you edit it directly by typing.  It is the "buddy" of the spin button
// control.

// (3) CSpinButtonCtrlTwng, a subclass of CSpinButtonCtrl.
// This is the up/down control, based on the MFC class.

// WARNING: DoSpinnerCell() creates a temporary CSpinButtonCtrlTwng just to
// format the text string to initially place into a grid cell!!  Although in
// that case, Create() is never called, so no windows are created.
///////////////////////////////////////////////////////////////////////////////


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      INCLUDE FILES
%
% Description:  All required include files are referenced here.
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include "stdafx.h"
#include "SpinnerTwng.h"

#include <locale.h>

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      GLOBALS
%
% Description:  Module specific typedefs, variables, & externs defined here
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#ifdef _DEBUG
#  define new DEBUG_NEW
#  undef THIS_FILE
char THIS_FILE[] = __FILE__;
#endif

extern "C" void g2pvt_trace(char *fmt, ...);
#define PRINTF g2pvt_trace

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- CSpinEditTwng Class
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

BEGIN_MESSAGE_MAP(CSpinEditTwng, CEdit)
 ON_WM_KILLFOCUS()
 ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
END_MESSAGE_MAP()


CSpinEditTwng::CSpinEditTwng ()
{
}

CSpinEditTwng::~CSpinEditTwng ()
{
}

CSpinnerTwng *CSpinEditTwng::GetSpinner()
{
  return (CSpinnerTwng *)GetParent();
}

CSpinButtonCtrlTwng *CSpinEditTwng::GetButtonCtrl()
{
  return GetSpinner()->m_pSpinButtonCtrl;
}

/*****************************************************************************
* void set_and_get_text (wchar_t *szBuf)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinEditTwng::set_and_get_text (wchar_t *szBuf)
{
  SetWindowText(szBuf);
  GetWindowText(m_strOrig);
}

/*****************************************************************************
* BOOL process_entered_contents ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL CSpinEditTwng::process_entered_contents ()
{
  CString strText;
  CSpinButtonCtrlTwng *p1;
  BOOL valid_p = FALSE;

  GetWindowText(strText);

  p1 = GetButtonCtrl();
  valid_p = p1->spinner_contents_are_valid(strText);

  if (valid_p) {
    // save the valid text for the next iteration
    m_strPrev = strText;
    return TRUE;
  }
  // put back the last valid value; just do a sanity check
  if (0 == wcscmp(m_strPrev, strText)) {
    g2pvt_gprintf(G2PVT_ERROR, "error: the PREVIOUS text of a spinner is invalid.\n");
    // previous value also bogus.
  } else {
    SetWindowText(m_strPrev); // put back previous value
  }
  return FALSE;
}


/*****************************************************************************
* void OnKillFocus (CWnd *pNewWnd)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinEditTwng::OnKillFocus (CWnd *pNewWnd)
{
  CSpinButtonCtrlTwng *pButtonCtrl = GetButtonCtrl();
  wchar_t *szBuf = NULL;

  if (pButtonCtrl == NULL) {
    return;
  }

  szBuf = pButtonCtrl->spin_value_as_text();
  set_and_get_text(szBuf);
  // clean up
  free(szBuf);
  szBuf = NULL;

  // This ends editing, so call AFTER reformatting the text.
  CEdit::OnKillFocus(pNewWnd);
}


/*****************************************************************************
* void OnChange ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinEditTwng::OnChange ()
{
  CString strText;

  BOOL bValid;
  CONTROLITEM *pControl;
  int id;
  CWnd *pParent;
  CSpinnerTwng *p;

  GetWindowText(strText);
  if (m_strOrig == strText)
    return; //the text has not changed

  bValid = process_entered_contents();
  if (!bValid) {
	::MessageBeep(MB_OK);
	return; // something bogus entered here
  }

  m_strOrig = strText; // save this value for the next iteration.

  p = GetSpinner();

  // gather the relevant info and send the response information
  id = p->GetDlgCtrlID();
  pParent =(CWnd *)p->GetParent();
  if (!pParent)
    return;

  // if the parent is a grid-view, don't send the respond stuff
  if (!(pParent->IsKindOf(RUNTIME_CLASS(CDialog))) )
    return;

  pControl = g2pvt_lookup_control_by_hwnd (id, pParent->m_hWnd);
  if (!pControl)
    return;

  g2pvt_ddlg_respond(pParent->m_hWnd, id, pControl->_respcode);
}



/*****************************************************************************
* void PostNcDestroy ()
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments: none
*   Returns: nothing
*   Notes: Cleans up memory leaks. Caller no longer has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinEditTwng::PostNcDestroy ()
{
  CEdit::PostNcDestroy();
  delete this;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- CSpinButtonCtrlTwng Class
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


BEGIN_MESSAGE_MAP(CSpinButtonCtrlTwng, CSpinButtonCtrl)
 ON_NOTIFY_REFLECT(UDN_DELTAPOS, OnDeltapos)
END_MESSAGE_MAP()


CSpinButtonCtrlTwng::CSpinButtonCtrlTwng ()
{
  m_pSpinEditTwng = NULL;
}

CSpinButtonCtrlTwng::~CSpinButtonCtrlTwng ()
{
}


/*****************************************************************************
* BOOL spinner_contents_are_valid (LPCTSTR pTextBuf)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL CSpinButtonCtrlTwng::spinner_contents_are_valid (LPCTSTR pTextBuf)
{
  NumericType dummy;
  wchar_t *stopstring;

  if (pTextBuf == NULL) {
    // assume the only reason we'd get NULL is out of memory
    return FALSE;
  }

  // KLudge to handle a few cases of intermediately invalid entries.  The
  // correct fix is to validate on focus lost instead of
  // character-by-character. However, that is too big a change at this
  // time. KB's may be expecting the character-by-character update callbacks.
  // Plus, we'd have to decide what to do when we lose focus because the user
  // OK'd the dialog; that is, do we let the OK proceed or not.

  wchar_t plus = L'+';
  wchar_t minus = L'-';
  wchar_t dp = L'.';
  struct lconv *pLC = localeconv();			// Get the locale-specific decimal point character.
  if(pLC && pLC->decimal_point)				// Paranoia
	dp = pLC->decimal_point[0];				// Or mon_decimal_point?

  BOOL barePlus     = (pTextBuf[0] == plus  && pTextBuf[1] == 0);
  BOOL bareMinus    = (pTextBuf[0] == minus && pTextBuf[1] == 0);
  BOOL bareDot      = (pTextBuf[0] == dp    && pTextBuf[1] == 0);
  BOOL barePlusDot  = (pTextBuf[0] == plus  && pTextBuf[1] == dp && pTextBuf[2] == 0);
  BOOL bareMinusDot = (pTextBuf[0] == minus && pTextBuf[1] == dp && pTextBuf[2] == 0);

  if (spinner_styles & G2_UDS_INTEGERS) {
    dummy.lValue = wcstol(pTextBuf, &stopstring, 10);

	if(barePlus || (bareMinus && spin_min.lValue < 0))
	  return TRUE;

    if (0 != wcscmp(stopstring, L""))
      return FALSE;

    if ((dummy.lValue < spin_min.lValue) || (dummy.lValue > spin_max.lValue))
      return FALSE;

    current_value.lValue = dummy.lValue;

  } else {
    dummy.dValue = wcstod(pTextBuf, &stopstring);

	if(barePlus || bareDot || barePlusDot || ((bareMinus || bareMinusDot) && spin_min.dValue < 0.0))
	  return TRUE;

	// If some characters were consumed, and stop character could possibly part
	// of a valid number, let it through.
    if (*stopstring && (stopstring == pTextBuf || wcschr(L"+-edED", *stopstring) == NULL))
      return FALSE;

    if ((dummy.dValue < spin_min.dValue) || (dummy.dValue > spin_max.dValue))
      return FALSE;

    current_value.dValue = dummy.dValue;
  }

  return TRUE;
}


/*****************************************************************************
* wchar_t *spin_value_as_text ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *CSpinButtonCtrlTwng::spin_value_as_text ()
{
  TCHAR *spinner_value;

  spinner_value = (wchar_t *)malloc(SIZE_OF_SPINNER_STRING * sizeof(TCHAR));
  if (spinner_value == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: spin_value_as_text\n");
    return NULL;            // out of memory!
  }

  // "integer" spinners are handled slightly differently
  if (spinner_styles & G2_UDS_INTEGERS) {
    _snwprintf(spinner_value, SIZE_OF_SPINNER_STRING-1, L"%d", current_value.lValue);
  } else {
    BOOL use_exponential;

    use_exponential = (fabs(current_value.dValue) >= pow(10.0,(double)left_of_decimal))
      || (fabs(current_value.dValue) < pow(10.0,(double)-right_of_decimal));

    _snwprintf(spinner_value,
               SIZE_OF_SPINNER_STRING-1,
               use_exponential ? _T("%.*g") : _T("%.*f"),
               use_exponential ? right_of_decimal+1 : right_of_decimal,
               current_value.dValue);
  }

  bool is_float = false;
  TCHAR *ptr = spinner_value;
  while (*ptr) {
      if (*ptr == _T('.')) {
          is_float = true;
          break;
      }
      ptr++;
  }
  if (is_float) {
      ptr = spinner_value;
      while (*(++ptr));
      ptr--;
      // This change was done as part of GENSYMCID-1342.
      // It supports display of digital number without useless 0-suffix. But 
      // this causes ATC test cases to fail since TWNG behavior is slightly 
      // changed. As part of GENSYMCID-1454, GENSYMCID-1457 and GENSYMCID-1459 
      // fixes, we comment out this unneeded change.
      // while (*ptr == _T('0')) *(ptr--) = _T('\0');
      if (*ptr == '.') *ptr = _T('\0');
  }

  return spinner_value;
}


/*****************************************************************************
* void parse_spin_integer_value (wchar_t *pszTemp)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: we don't check that max > min and so forth, because that check is
*     done already in Lisp
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinButtonCtrlTwng::parse_spin_integer_value (wchar_t *pszTemp)
{
  wchar_t *token, seps[] = L"| ";

  spinner_styles = G2_UDS_INTEGERS;
  spin_min.lValue = 0;
  spin_max.lValue = 100;
  increment.lValue = 1;
  defaultval.lValue = 50;
  current_value.lValue = 50;
  left_of_decimal = 6;
  right_of_decimal = 0;

  // extract default value
  token = wcstok(pszTemp, seps);
  if (token) {
    defaultval.lValue = wcstol(token, NULL, 10);
    current_value.lValue = defaultval.lValue;
    // extract minimum value
    token = wcstok(NULL, seps);
    if (token) {
      spin_min.lValue = wcstol(token, NULL, 10);
      // extract maximum value
      token = wcstok(NULL, seps);
      if (token) {
        spin_max.lValue = wcstol(token, NULL, 10);
        // extract increment
        token = wcstok(NULL, seps);
        if (token) {
          increment.lValue = wcstol(token, NULL, 10);
          if (increment.lValue == 0) {
            g2pvt_gprintf(G2PVT_ERROR, "rejecting too small increment\n");
            increment.lValue = 1;
          }
        }
      }
    }
  }
}


/*****************************************************************************
* int number_of_decimal_places (double dbl)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
int CSpinButtonCtrlTwng::number_of_decimal_places (double dbl)
{
  double tmp;
  double flr;
  int n=0;

  tmp = fabs(dbl);

  flr = floor(tmp);
  tmp = tmp - flr;

  while ((tmp > EPSILON) && (++n < SIZE_OF_SPINNER_STRING)) {
    tmp = tmp * 10.0;

    flr = floor(tmp + EPSILON);
    tmp = tmp - flr;
  }
  return n;
}


/*****************************************************************************
* void parse_spin_float_value (wchar_t *pszTemp)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinButtonCtrlTwng::parse_spin_float_value (wchar_t *pszTemp)
{
  wchar_t *token, seps[] = L"| ";
  double requested_increment;

  spinner_styles = 0L;
  spin_min.dValue = 0.0;
  spin_max.dValue = 100.0;
  increment.dValue = 1.0;
  defaultval.dValue = 50.0;
  current_value.dValue = 50.0;
  left_of_decimal = 6;
  right_of_decimal = 0;

  // extract default value
  token = wcstok(pszTemp, seps);
  if (token) {
    defaultval.dValue = wcstod(token, NULL);
    current_value.dValue = defaultval.dValue;
    // extract minimum value
    token = wcstok(NULL, seps);
    if (token) {
      spin_min.dValue = wcstod(token, NULL);
      // extract maximum value
      token = wcstok(NULL, seps);
      if (token) {
        spin_max.dValue = wcstod(token, NULL);
        // extract increment
        token = wcstok(NULL, seps);
        if (token) {
          requested_increment = wcstod(token, NULL);
          if ((requested_increment < MINIMUM_INCREMENT) &&
              (requested_increment > -MINIMUM_INCREMENT)) {
            if (requested_increment < 0.0) {
              increment.dValue = -MINIMUM_INCREMENT;
            } else {
              increment.dValue = MINIMUM_INCREMENT;
            }
            g2pvt_gprintf(G2PVT_ERROR, "rejecting too small increment %lf; using %lf instead\n",
                          requested_increment, increment.dValue);
          } else {
            increment.dValue = requested_increment;
          }
          // see if ddd.dddd is specifed
          token = wcstok(NULL, seps);
          if (token) {
            wchar_t *tok2;

            tok2 = wcstok(NULL, seps);

            if (tok2) {
              left_of_decimal = _wtoi(token);
              right_of_decimal = _wtoi(tok2);
            }
          }
        }
      }
    }
  }

  right_of_decimal = max(number_of_decimal_places(defaultval.dValue),
                         max(number_of_decimal_places(increment.dValue),
                             right_of_decimal));
}


/*****************************************************************************
* void set_spin (TCHAR *pText, DWORD g2Styles, TCHAR **new_text)
*
*   Description: takes a text as G2 sends it -- with the various values "packed"
*     into a single string -- and uses it to set up the internal data structures
*     of the object.  It also obtains what should be put up into the text box of
*     the spinner -- i.e., the current value, as a string.  Then, it does one of
*     two things: (1) if the third argument to this function is NULL, we go
*     ahead and set the text of the SpinEdit box.  This is the normal case.
*     (2) if the argument is not NULL, then we do not set anything directly,
*     but instead return the current value via the third argument.  This is
*     needed for the grid-view initialization case.
*
*   Input Arguments: the text to parse, the spinner's styles, and possibly a
*     pointer to a string to be filled in.
*   Returns: nothing directly, but may return the current value, by reference
*   Notes: we don't check that max > min and so forth, because that check is
*     done already in Lisp
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinButtonCtrlTwng::set_spin (LPCTSTR pText, DWORD g2Styles, TCHAR **new_text)
{
  wchar_t *szBuf = NULL;
  int len;

  // make temp copy of incoming string to mangle with wcstok
  len = wcslen(pText) + 1;
  szBuf = new wchar_t[len];
  if (szBuf == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: set_spin\n");
    return;                // out of memory!
  }
  wcsncpy(szBuf, pText, len);

  if (g2Styles & G2_UDS_INTEGERS) {
    parse_spin_integer_value(szBuf);
  } else {
    parse_spin_float_value(szBuf);
  }
  delete [] szBuf;

  // re-use local variable
  szBuf = spin_value_as_text();

  if (new_text == NULL) {
    m_pSpinEditTwng->set_and_get_text(szBuf);
    // clean up
    free(szBuf);
    szBuf = NULL;
  } else {
    *new_text = szBuf;
  }
}


/*****************************************************************************
* wchar_t *get_control_value ();
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
wchar_t *CSpinButtonCtrlTwng::get_control_value ()
{
  CString str;
  wchar_t *buffer;

  buffer = (wchar_t *)malloc(SIZE_OF_SPINNER_STRING * sizeof(TCHAR));
  if (buffer == NULL) {
    g2pvt_gprintf(G2PVT_ERROR, "out of memory: get_control_value\n");
    return NULL;            // out of memory!
  }

  m_pSpinEditTwng->GetWindowText(str);

  if (spinner_styles & G2_UDS_INTEGERS) {
    _snwprintf(buffer, SIZE_OF_SPINNER_STRING-1, L"%s|%d|%d|%d",
               (LPCTSTR) str, spin_min.lValue, spin_max.lValue, increment.lValue);
  } else {
    // GENSYMCID-1314: TWNG stops responding and crashes after performing described steps.
    // NOTE: use "%lf" or "%f" instead of "%g" could exceeds the output length. --binghe
    _snwprintf(buffer, SIZE_OF_SPINNER_STRING-1, L"%s|%g|%g|%g",
               (LPCTSTR) str, spin_min.dValue, spin_max.dValue, increment.dValue);
  }

  return buffer;
}

/*****************************************************************************
* void OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinButtonCtrlTwng::OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult)
{
  NM_UPDOWN *pNMUpDown = (NM_UPDOWN *)pNMHDR;
  TCHAR *szBuf = NULL;

  if (UDN_DELTAPOS == pNMHDR->code) {
    if (spinner_styles & G2_UDS_INTEGERS) {
      ldiv_t spins_from_orig;

      spins_from_orig = ldiv((current_value.lValue - defaultval.lValue), increment.lValue);
      current_value.lValue = ((pNMUpDown->iDelta + spins_from_orig.quot)
                              * increment.lValue) + defaultval.lValue;
      current_value.lValue = min(current_value.lValue, spin_max.lValue);
      current_value.lValue = max(current_value.lValue, spin_min.lValue);
    } else {
      double spins_from_orig;

      spins_from_orig = ((current_value.dValue - defaultval.dValue) / increment.dValue) +
        (double)pNMUpDown->iDelta;
      if (pNMUpDown->iDelta > 0) {
        current_value.dValue = (floor(spins_from_orig + EPSILON) * increment.dValue) +
          defaultval.dValue;
      } else {
        current_value.dValue = (ceil(spins_from_orig - EPSILON) * increment.dValue) +
          defaultval.dValue;
      }
      current_value.dValue = min(current_value.dValue, spin_max.dValue);
      current_value.dValue = max(current_value.dValue, spin_min.dValue);
    }

    szBuf = spin_value_as_text();
    // set buddy value
    m_pSpinEditTwng->SetWindowText(szBuf);
    free(szBuf);
    szBuf = NULL;
  }

  *pResult = 0;
}


/*****************************************************************************
* void PostNcDestroy ()
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments: none
*   Returns: nothing
*   Notes: Cleans up memory leaks. Caller no longer has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinButtonCtrlTwng::PostNcDestroy ()
{
  CSpinButtonCtrl::PostNcDestroy();
  delete this;
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- CSpinnerTwng Class
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


BEGIN_MESSAGE_MAP(CSpinnerTwng, CWnd)
 ON_WM_WINDOWPOSCHANGING()
 ON_WM_WINDOWPOSCHANGED()
 ON_WM_SETFOCUS()
 ON_WM_ENABLE()
END_MESSAGE_MAP()

CSpinnerTwng::CSpinnerTwng ()
{
  m_pSpinButtonCtrl = NULL;
}

CSpinnerTwng::~CSpinnerTwng ()
{
}


/*****************************************************************************
* BOOL Create (DWORD dwStyle, const RECT& rect, CWnd *pParent, UINT nID)
*
*   Description:
*   Input Arguments:
*   Returns: TRUE if creation succeeded, FALSE otherwise
*   Notes: we handle the clicks (UDN_DELTAPOS messages) ourselves, so we do
*     not need to really set the range via UDM_SETRANGE32.  But if we don't
*     send that message at all, sometimes the iDelta information sent with
*     the UDN_DELTAPOS message is backwards.  We then started sending the
*     real data, but the up/down control can only handle a range of 2^32,
*     and we support more than that.  Since it really doesn't matter what
*     the up/down control thinks its range is, just always send dummy values.
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL CSpinnerTwng::Create (DWORD dwStyle, const RECT& rect, CWnd *pParent, UINT nID)
{
  return Create(dwStyle, 0, rect, pParent, nID);
}

BOOL CSpinnerTwng::Create (DWORD dwStyle, DWORD dwEditStyle, const RECT& rect, CWnd *pParent, UINT nID)
{
  RECT rect2;
  DWORD local_style, spinner_style, edit_style;
  CSpinEditTwng *lSpinEditTwng;

  // G2 conflates the style bits intended for the top-level control, the inner
  // spin control, and the inner edit control into a single dwStyle. At this
  // point, we have no way of knowing whether the user wanted, eg,
  // UDS_ALIGNRIGHT for the spinner or ES_MULTILINE for the edit control.

  // Since this is a spinner, we will assume that all the control-specific style
  // bits (the lower 16 bits) were intended for the spin control.

  // We further assume that all of the generic style bits (the upper 16 bits)
  // apply to the top-level control.

  // When used as a cell in a grid view, dwEditStyle may be supplied.

  // One style bit we pass on to all windows, the WS_DISABLED bit.
  DWORD disabled = dwStyle & WS_DISABLED;

  local_style   = disabled | (dwStyle & 0xFFFF0000);
  edit_style    = disabled | WS_CHILD | WS_VISIBLE | dwEditStyle;
  spinner_style = disabled | WS_CHILD | WS_VISIBLE | (dwStyle & 0xFFFF);

  if(!CWnd::Create(NULL, _T("Spinner"), local_style, rect, pParent, nID))
    return FALSE;

  // the child window must be contained within the parent
  GetClientRect(&rect2);

  m_pSpinButtonCtrl = new CSpinButtonCtrlTwng;
  if (!m_pSpinButtonCtrl) return FALSE;

  if(!m_pSpinButtonCtrl->Create(spinner_style, rect2, this, ID_BUT))
	return FALSE;

  lSpinEditTwng = new CSpinEditTwng;
  if (!lSpinEditTwng) return FALSE;

  m_pSpinButtonCtrl->m_pSpinEditTwng = lSpinEditTwng;
  if(!lSpinEditTwng->CreateEx(WS_EX_CLIENTEDGE, _T("Edit"), NULL, edit_style, rect2, this, ID_EDIT))
	return FALSE;

  lSpinEditTwng->SetFont(GetParent()->GetFont()); // Propagate font

  m_pSpinButtonCtrl->SetBuddy(lSpinEditTwng);
  m_pSpinButtonCtrl->SetRange32(DUMMY_LOW_VALUE_FOR_OWNER_HANDLED_SPINNER,
								DUMMY_HIGH_VALUE_FOR_OWNER_HANDLED_SPINNER);

  lSpinEditTwng->BringWindowToTop(); // UpDown controls to need this for correct positioning
  m_pSpinButtonCtrl->ShowWindow(SW_SHOW);

  return TRUE;
}

// Propagate focus to our edit window, and select all text.
void CSpinnerTwng::OnSetFocus (CWnd *pOldWnd)
{
  CWnd::OnSetFocus(pOldWnd);
  if(GetEditCtrl()) {
	GetEditCtrl()->SetFocus();
	GetEditCtrl()->SetSel(0, -1);
  }
}

// Propagate enablement
void CSpinnerTwng::OnEnable(BOOL bEnable)
{
  CWnd::OnEnable(bEnable);
  if(GetEditCtrl())
	GetEditCtrl()->EnableWindow(bEnable);
  if(m_pSpinButtonCtrl)
	m_pSpinButtonCtrl->EnableWindow(bEnable);
}


/*****************************************************************************
* void PostNcDestroy ()
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments: none
*   Returns: nothing
*   Notes: Cleans up memory leaks. Caller no longer has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/
void CSpinnerTwng::PostNcDestroy ()
{
  CWnd::PostNcDestroy();
  delete this;
}

void CSpinnerTwng::OnWindowPosChanging(WINDOWPOS* pWndPos)
{
  if(m_pSpinButtonCtrl) {
	CRect r;
	GetClientRect(&r);
	pWndPos->cy = r.Height();	// Don't allow height to change.
	CWnd::OnWindowPosChanging(pWndPos);
	//RecalcLayout();
  } else {
	CWnd::OnWindowPosChanging(pWndPos);
  }
}

void CSpinnerTwng::OnWindowPosChanged(WINDOWPOS* pWndPos)
{
	CWnd::OnWindowPosChanged(pWndPos);
	if(m_pSpinButtonCtrl)
		RecalcLayout();

}

void CSpinnerTwng::RecalcLayout()
{
  if(!m_pSpinButtonCtrl)
	return;
  CRect r;
  GetClientRect(&r);
  GetEditCtrl()->SetWindowPos(NULL, 0, 0, r.Width(), r.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
  m_pSpinButtonCtrl->SetBuddy(GetEditCtrl());
}


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- API Functions
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* void g2pvt_set_twng_spin (CONTROLITEM *pcontrol, HWND hwndCtrl, HWND hwndDlg)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void g2pvt_set_twng_spin (CONTROLITEM *pctrl, HWND hwndCtrl, HWND hwndDlg)
{
  CWnd *pWnd;
  CSpinnerTwng *pSpin;

  pWnd = g2pvt_get_control_cwnd(pctrl->_controlId, hwndDlg);
  ASSERT(pWnd);
  pSpin = (CSpinnerTwng *)pWnd;
  if (pSpin != NULL) {
     pSpin->m_pSpinButtonCtrl->set_spin(pctrl->_mText, pctrl->_g2styles, NULL);
  }
}


/*****************************************************************************
* TCHAR *g2pvt_control_value_of_twng_spinner (HWND hwndControl)
*
*   Description: encapsulates the current state (control-value) of the TWNG
*     spinner into a string, suitable for parsing by G2
*   Input Arguments: the HWND of the spinner
*   Returns: a string containing the control value
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
TCHAR *g2pvt_control_value_of_twng_spinner (HWND hwndControl)
{
  CSpinnerTwng *pMainCtrl;
  CSpinButtonCtrlTwng *pButtonCtrl;

  pMainCtrl = (CSpinnerTwng *)CWnd::FromHandle(hwndControl);
  pButtonCtrl = pMainCtrl->m_pSpinButtonCtrl;

  return pButtonCtrl->get_control_value();
}
