// ReportDataBindingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportDataBinding.h"
#include "ReportDataBindingDlg.h"
#include "atldbcli.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CReportDataBindingDlg dialog

CReportDataBindingDlg::CReportDataBindingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportDataBindingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportDataBindingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReportDataBindingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDataBindingDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportDataBindingDlg, CDialog)
	//{{AFX_MSG_MAP(CReportDataBindingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_OPEN_DB_BUTTON, OnOpenDatabaseButton)
	ON_BN_CLICKED(IDC_ACTION_BUTTON, OnActionButton)
	ON_COMMAND(ID_ADD_REC_TO_RECSET, OnAddRecToRecset)
	ON_COMMAND(ID_DELETE_REC_FROM_RECSET, OnDeleteRecFromRecset)
	ON_COMMAND(ID_ADD_RECORD, OnAddRecord)
	ON_COMMAND(ID_DELETE_RECORD, OnDeleteRecord)
	ON_UPDATE_COMMAND_UI(ID_ADD_REC_TO_RECSET, OnUpdateAddRecToRecset)
	ON_UPDATE_COMMAND_UI(ID_ADD_RECORD, OnUpdateAddRecord)
	ON_UPDATE_COMMAND_UI(ID_DELETE_REC_FROM_RECSET, OnUpdateDeleteRecFromRecset)
	ON_UPDATE_COMMAND_UI(ID_DELETE_RECORD, OnUpdateDeleteRecord)
	ON_COMMAND(ID_SERVICE, OnService)
	//}}AFX_MSG_MAP
	ON_NOTIFY(XTP_NM_REPORT_SELCHANGED, IDC_TABLES, OnTableChanged)
	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED, IDC_RECORDS, OnValueChanged)
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDataBindingDlg message handlers

BOOL CReportDataBindingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// subclass the report control
	m_wndTablesReportCtrl.SubclassDlgItem(IDC_TABLES, this);
	m_wndRecordsReportCtrl.SubclassDlgItem(IDC_RECORDS, this);

	//  add table report columns
	m_wndTablesReportCtrl.AddColumn(new CXTPReportColumn(0, _T("Tables"), 280));

	// set the first column as a group column
	m_wndRecordsReportCtrl.ShowGroupBy();

	// define style attributes for the report control
	m_wndRecordsReportCtrl.FocusSubItems(TRUE);
	m_wndRecordsReportCtrl.AllowEdit(TRUE);


	// Set control resizing.
//	SetResize(IDC_TABLES, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_RECORDS, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
//	SetResize(IDC_OPEN_DB_BUTTON, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);

	// Load window placement
	LoadPlacement(_T("CReportDataBindingDlg"));


	// open default database
/*	TCHAR szModuleFileName[_MAX_PATH];
	GetModuleFileName(NULL, szModuleFileName, MAX_PATH);
	CString strDatabase = szModuleFileName;
	strDatabase = strDatabase.Left(strDatabase.ReverseFind('\\') + 1);
	strDatabase += _T("AccessSample.mdb");*/
	TCHAR szCurDir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, szCurDir);
	CString strDatabase = szCurDir;
	strDatabase += _T("\\AccessSample.mdb");
	CString strConnection;
	strConnection.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=%s;Mode=Share Deny None;"), strDatabase);
	OpenDatabase(strConnection);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReportDataBindingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReportDataBindingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReportDataBindingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReportDataBindingDlg::OnDestroy()
{
	CDialog::OnDestroy();

	try
	{
		if(m_pConnection)
			m_pConnection->Close();
	}
	catch(_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
	}

	// Save window placement
	SavePlacement(_T("CReportDataBindingDlg"));

}

void CReportDataBindingDlg::OnOpenDatabaseButton()
{
	m_wndTablesReportCtrl.ResetContent(TRUE);

	HRESULT hr;
	CString strTable = _T("");

	// choose database
	CDataSource dsConnection;
	if(FAILED(hr = dsConnection.Open(AfxGetMainWnd()->GetSafeHwnd())))
		return;
	BSTR bstrConnection;
	if(FAILED(hr = dsConnection.GetInitializationString(&bstrConnection, false)))
		return;
	CComVariant vtConnection(bstrConnection);
	::SysFreeString(bstrConnection);
	dsConnection.Close();
	// open database
	OpenDatabase(CString(vtConnection.bstrVal));
}

