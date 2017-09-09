//DynamicBaseDlg.h:header file
//
#pragma once

#include "resource.h"

class CDynamicBaseDlg : public CDialog
{
public:
  DECLARE_DYNCREATE(CDynamicBaseDlg)
  CDynamicBaseDlg(CWnd* pParent = NULL);
  virtual BOOL PreTranslateMessage(MSG* pMsg);

  CToolTipCtrl m_ToolTipControl;
  enum {IDD = IDD_DYNAMIC_BASE_DLG};

protected:
  virtual void PostNcDestroy();
  LRESULT OnDurationHelp(WPARAM, LPARAM);
  DECLARE_MESSAGE_MAP()
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
  void PrintMe();
  HBITMAP GetDialogImage();
};
