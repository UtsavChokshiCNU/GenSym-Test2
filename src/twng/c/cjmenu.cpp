/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      cjmenu.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   -fmw, 20Mar04
 +
 + Description:  Codejock backend for G2 Native Menus
 +
 + Dependencies: Codejock XTP library (http://www.codejock.com)
 +
 + Modifications:
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ControlIniter.h"

/* Copied from msincls.h */
#define NMS_NO_CHOICE 1500
#define WM_NMS_MENU_CHOICE (WM_USER + 2)

/* True for IDs which are dynamically allocated by NMS,
   and are never shared between multiple menu items. */
#define nms_allocated_id_p(id) ((1800<=(id) && (id)<9300) || (9600<=(id) && (id)<32000))

static BOOL tracking_popup_menu_p = FALSE; // TODO: Share in twpro.c

/* Array of XTP objects pending deletion. These are pending because G2 attempted
 * to delete them while they were being tracked by TrackPopupMenu(). */
CTypedPtrArray<CPtrArray,CCmdTarget*> g_pendingObjectDeletions;

/*
 * Debug
 */

#ifdef _DEBUG
#define XTRACE g2pvt_trace
#else
#define XTRACE 1 ? (void)0 : g2pvt_trace
#endif

#if defined(_DEBUG) | defined(DEBUG_VIEWS) | defined(TRACE_VIEWS)
void describe_flags(DWORD flags)
{
  g2pvt_printf("Flags: %08X", flags);
  if(flags&xtpFlagRightAlign)	g2pvt_printf(" xtpFlagRightAlign");
  if(flags&xtpFlagSkipFocus)	g2pvt_printf(" xtpFlagSkipFocus");
  if(flags&xtpFlagLeftPopup)	g2pvt_printf(" xtpFlagLeftPopup");
  if(flags&xtpFlagManualUpdate)	g2pvt_printf(" xtpFlagManualUpdate");
  if(flags&xtpFlagNoMovable)	g2pvt_printf(" xtpFlagNoMovable");

  if(flags&xtpFlagHideMinimizeBox)	g2pvt_printf(" xtpFlagHideMinimizeBox");
  if(flags&xtpFlagHideMaximizeBox)	g2pvt_printf(" xtpFlagHideMaximizeBox");
  if(flags&xtpFlagIgnoreSetMenuMessage)	g2pvt_printf(" xtpFlagIgnoreSetMenuMessage");
  if(flags&xtpFlagUseMDIMenus)	        g2pvt_printf(" xtpFlagUseMDIMenus");
  if(flags&xtpFlagHideClose)	        g2pvt_printf(" xtpFlagHideClose");
  if(flags&xtpFlagHideMDIButtons)	g2pvt_printf(" xtpFlagHideMDIButtons");
  if(flags&xtpFlagAddMDISysPopup)	g2pvt_printf(" xtpFlagAddMDISysPopup");
  g2pvt_printf("\n");
}

void print_object(CObject* pObject)
{
  LPCSTR className = pObject ? pObject->GetRuntimeClass()->m_lpszClassName : NULL;

  if(!pObject) {
    g2pvt_printf("NULL\n");

  } else if (pObject->IsKindOf(RUNTIME_CLASS(CCmdTarget))) {
    CCmdTarget *pCmd = (CCmdTarget*)pObject;
    g2pvt_printf("#<%s ref:%d %x>\n", className, pCmd->m_dwRef, pCmd);

  } else if (pObject->IsKindOf(RUNTIME_CLASS(CWnd)) &&
	     ((CWnd*)pObject)->GetSafeHwnd()) {
    CWnd *pWnd = (CWnd*)pObject;
    wchar_t buf[20];
    ZeroMemory(buf,sizeof(buf));
    pWnd->GetWindowText(buf,19);
    g2pvt_printf("#<%s \"%ls\" hwnd:%x %x>\n", className, buf, pWnd->m_hWnd, pWnd);

  } else {
    g2pvt_printf("#<%s %x>\n", className, pObject);
  }
}

void print_control(CXTPControl* pControl)
{
  if(pControl)
    g2pvt_printf("#<%s id:%d ref:%d \"%ls\"%s%s %x>\n",
		 pControl->GetRuntimeClass()->m_lpszClassName, 
		 pControl->GetID(),
		 pControl->m_dwRef,
		 pControl->GetCaption(),
		 pControl->GetChecked() ? " chk" : "",
		 pControl->GetBeginGroup() ? " grp" : "",
		 pControl);
  else
    g2pvt_printf("NULL\n");
}

void g2pvt_print_cmdbar(CXTPCommandBar* pBar)
{
  if(pBar)
    g2pvt_printf("#<%s id:%d \"%ls\" ref:%d %x>\n",
		 pBar->GetRuntimeClass()->m_lpszClassName, 
		 pBar->GetBarID(), 
		 pBar->GetTitle(),
		 pBar->m_dwRef,
		 pBar);
  else
    g2pvt_printf("NULL\n");
}

static void describe_cmdbar_1(CXTPCommandBar* pBar, int depth)
{
  CXTPControl* pControl;
  static const char fill[] = "       ";

  if(depth>=2) return;
  const char *indent = fill+sizeof(fill)-min(depth,(int)sizeof(fill));

  g2pvt_printf("%s ", indent);
  g2pvt_print_cmdbar(pBar);
  if(!pBar) return;

  for(int i=0; i<pBar->GetControls()->GetCount(); i++) {
    pControl = pBar->GetControls()->GetAt(i);
    g2pvt_printf("%s (%d) ", indent, i);
    print_control(pControl);
    if(pControl->IsKindOf(RUNTIME_CLASS(CXTPCommandBar))) { // Not Possible.
      g2pvt_printf("\n\n *** Not possible *** \n\n");
      describe_cmdbar_1((CXTPCommandBar*)pControl, depth+1);
    }
    else if(pControl->IsKindOf(RUNTIME_CLASS(CXTPControlPopup)))
      describe_cmdbar_1(((CXTPControlPopup*)pControl)->GetCommandBar(), depth+1);
  }
}

void g2pvt_describe_cmdbar(CXTPCommandBar* pBar)
{
  describe_cmdbar_1(pBar,0);
}
#endif // _DEBUG



/*
 * Utilities
 */

/* Unused bit in enum XTPControlFlags and XTPMenuBarFlags (for now).
 * FIXME: Use some other slot. */
static int const nmsPendingSeparator = 0x4000L;

static int nms_id_enabled[8192];	   /* 65K bit vector enabled[id%0xFFFF]. */ 

// Deals with XTP separators vs Win32 separators.
static BOOL AddSeparator(CXTPCommandBar* pMenu, BOOL addSeparator)
{
  if(addSeparator)
    pMenu->SetFlags(nmsPendingSeparator);
  return addSeparator;
}

static void SetSeparator(CXTPCommandBar* pMenu, CXTPControl* pControl)
{
  if(pMenu->GetFlags() & nmsPendingSeparator) {
    pControl->SetBeginGroup(TRUE);
    pMenu->SetFlags(0,nmsPendingSeparator);
  }
}

/* Find control by position or ID. The by-position case is complicated by the
 * fact that Win32 menus treat separators as menu items, while XTP menus do
 * not. The position we get is the position in a Win32 menu.
 * FIXME: More problems: inserting/removing a separator! */
static CXTPControl* find_control(CXTPCommandBar* pMenu, int item, int flags)
{
  CXTPControl* found = NULL;

  if(!pMenu)
    return NULL;

  if(flags&MF_BYPOSITION) {
    int pos = 0;
    CXTPControl* pControl;
    for(int i=0; i<pMenu->GetControls()->GetCount(); i++) {
      pControl = pMenu->GetControls()->GetAt(i);

      // Codejock adds one of these even when bShowExpandButtonAlways is FALSE,
      // and, depending on timing, it may get added in the middle of the toolbar
      // instead of at the end!  Ignore it for the purposes of finding one of
      // our controls. FIXME: We really should not use find-by-position at all
      // here.  -fmw, 12/14/04
      if(pControl->GetID() == XTP_ID_TOOLBAR_EXPAND)
	continue;

      if(pControl->GetBeginGroup()) pos++;
      //      XTRACE(" i=%d item=%d pos=%d ", i, item, pos); print_control(pControl);
      if(item == pos) {
	found = pControl;
	break;
      }
      pos++;
    }
  } else {
    found = pMenu->GetControls()->FindControl(item);
  }

  if(found == NULL) {
    //     XTRACE("ERROR: find_control failed: Menu 0x%0x item %d bypos %x not found.\n",
    // 					 pMenu, item, flags&MF_BYPOSITION != 0);
    //     describe_cmdbar(pMenu);
  }

  return found;
}

// This pair of routines manipulate the bitarray nms_id_enabled.
void g2pvt_nms_set_id_enabled(int id, int enabled)
{
  int i = (id&0xFFFF)>>3;
  int mask = 1<<(id&7);
  if(enabled)
    nms_id_enabled[i] |= mask;
  else
    nms_id_enabled[i] &= ~mask;
}

BOOL g2pvt_nms_get_id_enabled(int id)
{
  if(g2pvt_local_command_p(id))
    return g2pvt_local_command_enabled_p(id);

  int i = (id&0xFFFF)>>3;
  int mask = 1<<(id&7);
  return (nms_id_enabled[i] & mask) != 0;
}


/* These routines manage a bidirectional pointer between a control as created by G2,
 * and its clone in the menu bar (if any).  We need this kludge because XTP seems
 * to allow exactly one menu bar object, which can only be "refilled" with new controls,
 * and not set as Win32 SetMenu does. So when a command bar has been "set" to the menu bar,
 * any G2 operation on that command bar, and any events coming from the Window system
 * relative to the menu bar, must be converted to the object G2 knows about. */

/* NOTE: Code here assumes sizeof(DWORD) >= sizeof(pointer) */

static void link_command_bars(CXTPCommandBar* pBar, CXTPCommandBar* pCloneBar);

static void link_controls(CXTPControl* pControl, CXTPControl* pClone)
{
  pControl->SetUserData((DWORD) pClone);
  pClone->SetUserData((DWORD) pControl);

  if(pControl->IsKindOf(RUNTIME_CLASS(CXTPControlPopup)) &&
     pClone->IsKindOf(RUNTIME_CLASS(CXTPControlPopup)))
    link_command_bars(((CXTPControlPopup*)pControl)->GetCommandBar(),
		      ((CXTPControlPopup*)pClone)->GetCommandBar());
}

static void link_command_bars(CXTPCommandBar* pBar, CXTPCommandBar* pCloneBar)
{
  CXTPControl *pControl, *pClone;

  if(pBar == NULL || pCloneBar == NULL) return;

  pBar->SetCommandBarData((DWORD)pCloneBar);
  pCloneBar->SetCommandBarData((DWORD)pBar);

  for(int i=0; i<pBar->GetControls()->GetCount(); i++) {
    pControl = pBar->GetControls()->GetAt(i);
    pClone = pCloneBar->GetControls()->GetAt(i);
    link_controls(pControl, pClone);
  }
}

static void clear_clones(CXTPCommandBar* pBar)
{
  CXTPControl* pControl;

  if(pBar == NULL) return;

  if(CloneOfBar(pBar))
    CloneOfBar(pBar)->SetCommandBarData(0);
  pBar->SetCommandBarData(0);
  
  for(int i=0; i<pBar->GetControls()->GetCount(); i++) {
    pControl = pBar->GetControls()->GetAt(i);

    if(CloneOfControl(pControl))
      CloneOfControl(pControl)->SetUserData(0);
    pControl->SetUserData(0);

    if(pControl->IsKindOf(RUNTIME_CLASS(CXTPControlPopup)))
      clear_clones(((CXTPControlPopup*)pControl)->GetCommandBar());
  }
}


/* add_control appends control to the end of a command bar, dealing with pending
 * separators, expand buttons, and clones in the menubar. */

int add_control(CXTPCommandBar* pBar, CXTPControl* pControl)
{
  if(!pBar || !pControl)
    return -1;

  SetSeparator(pBar, pControl);

  // If Codejock has already added an expand button to the end of the command
  // bar (only applies to toolbars), insert control before it.

  CXTPControl* pExpand = pBar->GetControls()->FindControl(XTP_ID_POPUPBAR_EXPAND);
  pBar->GetControls()->Add(pControl, pControl->GetID(), _T(""), pExpand ? pExpand->GetIndex() : -1);

  //  XTRACE("add_control: "); print_control(pControl);

  // Propagate the right align bit forwards
  int i = pControl->GetIndex();
  if(i>0 && pBar->GetControls()->GetAt(i-1)->GetFlags() & xtpFlagRightAlign)
    pControl->SetFlags(xtpFlagRightAlign);

  if(CloneOfBar(pBar)) {
    // Insert before MDI buttons, if present.
    CXTPControl* pButton = CloneOfBar(pBar)->GetControls()->FindControl(XTP_ID_MENUBAR_MINIMIZE);
    int i = pButton ? pButton->GetIndex() : -1;

    CXTPControl *pClone = CloneOfBar(pBar)->GetControls()->AddClone(pControl,i,TRUE);
    link_controls(pControl,pClone);
  }
  return pBar->GetControls()->GetCount();
}

/* This is always recursive. */
static void delete_xtp_object(CCmdTarget* pObject)
{
  if(pObject->IsKindOf(RUNTIME_CLASS(CXTPControl))) {
    CXTPControl* pControl = (CXTPControl*)pObject;
    pControl->GetControls()->Remove(pControl);

  } else if(pObject->IsKindOf(RUNTIME_CLASS(CXTPToolBar))) {
    CXTPToolBar* pToolBar = (CXTPToolBar*)pObject;
    pToolBar->GetCommandBars()->Remove(pToolBar);

  } else {
    pObject->InternalRelease();
  }
}


static void delete_xtp_icon(CXTPControl *pControl)
{
  CXTPImageManagerIconSet* pIconSet;
  int id;

  id = pControl->GetID();

//   PRINTF("delete_xtp_icon %s %d ", nms_allocated_id_p(id) ? "NMS" : "XTP", id);
//   print_control(pControl);

  if(nms_allocated_id_p(id) && XTPImageManager()->GetImages()->Lookup(id, pIconSet)) {
    XTPImageManager()->GetImages()->RemoveKey(id);
    delete pIconSet;
  }
}

/*
 * Unmap and destroy all NMS icons used in the given command bar,
 * recursing to submenus.
 */
static void delete_xtp_icons(CXTPCommandBar *pBar)
{
  CXTPControl *pControl;
  int i;

  for(i=0; i<pBar->GetControls()->GetCount(); i++) {
    pControl = pBar->GetControls()->GetAt(i);

    delete_xtp_icon(pControl);

    if(pControl->GetCommandBar())
      delete_xtp_icons(pControl->GetCommandBar());
  }
}



/*
 * Custom XTP button class
 */

// So far, just to handle NMS fg/bg colors.
class CNmsButton : public CXTPControlButton
{
  DECLARE_XTP_CONTROL(CNmsButton)
public:
  CNmsButton();
  static CNmsButton* CreateNmsButton(long color, long color_fg = -1) {
    CNmsButton* pButton = (CNmsButton*) CNmsButton::CreateObject();
    pButton->SetColor(color);
	pButton->SetColor_fg(color_fg);
    return pButton;
  }
  //Suzsoft comment: the color only recorde the bg color
  void SetColor(long color) {
    m_bg_color = color;				    // A BG COLORREF or -1
  }
  //{{Suzsoft Added for Gensym-432
  void SetColor_fg(long color){
	 m_fg_color = color;				    // A FG COLORREF or -1
  }
  //}}Suzsoft
protected:
  virtual void Draw(CDC* pDC);
  virtual void Copy(CXTPControl* pControl, BOOL bRecursive = FALSE);	
  virtual void Serialize(CArchive& ar);
  virtual void OnClick(BOOL bKeyboard = FALSE, CPoint pt = CPoint(0, 0));
public:
  long m_bg_color;			// A bg color or -1.
  long m_fg_color;			// A fg color or -1.
};

IMPLEMENT_XTP_CONTROL(CNmsButton, CXTPControlButton)

CNmsButton::CNmsButton()
{
  m_bg_color = -1;
  m_fg_color = -1;
}

void CNmsButton::Copy(CXTPControl* pControl, BOOL bRecursive)
{
  ASSERT(DYNAMIC_DOWNCAST(CNmsButton, pControl));
  CXTPControlButton::Copy(pControl, bRecursive);
  m_bg_color = ((CNmsButton*)pControl)->m_bg_color;
  m_fg_color = ((CNmsButton*)pControl)->m_fg_color;
}

void CNmsButton::Serialize(CArchive& ar)
{
  CXTPControlButton::Serialize(ar);
  if (ar.IsStoring())
  {
    ar << m_bg_color;
	ar << m_fg_color;
  }
  else
  {
    ar >> m_bg_color;
	ar >> m_fg_color;
  }
}

void CNmsButton::Draw(CDC* pDC)
{
  CXTPControl::Draw(pDC);	// Draw as usual.

  if(m_bg_color < 0 && m_fg_color < 0)
    return;

  if(GetStyle() == xtpButtonCaption) // FIXME: Approximate test for no icon.
    return;

  // The "right way" is to override CXTPControl::GetImage(width):

  // Input:   nWidth - Width of the image to retrieve.
  // Returns: A pointer to a CXTPImageManagerIcon object
  // Summary: Call this method to retrieve the image of the control.
  // virtual CXTPImageManagerIcon* GetImage(int nWidth = 16);

  // FIXME: This works only for popup parents.

  // Now draw color square where the icon would be.
  // FIXME: This geometry was copied from
  // CXTPOfficeTheme::DrawControlPopupParent, so it really is theme-dependent!

  //{{Suzsoft Deleted for Gensym-432
  //CRect rc = m_rcControl;
  //CRect rcBox(rc.left, rc.top, rc.left + 16 + 4, rc.bottom);
  //rcBox.DeflateRect(1,1);

  /*Make square*/
  //   if(rcBox.Width() > rcBox.Height())
  //     rcBox.DeflateRect((rcBox.Width() - rcBox.Height())/2 ,0);
  //   else
  //     rcBox.DeflateRect(0,(rcBox.Height() - rcBox.Width())/2);


  //{{Suzsoft Added for Gensym-432
  if (m_bg_color >= 0 || m_fg_color >= 0)
  {
	  if(GetSelected())
	  {
		  long Temp = m_bg_color;
		  m_bg_color = m_fg_color;
		  m_fg_color = Temp;
			  
	  }
  }
  
  CRect rc = m_rcControl;
  CRect rcBox(rc.left + 16 + 8, rc.top, rc.right, rc.bottom);

  /* Draw Background. */
  { 
	  CBrush brush(m_bg_color);
	  CPen pen(PS_SOLID, 1, RGB(0,0,0));
	  CBrush* pOldBrush = pDC->SelectObject(&brush);
	  CPen* pOldPen = pDC->SelectObject(&pen);
	  
	  pDC->Rectangle(rcBox);
	  
	  pDC->SelectObject(pOldBrush);
	  pDC->SelectObject(pOldPen);
  }

  /* Draw text. */
  if(!GetCaption().IsEmpty()) {
	  int old_mode = pDC->SetBkMode(TRANSPARENT);
	  int old_color = pDC->SetTextColor(m_fg_color);
	  rcBox.left += 6;
	  rcBox.right -= 6;
	  pDC->DrawText(GetCaption(), rcBox,DT_SINGLELINE | DT_VCENTER  | DT_LEFT); 
	  pDC->SetTextColor(old_color);
	  pDC->SetBkMode(old_mode);
  }

  if (m_bg_color >= 0 || m_fg_color >= 0)
  {
	  if(GetSelected())
	  {
		  long Temp = m_bg_color;
		  m_bg_color = m_fg_color;
		  m_fg_color = Temp;
		  
	  }
  }
  //}}Suzsoft 
}

void CNmsButton::OnClick(BOOL bKeyboard, CPoint pt)
{
  g2pvt_enter_modal_loop();
  CXTPControlButton::OnClick(bKeyboard, pt);
  g2pvt_exit_modal_loop();
}

/*
 * Custom XTP popup menu class
 */

// This exists just so that we can no-op void CXTPPopupBar::UpdateShortcuts, which
// clobbers any item with ID>0 and not in some MFC accelerator table.

class CNmsPopupBar : public CXTPPopupBar
{
  DECLARE_XTP_COMMANDBAR(CNmsPopupBar)
public:
  static CNmsPopupBar* Create(CXTPCommandBars* pBars) {
    // Copied from CXTPPopupBar::CreatePopupBar().
    CNmsPopupBar *pMenu = (CNmsPopupBar*)CNmsPopupBar::CreateObject();
    pMenu->SetCommandBars(pBars);
    return pMenu;
  }
protected:
  virtual void UpdateShortcuts() {}	// Clobber
};
IMPLEMENT_XTP_COMMANDBAR(CNmsPopupBar, CXTPPopupBar)


/*
 * Custom XTP toolbar class
 */

class G2ToolBar : public CXTPToolBar
{
  DECLARE_XTP_COMMANDBAR(G2ToolBar)
public:
  G2ToolBar::G2ToolBar(void)
  {
    m_enableTooltips = FALSE;
    m_defaultButtonStyle = xtpButtonIconAndCaption;
  }
  BOOL m_enableTooltips;
  XTPButtonStyle m_defaultButtonStyle;
};
IMPLEMENT_XTP_COMMANDBAR(G2ToolBar, CXTPToolBar)


// Maintains tooltip == caption for buttons, if tooltips are enabled.
void set_control_caption(CXTPCommandBar *pMenu, CXTPControl *pControl, LPWSTR caption)
{
  G2ToolBar *pBar = DYNAMIC_DOWNCAST(G2ToolBar, pMenu);
  CXTPControl* pControlClone = CloneOfControl(pControl);

  pControl->SetCaption(caption);
  if(pControlClone)
    pControlClone->SetCaption(caption);

  if(pBar && pBar->m_enableTooltips) {
    pControl->SetTooltip(caption);
    if(pControlClone)
      pControlClone->SetTooltip(caption);
  }
}




/*
 * Pre-NMS Menus
 */

long g2ext_begin_item_menu(void) {
  CMainFrame *pFrame = GetMainWnd();
  CXTPPopupBar* pMenu = CNmsPopupBar::Create(pFrame->GetCommandBars());

  pMenu->SetTitle(_T("G2 Popup Menu")); /* Menu title. TODO: G2 wants to set this! */
  return SavePtr(pMenu);
}

long g2ext_add_string_to_item_menu(long popup_menu_index, LPWSTR string, long nId, long options)
{
  CXTPPopupBar* pMenu = GetPtr(CXTPPopupBar,popup_menu_index);

  if(AddSeparator(pMenu, options&2))
    return nId;

  CNmsButton* pControl = (CNmsButton*)CNmsButton::CreateObject();
  SetSeparator(pMenu, pControl);

  pControl->SetFlags(xtpFlagManualUpdate);
  pMenu->GetControls()->Add(pControl, nId);
  pControl->SetCaption(string);	// Add() may have set the string from nId
  return nId;
}

long g2ext_add_color_string_to_item_menu(long popup_menu_index, LPWSTR string, long nId,
																				 long options, long fg, long bg)
{
  CXTPPopupBar* pMenu = GetPtr(CXTPPopupBar,popup_menu_index);

  if(AddSeparator(pMenu, options&2))
    return nId;

  CNmsButton* pControl = (CNmsButton*)CNmsButton::CreateObject();
  SetSeparator(pMenu, pControl);

  pControl->SetFlags(xtpFlagManualUpdate | ((options&1) * xtpFlagWrapRow));
  pControl->SetColor(bg);               
  pControl->SetColor_fg(fg);    // Set the fg, or the caption can't display.
  pMenu->GetControls()->Add(pControl, nId);
  pControl->SetCaption(string);	// Add() may have set the string from nId
  return nId;
}

long g2ext_add_submenu_to_item_menu(long popup_menu_index, LPWSTR string,
				    long submenu_index, long options)
{
  CXTPPopupBar* pMenu = GetPtr(CXTPPopupBar,popup_menu_index);
  int nId = 123;		// FIXME: Need ID for submenu objects

  if(AddSeparator(pMenu, options&2))
    return nId;

  CXTPPopupBar* pSubMenu = GetPtr(CXTPPopupBar,submenu_index);
  CXTPControlPopup* pControl=(CXTPControlPopup*)CXTPControlPopup::CreateControlPopup(xtpControlPopup);
  SetSeparator(pMenu, pControl);

  CString strCaption(string);
  CXTPPaintManager::StripMnemonics(strCaption);
  pSubMenu->SetTitle(strCaption); /* Submenu gets title = the button that spawns it. */

  pControl->SetCaption(string);
  pControl->SetCommandBar(pSubMenu);
  pSubMenu->InternalRelease();	           // Compensate for SetCommandBar()
  pControl->SetFlags(xtpFlagManualUpdate);

  pMenu->GetControls()->Add(pControl, nId);
  pControl->SetCaption(string);	// Add() may have set the string from nId
  return submenu_index;
}

long g2ext_choose_from_item_menu(long window_index, long popup_menu_index, long x, long y)
{
  CXTPPopupBar* pMenu = GetPtr(CXTPPopupBar,popup_menu_index);
  CMainFrame*  pFrame = GetMainWnd();
  CPoint pt;
  int choice;

  // TODO: Check for recursion?

  pt.x = x; pt.y = y;
  ::ClientToScreen(pFrame->CoorHwnd(), &pt);

  g2pvt_enter_modal_loop();
  choice = pFrame->GetCommandBars()->TrackPopupMenu(pMenu, TPM_RETURNCMD | TPM_RIGHTBUTTON,
						    pt.x, pt.y, pFrame);
  g2pvt_exit_modal_loop();

  return choice;
}

long g2ext_reclaim_item_menu(long menu_index, long top_level_p)
{
  CXTPPopupBar* pMenu = GetPtr(CXTPPopupBar,menu_index);

  g2ext_decache_g2pointer(menu_index);
  if(top_level_p)
    pMenu->InternalRelease();
  return 0;
}



/*
 * NMS Menus
 */

long g2ext_nms_create_menu(long popup_p, unsigned short *result)
{
  CMainFrame *pFrame = GetMainWnd();
  CXTPCommandBars* pBars = pFrame->GetCommandBars();
  CXTPCommandBar* pMenu;

  // FIXME: We make the menubar a popup bar, too, because we aren't really
  // making the menu bar.  We're just making a container for controls, which we
  // then clone-into the real menu bar. This cloning is a kludge, and doesn't
  // work completely, and needs to be replaced.
  pMenu = CNmsPopupBar::Create(pBars);

  result[0] = HIWORD((long)pMenu);
  result[1] = LOWORD((long)pMenu);

  if(pMenu == NULL)
    return -1;

  pMenu->SetFlags(xtpFlagIgnoreSetMenuMessage);
  pMenu->SetFlags(xtpFlagManualUpdate);
  pMenu->SetVisible(FALSE);

  return SavePtr(pMenu);
}

long g2ext_nms_set_menu_title(long menu_index, LPWSTR title)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  if(pMenu) pMenu->SetTitle(title);
  return 1;
}

