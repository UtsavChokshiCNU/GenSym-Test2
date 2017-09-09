////////////////////////////////////////////////////////////////
// MSDN -- September 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
// Modified from MSDN Magazine -- September 2000 PupText.h

#pragma once

//////////////////
// Get NONCLIENTMETRICS info: ctor calls SystemParametersInfo.
//
class CNonClientMetrics : public NONCLIENTMETRICS {
public:
	CNonClientMetrics() {
		cbSize = sizeof(NONCLIENTMETRICS);
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS,0,this,0);
	}
};

//////////////////
// Popup text window, like tooltip.
// Can be right or left justified relative to creation point.
//
class CPopupText : public CWnd {
public:
	CSize m_szMargins;		// extra space around text: change if you like
	enum {JUSTIFYLEFT=0, JUSTIFYRIGHT};
	enum {DELAYTIMER=1, OUTOFWINDOWTIMER=2};

	CPopupText();
	virtual ~CPopupText();
	BOOL Create(CPoint pt, CWnd* pParentWnd, UINT nStyle=0, UINT nID=0);
	void ShowDelayed(UINT msec);
	void Cancel();
	BOOL MovedOutside () { return m_bMovedOutside; }

protected:
	CFont	m_font;				// font to use (same as tooltips)
	UINT	m_nStyle;			// style (see enum below)

	UINT m_DelayTimer;
	UINT m_MoveOutsideTimer;
	BOOL m_bMovedOutside;

	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void StopDelayTimer();
	void StopMoveOutsideTimer();
	void ShowPopup();

	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnSetText(WPARAM wp, LPARAM lp);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

	DECLARE_DYNAMIC(CPopupText);
	DECLARE_MESSAGE_MAP();
};
