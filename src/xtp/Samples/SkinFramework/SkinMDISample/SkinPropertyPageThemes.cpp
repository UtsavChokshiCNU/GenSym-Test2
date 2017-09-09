// SkinPropertyPageThemes.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SkinPropertyPageThemes.h"
#include "SkinPropertySheet.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertyPageThemes property page

CSkinPropertyPageThemes::CSkinPropertyPageThemes() : CPropertyPage(CSkinPropertyPageThemes::IDD)
{
	//{{AFX_DATA_INIT(CSkinPropertyPageThemes)
	m_nSchema = 3;
	m_nLocalSkins = 0;
	m_bApplyMetrics = TRUE;
	m_bApplyColors = TRUE;
	m_bApplyFrame = TRUE;
	m_nTheme = 3;
	//}}AFX_DATA_INIT
}

CSkinPropertyPageThemes::~CSkinPropertyPageThemes()
{
}

void CSkinPropertyPageThemes::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinPropertyPageThemes)
	DDX_Control(pDX, IDC_LIST_THEMES, m_lboxSkins);
	DDX_Control(pDX, IDC_COMBO_FONTS, m_cmbFonts);
	DDX_Control(pDX, IDC_COMBO_COLORS, m_cmbColors);
	DDX_Radio(pDX, IDC_RADIO_OFFICE2000, m_nTheme);
	DDX_Radio(pDX, IDC_RADIO_OFFICE2007, m_nSchema);
	DDX_Radio(pDX, IDC_RADIO_SKINPATH, m_nLocalSkins);
	DDX_Check(pDX, IDC_CHECK_APPLYMETRICS, m_bApplyMetrics);
	DDX_Check(pDX, IDC_CHECK_APPLYFRAME, m_bApplyFrame);
	DDX_Check(pDX, IDC_CHECK_APPLYCOLORS, m_bApplyColors);
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNCREATE(CSkinPropertyPageThemes, CPropertyPage)

BEGIN_MESSAGE_MAP(CSkinPropertyPageThemes, CPropertyPage)
	//{{AFX_MSG_MAP(CSkinPropertyPageThemes)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2007, OnRadioSchema)
	ON_BN_CLICKED(IDC_RADIO_LUNA, OnRadioSchema)
	ON_BN_CLICKED(IDC_RADIO_ROYALE, OnRadioSchema)
	ON_BN_CLICKED(IDC_RADIO_VISTA, OnRadioSchema)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnRadioSchema)
	ON_BN_CLICKED(IDC_RADIO_SKINPATH, ReloadThemes)
	ON_LBN_SELCHANGE(IDC_LIST_THEMES, OnSelChangeListThemes)
	ON_CBN_SELCHANGE(IDC_COMBO_COLORS, OnSelChangeComboColors)
	ON_CBN_SELCHANGE(IDC_COMBO_FONTS, OnSelChangeComboFonts)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_APPLYMETRICS, OnCheckApplyMetrics)
	ON_BN_CLICKED(IDC_CHECK_APPLYFRAME, OnCheckApplyFrame)
	ON_BN_CLICKED(IDC_CHECK_APPLYCOLORS, OnCheckApplyColors)
	ON_BN_CLICKED(IDC_RADIO_SKINPATH2, ReloadThemes)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2000, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_OFFICEXP, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_WINTHEME, OnThemeChanged)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003_BLUE, OnThemeChangedLuna)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003_OLIVE, OnThemeChangedLuna)
	ON_BN_CLICKED(IDC_RADIO_OFFICE2003_METALLIC, OnThemeChangedLuna)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSkinPropertyPageThemes::OnRadioSchema() 
{
	UpdateData();
	((CMainFrame*)AfxGetMainWnd())->OnShemaChanged(m_nSchema);
}

