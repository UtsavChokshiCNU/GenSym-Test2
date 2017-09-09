// GridCellDuration.h: interface for the CGridCellDuration class.
//
// G2 duration control as a GridCtrl cell
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "GridCell.h"
#include "NewDuration1.h"

class CGridCellDuration : public CGridCell  
{
  friend class CGridCtrl;
  DECLARE_DYNCREATE(CGridCellDuration)

  DWORD m_dwStyle;

public:
  CGridCellDuration();
  CGridCellDuration(DWORD dwStyle);
  virtual ~CGridCellDuration();
  virtual CSize GetCellExtent(CDC* pDC);

public:
  void Init(DWORD dwStyle);
  CWnd *CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
							int nRow, int nColumn, CString sInitText, 
							UINT nFirstChar);
};

class CInPlaceDuration : public CNewDuration
{
public:
  CInPlaceDuration(CWnd* pParent,         // parent
                   CRect& rect,           // dimensions & location
                   DWORD dwStyle,         // window/combobox style
                   UINT nID,              // control ID
                   int nRow, int nColumn, // row and column
                   LPCTSTR pText,
        		   UINT nFirstChar);      // first character to pass to control

public:
  virtual ~CInPlaceDuration();
  void EndEdit();
  BOOL PreTranslateMessage(MSG* pMsg);

protected:
  afx_msg void OnEditLostFocus();
  afx_msg void OnDateTimeLostFocus(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnEndEditMsg(WPARAM,LPARAM);
  DECLARE_MESSAGE_MAP()

private:
  int		 m_nRow;
  int		 m_nCol;
  UINT   m_nLastChar; 
  CString m_sInitText;
};
