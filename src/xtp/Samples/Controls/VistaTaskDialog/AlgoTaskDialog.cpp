#include "stdafx.h"

#include "AlgoTaskDialog.h"

///////////////// TEST CODE ///////////////////

enum
{
	Button_SendFeedback = 101,
	Button_NoThanks
};

#define MAX_DLU 371

static LPCTSTR SAMPLE_TEXT = _T("Aa Bb Cc");

CAlgoTaskDialog::CAlgoTaskDialog(void)
{
	m_strHeaderText = SAMPLE_TEXT;

	m_sizeClient.SetSizeEmpty();
	m_sizeDlu.SetSizeEmpty();

	SetWindowTitle(_T("Task Dialog Sample"));
	SetMainInstruction(SAMPLE_TEXT);
	SetFooter(SAMPLE_TEXT);
	//SetFooterIcon(TD_INFORMATION_ICON);
	//SetMainIcon(TD_WARNING_ICON);

	AddButton(_T("Increase Text Size\nClick here to dynamically increasing text size."), Button_SendFeedback);

	m_config.dwFlags |= TDF_ALLOW_DIALOG_CANCELLATION | TDF_USE_COMMAND_LINKS;
	m_config.dwCommonButtons = TDCBF_OK_BUTTON;
}

CAlgoTaskDialog::~CAlgoTaskDialog(void)
{
}

void CAlgoTaskDialog::UpdateFooterText()
{
	CXTPClientRect rcClient(CWnd::FromHandle(m_hWnd));
	m_sizeClient = rcClient.Size();

	//m_sizeDlu = XTPPix2Dlu(
	//	m_sizeClient.cx, m_sizeClient.cy);

	//XTPTaskData()->SetMargins();

	//CRect rcText = rcClient;
	//rcText.left  += m_wndClient.m_rcMargin.left;
	//rcText.right -= m_wndClient.m_rcMargin.right;

	//CWindowDC dc(NULL);
	//CXTPFontDC fontDC(&dc, &m_wndClient.m_fontLarge);

	//::DrawTextEx(dc, (TCHAR*)(LPCTSTR)m_strHeaderText, m_strHeaderText.GetLength(),
	//	&rcText, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_TOP | DT_WORDBREAK, NULL);

	//CSize sizeTextUnits = XTPPix2Dlu(
	//	rcText.Width(), rcText.Height());

	//m_strFooterText.Format(_T("Client Width: %d (%d), Text Size: %d (%d) x %d (%d)"),
	//	m_sizeClient.cx, m_sizeDlu.cx, rcText.Width(), sizeTextUnits.cx, rcText.Height(), sizeTextUnits.cy);

	CWindowDC dc(NULL);
	CXTPFontDC fontDC(&dc, &m_fontLarge);

	CSize sizeExtent = dc.GetTextExtent(m_strHeaderText);
	CSize sizeExtentUnits = XTPPix2Dlu(sizeExtent.cx, sizeExtent.cy);

	CSize sizeClient = m_sizeClient;
	CSize sizeClientUnits = XTPPix2Dlu(sizeClient.cx, sizeClient.cy);

	m_strFooterText.Format(_T("Extent cx: %d (%d), cy: %d (%d)\r\nClient cx: %d (%d), cy: %d (%d)"),
		sizeExtent.cx, sizeExtentUnits.cx, sizeExtent.cy, sizeExtentUnits.cy,
		sizeClient.cx, sizeClientUnits.cx, sizeClient.cy, sizeClientUnits.cy);

	SetFooter(m_strFooterText);
}

void CAlgoTaskDialog::OnDialogConstructed()
{
	UpdateFooterText();
}

BOOL CAlgoTaskDialog::CopyToClipboard(const CString& strText)
{
	if (::OpenClipboard(m_hWnd))
	{
		::EmptyClipboard();

		HGLOBAL hGlobalBuff = ::GlobalAlloc(GMEM_MOVEABLE, strText.GetLength() + 1);

		CHAR* szBuffer = (CHAR*)::GlobalLock(hGlobalBuff);

		WCSTOMBS_S(szBuffer, strText, strText.GetLength() + 1);
		::GlobalUnlock(hGlobalBuff);

		if (::SetClipboardData(CF_TEXT, hGlobalBuff) == NULL)
			return FALSE;

		::CloseClipboard();
		return TRUE;
	}

	return FALSE;
}

void CAlgoTaskDialog::OnButtonClicked(int nButtonID, BOOL& bCloseDialog)
{
	switch (nButtonID)
	{
	case Button_SendFeedback:
		{
			bCloseDialog = FALSE;

			CWnd* pTaskDlg = CWnd::FromHandle(m_hWnd);

			CXTPWindowRect rcWindow(pTaskDlg);
			USES_CONVERSION;
			
			TCHAR chMin   = 'A';
			TCHAR chMax   = 'Z';
			TCHAR chSpace = ' ';

			TCHAR ch;
			int i;

			int cxMax = 550;

			m_avgCharPix = ::GetDialogBaseUnits();

			CString strBuffer;
			strBuffer.Format(_T("Average character width: %d, height: %d\r\n"), m_avgCharPix.cx, m_avgCharPix.cy);
			strBuffer += m_strFooterText + _T("\r\n");

			CXTPClientRect rcClient(CWnd::FromHandle(m_hWnd));
			int cxWidth = rcClient.Width();

			for (ch = chMin, i = 0; i < 500; i += 100, ++ch)
			{
				if (ch > chMax)
					ch = chMin;

				TCHAR chUpper = ch;
				TCHAR chLower = ch + chSpace;

				CString strTemp;
				strTemp.Format(_T("%c%c%c"), chUpper, chLower, chSpace);

				m_strHeaderText += strTemp;
				SetMainInstruction(m_strHeaderText);

				UpdateFooterText();

				if (m_sizeClient.cx > cxWidth)
				{
					cxWidth = m_sizeClient.cx; 
					strBuffer += m_strFooterText + _T("\r\n---------------------------------------------\r\n");
				}

				if (cxMax <= cxWidth)
					break;

				Sleep(100);
			}

			CopyToClipboard(strBuffer);

			break;
		}
	case IDOK:
		{
			bCloseDialog = TRUE;
			break;
		}
	}
}
