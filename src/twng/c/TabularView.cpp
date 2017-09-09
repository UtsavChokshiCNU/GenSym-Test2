// TabularView.cpp -- Subclassed CListCtrl with G2 interface.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "NativeView.h"
#include "TabularView.h"

#ifndef HDF_SORTUP
#define HDF_SORTUP 0x0400
#endif

#ifndef HDF_SORTDOWN
#define HDF_SORTDOWN 0x0200
#endif

#define CDDS_SUBITEMPREPAINT (CDDS_ITEMPREPAINT | CDDS_SUBITEM)
const int IconSize = 16;

// Stock icons in toolbar.bmp
#define SMALL_UP_TRIANGLE        24
#define SMALL_DOWN_TRIANGLE      25
#define SMALL_3D_UP_TRIANGLE     26
#define SMALL_3D_DOWN_TRIANGLE   27

IMPLEMENT_DYNCREATE(G2TabularView, CListCtrl)

BEGIN_MESSAGE_MAP(G2TabularView, CListCtrl)
 ON_NATIVE_VIEW_MESSAGES()
 ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
// ON_NOTIFY_REFLECT(LVN_GETINFOTIP, OnGetInfoTip)
 ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemChanged)
 ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
END_MESSAGE_MAP()

int G2TabularView::m_savedSortColumn = 1;
BOOL G2TabularView::m_savedSortDirection = FALSE;

BOOL G2TabularView::G2WantsKey(UINT vKey, UINT scanCode)
{
  BOOL tvKey = (vKey==VK_UP || vKey==VK_DOWN || 
		vKey==VK_HOME || vKey==VK_END ||
		vKey==VK_PRIOR || vKey==VK_NEXT ||
		vKey==VK_BACK || vKey == VK_SPACE);
  BOOL shift = (GetKeyState(VK_SHIFT) < 0);
  BOOL ctrl = (GetKeyState(VK_CONTROL) < 0);
  BOOL alt = (GetKeyState(VK_MENU) < 0);

  if(tvKey)
    return alt;

  if((0 <= vKey && vKey <= VK_HELP) ||         // All other function keys
     (VK_NUMPAD0 <= vKey && vKey <= VK_F24) ||
     (VK_ATTN <= vKey))
    return TRUE;

  return ctrl;				       // Printing chars only if control modifier.
}

BOOL G2TabularView::KeyPress(UINT vKey, UINT scanCode)
{
  UINT g2key;

  if(G2WantsKey(vKey, scanCode) &&
     (g2key = g2pvt_compute_gensym_keycode(vKey, scanCode))) {
    m_consumedKey = TRUE;
    SendEvent(TBVE_KEYDOWN, GetSelectionMark(), -1, g2key);    // TODO: Get full selection?
    return FALSE;
  }
  return TRUE;
}

void G2TabularView::AfterMouseClick(UINT msg, UINT nFlags, CPoint p)
{
  LVHITTESTINFO lvh = {0};

  lvh.pt = p;
  if(SubItemHitTest(&lvh) >= 0) {

    int eventCode = 0;
    switch(msg) {
     case WM_LBUTTONDOWN: eventCode = TBVE_LCLICK; break;
     case WM_MBUTTONDOWN: eventCode = TBVE_MCLICK; break;
     case WM_RBUTTONDOWN: eventCode = TBVE_RCLICK; break;
    }

    if(eventCode > 0)
      SendEvent(eventCode, lvh.iItem, lvh.iSubItem, g2pvt_compute_gensym_mouse_keycode(msg));
  }
  CheckSelectionChanged();	// selection-changed event comes after the click event
}

void G2TabularView::AfterKeyPress(UINT vKey, UINT scanCode)
{
  CheckSelectionChanged();
}

void G2TabularView::SendEvent(int eventCode, int nRow/*=-1*/, int nCol/*=-1*/, int g2key/*=0*/)
{
  if(nRow<0) nRow = GetSelectionMark();
  CString label = GetItemText(nRow,0);
  int rowID = nRow<0 ? -1 : GetItemData(nRow);
  g2pvt_fire_control_event(GENSYM_TABULAR_VIEW, m_handle, eventCode, rowID, g2key, nCol, label);
}

