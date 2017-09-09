// CScintillaWnd -- Basic MFC wrapper for Scintilla

#pragma once

#define PLAT_WIN 1
#include "Scintilla.h"

#define Ctrl (SCMOD_CTRL<<16)
#define Shift (SCMOD_SHIFT<<16)
#define Alt (SCMOD_ALT<<16)

#define GENSYM_EDITOR 836	// Native editor notification

#define EDITOR_VAR_FONT "Arial Unicode MS"
#define EDITOR_FIXED_FONT "Courier New"
#define EDITOR_FONT_SIZE 11

#define STYLE_MASK 31

#define MARGIN_LINENUMBERS 0

//#define EDITOR_BG RGB(245,245,245)  // Smoke
#define EDITOR_BG RGB(255,255,255) // White
#define EDITOR_FG RGB(0,0,0)	   // Black

class CScintillaWnd : public CWnd
{
public:
  DECLARE_DYNCREATE(CScintillaWnd) // Needed?
  CScintillaWnd();
  virtual ~CScintillaWnd();

public:
  BOOL m_autoDelete;
  int m_controlType;		// Keysym for events
  int m_ownerHandle;		// Where events are sent (if > 0)
  void SetOwnerHandle(int handle) {m_ownerHandle=handle;}

protected:
  SciFnDirect m_sciDirectFunction;  
  sptr_t m_sciPtr;
  BOOL m_consumedKey;
  BOOL m_scroll_caret_p;	// Request to scroll caret on next SCN_PAINTED

protected:
  CFindReplaceDialog *m_pFindReplaceDlg;
  CString m_findWhat;
  CString m_replaceWith;
  BOOL m_matchCase;
  BOOL m_wholeWord;
  BOOL m_searchDown;

public:
  LPCSTR m_varFontName;
  LPCSTR m_fixedFontName;
  BOOL m_fixedFont;
  int m_fontSize;		// Base font size (at zoom==0)
  BOOL m_lineNumbers;
  BOOL m_iconsMargin;
  int m_zoom;
  int m_tabWidth;
  int m_ignore_save_points;	// Don't SetModified if non-zero

public:
  inline LRESULT Sc(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) {
    return (*m_sciDirectFunction)(m_sciPtr, message, wParam, lParam); }

  inline unsigned char CH(int i) {return ((unsigned char)Sc(SCI_GETCHARAT,i)); }
  inline int NEXT(int i) {return Sc(SCI_POSITIONAFTER,i); }
  inline int PREV(int i) {return Sc(SCI_POSITIONBEFORE,i); }
  inline int FULLSTYLE(int i) {return Sc(SCI_GETSTYLEAT,i); }
  inline int STYLE(int i) {return Sc(SCI_GETSTYLEAT,i) & STYLE_MASK; }
  inline int POS() {return Sc(SCI_GETCURRENTPOS); }
  inline int SETPOS(int i) {return Sc(SCI_GOTOPOS,i); }

protected:
  DECLARE_MESSAGE_MAP()

public:				// Automatically generated declarations
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  virtual void PreSubclassWindow();
  BOOL PreCreateWindow(CREATESTRUCT &cs);
  afx_msg void OnDestroy();
  void PostNcDestroy();
  virtual void SetupEditor();
  virtual void SetupStyles();
  LRESULT WithoutUpdateEvents(UINT msg, WPARAM wParam, LPARAM lParam);
  afx_msg void OnPainted(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnSavePointLeft(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnSavePointReached(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnChar(UINT ch, UINT rep, UINT flags);
  afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg BOOL OnZoom(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg LRESULT OnParentIsMoving(WPARAM, LPARAM);
  afx_msg void OnMarginClick(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnModifyAttemptRO(NMHDR *pNotifyStruct, LRESULT* result);
  afx_msg void OnHotSpotClick(NMHDR *pNotifyStruct, LRESULT* result);
  virtual void EditKeyPress(UINT key);
  virtual void SetModified(BOOL modified);
  virtual void MarginClick(int margin, int pos, int modifiers);
  virtual void HotSpotClick(LPCSTR str, int style, int pos);
  void SetUnicodeText(LPCWSTR wstr, int caret = 0);
  LPWSTR GetUnicodeText(int *pCaret = NULL);
  void InsertUnicodeText(LPWSTR wstr, int caret);
  void ReplaceUnicodeText(LPWSTR wstr, int startCaret, int endCaret);
  void DeleteUnicodeText(int startCaret, int endCaret);
  void AppendUnicodeText(LPCWSTR wstr);
  int pos_from_caret(int caret);
  int caret_from_pos(int pos);
  char *GetTextRange(int startPos, int endPos);
  char *GetLine(int line);
  void ClearOutput();
  void AppendOutput(LPCWSTR wstr, int style);
  void SetOutput(LPCSTR str, LPCWSTR wstr);
  void SetSel(int anchorPos = -1, int currentPos = -1);
  BOOL HasSel();
  LPSTR GetSel();
  BOOL IsModified();
  BOOL IsReadOnly();
  void SetReadOnly(BOOL val = TRUE);
  int Length();
  int GetEol(int pos);
  void SetTabWidth(int width);
  void HighlightBrace(BOOL on, int pos);
  int ApproxEditorWidthInColumns();
  void RecomputeLineNumberMargin();
  void EditorBeep();
  void InsertText(LPCSTR str, int pos = -1);
  void ReplaceText(LPCSTR str, int startPos, int endPos);
  void DeleteText(int startPos, int endPos);
  void ReplaceSelection(char *str);
  BOOL SelectionEqual(LPCWSTR wstr, BOOL matchCase);
  BOOL FindString(LPCWSTR wstr, BOOL matchCase, BOOL wholeWord, BOOL down);
  afx_msg void OnEditCut();
  afx_msg void OnEditCopy();
  afx_msg void OnEditPaste();
  afx_msg void OnEditClear();
  afx_msg void OnEditUndo();
  afx_msg void OnEditRedo();
  afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditReplace(CCmdUI* pCmdUI);
  void ToggleWhitespace();
  void SetLineNumbersVisible(BOOL vis);
  void ToggleLineNumbers();
  void ToggleFont();
  BOOL FindDialogPresent();
  BOOL ReplaceDialogPresent();
  afx_msg void OnEditFind();
  afx_msg void OnEditReplace();
  afx_msg void OnEditFindNext();
  afx_msg LRESULT OnFindReplaceMsg(WPARAM, LPARAM lParam);
  BOOL FindNext(CFindReplaceDialog *pDlg, BOOL quiet = FALSE);
  void FireEvent(int opcode, int caret, LPWSTR string = NULL, int arg1 = -1, int arg2 = -1);
  void DebugCaret();
};

extern LPWSTR g2pvt_to_native_linebreaks(LPWSTR s);
extern LPWSTR g2pvt_to_gensym_linebreaks(LPWSTR s);
extern LPWSTR g2pvt_to_gensym_unicode(LPCSTR str, int len, int *pCaret);

extern char *g2pvt_to_utf8(LPCWSTR ustr);
extern char *g2pvt_to_utf8(LPCWSTR ustr, int *pCaret);

extern char *g2pvt_wrap_words(char *string, int columns);

extern BOOL g2pvt_is_brace(int ch);
extern BOOL g2pvt_is_number(const char *s);
extern BOOL g2pvt_is_long_number(const char *s);

extern void g2pvt_subst_char(wchar_t newChar, wchar_t oldChar, LPWSTR s);
