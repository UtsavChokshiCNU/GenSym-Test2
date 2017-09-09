// DialogMarkerProperties.cpp : implementation file
//

#include "stdafx.h"
#include "trackcontrol.h"
#include "DialogMarkerProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMarkerProperties dialog


CDialogMarkerProperties::CDialogMarkerProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMarkerProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogMarkerProperties)
	m_strCaption = _T("");
	m_nPosition = 0;
	//}}AFX_DATA_INIT
}


void CDialogMarkerProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMarkerProperties)
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_nPosition);
	DDV_MinMaxInt(pDX, m_nPosition, 0, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMarkerProperties, CDialog)
	//{{AFX_MSG_MAP(CDialogMarkerProperties)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMarkerProperties message handlers
