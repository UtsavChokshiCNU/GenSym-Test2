// pagesearch.cpp : implementation file
//

#include "stdafx.h"
#include "styler.h"
#include "pagesearch.h"
#include "MainFrm.h"
#include "ComboBoxSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPageSearch::CEngineArray CPageSearch::m_arrEngines;

/////////////////////////////////////////////////////////////////////////////
// CPageSearch property page

IMPLEMENT_DYNCREATE(CPageSearch, COptionsPage)

CPageSearch::CPageSearch() : COptionsPage(CPageSearch::IDD)
{
	//{{AFX_DATA_INIT(CPageSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSearch::~CPageSearch()
{
}

void CPageSearch::DoDataExchange(CDataExchange* pDX)
{
	COptionsPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSearch)
	DDX_Control(pDX, IDC_LIST_SEARCH, m_wndSearch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSearch, COptionsPage)
	//{{AFX_MSG_MAP(CPageSearch)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SEARCH, OnDblclkListSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSearch message handlers

void CPageSearch::Load()
{
	CString strPath = GetModuleDir();
			
	TCHAR chReturn[255];
	CString strSearch;
	int nIndex = 0;
	
	strSearch.Format(_T("S%i"), nIndex);
	while (GetPrivateProfileString(_T("QuickSearch"), strSearch, _T(""), chReturn, 254, strPath + _T("QuickSearch.ini")) > 0)
	{
		ENGINE engine;
		engine.strSearch  = chReturn;
		
		strSearch.Format(_T("N%i"), nIndex);
		if (GetPrivateProfileString(_T("QuickSearch"), strSearch, _T(""), chReturn, 254, strPath + _T("QuickSearch.ini")) > 0)
			engine.strKeyword = chReturn;

		strSearch.Format(_T("T%i"), nIndex);
		if (GetPrivateProfileString(_T("QuickSearch"), strSearch, _T(""), chReturn, 254, strPath + _T("QuickSearch.ini")) > 0)
			engine.strTitle = chReturn; else engine.strTitle = engine.strKeyword;

		if (!engine.strSearch.IsEmpty() && !engine.strTitle.IsEmpty())
		{
			m_arrEngines.Add(engine);
		}
		
		strSearch.Format(_T("S%i"), ++nIndex);
	}



}

void CPageSearch::Save()
{
	CString strPath = GetModuleDir();
	
	CString str;
	if (PathFileExists(strPath + _T("QuickSearch.ini")))
		DeleteFile(strPath + _T("QuickSearch.ini"));

	for (int i = 0; i < m_arrEngines.GetSize(); i++)
	{
		ENGINE& engine = m_arrEngines[i];
		
		str.Format(_T("S%i"), i);
		WritePrivateProfileString(_T("QuickSearch"), str, engine.strSearch, strPath + _T("QuickSearch.ini"));

		str.Format(_T("N%i"), i);
		WritePrivateProfileString(_T("QuickSearch"), str, engine.strKeyword, strPath + _T("QuickSearch.ini"));

		str.Format(_T("T%i"), i);
		WritePrivateProfileString(_T("QuickSearch"), str, engine.strTitle, strPath + _T("QuickSearch.ini"));
	}


}

BOOL CPageSearch::OnInitDialog() 
{
	COptionsPage::OnInitDialog();
	
	m_wndSearch.SetExtendedStyle(m_wndSearch.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_wndSearch.InsertColumn(0, _T("Title"), LVCFMT_LEFT, 184);
	m_wndSearch.InsertColumn(1, _T("Keyword"), LVCFMT_LEFT, 150);

	RefreshList();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSearch::RefreshList()
{
	m_wndSearch.DeleteAllItems();
	for (int i = 0; i < m_arrEngines.GetSize(); i++)
	{
		ENGINE& engine = m_arrEngines[i];
		int nIndex = m_wndSearch.InsertItem(i, engine.strTitle);
		m_wndSearch.SetItemText(nIndex, 1, engine.strKeyword);
		m_wndSearch.SetItemData(nIndex, i);
	}

	CComboBoxSearch* pCombo = (CComboBoxSearch*) GetMainFrame()->GetCommandBars()->FindControl(xtpControlComboBox, ID_GOTO_SEARCH, FALSE, FALSE);
	ASSERT(pCombo);
	UpdateComboBox(pCombo);

}

void CPageSearch::OnButtonAdd() 
{
	ENGINE engine;
	CSearchDialog sd(engine);
	if (sd.DoModal() == IDOK)
	{
		if (sd.m_engine.strTitle != "" && sd.m_engine.strSearch != "")
		{
			m_arrEngines.Add(sd.m_engine);
			RefreshList();
		}				
	}	
}

void CPageSearch::OnButtonEdit() 
{
	int nItem = m_wndSearch.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1)
	{
		int dwData = (int)m_wndSearch.GetItemData(nItem);
		
		if (dwData >= 0 && dwData < m_arrEngines.GetSize())
		{
			ENGINE engine = m_arrEngines[dwData];
			CSearchDialog sd(engine);
			if (sd.DoModal() == IDOK)
			{
				if (sd.m_engine.strTitle != "" && sd.m_engine.strSearch != "")
				{
					m_arrEngines[dwData] = sd.m_engine;
					RefreshList();
				}				
			}	
		}
	}
	
}

void CPageSearch::OnButtonRemove() 
{
	int nItem = m_wndSearch.GetNextItem(-1, LVNI_SELECTED);
	if (nItem != -1)
	{
		int dwData = (int)m_wndSearch.GetItemData(nItem);
		
		if (dwData >= 0 && dwData < m_arrEngines.GetSize())
		{
			m_arrEngines.RemoveAt(dwData);
			RefreshList();
		}
	}
	
}

void CPageSearch::OnDblclkListSearch(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	OnButtonEdit();
	
	*pResult = 0;
}

void CPageSearch::UpdateComboBox(CComboBoxSearch *pCombo)
{
	pCombo->ResetContent();
	CString strText = pCombo->GetEditText();
	for (int i = 0; i < m_arrEngines.GetSize(); i++)
	{
		ENGINE& engine = m_arrEngines[i];
		pCombo->AddString(engine.strTitle);
	}
	pCombo->SetCurSel(pCombo->m_nCurrentEngine);
	if (!strText.IsEmpty()) pCombo->SetEditText(strText);

}

// SearchDialog

CSearchDialog::CSearchDialog(CPageSearch::ENGINE& engine, CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDialog::IDD, pParent)
{
	m_engine = engine;
}


void CSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDialog)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_TITLE, m_engine.strTitle);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_engine.strSearch);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, m_engine.strKeyword);
}

void CSearchDialog::OnOK()
{
	UpdateData();

	if(m_engine.strSearch.Find(_T("%s")) < 0)
	{
		AfxMessageBox(IDS_NEEDKEYSTRING);
		return;
	}

	CDialog::OnOK();

}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialog)
	//{{AFX_MSG_MAP(CSearchDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


