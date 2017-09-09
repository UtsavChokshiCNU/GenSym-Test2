// CScintillaWnd -- Basic MFC wrapper for Scintilla window

// CScintillaWnd provides the functionality common to all of our uses of
// Scintilla: the G2 editor, debugger, and output panes for the logbook, message
// board, and editor frame notes.

#include "stdafx.h"
#include "Twng.h"
#include "ScintillaWnd.h"

#define FATKEY(ch) ((ch) | (((GetKeyState(VK_SHIFT)   < 0) ? Shift : 0) | \
			    ((GetKeyState(VK_CONTROL) < 0) ? Ctrl : 0) | \
			    ((GetKeyState(VK_MENU)    < 0) ? Alt : 0)))

static UINT uFindReplaceMsg = ::RegisterWindowMessage(FINDMSGSTRING);

IMPLEMENT_DYNCREATE(CScintillaWnd,CWnd)

BEGIN_MESSAGE_MAP(CScintillaWnd,CWnd)
  ON_WM_CREATE()
  ON_WM_CHAR()
  ON_WM_KEYDOWN()
  ON_WM_SYSKEYDOWN()
  ON_WM_DESTROY()

  ON_MESSAGE(WM_PARENT_IS_MOVING,OnParentIsMoving)
  ON_REGISTERED_MESSAGE(uFindReplaceMsg,OnFindReplaceMsg)

  ON_NOTIFY_REFLECT(SCN_PAINTED,OnPainted)
  ON_NOTIFY_REFLECT(SCN_SAVEPOINTLEFT,OnSavePointLeft)
  ON_NOTIFY_REFLECT(SCN_SAVEPOINTREACHED,OnSavePointReached)
  ON_NOTIFY_REFLECT(SCN_MARGINCLICK,OnMarginClick)
  ON_NOTIFY_REFLECT(SCN_HOTSPOTCLICK,OnHotSpotClick)
  ON_NOTIFY_REFLECT(SCN_MODIFYATTEMPTRO,OnModifyAttemptRO)
  ON_NOTIFY_REFLECT_EX(SCN_ZOOM,OnZoom)

  ON_COMMAND(ID_EDIT_CUT,OnEditCut)
  ON_COMMAND(ID_EDIT_COPY,OnEditCopy)
  ON_COMMAND(ID_EDIT_PASTE,OnEditPaste)
  ON_COMMAND(ID_EDIT_CLEAR,OnEditClear)
  ON_COMMAND(ID_EDIT_UNDO,OnEditUndo)
  ON_COMMAND(ID_EDIT_REDO,OnEditRedo)
  ON_COMMAND(ID_EDIT_FIND,OnEditFind)
  ON_COMMAND(ID_EDIT_REPLACE,OnEditReplace)

  ON_UPDATE_COMMAND_UI(ID_EDIT_CUT,OnUpdateEditCut)
  ON_UPDATE_COMMAND_UI(ID_EDIT_COPY,OnUpdateEditCopy)
  ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE,OnUpdateEditPaste)
  ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR,OnUpdateEditClear)
  ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO,OnUpdateEditUndo)
  ON_UPDATE_COMMAND_UI(ID_EDIT_REDO,OnUpdateEditRedo)
  ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE,OnUpdateEditReplace)
END_MESSAGE_MAP()

void g2pvt_initialize_scintilla_library()
{
  static BOOL done = FALSE;
  HINSTANCE hInst = AfxGetResourceHandle();

  if(!done) {
    Scintilla_RegisterClasses(hInst);
    done = TRUE;
  }
}

CScintillaWnd::CScintillaWnd()
{
  m_sciDirectFunction = NULL;
  m_sciPtr = NULL;
  m_controlType = GENSYM_EDITOR;
  m_ownerHandle = 0;
  m_autoDelete = TRUE;		// Assume alloced on heap by default.
  m_varFontName = EDITOR_VAR_FONT;
  m_fixedFontName = EDITOR_FIXED_FONT;
  m_fontSize = EDITOR_FONT_SIZE;
  m_fixedFont = FALSE;
  m_lineNumbers = FALSE;
  m_iconsMargin = FALSE;
  m_zoom = 0;
  m_tabWidth = 4;
  m_consumedKey = FALSE;
  m_scroll_caret_p = FALSE;
  m_ignore_save_points = 0;
  m_pFindReplaceDlg = NULL;	// TODO: Encapsulate in our own find/replace object.
  m_matchCase = FALSE;
  m_wholeWord = FALSE;
  m_searchDown = TRUE;
}

