// -*- Mode: C++ -*-

#pragma once

class G2WorkspaceView : public CMDIChildWnd
{
 DECLARE_DYNCREATE(G2WorkspaceView)
public:
  G2WorkspaceView(int handle = 0);
  virtual ~G2WorkspaceView();

  LRESULT GetTabIcon(WPARAM wParam, LPARAM lParam);
  LRESULT OnSetNativeIcon(WPARAM wParam, LPARAM lParam);
  LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);

  afx_msg void OnSetIcon(WPARAM wParam, LPARAM lParam);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual int GetHandle() {return m_handle;}
  void SetBackgroundColor(COLORREF color);

public:
  afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
  afx_msg BOOL OnEraseBkgnd(CDC *pDC);

private:
  int m_handle;
  int m_icon;
  COLORREF m_bgColor;

protected:
  DECLARE_MESSAGE_MAP()
};
