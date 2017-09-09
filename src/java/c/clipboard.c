#include <stdio.h>
#include "fileio.h"
#include "shared.h"
#include "xcontain.h"
#include "dprintf.h"


#ifdef WIN32

static PCOMOBJ            my_local_list = NULL;


/*****************************************************************************
 * 
 *
 *   Description: 
 *     Make a copy of an object
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *    Not yet ready!!
 *     -----
 *   Modifications:
 *****************************************************************************/
static PCOMOBJ CopyObj(PCOMOBJ pObj, struct tagRECT *rectl)
{
    PCOMOBJ pNewObj = NULL;
    HRESULT hResult;

    dprintf(PROGRESS, "CopyObj");

    pNewObj = create_uninitialized_object();

    ASSERT(pObj->mp_Storage);
    if (!pObj->mp_Storage) return NULL;

    hResult = StgCreateDocfile(NULL,
			       STGM_READWRITE | STGM_SHARE_EXCLUSIVE
			       | STGM_DIRECT | STGM_CREATE,
			       (DWORD) NULL,
			       &(pNewObj->mp_Storage));
    if (FAILED(hResult)) {
	dprintf(DERROR, "Failed to create temp. storage");
	delete_temporary_object(pNewObj);
	return NULL;
    } else
	dprintf(PROGRESS, "StgCreateDocfile = %d", (unsigned int) hResult);

    /*  Copy the data  */
    hResult = pObj->mp_Storage->lpVtbl->CopyTo(pObj->mp_Storage,
				       (unsigned long) NULL,
				       NULL, NULL, pNewObj->mp_Storage);
    if (FAILED(hResult)) {
	dprintf(DERROR, "Failed to copy object storage");
	delete_temporary_object(pNewObj);
	return NULL;
    }
  
    /*  Create the new OLE object */
    ASSERT(pObj->clsid);
    if (!pObj->clsid) return NULL;

    hResult = OleCreate(pObj->clsid,
			&IID_IOleObject,
			OLERENDER_DRAW,     /*  let server chose format */
			NULL,               /*  no specific format */
			NULL,
			pNewObj->mp_Storage,     /*  storage object */
			(LPVOID)&(pNewObj->pComInfo));

    if (FAILED(hResult)) {
	dprintf(DERROR, "Failed to create OLE COMOBJ");
	delete_temporary_object(pNewObj);
	return NULL;
    }

    return pNewObj;
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
void Java_com_gensym_com_ActiveXProxy_copy_object
  (JNIEnv *env, jclass pThis, jint pObj_address, 
   jint top, jint left, jint bottom, jint right)
{
    LPSTR pData = NULL;
    PCOMOBJ pCFObj;
    LPDATAOBJECT pDataObj = NULL;
    HRESULT hResult;
    struct tagRECT rectl;  
    PCOMOBJ pObj;

    rectl.top = top;
    rectl.left = left;
    rectl.bottom = bottom;
    rectl.right = right;
    pObj = (PCOMOBJ) pObj_address;

    dprintf(PROGRESS, "Cut/Copy (%d, %d) - (%d, %d)", left, top, bottom, right);
    ASSERT(pObj);
    if (!pObj) return;
  
    /*  Make a snapshot of the object here */
    pCFObj = CopyObj(pObj, &rectl);
    if (!pCFObj) {
	AlertBox("Unable to copy object");
	return;
    }

  
    /*  get access to the clipboard */
    pDataObj = NULL;
    hResult = OleGetClipboard(&pDataObj);
    if (pDataObj)
	pDataObj->lpVtbl->Release(pDataObj);

  
    /*  Get a pointer to the data object  */
    pDataObj = (LPDATAOBJECT) &(pCFObj->ObjIDataObject);

  
    /*  Stuff it in the clipboard */
    hResult = OleSetClipboard(pDataObj);
    SUCCEEDED(hResult);
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     How to associate the storage (pObj->mp_Storage) ?
 *     -----
 *   Modifications:
 *****************************************************************************/
static HRESULT my_ole_create_manually(PCOMOBJ pObj, CLSID *pClsid)
{
    HRESULT rslt = S_OK;
    IClassFactory *pCF;
    IOleObject *pOO;

    dprintf(PROGRESS, "Inside my ole create (manually), client site = %x",
	    pObj->ObjIClientSite);
    print_iid_info(PROGRESS, "my ole create_manually: ", pClsid);
    rslt = CoGetClassObject(pClsid, CLSCTX_ALL, NULL,
			    &IID_IClassFactory,(void **)&pCF);
    dprintf(PROGRESS, "Got class factory");
    if (FAILED(rslt)) {
	dprintf(ALWAYS, "CoGetClassObject failed with result %x", rslt);
	return rslt;
    }

    rslt = pCF->lpVtbl->CreateInstance(pCF, NULL, &IID_IOleObject, &pOO);
    dprintf(PROGRESS, "Created instance; rslt = %x", rslt);
    /* pCF->lpVtbl->Release(pCF); */
    pObj->pComInfo = pOO;
    dprintf(PROGRESS, "About to set client site");
    if (pOO)
	pOO->lpVtbl->SetClientSite(pOO, (LPOLECLIENTSITE)&(pObj->ObjIClientSite));

    dprintf(PROGRESS, "Done with creation from Class Factory; rslt = %x", rslt);
    return rslt;
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
static void print_comobj(PCOMOBJ pObj)
{
    dprintf(PROGRESS, "storage name = %s", pObj->szStorageName);
    dprintf(PROGRESS, "%d references to it.", pObj->lRef);
    dprintf(PROGRESS, "pStorage = 0x%x; pComInfo = 0x%x", pObj->mp_Storage, pObj->pComInfo);
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
static void output_my_local_list (jclass pThis)
{
    PCOMOBJ current;

    for (current=my_local_list; current; current=current->next)
	print_comobj(current);
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
void update_my_local_list(PCOMOBJ pObj)
{
    pObj->next = my_local_list;
    my_local_list = pObj;
}


#endif
