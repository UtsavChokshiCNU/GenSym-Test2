// Editor.cpp : G2Editor based on Scintilla

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ScintillaWnd.h"
#include "Editor.h"
#include "EditorFrame.h"
#include "ModalEdit.h"
#include "ddrsc.h"

// NOTE: Don't we want all UTF8 extra bytes to be word chars?
#define G2_WORDCHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'-._@"
extern int maxUndoSteps;
/*
 * Utils
 */

// FIXME: Use a hash table
static BOOL word_in_list(const char *word, char **list)
{
  int i;

  for (i=0; list[i]; i++) {
    if ((toupper(list[i][0]) == toupper(word[0])) && (0 == stricmp(list[i], word))) 
      return TRUE;
  }
  return FALSE;
}

static void MarkAsModified(CWnd *pWnd, BOOL modified)
{
  CString title;
  LPCTSTR tag = _T(" *");

  pWnd->GetWindowText(title);

  BOOL marked = (title.Right(2) == tag);

  if(modified == marked) return;

  if(modified)
    title += tag;
  else
    title.TrimRight(tag);

  pWnd->SetWindowText(title);
}



/*
 * Icons
 */

static char *xpm_ArrowIcon[] = {
/* width height num_colors chars_per_pixel */
"    16    15        3            1",
/* colors */
"  c None",
". c #000000",
"# c #ffff00",
/* pixels */
"                ",
"       .        ",
"       ..       ",
"       .#.      ",
"       .##.     ",
" .......###.    ",
" .##########.   ",
" .###########.  ",
" .##########.   ",
" .......###.    ",
"       .##.     ",
"       .#.      ",
"       ..       ",
"       .        ",
"                "
};

static char *xpm_ClassIcon[] = {
/* columns rows colors chars-per-pixel */
"16 16 9 1",
"  c None",
"B c #000000",
". c #800000",
"o c #808000",
"g c #008080",
"# c #808080",
"* c #ffff00",
"- c #ff00ff",
"; c #00ffff",
/* pixels */
"   B            ",
"  B*B           ",
" B***B          ",
"B***ooB     B   ",
"***ooB     B-B  ",
"B*ooB#####B-..B ",
" BoB   # B-..B  ",
"  B    #  B.B   ",
"       #   B    ",
"       #        ",
"       #   B    ",
"       ###B;B   ",
"         B;ggB  ",
"        B;ggB   ",
"         BgB    ",
"          B     "
};

static char *xpm_ProcedureIcon[] = {
/* columns rows colors chars-per-pixel */
"16 16 4 1",
"  c None",
"B c #000000",
"+ c #800080",
"- c #ff00ff",
/* pixels */
"          B     ",
"         B-B    ",
"        B-+-B   ",
"       B-+-+-B  ",
"       BB-+-+-B ",
"       B-B-+-BB ",
"       B+-B-B+B ",
"        B+-B++B ",
"         B+B+B  ",
"          BBB   ",
"           B    ",
"                ",
"                ",
"                ",
"                ",
"                "
};

static char *xpm_VariableIcon[] = {
/* columns rows colors chars-per-pixel */
"16 16 6 1",
"  c None",
"B c #000000",
"+ c #800080",
"g c #008080",
"# c #808080",
"; c #00ffff",
/* pixels */
"           #    ",
"          #;#   ",
"         #;g;#  ",
"        #;g;g;B ",
"       #;g;g;BB ",
"       ##;g;B#B ",
"       #;#;B##B ",
"       #;;B##B  ",
"        #;B#B   ",
"         #BB    ",
"          B     ",
"                ",
"                ",
"                ",
"                ",
"                "
};

static char *xpm_ErrorIcon[] = {
/* columns rows colors chars-per-pixel */
"16 16 17 1",
"  c #040204",
". c #6C0B0C",
"X c #722120",
"o c #91100E",
"O c #BE1C0C",
"+ c #B4352C",
"@ c #984E4B",
"# c #D62F12",
"$ c #DE4C2D",
"% c #DC6B52",
"& c #D87469",
"* c #DF8778",
"= c #C0AEAC",
"- c #E89C94",
"; c #C6C3C4",
": c #FCFDFC",
"> c None",
/* pixels */
">>>>;&%$$$%=>>>>",
">>;*$##O#O##@;>>",
">;%###O#OOOOO+;>",
">&$O-*#O#O&-Oo@>",
"=$#-::&OO&::-Oo=",
"%##%:::&&:::%Oo@",
"$##O%::::::%oOOX",
"###O#&::::%OOOoo",
"#O#OO&::::&oOoO.",
"+#O#&::::::&OoO.",
"$OO&:::%%:::&oo@",
"=OO*::%oO%::*o.=",
">@OO*%OOOO%*oo@>",
">;+oOOOOoOoooX;>",
">>;@oooOooo.@;>>",
">>>>=@X..X@=>>>>"
};

static char *xpm_BreakpointIcon[] = {
"16 16 18 1",
"  c None",
"# c #446D8C",
"+ c #6297BF",
"@ c #7CB7E2",
"s c #78A1C2",
"$ c #4A7392",
"% c #6399C2",
"& c #7FBAE7",
"* c #7FA6C5",
"= c #8FC0E5",
"- c #9AC0DF",
"; c #9BB8CF",
"> c #8FA5B7",
", c #7E909E",
"' c #66717B",
") c #446984",
"! c #5A656D",
"~ c #4C6A80",
"                ",
"                ",
"                ",
"    #########   ",
"   #+@@@@@@@s$  ",
"  #%&&&&&&&&&*# ",
"  #===========# ",
"  #-----------# ",
"  #;;;;;;;;;;;# ",
"  #>>>>>>>>>>># ",
"  #,,,,,,,,,,,# ",
"  #'''''''''''# ",
"   )!!!!!!!!!~  ",
"    #########   ",
"                ",
"                "};

static char *xpm_DisabledBreakpointIcon[] = {
"16 16 18 1",
"  c None",
"# c #446D8C",
"+ c #6297BF",
"@ c #7CB7E2",
"s c #78A1C2",
"$ c #4A7392",
"% c #6399C2",
"& c #7FBAE7",
"* c #7FA6C5",
"= c #8FC0E5",
"- c #9AC0DF",
"; c #9BB8CF",
"> c #8FA5B7",
", c #7E909E",
"' c #66717B",
") c #446984",
"! c #5A656D",
"~ c #4C6A80",
"                ",
"                ",
"                ",
"    #########   ",
"   #+@@@@@@@s$  ",
"  #%         *# ",
"  #=         =# ",
"  #-         -# ",
"  #;         ;# ",
"  #>         ># ",
"  #,         ,# ",
"  #'         '# ",
"   )!!!!!!!!!~  ",
"    #########   ",
"                ",
"                "};



/*
 * Editor Preferences
 */

static G2EditorPrefs m_defaultEditorPrefs;

G2EditorPrefs::G2EditorPrefs()
{
  m_varFontName = EDITOR_VAR_FONT;
  m_fixedFontName = EDITOR_FIXED_FONT;
  m_fontSize = EDITOR_FONT_SIZE;
  m_fixedFont = FALSE;	  // Default to variable width
  m_colorStyles = TRUE;	  // Display styles in color
  m_lineNumbers = TRUE;	  // Display line numbers
  m_iconsMargin = TRUE;	  // Display breakpoints, syntax errors, etc.
  m_zoom = 0;		  // No zoom
}



/*
 * G2Editor Class
 */

#define Super CScintillaWnd

IMPLEMENT_DYNCREATE(G2Editor,Super)

BEGIN_MESSAGE_MAP(G2Editor,Super)
  ON_WM_SETFOCUS()
  ON_WM_DESTROY()
  ON_WM_CONTEXTMENU()

  ON_NOTIFY_REFLECT(SCN_STYLENEEDED,OnStyleNeeded)
  ON_NOTIFY_REFLECT(SCN_UPDATEUI,OnUpdateUI)
  ON_NOTIFY_REFLECT(SCN_CHARADDED,OnCharAdded)
  ON_NOTIFY_REFLECT(SCN_MODIFIED,OnModified)
  ON_NOTIFY_REFLECT(SCN_AUTOCSELECTION,OnAutoComplete)

  ON_CONTROL_REFLECT(SCEN_CHANGE,OnChange)

  ON_COMMAND(ID_EDIT_UNDO,OnEditUndo)
  ON_COMMAND(IDOK,OnEditOK)
  ON_COMMAND(IDCANCEL,OnEditCancel)

  ON_COMMAND(ID_FILE_SAVE,OnFileSave)
  ON_UPDATE_COMMAND_UI(ID_FILE_SAVE,OnUpdateFileSave)

  ON_COMMAND(ID_EDIT_SAVE_AND_EXIT,OnEditOK)
  ON_UPDATE_COMMAND_UI(ID_EDIT_SAVE_AND_EXIT,OnUpdateEditOK)

  ON_COMMAND(ID_GOTO_ITEM,OnGotoItem)
  ON_UPDATE_COMMAND_UI(ID_GOTO_ITEM,OnUpdateGotoItem)
