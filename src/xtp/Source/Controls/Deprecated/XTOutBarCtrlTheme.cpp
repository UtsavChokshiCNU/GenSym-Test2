// XTOutBarCtrlTheme.cpp: implementation of the CXTOutBarCtrlTheme class.
//
// This file is a part of the XTREME CONTROLS MFC class library.
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

#include "stdafx.h"

#include "Common/XTPColorManager.h"
#include "Common/XTPDrawHelpers.h"
#include "Common/XTPMaskEditT.h"
#include "Common/XTPWinThemeWrapper.h"

#include "../Defines.h"
#include "../Util/XTPControlTheme.h"
#include "../Edit/XTPEdit.h"

#include "XTThemeManager.h"
#include "XTVC50Helpers.h"
#include "XTOutBarCtrl.h"
#include "XTOutBarCtrlTheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_THEME_FACTORY1(CXTOutBarCtrlTheme)

//===========================================================================
// CXTOutBarCtrlTheme class
//===========================================================================

CXTOutBarCtrlTheme::CXTOutBarCtrlTheme()
{
	m_bFlatIcon = FALSE;
	m_bPlainText = FALSE;
}

CXTOutBarCtrlTheme::~CXTOutBarCtrlTheme()
{

}

void CXTOutBarCtrlTheme::RefreshMetrics()
{
	CXTThemeManagerStyle ::RefreshMetrics();

	m_clrBack.SetStandardValue(GetXtremeColor(COLOR_3DSHADOW));
	m_clrText.SetStandardValue(GetXtremeColor(COLOR_WINDOW));
}


void CXTOutBarCtrlTheme::DrawItemIcon(CDC* pDC, CPoint pt, CXTOutBarItem* pBarItem, CImageList* pImageList)
{
	int nIndex = pBarItem->GetIndex();

	if (pBarItem->IsEnabled())
	{
		pImageList->Draw(pDC, nIndex, pt, ILD_NORMAL);
	}
	else
	{
		HICON hIcon = pImageList->ExtractIcon(nIndex);

		if (m_bFlatIcon)
		{
			CBrush brush(GetXtremeColor(COLOR_3DSHADOW));
			pDC->DrawState(pt, CSize(0, 0), hIcon,
				DST_ICON | DSS_MONO, (HBRUSH)brush);
		}
		else
		{
			pDC->DrawState(pt, CSize(0, 0), hIcon,
				DSS_DISABLED | DST_ICON, (HBRUSH)NULL);
		}
		DestroyIcon(hIcon);
	}
}

void CXTOutBarCtrlTheme::DrawItemText(CDC* pDC, CRect rc, CXTOutBarItem* pBarItem, UINT nFormat)
{
	CString strText = pBarItem->GetName();

	if (pBarItem->IsEnabled())
	{
		pDC->DrawText(strText, rc, nFormat);
	}
	else
	{
		if (m_bPlainText)
		{
			pDC->SetTextColor(GetXtremeColor(COLOR_3DSHADOW));
			pDC->DrawText(strText, rc, nFormat);
		}
		else
		{
			rc.OffsetRect(1, 1);
			pDC->SetTextColor(GetXtremeColor(COLOR_WINDOW));
			pDC->DrawText(strText, rc, nFormat);

			rc.OffsetRect(-1, -1);
			pDC->SetTextColor(GetXtremeColor(COLOR_3DSHADOW));
			pDC->DrawText(strText, rc, nFormat);
		}
	}
}

