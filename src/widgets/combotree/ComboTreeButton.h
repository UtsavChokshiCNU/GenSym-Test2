#if !defined(AFX_COMBOTREEBUTTON_H__95F81AFA_6D79_4258_ADD1_2FF0E97D3130__INCLUDED_)
#define AFX_COMBOTREEBUTTON_H__95F81AFA_6D79_4258_ADD1_2FF0E97D3130__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboTreeButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ComboTreeButton window

class ComboTreeButton : public CButton
{
// Construction
public:
	ComboTreeButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ComboTreeButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ComboTreeButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(ComboTreeButton)
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOTREEBUTTON_H__95F81AFA_6D79_4258_ADD1_2FF0E97D3130__INCLUDED_)
