// OptionsDialogBar.cpp : implementation file
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
#include "calendardemo.h"
#include "OptionsDialogBar.h"
#include "MainFrm.h"
#include "CalendarDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialogBar dialog


COptionsDialogBar::COptionsDialogBar(CWnd* /*pParent =NULL*/)	
{
	//{{AFX_DATA_INIT(COptionsDialogBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionsDialogBar::~COptionsDialogBar()	
{
	m_Sink.UnadviseAll();
}


void COptionsDialogBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialogBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(COptionsDialogBar)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE_VOID(WM_INITDIALOG, OnInitDialog)
	ON_BN_CLICKED(IDD_MONTH_COMPRESS_WEEKEND_DAYS, OnBnClickedMonthCompressWeekendDays)
	ON_BN_CLICKED(IDD_MONTH_SHOW_END_TIME, OnBnClickedMonthShowEndTime)
	ON_BN_CLICKED(IDD_MONTH_SHOW_TIME_AS_CLOCKS, OnBnClickedMonthSchowTimeAsClock)
	ON_BN_CLICKED(IDD_TIMELINE_COMPACT, OnBnClickedTimelineCompact)
	ON_CBN_SELCHANGE(IDC_FIRST_DAY_OF_WEEK_CB, OnCbnSelchangeFirstDayOfWeekCb)
	ON_CBN_SELCHANGE(IDD_MONTH_WEEKS_COUNT, OnCbnSelchangeMonthWeeksCount)
	ON_CBN_SELCHANGE(IDC_TIME_SCALE, OnCbnSelchangeTimeScale)
	ON_BN_CLICKED(IDD_WEEK_SHOW_TIME_AS_CLOCK, OnBnClickedWeekSchowTimeAsClock)
	ON_BN_CLICKED(IDD_WEEK_SHOW_END_TIME, OnBnClickedWeekShowEndTime)
	ON_CBN_SELCHANGE(IDC_START_TIME_CB, OnCbnSelchangeStartTimeCb)
	ON_CBN_SELCHANGE(IDC_END_TIME_CB, OnCbnSelchangeEndTimeCb)
	ON_CBN_SELCHANGE(IDC_START_TIME_CB2, OnCbnSelchangeMinMaxScaleTimeCb)
	ON_CBN_SELCHANGE(IDC_END_TIME_CB2, OnCbnSelchangeMinMaxScaleTimeCb)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_SU, OnBnClickedWorkWeekDay)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_MO, OnBnClickedWorkWeekDay)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_TU, OnBnClickedWorkWeekDay)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_WE, OnBnClickedWorkWeekDay)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_TH, OnBnClickedWorkWeekDay)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_FR, OnBnClickedWorkWeekDay)
	ON_BN_CLICKED(IDC_WORK_WEEK_DAY_SA, OnBnClickedWorkWeekDay)

	ON_CBN_SELCHANGE(IDC_TOOLTIP_MODE, OnCbnSelchangeTooltipMode)

	ON_BN_CLICKED(IDC_CHECK_SHOW_TSMINUTES, OnShowTimeScaleMinutes)
	ON_BN_CLICKED(IDC_CHECK7, OnEcoMode)
	ON_BN_CLICKED(IDC_CHECK9, OnDayHeaderFormat)
	ON_BN_CLICKED(IDC_CHECK6, OnCustomTooltip)
	ON_BN_CLICKED(IDC_CHECK8, OnFullDateMode)
	ON_BN_CLICKED(IDC_CHECK4, OnMutliColumnMode)
	ON_BN_CLICKED(IDC_CHECK1, OnMonthViewDraftMode)
	ON_BN_CLICKED(IDC_CHECK5, OnRTL)
	ON_BN_CLICKED(IDC_CHECK3, OnTooltilUnderMouse)
	ON_BN_CLICKED(IDC_RADIO2, OnDayHeaderPeriod)
	ON_BN_CLICKED(IDC_RADIO3, OnDayHeaderPeriod2)
	ON_BN_CLICKED(IDC_RADIO4, OnDayHeaderPeriod3)
	ON_BN_CLICKED(IDC_CHECK10, OnFullScalePrinting)
	ON_BN_CLICKED(IDC_CHECK11, OnReadOnlyMode)
	ON_BN_CLICKED(IDC_CHECK12, OnMultiColorSchedules)
	ON_BN_CLICKED(IDC_CHECK13, OnPreventAutoAllDay)
	ON_BN_CLICKED(IDC_CHECK14, OnDatePickerYearArrows)
	ON_BN_CLICKED(IDC_CHECK15, OnShowCaptionBar)
	ON_BN_CLICKED(IDC_CHECK16, OnHide4TimelineMode)
	ON_BN_CLICKED(IDC_CHECK17, OnOneLineLayout)
	ON_BN_CLICKED(IDC_CHECK18, OnHideMonthView)
	ON_BN_CLICKED(IDC_CHECK19, OnShowMonthViewButton)
	ON_BN_CLICKED(IDC_CHECK20, OnHideTimelieButton)
	ON_BN_CLICKED(IDC_RADIO5, OnDayViewPrintFull)
	ON_BN_CLICKED(IDC_RADIO6, OnDayViewPrintSave)
	ON_BN_CLICKED(IDC_RADIO7, OnDayViewPrintDraft)
	ON_BN_CLICKED(IDC_CHECK_SINGLE_CLICK, OnDatePickerSingleClick)
