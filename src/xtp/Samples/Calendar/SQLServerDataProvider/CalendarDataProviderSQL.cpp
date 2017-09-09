// CalendarDataProviderSQL.cpp: implementation of the CCalendarDataProviderSQL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SQLServerDataProvider.h"
#include "CalendarDataProviderSQL.h"
#include "SQLDataHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
extern void TRACE_ComError(_com_error &e);
extern void TRACE_ProviderError(XTPADODB::_Connection* pConnDB);

#define DBGDATA_ASSERT ASSERT
#ifndef DBGDATA_ASSERT
	#define DBGDATA_ASSERT
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalendarDataProviderSQL::CCalendarDataProviderSQL()
{

}

CCalendarDataProviderSQL::~CCalendarDataProviderSQL()
{

}

BOOL CCalendarDataProviderSQL::Open()
{
	if (GetConnectionString().IsEmpty())
		return FALSE;

	if (IsOpen())
	{
		TRACE(_T("Provider is alredy opened. CCalendarDataProviderSQL::Open(ConnectionString='%s') \n"), (LPCTSTR)GetConnectionString());
		return TRUE;
	}

	try
	{
		HRESULT hr = m_ptrDBconn.CreateInstance(__uuidof(XTPADODB::Connection));
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || m_ptrDBconn == NULL)
		{
			TRACE(_T("ERROR: Cannot create XTPADODB::Connection. (HRESULT = %08lx) \n"), hr);
			return FALSE;
		}
	
		hr = m_ptrDBconn->Open(_bstr_t(GetConnectionString()), _T(""), _T(""), XTPADODB::adOptionUnspecified);
		ASSERT(SUCCEEDED(hr));

		if (FAILED(hr))
		{
			TRACE(_T("ERROR: Cannot open DB Connection. (HRESULT = %08lx, ConnectionString='%s') \n"), hr, (LPCTSTR)m_strConnectionString);
			return FALSE;
		}

		CXTPCalendarData::Open();
		
		return IsOpen();
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	TRACE(_T("ERROR: Exeption in CXTPCalendarDatabaseDataProvider::Open(ConnectionString='%s') \n"), (LPCTSTR)m_strConnectionString);

	return FALSE;

}

void CCalendarDataProviderSQL::Close()
{
	if (IsOpen())
	{
		try
		{
			if (m_ptrDBconn != NULL)
				m_ptrDBconn->Close();
		}
		catch (_com_error &e)
		{
			TRACE_ProviderError(m_ptrDBconn);
			TRACE_ComError(e);
		}
		catch (...)
		{}

		CXTPCalendarData::Close();
	}	
}

