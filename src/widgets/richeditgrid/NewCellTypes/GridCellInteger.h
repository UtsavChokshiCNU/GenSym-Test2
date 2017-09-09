// GridCellInteger.h: interface for the CGridCellInteger class.

#pragma once

#include "GridCellNumeric.h"

class CGridCellInteger : public CGridCell  
{
  DECLARE_DYNCREATE(CGridCellInteger)
public:
  CWnd *CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
							int nRow, int nColumn, CString sInitText, 
							UINT nFirstChar);
  virtual BOOL ValidateEdit(LPCTSTR str);
};
