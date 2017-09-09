// LogBook.cpp -- Native logbook/message board.

#include "stdafx.h"
#include "Twng.h"
#include "MainFrm.h"
#include "LogBook.h"

#if !defined(OLD_G2_LOGBOOK)

//////////////////////////////////////////////////////////
//
// GENSYMCID-1629: Memory leak when sending messages
// Completely rewritten by Srdjan Veljkovic (May 2016)
//
//////////////////////////////////////////////////////////

#include "YAWWA_windows.hpp"
#include "YAWWA.hpp"
#include <algorithm>
#include <stdint.h>

const COLORREF COLOR_FADED = RGB(128,128,128);
const COLORREF COLOR_URGENT = RGB(200,0,0);
const COLORREF COLOR_BOLD = RGB(0,200,0);
const COLORREF COLOR_DEFAULT = RGB(0,0,0);
const COLORREF COLOR_HIGHLIGHT_ITEM = RGB(0, 0, 255);
const COLORREF COLOR_SELECTED_BKGND = RGB(200, 200, 200);

wchar_t const * const LOGBOOK_FONT = L"Arial Unicode MS";
const size_t LOGBOOK_FONTSIZE = 11;
const size_t LOGBOOK_LEFT_MARGIN = 5;

/** Contents of the "separator" line, the one that goes between messages.
    More precisely, it is added _after_ a message. Could be empty or
    something else. If need be, this can be become a parameter of the
    G2LogBook class.
    */
wchar_t const * const LOGBOOK_SEPARATOR_LINE = /*L""*/ L"\u2014\u2014\u2014";

enum LogBookOpCode {
    LOGBOOK_DESTROY = 2,
    LOGBOOK_APPEND_MESSAGE = 10,
    LOGBOOK_DELETE_MESSAGE = 11,
    LOGBOOK_NORMAL_MESSAGE = 12,
    LOGBOOK_FADE_MESSAGE = 13,
    LOGBOOK_HIGHLIGHT_MESSAGE = 14,
    LOGBOOK_SET_LINE_WRAP = 15,
    LOGBOOK_SET_INCLUDE_DATE_IN_TITLE = 16,
    LOGBOOK_APPEND_EXTENRED_MESSAGE = 17
};

enum LogBookEvent {
    LBV_EVENT_SELECT = 1,
    LBV_EVENT_RCLICK = 2,
    LBV_EVENT_KEYPRESS = 3
};

enum LogBookStyle {
    STYLE_DEFAULT,
    STYLE_FADED,
    STYLE_BOLD,
    STYLE_HIGHLIGHT,
    STYLE_URGENT,
    STYLE_COUNT
};

/** Data about a message, as kept in the ListBox.
    ListBox keeps each line of the message as a separate
    entry.
*/
struct G2LogBook::MessageInABox {
    /** Message ID/number */
    int id;
    /** Date of the message in G2 "simple date" format  */
    int g2_simple_date;
    /** The whole contents of the message */
    CString contents;
    /** Style of the message to display */
    LogBookStyle style;
    /** Index of the first entry (line) of the message in
        the ListBox */
    int first_list_box_entry;
    /** Number of entries (lines) the messages "occupies"
        in the ListBox. This does _not_ include the 
        separator entry (line).
    */
    int entry_count;
    /** This is just an optimization, we cache the height
        of an entry. It is in fact the "tallest" entry,
        but they should all have the same height.
        */
    int entry_height;
    /// Similar, for width - these are all the same beyond a reasonable doubt
    int entry_width;

    /// Helper method, returns the last ListBox entry of this message
    int last_list_box_entry() const {
        return first_list_box_entry + entry_count;
    }
};


IMPLEMENT_DYNCREATE(G2LogBook, CListBox)

BEGIN_MESSAGE_MAP(G2LogBook, CListBox)
  ON_WM_CREATE()
  ON_WM_SIZE()
  ON_WM_DESTROY()
  ON_WM_CONTEXTMENU()
  ON_WM_CHAR()
  ON_WM_TIMER()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()
  ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
END_MESSAGE_MAP()

G2LogBook::G2LogBook(int handle, wchar_t const* title) 
    : m_g2pointer(-1)
    , m_handle(handle)
    , m_lastDate(0)
    , m_strTitle(title)
    , m_includeDateInTitle(true)
    , m_last_msg_redrawn(0)
    , m_timerID(0)
    , m_redrawing_allowed(true)
{
    SAVE_WND();
    VTRACE("Construct [%d] ", m_handle); POB(this);
}


inline bool IsValidItemDataPtr(void *p) {
    // ItemData pointer is `nullptr` if some part of code is called
    // between `AddString` and `SetItemDataPtr`. It is `-1` if item
    // doesn't exist.
    return (p != nullptr) && (reinterpret_cast<int>(p) != -1);
}


void G2LogBook::SelectMessage(int item_first, int item_last)
{
    int step = (item_first > item_last) ? -1 : +1;
    MessageInABox *pmsg = nullptr;
    for (int i = item_first; i != item_last+step; i += step) {
        MessageInABox *pi = static_cast<MessageInABox*>(GetItemDataPtr(i));
        if (IsValidItemDataPtr(pi) && (pi != pmsg)) {
            SelItemRange(TRUE, pi->first_list_box_entry, pi->last_list_box_entry());
            pmsg = pi;
        }
    }
    if (IsValidItemDataPtr(pmsg)) {
        SetCaretIndex(pmsg->first_list_box_entry);
        SetCaretIndex(pmsg->last_list_box_entry());
    }
}


void G2LogBook::UnselectMessage(int item_first, int item_last)
{
    if (item_first > item_last) {
        std::swap(item_first, item_last);
    }
    MessageInABox *pmsg = nullptr;
    for (int i = item_first; i <= item_last; ++i) {
        MessageInABox *pi = static_cast<MessageInABox*>(GetItemDataPtr(i));
        if (IsValidItemDataPtr(pi) && (pi != pmsg)) {
            SelItemRange(FALSE, pi->first_list_box_entry, pi->last_list_box_entry());
            pmsg = pi;
        }
    }
}