CScintillaWnd::~CScintillaWnd()
{
}

int CScintillaWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  int rc = CWnd::OnCreate(lpCreateStruct);

  if(rc == 0) {
    m_sciDirectFunction = (SciFnDirect)SendMessage(SCI_GETDIRECTFUNCTION);
    m_sciPtr = (sptr_t)SendMessage(SCI_GETDIRECTPOINTER);
    SetupEditor();
    SetupStyles();
  }
  return rc;
}

void CScintillaWnd::PreSubclassWindow() // virtual
{
  CWnd::PreSubclassWindow();
  if(!m_sciDirectFunction) {
    m_sciDirectFunction = (SciFnDirect)SendMessage(SCI_GETDIRECTFUNCTION);
    m_sciPtr = (sptr_t)SendMessage(SCI_GETDIRECTPOINTER);
  }
}

BOOL CScintillaWnd::PreCreateWindow(CREATESTRUCT &cs)
{
  g2pvt_initialize_scintilla_library();
  cs.lpszClass = _T("SCINTILLA");
  return CWnd::PreCreateWindow(cs);
}

void CScintillaWnd::OnDestroy()
{
  if(m_pFindReplaceDlg)
    m_pFindReplaceDlg->DestroyWindow();
  CWnd::OnDestroy();
}

void CScintillaWnd::PostNcDestroy()
{
  VTRACE("CScintillaWnd::PostNcDestroy\n");
  CWnd::PostNcDestroy();
  if(m_autoDelete)
    delete this;
}

void CScintillaWnd::SetupEditor()	    // virtual
{
  Sc(SCI_SETEOLMODE, SC_EOL_LF);    // Always use Unix line-endings
  Sc(SCI_SETCODEPAGE, SC_CP_UTF8);
  Sc(SCI_SETBUFFEREDDRAW, TRUE);
  Sc(SCI_USEPOPUP, FALSE);	    // No popup menu
  Sc(SCI_SETMODEVENTMASK, 0);

  // Disable all self-inserting control chars except ^M, ^J, and ^I
  for(char *keys = "BEFGHKNOPQRSW"; *keys; keys++)
    Sc(SCI_CLEARCMDKEY, Ctrl | *keys);

  // Tab handling
  SetTabWidth(m_tabWidth);
  Sc(SCI_SETTABINDENTS, TRUE);
  Sc(SCI_SETBACKSPACEUNINDENTS, TRUE);
  Sc(SCI_SETINDENTATIONGUIDES, TRUE);

  // Line number margin
  Sc(SCI_SETMARGINTYPEN, MARGIN_LINENUMBERS, SC_MARGIN_NUMBER);
  Sc(SCI_SETMARGINWIDTHN, MARGIN_LINENUMBERS, m_lineNumbers ? 25 : 0);
  Sc(SCI_SETMARGINSENSITIVEN, MARGIN_LINENUMBERS, FALSE);

  Sc(SCI_SETWRAPMODE, SC_WRAP_WORD);
  Sc(SCI_SETHSCROLLBAR, FALSE);
  Sc(SCI_SETWRAPVISUALFLAGS, SC_WRAPVISUALFLAG_END);
  Sc(SCI_SETWRAPVISUALFLAGSLOCATION, SC_WRAPVISUALFLAGLOC_END_BY_TEXT);

  Sc(SCI_SETCARETWIDTH, 2);	// More visible cursor.
  Sc(SCI_SETZOOM, m_zoom);

  // Some standard key bindings.
  Sc(SCI_ASSIGNCMDKEY, Ctrl | SCK_SUBTRACT , SCI_ZOOMOUT);
  Sc(SCI_ASSIGNCMDKEY, Ctrl | SCK_ADD,  SCI_ZOOMIN);
  Sc(SCI_ASSIGNCMDKEY, Ctrl | '0',  SCI_SETZOOM);
  Sc(SCI_ASSIGNCMDKEY, Alt | SCK_RETURN,  SCI_NEWLINE);
}

void CScintillaWnd::SetupStyles()	    // virtual
{
  Sc(SCI_STYLERESETDEFAULT);
  Sc(SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)(m_fixedFont ? m_fixedFontName : m_varFontName));
  Sc(SCI_STYLESETSIZE, STYLE_DEFAULT, (LPARAM)m_fontSize);
  Sc(SCI_STYLESETBACK, STYLE_DEFAULT, EDITOR_BG);
  Sc(SCI_STYLESETFORE, STYLE_DEFAULT, EDITOR_FG);
  Sc(SCI_STYLECLEARALL);
}

