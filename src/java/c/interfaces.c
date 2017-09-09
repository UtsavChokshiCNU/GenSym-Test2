/*****************************************************************************
* interfaces.c
*
* Authors: John Valente, Allan Scott
*  
*****************************************************************************/

#include <stdio.h>
#include "fileio.h"
#define LEAVE_BOOL_ALONE
#include "shared.h"
#include "xcontain.h"
#include "dprintf.h"

#ifdef WIN32


static int                s_nDbgIndent = 0;        /*  indent level for debug message */
static int                s_nDbgLevel = 0;   /*  default dbg level printed */
static UINT               gcfEmbeddedObject;
static UINT               gcfObjectDescriptor;
static DWORD              g_dwObjectCount = 0;  
static FORMATETC          gSingleObjGetFmts[MAXFORMATS];
static int                giSingleObjGetFmts;

static IUnknownVtbl			        MyUnknownVtbl;
static IOleClientSiteVtbl	      MyClientSiteVtbl;
static IAdviseSinkVtbl		      MyAdviseSinkVtbl;
static IDataObjectVtbl		      MyDataObjectVtbl;
static IOleInPlaceSiteExVtbl	    MyInPlaceSiteVtbl;
static IOleInPlaceUIWindowVtbl	MyInPlaceUIWindowVtbl;
static IOleInPlaceFrameVtbl		  MyInPlaceFrameVtbl;
static IPropertyNotifySinkVtbl  MyPropertyNotifySinkVtbl;
static ISimpleFrameSiteVtbl		  MySimpleFrameSiteVtbl;
static IDispatchVtbl		        MyDispatchAmbientVtbl;
static IDispatchVtbl		        MyDispatchEventVtbl;


/*****************************************************************************
/* OleStdQueryInterface
 * 
 *
 *   Description: 
 *     Returns the desired interface pointer if exposed by the given object.
 *     Returns NULL if the interface is not available.
 *     eg.:
 *        lpDataObj = OleStdQueryInterface(lpOleObj, &IID_DataObject);
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Internal
 *     -----
 *   Modifications:
 *****************************************************************************/
LPUNKNOWN ole_query_interface(LPUNKNOWN lpUnk, REFIID riid)
{
  LPUNKNOWN lpInterface;
  HRESULT hrErr;

  hrErr = lpUnk->lpVtbl->QueryInterface(lpUnk,
					riid,
					(LPVOID FAR*)&lpInterface);

  if (SUCCEEDED(hrErr))
    return lpInterface;
  else
    return NULL;
}


/* OleStdMalloc
 * ------------
 *    allocate memory using the currently active IMalloc* allocator
 */
STDAPI_(LPVOID) OleStdMalloc(ULONG ulSize)
{
  LPVOID pout;
  LPMALLOC pmalloc;

  if (CoGetMalloc(MEMCTX_TASK, &pmalloc) != NOERROR) {
    /*  OleDbgAssertSz(0, szAssertMemAlloc); */
    return NULL;
  }

  pout = (LPVOID)pmalloc->lpVtbl->Alloc(pmalloc, ulSize);

  if (pmalloc != NULL) {
    ULONG refs = pmalloc->lpVtbl->Release(pmalloc);
  }

  return pout;
}



/* OleStdFreeString
** ----------------
**    Free a string that was allocated with the currently active
**    IMalloc* allocator.
**
**    if the caller has the current IMalloc* handy, then it can be
**    passed as a argument, otherwise this function will retrieve the
**    active allocator and use it.
*/
STDAPI_(void) OleStdFreeString(LPOLESTR lpsz, LPMALLOC lpMalloc)
{
  BOOL fMustRelease = FALSE;

  if (! lpMalloc) {
    if (CoGetMalloc(MEMCTX_TASK, &lpMalloc) != NOERROR)
      return;
    fMustRelease = TRUE;
  }

  lpMalloc->lpVtbl->Free(lpMalloc, lpsz);

  if (fMustRelease)
    lpMalloc->lpVtbl->Release(lpMalloc);
}





/* Call Release on the object that is NOT necessarily expected to go away.
*/
STDAPI_(ULONG) OleStdRelease(LPUNKNOWN lpUnk)
{
  ULONG cRef;

  cRef = lpUnk->lpVtbl->Release(lpUnk);

#if defined( _DEBUG )
  {
    char szBuf[80];
    sprintf(
	     /*(LPSTR)*/szBuf,
	     "refcnt = %ld after object (0x%lx) release\n",
	     cRef,
	     lpUnk
			);
    /*  OleDbgOut4((LPSTR) szBuf); */
  }
#endif
  return cRef;
}


/*
 * OleStdGetOBJECTDESCRIPTORData
 *
 * Purpose:
 *  Fills and returns a OBJECTDESCRIPTOR structure.
 *  See OBJECTDESCRIPTOR for more information.
 *
 * Parameters:
 *  clsid           CLSID   CLSID of object being transferred
 *  dwDrawAspect    DWORD   Display Aspect of object
 *  sizel           SIZEL   Size of object in HIMETRIC
 *  pointl          POINTL  Offset from upper-left corner of object where mouse went
 *                          down for drag. Meaningful only when drag-drop is used.
 *  dwStatus        DWORD   OLEMISC flags
 *  lpszFullUserTypeName  LPSTR Full User Type Name
 *  lpszSrcOfCopy   LPSTR   Source of Copy
 *
 * Return Value:
 *  HBGLOBAL         Handle to OBJECTDESCRIPTOR structure.
 */
STDAPI_(HGLOBAL) OleStdGetOBJECTDESCRIPTORData(
					       CLSID     clsid,
					       DWORD     dwDrawAspect,
					       SIZEL     sizel,
					       POINTL    pointl,
					       DWORD     dwStatus,
					       LPOLESTR  lpszFullUserTypeName,
					       LPOLESTR  lpszSrcOfCopy
					       )
{
  HGLOBAL            hMem = NULL;
  IBindCtx   FAR    *pbc = NULL;
  LPOBJECTDESCRIPTOR lpOD;
  DWORD     dwObjectDescSize, dwFullUserTypeNameLen, dwSrcOfCopyLen;
  DWORD dwODSize ;

  /*  Get the length of Full User Type Name; Add 1 for the null terminator */
  dwFullUserTypeNameLen = lpszFullUserTypeName ?
    OLESTRLEN(lpszFullUserTypeName)+1 : 0;

  /*  Get the Source of Copy string and its length; Add 1 for the null terminator */
  if (lpszSrcOfCopy)
    dwSrcOfCopyLen = OLESTRLEN(lpszSrcOfCopy)+1;
  else {
    /*  No src moniker so use user type name as source string. */
    lpszSrcOfCopy =  lpszFullUserTypeName;
    dwSrcOfCopyLen = dwFullUserTypeNameLen;
  }

  /*  Allocate space for OBJECTDESCRIPTOR and the additional string data */
  dwObjectDescSize = sizeof(OBJECTDESCRIPTOR);
  dwODSize = dwObjectDescSize + (sizeof(OLECHAR) *
				 (dwFullUserTypeNameLen + dwSrcOfCopyLen)) ;
  hMem = GlobalAlloc((GMEM_MOVEABLE | GMEM_SHARE), dwODSize) ;
  if (NULL == hMem)
    goto error;

  lpOD = (LPOBJECTDESCRIPTOR)GlobalLock(hMem);

  /*  Set the FullUserTypeName offset and copy the string */
  if (lpszFullUserTypeName)
    {
      lpOD->dwFullUserTypeName = dwObjectDescSize;
      OLESTRCPY((LPOLESTR)((LPSTR)lpOD + lpOD->dwFullUserTypeName) ,
		lpszFullUserTypeName);
    }
  else lpOD->dwFullUserTypeName = 0;  /*  zero offset indicates that string is not present */

  /*  Set the SrcOfCopy offset and copy the string */
  if (lpszSrcOfCopy)
    {
      lpOD->dwSrcOfCopy = dwObjectDescSize +
	(sizeof(OLECHAR) * dwFullUserTypeNameLen) ;
      OLESTRCPY((LPOLESTR)((LPSTR)lpOD + lpOD->dwSrcOfCopy), lpszSrcOfCopy);
    }
  else lpOD->dwSrcOfCopy = 0;  /*  zero offset indicates that string is not present */

  /*  Initialize the rest of the OBJECTDESCRIPTOR */
  lpOD->cbSize       = dwODSize ;
  lpOD->clsid        = clsid;
  lpOD->dwDrawAspect = dwDrawAspect;
  lpOD->sizel        = sizel;
  lpOD->pointl       = pointl;
  lpOD->dwStatus     = dwStatus;

  GlobalUnlock(hMem);
  return hMem;

error:
  if (hMem)
    {
      GlobalUnlock(hMem);
      GlobalFree(hMem);
    }
  return NULL;
}


/*
 * OleStdGetObjectDescriptorDataFromOleObject
 *
 * Purpose:
 *  Fills and returns a OBJECTDESCRIPTOR structure. Information for the structure is
 *  obtained from an OLEobject.
 *  See OBJECTDESCRIPTOR for more information.
 *
 * Parameters:
 *  lpOleObj        LPOLEOBJECT OleObject from which OBJECTDESCRIPTOR info
 *                  is obtained.
 *  lpszSrcOfCopy   LPSTR string to identify source of copy.
 *                  May be NULL in which case IOleObject::GetMoniker is called
 *                  to get the moniker of the object. if the object is loaded
 *                  as part of a data transfer document, then usually
 *                  lpOleClientSite==NULL is passed to OleLoad when loading
 *                  the object. in this case the IOleObject:GetMoniker call
 *                  will always fail (it tries to call back to the object's
 *                  client site). in this situation a non-NULL lpszSrcOfCopy
 *                  parameter should be passed.
 *  dwDrawAspect    DWORD   Display Aspect of object
 *  pointl          POINTL  Offset from upper-left corner of object where
 *                  mouse went down for drag. Meaningful only when drag-drop
 *                  is used.
 *  lpSizelHim      SIZEL   (optional) If the object is being scaled in its
 *                  container, then the container should pass the extents
 *                  that it is using to display the object.
 *                  May be NULL if the object is NOT being scaled. in this
 *                  case, IViewobject2::GetExtent will be called to get the
 *                  extents from the object.
 *
 * Return Value:
 *  HBGLOBAL         Handle to OBJECTDESCRIPTOR structure.
 */