void G2LogBook::DoCopyToClipboard()
{
    std::vector<int> selected(GetSelCount());
    if (selected.empty()) {
        return;
    }
    if (LB_ERR == GetSelItems(selected.size(), selected.data())) {
        return;
    }
    CString prep;
    MessageInABox *pmsg = nullptr;
    for (unsigned i = 0; i < selected.size(); ++i) {
        MessageInABox *pi = static_cast<MessageInABox*>(GetItemDataPtr(selected[i]));
        if (IsValidItemDataPtr(pi) && (pi != pmsg)) {
            prep += pi->contents;
            prep += L"\r\n";
            pmsg = pi;
        }
    }

    std::unique_ptr<HGLOBAL, HGLOBALdeleter> g(GlobalAlloc(GMEM_MOVEABLE, (prep.GetLength() + 1) * sizeof(TCHAR)));
    if (0 == g) {
	return;
    }
    if (wchar_t *p = (wchar_t*)GlobalLock(g.get())) {
        wcscpy_s(p, prep.GetLength()+1, prep);
        GlobalUnlock(p);
    }
    else {
        return;
    }

    if (OpenClipboard()) {
	if (EmptyClipboard() && SetClipboardData(CF_UNICODETEXT, g.get())) {
	    g.release();
	}
	CloseClipboard();
    }
}

void G2LogBook::OnChar(UINT nChar, UINT /*nRepCnt*/, UINT /*nFlags*/)
{
    const int CTRL_C = 0x0003;
    const int CTRL_A = 0x0001;
    switch (nChar) {
    case CTRL_A:
        SelectMessage(0, GetCount());
        break;
    case CTRL_C:
        DoCopyToClipboard();
        break;
    }
}

int G2LogBook::ItemsShown() const
{
    CRect rect;
    GetClientRect(rect);
    int const total_height = rect.Height();
    GetItemRect(GetTopIndex(), rect);
    /* Assume that all items have the same or very similar height */
    return total_height / rect.Height();
}


int G2LogBook::HandleKBto(bool extend, int item)
{
    if (item < 0) {
        item = 0;
    }
    int first_entry_of_last_message = m_messages.back()->first_list_box_entry;
    if (item >= first_entry_of_last_message) {
        item = first_entry_of_last_message;
    }
    UnselectMessage(0, GetCount());
    if (extend) {
        SelectMessage(d_pivot_item, item);
    }
    else {
        SelectMessage(item);
        d_pivot_item = item;
    }

    return -2;
}


int G2LogBook::VKeyToItem(UINT nKey, UINT nIndex)
{
    MessageInABox *pMessage = static_cast<MessageInABox*>(GetItemDataPtr(nIndex));
    if (!IsValidItemDataPtr(pMessage)) {
        return -1;
    }
    bool shift_down = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    switch (nKey) {
    case VK_UP:
        if (pMessage->first_list_box_entry > 0) {
            return HandleKBto(shift_down, pMessage->first_list_box_entry - 1);
        }
        return -2;
    case VK_DOWN:
        if (pMessage != m_messages.back().get()) {
            return HandleKBto(shift_down, pMessage->last_list_box_entry() + 1);
        }
        return -2;
    case VK_HOME:
        if (pMessage->first_list_box_entry > 0) {
            return HandleKBto(shift_down, 0);
        }
        return -2;
    case VK_END:
        if (pMessage != m_messages.back().get()) {
            return HandleKBto(shift_down, GetCount());
        }
        return -2;
    case VK_PRIOR:
        if (pMessage->first_list_box_entry > 0) {
            return HandleKBto(shift_down, nIndex - ItemsShown());
        }
        return -2;
    case VK_NEXT:
        if (pMessage != m_messages.back().get()) {
            return HandleKBto(shift_down, nIndex + ItemsShown());
        }
        return -2;
    case VK_DELETE:
        SendEvent(LBV_EVENT_KEYPRESS, g2_keycode_for_virtual_key(nKey));
        break;
    }

    return -1;
}


void G2LogBook::OnLButtonDown(UINT nFlags, CPoint point)
{
    BOOL outside;
    UINT item = ItemFromPoint(point, outside);
    if (outside) {
        return;
    }
    bool selected = GetSel(item) > 0;
    bool ctrl_down = (nFlags & MK_CONTROL) != 0;
    if ((nFlags & MK_SHIFT) != 0) {
        if (selected && ctrl_down) {
            UnselectMessage(item);
        }
        else {
            UnselectMessage(0, GetCount());
            SelectMessage(d_pivot_item, item);
        }
    }
    else {
        if (ctrl_down) {
            SetMessageSelect(!selected, item);
        }
        else {
            UnselectMessage(0, GetCount());
            SelectMessage(item);
            d_pivot_item = item;
        }
    }
    SetFocus();
}


void G2LogBook::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    OnLButtonDown(nFlags, point);
}


void G2LogBook::OnContextMenu(CWnd *pWnd, CPoint point)
{
    ScreenToClient(&point);
    BOOL outside;
    UINT item = ItemFromPoint(point, outside);
    MessageInABox *pMessage = static_cast<MessageInABox*>(GetItemDataPtr(item));
    if (!IsValidItemDataPtr(pMessage)) {
        return;
    }
    if (pMessage->id >= 0) {
        SendEvent(LBV_EVENT_RCLICK, pMessage->id);
    }
}


G2LogBook::~G2LogBook()
{
    VTRACE("Destruct  [%d] ", m_handle); POB(this);
    FORGET_WND();
    if (m_g2pointer >= 0) {
	g2ext_decache_g2pointer(m_g2pointer);
    }
    m_handle = 0;
    m_g2pointer = -1;
    DeleteObject(m_font);
}


int G2LogBook::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    int rc = CWnd::OnCreate(lpCreateStruct);
    if (IsWindow(m_hWnd)) {
	m_font.CreatePointFont(LOGBOOK_FONTSIZE*10, LOGBOOK_FONT);
    }
    return rc;
}

void G2LogBook::PostNcDestroy()
{
    CWnd::PostNcDestroy();
    delete this;
}


void G2LogBook::OnDestroy()
{
    VTRACE("OnDestroy [%d] ", m_handle); POB(this);
    if (m_handle > 0) {
	g2pvt_send_window_closed(m_hWnd, m_handle);
    }
    CWnd::OnDestroy();
}


