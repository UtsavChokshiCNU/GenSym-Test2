// MarkupListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MarkupListCtrl.h"

#include "Markup/XTPMarkupObject.h"
#include "Markup/XTPMarkupBuilder.h"
#include "Markup/XTPMarkupUIElement.h"
#include "Markup/XTPMarkupDrawingContext.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupListCtrl

MARKUP_LISTITEM::MARKUP_LISTITEM(CXTPMarkupContext* pContext)
{
	this->pItem = NULL;
	this->pContext = pContext;
}

MARKUP_LISTITEM::~MARKUP_LISTITEM()
{
	MARKUP_RELEASE(pItem);
}


void MARKUP_LISTITEM::Resolve(LPCTSTR lpszMarkup)
{
	strMarkup = lpszMarkup;

	MARKUP_RELEASE(pItem);
	pItem = pContext->Parse(strMarkup);
}

CMarkupListCtrl::CMarkupListCtrl()
{
}

CMarkupListCtrl::~CMarkupListCtrl()
{
}

void CMarkupListCtrl::Init()
{
	// Don't call base class.
}

BEGIN_MESSAGE_MAP(CMarkupListCtrl, CXTPListBox)
	//{{AFX_MSG_MAP(CMarkupListCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupListCtrl message handlers

void CMarkupListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	MARKUP_LISTITEM* pListItem = (MARKUP_LISTITEM*)lpDrawItemStruct->itemData;
	if (!pListItem)
		return;

	if (!pListItem->pItem)
		return;

	CXTPMarkupDrawingContext dc(lpDrawItemStruct->hDC);

	if (((LONG)(lpDrawItemStruct->itemID) >= 0) &&
		(lpDrawItemStruct->itemAction & (ODA_DRAWENTIRE | ODA_SELECT)))
	{
		
		if (((lpDrawItemStruct->itemState & ODS_SELECTED) != 0))
		{
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, 0xc9afa6);
		}
		else
		{
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));
		}

		pListItem->pItem->Arrange(lpDrawItemStruct->rcItem);
		
		pListItem->pItem->Render(&dc);
	}

	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) != 0)
	{
		::SetTextColor(lpDrawItemStruct->hDC, 0);
		::SetBkColor(lpDrawItemStruct->hDC,0xFFFFFF);
		::DrawFocusRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
	}

}

void CMarkupListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	MARKUP_LISTITEM* pListItem = (MARKUP_LISTITEM*)lpMeasureItemStruct->itemData;
	if (!pListItem)
		return;

	if (!pListItem->pItem)
		return;

	CRect rc;
	GetClientRect(rc);

	CXTPMarkupDrawingContext dc;
	pListItem->pItem->Measure(&dc, CSize(rc.Width(), rc.Height()));

	lpMeasureItemStruct->itemHeight = pListItem->pItem->GetDesiredSize().cy;	
}

void CMarkupListCtrl::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) 
{
	delete (MARKUP_LISTITEM*)lpDeleteItemStruct->itemData;
	
	CXTPListBox::DeleteItem(lpDeleteItemStruct);
}

void CMarkupListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CXTPListBox::OnSize(nType, cx, cy);
	
	CRect rc;
	GetClientRect(rc);
	CXTPMarkupDrawingContext dc;

	for (int i = 0; i < GetCount(); i++)
	{
		MARKUP_LISTITEM* pListItem = (MARKUP_LISTITEM*)GetItemDataPtr(i);
		if (!pListItem)
			continue;
		
		if (!pListItem->pItem)
			continue;

		pListItem->pItem->Measure(&dc, CSize(rc.Width(), rc.Height()));
		SetItemHeight(i, pListItem->pItem->GetDesiredSize().cy);
	}

}

void CMarkupListCtrl::ItemChanged(MARKUP_LISTITEM* pItem)
{
	CRect rc;
	GetClientRect(rc);

	for (int i = 0; i < GetCount(); i++)
	{
		MARKUP_LISTITEM* pListItem = (MARKUP_LISTITEM*)GetItemDataPtr(i);
		if (pListItem == pItem)
		{
			CXTPMarkupDrawingContext dc;
			pListItem->pItem->Measure(&dc, CSize(rc.Width(), rc.Height()));
			SetItemHeight(i, pListItem->pItem->GetDesiredSize().cy);
			break;
		}
	}
	Invalidate(FALSE);
}

void CMarkupListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CXTPListBox::OnLButtonDown(nFlags, point);
}
