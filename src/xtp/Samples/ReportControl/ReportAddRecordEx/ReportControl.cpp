// ReportControl.cpp: implementation of the CReportControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MessageRecord.h"
#include "ReportControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportControl::CReportControl()
{
	m_pFocusedRecord = NULL;
	m_pTopRow = NULL;
}

CReportControl::~CReportControl()
{
	if(m_pFocusedRecord)
		m_pFocusedRecord = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CReportControl, CXTPReportControl)
	//{{AFX_MSG_MAP(CReportControl)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADD_RECORD_EX, OnAddRecordEx)
END_MESSAGE_MAP()


LRESULT CReportControl::OnAddRecordEx(WPARAM wParam, LPARAM /*lParam*/)
{
	CXTPReportRecord* pRecord = (CXTPReportRecord*)wParam;
	if(!pRecord)
		return -1;

	// save top row
	if(GetRows())
		m_pTopRow = GetRows()->GetAt(GetTopRowIndex());

	// add record
	AddRecordEx(pRecord);

	// restore top row
	if(m_pTopRow)
		SetTopRow(m_pTopRow->GetIndex());
	
	RedrawControl();

	return 0;
}

void CReportControl::DeleteSelectedRows()
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
			RemoveRecordEx(pRecord);
		if(nRow >= pSelectedRows->GetCount())
			nRow = pSelectedRows->GetCount() - 1;
	}
	SetFocusedRow(pFocusedRow ? pFocusedRow : GetFocusedRow());
}

void CReportControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
		case VK_DELETE :
			DeleteSelectedRows();
			break;
		case VK_RETURN :
			CXTPReportRow* pFocusedRow = GetFocusedRow();
			if(pFocusedRow && pFocusedRow->GetType() == xtpRowTypeHeader && m_pFocusedRecord)
			{
				*(CMessageRecord*)m_pFocusedRecord = *(CMessageRecord*)pFocusedRow->GetRecord();

				UpdateRecord(m_pFocusedRecord, FALSE);

			}
			break;
	}

	CXTPReportControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CReportControl::OnFocusChanging(CXTPReportRow* pNewRow, CXTPReportColumn* pNewCol)
{
	CXTPReportControl::OnFocusChanging(pNewRow, pNewCol);

	// apply changes
	CXTPReportRow* pFocusedRow = GetFocusedRow();
	if(pFocusedRow && pFocusedRow->GetType() == xtpRowTypeHeader && 
		pNewRow && pNewRow != GetFocusedRow() && m_pFocusedRecord && pNewRow->GetType() != xtpRowTypeHeader)
	{
		*(CMessageRecord*)m_pFocusedRecord = *(CMessageRecord*)pFocusedRow->GetRecord();

		UpdateRecord(m_pFocusedRecord, FALSE);

	}
	// set new header row
	if(!pNewRow || pNewRow == GetFocusedRow() || pNewRow->GetType() == xtpRowTypeHeader)
		return TRUE;
	if(m_pFocusedRecord)
		m_pFocusedRecord = NULL;
	if(!pNewRow->GetRecord())
	{
		GetHeaderRecords()->RemoveAll();
		GetHeaderRecords()->Add(new CMessageRecord());
		PopulateHeaderRows();
		return TRUE;
	}
	m_pFocusedRecord = pNewRow->GetRecord();
	GetHeaderRecords()->RemoveAll();
	GetHeaderRecords()->Add(new CMessageRecord((CMessageRecord*)m_pFocusedRecord));
	PopulateHeaderRows();

	return TRUE;
}