void CSkinPropertyPageThemes::EnumerateThemeColors(CXTPSkinManagerResourceFile* pFile, LPCTSTR lpszResourcePath, LPCTSTR lpszThemeName) 
{
	THEME* pTheme= new THEME;
	pTheme->strResourcePath = lpszResourcePath;

	CString str;
	CString strIniFile;
	CString csColorSchemes;
	CString csSizes;

	while(pFile->ReadString(str))
	{
		str.TrimLeft();
		if (str.IsEmpty())
			continue;
		
		if (str[1] == _T(';'))
			continue;

		if (str.Left(5).CompareNoCase(_T("[file")) == 0)
		{
			strIniFile = str.Mid(6, str.GetLength() - 7) + _T(".ini");
			csColorSchemes.Empty();
			csSizes.Empty();
		}
		else if (str[1] == _T('['))
		{
			strIniFile.Empty();
			csColorSchemes.Empty();
			csSizes.Empty();
		}
		else if (!strIniFile.IsEmpty())
		{
			int nPos = str.Find(_T('='));
			if (nPos > 0 && str.Left(12).CompareNoCase(_T("ColorSchemes")) == 0)
			{
				csColorSchemes = str.Mid(nPos + 1);
				csColorSchemes.TrimLeft();
			}
			if (nPos > 0 && str.Left(5).CompareNoCase(_T("Sizes")) == 0)
			{
				csSizes = str.Mid(nPos + 1);
				csSizes.TrimLeft();
			}

			if (!csSizes.IsEmpty() && !csColorSchemes.IsEmpty())
			{
				THEMEINFO* pThemeInfo = new THEMEINFO();
				pThemeInfo->csIniFileName = strIniFile;
				pThemeInfo->csColorSchemes = csColorSchemes;
				pThemeInfo->csSizes = csSizes;
				pThemeInfo->pTheme = pTheme;
				pTheme->m_arrThemes.Add(pThemeInfo);

				strIniFile.Empty();
			}
		}
	}

	if (pTheme->m_arrThemes.GetSize() == 0)
	{
		delete pTheme;
		return;
	}
	
	int nIndex = m_lboxSkins.AddString(lpszThemeName);
	m_lboxSkins.SetItemDataPtr(nIndex, pTheme);
}

void CSkinPropertyPageThemes::EnumerateThemes(CString strResourcePath) 
{
	CXTPSkinManagerResourceFile f;
	if (!f.Open(strResourcePath, _T("Themes.ini")))
		return;

	TCHAR szSkinName[256];
	if (::LoadString(f.GetModuleHandle(), 5000, szSkinName, 256))
	{
		EnumerateThemeColors(&f, strResourcePath, szSkinName);
		return;
	}
}

void CSkinPropertyPageThemes::FindThemes(CString strPath, BOOL bRecurse)
{
	CFileFind f;
	BOOL bNext = f.FindFile(strPath + _T("*.*"));
	while(bNext)
	{
		bNext = f.FindNextFile();
		if (f.IsDots())
			continue;

		if (f.IsDirectory())
		{
			if (bRecurse)
			{
				FindThemes(f.GetFilePath() + "\\", TRUE);
			}
		}
		else 
		{
			CString strExtension = f.GetFileName().Right(9);

			if ((strExtension.CompareNoCase(_T(".msstyles")) == 0) || (strExtension.CompareNoCase(_T(".cjstyles")) == 0))
			{
				EnumerateThemes(f.GetFilePath());
			}
		}
	}
	
	m_lboxSkins.SetCurSel(-1);
}


BOOL CSkinPropertyPageThemes::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	ReloadThemes();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkinPropertyPageThemes::ReleaseThemes()
{
	for (int i = 0; i < m_lboxSkins.GetCount(); i++)
	{
		THEME* pTheme = (THEME*)m_lboxSkins.GetItemDataPtr(i);

		for (int j = 0; j < pTheme->m_arrThemes.GetSize(); j++)
		{	
			delete pTheme->m_arrThemes[j];
		}		

		delete pTheme;
	}		

	m_lboxSkins.ResetContent();
	m_cmbFonts.ResetContent();
	m_cmbColors.ResetContent();
}

void CSkinPropertyPageThemes::ReloadThemes()
{
	UpdateData();

	ReleaseThemes();

	if (m_nLocalSkins == 0)
	{
		CString csStylesPath = CMainFrame::GetStylesPath();	
		FindThemes(csStylesPath, FALSE);
	}
	else
	{
		CString csStylesPath;
		GetWindowsDirectory(csStylesPath.GetBuffer(MAX_PATH), MAX_PATH);
		csStylesPath.ReleaseBuffer();
		
		FindThemes(csStylesPath + _T("\\Resources\\Themes\\"), TRUE);
	}
}


