/**********************************************************************************************
 *                                                                                            *
 *  FILE: RGTreeCtrl.cpp                                                                      *
 *                                                                                            *
 *  DESCRIPTION:                                                                              *
 *       Implementation of the TreeCtrl class using the template CRGTreeT                     *
 *                                                                                            *
 *  Ren?Greiner                                                                              *
 *        eMail: rene.greiner@gmx.de                                                          *
 *                                                                                            *
 **********************************************************************************************/

#include "stdafx.h"
#include "RGTreeCtrl.h"
#include "RGTreeT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GetWindowStyle(hwnd)            GetWindowLong( hwnd, GWL_STYLE)

#define ID_EDIT                    1211
#define ID_EDIT_TIMER            1345
#define ID_SHOW_TIMER            1346

#define PSNDMSG(hwnd, msg, wParam, lParam)  SNDMSG( GetParent(hwnd), msg, (WPARAM)wParam, (LPARAM)lParam)

#define PSNDNMSG(hwnd, nmh, msg)\
                        (    nmh.hdr.hwndFrom = hwnd,\
                            nmh.hdr.code = msg,\
                            nmh.hdr.idFrom = GetDlgCtrlID(hwnd),\
                            PSNDMSG(hwnd, WM_NOTIFY, nmh.hdr.idFrom, &nmh))

#define PT_FILL(pt, lParam) {pt.x = LOWORD(lParam); pt.y = HIWORD(lParam);}

struct TREE_MAP_STRUCT;
void _SetIndent(TREE_MAP_STRUCT *ptms, UINT nIndent);
HTREEITEM GetNextItem( TREE_MAP_STRUCT *ptms, HTREEITEM hItem, UINT flag);
bool EndEditLabelNow( TREE_MAP_STRUCT *ptms, BOOL fCancel);
bool GetItemRect(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, LPRECT lpRect, BOOL bTextOnly);
void ComputeMaxWidth( TREE_MAP_STRUCT *ptms);

#define SYS_COLOR_LINES GetSysColor(COLOR_GRAYTEXT)
#define BACK_FROM_INDEXTOSTATEIMAGEMASK(i) ((i) >> 12)
#define ITEM_HAS_BUTTON(ptms, bTreeHasButtons, hItem) (bTreeHasButtons && GetNextItem( ptms, hItem, TVGN_CHILD) != NULL)
#define ITEM_TEXT_X_OFFSET 2
#define ITEM_TEXT_X_R2LOFFSET(TextSizeX) (TextSizeX + 2 * ITEM_TEXT_X_OFFSET)


/**************************************************************************
 *                                                                        *
 *                                    TREE EDIT                           *
 *                                                                        *
 **************************************************************************/

IMPLEMENT_DYNCREATE(CRGTreeCtrl, CTreeCtrl)

typedef struct
{
    WNDPROC pOldWndProc;
    CRect        rcItem;
    RECT        rcParent;
} TREE_EDIT_STRUCT;

#ifdef RG_TREE_WITH_EDIT_MAP
static CMap<HWND, HWND, TREE_EDIT_STRUCT*, TREE_EDIT_STRUCT*>  TreeEditMap;
#endif

static LRESULT CALLBACK RGTreeEditWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    TREE_EDIT_STRUCT *ptes;
#ifdef RG_TREE_WITH_EDIT_MAP
    TreeEditMap.Lookup( hwnd, ptes);
#else
    ptes = (TREE_EDIT_STRUCT*)GetWindowLong( hwnd, GWL_USERDATA);
#endif

    switch( uMsg)
    {
        case WM_CREATE:
            {
                LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
                ptes = new TREE_EDIT_STRUCT;
                ptes->pOldWndProc = (WNDPROC)SetWindowLong( hwnd, GWL_WNDPROC, (LPARAM)RGTreeEditWindowProc);
#ifdef RG_TREE_WITH_EDIT_MAP
                TreeEditMap.SetAt( hwnd, ptes);
#else
                SetWindowLong( hwnd, GWL_USERDATA, (LONG)ptes);
#endif
            }
            return 0;
        case WM_CHAR:
            {
                HDC hDC = GetDC( hwnd);
                HGDIOBJ hOldFont = SelectObject( hDC, (HFONT)SNDMSG( hwnd, WM_GETFONT, 0, 0));
                _TCHAR str[MAX_PATH];
                SIZE size;
                VERIFY(GetTextExtentPoint( hDC, str, GetWindowText( hwnd, str, MAX_PATH), &size));
                if( wParam == VK_CLEAR)
                {
                    if( size.cx > ptes->rcItem.Width())
                        SetWindowPos( hwnd, NULL, ptes->rcItem.left, ptes->rcItem.top, size.cx, ptes->rcItem.Height(), SWP_NOMOVE|SWP_NOZORDER);
                    else
                        SetWindowPos( hwnd, NULL, ptes->rcItem.left, ptes->rcItem.top, ptes->rcItem.Width(), ptes->rcItem.Height(), SWP_NOMOVE|SWP_NOZORDER);
                }
                else
                {
                    size.cx += 16;
                    if( (ptes->rcItem.Width() < size.cx) && (ptes->rcItem.left+size.cx < ptes->rcParent.right))
                        SetWindowPos( hwnd, NULL, ptes->rcItem.left, ptes->rcItem.top, size.cx, ptes->rcItem.Height(), SWP_NOMOVE|SWP_NOZORDER);
                }
                SelectObject( hDC, hOldFont);
                ReleaseDC( hwnd, hDC);
                if(wParam == VK_RETURN
                    || wParam == VK_ESCAPE)
                    return 0;
                break;
            }
        case WM_KEYDOWN:
            switch( wParam)
            {
                case VK_RETURN:        
                    PSNDMSG(hwnd, TVM_ENDEDITLABELNOW, FALSE, 0);        
                    return 0;
                case VK_ESCAPE:        
                    PSNDMSG(hwnd, TVM_ENDEDITLABELNOW, TRUE, 0);            
                    return 0;
            }
            break;
        case WM_KILLFOCUS:        
            PSNDMSG(hwnd, TVM_ENDEDITLABELNOW, FALSE, 0);
            break;
        case WM_NCDESTROY:
            {
                LRESULT lResult = ::CallWindowProc( ptes->pOldWndProc, hwnd, uMsg, wParam, lParam);
                SetWindowLong( hwnd, GWL_WNDPROC, (LONG)ptes->pOldWndProc);
                delete ptes;
#ifdef RG_TREE_WITH_EDIT_MAP
                TreeEditMap.RemoveKey( hwnd);
#endif
                return lResult;
            }
    }
    return CallWindowProc( ptes->pOldWndProc, hwnd, uMsg, wParam, lParam);
}

static void SetEditPosition( HWND hwnd, const RECT& rcItem, const RECT& rcParent)
{
    TREE_EDIT_STRUCT *ptes;
#ifdef RG_TREE_WITH_EDIT_MAP
    if( TreeEditMap.Lookup( hwnd, ptes))
#else
    ptes = (TREE_EDIT_STRUCT*)GetWindowLong( hwnd, GWL_USERDATA);
    if(ptes)
#endif
    {
        ptes->rcItem = rcItem;
        ptes->rcParent = rcParent;
    }
}

/**************************************************************************
 *                                                                        *
 *                                RGTREE CTRL                             *
 *                                                                        *
 **************************************************************************/

template<class _T> class CRGTreeT;

#pragma pack( push, 4)

typedef struct tagRGTVIITEM
{
    UINT        state;
    LPTSTR    pszText;
    int            cchTextMax;
    int            iImage;
    int            iSelectedImage;
    LPARAM    lParam;

    unsigned short ItemTextWidth; //saved for speed enhancement

} RGTVITEM, *LPRGTVITEM;

typedef CRGTreeT<RGTVITEM> _rgTree;

struct TREE_MAP_STRUCT
{
    HWND                            hwnd;
    WNDPROC                        pOldWndProc;
    _rgTree                        rgTree;
    int                                nVisibleItemCount;
	int							       nScrollMax;
    int                                nMaxWidth;
    int                                nHPageWidth;
    int                                nVScrollPos;
    int                                nHScrollPos;
    HTREEITEM                    hItemFirstVisible;
    HTREEITEM                    hItemSelected;
    HTREEITEM                    hItemEditing;
    HTREEITEM                    hDropHilite;
    HWND                            hWndEdit;
    bool                            bRedrawFlag;
    UINT                            nItemHeight;

    UINT m_nIndent;
    UINT m_nButtonSize;
    UINT m_nButtonIndent;
    UINT m_nSignSize;

    HIMAGELIST m_hNormalImageList;
    HIMAGELIST m_hStateImageList;

    bool bInSetScrollBars;
    bool bInSetScrollBarsDoRedraw;

    HTREEITEM hItemPressed; //item is pressed by left or right mouse button
    bool bIsPressed; //because hItemPressed can be programaticaly changed to null    
    bool bPressedLeft; //was pressed by left or right mouse button,
    POINT ptPressed; //mouse coordinate when item was mouse button pressed
    HTREEITEM hItemOrigPressed; //because of possible hilite changes made by client

    TREE_MAP_STRUCT()
    {
        nScrollMax = nVisibleItemCount = nMaxWidth = nHPageWidth = nVScrollPos = nHScrollPos = 0;
        hItemFirstVisible = hItemSelected = hItemEditing = hDropHilite = NULL;
        bRedrawFlag = true;
        nItemHeight = 0;

        m_hNormalImageList = NULL;
        m_hStateImageList = NULL;

        hItemOrigPressed = hItemPressed = NULL;
        bIsPressed = false;
        PT_FILL(ptPressed, 0);

        bInSetScrollBars = false;
        bInSetScrollBarsDoRedraw = false;

        hwnd = NULL;
        _SetIndent(this, 19);
    }
};

#pragma pack( pop)

/**************************************************************************
 *                                                                        *
 *                           Helper functions                             *
 *                                                                        *
 **************************************************************************/

static void SetTVITEMforNotify(TREE_MAP_STRUCT *ptms, TVITEM *pTvitem, HTREEITEM hItem, int mask)
{
    if(hItem)
    {
        RGTVITEM *pItem = ptms->rgTree.GetAt((POSITION)hItem);

        pTvitem->mask = mask;

        ASSERT((mask & ~(TVIF_STATE | TVIF_PARAM | TVIF_HANDLE)) == 0);

        if(mask & TVIF_STATE)
            pTvitem->state = pItem->state;
        if(mask & TVIF_HANDLE)
            pTvitem->hItem = hItem;
        if(mask & TVIF_PARAM)
            pTvitem->lParam = pItem->lParam;
    }
    else
    {
        pTvitem->mask = 0;
        pTvitem->hItem = NULL;
    }
}

static void SetNMTREEVIEWforSELCHANGE(TREE_MAP_STRUCT *ptms, NMTREEVIEW *pNmtv, int action, HTREEITEM hItemOld, HTREEITEM hItemNew)
{
    pNmtv->action = action;
    SetTVITEMforNotify(ptms, &pNmtv->itemOld, hItemOld, TVIF_STATE | TVIF_PARAM | TVIF_HANDLE);
    SetTVITEMforNotify(ptms, &pNmtv->itemNew, hItemNew, TVIF_STATE | TVIF_PARAM | TVIF_HANDLE);
}

static HIMAGELIST GetImageList(TREE_MAP_STRUCT *ptms, UINT iImage)
{
    if(iImage == TVSIL_NORMAL)
        return ptms->m_hNormalImageList;
    else
        return ptms->m_hStateImageList;
}

static UINT GetItemHeight(TREE_MAP_STRUCT *ptms)
{
    if(ptms->nItemHeight == 0)
    {
        TEXTMETRIC tm;
        {
            //PAINTSTRUCT ps;
            HDC hDC = GetDC(ptms->hwnd); //BeginPaint( hwnd, &ps);
            HGDIOBJ hFont = (HFONT)(SNDMSG(ptms->hwnd, WM_GETFONT, 0, 0));
            HGDIOBJ hOldFont = SelectObject(hDC, hFont);
            GetTextMetrics(hDC, &tm);
            SelectObject(hDC, hOldFont);
            ReleaseDC(ptms->hwnd, hDC); //EndPaint( hwnd, &ps);
        }
        
        UINT nItemHeight = tm.tmHeight + 2;
        nItemHeight += nItemHeight % 2;
        
        HIMAGELIST hNormalImageList = GetImageList(ptms, TVSIL_NORMAL);
        if(hNormalImageList != NULL)
        {
            //all images in image list have the same size
            int cx, cy;
            if(ImageList_GetIconSize(hNormalImageList, &cx, &cy) != false)
            {            
                UINT nImageHeight = cy;
                
                if(nImageHeight > nItemHeight)
                {
                    nItemHeight = nImageHeight;
                }
            }
        }

        ptms->nItemHeight = nItemHeight;
    }

    return ptms->nItemHeight;
}

static UINT GetVisibleCount(TREE_MAP_STRUCT *ptms)
{
    RECT rc;
    GetClientRect(ptms->hwnd, &rc);
    UINT nItemHeight = GetItemHeight(ptms);
    return (rc.bottom - rc.top) / nItemHeight;
}

//returns: was made redraw
static bool SETSCROLLBARS(TREE_MAP_STRUCT *ptms)                                                                                
{ 
    bool old = ptms->bInSetScrollBars;
    ptms->bInSetScrollBars = true;

    ComputeMaxWidth(ptms);


    SCROLLINFO si, sio;
    si.cbSize = sio.cbSize = sizeof(SCROLLINFO);
    si.fMask = sio.fMask = SIF_RANGE|SIF_PAGE|SIF_POS;
    si.nMin = 0;


    GetScrollInfo( ptms->hwnd, SB_VERT, &sio);

    // GENSYMCID-593: Scrollbar problems for tree view in TwNg
    // Use Visible Item count to make the scrollbar autoresizable
    si.nMax = ptms->nVisibleItemCount > 0 ? ptms->nVisibleItemCount - 1 : 0;
    si.nPage = GetVisibleCount(ptms);
    si.nPos = ptms->nVScrollPos;
    
    if(si.nMin != sio.nMin
        || si.nMax != sio.nMax
        || si.nPage != sio.nPage
        || si.nPos != sio.nPos)
        SetScrollInfo( ptms->hwnd, SB_VERT, &si, TRUE);


    GetScrollInfo( ptms->hwnd, SB_HORZ, &sio);

    RECT rc;
    GetClientRect(ptms->hwnd, &rc);
    ASSERT(rc.left == 0);
    si.nMax = ptms->nMaxWidth > 0 ? ptms->nMaxWidth - 1 : 0;
    si.nPage = rc.right;
    si.nPos = ptms->nHScrollPos;                                        

    if(si.nMin != sio.nMin
        || si.nMax != sio.nMax
        || si.nPage != sio.nPage
        || si.nPos != sio.nPos)
        SetScrollInfo( ptms->hwnd, SB_HORZ, &si, TRUE);


    ptms->bInSetScrollBars = old;

    if(ptms->bInSetScrollBars == false
        && ptms->bInSetScrollBarsDoRedraw)
    {
        RedrawWindow( ptms->hwnd, NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE);
        ptms->bInSetScrollBarsDoRedraw = false;
        return true;
    }

    return false;
}

//fills .left and .right only
static void GetFullItemWidth( HWND hwnd, LPRECT lpRect)
{
    RECT rc;
    GetClientRect(hwnd, &rc);
    lpRect->left = rc.left;
    lpRect->right = rc.right;
}

static void InvalidateItemRect(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, BOOL bErase = TRUE)
{
    RECT rc;
    if(GetItemRect( ptms, hItem, &rc, FALSE))
        InvalidateRect( ptms->hwnd, &rc, bErase);
}

//will be called by SetImageList(TVSIL_NORMAL)
static void _SetNormalImageList(TREE_MAP_STRUCT *ptms)
{
    HIMAGELIST hNormalImageList = GetImageList(ptms, TVSIL_NORMAL);

    UINT nImageWidth;
    UINT nIndent;

    //all images in image list have the same size
    int cx, cy;
    if(ImageList_GetIconSize(hNormalImageList, &cx, &cy) == false)
    {
        nIndent = 0;
    }
    else
    {            
        nImageWidth = cx;

        nIndent = nImageWidth + 3;
    }

    if(nIndent < 19)
        nIndent = 19;

    _SetIndent(ptms, nIndent);

    ptms->nItemHeight = 0; //will be recomputed
}

//will be called by SetIndent()
static void _SetIndent(TREE_MAP_STRUCT *ptms, UINT nIndent)
{
    ptms->m_nIndent = (nIndent < 15) ? 15 : nIndent;

    HIMAGELIST hNormalImageList = 
        ptms->hwnd == NULL ? NULL : GetImageList(ptms, TVSIL_NORMAL);
    if(hNormalImageList == NULL)
    {
        ptms->m_nButtonSize = (ptms->m_nIndent > 15) ? 9 : 7;
        ptms->m_nButtonIndent = (ptms->m_nButtonSize < 9) ? 4 : (ptms->m_nIndent - 8) / 2;
        ptms->m_nSignSize = 2;
    }
    else
    {
        UINT nButtonCentre;
        UINT nImageMinSize;

        //all images in image list have the same size
        int cx, cy;
        if(ImageList_GetIconSize(hNormalImageList, &cx, &cy) == false)
        {
            //nImageWidth = 0;
            nImageMinSize = 0;
            nButtonCentre = 0;
        }
        else
        {            
            UINT nImageWidth;
            UINT nImageHeight;
            nImageWidth = cx;
            nImageHeight = cy;

            if(nImageWidth < nImageHeight)
                nImageMinSize = nImageWidth;
            else
                nImageMinSize = nImageHeight;

            nButtonCentre = nImageWidth / 2;
        }

        ptms->m_nButtonSize = (nImageMinSize / 4 ) * 2 + 1;
                                
        ptms->m_nButtonIndent = nButtonCentre - ptms->m_nButtonSize/2;

        if(ptms->m_nButtonSize < 3)
            ptms->m_nSignSize = 0;
        else
            if(ptms->m_nButtonSize < 5)
                ptms->m_nSignSize = 1;
            else
                if(ptms->m_nButtonSize < 11)
                    ptms->m_nSignSize = 2;
                else
                    if(ptms->m_nButtonSize < 13)
                        ptms->m_nSignSize = 3;
                    else
                        if(ptms->m_nButtonSize < 17)
                            ptms->m_nSignSize = 4;
                        else
                            ptms->m_nSignSize = ptms->m_nButtonSize / 3;

        UINT nMinIndent = ptms->m_nButtonSize + 2 * ptms->m_nButtonIndent;
        if(ptms->m_nIndent < nMinIndent)
            ptms->m_nIndent = nMinIndent;
    }
}