LRESULT CScintillaWnd::WithoutUpdateEvents(UINT msg, WPARAM wParam, LPARAM lParam)
{
  int mask = Sc(SCI_GETMODEVENTMASK);
  LRESULT rc;
  Sc(SCI_SETMODEVENTMASK, 0);
  rc = Sc(msg, wParam, lParam);
  Sc(SCI_SETMODEVENTMASK, mask);
  return rc;
}



/*
 * Event handlers
 */

void CScintillaWnd::OnPainted(NMHDR *pNotifyStruct, LRESULT* result)
{
  if(m_scroll_caret_p) {
    m_scroll_caret_p = FALSE;
    Sc(SCI_SCROLLCARET);
  }
}

void CScintillaWnd::OnSavePointLeft(NMHDR *pNotifyStruct, LRESULT* result)
{
  if(m_ignore_save_points == 0)
    SetModified(TRUE);
}

void CScintillaWnd::OnSavePointReached(NMHDR *pNotifyStruct, LRESULT* result)
{
  if(m_ignore_save_points == 0)
    SetModified(FALSE);
}

void CScintillaWnd::OnChar(UINT ch, UINT rep, UINT flags)
{
  if(!m_consumedKey)
    CWnd::OnChar(ch, rep, flags);
  m_consumedKey = FALSE;
}

void CScintillaWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  EditKeyPress(FATKEY(nChar));
  if(!m_consumedKey)
    CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CScintillaWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  EditKeyPress(FATKEY(nChar));
  if(!m_consumedKey)
    CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CScintillaWnd::OnZoom(NMHDR *pNotifyStruct, LRESULT* result)
{
  m_zoom = Sc(SCI_GETZOOM);
  RecomputeLineNumberMargin();
  return FALSE;			// Let parent see it, too.
}

LRESULT CScintillaWnd::OnParentIsMoving(WPARAM, LPARAM)
{
  Sc(SCI_CALLTIPCANCEL);
  return 0;
}

void CScintillaWnd::OnMarginClick(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;
  MarginClick(scn->margin, scn->position, scn->modifiers);
}

void CScintillaWnd::OnModifyAttemptRO(NMHDR *pNotifyStruct, LRESULT* result)
{
  EditorBeep();
}

void CScintillaWnd::OnHotSpotClick(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;
  // Collect string around click (all in same style).
  int pos = scn->position;
  int len = Length();
  int style = STYLE(pos);
  int i, j;
  for(i=pos; i>=0 && STYLE(i)==style; i--);
  for(j=pos; j<len && STYLE(j)==style; j++);
  char *str = GetTextRange(i+1, j);
  HotSpotClick(str, style, pos);
  free(str);
}



/*
 * Overrides
 */

void CScintillaWnd::EditKeyPress(UINT key) // virtual
{
}

void CScintillaWnd::SetModified(BOOL modified) // virtual
{
}

void CScintillaWnd::MarginClick(int margin, int pos, int modifiers) // virtual
{
}

void CScintillaWnd::HotSpotClick(LPCSTR str, int style, int pos) // virtual
{
}



/*
 * UTF8/16 Conversions
 */

void CScintillaWnd::SetUnicodeText(LPCWSTR wstr, int caret /*= 0*/)
{
  // Convert Gensym Unicode to UTF-8
  int pos = caret;
  char *buf = g2pvt_to_utf8(wstr, &pos);
  if(!buf)
    return;

  // Disable change events during replace.
  m_ignore_save_points++;
  WithoutUpdateEvents(SCI_SETTEXT, 0, (LPARAM)buf);
  Sc(SCI_SETSAVEPOINT);
  Sc(SCI_EMPTYUNDOBUFFER);
  SETPOS(pos);
  m_ignore_save_points--;

  free(buf);
  RecomputeLineNumberMargin();	// FIXME: really want when log(lines) changes.
  m_scroll_caret_p = TRUE;
}