END_MESSAGE_MAP()


G2Editor::G2Editor(int handle)
{
  m_handle = handle;
  m_ownerHandle = handle;
  m_g2pointer = -1;
  SAVE_WND();
  m_grammar = FreeText;
  m_singleLineComments = FALSE;
  m_singleLineMode = FALSE;
  m_queryClose = TRUE;
  m_contextMenuID = IDR_EDITOR;
  m_cursor = -1;
  m_incrementalUpdates = 0;
  m_syntax_error_marker = -1;
  m_remove_syntax_error = FALSE;
  m_autoclose = FALSE;
  m_disabled = FALSE;
  m_calltip_start = 0;
  m_calltip = NULL;
  m_bModal = FALSE; //Added by SoftServe
  RestorePrefs();
  VTRACE("G2Editor Construct [%d] %08X\n", m_handle, this);
}

G2Editor::~G2Editor()
{
  VTRACE("G2Editor  Destruct [%d] %08X\n", m_handle, this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
  if(m_calltip)
    free(m_calltip);
  m_calltip = NULL;
}

void G2Editor::OnSetFocus(CWnd* pOldWnd)
{
  VTRACE("G2Editor::OnSetFocus [%d] ", m_handle); POB(this);
  Super::OnSetFocus(pOldWnd);
  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
}

void G2Editor::OnDestroy()
{
  VTRACE("G2Editor OnDestroy [%d] %08X\n", m_handle, this);
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  SavePrefs();
  Super::OnDestroy();
}

G2EditorPrefs *G2Editor::GetPrefs() // virtual
{
  return &m_defaultEditorPrefs;
}

void G2Editor::RestorePrefs(G2EditorPrefs *p /*=NULL*/)
{
  if(!p) p=GetPrefs();
  m_varFontName = p->m_varFontName;
  m_fixedFontName = p->m_fixedFontName;
  m_fontSize = p->m_fontSize;
  m_fixedFont = p->m_fixedFont;
  m_colorStyles = p->m_colorStyles;
  m_lineNumbers = p->m_lineNumbers;
  m_zoom = p->m_zoom;
}

void G2Editor::SavePrefs(G2EditorPrefs *p /*=NULL*/)
{
  if(!p) p=GetPrefs();
  p->m_fontSize = m_fontSize;
  p->m_fixedFont = m_fixedFont;
  p->m_colorStyles = m_colorStyles;
  p->m_lineNumbers = m_lineNumbers;
  p->m_zoom = m_zoom;
}

CEditorWnd *G2Editor::GetEditorWnd()
{
  CWnd* pWnd = GetParent();
  while (pWnd != NULL) {
    if(pWnd->IsKindOf(RUNTIME_CLASS(CEditorWnd)))
      return (CEditorWnd*) pWnd;
    pWnd = pWnd->GetParent();
  }
  return NULL;
}

CXTPCommandBars *G2Editor::GetCommandBars()
{
  if(GetEditorWnd())
    return GetEditorWnd()->GetCommandBars();
  else
    return GetMainWnd()->GetCommandBars();
}

CScintillaWnd *G2Editor::GetOutputWnd()
{
  CEditorWnd *pFrame = GetEditorWnd();
  return pFrame ? pFrame->m_pOutput : NULL;
}

void G2Editor::ClearOutput()
{
  if(GetOutputWnd())
    GetOutputWnd()->ClearOutput();
}

void G2Editor::AppendOutput(LPCWSTR wstr, int style)
{
  if(GetOutputWnd())
    GetOutputWnd()->AppendOutput(wstr, style);
}

void G2Editor::SetOutput(LPCSTR str, LPCWSTR wstr)
{
  if(GetOutputWnd())
    GetOutputWnd()->SetOutput(str, wstr);
}

void G2Editor::EditorMsg(LPCSTR str)
{
  SetOutput(str, NULL);
}

void G2Editor::EditorMsg(LPCWSTR wstr)
{
  SetOutput(NULL, wstr);
}

void G2Editor::Beep()
{
  MessageBeep(MB_OK);
}

void G2Editor::Warn(LPCSTR str)
{
  Beep();
  EditorMsg(str);
}

void G2Editor::Warn(LPCWSTR string)
{
  Beep();
  EditorMsg(string);
}

void G2Editor::SetModified(BOOL modified) // virtual
{
  // Added by SoftServe 
  if (m_bModal)
	MarkAsModified(GetParentFrame()->GetParent(), modified);
  else
	MarkAsModified(GetParentFrame(), modified);
}



/*
 * Setup
 */

void G2Editor::SetupEditor()	// virtual
{
  Super::SetupEditor();

  Sc(SCI_SETMODEVENTMASK, m_incrementalUpdates ? EDITOR_EVENT_MASK : 0);

  // Margin for breakpoint markers
  Sc(SCI_SETMARGINTYPEN, MARGIN_ICONS, SC_MARGIN_SYMBOL);// SC_MARGIN_BACK
  Sc(SCI_SETMARGINWIDTHN, MARGIN_ICONS, MARGIN_ICONS_WIDTH);
  Sc(SCI_SETMARGINSENSITIVEN, MARGIN_ICONS, TRUE);
  Sc(SCI_SETMARGINMASKN, MARGIN_ICONS, MK_MASK);

  // Margin for folding symbols
  Sc(SCI_SETMARGINTYPEN, MARGIN_FOLD, SC_MARGIN_BACK);
  Sc(SCI_SETMARGINWIDTHN, MARGIN_FOLD, MARGIN_FOLD_WIDTH);
  Sc(SCI_SETMARGINSENSITIVEN, MARGIN_FOLD, TRUE);
  Sc(SCI_SETMARGINMASKN, MARGIN_FOLD, SC_MASK_FOLDERS);

  // Markers...folding
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_BOXMINUS);
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_BOXPLUS);
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE);
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNER);
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_BOXPLUSCONNECTED);
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_BOXMINUSCONNECTED);
  Sc(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNER);

  COLORREF mFG = EDITOR_BG;
  COLORREF mBG = RGB(172,168,153); // Light gray

  Sc(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPEN, mFG);
  Sc(SCI_MARKERSETFORE, SC_MARKNUM_FOLDER, mFG);
  Sc(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEREND, mFG);
  Sc(SCI_MARKERSETFORE, SC_MARKNUM_FOLDEROPENMID, mFG);

  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPEN, mBG);
  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDER, mBG);
  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB, mBG);
  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL, mBG);
  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEREND, mBG);
  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDEROPENMID, mBG);
  Sc(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL, mBG);

  // Markers...Program Counter
  Sc(SCI_MARKERDEFINEPIXMAP, MK_PC, (LPARAM) xpm_ArrowIcon);
  Sc(SCI_MARKERSETFORE, MK_PC, RGB(255,255,0)); // Yellow
  Sc(SCI_MARKERSETBACK, MK_PC, RGB(255,255,0));

  // Enabled breakpoint
  Sc(SCI_MARKERDEFINEPIXMAP, MK_ENABLED_BKPT, (LPARAM)xpm_BreakpointIcon);
  Sc(SCI_MARKERSETFORE, MK_ENABLED_BKPT, RGB(68,109,140)); // Dark blue

  // Disabled breakpoint
  Sc(SCI_MARKERDEFINEPIXMAP, MK_DISABLED_BKPT, (LPARAM)xpm_DisabledBreakpointIcon);
  Sc(SCI_MARKERSETFORE, MK_ENABLED_BKPT, RGB(143,192,229)); // Light blue

  // Syntax Error
  Sc(SCI_MARKERDEFINEPIXMAP, MK_SYNTAX, (LPARAM) xpm_ErrorIcon);
  Sc(SCI_MARKERSETFORE, MK_SYNTAX, SYNTAX_ERROR_COLOR);

  // Indicators...Syntax Error
  Sc(SCI_INDICSETSTYLE, INDICATOR_SYNTAX_ERROR, INDIC_ROUNDBOX);// INDIC_SQUIGGLE
  Sc(SCI_INDICSETFORE, INDICATOR_SYNTAX_ERROR, SYNTAX_ERROR_COLOR);

  Sc(SCI_SETCARETFORE, CARET_COLOR); // Black.

  Sc(SCI_AUTOCSETSEPARATOR, '\001');   // Completions delimiter: ^A
  Sc(SCI_AUTOCSETTYPESEPARATOR, '\f'); // LISP category-menu-icon-delimiter
  Sc(SCI_AUTOCSETDROPRESTOFWORD, TRUE);
  Sc(SCI_AUTOCSETAUTOHIDE, FALSE);

  Sc(SCI_REGISTERIMAGE, 1, (LPARAM) xpm_ClassIcon);
  Sc(SCI_REGISTERIMAGE, 2, (LPARAM) xpm_ProcedureIcon);
  Sc(SCI_REGISTERIMAGE, 3, (LPARAM) xpm_VariableIcon);

  // G2-specific syntax: Permit "-" within words, ignore case.
  Sc(SCI_AUTOCSETIGNORECASE, TRUE);
  Sc(SCI_SETWORDCHARS, 0, (LPARAM)G2_WORDCHARS);
}

