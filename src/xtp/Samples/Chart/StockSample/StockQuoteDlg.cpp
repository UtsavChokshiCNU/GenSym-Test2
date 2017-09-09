// StockQuoteDlg.cpp : implementation file
//
// --------------------------------------------------------------------------
// COPYRIGHT NOTICE:
// --------------------------------------------------------------------------
// 
// "Codejock Chart" is a MFC extension library for creating modern charting 
// applications. This file and the code herein are part of the Codejock Chart
// MFC extension library.
//
// This code is protected under U.S. Copyright Law and International treaties
// and is intended for registered and licensed use only. Any other use is 
// strictly prohibited. This code is subject to the terms and conditions 
// outlined in the "Codejock Chart" End User License Agreement (EULA).
//
// Copyright (c) 1998-2011 Codejock Technologies LLC, All Rights Reserved.
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stocksample.h"
#include "StockQuoteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockQuoteDlg dialog


CStockQuoteDlg::CStockQuoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockQuoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockQuoteDlg)
	m_strSymbol = _T("MSFT");
	m_str1yTargetEst = _T("");
	m_str52WkRange = _T("");
	m_strAsk = _T("");
	m_strAvgVol = _T("");
	m_strBid = _T("");
	m_strChange = _T("");
	m_strDaysRange = _T("");
	m_strLastTrade = _T("");
	m_strMarketCap = _T("");
	m_strName = _T("");
	m_strOpen = _T("");
	m_strPrevClose = _T("");
	m_strTradeTime = _T("");
	m_strVolume = _T("");
	m_nStyle = 0;
	//}}AFX_DATA_INIT
	
	m_crRed = RGB(204,51,0);
	m_crGreen = RGB(0,153,0);
	m_pDoc = NULL;
}


void CStockQuoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockQuoteDlg)
	DDX_Control(pDX, IDC_STR_VOLUME, m_txtVolume);
	DDX_Control(pDX, IDC_STR_TRADETIME, m_txtTradeTime);
	DDX_Control(pDX, IDC_STR_PREVCLOSE, m_txtPrevClose);
	DDX_Control(pDX, IDC_STR_OPEN, m_txtOpen);
	DDX_Control(pDX, IDC_STR_NAME, m_txtName);
	DDX_Control(pDX, IDC_STR_MARKETCAP, m_txtMarketCap);
	DDX_Control(pDX, IDC_STR_LASTTRADE, m_txtLastTrade);
	DDX_Control(pDX, IDC_STR_DAYSRANGE, m_txtDaysRange);
	DDX_Control(pDX, IDC_STR_CHANGE, m_txtChange);
	DDX_Control(pDX, IDC_STR_BID, m_txtBid);
	DDX_Control(pDX, IDC_STR_AVGVOL, m_txtAvgVol);
	DDX_Control(pDX, IDC_STR_ASK, m_txtAsk);
	DDX_Control(pDX, IDC_STR_52WKRANGE, m_txt52WkRange);
	DDX_Control(pDX, IDC_STR_1YTARGETEST, m_txt1yTargetEst);
	DDX_Text(pDX, IDC_EDIT_SYMBOL, m_strSymbol);
	DDX_Text(pDX, IDC_STR_1YTARGETEST, m_str1yTargetEst);
	DDX_Text(pDX, IDC_STR_52WKRANGE, m_str52WkRange);
	DDX_Text(pDX, IDC_STR_ASK, m_strAsk);
	DDX_Text(pDX, IDC_STR_AVGVOL, m_strAvgVol);
	DDX_Text(pDX, IDC_STR_BID, m_strBid);
	DDX_Text(pDX, IDC_STR_CHANGE, m_strChange);
	DDX_Text(pDX, IDC_STR_DAYSRANGE, m_strDaysRange);
	DDX_Text(pDX, IDC_STR_LASTTRADE, m_strLastTrade);
	DDX_Text(pDX, IDC_STR_MARKETCAP, m_strMarketCap);
	DDX_Text(pDX, IDC_STR_NAME, m_strName);
	DDX_Text(pDX, IDC_STR_OPEN, m_strOpen);
	DDX_Text(pDX, IDC_STR_PREVCLOSE, m_strPrevClose);
	DDX_Text(pDX, IDC_STR_TRADETIME, m_strTradeTime);
	DDX_Text(pDX, IDC_STR_VOLUME, m_strVolume);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStockQuoteDlg, CDialog)
	//{{AFX_MSG_MAP(CStockQuoteDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_GETQUOTE, OnBtnGetQuote)
	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelendOkComboStyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockQuoteDlg message handlers