void CReportDataBindingDlg::OnTableChanged(NMHDR* /*pNotifyStruct*/, LRESULT* /*result*/)
{
	CXTPReportSelectedRows* pSelectedRows = m_wndTablesReportCtrl.GetSelectedRows();
	if(!(pSelectedRows && pSelectedRows->GetCount()))
		return;
	CXTPReportRow* pRow = pSelectedRows->GetAt(0);
	if(pRow)
	{
		CXTPReportRecord* pRecord = pRow->GetRecord();
		if(pRecord)
		{
			CXTPReportRecordItemText* pItem = (CXTPReportRecordItemText*)pRecord->GetItem(0);
			if(pItem)
			{
				CString strTable = pItem->GetValue();
				ShowRecords(strTable);
			}
		}
	}
}

void CReportDataBindingDlg::OpenDatabase(CString strConnection)
{
	m_wndTablesReportCtrl.ResetContent(TRUE);

	HRESULT hr;
	CString strTable = _T("");
	try
	{

		// open database
		CComVariant vtConnection(strConnection);
		if(FAILED(hr = m_pConnection.CreateInstance(__uuidof(Connection))))
			return;
		if(FAILED(hr = m_pConnection->Open(_bstr_t(vtConnection), _bstr_t(""), _bstr_t(_T("")), 0)))
			return;
		// fill up table list
		_RecordsetPtr pTables;
		if(FAILED(hr = m_pConnection->raw_OpenSchema(adSchemaTables, vtMissing, vtMissing, &pTables)) || pTables == NULL)
			return;
		VARIANT_BOOL bEof;
		pTables->get_bEOF(&bEof);
		while(!bEof)
		{
			FieldsPtr pFields = NULL;
			hr = pTables->get_Fields(&pFields);
			if(pFields == NULL)
				break;
			FieldPtr pField = NULL;
			hr = pFields->get_Item(COleVariant(_bstr_t(_T("TABLE_TYPE"))), &pField);
			if(pField == NULL)
				break;
			VARIANT vtValue;
			pField->get_Value(&vtValue);
			if(_wcsicmp(vtValue.bstrVal, L"TABLE") == 0)
			{
				hr = pFields->get_Item(COleVariant(_bstr_t(_T("TABLE_NAME"))), &pField);
				if(pField == NULL)
					break;
				pField->get_Value(&vtValue);
				CXTPReportRecord* pRecord = m_wndTablesReportCtrl.AddRecord(new CXTPReportRecord);
				pRecord->AddItem(new CXTPReportRecordItemText(CString(vtValue.bstrVal)));
				if(strTable.IsEmpty())
					strTable = vtValue.bstrVal;
			}
			pTables->MoveNext();
			pTables->get_bEOF(&bEof);
		}
		pTables->Close();
		m_wndTablesReportCtrl.Populate();
		// show table records
		if(m_wndTablesReportCtrl.GetRows()->GetCount())
		{
			m_wndTablesReportCtrl.GetRows()->GetAt(0)->SetSelected(TRUE);
			ShowRecords(strTable);
		}
	}
	catch(_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
	}

}

