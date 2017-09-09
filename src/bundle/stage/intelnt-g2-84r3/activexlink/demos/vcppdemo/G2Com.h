/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 22 15:29:57 2008
 */
/* Compiler settings for G2Com.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_G2Com_0000 */
/* [local] */ 

typedef /* [public][public][public][public][public][public][public][public][public][public][uuid] */ 
enum __MIDL___MIDL_itf_G2Com_0000_0001
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
    }	G2Type;

typedef /* [public][public][uuid] */ 
enum __MIDL___MIDL_itf_G2Com_0000_0002
    {	g2UnknownState	= -1,
	g2Reset	= 0,
	g2Paused	= 1,
	g2Running	= 2
    }	G2RunStateType;

typedef /* [public][v1_enum][uuid] */ 
enum __MIDL___MIDL_itf_G2Com_0000_0003
    {	stModify	= 1,
	stDelete	= 2,
	stColorChg	= 3,
	stCustom	= 4,
	stValueChg	= 5,
	stWkspcAdd	= 6,
	stWkspcDel	= 7,
	stSelection	= 8
    }	g2SubscriptionType;



extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_G2Com_0000_v0_0_s_ifspec;

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
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments,
            /* [retval][out] */ VARIANT __RPC_FAR *ReturnArguments) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE CallDeferred( 
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT __RPC_FAR *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE Start( 
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNamedObject( 
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateObjectInstance( 
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsG2Connected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsG2Running( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_G2Location( 
            /* [retval][out] */ BSTR __RPC_FAR *Location) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_G2Location( 
            /* [in] */ BSTR Location) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InterfaceClass( 
            /* [retval][out] */ BSTR __RPC_FAR *InterfaceClassName) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_InterfaceClass( 
            /* [in] */ BSTR InterfaceClassName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteInitializationString( 
            /* [retval][out] */ BSTR __RPC_FAR *InitializationString) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_RemoteInitializationString( 
            /* [in] */ BSTR InitializationString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CallTimeout( 
            /* [retval][out] */ long __RPC_FAR *MaxWait) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_CallTimeout( 
            /* [in] */ long MaxWait) = 0;
        
        virtual /* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE _FireEvents( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PostMessage( 
            /* [in] */ VARIANT __RPC_FAR *Message) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2GatewayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Gateway __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Gateway __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Gateway __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IG2Gateway __RPC_FAR * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Call )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments,
            /* [retval][out] */ VARIANT __RPC_FAR *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallDeferred )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT __RPC_FAR *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamedObject )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObjectInstance )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Connected )( 
            IG2Gateway __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Running )( 
            IG2Gateway __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2Location )( 
            IG2Gateway __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_G2Location )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InterfaceClass )( 
            IG2Gateway __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InterfaceClass )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteInitializationString )( 
            IG2Gateway __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteInitializationString )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallTimeout )( 
            IG2Gateway __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CallTimeout )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_FireEvents )( 
            IG2Gateway __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostMessage )( 
            IG2Gateway __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Message);
        
        END_INTERFACE
    } IG2GatewayVtbl;

    interface IG2Gateway
    {
        CONST_VTBL struct IG2GatewayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Gateway_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Gateway_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Gateway_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Gateway_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Gateway_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Gateway_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Gateway_Connect(This,WaitFlag)	\
    (This)->lpVtbl -> Connect(This,WaitFlag)

#define IG2Gateway_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IG2Gateway_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments)

#define IG2Gateway_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)

#define IG2Gateway_Start(This,ProcedureName,Arguments)	\
    (This)->lpVtbl -> Start(This,ProcedureName,Arguments)

#define IG2Gateway_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj)

#define IG2Gateway_CreateObjectInstance(This,ClassName,Obj)	\
    (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj)

#define IG2Gateway_get_IsG2Connected(This,Val)	\
    (This)->lpVtbl -> get_IsG2Connected(This,Val)

#define IG2Gateway_get_IsG2Running(This,Val)	\
    (This)->lpVtbl -> get_IsG2Running(This,Val)

#define IG2Gateway_get_G2Location(This,Location)	\
    (This)->lpVtbl -> get_G2Location(This,Location)

#define IG2Gateway_put_G2Location(This,Location)	\
    (This)->lpVtbl -> put_G2Location(This,Location)

#define IG2Gateway_get_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway_put_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway_get_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString)

#define IG2Gateway_put_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString)

#define IG2Gateway_get_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> get_CallTimeout(This,MaxWait)

#define IG2Gateway_put_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> put_CallTimeout(This,MaxWait)

#define IG2Gateway__FireEvents(This)	\
    (This)->lpVtbl -> _FireEvents(This)

#define IG2Gateway_PostMessage(This,Message)	\
    (This)->lpVtbl -> PostMessage(This,Message)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_Connect_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL WaitFlag);


void __RPC_STUB IG2Gateway_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_Disconnect_Proxy( 
    IG2Gateway __RPC_FAR * This);


void __RPC_STUB IG2Gateway_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_Call_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR ProcedureName,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments,
    /* [retval][out] */ VARIANT __RPC_FAR *ReturnArguments);


void __RPC_STUB IG2Gateway_Call_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_CallDeferred_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR ProcedureName,
    /* [in] */ VARIANT __RPC_FAR *DeferredCallIdentifier,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);


void __RPC_STUB IG2Gateway_CallDeferred_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_Start_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR ProcedureName,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments);


void __RPC_STUB IG2Gateway_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_GetNamedObject_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR ObjectName,
    /* [defaultvalue][in] */ BSTR ObjectClass,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);


void __RPC_STUB IG2Gateway_GetNamedObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_CreateObjectInstance_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR ClassName,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);


void __RPC_STUB IG2Gateway_CreateObjectInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway_get_IsG2Connected_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);


void __RPC_STUB IG2Gateway_get_IsG2Connected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway_get_IsG2Running_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);


void __RPC_STUB IG2Gateway_get_IsG2Running_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway_get_G2Location_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Location);


void __RPC_STUB IG2Gateway_get_G2Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IG2Gateway_put_G2Location_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR Location);


void __RPC_STUB IG2Gateway_put_G2Location_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway_get_InterfaceClass_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *InterfaceClassName);


void __RPC_STUB IG2Gateway_get_InterfaceClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IG2Gateway_put_InterfaceClass_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR InterfaceClassName);


void __RPC_STUB IG2Gateway_put_InterfaceClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway_get_RemoteInitializationString_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *InitializationString);


void __RPC_STUB IG2Gateway_get_RemoteInitializationString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IG2Gateway_put_RemoteInitializationString_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ BSTR InitializationString);


void __RPC_STUB IG2Gateway_put_RemoteInitializationString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway_get_CallTimeout_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *MaxWait);


void __RPC_STUB IG2Gateway_get_CallTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IG2Gateway_put_CallTimeout_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ long MaxWait);


void __RPC_STUB IG2Gateway_put_CallTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway__FireEvents_Proxy( 
    IG2Gateway __RPC_FAR * This);


void __RPC_STUB IG2Gateway__FireEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway_PostMessage_Proxy( 
    IG2Gateway __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *Message);


