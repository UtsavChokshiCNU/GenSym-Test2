// GridCellSpinner.h: interface for the CGridCellSpinner class.
//

#pragma once

#include "GridCell.h"
#include "SpinnerTwng.h"

class CGridCellSpinner : public CGridCell
{
  friend class CGridCtrl;
  DECLARE_DYNCREATE(CGridCellSpinner)

public:
  DWORD m_SpinType;// int or decimal
  CString m_strSpec;			// Initial spec, as a packed string

public:
  CGridCellSpinner();
  virtual ~CGridCellSpinner();
  virtual CSize GetCellExtent(CDC* pDC);

public:
  CWnd *CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwEditStyle, UINT nID,
							int nRow, int nColumn, CString sInitText, 
							UINT nFirstChar);
};

class CInPlaceSpinner : public  CSpinnerTwng
{
public:
  CInPlaceSpinner(CWnd* pParent,         // parent
				  CRect& rect,           // dimensions & location
				  DWORD dwEditStyle,     // Style bits for the embedded edit control
				  UINT nID,              // control ID
				  int nRow, int nColumn, // row and column
				  LPCTSTR curText,
				  UINT nFirstChar);      // first character to pass to control

public:
  virtual ~CInPlaceSpinner();
  void EndEdit();
  void GetWindowText(CString& rString) const;
  virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
  afx_msg void OnEditLostFocus();
  afx_msg LRESULT OnEndEditMsg(WPARAM,LPARAM);
  DECLARE_MESSAGE_MAP()

private:
  int		 m_nRow;
  int		 m_nCol;
  UINT   m_nLastChar; 
  CString m_sInitText;
};
