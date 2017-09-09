// DynamicTabsDlg.h : header file
//

#pragma once

#include "resource.h"
#include "dyndlgs.h"
#include "DynamicBaseDlg.h"

class CDynamicTabsDlg : public CDynamicBaseDlg
{
public:
  CDynamicTabsDlg(CWnd* pParent = NULL);   // standard constructor
  enum { IDD = IDD_TABS_DLG };

protected:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
  DECLARE_MESSAGE_MAP()
};

class CG2TabWidget: public CXTPTabControl
{
public:
  CG2TabWidget ();

  void CreateTabs (CWnd *pParent, CONTROLITEM *pcontrol, RECT *rectAdj);
  BOOL SetSelectedTab (long selected);
  void ResizeTabChildDialog (HWND hwndDlg, HWND hwndTabCtrl, TABITEM *pTabItem);
  TCHAR *GetControlValue ();

  // Generated message map functions
protected:
  //{{AFX_MSG (testtab)
  afx_msg void OnSelchange (NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnSelchanging (NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnSize (UINT nType, int cx, int cy);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP ()
protected:
  virtual void PostNcDestroy ();

private:
  void PopulateSelectedTab (CWnd *pParent, CONTROLITEM *pcontrol,TABITEM *ptabitem);
  void ParseString (TCHAR *pText);

  // Member variables
public:
  int m_nControlId;

private:
  BOOL m_bTabInitComplete;

  CString m_strToParse;
  CString m_strLabels;
  CString m_strSelected;
  CString m_strIcons;
  CString m_strPosition;
  BOOL m_bLabelsSet;
  BOOL m_bSelectedSet;
  BOOL m_bIconsSet;
  BOOL m_bPositionSet;
};
