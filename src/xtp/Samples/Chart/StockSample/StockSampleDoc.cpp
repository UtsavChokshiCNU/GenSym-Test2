// StockSampleDoc.cpp : implementation of the CStockSampleDoc class
//
// --------------------------------------------------------------------------
// COPYRIGHT NOTICE:
// --------------------------------------------------------------------------
// 
// "Codejock Chart" is a MFC extension library for creating modern charting 
// applications. This file and the code herein are part of the Codejock Chart
// MFC extension library.
//
// This code is protected under U.S. Copyright Law and International treaties
// and is intended for registered and licensed use only. Any other use is 
// strictly prohibited. This code is subject to the terms and conditions 
// outlined in the "Codejock Chart" End User License Agreement (EULA).
//
// Copyright (c) 1998-2011 Codejock Technologies LLC, All Rights Reserved.
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StockSample.h"

#include "StockSampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockSampleDoc

IMPLEMENT_DYNCREATE(CStockSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CStockSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CStockSampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockSampleDoc construction/destruction

CStockSampleDoc::CStockSampleDoc()
{
	// TODO: add one-time construction code here

}

CStockSampleDoc::~CStockSampleDoc()
{
}

BOOL CStockSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStockSampleDoc serialization

void CStockSampleDoc::Serialize(CArchive& ar)
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
// CStockSampleDoc diagnostics

#ifdef _DEBUG
void CStockSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStockSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockSampleDoc commands
