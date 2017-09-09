// advancedcolorpicker.h : header file
//

#pragma once

class CAdvancedColorPicker : public CXTColorPicker
{
public:
  CAdvancedColorPicker();
  virtual ~CAdvancedColorPicker();
  BOOL Create(LPCTSTR lpszInitialVals, DWORD dwStyle,  RECT *prect, CWnd* pParentWnd, UINT nID);

protected:
  virtual void PostNcDestroy();
  DECLARE_MESSAGE_MAP()

private:
  COLORREF G2RGB_to_WinRGB(TCHAR *pText);
  void SetInitialValues( TCHAR *pText);
};
