// MyCDateTime.cpp : implementation file
//

#include "stdafx.h"
#include "MyCDateTime.h"
#include "NewDuration1.h"

#ifdef _DEBUG
#  define new DEBUG_NEW
#  undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMyCDateTime, CDateTimeCtrl)
 ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE, OnDatetimechange)
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

void CMyCDateTime::PostNcDestroy() 
{
	CDateTimeCtrl::PostNcDestroy();
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
CMyCDateTime::CMyCDateTime ()
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
CMyCDateTime::~CMyCDateTime ()
{
}

void CMyCDateTime::OnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
  // TODO: Add your control notification handler code here
  NMDATETIMECHANGE DTChange;
  WPARAM id;
  CWnd *pParent;
  int nRet;
  TCHAR szClassName[500];

  CNewDuration *pDuration;

  pDuration = DYNAMIC_DOWNCAST(CNewDuration, GetParent());

  if (!pDuration)
      return;

  if (pDuration->IsInitializing()) // if we haven't finished setting up the control, yet, send no messages 
      return;

  pParent = GetParent(); // main duration window
  pParent = pParent->GetParent(); // dialog box

  // The DTN_DATETIMECHANGE messages are sent via WM_NOTIFY. The grid does not handle WM_NOTIFY, and this message
  // is reflected, so we get stuck in a recursive loop if our parent is a grid.  Make sure the parent is a dialog.
  // Note that when a control is in the grid, the dialog does not expect control specific messages, so it doesn't matter
  // that we're throwing them away.
  nRet = GetClassName(pParent->m_hWnd, szClassName, sizeof(szClassName));
  if ( 0 == nRet)
	  return;
  if (_tcscmp(szClassName, _T("#32770")) != 0) // if our parent is not a CDialog #32770 return
	  return;

  memset(&DTChange, 0x00,sizeof(DTChange)); 
  id = GetParent()->GetDlgCtrlID();
  DTChange.nmhdr.hwndFrom = this->m_hWnd;
  DTChange.nmhdr.idFrom = id;
  DTChange.nmhdr.code = DTN_DATETIMECHANGE;
  DTChange.dwFlags = GDT_NONE;
   
 ::SendMessage(pParent->m_hWnd,WM_NOTIFY, id, (LPARAM) &DTChange); 
  *pResult = 0;
}