static UINT __GetItemVisibleIndex(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, bool bPrev, UINT SearchOnly)
{
    UINT nIndex;
    HTREEITEM hIndexItem;

    nIndex = 0;
    hIndexItem = ptms->hItemFirstVisible;
    while(hIndexItem != NULL)
    {
        if(hIndexItem == hItem)
        {
            nIndex += ptms->nVScrollPos;
            return nIndex;
        }

        if(SearchOnly == nIndex)
            return -1;
        
        hIndexItem = GetNextItem( ptms, hIndexItem, bPrev ? TVGN_PREVIOUSVISIBLE : TVGN_NEXTVISIBLE);

        bPrev ? nIndex-- : nIndex++;
    }

    return -1;
}

//root item has 0 index, next depends on visiblility of items
//return -1 for unvisible item
static UINT GetItemVisibleIndex(TREE_MAP_STRUCT *ptms, HTREEITEM hItem)
{
    UINT nIndex;
    HTREEITEM hIndexItem;

    if(ptms->nVisibleItemCount > 1000) //try from first visible
    {
        int SearchOnly = GetVisibleCount(ptms) + 1;

        nIndex = __GetItemVisibleIndex(ptms, hItem, false, SearchOnly * 2);
        if(nIndex != -1)
            return nIndex;

        nIndex = __GetItemVisibleIndex(ptms, hItem, true, SearchOnly);
        if(nIndex != -1)
            return nIndex;
    }

    nIndex = 0;
    hIndexItem = GetNextItem(ptms, NULL, TVGN_ROOT);
    while(hIndexItem != NULL)
    {
        if(hIndexItem == hItem)
        {
            return nIndex;
        }

        hIndexItem = GetNextItem(ptms, hIndexItem, TVGN_NEXTVISIBLE);

        nIndex++;
    }

    return -1; //wrong input
}

static bool IsItemVisible( _rgTree& rgTree, POSITION pos)
{
    while( pos = rgTree.GetParentPosition( pos))
        if( (rgTree.GetAt( pos)->state & TVIS_EXPANDED) == 0)
            return false;
    return true;
}

//for pos == NULL returns 0
static void _AddVisibleChildCount( _rgTree& rgTree, POSITION pos, UINT& nCount)
{
    for( ; pos;    pos=rgTree.GetNextPosition( pos))
    {
        nCount += 1; /* this item */
        if( rgTree.GetAt(pos)->state & TVIS_EXPANDED)
        {
            _AddVisibleChildCount( rgTree, rgTree.GetChildPosition(pos), nCount);
        }
    }
}

static void AddVisibleChildCount( _rgTree& rgTree, POSITION pos, UINT& nCount)
{
    if( rgTree.GetAt(pos)->state & TVIS_EXPANDED)
        _AddVisibleChildCount( rgTree, rgTree.GetChildPosition(pos), nCount);
}

static void SetFirstVisibleItem( TREE_MAP_STRUCT *ptms, HTREEITEM hItem)
{
    HTREEITEM hItemStart = ptms->hItemFirstVisible;
    HTREEITEM hItemRoot = GetNextItem( ptms, NULL, TVGN_ROOT);
    if( hItemStart == NULL)
    {
        hItemStart = hItemRoot;
        ptms->nVScrollPos = 0;
    }
    if(hItem != NULL)
    {
        ASSERT(IsItemVisible(ptms->rgTree, (POSITION)hItem));

        HTREEITEM hItem2, hLastItem2;
        int ndVScrollPos = 0;
        
        for(hLastItem2 = hItem2 = hItem; true; hItem2 = GetNextItem( ptms, hLastItem2, TVGN_PREVIOUS))
        {
            if(hItem2 == NULL)
            {
                //move to deeper to parents
                hItem2 = GetNextItem( ptms, hLastItem2, TVGN_PARENT);
                if(hItem2 == NULL)
                {
                    break; //from for
                }
            }
            else
            {
                UINT nCount = 0;
                if(hItem2 != hItem)
                    AddVisibleChildCount(ptms->rgTree, (POSITION)hItem2, nCount);

                ndVScrollPos += nCount;
            }

            if(hItem2 == hItemStart
                || hItem2 == hItemRoot)
            {
                break; //from for
            }

            ndVScrollPos += 1 /* this item */;

            hLastItem2 = hItem2;
        }

        if(hItem2 == hItemStart)
        {
            ptms->nVScrollPos += ndVScrollPos;
        }
        else
        {
            ptms->nVScrollPos = ndVScrollPos;
        }

#ifdef _DEBUG
        hItemStart = hItemRoot;
        for(ndVScrollPos = 0 ; hItemStart != hItem; hItemStart = GetNextItem( ptms, hItemStart, TVGN_NEXTVISIBLE))
        {
            ASSERT(hItemStart != NULL);
            ndVScrollPos++;
        }
        ASSERT(ndVScrollPos == ptms->nVScrollPos);
#endif
    }
    else
    {
        ASSERT(ptms->nVScrollPos == 0);
        //ASSERT(hItemStart == NULL);
    }
    ptms->hItemFirstVisible = hItem;
}

static int CALLBACK Compare( LPARAM lParam1, LPARAM lParam2)
{
    return _tcsicmp( ((LPRGTVITEM)lParam1)->pszText, ((LPRGTVITEM)lParam2)->pszText);
}

static void CALLBACK OnDelete( POSITION pos, LPARAM lParam)
{
    TREE_MAP_STRUCT *ptms = (TREE_MAP_STRUCT*)lParam;
    LPRGTVITEM pItemData = ptms->rgTree.GetAt( pos);
    NMTREEVIEW nmtv;
    SetTVITEMforNotify(ptms, &nmtv.itemOld, (HTREEITEM)pos, TVIF_PARAM | TVIF_HANDLE);
    HWND& hwnd = ptms->hwnd;
    PSNDNMSG(hwnd, nmtv, TVN_DELETEITEM);
    delete[] pItemData->pszText;
}

//root item has 0, its child 1, ...
static UINT GetItemChildLevel(TREE_MAP_STRUCT *ptms, HTREEITEM hItem)
{
    ASSERT(hItem != NULL);
    UINT nLevel = 0;
    while(hItem)
    {
        nLevel++;
        hItem = GetNextItem( ptms, hItem, TVGN_PARENT);
    }
    return nLevel - 1;
}

//for dotted line draw
struct LINEDDAPARAM
{
    HDC        hDC;
    bool    bSet;
};
static void __stdcall LineDDAProc( int x, int y, LPARAM lParam)
{
    LINEDDAPARAM *pParam = (LINEDDAPARAM*)lParam;
    if( pParam->bSet)
        SetPixelV( pParam->hDC, x, y, SYS_COLOR_LINES);
    pParam->bSet = !pParam->bSet;
}

class GetItemTextRectCache
{
public:
    bool m_bHasLinesAtRootInitialized;
    bool m_bHasLinesAtRoot;

    bool m_bStateImageSizeInitialized;
    CSize m_StateImageSize;

    bool m_bNormalImageSizeInitialized;
    CSize m_NormalImageSize;

    HWND m_hWnd;
    HDC m_hDC;
    HGDIOBJ m_hFont;
    HGDIOBJ m_hBoldFont;
    HGDIOBJ m_hOldFont;
    bool m_bBoldSelected;

    GetItemTextRectCache(HWND hWnd)
    {
        m_bHasLinesAtRootInitialized = false;
        m_bStateImageSizeInitialized = false;
        m_bNormalImageSizeInitialized = false;       

        m_hWnd = hWnd;
        m_hDC = NULL;
        m_hFont = NULL;
        m_hBoldFont = NULL;
        m_hOldFont = NULL;
        m_bBoldSelected = false;
    }

    ~GetItemTextRectCache()
    {
        if(m_hDC)
        {
            if(m_hOldFont)
            {
                SelectObject(m_hDC, m_hOldFont);
            }
            
            ReleaseDC(m_hWnd, m_hDC);
        }

        if(m_hBoldFont)
        {
            DeleteObject(m_hBoldFont);
        }        
    }

    bool HasLinesAtRoot()
    {
        if(m_bHasLinesAtRootInitialized == false)
        {
            m_bHasLinesAtRoot = (GetWindowStyle(m_hWnd) & TVS_LINESATROOT) != 0;
            m_bHasLinesAtRootInitialized = true;
        }

        return m_bHasLinesAtRoot;
    }

    CSize GetStateImageSize(TREE_MAP_STRUCT *ptms)
    {
        if(m_bStateImageSizeInitialized == false)
        {
            HIMAGELIST hStateImageList = GetImageList(ptms, TVSIL_STATE);
            if(hStateImageList == NULL)
                m_StateImageSize = CSize(0, 0);
            else
            {           
                //all images in image list have the same size
                int cx, cy;
                if(ImageList_GetIconSize(hStateImageList, &cx, &cy) == false)
                {
                    return CSize(0, 0);
                }
                
                m_StateImageSize = CSize(cx, cy);
            }
            
            m_bStateImageSizeInitialized = true;
        }

        return m_StateImageSize;
    }

    CSize GetNormalImageSizeAndOffset(TREE_MAP_STRUCT *ptms)
    {
        if(m_bNormalImageSizeInitialized == false)
        {
            HIMAGELIST hNormalImageList = GetImageList(ptms, TVSIL_NORMAL);
            if(hNormalImageList == NULL)
                m_NormalImageSize = CSize(0, 0);
            else
            {                
                //all images in image list have the same size
                int cx, cy;
                if(ImageList_GetIconSize(hNormalImageList, &cx, &cy) == false)
                    return CSize(0, 0);
                
                m_NormalImageSize = CSize(cx + 3 /* offset */, cy);
            }
            
            m_bNormalImageSizeInitialized = true;
        }

        return m_NormalImageSize;
    }

    void DCInitialize()
    {
        m_hDC = GetDC(m_hWnd);
		if(m_hDC)
			m_hFont = (HFONT)(SNDMSG(m_hWnd, WM_GETFONT, 0, 0));
    }

    void SetNormal()
    {
        if(m_hDC == NULL)
        {
            DCInitialize();
            ASSERT(m_bBoldSelected == false);
            HGDIOBJ hOldFont = SelectObject(m_hDC, m_hFont);
            if(m_hOldFont == NULL)
            {
                m_hOldFont = hOldFont;
            }
        }

        if(m_bBoldSelected == true)
        {
            HGDIOBJ hOldFont = SelectObject(m_hDC, m_hFont);
            if(m_hOldFont == NULL)
            {
                m_hOldFont = hOldFont;
            }
            m_bBoldSelected = false;
        }
    }
    
    void SetBold()
    {
        if(m_hDC == NULL)
        {
            DCInitialize();
            ASSERT(m_bBoldSelected == false);
        }

        if(m_bBoldSelected == false)
        {
            if(m_hBoldFont == NULL)
            {
                ASSERT(m_hFont != NULL);

                LOGFONT LogFont;
                GetObject(m_hFont, sizeof(LOGFONT), &LogFont);
                LogFont.lfWeight = FW_BOLD;
                m_hBoldFont = CreateFontIndirect(&LogFont);
            }
            
            HGDIOBJ hOldFont = SelectObject(m_hDC, m_hBoldFont);
            if(m_hOldFont == NULL)
            {
                m_hOldFont = hOldFont;
            }
            m_bBoldSelected = true;
        }
    }
};

//x offset where starts item draw (+/- sign or icon or text)
static UINT _GetBasicIndent(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, GetItemTextRectCache *pCache)
{
    UINT nLevel = GetItemChildLevel(ptms, hItem);
    UINT nIndent = ptms->m_nIndent * nLevel;
    if(pCache->HasLinesAtRoot())
    {
        nIndent += ptms->m_nIndent;
    }

    return nIndent;
}

static CSize _GetStateImageSize(TREE_MAP_STRUCT *ptms, LPRGTVITEM pItem, GetItemTextRectCache *pCache)
{
    if((pItem->state & TVIS_STATEIMAGEMASK) == 0)
        return CSize(0, 0);

    return pCache->GetStateImageSize(ptms);
}

static CSize _GetNormalImageSizeAndOffset(TREE_MAP_STRUCT *ptms, GetItemTextRectCache *pCache)
{
    return pCache->GetNormalImageSizeAndOffset(ptms);
}

static int _GetItemTextWidth(TREE_MAP_STRUCT *ptms, LPRGTVITEM pItem, GetItemTextRectCache *pCache)
{
    if(pItem->ItemTextWidth == 0)
    {
        if(pItem->state & TVIS_BOLD)
        {
            pCache->SetBold();
        }
        else
        {
            pCache->SetNormal();
        }
        
        SIZE TextSize;
        VERIFY(GetTextExtentPoint(pCache->m_hDC, pItem->pszText, pItem->cchTextMax, &TextSize));

        pItem->ItemTextWidth = (unsigned short)TextSize.cx;
        ASSERT(pItem->ItemTextWidth == TextSize.cx);
    }

    return pItem->ItemTextWidth;
}

//fills x coordinates only, y takes from lpFullItemRect
static void _GetItemTextRect(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, LPRGTVITEM pItem,
                             LPRECT lpFullItemRect, LPRECT lpItemTextRect, GetItemTextRectCache *pCache)
{
    *lpItemTextRect = *lpFullItemRect;

    lpItemTextRect->left = -ptms->nHScrollPos;

    lpItemTextRect->left += _GetBasicIndent(ptms, hItem, pCache);

    lpItemTextRect->left += _GetStateImageSize(ptms, pItem, pCache).cx;

    lpItemTextRect->left += _GetNormalImageSizeAndOffset(ptms, pCache).cx;

    int TextSize = _GetItemTextWidth(ptms, pItem, pCache);
    lpItemTextRect->right = lpItemTextRect->left + ITEM_TEXT_X_R2LOFFSET(TextSize);
}

static void _GetItemTextRect(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, LPRGTVITEM pItem, LPRECT lpFullItemRect, LPRECT lpItemTextRect)
{
    GetItemTextRectCache Cache(ptms->hwnd);
    _GetItemTextRect(ptms, hItem, pItem, lpFullItemRect, lpItemTextRect, &Cache);
}

static bool _GetItemRect(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, LPRECT lpRect, BOOL bTextOnly, UINT nItemHeight)
{
    ASSERT(hItem != NULL);

    UINT nItemVisibleIndex = GetItemVisibleIndex(ptms, hItem);
    if(nItemVisibleIndex == -1)
        return false;

    GetFullItemWidth(ptms->hwnd, lpRect);

    lpRect->top = (nItemVisibleIndex - ptms->nVScrollPos) * nItemHeight;
    lpRect->bottom = lpRect->top + nItemHeight;

    if(bTextOnly)
    {
        RGTVITEM *pItem = ptms->rgTree.GetAt((POSITION)hItem);
        _GetItemTextRect(ptms, hItem, pItem, lpRect, lpRect);
    }

    return true;
}

static void ComputeButtonCentre(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, RECT& rFullItemRect, POINT& ButtonCentre, GetItemTextRectCache *pCache)
{
    ButtonCentre.x = -ptms->nHScrollPos + _GetBasicIndent(ptms, hItem, pCache) - ptms->m_nIndent + ptms->m_nButtonIndent + ptms->m_nButtonSize/2;
    ButtonCentre.y = (rFullItemRect.top - rFullItemRect.bottom)/2 + rFullItemRect.bottom;
}

//function supposed both lines are visible and one is before two
//returns how many lines you must move to get from one to two
static int GetLineOffsetOfItems(TREE_MAP_STRUCT *ptms, HTREEITEM hItemOne, HTREEITEM hItemTwo)
{
    int offset = 0;
	//[tam.srogatch][2010-09-15]: This function was a performance bottleneck
    //HTREEITEM hTempItem = hItemOne;
    //while(hTempItem != hItemTwo)
    //{
    //    hTempItem =  GetNextItem( ptms, hTempItem, TVGN_NEXTVISIBLE);
    //    ASSERT(hTempItem != NULL);
    //    if(hTempItem == NULL)
    //        return -1; //not expected input
    //    offset ++;
    //}
	int i1 = GetItemVisibleIndex(ptms, hItemOne);
	int i2 = GetItemVisibleIndex(ptms, hItemTwo);
	if( i2 < i1 ) {
		offset = -1;
	} else {
		offset = i2-i1;
	}

    return offset;
}

