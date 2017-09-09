// CntrItem.cpp : implementation of the CSmartLayoutCntrItem class
//

#include "stdafx.h"
#include "SmartLayout.h"

#include "SmartLayoutDoc.h"
#include "SmartLayoutView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutCntrItem implementation

IMPLEMENT_SERIAL(CSmartLayoutCntrItem, CRichEditCntrItem, 0)

CSmartLayoutCntrItem::CSmartLayoutCntrItem(REOBJECT* preo, CSmartLayoutDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here

}

CSmartLayoutCntrItem::~CSmartLayoutCntrItem()
{
	// TODO: add cleanup code here

}

/////////////////////////////////////////////////////////////////////////////
// CSmartLayoutCntrItem diagnostics

#ifdef _DEBUG
void CSmartLayoutCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CSmartLayoutCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
