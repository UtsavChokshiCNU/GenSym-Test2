// DynamicBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DynamicBaseDlg.h"

extern UINT wm_get_tool_tip; 
static BOOL StoreBitmapFile(LPCTSTR lpszFileName, HBITMAP hBm);
static void PrintBitmap(LPCTSTR filename);
extern BOOL g_print_menu_on_custom_dialog;

BEGIN_MESSAGE_MAP(CDynamicBaseDlg, CDialog)
 ON_REGISTERED_MESSAGE(wm_get_tool_tip, OnDurationHelp)
 ON_WM_RBUTTONUP()
 ON_WM_VSCROLL()
 ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CDynamicBaseDlg, CDialog)

CDynamicBaseDlg::CDynamicBaseDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CDynamicBaseDlg::IDD, pParent)
{
}

void CDynamicBaseDlg::PostNcDestroy()
{
  delete this;			// See MSDN TN017
}

BOOL CDynamicBaseDlg::PreTranslateMessage (MSG *pMsg)
{
  if (m_ToolTipControl.m_hWnd)	// send only if window has been created
    m_ToolTipControl.RelayEvent(pMsg);

  return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CDynamicBaseDlg::OnDurationHelp(WPARAM, LPARAM)
{
  return (LRESULT)(&m_ToolTipControl);
}

void CDynamicBaseDlg::PrintMe()
{
	char *tmpDir = getenv("TMP");
	char tmp[128];
	tmpDir = (!tmpDir) ? getenv("TEMP") : tmpDir;
	CString pathName(tmpDir);
	tmpnam(tmp);
	pathName += tmp;
	if (StoreBitmapFile(pathName, GetDialogImage())) {
		PrintBitmap(pathName);
		CFile::Remove(pathName);
	} else {
		AfxMessageBox(_T("Can't create temporary file!"));
	}
}

void CDynamicBaseDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int limit = GetScrollLimit(SB_VERT);
	int Pos = GetScrollPos( SB_VERT );
	int delta;
	switch(nSBCode)
	{
	case SB_LINEDOWN : delta = -1;
		break;
	case SB_LINEUP : delta = 1;
		break;
	case SB_PAGEDOWN : delta = -10;
		break;
	case SB_PAGEUP : delta = 10;
		break;
	case SB_THUMBPOSITION : 
	case SB_THUMBTRACK : delta = Pos - nPos;
		break;
	case SB_BOTTOM : delta = Pos - limit;
		break;
	case SB_TOP : delta = -Pos;
		break;
	case SB_ENDSCROLL: delta = 0;
	}

	SetScrollPos( SB_VERT, Pos - delta );
	ScrollWindow(0, delta);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar); 
}

BOOL CDynamicBaseDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int limit = GetScrollLimit(SB_VERT);

	if(limit == 0)
	{ // there is no scrollbar and WM_MOUSEWHEEL is not handled
		return 0;
	}

	// use multiple 10 for quicker scrolling
	int delta = 10 * zDelta / WHEEL_DELTA;
	int Pos = GetScrollPos( SB_VERT );

	// analize boundaries
	if(Pos - delta < 0)
	{
		delta = Pos;
	} 
	else if(Pos - delta > limit)
	{
		delta = Pos - limit;
	}

	SetScrollPos( SB_VERT, Pos - delta );
	ScrollWindow(0, delta);

	// WM_MOUSEWHEEL was handled
	return 1;
}

void CDynamicBaseDlg::OnRButtonUp(UINT nHitTest, CPoint point)
{
	CDialog::OnRButtonUp(nHitTest, point);

	if (!g_print_menu_on_custom_dialog)
		return;
	CMenu menu;
	if(!menu.LoadMenu(IDR_PRINTDIALOG))
		return;
	CMenu* pmenu = menu.GetSubMenu(0);
	if(!pmenu)
		return;
	ClientToScreen((LPPOINT)&point);
	UINT ret = pmenu->TrackPopupMenu(
		TPM_RETURNCMD | TPM_LEFTALIGN |
		TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
	    point.x, point.y, this);
	
	if(ID_PRINTME == ret)
		PrintMe();
}

HBITMAP CDynamicBaseDlg::GetDialogImage()
{
	HDC hDCMem = CreateCompatibleDC(NULL);
	RECT rect;
	HBITMAP hBmp;

	// to consider nested dialog window case
	CWnd *winToPrint = ((GetStyle() & WS_POPUP) == WS_POPUP) ? this : GetOwner();
        winToPrint->GetWindowRect(&rect);

	HDC hDC = ::GetDC(0);// device context of whole screen - to get window with borders
	hBmp = CreateCompatibleBitmap(hDC, rect.right - rect.left, rect.bottom - rect.top);

	HGDIOBJ hOld = SelectObject(hDCMem, hBmp);

	BitBlt(hDCMem, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
           hDC, rect.left, rect.top, SRCCOPY);

	::SelectObject(hDCMem, hOld);
	::DeleteObject(hDCMem);

	return hBmp;
}