// GetUnicodeText -- Return newly malloced wide string in the format G2 wants:
// Unicode with Unicode line breaks. The caret is updated so that it points to
// the same character in the converted string.
LPWSTR CScintillaWnd::GetUnicodeText(int *pCaret /*= NULL*/)
{
  int len, caret;
  char *buf;
  LPWSTR wstr;

  len = Length();
  buf = (char *) malloc(len+1);
  if(buf == NULL)
    return NULL;

  caret = POS();		// UTF-8 caret
  Sc(SCI_GETTEXT, len+1, (LPARAM)buf); // UTF-8 text

  // Convert string and caret from UTF-8 to Gensym Unicode.
  wstr = g2pvt_to_gensym_unicode(buf, len, &caret);

  if(pCaret) *pCaret = caret;
  free(buf);
  return wstr;
}

void CScintillaWnd::InsertUnicodeText(LPWSTR wstr, int caret)
{
  if(wcslen(wstr) == 0)
    return;

  int pos = pos_from_caret(caret);
  char *str = g2pvt_to_utf8(wstr);
  Sc(SCI_BEGINUNDOACTION);
  WithoutUpdateEvents(SCI_INSERTTEXT, pos, (LPARAM)str);
  Sc(SCI_ENDUNDOACTION);
  SETPOS(pos+strlen(str));
  free(str);
  m_scroll_caret_p = TRUE;
}

void CScintillaWnd::ReplaceUnicodeText(LPWSTR wstr, int startCaret, int endCaret)
{
  int startPos = pos_from_caret(startCaret);
  int endPos = pos_from_caret(endCaret);

  Sc(SCI_SETTARGETSTART, startPos);
  Sc(SCI_SETTARGETEND, endPos);

  char *str = g2pvt_to_utf8(wstr);
  Sc(SCI_BEGINUNDOACTION);
  WithoutUpdateEvents(SCI_REPLACETARGET, -1, (LPARAM)str);
  Sc(SCI_ENDUNDOACTION);
  SETPOS(startPos+strlen(str));
  free(str);
}

void CScintillaWnd::DeleteUnicodeText(int startCaret, int endCaret)
{
  ReplaceUnicodeText(L"", startCaret, endCaret);
}

void CScintillaWnd::AppendUnicodeText(LPCWSTR wstr)
{
  if(wcslen(wstr) == 0)
    return;
  char *str = g2pvt_to_utf8(wstr);
  Sc(SCI_APPENDTEXT, strlen(str), (LPARAM)str);
  free(str);
}

// Convert Unicode caret to UTF-8 pos.
int CScintillaWnd::pos_from_caret(int caret)
{
  LPWSTR wstr;
  int pos;

  if(caret < 0)
    return POS();

  wstr = GetUnicodeText(NULL);

  g2pvt_to_native_linebreaks(wstr); // WideCharToMultiByte seems to need this.

  if(caret == 0)
    pos = 0;
  else if(caret >= (int)wcslen(wstr))
    pos = Length();
  else
    pos = WideCharToMultiByte(CP_UTF8, 0, wstr, caret, NULL, 0, NULL, NULL);

  /* Ensure that pos is in range. It can be out of range if the user modified
   * the buffer while a message from G2 was in transit. */
  pos = max(0, min(Length(), pos));

  free(wstr);
  return pos;
}

// NOTE: An expensive computation. Consider how to cache some of it
int CScintillaWnd::caret_from_pos(int pos)
{
  int caret, len = pos + 1;
  char *buf;

  buf = (char *) malloc(len);
  if(buf == NULL)
    return pos;			// Punt

  Sc(SCI_GETTEXT, len, (LPARAM)buf);

  caret = ::MultiByteToWideChar(CP_UTF8, 0, buf, pos, NULL, 0);
  free(buf);
  return caret;
}

// Get UTF8 substring from editor buffer.
char *CScintillaWnd::GetTextRange(int startPos, int endPos)
{
  int len = endPos - startPos + 1;
  ASSERT(len>=0);
  char *buf = (char *)malloc(len);
  TextRange tr = {{startPos, endPos}, buf};
  buf[0]= '\0';
  Sc(SCI_GETTEXTRANGE, 0, (LPARAM)&tr);
  return buf;
}

char *CScintillaWnd::GetLine(int line)
{
  int start = Sc(SCI_POSITIONFROMLINE, line);
  return GetTextRange(start, GetEol(start));
}



/*
 * Output Window support
 */

void CScintillaWnd::ClearOutput()
{
  SetReadOnly(FALSE);
  //  Sc(SCI_CLEARDOCUMENTSTYLE);	// Needed?
  Sc(SCI_CLEARALL);
  SetReadOnly(TRUE);
}

