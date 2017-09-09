// PaneLibrary.cpp: implementation of the CPaneLibrary class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandBarsDesigner.h"
#include "PaneLibrary.h"
#include "MainFrm.h"
#include "PropertyItemFlags.h"


CLIPFORMAT CPaneLibrary::m_cfItem = (CLIPFORMAT)::RegisterClipboardFormat(_T("PaneLibrary"));

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define IDC_TREE 100

BEGIN_MESSAGE_MAP(CTreeLibrary, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeLibrary)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LRESULT CTreeLibrary::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_NCPAINT:
		{
			CTreeCtrl::WindowProc(message, wParam, lParam);

			CRect rc;
			GetWindowRect(&rc);
			CWindowDC dc(this);
			rc.OffsetRect(-rc.TopLeft());
			COLORREF clr = GetStaticFrameColor();
			dc.Draw3dRect(rc, clr, clr);
			return TRUE;
		}
	}
	return CTreeCtrl::WindowProc(message, wParam, lParam);
}


void CPaneLibrary::CActions::DeleteAction(CXTPControlAction* pAction)
{
	for (int i = 0; i < GetCount(); i++)
	{
		if (GetAt(i) == pAction)
		{
			m_arrActions.RemoveAt(i);
			
			pAction->InternalRelease();
		}
	}
}

void CPaneLibrary::CActions::ReplaceActionId(CXTPControlAction* pAction, int nID)
{
	if (FindAction(nID) != 0)
		return;

	for (int i = 0; i < GetCount(); i++)
	{
		if (GetAt(i) == pAction)
		{
			m_arrActions.RemoveAt(i);
			
			SetActionId(pAction, nID);			
			Insert(pAction);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//
CPaneLibrary::CPaneLibrary()
{
	m_pActions = new CActions();

	m_pIcons = new CXTPImageManager();

	m_pDragAction = NULL;

	m_pResourceManager = new CResourceManager();
}

CPaneLibrary::~CPaneLibrary()
{
	m_pActions->InternalRelease();

	delete m_pIcons;

	delete m_pResourceManager;
}

BEGIN_MESSAGE_MAP(CPaneLibrary, CWnd)
	//{{AFX_MSG_MAP(CPaneLibrary)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, AFX_IDW_PANE_FIRST, OnTreeSelChange)
	ON_NOTIFY(NM_SETFOCUS, AFX_IDW_PANE_FIRST, OnTreeSetFocus)
	ON_NOTIFY(NM_RCLICK, AFX_IDW_PANE_FIRST, OnTreeRightClick)

	ON_NOTIFY(TVN_BEGINLABELEDIT, AFX_IDW_PANE_FIRST, OnTreeBeginLabelEdit)
	ON_NOTIFY(TVN_ENDLABELEDIT, AFX_IDW_PANE_FIRST, OnTreeEndLabelEdit)
	ON_NOTIFY(TVN_BEGINDRAG, AFX_IDW_PANE_FIRST, OnTreeBeginDrag)
	ON_NOTIFY(NM_CUSTOMDRAW, AFX_IDW_PANE_FIRST, OnTreeCustomDraw)


	ON_COMMAND(ID_LIBRARY_NEW, OnLibraryNew)
	ON_COMMAND(ID_LIBRARY_OPEN, OnLibraryOpen)
	ON_COMMAND(ID_LIBRARY_SAVE, OnLibrarySave)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPaneProperties message handlers

int CPaneLibrary::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_wndToolBar.CreateToolBar(WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS, this));
	VERIFY(m_wndToolBar.LoadToolBar(IDR_PANE_LIBRARY));

	if (!m_wndTreeCtrl.Create(WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE|TVS_HASLINES|
		TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_EDITLABELS, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	m_wndTreeCtrl.ModifyStyleEx(0, WS_EX_STATICEDGE);

	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR24, 0, 1);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_PANE_LIBRARY_ICONS);

	m_ilTreeIcons.Add(&bmp, RGB(0, 255, 0));
	m_wndTreeCtrl.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);

	CreateStandardActions();

	return 0;
}

void CPaneLibrary::OnDestroy()
{
	if (!m_strFileName.IsEmpty())
	{
		SaveToFile(m_strFileName);
	}

	CPaneHolder::OnDestroy();

}

