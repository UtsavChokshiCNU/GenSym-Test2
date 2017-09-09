// SimpleChartDlg.h : header file
//

#if !defined(AFX_SIMPLECHARTDLG_H__D149CDDD_5019_4FC8_9FFD_B7ADC600E278__INCLUDED_)
#define AFX_SIMPLECHARTDLG_H__D149CDDD_5019_4FC8_9FFD_B7ADC600E278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimpleChartDlg dialog

class CSimpleChartDlg : public CDialog
{
// Construction
public:
	CSimpleChartDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpleChartDlg)
	enum { IDD = IDD_SIMPLECHART_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	BOOL InitChart();

// Implementation
protected:
	HICON m_hIcon;
	CXTPChartControl m_wndChartControl; // subclassed chart window.

	// Generated message map functions
	//{{AFX_MSG(CSimpleChartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLECHARTDLG_H__D149CDDD_5019_4FC8_9FFD_B7ADC600E278__INCLUDED_)
