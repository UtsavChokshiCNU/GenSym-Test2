// PaneProperties.cpp : implementation file
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
#include "CommandBarsDesigner.h"
#include "PaneProperties.h"

#include "ResourceManager.h"
#include "DialogListEditor.h"
#include "PropertyItemFlags.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR lpStyles[] = {_T("xtpButtonAutomatic"), _T("xtpButtonCaption"), _T("xtpButtonIcon"), _T("xtpButtonIconAndCaption"), _T("xtpButtonIconAndCaptionBelow"), _T("xtpButtonCaptionAndDescription") };
LPCTSTR lpDropDownStyles[] = {_T("DropDown"), _T("DropDownList")};
LPCTSTR lpVisibility[] = {_T("Always visible in menus"), _T("Visible if recently used")};



/////////////////////////////////////////////////////////////////////////////
// CPaneProperties

CPaneProperties::CPaneProperties()
{
	m_pActiveObject = NULL;
	m_pActivePane = NULL;
	m_pActiveCommandBars = NULL;

	m_bApplyForGroup = FALSE;
}

CPaneProperties::~CPaneProperties()
{
}


BEGIN_MESSAGE_MAP(CPaneProperties, CWnd)
	//{{AFX_MSG_MAP(CPaneProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_PANEPROPERTIES_CATEGORIZED, OnPanePropertiesCategorized)
	ON_UPDATE_COMMAND_UI(ID_PANEPROPERTIES_CATEGORIZED, OnUpdatePanePropertiesCategorized)
	ON_COMMAND(ID_PANEPROPERTIES_ALPHABETIC, OnPanePropertiesAlphabetic)
	ON_UPDATE_COMMAND_UI(ID_PANEPROPERTIES_ALPHABETIC, OnUpdatePanePropertiesAlphabetic)
	ON_COMMAND(ID_PANEPROPERTIES_PAGES, OnPanePropertiesPages)
	ON_UPDATE_COMMAND_UI(ID_PANEPROPERTIES_PAGES, OnUpdatePanePropertiesPages)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_PROPERTYGRID_NOTIFY, OnGridNotify)
END_MESSAGE_MAP()


void CPaneProperties::Refresh(CPaneHolder* pActivePane /* = NULL */)
{
	if (!m_hWnd)
		return;

	m_pActiveCommandBars = GetMainFrame()? GetMainFrame()->GetActiveCommandBars(): NULL;

	m_pActivePane = pActivePane;
	m_pActiveObject = NULL;

	m_wndPropertyGrid.BeginUpdate(m_stateExpanding);

	if (m_pActivePane)
	{
		RefreshPaneProperties();
	}
	else
	{
		RefreshDragProperties();
	}

	m_wndPropertyGrid.EndUpdate(m_stateExpanding);
}

void CPaneProperties::FillConstraintsID(CXTPPropertyGridItem* pItem)
{
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
	CMapResources* pResources = pFrame->ResourceManager()->GetResources();

	POSITION pos = pResources->GetStartPosition();
	while (pos)
	{
		CResourceInfo* pInfo;
		CString strCaption;
		pResources->GetNextAssoc(pos, strCaption, (CObject*&)pInfo);

		pItem->GetConstraints()->AddConstraint(strCaption);
	}
	pItem->GetConstraints()->Sort();
}

void CPaneProperties::FillConstraintsActionsID(CXTPPropertyGridItem* pItem)
{
	CXTPCommandBars* pCommandBars = GetMainFrame()->GetActiveCommandBars();
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
	CResourceManager* pResourceManager = pFrame->ResourceManager();

	for (int i = 0; i < pCommandBars->GetActions()->GetCount(); i++)
	{
		int nID = pCommandBars->GetActions()->GetAt(i)->GetID();
		CString strCaption = pResourceManager->GetStringID(nID);
		

		pItem->GetConstraints()->AddConstraint(strCaption);
	}
	pItem->GetConstraints()->Sort();

}