void CPaneLibrary::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CSize sz(0);
	if (m_wndToolBar.GetSafeHwnd())
	{
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow(0, 0, cx, sz.cy);
		m_wndToolBar.Invalidate(FALSE);
	}

	if (m_wndTreeCtrl.GetSafeHwnd())
	{
		m_wndTreeCtrl.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	}
}


void CPaneLibrary::OnSetFocus(CWnd*)
{
	m_wndTreeCtrl.SetFocus();
}

void CPaneLibrary::RefreshResourceManager()
{
	m_pResourceManager->FreeAll();

	for (int i = 0; i < m_pActions->GetCount(); i++)
	{
		m_pResourceManager->Set(m_pActions->GetAt(i)->GetID(), m_pActions->GetAt(i)->GetKey());
	}

}


void CPaneLibrary::OnTreeSelChange(NMHDR* pNMHDR, LRESULT*)
{  
	NMTREEVIEW* pNMTreeView = (NMTREEVIEW *)pNMHDR;

	RefreshItem(pNMTreeView->itemNew.hItem);

	RefreshResourceManager();

	if (GetItemType(pNMTreeView->itemNew.hItem) == treeAction)
	{
		CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(pNMTreeView->itemNew.hItem);
		
		GetMainFrame()->m_paneIcons.ShowIcons(m_pIcons, pAction->GetID(), m_pResourceManager);
	}
}

void CPaneLibrary::OnTreeSetFocus(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();
	if (hItem) RefreshItem(hItem);

}

void CPaneLibrary::RefreshItem(HTREEITEM /*hItem*/)
{
	if (GetMainFrame()->m_pActiveCommandBars)
	{
		GetMainFrame()->m_pActiveCommandBars->SetDragControl(NULL);
	}

	GetMainFrame()->m_pActivePane = this;
	GetMainFrame()->m_paneProperties.Refresh(this);
}

TreeType CPaneLibrary::GetItemType(HTREEITEM hItem)
{
	hItem = m_wndTreeCtrl.GetParentItem(hItem);
	if (!hItem)
		return treeRoot;

	hItem = m_wndTreeCtrl.GetParentItem(hItem);
	
	return hItem ? treeAction : treeCategory;
}

int CPaneLibrary::FindLastId()
{
	int nCount = m_pActions->GetCount();
	int nId = 2000;
	
	for (int i = 0; i < nCount; i++)
	{
		if (m_pActions->GetAt(i)->GetID() >= nId && m_pActions->GetAt(i)->GetID() < 30000)
		{
			nId = m_pActions->GetAt(i)->GetID() + 1;
		}

	}

	return nId;
}

CString GetCategoryName(const CString& str)
{
	if (str == _T("(None)"))
		return _T("");
	
	return str;
}

int CPaneLibrary::GetTreeChildCount(HTREEITEM hItem)
{
	int nCount = 0;
	HTREEITEM hItemChild = m_wndTreeCtrl.GetChildItem(hItem);
	while (hItemChild)
	{
		nCount++;
		
		hItemChild = m_wndTreeCtrl.GetNextSiblingItem(hItemChild);
	}
	return nCount;
}

