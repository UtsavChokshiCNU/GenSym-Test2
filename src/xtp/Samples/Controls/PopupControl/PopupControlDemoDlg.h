// PopupControlDemoDlg.h : header file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"
#if !defined(AFX_POPUPWNDDEMODLG_H__375F8BC3_56DB_4F1F_9380_47F7460E9456__INCLUDED_)
#define AFX_POPUPWNDDEMODLG_H__375F8BC3_56DB_4F1F_9380_47F7460E9456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	xtpPopupThemeBlue = xtpPopupThemeCustom + 1,
	xtpPopupThemeBlack,
	xtpPopupThemeGreen,
	xtpPopupThemeRed,
	xtpPopupThemeTooltip,
	xtpPopupThemeRTF,
	xtpPopupThemeMarkup,
	xtpPopupThemeLayer,
	xtpPopupThemeCodejock,
};

/////////////////////////////////////////////////////////////////////////////
// CPopupControlDemoDlg dialog

class CPopupControlDemoDlg : public CDialog
{

// Construction
public:
	CPopupControlDemoDlg(CWnd* pParent = NULL); // standard constructor
	~CPopupControlDemoDlg();

// Dialog Data
	//{{AFX_DATA(CPopupControlDemoDlg)
	enum { IDD = IDD_POPUPWNDDEMO_DIALOG };
	CSliderCtrl m_wndSlider;
	CString m_strTrans;
	CListBox m_wndListBox;
	int m_nTheme;
	int m_nTrans;
	int m_nAnimStyle;
	UINT m_uAnimDelay;
	UINT m_uShowDelay;
	BOOL m_bAllowMove;
	SIZE m_sizePopup;
	//}}AFX_DATA

	void SetTheme(CXTPPopupControl* pPopup);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupControlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//init theme of popup window
	void SetMSNTheme(CXTPPopupControl* pPopup);
	void SetOffice2003Theme(CXTPPopupControl* pPopup);
	void SetOffice2007Theme(CXTPPopupControl* pPopup);
	void SetDefaultTheme(CXTPPopupControl* pPopup);
	void SetOfficeXPTheme(CXTPPopupControl* pPopup);
	void SetColorTheme(CXTPPopupControl* pPopup, CXTPPopupPaintManager* pPaintManager);
	void SetTooltipTheme(CXTPPopupControl* pPopup);
	void SetRTFTheme(CXTPPopupControl* pPopup);
	void SetMarkupTheme(CXTPPopupControl* pPopup);
	void SetCodejockTheme(CXTPPopupControl* pPopup);

	//enable/disable of dialog controls
	void EnableItems(BOOL bEnable);
	void SetDefaults();

// Implementation
protected:
	//handle to icon
	HICON m_hIcon;
	CPoint m_ptPopup;

#ifdef _XTP_INCLUDE_MARKUP
	void OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs);
#endif
	
	void FindBestPosition(CXTPPopupControl* pPopup, CSize szPopup);
	void AddListItem(LPCTSTR lpszItem, int nTheme, BOOL bSelect = FALSE);

	//popup window object
	CList<CXTPPopupControl*, CXTPPopupControl*> m_lstPopupControl;

	// Generated message map functions
	//{{AFX_MSG(CPopupControlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonShow();
	afx_msg void OnSelchangeComboAnimation();
	afx_msg void OnChangeEditAnimationdelay();
	afx_msg void OnChangeEditShowdelay();
	afx_msg void OnCheckAllowMove();
	afx_msg LRESULT OnPopUpNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLbnSelchangeListTheme();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// -------------------------------------------
// CPopupThemeColorBlue - Blue Color Custom Theme
// -------------------------------------------

class CPopupThemeColorBlue : public CXTPPopupPaintManager
{
public:
	virtual void DrawBackground(CDC* pDC, CXTPPopupControl* pControl, CRect rcClient);
	virtual void RefreshMetrics();

	CXTPPaintManagerColorGradient m_clrBackground2;
	CXTPPaintManagerColorGradient m_clrFrame2;
};

// -------------------------------------------
// CPopupThemeColorBlack - Black Color Custom Theme
// -------------------------------------------

class CPopupThemeColorBlack : public CPopupThemeColorBlue
{
public:
	virtual void RefreshMetrics();
};

// -------------------------------------------
// CPopupThemeColorGreen - Green Color Custom Theme
// -------------------------------------------

class CPopupThemeColorGreen : public CPopupThemeColorBlue
{
public:
	virtual void RefreshMetrics();
};

// -------------------------------------------
// CPopupThemeColorRed - Red Color Custom Theme
// -------------------------------------------

class CPopupThemeColorRed : public CPopupThemeColorBlue
{
public:
	virtual void RefreshMetrics();
};

// -------------------------------------------
// CPopupThemeCodejock - Codejock Custom Theme
// -------------------------------------------

class CPopupThemeCodejock : public CXTPPopupThemeMSN
{
public:
	virtual void DrawBackground(CDC* pDC, CXTPPopupControl* pControl, CRect rcClient);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPWNDDEMODLG_H__375F8BC3_56DB_4F1F_9380_47F7460E9456__INCLUDED_)