ControlIniter gDefaultControlIniter;
IControlIniter* gControlIniter = &gDefaultControlIniter;
//Gensym-2038-TAM3-CH-BF-JIRA-46987-Excluding "tile-vertically" menu excludes all menu under "tile-vertically"
static BOOL bAppendWindowMenu = FALSE;
long nLastMenuId = 0;
long nLastMenuIndex = 0;
//Gensym-2038-TAM3-CH-BF-JIRA-46987-Excluding "tile-vertically" menu excludes all menu under "tile-vertically"

struct MENU_ITEM_ID_ICON
{
	LPWSTR title;
	long id;
} menu_item_id_icon[] = {
    { L"Load KB...	Ctrl+O", TWPRO_LOAD_KB},	//Hear string must be "Load[space]KB...[Tab]Ctrl+O"
    { L"Merge KB...", TWPRO_MERGE_KB },	//"Merge[space]KB..."
    { L"Save KB...", TWPRO_SAVE_KB },	//"Save[space]KB..."
    { L"Printer Setup", TWPRO_PRINTER_SETUP },	//"Printer[space]Setup"
    { L"Print To Server", TWPRO_PRINT_TO_SERVER },	//"Print[space]To[space]Server"
    { L"Print...", TWPRO_PRINT },
    { L"Log Out", TWPRO_LOG_OUT },	//"Log[space]Out"
    { L"Shut Down G2", TWPRO_SHUT_DOWN_G2 },	//"Shut[space]Down[space]G2"
    { L"Disconnect", TWPRO_DISCONNECT },
    { L"Delete	Del", TWPRO_DELETE },		//"Delete[Tab]Del"
    { L"Full Scale	Ctrl+0", TWPRO_FULL_SCALE },	//"Full[space]Scale[Tab]Ctrl+0"
    { L"Scale To Fit	Ctrl+.", TWPRO_SCALE_TO_FIT },	//"Scale[space]To[space]Fit[Tab]Ctrl+."
    { L"Zoom In	Ctrl++", TWPRO_ZOOM_IN },	//"Zoom[space]In[Tab]Ctrl++"
    { L"Zoom Out	Ctrl+-", TWPRO_ZOOM_OUT },	//"Zoom[space]Out[Tab]Ctrl+-"
    { L"Quarter Scale	Ctrl+Q", TWPRO_QUARTER_SCALE },	//"Quarter[space]Scale[Tab]Ctrl+Q"
    { L"Four Times The Scale	Ctrl+4", TWPRO_FOUR_TIMES_TO_SCALE },	//"Four[space]Times[space]The[space]Scale[Tab]Ctrl+4"
    { L"Toggle Visible Grid	Ctrl+G", TWPRO_TOGGLE_VISIBLE_GRID },	//"Toggle[space]Visible[space]Grid[Tab]Ctrl+G"
    { L"Refresh	F5", TWPRO_REFRESH },	//"Refresh[Tab]F5"
    { L"Start", TWPRO_START },
    { L"Pause	Pause", TWPRO_PAUSE },	//"Pause[Tab]Pause"
    { L"Resume", TWPRO_RESUME },
    { L"Continue", TWPRO_CONTINUE },
    { L"Reset", TWPRO_RESET },
    { L"Restart", TWPRO_RESTART },
    { L"Run Options", TWPRO_RUN_OPTIONS },	//"Run[space]Options"
    { L"Inspect...", TWPRO_INSPECT },
    { L"Neatly Stack Windows", TWPRO_NEATLY_STACK_WINDOWS },	//"Neatly[space]Stack[space]Windows"
    { L"Network Info", TWPRO_NETWORK_INFO },	//"Network[space]Info"
    { L"New Workspace", TWPRO_NEW_WORKSPACE },	//"New[space]Workspace"
    { L"Get Workspace", TWPRO_GET_WORKSPACE },	//"Get[space]Workspace"
    { L"New Object", TWPRO_NEW_OBJECT },	//"New[space]Object"
    { L"New Rule", TWPRO_NEW_RULE },	//"New[space]Rule"
    { L"New Display", TWPRO_NEW_DISPLAY },	//"New[space]Display"
    { L"New Definition", TWPRO_NEW_DEFINITION },	//"New[space]Definition"
    { L"New Free Text", TWPRO_NEW_FREE_TEXT },	//"New[space]Free[space]Text"
    { L"New Button", TWPRO_NEW_BUTTON },	//"New[space]Button"
    { L"Table", TWPRO_TABLE },
    { L"Color", TWPRO_COLOR },
    { L"Move", TWPRO_MOVE },
    { L"Lift To Top	Ctrl+T", TWPRO_LIFT_TO_TOP },	//"Lift[space]To[space]Top[Tab]Ctrl+T"
    { L"Drop To Bottom	Ctrl+V", TWPRO_DROP_TO_BOTTOM },	//"Drop[space]To[space]Bottom[Tab]Ctrl+V"
    { L"Shrink Wrap", TWPRO_SHRINK_WRAP },	//"Shrink[space]Wrap"
    { L"Delete Workspace", TWPRO_DELETE_WORKSPACE } };	//"Delete[space]Workspace"

