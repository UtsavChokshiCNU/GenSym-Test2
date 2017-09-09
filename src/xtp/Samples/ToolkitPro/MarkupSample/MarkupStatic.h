#if !defined(AFX_MARKUPSTATIC_H__9851CB9F_CEAA_444A_87BB_C508D160702B__INCLUDED_)
#define AFX_MARKUPSTATIC_H__9851CB9F_CEAA_444A_87BB_C508D160702B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkupStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarkupStatic window

class CMarkupStatic : public CStatic, public CXTPMarkupContext
{
// Construction
public:
	CMarkupStatic();

// Attributes
public:

// Operations
public:
	void SetMarkupText(LPCSTR lpszMarkup);

// Implementation
public:
	virtual ~CMarkupStatic();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	//{{AFX_VIRTUAL(CMarkupStatic)
	BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMarkupStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	CXTPMarkupUIElement* m_pUIElement;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPSTATIC_H__9851CB9F_CEAA_444A_87BB_C508D160702B__INCLUDED_)