void CXTOutBarCtrlTheme::DrawFolder(CDC* pDC, CRect rect, CXTOutBarFolder* pBarFolder, const XTMouseState eHilight)
{
	CRect rcFolder(rect);

	CXTPFontDC fnt(pDC, pBarFolder->GetControl()->GetFontX());
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(GetXtremeColor(COLOR_BTNTEXT));

	pDC->FillSolidRect(rect, GetXtremeColor(COLOR_3DFACE));

	switch (eHilight)
	{
	case xtMouseNormal:
		pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DHILIGHT), GetXtremeColor(COLOR_3DSHADOW));
		break;

	case xtMouseSelect:
		pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DDKSHADOW), GetXtremeColor(COLOR_3DFACE));
		rect.InflateRect(-1, -1);
		pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHILIGHT));
		break;

	case xtMouseHover:
		pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DFACE), GetXtremeColor(COLOR_3DDKSHADOW));
		rect.InflateRect(-1, -1);
		pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DHILIGHT), GetXtremeColor(COLOR_3DSHADOW));
		break;
	}

	rcFolder.DeflateRect(4, 0);

	pDC->DrawText(pBarFolder->GetName(), rcFolder,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

}

void CXTOutBarCtrlTheme::FillInsideRect(CDC* pDC, CRect rc)
{
	pDC->FillSolidRect(rc, m_clrBack);
}


void CXTOutBarCtrlTheme::DrawIconFrame(CDC* pDC, CRect rcIcon, BOOL bSelected, BOOL bPressed)
{
	if (!bSelected)
	{
		if (bPressed)
			pDC->Draw3dRect(rcIcon, GetXtremeColor(COLOR_WINDOWFRAME), GetXtremeColor(COLOR_3DFACE));
		else
			pDC->Draw3dRect(rcIcon, GetXtremeColor(COLOR_3DFACE), GetXtremeColor(COLOR_WINDOWFRAME));
	}
	else
	{
		pDC->Draw3dRect(rcIcon, GetXtremeColor(COLOR_WINDOWFRAME), GetXtremeColor(COLOR_3DFACE));

	}
}

//////////////////////////////////////////////////////////////////////////
// CXTOutBarCtrlThemeOfficeXP

CXTOutBarCtrlThemeOfficeXP::CXTOutBarCtrlThemeOfficeXP()
{
	m_bFlatIcon = TRUE;
	m_bPlainText = TRUE;
}

void CXTOutBarCtrlThemeOfficeXP::RefreshMetrics()
{
	CXTOutBarCtrlTheme::RefreshMetrics();

	m_clrBack.SetStandardValue(GetXtremeColor(XPCOLOR_TOOLBAR_FACE));
	m_clrText.SetStandardValue(GetXtremeColor(COLOR_BTNTEXT));
}

void CXTOutBarCtrlThemeOfficeXP::DrawIconFrame(CDC* pDC, CRect rcIcon, BOOL bSelected, BOOL bPressed)
{
	if (!bSelected)
	{
		pDC->FillSolidRect(rcIcon, GetXtremeColor(bPressed ? XPCOLOR_HIGHLIGHT_PUSHED : XPCOLOR_HIGHLIGHT));
		pDC->Draw3dRect(rcIcon, GetXtremeColor(COLOR_HIGHLIGHT), GetXtremeColor(COLOR_HIGHLIGHT));
	}
	else
	{
		pDC->Draw3dRect(rcIcon, GetXtremeColor(COLOR_HIGHLIGHT), GetXtremeColor(COLOR_HIGHLIGHT));
	}
}

//////////////////////////////////////////////////////////////////////////
//
CXTOutBarCtrlThemeOffice2003::CXTOutBarCtrlThemeOffice2003()
{
	RefreshMetrics();
}

void CXTOutBarCtrlThemeOffice2003::RefreshMetrics()
{
	CXTOutBarCtrlThemeOfficeXP::RefreshMetrics();

	m_grcPushed.SetStandardValue(GetXtremeColor(XPCOLOR_HIGHLIGHT_PUSHED));
	m_grcHot.SetStandardValue(GetXtremeColor(XPCOLOR_HIGHLIGHT));
	m_grcSelected.SetStandardValue(GetXtremeColor(XPCOLOR_HIGHLIGHT_CHECKED));

	m_bLunaTheme = FALSE;

	if (!XTPColorManager()->IsLunaColorsDisabled())
	{
		XTPCurrentSystemTheme systemTheme = XTPColorManager()->GetCurrentSystemTheme();

		switch (systemTheme)
		{
		case xtpSystemThemeBlue:
		case xtpSystemThemeRoyale:
		case xtpSystemThemeAero:
			m_clrBack.SetStandardValue(RGB(216, 231, 252));
			break;
		case xtpSystemThemeOlive:
			m_clrBack.SetStandardValue(RGB(226, 231, 191));
			break;
		case xtpSystemThemeSilver:
			m_clrBack.SetStandardValue(RGB(223, 223, 234));
			break;
		}

		if (systemTheme != xtpSystemThemeUnknown)
		{
			m_grcSelected.SetStandardValue(RGB(251, 230, 148), RGB(238, 149, 21));
			m_grcPushed.SetStandardValue(RGB(232, 127, 8), RGB(247, 218, 124));
			m_grcHot.SetStandardValue(RGB(255, 255, 220), RGB(247, 192, 91));
			m_bLunaTheme = TRUE;
		}
	}
}

void CXTOutBarCtrlThemeOffice2003::DrawFolder(CDC* pDC, CRect rect, CXTOutBarFolder* pBarFolder, const XTMouseState eHilight)
{
	CRect rcFolder(rect);

	CXTPFontDC fnt(pDC, pBarFolder->GetControl()->GetFontX());
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(GetXtremeColor(COLOR_BTNTEXT));

	switch (eHilight)
	{
	case xtMouseNormal:
		XTPDrawHelpers()->GradientFill(pDC, rect, XTPColorManager()->grcDockBar.clrDark, XTPColorManager()->grcDockBar.clrLight, FALSE);
		break;

	case xtMouseSelect:
		XTPDrawHelpers()->GradientFill(pDC, rect, m_grcPushed, FALSE);
		break;

	case xtMouseHover:
		XTPDrawHelpers()->GradientFill(pDC, rect, m_grcSelected, FALSE);
		break;
	}
	pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DHILIGHT), GetXtremeColor(XPCOLOR_FRAME));

	rcFolder.DeflateRect(4, 0);

	pDC->DrawText(pBarFolder->GetName(), rcFolder,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

}

void CXTOutBarCtrlThemeOffice2003::DrawIconFrame(CDC* pDC, CRect rcIcon, BOOL bSelected, BOOL bPressed)
{
	if (!m_bLunaTheme)
	{
		CXTOutBarCtrlThemeOfficeXP::DrawIconFrame(pDC, rcIcon, bSelected, bPressed);
		return;
	}

	if (!bSelected)
	{
		if (bPressed)
			XTPDrawHelpers()->GradientFill(pDC, rcIcon, m_grcPushed, FALSE);
		else
			XTPDrawHelpers()->GradientFill(pDC, rcIcon, m_grcHot, FALSE);
	}
	else
	{
		XTPDrawHelpers()->GradientFill(pDC, rcIcon, m_grcSelected, FALSE);

	}
	pDC->Draw3dRect(rcIcon, GetXtremeColor(XPCOLOR_FRAME), GetXtremeColor(XPCOLOR_FRAME));
}

//////////////////////////////////////////////////////////////////////////
//
CXTOutBarCtrlThemeNativeWinXP::CXTOutBarCtrlThemeNativeWinXP()
{
	m_themeOutBar = new CXTPWinThemeWrapper();
	m_themeToolbar = new CXTPWinThemeWrapper();
}

BOOL CXTOutBarCtrlThemeNativeWinXP::IsThemeEnabled()
{
	return m_themeToolbar->IsAppThemed() && m_themeOutBar->IsAppThemed();
}

CXTOutBarCtrlThemeNativeWinXP::~CXTOutBarCtrlThemeNativeWinXP()
{
	SAFE_DELETE(m_themeOutBar);
	SAFE_DELETE(m_themeToolbar);
}

