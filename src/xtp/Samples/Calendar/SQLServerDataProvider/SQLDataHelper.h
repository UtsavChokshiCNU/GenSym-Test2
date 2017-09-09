// SQLDataHelper.h: interface for the CSQLDataHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLDATAHELPER_H__39DD3C0B_9D19_4855_8ABF_20A10C8D53DC__INCLUDED_)
#define AFX_SQLDATAHELPER_H__39DD3C0B_9D19_4855_8ABF_20A10C8D53DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSQLDataHelper  
{
public:
	CSQLDataHelper(CXTPCalendarData* pDataProvider, XTPADODB::_Connection* pDBconn);
	virtual ~CSQLDataHelper();

	static CString MakeRetrieveDayEventsSQL(COleDateTime dtDay);
	static CString MakeGetUpcomingEventsSQL(COleDateTime dtFrom, int nPeriodMinutes, BOOL bOptimized = TRUE);

	CXTPCalendarEventsPtr CreateEventsFromData(XTPADODB::_Recordset* pRSevents, BOOL bCloseRS);
	CXTPCalendarEventPtr CreateEventFromData(XTPADODB::_Recordset* pRSevent, BOOL bCloseRS);

	CXTPCalendarRecurrencePatternPtr CreatePatternFromData(XTPADODB::_Recordset* pRS);

	void PutEventToData(CXTPCalendarEvent* pEvent, XTPADODB::_Recordset* pRS);
	void PutPatternToData(CXTPCalendarRecurrencePattern* pPattern, XTPADODB::_Recordset* pRS);

protected:
	CXTPCalendarEventPtr _CreateEventFromData(XTPADODB::_Recordset* pRSevents, BOOL bException);
	void ReadRPatternExceptions(CXTPCalendarRecurrencePattern* pPattern);
private:
	CXTPCalendarData* m_pDataProvider;
	XTPADODB::_ConnectionPtr m_ptrDBconn;

};

#endif // !defined(AFX_SQLDATAHELPER_H__39DD3C0B_9D19_4855_8ABF_20A10C8D53DC__INCLUDED_)
