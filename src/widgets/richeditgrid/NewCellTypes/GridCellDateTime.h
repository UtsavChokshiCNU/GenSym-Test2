// GridCellDateTime.h: interface for the CGridCellDateTime class.
//
// Provides the implementation for a datetime picker cell type of the
// grid control.
//
// For use with CGridCtrl v2.22+
//
//////////////////////////////////////////////////////////////////////

#include "GridCell.h"
#include "afxdtctl.h"	// for CDateTimeCtrl

class CGridCellDateTime : public CGridCell  
{
  friend class CGridCtrl;
  DECLARE_DYNCREATE(CGridCellDateTime)

  CTime m_cTime;
  DWORD m_dwStyle;
  DWORD m_dwG2Style;

public:
	CGridCellDateTime();
	CGridCellDateTime(DWORD dwStyle);
	virtual ~CGridCellDateTime();
    virtual CSize GetCellExtent(CDC* pDC);

  // editing cells
public:
	void Init(DWORD dwStyle, long lStyle);
	virtual BOOL  Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
	virtual CWnd* GetEditWnd() const;
	virtual void  EndEdit();

	// Gensym addition -jv, 5/03/05
	DWORD GetExStyle();

	CTime* GetTime() {return &m_cTime;};
	void   SetTime(CTime time);
};

class CInPlaceDateTime : public CDateTimeCtrl
{
// Construction
public:
	CInPlaceDateTime(CWnd* pParent,         // parent
                   CRect& rect,           // dimensions & location
                   DWORD dwStyle,         // window/combobox style
                   DWORD dwG2Style,       // g2 style
                   UINT nID,              // control ID
                   int nRow, int nColumn, // row and column
                   COLORREF crFore, COLORREF crBack,  // Foreground, background colour
                   CTime* pcTime,
          		   UINT nFirstChar);      // first character to pass to control

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceList)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceDateTime();
    void EndEdit();

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

    void SetFormat(DWORD dwStyle, DWORD dwG2Style);
};
