#include "StdAfx.h"

#if _MSC_VER >= 1200 // MFC 6.0

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#include "MonthCalCtrlEx.h"

#ifndef AfxDeferRegisterClass
#define AfxDeferRegisterClass(fClass) AfxEndDeferRegisterClass(fClass)
BOOL AFXAPI AfxEndDeferRegisterClass(LONG fToRegister);
#define AFX_WNDCOMMCTL_DATE_REG 0x20000
#endif

BEGIN_MESSAGE_MAP(CMonthCalCtrlEx, CMonthCalCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(MCN_SELECT, OnSelChange)
END_MESSAGE_MAP()


BOOL CMonthCalCtrlEx::GoModal(const CPoint& pt, CWnd* pParentWnd, 
							  COleDateTime& rdtDate)
{
	if (::IsWindow(m_hWnd)) 
	{
		ASSERT(FALSE);
		return FALSE;
	}

	VERIFY(AfxDeferRegisterClass(AFX_WNDCOMMCTL_DATE_REG));

	CRect rcRect(pt.x, pt.y, 0, 0);
	BOOL bCreate = CreateEx(WS_EX_TOPMOST|WS_EX_DLGMODALFRAME, 
							MONTHCAL_CLASS, NULL, 
							WS_POPUP, rcRect, pParentWnd, 0);

	ASSERT(bCreate);

	if (!bCreate) 
	{		
		return FALSE;
	}

	CRect rect;
	
	if (GetMinReqRect(rect))
	{
		rect.InflateRect(5, 5);
		DWORD dwFlags = SWP_NOZORDER | SWP_NOREPOSITION | SWP_NOMOVE | SWP_NOACTIVATE;		
		SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), dwFlags);		
	}
	else 
	{
		ASSERT(FALSE);

		DestroyWindow();		
		return FALSE;
	}

	SetCurSel(rdtDate);

	// Enable this window
	EnableWindow(TRUE);

	CWnd* pFocusWnd = SetFocus();
	SetCapture();

	ShowWindow(SW_SHOWNA);

	m_nFlags |= WF_CONTINUEMODAL;
	int nResult = m_nModalResult;
	if (ContinueModal())
	{
		// enter modal loop
		DWORD dwFlags = MLF_SHOWONIDLE;
		if (GetStyle() & DS_NOIDLEMSG)
			dwFlags |= MLF_NOIDLEMSG;
		nResult = RunModalLoop(dwFlags);
	}

	ReleaseCapture();

	SYSTEMTIME sysTime;
	::ZeroMemory(&sysTime, sizeof(sysTime));
	BOOL bSelResult = GetCurSel(&sysTime);
	if (bSelResult) 
	{
		rdtDate = COleDateTime(sysTime.wYear, sysTime.wMonth, sysTime.wDay, 0, 0, 0);
	}

	DestroyWindow();

	if (pFocusWnd && ::IsWindow(pFocusWnd->GetSafeHwnd()))
		pFocusWnd->SetFocus();

	return (nResult == IDOK) && bSelResult;
}

void CMonthCalCtrlEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		EndModalLoop(nChar == VK_RETURN ? IDOK : IDCANCEL);
		return;
	}

	CMonthCalCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMonthCalCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!rcClient.PtInRect(point))
	{
		EndModalLoop(IDOK);
		return;
	}

	CMonthCalCtrl::OnLButtonDown(nFlags, point);
}

void CMonthCalCtrlEx::OnSelChange(NMHDR* /*pNMHdr*/, LRESULT* /*pResult*/)
{
	EndModalLoop(IDOK);
}

#endif
