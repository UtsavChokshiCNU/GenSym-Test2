// Debugger.cpp -- Native G2 debugger dialog based on Scintilla

// This is a modal dialog, just like the classic one in G2, and unlike the
// native editor, NOT an MDI child.  Someday, we want to be more like Visual
// Studio, where the editor stays up all the time in a pane, the buttons are in
// the toolbar, local variables are in their own watch-window, etc.

// TODO: Don't destroy dialog if G2 will be reposting it immediately (eg, while stepping).

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "filedlg.h"		// Resizer
#include "ddrsc.h"		// Resource IDs
#include "ScintillaWnd.h"
#include "Editor.h"
#include "Debugger.h"

void G2DebugEdit::MarginClick(int margin, int pos, int modifiers) // virtual
{
  if(margin == MARGIN_ICONS && modifiers == 0) {
    int zLine = Sc(SCI_LINEFROMPOSITION, pos);
    int opcode = OpcodeToCycleBreakpoint(zLine);
    g2pvt_fire_control_event(GENSYM_DEBUGGER_DIALOG, 0, opcode, zLine+1, 0, 0, NULL);
  }
}



static G2Debugger *g_pDialog = NULL;
CRect G2Debugger::m_lastShape = CRect(0,0,0,0);

BEGIN_MESSAGE_MAP(G2Debugger,CDialog)
  ON_WM_DESTROY()
  ON_COMMAND(IDPAUSE,OnPause)
END_MESSAGE_MAP()

G2Debugger::G2Debugger() : CDialog(IDD_DEBUGGER)
{
  m_sourceStepping = FALSE;
  m_resizer = NULL;
  m_title = NULL;
  m_label = NULL;
  m_proc = NULL;
  m_env = NULL;
  m_line = 0;
  m_flags = 0;
  m_tabWidth = 4;
  m_bkpts = NULL;

}
G2Debugger::~G2Debugger()
{
}

void G2Debugger::DoDataExchange(CDataExchange* pDX) // virtual
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_EDIT, m_edit);
  DDX_Control(pDX, IDC_LIST, m_list);
  DDX_Check(pDX, IDC_CHECK1, m_sourceStepping);
}

void G2Debugger::OnDestroy()
{
  g_pDialog = NULL;
  GetWindowRect(m_lastShape);
  CDialog::OnDestroy();
}

G2Editor* G2Debugger::GetEditor()
{
  return &m_edit;
}

CListCtrl* G2Debugger::GetListCtrl()
{
  return &m_list;
}

LRESULT G2Debugger::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) // virtual
{
  DWORD rc;
  if(g2pvt_resizer_dlgproc(m_resizer, &rc, m_hWnd, message, wParam, lParam))
    return rc;
  return CDialog::WindowProc(message, wParam, lParam);
}

