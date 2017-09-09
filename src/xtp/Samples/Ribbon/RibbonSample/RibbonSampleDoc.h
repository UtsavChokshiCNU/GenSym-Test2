// RibbonSampleDoc.h : interface of the CRibbonSampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIBBONSAMPLEDOC_H__6818BFEF_2548_4666_BB00_C1EF3E3E5F3A__INCLUDED_)
#define AFX_RIBBONSAMPLEDOC_H__6818BFEF_2548_4666_BB00_C1EF3E3E5F3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRibbonSampleDoc : public CRichEditDoc
{
protected: // create from serialization only
	CRibbonSampleDoc();
	DECLARE_DYNCREATE(CRibbonSampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonSampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CRibbonSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRibbonSampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIBBONSAMPLEDOC_H__6818BFEF_2548_4666_BB00_C1EF3E3E5F3A__INCLUDED_)
