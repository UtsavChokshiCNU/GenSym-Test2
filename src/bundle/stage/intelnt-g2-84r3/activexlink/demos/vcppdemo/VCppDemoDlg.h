// VCppDemoDlg.h : header file
//

#if !defined(AFX_VCppDemoDLG_H__73FA7ECB_36AC_4E0D_9E2B_0F977EF803A1__INCLUDED_)
#define AFX_VCppDemoDLG_H__73FA7ECB_36AC_4E0D_9E2B_0F977EF803A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVCppDemoDlg dialog

class CVCppDemoDlg : public CDialog
{
// Construction
public:
	CVCppDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVCppDemoDlg)
	enum { IDD = IDD_VCppDemo_DIALOG };
	CButton	c_BtnCycle;
	CButton	c_BtnCallG2;
	CEdit	c_EditMsg;
	CEdit	c_EditG2Location;
	CEdit	c_EditSeed;
	CEdit	c_EditResult;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCppDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	IG2Gateway3*    m_pIG2Gateway;
	CWnd 		    m_G2Gateway1;
//	void Update_Light(Mode As String)
	CString		    m_csNextMode;
	CString		    m_csMode;

	// Generated message map functions
	//{{AFX_MSG(CVCppDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPostMessageButton();
	afx_msg void OnButtonCallg2();
	afx_msg void OnCycleButton();
	afx_msg void OnBtnDiscon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnG2Paused();
	afx_msg void OnG2Resumed();
	afx_msg void OnG2Connected();
	afx_msg void OnG2Disconnected();
	afx_msg void OnRpcCalled(LPCTSTR Name, VARIANT FAR* InArgs, VARIANT FAR* OutArgs);
	afx_msg void OnRpcStart(LPCTSTR Name, VARIANT FAR* InArgs);
	afx_msg void OnG2Reset();
	afx_msg void OnG2Started();
	afx_msg void OnG2StateKnown();
	DECLARE_EVENTSINK_MAP()
private:
	boolean m_g2Connected;
	G2RunStateType m_g2RunState;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCppDemoDLG_H__73FA7ECB_36AC_4E0D_9E2B_0F977EF803A1__INCLUDED_)
