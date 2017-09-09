

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed Nov 25 14:29:18 2009
 */
/* Compiler settings for .\PITimeServer.idl:
    Oicf, W2, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __PITimeServer_h__
#define __PITimeServer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DeviceTimeZones_FWD_DEFINED__
#define ___DeviceTimeZones_FWD_DEFINED__
typedef interface _DeviceTimeZones _DeviceTimeZones;
#endif 	/* ___DeviceTimeZones_FWD_DEFINED__ */


#ifndef __IClockSource_FWD_DEFINED__
#define __IClockSource_FWD_DEFINED__
typedef interface IClockSource IClockSource;
#endif 	/* __IClockSource_FWD_DEFINED__ */


#ifndef ___PITime_FWD_DEFINED__
#define ___PITime_FWD_DEFINED__
typedef interface _PITime _PITime;
#endif 	/* ___PITime_FWD_DEFINED__ */


#ifndef ___PITimeFormat_FWD_DEFINED__
#define ___PITimeFormat_FWD_DEFINED__
typedef interface _PITimeFormat _PITimeFormat;
#endif 	/* ___PITimeFormat_FWD_DEFINED__ */


#ifndef ___DynamicTime_FWD_DEFINED__
#define ___DynamicTime_FWD_DEFINED__
typedef interface _DynamicTime _DynamicTime;
#endif 	/* ___DynamicTime_FWD_DEFINED__ */


#ifndef __PITimeZoneInfo_FWD_DEFINED__
#define __PITimeZoneInfo_FWD_DEFINED__
typedef interface PITimeZoneInfo PITimeZoneInfo;
#endif 	/* __PITimeZoneInfo_FWD_DEFINED__ */


#ifndef ___PITimeZoneInfos_FWD_DEFINED__
#define ___PITimeZoneInfos_FWD_DEFINED__
typedef interface _PITimeZoneInfos _PITimeZoneInfos;
#endif 	/* ___PITimeZoneInfos_FWD_DEFINED__ */


#ifndef ___PITimeZoneRule_FWD_DEFINED__
#define ___PITimeZoneRule_FWD_DEFINED__
typedef interface _PITimeZoneRule _PITimeZoneRule;
#endif 	/* ___PITimeZoneRule_FWD_DEFINED__ */


#ifndef __ITimeInterval_FWD_DEFINED__
#define __ITimeInterval_FWD_DEFINED__
typedef interface ITimeInterval ITimeInterval;
#endif 	/* __ITimeInterval_FWD_DEFINED__ */


#ifndef ___PITimeRestorer_FWD_DEFINED__
#define ___PITimeRestorer_FWD_DEFINED__
typedef interface _PITimeRestorer _PITimeRestorer;
#endif 	/* ___PITimeRestorer_FWD_DEFINED__ */


#ifndef ___PITimeZoneInfoRestorer_FWD_DEFINED__
#define ___PITimeZoneInfoRestorer_FWD_DEFINED__
typedef interface _PITimeZoneInfoRestorer _PITimeZoneInfoRestorer;
#endif 	/* ___PITimeZoneInfoRestorer_FWD_DEFINED__ */


#ifndef ___PITimeZoneRuleRestorer_FWD_DEFINED__
#define ___PITimeZoneRuleRestorer_FWD_DEFINED__
typedef interface _PITimeZoneRuleRestorer _PITimeZoneRuleRestorer;
#endif 	/* ___PITimeZoneRuleRestorer_FWD_DEFINED__ */


#ifndef ___PITimeFormatRestorer_FWD_DEFINED__
#define ___PITimeFormatRestorer_FWD_DEFINED__
typedef interface _PITimeFormatRestorer _PITimeFormatRestorer;
#endif 	/* ___PITimeFormatRestorer_FWD_DEFINED__ */


#ifndef ___DynamicTimeRestorer_FWD_DEFINED__
#define ___DynamicTimeRestorer_FWD_DEFINED__
typedef interface _DynamicTimeRestorer _DynamicTimeRestorer;
#endif 	/* ___DynamicTimeRestorer_FWD_DEFINED__ */


#ifndef __PITime_FWD_DEFINED__
#define __PITime_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITime PITime;
#else
typedef struct PITime PITime;
#endif /* __cplusplus */

#endif 	/* __PITime_FWD_DEFINED__ */


#ifndef __PITimeFormat_FWD_DEFINED__
#define __PITimeFormat_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeFormat PITimeFormat;
#else
typedef struct PITimeFormat PITimeFormat;
#endif /* __cplusplus */

#endif 	/* __PITimeFormat_FWD_DEFINED__ */


#ifndef __PITimeZoneInfos_FWD_DEFINED__
#define __PITimeZoneInfos_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeZoneInfos PITimeZoneInfos;
#else
typedef struct PITimeZoneInfos PITimeZoneInfos;
#endif /* __cplusplus */

#endif 	/* __PITimeZoneInfos_FWD_DEFINED__ */


#ifndef __PITimeZoneRule_FWD_DEFINED__
#define __PITimeZoneRule_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeZoneRule PITimeZoneRule;
#else
typedef struct PITimeZoneRule PITimeZoneRule;
#endif /* __cplusplus */

#endif 	/* __PITimeZoneRule_FWD_DEFINED__ */


#ifndef __DeviceTimeZones_FWD_DEFINED__
#define __DeviceTimeZones_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeviceTimeZones DeviceTimeZones;
#else
typedef struct DeviceTimeZones DeviceTimeZones;
#endif /* __cplusplus */

#endif 	/* __DeviceTimeZones_FWD_DEFINED__ */


#ifndef __DynamicTime_FWD_DEFINED__
#define __DynamicTime_FWD_DEFINED__

#ifdef __cplusplus
typedef class DynamicTime DynamicTime;
#else
typedef struct DynamicTime DynamicTime;
#endif /* __cplusplus */

#endif 	/* __DynamicTime_FWD_DEFINED__ */


#ifndef ___TimeIntervals_FWD_DEFINED__
#define ___TimeIntervals_FWD_DEFINED__
typedef interface _TimeIntervals _TimeIntervals;
#endif 	/* ___TimeIntervals_FWD_DEFINED__ */


#ifndef __ITimeIntervals2_FWD_DEFINED__
#define __ITimeIntervals2_FWD_DEFINED__
typedef interface ITimeIntervals2 ITimeIntervals2;
#endif 	/* __ITimeIntervals2_FWD_DEFINED__ */


#ifndef __TimeIntervals_FWD_DEFINED__
#define __TimeIntervals_FWD_DEFINED__

#ifdef __cplusplus
typedef class TimeIntervals TimeIntervals;
#else
typedef struct TimeIntervals TimeIntervals;
#endif /* __cplusplus */

#endif 	/* __TimeIntervals_FWD_DEFINED__ */


#ifndef __ITimeIntervals_FWD_DEFINED__
#define __ITimeIntervals_FWD_DEFINED__
typedef interface ITimeIntervals ITimeIntervals;
#endif 	/* __ITimeIntervals_FWD_DEFINED__ */


#ifndef __PITimeRestorer_FWD_DEFINED__
#define __PITimeRestorer_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeRestorer PITimeRestorer;
#else
typedef struct PITimeRestorer PITimeRestorer;
#endif /* __cplusplus */

#endif 	/* __PITimeRestorer_FWD_DEFINED__ */


#ifndef __PITimeZoneInfoRestorer_FWD_DEFINED__
#define __PITimeZoneInfoRestorer_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeZoneInfoRestorer PITimeZoneInfoRestorer;
#else
typedef struct PITimeZoneInfoRestorer PITimeZoneInfoRestorer;
#endif /* __cplusplus */

#endif 	/* __PITimeZoneInfoRestorer_FWD_DEFINED__ */


#ifndef __PITimeZoneRuleRestorer_FWD_DEFINED__
#define __PITimeZoneRuleRestorer_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeZoneRuleRestorer PITimeZoneRuleRestorer;
#else
typedef struct PITimeZoneRuleRestorer PITimeZoneRuleRestorer;
#endif /* __cplusplus */

#endif 	/* __PITimeZoneRuleRestorer_FWD_DEFINED__ */


#ifndef __PITimeFormatRestorer_FWD_DEFINED__
#define __PITimeFormatRestorer_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeFormatRestorer PITimeFormatRestorer;
#else
typedef struct PITimeFormatRestorer PITimeFormatRestorer;
#endif /* __cplusplus */

#endif 	/* __PITimeFormatRestorer_FWD_DEFINED__ */


