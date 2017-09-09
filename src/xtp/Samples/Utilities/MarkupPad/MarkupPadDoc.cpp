// MarkupPadDoc.cpp : implementation of the CMarkupPadDoc class
//

#include "stdafx.h"
#include "MarkupPad.h"

#include "MarkupPadDoc.h"
#include "MarkupPadView.h"
#include "MarkupPadEdit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc

IMPLEMENT_DYNCREATE(CMarkupPadDoc, CDocument)

BEGIN_MESSAGE_MAP(CMarkupPadDoc, CDocument)
	//{{AFX_MSG_MAP(CMarkupPadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc construction/destruction

CMarkupPadDoc::CMarkupPadDoc()
{
}

CMarkupPadDoc::~CMarkupPadDoc()
{
}

void CMarkupPadDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(lpszTitle);

}

BOOL CMarkupPadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CEditView)))
		{
			pView->SetWindowText(NULL);
		}
		else if (pView->IsKindOf(RUNTIME_CLASS(CMarkupPadView)))
		{
			MARKUP_RELEASE(((CMarkupPadView*)pView)->m_pUIElement);
		}
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc serialization

void WriteByte(CArchive& ar, int nByte)
{
	BYTE n = (BYTE)nByte;
	ar.Write(&n, 1);
}

CEditView* CMarkupPadDoc::GetView() const
{
	// find the first view - if there are no views
	// we must return NULL

	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
		return NULL;

	// find the first view that is a CRichEditView

	CView* pView;
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CEditView)))
			return (CEditView*) pView;
	}

	// can't find one--return NULL

	return NULL;
}

void CMarkupPadDoc::Serialize(CArchive& ar)
{
	//CDocument::m_bRTF = FALSE;
	//CDocument::Serialize(ar);

	CEditView* pView = GetView();
	if (pView != NULL)
	{
		if (ar.IsStoring())
		{
			LPWSTR lpBuffer = ((CMarkupPadEdit*)pView)->GetUnicodeText();
			
			if (lpBuffer)
			{
				int nLen = (int)wcslen(lpBuffer);
				for (int i = 0; i < nLen; i++)
				{
					int c = (int)lpBuffer[i];

					if (c == '\r' && lpBuffer[i + 1] != '\n')
					{
						WriteByte(ar, '\r');
						WriteByte(ar, '\n');
					}
					else if (c < (1 << 7))
					{
						WriteByte(ar, c);
					} 
					else if (c < (1 << 11))
					{
						WriteByte(ar, (c >> 6) | 0xc0);
						WriteByte(ar, (c & 0x3f) | 0x80);
					} 
					else if (c < (1 << 16))
					{
						WriteByte(ar, (c >> 12) | 0xe0);
						WriteByte(ar, ((c >> 6) & 0x3f) | 0x80);
						WriteByte(ar, (c & 0x3f) | 0x80);
					} 
					else if (c < (1 << 21))
					{
						WriteByte(ar, (c >> 18) | 0xe0);
						WriteByte(ar, ((c >> 12) & 0x3f) | 0x80);
						WriteByte(ar, ((c >> 6) & 0x3f) | 0x80);
						WriteByte(ar, (c & 0x3f) | 0x80);
					}
				}

				delete[] lpBuffer;
			}
		}
		else
		{
			//CDocument::Serialize(ar);
			CMemFile mf;

			WCHAR c;
			char t;
			while (ar.Read(&t, 1) == 1)
			{				
				if( 0 == ( t & '\x80' ) ) 
				{
					c = t;
				}
				else if('\xF0' == (t & '\xF0')) // 1111 - error, more than 16-bit char
				{
					
				}
				else if( '\xE0' == (t & '\xF0')) // 1110xxxx 10xxxxxx 10xxxxxx
				{
					char t2;
					char t3;
					ar.Read(&t2, 1);
					ar.Read(&t3, 1);
					
					c = (WCHAR)((WCHAR(t & '\x0F') << 12 ) | ( WCHAR(t2 & '\x3F' ) << 6 ) | WCHAR(t3 & '\x3F' ));
				}			
				else if( '\xC0' == (t & '\xE0')) // 110xxxxx 10xxxxxx 
				{
					char t2;
					ar.Read(&t2, 1);

					c = (WCHAR)((WCHAR( t & '\x1F' ) << 6 ) | ( t2 & '\x3F' ));
				}
				else 
				{
				}

				mf.Write(&c, sizeof(WCHAR));
			}
			mf.SeekToBegin();

			EDITSTREAM es = {0, 0, &CMarkupPadDoc::RichTextCtrlCallbackIn};
			es.dwCookie = (DWORD_PTR)&mf;

			pView->SendMessage(EM_STREAMIN, SF_TEXT | SF_UNICODE, (LPARAM)&es);
		}
	}
}

DWORD CALLBACK CMarkupPadDoc::RichTextCtrlCallbackIn(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	CFile* pFile = (CFile*) dwCookie;
	*pcb = pFile->Read(pbBuff, cb);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc diagnostics

#ifdef _DEBUG
void CMarkupPadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMarkupPadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc commands