LRESULT G2TabularView::OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  int image = g2pvt_icon_index(changed_icon);
  CRect r;
  int i, j, limit;

  CHeaderCtrl *pHdr = GetHeaderCtrl();
  HD_ITEM hdi = {0};
  hdi.mask = HDI_IMAGE;
  for(i=0; i<pHdr->GetItemCount(); i++) {
    if(pHdr->GetItem(i, &hdi) && hdi.iImage == image) {
      pHdr->GetItemRect(i, &r);
      pHdr->InvalidateRect(&r);
    }
  }

  LVITEM lvi = {0};
  lvi.mask = LVIF_IMAGE;
  limit = min(GetTopIndex() + GetCountPerPage(), GetItemCount());
  for(i=GetTopIndex(); i<limit; i++) {
    for(j=0; j<GetColumnCount(); j++) {
      lvi.iItem = i;
      lvi.iSubItem = j;
      lvi.iImage = -1;
      if(GetItem(&lvi) && lvi.iImage == image) {
	if(m_multiline) {
	  GetCellRect(i, j, LVIR_BOUNDS, r);
	  r.right = r.left + IconSize + 3;
	  r.bottom = r.top + IconSize + 3;
	} else {
	  GetCellRect(i, j, LVIR_ICON, r);
	}
	InvalidateRect(&r);
      }
    }
  }
  return 0;
}

// The imagelist we actually use for drawing.
CImageList *G2TabularView::GetDrawingImageList()
{
  return &GetMainWnd()->m_smallImageList;
}



/*
 * ListView Operations
 */

void G2TabularView::InsertColumn(int nCol, LPCTSTR label, int align, int width, int icon)
{
  LVCOLUMN lvc = {0};

  if(nCol<0) nCol = GetColumnCount();

  lvc.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM;
  lvc.pszText = (LPTSTR)label;
  lvc.fmt = align>=0 ? align : LVCFMT_LEFT;
  lvc.iSubItem = nCol;
  lvc.cx = width>=0 ? width : 75;

  CListCtrl::InsertColumn(nCol, &lvc);

  // The zeroth column is always left-aligned. To get a different alignment,
  // insert the new column again as column 1, then delete the incorrect column
  // 0. Suggested in MSDN.
  if(nCol==0 && (lvc.fmt&LVCFMT_JUSTIFYMASK) != LVCFMT_LEFT) {
    lvc.iSubItem = 1;
    CListCtrl::InsertColumn(1, &lvc);
    DeleteColumn(0);
  }

  if(icon >= 0)
    SetColumnIcon(nCol, icon);


  if(!isSortingDataApplied && (GetColumnCount() > G2TabularView::m_savedSortColumn)) {
	  	
	  m_sortColumn = G2TabularView::m_savedSortColumn;
	  m_sortAscending = G2TabularView::m_savedSortDirection;
	  isSortingDataApplied = TRUE;
  }


  m_columnWidth.InsertAt(nCol, width);
  AdjustColumnWidth(nCol);	// This is done again if we are reparented into a dialog.
}

void G2TabularView::AdjustColumnWidth(int nCol)
{
  int width = m_columnWidth[nCol];

  if(width == LVSCW_AUTOSIZE_USEHEADER || (width == LVSCW_AUTOSIZE && GetItemCount() > 0))
    CListCtrl::SetColumnWidth(nCol, width);

  else if(m_useDialogUnits && width>0) {
    CRect r(0, 0, width, 0);
    ::MapDialogRect(GetParent()->GetSafeHwnd(), &r);
    CListCtrl::SetColumnWidth(nCol, r.Width());
  }
}

void G2TabularView::RemoveColumn(int nCol)
{
  if(nCol<0) nCol = GetColumnCount() - 1;
  if(nCol<0 || nCol>=GetColumnCount())
    return;
  m_columnWidth.RemoveAt(nCol);
  DeleteColumn(nCol);
}

void G2TabularView::RemoveAllColumns()
{
  m_columnWidth.RemoveAll();
  for(int i=GetColumnCount()-1; i>=0; i--)
    DeleteColumn(i);
}

LRESULT G2TabularView::OnParentChanged(WPARAM wParam, LPARAM lParam)
{
  BOOL isDialog = (BOOL)wParam;
  HWND hDlg = (HWND)lParam;

  // TODO: Inherit parent's font?
  m_useDialogUnits = isDialog;
  for(int nCol=0; nCol<GetColumnCount(); nCol++)
    AdjustColumnWidth(nCol);

  if(m_rowHeight > 0)
    SetRowHeight(m_rowHeight);
  return 0;
}

void G2TabularView::SetColumnText(int nCol, LPCTSTR label)
{
  LVCOLUMN lvc = {0};
  if(nCol<0) nCol = GetColumnCount() - 1;
  lvc.mask = LVCF_SUBITEM | LVCF_TEXT;
  lvc.iSubItem = nCol;
  lvc.pszText = (LPTSTR)label;
  SetColumn(nCol, &lvc);
}

void G2TabularView::SetColumnWidth(int nCol, int width)
{
  if(nCol<0) nCol = GetColumnCount() - 1;
  if(nCol<0 || nCol>=GetColumnCount())
    return;
  m_columnWidth[nCol] = width;
  CListCtrl::SetColumnWidth(nCol, width);
}

