// MainFrame.cpp -- Overall frame window for TWNG

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "NativeView.h"
#include "WorkspaceView.h"
#include "TreeView.h"
#include "ShortcutBar.h"
#include "ListBar.h"
#include "PropGrid.h"
#include "dyndlgs.h"
#include "ConfirmExitDlg.h"

extern "C" int g2pvt_closebox;
extern "C" int g2pvt_minimize;
extern "C" int  g_Gensym69;
extern "C" char icon_name[];
extern void g2pvt_refresh_pane_tabs(CXTPDockingPane *pPane);
extern BOOL g2pvt_is_dynamic_dialog(CWnd *pWnd);
extern BOOL g2pvt_is_cchildfrm(CWnd *pWnd);
extern BOOL g2pvt_is_listbar(CWnd *pWnd);
extern void g2pvt_add_view_to_listbar(G2ListBar *pBar, LPCTSTR caption, int folder, CWnd *pWnd);

extern "C" {
  GENSYMDIALOG *g2pvt_find_dialog(int g2_id);
  CONTROLITEM *g2pvt_lookup_control_by_id(int controlId, GENSYMDIALOG *dialog);
  void g2pvt_set_window_icon_internal(HWND hwnd, int native_icon);
};

// Gensym additions to XTPDockingPaneOptions:
#define gensymPaneHideOnClose ((enum XTPDockingPaneOptions)256)
#define gensymPaneNoDraggable ((enum XTPDockingPaneOptions)512)

using namespace XTPDockingPanePaintThemes;

///////////////////////////////////////////////////////////////////
// CG2CommandBars

void CG2CommandBars::ContextMenu(CXTPToolBar* pToolBar, CPoint point)
{
  if (g_Gensym69)
  {
	return;
  }
  g2pvt_enter_modal_loop();
  
  CXTPCommandBars::ContextMenu(pToolBar, point);
  
  g2pvt_exit_modal_loop();
}

IMPLEMENT_DYNCREATE(CG2CommandBars, CXTPCommandBars)

////////////////////////////////////////////////////////////////////
// CG2DockingPaneTabbedContainer

CG2DockingPaneTabbedContainer::CG2DockingPaneTabbedContainer(CXTPDockingPaneLayout* pLayout)
  : CXTPDockingPaneTabbedContainer(pLayout)
{
}

void CG2DockingPaneTabbedContainer::OnLButtonDown(UINT nFlags, CPoint point)
{
  g2pvt_enter_modal_loop();
  CXTPDockingPaneTabbedContainer::OnLButtonDown(nFlags, point);
  g2pvt_exit_modal_loop();
}

IMPLEMENT_DYNAMIC(CG2DockingPaneTabbedContainer, CXTPDockingPaneTabbedContainer)

BEGIN_MESSAGE_MAP(CG2DockingPaneTabbedContainer, CXTPDockingPaneTabbedContainer)
  ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////
// CG2DockingPaneMiniWnd

CG2DockingPaneMiniWnd::CG2DockingPaneMiniWnd(CXTPDockingPaneLayout* pLayout)
  : CXTPDockingPaneMiniWnd(pLayout)
{
}

void CG2DockingPaneMiniWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
  g2pvt_enter_modal_loop();
  CXTPDockingPaneMiniWnd::OnNcLButtonDown(nHitTest, point);
  g2pvt_exit_modal_loop();
}

void CG2DockingPaneMiniWnd::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
  g2pvt_enter_modal_loop();
  CXTPDockingPaneMiniWnd::OnNcRButtonDown(nHitTest, point);
  g2pvt_exit_modal_loop();
}

IMPLEMENT_DYNAMIC(CG2DockingPaneMiniWnd, CXTPDockingPaneMiniWnd)

BEGIN_MESSAGE_MAP(CG2DockingPaneMiniWnd, CXTPDockingPaneMiniWnd)
  ON_WM_NCLBUTTONDOWN()
  ON_WM_NCRBUTTONDOWN()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////
// CG2DockingPaneManager

CXTPDockingPaneBase* CG2DockingPaneManager::OnCreatePane(XTPDockingPaneType type, CXTPDockingPaneLayout* pLayout)
{
  CXTPDockingPaneBase* pPane = NULL;

  switch (type)
  {
    case xtpPaneTypeTabbedContainer:
      pPane = new CG2DockingPaneTabbedContainer(pLayout);
      break;

    case xtpPaneTypeMiniWnd:
      pPane = new CG2DockingPaneMiniWnd(pLayout);
      break;

    default:
      pPane = CXTPDockingPaneManager::OnCreatePane(type, pLayout);
  }

  return pPane;
}

////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMainFrame, CXTPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTPMDIFrameWnd)
  ON_WM_CREATE()
  ON_WM_SYSCOMMAND()
  ON_XTP_INITCOMMANDSPOPUP()
  ON_MESSAGE(WM_XTP_INITMENUBAR, OnInitMenuBar)
  ON_MESSAGE(WM_XTP_UNINITCOMMANDSPOPUP, OnUnInitCommandsPopup)
  //Added for gensym-3031 by Suzsoft
  ON_MESSAGE(WM_XTP_RELEASE_POPUP, OnReleasePopup)
  //End of adding
  ON_MESSAGE(WM_XTP_MODALLOOP, OnModalLoop)
  ON_MESSAGE(WM_XTP_CONTROLSELECTED, OnControlSelected)
  ON_MESSAGE(WM_XTP_NEWTABITEM, OnNewTabItem)
  ON_MESSAGE(WM_XTP_PRETRANSLATEMOUSEMSG, OnTabClick)

  ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
  ON_MESSAGE(XTPWM_SHORTCUTBAR_NOTIFY, OnListBarNotify)
  ON_MESSAGE(XTPWM_PROPERTYGRID_NOTIFY, OnPropertyGridNotify)

  // XTP uses 9300-9599 (or so), plus 35000-35002
  // MFC uses/reserves 57600-59647 (0xE100-0xE8FF)
  // NMS uses 1000-1050 for stock commands, 1500-32000 for all others.

  ON_UPDATE_COMMAND_UI_RANGE(XTP_ID_MENUBAR_CLOSE, XTP_ID_MENUBAR_SYSMENU, OnUpdateMDIButton)

  // We want to start using fixed IDs for all of the built-in G2
  // commands, anyways. Or else, have TW send back command names.
  ON_XTP_EXECUTE_RANGE(1000,1050,OnExecuteNMS)   // "Stock" NMS commands
  ON_UPDATE_COMMAND_UI_RANGE(1000,1050,OnUpdateNMSCommand)

  ON_XTP_EXECUTE_RANGE(1500,9299,OnExecuteNMS)   // All other NMS Commands, batch 1.
  ON_UPDATE_COMMAND_UI_RANGE(1500,9299,OnUpdateNMSCommand)

  // FIX: use 9600-33500 range instead 9600-32000 for 8100-32000 NMS handles
  ON_XTP_EXECUTE_RANGE(9600,33500,OnExecuteNMS)   // All other NMS Commands, batch 2.
  ON_UPDATE_COMMAND_UI_RANGE(9500,33500,OnUpdateNMSCommand)
  ON_COMMAND(AFX_IDM_FIRST_MDICHILD - 1, onMDIWindowList)
  ON_WM_CLOSE()
END_MESSAGE_MAP()

void CMainFrame::onMDIWindowList() {
	SendMessage(WM_COMMAND, AFX_IDM_FIRST_MDICHILD + 9, 0);
}