void CXTOutBarCtrlThemeNativeWinXP::RefreshMetrics()
{
	CXTOutBarCtrlTheme::RefreshMetrics();

	HWND hWnd = AfxGetMainWnd() ? AfxGetMainWnd()->GetSafeHwnd() : 0;
	m_themeOutBar->OpenThemeData(hWnd, L"REBAR");
	m_themeToolbar->OpenThemeData(hWnd, L"TOOLBAR");

	if (!IsThemeEnabled())
		CXTOutBarCtrlTheme::RefreshMetrics();
}

void CXTOutBarCtrlThemeNativeWinXP::DrawFolder(CDC* pDC, CRect rect, CXTOutBarFolder* pBarFolder, const XTMouseState eHilight)
{
	if (IsThemeEnabled()) {
		m_themeOutBar->DrawThemeBackground(pDC->GetSafeHdc(), 6, 0, &rect, NULL);
		COLORREF clrText;
		m_themeToolbar->GetThemeColor(0, 0, TMT_TEXTCOLOR, &clrText);

		CRect rcFolder(rect);
		switch (eHilight)
		{
		case xtMouseNormal:
			m_themeToolbar->DrawThemeBackground(pDC->GetSafeHdc(), TP_BUTTON, TS_NORMAL, &rect, 0);
			break;

		case xtMouseSelect:
			m_themeToolbar->DrawThemeBackground(pDC->GetSafeHdc(), TP_BUTTON, TS_PRESSED, &rect, 0);
			break;

		case xtMouseHover:
			m_themeToolbar->DrawThemeBackground(pDC->GetSafeHdc(), TP_BUTTON, TS_HOT, &rect, 0);
			break;
		}

		CXTPFontDC fnt(pDC, pBarFolder->GetControl()->GetFontX());
		pDC->SetTextColor(clrText);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(pBarFolder->GetName(), rcFolder, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	} else {
		CXTOutBarCtrlTheme::DrawFolder(pDC, rect, pBarFolder, eHilight);
	}
}

void CXTOutBarCtrlThemeNativeWinXP::FillInsideRect(CDC* pDC, CRect rc) {
	if (IsThemeEnabled())
		m_themeOutBar->DrawThemeBackground(pDC->GetSafeHdc(), 6, 0, &rc, NULL);
	else {
		CXTOutBarCtrlTheme::FillInsideRect(pDC, rc);
	}
}

void CXTOutBarCtrlThemeNativeWinXP::DrawIconFrame(CDC* pDC, CRect rcIcon, BOOL bSelected, BOOL bPressed)
{
	if (IsThemeEnabled()) {
		if (bPressed)
			m_themeToolbar->DrawThemeBackground(pDC->GetSafeHdc(), TP_BUTTON, TS_PRESSED, &rcIcon, 0);
		else if (bSelected)
			m_themeToolbar->DrawThemeBackground(pDC->GetSafeHdc(), TP_BUTTON, TS_HOT, &rcIcon, 0);
		else
			m_themeToolbar->DrawThemeBackground(pDC->GetSafeHdc(), TP_BUTTON, TS_NORMAL, &rcIcon, 0);
	} else {
		CXTOutBarCtrlTheme::DrawIconFrame(pDC, rcIcon, bSelected, bPressed);
	}
}

void CXTOutBarCtrlThemeNativeWinXP::DrawItemText(CDC* pDC, CRect rc, CXTOutBarItem* pBarItem, UINT nFormat)
{
	if (IsThemeEnabled()) {
		COLORREF clrText;
		m_themeToolbar->GetThemeColor(0, 0, TMT_TEXTCOLOR, &clrText);
		pDC->SetTextColor(clrText);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(pBarItem->GetName(), rc, nFormat);
	} else
		CXTOutBarCtrlTheme::DrawItemText(pDC, rc, pBarItem, nFormat);
}