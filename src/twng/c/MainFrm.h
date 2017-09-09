// -*- Mode: C++ -*-

#pragma once

#include "StatusBar.h"

class CWndState {
  CRect m_rect;
  UINT m_style;
  UINT m_styleEx;
};

///////////////////////////////////////////////////////////////////
// CG2CommandBars class provides CXTPCommandBars interface
//  and calls g2pvt_enter_modal_loop() when ContextMenu() is called to avoid TWNG suspending
class CG2CommandBars : public CXTPCommandBars
{
  DECLARE_DYNCREATE(CG2CommandBars)

public:
  virtual void ContextMenu(CXTPToolBar* pToolBar, CPoint point);
};

///////////////////////////////////////////////////////////////////
// CG2DockingPaneTabbedContainer class provides CXTPDockingPaneTabbedContainer interface
//  and calls g2pvt_enter_modal_loop() when left mouse button is pressed to avoid TWNG suspending
class CG2DockingPaneTabbedContainer : public CXTPDockingPaneTabbedContainer
{
  DECLARE_DYNAMIC(CG2DockingPaneTabbedContainer)

public:
  CG2DockingPaneTabbedContainer(CXTPDockingPaneLayout* pLayout);

protected:
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////
// CG2DockingPaneMiniWnd class provides CXTPDockingPaneMiniWnd interface
//  and calls g2pvt_enter_modal_loop() when left mouse button is pressed to avoid TWNG suspending
class CG2DockingPaneMiniWnd : public CXTPDockingPaneMiniWnd
{
  DECLARE_DYNAMIC(CG2DockingPaneMiniWnd)

public:
  CG2DockingPaneMiniWnd(CXTPDockingPaneLayout* pLayout);

protected:
  afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
  afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);

  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////
// CG2DockingPaneManager class provides CXTPDockingPaneManager interface
//  and is used to create own Pane Tabbed Container
class CG2DockingPaneManager : public CXTPDockingPaneManager
{
protected:
  virtual CXTPDockingPaneBase* OnCreatePane(XTPDockingPaneType type, CXTPDockingPaneLayout* pLayout);
};

//////////////////////////////////////////////////////////////////////
// CMainFrame class
//////////////////////////////////////////////////////////////////////
class CMainFrame : public CXTPMDIFrameWnd
{
  DECLARE_DYNAMIC(CMainFrame)
// Overrides
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
  CMainFrame();
  virtual ~CMainFrame();
  BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs);
  CDocument *GetActiveDocument();
  G2StatusBar *GetStatusBar() {return &m_wndStatusBar;}
  CXTPTabClientWnd * GetTabClientWnd() {return &m_MTIClientWnd;}

  void SetTheme(int theme);
  void SetMenuSize(int menusize); //HQ-5476610 new procedure added to increase the menu font size;called by g2pvt_change_menu_size

  void ShowDefaultMenuBar(BOOL show = TRUE);
  CXTPCommandBar* GetMenuBarSource() {return m_pMenuBarSource;}
  void SetMenuBarSource(CXTPCommandBar* pBar) {m_pMenuBarSource = pBar;}

  CXTPDockingPaneManager* GetDockingPaneManager() {return &m_paneManager;}
  void DockToolBar(CXTPToolBar* pBar, XTPBarPosition side, CXTPToolBar* pNeighbor);

  CMDIChildWnd *WrapWnd(CWnd *pWnd, int handle, int x, int y, int width, int height,
			int dock, int neighbor, CSize minSize, LPWSTR title = NULL, int icon = 0);
  void SaveWnd(CWnd *pWnd, int handle);
  CWnd *FindWnd(int handle, CRuntimeClass *pClass = NULL);
  void ForgetWnd(int handle);
  void DestroyWnd(int handle);
  HWND CoorHwnd();

  int ManageMDIMode(int opcode, int arg);
  BOOL IsTabbedMDI() {return m_MTIClientWnd.IsAttached();}
  BOOL IsBogusResize(HWND hwnd, int cx, int cy);

  void SetMenuIconSize(int);

public:
  CImageList m_smallImageList;		 // Attached to native icons HIMAGELISTs
  CImageList m_largeImageList;
  CMap<int,int,CWnd*,CWnd*> m_windows;	 // G2 handle -> CWnd*
  CMap<int,int,CWndState,CWndState&> m_wndStates; // G2 handle -> Saved wnd state for normal MDI mode

protected:
  CXTPCommandBar* m_pMenuBarSource;	 // If non-NULL, menubar is a *clone* of this.
  CG2DockingPaneManager m_paneManager;

  G2StatusBar  m_wndStatusBar;
  CXTPTabClientWnd m_MTIClientWnd;

public:
  CXTPDockingPane* CreatePane(int handle, CString strTitle, 
			      int x, int y, int width, int height,
			      int dock, int neighborID, int icon, int *status, CSize minSize);
  int StoreNativeIcon(int native_icon);
  void SetPaneIcon(CXTPDockingPane *pPane, int native_icon);
  void ClearAllNativeIcons();
  void UpdateMDIChildIcons(int native_icon);

  void IconChanged(int changed_icon, int where);
  void RefreshChildIcon(CWnd *pChild, int changed_icon);
  void UpdateToolbarIcons(int native_icon);
  void UpdateWndIcons(int native_icon);
  void UpdatePaneIcons(int native_icon);
  void SetWindowCloseable(CWnd *pWnd, BOOL torf);

protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSysCommand(UINT nID, LPARAM);
  afx_msg void OnCustomize();	// Disabled
  afx_msg LRESULT OnInitMenuBar(WPARAM wParam, LPARAM lParam);
  afx_msg void OnInitCommandsPopup(CXTPPopupBar* pCommandBar);
  afx_msg LRESULT OnUnInitCommandsPopup(WPARAM,LPARAM);
  afx_msg LRESULT OnControlSelected(WPARAM,LPARAM);
  afx_msg LRESULT OnNewTabItem(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnTabClick(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnModalLoop(WPARAM wParam, LPARAM lParam);
  afx_msg void OnUpdateMDIButton(CCmdUI *pCmdUI);

  afx_msg BOOL OnExecuteNMS(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnUpdateNMSCommand(CCmdUI *pCmdUI);

  afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnListBarNotify(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnPropertyGridNotify(WPARAM wParam, LPARAM lParam);
  afx_msg void onMDIWindowList();
  //Added for gensym-3031 by Suzsoft
  afx_msg LRESULT OnReleasePopup(WPARAM wParam, LPARAM lParam);
 //End of adding
  //}}AFX_MSG
  void OnClose();
  DECLARE_MESSAGE_MAP()
};