void CReportDataBindingDlg::ShowRecords(CString strTable)
{
	HRESULT hr;

	// show records
	VARIANT vtRestrictions;
	SAFEARRAYBOUND rgsabound[1];
	::VariantInit(&vtRestrictions);
	vtRestrictions.vt = VT_ARRAY | VT_VARIANT;
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 4;
	vtRestrictions.parray = SafeArrayCreate(VT_VARIANT, 1, rgsabound);
	VARIANT vtValue;
	vtValue.vt = VT_EMPTY;
	long i = 0;
	SafeArrayPutElement(vtRestrictions.parray, &i, &vtValue);
	i = 1;
	SafeArrayPutElement(vtRestrictions.parray, &i, &vtValue);
	i = 3;
	SafeArrayPutElement(vtRestrictions.parray, &i, &vtValue);
	vtValue.vt = VT_BSTR;
	vtValue.bstrVal = _bstr_t(strTable);
	i = 2;
	SafeArrayPutElement(vtRestrictions.parray, &i, &vtValue);
	VARIANT vtConnection;
	vtConnection.vt = VT_DISPATCH;
	vtConnection.pdispVal = (IDispatch*)m_pConnection;
	vtConnection.pdispVal->AddRef();
	m_pRecords.CreateInstance(__uuidof(Recordset));
	m_pRecords->put_CursorType(adOpenDynamic);
	m_pRecords->put_CursorLocation(adUseClient);
	CString strQuery;
	strQuery.Format(_T("select * from [%s]"), strTable);
	hr = m_pRecords->Open(COleVariant(_bstr_t(strQuery)), vtConnection, adOpenDynamic, adLockOptimistic, adCmdText);
//	hr = m_pRecords->Open(COleVariant(_bstr_t(strTable)), vtConnection, adOpenDynamic, adLockOptimistic, adCmdTable);
	m_wndRecordsReportCtrl.GetDataManager()->SetDataSource(m_pRecords);
	m_wndRecordsReportCtrl.GetDataManager()->DataBind();
	// add empty header row
	m_wndRecordsReportCtrl.GetPaintManager()->SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerOutlook);
	m_wndRecordsReportCtrl.GetHeaderRecords()->RemoveAll();
	CXTPReportRecord* pRecord = NULL;
	if(SUCCEEDED(hr = m_wndRecordsReportCtrl.GetDataManager()->CreateEmptyRecord(&pRecord)) && pRecord != NULL)
	m_wndRecordsReportCtrl.GetHeaderRecords()->Add(pRecord);
	m_wndRecordsReportCtrl.ShowHeaderRows();
	m_wndRecordsReportCtrl.HeaderRowsAllowEdit(TRUE);
	m_wndRecordsReportCtrl.PopulateHeaderRows();
}

void CReportDataBindingDlg::OnValueChanged(NMHDR * pNotifyStruct, LRESULT*)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(!pItemNotify)
		return;
	if(pItemNotify->pRow->GetType() == xtpRowTypeHeader)
	{
		if(pItemNotify->pItem)
		{
		}
	}
	else if(pItemNotify->pItem && pItemNotify->pItem->GetRecord())
		m_wndRecordsReportCtrl.GetDataManager()->UpdateRecord(pItemNotify->pItem->GetRecord(), pItemNotify->pItem);
}

BOOL CReportDataBindingDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB))
		return FALSE;

	return CDialog::PreTranslateMessage(pMsg);
}

void CReportDataBindingDlg::OnActionButton()
{
	CMenu PopupMenu;
	CMenu* pSubMenu;

	if(!PopupMenu.LoadMenu(IDR_POPUP_MENU))
		return;
	pSubMenu = PopupMenu.GetSubMenu(0);
	if(!pSubMenu)
		return;
	CRect rc;
	GetDlgItem(IDC_ACTION_BUTTON)->GetWindowRect(&rc);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rc.right, rc.top, this);
	
	PopupMenu.DestroyMenu();
}

void CReportDataBindingDlg::OnUpdateAddRecToRecset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecords != NULL);
}

void CReportDataBindingDlg::OnAddRecToRecset() 
{
	// This function demonstrates the automatic report control update on new record insertion into the recordset.
	// Upon record insertion, the data manager receives an event and inserts a record into the report control,
	// binding it to the recordset record.
	try
	{
		
		HRESULT hr;
		
		if(m_pRecords == NULL)
			return;
		// create new record
		CXTPReportRecord* pRecord = NULL;
		if(FAILED(hr = m_wndRecordsReportCtrl.GetDataManager()->CreateEmptyRecord(&pRecord)) || !pRecord)
			return;
		// add record without field list
		if(FAILED(hr = m_pRecords->AddNew()))
			return;
		// update fields
		FieldsPtr pFields;
		if(FAILED(hr = m_pRecords->get_Fields(&pFields)) || pFields == NULL)
			return;
		long lFields;
		if(FAILED(hr = pFields->get_Count(&lFields)) || lFields == 0)
			return;
		VARIANT vtIdx;
		vtIdx.vt = VT_I4;
		int i;
		for(i = 0; i < lFields; i++)
		{
			vtIdx.lVal = i;
			FieldPtr pField;
			if(FAILED(hr = pFields->get_Item(vtIdx, &pField)) || pField == NULL)
				break;
			long lAttrs;
			if(FAILED(hr = pField->get_Attributes(&lAttrs)))
				break;
			//if(!(lAttrs & adFldUpdatable))
			//	continue;
			CXTPReportRecordItemVariant* pItem = (CXTPReportRecordItemVariant*)pRecord->GetItem(i);
			if(!pItem)
				break;
			VARIANT vtValue = pItem->GetValue();
			if(vtValue.vt == VT_BSTR)
			{
				CString strValue = _T("New Record");
				COleVariant vtBstrValue(strValue);
				hr = pField->put_Value(vtBstrValue);
			}
		}
		if(FAILED(hr) || i < lFields)
		{
			m_pRecords->CancelUpdate();
			return;
		}
		if(FAILED(hr = m_pRecords->Update()))
			hr = m_pRecords->CancelUpdate();

		pRecord->InternalRelease();
	}
	catch(_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
		m_pRecords->CancelUpdate();
	}

}

