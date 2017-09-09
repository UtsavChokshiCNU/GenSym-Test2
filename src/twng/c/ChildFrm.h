// ChildFrm -- Container for non-workspace-views

#pragma once

class CChildFrm : public CMDIChildWnd
{
 DECLARE_DYNCREATE(CChildFrm)
public:
  CChildFrm(int handle = 0);
  virtual ~CChildFrm();
  BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual int GetHandle() {return m_handle;}

private:
  int m_handle;
  int m_icon;

public:
  LRESULT GetTabIcon(WPARAM wParam, LPARAM lParam);
  LRESULT OnSetNativeIcon(WPARAM wParam, LPARAM lParam);
  LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);
  afx_msg void OnSysCommand(UINT nID, LONG lParam);
  afx_msg void OnWindowPosChanging(WINDOWPOS *pos);
  afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT nMsg);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnMove(int x, int y);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg LRESULT OnEnterSizeMove(WPARAM, LPARAM);
  afx_msg LRESULT OnExitSizeMove(WPARAM, LPARAM);
  afx_msg LRESULT OnEnterMenuLoop(WPARAM, LPARAM);
  afx_msg LRESULT OnExitMenuLoop(WPARAM, LPARAM);
  afx_msg void OnDestroy();

protected:
  DECLARE_MESSAGE_MAP()
};