STDAPI_(HGLOBAL) OleStdGetObjectDescriptorDataFromOleObject(LPOLEOBJECT lpOleObj,
							    LPOLESTR lpszSrcOfCopy,
							    DWORD dwDrawAspect,
							    POINTL pointl,
							    LPSIZEL lpSizelHim
							    )
{
  CLSID clsid;
  LPOLESTR lpszFullUserTypeName = NULL;
  char     lpszAnsiFullUserTypeName[256];
  LPMONIKER lpSrcMonikerOfCopy = NULL;
  HGLOBAL hObjDesc;
  IBindCtx  FAR  *pbc = NULL;
  HRESULT hrErr;
  SIZEL sizelHim;
  BOOL  fFreeSrcOfCopy = FALSE;
  LPOLELINK lpOleLink = (LPOLELINK)
    ole_query_interface((LPUNKNOWN)lpOleObj,&IID_IOleLink);
  LPVIEWOBJECT2 lpViewObj2 = (LPVIEWOBJECT2)
    ole_query_interface((LPUNKNOWN)lpOleObj, &IID_IViewObject2);
  BOOL  fIsLink = (lpOleLink ? TRUE : FALSE);
  OLECHAR  szLinkedTypeFmt[80];
  char     szAnsiLinkedTypeFmt[80];
  LPOLESTR lpszBuf = NULL;
  char     lpszAnsiBuf[256];
  DWORD dwStatus = 0;


  /*  Get CLSID */
  OLEDBG_BEGIN2("IOleObject::GetUserClassID called\r\n")
    hrErr = lpOleObj->lpVtbl->GetUserClassID(lpOleObj, &clsid);
  OLEDBG_END2
    if (hrErr != NOERROR)
      clsid = CLSID_NULL;

  /*  Get FullUserTypeName */
  OLEDBG_BEGIN2("IOleObject::GetUserType called\r\n")
    hrErr = lpOleObj->lpVtbl->GetUserType(lpOleObj,
					  USERCLASSTYPE_FULL,
					  /*(LPOLESTR FAR*)*/&lpszFullUserTypeName
					  );
  OLEDBG_END2

    /* if object is a link, then expand usertypename to be "Linked %s" */
    if (fIsLink && lpszFullUserTypeName) {
      AlertBox("Calling LoadString");
      if (0 == LoadString(NULL, (UINT)IDS_OLE2UIPASTELINKEDTYPE,
			  /*(LPSTR)*/szAnsiLinkedTypeFmt, 80))
	lstrcpy(szAnsiLinkedTypeFmt, /*(LPSTR)*/"Linked %s");
      A2W (szAnsiLinkedTypeFmt, szLinkedTypeFmt, 80);
      lpszBuf = OleStdMalloc((OLESTRLEN(lpszFullUserTypeName)+
			      OLESTRLEN(szLinkedTypeFmt)+1)*sizeof(OLECHAR));
      if (lpszBuf) {
	W2A (lpszFullUserTypeName, lpszAnsiFullUserTypeName, 256);
	sprintf(lpszAnsiBuf, szAnsiLinkedTypeFmt, lpszAnsiFullUserTypeName);
	OleStdFreeString(lpszFullUserTypeName, NULL);
	A2W (lpszAnsiBuf, lpszBuf, 256);
	lpszFullUserTypeName = lpszBuf;
      }
    }

  /* Get Source Of Copy
  **    if the object is an embedding, then get the object's moniker
  **    if the object is a link, then get the link source moniker
  */
  if (fIsLink) {

    OLEDBG_BEGIN2("IOleLink::GetSourceDisplayName called\r\n")
      hrErr = lpOleLink->lpVtbl->GetSourceDisplayName(
						      lpOleLink, &lpszSrcOfCopy );
    OLEDBG_END2
      fFreeSrcOfCopy = TRUE;

  } else {

    if (lpszSrcOfCopy == NULL) {
      OLEDBG_BEGIN2("IOleObject::GetMoniker called\r\n")
	hrErr = lpOleObj->lpVtbl->GetMoniker(
					     lpOleObj,
					     OLEGETMONIKER_TEMPFORUSER,
					     OLEWHICHMK_OBJFULL,
					     (LPMONIKER FAR*)&lpSrcMonikerOfCopy
					     );
      OLEDBG_END2
	if (hrErr == NOERROR)
	  {
            CreateBindCtx(0, (LPBC FAR*)&pbc);
            lpSrcMonikerOfCopy->lpVtbl->GetDisplayName(lpSrcMonikerOfCopy,
						       pbc, NULL, &lpszSrcOfCopy);
            pbc->lpVtbl->Release(pbc);
            fFreeSrcOfCopy = TRUE;
	  }
    }
  }

  /*  Get SIZEL */
  if (lpSizelHim) {
    /*  Use extents passed by the caller */
    sizelHim = *lpSizelHim;
  } else if (lpViewObj2) {
    /*  Get the current extents from the object */
    OLEDBG_BEGIN2("IViewObject2::GetExtent called\r\n")
      hrErr = lpViewObj2->lpVtbl->GetExtent(lpViewObj2,
					    dwDrawAspect,
					    -1,     /*lindex*/
					    NULL,   /*ptd*/
					    (LPSIZEL)&sizelHim
					    );
    OLEDBG_END2
      if (hrErr != NOERROR)
	sizelHim.cx = sizelHim.cy = 0;
  } else {
    sizelHim.cx = sizelHim.cy = 0;
  }

  /*  Get DWSTATUS */
  OLEDBG_BEGIN2("IOleObject::GetMiscStatus called\r\n")
    hrErr = lpOleObj->lpVtbl->GetMiscStatus(
					    lpOleObj,
					    dwDrawAspect,
					    &dwStatus
					    );
  OLEDBG_END2
    if (hrErr != NOERROR)
      dwStatus = 0;

  /*  Get OBJECTDESCRIPTOR */
  hObjDesc = OleStdGetOBJECTDESCRIPTORData(
					   clsid,
					   dwDrawAspect,
					   sizelHim,
					   pointl,
					   dwStatus,
					   lpszFullUserTypeName,
					   lpszSrcOfCopy
					   );
  if (! hObjDesc)
    goto error;

  /*  Clean up */
  if (lpszFullUserTypeName)
    OleStdFreeString(lpszFullUserTypeName, NULL);
  if (fFreeSrcOfCopy && lpszSrcOfCopy)
    OleStdFreeString(lpszSrcOfCopy, NULL);
  if (lpSrcMonikerOfCopy)
    OleStdRelease((LPUNKNOWN)lpSrcMonikerOfCopy);
  if (lpOleLink)
    OleStdRelease((LPUNKNOWN)lpOleLink);
  if (lpViewObj2)
    OleStdRelease((LPUNKNOWN)lpViewObj2);

  return hObjDesc;

error:
  if (lpszFullUserTypeName)
    OleStdFreeString(lpszFullUserTypeName, NULL);
  if (fFreeSrcOfCopy && lpszSrcOfCopy)
    OleStdFreeString(lpszSrcOfCopy, NULL);
  if (lpSrcMonikerOfCopy)
    OleStdRelease((LPUNKNOWN)lpSrcMonikerOfCopy);
  if (lpOleLink)
    OleStdRelease((LPUNKNOWN)lpOleLink);
  if (lpViewObj2)
    OleStdRelease((LPUNKNOWN)lpViewObj2);

  return NULL;
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *     test an hResult to see if its ok.  Returns true if no
 *     error and false if there is.  Shows error info in debug window
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Internal only
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL MyTestOleResult(HRESULT hResult)
{
  SCODE scode;
  DWORD dwFacility;
  DWORD dwCode;
  LPSTR pszFacility;
  PERRINFO pEI;

  if (! FAILED(hResult)) {
    return TRUE;
  }

  scode = GetScode(hResult);
  dwFacility = SCODE_FACILITY(scode);
  dwCode = SCODE_CODE(scode);

  switch (dwFacility) {
  case FACILITY_NULL:
    pszFacility = "NULL";
    break;    
  case FACILITY_RPC:    
    pszFacility = "RPC";
    break;    
  case FACILITY_DISPATCH:
    pszFacility = "DISPATCH";
    break;    
  case FACILITY_STORAGE:
    pszFacility = "STORAGE";
    break;    
  case FACILITY_ITF:    
    pszFacility = "ITF";
    break;    
  default:
    pszFacility = "(???)";
    break;    
  }

  /*  try to find it */

  pEI = errinfo;
  while (pEI->scode) {
    if (pEI->scode == scode) break;
    pEI++;
  }

  if (pEI->szDescription) {
    dprintf(DERROR, "OLE %s error: '%s'", pszFacility, pEI->szDescription);
  } else {
    dprintf(DERROR, "OLE %s error: %4.4XH", pszFacility, LOWORD(dwCode));
  }
  return FALSE;
}


/*  Get data for an object.  Note that if bHere is TRUE, the  */
/*  storage has already been allocated. */

BOOL GetObjData(PCOMOBJ pObj, LPFORMATETC pFmt, LPSTGMEDIUM pMed, BOOL bHere)
{
  HGLOBAL hGlobal;
  LPSTR pData = NULL;
  POINTL pointl;
  HRESULT hResult;
  LPSTR pRet;

#ifdef DEBUG
  {
    char buf[256];
    if (pFmt->cfFormat >= CF_PRIVATEFIRST) {
      GetClipboardFormatName(pFmt->cfFormat, buf, sizeof(buf));
    } else {
      sprintf(buf, "%4.4XH", pFmt->cfFormat);
    }
    dprintf(PROGRESS, "GetObjData(%s)", (LPSTR)buf);
  }
#endif /*  DEBUG */

  if (!bHere) {

    
    /*  Set the default return param state */
    

    pMed->tymed = (unsigned long) NULL;
    pMed->hGlobal = NULL;
    pMed->pUnkForRelease = NULL; /*  all punks should be locked up for life */
  }

  
  /*  See which format is being requested */
  

  if (pFmt->cfFormat == CF_TEXT) {

    
    /*  See if it can be returned in some way we can handle */
    

    if (!(pFmt->tymed & TYMED_HGLOBAL)) {

      dprintf(DERROR, "cannot return CF_TEXT in weird format");
      return FALSE;
    }

    
    /*  Since the object did not respond to the request for text data */
    /*  we should supply some sort of description here.  We can */
    /*  ask the object for its user type name. */
    

    if (!bHere) {
      hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE,
			    1024); /*  nice big chunk */
      if (!hGlobal) {
	AlertBox("Out of memory");
	return FALSE;
      }
    } else {
      hGlobal = pMed->hGlobal;
    }

    pData = GlobalLock(hGlobal);
    if (pData) {

      hResult = pObj->pComInfo->lpVtbl->GetUserType(pObj->pComInfo,
						   USERCLASSTYPE_FULL,
						   (unsigned short **) &pRet);
      if (!MyTestOleResult(hResult)) {

	dprintf(DERROR, "Failed to get object user type");
	lstrcpy(pData, "Some OLE thing");

      } else {

	dprintf(DETAIL, " User type: %s", pRet);
	lstrcpy(pData, pRet);

      }

      GlobalUnlock(hGlobal);

    } else {

      dprintf(DERROR, "failed to lock hGlobal");

    }

    if (!bHere) {
      pMed->tymed = TYMED_HGLOBAL;
      pMed->hGlobal = hGlobal;
    }

    dprintf(DETAIL, " returned CF_TEXT in hGlobal");
    return TRUE;

  } else if (pFmt->cfFormat == gcfObjectDescriptor) {

    
    /*  See if it can be returned in some way we can handle */
    

    if (!(pFmt->tymed & TYMED_HGLOBAL)) {

      dprintf(DERROR, "cannot return object Descriptor in weird format");
      return FALSE;
    }

    
    /*  And now some magic from the olestd.c module in ole2ui */
    /*  which will create an obejct descriptor for us.  Note that */
    /*  we use NULL for the name which (apparently) results in the */
    /*  object supplying that for us. */
    

    pointl.x = pointl.y = 0;

    if (!bHere) {

      
      /*  Allocate memory for the return data and fill it in. */
      

      hGlobal = (HGLOBAL) OleStdGetObjectDescriptorDataFromOleObject
	(pObj->pComInfo,
	 NULL,
	 DVASPECT_CONTENT,
	 pointl,
	 (LPSIZEL) NULL);
      if (!hGlobal) {
	dprintf(DETAIL, " failed to get object Descriptor from OLE object");
	return FALSE;
      }

    } else {

      
      /*  The caller is providing the memory.  We cannot handle */
      /*  this because I cannot find a suitable helper function */
      /*  and I am too lazy to do the work.  As it turns out */
      /*  this is not a problem */
      

      dprintf(DERROR, "cannot do 'here'");
      return FALSE;
    }

    if (!bHere) {
      pMed->tymed = TYMED_HGLOBAL;
      pMed->hGlobal = hGlobal;
    }

    dprintf(DETAIL, " returned object Descriptor in hGlobal");
    return TRUE;

  } else if (pFmt->cfFormat == gcfEmbeddedObject) {

    
    /*  See if it can be returned in some way we can handle */
    

    if (!(pFmt->tymed & TYMED_ISTORAGE)) {

      dprintf(DERROR, "cannot return embedded object in weird format");
      return FALSE;
    }

    if (!bHere) {

      dprintf(DERROR, "Arrgh, I do not want to create an ISTORAGE!");
      return FALSE;

    } else {

      
      /*  Copy the istorage */
      

      hResult = pObj->mp_Storage->lpVtbl->CopyTo(pObj->mp_Storage,
					       (unsigned long) NULL,
					       NULL,
					       NULL,
					       pMed->pstg);
      if (!MyTestOleResult(hResult)) return FALSE;

      dprintf(DETAIL, " returned Embedded object in ISTORAGE");
      return TRUE;
    }
  }

  dprintf(DETAIL, " some unknown format");
  return FALSE;
}



STDMETHODIMP OleStdEnumFmtEtc_QueryInterface(LPENUMFORMATETC lpThis,
					     REFIID riid, LPVOID FAR* ppobj)
				  
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;
  *ppobj = NULL;

  if (IsEqualIID(riid,&IID_IUnknown) || IsEqualIID(riid,&IID_IEnumFORMATETC)){
    *ppobj = (LPVOID)lpEF;
  }

  if (*ppobj == NULL) return ResultFromScode(E_NOINTERFACE);
  else{
    OleStdEnumFmtEtc_AddRef(lpThis);
    return NOERROR;
  }

} /* OleStdEnumFmtEtc_QueryInterface() */