BOOL G2Debugger::OnInitDialog()
{
  CDialog::OnInitDialog();

  SetIcon(theApp.LoadIcon(L"App"), FALSE);

  GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND|MF_GRAYED);

  g_pDialog = this;
  m_resizer = g2pvt_resizer_create(m_hWnd,20);
  g2pvt_resizer_add(m_resizer, IDC_LABEL,  ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_TOP);
  g2pvt_resizer_add(m_resizer, IDC_EDIT,   ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_TOP|ANCHOR_BOTTOM);
  g2pvt_resizer_add(m_resizer, IDC_LIST,   ANCHOR_LEFT|ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(m_resizer, IDOK,       ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(m_resizer, IDPAUSE ,   ANCHOR_RIGHT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(m_resizer, IDCANCEL,   ANCHOR_LEFT|ANCHOR_BOTTOM);
  g2pvt_resizer_add(m_resizer, IDC_CHECK1, ANCHOR_LEFT|ANCHOR_BOTTOM);
  g2pvt_resizer_lock(m_resizer);

  SetWindowText(m_title);

  if(m_lastShape.IsRectEmpty())
    g2pvt_center_window(m_hWnd, AfxGetMainWnd()->GetSafeHwnd());
  else
    MoveWindow(m_lastShape);

  // Initialize label
  GetDlgItem(IDC_LABEL)->SetWindowText(m_label);

  // Initialize editor
  G2Editor *pEdit = GetEditor();
  pEdit->m_autoDelete = FALSE;
  pEdit->m_grammar = Procedure;
  pEdit->m_contextMenuID = 0;
  pEdit->SetupEditor();
  pEdit->SetupStyles();
  pEdit->SetUnicodeText(m_proc);
  pEdit->Sc(SCI_SETYCARETPOLICY, CARET_SLOP|CARET_EVEN, 3);
  pEdit->Sc(SCI_MARKERADD, m_line-1, MK_PC);
  pEdit->Sc(SCI_GOTOLINE, m_line-1, 0);
  pEdit->SetBreakpoints(m_bkpts);
  pEdit->SetReadOnly(TRUE);

  // Initialize listview.
  CListCtrl *pLV = GetListCtrl();
  wchar_t *token;
  int item, subitem, i = 0;

  pLV->SetExtendedStyle(LVS_EX_FULLROWSELECT | pLV->GetExtendedStyle());

  pLV->InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
  pLV->InsertColumn(1, _T("Type"), LVCFMT_LEFT, 100);
  pLV->InsertColumn(2, _T("Value"), LVCFMT_LEFT, 150);

  // Env is a double-nul-terminated sequence of name,type,value, name, ...
  for(token=m_env; *token; token += wcslen(token)+1) {
    item = i/3;
    subitem = i%3;

    // For some reason the default font shows a Unicode line separator as a
    // random Japanese character. Work around that here by replacing with
    // an open box.
    g2pvt_subst_char(0x2423, GENSYM_CODE_FOR_LINEBREAK, token);

    if(subitem == 0)
      pLV->InsertItem(item, token);
    else
      pLV->SetItemText(item, subitem, token);
    i++;
  }
  return TRUE;
}



int G2Debugger::DoModalDebugDialog(LPWSTR title, LPWSTR label, LPWSTR proc, 
				   LPWSTR env, int sourceStepping, int line, int tab_width,
				   unsigned short *bkpts)
{
  g2pvt_initialize_scintilla_library();

  m_title = title;
  m_label = label;
  m_proc = proc;
  m_env = env;
  m_line = line;
  m_sourceStepping = sourceStepping;
  m_tabWidth = tab_width;
  m_bkpts = bkpts;

  g2pvt_enter_modal_loop();
  int id = DoModal();
  g2pvt_exit_modal_loop();

  int flag = m_sourceStepping ? DEBUGGER_SOURCE_STEPPING_FLAG : 0;
  switch(id) {
   case IDOK: return flag|1;
   case IDCANCEL: return flag|2;
   case IDPAUSE: return flag|3;
   default: return 0;
  }
}

void G2Debugger::OnPause()
{
  EndDialog(IDPAUSE);
}



/*
 * G2 Interface
 */

long g2ext_debugger_dialog(int opcode, LPWSTR title, LPWSTR label, LPWSTR proc, 
			   LPWSTR env, int flags, int line, int tab_width,
			   unsigned short *bkpts)
{  
  int rc = 0;

  switch(opcode) {
   case DEBUGGER_CREATE:
     if(g_pDialog) {
       WARNF("Recursive debugger dialog!\n");
     } else {
       G2Debugger dlg;
       rc = dlg.DoModalDebugDialog(title, label, proc, env, flags&1, line, tab_width, bkpts);
     }
     break;

   case EDITOR_SET_BREAKPOINT:
   case EDITOR_CLEAR_BREAKPOINT:
   case EDITOR_DISABLE_BREAKPOINT:
   case EDITOR_SET_BREAKPOINTS:
   case EDITOR_CLEAR_BREAKPOINTS:
     if(g_pDialog)
       g_pDialog->GetEditor()->BreakpointCommand(opcode, line-1, bkpts);
     break;

   case DEBUGGER_CANCEL:
     if(g_pDialog)
       g_pDialog->EndDialog(0); // id=0 means No-op
     break;
  }
  return rc;
}
