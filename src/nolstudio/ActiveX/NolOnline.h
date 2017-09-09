/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 28 08:09:38 2009
 */
/* Compiler settings for C:\G2\src\nolstudio\ActiveX\NolOnline.idl:
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

#ifndef __NolOnline_h__
#define __NolOnline_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INolPredictor_FWD_DEFINED__
#define __INolPredictor_FWD_DEFINED__
typedef interface INolPredictor INolPredictor;
#endif 	/* __INolPredictor_FWD_DEFINED__ */


#ifndef ___INolPredictorEvents_FWD_DEFINED__
#define ___INolPredictorEvents_FWD_DEFINED__
typedef interface _INolPredictorEvents _INolPredictorEvents;
#endif 	/* ___INolPredictorEvents_FWD_DEFINED__ */


#ifndef __NolPredictor_FWD_DEFINED__
#define __NolPredictor_FWD_DEFINED__

#ifdef __cplusplus
typedef class NolPredictor NolPredictor;
#else
typedef struct NolPredictor NolPredictor;
#endif /* __cplusplus */

#endif 	/* __NolPredictor_FWD_DEFINED__ */


#ifndef ___INolPredictorPropEvents_FWD_DEFINED__
#define ___INolPredictorPropEvents_FWD_DEFINED__
typedef interface _INolPredictorPropEvents _INolPredictorPropEvents;
#endif 	/* ___INolPredictorPropEvents_FWD_DEFINED__ */


#ifndef __INolOptimizer_FWD_DEFINED__
#define __INolOptimizer_FWD_DEFINED__
typedef interface INolOptimizer INolOptimizer;
#endif 	/* __INolOptimizer_FWD_DEFINED__ */


#ifndef __NolPredictorProp_FWD_DEFINED__
#define __NolPredictorProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class NolPredictorProp NolPredictorProp;
#else
typedef struct NolPredictorProp NolPredictorProp;
#endif /* __cplusplus */

#endif 	/* __NolPredictorProp_FWD_DEFINED__ */


#ifndef ___INolOptimizerEvents_FWD_DEFINED__
#define ___INolOptimizerEvents_FWD_DEFINED__
typedef interface _INolOptimizerEvents _INolOptimizerEvents;
#endif 	/* ___INolOptimizerEvents_FWD_DEFINED__ */


#ifndef __NolOptimizer_FWD_DEFINED__
#define __NolOptimizer_FWD_DEFINED__

#ifdef __cplusplus
typedef class NolOptimizer NolOptimizer;
#else
typedef struct NolOptimizer NolOptimizer;
#endif /* __cplusplus */

#endif 	/* __NolOptimizer_FWD_DEFINED__ */


#ifndef ___INolOptimizerPropEvents_FWD_DEFINED__
#define ___INolOptimizerPropEvents_FWD_DEFINED__
typedef interface _INolOptimizerPropEvents _INolOptimizerPropEvents;
#endif 	/* ___INolOptimizerPropEvents_FWD_DEFINED__ */


#ifndef __NolOptimizerProp_FWD_DEFINED__
#define __NolOptimizerProp_FWD_DEFINED__

#ifdef __cplusplus
typedef class NolOptimizerProp NolOptimizerProp;
#else
typedef struct NolOptimizerProp NolOptimizerProp;
#endif /* __cplusplus */

#endif 	/* __NolOptimizerProp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INolPredictor_INTERFACE_DEFINED__
#define __INolPredictor_INTERFACE_DEFINED__

