// MySpinButton.cpp : implementation file
//

#include "stdafx.h"
#include "MySpinButton.h"
#include "MyCEdit.h"


#ifdef _DEBUG
#  define new DEBUG_NEW
#  undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CMySpinButton, CSpinButtonCtrl)
 ON_NOTIFY_REFLECT(UDN_DELTAPOS, OnDeltapos)
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

void CMySpinButton::PostNcDestroy() 
{
	CSpinButtonCtrl::PostNcDestroy();

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
CMySpinButton::CMySpinButton ()
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
CMySpinButton::~CMySpinButton ()
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
void CMySpinButton::SetBuddy (CMyCEdit *pEdit)
{
  CSpinButtonCtrl::SetBuddy(pEdit);
  if (pEdit)
	pEdit->SetSpunValue(0);
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
void CMySpinButton::OnDeltapos (NMHDR *pNMHDR, LRESULT *pResult)
{
  NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
  CMyCEdit *pEdit = (CMyCEdit*)GetBuddy();
  if (pEdit)
    if (pEdit->IsKindOf(RUNTIME_CLASS(CEdit)))
      pEdit->SetSpunValue(pNMUpDown->iDelta);
    *pResult = 0;
}
