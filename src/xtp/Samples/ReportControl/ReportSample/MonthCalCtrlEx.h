// TaskListView.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(_MONTHCALCTRLEX_H_)
#define _MONTHCALCTRLEX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER >= 1200 // MFC 6.0
//////////////////////////////////////////////////////////////////////////
class CMonthCalCtrlEx : public CMonthCalCtrl
{
public:
	BOOL GoModal(const CPoint& pt, CWnd* pParentWnd, COleDateTime& rdtDate);

protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
	afx_msg void OnSelChange(NMHDR* pNMHdr, LRESULT* pResult);
	
	DECLARE_MESSAGE_MAP()
};

#endif // _MSC_VER >= 1200

#endif // !defined(_MONTHCALCTRLEX_H_)