void CScintillaWnd::AppendOutput(LPCWSTR wstr, int style)
{
  SetReadOnly(FALSE);
  if(style == 0) {
    AppendUnicodeText(wstr);
  } else {
    int start = Length();
    AppendUnicodeText(wstr);
    int end = Length();
    if(end > start) {
      Sc(SCI_STARTSTYLING, start, 31);
      Sc(SCI_SETSTYLING, end-start, style);
    }
  }
  SetReadOnly(TRUE);
}

void CScintillaWnd::SetOutput(LPCSTR str, LPCWSTR wstr)
{
  SetReadOnly(FALSE);
  if(str)
    Sc(SCI_SETTEXT, 0, (LPARAM)str);
  if(wstr)
    SetUnicodeText(wstr);
  SetReadOnly(TRUE);
}



/*
 * Utilities
 */

void CScintillaWnd::SetSel(int anchorPos /*= -1*/, int currentPos /*= -1*/)
{
  Sc(SCI_SETSEL, anchorPos, currentPos);
}

BOOL CScintillaWnd::HasSel()
{
  return Sc(SCI_GETSELECTIONSTART) != Sc(SCI_GETSELECTIONEND);
}

LPSTR CScintillaWnd::GetSel()
{
  int len = Sc(SCI_GETSELTEXT,0,0);
  char *buf = (char *)malloc(len);
  Sc(SCI_GETSELTEXT, 0, (LPARAM)buf);
  return buf;
}

BOOL CScintillaWnd::IsModified()
{
  return Sc(SCI_GETMODIFY) != 0;
}

BOOL CScintillaWnd::IsReadOnly()
{
  return Sc(SCI_GETREADONLY) != 0;
}

void CScintillaWnd::SetReadOnly(BOOL val /*= TRUE*/)
{
  Sc(SCI_SETREADONLY, val);
}

int CScintillaWnd::Length()
{
  return Sc(SCI_GETLENGTH);
}

int CScintillaWnd::GetEol(int pos)
{
  int line = Sc(SCI_LINEFROMPOSITION, pos);
  return Sc(SCI_GETLINEENDPOSITION, line);
}

void CScintillaWnd::SetTabWidth(int width)
{
  if(width<0 || width>255)
    return;

  if(width==0) {
    Sc(SCI_SETTABWIDTH, 8);
    Sc(SCI_SETUSETABS, TRUE);
  } else {
    Sc(SCI_SETTABWIDTH, width);
    Sc(SCI_SETUSETABS, FALSE);
  }
  m_tabWidth = width;
}

void CScintillaWnd::HighlightBrace(BOOL on, int pos)
{
  int match;

  if(on) {
    match = Sc(SCI_BRACEMATCH, pos);
    if(match < 0)
      Sc(SCI_BRACEBADLIGHT, pos); // Maybe beep?
    else
      Sc(SCI_BRACEHIGHLIGHT, pos, match);
  } else {
    Sc(SCI_BRACEHIGHLIGHT, -1, -1);
    Sc(SCI_BRACEBADLIGHT, -1);
  }
}

int CScintillaWnd::ApproxEditorWidthInColumns()
{
  RECT r;
  int charWidth = Sc(SCI_TEXTWIDTH, STYLE_DEFAULT, (LPARAM)"m");
  GetClientRect(&r);
  return 8 + (r.right - r.left + charWidth - 1) / charWidth;
}

void CScintillaWnd::RecomputeLineNumberMargin()
{
  int width = 0;
  if(m_lineNumbers) {
    char buf[32];
    sprintf(buf, "_%d", Sc(SCI_GETLINECOUNT));
    width = Sc(SCI_TEXTWIDTH, STYLE_LINENUMBER, (LPARAM)buf);
  }
  Sc(SCI_SETMARGINWIDTHN, MARGIN_LINENUMBERS, width);
}

void CScintillaWnd::EditorBeep()
{
  MessageBeep(MB_OK);
}

void CScintillaWnd::InsertText(LPCSTR str, int pos /*= -1*/)
{
  if(pos<0) pos = POS();
  Sc(SCI_INSERTTEXT, pos, (LPARAM)str);
  SETPOS(pos+strlen(str));
}

void CScintillaWnd::ReplaceText(LPCSTR str, int startPos, int endPos)
{
  Sc(SCI_SETTARGETSTART, startPos);
  Sc(SCI_SETTARGETEND, endPos);
  Sc(SCI_REPLACETARGET, -1, (LPARAM)str);
  SETPOS(startPos+strlen(str));
}

