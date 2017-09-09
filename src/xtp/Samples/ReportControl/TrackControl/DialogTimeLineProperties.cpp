// DialogTimeLineProperties.cpp : implementation file
//

#include "stdafx.h"
#include "trackcontrol.h"
#include "DialogTimeLineProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogTimeLineProperties dialog


CDialogTimeLineProperties::CDialogTimeLineProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTimeLineProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogTimeLineProperties)
	m_nMin = 0;
	m_nMax = 0;
	//}}AFX_DATA_INIT
}


void CDialogTimeLineProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogTimeLineProperties)
	DDX_Text(pDX, IDC_EDIT_MIN, m_nMin);
	DDV_MinMaxInt(pDX, m_nMin, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_MAX, m_nMax);
	DDV_MinMaxInt(pDX, m_nMax, 0, 10000);
	//}}AFX_DATA_MAP
	DDV_MinMaxInt(pDX, m_nMax, m_nMin + 1, 10000);
}


BEGIN_MESSAGE_MAP(CDialogTimeLineProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogTimeLineProperties)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTimeLineProperties message handlers
