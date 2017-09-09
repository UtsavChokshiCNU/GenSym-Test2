// -*- Mode: C++ -*-

#include "GridCtrl.h"

#define MAX_TEXT_SIZE 1000000
#define COLOR_LEN 50
#define DIM_SIZE 100
#define DELIM_LEN 1

/***********************************************************************************************************
There is an anomally in the Grid design.  The user is allowed to sort the grid on the TWNG side, but the grid 
is not sorted on the G2 side.  This leads to problems when G2 wishes to update the grid.
***********************************************************************************************************/

// In places where this constant is now used, we used to use MAX_GRID_TEXT.
// There are several places in GridExtras.cpp where we make a text buffer (named
// szValue in all cases), allocated of fixed size upon stack-frame activation,
// and write into it, and the "fixed size" is this constant.  I don't really
// think those buffers should be of fixed size at all; I think they should be as
// big as they need to be, and grow when they are too small.  Note also, for
// what it's worth, that in most cases, 1024 is far more than we need, but also
// that we don't actually check for overrun in several cases, because we use
// wsprintf.  In any case, I *definitely* don't think these string buffers
// should be tied to the size of m_szText, which is what MAX_GRID_TEXT is used
// for.  This should be improved.  -jv, 6/23/05
//   Note, now MAX_GRID_TEXT is gone entirely, but the rest of the comments
// still stand.  -jv, later 6/23/05
#define TEMP_BUFFER_SIZE  1024

// a subtype of [a cell in a] grid-view, not available as a standalone control
// make sure to keep this in synch in ext/c/dyndlgs.h
#define ctIntegerGridView  131
#define ctQuantityGridView 132
#define ctEllipsisGridView 642 

// I have absolutely no idea how to pick a value for this.  -jv, 4/21/05
#define GVN_BN_CLICKED          (LVN_FIRST-30)

#define G2_CBS_COLOR_PICKER 0x10000

#define ROW_HEADER_ID 0
#define COL_HEADER_ID 0

#define GRID_VIEW_DEFAULT_NROWS       10
#define GRID_VIEW_DEFAULT_NCOLS       10

#define GRID_VIEW_DEFAULT_NFIXED_ROWS 1
#define GRID_VIEW_DEFAULT_NFIXED_COLS 1

#define GRID_VIEW_NO_BUTTON_CLICKED  -1
#define GRID_VIEW_NO_PENDING_EDIT    -1

#define HEADER_GOING_ACROSS_AND_DOWN 0
#define HEADER_GOING_ACROSS 1
#define HEADER_GOING_DOWN   2
#define NO_HEADERS          3


// This constant, which stands for string zero terminator length, is to be used
// when increasing the length of a buffer to allow for the zero terminator.  It
// is simply more apparent to say "foo + SZTL" rather than "foo + 1"
#define SZTL 1

// This constant exists for when we're doing pointer arithmetic or otherwise
// indexing into a string, and we want to move one beyond a certain point.
// Like SZTL, it is just to make the intent clearer.
#define SKIP_CHAR 1

extern "C" int ICP_window_protocol_version;
#define ICP_GRID_VIEW_DELIMITER_FIX 89 // Sync with LISP grid-view-delimiter-fix

// header tokens
#define $StartDim        _T('{')
#define $EndDim          _T('}')
#define $HeaderIndicator _T('X')
#define $Sortable        _T('$')
#define $BGColor         _T('B')
#define $VisibleCell     _T('V')
#define $TitleRowHeight  _T('H')
#define $TitleColumnWidth  _T('W')
#define $FrozenRowCount  _T('A')
#define $FrozenColumnCount  _T('C')
#define $EndData         ((ICP_window_protocol_version > ICP_GRID_VIEW_DELIMITER_FIX) ? _T('\003') : _T(']'))

// value tokens
#define $StartCell       _T('(')
#define $Comma           _T(',')
#define $EndCell         _T(')')
#define $Alignment       _T('A')
#define $ControlType     _T('C')
#define $Bold            _T('D')
#define $Editable        _T('E')
#define $FGColor         _T('F')
#define $MultiLine       _T('G')
#define $Height          _T('H')
#define $IconIndex       _T('I')
#define $Clicked         _T('K')
#define $SelRange        _T('L')
#define $Text            _T('T')
#define $Value           _T('V')
#define $Width           _T('W')
#define $Slash           _T('/')
#define $Style           _T('S')
#define $TextFont        _T('Y')
#define $TextFontSize    _T('J')

#define $AllDelimiters _T("(,)ABCDEFGHIKLSTVWX]{}/$")


// Xn - optional where:
// If Xn does not exist (default case) means a header
// going across and a header going down.
// n = 0 is the same as NO Xn means a header going across and a header going down
// n = 1 is header going across
// n = 2 is header going down
// n = 3 is no header anywhere
// example {4/5}X1]

#define $PerRowOrCol  _T('_')

#define $StrDelim _T('\001')
#define $MultiStringDelim _T('\002')
static TCHAR $StringDelimiter[2]= { $StrDelim, 0 };

