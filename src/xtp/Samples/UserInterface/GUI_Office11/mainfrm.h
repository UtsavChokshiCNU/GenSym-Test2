// mainfrm.h : interface of the CMainFrame class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "ruler.h"

class CMainFrame : public CXTPFrameWnd, CXTPOffice2007FrameHook
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
public:
	CXTPControlGalleryItems* m_pItemsShapes;
	CXTPControlGalleryItems* m_pItemsStyles;
	CXTPControlGalleryItems* m_pItemsStyleSet;
	CXTPControlGalleryItems* m_pItemsThemeColors;
	CXTPControlGalleryItems* m_pItemsThemeFonts;
	
	CXTPControlGalleryItems* m_pItemsFontTextColor;
	CXTPControlGalleryItems* m_pItemsFontBackColor;
	CXTPControlGalleryItems* m_pItemsFontFace;
	CXTPControlGalleryItems* m_pItemsFontSize;
	CXTPControlGalleryItems* m_pItemsUndo;
	CXTPControlGalleryItems* m_pItemsColumns;

	void CreateGalleries();
	void LoadIcons();
	int m_nShape;
	UINT m_nStyle;
	int m_nColumns;

	int m_nStyleSet;
	int m_nThemeColors;
	int m_nThemeFonts;

	BOOL m_bAnimation;
	BOOL m_bLayoutRTL;
	BOOL m_bIsRibbon;
	CXTPMessageBar m_wndMessageBar;

// Attributes
public:
	HICON m_hIconDoc;
	HICON m_hIconText;
	HICON m_hIconWrite;
	HICON GetIcon(int nDocType);

// Operations
public:
	BOOL CreateRibbonBar();
	BOOL CreateMiniToolBar();
	BOOL CreateMessageBar();

	void OnGalleryColumns(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateGalleryColumns(CCmdUI* pCmdUI);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CToolBar    m_wndToolBar;
	CXTPStatusBar  m_wndStatusBar;
	CRulerBar   m_wndRulerBar;

protected:  // control bar embedded members
	BOOL CreateToolBars();
	BOOL CreateStatusBar();
	BOOL CreateRulerBar();
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHelpFinder();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnCharColor();
	afx_msg void OnPenToggle();
	afx_msg void OnFontChange();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	afx_msg void OnClose();
	afx_msg void OnUpdateViewThemeOffice2000(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewThemeOffice2002(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewThemeOffice2003(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewThemeOffice2007(CCmdUI* pCmdUI);
	afx_msg void OnFileQuickPrint();
	afx_msg void OnUpdateFileQuickPrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAsOpenDocTxt();
	afx_msg void OnUpdateFileSaveAsOpenDocTxt(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAsOpenXml();
	afx_msg void OnUpdateFileSaveAsOpenXml(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAsPlainTxtDoc();
	afx_msg void OnUpdateFileSaveAsPlainTxtDoc(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAsRichTxt();
	afx_msg void OnUpdateFileSaveAsRichTxt(CCmdUI* pCmdUI);
	afx_msg void OnFileAbout();
	afx_msg void OnFileSendMail();
	afx_msg void OnUpdateFileSendMail(CCmdUI* pCmdUI);
	afx_msg void OnSendInEmail();
	afx_msg void OnInsertPicture();
	afx_msg void OnInsertDrawing();
	afx_msg void OnInsertObject();
	afx_msg void OnInsertDatetime();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnHundredPercent();
	afx_msg void OnDummyHandler();
	afx_msg void OnUpdateGalleryThemeColors(CCmdUI* pCmdUI);
	afx_msg LRESULT OnBarState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOpenMsg(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);
	afx_msg void OnCustomize();
	afx_msg int OnCreateCommandBar(LPCREATEBARSTRUCT lpCreatePopup);
	afx_msg void OnGalleryThemeColors(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOptionsStyle(UINT nStyle);
	afx_msg void OnUpdateOptionsStyle(CCmdUI* pCmdUI);
	afx_msg void OnBorders(UINT nID);
	afx_msg void OnUpdateBorders(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChangeThemes(CCmdUI* pCmdUI);
	afx_msg void OnMeasurements(UINT nItem);
	afx_msg void OnUpdateMeasurements(CCmdUI* pCmdUI);
	afx_msg void OnWordWrap(UINT nItem);
	afx_msg void OnUpdateWordWrap(CCmdUI* pCmdUI);
	//}}AFX_MSG


	//Function for 
	void EnableRibbonStyle();
	void EnableNormalStyle();
	void SwitchBorders(DWORD dwState);
	void OnViewTheme(UINT nTheme);
	afx_msg void OnUpdateMeasurements();
	DWORD m_dwBorders;
	CString m_csStylesPath;
	UINT	m_nRibbonStyle;
	UINT	m_nWordWrap;
	UINT	m_nMeasurements;
	DECLARE_MESSAGE_MAP()
};
