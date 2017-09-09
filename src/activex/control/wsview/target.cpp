// target.cpp : implementation file
//

#include "stdafx.h"
#include "target.h"
#include "props-ws.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CInterfaceDropTarget

CInterfaceDropTarget::CInterfaceDropTarget()
{
  m_pAssocWnd = NULL;
}

CInterfaceDropTarget::~CInterfaceDropTarget()
{
  Revoke();
}

DROPEFFECT CInterfaceDropTarget::GetDropEffect(DWORD dwKeyState)
{
  DROPEFFECT dropEffect;

  DWORD state = dwKeyState & (MK_CONTROL | MK_ALT | MK_SHIFT);

  switch (state) {

    case (MK_CONTROL|MK_SHIFT):
      dropEffect = DROPEFFECT_LINK;
      break;

    case MK_CONTROL:
      dropEffect = DROPEFFECT_COPY;
      break;

    case MK_SHIFT:
    case 0:
      dropEffect = DROPEFFECT_MOVE;
      break;

    default:
      dropEffect = DROPEFFECT_NONE;
      break;
  }

  return dropEffect;
}

BOOL CInterfaceDropTarget::WrapDataObject(LPDATAOBJECT pDataObject, VARIANT *pvar)
{
  LPUNKNOWN pUnk;
  HRESULT hr = E_FAIL;

  hr = pDataObject->QueryInterface(IID_IUnknown, (LPVOID*)(&pUnk));
  if (FAILED(hr)) {
    return FALSE;
  }  

  VariantInit(pvar);
  V_VT(pvar) = VT_UNKNOWN;
  V_UNKNOWN(pvar) = pUnk;

  return TRUE;
}

void CInterfaceDropTarget::AssociatedCWnd(CWnd *pWnd)
{
  m_pAssocWnd = pWnd;
}

void CInterfaceDropTarget::OnDragLeave(CWnd *)
{
  //((CWorkspaceView*)m_pAssocWnd)->FireDragLeave();
}

DROPEFFECT CInterfaceDropTarget::OnDragEnter(CWnd *, COleDataObject *pDataObject,
					     DWORD dwKeyState, CPoint)
{
  DROPEFFECT dropEffect = GetDropEffect(dwKeyState);
  VARIANT var;
  // CWorkspaceView *pwsv = (CWorkspaceView*)m_pAssocWnd;

  LPDATAOBJECT pDataObj = pDataObject->m_lpDataObject;
  WrapDataObject(pDataObj, &var);

  // fire the drag enter event  
  //pwsv->FireDragEnter(&var, dropEffect, point.x, point.y);

  return dropEffect;
}

DROPEFFECT CInterfaceDropTarget::OnDragOver(CWnd *, COleDataObject *pDataObject,
					    DWORD dwKeyState, CPoint)
{
  DROPEFFECT dropEffect = GetDropEffect(dwKeyState);
  VARIANT var;

  LPDATAOBJECT pDataObj = pDataObject->m_lpDataObject;
  WrapDataObject(pDataObj, &var);

  // let container know we've received a drag over
  //((CWorkspaceView*)m_pAssocWnd)->FireDragOver(&var, dropEffect, point.x, point.y);

  return dropEffect;
}

BOOL CInterfaceDropTarget::OnDrop(CWnd *pDrop, COleDataObject *pDataObject,
				  DROPEFFECT dropEffect, CPoint point)
{
  VARIANT var;

  LPDATAOBJECT pDataObj = pDataObject->m_lpDataObject;
  WrapDataObject(pDataObj, &var);

#if 0
  HGLOBAL hstr;
  TCHAR *str;

  FORMATETC FormatEtc;
  BOOL bAvail = FALSE;
#endif
  CLIPFORMAT cf = CF_TEXT; 

//  HGLOBAL hData = pDataObject->GetGlobalData(CF_TEXT);

//  if (!hData) {
//      TRACE("Fail in getting data\n");
//      return FALSE;
//  }
//  LPCSTR lpcszData=(LPCSTR)GlobalLock(hData);

  //GlobalUnlock(hData);

 FORMATETC fmt;
 fmt.ptd = NULL;
 fmt.dwAspect = DVASPECT_CONTENT;
 fmt.lindex = -1;
 fmt.tymed = TYMED_HGLOBAL;
 fmt.cfFormat = cf;
 // HGLOBAL hGlobal = pDataObject->GetGlobalData(cf, &fmt);


#if 0
  int i = 0;
  pDataObject->BeginEnumFormats();
  while (pDataObject->GetNextFormat(&FormatEtc)) {
    bAvail = pDataObject->IsDataAvailable(cf, &FormatEtc);
    if (bAvail) {
      //TRACE ("\nGot format %s\n tymed = %s (%d)\n", GetFormatName(FormatEtc.cfFormat), GetTymedName(FormatEtc.tymed), FormatEtc.tymed);
      TRACE ("\nGot format \n  (%d)\n", FormatEtc.tymed);

      if (FormatEtc.tymed == TYMED_HGLOBAL) {
        hstr = pDataObject->GetGlobalData(cf);
        if (!hstr) {
          TRACE(" hstr is NULL\n");
        }
        else {
          TRACE(" hstr = %05X\n size = %d\n", hstr, ::GlobalSize(hstr));
        }

        ::GlobalFree(hstr);
      }

      //str = (TCHAR*)GlobalLock(hstr);
      //GlobalUnlock(hstr);

      i++;
    }
  }
#endif

  // let container know we've received a drop
  ((CWorkspaceView*)m_pAssocWnd)->FireDrop(&var, dropEffect, point.x, point.y);

  return COleDropTarget::OnDrop(pDrop, pDataObject, dropEffect, point);
}

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDropTarget message handlers
