// MergeView.cpp : implementation file
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

#include "StdAfx.h"
#include "MergeView.h"
#include "ReportSampleView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
// CMergeFrame


BEGIN_MESSAGE_MAP(CMergeFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMergeFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP    
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


int CMergeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}



	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_MERGE);


	return 0;
}

void CMergeFrame::OnDestroy()
{
	((CReportSampleView*)m_pOwnerView)->m_pWndMerge = NULL;

	CFrameWnd::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CMergeView

IMPLEMENT_DYNCREATE(CMergeView, CXTPReportView)

CMergeView::CMergeView()
	: m_bAutoSizing(TRUE)
	, m_pPreviewState(NULL)
{
}

CMergeView::~CMergeView()
{
}


BEGIN_MESSAGE_MAP(CMergeView, CXTPReportView)
	//{{AFX_MSG_MAP(CMergeView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	// Command handler
	ON_COMMAND(ID_REPORTCONTROL_ALLOWEDIT,     OnReportAllowEdit)
	ON_COMMAND(ID_REPORTCONTROL_EDITONCLICK,   OnReportEditOnClick)

	ON_COMMAND(ID_REPORTCONTROL_AUTOSIZING,    OnReportAutoSizing)
	ON_COMMAND(ID_REPORTCONTROL_FOCUSSUBITEMS, OnReportFocusSubItems)
	ON_COMMAND(ID_REPORTCONTROL_WATERMARK,     OnReportWatermark)

	// Update handler
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_ALLOWEDIT,     OnUpdateReportAllowEdit)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_EDITONCLICK,   OnUpdateReportEditOnClick)
	//
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_AUTOSIZING,    OnUpdateReportAutoSizing)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FOCUSSUBITEMS, OnUpdateReportFocusSubItems)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_WATERMARK,     OnUpdateReportWatermark)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMergeView drawing

/////////////////////////////////////////////////////////////////////////////
// CMergeView diagnostics

#ifdef _DEBUG
void CMergeView::AssertValid() const
{
	CView::AssertValid();
}

void CMergeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMergeView message handlers

int CMergeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));


	wndReport.AllowEdit(TRUE);
	wndReport.PreviewAllowEdit(TRUE);
	wndReport.EnablePreviewMode(TRUE);
	wndReport.ShowHeaderRows(TRUE);
	wndReport.ShowFooterRows(TRUE);
	wndReport.PinFooterRows(FALSE);

	int nFreezeCount = 3;
	int nColumnCount = 6;
	int nHeaderCount = 5;
	int nFooterCount = 5;
	int nRecordCount = 20;
	int nColumn;
	int nRecord;
	int nFreeze;

	CXTPReportRecord *pRecord;

	for (nFreeze=0; nFreeze<nFreezeCount; nFreeze++)
	{
		CString sName;
		sName.Format(_T("Freeze %d"), nFreeze);
		wndReport.AddColumn(new CXTPReportColumn(nFreeze, sName, 90, FALSE));
	}

	for (nColumn=nFreezeCount; nColumn<nFreezeCount+nColumnCount; nColumn++)
	{
		CString sName;
		sName.Format(_T("Column %d"), nColumn);
		CXTPReportColumn *pColumn = new CXTPReportColumn(nColumn, sName, 90, TRUE);
		pColumn = wndReport.AddColumn(pColumn);
/*
		if (1+nFreezeCount == nColumn ||
			 2+nFreezeCount == nColumn)
		{
			CXTPReportRecordItemEditOptions *pEditOptions = pColumn->GetEditOptions();
			pEditOptions->AddConstraint(_T("Column Constraint 0"), 0);
			pEditOptions->AddConstraint(_T("Column Constraint 1"), 1);
			pEditOptions->AddConstraint(_T("Column Constraint 2"), 2);
			pEditOptions->m_bConstraintEdit = TRUE;
			pEditOptions->m_bAllowEdit = TRUE;
			pEditOptions->AddComboButton(TRUE);
		}
*/
	}

	//////////////////////////////////////////////////////////////////////////
	// Add header records
	//////////////////////////////////////////////////////////////////////////

	for (nRecord=0; nRecord<nHeaderCount; nRecord++)
	{
		pRecord = wndReport.GetHeaderRecords()->Add(new CXTPReportRecord());

		for (nFreeze=0; nFreeze<nFreezeCount; nFreeze++)
		{
			CString sText;
			sText.Format(_T("Freeze %d, %d"), nRecord, nFreeze);

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sText);
			pItem->SetIconIndex(nFreeze);
			pRecord->AddItem(pItem);
		}
		for (nColumn=0; nColumn<nColumnCount; nColumn++)
		{
			CString sText;
			sText.Format(_T("Header %d, %d"), nRecord, nColumn);

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sText);
			pItem->SetIconIndex(nColumn);
			pRecord->AddItem(pItem);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Add records
	//////////////////////////////////////////////////////////////////////////

	for (nRecord=0; nRecord<nRecordCount; nRecord++)
	{
		pRecord = wndReport.AddRecord(new CXTPReportRecord());

		for (nFreeze=0; nFreeze<nFreezeCount; nFreeze++)
		{
			CString sText;
			sText.Format(_T("Freeze %d, %d"), nRecord, nFreeze);

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sText);
			pItem->SetIconIndex(nFreeze);
			pRecord->AddItem(pItem);
		}
		for (nColumn=0; nColumn<nColumnCount; nColumn++)
		{
			CString sText;

			if (1 == nColumn && 1 == nRecord)
			{
				sText.Format(_T("Long text for merged item %d, %d"), nRecord, nColumn);
			}
			else
			{
				sText.Format(_T("Row %d, %d"), nRecord, nColumn);
			}

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sText);
			//pItem->SetIconIndex(nColumn);
			pRecord->AddItem(pItem);
		}

		if (nRecord >= 5 && nRecord <= 10 && FALSE)
		{
			CString sText;
			sText.Format(_T("Item preview for row %d"), nRecord);
			CXTPReportRecordItemPreview *pItem = new CXTPReportRecordItemPreview(sText);
			pItem->SetIconIndex(4);
			pRecord->SetPreviewItem(pItem);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Add footer records
	//////////////////////////////////////////////////////////////////////////

	for (nRecord=0; nRecord<nFooterCount; nRecord++)
	{
		pRecord = wndReport.GetFooterRecords()->Add(new CXTPReportRecord());

		for (nFreeze=0; nFreeze<nFreezeCount; nFreeze++)
		{
			CString sText;
			sText.Format(_T("Freeze %d, %d"), nRecord, nFreeze);

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sText);
			pItem->SetIconIndex(nFreeze);
			pRecord->AddItem(pItem);
		}
		for (nColumn=0; nColumn<nColumnCount; nColumn++)
		{
			CString sText;
			sText.Format(_T("Footer %d, %d"), nRecord, nColumn);

			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText(sText);
			pItem->SetIconIndex(nColumn);
			pRecord->AddItem(pItem);
		}
	}


	wndReport.AllowEdit(FALSE);
	wndReport.FocusSubItems(TRUE);
	wndReport.Populate();

	wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	wndReport.SetFreezeColumnsCount(nFreezeCount);

	wndReport.GetHeaderRecords()->MergeItems(CXTPReportRecordItemRange(3,4,1,2));
	wndReport.GetFooterRecords()->MergeItems(CXTPReportRecordItemRange(3,4,3,4));
	wndReport.GetRecords()->MergeItems(CXTPReportRecordItemRange(4,5,1,4));

	//wndReport.ShowGroupBy(TRUE);

	wndReport.GetPaintManager()->m_bShowNonActiveInPlaceButton = TRUE;
	wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpReportGridSolid);
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnResource);

/*
	// Alternate background color
	wndReport.GetPaintManager()->m_bUseAlternativeBackground = TRUE;
	wndReport.GetPaintManager()->m_clrControlBack            = RGB(192,192,192);
	wndReport.GetPaintManager()->m_clrAlternativeBackground  = RGB(160,160,160);
*/