void CPaneProperties::FillActionProperties(CXTPPropertyGridItem* pCategory, CXTPControlAction* pAction)
{
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();

	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_CAPTION, pAction->GetCaption()));

	CString strIconID;
	if (pAction->GetIconId() != pAction->GetID())
		strIconID = pFrame->ResourceManager()->GetStringID(pAction->GetIconId());

	CXTPPropertyGridItem* pItemControlIconId = pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_ICONID, strIconID));
	pItemControlIconId->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
	FillConstraintsID(pItemControlIconId);

	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_DESCRIPTION, pAction->GetDescription()));
	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_TOOLTIP, pAction->GetTooltip()));

	CXTPPropertyGridItem* pItemControlCategory = pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_CATEGORY, pAction->GetCategory()));
	pItemControlCategory->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
	
	CXTPControls* pControls = pFrame->m_pControls;
	CXTPPropertyGridItemConstraints* pConstrants = pItemControlCategory->GetConstraints();
	
	for (int i = 0; i < pControls->GetCount(); i++)
	{
		CXTPControl* pControl = pControls->GetAt(i);
		
		if (pConstrants->FindConstraint(pControl->GetCategory()) == -1)
		{
			pConstrants->AddConstraint(pControl->GetCategory());
		}
	}
	
	CXTPCommandBarsOptions* pOptions = pAction->GetCommandBars()->GetCommandBarsOptions();
	
	BOOL bExists;
	BOOL bVisible = pOptions->m_mapHiddenCommands.Lookup(pAction->GetID(), bExists);
	
	CXTPPropertyGridItem* pItemControlVisibility = pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_VISIBILITY, lpVisibility[bVisible]));
	pConstrants = pItemControlVisibility->GetConstraints();
	pConstrants->AddConstraint(lpVisibility[0]);
	pConstrants->AddConstraint(lpVisibility[1]);
	pItemControlVisibility->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);

}

void CPaneProperties::RefreshDragProperties()
{
	CXTPCommandBars* pCommandBars = GetMainFrame()->GetActiveCommandBars();

	if (!pCommandBars)
		return;

	CCmdTarget* pDragControl = pCommandBars->GetDragControl();
	if (!pDragControl)
		return;

	if (pDragControl->IsKindOf(RUNTIME_CLASS(CXTPControl)))
	{
		RefreshControlProperties((CXTPControl*)pDragControl);
	}
	else if (pDragControl->IsKindOf(RUNTIME_CLASS(CXTPRibbonTab)))
	{
		RefreshRibbonTabProperties((CXTPRibbonTab*)pDragControl);
	}
	else if (pDragControl->IsKindOf(RUNTIME_CLASS(CXTPRibbonGroup)))
	{
		RefreshRibbonGroupProperties((CXTPRibbonGroup*)pDragControl);
	}
}


void CPaneProperties::RefreshRibbonGroupProperties(CXTPRibbonGroup* pGroup)
{
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();

	CXTPPropertyGridItem* pCategoryAppearance = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_APPEARANCE);
	CXTPPropertyGridItem* pCategoryBehavior = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_BEHAVIOR);


	pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_CAPTION, pGroup->GetCaption()));

	CString strID = pFrame->ResourceManager()->GetStringID(pGroup->GetID());
	CXTPPropertyGridItem* pItemControlId = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_ID, strID));
	pItemControlId->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
	FillConstraintsID(pItemControlId);


	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_GROUP_SHOWOPTIONBUTTON, pGroup->IsOptionButtonVisible()));


	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_GROUP_CONTROLSGROUPPING, pGroup->IsControlsGrouping()));

	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_GROUP_CONTROLSCENTERING, pGroup->IsControlsCentering()));

	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_GROUP_ALLOWREDUCELEVEL, pGroup->GetAllowReduceLevel()));



	m_pActiveObject = pGroup;
	
	
	if (m_stateExpanding.IsEmpty())
	{
		pCategoryAppearance->Expand();
		pCategoryBehavior->Expand();

	}
}


void CPaneProperties::RefreshRibbonTabProperties(CXTPRibbonTab* pTab)
{
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();

	CXTPPropertyGridItem* pCategoryAppearance = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_APPEARANCE);
	CXTPPropertyGridItem* pCategoryBehavior = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_BEHAVIOR);


	pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_CAPTION, pTab->GetCaption()));

	CString strID = pFrame->ResourceManager()->GetStringID(pTab->GetID());
	CXTPPropertyGridItem* pItemControlId = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_ID, strID));
	pItemControlId->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
	FillConstraintsID(pItemControlId);

	m_pActiveObject = pTab;
	
	
	if (m_stateExpanding.IsEmpty())
	{
		pCategoryAppearance->Expand();
		pCategoryBehavior->Expand();

	}
}

