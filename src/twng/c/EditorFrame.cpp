// CEditorWnd -- Container for G2Editor and G2Output panes

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ScintillaWnd.h"
#include "Editor.h"
#include "EditorFrame.h"
#include "ModalEdit.h"
#include "ddrsc.h"

typedef struct
{
  BOOL toolBarVisible;
  enum XTPBarPosition toolBarPos;
  int idealPaneSize;
} FramePrefs;

static FramePrefs framePrefs = {TRUE, xtpBarTop, 200};
static CRect multiLineEditorShape  = CRect(3,  20, 503, 470);
static CRect singleLineEditorShape = CRect(10, 30, 460, 230);

IMPLEMENT_DYNCREATE(CEditorWnd,CXTSplitterWnd)

BEGIN_MESSAGE_MAP(CEditorWnd,CXTSplitterWnd)
 ON_WM_CREATE()
 ON_WM_SETFOCUS()
 ON_WM_SIZE()
 ON_NOTIFY(SCN_ZOOM,AFX_IDW_PANE_FIRST,OnZoom)
 ON_MESSAGE(WM_QUERY_CLOSE, OnQueryClose)
 ON_MESSAGE(WM_PARENT_IS_CLOSING, OnParentClosing)
 ON_MESSAGE(WM_PARENT_IS_MOVING, OnParentIsMoving)

 ON_COMMAND(ID_TOGGLE_TOOLBAR,OnToggleToolBar)
 ON_UPDATE_COMMAND_UI(ID_TOGGLE_TOOLBAR,OnUpdateToggleToolBar)

 // Added by SoftServe
 ON_COMMAND_RANGE(EVENT_ID_TOOLBAR ,33500,OnCommandRange)   
 ON_UPDATE_COMMAND_UI_RANGE(EVENT_ID_TOOLBAR ,33500,OnCommandRangeUI)
 // End Of SoftServe changes

 ON_COMMAND(ID_EDIT_HELP,OnEditHelp)
END_MESSAGE_MAP()


CEditorWnd::CEditorWnd(int handle) 
{
  m_handle = handle;
  SAVE_WND();
  m_pEditor = NULL;
  m_pOutput = NULL;
  m_pContext = new CCreateContext();
  m_lastHeight = -1;
  menu_index = -1;
  m_pToolBar = NULL;
  iEventID = EVENT_ID_TOOLBAR;
  VTRACE("Construct CEditorWnd [%d] %08x\n", m_handle, this);
}

CEditorWnd::~CEditorWnd()
{
  m_MapData.RemoveAll();
  VTRACE("Destruct CEditorWnd [%d] %08x\n", m_handle, this);
}

UINT CEditorWnd::GetEventID(){
	return iEventID++;
};
BOOL CEditorWnd::Create(CWnd *pParent)
{
	
  if(!CreateStatic(pParent, 2, 1, WS_CHILD, AFX_IDW_PANE_FIRST))
    return FALSE;
  
  m_pParentDialog = pParent;
  
  CreateView(0, 0, RUNTIME_CLASS(G2Editor), CSize(0,0), m_pContext);
  CreateView(1, 0, RUNTIME_CLASS(G2Output), CSize(0,0), m_pContext);

  m_pEditor = (G2Editor*) GetPane(0,0);
  m_pEditor->SetHandle(m_handle);	                     // FIXME: kludge

  m_pOutput = (G2Output*) GetPane(1,0);
  m_pOutput->SetOwnerHandle(m_handle);
  m_pOutput->m_pEditor = m_pEditor;

  return TRUE;
}
void CEditorWnd::OnCommandRange(unsigned int iID){
	ProcessingCommandClick(iID);
}
void CEditorWnd::OnCommandRangeUI(CCmdUI* pCmdUI){
	 pCmdUI->Enable(g2pvt_nms_get_id_enabled(pCmdUI->m_nID));
};
void CEditorWnd::PostNcDestroy()
{
  CXTSplitterWnd::PostNcDestroy();
  delete this;
}

CXTPCommandBars* CEditorWnd::GetCommandBars()
{
  return (CXTPCommandBars*) GetParentFrame()->SendMessage(WM_GETCOMMANDBARS);
}