void G2LogBook::OnSize(UINT nType, int cx, int cy)
{
    VTRACE("OnSize [%d] type:%d %dx%d ", m_handle, nType, cx, cy); POB(this);
    CWnd::OnSize(nType, cx, cy);
    g2pvt_view_sized(this, m_handle);
}


void G2LogBook::InvalidateRectForMessage(MessageInABox *pMessage)
{
    tagRECT first_rect;
    GetItemRect(pMessage->first_list_box_entry, &first_rect);
    tagRECT last_rect;
    GetItemRect(pMessage->last_list_box_entry(), &last_rect);
    tagRECT r;
    r.top = first_rect.top;
    r.left = first_rect.left;
    r.bottom = last_rect.bottom;
    r.right = last_rect.right;
    InvalidateRect(&r);
}


void G2LogBook::OnTimer(UINT nIDEvent) 
{
    if (nIDEvent == m_timerID) {
        KillTimer(m_timerID);
        EnableRedraw();
        int i = GetCount();
        while (i > 0) {
            --i;
            MessageInABox *pMessage = static_cast<MessageInABox*>(GetItemDataPtr(i));
            ASSERT(IsValidItemDataPtr(pMessage));
            if (pMessage->style == STYLE_BOLD) {
                pMessage->style = STYLE_DEFAULT;
                InvalidateRectForMessage(pMessage);
            }
            i = pMessage->first_list_box_entry;
        }
    }
    else {
        CWnd::OnTimer(nIDEvent);
    }
}


int G2LogBook::GetCurrentDate() const
{
    int i = GetTopIndex();
    if (i > LB_ERR) {
        MessageInABox *pMessage = static_cast<MessageInABox*>(GetItemDataPtr(i));
        if (IsValidItemDataPtr(pMessage)) {
            return pMessage->g2_simple_date;
        }
    }
    return 0;
}

void G2LogBook::SetIncludeDateInTitle(bool include)
{
    if (include == m_includeDateInTitle) {
	return;
    }
    m_includeDateInTitle = include;
    if (include) {
	UpdateTitleBar(GetCurrentDate());
    }
    else {
	UpdateTitleBar(m_strTitle);
    }
}

void G2LogBook::UpdateTitleBar(CString const &title)
{
    CXTPDockingPane *pPane = g2pvt_find_pane(m_handle);
    if (pPane) {
	pPane->SetTitle(title);
    }
    else if (GetParent()) {
	GetParent()->SetWindowText(title);
    }
    else {
	SetWindowText(title);
    }
}

inline SYSTEMTIME g2_simple_date_to_SYSTEM_TIME(long date) {
    SYSTEMTIME st = {0};
    st.wDay =  date & 0x1F;
    st.wMonth = (date>>5) & 0x0F;
    st.wYear = (date>>14) & 0xFFF;
    return st;
}


void G2LogBook::UpdateTitleBar(long date)
{
    CString title = m_strTitle;
    wchar_t buf[32] = {L' ', L'\0'};
    SYSTEMTIME st = g2_simple_date_to_SYSTEM_TIME(date);
    GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, buf+1, sizeof buf / sizeof buf[0] - 1);
    title += buf;

    UpdateTitleBar(title);
}


void G2LogBook::OnIdleUpdateCmdUI()
{
    int date = GetCurrentDate();
    if ((date != m_lastDate) && m_includeDateInTitle) {
        UpdateTitleBar(date);
        m_lastDate = date;
    }
    if (m_last_msg_redrawn) {
        EnableRedraw();
        int count = GetCount();
        if (count >= 0) {
            SetTopIndex(count - 1);
        }
        m_last_msg_redrawn = 0;
    }
}

inline COLORREF ColorFromStyle(int style) {
    switch (style) {
    case STYLE_DEFAULT:
    default:
	return COLOR_DEFAULT;
    case STYLE_HIGHLIGHT:
	return COLOR_HIGHLIGHT_ITEM;
    case STYLE_BOLD:
	return COLOR_BOLD;
    case STYLE_URGENT:
	return COLOR_URGENT;
    case STYLE_FADED:
	return COLOR_FADED;
    }
}

static void replace_unicode_LF_with_ASCII(wchar_t *wstr) {
    for (wchar_t *ws = wstr; *ws != L'\0'; ++ws) {
	if (*ws == L'\u2028') {
	    *ws ='\n';
	}
    }
}

void G2LogBook::AppendMsg(int msg, int date, LPWSTR wstr)
{
    // since we know that it's OK, we replace here "in-situ", without
    // creating a copy, for performance.
    replace_unicode_LF_with_ASCII(wstr);

    // Some trivial "rate limiting". While it is not great and
    // could be improved, it is essential, because, we simply can't
    // be fast enough for the possible flood of incoming messages.
    time_t now = time(NULL);
    if (now > m_last_msg_redrawn) {
        m_last_msg_redrawn = now;
        EnableRedraw();
    }
    else {
        DisableRedraw();
    }

    /// Now add the entries
    int i = GetCount();
    if (i > 0) {
        // unbold previous message
        ASSERT(m_messages.size() > 0);
        if (m_messages.back()->style == STYLE_BOLD) {
            m_messages.back()->style = STYLE_DEFAULT;
        }
    }
    MessageInABox *pMessage = new MessageInABox;
    pMessage->id = msg;
    pMessage->g2_simple_date = date;
    pMessage->contents = wstr;
    pMessage->style = STYLE_BOLD;
    pMessage->first_list_box_entry = i;
    pMessage->entry_height = 0;
    m_messages.push_back(std::unique_ptr<MessageInABox>(pMessage));
    
    CDC dc;
    dc.Attach(CreateCompatibleDC(NULL));
    CFont *pFont = dc.SelectObject(&m_font);

    CRect rect;
    GetClientRect(rect);

    // Before we collect enough messages to fill up the window, there will be no
    // vertical scroller, so we need to take that into account. This is not a very
    // fast way to calculate this, but it is correct. If need be, we could trade
    // accuracy for speed.
    int width_to_deflate_for_vscroll = GetSystemMetrics(SM_CXVSCROLL);
    SCROLLBARINFO sbVert;
    sbVert.cbSize = sizeof sbVert;
    if (GetScrollBarInfo(OBJID_VSCROLL, &sbVert)) {
        // Index 0 of rgstate is the scrollbar itself
        if (0 == (sbVert.rgstate[0] & (STATE_SYSTEM_INVISIBLE | STATE_SYSTEM_UNAVAILABLE))) {
            width_to_deflate_for_vscroll = 0;
        }
    }
    rect.DeflateRect(LOGBOOK_LEFT_MARGIN, 0, width_to_deflate_for_vscroll, 0);

    pMessage->entry_width = rect.Width();
    
    YAWWA<tagSIZE>(wstr, wcslen(wstr), rect.Width(), TextExtentGetter(dc), [&](int cy, wchar_t const* wcs, int length){
        if (cy > pMessage->entry_height) {
            pMessage->entry_height = cy;
        }
        AddString(std::wstring(wcs, length).c_str());
        SetItemDataPtr(i++, pMessage);
    });

    // add the "separator"
    AddString(LOGBOOK_SEPARATOR_LINE);
    pMessage->entry_count = i - pMessage->first_list_box_entry;
    SetItemDataPtr(i, pMessage);
 
    // timer to unbold this message
    m_timerID = SetTimer(TIMER_ID, TIMER_PERIOD, NULL);
}


