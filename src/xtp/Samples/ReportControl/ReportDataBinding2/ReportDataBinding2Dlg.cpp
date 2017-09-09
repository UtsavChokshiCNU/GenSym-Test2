// ReportDataBinding2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportDataBinding2.h"
#include "ReportDataBinding2Dlg.h"
#include "MenuInit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString LoadStringFromResources(const UINT nID)
{
	CString str(_T(""));
	str.LoadString(nID);
	return str;
}

/////////////////////////////////////////////////////////////////////////////
// CStaticLine

CStaticLine::CStaticLine()
{
}

CStaticLine::~CStaticLine()
{
}


BEGIN_MESSAGE_MAP(CStaticLine, CStatic)
	//{{AFX_MSG_MAP(CStaticLine)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticLine message handlers

// This function draws the horizontal line, followed by the text. The general
// idea for the line drawing comes from Hans Buehler's article at
// http://www.codeguru.com/staticctrl/draw_bevel.shtml
//
// Note that this class is intended to be just a simple separator, so the
// only static styles I implement here are SS_LEFT, SS_CENTER, SS_RIGHT, and
// SS_NOPREFIX.  Also note that the line is always drawn vertically centered
// in the control, so if you make the control tall enough you can get the 
// text totally above the line.

void CStaticLine::OnPaint() 
{
	CPaintDC dc(this);             // device context for painting
	CRect    rcWnd;                // RECT of the static control
	CRect    rcText;               // RECT in which text will be drawn
	CString  strText;              // text to draw
	CFont*   pfontOld;
	UINT     uFormat;              // format for CDC::DrawText()
	DWORD    dwStyle = GetStyle(); // this window's style

    // Get the screen & client coords.

    GetWindowRect(rcWnd);
    GetClientRect(rcText);

    // If the control is taller than it is wide, draw a vertical line.
    // No text is drawn in this case.

    if (rcWnd.Height() > rcWnd.Width())
        dc.Draw3dRect(rcWnd.Width()/2, 0, 2, rcWnd.Height(), ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DHIGHLIGHT));
    else
	{
        // We're drawing a horizontal line.
        // The text will always be at the top of the control.  Also check
        // if the SS_NOPREFIX style is set.                                        

        uFormat = DT_TOP;

        if (dwStyle & SS_NOPREFIX)
            uFormat |= DT_NOPREFIX;

        // Voila!  One 3D line coming up.

        dc.Draw3dRect(0, rcWnd.Height()/2, rcWnd.Width(), 2, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DHIGHLIGHT));


        // Now get the text to be drawn.  I add two spaces to the string
        // to make a bit of space between the end of the line and the text.
        // Space is added to one or both ends of the text as appropriate.
        // Along the way, I add another formatting flag to uFormat.

        GetWindowText(strText);

        if (dwStyle & SS_CENTER)
        {
            strText = _T("  ") + strText;
            strText += _T("  ");

            uFormat |= DT_CENTER;
        }
        else if (dwStyle & SS_RIGHT)
        {
            strText = _T("  ") + strText;

            uFormat |= DT_RIGHT;
        }
        else
        {
            strText += _T("  ");
        
            uFormat |= DT_LEFT;
        }

        // Get the font for the text.
    
        pfontOld = dc.SelectObject(GetFont());

        // Set the background color to the same as the dialog, so the text
        // will be opaque.  This erases all traces of the 3D line as the
        // text is drawn over it.  (No need to call CDC::SetBkMode() because
        // the default mode for a DC is opaque.)

        dc.SetBkColor(::GetSysColor(COLOR_BTNFACE));
        dc.DrawText(strText, rcText, uFormat);

        // Clean up GDI objects like a good lil' programmer.

        dc.SelectObject(pfontOld);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent), m_strConnectionString(_T("")),
	m_pConnection(NULL), m_pRecordset(NULL)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)

	DDX_Control(pDX, IDOK, m_btnExitApp);
	DDX_Control(pDX, IDC_HELP_BUTTON, m_btnHelp);
	DDX_Control(pDX, IDC_ACTIONS_BUTTON, m_btnActions);
	DDX_Control(pDX, IDC_TABLES_LIST, m_wndTablesListCtrl);
	//DDX_Control(pDX, IDC_RECORDS_REPORT, m_wndRecordsReportCtrl);

	DDX_Control(pDX, IDC_CJ_LINE, m_wndHorizLine);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
	ON_LBN_SELCHANGE(IDC_TABLES_LIST, OnSelchangeTablesList)
	ON_BN_CLICKED(IDC_ACTIONS_BUTTON, OnButtonDropDown)
	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED, IDC_RECORDS_REPORT, OnValueChanged)
	ON_UPDATE_COMMAND_UI(ID_DELETE_RECORDS, OnUpdateDeleteRecords)
	ON_UPDATE_COMMAND_UI(ID_DELETE_RECORDS_FROM_RECORDSET, OnUpdateDeleteRecordsFromRecordset)
	ON_UPDATE_COMMAND_UI(ID_ADD_RECORDS, OnUpdateAddRecords)
	ON_UPDATE_COMMAND_UI(ID_ADD_RECORDS_TO_RECORDSET, OnUpdateAddRecordsToRecordset)
	ON_COMMAND(ID_ADD_RECORDS, OnAddRecords)
	ON_COMMAND(ID_ADD_RECORDS_TO_RECORDSET, OnAddRecordsToRecordset)
	ON_COMMAND(ID_DELETE_RECORDS, OnDeleteRecords)
	ON_COMMAND(ID_DELETE_RECORDS_FROM_RECORDSET, OnDeleteRecordsFromRecordset)
	//ON_WM_INITMENUPOPUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

