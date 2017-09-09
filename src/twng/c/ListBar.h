// -*- Mode: C++ -*-
// ListBar.h -- TWNG's Outlook 2003 shortcut bar subclass.
//

#pragma once

// TODO: Subclass CXTToolBox instead?

class G2ListBarPane;

class G2ListBar : public CXTPShortcutBar
{
public:
  G2pointer m_g2pointer;

private:
  int m_handle;			// G2-assigned window handle

public:
  COLORREF m_clrBack;
  COLORREF m_clrText;

public:
  DECLARE_DYNCREATE(G2ListBar)
  G2ListBar(int handle = 0);
  virtual ~G2ListBar();
  virtual int GetHandle() {return m_handle;}

public:
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  LRESULT OnListBarNotify(WPARAM wParam, LPARAM lParam);

public:
  G2ListBarPane *GetPane(int nFolder = -1);
  CListCtrl *GetListCtrl(int nFolder = -1);
  void SetColors(COLORREF bg, COLORREF fg);
  LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);
  int AddFolder(LPCTSTR caption, int icon, LPCTSTR tooltip);
  void AddTextItem(LPCTSTR label, int nFolder, int icon, LPCTSTR tooltip);
  void AddWindowItem(LPCTSTR caption, int nFolder, CWnd *pWnd);
  void SelectItemInFolder(int nFolder, int nIndex);
  void SetLargeIcons(BOOL large);

protected:
  virtual void PostNcDestroy();

 protected:
  DECLARE_MESSAGE_MAP()
};

// A pane within the listbar.
class G2ListBarPane : public CXTPShortcutBarPane
{
public:
  G2ListBarPane(int nFolder = 0);
  virtual ~G2ListBarPane();
  BOOL Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent, COLORREF bg, COLORREF fg);
  CListCtrl *GetListCtrl();
  CListCtrl *EnsureListCtrl();
  int GetHandle();
  void FireEvent(UINT nType, int nItem = -1);
  int SelectedItem();
  BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
  void Reposition();
  void OnParentNotify(UINT message, LPARAM lParam);

public:
  int m_nFolder;

private:
  CListCtrl m_listCtrl;		// Not used if only view items are added.
  COLORREF m_bg, m_fg;

 protected:
  DECLARE_MESSAGE_MAP()
};

extern int g2pvt_create_list_bar(int handle, LPWSTR title,
				 int x, int y, int width, int height,
				 int dock, int neighborID, int min_width, int min_height);
extern int g2pvt_manage_list_bar(int opcode, int handle, LPWSTR string, 
				 int nFolder, int icon, LPWSTR tooltip);
