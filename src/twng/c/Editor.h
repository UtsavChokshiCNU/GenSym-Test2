// -*- Mode: C++ -*-

#pragma once

typedef enum {FreeText=0, Procedure=1} Grammar;
typedef enum {BkptClear=0, BkptEnabled=1, BkptDisabled=2} BkptState;

typedef enum {
  G2S_NORMAL=0,
  G2S_COMMENT,			// {...}
  G2S_COMMENT_LINE,		// ... <eol>
  G2S_STRING,			// "...",  "...[, ]...[, or ]..."
  G2S_MIDSTRING,		// Within a [...] section in a string.
  G2S_IDENTIFIER,
  G2S_KEYWORD,			// These are styles, not states.
  G2S_TYPE,
  G2S_NUMBER,
  G2S_SYMBOL			// Quoted symbol
} G2LexerState;

class G2EditorPrefs
{
public:
  LPCSTR m_varFontName;
  LPCSTR m_fixedFontName;
  int m_fontSize;
  BOOL m_fixedFont;
  BOOL m_colorStyles;
  BOOL m_lineNumbers;
  BOOL m_iconsMargin;
  int m_zoom;
  G2EditorPrefs();
};

class CEditorWnd;

class G2Editor : public CScintillaWnd
{
public:
  G2pointer m_g2pointer;

private:
  int m_handle;

public:
  Grammar m_grammar;
  BOOL m_singleLineComments;	// Whether to enable '//' comments
  BOOL m_singleLineMode;	// Whether to exit on Return key
  BOOL m_queryClose;		// Whether to prompt to save changes
  int m_contextMenuID;		// Resource ID of context menu, or 0 for none
  BOOL m_incrementalUpdates;	// Enables sending moved/insert/delete msgs
  int m_cursor;			// Last one sent in incremental updates
  BOOL m_colorStyles;
  int m_syntax_error_marker;	// Scintilla marker handle or -1.
  BOOL m_remove_syntax_error;	// Pending delete of syntax error marker
  BOOL m_autoclose;	// Flag of the system procedure g2-ui-close-current-editor
  BOOL m_disabled;		// By G2, when editors are stacked
  int m_calltip_start;		// Position of start of calltip's function.
  char *m_calltip;		// Current calltip text, or NULL if none.
  
public:
  DECLARE_DYNCREATE(G2Editor)
  G2Editor(int handle=0);
  virtual ~G2Editor();
  virtual int GetHandle() {return m_handle;}
  void SetHandle(int handle) {m_handle=m_ownerHandle=handle;}
  void SetOwnerHandle(int handle) {m_ownerHandle=handle;}

protected:
  DECLARE_MESSAGE_MAP()

public:				// Automatically generated declarations
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnDestroy();
  virtual G2EditorPrefs *GetPrefs();
  void RestorePrefs(G2EditorPrefs *p =NULL);
  void SavePrefs(G2EditorPrefs *p =NULL);
  CEditorWnd *GetEditorWnd();
  CXTPCommandBars *GetCommandBars();
  CScintillaWnd *GetOutputWnd();
  void ClearOutput();
  void AppendOutput(LPCWSTR wstr, int style);
  void SetOutput(LPCSTR str, LPCWSTR wstr);
  void EditorMsg(LPCSTR str);
  void EditorMsg(LPCWSTR wstr);
  void Beep();
  void Warn(LPCSTR str);
  void Warn(LPCWSTR string);
  virtual void SetModified(BOOL modified);
  virtual void SetupEditor();
  virtual void SetupStyles();
  void ClearBreakpoint(int zLine);
  void ClearBreakpoints();
  void SetBreakpoint(int zLine, BkptState state);
  BkptState GetBreakpoint(int zLine);
  void SetBreakpoints(unsigned short *bkpts);
  LPWSTR GetBreakpoints();
  void BreakpointCommand(int opcode, int zLine, LPWSTR bkpts);
  int OpcodeToCycleBreakpoint(int zLine);
  inline BOOL IsIdentifierStart(int ch);
  inline BOOL IsIdentifierConstituentAt(int ch, int i);
  BOOL IsIdentifierAt(int i);
  BOOL IsNormal(int i);
  BOOL IsSpaceAt(int i);
  int BeginningOfWord(int pos=-1);
  char *GetTokenAtPoint(int pos=-1);
  char *GetPreviousToken(int *pPos, int *pEnd =NULL);
  BOOL PreviousTokenEqual(LPCSTR token, int *pPos);
  char *GetPreviousCall(int pos, int *start, int *end);
  int ComputeArgumentNumber(int start, int pos);
  void UpdateCalltip(int funPos, char *calltip);
  BOOL QuotedSymbolContext(int pos);
  G2LexerState ClassifyToken(LPCSTR token, int pos);
  void Style(int start, int end, G2LexerState state);
  void G2Colorize(int start, int end);
  BOOL IsFoldBegin(LPCSTR token, int pos);
  BOOL IsFoldEnd(LPCSTR token, int pos);
  void G2Fold(int start, int end);
  virtual void EditKeyPress(UINT key);
  virtual void MarginClick(int margin, int pos, int modifiers);
  afx_msg void OnUpdateUI(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnCharAdded(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnModified(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnChange();
  afx_msg void OnStyleNeeded(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnEditUndo();
  afx_msg void OnEditOK();
  afx_msg void OnUpdateEditOK(CCmdUI* pCmdUI);
  afx_msg void OnEditCancel();
  afx_msg void OnFileSave();
  afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
  void ToggleColorStyles();
  void ToggleIconsMargin();
  void ToggleFoldingMargin();
  void NewlineAndIndent();
  afx_msg void OnGotoItem();
  afx_msg void OnUpdateGotoItem(CCmdUI* pCmdUI);
  void SetGrammer(Grammar gram);
  void SetOptions(int mask);
  void EnableIncrementalUpdates(BOOL enable);
  void SuspendEditor();
  void ResumeEditor();
  BOOL IsSuspended();
  void TextSaved(LPCWSTR wstr);
  void ShowCompletionsPopup(LPWSTR wstr);
  void InsertCompletion(LPCSTR str);
  afx_msg void OnAutoComplete(NMHDR *pNotifyStruct, LRESULT* result);
  void ShowCalltip(LPWSTR wstr);
  void ShowSyntaxError(int caret, LPCWSTR msg);
  void ClearSyntaxError();
  void RequestCompletions();
  void RequestArglist(int pos);
  void CursorMoved(int pos);
  void TextInserted(int pos, LPCSTR text, int len);
  void TextDeleted(int pos, int len);
  int Checksum();
  void CommitChanges(BOOL exit_p);
  BOOL QueryClose();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint pt);
  void DumpBuf();

public:
  bool m_bModal; //Added by SoftServe
};


/*
 * Editor Opcodes (some used by debugger, too).
 */

#define EDITOR_CREATE 1
#define EDITOR_DESTROY 2
#define EDITOR_PRINT 3
#define EDITOR_SHOW 4
#define EDITOR_MODAL 5 //Added by SoftServe
#define EDITOR_ADD_TOOLBAR_BUTTON 6 //Added by SoftServe
#define EDITOR_CANCEL 7

#define EDITOR_CLEAR_BREAKPOINT 20
#define EDITOR_DISABLE_BREAKPOINT 21
#define EDITOR_SET_BREAKPOINT 22
#define EDITOR_SET_BREAKPOINTS 23
#define EDITOR_CLEAR_BREAKPOINTS 24

#define EDITOR_RESET 30
#define EDITOR_SET_TEXT 31
#define EDITOR_INSERT_TEXT 32
#define EDITOR_SYNTAX 33
#define EDITOR_COMPLETIONS 34
#define EDITOR_ARGLIST 35
#define EDITOR_EXIT 36
#define EDITOR_NOTES 37
#define EDITOR_APPLY 38
#define EDITOR_SUSPEND 39
#define EDITOR_RESUME 40
#define EDITOR_SET_GRAMMAR 41
#define EDITOR_SET_OPTIONS 42
#define EDITOR_SET_TABS 43

#define EDITOR_CURSOR_MOVED 44
#define EDITOR_TEXT_INSERTED 45
#define EDITOR_TEXT_DELETED 46
#define EDITOR_INCREMENTAL_UPDATES 47
#define EDITOR_EXIT_NEW 48
#define EDITOR_APPLY_NEW 49
#define EDITOR_COMPLETIONS_NEW 50
#define EDITOR_CLEAR_OUTPUT 51
#define EDITOR_APPEND_OUTPUT 52
#define EDITOR_HOTSPOT_CLICKED 53

#define EDITOR_REPLACE_TEXT 54
#define EDITOR_DELETE_TEXT 55

#define EDITOR_TEXT_SAVED 56
#define EDITOR_SHOW_COMPLETIONS 57
#define EDITOR_GOTO_ITEM 58
#define EDITOR_BEEP 59
#define EDITOR_CUSTOM_TOOLBAR 60 //Added by SoftServe
#define EDITOR_UNDO 61
#define EDITOR_MAXIMUM_NUMBER_OF_UNDOS_TO_REMEMBER 62
#define EDITOR_SYNTAX_REPAIR 28

// Bits for editor options
#define EDITOR_OPTIONS_SINGLE_LINE_COMMENTS 1
#define EDITOR_OPTIONS_SINGLE_LINE_EDITOR 2
#define EDITOR_OPTIONS_QUERY_ON_CLOSE 4

// Style numbers for hotspots. NOTE: These numbers are known to G2
#define G2S_CATEGORY 1
#define G2S_COMPLETION 2

/* Text messages */
#define MSG_APPLYING_CHANGES "Applying changes..."
#define MSG_BKPT_ON_MODIFIED "Breakpoints cannot be modified until changes are committed."
#define MSG_SAVE_CHANGES_P "The text is modified.\n\nDo you want to save the changes?"
#define MSG_MINIHELP "Press F1 for help."

#define MSG_KEYBOARD_HELP \
"Keyboard shortcuts:\n\
OK\tControl+Return\n\
Apply\tControl+Shift+Return\n\
Cancel\tEscape\n\
Show Completions\tControl+Space\n\
Show Arguments\tControl+Shift+Space\n\
Toggle Fixed Font\tControl+F2\n\
Toggle Line Numbers\tControl+F3\n\
Toggle Colors\tControl+F5"

#define EDITOR_EVENT_MASK (SC_MOD_INSERTTEXT | SC_MOD_BEFOREDELETE)

#define CARET_COLOR RGB(0,0,0)	        // black
#define SELECTION_COLOR RGB(192,192,192) // Gray
#define COMMENT_COLOR RGB(0,128,0)	// Dark green
#define STRING_COLOR RGB(255,0,255)	// Magenta
#define KEYWORD_COLOR RGB(0,0,255)	// Blue
#define TYPE_COLOR RGB(205,92,92)	// Indian red
#define BRACE_COLOR RGB(0,255,255)	// Cyan
#define IDENTIFIER_COLOR EDITOR_FG      // Black
#define NUMBER_COLOR RGB(128,128,128)   // Dark gray
#define SYMBOL_COLOR RGB(0,128,128)     // Blue green
#define BREAKPOINT_COLOR RGB(128,0,0)   // Dark red
#define DISABLED_BREAKPOINT_FILL_COLOR RGB(255,255,255) // White
#define SYNTAX_ERROR_COLOR RGB(255,0,0) // Red
#define ACTIVE_HOTSPOT_COLOR RGB(0,0,255) // Blue

#define MARGIN_ICONS 1		// Breakpoint and PC icons
#define MARGIN_FOLD 2		// Fold markers

#define MARGIN_ICONS_WIDTH 18
#define MARGIN_FOLD_WIDTH 11

#define MK_ENABLED_BKPT 0	// NOTE: We make use of this numbering
#define MK_DISABLED_BKPT 1
#define MK_NOTHING 2		// FIXME: Check this.
#define MK_PC 3
#define MK_SYNTAX 4

#define MK_BKPT_MASK ((1<<MK_DISABLED_BKPT) | (1<<MK_ENABLED_BKPT))
#define MK_MASK ((1<<(MK_SYNTAX+1))-1)

#define INDICATOR_SYNTAX_ERROR 0

#define DISABLED_BREAKPOINT_FLAG (1<<20)