/* interface INolPredictor */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INolPredictor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CDE0EF5F-4E9A-11D4-B8A0-0000861E0389")
    INolPredictor : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadModel( 
            /* [in] */ BSTR ModelFileName,
            /* [defaultvalue][in] */ BSTR ModelFilePath = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNumberOfInputs( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNumberOfOutputs( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputAtTimeByIndex( 
            /* [in] */ long Index,
            /* [in] */ double InputValue,
            /* [in] */ BSTR Time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputAtTimeByName( 
            /* [in] */ BSTR Name,
            /* [in] */ double InputValue,
            /* [in] */ BSTR Time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputAtTimeByTag( 
            /* [in] */ BSTR Tag,
            /* [in] */ double InputValue,
            /* [in] */ BSTR Time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputForRowByIndex( 
            /* [in] */ long Index,
            /* [in] */ double InputValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputForRowByName( 
            /* [in] */ BSTR InputName,
            /* [in] */ double InputValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputForRowByTag( 
            /* [in] */ BSTR Tag,
            /* [in] */ double InputValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputsAtTime( 
            /* [in] */ VARIANT Inputs,
            /* [in] */ BSTR Time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setInputsForRow( 
            /* [in] */ VARIANT Inputs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE calculateOutputsAtTime( 
            /* [in] */ BSTR Time,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE calculateOutputsForRow( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setTimeFormat( 
            BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isTimeBasedModel( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_modelComment( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_modelComment( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_modelFilePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_modelFilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_modelFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_modelFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_modelName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_modelName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_inputNames( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_inputTags( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_outputNames( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_outputTags( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_timeFormat( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_timeFormat( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_modelFullPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_modelFullPath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_numberOfInputs( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_numberOfOutputs( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_loadOnRun( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_loadOnRun( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainModel( 
            VARIANT input,
            VARIANT output,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainModelFromFile( 
            BSTR inputFileName,
            BSTR outputFileName,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainModelFromFiles( 
            VARIANT dataFileNames,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getModelRate( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTestRmse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTrainingRmse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTestCorr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTrainingCorr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_inputUnits( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_outputUnits( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setVariableValueAtTimeByName( 
            BSTR Name,
            double val,
            BSTR Time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setVariableValueAtTimeByTag( 
            BSTR Tag,
            double val,
            BSTR Time) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMaxValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMaxValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMinValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMinValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMeanValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMeanValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMedianValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMedianValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSumValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSumValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSTDValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSTDValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVarianceValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVarianceValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getKurtValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getKurtValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSkewValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSkewValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getRangeValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getRangeValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE clearDataBuffer( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INolPredictorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INolPredictor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INolPredictor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INolPredictor __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadModel )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR ModelFileName,
            /* [defaultvalue][in] */ BSTR ModelFilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getNumberOfInputs )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getNumberOfOutputs )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputAtTimeByIndex )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ long Index,
            /* [in] */ double InputValue,
            /* [in] */ BSTR Time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputAtTimeByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ double InputValue,
            /* [in] */ BSTR Time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputAtTimeByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR Tag,
            /* [in] */ double InputValue,
            /* [in] */ BSTR Time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputForRowByIndex )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ long Index,
            /* [in] */ double InputValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputForRowByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR InputName,
            /* [in] */ double InputValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputForRowByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR Tag,
            /* [in] */ double InputValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputsAtTime )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ VARIANT Inputs,
            /* [in] */ BSTR Time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setInputsForRow )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ VARIANT Inputs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *calculateOutputsAtTime )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR Time,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *calculateOutputsForRow )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTimeFormat )( 
            INolPredictor __RPC_FAR * This,
            BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isTimeBasedModel )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_modelComment )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_modelComment )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_modelFilePath )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_modelFilePath )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_modelFileName )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_modelFileName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_modelName )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_modelName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_inputNames )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_inputTags )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_outputNames )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_outputTags )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_timeFormat )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_timeFormat )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_modelFullPath )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_modelFullPath )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_numberOfInputs )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_numberOfOutputs )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_loadOnRun )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_loadOnRun )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainModel )( 
            INolPredictor __RPC_FAR * This,
            VARIANT input,
            VARIANT output,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainModelFromFile )( 
            INolPredictor __RPC_FAR * This,
            BSTR inputFileName,
            BSTR outputFileName,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainModelFromFiles )( 
            INolPredictor __RPC_FAR * This,
            VARIANT dataFileNames,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getModelRate )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTestRmse )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTrainingRmse )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTestCorr )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTrainingCorr )( 
            INolPredictor __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_inputUnits )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_outputUnits )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setVariableValueAtTimeByName )( 
            INolPredictor __RPC_FAR * This,
            BSTR Name,
            double val,
            BSTR Time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setVariableValueAtTimeByTag )( 
            INolPredictor __RPC_FAR * This,
            BSTR Tag,
            double val,
            BSTR Time);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMaxValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMaxValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMinValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMinValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMeanValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMeanValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMedianValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMedianValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSumValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSumValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSTDValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSTDValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getVarianceValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getVarianceValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getKurtValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getKurtValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSkewValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSkewValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRangeValueByName )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRangeValueByTag )( 
            INolPredictor __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clearDataBuffer )( 
            INolPredictor __RPC_FAR * This);
        
        END_INTERFACE
    } INolPredictorVtbl;

    interface INolPredictor
    {
        CONST_VTBL struct INolPredictorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INolPredictor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INolPredictor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INolPredictor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INolPredictor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INolPredictor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INolPredictor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INolPredictor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INolPredictor_loadModel(This,ModelFileName,ModelFilePath)	\
    (This)->lpVtbl -> loadModel(This,ModelFileName,ModelFilePath)

#define INolPredictor_getNumberOfInputs(This,pVal)	\
    (This)->lpVtbl -> getNumberOfInputs(This,pVal)

#define INolPredictor_getNumberOfOutputs(This,pVal)	\
    (This)->lpVtbl -> getNumberOfOutputs(This,pVal)

#define INolPredictor_setInputAtTimeByIndex(This,Index,InputValue,Time)	\
    (This)->lpVtbl -> setInputAtTimeByIndex(This,Index,InputValue,Time)

#define INolPredictor_setInputAtTimeByName(This,Name,InputValue,Time)	\
    (This)->lpVtbl -> setInputAtTimeByName(This,Name,InputValue,Time)

#define INolPredictor_setInputAtTimeByTag(This,Tag,InputValue,Time)	\
    (This)->lpVtbl -> setInputAtTimeByTag(This,Tag,InputValue,Time)

#define INolPredictor_setInputForRowByIndex(This,Index,InputValue)	\
    (This)->lpVtbl -> setInputForRowByIndex(This,Index,InputValue)

#define INolPredictor_setInputForRowByName(This,InputName,InputValue)	\
    (This)->lpVtbl -> setInputForRowByName(This,InputName,InputValue)

#define INolPredictor_setInputForRowByTag(This,Tag,InputValue)	\
    (This)->lpVtbl -> setInputForRowByTag(This,Tag,InputValue)

#define INolPredictor_setInputsAtTime(This,Inputs,Time)	\
    (This)->lpVtbl -> setInputsAtTime(This,Inputs,Time)

#define INolPredictor_setInputsForRow(This,Inputs)	\
    (This)->lpVtbl -> setInputsForRow(This,Inputs)

#define INolPredictor_calculateOutputsAtTime(This,Time,pVal)	\
    (This)->lpVtbl -> calculateOutputsAtTime(This,Time,pVal)

#define INolPredictor_calculateOutputsForRow(This,pVal)	\
    (This)->lpVtbl -> calculateOutputsForRow(This,pVal)

#define INolPredictor_setTimeFormat(This,newVal)	\
    (This)->lpVtbl -> setTimeFormat(This,newVal)

#define INolPredictor_isTimeBasedModel(This,pbool)	\
    (This)->lpVtbl -> isTimeBasedModel(This,pbool)

#define INolPredictor_get_modelComment(This,pVal)	\
    (This)->lpVtbl -> get_modelComment(This,pVal)

#define INolPredictor_put_modelComment(This,newVal)	\
    (This)->lpVtbl -> put_modelComment(This,newVal)

#define INolPredictor_get_modelFilePath(This,pVal)	\
    (This)->lpVtbl -> get_modelFilePath(This,pVal)

#define INolPredictor_put_modelFilePath(This,newVal)	\
    (This)->lpVtbl -> put_modelFilePath(This,newVal)

#define INolPredictor_get_modelFileName(This,pVal)	\
    (This)->lpVtbl -> get_modelFileName(This,pVal)

#define INolPredictor_put_modelFileName(This,newVal)	\
    (This)->lpVtbl -> put_modelFileName(This,newVal)

#define INolPredictor_get_modelName(This,pVal)	\
    (This)->lpVtbl -> get_modelName(This,pVal)

#define INolPredictor_put_modelName(This,newVal)	\
    (This)->lpVtbl -> put_modelName(This,newVal)

#define INolPredictor_get_inputNames(This,index,pVal)	\
    (This)->lpVtbl -> get_inputNames(This,index,pVal)

#define INolPredictor_get_inputTags(This,index,pVal)	\
    (This)->lpVtbl -> get_inputTags(This,index,pVal)

#define INolPredictor_get_outputNames(This,index,pVal)	\
    (This)->lpVtbl -> get_outputNames(This,index,pVal)

#define INolPredictor_get_outputTags(This,index,pVal)	\
    (This)->lpVtbl -> get_outputTags(This,index,pVal)

#define INolPredictor_get_timeFormat(This,pVal)	\
    (This)->lpVtbl -> get_timeFormat(This,pVal)

#define INolPredictor_put_timeFormat(This,newVal)	\
    (This)->lpVtbl -> put_timeFormat(This,newVal)

#define INolPredictor_get_modelFullPath(This,pVal)	\
    (This)->lpVtbl -> get_modelFullPath(This,pVal)

#define INolPredictor_put_modelFullPath(This,newVal)	\
    (This)->lpVtbl -> put_modelFullPath(This,newVal)

#define INolPredictor_get_numberOfInputs(This,pVal)	\
    (This)->lpVtbl -> get_numberOfInputs(This,pVal)

#define INolPredictor_get_numberOfOutputs(This,pVal)	\
    (This)->lpVtbl -> get_numberOfOutputs(This,pVal)

#define INolPredictor_get_loadOnRun(This,pVal)	\
    (This)->lpVtbl -> get_loadOnRun(This,pVal)

#define INolPredictor_put_loadOnRun(This,newVal)	\
    (This)->lpVtbl -> put_loadOnRun(This,newVal)

#define INolPredictor_trainModel(This,input,output,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainModel(This,input,output,timeInMinute,autoStop,newTraining,display)

#define INolPredictor_trainModelFromFile(This,inputFileName,outputFileName,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainModelFromFile(This,inputFileName,outputFileName,timeInMinute,autoStop,newTraining,display)

#define INolPredictor_trainModelFromFiles(This,dataFileNames,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainModelFromFiles(This,dataFileNames,timeInMinute,autoStop,newTraining,display)

#define INolPredictor_getModelRate(This,pVal)	\
    (This)->lpVtbl -> getModelRate(This,pVal)

#define INolPredictor_getTestRmse(This,pVal)	\
    (This)->lpVtbl -> getTestRmse(This,pVal)

#define INolPredictor_getTrainingRmse(This,pVal)	\
    (This)->lpVtbl -> getTrainingRmse(This,pVal)

#define INolPredictor_getTestCorr(This,pVal)	\
    (This)->lpVtbl -> getTestCorr(This,pVal)

#define INolPredictor_getTrainingCorr(This,pVal)	\
    (This)->lpVtbl -> getTrainingCorr(This,pVal)

#define INolPredictor_get_inputUnits(This,index,pVal)	\
    (This)->lpVtbl -> get_inputUnits(This,index,pVal)

#define INolPredictor_get_outputUnits(This,index,pVal)	\
    (This)->lpVtbl -> get_outputUnits(This,index,pVal)

#define INolPredictor_setVariableValueAtTimeByName(This,Name,val,Time)	\
    (This)->lpVtbl -> setVariableValueAtTimeByName(This,Name,val,Time)

#define INolPredictor_setVariableValueAtTimeByTag(This,Tag,val,Time)	\
    (This)->lpVtbl -> setVariableValueAtTimeByTag(This,Tag,val,Time)

#define INolPredictor_getMaxValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMaxValueByName(This,name,pVal)

#define INolPredictor_getMaxValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMaxValueByTag(This,tag,pVal)

#define INolPredictor_getMinValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMinValueByName(This,name,pVal)

#define INolPredictor_getMinValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMinValueByTag(This,tag,pVal)

#define INolPredictor_getMeanValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMeanValueByName(This,name,pVal)

#define INolPredictor_getMeanValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMeanValueByTag(This,tag,pVal)

#define INolPredictor_getMedianValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMedianValueByName(This,name,pVal)

#define INolPredictor_getMedianValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMedianValueByTag(This,tag,pVal)

#define INolPredictor_getSumValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getSumValueByName(This,name,pVal)

#define INolPredictor_getSumValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getSumValueByTag(This,tag,pVal)

#define INolPredictor_getSTDValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getSTDValueByName(This,name,pVal)

#define INolPredictor_getSTDValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getSTDValueByTag(This,tag,pVal)

#define INolPredictor_getVarianceValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getVarianceValueByName(This,name,pVal)

#define INolPredictor_getVarianceValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getVarianceValueByTag(This,tag,pVal)

#define INolPredictor_getKurtValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getKurtValueByName(This,name,pVal)

#define INolPredictor_getKurtValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getKurtValueByTag(This,tag,pVal)

#define INolPredictor_getSkewValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getSkewValueByName(This,name,pVal)

#define INolPredictor_getSkewValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getSkewValueByTag(This,tag,pVal)

#define INolPredictor_getRangeValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getRangeValueByName(This,name,pVal)

#define INolPredictor_getRangeValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getRangeValueByTag(This,tag,pVal)

#define INolPredictor_clearDataBuffer(This)	\
    (This)->lpVtbl -> clearDataBuffer(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_loadModel_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR ModelFileName,
    /* [defaultvalue][in] */ BSTR ModelFilePath);


void __RPC_STUB INolPredictor_loadModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getNumberOfInputs_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getNumberOfInputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getNumberOfOutputs_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getNumberOfOutputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputAtTimeByIndex_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ long Index,
    /* [in] */ double InputValue,
    /* [in] */ BSTR Time);


