/*|*\
|*|  File:      widgets/colorpicker/ColorCombo.cpp
|*|       (derived from FocusEditCtrl.cpp)
|*|
|*|  By:        James R. Twine
|*|    Copyright 1998, James R. Twine
|*|    Copyright 1999-2000, TransactionWorks, Inc.
|*|  Date:      xxxx, xxxx, 1998
|*|
|*|    This implementes a ComboBox control that can be
|*|    used to display and provide selection for a specific
|*|    set of colors.  The standard set of colors provided
|*|    by the control are a subset of the X11 colorset, and
|*|    are the ones available in (and the color names
|*|    recognized by) Internet Explorer.
|*|
|*|    The ComboBox that is subclassed must have the
|*|    Owner Draw Fixed and Has Strings styles.
|*|
|*|    This is based on code that was originally found on
|*|    CodeGuru, and was (c) 1997 Baldvin Hansson.
|*|
|*|    A bug fix by Marcel Galem was added to provide
|*|    correct masking of the COLORREF values.
|*|
|*|    DDX routines were provided by Paul Wardle
|*|    (paul.wardle@siemenscomms.co.uk)
|*|
|*|    This Code May Be Freely Incorporated Into
|*|    Projects Of Any Type Subject To The Following
|*|    Conditions:
|*|
|*|    o This Header Must Remain In This File, And Any
|*|      Files Derived From It
|*|    o Do Not Misrepresent The Origin Of Any Parts Of
|*|      This Code (IOW, Do Not Claim You Wrote It)
|*|
|*|    A "Mention In The Credits", Or Similar Acknowledgement,
|*|    Is *NOT* Required.  It Would Be Nice, Though! :)
|*|
\*|*/

// ColorCombo.cpp : implementation file
//

#include "stdafx.h"
#include "ColorCombo.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BLOCK_OF_COLOR_WIDTH 20


/////////////////////////////////////////////////////////////////////////////
// CColorCombo
// Load/Create Standard Colors...
//
extern "C" XCOLOR XMetaColorArray[TOTAL_NUMBER_OF_COLORS];

extern LPWSTR g2pvt_simple_tchar_to_wide_string (TCHAR *pText);

SColorAndName CColorCombo::ms_pColors[TOTAL_NUMBER_OF_COLORS];
TCHAR TextOutput[MAX_PATH];

CColorCombo::CColorCombo ()
{
}

CColorCombo::~CColorCombo ()
{
}

TCHAR *CColorCombo::char_to_TCHAR (char *pInput)
{
  int nCodePage = CP_ACP;
  DWORD dwFlags = MB_PRECOMPOSED |MB_ERR_INVALID_CHARS;
  int nRet;
  unsigned short nCount = strlen(pInput);

  // use static buffer
  memset(TextOutput, 0, sizeof(TextOutput));
  nRet = MultiByteToWideChar(nCodePage, dwFlags, pInput, nCount, TextOutput, nCount+1);
  if (0 == nRet)
  {
    fprintf(stderr,
      "char_to_TCHAR: failure in call to MultiByteToWideChar: %s\n",
      g2pvt_get_last_error_string());
    TextOutput[0] = 0;
    return TextOutput;
  }
  return TextOutput;
}


BEGIN_MESSAGE_MAP(CColorCombo, CComboBox)
//{{AFX_MSG_MAP(CColorCombo)
ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorCombo message handlers


