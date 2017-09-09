/*****************************************************************************
* xcontain.c
*
* Authors: John Valente, Allan Scott
*  
*****************************************************************************/
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "fileio.h"
#include "shared.h"
#include "xcontain.h"
#include "dprintf.h"


#ifdef WIN32

static char              *gszAppName;              /*  App name */
static HINSTANCE          ghAppInstance = NULL;    /*  App instance */
static DWORD              gdwNextObject = 0;       /*  next free object number */
static BOOL               gfDirty       = FALSE;   /*  TRUE if modified */
static LPSTORAGE          gpStorage     = NULL;    /*  pointer to the current storage object */

/* Use only if COINIT_MULTITHREADED is used in the futute */
/*static BOOL multiThreaded = FALSE; */

/* Needs to be synchronized with ActiveXModes.java */
#define AX_CREATE_LINK        0x0001
#define AX_CREATE_FROM_FILE   0x0002
#define AX_LOCATE_REMOTE      0x0004
#define AX_ACTIVATE_IN_PLACE  0x0008
#define AX_DISPLAY_AS_ICON    0x0010
#define AX_NOT_INSERTABLE     0x0010


OLEDBGDATA_MAIN("BUCKET")

OLEDBGDATA

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

static void update_stuff()
{
  MSG msg;

  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    /* 0x54a, 0x54a, PM_REMOVE */
    //jprintf(env, DUMP, "C handling Message - 0x%x (%d)", 
	//	msg.message, msg.message);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
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
static DWORD WINAPI alert_box_function(LPVOID * pvParameter) {
  char * message;

  message = (char*)pvParameter;
  AlertBox(message);
  return 0;
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

static void PesterUserForLicense() {
  static char message[] = 
    "You are using a 30-day evaluation copy of\n"
    "Gensym's BeanXporter. You may purchase\n"
    "BeanXporter through the on-line store at\n"
    "http://www.gensym.com/java.\n";
  static HANDLE hMsgThread = 0;
  static DWORD threadID = 0;
  /* static DWORD exitCode = 0; */
  /* At one time we only wanted to have one dialog pestering the user
     at a time. But now we do not care, but we may change our minds
     so I am just commenting this out.
  if (hMsgThread != 0 && GetExitCodeThread(hMsgThread, &exitCode) &&
      exitCode == STILL_ACTIVE) {
    return;
  }

  hMsgThread = 0; */

  /* start the alert box function immediately in another thread without
     security attributes, the default stack with the message as the
     parameter. */
  hMsgThread = CreateThread(NULL, 0, alert_box_function, message, 0,
                            &threadID);
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

static int TimeToPesterUserForLicense(JNIEnv *env) {
  static int isLicensed = FALSE;
  static int callCounter = 0;
  static int lastPopup = 0;
  static OLECHAR codeWord[80] = {0};

  jclass pJavaClass = NULL;
  jmethodID constructor = NULL;
  jobject pException = NULL;
  jmethodID getMessageMethod = NULL;
  jobject javaString = NULL;
  BSTR pMessage = NULL;
  int pester = TRUE;

  if (isLicensed)
    return FALSE;

  /* Only check every 5 min, this function could be called every 5
     microseconds, but only call time every 1000th call. */
  if (callCounter < 1000) {
    callCounter++;
    return FALSE;
  }

  callCounter = 0;

  if ((time(NULL) - lastPopup) <= 300)
    return FALSE;

  lastPopup = time(NULL);

  pJavaClass = (*env)->FindClass(env, "com/gensym/com/ActiveXNullException");
  if (pJavaClass == NULL) {
    (*env)->ExceptionClear(env);
    return TRUE;
  }

  constructor = (*env)->GetMethodID(env, pJavaClass, "<init>", "()V");
  if (constructor == NULL) {
    (*env)->ExceptionClear(env);
    return TRUE;
  }

  pException = (*env)->NewObject(env, pJavaClass, constructor);
  if (pException == NULL) {
    (*env)->ExceptionClear(env);
    return TRUE;
  }
  
  getMessageMethod = (*env)->GetMethodID(env, pJavaClass, "getMessage",
                       "()Ljava/lang/String;");
  if (getMessageMethod == NULL) {
    (*env)->ExceptionClear(env);
    return TRUE;
  }

  javaString = (*env)->CallObjectMethod(env, pException, getMessageMethod);
  if (javaString == NULL) {
    (*env)->ExceptionClear(env);
    return TRUE;
  }

  pMessage = java_to_BSTR(env, javaString);
  if (pMessage == NULL) {
    (*env)->ExceptionClear(env);
    return TRUE;
  }

  /* The code word is a calculated number (so it cannot just be searched
     for in the dll file) as a string.
     The number should be changed each version here and in the default
     constructor of ActiveXNullProxy. For ver 1.3 this is 114252. */
  swprintf(codeWord, L"%d", (86525 * /* minor ver. */ 3) %
    (145323 * /* major ver.*/ 1));
  if (wcscmp(pMessage, codeWord) == 0) {
    isLicensed = TRUE;
    pester = FALSE;
  }

  SysFreeString(pMessage);
  return pester;
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
static void delete_object(JNIEnv * env, PCOMOBJ pObj)
{
  jprintf(env, PROGRESS, "delete_object %x", pObj);
  if (!pObj)
	return;

  /* If it has an advisory connection then need to
    unadvise
  */

  if (pObj->pDataObj)
  {
    jprintf(env, DETAIL, " unadvise data object for 0x%x", pObj);
    pObj->pDataObj->lpVtbl->DUnadvise(pObj->pDataObj,
      pObj->unadviseID);
    pObj->pDataObj->lpVtbl->Release(pObj->pDataObj);
  }

  /*  Release the OLE object and its storage */  

  if (pObj->pUnk)
  {
    jprintf(env, DETAIL, " releasing IUnknown object for 0x%x", pObj);
    pObj->pUnk->lpVtbl->Release(pObj->pUnk);
  }

  if (pObj->pComInfo) {
    jprintf(env, DETAIL, " closing OLE object");
    
    pObj->pComInfo->lpVtbl->Close(pObj->pComInfo, OLECLOSE_NOSAVE);

    jprintf(env, DETAIL, " releasing OLE object for 0x%x", pObj);
    pObj->pComInfo->lpVtbl->Release(pObj->pComInfo);
  }

  if (pObj->mp_Storage) {
    jprintf(env, DETAIL, " releasing storage for 0x%x", pObj);
    pObj->mp_Storage->lpVtbl->Release(pObj->mp_Storage);
  }

  if (pObj->pIOleIPObject) {
    jprintf(env, DETAIL, " releasing IOleInPlaceObject for 0x%x", pObj);
    pObj->pIOleIPObject->lpVtbl->Release(pObj->pIOleIPObject);
  }

  if (pObj->pIOleIPActiveObject)
  {
    jprintf(env, DETAIL, " releasing IOleInPlaceActiveObject for 0x%x", pObj);
    pObj->pIOleIPActiveObject->lpVtbl->Release(pObj->pIOleIPActiveObject);
  }

  if (pObj->pIDispatch)
  {
    jprintf(env, DETAIL, " releasing IDispatch for 0x%x", pObj);
    pObj->pIDispatch->lpVtbl->Release(pObj->pIDispatch);
  }

  if (pObj->lRef != 0) {
    jprintf(env, DETAIL, "WARNING: Obj ref count not zero (%lu)", pObj->lRef);
  }

  if (pObj->createdHwnd)
  {
    jprintf(env, DETAIL, "Destroying hidden window for 0x%x", pObj);
    DestroyWindow(pObj->createdHwnd);   
  }
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
static void delete_temporary_object(JNIEnv * env, PCOMOBJ pObj)
{
    delete_object(env, pObj);
    free(pObj);
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
static GUID *copy_guid(GUID *original)
{
    GUID *new_clsid;

    new_clsid = (GUID *) malloc(sizeof(GUID));

    new_clsid->Data1 = original->Data1;
    new_clsid->Data2 = original->Data2;
    new_clsid->Data3 = original->Data3;
    new_clsid->Data4[0] = original->Data4[0];
    new_clsid->Data4[1] = original->Data4[1];
    new_clsid->Data4[2] = original->Data4[2];
    new_clsid->Data4[3] = original->Data4[3];
    new_clsid->Data4[4] = original->Data4[4];
    new_clsid->Data4[5] = original->Data4[5];
    new_clsid->Data4[6] = original->Data4[6];
    new_clsid->Data4[7] = original->Data4[7];

    return new_clsid;
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
static PCOMOBJ create_uninitialized_object(JNIEnv * env)
{
    PCOMOBJ pObj;

    /*  Allocate the memory for the structure */
    pObj = (PCOMOBJ) calloc(sizeof(COMOBJ), 1);
    if (!pObj) {
	jprintf(env, DERROR, "Out of memory allocating object");
	return NULL;
    } else {
	jprintf(env, DUMP, "pObj = %x", pObj);
#ifdef __OBJECT_LIST__
	update_my_local_list(pObj);
#endif
	initialize_object(pObj);
	pObj->env = env;
  return pObj;
    }
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
static void check_for_excel(PCOMOBJ pObj) {  
    CLSID clsExcelApp;

    /*  Remember Excel because it is so odd in so many ways
        Please replace with a better solution 
    */    
    CLSIDFromProgID(L"Excel.Chart", &clsExcelApp);

    if (! (pObj->clsid)) {
      pObj->bIsExcel =FALSE;
      return;
    }

    if (IsEqualCLSID(pObj->clsid, &clsExcelApp))
      pObj->bIsExcel = TRUE;

    CLSIDFromProgID(L"Excel.Sheet", &clsExcelApp);

    if (IsEqualCLSID(pObj->clsid, &clsExcelApp))
      pObj->bIsExcel = TRUE;

    /* End of Excel resize code */
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
static void collect_misc_info(PCOMOBJ pObj) {
  if(pObj->pComInfo) {
    pObj->pComInfo->lpVtbl->GetMiscStatus(pObj->pComInfo,
      DVASPECT_CONTENT,
      &(pObj->oleMisc));
  }
  check_for_excel(pObj);
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
static HRESULT my_ole_create(JNIEnv * env, 
                             PCOMOBJ pObj, 
                             CLSID *pClsid, 
                             BOOL insertable,
                             BSTR license)
{
    HRESULT rslt = S_OK;
    
    jprintf(env, DETAIL, "Inside my ole create, client site = %x",
	  pObj->ObjIClientSite);
    pObj->clsid = pClsid;

    print_iid_info(env, PROGRESS, "my ole create: ", pClsid);
  
    if (insertable) {
      rslt = OleCreate(pClsid, 
        &IID_IOleObject,
        OLERENDER_DRAW,     /*  let server choose format */
        NULL,               /*  no specific format */
        (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
			 pObj->mp_Storage,     /*  storage object */
       (LPVOID)&(pObj->pComInfo)); /*  where to put the result */
      jprintf(env, PROGRESS, "Done with OleCreate; rslt = %x", rslt);
      if (FAILED(rslt))
      {
        AlertBox("Failed to create component - %s", create_error_report(rslt));
        return (jint) NULL;
      }
    } else {
      HRESULT rslt2;
      BOOL useCoCreate = TRUE;

      if (license) 
      {
        /*  START of licensing code */
        IClassFactory2 *pClassFactory = NULL;
        HRESULT hr;
        LICINFO licenseInfo;
      
      
        /* Check to see whether this requires a license to create or not,
        and whether we have one in hand
        */
        /* Get IClassFactory2 */
        hr = CoGetClassObject(  
          pClsid,  //CLSID associated with the class object
          CLSCTX_INPROC_SERVER |
          CLSCTX_LOCAL_SERVER,  //Context for running executable code
          NULL,                    //Pointer to machine on which the object is to 
          // be instantiated
          &IID_IClassFactory2,      //Reference to the identifier of the interface
          (LPVOID *) &pClassFactory      //Address of output variable that receives the 
          // interface pointer requested in riid);
          );

        if (! (FAILED(hr) || (pClassFactory == NULL)))
        {
          // Check to see if we need a license to create
          hr = pClassFactory->lpVtbl->GetLicInfo(pClassFactory, &licenseInfo);
          
          if (! FAILED(hr)) 
          {
            BOOL fLicVerified;
            
            fLicVerified = licenseInfo.fLicVerified;
            if (! fLicVerified)
            {
              // This is the case where the runtime license is used.
              useCoCreate = FALSE;
              
              // In this case we have a license and we will attempt to create
              // the object by using CreateInstanceLic         
              jprintf(env, PROGRESS, "About to call IClassFactory2::CreateInstanceLic, license = %ls",
                license);
              hr =  pClassFactory->lpVtbl->CreateInstanceLic(
                pClassFactory,
                NULL,  //Pointer to controlling unknown of 
                // aggregated object
                NULL,  //Unused. Must be NULL.
                &IID_IUnknown,    //Reference to the identifier of the 
                // interface
                license,         //License key provided by 
                // IClassFactory2::RequestLicKey
                (void **)&(pObj->pUnk));      //Address of output variable that receives 
              // the interface pointer requested in riid)
              
              if (FAILED(hr))
              {
              jprintf(env, PROGRESS, "CreateInstanceLic returned failure 0x%x", hr);
              AlertBox("Failed to create component - %s", create_error_report(hr));
              return (jint) NULL;
              }
            }
          }
        }
      }

      /*  END of licensing code */
        
      if (useCoCreate)
      {
        /* Create an instance of the automation object and ask for the IUnknown interface */
        jprintf(env, PROGRESS, "About to call CoCreateInstance");
        rslt = CoCreateInstance(pClsid, NULL, 
          CLSCTX_INPROC_SERVER |
          /* In proc handler - not found to be useful and would prevent
          some local server application such as ExcelApplication and
          OutlookApplication from giving us an IDispatch interface 
          */
          /*CLSCTX_INPROC_HANDLER |*/
          CLSCTX_LOCAL_SERVER,
          &IID_IUnknown,
          (void **)&(pObj->pUnk));
      
      
        jprintf(env, PROGRESS, "CoCreateInstance returned 0x%x", rslt);
        if (FAILED(rslt)) {
          jprintf(env, PROGRESS, "CoCreateInstance returned failure 0x%x", rslt);
          AlertBox("Failed to create component - %s", create_error_report(rslt));
          return (jint) NULL;
        }
      }
      
      if (pObj->pUnk == NULL)
      {
        AlertBox("Failed to create component - %s", create_error_report(rslt));
        return (jint) NULL;
      }

      jprintf(env, PROGRESS, "pObj = 0x%x; pComInfo = 0x%x", pObj, pObj->pComInfo);
      jprintf(env, PROGRESS, "About to query interface.  pObj->pUnk = 0x%x",
         pObj->pUnk);
      rslt2 = pObj->pUnk->lpVtbl->QueryInterface(pObj->pUnk,
        &IID_IOleObject,
        (void **) &(pObj->pComInfo));
      jprintf(env, PROGRESS, "finished querying interface");
      if (FAILED(rslt2)) {
        jprintf(env, PROGRESS, "Unable to get IOleObject pointer: 0x%x", rslt);
      }
      else {
        IPersistStorage *pPST;
        IPersistStreamInit *pPS; 

        collect_misc_info(pObj);

        if ((pObj->oleMisc &
              OLEMISC_ACTIVATEWHENVISIBLE) != 0) {
            jprintf(env, DETAIL, "Setting client site first", rslt);
            pObj->pComInfo->lpVtbl->SetClientSite(pObj->pComInfo,
                                            (LPOLECLIENTSITE)&(pObj->ObjIClientSite));
        }
        rslt2 = pObj->pUnk->lpVtbl->QueryInterface(pObj->pUnk,
                                                   &IID_IPersistStorage,
                                                   (void **) &(pPST));

        if (FAILED(rslt2)) {
          jprintf(env, DETAIL, "Does not implement IPersistStorage");

          rslt2 = pObj->pUnk->lpVtbl->QueryInterface(pObj->pUnk,
                                                    &IID_IPersistStreamInit,
                                                   (void **) &(pPS));
          if (FAILED(rslt2)) {
              jprintf(env, DETAIL, 
                "Does not implement either IPersistStorage or IPersistStreamInit");
              pObj->pUnk->lpVtbl->Release(pObj->pUnk);
              return my_ole_create(env, pObj, pClsid, TRUE, license);  
          }
          pPS->lpVtbl->InitNew(pPS);
          pPS->lpVtbl->Release(pPS);
        }
        else {
          pPST->lpVtbl->InitNew(pPST, pObj->mp_Storage);
          pPST->lpVtbl->Release(pPST);
        }
      }
      jprintf(env, DETAIL, "CoCreated instance (%x)", rslt);
    }

    /* Collect misc info */
    collect_misc_info(pObj);
    
    jprintf(env, DETAIL, "returning");
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
static BOOL initialize_ole (JNIEnv * env)
{
    HRESULT hResult;

    hResult = OleInitialize(NULL);
    jprintf(env, PROGRESS, "OleInitialize hresult = %x", (unsigned int) hResult);
    if (hResult == S_OK) {
	jprintf(env, PROGRESS, "Successfully initialized.");
	return TRUE;
    } else {
	jprintf(env, PROGRESS, "Failed to initialize OLE.  Error = %x", (unsigned int) hResult);
	return FALSE;
    }
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
static void uninitialize_ole (JNIEnv * env)
{
    jprintf(env, PROGRESS, "UNinitializing OLE");
    OleUninitialize();
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
static BOOL do_from_clsid_stuff (JNIEnv * env, 
                                 PCOMOBJ pObj, 
                                 CLSID *pClsid, 
                                 BOOL insertable,
                                 BSTR license)
{
    HRESULT hResult;
    LPENUMFORMATETC enum_format;
    LPDATAOBJECT pDataObj;
    FORMATETC rgelt[1];
    WCHAR wszStorageName[32];
    HRESULT hr;

    if (!pClsid || IS_NULL_GUID(pClsid)) {
        jprintf(env, DERROR, "Not creating object from NULL clsid.");
        return FALSE;
    }
    
    swprintf(wszStorageName, L"OBJ%lu", gdwNextObject++);
    jprintf(env, DETAIL, "About to attempt to create storage");
    hResult = gpStorage->lpVtbl->CreateStorage(gpStorage,
					   wszStorageName,
                       STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                       | STGM_DIRECT | STGM_CREATE,
                       (unsigned long) NULL,
                       (unsigned long) NULL,
                       &(pObj->mp_Storage));

    if (FAILED(hResult)) {
        AlertBox("Failed to create %ls storage", wszStorageName);
        delete_temporary_object(env, pObj);
        return FALSE;
    }

    wcscpy(pObj->szStorageName, wszStorageName);
    jprintf(env, DETAIL, "Created storage; doing the actual creation");
    
    print_iid_info(env, PROGRESS,
        "Attempting to create an Ole Object from its class id: ", pClsid);
    print_iid_info(env, PROGRESS,
        "Requesting interface:", &IID_IOleObject);
    jprintf(env, PROGRESS, "ClientSite pointer = %d; Storage pointer = %d",
        (int) &(pObj->ObjIClientSite), (int) pObj->mp_Storage);
    
    hResult = my_ole_create(env, pObj, pClsid, insertable, license);
    
    if (FAILED(hResult)) {
        jprintf(env, PROGRESS, "Creation failed, hresult = 0x%x",
            (unsigned int) hResult);
        delete_temporary_object(env,pObj);
        jprintf(env, PROGRESS, "Deleted object");
        return FALSE;
    }

    jprintf(env, PROGRESS, "Creation succeeded. pObj->pComInfo = 0x%x",
        (unsigned int) pObj->pComInfo);

    if (pObj->pComInfo == NULL || !insertable)
        return TRUE;

    hr = pObj->pComInfo->lpVtbl->QueryInterface(pObj->pComInfo,
             &IID_IDataObject,
             &pDataObj);
    if (FAILED(hr) || !pDataObj) {
        jprintf(env, PROGRESS,
            "The object does not implement the IDataObject Interface.");
        return TRUE;
    }

    hr = pDataObj->lpVtbl->EnumFormatEtc(pDataObj, DATADIR_GET, &enum_format);
    /* EnumFormatEtc can return a success code even when a it does not
    provide a format enumeration. */
    if (hr != S_OK) {
        jprintf(env, PROGRESS,
            "Sorry, enum format etc failed (container will not receive updates)");
        return TRUE;
    }

    enum_format->lpVtbl->Next(enum_format, (ULONG) 1, rgelt, NULL);
    jprintf(env, DETAIL, "Calling dadvise");
    hr = pDataObj->lpVtbl->DAdvise(pDataObj,
             &(rgelt[0]),
             0,
             (LPADVISESINK)&(pObj->ObjIAdviseSink),
             &(pObj->unadviseID));
    
    if (FAILED(hr)) {
        pDataObj->lpVtbl->Release(pDataObj);
        jprintf(env, DETAIL, "dadvise returned %x", hr);
        return TRUE;
    }

    pObj->pDataObj = pDataObj;
    return TRUE;
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
static BOOL do_from_data_stuff (JNIEnv * env, PCOMOBJ pObj, CLSID *pClsid)
{
    HRESULT hResult;
    WCHAR wszStorageName[32];
    LPDATAOBJECT pDataObj = NULL;
    
    /*  Invent a name for the storage object and create the storage */
    swprintf(wszStorageName, L"OBJ%lu", gdwNextObject++);
    hResult = gpStorage->lpVtbl->CreateStorage(gpStorage,
              wszStorageName,
              STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,
              (unsigned long) NULL,
              (unsigned long) NULL,
              &(pObj->mp_Storage));
    
    if (FAILED(hResult)) {
        AlertBox("Failed to create %ls storage", wszStorageName);
        delete_temporary_object(env, pObj);
        return FALSE;
    }

    jprintf(env, DUMP, "pDataObj = %x, pObj->ObjIClientSite = %x,"
        "pObj->mp_Storage = %x", pDataObj, pObj->ObjIClientSite,
        pObj->mp_Storage);
    wcscpy(pObj->szStorageName, wszStorageName);
    hResult = OleCreateFromData(pDataObj,
        &IID_IOleObject,
        OLERENDER_DRAW,     /*  let server choose format */
        NULL,               /*  no specific format */
        (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
        pObj->mp_Storage,     /*  storage object */
        (LPVOID)&(pObj->pComInfo)); /*  where to put the result */
    
    if (FAILED(hResult)) {
        jprintf(env, DERROR, "Failed to create OLE object");
        delete_temporary_object(env,pObj);
        return FALSE;
    }
    return TRUE;
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
static PCOMOBJ create_object(JNIEnv * env, 
                             CLSID *pClsid, 
                             DWORD dwFlags, 
                             BOOL insertable,
                             BSTR license)
{
    PCOMOBJ pObj;
    DWORD pointerForUnadvise;
    BOOL result;

    jprintf(env, PROGRESS, "Create Obj - dwFlags = %d", (int) dwFlags);
    if (!pClsid) return NULL;

    pObj = create_uninitialized_object(env);
    pObj->insertable = insertable;
    if (dwFlags & FROM_STORAGE) {
	AlertBox("Sorry, creation from storage is not supported here.");
	/* pObj = do_from_storage_stuff(pObj, pClsid); */
    }
    if (dwFlags & FROM_CLASSID)
	result = do_from_clsid_stuff(env, pObj, pClsid, insertable, license);
    if (!result) return NULL;
    if (dwFlags & FROM_DATA)
	result = do_from_data_stuff(env, pObj, pClsid);
    if (!result) return NULL;

    if (pObj->pComInfo && (! (pObj->oleMisc) & OLEMISC_ACTIVATEWHENVISIBLE)) {
      /*  Set up the notifications we require */
      pObj->pComInfo->lpVtbl->Advise(pObj->pComInfo,
        (LPADVISESINK)&(pObj->ObjIAdviseSink),
        &pointerForUnadvise);
      /*  Call the hokey API which prevents ref count screw ups. */
      OleSetContainedObject((LPUNKNOWN)(pObj->pComInfo), TRUE);
      /*  Set the names we want the host to use */
      jprintf(env, DUMP, "Setting host name to %ls", gszAppName);
      pObj->pComInfo->lpVtbl->SetHostNames(pObj->pComInfo,
        (const unsigned short *) gszAppName,
        (const unsigned short *) NULL);
    }
    return pObj;
}




/*****************************************************************************
 * 
 *
 *   Description: 
 *      Activate an object.
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL ActivateObj(JNIEnv * env, PCOMOBJ pObj, LPRECT rect, HWND hwnd,
                        jboolean inplace)
{
  HRESULT hResult;

  pObj->hwnd = hwnd; 
  pObj->rect = rect; 
  jprintf(env, PROGRESS, "Activate Obj %x", pObj);
  
  /*  Invoke the server to allow the user to set the contents etc. */
  ASSERT(pObj);
  if (!pObj)
    return FALSE;

  if (!pObj->pComInfo)
    return TRUE;

  /* If there is no window then create an off-screen window to allow
   * in place activated components to still in-place activate. If I 
   * know that the component does not need to be displayed at runtime 
   * then I do not do this overhead.
   */
  if (!(pObj->hwnd)  &&
      (pObj->oleMisc & OLEMISC_INVISIBLEATRUNTIME) == 0) {
    /* Destroy the old window before we lose our reference to it. */
    if (pObj->createdHwnd != NULL)
      DestroyWindow(pObj->createdHwnd);

    pObj->createdHwnd = CreateWindow("STATIC", NULL, 0, CW_USEDEFAULT,
			                  0, 0, 0, (HWND)NULL, (HMENU)NULL, NULL, (LPSTR)NULL);
    pObj->hwnd = pObj->createdHwnd;
  }

  /* Prefer in place activation when:
     1) inplace is true
     2) OLEMISC_ACTIVATEIWHENVISIBLE is true
   */
  jprintf(env, DETAIL, "inplace = %d, oleMisc & ACTIVATEWHENVISABLE = %d\n",
    inplace, (pObj->oleMisc & OLEMISC_ACTIVATEWHENVISIBLE));
  jprintf(env,DETAIL,"ComInfo = %x", pObj->pComInfo);
 
  hResult = E_NOTIMPL; 
    
  if (inplace == JNI_TRUE || 
      ((pObj->oleMisc & OLEMISC_ACTIVATEWHENVISIBLE) != 0)) { 
    jprintf(env, PROGRESS,
      "Calling IOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE)");
    hResult = pObj->pComInfo->lpVtbl->DoVerb(pObj->pComInfo,
        OLEIVERB_INPLACEACTIVATE,
        NULL,
        (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
        0,
        hwnd,
        rect);
    if (SUCCEEDED(hResult))
      return TRUE;

    jprintf(env, PROGRESS,
      "IOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE) FAILED, reason: 0x%08.8X",
      hResult);
  }   

  if (FAILED(hResult) & (hResult != RPC_E_SERVERFAULT)) {
    if (pObj->bIsExcel) { 
      jprintf(env, PROGRESS,
        "Calling IOleObject->DoVerb(OLEIVERB_OPEN)");
      hResult = pObj->pComInfo->lpVtbl->DoVerb(pObj->pComInfo,
                OLEIVERB_OPEN, NULL,
                (LPOLECLIENTSITE)&(pObj->ObjIClientSite), 0,
                hwnd, rect);
    } else {
      jprintf(env, PROGRESS,
        "Calling IOleObject->DoVerb(OLEIVERB_PRIMARY)");
      hResult = pObj->pComInfo->lpVtbl->DoVerb(pObj->pComInfo,
                OLEIVERB_PRIMARY, NULL,
                (LPOLECLIENTSITE)&(pObj->ObjIClientSite),
                0, hwnd, rect);
    }
  }

  if (SUCCEEDED(hResult))
    return TRUE;

  /* Grumpy Servers complain all the time */
  if (hResult == RPC_E_SERVERFAULT) {
    jprintf(env, DERROR, "Grumpy Server during Activate, reason : (%8.8lX)",
      GetScode(hResult));
    return TRUE;
  }

  jprintf(env, DERROR, "Failed to Activate Object, reason: (%8.8lX)",
    GetScode(hResult));
  return FALSE;
}




/*****************************************************************************
 * 
 *
 *   Description: 
 *  Create a new document and a new storage object.
 *  Flags:
 *       FILE_PROMPT_FOR_SAVE
 *       FILE_UPDATE_CAPTION
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL FileNew(JNIEnv * env, WORD wFlags)
{
    HRESULT hResult;

    jprintf(env, PROGRESS, "FileNew");

    /* if ((wFlags & FILE_PROMPT_FOR_SAVE) && (!PromptToSave())) return FALSE; */

    if (gpStorage) {
	gpStorage->lpVtbl->Release(gpStorage);
	gpStorage = NULL;       /*  no current storage */
    }

    hResult = StgCreateDocfile(NULL,
			       STGM_READWRITE | STGM_SHARE_EXCLUSIVE
			       | STGM_DIRECT | STGM_CREATE,
			       (DWORD) NULL,
			       &gpStorage);

    if (FAILED(hResult)) {
	jprintf(env, DERROR, "Failed to create a temp. structured storage file (%8.8lXH)",
		GetScode(hResult));
	gpStorage = NULL;
	return FALSE;
    } else if (gpStorage == NULL)
	jprintf(env, PROGRESS, "StgCreateDocfile returned %x but gpStorage is still NULL",
		(unsigned int) hResult);
    else
	jprintf(env, PROGRESS, "Successfully created Docfile (%x)", (unsigned int) hResult);

    return TRUE;
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
static HRESULT saveIPersistStorageToFile(JNIEnv * env, LPUNKNOWN pObj,
                                         WCHAR *pWChar) 
{
    LPPERSISTSTORAGE lpPS;
    IStorage * pstgOpen;	
    HRESULT hErr;
    
    hErr = pObj->lpVtbl->QueryInterface(pObj, &IID_IPersistStorage, 
        (LPVOID FAR *)&lpPS);
    
    if (FAILED(hErr)) {
        jprintf(env, DERROR, "save_object: Does not implement IPersistStorage");
        return hErr;
    }
    
    if (SUCCEEDED(hErr)) {
        jprintf(env, PROGRESS,"save_object: implements IPersistStorage");
        hErr = StgCreateDocfile(pWChar,
            STGM_READWRITE | STGM_SHARE_EXCLUSIVE
            | STGM_DIRECT | STGM_CREATE,
            (DWORD) NULL,
            &pstgOpen);
        
        if (FAILED(hErr)) {
            jprintf(env, DERROR,
                "save_object: Cannot write temporary file for "
                "IPersistStorage, reason: %x", hErr);
            return hErr;
        } 
        
        jprintf(env, PROGRESS,"save_object: docfile created");
        
        hErr = OleSave(lpPS, pstgOpen, FALSE);
        pstgOpen->lpVtbl->Release(pstgOpen);
        
        lpPS->lpVtbl->SaveCompleted(lpPS,NULL);
        lpPS->lpVtbl->Release(lpPS);
        
        
        if (FAILED(hErr)) {
            jprintf(env, DERROR,
                "save_object: OleSave failed, reason: %x", hErr);
            return hErr;
        }
        jprintf(env, PROGRESS,"save_object: OleSave completed successfully");
    }		  
    
    return hErr;
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
static HRESULT loadIPersistStorageFromFile (JNIEnv * env, WCHAR *pWChar,
                                            PCOMOBJ *pObj) 
{ 
    struct IStorage *pstgOpen;
    LPSTORAGE pstgOpen2;
    HRESULT hErr;

    jprintf(env, PROGRESS, "load_object: loading with IPersistStorage");
  
    hErr = StgOpenStorage(pWChar,
			  NULL,
			  STGM_READWRITE | STGM_SHARE_EXCLUSIVE
			  | STGM_DIRECT,
			  (DWORD) NULL,
			  0,
			  &pstgOpen);

    if (FAILED(hErr)) {
	jprintf(env, DERROR,
                "load_object: unable to access temporary file, reason = %x",
                hErr);
	return hErr;
    }
  
    hErr = StgCreateDocfile(NULL,
			    STGM_READWRITE | STGM_SHARE_EXCLUSIVE
			    | STGM_DIRECT | STGM_CREATE,
			    (DWORD) NULL,
			    &pstgOpen2);

    if (FAILED(hErr)) {
	jprintf(env, DERROR,
                "load_object: unable to create anonymous storage, reason = %x",
                hErr);
	return hErr;
    }
  
    hErr = pstgOpen->lpVtbl->CopyTo(pstgOpen,0, NULL, NULL, pstgOpen2);
  
    pstgOpen->lpVtbl->Release(pstgOpen);
    if (FAILED(hErr)) {
	jprintf(env, DERROR,
               "load_object: unable to copy to anonymous storage, reason = %x",
                hErr);
	return (jint) -1;
    }
  
    /* Create empty comObj */
    (*pObj) = create_uninitialized_object(env);
  
    hErr = OleLoad(pstgOpen2,
		   &IID_IUnknown,
		   (LPOLECLIENTSITE)&((* pObj)->ObjIClientSite),
		   &((* pObj)->pUnk));
  
    if (FAILED(hErr)) {
	jprintf(env, DERROR,
                "load_object: unable to load temporary file, reason = %x",
                hErr);
	return hErr;
    }

    hErr = (*pObj)->pUnk->lpVtbl->QueryInterface((*pObj)->pUnk,
                                                 &IID_IOleObject,
                                                 &((*pObj)->pComInfo));

    if (FAILED(hErr)) {
        (*pObj)->pComInfo = NULL;
    }
    else {
        (*pObj)->pUnk = NULL;

	(* pObj)->mp_Storage = pstgOpen2;

        /* Restore CLSID and flags */
        (*pObj)->clsid = malloc(sizeof(CLSID));
        hErr = (*pObj)->pComInfo->lpVtbl->GetUserClassID((*pObj)->pComInfo,
                                                         (* pObj)->clsid);
        if (FAILED(hErr)) {
            jprintf(env, DERROR,
                    "load_object: unable to get CLSID, reason = %x",
                    hErr);
            return hErr;
        }
    }
   
    collect_misc_info(*pObj);
    if ((*pObj)->bIsExcel)
        jprintf(env, DETAIL, "load_object: found to be Excel");
	
    return hErr;
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
static void replace_rect(JNIEnv * env, PCOMOBJ pObj,
                        int left, int top, int right, int bottom) {
  
  LPRECT rect;  

  rect = pObj->rect;

  if (rect == NULL) {
    pObj->rect = malloc(sizeof(RECT));
    rect = pObj->rect;
  }
  SetRect(rect,left, top, right, bottom);

  jprintf(env, PROGRESS, "rect , left = %d, top = %d, right = %d, bottom = %d",
                    rect->left, rect->top, rect->right, rect->bottom);
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
static HRESULT resizeInPlaceObject(JNIEnv * env,
                                   PCOMOBJ pObj,
                                   IOleInPlaceObject * pIOleIPObject,
                                   LPRECT pRect, LPRECT pClipRect,
                                   BOOLEAN inverseClipping)
{ 
  HRESULT hErr = NOERROR;
  
  int clip1 = JAVA_BORDER_SIZE + CLIP_BORDER_SIZE;
  int clip2 = JAVA_BORDER_SIZE;

  if (pObj->bIsExcel) {
      clip1 += EXCEL_BORDER_SIZE;
  }
      
  replace_rect(env, pObj, pRect->left, pRect->top, pRect->right, pRect->bottom);

  if (inverseClipping) {
      SetClipBorder(pClipRect,-clip1);
  }
  else {
    SetClipBorder(pRect,clip1);
    SetClipBorder(pClipRect,clip2);
  }

  jprintf(env, DETAIL, "PRect , left = %d, top = %d, right = %d, bottom = %d",
                    pRect->left, pRect->top, pRect->right, pRect->bottom);

  jprintf(env, DETAIL, "PClipRect , left = %d, top = %d, right = %d, bottom = %d",
                    pClipRect->left, pClipRect->top, pClipRect->right, pClipRect->bottom);


  hErr = pIOleIPObject->lpVtbl->SetObjectRects(pIOleIPObject,pRect, pClipRect);

  if (FAILED(hErr)) {
     jprintf(env, DERROR, "resize_object: unable to resize rectangle, reason = %x",
		hErr);
  }

  return hErr;
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
static LPRECT make_bounding_rectangle(JNIEnv *env, int top, int left, 
				      int bottom, int right)
				      
{
    LPRECT result;
    HPEN hpenRed = NULL;
    HPEN hpenOld = NULL;

    result = (LPRECT) malloc(sizeof(RECT));

    /*  define the bounding rect */
    result->top = top + AXB_TITLEBAR_HEIGHT;
    result->left = left + AXB_BORDER_WIDTH;
    result->bottom = bottom - AXB_TITLEBAR_HEIGHT - AXB_BORDER_HEIGHT;
    result->right = right - AXB_BORDER_WIDTH - AXB_BORDER_WIDTH;

    jprintf(env, PROGRESS, "out: Drawing from (%d, %d) to (%d, %d)\n",
	    result->top, result->left, result->bottom, result->right);

    return result;
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
void SetClipBorder(LPRECT pRect,int size) 
{ 
  int lsize = (int) (((pRect->right - pRect->left) * size) / 100);
  int tsize = (int) (((pRect->bottom - pRect-> top) * size) / 100);
   
  SetRect(pRect, pRect->left  + lsize,
      pRect->top + tsize,
      pRect->right - lsize,
      pRect->bottom - tsize);                    
} 


/*******************************************************************************
 * Code above here is mostly glue between event handler/window and dll.  Code
 * below is mostly implementing the Interfaces necessary to be a container.
 *******************************************************************************/




/****************************************************************************
 * Code below here needs to have the interface functions defined before
 * it is defined.
 ****************************************************************************/

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
void setDirty(jboolean value)
{
    gfDirty = value;
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
void container_setup(JNIEnv * env, char *external_gszname, long external_appInstance)
{
    DWORD versionInfo;

    /*  This code would initialize the container as free
        threaded.  For now I do not see how I can use this,
        because:
        1) The requirement that OleInitialize() be called to
        support in-place activation;
        2) How can I guaruntee that the Java VM has not already
        called CoCreateInstanceEx on it's own
        3) It will only work on Windows NT, or Windows 95 machines
        with the DCOM extension (althought the code below checks for
        that)
    */
    /*
    {
    HANDLE hMod;
    FARPROC fp;
    hMod = GetModuleHandle("ole32.dll");
    fp = GetProcAddress(hMod, "CoCreateInstanceEx");

    if (fp != NULL)
    {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        printf("Calling CoInitializeEx\n");
        multiThreaded = TRUE;
    } 
    }
    */

    if (external_gszname == NULL) {
	gszAppName = "Bucket";
    }
    else {
        if (gszAppName != NULL)
            free(gszAppName);
	gszAppName = external_gszname;
    }

    jprintf(env, PROGRESS, "Setting appname to %s", gszAppName);
    ghAppInstance = (HINSTANCE) external_appInstance;
    start_up_debug_window(ghAppInstance);

    jprintf(env, PROGRESS, "Setting up container: hInstance = %d", external_appInstance);

  
    /*  Check the OLE version is ok and if it is initialize the  */
    /*  libraries we want to use */
    jprintf(env, PROGRESS, "About to determine OLE version");
    versionInfo = CoBuildVersion();
    jprintf(env, PROGRESS, "About to print OLE version");
    jprintf(env, DETAIL, "OLE ver %u.%u", HIWORD(versionInfo), LOWORD(versionInfo));
    if (HIWORD(versionInfo) != rmm) {
	AlertBox("This application requires OLE Version %u.%u",
		 rmm / 10, rmm % 10);
	/* return FALSE; */
    }

    if (LOWORD(versionInfo) < rup) {
	AlertBox("This application requires a later version of the OLE libs.");
	/*  return FALSE; */
    }

  
    /*  Since OLE is a message hog, set the message queue to */
    /*  be the fairly enormous value they suggest */
    SetMessageQueue(96);

  
    /*  Set up the OLE interfaces we support */
    /*  Set up the clipboard formats and data structs we need */
    InitInterfaces();
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
CLSID *get_clsid_and_details_from_user (JNIEnv * env, long hWnd_address,
  int *pdwFlags, char *pszFile) 
{
    HWND hWnd;
    char szFile[OLEUI_CCHPATHMAX];
    UINT uiRet;
    OLEUIINSERTOBJECT insert_object;

    hWnd = (HWND) hWnd_address;
    jprintf(env, PROGRESS, "InsertOleObj");

    /* Fill the info struct with zeroes and fill in any fields we might
       need to. Mostly this is a case of copying the example source code. */
    memset(&insert_object, 0, sizeof(insert_object));
    insert_object.cbStruct = sizeof(insert_object);
    insert_object.dwFlags = IOF_SELECTCREATENEW | IOF_SHOWHELP |
	IOF_DISABLEDISPLAYASICON | IOF_DISABLELINK;
    insert_object.hWndOwner = hWnd;
    szFile[0] = '\0';
    insert_object.lpszFile = szFile;
    insert_object.cchFile = sizeof(szFile);

    uiRet = OleUIInsertObject(&insert_object);

    if (uiRet != OLEUI_OK) {
	if (uiRet != OLEUI_CANCEL) {
	    if (uiRet == OLEUI_ERR_HWNDOWNERINVALID) {
		AlertBox("The specified hwnd address, %x, was not a valid HWND",
			 hWnd_address);
	    } else {
		AlertBox("Insert Dialog failed (%d)", uiRet);
	    }
	}
	(*pdwFlags) = 0;
	return NULL;
    }
	
    if (insert_object.dwFlags & IOF_SELECTCREATEFROMFILE) {
        WCHAR* unicode_string;
        unicode_string = ascii_to_unicode(insert_object.lpszFile);
	GetClassFile(unicode_string, &(insert_object.clsid));
        free(unicode_string);
	(*pdwFlags) = AX_CREATE_FROM_FILE; 
    } else {
	(*pdwFlags) = 0;
    }


    strcpy(pszFile,insert_object.lpszFile); 		
  
    return copy_guid(&(insert_object.clsid));
}


/*****************************************************************************
 * insert_object_from_clsid
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
PCOMOBJ insert_object_from_clsid(JNIEnv * env, 
                                 CLSID *cclsid, 
                                 BOOL insertable,
                                 BSTR license)
{
    PCOMOBJ pObj;

    jprintf(env, PROGRESS, "INSERT OBJECT FROM CLSID");

    /*  At this point, the book says to allocate the storage object,
     *  initialize the container site and then call the appropriate
     *  OLE fuction to create the object.
     *  Lots of tricky stuff here. We will try to get some form of render
     *  cache that will allow us to have the image of the object drawn with
     *  out having to launch the server app.  We use OLERENDER_DRAW to
     *  allow the server to select the render format. 
     */
    jprintf(env, PROGRESS, "checking gpStorage (value = %x)", (int) gpStorage);
    ASSERT(gpStorage);
    if (!gpStorage) 
      return NULL;

    pObj = create_object(env, cclsid, FROM_CLASSID, insertable, license);

    if (!pObj) {
	jprintf(env, DETAIL, "Failed to create new list object");
	return (PCOMOBJ) NULL;
    } else {
	jprintf(env, PROGRESS, "Create Obj returned to insert-object");
	setDirty(TRUE);
    }

    return(pObj);
}


/*****************************************************************************
 * insert_object_from_file
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
PCOMOBJ insert_object_from_file(JNIEnv * env, WCHAR *pWChar) 
{ 			
    LPSTORAGE pstgOpen;
    HRESULT hErr;
    PCOMOBJ pObj;
	
    jprintf(env, PROGRESS, "load_object: loading with IPersistFile");

    hErr = StgCreateDocfile(NULL,
			    STGM_READWRITE | STGM_SHARE_EXCLUSIVE
			    | STGM_DIRECT | STGM_CREATE,
			    (DWORD) NULL,
			    &pstgOpen);

    if (FAILED(hErr)) {
	jprintf(env, DERROR, "load_object: unable to create anonymous storage, reason = %x", hErr);
	return (PCOMOBJ) NULL;
    }
  
    pObj = create_uninitialized_object(env);
    hErr = OleCreateFromFile(
	NULL,
	pWChar,
	&IID_IOleObject,
	OLERENDER_DRAW,     /*  let server choose format */
	NULL,               /*  no specific format */
	(LPOLECLIENTSITE)&(pObj->ObjIClientSite),
	pstgOpen,
	&(pObj->pComInfo));				  
  
    if (FAILED(hErr)) {
	jprintf(env, DERROR, "load_object: unable to load, reason = %x", hErr);
	return (PCOMOBJ) NULL;
    }

  pObj->mp_Storage = pstgOpen;

  /* Restore CLSID and flags */
  pObj->clsid = malloc(sizeof(CLSID));
  hErr = pObj->pComInfo->lpVtbl->GetUserClassID(pObj->pComInfo, pObj->clsid);
  if (FAILED(hErr)) {
    jprintf(env, DERROR, "load_object: unable to get CLSID, reason = %x",hErr);
    return (PCOMOBJ) NULL;
  }       

  collect_misc_info(pObj);
  
  return(pObj);
}



/******************************************************************************
 * Code below here is never called from within this file, and is only used
 * in providing the API.
 ******************************************************************************/


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
JNIEXPORT jboolean JNICALL Java_com_gensym_com_NativeMethodBroker_clear
  (JNIEnv *env, jclass pThis, jshort flags)
{
    BOOL answer;

    answer = FileNew(env, (WORD) flags);
    if (answer)
	setDirty(FALSE);
    jprintf(env, PROGRESS, "Done with clear.");
    return((jboolean) answer);
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
JNIEXPORT void JNICALL Java_com_gensym_com_NativeMethodBroker_terminate
  (JNIEnv *env, jclass pThis, jint hwnd_address)
{
    HWND hwnd;

    hwnd = (HWND) hwnd_address;
    jprintf(env, PROGRESS, "ended");
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
JNIEXPORT jint JNICALL Java_com_gensym_com_NativeMethodBroker_getRatio
  (JNIEnv *env, jclass pThis, jint pObj_address)
{
    LPVIEWOBJECT2 pViewObj;
    HRESULT hrErr = NOERROR, hr;
    PCOMOBJ pObj;
    LPSIZEL extent;
    LONG x, y;

    pObj = (PCOMOBJ) pObj_address;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);
    if (!pObj->insertable) {
	return 100;
    }

    /*  Get a pointer to the IViewObject2 interface which all
     *  insertable objects are supposed to support.   */
    hr = pObj->pComInfo->lpVtbl->QueryInterface(pObj->pComInfo,
						&IID_IViewObject2,
						&pViewObj);
    if (FAILED(hr)) {
	jprintf(env, DERROR, "Failed to obtain IViewObject2 pointer.");
	pViewObj = NULL;
    }
    ASSERT(pViewObj); /*  should always support this */
    if (!pViewObj) return -1;

    extent = (LPSIZEL) malloc(sizeof(SIZE));
    hrErr = pViewObj->lpVtbl->GetExtent(pViewObj,
					DVASPECT_CONTENT,
					-1,
					NULL,
					extent);
    x = extent->cx;
    y = extent->cy;

    jprintf(env, DUMP, "extent = [%d, %d]", extent->cx, extent->cy);

    if (y == 0)
	return -1;
    else
	return ((x * 100) / y);
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_copy_1object
  (JNIEnv *env, jclass pThis, jint pObj_address, 
   jint top, jint left, jint bottom, jint right)
{
    AlertBox("Sorry, the clipboard is not supported yet.");
    return;
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_start_1up
  (JNIEnv *env, jclass pThis)
{
    initialize_ole(env);  
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_shut_1down
  (JNIEnv *env, jclass pThis, jint objPointer)
{
    /* Warning, do not use objPointer, the address it contains has already been
       freed by ActiveXProxy.delete_object! */

    uninitialize_ole(env);
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_update_1stuff
  (JNIEnv *env, jclass pThis)
{
  update_stuff();

  if (TimeToPesterUserForLicense(env)) {
    PesterUserForLicense();
  }
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
JNIEXPORT jboolean JNICALL Java_com_gensym_com_ActiveXProxy_activate_1object
  (JNIEnv *env, jclass pThis, jint pObj_address, jint hwnd_address, 
   jint top, jint left, jint bottom, jint right, jboolean inplace)
{
    HWND hwnd;
    PCOMOBJ pObj;
    LPRECT rect;
    jboolean result;

    hwnd = (HWND) hwnd_address;
    pObj = (PCOMOBJ) pObj_address;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);
    rect = (LPRECT) malloc(sizeof(RECT));
    rect->top = top;
    rect->left = left;
    rect->bottom = bottom;
    rect->right = right;

    jprintf(env, DUMP, "trying to activate %x", pObj_address);
    result = (jboolean) ActivateObj(env, pObj, rect, hwnd, inplace);
    jprintf(env, PROGRESS, "activate_object received answer %d", (long) result);
    return result;
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_delete_1object
  (JNIEnv *env, jclass pThis, jint pObj_address)
{
    PCOMOBJ pObj;

    pObj = (PCOMOBJ) pObj_address;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);
    delete_object(env,pObj);
    setDirty(TRUE);

    /* make sure any assertions fail */
    pObj->dwMagic = 0;
    free(pObj);
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_render_1object
  (JNIEnv *env, jclass pThis, jint pObj_address, 
   jint hwnd_address, jint top, jint left, jint bottom, jint right)
{
    LPVIEWOBJECT2 pViewObj;
    HRESULT hrErr = NOERROR, hr;
    RECT rclHim;
    PCOMOBJ pObj;
    HDC hDC;
    IOleInPlaceObject * pIOleIPObject;

    pObj = (PCOMOBJ) pObj_address;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);
    pIOleIPObject = pObj->pIOleIPObject;
    
    replace_rect(env, pObj, left, top, right, bottom);

    /* In place activatable object, will render itself,
       but needs to know if the Hwnd has changed
    */
    
    if (pIOleIPObject)
    {
      if (pObj->hwnd == (HWND)hwnd_address)
        return;
      else {
          pObj->hwnd = (HWND)hwnd_address;
          pIOleIPObject->lpVtbl->InPlaceDeactivate(pIOleIPObject);
          ActivateObj(env, pObj, pObj->rect, pObj->hwnd, TRUE);
      }
    }

    if (!pObj->insertable) { 
      return;
    }
    hDC = GetDC((HWND) hwnd_address);

    jprintf(env, DUMP, "Rendering in C");
  
    /*  Get a pointer to the IViewObject2 interface which all
     *  insertable COM objects are supposed to support.
     */
    hr = pObj->pComInfo->lpVtbl->QueryInterface(pObj->pComInfo,
						&IID_IViewObject2,
						&pViewObj);
	
    if (FAILED(hr)) {
	jprintf(env, DERROR, "Failed to obtain IViewObject2 pointer.");
	pViewObj = NULL;
    }
    ASSERT(pViewObj); /*  should always support this */
    if (!pViewObj) return;

    /*  define the bounding rect */
    rclHim.top = top;
    rclHim.left = left;
    rclHim.bottom = bottom;
    rclHim.right = right;

    /*  Invoke the Draw method */
    hrErr = pViewObj->lpVtbl->Draw(pViewObj, 
				   DVASPECT_CONTENT, /*  draw content (for now) */
				   -1, NULL, NULL, NULL,
           hDC, (LPRECTL) &rclHim, NULL, NULL, 0); 
				   /* hDC, &rclHim, &rclHim, NULL, 0); */
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
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_resize_1object
  (JNIEnv *env, jclass pThis, jint pObj_address, 
   jint top, jint left, jint bottom, jint right)
{
    PCOMOBJ pObj;
    IOleInPlaceObject * pIOleIPObject;
    LPRECT pRect, pClipRect;

    pObj = (PCOMOBJ) pObj_address;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);
    pIOleIPObject = pObj->pIOleIPObject;

    jprintf(env, PROGRESS,"Resize Object called in C");

    jprintf(env, PROGRESS,"Resize: %d, %d, %d,%d",left,top,right,bottom);

    pRect = malloc(sizeof(RECT));
    SetRect(pRect,left,top,right,bottom);
    pObj->rect = pRect;
    
    /* Only in place activatable object need be resized, all others
     * are dealt with by render_object */

    if ((! pIOleIPObject) && 
        ((pObj->oleMisc & OLEMISC_ACTIVATEWHENVISIBLE) != 0))
    {
      if (pObj->pComInfo)
      {
        /* Find the IOleInPlaceObject interface for that object */
        pObj->pComInfo->lpVtbl->QueryInterface(pObj->pComInfo,&IID_IOleInPlaceObject
          ,(LPVOID FAR*)&pObj->pIOleIPObject);
        pIOleIPObject = pObj->pIOleIPObject;
      }
    }
    if (pIOleIPObject) {
      jprintf(env, PROGRESS,"Resize Object called in C, and we have pIOleIPObject");
        
      pClipRect = malloc(sizeof(RECT));
      SetRect(pClipRect,left,top,right,bottom);

      resizeInPlaceObject(env, pObj, pIOleIPObject,pRect, pClipRect, FALSE);
    }
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
JNIEXPORT jstring JNICALL Java_com_gensym_com_ActiveXProxy_save_1object
  (JNIEnv *env, jclass pThis, jint pObj_address, jstring pJString)
{
  PCOMOBJ pObj;
  IUnknown *pIUnknown = NULL;
  WCHAR *pFileName;
  HRESULT hErr;

  jprintf(env, PROGRESS, "save_object");

  pObj = (PCOMOBJ) pObj_address;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  if (pObj->pComInfo) {
    pIUnknown = (IUnknown*) pObj->pComInfo;
  } else if (pObj->pUnk) {
      pIUnknown = pObj->pUnk;
  }

  if (pIUnknown) {
    pFileName = java_to_unicode_string(env, pJString);
    hErr = saveIPersistStorageToFile(env, pIUnknown, pFileName);
    free(pFileName);
    if (SUCCEEDED(hErr)) 
      return pJString;
  }

  jprintf(env, DERROR, "save_object: Failed to save");
  return (* env)->NewStringUTF(env,"");
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
JNIEXPORT jint JNICALL Java_com_gensym_com_ActiveXProxy_load_1object
  (JNIEnv *env, jclass pThis, jstring pJString)
{
  WCHAR* fileString;
  PCOMOBJ pObj;
  HRESULT hErr;

  jprintf(env, PROGRESS, "load_object");

  fileString = java_to_unicode_string(env, pJString);
  jprintf(env, PROGRESS, "load_object: filename %ls", fileString);

  hErr = StgIsStorageFile(fileString);
  free(fileString);
  if (hErr == S_OK) {
    hErr = loadIPersistStorageFromFile(env, fileString, &pObj); 
  }

  if (FAILED(hErr))
    return (jint) NULL;
					   
  jprintf(env, PROGRESS, "load_object: completed");
  return (jint) pObj;		
}


#endif /* WIN32 */