void CPaneLibrary::OnTreeRightClick(NMHDR* /*pNMHDR*/, LRESULT*)
{
	CPoint point, ptScreen;
	::GetCursorPos(&ptScreen);
	
	point = ptScreen;
	m_wndTreeCtrl.ScreenToClient(&point);
	
	TV_HITTESTINFO tvhti;
	tvhti.pt = point;
	m_wndTreeCtrl.HitTest(&tvhti);
	
	if ((tvhti.flags & (TVHT_ONITEMLABEL | TVHT_ONITEMICON)) && (tvhti.hItem != NULL))
	{
		TreeType type = GetItemType(tvhti.hItem);

		if (type == treeRoot)
		{
			CMenu menu;
			menu.LoadMenu(IDR_MENU_LIBRARY);

			UINT nCmd = TrackPopupMenu(menu.GetSubMenu(0)->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);

			if (nCmd == ID_ROOT_INSERT)
			{
				CString strCaption;
				strCaption.Format(_T("Category%i"), GetTreeChildCount(m_wndTreeCtrl.GetRootItem()));

				HTREEITEM hItem = m_wndTreeCtrl.InsertItem(strCaption, 0, 0, tvhti.hItem);
				m_wndTreeCtrl.SelectItem(hItem);

			}
			
			return;
		}

		if (type == treeCategory)
		{
			CMenu menu;
			menu.LoadMenu(IDR_MENU_LIBRARY);

			UINT nCmd = TrackPopupMenu(menu.GetSubMenu(1)->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);

			if (nCmd == ID_CATEGORY_ADDACTION)
			{
				int nID = FindLastId();
				CXTPControlAction* pAction = m_pActions->Add(nID);
				
				CString strCaption;
				strCaption.Format(_T("Action%i"), nID);
				pAction->SetCaption(strCaption);
				pAction->SetKey(strCaption);
				pAction->SetCategory(GetCategoryName(m_wndTreeCtrl.GetItemText(tvhti.hItem)));

				HTREEITEM hItem = m_wndTreeCtrl.InsertItem(strCaption, 1, 1, tvhti.hItem);
				m_wndTreeCtrl.SetItemData(hItem, (DWORD_PTR)pAction);

				m_wndTreeCtrl.SelectItem(hItem);
			}

			if (nCmd == ID_CATEGORY_DELETECATEGORY)
			{
				m_wndTreeCtrl.DeleteItem(tvhti.hItem);
			}
			
			return;
		}

		if (type == treeAction)
		{
			CMenu menu;
			menu.LoadMenu(IDR_MENU_LIBRARY);

			UINT nCmd = TrackPopupMenu(menu.GetSubMenu(2)->GetSafeHmenu(), TPM_RETURNCMD, ptScreen.x, ptScreen.y, 0, m_hWnd, 0);

			if (nCmd == ID_ACTION_DELETEACTION)
			{
				CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(tvhti.hItem);

				m_wndTreeCtrl.DeleteItem(tvhti.hItem);
				m_pActions->DeleteAction(pAction);
			}
			
			return;
		}
	}	
}

void CPaneLibrary::OnTreeBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTVDISPINFO ptvdi = (LPNMTVDISPINFO)pNMHDR; 

	TreeType type = GetItemType(ptvdi->item.hItem);
	
	if (type == treeRoot)
	{
		*pResult = 1;
	}
	else if (type == treeCategory)
	{
		if (GetCategoryName(m_wndTreeCtrl.GetItemText(ptvdi->item.hItem)).IsEmpty())
		{
			*pResult = 1;
		}
	}

}

void CPaneLibrary::OnTreeEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTVDISPINFO ptvdi = (LPNMTVDISPINFO)pNMHDR; 

	if (!ptvdi->item.pszText || ptvdi->item.pszText[0] == 0)
	{
		*pResult = FALSE;
		return;
	}

	*pResult = TRUE;

	TreeType type = GetItemType(ptvdi->item.hItem);
	
	if (type == treeAction)
	{
		CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(ptvdi->item.hItem);
		if (!pAction)
		{
			*pResult = FALSE;
			return;
		}
		
		pAction->SetCaption(ptvdi->item.pszText);
		RefreshItem(ptvdi->item.hItem);

	}
	else if (type == treeCategory)
	{
		if (GetCategoryName(ptvdi->item.pszText).IsEmpty())
		{
			*pResult = FALSE;
			return;
		}

		HTREEITEM hItemChild = m_wndTreeCtrl.GetChildItem(ptvdi->item.hItem);
		while (hItemChild)
		{
			CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(hItemChild);
			ASSERT(pAction);				

			if (pAction)
			{
				pAction->SetCategory(ptvdi->item.pszText);
			}

			hItemChild = m_wndTreeCtrl.GetNextSiblingItem(hItemChild);
		}

	}

}

CObject* CPaneLibrary::RefreshPropertyGrid(CXTPPropertyGrid* pPropertyGrid) 
{
	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();
	if (!hItem) 
		return NULL;

	if (GetItemType(hItem) != treeAction)
		return NULL;

	CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(hItem);
	if (!pAction)
		return NULL;

	CXTPPropertyGridItem* pCategory = pPropertyGrid->AddCategory(ID_GRID_CATEGORY_APPEARANCE);

	pCategory->AddChildItem(new CXTPPropertyGridItemNumber(ID_GRID_ITEM_CONTROL_ID, pAction->GetID()));

	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_KEY, pAction->GetKey()));

	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_CAPTION, pAction->GetCaption()));


	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_DESCRIPTION, pAction->GetDescription()));
	pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_TOOLTIP, pAction->GetTooltip()));

	CXTPPropertyGridItem* pItemControlCategory = pCategory->AddChildItem(new CXTPPropertyGridItem(ID_GRID_ITEM_ACTION_CATEGORY, pAction->GetCategory()));
	pItemControlCategory->SetFlags(xtpGridItemHasComboButton | xtpGridItemHasEdit);

	HTREEITEM hItemRoot = m_wndTreeCtrl.GetRootItem();
	HTREEITEM hItemChild = m_wndTreeCtrl.GetChildItem(hItemRoot);
	while (hItemChild)
	{
		CString strItem = m_wndTreeCtrl.GetItemText(hItemChild);
		
		if (!GetCategoryName(strItem).IsEmpty())
		{
			pItemControlCategory->GetConstraints()->AddConstraint(strItem);
		}

		hItemChild = m_wndTreeCtrl.GetNextSiblingItem(hItemChild);
	}
	
	pCategory->Expand();

	return pAction;
}

