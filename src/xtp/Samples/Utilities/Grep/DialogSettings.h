#if !defined(AFX_DIALOGSETTINGS_H__707B10E3_CCE0_42FC_8AB5_6A905FF14B43__INCLUDED_)
#define AFX_DIALOGSETTINGS_H__707B10E3_CCE0_42FC_8AB5_6A905FF14B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogSettings dialog

struct CApplicationSettings
{
	CApplicationSettings();

	BOOL m_bUseEditor;
	CString m_strEditor;

	void SaveSettings();
	void LoadSettings();
};

extern CApplicationSettings g_settings;

class CDialogSettings : public CDialog
{
// Construction
public:
	CDialogSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSettings)
	enum { IDD = IDD_DIALOG_SETTINGS };
	int		m_bUseEditor;
	CString	m_strEditor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSettings)
	virtual void OnOK();
	afx_msg void OnRadioEditorChanged();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSETTINGS_H__707B10E3_CCE0_42FC_8AB5_6A905FF14B43__INCLUDED_)