CXTPCalendarEventsPtr CCalendarDataProviderSQL::DoRetrieveDayEvents(COleDateTime dtDay)
{
	if (!IsOpen() || m_ptrDBconn == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);

	_bstr_t bstrSQL = CSQLDataHelper::MakeRetrieveDayEventsSQL(dtDay);

	try
	{
		XTPADODB::_RecordsetPtr ptrRSevents = m_ptrDBconn->Execute(bstrSQL, NULL, XTPADODB::adOptionUnspecified);
		DBGDATA_ASSERT(ptrRSevents != NULL);
		
		if (ptrRSevents == NULL) 
			return new CXTPCalendarEvents();


		CXTPCalendarEventsPtr ptrEvents = _SQLDataHelper.CreateEventsFromData(ptrRSevents, TRUE);
		ASSERT(ptrRSevents->GetState() == XTPADODB::adStateClosed);

		if (!ptrEvents) 
			ptrEvents = new CXTPCalendarEvents();

		return ptrEvents;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoRetrieveDayEvents(Date= %s) \n"), (LPCTSTR)dtDay.Format());

	return NULL;
}

CXTPCalendarEventPtr CCalendarDataProviderSQL::DoRead_Event(DWORD dwEventID)
{
	if (!IsOpen() || m_ptrDBconn == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
		
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM CalendarEvents WHERE EventID = %d"), dwEventID);
	
	try
	{
		XTPADODB::_RecordsetPtr ptrRSevent = m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adOptionUnspecified);
		DBGDATA_ASSERT(ptrRSevent != NULL);
		
		if (ptrRSevent == NULL) 
			return NULL;


		CXTPCalendarEventPtr ptrEvent = _SQLDataHelper.CreateEventFromData(ptrRSevent, TRUE);
		ASSERT(ptrRSevent->GetState() == XTPADODB::adStateClosed);

		return ptrEvent;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoRead_Event(ID= %d) \n"), dwEventID);

	return NULL;
}

BOOL CCalendarDataProviderSQL::DoCreate_Event(CXTPCalendarEvent* pEvent, DWORD& rdwNewEventID)
{
	if (!IsOpen() || m_ptrDBconn == NULL || !pEvent)
	{
		return FALSE;
	}
	
	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
	_bstr_t bstrSQL = _T("SELECT * FROM CalendarEvents WHERE EventID = 0");

	try
	{	
		XTPADODB::_RecordsetPtr ptrRSevent;
		HRESULT hr = ptrRSevent.CreateInstance(__uuidof(XTPADODB::Recordset));
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || ptrRSevent == NULL)
		{
			TRACE(_T("ERROR: Cannot create XTPADODB::Recordset. (HRESULT = %08lx) \n"), hr);
			return FALSE;
		}

		_variant_t vtConnDisp((IDispatch*)m_ptrDBconn.GetInterfacePtr());
		ptrRSevent->Open(bstrSQL, vtConnDisp, XTPADODB::adOpenStatic, XTPADODB::adLockOptimistic, XTPADODB::adOpenRecordUnspecified);
		        
		m_ptrDBconn->BeginTrans();
		//'-----------------------------------------------------
		ASSERT(ptrRSevent->bEOF && ptrRSevent->bBOF);
    
		ptrRSevent->AddNew();
        
		_SQLDataHelper.PutEventToData(pEvent, ptrRSevent);

		ptrRSevent->Update();
    
		//'--------------------------------------------    
		ptrRSevent->Close();
    
		m_ptrDBconn->CommitTrans();
    
		//'-- update Auto field EventID	
		bstrSQL = _T("SELECT MAX(EventID) AS NewEventID FROM CalendarEvents");
		XTPADODB::_RecordsetPtr ptrRSnewID = m_ptrDBconn->Execute(bstrSQL, NULL, XTPADODB::adOptionUnspecified);
		ASSERT(ptrRSnewID != NULL);
		
		if (ptrRSnewID != NULL) 
		{
			ASSERT(!ptrRSnewID->bEOF);
			if (!ptrRSnewID->bEOF)
			{
				rdwNewEventID = (DWORD)(long)ptrRSnewID->Fields->GetItem(_T("NewEventID"))->Value;
			}
			ptrRSnewID->Close();
		}
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoCreate_Event() \n"));

	return FALSE;
}

BOOL CCalendarDataProviderSQL::DoUpdate_Event (CXTPCalendarEvent* pEvent)
{
	ASSERT(pEvent);
	if (!IsOpen() || m_ptrDBconn == NULL || !pEvent)
	{
		return FALSE;
	}
	
	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM CalendarEvents WHERE EventID = %d"), pEvent->GetEventID());

	try
	{	
		XTPADODB::_RecordsetPtr ptrRSevent;
		HRESULT hr = ptrRSevent.CreateInstance(__uuidof(XTPADODB::Recordset));
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || ptrRSevent == NULL)
		{
			TRACE(_T("ERROR: Cannot create XTPADODB::Recordset. (HRESULT = %08lx) \n"), hr);
			return FALSE;
		}

		_variant_t vtConnDisp((IDispatch*)m_ptrDBconn.GetInterfacePtr());
		ptrRSevent->Open(_bstr_t(strSQL), vtConnDisp, XTPADODB::adOpenStatic, XTPADODB::adLockOptimistic, XTPADODB::adOpenRecordUnspecified);
		       
		m_ptrDBconn->BeginTrans();
		//'-----------------------------------------------------
		ASSERT(!ptrRSevent->bEOF && !ptrRSevent->bBOF);
    
		_SQLDataHelper.PutEventToData(pEvent, ptrRSevent);

		ptrRSevent->Update();
    
		//'--------------------------------------------    
		ptrRSevent->Close();
    
		m_ptrDBconn->CommitTrans();
    
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoUpdate_Event() \n"));

	return FALSE;
}

BOOL CCalendarDataProviderSQL::DoDelete_Event (CXTPCalendarEvent* pEvent)
{
	ASSERT(pEvent);
	if (!IsOpen() || m_ptrDBconn == NULL || !pEvent)
	{
		return FALSE;
	}
		
	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
		
	CString strSQL;
	strSQL.Format(_T("DELETE FROM CalendarEvents WHERE EventID = %d"), pEvent->GetEventID());
	
	try
	{
		m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adExecuteNoRecords);		
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoDelete_Event() \n"));

	return FALSE;	
}


CXTPCalendarRecurrencePatternPtr CCalendarDataProviderSQL::DoRead_RPattern(DWORD dwPatternID)
{		
	if (!IsOpen() || m_ptrDBconn == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
		
	CString strSQL;
	strSQL.Format(_T("SELECT * FROM CalendarRecurrencePatterns WHERE RecurrencePatternID = %d"), dwPatternID);
	
	try
	{
		XTPADODB::_RecordsetPtr ptrRS = m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adOptionUnspecified);
		DBGDATA_ASSERT(ptrRS != NULL);
		
		if (ptrRS == NULL) 
			return NULL;


		CXTPCalendarRecurrencePatternPtr ptrPattern = _SQLDataHelper.CreatePatternFromData(ptrRS);
		ASSERT(ptrRS->GetState() == XTPADODB::adStateClosed);

		return ptrPattern;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoRead_RPattern(ID= %d) \n"), dwPatternID);

	return NULL;	
}


BOOL CCalendarDataProviderSQL::DoCreate_RPattern(CXTPCalendarRecurrencePattern* pPattern, DWORD& rdwNewPatternID)
{
	if (!IsOpen() || m_ptrDBconn == NULL || !pPattern)
	{
		return FALSE;
	}
	
	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
	_bstr_t bstrSQL = _T("SELECT * FROM CalendarRecurrencePatterns WHERE RecurrencePatternID = 0");

	try
	{	
		XTPADODB::_RecordsetPtr ptrRS;
		HRESULT hr = ptrRS.CreateInstance(__uuidof(XTPADODB::Recordset));
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || ptrRS == NULL)
		{
			TRACE(_T("ERROR: Cannot create XTPADODB::Recordset. (HRESULT = %08lx) \n"), hr);
			return FALSE;
		}

		_variant_t vtConnDisp((IDispatch*)m_ptrDBconn.GetInterfacePtr());
		ptrRS->Open(bstrSQL, vtConnDisp, XTPADODB::adOpenStatic, XTPADODB::adLockOptimistic, XTPADODB::adOpenRecordUnspecified);
		        
		m_ptrDBconn->BeginTrans();
		//'-----------------------------------------------------
		ASSERT(ptrRS->bEOF && ptrRS->bBOF);
    
		ptrRS->AddNew();
        
		_SQLDataHelper.PutPatternToData(pPattern, ptrRS);

		ptrRS->Update();
    
		//'--------------------------------------------    
		ptrRS->Close();
    
		m_ptrDBconn->CommitTrans();
    
		//'-- update Auto field EventID	
		bstrSQL = _T("SELECT MAX(RecurrencePatternID) AS NewID FROM CalendarRecurrencePatterns");
		XTPADODB::_RecordsetPtr ptrRSnewID = m_ptrDBconn->Execute(bstrSQL, NULL, XTPADODB::adOptionUnspecified);
		ASSERT(ptrRSnewID != NULL);
		
		if (ptrRSnewID != NULL) 
		{
			ASSERT(!ptrRSnewID->bEOF);
			if (!ptrRSnewID->bEOF)
			{
				rdwNewPatternID = (DWORD)(long)ptrRSnewID->Fields->GetItem(_T("NewID"))->Value;
			}
			ptrRSnewID->Close();
		}
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoCreate_Event() \n"));

	return FALSE;
}


BOOL CCalendarDataProviderSQL::DoUpdate_RPattern(CXTPCalendarRecurrencePattern* pPattern)
{
	if (!IsOpen() || m_ptrDBconn == NULL || !pPattern)
	{
		return FALSE;
	}
	
	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);

	CString strSQL;
	strSQL.Format(_T("SELECT * FROM CalendarRecurrencePatterns WHERE RecurrencePatternID = %d"), pPattern->GetPatternID());

	try
	{	
		XTPADODB::_RecordsetPtr ptrRS;
		HRESULT hr = ptrRS.CreateInstance(__uuidof(XTPADODB::Recordset));
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr) || ptrRS == NULL)
		{
			TRACE(_T("ERROR: Cannot create XTPADODB::Recordset. (HRESULT = %08lx) \n"), hr);
			return FALSE;
		}

		_variant_t vtConnDisp((IDispatch*)m_ptrDBconn.GetInterfacePtr());
		ptrRS->Open(_bstr_t(strSQL), vtConnDisp, XTPADODB::adOpenStatic, XTPADODB::adLockOptimistic, XTPADODB::adOpenRecordUnspecified);
		        
		m_ptrDBconn->BeginTrans();
		//'-----------------------------------------------------
		ASSERT(!ptrRS->bEOF && !ptrRS->bBOF);
    			        
		_SQLDataHelper.PutPatternToData(pPattern, ptrRS);

		ptrRS->Update();
    
		//'--------------------------------------------    
		ptrRS->Close();
    
		m_ptrDBconn->CommitTrans();
    
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoUpdate_RPattern() \n"));

	return FALSE;
}


BOOL CCalendarDataProviderSQL::DoDelete_RPattern(CXTPCalendarRecurrencePattern* pPattern)
{
	ASSERT(pPattern);
	if (!IsOpen() || m_ptrDBconn == NULL || !pPattern)
	{
		return FALSE;
	}
		
	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);
		
	CString strSQL;
	strSQL.Format(_T("DELETE FROM CalendarRecurrencePatterns WHERE RecurrencePatternID = %d"), pPattern->GetPatternID());
	
	try
	{
		m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adExecuteNoRecords);		
		return TRUE;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoDelete_RPattern() \n"));

	return NULL;
}

