// StatusBar.cpp -- Subclassed CXTPStatusBar with G2 interface.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "StatusBar.h"

// Windows pane ID, given G2 pane handle.
static int get_pane_id(int paneHandle)
{
  switch(paneHandle) {
   case 0: return 0;
   case -1: return ID_INDICATOR_SSL;
   case -2: return ID_INDICATOR_PROG;
   default: return paneHandle + PANE_ID_OFFSET;
  }
}

// G2 pane handle, given Window pane ID.
static int get_pane_handle(int paneID)
{
  switch(paneID) {
   case 0: return 0;
   case ID_INDICATOR_SSL: return -1;
   case ID_INDICATOR_PROG: return -2;
   default: return  paneID - PANE_ID_OFFSET;
  }
}

class G2StatusBarPane : public CXTPStatusBarPane
{
public:
  void Initialize(G2StatusBar *pSB, UINT nID, LPCWSTR szText);
};

void G2StatusBarPane::Initialize(G2StatusBar *pSB, UINT nID, LPCWSTR szText)
{
  m_pStatusBar = pSB;
  m_nID = nID;
  m_strText = szText;
  if(szText)
    BestFit();
  else
    m_cxText = GetSystemMetrics(SM_CXICON);
};


IMPLEMENT_DYNCREATE(G2StatusBar, CXTPStatusBar)

BEGIN_MESSAGE_MAP(G2StatusBar, CXTPStatusBar)
 ON_MESSAGE(WM_ICON_CHANGED, OnIconChanged)
 ON_WM_LBUTTONDOWN()
 ON_WM_MBUTTONDOWN()
 ON_WM_RBUTTONDOWN()
 ON_WM_LBUTTONDBLCLK()
 ON_WM_MBUTTONDBLCLK()
 ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

G2StatusBar::G2StatusBar()
{
  VTRACE("Construct "); POB(this);
  m_securityIndicator = FALSE;
  m_securityIcon = NULL;
  m_securityTooltip = NULL;
}

G2StatusBar::~G2StatusBar()
{
  VTRACE("Destruct "); POB(this);
}

void G2StatusBar::OnLButtonDown(UINT nFlags, CPoint point)
{
  Click(SB_LEFT_CLICK, nFlags, point);
}

void G2StatusBar::OnMButtonDown(UINT nFlags, CPoint point)
{
  Click(SB_MIDDLE_CLICK, nFlags, point);
}

void G2StatusBar::OnRButtonDown(UINT nFlags, CPoint point)
{
  Click(SB_RIGHT_CLICK, nFlags, point);
}

void G2StatusBar::OnLButtonDblClk(UINT nFlags, CPoint point)
{
  Click(SB_LEFT_CLICK, nFlags, point, TRUE);
}

void G2StatusBar::OnMButtonDblClk(UINT nFlags, CPoint point)
{
  Click(SB_MIDDLE_CLICK, nFlags, point, TRUE);
}

void G2StatusBar::OnRButtonDblClk(UINT nFlags, CPoint point)
{
  Click(SB_RIGHT_CLICK, nFlags, point, TRUE);
}

void G2StatusBar::Click(UINT button, UINT nFlags, CPoint point, BOOL doubleClick/*=FALSE*/)
{
  CXTPStatusBarPane* pPane = HitTest(point);
  if (pPane) {
    int bits = ((nFlags & MK_CONTROL) ? X11_CONTROL_BIT : 0) |
               ((nFlags & MK_SHIFT) ? X11_SHIFT_BIT : 0) |
               ((GetKeyState(VK_MENU) < 0) ? X11_ALTERNATE_BIT : 0) |
               (doubleClick ? X11_DOUBLE_BIT : 0);
    SendEvent(button, pPane->GetID(), bits);
  }
}

LRESULT G2StatusBar::OnIconChanged(WPARAM changed_icon, LPARAM iconID)
{
  for(int i = 0; i < GetPaneCount(); i++) {
    CXTPStatusBarPane* pPane = GetPane(i);
    if(pPane->IsVisible() && pPane->GetIconIndex() == iconID) {
      CRect r;
      GetItemRect(i, &r);
      InvalidateRect(&r);
    }
  }
  return 0;
}

// Reset statusbar to include only system-defined panes.
BOOL G2StatusBar::Reset()
{
  UINT indicators[] = {ID_SEPARATOR};
  RemoveAll();
  SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
  if(m_securityIndicator)
    SetIconIndicator(ID_INDICATOR_SSL, m_securityIndicator, m_securityIcon, m_securityTooltip);
  return TRUE;
}