void CEditorWnd::InitToolBar()
{
  CXTPCommandBars* pCommandBars = GetCommandBars();
  if(!pCommandBars)
    return;

  pCommandBars->GetShortcutManager()->SetAccelerators(IDR_EDITOR);
  pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;
  pCommandBars->GetCommandBarsOptions()->bToolBarScreenTips = TRUE;
  pCommandBars->GetCommandBarsOptions()->bShowExpandButtonAlways = FALSE;

  CXTPToolBar* pToolBar = (CXTPToolBar*)pCommandBars->Add(_T("Editor"), framePrefs.toolBarPos);
  if(pToolBar && pToolBar->LoadToolBar(IDR_EDITOR))
    pToolBar->SetVisible(framePrefs.toolBarVisible);
}
//Added by SoftServe
void CEditorWnd::InitAdditioanlToolBar(UINT iIDG2,LPWSTR strName){
  
  if(NULL == m_pToolBar){
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(!pCommandBars)
		return;

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_EDITOR);
	pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;
	pCommandBars->GetCommandBarsOptions()->bToolBarScreenTips = TRUE;
	pCommandBars->GetCommandBarsOptions()->bShowExpandButtonAlways = FALSE;

	m_pToolBar = (CXTPToolBar*)pCommandBars->Add(_T("Editor"), framePrefs.toolBarPos);
	if(m_pToolBar){
		m_pToolBar->SetVisible(framePrefs.toolBarVisible);
	}
  }
	menu_index = SavePtr(m_pToolBar);
	CToolBarStructure tbStr;
	tbStr.iIDG2 = iIDG2;
	tbStr.strName = strName;
	//CString strEventName = strName + CString(iIDG2);
	UINT iID = GetEventID();//RegisterWindowMessage(strEventName);
	if(0 != iID){
		m_MapData[iID] = tbStr;
		g2ext_nms_append_menu(menu_index ,0,iID,-1,0,strName,-1,-1);
	}
};
void CEditorWnd::ProcessingCommandClick(UINT iID){
	CToolBarStructure tbStr;
	BOOL bRes = m_MapData.Lookup(iID,tbStr);
	if(bRes){
		m_pEditor->FireEvent(EDITOR_CUSTOM_TOOLBAR, tbStr.iIDG2);
	}
	
};
//End of SoftServe changes

// Once all the options have been selected, finishing setting up the splitter
// bar, etc, and show the frame.
void CEditorWnd::FinalizeAndShow()
{
  InitToolBar();
  RecalcLayout();

  CRect& r = GetInitialShape();
  GetParentFrame()->MoveWindow(GetInitialShape());

  m_pEditor->RestorePrefs();
  m_pEditor->SetupEditor();	// FIXME: redoing these
  m_pEditor->SetupStyles();
  m_pOutput->Sc(SCI_SETZOOM, m_pEditor->m_zoom);

  // Adjust editor height to minimum needed if single line mode
  int editorHeight = framePrefs.idealPaneSize;
  if(IsSingleLineMode()) {
    m_pEditor->SetLineNumbersVisible(FALSE);
    editorHeight = m_pEditor->Sc(SCI_TEXTHEIGHT) * max(1,m_pEditor->Sc(SCI_GETLINECOUNT));
  }

  SetRowInfo(0, editorHeight, 0);
  SetRowInfo(1, framePrefs.idealPaneSize, 0);
  RecalcLayout();

  AdjustExitShortcut();

  m_pEditor->ShowWindow(SW_SHOW);
  m_pOutput->ShowWindow(SW_SHOW);
  ShowWindow(SW_SHOW);
}

// Adjust the shortcut key for Save-And-Exit if in single line mode.
void CEditorWnd::AdjustExitShortcut()
{
  CXTPControl *pControl;

  if(IsSingleLineMode() && GetToolBar() &&
     (pControl = GetToolBar()->GetControls()->FindControl(ID_EDIT_SAVE_AND_EXIT)))
    pControl->SetShortcutText(_T("Enter"));
}