STDMETHODIMP_(ULONG) OleStdEnumFmtEtc_AddRef(LPENUMFORMATETC lpThis)
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;
  return lpEF->m_dwRefs++;

} /* OleStdEnumFmtEtc_AddRef()  */



/* OleStdFree
** ----------
**    free memory using the currently active IMalloc* allocator
*/
STDAPI_(void) OleStdFree(LPVOID pmem)
{
  LPMALLOC pmalloc;

  if (pmem == NULL)
    return;

  if (CoGetMalloc(MEMCTX_TASK, &pmalloc) != NOERROR) {
    /*  OleDbgAssertSz(0, szAssertMemAlloc); */
    return;
  }


  if (pmalloc != NULL)
    {
      ULONG refs;
#if defined(_DEBUG)
      int iReturn;
      iReturn = pmalloc->lpVtbl->DidAlloc(pmalloc, pmem);
      /*  OleDbgAssertSz(1 == iReturn, "OleStdFree tried to release a suspicious pointer"); */
#endif
      pmalloc->lpVtbl->Free(pmalloc, pmem);
      refs = pmalloc->lpVtbl->Release(pmalloc);
    }
}


VOID OleStdEnumFmtEtc_Destroy(LPOLESTDENUMFMTETC lpEF)
  /*----------------------------------------------------------------------------
 *
 * ---------------------------------------------------------------------------- */
{
  LPMALLOC lpMalloc=NULL;
  WORD i;

  if (lpEF != NULL) {

    if (CoGetMalloc(MEMCTX_TASK, &lpMalloc) == NOERROR) {

      /* NOTE: we MUST free any memory that was allocated for
      **    TARGETDEVICES contained within the FORMATETC elements.
      */
      for (i=0; i<lpEF->m_nCount; i++) {
	OleStdFree(lpEF->m_lpEtc[i].ptd);
      }

      if (lpEF->m_lpEtc != NULL) {
	lpMalloc->lpVtbl->Free(lpMalloc, lpEF->m_lpEtc);
      }

      lpMalloc->lpVtbl->Free(lpMalloc, lpEF);
      lpMalloc->lpVtbl->Release(lpMalloc);
    }
  }

  g_dwObjectCount-- ;

} /* OleStdEnumFmtEtc_Destroy() */


STDMETHODIMP_(ULONG) OleStdEnumFmtEtc_Release(LPENUMFORMATETC lpThis)
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;
  DWORD dwRefs = --lpEF->m_dwRefs;

  if (dwRefs == 0)
    OleStdEnumFmtEtc_Destroy(lpEF);

  return dwRefs;

} /* OleStdEnumFmtEtc_Release() */



STDMETHODIMP OleStdEnumFmtEtc_Next(LPENUMFORMATETC lpThis, ULONG celt, LPFORMATETC rgelt,
		      ULONG FAR* pceltFetched)
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;
  ULONG i=0;
  ULONG nOffset;

  if (rgelt == NULL) {
    return ResultFromScode(E_INVALIDARG);
  }

  while (i < celt) {
    nOffset = lpEF->m_nIndex + i;

    if (nOffset < lpEF->m_nCount) {
      OleStdCopyFormatEtc((LPFORMATETC)&(rgelt[i]),
			  (LPFORMATETC)&(lpEF->m_lpEtc[nOffset]));
      i++;
    }else{
      break;
    }
  }

  lpEF->m_nIndex += (WORD)i;

  if (pceltFetched != NULL) {
    *pceltFetched = i;
  }

  if (i != celt) {
    return ResultFromScode(S_FALSE);
  }

  return NOERROR;
} /* OleStdEnumFmtEtc_Next() */



STDMETHODIMP OleStdEnumFmtEtc_Skip(LPENUMFORMATETC lpThis, ULONG celt)
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;
  ULONG i=0;
  ULONG nOffset;

  while (i < celt) {
    nOffset = lpEF->m_nIndex + i;

    if (nOffset < lpEF->m_nCount) {
      i++;
    }else{
      break;
    }
  }

  lpEF->m_nIndex += (WORD)i;

  if (i != celt) {
    return ResultFromScode(S_FALSE);
  }

  return NOERROR;
} /* OleStdEnumFmtEtc_Skip() */



STDMETHODIMP OleStdEnumFmtEtc_Reset(LPENUMFORMATETC lpThis)
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;
  lpEF->m_nIndex = 0;

  return NOERROR;
} /* OleStdEnumFmtEtc_Reset() */



STDMETHODIMP OleStdEnumFmtEtc_Clone(LPENUMFORMATETC lpThis, LPENUMFORMATETC FAR* ppenum)
  /* ---------------------------------------------------------------------------- */
  
  /* ---------------------------------------------------------------------------- */
{
  LPOLESTDENUMFMTETC lpEF = (LPOLESTDENUMFMTETC)lpThis;

  if (ppenum == NULL) {
    return ResultFromScode(E_INVALIDARG);
  }

  *ppenum = OleStdEnumFmtEtc_Create(lpEF->m_nCount, lpEF->m_lpEtc);

  /*  make sure cloned enumerator has same index state as the original */
  if (*ppenum) {
    LPOLESTDENUMFMTETC lpEFClone = (LPOLESTDENUMFMTETC)*ppenum;
    lpEFClone->m_nIndex = lpEF->m_nIndex;
    return NOERROR;
  } else
    return ResultFromScode(E_OUTOFMEMORY);

} /* OleStdEnumFmtEtc_Clone() */



static IEnumFORMATETCVtbl g_EnumFORMATETCVtbl = 
{
  OleStdEnumFmtEtc_QueryInterface,
  OleStdEnumFmtEtc_AddRef,
  OleStdEnumFmtEtc_Release,
  OleStdEnumFmtEtc_Next,
  OleStdEnumFmtEtc_Skip,
  OleStdEnumFmtEtc_Reset,
  OleStdEnumFmtEtc_Clone,
};


/*----------------------------------------------------------------------------
 *
 *---------------------------------------------------------------------------- */
STDAPI_(LPENUMFORMATETC) OleStdEnumFmtEtc_Create(ULONG nCount, LPFORMATETC lpEtc)
{
  LPMALLOC lpMalloc=NULL;
  LPOLESTDENUMFMTETC lpEF=NULL;
  DWORD dwSize;
  WORD i;
  HRESULT hRes;

  hRes = CoGetMalloc(MEMCTX_TASK, &lpMalloc);
  if (hRes != NOERROR) {
    return NULL;
  }

  lpEF = (LPOLESTDENUMFMTETC)lpMalloc->lpVtbl->Alloc(lpMalloc,
						     sizeof(OLESTDENUMFMTETC));
  if (lpEF == NULL) {
    goto errReturn;
  }

  lpEF->lpVtbl = &g_EnumFORMATETCVtbl;
  lpEF->m_dwRefs = 1;
  lpEF->m_nCount = nCount;
  lpEF->m_nIndex = 0;

  dwSize = sizeof(FORMATETC) * lpEF->m_nCount;

  lpEF->m_lpEtc = (LPFORMATETC)lpMalloc->lpVtbl->Alloc(lpMalloc, dwSize);
  if (lpEF->m_lpEtc == NULL)
    goto errReturn;

  lpMalloc->lpVtbl->Release(lpMalloc);

  for (i=0; i<nCount; i++) {
    OleStdCopyFormatEtc(
                        (LPFORMATETC)&(lpEF->m_lpEtc[i]), (LPFORMATETC)&(lpEtc[i]));
  }

  g_dwObjectCount++ ;

  return (LPENUMFORMATETC)lpEF;

errReturn:
  if (lpEF != NULL)
    lpMalloc->lpVtbl->Free(lpMalloc, lpEF);

  if (lpMalloc != NULL)
    lpMalloc->lpVtbl->Release(lpMalloc);

  return NULL;

} /* OleStdEnumFmtEtc_Create() */



STDAPI_(void) OleDbgSetDbgLevel(int nDbgLvl)
{
  s_nDbgLevel = nDbgLvl;
}

STDAPI_(int) OleDbgGetDbgLevel( void )
{
  return s_nDbgLevel;
}

STDAPI_(void) OleDbgIndent(int n)
{
  switch (n) {
  case -1:
    s_nDbgIndent--;
    break;
  case 1:
    s_nDbgIndent++;
    break;
  case -2:
    s_nDbgIndent = 0;
    break;
  }
}

STDAPI_(void) OleDbgPrintAlways(LPSTR lpszPrefix, LPSTR lpszMsg, int nIndent)
{
  int i;

  if (nIndent < 0)
    OleDbgIndent(nIndent);

  if (lpszPrefix && *lpszPrefix != '\0') {
    OutputDebugString("| ");
    for (i = 0; i < s_nDbgIndent; i++)
      OutputDebugString("----");

    OutputDebugString(lpszPrefix);
    OutputDebugString(": ");
  }

  OutputDebugString(lpszMsg);
  if (nIndent > 0)
    OleDbgIndent(nIndent);
}

STDAPI_(void) OleDbgPrint(int     nDbgLvl,
			  LPSTR   lpszPrefix,
			  LPSTR   lpszMsg,
			  int     nIndent)
{
  if (nDbgLvl <= s_nDbgLevel)
    OleDbgPrintAlways(lpszPrefix, lpszMsg, nIndent);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *     Generic support for IUnknown methods of our own interfaces.
 *     This only works because we define each of our own interfaces
 *     the same way with the same field names and so on.
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
STDMETHODIMP ImplementQueryInterface (LPVOID pThis,
			      REFIID iid,
			      LPVOID FAR* ppNew,
            BOOL eventInterface)
{
  PCOMOBJ pObj;
  struct _EVENT_LISTENER FAR * pEventListener;

  dprintf(PROGRESS, "ImplementQueryInterface, event interface = %s",
    (eventInterface ? "TRUE" : "FALSE"));

  *ppNew = NULL;

  
  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  
  if (eventInterface) {
      pEventListener = (struct _EVENT_LISTENER FAR *)pThis;
      if (IsEqualIID(iid, pEventListener->iid) ||
          IsEqualIID(iid, &IID_IUnknown))
      {
        *ppNew = pThis;
         return NOERROR;
      }
      else pObj = pEventListener->pData;
  }
  else pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  /*  Test for the interfaces we support in our objects */
  if (IsEqualIID(iid, &IID_IOleClientSite)) {
    dprintf(PROGRESS, " Interface Query: ClientSite");
    *ppNew = &(pObj->ObjIClientSite);
  } else if (IsEqualIID(iid, &IID_IAdviseSink)) {
    dprintf(PROGRESS, " Interface Query: AdviseSink");
    *ppNew = &(pObj->ObjIAdviseSink);
  } else if (IsEqualIID(iid, &IID_IDataObject)) {
    dprintf(PROGRESS, " Interface Query: DataObject");
    *ppNew = &(pObj->ObjIDataObject);
  } else if (IsEqualIID(iid, &IID_IUnknown)) {
    dprintf(PROGRESS, " Interface Query: IUnknown");
    *ppNew = &(pObj->ObjIUnknown);
  } else if (IsEqualIID(iid, &IID_IMarshal)) {
    dprintf(PROGRESS, " Unsupported Interface Query: IMarshal");
    return ResultFromScode(E_NOINTERFACE);
  } else if (IsEqualIID(iid, &IID_IDispatch)) {
    /* IDispatch : 00020400-0000-0000-C000-000000000046 */
    dprintf(PROGRESS, " Interface Query: IDispatch");
    *ppNew = &(pObj->ObjIDispatchAmbient);
  } else if (IsEqualIID(iid, &IID_IOleControlSite)) {
    dprintf(PROGRESS, " Unsupported Interface Query: IOleControlSite");
    return ResultFromScode(E_NOINTERFACE);
  } else if (IsEqualIID(iid, &IID_IOleInPlaceSite)) {
    dprintf(PROGRESS, " Interface Query: IOleInPlaceSite");
    *ppNew = &(pObj->ObjIInPlaceSite);
  } else if (IsEqualIID(iid, &IID_IOleInPlaceSiteEx)) {
    dprintf(PROGRESS, " Interface Query: IOleInPlaceSiteEx");
    *ppNew = &(pObj->ObjIInPlaceSite);
  } else if (IsEqualIID(iid, &IID_IOleInPlaceFrame)) {
    dprintf(PROGRESS, " Interface Query: IOleInPlaceFrame");
    *ppNew = &(pObj->ObjIInPlaceFrame);
  } else if (IsEqualIID(iid, &IID_ISimpleFrameSite)) {
    dprintf(PROGRESS, " Interface Query: ISimpleFrameSite");
    *ppNew = &(pObj->ObjISimpleFrameSite);
  } else if (IsEqualIID(iid, &IID_IOleInPlaceUIWindow)) {
    dprintf(PROGRESS, " Interface Query: IOleInPlaceUIWindow");
    *ppNew = &(pObj->ObjIInPlaceUIWindow);
  } else if (IsEqualIID(iid, &IID_IStdMarshalInfo)) {
    dprintf(PROGRESS, " Unsupported Interface Query: IStdMarshalInfo");
    return ResultFromScode(E_NOINTERFACE);
  } else if (IsEqualIID(iid, &IID_IExternalConnection)) {
    dprintf(PROGRESS, " Unsupported Interface Query: IExternalConnection");
    return ResultFromScode(E_NOINTERFACE);
  } else if (IsEqualIID(iid, (const IID *) &that_1b_thing)) {
    dprintf(PROGRESS, " Unsupported Interface Query: that 1b thing again");
    return ResultFromScode(E_NOINTERFACE);
  } else if (IsEqualIID(iid, &IID_IOleDocumentSite)) {
    dprintf(PROGRESS, " Unsupported Interface Query: IOleDocumentSite");
    return ResultFromScode(E_NOINTERFACE);
  } else {
    dprintf(DETAIL, " unsupported interface requested");
    print_iid_info(NULL,PROGRESS, "Requested IID = ", iid);
    return ResultFromScode(E_NOINTERFACE);
  }

  /*  Increment the reference count on the object since we */
  /*  are returning a valid pointer to one of its interfaces */
  ((LPUNKNOWN)(*ppNew))->lpVtbl->AddRef(*ppNew);

  return NOERROR;
}     


STDMETHODIMP_(ULONG) ImplementAddRef(LPVOID pThis)
{
  PCOMOBJ pObj;

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  (pObj->lRef)++;
  dprintf(PROGRESS, "ImplementAddRef --> %ld", pObj->lRef);

  return pObj->lRef;
}


STDMETHODIMP_(ULONG) ImplementRelease(LPVOID pThis)
{
  PCOMOBJ pObj;
  LONG lReturn;

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  lReturn = --(pObj->lRef);
  dprintf(DUMP, "ImplementRelease --> %ld", pObj->lRef);
  /* ASSERT(pObj->lRef >= 0); */

  if (pObj->lRef == 0) {
    dprintf(DETAIL, " ImplementRelease should delete object %x now ", pObj);
    dprintf(DETAIL, "     because it's reference count is zero");
  }

  return lReturn;
}

/* / IUnknown */

STDMETHODIMP Unknown_QueryInterface(LPUNKNOWN pThis,
				    REFIID iid,
				    LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">Unknown_QueryInterface");

  return (ImplementQueryInterface(pThis, iid, ppNew, FALSE));
}

