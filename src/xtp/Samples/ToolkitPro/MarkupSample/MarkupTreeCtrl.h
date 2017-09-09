#if !defined(AFX_MARKUPTREECTRL_H__9C8085C5_3B14_4C7C_8624_D8F7EE868C02__INCLUDED_)
#define AFX_MARKUPTREECTRL_H__9C8085C5_3B14_4C7C_8624_D8F7EE868C02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkupTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarkupTreeCtrl window

class CMarkupTreeCtrl : public CXTPTreeCtrl, public CXTPMarkupContext
{
// Construction
public:
	CMarkupTreeCtrl();

// Attributes
public:

// Operations
public:
	HTREEITEM AddItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMarkupTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMarkupTreeCtrl)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	void DrawMarkupItem(NMTVCUSTOMDRAW* lpLVCD);
	HTREEITEM HitTestMarkupItem(CPoint point);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPTREECTRL_H__9C8085C5_3B14_4C7C_8624_D8F7EE868C02__INCLUDED_)
