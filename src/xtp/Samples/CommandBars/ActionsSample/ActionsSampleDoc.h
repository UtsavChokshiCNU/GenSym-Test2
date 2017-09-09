// ActionsSampleDoc.h : interface of the CActionsSampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACTIONSSAMPLEDOC_H__222FB84A_A6B5_4BDE_8AFD_EEDA70654539__INCLUDED_)
#define AFX_ACTIONSSAMPLEDOC_H__222FB84A_A6B5_4BDE_8AFD_EEDA70654539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CActionsSampleDoc : public CRichEditDoc
{
protected: // create from serialization only
	CActionsSampleDoc();
	DECLARE_DYNCREATE(CActionsSampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionsSampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CActionsSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CActionsSampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIONSSAMPLEDOC_H__222FB84A_A6B5_4BDE_8AFD_EEDA70654539__INCLUDED_)
