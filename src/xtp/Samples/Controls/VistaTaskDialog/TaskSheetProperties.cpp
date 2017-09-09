// TaskSheetProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VistaTaskDialog.h"

#include "TaskSheetProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskSheetProperties

IMPLEMENT_DYNAMIC(CTaskSheetProperties, CPropertySheet)

CTaskSheetProperties::CTaskSheetProperties(CWnd* pWndParent)
	: CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	AddPage(&m_pageGeneral);
	AddPage(&m_pageExpanded);
	AddPage(&m_pageButtons);
	AddPage(&m_pageRadioButtons);
	AddPage(&m_pageIcons);
	AddPage(&m_pageSamples);

	m_bUseComCtl32 = FALSE;

#ifdef _XTP_INCLUDE_SKINFRAMEWORK
	XTPSkinManager()->SetApplyOptions(/*xtpSkinApplyMetrics |*/ xtpSkinApplyFrame | xtpSkinApplyColors | xtpSkinApplyMenus);
#endif
}

CTaskSheetProperties::~CTaskSheetProperties()
{
}

void CTaskSheetProperties::DoDataExchange(CDataExchange* pDX)
{
	CPropertySheet::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVistaTaskDialogEditButton)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, ID_APPLY_NOW, m_btnApply);
	DDX_Control(pDX, IDHELP, m_btnHelp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTaskSheetProperties, CPropertySheet)
	//{{AFX_MSG_MAP(CTaskSheetProperties)
	ON_BN_CLICKED(IDHELP, OnChkUseComCtl)
	ON_BN_CLICKED(IDOK, OnShowDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskSheetProperties message handlers

void CTaskSheetProperties::GetButtonRect(CRect& rcButton, CButton& wndButton, BOOL bHideButton /*= FALSE*/)
{
	if (::IsWindow(wndButton.m_hWnd))
	{
		wndButton.GetWindowRect(&rcButton);
		ScreenToClient(&rcButton);

		if (bHideButton)
			wndButton.ShowWindow(SW_HIDE);
	}
}

int CTaskSheetProperties::GetPadding()
{
	CString strText;
	m_btnCancel.GetWindowText(strText);

	CWindowDC dc(NULL);
	CSize sizeText = dc.GetTextExtent(strText);
	return (m_rcCancel.Width()-sizeText.cx) / 2;
}

BOOL CTaskSheetProperties::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// transfer data into the dialog from member variables
	UpdateData(FALSE);
	
	// TODO: Add your specialized code here
	GetButtonRect(m_rcOk, m_btnOk);
	GetButtonRect(m_rcCancel, m_btnCancel);
	GetButtonRect(m_rcApply, m_btnApply, TRUE);
	GetButtonRect(m_rcHelp, m_btnHelp);

	// Move and change text for the OK button.
	m_btnCancel.MoveWindow(&m_rcHelp);
	m_btnCancel.SetWindowText(_T("Done"));

	// Move and resize and change text for the Cancel button.
	int cxPad = GetPadding();
	CWindowDC dc(NULL);
	CString strText = _T("Show Dialog");
	CSize sizeText = dc.GetTextExtent(strText);

	CRect rcCancel(m_rcApply);
	rcCancel.left = rcCancel.right - (cxPad + sizeText.cx + cxPad);
	m_btnOk.MoveWindow(&rcCancel);
	m_btnOk.SetWindowText(strText);

	// Move, resize, change text and style for Help button.
	CRect rcHelp(m_rcOk);
	CXTPWindowRect rcTab(GetTabControl());
	ScreenToClient(&rcTab);
	rcHelp.right = rcCancel.left - (m_rcHelp.left-m_rcApply.right);
	rcHelp.left = rcTab.left;

	// For Windows Vista, allow the option to use ComCtrl32 version.
	m_btnHelp.SetButtonStyle(BS_TEXT | BS_CHECKBOX | BS_LEFTTEXT);
	m_btnHelp.SetWindowText(_T("Use ComCtl32.dll ( Vista only )"));
	m_btnHelp.SetCheck(m_bUseComCtl32);
	m_btnHelp.MoveWindow(&rcHelp);
	m_btnHelp.ShowWindow(XTPSystemVersion()->IsWinVistaOrGreater() ? SW_SHOWNOACTIVATE : SW_HIDE);

	for (int i = GetPageCount()-1; i >= 0; --i)
	{
		SetActivePage(i);
	}

	return bResult;
}

