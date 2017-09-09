// TaskListView.cpp : implementation file
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
#include "ReportSample.h"
#include "TaskListView.h"
#include "ReportSampleView.h"

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
// CTaskListFrame

BEGIN_MESSAGE_MAP(CTaskListFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CTaskListFrame)
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


int CTaskListFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	pCommandBars->SetMenu(_T("Menu Bar"), IDR_TASKLIST);


	return 0;
}

void CTaskListFrame::OnDestroy()
{
	((CReportSampleView*)m_pOwnerView)->m_pTaskFrame = NULL;

	CFrameWnd::OnDestroy();
}

//////////////////////////////////////////////////////////////////////////
// CTaskRecord

CTaskRecord::CTaskRecord(
		BOOL bSharedTask, TaskImportance taskImportance, BOOL bHasAttachment,
		TaskStatus taskStatus, CString strSubject,
		COleDateTime odtDueDate, int nComplete, CString strCategories)
{
	AddItem(new CTaskItemType(bSharedTask));
	AddItem(new CTaskItemImportance(taskImportance));
	AddItem(new CTaskItemAttachment(bHasAttachment));
	AddItem(new CTaskItemStatus(taskStatus));
	AddItem(new CXTPReportRecordItemText(strSubject));
	AddItem(new CTaskItemDueDate(odtDueDate));
	AddItem(new CTaskItemComplete(nComplete));
	AddItem(new CXTPReportRecordItemText(strCategories));
}

void CTaskRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	if (((CTaskItemStatus*)GetItem(3))->m_taskStatus == taskStatusCompleted)
	{

		static CFont m_fontStriked;

		if (!m_fontStriked.GetSafeHandle())
		{
			LOGFONT lf;
			pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&lf);
			lf.lfStrikeOut = TRUE;

			m_fontStriked.CreateFontIndirect(&lf);
		}

		pItemMetrics->clrForeground = RGB(128, 128, 128);
		pItemMetrics->pFont = &m_fontStriked;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTaskListView

IMPLEMENT_DYNCREATE(CTaskListView, CXTPReportView)

CTaskListView::CTaskListView()
	: m_bAutoSizing(TRUE)
{
}

CTaskListView::~CTaskListView()
{
}


BEGIN_MESSAGE_MAP(CTaskListView, CXTPReportView)
	//{{AFX_MSG_MAP(CTaskListView)
	ON_WM_CREATE()

	ON_COMMAND(ID_REPORTCONTROL_ALLOWEDIT,         OnReportControlAllowEdit)
	ON_COMMAND(ID_REPORTCONTROL_EDITONCLICK,       OnReportControlEditOnClick)
	ON_COMMAND(ID_REPORTCONTROL_EDITONDELAYCLICK,  OnReportControlEditOnDelayClick)
	ON_COMMAND(ID_REPORTCONTROL_EDITONDOUBLECLICK, OnReportControlEditOnDoubleClick)
	ON_COMMAND(ID_REPORTCONTROL_FOCUSSUBITEMS,     OnReportControlFocusSubItems)
	ON_COMMAND(ID_REPORTCONTROL_AUTOSIZING,        OnReportControlAutoSizing)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_ALLOWEDIT,         OnUpdateReportControlAllowEdit)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_EDITONCLICK,       OnUpdateReportControlEditOnClick)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_EDITONDELAYCLICK,  OnUpdateReportControlEditOnDelayClick)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_EDITONDOUBLECLICK, OnUpdateReportControlEditOnDoubleClick)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_FOCUSSUBITEMS,     OnUpdateReportControlFocusSubItems)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_AUTOSIZING,        OnUpdateReportControlAutoSizing)
	
	ON_COMMAND(ID_EDIT_ADDTASK, OnAddTask)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_NOTIFY(XTP_NM_REPORT_INPLACEBUTTONDOWN, XTP_ID_REPORT_CONTROL, OnReportButtonClick)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskListView diagnostics

#ifdef _DEBUG
void CTaskListView::AssertValid() const
{
	CView::AssertValid();
}

void CTaskListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTaskListView message handlers


class CTaskListPaintManager : public CXTPReportPaintManager
{
public:

	virtual int GetRowHeight(CDC *pDC, CXTPReportRow *pRow, int nTotalWidth)
	{
		return 50;
	}
};


int CTaskListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CXTPReportControl& wndReport = GetReportCtrl();
	//wndReport.SetPaintManager(new CTaskListPaintManager());

	wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));

	wndReport.AddColumn(new CXTPReportColumn(COLUMN_TYPE, _T("Type"), 18, FALSE, 0));
	CXTPReportColumn *pColumnImportance = wndReport.AddColumn(new CXTPReportColumn(COLUMN_IMPORTANCE, _T("Importants"), 18, FALSE, 1));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_ATTACHMENT, _T("Attachments"), 18, FALSE, 7));
	CXTPReportColumn *pColumnStatus  = wndReport.AddColumn(new CXTPReportColumn(COLUMN_STATUS,   _T("Status"),     100, m_bAutoSizing));
	CXTPReportColumn *pColumnSubject = wndReport.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT,  _T("Subject"),    200, m_bAutoSizing));
	CXTPReportColumn *pColumnDueDate = wndReport.AddColumn(new CXTPReportColumn(COLUMN_DUE_DATE, _T("Due Date"),   100, m_bAutoSizing));
	CXTPReportColumn *pColumnPercent = wndReport.AddColumn(new CXTPReportColumn(COLUMN_COMPLETE, _T("% Complete"), 100, m_bAutoSizing));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_CATEGORIES, _T("Categories"), 80, m_bAutoSizing));
	
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Not Started"), taskStatusNotStarted);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("In Progress"), taskStatusInProgress);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Completed"), taskStatusCompleted);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Waiting on someone else"), taskStatusWaiting);
	pColumnStatus->GetEditOptions()->AddConstraint(_T("Deferred"), taskStatusDeferred);
	pColumnStatus->GetEditOptions()->m_bConstraintEdit = FALSE;
	pColumnStatus->GetEditOptions()->m_bAllowEdit = TRUE;
	pColumnStatus->GetEditOptions()->AddComboButton();

	pColumnSubject->GetEditOptions()->m_nMaxLength        = 40;
	pColumnSubject->GetEditOptions()->m_bSelectTextOnEdit = TRUE;
	pColumnSubject->GetEditOptions()->m_dwEditStyle       = ES_MULTILINE;


	pColumnImportance->GetEditOptions()->AddConstraint(_T("Low"), taskImportanceLow);
	pColumnImportance->GetEditOptions()->AddConstraint(_T("Normal"), taskImportanceNormal);
	pColumnImportance->GetEditOptions()->AddConstraint(_T("High"), taskImportanceHigh);
	pColumnImportance->GetEditOptions()->m_bAllowEdit = FALSE;
	pColumnImportance->GetEditOptions()->AddComboButton();

	pColumnDueDate->GetEditOptions()->AddComboButton();

	pColumnPercent->GetEditOptions()->AddSpinButton(TRUE);

	COleDateTime dtNone;
	COleDateTime dtNow = COleDateTime::GetCurrentTime();

	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceNormal, TRUE,  taskStatusNotStarted, _T("Support Email: Docking Pane ToggleDocking"), dtNone, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceHigh,   TRUE,  taskStatusNotStarted, _T("Feature Request: New Event for CommandBars"), dtNow, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(FALSE, taskImportanceNormal, TRUE,  taskStatusInProgress, _T("Support Email: Menus go wrong if another form has topmost setting"), dtNone, 10, _T("")));
	wndReport.AddRecord(new CTaskRecord(FALSE, taskImportanceNormal, TRUE,  taskStatusInProgress, _T("Support Email: Update Xtreme Suite from 8.6 to 8.7"), dtNone, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceLow,    TRUE,  taskStatusInProgress, _T("Support Email: Bug in Tree-View on Label Edit"), dtNone, 0, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceNormal, TRUE,  taskStatusInProgress, _T("Support Email: About tooltips"), dtNone, 70, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceHigh,   TRUE,  taskStatusCompleted,  _T("Support Email: Help Taskpanel And ShortcutBar"), dtNow, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceNormal, FALSE, taskStatusCompleted,  _T("Support Email: RE: Docking Pane Window Overlapping Issues"), dtNow, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceNormal, FALSE, taskStatusCompleted,  _T("Support Email: CXTPPropertyGridItem"), dtNone, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceNormal, TRUE,  taskStatusCompleted,  _T("Support Email: Toolbar Oddity"), dtNone, 100, _T("")));
	wndReport.AddRecord(new CTaskRecord(TRUE,  taskImportanceNormal, TRUE,  taskStatusCompleted,  _T("Support Email: CXTPTabControl"), dtNone, 100, _T("")));


	wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	wndReport.AllowEdit(TRUE);
	wndReport.FocusSubItems(TRUE);
	wndReport.Populate();

	wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpReportGridSolid);
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnResource);
	wndReport.GetPaintManager()->m_bShowNonActiveInPlaceButton = TRUE;

	wndReport.SetFocus();

	return 0;
}