void CScintillaWnd::DeleteText(int startPos, int endPos)
{
  ReplaceText("", startPos, endPos);
}



/*
 * Selection/Searching
 */

void CScintillaWnd::ReplaceSelection(char *str)
{
  Sc(SCI_REPLACESEL, 0, (LPARAM)str);
}

BOOL CScintillaWnd::SelectionEqual(LPCWSTR wstr, BOOL matchCase)
{
  char *sel = GetSel();
  char *str = g2pvt_to_utf8(wstr);
  int rc = matchCase ? strcmp(sel,str)==0 : _stricmp(sel,str)==0;
  free(sel);
  free(str);
  return rc;
}

BOOL CScintillaWnd::FindString(LPCWSTR wstr, BOOL matchCase, BOOL wholeWord, BOOL down)
{
  int pos = POS();
  struct TextToFind ttf;

  if(wstr[0] == L'\0')
    return FALSE;

  ZeroMemory(&ttf,sizeof(ttf));
  if(down) {
    ttf.chrg.cpMin = pos;
    ttf.chrg.cpMax = Length();
  } else {
    ttf.chrg.cpMin = max(0, pos - 1);
    ttf.chrg.cpMax = 0;
  }

  ttf.lpstrText = g2pvt_to_utf8(wstr);

  pos = Sc(SCI_FINDTEXT, 
	   (matchCase ? SCFIND_MATCHCASE : 0) | (wholeWord ? SCFIND_WHOLEWORD : 0),
	   (LPARAM) &ttf);
  free(ttf.lpstrText);

  if(pos < 0)
    return FALSE;

  if(down)
    SetSel(ttf.chrgText.cpMin, ttf.chrgText.cpMax);
  else
    SetSel(ttf.chrgText.cpMax, ttf.chrgText.cpMin);

  return TRUE;
}



/*
 * Commands
 */

void CScintillaWnd::OnEditCut()
{
  Sc(SCI_CUT);
}

void CScintillaWnd::OnEditCopy()
{
  Sc(SCI_COPY);
}

void CScintillaWnd::OnEditPaste()
{
  Sc(SCI_PASTE);
}

void CScintillaWnd::OnEditClear()
{
  Sc(SCI_CLEAR);
}

void CScintillaWnd::OnEditUndo()
{
  Sc(SCI_UNDO);
}

void CScintillaWnd::OnEditRedo()
{
  Sc(SCI_REDO);
}

void CScintillaWnd::OnUpdateEditCut(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(HasSel() && !IsReadOnly());
}

void CScintillaWnd::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(HasSel());
}

void CScintillaWnd::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(Sc(SCI_CANPASTE));
}

void CScintillaWnd::OnUpdateEditClear(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(!IsReadOnly());
}

void CScintillaWnd::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(Sc(SCI_CANUNDO));
}

void CScintillaWnd::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(Sc(SCI_CANREDO));
}

void CScintillaWnd::OnUpdateEditReplace(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(!IsReadOnly());
}

void CScintillaWnd::ToggleWhitespace()
{
  if(Sc(SCI_GETVIEWEOL)) {
    Sc(SCI_SETVIEWEOL, FALSE);
    Sc(SCI_SETVIEWWS, SCWS_INVISIBLE);
  } else {
    Sc(SCI_SETVIEWEOL, TRUE);
    Sc(SCI_SETVIEWWS, SCWS_VISIBLEALWAYS);
  }
}

void CScintillaWnd::SetLineNumbersVisible(BOOL vis)
{
  m_lineNumbers = vis;
  RecomputeLineNumberMargin();
}

void CScintillaWnd::ToggleLineNumbers()
{
  m_lineNumbers = !m_lineNumbers;
  RecomputeLineNumberMargin();
}

void CScintillaWnd::ToggleFont()
{
  m_fixedFont = !m_fixedFont;
  SetupStyles();
}



/*
 * Find/Replace Dialog
 */

BOOL CScintillaWnd::FindDialogPresent()
{
  return m_pFindReplaceDlg && !ReplaceDialogPresent();
}

BOOL CScintillaWnd::ReplaceDialogPresent()
{
  return m_pFindReplaceDlg && (m_pFindReplaceDlg->ReplaceAll() || m_pFindReplaceDlg->ReplaceCurrent());
}