// Called from the networking code when SSL handshake succeeds.
void G2StatusBar::SetSecurityIndicator(BOOL enable, LPCSTR szIcon, LPCSTR tooltip)
{
  m_securityIndicator = enable;
  m_securityIcon = szIcon ? strdup(szIcon) : NULL;
  m_securityTooltip = tooltip ? strdup(tooltip) : NULL;
  SetIconIndicator(ID_INDICATOR_SSL, m_securityIndicator, m_securityIcon, m_securityTooltip);
}

// Adapted from CXTPStatusBar::AddIndicator()
void G2StatusBar::AddPane(UINT nID, LPCWSTR szText/*= NULL*/, int icon /*= -1*/, int pos /*= -1*/)
{
  if(pos < 0 || pos > GetPaneCount())
    pos = GetPaneCount();

  if(CommandToIndex(nID) != -1) {
    TRACE1("Duplicate status bar pane ID %d.\n", nID);
    return;
  }

  G2StatusBarPane* pPane = new G2StatusBarPane;
  m_arrPanes.InsertAt(pos, pPane);

  pPane->Initialize(this, nID, szText);
  Update();			// Needed to finish initializing new pane.
}

void G2StatusBar::SetPaneIcon(CXTPStatusBarPane *pPane, int native_icon)
{
  CMainFrame *pFrame = GetMainWnd();
  int iconID = (native_icon >= 0) ? pFrame->StoreNativeIcon(native_icon) : -1;
  pPane->SetIconIndex(iconID);
  pPane->BestFit();
}

void G2StatusBar::SetPaneEnabled(CXTPStatusBarPane *pPane, BOOL enable)
{
  int style = pPane->GetStyle();
  if(enable)
    pPane->SetStyle(style & ~SBPS_DISABLED);
  else
    pPane->SetStyle(style | SBPS_DISABLED);
}

void G2StatusBar::SetPaneBorders(CXTPStatusBarPane *pPane, BOOL enable)
{
  int style = pPane->GetStyle();
  if(enable)
    pPane->SetStyle(style & ~SBPS_NOBORDERS);
  else
    pPane->SetStyle(style | SBPS_NOBORDERS);
}

void G2StatusBar::SetPaneStretch(CXTPStatusBarPane *pPane, BOOL enable)
{
  int style = pPane->GetStyle();
  if(enable)
    pPane->SetStyle(style | SBPS_STRETCH);
  else
    pPane->SetStyle(style & ~SBPS_STRETCH);
}

// Used only for the security icon. TODO: make this not be a special case.
void G2StatusBar::SetIconIndicator(int id, BOOL enable, LPCSTR szIcon, LPCSTR tooltip)
{
  if(enable) {
    if(CommandToIndex(id) >= 0)
      return;

    // Load the icon, if needed.
    if(!XTPImageManager()->GetIconSet(id)) {
      CString iconName(szIcon);
      HICON hIcon = (HICON) ::LoadImage(AfxGetInstanceHandle(), iconName,
					IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR | LR_SHARED);
      XTPImageManager()->SetIcon(hIcon, id);
      DestroyIcon(hIcon);
    }

    CXTPStatusBarPane* pPane = AddIndicator(id, GetPaneCount());
    CString tip(tooltip);
    pPane->SetText(L"");
    pPane->SetIconIndex(id);
    pPane->SetTooltip(tip);
    pPane->SetStyle(SBPS_NOBORDERS);
    pPane->SetWidth(16);

  } else if(CommandToIndex(id) >= 0) {
    RemoveIndicator(id);
  }
  Update();
}

CProgressCtrl *G2StatusBar::EnsureProgressBar(int id)
{
  if(CommandToIndex(id) >= 0)
    return &m_wndProgCtrl;

  // Create progress control
  if (!m_wndProgCtrl.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 0)) {
    TRACE0("Failed to create progress bar control.\n");
    return NULL;
  }
  
  // Add it just after pane 0, before user-defined panes.
  AddIndicator(id, GetPaneCount()<=1 ? GetPaneCount() : 1);

  // Put progress bar control into the pane.
  int nIndex = CommandToIndex(id);
  ASSERT (nIndex != -1);
  
  SetPaneWidth(nIndex, 150);
  SetPaneStyle(nIndex, SBPS_NOBORDERS);
  AddControl(&m_wndProgCtrl, id, FALSE);

  // Initialize progress control.
  m_wndProgCtrl.SetRange(0,100);
  m_wndProgCtrl.SetPos(0);
  m_wndProgCtrl.SetStep(1);

  return &m_wndProgCtrl;
}