void CSkinPropertyPageThemes::OnSelChangeListThemes() 
{
	m_cmbColors.ResetContent();
	m_cmbFonts.ResetContent();

	int nCurSel = m_lboxSkins.GetCurSel();
	if (nCurSel == LB_ERR)
		return;

	THEME* pTheme = (THEME*)m_lboxSkins.GetItemDataPtr(nCurSel);

	for (int i = 0; i < pTheme->m_arrThemes.GetSize(); i++)
	{
		THEMEINFO* pThemeInfo = pTheme->m_arrThemes[i];


		if (m_cmbColors.FindStringExact(-1, pThemeInfo->csColorSchemes) == LB_ERR)
		{
			int nIndex = m_cmbColors.AddString(pThemeInfo->csColorSchemes);
			m_cmbColors.SetItemDataPtr(nIndex, pThemeInfo);
		}		

		if (m_cmbFonts.FindStringExact(-1, pThemeInfo->csSizes) == LB_ERR)
		{
			int nIndex = m_cmbFonts.AddString(pThemeInfo->csSizes);
			m_cmbFonts.SetItemDataPtr(nIndex, pThemeInfo);
		}		
	}	
	
	m_cmbColors.SetCurSel(0);
	m_cmbFonts.SetCurSel(0);

	OnSelChangeComboColors();
}

void CSkinPropertyPageThemes::SetTheme(int nColor, int nFont)
{
	UpdateData();

	if (nColor == LB_ERR)
		return;

	THEMEINFO* pThemeInfo = (THEMEINFO*)m_cmbColors.GetItemDataPtr(nColor);

	CString csColorSchemes = pThemeInfo->csColorSchemes;
	CString csSizes;

	if (nFont != LB_ERR && m_bApplyMetrics)
	{
		THEMEINFO* pThemeInfo = (THEMEINFO*)m_cmbFonts.GetItemDataPtr(nFont);
		csSizes = pThemeInfo->csSizes;
	}

	THEME* pTheme = pThemeInfo->pTheme;

	for (int i = 0; i < pTheme->m_arrThemes.GetSize(); i++)
	{
		THEMEINFO* pThemeInfo = pTheme->m_arrThemes[i];
		if (pThemeInfo->csColorSchemes == csColorSchemes && 
			(csSizes.IsEmpty() || pThemeInfo->csSizes == csSizes))
		{
			XTPSkinManager()->LoadSkin(pTheme->strResourcePath, pThemeInfo->csIniFileName);
			break;
		}		
	}
	

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	pWnd->OnSkinChanged();
	pWnd->RedrawFrame(this);	
}

void CSkinPropertyPageThemes::OnSelChangeComboColors() 
{
	SetTheme(m_cmbColors.GetCurSel(), m_cmbFonts.GetCurSel());
}

void CSkinPropertyPageThemes::OnSelChangeComboFonts() 
{
	SetTheme(m_cmbColors.GetCurSel(), m_cmbFonts.GetCurSel());	
}

void CSkinPropertyPageThemes::OnDestroy() 
{
	ReleaseThemes();

	CPropertyPage::OnDestroy();
}

void CSkinPropertyPageThemes::OnCheckApplyMetrics() 
{
	UpdateData();
	
	DWORD dwApplyOptions = XTPSkinManager()->GetApplyOptions();

	if (m_bApplyMetrics)	
		XTPSkinManager()->SetApplyOptions(dwApplyOptions | xtpSkinApplyMetrics);
	else
		XTPSkinManager()->SetApplyOptions(dwApplyOptions & ~xtpSkinApplyMetrics);

	m_cmbFonts.EnableWindow(m_bApplyMetrics);
	
}

void CSkinPropertyPageThemes::OnCheckApplyFrame() 
{
	UpdateData();
	
	DWORD dwApplyOptions = XTPSkinManager()->GetApplyOptions();

	if (m_bApplyFrame)	
		XTPSkinManager()->SetApplyOptions(dwApplyOptions | xtpSkinApplyFrame);
	else
		XTPSkinManager()->SetApplyOptions(dwApplyOptions & ~xtpSkinApplyFrame);
}

void CSkinPropertyPageThemes::OnCheckApplyColors() 
{
	UpdateData();
	
	DWORD dwApplyOptions = XTPSkinManager()->GetApplyOptions();

	if (m_bApplyColors)	
		XTPSkinManager()->SetApplyOptions(dwApplyOptions | xtpSkinApplyColors);
	else
		XTPSkinManager()->SetApplyOptions(dwApplyOptions & ~xtpSkinApplyColors);
	
}

void CSkinPropertyPageThemes::OnThemeChanged() 
{
	XTPColorManager()->SetLunaTheme(xtpSystemThemeAuto);
	UpdateData();
	
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	pWnd->SetTheme(m_nTheme);
}

void CSkinPropertyPageThemes::OnThemeChangedLuna() 
{
	UpdateData();
	
	XTPColorManager()->SetLunaTheme(XTPCurrentSystemTheme(xtpSystemThemeBlue + m_nTheme - 4));
	
	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();	
	pWnd->SetTheme(2);
}
