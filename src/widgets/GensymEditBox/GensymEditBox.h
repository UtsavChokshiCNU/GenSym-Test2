/////////////////////////////////////////////////////////////////////////////
// CGensymEditBox window

#pragma once

#include "..\\..\\ext\\c\\dyndlgs.h"

#define _XTP_STATICLINK
#include <XTToolkitPro.h>

class GensymMaskEdit : public CXTMaskEdit
{
  int m_controlId;

public:
  void SetControlId(int InControlId)
  {
    m_controlId = InControlId;
  }
protected:
  virtual void PostNcDestroy()
  {
	CXTMaskEdit::PostNcDestroy();
  }
};

class CGensymEditBox : public GensymMaskEdit
{
// Construction
public:
   
    CGensymEditBox(CONTROLITEM *pControl); //control item information

// Implementation
public:
	virtual ~CGensymEditBox();
    BOOL Create(DWORD dwStyles, RECT *pRect, CWnd *pParent, int control_id);

    void ParseInputString(TCHAR *pValue, CString &strMaskInfo, CString &strTextInfo); // separate input string into mask info and text info

    void ParseMaskInfo(CString strMaskInfo, CString &strMask, CString &strLiteral, CString &strDefault); // separate out the parts of the mask
  
    void ParseTextInfo(CString strTextInfo, BOOL &bSelectionValuesSetByUser, BOOL &bTxColorValueSetByUser, BOOL &bGBColorValueSetByUser, 
                                   BOOL &start, int &end, COLORREF &crTextColor, COLORREF &crBackColor); // separate the parts of the text
    void SetTextInfo(BOOL bSelectionValuesSetByUser, BOOL bTxColorValueSetByUser, BOOL bGBColorValueSetByUser, 
                                 BOOL start, int end, COLORREF crTextColor, COLORREF drBackColor); // set the text information 
  

    void SetMaskInfo( CString strMask, CString strLiteral, CString strDefault); // set the mask information
    int  UseTextInfo(int updateType); // use the text information

 
    BOOL BGColorSetByUser() // was this color set by the users?
    {
       return m_bBGColorValueSetByUser;
    }

    BOOL TxColorSetByUser() // was this color set by the users?
    {
       return m_bTxColorValueSetByUser; 
    }

    COLORREF GetTextColor()
    {
        return m_crText;
    }

    COLORREF GetBackColor()
    {
        return m_crBackGnd;
    }

    virtual void UseMaskInfo()  // use the the mask information
    {
        if (m_strMask.IsEmpty() || m_strLiteral.IsEmpty() || m_strDefault.IsEmpty())
            return; // no mask set
    
        CXTMaskEdit::SetEditMask( m_strMask,  m_strLiteral, m_strDefault);
    }

    void GetEditMask(TCHAR *lpszMask, TCHAR *lpszLiteral, TCHAR *lpszDefault) // get the mask information
    {
        _tcscpy(lpszMask,    m_strMask);
        _tcscpy(lpszLiteral, m_strLiteral);
        _tcscpy(lpszDefault, m_strDefault);
    }

  
	// Generated message map functions
protected:
	//{{AFX_MSG(CGensymEditBox)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);  // change the edit box colors
	afx_msg void OnChange();  // send message to G2
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); // send message to G2
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags); // send message to G2
    afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
    afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

  

 virtual void PostNcDestroy()
  {
	GensymMaskEdit::PostNcDestroy(); // auto cleanup

	delete this;
  }

	DECLARE_MESSAGE_MAP()

private:
 
  CWnd *m_pParent; // parent of this control
  CONTROLITEM *m_pControl; //control item information

 
  int  m_controlId;
  CBrush m_brBackGnd;  //background brush



  CString m_strInput;    // both mask and extended text info

  CString m_strMaskInfo; // string with all the mask info
  CString m_strMask; // what can be typed
  CString m_strLiteral; // where can the user type
  CString m_strDefault; // default string information

  CString m_strTextInfo; // string with extended text info 

  BOOL m_bSelectionValuesSetByUser;
  BOOL m_bBGColorValueSetByUser;
  BOOL m_bTxColorValueSetByUser;
  int  m_start;
  int  m_end;
  COLORREF m_crText;
  COLORREF m_crBackGnd;

  void SetTextColor(COLORREF rgb);
  void SetBackColor(COLORREF rgb);
};
