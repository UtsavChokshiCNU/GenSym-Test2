

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jul 30 17:05:01 2012
 */
/* Compiler settings for ..\..\activex\G2Com\G2Com.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __G2Com_h__
#define __G2Com_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IG2Gateway_FWD_DEFINED__
#define __IG2Gateway_FWD_DEFINED__
typedef interface IG2Gateway IG2Gateway;
#endif 	/* __IG2Gateway_FWD_DEFINED__ */


#ifndef __IG2Gateway2_FWD_DEFINED__
#define __IG2Gateway2_FWD_DEFINED__
typedef interface IG2Gateway2 IG2Gateway2;
#endif 	/* __IG2Gateway2_FWD_DEFINED__ */


#ifndef __IG2Gateway3_FWD_DEFINED__
#define __IG2Gateway3_FWD_DEFINED__
typedef interface IG2Gateway3 IG2Gateway3;
#endif 	/* __IG2Gateway3_FWD_DEFINED__ */


#ifndef __IG2Gateway4_FWD_DEFINED__
#define __IG2Gateway4_FWD_DEFINED__
typedef interface IG2Gateway4 IG2Gateway4;
#endif 	/* __IG2Gateway4_FWD_DEFINED__ */


#ifndef __G2ComObject_FWD_DEFINED__
#define __G2ComObject_FWD_DEFINED__
typedef interface G2ComObject G2ComObject;
#endif 	/* __G2ComObject_FWD_DEFINED__ */


#ifndef __IG2StructureEntry_FWD_DEFINED__
#define __IG2StructureEntry_FWD_DEFINED__
typedef interface IG2StructureEntry IG2StructureEntry;
#endif 	/* __IG2StructureEntry_FWD_DEFINED__ */


#ifndef __IG2Structure_FWD_DEFINED__
#define __IG2Structure_FWD_DEFINED__
typedef interface IG2Structure IG2Structure;
#endif 	/* __IG2Structure_FWD_DEFINED__ */


#ifndef __IG2Item_FWD_DEFINED__
#define __IG2Item_FWD_DEFINED__
typedef interface IG2Item IG2Item;
#endif 	/* __IG2Item_FWD_DEFINED__ */


#ifndef __IG2Item2_FWD_DEFINED__
#define __IG2Item2_FWD_DEFINED__
typedef interface IG2Item2 IG2Item2;
#endif 	/* __IG2Item2_FWD_DEFINED__ */


#ifndef __IG2Item3_FWD_DEFINED__
#define __IG2Item3_FWD_DEFINED__
typedef interface IG2Item3 IG2Item3;
#endif 	/* __IG2Item3_FWD_DEFINED__ */


#ifndef __IG2Item4_FWD_DEFINED__
#define __IG2Item4_FWD_DEFINED__
typedef interface IG2Item4 IG2Item4;
#endif 	/* __IG2Item4_FWD_DEFINED__ */


#ifndef __IG2Attribute_FWD_DEFINED__
#define __IG2Attribute_FWD_DEFINED__
typedef interface IG2Attribute IG2Attribute;
#endif 	/* __IG2Attribute_FWD_DEFINED__ */


#ifndef __IG2ListOrArray_FWD_DEFINED__
#define __IG2ListOrArray_FWD_DEFINED__
typedef interface IG2ListOrArray IG2ListOrArray;
#endif 	/* __IG2ListOrArray_FWD_DEFINED__ */


#ifndef __IG2LAElement_FWD_DEFINED__
#define __IG2LAElement_FWD_DEFINED__
typedef interface IG2LAElement IG2LAElement;
#endif 	/* __IG2LAElement_FWD_DEFINED__ */


#ifndef __IG2Symbol_FWD_DEFINED__
#define __IG2Symbol_FWD_DEFINED__
typedef interface IG2Symbol IG2Symbol;
#endif 	/* __IG2Symbol_FWD_DEFINED__ */


#ifndef __IG2ItemRef_FWD_DEFINED__
#define __IG2ItemRef_FWD_DEFINED__
typedef interface IG2ItemRef IG2ItemRef;
#endif 	/* __IG2ItemRef_FWD_DEFINED__ */


#ifndef __IG2Workspace_FWD_DEFINED__
#define __IG2Workspace_FWD_DEFINED__
typedef interface IG2Workspace IG2Workspace;
#endif 	/* __IG2Workspace_FWD_DEFINED__ */


#ifndef __IG2Window_FWD_DEFINED__
#define __IG2Window_FWD_DEFINED__
typedef interface IG2Window IG2Window;
#endif 	/* __IG2Window_FWD_DEFINED__ */


#ifndef __IG2ComConfigurator_FWD_DEFINED__
#define __IG2ComConfigurator_FWD_DEFINED__
typedef interface IG2ComConfigurator IG2ComConfigurator;
#endif 	/* __IG2ComConfigurator_FWD_DEFINED__ */


#ifndef ___G2Events_FWD_DEFINED__
#define ___G2Events_FWD_DEFINED__
typedef interface _G2Events _G2Events;
#endif 	/* ___G2Events_FWD_DEFINED__ */


#ifndef __G2Gateway_FWD_DEFINED__
#define __G2Gateway_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Gateway G2Gateway;
#else
typedef struct G2Gateway G2Gateway;
#endif /* __cplusplus */

#endif 	/* __G2Gateway_FWD_DEFINED__ */


#ifndef __GatewayProp_FWD_DEFINED__
#define __GatewayProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class GatewayProp GatewayProp;
#else
typedef struct GatewayProp GatewayProp;
#endif /* __cplusplus */

#endif 	/* __GatewayProp_FWD_DEFINED__ */


#ifndef __G2StructureEntry_FWD_DEFINED__
#define __G2StructureEntry_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2StructureEntry G2StructureEntry;
#else
typedef struct G2StructureEntry G2StructureEntry;
#endif /* __cplusplus */

#endif 	/* __G2StructureEntry_FWD_DEFINED__ */


#ifndef __G2Structure_FWD_DEFINED__
#define __G2Structure_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Structure G2Structure;
#else
typedef struct G2Structure G2Structure;
#endif /* __cplusplus */

#endif 	/* __G2Structure_FWD_DEFINED__ */


#ifndef __G2Item_FWD_DEFINED__
#define __G2Item_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Item G2Item;
#else
typedef struct G2Item G2Item;
#endif /* __cplusplus */

#endif 	/* __G2Item_FWD_DEFINED__ */


#ifndef __G2Attribute_FWD_DEFINED__
#define __G2Attribute_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Attribute G2Attribute;
#else
typedef struct G2Attribute G2Attribute;
#endif /* __cplusplus */

#endif 	/* __G2Attribute_FWD_DEFINED__ */


#ifndef __G2ListOrArray_FWD_DEFINED__
#define __G2ListOrArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2ListOrArray G2ListOrArray;
#else
typedef struct G2ListOrArray G2ListOrArray;
#endif /* __cplusplus */

#endif 	/* __G2ListOrArray_FWD_DEFINED__ */


#ifndef __G2Symbol_FWD_DEFINED__
#define __G2Symbol_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Symbol G2Symbol;
#else
typedef struct G2Symbol G2Symbol;
#endif /* __cplusplus */

#endif 	/* __G2Symbol_FWD_DEFINED__ */


#ifndef __G2LAElement_FWD_DEFINED__
#define __G2LAElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2LAElement G2LAElement;
#else
typedef struct G2LAElement G2LAElement;
#endif /* __cplusplus */

#endif 	/* __G2LAElement_FWD_DEFINED__ */


#ifndef __G2ItemRef_FWD_DEFINED__
#define __G2ItemRef_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2ItemRef G2ItemRef;
#else
typedef struct G2ItemRef G2ItemRef;
#endif /* __cplusplus */

#endif 	/* __G2ItemRef_FWD_DEFINED__ */


#ifndef __G2Workspace_FWD_DEFINED__
#define __G2Workspace_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Workspace G2Workspace;
#else
typedef struct G2Workspace G2Workspace;
#endif /* __cplusplus */

#endif 	/* __G2Workspace_FWD_DEFINED__ */


#ifndef __G2Window_FWD_DEFINED__
#define __G2Window_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2Window G2Window;
#else
typedef struct G2Window G2Window;
#endif /* __cplusplus */

#endif 	/* __G2Window_FWD_DEFINED__ */


#ifndef __G2ComConfigurator_FWD_DEFINED__
#define __G2ComConfigurator_FWD_DEFINED__

#ifdef __cplusplus
typedef class G2ComConfigurator G2ComConfigurator;
#else
typedef struct G2ComConfigurator G2ComConfigurator;
#endif /* __cplusplus */

#endif 	/* __G2ComConfigurator_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_G2Com_0000_0000 */
/* [local] */ 

typedef /* [public][public][public][public][public][public][public][public][public][public][uuid] */  DECLSPEC_UUID("13255623-8420-4948-9CFD-130416633EEC") 
enum __MIDL___MIDL_itf_G2Com_0000_0000_0001
    {	g2Null	= 0,
	g2Integer	= 1,
	g2SymbolType	= 3,
	g2String	= 4,
	g2Logical	= 5,
	g2Float	= 6,
	g2IntegerArray	= 17,
	g2SymbolArray	= 19,
	g2StringArray	= 20,
	g2LogicalArray	= 21,
	g2FloatArray	= 22,
	g2ItemArray	= 23,
	g2ValueArray	= 24,
	g2ItemOrValueArray	= 25,
	g2QuantityArray	= 26,
	g2IntegerList	= 33,
	g2SymbolList	= 35,
	g2StringList	= 36,
	g2LogicalList	= 37,
	g2FloatList	= 38,
	g2ItemList	= 39,
	g2ValueList	= 40,
	g2ItemOrValueList	= 41,
	g2QuantityList	= 42,
	g2Sequence	= 49,
	g2StructureType	= 50
    } 	G2Type;

typedef /* [public][public][uuid] */  DECLSPEC_UUID("585F7437-1601-4245-B44E-9AC8B35A098E") 
enum __MIDL___MIDL_itf_G2Com_0000_0000_0002
    {	g2UnknownState	= -1,
	g2Reset	= 0,
	g2Paused	= 1,
	g2Running	= 2
    } 	G2RunStateType;

typedef /* [public][v1_enum][uuid] */  DECLSPEC_UUID("F2C13A71-2B27-46c7-AD2B-4B9A0DE4080A") 
enum __MIDL___MIDL_itf_G2Com_0000_0000_0003
    {	stModify	= 1,
	stDelete	= 2,
	stColorChg	= 3,
	stCustom	= 4,
	stValueChg	= 5,
	stWkspcAdd	= 6,
	stWkspcDel	= 7,
	stSelection	= 8
    } 	g2SubscriptionType;



extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_0000_v0_0_s_ifspec;

