// CustomControls.cpp
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

#include "stdafx.h"

#include "CustomControls.h"

IMPLEMENT_XTP_CONTROL(CControlButtonLine, CXTPControlButton)

CControlButtonLine::CControlButtonLine(double dWidth)
{
	m_dWidth = dWidth;
}

void CControlButtonLine::Copy(CXTPControl* pControl, BOOL bRecursive)
{
	ASSERT(DYNAMIC_DOWNCAST(CControlButtonLine, pControl));
	CXTPControlButton::Copy(pControl, bRecursive);
	m_dWidth = ((CControlButtonLine*)pControl)->m_dWidth;
}

void CControlButtonLine::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPControlButton::DoPropExchange(pPX);

	PX_Double(pPX, _T("Width"), m_dWidth);
}

CSize CControlButtonLine::GetSize(CDC* pDC)
{
	CSize sz = pDC->GetTextExtent(_T(" "));

	return CSize(160, max(sz.cy, 16));
}

void CControlButtonLine::Draw(CDC* pDC)
{
	XTPPaintManager()->DrawControlEntry(pDC, this);
	CRect rc = m_rcControl;
	int nWidth = (int)m_dWidth + 1;

	CString str;
	str.Format(_T("%2.2f"), m_dWidth);
	CRect rcText(rc); rcText.DeflateRect(2, 2);
	pDC->DrawText(str, rcText, DT_SINGLELINE|DT_VCENTER );

	CSize sz = pDC->GetTextExtent(str);

	CRect rcButton = CRect(rc.left + sz.cx + 8, rc.CenterPoint().y - nWidth/2, rc.right - 3, rc.CenterPoint().y - nWidth/2 + nWidth);

	XTPPaintManager()->Rectangle(pDC, rcButton, COLOR_BTNTEXT, COLOR_BTNTEXT);

}

////////////////////////////////////////////////////////////////////////
IMPLEMENT_XTP_CONTROL(CControlButtonStyle, CXTPControlButton)

CControlButtonStyle::CControlButtonStyle(int nStyle)
{
	m_nStyle = nStyle;
}

void CControlButtonStyle::Copy(CXTPControl* pControl, BOOL bRecursive)
{
	ASSERT(DYNAMIC_DOWNCAST(CControlButtonStyle, pControl));
	CXTPControlButton::Copy(pControl, bRecursive);
	m_nStyle = ((CControlButtonStyle*)pControl)->m_nStyle;
}
void CControlButtonStyle::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPControlButton::DoPropExchange(pPX);

	PX_Int(pPX, _T("Style"), m_nStyle);
}

CSize CControlButtonStyle::GetSize(CDC* /*pDC*/)
{
	return CSize(110, 16);
}

void CControlButtonStyle::Draw(CDC* pDC)
{
	XTPPaintManager()->DrawControlEntry(pDC, this);
	CRect rc = m_rcControl;
	int nWidth = (int)3;

	CRect rcButton = CRect(rc.left + 3, rc.CenterPoint().y - nWidth/2, rc.right - 3, rc.CenterPoint().y - nWidth/2 + nWidth);

	int nLine1 = 5; int nPause = 0; int nLine2 = 0;

	switch(m_nStyle)
	{
		case 1: nLine1 = nLine2 = nPause = 3; break;
		case 2: nLine1 = nLine2 = 10; nPause = 5; break;
		case 3: nLine1 = 10; nLine2 = nPause = 5; break;
		case 4: nLine1 = nLine2 = 20; nPause = 5; break;
		case 5: nLine1 = 20; nLine2 = nPause = 5; break;
	}

	int nRight = rcButton.left;
	while (nRight < rcButton.right)
	{
		CRect rcLine1(rcButton);
		rcLine1.left = nRight; rcLine1.right = rcLine1.left + nLine1;
		if (!rcLine1.IntersectRect(rcLine1, rcButton))
			break;
		XTPPaintManager()->Rectangle(pDC, rcLine1, COLOR_BTNTEXT, COLOR_BTNTEXT);

		CRect rcLine2(rcButton);
		rcLine2.left = nPause + rcLine1.right;
		rcLine2.right = rcLine2.left + nLine2;
		if (!rcLine2.IsRectEmpty())
		{
			if (!rcLine2.IntersectRect(rcLine2, rcButton))
				break;
		}

		XTPPaintManager()->Rectangle(pDC, rcLine2, COLOR_BTNTEXT, COLOR_BTNTEXT);

		nRight = rcLine2.right + nPause;

	}
}


////////////////////////////////////////////////////////////////////////
IMPLEMENT_XTP_CONTROL(CControlButtonArrow, CXTPControlButton)

CControlButtonArrow::CControlButtonArrow(int nStyle)
{
	m_nStyle = nStyle;
}

void CControlButtonArrow::Copy(CXTPControl* pControl, BOOL bRecursive)
{
	ASSERT(DYNAMIC_DOWNCAST(CControlButtonArrow, pControl));
	CXTPControlButton::Copy(pControl, bRecursive);
	m_nStyle = ((CControlButtonArrow*)pControl)->m_nStyle;
}

