// NolOptimizer.h : Declaration of the CNolOptimizer

#ifndef __NOLOPTIMIZER_H_
#define __NOLOPTIMIZER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "jni.h"
#include "jvm.h"


/////////////////////////////////////////////////////////////////////////////
// CNolOptimizer
class ATL_NO_VTABLE CNolOptimizer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CNolOptimizer, INolOptimizer, &IID_INolOptimizer, &LIBID_NOLONLINELib>,
	public CComControl<CNolOptimizer>,
	public IPersistStreamInitImpl<CNolOptimizer>,
	public IOleControlImpl<CNolOptimizer>,
	public IOleObjectImpl<CNolOptimizer>,
	public IOleInPlaceActiveObjectImpl<CNolOptimizer>,
	public IViewObjectExImpl<CNolOptimizer>,
	public IOleInPlaceObjectWindowlessImpl<CNolOptimizer>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CNolOptimizer>,
	public IPersistStorageImpl<CNolOptimizer>,
	public ISpecifyPropertyPagesImpl<CNolOptimizer>,
	public IQuickActivateImpl<CNolOptimizer>,
	public IDataObjectImpl<CNolOptimizer>,
	public IProvideClassInfo2Impl<&CLSID_NolOptimizer, &DIID__INolOptimizerEvents, &LIBID_NOLONLINELib>,
	public IPropertyNotifySinkCP<CNolOptimizer>,
	public CComCoClass<CNolOptimizer, &CLSID_NolOptimizer>
{
public:
	CNolOptimizer()
	{
  		m_bstrCaption = _T("File location");
		m_bValid = FALSE;

		m_optimizationName = '\0';
		m_optimizationComment = '\0'; //(BSTR)_T("comment1");
		m_optimizationFullPath = '\0';
		m_optimizationFileName = '\0';
		m_optimizationFilePath = '\0';
		m_isLoaded = FALSE;
		m_loadOnRun = -1;
		m_numberOfBounds = 5;
		m_numberOfWeights = 4;

		jmethodID mid;
		JNIEnv *env;
		env = getJavaEnvironment();
		if(env == NULL) {
			::MessageBox(NULL, "Environment is null", "Fatal Error", MB_OK);				
		}

		cls = env->FindClass("com/gensym/nols/deploy/OnlineOptimizer");
		if (cls == 0) {
			::MessageBox(NULL, "Can't find OnlineOptimizer class", "loading", MB_OK);	
			return;
		}

		mid = env->GetMethodID(cls,"<init>","()V");
		if (mid == 0) {
			::MessageBox(NULL, "Can't find OnlineOptimizer init method", "loading", MB_OK);	
			return;
		}
		m_optimizer = env->NewGlobalRef(env->NewObject(cls,mid));

	}

	~CNolOptimizer()
	{
		m_optimizationName = '\0';
		m_optimizationComment = '\0'; //(BSTR)_T("comment1");
		m_optimizationFullPath = '\0';
		m_optimizationFileName = '\0';
		m_optimizationFilePath = '\0';
		m_loadOnRun = -1;
		m_numberOfBounds = 5;
		m_numberOfWeights = 4;
		cls = 0;

		JNIEnv *env;
		env = getJavaEnvironment();

		env->DeleteGlobalRef(m_optimizer);
		m_optimizer = NULL;

		if(m_isLoaded){
			env->DeleteGlobalRef(m_outputNames);
			m_outputNames = NULL;
			env->DeleteGlobalRef(m_manipulatedNames);
			m_manipulatedNames = NULL;
			env->DeleteGlobalRef(m_stateNames);
			m_stateNames = NULL;
			env->DeleteGlobalRef(m_exogenousNames);
			m_exogenousNames = NULL;
			env->DeleteGlobalRef(m_outputTags);
			m_outputTags = NULL;
			env->DeleteGlobalRef(m_manipulatedTags);
			m_manipulatedTags = NULL;
			env->DeleteGlobalRef(m_stateTags);
			m_stateTags = NULL;
			env->DeleteGlobalRef(m_exogenousTags);
			m_exogenousTags = NULL;

			env->DeleteGlobalRef(m_outputUnits);
			m_outputUnits = NULL;
			env->DeleteGlobalRef(m_manipulatedUnits);
			m_manipulatedUnits = NULL;
			env->DeleteGlobalRef(m_stateUnits);
			m_stateUnits = NULL;
			env->DeleteGlobalRef(m_exogenousUnits);
			m_exogenousUnits = NULL;

		}
		m_isLoaded = FALSE;
		ATLTRACE(_T("I'm out of here\n"));
	}


DECLARE_REGISTRY_RESOURCEID(IDR_NOLOPTIMIZER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNolOptimizer)
	COM_INTERFACE_ENTRY(INolOptimizer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CNolOptimizer)
	PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NolOptimizerProp)
	PROP_ENTRY("Valid", DISPID_VALID, CLSID_NULL)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CNolOptimizer)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CNolOptimizer)
	CHAIN_MSG_MAP(CComControl<CNolOptimizer>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_INolOptimizer,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::ATL::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

public:
	STDMETHOD(getNumberOfVariablesReachHardbound)(short *pVal);
	STDMETHOD(getRangeValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getRangeValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getSkewValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getSkewValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getKurtValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getKurtValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getVarianceValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getVarianceValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getSTDValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getSTDValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getSumValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getSumValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMedianValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMedianValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMeanValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMeanValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMinValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMinValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMaxValueByTag)(/*[in]*/ BSTR tag, /*[out,retval]*/ double *pVal);
	STDMETHOD(getMaxValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(getStateTrainingCorr)(VARIANT *pVal);
	STDMETHOD(getStateTestCorr)(VARIANT *pVal);
	STDMETHOD(getStateTrainingRmse)(VARIANT *pVal);
	STDMETHOD(getStateTestRmse)(VARIANT *pVal);
	STDMETHOD(getStateModelRate)(double *pVal);
	STDMETHOD(getOutputTrainingCorr)(VARIANT *pVal);
	STDMETHOD(getOutputTestCorr)(VARIANT *pVal);
	STDMETHOD(getOutputTrainingRmse)(VARIANT *pVal);
	STDMETHOD(getOutputTestRmse)(VARIANT *pVal);
	STDMETHOD(getOutputModelRate)(double *pVal);
	STDMETHOD(trainModelFromFiles)(VARIANT dataFileNames, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(trainStateModelFromFile)(BSTR inputFileName, BSTR outputFileName, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(trainOutputModelFromFile)(BSTR inputFileName, BSTR outputFileName, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(trainStateModel)(VARIANT input, VARIANT output, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(trainOutputModel)(VARIANT input, VARIANT output, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(calculateOptimization)(/*[out, retval]*/ short * pVal);
	STDMETHOD(get_loadOnRun)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_loadOnRun)(/*[in]*/ BOOL newVal);
	STDMETHOD(getNumberOfVariables)(/*[in]*/ short type, /*[out, retval]*/ short * pVal);
	STDMETHOD(setWeightsByTag)(/*[in]*/ BSTR tag, /*[in]*/ VARIANT values);
	STDMETHOD(getWeightsByTag)(/*[in]*/ BSTR tag, /*[out, retval]*/ VARIANT * pVal);
	STDMETHOD(setWeightsByName)(/*[in]*/ BSTR name, /*[in]*/ VARIANT values);
	STDMETHOD(getWeightsByName)(/*[in]*/ BSTR name, /*[out, retval]*/ VARIANT * pVal);
	STDMETHOD(setValues)(/*[in]*/ short index, /*[in]*/ VARIANT values);
	STDMETHOD(getValues)(/*[in]*/ short type, /*[out, retval]*/ VARIANT  * pVal);
	STDMETHOD(setValueByTag)(/*[in]*/ BSTR tag, /*[in]*/ double value);
	STDMETHOD(getValueByTag)(/*[in]*/ BSTR tag, /*[out, retval]*/ double * pVal);
	STDMETHOD(setValueByName)(/*[in]*/ BSTR name, double value);
	STDMETHOD(getValueByName)(/*[in]*/ BSTR name, /*[out, retval]*/ double * pVal);
	STDMETHOD(setBoundsByTag)(/*[in]*/ BSTR name, /*[in]*/ VARIANT value);
	STDMETHOD(getBoundsByTag)(/*[in]*/ BSTR tag, /*[out, retval]*/ VARIANT * bounds);
	STDMETHOD(setBoundsByName)(/*[in]*/ BSTR name, /*[in]*/ VARIANT value);
	STDMETHOD(get_stateTags)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_exogenousTags)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_manipulatedTags)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_outputTags)(short index,/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(getBoundsByName)(/*[in]*/ BSTR name, /*[out, retval]*/ VARIANT * bounds);
	STDMETHOD(calculate)();
	STDMETHOD(get_stateNames)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_stateUnits)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_exogenousNames)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_exogenousUnits)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_manipulatedNames)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_manipulatedUnits)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_optimizationFilePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_optimizationFilePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_optimizationFileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_optimizationFileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(loadOptimization)(/*[in]*/ BSTR file,/*[in, defaultvalue("")]*/ BSTR directory);
	STDMETHOD(get_outputNames)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_outputUnits)(short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_optimizationFullPath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_optimizationFullPath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_optimizationComment)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_optimizationComment)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_optimizationName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_optimizationName)(/*[in]*/ BSTR newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("NeurOnLine Optimizer");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
	CComBSTR m_bstrCaption;
	BOOL m_bValid;

protected:
	BSTR m_optimizationName;
	BSTR m_optimizationComment;
	BSTR m_optimizationFullPath;
	BSTR m_optimizationFileName;
	BSTR m_optimizationFilePath;

	VARIANT_BOOL m_loadOnRun;
	BOOL m_isLoaded;
	short m_numberOfBounds;
	short m_numberOfWeights;

	jobjectArray m_outputNames;
	jobjectArray m_manipulatedNames;
	jobjectArray m_stateNames;
	jobjectArray m_exogenousNames;
	jobjectArray m_outputTags;
	jobjectArray m_manipulatedTags;
	jobjectArray m_stateTags;
	jobjectArray m_exogenousTags;
    jclass cls;
	jobject m_optimizer;

	jobjectArray m_outputUnits;
	jobjectArray m_manipulatedUnits;
	jobjectArray m_stateUnits;
	jobjectArray m_exogenousUnits;
};

#endif //__NOLOPTIMIZER_H_