void G2TabularView::SetColumnAlignment(int nCol, int align)
{
  LVCOLUMN lvc = {0};
  if(nCol<0) nCol = GetColumnCount() - 1;
  if(nCol<0 || nCol>=GetColumnCount())
    return;

  lvc.mask = LVCF_SUBITEM | LVCF_FMT;
  lvc.iSubItem = nCol;
  GetColumn(nCol, &lvc);

  lvc.fmt = (lvc.fmt & ~LVCFMT_JUSTIFYMASK) | (align>=0 ? align : LVCFMT_LEFT);
  SetColumn(nCol, &lvc);
}

int G2TabularView::GetTextFormat(int nCol)
{
  UINT fmt = DT_VCENTER | DT_WORD_ELLIPSIS; // DT_END_ELLIPSIS;

  if(nCol<0 || nCol>=GetColumnCount())
    return fmt;

  LVCOLUMN lvc = {0};
  lvc.mask = LVCF_SUBITEM | LVCF_FMT;
  lvc.iSubItem = nCol;
  GetColumn(nCol, &lvc);

  switch(lvc.fmt & LVCFMT_JUSTIFYMASK) {
   case LVCFMT_RIGHT: fmt |= DT_RIGHT; break;
   case LVCFMT_CENTER: fmt |= DT_CENTER; break;
   default: fmt |= DT_LEFT; break;
  }
  return fmt;
}

void G2TabularView::SetColumnIcon(int nCol, int icon)
{
  HD_ITEM hdi = {0};
  CHeaderCtrl *pHdr = GetHeaderCtrl();
  int image = g2pvt_icon_index(icon);

  if(nCol<0) nCol = GetColumnCount() - 1;
  if(nCol<0 || nCol>=GetColumnCount())
    return;

  if(icon>=0 && !pHdr->GetImageList()) // Lazily ensure header imagelist
    pHdr->SetImageList(GetDrawingImageList());

  hdi.mask = HDI_IMAGE | HDI_FORMAT;
  pHdr->GetItem(nCol, &hdi);

  // HDF_BITMAP_ON_RIGHT ?
  hdi.fmt = (hdi.fmt & ~HDF_JUSTIFYMASK) | (image>=0 ? HDF_IMAGE : 0);
  hdi.iImage = image;
  pHdr->SetItem(nCol, &hdi);
}

int G2TabularView::GetColumnCount()
{
  CHeaderCtrl* pHeader = GetHeaderCtrl();
  return pHeader ? pHeader->GetItemCount() : 0;
}

void G2TabularView::UpdateSortArrows()
{
  CHeaderCtrl *pHeader = GetHeaderCtrl();
  BOOL builtInIcons = (GetCommonControlsVersion() >= 6);
  HD_ITEM hdi;

  for(int i=0; i<GetColumnCount(); i++) {
    ZeroMemory(&hdi, sizeof(hdi));
    hdi.mask = HDI_FORMAT | HDI_IMAGE;
    pHeader->GetItem(i, &hdi);

    if(hdi.fmt&HDF_IMAGE && hdi.iImage>=0 && 
       hdi.iImage != SMALL_3D_UP_TRIANGLE && hdi.iImage != SMALL_3D_DOWN_TRIANGLE)
      continue;			// If column has a user icon, don't disturb it.

    hdi.fmt &= ~(HDF_IMAGE | HDF_BITMAP_ON_RIGHT | HDF_SORTDOWN | HDF_SORTUP);
    hdi.iImage = -1;

    if(i == m_sortColumn)
      if(builtInIcons) {
	hdi.fmt |= m_sortAscending ? HDF_SORTUP : HDF_SORTDOWN;
      } else {
	if(!pHeader->GetImageList()) // Lazily ensure header imagelist
	  pHeader->SetImageList(GetDrawingImageList());

	hdi.fmt |= HDF_IMAGE | HDF_BITMAP_ON_RIGHT;
	hdi.iImage = m_sortAscending ? SMALL_3D_UP_TRIANGLE : SMALL_3D_DOWN_TRIANGLE;
      }

    pHeader->SetItem(i, &hdi);
  }

  G2TabularView::m_savedSortColumn = m_sortColumn;
  G2TabularView::m_savedSortDirection = m_sortAscending;

}

