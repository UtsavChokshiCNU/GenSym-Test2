// SearchOptions.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Grep.h"
#include "SearchOptions.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CSearchBrowseButton::Initialize(CComboBox* pParentWnd, DWORD dwBStyle, UINT nMenu, int nSubMenuIndx)
{
	m_nMenu = nMenu;
	m_nSubMenuIndx = nSubMenuIndx;
	m_dwBStyle = dwBStyle;


	m_pComboBox = pParentWnd;
}

void CSearchBrowseButton::OnClicked()
{
	static BOOL m_bExecute = FALSE;
	if (m_bExecute)
		return;
	m_bExecute = TRUE;

	if (m_dwBStyle == BES_XTP_CHOOSEFILE)
	{
		CString strFilter = _T("XML Document (*.xml)|*.xml|All files (*.*)|*.*||");
		
		CFileDialog fd(TRUE, _T("xml"), NULL, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, strFilter);
		if (fd.DoModal() == IDOK)
		{
			m_pComboBox->SetWindowText(fd.GetPathName());
			m_pComboBox->GetParent()->SendMessage(WM_COMMAND,
				(WPARAM)MAKELONG(::GetDlgCtrlID(m_pComboBox->GetSafeHwnd()), CBN_EDITCHANGE),
				(LPARAM)m_pComboBox->GetSafeHwnd());
		}


		m_bExecute = FALSE;
		return;
	}
	if (m_dwBStyle == BES_XTP_CHOOSEDIR)
	{
		CString strPath;
		m_pComboBox->GetWindowText(strPath);

		// Instantiate a browse for folder dialog object
		CXTPBrowseDialog browseDlg;
		browseDlg.SetOwner(GetParent()->GetSafeHwnd());
		browseDlg.SetSelPath((TCHAR*)(LPCTSTR)strPath);

		if( browseDlg.DoModal() == IDOK ) {
			m_pComboBox->SetWindowText( browseDlg.GetSelPath() );
			m_pComboBox->GetParent()->SendMessage(WM_COMMAND,
				(WPARAM)MAKELONG(::GetDlgCtrlID(m_pComboBox->GetSafeHwnd()), CBN_EDITCHANGE),
				(LPARAM)m_pComboBox->GetSafeHwnd());
		}

		m_bExecute = FALSE;
		return;
	}

	SetState(TRUE);

	CRect rect;
	GetWindowRect(&rect);

	// loading a user resource.
	CMenu menu;
	menu.LoadMenu(m_nMenu);

	CMenu* pPopup = menu.GetSubMenu(m_nSubMenuIndx);
	ASSERT(pPopup != NULL);

	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	int nCmd = XTPContextMenu(pPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL |TPM_RETURNCMD,
		rect.right, rect.top, pWndPopupOwner, 0 );

	if (nCmd > 0)
	{
		CString str;
		str.LoadString(nCmd);

		CString strPrev;
		m_pComboBox->GetWindowText(strPrev);
		m_pComboBox->SetWindowText(strPrev + str);

		m_pComboBox->GetParent()->SendMessage(WM_COMMAND,
			(WPARAM)MAKELONG(::GetDlgCtrlID(m_pComboBox->GetSafeHwnd()), CBN_EDITCHANGE),
			(LPARAM)m_pComboBox->GetSafeHwnd());
	}

	// Return the button state to normal.
	SetState(FALSE);

	m_bExecute = FALSE;
};
/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsView

IMPLEMENT_DYNCREATE(CSearchOptionsView, CXTPResizeFormView)

CSearchOptions::CSearchOptions()
{
	m_bIncludeSubFolders = TRUE;
	m_bRegularExpressions = TRUE;
	m_bMatchCase = FALSE;
	m_bMatchWholeWords = FALSE;
	m_bFindInHiddenFiles = FALSE;

	m_strFind = _T("");
	m_strReplace = _T("");
	m_strPath = _T("");
	m_strFileTypes = _T("*.*");

	m_strBatchFile = _T("");
	m_bBatchMode = FALSE;

	pRegExp = 0;
}

