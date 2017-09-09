// ReportCustomHeapView.cpp : implementation of the CReportCustomHeapView class
//

#include "stdafx.h"
#include "ReportCustomHeap.h"

#include "ReportCustomHeapDoc.h"
#include "ReportCustomHeapView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLUMN_TEXT		 0
#define COLUMN_COSTRAINT 1
#define COLUMN_NUMBER	 2
#define COLUMN_DATETIME  3
#define COLUMN_VARIANT	 4


// XTP_DECLARE_HEAP_ALLOCATOR(CReportStringAllocator)
// XTP_IMPLEMENT_HEAP_ALLOCATOR(CReportStringAllocator, TRUE)
// typedef CXTPHeapStringT<CReportStringAllocator> CReportString;

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapView

IMPLEMENT_DYNCREATE(CReportCustomHeapView, CXTPReportView)

BEGIN_MESSAGE_MAP(CReportCustomHeapView, CXTPReportView)
	//{{AFX_MSG_MAP(CReportCustomHeapView)
	ON_COMMAND(ID_ADD_10K_RECORDS, OnAdd10kRecords)
	ON_COMMAND(ID_ADD_20K_RECORDS, OnAdd20kRecords)
	ON_COMMAND(ID_BATCHADD_10K_RECORDS, OnBatchAdd10kRecords)
	ON_COMMAND(ID_BATCHADD_20K_RECORDS, OnBatchAdd20kRecords)

	ON_COMMAND(ID_REMOVE_ALL_RECORDS, OnRemoveAllRecords)
	ON_COMMAND(ID_VIEW_PREVIEW_MODE, OnViewPreviewMode)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIEW_MODE, OnUpdateViewPreviewMode)
	ON_COMMAND(ID_REMOVE_HALF_RECORDS, OnRemoveHalfRecords)
	ON_COMMAND(ID_FREE_EXTRA_BATCH_DATA, OnFreeExtraBatchData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapView construction/destruction

CReportCustomHeapView::CReportCustomHeapView()
{
	// TODO: add construction code here
}

CReportCustomHeapView::~CReportCustomHeapView()
{
}

BOOL CReportCustomHeapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapView printing

BOOL CReportCustomHeapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReportCustomHeapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReportCustomHeapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapView diagnostics

#ifdef _DEBUG
void CReportCustomHeapView::AssertValid() const
{
	CView::AssertValid();
}

void CReportCustomHeapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReportCustomHeapDoc* CReportCustomHeapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportCustomHeapDoc)));
	return (CReportCustomHeapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCustomHeapView message handlers

void CReportCustomHeapView::OnInitialUpdate() 
{
	CXTPReportView::OnInitialUpdate();

//	GetReportCtrl().ShowHeader();
	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	//wndReport.AllowEdit(TRUE);	
	//wndReport.FocusSubItems(TRUE);

	wndReport.ShowGroupBy();
	wndReport.EnableDragDrop(_T("ReportCustomGeapSample"), xtpReportAllowDrag | xtpReportAllowDrop);
		
	//-----------------------------------------------------------------------
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_TEXT,		_T("Text"),		  150));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_COSTRAINT,	_T("Constraint"), 80, FALSE));	
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_NUMBER,		_T("Number"),	  100));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_DATETIME,	_T("Date"),		  150));
	wndReport.AddColumn(new CXTPReportColumn(COLUMN_VARIANT,	_T("VARIANT"),	  180));

	for (int i = 0; i < 5; i++)
	{
		wndReport.AddColumn(new CXTPReportColumn(COLUMN_VARIANT + i + 1, _T("Text"),	150));		
		wndReport.AddColumn(new CXTPReportColumn(COLUMN_VARIANT + i + 2, _T("Number"),	70));
		wndReport.AddColumn(new CXTPReportColumn(COLUMN_VARIANT + i + 3, _T("Date"),	150));
	}

	wndReport.GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->m_bConstraintEdit = TRUE;
	wndReport.GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->AddComboButton();

	wndReport.GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->AddConstraint(_T("State 1"), 1);
	wndReport.GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->AddConstraint(_T("State 2"), 2);
	wndReport.GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->AddConstraint(_T("State 3"), 3);
}

