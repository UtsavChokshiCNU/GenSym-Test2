// Based on example from September 2000 MSDN Magazine
// in C++ Q&A Tooltip article by Paul DiLascia (p155)
//

#pragma once

#include "subclass.h"
#include "puptext.h"

//////////////////
// Generic tip-handler to display tip for wide text in a TreeView box.
// To use:
// - instantiate one of these for each tree control
// - call Init
//
class ComboTreeTip : public CSubclassWnd {
protected:
	UINT	m_idMyControl;				 // id of tree control
	HTREEITEM m_hCurItem;				 // handle of current item
	BOOL	m_bCapture;					 // whether mouse is captured
	static CPopupText g_wndTip;			 // THE tip window

	// subclass window proc
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);

	// virtual fns you can override
	virtual void OnMouseMove(CPoint p);
	virtual BOOL IsRectCompletelyVisible(const CRect& rc);
	virtual HTREEITEM OnGetItemInfo(CPoint p, CRect& rc, CString& s);

public:
	ComboTreeTip();
	~ComboTreeTip();
	static UINT g_nTipTimeMsec;			 // global: msec wait before showing tip
	void Init(CWnd* pTreeCtl);				 // initialize
};
