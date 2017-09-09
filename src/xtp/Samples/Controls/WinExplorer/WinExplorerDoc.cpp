// WinExplorerDoc.cpp : implementation of the CWinExplorerDoc class
//

#include "stdafx.h"
#include "WinExplorer.h"

#include "WinExplorerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerDoc

IMPLEMENT_DYNCREATE(CWinExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CWinExplorerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerDoc construction/destruction

CWinExplorerDoc::CWinExplorerDoc()
{
	// TODO: add one-time construction code here

}

CWinExplorerDoc::~CWinExplorerDoc()
{
}

BOOL CWinExplorerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWinExplorerDoc serialization

void CWinExplorerDoc::Serialize(CArchive& ar)
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
// CWinExplorerDoc diagnostics

#ifdef _DEBUG
void CWinExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinExplorerDoc commands