#ifndef __DynamicTimeRestorer_FWD_DEFINED__
#define __DynamicTimeRestorer_FWD_DEFINED__

#ifdef __cplusplus
typedef class DynamicTimeRestorer DynamicTimeRestorer;
#else
typedef struct DynamicTimeRestorer DynamicTimeRestorer;
#endif /* __cplusplus */

#endif 	/* __DynamicTimeRestorer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_PITimeServer_0000 */
/* [local] */ 

#pragma once










extern RPC_IF_HANDLE __MIDL_itf_PITimeServer_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PITimeServer_0000_v0_0_s_ifspec;


#ifndef __PITimeServer_LIBRARY_DEFINED__
#define __PITimeServer_LIBRARY_DEFINED__

/* library PITimeServer */
/* [version][helpstring][helpfile][uuid] */ 

typedef /* [helpstring] */ 
enum TSErrorConstants
    {	tseMUSTBEEMPTY	= 0x80040420,
	tseDUPLICATENAME	= 0x80040421,
	tseNAMENOTFOUND	= 0x80040422,
	tseOUTOFRANGE	= 0x80040423,
	tseNOEMPTYSTRINGS	= 0x800404af,
	tseALLOCBSTR	= 0x80040618,
	tseALLOCSAFEARRAY	= 0x80040619,
	tseALLOCENUMVARIANT	= 0x80040620,
	tseALLOCVARIANT	= 0x80040621,
	tseTIMEINVALID	= 0x8004a100,
	tseTIMEGETCOMP	= 0x8004a101,
	tseTIMEFILETIME	= 0x8004a102,
	tseDATEOUTOFRANGE	= 0x8004a108,
	tseMEMBERNOTFOUND	= 0x8004a109,
	tseORDNOTFOUND	= 0x8004a10a,
	tseINVALIDARG	= 0x8004a10c,
	tseINUSE	= 0x8004a110,
	tseCANTGETUID	= 0x8004a111,
	tseREGERROR	= 0x8004a112,
	tseNOTREMOVEDFROMLIST	= 0x8004a113,
	tseCREATORNAME	= 0x8004a114,
	tseTZQIFAILED	= 0x8004a115,
	tseINVALIDTZFILE	= 0x8004a116,
	tseFILEOPEN	= 0x8004a117,
	tseMDBUNPASSIVATEINTERNALERROR	= 0x8004a119,
	tseMDBUNPASSIVATEVERSIONNBRERROR	= 0x8004a11a,
	tsePERSISTOBJECT	= 0x8004a11b,
	tseRESTORESERVERS	= 0x8004a11c,
	tseRESTOREOBJECT	= 0x8004a11d,
	tseTIMEPARSERINIT	= 0x8004a11e,
	tseTZNOTSET	= 0x8004a11f,
	tseCREATEPITIME	= 0x8004a120,
	tseNOREFTIME	= 0x8004a121,
	tseCREATEINTERVALSRV	= 0x8004a122,
	tseFRACTIONSNOTALLOWED	= 0x8004a123,
	tseCHARNOTALLOWED	= 0x8004a124,
	tseINVALIDFORMAT	= 0x8004a125,
	tseGETOBJSERVERS	= 0x8004060a,
	tseINCOMPLETEINTERVAL	= 0x8004a126,
	tseEXTRACHARACTERS	= 0x8004a127
    } 	TSErrorConstants;


EXTERN_C const IID LIBID_PITimeServer;

#ifndef ___DeviceTimeZones_INTERFACE_DEFINED__
#define ___DeviceTimeZones_INTERFACE_DEFINED__