END_MESSAGE_MAP()

void COptionsDialogBar::OnInitDialog() 
{
	Default();
	int i;
	
	if (m_arOptCtrlIDsAll.GetSize() == 0) 
	{	
		VERIFY( m_ctrlWorkWeekDays[0].SubclassDlgItem(IDC_WORK_WEEK_DAY_SU, this));
		VERIFY( m_ctrlWorkWeekDays[1].SubclassDlgItem(IDC_WORK_WEEK_DAY_MO, this));
		VERIFY( m_ctrlWorkWeekDays[2].SubclassDlgItem(IDC_WORK_WEEK_DAY_TU, this));
		VERIFY( m_ctrlWorkWeekDays[3].SubclassDlgItem(IDC_WORK_WEEK_DAY_WE, this));
		VERIFY( m_ctrlWorkWeekDays[4].SubclassDlgItem(IDC_WORK_WEEK_DAY_TH, this));
		VERIFY( m_ctrlWorkWeekDays[5].SubclassDlgItem(IDC_WORK_WEEK_DAY_FR, this));
		VERIFY( m_ctrlWorkWeekDays[6].SubclassDlgItem(IDC_WORK_WEEK_DAY_SA, this));
				
		VERIFY( m_ctrlFirstDayOfWeekCb.SubclassDlgItem(IDC_FIRST_DAY_OF_WEEK_CB, this));
		VERIFY( m_ctrlStartTimeCb.SubclassDlgItem(IDC_START_TIME_CB, this));
		VERIFY( m_ctrlEndTimeCb.SubclassDlgItem(IDC_END_TIME_CB, this));

		VERIFY( m_ctrlMinScaleTimeCb.SubclassDlgItem(IDC_START_TIME_CB2, this));
		VERIFY( m_ctrlMaxScaleTimeCb.SubclassDlgItem(IDC_END_TIME_CB2, this));

		for (i = 0; i < 7; i++) 
		{
			m_arOptCtrlIDsCommon.Add(m_ctrlWorkWeekDays[i].GetDlgCtrlID());
		}
		m_arOptCtrlIDsCommon.Add(IDC_WORK_WEEK_FRAME);
		m_arOptCtrlIDsCommon.Add(IDC_FIRST_DAY_OF_WEEK_CB);
		m_arOptCtrlIDsCommon.Add(IDC_FIRST_DAY_OF_WEEK_TEXT);
		m_arOptCtrlIDsCommon.Add(IDC_START_TIME_CB);
		m_arOptCtrlIDsCommon.Add(IDC_START_TIME_TEXT);
		m_arOptCtrlIDsCommon.Add(IDC_END_TIME_CB);
		m_arOptCtrlIDsCommon.Add(IDC_END_TIME_TEXT);

		m_arOptCtrlIDsCommon.Add(IDC_START_TIME_CB2);
		m_arOptCtrlIDsCommon.Add(IDC_START_TIME_TEXT2);
		m_arOptCtrlIDsCommon.Add(IDC_END_TIME_CB2);
		m_arOptCtrlIDsCommon.Add(IDC_END_TIME_TEXT2);

		m_arOptCtrlIDsCommon.Add(IDC_ADVANCED_FRAME);
		m_arOptCtrlIDsCommon.Add(IDC_ADVANCED_OPT_BTN);

		m_arOptCtrlIDsCommon.Add(IDC_BOTTOM_FRAME_STATIC);
			
		VERIFY( m_ctrlTooltipMode.SubclassDlgItem(IDC_TOOLTIP_MODE, this));
			
		// Day View ----------------------------
		VERIFY( m_ctrlSelchangeTimeScaleCb.SubclassDlgItem(IDC_TIME_SCALE, this));
		
		m_arOptCtrlIDsDayView.Add(IDC_DAY_VIEW_FRAME);
		m_arOptCtrlIDsDayView.Add(IDC_TIME_SCALE);
		m_arOptCtrlIDsDayView.Add(IDC_TIME_SCALE_TEXT);		
		m_arOptCtrlIDsDayView.Add(IDC_TIME_ZONE_BTN);

		// Month View ----------------------------
		VERIFY( m_ctrlMonth_ShowEndTime.SubclassDlgItem(IDD_MONTH_SHOW_END_TIME, this));
		VERIFY( m_ctrlMonth_ShowTimeAsClocks.SubclassDlgItem(IDD_MONTH_SHOW_TIME_AS_CLOCKS, this));
		VERIFY( m_ctrlMonth_CompressWeekendDays.SubclassDlgItem(IDD_MONTH_COMPRESS_WEEKEND_DAYS, this));
		VERIFY( m_ctrlMonth_WeeksCount.SubclassDlgItem(IDD_MONTH_WEEKS_COUNT, this));
	
		m_arOptCtrlIDsMonthView.Add(IDC_MONTH_VIEW_FRAME);
		m_arOptCtrlIDsMonthView.Add(IDD_MONTH_SHOW_END_TIME);
		m_arOptCtrlIDsMonthView.Add(IDD_MONTH_SHOW_TIME_AS_CLOCKS);
		m_arOptCtrlIDsMonthView.Add(IDD_MONTH_COMPRESS_WEEKEND_DAYS);
		m_arOptCtrlIDsMonthView.Add(IDD_MONTH_WEEKS_COUNT);
		m_arOptCtrlIDsMonthView.Add(IDD_MONTH_WEEKS_COUNT_TEXT);		

		// Week View ----------------------------
		VERIFY( m_ctrlWeek_ShowTimeAsClock.SubclassDlgItem(IDD_WEEK_SHOW_TIME_AS_CLOCK, this));
		VERIFY( m_ctrlWeek_ShowEndTime.SubclassDlgItem(IDD_WEEK_SHOW_END_TIME, this));
		
		m_arOptCtrlIDsWeekView.Add(IDC_WEEK_VIEW_FRAME);
		m_arOptCtrlIDsWeekView.Add(IDD_WEEK_SHOW_TIME_AS_CLOCK);
		m_arOptCtrlIDsWeekView.Add(IDD_WEEK_SHOW_END_TIME);

		// Timeline View ----------------------------
		VERIFY( m_ctrlCompactTimelineEvents.SubclassDlgItem(IDD_TIMELINE_COMPACT, this));
		m_arOptCtrlIDsTimelineView.Add(IDD_TIMELINE_COMPACT);
		//===========================================================================
		m_arOptCtrlIDsAll.Append(m_arOptCtrlIDsCommon);
		m_arOptCtrlIDsAll.Append(m_arOptCtrlIDsDayView);
		m_arOptCtrlIDsAll.Append(m_arOptCtrlIDsWeekView);
		m_arOptCtrlIDsAll.Append(m_arOptCtrlIDsMonthView);
		m_arOptCtrlIDsAll.Append(m_arOptCtrlIDsTimelineView);
	}

	CString strTmp;
	//---------------------------------------------------------------------------
	for (i = 0; i < 7; i++) 
	{
		m_ctrlWorkWeekDays[i].SetCheck((i > 0 && i < 6) ? 1 : 0);
	}
	//---------------------------------------------------------------------------
	int arScales[] = {60, 30, 15, 10, 6, 5}; 	
	m_ctrlSelchangeTimeScaleCb.ResetContent();
	for (i = 0; i < sizeof(arScales) / sizeof(arScales[0]); i++) 
	{
		strTmp.Format(_T("%d minutes"), arScales[i]);
		int nIndex = m_ctrlSelchangeTimeScaleCb.AddString(strTmp);
		m_ctrlSelchangeTimeScaleCb.SetItemData(nIndex, arScales[i]);
	}
	m_ctrlSelchangeTimeScaleCb.SetCurSel(1);
	//---------------------------------------------------------------------------
	TCHAR* srWDays[] = {_T("Sunday"), _T("Monday"), _T("Tuesday"), _T("Wednesday"), _T("Thursday"), _T("Friday"), _T("Saturday")}; 
    	
	m_ctrlFirstDayOfWeekCb.ResetContent();
	for (i = 0; i < 7; i++) 
	{
		int nIndex = m_ctrlFirstDayOfWeekCb.AddString(srWDays[i]); 		
		m_ctrlFirstDayOfWeekCb.SetItemData(nIndex, i+1);
	}
	m_ctrlFirstDayOfWeekCb.SetCurSel(1);
		
	//---------------------------------------------------------------------------
	COleDateTimeSpan spHalfHour(0,0,30,0);
	COleDateTime dtHours;
	dtHours.SetTime(0, 0, 0);

	m_ctrlStartTimeCb.ResetContent();
	m_ctrlEndTimeCb.ResetContent();

	m_ctrlMinScaleTimeCb.ResetContent();
	m_ctrlMaxScaleTimeCb.ResetContent();

	for (i = 0; i <= 48; i++) 
	{
//<<>>
		if (i < 48)
			strTmp.Format(_T("%02d:%02d"), dtHours.GetHour(), dtHours.GetMinute());
		else
			strTmp = _T("23:59:59");	
		int nIndex = m_ctrlStartTimeCb.AddString(strTmp); 		
		m_ctrlStartTimeCb.SetItemData(nIndex, i);
		
		nIndex = m_ctrlEndTimeCb.AddString(strTmp); 		
		m_ctrlEndTimeCb.SetItemData(nIndex, i);

		nIndex = m_ctrlMinScaleTimeCb.AddString(strTmp); 		
		m_ctrlMinScaleTimeCb.SetItemData(nIndex, i);

		nIndex = m_ctrlMaxScaleTimeCb.AddString(strTmp); 		
		m_ctrlMaxScaleTimeCb.SetItemData(nIndex, i);

		dtHours += spHalfHour;		
//Client App should use stored values here
		//if (i == 16)
		//{
		//	m_ctrlStartTimeCb.SetWindowText(strTmp);
		//	m_ctrlStartTimeCb.SetCurSel(16);

		//	m_ctrlMinScaleTimeCb.SetWindowText(strTmp);
		//	m_ctrlMinScaleTimeCb.SetCurSel(16);
		//}
		//else if (i == 34)
		//{
		//	m_ctrlEndTimeCb.SetWindowText(strTmp);
		//	m_ctrlEndTimeCb.SetCurSel(34);

		//	m_ctrlMaxScaleTimeCb.SetWindowText(strTmp);
		//	m_ctrlMaxScaleTimeCb.SetCurSel(34);
		//}
	}

	//-----------------------------------------------------------------------
	m_ctrlTooltipMode.ResetContent();

	ASSERT(m_ctrlTooltipMode.GetCount() == 0);
	
	int nIdx = m_ctrlTooltipMode.AddString(_T("Standard"));
	m_ctrlTooltipMode.SetItemData(nIdx, ctmStandard);

	nIdx = m_ctrlTooltipMode.AddString(_T("Custom"));
	m_ctrlTooltipMode.SetItemData(nIdx, ctmCustom);

	nIdx = m_ctrlTooltipMode.AddString(_T("Disabled"));
	m_ctrlTooltipMode.SetItemData(nIdx, ctmDisabled);
	
	//===========================================================================

	m_ctrlMonth_ShowEndTime.SetCheck(0);
	m_ctrlMonth_ShowTimeAsClocks.SetCheck(0);
	m_ctrlMonth_CompressWeekendDays.SetCheck(1);
	m_ctrlWeek_ShowTimeAsClock.SetCheck(0);
	m_ctrlWeek_ShowEndTime.SetCheck(1);
    
	//---------------------------------------------------------------------------	
	m_ctrlMonth_WeeksCount.ResetContent();
	for (i = 2; i <= 6; i++) 
	{
		strTmp.Format(_T("%d"), i);
		int nIndex = m_ctrlMonth_WeeksCount.AddString(strTmp); 		
		m_ctrlMonth_WeeksCount.SetItemData(nIndex, i);
	}

	m_ctrlMonth_WeeksCount.SetCurSel(3);
}