void CReportCustomHeapView::AddRecord(int nState, LPCTSTR pcszText, double dNumber, 
									  const COleDateTime& dtDate, const COleVariant& varVariant)
{
	static const CString cstrNumberFormat(_T("%06.3f"));

	CXTPReportRecord* pRec = new CXTPReportRecord;

	CString strConstraint = GetReportCtrl().GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->GetConstraints()->GetAt(nState)->m_strConstraint;	
	pRec->AddItem(new CXTPReportRecordItemText(pcszText));
	pRec->AddItem(new CXTPReportRecordItemText(strConstraint));
	pRec->AddItem(new CXTPReportRecordItemNumber(dNumber, cstrNumberFormat));
	pRec->AddItem(new CXTPReportRecordItemDateTime(dtDate));
	pRec->AddItem(new CXTPReportRecordItemVariant(varVariant));
	
	for (int i = 0; i < 5; i++)
	{	
		pRec->AddItem(new CXTPReportRecordItemText(pcszText));	
		pRec->AddItem(new CXTPReportRecordItemNumber(dNumber, cstrNumberFormat));
		pRec->AddItem(new CXTPReportRecordItemDateTime(dtDate));
	}

	CString strPreviewText;
	strPreviewText.Format(_T("%s, %s, %s, %s, %s"),
		pRec->GetItem(0)->GetCaption(NULL),
		pRec->GetItem(1)->GetCaption(NULL),
		pRec->GetItem(2)->GetCaption(NULL),
		pRec->GetItem(3)->GetCaption(NULL),
		pRec->GetItem(4)->GetCaption(NULL));

	CXTPReportRecordItemPreview* pPreviewItem = new CXTPReportRecordItemPreview(strPreviewText);
	
	pRec->SetPreviewItem(pPreviewItem);

	GetReportCtrl().AddRecord(pRec);
}

