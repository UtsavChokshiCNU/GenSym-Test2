// GallerySampleDoc.cpp : implementation of the CGallerySampleDoc class
//

#include "stdafx.h"
#include "GallerySample.h"

#include "GallerySampleDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleDoc

IMPLEMENT_DYNCREATE(CGallerySampleDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CGallerySampleDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CGallerySampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleDoc construction/destruction

CGallerySampleDoc::CGallerySampleDoc()
{
	// TODO: add one-time construction code here

}

CGallerySampleDoc::~CGallerySampleDoc()
{
}

BOOL CGallerySampleDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CGallerySampleDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CGallerySampleCntrItem(preo, (CGallerySampleDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CGallerySampleDoc serialization

void CGallerySampleDoc::Serialize(CArchive& ar)
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
// CGallerySampleDoc diagnostics

#ifdef _DEBUG
void CGallerySampleDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CGallerySampleDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGallerySampleDoc commands