CXTPCalendarControl* COptionsDialogBar::GetCalendarCtrl()
{
	CView* pView = ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	ASSERT_KINDOF(CCalendarDemoView, pView);

	if (pView)
		return &((CCalendarDemoView*)pView)->GetCalendarCtrl();
	else
		return NULL;
}


void COptionsDialogBar::OnBnClickedMonthCompressWeekendDays()
{
	int nCheck = m_ctrlMonth_CompressWeekendDays.GetCheck();
	GetCalendarCtrl()->MonthView_SetCompressWeekendDays(nCheck ? TRUE : FALSE);
	GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::OnBnClickedMonthShowEndTime()
{
	int nCheck = m_ctrlMonth_ShowEndTime.GetCheck();
	GetCalendarCtrl()->MonthView_SetShowEndDate(nCheck ? TRUE : FALSE);
	GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::OnBnClickedMonthSchowTimeAsClock()
{
	int nCheck = m_ctrlMonth_ShowTimeAsClocks.GetCheck();
	GetCalendarCtrl()->MonthView_SetShowTimeAsClocks(nCheck ? TRUE : FALSE);
	GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::OnBnClickedTimelineCompact()
{
	GetCalendarCtrl()->GetCalendarOptions()->bTimeLineCompact =
		m_ctrlCompactTimelineEvents.GetCheck();
	GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::OnCbnSelchangeFirstDayOfWeekCb()
{
	int nSel = m_ctrlFirstDayOfWeekCb.GetCurSel();	
	GetCalendarCtrl()->SetFirstDayOfWeek(nSel + 1);
	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl()->GetDayView());
	if (!pDayView)
		GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::PopulateWorkDays()
{
	// update picture
	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl()->GetDayView());
	if (pDayView)
	{
		// show working days interval
		COleDateTime dtDayViewStart;
		pDayView->GetSelection(&dtDayViewStart);
		pDayView->ShowWorkingDays(dtDayViewStart);
	}	
	else
	{
		GetCalendarCtrl()->Populate();
	}
}

void COptionsDialogBar::OnCbnSelchangeMonthWeeksCount()
{
	int nSel = m_ctrlMonth_WeeksCount.GetCurSel();
	CXTPCalendarMonthView* pMonthView = DYNAMIC_DOWNCAST(CXTPCalendarMonthView, GetCalendarCtrl()->GetActiveView());
	if (pMonthView) 
	{
		pMonthView->GetGrid()->SetWeeksCount(nSel+2);
		GetCalendarCtrl()->Populate();
	}
}

void COptionsDialogBar::OnCbnSelchangeTimeScale()
{   
	int nSel = m_ctrlSelchangeTimeScaleCb.GetCurSel();
	if (nSel == CB_ERR) 
		return;

	int nScale = (int)m_ctrlSelchangeTimeScaleCb.GetItemData(nSel);

	CCalendarDemoView* pView = (CCalendarDemoView*)(((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView());
	if (pView)
		pView->SetCalendarTimeScale(nScale);
}

void COptionsDialogBar::OnBnClickedWeekSchowTimeAsClock()
{
	int nCheck = m_ctrlWeek_ShowTimeAsClock.GetCheck();
	GetCalendarCtrl()->WeekView_SetShowTimeAsClocks(nCheck ? TRUE : FALSE);
	GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::OnBnClickedWeekShowEndTime()
{
	int nCheck = m_ctrlWeek_ShowEndTime.GetCheck();
	GetCalendarCtrl()->WeekView_SetShowEndDate(nCheck ? TRUE : FALSE);
	GetCalendarCtrl()->Populate();
}

void COptionsDialogBar::OnBnClickedTimeZoneBtn()
{
	//CalendarTimezone();
}

void COptionsDialogBar::OnCbnSelchangeStartTimeCb()
{
	int nSel = m_ctrlStartTimeCb.GetCurSel();
	int nSel2 = m_ctrlEndTimeCb.GetCurSel();

	if (nSel == CB_ERR || nSel2 == CB_ERR ) 
	{
		return;
	}
	if (nSel > nSel2) 
	{
		nSel2 = nSel;
		m_ctrlEndTimeCb.SetCurSel(nSel2);
	}

	COleDateTimeSpan spHalfHour(0,0,30,0);

	DWORD dwI = (DWORD)m_ctrlStartTimeCb.GetItemData(nSel);
	COleDateTime dtHour = (double)spHalfHour * dwI;
        	
	GetCalendarCtrl()->SetWorkDayStartTime(dtHour.GetHour(), dtHour.GetMinute(), 0); 
	GetCalendarCtrl()->Populate();
	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl()->GetDayView());
	if (pDayView)
		pDayView->ScrollToWorkDayBegin();
}

void COptionsDialogBar::OnCbnSelchangeEndTimeCb()
{
	int nSel1 = m_ctrlStartTimeCb.GetCurSel();
	int nSel = m_ctrlEndTimeCb.GetCurSel();

	if (nSel == CB_ERR || nSel1 == CB_ERR ) 
	{
		return;
	}
	if (nSel < nSel1) 
	{
		nSel1 = nSel;
		m_ctrlStartTimeCb.SetCurSel(nSel1);
	}

	COleDateTimeSpan spHalfHour(0,0,30,0);

	DWORD dwI = (DWORD)m_ctrlEndTimeCb.GetItemData(nSel);
	COleDateTime dtHour = (double)spHalfHour * dwI;
	if (dtHour.GetHour() == 0)
		GetCalendarCtrl()->SetWorkDayEndTime(23, 59, 59); 
	else    	
		GetCalendarCtrl()->SetWorkDayEndTime(dtHour.GetHour(), dtHour.GetMinute(), 0); 
	GetCalendarCtrl()->Populate();
	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl()->GetDayView());
	if (pDayView)
		pDayView->ScrollToWorkDayBegin();
}

void COptionsDialogBar::OnCbnSelchangeMinMaxScaleTimeCb()
{
	int nSelMin = m_ctrlMinScaleTimeCb.GetCurSel();
	int nSelMax = m_ctrlMaxScaleTimeCb.GetCurSel();
	
	if (nSelMin == CB_ERR || nSelMax == CB_ERR )
		return;

	if (nSelMin >= nSelMax) 
	{
		m_ctrlMaxScaleTimeCb.SetCurSel(nSelMin);
		m_ctrlMinScaleTimeCb.SetCurSel(nSelMin);
		return;
	}
	
	COleDateTimeSpan spHalfHour(0,0,30,0);
	
	DWORD dwI1 = (DWORD)m_ctrlMinScaleTimeCb.GetItemData(nSelMin);
	COleDateTime dtNewMin = (double)spHalfHour * dwI1;
	
	DWORD dwI2 = (DWORD)m_ctrlMaxScaleTimeCb.GetItemData(nSelMax);
	COleDateTime dtNewMax = (double)spHalfHour * dwI2;

	if (dtNewMax.GetHour() == 0)
		dtNewMax.SetTime(23, 59, 59); 

	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl()->GetDayView());
	if (pDayView)
	{
		// update scale interval
		pDayView->SetScaleMinTime(dtNewMin);
		pDayView->SetScaleMaxTime(dtNewMax);

		GetCalendarCtrl()->GetCalendarOptions()->dtScaleMinTime = dtNewMin;
		GetCalendarCtrl()->GetCalendarOptions()->dtScaleMaxTime = dtNewMax;

		GetCalendarCtrl()->Populate();
	}
}

void COptionsDialogBar::OnBnClickedWorkWeekDay()
{
	int nWWMask = 0;
	for (int i = 0; i < 7; i++) 
	{
		if (m_ctrlWorkWeekDays[i].GetCheck()) 
		{
			nWWMask |=  CXTPCalendarUtils::GetDayOfWeekMask(i+1);			
		}
	}
	if (nWWMask == 0)
	{
		m_ctrlWorkWeekDays[0].SetCheck(1);
		nWWMask |=  CXTPCalendarUtils::GetDayOfWeekMask(1);
	}
	GetCalendarCtrl()->SetWorkWeekMask(nWWMask);
	PopulateWorkDays();
}

void COptionsDialogBar::OnViewChanged(XTPCalendarViewType viewType)
{
	if (viewType == xtpCalendarWeekView)
	{
		OnBnClickedWeekSchowTimeAsClock();
		OnBnClickedWeekShowEndTime();	
	}
	if (viewType == xtpCalendarMonthView)
	{
		OnBnClickedMonthCompressWeekendDays();
		OnBnClickedMonthShowEndTime();
		OnCbnSelchangeFirstDayOfWeekCb();
		OnCbnSelchangeMonthWeeksCount();
	}
}

void COptionsDialogBar::OnCalendarEvent_TimeScaleWasChanged(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam); UNREFERENCED_PARAMETER(lParam);

	if (Event != XTP_NC_CALENDARVIEWTIMESCALEWASCHANGED) 
	{
		ASSERT(FALSE);
		return;
	}
    
	int nCurrScale = -1;
	int nSel = m_ctrlSelchangeTimeScaleCb.GetCurSel();
	if (nSel != CB_ERR) 
	{
		nCurrScale = (int)m_ctrlSelchangeTimeScaleCb.GetItemData(nSel);	
	}

	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, GetCalendarCtrl()->GetDayView());
	if (!pDayView) 
		return;

	COleDateTimeSpan spScale = pDayView->GetScaleInterval();
	int nNewScale = (int)spScale.GetTotalMinutes();

	if (nCurrScale == nNewScale)	
		return;

	int nCount = m_ctrlSelchangeTimeScaleCb.GetCount();
	for (int i = 0; i < nCount; i++) 
	{   				
		if (nNewScale == (int)m_ctrlSelchangeTimeScaleCb.GetItemData(i)) 
		{
			m_ctrlSelchangeTimeScaleCb.SetCurSel(i);
			break;
		}
	}
}

void COptionsDialogBar::OnCalendarEvent_ViewWasChanged(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam); UNREFERENCED_PARAMETER(lParam);

	if (Event != XTP_NC_CALENDARVIEWWASCHANGED) 
	{
		ASSERT(FALSE);
		return;
	}

	UpdateControlsState();
}