BOOL IsStandardControl(CRuntimeClass* pClass)
{
	return pClass == RUNTIME_CLASS(CXTPControlButton) ||
		pClass == RUNTIME_CLASS(CXTPControlPopup) ||
		pClass == RUNTIME_CLASS(CXTPControlLabel) ||
		pClass == RUNTIME_CLASS(CXTPControlComboBox) ||
		pClass == RUNTIME_CLASS(CXTPControlGallery) ||
		pClass == RUNTIME_CLASS(CXTPControlRadioButton) ||
		pClass == RUNTIME_CLASS(CXTPControlCheckBox) ||
		pClass == RUNTIME_CLASS(CXTPControlEdit);
}

void CPaneProperties::RefreshControlProperties(CXTPControl* pControl)
{
	CXTPCommandBars* pCommandBars = GetMainFrame()->GetActiveCommandBars();
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();

	if (!pControl->GetControls())
		return;

	BOOL bListControl = pControl->GetParent() == NULL;

	CXTPPropertyGridItem* pCategoryAppearance = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_APPEARANCE);
	CXTPPropertyGridItem* pCategoryBehavior = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_BEHAVIOR);

	BOOL bActionsEnable  = pCommandBars->IsActionsEnabled();
	BOOL bControlHasAction = pControl->GetAction() != NULL;

	if (bActionsEnable || bControlHasAction)
	{
		CString strID;
		if (bControlHasAction) strID =pFrame->ResourceManager()->GetStringID(pControl->GetID());
		CXTPPropertyGridItem* pItemControlAction = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_ACTION, strID));
		pItemControlAction->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
		FillConstraintsActionsID(pItemControlAction);

		if (bControlHasAction)
		{
			FillActionProperties(pItemControlAction, pControl->GetAction());
		}
	}

	if (!bControlHasAction)
	{
		pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_CAPTION, pControl->GetCaption()));

		CString strID = pFrame->ResourceManager()->GetStringID(pControl->GetID());
		CXTPPropertyGridItem* pItemControlId = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_ID, strID));
		pItemControlId->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
		FillConstraintsID(pItemControlId);

		CString strIconID;
		if (pControl->GetIconId() != pControl->GetID())
			strIconID = pFrame->ResourceManager()->GetStringID(pControl->GetIconId());

		CXTPPropertyGridItem* pItemControlIconId = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_ICONID, strIconID));
		pItemControlIconId->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
		FillConstraintsID(pItemControlIconId);
	}


	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_CONTROL_CLOSESUBMENUONCLICK, pControl->GetCloseSubMenuOnClick()));
	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_CONTROL_EXECUTEONPRESSINTERVAL, pControl->GetExecuteOnPressInterval()));

	if (!bControlHasAction)
	{
		pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_DESCRIPTION, pControl->GetDescription()));
		pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_TOOLTIP, pControl->GetTooltip()));
	}

	CRuntimeClass* pRuntimeClass = pControl->GetRuntimeClass();

	if (IsStandardControl(pRuntimeClass))
	{
		CXTPPropertyGridItem* pItemControlType = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemEnum(ID_GRID_ITEM_CONTROL_TYPE, pControl->GetType()));
		
		CXTPPropertyGridItemConstraints* pConstraints = pItemControlType->GetConstraints();
		for (int i = 0; i < _countof(lpTypes); i++) if (lpTypes[i])
		{
			pConstraints->AddConstraint(lpTypes[i], i);
		}
		
		if ((pControl->GetType() != xtpControlCheckBox) && (pControl->GetType() != xtpControlRadioButton))
		{
			CXTPPropertyGridItem* pItemControlStyle = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemEnum(ID_GRID_ITEM_CONTROL_STYLE, pControl->GetStyle()));
			
			CXTPPropertyGridItemConstraints* pConstraints = pItemControlStyle->GetConstraints();
			for (int i = 0; i < _countof(lpStyles); i++)
				pConstraints->AddConstraint(lpStyles[i], i);
		}
	}
	else
	{
		CXTPPropertyGridItem* pItemClass = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_CLASS, CString(pRuntimeClass->m_lpszClassName)));
		pItemClass->SetReadOnly();
	}

	pCategoryBehavior->AddChildItem(new CPropertyGridItemControlFlags(ID_GRID_ITEM_CONTROL_FLAGS, pControl->GetFlags()));

	if (!bListControl)
	{
		CXTPPropertyGridItem* pItemControlBeginGroup = pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_CONTROL_BEGINGROUP, pControl->GetBeginGroup()));
		pItemControlBeginGroup->SetReadOnly(pControl->GetIndex() == 0);
	}

	if (bListControl && !bControlHasAction)
	{
		CXTPPropertyGridItem* pItemControlCategory = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_CATEGORY, pControl->GetCategory()));
		pItemControlCategory->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);

		CXTPControls* pControls = pControl->GetControls();
		CXTPPropertyGridItemConstraints* pConstrants = pItemControlCategory->GetConstraints();

		for (int i = 0; i < pControls->GetCount(); i++)
		{
			CXTPControl* pControl = pControls->GetAt(i);

			if (pConstrants->FindConstraint(pControl->GetCategory()) == -1)
			{
				pConstrants->AddConstraint(pControl->GetCategory());
			}
		}
	}
	pCategoryAppearance->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_CONTROL_ITEMDEFAULT,
		pControl->IsItemDefault()));
	
	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_CONTROL_WIDTH,
		pControl->GetWidth()));

	pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_CONTROL_HEIGHT,
		pControl->GetHeight()));

	if (pControl->GetType() == xtpControlComboBox)
	{
		CXTPPropertyGridItem* pCategoryData = m_wndPropertyGrid.AddCategory(ID_GRID_CATEGORY_BEHAVIOR);

		CXTPPropertyGridItem* pItemControlList = pCategoryData->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_LIST, _T("(Collection)")));
		pItemControlList->SetFlags(xtpGridItemHasExpandButton);



		pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_CONTROL_DROPDOWNWIDTH,
			((CXTPControlComboBox*)pControl)->GetDropDownWidth()));

		CString strSelected = ((CXTPControlComboBox*)pControl)->GetDropDownListStyle()? lpDropDownStyles[0]: lpDropDownStyles[1];

		CXTPPropertyGridItem* pItemControlDropDownStyle = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_DROPDOWNSTYLE, strSelected));
		CXTPPropertyGridItemConstraints* pConstrants = pItemControlDropDownStyle->GetConstraints();
		pConstrants->AddConstraint(lpDropDownStyles[0]);
		pConstrants->AddConstraint(lpDropDownStyles[1]);
		pItemControlDropDownStyle->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);

	}
	if (pControl->GetType() == xtpControlEdit)
	{
		pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_CONTROL_READONLY, ((CXTPControlEdit*)pControl)->GetReadOnly()));
		pCategoryBehavior->AddChildItem(new CXTPPropertyGridItemBool(ID_GRID_ITEM_CONTROL_SHOWSPINBUTTONS, ((CXTPControlEdit*)pControl)->IsSpinButtonsVisible()));
	}

	if (!bListControl && pControl->GetParent()->GetType() == xtpBarTypePopup && pControl->GetID() > 0 && !bControlHasAction)
	{
		CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();

		BOOL bExists;
		BOOL bVisible = pOptions->m_mapHiddenCommands.Lookup(pControl->GetID(), bExists);

		CXTPPropertyGridItem* pItemControlVisibility = pCategoryAppearance->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_CONTROL_VISIBILITY, lpVisibility[bVisible]));
		CXTPPropertyGridItemConstraints* pConstrants = pItemControlVisibility->GetConstraints();
		pConstrants->AddConstraint(lpVisibility[0]);
		pConstrants->AddConstraint(lpVisibility[1]);
		pItemControlVisibility->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);
	}


	m_pActiveObject = pControl;

	if (!pCommandBars->IsActionsEnabled())
	{
		m_wndPropertyGrid.GetVerbs()->Add(_T("Enable Actions"), 0);
	}


	if (m_stateExpanding.IsEmpty())
	{
		pCategoryAppearance->Expand();
		pCategoryBehavior->Expand();

	}
}

