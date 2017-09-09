/*****************************************************************************
* dispatch.c
*
* Authors: John Valente, Allan Scott
*  
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "shared.h"
#include "dprintf.h"


#ifdef WIN32

#define AX_INVOKE 0
#define AX_PROPERTYGET 1
#define AX_PROPERTYSET 2


static DISPPARAMS dispparamsNoArgs = {
  NULL, 
  NULL, 
  0,
  0
};

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
void reclaim_dispparams(JNIEnv *env, jobject proxy, DISPPARAMS *pDisp)
{
  VARIANTARG *rgvarg;
  int cArgs,i;

  if (pDisp)
  {
    rgvarg = pDisp->rgvarg;

    cArgs = pDisp->cArgs;

    if (rgvarg)
    { 
      for (i = 0; i < cArgs; i++)
      {
        /* We only allocate a copy of the parameter value when we convert a
           string to a java string, so we should only free the strings.
           The dispatch interface and safe arrays will be referenced by
           java objects and should not be freed. */
        if (rgvarg[i].vt == VT_BSTR)
        {
          VariantClear(&(rgvarg[i]));
        }
        else if (rgvarg[i].vt & VT_BYREF)
        {
          CopyAndFreeNativeRefParameter(env, rgvarg[i], proxy);
        }
      }      
    }

    free(rgvarg);      
    free(pDisp);
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
DISPPARAMS *create_dispparams(JNIEnv *env, jobject args, jobject pThis)
{
  DISPPARAMS *result;
  jclass vectorClassPointer;
  jmethodID sizeMID, elementAtMID;
  jobject element;
  int size;
  int i = 0;
  VARIANTARG *pvarg = NULL;
  
  result = (DISPPARAMS *) malloc(sizeof(DISPPARAMS));
  result->cArgs = 0;
  result->rgvarg = NULL;
  result->cNamedArgs = 0;
  result->rgdispidNamedArgs = NULL;
  
  if (args == NULL) {
     return result;
  }

  vectorClassPointer = (*env)->GetObjectClass(env, args);
  sizeMID = (*env)->GetMethodID(env, vectorClassPointer, "size", "()I");
  if (sizeMID == NULL) {
    jprintf(env, DERROR, "Error: could not obtain method id");
    return result;
  }

  size = (*env)->CallIntMethod(env, args, sizeMID);
    
  if (size <= 0) {
    return result;
  }
    
  elementAtMID = (*env)->GetMethodID(env, vectorClassPointer,
	               "elementAt", "(I)Ljava/lang/Object;");
  if (elementAtMID == NULL) {
    jprintf(env, DERROR, "Error: could not obtain method id");
    return result;
  }
    
  result->cArgs = size;
  result->rgvarg = malloc(size * sizeof(VARIANTARG)); 
    
  jprintf(env, PROGRESS, "Converting %d dispparams", size);
    
  /* reverse the order of the arguments */
	for (i = (size - 1); i >= 0; i--) {
	  element = (*env)->CallObjectMethod(env, args, elementAtMID, i);

    pvarg = &(result->rgvarg[(size - 1) - i]);

    if (element == NULL) {
       /* VT_NULL is for null pointers not VT_DISPATCH */
       pvarg->vt = VT_NULL;
       pvarg->pdispVal = NULL;
       continue;
    }

    /* Store the java parameter to copy the output during reclaiming. */
    init_variant_from_jobject(env, element, pvarg, pThis, FALSE);
  }
    
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
LPDISPATCH get_dispatch_pointer(JNIEnv * env, LPDISPATCH pIDispatch, wchar_t *property_name)
{
    HRESULT hr;
    wchar_t *method_names[1];
    LPDISPATCH property;
    DISPID dispid;
    VARIANT varResult;
    
    if (!pIDispatch)
        return NULL;
    
    method_names[0] = property_name;
    hr = pIDispatch->lpVtbl->GetIDsOfNames(pIDispatch, &IID_NULL,
        method_names, 1, GetUserDefaultLCID(),
        &dispid);
    if (FAILED(hr)) {
        jprintf(env, DETAIL, "Query GetIDsOfNames for %ls failed, %x", method_names[0], hr);
        return NULL;
    }
    
    VariantInit(&varResult);
    jprintf(env, DETAIL, "Invoke the method %ls (dispid %x)", method_names[0], dispid);
    hr = pIDispatch->lpVtbl->Invoke(pIDispatch, dispid, &IID_NULL,
        GetUserDefaultLCID(), DISPATCH_PROPERTYGET,
        &dispparamsNoArgs, &varResult, NULL, NULL);
    if (FAILED(hr)) {
        jprintf(env, DETAIL, "Propertyget invoke call failed (%x)", hr);
        return NULL;
    }
    
    if (varResult.vt == VT_DISPATCH) {
        property = varResult.pdispVal;
        jprintf(env, DETAIL, "propertyget returned %x", property);
        jprintf(env, DETAIL, "propertyget returned vtbl %x", property->lpVtbl);
    } else {
        jprintf(env, DETAIL, "Error: wrong type argument returned from %ls (%x)",
            method_names[0], varResult.vt);
        VariantClear(&varResult);
        return NULL;
    }
    
    property->lpVtbl->AddRef(property);
    return property;
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
 static void throw_dispatch_exception(JNIEnv *env, 
                                      IDispatch *pIDispatch,
                                      long hr,
                                      EXCEPINFO *pExcept)
 {
   jclass activeXDispatchExceptionPointer;
   jmethodID exception_constructor;
   jclass excepinfoClass;
   jmethodID excepinfo_constructor;
   jobject exception;
   jobject excepinfo;

   if (env == NULL) {
     jprintf(env, DERROR, "Error: could not throw an exception because I don't have a ");
     jprintf(env, DERROR, "pointer to the VM.");
     }

   activeXDispatchExceptionPointer = (*env)->FindClass
 				(env, "com/gensym/com/ActiveXDispatchException");
   if (activeXDispatchExceptionPointer == NULL) {
     (*env)->ExceptionClear(env);
     jprintf(env, DERROR, "Could not find the class ActiveXDispatchExecption.");
     return;
   }
 
   if (hr == DISP_E_EXCEPTION) 
   {
     jprintf(env, DETAIL, "DISP_E_EXCEPTION - creating excepinfo");
     excepinfoClass =  (*env)->FindClass
 				(env, "com/gensym/com/Excepinfo");
  
     excepinfo_constructor = (*env)->GetMethodID(env, excepinfoClass,
 						   "<init>",
                "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;J)V");
 
     if (excepinfo_constructor != NULL)
     {
       jprintf(env, DETAIL, "Found excepinfo constructor");
       excepinfo = (*env)->NewObject
             (env, excepinfoClass, 
               excepinfo_constructor,
               (jlong) ((pExcept->wCode == 0 ? pExcept->scode : pExcept->wCode)
                        & 0xFFFFFFFF),   
               BSTR_to_jstring(env, pExcept->bstrSource),
               BSTR_to_jstring(env, pExcept->bstrDescription),
               BSTR_to_jstring(env, pExcept->bstrHelpFile),
               (jlong) (pExcept->dwHelpContext & 0xFFFFFFFF));
 
       jprintf(env, DETAIL, "Found exception constructor");
       exception_constructor = (*env)->GetMethodID(env, activeXDispatchExceptionPointer,
         "<init>",
         "(Lcom/gensym/com/Excepinfo;)V");
 
      exception =  (*env)->NewObject
       (env, activeXDispatchExceptionPointer, 
        exception_constructor, 
        excepinfo);
 
      if (exception)
      {
        jprintf(env, DETAIL, "About to throw the exception");
        (*env)->Throw(env, exception);
      }
 
      return;
     }
   }
  
   exception_constructor = (*env)->GetMethodID(env, activeXDispatchExceptionPointer,
     "<init>",
     "(Ljava/lang/String;J)V");
   
   if (exception_constructor != NULL)
   {
     jprintf(env, DETAIL, "Found exception constructor");
     exception =  (*env)->NewObject
       (env, activeXDispatchExceptionPointer, 
       exception_constructor, c_to_java_string(env, "Method dispatch failed"), 
       (jlong) (hr & 0xFFFFFFFF) );
       
     if (exception) 
     {
       jprintf(env, DETAIL, "About to throw the exception");
       (*env)->Throw(env, exception);      
     }
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
JNIEXPORT jobject JNICALL
Java_com_gensym_com_ActiveXProxy_com_1Invoke
    (JNIEnv *env, jobject pThis, jint pObj_address, jint hIDispatch, jint memid,
     jint dispatchType, jboolean voidReturn, jobject args)
{
  long hr;
  jobject return_value;
  IDispatch *pIDispatch;
  DISPID method_id;
  DISPPARAMS *method_args;
  VARIANT varResult;
  PCOMOBJ pObj;
  EXCEPINFO excepInfo;
  DISPID dispIDParam = DISPID_PROPERTYPUT;
  
  pObj = (PCOMOBJ) pObj_address;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);
  
  if (pObj->sOpenInWindow != TRUE) {
    jprintf(env, DERROR, "Cannot invoke method on an inactive object");
    return (jobject) NULL;
  }

  pIDispatch = (LPDISPATCH) hIDispatch;
  
  jprintf(env, PROGRESS, "inside invoke 0x%x", memid);
  method_id = (DISPID) memid;
  
  VariantInit(&varResult);
  jprintf(env, PROGRESS, "About to call method with memid 0x%x", method_id);
  jprintf(env, PROGRESS, "pIDispatch = 0x%x", pIDispatch);
  jprintf(env, PROGRESS, "dispatchType = 0x%x", dispatchType);
  jprintf(env, PROGRESS, "voidReturn = %s", (voidReturn ? "true" : "false"));
  
  switch (dispatchType) {
  case AX_INVOKE:
    method_args = create_dispparams(env, args, pThis);
    if (! method_args)
      break;


    jprintf(env, PROGRESS, "created dispparams for method invoke");
    hr = pIDispatch->lpVtbl->Invoke(pIDispatch, method_id, &IID_NULL,
           LOCALE_USER_DEFAULT, DISPATCH_METHOD,
           method_args, &varResult, &excepInfo, NULL);

    /* force an empty variant */
    if (voidReturn == JNI_TRUE)
      VariantClear(&varResult);

    break;              
      
  case AX_PROPERTYGET:
    method_args = create_dispparams(env, args, pThis);
    if (! method_args)
      break;

    jprintf(env, PROGRESS, "created dispparams for property get");
    hr = pIDispatch->lpVtbl->Invoke(pIDispatch, 
           method_id, &IID_NULL,
           LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET,
           method_args, &varResult, &excepInfo, NULL);
    break;              
      
  case AX_PROPERTYSET:
    method_args = create_dispparams(env, args, pThis);
    if (! method_args)
      break;

    method_args->cNamedArgs = 1;
    method_args->rgdispidNamedArgs = &dispIDParam;
    jprintf(env, PROGRESS, "created dispparams for property set");

    hr = pIDispatch->lpVtbl->Invoke(pIDispatch, 
           method_id, &IID_NULL,
           LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT,
           method_args, NULL, &excepInfo, NULL);
         break;              
  }
    
  jprintf(env, DETAIL, "Completed invoke.  hr = 0x%x", hr);
  if (FAILED(hr) && (hr != 0xc0000005L)) {  
    jprintf(env, DETAIL, "Attempting to throw exception");
    throw_dispatch_exception(env, pIDispatch, hr, &excepInfo);
    return NULL;
  }

  return_value = make_jobject_from_variant(env, varResult, pThis, FALSE);
  /* We only allocate a copy of the return value when we convert a
     string to a java string, so we should only free the strings.
     The dispatch interface and safe arrays will be referenced by
     java objects and should not be freed. */
  if (varResult.vt == VT_BSTR)
    VariantClear(&varResult);

  reclaim_dispparams(env, pThis, method_args); 

  return return_value;
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
JNIEXPORT jobject JNICALL
Java_com_gensym_com_ActiveXProxy_com_1Invoke_1by_1name
    (JNIEnv *env, jobject pThis, jint pObj_address, jint hIDispatch,
     jstring jmethod_name, jint dispatchType, jboolean voidReturn,
     jobject args)
{
    DISPID method_id;
    WCHAR *method_names[1];
    IDispatch *pIDispatch = (IDispatch *) hIDispatch;
    HRESULT hr;

    method_names[0] = java_to_unicode_string(env, jmethod_name);
    hr = pIDispatch->lpVtbl->GetIDsOfNames(pIDispatch, &IID_NULL,
                                           method_names, 1, 
					   LOCALE_USER_DEFAULT, &method_id);
    if (FAILED(hr)) {
	jprintf(env, DERROR,
                "Unable to obtain memid for %ls", method_names[0]);
	return NULL;
    }

    jprintf(env, DETAIL, "About to try to call %ls, memid 0x%x",
	    method_names[0], method_id);
    free(method_names[0]);
    return Java_com_gensym_com_ActiveXProxy_com_1Invoke
	(env, pThis, pObj_address, hIDispatch, method_id, dispatchType,
         voidReturn, args);
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
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_marshal_1interface
    (JNIEnv *env, jobject pThis, jint pObj_address, jint hIDispatch)
{
  HRESULT hr;
  IDispatch *pDispatch;
  IStream *pStream;

  if (hIDispatch == 0)
    return 0;
  
  pDispatch = (LPDISPATCH) hIDispatch;
  
  hr = CoMarshalInterThreadInterfaceInStream(
            &IID_IDispatch,
            (IUnknown *) pDispatch,
            &pStream);

  if (hr != S_OK)
  {
    printf("Attempt to marshal interface failed hIDispatch = 0x%08.8X\n",
      hIDispatch);
    return 0;
  }

  return (jint) pStream;
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
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_get_1marshaled_1interface
    (JNIEnv *env, jobject pThis, jint pObj_address, jint hIStream)
{
 
  HRESULT hr;
  IStream *pStream;
  IDispatch *pDispatch;

  pStream = (IStream *) hIStream;
  if (hIStream == 0)
    return 0;
  
  hr = CoGetInterfaceAndReleaseStream(pStream,
                                      &IID_IDispatch,
                                      (LPVOID *) &pDispatch);

  if (hr != S_OK)
  {
    printf("Attempt to get marshaled interface failed, hIStream = 0x08.8X\n",
      hIStream);
    return 0;
  }
   
  return (jint) pDispatch;
}
  
#endif /* WIN32 */