#ifndef __IG2Gateway_INTERFACE_DEFINED__
#define __IG2Gateway_INTERFACE_DEFINED__

/* interface IG2Gateway */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Gateway;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A71ACD10-3B6E-11D1-8AB3-00609703E60F")
    IG2Gateway : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ VARIANT_BOOL WaitFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE Call( 
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *InputArguments,
            /* [retval][out] */ VARIANT *ReturnArguments) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE CallDeferred( 
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY * *InputArguments) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE Start( 
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *Arguments) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNamedObject( 
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH *Obj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateObjectInstance( 
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH *Obj) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsG2Connected( 
            /* [retval][out] */ VARIANT_BOOL *Val) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsG2Running( 
            /* [retval][out] */ VARIANT_BOOL *Val) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_G2Location( 
            /* [retval][out] */ BSTR *Location) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_G2Location( 
            /* [in] */ BSTR Location) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InterfaceClass( 
            /* [retval][out] */ BSTR *InterfaceClassName) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_InterfaceClass( 
            /* [in] */ BSTR InterfaceClassName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteInitializationString( 
            /* [retval][out] */ BSTR *InitializationString) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteInitializationString( 
            /* [in] */ BSTR InitializationString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CallTimeout( 
            /* [retval][out] */ long *MaxWait) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_CallTimeout( 
            /* [in] */ long MaxWait) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _FireEvents( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PostMessage( 
            /* [in] */ VARIANT *Message) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2GatewayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Gateway * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Gateway * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Gateway * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Gateway * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Gateway * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Gateway * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Gateway * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IG2Gateway * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IG2Gateway * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Call )( 
            IG2Gateway * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *InputArguments,
            /* [retval][out] */ VARIANT *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *CallDeferred )( 
            IG2Gateway * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY * *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IG2Gateway * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNamedObject )( 
            IG2Gateway * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateObjectInstance )( 
            IG2Gateway * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Connected )( 
            IG2Gateway * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Running )( 
            IG2Gateway * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2Location )( 
            IG2Gateway * This,
            /* [retval][out] */ BSTR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_G2Location )( 
            IG2Gateway * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InterfaceClass )( 
            IG2Gateway * This,
            /* [retval][out] */ BSTR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InterfaceClass )( 
            IG2Gateway * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteInitializationString )( 
            IG2Gateway * This,
            /* [retval][out] */ BSTR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteInitializationString )( 
            IG2Gateway * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CallTimeout )( 
            IG2Gateway * This,
            /* [retval][out] */ long *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CallTimeout )( 
            IG2Gateway * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_FireEvents )( 
            IG2Gateway * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PostMessage )( 
            IG2Gateway * This,
            /* [in] */ VARIANT *Message);
        
        END_INTERFACE
    } IG2GatewayVtbl;

    interface IG2Gateway
    {
        CONST_VTBL struct IG2GatewayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Gateway_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Gateway_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Gateway_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Gateway_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Gateway_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Gateway_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Gateway_Connect(This,WaitFlag)	\
    ( (This)->lpVtbl -> Connect(This,WaitFlag) ) 

#define IG2Gateway_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IG2Gateway_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    ( (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments) ) 

#define IG2Gateway_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    ( (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments) ) 

#define IG2Gateway_Start(This,ProcedureName,Arguments)	\
    ( (This)->lpVtbl -> Start(This,ProcedureName,Arguments) ) 

#define IG2Gateway_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    ( (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj) ) 

#define IG2Gateway_CreateObjectInstance(This,ClassName,Obj)	\
    ( (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj) ) 

#define IG2Gateway_get_IsG2Connected(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Connected(This,Val) ) 

#define IG2Gateway_get_IsG2Running(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Running(This,Val) ) 

#define IG2Gateway_get_G2Location(This,Location)	\
    ( (This)->lpVtbl -> get_G2Location(This,Location) ) 

#define IG2Gateway_put_G2Location(This,Location)	\
    ( (This)->lpVtbl -> put_G2Location(This,Location) ) 

#define IG2Gateway_get_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway_put_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway_get_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway_put_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway_get_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> get_CallTimeout(This,MaxWait) ) 

#define IG2Gateway_put_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> put_CallTimeout(This,MaxWait) ) 

#define IG2Gateway__FireEvents(This)	\
    ( (This)->lpVtbl -> _FireEvents(This) ) 

#define IG2Gateway_PostMessage(This,Message)	\
    ( (This)->lpVtbl -> PostMessage(This,Message) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Gateway_INTERFACE_DEFINED__ */


#ifndef __IG2Gateway2_INTERFACE_DEFINED__
#define __IG2Gateway2_INTERFACE_DEFINED__

/* interface IG2Gateway2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Gateway2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C18D503E-C8A5-45c6-A42F-100F4347B367")
    IG2Gateway2 : public IG2Gateway
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnStartPage( 
            /* [in] */ IUnknown *piUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnEndPage( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Gateway2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Gateway2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Gateway2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Gateway2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Gateway2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Gateway2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Gateway2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Gateway2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IG2Gateway2 * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IG2Gateway2 * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Call )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *InputArguments,
            /* [retval][out] */ VARIANT *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *CallDeferred )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY * *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNamedObject )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateObjectInstance )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Connected )( 
            IG2Gateway2 * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Running )( 
            IG2Gateway2 * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2Location )( 
            IG2Gateway2 * This,
            /* [retval][out] */ BSTR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_G2Location )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InterfaceClass )( 
            IG2Gateway2 * This,
            /* [retval][out] */ BSTR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InterfaceClass )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteInitializationString )( 
            IG2Gateway2 * This,
            /* [retval][out] */ BSTR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteInitializationString )( 
            IG2Gateway2 * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CallTimeout )( 
            IG2Gateway2 * This,
            /* [retval][out] */ long *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CallTimeout )( 
            IG2Gateway2 * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_FireEvents )( 
            IG2Gateway2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PostMessage )( 
            IG2Gateway2 * This,
            /* [in] */ VARIANT *Message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnStartPage )( 
            IG2Gateway2 * This,
            /* [in] */ IUnknown *piUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnEndPage )( 
            IG2Gateway2 * This);
        
        END_INTERFACE
    } IG2Gateway2Vtbl;

    interface IG2Gateway2
    {
        CONST_VTBL struct IG2Gateway2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Gateway2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Gateway2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Gateway2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Gateway2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Gateway2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Gateway2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Gateway2_Connect(This,WaitFlag)	\
    ( (This)->lpVtbl -> Connect(This,WaitFlag) ) 

#define IG2Gateway2_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IG2Gateway2_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    ( (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments) ) 

#define IG2Gateway2_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    ( (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments) ) 

#define IG2Gateway2_Start(This,ProcedureName,Arguments)	\
    ( (This)->lpVtbl -> Start(This,ProcedureName,Arguments) ) 

#define IG2Gateway2_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    ( (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj) ) 

#define IG2Gateway2_CreateObjectInstance(This,ClassName,Obj)	\
    ( (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj) ) 

#define IG2Gateway2_get_IsG2Connected(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Connected(This,Val) ) 

#define IG2Gateway2_get_IsG2Running(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Running(This,Val) ) 

#define IG2Gateway2_get_G2Location(This,Location)	\
    ( (This)->lpVtbl -> get_G2Location(This,Location) ) 

#define IG2Gateway2_put_G2Location(This,Location)	\
    ( (This)->lpVtbl -> put_G2Location(This,Location) ) 

#define IG2Gateway2_get_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway2_put_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway2_get_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway2_put_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway2_get_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> get_CallTimeout(This,MaxWait) ) 

#define IG2Gateway2_put_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> put_CallTimeout(This,MaxWait) ) 

#define IG2Gateway2__FireEvents(This)	\
    ( (This)->lpVtbl -> _FireEvents(This) ) 

#define IG2Gateway2_PostMessage(This,Message)	\
    ( (This)->lpVtbl -> PostMessage(This,Message) ) 


#define IG2Gateway2_OnStartPage(This,piUnk)	\
    ( (This)->lpVtbl -> OnStartPage(This,piUnk) ) 

#define IG2Gateway2_OnEndPage(This)	\
    ( (This)->lpVtbl -> OnEndPage(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Gateway2_INTERFACE_DEFINED__ */


#ifndef __IG2Gateway3_INTERFACE_DEFINED__
#define __IG2Gateway3_INTERFACE_DEFINED__

/* interface IG2Gateway3 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Gateway3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43DD340A-7247-416a-9DB0-64B15CD4BD28")
    IG2Gateway3 : public IG2Gateway2
    {
    public:
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE MakeG2ComVariable( 
            /* [in] */ G2Type ComType,
            /* [in] */ SAFEARRAY * *inArgs,
            /* [retval][out] */ VARIANT *pResult) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE DbgMsg( 
            /* [in] */ BSTR msg) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_G2RunState( 
            /* [retval][out] */ G2RunStateType *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Gateway3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Gateway3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Gateway3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Gateway3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Gateway3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Gateway3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Gateway3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Gateway3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IG2Gateway3 * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IG2Gateway3 * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Call )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *InputArguments,
            /* [retval][out] */ VARIANT *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *CallDeferred )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY * *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNamedObject )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateObjectInstance )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Connected )( 
            IG2Gateway3 * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Running )( 
            IG2Gateway3 * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2Location )( 
            IG2Gateway3 * This,
            /* [retval][out] */ BSTR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_G2Location )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InterfaceClass )( 
            IG2Gateway3 * This,
            /* [retval][out] */ BSTR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InterfaceClass )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteInitializationString )( 
            IG2Gateway3 * This,
            /* [retval][out] */ BSTR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteInitializationString )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CallTimeout )( 
            IG2Gateway3 * This,
            /* [retval][out] */ long *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CallTimeout )( 
            IG2Gateway3 * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_FireEvents )( 
            IG2Gateway3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PostMessage )( 
            IG2Gateway3 * This,
            /* [in] */ VARIANT *Message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnStartPage )( 
            IG2Gateway3 * This,
            /* [in] */ IUnknown *piUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnEndPage )( 
            IG2Gateway3 * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *MakeG2ComVariable )( 
            IG2Gateway3 * This,
            /* [in] */ G2Type ComType,
            /* [in] */ SAFEARRAY * *inArgs,
            /* [retval][out] */ VARIANT *pResult);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DbgMsg )( 
            IG2Gateway3 * This,
            /* [in] */ BSTR msg);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2RunState )( 
            IG2Gateway3 * This,
            /* [retval][out] */ G2RunStateType *pVal);
        
        END_INTERFACE
    } IG2Gateway3Vtbl;

    interface IG2Gateway3
    {
        CONST_VTBL struct IG2Gateway3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Gateway3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Gateway3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Gateway3_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Gateway3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Gateway3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Gateway3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Gateway3_Connect(This,WaitFlag)	\
    ( (This)->lpVtbl -> Connect(This,WaitFlag) ) 

#define IG2Gateway3_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IG2Gateway3_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    ( (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments) ) 

#define IG2Gateway3_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    ( (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments) ) 

#define IG2Gateway3_Start(This,ProcedureName,Arguments)	\
    ( (This)->lpVtbl -> Start(This,ProcedureName,Arguments) ) 

#define IG2Gateway3_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    ( (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj) ) 

#define IG2Gateway3_CreateObjectInstance(This,ClassName,Obj)	\
    ( (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj) ) 

#define IG2Gateway3_get_IsG2Connected(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Connected(This,Val) ) 

#define IG2Gateway3_get_IsG2Running(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Running(This,Val) ) 

#define IG2Gateway3_get_G2Location(This,Location)	\
    ( (This)->lpVtbl -> get_G2Location(This,Location) ) 

#define IG2Gateway3_put_G2Location(This,Location)	\
    ( (This)->lpVtbl -> put_G2Location(This,Location) ) 

#define IG2Gateway3_get_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway3_put_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway3_get_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway3_put_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway3_get_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> get_CallTimeout(This,MaxWait) ) 

#define IG2Gateway3_put_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> put_CallTimeout(This,MaxWait) ) 

#define IG2Gateway3__FireEvents(This)	\
    ( (This)->lpVtbl -> _FireEvents(This) ) 

#define IG2Gateway3_PostMessage(This,Message)	\
    ( (This)->lpVtbl -> PostMessage(This,Message) ) 


#define IG2Gateway3_OnStartPage(This,piUnk)	\
    ( (This)->lpVtbl -> OnStartPage(This,piUnk) ) 

#define IG2Gateway3_OnEndPage(This)	\
    ( (This)->lpVtbl -> OnEndPage(This) ) 


#define IG2Gateway3_MakeG2ComVariable(This,ComType,inArgs,pResult)	\
    ( (This)->lpVtbl -> MakeG2ComVariable(This,ComType,inArgs,pResult) ) 

#define IG2Gateway3_DbgMsg(This,msg)	\
    ( (This)->lpVtbl -> DbgMsg(This,msg) ) 

#define IG2Gateway3_get_G2RunState(This,pVal)	\
    ( (This)->lpVtbl -> get_G2RunState(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Gateway3_INTERFACE_DEFINED__ */


#ifndef __IG2Gateway4_INTERFACE_DEFINED__
#define __IG2Gateway4_INTERFACE_DEFINED__

/* interface IG2Gateway4 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Gateway4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("064BEA68-090C-47fe-8D43-1BF88F5BC47D")
    IG2Gateway4 : public IG2Gateway3
    {
    public:
        virtual /* [helpstring][id][propget][hidden] */ HRESULT STDMETHODCALLTYPE get_TWHandle( 
            /* [retval][out] */ long *plHWnd) = 0;
        
        virtual /* [helpstring][id][propput][hidden] */ HRESULT STDMETHODCALLTYPE put_TWHandle( 
            /* [in] */ long lHWnd) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE ObtainTWLockIfUnused( 
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE ClearTWLock( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_G2Symbols( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_G2Symbols( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisconnectOnReset( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisconnectOnReset( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetContextLimit( 
            /* [in] */ long limit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Gateway4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Gateway4 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Gateway4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Gateway4 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Gateway4 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Gateway4 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Gateway4 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Gateway4 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IG2Gateway4 * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IG2Gateway4 * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Call )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *InputArguments,
            /* [retval][out] */ VARIANT *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *CallDeferred )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY * *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Start )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY * *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNamedObject )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateObjectInstance )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Connected )( 
            IG2Gateway4 * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsG2Running )( 
            IG2Gateway4 * This,
            /* [retval][out] */ VARIANT_BOOL *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2Location )( 
            IG2Gateway4 * This,
            /* [retval][out] */ BSTR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_G2Location )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InterfaceClass )( 
            IG2Gateway4 * This,
            /* [retval][out] */ BSTR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InterfaceClass )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RemoteInitializationString )( 
            IG2Gateway4 * This,
            /* [retval][out] */ BSTR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RemoteInitializationString )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CallTimeout )( 
            IG2Gateway4 * This,
            /* [retval][out] */ long *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CallTimeout )( 
            IG2Gateway4 * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *_FireEvents )( 
            IG2Gateway4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PostMessage )( 
            IG2Gateway4 * This,
            /* [in] */ VARIANT *Message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnStartPage )( 
            IG2Gateway4 * This,
            /* [in] */ IUnknown *piUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnEndPage )( 
            IG2Gateway4 * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *MakeG2ComVariable )( 
            IG2Gateway4 * This,
            /* [in] */ G2Type ComType,
            /* [in] */ SAFEARRAY * *inArgs,
            /* [retval][out] */ VARIANT *pResult);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DbgMsg )( 
            IG2Gateway4 * This,
            /* [in] */ BSTR msg);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2RunState )( 
            IG2Gateway4 * This,
            /* [retval][out] */ G2RunStateType *pVal);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_TWHandle )( 
            IG2Gateway4 * This,
            /* [retval][out] */ long *plHWnd);
        
        /* [helpstring][id][propput][hidden] */ HRESULT ( STDMETHODCALLTYPE *put_TWHandle )( 
            IG2Gateway4 * This,
            /* [in] */ long lHWnd);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *ObtainTWLockIfUnused )( 
            IG2Gateway4 * This,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *ClearTWLock )( 
            IG2Gateway4 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_G2Symbols )( 
            IG2Gateway4 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_G2Symbols )( 
            IG2Gateway4 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisconnectOnReset )( 
            IG2Gateway4 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisconnectOnReset )( 
            IG2Gateway4 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetContextLimit )( 
            IG2Gateway4 * This,
            /* [in] */ long limit);
        
        END_INTERFACE
    } IG2Gateway4Vtbl;

    interface IG2Gateway4
    {
        CONST_VTBL struct IG2Gateway4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway4_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Gateway4_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Gateway4_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Gateway4_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Gateway4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Gateway4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Gateway4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Gateway4_Connect(This,WaitFlag)	\
    ( (This)->lpVtbl -> Connect(This,WaitFlag) ) 

#define IG2Gateway4_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IG2Gateway4_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    ( (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments) ) 

#define IG2Gateway4_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    ( (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments) ) 

#define IG2Gateway4_Start(This,ProcedureName,Arguments)	\
    ( (This)->lpVtbl -> Start(This,ProcedureName,Arguments) ) 

#define IG2Gateway4_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    ( (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj) ) 

#define IG2Gateway4_CreateObjectInstance(This,ClassName,Obj)	\
    ( (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj) ) 

#define IG2Gateway4_get_IsG2Connected(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Connected(This,Val) ) 

#define IG2Gateway4_get_IsG2Running(This,Val)	\
    ( (This)->lpVtbl -> get_IsG2Running(This,Val) ) 

#define IG2Gateway4_get_G2Location(This,Location)	\
    ( (This)->lpVtbl -> get_G2Location(This,Location) ) 

#define IG2Gateway4_put_G2Location(This,Location)	\
    ( (This)->lpVtbl -> put_G2Location(This,Location) ) 

#define IG2Gateway4_get_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway4_put_InterfaceClass(This,InterfaceClassName)	\
    ( (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName) ) 

#define IG2Gateway4_get_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway4_put_RemoteInitializationString(This,InitializationString)	\
    ( (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString) ) 

#define IG2Gateway4_get_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> get_CallTimeout(This,MaxWait) ) 

#define IG2Gateway4_put_CallTimeout(This,MaxWait)	\
    ( (This)->lpVtbl -> put_CallTimeout(This,MaxWait) ) 

#define IG2Gateway4__FireEvents(This)	\
    ( (This)->lpVtbl -> _FireEvents(This) ) 

#define IG2Gateway4_PostMessage(This,Message)	\
    ( (This)->lpVtbl -> PostMessage(This,Message) ) 


#define IG2Gateway4_OnStartPage(This,piUnk)	\
    ( (This)->lpVtbl -> OnStartPage(This,piUnk) ) 

#define IG2Gateway4_OnEndPage(This)	\
    ( (This)->lpVtbl -> OnEndPage(This) ) 


#define IG2Gateway4_MakeG2ComVariable(This,ComType,inArgs,pResult)	\
    ( (This)->lpVtbl -> MakeG2ComVariable(This,ComType,inArgs,pResult) ) 

#define IG2Gateway4_DbgMsg(This,msg)	\
    ( (This)->lpVtbl -> DbgMsg(This,msg) ) 

#define IG2Gateway4_get_G2RunState(This,pVal)	\
    ( (This)->lpVtbl -> get_G2RunState(This,pVal) ) 


#define IG2Gateway4_get_TWHandle(This,plHWnd)	\
    ( (This)->lpVtbl -> get_TWHandle(This,plHWnd) ) 

#define IG2Gateway4_put_TWHandle(This,lHWnd)	\
    ( (This)->lpVtbl -> put_TWHandle(This,lHWnd) ) 

#define IG2Gateway4_ObtainTWLockIfUnused(This,pResult)	\
    ( (This)->lpVtbl -> ObtainTWLockIfUnused(This,pResult) ) 

#define IG2Gateway4_ClearTWLock(This)	\
    ( (This)->lpVtbl -> ClearTWLock(This) ) 

#define IG2Gateway4_get_G2Symbols(This,pVal)	\
    ( (This)->lpVtbl -> get_G2Symbols(This,pVal) ) 

#define IG2Gateway4_put_G2Symbols(This,newVal)	\
    ( (This)->lpVtbl -> put_G2Symbols(This,newVal) ) 

#define IG2Gateway4_get_DisconnectOnReset(This,pVal)	\
    ( (This)->lpVtbl -> get_DisconnectOnReset(This,pVal) ) 

#define IG2Gateway4_put_DisconnectOnReset(This,newVal)	\
    ( (This)->lpVtbl -> put_DisconnectOnReset(This,newVal) ) 

#define IG2Gateway4_SetContextLimit(This,limit)	\
    ( (This)->lpVtbl -> SetContextLimit(This,limit) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Gateway4_INTERFACE_DEFINED__ */


#ifndef __G2ComObject_INTERFACE_DEFINED__
#define __G2ComObject_INTERFACE_DEFINED__

/* interface G2ComObject */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_G2ComObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FCEB8041-EF78-4be6-ADC8-51C173F65484")
    G2ComObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget][hidden] */ HRESULT STDMETHODCALLTYPE get_WhatAmI( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE Duplicate( 
            /* [retval][out] */ IUnknown **pNewObj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct G2ComObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            G2ComObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            G2ComObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            G2ComObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            G2ComObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            G2ComObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            G2ComObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            G2ComObject * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            G2ComObject * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            G2ComObject * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        END_INTERFACE
    } G2ComObjectVtbl;

    interface G2ComObject
    {
        CONST_VTBL struct G2ComObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define G2ComObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define G2ComObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define G2ComObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define G2ComObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define G2ComObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define G2ComObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define G2ComObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define G2ComObject_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define G2ComObject_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __G2ComObject_INTERFACE_DEFINED__ */


#ifndef __IG2StructureEntry_INTERFACE_DEFINED__
#define __IG2StructureEntry_INTERFACE_DEFINED__

/* interface IG2StructureEntry */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2StructureEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4E20F9C-7ECC-4EE8-8FEF-6AB6D3D80943")
    IG2StructureEntry : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2StructureEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2StructureEntry * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2StructureEntry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2StructureEntry * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2StructureEntry * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2StructureEntry * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2StructureEntry * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2StructureEntry * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2StructureEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2StructureEntry * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IG2StructureEntry * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IG2StructureEntry * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2StructureEntry * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2StructureEntry * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IG2StructureEntryVtbl;

    interface IG2StructureEntry
    {
        CONST_VTBL struct IG2StructureEntryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2StructureEntry_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2StructureEntry_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2StructureEntry_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2StructureEntry_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2StructureEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2StructureEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2StructureEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2StructureEntry_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2StructureEntry_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2StructureEntry_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IG2StructureEntry_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define IG2StructureEntry_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IG2StructureEntry_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2StructureEntry_INTERFACE_DEFINED__ */


#ifndef __IG2Structure_INTERFACE_DEFINED__
#define __IG2Structure_INTERFACE_DEFINED__

/* interface IG2Structure */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Structure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A59A1DFB-3711-4893-B3F4-D9FD0B824C23")
    IG2Structure : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ VARIANT *pItem) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ VARIANT index,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ SAFEARRAY * *InputArguments) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT index) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Names( 
            /* [retval][out] */ SAFEARRAY * *nameList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Values( 
            /* [retval][out] */ SAFEARRAY * *valueList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2StructureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Structure * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Structure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Structure * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Structure * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Structure * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Structure * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Structure * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Structure * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Structure * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2Structure * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ VARIANT *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2Structure * This,
            /* [in] */ VARIANT index,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IG2Structure * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IG2Structure * This,
            /* [in] */ SAFEARRAY * *InputArguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IG2Structure * This,
            /* [in] */ VARIANT index);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IG2Structure * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Names )( 
            IG2Structure * This,
            /* [retval][out] */ SAFEARRAY * *nameList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Values )( 
            IG2Structure * This,
            /* [retval][out] */ SAFEARRAY * *valueList);
        
        END_INTERFACE
    } IG2StructureVtbl;

    interface IG2Structure
    {
        CONST_VTBL struct IG2StructureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Structure_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Structure_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Structure_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Structure_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Structure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Structure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Structure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Structure_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Structure_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Structure_get_Item(This,index,pItem)	\
    ( (This)->lpVtbl -> get_Item(This,index,pItem) ) 

#define IG2Structure_put_Item(This,index,value)	\
    ( (This)->lpVtbl -> put_Item(This,index,value) ) 

#define IG2Structure_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IG2Structure_Add(This,InputArguments)	\
    ( (This)->lpVtbl -> Add(This,InputArguments) ) 

#define IG2Structure_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IG2Structure_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IG2Structure_Names(This,nameList)	\
    ( (This)->lpVtbl -> Names(This,nameList) ) 

#define IG2Structure_Values(This,valueList)	\
    ( (This)->lpVtbl -> Values(This,valueList) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Structure_INTERFACE_DEFINED__ */


#ifndef __IG2Item_INTERFACE_DEFINED__
#define __IG2Item_INTERFACE_DEFINED__

/* interface IG2Item */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Item;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4A49E08-2ADA-49D2-BBCB-7FDD7EBB6D86")
    IG2Item : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT *pItem) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClassName( 
            /* [retval][out] */ BSTR *pClassName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClassName( 
            /* [in] */ BSTR bstrClassName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pItemName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR ItemName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ G2Type *pGsiType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ G2Type GsiType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pGsiType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT GsiType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT varIdx) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrNames( 
            /* [retval][out] */ SAFEARRAY * *attrNameList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrValues( 
            /* [retval][out] */ SAFEARRAY * *attrValList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrTypes( 
            /* [retval][out] */ SAFEARRAY * *attrTypeList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Symbolize( 
            VARIANT idx,
            VARIANT_BOOL flgSym) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ long pItem) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Git( 
            /* [out] */ long *pGsiItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Item * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Item * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Item * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Item * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Item * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Item * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Item * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Item * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Item * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2Item * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2Item * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClassName )( 
            IG2Item * This,
            /* [retval][out] */ BSTR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClassName )( 
            IG2Item * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IG2Item * This,
            /* [retval][out] */ BSTR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IG2Item * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IG2Item * This,
            /* [retval][out] */ G2Type *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IG2Item * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2Item * This,
            /* [retval][out] */ VARIANT *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2Item * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IG2Item * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IG2Item * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IG2Item * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IG2Item * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrNames )( 
            IG2Item * This,
            /* [retval][out] */ SAFEARRAY * *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrValues )( 
            IG2Item * This,
            /* [retval][out] */ SAFEARRAY * *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrTypes )( 
            IG2Item * This,
            /* [retval][out] */ SAFEARRAY * *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Symbolize )( 
            IG2Item * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2Item * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Git )( 
            IG2Item * This,
            /* [out] */ long *pGsiItem);
        
        END_INTERFACE
    } IG2ItemVtbl;

    interface IG2Item
    {
        CONST_VTBL struct IG2ItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Item_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Item_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Item_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Item_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Item_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Item_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Item_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Item_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Item_get_Item(This,Idx,pItem)	\
    ( (This)->lpVtbl -> get_Item(This,Idx,pItem) ) 

#define IG2Item_put_Item(This,Idx,value)	\
    ( (This)->lpVtbl -> put_Item(This,Idx,value) ) 

#define IG2Item_get_ClassName(This,pClassName)	\
    ( (This)->lpVtbl -> get_ClassName(This,pClassName) ) 

#define IG2Item_put_ClassName(This,bstrClassName)	\
    ( (This)->lpVtbl -> put_ClassName(This,bstrClassName) ) 

#define IG2Item_get_Name(This,pItemName)	\
    ( (This)->lpVtbl -> get_Name(This,pItemName) ) 

#define IG2Item_put_Name(This,ItemName)	\
    ( (This)->lpVtbl -> put_Name(This,ItemName) ) 

#define IG2Item_get_Type(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Type(This,pGsiType) ) 

#define IG2Item_put_Type(This,GsiType)	\
    ( (This)->lpVtbl -> put_Type(This,GsiType) ) 

#define IG2Item_get_Value(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Value(This,pGsiType) ) 

#define IG2Item_put_Value(This,GsiType)	\
    ( (This)->lpVtbl -> put_Value(This,GsiType) ) 

#define IG2Item_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IG2Item_Add(This,atName,atVal)	\
    ( (This)->lpVtbl -> Add(This,atName,atVal) ) 

#define IG2Item_Remove(This,varIdx)	\
    ( (This)->lpVtbl -> Remove(This,varIdx) ) 

#define IG2Item_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IG2Item_get_AttrNames(This,attrNameList)	\
    ( (This)->lpVtbl -> get_AttrNames(This,attrNameList) ) 

#define IG2Item_get_AttrValues(This,attrValList)	\
    ( (This)->lpVtbl -> get_AttrValues(This,attrValList) ) 

#define IG2Item_get_AttrTypes(This,attrTypeList)	\
    ( (This)->lpVtbl -> get_AttrTypes(This,attrTypeList) ) 

#define IG2Item_Symbolize(This,idx,flgSym)	\
    ( (This)->lpVtbl -> Symbolize(This,idx,flgSym) ) 

#define IG2Item_Init(This,pItem)	\
    ( (This)->lpVtbl -> Init(This,pItem) ) 

#define IG2Item_Git(This,pGsiItem)	\
    ( (This)->lpVtbl -> Git(This,pGsiItem) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Item_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_G2Com_0000_0008 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_0008_v0_0_s_ifspec;

#ifndef __IG2Item2_INTERFACE_DEFINED__
#define __IG2Item2_INTERFACE_DEFINED__

/* interface IG2Item2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Item2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E22A2CD-4E8C-4f5d-BE79-39D6CCC804F3")
    IG2Item2 : public IG2Item
    {
    public:
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Inix( 
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef *pRef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LPDISPATCH pAxL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Linked( 
            /* [retval][out] */ VARIANT_BOOL *pflgLinked) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Link( 
            /* [in] */ IG2ItemRef *pItemRef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Unlink( void) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Unhandle( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrType( 
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Reference( 
            /* [retval][out] */ IG2ItemRef **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToAttributeModification( 
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToDeletion( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToIconColorChange( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToCustomEvent( 
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToValueChange( 
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT *subscriptionHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromAttributeModification( 
            /* [in] */ VARIANT FromWhat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromDeletion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromIconColorChange( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromCustomEvent( 
            VARIANT EventNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromValueChange( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Subscriptions( 
            /* [retval][out] */ VARIANT *ArrayOfSubscriptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Item2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Item2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Item2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Item2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Item2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Item2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Item2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Item2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Item2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Item2 * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2Item2 * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2Item2 * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClassName )( 
            IG2Item2 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClassName )( 
            IG2Item2 * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IG2Item2 * This,
            /* [retval][out] */ BSTR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IG2Item2 * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IG2Item2 * This,
            /* [retval][out] */ G2Type *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IG2Item2 * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2Item2 * This,
            /* [retval][out] */ VARIANT *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2Item2 * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IG2Item2 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IG2Item2 * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IG2Item2 * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IG2Item2 * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrNames )( 
            IG2Item2 * This,
            /* [retval][out] */ SAFEARRAY * *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrValues )( 
            IG2Item2 * This,
            /* [retval][out] */ SAFEARRAY * *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrTypes )( 
            IG2Item2 * This,
            /* [retval][out] */ SAFEARRAY * *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Symbolize )( 
            IG2Item2 * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2Item2 * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Git )( 
            IG2Item2 * This,
            /* [out] */ long *pGsiItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Inix )( 
            IG2Item2 * This,
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef *pRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IG2Item2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IG2Item2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IG2Item2 * This,
            /* [in] */ LPDISPATCH pAxL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IG2Item2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Linked )( 
            IG2Item2 * This,
            /* [retval][out] */ VARIANT_BOOL *pflgLinked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Link )( 
            IG2Item2 * This,
            /* [in] */ IG2ItemRef *pItemRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unlink )( 
            IG2Item2 * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unhandle )( 
            IG2Item2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrType )( 
            IG2Item2 * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Reference )( 
            IG2Item2 * This,
            /* [retval][out] */ IG2ItemRef **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToAttributeModification )( 
            IG2Item2 * This,
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToDeletion )( 
            IG2Item2 * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToIconColorChange )( 
            IG2Item2 * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToCustomEvent )( 
            IG2Item2 * This,
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToValueChange )( 
            IG2Item2 * This,
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT *subscriptionHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromAttributeModification )( 
            IG2Item2 * This,
            /* [in] */ VARIANT FromWhat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromDeletion )( 
            IG2Item2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromIconColorChange )( 
            IG2Item2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromCustomEvent )( 
            IG2Item2 * This,
            VARIANT EventNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromAll )( 
            IG2Item2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromValueChange )( 
            IG2Item2 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Subscriptions )( 
            IG2Item2 * This,
            /* [retval][out] */ VARIANT *ArrayOfSubscriptions);
        
        END_INTERFACE
    } IG2Item2Vtbl;

    interface IG2Item2
    {
        CONST_VTBL struct IG2Item2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Item2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Item2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Item2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Item2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Item2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Item2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Item2_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Item2_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Item2_get_Item(This,Idx,pItem)	\
    ( (This)->lpVtbl -> get_Item(This,Idx,pItem) ) 

#define IG2Item2_put_Item(This,Idx,value)	\
    ( (This)->lpVtbl -> put_Item(This,Idx,value) ) 

#define IG2Item2_get_ClassName(This,pClassName)	\
    ( (This)->lpVtbl -> get_ClassName(This,pClassName) ) 

#define IG2Item2_put_ClassName(This,bstrClassName)	\
    ( (This)->lpVtbl -> put_ClassName(This,bstrClassName) ) 

#define IG2Item2_get_Name(This,pItemName)	\
    ( (This)->lpVtbl -> get_Name(This,pItemName) ) 

#define IG2Item2_put_Name(This,ItemName)	\
    ( (This)->lpVtbl -> put_Name(This,ItemName) ) 

#define IG2Item2_get_Type(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Type(This,pGsiType) ) 

#define IG2Item2_put_Type(This,GsiType)	\
    ( (This)->lpVtbl -> put_Type(This,GsiType) ) 

#define IG2Item2_get_Value(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Value(This,pGsiType) ) 

#define IG2Item2_put_Value(This,GsiType)	\
    ( (This)->lpVtbl -> put_Value(This,GsiType) ) 

#define IG2Item2_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IG2Item2_Add(This,atName,atVal)	\
    ( (This)->lpVtbl -> Add(This,atName,atVal) ) 

#define IG2Item2_Remove(This,varIdx)	\
    ( (This)->lpVtbl -> Remove(This,varIdx) ) 

#define IG2Item2_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IG2Item2_get_AttrNames(This,attrNameList)	\
    ( (This)->lpVtbl -> get_AttrNames(This,attrNameList) ) 

#define IG2Item2_get_AttrValues(This,attrValList)	\
    ( (This)->lpVtbl -> get_AttrValues(This,attrValList) ) 

#define IG2Item2_get_AttrTypes(This,attrTypeList)	\
    ( (This)->lpVtbl -> get_AttrTypes(This,attrTypeList) ) 

#define IG2Item2_Symbolize(This,idx,flgSym)	\
    ( (This)->lpVtbl -> Symbolize(This,idx,flgSym) ) 

#define IG2Item2_Init(This,pItem)	\
    ( (This)->lpVtbl -> Init(This,pItem) ) 

#define IG2Item2_Git(This,pGsiItem)	\
    ( (This)->lpVtbl -> Git(This,pGsiItem) ) 


#define IG2Item2_Inix(This,pItem,pRef)	\
    ( (This)->lpVtbl -> Inix(This,pItem,pRef) ) 

#define IG2Item2_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IG2Item2_Update(This)	\
    ( (This)->lpVtbl -> Update(This) ) 

#define IG2Item2_Create(This,pAxL)	\
    ( (This)->lpVtbl -> Create(This,pAxL) ) 

#define IG2Item2_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IG2Item2_get_Linked(This,pflgLinked)	\
    ( (This)->lpVtbl -> get_Linked(This,pflgLinked) ) 

#define IG2Item2_Link(This,pItemRef)	\
    ( (This)->lpVtbl -> Link(This,pItemRef) ) 

#define IG2Item2_Unlink(This)	\
    ( (This)->lpVtbl -> Unlink(This) ) 

#define IG2Item2_Unhandle(This)	\
    ( (This)->lpVtbl -> Unhandle(This) ) 

#define IG2Item2_get_AttrType(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_AttrType(This,idx,pVal) ) 

#define IG2Item2_get_Reference(This,pVal)	\
    ( (This)->lpVtbl -> get_Reference(This,pVal) ) 

#define IG2Item2_SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)	\
    ( (This)->lpVtbl -> SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls) ) 

#define IG2Item2_SubscribeToDeletion(This,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToDeletion(This,userData,SubscripHndl) ) 

#define IG2Item2_SubscribeToIconColorChange(This,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToIconColorChange(This,userData,SubscripHndl) ) 

#define IG2Item2_SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToCustomEvent(This,EventName,userData,SubscripHndl) ) 

#define IG2Item2_SubscribeToValueChange(This,userData,subscriptionHandle)	\
    ( (This)->lpVtbl -> SubscribeToValueChange(This,userData,subscriptionHandle) ) 

#define IG2Item2_UnsubscribeFromAttributeModification(This,FromWhat)	\
    ( (This)->lpVtbl -> UnsubscribeFromAttributeModification(This,FromWhat) ) 

#define IG2Item2_UnsubscribeFromDeletion(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromDeletion(This) ) 

#define IG2Item2_UnsubscribeFromIconColorChange(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromIconColorChange(This) ) 

#define IG2Item2_UnsubscribeFromCustomEvent(This,EventNames)	\
    ( (This)->lpVtbl -> UnsubscribeFromCustomEvent(This,EventNames) ) 

#define IG2Item2_UnsubscribeFromAll(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromAll(This) ) 

#define IG2Item2_UnsubscribeFromValueChange(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromValueChange(This) ) 

#define IG2Item2_Subscriptions(This,ArrayOfSubscriptions)	\
    ( (This)->lpVtbl -> Subscriptions(This,ArrayOfSubscriptions) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Item2_INTERFACE_DEFINED__ */


#ifndef __IG2Item3_INTERFACE_DEFINED__
#define __IG2Item3_INTERFACE_DEFINED__

/* interface IG2Item3 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Item3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("159B27B6-6BB3-4317-A5E5-FD55001D3E9F")
    IG2Item3 : public IG2Item2
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Icon( 
            /* [in] */ long BackgroundColor,
            /* [retval][out] */ LPDISPATCH *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Item3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Item3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Item3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Item3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Item3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Item3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Item3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Item3 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Item3 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Item3 * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2Item3 * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2Item3 * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClassName )( 
            IG2Item3 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClassName )( 
            IG2Item3 * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IG2Item3 * This,
            /* [retval][out] */ BSTR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IG2Item3 * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IG2Item3 * This,
            /* [retval][out] */ G2Type *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IG2Item3 * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2Item3 * This,
            /* [retval][out] */ VARIANT *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2Item3 * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IG2Item3 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IG2Item3 * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IG2Item3 * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IG2Item3 * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrNames )( 
            IG2Item3 * This,
            /* [retval][out] */ SAFEARRAY * *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrValues )( 
            IG2Item3 * This,
            /* [retval][out] */ SAFEARRAY * *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrTypes )( 
            IG2Item3 * This,
            /* [retval][out] */ SAFEARRAY * *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Symbolize )( 
            IG2Item3 * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2Item3 * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Git )( 
            IG2Item3 * This,
            /* [out] */ long *pGsiItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Inix )( 
            IG2Item3 * This,
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef *pRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IG2Item3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IG2Item3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IG2Item3 * This,
            /* [in] */ LPDISPATCH pAxL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IG2Item3 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Linked )( 
            IG2Item3 * This,
            /* [retval][out] */ VARIANT_BOOL *pflgLinked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Link )( 
            IG2Item3 * This,
            /* [in] */ IG2ItemRef *pItemRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unlink )( 
            IG2Item3 * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unhandle )( 
            IG2Item3 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrType )( 
            IG2Item3 * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Reference )( 
            IG2Item3 * This,
            /* [retval][out] */ IG2ItemRef **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToAttributeModification )( 
            IG2Item3 * This,
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToDeletion )( 
            IG2Item3 * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToIconColorChange )( 
            IG2Item3 * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToCustomEvent )( 
            IG2Item3 * This,
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToValueChange )( 
            IG2Item3 * This,
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT *subscriptionHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromAttributeModification )( 
            IG2Item3 * This,
            /* [in] */ VARIANT FromWhat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromDeletion )( 
            IG2Item3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromIconColorChange )( 
            IG2Item3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromCustomEvent )( 
            IG2Item3 * This,
            VARIANT EventNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromAll )( 
            IG2Item3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromValueChange )( 
            IG2Item3 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Subscriptions )( 
            IG2Item3 * This,
            /* [retval][out] */ VARIANT *ArrayOfSubscriptions);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Icon )( 
            IG2Item3 * This,
            /* [in] */ long BackgroundColor,
            /* [retval][out] */ LPDISPATCH *pVal);
        
        END_INTERFACE
    } IG2Item3Vtbl;

    interface IG2Item3
    {
        CONST_VTBL struct IG2Item3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Item3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Item3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Item3_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Item3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Item3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Item3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Item3_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Item3_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Item3_get_Item(This,Idx,pItem)	\
    ( (This)->lpVtbl -> get_Item(This,Idx,pItem) ) 

#define IG2Item3_put_Item(This,Idx,value)	\
    ( (This)->lpVtbl -> put_Item(This,Idx,value) ) 

#define IG2Item3_get_ClassName(This,pClassName)	\
    ( (This)->lpVtbl -> get_ClassName(This,pClassName) ) 

#define IG2Item3_put_ClassName(This,bstrClassName)	\
    ( (This)->lpVtbl -> put_ClassName(This,bstrClassName) ) 

#define IG2Item3_get_Name(This,pItemName)	\
    ( (This)->lpVtbl -> get_Name(This,pItemName) ) 

#define IG2Item3_put_Name(This,ItemName)	\
    ( (This)->lpVtbl -> put_Name(This,ItemName) ) 

#define IG2Item3_get_Type(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Type(This,pGsiType) ) 

#define IG2Item3_put_Type(This,GsiType)	\
    ( (This)->lpVtbl -> put_Type(This,GsiType) ) 

#define IG2Item3_get_Value(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Value(This,pGsiType) ) 

#define IG2Item3_put_Value(This,GsiType)	\
    ( (This)->lpVtbl -> put_Value(This,GsiType) ) 

#define IG2Item3_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IG2Item3_Add(This,atName,atVal)	\
    ( (This)->lpVtbl -> Add(This,atName,atVal) ) 

#define IG2Item3_Remove(This,varIdx)	\
    ( (This)->lpVtbl -> Remove(This,varIdx) ) 

#define IG2Item3_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IG2Item3_get_AttrNames(This,attrNameList)	\
    ( (This)->lpVtbl -> get_AttrNames(This,attrNameList) ) 

#define IG2Item3_get_AttrValues(This,attrValList)	\
    ( (This)->lpVtbl -> get_AttrValues(This,attrValList) ) 

#define IG2Item3_get_AttrTypes(This,attrTypeList)	\
    ( (This)->lpVtbl -> get_AttrTypes(This,attrTypeList) ) 

#define IG2Item3_Symbolize(This,idx,flgSym)	\
    ( (This)->lpVtbl -> Symbolize(This,idx,flgSym) ) 

#define IG2Item3_Init(This,pItem)	\
    ( (This)->lpVtbl -> Init(This,pItem) ) 

#define IG2Item3_Git(This,pGsiItem)	\
    ( (This)->lpVtbl -> Git(This,pGsiItem) ) 


#define IG2Item3_Inix(This,pItem,pRef)	\
    ( (This)->lpVtbl -> Inix(This,pItem,pRef) ) 

#define IG2Item3_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IG2Item3_Update(This)	\
    ( (This)->lpVtbl -> Update(This) ) 

#define IG2Item3_Create(This,pAxL)	\
    ( (This)->lpVtbl -> Create(This,pAxL) ) 

#define IG2Item3_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IG2Item3_get_Linked(This,pflgLinked)	\
    ( (This)->lpVtbl -> get_Linked(This,pflgLinked) ) 

#define IG2Item3_Link(This,pItemRef)	\
    ( (This)->lpVtbl -> Link(This,pItemRef) ) 

#define IG2Item3_Unlink(This)	\
    ( (This)->lpVtbl -> Unlink(This) ) 

#define IG2Item3_Unhandle(This)	\
    ( (This)->lpVtbl -> Unhandle(This) ) 

#define IG2Item3_get_AttrType(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_AttrType(This,idx,pVal) ) 

#define IG2Item3_get_Reference(This,pVal)	\
    ( (This)->lpVtbl -> get_Reference(This,pVal) ) 

#define IG2Item3_SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)	\
    ( (This)->lpVtbl -> SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls) ) 

#define IG2Item3_SubscribeToDeletion(This,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToDeletion(This,userData,SubscripHndl) ) 

#define IG2Item3_SubscribeToIconColorChange(This,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToIconColorChange(This,userData,SubscripHndl) ) 

#define IG2Item3_SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToCustomEvent(This,EventName,userData,SubscripHndl) ) 

#define IG2Item3_SubscribeToValueChange(This,userData,subscriptionHandle)	\
    ( (This)->lpVtbl -> SubscribeToValueChange(This,userData,subscriptionHandle) ) 

#define IG2Item3_UnsubscribeFromAttributeModification(This,FromWhat)	\
    ( (This)->lpVtbl -> UnsubscribeFromAttributeModification(This,FromWhat) ) 

#define IG2Item3_UnsubscribeFromDeletion(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromDeletion(This) ) 

#define IG2Item3_UnsubscribeFromIconColorChange(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromIconColorChange(This) ) 

#define IG2Item3_UnsubscribeFromCustomEvent(This,EventNames)	\
    ( (This)->lpVtbl -> UnsubscribeFromCustomEvent(This,EventNames) ) 

#define IG2Item3_UnsubscribeFromAll(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromAll(This) ) 

#define IG2Item3_UnsubscribeFromValueChange(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromValueChange(This) ) 

#define IG2Item3_Subscriptions(This,ArrayOfSubscriptions)	\
    ( (This)->lpVtbl -> Subscriptions(This,ArrayOfSubscriptions) ) 


#define IG2Item3_get_Icon(This,BackgroundColor,pVal)	\
    ( (This)->lpVtbl -> get_Icon(This,BackgroundColor,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Item3_INTERFACE_DEFINED__ */


#ifndef __IG2Item4_INTERFACE_DEFINED__
#define __IG2Item4_INTERFACE_DEFINED__

/* interface IG2Item4 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Item4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D8B90DC4-74BB-4775-983C-02137E2E283B")
    IG2Item4 : public IG2Item3
    {
    public:
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE Init2( 
            /* [in] */ long pDatum) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE Init3( 
            /* [in] */ long pDatum,
            /* [in] */ IG2ItemRef *pRef) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE Git2( 
            /* [out] */ long *ppDatum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Item4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Item4 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Item4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Item4 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Item4 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Item4 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Item4 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Item4 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Item4 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Item4 * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2Item4 * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2Item4 * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClassName )( 
            IG2Item4 * This,
            /* [retval][out] */ BSTR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClassName )( 
            IG2Item4 * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IG2Item4 * This,
            /* [retval][out] */ BSTR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IG2Item4 * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IG2Item4 * This,
            /* [retval][out] */ G2Type *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IG2Item4 * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2Item4 * This,
            /* [retval][out] */ VARIANT *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2Item4 * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IG2Item4 * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IG2Item4 * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IG2Item4 * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IG2Item4 * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrNames )( 
            IG2Item4 * This,
            /* [retval][out] */ SAFEARRAY * *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrValues )( 
            IG2Item4 * This,
            /* [retval][out] */ SAFEARRAY * *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrTypes )( 
            IG2Item4 * This,
            /* [retval][out] */ SAFEARRAY * *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Symbolize )( 
            IG2Item4 * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2Item4 * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Git )( 
            IG2Item4 * This,
            /* [out] */ long *pGsiItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Inix )( 
            IG2Item4 * This,
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef *pRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IG2Item4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Update )( 
            IG2Item4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IG2Item4 * This,
            /* [in] */ LPDISPATCH pAxL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            IG2Item4 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Linked )( 
            IG2Item4 * This,
            /* [retval][out] */ VARIANT_BOOL *pflgLinked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Link )( 
            IG2Item4 * This,
            /* [in] */ IG2ItemRef *pItemRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unlink )( 
            IG2Item4 * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unhandle )( 
            IG2Item4 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttrType )( 
            IG2Item4 * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Reference )( 
            IG2Item4 * This,
            /* [retval][out] */ IG2ItemRef **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToAttributeModification )( 
            IG2Item4 * This,
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToDeletion )( 
            IG2Item4 * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToIconColorChange )( 
            IG2Item4 * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToCustomEvent )( 
            IG2Item4 * This,
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToValueChange )( 
            IG2Item4 * This,
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT *subscriptionHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromAttributeModification )( 
            IG2Item4 * This,
            /* [in] */ VARIANT FromWhat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromDeletion )( 
            IG2Item4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromIconColorChange )( 
            IG2Item4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromCustomEvent )( 
            IG2Item4 * This,
            VARIANT EventNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromAll )( 
            IG2Item4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromValueChange )( 
            IG2Item4 * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Subscriptions )( 
            IG2Item4 * This,
            /* [retval][out] */ VARIANT *ArrayOfSubscriptions);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Icon )( 
            IG2Item4 * This,
            /* [in] */ long BackgroundColor,
            /* [retval][out] */ LPDISPATCH *pVal);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Init2 )( 
            IG2Item4 * This,
            /* [in] */ long pDatum);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Init3 )( 
            IG2Item4 * This,
            /* [in] */ long pDatum,
            /* [in] */ IG2ItemRef *pRef);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE *Git2 )( 
            IG2Item4 * This,
            /* [out] */ long *ppDatum);
        
        END_INTERFACE
    } IG2Item4Vtbl;

    interface IG2Item4
    {
        CONST_VTBL struct IG2Item4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item4_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Item4_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Item4_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Item4_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Item4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Item4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Item4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Item4_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Item4_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Item4_get_Item(This,Idx,pItem)	\
    ( (This)->lpVtbl -> get_Item(This,Idx,pItem) ) 

#define IG2Item4_put_Item(This,Idx,value)	\
    ( (This)->lpVtbl -> put_Item(This,Idx,value) ) 

#define IG2Item4_get_ClassName(This,pClassName)	\
    ( (This)->lpVtbl -> get_ClassName(This,pClassName) ) 

#define IG2Item4_put_ClassName(This,bstrClassName)	\
    ( (This)->lpVtbl -> put_ClassName(This,bstrClassName) ) 

#define IG2Item4_get_Name(This,pItemName)	\
    ( (This)->lpVtbl -> get_Name(This,pItemName) ) 

#define IG2Item4_put_Name(This,ItemName)	\
    ( (This)->lpVtbl -> put_Name(This,ItemName) ) 

#define IG2Item4_get_Type(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Type(This,pGsiType) ) 

#define IG2Item4_put_Type(This,GsiType)	\
    ( (This)->lpVtbl -> put_Type(This,GsiType) ) 

#define IG2Item4_get_Value(This,pGsiType)	\
    ( (This)->lpVtbl -> get_Value(This,pGsiType) ) 

#define IG2Item4_put_Value(This,GsiType)	\
    ( (This)->lpVtbl -> put_Value(This,GsiType) ) 

#define IG2Item4_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IG2Item4_Add(This,atName,atVal)	\
    ( (This)->lpVtbl -> Add(This,atName,atVal) ) 

#define IG2Item4_Remove(This,varIdx)	\
    ( (This)->lpVtbl -> Remove(This,varIdx) ) 

#define IG2Item4_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define IG2Item4_get_AttrNames(This,attrNameList)	\
    ( (This)->lpVtbl -> get_AttrNames(This,attrNameList) ) 

#define IG2Item4_get_AttrValues(This,attrValList)	\
    ( (This)->lpVtbl -> get_AttrValues(This,attrValList) ) 

#define IG2Item4_get_AttrTypes(This,attrTypeList)	\
    ( (This)->lpVtbl -> get_AttrTypes(This,attrTypeList) ) 

#define IG2Item4_Symbolize(This,idx,flgSym)	\
    ( (This)->lpVtbl -> Symbolize(This,idx,flgSym) ) 

#define IG2Item4_Init(This,pItem)	\
    ( (This)->lpVtbl -> Init(This,pItem) ) 

#define IG2Item4_Git(This,pGsiItem)	\
    ( (This)->lpVtbl -> Git(This,pGsiItem) ) 


#define IG2Item4_Inix(This,pItem,pRef)	\
    ( (This)->lpVtbl -> Inix(This,pItem,pRef) ) 

#define IG2Item4_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IG2Item4_Update(This)	\
    ( (This)->lpVtbl -> Update(This) ) 

#define IG2Item4_Create(This,pAxL)	\
    ( (This)->lpVtbl -> Create(This,pAxL) ) 

#define IG2Item4_Delete(This)	\
    ( (This)->lpVtbl -> Delete(This) ) 

#define IG2Item4_get_Linked(This,pflgLinked)	\
    ( (This)->lpVtbl -> get_Linked(This,pflgLinked) ) 

#define IG2Item4_Link(This,pItemRef)	\
    ( (This)->lpVtbl -> Link(This,pItemRef) ) 

#define IG2Item4_Unlink(This)	\
    ( (This)->lpVtbl -> Unlink(This) ) 

#define IG2Item4_Unhandle(This)	\
    ( (This)->lpVtbl -> Unhandle(This) ) 

#define IG2Item4_get_AttrType(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_AttrType(This,idx,pVal) ) 

#define IG2Item4_get_Reference(This,pVal)	\
    ( (This)->lpVtbl -> get_Reference(This,pVal) ) 

#define IG2Item4_SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)	\
    ( (This)->lpVtbl -> SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls) ) 

#define IG2Item4_SubscribeToDeletion(This,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToDeletion(This,userData,SubscripHndl) ) 

#define IG2Item4_SubscribeToIconColorChange(This,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToIconColorChange(This,userData,SubscripHndl) ) 

#define IG2Item4_SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)	\
    ( (This)->lpVtbl -> SubscribeToCustomEvent(This,EventName,userData,SubscripHndl) ) 

#define IG2Item4_SubscribeToValueChange(This,userData,subscriptionHandle)	\
    ( (This)->lpVtbl -> SubscribeToValueChange(This,userData,subscriptionHandle) ) 

#define IG2Item4_UnsubscribeFromAttributeModification(This,FromWhat)	\
    ( (This)->lpVtbl -> UnsubscribeFromAttributeModification(This,FromWhat) ) 

#define IG2Item4_UnsubscribeFromDeletion(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromDeletion(This) ) 

#define IG2Item4_UnsubscribeFromIconColorChange(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromIconColorChange(This) ) 

#define IG2Item4_UnsubscribeFromCustomEvent(This,EventNames)	\
    ( (This)->lpVtbl -> UnsubscribeFromCustomEvent(This,EventNames) ) 

#define IG2Item4_UnsubscribeFromAll(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromAll(This) ) 

#define IG2Item4_UnsubscribeFromValueChange(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromValueChange(This) ) 

#define IG2Item4_Subscriptions(This,ArrayOfSubscriptions)	\
    ( (This)->lpVtbl -> Subscriptions(This,ArrayOfSubscriptions) ) 


#define IG2Item4_get_Icon(This,BackgroundColor,pVal)	\
    ( (This)->lpVtbl -> get_Icon(This,BackgroundColor,pVal) ) 


#define IG2Item4_Init2(This,pDatum)	\
    ( (This)->lpVtbl -> Init2(This,pDatum) ) 

#define IG2Item4_Init3(This,pDatum,pRef)	\
    ( (This)->lpVtbl -> Init3(This,pDatum,pRef) ) 

#define IG2Item4_Git2(This,ppDatum)	\
    ( (This)->lpVtbl -> Git2(This,ppDatum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Item4_INTERFACE_DEFINED__ */


#ifndef __IG2Attribute_INTERFACE_DEFINED__
#define __IG2Attribute_INTERFACE_DEFINED__

/* interface IG2Attribute */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Attribute;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45BB4FD7-576B-4672-923E-15E7C13D2C76")
    IG2Attribute : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT AttrVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ G2Type *pType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ G2Type nType) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ long pGsiAttr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2AttributeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Attribute * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Attribute * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Attribute * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Attribute * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Attribute * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Attribute * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Attribute * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Attribute * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Attribute * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IG2Attribute * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2Attribute * This,
            /* [in] */ VARIANT AttrVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2Attribute * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IG2Attribute * This,
            /* [retval][out] */ G2Type *pType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IG2Attribute * This,
            /* [in] */ G2Type nType);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2Attribute * This,
            /* [in] */ long pGsiAttr);
        
        END_INTERFACE
    } IG2AttributeVtbl;

    interface IG2Attribute
    {
        CONST_VTBL struct IG2AttributeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Attribute_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Attribute_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Attribute_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Attribute_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Attribute_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Attribute_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Attribute_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Attribute_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Attribute_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Attribute_get_Name(This,pName)	\
    ( (This)->lpVtbl -> get_Name(This,pName) ) 

#define IG2Attribute_put_Value(This,AttrVal)	\
    ( (This)->lpVtbl -> put_Value(This,AttrVal) ) 

#define IG2Attribute_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IG2Attribute_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IG2Attribute_put_Type(This,nType)	\
    ( (This)->lpVtbl -> put_Type(This,nType) ) 

#define IG2Attribute_Init(This,pGsiAttr)	\
    ( (This)->lpVtbl -> Init(This,pGsiAttr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Attribute_INTERFACE_DEFINED__ */


#ifndef __IG2ListOrArray_INTERFACE_DEFINED__
#define __IG2ListOrArray_INTERFACE_DEFINED__

/* interface IG2ListOrArray */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2ListOrArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4A80A9FD-41DF-4b49-8740-13C43E350F29")
    IG2ListOrArray : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long idx,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ long idx,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ G2Type *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ G2Type newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ long pGsiItem) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ long idx,
            /* [in] */ VARIANT varX) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ long idx,
            /* [in] */ VARIANT varX) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT varX) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long idx) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ListOrArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2ListOrArray * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2ListOrArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2ListOrArray * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2ListOrArray * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2ListOrArray * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2ListOrArray * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2ListOrArray * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2ListOrArray * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2ListOrArray * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2ListOrArray * This,
            /* [in] */ long idx,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2ListOrArray * This,
            /* [in] */ long idx,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IG2ListOrArray * This,
            /* [retval][out] */ G2Type *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Type )( 
            IG2ListOrArray * This,
            /* [in] */ G2Type newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IG2ListOrArray * This,
            /* [retval][out] */ long *pVal);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2ListOrArray * This,
            /* [in] */ long pGsiItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            IG2ListOrArray * This,
            /* [in] */ long idx,
            /* [in] */ VARIANT varX);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Append )( 
            IG2ListOrArray * This,
            /* [in] */ long idx,
            /* [in] */ VARIANT varX);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IG2ListOrArray * This,
            /* [in] */ VARIANT varX);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IG2ListOrArray * This,
            /* [in] */ long idx);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IG2ListOrArray * This,
            /* [retval][out] */ LPUNKNOWN *pVal);
        
        END_INTERFACE
    } IG2ListOrArrayVtbl;

    interface IG2ListOrArray
    {
        CONST_VTBL struct IG2ListOrArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2ListOrArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2ListOrArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2ListOrArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2ListOrArray_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2ListOrArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2ListOrArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2ListOrArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2ListOrArray_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2ListOrArray_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2ListOrArray_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IG2ListOrArray_put_Item(This,idx,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,idx,newVal) ) 