CMainFrame::CMainFrame()
{
  XTAuxData().InitResources(AfxGetInstanceHandle());
}

CMainFrame::~CMainFrame()
{
  // XTP automatically destroys the menu bar and all toolbars on exit.  The NMS
  // menus we create, however, are actually popup bars, which XTP doesn't keep
  // track of. So we ought to free all of them here. For starters, just free the
  // one which was cloned into the menu bar. This is all just for tidiness in
  // Visual Studio, since we're exiting and don't really care. -fmw, 2/22/06
  if(m_pMenuBarSource)
    m_pMenuBarSource->InternalRelease();
  m_pMenuBarSource = NULL;
}


// Take control of the frame title.
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  cs.style &= ~FWS_ADDTOTITLE;
  // GENSYMCID-809: Twng window should have a fixed ClassName value
  // Check if our class is already defined
  LPCTSTR pszClassName = _T("GensymFrameClass");
  WNDCLASS wndcls;
  if (!::GetClassInfo(AfxGetInstanceHandle(), pszClassName, &wndcls)) {
      // Get the current requested window class
      VERIFY(GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wndcls));

      // We want to register this info with our name
      wndcls.lpszClassName = pszClassName;

      // Need to preset the icon otherwise the function GetIconWndClass
      // calling us will overwrite our class.
      LPCTSTR pszIcon = MAKEINTRESOURCE(IDR_MAINFRAME);
      HINSTANCE hInst = AfxFindResourceHandle(pszIcon, ATL_RT_GROUP_ICON);
      _ASSERTE(hInst!=NULL);
      wndcls.hIcon =     ::LoadIcon(hInst, pszIcon);

      // Register our class now and check the outcome
      if (!::RegisterClass(&wndcls)) {
	  _ASSERTE(!__FUNCTION__ "RegisterClass failed");
	  return CXTPMDIFrameWnd::PreCreateWindow(cs);
	}
    }

  // Now use our class
  cs.lpszClass = pszClassName;
  return CXTPMDIFrameWnd::PreCreateWindow(cs);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  if (strlen (icon_name) > 0) {
    HANDLE icn = LoadImageA(::GetModuleHandle(NULL), icon_name, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (icn) {
      ::SetClassLong(m_hWnd,GCL_HICON,(LONG)icn);
    }
  }

  if (!m_wndStatusBar.CreateEx(this, SBARS_SIZEGRIP | SBT_TOOLTIPS) ||
      !m_wndStatusBar.Reset()) {
    TRACE0("Failed to create status bar\n");
    return -1;
  }

  if (!InitCommandBars(RUNTIME_CLASS(CG2CommandBars)))
    return -1;

  // Set some global options.
  // FIXME?
  //  xtAfxData.bXPMode = TRUE;

  GetCommandBars()->GetCommandBarsOptions()->bShowExpandButtonAlways = FALSE;

  // Default menu bar
  CXTPCommandBar* pMenuBar = GetCommandBars()->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
  pMenuBar->SetFlags(xtpFlagIgnoreSetMenuMessage);
  pMenuBar->SetFlags(xtpFlagAddMDISysPopup);
	
  CXTPCommandBars* pCommandBars = GetCommandBars();
  //File toolbar
  CXTPToolBar* pFileBar = (CXTPToolBar*)pCommandBars->Add(_T("File"), xtpBarTop);
  if (!pFileBar ||
		!pFileBar->LoadToolBar(IDR_FILE))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pFileBar->SetVisible(FALSE);
  //Edit toolbar
  CXTPToolBar* pEditBar = (CXTPToolBar*)pCommandBars->Add(_T("Edit"), xtpBarTop);
  if (!pEditBar ||
		!pEditBar->LoadToolBar(IDR_EDIT))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pEditBar->SetVisible(FALSE);
  //View toolbar
  CXTPToolBar* pViewBar = (CXTPToolBar*)pCommandBars->Add(_T("View"), xtpBarTop);
  if (!pViewBar ||
		!pViewBar->LoadToolBar(IDR_VIEW))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pViewBar->SetVisible(FALSE);
  //Workspace toolbar
  CXTPToolBar* pWorkspaceBar = (CXTPToolBar*)pCommandBars->Add(_T("Workspace"), xtpBarTop);
  if (!pWorkspaceBar ||
		!pWorkspaceBar->LoadToolBar(IDR_WORKSPACE))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pWorkspaceBar->SetVisible(FALSE);
  //Run toolbar
  CXTPToolBar* pRunBar = (CXTPToolBar*)pCommandBars->Add(_T("Run"), xtpBarTop);
  if (!pRunBar ||
		!pRunBar->LoadToolBar(IDR_RUN))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pRunBar->SetVisible(FALSE);
  //Tools toolbar
  CXTPToolBar* pToolsBar = (CXTPToolBar*)pCommandBars->Add(_T("Tools"), xtpBarTop);
  if (!pToolsBar ||
		!pToolsBar->LoadToolBar(IDR_TOOLS))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pToolsBar->SetVisible(FALSE);
  //Window toolbar
  CXTPToolBar* pWindowBar = (CXTPToolBar*)pCommandBars->Add(_T("Window"), xtpBarTop);
  if (!pWindowBar ||
		!pWindowBar->LoadToolBar(IDR_WINDOW))
	{
		TRACE0("Failed to create toolbar\n");
	}
  pWindowBar->SetVisible(FALSE);

  m_pMenuBarSource = NULL;	// Toolbar which was the source of current menu bar.

  // Disable the closebox if requested.
  if(g2pvt_closebox == 0)
    GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_GRAYED);

  // Disable the minimize box if requested.
  if(g2pvt_minimize == 0) {
    GetSystemMenu(FALSE)->EnableMenuItem(SC_MINIMIZE,MF_BYCOMMAND|MF_GRAYED);
    LONG style = ::GetWindowLong(m_hWnd, GWL_STYLE);
    style = style & (~WS_MINIMIZEBOX);
    ::SetWindowLongA(m_hWnd, GWL_STYLE, style);
  }

  // Enable dockable panes
  m_paneManager.InstallDockingPanes(this);
  m_paneManager.SetAlphaDockingContext(TRUE);

  // Default UI theme
  SetTheme(DEFAULT_UI_THEME);

  // Initialize our CImageList versions of the native-icons HIMAGELISTs.
  m_smallImageList.Attach(g2pvt_get_image_list(16));
  m_largeImageList.Attach(g2pvt_get_image_list(32));

  XTPPaintManager()->RefreshMetrics();

  return 0;
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
  switch(nID & 0xFFF0) {
   case SC_CLOSE:
     if(g2pvt_closebox == 0)
       return;
     break;
   case SC_MINIMIZE:
     if(g2pvt_minimize == 0)
       return;
     break;
   case SC_KEYMENU:
     if(lParam == VK_RETURN)	// Alt+Return in the editor gets here, and causes a beep
       return;			// if we let it through. -fmw, 7/27/07
     break;
  }
  CXTPMDIFrameWnd::OnSysCommand(nID,lParam);
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  int rc = g2pvt_frame_wndproc(m_hWnd, message, wParam, lParam);
  if(rc == 0)
    return 0;
  else if (rc == 2)
    return TRUE;
  else
    return CFrameWnd::WindowProc(message, wParam, lParam);
}

CDocument *CMainFrame::GetActiveDocument()
{
  return NULL;
}