void G2Editor::SetupStyles()	// virtual
{
  Super::SetupStyles();

  Sc(SCI_SETSELBACK, TRUE, SELECTION_COLOR);

  if(m_colorStyles) {
    Sc(SCI_STYLESETFORE, G2S_NORMAL, EDITOR_FG);
    Sc(SCI_STYLESETFORE, G2S_MIDSTRING, EDITOR_FG);

    Sc(SCI_STYLESETFORE, G2S_COMMENT, COMMENT_COLOR);
    Sc(SCI_STYLESETFORE, G2S_COMMENT_LINE, COMMENT_COLOR);

    Sc(SCI_STYLESETFORE, G2S_STRING, STRING_COLOR);
    Sc(SCI_STYLESETFORE, G2S_KEYWORD, KEYWORD_COLOR);
    Sc(SCI_STYLESETFORE, G2S_TYPE, TYPE_COLOR);
    Sc(SCI_STYLESETFORE, G2S_NUMBER, NUMBER_COLOR);
    Sc(SCI_STYLESETFORE, G2S_SYMBOL, SYMBOL_COLOR);
    Sc(SCI_STYLESETFORE, G2S_IDENTIFIER, IDENTIFIER_COLOR);
  }

  // Bold unless fixed font
  if(!m_fixedFont) {
    Sc(SCI_STYLESETBOLD, G2S_KEYWORD, TRUE);
    Sc(SCI_STYLESETBOLD, G2S_TYPE, TRUE);
  }

  Sc(SCI_STYLESETBACK, STYLE_BRACELIGHT, BRACE_COLOR);

  Sc(SCI_CALLTIPSETBACK, RGB(255,255,225)); // Pale yellow
  Sc(SCI_CALLTIPSETFORE, RGB(0,0,0));       // Black
  Sc(SCI_CALLTIPSETFOREHLT, RGB(0,0,255));  // Blue

  RecomputeLineNumberMargin();
}



/*
 * Breakpoint Markers
 */

// Clear any sort of breakpoint on line.
void G2Editor::ClearBreakpoint(int zLine)
{
  Sc(SCI_MARKERDELETE, zLine, MK_ENABLED_BKPT);
  Sc(SCI_MARKERDELETE, zLine, MK_DISABLED_BKPT);
}

// Clear all breakpoints on all lines.
void G2Editor::ClearBreakpoints()
{
  Sc(SCI_MARKERDELETEALL, MK_ENABLED_BKPT, 0);
  Sc(SCI_MARKERDELETEALL, MK_DISABLED_BKPT, 0);
}

void G2Editor::SetBreakpoint(int zLine, BkptState state)
{
  // This could happen if the breakpoint was set by other means, such as by
  // another editor on the same procedure.
  if(IsModified()) {
    Warn(MSG_BKPT_ON_MODIFIED);
    return;
  }

  ClearBreakpoint(zLine);
  switch(state) {
   case BkptEnabled:
     Sc(SCI_MARKERADD, zLine, MK_ENABLED_BKPT);
     break;
   case BkptDisabled:
     Sc(SCI_MARKERADD, zLine, MK_DISABLED_BKPT);
     break;
   case BkptClear:
    break;
  }
}

BkptState G2Editor::GetBreakpoint(int zLine)
{
  int mask = Sc(SCI_MARKERGET, zLine, 0);

  if(mask & (1<<MK_ENABLED_BKPT))
    return BkptEnabled;
  else if (mask & (1<<MK_DISABLED_BKPT))
    return BkptDisabled;
  else
    return BkptClear;
}

// bkpts is a null-terminated wide string as created by Lisp
// fixnum-list-to-word-vector. Least-significant word first, 15 bits/word.
void G2Editor::SetBreakpoints(unsigned short *bkpts)
{
  int i, bkpt, zLine;
  BkptState state;

  if(IsModified()) {
    Warn(MSG_BKPT_ON_MODIFIED);
    return;
  }

  ClearBreakpoints();
  for(i=0; bkpts[i]; i+=2) {
    bkpt = ((bkpts[i+1] & 0x7FFF) << 15) | (bkpts[i] & 0x7FFF);
    zLine = (bkpt & 0xFFFFF) - 1;
    state = (bkpt & DISABLED_BREAKPOINT_FLAG) ? BkptDisabled : BkptEnabled;
    SetBreakpoint(zLine, state);
  }
}

// Returns newly malloced array of breakpoint line numbers and states, in the
// format LISP word-vector-to-fixnum-list understands.
LPWSTR G2Editor::GetBreakpoints()
{
  int zLine, i, n, line;
  LPWSTR bkpts;

  n=0;
  zLine = -1;
  while((zLine = Sc(SCI_MARKERNEXT, zLine+1, MK_BKPT_MASK)) >= 0)
    n++;

  if(n==0) return NULL;

  bkpts = (LPWSTR) calloc(2*n+1, sizeof(wchar_t));
  if(bkpts == NULL) return NULL;

  i=0;
  zLine = -1;
  while((zLine = Sc(SCI_MARKERNEXT, zLine+1, MK_BKPT_MASK)) >= 0) {
    line = zLine + 1;
    if(GetBreakpoint(zLine) == BkptDisabled)
      line |= DISABLED_BREAKPOINT_FLAG;
    bkpts[i++] = 0x8000 | (line & 0x7FFF);
    bkpts[i++] = 0x8000 | ((line>>15) & 0x7FFF);
  }
  bkpts[i++] = 0;		// Must be nul terminated
  return bkpts;
}

// Execute a breakpoint command. Used by editor and debugger.
void G2Editor::BreakpointCommand(int opcode, int zLine, LPWSTR bkpts)
{
  BOOL modified = IsModified();

  switch(opcode) {
   case EDITOR_SET_BREAKPOINT:
     if(!modified) SetBreakpoint(zLine, BkptEnabled);
     break;

   case EDITOR_CLEAR_BREAKPOINT:
     if(!modified) SetBreakpoint(zLine, BkptClear);
     break;

   case EDITOR_DISABLE_BREAKPOINT:
     if(!modified) SetBreakpoint(zLine, BkptDisabled);
     break;

   case EDITOR_SET_BREAKPOINTS:
     if(!modified) SetBreakpoints(bkpts);
     break;

   case EDITOR_CLEAR_BREAKPOINTS:
     if(!modified) ClearBreakpoints();
     break;
  }
}

// Return opcode to move breakpoint to its next state, as we define "next".
int G2Editor::OpcodeToCycleBreakpoint(int zLine)
{
  BkptState state = GetBreakpoint(zLine);
  switch(state) {
   case BkptClear: return EDITOR_SET_BREAKPOINT;
   case BkptEnabled: return EDITOR_DISABLE_BREAKPOINT;
   case BkptDisabled: return EDITOR_CLEAR_BREAKPOINT;
  }
  return 0;
}



/*
 * G2 Syntax Highlighting
 */

/* Reference: g2-standard-tokens, in alphabet.lisp */