void __RPC_STUB IG2Gateway_PostMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [in] */ IUnknown __RPC_FAR *piUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnEndPage( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Gateway2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Gateway2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Gateway2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IG2Gateway2 __RPC_FAR * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Call )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments,
            /* [retval][out] */ VARIANT __RPC_FAR *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallDeferred )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT __RPC_FAR *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamedObject )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObjectInstance )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Connected )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Running )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2Location )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_G2Location )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InterfaceClass )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InterfaceClass )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteInitializationString )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteInitializationString )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallTimeout )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CallTimeout )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_FireEvents )( 
            IG2Gateway2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostMessage )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStartPage )( 
            IG2Gateway2 __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *piUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEndPage )( 
            IG2Gateway2 __RPC_FAR * This);
        
        END_INTERFACE
    } IG2Gateway2Vtbl;

    interface IG2Gateway2
    {
        CONST_VTBL struct IG2Gateway2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Gateway2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Gateway2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Gateway2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Gateway2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Gateway2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Gateway2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Gateway2_Connect(This,WaitFlag)	\
    (This)->lpVtbl -> Connect(This,WaitFlag)

#define IG2Gateway2_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IG2Gateway2_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments)

#define IG2Gateway2_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)

#define IG2Gateway2_Start(This,ProcedureName,Arguments)	\
    (This)->lpVtbl -> Start(This,ProcedureName,Arguments)

#define IG2Gateway2_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj)

#define IG2Gateway2_CreateObjectInstance(This,ClassName,Obj)	\
    (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj)

#define IG2Gateway2_get_IsG2Connected(This,Val)	\
    (This)->lpVtbl -> get_IsG2Connected(This,Val)

#define IG2Gateway2_get_IsG2Running(This,Val)	\
    (This)->lpVtbl -> get_IsG2Running(This,Val)

#define IG2Gateway2_get_G2Location(This,Location)	\
    (This)->lpVtbl -> get_G2Location(This,Location)

#define IG2Gateway2_put_G2Location(This,Location)	\
    (This)->lpVtbl -> put_G2Location(This,Location)

#define IG2Gateway2_get_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway2_put_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway2_get_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString)

#define IG2Gateway2_put_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString)

#define IG2Gateway2_get_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> get_CallTimeout(This,MaxWait)

#define IG2Gateway2_put_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> put_CallTimeout(This,MaxWait)

#define IG2Gateway2__FireEvents(This)	\
    (This)->lpVtbl -> _FireEvents(This)

#define IG2Gateway2_PostMessage(This,Message)	\
    (This)->lpVtbl -> PostMessage(This,Message)


#define IG2Gateway2_OnStartPage(This,piUnk)	\
    (This)->lpVtbl -> OnStartPage(This,piUnk)

#define IG2Gateway2_OnEndPage(This)	\
    (This)->lpVtbl -> OnEndPage(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway2_OnStartPage_Proxy( 
    IG2Gateway2 __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *piUnk);


void __RPC_STUB IG2Gateway2_OnStartPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway2_OnEndPage_Proxy( 
    IG2Gateway2 __RPC_FAR * This);


void __RPC_STUB IG2Gateway2_OnEndPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *inArgs,
            /* [retval][out] */ VARIANT __RPC_FAR *pResult) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE DbgMsg( 
            /* [in] */ BSTR msg) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_G2RunState( 
            /* [retval][out] */ G2RunStateType __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Gateway3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Gateway3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Gateway3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IG2Gateway3 __RPC_FAR * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Call )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments,
            /* [retval][out] */ VARIANT __RPC_FAR *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallDeferred )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT __RPC_FAR *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamedObject )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObjectInstance )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Connected )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Running )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2Location )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_G2Location )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InterfaceClass )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InterfaceClass )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteInitializationString )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteInitializationString )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallTimeout )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CallTimeout )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_FireEvents )( 
            IG2Gateway3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostMessage )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStartPage )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *piUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEndPage )( 
            IG2Gateway3 __RPC_FAR * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeG2ComVariable )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ G2Type ComType,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *inArgs,
            /* [retval][out] */ VARIANT __RPC_FAR *pResult);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DbgMsg )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [in] */ BSTR msg);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2RunState )( 
            IG2Gateway3 __RPC_FAR * This,
            /* [retval][out] */ G2RunStateType __RPC_FAR *pVal);
        
        END_INTERFACE
    } IG2Gateway3Vtbl;

    interface IG2Gateway3
    {
        CONST_VTBL struct IG2Gateway3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Gateway3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Gateway3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Gateway3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Gateway3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Gateway3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Gateway3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Gateway3_Connect(This,WaitFlag)	\
    (This)->lpVtbl -> Connect(This,WaitFlag)

#define IG2Gateway3_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IG2Gateway3_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments)

#define IG2Gateway3_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)

#define IG2Gateway3_Start(This,ProcedureName,Arguments)	\
    (This)->lpVtbl -> Start(This,ProcedureName,Arguments)

#define IG2Gateway3_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj)

#define IG2Gateway3_CreateObjectInstance(This,ClassName,Obj)	\
    (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj)

#define IG2Gateway3_get_IsG2Connected(This,Val)	\
    (This)->lpVtbl -> get_IsG2Connected(This,Val)

#define IG2Gateway3_get_IsG2Running(This,Val)	\
    (This)->lpVtbl -> get_IsG2Running(This,Val)

#define IG2Gateway3_get_G2Location(This,Location)	\
    (This)->lpVtbl -> get_G2Location(This,Location)

#define IG2Gateway3_put_G2Location(This,Location)	\
    (This)->lpVtbl -> put_G2Location(This,Location)

#define IG2Gateway3_get_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway3_put_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway3_get_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString)

#define IG2Gateway3_put_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString)

#define IG2Gateway3_get_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> get_CallTimeout(This,MaxWait)

#define IG2Gateway3_put_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> put_CallTimeout(This,MaxWait)

#define IG2Gateway3__FireEvents(This)	\
    (This)->lpVtbl -> _FireEvents(This)

#define IG2Gateway3_PostMessage(This,Message)	\
    (This)->lpVtbl -> PostMessage(This,Message)


#define IG2Gateway3_OnStartPage(This,piUnk)	\
    (This)->lpVtbl -> OnStartPage(This,piUnk)

#define IG2Gateway3_OnEndPage(This)	\
    (This)->lpVtbl -> OnEndPage(This)


#define IG2Gateway3_MakeG2ComVariable(This,ComType,inArgs,pResult)	\
    (This)->lpVtbl -> MakeG2ComVariable(This,ComType,inArgs,pResult)

#define IG2Gateway3_DbgMsg(This,msg)	\
    (This)->lpVtbl -> DbgMsg(This,msg)

#define IG2Gateway3_get_G2RunState(This,pVal)	\
    (This)->lpVtbl -> get_G2RunState(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway3_MakeG2ComVariable_Proxy( 
    IG2Gateway3 __RPC_FAR * This,
    /* [in] */ G2Type ComType,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *inArgs,
    /* [retval][out] */ VARIANT __RPC_FAR *pResult);


void __RPC_STUB IG2Gateway3_MakeG2ComVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Gateway3_DbgMsg_Proxy( 
    IG2Gateway3 __RPC_FAR * This,
    /* [in] */ BSTR msg);


void __RPC_STUB IG2Gateway3_DbgMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway3_get_G2RunState_Proxy( 
    IG2Gateway3 __RPC_FAR * This,
    /* [retval][out] */ G2RunStateType __RPC_FAR *pVal);


void __RPC_STUB IG2Gateway3_get_G2RunState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ long __RPC_FAR *plHWnd) = 0;
        
        virtual /* [helpstring][id][propput][hidden] */ HRESULT STDMETHODCALLTYPE put_TWHandle( 
            /* [in] */ long lHWnd) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE ObtainTWLockIfUnused( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE ClearTWLock( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_G2Symbols( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_G2Symbols( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisconnectOnReset( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DisconnectOnReset( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Gateway4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Gateway4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Gateway4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL WaitFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IG2Gateway4 __RPC_FAR * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Call )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments,
            /* [retval][out] */ VARIANT __RPC_FAR *ReturnArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallDeferred )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ VARIANT __RPC_FAR *DeferredCallIdentifier,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR ProcedureName,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *Arguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamedObject )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR ObjectName,
            /* [defaultvalue][in] */ BSTR ObjectClass,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObjectInstance )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR ClassName,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *Obj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Connected )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsG2Running )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2Location )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Location);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_G2Location )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR Location);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InterfaceClass )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InterfaceClassName);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InterfaceClass )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR InterfaceClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteInitializationString )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *InitializationString);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteInitializationString )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR InitializationString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallTimeout )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *MaxWait);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CallTimeout )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ long MaxWait);
        
        /* [restricted][hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_FireEvents )( 
            IG2Gateway4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostMessage )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Message);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStartPage )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *piUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEndPage )( 
            IG2Gateway4 __RPC_FAR * This);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeG2ComVariable )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ G2Type ComType,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *inArgs,
            /* [retval][out] */ VARIANT __RPC_FAR *pResult);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DbgMsg )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ BSTR msg);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2RunState )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ G2RunStateType __RPC_FAR *pVal);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TWHandle )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plHWnd);
        
        /* [helpstring][id][propput][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TWHandle )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ long lHWnd);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ObtainTWLockIfUnused )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearTWLock )( 
            IG2Gateway4 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_G2Symbols )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_G2Symbols )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisconnectOnReset )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisconnectOnReset )( 
            IG2Gateway4 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IG2Gateway4Vtbl;

    interface IG2Gateway4
    {
        CONST_VTBL struct IG2Gateway4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Gateway4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Gateway4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Gateway4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Gateway4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Gateway4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Gateway4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Gateway4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Gateway4_Connect(This,WaitFlag)	\
    (This)->lpVtbl -> Connect(This,WaitFlag)

#define IG2Gateway4_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IG2Gateway4_Call(This,ProcedureName,InputArguments,ReturnArguments)	\
    (This)->lpVtbl -> Call(This,ProcedureName,InputArguments,ReturnArguments)

#define IG2Gateway4_CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)	\
    (This)->lpVtbl -> CallDeferred(This,ProcedureName,DeferredCallIdentifier,InputArguments)

#define IG2Gateway4_Start(This,ProcedureName,Arguments)	\
    (This)->lpVtbl -> Start(This,ProcedureName,Arguments)

#define IG2Gateway4_GetNamedObject(This,ObjectName,ObjectClass,Obj)	\
    (This)->lpVtbl -> GetNamedObject(This,ObjectName,ObjectClass,Obj)

#define IG2Gateway4_CreateObjectInstance(This,ClassName,Obj)	\
    (This)->lpVtbl -> CreateObjectInstance(This,ClassName,Obj)

#define IG2Gateway4_get_IsG2Connected(This,Val)	\
    (This)->lpVtbl -> get_IsG2Connected(This,Val)

#define IG2Gateway4_get_IsG2Running(This,Val)	\
    (This)->lpVtbl -> get_IsG2Running(This,Val)

#define IG2Gateway4_get_G2Location(This,Location)	\
    (This)->lpVtbl -> get_G2Location(This,Location)

#define IG2Gateway4_put_G2Location(This,Location)	\
    (This)->lpVtbl -> put_G2Location(This,Location)

#define IG2Gateway4_get_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> get_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway4_put_InterfaceClass(This,InterfaceClassName)	\
    (This)->lpVtbl -> put_InterfaceClass(This,InterfaceClassName)

#define IG2Gateway4_get_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> get_RemoteInitializationString(This,InitializationString)

#define IG2Gateway4_put_RemoteInitializationString(This,InitializationString)	\
    (This)->lpVtbl -> put_RemoteInitializationString(This,InitializationString)

#define IG2Gateway4_get_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> get_CallTimeout(This,MaxWait)

#define IG2Gateway4_put_CallTimeout(This,MaxWait)	\
    (This)->lpVtbl -> put_CallTimeout(This,MaxWait)

#define IG2Gateway4__FireEvents(This)	\
    (This)->lpVtbl -> _FireEvents(This)

#define IG2Gateway4_PostMessage(This,Message)	\
    (This)->lpVtbl -> PostMessage(This,Message)


#define IG2Gateway4_OnStartPage(This,piUnk)	\
    (This)->lpVtbl -> OnStartPage(This,piUnk)

#define IG2Gateway4_OnEndPage(This)	\
    (This)->lpVtbl -> OnEndPage(This)


#define IG2Gateway4_MakeG2ComVariable(This,ComType,inArgs,pResult)	\
    (This)->lpVtbl -> MakeG2ComVariable(This,ComType,inArgs,pResult)

#define IG2Gateway4_DbgMsg(This,msg)	\
    (This)->lpVtbl -> DbgMsg(This,msg)

#define IG2Gateway4_get_G2RunState(This,pVal)	\
    (This)->lpVtbl -> get_G2RunState(This,pVal)


#define IG2Gateway4_get_TWHandle(This,plHWnd)	\
    (This)->lpVtbl -> get_TWHandle(This,plHWnd)

#define IG2Gateway4_put_TWHandle(This,lHWnd)	\
    (This)->lpVtbl -> put_TWHandle(This,lHWnd)

#define IG2Gateway4_ObtainTWLockIfUnused(This,pResult)	\
    (This)->lpVtbl -> ObtainTWLockIfUnused(This,pResult)

#define IG2Gateway4_ClearTWLock(This)	\
    (This)->lpVtbl -> ClearTWLock(This)

#define IG2Gateway4_get_G2Symbols(This,pVal)	\
    (This)->lpVtbl -> get_G2Symbols(This,pVal)

#define IG2Gateway4_put_G2Symbols(This,newVal)	\
    (This)->lpVtbl -> put_G2Symbols(This,newVal)

#define IG2Gateway4_get_DisconnectOnReset(This,pVal)	\
    (This)->lpVtbl -> get_DisconnectOnReset(This,pVal)

#define IG2Gateway4_put_DisconnectOnReset(This,newVal)	\
    (This)->lpVtbl -> put_DisconnectOnReset(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget][hidden] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_get_TWHandle_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plHWnd);


void __RPC_STUB IG2Gateway4_get_TWHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput][hidden] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_put_TWHandle_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [in] */ long lHWnd);


