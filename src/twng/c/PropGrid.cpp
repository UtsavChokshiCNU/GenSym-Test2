// PropGrid.cpp -- Subclassed CXTPPropertyGrid with G2 interface.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "PropGrid.h"

#define ItemType(pItem) (pItem->GetItemData())

IMPLEMENT_DYNCREATE(G2PropGrid, CXTPPropertyGrid)

BEGIN_MESSAGE_MAP(G2PropGrid, CXTPPropertyGrid)
 ON_WM_SETFOCUS()
 ON_WM_SIZE()
 ON_WM_RBUTTONDOWN()
 ON_WM_DESTROY()
 ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged)
END_MESSAGE_MAP()

G2PropGrid::G2PropGrid(int handle)
{
  m_handle = handle;
  m_g2pointer = -1;
  m_suppressEvents = 0;
  m_lastSelectedID = -1;
  SAVE_WND();
  VTRACE("Construct [%d] ", m_handle); POB(this);
}

G2PropGrid::~G2PropGrid()
{
  VTRACE("Destruct  [%d] ", m_handle); POB(this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle = 0;
  m_g2pointer = -1;
}

void G2PropGrid::PostNcDestroy()
{
  CXTPPropertyGrid::PostNcDestroy();
  delete this;
}

void G2PropGrid::OnSetFocus(CWnd* pOldWnd)
{
  VTRACE("OnSetFocus [%d] ", m_handle); POB(this);
  CXTPPropertyGrid::OnSetFocus(pOldWnd);
  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void G2PropGrid::OnDestroy()
{
  VTRACE("OnDestroy [%d] ", m_handle); POB(this);
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  CXTPPropertyGrid::OnDestroy();
}

void G2PropGrid::OnSize(UINT nType, int cx, int cy)
{
  VTRACE("OnSize [%d] type:%d %dx%d ", m_handle, nType, cx, cy); POB(this);
  CXTPPropertyGrid::OnSize(nType, cx, cy);
  g2pvt_view_sized(this, m_handle);
}

void G2PropGrid::RefreshItem(CXTPPropertyGridItem *pItem, BOOL captionToo)
{
  if(pItem->IsVisible())
    GetGridView().InvalidateRect(captionToo ? pItem->GetItemRect() : pItem->GetValueRect());
}

LRESULT G2PropGrid::OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  CXTPPropertyGridView &grid = GetGridView();
  CXTPPropertyGridItem *pItem;

  for(int i=0; i<grid.GetCount(); i++) {
    pItem = grid.GetItem(i);
    if(ItemType(pItem) == PG_NODE_TYPE_TEXT &&
       ((CCustomItemTextWithIcon*)pItem)->m_icon == (int)changed_icon)
      RefreshItem(pItem);
  }
  return 0;
}

BOOL G2PropGrid::OnPropertyGridNotify(int eventCode, CXTPPropertyGridItem* pItem)
{
  switch(eventCode) {
   case XTP_PGN_SELECTION_CHANGED:
     if(m_lastSelectedID != pItem->GetID()) { // NOTE: Maybe don't do this?
       m_lastSelectedID = pItem->GetID();
       SendEvent(PG_EVENT_SELECT, pItem);
     }
     break;
   case XTP_PGN_ITEMVALUE_CHANGED:
     SendEvent(PG_EVENT_EDITED, pItem, pItem->GetValue(), GetIntegerValue(pItem));
     break;
   case XTP_PGN_ITEMEXPANDCHANGED:
     SendEvent(pItem->IsExpanded() ? PG_EVENT_NODE_EXPANDED : PG_EVENT_NODE_COLLAPSED, pItem);
     break;
   case XTP_PGN_DBLCLICK:
     SendEvent(PG_EVENT_DOUBLE_CLICK, pItem);
     break;
   case XTP_PGN_RCLICK:
     pItem->Select();		       // Default behavior, to agree with tree view.
     SendEvent(PG_EVENT_RIGHT_CLICK, pItem);
     break;
   case XTP_PGN_INPLACEBUTTONDOWN:
     if(pItem->GetFlags() & xtpGridItemHasExpandButton)	// Not if merely a combo box button.
       SendEvent(PG_EVENT_EDIT, pItem);
     break;
   case XTP_PGN_SORTORDER_CHANGED:
     SendEvent(PG_EVENT_SORTED, pItem, NULL, GetSort());
     break;
   case XTP_PGN_EDIT_CHANGED:	// Validate editor input
     break;
  }
  return FALSE;
}


void G2PropGrid::OnVerbClick(int nIndex, CPoint pt)
{
  CXTPPropertyGrid::OnVerbClick(nIndex, pt);
  SendEvent(PG_EVENT_VERB, NULL, NULL, nIndex);
}

void G2PropGrid::SendEvent(int eventCode, CXTPPropertyGridItem *pItem, LPCWSTR string, int intValue)
{
  if(m_suppressEvents == 0)
    g2pvt_fire_control_event(GENSYM_PROP_GRID, m_handle,
			     eventCode,	                  // x
			     pItem ? pItem->GetID() : 0,  // y
			     intValue,			  // width
			     0,				  // height
			     string);			  // value
}

CXTPPropertyGridItem *G2PropGrid::AddItem(int id, int type, LPCTSTR caption, 
					  CXTPPropertyGridItem *pParent,
					  LPCTSTR strValue, int intValue, double floatValue)
{
  CXTPPropertyGridItem *pItem = NULL;
  CString _strValue;

  switch(type) {
   case PG_NODE_TYPE_CATEGORY:
     pItem = AddCategory(caption);
     break;
   case PG_NODE_TYPE_TEXT:
     _strValue = strValue;
     _strValue.Remove(GENSYM_CODE_FOR_LINEBREAK); // GENSYMCID-940, GENSYM-429
     pItem = new CCustomItemTextWithIcon(caption, _strValue);
     break;
   case PG_NODE_TYPE_INTEGER:
     pItem = new CXTPPropertyGridItemNumber(caption, intValue);
     break;
   case PG_NODE_TYPE_BOOLEAN:
     pItem = new CXTPPropertyGridItemBool(caption, intValue != 0);
     break;
   case PG_NODE_TYPE_COLOR:
     pItem = new CCustomItemColor(caption, (COLORREF)intValue);
     break;
   case PG_NODE_TYPE_DATE:
     pItem = new CXTPPropertyGridItemDate(caption, (COleDateTime)(DATE)intValue);
     break;
   case PG_NODE_TYPE_FLOAT:
     pItem = new CXTPPropertyGridItemDouble(caption, floatValue, _T("%0.6g"));
     break;
  }

  if(pItem) {
    pItem->SetItemData(type);
    pItem->SetID(id);
    if(type != PG_NODE_TYPE_CATEGORY)
      pParent->AddChildItem(pItem);
  }
  return pItem;
}

void G2PropGrid::SetNodeIcon(CXTPPropertyGridItem* pItem, int icon)
{
  if(pItem && ItemType(pItem) == PG_NODE_TYPE_TEXT) {
    ((CCustomItemTextWithIcon*)pItem)->SetIcon(icon);
    RefreshItem(pItem);
  }
}

void G2PropGrid::SetNodeValue(CXTPPropertyGridItem* pItem, 
			      LPCTSTR strValue, int intValue, double floatValue)
{
  CString _strValue;
  switch(ItemType(pItem)) {
   case PG_NODE_TYPE_CATEGORY:
     break;
   case PG_NODE_TYPE_TEXT:
     _strValue = strValue;
     _strValue.Remove(GENSYM_CODE_FOR_LINEBREAK); // GENSYMCID-940, GENSYM-429
     pItem->SetValue(_strValue);
     break;
   case PG_NODE_TYPE_INTEGER:
     ((CXTPPropertyGridItemNumber*)pItem)->SetNumber(intValue);
     break;
   case PG_NODE_TYPE_BOOLEAN:
     ((CXTPPropertyGridItemBool*)pItem)->SetBool(intValue != 0);
     break;
   case PG_NODE_TYPE_COLOR:
     ((CCustomItemColor*)pItem)->SetColor((COLORREF)intValue);
     break;
   case PG_NODE_TYPE_DATE:
     ((CXTPPropertyGridItemDate*)pItem)->SetDate((COleDateTime)(DATE)intValue);
     break;
   case PG_NODE_TYPE_FLOAT:
     ((CXTPPropertyGridItemDouble*)pItem)->SetDouble(floatValue);
     break;
  }
  RefreshItem(pItem);
}

int G2PropGrid::GetIntegerValue(CXTPPropertyGridItem* pItem)
{
  switch(ItemType(pItem)) {
   case PG_NODE_TYPE_TEXT:
     if(pItem->GetConstraintEdit())
       return pItem->GetConstraints()->FindConstraint(pItem->GetValue());
     break;
   case PG_NODE_TYPE_INTEGER:
     return ((CXTPPropertyGridItemNumber*)pItem)->GetNumber();
   case PG_NODE_TYPE_BOOLEAN:
     return (int) ((CXTPPropertyGridItemBool*)pItem)->GetBool();
   case PG_NODE_TYPE_COLOR:
     return (int) ((CXTPPropertyGridItemColor*)pItem)->GetColor();
   case PG_NODE_TYPE_DATE:
     return (int)(DATE)((CXTPPropertyGridItemDate*)pItem)->GetDate();
  }
  return NO_INT_VALUE;
}

int G2PropGrid::GetSort()
{
  switch(GetPropertySort()) {
   case xtpGridSortNoSort:
     return PG_SORT_NONE;
   case xtpGridSortAlphabetical:
     return PG_SORT_ALPHABETICAL;
   case xtpGridSortCategorized:
     return PG_SORT_CATEGORIZED;
   default:
     return PG_SORT_NONE;	// Can't happen
  }
}

void G2PropGrid::SetSort(int code)
{
  switch(code) {
   case PG_SORT_NONE:
     SetPropertySort(xtpGridSortNoSort);
     break;
   case PG_SORT_ALPHABETICAL:
     SetPropertySort(xtpGridSortAlphabetical);
     break;
   case PG_SORT_CATEGORIZED:
     SetPropertySort(xtpGridSortCategorized);
     break;
  }
}

void G2PropGrid::SetItemFlag(CXTPPropertyGridItem *pItem, UINT flag, BOOL value)
{
  if(pItem->IsCategory())
    return;

  UINT flags = (pItem->GetFlags() & ~flag) | (value ? flag : 0);
  switch(flag) {
   case xtpGridItemHasExpandButton:
     flags &= ~xtpGridItemHasComboButton;
     break;

   case xtpGridItemHasComboButton:
     flags &= ~xtpGridItemHasExpandButton;
     break;
  }
  pItem->SetFlags(flags);
}

void G2PropGrid::DoCollapseExpand(BOOL expand, CXTPPropertyGridItem* pItem)
{
  CXTPPropertyGridItems* pChildren;

  if(pItem && pItem->HasChilds()) {
    if(expand)
      pItem->Expand();
    else
      pItem->Collapse();
  }

  if(pItem == NULL)
    pChildren = GetCategories();
  else
    pChildren = pItem->GetChilds();

  if(pChildren)
    for(int i = 0; i < pChildren->GetCount(); i++)
      DoCollapseExpand(expand, pChildren->GetAt(i));
}



/*
 * Color Type
 */

class CCustomItemColorPopup: public CXTColorPopup
{
  friend class CCustomItemColor;
public:
  CCustomItemColorPopup() : CXTColorPopup(TRUE) {}
private:
  DECLARE_MESSAGE_MAP()
  afx_msg LRESULT OnSelEndOK(WPARAM wParam, LPARAM lParam);
  CCustomItemColor* m_pItem;
};

BEGIN_MESSAGE_MAP(CCustomItemColorPopup, CXTColorPopup)
 ON_MESSAGE(CPN_XT_SELENDOK, OnSelEndOK)
END_MESSAGE_MAP()

LRESULT CCustomItemColorPopup::OnSelEndOK(WPARAM wParam, LPARAM /*lParam*/)
{
  m_pItem->OnValueChanged(m_pItem->RGBToString((COLORREF)wParam));
  return 0;
}

CCustomItemColor::CCustomItemColor(CString strCaption, COLORREF clr)
  : CXTPPropertyGridItemColor(strCaption, clr)
{
  m_nFlags = xtpGridItemHasComboButton | xtpGridItemHasEdit;
  SetColor(clr);
}

void CCustomItemColor::OnInplaceButtonDown()
{
  CCustomItemColorPopup *pColorPopup = new CCustomItemColorPopup();
  
  CRect rcItem= GetItemRect();
  m_pGrid->ClientToScreen(&rcItem);
  rcItem.left = rcItem.right - 158; // small hack. need to add CPS_XT_LEFTALLIGN

  pColorPopup->Create(rcItem, m_pGrid, CPS_XTP_USERCOLORS|CPS_XT_EXTENDED|
		      CPS_XT_MORECOLORS|CPS_XT_SHOW3DSELECTION|CPS_XT_SHOWHEXVALUE, 
		      GetColor(), GetColor());
  pColorPopup->SetOwner(m_pGrid);
  pColorPopup->SetFocus();	
  pColorPopup->AddListener(pColorPopup->GetSafeHwnd());
  pColorPopup->m_pItem = this;
}



/*
 * G2 Icon Type
 */

CCustomItemTextWithIcon::CCustomItemTextWithIcon(CString strCaption, LPCTSTR strValue)
  : CXTPPropertyGridItem(strCaption, strValue)
{
  m_icon = -1;			// No icon
  m_stretch = TRUE;
  m_frame = TRUE;
}

BOOL CCustomItemTextWithIcon::OnDrawItemValue(CDC& dc, CRect r)
{
  if(m_icon < 0)
    return FALSE;

  CRect rc(r.left - 2, r.top + 1, r.left + 18, r.bottom - 1);
  int size = rc.Height() >= 32 ? 32 : 16;

  if(m_stretch) {
    HICON hIcon = g2pvt_get_native_iconEx(m_icon, size);
    DrawIconEx(dc, rc.left, rc.top, hIcon, rc.Width(), rc.Height(), 0, NULL, DI_NORMAL);
    ::DestroyIcon(hIcon);
  } else {
    // Faster version, but which clips rather than stretches the image.
    HIMAGELIST himl = g2pvt_get_image_list(size);
    ImageList_DrawEx(himl, g2pvt_icon_index(m_icon), dc, rc.left, rc.top, 
		     min(size,rc.Width()), min(size,rc.Height()), CLR_NONE, CLR_NONE, ILD_TRANSPARENT);
  }

  if(m_frame) {
    COLORREF clr = dc.GetTextColor();
    dc.Draw3dRect(rc, clr, clr);
  }

  CRect rcText(r);
  rcText.left += rc.Width() + 5;
  dc.DrawText(m_strValue, rcText,  DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);

  return TRUE;
}



/*
 * Some missing methods
 */

COLORREF G2PropGrid::GetLineColor()
{
  return GetPaintManager()->GetItemMetrics()->m_clrLine;
}
COLORREF G2PropGrid::GetBackColor()
{
  return GetPaintManager()->GetItemMetrics()->m_clrBack;
}
COLORREF G2PropGrid::GetForeColor()
{
  return GetPaintManager()->GetItemMetrics()->m_clrFore;
}
COLORREF G2PropGrid::GetCategoryForeColor()
{
  return GetPaintManager()->GetItemMetrics()->m_clrCategoryFore;
}
COLORREF G2PropGrid::GetReadOnlyForeColor()
{
  return GetPaintManager()->GetItemMetrics()->m_clrReadOnlyFore;
}

void G2PropGrid::SetHelpBackColor(COLORREF color)
{
  SetCustomColors(color, GetHelpForeColor(), GetLineColor(), GetBackColor(), GetForeColor(), GetCategoryForeColor());
}
void G2PropGrid::SetHelpForeColor(COLORREF color)
{
  SetCustomColors(GetHelpBackColor(), color, GetLineColor(), GetBackColor(), GetForeColor(), GetCategoryForeColor());
}
void G2PropGrid::SetLineColor(COLORREF color)
{
  SetCustomColors(GetHelpBackColor(), GetHelpForeColor(), color, GetBackColor(), GetForeColor(), GetCategoryForeColor());
}
void G2PropGrid::SetBackColor(COLORREF color)
{
  SetCustomColors(GetHelpBackColor(), GetHelpForeColor(), GetLineColor(), color, GetForeColor(), GetCategoryForeColor());
}
void G2PropGrid::SetForeColor(COLORREF color)
{
  SetCustomColors(GetHelpBackColor(), GetHelpForeColor(), GetLineColor(), GetBackColor(), color, GetCategoryForeColor());
}
void G2PropGrid::SetCategoryForeColor(COLORREF color)
{
  SetCustomColors(GetHelpBackColor(), GetHelpForeColor(), GetLineColor(), GetBackColor(), GetForeColor(), color);
}
void G2PropGrid::SetReadOnlyForeColor(COLORREF color)
{
  GetPaintManager()->GetItemMetrics()->m_clrReadOnlyFore = color;
  RedrawControl();
}



/*
 * Lisp Interface
 */

long g2ext_create_property_grid(int handle, LPWSTR title,
				long x, long y, long width, long height,
				long dock, long neighbor)
{
  CMainFrame *pFrame = GetMainWnd();
  G2PropGrid *pPG = new G2PropGrid(handle);

  pPG->Create(WinSize(width,height), pFrame, handle);
  pPG->SetPropertySort(xtpGridSortNoSort); // Default is categorized
  pPG->m_g2pointer = SavePtr(pPG->m_hWnd);
  CSize min_size(0, 0);
  pFrame->WrapWnd(pPG, handle, x, y, width, height, dock, neighbor, min_size, title);
  pPG->SetOwner(pFrame);
  return pPG->m_g2pointer;
}

long g2ext_manage_property_grid(long opcode, long handle, 
				long node, long type, long parent, LPWSTR caption,
				LPWSTR strValue, long intValue, double floatValue)
{
  G2PropGrid *pPG = FIND_WND(handle,G2PropGrid);
  CXTPPropertyGridItem *pItem   = pPG ? pPG->FindItem(node) : NULL;
  CXTPPropertyGridItem *pParent = pPG ? pPG->FindItem(parent) : NULL;
  BOOL boolValue = (intValue != 0);
  static LPCTSTR mask = NULL;

  if(!pPG) return 0;

  VTRACE("g2ext_manage_property_grid op=%d [%d] caption=%ls strValue=%ls\n",
	 opcode, handle, caption, strValue);

  switch(opcode) {
   case PG_DESTROY:
     DESTROY_WND(handle);
     break;

   case PG_ADD_ITEM:
     pPG->AddItem(node, type, caption, pParent, strValue, intValue, floatValue);
     return node;

   case PG_CLEAR:
     pPG->ResetContent();
     break;

   case PG_REFRESH:
     pPG->Refresh();
     break;

   case PG_RESET_COLORS:
     pPG->SetStandardColors();
     break;

   case PG_HELP_BACKGROUND:
     pPG->SetHelpBackColor((COLORREF)intValue);
     break;

   case PG_HELP_FOREGROUND:
     pPG->SetHelpForeColor((COLORREF)intValue);
     break;

   case PG_LINE_COLOR:
     pPG->SetLineColor((COLORREF)intValue);
     break;

   case PG_BACKGROUND:
     pPG->SetBackColor((COLORREF)intValue);
     break;

   case PG_FOREGROUND:
     pPG->SetForeColor((COLORREF)intValue);
     break;

   case PG_CATEGORY_FOREGROUND:
     pPG->SetCategoryForeColor((COLORREF)intValue);
     break;

   case PG_READONLY_FOREGROUND:
     pPG->SetReadOnlyForeColor((COLORREF)intValue);
     break;

   case PG_SORT:
     pPG->SetSort(intValue);
     pPG->Refresh();
     break;

   case PG_FONT:
     // pPG->SetFont(pFont);
     // pPG->Refresh();
     break;

   case PG_SHOW_TOOLBAR:
     pPG->ShowToolBar(boolValue);
     break;

   case PG_SHOW_HELP:
     pPG->ShowHelp(boolValue);
     break;

   case PG_HELP_HEIGHT:
     pPG->SetHelpHeight(intValue);
     break;

   case PG_VIEW_DIVIDER:
     pPG->SetViewDivider(floatValue);
     break;

   case PG_VERBS:
     // type == index, parent == total count
     if(type == 0)
       pPG->GetVerbs()->RemoveAll();
     if(parent > 0)
       pPG->GetVerbs()->Add(strValue, pPG->GetVerbs()->GetCount());
     break;

   case PG_VERBS_HEIGHT:
     pPG->SetVerbsHeight(intValue);
     break;

   /* Node Operations */

   case PG_NODE_LABEL:
     if(pItem) {
       pItem->SetCaption(strValue);
       pPG->RefreshItem(pItem, TRUE);
     }
     break;

   case PG_NODE_DESCRIPTION:
     if(pItem) {
       LPWSTR wstr = g2pvt_g2_to_windows_text(strValue);
       pItem->SetDescription(wstr);
       free(wstr);
       if(pItem == pPG->GetSelectedItem() && pPG->IsHelpVisible())
	 pPG->Refresh();	// TODO: Refresh just the help pane.
     }
     break;

   case PG_NODE_CURRENT_VALUE:
     if(pItem) pPG->SetNodeValue(pItem, strValue, intValue, floatValue);
     break;

   case PG_NODE_VALUE_FORMAT:
     if(pItem && wcslen(strValue)>0) {
       pItem->SetFormat(strValue);
       pPG->RefreshItem(pItem);	// TODO: needed?
     }
     break;

   case PG_NODE_ICON:
     if(pItem) pPG->SetNodeIcon(pItem, intValue);
     break;

   case PG_NODE_MASK:
     if(pItem) {
       int i = type;		// Index for list-valued property
       int n = parent;		// Total count
       if(i==0) mask = strValue;
       if(i==1 && mask) {
	 pItem->SetMask(mask, strValue);
	 mask = NULL;
       }
     }
     break;

   case PG_NODE_READONLY:
     if(pItem) pItem->SetReadOnly(boolValue);
     break;

   case PG_NODE_ELLIPSIS:
     if(pItem) {
       pPG->SetItemFlag(pItem, xtpGridItemHasExpandButton, boolValue);
       pPG->RefreshItem(pItem, TRUE);
     }
     break;

   case PG_NODE_EDIT_IN_PLACE:
     if(pItem) {
       pPG->SetItemFlag(pItem, xtpGridItemHasEdit, boolValue);
       pPG->RefreshItem(pItem, TRUE);
     }
     break;

   case PG_NODE_SELECT:		// Select as a property
   case PG_NODE_SELECT_NODE:	// Select as an action
     if(pItem) pItem->Select();
     break;

   case PG_NODE_DELETE_NODE:
     if(pItem) pItem->Remove();
     break;

   case PG_NODE_EXPAND_NODE:
     if(pItem) pItem->Expand();
     break;

   case PG_NODE_COLLAPSE_NODE:
     if(pItem) pItem->Collapse();
     break;

   case PG_NODE_EXPAND:
     if(pItem) 
       if(boolValue)
	 pItem->Expand();
       else
	 pItem->Collapse();
     break;

   case PG_EXPAND_ALL:
     pPG->DoCollapseExpand(TRUE, pItem);
     break;

   case PG_COLLAPSE_ALL:
     pPG->DoCollapseExpand(FALSE, pItem);
     break;

   case PG_NODE_POSSIBLE_VALUES:
     if(pItem) {
       int i = type;			       // Index for list-valued property
       int n = parent;			       // Total count
       if(i == 0)
	 pItem->GetConstraints()->RemoveAll();
       if(n == 0) {
	 pItem->SetConstraintEdit(FALSE);
	 pItem->SetFlags(0);
       } else {
	 pItem->SetConstraintEdit(TRUE);
	 pItem->SetFlags(xtpGridItemHasComboButton);
	 pItem->GetConstraints()->AddConstraint(strValue);
       }
     }
     break;

   default:
     return 0;
  }
  return 1;
}
