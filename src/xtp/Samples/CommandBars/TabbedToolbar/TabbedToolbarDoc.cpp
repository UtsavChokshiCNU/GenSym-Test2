// TabbedToolbarDoc.cpp : implementation of the CTabbedToolbarDoc class
//

#include "stdafx.h"
#include "TabbedToolbar.h"

#include "TabbedToolbarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarDoc

IMPLEMENT_DYNCREATE(CTabbedToolbarDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabbedToolbarDoc, CDocument)
	//{{AFX_MSG_MAP(CTabbedToolbarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarDoc construction/destruction

CTabbedToolbarDoc::CTabbedToolbarDoc()
{
	// TODO: add one-time construction code here

}

CTabbedToolbarDoc::~CTabbedToolbarDoc()
{
}

BOOL CTabbedToolbarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarDoc serialization

void CTabbedToolbarDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarDoc diagnostics

#ifdef _DEBUG
void CTabbedToolbarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabbedToolbarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabbedToolbarDoc commands
