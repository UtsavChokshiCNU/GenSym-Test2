/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+
+ Module:      G2CheckListBox.cpp
+
+ Copyright (C) 1986-2017 Gensym Corporation.
+            All Rights Reserved.
+
+ Author(s):
+   MS Windows portions:
+              2005 - 2006      hjg, jv
+
+ Description:  Checkable List-Box Native Custom Dialog Component
+
+
+ Key:
+   (obsolete)
+
+ File Organization:
+   Section:      INCLUDE FILES
+   Section:      DEFINES
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

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      INCLUDE FILES
%
% Description:  All required include files are referenced here.
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include "G2CheckListBox.h"
#include "cprim.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      GLOBALS
%
% Description:  Module specific typedefs, variables, & externs defined here
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
extern void g2pvt_set_up_list_box (HWND, wchar_t *, int, CONTROLITEM *);
extern wchar_t *g2pvt_get_control_value_of_list (HWND, CONTROLITEM *);
extern void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode);


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Checkable List Box
%
% Description:
%
% Notes:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
* TCHAR *g2pvt_control_value_of_check_listbox (HWND hwndControl, CONTROLITEM *pitem)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes: Note that selected and checked are reversed from the
*          string used to setup the listbox:
*              [(selected ^A) ?] ^B [(checked ^A) ?] ^B
*
*     -----
*   Modifications:
*****************************************************************************/
TCHAR *g2pvt_control_value_of_check_listbox (HWND hwndControl, CONTROLITEM *pitem)
{
  CG2CheckListBox *pListBox;
  TCHAR *ptr;
  int idx, nCount, num_chars;
  CString ReturnBuf, Entry;
  TCHAR delim = _T('\001');
  TCHAR begin_checked_token = _T('\002');

  pListBox = (CG2CheckListBox *)CWnd::FromHandle(hwndControl);
  if (pListBox == NULL)
  {
    return NULL;
  }

  // old C code that does this for regular list box
  ptr = g2pvt_get_control_value_of_list(hwndControl, pitem);
  // concatenate what's selected and the contents of the list box
  ReturnBuf += ptr;

  // Ensure terminator character is present (HQ-5524722)
  if(ReturnBuf.IsEmpty() || ReturnBuf[ReturnBuf.GetLength() - 1] != begin_checked_token)
	ReturnBuf += begin_checked_token;

  free(ptr); // free the original pointer

  nCount = pListBox->GetCount();
  if (nCount)
  {
    for (idx = 0; idx < nCount; idx++)
    {
      if (1 == pListBox->GetCheck(idx)) // look at each entry and see if it's checked
      {
	pListBox->GetText(idx, Entry);
	ReturnBuf += Entry;
	ReturnBuf += delim; // \001    // concatenate entry and add delimiter
      }
    }
  }
  num_chars = ReturnBuf.GetLength();

  // make a new C array to pass back. We can't pass back a CString.GetBuffer()
  ptr = (TCHAR *)malloc((num_chars+2) * sizeof(TCHAR));
  if (ptr)
  {
    _tcsnset(ptr, 0x00, num_chars+2);
    _tcsncpy(ptr, ReturnBuf.GetBuffer(0), num_chars);
    ptr[num_chars] = begin_checked_token;
    ptr[num_chars+1] = '\000';
  }

  return ptr;
}


/*****************************************************************************
* void PostNcDestroy ()
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments: none
*   Returns: none
*   Notes: Cleans up memory leaks. Caller no longer has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2CheckListBox::PostNcDestroy ()
{
  CCheckListBox::PostNcDestroy();

  delete this;
}


/*****************************************************************************
* void CG2CheckListBox::set_up_check_listbox (CG2CheckListBox *pListBox,
*                                             CONTROLITEM *pcontrol, int update_type)
*
*   Description: takes the "control-value" of a checkable-list-box, as a string,
*     and uses it to set up the control.
*   Input Arguments:
*   Returns:
*   Notes:
*     Format for the CheckListBox info
*       [(checked ^A) ?] ^B [(selection ^A) ?] ^B ([entry]^A)* ^B
*           ([ts-begin]^A[ts-end])?
*
*     The first group of entries are the items that will be initially checked in
*     the list-box.
*
*     When \002 is encountered, the second set of entries begins. It is the list
*     of items that will be selected in the the list-box.
*
*     When the next \002 is encountered, the third set of entries begins. It is
*     the list or items that will be contained in the list-box.
*
*     The section after the final \002 is the initial text-selection, if any.
*
*     All we actually do here is strip off the list of "checked" items, send the
*     rest of the string to the "regular" list-box code in C, and then make sure
*     the items specified to be checked are made so.
*
*     -----
*   Modifications:
*****************************************************************************/
void CG2CheckListBox::set_up_check_listbox (CG2CheckListBox *pListBox,
                                            CONTROLITEM *pcontrol, int update_type)
{
  CString StrsToAddAndSelect, StrsToCheck, StrToFind, StrsEntire, ListString;
  BOOL bNoChecks = FALSE;
  int n, i;

  if (::IsWindow(m_hWnd))
  {
    ModifyStyleEx(0, WS_EX_CLIENTEDGE);
  }

  StrsEntire = pcontrol->_mText;
  n = StrsEntire.Find(_T('\002'), 0); // looked for the initially checked items first
  if (-1 == n)
  {
    bNoChecks = TRUE;  // if there is no \002 then there are no initially checked items
    n = StrsEntire.GetLength();
  }

  StrsToAddAndSelect = StrsEntire.Right((StrsEntire.GetLength() - n) -1);

  // call the old C code that already does this part
  g2pvt_set_up_list_box(pListBox->m_hWnd, StrsToAddAndSelect.GetBuffer(0),
                        update_type, pcontrol);

  if (bNoChecks)
    return;

  StrsToCheck = StrsEntire.Left(n);
  while (TRUE)
  {
    StrToFind = StrsToCheck.SpanExcluding(_T("\001"));
    if (StrToFind.IsEmpty())
      break; // no more strings to check
    n = pListBox->GetCount();
    for (i=0; i < n; i++) // go through the entire list
    {
      pListBox->GetText(i, ListString);
      if (StrToFind == ListString)
      {
        SetCheck(i, 1); // check the entry if it's found.
        break;          // we're assuming no duplicate entries.
      }
    }
    StrsToCheck.TrimLeft(StrToFind);
    StrsToCheck.TrimLeft(_T("\001"));
    StrToFind = StrsToCheck;
  }
}


BOOL g2pvt_check_list_box_wm_command (HWND hwndDlg, long controlId,
                                      CONTROLITEM *pcontrol, int notifyCode)
{
  if ((notifyCode == LBN_SELCHANGE) || (notifyCode == CLBN_CHKCHANGE)) {
    g2pvt_ddlg_respond(hwndDlg, controlId, pcontrol->_respcode);
    return TRUE;
  }
  return FALSE;
}
