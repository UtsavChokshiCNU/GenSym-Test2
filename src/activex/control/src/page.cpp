// page.cpp : Implementation of the CTwControlPropPage property page class.

#include "classes-twax.hxx"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CTwControlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CTwControlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CTwControlPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CTwControlPropPage, "TW.TwControlPropPage.1",
	0x78e2cd8d, 0x9683, 0x4bf7, 0x81, 0x13, 0x40, 0x8d, 0x8, 0xaa, 0x1c, 0x54)


/////////////////////////////////////////////////////////////////////////////
// CTwControlPropPage::CTwControlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CTwControlPropPage

BOOL CTwControlPropPage::CTwControlPropPageFactory::UpdateRegistry (BOOL bRegister)
{
  dprintf(DUMP, "page CTwControlPropPage::CTwControlPropPageFactory::UpdateRegistry method call");
  if (bRegister)
    return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle (),
                                           m_clsid, IDS_TWAX_PPG);
  else
    return AfxOleUnregisterClass (m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CTwControlPropPage::CTwControlPropPage - Constructor

CTwControlPropPage::CTwControlPropPage () :
	COlePropertyPage(IDD, IDS_TWAX_PPG_CAPTION)
{
  dprintf(DUMP, "page CTwControlPropPage::CTwControlPropPage method call");
  //{{AFX_DATA_INIT(CTwControlPropPage)
  // NOTE: ClassWizard will add member initialization here
  //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CTwControlPropPage::DoDataExchange - Moves data between page and properties

void CTwControlPropPage::DoDataExchange (CDataExchange *pDX)
{
  dprintf(DUMP, "page DoDataExchange method call");
  //{{AFX_DATA_MAP(CTwControlPropPage)
  // NOTE: ClassWizard will add DDP, DDX, and DDV calls here
  //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_DATA_MAP
  DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CTwControlPropPage message handlers