void ExchangeList(CXTPPropExchange* pPX,  LPCTSTR pszPropName, CStringList& lst)
{
	CXTPPropExchangeSection secItems(pPX->GetSection(pszPropName));
	CString str, strSection;

	if (pPX->IsStoring())
	{
		DWORD dwCount = (DWORD)lst.GetCount();
		secItems->WriteCount(dwCount);
		
		POSITION pos = lst.GetHeadPosition();
		int i = 0;
		while (pos)
		{
			str = lst.GetNext(pos);				
			strSection.Format(_T("Item%i"), i++);
			PX_String(&secItems, strSection, str, _T(""));
			
		}	
	}
	else
	{
		DWORD nNewCount = secItems->ReadCount();
		for (DWORD i = 0; i < nNewCount; i++)
		{
			strSection.Format(_T("Item%i"), i);

			PX_String(&secItems, strSection, str, _T(""));
			lst.AddTail(str);
		}
	}
	
}

void CSearchOptions::DoPropExchange(CXTPPropExchange* pPX)
{
	pPX->ExchangeSchema();

	PX_Bool(pPX, _T("MatchCase"), m_bMatchCase, FALSE);
	PX_Bool(pPX, _T("MatchWholeWords"), m_bMatchWholeWords, FALSE);
	PX_Bool(pPX, _T("RegularExpressions"), m_bRegularExpressions, TRUE);
	PX_Bool(pPX, _T("IncludeSubFolders"), m_bIncludeSubFolders, TRUE);
	PX_Bool(pPX, _T("FindInHiddenFiles"), m_bFindInHiddenFiles, TRUE);

	PX_String(pPX, _T("FindString"), m_strFind, _T(""));
	PX_String(pPX, _T("ReplaceString"), m_strReplace, _T(""));
	PX_String(pPX, _T("Path"), m_strPath, _T(""));
	PX_String(pPX, _T("FileTypes"), m_strFileTypes, _T("*.*"));

	PX_String(pPX, _T("BatchFile"), m_strBatchFile, _T(""));
	PX_Bool(pPX, _T("BatchMode"), m_bBatchMode, FALSE);

	ExchangeList(pPX, _T("FileTypesHistory"),m_lstFileTypesHistory);
	ExchangeList(pPX, _T("ReplaceHistory"),m_lstReplaceHistory);
	ExchangeList(pPX, _T("FindHistory"),m_lstFindHistory);
	ExchangeList(pPX, _T("PathHistory"),m_lstPathHistory);
}

CSearchOptions* GetSearchOptions()
{
	static CSearchOptions options;
	return &options;
}



CSearchOptionsView::CSearchOptionsView()
	: CXTPResizeFormView(CSearchOptionsView::IDD)
{
	//{{AFX_DATA_INIT(CSearchOptionsView)
	//}}AFX_DATA_INIT

	m_bSearchMode = FALSE;
	m_bInitialized = FALSE;
}

CSearchOptionsView::~CSearchOptionsView()
{
}