void CPaneProperties::CreateActionList(CXTPCommandBars* pCommandBars, CXTPControls* pControls)
{
	for (int i = 0; i < pControls->GetCount(); i++)
	{
		CXTPControl* pControl = pControls->GetAt(i);

		if (pControl->IsTemporary())
			continue;

		if (pControl->GetID() > 0 && pControl->GetID() < 0xFFFFFF && pControl->GetAction() == NULL)
		{
			CXTPControlAction* pAction = pCommandBars->CreateAction(pControl->GetID());

			if (!pControl->GetCaption().IsEmpty())
				pAction->SetCaption(pControl->GetCaption());
			
			if (!pControl->GetTooltip().IsEmpty())
				pAction->SetTooltip(pControl->GetTooltip());

			if (!pControl->GetDescription().IsEmpty())
				pAction->SetDescription(pControl->GetDescription());

			if (!pControl->GetCategory().IsEmpty())
				pAction->SetCategory(pControl->GetCategory());

			pControl->SetAction(pAction);		
		}

		if (pControl->GetCommandBar())
		{
			CreateActionList(pCommandBars, pControl->GetCommandBar()->GetControls());
		}
	}
}

void CPaneProperties::EnableActions()
{
	CXTPCommandBars* pCommandBars = GetMainFrame()->GetActiveCommandBars();
	CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();

	if (!pCommandBars)
		return;

	pCommandBars->EnableActions();

	CXTPToolBar* pMenuBar = pCommandBars->GetMenuBar();

	int i;
	for (i = 0; i < pCommandBars->GetCount(); i++)
	{
		CXTPCommandBar* pCommandBar = pCommandBars->GetAt(i);
		if (pCommandBar != pMenuBar)
			CreateActionList(pCommandBars, pCommandBar->GetControls());
	}

	for (i = 0; i < pCommandBars->GetContextMenus()->GetCount(); i++)
	{
		CXTPCommandBar* pCommandBar = pCommandBars->GetContextMenus()->GetAt(i);
		CreateActionList(pCommandBars, pCommandBar->GetControls());
	}

	CreateActionList(pCommandBars, pFrame->m_pControls);

	if (pMenuBar)
		CreateActionList(pCommandBars, pCommandBars->GetMenuBar()->GetControls());

	Refresh();
}