int G2TabularView::InsertRow(int positionID, DWORD rowID, LPCTSTR text, COLORREF fg, COLORREF bg, bool bInsertToTop)
{
  int nRow = 0;

  if (!bInsertToTop) {
	  nRow = positionID<0 ? GetItemCount() : FindRow(positionID);
  }

  if((nRow = InsertItem(nRow, text, -1)) < 0)
    return -1;
  SetItemData(nRow, rowID);
  if(fg != CLR_NONE) m_rowFG[rowID] = fg;
  if(bg != CLR_NONE) m_rowBG[rowID] = bg;

  m_cacheRowID = rowID;
  m_cacheRowNum = nRow;
  return nRow;
}

void G2TabularView::SetCellText(int rowID, int nCol, LPCTSTR text)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;

  if(_tcschr(text, GENSYM_CODE_FOR_LINEBREAK)) {
    LPWSTR wstr = g2pvt_g2_to_windows_text((LPWSTR)text);
    SetItemText(nRow, nCol, wstr);
    free(wstr);
  } else {
    SetItemText(nRow, nCol, text);
  }
}

void G2TabularView::SetCellIcon(int rowID, int nCol, int icon)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;

  // Switch to alternate rendering if any icon is set. Actually, there needs to
  // be a non-default background color on the row, too, but I'm not bothering to
  // optimize that far.
  if(icon>=0 && !m_multiline) {
    m_multiline = TRUE;
    Invalidate();
  }

  if(icon>=0 && !GetImageList(LVSIL_SMALL)) //  Lazily ensure imagelist.
    SetImageList(GetDrawingImageList(), LVSIL_SMALL);

  SetItem(nRow, nCol, LVIF_IMAGE, NULL, g2pvt_icon_index(icon), 0, 0, 0);
  Update(nRow);
}

BOOL G2TabularView::GetCellRect(int nRow, int nCol, int nArea, CRect &r)
{
  if(nCol > 0)
    return GetSubItemRect(nRow, nCol, nArea, r);

  if(GetColumnCount() <= 1)
    return GetItemRect(nRow, r, nArea);

  if(!GetItemRect(nRow, r, nArea))
    return FALSE;

  if(nArea != LVIR_ICON) {
    CRect r1;
    GetSubItemRect(nRow, 1, LVIR_BOUNDS, r1);
    r.right = r1.left;
  }
  return TRUE;
}

void G2TabularView::SelectRow(int rowID)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;
  SetItemState(nRow, LVIS_SELECTED, LVIS_SELECTED);
}

void G2TabularView::DeselectRow(int rowID)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;
  SetItemState(nRow, 0, LVIS_SELECTED);
}

void G2TabularView::DeselectAllRows()
{
  for(int i=0; i<GetItemCount(); i++)
    SetItemState(i, 0, LVIS_SELECTED);
}

int G2TabularView::FindRow(DWORD rowID)
{
  if(rowID==m_cacheRowID && 
     m_cacheRowNum>=0 && 
     m_cacheRowNum<GetItemCount() &&
     GetItemData(m_cacheRowNum) == m_cacheRowID)
    return m_cacheRowNum;

  LVFINDINFO lvf = {0};
  lvf.flags = LVFI_PARAM;
  lvf.lParam = rowID;
  int nRow = FindItem(&lvf);
  if(nRow >= 0) {
    m_cacheRowID = rowID;
    m_cacheRowNum = nRow;
  }
  return nRow;
}

void G2TabularView::DeleteRow(int rowID)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;
  m_rowFG.RemoveKey(rowID);
  m_rowBG.RemoveKey(rowID);
  DeleteItem(nRow);
}

void G2TabularView::DeleteAllRows()
{
  m_rowFG.RemoveAll();
  m_rowBG.RemoveAll();
  DeleteAllItems();
}

void G2TabularView::SetRowBackgroundColor(int rowID, COLORREF color)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;

  if(color == CLR_NONE)
    m_rowBG.RemoveKey(rowID);
  else
    m_rowBG[rowID] = color;
  Update(nRow);
}

void G2TabularView::SetRowTextColor(int rowID, COLORREF color)
{
  int nRow = FindRow(rowID);
  if(nRow<0) return;

  if(color == CLR_NONE)
    m_rowFG.RemoveKey(rowID);
  else
    m_rowFG[rowID] = color;
  Update(nRow);
}

void G2TabularView::SetRowTextFontSize(int iFontSize)
{
	m_iFontHeight = iFontSize;
	m_strFontName= "Times New Roman";
	SetRowHeight(m_rowHeight);
}
int G2TabularView::GetRowTextFontSize()
{
	return m_iFontHeight;	
}
BOOL G2TabularView::GetRowBackgroundColor(int nRow, COLORREF& color)
{
  return m_rowBG.Lookup(GetItemData(nRow), color);
}

BOOL G2TabularView::GetRowTextColor(int nRow, COLORREF& color)
{
  return m_rowFG.Lookup(GetItemData(nRow), color);
}

