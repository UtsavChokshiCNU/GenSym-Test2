// CommandBarControlsDoc.cpp : implementation of the CCommandBarControlsDoc class
//

#include "stdafx.h"
#include "CommandBarControls.h"

#include "CommandBarControlsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsDoc

IMPLEMENT_DYNCREATE(CCommandBarControlsDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommandBarControlsDoc, CDocument)
	//{{AFX_MSG_MAP(CCommandBarControlsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsDoc construction/destruction

CCommandBarControlsDoc::CCommandBarControlsDoc()
{
	// TODO: add one-time construction code here

}

CCommandBarControlsDoc::~CCommandBarControlsDoc()
{
}

BOOL CCommandBarControlsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsDoc serialization

void CCommandBarControlsDoc::Serialize(CArchive& ar)
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
// CCommandBarControlsDoc diagnostics

#ifdef _DEBUG
void CCommandBarControlsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCommandBarControlsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandBarControlsDoc commands