#define COMMENT_START '{'
#define COMMENT_END '}'
#define COMMENT_LINE_START '/'	// Plus another slash, of course.
#define STRING_START '"'
#define STRING_END '"'
#define BRACKET_START '['
#define BRACKET_END ']'
#define ESCAPE_CHAR '@'
#define ARGLIST_START '('
#define CLASS_QUALIFIER_CHAR ':' // Plus another one, of course.

static char *g2_keywords[] = {"begin", "end", "if", "then", "else", "for", "do",
			      "start", "call", "when", "whenever", "and", "or",
			      "case", "exit", "signal", "return", "repeat",
			      /* "go to", "on error", */
			      "true", "false", NULL};

static char *g2_types[] = {"truth-value", "symbol", "text", "quantity", "value",
			   "item-or-value", "sequence", "structure",
			   "time-stamp", "long", "integer", "float", "class",
			   NULL};


// Approximate inverse of characters-not-allowed-in-symbols-in-g2-50r0
inline BOOL G2Editor::IsIdentifierStart(int ch)
{
  return ch>=0x80 || isalnum(ch) || strchr("'-._@",ch);
}

inline BOOL G2Editor::IsIdentifierConstituentAt(int ch, int i)
{
  return ch>=0x80 || isalnum(ch) || strchr("'-._@",ch) ||
    (ch == CLASS_QUALIFIER_CHAR &&
     ((i>0          && CH(i-1) == CLASS_QUALIFIER_CHAR) ||
      (i<Length()-1 && CH(i+1) == CLASS_QUALIFIER_CHAR)));
}

BOOL G2Editor::IsIdentifierAt(int i)
{
  int style = STYLE(i);
  return style == G2S_IDENTIFIER || style == G2S_KEYWORD || style == G2S_TYPE || style == G2S_SYMBOL;
}

BOOL G2Editor::IsNormal(int i)
{
  int style = STYLE(i);
  return !(style == G2S_COMMENT || style == G2S_COMMENT_LINE || style == G2S_STRING);
}

BOOL G2Editor::IsSpaceAt(int i)
{
  return isspace(CH(i)) && STYLE(i)==G2S_NORMAL;
}

// Return the position of the beginning of the current word, assuming pos is
// either within, or immediately after the word.
int G2Editor::BeginningOfWord(int pos/*=-1*/)
{
  int i;

  i = (pos>=0) ? pos : POS();

  if(i>0 && IsIdentifierAt(i-1) && !IsIdentifierAt(i))
    i--;

  for(; i>=0 && IsIdentifierAt(i); i--) ;
  return i+1;
}

char *G2Editor::GetTokenAtPoint(int pos/*=-1*/)
{
  int i = BeginningOfWord(pos);
  int j;

  j=i;
  while(IsIdentifierAt(j) && j<Length())
    j++;

  return (i<j) ? GetTextRange(i,j) : NULL;
}

char *G2Editor::GetPreviousToken(int *pPos, int *pEnd /*=NULL*/)
{
  int i,j;

  i=*pPos;
  while(IsIdentifierAt(i) && i>=0)
    i--;

  while(!IsIdentifierAt(i) && i>=0)
    i--;

  j=i+1;
  while(IsIdentifierAt(i) && i>=0)
    i--;

  i++;
  if(i<j) {
    *pPos = i;
    if(pEnd) *pEnd = j;
    return GetTextRange(i,j);
  } else {
    return NULL;
  }
}

BOOL G2Editor::PreviousTokenEqual(LPCSTR token, int *pPos)
{
  int pos = *pPos;
  char *prev = GetPreviousToken(&pos);
  BOOL rc = prev && stricmp(prev, token) == 0;

  free(prev);
  if(rc) {
    *pPos = pos;
    return TRUE;
  } else {
    return FALSE;
  }
}

// Re-reverse-search for "identifier+ *(", skipping over comments, strings, and
// balanced parentheses. String is newly alloced.
char *G2Editor::GetPreviousCall(int pos, int *start, int *end)
{
  int i,j,ch,brace=0;
  int len = Length();

  // First try to find the function, assuming we are inside the body of the
  // function's argument list.
  i=pos;
  if(IsNormal(i) && CH(i) == ')') i--;

  for(i=i; i>0; i--) {
    if(!IsNormal(i))
      continue;
    ch = CH(i);
    if(ch == '(' && brace==0)
      break;
    else if(ch == ')' || ch == ']')
      brace++;
    else if(ch == '(' || ch == '[')
      brace--;
  }

  for(i=i-1; i>0 && IsSpaceAt(i); i--) ;
  for(j=i; j>=0 && IsIdentifierAt(j); j--) ;

  // If that failed, try to find function assuming we are between the start of
  // the function name and the open paren.

  if(i==j) {
    for(i=pos; IsIdentifierAt(i) && i<len; i++) ;
    for(i=i; IsSpaceAt(i) && i<len; i++) ;
    if(CH(i) == '(') {
      for(i=i-1; IsSpaceAt(i) && i>=0; i--) ;
      for(j=i; IsIdentifierAt(j) && j>=0; j--) ;
    } else {
      i=j;
    }
  }

  if(start) *start = j+1;
  if(end) *end = i+1;

  return GetTextRange(*start, *end);
}

// Given pos is within the extent of a call to fun, return the argument number
// it is within, starting from 1, or 0 if inside the text of fun itself.
//  Start here is the start of the function name, eg, the f in foobar(x, y, z)
int G2Editor::ComputeArgumentNumber(int start, int pos)
{
  int i,ch;
  int any = 0;
  int brace = 0;
  int comma = 0;

  // When the caret is at pos, CH(pos) is the following char, which we don't
  // care about.
  for(i=start; i<pos; i++) {
    if(IsNormal(i)) {
      ch = CH(i);
      if(ch == '(')
	any++;
      if(ch == '(' || ch == '[')
	brace++;
      else if(ch == ')' || ch == ']')
	brace--;
      else if(ch == ',' && brace == 1)
	comma++;
    }
  }

  if(brace == 0)
    return pos<start ? -1 : any>0 ? -1 : 0;
  else
    return comma+1;
}

// Return positions in a CALLTIP (i.e., NOT something in the edit buffer) which
// delimit argument number N, counting from 1. Calltip is ALWAYS of the form:
//
//    fun (arg:type, ..., arg:type) => (type, ... type)
//
// where the return types are optional

static void DelimitArgInCalltip(char *calltip, int n, int *start, int *end)
{
  char *s, *e;

  s = calltip;
  e = strchr(calltip, '(');

  while(e != NULL && n>0) {
    s=e+1;
    e=strchr(s,',');
    n--;
  }
  if(e == NULL) e = strchr(calltip,')');
  if(e == NULL) e = calltip + strlen(calltip); // This should never happen.
  *start = s - calltip;
  *end   = e - calltip;
}

// Highlight current argument. TODO: Need to resize the window.
void G2Editor::UpdateCalltip(int funPos, char *calltip)
{
  int pos, arg; //, start, end;
  if(!Sc(SCI_CALLTIPACTIVE, 0, 0))
    return;

  pos = POS();

  if(calltip == NULL)
    return;

  arg = ComputeArgumentNumber(funPos, pos);
  if(arg < 0)
    Sc(SCI_CALLTIPCANCEL, 0, 0);
  else {
	//{{suzsoft changed for Gensym 347
    //DelimitArgInCalltip(calltip, arg, &start, &end);
    //Sc(SCI_CALLTIPSETHLT, start, end);
	//only send the number of the argument signatures that need highlight
	Sc(SCI_CALLTIPSETHLT, arg);
	//}}
  }
}

BOOL G2Editor::QuotedSymbolContext(int pos)
{
  int p;

  p=pos;
  if(PreviousTokenEqual("is", &p))
    return TRUE;

  p=pos;
  if(PreviousTokenEqual("not", &p) && PreviousTokenEqual("is", &p))
    return TRUE;

  p=pos;
  if(PreviousTokenEqual("symbol", &p) && PreviousTokenEqual("the", &p))
    return TRUE;
  return FALSE;
}

G2LexerState G2Editor::ClassifyToken(LPCSTR token, int pos)
{							//added by SoftServe
  if(g2pvt_is_number(token) || g2pvt_is_long_number(token))
    return G2S_NUMBER;

  else if(QuotedSymbolContext(pos))
    return G2S_SYMBOL;

  else if(word_in_list(token,g2_keywords)) // TODO: hash table
    return G2S_KEYWORD;

  else if(word_in_list(token,g2_types))
    return G2S_TYPE;

  else
    return G2S_IDENTIFIER;
}