/*
	// Constraints not supported in 15.1.1
	CXTPReportRecordItem *pItem;
	pItem = wndReport.GetRecords()->GetAt(1)->GetItem(4);
	CXTPReportRecordItemEditOptions *pEditOptions = pItem->GetEditOptions(NULL);
	pEditOptions->AddConstraint(_T("Constraint 0"), 0);
	pEditOptions->AddConstraint(_T("Constraint 1"), 1);
	pEditOptions->AddConstraint(_T("Constraint 2"), 2);
	pEditOptions->m_bConstraintEdit = TRUE;
	pEditOptions->m_bAllowEdit = TRUE;
	pEditOptions->AddComboButton(TRUE);
*/
	wndReport.SetFocus();

	return 0;
}

void CMergeView::OnDestroy()
{
	base::OnDestroy();

	// Close print preview
	if (NULL != m_pPreviewState)
	{
		m_pPreviewState->lpfnCloseProc((CFrameWnd*)AfxGetMainWnd());
		m_pPreviewState = NULL;
	}
}


void CMergeView::OnEndPrintPreview(CDC *pDC, CPrintInfo *pInfo, POINT point, CPreviewView *pView)
{
	base::OnEndPrintPreview(pDC, pInfo, point, pView);
	m_pPreviewState = NULL;
}


void CMergeView::OnReportAllowEdit()
{
	GetReportCtrl().AllowEdit(!GetReportCtrl().IsAllowEdit());

}

void CMergeView::OnUpdateReportAllowEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsAllowEdit()? TRUE: FALSE);

}

void CMergeView::OnReportEditOnClick()
{
	GetReportCtrl().EditOnClick(!GetReportCtrl().IsEditOnClick());

}

void CMergeView::OnUpdateReportEditOnClick(CCmdUI *pCmdUI)
{

	pCmdUI->SetCheck(GetReportCtrl().IsAllowEdit() && GetReportCtrl().IsEditOnClick()? TRUE: FALSE);

	if (!GetReportCtrl().IsAllowEdit())
		pCmdUI->Enable(FALSE);

}

void CMergeView::OnReportFocusSubItems()
{
	GetReportCtrl().FocusSubItems(!GetReportCtrl().IsFocusSubItems());

}

void CMergeView::OnUpdateReportFocusSubItems(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsFocusSubItems()? TRUE: FALSE);
}


void CMergeView::OnUpdateReportAutoSizing(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bAutoSizing ? 1 : 0);
}

void CMergeView::OnReportAutoSizing()
{
	m_bAutoSizing = !m_bAutoSizing;

	for (int nColumn=3; nColumn< GetReportCtrl().GetColumns()->GetCount(); nColumn++)
	{
		GetReportCtrl().GetColumns()->GetAt(nColumn)->SetAutoSize(m_bAutoSizing);
	}
}


void CMergeView::OnFilePrintPreview()
{
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	
	// must not create this on the frame.  Must outlive this function
	m_pPreviewState = new CPrintPreviewState;
	
	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.
	
	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), m_pPreviewState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete m_pPreviewState;
		m_pPreviewState = NULL;
		
	}
}


/////////////////////////////////////////////////////////////////////////////

void CMergeView::OnReportWatermark()
{
	CXTPReportControl &wndReport = GetReportCtrl();

	if (NULL == wndReport.GetWatermarkBitmap())
	{
		CBitmap bmpWatermark;

		if (bmpWatermark.LoadBitmap(IDB_CODEJOCKGEAR))
		{
			wndReport.SetWatermarkBitmap(bmpWatermark, 64);
			wndReport.GetPaintManager()->m_bPrintWatermark = TRUE;
		}
	}
	else
	{
		wndReport.SetWatermarkBitmap(HBITMAP(NULL), 0);
		wndReport.GetPaintManager()->m_bPrintWatermark = FALSE;
	}

	wndReport.RedrawControl();
}

void CMergeView::OnUpdateReportWatermark(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(NULL == GetReportCtrl().GetWatermarkBitmap() ? 0 : 1);
}