void __RPC_STUB INolPredictor_setInputAtTimeByIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputAtTimeByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ double InputValue,
    /* [in] */ BSTR Time);


void __RPC_STUB INolPredictor_setInputAtTimeByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputAtTimeByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR Tag,
    /* [in] */ double InputValue,
    /* [in] */ BSTR Time);


void __RPC_STUB INolPredictor_setInputAtTimeByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputForRowByIndex_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ long Index,
    /* [in] */ double InputValue);


void __RPC_STUB INolPredictor_setInputForRowByIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputForRowByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR InputName,
    /* [in] */ double InputValue);


void __RPC_STUB INolPredictor_setInputForRowByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputForRowByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR Tag,
    /* [in] */ double InputValue);


void __RPC_STUB INolPredictor_setInputForRowByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputsAtTime_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ VARIANT Inputs,
    /* [in] */ BSTR Time);


void __RPC_STUB INolPredictor_setInputsAtTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setInputsForRow_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ VARIANT Inputs);


void __RPC_STUB INolPredictor_setInputsForRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_calculateOutputsAtTime_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR Time,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_calculateOutputsAtTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_calculateOutputsForRow_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_calculateOutputsForRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setTimeFormat_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR newVal);


void __RPC_STUB INolPredictor_setTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_isTimeBasedModel_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);


void __RPC_STUB INolPredictor_isTimeBasedModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_modelComment_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_modelComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_modelComment_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolPredictor_put_modelComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_modelFilePath_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_modelFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_modelFilePath_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolPredictor_put_modelFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_modelFileName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_modelFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_modelFileName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolPredictor_put_modelFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_modelName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_modelName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_modelName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolPredictor_put_modelName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_inputNames_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_inputNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_inputTags_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_inputTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_outputNames_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_outputNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_outputTags_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_outputTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_timeFormat_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_timeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_timeFormat_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolPredictor_put_timeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_modelFullPath_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_modelFullPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_modelFullPath_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolPredictor_put_modelFullPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_numberOfInputs_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_numberOfInputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_numberOfOutputs_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_numberOfOutputs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_loadOnRun_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_loadOnRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolPredictor_put_loadOnRun_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB INolPredictor_put_loadOnRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_trainModel_Proxy( 
    INolPredictor __RPC_FAR * This,
    VARIANT input,
    VARIANT output,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolPredictor_trainModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_trainModelFromFile_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR inputFileName,
    BSTR outputFileName,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolPredictor_trainModelFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_trainModelFromFiles_Proxy( 
    INolPredictor __RPC_FAR * This,
    VARIANT dataFileNames,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolPredictor_trainModelFromFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getModelRate_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getModelRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTestRmse_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getTestRmse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTrainingRmse_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getTrainingRmse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTestCorr_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getTestCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getTrainingCorr_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getTrainingCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_inputUnits_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_inputUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolPredictor_get_outputUnits_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_get_outputUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setVariableValueAtTimeByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR Name,
    double val,
    BSTR Time);


void __RPC_STUB INolPredictor_setVariableValueAtTimeByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_setVariableValueAtTimeByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    BSTR Tag,
    double val,
    BSTR Time);