void CPaneProperties::RefreshPaneProperties()
{
	if (!m_pActivePane)
		return;

	m_pActiveObject = m_pActivePane->RefreshPropertyGrid(&m_wndPropertyGrid);
}



/////////////////////////////////////////////////////////////////////////////
// CPaneProperties message handlers

int CPaneProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_wndToolBar.CreateToolBar(WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	VERIFY(m_wndToolBar.LoadToolBar(IDR_PANE_PROPERTIES));


	VERIFY(m_wndPropertyGrid.Create( CRect(0, 0, 0, 0), this, 0 ));
	m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);

	return 0;
}

void CPaneProperties::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CSize sz(0);
	if (m_wndToolBar.GetSafeHwnd())
	{
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow(0, 0, cx, sz.cy);
		m_wndToolBar.Invalidate(FALSE);
	}
	if (m_wndPropertyGrid.GetSafeHwnd())
	{
		m_wndPropertyGrid.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	}
}

void CPaneProperties::OnSetFocus(CWnd*)
{
	m_wndPropertyGrid.SetFocus();
}


void CPaneProperties::OnPanePropertiesCategorized()
{
	m_wndPropertyGrid.SetPropertySort(xtpGridSortCategorized);

}

void CPaneProperties::OnUpdatePanePropertiesCategorized(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropertyGrid.GetPropertySort() == xtpGridSortCategorized);

}

void CPaneProperties::OnPanePropertiesAlphabetic()
{
	m_wndPropertyGrid.SetPropertySort(xtpGridSortAlphabetical);

}

void CPaneProperties::OnUpdatePanePropertiesAlphabetic(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropertyGrid.GetPropertySort() == xtpGridSortAlphabetical);

}

void CPaneProperties::RefreshToolbarsPane()
{
	GetMainFrame()->m_paneToolbars.Refresh();
}
void CPaneProperties::RefreshControlsPane()
{
	GetMainFrame()->m_paneControls.Refresh(TRUE);
}


void CPaneProperties::OnPropertyChanged(CXTPControl* pControl)
{
	CXTPCommandBar* pCommandBar = pControl->GetParent();
	if (pCommandBar)
	{
		pCommandBar->SetSelected(-1);
		pCommandBar->SetPopuped(-1);
		if (pCommandBar->GetSafeHwnd())
		{
			pCommandBar->OnIdleUpdateCmdUI(NULL, NULL);
		}
	}
}

void CPaneProperties::OnTabValueChanged(CXTPRibbonTab* pTab, CXTPPropertyGridItem* pItem)
{
	switch (pItem->GetID())
	{
	case ID_GRID_ITEM_CONTROL_CAPTION:
		ASSERT(pTab);
		pTab->SetCaption(pItem->GetValue());
		return;

	case ID_GRID_ITEM_CONTROL_ID:
		{
			ASSERT(pTab);

			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			ASSERT(pFrame);

			UINT nID = pFrame->ResourceManager()->GetStringID(pItem->GetValue());

			pTab->SetID(nID);
		}
		return;
	}
}

