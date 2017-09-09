// FlowGraphSampleDoc.h : interface of the CFlowGraphSampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOWGRAPHSAMPLEDOC_H__7C694EDD_60B9_46FA_9611_F29C85A2BDF6__INCLUDED_)
#define AFX_FLOWGRAPHSAMPLEDOC_H__7C694EDD_60B9_46FA_9611_F29C85A2BDF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFlowGraphSampleDoc : public CDocument
{
protected: // create from serialization only
	CFlowGraphSampleDoc();
	DECLARE_DYNCREATE(CFlowGraphSampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlowGraphSampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	BOOL OnOpenDocument(LPCTSTR lpszPathName);
	BOOL OnSaveDocument(LPCTSTR lpszPathName);

// Implementation
public:
	virtual ~CFlowGraphSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFlowGraphSampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOWGRAPHSAMPLEDOC_H__7C694EDD_60B9_46FA_9611_F29C85A2BDF6__INCLUDED_)