long g2ext_nms_append_menu(long menu_index, long flags, long nId, long submenu_index,
			   long wide, LPWSTR label, long fg, long bg)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  BOOL enabled = (flags&(MF_GRAYED|MF_DISABLED)) == 0;
  CXTPControl* pControl = NULL;

  if(AddSeparator(pMenu, flags&MF_SEPARATOR))
    return nId;

  //Gensym-2038-TAM3-CH-BF-JIRA-46987-Excluding "tile-vertically" menu excludes all menu under "tile-vertically"
  if (!bAppendWindowMenu)
  {
	  if (nId == TWPRO_CLOSE || nId == TWPRO_CLOSEALL || nId == TWPRO_CASCADE || nId == TWPRO_TILE_HORIZONTALLY)
	  {
		  bAppendWindowMenu = TRUE;
		  nLastMenuId = nId;
		  nLastMenuIndex = menu_index;
	  }
  }
  else
  {
	  if (nLastMenuId == TWPRO_CLOSE && nId != TWPRO_CLOSEALL && nId != TWPRO_CASCADE && nId != TWPRO_TILE_HORIZONTALLY && nId != TWPRO_TILE_VERTICALLY)
		  bAppendWindowMenu = FALSE;
	  else if (nLastMenuId == TWPRO_CLOSEALL && nId != TWPRO_CASCADE && nId != TWPRO_TILE_HORIZONTALLY && nId != TWPRO_TILE_VERTICALLY)
		  bAppendWindowMenu = FALSE;
	  else if (nLastMenuId == TWPRO_CASCADE && nId != TWPRO_TILE_HORIZONTALLY && nId != TWPRO_TILE_VERTICALLY)
		  bAppendWindowMenu = FALSE;
	  else if (nLastMenuId == TWPRO_TILE_HORIZONTALLY && nId != TWPRO_TILE_VERTICALLY)
		  bAppendWindowMenu = FALSE;

	  if (bAppendWindowMenu)
	  {
		  nLastMenuId = nId;
		  nLastMenuIndex = menu_index;
	  }
	  else
	  {
		  CXTPCommandBar* pMenu1 = GetPtr(CXTPCommandBar,nLastMenuIndex);
		  pControl = find_control(pMenu1, nLastMenuId, MF_BYCOMMAND);

		  pControl = (CXTPControl*)CXTPControlWindowList::CreateObject();
		  gControlIniter->initControl(pControl, pMenu1, XTP_ID_WINDOWLIST, flags, label);

		  //pControl = (CXTPControl*)CXTPControlButton::CreateObject();
		  //pControl->SetBeginGroup(TRUE);
		  //gControlIniter->initControl(pControl, pMenu1, AFX_IDM_FIRST_MDICHILD - 1, flags, L"More Windows...");			
	  }
  }
  //Gensym-2038-TAM3-CH-BF-JIRA-46987-Excluding "tile-vertically" menu excludes all menu under "tile-vertically"

  CString title(label);
  CXTPPaintManager::StripMnemonics(title);

  // First check for a few special controls. XTP handles this in AddMenuItem,
  // but incredibly that requires a CMenu as an argument.

  if (nId == TWPRO_TOOLBARS) {
    nId = ID_VIEW_TOOLBAR;
    pControl = (CXTPControl*)CXTPControlToolbars::CreateObject();

  } else if(flags&MF_POPUP) {
    CXTPPopupBar* pSubMenu = GetPtr(CXTPPopupBar,submenu_index);
    CXTPControlPopup* pButton = CXTPControlPopup::CreateControlPopup(xtpControlPopup);
    pSubMenu->SetTitle(title);
    pButton->SetCommandBar(pSubMenu);
    pSubMenu->InternalRelease();     // Compensate for SetCommandBar()
    pControl = pButton;

	//Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice
  } else if (nId == TWPRO_MORE_WINDOWS) {
	  pControl = (CXTPControl*)CXTPControlButton::CreateObject();
	  pControl->SetBeginGroup(TRUE);
	  //Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice

  } else {
    pControl = CNmsButton::CreateNmsButton(bg);
    LPWSTR help = gControlIniter->getHelpString(nId); // Available now for built-in menu items.
    if(help)
      pControl->SetDescription(help);
    if(nId == TWPRO_STATUSBAR) 	            // FIXME: Change ID on G2 side?
      nId = ID_VIEW_STATUS_BAR;
  }

  for (int i = 0; i <= sizeof menu_item_id_icon / sizeof menu_item_id_icon[0]; i++)
  {
	  if (wcscmp(menu_item_id_icon[i].title, title) == 0)
	  {
		  pControl->SetIconId(menu_item_id_icon[i].id);
		  break;
	  }
  }

  long initResult = gControlIniter->initControl(pControl, pMenu, nId, flags, label);
  
  if (nId == TWPRO_TILE_VERTICALLY) {
	  //Gensym-2038-TAM3-CH-BF-JIRA-46987-Excluding "tile-vertically" menu excludes all menu under "tile-vertically"
	  nLastMenuId = nId;
	  bAppendWindowMenu = FALSE;
	  //Gensym-2038-TAM3-CH-BF-JIRA-46987-Excluding "tile-vertically" menu excludes all menu under "tile-vertically"
	  nId = XTP_ID_WINDOWLIST;
	  pControl = (CXTPControl*)CXTPControlWindowList::CreateObject();
	  gControlIniter->initControl(pControl, pMenu, nId, flags, label);

	  //Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice
	  //pControl = (CXTPControl*)CXTPControlButton::CreateObject();
	  //pControl->SetBeginGroup(TRUE);
	  //nId = AFX_IDM_FIRST_MDICHILD - 1;
	  //gControlIniter->initControl(pControl, pMenu, nId, flags, L"More Windows...");
	  //Gensym-2041-TAM3-CH-SUCA-JIRA-46986-Add the ability to exclude "more windows" menu choice
  }
  return initResult;
}