void CScintillaWnd::OnEditFind()
{
  if(FindDialogPresent()) {
    m_pFindReplaceDlg->SetActiveWindow();
  } else {
    if(m_pFindReplaceDlg)
      m_pFindReplaceDlg->SendMessage(WM_CLOSE);
    UINT flags = (m_matchCase ? FR_MATCHCASE : 0) | (m_wholeWord ? FR_WHOLEWORD : 0) |
      (m_searchDown ? FR_DOWN : 0);

    m_pFindReplaceDlg = new CFindReplaceDialog();
    m_pFindReplaceDlg->Create(TRUE, m_findWhat, NULL, flags, this);
  }
}

void CScintillaWnd::OnEditReplace()
{
  if(ReplaceDialogPresent()) {
    m_pFindReplaceDlg->SetActiveWindow();
  } else {
    if(m_pFindReplaceDlg)
      m_pFindReplaceDlg->SendMessage(WM_CLOSE);
    m_pFindReplaceDlg = new CFindReplaceDialog();
    UINT flags = (m_matchCase ? FR_MATCHCASE : 0) | (m_wholeWord ? FR_WHOLEWORD : 0) |
      (m_searchDown ? FR_DOWN : 0);
    m_pFindReplaceDlg->Create(FALSE, m_findWhat, m_replaceWith, flags, this);
  }
}

void CScintillaWnd::OnEditFindNext()
{
  if(!FindString(m_findWhat, m_matchCase, m_wholeWord, m_searchDown))
    EditorBeep();
}

LRESULT CScintillaWnd::OnFindReplaceMsg(WPARAM, LPARAM lParam)
{
  CFindReplaceDialog *pDlg = CFindReplaceDialog::GetNotifier(lParam);
  char *str;
  CString fs = pDlg->GetFindString();

  if(!pDlg)
    return 0;

  if(pDlg->FindNext()) {
    FindNext(pDlg);

  } else if(pDlg->ReplaceCurrent()) {
    if(SelectionEqual(pDlg->GetFindString(), pDlg->MatchCase()) || FindNext(pDlg)) {
      str = g2pvt_to_utf8(pDlg->GetReplaceString());
      ReplaceSelection(str);
      free(str);
      FindNext(pDlg,TRUE);
    }

  } else if(pDlg->ReplaceAll()) {
    if(SelectionEqual(pDlg->GetFindString(), pDlg->MatchCase()) || FindNext(pDlg)) {
      str = g2pvt_to_utf8(pDlg->GetReplaceString());
      do {
	ReplaceSelection(str);
      } while (FindNext(pDlg,TRUE));
      free(str);
    }

  } else if(pDlg->IsTerminating()) {
    // TODO: Save flags.
    m_findWhat = pDlg->GetFindString();
    m_replaceWith = pDlg->GetReplaceString();
    m_matchCase = pDlg->MatchCase();
    m_wholeWord = pDlg->MatchWholeWord();
    m_searchDown = pDlg->SearchDown();

    m_pFindReplaceDlg = NULL; 
  }
  return 0;
}

BOOL CScintillaWnd::FindNext(CFindReplaceDialog *pDlg, BOOL quiet /*= FALSE*/)
{
  BOOL found = FindString(pDlg->GetFindString(), pDlg->MatchCase(),
			  pDlg->MatchWholeWord(), pDlg->SearchDown());
  if(!found && !quiet)
    EditorBeep();
  return found;
}



/*
 * G2 Interface
 */

void CScintillaWnd::FireEvent(int opcode, int caret, LPWSTR string /*= NULL*/, int arg1 /*= -1*/, int arg2 /*= -1*/)
{
  if(m_ownerHandle > 0)
    g2pvt_fire_control_event(m_controlType, m_ownerHandle, opcode, caret, arg1, arg2, string);
}




/*
 * Debugging
 */

void CScintillaWnd::DebugCaret()
{
  CString s;
  int pos = POS();
  s.Format(_T("pos %d line %d col %d"), pos, Sc(SCI_LINEFROMPOSITION, pos), Sc(SCI_GETCOLUMN, pos));
  GetParentFrame()->SetWindowText(s);
}


/*
 * String Utilities
 */

void g2pvt_subst_char(wchar_t newChar, wchar_t oldChar, LPWSTR s)
{
  while(*s)
    *s++ = (*s == oldChar) ? newChar : *s;
}