void CMainFrame::OnUpdateMDIButton(CCmdUI *pCmdUI)
{
  UINT nID = pCmdUI->m_nID;

  nID = nID == XTP_ID_MENUBAR_CLOSE ? SC_CLOSE :
        nID == XTP_ID_MENUBAR_RESTORE ? SC_RESTORE :
        nID == XTP_ID_MENUBAR_MINIMIZE ? SC_MINIMIZE : nID;

  pCmdUI->Enable(g2pvt_syscommand_enabled_p(MDIGetActive()->GetSafeHwnd(),nID));
}




/*
 * G2-Managed Windows
 */

#define DEFAULT_PANE_SIZE 240

// Create appropriate container window and install pWnd therein.
CMDIChildWnd* CMainFrame::WrapWnd(CWnd *pWnd, int handle,
				  int x, int y, int width, int height,
				  int dock, int neighbor, CSize minSize, LPWSTR title, int icon)
{
  CMDIChildWnd *pMDIChild = NULL;
  CXTPDockingPane* pPane = NULL;
  CWnd *pParentWnd;
  GENSYMDIALOG *pDlg;
  CONTROLITEM *pControl;
  CRect rect;
  int status, ctrlID;
  CString strTitle;
  HICON hIcon;

  if(title == NULL)
    pWnd->GetWindowText(strTitle);
  else
    strTitle = title;

  switch(dock&0xF) {
   case DOCK_MDI_CHILD:
     x = DefDim(x,CW_USEDEFAULT);
     y = DefDim(y,CW_USEDEFAULT);

     if(width==DEFAULT_DIM || height==DEFAULT_DIM)
       rect = CRect(x, y, CW_USEDEFAULT, CW_USEDEFAULT);
     else {
       rect = CRect(x, y, x+width, y+height);
       // Compute size of container window, but leave position alone.
       ClientToWindowEx(&rect, WS_OVERLAPPEDWINDOW|WS_CHILD, WS_EX_MDICHILD);
       rect = CRect(x, y, x+rect.Width(), y+rect.Height());
     }

     pMDIChild = new CChildFrm();
     pMDIChild->Create(NULL, strTitle, WS_CHILD | WS_OVERLAPPEDWINDOW, rect);
     pMDIChild->GetClientRect(rect);
     pWnd->SetParent(pMDIChild);
     pWnd->MoveWindow(rect);
     hIcon = (icon>0) ? g2pvt_get_native_icon(icon) : theApp.LoadIcon(L"App");
     if(hIcon)
       pMDIChild->SetIcon(hIcon, FALSE);

     pWnd->ShowWindow(SW_SHOW);
     pMDIChild->ShowWindow(SW_SHOW);
     pMDIChild->MDIActivate();
     break;

   case DOCK_EMBEDDED:
     // Sync with LISP encode-dock-and-neighbor

     // Neighbor here is the container's handle, and dock is some encoding of
     // where in the container. For dialogs, it is the control ID; for shortcut bars,
     // it is the folder number.
     ctrlID = (dock>>4) & 0xFFFF;
     pDlg = g2pvt_find_dialog(neighbor);
     pControl = g2pvt_lookup_control_by_id(ctrlID, pDlg);

     // Even is pParentWnd is NULL, we *should* be able to find a dialog
     // component structure (CONTROLITEM). Then save our window into that,
     // hidden, pending reparenting when the dialog window is created.
     if(pControl)
       pControl->view_handle = handle;

     pParentWnd = FIND_WND(neighbor,CWnd);
     if(!pParentWnd)
       return NULL;

     if(g2pvt_is_dynamic_dialog(pParentWnd) || g2pvt_is_cchildfrm(pParentWnd)) {
       g2pvt_replace_control_in_dialog(neighbor, ctrlID, pWnd);
       pWnd->ShowWindow(SW_SHOW);

     } else if(g2pvt_is_listbar(pParentWnd)) {
       g2pvt_add_view_to_listbar((G2ListBar*)pParentWnd, strTitle, ctrlID, pWnd);
     } else {
       // TODO: warning
     }
     break;

   case DOCK_TOP_LEVEL:
     pWnd->ShowWindow(SW_SHOW);	// FIXME: placeholder.
     break;

   default:			// Otherwise, a docking pane.
     pPane = CreatePane(handle, strTitle,
			DefDim(x,0), DefDim(y,0),
			DefDim(width,DEFAULT_PANE_SIZE), DefDim(height,DEFAULT_PANE_SIZE),
			dock, neighbor, icon, &status, minSize);
     pPane->Attach(pWnd);
     // G2 needs to know where docked.
     g2pvt_send_window_status(pWnd->m_hWnd, handle, status);
     break;
  }
  return pMDIChild;
}

void CMainFrame::SaveWnd(CWnd *pWnd, int handle)
{
  if(handle <= 0) return;
  m_windows[handle] = pWnd;
}

CWnd *CMainFrame::FindWnd(int handle, CRuntimeClass *pClass /* = NULL */)
{
  if(handle <= 0) return NULL;
  CWnd *pWnd;

  if(!m_windows.Lookup(handle,pWnd))
    return NULL;

  if(pClass && !pWnd->IsKindOf(pClass)) {
    WARNF("CWnd for handle [%d] not of expected class!\n", handle);
    return NULL;
  }
  return pWnd;
}

void CMainFrame::ForgetWnd(int handle)
{
  if(handle <= 0) return;
  m_windows.RemoveKey(handle);
}

// Deals with the various possible parent types.
void CMainFrame::DestroyWnd(int handle)
{
  if(handle <= 0) return;

  CXTPDockingPaneManager *pMgr = GetDockingPaneManager();
  CXTPDockingPane *pPane = g2pvt_find_pane(handle);
  CWnd *pChild = pPane ? pPane->GetChild() : NULL;
  CWnd *pWnd = FindWnd(handle);

  if(pPane) {
    pPane->Detach();
    pMgr->DestroyPane(pPane);
    if(pChild)
      pChild->DestroyWindow();

  } else if (pWnd) {
    CFrameWnd *pFrame = pWnd->GetParentFrame();
    if(pFrame == this)
      pWnd->DestroyWindow();
    else
      pFrame->DestroyWindow();
  }
}

HWND CMainFrame::CoorHwnd()
{
  return Frame_is_embedded ? ::GetDesktopWindow() : m_hWndMDIClient;
}




/*
 * Menus
 */

// We get a chance to handle this message first, before WM_COMMAND. The
// difference here is that we get a handle to the control. See the end of
// CXTPControl::OnExecute. You must set *pResult to TRUE, otherwise the
// WM_COMMAND handler will run, too.
BOOL CMainFrame::OnExecuteNMS(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
  NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

  MTRACE("CMainFrame::OnExecuteNMS id=%d, NotifyCode=%d\n", id, pNMHDR->code);
  SendMessage(WM_NULL);		// Try to wake up the event loop.

  if(pNMHDR->code != CBN_XTP_EXECUTE)
    return FALSE;

  NMXTPCONTROL* pNMH = (NMXTPCONTROL*)pNMHDR;
  CXTPControl* pControl = (CXTPControl*) pNMH->pControl;


  if (pControl->GetType() == xtpControlComboBox) {
    CXTPControlComboBox* pCombo = (CXTPControlComboBox*)pControl;
    MTRACE("Combo choice: %d \"%s\"\n", pCombo->GetCurSel(), pCombo->GetEditText());
    g2pvt_send_nms_control_event(m_hWnd,
				 pControl->GetID(),
				 pCombo->GetCurSel(),
				 WStr(pCombo->GetEditText()));

    *pResult = TRUE;		// Handled
    return TRUE;

  } else if (pControl->GetType() == xtpControlEdit) {
    CXTPControlEdit* pEdit = (CXTPControlEdit*)pControl;
    MTRACE("Edit choice: \"%s\"\n", pEdit->GetEditText());
    g2pvt_send_nms_control_event(m_hWnd,
				 pControl->GetID(),
				 -1,
				 WStr(pEdit->GetEditText()));
    *pResult = TRUE;		// Handled
    return TRUE;
  }

  return FALSE;
}