void CColorCombo::DrawItem (LPDRAWITEMSTRUCT pDIStruct)
{
  COLORREF crColor = 0;
  COLORREF crNormal = GetSysColor(COLOR_WINDOW);
  COLORREF crSelected = GetSysColor(COLOR_HIGHLIGHT);
  COLORREF crText = GetSysColor(COLOR_WINDOWTEXT);
  CBrush brFrameBrush;
  TCHAR cColor[ CCB_MAX_COLOR_NAME ]; // Color Name Buffer
  CRect rItemRect(pDIStruct -> rcItem);
  CRect rBlockRect(rItemRect);
  CRect rTextRect(rBlockRect);
  CDC dcContext;
  int iBlockWidth = 0;
  int iItem = pDIStruct -> itemID;
  int iState = pDIStruct -> itemState;

  if (!dcContext.Attach(pDIStruct -> hDC)) // Attach CDC Object
  {
    return; // Stop If Attach Failed
  }
  iBlockWidth = BLOCK_OF_COLOR_WIDTH;
  brFrameBrush.CreateStockObject(BLACK_BRUSH); // Create Black Brush

  if (iState & ODS_SELECTED) // If Selected
  { // Set Selected Attributes
    dcContext.SetTextColor((0x00FFFFFF & ~ (crText))); // Set Inverted Text Color
    // (With Mask)
    dcContext.SetBkColor(crSelected); // Set BG To Highlight Color
    dcContext.FillSolidRect(&rBlockRect, crSelected); // Erase Item
  }
  else // If Not Selected
  { // Set Standard Attributes
    dcContext.SetTextColor(crText); // Set Text Color
    dcContext.SetBkColor(crNormal); // Set BG Color
    dcContext.FillSolidRect(&rBlockRect, crNormal); // Erase Item
  }
  if (iState & ODS_FOCUS) // If Item Has The Focus
  {
    dcContext.DrawFocusRect(&rItemRect); // Draw Focus Rect
  }
  //
  // Calculate Text Area...
  //
  rTextRect.left += (iBlockWidth + 2); // Set Start Of Text
  rTextRect.top += 2; // Offset A Bit

  //
  // Calculate Color Block Area..
  //
  rBlockRect.DeflateRect(CSize(2, 2)); // Reduce Color Block Size
  rBlockRect.right = iBlockWidth; // Set Width Of Color Block

  //
  // Draw Color Text And Block...
  //
  if (iItem != -1) // If Not An Empty Item
  {
    int iChars = GetLBText(iItem, cColor); // Get Color Text
    int iaTabStops[ 1 ] = { 50 };

    _ASSERTE(iChars != LB_ERR); // Sanity Check

    if (iState & ODS_DISABLED) // If Disabled
    {
      crColor = ::GetSysColor(COLOR_GRAYTEXT); // Get Inactive Text Color
      dcContext.SetTextColor(crColor); // Set Text Color
    }
    else // If Normal
    {
      crColor = GetItemData(iItem); // Get Color Value
    }
    dcContext.SetBkMode(TRANSPARENT); // Transparent Background
    dcContext.TabbedTextOut(rTextRect.left,
      rTextRect.top, cColor, iChars, 1,
      iaTabStops, 0); // Draw Color Name

    dcContext.FillSolidRect(&rBlockRect, crColor); // Draw Color

    dcContext.FrameRect(&rBlockRect, &brFrameBrush); // Draw Frame
  }
  dcContext.Detach(); // Detach DC From Object

  return; // Done!
}

void CColorCombo::OnLButtonDown (UINT nFlags, CPoint ptPoint)
{
  if (GetFocus() != this) // If Not Focused
  {
    SetFocus(); // Gain Focus
  }
  CComboBox::OnLButtonDown(nFlags, ptPoint); // Do Default

  return; // Done!
}


//void CColorCombo::InitializeDefaultColors (void)
void CColorCombo::InitializeDefaultColors (int TokenList[])
{
  // Done!
  _ASSERTE(m_hWnd); // We Must Be Created First...

#if defined (_INCLUDE_COLOR_INFO)
  COLORREF crColor;
  TCHAR caColor[ 256 ];
#endif
  int iAddedItem = -1;
  int iColors = TOTAL_NUMBER_OF_COLORS; // Number Of Colors Set

  ResetContent(); // Clear All Colors

#if defined (_INCLUDE_COLOR_INFO)
  SetDroppedWidth(400); // Increase Drop Width
#endif
  int i;
  TCHAR *pTCHAR;
  for (i = 0; i < TOTAL_NUMBER_OF_COLORS; i++) // get colors from GENSYM table
  {
    if (0 != TokenList[i])
    {
      pTCHAR = char_to_TCHAR(XMetaColorArray[i].szColor);
      memcpy(ms_pColors[i].m_cColor, pTCHAR, sizeof(ms_pColors[i]));
      ms_pColors[i].m_crColor = XMetaColorArray[i].rgbColor;

    }
  }

  // This is very inefficient!  To be improved!  -jv, 2/07/05
  for (i = 1; i <= TOTAL_NUMBER_OF_COLORS; i++)
  {
    for (int iColor = 0; iColor < iColors; iColor++) // For All Colors
    {
      if (i == TokenList[iColor])
      {
#if defined (_INCLUDE_COLOR_INFO)
        crColor = ms_pColors[ iColor ].m_crColor; // Store The Color Value

        _ASSERTE(_stprintf(caColor,
          _T("%s\t\t%02X%02X%02X"), ms_pColors[
          iColor ].m_cColor, GetRValue(crColor),
          GetGValue(crColor), GetBValue(crColor))
          < 255); // Build The Debug String
        iAddedItem = AddString(caColor); // Set Color Name/Text
#else
        iAddedItem = AddString(ms_pColors[
          iColor ].m_cColor); // Set Color Name/Text
#endif
        if (iAddedItem == CB_ERRSPACE) // If Not Added
        {
#pragma warning (disable : 4127)
          ASSERT(FALSE); // Let 'Em Know What Happened...
#pragma warning (default : 4127)
          break; // Stop
        }
        else // If Added Successfully
        {
          SetItemData(iAddedItem, ms_pColors[
            iColor ].m_crColor); // Set Color RGB Value
        }
      }
    }
  }
  return;
}