void COptionsDialogBar::Init()
{
	Close();

	CXTPCalendarControl* pCalendar = GetCalendarCtrl();

	if (!pCalendar) 
	{
		ASSERT(FALSE);
		return;
	}

	CXTPNotifyConnection* pCConn = pCalendar->GetConnection();
	ASSERT(pCConn);

	m_Sink.Advise(pCConn, XTP_NC_CALENDARVIEWTIMESCALEWASCHANGED, &COptionsDialogBar::OnCalendarEvent_TimeScaleWasChanged);
	m_Sink.Advise(pCConn, XTP_NC_CALENDARVIEWWASCHANGED, &COptionsDialogBar::OnCalendarEvent_ViewWasChanged);

	UpdateControlsState();
}

void COptionsDialogBar::Close()
{
	m_Sink.UnadviseAll();
}

void COptionsDialogBar::UpdateControlsState()
{
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	CView* pView = ((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	ASSERT_KINDOF(CCalendarDemoView, pView);
	
	CCalendarDemoView* pDemoView = (CCalendarDemoView*)pView;


	if (!pCalendar || !pDemoView) 
	{
		ASSERT(FALSE);
		return;
	}

	//===========================================================================
	int nWorkWeekMask = pCalendar->GetWorkWeekMask();
	CString strTmp;
	int i;
	//---------------------------------------------------------------------------
	for (i = 0; i < 7; i++) 
	{
		int nCheck = (nWorkWeekMask & CXTPCalendarUtils::GetDayOfWeekMask(i+1)) ? 1 : 0;
		m_ctrlWorkWeekDays[i].SetCheck(nCheck);
	}
	//---------------------------------------------------------------------------
	OnCalendarEvent_TimeScaleWasChanged(XTP_NC_CALENDARVIEWTIMESCALEWASCHANGED, 0, 0);
	
	//---------------------------------------------------------------------------
	int nFirstDayOfWeek = pCalendar->GetFirstDayOfWeek();
		
	for (i = 0; i < 7; i++) 
	{   		
		if ((int)m_ctrlFirstDayOfWeekCb.GetItemData(i) == nFirstDayOfWeek) 
		{
			m_ctrlFirstDayOfWeekCb.SetCurSel(i);
			break;
		}
	}      	

	//---------------------------------------------------------------------------
	COleDateTime dtWWStartTime, dtWWEndTime;
	pCalendar->GetWorkDayStartTime(dtWWStartTime);
	pCalendar->GetWorkDayEndTime(dtWWEndTime);

	int nIndex1 = dtWWStartTime.GetHour() * 2 + (dtWWStartTime.GetMinute() ? 1 : 0);
	int nIndex2 = dtWWEndTime.GetHour() * 2 + (dtWWEndTime.GetMinute() ? 1 : 0);
	m_ctrlStartTimeCb.SetCurSel(nIndex1);
//<<>>
	if (dtWWEndTime.GetMinute() == 59)
		nIndex2++;
//<<>>
	m_ctrlEndTimeCb.SetCurSel(nIndex2);

	COleDateTime dtScaleMinTime = GetCalendarCtrl()->GetCalendarOptions()->dtScaleMinTime;
	COleDateTime dtScaleMaxTime = GetCalendarCtrl()->GetCalendarOptions()->dtScaleMaxTime;
	int n1 = dtScaleMinTime.GetHour() * 2 + (dtScaleMinTime.GetMinute() ? 1 : 0);
	int n2 = dtScaleMaxTime.GetHour() * 2 + (dtScaleMaxTime.GetMinute() ? 1 : 0);
//<<>>
	if (dtScaleMaxTime.GetMinute() == 59)
		n2++;
//<<>>
	m_ctrlMinScaleTimeCb.SetCurSel(n1);
	m_ctrlMaxScaleTimeCb.SetCurSel(n2);		

	CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
	if (pDayView) 
	{
		pDayView->SetScaleMinTime(dtScaleMinTime);
		pDayView->SetScaleMaxTime(dtScaleMaxTime);

		//COleDateTime dtScaleMin = pDayView->GetScaleMinTime();
		//COleDateTime dtScaleMax = pDayView->GetScaleMaxTime();
		//int n1 = dtScaleMin.GetHour() * 2 + (dtScaleMin.GetMinute() ? 1 : 0);
		//int n2 = dtScaleMax.GetHour() * 2 + (dtScaleMax.GetMinute() ? 1 : 0);
		//m_ctrlMinScaleTimeCb.SetCurSel(n1);
		//m_ctrlMaxScaleTimeCb.SetCurSel(n2);		
	}
	//===========================================================================

	m_ctrlMonth_ShowEndTime.SetCheck(pCalendar->MonthView_IsShowEndDate() ? 1 : 0);
	m_ctrlMonth_ShowTimeAsClocks.SetCheck(pCalendar->MonthView_IsShowTimeAsClocks() ? 1 : 0);
	m_ctrlMonth_CompressWeekendDays.SetCheck(pCalendar->MonthView_IsCompressWeekendDays() ? 1 : 0);

	//---------------------------------------------------------------------------
	CXTPCalendarMonthView* pMonthView = DYNAMIC_DOWNCAST(CXTPCalendarMonthView, pCalendar->GetActiveView());
	if (pMonthView) 
	{
		int nWCount = pMonthView->GetGrid()->GetWeeksCount();
        		
		for (i = 0; i < m_ctrlMonth_WeeksCount.GetCount(); i++) 
		{   		
			if ((int)m_ctrlMonth_WeeksCount.GetItemData(i) == nWCount) 
			{
				m_ctrlMonth_WeeksCount.SetCurSel(i);
				break;
			}
		}
	}

	//------------------------------------------------------------------------
	m_ctrlWeek_ShowTimeAsClock.SetCheck(pCalendar->WeekView_IsShowTimeAsClocks() ? 1 : 0);
	m_ctrlWeek_ShowEndTime.SetCheck(pCalendar->WeekView_IsShowEndDate() ? 1 : 0);

	m_ctrlCompactTimelineEvents.SetCheck(pCalendar->GetCalendarOptions()->bTimeLineCompact);
	//------------------------------------------------------------------------
	for (i = 0; i < m_ctrlTooltipMode.GetCount(); i++) 
	{
		if ((int)m_ctrlTooltipMode.GetItemData(i) == 
			pDemoView->m_wndCalendarEx.m_nToolTipMode) 
		{
			m_ctrlTooltipMode.SetCurSel(i);
			break;
		}
	}
	
	((CButton*) GetDlgItem(IDC_CHECK_SINGLE_CLICK))->SetCheck(GetCalendarCtrl()->m_bSwitchToDayViewIfPickedSingleDay);
}

void COptionsDialogBar::OnCbnSelchangeTooltipMode()
{
	CCalendarDemoView* pView = (CCalendarDemoView*)(((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveView());
	int nSel = m_ctrlTooltipMode.GetCurSel();
	if (nSel != CB_ERR && pView)
	{
		pView->SetCalendarToolTipMode((int)m_ctrlTooltipMode.GetItemData(nSel));
	}
}

HBRUSH COptionsDialogBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor == CTLCOLOR_LISTBOX || nCtlColor == CTLCOLOR_EDIT)
		return CDialogBar::OnCtlColor(pDC, pWnd, nCtlColor);

	COLORREF clr = XTPColorManager()->grcDockBar.clrDark;

	static CBrush brush;
	static COLORREF brushColor = 0;

	if (brush.GetSafeHandle() == 0 || brushColor != clr)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(clr);
		brushColor = clr;
	}

	pDC->SetBkColor(clr);
	return brush;
}
void COptionsDialogBar::OnShowTimeScaleMinutes()
{
	//IDC_CHECK_SHOW_TSMINUTES
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK_SHOW_TSMINUTES))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarOptions* pOptions = pCalendar->GetCalendarOptions();
		if (pOptions) 
		{
			pOptions->bDayView_TimeScaleShowMinutes = b;
			pOptions->OnOptionsChanged();
			pCalendar->RedrawControl();
		}
	}
}

