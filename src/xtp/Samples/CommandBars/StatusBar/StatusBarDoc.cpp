// StatusBarDoc.cpp : implementation of the CStatusBarDoc class
//

#include "stdafx.h"
#include "StatusBar.h"

#include "StatusBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarDoc

IMPLEMENT_DYNCREATE(CStatusBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusBarDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBarDoc construction/destruction

CStatusBarDoc::CStatusBarDoc()
{
	// TODO: add one-time construction code here

}

CStatusBarDoc::~CStatusBarDoc()
{
}

BOOL CStatusBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStatusBarDoc serialization

void CStatusBarDoc::Serialize(CArchive& ar)
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
// CStatusBarDoc diagnostics

#ifdef _DEBUG
void CStatusBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusBarDoc commands