BOOL CPaneLibrary::OnPropertyGridValueChanged(CObject* pActiveObject, CXTPPropertyGridItem* pItem)
{
	CXTPControlAction* pAction = DYNAMIC_DOWNCAST(CXTPControlAction, pActiveObject);
	if (!pAction)
		return FALSE;

	HTREEITEM hItem = m_wndTreeCtrl.GetSelectedItem();
	if (m_wndTreeCtrl.GetItemData(hItem) != (DWORD_PTR)pAction)
		return FALSE;
	
	switch (pItem->GetID())
	{
	case ID_GRID_ITEM_ACTION_KEY:	
		pAction->SetKey(pItem->GetValue());
		return TRUE;

	case ID_GRID_ITEM_ACTION_CAPTION:
		pAction->SetCaption(pItem->GetValue());
		m_wndTreeCtrl.SetItemText(hItem, pAction->GetCaption());	
		return TRUE;

	case ID_GRID_ITEM_CONTROL_ID:
		m_pActions->ReplaceActionId(pAction, GetNumberValue(pItem));
		return TRUE;

	case ID_GRID_ITEM_ACTION_DESCRIPTION:
		pAction->SetDescription(pItem->GetValue());
		return TRUE;

	case ID_GRID_ITEM_ACTION_TOOLTIP:
		pAction->SetTooltip(pItem->GetValue());
		return TRUE;

	case ID_GRID_ITEM_ACTION_CATEGORY:
		{
			pAction->SetCategory(pItem->GetValue());
			
			HTREEITEM hItemRoot = m_wndTreeCtrl.GetRootItem();
			HTREEITEM hItemChild = m_wndTreeCtrl.GetChildItem(hItemRoot);

			CString strCategory = pAction->GetCategory();
			if (strCategory.IsEmpty()) strCategory = _T("(None)");
			
			while (hItemChild)
			{
				CString strItem = m_wndTreeCtrl.GetItemText(hItemChild);
				
				if (GetCategoryName(strItem) == strCategory)
				{
					break;
				}			
				hItemChild = m_wndTreeCtrl.GetNextSiblingItem(hItemChild);
			}

			if (!hItemChild)
			{
				hItemChild = m_wndTreeCtrl.InsertItem(strCategory, 0, 0, hItemRoot);
			}
				
			m_wndTreeCtrl.DeleteItem(hItem);
			
			HTREEITEM hNewItem = m_wndTreeCtrl.InsertItem(pAction->GetCaption(), 0, 0, hItemChild);
			m_wndTreeCtrl.SetItemData(hNewItem, (DWORD_PTR)pAction);
			
			m_wndTreeCtrl.SelectItem(hNewItem);			

		}
		return TRUE;

	}

	return FALSE;
}

void CPaneLibrary::OnTreeCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTVCUSTOMDRAW* lpLVCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
	*pResult = CDRF_DODEFAULT;

	switch (lpLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;

	case CDDS_PREPAINT | CDDS_ITEM:
		{
			HTREEITEM hItem = (HTREEITEM)lpLVCD->nmcd.dwItemSpec;
			if (GetItemType(hItem) != treeAction)
				return;
			
			CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(hItem);
			if (!pAction)
				return;
	
			*pResult |= CDRF_NOTIFYPOSTPAINT;
			
			break;
		}

	case CDDS_POSTPAINT | CDDS_ITEM:
	case CDDS_POSTPAINT | CDDS_ITEM  | CDDS_SUBITEM:
		{
			HTREEITEM hItem = (HTREEITEM)lpLVCD->nmcd.dwItemSpec;

			CXTPControlAction* pAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(hItem);
			if (!pAction)
				return;
			
			CSize sz(16, 16);
			
			CXTPImageManagerIcon* pIcon = m_pIcons->GetImage(pAction->GetIconId(), 16);
			
			if (!pIcon)
				return;

			CRect rc(0, 0, 0, 0);
			m_wndTreeCtrl.GetItemRect(hItem, rc, TRUE);
			
			if (!rc.IsRectEmpty())
			{
				XTPImageState imageState = xtpImageNormal;

				CPoint pt(rc.left - 16 - 2, (rc.top + rc.bottom - sz.cy) / 2);
				pIcon->Draw(CDC::FromHandle(lpLVCD->nmcd.hdc), pt, pIcon->GetIcon(imageState), sz);
			}
			
			break;
		}
	}

}

