// VirtualListView.cpp : implementation of the CVirtualListView class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VirtualList.h"

#include "VirtualListDoc.h"
#include "VirtualListView.h"

#include "DialogRowsCount.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CVirtualRecord::CVirtualRecord(CDBVListSet* pSet)
{
	AddItem(new CXTPReportRecordItemText());
	AddItem(new CXTPReportRecordItemText());
	AddItem(new CXTPReportRecordItemText());
	AddItem(new CXTPReportRecordItemText());
	AddItem(new CXTPReportRecordItemText());
	AddItem(new CXTPReportRecordItemText());
	m_pSet = pSet;
}

void CVirtualRecord::GetItemMetrics(
	XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs,
	XTP_REPORTRECORDITEM_METRICS  *pItemMetrics)
{
	TRACE(_T("%d %d\n"), pDrawArgs->pColumn->GetIndex(), pDrawArgs->pRow->GetIndex());

	CXTPReportColumnOrder* pSortOrder = pDrawArgs->pControl->GetColumns()->GetSortOrder();

	BOOL bDecreasing = pSortOrder->GetCount() > 0 && pSortOrder->GetAt(0)->IsSortedDecreasing();

	CString strColumn = pDrawArgs->pColumn->GetCaption();
	int nIndexCol = pDrawArgs->pColumn->GetItemIndex();
	int nIndexRow = pDrawArgs->pRow->GetIndex();
	int nCount = pDrawArgs->pControl->GetRows()->GetCount();
//MD
	if (m_pSet)
	{
		int iCnt = m_pSet->GetFieldCount();
		if (nIndexCol < iCnt)
		{
			m_pSet->MoveFirst();
			m_pSet->Move(nIndexRow);

			if (!m_pSet->IsEOF())
			{
				switch(nIndexCol)
				{
				case 0:
					pItemMetrics->strText = m_pSet->m_Email;
					break;
				case 1:
					pItemMetrics->strText = m_pSet->m_Name;
					break;
				case 2:
					pItemMetrics->strText = m_pSet->m_Phone;
					break;
				case 3:
					pItemMetrics->strText = m_pSet->m_Location;
					break;
				case 4:
					pItemMetrics->strText = m_pSet->m_Title;
					break;
				case 5:
					pItemMetrics->strText = m_pSet->m_Department;
					break;
				}
			}
		}
	}
	else
	{
		pItemMetrics->strText.Format(_T("%s - Row %i"), strColumn, bDecreasing? nCount - nIndexRow: nIndexRow + 1);

	}
//MD - this is just example of auto-generated strings for cell caption
	CVirtualListView* pView = DYNAMIC_DOWNCAST(CVirtualListView, pDrawArgs->pControl->GetParent());

	if (pView && pView->m_bColorize)
	{
		// Execute this code to apply predefined formatting.  
		// To turn on automatic formatting, select it from the menu
		if (nIndexRow % 2)
		{
			pItemMetrics->clrBackground = RGB(245, 245, 245);
		}
	}

	if (pView && pView->m_bSimpleTree)
	{
		// Demonstrate possibility to organize one-level tree
		if (nIndexRow % 10 == 0)
		{
			POSITION pos = pView->m_lstCollapsed.Find(nIndexRow);
			pDrawArgs->pRow->SetExpanded(pos == NULL);

			if (pDrawArgs->pColumn->GetIndex() == 0)
			{
				pItemMetrics->nVirtRowLevel = 0;
				pItemMetrics->nVirtRowFlags = xtpVirtRowHasChildren; // row has children
			}
			pItemMetrics->nVirtRowFlags |= xtpVirtRowLastChild; // row is the last child

		}
		else
		{
			pDrawArgs->pRow->SetExpanded(FALSE);
			if (pDrawArgs->pColumn->GetIndex() == 0)
			{
				pItemMetrics->nVirtRowLevel = 1;
				pItemMetrics->nVirtRowFlags = 0; 
			}
			if (nIndexRow % 10 == 9)
			{
				pItemMetrics->nVirtRowFlags |= xtpVirtRowLastChild;
			}
		}
	}
}