void CPaneProperties::OnGroupValueChanged(CXTPRibbonGroup* pGroup, CXTPPropertyGridItem* pItem)
{
	ASSERT(pGroup);
	
	switch (pItem->GetID())
	{
	case ID_GRID_ITEM_CONTROL_CAPTION:
		pGroup->SetCaption(pItem->GetValue());
		pGroup->GetControlGroupPopup()->SetCaption(pItem->GetValue());
		pGroup->GetControlGroupOption()->SetCaption(pItem->GetValue());
		return;

	case ID_GRID_ITEM_GROUP_SHOWOPTIONBUTTON:
		pGroup->ShowOptionButton(GetBoolValue(pItem));
		pGroup->GetRibbonBar()->DelayLayout();
		return;

	case ID_GRID_ITEM_GROUP_CONTROLSGROUPPING:
		pGroup->SetControlsGrouping(GetBoolValue(pItem));
		pGroup->GetRibbonBar()->DelayLayout();
		return;

	case ID_GRID_ITEM_GROUP_CONTROLSCENTERING:
		pGroup->SetControlsCentering(GetBoolValue(pItem));
		pGroup->GetRibbonBar()->DelayLayout();
		return;

	case ID_GRID_ITEM_GROUP_ALLOWREDUCELEVEL:
		pGroup->AllowReduce(min(4, max(0, GetNumberValue(pItem))));
		pGroup->GetRibbonBar()->DelayLayout();
		return;		

	case ID_GRID_ITEM_CONTROL_ID:
		{

			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			ASSERT(pFrame);

			UINT nID = pFrame->ResourceManager()->GetStringID(pItem->GetValue());

			pGroup->SetID(nID);
		}
		return;
	}
}

void CPaneProperties::OnControlValueChanged(CXTPPropertyGridItem* pItem )
{
	ASSERT(pItem);
	ASSERT(m_pActiveObject);

	CXTPControl* pControl = DYNAMIC_DOWNCAST(CXTPControl, m_pActiveObject);
	if (!pControl)
		return;

	FINDCONTROLPARAM param;
	param.bIncludeSelf = FALSE;
	param.pItem = pItem;
	param.bRefresh = TRUE;

	OnControlValueChangedInstance(pControl, &param);
}

