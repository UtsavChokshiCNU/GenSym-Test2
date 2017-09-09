// CntrItem.h : interface of the CSmartLayoutCntrItem class
//

#if !defined(AFX_CNTRITEM_H__C2967F08_F5DD_4BFC_9899_A867D356C1CB__INCLUDED_)
#define AFX_CNTRITEM_H__C2967F08_F5DD_4BFC_9899_A867D356C1CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSmartLayoutDoc;
class CSmartLayoutView;

class CSmartLayoutCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CSmartLayoutCntrItem)

// Constructors
public:
	CSmartLayoutCntrItem(REOBJECT* preo = NULL, CSmartLayoutDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CSmartLayoutDoc* GetDocument()
		{ return (CSmartLayoutDoc*)CRichEditCntrItem::GetDocument(); }
	CSmartLayoutView* GetActiveView()
		{ return (CSmartLayoutView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartLayoutCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CSmartLayoutCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__C2967F08_F5DD_4BFC_9899_A867D356C1CB__INCLUDED_)