void CReportCustomHeapView::AddRecords(int nCountToAdd) 
{		
	CWaitCursor _wc;

	DWORD dwTime0 = ::GetTickCount();

	int nRecords0 = GetReportCtrl().GetRecords()->GetCount();

	CString strText;
	COleVariant varVariant;
	
	CWnd* pStatusBap = &((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar;

	for (int i = 0; i < nCountToAdd; i++)
	{
		int n = nRecords0 + i;
		int nState = n % 3;	
		strText.Format(_T("[%d] - Test TEXT item"), n+1);

		// just for test

		double dNumber = 77.77 * (n+11) / (double)(n / 7.11 + 1.1);
		
		COleDateTime dtDate(2000 + ((n%2) ? 1 : -1) * i % 400, n % 12 + 1, n % 28 + 1,
							n * 7 % 24, n * 31 % 60, n * 11 % 60);

		if (n%2 == 0) 
		{
			varVariant = (long)nState;
		}
		else if (n%3 == 0) 
		{
			varVariant = dtDate;
		}
		else if (n%5 == 0) 
		{
			varVariant = strText;
		}
		else
		{
			varVariant = _T("this is a VARIANT field");
		}		

		AddRecord(nState, strText, dNumber, dtDate, varVariant);

		if (i % 2500 == 0)
		{
			CString str;
			str.Format(_T("Adding Records %d %%"), (i + 1) * 100 / nCountToAdd);
			pStatusBap->SetWindowText(str);
			pStatusBap->UpdateWindow();
		}
	}
	pStatusBap->SetWindowText(_T(""));

	DWORD dwTime1 = ::GetTickCount();

	GetReportCtrl().Populate();

	DWORD dwTime2 = ::GetTickCount();

	UpdateTitle(dwTime1 - dwTime0, dwTime2 - dwTime1);
}

XTP_DECLARE_BATCH_ALLOC_OBJ_DATA(CBatchReportRecord_Data);

class CBatchReportRecord : public CXTPBatchAllocObjT<CXTPReportRecord, CBatchReportRecord_Data> 
{
public:
	CBatchReportRecord()
	{
		// nGrowBy parameter set to expected items count to avoid additional re-allocations.
		m_arrItems.SetSize(0, 20);

		AddItem(&m_itemText1);
		AddItem(&m_itemText2);
		AddItem(&m_itemNumber1);
		AddItem(&m_itemDateTime);
		AddItem(&m_itemVariant);

		for (int i = 0; i < 5; i++)
		{
			AddItem(&m_itemTextA[i]);
			AddItem(&m_itemNumberA[i]);
			AddItem(&m_itemDateTimeA[i]);
		}
	}
	~CBatchReportRecord()
	{
		m_arrItems.RemoveAll(); // don't call delete for each item.
	}

public:
	CXTPReportRecordItemText m_itemText1;
	CXTPReportRecordItemText m_itemText2;
	CXTPReportRecordItemNumber m_itemNumber1;
	CXTPReportRecordItemDateTime m_itemDateTime;
	CXTPReportRecordItemVariant m_itemVariant;
	
	CXTPReportRecordItemText m_itemTextA[5];	
	CXTPReportRecordItemNumber m_itemNumberA[5];	
	CXTPReportRecordItemDateTime m_itemDateTimeA[5];	
};

XTP_IMPLEMENT_BATCH_ALLOC_OBJ_DATA(CBatchReportRecord_Data, CBatchReportRecord, TRUE);

void CReportCustomHeapView::BatchAddRecords(int nCountToAdd) 
{	
//	CBatchReportRecord_Data::m_bDestroyEmptyBlocksOnFree = TRUE;
//	CBatchReportRecord_Data::m_bDestroyLastEmptyBlockOnFree = TRUE;
//	CBatchReportRecord_Data::m_nBlockSize = 5000;

	CWaitCursor _wc;

	DWORD dwTime0 = ::GetTickCount();
	int i;

	int nRecords0 = GetReportCtrl().GetRecords()->GetCount();

	CString strText;
	COleVariant varVariant;
	
	CWnd* pStatusBap = &((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar;

	// Expand array size once to avoid additional re-allocations.
	GetReportCtrl().GetRecords()->SetSize(nRecords0 + nCountToAdd, 10000);

	for (i = 0; i < nCountToAdd; i++)
	{
		CBatchReportRecord* pRec = new CBatchReportRecord();
		//GetReportCtrl().GetRecords()->Add(pRec);
		
		// Set new records to array which was previously expanded by SetSize.
		GetReportCtrl().GetRecords()->SetAt(nRecords0 + i, pRec);

		int n = nRecords0 + i;
		int nState = n % 3;	
		strText.Format(_T("[%d] - Test TEXT item"), n+1);

		// just for test

		double dNumber = 77.77 * (n+11) / (double)(n / 7.11 + 1.1);
		
		COleDateTime dtDate(2000 + ((n%2) ? 1 : -1) * i % 400, n % 12 + 1, n % 28 + 1,
							n * 7 % 24, n * 31 % 60, n * 11 % 60);

		if (n%2 == 0) 
		{
			varVariant = (long)nState;
		}
		else if (n%3 == 0) 
		{
			varVariant = dtDate;
		}
		else if (n%5 == 0) 
		{
			varVariant = strText;
		}
		else
		{
			varVariant = _T("this is a VARIANT field");
		}	
		
		static const CString cstrNumberFormat(_T("%06.3f"));
		
		CString strConstraint = GetReportCtrl().GetColumns()->GetAt(COLUMN_COSTRAINT)->GetEditOptions()->GetConstraints()->GetAt(nState)->m_strConstraint;	
		pRec->m_itemText1.SetValue(strText);
		pRec->m_itemText2.SetValue(strConstraint);
		pRec->m_itemNumber1.SetValue(dNumber);
		pRec->m_itemNumber1.SetFormatString(cstrNumberFormat);
		pRec->m_itemDateTime.SetValue(dtDate);
		pRec->m_itemVariant.SetValue(varVariant);
		
		for (int j = 0; j < 5; j++)
		{	
			pRec->m_itemTextA[j].SetValue(strText);	
			pRec->m_itemNumberA[j].SetValue(dNumber);	
			pRec->m_itemDateTimeA[j].SetValue(dtDate);
		}

		if (i % 2500 == 0)
		{
			CString str;
			str.Format(_T("Adding Records %d %%"), (i + 1) * 100 / nCountToAdd);
			pStatusBap->SetWindowText(str);
			pStatusBap->UpdateWindow();
		}
	}
	pStatusBap->SetWindowText(_T(""));

	DWORD dwTime1 = ::GetTickCount();

	GetReportCtrl().Populate();

	DWORD dwTime2 = ::GetTickCount();

	UpdateTitle(dwTime1 - dwTime0, dwTime2 - dwTime1);
}


void CReportCustomHeapView::UpdateTitle(DWORD dwAddTime, DWORD dwPopulateTime) 
{
	int nRecordsCount = GetReportCtrl().GetRecords()->GetCount();
	CString strTitleNew, strTitle = GetDocument()->GetTitle();
	strTitle = strTitle.SpanExcluding(_T("-"));
	strTitle.TrimRight();
	
	if (dwPopulateTime != (DWORD)-1)
	{	
		strTitleNew.Format(_T("%s - records count [%d], Operation time %.3f sec (add/remove records = %.3f sec, populate = %.3f sec)"), 
						strTitle, nRecordsCount,
						(double)(dwAddTime + dwPopulateTime) / 1000.0, 
						(double)dwAddTime / 1000.0, (double)dwPopulateTime / 1000.0);
	}
	else
	{
		strTitleNew.Format(_T("%s - records count [%d], Operation %.3f sec"), 
						strTitle, nRecordsCount, (double)(dwAddTime) / 1000.0);
	}
	
	GetDocument()->SetTitle(strTitleNew);


//	strTitle.Format(_T("Allocators: Refs (heap handle) Data = %d (%x), Row = %d (%x), Str = %d (%x)"),
//		CXTPReportDataAllocator::ms_dwRefs, CXTPReportDataAllocator::ms_hCustomHeap, 
//		CXTPReportRowAllocator::ms_dwRefs, CXTPReportRowAllocator::ms_hCustomHeap, 
//		CXTPReportStringAllocator::ms_dwRefs, CXTPReportStringAllocator::ms_hCustomHeap);
//
//	CWnd* pStatusBap = &((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar;
//	pStatusBap->SetWindowText(strTitle);
}

void CReportCustomHeapView::OnViewPreviewMode() 
{
	GetReportCtrl().EnablePreviewMode(!GetReportCtrl().IsPreviewMode());
	
	GetReportCtrl().AdjustScrollBars();
	GetReportCtrl().RedrawControl();	
}

void CReportCustomHeapView::OnUpdateViewPreviewMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().IsPreviewMode());
}

void CReportCustomHeapView::OnAdd10kRecords() 
{
//	GetReportCtrl().ResetContent();
	AddRecords(10000);
}

void CReportCustomHeapView::OnAdd20kRecords() 
{
//	GetReportCtrl().ResetContent();
	AddRecords(20000);	
}


void CReportCustomHeapView::OnBatchAdd10kRecords() 
{
//	GetReportCtrl().ResetContent();
	BatchAddRecords(10000);
}

void CReportCustomHeapView::OnBatchAdd20kRecords() 
{
//	GetReportCtrl().ResetContent();
	BatchAddRecords(20000);	
}


void CReportCustomHeapView::OnRemoveAllRecords() 
{
	CWaitCursor _wc;

	DWORD dwTime0 = ::GetTickCount();

	//GetReportCtrl().GetRecords()->RemoveAll();
	GetReportCtrl().ResetContent();
	
	DWORD dwTime1 = ::GetTickCount();
	//GetReportCtrl().Populate();	

	//DWORD dwTime2 = ::GetTickCount();
	
	UpdateTitle(dwTime1 - dwTime0, (DWORD)-1);
}

void CReportCustomHeapView::OnRemoveHalfRecords() 
{
	CWaitCursor _wc;

	DWORD dwTime0 = ::GetTickCount();

	CXTPReportRecords* pRecords = GetReportCtrl().GetRecords();
	int nRecordsToDel = pRecords->GetCount() / 2 + 1;
		
	CWnd* pStatusBap = &((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar;

	for (int i = 0; i < nRecordsToDel && pRecords->GetCount(); i++)
	{
		int nRand = (int)RAND_S();

		int nIndex = (pRecords->GetCount() * nRand) % pRecords->GetCount();

		if (nIndex >= 0 && nIndex < pRecords->GetCount())
			pRecords->RemoveAt(nIndex);
		
		if (i % 500 == 0)
		{
			CString str;
			str.Format(_T("Removing Records %d %%"), (i + 1) * 100 / nRecordsToDel);
			pStatusBap->SetWindowText(str);
			pStatusBap->UpdateWindow();
		}
	}
	pStatusBap->SetWindowText(_T(""));
		
	
	DWORD dwTime1 = ::GetTickCount();
	
	GetReportCtrl().Populate();	

	DWORD dwTime2 = ::GetTickCount();
	
	UpdateTitle(dwTime1 - dwTime0, dwTime2 - dwTime1);	
}

void CReportCustomHeapView::OnFreeExtraBatchData() 
{
	CBatchReportRecord::FreeExtraData();	
	CXTPReportControl::FreeRowBatchExtraData();
}
