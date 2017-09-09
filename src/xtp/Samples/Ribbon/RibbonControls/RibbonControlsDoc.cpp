// RibbonControlsDoc.cpp : implementation of the CRibbonControlsDoc class
//

#include "stdafx.h"
#include "RibbonControls.h"

#include "RibbonControlsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsDoc

IMPLEMENT_DYNCREATE(CRibbonControlsDoc, CDocument)

BEGIN_MESSAGE_MAP(CRibbonControlsDoc, CDocument)
	//{{AFX_MSG_MAP(CRibbonControlsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsDoc construction/destruction

CRibbonControlsDoc::CRibbonControlsDoc()
{
	// TODO: add one-time construction code here

}

CRibbonControlsDoc::~CRibbonControlsDoc()
{
}

BOOL CRibbonControlsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsDoc serialization

void CRibbonControlsDoc::Serialize(CArchive& ar)
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
// CRibbonControlsDoc diagnostics

#ifdef _DEBUG
void CRibbonControlsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRibbonControlsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRibbonControlsDoc commands