static void DrawDottedLine(HDC hDC, int xSrc, int ySrc, int xDest, int yDest) {
	LOGBRUSH logBrush;
	logBrush.lbColor = SYS_COLOR_LINES;
	logBrush.lbStyle = PS_SOLID;
	HBRUSH hBrush = CreateBrushIndirect( &logBrush );
	HPEN hPen = ExtCreatePen( PS_COSMETIC | PS_ALTERNATE, 1, &logBrush, 0, NULL );
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	POINT pts[2] = { {xSrc, ySrc}, {xDest, yDest} };
	Polyline( hDC, pts, 2 );
	SelectObject(hDC, hOldBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

static void DrawFromItemLines(HDC hDC, TREE_MAP_STRUCT *ptms, bool bHasButtons,
                      HTREEITEM hItem, RECT& rItemTextRect, POINT& ButtonCentre,
                      HTREEITEM hParentItem, UINT nItemHeight,
                      SIZE& NormalImageSizeAndOffset, SIZE& StateImageSize)
{      
	//[tam.srogatch][2010-09-15]: 24% of TWNG time was spent in drawing
    //LINEDDAPARAM ddaParam;
    //ddaParam.hDC = hDC;
    //ddaParam.bSet = false;

    //LineDDA(rItemTextRect.left - 1 - StateImageSize.cx - NormalImageSizeAndOffset.cx, ButtonCentre.y,
    //    ButtonCentre.x, ButtonCentre.y, LineDDAProc, (LPARAM)&ddaParam);
    DrawDottedLine(hDC, rItemTextRect.left - 1 - StateImageSize.cx - NormalImageSizeAndOffset.cx, ButtonCentre.y,
        ButtonCentre.x, ButtonCentre.y);
    

    HTREEITEM hToItem = GetNextItem( ptms, hItem, TVGN_PREVIOUS);
    if(hToItem == NULL)
    {
        hToItem = hParentItem;
    }
    if(hToItem != NULL)
    {
        //in large data can quicker to get to hToItem from hItem than from TVI_ROOT
        int rToItemTextRectbottom = rItemTextRect.bottom;
        rToItemTextRectbottom -= nItemHeight
            * GetLineOffsetOfItems(ptms, hToItem, hItem);

        int ToY;
        if(hToItem == hParentItem)
        {
            ToY = rToItemTextRectbottom;
        }
        else
        {
            ToY = rToItemTextRectbottom - nItemHeight/2;
            if(ITEM_HAS_BUTTON(ptms, bHasButtons, hToItem))
            {
                ToY += ptms->m_nButtonSize/2;
            }
        }
        //LineDDA(ButtonCentre.x, ButtonCentre.y,
        //    ButtonCentre.x, ToY - 1, LineDDAProc, (LPARAM)&ddaParam);
		DrawDottedLine(hDC, ButtonCentre.x, ButtonCentre.y,
            ButtonCentre.x, ToY - 1);
    }
}

static void _CancelItemPressed(TREE_MAP_STRUCT *ptms)
{
    if(ptms->bIsPressed)
    {
        ptms->bIsPressed = false;
        ReleaseCapture();
        ptms->hItemOrigPressed = ptms->hItemPressed = NULL;
    }
}

static void CancelItemPressed(TREE_MAP_STRUCT *ptms)
{
    HTREEITEM hItemPressed = ptms->hItemPressed;

    _CancelItemPressed(ptms);
    
    if(ptms->hItemSelected)
        InvalidateItemRect(ptms, ptms->hItemSelected, FALSE);
    if(hItemPressed)
        InvalidateItemRect(ptms, hItemPressed, TRUE);
    if(ptms->hDropHilite)
        InvalidateItemRect(ptms, ptms->hDropHilite, TRUE);
}

//for the same items returns false
static bool IsAnyLevelParent(TREE_MAP_STRUCT *ptms, HTREEITEM hPossibleParent, HTREEITEM hPossibleChild)
{
    ASSERT(hPossibleParent != NULL);
    ASSERT(hPossibleChild != NULL);

    do
    {
        hPossibleChild = GetNextItem( ptms, hPossibleChild, TVGN_PARENT);
        if(hPossibleParent == hPossibleChild)
            return true;
    }
    while(hPossibleChild != NULL);

    return false;
}

//called after some items (from view) removing when is sure must be scrolled
//that way where last visible item will be at view bottom
//without this will be scrolled "more than in number of items"
//expect has enought items in view (full page minimaly) means was called in described situation
//returns item what has to be set first visible to get wanted state
static HTREEITEM _ScrollAbsolutelyDown(TREE_MAP_STRUCT *ptms, UINT nVisibleCount)
{
    //if(ptms->hItemFirstVisible == NULL)
    //    return NULL;

    ASSERT(nVisibleCount == GetVisibleCount(ptms));
    
    ASSERT((ptms->nVScrollPos + (int)nVisibleCount) > ptms->nVisibleItemCount);
    
    //scroll absolutely down
    HTREEITEM hNewItemFirstVisible = ptms->hItemFirstVisible;

    UINT nMove = ptms->nVScrollPos + (int)nVisibleCount - ptms->nVisibleItemCount;
    for(UINT offset = 0; offset < nMove; offset++)
    {
        HTREEITEM hPrev = GetNextItem(ptms, hNewItemFirstVisible, TVGN_PREVIOUSVISIBLE);
        //ASSERT(hPrev != NULL);
        if(hPrev == NULL) //less items than visible count
        {
            ASSERT(hNewItemFirstVisible != NULL);
            break;
        }
        hNewItemFirstVisible = hPrev;
    }

    ASSERT(hNewItemFirstVisible != NULL);
    return hNewItemFirstVisible;
}

static void _ScrollAbsolutelyDownWhenRequired(TREE_MAP_STRUCT *ptms)
{
	if(ptms->nVisibleItemCount)
	{
		UINT nVisibleCount = GetVisibleCount(ptms);
		
		if((ptms->nVScrollPos + (int)nVisibleCount) > ptms->nVisibleItemCount)
		{
			HTREEITEM hNewItemFirstVisible = _ScrollAbsolutelyDown(ptms, nVisibleCount);
			ptms->hItemFirstVisible = NULL;
			SetFirstVisibleItem(ptms, hNewItemFirstVisible);
		}
	}
}

//when rcItem of hItem is over or under rcClient returns HTREEITEM of
//item what has to be first visible to have hItem fully visible
//othervise returns NULL
static HTREEITEM _FirstVisibleItemFullyVisible(TREE_MAP_STRUCT *ptms, RECT &rcClient,
                                   HTREEITEM hItem, RECT &rcItem)
{
    HTREEITEM hNewItemFirstVisible = NULL;

    if(rcItem.top < rcClient.top) //item was "over view"
    {
        //show as a first
        hNewItemFirstVisible = hItem;
    }
    else
    {
        if(rcItem.bottom >= rcClient.bottom) //item was "under view"
        {
            UINT nVisibleCount = GetVisibleCount(ptms);

            //show as a last
            //find item what will be first visible
            //going back from hItem nVisibleCount-times (if possible)
            hNewItemFirstVisible = hItem;
            for(UINT offset = 0; offset < nVisibleCount - 1; offset++)
            {
                HTREEITEM hPrev = GetNextItem(ptms, hNewItemFirstVisible, TVGN_PREVIOUSVISIBLE);
                if(hPrev == NULL
                    /*|| hPrev == ptms->hItemFirstVisible*/)
                {
                    hNewItemFirstVisible = NULL;
                    break;
                }
                hNewItemFirstVisible = hPrev;
            }
        }
    }

    return hNewItemFirstVisible;
}

//not sends selchange messages
static void _RemoveSelectedStateFlagForAllLevelChildren(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, HTREEITEM hExceptItem)
{
    if(hItem != hExceptItem)
        ptms->rgTree.GetAt( (POSITION)hItem)->state &= ~TVIS_SELECTED;

    for(HTREEITEM hChild = GetNextItem( ptms, hItem, TVGN_CHILD); hChild != NULL; hChild = GetNextItem( ptms, hChild, TVGN_NEXT))
        _RemoveSelectedStateFlagForAllLevelChildren(ptms, hChild, hExceptItem);
}    

static void RemoveSelectedStateFlagForAllLevelChildren(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, HTREEITEM hExceptItem)
{                
    for(HTREEITEM hChild = GetNextItem( ptms, hItem, TVGN_CHILD); hChild != NULL; hChild = GetNextItem( ptms, hChild, TVGN_NEXT))
        _RemoveSelectedStateFlagForAllLevelChildren(ptms, hChild, hExceptItem);
}

//notification messages are sent by system expand state change only
//not by TreeView_Expand call
static bool Expand( TREE_MAP_STRUCT *ptms, HTREEITEM hItem, UINT state,
                  BOOL bSetNotification)
{
    LPRGTVITEM pItem = ptms->rgTree.GetAt( (POSITION)hItem);

    UINT oldstate = pItem->state;
    UINT newstate = pItem->state;
    switch( state)
    {
        case TVE_TOGGLE:
            newstate ^= TVIS_EXPANDED;
            break;
        case TVE_EXPAND:
            newstate |= TVIS_EXPANDED;        
            break;
        case TVE_COLLAPSE:
            newstate &= ~TVIS_EXPANDED;
            break;
#ifdef _DEBUG
        default:
            ASSERT(0); //not implemented
            return FALSE;
#endif
    }
    if( oldstate == newstate)
        return FALSE;

    UINT nCount = 0;
    _AddVisibleChildCount( ptms->rgTree, ptms->rgTree.GetChildPosition((POSITION)hItem), nCount);
    //if(nCount == 0)
    //    return FALSE;

    NMTREEVIEW nmTV;
    nmTV.action = (newstate & TVIS_EXPANDED) ? TVE_EXPAND : TVE_COLLAPSE;
    SetTVITEMforNotify(ptms, &nmTV.itemNew, hItem, TVIF_STATE | TVIF_PARAM | TVIF_HANDLE);

    if(bSetNotification
        && PSNDNMSG(ptms->hwnd, nmTV, TVN_ITEMEXPANDING))
        return FALSE;

    pItem->state = newstate;

    if(nCount != 0)
    {
        if(IsItemVisible( ptms->rgTree, (POSITION)hItem))
        {
            bool bRedrawAll = false;
            
            KillTimer( ptms->hwnd, ID_EDIT_TIMER);
            EndEditLabelNow( ptms, TRUE);
            
            RECT rcc;
            GetClientRect( ptms->hwnd, &rcc);
            RECT rc;
            VERIFY(GetItemRect( ptms, hItem, &rc, FALSE));
            
            HTREEITEM hNewItemFirstVisible = NULL;
            
            if( pItem->state & TVIS_EXPANDED)
            {
                ptms->nVisibleItemCount += nCount;
                
                if(rc.top >= rcc.top)
                {
                    //try to show last expanded item (if by expanding will be out of view)
                    //if will be too much items expanded keep hItem visible in view
                    //and show so much next visible items as possible
                    
                    UINT nVisibleCount = GetVisibleCount(ptms);
                    if(nVisibleCount <= nCount + 1/* means +hItem */)
                    {
                        hNewItemFirstVisible = hItem;
                    }
                    else
                    {
                        //find last expanded
                        HTREEITEM hLastExpandedItem = hItem;
                        for(UINT offset = 0; offset < nCount; offset++)
                        {
                            hLastExpandedItem = GetNextItem(ptms, hLastExpandedItem, TVGN_NEXTVISIBLE);
                        }
                        
                        //ASSERT(GetNextItem(ptms, hLastExpandedItem, TVGN_PARENT) == hItem);
                        
                        //find item what will be first visible
                        //going back from hLastExpandedItem nVisibleCount-times (if possible)
                        hNewItemFirstVisible = hLastExpandedItem;
                        for(/*UINT*/ offset = 0; offset < nVisibleCount - 1; offset++)
                        {
                            HTREEITEM hPrev = GetNextItem(ptms, hNewItemFirstVisible, TVGN_PREVIOUSVISIBLE);
                            //if(hPrev == NULL)
                            //    break;
                            ASSERT(hPrev != NULL);
                            ASSERT(ptms->hItemFirstVisible != NULL);
                            if(hPrev == ptms->hItemFirstVisible)
                            {
                                hNewItemFirstVisible = NULL;
                                break;
                            }
                            hNewItemFirstVisible = hPrev;
                        }
                    }
                }
                else //item is "over view"
                {
                    ptms->nVScrollPos += nCount;
                }
            }
            else //collapsed
            {
                UINT nVisibleCount = GetVisibleCount(ptms);
                
                ptms->nVisibleItemCount -= nCount;
                
                if(ptms->hItemFirstVisible)
                {
                    if(IsAnyLevelParent(ptms, hItem, ptms->hItemFirstVisible))
                        //hItemFirstVisible will be collapsed, set hItem as first visible
                    {
                        SetFirstVisibleItem(ptms, hItem); //direct call to correct nVScrollPos before next
                        ASSERT(hItem == ptms->hItemFirstVisible);
                        hNewItemFirstVisible = hItem;
                    }
                }
                
                if(rc.top < rcc.top //item was "over view"
                    && hNewItemFirstVisible == NULL) //and not already solved
                {
                    //we are sure collapsed item had all items 'over' - if not it was solved before
                    ptms->nVScrollPos -= nCount;
                    ASSERT(ptms->nVScrollPos >= 0);
                }

                if((ptms->nVScrollPos + (int)nVisibleCount) > ptms->nVisibleItemCount)
                {
                    hNewItemFirstVisible = _ScrollAbsolutelyDown(ptms, nVisibleCount);
                    ASSERT(hNewItemFirstVisible != NULL);
                }
                else
                {
                    hNewItemFirstVisible = _FirstVisibleItemFullyVisible(ptms, rcc, hItem, rc);
                }
                
                //remove selected state flag for all children except item selected ptms->hItemSelected
                RemoveSelectedStateFlagForAllLevelChildren(ptms, hItem, ptms->hItemSelected);
                
                if(ptms->hItemSelected)
                {
                    if(IsAnyLevelParent(ptms, hItem, ptms->hItemSelected))
                        //hItemSelected will be collapsed, find new one
                    {
                        NMTREEVIEW nmtv;
                        SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, TVC_UNKNOWN, ptms->hItemSelected, hItem);
                        if(bSetNotification && PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGING))
                        {
                            ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected)->state &= ~TVIS_SELECTED;
                            
                            ptms->hItemSelected = NULL;
                            KillTimer( ptms->hwnd, ID_SHOW_TIMER);
                            KillTimer( ptms->hwnd, ID_EDIT_TIMER);
                            EndEditLabelNow(ptms, TRUE);
                        }
                        else
                        {
                            ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected)->state &= ~TVIS_SELECTED;
                            
                            ptms->hItemSelected = hItem;
                            KillTimer( ptms->hwnd, ID_SHOW_TIMER);
                            KillTimer( ptms->hwnd, ID_EDIT_TIMER);
                            EndEditLabelNow(ptms, TRUE);
                            
                            ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected)->state |= TVIS_SELECTED;
                            if(bSetNotification)
                            {
                                SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, TVC_UNKNOWN, nmtv.itemOld.hItem, ptms->hItemSelected);
                                PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGED);
                            }
                        }
                    }
                }
                
                if(ptms->hItemPressed)
                {
                    if(IsAnyLevelParent(ptms, hItem, ptms->hItemPressed))
                        //hItemPressed will be collapsed, reset it
                    {
                        _CancelItemPressed(ptms);
                    }
                }
            }
            
            if(hNewItemFirstVisible
                && (hNewItemFirstVisible != ptms->hItemFirstVisible))
            {
                ptms->hItemFirstVisible = NULL;
                SetFirstVisibleItem( ptms, hNewItemFirstVisible);
                bRedrawAll = true;
            }
            
            if( ptms->bRedrawFlag)
            {
                if(SETSCROLLBARS(ptms) == false)
                {
                    if(bRedrawAll == true)
                    {
                        rc.top = rcc.top;
                        rc.bottom = rcc.bottom;
                    }
                    else
                    {
                        VERIFY(GetItemRect( ptms, hItem, &rc, FALSE));
                    }
                    if(rcc.top <= rc.bottom
                        && rcc.bottom >= rc.top)
                    {
                        rcc.top = rc.top;
                        InvalidateRect( ptms->hwnd, &rcc, TRUE);
                    }
                }
            }
        }
    }

    if(bSetNotification)
    {
        PSNDNMSG(ptms->hwnd, nmTV, TVN_ITEMEXPANDED);
    }
    return TRUE;
}

static bool GetItemRect(TREE_MAP_STRUCT *ptms, HTREEITEM hItem, LPRECT lpRect, BOOL bTextOnly)
{
    UINT nItemHeight = GetItemHeight(ptms);
    return _GetItemRect(ptms, hItem, lpRect, bTextOnly, nItemHeight);
}

static HTREEITEM GetNextItem( TREE_MAP_STRUCT *ptms, HTREEITEM hItem, UINT flag)
{
    switch(flag)
    {
        case TVGN_CARET:
            return ptms->hItemSelected;
        case TVGN_CHILD:
            return (HTREEITEM)ptms->rgTree.GetChildPosition((POSITION)hItem);
        case TVGN_DROPHILITE:
            return ptms->bIsPressed ? ptms->hItemPressed : ptms->hDropHilite;
        case TVGN_FIRSTVISIBLE:
            return ptms->hItemFirstVisible;
#ifdef TVGN_LASTVISIBLE
        case TVGN_LASTVISIBLE:
            {
                POSITION LastPos = ptms->rgTree.GetRootPosition();
                for(POSITION pos = LastPos; pos != NULL;)
                {
                    //sub-tree level is visible - go to last item there (LastSiblingItem)
                    {
                        POSITION pos2 = pos;
                        do
                        {
                            pos = pos2; //remember last not-null item
                            pos2 = ptms->rgTree.GetNextPosition(pos2);
                        }
                        while(pos2 != NULL);
                    }

                    ASSERT(pos != NULL);
                    LastPos = pos; //remember last not-null item

                    //if expanded go to child (if has any)
                    LPRGTVITEM pItem = ptms->rgTree.GetAt( pos);
                    if( pItem->state & TVIS_EXPANDED)
                        pos = ptms->rgTree.GetChildPosition( pos);
                    else
                        pos = NULL;
                }
                
                return (HTREEITEM)LastPos;
            }
#endif
        case TVGN_NEXT:
            return hItem ? (HTREEITEM)ptms->rgTree.GetNextPosition((POSITION)hItem) : NULL;
        case TVGN_NEXTVISIBLE:
            {
                if(hItem == NULL)
                    return NULL;
                POSITION pos = (POSITION)hItem;
                LPRGTVITEM pItem = ptms->rgTree.GetAt( pos);
                POSITION posNext = NULL;
                if( pItem->state & TVIS_EXPANDED)
                    posNext = ptms->rgTree.GetChildPosition( pos);
                if( posNext == NULL)
                    while( (posNext = ptms->rgTree.GetNextPosition( pos)) == NULL)
                    {
                        posNext = ptms->rgTree.GetParentPosition( pos);
                        if( posNext == NULL)
                            break;
                        pos = posNext;
                    }
                return posNext ? (HTREEITEM)posNext : NULL;
            }
        case TVGN_PARENT:
            return hItem ? (HTREEITEM)ptms->rgTree.GetParentPosition( (POSITION)hItem) : NULL;
        case TVGN_PREVIOUS:
            return hItem ? (HTREEITEM)ptms->rgTree.GetPrevPosition((POSITION)hItem) : NULL;
        case TVGN_PREVIOUSVISIBLE:
            {
                if(hItem == NULL)
                    return NULL;
                for( POSITION pos=ptms->rgTree.GetPrevPosition((POSITION)hItem);
                pos && (ptms->rgTree.GetAt( pos)->state & TVIS_EXPANDED)
                    && ptms->rgTree.GetChildPosition( pos);
                pos=ptms->rgTree.GetChildPosition( pos, FALSE));
                if( pos == NULL)
                    pos = ptms->rgTree.GetParentPosition( (POSITION)hItem);
                return pos ? (HTREEITEM)pos : NULL;
            }
        case TVGN_ROOT:
            return (HTREEITEM)ptms->rgTree.GetRootPosition();
    }

    return NULL;
}

