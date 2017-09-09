// XTPReportRecordItemProgress.cpp : implementation of the CXTPReportRecordItemProgress class.
//
// This file is a part of the XTREME REPORTCONTROL MFC class library.
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

#include "XTPReportRecordItemProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CXTPReportRecordItemProgress

IMPLEMENT_SERIAL(CXTPReportRecordItemProgress, CXTPReportRecordItemText, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

CXTPReportRecordItemProgress::CXTPReportRecordItemProgress(LPCTSTR szText)
	: CXTPReportRecordItemText(szText)
{
	m_clrProgress = RGB(0, 0, 0);
	m_nProgressWidth = 1;
	m_nProgressLower = 0;
	m_nProgressUpper = 100;
	m_nProgressStep = 3;
	m_nProgressPos = 0;
}

CXTPReportRecordItemProgress::CXTPReportRecordItemProgress(LPCTSTR szText, COLORREF clrProgress, int nWidth, int nLower, int nUpper, int nStep, int nPos)
	: CXTPReportRecordItemText(szText)
{
	m_clrProgress = clrProgress;
	m_nProgressWidth = nWidth;
	m_nProgressLower = nLower;
	m_nProgressUpper = nUpper;
	m_nProgressStep = nStep;
	m_nProgressPos = nPos;
}

/*
void CXTPReportRecordItemText::DoPropExchange(CXTPPropExchange* pPX)
{
	CXTPReportRecordItem::DoPropExchange(pPX);

	PX_String(pPX, _T("Text"), m_strText, _T(""));
	PX_String(pPX, _T("Color"), m_clrProgress, _T(""));
	PX_String(pPX, _T("Width"), m_nProgressWidth, _T(""));
	PX_String(pPX, _T("Lower"), m_nProgressLower, _T(""));
	PX_String(pPX, _T("Upper"), m_nProgressUpper, _T(""));
	PX_String(pPX, _T("Step"), m_nProgressStep, _T(""));
	PX_String(pPX, _T("Position"), m_nProgressPos, _T(""));
}
*/
void CXTPReportRecordItemProgress::SetProgressColor(COLORREF clrProgress)
{
	m_clrProgress = clrProgress;
}

COLORREF CXTPReportRecordItemProgress::GetProgressColor()
{
	return m_clrProgress;
}

void CXTPReportRecordItemProgress::SetProgressWidth(int nWidth)
{
	m_nProgressWidth = nWidth;
}

int CXTPReportRecordItemProgress::GetProgressWidth()
{
	return m_nProgressWidth;
}

void CXTPReportRecordItemProgress::SetProgressRange(int nLower, int nUpper)
{
	m_nProgressLower = nLower;
	m_nProgressUpper = nUpper;
}

void CXTPReportRecordItemProgress::GetProgressRange(int& nLower, int& nUpper)
{
	nLower = m_nProgressLower;
	nUpper = m_nProgressUpper;
}

void CXTPReportRecordItemProgress::SetProgressStep(int nStep)
{
	m_nProgressStep = nStep;
}

int CXTPReportRecordItemProgress::GetProgressStep()
{
	return m_nProgressStep;
}

int CXTPReportRecordItemProgress::SetProgressPos(int nPos)
{
	int nPrevPos = m_nProgressPos;
	m_nProgressPos = nPos;
	m_nProgressPos = min(m_nProgressPos, m_nProgressUpper);
	m_nProgressPos = max(m_nProgressPos, m_nProgressLower);
	return nPrevPos;
}

int CXTPReportRecordItemProgress::GetProgressPos()
{
	return m_nProgressPos;
}

int CXTPReportRecordItemProgress::GetProgressPosPercent()
{
	return (m_nProgressPos - m_nProgressLower) * 100 / (m_nProgressUpper - m_nProgressLower);
}

int CXTPReportRecordItemProgress::OffsetProgressPos(int nOffset)
{
	int nPrevPos = m_nProgressPos;
	m_nProgressPos += nOffset;
	m_nProgressPos = min(m_nProgressPos, m_nProgressUpper);
	m_nProgressPos = max(m_nProgressPos, m_nProgressLower);
	return nPrevPos;
}

int CXTPReportRecordItemProgress::StepProgressPos()
{
	int nPrevPos = m_nProgressPos;
	m_nProgressPos += m_nProgressStep;
	m_nProgressPos = min(m_nProgressPos, m_nProgressUpper);
	m_nProgressPos = max(m_nProgressPos, m_nProgressLower);
	return nPrevPos;
}

void CXTPReportRecordItemProgress::OnDrawCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	if(!(pDrawArgs && pMetrics))
		return;
	// draw text
	CXTPReportRecordItemText::OnDrawCaption(pDrawArgs, pMetrics);
	// draw progress
	int nWidth = min(m_nProgressWidth, pDrawArgs->rcItem.Height());
	int nLength = pDrawArgs->rcItem.Width() * m_nProgressPos / (m_nProgressUpper - m_nProgressLower);
	pDrawArgs->pDC->FillSolidRect(pDrawArgs->rcItem.left, pDrawArgs->rcItem.top, nLength, nWidth, m_clrProgress);
}
