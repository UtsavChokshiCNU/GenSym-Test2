// HeaderFooterView.cpp : implementation file
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
#include "Resource.h"
#include "HeaderFooterView.h"
#include "ReportSampleView.h"
#include "TaskListView.h"

#if _MSC_VER >= 1200 // MFC 6.0
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#include "MonthCalCtrlEx.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
// CHeaderFooterFrame

BEGIN_MESSAGE_MAP(CHeaderFooterFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CHeaderFooterFrame)
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

#define COLUMN_TYPE             0
#define COLUMN_IMPORTANCE       1
#define COLUMN_ATTACHMENT       2
#define COLUMN_STATUS           3
#define COLUMN_SUBJECT          4
#define COLUMN_DUE_DATE         5
#define COLUMN_COMPLETE         6
#define COLUMN_CATEGORIES       7


int CHeaderFooterFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_HEADERFOOTER);


	return 0;
}

void CHeaderFooterFrame::OnDestroy()
{
	((CReportSampleView*)m_pOwnerView)->m_pHeaderFooterFrame = NULL;

	CFrameWnd::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderFooterView

IMPLEMENT_DYNCREATE(CHeaderFooterView, CXTPReportView)

CHeaderFooterView::CHeaderFooterView()
	: m_pPreviewState(NULL)
{
}

CHeaderFooterView::~CHeaderFooterView()
{
}


BEGIN_MESSAGE_MAP(CHeaderFooterView, CXTPReportView)
	//{{AFX_MSG_MAP(CHeaderFooterView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_COMMAND(ID_REPORTCONTROL_SHOWHEADERRECORDS, OnShowHeaderRecords)
	ON_COMMAND(ID_REPORTCONTROL_SHOWFOOTERRECORDS, OnShowFooterRecords)
	ON_COMMAND(ID_REPORTCONTROL_SHOW_GROUPBY,      OnShowGroupBy)
	ON_COMMAND(ID_REPORTCONTROL_HEADERRECORDS_EDIT, OnHeaderRecordsAllowEdit)
	ON_COMMAND(ID_REPORTCONTROL_FOOTERRECORDS_EDIT, OnFooterRecordsAllowEdit)

	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_SHOWHEADERRECORDS, OnUpdateShowHeaderRecords)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_SHOWFOOTERRECORDS, OnUpdateShowFooterRecords)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_SHOW_GROUPBY,      OnUpdateShowGroupBy)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_HEADERRECORDS_EDIT, OnUpdateHeaderRecordsAllowEdit)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FOOTERRECORDS_EDIT, OnUpdateFooterRecordsAllowEdit)

	ON_COMMAND(ID_REPORTCONTROL_PIN_FOOTER,         OnPinFooterRows)
	ON_COMMAND(ID_REPORTCONTROL_PIN_FOOTER_PRINTED, OnPinFooterRowsPrinted)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_PIN_FOOTER,         OnUpdatePinFooterRows)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_PIN_FOOTER_PRINTED, OnUpdatePinFooterRowsPrinted)

	ON_COMMAND(ID_REPORTCONTROL_DRAW_GRID_EMPTY, OnDrawGridForEmpty)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_DRAW_GRID_EMPTY, OnUpdateDrawGridForEmpty)

	ON_COMMAND(ID_REPORTCONTROL_MOVEINHEADER, OnMoveInHeader)
	ON_COMMAND(ID_REPORTCONTROL_MOVEINFOOTER, OnMoveInFooter)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_MOVEINHEADER, OnUpdateMoveInHeader)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_MOVEINFOOTER, OnUpdateMoveInFooter)
	
	ON_COMMAND(ID_REPORTCONTROL_HDIV_THIN,    OnHeaderDividerStyleThin)
	ON_COMMAND(ID_REPORTCONTROL_HDIV_BOLD,    OnHeaderDividerStyleBold)
	ON_COMMAND(ID_REPORTCONTROL_HDIV_SHADE,   OnHeaderDividerStyleShade)
	ON_COMMAND(ID_REPORTCONTROL_HDIV_NONE,    OnHeaderDividerStyleNone)
	ON_COMMAND(ID_REPORTCONTROL_HDIV_OUTLOOK, OnHeaderDividerStyleOutlook)

	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_HDIV_THIN,    OnUpdateHeaderDividerStyleThin)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_HDIV_BOLD,    OnUpdateHeaderDividerStyleBold)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_HDIV_SHADE,   OnUpdateHeaderDividerStyleShade)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_HDIV_NONE,    OnUpdateHeaderDividerStyleNone)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_HDIV_OUTLOOK, OnUpdateHeaderDividerStyleOutlook)

	ON_COMMAND(ID_REPORTCONTROL_FDIV_THIN,    OnFooterDividerStyleThin)
	ON_COMMAND(ID_REPORTCONTROL_FDIV_BOLD,    OnFooterDividerStyleBold)
	ON_COMMAND(ID_REPORTCONTROL_FDIV_SHADE,   OnFooterDividerStyleShade)
	ON_COMMAND(ID_REPORTCONTROL_FDIV_NONE,    OnFooterDividerStyleNone)
	ON_COMMAND(ID_REPORTCONTROL_FDIV_OUTLOOK, OnFooterDividerStyleOutlook)

	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FDIV_THIN,    OnUpdateFooterDividerStyleThin)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FDIV_BOLD,    OnUpdateFooterDividerStyleBold)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FDIV_SHADE,   OnUpdateFooterDividerStyleShade)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FDIV_NONE,    OnUpdateFooterDividerStyleNone)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FDIV_OUTLOOK, OnUpdateFooterDividerStyleOutlook)
	
	ON_COMMAND(ID_REPORTCONTROL_COLUMNS_SHADED,     OnColumnsStyleShaded)
	ON_COMMAND(ID_REPORTCONTROL_COLUMNS_FLAT,       OnColumnsStyleFlat)
	ON_COMMAND(ID_REPORTCONTROL_COLUMNS_EXPLORER,   OnColumnsStyleExplorer)
	ON_COMMAND(ID_REPORTCONTROL_COLUMNS_OFFICE2003, OnColumnsStyleOffice2003)

	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_COLUMNS_SHADED,     OnUpdateColumnsStyleShaded)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_COLUMNS_FLAT,       OnUpdateColumnsStyleFlat)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_COLUMNS_EXPLORER,   OnUpdateColumnsStyleExplorer)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_COLUMNS_OFFICE2003, OnUpdateColumnsStyleOffice2003)

	//}}AFX_MSG_MAP
	ON_NOTIFY(XTP_NM_REPORT_INPLACEBUTTONDOWN, XTP_ID_REPORT_CONTROL, OnReportButtonClick)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderFooterView drawing