// Change the style of characters start thru end (exclusive), which all have the
// same lexical type (state), to the the appropriate Scintilla style.
void G2Editor::Style(int start, int end, G2LexerState state)
{
  G2LexerState style;
  char *token;

  if(start >= end)
    return;

  style = state;
  switch(state) {
   case G2S_IDENTIFIER:
     token = GetTextRange(start,end);
     style = ClassifyToken(token, start);
     free(token);
     break;
  }

  Sc(SCI_SETSTYLING, end - start, style);
}

#define MaxStack 50
#define PushToState(newState) if(tos<MaxStack) stack[tos++] = state; nextState = (newState)
#define PopState() nextState = (tos>0) ? stack[--tos] : G2S_NORMAL

/*
 * G2Colorize -- Apply G2 standard syntax highlighting.
 */
void G2Editor::G2Colorize(int start, int end)
{
  int anchor, i, ch, skip, tos;
  BOOL escape;
  G2LexerState state, nextState, stack[MaxStack];

  /* Backup until we reach a NORMAL state. We could avoid backing up in most
   * cases by adding a few more states, but it's probably not worthwhile. See
   * the bash lexer, for example, which also does this. */

  while(start>0 && STYLE(start-1) != G2S_NORMAL)
    start--;

  state = (G2LexerState) ((start > 0) ? STYLE(start-1) : G2S_NORMAL);
  escape = (start > 0) ? (CH(start-1) == ESCAPE_CHAR) : FALSE;
  tos = 0;

  nextState = state;
  anchor = i = start;
  Sc(SCI_STARTSTYLING, start, 31);
  while(i<end) {
    // Compute nextState, anchor=first char in it, i=next char to scan.
    skip = 0;
    switch(state) {
     case G2S_NORMAL:
       while(i<end && nextState==state) {
	 ch = CH(i);
	 switch(ch) {
	  case COMMENT_START:
	    PushToState(G2S_COMMENT);
	    continue;		// ch in new state
	  case STRING_START:
	    PushToState(G2S_STRING);
	    skip=1;
	    continue;		// ch in new state
	  case COMMENT_LINE_START:
	    if(m_singleLineComments && i<end-1 && CH(i+1) == COMMENT_LINE_START) {
	      PushToState(G2S_COMMENT_LINE);
	      continue;
	    }
        /* Fall through */
	  default:
	    if(IsIdentifierStart(ch)) {
	      PushToState(G2S_IDENTIFIER);
	      continue;		// ch in new state
	    }
	 }
	 i++;
       }
     case G2S_STRING:
       while(i<end && nextState==state) {
	 ch = CH(i);
	 if(escape)
	   escape = FALSE;
	 else
	   switch(ch) {
	    case ESCAPE_CHAR:
	      escape = TRUE;
	      break;
	    case STRING_END:
	      PopState();
	      break;		// ch in old state.
	    case BRACKET_START:
	      PushToState(G2S_MIDSTRING);
	      continue;		// ch in new state.
	   }
	 i++;
       }
       break;
     case G2S_MIDSTRING:
       while(i<end && nextState==state) {
	 ch = CH(i);
	 switch(ch) {
	  case COMMENT_START:
	    PushToState(G2S_COMMENT);
	    continue;		// ch in new state
	  case STRING_START:
	    PushToState(G2S_STRING);
	    skip=1;
	    continue;		// ch in new state
	  case BRACKET_END:
	    PopState();
	    break;		// ch in old state.
	  case COMMENT_LINE_START:
	    if(m_singleLineComments && i<end-1 && CH(i+1) == COMMENT_LINE_START) {
	      PushToState(G2S_COMMENT_LINE);
	      continue;
	    }
    /* Fall through */
	  default:
	    if(IsIdentifierStart(ch)) {
	      PushToState(G2S_IDENTIFIER);
	      continue;
	    }
	 }
	 i++;
       }
     case G2S_IDENTIFIER:
       while(i<end && nextState==state) {
	 ch = CH(i);
	 if(escape)
	   escape = FALSE;
	 else if(ch == ESCAPE_CHAR)
	   escape = TRUE;
	 else if(!IsIdentifierConstituentAt(ch,i)) {
	   PopState();
	   continue;		// ch in new state
	 }
	 i++;
       }
       break;
     case G2S_COMMENT:
       while(i<end && CH(i) != COMMENT_END) i++;
       escape = FALSE;
       PopState();
       i++;
       break;
     case G2S_COMMENT_LINE:
       i = GetEol(i);		// Go directly to end of line
       escape = FALSE;
       PopState();
       break;
    }
    Style(anchor, i, state);
    state = nextState;
    anchor=i;
    i += skip;
  }
  Style(anchor, i, state);
}



/*
 * G2 Folding
 */

// For procedures, a simple algorithm: increment folding level for BEGIN, CASE,
// COLLECT, DO, END ON ERROR, and REPEAT. Decrement only on END.

BOOL G2Editor::IsFoldBegin(LPCSTR token, int pos)
{
  static char *begins[] = {"begin", "case", "collect", "do", "repeat", NULL};

  if(word_in_list(token, begins))
    return TRUE;
  else if(!stricmp(token,"error") &&
	  PreviousTokenEqual("on",&pos) &&
	  PreviousTokenEqual("end",&pos))
    return TRUE;
  else
    return FALSE;
}

BOOL G2Editor::IsFoldEnd(LPCSTR token, int pos)
{
  return stricmp(token,"end") == 0;
}

void G2Editor::G2Fold(int start, int end)
{
  int i, j, ch, style;
  int line = Sc(SCI_LINEFROMPOSITION, start);
  int levelPrev = Sc(SCI_GETFOLDLEVEL, line) & SC_FOLDLEVELNUMBERMASK;
  int level = levelPrev;
  BOOL blank = TRUE;
  BOOL eolp;
  char token[32];		// Large enough for any keyword.

  j = 0;
  for(i=start; i<end; i++) {
    ch = CH(i);
    eolp = (ch == '\n');
    style = STYLE(i);

    if(style == G2S_KEYWORD || style == G2S_IDENTIFIER) { // NOTE: Not including G2S_SYMBOL
      if(j<sizeof(token)-1)
	token[j++] = ch;

    } else if(j > 0) {
      token[j++] = '\0';
      j = 0;
      if(IsFoldBegin(token, i-1))
	level++;
      else if(IsFoldEnd(token, i-1))
	level--;
    }

    if(eolp) {
      int lev = levelPrev;

      if(blank)
	lev |= SC_FOLDLEVELWHITEFLAG;
      else if(level > levelPrev)
	lev |= SC_FOLDLEVELHEADERFLAG;
      if(lev != Sc(SCI_GETFOLDLEVEL, line))
	Sc(SCI_SETFOLDLEVEL, line, lev);

      line++;
      levelPrev = level;
      blank = TRUE;
    }
    if(!isspace(ch))
      blank = FALSE;
  }

  // Fill in the real level of the next line, keeping the current flags as they
  // will be filled in later
  int flagsNext = Sc(SCI_GETFOLDLEVEL, line) & ~SC_FOLDLEVELNUMBERMASK;
  Sc(SCI_SETFOLDLEVEL, line, level | flagsNext);
}



/*
 * Event handlers
 */