void G2LogBook::StyleMsg(int msg, int style)
{
    // While this linear search can be very slow,
    // this rarely happens, so it's OK, and we can't
    // be 100% sure that messages come in total order,
    // so we can't use binary search.
    msg_iter i = std::find_if(m_messages.begin(), m_messages.end(), [=](const std::unique_ptr<MessageInABox> &m) {
        return m->id == msg;
    });
    if (i != m_messages.end()) {
        i->get()->style = static_cast<LogBookStyle>(style);
    }
}


void G2LogBook::DeleteMsg(int msg)
{
    // G2 deletes the oldest message, thus this should find it
    // right away.
    // When user decides to delete some message that is not the
    // first one, this will be fast enough (and we can't be 100% 
    // sure that we can use binary search).
    msg_iter i = std::find_if(m_messages.begin(), m_messages.end(), [=](const std::unique_ptr<MessageInABox> &m) {
        return m->id == msg;
    });
    if (i != m_messages.end()) {
        MessageInABox *pMessage = i->get();
        for (int j = pMessage->last_list_box_entry(); j >= pMessage->first_list_box_entry; --j) {
            DeleteString(j);
        }
        int const distance = pMessage->entry_count + 1;
        std::for_each(i, m_messages.end(), [=](std::unique_ptr<MessageInABox> &m) {
            m->first_list_box_entry -= distance;
        });
        m_messages.erase(i);
    }
}


void G2LogBook::SendEvent(int eventCode, int msg) const
{
    CMainFrame *pFrame = GetMainWnd();

    POINT p;
    ::GetCursorPos(&p);
    ::ScreenToClient(pFrame->CoorHwnd(), &p);
    g2pvt_fire_control_event(GENSYM_LOGBOOK_VIEW, m_handle, p.x, p.y, msg, eventCode, NULL);
}


void G2LogBook::DrawItem(LPDRAWITEMSTRUCT lpdi)
{
    ASSERT(lpdi->CtlType == ODT_LISTBOX);
    if ((int)lpdi->itemID < 0) {
        return;
    }
    CDC dc;

    dc.Attach(lpdi->hDC);

    COLORREF crOldTextColor = dc.GetTextColor();
    COLORREF crOldBkColor = dc.GetBkColor();

    MessageInABox *pMessage = static_cast<MessageInABox*>(GetItemDataPtr(lpdi->itemID));
    ASSERT(IsValidItemDataPtr(pMessage));

    dc.SetTextColor(ColorFromStyle(pMessage->style));

    /* If this item is selected, set the background color 
        to appropriate values. Also, erase
        rect by filling it with the background color (getting
        rid of old contents at these pixels).
    */
    if (lpdi->itemState & ODS_SELECTED) {
        dc.SetBkColor(COLOR_SELECTED_BKGND);
        dc.FillSolidRect(&lpdi->rcItem, COLOR_SELECTED_BKGND);
    }
    else {
        dc.FillSolidRect(&lpdi->rcItem, crOldBkColor);
    }

    lpdi->rcItem.left += LOGBOOK_LEFT_MARGIN;
    CFont *pFont = dc.SelectObject(&m_font);

    CString strText;
    GetText(lpdi->itemID, strText);
    dc.TextOut(lpdi->rcItem.left, lpdi->rcItem.top, strText);

    dc.SetTextColor(crOldTextColor);
    dc.SetBkColor(crOldBkColor);

    dc.SelectObject(pFont);
    dc.Detach(); 
}


void G2LogBook::MeasureItem(LPMEASUREITEMSTRUCT lpmi)
{
    ASSERT(lpmi->CtlType == ODT_LISTBOX);

    if (m_messages.size() == 0) {
        /// Should not happen, but, a little paranoia never hurts
        return;
    }
    MessageInABox *pMessage = m_messages.back().get();
    lpmi->itemHeight = pMessage->entry_height;
    lpmi->itemWidth = pMessage->entry_width;
}


/*
 * Lisp Interface
 */

long g2ext_is_operator_logbook_enabled() {
    return Twng_LogbookDisabled() ? 0 : 1;
}

long g2ext_is_message_board_enabled() {
    return Twng_MessageBoardDisabled() ? 0 : 1;
}

// synchronized with native-tw.lisp, manage-logbook icp message handler
static const int LOGBOOK_TYPE_MSG_BOARD = 0;
static const int LOGBOOK_TYPE_OPERATOR_LOGBOOK = 1;

