// NolPredictor.h : Declaration of the CNolPredictor

#ifndef __NOLPREDICTOR_H_
#define __NOLPREDICTOR_H_

#include "resource.h"       // main symbols
#include <atlctl.h>

#include "jni.h"           
#include "jvm.h"

/////////////////////////////////////////////////////////////////////////////
// CNolPredictor
class ATL_NO_VTABLE CNolPredictor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<INolPredictor, &IID_INolPredictor, &LIBID_NOLONLINELib>,
	public CComControl<CNolPredictor>,
	public IPersistStreamInitImpl<CNolPredictor>,
	public IOleControlImpl<CNolPredictor>,
	public IOleObjectImpl<CNolPredictor>,
	public IOleInPlaceActiveObjectImpl<CNolPredictor>,
	public IViewObjectExImpl<CNolPredictor>,
	public IOleInPlaceObjectWindowlessImpl<CNolPredictor>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CNolPredictor>,
	public IPersistStorageImpl<CNolPredictor>,
	public ISpecifyPropertyPagesImpl<CNolPredictor>,
	public IQuickActivateImpl<CNolPredictor>,
	public IDataObjectImpl<CNolPredictor>,
	public IProvideClassInfo2Impl<&CLSID_NolPredictor, &DIID__INolPredictorEvents, &LIBID_NOLONLINELib>,
	public IPropertyNotifySinkCP<CNolPredictor>,
	public CComCoClass<CNolPredictor, &CLSID_NolPredictor>
{
public:
	CNolPredictor()
	{
		m_modelName = '\0';
		m_modelComment = '\0'; //(BSTR)_T("comment1");
		m_modelPath = '\0';
		m_modelFileName = '\0';
		m_modelFilePath = '\0';
		m_timeFormat = '\0';
		m_isLoaded = FALSE;
		m_loadOnRun = -1;
		m_numberOfInputs = 0;
		m_numberOfOutputs = 0;

	
		jmethodID mid;
		JNIEnv *env;
		env = getJavaEnvironment();
		if(env == NULL) {
			::MessageBox(NULL, "Environment is null", "Fatal Error", MB_OK);				
		}

		cls = env->FindClass("com/gensym/nols/deploy/OnlineProcessor");
		if (cls == 0) {
			::MessageBox(NULL, "Can't find OnlineProcessor class", "loading", MB_OK);	
			return;
		}

		mid = env->GetMethodID(cls,"<init>","()V");
		if (mid == 0) {
			::MessageBox(NULL, "Can't find OnlineProcessor init method", "loading", MB_OK);	
			return;
		}
		m_processor = env->NewGlobalRef(env->NewObject(cls,mid));  

	}

		~CNolPredictor()
	{
		JNIEnv *env;
		env = getJavaEnvironment();
		m_modelName = '\0';
		m_modelComment = '\0'; //(BSTR)_T("comment1");
		m_modelPath = '\0';
		m_modelFileName = '\0';
		m_modelFilePath = '\0';
		m_timeFormat = '\0';
		m_loadOnRun = -1;
		m_numberOfInputs = 0;
		m_numberOfOutputs = 0;

		env->DeleteGlobalRef(m_processor);
		m_processor = NULL;

		if(m_isLoaded){
			env->DeleteGlobalRef(m_outputNames);
			m_outputNames = NULL;
			env->DeleteGlobalRef(m_inputNames);
			m_inputNames = NULL;
			env->DeleteGlobalRef(m_outputTags);
			m_outputTags = NULL;
			env->DeleteGlobalRef(m_inputTags);
			m_inputTags = NULL;
		}
		m_isLoaded = FALSE;
		ATLTRACE(_T("I'm out of here\n"));
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NOLPREDICTOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNolPredictor)
	COM_INTERFACE_ENTRY(INolPredictor)
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

BEGIN_PROP_MAP(CNolPredictor)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_PAGE(CLSID_NolPredictorProp)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CNolPredictor)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CNolPredictor)
	CHAIN_MSG_MAP(CComControl<CNolPredictor>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()

	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_INolPredictor,
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
	STDMETHOD(clearDataBuffer)();
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
	STDMETHOD(getMaxValueByTag)(/*[in]*/ BSTR tag,  /*[out,retval]*/ double *pVal);
	STDMETHOD(getMaxValueByName)(/*[in]*/ BSTR name, /*[out,retval]*/ double *pVal);
	STDMETHOD(setVariableValueAtTimeByTag)(BSTR Name, double val, BSTR Time);
	STDMETHOD(setVariableValueAtTimeByName)(BSTR Name, double val, BSTR Time);
	STDMETHOD(getTrainingCorr)(VARIANT *pVal);
	STDMETHOD(getTestCorr)(VARIANT *pVal);
	STDMETHOD(getTrainingRmse)(VARIANT *pVal);
	STDMETHOD(getTestRmse)(VARIANT *pVal);
	STDMETHOD(getModelRate)(double *pVal);
	STDMETHOD(trainModelFromFiles)(VARIANT dataFileNames, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(trainModelFromFile)(BSTR inputFileName, BSTR outputFileName, double  timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(trainModel)(VARIANT input, VARIANT output, double timeInMinute, VARIANT_BOOL  autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display);
	STDMETHOD(get_loadOnRun)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_loadOnRun)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_numberOfOutputs)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_numberOfInputs)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_modelFullPath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_modelFullPath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_timeFormat)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_timeFormat)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_outputTags)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_outputNames)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_outputUnits)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_inputTags)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_inputNames)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_inputUnits)(/*[in]*/ short index, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_modelName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_modelName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_modelFileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_modelFileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_modelFilePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_modelFilePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_modelComment)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_modelComment)(/*[in]*/ BSTR newVal);
	STDMETHOD(isTimeBasedModel)(/*[out, retval]*/VARIANT_BOOL* pbool);
	STDMETHOD(setTimeFormat)(BSTR newVal);
	STDMETHOD(calculateOutputsForRow)(/*[out, retval]*/ VARIANT* pVal);
	STDMETHOD(calculateOutputsAtTime)(/*[in]*/ BSTR Time,/*[out, retval]*/ VARIANT* pVal);
	STDMETHOD(setInputsForRow)(/*[in]*/ VARIANT Inputs);
	STDMETHOD(setInputsAtTime)(/*[in]*/ VARIANT Inputs,/*[in]*/ BSTR Time);
	STDMETHOD(setInputForRowByTag)(/*[in]*/ BSTR Tag,/*[in]*/ double InputValue);
	STDMETHOD(setInputForRowByName)(/*[in]*/ BSTR InputName,/*[in]*/ double InputValue);
	STDMETHOD(setInputForRowByIndex)(/*[in]*/ long Index,/*[in]*/ double InputValue);
	STDMETHOD(setInputAtTimeByTag)(/*[in]*/ BSTR Tag,/*[in]*/ double InputValue,/*[in]*/ BSTR Time);
	STDMETHOD(setInputAtTimeByName)(/*[in]*/ BSTR Name,/*[in]*/ double InputValue,/*[in]*/ BSTR Time);
	STDMETHOD(setInputAtTimeByIndex)(/*[in]*/ long Index,/*[in]*/ double InputValue,/*[in]*/ BSTR Time);
	STDMETHOD(getNumberOfOutputs)(/*[out, retval]*/ long *pVal);
	STDMETHOD(getNumberOfInputs)(/*[out, retval]*/ long *pVal);
	STDMETHOD(loadModel)(/*[in]*/ BSTR ModelFileName,/*[in, defaultvalue("")]*/ BSTR ModelFilePath);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("NeurOnLine Predictor");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}

protected:
	BOOL m_bValid;
	BSTR m_modelName;
	BSTR m_modelComment;
	BSTR m_modelPath;
	BSTR m_modelFileName;
	BSTR m_modelFilePath;
	BSTR m_timeFormat;
	long m_numberOfInputs;
	long m_numberOfOutputs;
	VARIANT_BOOL m_loadOnRun;
	BOOL m_isLoaded;
	jobjectArray m_outputNames ;
	jobjectArray m_inputNames;
	jobjectArray m_outputTags;
	jobjectArray m_inputTags;
    jclass cls;
	jobject m_processor;
	jobjectArray m_inputUnits;
	jobjectArray m_outputUnits;
};

#endif //__NOLPREDICTOR_H_