void CMainFrame::OnUpdateNMSCommand(CCmdUI *pCmdUI)
{
  pCmdUI->Enable(g2pvt_nms_get_id_enabled(pCmdUI->m_nID));
}

// Sets the menu bar to be the default, "unconnected" menu bar.
void CMainFrame::ShowDefaultMenuBar(BOOL show)
{
  CXTPMenuBar* pMenuBar = GetCommandBars()->GetMenuBar();
  if(pMenuBar->IsTrackingMode())
    pMenuBar->SetTrackingMode(FALSE);
  pMenuBar->GetControls()->RemoveAll();
  pMenuBar->LoadMenuBar(IDR_MAINFRAME);
  pMenuBar->SetVisible(show);
  m_pMenuBarSource = NULL;
}

// Our local copy of XTP now supports WM_XTP_INITMENUBAR, the analog of
// WM_INITMENU. XTP 9.00 also supports it. So we no longer need the
// PreTranslateMessage hack. -fmw, 6/21/04

LRESULT CMainFrame::OnInitMenuBar(WPARAM wParam, LPARAM lParam)
{
  CXTPMenuBar* pMenuBar = (CXTPMenuBar*)lParam;

  return g2pvt_update_menubar(); // This may delete and recreate all items in the menubar!
}

void CMainFrame::OnInitCommandsPopup(CXTPPopupBar* pPopup)
{
  CXTPCommandBar* pCommandBar = (CXTPCommandBar*)pPopup;

  if(pCommandBar == NULL)
    return;

  // Update system menu items. Since XTP's InitCommandsPopup doesn't tell us
  // whether it is the system menu, unlike Win32 WM_INITMENUPOPUP, we guess by
  // looking at the class, which is a plain CXTPPopupBar (all of the G2 popups
  // are CNmsPopupBar's). It does no harm if we accidentally update other menus.
  // -fmw, 2/2/06
  if(pCommandBar->GetRuntimeClass() == RUNTIME_CLASS(CXTPPopupBar)) {
    for(int i=0; i<pCommandBar->GetControls()->GetCount(); i++) {
      UINT nID = pCommandBar->GetControl(i)->GetID();
      if (0xF000 <= nID && nID < 0xF1F0)
	pCommandBar->GetControl(i)->SetEnabled(g2pvt_syscommand_enabled_p(MDIGetActive()->GetSafeHwnd(), nID));
    }

  } else {
    if(CloneOfBar(pCommandBar))		// Want the clone if there is one.
      pCommandBar = CloneOfBar(pCommandBar);

    g2pvt_update_dynamic_menu((HANDLE)pCommandBar, 0); // TODO: Compute pos in parent.
  }
}

LRESULT CMainFrame::OnUnInitCommandsPopup(WPARAM wParam, LPARAM lParam)
{
  CXTPCommandBar* pCommandBar = (CXTPCommandBar*)lParam;

  if(pCommandBar == NULL)
    return 0;

  if(CloneOfBar(pCommandBar))		     // Want the clone if there is one.
    pCommandBar = CloneOfBar(pCommandBar);

  g2pvt_nms_menu_unposted((HANDLE)pCommandBar);
  return 0;
}

//Added for gensym-3031 by Suzsoft
LRESULT CMainFrame::OnReleasePopup(WPARAM wParam, LPARAM lParam)
{
  CXTPPopupBar* PopupBar = (CXTPPopupBar*)lParam;
  if (PopupBar != NULL)
  {
	PopupBar->InternalRelease();
  }
  return 0;
}
//End of adding

LRESULT CMainFrame::OnControlSelected(WPARAM wParam, LPARAM lParam)
{
  CXTPControl *pControl = (CXTPControl*)wParam;

  if(pControl == NULL) {
    if(XTPMouseManager()->IsMouseLocked() == FALSE &&
       XTPMouseManager()->IsTrackedLock() == FALSE)
      g2pvt_fire_nms_selection_callbacks((HANDLE)NULL, 0); /* Exited menu tracking entirely. */

  } else {
    if(CloneOfControl(pControl))	             // Want the clone if there is one.
      pControl = CloneOfControl(pControl);

    g2pvt_fire_nms_selection_callbacks((HANDLE)pControl->GetParent(), pControl->GetID());
  }
  return 0;
}

LRESULT CMainFrame::OnModalLoop(WPARAM wParam, LPARAM lParam)
{
  if(wParam)
    g2pvt_enter_modal_loop();
  else
    g2pvt_exit_modal_loop();
  return 0;
}

void g2pvt_menu_size(int menu_size)
{
	GetMainWnd()->SetMenuSize(menu_size);
}

void CMainFrame::SetMenuSize(int menusize)
{
		LOGFONT logFont;
		HGDIOBJ hObj = ::GetStockObject (DEFAULT_GUI_FONT);
	    ::GetObject (hObj, sizeof (LOGFONT), &logFont);
		logFont.lfWeight = FW_THIN;
		logFont.lfHeight = menusize;
        GetCommandBars() ->GetPaintManager()->SetCommandBarsFontIndirect(&logFont);
		::DeleteObject (hObj);	
		GetCommandBars()->RedrawCommandBars();
		m_wndStatusBar.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}


void CMainFrame::SetMenuIconSize(int menu_icon_size)
{
    if ((menu_icon_size<0)||(menu_icon_size>96))
    {
        return;
    }

    CXTPCommandBars* pCommandBars = GetMainWnd()->GetCommandBars();
    if (NULL==pCommandBars)
    {
        return;
    }
        
    CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();
    if (NULL==pOptions)
    {
        return;
    }
    
    pOptions->bLargeIcons = TRUE;
    pOptions->szIcons.cx=menu_icon_size;
    pOptions->szIcons.cy=menu_icon_size;
    pOptions->szLargeIcons.cx=menu_icon_size;
    pOptions->szLargeIcons.cy=menu_icon_size;
    pOptions->szPopupIcons.cx=menu_icon_size;
    pOptions->szPopupIcons.cy=menu_icon_size;
	pCommandBars->RedrawCommandBars();
	
    return;
}

void CMainFrame::OnClose()
{
	// Display exit confirm dialog if necessary
	// ("Don't ask again" check box is not checked in previous or in this sessions)
	if(ConfirmExitDialog_AskToExit())
	{
		// Exit TWNG if user click "Yes" button or such a necessity is absent
		CXTPMDIFrameWnd::OnClose();
	}
}

void g2ext_nms_set_iconsize(long icon_size)
{
    GetMainWnd()->SetMenuIconSize(icon_size);
}

/*
 * UI Theme
 */


long g2ext_nms_set_theme(long theme)
{
  GetMainWnd()->SetTheme(theme);
  return 1;
}