void COptionsDialogBar::OnEcoMode()
{
}

void COptionsDialogBar::OnDayHeaderFormat()
{
	// IDC_CHECK9, IDC_EDIT2
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK9))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			CString s;
			GetDlgItem(IDC_EDIT2)->GetWindowText(s);
			if (b)
				pDayView->SetDayHeaderFormat(s);
			else
				pDayView->SetDayHeaderFormat(_T(""));
			pCalendar->RedrawControl();
		}
	}
}

void COptionsDialogBar::OnCustomTooltip()
{
	// IDC_CHECK6, IDC_EDIT1
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK6))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CString s;
		GetDlgItem(IDC_EDIT1)->GetWindowText(s);
		if (b)
			pCalendar->m_sCustomFormat4Tooltip = s;
		else
			pCalendar->m_sCustomFormat4Tooltip.Empty();
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnFullDateMode()
{
	// IDC_CHECK8
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK8))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->m_bFullDateMode = b;
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnMutliColumnMode()
{
	// IDC_CHECK4
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK4))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->m_bMultiColumnWeekMode = b;
		CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
		if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
		{
			CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
			pView->SetView(xtpCalendarWeekView);
		}
	}
}

void COptionsDialogBar::OnMonthViewDraftMode()
{
	// IDC_CHECK1
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK1))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarMonthView* pMonthView = DYNAMIC_DOWNCAST(CXTPCalendarMonthView, pCalendar->GetMonthView());
		if (pMonthView) 
			pMonthView->m_bDraftMode = b;
	}
}

