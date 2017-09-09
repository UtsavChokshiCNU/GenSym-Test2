// WinExplorerDoc.h : interface of the CWinExplorerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINEXPLORERDOC_H__C1774705_3B3F_44A5_8F67_57EF66BF1406__INCLUDED_)
#define AFX_WINEXPLORERDOC_H__C1774705_3B3F_44A5_8F67_57EF66BF1406__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CWinExplorerDoc : public CDocument
{
protected: // create from serialization only
	CWinExplorerDoc();
	DECLARE_DYNCREATE(CWinExplorerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinExplorerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinExplorerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINEXPLORERDOC_H__C1774705_3B3F_44A5_8F67_57EF66BF1406__INCLUDED_)