CXTPCalendarEventsPtr CCalendarDataProviderSQL::DoGetAllEvents_raw()
{
		if (!IsOpen() || m_ptrDBconn == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);

	CString strSQL;
	strSQL.Format(_T("SELECT * FROM CalendarEvents WHERE RecurrenceState = %d OR RecurrenceState = %d"),
				  xtpCalendarRecurrenceNotRecurring, xtpCalendarRecurrenceMaster);
	try
	{
		XTPADODB::_RecordsetPtr ptrRSevents = m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adOptionUnspecified);
		DBGDATA_ASSERT(ptrRSevents != NULL);
		
		if (ptrRSevents == NULL) 
			return new CXTPCalendarEvents();


		CXTPCalendarEventsPtr ptrEvents = _SQLDataHelper.CreateEventsFromData(ptrRSevents, TRUE);
		ASSERT(ptrRSevents->GetState() == XTPADODB::adStateClosed);

		if (!ptrEvents) 
			ptrEvents = new CXTPCalendarEvents();

		return ptrEvents;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoGetAllEvents_raw() \n"));

	return NULL;

}

CXTPCalendarEventsPtr CCalendarDataProviderSQL::DoGetUpcomingEvents(COleDateTime dtFrom, COleDateTimeSpan spPeriod)
{	
	// The following code is also allowed: 
	//	return DoGetAllEvents_raw();	
	// 
	// Of cause it is not optimal, but if you like it ....
	// or just for some testing purposes it will work fine. 
	// (of cause DoGetAllEvents_raw must be implemented)
	
	if (!IsOpen() || m_ptrDBconn == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	CSQLDataHelper _SQLDataHelper(this, m_ptrDBconn);

	BOOL bOptimized = TRUE;
	CString strSQL = CSQLDataHelper::MakeGetUpcomingEventsSQL(dtFrom, (int)spPeriod.GetTotalMinutes(), bOptimized);

	//TRACE(_T("\n%s"), strSQL.Left(500));
	//TRACE(_T("%s\n"), strSQL.Mid(500));

	try
	{
		XTPADODB::_RecordsetPtr ptrRSevents = m_ptrDBconn->Execute(_bstr_t(strSQL), NULL, XTPADODB::adOptionUnspecified);
		DBGDATA_ASSERT(ptrRSevents != NULL);
		
		if (ptrRSevents == NULL) 
			return new CXTPCalendarEvents();


		CXTPCalendarEventsPtr ptrEvents = _SQLDataHelper.CreateEventsFromData(ptrRSevents, TRUE);
		ASSERT(ptrRSevents->GetState() == XTPADODB::adStateClosed);

		if (!ptrEvents) 
			ptrEvents = new CXTPCalendarEvents();

		return ptrEvents;
	}
	catch (_com_error &e)
	{
		TRACE_ProviderError(m_ptrDBconn);
		TRACE_ComError(e);
	}
	catch (...)
	{}
	
	TRACE(_T("ERROR: Exeption in CCalendarDataProviderSQL::DoGetUpcomingEvents() \n"));

	return NULL;
}
  
void CCalendarDataProviderSQL::DoRemoveAllEvents()
{
	// its easy to implement.
	// See DoDelete_Event and DoDelete_RPattern
}