void __RPC_STUB IG2Gateway4_put_TWHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_ObtainTWLockIfUnused_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pResult);


void __RPC_STUB IG2Gateway4_ObtainTWLockIfUnused_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_ClearTWLock_Proxy( 
    IG2Gateway4 __RPC_FAR * This);


void __RPC_STUB IG2Gateway4_ClearTWLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_get_G2Symbols_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IG2Gateway4_get_G2Symbols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_put_G2Symbols_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IG2Gateway4_put_G2Symbols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_get_DisconnectOnReset_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IG2Gateway4_get_DisconnectOnReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Gateway4_put_DisconnectOnReset_Proxy( 
    IG2Gateway4 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IG2Gateway4_put_DisconnectOnReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE Duplicate( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct G2ComObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            G2ComObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            G2ComObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            G2ComObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            G2ComObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            G2ComObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            G2ComObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            G2ComObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            G2ComObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            G2ComObject __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        END_INTERFACE
    } G2ComObjectVtbl;

    interface G2ComObject
    {
        CONST_VTBL struct G2ComObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define G2ComObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define G2ComObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define G2ComObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define G2ComObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define G2ComObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define G2ComObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define G2ComObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define G2ComObject_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define G2ComObject_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget][hidden] */ HRESULT STDMETHODCALLTYPE G2ComObject_get_WhatAmI_Proxy( 
    G2ComObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB G2ComObject_get_WhatAmI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE G2ComObject_Duplicate_Proxy( 
    G2ComObject __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);


void __RPC_STUB G2ComObject_Duplicate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2StructureEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2StructureEntry __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2StructureEntry __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2StructureEntry __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IG2StructureEntryVtbl;

    interface IG2StructureEntry
    {
        CONST_VTBL struct IG2StructureEntryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2StructureEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2StructureEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2StructureEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2StructureEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2StructureEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2StructureEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2StructureEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2StructureEntry_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2StructureEntry_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2StructureEntry_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IG2StructureEntry_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IG2StructureEntry_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IG2StructureEntry_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2StructureEntry_get_Name_Proxy( 
    IG2StructureEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IG2StructureEntry_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2StructureEntry_put_Name_Proxy( 
    IG2StructureEntry __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IG2StructureEntry_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2StructureEntry_get_Value_Proxy( 
    IG2StructureEntry __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IG2StructureEntry_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2StructureEntry_put_Value_Proxy( 
    IG2StructureEntry __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IG2StructureEntry_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT __RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ VARIANT index,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT index) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Names( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *nameList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Values( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *valueList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2StructureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Structure __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Structure __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Structure __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Structure __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Structure __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ VARIANT __RPC_FAR *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ VARIANT index,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IG2Structure __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][vararg][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IG2Structure __RPC_FAR * This,
            /* [in] */ VARIANT index);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IG2Structure __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Names )( 
            IG2Structure __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *nameList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Values )( 
            IG2Structure __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *valueList);
        
        END_INTERFACE
    } IG2StructureVtbl;

    interface IG2Structure
    {
        CONST_VTBL struct IG2StructureVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Structure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Structure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Structure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Structure_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Structure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Structure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Structure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Structure_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Structure_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Structure_get_Item(This,index,pItem)	\
    (This)->lpVtbl -> get_Item(This,index,pItem)

#define IG2Structure_put_Item(This,index,value)	\
    (This)->lpVtbl -> put_Item(This,index,value)

#define IG2Structure_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IG2Structure_Add(This,InputArguments)	\
    (This)->lpVtbl -> Add(This,InputArguments)

#define IG2Structure_Remove(This,index)	\
    (This)->lpVtbl -> Remove(This,index)

#define IG2Structure_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IG2Structure_Names(This,nameList)	\
    (This)->lpVtbl -> Names(This,nameList)

#define IG2Structure_Values(This,valueList)	\
    (This)->lpVtbl -> Values(This,valueList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Structure_get_Item_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ VARIANT __RPC_FAR *pItem);


void __RPC_STUB IG2Structure_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Structure_put_Item_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [in] */ VARIANT index,
    /* [in] */ VARIANT value);


void __RPC_STUB IG2Structure_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Structure_get_Count_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IG2Structure_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][vararg][id] */ HRESULT STDMETHODCALLTYPE IG2Structure_Add_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [in] */ SAFEARRAY __RPC_FAR * __RPC_FAR *InputArguments);


void __RPC_STUB IG2Structure_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Structure_Remove_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [in] */ VARIANT index);


void __RPC_STUB IG2Structure_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IG2Structure_get__NewEnum_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IG2Structure_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Structure_Names_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *nameList);


void __RPC_STUB IG2Structure_Names_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Structure_Values_Proxy( 
    IG2Structure __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *valueList);


void __RPC_STUB IG2Structure_Values_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT __RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClassName( 
            /* [retval][out] */ BSTR __RPC_FAR *pClassName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClassName( 
            /* [in] */ BSTR bstrClassName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pItemName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR ItemName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ G2Type __RPC_FAR *pGsiType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ G2Type GsiType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pGsiType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT GsiType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT varIdx) = 0;
        
        virtual /* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrNames( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrNameList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrValues( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrValList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrTypes( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrTypeList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Symbolize( 
            VARIANT idx,
            VARIANT_BOOL flgSym) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ long pItem) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Git( 
            /* [out] */ long __RPC_FAR *pGsiItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Item __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Item __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Item __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT __RPC_FAR *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassName )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClassName )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ G2Type __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrNames )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrValues )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrTypes )( 
            IG2Item __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Symbolize )( 
            IG2Item __RPC_FAR * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2Item __RPC_FAR * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Git )( 
            IG2Item __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pGsiItem);
        
        END_INTERFACE
    } IG2ItemVtbl;

    interface IG2Item
    {
        CONST_VTBL struct IG2ItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Item_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Item_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Item_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Item_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Item_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Item_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Item_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Item_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Item_get_Item(This,Idx,pItem)	\
    (This)->lpVtbl -> get_Item(This,Idx,pItem)

#define IG2Item_put_Item(This,Idx,value)	\
    (This)->lpVtbl -> put_Item(This,Idx,value)

#define IG2Item_get_ClassName(This,pClassName)	\
    (This)->lpVtbl -> get_ClassName(This,pClassName)

#define IG2Item_put_ClassName(This,bstrClassName)	\
    (This)->lpVtbl -> put_ClassName(This,bstrClassName)

#define IG2Item_get_Name(This,pItemName)	\
    (This)->lpVtbl -> get_Name(This,pItemName)

#define IG2Item_put_Name(This,ItemName)	\
    (This)->lpVtbl -> put_Name(This,ItemName)

#define IG2Item_get_Type(This,pGsiType)	\
    (This)->lpVtbl -> get_Type(This,pGsiType)

#define IG2Item_put_Type(This,GsiType)	\
    (This)->lpVtbl -> put_Type(This,GsiType)

#define IG2Item_get_Value(This,pGsiType)	\
    (This)->lpVtbl -> get_Value(This,pGsiType)

#define IG2Item_put_Value(This,GsiType)	\
    (This)->lpVtbl -> put_Value(This,GsiType)

#define IG2Item_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IG2Item_Add(This,atName,atVal)	\
    (This)->lpVtbl -> Add(This,atName,atVal)

#define IG2Item_Remove(This,varIdx)	\
    (This)->lpVtbl -> Remove(This,varIdx)

#define IG2Item_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IG2Item_get_AttrNames(This,attrNameList)	\
    (This)->lpVtbl -> get_AttrNames(This,attrNameList)

#define IG2Item_get_AttrValues(This,attrValList)	\
    (This)->lpVtbl -> get_AttrValues(This,attrValList)

#define IG2Item_get_AttrTypes(This,attrTypeList)	\
    (This)->lpVtbl -> get_AttrTypes(This,attrTypeList)

#define IG2Item_Symbolize(This,idx,flgSym)	\
    (This)->lpVtbl -> Symbolize(This,idx,flgSym)

#define IG2Item_Init(This,pItem)	\
    (This)->lpVtbl -> Init(This,pItem)

#define IG2Item_Git(This,pGsiItem)	\
    (This)->lpVtbl -> Git(This,pGsiItem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_Item_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ VARIANT Idx,
    /* [retval][out] */ VARIANT __RPC_FAR *pItem);


void __RPC_STUB IG2Item_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Item_put_Item_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ VARIANT Idx,
    /* [in] */ VARIANT value);


