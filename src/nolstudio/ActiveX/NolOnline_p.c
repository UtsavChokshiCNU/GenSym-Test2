/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 28 08:09:38 2009
 */
/* Compiler settings for C:\G2\src\nolstudio\ActiveX\NolOnline.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "NolOnline.h"

#define TYPE_FORMAT_STRING_SIZE   1065                              
#define PROC_FORMAT_STRING_SIZE   2235                              

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: INolPredictor, ver. 0.0,
   GUID={0xCDE0EF5F,0x4E9A,0x11D4,{0xB8,0xA0,0x00,0x00,0x86,0x1E,0x03,0x89}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO INolPredictor_ServerInfo;

#pragma code_seg(".orpc")
/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_outputNames_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[784],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[784],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&index,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[784],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_outputTags_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[818],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[818],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&index,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[818],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_timeFormat_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[852],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[852],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[852],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_timeFormat_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,newVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[880],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[880],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&newVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[880],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_modelFullPath_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[908],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[908],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[908],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_modelFullPath_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,newVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[936],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[936],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&newVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[936],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_numberOfInputs_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[964],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[964],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[964],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_numberOfOutputs_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[992],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[992],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[992],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_loadOnRun_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1020],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1020],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1020],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_loadOnRun_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,newVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1048],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1048],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&newVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1048],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_trainModel_Proxy( 
    INolPredictor __RPC_FAR * This,
    VARIANT input,
    VARIANT output,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,display);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1076],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1076],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&input,
                  ( unsigned char __RPC_FAR * )&output,
                  ( unsigned char __RPC_FAR * )&timeInMinute,
                  ( unsigned char __RPC_FAR * )&autoStop,
                  ( unsigned char __RPC_FAR * )&newTraining,
                  ( unsigned char __RPC_FAR * )&display);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1076],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_trainModelFromFile_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR inputFileName,
    BSTR outputFileName,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,display);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1134],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1134],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&inputFileName,
                  ( unsigned char __RPC_FAR * )&outputFileName,
                  ( unsigned char __RPC_FAR * )&timeInMinute,
                  ( unsigned char __RPC_FAR * )&autoStop,
                  ( unsigned char __RPC_FAR * )&newTraining,
                  ( unsigned char __RPC_FAR * )&display);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1134],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_trainModelFromFiles_Proxy( 
    INolPredictor __RPC_FAR * This,
    VARIANT dataFileNames,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,display);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1192],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1192],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&dataFileNames,
                  ( unsigned char __RPC_FAR * )&timeInMinute,
                  ( unsigned char __RPC_FAR * )&autoStop,
                  ( unsigned char __RPC_FAR * )&newTraining,
                  ( unsigned char __RPC_FAR * )&display);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1192],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getModelRate_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1244],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1244],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1244],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTestRmse_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1272],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1272],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1272],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTrainingRmse_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1300],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1300],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1300],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTestCorr_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1328],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1328],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1328],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTrainingCorr_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1356],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1356],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1356],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_inputUnits_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1384],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1384],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&index,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1384],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_outputUnits_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1418],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1418],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&index,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1418],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setVariableValueAtTimeByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR Name,
    double val,
    BSTR Time)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,Time);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1452],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1452],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&Name,
                  ( unsigned char __RPC_FAR * )&val,
                  ( unsigned char __RPC_FAR * )&Time);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1452],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setVariableValueAtTimeByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR Tag,
    double val,
    BSTR Time)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,Time);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1492],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1492],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&Tag,
                  ( unsigned char __RPC_FAR * )&val,
                  ( unsigned char __RPC_FAR * )&Time);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1492],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMaxValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1532],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1532],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1532],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMaxValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1566],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1566],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1566],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMinValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1600],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1600],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1600],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMinValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1634],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1634],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1634],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMeanValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1668],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1668],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1668],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMeanValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1702],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1702],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1702],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMedianValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1736],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1736],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1736],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMedianValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1770],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1770],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1770],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSumValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1804],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1804],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1804],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSumValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1838],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1838],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1838],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSTDValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1872],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1872],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1872],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSTDValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1906],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1906],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1906],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getVarianceValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1940],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1940],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1940],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getVarianceValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1974],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1974],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1974],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getKurtValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2008],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2008],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2008],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getKurtValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2042],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2042],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2042],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSkewValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2076],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2076],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2076],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSkewValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2110],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2110],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2110],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getRangeValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2144],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2144],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&name,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2144],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getRangeValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pVal);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2178],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2178],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&tag,
                  ( unsigned char __RPC_FAR * )&pVal);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2178],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_clearDataBuffer_Proxy( 
    INolPredictor __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2212],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2212],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2212],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short INolPredictor_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    34,
    62,
    90,
    130,
    170,
    210,
    244,
    278,
    312,
    346,
    374,
    408,
    436,
    464,
    492,
    520,
    548,
    576,
    604,
    632,
    660,
    688,
    716,
    750,
    784,
    818,
    852,
    880,
    908,
    936,
    964,
    992,
    1020,
    1048,
    1076,
    1134,
    1192,
    1244,
    1272,
    1300,
    1328,
    1356,
    1384,
    1418,
    1452,
    1492,
    1532,
    1566,
    1600,
    1634,
    1668,
    1702,
    1736,
    1770,
    1804,
    1838,
    1872,
    1906,
    1940,
    1974,
    2008,
    2042,
    2076,
    2110,
    2144,
    2178,
    2212
    };

static const MIDL_SERVER_INFO INolPredictor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &INolPredictor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO INolPredictor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &INolPredictor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(75) _INolPredictorProxyVtbl = 
{
    &INolPredictor_ProxyInfo,
    &IID_INolPredictor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* INolPredictor::loadModel */ ,
    (void *)-1 /* INolPredictor::getNumberOfInputs */ ,
    (void *)-1 /* INolPredictor::getNumberOfOutputs */ ,
    (void *)-1 /* INolPredictor::setInputAtTimeByIndex */ ,
    (void *)-1 /* INolPredictor::setInputAtTimeByName */ ,
    (void *)-1 /* INolPredictor::setInputAtTimeByTag */ ,
    (void *)-1 /* INolPredictor::setInputForRowByIndex */ ,
    (void *)-1 /* INolPredictor::setInputForRowByName */ ,
    (void *)-1 /* INolPredictor::setInputForRowByTag */ ,
    (void *)-1 /* INolPredictor::setInputsAtTime */ ,
    (void *)-1 /* INolPredictor::setInputsForRow */ ,
    (void *)-1 /* INolPredictor::calculateOutputsAtTime */ ,
    (void *)-1 /* INolPredictor::calculateOutputsForRow */ ,
    (void *)-1 /* INolPredictor::setTimeFormat */ ,
    (void *)-1 /* INolPredictor::isTimeBasedModel */ ,
    (void *)-1 /* INolPredictor::get_modelComment */ ,
    (void *)-1 /* INolPredictor::put_modelComment */ ,
    (void *)-1 /* INolPredictor::get_modelFilePath */ ,
    (void *)-1 /* INolPredictor::put_modelFilePath */ ,
    (void *)-1 /* INolPredictor::get_modelFileName */ ,
    (void *)-1 /* INolPredictor::put_modelFileName */ ,
    (void *)-1 /* INolPredictor::get_modelName */ ,
    (void *)-1 /* INolPredictor::put_modelName */ ,
    (void *)-1 /* INolPredictor::get_inputNames */ ,
    (void *)-1 /* INolPredictor::get_inputTags */ ,
    INolPredictor_get_outputNames_Proxy ,
    INolPredictor_get_outputTags_Proxy ,
    INolPredictor_get_timeFormat_Proxy ,
    INolPredictor_put_timeFormat_Proxy ,
    INolPredictor_get_modelFullPath_Proxy ,
    INolPredictor_put_modelFullPath_Proxy ,
    INolPredictor_get_numberOfInputs_Proxy ,
    INolPredictor_get_numberOfOutputs_Proxy ,
    INolPredictor_get_loadOnRun_Proxy ,
    INolPredictor_put_loadOnRun_Proxy ,
    INolPredictor_trainModel_Proxy ,
    INolPredictor_trainModelFromFile_Proxy ,
    INolPredictor_trainModelFromFiles_Proxy ,
    INolPredictor_getModelRate_Proxy ,
    INolPredictor_getTestRmse_Proxy ,
    INolPredictor_getTrainingRmse_Proxy ,
    INolPredictor_getTestCorr_Proxy ,
    INolPredictor_getTrainingCorr_Proxy ,
    INolPredictor_get_inputUnits_Proxy ,
    INolPredictor_get_outputUnits_Proxy ,
    INolPredictor_setVariableValueAtTimeByName_Proxy ,
    INolPredictor_setVariableValueAtTimeByTag_Proxy ,
    INolPredictor_getMaxValueByName_Proxy ,
    INolPredictor_getMaxValueByTag_Proxy ,
    INolPredictor_getMinValueByName_Proxy ,
    INolPredictor_getMinValueByTag_Proxy ,
    INolPredictor_getMeanValueByName_Proxy ,
    INolPredictor_getMeanValueByTag_Proxy ,
    INolPredictor_getMedianValueByName_Proxy ,
    INolPredictor_getMedianValueByTag_Proxy ,
    INolPredictor_getSumValueByName_Proxy ,
    INolPredictor_getSumValueByTag_Proxy ,
    INolPredictor_getSTDValueByName_Proxy ,
    INolPredictor_getSTDValueByTag_Proxy ,
    INolPredictor_getVarianceValueByName_Proxy ,
    INolPredictor_getVarianceValueByTag_Proxy ,
    INolPredictor_getKurtValueByName_Proxy ,
    INolPredictor_getKurtValueByTag_Proxy ,
    INolPredictor_getSkewValueByName_Proxy ,
    INolPredictor_getSkewValueByTag_Proxy ,
    INolPredictor_getRangeValueByName_Proxy ,
    INolPredictor_getRangeValueByTag_Proxy ,
    INolPredictor_clearDataBuffer_Proxy
};


