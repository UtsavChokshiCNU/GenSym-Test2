// SmartLayoutDoc.cpp : implementation of the CSmartLayoutDoc class
//

#include "stdafx.h"
#include "SmartLayout.h"

#include "SmartLayoutDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutDoc

IMPLEMENT_DYNCREATE(CSmartLayoutDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CSmartLayoutDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CSmartLayoutDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutDoc construction/destruction

CSmartLayoutDoc::CSmartLayoutDoc()
{
	// TODO: add one-time construction code here

}

CSmartLayoutDoc::~CSmartLayoutDoc()
{
}

BOOL CSmartLayoutDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CSmartLayoutDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CSmartLayoutCntrItem(preo, (CSmartLayoutDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutDoc serialization

void CSmartLayoutDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutDoc diagnostics

#ifdef _DEBUG
void CSmartLayoutDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CSmartLayoutDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutDoc commands