void __RPC_STUB IG2Item_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_ClassName_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pClassName);


void __RPC_STUB IG2Item_get_ClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Item_put_ClassName_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ BSTR bstrClassName);


void __RPC_STUB IG2Item_put_ClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_Name_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pItemName);


void __RPC_STUB IG2Item_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Item_put_Name_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ BSTR ItemName);


void __RPC_STUB IG2Item_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_Type_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ G2Type __RPC_FAR *pGsiType);


void __RPC_STUB IG2Item_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Item_put_Type_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ G2Type GsiType);


void __RPC_STUB IG2Item_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_Value_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pGsiType);


void __RPC_STUB IG2Item_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Item_put_Value_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ VARIANT GsiType);


void __RPC_STUB IG2Item_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_Count_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IG2Item_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item_Add_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ BSTR atName,
    /* [in] */ VARIANT atVal);


void __RPC_STUB IG2Item_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item_Remove_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ VARIANT varIdx);


void __RPC_STUB IG2Item_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][restricted][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get__NewEnum_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IG2Item_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_AttrNames_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrNameList);


void __RPC_STUB IG2Item_get_AttrNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_AttrValues_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrValList);


void __RPC_STUB IG2Item_get_AttrValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item_get_AttrTypes_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrTypeList);


void __RPC_STUB IG2Item_get_AttrTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item_Symbolize_Proxy( 
    IG2Item __RPC_FAR * This,
    VARIANT idx,
    VARIANT_BOOL flgSym);


void __RPC_STUB IG2Item_Symbolize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IG2Item_Init_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [in] */ long pItem);


void __RPC_STUB IG2Item_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IG2Item_Git_Proxy( 
    IG2Item __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pGsiItem);


void __RPC_STUB IG2Item_Git_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IG2Item_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_G2Com_0216 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_G2Com_0216_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_G2Com_0216_v0_0_s_ifspec;

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
            /* [in] */ IG2ItemRef __RPC_FAR *pRef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Update( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LPDISPATCH pAxL) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Linked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pflgLinked) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Link( 
            /* [in] */ IG2ItemRef __RPC_FAR *pItemRef) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Unlink( void) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Unhandle( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttrType( 
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Reference( 
            /* [retval][out] */ IG2ItemRef __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToAttributeModification( 
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndls) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToDeletion( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToIconColorChange( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToCustomEvent( 
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToValueChange( 
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT __RPC_FAR *subscriptionHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromAttributeModification( 
            /* [in] */ VARIANT FromWhat) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromDeletion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromIconColorChange( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromCustomEvent( 
            VARIANT EventNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromValueChange( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Subscriptions( 
            /* [retval][out] */ VARIANT __RPC_FAR *ArrayOfSubscriptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Item2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Item2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Item2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Item2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT __RPC_FAR *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassName )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClassName )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ G2Type __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrNames )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrValues )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrTypes )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Symbolize )( 
            IG2Item2 __RPC_FAR * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Git )( 
            IG2Item2 __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pGsiItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Inix )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef __RPC_FAR *pRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ LPDISPATCH pAxL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Linked )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pflgLinked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Link )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ IG2ItemRef __RPC_FAR *pItemRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unlink )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unhandle )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrType )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Reference )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ IG2ItemRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToAttributeModification )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToDeletion )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToIconColorChange )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToCustomEvent )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToValueChange )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT __RPC_FAR *subscriptionHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromAttributeModification )( 
            IG2Item2 __RPC_FAR * This,
            /* [in] */ VARIANT FromWhat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromDeletion )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromIconColorChange )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromCustomEvent )( 
            IG2Item2 __RPC_FAR * This,
            VARIANT EventNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromAll )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromValueChange )( 
            IG2Item2 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subscriptions )( 
            IG2Item2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *ArrayOfSubscriptions);
        
        END_INTERFACE
    } IG2Item2Vtbl;

    interface IG2Item2
    {
        CONST_VTBL struct IG2Item2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Item2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Item2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Item2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Item2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Item2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Item2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Item2_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Item2_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Item2_get_Item(This,Idx,pItem)	\
    (This)->lpVtbl -> get_Item(This,Idx,pItem)

#define IG2Item2_put_Item(This,Idx,value)	\
    (This)->lpVtbl -> put_Item(This,Idx,value)

#define IG2Item2_get_ClassName(This,pClassName)	\
    (This)->lpVtbl -> get_ClassName(This,pClassName)

#define IG2Item2_put_ClassName(This,bstrClassName)	\
    (This)->lpVtbl -> put_ClassName(This,bstrClassName)

#define IG2Item2_get_Name(This,pItemName)	\
    (This)->lpVtbl -> get_Name(This,pItemName)

#define IG2Item2_put_Name(This,ItemName)	\
    (This)->lpVtbl -> put_Name(This,ItemName)

#define IG2Item2_get_Type(This,pGsiType)	\
    (This)->lpVtbl -> get_Type(This,pGsiType)

#define IG2Item2_put_Type(This,GsiType)	\
    (This)->lpVtbl -> put_Type(This,GsiType)

#define IG2Item2_get_Value(This,pGsiType)	\
    (This)->lpVtbl -> get_Value(This,pGsiType)

#define IG2Item2_put_Value(This,GsiType)	\
    (This)->lpVtbl -> put_Value(This,GsiType)

#define IG2Item2_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IG2Item2_Add(This,atName,atVal)	\
    (This)->lpVtbl -> Add(This,atName,atVal)

#define IG2Item2_Remove(This,varIdx)	\
    (This)->lpVtbl -> Remove(This,varIdx)

#define IG2Item2_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IG2Item2_get_AttrNames(This,attrNameList)	\
    (This)->lpVtbl -> get_AttrNames(This,attrNameList)

#define IG2Item2_get_AttrValues(This,attrValList)	\
    (This)->lpVtbl -> get_AttrValues(This,attrValList)

#define IG2Item2_get_AttrTypes(This,attrTypeList)	\
    (This)->lpVtbl -> get_AttrTypes(This,attrTypeList)

#define IG2Item2_Symbolize(This,idx,flgSym)	\
    (This)->lpVtbl -> Symbolize(This,idx,flgSym)

#define IG2Item2_Init(This,pItem)	\
    (This)->lpVtbl -> Init(This,pItem)

#define IG2Item2_Git(This,pGsiItem)	\
    (This)->lpVtbl -> Git(This,pGsiItem)


#define IG2Item2_Inix(This,pItem,pRef)	\
    (This)->lpVtbl -> Inix(This,pItem,pRef)

#define IG2Item2_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IG2Item2_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IG2Item2_Create(This,pAxL)	\
    (This)->lpVtbl -> Create(This,pAxL)

#define IG2Item2_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IG2Item2_get_Linked(This,pflgLinked)	\
    (This)->lpVtbl -> get_Linked(This,pflgLinked)

#define IG2Item2_Link(This,pItemRef)	\
    (This)->lpVtbl -> Link(This,pItemRef)

#define IG2Item2_Unlink(This)	\
    (This)->lpVtbl -> Unlink(This)

#define IG2Item2_Unhandle(This)	\
    (This)->lpVtbl -> Unhandle(This)

#define IG2Item2_get_AttrType(This,idx,pVal)	\
    (This)->lpVtbl -> get_AttrType(This,idx,pVal)

#define IG2Item2_get_Reference(This,pVal)	\
    (This)->lpVtbl -> get_Reference(This,pVal)

#define IG2Item2_SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)	\
    (This)->lpVtbl -> SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)