// Returns TRUE if key was handled. Not allowed to enter a modal loop here.
void G2Editor::EditKeyPress(UINT key)   // virtual
{
  int pos = POS();
  m_consumedKey = TRUE;
  switch(key) {
   case VK_ESCAPE:
     if(Sc(SCI_AUTOCACTIVE))
       Sc(SCI_AUTOCCANCEL);
     else if(Sc(SCI_CALLTIPACTIVE))
       Sc(SCI_CALLTIPCANCEL);
     else if(Sc(SCI_GETANCHOR) != POS())
       Sc(SCI_SETSEL, -1, POS());
     else
       OnEditCancel();		// Unhandled Escape
     break;

   case Ctrl+VK_OEM_PLUS:
     Sc(SCI_ZOOMIN);
     break;

   case Ctrl+VK_OEM_MINUS:
     Sc(SCI_ZOOMOUT);
     break;

   case Ctrl+'F':
     OnEditFind();
     break;

   case Ctrl+'H':
     OnEditReplace();
     break;

   case VK_F1:
     EditorMsg(MSG_KEYBOARD_HELP); // TODO: Post full help window.
     break;

   case VK_F3:
     OnEditFindNext();
     break;

   case Ctrl+VK_SPACE:
     // Beep if completions are requested "within" a comment or a string. We are
     // "within" only if chars at both pos-1 and pos have either comment or
     // string style.
     if(m_grammar == FreeText)
       Beep();
     else if(pos==0 || IsNormal(pos-1) || IsNormal(pos))
       RequestCompletions();
     else
       Beep();
     break;

   case Ctrl+Shift+VK_SPACE:
     if(m_grammar == FreeText)
       Beep();
     else if(pos>0 && (IsNormal(pos-1) || IsNormal(pos)))
       RequestArglist(POS());
     else
       Beep();
     break;

   case Ctrl+VK_F2:
     ToggleFont();
     if(GetOutputWnd()) GetOutputWnd()->ToggleFont(); // Kludgey
     break;

   case Ctrl+VK_F3:
     ToggleLineNumbers();
     break;
				// Ctrl+F4 = close window!
   case Ctrl+VK_F5:
     ToggleColorStyles();
     break;
				// Ctrl+F6 = next window!
   case Ctrl+VK_F7:
     ToggleIconsMargin();
     break;

   case Ctrl+VK_F8:
     ToggleFoldingMargin();
     break;

   case Ctrl+Shift+VK_F9:	// Undocumented
     ToggleWhitespace();
     break;

   case VK_RETURN:
     if(Sc(SCI_AUTOCACTIVE))	// Let autocomplete listbox have it.
       m_consumedKey = FALSE;
     else if(m_singleLineMode)
       OnEditOK();
     else if(m_grammar != FreeText)
       NewlineAndIndent();
     else
       m_consumedKey = FALSE;
     break;

   case Ctrl+VK_RETURN:
     OnEditOK();
     break;

   case Ctrl+Shift+VK_RETURN:
     OnFileSave();
     break;

#ifdef DEBUG_COLORIZER
   case Ctrl+'D':
     {
       DumpBuf();
       for(int line=0; line<Sc(SCI_GETLINECOUNT); line++)
	 g2pvt_printf("[%2d] %04x %s\n", line+1, Sc(SCI_GETFOLDLEVEL,line), GetLine(line));
     }
     break;
#endif

   default:
     m_consumedKey = FALSE;
     break;
  }
}

void G2Editor::MarginClick(int margin, int pos, int modifiers) // virtual
{
  if(m_grammar != Procedure) {
    Beep();
    return;
  }

  int line = Sc(SCI_LINEFROMPOSITION, pos);
  switch(margin) {
   case MARGIN_ICONS:
     if(modifiers == 0)
       if(IsModified())
	 Warn(MSG_BKPT_ON_MODIFIED);
       else
	 FireEvent(OpcodeToCycleBreakpoint(line), line+1);
     break;

   case MARGIN_FOLD:
     if(modifiers == 0)
       if(Sc(SCI_GETFOLDLEVEL, line) & SC_FOLDLEVELHEADERFLAG)
	 Sc(SCI_TOGGLEFOLD, line);
     break;
  }
}

void G2Editor::OnUpdateUI(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;
  int pos = POS();

  if(m_remove_syntax_error) {
    ClearSyntaxError();
    m_remove_syntax_error = FALSE;
  }

  if(Sc(SCI_CALLTIPACTIVE))
    UpdateCalltip(m_calltip_start, m_calltip);

  if(m_incrementalUpdates && pos != m_cursor) {
    if(m_syntax_error_marker >= 0)
      ClearSyntaxError();
    CursorMoved(pos);
  }

  // FIXME: Only if grammar == Procedure?
  HighlightBrace(g2pvt_is_brace(CH(pos-1)), pos-1);

#ifdef DEBUG_CARET
  DebugCaret();
#endif
}

void G2Editor::OnCharAdded(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;
  int pos = POS()-1;

  if(m_grammar == FreeText)
    ;
  else if(scn->ch == ARGLIST_START && pos>0 && IsNormal(pos-1))
    RequestArglist(pos);
  // TODO: Check for "...end" and highlight matching.
}

void G2Editor::OnModified(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;

  if(!m_incrementalUpdates)
    ;

  else if(scn->modificationType & SC_MOD_INSERTTEXT)
    TextInserted(scn->position, scn->text, scn->length);

  else if(scn->modificationType & SC_MOD_BEFOREDELETE)
    TextDeleted(scn->position, scn->length);
}

void G2Editor::OnChange()
{
  // Scintilla prevents any document changes, whether text or style,
  // during an SCEN_CHANGE event. So we have to undo the syntax error
  // highlighting later, in UPDATEUI.
  if(m_syntax_error_marker >= 0)
    m_remove_syntax_error = TRUE;
}

void G2Editor::OnStyleNeeded(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;
  if(m_grammar == FreeText)
    return;

  int start = Sc(SCI_GETENDSTYLED);
  int end = scn->position;
  int line = Sc(SCI_LINEFROMPOSITION, start);
  start = Sc(SCI_POSITIONFROMLINE, line);

  G2Colorize(start, end);

  // Move back one line in case deletion wrecked current line fold state (Copied
  // from LexerModule::Fold()
  if (line > 0)
    start = Sc(SCI_POSITIONFROMLINE, --line);

  G2Fold(start, end);
}



/*
 * Commands
 */

void G2Editor::OnEditUndo()
{
  // GENSYMCID-844: request updating the value of maxUndoSteps.
  FireEvent(EDITOR_UNDO, maxUndoSteps);
  CScintillaWnd::OnEditUndo();
}

void G2Editor::OnEditOK()
{
  GetMainWnd()->EnableWindow(TRUE);
  CommitChanges(TRUE);		// Try to end editing.
}

void G2Editor::OnUpdateEditOK(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(!IsSuspended());
}

void G2Editor::OnEditCancel()
{
  GetParentFrame()->PostMessage(WM_CLOSE);
}

void G2Editor::OnFileSave()
{
  CommitChanges(FALSE);
}

void G2Editor::OnUpdateFileSave(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(IsModified() && !IsSuspended());
}

void G2Editor::ToggleColorStyles()
{
  m_colorStyles = !m_colorStyles;
  SetupStyles();
}

void G2Editor::ToggleIconsMargin()
{
  if(Sc(SCI_GETMARGINWIDTHN, MARGIN_ICONS) == 0)
    Sc(SCI_SETMARGINWIDTHN, MARGIN_ICONS, MARGIN_ICONS_WIDTH);
  else
    Sc(SCI_SETMARGINWIDTHN, MARGIN_ICONS, 0);
}

void G2Editor::ToggleFoldingMargin()
{
  if(Sc(SCI_GETMARGINWIDTHN, MARGIN_FOLD) == 0)
    Sc(SCI_SETMARGINWIDTHN, MARGIN_FOLD,  MARGIN_FOLD_WIDTH);
  else
    Sc(SCI_SETMARGINWIDTHN, MARGIN_FOLD, 0);
}

void G2Editor::NewlineAndIndent()
{
  int pos = POS();
  int thisStyle = STYLE(max(0,pos-1));
  int nextStyle = STYLE(pos);
  int line = Sc(SCI_LINEFROMPOSITION, pos);
  int indent = Sc(SCI_GETLINEINDENTATION, line);

  Sc(SCI_BEGINUNDOACTION);
  Sc(SCI_ADDTEXT, 1, (LPARAM)"\n");

  // TODO: Want IndentLine here, but we don't have that yet. So do the dumb
  // thing and just match the preceding line's indentation.
  if(thisStyle == G2S_NORMAL || nextStyle == G2S_NORMAL || thisStyle == G2S_COMMENT_LINE) {
    Sc(SCI_SETLINEINDENTATION, line+1, indent);
    SETPOS(Sc(SCI_GETLINEINDENTPOSITION, line+1));
  }
  Sc(SCI_ENDUNDOACTION);
}

void G2Editor::OnGotoItem()
{
  char *token = HasSel() ? GetSel() : GetTokenAtPoint();

  if(token) {
    LPWSTR wtoken = g2pvt_to_gensym_unicode(token, -1, NULL);
    FireEvent(EDITOR_GOTO_ITEM, caret_from_pos(POS()), wtoken);
    free(token);
    free(wtoken);
  } else {
    Beep();
  }
}

void G2Editor::OnUpdateGotoItem(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(HasSel() || Length()>0); // TODO: Something better here.
}



/*
 * More Commands
 */

