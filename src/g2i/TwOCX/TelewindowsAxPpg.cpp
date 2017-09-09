// TelewindowsAxPpg.cpp : Implementation of the CTelewindowsAxPropPage property page class.

#include "stdafx.h"
#include "TelewindowsAx.h"
#include "TelewindowsAxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CTelewindowsAxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CTelewindowsAxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CTelewindowsAxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTelewindowsAxPropPage, "TelewindowsAx.TelewindowsAxPropPage.1",
	0x344a8f, 0x58cb, 0x4449, 0xbc, 0xe1, 0x70, 0x75, 0x8b, 0x5c, 0xf6, 0xea)


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxPropPage::CTelewindowsAxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CTelewindowsAxPropPage

BOOL CTelewindowsAxPropPage::CTelewindowsAxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_TELEWINDOWSAX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxPropPage::CTelewindowsAxPropPage - Constructor

CTelewindowsAxPropPage::CTelewindowsAxPropPage() :
	COlePropertyPage(IDD, IDS_TELEWINDOWSAX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CTelewindowsAxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxPropPage::DoDataExchange - Moves data between page and properties

void CTelewindowsAxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CTelewindowsAxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CTelewindowsAxPropPage message handlers