static void process_pending_menu_deletions()
{
  for(int i=0; i<g_pendingObjectDeletions.GetSize(); i++) {
    CCmdTarget *pObject = g_pendingObjectDeletions[i];
    pObject->InternalRelease();
    delete_xtp_object(pObject);
  }
  g_pendingObjectDeletions.RemoveAll();
}

long g2ext_nms_destroy_menu(long window_index, long menu_index, long recurse_p)
{
  CMainFrame* pFrame = GetMainWnd();
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);

  g2ext_decache_g2pointer(menu_index);
  if(pMenu == NULL)
    return -1;

  ASSERT_KINDOF(CXTPCommandBar,pMenu);

  // FIXME: The user can call this with recurse_p==0 straight from a sysproc!
  if(recurse_p == 0) {
    fprintf(stderr,"Error: nms_destroy_menu can't handle recurse==0\n");
    return -1;
  }

  CXTPCommandBar *pClone = CloneOfBar(pMenu);
  if(pClone)			// Snap clone links (if any)
    clear_clones(pMenu);
  delete_xtp_icons(pMenu);	// Reclaim icons (by ID)

  // If destroying the current menu bar, we want to switch to no menu bar, but
  // that's not possible with XTP. Instead, we switch to the built-in menu bar,
  // but leave it hidden.
  if(pMenu == pFrame->GetMenuBarSource())
    pFrame->ShowDefaultMenuBar(FALSE);

  else if(pClone)		// Must be a menu buried inside the menu bar. Unlike the
    delete_xtp_object(pClone);	// menu bar itself, those are OK to delete.

  // If destroying menu being tracked, set tracking mode False so that the modal
  // loop will exit, and postpone the deletion until then.
  if(pMenu->IsTrackingMode()) {
    pMenu->InternalAddRef();	// For reference from array.
    g_pendingObjectDeletions.Add(pMenu);
    pMenu->SetTrackingMode(FALSE);
  } else {
    delete_xtp_object(pMenu);
  }
  return 1;
}

