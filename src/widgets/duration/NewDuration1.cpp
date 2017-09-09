// NewDuration1.cpp : implementation file
//

#include "stdafx.h"
#include "NewDuration1.h"
#include "MyCDateTime.h"

UINT wm_get_tool_tip;			// FIXME
#define DURATION_CONTROL_TOOLTIP _T("Weeks:Days:Hours:Minutes:Seconds")

#ifdef _DEBUG
#  define new DEBUG_NEW
#  undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNewDuration, CWnd)

BEGIN_MESSAGE_MAP(CNewDuration, CWnd)
 ON_WM_ENABLE()
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

void CNewDuration::PostNcDestroy()
{
  CWnd::PostNcDestroy();
  delete this;
}


/*****************************************************************************
*
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CNewDuration::SetToolTip ()
{
  CWnd *pParent;
  CToolTipCtrl *pTip;
  wm_get_tool_tip = RegisterWindowMessage(_T("Get Tool Tip Control"));

  // FIXME: Get the tooltip control from the main frame instead.

  pParent = GetParent();
  if (!pParent->IsKindOf(RUNTIME_CLASS(CDialog)))
  {
     // if our parent is not a dialog, we're on the grid; so go up a level
     pParent = pParent->GetParent();  
  }

  pTip = (CToolTipCtrl *)pParent->SendMessage(wm_get_tool_tip,0,0);
  if (!pTip)
	return;

  pTip->AddTool(pEdit, DURATION_CONTROL_TOOLTIP);
  pTip->AddTool(pButton,DURATION_CONTROL_TOOLTIP);
  pTip->AddTool(pEdit2,DURATION_CONTROL_TOOLTIP);
  pTip->AddTool(pButton2,DURATION_CONTROL_TOOLTIP);
  pTip->AddTool(pDateTime,DURATION_CONTROL_TOOLTIP);
}


CNewDuration::~CNewDuration ()
{
}


/*****************************************************************************
*
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CNewDuration::OnEnable (BOOL bEnable)
{
  CWnd::OnEnable(bEnable);

  pEdit->EnableWindow(bEnable);
  pButton->EnableWindow(bEnable);
  pEdit2->EnableWindow(bEnable);
  pButton2->EnableWindow(bEnable);
  pDateTime->EnableWindow(bEnable);
}


/*****************************************************************************
* void CNewDuration::SetCurrentDurationValue (TCHAR *pTextValue)
*
*   Description: parses the given string, and sets the duration control's
*     values to the results of the parse.
*   Input Arguments:
*   Returns:
*   Notes: in theory, could be used at any time, but in practice, only
*     called when constructing a new duration control.  In that sense,
*     it might as well be named SetInitialDurationValue.
*
*     -----
*   Modifications:
*****************************************************************************/
void CNewDuration::SetCurrentDurationValue (LPCTSTR pTextValue)
{
  int hours;
  int minutes;
  int seconds;
  LPTSTR pszTemp, token;
  TCHAR seps[] = _T(":");

  if (!pTextValue)
    return;

  pszTemp = _tcsdup(pTextValue);
  if (pszTemp == NULL)
    return;

  token = _tcstok(pszTemp, seps);
  if(token)
	pEdit->SetProgrammaticValue(token); // weeks

  token = _tcstok(NULL, seps);
  if(token)
	pEdit2->SetProgrammaticValue(token); // days

  hours = minutes = seconds = 0;

  token = _tcstok(NULL, seps);
  if(token)
	hours = _ttoi(token);

  token = _tcstok(NULL, seps);
  if(token)
	minutes = _ttoi(token);

  token = _tcstok(NULL, seps);
  if(token)
	seconds = _ttoi(token);

  free(pszTemp);

  CTime initialInterval(2000, 1, 1, hours, minutes, seconds);
  ASSERT(::IsWindow(m_hWnd));
  if (::IsWindow(m_hWnd)) {
    pDateTime->SetTime(&initialInterval);
  }

  ClearInitializing();// enable WM_NOTIFY
}