static bool EnsureVisible( TREE_MAP_STRUCT *ptms, HTREEITEM hItem, bool bExpandOnly)
{
    //expand all parents
    POSITION pos = (POSITION)hItem;
    while( pos = ptms->rgTree.GetParentPosition( pos))
    {
        if( (ptms->rgTree.GetAt( pos)->state & TVIS_EXPANDED) == 0)
        {
            if(Expand(ptms, (HTREEITEM)pos, TVE_EXPAND, TRUE) == false)
                return false;
        }
    }

    if(bExpandOnly == false)
    {    
        RECT rcc;
        GetClientRect( ptms->hwnd, &rcc);
        RECT rc;
        VERIFY(GetItemRect( ptms, hItem, &rc, FALSE));

        HTREEITEM hNewItemFirstVisible = _FirstVisibleItemFullyVisible(ptms, rcc, hItem, rc);
        
        if(hNewItemFirstVisible
            && (hNewItemFirstVisible != ptms->hItemFirstVisible))
        {
            ptms->hItemFirstVisible = NULL;
            SetFirstVisibleItem( ptms, hNewItemFirstVisible);

            if( ptms->bRedrawFlag)
            {
                if(SETSCROLLBARS(ptms) == false)
                    InvalidateRect( ptms->hwnd, &rcc, TRUE);
            }        
        }
    }

    return true;
}

static bool Select( TREE_MAP_STRUCT *ptms, HTREEITEM hItem, UINT flag, bool bByMouse)
{
    switch( flag)
    {
        case TVGN_CARET:
            {
                int action = bByMouse ? TVC_UNKNOWN : TVC_BYKEYBOARD;
                NMTREEVIEW nmtv;
                SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, action, ptms->hItemSelected, hItem);
                if( PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGING))
                    return TRUE;
                if( ptms->hItemSelected != hItem)
                {
                    if( ptms->hItemSelected)
                    {
                        ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected)->state &= ~TVIS_SELECTED;
                        InvalidateItemRect( ptms, ptms->hItemSelected, TRUE);
                    }

                    ptms->hItemSelected = hItem;
                    KillTimer( ptms->hwnd, ID_SHOW_TIMER);
                    KillTimer( ptms->hwnd, ID_EDIT_TIMER);
                    EndEditLabelNow(ptms, TRUE);

                    if( ptms->hItemSelected)
                    {
                        POSITION pos = (POSITION)ptms->hItemSelected;
                        ptms->rgTree.GetAt(pos)->state |= TVIS_SELECTED;
                        //if(IsItemVisible(ptms->rgTree, pos) == false)
                        //{
                        //    ASSERT(bByMouse == false);
                            EnsureVisible(ptms, ptms->hItemSelected,
                                (bByMouse == true || ptms->bRedrawFlag == false)? true : false);
                        //}
                        //else
                        //{
                        //    if(bByMouse == false && ptms->bRedrawFlag == true)
                        //        EnsureVisible(ptms, ptms->hItemSelected, false);
                        //}

                        InvalidateItemRect( ptms, ptms->hItemSelected, FALSE);

                        if(bByMouse)
                        {
                            SetTimer( ptms->hwnd, ID_SHOW_TIMER, GetDoubleClickTime(), NULL);
                        }
                    }
                }
                SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, action, nmtv.itemOld.hItem, ptms->hItemSelected);
                PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGED);
            }
            break;
        case TVGN_DROPHILITE:
            {
                HTREEITEM &hHiliteItem = ptms->bIsPressed ? ptms->hItemPressed : ptms->hDropHilite;
                
                if( hHiliteItem != hItem)
                {
                    HTREEITEM hOldDropHilite = hHiliteItem;
                    hHiliteItem = hItem;
                    
                    if(hOldDropHilite)
                    {
                        InvalidateItemRect( ptms, hOldDropHilite, FALSE);
                    }
                    if(ptms->hDropHilite)
                    {
                        InvalidateItemRect( ptms, ptms->hDropHilite, FALSE);
                    }
                    if(ptms->hItemSelected)
                    {
                        InvalidateItemRect( ptms, ptms->hItemSelected, FALSE);
                    }
                    if(ptms->hItemPressed)
                    {
                        InvalidateItemRect( ptms, ptms->hItemPressed, FALSE);
                    }
                    
                    UpdateWindow(ptms->hwnd);
                }
            }
            break;
        case TVGN_FIRSTVISIBLE:
            ptms->hItemFirstVisible = NULL;
            SetFirstVisibleItem( ptms, hItem);
            Select( ptms, hItem, TVGN_CARET, false);
            break;
    }
    return TRUE;
}

static LRESULT SetItem( TREE_MAP_STRUCT *ptms, LPTVITEM pItem)
{
    LPRGTVITEM pTempItem = ptms->rgTree.GetAt((POSITION)pItem->hItem);
    bool bDraw = false;
    if( pItem->mask & TVIF_TEXT)
    {
        if(pTempItem->pszText)
            delete[] pTempItem->pszText;
        if(pItem->pszText)
        {
            pTempItem->cchTextMax = _tcslen( pItem->pszText);
            pTempItem->pszText = new TCHAR[pTempItem->cchTextMax+1];
            memcpy( pTempItem->pszText, pItem->pszText, (pTempItem->cchTextMax+1)*sizeof(TCHAR));
        }
        else
        {
            pTempItem->cchTextMax = 0;
            pTempItem->pszText = NULL;
        }
        pTempItem->ItemTextWidth = 0;
        bDraw = true; //in future can be set with real text change only
    }
    
    if( pItem->mask & TVIF_STATE)
    {
        if( pItem->stateMask & TVIS_EXPANDED)
            Expand( ptms, pItem->hItem, pItem->state & TVIS_EXPANDED ? TVE_EXPAND : TVE_COLLAPSE, FALSE);

        UINT filteredStateMask = pItem->stateMask & ~TVIS_EXPANDED; //expand change was maybe canceled (Expand returns false)
        UINT oldState = pTempItem->state; //after Expand call - it requests redraw by own call
        pTempItem->state = (pItem->state & filteredStateMask) | (~filteredStateMask & pTempItem->state);
        if(oldState != pTempItem->state)
            bDraw = true;
    }

    if( pItem->mask & TVIF_PARAM)
    {
        pTempItem->lParam = pItem->lParam;
    }
    if( pItem->mask & TVIF_IMAGE)
    {
        pTempItem->iImage = pItem->iImage;
    }
    if( pItem->mask & TVIF_SELECTEDIMAGE)
    {
        pTempItem->iSelectedImage = pItem->iSelectedImage;
    }

    if(bDraw && ptms->bRedrawFlag)
    {
        int SearchOnly = GetVisibleCount(ptms) + 1;

        int nIndex = __GetItemVisibleIndex(ptms, pItem->hItem, false, SearchOnly);
        if(nIndex != -1) //has sence to redraw
        {                       
            RECT rc;
            if(GetItemRect( ptms, pItem->hItem, &rc, FALSE))
            {
                if(SETSCROLLBARS(ptms) == false)
                    InvalidateRect( ptms->hwnd, &rc, TRUE);
            }
        }
        else
        {
            if(pItem->mask & TVIF_TEXT) //can have influence to horizontal scroll size
                SETSCROLLBARS(ptms);
        }
    }

    return 0;
}

static HTREEITEM HitTest(TREE_MAP_STRUCT *ptms, LPTVHITTESTINFO ptvhti)
{
    ptvhti->flags = 0;
    ptvhti->hItem = NULL;
    RECT rcClient;
    GetClientRect( ptms->hwnd, &rcClient);
    if(PtInRect(&rcClient, ptvhti->pt) == FALSE)
    {
        if(ptvhti->pt.x <= rcClient.left)
          ptvhti->flags |= TVHT_TOLEFT;
        if(ptvhti->pt.x >= rcClient.right)
          ptvhti->flags |= TVHT_TORIGHT;
        if(ptvhti->pt.y <= rcClient.top)
          ptvhti->flags |= TVHT_ABOVE;
        if(ptvhti->pt.y >= rcClient.bottom)
          ptvhti->flags |= TVHT_BELOW;
        return ptvhti->hItem;
    }

    POINT pt = ptvhti->pt;
    pt.x += ptms->nHScrollPos;

    const int iHeight = GetItemHeight(ptms);
    ptvhti->hItem = ptms->hItemFirstVisible;
    int iItemTop = 0;
    for( int iItemBottom = iHeight;
    (ptvhti->hItem != NULL) && (iItemBottom <= pt.y);
    iItemTop += iHeight, iItemBottom += iHeight)
        ptvhti->hItem = GetNextItem( ptms, ptvhti->hItem, TVGN_NEXTVISIBLE);
                
    if(ptvhti->hItem)
    {
        GetItemTextRectCache Cache(ptms->hwnd);

        RECT rc;
        GetClientRect(ptms->hwnd, &rc);
        int left = rc.left;
        
        int offset;
        offset = _GetBasicIndent(ptms, ptvhti->hItem, &Cache);
        left += offset;
        if(pt.x < left)
        {
            DWORD dwStyle = GetWindowStyle( ptms->hwnd);
            bool bHasButtons = (dwStyle & TVS_HASBUTTONS) != 0;
            
            if(ITEM_HAS_BUTTON(ptms, bHasButtons, ptvhti->hItem)
                && (pt.x >= (left - (int)ptms->m_nIndent)))
            {
                ASSERT((left - ptms->m_nIndent) >= 0); //must be? (h-scroll)
                ptvhti->flags = TVHT_ONITEMBUTTON;
            }
            else
            {
                ptvhti->flags = TVHT_ONITEMINDENT;
            }
        }
        else
        {
            RGTVITEM *pItem = ptms->rgTree.GetAt((POSITION)ptvhti->hItem);
            
            offset = _GetStateImageSize(ptms, pItem, &Cache).cx;
            left += offset;
            if(pt.x < left)
            {
                ptvhti->flags = TVHT_ONITEMSTATEICON;
            }
            else
            {
                offset = _GetNormalImageSizeAndOffset(ptms, &Cache).cx;
                left += offset;
                if(pt.x < left)
                {
                    ptvhti->flags = TVHT_ONITEMICON;
                }
                else
                {
                    int TextSize = _GetItemTextWidth(ptms, pItem, &Cache);
                    offset = ITEM_TEXT_X_R2LOFFSET(TextSize);
                    left += offset;
                    if(pt.x < left)
                    {
                        ptvhti->flags = TVHT_ONITEMLABEL;
                    }
                    else
                    {
                        ptvhti->flags = TVHT_ONITEMRIGHT;
                    }
                }
            }
        }
    }
    else
    {
        ptvhti->flags = TVHT_NOWHERE;
    }

    return ptvhti->hItem;
}

static bool EndEditLabelNow( TREE_MAP_STRUCT *ptms, BOOL fCancel)
{
    if(ptms->hItemEditing == NULL) //nothing to end
        return FALSE;

    NMTVDISPINFO tvdi;
    SetTVITEMforNotify(ptms, &tvdi.item, ptms->hItemEditing, TVIF_PARAM | TVIF_HANDLE);
    LPRGTVITEM pItem = ptms->rgTree.GetAt( (POSITION)ptms->hItemEditing);
    TCHAR strEdit[MAX_PATH];
    if(fCancel)
    {
        tvdi.item.pszText = NULL;
        tvdi.item.cchTextMax = 0;
    }
    else
    {
        tvdi.item.mask |= TVIF_TEXT;
        tvdi.item.pszText = strEdit;
        tvdi.item.cchTextMax = GetWindowText( ptms->hWndEdit, strEdit, MAX_PATH);
    }

    bool bResult = FALSE;
    if(PSNDNMSG(ptms->hwnd, tvdi, TVN_ENDLABELEDIT) && (fCancel == FALSE))
    {
        TVITEM tvItem;
        tvItem.mask = TVIF_TEXT;
        tvItem.pszText = strEdit;
        tvItem.hItem = ptms->hItemEditing;
        SetItem( ptms, &tvItem);
        bResult = TRUE;
    }
    ptms->hItemEditing = NULL;
    ShowWindow( ptms->hWndEdit, SW_HIDE);
    return bResult;
}

static void ComputeMaxWidth( TREE_MAP_STRUCT *ptms)
{
    ptms->nMaxWidth = 0;

    GetItemTextRectCache Cache(ptms->hwnd);
        
    HTREEITEM hItem = GetNextItem( ptms, NULL, TVGN_ROOT);
    while(hItem != NULL)
    {
        RECT rc;
        rc.left = 0;
        RGTVITEM *pItem = ptms->rgTree.GetAt((POSITION)hItem);
        _GetItemTextRect(ptms, hItem, pItem, &rc, &rc, &Cache);

        rc.right += ptms->nHScrollPos;

        if(ptms->nMaxWidth < rc.right)
            ptms->nMaxWidth = rc.right;

        hItem = GetNextItem( ptms, hItem, TVGN_NEXTVISIBLE);
    }

    if(ptms->nMaxWidth > 0)
    {
        RECT rc;
        GetClientRect(ptms->hwnd, &rc);
        ASSERT(rc.left == 0);

        //if(rc.right < ptms->nMaxWidth)
            if(rc.right + ptms->nHScrollPos > ptms->nMaxWidth)
            {           
                ptms->nHScrollPos = ptms->nMaxWidth - rc.right;
                if(ptms->nHScrollPos < 0)
                {
                    ptms->nHScrollPos = 0;
                }
//                InvalidateRect(ptms->hwnd, NULL, TRUE);
            }
    }
}

//function without HIWORD position limit
static void _DoScroll(TREE_MAP_STRUCT *ptms, int ScrollBar, int nPos, int vCount)
{
    if(ScrollBar == SB_HORZ)
    {
        if( nPos > ptms->nMaxWidth - vCount)
            nPos = ptms->nMaxWidth - vCount;
        if( nPos < 0)
            nPos = 0;
        
        if( nPos != ptms->nHScrollPos)
        {
            SCROLLINFO info;
            info.cbSize = sizeof( SCROLLINFO);
            info.fMask = SIF_POS;
            info.nPos = nPos;
            SetScrollInfo( ptms->hwnd, SB_HORZ, &info, TRUE);
            const int delta = ptms->nHScrollPos - nPos;
            ptms->nHScrollPos = nPos;
            ScrollWindow(ptms->hwnd, delta, 0, NULL, NULL);
            UpdateWindow(ptms->hwnd);
        }
    }
    else
    {
        ASSERT(ScrollBar == SB_VERT);

        if( nPos > ptms->nVisibleItemCount - vCount)
            nPos = ptms->nVisibleItemCount - vCount;
        if( nPos < 0)
            nPos = 0;
        
        if( nPos != ptms->nVScrollPos)
        {
            SCROLLINFO info;
            info.cbSize = sizeof( SCROLLINFO);
            info.fMask = SIF_POS;
            info.nPos = nPos;
            SetScrollInfo(ptms->hwnd, SB_VERT, &info, TRUE);
            const int delta = ptms->nVScrollPos - nPos;
            if( ptms->nVScrollPos < nPos)
            {
                while( ptms->hItemFirstVisible && ptms->nVScrollPos < nPos)
                {
                    ptms->hItemFirstVisible = GetNextItem( ptms, ptms->hItemFirstVisible, TVGN_NEXTVISIBLE);
                    ptms->nVScrollPos++;
                }
            }
            else
            {
                while( ptms->hItemFirstVisible && ptms->nVScrollPos > nPos)
                {
                    ptms->hItemFirstVisible = GetNextItem( ptms, ptms->hItemFirstVisible, TVGN_PREVIOUSVISIBLE);
                    ptms->nVScrollPos--;
                }
            }
            ScrollWindow(ptms->hwnd, 0, delta * GetItemHeight(ptms), NULL, NULL);
            UpdateWindow(ptms->hwnd);
        }
    }
}

