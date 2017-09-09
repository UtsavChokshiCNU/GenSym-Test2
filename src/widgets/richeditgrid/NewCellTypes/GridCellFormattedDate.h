///////////////////////////////////////////////////////////////////////////
//
// CGridCellFormattedDate.cpp: implementation of the CGridCellFormattedDate class.
//
// Provides the implementation for a formatted date picker cell type of the
// grid control.
//
// Written by Heidi Goddard
//
///////////////////////////////////////////////////////////////////////////

#include "GridCell.h"
#include "afxdtctl.h"	// for CDateTimeCtrl

class CGridCellFormattedDate : public CGridCell  
{
  friend class CGridCtrl;
  DECLARE_DYNCREATE(CGridCellFormattedDate)

  CTime m_cTime;
  DWORD m_dwStyle;

  DWORD m_dwTimeFormat;
public:
	CGridCellFormattedDate();
	CGridCellFormattedDate(DWORD dwStyle);
	virtual ~CGridCellFormattedDate();
    virtual CSize GetCellExtent(CDC* pDC);
    void  SetFormattedDate(CTime time, DWORD nFormat);
  // editing cells
public:
	virtual BOOL  Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);

	virtual CWnd* GetEditWnd() const;
	virtual void  EndEdit();

	CTime* GetTime() {return &m_cTime;};
};

class CInPlaceFormattedDate : public CDateTimeCtrl
{
// Construction
public:
	CInPlaceFormattedDate(CWnd* pParent,         // parent
                   CRect& rect,           // dimensions & location
                   DWORD dwStyle,         // window/combobox style
                   UINT nID,              // control ID
                   int nRow, int nColumn, // row and column
                   COLORREF crFore, COLORREF crBack,  // Foreground, background colour
                   CTime* pcTime,
				   DWORD dwDateTimeFormat,
          		   UINT nFirstChar);      // first character to pass to control

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceList)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceFormattedDate();
    void EndEdit();
    void SetDateFormat(DWORD dwStyle, DWORD dwFormat);

// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceList)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
// Gensym change -fmw, 9/21/06
//	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	//afx_msg void OnSelendOK();

	DECLARE_MESSAGE_MAP()

private:
    CTime*   m_pcTime;
	int		 m_nRow;
	int		 m_nCol;
 	UINT     m_nLastChar; 
	BOOL	 m_bExitOnArrows; 
    COLORREF m_crForeClr, m_crBackClr;
    DWORD m_dwTimeFormat;

};
