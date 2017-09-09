// OptionsDialogBar.h : header file
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

#if !defined(AFX_OPTIONSDIALOGBAR_H__FD6A82C4_7E32_441A_BF20_888CC7F17443__INCLUDED_)
#define AFX_OPTIONSDIALOGBAR_H__FD6A82C4_7E32_441A_BF20_888CC7F17443__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CXTPCalendarControl;

/////////////////////////////////////////////////////////////////////////////
// COptionsDialogBar dialog

class COptionsDialogBar : public CDialogBar
{
// Construction
public:
	COptionsDialogBar(CWnd* pParent = NULL);   // standard constructor
	~COptionsDialogBar();

// Dialog Data
	//{{AFX_DATA(COptionsDialogBar)
	enum { IDD = IDD_CALENDAR_DEMO_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	void OnViewChanged(XTPCalendarViewType viewType);
	
	void Init();
	void Close();

	CButton m_ctrlWorkWeekDays[7];

	CComboBox m_ctrlFirstDayOfWeekCb;
	CComboBox m_ctrlStartTimeCb;
	CComboBox m_ctrlEndTimeCb;
	CComboBox m_ctrlMinScaleTimeCb;
	CComboBox m_ctrlMaxScaleTimeCb;
    
	CComboBox m_ctrlSelchangeTimeScaleCb;

	CComboBox m_ctrlTooltipMode;

	CButton m_ctrlMonth_ShowEndTime;
	CButton m_ctrlMonth_ShowTimeAsClocks;
	CButton m_ctrlMonth_CompressWeekendDays;
	CComboBox m_ctrlMonth_WeeksCount;
		
	CButton m_ctrlWeek_ShowTimeAsClock;
	CButton m_ctrlWeek_ShowEndTime;
	CButton m_ctrlCompactTimelineEvents;

	CUIntArray m_arOptCtrlIDsAll;
	CUIntArray m_arOptCtrlIDsCommon;
	CUIntArray m_arOptCtrlIDsDayView;
	CUIntArray m_arOptCtrlIDsWeekView;
	CUIntArray m_arOptCtrlIDsMonthView;
	CUIntArray m_arOptCtrlIDsTimelineView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialogBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialogBar)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
//public:
	afx_msg void OnInitDialog();
	afx_msg void OnBnClickedMonthCompressWeekendDays();
	afx_msg void OnBnClickedMonthShowEndTime();
	afx_msg void OnBnClickedMonthSchowTimeAsClock();
	afx_msg void OnBnClickedTimelineCompact();
	afx_msg void OnCbnSelchangeFirstDayOfWeekCb();
	afx_msg void OnCbnSelchangeMonthWeeksCount();
	afx_msg void OnCbnSelchangeTimeScale();
	afx_msg void OnBnClickedWeekSchowTimeAsClock();
	afx_msg void OnBnClickedWeekShowEndTime();
	afx_msg void OnBnClickedTimeZoneBtn();
	afx_msg void OnBnClickedScrollDayPrev();
	afx_msg void OnBnClickedIdcScrollDayNext();
	afx_msg void OnCbnSelchangeStartTimeCb();
	afx_msg void OnCbnSelchangeEndTimeCb();
	afx_msg void OnCbnSelchangeMinMaxScaleTimeCb();
	
	afx_msg void OnBnClickedWorkWeekDay();
	
	afx_msg void OnBnClickedHideOptionsPane();

	afx_msg void OnCbnSelchangeTooltipMode();

	CXTPCalendarControl* GetCalendarCtrl();
    
	void UpdateControlsState();

	DECLARE_MESSAGE_MAP()

	DECLARE_XTP_SINK(COptionsDialogBar, m_Sink);
	void OnCalendarEvent_TimeScaleWasChanged(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam);
	void OnCalendarEvent_ViewWasChanged(XTP_NOTIFY_CODE Event, WPARAM wParam, LPARAM lParam);
public:
	void PopulateWorkDays();
	afx_msg void OnShowTimeScaleMinutes();
	afx_msg void OnEcoMode();
	afx_msg void OnDayHeaderFormat();
	afx_msg void OnCustomTooltip();
	afx_msg void OnFullDateMode();
	afx_msg void OnMutliColumnMode();
	afx_msg void OnMonthViewDraftMode();
	afx_msg void OnRTL();
	afx_msg void OnTooltilUnderMouse();
	afx_msg void OnDayHeaderPeriod();
	afx_msg void OnDayHeaderPeriod2();
	afx_msg void OnDayHeaderPeriod3();
	afx_msg void OnFullScalePrinting();
	afx_msg void OnReadOnlyMode();
	afx_msg void OnMultiColorSchedules();
	afx_msg void OnPreventAutoAllDay();
	afx_msg void OnDatePickerYearArrows();
	afx_msg void OnShowCaptionBar();
	afx_msg void OnHide4TimelineMode();
	afx_msg void OnOneLineLayout();
	afx_msg void OnHideMonthView();
	afx_msg void OnShowMonthViewButton();
	afx_msg void OnHideTimelieButton();
	afx_msg void OnDayViewPrintFull();
	afx_msg void OnDayViewPrintSave();
	afx_msg void OnDayViewPrintDraft();
	afx_msg void OnDatePickerSingleClick();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOGBAR_H__FD6A82C4_7E32_441A_BF20_888CC7F17443__INCLUDED_)