//Gensym-538 fix, WM_VSCROLL and WM_HSCROLL message carries only 16 bits of scroll box position data. 
//Thus, applications that rely solely on WM_VSCROLL (and WM_HSCROLL) for scroll position data have a practical maximum position value of 65,535
//Now add a parameter bUsed16bit, if it is TRUE, using GetScrollInfo and SIF_TRACKPOS to support 32-bit position data 
//when nScrollCode is SB_THUMBPOSITION or SB_THUMBTRACK, and its default value is FALSE
//static void DoScroll(TREE_MAP_STRUCT *ptms, int ScrollBar, int nScrollCode, int nPosition)
static void DoScroll(TREE_MAP_STRUCT *ptms, int ScrollBar, int nScrollCode, int nPosition, BOOL bUsed16bit = FALSE)
{
    int nPos;
    int vCount;

    if(ScrollBar == SB_HORZ)
    {
        RECT rc;
        GetClientRect(ptms->hwnd, &rc);
        ASSERT(rc.left == 0);
        
        vCount = rc.right;

        nPos = ptms->nHScrollPos;
    }
    else
    {
        vCount = GetVisibleCount(ptms);

        nPos = ptms->nVScrollPos;
    }

    switch(nScrollCode)
    {
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
    //    nPos = nPosition;
{
if (bUsed16bit)
{
SCROLLINFO info = {0};
info.cbSize = sizeof( SCROLLINFO);
info.fMask = SIF_TRACKPOS;
GetScrollInfo(ptms->hwnd, ScrollBar, &info);
nPos = info.nTrackPos;
}
else
	nPos = nPosition;
}

        break;
    case SB_LINELEFT:
        nPos--;
        break;
    case SB_LINERIGHT:
        nPos++;
        break;
    case SB_PAGELEFT:
        nPos -= vCount - 1;
        break;
    case SB_PAGERIGHT:
        nPos += vCount - 1;
        break;
    }

    _DoScroll(ptms, ScrollBar, nPos, vCount);
    // check if need to load more nodes
	if(ScrollBar == SB_VERT)
		SendMessage(ptms->hwnd, WM_TREECTRL_CHECKANDLOADNODES, (WPARAM)vCount, (LPARAM)nPos);
 }

static void DoScroll(TREE_MAP_STRUCT *ptms, int ScrollBar, int nPos)
{
    DoScroll(ptms, ScrollBar, SB_THUMBPOSITION, nPos);
}

/**************************************************************************
 *                                                                        *
 *                                  WM_MESSAGES                           *
 *                                                                        *
 **************************************************************************/

static LRESULT OnKeyDown( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    bool bUsed = true;

    if( HIWORD(GetKeyState( VK_CONTROL)))
        switch( wParam)
        {
            case VK_LEFT:        
                DoScroll(ptms, SB_HORZ, SB_LINELEFT, 0);            
                break;
            case VK_RIGHT:
                DoScroll(ptms, SB_HORZ, SB_LINERIGHT, 0);
                break;
			case VK_UP:
                DoScroll(ptms, SB_VERT, SB_LINELEFT, 0);
				break;
			case VK_DOWN:
                DoScroll(ptms, SB_VERT, SB_LINERIGHT, 0);
				break;
            case VK_PRIOR:
                DoScroll(ptms, SB_VERT, SB_PAGELEFT, 0);
                break;
            case VK_NEXT:
                DoScroll(ptms, SB_VERT, SB_PAGERIGHT, 0);
                break;
			case VK_HOME:
				DoScroll(ptms, SB_VERT, SB_THUMBPOSITION, 0);
				break;
			case VK_END:
				{
					// Get the current scrolling information
					SCROLLINFO sio = {0};
					sio.cbSize = sizeof(SCROLLINFO);
					sio.fMask  = SIF_RANGE;
					GetScrollInfo( ptms->hwnd, SB_VERT, &sio );
					
					DoScroll(ptms, SB_VERT, SB_THUMBPOSITION, sio.nMax);
				}
				break;
            default:
                bUsed = false;
                break;
        }
    else
    {
        HTREEITEM hItem;
        if(ptms->hItemSelected)
        {
            switch( wParam)
            {
            case VK_LEFT:
                {
                    LPRGTVITEM pItemSelected = ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected);
                    
                    if(pItemSelected->state & TVIS_EXPANDED)
                    {
                        Expand( ptms, ptms->hItemSelected, TVE_COLLAPSE, TRUE);
                        break;
                    }
                }
                hItem = GetNextItem( ptms, ptms->hItemSelected, TVGN_PARENT);
                if( hItem)
                {
                    RECT rc;
                    if( GetItemRect( ptms, hItem, &rc, FALSE) == false)
                    {
                        ptms->hItemFirstVisible = hItem;
                        ptms->nVScrollPos = 0;
                        InvalidateRect( ptms->hwnd, NULL, TRUE);
                    }
                    Select( ptms, hItem, TVGN_CARET, false);
                }
                break;
            case VK_RIGHT:
                hItem = GetNextItem( ptms, ptms->hItemSelected, TVGN_CHILD);
                if( hItem)
                {
                    LPRGTVITEM pItemSelected = ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected);
                    
                    if((pItemSelected->state & TVIS_EXPANDED) == 0)
                    {
                        Expand( ptms, ptms->hItemSelected, TVE_EXPAND, TRUE);
                    }
                    else
                    {
                        Select( ptms, hItem, TVGN_CARET, false);
                    }
                }
                break;
            case VK_UP:
                hItem = GetNextItem( ptms, ptms->hItemSelected, TVGN_PREVIOUSVISIBLE);
                goto VK_DOWN_JUMP;

            case VK_DOWN:
                hItem = GetNextItem( ptms, ptms->hItemSelected, TVGN_NEXTVISIBLE);
VK_DOWN_JUMP:
                if( hItem!= NULL)
                {
                    RECT rc;
                    GetItemRect( ptms, hItem, &rc, FALSE);

                    RECT rcc;
                    GetClientRect(ptms->hwnd, &rcc);

                    if(rc.top < rcc.top)
                    {
                        UINT nItemVisibleIndex = GetItemVisibleIndex(ptms, hItem);
                        DoScroll(ptms, SB_VERT, SB_THUMBPOSITION, nItemVisibleIndex);
                    }
                    if(rc.bottom >= rcc.bottom)
                    {
                        UINT nItemVisibleIndex = GetItemVisibleIndex(ptms, hItem);
                        nItemVisibleIndex -= GetVisibleCount( ptms) - 1;
                        DoScroll(ptms, SB_VERT, SB_THUMBPOSITION, nItemVisibleIndex);
                    }

                    Select( ptms, hItem, TVGN_CARET, false);
                }
                break;
            case VK_PRIOR: //pgup
            case VK_NEXT: //pgdn
                {
                    int vCount = GetVisibleCount( ptms);

                    ASSERT(ptms->hItemSelected);
                    HTREEITEM hNextItem = ptms->hItemSelected;
                    hItem = ptms->hItemSelected;

                    while(vCount > 0
                        && hNextItem != NULL)
                    {
                        hItem = hNextItem;
                        hNextItem = (wParam == VK_NEXT)
                            ? GetNextItem( ptms, hItem, TVGN_NEXTVISIBLE)
                            : GetNextItem( ptms, hItem, TVGN_PREVIOUSVISIBLE);
                        vCount--;
                    }
                    goto VK_DOWN_JUMP;
                }
                break;
#ifdef TVGN_LASTVISIBLE
			case VK_HOME:
				hItem = GetNextItem( ptms, NULL, TVGN_ROOT);
				goto VK_DOWN_JUMP;
			case VK_END:
				hItem = GetNextItem( ptms, NULL, TVGN_LASTVISIBLE);
				goto VK_DOWN_JUMP;
#endif
            case VK_ADD:
                {
                    LPRGTVITEM pItemSelected = ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected);
                    
                    if((pItemSelected->state & TVIS_EXPANDED) == 0)
                    {
                        Expand( ptms, ptms->hItemSelected, TVE_EXPAND, TRUE);
                    }
                }
                break;
            case VK_SUBTRACT:
                {
                    LPRGTVITEM pItemSelected = ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected);
                    
                    if(pItemSelected->state & TVIS_EXPANDED)
                    {
                        Expand( ptms, ptms->hItemSelected, TVE_COLLAPSE, TRUE);
                        break;
                    }
                }
                break;
            default:
                bUsed = false;
                break;
            }
        }
    }

    if(bUsed == false
        && (ptms->hItemFirstVisible != NULL))
    {
        if(wParam == VK_SPACE
            || (wParam >= '0' && wParam <= '9')
            || (wParam >= 'A' && wParam <= 'Z')
            || (wParam >= 0xba && wParam <= 0xc0)
            || (wParam >= 0xdb && wParam <= 0xde)
            )
        {
            MessageBeep(-1);
        }
    }

    return !bUsed;
}

static LRESULT OnLButtonDblClk( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    if( ptms->hItemFirstVisible == NULL)
        return 0;

    KillTimer( ptms->hwnd, ID_EDIT_TIMER);

    TVHITTESTINFO tvhti;
    PT_FILL( tvhti.pt, lParam);
    HitTest( ptms, &tvhti);
    if( tvhti.hItem)
    {
        // bitmaps also has to be handled. TVHT_ONITEMLABEL doesn't do this.
        // double click on an item button should be processed as an additional
        // single click
        if(tvhti.flags & (TVHT_ONITEM | TVHT_ONITEMBUTTON))
        {
          // double click on an item button doesn't select it
          if (tvhti.hItem != ptms->hItemSelected
                    && !(tvhti.flags & TVHT_ONITEMBUTTON)) {
                Select( ptms, tvhti.hItem, TVGN_CARET, true);
            }
            Expand( ptms, tvhti.hItem, TVE_TOGGLE, TRUE);
        }
        if(tvhti.flags & TVHT_ONITEMINDENT) //must be hit under (one of its) parent's button + tree must have has-lines flag
        {
            DWORD dwStyle = GetWindowStyle( ptms->hwnd);
            bool bHasLines = (dwStyle & TVS_HASLINES) != 0;

            if(bHasLines)
            {
                UINT ParentLevel = tvhti.pt.x / ptms->m_nIndent; //level from left to right (0 for root items and its brothers (when are lines at root))

                bool bLinesAtRoot = (dwStyle & TVS_LINESATROOT) != 0; //with no lines at root x coortinate gives parent level -1
                if(bLinesAtRoot == FALSE)
                {
                    ASSERT(ParentLevel > 0);
                    ParentLevel -= 1;
                }

                UINT ChildLevel = GetItemChildLevel(ptms, tvhti.hItem);

                if(ChildLevel > ParentLevel) //clicked to lines from parent's +/- sign down
                {
                    UINT WhatParent = ChildLevel - ParentLevel;
                    
                    HTREEITEM hParentItem = tvhti.hItem;
                    for(UINT i = 0; i < WhatParent; i++) //find parent on which line we clicked
                    {
                        hParentItem = GetNextItem( ptms, hParentItem, TVGN_PARENT);
                        ASSERT(hParentItem);
                    }
                    
                    Expand( ptms, hParentItem, TVE_TOGGLE, TRUE);
                }
            }
        }
    }
    return 0;
}

