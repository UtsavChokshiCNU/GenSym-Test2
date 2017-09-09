// GridCellInteger -- Grid cell restricted to integer values

#include "stdafx.h"
#include "GridCellInteger.h"

IMPLEMENT_DYNCREATE(CGridCellInteger, CGridCell)

CWnd *CGridCellInteger::CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
											int nRow, int nColumn, CString sInitText, 
											UINT nFirstChar)
{
  CInPlaceNumeric *pEditor;
  pEditor = new CInPlaceNumeric(pParent, rect, dwStyle, nID, nRow, nColumn, sInitText, nFirstChar);
  pEditor->SetValidCharacters(_T("0123456789+-"));
  return pEditor;
}

BOOL CGridCellInteger::ValidateEdit(LPCTSTR str)
{
  LPTSTR pEnd = NULL;
  _tcstol(str, &pEnd, 10);
  BOOL ok = (pEnd == (str + _tcslen(str)));	// TODO: && fixnump ?
  if(!ok)
	MessageBeep(MB_OK);
  return ok;
}