long g2ext_nms_check_menu_item(long menu_index, long item, long flags)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  CXTPControl* pControl = find_control(pMenu,item,flags);
  BOOL check = (flags & MF_CHECKED) != 0;

  if(!pControl)
    return -1;

  pControl->SetChecked(check);
  if(CloneOfControl(pControl))
    CloneOfControl(pControl)->SetChecked(check);

  return 1;
}

long g2ext_nms_check_radio_item(long menu_index, long first, long last,
				long check, long flags)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  CXTPControl* pControl;

  for(int i = first; i<=last; i++) {                // Always by command ID.
    pControl = find_control(pMenu,i,MF_BYCOMMAND);
    if(!pControl)
      continue;

    pControl->SetChecked(i == check); // TODO: Bullet instead of checkmark
    if(CloneOfControl(pControl))
      CloneOfControl(pControl)->SetChecked(i == check);
  }
  return -1;
}

long g2ext_nms_enable_menu_item(long menu_index, long item, long flags)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  CXTPControl* pControl = find_control(pMenu,item,flags);
  BOOL enable = (flags&(MF_GRAYED|MF_DISABLED)) == 0;

  if(!pControl)
    return -1;

  pControl->SetEnabled(enable);
  g2pvt_nms_set_id_enabled(pControl->GetID(), enable); // Remember in bitarray

  if(CloneOfControl(pControl))
    CloneOfControl(pControl)->SetEnabled(enable); // Not needed if auto-updating?

  return 1;
}

