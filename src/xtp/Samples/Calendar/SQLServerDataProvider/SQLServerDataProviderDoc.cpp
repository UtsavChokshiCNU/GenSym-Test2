// SQLServerDataProviderDoc.cpp : implementation of the CSQLServerDataProviderDoc class
//

#include "stdafx.h"
#include "SQLServerDataProvider.h"

#include "SQLServerDataProviderDoc.h"
#include "CalendarDataProviderSQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderDoc

IMPLEMENT_DYNCREATE(CSQLServerDataProviderDoc, CDocument)

BEGIN_MESSAGE_MAP(CSQLServerDataProviderDoc, CDocument)
	//{{AFX_MSG_MAP(CSQLServerDataProviderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderDoc construction/destruction

CSQLServerDataProviderDoc::CSQLServerDataProviderDoc()
{
	m_pSQLDataProvider = NULL;

}

CSQLServerDataProviderDoc::~CSQLServerDataProviderDoc()
{
	SafeReleaseSQLDataProvider();
}

void CSQLServerDataProviderDoc::SafeReleaseSQLDataProvider()
{
	if (m_pSQLDataProvider)
	{
		m_pSQLDataProvider->Close();

		m_pSQLDataProvider->InternalRelease();
	}
	m_pSQLDataProvider = NULL;
}

BOOL CSQLServerDataProviderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CString strConnectionString = AfxGetApp()->GetProfileString(csOptProfileSection, 
									csOptDataSourceSQLsrvProp, _T(""));
	
	SafeReleaseSQLDataProvider();
	m_pSQLDataProvider = new CCalendarDataProviderSQL();

	if (!m_pSQLDataProvider)
		AfxThrowMemoryException();
	
	m_pSQLDataProvider->SetConnectionString(strConnectionString);

	if (!m_pSQLDataProvider->Open())
	{
		if (!strConnectionString.IsEmpty())
		{
			if (AfxGetMainWnd() && !AfxGetMainWnd()->IsWindowVisible()) 
			{					
				AfxGetMainWnd()->ShowWindow(SW_SHOW);
				AfxGetMainWnd()->UpdateWindow();				
			}
			CString strErr = _T("Cannot connect to DataSource: ");
			strErr += strConnectionString;
			AfxMessageBox(strErr);
			
		}
		else if (AfxGetMainWnd()) 
		{
			AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILE_OPEN);
		}

		UpdateAllViews(NULL, uvfPopulate + uvfDetachDataProvider);
	}
	else 
	{
		UpdateAllViews(NULL, uvfPopulate + uvfSetDataProvider);
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderDoc serialization

void CSQLServerDataProviderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

CXTPCalendarData* CSQLServerDataProviderDoc::GetDataProvider_SQLServer() 
{
	return m_pSQLDataProvider;
}
/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderDoc diagnostics

#ifdef _DEBUG
void CSQLServerDataProviderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSQLServerDataProviderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSQLServerDataProviderDoc commands

