// GensymEditBox.cpp : implementation file
//

#include "stdafx.h"
#include "GensymEditBox.h"

extern CONTROLHWND* g2pvt_get_control_hwnd_by_controlId (DIALOGINFO *pdlgInfo, long controlId);
extern void g2pvt_ddlg_respond (HWND hwndDlg, int controlId, int respcode);
extern void g2pvt_get_g2_selection(HWND hwndEdit, DWORD *pStart, DWORD *pEnd);
extern void g2pvt_set_g2_selection(HWND hwndEdit, DWORD start, DWORD end);

static LPCTSTR $StringDelim =   _T("\001");
static LPCTSTR $StringDelim2=   _T("\002");
static LPCTSTR $StringDelims=   _T("\001\002");

extern wchar_t *g2pvt_windows_to_g2_text (wchar_t *pText);

extern "C" void g2pvt_trace(const char *fmt, ...);
#define PRINTF g2pvt_trace

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGensymEditBox

CGensymEditBox::CGensymEditBox(CONTROLITEM *pControl) //control item information)
{
 
   m_bBGColorValueSetByUser = FALSE;
   m_bTxColorValueSetByUser = FALSE;
   m_bSelectionValuesSetByUser = FALSE;
   m_pControl = pControl;
   m_crText = 0;
   m_crBackGnd = 0;
   m_strMask.Empty();
   m_strLiteral.Empty();
   m_strDefault.Empty();
   m_start = 0;
   m_end = 0;
}

CGensymEditBox::~CGensymEditBox()
{
}


BEGIN_MESSAGE_MAP(CGensymEditBox, GensymMaskEdit)
	//{{AFX_MSG_MAP(CGensymEditBox)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
 	ON_WM_LBUTTONUP()
 	ON_WM_KEYDOWN()
    ON_MESSAGE(EM_SETSEL,OnSetSel)
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CGensymEditBox::Create(DWORD dwStyles, RECT *pRect, CWnd *pParent, int control_id)
{
   m_pParent = pParent; // save the parent for use later
   return CreateEx(WS_EX_CLIENTEDGE, _T("EDIT"), NULL, dwStyles, *pRect, pParent, control_id, NULL);
}

// NOTE: Code is duplicated in SubClassTextBxFunc()
UINT CGensymEditBox::OnGetDlgCode()
{
  UINT result = GensymMaskEdit::OnGetDlgCode();

  if(m_bSelectionValuesSetByUser)
	result &= ~DLGC_HASSETSEL;
  return result;
}

void CGensymEditBox::OnSetFocus(CWnd* pOldWnd)
{
  int s, e;
  GetSel(s, e);

  GensymMaskEdit::OnSetFocus(pOldWnd);

  if (!CanUseMask())
	return;

  if(!m_bSelectionValuesSetByUser)
	return;

  // If the selection was user-specified, put it back. The codejock control, for
  // some reason, sets the selection to be empty in its OnSetFocus() handler.
  m_nStartChar = s;
  m_nEndChar = e;
  CorrectPosition(m_nStartChar); // NOTE: This is an internal, private function of CXTMaskEdit.
  CorrectPosition(m_nEndChar);

  SetSel(m_nStartChar, m_nEndChar);
}


void CGensymEditBox::OnChange()
{
   CWnd *pWnd;
   pWnd = GetFocus();
   if (this == pWnd) 
   {
      // we only want a response if the edit is due
      // to an update via the UI and not programmatically
      g2pvt_ddlg_respond(m_pParent->m_hWnd, m_pControl->_controlId, m_pControl->_respcode);
   }
}
HBRUSH CGensymEditBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
   // TODO: Return a non-NULL brush if the parent's handler should not be called
 	//set text color
   if (TRUE  == m_bTxColorValueSetByUser)
   {
	 SetTextColor(m_crText);
     pDC->SetBkMode(TRANSPARENT);
     pDC->SetTextColor(m_crText);
   }
	//set the text's background color
   if (TRUE  == m_bBGColorValueSetByUser)	
   {
	 SetBackColor(m_crBackGnd);
   }

   // sets control background
   return m_brBackGnd;
}



void CGensymEditBox::SetBackColor(COLORREF rgb)
{
	//set background color ref (used for text's background)
    
	m_crBackGnd = rgb;
	
	//free brush
	if (m_brBackGnd.GetSafeHandle())
       m_brBackGnd.DeleteObject();
	//set brush to new color
	m_brBackGnd.CreateSolidBrush(rgb);
}


void CGensymEditBox::SetTextColor(COLORREF rgb)
{
	//set text color ref
   
	m_crText = rgb;
}



/*****************************************************************************
* wchar_t *g2pvt_get_contents_of_gensym_edit_control (HWND hwndControl)
*
*   Description: build up the return string a la:
*     "textbox value\001start\002end\001rgb\001rgb"
*   Input Arguments:
*   Returns: a freshly malloc'ed wide string, or NULL
*   Notes: it is the caller's responsibility to free the returned value.
*     LIMIT_TEXT_BOXES
*
*     -----
*   Modifications:
*****************************************************************************/
 wchar_t *g2pvt_get_contents_of_gensym_edit_control (HWND hwndControl,  CONTROLITEM *pitem)
{
  union
  {
    COLORREF color_ref;
    BYTE rgb_array[sizeof(long)];
  } my_color;

  wchar_t *pszValue = NULL;
  wchar_t *converted_text;
  int nLen = 0;

  DWORD start;
  DWORD end;
  TCHAR szStartValue[10];
  TCHAR szEndValue[10];
  TCHAR r_buf1[3];
  TCHAR g_buf1[3];
  TCHAR b_buf1[3];
  TCHAR r_buf2[3];
  TCHAR g_buf2[3];
  TCHAR b_buf2[3];
  CONTROLHWND *ctrl_hwnd = NULL;
  DIALOGINFO *dialog_info = NULL;
  HWND hwndDlg;

  CGensymEditBox *p;

  hwndDlg = GetParent(hwndControl);
  if (hwndDlg == NULL) return NULL;

  
  dialog_info = (DIALOGINFO *)::GetWindowLong(hwndDlg, GWL_USERDATA);
  if (dialog_info == NULL) return NULL;

  ctrl_hwnd = g2pvt_get_control_hwnd_by_controlId(dialog_info, pitem->_controlId);
  if (ctrl_hwnd == NULL) return NULL;

  p = (CGensymEditBox*)(ctrl_hwnd->pObj);
  
  g2pvt_get_g2_selection(hwndControl, &start, &end);
  wsprintf(szStartValue, L"%d", start);
  wsprintf(szEndValue, L"%d", end);

  // get the colors the user set for this control earlier

  my_color.color_ref = 	p->GetTextColor();

  _snwprintf(b_buf1, 3, L"%02X", my_color.rgb_array[2]);
  my_color.rgb_array[2] = 0;

  _snwprintf(g_buf1, 3, L"%02X", my_color.rgb_array[1]);
  my_color.rgb_array[1] = 0;

  _snwprintf(r_buf1, 3, L"%02X", my_color.rgb_array[0]);

  my_color.color_ref =  p->GetBackColor();

  _snwprintf(b_buf2, 3, L"%02X", my_color.rgb_array[2]);
  my_color.rgb_array[2] = 0;

  _snwprintf(g_buf2, 3, L"%02X", my_color.rgb_array[1]);
  my_color.rgb_array[1] = 0;

  _snwprintf(r_buf2, 3, L"%02X", my_color.rgb_array[0]);
  
  // get the length of the text associated with the edit control
  // does not include null terminator
  nLen = SendMessage(hwndControl, WM_GETTEXTLENGTH, 0, 0);
  nLen += 1;// delimiter \001
  nLen += _tcslen(szStartValue);  // start
  nLen += 1;// delimiter \002
  nLen += _tcslen(szEndValue); // end
  nLen += 1; //delimter \001
  nLen += 6+1+6; //rgb\001rgb

  pszValue = (wchar_t *)malloc((nLen+1) * sizeof(wchar_t));
  if (pszValue == NULL) {
    return NULL;            // out of memory!
  }
  ZeroMemory((PVOID)pszValue, sizeof(wchar_t) * (nLen + 1));

  SendMessage(hwndControl, WM_GETTEXT, nLen+1, (LPARAM)pszValue);

  lstrcat(pszValue,$StringDelim);
  lstrcat(pszValue, szStartValue);
  lstrcat(pszValue,$StringDelim2);
  lstrcat(pszValue, szEndValue);
  lstrcat(pszValue,$StringDelim);
  if (p->TxColorSetByUser())
  {
    lstrcat(pszValue, r_buf1);
    lstrcat(pszValue, g_buf1);
    lstrcat(pszValue, b_buf1);
  }
  lstrcat(pszValue,$StringDelim);
  if (p->BGColorSetByUser())
  {
    lstrcat(pszValue, r_buf2);
    lstrcat(pszValue, g_buf2);
    lstrcat(pszValue, b_buf2);
  }

  converted_text = g2pvt_windows_to_g2_text(pszValue);
  free(pszValue);
  return converted_text;
}
void CGensymEditBox::SetTextInfo(BOOL bSelectionValuesSetByUser, BOOL bTxColorValueSetByUser, BOOL bGBColorValueSetByUser, 
                                 BOOL start, int end, COLORREF crText, COLORREF crBackGnd)
  
{
  m_bSelectionValuesSetByUser = bSelectionValuesSetByUser;
  m_bBGColorValueSetByUser = bGBColorValueSetByUser;
  m_bTxColorValueSetByUser = bTxColorValueSetByUser;
  m_start = start;
  m_end = end;
  m_crBackGnd = crBackGnd;
  m_crText = crText;
 
}
// "start\002end\001rgb\001rgb"
void CGensymEditBox::ParseTextInfo(CString strTextInfo,
                                   BOOL &bSelectionValuesSetByUser, BOOL &bTxColorValueSetByUser, BOOL &bGBColorValueSetByUser, 
                                   BOOL &start, int &end, COLORREF &crText, COLORREF &crBackGnd)
{
 
  TCHAR *pSubToken;
  TCHAR *pSelection;
  TCHAR *pText;
  TCHAR *pBackground;
  int red;
  int blue;
  int green;
  TCHAR *pDelim;
  TCHAR *value;
  int len;
  CDC *pDC;
      
  bSelectionValuesSetByUser = m_bSelectionValuesSetByUser;
  start = m_start;
  end = m_end;
  pDC = GetDC();
  bGBColorValueSetByUser = m_bBGColorValueSetByUser;
  bTxColorValueSetByUser = m_bTxColorValueSetByUser;
  crText =    m_crText; // default the color to what it is now
  crBackGnd = m_crBackGnd;   // default the color to what it is now
 
  if (strTextInfo.IsEmpty())
      return;
  len = strTextInfo.GetLength()+1;
  value = ( TCHAR *)malloc(len*sizeof(TCHAR));
  _tcscpy(value, strTextInfo);

  pDelim = _tcschr(value, $StringDelim[0]);
  pText = pDelim+1;
 
  pSelection = _tcstok(value, $StringDelim); // this will NULL out the delimiter
  if (!pSelection)
  {
     free(value);
     return;
  }
  if ($StringDelim2[0] != *pSelection)  // if we don't hit this delim, we have a selection
  {
     int chars_to_skip;
     pSubToken = _tcstok(value, $StringDelim2);
     if (!pSubToken)
     {
         free(value);
         return;
     }
     start = _wtoi(pSubToken);
     chars_to_skip = 1 + _tcslen(pSubToken);
     pSubToken = _tcstok(pSubToken+chars_to_skip, $StringDelim);
     if (!pSubToken)
     {
         free(value);
         return;
     }
     end = _wtoi(pSubToken);
     bSelectionValuesSetByUser = TRUE;
  }

  //  convert from g2 rgb format to windows rgb format ie. widestring "RRGGBB" to COLORREF
  if ($StringDelim[0] != *pText) // if we don't hit this delim, we have a text color
  {
     bTxColorValueSetByUser = TRUE;
     swscanf(pText, _T("%2x%2x%2x"), &red, &green, &blue);
     crText = RGB(red, green, blue);
  }
  pDelim = _tcschr(pText, $StringDelim[0]);
  pBackground = pDelim+1;

  if (!pBackground)
  {
       free(value);
       return;
  }
 
  if (0 != *pBackground)
  {
    // if we don't hit the end of text, we have a background color
     bGBColorValueSetByUser = TRUE;
     swscanf(pBackground, _T("%2x%2x%2x"), &red, &green, &blue);
     crBackGnd = RGB(red, green, blue);
  }
  free(value);
}

//"mask|literal|default text value"
void CGensymEditBox::SetMaskInfo( CString strMask, CString strLiteral, CString strDefault)
{
    m_strMask = strMask;
    m_strLiteral = strLiteral;
    m_strDefault = strDefault;
}


//"mask|literal|default text value"
// could be just the text value, or mask|literal|text
void CGensymEditBox::ParseMaskInfo(CString strMaskInfo, CString &strMask, CString &strLiteral, CString &strDefault)
{
    int idx1 = -1;
    int idx2 = -1;
    CString strTemp;
    int i;
    int len;
    strMask.Empty();
    strLiteral.Empty();

    strDefault = strMaskInfo;  //perhaps we have only a the text
   
    idx1 = strMaskInfo.Find(_T('|')); // if we have anything else, assume both the mask and the literal here
    if (-1 != idx1)
        idx2 = strMaskInfo.Find(_T('|'), idx1+1); 
    if (-1 != idx2)
    {
        strDefault.SetAt(idx1, 0);
        strMask    = strDefault;
        strLiteral = strMaskInfo.Mid(idx1+1, idx2- idx1 -1);
        len = strMaskInfo.GetLength();
        strDefault = strMaskInfo.Right(len - (idx2+1));
        if (strLiteral.IsEmpty() || strMask.IsEmpty())
        {
            strLiteral = strDefault;
            strMask    = strDefault;
            for (i = 0; i < m_strDefault.GetLength(); i++) 
            {
                strLiteral.SetAt(i,_T('_')); //initialize mask to accept anything
                strMask.SetAt(i,_T('&'));    
            }
        }
    }
    else 
    {
        OutputDebugString(_T("GensymEdit Missing Mask params \n"));
    }
}

 //"mask|literal|default text value\001start\002end\001rgb\001rgb"
void CGensymEditBox::ParseInputString( TCHAR *pValue, CString &strMaskInfo, CString &strTextInfo)
{
  int idx;

  m_strInput = pValue;
  idx = m_strInput.FindOneOf($StringDelims);
 
  if (-1 != idx)
  {
    if (m_strInput.GetAt(idx) == _T('\001'))
    {
      strMaskInfo = m_strInput.Left(idx);
      strTextInfo = m_strInput.Right(m_strInput.GetLength() - (idx+1));
    }
  }
  else
  {
    strTextInfo.IsEmpty();
    strMaskInfo = m_strInput;
  }
}

int CGensymEditBox::UseTextInfo(int updateType)
{
  long result = DYNAMIC_DIALOG_UPDATE_SUCCEEDED;
  CString strTemp;
  if (m_bTxColorValueSetByUser)
  {
     switch(updateType)
     {
        case REPLACE:
            SetWindowText(m_strDefault);
        break;
        case ADD:
            GetWindowText(strTemp);
            SetWindowText(m_strDefault + strTemp);
        break;
        default:
          result = DYNAMIC_DIALOG_UPDATE_FAILED;
        break;

     }
  }
  if (DYNAMIC_DIALOG_UPDATE_SUCCEEDED == result)
  {
     if (m_bSelectionValuesSetByUser)
     {
	   g2pvt_set_g2_selection(m_hWnd, m_start, m_end);
     }
  }

  return result;
}

/*****************************************************************************
* long g2pvt_modify_gensym_edit (HWND hwndDlg, CONTROLITEM *pcontrol,
*                                wchar_t *value, int updateType)
*
*   Description:
*   Input Arguments:
*   Returns:
*   Notes:
*
*     -----
*   Modifications:
*****************************************************************************/
long g2pvt_modify_gensym_edit (HWND hwndDlg, CONTROLITEM *pControl, wchar_t *value, HWND hWnd, int updateType)
{
  CWnd *pParent;
  CGensymEditBox *pGEB;
  pGEB = (CGensymEditBox*)CWnd::FromHandle(hWnd);
  pParent = CWnd::FromHandle(hwndDlg);
  long result;
  CString strTemp;
  CString strMaskInfo;
  CString strTextInfo;
  CString strMask;
  CString strLiteral;
  CString strDefault;
  BOOL bSelectionValuesSetByUser;
  BOOL bTxColorValueSetByUser;
  BOOL bGBColorValueSetByUser; 
  int start; 
  int end; 
  COLORREF crTextColor;
  COLORREF crBackColor;

  pGEB->ParseInputString(value, strMaskInfo, strTextInfo);

  pGEB->ParseMaskInfo(strMaskInfo, strMask, strLiteral, strDefault);
  pGEB->SetMaskInfo(strMask, strLiteral, strDefault);
  pGEB->UseMaskInfo();

  pGEB->ParseTextInfo(strTextInfo, bSelectionValuesSetByUser, bTxColorValueSetByUser, bGBColorValueSetByUser, start, end, crTextColor, crBackColor);
  pGEB->SetTextInfo(bSelectionValuesSetByUser, bTxColorValueSetByUser, bGBColorValueSetByUser, start, end, crTextColor, crBackColor);
  pGEB->UseTextInfo(updateType);


  result = DYNAMIC_DIALOG_UPDATE_SUCCEEDED;


  return result;
}


// Simulate EN_SELCHANGE
// NOTE: Code is duplicated in SubClassTextBxFunc().

void CGensymEditBox::OnLButtonUp(UINT nFlags, CPoint point)
{
  GensymMaskEdit::OnLButtonUp(nFlags, point);
  g2pvt_ddlg_respond(m_pParent->m_hWnd, m_pControl->_controlId, m_pControl->_respcode);
}

void CGensymEditBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  GensymMaskEdit::OnKeyDown(nChar, nRepCnt, nFlags);
  if(nChar != VK_SHIFT && nChar != VK_CONTROL)
	g2pvt_ddlg_respond(m_pParent->m_hWnd, m_pControl->_controlId, m_pControl->_respcode);
}

LRESULT CGensymEditBox::OnSetSel(WPARAM wParam, LPARAM lParam)
{
  LRESULT result = Default();
  if(GetFocus() == this)
	g2pvt_ddlg_respond(m_pParent->m_hWnd, m_pControl->_controlId, m_pControl->_respcode);
  return result;
}