/////////////////////////////////////////////////////////////////////////////
// CHeaderFooterView diagnostics

#ifdef _DEBUG
void CHeaderFooterView::AssertValid() const
{
	CView::AssertValid();
}

void CHeaderFooterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHeaderFooterView message handlers

int CHeaderFooterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));

	wndReport.AddColumn(new CXTPReportColumn(COLUMN_TYPE, _T("Type"), 18, FALSE, 0));
	CXTPReportColumn* pColumnImportance = wndReport.AddColumn(new CXTPReportColumn(COLUMN_IMPORTANCE, _T("Importants"), 18, FALSE, 1));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_ATTACHMENT, _T("Attachments"), 18, FALSE, 7));
	CXTPReportColumn* pColumnStatus = wndReport.AddColumn(new CXTPReportColumn(COLUMN_STATUS, _T("Status"), 100));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT, _T("Subject"), 200));
	CXTPReportColumn* pColumnDueDate = wndReport.AddColumn(new CXTPReportColumn(COLUMN_DUE_DATE, _T("Due Date"), 100));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_COMPLETE, _T("% Complete"), 100));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CATEGORIES, _T("Categories"), 80));

	pColumnStatus->GetEditOptions()->AddConstraint(_T("Not Started"), taskStatusNotStarted);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("In Progress"), taskStatusInProgress);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Completed"), taskStatusCompleted);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Waiting on someone else"), taskStatusWaiting);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Deferred"), taskStatusDeferred);
	pColumnStatus->GetEditOptions()->m_bConstraintEdit = TRUE;
	pColumnStatus->GetEditOptions()->m_bAllowEdit = TRUE;
	pColumnStatus->GetEditOptions()->AddComboButton();

	pColumnImportance->GetEditOptions()->AddConstraint(_T("Low"), taskImportanceLow);
	pColumnImportance->GetEditOptions()->AddConstraint(_T("Normal"), taskImportanceNormal);
	pColumnImportance->GetEditOptions()->AddConstraint(_T("High"), taskImportanceHigh);
	pColumnImportance->GetEditOptions()->m_bAllowEdit = FALSE;
	pColumnImportance->GetEditOptions()->AddComboButton();

	pColumnDueDate->GetEditOptions()->AddComboButton();

	COleDateTime dtNone;
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Support Email: About tooltips"), dtNone, 70, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusNotStarted, _T("Support Email: Docking Pane ToggleDocking"), dtNone, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceHigh, TRUE, taskStatusNotStarted, _T("Feature Request: New Event for CommandBars"), dtNow, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceHigh, TRUE, taskStatusCompleted, _T("Support Email: Help Taskpanel And ShortcutBar"), dtNow, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, FALSE, taskStatusCompleted, _T("Support Email: RE: Docking Pane Window Overlapping Issues"), dtNow, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, FALSE, taskStatusCompleted, _T("Support Email: CXTPPropertyGridItem"), dtNone, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusCompleted, _T("Support Email: Toolbar Oddity"), dtNone, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusCompleted, _T("Support Email: CXTPTabControl"), dtNone, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(FALSE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Support Email: Menus go wrong if another form has topmost setting"), dtNone, 10, _T("")));
	wndReport.AddRecord(new CTaskRecord(FALSE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Support Email: Update Xtreme Suite from 8.6 to 8.7"), dtNone, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE, taskImportanceLow, TRUE, taskStatusInProgress, _T("Support Email: Bug in Tree-View on Label Edit"), dtNone, 0, _T("")));

	// Fixed rows
	wndReport.GetHeaderRecords()->Add(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Header record 1"), dtNone, 0, _T("")));
	wndReport.GetHeaderRecords()->Add(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Header record 2"), dtNone, 0, _T("")));
	wndReport.GetFooterRecords()->Add(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Footer record 1"), dtNone, 100, _T("")));
	wndReport.GetFooterRecords()->Add(new CTaskRecord(TRUE, taskImportanceNormal, TRUE, taskStatusInProgress, _T("Footer record 2"), dtNone, 100, _T("")));

	// Fixed rows appearance
	wndReport.ShowHeaderRows(TRUE);
	wndReport.ShowFooterRows(TRUE);
	wndReport.PinFooterRows(FALSE);

	// Allow grouping of header and footer rows
	wndReport.HeaderRowsAllowGroup(TRUE);
	wndReport.FooterRowsAllowGroup(TRUE);

	// Allow sorting of header and footer rows
	wndReport.HeaderRowsAllowSort(TRUE);
	wndReport.FooterRowsAllowSort(TRUE);

	wndReport.GetPaintManager()->SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerNone);
	wndReport.GetPaintManager()->SetFooterRowsDividerStyle(xtpReportFixedRowsDividerNone);
	wndReport.GetPaintManager()->m_clrHeaderRowsDivider = RGB(255,0,0);
	wndReport.GetPaintManager()->m_clrFooterRowsDivider = RGB(0,0,255);
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat);
	wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpReportGridSolid);

	wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	wndReport.ShowGroupBy(TRUE);
	wndReport.AllowEdit(TRUE);
	wndReport.FocusSubItems(TRUE);
	wndReport.Populate();
	wndReport.SetFocus();
	wndReport.EnableMarkup(TRUE);

	return 0;
}



void CHeaderFooterView::OnDestroy()
{
	base::OnDestroy();

	// Close print preview
	if (NULL != m_pPreviewState)
	{
		m_pPreviewState->lpfnCloseProc((CFrameWnd*)AfxGetMainWnd());
		m_pPreviewState = NULL;
	}
}


void CHeaderFooterView::OnEndPrintPreview(CDC *pDC, CPrintInfo *pInfo, POINT point, CPreviewView *pView)
{
	base::OnEndPrintPreview(pDC, pInfo, point, pView);
	m_pPreviewState = NULL;
}


void CHeaderFooterView::OnShowHeaderRecords()
{
	GetReportCtrl().ShowHeaderRows(!GetReportCtrl().IsHeaderRowsVisible());
}

void CHeaderFooterView::OnUpdateShowHeaderRecords(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().IsHeaderRowsVisible()); 
}

