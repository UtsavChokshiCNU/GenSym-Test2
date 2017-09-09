// MarkupPadDoc.h : interface of the CMarkupPadDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKUPPADDOC_H__51982D4F_56C1_41CA_ABD5_877164B63440__INCLUDED_)
#define AFX_MARKUPPADDOC_H__51982D4F_56C1_41CA_ABD5_877164B63440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMarkupPadDoc : public CDocument
{
protected: // create from serialization only
	CMarkupPadDoc();
	DECLARE_DYNCREATE(CMarkupPadDoc)

// Attributes
public:

	CEditView* GetView() const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	static DWORD CALLBACK RichTextCtrlCallbackIn(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);

	void SetTitle(LPCTSTR lpszTitle);


// Implementation
public:
	virtual ~CMarkupPadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMarkupPadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPADDOC_H__51982D4F_56C1_41CA_ABD5_877164B63440__INCLUDED_)