#define IG2Item2_SubscribeToDeletion(This,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToDeletion(This,userData,SubscripHndl)

#define IG2Item2_SubscribeToIconColorChange(This,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToIconColorChange(This,userData,SubscripHndl)

#define IG2Item2_SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)

#define IG2Item2_SubscribeToValueChange(This,userData,subscriptionHandle)	\
    (This)->lpVtbl -> SubscribeToValueChange(This,userData,subscriptionHandle)

#define IG2Item2_UnsubscribeFromAttributeModification(This,FromWhat)	\
    (This)->lpVtbl -> UnsubscribeFromAttributeModification(This,FromWhat)

#define IG2Item2_UnsubscribeFromDeletion(This)	\
    (This)->lpVtbl -> UnsubscribeFromDeletion(This)

#define IG2Item2_UnsubscribeFromIconColorChange(This)	\
    (This)->lpVtbl -> UnsubscribeFromIconColorChange(This)

#define IG2Item2_UnsubscribeFromCustomEvent(This,EventNames)	\
    (This)->lpVtbl -> UnsubscribeFromCustomEvent(This,EventNames)

#define IG2Item2_UnsubscribeFromAll(This)	\
    (This)->lpVtbl -> UnsubscribeFromAll(This)

#define IG2Item2_UnsubscribeFromValueChange(This)	\
    (This)->lpVtbl -> UnsubscribeFromValueChange(This)

#define IG2Item2_Subscriptions(This,ArrayOfSubscriptions)	\
    (This)->lpVtbl -> Subscriptions(This,ArrayOfSubscriptions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Inix_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ long pItem,
    /* [in] */ IG2ItemRef __RPC_FAR *pRef);


void __RPC_STUB IG2Item2_Inix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Refresh_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Update_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Create_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ LPDISPATCH pAxL);


void __RPC_STUB IG2Item2_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Delete_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item2_get_Linked_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pflgLinked);


void __RPC_STUB IG2Item2_get_Linked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Link_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ IG2ItemRef __RPC_FAR *pItemRef);


void __RPC_STUB IG2Item2_Link_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Unlink_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_Unlink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Unhandle_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_Unhandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item2_get_AttrType_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ VARIANT idx,
    /* [retval][out] */ G2Type __RPC_FAR *pVal);


void __RPC_STUB IG2Item2_get_AttrType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item2_get_Reference_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [retval][out] */ IG2ItemRef __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IG2Item2_get_Reference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_SubscribeToAttributeModification_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ VARIANT AttrName,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndls);


void __RPC_STUB IG2Item2_SubscribeToAttributeModification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_SubscribeToDeletion_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);


void __RPC_STUB IG2Item2_SubscribeToDeletion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_SubscribeToIconColorChange_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);


void __RPC_STUB IG2Item2_SubscribeToIconColorChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_SubscribeToCustomEvent_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ BSTR EventName,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);


void __RPC_STUB IG2Item2_SubscribeToCustomEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_SubscribeToValueChange_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ VARIANT userData,
    /* [out][retval] */ VARIANT __RPC_FAR *subscriptionHandle);


void __RPC_STUB IG2Item2_SubscribeToValueChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_UnsubscribeFromAttributeModification_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [in] */ VARIANT FromWhat);


void __RPC_STUB IG2Item2_UnsubscribeFromAttributeModification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_UnsubscribeFromDeletion_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_UnsubscribeFromDeletion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_UnsubscribeFromIconColorChange_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_UnsubscribeFromIconColorChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_UnsubscribeFromCustomEvent_Proxy( 
    IG2Item2 __RPC_FAR * This,
    VARIANT EventNames);


void __RPC_STUB IG2Item2_UnsubscribeFromCustomEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_UnsubscribeFromAll_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_UnsubscribeFromAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_UnsubscribeFromValueChange_Proxy( 
    IG2Item2 __RPC_FAR * This);


void __RPC_STUB IG2Item2_UnsubscribeFromValueChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Item2_Subscriptions_Proxy( 
    IG2Item2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *ArrayOfSubscriptions);


void __RPC_STUB IG2Item2_Subscriptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Item3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Item3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Item3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Item3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT __RPC_FAR *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassName )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClassName )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ G2Type __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrNames )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrValues )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrTypes )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Symbolize )( 
            IG2Item3 __RPC_FAR * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Git )( 
            IG2Item3 __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pGsiItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Inix )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef __RPC_FAR *pRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ LPDISPATCH pAxL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Linked )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pflgLinked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Link )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ IG2ItemRef __RPC_FAR *pItemRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unlink )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unhandle )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrType )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Reference )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ IG2ItemRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToAttributeModification )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToDeletion )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToIconColorChange )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToCustomEvent )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToValueChange )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT __RPC_FAR *subscriptionHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromAttributeModification )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ VARIANT FromWhat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromDeletion )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromIconColorChange )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromCustomEvent )( 
            IG2Item3 __RPC_FAR * This,
            VARIANT EventNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromAll )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromValueChange )( 
            IG2Item3 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subscriptions )( 
            IG2Item3 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *ArrayOfSubscriptions);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Icon )( 
            IG2Item3 __RPC_FAR * This,
            /* [in] */ long BackgroundColor,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal);
        
        END_INTERFACE
    } IG2Item3Vtbl;

    interface IG2Item3
    {
        CONST_VTBL struct IG2Item3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Item3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Item3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Item3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Item3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Item3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Item3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Item3_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Item3_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Item3_get_Item(This,Idx,pItem)	\
    (This)->lpVtbl -> get_Item(This,Idx,pItem)

#define IG2Item3_put_Item(This,Idx,value)	\
    (This)->lpVtbl -> put_Item(This,Idx,value)

#define IG2Item3_get_ClassName(This,pClassName)	\
    (This)->lpVtbl -> get_ClassName(This,pClassName)

#define IG2Item3_put_ClassName(This,bstrClassName)	\
    (This)->lpVtbl -> put_ClassName(This,bstrClassName)

#define IG2Item3_get_Name(This,pItemName)	\
    (This)->lpVtbl -> get_Name(This,pItemName)

#define IG2Item3_put_Name(This,ItemName)	\
    (This)->lpVtbl -> put_Name(This,ItemName)

#define IG2Item3_get_Type(This,pGsiType)	\
    (This)->lpVtbl -> get_Type(This,pGsiType)

#define IG2Item3_put_Type(This,GsiType)	\
    (This)->lpVtbl -> put_Type(This,GsiType)

#define IG2Item3_get_Value(This,pGsiType)	\
    (This)->lpVtbl -> get_Value(This,pGsiType)

#define IG2Item3_put_Value(This,GsiType)	\
    (This)->lpVtbl -> put_Value(This,GsiType)

#define IG2Item3_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IG2Item3_Add(This,atName,atVal)	\
    (This)->lpVtbl -> Add(This,atName,atVal)

#define IG2Item3_Remove(This,varIdx)	\
    (This)->lpVtbl -> Remove(This,varIdx)

#define IG2Item3_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IG2Item3_get_AttrNames(This,attrNameList)	\
    (This)->lpVtbl -> get_AttrNames(This,attrNameList)

#define IG2Item3_get_AttrValues(This,attrValList)	\
    (This)->lpVtbl -> get_AttrValues(This,attrValList)

#define IG2Item3_get_AttrTypes(This,attrTypeList)	\
    (This)->lpVtbl -> get_AttrTypes(This,attrTypeList)

#define IG2Item3_Symbolize(This,idx,flgSym)	\
    (This)->lpVtbl -> Symbolize(This,idx,flgSym)

#define IG2Item3_Init(This,pItem)	\
    (This)->lpVtbl -> Init(This,pItem)

#define IG2Item3_Git(This,pGsiItem)	\
    (This)->lpVtbl -> Git(This,pGsiItem)


#define IG2Item3_Inix(This,pItem,pRef)	\
    (This)->lpVtbl -> Inix(This,pItem,pRef)

#define IG2Item3_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IG2Item3_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IG2Item3_Create(This,pAxL)	\
    (This)->lpVtbl -> Create(This,pAxL)

#define IG2Item3_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IG2Item3_get_Linked(This,pflgLinked)	\
    (This)->lpVtbl -> get_Linked(This,pflgLinked)

#define IG2Item3_Link(This,pItemRef)	\
    (This)->lpVtbl -> Link(This,pItemRef)

#define IG2Item3_Unlink(This)	\
    (This)->lpVtbl -> Unlink(This)

#define IG2Item3_Unhandle(This)	\
    (This)->lpVtbl -> Unhandle(This)

#define IG2Item3_get_AttrType(This,idx,pVal)	\
    (This)->lpVtbl -> get_AttrType(This,idx,pVal)

#define IG2Item3_get_Reference(This,pVal)	\
    (This)->lpVtbl -> get_Reference(This,pVal)

#define IG2Item3_SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)	\
    (This)->lpVtbl -> SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)

#define IG2Item3_SubscribeToDeletion(This,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToDeletion(This,userData,SubscripHndl)

