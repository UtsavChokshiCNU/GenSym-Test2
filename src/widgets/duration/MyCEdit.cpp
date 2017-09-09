// MyCEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MYCEdit.h"
#include "NewDuration1.h"

#ifdef _DEBUG
#  define new DEBUG_NEW
#  undef THIS_FILE
#endif

//
// The MyCEdit window class is a special-purpose subclass of CEdit only for use
// by the duration control, which uses two of them, one for weeks and one for
// days.
//

#define WEEKS_ID 202
#define DAYS_ID 203

BEGIN_MESSAGE_MAP(CMyCEdit, CEdit)
 ON_WM_SETFOCUS()
 ON_WM_KILLFOCUS()
 ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
END_MESSAGE_MAP()


/*****************************************************************************
* PostNcDestroy
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments:None
*   Returns: None
*   Notes: Cleans up memory leaks. Caller nolonger has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/

void CMyCEdit::PostNcDestroy() 
{
	CEdit::PostNcDestroy();
	delete this;
}


/*****************************************************************************
* CMyCEdit constructor
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CMyCEdit::CMyCEdit ()
{
  m_last_value = 0;
  m_upper_limit = -1;
}


/*****************************************************************************
* CMyCEdit destructor
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
CMyCEdit::~CMyCEdit ()
{
}

/*****************************************************************************
* void CMyCEdit::SetUpperLimit (int HighVal)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::SetUpperLimit (int HighVal)
{
  m_upper_limit = HighVal;
}


/*****************************************************************************
* void CMyCEdit::OnSetFocus (CWnd *pOldWnd)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::OnSetFocus (CWnd *pOldWnd)
{
  CEdit::OnSetFocus(pOldWnd);
  SetSel(0, -1, TRUE ); // select all three characters on focus
}


/*****************************************************************************
* void CMyCEdit::OnUpdate ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::OnUpdate ()
{
  CString cur_str;
  GetWindowText(cur_str);
  SetTypedValue(cur_str);
}


/*****************************************************************************
* void CMyCEdit::SetTypedValue (LPTSTR current_string)
*
*   Description:
*   Input Arguments:
*   Returns:
*
*   Notes: The differences between SetTypedValue and SetSpunValue are:
*     (1) SetTypedValue takes a string, whereas SetSpunValue takes an integer;
*     (2) they do different things in case of certain "invalid" values; if you
*     overflow the maximum or underflow the minimum while spinning, we just
*     wrap around.  If you enter any invalid data while typing (including
*     underflow and overflow), we simply revert to the last valid value.
*     External callers should never be calling SetWindowText directly; they
*     should go through one or the other of these functions.  -jv, 7/02/05
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::SetTypedValue (LPCTSTR current_string)
{
  long current_value;
  BOOL valid_p;
  LPTSTR stopstring;
  TCHAR display[4];

  current_value = _tcstol(current_string, &stopstring, 10);
  valid_p = (current_value >= 0)
    &&
    ((m_upper_limit == UPPER_LIMIT_UNDEFINED) ||
    (current_value <= m_upper_limit))
    &&
    (0 == wcscmp(stopstring, L""));

  if (valid_p) {
    m_last_value = current_value;
  } else {
    _sntprintf(display, 3, _T("%03d"), m_last_value);
    display[3] = (TCHAR) 0;  // final null terminator
    SetWindowText(display);
    SendNotifyOnChange();
  }
}


/*****************************************************************************
* void CMyCEdit::SetSpunValue (int val)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::SetSpunValue (int val)
{
  int temp;
  CString cur_str;
  TCHAR temp_buf[4];
  TCHAR display[4];

  GetWindowText(cur_str);
  _tcsncpy(temp_buf, cur_str, 3);
  temp = temp_buf[3] = 0;

  temp = _ttoi(temp_buf);
  temp = temp + (-1*val);

  if (m_upper_limit != UPPER_LIMIT_UNDEFINED) {
    if (temp < 0)
      temp = m_upper_limit;
    if (temp > m_upper_limit)
      temp = 0;
  }
  m_last_value = temp;

  _sntprintf(display, 3, _T("%03d"), temp);
  display[3] = (TCHAR) 0;  // final null terminator
  SetWindowText(display);
  SendNotifyOnChange();
}


/*****************************************************************************
* void CMyCEdit::SetProgrammaticValue (LPTSTR current_string)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::SetProgrammaticValue (LPTSTR current_string)
{
  long m_previous_value;
  TCHAR new_display[4];

  m_previous_value = m_last_value;
  SetTypedValue(current_string);
  if (m_previous_value != m_last_value) {
    _sntprintf(new_display, 3, _T("%03d"), m_last_value);
    new_display[3] = (TCHAR) 0;  // final null terminator
    SetWindowText(new_display);
    SendNotifyOnChange();
  }
}


/*****************************************************************************
* void CMyCEdit::OnKillFocus ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::OnKillFocus (CWnd *pNewWnd)
{
  CEdit::OnKillFocus(pNewWnd);
   int temp;
   CString cur_str;
   TCHAR temp_buf[4];
   TCHAR display[4];

   GetWindowText(cur_str);
   _tcsncpy(temp_buf, cur_str, 3);
   temp = temp_buf[3] = 0;

   temp = _ttoi(temp_buf);

   if (temp < 0)
     temp = 0;
   if (temp > m_upper_limit)
     temp = m_upper_limit;

   _sntprintf(display, 3, _T("%03d"), temp);
   display[3] = (TCHAR) 0;  // final null terminator
   SetWindowText(display);
   SendNotifyOnChange();
}


/*****************************************************************************
* void CMyCEdit::SendNotifyOnChange ()
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CMyCEdit::SendNotifyOnChange ()
{
  HWND hWnd;
  NMDATETIMECHANGE DTChange;
  WPARAM id;
  CNewDuration *pDuration;

  pDuration = DYNAMIC_DOWNCAST(CNewDuration, GetParent());
  if (!pDuration)
      return;

  if (pDuration->IsInitializing()) // if we haven't finished setting up the control, yet, send no messages 
      return;

  // I need to change this so we don't start notifying until after we init everything
  memset(&DTChange, 0x00,sizeof(DTChange));
  id = GetParent()->GetDlgCtrlID();
  DTChange.nmhdr.hwndFrom = this->m_hWnd;
  DTChange.nmhdr.idFrom = id;
  DTChange.nmhdr.code = DTN_DATETIMECHANGE;
  DTChange.dwFlags = GDT_NONE;
  hWnd = ::GetParent(m_hWnd); // this is the duration main window
  hWnd = ::GetParent(hWnd);// this is dialog
  ::SendMessage(hWnd, WM_NOTIFY, id, (LPARAM) &DTChange);

  // g2pvt_ddlg_respond(hWnd, pcontrol->_controlId, pcontrol->_respcode);
}