//MD - custom derived function (base class function does nothing)
//to simulate SetDispInfo action (persist updates)
//User can put here extra validation, propmt to confirm or fill audit trail record about modifications
BOOL CVirtualRecord::UpdateRecordField(int nIndexRow, int nIndexCol, CString strText)
{
	if (m_pSet)
	{
		int iCnt = m_pSet->GetFieldCount();
		if (nIndexCol < iCnt)
		{
			m_pSet->MoveFirst();
			m_pSet->Move(nIndexRow);

			m_pSet->Edit();

			if (!m_pSet->IsEOF())
			{
				BOOL bUpd(FALSE);
				switch(nIndexCol)
				{
				case 0:
					if (m_pSet->m_Email != strText)
					{
						m_pSet->m_Email = strText;
						bUpd = TRUE;
					}
					break;
				case 1:
					if (m_pSet->m_Name != strText)
					{
						m_pSet->m_Name = strText;
						bUpd = TRUE;
					}
					break;
				case 2:
					if (m_pSet->m_Phone != strText)
					{
						m_pSet->m_Phone = strText;
						bUpd = TRUE;
					}
					break;
				case 3:
					if (m_pSet->m_Location != strText)
					{
						m_pSet->m_Location = strText;
						bUpd = TRUE;
					}
					break;
				case 4:
					if (m_pSet->m_Title != strText)
					{
						m_pSet->m_Title = strText;
						bUpd = TRUE;
					}
					break;
				case 5:
					if (m_pSet->m_Department != strText)
					{
						m_pSet->m_Department = strText;
						bUpd = TRUE;
					}
					break;
				}
				if (bUpd)
					m_pSet->Update();
			}
		}
	}
	return TRUE;
}
//MD
/////////////////////////////////////////////////////////////////////////////
// CVirtualListView

IMPLEMENT_DYNCREATE(CVirtualListView, CXTPReportView)

BEGIN_MESSAGE_MAP(CVirtualListView, CXTPReportView)
	//{{AFX_MSG_MAP(CVirtualListView)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_REPORT_SETROWSCOUNT, OnReportSetrowscount)
	ON_COMMAND(ID_REPORT_COLORIZE, OnReportColorize)
	ON_UPDATE_COMMAND_UI(ID_REPORT_COLORIZE, OnUpdateReportColorize)
	ON_COMMAND(ID_REPORT_TREE, OnReportSimpleTree)
	ON_UPDATE_COMMAND_UI(ID_REPORT_TREE, OnUpdateReportSimpleTree)	
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CXTPReportView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CXTPReportView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CXTPReportView::OnFilePrintPreview)

	ON_NOTIFY(NM_CLICK, XTP_ID_REPORT_CONTROL, OnReportItemClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView construction/destruction

CVirtualListView::CVirtualListView()
{
	m_bColorize = FALSE;
	m_bSimpleTree = FALSE;

}

CVirtualListView::~CVirtualListView()
{
}

BOOL CVirtualListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CXTPReportView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CVirtualListView diagnostics

#ifdef _DEBUG
void CVirtualListView::AssertValid() const
{
	CView::AssertValid();
}

void CVirtualListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVirtualListDoc* CVirtualListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVirtualListDoc)));
	return (CVirtualListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVirtualListView message handlers

int CVirtualListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl& wndReport = GetReportCtrl();
	wndReport.GetReportHeader()->AllowColumnRemove(FALSE);

	CDBVListSet* pSet = &GetDocument()->m_dBVListSet;

	TRY
	{
		if (pSet && pSet->Open())
		{
			CXTPReportColumn* 
				pCol = wndReport.AddColumn(new CXTPReportColumn(0, _T("Email"), 50));
			CXTPReportRecordItemEditOptions* pOpt = pCol->GetEditOptions();
			pCol = wndReport.AddColumn(new CXTPReportColumn(1, _T("Name (First, Last)"), 100));
			pCol = wndReport.AddColumn(new CXTPReportColumn(2, _T("Phone"), 50));
			pCol = wndReport.AddColumn(new CXTPReportColumn(3, _T("Location"), 50));
			pCol = wndReport.AddColumn(new CXTPReportColumn(4, _T("Title"), 50));
			pCol = wndReport.AddColumn(new CXTPReportColumn(5, _T("Dept"), 50));
			
			wndReport.GetHeaderRecords()->Add(new CVirtualRecord(pSet));
			wndReport.GetHeaderRecords()->Add(new CVirtualRecord(pSet));
			wndReport.GetHeaderRecords()->Add(new CVirtualRecord(pSet));
			wndReport.ShowHeaderRows(TRUE);
			wndReport.HeaderRowsAllowAccess(TRUE);
			wndReport.HeaderRowsEnableSelection(TRUE);

			wndReport.GetFooterRecords()->Add(new CVirtualRecord(pSet));
			wndReport.GetFooterRecords()->Add(new CVirtualRecord(pSet));
			wndReport.GetFooterRecords()->Add(new CVirtualRecord(pSet));
			wndReport.ShowFooterRows(TRUE);
			wndReport.FooterRowsAllowAccess(TRUE);
			wndReport.FooterRowsEnableSelection(TRUE);

			//pSet->SetFilter("Business Systems");
			//pSet->SetFilter("Consumer");
			pSet->SetFilter(_T("Desktop"));
			//pSet->SetFilter("Developer");
			//pSet->SetFilter("F & A");
			//pSet->SetFilter("International Operat");
			//pSet->SetFilter("International Subs");
			//pSet->SetFilter("Law & Corporate Affa");
			//pSet->SetFilter("Operations Service C");
			//pSet->SetFilter("Personal Systems Div");
			
			//wndReport.SetFilterText();
			
			// set the item count to the new record count
			int nRecordCount = 0;
			if (pSet->IsOpen())
				nRecordCount = pSet->GetRecordCount();
			
			wndReport.SetVirtualMode(new CVirtualRecord(pSet), nRecordCount);
	
			wndReport.GetReportHeader()->AllowColumnSort(FALSE);
		}
	}
	CATCH_ALL(e)
	{
		pSet = NULL;
	}
	END_CATCH_ALL

	if (!pSet)
	{
		wndReport.AddColumn(new CXTPReportColumn(0, _T("Column 1"), 50));
		wndReport.AddColumn(new CXTPReportColumn(1, _T("Column 2"), 50));
		wndReport.AddColumn(new CXTPReportColumn(2, _T("Column 3"), 50));
		
		
		wndReport.SetVirtualMode(new CVirtualRecord(), 1000000);
		
	}


	wndReport.Populate();

	wndReport.AllowEdit(TRUE);
	
	wndReport.FocusSubItems(TRUE);


	return 0;
}