#define IG2Item3_SubscribeToIconColorChange(This,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToIconColorChange(This,userData,SubscripHndl)

#define IG2Item3_SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)

#define IG2Item3_SubscribeToValueChange(This,userData,subscriptionHandle)	\
    (This)->lpVtbl -> SubscribeToValueChange(This,userData,subscriptionHandle)

#define IG2Item3_UnsubscribeFromAttributeModification(This,FromWhat)	\
    (This)->lpVtbl -> UnsubscribeFromAttributeModification(This,FromWhat)

#define IG2Item3_UnsubscribeFromDeletion(This)	\
    (This)->lpVtbl -> UnsubscribeFromDeletion(This)

#define IG2Item3_UnsubscribeFromIconColorChange(This)	\
    (This)->lpVtbl -> UnsubscribeFromIconColorChange(This)

#define IG2Item3_UnsubscribeFromCustomEvent(This,EventNames)	\
    (This)->lpVtbl -> UnsubscribeFromCustomEvent(This,EventNames)

#define IG2Item3_UnsubscribeFromAll(This)	\
    (This)->lpVtbl -> UnsubscribeFromAll(This)

#define IG2Item3_UnsubscribeFromValueChange(This)	\
    (This)->lpVtbl -> UnsubscribeFromValueChange(This)

#define IG2Item3_Subscriptions(This,ArrayOfSubscriptions)	\
    (This)->lpVtbl -> Subscriptions(This,ArrayOfSubscriptions)


#define IG2Item3_get_Icon(This,BackgroundColor,pVal)	\
    (This)->lpVtbl -> get_Icon(This,BackgroundColor,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Item3_get_Icon_Proxy( 
    IG2Item3 __RPC_FAR * This,
    /* [in] */ long BackgroundColor,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal);


void __RPC_STUB IG2Item3_get_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [in] */ IG2ItemRef __RPC_FAR *pRef) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE Git2( 
            /* [out] */ long __RPC_FAR *ppDatum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2Item4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Item4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Item4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Item4 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [retval][out] */ VARIANT __RPC_FAR *pItem);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT Idx,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClassName )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pClassName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClassName )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ BSTR bstrClassName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pItemName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ BSTR ItemName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ G2Type __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ G2Type GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pGsiType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT GsiType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ BSTR atName,
            /* [in] */ VARIANT atVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT varIdx);
        
        /* [id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrNames )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrNameList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrValues )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrValList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrTypes )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *attrTypeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Symbolize )( 
            IG2Item4 __RPC_FAR * This,
            VARIANT idx,
            VARIANT_BOOL flgSym);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ long pItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Git )( 
            IG2Item4 __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pGsiItem);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Inix )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ long pItem,
            /* [in] */ IG2ItemRef __RPC_FAR *pRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ LPDISPATCH pAxL);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Linked )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pflgLinked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Link )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ IG2ItemRef __RPC_FAR *pItemRef);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unlink )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unhandle )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttrType )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT idx,
            /* [retval][out] */ G2Type __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Reference )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ IG2ItemRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToAttributeModification )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT AttrName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndls);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToDeletion )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToIconColorChange )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToCustomEvent )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ BSTR EventName,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *SubscripHndl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToValueChange )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [out][retval] */ VARIANT __RPC_FAR *subscriptionHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromAttributeModification )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ VARIANT FromWhat);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromDeletion )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromIconColorChange )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromCustomEvent )( 
            IG2Item4 __RPC_FAR * This,
            VARIANT EventNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromAll )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromValueChange )( 
            IG2Item4 __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subscriptions )( 
            IG2Item4 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *ArrayOfSubscriptions);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Icon )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ long BackgroundColor,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pVal);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init2 )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ long pDatum);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init3 )( 
            IG2Item4 __RPC_FAR * This,
            /* [in] */ long pDatum,
            /* [in] */ IG2ItemRef __RPC_FAR *pRef);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Git2 )( 
            IG2Item4 __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *ppDatum);
        
        END_INTERFACE
    } IG2Item4Vtbl;

    interface IG2Item4
    {
        CONST_VTBL struct IG2Item4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Item4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Item4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Item4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Item4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Item4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Item4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Item4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Item4_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Item4_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Item4_get_Item(This,Idx,pItem)	\
    (This)->lpVtbl -> get_Item(This,Idx,pItem)

#define IG2Item4_put_Item(This,Idx,value)	\
    (This)->lpVtbl -> put_Item(This,Idx,value)

#define IG2Item4_get_ClassName(This,pClassName)	\
    (This)->lpVtbl -> get_ClassName(This,pClassName)

#define IG2Item4_put_ClassName(This,bstrClassName)	\
    (This)->lpVtbl -> put_ClassName(This,bstrClassName)

#define IG2Item4_get_Name(This,pItemName)	\
    (This)->lpVtbl -> get_Name(This,pItemName)

#define IG2Item4_put_Name(This,ItemName)	\
    (This)->lpVtbl -> put_Name(This,ItemName)

#define IG2Item4_get_Type(This,pGsiType)	\
    (This)->lpVtbl -> get_Type(This,pGsiType)

#define IG2Item4_put_Type(This,GsiType)	\
    (This)->lpVtbl -> put_Type(This,GsiType)

#define IG2Item4_get_Value(This,pGsiType)	\
    (This)->lpVtbl -> get_Value(This,pGsiType)

#define IG2Item4_put_Value(This,GsiType)	\
    (This)->lpVtbl -> put_Value(This,GsiType)

#define IG2Item4_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IG2Item4_Add(This,atName,atVal)	\
    (This)->lpVtbl -> Add(This,atName,atVal)

#define IG2Item4_Remove(This,varIdx)	\
    (This)->lpVtbl -> Remove(This,varIdx)

#define IG2Item4_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IG2Item4_get_AttrNames(This,attrNameList)	\
    (This)->lpVtbl -> get_AttrNames(This,attrNameList)

#define IG2Item4_get_AttrValues(This,attrValList)	\
    (This)->lpVtbl -> get_AttrValues(This,attrValList)

#define IG2Item4_get_AttrTypes(This,attrTypeList)	\
    (This)->lpVtbl -> get_AttrTypes(This,attrTypeList)

#define IG2Item4_Symbolize(This,idx,flgSym)	\
    (This)->lpVtbl -> Symbolize(This,idx,flgSym)

#define IG2Item4_Init(This,pItem)	\
    (This)->lpVtbl -> Init(This,pItem)

#define IG2Item4_Git(This,pGsiItem)	\
    (This)->lpVtbl -> Git(This,pGsiItem)


#define IG2Item4_Inix(This,pItem,pRef)	\
    (This)->lpVtbl -> Inix(This,pItem,pRef)

#define IG2Item4_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IG2Item4_Update(This)	\
    (This)->lpVtbl -> Update(This)

#define IG2Item4_Create(This,pAxL)	\
    (This)->lpVtbl -> Create(This,pAxL)

#define IG2Item4_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define IG2Item4_get_Linked(This,pflgLinked)	\
    (This)->lpVtbl -> get_Linked(This,pflgLinked)

#define IG2Item4_Link(This,pItemRef)	\
    (This)->lpVtbl -> Link(This,pItemRef)

#define IG2Item4_Unlink(This)	\
    (This)->lpVtbl -> Unlink(This)

#define IG2Item4_Unhandle(This)	\
    (This)->lpVtbl -> Unhandle(This)

#define IG2Item4_get_AttrType(This,idx,pVal)	\
    (This)->lpVtbl -> get_AttrType(This,idx,pVal)

#define IG2Item4_get_Reference(This,pVal)	\
    (This)->lpVtbl -> get_Reference(This,pVal)

#define IG2Item4_SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)	\
    (This)->lpVtbl -> SubscribeToAttributeModification(This,AttrName,userData,SubscripHndls)

#define IG2Item4_SubscribeToDeletion(This,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToDeletion(This,userData,SubscripHndl)

#define IG2Item4_SubscribeToIconColorChange(This,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToIconColorChange(This,userData,SubscripHndl)

#define IG2Item4_SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)	\
    (This)->lpVtbl -> SubscribeToCustomEvent(This,EventName,userData,SubscripHndl)

#define IG2Item4_SubscribeToValueChange(This,userData,subscriptionHandle)	\
    (This)->lpVtbl -> SubscribeToValueChange(This,userData,subscriptionHandle)

#define IG2Item4_UnsubscribeFromAttributeModification(This,FromWhat)	\
    (This)->lpVtbl -> UnsubscribeFromAttributeModification(This,FromWhat)

#define IG2Item4_UnsubscribeFromDeletion(This)	\
    (This)->lpVtbl -> UnsubscribeFromDeletion(This)

#define IG2Item4_UnsubscribeFromIconColorChange(This)	\
    (This)->lpVtbl -> UnsubscribeFromIconColorChange(This)

#define IG2Item4_UnsubscribeFromCustomEvent(This,EventNames)	\
    (This)->lpVtbl -> UnsubscribeFromCustomEvent(This,EventNames)

#define IG2Item4_UnsubscribeFromAll(This)	\
    (This)->lpVtbl -> UnsubscribeFromAll(This)

#define IG2Item4_UnsubscribeFromValueChange(This)	\
    (This)->lpVtbl -> UnsubscribeFromValueChange(This)

#define IG2Item4_Subscriptions(This,ArrayOfSubscriptions)	\
    (This)->lpVtbl -> Subscriptions(This,ArrayOfSubscriptions)


#define IG2Item4_get_Icon(This,BackgroundColor,pVal)	\
    (This)->lpVtbl -> get_Icon(This,BackgroundColor,pVal)


#define IG2Item4_Init2(This,pDatum)	\
    (This)->lpVtbl -> Init2(This,pDatum)

#define IG2Item4_Init3(This,pDatum,pRef)	\
    (This)->lpVtbl -> Init3(This,pDatum,pRef)

#define IG2Item4_Git2(This,ppDatum)	\
    (This)->lpVtbl -> Git2(This,ppDatum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IG2Item4_Init2_Proxy( 
    IG2Item4 __RPC_FAR * This,
    /* [in] */ long pDatum);


void __RPC_STUB IG2Item4_Init2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IG2Item4_Init3_Proxy( 
    IG2Item4 __RPC_FAR * This,
    /* [in] */ long pDatum,
    /* [in] */ IG2ItemRef __RPC_FAR *pRef);


void __RPC_STUB IG2Item4_Init3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IG2Item4_Git2_Proxy( 
    IG2Item4 __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *ppDatum);


void __RPC_STUB IG2Item4_Git2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT AttrVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ G2Type __RPC_FAR *pType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ G2Type nType) = 0;
        
        virtual /* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ long pGsiAttr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2AttributeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Attribute __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Attribute __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Attribute __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Attribute __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Attribute __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IG2Attribute __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ VARIANT AttrVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2Attribute __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IG2Attribute __RPC_FAR * This,
            /* [retval][out] */ G2Type __RPC_FAR *pType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ G2Type nType);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2Attribute __RPC_FAR * This,
            /* [in] */ long pGsiAttr);
        
        END_INTERFACE
    } IG2AttributeVtbl;

    interface IG2Attribute
    {
        CONST_VTBL struct IG2AttributeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Attribute_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Attribute_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Attribute_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Attribute_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Attribute_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Attribute_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Attribute_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Attribute_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Attribute_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Attribute_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define IG2Attribute_put_Value(This,AttrVal)	\
    (This)->lpVtbl -> put_Value(This,AttrVal)

#define IG2Attribute_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IG2Attribute_get_Type(This,pType)	\
    (This)->lpVtbl -> get_Type(This,pType)

#define IG2Attribute_put_Type(This,nType)	\
    (This)->lpVtbl -> put_Type(This,nType)

#define IG2Attribute_Init(This,pGsiAttr)	\
    (This)->lpVtbl -> Init(This,pGsiAttr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Attribute_get_Name_Proxy( 
    IG2Attribute __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB IG2Attribute_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Attribute_put_Value_Proxy( 
    IG2Attribute __RPC_FAR * This,
    /* [in] */ VARIANT AttrVal);


void __RPC_STUB IG2Attribute_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Attribute_get_Value_Proxy( 
    IG2Attribute __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IG2Attribute_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Attribute_get_Type_Proxy( 
    IG2Attribute __RPC_FAR * This,
    /* [retval][out] */ G2Type __RPC_FAR *pType);


void __RPC_STUB IG2Attribute_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Attribute_put_Type_Proxy( 
    IG2Attribute __RPC_FAR * This,
    /* [in] */ G2Type nType);


void __RPC_STUB IG2Attribute_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][hidden] */ HRESULT STDMETHODCALLTYPE IG2Attribute_Init_Proxy( 
    IG2Attribute __RPC_FAR * This,
    /* [in] */ long pGsiAttr);


void __RPC_STUB IG2Attribute_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ long idx,
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ G2Type __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ G2Type newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
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
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ListOrArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2ListOrArray __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2ListOrArray __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ long idx,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ long idx,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [retval][out] */ G2Type __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ G2Type newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ long pGsiItem);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ long idx,
            /* [in] */ VARIANT varX);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Append )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ long idx,
            /* [in] */ VARIANT varX);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ VARIANT varX);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [in] */ long idx);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IG2ListOrArray __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        END_INTERFACE
    } IG2ListOrArrayVtbl;

    interface IG2ListOrArray
    {
        CONST_VTBL struct IG2ListOrArrayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2ListOrArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2ListOrArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2ListOrArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2ListOrArray_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2ListOrArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2ListOrArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2ListOrArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2ListOrArray_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2ListOrArray_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2ListOrArray_get_Item(This,idx,pVal)	\
    (This)->lpVtbl -> get_Item(This,idx,pVal)

#define IG2ListOrArray_put_Item(This,idx,newVal)	\
    (This)->lpVtbl -> put_Item(This,idx,newVal)

#define IG2ListOrArray_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IG2ListOrArray_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define IG2ListOrArray_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IG2ListOrArray_Init(This,pGsiItem)	\
    (This)->lpVtbl -> Init(This,pGsiItem)

#define IG2ListOrArray_Insert(This,idx,varX)	\
    (This)->lpVtbl -> Insert(This,idx,varX)

#define IG2ListOrArray_Append(This,idx,varX)	\
    (This)->lpVtbl -> Append(This,idx,varX)

#define IG2ListOrArray_Add(This,varX)	\
    (This)->lpVtbl -> Add(This,varX)

#define IG2ListOrArray_Remove(This,idx)	\
    (This)->lpVtbl -> Remove(This,idx)

#define IG2ListOrArray_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_get_Item_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ long idx,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IG2ListOrArray_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_put_Item_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ long idx,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IG2ListOrArray_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_get_Type_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [retval][out] */ G2Type __RPC_FAR *pVal);


void __RPC_STUB IG2ListOrArray_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_put_Type_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ G2Type newVal);


