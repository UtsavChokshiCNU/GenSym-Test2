// GridCellNumeric -- Grid cell accepting integers or floats
//
// Very little left from original written by Andrew Truckle [ajtruckle@wsatkins.co.uk]
//

#include "stdafx.h"
#include "GridCellNumeric.h"
#include "GridCtrl.h"

//
// CGridCellNumeric -- the grid cell subclass
//

IMPLEMENT_DYNCREATE(CGridCellNumeric, CGridCell)

CWnd *CGridCellNumeric::CreateInPlaceEditor(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
											int nRow, int nColumn, CString sInitText, 
											UINT nFirstChar)
{
  return new CInPlaceNumeric(pParent, rect, dwStyle, nID, nRow, nColumn, sInitText, nFirstChar);
}

BOOL CGridCellNumeric::ValidateEdit(LPCTSTR str)
{
  LPTSTR pEnd = NULL;
  _tcstod(str, &pEnd);
  BOOL ok = (pEnd == (str + _tcslen(str)));
  if(!ok)
	MessageBeep(MB_OK);
  return ok;
}


//
// CInPlaceNumeric -- the in-place editor subclass
//

BEGIN_MESSAGE_MAP(CInPlaceNumeric, CInPlaceEdit)
//{{AFX_MSG_MAP(CInPlaceNumeric)
  ON_WM_CHAR()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CInPlaceNumeric::CInPlaceNumeric(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
								 int nRow, int nColumn, CString sInitText, UINT nFirstChar)
  : CInPlaceEdit(pParent, rect, dwStyle, nID, nRow, nColumn, sInitText, nFirstChar)
{
  m_validCharacters = _T("0123456789.,+-eEdD"); // TODO: Locale-specific
}

LPCTSTR CInPlaceNumeric::SetValidCharacters(LPCTSTR str)
{
  LPCTSTR old = m_validCharacters;
  m_validCharacters = str;
  return old;
}

void CInPlaceNumeric::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if(!_istprint(nChar) || _tcschr(m_validCharacters, nChar))
	CInPlaceEdit::OnChar(nChar, nRepCnt, nFlags);
  else
	MessageBeep(MB_OK);
}