void CControlButtonArrow::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPControlButton::DoPropExchange(pPX);

	PX_Int(pPX, _T("Style"), m_nStyle);
}

CSize CControlButtonArrow::GetSize(CDC* pDC)
{
	if (m_nStyle == 0)
	{
		CSize sz = CXTPControlButton::GetSize(pDC);
		sz.cx = 120;
		return sz;
	}
	return CSize(120, 18);
}

void CControlButtonArrow::Draw(CDC* pDC)
{
	XTPPaintManager()->DrawControlEntry(pDC, this);

	if (m_nStyle == 0 )
	{
		pDC->DrawText(GetCaption(), m_rcControl, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		return;
	}

	CRect rc = m_rcControl;
	CRect rcButton = CRect(rc.left + 3, rc.CenterPoint().y, rc.right - 3, rc.CenterPoint().y);

	XTPPaintManager()->Line(pDC, rcButton.left, rcButton.top, rcButton.right, rcButton.top, COLOR_BTNTEXT);

	if (m_nStyle == 2 || m_nStyle == 4)
	{
		XTPPaintManager()->Line(pDC, rcButton.left, rcButton.top, rcButton.left + 8, rcButton.top - 4, COLOR_BTNTEXT);
		XTPPaintManager()->Line(pDC, rcButton.left, rcButton.top, rcButton.left + 8, rcButton.top + 4, COLOR_BTNTEXT);
	}
	if (m_nStyle == 3 || m_nStyle == 4)
	{
		XTPPaintManager()->Line(pDC, rcButton.right - 8, rcButton.top - 4, rcButton.right, rcButton.top, COLOR_BTNTEXT);
		XTPPaintManager()->Line(pDC, rcButton.right - 8, rcButton.top + 4, rcButton.right, rcButton.top, COLOR_BTNTEXT);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

BEGIN_MESSAGE_MAP(CControlComboBoxEditEx, CXTPMaskEditT<CXTPControlComboBoxEditCtrl>)
	ON_MASKEDIT_REFLECT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CControlComboBoxEditEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetEditMask(_T("00:00:00:00"), _T("__:__:__:__"), _T("00:00:00:00"));

	return CXTPMaskEditT<CXTPControlComboBoxEditCtrl>::OnCreate(lpCreateStruct);
}

IMPLEMENT_XTP_CONTROL(CControlComboBoxEx, CXTPControlComboBox)


//////////////////////////////////////////////////////////////////////////
// CControlComboBoxPopup

IMPLEMENT_XTP_CONTROL(CControlComboBoxPopup, CXTPControlComboBox)


CString CControlComboBoxPopup::GetListBoxText() const
{
	UINT nID = ((CMainFrame*)AfxGetMainWnd())->m_nIDSaveAs;

	CString str;
	str.LoadString(nID);

	return str;
}


//////////////////////////////////////////////////////////////////////////
// CControlComboBoxCustomDraw

IMPLEMENT_XTP_CONTROL(CControlComboBoxCustomDraw, CXTPControlFontComboBox)

void CControlComboBoxCustomDraw::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CString strText;
	GetLBText(lpDrawItemStruct->itemID, strText);

	CRect rc(&lpDrawItemStruct->rcItem);

	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	BOOL bSelected = lpDrawItemStruct->itemState & ODS_SELECTED;
	CXTPPaintManager* pPaintManager = GetPaintManager();

	COLORREF crOldTextColor = pDC->SetTextColor(pPaintManager->GetRectangleTextColor(bSelected, FALSE, TRUE, FALSE, FALSE, xtpBarTypePopup, xtpBarPopup));

	if (bSelected)
		pPaintManager->DrawRectangle(pDC, rc, TRUE, FALSE, TRUE, FALSE, FALSE, xtpBarTypePopup, xtpBarPopup);
	else
		pDC->FillSolidRect(rc, pPaintManager->GetXtremeColor(COLOR_WINDOW));


	CFont fnt;
	fnt.CreatePointFont(100, strText);

	CXTPFontDC font(pDC, &fnt);

	pDC->SetBkMode(TRANSPARENT);
	rc.left += 3;
	pDC->DrawText(strText, rc, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);

	pDC->SetTextColor(crOldTextColor);
}

#ifdef _XTP_INCLUDE_CALENDAR

//////////////////////////////////////////////////////////////////////////
// CControlComboBoxDatePicker

class CControlComboBoxDatePickerPopupBar : public CXTPControlComboBoxPopupBar
{
	DECLARE_XTP_COMMANDBAR(CControlComboBoxDatePickerPopupBar)

public:
	CControlComboBoxDatePickerPopupBar();
	~CControlComboBoxDatePickerPopupBar();

	BOOL OnHookKeyDown(UINT nChar, LPARAM lParam);

public:
	BOOL Popup(CXTPControlPopup* pControlPopup, BOOL /*bSelectFirst*/);
	BOOL DestroyWindow();

public:
	class CDatePickerControl : public CXTPDatePickerControl
	{
	public:
		CDatePickerControl()
		{
			m_pControl = 0;
			SetMaxSelCount(1);
		}
		
		void SetModal()
		{
			m_bIsModal = TRUE;
		}
		
		virtual BOOL ContinueModal()
		{
			return TRUE;
		}

		virtual void EndModalLoop(int nResult)
		{
			if (!m_pControl)
				return;

			if (nResult == IDOK)
			{
				COleDateTime dt;
				GetCurSel(dt);
				m_pControl->SetDate(dt);
				m_pControl->OnExecute();				
			}
			else
			{
				m_pControl->GetParent()->GetCommandBars()->ClosePopups();
			}

			m_pControl = NULL;
			ReleaseCapture();
		}
		CControlComboBoxDatePicker* m_pControl;
	};

	CDatePickerControl m_wndDatePickerControl;
};

IMPLEMENT_XTP_COMMANDBAR(CControlComboBoxDatePickerPopupBar, CXTPControlComboBoxPopupBar)

CControlComboBoxDatePickerPopupBar::CControlComboBoxDatePickerPopupBar()
{
	SetShowGripper(FALSE);

	m_wndDatePickerControl.SetBorderStyle(xtpDatePickerBorderNone);
}

CControlComboBoxDatePickerPopupBar::~CControlComboBoxDatePickerPopupBar()
{
}

BOOL CControlComboBoxDatePickerPopupBar::Popup(CXTPControlPopup* pControlPopup, BOOL bSelectFirst)
{
	if (!Create())
		return FALSE;

	ASSERT(pControlPopup->IsKindOf(RUNTIME_CLASS(CControlComboBoxDatePicker)));

	GetControls()->RemoveAll();

	CXTPControlCustom* pControl = new CXTPControlCustom();	

	CRect rcMin;
	m_wndDatePickerControl.GetMinReqRect(rcMin);
	rcMin.bottom += 5;

	m_wndDatePickerControl.DestroyWindow();
	m_wndDatePickerControl.Create(WS_CHILD|WS_VISIBLE, rcMin, this, 0);
	m_wndDatePickerControl.SetModal();
	m_wndDatePickerControl.SetFocus();
	m_wndDatePickerControl.SetCapture();
	m_wndDatePickerControl.m_pControl = (CControlComboBoxDatePicker*)pControlPopup;

	m_wndDatePickerControl.SetCurSel(((CControlComboBoxDatePicker*)pControlPopup)->GetDate());
	m_wndDatePickerControl.EnsureVisibleSelection();
	
	pControl->SetControl(&m_wndDatePickerControl);
	pControl->SetSize(rcMin.Size());
	pControl->SetID(pControlPopup->GetID());

	GetControls()->Add(pControl);


	return CXTPControlComboBoxPopupBar::Popup(pControlPopup, bSelectFirst);
}

BOOL CControlComboBoxDatePickerPopupBar::OnHookKeyDown(UINT nChar, LPARAM lParam)
{

	CXTPControlCustom* pControl = (CXTPControlCustom*)GetControl(0);

	pControl->GetControl()->SendMessage(WM_KEYDOWN, nChar, lParam);

	return TRUE;
}


BOOL CControlComboBoxDatePickerPopupBar::DestroyWindow()
{
	m_wndDatePickerControl.m_pControl = NULL;
	
	if (::GetCapture() == m_wndDatePickerControl.GetSafeHwnd())
		ReleaseCapture();

	return CXTPControlComboBoxPopupBar::DestroyWindow();
}

#endif

IMPLEMENT_XTP_CONTROL(CControlComboBoxDatePicker, CXTPControlComboBox)

CControlComboBoxDatePicker::CControlComboBoxDatePicker()
{
#ifdef _XTP_INCLUDE_CALENDAR
	CXTPCommandBar* pCommandBar = new CControlComboBoxDatePickerPopupBar();
	
	SetCommandBar(pCommandBar);

	SetDropDownListStyle();

	pCommandBar->InternalRelease();
#endif
	SetDate(COleDateTime::GetCurrentTime());
}

CControlComboBoxDatePicker::~CControlComboBoxDatePicker()
{

}

void CControlComboBoxDatePicker::SetDate(const COleDateTime& dt)
{
	if (m_dt != dt)
	{
		m_dt = dt;
		SetEditText(m_dt.Format(VAR_DATEVALUEONLY, LANG_USER_DEFAULT));
	}
}

const COleDateTime& CControlComboBoxDatePicker::GetDate() const 
{
	return m_dt;
}

void CControlComboBoxDatePicker::OnKillFocus()
{
	SetFocused(FALSE);
}

BOOL CControlComboBoxDatePicker::OnHookKeyDown(UINT nChar, LPARAM lParam)
{
	if (nChar == VK_RETURN)
	{
		COleDateTime dt;
		if (dt.ParseDateTime(GetEditText()))
		{
			SetDate(dt);
		}
		
		::SetFocus(m_pParent->GetTrackFocus());
		OnExecute();
		return TRUE;
	}

	if (nChar == VK_ESCAPE)
		return FALSE;

	return CXTPControlComboBox::OnHookKeyDown(nChar, lParam);
}