void CTaskListView::OnReportControlAllowEdit()
{
	GetReportCtrl().AllowEdit(!GetReportCtrl().IsAllowEdit());
}

void CTaskListView::OnUpdateReportControlAllowEdit(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsAllowEdit()? TRUE: FALSE);
}


void CTaskListView::OnReportControlEditOnClick()
{
	GetReportCtrl().EditOnClick(!GetReportCtrl().IsEditOnClick());
}

void CTaskListView::OnUpdateReportControlEditOnClick(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsEditOnClick() ? 1 : 0);
	pCmdUI->Enable(GetReportCtrl().IsAllowEdit());
}


void CTaskListView::OnReportControlEditOnDelayClick()
{
	GetReportCtrl().EditOnDelayClick(!GetReportCtrl().IsEditOnDelayClick());
}

void CTaskListView::OnUpdateReportControlEditOnDelayClick(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsEditOnDelayClick() ? 1 : 0);
	pCmdUI->Enable(GetReportCtrl().IsAllowEdit());
}


void CTaskListView::OnReportControlEditOnDoubleClick()
{
	GetReportCtrl().EditOnDoubleClick(!GetReportCtrl().IsEditOnDoubleClick());
}

void CTaskListView::OnUpdateReportControlEditOnDoubleClick(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsEditOnDoubleClick()? 1: 0);
	pCmdUI->Enable(GetReportCtrl().IsAllowEdit());
}


void CTaskListView::OnReportControlFocusSubItems()
{
	GetReportCtrl().FocusSubItems(!GetReportCtrl().IsFocusSubItems());
}

void CTaskListView::OnUpdateReportControlFocusSubItems(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsFocusSubItems()? 1: 0);
}


void CTaskListView::OnUpdateReportControlAutoSizing(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bAutoSizing ? 1 : 0);
}

void CTaskListView::OnReportControlAutoSizing()
{
	m_bAutoSizing = !m_bAutoSizing;

	for (int nColumn=3; nColumn< GetReportCtrl().GetColumns()->GetCount(); nColumn++)
	{
		GetReportCtrl().GetColumns()->GetAt(nColumn)->SetAutoSize(m_bAutoSizing);
	}

	GetReportCtrl().GetReportHeader()->SetAutoColumnSizing(m_bAutoSizing);
}

void CTaskListView::OnAddTask() 
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

void CTaskListView::OnReportButtonClick(NMHDR * pNotifyStruct, LRESULT* pResult)
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
	GetReportCtrl().SetFocus();

	bResult = Show_XTPDatePicker(pControl, rcItem, dtDateValue);
		
	if (bResult < 0) 
	{		
		bResult = Show_MFCDatePicker(pControl, rcItem, dtDateValue);
	}

	if (!bResult) 
	{
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

BOOL CTaskListView::Show_XTPDatePicker(CXTPReportControl* pControl, 
										const CRect& rcItem,
										COleDateTime& rdtDate)
{
#ifdef _XTP_INCLUDE_CALENDAR
	CXTPDatePickerControl wndDatePicker;

	if(!wndDatePicker.GetSelectedDays())
	{
		ASSERT(FALSE);
		return FALSE;
	}

	wndDatePicker.SetMaxSelCount(1);
	wndDatePicker.GetSelectedDays()->Select(rdtDate);
	wndDatePicker.EnsureVisible(rdtDate);

	CRect rcSize;
	if (!wndDatePicker.GetMinReqRect(&rcSize, 1, 1) ) 
	{
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

BOOL CTaskListView::Show_MFCDatePicker(CXTPReportControl* pControl, 
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