void CHeaderFooterView::OnShowFooterRecords()
{
	GetReportCtrl().ShowFooterRows(!GetReportCtrl().IsFooterRowsVisible());
}

void CHeaderFooterView::OnUpdateShowFooterRecords(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().IsFooterRowsVisible()); 
}

void CHeaderFooterView::OnShowGroupBy()
{
	GetReportCtrl().ShowGroupBy(!GetReportCtrl().IsGroupByVisible());
}

void CHeaderFooterView::OnUpdateShowGroupBy(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsGroupByVisible());
}

void CHeaderFooterView::OnHeaderRecordsAllowEdit()
{
	GetReportCtrl().HeaderRowsAllowEdit(!GetReportCtrl().IsHeaderRowsAllowEdit());
}

void CHeaderFooterView::OnUpdateHeaderRecordsAllowEdit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().IsHeaderRowsAllowEdit()); 
}

void CHeaderFooterView::OnFooterRecordsAllowEdit()
{
	GetReportCtrl().FooterRowsAllowEdit(!GetReportCtrl().IsFooterRowsAllowEdit());
}

void CHeaderFooterView::OnUpdateFooterRecordsAllowEdit(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().IsFooterRowsAllowEdit()); 
}

void CHeaderFooterView::OnPinFooterRows()
{
	GetReportCtrl().PinFooterRows(!GetReportCtrl().IsFooterRowsPinned());
	GetReportCtrl().RedrawControl();
}