// TODO: In general, we should re-colorize here. But not needed yet.
void G2Editor::SetGrammer(Grammar gram)
{
  if(m_grammar == gram)
    return;
  m_grammar = gram;
  if(m_grammar == Procedure)	// Any grammar that has completions & arglists.
    EditorMsg(MSG_MINIHELP);
}

void G2Editor::SetOptions(int mask)
{
  m_singleLineComments = (mask&EDITOR_OPTIONS_SINGLE_LINE_COMMENTS) != 0;
  m_singleLineMode = (mask&EDITOR_OPTIONS_SINGLE_LINE_EDITOR) != 0;
  m_queryClose = (mask&EDITOR_OPTIONS_QUERY_ON_CLOSE) != 0;
}

void G2Editor::EnableIncrementalUpdates(BOOL enable)
{
  m_incrementalUpdates = enable;

  if(m_incrementalUpdates)
    Sc(SCI_SETMODEVENTMASK, EDITOR_EVENT_MASK);
  else
    Sc(SCI_SETMODEVENTMASK, 0);
}

void G2Editor::SuspendEditor()
{
  SetReadOnly(TRUE);
  m_disabled = TRUE;
}

void G2Editor::ResumeEditor()
{
  SetReadOnly(FALSE);
  m_disabled = FALSE;
}

BOOL G2Editor::IsSuspended()
{
  return m_disabled;
}

// Acknowledgement from G2 that text was saved, with optional note.
void G2Editor::TextSaved(LPCWSTR wstr)
{
  Sc(SCI_SETSAVEPOINT);
  EditorMsg(wstr);
}

void G2Editor::ShowCompletionsPopup(LPWSTR wstr)
{
  if(wcslen(wstr) == 0)
    return;

  char *str = g2pvt_to_utf8(wstr);
  int pos = POS();

  // NOTE: This assumes that the completions G2 provides always start at the
  // beginning of the current token. That's not true, at least in the presence
  // of class qualified symbols. But since we now perform the completion
  // insertion ourselves, by asking G2 in OnAutoComplete(), all the len
  // parameter is used for is to initially select a matching item in the
  // list. The fact that that is wrong sometimes is unfortunate but not a big
  // deal. -fmw, 3/29/07
  int len = pos - BeginningOfWord(pos);
  if(len < 0) len = 0;
  Sc(SCI_AUTOCSHOW, len, (LPARAM)str);
  free(str);
}

// Inserts the completion by asking G2 to do it, thus getting all the
// replace-fragments-on-sides goodness (and badness).
void G2Editor::InsertCompletion(LPCSTR str)
{
  LPWSTR wstr = g2pvt_to_gensym_unicode(str, -1, NULL);
  int pos = POS();
  FireEvent(EDITOR_HOTSPOT_CLICKED, caret_from_pos(pos), wstr, G2S_COMPLETION);
  free(wstr);
}

void G2Editor::OnAutoComplete(NMHDR *pNotifyStruct, LRESULT* result)
{
  struct SCNotification *scn = (struct SCNotification *)pNotifyStruct;
  InsertCompletion(scn->text);
  Sc(SCI_AUTOCCANCEL);
}

void G2Editor::ShowCalltip(LPWSTR wstr)
{
  Sc(SCI_CALLTIPCANCEL);

  // No arglist found for token. This happens when typing an lparen just in an
  // arithmetic expression, for example. The beeping is very annoying
  if(wcslen(wstr) == 0)
    return;

  if(m_calltip)
    free(m_calltip);

  char *calltip = g2pvt_to_utf8(wstr);
  int columns = ApproxEditorWidthInColumns();

  // Show all lines of the calltip.
  char *wrapped = g2pvt_wrap_words(calltip, columns);
  Sc(SCI_CALLTIPSHOW, m_calltip_start, (LPARAM)wrapped);
  free(wrapped);

  // But do arg highlighting based only on the first line.
  char *nl = strchr(calltip, '\n');
  if(nl) *nl = '\0';
  m_calltip = g2pvt_wrap_words(calltip, columns);
  free(calltip);

  UpdateCalltip(m_calltip_start, m_calltip);
}

void G2Editor::ShowSyntaxError(int caret, LPCWSTR msg)
{
  if(wcslen(msg) == 0)
    return;

  int start = max(0,pos_from_caret(caret) - 1);
  int zLine = Sc(SCI_LINEFROMPOSITION, start);
  int len = max(0,min(Length()-start, 2));

  m_syntax_error_marker = Sc(SCI_MARKERADD, zLine, MK_SYNTAX);
  if(start>=0 && len>0) {	// Paranoia. Scintilla already handles this.
    Sc(SCI_STARTSTYLING, start, INDIC0_MASK);
    Sc(SCI_SETSTYLING, len, INDIC0_MASK);
  }
  EditorMsg(msg);
}

void G2Editor::ClearSyntaxError()
{
  int zLine = Sc(SCI_MARKERLINEFROMHANDLE, m_syntax_error_marker);
  int start = Sc(SCI_POSITIONFROMLINE, zLine);
  int len = Sc(SCI_LINELENGTH, zLine);

  if(zLine>=0)			// Paranoia
    Sc(SCI_MARKERDELETE, zLine, MK_SYNTAX);

  if(start>=0 && len>0) {	// Paranoia
    Sc(SCI_STARTSTYLING, start, INDIC0_MASK);
    Sc(SCI_SETSTYLING, len);
  }
  m_syntax_error_marker = -1;

  EditorMsg(L"");
}

void G2Editor::RequestCompletions()
{
  int caret;

  if(m_incrementalUpdates) {
    caret = caret_from_pos(POS());
    FireEvent(EDITOR_COMPLETIONS_NEW, caret);
  } else {
    LPWSTR string = GetUnicodeText(&caret);
    FireEvent(EDITOR_COMPLETIONS, caret, string);
    free(string);
  }
}

void G2Editor::RequestArglist(int pos)
{
  int start, end;
  char *token = GetPreviousCall(pos, &start, &end);
  LPWSTR wtoken;

  if(token[0] == '\0') {
    Beep();
    free(token);
    return;
  }

  m_calltip_start = start;

  wtoken = g2pvt_to_gensym_unicode(token, -1, NULL);
  FireEvent(EDITOR_ARGLIST, caret_from_pos(pos), wtoken);
  free(token);
  free(wtoken);
}

void G2Editor::CursorMoved(int pos)
{
  m_cursor = pos;		// Last one sent.
  FireEvent(EDITOR_CURSOR_MOVED, caret_from_pos(pos));
}

void G2Editor::TextInserted(int pos, LPCSTR text, int len)
{
  LPWSTR wstr = g2pvt_to_gensym_unicode(text, len, NULL);
  FireEvent(EDITOR_TEXT_INSERTED, caret_from_pos(pos), wstr);
  free(wstr);
}

void G2Editor::TextDeleted(int pos, int len)
{
  FireEvent(EDITOR_TEXT_DELETED, caret_from_pos(pos), NULL, caret_from_pos(pos+len));
}

int G2Editor::Checksum()
{
  LPWSTR wstr = GetUnicodeText();
  for(int sum = 0; *wstr; wstr++)
    sum += *wstr;
  free(wstr);
  return sum & 0xFFFFFFF;
}

// Try to commit changes. G2 decides whether to accept them. Note that we can't
// declare ourself unmodified until G2 accepts the text.
void G2Editor::CommitChanges(BOOL exit_p)
{
  int opcode, caret;
  LPWSTR text;

  if(IsSuspended())
    return;

  /* Remove any current error in prep for new one. */
  if(m_syntax_error_marker >= 0)
    ClearSyntaxError();

  EditorMsg(MSG_APPLYING_CHANGES);

  // If we aren't modified, then breakpoint changes were already sent to G2, as
  // the changes were made. The only pending changes we might have here are due
  // to the user inserting and deleting lines.
  if(IsModified()) {
    LPWSTR bkpts = GetBreakpoints();
    if(bkpts) {
      FireEvent(EDITOR_SET_BREAKPOINTS, 0, bkpts);
      free(bkpts);
    }
  }

  if(m_incrementalUpdates) {
    opcode = exit_p ? EDITOR_EXIT_NEW : EDITOR_APPLY_NEW;
    caret = caret_from_pos(POS());
    FireEvent(opcode, caret);
  } else {
    opcode = exit_p ? EDITOR_EXIT : EDITOR_APPLY;
    text = GetUnicodeText(&caret);
    FireEvent(opcode, caret, text);
    free(text);
  }
}

