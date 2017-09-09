// CntrItem.h : interface of the CSkinSDISampleCntrItem class
//

#if !defined(AFX_CNTRITEM_H__FDA7B716_F1B5_462F_9390_176FFF9280A5__INCLUDED_)
#define AFX_CNTRITEM_H__FDA7B716_F1B5_462F_9390_176FFF9280A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinSDISampleDoc;
class CSkinSDISampleView;

class CSkinSDISampleCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CSkinSDISampleCntrItem)

// Constructors
public:
	CSkinSDISampleCntrItem(REOBJECT* preo = NULL, CSkinSDISampleDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CSkinSDISampleDoc* GetDocument()
		{ return (CSkinSDISampleDoc*)CRichEditCntrItem::GetDocument(); }
	CSkinSDISampleView* GetActiveView()
		{ return (CSkinSDISampleView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinSDISampleCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CSkinSDISampleCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__FDA7B716_F1B5_462F_9390_176FFF9280A5__INCLUDED_)