BOOL CSampleDlg::OnInitDialog()
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

	// Subclass the Report Control
	m_wndRecordsReportCtrl.SubclassDlgItem(IDC_RECORDS_REPORT, this);
	
	// Assign the watermark
	CBitmap bm;
	if (bm.LoadBitmap(IDB_CJ_LOGO))
	{
		m_wndRecordsReportCtrl.SetWatermarkBitmap(bm, 140);
		m_wndRecordsReportCtrl.SetWatermarkAlignment(xtpReportWatermarkRight | xtpReportWatermarkBottom);
	}	


	// Set control resizing.
	SetResize(IDOK, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_CJ_LINE, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_HELP_BUTTON, XTP_ANCHOR_BOTTOMLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_ACTIONS_BUTTON, XTP_ANCHOR_BOTTOMRIGHT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_TABLES_LIST, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMLEFT);
	SetResize(IDC_RECORDS_REPORT, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_BOTTOMRIGHT);
	SetResize(IDC_DESCR_TEXT, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);

	// Set controls theme
	m_btnExitApp.SetTheme(xtpControlThemeOffice2000);
	m_btnExitApp.SetUseVisualStyle(TRUE);

	m_btnActions.SetTheme(xtpControlThemeOffice2000);
	m_btnActions.SetUseVisualStyle(TRUE);
	m_btnActions.SetPushButtonStyle(xtpButtonDropDown);

	m_btnHelp.SetBitmap(CSize(16, 14), IDB_HELP);
	m_btnHelp.SetUseVisualStyle(TRUE);
	m_btnHelp.SetTheme(xtpControlThemeOffice2000);

	// define style attributes for the report control
	m_wndRecordsReportCtrl.FocusSubItems(TRUE);
	m_wndRecordsReportCtrl.AllowEdit(TRUE);


	// Construct connection string for sample database
	TCHAR szCurDir[_MAX_PATH];
	::GetCurrentDirectory(_MAX_PATH, szCurDir);
	CString strDatabasePath(szCurDir);
	strDatabasePath += _T("\\");
	strDatabasePath += LoadStringFromResources(IDS_DATABASE_NAME);

	CString strConnectionString(_T(""));
	strConnectionString.Format(IDS_CONNECTION_STRING, strDatabasePath);

	// Try to open the sample database
	if (OpenDatabase(strConnectionString))
		m_strConnectionString = strConnectionString;
	else
		AfxMessageBox(_T("Please create sample database to run CreateSampleDB.vbs script"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSampleDlg::OnPaint() 
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
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnHelpButton() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

BOOL CSampleDlg::OpenDatabase(CString strConnection)
{
	BOOL bResult = FALSE;
	HRESULT hr = S_OK;
	_RecordsetPtr pTablesList = NULL;
	CString strTableName(_T(""));

	if (strConnection.IsEmpty())
		return bResult;

	// Clear current content of the tables listbox
	m_wndTablesListCtrl.ResetContent();

	_bstr_t bstrConnectionString(strConnection.GetBuffer(_MAX_PATH));
	
	strConnection.ReleaseBuffer();

	try
	{
		// Create connection to sample database

		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		_com_util::CheckError(hr);

		hr = m_pConnection->Open(_bstr_t(bstrConnectionString), _bstr_t(_T("")), _bstr_t(_T("")), 0);
		_com_util::CheckError(hr);

		// Open schema of the database

		hr = m_pConnection->raw_OpenSchema(adSchemaTables, vtMissing, vtMissing, &pTablesList);
		_com_util::CheckError(hr);

		VARIANT_BOOL bEof;
		hr = pTablesList->get_bEOF(&bEof);
		_com_util::CheckError(hr);

		// Find field with table's name and add it to the tables listbox

		while (!bEof)
		{
			FieldsPtr pFields = NULL;
			hr = pTablesList->get_Fields(&pFields);
			_com_util::CheckError(hr);

			if (pFields == NULL)
				break;

			FieldPtr pField = NULL;
			hr = pFields->get_Item(_variant_t(_bstr_t(_T("TABLE_TYPE"))), &pField);
			_com_util::CheckError(hr);

			if (pField == NULL)
				break;

			VARIANT vtValue;
			hr = pField->get_Value(&vtValue);
			_com_util::CheckError(hr);

			if (_wcsicmp(vtValue.bstrVal, L"TABLE") == 0)
			{
				hr = pFields->get_Item(_variant_t(_bstr_t(_T("TABLE_NAME"))), &pField);
				_com_util::CheckError(hr);

				if (pField == NULL)
					break;

				hr = pField->get_Value(&vtValue);
				_com_util::CheckError(hr);

				m_wndTablesListCtrl.AddString(_bstr_t(vtValue.bstrVal));

				if (strTableName.IsEmpty())
					strTableName = vtValue.bstrVal;
			}
			hr = pTablesList->MoveNext();
			_com_util::CheckError(hr);

			hr = pTablesList->get_bEOF(&bEof);
		}

		hr = pTablesList->Close();
		_com_util::CheckError(hr);

		if (m_wndTablesListCtrl.GetCount() > 0)
		{
			m_wndTablesListCtrl.SetCurSel(0);
			m_wndTablesListCtrl.GetText(m_wndTablesListCtrl.GetCurSel(), strTableName);
			bResult = ShowRecords(strTableName);
		}

		bResult = TRUE;
	}
	catch (_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
		bResult = FALSE;
	}
	catch (...)
	{
		bResult = FALSE;
	}

	return bResult;
}

BOOL CSampleDlg::ShowRecords(CString strTableName)
{
	BOOL bResult = FALSE;
	HRESULT hr = S_OK;

	try
	{
		hr = m_pRecordset.CreateInstance(__uuidof(Recordset));
		_com_util::CheckError(hr);

		hr = m_pRecordset->put_CursorLocation(adUseClient);
		_com_util::CheckError(hr);

		hr = m_pRecordset->Open(_bstr_t(strTableName),_variant_t((IDispatch *)m_pConnection, true), adOpenDynamic, adLockBatchOptimistic, adCmdTable);
		_com_util::CheckError(hr);

		m_wndRecordsReportCtrl.GetDataManager()->SetDataSource(m_pRecordset);

		if (!m_wndRecordsReportCtrl.GetDataManager()->DataBind())
			_com_util::CheckError(E_FAIL);
	}
	catch (_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
	}
	catch (...)
	{
	}

	m_wndRecordsReportCtrl.GetPaintManager()->SetHeaderRowsDividerStyle(xtpReportFixedRowsDividerOutlook);
	m_wndRecordsReportCtrl.GetHeaderRecords()->RemoveAll();
	m_wndRecordsReportCtrl.ShowHeaderRows();
	m_wndRecordsReportCtrl.HeaderRowsAllowEdit(TRUE);
	m_wndRecordsReportCtrl.PopulateHeaderRows();

	return bResult;
}

void CSampleDlg::OnSelchangeTablesList() 
{
	BOOL bResult = FALSE;
	CString strTableName(_T(""));

	if (m_wndTablesListCtrl.GetCount() > 0)
	{
		m_wndTablesListCtrl.GetText(m_wndTablesListCtrl.GetCurSel(), strTableName);
		bResult = ShowRecords(strTableName);
	}
}

void CSampleDlg::OnValueChanged(NMHDR * pNotifyStruct, LRESULT*)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify)
		return;
	
	if (pItemNotify->pRow->GetType() == xtpRowTypeHeader)
	{
		if (pItemNotify->pItem)
		{
		}
	}
	else if (pItemNotify->pItem && pItemNotify->pItem->GetRecord())
		m_wndRecordsReportCtrl.GetDataManager()->UpdateRecord(pItemNotify->pItem->GetRecord());
}

