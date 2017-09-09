// CEditorWnd -- Container for a G2Editor and G2Output window

#pragma once
#define EVENT_ID_TOOLBAR 9600

class G2Output : public CScintillaWnd
{
  DECLARE_DYNCREATE(G2Output)
public:
  G2Output();
  virtual ~G2Output();
  G2Editor *m_pEditor;
  virtual void HotSpotClick(LPCSTR str, int style, int pos);
  virtual void SetupEditor();
  virtual void SetupStyles();
protected:
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnSetFocus(CWnd* pOldWnd);
};
struct CToolBarStructure{
	CString strName;
	UINT iIDG2;
};

// Misnomer: not a CFrameWnd
class CEditorWnd : public CXTSplitterWnd
{
  DECLARE_DYNCREATE(CEditorWnd)
public:
  CEditorWnd(int handle = 0);
  virtual ~CEditorWnd();
  int m_handle;

public:
  G2Editor* m_pEditor;
  G2Output* m_pOutput;
  CCreateContext *m_pContext; //Added by SoftServe
  CWnd *m_pParentDialog; //Added by SoftServe
private:
  int m_lastHeight;
  unsigned long menu_index;
  CXTPCommandBar* m_pToolBar; //Added by SoftServe
protected:
  DECLARE_MESSAGE_MAP()

public:				// Automatically generated declarations
  BOOL Create(CWnd *pParent);
  void PostNcDestroy();
  CXTPCommandBars* GetCommandBars();
  void InitToolBar();
  void InitAdditioanlToolBar(UINT iIDG2,LPWSTR strName);
  void FinalizeAndShow();
  void AdjustExitShortcut();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg LRESULT OnQueryClose(WPARAM,LPARAM);
  afx_msg void OnZoom(NMHDR *pNotifyStruct, LRESULT* result);
  BOOL IsSingleLineMode();
  CRect& GetInitialShape();
  CXTPToolBar* GetToolBar();
  afx_msg void OnToggleToolBar();
  afx_msg void OnUpdateToggleToolBar(CCmdUI* pCmdUI);
  void ShowToolBar(BOOL visible);
  afx_msg void OnEditHelp();
  afx_msg LPARAM OnParentIsMoving(WPARAM, LPARAM);
  afx_msg LPARAM OnParentClosing(WPARAM,LPARAM);
  afx_msg BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
 // Added by SoftServe
  void ProcessingCommandClick(UINT iID);
  void OnCommandRange(unsigned int iID);
  void OnCommandRangeUI(CCmdUI* pCmdUI);

protected:
  UINT GetEventID();
protected:
  CMap<UINT,UINT,CToolBarStructure,CToolBarStructure> m_MapData;
  UINT iEventID;
 // End of SoftServe changes
};


// Template class for a G2-compliant XTP FrameWnd (with toolbars) which manages
// a single child window. NOTE: If the child was a CView, MFC would take care of
// much of this automatically.

template <class TBase>
class G2FrameWndBase : public CXTPFrameWndBase<TBase>
{
public:
  CWnd *GetChild() {
    return GetDlgItem(AFX_IDW_PANE_FIRST); // For a SplitterWnd child, at least.
  }

  void OnSetFocus(CWnd* pOldWnd) {
    if (GetChild())
      GetChild()->SetFocus();
    else
      TBase::OnSetFocus(pOldWnd);
  }

  void OnClose() {
    if(!GetChild() || GetChild()->SendMessage(WM_QUERY_CLOSE))
      TBase::OnClose();
  }

  void OnDestroy() {
    if(GetChild())
      GetChild()->SendMessage(WM_PARENT_IS_CLOSING);
    TBase::OnDestroy();
  }

  LRESULT OnGetCommandBars(WPARAM wParam, LPARAM lParam) {
    if(!GetCommandBars())
      InitCommandBars();
    return (LRESULT) GetCommandBars();
  }

  BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
    if(GetChild() && GetChild()->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
      return TRUE;
    return TBase::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
  }

  LRESULT OnEnterSizeMove(WPARAM, LPARAM) {
    LRESULT rc = Default();
    if(GetChild())
      GetChild()->SendMessage(WM_PARENT_IS_MOVING);
    g2pvt_enter_modal_loop();
    return rc;
  }

  LRESULT OnExitSizeMove(WPARAM, LPARAM) {
    g2pvt_exit_modal_loop();
    return Default();
  }

  LRESULT OnEnterMenuLoop(WPARAM, LPARAM) {
    LRESULT rc = Default();
    g2pvt_enter_modal_loop();
    return rc;
  }

  LRESULT OnExitMenuLoop(WPARAM, LPARAM) {
    g2pvt_exit_modal_loop();
    return Default();
  }

  LRESULT OnModalLoop(WPARAM wParam, LPARAM lParam) {
    if(wParam)
      g2pvt_enter_modal_loop();
    else
      g2pvt_exit_modal_loop();
    return 0;
  }
};

#define DECLARE_G2FRAME_MESSAGE_HANDLERS() \
 ON_WM_SETFOCUS() \
 ON_WM_CLOSE() \
 ON_WM_DESTROY() \
 ON_WM_WINDOWPOSCHANGING() \
 ON_MESSAGE(WM_GETCOMMANDBARS,OnGetCommandBars) \
 ON_MESSAGE(WM_ENTERSIZEMOVE, OnEnterSizeMove) \
 ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove) \
 ON_MESSAGE(WM_ENTERMENULOOP, OnEnterMenuLoop) \
 ON_MESSAGE(WM_EXITMENULOOP, OnExitMenuLoop) \
 ON_MESSAGE(WM_XTP_MODALLOOP, OnModalLoop)


// MDI Child frame with command bars
class CChildFrmEx : public G2FrameWndBase<CMDIChildWnd>
{
  DECLARE_DYNCREATE(CChildFrmEx)
protected:
  DECLARE_MESSAGE_MAP()
};

// Top-level frame with command bars
class CTopFrameEx : public G2FrameWndBase<CFrameWnd>
{
  DECLARE_DYNCREATE(CTopFrameEx)
protected:
  DECLARE_MESSAGE_MAP()
};