long g2ext_create_logbook(int handle, LPWSTR title,
                          long /*x*/, long /*y*/, long width, long height,
                          long dock, long neighbor, long logbookType)
{
    if (((logbookType == LOGBOOK_TYPE_OPERATOR_LOGBOOK) && Twng_LogbookDisabled()) ||
        ((logbookType == LOGBOOK_TYPE_MSG_BOARD) && Twng_MessageBoardDisabled()))
        return -1;

    CMainFrame *pFrame = GetMainWnd();
    G2LogBook *pLB = new G2LogBook(handle, title);

    /* Ignore x and y, it's getting wrapped up in a docking
        container anyway.

        In order to be able to receive WM_MEASUREITEM to
        the correct window, they must have unique IDCs. We
        abuse `handle` for that here, but, maybe we could-
        should do it some other way.
    */
    pLB->Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL| 
        LBS_HASSTRINGS | LBS_MULTIPLESEL | LBS_WANTKEYBOARDINPUT | LBS_OWNERDRAWVARIABLE,
        CRect(0, 0, width, height), pFrame, IDC_LOGBOOK+handle);

    CSize min_size(0, 0);
    pFrame->WrapWnd(pLB, handle, 0, 0, width, height, dock, neighbor, min_size, title);
    return pLB->m_g2pointer;
}

long g2ext_manage_logbook(long opcode, long handle, long msg, long date, LPWSTR wstr)
{
    G2LogBook *pLB = FIND_WND(handle, G2LogBook);
    if (!pLB) {
        return 0;
    }

    switch(opcode) {
    case LOGBOOK_APPEND_MESSAGE:
        pLB->AppendMsg(msg, date, wstr);
        break;
    case LOGBOOK_DELETE_MESSAGE:    // TODO: Delete range of msgs, delete all msgs
        pLB->DeleteMsg(msg);
        break;
    case LOGBOOK_NORMAL_MESSAGE:
        pLB->StyleMsg(msg, STYLE_DEFAULT);
        break;
    case LOGBOOK_FADE_MESSAGE:
        pLB->StyleMsg(msg, STYLE_FADED);
        break;
    case LOGBOOK_HIGHLIGHT_MESSAGE:
        pLB->StyleMsg(msg, STYLE_HIGHLIGHT);
        break;
    case LOGBOOK_SET_LINE_WRAP:
        // No support for setting line wrapping (yet). It's always on.
        break;
    case LOGBOOK_SET_INCLUDE_DATE_IN_TITLE:
        pLB->SetIncludeDateInTitle(msg != 0);
        break;
    case LOGBOOK_DESTROY:
        DESTROY_WND(handle);
        break;
    }
    return 1;
}

long g2ext_manage_extended_logbook(long opcode, long handle, long msgNum, long date, 
				   LPWSTR string, long message_type,
				   LPWSTR workspace_uuid, LPWSTR workspace_name,
				   LPWSTR object_uuid, LPWSTR object_type, LPWSTR object_name, 
				   long line_number)
{
    return -1;
}

#else

//////////////////////////////////////////////////////////
//
// Native logbook/message board (original implementation)
//
//////////////////////////////////////////////////////////

#include "Scintilla.h"

#define Ctrl (SCMOD_CTRL<<16)
#define Shift (SCMOD_SHIFT<<16)
#define Alt (SCMOD_ALT<<16)

#define MSG_MARKER 0
#define MSG_MARKER_MASK (1<<MSG_MARKER)

IMPLEMENT_DYNCREATE(G2LogBook, CWnd)

BEGIN_MESSAGE_MAP(G2LogBook, CWnd)
 ON_WM_CREATE()
 ON_WM_SETFOCUS()
 ON_WM_KILLFOCUS()
 ON_WM_SIZE()
 ON_WM_DESTROY()
 ON_WM_KEYDOWN()
 ON_WM_LBUTTONUP()
 ON_WM_RBUTTONUP()
 ON_WM_TIMER()
 ON_NOTIFY_REFLECT(SCN_UPDATEUI, OnUpdateUI)
END_MESSAGE_MAP()

G2LogBook::G2LogBook(int handle)
{
  m_handle = handle;
  m_lastMsg = 0;
  m_selectedMsg = 0;
  m_msgSeparator = TRUE;
  m_pendingScroll = FALSE;
  m_lastDate = 0;
  m_includeDateInTitle = TRUE;
  m_boldMsg = 0;
  m_timerID = 0;
  m_g2pointer = -1;
  SAVE_WND();
  VTRACE("Construct [%d] ", m_handle); POB(this);
}

G2LogBook::~G2LogBook()
{
  VTRACE("Destruct  [%d] ", m_handle); POB(this);
  FORGET_WND();
  if(m_g2pointer>=0)
    g2ext_decache_g2pointer(m_g2pointer);
  m_handle=0;
  m_g2pointer=-1;
}

int G2LogBook::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  int rc = CWnd::OnCreate(lpCreateStruct);
  if(IsWindow(m_hWnd)) {
    m_strTitle = lpCreateStruct->lpszName;
    SetupEditor();
  }
  return rc;
}

void G2LogBook::PostNcDestroy()
{
  CWnd::PostNcDestroy();
  delete this;
}

void G2LogBook::OnSetFocus(CWnd* pOldWnd)
{
  CWnd::OnSetFocus(pOldWnd);
  if(m_handle > 0)
    g2pvt_send_window_activated(m_hWnd, m_handle);
  SendMessage(SCI_HIDESELECTION, FALSE);
}

void G2LogBook::OnKillFocus(CWnd* pNewWnd)
{
  CWnd::OnKillFocus(pNewWnd);
  SendMessage(SCI_HIDESELECTION, TRUE);
}

void G2LogBook::OnDestroy()
{
  VTRACE("OnDestroy [%d] ", m_handle); POB(this);
  if(m_handle > 0)
    g2pvt_send_window_closed(m_hWnd, m_handle);
  CWnd::OnDestroy();
}

void G2LogBook::OnSize(UINT nType, int cx, int cy)
{
  VTRACE("OnSize [%d] type:%d %dx%d ", m_handle, nType, cx, cy); POB(this);
  CWnd::OnSize(nType, cx, cy);
  g2pvt_view_sized(this, m_handle);
}