void CMainFrame::SetTheme(int theme)
{
  switch(theme) {
   case 2000:
     m_paneManager.SetTheme(xtpPaneThemeDefault);
     CXTPPaintManager::SetTheme(xtpThemeOffice2000);
     XTThemeManager()->SetTheme(xtThemeOffice2000);
     CXTPShortcutBarThemeManager::GetThemeManager()->SetTheme(xtpShortcutThemeOffice2000);
     break;

   case 2001:			// This has been the default theme.
     m_paneManager.SetTheme(xtpPaneThemeOffice);
     CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
     XTThemeManager()->SetTheme(xtThemeOfficeXP);
     CXTPShortcutBarThemeManager::GetThemeManager()->SetTheme(xtpShortcutThemeOfficeXP);
     break;

   case 2002:
     m_paneManager.SetTheme(xtpPaneThemeWinExplorer);
     CXTPPaintManager::SetTheme(xtpThemeNativeWinXP);
     XTThemeManager()->SetTheme(xtThemeNativeWinXP);
     CXTPShortcutBarThemeManager::GetThemeManager()->SetTheme(xtpShortcutThemeNativeWinXP);
     break;

   case 2003:
     m_paneManager.SetTheme(xtpPaneThemeOffice2003);
     CXTPPaintManager::SetTheme(xtpThemeOffice2003);
     XTThemeManager()->SetTheme(xtThemeOffice2003);
     CXTPShortcutBarThemeManager::GetThemeManager()->SetTheme(xtpShortcutThemeOffice2003);
     break;

  }

  GetCommandBars()->RedrawCommandBars();
  m_wndStatusBar.RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
}



/*
 * Native Icons
 */

#define NATIVE_ICON_RESOURCE_OFFSET 32000 // Don't overlap with command IDs

void g2pvt_destroy_native_icons(BOOL destroy)
{
  GetMainWnd()->ClearAllNativeIcons();
  g2pvt_destroy_native_icon_imagelists(destroy);
}

int g2pvt_icon_resource_id(int native_icon)
{
  // FIXME: Check for exceeding 16 bits !!
  return g2pvt_icon_index(native_icon) + NATIVE_ICON_RESOURCE_OFFSET;
}

/* Copy into XTP's icon stores, and return assigned iconID.  We only need to do
 * this for icons used in XTP controls, such as command bars, tabs, panes, etc. */
int CMainFrame::StoreNativeIcon(int native_icon)
{
  HICON hIcon;
  int iconID;

  hIcon = g2pvt_get_native_icon(native_icon);
  if(!hIcon)
    return -1;

  iconID = g2pvt_icon_resource_id(native_icon);

  XTPImageManager()->SetIcon(hIcon, iconID);
  GetDockingPaneManager()->SetIcon(iconID, hIcon);
  DestroyIcon(hIcon);
  return iconID;
}

void CMainFrame::SetPaneIcon(CXTPDockingPane *pPane, int native_icon)
{
  pPane->SetIconID(StoreNativeIcon(native_icon));
  g2pvt_refresh_pane_tabs(pPane);
}

void CMainFrame::ClearAllNativeIcons()
{
  // Remove only from NATIVE_ICON_RESOURCE_OFFSET on up?
  // XTPImageManager()->RemoveAll(); // FIXME: Too much?
  GetDockingPaneManager()->ClearIconMap();
}




/*
 * Icon Updating
 */

void g2pvt_refresh_native_icon(int native_icon, int where)
{
  GetMainWnd()->IconChanged(native_icon, where);
}

// Gensym-397 fix. For tree-views refreshing, where is 0xF0, otherwise 0xFF,
// So modify bitwise AND operation, at this time for XTP controls, it's &0x09, icons will not be copied into,
// and for others, 0x11,0x12, 0x14, 0x18, 0x20, 0x40 will enture icon refreshed. 
void CMainFrame::IconChanged(int native_icon, int where)
{
  int iconID = g2pvt_icon_resource_id(native_icon);

  if(where & 0x09)		/* If used by XTP controls */
    StoreNativeIcon(native_icon);

  if(where & 0x01)		/* MenuBar and toolbars */
    UpdateToolbarIcons(native_icon);

  if(where & 0x02)		/* MDI child windows */
    UpdateMDIChildIcons(native_icon);

  if(where & 0x04)		/* Dialog windows */
    g2pvt_refresh_dialog_icon(native_icon);

  if(where & 0x08)		/* Panes */
    UpdatePaneIcons(native_icon);

  if(where & 0x08)		/* Interior of managed windows */
    UpdateWndIcons(native_icon);

  if(where & 0x20)		/* Status Bar */
    GetStatusBar()->SendMessage(WM_ICON_CHANGED, native_icon, iconID);

  if(where & 0x40)		/* Grid Views */
    g2pvt_refresh_grid_view_icon(native_icon);
}

void CMainFrame::UpdateToolbarIcons(int native_icon)
{
  CXTPCommandBars* pBars = GetCommandBars();
  CXTPToolBar *pBar;
  CXTPControl *pControl;
  int i,j;
  int iconID = g2pvt_icon_resource_id(native_icon);

  for(i=0; i<pBars->GetCount(); i++) {
    pBar = pBars->GetAt(i);
    for(j=0; j<pBar->GetControls()->GetCount(); j++) {
      pControl = pBar->GetControls()->GetAt(j);
      if(pControl->GetIconId() == iconID && pControl->IsVisible())
	pControl->GetParent()->InvalidateRect(pControl->GetRect());
    }
  }
}

void CMainFrame::UpdateMDIChildIcons(int native_icon)
{
  CWnd *pClient = CWnd::FromHandle(m_hWndMDIClient);
  int iconID = g2pvt_icon_resource_id(native_icon);

  for(CWnd *pWnd=pClient->GetWindow(GW_CHILD); pWnd; pWnd=pWnd->GetWindow(GW_HWNDNEXT))
    pWnd->SendMessage(WM_ICON_CHANGED, native_icon, iconID);
}

void CMainFrame::UpdateWndIcons(int native_icon)
{
  POSITION pos;
  int handle;
  CWnd *pWnd;
  int iconID = g2pvt_icon_resource_id(native_icon);

  for(pos = m_windows.GetStartPosition(); pos; ) {
    m_windows.GetNextAssoc(pos, handle, pWnd);
    if(::IsWindow(pWnd->GetSafeHwnd()) && pWnd->IsWindowVisible() && !pWnd->IsIconic())
      pWnd->SendMessage(WM_ICON_CHANGED, native_icon, iconID);
  }
}

void CMainFrame::UpdatePaneIcons(int native_icon)
{
  CXTPDockingPaneInfoList& panes = GetDockingPaneManager()->GetPaneList();
  CXTPDockingPane* pPane;
  POSITION pos;
  int iconID = g2pvt_icon_resource_id(native_icon);

  for(pos = panes.GetHeadPosition(); pos; ) {
    pPane = panes.GetNext(pos);
    if(pPane->IsValid() && !pPane->IsClosed()) {
      if(pPane->GetIconID() == iconID)
	g2pvt_refresh_pane_tabs(pPane);
    }
  }
}

void CMainFrame::RefreshChildIcon(CWnd *pChild, int native_icon)
{
  g2pvt_set_window_icon_internal(pChild->GetSafeHwnd(), native_icon);

  CXTPTabManagerItem* pItem;

  if(IsTabbedMDI() && (pItem = m_MTIClientWnd.FindItem(pChild->GetSafeHwnd())))
    m_MTIClientWnd.InvalidateRect(pItem->GetRect());
}




/*
 * Panes
 */

#define PANE_EVENT_CLOSED 4
#define dockFloat ((XTPDockingPaneDirection)1234)
#define dockWithin ((XTPDockingPaneDirection)4321)

