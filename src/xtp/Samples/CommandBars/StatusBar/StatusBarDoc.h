// StatusBarDoc.h : interface of the CStatusBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSBARDOC_H__38055D1B_3FD5_4ADF_9DBB_1199B4ECF988__INCLUDED_)
#define AFX_STATUSBARDOC_H__38055D1B_3FD5_4ADF_9DBB_1199B4ECF988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStatusBarDoc : public CDocument
{
protected: // create from serialization only
	CStatusBarDoc();
	DECLARE_DYNCREATE(CStatusBarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusBarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSBARDOC_H__38055D1B_3FD5_4ADF_9DBB_1199B4ECF988__INCLUDED_)