void CSampleDlg::OnButtonDropDown()
{
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_MENU);

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	BOOL bDropDown = TRUE;

	DWORD dwStyle = m_btnActions.GetPushButtonStyle();
	ASSERT(m_btnActions.IsDropDownStyle());
	bDropDown = !(dwStyle == xtpButtonDropDownRight);

	CXTPWindowRect rect(m_btnActions.GetSafeHwnd());

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON /*| TPM_VERTICAL | TPM_RETURNCMD*/,
		!bDropDown ? rect.right : rect.left, !bDropDown ? rect.top : rect.bottom, this);

	menu.DestroyMenu();
}

BOOL CSampleDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN &&
		(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB))
		return FALSE;

	return CDialog::PreTranslateMessage(pMsg);
}

void CSampleDlg::OnUpdateDeleteRecords(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecordset != NULL &&
		           m_wndRecordsReportCtrl.GetSelectedRows() &&
				   m_wndRecordsReportCtrl.GetSelectedRows()->GetCount() > 0);
}

void CSampleDlg::OnUpdateDeleteRecordsFromRecordset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecordset != NULL &&
		           m_wndRecordsReportCtrl.GetSelectedRows() &&
				   m_wndRecordsReportCtrl.GetSelectedRows()->GetCount() > 0);
}