long g2ext_nms_set_menu(long window_index, long menu_index, long nms_menu_handle)
{
  CMainFrame* pFrame = GetMainWnd();
  CXTPCommandBars* pBars = pFrame->GetCommandBars();
  CXTPMenuBar* pMenuBar = pBars->GetMenuBar();
  CXTPToolBar* pNew = GetPtr(CXTPToolBar,menu_index);

  if(menu_index == -1) {	// -1 => show default menu bar
    if(pFrame->GetMenuBarSource())
      clear_clones(pFrame->GetMenuBarSource());
    pFrame->ShowDefaultMenuBar();
    return 1;
  }

  if(pNew == NULL) {		// -2 or menu not found => hide menu bar
    pMenuBar->SetVisible(FALSE);
    return 1;
  }

  if(pNew == pFrame->GetMenuBarSource()) {
    pMenuBar->SetVisible(TRUE);
    return 1;
  }

  // Detach clone pointers from the old menu bar source.
  if(pFrame->GetMenuBarSource())
    clear_clones(pFrame->GetMenuBarSource());

  // Fix for HQ-5014595 "TWNG dies when menu pulled down one machine, refreshed on another"
  if(pMenuBar->IsTrackingMode())
    pMenuBar->SetTrackingMode(FALSE);

  // Fill up menubar with cloned controls from the source.
  // See CXTPToolBar::Reset() for code similar to this.
  pMenuBar->GetControls()->RemoveAll();
  for(int i=0; i<pNew->GetControls()->GetCount(); i++)
    pMenuBar->GetControls()->AddClone(pNew->GetControls()->GetAt(i), -1, TRUE);

  // Record in each source control a pointer to its clone.
  link_command_bars(pNew,pMenuBar);

  // Remember the source of the controls
  pFrame->SetMenuBarSource(pNew);

  // Put back MDI buttons, if any.
  pMenuBar->RefreshMenu();

  pMenuBar->SetVisible(TRUE);
  return 1;
}

