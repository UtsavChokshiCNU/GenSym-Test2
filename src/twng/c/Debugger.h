// G2Debugger -- Debugger dialog based on Scintilla

#pragma once

#define GENSYM_DEBUGGER_DIALOG 835

#define DEBUGGER_CREATE 1	// Sync with lisp/dialogs.lisp
#define DEBUGGER_CANCEL 2
#define DEBUGGER_SOURCE_STEPPING_FLAG 0x100

class G2DebugEdit : public G2Editor
{
  virtual void MarginClick(int margin, int pos, int modifiers);
};

class G2Debugger : public CDialog
{
private:
  G2DebugEdit m_edit;
  CListCtrl m_list;
  static CRect m_lastShape;

public:
  BOOL m_sourceStepping;
  Resizer *m_resizer;
  LPWSTR m_title;
  LPWSTR m_label;
  LPWSTR m_proc;
  LPWSTR m_env;
  int m_line;
  int m_flags;			// Bit0 = source-stepping-p
  unsigned short *m_bkpts;	// Element 0 is count.
  int m_tabWidth;

public:
  G2Debugger();
  virtual ~G2Debugger();

protected:
  DECLARE_MESSAGE_MAP()

public:				// Automatically generated declarations
  virtual void DoDataExchange(CDataExchange* pDX);
  afx_msg void OnDestroy();
  G2Editor* GetEditor();
  CListCtrl* GetListCtrl();
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  afx_msg BOOL OnInitDialog();
  int DoModalDebugDialog(LPWSTR title, LPWSTR label, LPWSTR proc, LPWSTR env, int sourceStepping, int line, int tab_width,unsigned short *bkpts);
  afx_msg void OnPause();
};
