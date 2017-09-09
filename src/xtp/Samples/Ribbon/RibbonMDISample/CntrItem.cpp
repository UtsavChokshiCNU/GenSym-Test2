// CntrItem.cpp : implementation of the CRibbonMDISampleCntrItem class
//

#include "stdafx.h"
#include "RibbonMDISample.h"

#include "RibbonMDISampleDoc.h"
#include "RibbonMDISampleView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleCntrItem implementation

IMPLEMENT_SERIAL(CRibbonMDISampleCntrItem, CRichEditCntrItem, 0)

CRibbonMDISampleCntrItem::CRibbonMDISampleCntrItem(REOBJECT* preo, CRibbonMDISampleDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CRibbonMDISampleCntrItem::~CRibbonMDISampleCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CRibbonMDISampleCntrItem diagnostics

#ifdef _DEBUG
void CRibbonMDISampleCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CRibbonMDISampleCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