long g2ext_nms_pop_up_menu(long window_index, long menu_handle, long menu_index, 
			   long x, long y)
{
  CXTPPopupBar* pMenu = GetPtr(CXTPPopupBar,menu_index);
  CMainFrame* pFrame = GetMainWnd();
  CPoint pt;
  int flags = TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_CENTERALIGN | TPM_TOPALIGN;
  int choice;

  if(tracking_popup_menu_p)	/* Can't happen. */
    return NMS_NO_CHOICE;

  pt.x = x; pt.y = y;
  ::ClientToScreen(pFrame->CoorHwnd(), &pt);

  g2pvt_enter_modal_loop();
  tracking_popup_menu_p = TRUE;
  choice = pFrame->GetCommandBars()->TrackPopupMenu(pMenu, flags, pt.x, pt.y, pFrame);
  tracking_popup_menu_p = FALSE;
  g2pvt_exit_modal_loop();

  if(choice == 0) choice = NMS_NO_CHOICE;
  pFrame->PostMessage(WM_NMS_MENU_CHOICE, choice, menu_handle);

  process_pending_menu_deletions();

  return choice;
}

long g2ext_nms_width_maintainance_p(void) {
  return 0;
}

long g2ext_nms_set_help(long menu_index, long nID, LPWSTR help)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  CXTPControl* pControl = find_control(pMenu, nID, MF_BYCOMMAND);
  CXTPControl* pControlClone = CloneOfControl(pControl);

  if(pControl)
    pControl->SetDescription(help);
  if(pControlClone)
    pControlClone->SetDescription(help);
  return 0;
}

long g2ext_nms_modify_menu_item(long menu_index, long nId, long pos, long wide,
				long new_label_p, LPWSTR new_label,
				long new_fg, long new_bg, long new_icon)
{
  CMainFrame* pFrame = GetMainWnd();
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  G2ToolBar *pBar = DYNAMIC_DOWNCAST(G2ToolBar, pMenu);
  CXTPControl* pControl = find_control(pMenu, nId, MF_BYCOMMAND); // More reliable for XTP
  CXTPCommandBar* pMenuClone = CloneOfBar(pMenu);
  CXTPControl* pControlClone = CloneOfControl(pControl);

  if(pControl == NULL)
    return -1;

  if(!new_label_p && new_fg<0 && new_bg<0 && new_icon<0) {
    // XTRACE("SetWide %d ignored.\n", wide);
    return 1;
  }

  if(new_label_p)
    set_control_caption(pMenu, pControl, new_label);

  if(new_icon>=0) {
    int iconID = pFrame->StoreNativeIcon(new_icon);
    if(iconID >= 0) {
      // Force icon to be visible, as well as the caption, by default.
      XTPButtonStyle style = pBar ? pBar->m_defaultButtonStyle : xtpButtonIconAndCaption;
      pControl->SetIconId(iconID);
      pControl->SetStyle(style);
      if(pControlClone) {
	pControlClone->SetStyle(style);
	pControlClone->SetIconId(iconID);
      }
    }
  }

  if(IsPopupControlType(pControl->GetType()))	    // Can't set colors on popup items.
    return 1;

  // XTRACE("SetColor fg of %x to %06X not supported.\n", pControl, new_fg);

  if(new_bg >= 0) {
    CNmsButton* pButton = (CNmsButton*)pControl;
    pButton->SetColor(new_bg);
    if(pControlClone)
      ((CNmsButton*)pControlClone)->SetColor(new_bg);
  }

  //{{Suzsoft added for Gensym-432
  if(new_fg >= 0) {
	  CNmsButton* pButton = (CNmsButton*)pControl;
	  pButton->SetColor_fg(new_fg);
	  if(pControlClone)
		  ((CNmsButton*)pControlClone)->SetColor_fg(new_fg);
  }
  //}}Suzsoft

  return 1;
}

long g2ext_nms_remove_menu_item(long menu_index, long nID)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);
  CXTPControl* pControl = find_control(pMenu,nID,MF_BYCOMMAND);

  /* FIXME: Separators aren't items, so pControl will be NULL in that case.
   * We need to adjust flags instead. */
  if(pControl) {
    delete_xtp_icon(pControl);
    pMenu->GetControls()->Remove(pControl);
  }

  if(CloneOfBar(pMenu) && CloneOfControl(pControl)) // Double yuck
    CloneOfBar(pMenu)->GetControls()->Remove(CloneOfControl(pControl));

  // pControl->InternalRelease();
  return 1;
}

long g2ext_nms_dismiss(long window_index)
{
  CMainFrame*  pFrame = GetMainWnd();
  CXTPCommandBars* pCmdBars = pFrame->GetCommandBars();

  if(pCmdBars != NULL)
	  pCmdBars->ClosePopups();

  return pFrame->SendMessage(WM_CANCELMODE);
}

long g2ext_nms_delete_menu_items(long window_index, long menu_index)
{
  CXTPCommandBar* pMenu = GetPtr(CXTPCommandBar,menu_index);

  // This deletes the icons associated with the menu item IDs. Since clones, if
  // any, share the same IDs, this takes care of them also.
  delete_xtp_icons(pMenu);

  pMenu->SetSelected(-1);
  pMenu->GetControls()->RemoveAll();

  if(CloneOfBar(pMenu) != NULL) { // Yuck.
    CloneOfBar(pMenu)->SetSelected(-1);
    CloneOfBar(pMenu)->GetControls()->RemoveAll();
  }

  // Put back MDI buttons, if any.
  CXTPMenuBar* pMenuBar = (GetMainWnd())->GetCommandBars()->GetMenuBar();
  if(pMenu == pMenuBar || CloneOfBar(pMenu) == pMenuBar)
    pMenuBar->RefreshMenu();

  return 1;
}



