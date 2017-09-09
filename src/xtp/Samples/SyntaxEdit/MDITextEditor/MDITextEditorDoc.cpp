// MDITextEditorDoc.cpp : implementation of the CMDITextEditorDoc class
//

#include "stdafx.h"
#include "MDITextEditor.h"

#include "MDITextEditorDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE 
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorDoc

IMPLEMENT_DYNCREATE(CMDITextEditorDoc, CDocBase)

BEGIN_MESSAGE_MAP(CMDITextEditorDoc, CDocBase)
	//{{AFX_MSG_MAP(CMDITextEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorDoc construction/destruction

CMDITextEditorDoc::CMDITextEditorDoc()
{
	// TODO: add one-time construction code here

}

CMDITextEditorDoc::~CMDITextEditorDoc()
{
}

BOOL CMDITextEditorDoc::OnNewDocument()
{
	if (!CDocBase::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorDoc serialization

void CMDITextEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	CDocBase::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorDoc diagnostics

#ifdef _DEBUG
void CMDITextEditorDoc::AssertValid() const
{
	CDocBase::AssertValid();
}

void CMDITextEditorDoc::Dump(CDumpContext& dc) const
{
	CDocBase::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDITextEditorDoc commands

BOOL CMDITextEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocBase::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

BOOL CMDITextEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocBase::OnSaveDocument(lpszPathName);
}

void CMDITextEditorDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.m_pMainFrame->SetRowCol(0,0);
	
	CDocBase::OnCloseDocument();
}

void CMDITextEditorDoc::OnChangedViewList() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocBase::OnChangedViewList();
}