static LRESULT OnPaint( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    HDC hDC, hDCOriginal;
    PAINTSTRUCT ps;
    CRect rcUpdate;
    if( wParam)
    {
        hDCOriginal = (HDC)wParam;
        if(GetUpdateRect( ptms->hwnd, rcUpdate, FALSE) == false)
            GetClientRect(ptms->hwnd, rcUpdate);
    }
    else
    {
        hDCOriginal = BeginPaint( ptms->hwnd, &ps);
        rcUpdate = ps.rcPaint;
    }

    //hDC = hDCOriginal;
    // Initialize double duffering
    int win_width = rcUpdate.right;
    int win_height = rcUpdate.bottom;
    hDC = CreateCompatibleDC(hDCOriginal);
    HBITMAP hbmMem = CreateCompatibleBitmap(hDCOriginal, win_width, win_height);
    HBITMAP hOld   = (HBITMAP)SelectObject(hDC, hbmMem);

    // Draw into memory

    int nOldBkMode = SetBkMode( hDC, TRANSPARENT);
    HGDIOBJ hFont = (HFONT)SNDMSG( ptms->hwnd, WM_GETFONT, 0, 0);
    HGDIOBJ hOldFont = SelectObject( hDC, hFont);
    HGDIOBJ hBoldFont = NULL;

    bool bFocused = (GetFocus() == ptms->hwnd);
    DWORD style = GetWindowStyle( ptms->hwnd);
    bool bShowSelAlways = ((style & TVS_SHOWSELALWAYS) != 0);
    bool bHasButtons = ((style & TVS_HASBUTTONS) != 0);
    bool bHasLines = ((style & TVS_HASLINES) != 0);
    bool bLinesAtRoot = ((style & TVS_LINESATROOT) != 0);
    bool bDisabled = ((style & WS_DISABLED) != 0);
    bool bReallyFullRowSelect = ((style & TVS_FULLROWSELECT) != 0) && bHasLines == false;

    SetBkColor(hDC, bDisabled ? GetSysColor(COLOR_3DFACE) : GetSysColor(COLOR_WINDOW));
    ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rcUpdate, NULL, 0, NULL);

    HTREEITEM hSelectedItem = ptms->hItemSelected;

    HTREEITEM hItem = ptms->hItemFirstVisible;

    CRect rFullItemRect;
    UINT nItemHeight = GetItemHeight(ptms);

    GetItemTextRectCache Cache(ptms->hwnd);

    CSize NormalImageSizeAndOffset(_GetNormalImageSizeAndOffset(ptms, &Cache));

    while(hItem != NULL)
    {
        //note: newer tree versions are able to set individual parameters to every item
        
        if(hItem == ptms->hItemFirstVisible)
        {
            GetFullItemWidth(ptms->hwnd, &rFullItemRect);
            rFullItemRect.top = 0;
            rFullItemRect.bottom = nItemHeight;
        }
        else
        {
            rFullItemRect.top += nItemHeight;
            rFullItemRect.bottom += nItemHeight;
        }
        
        if(rFullItemRect.top >= rcUpdate.bottom)
        {
            break; //break from while
        }
        
        if(rFullItemRect.bottom >= rcUpdate.top)
        {            
            LPRGTVITEM pItem = ptms->rgTree.GetAt( (POSITION)hItem);
            
            CRect rItemTextRect(rFullItemRect);
            _GetItemTextRect(ptms, hItem, pItem, &rFullItemRect, &rItemTextRect, &Cache);
            
            bool bResetTextColor = false;
            
            UINT itemState = pItem->state;
            if(bDisabled)
            {
                bResetTextColor = true;
                SetTextColor(hDC, GetSysColor(COLOR_GRAYTEXT));
            }
            else
            {
                if((itemState & TVIS_SELECTED)
                    || (hItem == ptms->hItemPressed)                    
                    || (hItem == ptms->hDropHilite && ptms->hItemPressed == NULL))
                {
                    if(bFocused || bShowSelAlways
                        || (hItem == ptms->hItemPressed)
                        || (hItem == ptms->hDropHilite))
                    {
                        COLORREF oldColor = GetBkColor(hDC);
                        
                        if(((itemState & TVIS_SELECTED) && (ptms->hDropHilite == NULL) && (ptms->hItemPressed == NULL))
                            || (hItem == ptms->hItemPressed)
                            || (hItem == ptms->hDropHilite))
                        {
                            COLORREF rectColor;
                            if((bFocused)
                                || GetSysColor(COLOR_3DFACE) == GetSysColor(COLOR_WINDOW)
                                || (hItem == ptms->hItemPressed)
                                || (hItem == ptms->hDropHilite))
                                //note: later versions can use tree's GetBkColor()?
                            {
                                rectColor = GetSysColor(COLOR_HIGHLIGHT);
                            }
                            else
                            {
                                rectColor = GetSysColor(COLOR_3DFACE);
                            }
                            SetBkColor(hDC, rectColor);

                            ExtTextOut(hDC, 0, 0, ETO_OPAQUE,
                                bReallyFullRowSelect ? rFullItemRect : rItemTextRect, NULL, 0, NULL);
                            
                            if(bFocused
                                || GetSysColor(COLOR_3DLIGHT) == GetSysColor(COLOR_WINDOW)
                                || (hItem == ptms->hItemPressed)
                                || (hItem == ptms->hDropHilite))
                            {
                                bResetTextColor = true;
                                SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
                            }
                        }
                        
                        if(hItem == hSelectedItem && bFocused && (bReallyFullRowSelect == false))
                        {
                            DrawFocusRect(hDC, rItemTextRect);
                        }
                        
                        SetBkColor(hDC, oldColor);
                    }
                }
            }
            
            HGDIOBJ hOldFont2;
            if(itemState & TVIS_BOLD)
            {
                if(hBoldFont == NULL)
                {
                    LOGFONT LogFont;
                    GetObject(hFont, sizeof(LOGFONT), &LogFont);
                    LogFont.lfWeight = FW_BOLD;
                    hBoldFont = CreateFontIndirect(&LogFont);
                }

                hOldFont2 = SelectObject(hDC, hBoldFont);
            }
            
            DrawText(hDC, pItem->pszText, pItem->cchTextMax, rItemTextRect, DT_CENTER | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER);
            
            if(itemState & TVIS_BOLD)
            {
                VERIFY(SelectObject(hDC, hOldFont2) == hBoldFont);
            }
            
            if(bResetTextColor)
            {
                SetTextColor(hDC, GetSysColor(COLOR_WINDOWTEXT));
            }
            
            CSize StateImageSize(_GetStateImageSize(ptms, pItem, &Cache));
            
            HTREEITEM hParentItem = GetNextItem( ptms, hItem, TVGN_PARENT);
            if(bLinesAtRoot
                || (hParentItem != NULL))
            {                
                POINT ButtonCentre;
                ComputeButtonCentre(ptms, hItem, rFullItemRect, ButtonCentre, &Cache);

                if(bHasLines)
                {
                    DrawFromItemLines(hDC, ptms, bHasButtons,
                        hItem, rItemTextRect, ButtonCentre,
                        hParentItem, nItemHeight,
                        NormalImageSizeAndOffset, StateImageSize);
                }
                
                if(ITEM_HAS_BUTTON(ptms, bHasButtons, hItem))
                {
                    if(bReallyFullRowSelect)
                    {
                        CRect rCleanArea(rItemTextRect);
                        rCleanArea.right = rCleanArea.left;
                        rCleanArea.left = 2 * ButtonCentre.x - rCleanArea.right;
                        ExtTextOut(hDC, 0, 0, ETO_OPAQUE, rCleanArea, NULL, 0, NULL);
                    }

                    CRect rButtonRect;
                    rButtonRect.left = ButtonCentre.x - ptms->m_nButtonSize/2;
                    rButtonRect.right = rButtonRect.left + ptms->m_nButtonSize;
                    rButtonRect.top = ButtonCentre.y - ptms->m_nButtonSize/2;
                    rButtonRect.bottom = rButtonRect.top + ptms->m_nButtonSize;
                    
                    //note: later versions can use GetBkColor()?
                    HGDIOBJ hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
                    HGDIOBJ hOldBrush = SelectObject(hDC, hBrush);
                    HPEN hPen = CreatePen(PS_SOLID, 0, SYS_COLOR_LINES);
                    HGDIOBJ hOldPen = SelectObject(hDC, hPen);
                    Rectangle(hDC, rButtonRect.left, rButtonRect.top, rButtonRect.right, rButtonRect.bottom);                    
                    SelectObject(hDC, hOldBrush);
                    DeleteObject(hBrush);
                    SelectObject(hDC, hOldPen);
                    DeleteObject(hPen);
                    
                    if(ptms->m_nSignSize >= 1)
                    {
                        HPEN hPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_WINDOWTEXT));
                        HGDIOBJ hOldPen = SelectObject(hDC, hPen);
                        
                        if(ptms->m_nSignSize < 5)
                        {
                            POINT point;
                            MoveToEx(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y, &point);
                            LineTo(hDC, ButtonCentre.x - ptms->m_nSignSize - 1, ButtonCentre.y);
                            if((itemState & TVIS_EXPANDED) == 0)
                            {
                                MoveToEx(hDC, ButtonCentre.x, ButtonCentre.y + ptms->m_nSignSize, &point);
                                LineTo(hDC, ButtonCentre.x, ButtonCentre.y - ptms->m_nSignSize - 1);
                            }
                        }
                        else //bigger signs has to be drawn as "swiss"
                        {
                            if((itemState & TVIS_EXPANDED) == 0)
                            {
                                //+
                                POINT point;
                                MoveToEx(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y + 1, &point);
                                LineTo(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y - 1);
                                LineTo(hDC, ButtonCentre.x + 1, ButtonCentre.y - 1);
                                LineTo(hDC, ButtonCentre.x + 1, ButtonCentre.y - ptms->m_nSignSize);
                                LineTo(hDC, ButtonCentre.x - 1, ButtonCentre.y - ptms->m_nSignSize);
                                LineTo(hDC, ButtonCentre.x - 1, ButtonCentre.y - 1);
                                LineTo(hDC, ButtonCentre.x - ptms->m_nSignSize, ButtonCentre.y - 1);
                                LineTo(hDC, ButtonCentre.x - ptms->m_nSignSize, ButtonCentre.y + 1);
                                LineTo(hDC, ButtonCentre.x - 1, ButtonCentre.y + 1);
                                LineTo(hDC, ButtonCentre.x - 1, ButtonCentre.y + ptms->m_nSignSize);
                                LineTo(hDC, ButtonCentre.x + 1, ButtonCentre.y + ptms->m_nSignSize);
                                LineTo(hDC, ButtonCentre.x + 1, ButtonCentre.y + 1);
                                LineTo(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y + 1);
                            }
                            else
                            {
                                //-
                                POINT point;
                                MoveToEx(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y + 1, &point);
                                LineTo(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y - 1);
                                LineTo(hDC, ButtonCentre.x - ptms->m_nSignSize, ButtonCentre.y - 1);
                                LineTo(hDC, ButtonCentre.x - ptms->m_nSignSize, ButtonCentre.y + 1);
                                LineTo(hDC, ButtonCentre.x + ptms->m_nSignSize, ButtonCentre.y + 1);
                            }
                        }
                        
                        SelectObject(hDC, hOldPen);
                        DeleteObject(hPen);
                    }
                }
            }
            
            if(itemState & TVIS_STATEIMAGEMASK)
            {
                HIMAGELIST hStateImageList = GetImageList(ptms, TVSIL_STATE);
                if(hStateImageList != NULL)
                {
                    int nImage = BACK_FROM_INDEXTOSTATEIMAGEMASK(pItem->state & TVIS_STATEIMAGEMASK);
                    //misssing state icon clipping (when state icon higher than normal one)
                    ImageList_Draw(hStateImageList, nImage, hDC,
                        rItemTextRect.left - StateImageSize.cx - NormalImageSizeAndOffset.cx,
                        rItemTextRect.bottom - StateImageSize.cy,
                        ILD_NORMAL/*or ILD_TRANSPARENT?*/);
                }
            }
            
            HIMAGELIST hNormalImageList = GetImageList(ptms, TVSIL_NORMAL);
            if( hNormalImageList != NULL )
            {
                // Test to see if I_IMAGECALLBACK is required for either
                // the image or the selected image. Ask the parent for the
                // index of the icon if necessary.
                bool bSelected = (pItem->state & TVIS_SELECTED) != 0;
                int nImage = (bSelected) ? pItem->iSelectedImage : pItem->iImage;
                if( nImage == I_IMAGECALLBACK )
                {
                    HWND hWndParent = GetParent( ptms->hwnd );
                    if( hWndParent )
                    {
                        // This should be in a common routine for other TV_DISPINFO callbacks
                            TV_DISPINFO tv = {0};
                        tv.hdr.hwndFrom = ptms->hwnd;
                        tv.hdr.idFrom = GetWindowLong( ptms->hwnd, GWL_ID );
                        tv.hdr.code = TVN_GETDISPINFO;
                        tv.item.hItem = hItem;
                        tv.item.state = pItem->state;
                        tv.item.lParam = pItem->lParam;
                        tv.item.mask = TVIF_HANDLE|TVIF_PARAM|TVIF_STATE;
                        
                        // Set the proper mask for the required icon.
                        if( bSelected )
                        {
                            tv.item.mask |= TVIF_SELECTEDIMAGE;
                            tv.item.iSelectedImage = nImage;
                        }
                        else
                        {
                            tv.item.mask |= TVIF_IMAGE;
                            tv.item.iImage = nImage;
                        }
                        
                        // Ask the parent for the image index.
                        // CWnd::OnNotify() states: "An application returns nonzero
                        // if it processes this message; otherwise 0."
                        if( SendMessage( hWndParent, WM_NOTIFY, tv.hdr.idFrom, (LPARAM)&tv ) != 0 )
                            nImage = (bSelected) ? tv.item.iSelectedImage : tv.item.iImage;
                    }
                }
                
                ImageList_Draw( hNormalImageList, nImage, hDC,
                    rItemTextRect.left - NormalImageSizeAndOffset.cx,
                    (rItemTextRect.top - rItemTextRect.bottom)/2 + rItemTextRect.bottom - NormalImageSizeAndOffset.cy/2,
                    ILD_NORMAL/*or ILD_TRANSPARENT?*/);
            }
        }

        hItem = GetNextItem( ptms, hItem, TVGN_NEXTVISIBLE);
    }

    if(bHasLines)
    {
        //hItem != NULL: was not drawn till end - draw lines left/under last drawn item
        //hItem is now (at while start):
        //next item to last drawn item
        //or its first child
        //or next item of its parent
        
        while(hItem != NULL)
        {
            HTREEITEM hParentItem = GetNextItem( ptms, hItem, TVGN_PARENT);
            
            if(bLinesAtRoot
                || (hParentItem != NULL))
            {
                LPRGTVITEM pItem = ptms->rgTree.GetAt( (POSITION)hItem);
                
                CSize StateImageSize(_GetStateImageSize(ptms, pItem, &Cache));
                
                CRect rItemTextRect(rFullItemRect);
                _GetItemTextRect(ptms, hItem, pItem, &rFullItemRect, &rItemTextRect, &Cache);
                
                POINT ButtonCentre;
                ComputeButtonCentre(ptms, hItem, rFullItemRect, ButtonCentre, &Cache);
                
                DrawFromItemLines(hDC, ptms, bHasButtons,
                    hItem, rItemTextRect, ButtonCentre,
                    hParentItem, nItemHeight,
                    NormalImageSizeAndOffset, StateImageSize);
            }
            
            if(hParentItem)
            {
                int offset = nItemHeight * GetLineOffsetOfItems(ptms, hParentItem, hItem);
                rFullItemRect.top -= offset;
                rFullItemRect.bottom -= offset;
            }
            hItem = hParentItem;
            
            while(hItem != NULL)
            {
                HTREEITEM hNext = GetNextItem( ptms, hItem, TVGN_NEXT);
                if(hNext == NULL)
                {
                    hParentItem = GetNextItem( ptms, hItem, TVGN_PARENT);
                    if(hParentItem)
                    {
                        int offset = nItemHeight * GetLineOffsetOfItems(ptms, hParentItem, hItem);
                        rFullItemRect.top -= offset;
                        rFullItemRect.bottom -= offset;
                    }
                    hItem = hParentItem;
                    //continue in nearest while
                }
                else
                {
                    int offset = nItemHeight * GetLineOffsetOfItems(ptms, hItem, hNext);
                    rFullItemRect.top += offset;
                    rFullItemRect.bottom += offset;
                    hItem = hNext;
                    break; //break from nearest while
                }
            }
        }
    }
    
    SelectObject( hDC, hOldFont);
    if(hBoldFont)
        DeleteObject(hBoldFont);

    // Deinitialize double buffering
    // Transfer the off-screen DC to the screen
    BitBlt(hDCOriginal, 0, 0, win_width, win_height, hDC, 0, 0, SRCCOPY);

    // Free-up the off-screen DC
    SelectObject(hDC, hOld);
    DeleteObject(hbmMem);
    DeleteDC    (hDC);

    if( wParam == 0)
        EndPaint( ptms->hwnd, &ps);
    else
        SetBkMode( hDCOriginal, nOldBkMode);

    return 0;
}

/**************************************************************************
 *                                                                        *
 *                              TVM - Messages                            *
 *                                                                        *
 **************************************************************************/


// TVM_CREATEDRAGEIMAGE
static LRESULT OnCreateDragImage( TREE_MAP_STRUCT *ptms, LPARAM lParam)
{
    HIMAGELIST hImageList = NULL;
    HTREEITEM hItem = (HTREEITEM)lParam;
    
    HIMAGELIST hNormalImageList = GetImageList(ptms, TVSIL_NORMAL);
    if(hNormalImageList) //not understable system tree logic
    {
        CRect rect(0,0,0,0);
        CSize StateImageSize(0,0);
        CSize NormalImageSizeAndOffset(0,0);
        LPRGTVITEM pItem = NULL;
        UINT itemState = 0;

        if(hItem)
        {
            GetItemRect(ptms, hItem, rect, TRUE);
            rect.OffsetRect(-rect.left, -rect.top);

            pItem = ptms->rgTree.GetAt((POSITION)hItem);
            itemState = pItem->state;

            GetItemTextRectCache Cache(ptms->hwnd);    

            if(itemState & TVIS_STATEIMAGEMASK)
            {
                StateImageSize =  _GetStateImageSize(ptms, pItem, &Cache);
                rect.right += StateImageSize.cx;
            }

            if(hNormalImageList)
            {
                NormalImageSizeAndOffset = _GetNormalImageSizeAndOffset(ptms, &Cache);
                rect.right += NormalImageSizeAndOffset.cx;
            }
        }
        
        HDC hClientDC = GetDC(ptms->hwnd);

        HDC hMemDC = CreateCompatibleDC(hClientDC);
        if(hMemDC == NULL)
        {
            return NULL;
        }
        
        HGDIOBJ hBitmap = CreateCompatibleBitmap(hClientDC, rect.Width(), rect.Height());
        if(hBitmap == NULL)
        {
            DeleteDC(hMemDC);
            return NULL;
        }
        
        HGDIOBJ hOldMemDCBitmap = SelectObject(hMemDC, hBitmap);

        COLORREF mask = RGB(0, 255, 0);
        
        SetBkColor(hMemDC, mask);
        ExtTextOut(hMemDC, 0, 0, ETO_OPAQUE, rect, NULL, 0, NULL);

        if(hItem)
        {
            HGDIOBJ hWndFont = (HFONT)SNDMSG( ptms->hwnd, WM_GETFONT, 0, 0);
            
            HGDIOBJ hBoldFont = NULL;
            if(itemState & TVIS_BOLD)
            {
                LOGFONT LogFont;
                GetObject(hWndFont, sizeof(LOGFONT), &LogFont);
                LogFont.lfWeight = FW_BOLD;
                hBoldFont = CreateFontIndirect(&LogFont);
            }
            
            HGDIOBJ hOldFont = SelectObject(hMemDC, (itemState & TVIS_BOLD) ? hBoldFont : hWndFont);
            
            CRect rItemTextRect(rect);
            rItemTextRect.left += StateImageSize.cx + NormalImageSizeAndOffset.cx;
            DrawText(hMemDC, pItem->pszText, pItem->cchTextMax, rItemTextRect, DT_CENTER | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER);
            
            SelectObject(hMemDC, hOldFont);
            if(hBoldFont)
            {
                DeleteObject(hBoldFont);
            }

            if(itemState & TVIS_STATEIMAGEMASK)
            {
                HIMAGELIST hStateImageList = GetImageList(ptms, TVSIL_STATE);
                if(hStateImageList != NULL)
                {
                    int nImage = BACK_FROM_INDEXTOSTATEIMAGEMASK(pItem->state & TVIS_STATEIMAGEMASK);
                    //misssing state icon clipping (when state icon higher than normal one)
                    ImageList_Draw(hStateImageList, nImage, hMemDC,
                        rItemTextRect.left - StateImageSize.cx - NormalImageSizeAndOffset.cx,
                        rItemTextRect.bottom - StateImageSize.cy,
                        ILD_NORMAL/*or ILD_TRANSPARENT?*/);
                }
            }
            
            if(hNormalImageList != NULL)
            {
                HTREEITEM hSelectedItem = ptms->hItemSelected;

                int nImage = (hItem == hSelectedItem) ? pItem->iSelectedImage : pItem->iImage;
                ImageList_Draw(hNormalImageList, nImage, hMemDC,
                    rItemTextRect.left - NormalImageSizeAndOffset.cx,
                    (rItemTextRect.top - rItemTextRect.bottom)/2 + rItemTextRect.bottom - NormalImageSizeAndOffset.cy/2,
                    ILD_NORMAL/*or ILD_TRANSPARENT?*/);
            }
        }
        
        SelectObject(hMemDC, hOldMemDCBitmap );
        
        hImageList = ImageList_Create(rect.Width(), rect.Height(), ILC_COLOR | ILC_MASK, 0, 1);
        if(hImageList)
        {
            ImageList_AddMasked(hImageList, (HBITMAP)hBitmap, mask);
        }
        else
        {
            DeleteObject(hBitmap);
        }

        DeleteDC(hMemDC);
    }

    return (LRESULT)hImageList;
}

static POSITION GetTopLevelParentPos( _rgTree& rgTree, POSITION pos)
{
    POSITION TopParentPos = pos;
    while( pos = rgTree.GetParentPosition( pos))
    {
        TopParentPos = pos;
    }
    return TopParentPos;
}

static bool IsBeforeFirstVisibleItem(TREE_MAP_STRUCT *ptms, HTREEITEM hTestedItem)
{
    ASSERT(ptms->hItemFirstVisible != NULL);
    ASSERT(hTestedItem != NULL);

    //if(ptms->hItemFirstVisible == NULL)
    //{
    //    return false;
    //}

    if(ptms->hItemFirstVisible == hTestedItem)
    {
        return false;
    }

    HTREEITEM hFirstVisibleTopParent = (HTREEITEM)GetTopLevelParentPos(ptms->rgTree, (POSITION)ptms->hItemFirstVisible);

    //if(hFirstVisibleTopParent == GetNextItem( ptms, NULL, TVGN_ROOT))
    //{
    //    return false;
    //}

    HTREEITEM hNewItemTopParent = (HTREEITEM)GetTopLevelParentPos(ptms->rgTree, (POSITION)hTestedItem);

    if(hFirstVisibleTopParent == hNewItemTopParent) //items have the same parent
    {        
        //search in subitems what will be found sooner

        //(can be quicker search in childs with TVGN_NEXT only with "optimized" IsAnyLevelParent()?,
        //when item is not equal to one of searched still can be parent for both of them so...)

        for(HTREEITEM hItem = hFirstVisibleTopParent; true; hItem = GetNextItem(ptms, hItem, TVGN_NEXTVISIBLE))
        {
            ASSERT(hItem != NULL);
            if(hItem == ptms->hItemFirstVisible)
            {
                return false;
            }

            if(hItem == hTestedItem)
            {
                return true;
            }
        }
    }

    //look what can be (can be only) quicker - search from hItemFirstVisible to begin or to end
    if((ptms->nVisibleItemCount - ptms->nVScrollPos) >= ptms->nVScrollPos)
    {
        //search to begin
        for(HTREEITEM hItem = hFirstVisibleTopParent; hItem != NULL; hItem = GetNextItem(ptms, hItem, TVGN_PREVIOUS))
        {
            if(hItem == hNewItemTopParent)
            {
                return true;
            }
        }
    }
    else
    {
        //search to end
        for(HTREEITEM hItem = hFirstVisibleTopParent; hItem != NULL; hItem = GetNextItem(ptms, hItem, TVGN_NEXT))
        {
            if(hItem == hNewItemTopParent)
            {
                return false;
            }
        }
        return true;
    }

    return false;
}