void CSampleDlg::OnUpdateAddRecords(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecordset != NULL);
}

void CSampleDlg::OnUpdateAddRecordsToRecordset(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pRecordset != NULL);
}

void CSampleDlg::OnAddRecords() 
{
	m_wndRecordsReportCtrl.AddNewRecord();
}

void CSampleDlg::OnAddRecordsToRecordset() 
{
	// This function demonstrates the automatic report control update on new record insertion into the recordset.
	// Upon record insertion, the data manager receives an event and inserts a record into the report control,
	// binding it to the recordset record.
	try
	{
		HRESULT hr = S_OK;
		
		if (m_pRecordset == NULL)
			return;
		
		// create new record
		CXTPReportRecord* pRecord = NULL;
		
		if (FAILED(hr = m_wndRecordsReportCtrl.GetDataManager()->CreateEmptyRecord(&pRecord)) || !pRecord)
			return;
		
		// add record without field list
		if (FAILED(hr = m_pRecordset->AddNew()))
			return;
		
		// update fields
		FieldsPtr pFields;
		
		if(FAILED(hr = m_pRecordset->get_Fields(&pFields)) || pFields == NULL)
			return;
		
		long lFields;
		
		if (FAILED(hr = pFields->get_Count(&lFields)) || lFields == 0)
			return;
		
		VARIANT vtIdx;
		vtIdx.vt = VT_I4;
		int i;
		for (i = 0; i < lFields; i++)
		{
			vtIdx.lVal = i;
			FieldPtr pField;
			if (FAILED(hr = pFields->get_Item(vtIdx, &pField)) || pField == NULL)
				break;
			
			long lAttrs;
			
			if (FAILED(hr = pField->get_Attributes(&lAttrs)))
				break;
			
			CXTPReportRecordItemVariant* pItem = (CXTPReportRecordItemVariant*)pRecord->GetItem(i);
			
			if (!pItem)
				break;
			
			VARIANT vtValue = pItem->GetValue();
			
			if (vtValue.vt == VT_BSTR)
			{
				CString strValue = _T("New Record");
				COleVariant vtBstrValue(strValue);
				hr = pField->put_Value(vtBstrValue);
			}
		}
		if (FAILED(hr) || i < lFields)
		{
			m_pRecordset->CancelUpdate();
			return;
		}

		if (FAILED(hr = m_pRecordset->Update()))
			hr = m_pRecordset->CancelUpdate();

		pRecord->InternalRelease();
	}
	catch(_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
		m_pRecordset->CancelUpdate();
	}
}

