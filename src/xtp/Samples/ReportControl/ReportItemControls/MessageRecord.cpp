// MessageRecord.cpp: implementation of the CMessageRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportItemControls.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// CMessageRecord class

IMPLEMENT_SERIAL(CMessageRecord, CXTPReportRecord, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageRecord::CMessageRecord()
{
	CreateItems();
}

CMessageRecord::CMessageRecord(CString strItem1, CString strItem2, CString strItem3)
{
	AddItem(new CXTPReportRecordItemText(strItem1));
	AddItem(new CXTPReportRecordItemText(strItem2));
	AddItem(new CXTPReportRecordItemText(strItem3));
}

CMessageRecord::CMessageRecord(CMessageRecord* pRecord)
{
	for(int i = 0; i < 3; i++)
	{
		AddItem(new CXTPReportRecordItemText(((CXTPReportRecordItemText*)pRecord->GetItem(i))->GetValue()));
	}
}

CMessageRecord& CMessageRecord::operator= (const CMessageRecord& x)
{
	for(int i = 0; i < GetItemCount(); i++)
	{
		((CXTPReportRecordItemText*)GetItem(i))->SetValue(((CXTPReportRecordItemText*)x.GetItem(i))->GetValue());
	}

	return *this;
}

void CMessageRecord::CreateItems()
{
	// Initialize record items with empty values
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
}

CMessageRecord::~CMessageRecord()
{
}

void CMessageRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPReportRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}
