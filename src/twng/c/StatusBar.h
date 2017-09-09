// -*- Mode: C++ -*-

#pragma once

#define ID_INDICATOR_SSL  0xE70A // Built-in indicators, from MFC's E7xx range.
#define ID_INDICATOR_PROG 0xE70B
#define PANE_ID_OFFSET    0xE710

#define SB_LEFT_CLICK 1		// Event codes
#define SB_MIDDLE_CLICK 2
#define SB_RIGHT_CLICK 3

#define SB_HIDE  0		// Opcodes
#define SB_SHOW  1
#define SB_TEXT 2
#define SB_RESET  3
#define SB_MINHEIGHT 4
#define SB_UPDATE 5
#define SB_ADD_PANE  6
#define SB_REMOVE_PANE  7
#define SB_PANE_TEXT  8
#define SB_PANE_WIDTH  9
#define SB_PANE_VISIBLE  10
#define SB_PANE_FOREGROUND  11
#define SB_PANE_BACKGROUND  12
#define SB_PANE_ICON  13
#define SB_PANE_ALIGNMENT  14
#define SB_PANE_TOOLTIP  15
#define SB_PANE_ENABLED  16
#define SB_PANE_BORDERS  17

class G2StatusBar : public CXTPStatusBar
{
private:
  CProgressCtrl m_wndProgCtrl;	// One built-in progress control

public:
  DECLARE_DYNCREATE(G2StatusBar)
  G2StatusBar();
  virtual ~G2StatusBar();

public:
  BOOL m_securityIndicator;
  LPCSTR m_securityIcon;
  LPCSTR m_securityTooltip;

public:
  void Click(UINT button, UINT nFlags, CPoint point, BOOL doubleClick=FALSE);
  BOOL Reset();
  void SetSecurityIndicator(BOOL enable, LPCSTR szIcon, LPCSTR tooltip);
  void SetIconIndicator(int id, BOOL enable, LPCSTR szIcon, LPCSTR tooltip);

  CProgressCtrl *EnsureProgressBar(int id);
  void RemoveProgressBar(int id);

  void AddPane(UINT nID, LPCWSTR pText=NULL, int icon=-1, int pos=-1);
  void SetPaneIcon(CXTPStatusBarPane *pPane, int native_icon);
  void SetPaneEnabled(CXTPStatusBarPane *pPane, BOOL enable);
  void SetPaneBorders(CXTPStatusBarPane *pPane, BOOL enable);
  void SetPaneStretch(CXTPStatusBarPane *pPane, BOOL enable);
  void Update();
  void SendEvent(int eventCode, int paneID = 0, int bits = 0);

protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
  afx_msg LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);
};