void __RPC_STUB INolPredictor_setVariableValueAtTimeByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMaxValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMaxValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMaxValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMaxValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMinValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMinValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMinValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMinValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMeanValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMeanValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMeanValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMeanValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMedianValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMedianValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getMedianValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getMedianValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSumValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getSumValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSumValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getSumValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSTDValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getSTDValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSTDValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getSTDValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getVarianceValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getVarianceValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getVarianceValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getVarianceValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getKurtValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getKurtValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getKurtValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getKurtValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSkewValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getSkewValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getSkewValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getSkewValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getRangeValueByName_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getRangeValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_getRangeValueByTag_Proxy( 
    INolPredictor __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolPredictor_getRangeValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolPredictor_clearDataBuffer_Proxy( 
    INolPredictor __RPC_FAR * This);


void __RPC_STUB INolPredictor_clearDataBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INolPredictor_INTERFACE_DEFINED__ */



#ifndef __NOLONLINELib_LIBRARY_DEFINED__
#define __NOLONLINELib_LIBRARY_DEFINED__

/* library NOLONLINELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_NOLONLINELib;

#ifndef ___INolPredictorEvents_DISPINTERFACE_DEFINED__
#define ___INolPredictorEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INolPredictorEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INolPredictorEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDE0EF60-4E9A-11D4-B8A0-0000861E0389")
    _INolPredictorEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INolPredictorEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _INolPredictorEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _INolPredictorEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _INolPredictorEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _INolPredictorEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _INolPredictorEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _INolPredictorEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _INolPredictorEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _INolPredictorEventsVtbl;

    interface _INolPredictorEvents
    {
        CONST_VTBL struct _INolPredictorEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INolPredictorEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _INolPredictorEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _INolPredictorEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _INolPredictorEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _INolPredictorEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _INolPredictorEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _INolPredictorEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INolPredictorEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NolPredictor;

#ifdef __cplusplus

class DECLSPEC_UUID("5B0BEE9F-4DD6-11D4-B8A0-0000861E0389")
NolPredictor;
#endif

#ifndef ___INolPredictorPropEvents_DISPINTERFACE_DEFINED__
#define ___INolPredictorPropEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INolPredictorPropEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INolPredictorPropEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BF5BD744-4EA2-11D4-8704-00609703E392")
    _INolPredictorPropEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INolPredictorPropEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _INolPredictorPropEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _INolPredictorPropEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _INolPredictorPropEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _INolPredictorPropEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _INolPredictorPropEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _INolPredictorPropEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _INolPredictorPropEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _INolPredictorPropEventsVtbl;

    interface _INolPredictorPropEvents
    {
        CONST_VTBL struct _INolPredictorPropEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INolPredictorPropEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _INolPredictorPropEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _INolPredictorPropEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _INolPredictorPropEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _INolPredictorPropEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _INolPredictorPropEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _INolPredictorPropEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INolPredictorPropEvents_DISPINTERFACE_DEFINED__ */


#ifndef __INolOptimizer_INTERFACE_DEFINED__
#define __INolOptimizer_INTERFACE_DEFINED__

/* interface INolOptimizer */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INolOptimizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49079011-4EB0-11D4-8704-00609703E392")
    INolOptimizer : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR strCaption) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrCaption) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_Valid( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Valid( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_optimizationName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_optimizationName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_optimizationComment( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_optimizationComment( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_optimizationFullPath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_optimizationFullPath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_outputNames( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadOptimization( 
            /* [in] */ BSTR file,
            /* [defaultvalue][in] */ BSTR directory = L"") = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_optimizationFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_optimizationFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_optimizationFilePath( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_optimizationFilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_manipulatedNames( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_exogenousNames( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stateNames( 
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE calculate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getBoundsByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *bounds) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_outputTags( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_manipulatedTags( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_exogenousTags( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stateTags( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setBoundsByName( 
            /* [in] */ BSTR name,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getBoundsByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ VARIANT __RPC_FAR *bounds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setBoundsByTag( 
            /* [in] */ BSTR name,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValueByName( 
            /* [in] */ BSTR name,
            double value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValueByTag( 
            /* [in] */ BSTR tag,
            /* [in] */ double value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getValues( 
            /* [in] */ short type,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setValues( 
            /* [in] */ short index,
            /* [in] */ VARIANT values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getWeightsByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setWeightsByName( 
            /* [in] */ BSTR name,
            /* [in] */ VARIANT values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getWeightsByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setWeightsByTag( 
            /* [in] */ BSTR tag,
            /* [in] */ VARIANT values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNumberOfVariables( 
            /* [in] */ short type,
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_loadOnRun( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_loadOnRun( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE calculateOptimization( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainOutputModel( 
            VARIANT input,
            VARIANT output,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainStateModel( 
            VARIANT input,
            VARIANT output,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainOutputModelFromFile( 
            BSTR inputFileName,
            BSTR outputFileName,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainStateModelFromFile( 
            BSTR inputFileName,
            BSTR outputFileName,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE trainModelFromFiles( 
            VARIANT dataFileNames,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOutputModelRate( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOutputTestRmse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOutputTrainingRmse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOutputTestCorr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getOutputTrainingCorr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStateModelRate( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStateTestRmse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStateTrainingRmse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStateTestCorr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getStateTrainingCorr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_outputUnits( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_manipulatedUnits( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_exogenousUnits( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_stateUnits( 
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMaxValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMaxValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMinValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMinValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMeanValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMeanValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMedianValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getMedianValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSumValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSumValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSTDValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSTDValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVarianceValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVarianceValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getKurtValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getKurtValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSkewValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSkewValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getRangeValueByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getRangeValueByTag( 
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getNumberOfVariablesReachHardbound( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INolOptimizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INolOptimizer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INolOptimizer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INolOptimizer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR strCaption);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCaption);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Valid )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Valid )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_optimizationName )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_optimizationName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_optimizationComment )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_optimizationComment )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_optimizationFullPath )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_optimizationFullPath )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_outputNames )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadOptimization )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR file,
            /* [defaultvalue][in] */ BSTR directory);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_optimizationFileName )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_optimizationFileName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_optimizationFilePath )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_optimizationFilePath )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_manipulatedNames )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_exogenousNames )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stateNames )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *calculate )( 
            INolOptimizer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getBoundsByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *bounds);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_outputTags )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_manipulatedTags )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_exogenousTags )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stateTags )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setBoundsByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getBoundsByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ VARIANT __RPC_FAR *bounds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setBoundsByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            double value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [in] */ double value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getValues )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ short type,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setValues )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ short index,
            /* [in] */ VARIANT values);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getWeightsByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setWeightsByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [in] */ VARIANT values);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getWeightsByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setWeightsByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [in] */ VARIANT values);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getNumberOfVariables )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ short type,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_loadOnRun )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_loadOnRun )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *calculateOptimization )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainOutputModel )( 
            INolOptimizer __RPC_FAR * This,
            VARIANT input,
            VARIANT output,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainStateModel )( 
            INolOptimizer __RPC_FAR * This,
            VARIANT input,
            VARIANT output,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainOutputModelFromFile )( 
            INolOptimizer __RPC_FAR * This,
            BSTR inputFileName,
            BSTR outputFileName,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainStateModelFromFile )( 
            INolOptimizer __RPC_FAR * This,
            BSTR inputFileName,
            BSTR outputFileName,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *trainModelFromFiles )( 
            INolOptimizer __RPC_FAR * This,
            VARIANT dataFileNames,
            double timeInMinute,
            VARIANT_BOOL autoStop,
            VARIANT_BOOL newTraining,
            VARIANT_BOOL display);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getOutputModelRate )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getOutputTestRmse )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getOutputTrainingRmse )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getOutputTestCorr )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getOutputTrainingCorr )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getStateModelRate )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getStateTestRmse )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getStateTrainingRmse )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getStateTestCorr )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getStateTrainingCorr )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_outputUnits )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_manipulatedUnits )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_exogenousUnits )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_stateUnits )( 
            INolOptimizer __RPC_FAR * This,
            short index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMaxValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMaxValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMinValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMinValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMeanValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMeanValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMedianValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getMedianValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSumValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSumValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSTDValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSTDValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getVarianceValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getVarianceValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getKurtValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getKurtValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSkewValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getSkewValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRangeValueByName )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRangeValueByTag )( 
            INolOptimizer __RPC_FAR * This,
            /* [in] */ BSTR tag,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getNumberOfVariablesReachHardbound )( 
            INolOptimizer __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        END_INTERFACE
    } INolOptimizerVtbl;

    interface INolOptimizer
    {
        CONST_VTBL struct INolOptimizerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INolOptimizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INolOptimizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INolOptimizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INolOptimizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INolOptimizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INolOptimizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INolOptimizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INolOptimizer_put_Caption(This,strCaption)	\
    (This)->lpVtbl -> put_Caption(This,strCaption)

#define INolOptimizer_get_Caption(This,pstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pstrCaption)

#define INolOptimizer_put_Valid(This,vbool)	\
    (This)->lpVtbl -> put_Valid(This,vbool)

#define INolOptimizer_get_Valid(This,pbool)	\
    (This)->lpVtbl -> get_Valid(This,pbool)

#define INolOptimizer_get_optimizationName(This,pVal)	\
    (This)->lpVtbl -> get_optimizationName(This,pVal)

#define INolOptimizer_put_optimizationName(This,newVal)	\
    (This)->lpVtbl -> put_optimizationName(This,newVal)

#define INolOptimizer_get_optimizationComment(This,pVal)	\
    (This)->lpVtbl -> get_optimizationComment(This,pVal)

#define INolOptimizer_put_optimizationComment(This,newVal)	\
    (This)->lpVtbl -> put_optimizationComment(This,newVal)

#define INolOptimizer_get_optimizationFullPath(This,pVal)	\
    (This)->lpVtbl -> get_optimizationFullPath(This,pVal)

#define INolOptimizer_put_optimizationFullPath(This,newVal)	\
    (This)->lpVtbl -> put_optimizationFullPath(This,newVal)

#define INolOptimizer_get_outputNames(This,index,pVal)	\
    (This)->lpVtbl -> get_outputNames(This,index,pVal)

#define INolOptimizer_loadOptimization(This,file,directory)	\
    (This)->lpVtbl -> loadOptimization(This,file,directory)

#define INolOptimizer_get_optimizationFileName(This,pVal)	\
    (This)->lpVtbl -> get_optimizationFileName(This,pVal)

#define INolOptimizer_put_optimizationFileName(This,newVal)	\
    (This)->lpVtbl -> put_optimizationFileName(This,newVal)

#define INolOptimizer_get_optimizationFilePath(This,pVal)	\
    (This)->lpVtbl -> get_optimizationFilePath(This,pVal)

#define INolOptimizer_put_optimizationFilePath(This,newVal)	\
    (This)->lpVtbl -> put_optimizationFilePath(This,newVal)

#define INolOptimizer_get_manipulatedNames(This,index,pVal)	\
    (This)->lpVtbl -> get_manipulatedNames(This,index,pVal)

#define INolOptimizer_get_exogenousNames(This,index,pVal)	\
    (This)->lpVtbl -> get_exogenousNames(This,index,pVal)

#define INolOptimizer_get_stateNames(This,index,pVal)	\
    (This)->lpVtbl -> get_stateNames(This,index,pVal)

#define INolOptimizer_calculate(This)	\
    (This)->lpVtbl -> calculate(This)

#define INolOptimizer_getBoundsByName(This,name,bounds)	\
    (This)->lpVtbl -> getBoundsByName(This,name,bounds)

#define INolOptimizer_get_outputTags(This,index,pVal)	\
    (This)->lpVtbl -> get_outputTags(This,index,pVal)

#define INolOptimizer_get_manipulatedTags(This,index,pVal)	\
    (This)->lpVtbl -> get_manipulatedTags(This,index,pVal)

#define INolOptimizer_get_exogenousTags(This,index,pVal)	\
    (This)->lpVtbl -> get_exogenousTags(This,index,pVal)

#define INolOptimizer_get_stateTags(This,index,pVal)	\
    (This)->lpVtbl -> get_stateTags(This,index,pVal)

#define INolOptimizer_setBoundsByName(This,name,value)	\
    (This)->lpVtbl -> setBoundsByName(This,name,value)

#define INolOptimizer_getBoundsByTag(This,tag,bounds)	\
    (This)->lpVtbl -> getBoundsByTag(This,tag,bounds)

#define INolOptimizer_setBoundsByTag(This,name,value)	\
    (This)->lpVtbl -> setBoundsByTag(This,name,value)

#define INolOptimizer_getValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getValueByName(This,name,pVal)

#define INolOptimizer_setValueByName(This,name,value)	\
    (This)->lpVtbl -> setValueByName(This,name,value)

#define INolOptimizer_getValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getValueByTag(This,tag,pVal)

#define INolOptimizer_setValueByTag(This,tag,value)	\
    (This)->lpVtbl -> setValueByTag(This,tag,value)

#define INolOptimizer_getValues(This,type,pVal)	\
    (This)->lpVtbl -> getValues(This,type,pVal)

#define INolOptimizer_setValues(This,index,values)	\
    (This)->lpVtbl -> setValues(This,index,values)

#define INolOptimizer_getWeightsByName(This,name,pVal)	\
    (This)->lpVtbl -> getWeightsByName(This,name,pVal)

#define INolOptimizer_setWeightsByName(This,name,values)	\
    (This)->lpVtbl -> setWeightsByName(This,name,values)

#define INolOptimizer_getWeightsByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getWeightsByTag(This,tag,pVal)

#define INolOptimizer_setWeightsByTag(This,tag,values)	\
    (This)->lpVtbl -> setWeightsByTag(This,tag,values)

#define INolOptimizer_getNumberOfVariables(This,type,pVal)	\
    (This)->lpVtbl -> getNumberOfVariables(This,type,pVal)

#define INolOptimizer_get_loadOnRun(This,pVal)	\
    (This)->lpVtbl -> get_loadOnRun(This,pVal)

#define INolOptimizer_put_loadOnRun(This,newVal)	\
    (This)->lpVtbl -> put_loadOnRun(This,newVal)

#define INolOptimizer_calculateOptimization(This,pVal)	\
    (This)->lpVtbl -> calculateOptimization(This,pVal)

#define INolOptimizer_trainOutputModel(This,input,output,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainOutputModel(This,input,output,timeInMinute,autoStop,newTraining,display)

#define INolOptimizer_trainStateModel(This,input,output,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainStateModel(This,input,output,timeInMinute,autoStop,newTraining,display)

#define INolOptimizer_trainOutputModelFromFile(This,inputFileName,outputFileName,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainOutputModelFromFile(This,inputFileName,outputFileName,timeInMinute,autoStop,newTraining,display)

#define INolOptimizer_trainStateModelFromFile(This,inputFileName,outputFileName,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainStateModelFromFile(This,inputFileName,outputFileName,timeInMinute,autoStop,newTraining,display)

#define INolOptimizer_trainModelFromFiles(This,dataFileNames,timeInMinute,autoStop,newTraining,display)	\
    (This)->lpVtbl -> trainModelFromFiles(This,dataFileNames,timeInMinute,autoStop,newTraining,display)

#define INolOptimizer_getOutputModelRate(This,pVal)	\
    (This)->lpVtbl -> getOutputModelRate(This,pVal)

#define INolOptimizer_getOutputTestRmse(This,pVal)	\
    (This)->lpVtbl -> getOutputTestRmse(This,pVal)

#define INolOptimizer_getOutputTrainingRmse(This,pVal)	\
    (This)->lpVtbl -> getOutputTrainingRmse(This,pVal)

#define INolOptimizer_getOutputTestCorr(This,pVal)	\
    (This)->lpVtbl -> getOutputTestCorr(This,pVal)

#define INolOptimizer_getOutputTrainingCorr(This,pVal)	\
    (This)->lpVtbl -> getOutputTrainingCorr(This,pVal)

#define INolOptimizer_getStateModelRate(This,pVal)	\
    (This)->lpVtbl -> getStateModelRate(This,pVal)

#define INolOptimizer_getStateTestRmse(This,pVal)	\
    (This)->lpVtbl -> getStateTestRmse(This,pVal)

#define INolOptimizer_getStateTrainingRmse(This,pVal)	\
    (This)->lpVtbl -> getStateTrainingRmse(This,pVal)

#define INolOptimizer_getStateTestCorr(This,pVal)	\
    (This)->lpVtbl -> getStateTestCorr(This,pVal)

#define INolOptimizer_getStateTrainingCorr(This,pVal)	\
    (This)->lpVtbl -> getStateTrainingCorr(This,pVal)

#define INolOptimizer_get_outputUnits(This,index,pVal)	\
    (This)->lpVtbl -> get_outputUnits(This,index,pVal)

#define INolOptimizer_get_manipulatedUnits(This,index,pVal)	\
    (This)->lpVtbl -> get_manipulatedUnits(This,index,pVal)

#define INolOptimizer_get_exogenousUnits(This,index,pVal)	\
    (This)->lpVtbl -> get_exogenousUnits(This,index,pVal)

#define INolOptimizer_get_stateUnits(This,index,pVal)	\
    (This)->lpVtbl -> get_stateUnits(This,index,pVal)

#define INolOptimizer_getMaxValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMaxValueByName(This,name,pVal)

#define INolOptimizer_getMaxValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMaxValueByTag(This,tag,pVal)

#define INolOptimizer_getMinValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMinValueByName(This,name,pVal)

#define INolOptimizer_getMinValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMinValueByTag(This,tag,pVal)

#define INolOptimizer_getMeanValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMeanValueByName(This,name,pVal)

#define INolOptimizer_getMeanValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMeanValueByTag(This,tag,pVal)

#define INolOptimizer_getMedianValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getMedianValueByName(This,name,pVal)

#define INolOptimizer_getMedianValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getMedianValueByTag(This,tag,pVal)

#define INolOptimizer_getSumValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getSumValueByName(This,name,pVal)

#define INolOptimizer_getSumValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getSumValueByTag(This,tag,pVal)

#define INolOptimizer_getSTDValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getSTDValueByName(This,name,pVal)

#define INolOptimizer_getSTDValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getSTDValueByTag(This,tag,pVal)

#define INolOptimizer_getVarianceValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getVarianceValueByName(This,name,pVal)

#define INolOptimizer_getVarianceValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getVarianceValueByTag(This,tag,pVal)

#define INolOptimizer_getKurtValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getKurtValueByName(This,name,pVal)

#define INolOptimizer_getKurtValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getKurtValueByTag(This,tag,pVal)

#define INolOptimizer_getSkewValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getSkewValueByName(This,name,pVal)

#define INolOptimizer_getSkewValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getSkewValueByTag(This,tag,pVal)

#define INolOptimizer_getRangeValueByName(This,name,pVal)	\
    (This)->lpVtbl -> getRangeValueByName(This,name,pVal)

#define INolOptimizer_getRangeValueByTag(This,tag,pVal)	\
    (This)->lpVtbl -> getRangeValueByTag(This,tag,pVal)

#define INolOptimizer_getNumberOfVariablesReachHardbound(This,pVal)	\
    (This)->lpVtbl -> getNumberOfVariablesReachHardbound(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_Caption_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR strCaption);


void __RPC_STUB INolOptimizer_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_Caption_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrCaption);