void COptionsDialogBar::OnRTL()
{
	// IDC_CHECK5
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK5))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->SetLayoutRTL(b);
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnTooltilUnderMouse()
{
	// IDC_CHECK3
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK3))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->m_bTooltipUnderMouse = b;
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnDayHeaderPeriod()
{
	// IDC_RADIO2, IDC_RADIO3, IDC_RADIO4
	BOOL b = ((CButton*) GetDlgItem(IDC_RADIO2))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			if (b)
			{
				pDayView->m_nDayHeaderPeriod = 1;
				pCalendar->RedrawControl();
			}
		}
	}
}

void COptionsDialogBar::OnDayHeaderPeriod2()
{
	BOOL b = ((CButton*) GetDlgItem(IDC_RADIO3))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			if (b)
			{
				pDayView->m_nDayHeaderPeriod = 2;
				pCalendar->RedrawControl();
			}
		}
	}
}

void COptionsDialogBar::OnDayHeaderPeriod3()
{
	BOOL b = ((CButton*) GetDlgItem(IDC_RADIO4))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			if (b)
			{
				pDayView->m_nDayHeaderPeriod = 3;
				pCalendar->RedrawControl();
			}
		}
	}
}

void COptionsDialogBar::OnFullScalePrinting()
{
	// IDC_CHECK10
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK10))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		pView->m_bPrintFullScale = b;
		//pView->GetCalendarCaptionBarCtrl().EnableMulticolumns(b);
		//pView->GetCalendarCaptionBarCtrl().EnableTimeline(b);
	}
}