// Store bitmap to temporary file
static BOOL StoreBitmapFile(LPCTSTR lpszFileName, HBITMAP HBM)
{
	BITMAP BM;
	BITMAPFILEHEADER BFH;
	LPBITMAPINFO BIP;
	HDC DC;
	LPBYTE Buf;
	DWORD ColorSize = 0,DataSize;
	WORD BitCount;
	HANDLE FP;
	DWORD dwTemp;

	GetObject(HBM, sizeof(BITMAP), (LPSTR)&BM);

	BitCount = (WORD)BM.bmPlanes * BM.bmBitsPixel;
	switch (BitCount)
	{
		case 1:
		case 4:
		case 8:
		case 32:
			ColorSize = sizeof(RGBQUAD) * (1 << BitCount);
			break;
	}

	DataSize = ((BM.bmWidth*BitCount+31) & ~31)/8*BM.bmHeight;
	BIP=(LPBITMAPINFO)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(BITMAPINFO)+ColorSize);

	BIP->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BIP->bmiHeader.biWidth = BM.bmWidth;
	BIP->bmiHeader.biHeight = BM.bmHeight;
	BIP->bmiHeader.biPlanes = 1;
	BIP->bmiHeader.biBitCount = BitCount;
	BIP->bmiHeader.biCompression = 0;
	BIP->bmiHeader.biSizeImage = DataSize;
	BIP->bmiHeader.biXPelsPerMeter = 0;
	BIP->bmiHeader.biYPelsPerMeter = 0;
	if (BitCount < 24)
		BIP->bmiHeader.biClrUsed = (1<<BitCount);

	BIP->bmiHeader.biClrImportant = 0;
	BFH.bfType = 0x4d42;
	BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD);
	BFH.bfReserved1 = 0;
	BFH.bfReserved2 = 0;
	BFH.bfSize = BFH.bfOffBits + DataSize;

	Buf = (LPBYTE)GlobalAlloc(GMEM_FIXED, DataSize);

	DC = GetDC(0);
	GetDIBits(DC, HBM, 0,(WORD)BM.bmHeight, Buf, BIP, DIB_RGB_COLORS);
	ReleaseDC(0, DC);

	FP = CreateFile(lpszFileName,GENERIC_READ | GENERIC_WRITE, 0, NULL,
		  		    CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE == FP) {
		return false;
	}
	WriteFile(FP,&BFH,sizeof(BITMAPFILEHEADER),&dwTemp,NULL);
	WriteFile(FP,BIP,sizeof(BITMAPINFOHEADER) + BIP->bmiHeader.biClrUsed * sizeof(RGBQUAD),&dwTemp,NULL);
	WriteFile(FP,Buf,DataSize,&dwTemp,NULL);

	CloseHandle(FP);
	GlobalFree((HGLOBAL)Buf);
	HeapFree(GetProcessHeap(),0,(LPVOID)BIP);

	return true;
}


static void PrintBitmap(LPCTSTR filename) 
{
	CPrintDialog printDlg(FALSE);
	if (printDlg.DoModal() == IDCANCEL)   
	    return; 

	CDC dc;
	if (!dc.Attach(printDlg.GetPrinterDC())) {
		AfxMessageBox(_T("No printer found!")); 
		return;
	} 
 
	dc.m_bPrinting = TRUE; 
	DOCINFO di;    
	// Initialise print document details
	::ZeroMemory (&di, sizeof (DOCINFO));
	di.cbSize = sizeof (DOCINFO);
	di.lpszDocName = filename; 
	BOOL bPrintingOK = dc.StartDoc(&di); // Begin a new print job 
	// Get the printing extents
	// and store in the m_rectDraw field of a 
	// CPrintInfo object
	CPrintInfo Info;
	Info.SetMaxPage(1); // just one page 
	int maxw = dc.GetDeviceCaps(HORZRES);
	int maxh = dc.GetDeviceCaps(VERTRES); 
	Info.m_rectDraw.SetRect(0, 0, maxw, maxh); 
	for (UINT page = Info.GetMinPage(); page <= 
		Info.GetMaxPage() && bPrintingOK; page++) 
	{
		dc.StartPage();    // begin new page
		Info.m_nCurPage = page;
		CBitmap bitmap;
		if(!bitmap.Attach(::LoadImage(
				::GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, 
				LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE))) {
			AfxMessageBox(_T("Error loading bitmap!")); 
			return;
		} 
		BITMAP bm;
		bitmap.GetBitmap(&bm);
		int w = bm.bmWidth; 
		int h = bm.bmHeight; 
		// create memory device context
		CDC memDC; 
		memDC.CreateCompatibleDC(&dc);
		CBitmap *pBmp = memDC.SelectObject(&bitmap);
		memDC.SetMapMode(dc.GetMapMode());
		dc.SetStretchBltMode(HALFTONE);

		// Occupying not more, than 1/2 of page size
		int _x, _y;
		float rate = (float)w/(float)h;
		_x = (w > h) ? maxw : (int)(maxh * rate);
		_y = (w > h) ? (int)(maxw / rate) : maxh;
		dc.StretchBlt(0, 0, _x/2, _y/2,	&memDC, 0, 0, w, h, SRCCOPY); 

		// clean up
		memDC.SelectObject(pBmp);
		bPrintingOK = (dc.EndPage() > 0);   // end page
	} 
	if (bPrintingOK)
		dc.EndDoc();   // end a print job
	else 
		dc.AbortDoc(); // abort job. 
}