void __RPC_STUB INolOptimizer_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_Valid_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB INolOptimizer_put_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_Valid_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbool);


void __RPC_STUB INolOptimizer_get_Valid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_optimizationName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_optimizationName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_optimizationName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolOptimizer_put_optimizationName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_optimizationComment_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_optimizationComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_optimizationComment_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolOptimizer_put_optimizationComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_optimizationFullPath_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_optimizationFullPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_optimizationFullPath_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolOptimizer_put_optimizationFullPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_outputNames_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_outputNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_loadOptimization_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR file,
    /* [defaultvalue][in] */ BSTR directory);


void __RPC_STUB INolOptimizer_loadOptimization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_optimizationFileName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_optimizationFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_optimizationFileName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolOptimizer_put_optimizationFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_optimizationFilePath_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_optimizationFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_optimizationFilePath_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB INolOptimizer_put_optimizationFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_manipulatedNames_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_manipulatedNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_exogenousNames_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_exogenousNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_stateNames_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_stateNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_calculate_Proxy( 
    INolOptimizer __RPC_FAR * This);


void __RPC_STUB INolOptimizer_calculate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getBoundsByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT __RPC_FAR *bounds);


void __RPC_STUB INolOptimizer_getBoundsByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_outputTags_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_outputTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_manipulatedTags_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_manipulatedTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_exogenousTags_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_exogenousTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_stateTags_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_stateTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setBoundsByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ VARIANT value);