static const PRPC_STUB_FUNCTION INolPredictor_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _INolPredictorStubVtbl =
{
    &IID_INolPredictor,
    &INolPredictor_ServerInfo,
    75,
    &INolPredictor_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure loadModel */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter ModelFileName */

/* 16 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter ModelFilePath */

/* 22 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 28 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 30 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 32 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNumberOfInputs */

/* 34 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 42 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 44 */	NdrFcShort( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x10 ),	/* 16 */
/* 48 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 50 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 56 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 58 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 60 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getNumberOfOutputs */

/* 62 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 64 */	NdrFcLong( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 70 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 72 */	NdrFcShort( 0x0 ),	/* 0 */
/* 74 */	NdrFcShort( 0x10 ),	/* 16 */
/* 76 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 78 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 80 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 84 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputAtTimeByIndex */

/* 90 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 92 */	NdrFcLong( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 98 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 100 */	NdrFcShort( 0x18 ),	/* 24 */
/* 102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 104 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter Index */

/* 106 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 108 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter InputValue */

/* 112 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 114 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 116 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter Time */

/* 118 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 120 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 122 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 124 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 126 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputAtTimeByName */

/* 130 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 138 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 140 */	NdrFcShort( 0x10 ),	/* 16 */
/* 142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 144 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter Name */

/* 146 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 148 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 150 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter InputValue */

/* 152 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 154 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 156 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter Time */

/* 158 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 160 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 162 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 164 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 166 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 168 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputAtTimeByTag */

/* 170 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 172 */	NdrFcLong( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 178 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 180 */	NdrFcShort( 0x10 ),	/* 16 */
/* 182 */	NdrFcShort( 0x8 ),	/* 8 */
/* 184 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter Tag */

/* 186 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 188 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 190 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter InputValue */

/* 192 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 194 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 196 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter Time */

/* 198 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 200 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 202 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 204 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 206 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputForRowByIndex */

/* 210 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 212 */	NdrFcLong( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
/* 218 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 220 */	NdrFcShort( 0x18 ),	/* 24 */
/* 222 */	NdrFcShort( 0x8 ),	/* 8 */
/* 224 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 226 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 228 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 230 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter InputValue */

/* 232 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 234 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 236 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 238 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 240 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 242 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputForRowByName */

/* 244 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 246 */	NdrFcLong( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 252 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 254 */	NdrFcShort( 0x10 ),	/* 16 */
/* 256 */	NdrFcShort( 0x8 ),	/* 8 */
/* 258 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter InputName */

/* 260 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 262 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 264 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter InputValue */

/* 266 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 268 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 270 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 272 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 274 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 276 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputForRowByTag */

/* 278 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 280 */	NdrFcLong( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
/* 286 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 288 */	NdrFcShort( 0x10 ),	/* 16 */
/* 290 */	NdrFcShort( 0x8 ),	/* 8 */
/* 292 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Tag */

/* 294 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 296 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 298 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter InputValue */

/* 300 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 302 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 304 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 308 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputsAtTime */

/* 312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x10 ),	/* 16 */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 320 */	NdrFcShort( 0x1c ),	/* x86, MIPS Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x1c ),	/* MIPS Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 326 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Inputs */

/* 328 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 330 */	NdrFcShort( 0x4 ),	/* x86, MIPS Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x4 ),	/* MIPS Stack size/offset = 4 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 332 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter Time */

/* 334 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 336 */	NdrFcShort( 0x14 ),	/* x86, MIPS Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x14 ),	/* MIPS Stack size/offset = 20 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 338 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 340 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 342 */	NdrFcShort( 0x18 ),	/* x86, MIPS Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x18 ),	/* MIPS Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setInputsForRow */

/* 346 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x11 ),	/* 17 */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 354 */	NdrFcShort( 0x18 ),	/* x86, MIPS Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x18 ),	/* MIPS Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 358 */	NdrFcShort( 0x8 ),	/* 8 */
/* 360 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter Inputs */

/* 362 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 364 */	NdrFcShort( 0x4 ),	/* x86, MIPS Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x4 ),	/* MIPS Stack size/offset = 4 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 366 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Return value */

/* 368 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 370 */	NdrFcShort( 0x14 ),	/* x86, MIPS Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x14 ),	/* MIPS Stack size/offset = 20 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure calculateOutputsAtTime */

/* 374 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x12 ),	/* 18 */
#ifndef _ALPHA_
/* 382 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 388 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Time */

/* 390 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 392 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 394 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 396 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 398 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 400 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */

	/* Return value */

/* 402 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 404 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure calculateOutputsForRow */

/* 408 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 416 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 420 */	NdrFcShort( 0x8 ),	/* 8 */
/* 422 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 424 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 426 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 428 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */

	/* Return value */

/* 430 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 432 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setTimeFormat */

/* 436 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 438 */	NdrFcLong( 0x0 ),	/* 0 */
/* 442 */	NdrFcShort( 0x14 ),	/* 20 */
#ifndef _ALPHA_
/* 444 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 448 */	NdrFcShort( 0x8 ),	/* 8 */
/* 450 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 452 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 454 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 456 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 460 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure isTimeBasedModel */

/* 464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 470 */	NdrFcShort( 0x15 ),	/* 21 */
#ifndef _ALPHA_
/* 472 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 476 */	NdrFcShort( 0xe ),	/* 14 */
/* 478 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pbool */

/* 480 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 482 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 484 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 486 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 488 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_modelComment */

/* 492 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 494 */	NdrFcLong( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0x16 ),	/* 22 */
#ifndef _ALPHA_
/* 500 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x8 ),	/* 8 */
/* 506 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 508 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 510 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 512 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 514 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 516 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 518 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_modelComment */

/* 520 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 522 */	NdrFcLong( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0x17 ),	/* 23 */
#ifndef _ALPHA_
/* 528 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0x8 ),	/* 8 */
/* 534 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 536 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 538 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 540 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 542 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 544 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 546 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_modelFilePath */

/* 548 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 550 */	NdrFcLong( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x18 ),	/* 24 */
#ifndef _ALPHA_
/* 556 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	NdrFcShort( 0x8 ),	/* 8 */
/* 562 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 564 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 566 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 568 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 570 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 572 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_modelFilePath */

/* 576 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x19 ),	/* 25 */
#ifndef _ALPHA_
/* 584 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x8 ),	/* 8 */
/* 590 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 592 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 594 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 596 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 598 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 600 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_modelFileName */

/* 604 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 606 */	NdrFcLong( 0x0 ),	/* 0 */
/* 610 */	NdrFcShort( 0x1a ),	/* 26 */
#ifndef _ALPHA_
/* 612 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 618 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 620 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 622 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 624 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 628 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_modelFileName */

/* 632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 638 */	NdrFcShort( 0x1b ),	/* 27 */
#ifndef _ALPHA_
/* 640 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 646 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 648 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 650 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 652 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 654 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 656 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 658 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_modelName */

/* 660 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 662 */	NdrFcLong( 0x0 ),	/* 0 */
/* 666 */	NdrFcShort( 0x1c ),	/* 28 */
#ifndef _ALPHA_
/* 668 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0x8 ),	/* 8 */
/* 674 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 676 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 678 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 680 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 682 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 684 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 686 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_modelName */

/* 688 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 690 */	NdrFcLong( 0x0 ),	/* 0 */
/* 694 */	NdrFcShort( 0x1d ),	/* 29 */
#ifndef _ALPHA_
/* 696 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x8 ),	/* 8 */
/* 702 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 704 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 706 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 708 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 710 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 712 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 714 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_inputNames */

/* 716 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 718 */	NdrFcLong( 0x0 ),	/* 0 */
/* 722 */	NdrFcShort( 0x1e ),	/* 30 */
#ifndef _ALPHA_
/* 724 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 726 */	NdrFcShort( 0x6 ),	/* 6 */
/* 728 */	NdrFcShort( 0x8 ),	/* 8 */
/* 730 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 732 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 734 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 736 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 738 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 740 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 742 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 744 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 746 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_inputTags */

/* 750 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 752 */	NdrFcLong( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x1f ),	/* 31 */
#ifndef _ALPHA_
/* 758 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 760 */	NdrFcShort( 0x6 ),	/* 6 */
/* 762 */	NdrFcShort( 0x8 ),	/* 8 */
/* 764 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 766 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 768 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 770 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 772 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 774 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 776 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 778 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 780 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 782 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_outputNames */

/* 784 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 786 */	NdrFcLong( 0x0 ),	/* 0 */
/* 790 */	NdrFcShort( 0x20 ),	/* 32 */
#ifndef _ALPHA_
/* 792 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 794 */	NdrFcShort( 0x6 ),	/* 6 */
/* 796 */	NdrFcShort( 0x8 ),	/* 8 */
/* 798 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 800 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 802 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 804 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 806 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 808 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 810 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 812 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 814 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_outputTags */

/* 818 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 820 */	NdrFcLong( 0x0 ),	/* 0 */
/* 824 */	NdrFcShort( 0x21 ),	/* 33 */
#ifndef _ALPHA_
/* 826 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 828 */	NdrFcShort( 0x6 ),	/* 6 */
/* 830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 832 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 834 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 836 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 838 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 840 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 842 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 844 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 846 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 848 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 850 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_timeFormat */

/* 852 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 854 */	NdrFcLong( 0x0 ),	/* 0 */
/* 858 */	NdrFcShort( 0x22 ),	/* 34 */
#ifndef _ALPHA_
/* 860 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 866 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 868 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 870 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 872 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 874 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 876 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 878 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_timeFormat */

/* 880 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 882 */	NdrFcLong( 0x0 ),	/* 0 */
/* 886 */	NdrFcShort( 0x23 ),	/* 35 */
#ifndef _ALPHA_
/* 888 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 894 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 896 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 898 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 900 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 902 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 904 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 906 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_modelFullPath */

/* 908 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 910 */	NdrFcLong( 0x0 ),	/* 0 */
/* 914 */	NdrFcShort( 0x24 ),	/* 36 */
#ifndef _ALPHA_
/* 916 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 922 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 924 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 926 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 928 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 930 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 932 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_modelFullPath */

/* 936 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 938 */	NdrFcLong( 0x0 ),	/* 0 */
/* 942 */	NdrFcShort( 0x25 ),	/* 37 */
#ifndef _ALPHA_
/* 944 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x8 ),	/* 8 */
/* 950 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 952 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 954 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 956 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 958 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 960 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 962 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_numberOfInputs */

/* 964 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 966 */	NdrFcLong( 0x0 ),	/* 0 */
/* 970 */	NdrFcShort( 0x26 ),	/* 38 */
#ifndef _ALPHA_
/* 972 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 974 */	NdrFcShort( 0x0 ),	/* 0 */
/* 976 */	NdrFcShort( 0x10 ),	/* 16 */
/* 978 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 980 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 982 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 984 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 986 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 988 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 990 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_numberOfOutputs */

/* 992 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 994 */	NdrFcLong( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0x27 ),	/* 39 */
#ifndef _ALPHA_
/* 1000 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1002 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1004 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1006 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1008 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1010 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1014 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1016 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1018 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_loadOnRun */

/* 1020 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1022 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1026 */	NdrFcShort( 0x28 ),	/* 40 */
#ifndef _ALPHA_
/* 1028 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1032 */	NdrFcShort( 0xe ),	/* 14 */
/* 1034 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1036 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1038 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1040 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1042 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1044 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1046 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_loadOnRun */

/* 1048 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1050 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1054 */	NdrFcShort( 0x29 ),	/* 41 */
#ifndef _ALPHA_
/* 1056 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1058 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1060 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1062 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1064 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1066 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1068 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1070 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1072 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1074 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure trainModel */

/* 1076 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1078 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1082 */	NdrFcShort( 0x2a ),	/* 42 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1084 */	NdrFcShort( 0x3c ),	/* x86 Stack size/offset = 60 */
#else
			NdrFcShort( 0x40 ),	/* MIPS & PPC Stack size/offset = 64 */
#endif
#else
			NdrFcShort( 0x50 ),	/* Alpha Stack size/offset = 80 */
#endif
/* 1086 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1088 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1090 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x7,		/* 7 */

	/* Parameter input */

/* 1092 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 1094 */	NdrFcShort( 0x4 ),	/* x86, MIPS Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x4 ),	/* MIPS Stack size/offset = 4 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1096 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter output */

/* 1098 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 1100 */	NdrFcShort( 0x14 ),	/* x86, MIPS Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x14 ),	/* MIPS Stack size/offset = 20 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1102 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter timeInMinute */

/* 1104 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1106 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
#else
			NdrFcShort( 0x28 ),	/* MIPS & PPC Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1108 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter autoStop */

/* 1110 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1112 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
#else
			NdrFcShort( 0x30 ),	/* MIPS & PPC Stack size/offset = 48 */
#endif
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1114 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter newTraining */

/* 1116 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1118 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
#else
			NdrFcShort( 0x34 ),	/* MIPS & PPC Stack size/offset = 52 */
#endif
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1120 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter display */

/* 1122 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1124 */	NdrFcShort( 0x34 ),	/* x86 Stack size/offset = 52 */
#else
			NdrFcShort( 0x38 ),	/* MIPS & PPC Stack size/offset = 56 */
#endif
#else
			NdrFcShort( 0x40 ),	/* Alpha Stack size/offset = 64 */
#endif
/* 1126 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1128 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1130 */	NdrFcShort( 0x38 ),	/* x86 Stack size/offset = 56 */
#else
			NdrFcShort( 0x3c ),	/* MIPS & PPC Stack size/offset = 60 */
#endif
#else
			NdrFcShort( 0x48 ),	/* Alpha Stack size/offset = 72 */
#endif
/* 1132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure trainModelFromFile */

/* 1134 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1136 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x2b ),	/* 43 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1142 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
#else
			NdrFcShort( 0x28 ),	/* MIPS & PPC Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x40 ),	/* Alpha Stack size/offset = 64 */
#endif
/* 1144 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1148 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x7,		/* 7 */

	/* Parameter inputFileName */

/* 1150 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1152 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1154 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter outputFileName */

/* 1156 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1158 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1160 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter timeInMinute */

/* 1162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
#else
			NdrFcShort( 0x10 ),	/* MIPS & PPC Stack size/offset = 16 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1166 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter autoStop */

/* 1168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1170 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1172 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter newTraining */

/* 1174 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1176 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1178 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter display */

/* 1180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1182 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* MIPS & PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1184 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1186 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1188 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
#else
			NdrFcShort( 0x24 ),	/* MIPS & PPC Stack size/offset = 36 */
#endif
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure trainModelFromFiles */

/* 1192 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1194 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1198 */	NdrFcShort( 0x2c ),	/* 44 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1200 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
#else
			NdrFcShort( 0x30 ),	/* MIPS & PPC Stack size/offset = 48 */
#endif
#else
			NdrFcShort( 0x40 ),	/* Alpha Stack size/offset = 64 */
#endif
/* 1202 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1204 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1206 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x6,		/* 6 */

	/* Parameter dataFileNames */

/* 1208 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 1210 */	NdrFcShort( 0x4 ),	/* x86, MIPS Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x4 ),	/* MIPS Stack size/offset = 4 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1212 */	NdrFcShort( 0x3f2 ),	/* Type Offset=1010 */

	/* Parameter timeInMinute */

/* 1214 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1216 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1218 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter autoStop */

/* 1220 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1222 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* MIPS & PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1224 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter newTraining */

/* 1226 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1228 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
#else
			NdrFcShort( 0x24 ),	/* MIPS & PPC Stack size/offset = 36 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1230 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter display */

/* 1232 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1234 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
#else
			NdrFcShort( 0x28 ),	/* MIPS & PPC Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1236 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1238 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1240 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
#else
			NdrFcShort( 0x2c ),	/* MIPS & PPC Stack size/offset = 44 */
#endif
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1242 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getModelRate */

/* 1244 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1246 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1250 */	NdrFcShort( 0x2d ),	/* 45 */
#ifndef _ALPHA_
/* 1252 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1256 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1258 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1260 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1262 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1264 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1266 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1268 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1270 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getTestRmse */

/* 1272 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1274 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1278 */	NdrFcShort( 0x2e ),	/* 46 */
#ifndef _ALPHA_
/* 1280 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1284 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1286 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1288 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1290 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1292 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */

	/* Return value */

/* 1294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1296 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getTrainingRmse */

/* 1300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1306 */	NdrFcShort( 0x2f ),	/* 47 */
#ifndef _ALPHA_
/* 1308 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1314 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1316 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1318 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1320 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */

	/* Return value */

/* 1322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1324 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getTestCorr */

/* 1328 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1334 */	NdrFcShort( 0x30 ),	/* 48 */
#ifndef _ALPHA_
/* 1336 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1342 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1344 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1346 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1348 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */

	/* Return value */

/* 1350 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1352 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1354 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getTrainingCorr */

/* 1356 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1358 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1362 */	NdrFcShort( 0x31 ),	/* 49 */
#ifndef _ALPHA_
/* 1364 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1368 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1370 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1372 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
#ifndef _ALPHA_
/* 1374 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1376 */	NdrFcShort( 0x404 ),	/* Type Offset=1028 */

	/* Return value */

/* 1378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1380 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_inputUnits */

/* 1384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1390 */	NdrFcShort( 0x32 ),	/* 50 */
#ifndef _ALPHA_
/* 1392 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1394 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1396 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1398 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 1400 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1402 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1404 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1406 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1408 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1410 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1412 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1414 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_outputUnits */

/* 1418 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1420 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1424 */	NdrFcShort( 0x33 ),	/* 51 */
#ifndef _ALPHA_
/* 1426 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1428 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1432 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 1434 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1436 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1438 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1440 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1442 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1444 */	NdrFcShort( 0x41a ),	/* Type Offset=1050 */

	/* Return value */

/* 1446 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1448 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1450 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setVariableValueAtTimeByName */

/* 1452 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1454 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1458 */	NdrFcShort( 0x34 ),	/* 52 */
#ifndef _ALPHA_
/* 1460 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1462 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1464 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1466 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter Name */

/* 1468 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1470 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1472 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter val */

/* 1474 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1476 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1478 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter Time */

/* 1480 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1482 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1484 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 1486 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1488 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setVariableValueAtTimeByTag */

/* 1492 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1494 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1498 */	NdrFcShort( 0x35 ),	/* 53 */
#ifndef _ALPHA_
/* 1500 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1502 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1504 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1506 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter Tag */

/* 1508 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1510 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1512 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter val */

/* 1514 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1516 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1518 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter Time */

/* 1520 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1522 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1524 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Return value */

/* 1526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1528 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMaxValueByName */

/* 1532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1538 */	NdrFcShort( 0x36 ),	/* 54 */
#ifndef _ALPHA_
/* 1540 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1544 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1546 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1548 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1550 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1552 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1554 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1556 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1558 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1560 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1562 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMaxValueByTag */

/* 1566 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1568 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x37 ),	/* 55 */
#ifndef _ALPHA_
/* 1574 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1576 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1578 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1580 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1582 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1584 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1586 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1588 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1590 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1592 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1594 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1596 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMinValueByName */

/* 1600 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1602 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1606 */	NdrFcShort( 0x38 ),	/* 56 */
#ifndef _ALPHA_
/* 1608 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1612 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1614 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1616 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1618 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1620 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1622 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1624 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1626 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1628 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1630 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1632 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMinValueByTag */

/* 1634 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1636 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x39 ),	/* 57 */
#ifndef _ALPHA_
/* 1642 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1646 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1648 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1650 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1652 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1654 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1656 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1658 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1660 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1664 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMeanValueByName */

/* 1668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x3a ),	/* 58 */
#ifndef _ALPHA_
/* 1676 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1680 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1682 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1684 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1686 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1688 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1690 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1692 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1694 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1696 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1698 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1700 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMeanValueByTag */

/* 1702 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1704 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1708 */	NdrFcShort( 0x3b ),	/* 59 */
#ifndef _ALPHA_
/* 1710 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1714 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1716 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1718 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1720 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1722 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1724 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1726 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1728 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1730 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1732 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1734 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMedianValueByName */

/* 1736 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1738 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1742 */	NdrFcShort( 0x3c ),	/* 60 */
#ifndef _ALPHA_
/* 1744 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1748 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1750 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1752 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1754 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1756 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1758 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1760 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1762 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1764 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1766 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1768 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getMedianValueByTag */

/* 1770 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1772 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1776 */	NdrFcShort( 0x3d ),	/* 61 */
#ifndef _ALPHA_
/* 1778 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1782 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1784 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1786 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1788 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1790 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1792 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1794 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1796 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1798 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1800 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1802 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSumValueByName */

/* 1804 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1806 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1810 */	NdrFcShort( 0x3e ),	/* 62 */
#ifndef _ALPHA_
/* 1812 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1816 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1818 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1820 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1822 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1824 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1826 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1828 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1830 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1832 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1834 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1836 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSumValueByTag */

/* 1838 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1840 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1844 */	NdrFcShort( 0x3f ),	/* 63 */
#ifndef _ALPHA_
/* 1846 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1850 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1852 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1854 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1856 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1858 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1860 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1862 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1864 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1866 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1868 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1870 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSTDValueByName */

/* 1872 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1874 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1878 */	NdrFcShort( 0x40 ),	/* 64 */
#ifndef _ALPHA_
/* 1880 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1884 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1886 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1888 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1890 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1892 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1894 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1896 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1898 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1902 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSTDValueByTag */

/* 1906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1912 */	NdrFcShort( 0x41 ),	/* 65 */
#ifndef _ALPHA_
/* 1914 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1918 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1920 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1922 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1924 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1926 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1928 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1930 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1932 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1934 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1936 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1938 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getVarianceValueByName */

/* 1940 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1942 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1946 */	NdrFcShort( 0x42 ),	/* 66 */
#ifndef _ALPHA_
/* 1948 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1950 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1952 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1954 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 1956 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1958 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1960 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1962 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1964 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1966 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1968 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1970 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1972 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getVarianceValueByTag */

/* 1974 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1976 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1980 */	NdrFcShort( 0x43 ),	/* 67 */
#ifndef _ALPHA_
/* 1982 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1986 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1988 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 1990 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 1992 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1994 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 1996 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 1998 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2000 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2002 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2004 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getKurtValueByName */

/* 2008 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2010 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2014 */	NdrFcShort( 0x44 ),	/* 68 */
#ifndef _ALPHA_
/* 2016 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2020 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2022 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 2024 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 2026 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2028 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 2030 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2032 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2034 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2036 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2038 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2040 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getKurtValueByTag */

/* 2042 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2044 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2048 */	NdrFcShort( 0x45 ),	/* 69 */
#ifndef _ALPHA_
/* 2050 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2054 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2056 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 2058 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 2060 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2062 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 2064 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2066 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2068 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2070 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2072 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2074 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSkewValueByName */

/* 2076 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2078 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2082 */	NdrFcShort( 0x46 ),	/* 70 */
#ifndef _ALPHA_
/* 2084 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2086 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2088 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2090 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 2092 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 2094 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2096 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 2098 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2100 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2102 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2104 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2106 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSkewValueByTag */

/* 2110 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2112 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2116 */	NdrFcShort( 0x47 ),	/* 71 */
#ifndef _ALPHA_
/* 2118 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2122 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2124 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 2126 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 2128 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2130 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 2132 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2134 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2136 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2138 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2140 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getRangeValueByName */

/* 2144 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2146 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2150 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 2152 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2156 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2158 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 2160 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 2162 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2164 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 2166 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2168 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2170 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2174 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getRangeValueByTag */

/* 2178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2184 */	NdrFcShort( 0x49 ),	/* 73 */
#ifndef _ALPHA_
/* 2186 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2190 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2192 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter tag */

/* 2194 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 2196 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2198 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pVal */

/* 2200 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
#ifndef _ALPHA_
/* 2202 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2204 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2206 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2208 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure clearDataBuffer */

/* 2212 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2214 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2218 */	NdrFcShort( 0x4a ),	/* 74 */
#ifndef _ALPHA_
/* 2220 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2224 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2226 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 2228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2230 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xc ),	/* Offset= 12 (16) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 16 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 18 */	NdrFcShort( 0x8 ),	/* 8 */
/* 20 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (6) */
/* 22 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 24 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 38 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x12, 0x0,	/* FC_UP */
/* 42 */	NdrFcShort( 0x3b4 ),	/* Offset= 948 (990) */
/* 44 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 46 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 48 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 50 */	NdrFcShort( 0x2 ),	/* Offset= 2 (52) */
/* 52 */	NdrFcShort( 0x10 ),	/* 16 */
/* 54 */	NdrFcShort( 0x2f ),	/* 47 */
/* 56 */	NdrFcLong( 0x14 ),	/* 20 */
/* 60 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 62 */	NdrFcLong( 0x3 ),	/* 3 */
/* 66 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 68 */	NdrFcLong( 0x11 ),	/* 17 */
/* 72 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 74 */	NdrFcLong( 0x2 ),	/* 2 */
/* 78 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 80 */	NdrFcLong( 0x4 ),	/* 4 */
/* 84 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 86 */	NdrFcLong( 0x5 ),	/* 5 */
/* 90 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 92 */	NdrFcLong( 0xb ),	/* 11 */
/* 96 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 98 */	NdrFcLong( 0xa ),	/* 10 */
/* 102 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 104 */	NdrFcLong( 0x6 ),	/* 6 */
/* 108 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (340) */
/* 110 */	NdrFcLong( 0x7 ),	/* 7 */
/* 114 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 116 */	NdrFcLong( 0x8 ),	/* 8 */
/* 120 */	NdrFcShort( 0xffffff8a ),	/* Offset= -118 (2) */
/* 122 */	NdrFcLong( 0xd ),	/* 13 */
/* 126 */	NdrFcShort( 0xdc ),	/* Offset= 220 (346) */
/* 128 */	NdrFcLong( 0x9 ),	/* 9 */
/* 132 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (364) */
/* 134 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 138 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (382) */
/* 140 */	NdrFcLong( 0x24 ),	/* 36 */
/* 144 */	NdrFcShort( 0x302 ),	/* Offset= 770 (914) */
/* 146 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 150 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (914) */
/* 152 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 156 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (918) */
/* 158 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 162 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (922) */
/* 164 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 168 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (926) */
/* 170 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 174 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (930) */
/* 176 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 180 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (934) */
/* 182 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 186 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (938) */
/* 188 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 192 */	NdrFcShort( 0x2da ),	/* Offset= 730 (922) */
/* 194 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 198 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (926) */
/* 200 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 204 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (942) */
/* 206 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 210 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (938) */
/* 212 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 216 */	NdrFcShort( 0x2da ),	/* Offset= 730 (946) */
/* 218 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 222 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (950) */
/* 224 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 228 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (954) */
/* 230 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 234 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (958) */
/* 236 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 240 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (962) */
/* 242 */	NdrFcLong( 0x10 ),	/* 16 */
/* 246 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 248 */	NdrFcLong( 0x12 ),	/* 18 */
/* 252 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 254 */	NdrFcLong( 0x13 ),	/* 19 */
/* 258 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 260 */	NdrFcLong( 0x15 ),	/* 21 */
/* 264 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 266 */	NdrFcLong( 0x16 ),	/* 22 */
/* 270 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 272 */	NdrFcLong( 0x17 ),	/* 23 */
/* 276 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 278 */	NdrFcLong( 0xe ),	/* 14 */
/* 282 */	NdrFcShort( 0x2b0 ),	/* Offset= 688 (970) */
/* 284 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 288 */	NdrFcShort( 0x2b6 ),	/* Offset= 694 (982) */
/* 290 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 294 */	NdrFcShort( 0x2b4 ),	/* Offset= 692 (986) */
/* 296 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 300 */	NdrFcShort( 0x26e ),	/* Offset= 622 (922) */
/* 302 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 306 */	NdrFcShort( 0x26c ),	/* Offset= 620 (926) */
/* 308 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 312 */	NdrFcShort( 0x26a ),	/* Offset= 618 (930) */
/* 314 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 318 */	NdrFcShort( 0x260 ),	/* Offset= 608 (926) */
/* 320 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 324 */	NdrFcShort( 0x25a ),	/* Offset= 602 (926) */
/* 326 */	NdrFcLong( 0x0 ),	/* 0 */
/* 330 */	NdrFcShort( 0x0 ),	/* Offset= 0 (330) */
/* 332 */	NdrFcLong( 0x1 ),	/* 1 */
/* 336 */	NdrFcShort( 0x0 ),	/* Offset= 0 (336) */
/* 338 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (337) */
/* 340 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 344 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 346 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 356 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 358 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 360 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 362 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 364 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 366 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0x0 ),	/* 0 */
/* 374 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 376 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 378 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 380 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 382 */	
			0x12, 0x10,	/* FC_UP */
/* 384 */	NdrFcShort( 0x2 ),	/* Offset= 2 (386) */
/* 386 */	
			0x12, 0x0,	/* FC_UP */
/* 388 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (896) */
/* 390 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 392 */	NdrFcShort( 0x18 ),	/* 24 */
/* 394 */	NdrFcShort( 0xa ),	/* 10 */
/* 396 */	NdrFcLong( 0x8 ),	/* 8 */
/* 400 */	NdrFcShort( 0x58 ),	/* Offset= 88 (488) */
/* 402 */	NdrFcLong( 0xd ),	/* 13 */
/* 406 */	NdrFcShort( 0x78 ),	/* Offset= 120 (526) */
/* 408 */	NdrFcLong( 0x9 ),	/* 9 */
/* 412 */	NdrFcShort( 0x94 ),	/* Offset= 148 (560) */
/* 414 */	NdrFcLong( 0xc ),	/* 12 */
/* 418 */	NdrFcShort( 0xbc ),	/* Offset= 188 (606) */
/* 420 */	NdrFcLong( 0x24 ),	/* 36 */
/* 424 */	NdrFcShort( 0x114 ),	/* Offset= 276 (700) */
/* 426 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 430 */	NdrFcShort( 0x130 ),	/* Offset= 304 (734) */
/* 432 */	NdrFcLong( 0x10 ),	/* 16 */
/* 436 */	NdrFcShort( 0x148 ),	/* Offset= 328 (764) */
/* 438 */	NdrFcLong( 0x2 ),	/* 2 */
/* 442 */	NdrFcShort( 0x160 ),	/* Offset= 352 (794) */
/* 444 */	NdrFcLong( 0x3 ),	/* 3 */
/* 448 */	NdrFcShort( 0x178 ),	/* Offset= 376 (824) */
/* 450 */	NdrFcLong( 0x14 ),	/* 20 */
/* 454 */	NdrFcShort( 0x190 ),	/* Offset= 400 (854) */
/* 456 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (455) */
/* 458 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 460 */	NdrFcShort( 0x4 ),	/* 4 */
/* 462 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 468 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 470 */	NdrFcShort( 0x4 ),	/* 4 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	NdrFcShort( 0x1 ),	/* 1 */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 480 */	0x12, 0x0,	/* FC_UP */
/* 482 */	NdrFcShort( 0xfffffe2e ),	/* Offset= -466 (16) */
/* 484 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 486 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 488 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 490 */	NdrFcShort( 0x8 ),	/* 8 */
/* 492 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 494 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 496 */	NdrFcShort( 0x4 ),	/* 4 */
/* 498 */	NdrFcShort( 0x4 ),	/* 4 */
/* 500 */	0x11, 0x0,	/* FC_RP */
/* 502 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (458) */
/* 504 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 506 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 508 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 512 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 520 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 522 */	NdrFcShort( 0xffffff50 ),	/* Offset= -176 (346) */
/* 524 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 526 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 528 */	NdrFcShort( 0x8 ),	/* 8 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0x6 ),	/* Offset= 6 (538) */
/* 534 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 536 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 538 */	
			0x11, 0x0,	/* FC_RP */
/* 540 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (508) */
/* 542 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 554 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 556 */	NdrFcShort( 0xffffff40 ),	/* Offset= -192 (364) */
/* 558 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 560 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 562 */	NdrFcShort( 0x8 ),	/* 8 */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x6 ),	/* Offset= 6 (572) */
/* 568 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 570 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 572 */	
			0x11, 0x0,	/* FC_RP */
/* 574 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (542) */
/* 576 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 578 */	NdrFcShort( 0x4 ),	/* 4 */
/* 580 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 586 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 588 */	NdrFcShort( 0x4 ),	/* 4 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x1 ),	/* 1 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 598 */	0x12, 0x0,	/* FC_UP */
/* 600 */	NdrFcShort( 0xfffffda8 ),	/* Offset= -600 (0) */
/* 602 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 604 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 606 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 608 */	NdrFcShort( 0x8 ),	/* 8 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x6 ),	/* Offset= 6 (618) */
/* 614 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 616 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 618 */	
			0x11, 0x0,	/* FC_RP */
/* 620 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (576) */
/* 622 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 624 */	NdrFcLong( 0x2f ),	/* 47 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 634 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 636 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 638 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 640 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 642 */	NdrFcShort( 0x1 ),	/* 1 */
/* 644 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 650 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 652 */	NdrFcShort( 0x10 ),	/* 16 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0xa ),	/* Offset= 10 (666) */
/* 658 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 660 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 662 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (622) */
/* 664 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 666 */	
			0x12, 0x0,	/* FC_UP */
/* 668 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (640) */
/* 670 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 672 */	NdrFcShort( 0x4 ),	/* 4 */
/* 674 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 680 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 682 */	NdrFcShort( 0x4 ),	/* 4 */
/* 684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 686 */	NdrFcShort( 0x1 ),	/* 1 */
/* 688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 692 */	0x12, 0x0,	/* FC_UP */
/* 694 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (650) */
/* 696 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 698 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 700 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x6 ),	/* Offset= 6 (712) */
/* 708 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 710 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 712 */	
			0x11, 0x0,	/* FC_RP */
/* 714 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (670) */
/* 716 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 718 */	NdrFcShort( 0x8 ),	/* 8 */
/* 720 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 722 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 724 */	NdrFcShort( 0x10 ),	/* 16 */
/* 726 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 728 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 730 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (716) */
			0x5b,		/* FC_END */
/* 734 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 736 */	NdrFcShort( 0x18 ),	/* 24 */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0xa ),	/* Offset= 10 (750) */
/* 742 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 744 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 746 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (722) */
/* 748 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 750 */	
			0x11, 0x0,	/* FC_RP */
/* 752 */	NdrFcShort( 0xffffff0c ),	/* Offset= -244 (508) */
/* 754 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 756 */	NdrFcShort( 0x1 ),	/* 1 */
/* 758 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 764 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x8 ),	/* 8 */
/* 768 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 770 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 772 */	NdrFcShort( 0x4 ),	/* 4 */
/* 774 */	NdrFcShort( 0x4 ),	/* 4 */
/* 776 */	0x12, 0x0,	/* FC_UP */
/* 778 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (754) */
/* 780 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 782 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 784 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 786 */	NdrFcShort( 0x2 ),	/* 2 */
/* 788 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 792 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 794 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x8 ),	/* 8 */
/* 798 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 800 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 802 */	NdrFcShort( 0x4 ),	/* 4 */
/* 804 */	NdrFcShort( 0x4 ),	/* 4 */
/* 806 */	0x12, 0x0,	/* FC_UP */
/* 808 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (784) */
/* 810 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 812 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 814 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 816 */	NdrFcShort( 0x4 ),	/* 4 */
/* 818 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 824 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 826 */	NdrFcShort( 0x8 ),	/* 8 */
/* 828 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 830 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 832 */	NdrFcShort( 0x4 ),	/* 4 */
/* 834 */	NdrFcShort( 0x4 ),	/* 4 */
/* 836 */	0x12, 0x0,	/* FC_UP */
/* 838 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (814) */
/* 840 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 842 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 844 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 852 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 854 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 858 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 860 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 862 */	NdrFcShort( 0x4 ),	/* 4 */
/* 864 */	NdrFcShort( 0x4 ),	/* 4 */
/* 866 */	0x12, 0x0,	/* FC_UP */
/* 868 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (844) */
/* 870 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 872 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 874 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 878 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 880 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 882 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 886 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 888 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 890 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 892 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (874) */
/* 894 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 896 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 898 */	NdrFcShort( 0x28 ),	/* 40 */
/* 900 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (882) */
/* 902 */	NdrFcShort( 0x0 ),	/* Offset= 0 (902) */
/* 904 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 906 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 908 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 910 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf7 ),	/* Offset= -521 (390) */
			0x5b,		/* FC_END */
/* 914 */	
			0x12, 0x0,	/* FC_UP */
/* 916 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (650) */
/* 918 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 920 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 922 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 924 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 926 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 928 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 930 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 932 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 934 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 936 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 938 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 940 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 942 */	
			0x12, 0x0,	/* FC_UP */
/* 944 */	NdrFcShort( 0xfffffda4 ),	/* Offset= -604 (340) */
/* 946 */	
			0x12, 0x10,	/* FC_UP */
/* 948 */	NdrFcShort( 0xfffffc4e ),	/* Offset= -946 (2) */
/* 950 */	
			0x12, 0x10,	/* FC_UP */
/* 952 */	NdrFcShort( 0xfffffda2 ),	/* Offset= -606 (346) */
/* 954 */	
			0x12, 0x10,	/* FC_UP */
/* 956 */	NdrFcShort( 0xfffffdb0 ),	/* Offset= -592 (364) */
/* 958 */	
			0x12, 0x10,	/* FC_UP */
/* 960 */	NdrFcShort( 0xfffffdbe ),	/* Offset= -578 (382) */
/* 962 */	
			0x12, 0x10,	/* FC_UP */
/* 964 */	NdrFcShort( 0x2 ),	/* Offset= 2 (966) */
/* 966 */	
			0x12, 0x0,	/* FC_UP */
/* 968 */	NdrFcShort( 0xfffffc38 ),	/* Offset= -968 (0) */
/* 970 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 972 */	NdrFcShort( 0x10 ),	/* 16 */
/* 974 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 976 */	0x1,		/* FC_BYTE */
			0x38,		/* FC_ALIGNM4 */
/* 978 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 980 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 982 */	
			0x12, 0x0,	/* FC_UP */
/* 984 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (970) */
/* 986 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 988 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 990 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 992 */	NdrFcShort( 0x20 ),	/* 32 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 996 */	NdrFcShort( 0x0 ),	/* Offset= 0 (996) */
/* 998 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1000 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1002 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1004 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1006 */	NdrFcShort( 0xfffffc3e ),	/* Offset= -962 (44) */
/* 1008 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1010 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1012 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1014 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1018 */	NdrFcShort( 0xfffffc2e ),	/* Offset= -978 (40) */
/* 1020 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1022 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1028) */
/* 1024 */	
			0x13, 0x0,	/* FC_OP */
/* 1026 */	NdrFcShort( 0xffffffdc ),	/* Offset= -36 (990) */
/* 1028 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1030 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1032 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1024) */
/* 1038 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1040 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1042 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1044 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1050) */
/* 1046 */	
			0x13, 0x0,	/* FC_OP */
/* 1048 */	NdrFcShort( 0xfffffbf8 ),	/* Offset= -1032 (16) */
/* 1050 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1054 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1058 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1046) */
/* 1060 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1062 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _NolOnline_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INolPredictorProxyVtbl,
    0
};

const CInterfaceStubVtbl * _NolOnline_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INolPredictorStubVtbl,
    0
};

PCInterfaceName const _NolOnline_InterfaceNamesList[] = 
{
    "INolPredictor",
    0
};

const IID *  _NolOnline_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _NolOnline_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _NolOnline, pIID, n)

int __stdcall _NolOnline_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_NolOnline_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo NolOnline_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _NolOnline_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _NolOnline_StubVtblList,
    (const PCInterfaceName * ) & _NolOnline_InterfaceNamesList,
    (const IID ** ) & _NolOnline_BaseIIDList,
    & _NolOnline_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