void G2LogBook::SetupEditor()
{
  SendMessage(SCI_SETREADONLY, TRUE);
  SendMessage(SCI_SETBUFFEREDDRAW, TRUE);
  SendMessage(SCI_SETCARETWIDTH, 0);        // Invisible caret

  SendMessage(SCI_SETMARGINLEFT, 0, 5);
  SendMessage(SCI_SETMARGINRIGHT, 0, 0);
  SendMessage(SCI_SETMARGINWIDTHN, 0, 0);  // Line numbers
  SendMessage(SCI_SETMARGINWIDTHN, 1, 0); // Markers
  SendMessage(SCI_SETMARGINWIDTHN, 2, 0);

  SendMessage(SCI_SETWRAPMODE, SC_WRAP_WORD);
  SendMessage(SCI_SETWRAPVISUALFLAGS, SC_WRAPVISUALFLAG_NONE);
  SendMessage(SCI_SETWRAPSTARTINDENT, 1);
  SendMessage(SCI_SETEOLMODE, SC_EOL_LF);

  SendMessage(SCI_SETCODEPAGE, SC_CP_UTF8);
  SendMessage(SCI_USEPOPUP, FALSE);

  SendMessage(SCI_MARKERDEFINE, MSG_MARKER, SC_MARK_EMPTY); // Marker for start of each message.
  // SendMessage(SCI_MARKERDEFINE, MSG_MARKER, SC_MARK_ARROW);

  // TODO: Let user specify the attributes of each style.
  SendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, (LPARAM)LOGBOOK_FONT);
  SendMessage(SCI_STYLESETSIZE, STYLE_DEFAULT, (LPARAM)LOGBOOK_FONTSIZE);
  SendMessage(SCI_STYLECLEARALL);

  SendMessage(SCI_SETSELBACK, TRUE, RGB(220,220,220)); // Light gray
  //  SendMessage(SCI_STYLESETBOLD, STYLE_BOLD, TRUE);
  SendMessage(SCI_STYLESETFORE, STYLE_BOLD, RGB(0, 128, 0));

  SendMessage(SCI_STYLESETFORE, STYLE_HIGHLIGHT, RGB(255,255,255));
  SendMessage(SCI_STYLESETBACK, STYLE_HIGHLIGHT, RGB(0,0,0));
  SendMessage(SCI_STYLESETEOLFILLED, STYLE_HIGHLIGHT, TRUE);

  SendMessage(SCI_STYLESETFORE, STYLE_FADED, COLOR_FADED);
  SendMessage(SCI_STYLESETFORE, STYLE_URGENT, COLOR_URGENT);

  SendMessage(SCI_CLEARALLCMDKEYS);
  SendMessage(SCI_ASSIGNCMDKEY, Ctrl | 'A' , SCI_SELECTALL);
  SendMessage(SCI_ASSIGNCMDKEY, Ctrl | 'C' , SCI_COPY);
  SendMessage(SCI_ASSIGNCMDKEY, Ctrl | '0',  SCI_SETZOOM); // FIXME: broken?
  SendMessage(SCI_ASSIGNCMDKEY, Ctrl | SCK_DIVIDE,  SCI_SETZOOM);
  SendMessage(SCI_ASSIGNCMDKEY, Ctrl | SCK_SUBTRACT , SCI_ZOOMOUT);
  SendMessage(SCI_ASSIGNCMDKEY, Ctrl | SCK_ADD,  SCI_ZOOMIN);
  SendMessage(SCI_ASSIGNCMDKEY, SCK_HOME, SCI_DOCUMENTSTART);
  SendMessage(SCI_ASSIGNCMDKEY, SCK_END, SCI_DOCUMENTEND);
  SendMessage(SCI_ASSIGNCMDKEY, SCK_PRIOR, SCI_PAGEUP);
  SendMessage(SCI_ASSIGNCMDKEY, SCK_NEXT, SCI_PAGEDOWN);
  SendMessage(SCI_ASSIGNCMDKEY, SCK_DOWN, SCI_LINESCROLLDOWN); // SCI_PARADOWN?
  SendMessage(SCI_ASSIGNCMDKEY, SCK_UP, SCI_LINESCROLLUP);

  //SendMessage(SCI_SETVIEWEOL, TRUE);
}

// Return number of message at line.
int G2LogBook::GetMsgNumber(int line)
{
  int pos = SendMessage(SCI_POSITIONFROMLINE, line);
  int ch, num = 0;

  if(!(SendMessage(SCI_MARKERGET,line) & MSG_MARKER_MASK))
    return -1;
  if(SendMessage(SCI_GETCHARAT,pos) != '#')
    return -1;

  for(int i=pos+1; i<pos+20; i++) {
    ch = SendMessage(SCI_GETCHARAT,i);
    if(isdigit(ch))
      num = 10*num + (ch&0xF);
    else
      break;
  }
  return num;
}

// Compute the message number and extent of the message containing given line.
// The character positions returned cover the entire message, including
// inter-message blanks. However, the line numbers returned cover just the
// message itself. startLine is always the line with the marker set.
BOOL G2LogBook::GetMsg(int line, int* pMsgNum,
		       int* pStartPos, int* pEndPos,
		       int* pStartLine, int* pEndLine)
{
  int nlines = SendMessage(SCI_GETLINECOUNT);
  int len = SendMessage(SCI_GETLENGTH);
  int msg, start, end, startLine, endLine;

  if(SendMessage(SCI_MARKERGET,line) & MSG_MARKER_MASK)
    startLine = line;
  else
    startLine = max(0, SendMessage(SCI_MARKERPREVIOUS, line, MSG_MARKER_MASK));

  endLine = SendMessage(SCI_MARKERNEXT, line+1, MSG_MARKER_MASK) - 1;
  if(endLine<0) endLine = nlines-1;

  msg = GetMsgNumber(startLine);
  start = SendMessage(SCI_POSITIONFROMLINE, startLine);
  end = SendMessage(SCI_GETLINEENDPOSITION, endLine);

  if(start == 0) {
    if(m_msgSeparator && end<len) end++; // Gobble up optional newline of next msg.
  } else {
    start--;			    // Preceding unconditional newline
    if(m_msgSeparator) start--;	    // Preceding optional newline.
    if(end < len) end--;
  }

  if(pMsgNum) *pMsgNum = msg;
  if(pStartPos) *pStartPos = start;
  if(pEndPos) *pEndPos = end;
  if(pStartLine) *pStartLine = startLine;
  if(pEndLine) *pEndLine = endLine;

  return TRUE;
}