void CPaneLibrary::OnTreeBeginDrag(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{
	LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)pNMHDR;
	
	if (GetItemType(pnmtv->itemNew.hItem) != treeAction)
		return;

	m_pDragAction = (CXTPControlAction*)m_wndTreeCtrl.GetItemData(pnmtv->itemNew.hItem);
	if (!m_pDragAction)
		return;

	COleDataSource dataSource;

	HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, 1);

	dataSource.CacheGlobalData(m_cfItem, hGlobal);


	dataSource.DoDragDrop(DROPEFFECT_COPY);

	m_pDragAction = NULL;
}

void CPaneLibrary::OnLibraryNew()
{
	if (AfxMessageBox(_T("Are you sure you want remove all actions?"), MB_YESNO) != IDYES)
		return;

	m_wndTreeCtrl.DeleteAllItems();
	m_pActions->RemoveAll();

	FillActions();

	m_strFileName.Empty();
}


void CPaneLibrary::AddAction(int nID, LPCTSTR lpszKey, LPCTSTR lpszCategory)
{
	CXTPControlAction* pAction = m_pActions->Add(nID);
	pAction->SetCategory(lpszCategory);
	pAction->SetKey(lpszKey);
}

void CPaneLibrary::CreateStandardActions()
{
	CString strFileName = AfxGetApp()->GetProfileString(_T("ActionsLibrary"), _T("CurrentFile"), _T(""));
	
	if (!strFileName.IsEmpty() && LoadFromFile(strFileName))
	{
		return;
	}

	m_strFileName.Empty();


	m_wndTreeCtrl.DeleteAllItems();
	m_pActions->RemoveAll();
	m_pIcons->RemoveAll();

	CXTPPropExchangeXMLNode px(TRUE, NULL, _T("DesignerFile"));
	if (px.LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_PANE_LIBRARY_ACTIONS), _T("XML")))
	{
		CXTPPropExchangeSection secCategories(px.GetSection(_T("Categories")));
		ExchangeCategories(&secCategories);
		
		CXTPPropExchangeSection secActions(px.GetSection(_T("Actions")));
		m_pActions->DoPropExchange(&secActions);
		
		CXTPPropExchangeSection secImages(px.GetSection(_T("Images")));
		m_pIcons->DoPropExchange(&secImages);
	}

	FillActions();
}

BOOL CPaneLibrary::LoadFromFile(CString strFileName)
{
	CXTPPropExchangeXMLNode px(TRUE, NULL, _T("DesignerFile"));
	if (!px.LoadFromFile(strFileName))
		return FALSE;

	m_wndTreeCtrl.SetRedraw(FALSE);

	m_wndTreeCtrl.DeleteAllItems();
	m_pActions->RemoveAll();
	m_pIcons->RemoveAll();

	CXTPPropExchangeSection secCategories(px.GetSection(_T("Categories")));
	ExchangeCategories(&secCategories);

	CXTPPropExchangeSection secActions(px.GetSection(_T("Actions")));
	m_pActions->DoPropExchange(&secActions);

	CXTPPropExchangeSection secImages(px.GetSection(_T("Images")));
	m_pIcons->DoPropExchange(&secImages);


	FillActions();

	m_wndTreeCtrl.SetRedraw(TRUE);
	m_strFileName = strFileName;

	return TRUE;

}

void CPaneLibrary::OnLibraryOpen()
{
	CString strFilter = _T("XML Document (*.xml)|*.xml|All files (*.*)|*.*||");

	CFileDialog fd(TRUE, _T("xml"), NULL, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, strFilter);
	if (fd.DoModal() != IDOK)
		return;

	if (!LoadFromFile(fd.GetPathName()))
		return;

	AfxGetApp()->WriteProfileString(_T("ActionsLibrary"), _T("CurrentFile"), fd.GetPathName());
}