void COptionsDialogBar::OnReadOnlyMode()
{
	// IDC_CHECK11
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK11))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->m_bReadOnlyMode = b;
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnMultiColorSchedules()
{
	// IDC_CHECK12
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK12))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->m_bMultiColorScheduleMode = b;
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnPreventAutoAllDay()
{
	// IDC_CHECK13
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK13))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		pCalendar->m_bPreventAutoAllDayMode = b;
		pCalendar->RedrawControl();
	}
}

void COptionsDialogBar::OnDatePickerYearArrows()
{
	// IDC_CHECK14
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK14))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		((CMainFrame*) pView->GetParentFrame())->m_dlgDatePicker.m_wndDatePicker.m_bYearsTriangle = b;
		((CMainFrame*) pView->GetParentFrame())->m_dlgDatePicker.m_wndDatePicker.RedrawControl();
	}
}

void COptionsDialogBar::OnShowCaptionBar()
{
	// IDC_CHECK15
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK15))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		pView->ShowCaptionBar(!b);
	}
}

void COptionsDialogBar::OnHide4TimelineMode()
{
	// IDC_CHECK16
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK16))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
		pCalendar->m_bHideCaptionBar = b;
}

void COptionsDialogBar::OnOneLineLayout()
{
	// IDC_CHECK17
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK17))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		pView->GetCalendarCaptionBarCtrl().UseOneLine(b);
	}
}