/*****************************************************************************
* CGensymGridCtrl Class Definition
*
*   Description:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
class CGensymGridCtrl: public CGridCtrl
{
  DECLARE_DYNCREATE(CGensymGridCtrl)
  virtual ~CGensymGridCtrl();

public:
  CGensymGridCtrl(int nScrollRows=GRID_VIEW_DEFAULT_NROWS,
		  int nScrollCols=GRID_VIEW_DEFAULT_NCOLS,
		  int nFixedRows=GRID_VIEW_DEFAULT_NFIXED_ROWS,
		  int nFixedCols=GRID_VIEW_DEFAULT_NFIXED_COLS);
 
  int m_nSortable; // is the grid sortable by column 
  POINT m_lastButtonClicked;
  POINT m_lastEdit;
  int m_dialogID;
  BOOL m_consumedKey;

  long GetSizeOfReturnBuf()
  {
    return lSizeOfReturnBuf;
  }

  void SetSizeOfReturnBuf(long len)
  {
    lSizeOfReturnBuf = len;
  }

public:
  void InitializeRowTags();
  int G2RowCount();
  int G2Row(int row);
  int G2Column(int col);
  int G2ColumnCount();
  int PhysicalRow(int G2row);
  int PhysicalColumn(int G2col);
  void GensymInsertRow(LPCTSTR strHeading, int G2row);
  BOOL GensymDeleteRow(int G2row);
  void GensymInsertColumn(LPCTSTR strHeading, int G2col);
  BOOL GensymDeleteColumn(int G2col);
  void GetPackedSelection(int& G2row, int& G2col, CString& str);
  BOOL SelectionChanged(NM_GRIDVIEW *pGH, int dialogId, int controlId);
  void IconChanged(int native_icon);
  BOOL G2WantsKey(UINT vKey, UINT scanCode);
  BOOL SendKeyToG2(UINT vKey, UINT scanCode);
  void SetItemBold(int row, int col, BOOL bold);
  BOOL SetRowHeight(int nRow, int height);
  BOOL SetColumnWidth(int nCol, int width);
  int GetScrollPos(int nBar);
  BOOL SetScrollPos(int nBar, int nPos);

protected:
  virtual void PostNcDestroy();

private:
  long lSizeOfReturnBuf;

public:
  void OnKeyDown(UINT vKey, UINT nRepCnt, UINT scanCode);
  void OnSysKeyDown(UINT vKey, UINT nRepCnt, UINT scanCode);
  void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
  DECLARE_MESSAGE_MAP()
};



/*****************************************************************************
* CRichGridItem Class Definition
*
*   Description:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
class CRichGridItem
{
public:
  CRichGridItem(TCHAR *token_string);
  CRichGridItem()
  {
    pTextFont = NULL;
	  pTokenString = NULL;
	  m_szText = NULL;
  };
  ~CRichGridItem()
  {
    if (pTextFont)
      delete [] pTextFont;
    if (pTokenString)
      delete [] pTokenString;
	if (m_szText)
      delete [] m_szText;
    return;
  }

  void InitializeItem (TCHAR *token_string);

  // The members nCRow and nCColumn are so named (with the extra "C") to
  // indicate that their values are correct on the "C side"; the values in Lisp
  // are generally one less.  That is because the headers in C are row/column
  // zero, but in Lisp, they're special cases, not included in the data of the
  // grid.  So what C thinks of as (1, 1), Lisp sees as (0, 0).  The other
  // reason for the weird names is for greppability.  There are other instances
  // of "nRow" and "nCol", and this makes it very easy to find out exactly where
  // these members are being used. -jv, 5/02/05
  int nCRow;
  int nCCol;

  int nWidth;
  int nHeight;
  int nType;
  int nEditable;
  int nMultiline; // added by SoftServe

  int nValue;
  int nSelected;
  int nIconIdx;
  int nAlignment; //ES_LEFT, ES_CENTER or ES_RIGHT
  int nBold;	  // 1==Bold, 0==Normal

  long dwStyle;    // Varies by control For CGridFormattedDate these are the values
                 
				 // #define G2_DTS_US_FORMAT       0x0000L // mm/dd/yyyy  - default
				 // #define G2_DTS_EU_FORMAT       0x0010L // dd/mm/yyyy
				 // #define G2_DTS_GOV_FORMAT      0x0020L // yyyy/mm/dd
  BOOL bFGColorSet;
  BOOL bBGColorSet;
  BOOL bTextSet;
  BOOL bWidthSet;
  BOOL bHeightSet;
  BOOL bEditableSet;
  BOOL bMultilineSet; // added by SoftServe
  BOOL bRowHeaderSet;
  BOOL bColHeaderSet;
  BOOL bSelectionSet;
  BOOL bIconSet;
  BOOL bAlignmentSet;
  BOOL bBoldSet;
  BOOL bStyleSet;
  BOOL bTextFontSet;
  BOOL bTextFontSizeSet;

  TCHAR szFGColor[COLOR_LEN];
  TCHAR szBGColor[COLOR_LEN];

  TCHAR *pTextFont;
  int nTextFontSize;

  TCHAR *m_szText;
  int m_textSize;

  TCHAR *pTokenString;
  int buf_size;
};
