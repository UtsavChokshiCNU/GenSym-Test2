// -*- Mode: C++ -*-

#pragma once

class G2HtmlView : public CHtmlView
{
public:
  G2pointer m_g2pointer;

private:
  int m_handle;			// G2 handle

public:
  DECLARE_DYNCREATE(G2HtmlView)
  G2HtmlView(int handle=0);
  virtual ~G2HtmlView();
  BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual int GetHandle() {return m_handle;}

public:
  virtual void OnInitialUpdate();
  void OnTitleChange(LPCTSTR lpszText);
  void OnSize(UINT nType, int cx, int cy);
  virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
  int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg);

public:
  afx_msg void OnDestroy();
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

protected:
  void FireEvent(int event);

  // Patch from BUG: CHtmlView Leaks Memory by Not Releasing BSTRs in Several Methods
  // http://support.microsoft.com/default.aspx?scid=kb;EN-US;Q241750
public:
  CString GetFullName() const;
  CString GetType() const;
  CString GetLocationName() const;
  CString GetLocationURL() const;
  void Navigate(LPCTSTR lpszURL, DWORD dwFlags = 0 ,
		LPCTSTR lpszTargetFrameName = NULL ,
		LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL,
		DWORD dwPostDataLen = 0);

  // Add the following functions. This action prevents the leak because the
  // CHtmlView versions of LoadFromResource() call CHtmlView::Navigate(). These
  // need to be defined because CHtmlView::Navigate() is not virtual.
    BOOL LoadFromResource(LPCTSTR lpszResource);
    BOOL LoadFromResource(UINT nRes);
  // End of patch

protected:
  DECLARE_MESSAGE_MAP()
};
