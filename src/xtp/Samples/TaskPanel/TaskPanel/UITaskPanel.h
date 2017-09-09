// UITaskPanel.h: interface for the CUITaskPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UITASKPANEL_H__32F98AF5_EFF3_4436_87D1_D2DBB1ABCC0E__INCLUDED_)
#define AFX_UITASKPANEL_H__32F98AF5_EFF3_4436_87D1_D2DBB1ABCC0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUITaskPanel : public CXTPTaskPanel  
{
	class CTaskPanelCmdUI;
public:
	CUITaskPanel();
	virtual ~CUITaskPanel();

	void CreateFromMenu(CMenu* pMenu);

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	void OnUpdateCmdUI(CWnd* pTarget, BOOL bDisableIfNoHndler);


public:
	BOOL m_bUIMode;

};

#endif // !defined(AFX_UITASKPANEL_H__32F98AF5_EFF3_4436_87D1_D2DBB1ABCC0E__INCLUDED_)
