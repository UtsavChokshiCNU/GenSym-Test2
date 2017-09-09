// -*- Mode: C++ -*-

#pragma once

// #define OLD_G2_LOGBOOK
#undef OLD_G2_LOGBOOK

#if !defined(OLD_G2_LOGBOOK)

//////////////////////////////////////////////////////////
//
// GENSYMCID-1629: Memory leak when sending messages
// Completely rewritten by Srdjan Veljkovic (May 2016)
//
//////////////////////////////////////////////////////////

#include <deque>
#include <memory>

#define IDC_LOGBOOK 161
#define TIMER_ID 621
#define TIMER_PERIOD 1000

struct HGLOBALdeleter {
    typedef HGLOBAL pointer;
    void operator()(HGLOBAL h) {
	GlobalFree(h);
    }
};

class G2LogBook : public CListBox {
public:
    G2pointer m_g2pointer;

private:

    struct MessageInABox;    

    // Control handle (G2-assigned)
    int m_handle;

    // Last date recorded in title bar
    int m_lastDate;

    // Base window title
    CString m_strTitle;

    // Indicates whether date is included in the windows title 
    bool m_includeDateInTitle;

    // time_t of last message (re)drawn
    time_t m_last_msg_redrawn;

    // ID of the "un-bold" timer, while running
    UINT m_timerID;

    // The font to use for text of the LogBook (list box)
    CFont m_font;

    // Is redrawing of the LogBook (list box) currently allowed
    bool m_redrawing_allowed;

    // Messages
    std::deque<std::unique_ptr<MessageInABox>> m_messages;
    typedef std::deque<std::unique_ptr<G2LogBook::MessageInABox> >::iterator msg_iter;
    
    // The "pivot" item for multi-message selection purposes
    int d_pivot_item;

public:
    DECLARE_DYNCREATE(G2LogBook)
    G2LogBook(int handle=0, wchar_t const *title=L"");
    virtual ~G2LogBook();

    int GetHandle() const {
	return m_handle;
    }

    void AppendMsg(int msgNum, int date, LPWSTR wstr);
    void StyleMsg(int msgNum, int style);
    void DeleteMsg(int msgNum);
    void SendEvent(int eventCode, int msg) const;
    int GetCurrentDate() const;
    void UpdateTitleBar(long date);
    void UpdateTitleBar(CString const &title);
    void SetIncludeDateInTitle(bool include);

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnDestroy();
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnContextMenu(CWnd *pWnd, CPoint pont);
    afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags ); 
    afx_msg void OnIdleUpdateCmdUI();

    /*override*/ void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    /*override*/ void MeasureItem(LPMEASUREITEMSTRUCT lpmi);
    /*override*/ int VKeyToItem(UINT nKey, UINT nIndex);

protected:
    virtual void PostNcDestroy();
    void DoCopyToClipboard();
    int HandleKBto(bool extend, int item);
    void SelectMessage(int item_first, int item_last);
    void SelectMessage(int item) { SelectMessage(item, item); }
    void UnselectMessage(int item_first, int item_last);
    void UnselectMessage(int item) { UnselectMessage(item, item); }
    void SetMessageSelect(bool selected, int item) { 
        if (selected) {
            SelectMessage(item);
        }
        else {
            UnselectMessage(item);
        }
    }
    int ItemsShown() const;
    void InvalidateRectForMessage(MessageInABox *pMessage);

    void EnableRedraw() {
	if (!m_redrawing_allowed) {
	    SendMessage(WM_SETREDRAW, TRUE);
	    m_redrawing_allowed = true;
	}
    }
    void DisableRedraw() {
	if (m_redrawing_allowed) {
	    SendMessage(WM_SETREDRAW, FALSE);
	    m_redrawing_allowed = false;
	}
    }

protected:
    DECLARE_MESSAGE_MAP()
};

#else

//////////////////////////////////////////////////////////
//
// Native logbook/message board (original implementation)
//
//////////////////////////////////////////////////////////

#define LOGBOOK_DESTROY 2			// Opcodes
#define LOGBOOK_APPEND_MESSAGE 10
#define LOGBOOK_DELETE_MESSAGE 11
#define LOGBOOK_NORMAL_MESSAGE 12
#define LOGBOOK_FADE_MESSAGE 13
#define LOGBOOK_HIGHLIGHT_MESSAGE 14
#define LOGBOOK_SET_LINE_WRAP 15
#define LOGBOOK_SET_INCLUDE_DATE_IN_TITLE 16
#define LOGBOOK_APPEND_EXTENRED_MESSAGE 17

#define LBV_EVENT_SELECT 1			// Events
#define LBV_EVENT_RCLICK 2
#define LBV_EVENT_KEYPRESS 3

#define STYLE_FADED 1
#define STYLE_BOLD 2
#define STYLE_HIGHLIGHT 3
#define STYLE_URGENT 4

#define COLOR_FADED RGB(128,128,128)
#define COLOR_URGENT RGB(200,0,0)

#define LOGBOOK_FONT "Arial Unicode MS"
#define LOGBOOK_FONTSIZE 11

// #define LOGBOOK_FONT "Courier New"
// #define LOGBOOK_FONTSIZE 10

#define IDC_LOGBOOK 161
#define TIMER_ID 621
#define TIMER_PERIOD 1000

class G2LogBook : public CWnd
{
public:
  G2pointer m_g2pointer;
  CMap<int,int,int,int> m_msgLine;	// Msgnum -> start line or later
  CMap<int,int,int,int> m_msgDate;	// Msgnum -> encoded date

private:
  int m_handle;				// Control handle (G2-assigned)
  int m_selectedMsg;			// If only one.
  int m_lastMsg;			// Largest msg number encountered
  BOOL m_pendingScroll;
  BOOL m_msgSeparator;			// TRUE for blank line between msgs
  BOOL m_includeDateInTitle;		// TRUE to include current date in title bar
  int m_lastDate;			// Last date recorded in title bar
  CString m_strTitle;			// Base window title
  int m_boldMsg;			// Bold face until timer goes off or msg added
  UINT m_timerID;

public:
  DECLARE_DYNCREATE(G2LogBook)
  G2LogBook(int handle = 0);
  virtual ~G2LogBook();
  virtual int GetHandle() {return m_handle;}

public:
  void SetupEditor();
  int GetMsgNumber(int line);
  BOOL GetMsg(int line, int* pMsgNum, int* pStartPos=NULL, int* pEndPos=NULL,
	      int* pStartLine=NULL, int* pEndLine=NULL);
  BOOL FindMsg(int msg, int *startPos=NULL, int *endPos=NULL, 
	       int *startLine=NULL, int *endLine=NULL);
  BOOL GetMsgAtPos(int pos, int* pMsgNum, int* pStartPos=NULL, int* pEndPos=NULL);
  void SelectMsg(int msg, int start=-1, int end=-1);
  void UnBold();
  void AppendMsg(int msgNum, int date, LPWSTR wstr);
  void StyleMsg(int msgNum, int style);
  void DeleteMsg(int msgNum);
  void SendEvent(int eventCode, int msg);
  int GetCurrentDate();
  void UpdateTitleBar();
  void SetIncludeDateInTitle(BOOL torf);

public:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnUpdateUI(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();

protected:
  virtual void PostNcDestroy();
  DECLARE_MESSAGE_MAP()
};

#endif // OLD_G2_LOGBOOK

