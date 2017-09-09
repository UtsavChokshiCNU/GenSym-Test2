

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Wed Nov 25 14:30:10 2009
 */
/* Compiler settings for .\PISDKParse.idl:
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


#ifndef __PISDKParse_h__
#define __PISDKParse_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFunction_FWD_DEFINED__
#define __IFunction_FWD_DEFINED__
typedef interface IFunction IFunction;
#endif 	/* __IFunction_FWD_DEFINED__ */


#ifndef __IFunction2_FWD_DEFINED__
#define __IFunction2_FWD_DEFINED__
typedef interface IFunction2 IFunction2;
#endif 	/* __IFunction2_FWD_DEFINED__ */


#ifndef __IFunctionLib_FWD_DEFINED__
#define __IFunctionLib_FWD_DEFINED__
typedef interface IFunctionLib IFunctionLib;
#endif 	/* __IFunctionLib_FWD_DEFINED__ */


#ifndef __IFunctionLibs_FWD_DEFINED__
#define __IFunctionLibs_FWD_DEFINED__
typedef interface IFunctionLibs IFunctionLibs;
#endif 	/* __IFunctionLibs_FWD_DEFINED__ */


#ifndef __FunctionLibs_FWD_DEFINED__
#define __FunctionLibs_FWD_DEFINED__

#ifdef __cplusplus
typedef class FunctionLibs FunctionLibs;
#else
typedef struct FunctionLibs FunctionLibs;
#endif /* __cplusplus */

#endif 	/* __FunctionLibs_FWD_DEFINED__ */


#ifndef __INameResolvers_FWD_DEFINED__
#define __INameResolvers_FWD_DEFINED__
typedef interface INameResolvers INameResolvers;
#endif 	/* __INameResolvers_FWD_DEFINED__ */


#ifndef __NameResolvers_FWD_DEFINED__
#define __NameResolvers_FWD_DEFINED__

#ifdef __cplusplus
typedef class NameResolvers NameResolvers;
#else
typedef struct NameResolvers NameResolvers;
#endif /* __cplusplus */

#endif 	/* __NameResolvers_FWD_DEFINED__ */


#ifndef __IReadLock_FWD_DEFINED__
#define __IReadLock_FWD_DEFINED__
typedef interface IReadLock IReadLock;
#endif 	/* __IReadLock_FWD_DEFINED__ */


#ifndef ___EvalContext_FWD_DEFINED__
#define ___EvalContext_FWD_DEFINED__
typedef interface _EvalContext _EvalContext;
#endif 	/* ___EvalContext_FWD_DEFINED__ */


#ifndef __EvalContext_FWD_DEFINED__
#define __EvalContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class EvalContext EvalContext;
#else
typedef struct EvalContext EvalContext;
#endif /* __cplusplus */

#endif 	/* __EvalContext_FWD_DEFINED__ */


#ifndef ___PIExpression_FWD_DEFINED__
#define ___PIExpression_FWD_DEFINED__
typedef interface _PIExpression _PIExpression;
#endif 	/* ___PIExpression_FWD_DEFINED__ */


#ifndef __PIExpression_FWD_DEFINED__
#define __PIExpression_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIExpression PIExpression;
#else
typedef struct PIExpression PIExpression;
#endif /* __cplusplus */

#endif 	/* __PIExpression_FWD_DEFINED__ */


#ifndef __PITimeExpression_FWD_DEFINED__
#define __PITimeExpression_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeExpression PITimeExpression;
#else
typedef struct PITimeExpression PITimeExpression;
#endif /* __cplusplus */

#endif 	/* __PITimeExpression_FWD_DEFINED__ */


#ifndef ___PIExpressions_FWD_DEFINED__
#define ___PIExpressions_FWD_DEFINED__
typedef interface _PIExpressions _PIExpressions;
#endif 	/* ___PIExpressions_FWD_DEFINED__ */


#ifndef __PIExpressions_FWD_DEFINED__
#define __PIExpressions_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIExpressions PIExpressions;
#else
typedef struct PIExpressions PIExpressions;
#endif /* __cplusplus */

#endif 	/* __PIExpressions_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_PISDKParse_0000 */
/* [local] */ 












extern RPC_IF_HANDLE __MIDL_itf_PISDKParse_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PISDKParse_0000_v0_0_s_ifspec;