/* interface _DeviceTimeZones */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__DeviceTimeZones;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4507ED2-D021-11d3-853D-00C04F45D1DA")
    _DeviceTimeZones : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR DeviceName,
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR DeviceName,
            /* [in] */ BSTR ZoneID,
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR DeviceName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DeviceTimeZonesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DeviceTimeZones * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DeviceTimeZones * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DeviceTimeZones * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DeviceTimeZones * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DeviceTimeZones * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DeviceTimeZones * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DeviceTimeZones * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            _DeviceTimeZones * This,
            /* [in] */ BSTR DeviceName,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            _DeviceTimeZones * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            _DeviceTimeZones * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            _DeviceTimeZones * This,
            /* [in] */ BSTR DeviceName,
            /* [in] */ BSTR ZoneID,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            _DeviceTimeZones * This,
            /* [in] */ BSTR DeviceName);
        
        END_INTERFACE
    } _DeviceTimeZonesVtbl;

    interface _DeviceTimeZones
    {
        CONST_VTBL struct _DeviceTimeZonesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DeviceTimeZones_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DeviceTimeZones_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DeviceTimeZones_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DeviceTimeZones_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DeviceTimeZones_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DeviceTimeZones_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DeviceTimeZones_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _DeviceTimeZones_get_Item(This,DeviceName,pVal)	\
    (This)->lpVtbl -> get_Item(This,DeviceName,pVal)

#define _DeviceTimeZones_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _DeviceTimeZones_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _DeviceTimeZones_Add(This,DeviceName,ZoneID,pVal)	\
    (This)->lpVtbl -> Add(This,DeviceName,ZoneID,pVal)

#define _DeviceTimeZones_Remove(This,DeviceName)	\
    (This)->lpVtbl -> Remove(This,DeviceName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_get_Item_Proxy( 
    _DeviceTimeZones * This,
    /* [in] */ BSTR DeviceName,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB _DeviceTimeZones_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_get__NewEnum_Proxy( 
    _DeviceTimeZones * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB _DeviceTimeZones_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_get_Count_Proxy( 
    _DeviceTimeZones * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _DeviceTimeZones_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_Add_Proxy( 
    _DeviceTimeZones * This,
    /* [in] */ BSTR DeviceName,
    /* [in] */ BSTR ZoneID,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB _DeviceTimeZones_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_Remove_Proxy( 
    _DeviceTimeZones * This,
    /* [in] */ BSTR DeviceName);


void __RPC_STUB _DeviceTimeZones_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DeviceTimeZones_INTERFACE_DEFINED__ */


#ifndef __IClockSource_INTERFACE_DEFINED__
#define __IClockSource_INTERFACE_DEFINED__

/* interface IClockSource */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IClockSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7F3F8C1-CA24-11d3-BDC2-00C04F779EB2")
    IClockSource : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCSeconds( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeZoneInfo( 
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClockSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IClockSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IClockSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IClockSource * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCSeconds )( 
            IClockSource * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeZoneInfo )( 
            IClockSource * This,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IClockSource * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IClockSource * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IClockSourceVtbl;

    interface IClockSource
    {
        CONST_VTBL struct IClockSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClockSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClockSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClockSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClockSource_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define IClockSource_get_TimeZoneInfo(This,pVal)	\
    (This)->lpVtbl -> get_TimeZoneInfo(This,pVal)

#define IClockSource_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IClockSource_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_UTCSeconds_Proxy( 
    IClockSource * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IClockSource_get_UTCSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_TimeZoneInfo_Proxy( 
    IClockSource * This,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB IClockSource_get_TimeZoneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_Name_Proxy( 
    IClockSource * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IClockSource_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_Description_Proxy( 
    IClockSource * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IClockSource_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClockSource_INTERFACE_DEFINED__ */


#ifndef ___PITime_INTERFACE_DEFINED__
#define ___PITime_INTERFACE_DEFINED__

/* interface _PITime */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITime;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("626F6911-CA37-11d3-BDC2-00C04F779EB2")
    _PITime : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCSeconds( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_UTCSeconds( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalDate( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetToCurrent( void) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCFileTime( 
            /* [retval][out] */ CURRENCY *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_UTCFileTime( 
            /* [in] */ CURRENCY newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ _PITime **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITime * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITime * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITime * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITime * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITime * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITime * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITime * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCSeconds )( 
            _PITime * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UTCSeconds )( 
            _PITime * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalDate )( 
            _PITime * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalDate )( 
            _PITime * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *SetToCurrent )( 
            _PITime * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCFileTime )( 
            _PITime * This,
            /* [retval][out] */ CURRENCY *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UTCFileTime )( 
            _PITime * This,
            /* [in] */ CURRENCY newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            _PITime * This,
            /* [retval][out] */ _PITime **pVal);
        
        END_INTERFACE
    } _PITimeVtbl;

    interface _PITime
    {
        CONST_VTBL struct _PITimeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITime_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITime_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITime_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITime_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITime_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITime_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITime_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITime_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define _PITime_put_UTCSeconds(This,newVal)	\
    (This)->lpVtbl -> put_UTCSeconds(This,newVal)

#define _PITime_get_LocalDate(This,pVal)	\
    (This)->lpVtbl -> get_LocalDate(This,pVal)

#define _PITime_put_LocalDate(This,newVal)	\
    (This)->lpVtbl -> put_LocalDate(This,newVal)

#define _PITime_SetToCurrent(This)	\
    (This)->lpVtbl -> SetToCurrent(This)

#define _PITime_get_UTCFileTime(This,pVal)	\
    (This)->lpVtbl -> get_UTCFileTime(This,pVal)

#define _PITime_put_UTCFileTime(This,newVal)	\
    (This)->lpVtbl -> put_UTCFileTime(This,newVal)

#define _PITime_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITime_get_UTCSeconds_Proxy( 
    _PITime * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB _PITime_get_UTCSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITime_put_UTCSeconds_Proxy( 
    _PITime * This,
    /* [in] */ double newVal);


void __RPC_STUB _PITime_put_UTCSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITime_get_LocalDate_Proxy( 
    _PITime * This,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB _PITime_get_LocalDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITime_put_LocalDate_Proxy( 
    _PITime * This,
    /* [in] */ DATE newVal);


void __RPC_STUB _PITime_put_LocalDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITime_SetToCurrent_Proxy( 
    _PITime * This);


void __RPC_STUB _PITime_SetToCurrent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITime_get_UTCFileTime_Proxy( 
    _PITime * This,
    /* [retval][out] */ CURRENCY *pVal);


void __RPC_STUB _PITime_get_UTCFileTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITime_put_UTCFileTime_Proxy( 
    _PITime * This,
    /* [in] */ CURRENCY newVal);


void __RPC_STUB _PITime_put_UTCFileTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITime_Clone_Proxy( 
    _PITime * This,
    /* [retval][out] */ _PITime **pVal);


void __RPC_STUB _PITime_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITime_INTERFACE_DEFINED__ */


#ifndef ___PITimeFormat_INTERFACE_DEFINED__
#define ___PITimeFormat_INTERFACE_DEFINED__

/* interface _PITimeFormat */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeFormat;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB149699-C3CA-11D3-BDBF-00C04F779EB2")
    _PITimeFormat : public _PITime
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeZoneInfo( 
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_TimeZoneInfo( 
            /* [in] */ PITimeZoneInfo *newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_FormatString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE StartOfInterval( 
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IntervalNumber( 
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddIntervals( 
            /* [in] */ BSTR IntervalName,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocaleIndependent( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocaleIndependent( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeFormatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeFormat * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeFormat * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeFormat * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeFormat * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeFormat * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeFormat * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeFormat * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCSeconds )( 
            _PITimeFormat * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UTCSeconds )( 
            _PITimeFormat * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalDate )( 
            _PITimeFormat * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalDate )( 
            _PITimeFormat * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *SetToCurrent )( 
            _PITimeFormat * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCFileTime )( 
            _PITimeFormat * This,
            /* [retval][out] */ CURRENCY *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UTCFileTime )( 
            _PITimeFormat * This,
            /* [in] */ CURRENCY newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            _PITimeFormat * This,
            /* [retval][out] */ _PITime **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeZoneInfo )( 
            _PITimeFormat * This,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [helpstring][helpcontext][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TimeZoneInfo )( 
            _PITimeFormat * This,
            /* [in] */ PITimeZoneInfo *newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputString )( 
            _PITimeFormat * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputString )( 
            _PITimeFormat * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FormatString )( 
            _PITimeFormat * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FormatString )( 
            _PITimeFormat * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputString )( 
            _PITimeFormat * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *StartOfInterval )( 
            _PITimeFormat * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *IntervalNumber )( 
            _PITimeFormat * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *AddIntervals )( 
            _PITimeFormat * This,
            /* [in] */ BSTR IntervalName,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocaleIndependent )( 
            _PITimeFormat * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocaleIndependent )( 
            _PITimeFormat * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } _PITimeFormatVtbl;

    interface _PITimeFormat
    {
        CONST_VTBL struct _PITimeFormatVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeFormat_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeFormat_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeFormat_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeFormat_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeFormat_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeFormat_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeFormat_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITimeFormat_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define _PITimeFormat_put_UTCSeconds(This,newVal)	\
    (This)->lpVtbl -> put_UTCSeconds(This,newVal)

#define _PITimeFormat_get_LocalDate(This,pVal)	\
    (This)->lpVtbl -> get_LocalDate(This,pVal)

#define _PITimeFormat_put_LocalDate(This,newVal)	\
    (This)->lpVtbl -> put_LocalDate(This,newVal)

#define _PITimeFormat_SetToCurrent(This)	\
    (This)->lpVtbl -> SetToCurrent(This)

#define _PITimeFormat_get_UTCFileTime(This,pVal)	\
    (This)->lpVtbl -> get_UTCFileTime(This,pVal)

#define _PITimeFormat_put_UTCFileTime(This,newVal)	\
    (This)->lpVtbl -> put_UTCFileTime(This,newVal)

#define _PITimeFormat_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)


#define _PITimeFormat_get_TimeZoneInfo(This,pVal)	\
    (This)->lpVtbl -> get_TimeZoneInfo(This,pVal)

#define _PITimeFormat_putref_TimeZoneInfo(This,newVal)	\
    (This)->lpVtbl -> putref_TimeZoneInfo(This,newVal)

#define _PITimeFormat_get_InputString(This,pVal)	\
    (This)->lpVtbl -> get_InputString(This,pVal)

#define _PITimeFormat_put_InputString(This,newVal)	\
    (This)->lpVtbl -> put_InputString(This,newVal)

#define _PITimeFormat_get_FormatString(This,pVal)	\
    (This)->lpVtbl -> get_FormatString(This,pVal)

#define _PITimeFormat_put_FormatString(This,newVal)	\
    (This)->lpVtbl -> put_FormatString(This,newVal)

#define _PITimeFormat_get_OutputString(This,pVal)	\
    (This)->lpVtbl -> get_OutputString(This,pVal)

#define _PITimeFormat_StartOfInterval(This,IntervalName,pVal)	\
    (This)->lpVtbl -> StartOfInterval(This,IntervalName,pVal)

#define _PITimeFormat_IntervalNumber(This,IntervalName,pVal)	\
    (This)->lpVtbl -> IntervalNumber(This,IntervalName,pVal)

#define _PITimeFormat_AddIntervals(This,IntervalName,nIntervals,pVal)	\
    (This)->lpVtbl -> AddIntervals(This,IntervalName,nIntervals,pVal)

#define _PITimeFormat_get_LocaleIndependent(This,pVal)	\
    (This)->lpVtbl -> get_LocaleIndependent(This,pVal)

#define _PITimeFormat_put_LocaleIndependent(This,newVal)	\
    (This)->lpVtbl -> put_LocaleIndependent(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_TimeZoneInfo_Proxy( 
    _PITimeFormat * This,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB _PITimeFormat_get_TimeZoneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propputref] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_putref_TimeZoneInfo_Proxy( 
    _PITimeFormat * This,
    /* [in] */ PITimeZoneInfo *newVal);


void __RPC_STUB _PITimeFormat_putref_TimeZoneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_InputString_Proxy( 
    _PITimeFormat * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB _PITimeFormat_get_InputString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_put_InputString_Proxy( 
    _PITimeFormat * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB _PITimeFormat_put_InputString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_FormatString_Proxy( 
    _PITimeFormat * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB _PITimeFormat_get_FormatString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_put_FormatString_Proxy( 
    _PITimeFormat * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB _PITimeFormat_put_FormatString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_OutputString_Proxy( 
    _PITimeFormat * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB _PITimeFormat_get_OutputString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_StartOfInterval_Proxy( 
    _PITimeFormat * This,
    /* [in] */ BSTR IntervalName,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB _PITimeFormat_StartOfInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_IntervalNumber_Proxy( 
    _PITimeFormat * This,
    /* [in] */ BSTR IntervalName,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeFormat_IntervalNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_AddIntervals_Proxy( 
    _PITimeFormat * This,
    /* [in] */ BSTR IntervalName,
    /* [in] */ double nIntervals,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB _PITimeFormat_AddIntervals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_LocaleIndependent_Proxy( 
    _PITimeFormat * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB _PITimeFormat_get_LocaleIndependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_put_LocaleIndependent_Proxy( 
    _PITimeFormat * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB _PITimeFormat_put_LocaleIndependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITimeFormat_INTERFACE_DEFINED__ */


#ifndef ___DynamicTime_INTERFACE_DEFINED__
#define ___DynamicTime_INTERFACE_DEFINED__

/* interface _DynamicTime */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__DynamicTime;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7BD37E3-C94E-11D3-BDC2-00C04F779EB2")
    _DynamicTime : public _PITimeFormat
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReferenceTime( 
            /* [retval][out] */ _PITime **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReferenceTime( 
            /* [in] */ _PITime *newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetClockSource( 
            /* [in] */ IClockSource *pSource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DynamicTimeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DynamicTime * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DynamicTime * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DynamicTime * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DynamicTime * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DynamicTime * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DynamicTime * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DynamicTime * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCSeconds )( 
            _DynamicTime * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UTCSeconds )( 
            _DynamicTime * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocalDate )( 
            _DynamicTime * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocalDate )( 
            _DynamicTime * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *SetToCurrent )( 
            _DynamicTime * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UTCFileTime )( 
            _DynamicTime * This,
            /* [retval][out] */ CURRENCY *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UTCFileTime )( 
            _DynamicTime * This,
            /* [in] */ CURRENCY newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            _DynamicTime * This,
            /* [retval][out] */ _PITime **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeZoneInfo )( 
            _DynamicTime * This,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [helpstring][helpcontext][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_TimeZoneInfo )( 
            _DynamicTime * This,
            /* [in] */ PITimeZoneInfo *newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputString )( 
            _DynamicTime * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputString )( 
            _DynamicTime * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FormatString )( 
            _DynamicTime * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FormatString )( 
            _DynamicTime * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputString )( 
            _DynamicTime * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *StartOfInterval )( 
            _DynamicTime * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *IntervalNumber )( 
            _DynamicTime * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *AddIntervals )( 
            _DynamicTime * This,
            /* [in] */ BSTR IntervalName,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocaleIndependent )( 
            _DynamicTime * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocaleIndependent )( 
            _DynamicTime * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReferenceTime )( 
            _DynamicTime * This,
            /* [retval][out] */ _PITime **pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ReferenceTime )( 
            _DynamicTime * This,
            /* [in] */ _PITime *newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *SetClockSource )( 
            _DynamicTime * This,
            /* [in] */ IClockSource *pSource);
        
        END_INTERFACE
    } _DynamicTimeVtbl;

    interface _DynamicTime
    {
        CONST_VTBL struct _DynamicTimeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DynamicTime_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DynamicTime_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DynamicTime_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DynamicTime_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DynamicTime_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DynamicTime_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DynamicTime_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _DynamicTime_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define _DynamicTime_put_UTCSeconds(This,newVal)	\
    (This)->lpVtbl -> put_UTCSeconds(This,newVal)

#define _DynamicTime_get_LocalDate(This,pVal)	\
    (This)->lpVtbl -> get_LocalDate(This,pVal)

#define _DynamicTime_put_LocalDate(This,newVal)	\
    (This)->lpVtbl -> put_LocalDate(This,newVal)

#define _DynamicTime_SetToCurrent(This)	\
    (This)->lpVtbl -> SetToCurrent(This)

#define _DynamicTime_get_UTCFileTime(This,pVal)	\
    (This)->lpVtbl -> get_UTCFileTime(This,pVal)

#define _DynamicTime_put_UTCFileTime(This,newVal)	\
    (This)->lpVtbl -> put_UTCFileTime(This,newVal)

#define _DynamicTime_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)


#define _DynamicTime_get_TimeZoneInfo(This,pVal)	\
    (This)->lpVtbl -> get_TimeZoneInfo(This,pVal)

#define _DynamicTime_putref_TimeZoneInfo(This,newVal)	\
    (This)->lpVtbl -> putref_TimeZoneInfo(This,newVal)

#define _DynamicTime_get_InputString(This,pVal)	\
    (This)->lpVtbl -> get_InputString(This,pVal)

#define _DynamicTime_put_InputString(This,newVal)	\
    (This)->lpVtbl -> put_InputString(This,newVal)

#define _DynamicTime_get_FormatString(This,pVal)	\
    (This)->lpVtbl -> get_FormatString(This,pVal)

#define _DynamicTime_put_FormatString(This,newVal)	\
    (This)->lpVtbl -> put_FormatString(This,newVal)

#define _DynamicTime_get_OutputString(This,pVal)	\
    (This)->lpVtbl -> get_OutputString(This,pVal)

#define _DynamicTime_StartOfInterval(This,IntervalName,pVal)	\
    (This)->lpVtbl -> StartOfInterval(This,IntervalName,pVal)

#define _DynamicTime_IntervalNumber(This,IntervalName,pVal)	\
    (This)->lpVtbl -> IntervalNumber(This,IntervalName,pVal)

#define _DynamicTime_AddIntervals(This,IntervalName,nIntervals,pVal)	\
    (This)->lpVtbl -> AddIntervals(This,IntervalName,nIntervals,pVal)

#define _DynamicTime_get_LocaleIndependent(This,pVal)	\
    (This)->lpVtbl -> get_LocaleIndependent(This,pVal)

#define _DynamicTime_put_LocaleIndependent(This,newVal)	\
    (This)->lpVtbl -> put_LocaleIndependent(This,newVal)


#define _DynamicTime_get_ReferenceTime(This,pVal)	\
    (This)->lpVtbl -> get_ReferenceTime(This,pVal)

#define _DynamicTime_put_ReferenceTime(This,newVal)	\
    (This)->lpVtbl -> put_ReferenceTime(This,newVal)

#define _DynamicTime_SetClockSource(This,pSource)	\
    (This)->lpVtbl -> SetClockSource(This,pSource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _DynamicTime_get_ReferenceTime_Proxy( 
    _DynamicTime * This,
    /* [retval][out] */ _PITime **pVal);


void __RPC_STUB _DynamicTime_get_ReferenceTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _DynamicTime_put_ReferenceTime_Proxy( 
    _DynamicTime * This,
    /* [in] */ _PITime *newVal);


void __RPC_STUB _DynamicTime_put_ReferenceTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _DynamicTime_SetClockSource_Proxy( 
    _DynamicTime * This,
    /* [in] */ IClockSource *pSource);


void __RPC_STUB _DynamicTime_SetClockSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DynamicTime_INTERFACE_DEFINED__ */


#ifndef __PITimeZoneInfo_INTERFACE_DEFINED__
#define __PITimeZoneInfo_INTERFACE_DEFINED__

/* interface PITimeZoneInfo */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_PITimeZoneInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB14969B-C3CA-11D3-BDBF-00C04F779EB2")
    PITimeZoneInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZoneID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZoneRulesName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StandardName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StandardShortName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DaylightName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DaylightShortName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bias( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_JanuaryIsStandard( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Creator( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreationDate( 
            /* [retval][out] */ _PITime **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DSTRules( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct PITimeZoneInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            PITimeZoneInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            PITimeZoneInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            PITimeZoneInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            PITimeZoneInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            PITimeZoneInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            PITimeZoneInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            PITimeZoneInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZoneID )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZoneRulesName )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StandardName )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StandardShortName )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DaylightName )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DaylightShortName )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bias )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JanuaryIsStandard )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Creator )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreationDate )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ _PITime **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DSTRules )( 
            PITimeZoneInfo * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        END_INTERFACE
    } PITimeZoneInfoVtbl;

    interface PITimeZoneInfo
    {
        CONST_VTBL struct PITimeZoneInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PITimeZoneInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PITimeZoneInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PITimeZoneInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PITimeZoneInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PITimeZoneInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PITimeZoneInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PITimeZoneInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define PITimeZoneInfo_get_ZoneID(This,pVal)	\
    (This)->lpVtbl -> get_ZoneID(This,pVal)

#define PITimeZoneInfo_get_ZoneRulesName(This,pVal)	\
    (This)->lpVtbl -> get_ZoneRulesName(This,pVal)

#define PITimeZoneInfo_get_StandardName(This,pVal)	\
    (This)->lpVtbl -> get_StandardName(This,pVal)

#define PITimeZoneInfo_get_StandardShortName(This,pVal)	\
    (This)->lpVtbl -> get_StandardShortName(This,pVal)

#define PITimeZoneInfo_get_DaylightName(This,pVal)	\
    (This)->lpVtbl -> get_DaylightName(This,pVal)

#define PITimeZoneInfo_get_DaylightShortName(This,pVal)	\
    (This)->lpVtbl -> get_DaylightShortName(This,pVal)

#define PITimeZoneInfo_get_Bias(This,pVal)	\
    (This)->lpVtbl -> get_Bias(This,pVal)

#define PITimeZoneInfo_get_JanuaryIsStandard(This,pVal)	\
    (This)->lpVtbl -> get_JanuaryIsStandard(This,pVal)

#define PITimeZoneInfo_get_Creator(This,pVal)	\
    (This)->lpVtbl -> get_Creator(This,pVal)

#define PITimeZoneInfo_get_CreationDate(This,pVal)	\
    (This)->lpVtbl -> get_CreationDate(This,pVal)

#define PITimeZoneInfo_get_DSTRules(This,pVal)	\
    (This)->lpVtbl -> get_DSTRules(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_ZoneID_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_ZoneID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_ZoneRulesName_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_ZoneRulesName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_StandardName_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_StandardName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_StandardShortName_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_StandardShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DaylightName_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DaylightName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DaylightShortName_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DaylightShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_Bias_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB PITimeZoneInfo_get_Bias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_JanuaryIsStandard_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB PITimeZoneInfo_get_JanuaryIsStandard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_Creator_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB PITimeZoneInfo_get_Creator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_CreationDate_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ _PITime **pVal);


void __RPC_STUB PITimeZoneInfo_get_CreationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DSTRules_Proxy( 
    PITimeZoneInfo * This,
    /* [retval][out] */ SAFEARRAY * *pVal);


void __RPC_STUB PITimeZoneInfo_get_DSTRules_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __PITimeZoneInfo_INTERFACE_DEFINED__ */


#ifndef ___PITimeZoneInfos_INTERFACE_DEFINED__
#define ___PITimeZoneInfos_INTERFACE_DEFINED__

/* interface _PITimeZoneInfos */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeZoneInfos;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A14DB12-CFA3-11d3-853D-00C04F45D1DA")
    _PITimeZoneInfos : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR ZoneID,
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR ZoneName,
            /* [in] */ BSTR StandardName,
            /* [in] */ BSTR StandardShortName,
            /* [in] */ BSTR DaylightName,
            /* [in] */ BSTR DaylightShortName,
            /* [in] */ long Bias,
            /* [in] */ VARIANT_BOOL JanuaryIsStandard,
            /* [in] */ SAFEARRAY * *tzRules,
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR ZoneID) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE LoadFromFile( 
            /* [in] */ BSTR FileName,
            /* [retval][out] */ PITimeZoneInfo **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE DumpToFile( 
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR FileName,
            /* [defaultvalue][in] */ long OutputVer = 0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeZoneInfosVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeZoneInfos * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeZoneInfos * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeZoneInfos * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeZoneInfos * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeZoneInfos * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeZoneInfos * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeZoneInfos * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            _PITimeZoneInfos * This,
            /* [in] */ BSTR ZoneID,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            _PITimeZoneInfos * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            _PITimeZoneInfos * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            _PITimeZoneInfos * This,
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR ZoneName,
            /* [in] */ BSTR StandardName,
            /* [in] */ BSTR StandardShortName,
            /* [in] */ BSTR DaylightName,
            /* [in] */ BSTR DaylightShortName,
            /* [in] */ long Bias,
            /* [in] */ VARIANT_BOOL JanuaryIsStandard,
            /* [in] */ SAFEARRAY * *tzRules,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            _PITimeZoneInfos * This,
            /* [in] */ BSTR ZoneID);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFromFile )( 
            _PITimeZoneInfos * This,
            /* [in] */ BSTR FileName,
            /* [retval][out] */ PITimeZoneInfo **pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *DumpToFile )( 
            _PITimeZoneInfos * This,
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR FileName,
            /* [defaultvalue][in] */ long OutputVer);
        
        END_INTERFACE
    } _PITimeZoneInfosVtbl;

    interface _PITimeZoneInfos
    {
        CONST_VTBL struct _PITimeZoneInfosVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeZoneInfos_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeZoneInfos_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeZoneInfos_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeZoneInfos_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeZoneInfos_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeZoneInfos_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeZoneInfos_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITimeZoneInfos_get_Item(This,ZoneID,pVal)	\
    (This)->lpVtbl -> get_Item(This,ZoneID,pVal)

#define _PITimeZoneInfos_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _PITimeZoneInfos_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _PITimeZoneInfos_Add(This,ZoneID,ZoneName,StandardName,StandardShortName,DaylightName,DaylightShortName,Bias,JanuaryIsStandard,tzRules,pVal)	\
    (This)->lpVtbl -> Add(This,ZoneID,ZoneName,StandardName,StandardShortName,DaylightName,DaylightShortName,Bias,JanuaryIsStandard,tzRules,pVal)

#define _PITimeZoneInfos_Remove(This,ZoneID)	\
    (This)->lpVtbl -> Remove(This,ZoneID)

#define _PITimeZoneInfos_LoadFromFile(This,FileName,pVal)	\
    (This)->lpVtbl -> LoadFromFile(This,FileName,pVal)

#define _PITimeZoneInfos_DumpToFile(This,ZoneID,FileName,OutputVer)	\
    (This)->lpVtbl -> DumpToFile(This,ZoneID,FileName,OutputVer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_get_Item_Proxy( 
    _PITimeZoneInfos * This,
    /* [in] */ BSTR ZoneID,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB _PITimeZoneInfos_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_get__NewEnum_Proxy( 
    _PITimeZoneInfos * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB _PITimeZoneInfos_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_get_Count_Proxy( 
    _PITimeZoneInfos * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneInfos_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_Add_Proxy( 
    _PITimeZoneInfos * This,
    /* [in] */ BSTR ZoneID,
    /* [in] */ BSTR ZoneName,
    /* [in] */ BSTR StandardName,
    /* [in] */ BSTR StandardShortName,
    /* [in] */ BSTR DaylightName,
    /* [in] */ BSTR DaylightShortName,
    /* [in] */ long Bias,
    /* [in] */ VARIANT_BOOL JanuaryIsStandard,
    /* [in] */ SAFEARRAY * *tzRules,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB _PITimeZoneInfos_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_Remove_Proxy( 
    _PITimeZoneInfos * This,
    /* [in] */ BSTR ZoneID);


void __RPC_STUB _PITimeZoneInfos_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_LoadFromFile_Proxy( 
    _PITimeZoneInfos * This,
    /* [in] */ BSTR FileName,
    /* [retval][out] */ PITimeZoneInfo **pVal);


void __RPC_STUB _PITimeZoneInfos_LoadFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_DumpToFile_Proxy( 
    _PITimeZoneInfos * This,
    /* [in] */ BSTR ZoneID,
    /* [in] */ BSTR FileName,
    /* [defaultvalue][in] */ long OutputVer);


void __RPC_STUB _PITimeZoneInfos_DumpToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITimeZoneInfos_INTERFACE_DEFINED__ */


#ifndef ___PITimeZoneRule_INTERFACE_DEFINED__
#define ___PITimeZoneRule_INTERFACE_DEFINED__

/* interface _PITimeZoneRule */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeZoneRule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6D66C51-6837-4FE0-AD8D-811B840BEB1E")
    _PITimeZoneRule : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetRule( 
            /* [in] */ long lStartYear,
            /* [in] */ long lEndYear,
            /* [in] */ long lMonth,
            /* [in] */ long lWeek,
            /* [in] */ long lDay,
            /* [in] */ long lTime,
            /* [in] */ long DaylightBias) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartYear( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartYear( 
            /* [in] */ long lYear) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndYear( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_EndYear( 
            /* [in] */ long lYears) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Month( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Month( 
            /* [in] */ long lMonth) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Week( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Week( 
            /* [in] */ long lWeek) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Day( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Day( 
            /* [in] */ long lDay) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Time( 
            /* [in] */ long lTime) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_BiasOffset( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_BiasOffset( 
            /* [in] */ long lOffset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeZoneRuleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeZoneRule * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeZoneRule * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeZoneRule * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeZoneRule * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeZoneRule * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeZoneRule * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeZoneRule * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *SetRule )( 
            _PITimeZoneRule * This,
            /* [in] */ long lStartYear,
            /* [in] */ long lEndYear,
            /* [in] */ long lMonth,
            /* [in] */ long lWeek,
            /* [in] */ long lDay,
            /* [in] */ long lTime,
            /* [in] */ long DaylightBias);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartYear )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartYear )( 
            _PITimeZoneRule * This,
            /* [in] */ long lYear);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndYear )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndYear )( 
            _PITimeZoneRule * This,
            /* [in] */ long lYears);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Month )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Month )( 
            _PITimeZoneRule * This,
            /* [in] */ long lMonth);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Week )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Week )( 
            _PITimeZoneRule * This,
            /* [in] */ long lWeek);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Day )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Day )( 
            _PITimeZoneRule * This,
            /* [in] */ long lDay);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Time )( 
            _PITimeZoneRule * This,
            /* [in] */ long lTime);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BiasOffset )( 
            _PITimeZoneRule * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BiasOffset )( 
            _PITimeZoneRule * This,
            /* [in] */ long lOffset);
        
        END_INTERFACE
    } _PITimeZoneRuleVtbl;

    interface _PITimeZoneRule
    {
        CONST_VTBL struct _PITimeZoneRuleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeZoneRule_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeZoneRule_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeZoneRule_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeZoneRule_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeZoneRule_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeZoneRule_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeZoneRule_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITimeZoneRule_SetRule(This,lStartYear,lEndYear,lMonth,lWeek,lDay,lTime,DaylightBias)	\
    (This)->lpVtbl -> SetRule(This,lStartYear,lEndYear,lMonth,lWeek,lDay,lTime,DaylightBias)

#define _PITimeZoneRule_get_StartYear(This,pVal)	\
    (This)->lpVtbl -> get_StartYear(This,pVal)

#define _PITimeZoneRule_put_StartYear(This,lYear)	\
    (This)->lpVtbl -> put_StartYear(This,lYear)

#define _PITimeZoneRule_get_EndYear(This,pVal)	\
    (This)->lpVtbl -> get_EndYear(This,pVal)

#define _PITimeZoneRule_put_EndYear(This,lYears)	\
    (This)->lpVtbl -> put_EndYear(This,lYears)

#define _PITimeZoneRule_get_Month(This,pVal)	\
    (This)->lpVtbl -> get_Month(This,pVal)

#define _PITimeZoneRule_put_Month(This,lMonth)	\
    (This)->lpVtbl -> put_Month(This,lMonth)

#define _PITimeZoneRule_get_Week(This,pVal)	\
    (This)->lpVtbl -> get_Week(This,pVal)

#define _PITimeZoneRule_put_Week(This,lWeek)	\
    (This)->lpVtbl -> put_Week(This,lWeek)

#define _PITimeZoneRule_get_Day(This,pVal)	\
    (This)->lpVtbl -> get_Day(This,pVal)

#define _PITimeZoneRule_put_Day(This,lDay)	\
    (This)->lpVtbl -> put_Day(This,lDay)

#define _PITimeZoneRule_get_Time(This,pVal)	\
    (This)->lpVtbl -> get_Time(This,pVal)

#define _PITimeZoneRule_put_Time(This,lTime)	\
    (This)->lpVtbl -> put_Time(This,lTime)

#define _PITimeZoneRule_get_BiasOffset(This,pVal)	\
    (This)->lpVtbl -> get_BiasOffset(This,pVal)

#define _PITimeZoneRule_put_BiasOffset(This,lOffset)	\
    (This)->lpVtbl -> put_BiasOffset(This,lOffset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_SetRule_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lStartYear,
    /* [in] */ long lEndYear,
    /* [in] */ long lMonth,
    /* [in] */ long lWeek,
    /* [in] */ long lDay,
    /* [in] */ long lTime,
    /* [in] */ long DaylightBias);


void __RPC_STUB _PITimeZoneRule_SetRule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_StartYear_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_StartYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_StartYear_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lYear);


void __RPC_STUB _PITimeZoneRule_put_StartYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_EndYear_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_EndYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_EndYear_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lYears);


void __RPC_STUB _PITimeZoneRule_put_EndYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_Month_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_Month_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_Month_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lMonth);


void __RPC_STUB _PITimeZoneRule_put_Month_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_Week_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_Week_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_Week_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lWeek);


void __RPC_STUB _PITimeZoneRule_put_Week_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_Day_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_Day_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_Day_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lDay);


void __RPC_STUB _PITimeZoneRule_put_Day_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_Time_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_Time_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_Time_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lTime);


void __RPC_STUB _PITimeZoneRule_put_Time_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_get_BiasOffset_Proxy( 
    _PITimeZoneRule * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PITimeZoneRule_get_BiasOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeZoneRule_put_BiasOffset_Proxy( 
    _PITimeZoneRule * This,
    /* [in] */ long lOffset);


void __RPC_STUB _PITimeZoneRule_put_BiasOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITimeZoneRule_INTERFACE_DEFINED__ */


#ifndef __ITimeInterval_INTERFACE_DEFINED__
#define __ITimeInterval_INTERFACE_DEFINED__

/* interface ITimeInterval */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 

typedef /* [helpstring][public] */ 
enum FindIntervalConstants
    {	fiBefore	= 0,
	fiOnOrBefore	= fiBefore + 1,
	fiCurrent	= fiOnOrBefore + 1,
	fiOnOrAfter	= fiCurrent + 1,
	fiAfter	= fiOnOrAfter + 1
    } 	FindIntervalConstants;


EXTERN_C const IID IID_ITimeInterval;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E2496D2-C3CB-11d3-BDBF-00C04F779EB2")
    ITimeInterval : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShortName( 
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberName( 
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberShortName( 
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberLo( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberHi( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [in] */ _PITime *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ordinal( 
            /* [in] */ _PITime *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddIntervals( 
            /* [in] */ _PITime *pTime,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE FindMember( 
            /* [in] */ _PITime *pTime,
            /* [in] */ VARIANT Index,
            /* [defaultvalue][in] */ FindIntervalConstants WhatToFind,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_PluralName( 
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeIntervalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITimeInterval * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITimeInterval * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITimeInterval * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITimeInterval * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITimeInterval * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITimeInterval * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITimeInterval * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITimeInterval * This,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ShortName )( 
            ITimeInterval * This,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberName )( 
            ITimeInterval * This,
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberShortName )( 
            ITimeInterval * This,
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberLo )( 
            ITimeInterval * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberHi )( 
            ITimeInterval * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            ITimeInterval * This,
            /* [in] */ _PITime *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ordinal )( 
            ITimeInterval * This,
            /* [in] */ _PITime *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *AddIntervals )( 
            ITimeInterval * This,
            /* [in] */ _PITime *pTime,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *FindMember )( 
            ITimeInterval * This,
            /* [in] */ _PITime *pTime,
            /* [in] */ VARIANT Index,
            /* [defaultvalue][in] */ FindIntervalConstants WhatToFind,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PluralName )( 
            ITimeInterval * This,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ITimeIntervalVtbl;

    interface ITimeInterval
    {
        CONST_VTBL struct ITimeIntervalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeInterval_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimeInterval_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimeInterval_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimeInterval_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITimeInterval_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITimeInterval_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITimeInterval_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITimeInterval_get_Name(This,localeindependent,pVal)	\
    (This)->lpVtbl -> get_Name(This,localeindependent,pVal)

#define ITimeInterval_get_ShortName(This,localeindependent,pVal)	\
    (This)->lpVtbl -> get_ShortName(This,localeindependent,pVal)

#define ITimeInterval_get_MemberName(This,Index,localeindependent,pVal)	\
    (This)->lpVtbl -> get_MemberName(This,Index,localeindependent,pVal)

#define ITimeInterval_get_MemberShortName(This,Index,localeindependent,pVal)	\
    (This)->lpVtbl -> get_MemberShortName(This,Index,localeindependent,pVal)

#define ITimeInterval_get_MemberLo(This,pVal)	\
    (This)->lpVtbl -> get_MemberLo(This,pVal)

#define ITimeInterval_get_MemberHi(This,pVal)	\
    (This)->lpVtbl -> get_MemberHi(This,pVal)

#define ITimeInterval_get_StartTime(This,pTime,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_StartTime(This,pTime,LocaleIndependent,pVal)

#define ITimeInterval_get_Ordinal(This,pTime,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_Ordinal(This,pTime,LocaleIndependent,pVal)

#define ITimeInterval_AddIntervals(This,pTime,nIntervals,pVal)	\
    (This)->lpVtbl -> AddIntervals(This,pTime,nIntervals,pVal)

#define ITimeInterval_FindMember(This,pTime,Index,WhatToFind,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> FindMember(This,pTime,Index,WhatToFind,LocaleIndependent,pVal)

#define ITimeInterval_get_PluralName(This,localeindependent,pVal)	\
    (This)->lpVtbl -> get_PluralName(This,localeindependent,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_Name_Proxy( 
    ITimeInterval * This,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeInterval_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_ShortName_Proxy( 
    ITimeInterval * This,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeInterval_get_ShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberName_Proxy( 
    ITimeInterval * This,
    /* [in] */ long Index,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeInterval_get_MemberName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberShortName_Proxy( 
    ITimeInterval * This,
    /* [in] */ long Index,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeInterval_get_MemberShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberLo_Proxy( 
    ITimeInterval * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITimeInterval_get_MemberLo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberHi_Proxy( 
    ITimeInterval * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITimeInterval_get_MemberHi_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_StartTime_Proxy( 
    ITimeInterval * This,
    /* [in] */ _PITime *pTime,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITimeInterval_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_Ordinal_Proxy( 
    ITimeInterval * This,
    /* [in] */ _PITime *pTime,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITimeInterval_get_Ordinal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITimeInterval_AddIntervals_Proxy( 
    ITimeInterval * This,
    /* [in] */ _PITime *pTime,
    /* [in] */ double nIntervals,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITimeInterval_AddIntervals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITimeInterval_FindMember_Proxy( 
    ITimeInterval * This,
    /* [in] */ _PITime *pTime,
    /* [in] */ VARIANT Index,
    /* [defaultvalue][in] */ FindIntervalConstants WhatToFind,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ DATE *pVal);


void __RPC_STUB ITimeInterval_FindMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_PluralName_Proxy( 
    ITimeInterval * This,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeInterval_get_PluralName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeInterval_INTERFACE_DEFINED__ */


#ifndef ___PITimeRestorer_INTERFACE_DEFINED__
#define ___PITimeRestorer_INTERFACE_DEFINED__

/* interface _PITimeRestorer */
/* [unique][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeRestorer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("67C16825-DABE-437B-B87D-EB5E8C0F98CD")
    _PITimeRestorer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct _PITimeRestorerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeRestorer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeRestorer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeRestorer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeRestorer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeRestorer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeRestorer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeRestorer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _PITimeRestorerVtbl;

    interface _PITimeRestorer
    {
        CONST_VTBL struct _PITimeRestorerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeRestorer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeRestorer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeRestorer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeRestorer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeRestorer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeRestorer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeRestorer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___PITimeRestorer_INTERFACE_DEFINED__ */


#ifndef ___PITimeZoneInfoRestorer_INTERFACE_DEFINED__
#define ___PITimeZoneInfoRestorer_INTERFACE_DEFINED__

/* interface _PITimeZoneInfoRestorer */
/* [unique][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeZoneInfoRestorer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DA1515AB-469E-4B09-872E-172F841C9AB0")
    _PITimeZoneInfoRestorer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct _PITimeZoneInfoRestorerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeZoneInfoRestorer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeZoneInfoRestorer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeZoneInfoRestorer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeZoneInfoRestorer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeZoneInfoRestorer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeZoneInfoRestorer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeZoneInfoRestorer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _PITimeZoneInfoRestorerVtbl;

    interface _PITimeZoneInfoRestorer
    {
        CONST_VTBL struct _PITimeZoneInfoRestorerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeZoneInfoRestorer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeZoneInfoRestorer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeZoneInfoRestorer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeZoneInfoRestorer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeZoneInfoRestorer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeZoneInfoRestorer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeZoneInfoRestorer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___PITimeZoneInfoRestorer_INTERFACE_DEFINED__ */


#ifndef ___PITimeZoneRuleRestorer_INTERFACE_DEFINED__
#define ___PITimeZoneRuleRestorer_INTERFACE_DEFINED__

/* interface _PITimeZoneRuleRestorer */
/* [unique][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeZoneRuleRestorer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C9293BB4-44E0-49E1-A5C7-A5361AF1A282")
    _PITimeZoneRuleRestorer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct _PITimeZoneRuleRestorerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeZoneRuleRestorer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeZoneRuleRestorer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeZoneRuleRestorer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeZoneRuleRestorer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeZoneRuleRestorer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeZoneRuleRestorer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeZoneRuleRestorer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _PITimeZoneRuleRestorerVtbl;

    interface _PITimeZoneRuleRestorer
    {
        CONST_VTBL struct _PITimeZoneRuleRestorerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeZoneRuleRestorer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeZoneRuleRestorer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeZoneRuleRestorer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeZoneRuleRestorer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeZoneRuleRestorer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeZoneRuleRestorer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeZoneRuleRestorer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___PITimeZoneRuleRestorer_INTERFACE_DEFINED__ */


#ifndef ___PITimeFormatRestorer_INTERFACE_DEFINED__
#define ___PITimeFormatRestorer_INTERFACE_DEFINED__

/* interface _PITimeFormatRestorer */
/* [unique][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeFormatRestorer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7EAA023F-2E26-49AB-9278-CA940FE40FB8")
    _PITimeFormatRestorer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct _PITimeFormatRestorerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PITimeFormatRestorer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PITimeFormatRestorer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PITimeFormatRestorer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PITimeFormatRestorer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PITimeFormatRestorer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PITimeFormatRestorer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PITimeFormatRestorer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _PITimeFormatRestorerVtbl;

    interface _PITimeFormatRestorer
    {
        CONST_VTBL struct _PITimeFormatRestorerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeFormatRestorer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeFormatRestorer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeFormatRestorer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeFormatRestorer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeFormatRestorer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeFormatRestorer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeFormatRestorer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___PITimeFormatRestorer_INTERFACE_DEFINED__ */


#ifndef ___DynamicTimeRestorer_INTERFACE_DEFINED__
#define ___DynamicTimeRestorer_INTERFACE_DEFINED__

/* interface _DynamicTimeRestorer */
/* [unique][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__DynamicTimeRestorer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB8D220E-1A79-40F9-BAC6-AF0D468CC121")
    _DynamicTimeRestorer : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct _DynamicTimeRestorerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DynamicTimeRestorer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DynamicTimeRestorer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DynamicTimeRestorer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DynamicTimeRestorer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DynamicTimeRestorer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DynamicTimeRestorer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DynamicTimeRestorer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DynamicTimeRestorerVtbl;

    interface _DynamicTimeRestorer
    {
        CONST_VTBL struct _DynamicTimeRestorerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DynamicTimeRestorer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DynamicTimeRestorer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DynamicTimeRestorer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DynamicTimeRestorer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DynamicTimeRestorer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DynamicTimeRestorer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DynamicTimeRestorer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___DynamicTimeRestorer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PITime;

#ifdef __cplusplus

class DECLSPEC_UUID("80AB1DC1-CA37-11d3-BDC2-00C04F779EB2")
PITime;
#endif

EXTERN_C const CLSID CLSID_PITimeFormat;

#ifdef __cplusplus

class DECLSPEC_UUID("CB14969A-C3CA-11D3-BDBF-00C04F779EB2")
PITimeFormat;
#endif

EXTERN_C const CLSID CLSID_PITimeZoneInfos;

#ifdef __cplusplus

class DECLSPEC_UUID("0A14DB11-CFA3-11d3-853D-00C04F45D1DA")
PITimeZoneInfos;
#endif

EXTERN_C const CLSID CLSID_PITimeZoneRule;

#ifdef __cplusplus

class DECLSPEC_UUID("5ACDBE88-BF82-4F40-B56C-8507F1E28561")
PITimeZoneRule;
#endif

EXTERN_C const CLSID CLSID_DeviceTimeZones;

#ifdef __cplusplus

class DECLSPEC_UUID("A4507ED1-D021-11d3-853D-00C04F45D1DA")
DeviceTimeZones;
#endif

EXTERN_C const CLSID CLSID_DynamicTime;

#ifdef __cplusplus

class DECLSPEC_UUID("B7BD37E4-C94E-11D3-BDC2-00C04F779EB2")
DynamicTime;
#endif

#ifndef ___TimeIntervals_INTERFACE_DEFINED__
#define ___TimeIntervals_INTERFACE_DEFINED__

/* interface _TimeIntervals */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 

typedef /* [helpcontext][helpstring][hidden] */ 
enum tiSpecialNames
    {	tisnYesterday	= -1,
	tisnToday	= 0,
	tisnSunday	= 1,
	tisnMonday	= 2,
	tisnTuesday	= 3,
	tisnWednesday	= 4,
	tisnThursday	= 5,
	tisnFriday	= 6,
	tisnSaturday	= 7
    } 	tiSpecialNames;


EXTERN_C const IID IID__TimeIntervals;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4B7F591-B417-11d4-BE0E-00C04F779EB2")
    _TimeIntervals : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index1,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ ITimeInterval **pVal) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Errors( 
            /* [retval][out] */ /* external definition not present */ _PIErrors **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE SpecialName( 
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ tiSpecialNames *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _TimeIntervalsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _TimeIntervals * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _TimeIntervals * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _TimeIntervals * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _TimeIntervals * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _TimeIntervals * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _TimeIntervals * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _TimeIntervals * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            _TimeIntervals * This,
            /* [in] */ VARIANT Index1,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ ITimeInterval **pVal);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            _TimeIntervals * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            _TimeIntervals * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            _TimeIntervals * This,
            /* [retval][out] */ /* external definition not present */ _PIErrors **pVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *SpecialName )( 
            _TimeIntervals * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ tiSpecialNames *pVal);
        
        END_INTERFACE
    } _TimeIntervalsVtbl;

    interface _TimeIntervals
    {
        CONST_VTBL struct _TimeIntervalsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _TimeIntervals_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _TimeIntervals_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _TimeIntervals_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _TimeIntervals_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _TimeIntervals_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _TimeIntervals_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _TimeIntervals_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _TimeIntervals_get_Item(This,Index1,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index1,LocaleIndependent,pVal)

#define _TimeIntervals_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _TimeIntervals_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _TimeIntervals_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define _TimeIntervals_SpecialName(This,Name,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> SpecialName(This,Name,LocaleIndependent,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get_Item_Proxy( 
    _TimeIntervals * This,
    /* [in] */ VARIANT Index1,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ ITimeInterval **pVal);


void __RPC_STUB _TimeIntervals_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get__NewEnum_Proxy( 
    _TimeIntervals * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB _TimeIntervals_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get_Count_Proxy( 
    _TimeIntervals * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _TimeIntervals_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get_Errors_Proxy( 
    _TimeIntervals * This,
    /* [retval][out] */ /* external definition not present */ _PIErrors **pVal);


void __RPC_STUB _TimeIntervals_get_Errors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_SpecialName_Proxy( 
    _TimeIntervals * This,
    /* [in] */ BSTR Name,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ tiSpecialNames *pVal);


void __RPC_STUB _TimeIntervals_SpecialName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___TimeIntervals_INTERFACE_DEFINED__ */


#ifndef __ITimeIntervals2_INTERFACE_DEFINED__
#define __ITimeIntervals2_INTERFACE_DEFINED__

/* interface ITimeIntervals2 */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITimeIntervals2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6E691CBD-3116-4308-97AA-F78461D260B4")
    ITimeIntervals2 : public _TimeIntervals
    {
    public:
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ParseTimeStepString( 
            /* [in] */ BSTR IntervalStep,
            /* [in] */ VARIANT_BOOL LocaleIndependent,
            /* [out] */ double *StepSize,
            /* [retval][out] */ ITimeInterval **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeIntervals2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITimeIntervals2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITimeIntervals2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITimeIntervals2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITimeIntervals2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITimeIntervals2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITimeIntervals2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITimeIntervals2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITimeIntervals2 * This,
            /* [in] */ VARIANT Index1,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ ITimeInterval **pVal);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITimeIntervals2 * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITimeIntervals2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Errors )( 
            ITimeIntervals2 * This,
            /* [retval][out] */ /* external definition not present */ _PIErrors **pVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *SpecialName )( 
            ITimeIntervals2 * This,
            /* [in] */ BSTR Name,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ tiSpecialNames *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE *ParseTimeStepString )( 
            ITimeIntervals2 * This,
            /* [in] */ BSTR IntervalStep,
            /* [in] */ VARIANT_BOOL LocaleIndependent,
            /* [out] */ double *StepSize,
            /* [retval][out] */ ITimeInterval **pVal);
        
        END_INTERFACE
    } ITimeIntervals2Vtbl;

    interface ITimeIntervals2
    {
        CONST_VTBL struct ITimeIntervals2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeIntervals2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimeIntervals2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimeIntervals2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimeIntervals2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITimeIntervals2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITimeIntervals2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITimeIntervals2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITimeIntervals2_get_Item(This,Index1,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index1,LocaleIndependent,pVal)

#define ITimeIntervals2_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define ITimeIntervals2_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITimeIntervals2_get_Errors(This,pVal)	\
    (This)->lpVtbl -> get_Errors(This,pVal)

#define ITimeIntervals2_SpecialName(This,Name,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> SpecialName(This,Name,LocaleIndependent,pVal)


#define ITimeIntervals2_ParseTimeStepString(This,IntervalStep,LocaleIndependent,StepSize,pVal)	\
    (This)->lpVtbl -> ParseTimeStepString(This,IntervalStep,LocaleIndependent,StepSize,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITimeIntervals2_ParseTimeStepString_Proxy( 
    ITimeIntervals2 * This,
    /* [in] */ BSTR IntervalStep,
    /* [in] */ VARIANT_BOOL LocaleIndependent,
    /* [out] */ double *StepSize,
    /* [retval][out] */ ITimeInterval **pVal);


void __RPC_STUB ITimeIntervals2_ParseTimeStepString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeIntervals2_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TimeIntervals;

#ifdef __cplusplus

class DECLSPEC_UUID("500776E1-CF9C-11d3-853D-00C04F45D1DA")
TimeIntervals;
#endif

#ifndef __ITimeIntervals_INTERFACE_DEFINED__
#define __ITimeIntervals_INTERFACE_DEFINED__

/* interface ITimeIntervals */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITimeIntervals;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E2496D3-C3CB-11d3-BDBF-00C04F779EB2")
    ITimeIntervals : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index1,
            /* [retval][out] */ ITimeInterval **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeIntervalsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITimeIntervals * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITimeIntervals * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITimeIntervals * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITimeIntervals * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITimeIntervals * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITimeIntervals * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITimeIntervals * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITimeIntervals * This,
            /* [in] */ long Index1,
            /* [retval][out] */ ITimeInterval **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITimeIntervals * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ITimeIntervals * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ITimeIntervals * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ITimeIntervalsVtbl;

    interface ITimeIntervals
    {
        CONST_VTBL struct ITimeIntervalsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeIntervals_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimeIntervals_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimeIntervals_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimeIntervals_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITimeIntervals_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITimeIntervals_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITimeIntervals_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITimeIntervals_get_Item(This,Index1,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index1,pVal)

#define ITimeIntervals_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITimeIntervals_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ITimeIntervals_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE ITimeIntervals_get_Item_Proxy( 
    ITimeIntervals * This,
    /* [in] */ long Index1,
    /* [retval][out] */ ITimeInterval **pVal);


void __RPC_STUB ITimeIntervals_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE ITimeIntervals_get_Count_Proxy( 
    ITimeIntervals * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB ITimeIntervals_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE ITimeIntervals_get_Name_Proxy( 
    ITimeIntervals * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeIntervals_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE ITimeIntervals_get_Description_Proxy( 
    ITimeIntervals * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ITimeIntervals_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeIntervals_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PITimeRestorer;

#ifdef __cplusplus

class DECLSPEC_UUID("9FAC45A8-3F76-4729-AFDF-DFEDB2142416")
PITimeRestorer;
#endif

EXTERN_C const CLSID CLSID_PITimeZoneInfoRestorer;

#ifdef __cplusplus

class DECLSPEC_UUID("2605FD6D-825B-4B8F-9C07-954E19ADAF45")
PITimeZoneInfoRestorer;
#endif

EXTERN_C const CLSID CLSID_PITimeZoneRuleRestorer;

#ifdef __cplusplus

class DECLSPEC_UUID("17F9BE90-04E8-4CDA-B16E-398BFB65507A")
PITimeZoneRuleRestorer;
#endif

EXTERN_C const CLSID CLSID_PITimeFormatRestorer;

#ifdef __cplusplus

class DECLSPEC_UUID("57ECD270-448E-4BF8-B1DC-A2BB95EEB3DE")
PITimeFormatRestorer;
#endif

EXTERN_C const CLSID CLSID_DynamicTimeRestorer;

#ifdef __cplusplus

class DECLSPEC_UUID("C3B4055C-A536-47B1-B01D-41EE6007F158")
DynamicTimeRestorer;
#endif
#endif /* __PITimeServer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


