// PropertyItemFlags.h: interface for the CPropertyItemFlags class.
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

#if !defined(AFX_PROPERTYITEMFLAGS_H__36ED730B_E310_460F_ACA4_28AE60A54492__INCLUDED_)
#define AFX_PROPERTYITEMFLAGS_H__36ED730B_E310_460F_ACA4_28AE60A54492__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommandBarsDesigner.h"


class CPropertyGridItemDockingFlags : public CXTPPropertyGridItemFlags
{
public:
	CPropertyGridItemDockingFlags(UINT nID, UINT dwFlags)
		: CXTPPropertyGridItemFlags(nID, dwFlags)
	{
	}

	void OnAddChildItem()
	{
		m_pConstraints->AddConstraint(_T("xtpFlagAlignAny"), xtpFlagAlignAny);
		m_pConstraints->AddConstraint(_T("xtpFlagAlignLeft"), xtpFlagAlignLeft);
		m_pConstraints->AddConstraint(_T("xtpFlagAlignTop"), xtpFlagAlignTop);
		m_pConstraints->AddConstraint(_T("xtpFlagAlignRight"), xtpFlagAlignRight);
		m_pConstraints->AddConstraint(_T("xtpFlagAlignBottom"), xtpFlagAlignBottom);
		m_pConstraints->AddConstraint(_T("xtpFlagFloating"), xtpFlagFloating);
	}
};


class CPropertyGridItemStretchFlags : public CXTPPropertyGridItemFlags
{
public:
	CPropertyGridItemStretchFlags(UINT nID, UINT dwFlags)
		: CXTPPropertyGridItemFlags(nID, dwFlags)
	{
	}

	void OnAddChildItem()
	{
		m_pConstraints->AddConstraint(_T("xtpFlagHideWrap"), xtpFlagHideWrap);
		m_pConstraints->AddConstraint(_T("xtpFlagStretched"), xtpFlagStretched);
	}
};


class CPropertyGridItemControlFlags : public CXTPPropertyGridItemFlags
{
public:
	CPropertyGridItemControlFlags(UINT nID, UINT dwFlags)
		: CXTPPropertyGridItemFlags(nID, dwFlags)
	{
	}

	void OnAddChildItem()
	{
		m_pConstraints->AddConstraint(_T("xtpFlagRightAlign"), xtpFlagRightAlign);
		m_pConstraints->AddConstraint(_T("xtpFlagNoMovable"), xtpFlagNoMovable);
		m_pConstraints->AddConstraint(_T("xtpFlagSkipFocus"), xtpFlagSkipFocus);
		m_pConstraints->AddConstraint(_T("xtpFlagControlStretched"), xtpFlagControlStretched);
		m_pConstraints->AddConstraint(_T("xtpFlagWrapRow"), xtpFlagWrapRow);		
	}
};


AFX_INLINE BOOL GetBoolValue(CXTPPropertyGridItem* pItem) {
	return ((CXTPPropertyGridItemBool*)pItem)->GetBool();
}
AFX_INLINE int GetFlagsValue(CXTPPropertyGridItem* pItem) {
	return ((CXTPPropertyGridItemFlags*)pItem)->GetFlags();
}
AFX_INLINE int GetNumberValue(CXTPPropertyGridItem* pItem) {
	return ((CXTPPropertyGridItemNumber*)pItem)->GetNumber();
}
AFX_INLINE int GetEnumValue(CXTPPropertyGridItem* pItem) {
	return ((CXTPPropertyGridItemEnum*)pItem)->GetEnum();
}




#endif // !defined(AFX_PROPERTYITEMFLAGS_H__36ED730B_E310_460F_ACA4_28AE60A54492__INCLUDED_)
