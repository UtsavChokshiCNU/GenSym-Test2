#if !defined(AFX_APPCAPTION_H__41FCA746_6748_4414_868A_3DC9275BD021__INCLUDED_)
#define AFX_APPCAPTION_H__41FCA746_6748_4414_868A_3DC9275BD021__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppCaption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppCaption window

class CAppCaption : public CControlBar
{
// Construction
public:
	CAppCaption();

// Attributes
public:

// Operations
public:
	CFont m_fnt;
	void SetContent(CString str);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppCaption)
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//}}AFX_VIRTUAL
	void Create(CWnd* pParentWnd);
	CSize CalcFixedLayout(BOOL, BOOL /*bHorz*/);

// Implementation
public:
	virtual ~CAppCaption();


	CString m_strContent;
	// Generated message map functions
protected:
	//{{AFX_MSG(CAppCaption)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPCAPTION_H__41FCA746_6748_4414_868A_3DC9275BD021__INCLUDED_)
