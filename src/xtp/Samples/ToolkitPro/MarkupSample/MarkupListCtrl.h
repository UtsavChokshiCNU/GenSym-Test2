#if !defined(AFX_MARKUPLISTCTRL_H__06229B33_231D_466F_A764_F8C47946C163__INCLUDED_)
#define AFX_MARKUPLISTCTRL_H__06229B33_231D_466F_A764_F8C47946C163__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkupListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
class CXTPMarkupUIElement;

/////////////////////////////////////////////////////////////////////////////
// CMarkupListCtrl window
struct MARKUP_LISTITEM
{
public:
	MARKUP_LISTITEM(CXTPMarkupContext* pContext);
	~MARKUP_LISTITEM();

public:
	void Resolve(LPCTSTR lpszMarkup);

	CString strMarkup;
	CXTPMarkupUIElement* pItem;
	CXTPMarkupContext* pContext;
};


class CMarkupListCtrl : public CXTPListBox, public CXTPMarkupContext
{
// Construction
public:
	CMarkupListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupListCtrl)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMarkupListCtrl();
	void Init();

	void ItemChanged(MARKUP_LISTITEM* pItem);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMarkupListCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPLISTCTRL_H__06229B33_231D_466F_A764_F8C47946C163__INCLUDED_)
