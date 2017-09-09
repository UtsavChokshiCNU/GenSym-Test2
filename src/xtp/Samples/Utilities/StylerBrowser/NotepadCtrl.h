#if !defined(AFX_NOTEPADCTRL_H__2EE51CD0_7CE8_417F_A452_E61D7FA9AB59__INCLUDED_)
#define AFX_NOTEPADCTRL_H__2EE51CD0_7CE8_417F_A452_E61D7FA9AB59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotepadCtrl.h : header file
//
#include <afxole.h>
#include "resource.h"

//#include "Tools\ComboBoxXP.h"

/////////////////////////////////////////////////////////////////////////////
// CNotepadCtrl window

class CTxtDropTarget : public COleDropTarget
{
public:
    CTxtDropTarget(CWnd* pWnd) {m_pParent = pWnd;}

    BOOL        OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
    DROPEFFECT  OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    void        OnDragLeave(CWnd* pWnd);
    DROPEFFECT  OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    DROPEFFECT  OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point);
//	void SetParent(CWnd* pWnd) { m_pParent = pWnd;}

private:
	CWnd* m_pParent;
};


class CNotepadCtrl : public CXTPEdit
{
// Construction
public:
	CNotepadCtrl();

// Attributes
public:
private:
	CTxtDropTarget	m_dropTarget;
	CFont m_fntText;

// Operations
public:
	CString GetTitle()
	{
		CString strTitle;
		strTitle.LoadString(IDS_TITLE_NOTEPAD);
		return strTitle;
	}
	BOOL Create(CWnd* pParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotepadCtrl)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotepadCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNotepadCtrl)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEPADCTRL_H__2EE51CD0_7CE8_417F_A452_E61D7FA9AB59__INCLUDED_)
