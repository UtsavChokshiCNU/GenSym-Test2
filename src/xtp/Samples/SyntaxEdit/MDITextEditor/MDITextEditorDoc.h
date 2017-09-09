// MDITextEditorDoc.h : interface of the CMDITextEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDITEXTEDITORDOC_H__51869C8E_3587_4FB1_9C17_8ACB2424D551__INCLUDED_)
#define AFX_MDITEXTEDITORDOC_H__51869C8E_3587_4FB1_9C17_8ACB2424D551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define CDocBase	CDocument
#define CDocBase	CXTPSyntaxEditDoc

class CMDITextEditorDoc : public CDocBase
{
protected: // create from serialization only
	CMDITextEditorDoc();
	DECLARE_DYNCREATE(CMDITextEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDITextEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDITextEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDITextEditorDoc)
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void OnChangedViewList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDITEXTEDITORDOC_H__51869C8E_3587_4FB1_9C17_8ACB2424D551__INCLUDED_)