//void CVirtualListView::OnTest()
//{
//	CXTPReportControl& wndReport = GetReportCtrl();
//	CString sCaption;
//	CXTPReportColumns* pColumns = wndReport.GetColumns();
//	CXTPReportColumn* pColumn = NULL;
//	if (pColumns)
//	{
//		pColumn = pColumns->GetAt(0);
//	}
//	int nRecs = wndReport.GetRecords()->GetCount();
//	if (nRecs > 0)
//	{
//		CXTPReportRecord* pRec = wndReport.GetRecords()->GetAt(0);
//		if (pRec)
//		{
//			int nItems = pRec->GetItemCount();
//			if (nItems > 0)
//			{
//				CXTPReportRecordItem* pRecItem = pRec->GetItem(0);
//				if (pRecItem)
//					sCaption = pRecItem->GetCaption(pColumn);
//			}
//		}
//	}
//}

void CVirtualListView::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	TRACE(_T("Click on row %d, col %d\n"),
			pItemNotify->pRow->GetIndex(), pItemNotify->pColumn->GetItemIndex());

	if (m_bSimpleTree)
	{
		int ind = pItemNotify->pRow->GetIndex();
		//POSITION pos = m_lstCollapsed.Find(ind);

		//CXTPReportSelectedRows* pSelectedRows = GetReportCtrl().GetSelectedRows();
		//POSITION pos = pSelectedRows->GetFirstSelectedRowPosition();
		//if (pos)
		//	m_lstCollapsed.RemoveAt(pos);
		//pItemNotify->pRow->SetExpanded(FALSE);
		
		GetReportCtrl().RedrawControl();
	}
}


void CVirtualListView::OnEditCopy()
{
	CXTPReportSelectedRows* pSelectedRows = GetReportCtrl().GetSelectedRows();
	POSITION pos = pSelectedRows->GetFirstSelectedRowPosition();

	while (pos)
	{
		int nIndex = pSelectedRows->GetNextSelectedRow(pos)->GetIndex();
		TRACE(_T("%i, "), nIndex + 1);
	}

}

void CVirtualListView::OnReportSetrowscount()
{
	CDialogRowsCount dr;
	if (dr.DoModal() == IDOK)
	{
		GetReportCtrl().SetVirtualMode(new CVirtualRecord(), dr.m_nRowsCount);
		GetReportCtrl().Populate();
	}
}

void CVirtualListView::OnReportColorize()
{
	m_bColorize = !m_bColorize;
	GetReportCtrl().RedrawControl();

}

void CVirtualListView::OnUpdateReportColorize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bColorize);
}


void CVirtualListView::OnReportSimpleTree()
{
	m_bSimpleTree = !m_bSimpleTree;

	GetReportCtrl().GetColumns()->GetAt(0)->SetTreeColumn(m_bSimpleTree);

	if (!m_bSimpleTree)
	{
		m_lstCollapsed.RemoveAll();
	}
	
	GetReportCtrl().RedrawControl();
}

void CVirtualListView::OnUpdateReportSimpleTree(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bSimpleTree);
}


