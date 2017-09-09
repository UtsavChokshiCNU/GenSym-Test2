// AnimationDlg.h : header file
//

#if !defined(AFX_ANIMATIONDLG_H__681C4706_B7BB_4150_93E8_C108A9F1A7FC__INCLUDED_)
#define AFX_ANIMATIONDLG_H__681C4706_B7BB_4150_93E8_C108A9F1A7FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AnimateStatic.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CAnimationDlg dialog

class CAnimationDlg : public CDialog
{
// Construction
public:
	CAnimationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimationDlg)
	enum { IDD = IDD_ANIMATION_DIALOG };
	CEdit	m_editSteps;
	CEdit	m_editDelay;
	CStatic m_staticDelay;
	CStatic m_staticSteps;
	CAnimateStatic	m_staticGear;
	int		m_nAnimationDelay;
	int		m_nAnimationType;
	int		m_nAnimationSteps;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAnimationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAnimate();
	afx_msg void OnChangeEditDelay();
	afx_msg void OnChangeEditSteps();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRadio();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATIONDLG_H__681C4706_B7BB_4150_93E8_C108A9F1A7FC__INCLUDED_)