// TVM_DELETEITEM
static LRESULT OnDeleteItem( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    HTREEITEM hItem = (HTREEITEM)lParam;
    if( hItem == NULL)
        hItem = TVI_ROOT;
    if( hItem == TVI_ROOT)
    {
        if(ptms->hItemSelected != NULL)
        {
            bool bCallSelchanged = false;
            NMTREEVIEW nmtv;
            SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, TVC_UNKNOWN, ptms->hItemSelected, NULL);
            if(PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGING))
            {
                bCallSelchanged = true;
            }
            ptms->hItemSelected = NULL;
            KillTimer( ptms->hwnd, ID_SHOW_TIMER);
            KillTimer( ptms->hwnd, ID_EDIT_TIMER);
            EndEditLabelNow( ptms, TRUE);

            if(bCallSelchanged)
            {
                SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, TVC_UNKNOWN, nmtv.itemOld.hItem, ptms->hItemSelected);
                PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGED);
            }
        }
        ptms->hItemFirstVisible = NULL;
        _CancelItemPressed(ptms);
        ptms->hDropHilite = NULL;

        ptms->rgTree.RemoveAll();
        
        ptms->nVisibleItemCount = ptms->nVScrollPos = ptms->nHScrollPos = 0;
        //SNDMSG( ptms->hwnd, WM_SETREDRAW, TRUE, 0);
        if( ptms->bRedrawFlag)
        {
            if(SETSCROLLBARS(ptms) == false)
                InvalidateRect(ptms->hwnd, NULL, TRUE);
        }
        return TRUE;
    }

    KillTimer( ptms->hwnd, ID_EDIT_TIMER);
    EndEditLabelNow( ptms, TRUE);

    HTREEITEM hNewItemFirstVisible = NULL;
    if(ptms->hItemFirstVisible)
    {
        if( hItem == ptms->hItemFirstVisible
            || IsAnyLevelParent(ptms, hItem, ptms->hItemFirstVisible))
            //hItemFirstVisible will be deleted, find new one
        {
            hNewItemFirstVisible = GetNextItem( ptms, hItem, TVGN_NEXT);
            if(hNewItemFirstVisible == NULL)
            {
                hNewItemFirstVisible = GetNextItem( ptms, hItem, TVGN_PARENT);
                if(hNewItemFirstVisible == NULL)
                {
                    hNewItemFirstVisible = GetNextItem( ptms, hItem, TVGN_PREVIOUS);
                }
            }

        }
    }

    bool bDoScrollAbsolutelyDown = false;

    if( IsItemVisible( ptms->rgTree, (POSITION)hItem))
    {
        UINT nCount = 1;
        AddVisibleChildCount( ptms->rgTree, (POSITION)hItem, nCount);

        UINT nVisibleCount = GetVisibleCount(ptms);

        ptms->nVisibleItemCount -= nCount;

        if(hNewItemFirstVisible == NULL)
        {
            //when we deleting item before first visible item needs to decrease nVScroll pos with nCount too
            bool bIsBefore = IsBeforeFirstVisibleItem (ptms, hItem);
            if(bIsBefore)
            {
                ptms->nVScrollPos -= nCount;
            }
        }

        if((ptms->nVScrollPos + (int)nVisibleCount) > ptms->nVisibleItemCount)
        {
            //ptms->hItemFirstVisible = NULL; //not now
            //hNewItemFirstVisible = NULL; //not now
            bDoScrollAbsolutelyDown = true;
        }
    }

    if(ptms->hItemSelected)
    {
        if( hItem == ptms->hItemSelected
            || IsAnyLevelParent(ptms, hItem, ptms->hItemSelected))
            //hItemSelected will be deleted, find new one
        {
            HTREEITEM hItemNew = GetNextItem( ptms, hItem, TVGN_NEXT);            
            if(hItemNew == NULL)
            {
                hItemNew = GetNextItem( ptms, hItem, TVGN_PARENT);
                if(hItemNew == NULL)
                {
                    hItemNew = GetNextItem( ptms, hItem, TVGN_PREVIOUS);
                }
            }

            NMTREEVIEW nmtv;
            SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, TVC_UNKNOWN, ptms->hItemSelected, hItemNew);
            if(PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGING))
            {
                ptms->hItemSelected = NULL;
                KillTimer( ptms->hwnd, ID_SHOW_TIMER);
                KillTimer( ptms->hwnd, ID_EDIT_TIMER);
                EndEditLabelNow( ptms, TRUE);
            }
            else
            {
                ptms->hItemSelected = hItemNew;
                KillTimer( ptms->hwnd, ID_SHOW_TIMER);
                KillTimer( ptms->hwnd, ID_EDIT_TIMER);
                EndEditLabelNow( ptms, TRUE);

                if(ptms->hItemSelected != NULL)
                {
                    ptms->rgTree.GetAt( (POSITION)ptms->hItemSelected)->state |= TVIS_SELECTED;
                }
                SetNMTREEVIEWforSELCHANGE(ptms, &nmtv, TVC_UNKNOWN, nmtv.itemOld.hItem, ptms->hItemSelected);
                PSNDNMSG(ptms->hwnd, nmtv, TVN_SELCHANGED);
            }
        }
    }
    
    if(ptms->hItemPressed)
    {
        if( hItem == ptms->hItemPressed
            || IsAnyLevelParent(ptms, hItem, ptms->hItemPressed))
            //hItemPressed will be deleted, reset it
        {
            ptms->hItemPressed = NULL;
        }
    }

    if(ptms->hItemOrigPressed)
    {
        if( hItem == ptms->hItemOrigPressed
            || IsAnyLevelParent(ptms, hItem, ptms->hItemOrigPressed))
            //hItemPressed will be deleted, reset it
        {
            ptms->hItemOrigPressed = NULL;
        }
    }

    if(ptms->hDropHilite)
    {
        if( hItem == ptms->hDropHilite
            || IsAnyLevelParent(ptms, hItem, ptms->hDropHilite))
            //hDropHilite will be deleted, reset it
        {
            ptms->hDropHilite = NULL;
        }
    }

    ptms->rgTree.RemoveAt( (POSITION)hItem);

    if(hNewItemFirstVisible)
    {
        ptms->hItemFirstVisible = NULL;
        SetFirstVisibleItem( ptms, hNewItemFirstVisible);
    }

    if(bDoScrollAbsolutelyDown || (ptms->nVisibleItemCount == 0))
    {
        if(ptms->nVisibleItemCount)
        {
			UINT nVisibleCount = GetVisibleCount(ptms);

			if((ptms->nVScrollPos + (int)nVisibleCount) > ptms->nVisibleItemCount)
			{
				hNewItemFirstVisible = _ScrollAbsolutelyDown(ptms, nVisibleCount);
			}
            ASSERT(hNewItemFirstVisible != NULL);
        }
        else
            hNewItemFirstVisible = NULL;

        ptms->hItemFirstVisible = NULL;
        SetFirstVisibleItem( ptms, hNewItemFirstVisible);
    }

    ASSERT((ptms->nVisibleItemCount != 0 && ptms->hItemFirstVisible != NULL)
        || (ptms->nVisibleItemCount == 0 && ptms->hItemFirstVisible == NULL));

    if( ptms->bRedrawFlag)
    {
        if(SETSCROLLBARS(ptms) == false)
            InvalidateRect(ptms->hwnd, NULL, TRUE);
    }
    return TRUE;
}

// TVM_EDITLABEL
static LRESULT OnEditLabel( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    LPRGTVITEM pItem = ptms->rgTree.GetAt( (POSITION)lParam);

    NMTVDISPINFO tvdi;
    SetTVITEMforNotify(ptms, &tvdi.item, (HTREEITEM)lParam, TVIF_STATE | TVIF_PARAM | TVIF_HANDLE);
    tvdi.item.mask |= TVIF_TEXT;
    tvdi.item.pszText = pItem->pszText;
    tvdi.item.cchTextMax = pItem->cchTextMax;

    if( PSNDNMSG(ptms->hwnd, tvdi, TVN_BEGINLABELEDIT))
        return 0;

    Select(ptms, (HTREEITEM)lParam, TVGN_CARET, false);
    EnsureVisible(ptms, (HTREEITEM)lParam, false);
    GetFocus();
    CRect rcItem;
    GetItemRect( ptms, (HTREEITEM)lParam, &rcItem, TRUE);
    rcItem.top--;
    rcItem.right += 20;

    RECT rc;
    GetClientRect( ptms->hwnd, &rc);

    if( rcItem.right > rc.right)
        rcItem.right = rc.right;
    MoveWindow( ptms->hWndEdit, rcItem.left, rcItem.top, rcItem.Width(), rcItem.Height(), FALSE);
    ClientToScreen( ptms->hwnd, (LPPOINT)&rcItem);
    ClientToScreen( ptms->hwnd, ((LPPOINT)&rcItem)+1);
    ClientToScreen( ptms->hwnd, (LPPOINT)&rc);
    ClientToScreen( ptms->hwnd, ((LPPOINT)&rc)+1);
    SetEditPosition( ptms->hWndEdit, rcItem, rc);

    SetWindowText( ptms->hWndEdit, tvdi.item.pszText);
    SNDMSG(ptms->hWndEdit, EM_SETSEL, 0, -1);
    ShowWindow( ptms->hWndEdit, SW_SHOW);
    SetFocus( ptms->hWndEdit);
    ptms->hItemEditing = (HTREEITEM)lParam;
    return lParam;
}

// TVM_GETITEM
static LRESULT OnGetItem( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    LPTVITEM pItem = (LPTVITEM)lParam;
    const LPRGTVITEM pTempItem = ptms->rgTree.GetAt((POSITION)pItem->hItem);
    if( pItem->mask & TVIF_TEXT)
    {
        int len = pTempItem->cchTextMax+1;
        if( len > pItem->cchTextMax)
            len = pItem->cchTextMax;
        memcpy( pItem->pszText, pTempItem->pszText, (len-1)*sizeof(TCHAR));
        pItem->pszText[len-1] = 0;
    }
    if( pItem->mask & TVIF_CHILDREN)
    {
        pItem->cChildren = ptms->rgTree.GetChildCount( (POSITION)pItem->hItem) != 0 ? 1 : 0;
    }
    if( pItem->mask & TVIF_PARAM)
    {
        pItem->lParam = pTempItem->lParam;
    }
    if( pItem->mask & TVIF_IMAGE)
    {
        pItem->iImage = pTempItem->iImage;
    }
    if( pItem->mask & TVIF_SELECTEDIMAGE)
    {
        pItem->iSelectedImage = pTempItem->iSelectedImage;
    }
    if( pItem->mask & TVIF_STATE)
    {
        pItem->state = pTempItem->state;
    }
    return TRUE;
}

//if newly inserted item is before first visible must be vscroll pos incremented
static void InsertItem_UpdateVScrollPos(TREE_MAP_STRUCT *ptms, HTREEITEM hNewItem)
{
    ASSERT(ptms->hItemFirstVisible != NULL);

    if(IsBeforeFirstVisibleItem(ptms, hNewItem))
    {
        ptms->nVScrollPos++; //new before first visible
    }
}

// TVM_INSERTITEM
static LRESULT OnInsertItem( TREE_MAP_STRUCT *ptms, WPARAM wParam, LPARAM lParam)
{
    LPTVINSERTSTRUCT lptvi = (LPTVINSERTSTRUCT)lParam;
	if (lptvi == NULL) {
		ptms->nScrollMax++;
		return (LRESULT)0;
	}
    POSITION posParent = lptvi->hParent == TVI_ROOT ? NULL : (POSITION)lptvi->hParent;
	UINT ic = ptms->rgTree.GetItemCount();
	static DWORD timeValueOnInsertionStart;

	if (ic == 0) {
		timeValueOnInsertionStart = GetTickCount();
	}

	if (ic == 25000) {
		timeValueOnInsertionStart = GetTickCount() - timeValueOnInsertionStart;
		printf("Nodes time: %d\n", timeValueOnInsertionStart);
	}

    RGTVITEM item;
    item.state = (lptvi->item.mask & TVIF_STATE) ? lptvi->item.state : 0;
    item.lParam = (lptvi->item.mask & TVIF_PARAM) ? lptvi->item.lParam : 0;
    item.iImage = (lptvi->item.mask & TVIF_IMAGE) ? lptvi->item.iImage : 0;
    item.iSelectedImage = (lptvi->item.mask & TVIF_SELECTEDIMAGE) ? lptvi->item.iSelectedImage : 0;
    if((lptvi->item.pszText != NULL) && (lptvi->item.mask & TVIF_TEXT))
    {
        item.cchTextMax = _tcslen( lptvi->item.pszText);
        item.pszText = new TCHAR[item.cchTextMax+1];
        memcpy( item.pszText, lptvi->item.pszText, (item.cchTextMax+1)*sizeof(TCHAR));
    }
    else
    {
        item.cchTextMax = 0;
        item.pszText = NULL;
    }
    item.ItemTextWidth = 0;

    POSITION posItem;
    if( lptvi->hInsertAfter == TVI_FIRST)
        posItem = ptms->rgTree.AddHead( &item, posParent);
    else if( lptvi->hInsertAfter == TVI_LAST)
        posItem = ptms->rgTree.AddTail( &item, posParent);
    else if( lptvi->hInsertAfter == TVI_SORT)
        ASSERT(!(posItem = NULL)); //missing case
    else
        posItem = ptms->rgTree.InsertAfter( &item, posParent, (POSITION)lptvi->hInsertAfter);

    if(posItem != NULL)
    {
        if( ptms->hItemFirstVisible == NULL)
        {
            ptms->hItemFirstVisible = (HTREEITEM)posItem;
            ASSERT(ptms->nVScrollPos == 0);
        }
        if( IsItemVisible( ptms->rgTree, posItem))
        {
            ptms->nVisibleItemCount++;
            InsertItem_UpdateVScrollPos(ptms, (HTREEITEM)posItem);
        }
        if( ptms->bRedrawFlag)
        {
            if(SETSCROLLBARS(ptms) == false)
                InvalidateRect( ptms->hwnd, NULL, TRUE);
        }
    }

    return (LRESULT)posItem;
}

#ifdef RG_TREE_WITH_WND_PROC_MAP
static CMap<HWND, HWND, TREE_MAP_STRUCT*, TREE_MAP_STRUCT*> WndProcMap;
#endif

LRESULT CALLBACK RGTreeWindowProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  register TREE_MAP_STRUCT *ptms;
#ifdef RG_TREE_WITH_WND_PROC_MAP
    WndProcMap.Lookup( hwnd, ptms);
#else
    ptms = (TREE_MAP_STRUCT*)GetWindowLong( hwnd, GWL_USERDATA);