#ifndef __PISDKParse_LIBRARY_DEFINED__
#define __PISDKParse_LIBRARY_DEFINED__

/* library PISDKParse */
/* [helpstring][helpfile][version][uuid] */ 

typedef /* [helpstring] */ 
enum ppeErrorConstants
    {	ppeEMPTYFUNCTIONLIB	= 0x800405a3,
	ppeEXPECTEDAND	= 0x800404f5,
	ppeEXPECTEDELSE	= 0x800404f3,
	ppeEXPECTEDEOS	= 0x800404f7,
	ppeEXPECTEDMINUTES	= 0x800404f8,
	ppeEXPECTEDNULL	= 0x800404f0,
	ppeEXPECTEDRPAREN	= 0x800404f1,
	ppeEXPECTEDSECONDS	= 0x800404f9,
	ppeEXPECTEDTHEN	= 0x800404f2,
	ppeHUGEEXPONENT	= 0x800404ef,
	ppeLIBITEMNOTFUNCTION	= 0x800405a4,
	ppeMALFORMEDTOKEN	= 0x800404ee,
	ppeNEEDEVALCONTEXT	= 0x800405a1,
	ppeNEEDFUNCTIONLIB	= 0x800405a2,
	ppeNEEDNAMERESOLVER	= 0x800405a5,
	ppeNOSTRINGDELIM	= 0x800404ed,
	ppeNOTARESOLVER	= 0x800405a6,
	ppeNOTASSOCIATIVE	= 0x800404f6,
	ppeSYNTAX	= 0x800404f4,
	ppeTOOMANYMINUTES	= 0x800404fa,
	ppeTOOMANYSECONDS	= 0x800404fb,
	ppeTYPEMISMATCH	= 0x800404ff,
	ppeWRONGNOARGS	= 0x800404fe,
	ppeNEGATIVEARG	= 0x800405a9,
	ppeARGERROR	= 0x800405aa
    } 	ppeErrorConstants;


EXTERN_C const IID LIBID_PISDKParse;

#ifndef __IFunction_INTERFACE_DEFINED__
#define __IFunction_INTERFACE_DEFINED__