void CReportDataBindingDlg::OnUpdateDeleteRecFromRecset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecords != NULL && m_wndRecordsReportCtrl.GetSelectedRows() && m_wndRecordsReportCtrl.GetSelectedRows()->GetCount() > 0);
}

void CReportDataBindingDlg::OnDeleteRecFromRecset() 
{
	// This function demonstrates the automatic report control update on record deletion from the recordset.
	// Upon record deletion, the data manager receives an event and deletes a record from the report control.

	HRESULT hr;

	if(m_pRecords == NULL)
		return;
	CXTPReportSelectedRows* pSelectedRows = m_wndRecordsReportCtrl.GetSelectedRows();
	if(!pSelectedRows)
		return;
	int nRow = pSelectedRows->GetCount() - 1;
	if(nRow < 0)
		return;
	CWaitCursor wc;
	CXTPReportRow* pFocusedRow = pSelectedRows->GetAt(pSelectedRows->GetCount() - 1);
	pFocusedRow = m_wndRecordsReportCtrl.GetRows()->GetAt(pFocusedRow->GetIndex() + 1);
	while(nRow >= 0)
	{
		CXTPReportRecord* pRecord = pSelectedRows->GetAt(nRow--)->GetRecord();
		if(pRecord)
		{
			// get data source record bookmark
			VARIANT vtBookmark = pRecord->GetBookmark();
			if(vtBookmark.vt != VT_EMPTY)
			{
				// move to specified record
				if(SUCCEEDED(hr = m_pRecords->put_Bookmark(vtBookmark)))
				{
					// delete record
					if(FAILED(hr = m_pRecords->Delete(adAffectCurrent)))
						m_pRecords->CancelUpdate();
				}
			}
		}
		if(nRow >= pSelectedRows->GetCount())
			nRow = pSelectedRows->GetCount() - 1;
	}
	m_wndRecordsReportCtrl.SetFocusedRow(pFocusedRow ? pFocusedRow : m_wndRecordsReportCtrl.GetFocusedRow());
}

void CReportDataBindingDlg::OnUpdateAddRecord(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecords != NULL);
}

void CReportDataBindingDlg::OnAddRecord() 
{
	// This function demonstrates how to insert records into the report control.

	m_wndRecordsReportCtrl.AddNewRecord();
}

void CReportDataBindingDlg::OnUpdateDeleteRecord(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecords != NULL && m_wndRecordsReportCtrl.GetSelectedRows() && m_wndRecordsReportCtrl.GetSelectedRows()->GetCount() > 0);
}

void CReportDataBindingDlg::OnDeleteRecord() 
{
	// This function demonstrates how to delete records from the report control.

	m_wndRecordsReportCtrl.DeleteSelectedRows();
}

void CReportDataBindingDlg::OnService() 
{
	HRESULT hr;

	if(m_pRecords == NULL)
		return;
	long lStatus;
	if(FAILED(hr = m_pRecords->get_Status(&lStatus)))
		return;
//	if(lStatus == adStateOpen)
		m_pRecords->Close();
//	else if(lStatus == adStateClosed)
	{
		VARIANT vtSource;
		m_pRecords->get_Source(&vtSource);
		VARIANT vtConnection;
		vtConnection.vt = VT_DISPATCH;
		vtConnection.pdispVal = (IDispatch*)m_pConnection;
//		vtConnection.pdispVal->AddRef();
//		m_pRecords->put_CursorType(adOpenDynamic);
//		m_pRecords->put_CursorLocation(adUseClient);
//		CString strQuery;
//		strQuery.Format(_T("select * from [%s]"), strTable);
		hr = m_pRecords->Open(vtSource, vtConnection, adOpenDynamic, adLockOptimistic, adCmdText);
	}
//	HRESULT hr = m_pRecords->Resync(adAffectAll, adResyncUnderlyingValues);
}


void CReportDataBindingDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	CPopupMenuInit::Init(this, pPopupMenu, TRUE);
}