void COptionsDialogBar::OnHideMonthView()
{
	// IDC_CHECK18
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK18))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		if (b)
		{
			pView->GetCalendarCaptionBarCtrl().SetButtonText(2, _T(""));
			pView->ShowCaptionBar(!b);
			pView->ShowCaptionBar(b);
		}
	}
}

void COptionsDialogBar::OnShowMonthViewButton()
{
	// IDC_CHECK19
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK19))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		if (b)
		{
			pView->GetCalendarCaptionBarCtrl().SetButtonText(2, _T("MV"));
			pView->ShowCaptionBar(!b);
			pView->ShowCaptionBar(b);
		}
	}
}

void COptionsDialogBar::OnHideTimelieButton()
{
	// IDC_CHECK20
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK20))->GetCheck();
	CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveFrame()->GetActiveView();
	if (pActiveView->IsKindOf(RUNTIME_CLASS(CCalendarDemoView)))
	{
		CCalendarDemoView* pView = (CCalendarDemoView*) pActiveView;
		if (b)
		{
			pView->GetCalendarCaptionBarCtrl().EnableTimeline(!b);
			pView->ShowCaptionBar(!b);
			pView->ShowCaptionBar(b);
		}
	}
}

void COptionsDialogBar::OnDayViewPrintFull()
{
	BOOL b = ((CButton*) GetDlgItem(IDC_RADIO5))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			if (b)
			{
				pDayView->m_bDraftMode = FALSE;
				pDayView->m_bPrintRepeatHeaderFooterMode = TRUE;
			}
		}
	}
}

void COptionsDialogBar::OnDayViewPrintSave()
{
	BOOL b = ((CButton*) GetDlgItem(IDC_RADIO6))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			if (b)
			{
				pDayView->m_bDraftMode = FALSE;
				pDayView->m_bPrintRepeatHeaderFooterMode = FALSE;
			}
		}
	}
}

void COptionsDialogBar::OnDayViewPrintDraft()
{
	BOOL b = ((CButton*) GetDlgItem(IDC_RADIO7))->GetCheck();
	CXTPCalendarControl* pCalendar = GetCalendarCtrl();
	if (pCalendar)
	{
		CXTPCalendarDayView* pDayView = DYNAMIC_DOWNCAST(CXTPCalendarDayView, pCalendar->GetDayView());
		if (pDayView) 
		{
			if (b)
				pDayView->m_bDraftMode = TRUE;
		}
	}
}

void COptionsDialogBar::OnDatePickerSingleClick()
{
	BOOL b = ((CButton*) GetDlgItem(IDC_CHECK_SINGLE_CLICK))->GetCheck() > 0;
	GetCalendarCtrl()->m_bSwitchToDayViewIfPickedSingleDay = b;
}
