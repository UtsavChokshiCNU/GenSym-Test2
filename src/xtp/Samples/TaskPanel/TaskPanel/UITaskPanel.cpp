// UITaskPanel.cpp: implementation of the CUITaskPanel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UITaskPanel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

class CTaskPanelSeparatorItem : public CXTPTaskPanelGroupItem
{
public:
	CTaskPanelSeparatorItem()
	{
	}

	virtual CRect OnReposition(CRect rc)
	{
		rc.bottom = rc.top + 4;
		m_rcItem = rc;

		return m_rcItem;
	}

	virtual void OnDrawItem(CDC* pDC, CRect rc)
	{
		rc.DeflateRect(0, 1);
		pDC->Draw3dRect(rc, GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHIGHLIGHT));		
	}
};

CUITaskPanel::CUITaskPanel()
{
	m_bUIMode = FALSE;
}

CUITaskPanel::~CUITaskPanel()
{

}

CString StripMnemonics(CString str)
{
	XTPDrawHelpers()->StripMnemonics(str);
	int nIndex = str.Find(_T('\t'));
	if (nIndex > 0)
	{
		return str.Left(nIndex);
	}
	return str;
}

void AddGroupItems(CXTPTaskPanelGroup* pGroup,  CMenu* pMenu)
{
	for (int i = 0; i < (int)pMenu->GetMenuItemCount(); i++)
	{
		CMenu* pMenuPopup = pMenu->GetSubMenu(i);

		if (pMenuPopup)
		{
			AddGroupItems(pGroup, pMenuPopup);
		}
		else
		{	
			MENUITEMINFO info = { sizeof(MENUITEMINFO), MIIM_TYPE | MIIM_STATE};
			::GetMenuItemInfo(pMenu->m_hMenu, i, TRUE, &info);
	
			if (((info.fType & MFT_SEPARATOR) == MFT_SEPARATOR) || (pMenu->GetMenuItemID(i) == 0))
			{
				pGroup->GetItems()->Add(new CTaskPanelSeparatorItem(), 0);
				continue;
			}

			CString strCaption;
			pMenu->GetMenuString(i, strCaption, MF_BYPOSITION);			;
			
			UINT nID = pMenu->GetMenuItemID(i);
			CXTPTaskPanelGroupItem* pItem = pGroup->AddLinkItem(nID, nID);
			pItem->SetCaption(StripMnemonics(strCaption));
		}		
	}
}

void CUITaskPanel::CreateFromMenu(CMenu* pMenu)
{
	GetGroups()->Clear();


	for (int i = 0; i < (int)pMenu->GetMenuItemCount(); i++)
	{
		CMenu* pMenuPopup = pMenu->GetSubMenu(i);
		if (!pMenuPopup)
			continue;

		CString strCaption;
		pMenu->GetMenuString(i, strCaption, MF_BYPOSITION);

		CXTPTaskPanelGroup* pGroup = AddGroup(0);
		pGroup->SetCaption(StripMnemonics(strCaption));


		AddGroupItems(pGroup, pMenuPopup);
	}
}

BEGIN_MESSAGE_MAP(CUITaskPanel, CXTPTaskPanel)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
END_MESSAGE_MAP()


class CUITaskPanel::CTaskPanelCmdUI : public CCmdUI
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);

public:
	CXTPTaskPanelGroupItem* m_pItem;
};

void CUITaskPanel::CTaskPanelCmdUI::Enable(BOOL bOn)
{
	m_bEnableChanged = TRUE;

	ASSERT(m_pItem != NULL);

	m_pItem->SetEnabled(bOn);
}

void CUITaskPanel::CTaskPanelCmdUI::SetCheck(int nCheck)
{
	ASSERT(nCheck >= 0 && nCheck <= 2); // 0 =>off, 1 =>on, 2 =>indeterminate
	ASSERT(m_pItem != NULL);

	m_pItem->SetItemSelected(nCheck);
}

void CUITaskPanel::CTaskPanelCmdUI::SetText(LPCTSTR lpszCaption)
{
	ASSERT(m_pItem != NULL);

	m_pItem->SetCaption(lpszCaption);
}


LRESULT CUITaskPanel::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	
	if (m_bUIMode && GetSafeHwnd() && (GetStyle() & WS_VISIBLE))
	{
		CWnd* pTarget = GetOwner();

		if (pTarget != NULL)
			OnUpdateCmdUI(pTarget, (BOOL)wParam);
	}
	return 0L;
}

void CUITaskPanel::OnUpdateCmdUI(CWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CTaskPanelCmdUI state;
	state.m_pOther = this;

	for (int i = 0; i < GetGroupCount(); i++)
	{
		CXTPTaskPanelGroup* pGroup = GetAt(i);
		
		for (state.m_nIndex = 0; (int)state.m_nIndex < pGroup->GetItemCount(); state.m_nIndex++)
		{
			CXTPTaskPanelGroupItem* pItem = pGroup->GetAt(state.m_nIndex);
			
			state.m_nID = pItem->GetID();
			state.m_pItem = pItem;
			
			if (CWnd::OnCmdMsg(0,
				MAKELONG((int)CN_UPDATE_COMMAND_UI, WM_COMMAND + WM_REFLECT_BASE),
				&state, NULL))
				continue;
			
			// allow the toolbar itself to have update handlers
			if (CWnd::OnCmdMsg(state.m_nID, (int)CN_UPDATE_COMMAND_UI, &state, NULL))
				continue;
			
			// allow the owner to process the update
			state.DoUpdate(pTarget, bDisableIfNoHndler);
		}
	}

	// update the dialog controls added to the toolbar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);

}
