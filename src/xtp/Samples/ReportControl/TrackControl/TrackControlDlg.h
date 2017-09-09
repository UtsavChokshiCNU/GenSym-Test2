// TrackControlDlg.h : header file
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTrackControlDlg dialog


class CReportViewRecord : public CXTPReportRecord
{
	DECLARE_SERIAL(CReportViewRecord)
public:
	CReportViewRecord();
	CReportViewRecord(int j);
};

class CTrackControlDlg : public CXTPResizeDialog
{
// Construction
public:
	CTrackControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTrackControlDlg)
	enum { IDD = IDD_REPORTDIALOG_DIALOG };
	CSliderCtrl	m_wndSlider;
	CScrollBar	m_wndScrollBar;
	CXTPTrackControl m_wndTrackControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	HACCEL  m_hAccelTable;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 

	void RepositionControls();

// Implementation
protected:
	HICON m_hIcon;

	BOOL m_bClassicStyle;

	// Generated message map functions
	//{{AFX_MSG(CTrackControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnUseTimeOffsetMode();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI *pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI *pCmdUI);
	afx_msg void OnViewGroupbox();
	afx_msg void OnUpdateViewGroupbox(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnViewClassicStyle();
	afx_msg void OnAppAbout();
	afx_msg void OnFlexibleDrag();
	afx_msg void OnUpdateViewClassicStyle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlexibleDrag(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnSnapToBlocks();
	afx_msg void OnUpdateSnapToBlocks(CCmdUI* pCmdUI);
	afx_msg void OnSnapToMarkers();
	afx_msg void OnUpdateSnapToMarkers(CCmdUI* pCmdUI);
	afx_msg void OnAllowblockmove();
	afx_msg void OnUpdateAllowblockmove(CCmdUI* pCmdUI);
	afx_msg void OnAllowblockscale();
	afx_msg void OnUpdateAllowblockscale(CCmdUI* pCmdUI);
	afx_msg void OnAllowRowResize();
	afx_msg void OnUpdateAllowRowResize(CCmdUI* pCmdUI);
	afx_msg void OnScaleOnResize();
	afx_msg void OnUpdateScaleOnResize(CCmdUI* pCmdUI);
	afx_msg void OnAllowblockRemove();
	afx_msg void OnUpdateAllowblockRemove(CCmdUI* pCmdUI);
	afx_msg void OnShowWorkarea();
	afx_msg void OnUpdateShowWorkarea(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnRClick(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnHeaderRClick(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnPropertyChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	
	afx_msg void OnTrackSliderChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTrackTimeLineChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTrackMarkerChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTrackBlockChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnTrackSelectedBlocksChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	DECLARE_MESSAGE_MAP()

public:
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