// TODO: It only works to set this once.
void G2TabularView::SetRowHeight(int height)
{
  m_rowHeight = height;
  if(height > 0)		// Allow -1 to mean default behavior.
    m_multiline = TRUE;

  if(!m_multiline)
    return;

  if(m_useDialogUnits) {
    CRect r(0, 0, 0, m_rowHeight);
    ::MapDialogRect(GetParent()->GetSafeHwnd(), &r);
    height = r.Height();
  }

  // This imagelist hacking tricks the listview control to change its row
  // height. Then, since we are custom draw, we use a different imagelist for
  // actually drawing icons.
  if(m_scratchImageList.GetSafeHandle())
    m_scratchImageList.DeleteImageList();
  m_scratchImageList.Create(1, height, ILC_COLOR24, 1, 1);
  SetImageList(&m_scratchImageList, LVSIL_SMALL);
  GetHeaderCtrl()->SetImageList(GetDrawingImageList());
}

void G2TabularView::SetGridLines(BOOL torf)
{
  if(torf) {
    if (!m_hasGridlineColor)
      SetExtendedStyle(GetExtendedStyle() | LVS_EX_GRIDLINES);
    m_hasGridLine = TRUE;
  } else {
    SetExtendedStyle(GetExtendedStyle() & ~LVS_EX_GRIDLINES);
    m_hasGridLine = FALSE;
  }
}

void G2TabularView::OnCustomDraw(NMHDR *pNotifyStruct, LRESULT *pResult)
{
  if(m_multiline)
    MultilineCustomDraw(pNotifyStruct, pResult);
  else
    SimpleCustomDraw(pNotifyStruct, pResult);

  if (m_hasGridLine && m_hasGridlineColor) {
    CClientDC dc(this );
    CPen pen(PS_SOLID, 1, m_gridlinecolor);
    CPen *pOldPen = dc.SelectObject(&pen);

    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    RECT rect;
    pHeader->GetClientRect( &rect );
    int top = rect.bottom;

    GetClientRect( &rect );
    int borderx = 0 - GetScrollPos( SB_HORZ );
    for( int i = 0; i < nColumnCount; i++ )
    {
      borderx += GetColumnWidth( i );
      if( borderx >= rect.right ) break;
      dc.MoveTo( borderx-1, top);
      dc.LineTo( borderx-1, rect.bottom );
    }
    
    if( !GetItemRect( 0, &rect, LVIR_BOUNDS )) {
      dc.SelectObject(pOldPen);
      return;
    }

    int height = rect.bottom - rect.top;
    GetClientRect( &rect );
    int width = rect.right;
    for( i = 1; i <= GetCountPerPage(); i++ )
    {
      dc.MoveTo( 0, top + height*i);
      dc.LineTo( width, top + height*i );
    }

    dc.SelectObject(pOldPen);
  }
}

void G2TabularView::SimpleCustomDraw(NMHDR *pNotifyStruct, LRESULT *pResult)
{
  LPNMLVCUSTOMDRAW pCD = (LPNMLVCUSTOMDRAW)pNotifyStruct;
  int nRow = (int)pCD->nmcd.dwItemSpec;
  COLORREF color;

  *pResult = CDRF_DODEFAULT;

  switch(pCD->nmcd.dwDrawStage) {
   case CDDS_PREPAINT:
     *pResult = CDRF_NOTIFYITEMDRAW;
     break;

   case CDDS_ITEMPREPAINT:
     if(GetRowBackgroundColor(nRow, color))
       pCD->clrTextBk = color;

     if(GetRowTextColor(nRow, color))
       pCD->clrText = color;
     break;
  }
}