void CPaneProperties::OnControlValueChangedInstance(CXTPControl* pControl, FINDCONTROLPARAM* pParam )
{
	CXTPPropertyGridItem* pItem = pParam->pItem;
	BOOL bRefresh = pParam->bRefresh;

	switch (pItem->GetID())
	{

	case ID_GRID_ITEM_CONTROL_CAPTION:
		ASSERT(pControl);
		pControl->SetCaption(pItem->GetValue());
		OnPropertyChanged(pControl);
		if (pControl->GetParent() == NULL) RefreshControlsPane();
		return;
	case ID_GRID_ITEM_ACTION_CAPTION:
		ASSERT(pControl && pControl->GetAction());
		pControl->GetAction()->SetCaption(pItem->GetValue());
		OnPropertyChanged(pControl);
		if (pControl->GetParent() == NULL) RefreshControlsPane();
		return;
	case ID_GRID_ITEM_CONTROL_CLOSESUBMENUONCLICK:
		ASSERT(pControl);
		pControl->SetCloseSubMenuOnClick(GetBoolValue(pItem));
		OnPropertyChanged(pControl);
		return;
	case ID_GRID_ITEM_CONTROL_EXECUTEONPRESSINTERVAL:
		ASSERT(pControl);
		pControl->SetExecuteOnPressInterval(GetNumberValue(pItem));
		OnPropertyChanged(pControl);
		return;
	case ID_GRID_ITEM_CONTROL_DESCRIPTION:
		ASSERT(pControl);
		pControl->SetDescription(pItem->GetValue());
		OnPropertyChanged(pControl);
		return;
	case ID_GRID_ITEM_ACTION_DESCRIPTION:
		ASSERT(pControl && pControl->GetAction());
		pControl->GetAction()->SetDescription(pItem->GetValue());
		OnPropertyChanged(pControl);
		return;
	case ID_GRID_ITEM_CONTROL_TOOLTIP:
		ASSERT(pControl);
		pControl->SetTooltip(pItem->GetValue());
		OnPropertyChanged(pControl);
		return;
	case ID_GRID_ITEM_ACTION_TOOLTIP:
		ASSERT(pControl && pControl->GetAction());
		pControl->GetAction()->SetTooltip(pItem->GetValue());
		OnPropertyChanged(pControl);
		return;

	case ID_GRID_ITEM_CONTROL_FLAGS:
		ASSERT(pControl);
		pControl->SetFlags(GetFlagsValue(pItem));
		OnPropertyChanged(pControl);
		pControl->DelayLayoutParent();
		return;

	case ID_GRID_ITEM_CONTROL_TYPE:
		{
			CXTPControls* pControls = pControl->GetControls();
			CXTPCommandBars* pCommandBars = pControls->GetCommandBars();

			XTPControlType type = (XTPControlType)GetEnumValue(pItem);


			int nIndex = pControl->GetIndex();
			if (bRefresh) pCommandBars->SetDragControl(NULL);

			if (pControl->GetRibbonGroup())
			{
				pControl = pControl->GetRibbonGroup()->SetControlType(pControl, type);
			}
			else
			{
				pControl = pControls->SetControlType(nIndex, type);
			}
			pControl->DelayLayoutParent();

			OnPropertyChanged(pControl);
			if (bRefresh) pCommandBars->SetDragControl(pControl);

			if (pControl->GetParent() == NULL) RefreshControlsPane();
		}
		return;

	case ID_GRID_ITEM_CONTROL_STYLE:
		pControl->SetStyle((XTPButtonStyle)GetEnumValue(pItem));
		OnPropertyChanged(pControl);
		return;

	case ID_GRID_ITEM_CONTROL_BEGINGROUP:
		ASSERT(pControl);
		pControl->SetBeginGroup(GetBoolValue(pItem));
		OnPropertyChanged(pControl);
		return;

	case ID_GRID_ITEM_CONTROL_CATEGORY:
		ASSERT(pControl);
		pControl->SetCategory(pItem->GetValue());
		RefreshControlsPane();
		return;
	case ID_GRID_ITEM_ACTION_CATEGORY:
		ASSERT(pControl && pControl->GetAction());
		pControl->GetAction()->SetCategory(pItem->GetValue());
		RefreshControlsPane();
		return;

	case ID_GRID_ITEM_CONTROL_ACTION:
		{
			ASSERT(pControl);

			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			ASSERT(pFrame);

			UINT nID = pFrame->ResourceManager()->GetStringID(pItem->GetValue());

			if (nID > 0)
			{
				CXTPControlAction* pAction = pFrame->GetCommandBars()->CreateAction(nID);
				pAction->SetKey(pItem->GetValue());
				pControl->SetAction( pAction);
			}
			else
				pControl->SetAction(NULL);

			pControl->DelayLayoutParent();
			OnPropertyChanged(pControl);
			if (pControl->GetParent() == NULL) RefreshControlsPane();
			if (bRefresh) Refresh();
		}
		return;

	case ID_GRID_ITEM_CONTROL_ID:
		{

			ASSERT(pControl);

			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			ASSERT(pFrame);

			UINT nID = pFrame->ResourceManager()->GetStringID(pItem->GetValue());

			pControl->SetID(nID);
			pControl->DelayLayoutParent();
			OnPropertyChanged(pControl);
			if (pControl->GetParent() == NULL) RefreshControlsPane();
			if (bRefresh) Refresh();
		}
		return;

	case ID_GRID_ITEM_CONTROL_ICONID:
	case ID_GRID_ITEM_ACTION_ICONID:
		{
			ASSERT(pControl);

			CEmbeddedFrame* pFrame = GetMainFrame()->GetActiveEmbeddedFrame();
			ASSERT(pFrame);

			int nID = pFrame->ResourceManager()->GetStringID(pItem->GetValue());
			if (nID == 0) nID = -1;

			if (pItem->GetID() == ID_GRID_ITEM_CONTROL_ICONID)
				pControl->SetIconId(nID);
			else
				pControl->GetAction()->SetIconId(nID);
			pControl->DelayLayoutParent();
			OnPropertyChanged(pControl);
			if (pControl->GetParent() == NULL) RefreshControlsPane();
			if (bRefresh) Refresh();
		}
		return;

	case ID_GRID_ITEM_CONTROL_WIDTH:
		pControl->SetWidth(GetNumberValue(pItem));
		pControl->DelayLayoutParent();
		return;
	case ID_GRID_ITEM_CONTROL_HEIGHT:
		pControl->SetHeight(GetNumberValue(pItem));
		pControl->DelayLayoutParent();
		return;
	case ID_GRID_ITEM_CONTROL_ITEMDEFAULT:
		pControl->SetItemDefault(GetBoolValue(pItem));
		pControl->DelayLayoutParent();
		return;
	case ID_GRID_ITEM_CONTROL_DROPDOWNWIDTH:
		if (pControl->GetType() == xtpControlComboBox)
			((CXTPControlComboBox*)pControl)->SetDropDownWidth(GetNumberValue(pItem));
		pControl->DelayLayoutParent();
		return;
	case ID_GRID_ITEM_CONTROL_DROPDOWNSTYLE:
		if (pControl->GetType() == xtpControlComboBox)
			((CXTPControlComboBox*)pControl)->SetDropDownListStyle(pItem->GetValue() == lpDropDownStyles[0]);
		return;
	case ID_GRID_ITEM_CONTROL_READONLY:
		if (pControl->GetType() == xtpControlEdit)
			((CXTPControlEdit*)pControl)->SetReadOnly(GetBoolValue(pItem));
		return;
	case ID_GRID_ITEM_CONTROL_SHOWSPINBUTTONS:
		if (pControl->GetType() == xtpControlEdit)
			((CXTPControlEdit*)pControl)->ShowSpinButtons(GetBoolValue(pItem));
		pControl->DelayLayoutParent();
		return;
	case ID_GRID_ITEM_CONTROL_VISIBILITY:
		{
			CXTPCommandBarsOptions* pOptions = pControl->GetControls()->GetCommandBars()->GetCommandBarsOptions();
			if (pItem->GetValue() == lpVisibility[0])
			{
				pOptions->m_mapHiddenCommands.RemoveKey(pControl->GetID());

			} else
			{
				pOptions->m_mapHiddenCommands.SetAt(pControl->GetID(), TRUE);

			}
			if (bRefresh) Refresh();
		}
		return;
	}
}

