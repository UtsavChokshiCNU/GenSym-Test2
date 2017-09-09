/*|*\
|*|  File:      widgets/colorpicker/ColorCombo.h
|*|                (derived from FocusEditCtrl.h)
|*|
|*|  By:        James R. Twine
|*|             Copyright 1998, James R. Twine
|*|             Copyright 1999-2000, TransactionWorks, Inc.
|*|  Date:      xxxx, xxxx, 1998
|*|
|*|             This implementes a ComboBox control that can be
|*|             used to display and provide selection for a specific
|*|             set of colors.  The standard set of colors provided
|*|             by the control are a subset of the X11 colorset, and
|*|             are the ones available in (and the color names
|*|                                recognized by) Internet Explorer.
|*|
|*|                                The ComboBox that is subclassed must have the
|*|             Owner Draw Fixed and Has Strings styles.
|*|
|*|             This is based on code that was originally found on
|*|             CodeGuru, and was © 1997 Baldvin Hansson.
|*|
|*|             A bug fix by Marcel Galem was added to provide
|*|             correct masking of the COLORREF values.
|*|
|*|             DDX routines were provided by Paul Wardle
|*|             (paul.wardle@siemenscomms.co.uk)
|*|
|*|             This Code May Be Freely Incorporated Into
|*|             Projects Of Any Type Subject To The Following
|*|             Conditions:
|*|
|*|             o This Header Must Remain In This File, And Any
|*|               Files Derived From It
|*|             o Do Not Misrepresent The Origin Of Any Parts Of
|*|               This Code (IOW, Do Not Claim You Wrote It)
|*|
|*|             A "Mention In The Credits", Or Similar Acknowledgement,
|*|             Is *NOT* Required.  It Would Be Nice, Though! :)
|*|
\*|*/



#if !defined(AFX_COLORCOMBO_H__BD768E6A_1C14_4F39_BF05_85B16DABF59A__INCLUDED_)
#define AFX_COLORCOMBO_H__BD768E6A_1C14_4F39_BF05_85B16DABF59A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorCombo.h : header file
//
#include "msincls.h"
/////////////////////////////////////////////////////////////////////////////
// CColorCombo window
#define                CCB_MAX_COLOR_NAME                32                                                        // Max Chars For Color Name - 1


//
//        Macros...
//

extern "C" char *g2pvt_get_last_error_string (void);


//
//        Internal Structure For Color/Name Storage...
//
struct SColorAndName
{
  /**/
  SColorAndName()                                                                        // Default Constructor
  {
    memset( this, 0, sizeof( SColorAndName ) );                        // Init Structure
  };
  /**/
  SColorAndName( COLORREF crColor,
    LPCTSTR cpColor ) : m_crColor( crColor )// Smart Constructor
  {
    _tcsncpy( m_cColor, cpColor, CCB_MAX_COLOR_NAME );        // Set Color Name
    m_cColor[ CCB_MAX_COLOR_NAME - 1 ] = _T( '\0' );        // Just To Make Sure...
  };
  COLORREF        m_crColor;                                                                        // Actual Color RGB Value
  TCHAR                m_cColor[ CCB_MAX_COLOR_NAME ];                                // Actual Name For Color
};

class CColorCombo : public CComboBox
{
  // Construction
public:
  CColorCombo();

  // Attributes
public:

  // Operations
public:

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CColorCombo)
public:
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
  virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
  //}}AFX_VIRTUAL
  void                        InitializeDefaultColors( int *);                // Initialize Control With Default Colors

  COLORREF                GetSelectedColorValue( void );                        // Get Selected Color Value
  LPCTSTR                        GetSelectedColorName( void );                        // Get Selected Color Name

  void                        SetSelectedColorValue( COLORREF crClr );// Set Selected Color Value
  void                        SetSelectedColorName( LPCTSTR cpColor );// Set Selected Color Name

  bool                        RemoveColor( LPCTSTR cpColor );                        // Remove Color From List
  bool                        RemoveColor( COLORREF crClr );                        // Remove Color From List

  int                                AddColor( LPCTSTR cpName,
    COLORREF crColor );                                // Add A New Color


  void                        DDX_ColorPicker( CDataExchange *pDX,
    int iIDC, COLORREF &crColor );        // DDX Function For COLORREF Value

  void                        DDX_ColorPicker( CDataExchange *pDX,
    int iIDC, CString &sName );                // DDX Function For Color Name

  // Implementation
public:
  virtual ~CColorCombo();

protected:
	virtual void PostNcDestroy();

  // Generated message map functions
protected:
  //{{AFX_MSG(CColorCombo)
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

private:
  static
    SColorAndName        ms_pColors[];                                                        // Array Of Colors And Names

  TCHAR                        m_cColorName[ CCB_MAX_COLOR_NAME ];                // Name Of Selected Color

  TCHAR *char_to_TCHAR(char *pInput);

  //
  //        Prevent Misuse Of Copies...
  //
  /**/
#if 0
  CColorCombo( const CColorPickerCB& rSrc );
  CColorCombo        &operator=( const CColorPickerCB& rSrc );
#endif

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCOMBO_H__BD768E6A_1C14_4F39_BF05_85B16DABF59A__INCLUDED_)
#if 0

public:

public:

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CColorPickerCB)
protected:
  virtual void PreSubclassWindow();
  virtual void OnLButtonDown(UINT nFlags, CPoint point);
  // hjg 01-27-2005         afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

  //}}AFX_VIRTUAL
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);


  // Generated message map functions
protected:
  //{{AFX_MSG(CColorPickerCB)        //}}AFX_MSG
  DECLARE_MESSAGE_MAP()


#endif
