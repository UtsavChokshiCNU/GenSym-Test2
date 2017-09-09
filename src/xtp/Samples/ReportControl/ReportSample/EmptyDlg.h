// EmptyDlg.h
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

#if !defined(_EMPTYDLG_H_)
#define _EMPTYDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEmptyDlg dialog

class CEmptyDlg : public CDialog
{
public:
	CEmptyDlg(CWnd *pParent = NULL);

	//{{AFX_DATA(CEmptyDlg)
	enum { IDD = IDD_EMPTY };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CEmptyDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange *pDX);
	//}}AFX_VIRTUAL

protected:

	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport1;
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport2;
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport3;
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport4;

	//{{AFX_MSG(CEmptyDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_EMPTYDLG_H_)