// Fake out the splitter to keep height of second pane constant during resize.
void CEditorWnd::OnSize(UINT nType, int cx, int cy)
{
  if(GetMainWnd()->IsBogusResize(GetParentFrame()->GetSafeHwnd(), cx, cy)) {
    CXTSplitterWnd::OnSize(nType, cx, cy);
    return;
  }

  // If multiline mode, keep editor height constant on resize.
  if(IsWindowVisible() && m_pEditor && !IsSingleLineMode() &&
     nType != SIZE_MINIMIZED && m_lastHeight > 0) {
    int idealSize, minSize;
    GetRowInfo(0, idealSize, minSize);
    idealSize = max(minSize, idealSize + cy - m_lastHeight);
    SetRowInfo(0, idealSize, minSize);
  }

  if (nType != SIZE_MINIMIZED)
    m_lastHeight = cy;

  CXTSplitterWnd::OnSize(nType, cx, cy);
}

void CEditorWnd::OnSetFocus(CWnd* pOldWnd)
{
  if (m_pEditor == NULL) {
    CXTSplitterWnd::OnSetFocus(pOldWnd);
  } else {
    m_pEditor->SetFocus();
    g2pvt_send_window_activated(m_hWnd, m_handle);
  }
}

LRESULT CEditorWnd::OnQueryClose(WPARAM,LPARAM)
{
  if(m_pEditor)
    return m_pEditor->QueryClose();
  else
    return TRUE;
}

void CEditorWnd::OnZoom(NMHDR *pNotifyStruct, LRESULT* result)
{
  if(m_pOutput && m_pEditor)
    m_pOutput->Sc(SCI_SETZOOM,m_pEditor->m_zoom);
}

BOOL CEditorWnd::IsSingleLineMode()
{
  return (m_pEditor && m_pEditor->m_singleLineMode);
}

CRect& CEditorWnd::GetInitialShape()
{
  return IsSingleLineMode() ? singleLineEditorShape : multiLineEditorShape;
}

CXTPToolBar* CEditorWnd::GetToolBar()
{
  return GetCommandBars()->GetToolBar(IDR_EDITOR);
}

void CEditorWnd::OnToggleToolBar()
{
  if(GetToolBar())
    GetToolBar()->SetVisible(!GetToolBar()->IsVisible());
}

void CEditorWnd::OnUpdateToggleToolBar(CCmdUI* pCmdUI)
{
  if(GetToolBar()) {
    pCmdUI->Enable(TRUE);
    pCmdUI->SetCheck(GetToolBar()->IsVisible());
  } else {
    pCmdUI->Enable(FALSE);
  }
}

void CEditorWnd::ShowToolBar(BOOL visible)
{
  if(GetToolBar())
    GetToolBar()->SetVisible(visible);
}

void CEditorWnd::OnEditHelp()
{
  MessageBox(L"Help", L"Editor Help", MB_OK);
}

LPARAM CEditorWnd::OnParentIsMoving(WPARAM, LPARAM)
{
  if(m_pEditor)
    m_pEditor->SendMessage(WM_PARENT_IS_MOVING);
  return 0;
}

LPARAM CEditorWnd::OnParentClosing(WPARAM,LPARAM)
{
  if(GetToolBar()) {
    framePrefs.toolBarVisible = GetToolBar()->IsVisible();
    framePrefs.toolBarPos = GetToolBar()->GetPosition();
  }

  if(!IsSingleLineMode()) {
    int idealSize, minSize;
    GetRowInfo(0, idealSize, minSize);
    framePrefs.idealPaneSize = idealSize;
  }

  CFrameWnd *pFrame = GetParentFrame();
  CRect& r = GetInitialShape();
  pFrame->GetWindowRect(r);
  if(pFrame->GetParent())
    pFrame->GetParent()->ScreenToClient(r);

  if(m_pEditor)
    m_pEditor->SavePrefs();
  return 0;
}