// Keep in sync with LISP function GET-DOCK-CODE.
static XTPDockingPaneDirection g2pvt_get_dock_code(int k)
{
  switch(k&0xF) {
   case DOCK_TOP: return xtpPaneDockTop;
   case DOCK_BOTTOM: return xtpPaneDockBottom;
   case DOCK_LEFT: return xtpPaneDockLeft;
   case DOCK_RIGHT: return xtpPaneDockRight;
   case DOCK_FLOAT: return dockFloat;
   case DOCK_WITHIN: return dockWithin;
   default: return xtpPaneDockLeft;
  }
}

static int g2pvt_dock_status(XTPDockingPaneDirection dir)
{
  switch(dir) {
   case xtpPaneDockLeft:   return STATUS_DOCKED_LEFT;
   case xtpPaneDockRight:  return STATUS_DOCKED_RIGHT;
   case xtpPaneDockTop:    return STATUS_DOCKED_TOP;
   case xtpPaneDockBottom: return STATUS_DOCKED_BOTTOM;
  }
  return STATUS_DOCKED;
}

// Note that this gets the current client rect, rather than relying on the cx,
// cy passed into OnSize(), since those may be out of date due to recursive
// calls to OnSize().
void g2pvt_view_sized(CWnd *pWnd, int handle, int nType /*= STATUS_UNKNOWN*/)
{
  if(handle <= 0) return;
  CRect r;
  pWnd->GetClientRect(r);
  g2pvt_send_window_sized(pWnd->m_hWnd, handle, STATUS_UNKNOWN, r.Width(), r.Height());
}

// Find docking pane containing child with handle.
CXTPDockingPane* g2pvt_find_pane(int handle)
{
  if(handle <= 0) return NULL;

  CMainFrame *pFrame = GetMainWnd();
  CXTPDockingPane* pPane = pFrame->GetDockingPaneManager()->FindPane(handle);
  return (pPane && pPane->IsValid()) ? pPane : NULL;
}

// A pane icon appears only in its tab.
void g2pvt_refresh_pane_tabs(CXTPDockingPane *pPane)
{
  CXTPDockingPaneBase* pContainer = pPane->GetContainer();
  if(pContainer && pContainer->GetType() == xtpPaneTypeTabbedContainer)
    ((CXTPDockingPaneTabbedContainer*)pContainer)->UpdateTabs();
}

// If neighbor is closed or (auto)hidden, then we can't use it (Codejock aborts
// if we try).
static CXTPDockingPane *check_neighbor(CXTPDockingPane *pNeighbor)
{
  if(pNeighbor && (pNeighbor->IsClosed() || pNeighbor->IsHidden())) {
    pNeighbor = NULL;
    // FIXME: This warning really wants to be sent back to G2 for the logbook.
    g2ext_write_string_to_console("Warning: Cannot dock pane to hidden neighbor.\n");
  }
  return pNeighbor;
}

// Create a pane at given position. Copied from the XTP DynamicPanes sample.
CXTPDockingPane* CMainFrame::CreatePane(int handle, CString strTitle, 
					int x, int y, int width, int height,
					int dock, int neighborID, int icon,
					int *pStatus, CSize minSize)
{
  CXTPDockingPane* pPane;
  XTPDockingPaneDirection direction = g2pvt_get_dock_code(dock);
  CXTPDockingPane *pNeighbor = g2pvt_find_pane(neighborID);
  BOOL pseudoDock = (direction == dockFloat || direction == dockWithin);
  CRect rect(x, y, x+width, y+height);

  pNeighbor = check_neighbor(pNeighbor);

  pPane = m_paneManager.CreatePane(handle, rect,
				   pseudoDock ? xtpPaneDockLeft : direction,
				   pseudoDock ? NULL : pNeighbor);
  pPane->SetMinTrackSize(minSize);
  pPane->SetTitle(strTitle);
  pPane->SetPaneData(0);	// No longer used, but might as well initialize it.
  if(icon>0)
    SetPaneIcon(pPane, icon);

  *pStatus = STATUS_DOCKED;
  switch(direction) {
   case dockWithin:
     if(pNeighbor) {
       m_paneManager.AttachPane(pPane,pNeighbor);
       *pStatus = STATUS_ATTACHED;
     }
     break;
   case dockFloat:
     // ClientToWindowEx doesn't seem to handle tool windows.
     rect.InflateRect(0, 0, 
 		      2*GetSystemMetrics(SM_CXFRAME),
 		      2*GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYSMCAPTION));
     m_paneManager.FloatPane(pPane, rect);
     *pStatus = STATUS_FLOATED;
     break;
   default:
     *pStatus = g2pvt_dock_status(direction);
     break;
  }

  return pPane;
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
  CXTPDockingPaneManager *pMgr = GetDockingPaneManager();
  CXTPDockingPane *pPane = (CXTPDockingPane*)lParam;
  CXTPDockingPaneBase *pContainer;
  XTP_DOCKINGPANE_ACTION *pAction;
  CWnd *pChild = NULL;
  HWND hwnd;
  int handle;

  switch(wParam) {
   case XTP_DPN_ACTION:
     pAction = (XTP_DOCKINGPANE_ACTION*)lParam;
     pContainer = pAction->pDockContainer;
     pPane = pAction->pPane;
     pChild = pPane->GetChild();
     hwnd = pChild->GetSafeHwnd();
     handle = pPane->GetID();

     switch(pAction->action) {
      case xtpPaneActionMoved:	// Only for floating panes. New action added by Gensym to XTP sources.
	if(handle > 0) {
	  RECT r;
	  pChild->GetWindowRect(&r);
	  g2pvt_send_window_moved(hwnd, handle, r.left, r.top);
	}
	break;

      case xtpPaneActionDragging:
	if(pPane->GetOptions() & gensymPaneNoDraggable)
	  pAction->bCancel = TRUE;
	break;

      case xtpPaneActionFloated:
	if(handle > 0)
	  g2pvt_send_window_status(hwnd, handle, STATUS_FLOATED);
	break;

      case xtpPaneActionDocked:
	if(handle > 0)
	  g2pvt_send_window_status(hwnd, handle, g2pvt_dock_status(pMgr->GetPaneDirection(pPane)));
	break;

      case xtpPaneActionAttached:
	if(handle > 0)
	  g2pvt_send_window_status(hwnd, handle, STATUS_ATTACHED);
	break;

      case xtpPaneActionPinned:
	if(handle > 0)
	  g2pvt_send_window_status(hwnd, handle, STATUS_PINNED);
	break;

      case xtpPaneActionExpanded:
	if(handle > 0)
	  g2pvt_send_window_status(hwnd, handle, STATUS_EXPANDED);
	break;

      case xtpPaneActionCollapsed:
	if(handle > 0)
	  g2pvt_send_window_status(hwnd, handle, STATUS_COLLAPSED);
	break;

      case xtpPaneActionClosed:
	if(pPane->GetOptions() & gensymPaneHideOnClose)	{
	  if(handle > 0)
	    g2pvt_send_window_status(hwnd, handle, STATUS_HIDDEN);
	} else {
	  // Closing a pane is really just hiding it -- the child window is not
	  // destroyed, although the pane window is.  For G2 users, we probably want
	  // the close box on panes to do the same thing as the close box on MDI
	  // child workspace views -- the view is deleted, rather than hidden. So we
	  // destroy the pane and the child window here. -fmw, 3/9/05
	  pPane->Detach();	         // Detach child window from the pane.
	  pChild->PostMessage(WM_CLOSE); // Close the child window
	  pMgr->DestroyPane(pPane);	 // And destroy the pane.
	}
	break;
     }
     return TRUE;
  }
  return FALSE;
}

