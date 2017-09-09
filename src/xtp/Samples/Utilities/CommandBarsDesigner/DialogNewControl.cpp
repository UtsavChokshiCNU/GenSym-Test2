// DialogNewControl.cpp : implementation file
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
#include "commandbarsdesigner.h"
#include "DialogNewControl.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogNewControl dialog


CDialogNewControl::CDialogNewControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNewControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogNewControl)
	m_strCaption = _T("");
	//}}AFX_DATA_INIT
	m_bGenerateId = TRUE;
}


void CDialogNewControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogNewControl)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_COMBO_ID, m_comboId);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_comboCategory);
	DDX_Control(pDX, IDC_COMBO_CLASS, m_comboClass);
	DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
	DDX_CBString(pDX, IDC_COMBO_CATEGORY, m_strCategory);
	DDX_CBString(pDX, IDC_COMBO_ID, m_strId);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strType);
	DDX_CBString(pDX, IDC_COMBO_CLASS, m_strClass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogNewControl, CDialog)
	//{{AFX_MSG_MAP(CDialogNewControl)
	ON_EN_CHANGE(IDC_EDIT_CAPTION, OnChangeEditCaption)
	ON_CBN_EDITCHANGE(IDC_COMBO_CATEGORY, OnEditchangeComboCategory)
	ON_CBN_SELCHANGE(IDC_COMBO_CATEGORY, OnSelchangeComboCategory)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_CBN_EDITCHANGE(IDC_COMBO_ID, OnEditchangeComboId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogNewControl message handlers

void CDialogNewControl::FillClassCombo()
{
/*
	CRuntimeClass* pClass;
	// search app specific classes
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();

	for (pClass = pModuleState->m_classList; pClass != NULL; pClass = pClass->m_pNextClass)
	{
		if (pClass->IsDerivedFrom(RUNTIME_CLASS(CXTPControl)))
		{
			m_comboClass.AddString(CString(pClass->m_lpszClassName));
			TRACE("m_comboClass.AddString(RUNTIMC_CLASS(%s));\n", CString(pClass->m_lpszClassName));
		}
	}

#ifdef _AFXDLL
	// search classes in shared DLLs
	for (CDynLinkLibrary* pDLL = pModuleState->m_libraryList; pDLL != NULL; pDLL = pDLL->m_pNextDLL)
	{
		for (pClass = pDLL->m_classList; pClass != NULL; pClass = pClass->m_pNextClass)
		{
			if (pClass->IsDerivedFrom(RUNTIME_CLASS(CXTPControl)))
			{
				m_comboClass.AddString(CString(pClass->m_lpszClassName));
				TRACE("m_comboClass.AddString(RUNTIMC_CLASS(%s));\n", CString(pClass->m_lpszClassName));
			}
			
		}
	}
#endif*/
	m_comboClass.AddString(_T("CXTPRibbonControlSystemRecentFileList"));
	m_comboClass.AddString(_T("CXTPRibbonControlSystemPopupBarListCaption"));
	m_comboClass.AddString(_T("CXTPRibbonControlSystemPopupBarListItem"));
	m_comboClass.AddString(_T("CXTPRibbonControlSystemPopupBarButton"));
	m_comboClass.AddString(_T("CXTPControlSlider"));
	m_comboClass.AddString(_T("CXTPControlScrollBar"));
	m_comboClass.AddString(_T("CXTPControlProgress"));
	m_comboClass.AddString(_T("CXTPControlColorSelector"));
	m_comboClass.AddString(_T("CXTPControlPopupColor"));
	m_comboClass.AddString(_T("CXTPControlPopup"));
	m_comboClass.AddString(_T("CXTPControlGallery"));
	m_comboClass.AddString(_T("CXTPControlHyperlink"));
	m_comboClass.AddString(_T("CXTPControlBitmap"));
	m_comboClass.AddString(_T("CXTPControlMarkupLabel"));
	m_comboClass.AddString(_T("CXTPControlRadioButton"));
	m_comboClass.AddString(_T("CXTPControlCheckBox"));
	m_comboClass.AddString(_T("CXTPControlLabel"));
	m_comboClass.AddString(_T("CXTPControlToolbars"));
	m_comboClass.AddString(_T("CXTPControlWindowList"));
	m_comboClass.AddString(_T("CXTPControlEdit"));
	m_comboClass.AddString(_T("CXTPControlFontComboBox"));
	m_comboClass.AddString(_T("CXTPControlComboBox"));
	m_comboClass.AddString(_T("CXTPControlButton"));
}


BOOL CDialogNewControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	CXTPControls* pControls = ((CMainFrame*)AfxGetMainWnd())->GetActiveEmbeddedFrame()->m_pControls;

	ASSERT(pControls);

	for (int i = 0; i < pControls->GetCount(); i++)
	{
		CXTPControl* pControl = pControls->GetAt(i);

		if (m_comboCategory.FindStringExact(0, pControl->GetCategory()) == CB_ERR)
		{
			m_comboCategory.AddString(pControl->GetCategory());
		}
	}

	for (int j = 1; j < _countof(lpTypes); j++)
	{
		if (lpTypes[j])
		{
			m_comboType.AddString(lpTypes[j]);
		}
	}
	m_comboType.AddString(_T("Custom"));

	m_comboType.SetCurSel(0);
	OnSelchangeComboType();
	
	FillClassCombo();


	CResourceManager* pResourceManager = ((CMainFrame*)AfxGetMainWnd())->GetActiveEmbeddedFrame()->ResourceManager();
	ASSERT(pResourceManager);

	CMapResources* pResources = pResourceManager->GetResources();

	POSITION pos = pResources->GetStartPosition();
	while (pos)
	{
		CResourceInfo* pInfo;
		CString strCaption;
		pResources->GetNextAssoc(pos, strCaption, (CObject*&)pInfo);

		m_comboId.AddString(strCaption);

	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogNewControl::GenerateID()
{
	if (m_bGenerateId)
	{
		CString strCaption = StripChars(m_strCaption);

		CString strCategory;
		m_comboCategory.GetWindowText(strCategory);
		strCategory = StripChars(strCategory);

		CString strId = _T("ID");

		if (!strCategory.IsEmpty()) strId += _T("_") + strCategory;
		if (!strCaption.IsEmpty()) strId += _T("_") + strCaption;

		m_comboId.SetWindowText(strId);
	}
}

void CDialogNewControl::OnChangeEditCaption()
{
	UpdateData();
	GenerateID();
}

void CDialogNewControl::OnEditchangeComboCategory()
{
	GenerateID();
}

void CDialogNewControl::OnSelchangeComboType()
{
	BOOL bCustom = m_comboType.GetCurSel() == m_comboType.GetCount() - 1;

	GetDlgItem(IDC_STATIC_CLASS)->ShowWindow(bCustom);
	GetDlgItem(IDC_COMBO_CLASS)->ShowWindow(bCustom);
}

void CDialogNewControl::OnSelchangeComboCategory()
{
	int nIndex = m_comboCategory.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CString strCategory;
		m_comboCategory.GetLBText(nIndex, strCategory);
		m_comboCategory.SetWindowText(strCategory);
	}
	GenerateID();
}


void CDialogNewControl::OnEditchangeComboId()
{
	m_bGenerateId = FALSE;

}

void CDialogNewControl::OnOK()
{
	UpdateData();


	CDialog::OnOK();
}
