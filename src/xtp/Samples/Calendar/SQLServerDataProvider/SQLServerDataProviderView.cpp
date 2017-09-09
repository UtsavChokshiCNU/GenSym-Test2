// SQLServerDataProviderView.cpp : implementation of the CSQLServerDataProviderView class
//

#include "stdafx.h"
#include "SQLServerDataProvider.h"
#include "SQLServerDataProviderDoc.h"
#include "SQLServerDataProviderView.h"

#include "MainFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderView

IMPLEMENT_DYNCREATE(CSQLServerDataProviderView, CXTPCalendarControlView)

BEGIN_MESSAGE_MAP(CSQLServerDataProviderView, CXTPCalendarControlView)
	//{{AFX_MSG_MAP(CSQLServerDataProviderView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CXTPCalendarControlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CXTPCalendarControlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CXTPCalendarControlView::OnFilePrintPreview)

	ON_COMMAND(ID_CALENDAR_VIEW_DAY, OnCalendarViewDay)
	ON_COMMAND(ID_CALENDAR_VIEW_WORKWEEK, OnCalendarViewWorkWeek)
	ON_COMMAND(ID_CALENDAR_VIEW_WEEK, OnCalendarViewWeek)
	ON_COMMAND(ID_CALENDAR_VIEW_MONTH, OnCalendarViewMonth)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_DAY, OnUpdateCalendarViewDay)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_WORKWEEK, OnUpdateCalendarViewWorkWeek)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_WEEK, OnUpdateCalendarViewWeek)
	ON_UPDATE_COMMAND_UI(ID_CALENDAR_VIEW_MONTH, OnUpdateCalendarViewMonth)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderView construction/destruction

CSQLServerDataProviderView::CSQLServerDataProviderView()
{
	// TODO: add construction code here

}

CSQLServerDataProviderView::~CSQLServerDataProviderView()
{
}

BOOL CSQLServerDataProviderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CXTPCalendarControlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderView drawing

void CSQLServerDataProviderView::OnDraw(CDC* pDC)
{
	CSQLServerDataProviderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderView diagnostics

#ifdef _DEBUG
void CSQLServerDataProviderView::AssertValid() const
{
	CXTPCalendarControlView::AssertValid();
}

void CSQLServerDataProviderView::Dump(CDumpContext& dc) const
{
	CXTPCalendarControlView::Dump(dc);
}

CSQLServerDataProviderDoc* CSQLServerDataProviderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSQLServerDataProviderDoc)));
	return (CSQLServerDataProviderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderView message handlers

void CSQLServerDataProviderView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{	  
	CSQLServerDataProviderDoc* pDocument = GetDocument();
	ASSERT(pDocument);
	
	if (!pDocument)
		return;

	if (lHint & CSQLServerDataProviderDoc::uvfSetDataProvider)
	{
		GetCalendarCtrl().SetDataProvider(pDocument->GetDataProvider_SQLServer(), FALSE);		
	}

	if (lHint & CSQLServerDataProviderDoc::uvfDetachDataProvider)
	{
		GetCalendarCtrl().SetDataProvider(xtpCalendarDataProviderMemory);		
	}

	if (lHint & CSQLServerDataProviderDoc::uvfPopulate)
	{
		GetCalendarCtrl().Populate();
	}	
}

void CSQLServerDataProviderView::OnInitialUpdate() 
{
	CXTPCalendarControlView::OnInitialUpdate();

	GetCalendarCtrl().SwitchActiveView(xtpCalendarWorkWeekView);

//	CXTPCalendarThemeOffice2007* pTheme2007 = DYNAMIC_DOWNCAST(CXTPCalendarThemeOffice2007, GetCalendarCtrl().GetTheme());
//	if (pTheme2007)
//	{
//		pTheme2007->GetMonthViewPartX()->GetEventPartX()->GetEventIconsToDrawPartX()->m_ShowOccurrence = TRUE;
//		pTheme2007->GetMonthViewPartX()->GetEventPartX()->GetEventIconsToDrawPartX()->m_ShowException = TRUE;
//
//		GetCalendarCtrl().GetTheme()->RefreshMetrics();
//	}

	GetCalendarCtrl().EnableReminders();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	if (::IsWindow(pWnd->GetSafeHwnd()))
	{
		m_calController.SetCalendar(&GetCalendarCtrl());
		m_calController.SetDatePicker(&pWnd->GetDatePicker());
	}
}

void CSQLServerDataProviderView::OnCalendarViewDay() 
{
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarDayView) 
	{
		GetCalendarCtrl().SwitchActiveView(xtpCalendarDayView);
	}	
}

void CSQLServerDataProviderView::OnCalendarViewWorkWeek() 
{
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarWorkWeekView) 
	{
		GetCalendarCtrl().SwitchActiveView(xtpCalendarWorkWeekView);
	}	
}

void CSQLServerDataProviderView::OnCalendarViewWeek() 
{
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarWeekView) 
	{
		GetCalendarCtrl().SwitchActiveView(xtpCalendarWeekView);
	}
}

void CSQLServerDataProviderView::OnCalendarViewMonth() 
{   
	if(GetCalendarCtrl().GetActiveView() && 
		GetCalendarCtrl().GetActiveView()->GetViewType() != xtpCalendarMonthView) 
	{
		TRACE(_T("Switch to month view.\n"));
		GetCalendarCtrl().SwitchActiveView(xtpCalendarMonthView);

	}
}

void CSQLServerDataProviderView::OnUpdateCalendarViewDay(CCmdUI* pCmdUI) 
{
	BOOL bViewDay = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarDayView) {
		bViewDay = TRUE;			
	}
	pCmdUI->SetCheck(bViewDay);	
}

void CSQLServerDataProviderView::OnUpdateCalendarViewWorkWeek(CCmdUI* pCmdUI) 
{
	BOOL bViewDays = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarWorkWeekView) {
		bViewDays = TRUE;			
	}
	pCmdUI->SetCheck(bViewDays);	
}

void CSQLServerDataProviderView::OnUpdateCalendarViewWeek(CCmdUI* pCmdUI) 
{
	BOOL bViewWeek = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarWeekView) 
		bViewWeek = TRUE;	
	pCmdUI->SetCheck(bViewWeek);	
}

void CSQLServerDataProviderView::OnUpdateCalendarViewMonth(CCmdUI* pCmdUI) 
{
	BOOL bViewMonth = FALSE;
	CXTPCalendarView* pView = GetCalendarCtrl().GetActiveView();
	if (pView && pView->GetViewType() == xtpCalendarMonthView) 
		bViewMonth = TRUE; 
	pCmdUI->SetCheck(bViewMonth);	
}