void CHeaderFooterView::OnUpdatePinFooterRows(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().IsFooterRowsPinned()); 
}

void CHeaderFooterView::OnPinFooterRowsPrinted()
{
	GetReportCtrl().PinFooterRowsPrinted(!GetReportCtrl().IsFooterRowsPinnedPrinted());
}

void CHeaderFooterView::OnUpdatePinFooterRowsPrinted(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().IsFooterRowsPinnedPrinted()); 
}

void CHeaderFooterView::OnDrawGridForEmpty()
{
	GetReportCtrl().GetPaintManager()->SetDrawGridForEmptySpace(!GetReportCtrl().GetPaintManager()->IsDrawGridForEmptySpace());
	GetReportCtrl().RedrawControl();
}

void CHeaderFooterView::OnUpdateDrawGridForEmpty(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE); 
	pCmdUI->SetCheck(GetReportCtrl().GetPaintManager()->IsDrawGridForEmptySpace());
}

void CHeaderFooterView::OnMoveInHeader()
{
	GetReportCtrl().GetNavigator()->SetCurrentFocusInHeadersRows(!GetReportCtrl().GetNavigator()->GetCurrentFocusInHeadersRows());
	GetReportCtrl().RedrawControl();
}

void CHeaderFooterView::OnUpdateMoveInHeader(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetReportCtrl().IsHeaderRowsVisible()); 
	pCmdUI->SetCheck(GetReportCtrl().GetNavigator()->GetCurrentFocusInHeadersRows());
}

void CHeaderFooterView::OnMoveInFooter()
{
	GetReportCtrl().GetNavigator()->SetCurrentFocusInFootersRows(!GetReportCtrl().GetNavigator()->GetCurrentFocusInFootersRows());
	GetReportCtrl().RedrawControl();
}

