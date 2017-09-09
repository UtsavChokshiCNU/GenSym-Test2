#if !defined(AFX_PAGECOMBOBOX_H__17A13E29_3B64_4956_9D9D_11AEABC6518E__INCLUDED_)
#define AFX_PAGECOMBOBOX_H__17A13E29_3B64_4956_9D9D_11AEABC6518E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageComboBox dialog

class CPageComboBox : public CXTPResizePropertyPage
{
	DECLARE_DYNCREATE(CPageComboBox)

// Construction
public:
	CPageComboBox();
	~CPageComboBox();

// Dialog Data
	//{{AFX_DATA(CPageComboBox)
	enum { IDD = IDD_PAGE_COMBOBOX };
	CXTPComboBox	m_cmbDropDown;
	CXTPComboBox	m_cmbDropDownList;
	BOOL	m_bEnabled;
	BOOL	m_bFlatStyle;
	int		m_nTheme;
	BOOL	m_bUseVisualStyle;
	BOOL	m_bAutoComplete;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageComboBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageComboBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadTheme();
	afx_msg void OnCheckFlatstyle();
	afx_msg void OnCheckWinxpThemes();
	afx_msg void OnCheckEnabled();
	afx_msg void OnCheckAutocomplete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECOMBOBOX_H__17A13E29_3B64_4956_9D9D_11AEABC6518E__INCLUDED_)