LRESULT CPaneProperties::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_PGN_INPLACEBUTTONDOWN)
	{
		CXTPPropertyGridInplaceButton* pButton = (CXTPPropertyGridInplaceButton*)lParam;
		CXTPPropertyGridItem* pItem = pButton->GetItem();

		switch (pItem->GetID())
		{
			case ID_GRID_ITEM_CONTROL_LIST:
				if (m_pActiveObject && m_pActiveObject->IsKindOf(RUNTIME_CLASS(CXTPControl)))
				{
					if (((CXTPControl*)m_pActiveObject)->GetType() == xtpControlComboBox)
					{
						CXTPControlComboBox* pCombo = (CXTPControlComboBox*)((CXTPControl*)m_pActiveObject);
						CDialogListEditor ld(pCombo);
						ld.DoModal();
						
						return TRUE;
					}
				}
		}

	}
	if (wParam == XTP_PGN_VERB_CLICK)
	{
		CXTPPropertyGridVerb* pVerb = (CXTPPropertyGridVerb*)lParam;
		if (pVerb->GetID() == 0)
		{
			if (AfxMessageBox(_T("Are you sure you want to enable Actions? It will modify all controls that were created"), MB_YESNO) != IDYES)
				return TRUE;

			EnableActions();
		}
		

		return TRUE;
	}

	if (wParam == XTP_PGN_ITEMVALUE_CHANGED)
	{
		CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;

		if (m_pActiveObject && pItem)
		{
			if (m_pActivePane)
			{
				return m_pActivePane->OnPropertyGridValueChanged(m_pActiveObject, pItem);
			}
			else if (m_pActiveObject->IsKindOf(RUNTIME_CLASS(CXTPControl)))
			{
				OnControlValueChanged(pItem);
				return TRUE;
			}
			else if (m_pActiveObject->IsKindOf(RUNTIME_CLASS(CXTPRibbonTab)))
			{
				OnTabValueChanged((CXTPRibbonTab*)m_pActiveObject, pItem);
			}
			else if (m_pActiveObject->IsKindOf(RUNTIME_CLASS(CXTPRibbonGroup)))
			{
				OnGroupValueChanged((CXTPRibbonGroup*)m_pActiveObject, pItem);
			}
		}


	}
	return 0;
}

void CPaneProperties::OnPanePropertiesPages()
{
	if (m_pActiveCommandBars)
	{
		GetMainFrame()->GetActiveEmbeddedFrame()->ShowPropertyPage();
	}

}

void CPaneProperties::OnUpdatePanePropertiesPages(CCmdUI* pCmdUI)
{

	pCmdUI->Enable(m_pActiveCommandBars != NULL);

}