BOOL G2Editor::QueryClose()
{
  if(IsSuspended()) {
    EditorBeep();
    return FALSE;
  }

  if(!IsModified())
    return TRUE;

  if(!m_queryClose)
    return TRUE;

  // When auto close without changes, skip the confirm message board.
  if(m_autoclose == TRUE)
  {
    m_autoclose = FALSE;
    return TRUE;
  }
  g2pvt_enter_modal_loop();
  int rc = MessageBox(_T(MSG_SAVE_CHANGES_P), _T("G2 Editor"), MB_ICONWARNING | MB_YESNOCANCEL);
  g2pvt_exit_modal_loop();

  switch(rc) {
   case IDYES:
     OnEditOK();		// Save changes, but don't close until G2 says Ok.
   case IDCANCEL:
     return FALSE;
  }
  return TRUE;
}

void G2Editor::OnContextMenu(CWnd* pWnd, CPoint pt)
{
  if(m_contextMenuID == 0) {
    Default();
    return;
  }

  CWnd *pFrame = GetMainWnd();
  if(GetEditorWnd())
    pFrame = GetEditorWnd();

  CMenu menu;
  if(!menu.LoadMenu(m_contextMenuID))
    return;

  if ((pt.x == -1) && (pt.y == -1)) { // Posted via keyboard, so display menu near caret
    pt.x = Sc(SCI_POINTXFROMPOSITION, 0, POS());
    pt.y = Sc(SCI_POINTYFROMPOSITION, 0, POS());
    ClientToScreen(&pt);
  } else if(!HasSel()) {	      // Else, move caret to mouse click,
    CPoint q = pt;		      //  but only if selection is empty.
    ScreenToClient(&q);
    int pos = Sc(SCI_POSITIONFROMPOINTCLOSE, q.x, q.y);
    if(pos>=0)
      SETPOS(pos);
  }

  g2pvt_enter_modal_loop();
  GetCommandBars()->TrackPopupMenu(&menu, TPM_RIGHTBUTTON, pt.x, pt.y, pFrame);
  g2pvt_exit_modal_loop();
}



/*
 * Debugging
 */

#ifdef DEBUG_COLORIZER

static char *LexName(G2LexerState state)
{
  switch(state) {
   case G2S_NORMAL: return "NORMAL";
   case G2S_COMMENT: return "COMMENT";
   case G2S_COMMENT_LINE: return "COMMENT-LINE";
   case G2S_STRING: return "STRING";
   case G2S_MIDSTRING: return "MIDSTRING";
   case G2S_IDENTIFIER: return "IDENTIFIER";
   case G2S_KEYWORD: return "KEYWORD";
   case G2S_TYPE: return "TYPE";
   case G2S_NUMBER: return "NUMBER";
   default: return "unknown";
  }
}

static char *OpcodeName(int opcode)
{
  char *names[] = {"Unknown", "SetText", "InsertText", "Syntax",
		   "Completions", "Arglist", "Exit", "Notes", "Update"};
  if(opcode<0 || opcode >= sizeof(names)/sizeof(char *))
    return "unknown";
  return names[opcode];
}

void G2Editor::DumpBuf()
{
  int len = Length();
  int i,ch,st;

  for(i=0; i<len; i++) {
    ch = CH(i);
    st = STYLE(i);
    g2pvt_printf("[%2d] ", i);
    if(ch<32)
      g2pvt_printf(" %02X ", ch);
    else
      g2pvt_printf("'%c' ", ch);
    g2pvt_printf("%-12s\n", LexName((G2LexerState)st));
  }
}

#endif



/*
 * G2 Interface
 */

long g2ext_manage_editor(long opcode, long handle, LPWSTR string, long number, long n2)
{
  CEditorWnd *pFrame = FIND_WND(handle,CEditorWnd);
  G2Editor *pEdit = pFrame ? pFrame->m_pEditor : NULL;
  CModalEdit *pModal = NULL;
  int caret = number;
  CString s;

  if(!pEdit) {
    WARNF("Handle %d does not refer to a CEditorWnd\n", handle);
    return 0;
  }

  // TODO: We'll need a handle for per editor buffer

  switch(opcode) {
   case EDITOR_SET_BREAKPOINT:
   case EDITOR_CLEAR_BREAKPOINT:
   case EDITOR_DISABLE_BREAKPOINT:
   case EDITOR_SET_BREAKPOINTS:
   case EDITOR_CLEAR_BREAKPOINTS:
     // Number is the 1-origin line number here.
     pEdit->BreakpointCommand(opcode, number-1, string);
     break;

   case EDITOR_SET_TEXT:
     pEdit->SetUnicodeText(string, caret);
     break;

   case EDITOR_INSERT_TEXT:
     pEdit->InsertUnicodeText(string, caret);
     break;

   case EDITOR_REPLACE_TEXT:
     pEdit->ReplaceUnicodeText(string, caret, n2);
     break;

   case EDITOR_DELETE_TEXT:
     pEdit->DeleteUnicodeText(caret, n2);
     break;
   case EDITOR_MAXIMUM_NUMBER_OF_UNDOS_TO_REMEMBER:
     maxUndoSteps = caret;
     break;
   case EDITOR_SYNTAX:
     pEdit->ShowSyntaxError(caret, string);
     break;

   case EDITOR_COMPLETIONS:
     pEdit->ShowCompletionsPopup(string);
     break;

   case EDITOR_ARGLIST:
     pEdit->ShowCalltip(string);
     break;

   case EDITOR_NOTES:
     pEdit->EditorMsg(string);
     break;

   case EDITOR_TEXT_SAVED:
     pEdit->TextSaved(string);
     break;

   case EDITOR_SUSPEND:
     pEdit->SuspendEditor();
     break;

   case EDITOR_RESUME:
     pEdit->ResumeEditor();
     break;

   case EDITOR_SET_GRAMMAR:
     pEdit->SetGrammer((Grammar)number);
     break;

   case EDITOR_SET_OPTIONS:
     pEdit->SetOptions(number);
     break;

   case EDITOR_SET_TABS:
     pEdit->SetTabWidth(number);
     break;

   case EDITOR_INCREMENTAL_UPDATES:
     pEdit->EnableIncrementalUpdates((number&1) != 0);
     break;

   case EDITOR_CLEAR_OUTPUT:
     pEdit->ClearOutput();
     break;

   case EDITOR_APPEND_OUTPUT:
     pEdit->AppendOutput(string, number); // Number==numeric style
     break;

   case EDITOR_SHOW:
	 pFrame->FinalizeAndShow();
     break;

   // Added by SoftServe
   case EDITOR_MODAL:
	 pModal = new CModalEdit ();
	 GetMainWnd()->EnableWindow(false);
	 pModal->m_pParent = (CFrameWnd *)pFrame->m_pParentDialog;
	 pModal->m_EditorWnd = pEdit;
	 pEdit->m_bModal = TRUE;
     LONG lStyle;
	 lStyle = GetWindowLong(pModal->m_pParent->GetSafeHwnd(), GWL_STYLE);
	 lStyle &= ~WS_BORDER;
	 lStyle &= ~WS_CAPTION;
	 lStyle &= ~WS_DLGFRAME;
	 lStyle &= ~WS_THICKFRAME;
     lStyle |= WS_CHILD;
	 lStyle |= WS_MAXIMIZEBOX;
	 lStyle |= WS_MAXIMIZE;
     SetWindowLong(pModal->m_pParent->GetSafeHwnd(), GWL_STYLE, lStyle);  
	 pModal->Create(0);
	 pModal->SetIcon(theApp.LoadIcon(L"App"), FALSE);
	 pFrame->m_pParentDialog->GetWindowText(s);
	 pModal->SetWindowText(s);
	 break;

   case  EDITOR_ADD_TOOLBAR_BUTTON:
	 pFrame->InitAdditioanlToolBar(caret,string);
	 break;
   // End of SoftServe changes
   case EDITOR_CANCEL:
       pEdit->m_autoclose = TRUE;
       pEdit->OnEditCancel();
     break;

   case EDITOR_EXIT_NEW:
       pEdit->OnEditOK();
     break;	 

   case EDITOR_BEEP:
     pEdit->Beep();
     break;

   case EDITOR_SYNTAX_REPAIR:
     break;

   case EDITOR_DESTROY:
	 if (pModal != NULL)
		pModal->DestroyWindow();
	 break;
   default:
     WARNF("g2ext_manage_editor: unhandled opcode: %d\n", opcode);
     break;
  }
  return 1;
}