/* interface IFunction */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("289040A2-599F-11d2-8118-00A0240B7FDC")
    IFunction : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ArgInfo( 
            /* [retval][out] */ /* external definition not present */ _NamedValues **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsVolatile( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Evaluate( 
            /* [in] */ SAFEARRAY * ActualArgs,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFunction * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFunction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFunction * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IFunction * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ArgInfo )( 
            IFunction * This,
            /* [retval][out] */ /* external definition not present */ _NamedValues **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsVolatile )( 
            IFunction * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Evaluate )( 
            IFunction * This,
            /* [in] */ SAFEARRAY * ActualArgs,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IFunctionVtbl;

    interface IFunction
    {
        CONST_VTBL struct IFunctionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFunction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFunction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFunction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFunction_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IFunction_get_ArgInfo(This,pVal)	\
    (This)->lpVtbl -> get_ArgInfo(This,pVal)

#define IFunction_get_IsVolatile(This,pVal)	\
    (This)->lpVtbl -> get_IsVolatile(This,pVal)

#define IFunction_Evaluate(This,ActualArgs,pVal)	\
    (This)->lpVtbl -> Evaluate(This,ActualArgs,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IFunction_get_Name_Proxy( 
    IFunction * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IFunction_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IFunction_get_ArgInfo_Proxy( 
    IFunction * This,
    /* [retval][out] */ /* external definition not present */ _NamedValues **pVal);


void __RPC_STUB IFunction_get_ArgInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IFunction_get_IsVolatile_Proxy( 
    IFunction * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IFunction_get_IsVolatile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IFunction_Evaluate_Proxy( 
    IFunction * This,
    /* [in] */ SAFEARRAY * ActualArgs,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IFunction_Evaluate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFunction_INTERFACE_DEFINED__ */


#ifndef __IFunction2_INTERFACE_DEFINED__
#define __IFunction2_INTERFACE_DEFINED__

/* interface IFunction2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFunction2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59528041-62ED-11d2-811B-00A0240B7FDC")
    IFunction2 : public IFunction
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Evaluate2( 
            /* [in] */ SAFEARRAY * SymbolicArgs,
            /* [defaultvalue][in] */ _EvalContext *Context,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFunction2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFunction2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFunction2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFunction2 * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IFunction2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ArgInfo )( 
            IFunction2 * This,
            /* [retval][out] */ /* external definition not present */ _NamedValues **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsVolatile )( 
            IFunction2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Evaluate )( 
            IFunction2 * This,
            /* [in] */ SAFEARRAY * ActualArgs,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Evaluate2 )( 
            IFunction2 * This,
            /* [in] */ SAFEARRAY * SymbolicArgs,
            /* [defaultvalue][in] */ _EvalContext *Context,
            /* [retval][out] */ VARIANT *pVal);
        
        END_INTERFACE
    } IFunction2Vtbl;

    interface IFunction2
    {
        CONST_VTBL struct IFunction2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFunction2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFunction2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFunction2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFunction2_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IFunction2_get_ArgInfo(This,pVal)	\
    (This)->lpVtbl -> get_ArgInfo(This,pVal)

#define IFunction2_get_IsVolatile(This,pVal)	\
    (This)->lpVtbl -> get_IsVolatile(This,pVal)

#define IFunction2_Evaluate(This,ActualArgs,pVal)	\
    (This)->lpVtbl -> Evaluate(This,ActualArgs,pVal)


#define IFunction2_Evaluate2(This,SymbolicArgs,Context,pVal)	\
    (This)->lpVtbl -> Evaluate2(This,SymbolicArgs,Context,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IFunction2_Evaluate2_Proxy( 
    IFunction2 * This,
    /* [in] */ SAFEARRAY * SymbolicArgs,
    /* [defaultvalue][in] */ _EvalContext *Context,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IFunction2_Evaluate2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFunction2_INTERFACE_DEFINED__ */


#ifndef __IFunctionLib_INTERFACE_DEFINED__
#define __IFunctionLib_INTERFACE_DEFINED__

/* interface IFunctionLib */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFunctionLib;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88E9DA31-62ED-11d2-811B-00A0240B7FDC")
    IFunctionLib : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Functions( 
            /* [retval][out] */ /* external definition not present */ _NamedValues **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFunctionLibVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFunctionLib * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFunctionLib * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFunctionLib * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IFunctionLib * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Functions )( 
            IFunctionLib * This,
            /* [retval][out] */ /* external definition not present */ _NamedValues **pVal);
        
        END_INTERFACE
    } IFunctionLibVtbl;

    interface IFunctionLib
    {
        CONST_VTBL struct IFunctionLibVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFunctionLib_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFunctionLib_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFunctionLib_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFunctionLib_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IFunctionLib_get_Functions(This,pVal)	\
    (This)->lpVtbl -> get_Functions(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IFunctionLib_get_Name_Proxy( 
    IFunctionLib * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IFunctionLib_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFunctionLib_get_Functions_Proxy( 
    IFunctionLib * This,
    /* [retval][out] */ /* external definition not present */ _NamedValues **pVal);


void __RPC_STUB IFunctionLib_get_Functions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFunctionLib_INTERFACE_DEFINED__ */


#ifndef __IFunctionLibs_INTERFACE_DEFINED__
#define __IFunctionLibs_INTERFACE_DEFINED__

/* interface IFunctionLibs */
/* [unique][helpcontext][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFunctionLibs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D6D9F543-D5D1-11d2-BD68-00C04F779EB2")
    IFunctionLibs : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IFunctionLib *pNewItem,
            /* [defaultvalue][in] */ long Before = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IFunctionLib **pVal) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFunctionLibsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFunctionLibs * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFunctionLibs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFunctionLibs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFunctionLibs * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFunctionLibs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFunctionLibs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFunctionLibs * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IFunctionLibs * This,
            /* [in] */ IFunctionLib *pNewItem,
            /* [defaultvalue][in] */ long Before);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFunctionLibs * This);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFunctionLibs * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFunctionLibs * This,
            /* [in] */ long Index,
            /* [retval][out] */ IFunctionLib **pVal);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFunctionLibs * This,
            /* [retval][out] */ IUnknown **pVal);
        
        END_INTERFACE
    } IFunctionLibsVtbl;

    interface IFunctionLibs
    {
        CONST_VTBL struct IFunctionLibsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFunctionLibs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFunctionLibs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFunctionLibs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFunctionLibs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFunctionLibs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFunctionLibs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFunctionLibs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFunctionLibs_Add(This,pNewItem,Before)	\
    (This)->lpVtbl -> Add(This,pNewItem,Before)

#define IFunctionLibs_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IFunctionLibs_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IFunctionLibs_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define IFunctionLibs_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFunctionLibs_Add_Proxy( 
    IFunctionLibs * This,
    /* [in] */ IFunctionLib *pNewItem,
    /* [defaultvalue][in] */ long Before);


void __RPC_STUB IFunctionLibs_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFunctionLibs_Clear_Proxy( 
    IFunctionLibs * This);


void __RPC_STUB IFunctionLibs_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFunctionLibs_get_Count_Proxy( 
    IFunctionLibs * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IFunctionLibs_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFunctionLibs_get_Item_Proxy( 
    IFunctionLibs * This,
    /* [in] */ long Index,
    /* [retval][out] */ IFunctionLib **pVal);


void __RPC_STUB IFunctionLibs_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IFunctionLibs_get__NewEnum_Proxy( 
    IFunctionLibs * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB IFunctionLibs_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFunctionLibs_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FunctionLibs;

#ifdef __cplusplus

class DECLSPEC_UUID("ABEEB501-48D2-11d4-BDEB-00C04F779EB2")
FunctionLibs;
#endif

#ifndef __INameResolvers_INTERFACE_DEFINED__
#define __INameResolvers_INTERFACE_DEFINED__

/* interface INameResolvers */
/* [unique][helpcontext][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_INameResolvers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D6D9F541-D5D1-11d2-BD68-00C04F779EB2")
    INameResolvers : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ /* external definition not present */ INameResolver *pNewItem,
            /* [defaultvalue][in] */ long Before = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ /* external definition not present */ INameResolver **pVal) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INameResolversVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INameResolvers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INameResolvers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INameResolvers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            INameResolvers * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            INameResolvers * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            INameResolvers * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            INameResolvers * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            INameResolvers * This,
            /* [in] */ /* external definition not present */ INameResolver *pNewItem,
            /* [defaultvalue][in] */ long Before);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            INameResolvers * This);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            INameResolvers * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            INameResolvers * This,
            /* [in] */ long Index,
            /* [retval][out] */ /* external definition not present */ INameResolver **pVal);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            INameResolvers * This,
            /* [retval][out] */ IUnknown **pVal);
        
        END_INTERFACE
    } INameResolversVtbl;

    interface INameResolvers
    {
        CONST_VTBL struct INameResolversVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INameResolvers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INameResolvers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INameResolvers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INameResolvers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INameResolvers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INameResolvers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INameResolvers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INameResolvers_Add(This,pNewItem,Before)	\
    (This)->lpVtbl -> Add(This,pNewItem,Before)

#define INameResolvers_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define INameResolvers_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define INameResolvers_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define INameResolvers_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE INameResolvers_Add_Proxy( 
    INameResolvers * This,
    /* [in] */ /* external definition not present */ INameResolver *pNewItem,
    /* [defaultvalue][in] */ long Before);


void __RPC_STUB INameResolvers_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE INameResolvers_Clear_Proxy( 
    INameResolvers * This);


void __RPC_STUB INameResolvers_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INameResolvers_get_Count_Proxy( 
    INameResolvers * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB INameResolvers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INameResolvers_get_Item_Proxy( 
    INameResolvers * This,
    /* [in] */ long Index,
    /* [retval][out] */ /* external definition not present */ INameResolver **pVal);


void __RPC_STUB INameResolvers_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE INameResolvers_get__NewEnum_Proxy( 
    INameResolvers * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB INameResolvers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INameResolvers_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NameResolvers;

#ifdef __cplusplus

class DECLSPEC_UUID("ABEEB502-48D2-11d4-BDEB-00C04F779EB2")
NameResolvers;
#endif

#ifndef __IReadLock_INTERFACE_DEFINED__
#define __IReadLock_INTERFACE_DEFINED__

/* interface IReadLock */
/* [unique][local][restricted][uuid][object] */ 


EXTERN_C const IID IID_IReadLock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("60DD6771-D12A-11d2-BD65-00C04F779EB2")
    IReadLock : public IUnknown
    {
    public:
        virtual void STDMETHODCALLTYPE IncrementLock( void) = 0;
        
        virtual void STDMETHODCALLTYPE DecrementLock( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReadLockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadLock * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadLock * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadLock * This);
        
        void ( STDMETHODCALLTYPE *IncrementLock )( 
            IReadLock * This);
        
        void ( STDMETHODCALLTYPE *DecrementLock )( 
            IReadLock * This);
        
        END_INTERFACE
    } IReadLockVtbl;

    interface IReadLock
    {
        CONST_VTBL struct IReadLockVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadLock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReadLock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReadLock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReadLock_IncrementLock(This)	\
    (This)->lpVtbl -> IncrementLock(This)

#define IReadLock_DecrementLock(This)	\
    (This)->lpVtbl -> DecrementLock(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



void STDMETHODCALLTYPE IReadLock_IncrementLock_Proxy( 
    IReadLock * This);


void __RPC_STUB IReadLock_IncrementLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


void STDMETHODCALLTYPE IReadLock_DecrementLock_Proxy( 
    IReadLock * This);


void __RPC_STUB IReadLock_DecrementLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReadLock_INTERFACE_DEFINED__ */


#ifndef ___EvalContext_INTERFACE_DEFINED__
#define ___EvalContext_INTERFACE_DEFINED__

/* interface _EvalContext */
/* [unique][helpcontext][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__EvalContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D6D9F542-D5D1-11d2-BD68-00C04F779EB2")
    _EvalContext : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NameResolvers( 
            /* [retval][out] */ INameResolvers **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FunctionLibs( 
            /* [retval][out] */ IFunctionLibs **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurTime( 
            /* [retval][out] */ /* external definition not present */ _PITime **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_CurTime( 
            /* [in] */ /* external definition not present */ _PITime *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _EvalContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _EvalContext * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _EvalContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _EvalContext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _EvalContext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _EvalContext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _EvalContext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _EvalContext * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NameResolvers )( 
            _EvalContext * This,
            /* [retval][out] */ INameResolvers **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FunctionLibs )( 
            _EvalContext * This,
            /* [retval][out] */ IFunctionLibs **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurTime )( 
            _EvalContext * This,
            /* [retval][out] */ /* external definition not present */ _PITime **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_CurTime )( 
            _EvalContext * This,
            /* [in] */ /* external definition not present */ _PITime *newVal);
        
        END_INTERFACE
    } _EvalContextVtbl;

    interface _EvalContext
    {
        CONST_VTBL struct _EvalContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _EvalContext_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _EvalContext_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _EvalContext_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _EvalContext_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _EvalContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _EvalContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _EvalContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _EvalContext_get_NameResolvers(This,pVal)	\
    (This)->lpVtbl -> get_NameResolvers(This,pVal)

#define _EvalContext_get_FunctionLibs(This,pVal)	\
    (This)->lpVtbl -> get_FunctionLibs(This,pVal)

#define _EvalContext_get_CurTime(This,pVal)	\
    (This)->lpVtbl -> get_CurTime(This,pVal)

#define _EvalContext_putref_CurTime(This,newVal)	\
    (This)->lpVtbl -> putref_CurTime(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _EvalContext_get_NameResolvers_Proxy( 
    _EvalContext * This,
    /* [retval][out] */ INameResolvers **pVal);


void __RPC_STUB _EvalContext_get_NameResolvers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _EvalContext_get_FunctionLibs_Proxy( 
    _EvalContext * This,
    /* [retval][out] */ IFunctionLibs **pVal);


void __RPC_STUB _EvalContext_get_FunctionLibs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _EvalContext_get_CurTime_Proxy( 
    _EvalContext * This,
    /* [retval][out] */ /* external definition not present */ _PITime **pVal);


void __RPC_STUB _EvalContext_get_CurTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE _EvalContext_putref_CurTime_Proxy( 
    _EvalContext * This,
    /* [in] */ /* external definition not present */ _PITime *newVal);


void __RPC_STUB _EvalContext_putref_CurTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___EvalContext_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_EvalContext;

#ifdef __cplusplus

class DECLSPEC_UUID("9E5A6038-F82F-11D2-BD73-00C04F779EB2")
EvalContext;
#endif

#ifndef ___PIExpression_INTERFACE_DEFINED__
#define ___PIExpression_INTERFACE_DEFINED__

/* interface _PIExpression */
/* [unique][helpcontext][helpstring][nonextensible][dual][hidden][uuid][object] */ 

typedef /* [public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("294A1D51-6493-11d2-811C-00A0240B7FDC") 
enum __MIDL__PIExpression_0001
    {	pexVolatile	= 0,
	pexContextSensitive	= 1,
	pexConstant	= 2
    } 	pexVolatilityConstants;

typedef /* [public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("156D6BB1-C31C-11d2-BD5F-00C04F779EB2") 
enum __MIDL__PIExpression_0002
    {	pexLiteral	= 0x1,
	pexCurTime	= 0x2,
	pexGenString	= 0x3,
	pexIdentifier	= 0x4,
	pexIfOp	= 0x8,
	pexOrOp	= 0x20,
	pexAndOp	= 0x30,
	pexNotOp	= 0x40,
	pexLTOp	= 0x50,
	pexEQOp	= 0x51,
	pexGTOp	= 0x52,
	pexLEOp	= 0x53,
	pexNEOp	= 0x54,
	pexGEOp	= 0x55,
	pexInOp	= 0x56,
	pexNotInOp	= 0x57,
	pexLikeOp	= 0x58,
	pexNotLikeOp	= 0x59,
	pexIsNullOp	= 0x5c,
	pexNotNullOp	= 0x5d,
	pexRangeOp	= 0x60,
	pexAddOp	= 0x70,
	pexSubOp	= 0x71,
	pexConcatOp	= 0x72,
	pexMulOp	= 0x80,
	pexDivOp	= 0x81,
	pexModOp	= 0x82,
	pexRaiseOp	= 0x90,
	pexUMinusOp	= 0xa0,
	pexDotOp	= 0xb0,
	pexIntervalOp	= 0xfd,
	pexFCallOp	= 0xfe,
	pexErrorOp	= 0xff
    } 	pexOperatorCodes;


EXTERN_C const IID IID__PIExpression;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6A899A5-599D-11D2-8118-00A0240B7FDC")
    _PIExpression : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Source( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Source( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EvalContext( 
            /* [retval][out] */ _EvalContext **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_EvalContext( 
            /* [in] */ _EvalContext *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Volatility( 
            /* [retval][out] */ pexVolatilityConstants *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Decompose( 
            /* [out] */ pexOperatorCodes *OpCode,
            /* [out] */ BSTR *OpString,
            /* [out] */ IFunction **pFunc,
            /* [out] */ _PIExpressions **SubExpressions) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocaleIndependent( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocaleIndependent( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PIExpressionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PIExpression * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PIExpression * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PIExpression * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PIExpression * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PIExpression * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PIExpression * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PIExpression * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            _PIExpression * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Source )( 
            _PIExpression * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Source )( 
            _PIExpression * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EvalContext )( 
            _PIExpression * This,
            /* [retval][out] */ _EvalContext **pVal);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_EvalContext )( 
            _PIExpression * This,
            /* [in] */ _EvalContext *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Volatility )( 
            _PIExpression * This,
            /* [retval][out] */ pexVolatilityConstants *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Decompose )( 
            _PIExpression * This,
            /* [out] */ pexOperatorCodes *OpCode,
            /* [out] */ BSTR *OpString,
            /* [out] */ IFunction **pFunc,
            /* [out] */ _PIExpressions **SubExpressions);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LocaleIndependent )( 
            _PIExpression * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LocaleIndependent )( 
            _PIExpression * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } _PIExpressionVtbl;

    interface _PIExpression
    {
        CONST_VTBL struct _PIExpressionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PIExpression_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PIExpression_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PIExpression_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PIExpression_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PIExpression_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PIExpression_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PIExpression_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PIExpression_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define _PIExpression_get_Source(This,pVal)	\
    (This)->lpVtbl -> get_Source(This,pVal)

#define _PIExpression_put_Source(This,newVal)	\
    (This)->lpVtbl -> put_Source(This,newVal)

#define _PIExpression_get_EvalContext(This,pVal)	\
    (This)->lpVtbl -> get_EvalContext(This,pVal)

#define _PIExpression_putref_EvalContext(This,newVal)	\
    (This)->lpVtbl -> putref_EvalContext(This,newVal)

#define _PIExpression_get_Volatility(This,pVal)	\
    (This)->lpVtbl -> get_Volatility(This,pVal)

#define _PIExpression_Decompose(This,OpCode,OpString,pFunc,SubExpressions)	\
    (This)->lpVtbl -> Decompose(This,OpCode,OpString,pFunc,SubExpressions)

#define _PIExpression_get_LocaleIndependent(This,pVal)	\
    (This)->lpVtbl -> get_LocaleIndependent(This,pVal)

#define _PIExpression_put_LocaleIndependent(This,newVal)	\
    (This)->lpVtbl -> put_LocaleIndependent(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpression_get_Value_Proxy( 
    _PIExpression * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB _PIExpression_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpression_get_Source_Proxy( 
    _PIExpression * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB _PIExpression_get_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE _PIExpression_put_Source_Proxy( 
    _PIExpression * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB _PIExpression_put_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpression_get_EvalContext_Proxy( 
    _PIExpression * This,
    /* [retval][out] */ _EvalContext **pVal);


void __RPC_STUB _PIExpression_get_EvalContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE _PIExpression_putref_EvalContext_Proxy( 
    _PIExpression * This,
    /* [in] */ _EvalContext *newVal);


void __RPC_STUB _PIExpression_putref_EvalContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpression_get_Volatility_Proxy( 
    _PIExpression * This,
    /* [retval][out] */ pexVolatilityConstants *pVal);


void __RPC_STUB _PIExpression_get_Volatility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE _PIExpression_Decompose_Proxy( 
    _PIExpression * This,
    /* [out] */ pexOperatorCodes *OpCode,
    /* [out] */ BSTR *OpString,
    /* [out] */ IFunction **pFunc,
    /* [out] */ _PIExpressions **SubExpressions);


void __RPC_STUB _PIExpression_Decompose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpression_get_LocaleIndependent_Proxy( 
    _PIExpression * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB _PIExpression_get_LocaleIndependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE _PIExpression_put_LocaleIndependent_Proxy( 
    _PIExpression * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB _PIExpression_put_LocaleIndependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PIExpression_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIExpression;

#ifdef __cplusplus

class DECLSPEC_UUID("A6A899A6-599D-11D2-8118-00A0240B7FDC")
PIExpression;
#endif

EXTERN_C const CLSID CLSID_PITimeExpression;

#ifdef __cplusplus

class DECLSPEC_UUID("59519CF1-79B8-4d0d-9B8C-B0904B01E3C9")
PITimeExpression;
#endif

#ifndef ___PIExpressions_INTERFACE_DEFINED__
#define ___PIExpressions_INTERFACE_DEFINED__

/* interface _PIExpressions */
/* [unique][helpcontext][helpstring][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PIExpressions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5669EFB6-C313-11D2-BD5F-00C04F779EB2")
    _PIExpressions : public IDispatch
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ _PIExpression **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ _PIExpression *pExpr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PIExpressionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _PIExpressions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _PIExpressions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _PIExpressions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _PIExpressions * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _PIExpressions * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _PIExpressions * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _PIExpressions * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            _PIExpressions * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            _PIExpressions * This,
            /* [in] */ long Index,
            /* [retval][out] */ _PIExpression **pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            _PIExpressions * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            _PIExpressions * This,
            /* [in] */ long Index);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            _PIExpressions * This,
            /* [in] */ _PIExpression *pExpr);
        
        END_INTERFACE
    } _PIExpressionsVtbl;

    interface _PIExpressions
    {
        CONST_VTBL struct _PIExpressionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PIExpressions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PIExpressions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PIExpressions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PIExpressions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PIExpressions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PIExpressions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PIExpressions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PIExpressions_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _PIExpressions_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define _PIExpressions_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _PIExpressions_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define _PIExpressions_Add(This,pExpr)	\
    (This)->lpVtbl -> Add(This,pExpr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpressions_get__NewEnum_Proxy( 
    _PIExpressions * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB _PIExpressions_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpressions_get_Item_Proxy( 
    _PIExpressions * This,
    /* [in] */ long Index,
    /* [retval][out] */ _PIExpression **pVal);


void __RPC_STUB _PIExpressions_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE _PIExpressions_get_Count_Proxy( 
    _PIExpressions * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB _PIExpressions_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE _PIExpressions_Remove_Proxy( 
    _PIExpressions * This,
    /* [in] */ long Index);


void __RPC_STUB _PIExpressions_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE _PIExpressions_Add_Proxy( 
    _PIExpressions * This,
    /* [in] */ _PIExpression *pExpr);


void __RPC_STUB _PIExpressions_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PIExpressions_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIExpressions;

#ifdef __cplusplus

class DECLSPEC_UUID("5669EFB7-C313-11D2-BD5F-00C04F779EB2")
PIExpressions;
#endif
#endif /* __PISDKParse_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


