// DBVListSet.cpp : implementation of the CDBVListSet class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "VirtualList.h"
#include "DBVListSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBVListSet implementation

IMPLEMENT_DYNAMIC(CDBVListSet, CRecordset)

CDBVListSet::CDBVListSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDBVListSet)
	m_Email = _T("");
	m_Name = _T("");
	m_Phone = _T("");
	m_Location = _T("");
	m_Title = _T("");
	m_Department = _T("");
	m_Division = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CDBVListSet::GetDefaultConnect()
{
	
	CString strPath;
	
	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, strPath.GetBuffer(_MAX_PATH), _MAX_PATH));		
	
	strPath.ReleaseBuffer();
	
	int nIndex  = strPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		strPath = strPath.Left(nIndex);
	}
	else {
		strPath.Empty();
	}

	CString strConnection;
	strConnection.Format(_T("ODBC;DSN=MS Access Database;DBQ=%s\\employee.mdb;UID=;PWD=;"), (LPCTSTR)strPath);

	return strConnection;
}


CString CDBVListSet::GetDefaultSQL()
{
	return _T("[Employee8]");
}

void CDBVListSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDBVListSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Email]"), m_Email);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Phone]"), m_Phone);
	RFX_Text(pFX, _T("[Location]"), m_Location);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Department]"), m_Department);
	RFX_Text(pFX, _T("[Division]"), m_Division);
	//}}AFX_FIELD_MAP
}

void CDBVListSet::SetFilter(CString strCurQuery)
{
	if (strCurQuery == m_strFilter)
		return;

	CWaitCursor wait;

	m_strFilter.Format(_T("[Division] = '%s'"), (LPCTSTR)strCurQuery);
	if (!IsOpen())
		Open();

	Requery();

	// update record counts
	while (!IsEOF())
		MoveNext();
}


void CDBVListSet::SetSort(LPCTSTR pszSortField)
{
	// convenience function to set the SQL sort for the query

	m_strSort = pszSortField;
	if (IsOpen())
	{
		CWaitCursor wait;
		Requery();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBVListSet diagnostics

#ifdef _DEBUG
void CDBVListSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDBVListSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