void CPaneLibrary::ExchangeCategories(CXTPPropExchange* pPX)
{
	if (pPX->IsLoading())
	{
		HTREEITEM hItemRoot = m_wndTreeCtrl.GetRootItem();
		if (!hItemRoot)
		{
			m_wndTreeCtrl.InsertItem(_T("Categories"), 0, 0);
		}

		for (int i = 0; ;i++)
		{
			CString strCategory;
			strCategory.Format(_T("Category%i"), i);
			
			CString strItem;

			if (!PX_String(pPX, strCategory, strItem))
				break;			

			AddCategory(strItem);
		}
	}
	else
	{
		HTREEITEM hItemRoot = m_wndTreeCtrl.GetRootItem();
		HTREEITEM hItemChild = m_wndTreeCtrl.GetChildItem(hItemRoot);
		int i = 0;
		
		while (hItemChild)
		{
			CString strItem = GetCategoryName(m_wndTreeCtrl.GetItemText(hItemChild));

			CString strCategory;
			strCategory.Format(_T("Category%i"), i);
			PX_String(pPX, strCategory, strItem);

			hItemChild = m_wndTreeCtrl.GetNextSiblingItem(hItemChild);
			i++;
		}
	}

}

HTREEITEM CPaneLibrary::AddCategory(CString strCategory)
{
	HTREEITEM hItemRoot = m_wndTreeCtrl.GetRootItem();
	HTREEITEM hItemChild = m_wndTreeCtrl.GetChildItem(hItemRoot);
	
	while (hItemChild)
	{
		CString strItem = m_wndTreeCtrl.GetItemText(hItemChild);
		
		if (GetCategoryName(strItem) == strCategory)
		{
			break;
		}			
		hItemChild = m_wndTreeCtrl.GetNextSiblingItem(hItemChild);
	}
	
	if (!hItemChild)
	{
		hItemChild = m_wndTreeCtrl.InsertItem(strCategory.IsEmpty() ? _T("(None)") : strCategory, 0, 0, hItemRoot);
		m_wndTreeCtrl.Expand(hItemChild, TVE_EXPAND);
	}

	return hItemChild;
}

void CPaneLibrary::FillActions()
{
	HTREEITEM hItemRoot = m_wndTreeCtrl.GetRootItem();
	if (!hItemRoot)
	{
		hItemRoot = m_wndTreeCtrl.InsertItem(_T("Categories"), 0, 0);
	}

	int nCount = m_pActions->GetCount();

	for (int i = 0; i < nCount; i++)
	{
		CXTPControlAction* pAction = m_pActions->GetAt(i);

		HTREEITEM hItemChild = AddCategory(pAction->GetCategory());

		HTREEITEM hNewItem = m_wndTreeCtrl.InsertItem(pAction->GetCaption(), 1, 1, hItemChild);
		m_wndTreeCtrl.SetItemData(hNewItem, (DWORD_PTR)pAction);

		m_wndTreeCtrl.Expand(hItemChild, TVE_EXPAND);
	}
	m_wndTreeCtrl.Expand(hItemRoot, TVE_EXPAND);
}

void CPaneLibrary::SaveToFile(CString strFileName)
{
	CXTPPropExchangeXMLNode px(FALSE, 0, _T("DesignerFile"));

	CXTPPropExchangeSection secCategories(px.GetSection(_T("Categories")));
	ExchangeCategories(&secCategories);

	CXTPPropExchangeSection secActions(px.GetSection(_T("Actions")));
	
	m_pActions->DoPropExchange(&secActions);

	CXTPPropExchangeSection secImages(px.GetSection(_T("Images")));
	
	m_pIcons->DoPropExchange(&secImages);

	px.SaveToFile(strFileName);

	m_strFileName = strFileName;
}

void CPaneLibrary::OnLibrarySave()
{
	CString strFilter = _T("XML Document (*.xml)|*.xml|All files (*.*)|*.*||");

	CFileDialog fd(FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() != IDOK)
		return;

	SaveToFile(fd.GetPathName());

	AfxGetApp()->WriteProfileString(_T("ActionsLibrary"), _T("CurrentFile"), fd.GetPathName());
}