void CHeaderFooterView::OnUpdateMoveInFooter(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetReportCtrl().IsFooterRowsVisible()); 
	pCmdUI->SetCheck(GetReportCtrl().GetNavigator()->GetCurrentFocusInFootersRows());
}

// styles
#define ONDIVIDER_STYLE(Where, Style)	\
	void CHeaderFooterView::On##Where##DividerStyle##Style()\
	{\
		GetReportCtrl().GetPaintManager()->Set##Where##RowsDividerStyle(xtpReportFixedRowsDivider##Style);\
		GetReportCtrl().AdjustLayout();\
		GetReportCtrl().RedrawControl();\
	}\
	void CHeaderFooterView::OnUpdate##Where##DividerStyle##Style(CCmdUI* pCmdUI)\
	{\
		pCmdUI->Enable(TRUE); \
		pCmdUI->SetCheck(GetReportCtrl().GetPaintManager()->Get##Where##RowsDividerStyle() == xtpReportFixedRowsDivider##Style); \
	}

ONDIVIDER_STYLE(Header, Thin)
ONDIVIDER_STYLE(Header, Bold)
ONDIVIDER_STYLE(Header, Shade)
ONDIVIDER_STYLE(Header, None)
ONDIVIDER_STYLE(Header, Outlook)

ONDIVIDER_STYLE(Footer, Thin)
ONDIVIDER_STYLE(Footer, Bold)
ONDIVIDER_STYLE(Footer, Shade)
ONDIVIDER_STYLE(Footer, None)
ONDIVIDER_STYLE(Footer, Outlook)



// columns style
#define CONCOLUMN_STYLE(Style)	\
	void CHeaderFooterView::OnColumnsStyle##Style()\
	{\
		GetReportCtrl().GetPaintManager()->SetColumnStyle(xtpReportColumn##Style);\
		GetReportCtrl().AdjustLayout();\
		GetReportCtrl().RedrawControl();\
	}\
	void CHeaderFooterView::OnUpdateColumnsStyle##Style(CCmdUI* pCmdUI)\
	{\
		pCmdUI->Enable(TRUE); \
		pCmdUI->SetCheck(GetReportCtrl().GetPaintManager()->GetColumnStyle() == xtpReportColumn##Style); \
	}

CONCOLUMN_STYLE(Flat)
CONCOLUMN_STYLE(Explorer)
CONCOLUMN_STYLE(Shaded)
CONCOLUMN_STYLE(Office2003)



//
void CHeaderFooterView::OnAddTask() 
{
	CTaskRecord* pRecord = (CTaskRecord*)GetReportCtrl().AddRecord(new CTaskRecord(TRUE, taskImportanceNormal, FALSE, taskStatusNotStarted, _T(""), COleDateTime(), 0, _T("")));
	GetReportCtrl().Populate();

	CXTPReportRow* pRow = GetReportCtrl().GetRows()->Find(pRecord);
	if (pRow)
	{			
		XTP_REPORTRECORDITEM_ARGS itemArgs(&GetReportCtrl(), pRow, GetReportCtrl().GetColumns()->Find(COLUMN_SUBJECT));
		GetReportCtrl().EditItem(&itemArgs);
	}
}

void CHeaderFooterView::OnReportButtonClick(NMHDR * pNotifyStruct, LRESULT* pResult)
{
    XTP_NM_REPORTINPLACEBUTTON* pItemNotify = (XTP_NM_REPORTINPLACEBUTTON*) pNotifyStruct;
    ASSERT(pItemNotify->pButton);

	if (!pItemNotify->pButton->pColumn || pItemNotify->pButton->pColumn->GetItemIndex() != COLUMN_DUE_DATE)
		return;
	

	CRect rcRow = pItemNotify->pButton->pRow->GetRect();
	CRect rcCol = pItemNotify->pButton->pColumn->GetRect();
	CRect rcItem = rcRow;
	rcItem.left = rcCol.left;
	rcItem.right = rcCol.right;
	
	CXTPReportRecordItemDateTime* pItemDateTime = DYNAMIC_DOWNCAST(CXTPReportRecordItemDateTime, pItemNotify->pItem);
	if (!pItemDateTime) {
		ASSERT(FALSE);
		return;
	}

	COleDateTime dtDateValue = pItemDateTime->GetValue();
	if (dtDateValue.GetStatus() != COleDateTime::valid || dtDateValue == 0) 
	{
		dtDateValue = COleDateTime::GetCurrentTime();

#ifdef _XTP_INCLUDE_CALENDAR
		dtDateValue = CXTPCalendarUtils::ResetTime(dtDateValue);
#endif
	}

	CXTPReportControl* pControl = pItemNotify->pButton->pControl;

	BOOL bResult = -1; // -1 means that XTP DatePicker is not supported in this build.

//#define DBG_DATE_PICKERS
#ifdef DBG_DATE_PICKERS
	static int s_nRotator = 0;
	s_nRotator++;
	if(s_nRotator % 2 == 0)
#endif
	bResult = Show_XTPDatePicker(pControl, rcItem, dtDateValue);
		
	if(bResult < 0) {		
		bResult = Show_MFCDatePicker(pControl, rcItem, dtDateValue);
	}

	if(!bResult) {
		return;
	}
	
	CString strNewVal = dtDateValue.Format();
	//pItemNotify->pButton->pControl->GetInplaceEdit()->SetWindowText(strNewVal);
	pItemNotify->pItem->OnEditChanged(NULL, strNewVal);
	
	// uncomment to end editing after pop-up date picker closed.
	//pItemNotify->pButton->pControl->EditItem(NULL);

	pItemNotify->pButton->pControl->RedrawControl();
	*pResult = (LRESULT)TRUE;
}


void CHeaderFooterView::OnFilePrintPreview()
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
	
	if (!DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), m_pPreviewState))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );

		delete m_pPreviewState;
		m_pPreviewState = NULL;
	}
}