// We have to replicate most of the list control's default drawing in order to
// change the format flags in the DrawText call. Also, since we've set a scratch
// imagelist in this case, to get the desired row height, we also need to draw
// icons from the real imagelist.
void G2TabularView::MultilineCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
  LPNMLVCUSTOMDRAW pCD = (LPNMLVCUSTOMDRAW)pNMHDR;
  int nRow = (int)pCD->nmcd.dwItemSpec;
  int nCol = (int)pCD->iSubItem;

  *pResult = CDRF_DODEFAULT;

  switch(pCD->nmcd.dwDrawStage) {
   case CDDS_PREPAINT:
     *pResult = CDRF_NOTIFYITEMDRAW;
     break;

   case CDDS_ITEMPREPAINT:
     *pResult = CDRF_NOTIFYSUBITEMDRAW;
     break;

   case CDDS_SUBITEMPREPAINT:
     {
       LVITEM lvi = {0};
       BOOL wndFocused = (m_hWnd == ::GetFocus());
       BOOL itemSelected, itemFocused, hasImage;
       CDC *pDC = CDC::FromHandle(pCD->nmcd.hdc);
       COLORREF bgColor, fgColor, color;
       CRect r, b;
       
       lvi.mask = LVIF_IMAGE | LVIF_STATE;
       lvi.iItem = nRow;
       lvi.iSubItem = nCol;
       lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
       GetItem(&lvi);

       itemSelected = (lvi.state & LVIS_SELECTED);
       itemFocused = (lvi.state & LVIS_FOCUSED);
       hasImage = (lvi.iImage >= 0);

       // Choose fg/bg colors based on selected and focus state.
       if(itemSelected) {
	 bgColor = GetSysColor(wndFocused ? COLOR_HIGHLIGHT : COLOR_BTNFACE);
	 fgColor = GetSysColor(wndFocused ? COLOR_HIGHLIGHTTEXT : COLOR_BTNTEXT);
       } else {
	 bgColor = GetRowBackgroundColor(nRow,color) ? color : GetBkColor(); // GetTextBkColor?
	 fgColor = GetRowTextColor(nRow,color) ? color : GetTextColor();
       }

       // Draw background color
       GetCellRect(nRow, nCol, LVIR_BOUNDS, b);
       b.left++;
       b.bottom--;
       pDC->FillSolidRect(b, bgColor);
       r = b;

       // Draw image, if any.
       if(hasImage) {
	 UINT uFormat = ILD_TRANSPARENT;
	 if(itemSelected && wndFocused)
	   uFormat |= ILD_SELECTED;
	 int k = pDC->SaveDC();
	 pDC->IntersectClipRect(r);
	 POINT p = r.TopLeft();
	 
	 IMAGEINFO imInfo;
	 GetDrawingImageList()->GetImageInfo(lvi.iImage,&imInfo);
	 GetDrawingImageList()->Draw(pDC, lvi.iImage, p, uFormat);
	 pDC->RestoreDC(k);
	 r.top += 1;
       }

       // Draw text.
       GetCellRect(nRow, nCol, LVIR_LABEL, r);
       if(hasImage)		// Note that we ignore the label r.left, which is unreliable.
 	 r.left = b.left + IconSize + 2;
       else
	 r.left = b.left + 6;	// Indent of 6 seems excessive, but agrees with MS default.
       r.right = max(r.left, r.right - 6);
       r.top++;

		LOGFONT lf;
		HFONT hf, old;

		RtlZeroMemory(&lf, sizeof(lf));
		lstrcpyA((char*)lf.lfFaceName, m_strFontName);
		lf.lfHeight = m_iFontHeight;
		hf = CreateFontIndirect(&lf);
		old = (HFONT)pDC->SelectObject(hf);
		
		
       pDC->SetTextColor(fgColor);
       pDC->SetBkMode(TRANSPARENT);
       pDC->DrawText(GetItemText(nRow,nCol), r, GetTextFormat(nCol));
	   TEXTMETRIC  lpTextAtrib;
		pDC->GetTextMetrics(&lpTextAtrib);

	   pDC->SelectObject(old);
		DeleteObject(hf);
		//comment, Gensym-2037-TAM3-CH-BF-JIRA-46969-Tabular View Row Height doesn't work
		//if(m_rowHeight!=lpTextAtrib.tmAscent){
		//	SetRowHeight(lpTextAtrib.tmAscent);
		//
		//}
		


       // Draw focus rect for entire row, but clipped to current cell.
       if(wndFocused && itemFocused) {
	 GetItemRect(nRow, r, LVIR_BOUNDS);
	 r.left++;
	 r.bottom--;
	 int k = pDC->SaveDC();
	 pDC->IntersectClipRect(b);
	 pDC->DrawFocusRect(r);
	 pDC->RestoreDC(k);
       }

       *pResult = CDRF_SKIPDEFAULT;
       break;
     }
  }
}

// TODO: Maybe suppress these events for G2-initiated selections.
void G2TabularView::OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
  NMLISTVIEW *pLV = (NMLISTVIEW*)pNMHDR;

  if((pLV->uNewState & LVIS_SELECTED) != 
     (pLV->uOldState & LVIS_SELECTED)) {

    if(pLV->uNewState & LVIS_SELECTED)
      SendEvent(TBVE_SELECT, pLV->iItem);
    else
      SendEvent(TBVE_DESELECT, pLV->iItem);

    m_selectionChanged = TRUE;
  }
}

void G2TabularView::CheckSelectionChanged()
{
  if(m_selectionChanged)
    SendEvent(TBVE_SELECTION_CHANGED);
  m_selectionChanged = FALSE;
}

