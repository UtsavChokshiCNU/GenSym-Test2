#if !defined(AFX_INTERFACEDROPTARGET_H__BA45670B_7D91_436A_B41E_93F4170A85CD__INCLUDED_)
#define AFX_INTERFACEDROPTARGET_H__BA45670B_7D91_436A_B41E_93F4170A85CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// target.h : header file
//
#include <afxole.h>

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDropTarget window

class CInterfaceDropTarget : public COleDropTarget
{
// Construction
public:
	CInterfaceDropTarget();

// Attributes
protected:
  CWnd *m_pAssocWnd;

public:
  void AssociatedCWnd(CWnd *pWnd);

private:

  UINT m_DragDropFormat;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceDropTarget)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInterfaceDropTarget();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInterfaceDropTarget)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

protected:
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);

  DROPEFFECT GetDropEffect(DWORD dwKeyState);
  BOOL WrapDataObject(LPDATAOBJECT pDataObject, VARIANT *pvar);


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEDROPTARGET_H__BA45670B_7D91_436A_B41E_93F4170A85CD__INCLUDED_)