LRESULT CMainFrame::OnListBarNotify(WPARAM wParam, LPARAM lParam)
{
  if(wParam == XTP_SBN_SELECTION_CHANGING) {
    CXTPShortcutBarItem* pFolder = (CXTPShortcutBarItem *)lParam;
    pFolder->GetShortcutBar()->SendMessage(XTPWM_SHORTCUTBAR_NOTIFY, wParam, lParam); // Reflect
  }
  return 0;
}

LRESULT CMainFrame::OnPropertyGridNotify(WPARAM wParam, LPARAM lParam)
{
  G2PropGrid *pPG = NULL;
  CXTPPropertyGridItem *pItem = NULL;
  CXTPPropertyGridInplaceEdit* pEdit = NULL;
  CXTPPropertyGridInplaceButton *pButton = NULL;

  switch(wParam) {
   case XTP_PGN_SELECTION_CHANGED:
   case XTP_PGN_ITEMVALUE_CHANGED:
   case XTP_PGN_DBLCLICK:
   case XTP_PGN_ITEMEXPANDCHANGED:
   case XTP_PGN_RCLICK:
     pItem = (CXTPPropertyGridItem*)lParam;
     break;
    
   case XTP_PGN_INPLACEBUTTONDOWN:
     pButton = DYNAMIC_DOWNCAST(CXTPPropertyGridInplaceButton, (CWnd*)lParam);
     pItem = pButton ? pButton->GetItem() : NULL;
     break;

   case XTP_PGN_EDIT_CHANGED:
     pEdit = DYNAMIC_DOWNCAST(CXTPPropertyGridInplaceEdit, (CWnd*)lParam);
     pItem = pEdit ? pEdit->GetItem() : NULL;
     break;

   case XTP_PGN_SORTORDER_CHANGED:
     pPG = FIND_WND(lParam,G2PropGrid);
     break;
  }

  if(pItem)
    pPG = DYNAMIC_DOWNCAST(G2PropGrid,pItem->GetGrid()->GetParent());

  if(pPG)
    return pPG->OnPropertyGridNotify(wParam, pItem);
  else
    return FALSE;
}

static void SetPaneOption(CXTPDockingPane *pPane, enum XTPDockingPaneOptions option, BOOL on)
{
  UINT options = pPane->GetOptions();

  if(on)
    pPane->SetOptions(options | option);
  else
    pPane->SetOptions(options & ~option);
}




/*
 * Generic Pane Management
 */

long g2ext_manage_pane(long opcode, long handle, 
		       long x, long y, long width, long height,
		       LPWSTR string)
{
  CMainFrame *pFrame = GetMainWnd();
  CXTPDockingPaneManager *pMgr = pFrame->GetDockingPaneManager();
  CXTPDockingPane *pPane = g2pvt_find_pane(handle);
  CWnd *pChild = pPane ? pPane->GetChild() : NULL;

  if(!pPane) return 0;

  switch(opcode) {
   case PANE_HIDE:		// NOTE: G2 calls this state=AUTOHIDDEN
     pPane->Hide();		// Autohide if docked, else ?
     return 1;

   case PANE_SHOW:
     pMgr->ShowPane(pPane);	// Unautohides, but does it work on closed pane? Yes.
     return 1;

   case PANE_SELECT:
     pMgr->ShowPane(pPane);
     pPane->Select();
     pPane->SetFocus();
     return 1;

   case PANE_FLOAT:
     if(!pPane->IsFloating()) {
       if(pPane->IsClosed())
         pMgr->ShowPane(pPane);
       pMgr->ToggleDocking(pPane);
     }
     // The supplied dimensions are currently bogus, either all 0 or all
     // DEFAULT_DIM.  pMgr->FloatPane(pPane, CRect(x,y,x+width,y+height));
     return 1;

   case PANE_FILL:
     pMgr->HideClient(x==1);	// NOTE: Somewhat unpredictable which pane fills it.
     return 1;

   case PANE_DOCK:
     {
       XTPDockingPaneDirection direction = g2pvt_get_dock_code(x);
       CXTPDockingPane *pNeighbor = g2pvt_find_pane(y);

       if(pPane->IsClosed())
	 pMgr->ShowPane(pPane);

       // Check for neighbor hidden or autohidden!
       pNeighbor = check_neighbor(pNeighbor);
       if(direction == dockWithin) {
	 if(pNeighbor)
	   pMgr->AttachPane(pPane,pNeighbor);
       } else {
	 pMgr->DockPane(pPane, direction, pNeighbor);
       }
     }
     return 1;

   case PANE_REDOCK: 
     if(pPane->IsFloating())
       pMgr->ToggleDocking(pPane);
     return 1;

   case PANE_TOGGLE_DOCKING:
     if(pPane->IsClosed())
       pMgr->ShowPane(pPane);
     pMgr->ToggleDocking(pPane);
     return 1;

   case PANE_SET_TITLE:
     pPane->SetTitle(string);
     g2pvt_refresh_pane_tabs(pPane);
     return 1;

   case PANE_SET_ICON:
     pFrame->SetPaneIcon(pPane, x);
     return 1;

   case PANE_SET_CLOSEABLE:
     SetPaneOption(pPane, xtpPaneNoCloseable, x==0);
     pPane->SetTitle(pPane->GetTitle()); // Needed to update screen.
     break;
	 
   case PANE_SET_AUTOHIDEABLE:
     SetPaneOption(pPane, xtpPaneNoHideable, x==0);
     pPane->SetTitle(pPane->GetTitle()); // Needed to update screen.
     break;

   case PANE_SET_FLOATABLE:
     if(!(pPane->IsFloating() && x)) // Don't set a floating pane nonfloatable!
       SetPaneOption(pPane, xtpPaneNoFloatable, x==0);
    break;

   case PANE_SET_DRAGGABLE:
     if(!pPane->IsFloating())	// Doesn't apply to a floating pane.
       SetPaneOption(pPane, gensymPaneNoDraggable, x==0);
    break;

   case PANE_SET_VISIBLE_CAPTION:
     SetPaneOption(pPane, xtpPaneNoCaption, x==0);
     break;

   // TODO: xtpPaneHasMenuButton

   case PANE_SET_HIDE_ON_CLOSE:
     SetPaneOption(pPane, gensymPaneHideOnClose, x!=0);
     break;

   case PANE_CLOSE:		// NOTE: G2 calls this state=HIDDEN
     pPane->Close();
     return 1;

   case PANE_DESTROY:
     pPane->Detach();
     pMgr->DestroyPane(pPane);
     if(pChild)
       pChild->DestroyWindow();
     return 1;
  }
  return 0;
}




/*
 * ToolBars
 */

