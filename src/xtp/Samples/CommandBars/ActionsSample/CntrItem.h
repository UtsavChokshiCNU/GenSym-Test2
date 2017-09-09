// CntrItem.h : interface of the CActionsSampleCntrItem class
//

#if !defined(AFX_CNTRITEM_H__002BBEDF_C575_478F_8A96_DE2E65C60C21__INCLUDED_)
#define AFX_CNTRITEM_H__002BBEDF_C575_478F_8A96_DE2E65C60C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CActionsSampleDoc;
class CActionsSampleView;

class CActionsSampleCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CActionsSampleCntrItem)

// Constructors
public:
	CActionsSampleCntrItem(REOBJECT* preo = NULL, CActionsSampleDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CActionsSampleDoc* GetDocument()
		{ return (CActionsSampleDoc*)CRichEditCntrItem::GetDocument(); }
	CActionsSampleView* GetActiveView()
		{ return (CActionsSampleView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActionsSampleCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CActionsSampleCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__002BBEDF_C575_478F_8A96_DE2E65C60C21__INCLUDED_)