STDMETHODIMP_(ULONG) Unknown_AddRef(LPUNKNOWN pThis)
{
  dprintf(PROGRESS, ">Unknown_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) Unknown_Release(LPUNKNOWN pThis)
{
  dprintf(PROGRESS, ">Unknown_Release");

  return ImplementRelease(pThis);
}




/*  Client site interface method functions */


STDMETHODIMP ClientSite_QueryInterface(LPOLECLIENTSITE pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">ClientSite_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) ClientSite_AddRef(LPOLECLIENTSITE pThis)
{
  dprintf(PROGRESS, ">ClientSite_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) ClientSite_Release(LPOLECLIENTSITE pThis)
{
  dprintf(PROGRESS, ">ClientSite_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP ClientSite_GetMoniker(LPOLECLIENTSITE pThis,
				   DWORD dwAssign,
				   DWORD dwWhichMoniker,
				   LPMONIKER FAR *ppmk)
{
  dprintf(PROGRESS, ">ClientSite_GetMoniker(%lu, %lu)", dwAssign, dwWhichMoniker);
  *ppmk = NULL;

  return ResultFromScode(E_FAIL);
}

STDMETHODIMP ClientSite_GetContainer(LPOLECLIENTSITE pThis,
				     LPOLECONTAINER FAR *ppContainer)
{
  dprintf(PROGRESS, ">ClientSite_GetContainer");
  *ppContainer = NULL;

  return E_NOINTERFACE;
}

STDMETHODIMP ClientSite_ShowObject(LPOLECLIENTSITE pThis)
{
  dprintf(PROGRESS, ">ClientSite_ShowObject");
    
  return NOERROR;
}

STDMETHODIMP ClientSite_RequestNewObjectLayout(LPOLECLIENTSITE pThis)
{
  dprintf(PROGRESS, ">ClientSite_RequestNewObjectLayout");

  return NOERROR;
}

STDMETHODIMP ClientSite_SaveObject(LPOLECLIENTSITE pThis)
{
  PCOMOBJ pObj;
  LPPERSISTSTORAGE pPersist;
  HRESULT hResult;

  dprintf(PROGRESS, ">ClientSite_SaveObject");

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  /*  Get a pointer to the OLE objects persistent storage interface */
  pPersist = (LPPERSISTSTORAGE) ole_query_interface((LPUNKNOWN) pObj->pComInfo,
						    &IID_IPersistStorage);

  if (!pPersist) {
    dprintf(DERROR, "Failed to get IPersistStorage interface");
    return ResultFromScode(E_FAIL);
  }
  
  /*  We use one of the OLE helper functions to perform */
  /*  this particular piece of black magic. */
  hResult = OleSave(pPersist, pObj->mp_Storage, TRUE);
  pPersist->lpVtbl->Release(pPersist);
  if (!MyTestOleResult(hResult)) {
    dprintf(DERROR, "Failed to save OLE object");
    return ResultFromScode(E_FAIL);
  }

  dprintf(DETAIL, " saved");
  return NOERROR;
}

STDMETHODIMP ClientSite_OnShowWindow(LPOLECLIENTSITE pThis,
				     BOOL fShow)
{
  PCOMOBJ pObj;

  dprintf(PROGRESS, ">ClientSite_OnShowWindow(%u)", fShow);

  
  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  
  /*  Set a flag in the object to say if its currently open in */
  /*  a server window or not.  Redraw it to show its state as */
  /*  shaded or normal */
  if (fShow == FALSE)
    client_set_open_in_window(pObj, FALSE);
  else
    client_set_open_in_window(pObj, TRUE);

  
  /*  Force a redraw */
  client_force_redraw(pObj);

  return NOERROR;
}





/*  Advise sink interface method functions */


STDMETHODIMP AdviseSink_QueryInterface(LPADVISESINK pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">AdviseSink_QueryInterface");

  return (ImplementQueryInterface(pThis, iid, ppNew, FALSE));
}

STDMETHODIMP_(ULONG) AdviseSink_AddRef(LPADVISESINK pThis)
{
  dprintf(PROGRESS, ">AdviseSink_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) AdviseSink_Release(LPADVISESINK pThis)
{
  dprintf(PROGRESS, ">AdviseSink_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP_(void) AdviseSink_OnViewChange(LPADVISESINK pThis,
					    DWORD dwAspect,
					    LONG lIndex)
{
  PCOMOBJ pObj;

  dprintf(PROGRESS, ">AdviseSink_OnViewChange");

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  
  /*  Mark the document as dirty and repaint the  */
  /*  object area to show the changes */
  client_force_redraw(pObj);
}

STDMETHODIMP_(void) AdviseSink_OnDataChange(LPADVISESINK pThis,
					    FORMATETC FAR *pFormatEtc,
					    STGMEDIUM FAR *pStgmed)
{
  AdviseSink_OnViewChange(pThis, DVASPECT_CONTENT, -1);
  dprintf(PROGRESS, ">AdviseSink_OnDataChange");
}

STDMETHODIMP_(void) AdviseSink_OnRename(LPADVISESINK pThis,
					LPMONIKER pMnk)
{
  dprintf(PROGRESS, ">AdviseSink_OnRename");
}

STDMETHODIMP_(void) AdviseSink_OnSave(LPADVISESINK pThis)
{
  dprintf(PROGRESS, ">AdviseSink_OnSave");
}

STDMETHODIMP_(void) AdviseSink_OnClose(LPADVISESINK pThis)
{
  dprintf(PROGRESS, ">AdviseSink_OnClose");
    
}


/*  Data object interface method functions */


/*
 * OleStdCopyTargetDevice()
 *
 * Purpose:
 *  duplicate a TARGETDEVICE struct. this function allocates memory for
 *  the copy. the caller MUST free the allocated copy when done with it
 *  using the standard allocator returned from CoGetMalloc.
 *  (OleStdFree can be used to free the copy).
 *
 * Parameters:
 *  ptdSrc      pointer to source TARGETDEVICE
 *
 * Return Value:
 *    pointer to allocated copy of ptdSrc
 *    if ptdSrc==NULL then retuns NULL is returned.
 *    if ptdSrc!=NULL and memory allocation fails, then NULL is returned
 */
STDAPI_(DVTARGETDEVICE FAR*) OleStdCopyTargetDevice(DVTARGETDEVICE FAR* ptdSrc)
{
  DVTARGETDEVICE FAR* ptdDest = NULL;

  if (ptdSrc == NULL) {
    return NULL;
  }

  if ((ptdDest = (DVTARGETDEVICE FAR*)OleStdMalloc(ptdSrc->tdSize)) != NULL) {
    memcpy(ptdDest, ptdSrc, (size_t)ptdSrc->tdSize);
  }

  return ptdDest;
}


/*
 * OleStdCopyFormatEtc()
 *
 * Purpose:
 *  Copies the contents of a FORMATETC structure. this function takes
 *  special care to copy correctly copying the pointer to the TARGETDEVICE
 *  contained within the source FORMATETC structure.
 *  if the source FORMATETC has a non-NULL TARGETDEVICE, then a copy
 *  of the TARGETDEVICE will be allocated for the destination of the
 *  FORMATETC (petcDest).
 *
 *  NOTE: the caller MUST free the allocated copy of the TARGETDEVICE
 *  within the destination FORMATETC when done with it
 *  using the standard allocator returned from CoGetMalloc.
 *  (OleStdFree can be used to free the copy).
 *
 * Parameters:
 *  petcDest      pointer to destination FORMATETC
 *  petcSrc       pointer to source FORMATETC
 *
 * Return Value:
 *    returns TRUE is copy is successful; retuns FALSE if not successful
 */
STDAPI_(BOOL) OleStdCopyFormatEtc(LPFORMATETC petcDest, LPFORMATETC petcSrc)
{
  if ((petcDest == NULL) || (petcSrc == NULL)) {
    return FALSE;
  }

  petcDest->cfFormat = petcSrc->cfFormat;
  petcDest->ptd      = OleStdCopyTargetDevice(petcSrc->ptd);
  petcDest->dwAspect = petcSrc->dwAspect;
  petcDest->lindex   = petcSrc->lindex;
  petcDest->tymed    = petcSrc->tymed;

  return TRUE;

}


/*****************************************************************************
 * 
 *
 *   Description: 
 *     Test a format to see if we support it
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Internal only
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL IsValidDataFormat(PCOMOBJ pObj, LPFORMATETC pFmt)
{
  int i;
  LPDATAOBJECT pDataObj;
  HRESULT hResult;

  /*   */
  /*  see if we have it in our list */
  

  for (i=0; i<giSingleObjGetFmts; i++) {
    if (gSingleObjGetFmts[i].cfFormat == pFmt->cfFormat) {
      return TRUE;
    }
  }

  
  /*  see if our OLE object supports it */
  

  pDataObj = (LPDATAOBJECT)ole_query_interface((LPUNKNOWN) (pObj->pComInfo),
					       &IID_IDataObject);
  if (pDataObj) {

    hResult = pDataObj->lpVtbl->QueryGetData(pDataObj,
					     pFmt);
    pDataObj->lpVtbl->Release(pDataObj);
    if (SUCCEEDED(hResult)) return TRUE;

  }

  return FALSE;
}


STDMETHODIMP DataObject_QueryInterface(LPDATAOBJECT pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">DataObject_QueryInterface");

  return (ImplementQueryInterface(pThis, iid, ppNew, FALSE));
}

STDMETHODIMP_(ULONG) DataObject_AddRef(LPDATAOBJECT pThis)
{
  dprintf(PROGRESS, ">DataObject_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) DataObject_Release(LPDATAOBJECT pThis)
{
  dprintf(PROGRESS, ">DataObject_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP DataObject_GetData(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                LPSTGMEDIUM pMedium)
{
  PCOMOBJ pObj;
  LPDATAOBJECT pDataObj;
  HRESULT hResult;

  dprintf(PROGRESS, ">DataObject_GetData");

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  
  /*  see if our OLE object can supply it */
  

  pDataObj = (LPDATAOBJECT)ole_query_interface((LPUNKNOWN) (pObj->pComInfo),
					       &IID_IDataObject);
  if (pDataObj) {

    hResult = pDataObj->lpVtbl->GetData(pDataObj,
					pFormat,
					pMedium);
    pDataObj->lpVtbl->Release(pDataObj);
    if (SUCCEEDED(hResult)) {
      dprintf(DETAIL, " data supplied by OLE object");
      return NOERROR;
    }

  }

  
  /*  Might be one for us then */
  
  
  if (GetObjData(pObj, pFormat, pMedium, FALSE)) {
    return NOERROR;
  }

  dprintf(DETAIL, " failed");
  return ResultFromScode(DATA_E_FORMATETC);
}


STDMETHODIMP DataObject_GetDataHere(LPDATAOBJECT pThis,
				    LPFORMATETC pFormat,
				    LPSTGMEDIUM pMedium)
{
  PCOMOBJ pObj;
  LPDATAOBJECT pDataObj;
  HRESULT hResult;

  dprintf(PROGRESS, ">DataObject_GetDataHere");

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  
  /*  see if our OLE object can supply it */
  

  pDataObj = (LPDATAOBJECT)ole_query_interface((LPUNKNOWN) (pObj->pComInfo),
					       &IID_IDataObject);
  if (pDataObj) {

    hResult = pDataObj->lpVtbl->GetDataHere(pDataObj,
                                            pFormat,
                                            pMedium);
    pDataObj->lpVtbl->Release(pDataObj);
    if (SUCCEEDED(hResult)) {
      dprintf(DETAIL, " data supplied by OLE object");
      return NOERROR;
    }
  }

  
  /*  Might be one for us then */
  

  if (GetObjData(pObj, pFormat, pMedium, TRUE)) {
    return NOERROR;
  }


  dprintf(DETAIL, " failed");
  return ResultFromScode(DATA_E_FORMATETC);
}

STDMETHODIMP DataObject_QueryGetData(LPDATAOBJECT pThis,
				     LPFORMATETC pFormat)
{
  PCOMOBJ pObj;

  dprintf(PROGRESS, ">DataObject_QueryGetData");

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  if (!IsValidDataFormat(pObj, pFormat)) {

    dprintf(DETAIL, " unsupported format");
    return ResultFromScode(DATA_E_FORMATETC);
  }

  return NOERROR;
}




STDMETHODIMP DataObject_GetCanonicalFormatEtc(LPDATAOBJECT pThis,
					      LPFORMATETC pInFormat,
					      LPFORMATETC pOutFormat)
{
  dprintf(PROGRESS, ">DataObject_GetCanonicalFormatEtc");

  return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_SetData(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                LPSTGMEDIUM pMedium,
                                BOOL fRelease)
{
  dprintf(PROGRESS, ">DataObject_SetData");

  return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_EnumFormatEtc(LPDATAOBJECT pThis,
				      DWORD dwDirection,
				      LPENUMFORMATETC FAR *ppForm)
{
  dprintf(PROGRESS, ">DataObject_EnumFormatEtc");

  if (dwDirection != DATADIR_GET) {
    return ResultFromScode(E_FAIL);
  }

  
  /*  Call a helper in ole2ui to do the work */
  
  *ppForm = (LPENUMFORMATETC) OleStdEnumFmtEtc_Create(giSingleObjGetFmts, gSingleObjGetFmts);

  /*  dprintf(DERROR, "Sorry, EnumFormatEtc is not currently supported.\n"); */
  return NOERROR;
}

STDMETHODIMP DataObject_DAdvise(LPDATAOBJECT pThis,
                                LPFORMATETC pFormat,
                                DWORD advf,
                                LPADVISESINK pAdvSink,
                                DWORD FAR *pConnect)
{
  dprintf(PROGRESS, ">DataObject_DAdvise");

  return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_DUnadvise(LPDATAOBJECT pThis,
				  DWORD dwConnect)
{
  dprintf(PROGRESS, ">DataObject_DUnadvise");

  return ResultFromScode(E_FAIL);
}

STDMETHODIMP DataObject_EnumDAdvise(LPDATAOBJECT pThis,
				    LPENUMSTATDATA FAR *pAdvise)
{
  dprintf(PROGRESS, ">DataObject_DEnumAdvise");

  return ResultFromScode(E_FAIL);
}




STDMETHODIMP ImplementGetWindow(LPVOID pThis,
  HWND * phwnd  //Pointer to where to return window handle
)
{  
  PCOMOBJ pObj;
  HWND hwnd;

  dprintf(PROGRESS, "ImplementGetWindow");

  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  hwnd = pObj->hwnd;

  dprintf(PROGRESS, "Hwnd returned = %x ", hwnd);
  
  if (hwnd) {
    *phwnd = hwnd;
    return NOERROR;
  }
  else return E_FAIL;
}


STDMETHODIMP ImplementSetActiveObject(LPVOID pThis,
  IOleInPlaceActiveObject *pActiveObject,
                        //Pointer to active in-place object
  LPCOLESTR pszObjName  //Pointer tostring containing a name 
                        // describing the object
)
{
  PCOMOBJ pObj;
  IOleInPlaceActiveObject * pIOleIPActiveObject;

  dprintf(PROGRESS, "  ImplementSetActiveObject");
 
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  pIOleIPActiveObject = pObj->pIOleIPActiveObject; 

  if (NULL!=pIOleIPActiveObject)
        pIOleIPActiveObject->lpVtbl->Release(pIOleIPActiveObject);

  //This will set our member to NULL on deactivation
  pObj->pIOleIPActiveObject=pActiveObject;
  
  if (NULL!=(pObj->pIOleIPActiveObject))
    pObj->pIOleIPActiveObject->lpVtbl->AddRef(pObj->pIOleIPActiveObject);

 return NOERROR;
}


STDMETHODIMP ImplementGetBorder(LPOLEINPLACEFRAME pThis,
  LPRECT lprectBorder  //Pointer to structure
)
{
  PCOMOBJ pObj;

  dprintf(PROGRESS, ">InPlaceFrame_GetBorder");

  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  if (pObj->rect) {
      lprectBorder = pObj->rect;
  }  
  return NOERROR;
}


STDMETHODIMP ImplementSetBorderSpace(LPVOID pThis,
  LPCBORDERWIDTHS pborderwidths  //Pointer to a structure
)
{
 dprintf(PROGRESS, " Implement SetBorderSpace");


 return INPLACE_E_NOTOOLSPACE;
}

STDMETHODIMP ImplementRequestBorderSpace(LPVOID pThis,
  LPCBORDERWIDTHS pborderwidths  //Pointer to a structure
)
{
 dprintf(PROGRESS, " Implement RequestBorderSpace");
 
 return INPLACE_E_NOTOOLSPACE;
}


/* In Place Site interface method functions */

STDMETHODIMP InPlaceSite_QueryInterface(LPOLEINPLACESITEEX pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">InPlaceSite_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) InPlaceSite_AddRef(LPOLEINPLACESITEEX pThis)
{
  dprintf(PROGRESS, ">InPlaceSite_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) InPlaceSite_Release(LPOLEINPLACESITEEX pThis)
{
  dprintf(PROGRESS, ">InPlaceSite_Release");

  return ImplementRelease(pThis);
}


STDMETHODIMP InPlaceSite_GetWindow(LPOLEINPLACESITEEX pThis,
  HWND * phwnd  //Pointer to where to return window handle
)
{  
  dprintf(PROGRESS, ">InPlaceSite_GetWindow");
  return ImplementGetWindow((LPVOID) pThis, phwnd);
}


STDMETHODIMP InPlaceSite_ContextSensitiveHelp(LPOLEINPLACESITEEX pThis,
  BOOL fEnterMode  // Specifies whether or not to enter help mode 
)
{
	dprintf(PROGRESS, ">InPlaceSite_ContextSensitiveHelp");
  return E_NOTIMPL;
}

STDMETHODIMP InPlaceSite_CanInPlaceActivate(LPOLEINPLACESITEEX pThis)
{
	dprintf(PROGRESS, ">InPlaceSite_CanInPlaceActivate");
  return NOERROR;
}

STDMETHODIMP InPlaceSite_OnInPlaceActivate(LPOLEINPLACESITEEX pThis)
{
  PCOMOBJ pObj;

  dprintf(PROGRESS, ">InPlaceSite_OnInPlaceActivate");

  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  /* Find the IOleInPlaceObject interface for that object */
  pObj->pComInfo->lpVtbl->QueryInterface(pObj->pComInfo,&IID_IOleInPlaceObject
        ,(LPVOID FAR*)&pObj->pIOleIPObject);

  return NOERROR;
}

STDMETHODIMP InPlaceSite_OnUIActivate(LPOLEINPLACESITEEX pThis)
{
	dprintf(PROGRESS, ">InPlaceSite_OnUIActivate");

  return E_NOTIMPL;
}

STDMETHODIMP InPlaceSite_GetWindowContext(LPOLEINPLACESITEEX pThis,
  IOleInPlaceFrame **ppFrame,
                       //Address of output variable that receives 
                       // the IOleInPlaceFrame interface pointer
  IOleInPlaceUIWindow **ppDoc,
                       //Address of output variable that receives 
                       // the IOleInPlaceUIWindow interface pointer
  LPRECT lprcPosRect,  //Points to position of in-place object
  LPRECT lprcClipRect, //Points to in-place object's position 
                       // rectangle
  LPOLEINPLACEFRAMEINFO lpFrameInfo
                       //Points to structure
 ) 
{
  PCOMOBJ pObj;
  LPRECT rect;

  dprintf(PROGRESS, ">InPlaceSite_GetWindowContext");
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  /* In place UI Window pointer */
  *ppDoc = (LPOLEINPLACEUIWINDOW) &(pObj->ObjIInPlaceUIWindow);

  /* In place Window pointer */
  *ppFrame = (LPOLEINPLACEFRAME) &(pObj->ObjIInPlaceFrame);

  rect = pObj->rect;

  dprintf(PROGRESS, "Rectangle , left = %d, top = %d, right = %d, bottom = %d",
                    rect->left, rect->top, rect->right, rect->bottom);

  /* Position Rectangle */
  SetRect(lprcPosRect,rect->left,
                   rect->top,
                   rect->right,
                   rect->bottom);
  SetClipBorder(lprcPosRect,JAVA_BORDER_SIZE + CLIP_BORDER_SIZE + 
    (pObj->bIsExcel ? EXCEL_BORDER_SIZE : 0));

  dprintf(PROGRESS, "lprcPosRect , left = %d, top = %d, right = %d, bottom = %d",
                    lprcPosRect->left, lprcPosRect->top, lprcPosRect->right, lprcPosRect->bottom);
  

  /* Clipping Rectangle */

  SetRect(lprcClipRect,rect->left,
                   rect->top,
                   rect->right,
                   rect->bottom);
  SetClipBorder(lprcClipRect, JAVA_BORDER_SIZE); 


  dprintf(PROGRESS, "lprcClipRect , left = %d, top = %d, right = %d, bottom = %d",
                    lprcClipRect->left, lprcClipRect->top, lprcClipRect->right, lprcClipRect->bottom);

  /*  In Place Frame Info */
  lpFrameInfo->cb=sizeof(OLEINPLACEFRAMEINFO);
  lpFrameInfo->fMDIApp=FALSE;

  lpFrameInfo->hwndFrame = pObj->hwnd;

  lpFrameInfo->haccel= CreateAcceleratorTable(NULL,0);

  lpFrameInfo->cAccelEntries=0;


  /* AddRefs to the two new interface pointers that were returned */

  ((LPUNKNOWN)(*ppDoc))->lpVtbl->AddRef((LPUNKNOWN)*ppDoc);
  ((LPUNKNOWN)(*ppFrame))->lpVtbl->AddRef((LPUNKNOWN)*ppFrame);

  dprintf(PROGRESS, ">InPlaceSite_GetWindowContext finished");

  return NOERROR;
}


STDMETHODIMP InPlaceSite_Scroll(LPOLEINPLACESITEEX pThis,
  SIZE scrollExtent  //Number of pixels
) 
{
  dprintf(PROGRESS, ">InPlaceSite_Scroll");
  return E_NOTIMPL;
}

STDMETHODIMP InPlaceSite_OnUIDeactivate(LPOLEINPLACESITEEX pThis,
  BOOL fUndoable  //Specifies if object can undo changes
)
{
  dprintf(PROGRESS, ">InPlaceSite_OnUIDeactivate");
  
  return E_NOTIMPL;
}

STDMETHODIMP InPlaceSite_OnInPlaceDeactivate(LPOLEINPLACESITEEX pThis)
{
  PCOMOBJ pObj;
  IOleInPlaceObject * pIOleIPObject;
  IOleInPlaceActiveObject *pIOleIPActiveObject;

  dprintf(PROGRESS, ">InPlaceSite_OnInPlaceDeactivate");

  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  
  pIOleIPObject = pObj->pIOleIPObject;

  if (pIOleIPObject)
  {
    pIOleIPObject->lpVtbl->Release(pIOleIPObject);
    pObj->pIOleIPObject=NULL;
  }

  pIOleIPActiveObject = pObj->pIOleIPActiveObject;
  if (pIOleIPActiveObject)
  {
    pIOleIPActiveObject->lpVtbl->Release(pIOleIPActiveObject);
    pObj->pIOleIPActiveObject=NULL;
  }


  return S_OK;
} 

STDMETHODIMP InPlaceSite_DiscardUndoState(LPOLEINPLACESITEEX pThis) 
{
  dprintf(PROGRESS, ">InPlaceSite_DiscardUndoState");
  return E_NOTIMPL;

}

STDMETHODIMP InPlaceSite_DeactivateAndUndo(LPOLEINPLACESITEEX pThis) 
{
  dprintf(PROGRESS, ">InPlaceSite_DeactivateAndUndo");
  return E_NOTIMPL;
}


STDMETHODIMP InPlaceSite_OnPosRectChange(LPOLEINPLACESITEEX pThis,
   LPCRECT lprcPosRect  //Pointer to rectangle containing the 
                       // position of in-place object
) 
{
  PCOMOBJ pObj;
  IOleInPlaceObject * pIOleIPObject;
  LPRECT lprcClipRect;

  dprintf(PROGRESS, ">InPlaceSite_OnPosRectChange");
  
  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  pIOleIPObject = pObj->pIOleIPObject;
  if (pIOleIPObject)
  {
     lprcClipRect = malloc(sizeof(RECT));

     SetRect(lprcClipRect,lprcPosRect->left,
       lprcPosRect->top,
       lprcPosRect->right,
       lprcPosRect->bottom);
     
     resizeInPlaceObject(NULL,pObj,pIOleIPObject,(LPRECT)lprcPosRect,(LPRECT)lprcClipRect,TRUE);
  }
  return NOERROR;
}

/* In Place Site Ex interface method functions */

STDMETHODIMP InPlaceSite_OnInPlaceActivateEx(LPOLEINPLACESITEEX pThis,
  BOOL* pfNoRedraw,  //Pointer to current redraw status
  DWORD dwFlags      //Indicates whether the object is windowless
)
{
  (* pfNoRedraw) = TRUE;

  return NOERROR;
}

STDMETHODIMP InPlaceSite_OnInPlaceDeactivateEx(LPOLEINPLACESITEEX pThis,
    BOOL fNoRedraw   //Indicates whether the object needs to be redrawn
)
{
  return NOERROR;
}
 
STDMETHODIMP InPlaceSite_RequestUIActivate(LPOLEINPLACESITEEX pThis)
{
  return S_FALSE; 
}
 

/* In Place Frame interface method functions */

STDMETHODIMP InPlaceFrame_QueryInterface(LPOLEINPLACEFRAME pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">InPlaceFrame_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) InPlaceFrame_AddRef(LPOLEINPLACEFRAME pThis)
{
  dprintf(PROGRESS, ">InPlaceFrame_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) InPlaceFrame_Release(LPOLEINPLACEFRAME pThis)
{
  dprintf(PROGRESS, ">InPlaceFrame_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP InPlaceFrame_GetWindow(LPOLEINPLACEFRAME pThis,
  HWND * phwnd  //Pointer to where to return window handle
)
{  
  dprintf(PROGRESS, ">InPlaceFrame_GetWindow");
  return ImplementGetWindow((LPVOID) pThis, phwnd);

}


STDMETHODIMP InPlaceFrame_ContextSensitiveHelp(LPOLEINPLACEFRAME pThis,
  BOOL fEnterMode  // Specifies whether or not to enter help mode 
)
{
	dprintf(PROGRESS, ">InPlaceFrame_ContextSensitiveHelp");
  return E_NOTIMPL;
}

STDMETHODIMP InPlaceFrame_GetBorder(LPOLEINPLACEFRAME pThis,
  LPRECT lprectBorder  //Pointer to structure
)
{
  dprintf(PROGRESS, ">InPlaceFrame_GetBorder");

  return ImplementGetBorder((LPVOID) pThis,lprectBorder);
}

 
STDMETHODIMP InPlaceFrame_RequestBorderSpace(LPOLEINPLACEFRAME pThis,
  LPCBORDERWIDTHS pborderwidths  //Pointer to a structure
)
{
 dprintf(PROGRESS, ">InPlaceFrame_RequestBorderSpace");
 return ImplementRequestBorderSpace(pThis, pborderwidths);
}

STDMETHODIMP InPlaceFrame_SetBorderSpace(LPOLEINPLACEFRAME pThis,
  LPCBORDERWIDTHS pborderwidths  //Pointer to a structure
)
{
 dprintf(PROGRESS, ">InPlaceFrame_SetBorderSpace");
 return ImplementSetBorderSpace(pThis,pborderwidths);
}
  
STDMETHODIMP InPlaceFrame_SetActiveObject(LPOLEINPLACEFRAME pThis,
  IOleInPlaceActiveObject *pActiveObject,
                        //Pointer to active in-place object
  LPCOLESTR pszObjName  //Pointer tostring containing a name 
                        // describing the object
)
{
 dprintf(PROGRESS, ">InPlaceFrame_SetActiveObject");
 return ImplementSetActiveObject((LPVOID)pThis,pActiveObject,pszObjName);
}

STDMETHODIMP InPlaceFrame_InsertMenus(LPOLEINPLACEFRAME pThis,
  HMENU hmenuShared,                 //Handle to empty menu
  LPOLEMENUGROUPWIDTHS lpMenuWidths  //Pointer to array
)
{
 dprintf(PROGRESS, ">InPlaceFrame_InsertMenus");
 return E_NOTIMPL;
}
 

STDMETHODIMP InPlaceFrame_SetMenu(LPOLEINPLACEFRAME pThis,
  HMENU hmenuShared,     //Handle to composite menu
  HOLEMENU holemenu,     //Handle to menu descriptor
  HWND hwndActiveObject  //Handle to object's window
)
{
 dprintf(PROGRESS, ">InPlaceFrame_SetMenus");
 return E_NOTIMPL;
}

STDMETHODIMP InPlaceFrame_RemoveMenus(LPOLEINPLACEFRAME pThis,
  HMENU hmenuShared  //Handle to in-place composite menu
)
{
 dprintf(PROGRESS, ">InPlaceFrame_RemoveMenus");
 return E_NOTIMPL;
}
 
STDMETHODIMP InPlaceFrame_SetStatusText(LPOLEINPLACEFRAME pThis,
  LPCOLESTR pszStatusText  //Pointer to message to display
)
{
 dprintf(PROGRESS, ">InPlaceFrame_SetStatusText");
 return E_NOTIMPL;
}


STDMETHODIMP InPlaceFrame_EnableModeless(LPOLEINPLACEFRAME pThis,
  BOOL fEnable  //Enable or disable modeless dialog box windows
)
{
 dprintf(PROGRESS, ">InPlaceFrame_SetStatusText");
 return E_NOTIMPL;
}

STDMETHODIMP InPlaceFrame_TranslateAccelerator(LPOLEINPLACEFRAME pThis,
  LPMSG lpmsg,  //Pointer to structure
  WORD wID      //Command identifier value
)
{
 dprintf(PROGRESS, ">InPlaceFrame_TranslateAccelerator");
 return E_NOTIMPL;
}


/* In Place UIWIndow interface method functions */

STDMETHODIMP InPlaceUIWindow_QueryInterface(LPOLEINPLACEUIWINDOW pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">InPlaceUIWindow_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) InPlaceUIWindow_AddRef(LPOLEINPLACEUIWINDOW pThis)
{
  dprintf(PROGRESS, ">InPlaceUIWindow_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) InPlaceUIWindow_Release(LPOLEINPLACEUIWINDOW pThis)
{
  dprintf(PROGRESS, ">InPlaceUIWindow_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP InPlaceUIWindow_GetWindow(LPOLEINPLACEUIWINDOW pThis,
  HWND * phwnd  //Pointer to where to return window handle
)
{  
  dprintf(PROGRESS, ">InPlaceUIWindow_GetWindow");
  return ImplementGetWindow((LPVOID) pThis, phwnd);

}


STDMETHODIMP InPlaceUIWindow_ContextSensitiveHelp(LPOLEINPLACEUIWINDOW pThis,
  BOOL fEnterMode  // Specifies whether or not to enter help mode 
)
{
	dprintf(PROGRESS, ">InPlaceUIWindow_ContextSensitiveHelp");
  return E_NOTIMPL;
}

STDMETHODIMP InPlaceUIWindow_GetBorder(LPOLEINPLACEUIWINDOW pThis,
  LPRECT lprectBorder  //Pointer to structure
)
{
  dprintf(PROGRESS, ">InPlaceUIWindow_GetBorder");
  return ImplementGetBorder((LPVOID) pThis,lprectBorder);
}

 
STDMETHODIMP InPlaceUIWindow_RequestBorderSpace(LPOLEINPLACEUIWINDOW pThis,
  LPCBORDERWIDTHS pborderwidths  //Pointer to a structure
)
{
 dprintf(PROGRESS, ">InPlaceUIWindow_RequestBorderSpace");
 
 return ImplementRequestBorderSpace(pThis, pborderwidths);
}

STDMETHODIMP InPlaceUIWindow_SetBorderSpace(LPOLEINPLACEUIWINDOW pThis,
  LPCBORDERWIDTHS pborderwidths  //Pointer to a structure
)
{
 dprintf(PROGRESS, ">InPlaceUIWindow_SetBorderSpace");
 return ImplementSetBorderSpace(pThis,pborderwidths);
}
  
STDMETHODIMP InPlaceUIWindow_SetActiveObject(LPOLEINPLACEUIWINDOW pThis,
  IOleInPlaceActiveObject *pActiveObject,
                        //Pointer to active in-place object
  LPCOLESTR pszObjName  //Pointer tostring containing a name 
                        // describing the object
)
{
 dprintf(PROGRESS, ">InPlaceUIWindow_SetActiveObject");
 return ImplementSetActiveObject((LPVOID)pThis,pActiveObject,pszObjName);
}


/* IPropertyNotifySink interface method functions */

STDMETHODIMP PropertyNotifySink_QueryInterface(LPPROPERTYNOTIFYSINK pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">PropertyNotifySink_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) PropertyNotifySink_AddRef(LPPROPERTYNOTIFYSINK pThis)
{
  dprintf(PROGRESS, ">PropertyNotifySink_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) PropertyNotifySink_Release(LPPROPERTYNOTIFYSINK pThis)
{
  dprintf(PROGRESS, ">PropertyNotifySink_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP_(ULONG) 
PropertyNotifySink_OnChanged(LPPROPERTYNOTIFYSINK pThis, DISPID dispID)
{
  dprintf(PROGRESS, ">PropertyNotifySink_OnRequestEdit");

  return S_OK;
}

STDMETHODIMP_(ULONG) 
PropertyNotifySink_OnRequestEdit(LPPROPERTYNOTIFYSINK pThis, DISPID dispID)
{
  dprintf(PROGRESS, ">PropertyNotifySink_OnRequestEdit");

  return S_OK;
}

/* ISimpleFrameSite interface method functions */

STDMETHODIMP SimpleFrameSite_QueryInterface(LPSIMPLEFRAMESITE pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">SimpleFrameSite_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) SimpleFrameSite_AddRef(LPSIMPLEFRAMESITE pThis)
{
  dprintf(PROGRESS, ">SimpleFrameSite_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) SimpleFrameSite_Release(LPSIMPLEFRAMESITE pThis)
{
  dprintf(PROGRESS, ">SimpleFrameSite_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP SimpleFrameSite_PreMessageFilter(LPSIMPLEFRAMESITE pThis,
  HWND hWnd,          //Handle of window receiving message
  UINT msg,           //Received message
  WPARAM wp,          //WPARAM of message
  LPARAM lp,          //LPARAM of message
  LRESULT* plResult,  //Pointer to variable to receive result of 
                      //message processing
  DWORD* pdwCookie    //Pointer to a variable used later
)
{
  dprintf(PROGRESS, ">SimpleFrameSite_PreMessageFilter");

  return E_NOTIMPL;
}

STDMETHODIMP SimpleFrameSite_PostMessageFilter(LPSIMPLEFRAMESITE pThis,
  HWND hWnd,          //Handle of window receiving message
  UINT msg,           //Received message
  WPARAM wp,          //WPARAM of message
  LPARAM lp,          //LPARAM of message
  LRESULT* plResult,  //Pointer to variable to receive result
  DWORD dwCookie      //Token returned by PreMessageFilter                                             
)
{
  dprintf(PROGRESS, ">SimpleFrameSite_PostMessageFilter");

  return E_NOTIMPL;
}


/* IDispatch interface for ambient properties */

STDMETHODIMP DispatchAmbient_QueryInterface(LPDISPATCH pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  dprintf(PROGRESS, ">DispatchAmbient_QueryInterface");

  return ImplementQueryInterface(pThis, iid, ppNew, FALSE);
}

STDMETHODIMP_(ULONG) DispatchAmbient_AddRef(LPDISPATCH pThis)
{
  dprintf(PROGRESS, ">DispatchAmbient_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) DispatchAmbient_Release(LPDISPATCH pThis)
{
  dprintf(PROGRESS, ">DispatchAmbient_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP DispatchAmbient_GetIDsOfNames (LPDISPATCH pThis,
      REFIID  riid, 
      OLECHAR FAR* FAR*  rgszNames,  
      unsigned int  cNames,
      LCID   lcid,                   
      DISPID FAR*  rgDispId          
)
{
    dprintf(PROGRESS, ">DispatchAmbient_GetIDsOfNames");
    return E_NOTIMPL;
}

STDMETHODIMP DispatchAmbient_GetTypeInfo (LPDISPATCH pThis,
       unsigned int  iTInfo,        
       LCID  lcid,                   
       ITypeInfo FAR* FAR*  ppTInfo   
)
{
  dprintf(PROGRESS, ">DispatchAmbient_GetTypeInfo");
  return E_NOTIMPL;
}

STDMETHODIMP DispatchAmbient_GetTypeInfoCount (LPDISPATCH pThis,  
      unsigned int FAR*  pctinfo  
)
{
  dprintf(PROGRESS, ">DispatchAmbient_GetTypeInfoCount");
  return E_NOTIMPL;
}

STDMETHODIMP DispatchAmbient_Invoke (LPDISPATCH pThis,  
  DISPID  dispIdMember,  
  REFIID  riid,              
  LCID  lcid,
  WORD  wFlags,              
  DISPPARAMS FAR*  pDispParams,
  VARIANT FAR*  pVarResult,  
  EXCEPINFO FAR*  pExcepInfo,
  unsigned int FAR*  puArgErr  
)
{
  HRESULT hr;
  VARIANT varResult;
  PCOMOBJ pObj;

  dprintf(PROGRESS, ">DispatchAmbient_Invoke");

  /*  Cast the 'this' pointer and deref to get a pointer to our object struct */
  
  pObj = ((struct _ObjIClientSite FAR *)pThis)->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  if (! IsEqualIID(riid,&IID_NULL))
    return ResultFromScode(E_INVALIDARG);

  if (NULL==pVarResult)
    pVarResult = &varResult;

  VariantInit(pVarResult);

  // Use BOOL as the default
  V_VT(pVarResult) = VT_BOOL;

  if (!(DISPATCH_PROPERTYGET & wFlags)) {
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::<Not a property get>");
      return ResultFromScode(DISP_E_MEMBERNOTFOUND);
  }
  hr = NOERROR;

  switch (dispIdMember)
  {
    case DISPID_AMBIENT_BACKCOLOR:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::Backcolor");
      V_I4(pVarResult) = pObj->rgbBack;
      V_VT(pVarResult) = VT_I4;
      break;

    case DISPID_AMBIENT_FORECOLOR:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::ForeColor");      
      V_I4(pVarResult) = pObj->rgbFore;
      V_VT(pVarResult) = VT_I4;
      break;

    case DISPID_AMBIENT_FONT:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::Font");
      /*  Haven't figured out a way to get a font yet
      V_I4(pVarResult) = (LONG) (UINT) pObj->font;
      V_VT(pVarResult) = VT_I4;
      */
      return ResultFromScode(DISP_E_MEMBERNOTFOUND);      
      break;

    case DISPID_AMBIENT_LOCALEID:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::Localeid");
      V_I4(pVarResult) =   pObj->locale;
      V_VT(pVarResult) = VT_I4;
      break;

    case DISPID_AMBIENT_USERMODE:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::Usermode");
      V_BOOL(pVarResult) = (pObj->designMode ? VARIANT_FALSE :
                                               VARIANT_TRUE); 
      break;

    case DISPID_AMBIENT_UIDEAD:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::Uidead");
      V_BOOL(pVarResult) = VARIANT_FALSE;
      break;

    case DISPID_AMBIENT_SUPPORTSMNEMONICS:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::SupportsMnemonics");
      V_BOOL(pVarResult) = VARIANT_FALSE;
      break;

    case DISPID_AMBIENT_SHOWGRABHANDLES:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::ShowGrabHandles");
      V_BOOL(pVarResult) = (pObj->designMode ? VARIANT_TRUE :
                                               VARIANT_FALSE);  
      break;

    case DISPID_AMBIENT_SHOWHATCHING:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::ShowHatching");
      V_BOOL(pVarResult) = (pObj->designMode ? VARIANT_TRUE :
                                               VARIANT_FALSE);  
      break;

    case DISPID_AMBIENT_DISPLAYASDEFAULT:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::DisplayAsDefault");
      V_BOOL(pVarResult) = FALSE;
      break;

    case DISPID_AMBIENT_MESSAGEREFLECT:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::MessageReflect");
      V_BOOL(pVarResult) = FALSE;
      break;

    case DISPID_AMBIENT_AUTOCLIP:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::AutoClip");
      V_BOOL(pVarResult) = FALSE;
      break;

    case DISPID_AMBIENT_DISPLAYNAME:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::DisplayName");
      return ResultFromScode(DISP_E_MEMBERNOTFOUND);      

    case DISPID_AMBIENT_SCALEUNITS:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::ScaleUnits");
      return ResultFromScode(DISP_E_MEMBERNOTFOUND);      

    case DISPID_AMBIENT_TEXTALIGN:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::TextAlign");
      return ResultFromScode(DISP_E_MEMBERNOTFOUND);      

    case DISPID_AMBIENT_APPEARANCE:
      dprintf(PROGRESS, ">DispatchAmbient_Invoke::TextAlign");
      return ResultFromScode(DISP_E_MEMBERNOTFOUND);    

    default:
        dprintf(PROGRESS, ">DispatchAmbient_Invoke::<Unknown>, %x",
                            dispIdMember);
        hr=ResultFromScode(DISP_E_MEMBERNOTFOUND);
        break;
    }

    return hr;
}


/* IDispatch interface for event listeners */

STDMETHODIMP DispatchEvent_QueryInterface(LPDISPATCH pThis,
				       REFIID iid,
				       LPVOID FAR* ppNew)
{
  LPVOID FAR pNew2;
  HRESULT hr;

  dprintf(PROGRESS, ">DispatchEvent_QueryInterface");

  if (IsEqualIID(iid, &IID_IDispatch)) 
  {
      dprintf(PROGRESS, " Interface Query: Event IDispatch");
      *ppNew = pThis;
      return NOERROR;
  }
  
  hr = ImplementQueryInterface(pThis, iid, &pNew2, TRUE);

  /* Should do some more wrapping here .. */

  *ppNew = pNew2;
  return hr;  
}

STDMETHODIMP_(ULONG) DispatchEvent_AddRef(LPDISPATCH pThis)
{
  dprintf(PROGRESS, ">DispatchEvent_AddRef");

  return ImplementAddRef(pThis);
}

STDMETHODIMP_(ULONG) DispatchEvent_Release(LPDISPATCH pThis)
{
  dprintf(PROGRESS, ">DispatchEvent_Release");

  return ImplementRelease(pThis);
}

STDMETHODIMP DispatchEvent_GetIDsOfNames (LPDISPATCH pThis,
      REFIID  riid, 
      OLECHAR FAR* FAR*  rgszNames,  
      unsigned int  cNames,
      LCID   lcid,                   
      DISPID FAR*  rgDispId          
)
{
    dprintf(PROGRESS, ">DispatchEvent_GetIDsOfNames");
    return E_NOTIMPL;
}

STDMETHODIMP DispatchEvent_GetTypeInfo (LPDISPATCH pThis,
       unsigned int  iTInfo,        
       LCID  lcid,                   
       ITypeInfo FAR* FAR*  ppTInfo   
)
{
  dprintf(PROGRESS, ">DispatchEvent_GetTypeInfo");
  return E_NOTIMPL;
}

STDMETHODIMP DispatchEvent_GetTypeInfoCount (LPDISPATCH pThis,  
      unsigned int FAR*  pctinfo  
)
{
  dprintf(PROGRESS, ">DispatchEvent_GetTypeInfoCount");
  return E_NOTIMPL;
}

STDMETHODIMP DispatchEvent_Invoke (LPDISPATCH pThis,  
  DISPID  dispIdMember,  
  REFIID  riid,              
  LCID  lcid,
  WORD  wFlags,              
  DISPPARAMS FAR*  pDispParams,
  VARIANT FAR*  pVarResult,  
  EXCEPINFO FAR*  pExcepInfo,
  unsigned int FAR*  puArgErr  
)
{
  HRESULT hr;

  dprintf(PROGRESS, ">DispatchEvent_Invoke");
  
  if (! IsEqualIID(riid,&IID_NULL))
    return ResultFromScode(E_INVALIDARG);

  hr = forward_event(pThis,
                dispIdMember,  
                pDispParams,
                pVarResult,
                pExcepInfo,
                puArgErr);
  return hr;
}




/*****************************************************************************
 * 
 *
 *   Description: 
 *     Initialize the vtbls of the interfaces we support
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void InitInterfaces()
{
  MyUnknownVtbl.QueryInterface = Unknown_QueryInterface;
  MyUnknownVtbl.AddRef = Unknown_AddRef;
  MyUnknownVtbl.Release = Unknown_Release;

  MyClientSiteVtbl.QueryInterface = ClientSite_QueryInterface;
  MyClientSiteVtbl.AddRef = ClientSite_AddRef;
  MyClientSiteVtbl.Release = ClientSite_Release;
  MyClientSiteVtbl.SaveObject = ClientSite_SaveObject;
  MyClientSiteVtbl.GetMoniker = ClientSite_GetMoniker;
  MyClientSiteVtbl.GetContainer = ClientSite_GetContainer;
  MyClientSiteVtbl.ShowObject = ClientSite_ShowObject;
  MyClientSiteVtbl.OnShowWindow = ClientSite_OnShowWindow;
  MyClientSiteVtbl.RequestNewObjectLayout = ClientSite_RequestNewObjectLayout;

  MyAdviseSinkVtbl.QueryInterface = AdviseSink_QueryInterface;
  MyAdviseSinkVtbl.AddRef = AdviseSink_AddRef;
  MyAdviseSinkVtbl.Release = AdviseSink_Release;
  MyAdviseSinkVtbl.OnDataChange = AdviseSink_OnDataChange;
  MyAdviseSinkVtbl.OnViewChange = AdviseSink_OnViewChange;
  MyAdviseSinkVtbl.OnRename = AdviseSink_OnRename;
  MyAdviseSinkVtbl.OnSave = AdviseSink_OnSave;
  MyAdviseSinkVtbl.OnClose = AdviseSink_OnClose;

  MyDataObjectVtbl.QueryInterface = DataObject_QueryInterface;
  MyDataObjectVtbl.AddRef = DataObject_AddRef;
  MyDataObjectVtbl.Release = DataObject_Release;
  MyDataObjectVtbl.GetData = DataObject_GetData;
  MyDataObjectVtbl.GetDataHere = DataObject_GetDataHere;
  MyDataObjectVtbl.QueryGetData = DataObject_QueryGetData;
  MyDataObjectVtbl.GetCanonicalFormatEtc = DataObject_GetCanonicalFormatEtc;
  MyDataObjectVtbl.SetData = DataObject_SetData;
  MyDataObjectVtbl.EnumFormatEtc = DataObject_EnumFormatEtc;
  MyDataObjectVtbl.DAdvise = DataObject_DAdvise;
  MyDataObjectVtbl.DUnadvise = DataObject_DUnadvise;
  MyDataObjectVtbl.EnumDAdvise = DataObject_EnumDAdvise;

  MyInPlaceSiteVtbl.QueryInterface = InPlaceSite_QueryInterface;
  MyInPlaceSiteVtbl.AddRef = InPlaceSite_AddRef;
  MyInPlaceSiteVtbl.Release = InPlaceSite_Release;
  MyInPlaceSiteVtbl.GetWindow = InPlaceSite_GetWindow;
  MyInPlaceSiteVtbl.ContextSensitiveHelp = InPlaceSite_ContextSensitiveHelp;
  MyInPlaceSiteVtbl.CanInPlaceActivate = InPlaceSite_CanInPlaceActivate;
  MyInPlaceSiteVtbl.OnInPlaceActivate = InPlaceSite_OnInPlaceActivate;
  MyInPlaceSiteVtbl.OnUIActivate =  InPlaceSite_OnUIActivate;
  MyInPlaceSiteVtbl.GetWindowContext =  InPlaceSite_GetWindowContext;
  MyInPlaceSiteVtbl.Scroll =  InPlaceSite_Scroll;
  MyInPlaceSiteVtbl.OnUIDeactivate =  InPlaceSite_OnUIDeactivate;
  MyInPlaceSiteVtbl.OnInPlaceDeactivate =  InPlaceSite_OnInPlaceDeactivate;
  MyInPlaceSiteVtbl.DiscardUndoState =  InPlaceSite_DiscardUndoState;
  MyInPlaceSiteVtbl.DeactivateAndUndo =  InPlaceSite_DeactivateAndUndo;
  MyInPlaceSiteVtbl.OnPosRectChange =  InPlaceSite_OnPosRectChange;
  MyInPlaceSiteVtbl.OnInPlaceActivateEx =  InPlaceSite_OnInPlaceActivateEx;
  MyInPlaceSiteVtbl.OnInPlaceDeactivateEx =  InPlaceSite_OnInPlaceDeactivateEx;
  MyInPlaceSiteVtbl.RequestUIActivate =  InPlaceSite_RequestUIActivate;

  MyInPlaceUIWindowVtbl.QueryInterface = InPlaceUIWindow_QueryInterface;
  MyInPlaceUIWindowVtbl.AddRef = InPlaceUIWindow_AddRef;
  MyInPlaceUIWindowVtbl.Release = InPlaceUIWindow_Release;
  MyInPlaceUIWindowVtbl.GetWindow = InPlaceUIWindow_GetWindow;
  MyInPlaceUIWindowVtbl.ContextSensitiveHelp = InPlaceUIWindow_ContextSensitiveHelp;
  MyInPlaceUIWindowVtbl.GetBorder = InPlaceUIWindow_GetBorder;
  MyInPlaceUIWindowVtbl.RequestBorderSpace = InPlaceUIWindow_RequestBorderSpace;
  MyInPlaceUIWindowVtbl.SetBorderSpace = InPlaceUIWindow_SetBorderSpace;
  MyInPlaceUIWindowVtbl.SetActiveObject = InPlaceUIWindow_SetActiveObject;
  

  MyInPlaceFrameVtbl.QueryInterface = InPlaceFrame_QueryInterface;
  MyInPlaceFrameVtbl.AddRef = InPlaceFrame_AddRef;
  MyInPlaceFrameVtbl.Release = InPlaceFrame_Release;
  MyInPlaceFrameVtbl.GetWindow = InPlaceFrame_GetWindow;
  MyInPlaceFrameVtbl.ContextSensitiveHelp = InPlaceFrame_ContextSensitiveHelp;
  MyInPlaceFrameVtbl.GetBorder = InPlaceFrame_GetBorder;
  MyInPlaceFrameVtbl.RequestBorderSpace = InPlaceFrame_RequestBorderSpace;
  MyInPlaceFrameVtbl.SetBorderSpace = InPlaceFrame_SetBorderSpace;
  MyInPlaceFrameVtbl.SetActiveObject = InPlaceFrame_SetActiveObject;
  MyInPlaceFrameVtbl.InsertMenus = InPlaceFrame_InsertMenus;
  MyInPlaceFrameVtbl.SetMenu = InPlaceFrame_SetMenu;
  MyInPlaceFrameVtbl.RemoveMenus = InPlaceFrame_RemoveMenus;
  MyInPlaceFrameVtbl.SetStatusText = InPlaceFrame_SetStatusText;
  MyInPlaceFrameVtbl.EnableModeless = InPlaceFrame_EnableModeless;
  MyInPlaceFrameVtbl.TranslateAccelerator = InPlaceFrame_TranslateAccelerator;

  MyPropertyNotifySinkVtbl.QueryInterface = PropertyNotifySink_QueryInterface;
  MyPropertyNotifySinkVtbl.AddRef = PropertyNotifySink_AddRef;
  MyPropertyNotifySinkVtbl.Release = PropertyNotifySink_Release;
  MyPropertyNotifySinkVtbl.OnChanged = PropertyNotifySink_OnChanged;
  MyPropertyNotifySinkVtbl.OnRequestEdit = PropertyNotifySink_OnRequestEdit;  

  MySimpleFrameSiteVtbl.QueryInterface = SimpleFrameSite_QueryInterface;
  MySimpleFrameSiteVtbl.AddRef = SimpleFrameSite_AddRef;
  MySimpleFrameSiteVtbl.Release = SimpleFrameSite_Release;
  MySimpleFrameSiteVtbl.PreMessageFilter = SimpleFrameSite_PreMessageFilter;
  MySimpleFrameSiteVtbl.PostMessageFilter = SimpleFrameSite_PostMessageFilter;

  MyDispatchAmbientVtbl.QueryInterface = DispatchAmbient_QueryInterface;
  MyDispatchAmbientVtbl.AddRef = DispatchAmbient_AddRef;
  MyDispatchAmbientVtbl.Release = DispatchAmbient_Release;
  MyDispatchAmbientVtbl.GetIDsOfNames = DispatchAmbient_GetIDsOfNames;
  MyDispatchAmbientVtbl.GetTypeInfo = DispatchAmbient_GetTypeInfo;
  MyDispatchAmbientVtbl.GetTypeInfoCount = DispatchAmbient_GetTypeInfoCount;
  MyDispatchAmbientVtbl.Invoke = DispatchAmbient_Invoke;

  MyDispatchEventVtbl.QueryInterface = DispatchEvent_QueryInterface;
  MyDispatchEventVtbl.AddRef = DispatchEvent_AddRef;
  MyDispatchEventVtbl.Release = DispatchEvent_Release;
  MyDispatchEventVtbl.GetIDsOfNames = DispatchEvent_GetIDsOfNames;
  MyDispatchEventVtbl.GetTypeInfo = DispatchEvent_GetTypeInfo;
  MyDispatchEventVtbl.GetTypeInfoCount = DispatchEvent_GetTypeInfoCount;
  MyDispatchEventVtbl.Invoke = DispatchEvent_Invoke;

  
  /*  Register any clipboard formats we need */
  /*  Note: CF_... defined in global.h  */
  gcfEmbeddedObject = RegisterClipboardFormat(CF_EMBEDDEDOBJECT);
  gcfObjectDescriptor = RegisterClipboardFormat(CF_OBJECTDESCRIPTOR);

    
  /*  Set up the array of formats */
  gSingleObjGetFmts[0].cfFormat = gcfEmbeddedObject;
  gSingleObjGetFmts[0].ptd      = NULL;
  gSingleObjGetFmts[0].dwAspect = DVASPECT_CONTENT;
  gSingleObjGetFmts[0].tymed    = TYMED_ISTORAGE;
  gSingleObjGetFmts[0].lindex   = -1;

  gSingleObjGetFmts[1].cfFormat = gcfObjectDescriptor;
  gSingleObjGetFmts[1].ptd      = NULL;
  gSingleObjGetFmts[1].dwAspect = DVASPECT_CONTENT;
  gSingleObjGetFmts[1].tymed    = TYMED_HGLOBAL;
  gSingleObjGetFmts[1].lindex   = -1;

  gSingleObjGetFmts[2].cfFormat = CF_METAFILEPICT;
  gSingleObjGetFmts[2].ptd      = NULL;
  gSingleObjGetFmts[2].dwAspect = DVASPECT_CONTENT;
  gSingleObjGetFmts[2].tymed    = TYMED_MFPICT;
  gSingleObjGetFmts[2].lindex   = -1;

  gSingleObjGetFmts[3].cfFormat = CF_TEXT;
  gSingleObjGetFmts[3].ptd      = NULL;
  gSingleObjGetFmts[3].dwAspect = DVASPECT_CONTENT;
  gSingleObjGetFmts[3].tymed    = TYMED_HGLOBAL;
  gSingleObjGetFmts[3].lindex   = -1;

  giSingleObjGetFmts = 4;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void initialize_object(PCOMOBJ pObj)
{
  /*  Set the default state of each field */
  pObj->dwMagic = OBJECT_MAGIC;
  pObj->env = NULL;
  pObj->lRef = 0;
  pObj->pComInfo = NULL;
  pObj->pUnk = NULL;
  pObj->oleMisc = 0;
  pObj->mp_Storage = NULL;
  pObj->hwnd = NULL;               
  pObj->createdHwnd = NULL;
  pObj->rect = NULL;         
  pObj->pIOleIPObject = NULL;
  pObj->pIOleIPActiveObject = NULL;
  pObj->pIDispatch = NULL;
  pObj->insertable = TRUE;
  pObj->bIsExcel = FALSE;
  pObj->szStorageName[0] = '\0';
  pObj->pDataObj = NULL;

  pObj->rgbBack = GetSysColor(COLOR_WINDOW);
  pObj->rgbFore = GetSysColor(COLOR_WINDOWTEXT);
  /* Haven't figured out how to get a default font yet
  pObj->font = ; */
  pObj->designMode = FALSE;

  pObj->ObjIUnknown.lpVtbl = &MyUnknownVtbl;
  pObj->ObjIUnknown.pData = pObj;
  pObj->ObjIClientSite.lpVtbl = &MyClientSiteVtbl;
  pObj->ObjIClientSite.pData = pObj;
  pObj->ObjIAdviseSink.lpVtbl = &MyAdviseSinkVtbl;
  pObj->ObjIAdviseSink.pData = pObj;
  pObj->ObjIDataObject.lpVtbl = &MyDataObjectVtbl;
  pObj->ObjIDataObject.pData = pObj;
  
  pObj->ObjIInPlaceSite.lpVtbl = &MyInPlaceSiteVtbl;
  pObj->ObjIInPlaceSite.pData = pObj;

  pObj->ObjIInPlaceUIWindow.lpVtbl = &MyInPlaceUIWindowVtbl;
  pObj->ObjIInPlaceUIWindow.pData = pObj;

  pObj->ObjIInPlaceFrame.lpVtbl = &MyInPlaceFrameVtbl;
  pObj->ObjIInPlaceFrame.pData = pObj;

  pObj->ObjIPropertyNotifySink.lpVtbl = &MyPropertyNotifySinkVtbl;
  pObj->ObjIPropertyNotifySink.pData = pObj;

  pObj->ObjISimpleFrameSite.lpVtbl = &MySimpleFrameSiteVtbl;
  pObj->ObjISimpleFrameSite.pData = pObj;

  pObj->ObjIDispatchAmbient.lpVtbl = &MyDispatchAmbientVtbl;
  pObj->ObjIDispatchAmbient.pData = pObj;

  pObj->event_listeners_head = NULL;
  pObj->event_listeners_tail = NULL;

  pObj->sOpenInWindow = TRUE;
  dprintf(PROGRESS, "Initializing an empty object");
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void initialize_event_listener(EVENT_LISTENER *pEventListener, PCOMOBJ pObj)
{
  pEventListener->dwMagic = EVENT_LISTENER_MAGIC;
  pEventListener->lpVtbl = &MyDispatchEventVtbl;
  pEventListener->pData = pObj;
  pEventListener->next = NULL;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
TRUTH_VALUE is_clipboard_format_available ()
{
  return (TRUTH_VALUE) (IsClipboardFormatAvailable(gcfObjectDescriptor));
}


#endif /* WIN32 */