BOOL CHeaderFooterView::Show_XTPDatePicker(CXTPReportControl* pControl, 
										const CRect& rcItem,
										COleDateTime& rdtDate)
{
#ifdef _XTP_INCLUDE_CALENDAR
	CXTPDatePickerControl wndDatePicker;

	if(!wndDatePicker.GetSelectedDays()) {
		ASSERT(FALSE);
		return FALSE;
	}

	wndDatePicker.SetMaxSelCount(1);
	wndDatePicker.GetSelectedDays()->Select(rdtDate);
	wndDatePicker.EnsureVisible(rdtDate);

	CRect rcSize;
	if(!wndDatePicker.GetMinReqRect(&rcSize, 1, 1) ) {
		ASSERT(FALSE);
		return FALSE;
	}
	rcSize.InflateRect(5, 5);
	
	CRect rcPopUp = rcItem;
	pControl->ClientToScreen(&rcPopUp);

	rcPopUp.right = rcPopUp.left + rcSize.Width();
	rcPopUp.top = rcPopUp.bottom;
	rcPopUp.bottom = rcPopUp.bottom + rcSize.Height();

	BOOL bResult = wndDatePicker.GoModal(rcPopUp, pControl);

	if(bResult) 
	{
		int nSelCount = wndDatePicker.GetSelectedDays()->GetSelectedBlocksCount();
		if(nSelCount) 
		{
			rdtDate = (DATE)wndDatePicker.GetSelectedDays()->GetSelectedBlock(0).nDateBegin;
		}
	}
	return bResult;

#else 
	return -1; 
#endif
}

BOOL CHeaderFooterView::Show_MFCDatePicker(CXTPReportControl* pControl, 
										const CRect& rcItem,
										COleDateTime& rdtDate)
{
#if _MSC_VER >= 1200 // MFC 6.0

	CMonthCalCtrlEx wndMFCDatePicker;
	
	CPoint pt(rcItem.left, rcItem.bottom);
	pControl->ClientToScreen(&pt);

	BOOL bResult = wndMFCDatePicker.GoModal(pt, pControl, rdtDate);
	
	return bResult;
#else
	return FALSE;
#endif
}