COLORREF CColorCombo::GetSelectedColorValue (void)
{
  int iSelectedItem = GetCurSel(); // Get Selected Item

  if (iSelectedItem == CB_ERR) // If Nothing Selected
  {
    return (RGB(0, 0, 0)); // Return Black
  }
  return (GetItemData(iSelectedItem)); // Return Selected Color
}


LPCTSTR CColorCombo::GetSelectedColorName (void)
{
  int iSelectedItem = GetCurSel(); // Get Selected Item

  if (iSelectedItem != CB_ERR) // If Something Selected
  {
    GetLBText(iSelectedItem, m_cColorName); // Store Name Of Color
  }
  else // If Nothing Selected
  {
    m_cColorName[ 0 ] = _T('\0'); // Terminate Color Name Buffer (Zero Length String)
  }
  return (m_cColorName); // Return Selected Color Name
}


void CColorCombo::SetSelectedColorValue (COLORREF crClr)
{
  int iItems = GetCount();

  for (int iItem = 0; iItem < iItems; iItem++)
  {
    if (crClr == GetItemData(iItem)) // If Match Found
    {
      SetCurSel(iItem); // Select It
      break; // Stop Looping
    }
  }
  return; // Done!
}


void CColorCombo::SetSelectedColorName (LPCTSTR cpColor)
{
  int iItems = GetCount();
  TCHAR cColor[ CCB_MAX_COLOR_NAME ];

  for (int iItem = 0; iItem < iItems; iItem++)
  {
    GetLBText(iItem, cColor); // Get Color Name
    if (!_tcsicmp(cColor, cpColor)) // If Match Found
    {
      SetCurSel(iItem); // Select It
      break; // Stop Looping
    }
  }
  return; // Done!
}


int CColorCombo::AddColor (LPCTSTR cpColor, COLORREF crColor)
{
  int iIndex = CB_ERR;

  _ASSERTE(cpColor); // Need This!

#if defined (_INCLUDE_COLOR_INFO)
  TCHAR caColor[ 256 ];

  _ASSERTE(_stprintf(caColor,
    _T("%s\t\t%02X%02X%02X"), cpColor, GetRValue(
    crColor), GetGValue(crColor), GetBValue(
    crColor)) < 255); // Build The Debug String
  iIndex = AddString(caColor); // Set Color Name/Text
#else
  iIndex = AddString(cpColor); // Insert Just The Color
#endif
  if (iIndex != CB_ERR) // If Inserted
  {
    SetItemData(iIndex, (DWORD)crColor); // Set The Color Value
  }
  return (iIndex); // Return Insertion Locatiom Or Failure Code
}


bool CColorCombo::RemoveColor (LPCTSTR cpColor)
{
  TCHAR cColor[ CCB_MAX_COLOR_NAME ];
  bool bRemoved = false;
  int iItems = GetCount();

  for (int iItem = 0; iItem < iItems; iItem++)
  {
    GetLBText(iItem, cColor); // Get Color Name
    if (!_tcsicmp(cColor, cpColor)) // If Match Found
    {
      if (DeleteString(iItem) != CB_ERR) // Remove It
      {
        bRemoved = true; // Set Flag If Removed
        break; // Stop Checking
      }
    }
  }
  return (bRemoved); // Done!
}


bool CColorCombo::RemoveColor (COLORREF crClr)
{
  bool bRemoved = false;
  int iItems = GetCount();

  for (int iItem = 0; iItem < iItems; iItem++)
  {
    if (crClr == GetItemData(iItem)) // If Desired Color Found
    {
      if (DeleteString(iItem) != CB_ERR) // Remove It
      {
        bRemoved = true; // Set Flag If Removed
        break; // Stop Checking
      }
    }
  }
  return (bRemoved); // Done!
}


int CColorCombo::CompareItem (LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
  // TODO: Add your code to determine the sorting order of the specified items
  // return -1 = item 1 sorts before item 2
  // return 0 = item 1 and item 2 sort the same
  // return 1 = item 1 sorts after item 2

  return 0;
}


void CColorCombo::MeasureItem (LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
  lpMeasureItemStruct->itemHeight = ::GetSystemMetrics(SM_CYMENU);
}
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

void CColorCombo::PostNcDestroy() 
{
	CComboBox::PostNcDestroy();

	delete this;
}
