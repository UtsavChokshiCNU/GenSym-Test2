// GridCellNumeric.h: interface for the CGridCellNumeric class.
//
// Written by Andrew Truckle [ajtruckle@wsatkins.co.uk]
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "InPlaceEdit.h"
#include "GridCell.h"

class CGridCellNumeric : public CGridCell  
{
  DECLARE_DYNCREATE(CGridCellNumeric)
public:
  CWnd *CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
							int nRow, int nColumn, CString sInitText, 
							UINT nFirstChar);
  virtual BOOL ValidateEdit(LPCTSTR str);
};


class CInPlaceNumeric : public CInPlaceEdit
{
public:
  CInPlaceNumeric(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
				  int nRow, int nColumn, CString sInitText, UINT nFirstChar);
  LPCTSTR SetValidCharacters(LPCTSTR str);

private:
  LPCTSTR m_validCharacters;

protected:
	//{{AFX_MSG(CInPlaceNumeric)
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
 DECLARE_MESSAGE_MAP()
};
