// TaskPageRadioButtons.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"
#include "TaskSheetProperties.h"
#include "TaskPageRadioButtons.h"
#include "TaskEditButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskPageRadioButtons property page

IMPLEMENT_DYNCREATE(CTaskPageRadioButtons, CPropertyPage)

CTaskPageRadioButtons::CTaskPageRadioButtons() : CPropertyPage(CTaskPageRadioButtons::IDD)
{
	//{{AFX_DATA_INIT(CTaskPageRadioButtons)
	m_bNoDefault = FALSE;
	//}}AFX_DATA_INIT
}

CTaskPageRadioButtons::~CTaskPageRadioButtons()
{
}

void CTaskPageRadioButtons::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskPageRadioButtons)
	DDX_Control(pDX, IDC_TXT_DEFAULT, m_txtDefault);
	DDX_Control(pDX, IDC_BTN_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST_CUSTOM, m_listCustom);
	DDX_Control(pDX, IDC_COMBO_DEFAULT, m_comboDefault);
	DDX_Check(pDX, IDC_CHK_NODEFAULT, m_bNoDefault);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskPageRadioButtons, CPropertyPage)
	//{{AFX_MSG_MAP(CTaskPageRadioButtons)
	ON_BN_CLICKED(IDC_CHK_NODEFAULT, OnChkNoDefault)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
	ON_CBN_SELENDOK(IDC_COMBO_DEFAULT, OnSelEndOkDefault)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CUSTOM, OnItemChangedListCustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskPageRadioButtons message handlers

void CTaskPageRadioButtons::OnChkNoDefault()
{
	UpdateData();
	m_comboDefault.EnableWindow(!m_bNoDefault);
	m_txtDefault.EnableWindow(!m_bNoDefault);
}

void CTaskPageRadioButtons::OnSelEndOkDefault()
{
	UpdateData();
}

void CTaskPageRadioButtons::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	CTaskEditButtonDlg dlg(&m_comboDefault, FALSE, m_pDlgParent);
	if (dlg.DoModal() == IDOK)
	{
		CString strID;
		strID.Format(_T("%d"), dlg.m_nID);
		int nIndex = m_listCustom.GetItemCount();
		m_listCustom.InsertItem(nIndex, dlg.m_strText);
		m_listCustom.SetItemText(nIndex, 1, strID);
	}
	m_listCustom.SetFocus();
}

void CTaskPageRadioButtons::OnBtnEdit() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listCustom.GetFirstSelectedItemPosition();
	if (pos)
	{
		CTaskEditButtonDlg dlg(&m_comboDefault, TRUE, m_pDlgParent);

		int nIndex = m_listCustom.GetNextSelectedItem(pos);
		dlg.m_strText = m_listCustom.GetItemText(nIndex, 0);
		dlg.m_nID = _ttoi(m_listCustom.GetItemText(nIndex, 1));

		if (dlg.DoModal() == IDOK)
		{
			CString strID;
			strID.Format(_T("%d"), dlg.m_nID);
			m_listCustom.SetItemText(nIndex, 0, dlg.m_strText);
			m_listCustom.SetItemText(nIndex, 1, strID);
		}
	}
	m_listCustom.SetFocus();
}

void CTaskPageRadioButtons::OnBtnRemove() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listCustom.GetFirstSelectedItemPosition();
	if (pos)
	{
		if (::MessageBox(m_hWnd, _T("Are you sure you want to delete this item?"),
			_T("Confirm Delete"), MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			int nIndex = m_listCustom.GetNextSelectedItem(pos);
			if (nIndex != LB_ERR)
			{
				int nID = _ttoi(m_listCustom.GetItemText(nIndex, 1));
				CString strText = m_listCustom.GetItemText(nIndex, 0);

				m_pDlgParent->UpdateButtonMap(
					strText, nID, &m_comboDefault, FALSE);

				m_listCustom.DeleteItem(nIndex);
			}
		}
	}
	m_listCustom.SetFocus();
}

void CTaskPageRadioButtons::OnItemChangedListCustom(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	EnableButtons();
	
	*pResult = 0;
}

void CTaskPageRadioButtons::InsertItem(CString strText, UINT nID)
{
	CString strID;
	strID.Format(_T("%d"), nID);

	int nIndex = m_listCustom.GetItemCount();
	m_listCustom.InsertItem(nIndex, strText);
	m_listCustom.SetItemText(nIndex, 1, strID);

	m_pDlgParent->UpdateButtonMap(
		strText, nID, &m_comboDefault, TRUE);
}

void CTaskPageRadioButtons::InsertItem(UINT nString, UINT nID)
{
	CString strText;
	strText.LoadString(nString);
	InsertItem(strText, nID);
}

BOOL CTaskPageRadioButtons::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	// TODO: Add extra initialization here
	m_pDlgParent = DYNAMIC_DOWNCAST(CTaskSheetProperties, GetParent());
	ASSERT_VALID(m_pDlgParent);

	m_listCustom.InsertColumn(0, _T("Text"),  LVCFMT_LEFT, 160);
	m_listCustom.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 60);

	ListView_SetExtendedListViewStyle(
		m_listCustom.m_hWnd, LVS_EX_FULLROWSELECT);

	//InsertItem(IDS_RB_GOOD, RB_GOOD);
	//InsertItem(IDS_RB_OK,   RB_OK);
	//InsertItem(IDS_RB_BAD,  RB_BAD);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTaskPageRadioButtons::OnSetActive()
{
	if (!CPropertyPage::OnSetActive())
		return FALSE;

	EnableButtons();

	return TRUE;
}

void CTaskPageRadioButtons::EnableButtons()
{
	if (::IsWindow(m_listCustom.m_hWnd))
	{
		BOOL bEnable = (m_listCustom.GetSelectedCount() > 0);
		m_btnEdit.EnableWindow(bEnable);
		m_btnRemove.EnableWindow(bEnable);
	}
}