BOOL G2LogBook::GetMsgAtPos(int pos, int *pMsgNum, int *pStartPos, int *pEndPos)
{
  return GetMsg(SendMessage(SCI_LINEFROMPOSITION,pos), pMsgNum, pStartPos, pEndPos);
}

// Find message given its number.
BOOL G2LogBook::FindMsg(int msg, int *startPos, int *endPos, int *startLine, int *endLine)
{
  int i, line, junk;

  *startPos = *endPos = -1;
  if(!m_msgLine.Lookup(msg,line))
    return FALSE;

  // Message is most likely at line or earlier.
  for(i=line; i>=0 && GetMsgNumber(i) != msg; i=SendMessage(SCI_MARKERPREVIOUS, i-1, MSG_MARKER_MASK));
  if(i>=0)
    return GetMsg(i, &junk, startPos, endPos, startLine, endLine);
    
  for(i=line; i>=0 && GetMsgNumber(i) != msg; i=SendMessage(SCI_MARKERNEXT, i, MSG_MARKER_MASK));
  if(i>=0)
    return GetMsg(i, &junk, startPos, endPos, startLine, endLine);

  return FALSE;
}

// Given full msg extent, select text region of msg we want to highlight.
void G2LogBook::SelectMsg(int msg, int start, int end)
{
  if(start<0) FindMsg(msg,&start,&end);
  if(start<0) return;
  m_selectedMsg = msg;
  if(start>0) start++;			       // Don't include separator lines in selection.
  if(m_msgSeparator && start>0) start++;
  PostMessage(SCI_SETSEL, start, end);
}

void G2LogBook::UnBold()
{
  if(m_boldMsg > 0) {
    StyleMsg(m_boldMsg, STYLE_DEFAULT);
    m_boldMsg = 0;
  }
}

void G2LogBook::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
  BOOL ctrl = (GetKeyState(VK_CONTROL) < 0);
  BOOL shift = (GetKeyState(VK_SHIFT) < 0);
  BOOL alt = (GetKeyState(VK_MENU) < 0);
  UINT i;

  int key = nChar | (shift ? Shift : 0) | (ctrl ? Ctrl : 0) | (alt ? Alt : 0);

  switch(key) {
   case Ctrl+VK_OEM_PLUS:
   case Ctrl+Shift+VK_OEM_PLUS:
     for(i=0; i<nRepCnt; i++)
       SendMessage(SCI_ZOOMIN);
     return;

   case Ctrl+VK_OEM_MINUS:
   case Ctrl+Shift+VK_OEM_MINUS:
     for(i=0; i<nRepCnt; i++)
       SendMessage(SCI_ZOOMOUT);
     return;

   case VK_TAB:
   case Shift+VK_TAB:
     if(m_selectedMsg) {
       int line, d = shift ? -1 : +1;
       SelectMsg(m_selectedMsg);	   // Pressing key removed the selection.
       for(int i=m_selectedMsg+d; 0<=i && i<=m_lastMsg; i+=d) {
	 if(m_msgLine.Lookup(i,line)) {
	   SendMessage(SCI_GOTOLINE, line); // Make line visible.
	   SelectMsg(i);
	   break;
	 }
       }
     }
     return;
  }
  UINT g2key = g2_keycode_for_virtual_key(nChar);
  SendEvent(LBV_EVENT_KEYPRESS, g2key);	       // TODO: modifier bits, selected msg, etc.
}

void G2LogBook::OnLButtonUp(UINT nFlags, CPoint p)
{
  CWnd::OnLButtonUp(nFlags, p);
  int p1 = SendMessage(SCI_GETSELECTIONSTART);
  int p2 = SendMessage(SCI_GETSELECTIONEND);

  if(p1==p2) {
    int start, end, msg;
    if(GetMsgAtPos(p1, &msg, &start, &end)) { // TODO: Make clicks on separator line clear all?
      SelectMsg(msg,start,end);
      SendEvent(LBV_EVENT_SELECT, msg);
    }
  }
}

void G2LogBook::OnRButtonUp(UINT nFlags, CPoint p)
{
  CWnd::OnRButtonUp(nFlags, p);
  int pos = SendMessage(SCI_POSITIONFROMPOINTCLOSE, p.x, p.y);
  int start, end, msg;
  if(pos>=0 && GetMsgAtPos(pos, &msg, &start, &end)) {
    SelectMsg(msg,start,end);
    SendEvent(LBV_EVENT_RCLICK, msg);
  }
}

void G2LogBook::OnTimer(UINT nIDEvent) 
{
  CWnd::OnTimer(nIDEvent);
  if(nIDEvent == m_timerID) {
    KillTimer(m_timerID);
    UnBold();
  }
}



int G2LogBook::GetCurrentDate()
{
  int line, msg;
  line = SendMessage(SCI_GETFIRSTVISIBLELINE);
  if(GetMsg(line, &msg))
    return m_msgDate[msg];
  return 0;
}

void G2LogBook::SetIncludeDateInTitle(BOOL torf)
{
  if(torf == m_includeDateInTitle) return;
  m_includeDateInTitle = torf;
  UpdateTitleBar();
}

void G2LogBook::UpdateTitleBar()
{
  CXTPDockingPane *pPane = g2pvt_find_pane(m_handle);
  CString title = m_strTitle;

  if(m_includeDateInTitle) {
    int date = GetCurrentDate();
    int day = date & 0x1F;		       // See LISP simple-encode-date
    int month = (date>>5) & 0xF;
    int year = (date>>14) & 0xFFF;
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char buf[32] = {0};
    if(1 <= month && month <= 12)
      sprintf(buf, "  %2d %s %d", day, months[month-1], year);
    title += buf;
    m_lastDate = date;
  }
  if(pPane)
    pPane->SetTitle(title);
  else if(GetParent())
    GetParent()->SetWindowText(title);
  else
    SetWindowText(title);
}

