// -*- Mode: C++ -*-
// ShortcutBar.h -- TWNG's shortcut bar subclass.
//

#pragma once

// Styles
#define SHORTCUT_BAR_STYLE_DEFAULT 1      // Aka "Outlook Bar"
#define SHORTCUT_BAR_STYLE_LISTBAR 2	  // Aka "List Bar"

// Opcodes. Keep in sync with lisp.
#define SHORTCUT_BAR_DESTROY 6
#define SHORTCUT_BAR_ADD_FOLDER 10
#define SHORTCUT_BAR_ADD_ITEM 11
#define SHORTCUT_BAR_CLEAR 12

#define SHORTCUT_BAR_SELECT_FOLDER 13
#define SHORTCUT_BAR_ENABLE_FOLDER 14
#define SHORTCUT_BAR_DISABLE_FOLDER 15

#define SHORTCUT_BAR_SELECT_ITEM 16
#define SHORTCUT_BAR_ENABLE_ITEM 17
#define SHORTCUT_BAR_DISABLE_ITEM 18

#define SHORTCUT_BAR_SMALL_ICONS 19
#define SHORTCUT_BAR_LARGE_ICONS 20

#define SHORTCUT_BAR_BACKGROUND_COLOR 21
#define SHORTCUT_BAR_FOREGROUND_COLOR 22

// TODO: Subclass CXTToolBox instead?
class G2ShortcutBar : public CXTOutBarCtrl
{
public:
  G2pointer m_g2pointer;

private:
  int m_handle;			// G2-assigned window handle

public:
  DECLARE_DYNCREATE(G2ShortcutBar)
  G2ShortcutBar(int handle = 0);
  virtual ~G2ShortcutBar();
  virtual int GetHandle() {return m_handle;}

public:
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
  LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);
  void SetColors(COLORREF bg, COLORREF fg);

  virtual CWnd* GetOutBarOwner() {return this;}	// Override

protected:
  afx_msg LRESULT OnOutBarNotify(WPARAM wParam, LPARAM lParam);
  virtual void PostNcDestroy();

 protected:
  DECLARE_MESSAGE_MAP()
};
