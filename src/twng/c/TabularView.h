// -*- Mode: C++ -*-

// A G2 Tabular View is simply a Windows list view (CListCtrl)

#pragma once

// Operations
#define TBV_DESTROY 1
#define TBV_INSERT_COLUMN 2
#define TBV_INSERT_ROW 3
#define TBV_CELL_TEXT 4
#define TBV_CELL_ICON 5
#define TBV_COLUMN_TEXT 6
#define TBV_COLUMN_ALIGNMENT 7
#define TBV_COLUMN_WIDTH 8
#define TBV_COLUMN_ICON 9
#define TBV_SETREDRAW 10
#define TBV_BACKGROUND_COLOR 11
#define TBV_TEXT_COLOR 12
#define TBV_ROW_HEIGHT 13
#define TBV_GRIDLINES 14
#define TBV_SORTABLE 15
#define TBV_SINGLE_SELECTION 16
#define TBV_ROW_BACKGROUND_COLOR 17
#define TBV_ROW_TEXT_COLOR 18
#define TBV_REMOVE_COLUMN 19
#define TBV_SELECT_ROW 20
#define TBV_DESELECT_ROW 21
#define TBV_DESELECT_ALL_ROWS 22
#define TBV_REMOVE_ROW 23
#define TBV_REMOVE_ALL_ROWS 24
#define TBV_REMOVE_ALL_COLUMNS 25
#define TBV_CHECK_SELECTION_CHANGED 26
#define TBV_SORT_ROWS 27
#define TBV_INSERT_ROW_TO_TOP 28 //added by SoftServe
#define TBV_FONT_SIZE_CHANGE 29 //added by SoftServe
#define TBV_CHANGE_SORT 30
#define TBV_GRIDLINE_COLOR 31

// Events
#define TBVE_SELECT 1
#define TBVE_DESELECT 2
#define TBVE_LCLICK 3
#define TBVE_MCLICK 4
#define TBVE_RCLICK 5
#define TBVE_KEYDOWN 6
#define TBVE_SELECTION_CHANGED 7

class G2TabularView : public G2NativeView<CListCtrl>
{
private:
  DWORD m_cacheRowID;		// One-element cache for FindRow()
  int m_cacheRowNum;
  int m_iFontHeight;
  LPCSTR	m_strFontName;	
  int m_sortColumn;
  BOOL m_sortAscending;
  BOOL m_useDialogUnits;	// User-specified dimensions are in DLU
  BOOL m_multiline;		// Permit multiline text in cells
  int m_rowHeight;		// User-specified row height
  BOOL m_selectionChanged;	// True if selection changed since last notification
  CImageList m_scratchImageList;
  CMap<DWORD,DWORD,COLORREF,COLORREF> m_rowFG;
  CMap<DWORD,DWORD,COLORREF,COLORREF> m_rowBG;
  CDWordArray m_columnWidth;	// Original user-specified widths
  static int m_savedSortColumn;
  static BOOL m_savedSortDirection;
  COLORREF m_gridlinecolor;
  BOOL m_hasGridlineColor;
  BOOL m_hasGridLine;
  BOOL isSortingDataApplied;

public:
  DECLARE_DYNCREATE(G2TabularView)
  G2TabularView(int handle = 0) : 
    G2NativeView<CListCtrl>(handle),
    m_cacheRowID(0), m_cacheRowNum(-1), m_sortColumn(-1), m_sortAscending(FALSE),
    m_useDialogUnits(FALSE), m_multiline(FALSE), m_rowHeight(-1), isSortingDataApplied(FALSE),
    m_selectionChanged(FALSE),m_iFontHeight(14),m_strFontName("Time New Roman"), m_hasGridlineColor(0), m_hasGridLine(TRUE) {}

public:
  void SendEvent(int eventCode, int nRow = -1, int nCol = -1, int g2key = 0);
  BOOL G2WantsKey(UINT vKey, UINT scanCode);
  LRESULT OnIconChanged(WPARAM changed_icon, LPARAM iconID);
  LRESULT OnParentChanged(WPARAM/*BOOL*/ bIsDialog, LPARAM/*HWND*/ hwndNewParent);

  virtual BOOL KeyPress(UINT vKey, UINT scanCode);
  virtual void AfterKeyPress(UINT vKey, UINT scanCode);
  virtual void AfterMouseClick(UINT msg, UINT nFlags, CPoint p);

  CImageList *GetDrawingImageList();

  void SetRowBackgroundColor(int rowID, COLORREF color);
  void SetRowTextColor(int rowID, COLORREF color);
  void SetRowTextFontSize(int iFontSize);
  int  GetRowTextFontSize();	
  BOOL GetRowBackgroundColor(int nRow, COLORREF& color);
  BOOL GetRowTextColor(int nRow, COLORREF& color);

  void InsertColumn(int nCol, LPCTSTR label, int fmt, int width, int icon);
  void SetColumnText(int nCol, LPCTSTR label);
  void SetColumnWidth(int nCol, int width);
  void SetColumnAlignment(int nCol, int align);
  void SetColumnIcon(int nCol, int icon);
  int GetColumnCount();
  int GetTextFormat(int nCol);
  void RemoveColumn(int nCol);
  void RemoveAllColumns();
  void AdjustColumnWidth(int nCol);
  void UpdateSortArrows();

  static void SaveSortColumn(int sortColumn);
  static void SaveSortAscending(BOOL sortAscending);
  
  int GetSortColumn(void);
  BOOL GetSortAscending(void);

  void SetCellText(int rowID, int nCol, LPCTSTR text);
  void SetCellIcon(int rowID, int nCol, int icon);
  BOOL GetCellRect(int nRow, int nCol, int nArea, CRect &r);

  int InsertRow(int positionID, DWORD rowID, LPCTSTR text, COLORREF fg, COLORREF bg, bool bInsertToTop); //modified by SoftServe
  void SelectRow(int nRow);
  void DeselectRow(int nRow);
  void DeselectAllRows();
  int FindRow(DWORD rowID);

  void DeleteRow(int rowID);
  void DeleteAllRows();
  void SetRowHeight(int height);
  void SetGridLines(BOOL torf);
  BOOL HasGridLines();
  void SetGridlineColor(COLORREF color);
  COLORREF GetGridlineColor();
  BOOL HasGridlineColor();

  void SimpleCustomDraw(NMHDR *pNotifyStruct, LRESULT *pResult);
  void MultilineCustomDraw(NMHDR *pNotifyStruct, LRESULT *pResult);

  void SetSortable(BOOL torf);
  BOOL IsSortable();
  void CheckSelectionChanged();
  void SortRows(int nCol = -1, BOOL ascending = TRUE);
  int CompareItems(int nRowA, int nRowB);
  static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

protected:
  DECLARE_MESSAGE_MAP()
  afx_msg void OnCustomDraw(NMHDR *pNotifyStruct, LRESULT* pResult);
  afx_msg void OnGetInfoTip(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnColumnClick(NMHDR *pNMHDR, LRESULT *pResult);
};
