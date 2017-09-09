// TreeViewDlg.h
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

#if !defined(_TREEVIEWDLG_H_)
#define _TREEVIEWDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTreeViewDlg dialog

class CTreeViewDlg : public CDialog
{
private:

	enum Column
	{
		COLUMN_IMPORTANCE   =  0,
		COLUMN_ICON         =  1,
		COLUMN_ATTACHMENT   =  2,
		COLUMN_FROM         =  3,
		COLUMN_SUBJECT      =  4,
		COLUMN_SENT         =  5,
		COLUMN_SIZE         =  6,
		COLUMN_CHECK        =  7,
		COLUMN_PRICE        =  8,
		COLUMN_CREATED      =  9,
		COLUMN_RECEIVED     = 10,
		COLUMN_CONVERSATION = 11,
		COLUMN_CONTACTS     = 12,
		COLUMN_MESSAGE      = 13,
		COLUMN_CC           = 14,
		COLUMN_CATEGORIES   = 15,
		COLUMN_AUTOFORWARD  = 16,
		COLUMN_AUTOARCHIVE  = 17,
		COLUMN_DUE_BY       = 18
	};

public:
	CTreeViewDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CTreeViewDlg)
	enum { IDD = IDD_TREEVIEW };
	//}}AFX_DATA
	CXTPOfficeBorder<CXTPReportControl,false> m_wndReport;

	CImageList m_ilIcons;


	//{{AFX_VIRTUAL(CTreeViewDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	CImageList m_ilTree;

	//{{AFX_MSG(CTreeViewDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	afx_msg void OnReportRClick(NMHDR *pNotifyStruct, LRESULT *result);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(_TREEVIEWDLG_H_)