void CSearchOptionsView::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchOptionsView)
	DDX_Control(pDX, IDC_COMBO_REPLACE, m_cmbReplace);
	DDX_Control(pDX, IDC_COMBO_PATH, m_cmbPath);
	DDX_Control(pDX, IDC_COMBO_FIND, m_cmbFind);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbFileTypes);
	DDX_Control(pDX, IDC_BUTTON_REPLACE_EXPAND, m_btnReplaceExpand);
	DDX_Control(pDX, IDC_BUTTON_FIND_EXPAND, m_btnFindExpand);
	DDX_Control(pDX, IDC_BUTTON_PATH_EXPAND, m_btnPathExpand);
	DDX_Control(pDX, IDC_GROUP_FINDOPTIONS, m_wndGroupFindOptions);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_EDIT_BATCH, m_cmbFile);
	DDX_Control(pDX, IDC_BUTTON_BATCH_EXPAND, m_btnFileExpand);

	DDX_CBString(pDX, IDC_EDIT_BATCH, GetSearchOptions()->m_strBatchFile);

	DDX_CBString(pDX, IDC_COMBO_FIND, GetSearchOptions()->m_strFind);
	DDX_CBString(pDX, IDC_COMBO_REPLACE, GetSearchOptions()->m_strReplace);
	DDX_CBString(pDX, IDC_COMBO_PATH, GetSearchOptions()->m_strPath);
	DDX_Check(pDX, IDC_CHECK_INCLUDE_SUBFOLDERS, GetSearchOptions()->m_bIncludeSubFolders);
	DDX_Check(pDX, IDC_CHECK_REGULAR, GetSearchOptions()->m_bRegularExpressions);
	DDX_Check(pDX, IDC_CHECK_MATCH_CASE, GetSearchOptions()->m_bMatchCase);
	DDX_Check(pDX, IDC_CHECK_HIDDEN, GetSearchOptions()->m_bFindInHiddenFiles);
	DDX_Check(pDX, IDC_CHECK_MATCH_WHOLE_WORDS, GetSearchOptions()->m_bMatchWholeWords);
	DDX_CBString(pDX, IDC_COMBO_TYPE, GetSearchOptions()->m_strFileTypes);
}


BEGIN_MESSAGE_MAP(CSearchOptionsView, CXTPResizeFormView)
	//{{AFX_MSG_MAP(CSearchOptionsView)
	ON_BN_CLICKED(IDC_BUTTON_FINDALL, OnButtonFindAll)
	ON_BN_CLICKED(IDC_BUTTON_REPLACEALL, OnButtonReplaceAll)
	ON_CBN_EDITCHANGE(IDC_COMBO_FIND, UpdateOptions)
	ON_CBN_EDITCHANGE(IDC_COMBO_PATH, UpdateOptions)
	ON_CBN_EDITCHANGE(IDC_COMBO_REPLACE, UpdateOptions)
	ON_CBN_EDITCHANGE(IDC_EDIT_BATCH, UpdateOptions)
	ON_BN_CLICKED(IDC_CHECK_REGULAR, UpdateOptions)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_TOOLBAR_REPLACEINFILES, ID_TOOLBAR_BATCH, OnToolbarButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsView diagnostics

#ifdef _DEBUG
void CSearchOptionsView::AssertValid() const
{
	CXTPResizeFormView::AssertValid();
}

void CSearchOptionsView::Dump(CDumpContext& dc) const
{
	CXTPResizeFormView::Dump(dc);
}
#endif //_DEBUG


void RestoryCombo(CComboBox& cmb, CStringList& lstHistory, LPCTSTR lpszDefault = 0)
{
	if (lstHistory.GetCount() > 0)
	{
		POSITION pos = lstHistory.GetHeadPosition();
		while (pos)
		{
			cmb.AddString(lstHistory.GetNext(pos));
		}

	}
	else if (lpszDefault)
	{
		cmb.AddString(lpszDefault);
		lstHistory.AddTail(lpszDefault);
	}

}
/////////////////////////////////////////////////////////////////////////////
// CSearchOptionsView message handlers

