// WebSCORaxPpg.cpp : Implementation of the CWebSCORaxPropPage property page class.

#include "stdafx.h"
#include "WebSCORax.h"
#include "WebSCORaxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWebSCORaxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWebSCORaxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CWebSCORaxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebSCORaxPropPage, "WEBSCORAX.WebSCORaxPropPage.1",
	0x344a8f, 0x58cb, 0x4449, 0xbc, 0xe1, 0x70, 0x75, 0x8b, 0x5c, 0xf6, 0xea)


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxPropPage::CWebSCORaxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebSCORaxPropPage

BOOL CWebSCORaxPropPage::CWebSCORaxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WEBSCORAX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxPropPage::CWebSCORaxPropPage - Constructor

CWebSCORaxPropPage::CWebSCORaxPropPage() :
	COlePropertyPage(IDD, IDS_WEBSCORAX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CWebSCORaxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxPropPage::DoDataExchange - Moves data between page and properties

void CWebSCORaxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CWebSCORaxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CWebSCORaxPropPage message handlers
