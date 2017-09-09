// ConstraintsDlg.h
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

#if !defined(_CONSTRAINTSDLG_H_)
#define _CONSTRAINTSDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


class CConstraintsDlg : public CDialog
{
public:
	CConstraintsDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CConstraintsDlg)
	enum { IDD = IDD_CONSTRAINTS };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CConstraintsDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CConstraintsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCaption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_CONSTRAINTSDLG_H_)
