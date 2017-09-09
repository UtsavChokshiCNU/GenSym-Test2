#if !defined(AFX_SHORTCUTBARSPLITTER_H__F44C5093_06DE_4CDC_AA2B_73D65FB65858__INCLUDED_)
#define AFX_SHORTCUTBARSPLITTER_H__F44C5093_06DE_4CDC_AA2B_73D65FB65858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShortcutBarSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarSplitter frame with splitter


class CShortcutBarSplitter : public CXTPSplitterWndEx
{
	DECLARE_DYNCREATE(CShortcutBarSplitter)

public:
	CShortcutBarSplitter();           // protected constructor used by dynamic creation

// Attributes
protected:
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutBarSplitter)
	protected:
	//}}AFX_VIRTUAL

	void TrackColumnSize(int x, int col);

// Implementation
public:
	virtual ~CShortcutBarSplitter();

	// Generated message map functions
	//{{AFX_MSG(CShortcutBarSplitter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CSplitterWndEx : public CXTPSplitterWnd
{
public:
	CSplitterWndEx()
	{
		m_cyBorder = m_cxBorder = 2;
		m_cxSplitter = m_cySplitter = 4;
		m_cySplitterGap = m_cxSplitterGap = 4;
		
		m_cxBorderShare = m_cyBorderShare = 0;
		
		
		EnableFullDrag(FALSE);
	}
	
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTBARSPLITTER_H__F44C5093_06DE_4CDC_AA2B_73D65FB65858__INCLUDED_)