LPWSTR g2pvt_to_native_linebreaks(LPWSTR s)
{
  g2pvt_subst_char(L'\n', GENSYM_CODE_FOR_LINEBREAK, s);
  return s;
}

// Convert LF's to Gensym Unicode line breaks, in-place.
LPWSTR g2pvt_to_gensym_linebreaks(LPWSTR s)
{
  g2pvt_subst_char(GENSYM_CODE_FOR_LINEBREAK, L'\n', s);
  return s;
}

// Return newly allocated UTF8 string for Gensym Unicode string.
char *g2pvt_to_utf8(LPCWSTR ustr, int *pCaret)
{
  int len;
  char *buf;
  LPWSTR wstr = wcsdup(ustr);

  g2pvt_to_native_linebreaks(wstr);

  len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
  buf = (char *) malloc(len+1);
  if(buf == NULL) return NULL;

  // Convert Unicode caret to UTF-8.
  if(pCaret && *pCaret > 0) {
    *pCaret = WideCharToMultiByte(CP_UTF8, 0, wstr, *pCaret, NULL, 0, NULL, NULL);
  }

  buf[0] = 0;
  WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buf, len+1, NULL, NULL);
  free(wstr);
  return buf;
}

char *g2pvt_to_utf8(LPCWSTR ustr)
{
  return g2pvt_to_utf8(ustr, NULL);
}

/* Convert UTF8 to Unicode, with Unicode line breaks.
 * Unlike the other routines, this one returns a NEW string.
 * Caret is adjusted to point to the same character. */
LPWSTR g2pvt_to_gensym_unicode(LPCSTR str, int len, int *pCaret)
{
  int wlen;
  LPWSTR wstr;

  if(len < 0)
    len = strlen(str);

  wlen = MultiByteToWideChar(CP_UTF8, 0, str, len, NULL, 0);
  wstr = (LPWSTR) malloc((wlen+1) * sizeof(wchar_t));
  if(wstr == NULL)
    return NULL;

  if(pCaret)				// Convert caret
    *pCaret = MultiByteToWideChar(CP_UTF8, 0, str, *pCaret, NULL, 0);

  MultiByteToWideChar(CP_UTF8, 0, str, len, wstr, wlen); // Convert string.
  wstr[wlen] = L'\0';
  g2pvt_to_gensym_linebreaks(wstr);

  return wstr;
}

/* Returns newly allocated string with words wrapped (approximately) at given
   number of columns. */
char *g2pvt_wrap_words(char *string, int columns)
{
  int n = strlen(string);
  int col = 0;
  char *s, *t, *u;

  u = t = (char *) malloc(3*n+1); // Generous upper bound

  s=string;
  while(*s) {
    if(col > columns) {
      while(*s && !isspace(*s))	// Output rest of this word
	*t++ = *s++;
      if(*s) {
	if(*s == '\n') {
	  *t++ = *s++;
	  col=0;
	} else {
	  *t++ = *s++;
	  *t++ = '\n';
	  *t++ = ' ';
	  col=1;
	}
      }
    } else {
      if(*s == '\n') col = -1;
      *t++ = *s++;
      col++;
    }
  }
  *t++ = '\0';

  t = strdup(u);
  free(u);
  return t;
}

BOOL g2pvt_is_brace(int ch) {
  return ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '{' || ch == '}';
}

BOOL g2pvt_is_number(const char *s)
{
  int k=0;

  if(*s != '.') {
    if(*s == '-' || *s == '+') s++;
    for(;*s;s++)
      if(isdigit(*s))
	k++;
      else
	break;
  }

  if(*s == '.')
    for(s++;*s;s++)
      if(isdigit(*s))
	k++;
      else
	break;

  if(k==0) return FALSE;

  if(*s == 'e' || *s == 'E') {
    s++;
    if(*s == '-' || *s == '+') s++;
    k=0;
    for(;*s;s++)
      if(isdigit(*s))
	k++;
      else
	break;
    if(k==0) return FALSE;
  }
  return *s ? FALSE : TRUE;
}

//added by SoftServe
BOOL g2pvt_is_long_number (const char *s) {

	int k = 0;

	if (s == NULL) return FALSE;

	if (strlen(s) == 1) return FALSE;

	if(*s == '-' || *s == '+') s++;
	for(s++;*s;s++)
      if(isdigit(*s))
	k++;
      else
	break;

	return (k !=0 && *s == 'L');
}
//end of changes