void CSampleDlg::OnDeleteRecords() 
{
	// This function demonstrates how to delete records from the report control.

	m_wndRecordsReportCtrl.DeleteSelectedRows();
}

void CSampleDlg::OnDeleteRecordsFromRecordset() 
{
	// This function demonstrates the automatic report control update on record deletion from the recordset.
	// Upon record deletion, the data manager receives an event and deletes a record from the report control.

	HRESULT hr = S_OK;

	if (m_pRecordset == NULL)
		return;

	CXTPReportSelectedRows* pSelectedRows = m_wndRecordsReportCtrl.GetSelectedRows();
	
	if (!pSelectedRows)
		return;
	int nRow = pSelectedRows->GetCount() - 1;
	
	if (nRow < 0)
		return;
	CWaitCursor wc;
	CXTPReportRow* pFocusedRow = pSelectedRows->GetAt(pSelectedRows->GetCount() - 1);
	pFocusedRow = m_wndRecordsReportCtrl.GetRows()->GetAt(pFocusedRow->GetIndex() + 1);
	while (nRow >= 0)
	{
		CXTPReportRecord* pRecord = pSelectedRows->GetAt(nRow--)->GetRecord();
		
		if (pRecord)
		{
			// get data source record bookmark
			VARIANT vtBookmark = pRecord->GetBookmark();
			
			if (vtBookmark.vt != VT_EMPTY)
			{
				// move to specified record
				if (SUCCEEDED(hr = m_pRecordset->put_Bookmark(vtBookmark)))
				{
					// delete record
					if (FAILED(hr = m_pRecordset->Delete(adAffectCurrent)))
						m_pRecordset->CancelUpdate();
				}
			}
		}

		if(nRow >= pSelectedRows->GetCount())
			nRow = pSelectedRows->GetCount() - 1;
	}
	m_wndRecordsReportCtrl.SetFocusedRow(pFocusedRow ? pFocusedRow : m_wndRecordsReportCtrl.GetFocusedRow());
}

void CSampleDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	CPopupMenuInit::Init(this, pPopupMenu, TRUE);
}

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

BOOL CRecordsReportControl::AddNewRecord()
{
	CXTPReportRecord* pRecord = NULL;
	
	if (FAILED(GetDataManager()->CreateEmptyRecord(&pRecord)) || !pRecord)
		return FALSE;
	
	for (int i = 0; i < pRecord->GetItemCount(); i++)
	{
		VARIANT vtValue = ((CXTPReportRecordItemVariant*)pRecord->GetItem(i))->GetValue();
		if (vtValue.vt == VT_BSTR)
		{
			//CString strValue = _T("New Record");
			COleVariant vtBstrValue(_bstr_t((_T("New Record"))));
			((CXTPReportRecordItemVariant*)pRecord->GetItem(i))->SetValue(vtBstrValue);
		}
	}
	
	if (FAILED(GetDataManager()->AddRecord(pRecord, TRUE)))
	{
		pRecord->InternalRelease();
		return FALSE;
	}

	return TRUE;
}

void CRecordsReportControl::DeleteSelectedRows()
{
	CXTPReportSelectedRows* pSelectedRows = GetSelectedRows();
	
	if (!pSelectedRows)
		return;
	
	int nRow = pSelectedRows->GetCount() - 1;
	
	if (nRow < 0)
		return;
	
	CWaitCursor wc;
	
	CXTPReportRow* pFocusedRow = pSelectedRows->GetAt(pSelectedRows->GetCount() - 1);
	
	pFocusedRow = GetRows()->GetAt(pFocusedRow->GetIndex() + 1);
	
	while (nRow >= 0)
	{
		CXTPReportRecord* pRecord = pSelectedRows->GetAt(nRow--)->GetRecord();
		if (pRecord)
			GetDataManager()->DeleteRecord(pRecord);
		if (nRow >= pSelectedRows->GetCount())
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

void CSampleDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_MENU);

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	ClientToScreen(&point);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CSampleDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	try
	{
		if (m_pConnection)
			m_pConnection->Close();
	}
	catch(_com_error &e)
	{
		UNREFERENCED_PARAMETER(e);
	}
	
}