/*
 * Toolkit Info
 */

long g2ext_nms_get_toolkit(void)
{
  return 2;			/* XTP */
}

/*
 * Native Toolbar
 */

/* For codejock, there's almost no difference between a toolbar and a menu, but
 * that may not be true of all toolkits we might use. */

static XTPBarPosition get_bar_position(int k)
{
  switch(k) {
   case 1: return xtpBarTop;
   case 2: return xtpBarBottom;
   case 3: return xtpBarLeft;
   case 4: return xtpBarRight;
   case 5: return xtpBarFloating;
   default: return xtpBarTop;
  }
}

long g2ext_nms_create_toolbar(long handle, LPWSTR name, long dock, long neighbor,
			      long flags, long default_button_style)
{
  CMainFrame *pFrame = GetMainWnd();
  CXTPCommandBars* pBars = pFrame->GetCommandBars();
  XTPBarPosition pos = get_bar_position(dock);
  CXTPToolBar* pNeighbor = DYNAMIC_DOWNCAST(CXTPToolBar,pBars->GetToolBar(neighbor));
  BOOL enable_tooltips = (flags&1) != 0;
  BOOL visible = (flags&2) != 0;
  G2ToolBar* pBar;

  pBar = (G2ToolBar*) pBars->Add(TStr(name), pos, RUNTIME_CLASS(G2ToolBar));
  if(pBar == NULL)
    return -1;

  pBar->SetVisible(FALSE);
  pBar->m_enableTooltips = enable_tooltips;

  if(default_button_style >= 0)
    pBar->m_defaultButtonStyle = (XTPButtonStyle) default_button_style;

  if(pNeighbor)
    pFrame->DockToolBar(pBar, pos, pNeighbor);

  pBar->SetBarID(handle);
  pBar->SetVisible(visible);
  pFrame->DelayRecalcLayout();
  return SavePtr(pBar);
}



/*
 * Other native controls
 */

#define NMSC_SHOW 1		// Opcodes
#define NMSC_HIDE 2
#define NMSC_SETCURSEL 3
#define NMSC_SETTEXT 4
#define NMSC_ADDTEXT 5
#define NMSC_DELETETEXT 6

/* Add any control to a menu/toolbar. */
long g2ext_nms_append_control(long menu_index, long control_index, long flags)
{
  CXTPCommandBar* pBar  = GetPtr(CXTPCommandBar,menu_index);
  CXTPControl* pControl = GetPtr(CXTPControl,control_index);

  if(flags&MF_RIGHTJUSTIFY)
    pControl->SetFlags(xtpFlagRightAlign);

  return add_control(pBar,pControl);
}

/* Manage an NMS control or toolbar. */
long g2ext_nms_manage_control(long control_index, long opcode, long intArg, LPWSTR strArg)
{
  CObject *pObj = GetPtr(CObject,control_index);
  CXTPToolBar *pBar = DYNAMIC_DOWNCAST(CXTPToolBar,pObj);
  CXTPControl *pControl = DYNAMIC_DOWNCAST(CXTPControl,pObj);
  CXTPControlComboBox *pCombo = DYNAMIC_DOWNCAST(CXTPControlComboBox,pObj);
  CXTPControlEdit *pEdit = DYNAMIC_DOWNCAST(CXTPControlEdit,pObj);

  if(pObj == NULL)
    return -1;

  switch(opcode) {
   case NMSC_SHOW:
     if(pBar) pBar->SetVisible(TRUE);
     if(pControl) pControl->SetVisible(TRUE);
     break;
   case NMSC_HIDE:
     if(pBar) pBar->SetVisible(FALSE);
     if(pControl) pControl->SetVisible(FALSE);
     break;
   case NMSC_ADDTEXT: //added in Gensym-267
     if(pCombo)pCombo->AddString(strArg);
     break;
   case NMSC_DELETETEXT: //added in Gensym-267
     if(pCombo)pCombo->DeleteString(strArg);
   case NMSC_SETCURSEL:
     if(pCombo) pCombo->SetCurSel(intArg);
     break;
   case NMSC_SETTEXT:
     if(pCombo) {
       if(pCombo->GetDropDownListStyle()) {
	 pCombo->SetEditText(strArg);
       } else {
	 int idx = pCombo->FindString(-1, strArg);
	 pCombo->SetCurSel((idx==CB_ERR) ? -1 : idx);
       }
     }
     if(pEdit) pEdit->SetEditText(strArg);
     break;
  }
  return 1;
}

/* Delete any type of control or command bar */
/* FIXME: This doesn't handle clones in the menu bar. */
long g2ext_nms_delete_control(long menu_index, long object_index)
{
  /* menu_index is ignored */
  CCmdTarget* pObject = GetPtr(CCmdTarget,object_index);

  g2ext_decache_g2pointer(object_index);

  if(pObject == NULL)
    return -1;

  delete_xtp_object(pObject);
  return 1;
}

long g2ext_nms_create_edit_box(long nId, LPWSTR name, long width, LPWSTR initial_contents)
{
  CXTPControlEdit* pEdit = (CXTPControlEdit*)CXTPControlEdit::CreateObject();

  if(pEdit == NULL)
    return -1;

  pEdit->SetCaption(TStr(name));
  pEdit->SetID(nId);
  pEdit->SetEditText(TStr(initial_contents));
  if(width>0)
    pEdit->SetWidth(width);

  pEdit->SetFlags(xtpFlagManualUpdate);
  pEdit->ShowLabel(TRUE);	// Apparently no longer the default in XTP 10.2
  g2pvt_nms_set_id_enabled(nId, TRUE);

  return SavePtr(pEdit);
}

/* TODO: Want choices with icons. Probably choices should have been
 * full menu items. */
long g2ext_nms_create_combo_box(long nId, LPWSTR name, long width,
				LPWSTR initial, LPWSTR choices, 
				long flags, long drop_down_width)
{
  CXTPControlComboBox* pCombo = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
  LPWSTR p;
  BOOL allowAnyInput = (flags&1) != 0;

  MTRACE("g2ext_create_combo_box(%d, %ls, %d, %ls, %ls, %d, %d) -> %x\n",
	 nId, name, width, initial, choices, flags, drop_down_width);

  if(pCombo == NULL)
    return -1;

  pCombo->SetCaption(TStr(name));
  pCombo->SetID(nId);
  if(allowAnyInput)
    pCombo->SetDropDownListStyle();

  pCombo->SetStyle(xtpComboLabel); // Show label on the left.

  for(p=choices; *p; p+=wcslen(p)+1)
    pCombo->AddString(TStr(p));

  if(width>0)
    pCombo->SetWidth(width);
  if(drop_down_width>0)
    pCombo->SetDropDownWidth(drop_down_width);

  if(allowAnyInput)
    pCombo->SetEditText(TStr(initial));
  else
    pCombo->SetCurSel(pCombo->FindStringExact(0, TStr(initial))); // Set AFTER adding choices

  pCombo->SetFlags(xtpFlagManualUpdate);
  g2pvt_nms_set_id_enabled(nId, TRUE);

  return SavePtr(pCombo);
}