#define IG2ListOrArray_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IG2ListOrArray_put_Type(This,newVal)	\
    ( (This)->lpVtbl -> put_Type(This,newVal) ) 

#define IG2ListOrArray_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IG2ListOrArray_Init(This,pGsiItem)	\
    ( (This)->lpVtbl -> Init(This,pGsiItem) ) 

#define IG2ListOrArray_Insert(This,idx,varX)	\
    ( (This)->lpVtbl -> Insert(This,idx,varX) ) 

#define IG2ListOrArray_Append(This,idx,varX)	\
    ( (This)->lpVtbl -> Append(This,idx,varX) ) 

#define IG2ListOrArray_Add(This,varX)	\
    ( (This)->lpVtbl -> Add(This,varX) ) 

#define IG2ListOrArray_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define IG2ListOrArray_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2ListOrArray_INTERFACE_DEFINED__ */


#ifndef __IG2LAElement_INTERFACE_DEFINED__
#define __IG2LAElement_INTERFACE_DEFINED__

/* interface IG2LAElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2LAElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98A966CA-2D0B-4952-BD49-25B3BBEE91F6")
    IG2LAElement : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IG2ListOrArray *pLaw,
            /* [in] */ long idx) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2LAElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2LAElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2LAElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2LAElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2LAElement * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2LAElement * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2LAElement * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2LAElement * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2LAElement * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2LAElement * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2LAElement * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            IG2LAElement * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            IG2LAElement * This,
            /* [in] */ VARIANT newVal);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2LAElement * This,
            /* [in] */ IG2ListOrArray *pLaw,
            /* [in] */ long idx);
        
        END_INTERFACE
    } IG2LAElementVtbl;

    interface IG2LAElement
    {
        CONST_VTBL struct IG2LAElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2LAElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2LAElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2LAElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2LAElement_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2LAElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2LAElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2LAElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2LAElement_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2LAElement_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2LAElement_get_Item(This,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,pVal) ) 