// Route command messages thru the editor window.
BOOL CEditorWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
  if(m_pEditor && m_pEditor->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;
  return CXTSplitterWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


/*
 * Output Pane (internal helper class)
 */

IMPLEMENT_DYNCREATE(G2Output,CScintillaWnd)

BEGIN_MESSAGE_MAP(G2Output,CScintillaWnd)
  ON_WM_SETFOCUS()
END_MESSAGE_MAP()

G2Output::G2Output()
{
  m_pEditor = NULL;
}

G2Output::~G2Output()
{
}

void G2Output::SetupEditor()	// virtual
{
  m_pEditor = NULL;
  m_lineNumbers = FALSE;
  m_ignore_save_points = 1;
  CScintillaWnd::SetupEditor();
  Sc(SCI_SETUNDOCOLLECTION, FALSE);
  Sc(SCI_EMPTYUNDOBUFFER);
  SetReadOnly(TRUE);
  Sc(SCI_SETCARETWIDTH, 0);
  Sc(SCI_HIDESELECTION, TRUE);
  Sc(SCI_SETMARGINWIDTHN, 0, 0);
  Sc(SCI_SETMARGINWIDTHN, 1, 0);
  Sc(SCI_SETMARGINWIDTHN, 2, 0);
  Sc(SCI_SETMARGINLEFT, 0, 5);
}

void G2Output::SetupStyles()	// virtual
{
  CScintillaWnd::SetupStyles();
  Sc(SCI_STYLESETHOTSPOT, G2S_CATEGORY, TRUE);
  Sc(SCI_STYLESETHOTSPOT, G2S_COMPLETION, TRUE);

  Sc(SCI_STYLESETITALIC, G2S_CATEGORY, TRUE);
  Sc(SCI_STYLESETBOLD, G2S_COMPLETION, TRUE);

  Sc(SCI_STYLESETUNDERLINE, G2S_CATEGORY, TRUE);
  Sc(SCI_STYLESETUNDERLINE, G2S_COMPLETION, TRUE);
}

void G2Output::OnSetFocus(CWnd* pOldWnd)
{
  if(m_pEditor)
    m_pEditor->SetFocus();
  else
    Default();
}

void G2Output::HotSpotClick(LPCSTR str, int style, int pos) // virtual
{
  LPWSTR wstr = g2pvt_to_gensym_unicode(str, -1, NULL);
  FireEvent(EDITOR_HOTSPOT_CLICKED, caret_from_pos(pos), wstr, style);
  free(wstr);
}


/*
 * Frame Windows with ToolBars
 */

static CFrameWnd* CreateFrameWnd( LPWSTR title, BOOL topLevel, BOOL toolBars)
{
  CFrameWnd *pFrame;
  DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
  if(topLevel) {
    if(toolBars) {
      CTopFrameEx *pTop = new CTopFrameEx();
      pTop->Create(NULL, title, style);
      pFrame = pTop;
    } else {
      CFrameWnd *pTop = new CFrameWnd();
      pTop->Create(NULL, title, style);
      pFrame = pTop;
    }
  } else {
    if(toolBars) {
      CChildFrmEx *pMdi = new CChildFrmEx();
      pMdi->Create(NULL, title, style | WS_CHILD);
      pFrame = pMdi;
    } else {
      CChildFrm *pMdi = new CChildFrm();
      pMdi->Create(NULL, title, style | WS_CHILD);
      pFrame = pMdi;
    }
  }
  pFrame->SetIcon(theApp.LoadIcon(L"App"), FALSE); // TODO: hack
  return pFrame;
}

IMPLEMENT_DYNCREATE(CChildFrmEx,CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrmEx,CMDIChildWnd)
 DECLARE_G2FRAME_MESSAGE_HANDLERS()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CTopFrameEx,CFrameWnd)

BEGIN_MESSAGE_MAP(CTopFrameEx,CFrameWnd)
 DECLARE_G2FRAME_MESSAGE_HANDLERS()
END_MESSAGE_MAP()


/*
 * G2 Interface
 */

HWND g2pvt_create_editor(long handle, LPWSTR title, DWORD style, DWORD exStyle, RECT* pRect, BOOL topLevel)
{
  CFrameWnd *pParent = CreateFrameWnd(title, topLevel, TRUE);
  
  CEditorWnd *pEditor = new CEditorWnd(handle);
  pEditor->Create(pParent);
  return pEditor->m_pEditor->GetSafeHwnd();
}
