// Advancedcolorpicker.cpp : implementation file
//

#define _XTP_STATICLINK
#include <XTToolkitPro.h>

#include "Advancedcolorpicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedColorPicker

/*****************************************************************************
* PostNcDestroy
*
*   Description:
*   This method is called as a result of a call to DestroyWindow.
*   This is the last message received, so delete ourselves
*
*   Input Arguments:None
*   Returns: None
*   Notes: Cleans up memory leaks. Caller nolonger has to delete this object
*
*     -----
*   Modifications:
*****************************************************************************/

void CAdvancedColorPicker::PostNcDestroy() 
{
	CXTColorPicker::PostNcDestroy();
	delete this;
}

CAdvancedColorPicker::CAdvancedColorPicker()
{
}

CAdvancedColorPicker::~CAdvancedColorPicker()
{
}


BEGIN_MESSAGE_MAP(CAdvancedColorPicker, CXTColorPicker)
END_MESSAGE_MAP()

BOOL CAdvancedColorPicker::Create(LPCTSTR lpszInitialVals, DWORD dwStyle, RECT *prect, 
								  CWnd* pParentWnd, UINT nID)
{
  BOOL ok = CXTColorPicker::Create(lpszInitialVals, dwStyle, *prect, pParentWnd, nID);
  if(ok)
	SetInitialValues((TCHAR*)lpszInitialVals);
  return ok;
}

// convert from g2 rgb format to windows rgb format ie. widestring "RRGGBB" to COLORREF
COLORREF  CAdvancedColorPicker::G2RGB_to_WinRGB(TCHAR *pText)
{
	COLORREF cref;
	int Red;
	int Green;
	int Blue;

    swscanf(pText, _T("%2x%2x%2x"), &Red, &Green, &Blue);

    cref = RGB(Red, Green, Blue);
	return cref;
}

// this will allow the user to change defaults for this control if s/he desires
void CAdvancedColorPicker::SetInitialValues( TCHAR *pText)
{
    COLORREF cref;
    cref = G2RGB_to_WinRGB(pText);
    SetColor(cref); // set proposed user selection
    SetDefaultColor(cref);//set the default rgb color (current color)
}

// this returns the selected color in a string in hex format as RRGGBB
TCHAR *g2pvt_control_value_of_advanced_color(HWND hwndControl)
{
  CAdvancedColorPicker *pWnd;
  COLORREF color;
  CString str;

  pWnd = (CAdvancedColorPicker*)CWnd::FromHandle(hwndControl);
  color = pWnd->GetColor();

  str.Format(_T("%02X%02X%02X"), GetRValue(color), GetGValue(color), GetBValue(color));

  return _tcsdup((LPCTSTR)str);
}