void CTaskSheetProperties::OnChkUseComCtl()
{
	m_bUseComCtl32 = !m_bUseComCtl32;
	m_btnHelp.SetCheck(m_bUseComCtl32);

	if (::IsWindow(m_pageIcons.m_hWnd) && 
		::IsWindow(m_pageIcons.m_chkSysIcon.m_hWnd))
	{
		m_pageIcons.m_chkSysIcon.EnableWindow(!m_bUseComCtl32);
	}
}

inline CString ConvertNewLineChar(CString strBuffer)
{
	strBuffer.Replace(_T("\\n"), _T("\n"));
	return strBuffer;
}

void CTaskSheetProperties::OnShowDialog()
{
	//CAboutDlg ad;
	//ad.DoModal();
	//return;


	//AfxMessageBox("A TaskDialog presents Hyperlink Text information in a clear and consistent way.", MB_OK|MB_ICONWARNING);
	//return;

	CTaskDialogEx taskDialog(this);

	
	taskDialog.SetWindowTitle(m_pageGeneral.m_strWindowTitle);
	taskDialog.SetMainInstruction(m_pageGeneral.m_strMainInstruction);
	taskDialog.SetContent(ConvertNewLineChar(m_pageGeneral.m_strContent));
	taskDialog.SetFooter(ConvertNewLineChar(m_pageGeneral.m_strFooter));
	taskDialog.SetVerificationText(ConvertNewLineChar(m_pageGeneral.m_strVerificationText));
	taskDialog.SetExpandedInformation(ConvertNewLineChar(m_pageExpanded.m_strExpandedInformation));
	taskDialog.SetExpandedControlText(m_pageExpanded.m_strExpandedControlText);
	taskDialog.SetCollapsedControlText(m_pageExpanded.m_strCollapsedControlText);

	//-------------------------------------------------------------------------
	// General tab.
	//-------------------------------------------------------------------------

	if (m_pageGeneral.m_bWidth)
		taskDialog.SetWidth(m_pageGeneral.m_nWidth, TRUE);

	taskDialog.SetVerifyCheckState(m_pageGeneral.m_bVerify);
	taskDialog.EnableHyperlinks(m_pageGeneral.m_bHyperLinks);
	taskDialog.EnableCancellation(m_pageGeneral.m_bAllowCancel);
	taskDialog.EnableRelativePosition(m_pageGeneral.m_bPosition);
	taskDialog.ShowProgressBar(m_pageGeneral.m_bProgress, m_pageGeneral.m_bMarquee);
	taskDialog.EnableRtlLayout(m_pageGeneral.m_bRtl);

	//-------------------------------------------------------------------------
	// Expanded tab.
	//-------------------------------------------------------------------------

	taskDialog.ExpandedByDefault(m_pageExpanded.m_bByDefault);
	taskDialog.ExpandFooterArea(m_pageExpanded.m_bFooterArea);

	//-------------------------------------------------------------------------
	// Buttons tab.
	//-------------------------------------------------------------------------
	taskDialog.SetCommonButtons(
		m_pageButtons.m_bOk,
	    m_pageButtons.m_bYes,
	    m_pageButtons.m_bNo,
	    m_pageButtons.m_bCancel,
	    m_pageButtons.m_bRetry,
	    m_pageButtons.m_bClose);

	if (::IsWindow(m_pageButtons.m_listCustom.m_hWnd))
	{
		for (int i = 0; i < m_pageButtons.m_listCustom.GetItemCount(); ++i)
		{
			CString strText = ConvertNewLineChar(m_pageButtons.m_listCustom.GetItemText(i, 0));
			taskDialog.AddButton(strText, _ttoi(m_pageButtons.m_listCustom.GetItemText(i, 1)));
		}

		taskDialog.EnableCommandLinks(m_pageButtons.m_bUseLinks, m_pageButtons.m_bShowIcons);
	}

	if (::IsWindow(m_pageButtons.m_comboDefault.m_hWnd))
	{
		int iCurSel = m_pageButtons.m_comboDefault.GetCurSel();
		if (iCurSel != CB_ERR)
		{
			taskDialog.SetDefaultButton(
				(int)m_pageButtons.m_comboDefault.GetItemData(iCurSel));
		}
	}

	//-------------------------------------------------------------------------
	// Radio buttons tab.
	//-------------------------------------------------------------------------
	if (::IsWindow(m_pageRadioButtons.m_listCustom.m_hWnd))
	{
		for (int i = 0; i < m_pageRadioButtons.m_listCustom.GetItemCount(); ++i)
		{
			taskDialog.AddRadioButton(m_pageRadioButtons.m_listCustom.GetItemText(i, 0),
				_ttoi(m_pageRadioButtons.m_listCustom.GetItemText(i, 1)));
		}
	}

	if (::IsWindow(m_pageRadioButtons.m_comboDefault.m_hWnd))
	{
		int iCurSel = m_pageRadioButtons.m_comboDefault.GetCurSel();
		if (iCurSel != CB_ERR)
		{
			taskDialog.SetDefaultRadioButton((int)
				m_pageRadioButtons.m_comboDefault.GetItemData(iCurSel));
		}
	}

	taskDialog.NoDefaultRadioButton(m_pageRadioButtons.m_bNoDefault);

	//-------------------------------------------------------------------------
	// Icons tab.
	//-------------------------------------------------------------------------
	if (m_pageIcons.m_nMainIcon != 0)
	{
		if (::IsWindow(m_pageIcons.m_comboMainIcon.m_hWnd))
		{
			taskDialog.SetMainIcon((LPCWSTR)m_pageIcons.m_comboMainIcon.GetItemData(m_pageIcons.m_nMainIcon));
		}
	}
	else
	{
		taskDialog.SetMainIcon(m_pageIcons.m_hMainIcon);
	}

	if (m_pageIcons.m_nFootIcon != 0)
	{
		if (::IsWindow(m_pageIcons.m_comboFootIcon.m_hWnd))
		{
			taskDialog.SetFooterIcon((LPCWSTR)
				m_pageIcons.m_comboFootIcon.GetItemData(m_pageIcons.m_nFootIcon));
		}
	}
	else
	{
		taskDialog.SetFooterIcon(m_pageIcons.m_hFootIcon);
	}

	taskDialog.SetUseSysIcons(m_pageIcons.m_bSysIcons);
	//taskDialog.EnableMinimize(TRUE);

#if 1
	INT_PTR nResult =  taskDialog.DoModal(m_bUseComCtl32);
	TRACE(_T("Result is %i\n"), nResult);

	if (!m_pageGeneral.m_strVerificationText.IsEmpty())
	{
		TRACE(_T("Verification is %i\n"), taskDialog.IsVerificiationChecked());
	}

	if (m_pageRadioButtons.m_listCustom.GetItemCount() > 0)
	{
		TRACE(_T("Selected RadioButton is %i\n"), taskDialog.GetSelectedRadioButtonId());
	}
#endif

#if 0

	CAlgoTaskDialog taskDlg;
	taskDlg.DoModal(FALSE);

	if (taskDialog.GetSelectedButtonId() == CB_SAVE)
	{
		/*switch (taskDialog.GetSelectedRadioButtonId())
		{
		case RB_GOOD:
			TaskDialog(NULL, NULL,
				L"TaskDialog Result",
				L"You like TaskDialogs alot", L"I'm glad you like TaskDialogs!",
				TDCBF_OK_BUTTON, NULL, NULL);
			break;

		case RB_OK:
			TaskDialog(NULL, NULL,
				L"TaskDialog Result",
				L"You like TaskDialogs a little bit", L"Maybe we'll do better next time.",
				TDCBF_OK_BUTTON, NULL, NULL);
			break;

		case RB_BAD:
			TaskDialog(NULL, NULL,
				L"TaskDialog Result",
				L"You don't like TaskDialogs at all", L"Back to MessageBox you go!",
				TDCBF_OK_BUTTON, NULL, NULL);
			break;
		}*/
	}
#endif

}

BOOL CTaskSheetProperties::UpdateButtonMap(CString strName, int nID, CComboBox* pWndCombo /*=NULL*/, BOOL bAdd /*=TRUE*/)
{
	CString strLookUp;

	if (bAdd)
	{
		if (!m_mapButtons.Lookup(nID, strLookUp))
		{
			AfxExtractSubString(strName, strName, 0);

			if (::IsWindow(pWndCombo->GetSafeHwnd()))
			{
				int nItem = pWndCombo->AddString(strName);
				pWndCombo->SetItemData(nItem, nID);
			}

			m_mapButtons[nID] = strName;
			return TRUE;
		}

		CString strBuffer;
		strBuffer.Format(_T("The button \"%s\" already exists with the ID %d"), strLookUp, nID);
		AfxMessageBox(strBuffer, MB_ICONEXCLAMATION|MB_OK);
	}
	else
	{
		if (m_mapButtons.Lookup(nID, strLookUp))
		{
			if (::IsWindow(pWndCombo->GetSafeHwnd()))
			{
				pWndCombo->DeleteString(
					pWndCombo->FindStringExact(0, strLookUp));
			}

			return m_mapButtons.RemoveKey(nID);
		}
	}

	return FALSE;
}
