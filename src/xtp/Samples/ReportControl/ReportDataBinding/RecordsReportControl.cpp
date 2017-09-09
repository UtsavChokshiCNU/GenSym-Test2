// RecordsReportControl.cpp: implementation of the CRecordsReportControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordsReportControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecordsReportControl::CRecordsReportControl()
{
	m_pFocusedRecord = NULL;
	m_pTopRow = NULL;
}

CRecordsReportControl::~CRecordsReportControl()
{
	if(m_pFocusedRecord)
		m_pFocusedRecord = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRecordsReportControl, CXTPReportControl)
	//{{AFX_MSG_MAP(CRecordsReportControl)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CRecordsReportControl::AddNewRecord()
{
/*	CXTPReportRecord* pRecordSrc = GetRecords()->GetAt(0);
	CXTPReportRecord* pRecord = new CXTPReportRecord;
	if(!pRecord)
		break;
	for(int i = 0; i < 4; i++)
	{
		VARIANT vtValue = ((CXTPReportRecordItemVariant*)pRecordSrc->GetItem(i))->GetValue();
		if(vtValue.vt == VT_BSTR)
		{
			CString strValue = vtValue.bstrVal;
			strValue += _T("_New");
			COleVariant vtBstrValue(strValue);
			vtValue = vtBstrValue;
		}
		if(vtValue.vt & VT_ARRAY)
			vtValue.vt = VT_EMPTY;
		CXTPReportRecordItemVariant* pItem = new CXTPReportRecordItemVariant(vtValue);
		pRecord->AddItem(pItem);
	}
	GetDataManager()->AddRecord(pRecord, TRUE);*/
	CXTPReportRecord* pRecord = NULL;
	if(FAILED(GetDataManager()->CreateEmptyRecord(&pRecord)) || !pRecord)
		return;
	int i;
	for(i = 0; i < pRecord->GetItemCount(); i++)
	{
		VARIANT vtValue = ((CXTPReportRecordItemVariant*)pRecord->GetItem(i))->GetValue();
		if(vtValue.vt == VT_BSTR)
		{
			CString strValue = _T("New Record");
			COleVariant vtBstrValue(strValue);
			((CXTPReportRecordItemVariant*)pRecord->GetItem(i))->SetValue(vtBstrValue);
		}
	}
	if(!GetDataManager()->AddRecord(pRecord, TRUE))
		pRecord->InternalRelease();
}

void CRecordsReportControl::DeleteSelectedRows()
{
	CXTPReportSelectedRows* pSelectedRows = GetSelectedRows();
	if(!pSelectedRows)
		return;
	int nRow = pSelectedRows->GetCount() - 1;
	if(nRow < 0)
		return;
	CWaitCursor wc;
	CXTPReportRow* pFocusedRow = pSelectedRows->GetAt(pSelectedRows->GetCount() - 1);
	pFocusedRow = GetRows()->GetAt(pFocusedRow->GetIndex() + 1);
	while(nRow >= 0)
	{
		CXTPReportRecord* pRecord = pSelectedRows->GetAt(nRow--)->GetRecord();
		if(pRecord)
			GetDataManager()->DeleteRecord(pRecord);
		if(nRow >= pSelectedRows->GetCount())
			nRow = pSelectedRows->GetCount() - 1;
	}
	SetFocusedRow(pFocusedRow ? pFocusedRow : GetFocusedRow());
}

void CRecordsReportControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
		case VK_DELETE :
			DeleteSelectedRows();
			break;
		case VK_INSERT :
		{
			AddNewRecord();
			break;
		}
		case VK_RETURN :
			CXTPReportRow* pFocusedRow = GetFocusedRow();
			if(pFocusedRow && pFocusedRow->GetType() == xtpRowTypeHeader)
			{
				CXTPReportRecord* pRecord = pFocusedRow->GetRecord();
				if(!pRecord)
					break;
				pRecord->InternalAddRef();
				HRESULT hr;
				if(FAILED(hr = GetDataManager()->AddRecord(pRecord, TRUE)))
				{
					pRecord->InternalRelease();
					break;
				}
				pRecord = NULL;
				if(FAILED(hr = GetDataManager()->CreateEmptyRecord(&pRecord)) || pRecord == NULL)
					break;
				GetHeaderRecords()->RemoveAll();
				GetHeaderRecords()->Add(pRecord);
				PopulateHeaderRows();
			}
			break;
	}

	CXTPReportControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CRecordsReportControl::OnFocusChanging(CXTPReportRow* pNewRow, CXTPReportColumn* pNewCol)
{
	CXTPReportControl::OnFocusChanging(pNewRow, pNewCol);

	// add new record
	CXTPReportRow* pFocusedRow = GetFocusedRow();
	if(pFocusedRow && pFocusedRow->GetType() == xtpRowTypeHeader && pNewRow && pNewRow != pFocusedRow && pNewRow->GetType() != xtpRowTypeHeader)
	{
		CXTPReportRecord* pRecord = pFocusedRow->GetRecord();
		if(!pRecord)
			return TRUE;
		pRecord->InternalAddRef();
		HRESULT hr;
		if(FAILED(hr = GetDataManager()->AddRecord(pRecord, TRUE)))
		{
			pRecord->InternalRelease();
			return TRUE;
		}
		pRecord = NULL;
		if(FAILED(hr = GetDataManager()->CreateEmptyRecord(&pRecord)) || pRecord == NULL)
			return TRUE;
		GetHeaderRecords()->RemoveAll();
		GetHeaderRecords()->Add(pRecord);
		PopulateHeaderRows();
	}

	return TRUE;
}