int G2TabularView::CompareItems(int nRowA, int nRowB)
{
  CString strA = GetItemText(nRowA, m_sortColumn);
  CString strB = GetItemText(nRowB, m_sortColumn);
  LPTSTR endA, endB;
  double valueA = _tcstod((LPCTSTR)strA, &endA);
  double valueB = _tcstod((LPCTSTR)strB, &endB);
  int rc;

  if(endA[0] == L'\0' && endB[0] == L'\0')
    rc = (valueA==valueB) ? 0 : (valueA<valueB) ? -1 : +1;
  else
    rc = _tcscmp(strA,strB);
  return m_sortAscending ? rc : -rc;
}

int CALLBACK G2TabularView::CompareProc(LPARAM index1, LPARAM index2, LPARAM lParam) // static
{
  return ((G2TabularView*)lParam)->CompareItems(index1, index2);
}

void G2TabularView::OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult)
{
  NMLISTVIEW *pNLV = (NMLISTVIEW*)pNMHDR;
  
  if(!IsSortable())
    return;

  if(m_sortColumn == pNLV->iSubItem)
    m_sortAscending = !m_sortAscending;
  else {
    m_sortColumn = pNLV->iSubItem;
    m_sortAscending = TRUE;
  }
  SortRows();
}

void G2TabularView::SortRows(int nCol, BOOL ascending)
{
  if(!IsSortable())
    return;

  if(0 <= nCol && nCol<GetColumnCount()) {
    m_sortColumn = nCol;
    m_sortAscending = ascending;
  }

  if(m_sortColumn < 0)
    return;

  SendMessage(LVM_SORTITEMSEX, (WPARAM)this, (LPARAM)CompareProc);
  UpdateSortArrows();
}

void G2TabularView::SetSortable(BOOL torf)
{
  if(torf == IsSortable())
    return;

  m_sortColumn = -1;
  m_sortAscending = FALSE;
  UpdateSortArrows();

  CHeaderCtrl *pHdr = GetHeaderCtrl();
  if(torf) {
    ModifyStyle(LVS_NOSORTHEADER, 0);
    pHdr->ModifyStyle(0, HDS_BUTTONS);
  } else {
    ModifyStyle(0, LVS_NOSORTHEADER);
    pHdr->ModifyStyle(HDS_BUTTONS, 0);
  }
}

BOOL G2TabularView::IsSortable()
{
  return (GetStyle() & LVS_NOSORTHEADER) == 0;
}

void G2TabularView::OnGetInfoTip(NMHDR *pNMHDR, LRESULT *pResult)
{
  NMLVGETINFOTIP *pInfoTip = (NMLVGETINFOTIP*)pNMHDR;
  _tcscpy(pInfoTip->pszText, _T("I am InfoTip"));
}

void G2TabularView::SaveSortColumn(int sortColumn)
{
	m_savedSortColumn = sortColumn;
}

void G2TabularView::SaveSortAscending(BOOL sortAscending)
{
	m_savedSortDirection = sortAscending;
}

int G2TabularView::GetSortColumn()
{
	return m_savedSortColumn;
}

BOOL G2TabularView::GetSortAscending()
{
	return m_savedSortDirection;
}

void G2TabularView::SetGridlineColor(COLORREF color)
{
  m_hasGridlineColor = 1;
  m_gridlinecolor = color;
}

COLORREF G2TabularView::GetGridlineColor()
{
  return m_gridlinecolor;
}

BOOL G2TabularView::HasGridLines()
{
  return m_hasGridLine;
}

BOOL G2TabularView::HasGridlineColor()
{
  return m_hasGridlineColor;
}



/*
 * Custom Dialogs Interface
 */

LPWSTR g2pvt_tabular_view_value(HWND hwnd)
{
  // If we return NULL, then "multi-updates" aren't done, which for some reason
  // causes instead multiple singleton updates, causing multiple calls to the
  // user's KB-level callback procedure. Foo. -fmw, 2/8/07
  return wcsdup(L"");
}




/*
 * Lisp Interface
 */

long g2ext_create_tabular_view(int handle, LPWSTR title,
			       long x, long y, long width, long height,
			       long dock, long neighbor,
				   int sortColumn, BOOL sortAscending)
{
  CMainFrame *pFrame = GetMainWnd();
  G2TabularView *pTV = new G2TabularView(handle);
  
  pTV->SaveSortColumn(sortColumn);
  pTV->SaveSortAscending(sortAscending);
  
  pTV->Create(WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS,
	      WinSize(width,height), pFrame, handle);
  // LVS_EX_HEADERDRAGDROP
  pTV->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
  pTV->SetGridLines(TRUE);
  if (pTV->HasGridLines() && pTV->HasGridlineColor())
    pTV->SetExtendedStyle(pTV->GetExtendedStyle() | LVS_EX_GRIDLINES);
  pTV->m_g2pointer = SavePtr(pTV->m_hWnd);  
  CSize min_size(0, 0);
  pFrame->WrapWnd(pTV, handle, x, y, width, height, dock, neighbor, min_size, title);

  return pTV->m_g2pointer;
}