void CSearchOptionsView::OnInitialUpdate()
{
	CXTPResizeFormView::OnInitialUpdate();

	SetScaleToFitSize(CSize(90, 1));

	if (m_bInitialized)
		return;


	VERIFY(m_wndToolBar.CreateToolBar(WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	CXTPControl* pControl = m_wndToolBar.GetControls()->Add(xtpControlButton, ID_TOOLBAR_REPLACEINFILES);
	pControl->SetChecked(TRUE);
	pControl = m_wndToolBar.GetControls()->Add(xtpControlButton, ID_TOOLBAR_BATCH);
	pControl->SetBeginGroup(TRUE);

	SetResize(IDC_STATIC_FIND, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_COMBO_FIND, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_FIND_EXPAND, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_STATIC_BATCH, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_EDIT_BATCH, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_BATCH_EXPAND, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_STATIC_REPLACE, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_COMBO_REPLACE, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_REPLACE_EXPAND, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_STATIC_PATH, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_COMBO_PATH, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_PATH_EXPAND, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_COMBO_TYPE, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_GROUP_FINDOPTIONS, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_FINDALL, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_BUTTON_REPLACEALL, XTP_ANCHOR_TOPRIGHT, XTP_ANCHOR_TOPRIGHT);

	SetResize(IDC_CHECK_INCLUDE_SUBFOLDERS, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_MATCH_CASE, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_MATCH_WHOLE_WORDS, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_HIDDEN, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_CHECK_REGULAR, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);
	SetResize(IDC_STATIC_LOOK, XTP_ANCHOR_TOPLEFT, XTP_ANCHOR_TOPRIGHT);

	m_bInitialized = TRUE;

	m_btnFindExpand.SetBrowseStyle(BES_XTP_POPUPMENU);
	m_btnFindExpand.Initialize(&m_cmbFind, BES_XTP_POPUPMENU, IDR_SEARCH_POPUP, 0);

	m_btnReplaceExpand.SetBrowseStyle(BES_XTP_POPUPMENU);
	m_btnReplaceExpand.Initialize(&m_cmbReplace, BES_XTP_POPUPMENU, IDR_SEARCH_POPUP, 1);

	m_btnPathExpand.Initialize(&m_cmbPath, BES_XTP_CHOOSEDIR);

	m_btnFileExpand.Initialize(&m_cmbFile, BES_XTP_CHOOSEFILE);

	if (GetSearchOptions()->m_bBatchMode)
	{
		OnToolbarButton(ID_TOOLBAR_BATCH);
	}

	UpdateOptions();


	IRegExpPtr regExp;
	HRESULT hr = regExp.CreateInstance(__uuidof(RegExp));
	if (FAILED(hr))
	{
		GetDlgItem(IDC_CHECK_REGULAR)->EnableWindow(FALSE);

		GetSearchOptions()->m_bRegularExpressions = FALSE;
		UpdateData(FALSE);
	}

	RestoryCombo(m_cmbFileTypes, GetSearchOptions()->m_lstFileTypesHistory, _T("*.cpp;*.h"));
	RestoryCombo(m_cmbFind, GetSearchOptions()->m_lstFindHistory);
	RestoryCombo(m_cmbReplace, GetSearchOptions()->m_lstReplaceHistory);
	RestoryCombo(m_cmbPath, GetSearchOptions()->m_lstPathHistory);


}

BOOL CSearchOptionsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CXTPResizeFormView::PreCreateWindow(cs);
}

void CSearchOptionsView::OnButtonFindAll()
{
	UpdateData();

	if (m_bSearchMode)
	{
		((CMainFrame*)AfxGetMainWnd())->OnCancelFind();
	}
	else
	{
		((CMainFrame*)AfxGetMainWnd())->OnFindAll();
	}
}

BOOL CSearchOptionsView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
	{
		if ((::GetFocus() == m_hWnd) || (::GetParent(::GetFocus()) == m_hWnd) || (::GetParent(::GetParent(::GetFocus())) == m_hWnd))
		{
			if (IsDialogMessage(pMsg))
				return TRUE;
		}
	}

	return CXTPResizeFormView::PreTranslateMessage(pMsg);
}