/*****************************************************************************
*
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CNewDuration::SetInitializing ()
{
  m_bIsInitializing = TRUE;
}


/*****************************************************************************
*
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
void CNewDuration::ClearInitializing ()
{
  m_bIsInitializing = FALSE;
}



/*****************************************************************************
*
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL CNewDuration::IsInitializing ()
{
  return m_bIsInitializing;
}


/*****************************************************************************
*
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
BOOL CNewDuration::Create (DWORD dwStyle, const RECT& rect, CWnd *pParentWnd, UINT nID)
{
  BOOL bEnabled = TRUE;
  int width_unit;
  int total_width;
  int up_down_width;
  DWORD dwExStyle;
  RECT butRect, editRect, but2Rect, edit2Rect, edit3Rect, in_rect;

  SetInitializing(); // prevent WM_NOTIFY during setup

  if (WS_DISABLED & dwStyle) // initially disable, if neccessary
    bEnabled = FALSE;    // save this and enable/disable later
  dwStyle = dwStyle & (~WS_DISABLED); // the init

  if(!CWnd::Create(NULL, _T("Duration"), WS_CHILD | dwStyle, rect, pParentWnd, nID))
    return FALSE;

  ModifyStyleEx(0,WS_EX_CONTROLPARENT);	// Assuming our parent is a dialog window.

  GetClientRect(&in_rect);

  // set the control up in these porportions

  // EDIT_MULTIPLIER*width_unit + EDIT_MULTIPLIER*width_unit +
  // DATETIME_MULTIPLIER*width_unit = totalwidth;

  total_width = in_rect.right - in_rect.left;

  width_unit = total_width/( EDIT_MULTIPLIER + EDIT_MULTIPLIER + DATETIME_MULTIPLIER);

  up_down_width = (EDIT_MULTIPLIER*width_unit)/UPDOWN_DENOMINATOR;

  butRect = in_rect;
  butRect.right = in_rect.left+up_down_width;
  but2Rect = butRect;

  editRect = in_rect;

  editRect.left = in_rect.left;
  editRect.right = in_rect.left + EDIT_MULTIPLIER*width_unit;

  edit2Rect = in_rect;

  edit2Rect.left = editRect.right+1;
  edit2Rect.right = edit2Rect.left + EDIT_MULTIPLIER*width_unit;

  edit3Rect = in_rect;
  edit3Rect.left = edit2Rect.right + 1;
  edit3Rect.right = in_rect.right; // make sure we fill the entire space

  pDateTime = new CMyCDateTime();
  pDateTime->Create(WS_TABSTOP | WS_VISIBLE| DTS_TIMEFORMAT | DTS_RIGHTALIGN, edit3Rect, this, ID_EDIT3);
  pDateTime->SetFormat(_T("HH':'mm':'ss"));

  dwStyle = pDateTime->GetStyle(); //  get the style so we can use it
  dwStyle = dwStyle & ~DTS_TIMEFORMAT;
  dwStyle = dwStyle & ~DTS_RIGHTALIGN;
  dwExStyle = pDateTime->GetExStyle(); // get the extended style so we can use

  UINT btnStyle = WS_VISIBLE | WS_CHILD | UDS_ARROWKEYS | UDS_ALIGNRIGHT;
  UINT editStyle = WS_VISIBLE | WS_CHILD | WS_TABSTOP;

  // The datetime control seems to use it's own default styles.
  // Let's get them and re-use on the other windows, so things look relatively
  // the same.  Later we'll use WindowEnable to set the enable/disable bit.

  CFont *dtmFont = pDateTime->GetFont(); // get the DateTime font and use that

  pButton = new CMySpinButton();
  pEdit = new CMyCEdit();
  pButton->Create(btnStyle, butRect, this, ID_BUT);
  pEdit->CreateEx(dwExStyle, _T("Edit"), NULL, editStyle, editRect, this, ID_EDIT);
  pEdit->SetFont(dtmFont);
  pEdit->SetUpperLimit(999);
  pEdit->SetTypedValue(_T("0"));
  pButton->SetBuddy(pEdit);

  pButton2 = new CMySpinButton();
  pEdit2 = new CMyCEdit();
  pButton2->Create(btnStyle, but2Rect, this, ID_BUT2);
  pEdit2->CreateEx(dwExStyle, _T("Edit"), NULL, editStyle, edit2Rect, this, ID_EDIT2);
  pEdit2->SetFont(dtmFont);
  pEdit2->SetUpperLimit(365);
  pEdit2->SetTypedValue(_T("0"));
  pButton2->SetBuddy(pEdit2);

  // Adjust tab order by adjusting the Z order.
  pDateTime->BringWindowToTop();
  pEdit2->BringWindowToTop();
  pEdit->BringWindowToTop();

  EnableWindow(bEnabled); // initially disable, if neccessary

  SetToolTip();
  return TRUE;
}

// Compute the duration value. Also sets window's text for good measure.
void CNewDuration::ReComputeWindowText(CString& str)
{
  CString weeks, days, hms;

  pEdit->GetWindowText(weeks);
  pEdit2->GetWindowText(days);
  pDateTime->GetWindowText(hms);

  str = weeks + _T(":") + days + _T(":") + hms;
  SetWindowText(str);
}

// Returns a newly allocated string.
TCHAR *g2pvt_control_value_of_duration(HWND hwndControl)
{
  CNewDuration *pDuration = DYNAMIC_DOWNCAST(CNewDuration, CWnd::FromHandlePermanent(hwndControl));
  CString str;
  if(pDuration)
	pDuration->ReComputeWindowText(str);
  return _tcsdup(str);
}