BOOL CStockQuoteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	NONCLIENTMETRICS ncm;
	::ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS), &ncm, 0));
	
	ncm.lfMenuFont.lfWeight = FW_BOLD;
	m_fontBold.CreateFontIndirect(&ncm.lfMenuFont);
	
	OnBtnGetQuote();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStockQuoteDlg::OnBtnGetQuote() 
{
	UpdateData();
	
	m_txtVolume.SetFont(&m_fontBold);
	m_txtTradeTime.SetFont(&m_fontBold);
	m_txtPrevClose.SetFont(&m_fontBold);
	m_txtOpen.SetFont(&m_fontBold);
	m_txtName.SetFont(&m_fontBold);
	m_txtMarketCap.SetFont(&m_fontBold);
	m_txtLastTrade.SetFont(&m_fontBold);
	m_txtDaysRange.SetFont(&m_fontBold);
	m_txtChange.SetFont(&m_fontBold);
	m_txtBid.SetFont(&m_fontBold);
	m_txtAvgVol.SetFont(&m_fontBold);
	m_txtAsk.SetFont(&m_fontBold);
	m_txt52WkRange.SetFont(&m_fontBold);
	m_txt1yTargetEst.SetFont(&m_fontBold);
	
	CStringArray& arrQuote = m_quote.GetQuote(m_strSymbol);
	
	AfxExtractSubString(m_strName, arrQuote[0], 0, ',');
	AfxExtractSubString(m_strLastTrade, arrQuote[0], 1, ',');
	AfxExtractSubString(m_strTradeTime, arrQuote[0], 2, ',');
	AfxExtractSubString(m_strChange, arrQuote[0], 3, ',');
	AfxExtractSubString(m_strPrevClose, arrQuote[0], 4, ',');
	AfxExtractSubString(m_strOpen, arrQuote[0], 5, ',');
	AfxExtractSubString(m_strBid, arrQuote[0], 6, ',');
	AfxExtractSubString(m_strAsk, arrQuote[0], 7, ',');
	AfxExtractSubString(m_str1yTargetEst, arrQuote[0], 8, ',');
	AfxExtractSubString(m_strDaysRange, arrQuote[0], 9, ',');
	AfxExtractSubString(m_str52WkRange, arrQuote[0], 10, ',');
	AfxExtractSubString(m_strVolume, arrQuote[0], 11, ',');
	AfxExtractSubString(m_strAvgVol, arrQuote[0], 12, ',');
	AfxExtractSubString(m_strMarketCap, arrQuote[0], 13, ',');
	
	m_strVolume = FormatNumber(_ttoi(m_strVolume));
	m_strAvgVol = FormatNumber(_ttoi(m_strAvgVol));
	
	m_strName.MakeUpper();
	m_strSymbol.MakeUpper();
	
	UpdateData(FALSE);

	if (m_pDoc)
	{
		m_pDoc->UpdateAllViews(NULL, (LPARAM)m_hWnd);
	}
}

CString CStockQuoteDlg::FormatNumber(LONGLONG ulNumber)
{
	TCHAR szLeadingZero[30];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_ILZERO, szLeadingZero, 2) == 0)
	{
		TRACE0("Error obtaining leading zero locale information.\n");
		return _T("");
	}
	
	TCHAR szDecimalSep[5];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_SDECIMAL, szDecimalSep, 4) == 0)
	{
		TRACE0("Error obtaining decimal separator locale information.\n");
		return _T("");
	}
	
	TCHAR szThousandSep[5];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_STHOUSAND, szThousandSep, 4) == 0)
	{
		TRACE0("Error obtaining thousand separator locale information.\n");
		return _T("");
	}
	
	TCHAR szNegativeOrder[30];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_INEGNUMBER, szNegativeOrder, 2) == 0)
	{
		TRACE0("Error obtaining negative order locale information.\n");
		return _T("");
	}
	
	NUMBERFMT fmt;
	fmt.NumDigits     = 0;
	fmt.LeadingZero   = _ttoi(szLeadingZero);
	fmt.Grouping      = 3;
	fmt.lpDecimalSep  = szDecimalSep;
	fmt.lpThousandSep = szThousandSep;
	fmt.NegativeOrder = _ttoi(szNegativeOrder);
	
	CString strValue;
	strValue.Format(_T("%I64d"), ulNumber);
	
	TCHAR szBuffer[256];
	if (::GetNumberFormat(LOCALE_USER_DEFAULT, 0, strValue, &fmt, szBuffer, 256) == 0)
	{
		TRACE0("Error obtaining number format for default locale.\n");
		return _T("");
	}
	
	return szBuffer;
}

HBRUSH CStockQuoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STR_CHANGE)
	{
		if (m_strChange.Find(_T("+")) != -1)
		{
			pDC->SetTextColor(m_crGreen);
		}
		else
		{
			pDC->SetTextColor(m_crRed);
		}
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CStockQuoteDlg::Create(UINT nIDTemplate, CWnd* pParentWnd, CDocument* pDoc)
{
	m_pDoc = pDoc;
	return CDialog::Create(nIDTemplate, pParentWnd);
}

void CStockQuoteDlg::OnSelendOkComboStyle() 
{
	UpdateData();
	
    if (m_pDoc)
    {
        m_pDoc->UpdateAllViews(NULL, (LPARAM)m_hWnd);
    }
}