void __RPC_STUB IG2ListOrArray_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_get_Count_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IG2ListOrArray_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_Init_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ long pGsiItem);


void __RPC_STUB IG2ListOrArray_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_Insert_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ long idx,
    /* [in] */ VARIANT varX);


void __RPC_STUB IG2ListOrArray_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_Append_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ long idx,
    /* [in] */ VARIANT varX);


void __RPC_STUB IG2ListOrArray_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_Add_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ VARIANT varX);


void __RPC_STUB IG2ListOrArray_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_Remove_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [in] */ long idx);


void __RPC_STUB IG2ListOrArray_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2ListOrArray_get__NewEnum_Proxy( 
    IG2ListOrArray __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IG2ListOrArray_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IG2ListOrArray __RPC_FAR *pLaw,
            /* [in] */ long idx) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2LAElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2LAElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2LAElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2LAElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2LAElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2LAElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2LAElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2LAElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2LAElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2LAElement __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2LAElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IG2LAElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            IG2LAElement __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2LAElement __RPC_FAR * This,
            /* [in] */ IG2ListOrArray __RPC_FAR *pLaw,
            /* [in] */ long idx);
        
        END_INTERFACE
    } IG2LAElementVtbl;

    interface IG2LAElement
    {
        CONST_VTBL struct IG2LAElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2LAElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2LAElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2LAElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2LAElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2LAElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2LAElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2LAElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2LAElement_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2LAElement_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2LAElement_get_Item(This,pVal)	\
    (This)->lpVtbl -> get_Item(This,pVal)

#define IG2LAElement_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define IG2LAElement_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define IG2LAElement_Init(This,pLaw,idx)	\
    (This)->lpVtbl -> Init(This,pLaw,idx)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2LAElement_get_Item_Proxy( 
    IG2LAElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IG2LAElement_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2LAElement_get_Value_Proxy( 
    IG2LAElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IG2LAElement_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2LAElement_put_Value_Proxy( 
    IG2LAElement __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IG2LAElement_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2LAElement_Init_Proxy( 
    IG2LAElement __RPC_FAR * This,
    /* [in] */ IG2ListOrArray __RPC_FAR *pLaw,
    /* [in] */ long idx);


void __RPC_STUB IG2LAElement_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpperCase( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UpperCase( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2SymbolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Symbol __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Symbol __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Symbol __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Symbol __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Symbol __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Symbol __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Symbol __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Symbol __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Symbol __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IG2Symbol __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IG2Symbol __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpperCase )( 
            IG2Symbol __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UpperCase )( 
            IG2Symbol __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IG2SymbolVtbl;

    interface IG2Symbol
    {
        CONST_VTBL struct IG2SymbolVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Symbol_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Symbol_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Symbol_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Symbol_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Symbol_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Symbol_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Symbol_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Symbol_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Symbol_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Symbol_get_Item(This,pVal)	\
    (This)->lpVtbl -> get_Item(This,pVal)

#define IG2Symbol_put_Item(This,newVal)	\
    (This)->lpVtbl -> put_Item(This,newVal)

#define IG2Symbol_get_UpperCase(This,pVal)	\
    (This)->lpVtbl -> get_UpperCase(This,pVal)

#define IG2Symbol_put_UpperCase(This,newVal)	\
    (This)->lpVtbl -> put_UpperCase(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Symbol_get_Item_Proxy( 
    IG2Symbol __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IG2Symbol_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Symbol_put_Item_Proxy( 
    IG2Symbol __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IG2Symbol_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Symbol_get_UpperCase_Proxy( 
    IG2Symbol __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IG2Symbol_get_UpperCase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Symbol_put_UpperCase_Proxy( 
    IG2Symbol __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IG2Symbol_put_UpperCase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [in] */ unsigned short __RPC_FAR *pUUIDin,
            /* [in] */ long pCtx) = 0;
        
        virtual /* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE Git( 
            /* [out] */ unsigned short __RPC_FAR *pUUIDout,
            /* [out] */ long __RPC_FAR *pctx) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UUID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UUID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Gateway( 
            /* [in] */ IG2Gateway4 __RPC_FAR *gateway) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ItemRefVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2ItemRef __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2ItemRef __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2ItemRef __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2ItemRef __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2ItemRef __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ unsigned short __RPC_FAR *pUUIDin,
            /* [in] */ long pCtx);
        
        /* [hidden][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Git )( 
            IG2ItemRef __RPC_FAR * This,
            /* [out] */ unsigned short __RPC_FAR *pUUIDout,
            /* [out] */ long __RPC_FAR *pctx);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UUID )( 
            IG2ItemRef __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UUID )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [hidden][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Gateway )( 
            IG2ItemRef __RPC_FAR * This,
            /* [in] */ IG2Gateway4 __RPC_FAR *gateway);
        
        END_INTERFACE
    } IG2ItemRefVtbl;

    interface IG2ItemRef
    {
        CONST_VTBL struct IG2ItemRefVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2ItemRef_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2ItemRef_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2ItemRef_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2ItemRef_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2ItemRef_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2ItemRef_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2ItemRef_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2ItemRef_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2ItemRef_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2ItemRef_Init(This,pUUIDin,pCtx)	\
    (This)->lpVtbl -> Init(This,pUUIDin,pCtx)

#define IG2ItemRef_Git(This,pUUIDout,pctx)	\
    (This)->lpVtbl -> Git(This,pUUIDout,pctx)

#define IG2ItemRef_get_UUID(This,pVal)	\
    (This)->lpVtbl -> get_UUID(This,pVal)

#define IG2ItemRef_put_UUID(This,newVal)	\
    (This)->lpVtbl -> put_UUID(This,newVal)

#define IG2ItemRef_put_Gateway(This,gateway)	\
    (This)->lpVtbl -> put_Gateway(This,gateway)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ItemRef_Init_Proxy( 
    IG2ItemRef __RPC_FAR * This,
    /* [in] */ unsigned short __RPC_FAR *pUUIDin,
    /* [in] */ long pCtx);


void __RPC_STUB IG2ItemRef_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2ItemRef_Git_Proxy( 
    IG2ItemRef __RPC_FAR * This,
    /* [out] */ unsigned short __RPC_FAR *pUUIDout,
    /* [out] */ long __RPC_FAR *pctx);


void __RPC_STUB IG2ItemRef_Git_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2ItemRef_get_UUID_Proxy( 
    IG2ItemRef __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IG2ItemRef_get_UUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2ItemRef_put_UUID_Proxy( 
    IG2ItemRef __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IG2ItemRef_put_UUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2ItemRef_put_Gateway_Proxy( 
    IG2ItemRef __RPC_FAR * This,
    /* [in] */ IG2Gateway4 __RPC_FAR *gateway);


void __RPC_STUB IG2ItemRef_put_Gateway_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT __RPC_FAR *subHdl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SubscribeToItemRemoval( 
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *subHdl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromItemAddition( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromItemRemoval( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2WorkspaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Workspace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Workspace __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Workspace __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Workspace __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Workspace __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Workspace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Workspace __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Workspace __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Workspace __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToItemAddition )( 
            IG2Workspace __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *subHdl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToItemRemoval )( 
            IG2Workspace __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *subHdl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromItemAddition )( 
            IG2Workspace __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromItemRemoval )( 
            IG2Workspace __RPC_FAR * This);
        
        END_INTERFACE
    } IG2WorkspaceVtbl;

    interface IG2Workspace
    {
        CONST_VTBL struct IG2WorkspaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Workspace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Workspace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Workspace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Workspace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Workspace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Workspace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Workspace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Workspace_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Workspace_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Workspace_SubscribeToItemAddition(This,userData,subHdl)	\
    (This)->lpVtbl -> SubscribeToItemAddition(This,userData,subHdl)

#define IG2Workspace_SubscribeToItemRemoval(This,userData,subHdl)	\
    (This)->lpVtbl -> SubscribeToItemRemoval(This,userData,subHdl)

#define IG2Workspace_UnsubscribeFromItemAddition(This)	\
    (This)->lpVtbl -> UnsubscribeFromItemAddition(This)

#define IG2Workspace_UnsubscribeFromItemRemoval(This)	\
    (This)->lpVtbl -> UnsubscribeFromItemRemoval(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Workspace_SubscribeToItemAddition_Proxy( 
    IG2Workspace __RPC_FAR * This,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *subHdl);


void __RPC_STUB IG2Workspace_SubscribeToItemAddition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Workspace_SubscribeToItemRemoval_Proxy( 
    IG2Workspace __RPC_FAR * This,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *subHdl);


void __RPC_STUB IG2Workspace_SubscribeToItemRemoval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Workspace_UnsubscribeFromItemAddition_Proxy( 
    IG2Workspace __RPC_FAR * This);


void __RPC_STUB IG2Workspace_UnsubscribeFromItemAddition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Workspace_UnsubscribeFromItemRemoval_Proxy( 
    IG2Workspace __RPC_FAR * This);


void __RPC_STUB IG2Workspace_UnsubscribeFromItemRemoval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT __RPC_FAR *results) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnsubscribeFromSelection( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_g2UserMode( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_g2UserMode( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2WindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2Window __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2Window __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2Window __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2Window __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2Window __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2Window __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2Window __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhatAmI )( 
            IG2Window __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Duplicate )( 
            IG2Window __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pNewObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeToSelection )( 
            IG2Window __RPC_FAR * This,
            /* [in] */ VARIANT userData,
            /* [retval][out] */ VARIANT __RPC_FAR *results);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeFromSelection )( 
            IG2Window __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_g2UserMode )( 
            IG2Window __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_g2UserMode )( 
            IG2Window __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IG2WindowVtbl;

    interface IG2Window
    {
        CONST_VTBL struct IG2WindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2Window_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2Window_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2Window_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2Window_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2Window_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2Window_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2Window_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2Window_get_WhatAmI(This,pVal)	\
    (This)->lpVtbl -> get_WhatAmI(This,pVal)

#define IG2Window_Duplicate(This,pNewObj)	\
    (This)->lpVtbl -> Duplicate(This,pNewObj)


#define IG2Window_SubscribeToSelection(This,userData,results)	\
    (This)->lpVtbl -> SubscribeToSelection(This,userData,results)

#define IG2Window_UnsubscribeFromSelection(This)	\
    (This)->lpVtbl -> UnsubscribeFromSelection(This)

#define IG2Window_get_g2UserMode(This,pVal)	\
    (This)->lpVtbl -> get_g2UserMode(This,pVal)

#define IG2Window_put_g2UserMode(This,newVal)	\
    (This)->lpVtbl -> put_g2UserMode(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Window_SubscribeToSelection_Proxy( 
    IG2Window __RPC_FAR * This,
    /* [in] */ VARIANT userData,
    /* [retval][out] */ VARIANT __RPC_FAR *results);


void __RPC_STUB IG2Window_SubscribeToSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IG2Window_UnsubscribeFromSelection_Proxy( 
    IG2Window __RPC_FAR * This);


void __RPC_STUB IG2Window_UnsubscribeFromSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2Window_get_g2UserMode_Proxy( 
    IG2Window __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IG2Window_get_g2UserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2Window_put_g2UserMode_Proxy( 
    IG2Window __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IG2Window_put_g2UserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



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
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HighThroughput( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IG2ComConfiguratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IG2ComConfigurator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IG2ComConfigurator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HighThroughput )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HighThroughput )( 
            IG2ComConfigurator __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IG2ComConfiguratorVtbl;

    interface IG2ComConfigurator
    {
        CONST_VTBL struct IG2ComConfiguratorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IG2ComConfigurator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IG2ComConfigurator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IG2ComConfigurator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IG2ComConfigurator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IG2ComConfigurator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IG2ComConfigurator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IG2ComConfigurator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IG2ComConfigurator_get_HighThroughput(This,pVal)	\
    (This)->lpVtbl -> get_HighThroughput(This,pVal)

#define IG2ComConfigurator_put_HighThroughput(This,newVal)	\
    (This)->lpVtbl -> put_HighThroughput(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IG2ComConfigurator_get_HighThroughput_Proxy( 
    IG2ComConfigurator __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IG2ComConfigurator_get_HighThroughput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IG2ComConfigurator_put_HighThroughput_Proxy( 
    IG2ComConfigurator __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IG2ComConfigurator_put_HighThroughput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IG2ComConfigurator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_G2Com_0227 */
/* [local] */ 






extern RPC_IF_HANDLE __MIDL_itf_G2Com_0227_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_G2Com_0227_v0_0_s_ifspec;


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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _G2Events __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _G2Events __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _G2Events __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _G2Events __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _G2Events __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _G2Events __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _G2Events __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _G2EventsVtbl;

    interface _G2Events
    {
        CONST_VTBL struct _G2EventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _G2Events_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _G2Events_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _G2Events_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _G2Events_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _G2Events_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _G2Events_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _G2Events_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

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

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
