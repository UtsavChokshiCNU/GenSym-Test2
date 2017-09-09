// ExcelTabDoc.h : interface of the CExcelTabDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELTABDOC_H__8A5DE73C_5687_495B_B8B0_8E248BADEBB6__INCLUDED_)
#define AFX_EXCELTABDOC_H__8A5DE73C_5687_495B_B8B0_8E248BADEBB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExcelTabDoc : public CDocument
{
protected: // create from serialization only
	CExcelTabDoc();
	DECLARE_DYNCREATE(CExcelTabDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelTabDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExcelTabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExcelTabDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELTABDOC_H__8A5DE73C_5687_495B_B8B0_8E248BADEBB6__INCLUDED_)