// Dock pBar on given side of pNeighbor.
void CMainFrame::DockToolBar(CXTPToolBar* pBar, XTPBarPosition side, CXTPToolBar* pNeighbor)
{
  RecalcLayout(TRUE);		// Taken from Codejock example. Needed?
  CXTPWindowRect r(pNeighbor);

  switch(side) {
   case xtpBarLeft:
     r.OffsetRect(-r.Width(), 0); // FIXME: Need pBar's width, but not yet known.
     break;
   case xtpBarTop: 
     r.OffsetRect(0, -r.Height()); // Ditto.
     break;
   case xtpBarRight:
     r.OffsetRect(r.Width(), 0);
     break;
   case xtpBarBottom:
     r.OffsetRect(0, r.Height());
     break;
  }
    
  if(pNeighbor->GetDockBar())
    GetCommandBars()->DockCommandBar(pBar, r, pNeighbor->GetDockBar());
  else {
    pBar->SetPosition(xtpBarFloating);
    pBar->SetWindowPos(NULL, max(r.left,0), max(r.top,0), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  }
}




/*
 * Tabbed MDI Mode
 */

#define MDI_NORMAL_MODE 1	// Keep in sync with lisp/native-tw.lisp
#define MDI_TABBED_MODE 2
#define MDI_GROUPED_MODE 3
#define MDI_SHOW_ICONS 4
#define MDI_TAB_POSITION 5
#define MDI_TAB_LAYOUT 6

long g2ext_tabbed_mdi_mode(long opcode, long arg)
{
  return GetMainWnd()->ManageMDIMode(opcode,arg);
}

BOOL g2pvt_tabbed_mdi_mode_p()
{
  return GetMainWnd()->IsTabbedMDI();
}

void g2pvt_set_window_closeable(HWND hwnd, BOOL torf)
{
  GetMainWnd()->SetWindowCloseable(CWnd::FromHandle(hwnd), torf);
}

void g2pvt_process_window_style(CWnd *pWnd, DWORD style)
{
  CMDIChildWnd *pMDI = DYNAMIC_DOWNCAST(CMDIChildWnd,pWnd);

  if(GetMainWnd()->IsTabbedMDI()) {
    if(style&WS_VISIBLE)
      pWnd->ShowWindow(SW_NORMAL);

  } else {
    DWORD mask = WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
    pWnd->ModifyStyle(~style & mask, style & mask);

    if(style & WS_MINIMIZE)
      pWnd->ShowWindow(SW_MINIMIZE);

    else if(style & WS_MAXIMIZE)
      if(pMDI)
	pMDI->MDIMaximize();
      else
	pWnd->ShowWindow(SW_SHOWMAXIMIZED);
  }
}

int CMainFrame::ManageMDIMode(int opcode, int arg)
{
  switch(opcode) {
   case MDI_NORMAL_MODE:
     if(!IsTabbedMDI())
       return 0;
     m_MTIClientWnd.Detach();
     CWnd::FromHandle(m_hWndMDIClient)->Invalidate();
     break;

   case MDI_TABBED_MODE:
   case MDI_GROUPED_MODE:
     if(IsTabbedMDI())
       return 0;
     m_MTIClientWnd.Attach(this, opcode==MDI_GROUPED_MODE);
     m_MTIClientWnd.EnableToolTips();
     break;

   case MDI_SHOW_ICONS:
     m_MTIClientWnd.GetPaintManager()->m_bShowIcons = (arg != 0);
     m_MTIClientWnd.Refresh();
     break;

   case MDI_TAB_POSITION:
     switch(arg) {
      case LK_LEFT:
	m_MTIClientWnd.GetPaintManager()->SetPosition(xtpTabPositionLeft);
	break;
      case LK_TOP:
	m_MTIClientWnd.GetPaintManager()->SetPosition(xtpTabPositionTop);
	break;
      case LK_RIGHT:
	m_MTIClientWnd.GetPaintManager()->SetPosition(xtpTabPositionRight);
	break;
      case LK_BOTTOM:
	m_MTIClientWnd.GetPaintManager()->SetPosition(xtpTabPositionBottom);
	break;
     }
     m_MTIClientWnd.Refresh();
     break;

   case MDI_TAB_LAYOUT:
     switch(arg) {
      case LK_AUTOMATIC:
	m_MTIClientWnd.GetPaintManager()->SetLayout(xtpTabLayoutAutoSize);
	break;
      case LK_SIZE_TO_FIT:
	m_MTIClientWnd.GetPaintManager()->SetLayout(xtpTabLayoutSizeToFit);
	break;
      case LK_FIXED:
	m_MTIClientWnd.GetPaintManager()->SetLayout(xtpTabLayoutFixed);
	break;
      case LK_COMPRESSED:
	m_MTIClientWnd.GetPaintManager()->SetLayout(xtpTabLayoutCompressed);
	break;
     }
     m_MTIClientWnd.Refresh();	
     break;

   default:
     return -1;
  }
  return 1;
}

// See CXTPTabClientWnd::CalcWindowRect
BOOL CMainFrame::IsBogusResize(HWND hwnd, int cx, int cy)
{
  CXTPTabManagerItem* pItem;
  return IsTabbedMDI() && (cx==0) && (cy==0) && 
    (pItem = m_MTIClientWnd.FindItem(hwnd)) &&
    !pItem->IsSelected();
}

LRESULT CMainFrame::OnNewTabItem(WPARAM wParam, LPARAM /*lParam*/)
{
  CXTPTabManagerItem* pItem = (CXTPTabManagerItem*)wParam;
  CWnd *pWnd = FromHandle(pItem->GetHandle());

  if(pWnd) {
    pWnd->ModifyStyle(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 0);
    pWnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);

    // This resize to 0x0, followed immediately by another (final) resize,
    // confuses G2. Hopefully we'll fix this right in 8.3, but for possible
    // backproping to 8.2, we have this kludegy fix to simply not notify G2 in
    // this case. -fmw, 5/19/06

    // The resize was originally copied from CXTPTabClientWnd::OnMDICreate() and
    // definitely confuses things. If this new tab is due to a new window, then
    // OnMDICreate() has already taken care of it.  If this new tab is due to
    // switching modes, then the reshape does not appear to be needed. -fmw, 4/18/07

//     G2_reshape_in_progress++;
//     pWnd->MoveWindow(0, 0, 0, 0);			
//     G2_reshape_in_progress--;

    pItem->SetClosable(g2pvt_syscommand_enabled_p(pWnd->GetSafeHwnd(), SC_CLOSE));
  }
  return 0;
}

void CMainFrame::SetWindowCloseable(CWnd *pWnd, BOOL torf)
{
  CMenu *pMenu = pWnd->GetSystemMenu(FALSE);
  if (pMenu) // GENSYMCID-920: TWng aborted (TWNG crash when the g2-ui-modify-view procedure is used)
    pMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | (torf ? MF_ENABLED : MF_GRAYED));

  if(!IsTabbedMDI())
    return;

  CXTPTabManagerItem* pItem = m_MTIClientWnd.FindItem(pWnd->GetSafeHwnd());
  if(!pItem)
    return;

  pItem->SetClosable(torf);
  m_MTIClientWnd.SetFlags(m_MTIClientWnd.GetFlags());	// Forces display update.
}

LRESULT CMainFrame::OnTabClick(WPARAM wParam, LPARAM lParam)
{
  CPoint point = CPoint((DWORD)lParam);
  CXTPTabManagerItem* pItem =  m_MTIClientWnd.HitTest(point);
  CWnd *pWnd;

  // This restores what seems to have been CXTPTabClientWnd's behavior in
  // 8.2. And it appears to fix HQ-5495949.
  if ((wParam == WM_LBUTTONDOWN) && pItem &&
      (pItem->GetHandle() != MDIGetActive()->GetSafeHwnd()) &&
      (pWnd = CWnd::FromHandle(pItem->GetHandle())))
    MDIActivate(pWnd);
  return FALSE;
}
