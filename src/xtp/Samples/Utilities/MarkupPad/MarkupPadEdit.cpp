// MarkupPadEdit.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "MarkupPadEdit.h"
#include "MarkupPadDoc.h"
#include "MarkupPadView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadEdit

IMPLEMENT_DYNCREATE(CMarkupPadEdit, CEditView)

CMarkupPadEdit::CMarkupPadEdit()
{

	m_hInstance = LoadLibraryA("RICHED20.DLL");

	if (m_hInstance)
	{
	#ifdef _UNICODE
		m_strClass = _T("RichEdit20W");
	#else
		m_strClass = _T("RichEdit20A");
	#endif
	}
	else
	{
		m_hInstance = LoadLibraryA("RICHED32.DLL");
		m_strClass = _T("RICHEDIT");
	}


	NONCLIENTMETRICS ncm = { sizeof(NONCLIENTMETRICS) };
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

	STRCPY_S(ncm.lfMessageFont.lfFaceName, LF_FACESIZE, _T("Courier New"));
	ncm.lfMessageFont.lfHeight = -14;

	m_fnt.CreateFontIndirect(&ncm.lfMessageFont);

	m_bFirstDoc = TRUE;
	m_bError = FALSE;
}

CMarkupPadEdit::~CMarkupPadEdit()
{
}


BEGIN_MESSAGE_MAP(CMarkupPadEdit, CEditView)
	//{{AFX_MSG_MAP(CMarkupPadEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMarkupPadEdit diagnostics

#ifdef _DEBUG
void CMarkupPadEdit::AssertValid() const
{
	CEditView::AssertValid();
}

void CMarkupPadEdit::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadEdit message handlers

void CMarkupPadEdit::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	SetFont(&m_fnt);
	SendMessage(EM_SETTEXTMODE, TM_PLAINTEXT | TM_MULTILEVELUNDO);
	SendMessage(EM_SETEVENTMASK, 0, ENM_CHANGE);

	if (m_bFirstDoc)
	{
		CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();
		if (pMainFrame)
		{
			CXTPStatusBar* pStatusBar = (CXTPStatusBar*)pMainFrame->GetDlgItem(AFX_IDW_STATUS_BAR);
			pStatusBar->GetMarkupContext()->AddHandler(CXTPMarkupHyperlink::m_pClickEvent, CreateMarkupClassDelegate(this, &CMarkupPadEdit::OnStatusBarHyperlinkClick));
		}
	}

	if (GetDocument()->GetPathName().IsEmpty() && m_bFirstDoc)
	{
		SetWindowText(_T("<Page xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml'>\r\n  <TextBlock Cursor=\"Hand\" VerticalAlignment=\"Center\" HorizontalAlignment=\"Center\">Enter Text Here</TextBlock>\r\n</Page>"));
	}
	m_bFirstDoc = FALSE;

	OnChange();	
	GetDocument()->SetModifiedFlag(FALSE);
}

LPWSTR CMarkupPadEdit::GetUnicodeText()
{
	GETTEXTLENGTHEX gtl =
	{
		GTL_DEFAULT, 1200
	};
	
	int nLen = (int)SendMessage(EM_GETTEXTLENGTHEX, (WPARAM)&gtl);
	
	if (nLen > 0)
	{
		GETTEXTEX gt =
		{
			(nLen + 1) * sizeof(WCHAR), GT_DEFAULT, 1200, 0, 0
		};
		
		LPWSTR lpBuffer = new WCHAR[nLen + 1];
		
		SendMessage(EM_GETTEXTEX, (WPARAM)&gt, (LPARAM)lpBuffer);
		
		return lpBuffer;
	}

	return NULL;
}

CString CreateMarkupError(LPCTSTR lpszLastError)
{
	LPCTSTR lpszIndex = _tcsstr(lpszLastError, _T(". Line "));
	if (lpszIndex == NULL)
		return lpszLastError;

	((LPTSTR)lpszIndex)[1] = 0;

	CString str;
	str.Format(_T("<TextBlock VerticalAlignment='Center'>%s <Hyperlink>%s</Hyperlink></TextBlock>"), lpszLastError, lpszIndex + 2);
	
	((LPTSTR)lpszIndex)[1] = ' ';
	
	return str;
}

void CMarkupPadEdit::OnChange() 
{
	USES_CONVERSION;

	CMarkupPadDoc* pDocument = (CMarkupPadDoc*)GetDocument();
	
	POSITION pos = pDocument->GetFirstViewPosition();
	CMarkupPadView* pView = (CMarkupPadView*)pDocument->GetNextView(pos);

	LPWSTR lpszMarkup = GetUnicodeText();
	

	_int64 nPerfomanceEnd;
	_int64 nPerfomanceStart;

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceStart);

	CXTPMarkupParser sc;
	if (lpszMarkup) sc.SetBuffer(lpszMarkup, lpszMarkup + wcslen(lpszMarkup));

	CXTPMarkupBuilder builder(pView);
	CXTPMarkupUIElement* pUIElement = builder.Parse(&sc);

	if (lpszMarkup)
		delete[] lpszMarkup;

	QueryPerformanceCounter((LARGE_INTEGER*)&nPerfomanceEnd);
	TRACE(_T("Parse   = %i \n"), int(nPerfomanceEnd - nPerfomanceStart));
	
	BOOL bError = m_bError;

	if (pUIElement)
	{
		MARKUP_RELEASE(pView->m_pUIElement);
		pView->m_pUIElement = pUIElement;

		bError = FALSE;
		UpdateViews();
		GetParentFrame()->SetMessageText(_T("Done."));
	}
	else
	{		
		bError = TRUE;
		GetParentFrame()->SetMessageText(CreateMarkupError(builder.GetLastError()));
	}

	if (m_bError != bError)
	{
		m_bError = bError;

		CHARFORMAT cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT));
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = m_bError ? RGB(255, 0, 0) : 0;
		
		SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}
	pDocument->SetModifiedFlag(TRUE);
}

void CMarkupPadEdit::UpdateViews() 
{
	CDocument* pDocument = GetDocument();
	POSITION pos = pDocument->GetFirstViewPosition();
	
	while (pos)
	{
		CView* pView = pDocument->GetNextView(pos);
		if (pView != this)
		{
			pView->Invalidate(FALSE);
			break;
		}
	}	
}

void CMarkupPadEdit::OnStatusBarHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		CXTPMarkupRun* pRun = (CXTPMarkupRun*)((CXTPMarkupHyperlink*)pSender)->GetInlines()->GetInline(0);

		CString strText = pRun->GetText();

		int nLine = 0, nPosition = 0;
		if (SCANF_S(strText, _T("Line %i, position %i"), &nLine, &nPosition) == 2)
		{
			int nPos = nPosition + (int)SendMessage(EM_LINEINDEX, nLine - 1); 
			SendMessage(EM_SETSEL, nPos, nPos);
		}

		pArgs->SetHandled();
	}
}

void CMarkupPadEdit::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_CONTEXT);

	if (point == CPoint(-1, -1))
		GetCursorPos(&point);

	((CXTPFrameWnd*)AfxGetMainWnd())->GetCommandBars()->TrackPopupMenuEx(menu.GetSubMenu(0), 0, point.x, point.y, pWnd);
	
}
