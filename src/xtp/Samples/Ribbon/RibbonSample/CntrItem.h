// CntrItem.h : interface of the CRibbonSampleCntrItem class
//

#if !defined(AFX_CNTRITEM_H__4AB69C50_A727_4E11_ABA5_885476ECD247__INCLUDED_)
#define AFX_CNTRITEM_H__4AB69C50_A727_4E11_ABA5_885476ECD247__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRibbonSampleDoc;
class CRibbonSampleView;

class CRibbonSampleCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CRibbonSampleCntrItem)

// Constructors
public:
	CRibbonSampleCntrItem(REOBJECT* preo = NULL, CRibbonSampleDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CRibbonSampleDoc* GetDocument()
		{ return (CRibbonSampleDoc*)CRichEditCntrItem::GetDocument(); }
	CRibbonSampleView* GetActiveView()
		{ return (CRibbonSampleView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRibbonSampleCntrItem)
	public:
		int m_nImage;
	protected:
	//}}AFX_VIRTUAL

		
	void OnDeactivateUI(BOOL bUndoable);
	void OnActivate();
	void ActiveStateChanged(BOOL bActive);


// Implementation
public:
	~CRibbonSampleCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__4AB69C50_A727_4E11_ABA5_885476ECD247__INCLUDED_)
