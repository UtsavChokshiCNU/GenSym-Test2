// NativeView.h -- Base class for G2 native views

#pragma once
#include "IDestroyListener.h"

#define ON_NATIVE_VIEW_MESSAGES() \
 ON_WM_DESTROY() \
 ON_WM_SETFOCUS() \
 ON_WM_SIZE() \
 ON_WM_KEYDOWN() \
 ON_WM_SYSKEYDOWN() \
 ON_WM_CHAR() \
 ON_WM_LBUTTONDOWN() \
 ON_WM_LBUTTONUP() \
 ON_WM_MBUTTONDOWN() \
 ON_WM_RBUTTONDOWN() \
 ON_WM_RBUTTONUP() \
 ON_WM_LBUTTONDBLCLK() \
 ON_WM_MBUTTONDBLCLK() \
 ON_WM_RBUTTONDBLCLK() \
 ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged) \
 ON_MESSAGE(WM_PARENT_CHANGED, OnParentChanged)

template <class TBase>
class G2NativeView : public TBase
{
protected:
  int m_handle;			// Control handle (G2-assigned)
  BOOL m_consumedKey;

public:
  G2pointer m_g2pointer;	// TODO: deprecate

public:
virtual int GetHandle() {return m_handle;} // TODO: deprecate

G2NativeView(int handle): destroyListener(0)
{
  m_handle = handle;
  m_consumedKey = FALSE;
  m_g2pointer = -1;
  SAVE_WND();
  VTRACE("TBase::Construct [%d] ", m_handle); POB(this);
}

virtual ~G2NativeView()
{
  VTRACE("Destruct  [%d] ", m_handle); POB(this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
}

void OnDestroy()
{
  VTRACE("OnDestroy [%d] ", m_handle); POB(this);
  if (destroyListener) destroyListener->fire();
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  TBase::OnDestroy();
}

void OnSetFocus(CWnd* pOldWnd)
{
  VTRACE("G2NativeView::OnSetFocus [%d] ", m_handle); POB(this);
  TBase::OnSetFocus(pOldWnd);
  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void OnSize(UINT nType, int cx, int cy)
{
  VTRACE("G2NativeView::OnSize [%d] type:%d %dx%d ", m_handle, nType, cx, cy); POB(this);
  TBase::OnSize(nType, cx, cy);
  g2pvt_view_sized(this, m_handle);
}

void OnKeyDown(UINT vKey, UINT nRepCnt, UINT scanCode)
{
  if(KeyPress(vKey, scanCode))
    TBase::OnKeyDown(vKey, nRepCnt, scanCode);
  AfterKeyPress(vKey, scanCode);
}

void OnSysKeyDown(UINT vKey, UINT nRepCnt, UINT scanCode)
{
  if(KeyPress(vKey, scanCode))
    TBase::OnSysKeyDown(vKey, nRepCnt, scanCode);
  AfterKeyPress(vKey, scanCode);
}

void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  if(!m_consumedKey)
    TBase::OnChar(nChar, nRepCnt, nFlags);
  m_consumedKey = FALSE;
  AfterKeyPress(nChar, 0);
}

void OnLButtonDown(UINT flags, CPoint p)
{
  if(MouseClick(WM_LBUTTONDOWN, flags, p))
    TBase::OnLButtonDown(flags, p);
  AfterMouseClick(WM_LBUTTONDOWN, flags, p);
}

void OnLButtonUp(UINT flags, CPoint p)
{
	if(MouseClick(WM_LBUTTONUP, flags, p))
		TBase::OnLButtonDown(flags, p);
	AfterMouseClick(WM_LBUTTONUP, flags, p);
}

void OnMButtonDown(UINT flags, CPoint p)
{
  if(MouseClick(WM_MBUTTONDOWN, flags, p))
    TBase::OnMButtonDown(flags, p);
  AfterMouseClick(WM_MBUTTONDOWN, flags, p);
}

void OnRButtonDown(UINT flags, CPoint p)
{
  if(MouseClick(WM_RBUTTONDOWN, flags, p))
    TBase::OnRButtonDown(flags, p);
  AfterMouseClick(WM_RBUTTONDOWN, flags, p);
}

void OnRButtonUp(UINT flags, CPoint p)
{
	if(MouseClick(WM_RBUTTONUP, flags, p))
		TBase::OnRButtonUp(flags, p);
  AfterMouseClick(WM_RBUTTONUP, flags, p);
}

void OnLButtonDblClk(UINT flags, CPoint p)
{
  if(MouseClick(WM_LBUTTONDBLCLK, flags, p))
    TBase::OnLButtonDblClk(flags, p);
  AfterMouseClick(WM_LBUTTONDBLCLK, flags, p);
}

void OnMButtonDblClk(UINT flags, CPoint p)
{
  if(MouseClick(WM_MBUTTONDBLCLK, flags, p))
    TBase::OnMButtonDblClk(flags, p);
  AfterMouseClick(WM_MBUTTONDBLCLK, flags, p);
}

void OnRButtonDblClk(UINT flags, CPoint p)
{
  if(MouseClick(WM_RBUTTONDBLCLK, flags, p))
    TBase::OnRButtonDblClk(flags, p);
  AfterMouseClick(WM_RBUTTONDBLCLK, flags, p);
}

LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  return 0;
}

LRESULT OnParentChanged(WPARAM/*BOOL*/ isDialog, LPARAM/*HWND*/ hwndNewParent)
{
  return 0;
}


  void setDestroyListener(IDestroyListener* listener)
  {
    destroyListener = listener;
  }

// Overrides
protected:
virtual BOOL MouseClick(UINT msg, UINT flags, CPoint p)
{
  return TRUE;
}

virtual BOOL KeyPress(UINT vKey, UINT scanCode)
{
  return TRUE;
}

virtual void AfterMouseClick(UINT msg, UINT flags, CPoint p)
{
}

virtual void AfterKeyPress(UINT vKey, UINT scanCode)
{
}

virtual void PostNcDestroy()
{
  TBase::PostNcDestroy();
  delete this;
}

private:
  IDestroyListener* destroyListener;
};