#define IG2LAElement_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define IG2LAElement_put_Value(This,newVal)	\
    ( (This)->lpVtbl -> put_Value(This,newVal) ) 

#define IG2LAElement_Init(This,pLaw,idx)	\
    ( (This)->lpVtbl -> Init(This,pLaw,idx) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2LAElement_INTERFACE_DEFINED__ */


#ifndef __IG2Symbol_INTERFACE_DEFINED__
#define __IG2Symbol_INTERFACE_DEFINED__

/* interface IG2Symbol */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Symbol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B2E73BD0-B965-4456-B9D0-8D11EA69D476")
    IG2Symbol : public G2ComObject
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperCase( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperCase( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2SymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Symbol * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Symbol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Symbol * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Symbol * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Symbol * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Symbol * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Symbol * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Symbol * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Symbol * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IG2Symbol * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Item )( 
            IG2Symbol * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UpperCase )( 
            IG2Symbol * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UpperCase )( 
            IG2Symbol * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IG2SymbolVtbl;

    interface IG2Symbol
    {
        CONST_VTBL struct IG2SymbolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Symbol_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Symbol_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Symbol_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Symbol_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Symbol_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Symbol_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Symbol_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Symbol_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Symbol_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Symbol_get_Item(This,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,pVal) ) 

#define IG2Symbol_put_Item(This,newVal)	\
    ( (This)->lpVtbl -> put_Item(This,newVal) ) 

#define IG2Symbol_get_UpperCase(This,pVal)	\
    ( (This)->lpVtbl -> get_UpperCase(This,pVal) ) 

#define IG2Symbol_put_UpperCase(This,newVal)	\
    ( (This)->lpVtbl -> put_UpperCase(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Symbol_INTERFACE_DEFINED__ */


#ifndef __IG2ItemRef_INTERFACE_DEFINED__
#define __IG2ItemRef_INTERFACE_DEFINED__

/* interface IG2ItemRef */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2ItemRef;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3862DC96-AF87-48C9-9C14-0F2D5A4B7250")
    IG2ItemRef : public G2ComObject
    {
    public:
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ unsigned short *pUUIDin,
            /* [in] */ long pCtx) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Git( 
            /* [out] */ unsigned short *pUUIDout,
            /* [out] */ long *pctx) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UUID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UUID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Gateway( 
            /* [in] */ IG2Gateway4 *gateway) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ItemRefVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2ItemRef * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2ItemRef * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2ItemRef * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2ItemRef * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2ItemRef * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2ItemRef * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2ItemRef * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2ItemRef * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2ItemRef * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IG2ItemRef * This,
            /* [in] */ unsigned short *pUUIDin,
            /* [in] */ long pCtx);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Git )( 
            IG2ItemRef * This,
            /* [out] */ unsigned short *pUUIDout,
            /* [out] */ long *pctx);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UUID )( 
            IG2ItemRef * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UUID )( 
            IG2ItemRef * This,
            /* [in] */ BSTR newVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Gateway )( 
            IG2ItemRef * This,
            /* [in] */ IG2Gateway4 *gateway);
        
        END_INTERFACE
    } IG2ItemRefVtbl;

    interface IG2ItemRef
    {
        CONST_VTBL struct IG2ItemRefVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2ItemRef_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2ItemRef_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2ItemRef_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2ItemRef_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2ItemRef_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2ItemRef_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2ItemRef_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2ItemRef_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2ItemRef_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2ItemRef_Init(This,pUUIDin,pCtx)	\
    ( (This)->lpVtbl -> Init(This,pUUIDin,pCtx) ) 

#define IG2ItemRef_Git(This,pUUIDout,pctx)	\
    ( (This)->lpVtbl -> Git(This,pUUIDout,pctx) ) 

#define IG2ItemRef_get_UUID(This,pVal)	\
    ( (This)->lpVtbl -> get_UUID(This,pVal) ) 

#define IG2ItemRef_put_UUID(This,newVal)	\
    ( (This)->lpVtbl -> put_UUID(This,newVal) ) 

#define IG2ItemRef_put_Gateway(This,gateway)	\
    ( (This)->lpVtbl -> put_Gateway(This,gateway) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2ItemRef_INTERFACE_DEFINED__ */


#ifndef __IG2Workspace_INTERFACE_DEFINED__
#define __IG2Workspace_INTERFACE_DEFINED__

/* interface IG2Workspace */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Workspace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("986F5307-690C-4EF3-9173-7A2AE4014590")
    IG2Workspace : public G2ComObject
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToItemAddition( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *subHdl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToItemRemoval( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *subHdl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromItemAddition( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromItemRemoval( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2WorkspaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Workspace * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Workspace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Workspace * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Workspace * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Workspace * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Workspace * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Workspace * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Workspace * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Workspace * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToItemAddition )( 
            IG2Workspace * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *subHdl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToItemRemoval )( 
            IG2Workspace * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *subHdl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromItemAddition )( 
            IG2Workspace * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromItemRemoval )( 
            IG2Workspace * This);
        
        END_INTERFACE
    } IG2WorkspaceVtbl;

    interface IG2Workspace
    {
        CONST_VTBL struct IG2WorkspaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Workspace_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Workspace_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Workspace_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Workspace_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Workspace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Workspace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Workspace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Workspace_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Workspace_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Workspace_SubscribeToItemAddition(This,userData,subHdl)	\
    ( (This)->lpVtbl -> SubscribeToItemAddition(This,userData,subHdl) ) 

#define IG2Workspace_SubscribeToItemRemoval(This,userData,subHdl)	\
    ( (This)->lpVtbl -> SubscribeToItemRemoval(This,userData,subHdl) ) 

#define IG2Workspace_UnsubscribeFromItemAddition(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromItemAddition(This) ) 

#define IG2Workspace_UnsubscribeFromItemRemoval(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromItemRemoval(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Workspace_INTERFACE_DEFINED__ */


#ifndef __IG2Window_INTERFACE_DEFINED__
#define __IG2Window_INTERFACE_DEFINED__

/* interface IG2Window */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2Window;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2488BB94-3222-4D5D-8257-8DD9600561F5")
    IG2Window : public G2ComObject
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToSelection( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *results) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromSelection( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_g2UserMode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_g2UserMode( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2WindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2Window * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2Window * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2Window * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2Window * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2Window * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2Window * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2Window * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE *get_WhatAmI )( 
            IG2Window * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE *Duplicate )( 
            IG2Window * This,
            /* [retval][out] */ IUnknown **pNewObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SubscribeToSelection )( 
            IG2Window * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT *results);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnsubscribeFromSelection )( 
            IG2Window * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_g2UserMode )( 
            IG2Window * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_g2UserMode )( 
            IG2Window * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IG2WindowVtbl;

    interface IG2Window
    {
        CONST_VTBL struct IG2WindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Window_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2Window_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2Window_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2Window_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2Window_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2Window_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2Window_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2Window_get_WhatAmI(This,pVal)	\
    ( (This)->lpVtbl -> get_WhatAmI(This,pVal) ) 

#define IG2Window_Duplicate(This,pNewObj)	\
    ( (This)->lpVtbl -> Duplicate(This,pNewObj) ) 


#define IG2Window_SubscribeToSelection(This,userData,results)	\
    ( (This)->lpVtbl -> SubscribeToSelection(This,userData,results) ) 

#define IG2Window_UnsubscribeFromSelection(This)	\
    ( (This)->lpVtbl -> UnsubscribeFromSelection(This) ) 

#define IG2Window_get_g2UserMode(This,pVal)	\
    ( (This)->lpVtbl -> get_g2UserMode(This,pVal) ) 

#define IG2Window_put_g2UserMode(This,newVal)	\
    ( (This)->lpVtbl -> put_g2UserMode(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2Window_INTERFACE_DEFINED__ */


#ifndef __IG2ComConfigurator_INTERFACE_DEFINED__
#define __IG2ComConfigurator_INTERFACE_DEFINED__

/* interface IG2ComConfigurator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IG2ComConfigurator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56E2306B-4F30-4249-94B0-B3B9647DBC3A")
    IG2ComConfigurator : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HighThroughput( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HighThroughput( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ComConfiguratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IG2ComConfigurator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IG2ComConfigurator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IG2ComConfigurator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IG2ComConfigurator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IG2ComConfigurator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IG2ComConfigurator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IG2ComConfigurator * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HighThroughput )( 
            IG2ComConfigurator * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HighThroughput )( 
            IG2ComConfigurator * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IG2ComConfiguratorVtbl;

    interface IG2ComConfigurator
    {
        CONST_VTBL struct IG2ComConfiguratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2ComConfigurator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IG2ComConfigurator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IG2ComConfigurator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IG2ComConfigurator_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IG2ComConfigurator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IG2ComConfigurator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IG2ComConfigurator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IG2ComConfigurator_get_HighThroughput(This,pVal)	\
    ( (This)->lpVtbl -> get_HighThroughput(This,pVal) ) 

#define IG2ComConfigurator_put_HighThroughput(This,newVal)	\
    ( (This)->lpVtbl -> put_HighThroughput(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IG2ComConfigurator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_G2Com_0000_0019 */
/* [local] */ 






extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_0019_v0_0_s_ifspec;


#ifndef __GensymAxl_LIBRARY_DEFINED__
#define __GensymAxl_LIBRARY_DEFINED__

/* library GensymAxl */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_GensymAxl;

#ifndef ___G2Events_DISPINTERFACE_DEFINED__
#define ___G2Events_DISPINTERFACE_DEFINED__

/* dispinterface _G2Events */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__G2Events;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F15B9434-B166-11d1-A718-006008C5F933")
    _G2Events : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _G2EventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _G2Events * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _G2Events * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _G2Events * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _G2Events * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _G2Events * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _G2Events * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _G2Events * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _G2EventsVtbl;

    interface _G2Events
    {
        CONST_VTBL struct _G2EventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _G2Events_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _G2Events_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _G2Events_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _G2Events_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _G2Events_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _G2Events_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _G2Events_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___G2Events_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_G2Gateway;

#ifdef __cplusplus

class DECLSPEC_UUID("AC4C85D0-B16C-11d1-A718-006008C5F933")
G2Gateway;
#endif

EXTERN_C const CLSID CLSID_GatewayProp;

#ifdef __cplusplus

class DECLSPEC_UUID("8AEF2DA3-471A-11D1-8AB5-00609703E60F")
GatewayProp;
#endif

EXTERN_C const CLSID CLSID_G2StructureEntry;

#ifdef __cplusplus

class DECLSPEC_UUID("15FC7CCC-C179-49BA-A68B-13C20C580DC0")
G2StructureEntry;
#endif

EXTERN_C const CLSID CLSID_G2Structure;

#ifdef __cplusplus

class DECLSPEC_UUID("CE90290F-2EAE-49EF-8B5A-D5FF6AAE8CE0")
G2Structure;
#endif

EXTERN_C const CLSID CLSID_G2Item;

#ifdef __cplusplus

class DECLSPEC_UUID("65DA1F96-DA11-47FE-B3EF-1CE21CDB0ED0")
G2Item;
#endif

EXTERN_C const CLSID CLSID_G2Attribute;

#ifdef __cplusplus

class DECLSPEC_UUID("738B47FA-2D36-40D2-8DC3-47E97717E64B")
G2Attribute;
#endif

EXTERN_C const CLSID CLSID_G2ListOrArray;

#ifdef __cplusplus

class DECLSPEC_UUID("27F911C6-B864-4C85-A7FA-CE151B60F4BF")
G2ListOrArray;
#endif

EXTERN_C const CLSID CLSID_G2Symbol;

#ifdef __cplusplus

class DECLSPEC_UUID("3137F3E2-9860-4335-907B-3F0A4DE31C62")
G2Symbol;
#endif

EXTERN_C const CLSID CLSID_G2LAElement;

#ifdef __cplusplus

class DECLSPEC_UUID("9BB94100-E344-415F-9976-D2BEB3DA4B29")
G2LAElement;
#endif

EXTERN_C const CLSID CLSID_G2ItemRef;

#ifdef __cplusplus

class DECLSPEC_UUID("15DD1D07-37FD-4D16-9ACB-BEBC4CE25438")
G2ItemRef;
#endif

EXTERN_C const CLSID CLSID_G2Workspace;

#ifdef __cplusplus

class DECLSPEC_UUID("4F6FF39F-793B-4BC5-8413-657F7BA99F57")
G2Workspace;
#endif

EXTERN_C const CLSID CLSID_G2Window;

#ifdef __cplusplus

class DECLSPEC_UUID("4E1A836D-1FEA-4E83-8F2F-A21204406222")
G2Window;
#endif

EXTERN_C const CLSID CLSID_G2ComConfigurator;

#ifdef __cplusplus

class DECLSPEC_UUID("659E9603-1375-4225-BFD8-DDB4281855A6")
G2ComConfigurator;
#endif
#endif /* __GensymAxl_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