#endif

    switch( uMsg)
    {
        case WM_CREATE:
            {
                TREE_MAP_STRUCT *ptms = new TREE_MAP_STRUCT;
#ifndef RG_TREE_WITH_WND_PROC_MAP
                SetWindowLong( hwnd, GWL_USERDATA, (LONG)ptms);
#endif
                ptms->pOldWndProc = (WNDPROC)SetWindowLong( hwnd, GWL_WNDPROC, (LONG)RGTreeWindowProc);
                ptms->hwnd = hwnd;
                ptms->rgTree.SetCompareFunc( Compare);
                ptms->rgTree.SetDeleteFunc( OnDelete, (LPARAM)ptms);
#ifdef RG_TREE_WITH_WND_PROC_MAP
                WndProcMap.SetAt( hwnd, ptms);
#endif
                ptms->hWndEdit = CreateWindow( _T("EDIT"), NULL, WS_CHILD|WS_BORDER|ES_WANTRETURN|ES_MULTILINE|ES_AUTOHSCROLL, 0, 0, 0, 0, hwnd, NULL, (HINSTANCE)lParam, (LPVOID)ID_EDIT);
                RGTreeEditWindowProc( ptms->hWndEdit, WM_CREATE, 0, 0);
                SNDMSG( ptms->hWndEdit, WM_SETFONT, SNDMSG(hwnd, WM_GETFONT, 0, 0), 0);
            }
            return 0;

        case WM_DESTROY:
            OnDeleteItem( ptms, 0, (LPARAM)TVI_ROOT);
            DestroyWindow( ptms->hWndEdit);
            break;

        case WM_FONTCHANGE:
        case WM_SETFONT:
            ptms->nItemHeight = 0; //will be recomputed
            break;

        case WM_HSCROLL:
        		//Gensym-538 fix
            //DoScroll(ptms, SB_HORZ, LOWORD(wParam), HIWORD(wParam));
            DoScroll(ptms, SB_HORZ, LOWORD(wParam), HIWORD(wParam), TRUE);
            return 0;

        case WM_KEYDOWN:
            return OnKeyDown( ptms, wParam, lParam);

        case WM_LBUTTONDBLCLK:
            return OnLButtonDblClk( ptms, wParam, lParam);

        case WM_LBUTTONDOWN:
            if( ptms->hItemFirstVisible)
            {
                TVHITTESTINFO tvhti;
                PT_FILL( tvhti.pt, lParam);
                HTREEITEM hItem = HitTest( ptms, &tvhti);
                
                if(hItem)
                {
                    if(ptms->bIsPressed == false)
                    {
                        DWORD style = GetWindowStyle(hwnd);
                        if(tvhti.flags & TVHT_ONITEM 
                           // not TVHT_ONITEMLABEL because we want to handle clicks on bitmap as well
                            || ((tvhti.flags & (TVHT_ONITEMINDENT | TVHT_ONITEMRIGHT))
                            && (style & TVS_FULLROWSELECT)
                            && (style & TVS_HASLINES) == 0))
                        {
                            if((style & TVS_DISABLEDRAGDROP) == 0)
                            {
                                ptms->bIsPressed = true;
                                ptms->hItemOrigPressed = ptms->hItemPressed = hItem;
                                ptms->bPressedLeft = true;
                                PT_FILL(ptms->ptPressed, lParam);
                                
                                if(ptms->hItemSelected)
                                    InvalidateItemRect(ptms, ptms->hItemSelected, TRUE);
                                InvalidateItemRect(ptms, ptms->hItemPressed, FALSE);
                                if(ptms->hDropHilite)
                                    InvalidateItemRect(ptms, ptms->hDropHilite, TRUE);
                                
                                SetCapture(ptms->hwnd);
								
								//Gensym-2085
								//Send selected even when the user click a tree item with left click
								Select( ptms, hItem, TVGN_CARET, true);
								
                                //break;
                                return 0; //no SetFocus
                            }
                            else
                            {
                                if(ptms->hItemSelected != hItem)
                                {
                                    Select( ptms, hItem, TVGN_CARET, true);
                                }
                                else
                                {
                                    if(style & TVS_EDITLABELS)
                                    {
                                        HWND oldhwnd = SetFocus(hwnd);
                                        
                                        if(oldhwnd == hwnd)
                                            SetTimer( hwnd, ID_EDIT_TIMER, GetDoubleClickTime(), NULL);

                                        return 0; //already was SetFocus
                                    }
                                }
                            }                                
                        }
                        else
                        {
                            if(tvhti.flags & TVHT_ONITEMBUTTON)
                            {
                                Expand( ptms, hItem, TVE_TOGGLE, TRUE);
                            }
                        }
                        
                    }
                    else
                    {
                        ASSERT(ptms->bPressedLeft == false);
                        
                        CancelItemPressed(ptms);
                    }
                }
            }
            
            SetFocus(hwnd);
            //break;
            return 0;

        case WM_MOUSEMOVE:
			//{{suzsoft Added for Gensym-452
			{
				TVHITTESTINFO tvhti;
				PT_FILL( tvhti.pt, lParam);
                HTREEITEM hItem = HitTest( ptms, &tvhti);

				NMTVGETINFOTIP infoTip;
				infoTip.hdr.code = TVN_GETINFOTIP;
				infoTip.hdr.hwndFrom = hwnd;
				infoTip.hdr.idFrom = GetDlgCtrlID(hwnd);
				infoTip.hItem = hItem;
			
				SendMessage( hwnd, WM_NOTIFY, GetDlgCtrlID(hwnd), (LPARAM)&infoTip );
			}
			//}}Suzsoft
			
            if(ptms->bIsPressed)
            {
                POINT pt;
                PT_FILL(pt, lParam);
                
                if((abs((int)ptms->ptPressed.x - (int)pt.x) > GetSystemMetrics( SM_CXDRAG )
                    || abs((int)ptms->ptPressed.y - (int)pt.y) > GetSystemMetrics( SM_CYDRAG )) )
                {
                    bool bPressedLeft = ptms->bPressedLeft;
                    HTREEITEM hItemPressed = ptms->hItemOrigPressed;

                    if(bPressedLeft)
                    {
                        CancelItemPressed(ptms);
                    }
                                            
                    if(hItemPressed)
                    {
                        DWORD style = GetWindowStyle(hwnd);
                        if((style & TVS_DISABLEDRAGDROP) == 0
                            || bPressedLeft == false)
                        {
                            HWND hWndParent = GetParent(ptms->hwnd);
                            if (hWndParent)
                            {
                                LPRGTVITEM pItem = ptms->rgTree.GetAt( (POSITION)hItemPressed);
                                
                                NM_TREEVIEW tv;
                                
                                tv.hdr.hwndFrom = ptms->hwnd;
                                tv.hdr.idFrom = GetWindowLong(ptms->hwnd, GWL_ID );
                                tv.hdr.code = bPressedLeft ? TVN_BEGINDRAG : TVN_BEGINRDRAG;
                                
                                tv.itemNew.hItem = hItemPressed;
                                tv.itemNew.state = pItem->state;
                                tv.itemNew.lParam = pItem->lParam;
                                
                                tv.ptDrag = pt;
                                
                                SendMessage(hWndParent, WM_NOTIFY, tv.hdr.idFrom, (LPARAM)&tv );
                            }
                        }
                    }

                    CancelItemPressed(ptms);
                }
            }
            return 0;
            
        case WM_LBUTTONUP:
            if(ptms->bIsPressed == true)
            {
                HTREEITEM hItemOrigPressed = ptms->hItemOrigPressed;
                _CancelItemPressed(ptms);

                if(hItemOrigPressed && hItemOrigPressed != ptms->hItemSelected)
                {
                    Select( ptms, hItemOrigPressed, TVGN_CARET, true);
                    
                    SetFocus(hwnd);
                }
                else
                {
                    if(GetWindowStyle(hwnd) & TVS_EDITLABELS)
                    {
                        HWND oldhwnd = SetFocus(hwnd);
                        
                        if(oldhwnd == hwnd)
                            SetTimer( hwnd, ID_EDIT_TIMER, GetDoubleClickTime(), NULL);
                    }
                }
                
            }
            return 0;

        case WM_RBUTTONDOWN:
            if( ptms->hItemFirstVisible)
            {
                TVHITTESTINFO tvhti;
                PT_FILL( tvhti.pt, lParam);
                HTREEITEM hItem = HitTest( ptms, &tvhti);
                
                if(hItem)
                {
                    if(ptms->bIsPressed == false)
                    {
                        ptms->bIsPressed = true;
                        ptms->hItemOrigPressed = ptms->hItemPressed = hItem;
                        PT_FILL(ptms->ptPressed, lParam);
                        ptms->bPressedLeft = false;
                        
                        if(ptms->hItemSelected)
                            InvalidateItemRect(ptms, ptms->hItemSelected, TRUE);
                        InvalidateItemRect(ptms, ptms->hItemPressed, FALSE);
                        if(ptms->hDropHilite)
                            InvalidateItemRect(ptms, ptms->hDropHilite, TRUE);
                        
                        SetCapture(ptms->hwnd);
                    }
                    else
                    {
                        HTREEITEM hItemOrigPressed = ptms->hItemOrigPressed;
                        _CancelItemPressed(ptms);

                        if(hItemOrigPressed && hItemOrigPressed != ptms->hItemSelected)
                        {
                            Select( ptms, hItemOrigPressed, TVGN_CARET, true);
                        }
                        else
                        {
                            if(GetWindowStyle(hwnd) & TVS_EDITLABELS)
                            {
                                SetTimer( hwnd, ID_EDIT_TIMER, GetDoubleClickTime(), NULL);
                            }
                        }

                    }
                }
            }
            return 0;

        case WM_RBUTTONUP:
            SetFocus( hwnd );

            {
                POINT pt;
                PT_FILL(pt, lParam);
                
                if((abs((int)ptms->ptPressed.x - (int)pt.x) > GetSystemMetrics( SM_CXDRAG )
                    || abs((int)ptms->ptPressed.y - (int)pt.y) > GetSystemMetrics( SM_CYDRAG )) )
                {
                    SNDMSG(hwnd, WM_CONTEXTMENU, (WPARAM) hwnd, GetMessagePos());
                }
                else
                {
                    TVHITTESTINFO tvhti;
                    PT_FILL( tvhti.pt, lParam );
                    HTREEITEM hItem = HitTest( ptms, &tvhti );
                    
                    // Notify the parent of a RCLICK event via the WM_NOTIFY handler.
                    NMTREEVIEW nmTV = {0};
                    SetTVITEMforNotify( ptms, &nmTV.itemNew, hItem, TVIF_PARAM | TVIF_HANDLE );
                    if(PSNDNMSG( hwnd, nmTV, NM_RCLICK ) == 0)
                    {
                        PSNDMSG(hwnd, WM_CONTEXTMENU, (WPARAM) hwnd, GetMessagePos());
                    }
                }
            }

            // Cancel the item pressed stuff.
            if( ptms->bIsPressed == true)
                CancelItemPressed( ptms );

            return 0;

        case WM_SETFOCUS:
            if(ptms->hItemSelected == NULL
                && ptms->hItemFirstVisible != NULL)
            {
                Select( ptms, ptms->hItemFirstVisible, TVGN_CARET, false);
            }
            else
            {
                if(ptms->hItemSelected != NULL)
                {
                    InvalidateItemRect(ptms, ptms->hItemSelected, FALSE);
                }
            }
            break;

        case WM_SIZE:            
            if(wParam == SIZE_RESTORED)
            {
                //int x = HIWORD(lParam);
                //int y = LOWORD(lParam);
                if( ptms->bRedrawFlag)
                {
					_ScrollAbsolutelyDownWhenRequired(ptms);
					
					if(SETSCROLLBARS(ptms) == false)
					{
						if(ptms->bInSetScrollBars == false)
							RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE);
						else
							ptms->bInSetScrollBarsDoRedraw = true;
					}
				}
            }
            break;

        case WM_KILLFOCUS:
        case WM_CAPTURECHANGED:
            if(ptms->bIsPressed == true)
            {
                if(ptms->bPressedLeft == true)
                {
                    HTREEITEM hItemOrigPressed = ptms->hItemOrigPressed;
                    _CancelItemPressed(ptms);
                    if(hItemOrigPressed)
                        Select( ptms, hItemOrigPressed, TVGN_CARET, false);
                }
                else
                {
                    CancelItemPressed(ptms);

                    ASSERT( ptms->hItemFirstVisible);
                    
                    if(ptms->hItemSelected == NULL)
                    {
                        Select( ptms, ptms->hItemFirstVisible, TVGN_CARET, false);
                    }
                }
            }
            else
            {                
                if(uMsg == WM_KILLFOCUS
                    && ptms->hItemSelected)
                {
                    InvalidateItemRect(ptms, ptms->hItemSelected, FALSE);
                }
            }
            break;

        case WM_NCDESTROY:
            {
                LRESULT lResult = ::CallWindowProc( ptms->pOldWndProc, hwnd, uMsg, wParam, lParam);
                SetWindowLong( hwnd, GWL_WNDPROC, (LONG)ptms->pOldWndProc);
                delete ptms;
#ifdef RG_TREE_WITH_WND_PROC_MAP
                WndProcMap.RemoveKey( hwnd);
#endif
                return lResult;
            }

        case WM_PAINT:
			if(ptms->bRedrawFlag && ((ptms->hItemFirstVisible || wParam /* because of last item delete bottom problem */) 
				|| ptms->nVisibleItemCount == 0))  //add for Gensym-2032, if the tree is empty, the view still need to paint 
                return OnPaint( ptms, wParam, lParam);
            break;

        case WM_SETREDRAW:
            ptms->bRedrawFlag = (wParam != 0);
            if( ptms->bRedrawFlag)
            {
				        _ScrollAbsolutelyDownWhenRequired(ptms);
                if(SETSCROLLBARS(ptms) == false)
                    RedrawWindow( hwnd, NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE);
            }
            return 0;

        case WM_ERASEBKGND:
          {
            return 1;
          }
          
        case WM_TIMER:
            if( wParam == ID_SHOW_TIMER)
            {
                KillTimer( hwnd, ID_SHOW_TIMER);
                ASSERT(ptms->hItemSelected);
                EnsureVisible( ptms, ptms->hItemSelected, false);
            }
            if( wParam == ID_EDIT_TIMER)
            {
                KillTimer( hwnd, ID_EDIT_TIMER);
                ASSERT(ptms->hItemSelected);
                OnEditLabel( ptms, 0, (LPARAM)ptms->hItemSelected);
            }
            break;

        case WM_VSCROLL:
        		//Gensym-538 fix
            //DoScroll(ptms, SB_VERT, LOWORD(wParam), HIWORD(wParam));
            DoScroll(ptms, SB_VERT, LOWORD(wParam), HIWORD(wParam), TRUE);
            return 0;

        case WM_MOUSEWHEEL:
            {
                int nPos = ptms->nVScrollPos;
                
                short zDelta = HIWORD(wParam);
                ASSERT(sizeof(zDelta) * 2 == sizeof(wParam));
                int nSteps = - zDelta * 3 / WHEEL_DELTA;
                nPos += nSteps;
                
                DoScroll(ptms, SB_VERT, nPos);
            }
            return 0;

        case TVM_CREATEDRAGIMAGE:
            return OnCreateDragImage(ptms, lParam);
            
        case TVM_DELETEITEM:
            return OnDeleteItem( ptms, wParam, lParam);

        case TVM_EDITLABEL:
            return OnEditLabel( ptms, wParam, lParam);

        case TVM_ENDEDITLABELNOW:
            return EndEditLabelNow( ptms, wParam);

        case TVM_ENSUREVISIBLE:
            return EnsureVisible( ptms, (HTREEITEM)lParam, false);
            
        case TVM_EXPAND:
            // We want to have a notification nevertheless in which way it was sent.
            // That's why TRUE instead of FALSE.
            return Expand( ptms, (HTREEITEM)lParam, wParam, TRUE /*FALSE*/);

        case TVM_GETCOUNT:
            return (LRESULT)ptms->rgTree.GetItemCount();

        case TVM_GETEDITCONTROL:
            if( ptms->hItemEditing)
                return (LRESULT)ptms->hWndEdit;
            return 0;

        case TVM_GETITEM:
            return OnGetItem( ptms, wParam, lParam);

        case TVM_GETITEMRECT:
            {
                HTREEITEM hItem = *(HTREEITEM*)lParam;
                LPRECT lpRect = (LPRECT)lParam;
                BOOL bTextOnly = (BOOL)wParam;
                return (LRESULT)GetItemRect( ptms, hItem, lpRect, bTextOnly);
            }

        case TVM_GETNEXTITEM:
            return (LPARAM)GetNextItem( ptms, (HTREEITEM)lParam, wParam);
            
        case TVM_HITTEST:
            return (LPARAM)HitTest(ptms, (LPTVHITTESTINFO)lParam);

        case TVM_INSERTITEM:
            return OnInsertItem( ptms, wParam, lParam);

        case TVM_SELECTITEM:
            return Select( ptms, (HTREEITEM)lParam, wParam, false);

        case TVM_SETITEM:
            return SetItem( ptms, (LPTVITEM)lParam);

        case TVM_SORTCHILDREN:
            if( lParam == (LPARAM)TVI_ROOT)
                lParam = 0;
            ptms->rgTree.SortChildren( (POSITION)lParam);
            if( lParam == 0)
            {
                ptms->hItemFirstVisible = GetNextItem( ptms, (HTREEITEM)lParam, TVGN_CHILD);
                ptms->nVScrollPos = 0;
				if( ptms->bRedrawFlag)
				{
					if(SETSCROLLBARS(ptms) == false)
						InvalidateRect( hwnd, NULL, TRUE);
				}
            }
            else
			{
				if( ptms->bRedrawFlag)
				{
					InvalidateRect( hwnd, NULL, TRUE);
				}
			}
            return TRUE;

        case TVM_GETVISIBLECOUNT:
            return GetVisibleCount(ptms);

        case TVM_GETINDENT:
            return ptms->m_nIndent;

        case TVM_SETINDENT:
            _SetIndent(ptms, wParam);
            InvalidateRect( hwnd, NULL, TRUE);
            return TRUE;

        case TVM_GETIMAGELIST:
            return (LRESULT)GetImageList(ptms, wParam);

        case TVM_SETIMAGELIST:
            {
                HIMAGELIST hOld;
                if(wParam == TVSIL_NORMAL)
                {
                    hOld = ptms->m_hNormalImageList;
                    ptms->m_hNormalImageList = (HIMAGELIST)lParam;
                    _SetNormalImageList(ptms);
                }
                else
                {
                    hOld = ptms->m_hStateImageList;
                    ptms->m_hStateImageList = (HIMAGELIST)lParam;
                }
                            
                InvalidateRect( hwnd, NULL, TRUE);
                return (LRESULT)hOld;
            }

#ifdef TVM_GETITEMHEIGHT
        case TVM_GETITEMHEIGHT:
            return GetItemHeight(ptms);
#endif
    }
    return ::CallWindowProc( ptms->pOldWndProc, hwnd, uMsg, wParam, lParam);
}

HWND CreateRGTree( DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HANDLE hInstance, LPVOID lpParam)
{
    HWND hWnd = CreateWindow( _T("SYSTREE32"), NULL, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, (HINSTANCE)hInstance, lpParam);
    if( hWnd)
        RGTreeWindowProc( hWnd, WM_CREATE, 0, 0);
    return hWnd;    
}

#ifdef __AFX_H__ // MFC project

/**************************************************************************
 *                                                                        *
 *                                CRGTreeCtrl                             *
 *                                                                        *
 **************************************************************************/

CRGTreeCtrl::CRGTreeCtrl()
{
    m_bCreated = false;
}

LRESULT CRGTreeCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch( message)
    {
        case WM_CREATE:
            {

                LRESULT lResult;
                ASSERT(m_bCreated);
                if( (lResult = CTreeCtrl::WindowProc(message, wParam, lParam)) == 0)
                {
                    WNDPROC mfcWndProc = (WNDPROC)SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)m_pfnSuper);
                    RGTreeWindowProc(m_hWnd, WM_CREATE, 0, lParam);
                    m_pfnSuper = &RGTreeWindowProc;
                    SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)mfcWndProc);
                }
                return lResult;
            }
    }
    return CTreeCtrl::WindowProc(message, wParam, lParam);
}

void CRGTreeCtrl::PreSubclassWindow()
{
    CTreeCtrl::PreSubclassWindow();
    if(!m_bCreated)
    {
        RGTreeWindowProc( m_hWnd, WM_CREATE, 0, (LPARAM)AfxGetInstanceHandle());
        m_bCreated = true;
    }
}

BOOL CRGTreeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
    m_bCreated = true;
    return CTreeCtrl::Create(dwStyle, rect, pParentWnd, nID);
}

/*BOOL CRGTreeCtrl::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
                           LPCTSTR lpszWindowName, DWORD dwStyle,
                           int x, int y, int nWidth, int nHeight,
                           HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
    m_bCreated = true;
	#if defined(_MFC_VER)&&_MFC_VER>=0x0900//VS2008 MFC and more		
    return CTreeCtrl::CreateEx(dwExStyle, dwStyle, CRect( x, y, x+nWidth, y+nHeight),
		CWnd::FromHandle(hWndParent), (UINT)nIDorHMenu);

	#else
	return CTreeCtrl::CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, x, y, nWidth, nHeight,
        hWndParent, nIDorHMenu, lpParam);
	#endif
}

BOOL CRGTreeCtrl::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
                           LPCTSTR lpszWindowName, DWORD dwStyle,
                           const RECT& rect,
                           CWnd* pParentWnd, UINT nID,
                           LPVOID lpParam)
{
    m_bCreated = true;

#	if defined(_MFC_VER) && _MFC_VER >= 0x0900   //VS2008 MFC and more

    return CTreeCtrl::CreateEx(dwExStyle, dwStyle, rect, pParentWnd, nID);

#	else

	return CTreeCtrl::CreateEx(dwExStyle, lpszClassName, lpszWindowName,
		dwStyle, rect, pParentWnd, nID, lpParam);

#	endif
}
*/

#endif //__AFX_H__