void __RPC_STUB INolOptimizer_setBoundsByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getBoundsByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ VARIANT __RPC_FAR *bounds);


void __RPC_STUB INolOptimizer_getBoundsByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setBoundsByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ VARIANT value);


void __RPC_STUB INolOptimizer_setBoundsByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    double value);


void __RPC_STUB INolOptimizer_setValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [in] */ double value);


void __RPC_STUB INolOptimizer_setValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getValues_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ short type,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setValues_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ short index,
    /* [in] */ VARIANT values);


void __RPC_STUB INolOptimizer_setValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getWeightsByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getWeightsByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setWeightsByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [in] */ VARIANT values);


void __RPC_STUB INolOptimizer_setWeightsByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getWeightsByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getWeightsByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_setWeightsByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [in] */ VARIANT values);


void __RPC_STUB INolOptimizer_setWeightsByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getNumberOfVariables_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ short type,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getNumberOfVariables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_loadOnRun_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_loadOnRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INolOptimizer_put_loadOnRun_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB INolOptimizer_put_loadOnRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_calculateOptimization_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_calculateOptimization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_trainOutputModel_Proxy( 
    INolOptimizer __RPC_FAR * This,
    VARIANT input,
    VARIANT output,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolOptimizer_trainOutputModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_trainStateModel_Proxy( 
    INolOptimizer __RPC_FAR * This,
    VARIANT input,
    VARIANT output,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolOptimizer_trainStateModel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_trainOutputModelFromFile_Proxy( 
    INolOptimizer __RPC_FAR * This,
    BSTR inputFileName,
    BSTR outputFileName,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolOptimizer_trainOutputModelFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_trainStateModelFromFile_Proxy( 
    INolOptimizer __RPC_FAR * This,
    BSTR inputFileName,
    BSTR outputFileName,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolOptimizer_trainStateModelFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_trainModelFromFiles_Proxy( 
    INolOptimizer __RPC_FAR * This,
    VARIANT dataFileNames,
    double timeInMinute,
    VARIANT_BOOL autoStop,
    VARIANT_BOOL newTraining,
    VARIANT_BOOL display);


void __RPC_STUB INolOptimizer_trainModelFromFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getOutputModelRate_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getOutputModelRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getOutputTestRmse_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getOutputTestRmse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getOutputTrainingRmse_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getOutputTrainingRmse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getOutputTestCorr_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getOutputTestCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getOutputTrainingCorr_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getOutputTrainingCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getStateModelRate_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getStateModelRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getStateTestRmse_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getStateTestRmse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getStateTrainingRmse_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getStateTrainingRmse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getStateTestCorr_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getStateTestCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getStateTrainingCorr_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getStateTrainingCorr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_outputUnits_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_outputUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_manipulatedUnits_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_manipulatedUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_exogenousUnits_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_exogenousUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INolOptimizer_get_stateUnits_Proxy( 
    INolOptimizer __RPC_FAR * This,
    short index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_get_stateUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMaxValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMaxValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMaxValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMaxValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMinValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMinValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMinValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMinValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMeanValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMeanValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMeanValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMeanValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMedianValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMedianValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getMedianValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getMedianValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getSumValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getSumValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getSumValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getSumValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getSTDValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getSTDValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getSTDValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getSTDValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getVarianceValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getVarianceValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getVarianceValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getVarianceValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getKurtValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getKurtValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getKurtValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getKurtValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getSkewValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getSkewValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getSkewValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getSkewValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getRangeValueByName_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR name,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getRangeValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getRangeValueByTag_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [in] */ BSTR tag,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getRangeValueByTag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INolOptimizer_getNumberOfVariablesReachHardbound_Proxy( 
    INolOptimizer __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB INolOptimizer_getNumberOfVariablesReachHardbound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INolOptimizer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NolPredictorProp;

#ifdef __cplusplus

class DECLSPEC_UUID("BF5BD743-4EA2-11D4-8704-00609703E392")
NolPredictorProp;
#endif

#ifndef ___INolOptimizerEvents_DISPINTERFACE_DEFINED__
#define ___INolOptimizerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INolOptimizerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INolOptimizerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("49079013-4EB0-11D4-8704-00609703E392")
    _INolOptimizerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INolOptimizerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _INolOptimizerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _INolOptimizerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _INolOptimizerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _INolOptimizerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _INolOptimizerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _INolOptimizerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _INolOptimizerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _INolOptimizerEventsVtbl;

    interface _INolOptimizerEvents
    {
        CONST_VTBL struct _INolOptimizerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INolOptimizerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _INolOptimizerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _INolOptimizerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _INolOptimizerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _INolOptimizerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _INolOptimizerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _INolOptimizerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INolOptimizerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NolOptimizer;

#ifdef __cplusplus

class DECLSPEC_UUID("49079012-4EB0-11D4-8704-00609703E392")
NolOptimizer;
#endif

#ifndef ___INolOptimizerPropEvents_DISPINTERFACE_DEFINED__
#define ___INolOptimizerPropEvents_DISPINTERFACE_DEFINED__

/* dispinterface _INolOptimizerPropEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__INolOptimizerPropEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("49079015-4EB0-11D4-8704-00609703E392")
    _INolOptimizerPropEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _INolOptimizerPropEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _INolOptimizerPropEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _INolOptimizerPropEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _INolOptimizerPropEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _INolOptimizerPropEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _INolOptimizerPropEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _INolOptimizerPropEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _INolOptimizerPropEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _INolOptimizerPropEventsVtbl;

    interface _INolOptimizerPropEvents
    {
        CONST_VTBL struct _INolOptimizerPropEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _INolOptimizerPropEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _INolOptimizerPropEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _INolOptimizerPropEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _INolOptimizerPropEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _INolOptimizerPropEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _INolOptimizerPropEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _INolOptimizerPropEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___INolOptimizerPropEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_NolOptimizerProp;

#ifdef __cplusplus

class DECLSPEC_UUID("49079014-4EB0-11D4-8704-00609703E392")
NolOptimizerProp;
#endif
#endif /* __NOLONLINELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