void G2LogBook::OnUpdateUI(NMHDR* pNMHDR, LRESULT* pResult)
{
  struct SCNotification *scn = (struct SCNotification *)pNMHDR;
  int p1 = SendMessage(SCI_GETSELECTIONSTART);
  int p2 = SendMessage(SCI_GETSELECTIONEND);

  if(p1==p2)
    m_selectedMsg = 0;

  if(m_pendingScroll) {
    m_pendingScroll = FALSE;
    PostMessage(WM_VSCROLL, SB_BOTTOM);
  }

  if(m_includeDateInTitle && (GetCurrentDate()) != m_lastDate)
    UpdateTitleBar();
}

void G2LogBook::AppendMsg(int msg, int date, LPWSTR wstr)
{
  char *str;
  int len = SendMessage(SCI_GETLENGTH);
  int pos = SendMessage(SCI_GETCURRENTPOS);
  int anchor = SendMessage(SCI_GETANCHOR);
  int line, startLine, endLine;

  m_pendingScroll = (pos==anchor);	   // If no selection, scroll to end.
  m_lastMsg = max(m_lastMsg,msg);

  SendMessage(SCI_SETREADONLY, FALSE);
  if(len==0) {
    startLine = 0;
    m_msgLine[msg] = 0;
  } else {
    SendMessage(SCI_APPENDTEXT, 1, (LPARAM)"\n");
    startLine = SendMessage(SCI_LINEFROMPOSITION, SendMessage(SCI_GETLENGTH));
    if(m_msgSeparator)
      SendMessage(SCI_APPENDTEXT, 1, (LPARAM)"\n");
  }

  // Mark start of message line.
  line = SendMessage(SCI_LINEFROMPOSITION, SendMessage(SCI_GETLENGTH));
  SendMessage(SCI_MARKERADD, line, MSG_MARKER);
  m_msgLine[msg] = line;
  m_msgDate[msg] = date;

  str = g2pvt_to_utf8(wstr);
  SendMessage(SCI_APPENDTEXT, strlen(str), (LPARAM)str);
  free(str);

  endLine = SendMessage(SCI_LINEFROMPOSITION, SendMessage(SCI_GETLENGTH));

  SendMessage(SCI_EMPTYUNDOBUFFER);
  SendMessage(SCI_SETREADONLY, TRUE);

  UnBold();
  StyleMsg(msg, STYLE_BOLD);
  m_boldMsg = msg;
  m_timerID = SetTimer(TIMER_ID, TIMER_PERIOD, NULL); // Start timer to unbold.
}

void G2LogBook::StyleMsg(int msg, int style)
{
  int start, end;
  if(FindMsg(msg, &start, &end) && start<end) {
    if(m_msgSeparator && start>0) start++; // Skip over newline separator.
    SendMessage(SCI_STARTSTYLING, start, 31);
    SendMessage(SCI_SETSTYLING, end-start, style);
  }
}

void G2LogBook::DeleteMsg(int msg)
{
  int start, end, startLine;
  if(FindMsg(msg, &start, &end, &startLine) && start < end) {
    SendMessage(SCI_MARKERDELETE, startLine, MSG_MARKER);
    SendMessage(SCI_SETTARGETSTART, start);
    SendMessage(SCI_SETTARGETEND, end);
    SendMessage(SCI_SETREADONLY, FALSE);
    SendMessage(SCI_REPLACETARGET, 0, (LPARAM)"");
    SendMessage(SCI_EMPTYUNDOBUFFER);
    SendMessage(SCI_SETREADONLY, TRUE);
    m_msgLine.RemoveKey(msg);
    m_msgDate.RemoveKey(msg);
  }
}

void G2LogBook::SendEvent(int eventCode, int msg)
{
  CMainFrame *pFrame = GetMainWnd();

  POINT p;
  ::GetCursorPos(&p);
  ::ScreenToClient(pFrame->CoorHwnd(), &p);
  g2pvt_fire_control_event(GENSYM_LOGBOOK_VIEW, m_handle, p.x, p.y, msg, eventCode, NULL);
}



/*
 * Lisp Interface
 */

long g2ext_create_logbook(int handle, LPWSTR title,
			  long x, long y, long width, long height,
			  long dock, long neighbor)
{
  CMainFrame *pFrame = GetMainWnd();
  G2LogBook *pLB = new G2LogBook(handle);

  g2pvt_initialize_scintilla_library();
  pLB->Create(_T("SCINTILLA"), title, WS_CHILD, CRect(x, y, width, height), pFrame, IDC_LOGBOOK);

  pFrame->WrapWnd(pLB, handle, x, y, width, height, dock, neighbor, title);
  return pLB->m_g2pointer;
}

long g2ext_manage_logbook(long opcode, long handle, long msg, long date, LPWSTR wstr)
{
  G2LogBook *pLB = FIND_WND(handle,G2LogBook);

  if(!pLB) return 0;

  switch(opcode) {
   case LOGBOOK_APPEND_MESSAGE:
     pLB->AppendMsg(msg, date, wstr);
     break;
   case LOGBOOK_DELETE_MESSAGE:	// TODO: Delete range of msgs, delete all msgs
     pLB->DeleteMsg(msg);
     break;
   case LOGBOOK_NORMAL_MESSAGE:
     pLB->StyleMsg(msg, STYLE_DEFAULT);
     break;
   case LOGBOOK_FADE_MESSAGE:
     pLB->StyleMsg(msg, STYLE_FADED);
     break;
   case LOGBOOK_HIGHLIGHT_MESSAGE:
     pLB->StyleMsg(msg, STYLE_HIGHLIGHT);
     break;
   case LOGBOOK_SET_LINE_WRAP:
     pLB->SendMessage(SCI_SETWRAPMODE, msg);
     break;
   case LOGBOOK_SET_INCLUDE_DATE_IN_TITLE:
     pLB->SetIncludeDateInTitle(msg != 0);
     break;
   case LOGBOOK_DESTROY:
     DESTROY_WND(handle);
     break;
  }
  return 1;
}

long g2ext_manage_extended_logbook(long opcode, long handle, long msgNum, long date, 
                                   LPWSTR string, long message_type,
                                   LPWSTR workspace_uuid, LPWSTR workspace_name,
                                   LPWSTR object_uuid, LPWSTR object_type, LPWSTR object_name, 
                                   long line_number)
{
	return -1;
}

#endif // OLD_G2_LOGBOOK