void CSearchOptionsView::UpdateOptions()
{
	UpdateData();

	CSearchOptions* pOptions = GetSearchOptions();

	if (pOptions->m_bBatchMode)
	{
		GetDlgItem(IDC_BUTTON_FINDALL)->EnableWindow(!pOptions->m_strBatchFile.IsEmpty());
		
		GetDlgItem(IDC_CHECK_MATCH_WHOLE_WORDS)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FINDALL)->EnableWindow(!pOptions->m_strFind.IsEmpty() && !pOptions->m_strPath.IsEmpty());
		
		GetDlgItem(IDC_CHECK_MATCH_WHOLE_WORDS)->EnableWindow(!pOptions->m_bRegularExpressions);
	}
	
	GetDlgItem(IDC_BUTTON_REPLACEALL)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_FIND_EXPAND)->EnableWindow(pOptions->m_bRegularExpressions);
	GetDlgItem(IDC_BUTTON_REPLACE_EXPAND)->EnableWindow(pOptions->m_bRegularExpressions);

	GetDlgItem(IDC_CHECK_REGULAR)->EnableWindow(!pOptions->m_bBatchMode);

}

void CSearchOptionsView::SetSearchMode(BOOL bSearchMode)
{
	CWnd* pWnd = GetWindow(GW_CHILD);
	while (pWnd)
	{
		pWnd->EnableWindow(!bSearchMode);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
	GetDlgItem(IDC_BUTTON_FINDALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FINDALL)->SetWindowText(bSearchMode ? _T("Cancel") : _T("&Find All"));

	if (!bSearchMode)
	{
		UpdateOptions();
	}

	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE|RDW_UPDATENOW);

	m_bSearchMode = bSearchMode;
}

void CSearchOptionsView::OnButtonReplaceAll()
{
	((CMainFrame*)AfxGetMainWnd())->OnReplaceAll();
}

void CSearchOptionsView::OnSize(UINT nType, int cx, int cy)
{
	CXTPResizeFormView::OnSize(nType, cx, cy);

	if (m_wndToolBar.GetSafeHwnd())
	{
		CSize sz = m_wndToolBar.CalcDockingLayout(cx, LM_HIDEWRAP| LM_HORZDOCK|LM_HORZ | LM_COMMIT);
		
		m_wndToolBar.MoveWindow(0, 0, cx, sz.cy);
		m_wndToolBar.Invalidate(FALSE);
	}

}

void CSearchOptionsView::OnToolbarButton(UINT nCmd)
{
	BOOL bBatchMode = ((int)nCmd == ID_TOOLBAR_BATCH);

	for (int i = 0; i < m_wndToolBar.GetControlCount(); i++)
	{
		m_wndToolBar.GetControl(i)->SetChecked(m_wndToolBar.GetControl(i)->GetID() == (int)nCmd);
	}

	GetSearchOptions()->m_bBatchMode = bBatchMode;


	GetDlgItem(IDC_COMBO_REPLACE)->ShowWindow(!bBatchMode);
	GetDlgItem(IDC_BUTTON_REPLACE_EXPAND)->ShowWindow(!bBatchMode);
	GetDlgItem(IDC_STATIC_REPLACE)->ShowWindow(!bBatchMode);

	GetDlgItem(IDC_COMBO_FIND)->ShowWindow(!bBatchMode);
	GetDlgItem(IDC_BUTTON_FIND_EXPAND)->ShowWindow(!bBatchMode);
	GetDlgItem(IDC_STATIC_FIND)->ShowWindow(!bBatchMode);

	GetDlgItem(IDC_EDIT_BATCH)->ShowWindow(bBatchMode);
	GetDlgItem(IDC_BUTTON_BATCH_EXPAND)->ShowWindow(bBatchMode);
	GetDlgItem(IDC_STATIC_BATCH)->ShowWindow(bBatchMode);


	if (bBatchMode)
	{
		GetSearchOptions()->m_bMatchCase = TRUE;
		GetSearchOptions()->m_bMatchWholeWords = TRUE;
		GetSearchOptions()->m_bRegularExpressions = FALSE;
		UpdateData(FALSE);
	}

	UpdateOptions();
}
