// SkinPropertyPageThemes.h : header file
//

#ifndef __SKINPROPERTYPAGETHEMES_H__
#define __SKINPROPERTYPAGETHEMES_H__

struct THEMEINFO
{
	CString csIniFileName;
	CString csColorSchemes;
	CString csSizes;
	struct THEME* pTheme;
};

struct THEME
{
	CString strResourcePath;
	CArray<THEMEINFO*, THEMEINFO*> m_arrThemes;
};

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertyPageThemes dialog

class CSkinPropertyPageThemes : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkinPropertyPageThemes)

public:
	CSkinPropertyPageThemes();
	virtual ~CSkinPropertyPageThemes();

	//{{AFX_DATA(CSkinPropertyPageThemes)
	enum { IDD = IDD_PROPPAGE_THEMES };
	int		m_nSchema;
	CListBox	m_lboxSkins;
	CComboBox	m_cmbFonts;
	CComboBox	m_cmbColors;
	int		m_nTheme;
	int		m_nLocalSkins;
	BOOL	m_bApplyMetrics;
	BOOL	m_bApplyFrame;
	BOOL	m_bApplyColors;
	//}}AFX_DATA
	
	void FindThemes(CString strPath, BOOL bRecurse);
	void EnumerateThemes(CString strResourcePath);
	void EnumerateThemeColors(CXTPSkinManagerResourceFile* pFile, LPCTSTR lpszResourcePath, LPCTSTR lpszThemeName);
	void ReleaseThemes();

	//{{AFX_VIRTUAL(CSkinPropertyPageThemes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void SetTheme(int nColor, int nFont);

protected:
	//{{AFX_MSG(CSkinPropertyPageThemes)
	afx_msg void OnRadioSchema();
	virtual BOOL OnInitDialog();
	afx_msg void ReloadThemes();
	afx_msg void OnSelChangeListThemes();
	afx_msg void OnSelChangeComboColors();
	afx_msg void OnSelChangeComboFonts();
	afx_msg void OnDestroy();
	afx_msg void OnCheckApplyMetrics();
	afx_msg void OnCheckApplyFrame();
	afx_msg void OnCheckApplyColors();
	afx_msg void OnThemeChanged();
	afx_msg void OnThemeChangedLuna();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __SKINPROPERTYPAGETHEMES_H__