long g2ext_manage_tabular_view(long opcode, long handle, long rowID,
			       LPWSTR strValue,
			       long argA, long argB, long argC)
{
  G2TabularView *pTV = FIND_WND(handle,G2TabularView);
  int nCol = rowID;		// For column operations
  BOOL torf = (argA == 1);
  COLORREF color = argA>=0 ? (COLORREF)argA : CLR_NONE;

  if(!pTV) return 0;

  switch(opcode) {
   case TBV_DESTROY:
     DESTROY_WND(handle);
     break;

   case TBV_INSERT_COLUMN:
     pTV->InsertColumn(nCol, strValue, argA, argB, argC); // label, alignment, width, icon
     break;

   case TBV_INSERT_ROW:
     pTV->InsertRow(argA, rowID, strValue, argB, argC, false); // positionID, rowID, text, fg, bg
     break;

   case TBV_CELL_TEXT:
     pTV->SetCellText(rowID, argA, strValue);
     break;

   case TBV_CELL_ICON:
     pTV->SetCellIcon(rowID, argA, argB); // argA=col, argB=icon
     break;

   case TBV_COLUMN_TEXT:
     pTV->SetColumnText(nCol, strValue);
     break;

   case TBV_COLUMN_ALIGNMENT:
     pTV->SetColumnAlignment(nCol, argA);
     break;

   case TBV_COLUMN_WIDTH:
     pTV->SetColumnWidth(nCol, argA);
     break;

   case TBV_COLUMN_ICON:
     pTV->SetColumnIcon(nCol, argA);
     break;

   case TBV_SETREDRAW:
     pTV->SetRedraw(torf);
     break;

   case TBV_BACKGROUND_COLOR:
     pTV->SetBkColor(color);
     pTV->SetTextBkColor(color);
     pTV->Invalidate();
     break;

   case TBV_TEXT_COLOR:
     pTV->SetTextColor(color);
     pTV->Invalidate();
     break;

   case TBV_ROW_HEIGHT:
     pTV->SetRowHeight(argA);
     break;

   case TBV_GRIDLINES:
     pTV->SetGridLines(torf);
     break;

   case TBV_SORTABLE:
     pTV->SetSortable(torf);
     break;

   case TBV_SINGLE_SELECTION:
     pTV->ModifyStyle(torf ? 0 : LVS_SINGLESEL, torf ? LVS_SINGLESEL : 0);
     break;

   case TBV_ROW_BACKGROUND_COLOR:
     pTV->SetRowBackgroundColor(rowID, color);
     break;

   case TBV_ROW_TEXT_COLOR:
     pTV->SetRowTextColor(rowID, color);
     break;

   case TBV_REMOVE_COLUMN:
     pTV->RemoveColumn(argA);
     break;

   case TBV_SELECT_ROW:
     pTV->SelectRow(rowID);
     break;

   case TBV_DESELECT_ROW:
     pTV->DeselectRow(rowID);
     break;

   case TBV_DESELECT_ALL_ROWS:
     pTV->DeselectAllRows();
     break;

   case TBV_REMOVE_ROW:
     pTV->DeleteRow(rowID);
     break;

   case TBV_REMOVE_ALL_ROWS:
     pTV->DeleteAllRows();
     break;

   case TBV_REMOVE_ALL_COLUMNS:
     pTV->RemoveAllColumns();
     break;

   case TBV_CHECK_SELECTION_CHANGED:
     pTV->CheckSelectionChanged();
     break;

   case TBV_SORT_ROWS:
     pTV->SortRows(nCol, torf);
     break;
	
   case TBV_INSERT_ROW_TO_TOP:
	   pTV->InsertRow(argA, rowID, strValue, argB, argC, true);
	   break;
   case TBV_GRIDLINE_COLOR:
	 pTV->SetExtendedStyle(pTV->GetExtendedStyle() & ~LVS_EX_GRIDLINES);
     pTV->SetGridlineColor(color);
     break;
   case TBV_CHANGE_SORT:	   pTV->SortRows(nCol, torf);	   break;   //Added by SoftServer
   case TBV_FONT_SIZE_CHANGE:	   
	  CString String(strValue);
	  int iVal = _ttoi(String);
	  pTV->SetRowTextFontSize(iVal);
      break;
  //End added by SoftServer
  }
  return 1;
}