void G2StatusBar::RemoveProgressBar(int id)
{
  if(CommandToIndex(id) >= 0)
    RemoveIndicator(id);
}

void G2StatusBar::Update()
{
  UpdateAllPanes(TRUE, TRUE);
}

void G2StatusBar::SendEvent(int eventCode, int paneID /*= 0*/, int bits /*= 0*/)
{
  int paneHandle = get_pane_handle(paneID);
  g2pvt_fire_control_event(GENSYM_STATUSBAR, 0, eventCode, paneHandle, bits, 0, NULL);
}



/*
 * Internal Interface
 */

void g2pvt_set_indicator_icon(BOOL enable, LPCSTR szIcon, LPCSTR tooltip)
{
  GetMainWnd()->GetStatusBar()->SetSecurityIndicator(enable, szIcon, tooltip);
}

/*
 * Lisp Interface
 */

// Pct is 0-100, or -1 to remove the progress bar.
long g2ext_note_progress(LPWSTR message, long pct)
{
  G2StatusBar *pSB = GetMainWnd()->GetStatusBar();

  if(!pSB) return 0;

  if(pct >= 0)
    pSB->EnsureProgressBar(ID_INDICATOR_PROG)->SetPos(pct);
  else
    pSB->RemoveProgressBar(ID_INDICATOR_PROG);

  pSB->SetPaneText(0,message);
  return 1;
}


long g2ext_manage_status_bar(long opcode, long paneHandle, LPCWSTR strValue, long intValue)
{
  CMainFrame *pFrame = GetMainWnd();
  G2StatusBar *pSB = pFrame->GetStatusBar();
  CXTPStatusBarPane *pPane = NULL;
  int paneID = get_pane_id(paneHandle);

  if(!pSB) return 0;

  VTRACE("g2ext_manage_status_bar op=%02d pane=%d %04X str=\"%ls\" int=%d\n",
	 opcode, paneHandle, paneID, strValue, intValue);

  // Status Bar Commands
  switch(opcode) {
   case SB_HIDE:
     pFrame->ShowControlBar(pSB, FALSE, FALSE);
     return 1;

   case SB_SHOW:
     pFrame->ShowControlBar(pSB, TRUE, FALSE);
     return 1;

   case SB_RESET:
     pSB->Reset();
     return 1;

   case SB_MINHEIGHT:
     pSB->GetStatusBarCtrl().SetMinHeight(intValue);
     return 1;

   case SB_TEXT:		// Set text for part 0
     pSB->SetPaneText(0, strValue);
     return 1;

   case SB_ADD_PANE:
     pSB->AddPane(paneID, strValue, -1, intValue); // intValue = where to insert. Default: at end.
     return 1;

   case SB_UPDATE:
     pSB->Update();
     return 1;
  }

  // Status Bar Pane Commands
  pPane = pSB->FindPane(paneID);
  if(!pPane) {
    TRACE1("No status-bar pane found for id %04X\n", paneID);
    return 0;
  }

  switch(opcode) {
   case SB_REMOVE_PANE:
     pPane->Remove();
     return 1;

   case SB_PANE_TEXT:
     pPane->SetText(strValue);
     return 1;

   case SB_PANE_WIDTH:
     pPane->SetWidth(intValue);
     return 1;

   case SB_PANE_VISIBLE:
     pPane->SetVisible(intValue != 0);
     return 1;

   case SB_PANE_FOREGROUND:
     pPane->SetTextColor(intValue);
     return 1;

   case SB_PANE_BACKGROUND:
     pPane->SetBackgroundColor(intValue);
     return 1;

   case SB_PANE_ICON:
     pSB->SetPaneIcon(pPane, intValue);
     return 1;

   case SB_PANE_ALIGNMENT:
     pPane->SetTextAlignment(intValue);
     return 1;

   case SB_PANE_TOOLTIP:
     pPane->SetTooltip(strValue);
     return 1;

   case SB_PANE_ENABLED:
     pSB->SetPaneEnabled(pPane, intValue != 0);
     return 1;

   case SB_PANE_BORDERS:
     pSB->SetPaneBorders(pPane, intValue != 0);
     return 1;
  }
  return 0;
}
