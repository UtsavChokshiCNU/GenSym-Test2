/*****************************************************************************
* autojava.c
*
* Author: Allan Scott
*  
*****************************************************************************/
#include "shared.h"
#include "dprintf.h"

#ifdef WIN32

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
 BOOL Connect(LPUNKNOWN pObj, REFIID riid
   , LPUNKNOWN pIUnknownSink, LPDWORD pdwConn)
   {
   HRESULT           hr;
   LPCONNECTIONPOINTCONTAINER pCPC;
   LPCONNECTIONPOINT      pCP;

   if (NULL==pObj || NULL==pIUnknownSink || NULL==pdwConn)
      return FALSE;

   hr=pObj->lpVtbl->QueryInterface(pObj, &IID_IConnectionPointContainer
      , (VOID **)&pCPC);

   if (FAILED(hr))
      return FALSE;

   hr=pCPC->lpVtbl->FindConnectionPoint(pCPC, riid, &pCP);

   if (SUCCEEDED(hr))
      {
      hr=pCP->lpVtbl->Advise(pCP, pIUnknownSink, pdwConn);
      pCP->lpVtbl->Release(pCP);
      }

   pCPC->lpVtbl->Release(pCPC);
   return SUCCEEDED(hr);
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
BOOL Disconnect(LPUNKNOWN pObj, REFIID riid
   , LPDWORD pdwConn)
   {
   HRESULT                hr;
   LPCONNECTIONPOINTCONTAINER pCPC;
   LPCONNECTIONPOINT         pCP;

   if (NULL==pObj || NULL==pdwConn)
      return FALSE;

   if (0==*pdwConn)
      return FALSE;

   hr=pObj->lpVtbl->QueryInterface(pObj, &IID_IConnectionPointContainer
      , (VOID **)&pCPC);
   
   if (FAILED(hr))
      return FALSE;

   hr=pCPC->lpVtbl->FindConnectionPoint(pCPC, riid, &pCP);

   if (SUCCEEDED(hr))
      {

      hr=pCP->lpVtbl->Unadvise(pCP, *pdwConn);

      if (SUCCEEDED(hr))
         *pdwConn=0L;

      pCP->lpVtbl->Release(pCP);
      }

   pCPC->lpVtbl->Release(pCPC);
   return SUCCEEDED(hr);
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
HRESULT forward_event(LPDISPATCH pThis,
                      DISPID  dispIdMember,  
                      DISPPARAMS FAR*  pDispParams,
                      VARIANT FAR*  pVarResult,  
                      EXCEPINFO FAR*  pExcepInfo,
                      unsigned int FAR*  puArgErr)
{
  EVENT_LISTENER *pEventListener;
  PCOMOBJ pObj;
  HRESULT hr = NOERROR;
  JNIEnv *env;
  jobject  jiid;
  jarray variantArray = NULL;
  unsigned int i;
  VARIANT *arg;
  jobject javaArg;
  
  pEventListener = (struct _EVENT_LISTENER FAR *) pThis;
  ASSERT(pEventListener->dwMagic == EVENT_LISTENER_MAGIC);
  
  pObj = pEventListener->pData;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  if (pVarResult != NULL)
    pVarResult = NULL;
  
  env = pObj->env;
  
  jiid = create_guid(env, pEventListener->iid);
  
  if (env == NULL) {
    dprintf(DERROR, "Error: could forward even to Java because I don't have a ");
    dprintf(DERROR, "pointer to the VM.");
    return E_FAIL;
  }
  
  if (pDispParams)
  {
    variantArray =  create_jvariant_array(env, pDispParams->cArgs);
      
    for (i = 0; i < pDispParams->cArgs; i++) {
      arg = (VARIANT *) &(pDispParams->rgvarg[i]);

      /* Note because of the current design we need an ActiveXProxy
         or we can not create java variants with objects here. Also we
         need a way to flag to indcate that we need to addref to any
         objects in the variant array because our parent did not,
         because we are being called, the rule is that if we
         want to keep the reference after the event is over we must
         call addref. */
      (*env)->SetObjectArrayElement(env, variantArray,
          (jsize) (pDispParams->cArgs - 1 - i),                                
          make_jobject_from_variant(env, *arg, NULL, TRUE)
      );
    }
  }

  hr = client_forward_event(pObj,
    jiid,
    dispIdMember,
    NULL,
    variantArray);
  
  /* Copy out the values from the Java Reference Parameters. */
  for (i = 0; i < pDispParams->cArgs; i++) {
    arg = (VARIANT *) &(pDispParams->rgvarg[i]);

    javaArg = (*env)->GetObjectArrayElement(env, variantArray,
                (jsize) (pDispParams->cArgs - 1 - i));
    CopyOutJavaRefParameter(env, *arg, javaArg, NULL);
  }

  return hr;
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
JNIEXPORT jboolean JNICALL Java_com_gensym_com_ActiveXProxy_property_1change_1listen
  (JNIEnv *env, jclass pThis, jint pObj_address, jstring pPropertyName, jboolean add)
{
  PCOMOBJ pObj;
    
  pObj = (PCOMOBJ) pObj_address;

  return JNI_TRUE;
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
JNIEXPORT jboolean JNICALL Java_com_gensym_com_ActiveXProxy_event_1listen
  (JNIEnv *env, jclass pThis, jint pObj_address, jint iunknown,
                jobject iid, jboolean add)
{
  PCOMOBJ pObj;
  EVENT_LISTENER *eventListener;
  EVENT_LISTENER *eventListenerPrevious;
  IUnknown *pUnk;  
  BOOL success;
  IID *pIid;

  pObj = (PCOMOBJ) pObj_address;
  pUnk = (IUnknown *) iunknown;

  pIid = (IID *) make_guid_from_java_guid(env, iid);
  
  if (add == JNI_TRUE) {
    eventListener = malloc(sizeof(EVENT_LISTENER));
    initialize_event_listener(eventListener, pObj);

    /* eventListener->jiid = (*env)->NewGlobalRef(env, iid); */
  
    /* Convert a java Guid to C IID */
    eventListener->iid = pIid;
  
    /* Now actually try to register this interface */  

    success = Connect(pUnk, eventListener->iid, 
                    (IUnknown*)eventListener, &(eventListener->dwConn));
  
    /* Adding this listener to the list for this object */
  
    if (!(pObj->event_listeners_tail)) {
      pObj->event_listeners_head = eventListener;
      pObj->event_listeners_tail = eventListener;
    } else {
      pObj->event_listeners_tail->next = eventListener;
      pObj->event_listeners_tail = eventListener;
    }
  }
  else {
    // Iterate until I find the same IID then
    // Disconnect and remove the listener

    eventListener = pObj->event_listeners_head;
    eventListenerPrevious = NULL;

    while(eventListener)
    {
      if (IsEqualIID(eventListener->iid,pIid))
      {
        // Disconnect the interface
        Disconnect(pUnk, eventListener->iid, 
                         &(eventListener->dwConn));
        
        // Remove the interace from the list of
        // interfaces
        if (eventListenerPrevious)
        {
          eventListenerPrevious->next = eventListener->next;
        }
        else {
           if (eventListener->next)
              pObj->event_listeners_head = eventListener->next;
        }
        break;    
      }
      eventListenerPrevious = eventListener;
      eventListener = eventListener->next;
    }
      
  }
  return JNI_TRUE;
}


#endif /* WIN32 */
