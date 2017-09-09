// NolPredictor.cpp : Implementation of CNolPredictor

#include "stdafx.h"
#include "NolOnline.h"
#include "NolPredictor.h"

/////////////////////////////////////////////////////////////////////////////
// CNolPredictor


STDMETHODIMP CNolPredictor::loadModel(BSTR ModelFileName, BSTR ModelFilePath)
{
	if(m_isLoaded) 
		return S_OK;
	jmethodID mid;
	jstring jfile;
	jstring jresult;
	jint jnumber;
	JNIEnv *env;

	env = getJavaEnvironment();
	int pathLength = SysStringLen(ModelFilePath);

	if(pathLength == 0){
		jfile = convertString(ModelFileName);
		mid =env->GetMethodID(cls,"loadModel","(Ljava/lang/String;)V");
		CheckJavaException(FALSE, _T("loadModel 1"));
		if (mid == 0) {
			::MessageBox(NULL, "Can't find OnlinePredictorAPI loadModel method", "loading", MB_OK);	
			return S_OK;
		}
		env->CallVoidMethod(m_processor,mid,jfile);
		CheckJavaException(FALSE, _T("loadModel 2"));
		env->DeleteLocalRef(jfile);
	}else{
		jstring jdir = convertString(ModelFilePath);
		jfile = convertString(ModelFileName);
		mid =env->GetMethodID(cls,"loadModel","(Ljava/lang/String;Ljava/lang/String;)V");
		CheckJavaException(FALSE, _T("loadModel 3"));
		if (mid == 0) {
			::MessageBox(NULL, "Can't find OnlinePredictorAPI loadModel method", "loading", MB_OK);	
			return S_OK;
		}
		env->CallVoidMethod(m_processor,mid,jfile,jdir);
		CheckJavaException(FALSE, _T("loadModel 4"));
		env->DeleteLocalRef(jfile);
		env->DeleteLocalRef(jdir);
	}
	mid =env->GetMethodID(cls,"getName","()Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 5"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getName method", "loading", MB_OK);	
        return S_OK;
    }
	jresult = (jstring)env->CallObjectMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("loadModel 6"));
	m_modelName = convertString(jresult);

	mid =env->GetMethodID(cls,"getComment","()Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 7"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getComment method", "loading", MB_OK);	
        return S_OK;
    }
	jresult = (jstring)env->CallObjectMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("loadModel 8"));
	m_modelComment = convertString(jresult);
	env->DeleteLocalRef(jresult);

	mid =env->GetMethodID(cls,"getOutputNames","()[Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 9"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getOutputNames method", "loading", MB_OK);	
        return S_OK;
    }	
	m_outputNames = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_processor,mid));
	CheckJavaException(FALSE, _T("loadModel 10"));

	mid =env->GetMethodID(cls,"getOutputTags","()[Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 11"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getOutputTags method", "loading", MB_OK);	
        return S_OK;
    }	
	m_outputTags = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_processor,mid));
	CheckJavaException(FALSE, _T("loadModel 12"));

	mid =env->GetMethodID(cls,"getInputNames","()[Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 13"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getOutputTags method", "loading", MB_OK);	
        return S_OK;
    }	
	m_inputNames = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_processor,mid));
	CheckJavaException(FALSE, _T("loadModel 14"));
	mid =env->GetMethodID(cls,"getInputTags","()[Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 15"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getInputTags method", "loading", MB_OK);	
        return S_OK;
    }	
	m_inputTags = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_processor,mid));
	CheckJavaException(FALSE, _T("loadModel 16"));

	mid =env->GetMethodID(cls,"getNumberOfInputs","()I");
	CheckJavaException(FALSE, _T("loadModel 17"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getNumberOfInputs method", "loading", MB_OK);	
        return S_OK;
    }
	jnumber = (jint)env->CallIntMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("loadModel 18"));
	m_numberOfInputs = jnumber;
	
	mid =env->GetMethodID(cls,"getNumberOfOutputs","()I");
	CheckJavaException(FALSE, _T("loadModel 19"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getNumberOfOutputs method", "loading", MB_OK);	
        return S_OK;
    }
	jnumber = (jint)env->CallIntMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("loadModel 20"));

	mid =env->GetMethodID(cls,"getInputUnits","()[Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 21"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getInputUnits method", "loading", MB_OK);	
        return S_OK;
    }	
	m_inputUnits = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_processor,mid));
	CheckJavaException(FALSE, _T("loadModel 22"));
	mid =env->GetMethodID(cls,"getOutputUnits","()[Ljava/lang/String;");
	CheckJavaException(FALSE, _T("loadModel 23"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getOutputUnits method", "loading", MB_OK);	
        return S_OK;
    }	
	m_outputUnits = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_processor,mid));
	CheckJavaException(FALSE, _T("loadModel 24"));
	m_numberOfOutputs = jnumber;
	m_isLoaded = TRUE;

	return S_OK;
}

STDMETHODIMP CNolPredictor::getNumberOfInputs(long *pVal)
{
	*pVal = m_numberOfInputs;
	return S_OK;
}

STDMETHODIMP CNolPredictor::getNumberOfOutputs(long *pVal)
{
	*pVal = m_numberOfOutputs;
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputAtTimeByIndex(long Index, double InputValue, BSTR Time)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setInputAtTimeByIndex", "(IDLjava/lang/String;)V");
	CheckJavaException(FALSE, _T("setInputAtTimeByIndex 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setInputAtTimeByIndex method", "loading", MB_OK);	
		return S_OK;
	}
	jstring jtime = convertString(Time);
	env->CallVoidMethod(m_processor, mid, Index, InputValue, jtime);
	CheckJavaException(FALSE, _T("setInputAtTimeByIndex 2"));
	env->DeleteLocalRef(jtime);
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputAtTimeByName(BSTR Name, double InputValue, BSTR Time)
{
  	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setInputAtTimeByName", "(Ljava/lang/String;DLjava/lang/String;)V");
	CheckJavaException(FALSE, _T("setInputAtTimeByName 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setInputAtTimeByName method", "loading", MB_OK);	
		return S_OK;
	}
	jstring jname = convertString(Name);
	jstring jtime = convertString(Time);
	env->CallVoidMethod(m_processor, mid, jname, InputValue, jtime);
	CheckJavaException(FALSE, _T("setInputAtTimeByName 2"));
	env->DeleteLocalRef(jname);
	env->DeleteLocalRef(jtime);
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputAtTimeByTag(BSTR Tag, double InputValue, BSTR Time)
{
  	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setInputAtTimeByTag", "(Ljava/lang/String;DLjava/lang/String;)V");
	CheckJavaException(FALSE, _T("setInputAtTimeByTag 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setInputAtTimeByTag method", "loading", MB_OK);	
		return S_OK; 
	}
	jstring jtag = convertString(Tag);
	jstring jtime = convertString(Time);
	env->CallVoidMethod(m_processor, mid, jtag, InputValue, jtime);
	CheckJavaException(FALSE, _T("setInputAtTimeByTag 2"));
	env->DeleteLocalRef(jtag);
	env->DeleteLocalRef(jtime);
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputForRowByIndex(long Index, double InputValue)
{
  	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setInputForRowByIndex", "(ID)V");
	CheckJavaException(FALSE, _T("setInputForRowByIndex 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setInputForRowByIndex method", "loading", MB_OK);	
        return S_OK;
	}
	env->CallVoidMethod(m_processor, mid, Index, InputValue);
	CheckJavaException(FALSE, _T("setInputForRowByIndex 2"));
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputForRowByName(BSTR InputName, double InputValue)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setInputForRowByName", "(Ljava/lang/String;D)V");
	CheckJavaException(FALSE, _T("setInputForRowByName 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setInputForRowByName method", "loading", MB_OK);	
        return S_OK;
	}
	jstring jname = convertString(InputName);
	env->CallVoidMethod(m_processor, mid, jname, InputValue);
	CheckJavaException(FALSE, _T("setInputForRowByName 2"));
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputForRowByTag(BSTR Tag, double InputValue)
{
  	if(!m_isLoaded){
		return S_OK;
	}
    jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setInputForRowByTag", "(Ljava/lang/String;D)V");
	CheckJavaException(FALSE, _T("setInputForRowByTag 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setInputForRowByTag method", "loading", MB_OK);	
        return S_OK;
	}
	jstring jtag = convertString(Tag);
	env->CallVoidMethod(m_processor, mid, jtag, InputValue);
	CheckJavaException(FALSE, _T("setInputForRowByTag 2"));
	env->DeleteLocalRef(jtag);
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputsAtTime(VARIANT Inputs, BSTR Time)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	SAFEARRAY *sa;
	if(Inputs.vt == (VT_ARRAY|VT_R8)) {
		sa = Inputs.parray;
	}else if (Inputs.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = Inputs.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
		return S_OK;
	}

	long ins = 0;
	getNumberOfInputs(&ins);
	double va;
	for(long i=0;i<ins;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		setInputAtTimeByIndex(i, va, Time);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::setInputsForRow(VARIANT Inputs)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	SAFEARRAY *sa;
	if(Inputs.vt == (VT_ARRAY|VT_R8)) {
		sa = Inputs.parray;
	}else if (Inputs.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = Inputs.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
		return S_OK;
	}

	long n = SafeArrayGetElemsize(sa);
	long ins = 0;
	getNumberOfInputs(&ins);

	double va;
	for(long i=0;i<ins;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		setInputForRowByIndex(i, va);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::calculateOutputsAtTime(BSTR Time, VARIANT *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
    jmethodID mid;
    JNIEnv *env;
	long numOutputs;
	SAFEARRAY *sa;
	VARIANT vaResult;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "calculateOutputAtTime", "(Ljava/lang/String;)V");
	CheckJavaException(FALSE, _T("calculateOutputsAtTime 1"));
	if (mid == 0) {
		return Error("Can't find method calculateOutputAtTime."); // S_FALSE
	}
	jstring jtime = convertString(Time);
	env->CallVoidMethod(m_processor, mid,jtime);
	CheckJavaException(FALSE, _T("calculateOutputsAtTime 2"));
	getNumberOfOutputs(&numOutputs);

	// now create a safe array of numOutputs elements
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)numOutputs); 
	if (sa == NULL) {
		return E_OUTOFMEMORY;
	}
	vaResult.parray = sa;

	mid = env->GetMethodID(cls, "getOutputAtTimeByIndex", "(ILjava/lang/String;)D");
	CheckJavaException(FALSE, _T("calculateOutputsAtTime 3"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getOutputAtTimeByIndex method", "loading", MB_OK);	
        return S_OK;
	}
	// fill variant structure, an array of doubles
	jdouble output;
	for(long i = 0; i < numOutputs; i++)
	{
		output = (jdouble) env->CallDoubleMethod(m_processor, mid, i, jtime);
		CheckJavaException(FALSE, _T("calculateOutputsAtTime 4"));
		SafeArrayPutElement(sa, &i, (void*)(&output));
	}
	*pVal = vaResult;
	env->DeleteLocalRef(jtime);
	return S_OK;
}

STDMETHODIMP CNolPredictor::calculateOutputsForRow(VARIANT *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
    jmethodID mid;
    JNIEnv *env;
	long numOutputs;
	SAFEARRAY *sa;
	VARIANT vaResult;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "calculateOutputForRow", "()V");
	CheckJavaException(FALSE, _T("calculateOutputForRow 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI calculateOutputForRow method", "loading", MB_OK);	
        return S_OK;
	}
	env->CallVoidMethod(m_processor, mid);
	CheckJavaException(FALSE, _T("calculateOutputForRow 2"));
	getNumberOfOutputs(&numOutputs);

	// now create a safe array of numOutputs elements
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)numOutputs); 
	if (sa == NULL) {
		return E_OUTOFMEMORY;
	}
	vaResult.parray = sa;

	mid = env->GetMethodID(cls, "getCurrentOutputByIndex", "(I)D");
	CheckJavaException(FALSE, _T("calculateOutputForRow 3"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getCurrentOutputByIndex method", "loading", MB_OK);	
        return S_OK;
	}
	// fill variant structure, an array of doubles
	jdouble output;
	for(long i = 0; i < numOutputs; i++)
	{
		output = (jdouble) env->CallDoubleMethod(m_processor, mid, i);
		CheckJavaException(FALSE, _T("calculateOutputForRow 4"));
		SafeArrayPutElement(sa, &i, (void*)(&output));
	}
	*pVal = vaResult;
	return S_OK;
}

STDMETHODIMP CNolPredictor::setTimeFormat(BSTR newVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
	JNIEnv *env;
	env = getJavaEnvironment();
	m_timeFormat = newVal;
	jstring format = convertString(newVal);
	mid =env->GetMethodID(cls,"setTimeFormat","(Ljava/lang/String;)V");
	CheckJavaException(FALSE, _T("setTimeFormat 1"));
    if (mid == 0) {
 		::MessageBox(NULL, "Can't find OnlinePredictorAPI setTimeFormat method", "loading", MB_OK);	
       return S_OK;
    }
	env->CallVoidMethod(m_processor,mid,format);
	CheckJavaException(FALSE, _T("setTimeFormat 2"));
	env->DeleteLocalRef(format);
	return S_OK;
}

STDMETHODIMP CNolPredictor::isTimeBasedModel(VARIANT_BOOL *pbool)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
	jboolean hasTime;
	JNIEnv *env;
	env = getJavaEnvironment();

	mid =env->GetMethodID(cls,"hasTimeStamps","()Z");
    if (mid == 0) {
 		::MessageBox(NULL, "No hasTimeStamps method", "Load", MB_OK);	
       return S_OK;
    }
	hasTime = env->CallBooleanMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("hasTimeStamps"));
	VARIANT_BOOL hasT = 0;
	if(hasTime){
 //		::MessageBox(NULL, "time-based", "Load", MB_OK);	
		hasT = 1;
	}else{
 //		::MessageBox(NULL, "row-based", "Load", MB_OK);	
	}
	*pbool = hasT;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_modelComment(BSTR *pVal)
{
	*pVal = m_modelComment; 
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_modelComment(BSTR newVal)
{
	m_modelComment = newVal;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_modelFilePath(BSTR *pVal)
{
	*pVal = m_modelFilePath;
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_modelFilePath(BSTR newVal)
{
	m_modelFilePath = newVal;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_modelFileName(BSTR *pVal)
{
	*pVal = m_modelFileName;
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_modelFileName(BSTR newVal)
{
	m_modelFileName = newVal;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_modelName(BSTR *pVal)
{
	*pVal = m_modelName; 
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_modelName(BSTR newVal)
{
	m_modelName = newVal;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_inputNames(short index, BSTR *pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_inputNames);
	CheckJavaException(FALSE, _T("get_inputNames 0"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_inputNames,index);
		CheckJavaException(FALSE, _T("get_inputNames 1"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_inputTags(short index, BSTR *pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_inputTags);
	CheckJavaException(FALSE, _T("get_inputTags 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_inputTags,index);
		CheckJavaException(FALSE, _T("get_inputTags 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_outputNames(short index, BSTR *pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_outputNames);
	CheckJavaException(FALSE, _T("get_outputNames 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_outputNames,index);
		CheckJavaException(FALSE, _T("get_outputNames 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_outputTags(short index, BSTR *pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_outputTags);
	CheckJavaException(FALSE, _T("get_outputTags 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_outputTags,index);
		CheckJavaException(FALSE, _T("get_outputTags 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_timeFormat(BSTR *pVal)
{
	*pVal = m_timeFormat; 
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_timeFormat(BSTR newVal)
{
	jmethodID mid;
	JNIEnv *env;
	env = getJavaEnvironment();
	m_timeFormat = newVal;
	jstring format = convertString(newVal);
	mid =env->GetMethodID(cls,"setTimeFormat","(Ljava/lang/String;)V");
	CheckJavaException(FALSE, _T("put_timeFormat 1"));
    if (mid == 0) {
 		::MessageBox(NULL, "Can't find OnlinePredictorAPI setTimeFormat method", "loading", MB_OK);	
       return S_OK;
    }
	env->CallVoidMethod(m_processor,mid,format);
	CheckJavaException(FALSE, _T("put_timeFormat 2"));
	env->DeleteLocalRef(format);
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_modelFullPath(BSTR *pVal)
{
	*pVal = m_modelPath; 
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_modelFullPath(BSTR newVal)
{
	USES_CONVERSION;
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char fullFileName[_MAX_FNAME + _MAX_EXT + 1] ;
	char fullDirName[_MAX_DRIVE + _MAX_DIR + 1];

	_splitpath(W2A(newVal), drive, dir, fname, ext );

	 sprintf(fullFileName, "%s%s", fname, ext);
	 sprintf(fullDirName, "%s%s", drive, dir);

	 m_modelFilePath = T2BSTR(fullDirName);
	 m_modelFileName = T2BSTR(fullFileName);
	 
	m_modelPath = newVal;
	m_isLoaded = FALSE;
	loadModel(m_modelFileName,m_modelFilePath);
	if(m_loadOnRun == -1){
		m_bValid = TRUE;
	}
//	put_Caption(newVal);  //Gchen need to check the loadrun property.

/*	FireOnChanged(DISPID_VALID);
	FireOnChanged(DISPID_CAPTION);
	FireOnChanged(21);
*/	
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_numberOfInputs(long *pVal)
{
	*pVal = m_numberOfInputs;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_numberOfOutputs(long *pVal)
{
	*pVal = m_numberOfOutputs;
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_loadOnRun(VARIANT_BOOL *pVal)
{
	*pVal = m_loadOnRun;
	return S_OK;
}

STDMETHODIMP CNolPredictor::put_loadOnRun(VARIANT_BOOL newVal)
{
	if(m_isLoaded){
		m_loadOnRun = newVal;
		if(m_loadOnRun == -1){
			m_bValid = TRUE;
		}else{
			m_bValid = FALSE;
		}
		return S_OK;
	}
	m_loadOnRun = 0;
	return S_OK;
}

STDMETHODIMP CNolPredictor::trainModel(VARIANT input, VARIANT output, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
{
	double val;
	long lDim[2];
    long xcols;
    long xrows;
    long ycols;
    long yrows;
	HRESULT hresult;
    jclass matlibCls;
    jclass matrixCls;
	JNIEnv *env;
	jmethodID staticMid;
	jmethodID mid;
	SAFEARRAY *sax;
	SAFEARRAY *say;
	jobject inputMatrix;
	jobject outputMatrix;
	jboolean jautoStop;
	jboolean jnewTraining;
	jboolean jdisplay;
	jdouble jtimeinMili;
	jint jninputs;
	jint jnoutputs;

	if(!m_isLoaded){
		return S_OK;
	}
	
	if(input.vt == (VT_ARRAY|VT_R8)) {
		sax = input.parray;
	}else if (input.vt == (VT_VARIANT | VT_ARRAY)){
		VARIANT *vat;
		vat = input.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sax = vat->parray;
		}
	}else{
		::MessageBox(NULL, "Wrong input data type!", "Train Model", MB_OK);	
		return S_OK;
	}

	hresult = SafeArrayGetUBound(sax, 1, &xrows);
    if(FAILED(hresult)){
		::MessageBox(NULL, "Error access input data!", "Train Model", MB_OK);	
		return S_OK;
	}
	hresult = SafeArrayGetUBound(sax, 2, &xcols);
    if(FAILED(hresult)){
		::MessageBox(NULL, "Error access input data!", "Train Model", MB_OK);	
		return S_OK;
	}

	if(output.vt == (VT_ARRAY|VT_R8)) {
		say = output.parray;
	}else if (input.vt == (VT_VARIANT | VT_ARRAY)){
		VARIANT *vat;
		vat = output.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			say = vat->parray;
		}
	}else{
		::MessageBox(NULL, "Wrong output data type!", "Train Model", MB_OK);	
		return S_OK;
	}
	hresult = SafeArrayGetUBound(say, 1, &yrows);
    if(FAILED(hresult)){
		::MessageBox(NULL, "Error access output data!", "Train Model", MB_OK);	
		return S_OK;
	}
	hresult = SafeArrayGetUBound(say, 2, &ycols);
    if(FAILED(hresult)){
		::MessageBox(NULL, "Error access output data!", "Train Model", MB_OK);	
		return S_OK;
	}

	if (yrows != xrows){
		::MessageBox(NULL, "X and Y do not have same number of rows!", "Train Model", MB_OK);	
		return S_OK;
	}
	if (yrows < 10){
		::MessageBox(NULL, "TThere is not enough data for training!", "Train Model", MB_OK);	
		return S_OK;
	}

	env = getJavaEnvironment();
	mid = env->GetMethodID(cls, "getNumberOfModelInputs", "()I");
	CheckJavaException(FALSE, _T("trainModel"));
	jninputs = (jint)env->CallIntMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("trainModel"));

	mid = env->GetMethodID(cls, "getNumberOfModelOutputs", "()I");
	CheckJavaException(FALSE, _T("trainModel"));
	jnoutputs = (jint)env->CallIntMethod(m_processor,mid);
	CheckJavaException(FALSE, _T("trainModel"));

	if (ycols != jnoutputs){
		::MessageBox(NULL, "The number of Y column does not match model outputs!", "Train Model", MB_OK);	
		return S_OK;
	}
	if (xcols != jninputs){
		::MessageBox(NULL, "The number of X column does not match model inputs!", "Train Model", MB_OK);	
		return S_OK;
	}
	
	matlibCls = env->FindClass("com/gensym/math/matrix/Matlib");
	matrixCls = env->FindClass("com/gensym/math/matrix/Matrix");
	if (matlibCls == 0) {
		::MessageBox(NULL, "Can't find Matlib class", "Train Model", MB_OK);	
		return S_OK;
	}
	if (matrixCls == 0) {
		::MessageBox(NULL, "Can't find Matrix class", "Train Model", MB_OK);	
		return S_OK;
	}
	staticMid =env->GetStaticMethodID(matlibCls,"createMatrix","(II)Lcom/gensym/math/matrix/Matrix;");
	if (staticMid == 0) {
		::MessageBox(NULL, "Can't find Matlib createMatrix method", "trainModel", MB_OK);	
		return S_OK;
	}
	inputMatrix = env->CallStaticObjectMethod(matlibCls,staticMid, xrows,xcols);
	mid =env->GetMethodID(matrixCls,"set","(IID)V");
	if (mid == 0) {
		::MessageBox(NULL, "Can't find Matrix set method", "trainModel", MB_OK);	
		return S_OK;
	}
	for(long i=0;i<xrows;i++){
		for(long j=0;j<xcols;j++){
			lDim[0] = i;
			lDim[1] = j;
			hresult = SafeArrayGetElement(sax, lDim, (void*)(&val));
			if(FAILED(hresult)){
				::MessageBox(NULL, "Error access input data!", "Train Model", MB_OK);	
				return S_OK;
			}
			env->CallVoidMethod(inputMatrix, mid, i, j, val);
			CheckJavaException(FALSE, _T("trainModel 1"));
		}
	}
	outputMatrix = env->CallStaticObjectMethod(matlibCls,staticMid, yrows,ycols);
	for( i=0;i<yrows;i++){
		for(long j=0;j<ycols;j++){
			lDim[0] = i;
			lDim[1] = j;
			hresult = SafeArrayGetElement(say, lDim, (void*)(&val));
			if(FAILED(hresult)){
				::MessageBox(NULL, "Error access output data!", "Train Model", MB_OK);	
				return S_OK;
			}
			env->CallVoidMethod(outputMatrix, mid, i, j, val);
			CheckJavaException(FALSE, _T("trainModel 2"));
		}
	}
    
	mid = env->GetMethodID(cls, "trainModel", "(Ljava/util/Vector;Lcom/gensym/math/matrix/Matrix;Lcom/gensym/math/matrix/Matrix;DZZZ)V");
	CheckJavaException(FALSE, _T("trainModel"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI trainModel method", "loading", MB_OK);	
		return S_OK;
	}
	if(autoStop){
		jautoStop = 1;
	}else{
		jautoStop = 0;
	}
	if(newTraining){
		jnewTraining = 1;
	}else{
		jnewTraining = 0;
	}
	if(display){
		jdisplay = 1;
	}else{
		jdisplay = 0;
	}
	if (timeInMinute == 0 ) timeInMinute = 1.0;
	jtimeinMili = timeInMinute*60000.0;
	env->CallVoidMethod(m_processor, mid, NULL, inputMatrix,outputMatrix, jtimeinMili, jautoStop, jnewTraining,display);
	CheckJavaException(FALSE, _T("trainModel 3"));
	env->DeleteLocalRef(inputMatrix);
	env->DeleteLocalRef(outputMatrix);
	return S_OK;
}

STDMETHODIMP CNolPredictor::trainModelFromFile(BSTR inputFileName, BSTR outputFileName, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
{
//	USES_CONVERSION;
//::MessageBox(NULL, W2A(inputFileName), "trainModelFromFile", MB_OK);	
//::MessageBox(NULL, W2A(outputFileName), "trainModelFromFile", MB_OK);	
	jstring jinputFileName;
	jstring joutputFileName;
	JNIEnv *env;
	jmethodID mid;
	jboolean jautoStop;
	jboolean jnewTraining;
	jboolean jdisplay;
	jdouble jtimeinMili;
	jinputFileName = convertString(inputFileName);
	joutputFileName = convertString(outputFileName);
	if(autoStop){
		jautoStop = 1;
	}else{
		jautoStop = 0;
	}
	if(newTraining){
		jnewTraining = 1;
	}else{
		jnewTraining = 0;
	}
	if(display){
		jdisplay = 1;
	}else{
		jdisplay = 0;
	}
	if (timeInMinute == 0 ) timeInMinute = 1.0;
	jtimeinMili = timeInMinute*60000.0;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "trainModelFromFile", "(Ljava/util/Vector;Ljava/lang/String;Ljava/lang/String;DZZZ)V");
	CheckJavaException(FALSE, _T("trainModelFromFile 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI trainModelFromFile method", "loading", MB_OK);	
		return S_OK;
	}
//::MessageBox(NULL, "start calling trainModelFromFile", "trainModelFromFile", MB_OK);	
	env->CallVoidMethod(m_processor, mid, NULL, jinputFileName,joutputFileName, jtimeinMili, jautoStop, jnewTraining,jdisplay);
	CheckJavaException(FALSE, _T("trainModelFromFile 2"));
	env->DeleteLocalRef(jinputFileName);
	env->DeleteLocalRef(joutputFileName);
	return S_OK;
}

STDMETHODIMP CNolPredictor::trainModelFromFiles(VARIANT dataFileNames, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
{
	USES_CONVERSION;
	JNIEnv *env;
	jmethodID mid;
	HRESULT hresult;
	SAFEARRAY *sa;
	BSTR fileName;
	long size;
	jobjectArray jfileNames;
	jboolean jautoStop;
	jboolean jnewTraining;
	jboolean jdisplay;
	jdouble jtimeinMili;

	if(dataFileNames.vt == (VT_ARRAY|VT_BSTR)) {
		sa = dataFileNames.parray;
	}else{
		::MessageBox(NULL, "Wrong input data type!", "Train Model from File", MB_OK);	
		return S_OK;
	}
	hresult = SafeArrayGetUBound(sa, 1, &size);
    if(FAILED(hresult)){
		::MessageBox(NULL, "Error access input data!", "Train Model from File", MB_OK);	
		return S_OK;
	}

	env = getJavaEnvironment();

	jclass strArrCls = env->FindClass("Ljava/lang/String;");
	if (strArrCls == 0) {
		::MessageBox(NULL, "Can not fine String class!", "Train Model from File", MB_OK);	
		return S_OK;
	}
	jfileNames = env->NewObjectArray(size, strArrCls, NULL);
	
	for(long i=0;i<size;i++){
		hresult = SafeArrayGetElement(sa, &i, &fileName);
		if(FAILED(hresult)){
			::MessageBox(NULL, "Error access input data!", "Train Model from File", MB_OK);	
			return S_OK;
		}
		jstring jfileName = convertString(fileName); 
		env->SetObjectArrayElement(jfileNames, i, jfileName);
		env->DeleteLocalRef(jfileName);
	}
	if(autoStop){
		jautoStop = 1;
	}else{
		jautoStop = 0;
	}
	if(newTraining){
		jnewTraining = 1;
	}else{
		jnewTraining = 0;
	}
	if(display){
		jdisplay = 1;
	}else{
		jdisplay = 0;
	}
	if (timeInMinute == 0 ) timeInMinute = 1.0;
	jtimeinMili = timeInMinute*60000.0;
    mid = env->GetMethodID(cls, "trainModelFromFile", "(Ljava/util/Vector;[Ljava/lang/String;DZZZ)V");
	CheckJavaException(FALSE, _T("trainModelFromFile 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI trainModelFromFile method", "loading", MB_OK);	
		return S_OK;
	}
	env->CallVoidMethod(m_processor, mid, NULL, jfileNames,jtimeinMili, jautoStop, jnewTraining,jdisplay);
	CheckJavaException(FALSE, _T("trainModelFromFile 2"));
	env->DeleteLocalRef(jfileNames);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getModelRate(double *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
	jdouble jresult;
	JNIEnv *env;
	env = getJavaEnvironment();

	mid =env->GetMethodID(cls,"getModelRate","()D");
 	CheckJavaException(TRUE, _T("getModelRate 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getModelRate method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid);
 	CheckJavaException(TRUE, _T("getModelRate 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	return S_OK;
}

STDMETHODIMP CNolPredictor::getTestRmse(VARIANT *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	JNIEnv *env;
	env = getJavaEnvironment();
	jboolean	isCopy;
	SAFEARRAY *sa;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	mid =env->GetMethodID(cls,"getTestRmse","()[D");
	CheckJavaException(TRUE, _T("getTestRmse 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getTestRmse method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_processor,mid);
	CheckJavaException(TRUE, _T("getTestRmse 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getTestRmse 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getTestRmse 4"));
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}
	vaResult.parray = sa;
	*pVal = vaResult;

	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolPredictor::getTrainingRmse(VARIANT *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	JNIEnv *env;
	env = getJavaEnvironment();
	jboolean	isCopy;
	SAFEARRAY *sa;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	mid =env->GetMethodID(cls,"getTrainingRmse","()[D");
	CheckJavaException(TRUE, _T("getTrainingRmse 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getTrainingRmse method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_processor,mid);
	CheckJavaException(TRUE, _T("getTrainingRmse 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getTrainingRmse 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getTrainingRmse 4"));
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}
	vaResult.parray = sa;
	*pVal = vaResult;

	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolPredictor::getTestCorr(VARIANT *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	JNIEnv *env;
	env = getJavaEnvironment();
	jboolean	isCopy;
	SAFEARRAY *sa;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	mid =env->GetMethodID(cls,"getTestCorr","()[D");
	CheckJavaException(TRUE, _T("getTestCorr 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getTestCorr method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_processor,mid);
	CheckJavaException(TRUE, _T("getTestCorr 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getTestCorr 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getTestCorr 4"));
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}
	vaResult.parray = sa;
	*pVal = vaResult;

	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	env->DeleteLocalRef(jresultArray);


	return S_OK;
}

STDMETHODIMP CNolPredictor::getTrainingCorr(VARIANT *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	JNIEnv *env;
	env = getJavaEnvironment();
	jboolean	isCopy;
	SAFEARRAY *sa;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	mid =env->GetMethodID(cls,"getTrainingCorr","()[D");
	CheckJavaException(TRUE, _T("getTrainingCorr 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI getTrainingCorr method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_processor,mid);
	CheckJavaException(TRUE, _T("getTrainingCorr 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getTrainingCorr 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getTrainingCorr 4"));
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}
	vaResult.parray = sa;
	*pVal = vaResult;

	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolPredictor::get_inputUnits(short index, BSTR *pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_inputUnits);
	CheckJavaException(FALSE, _T("get_inputUnits 0"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_inputUnits,index);
		CheckJavaException(FALSE, _T("get_inputUnits 1"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolPredictor::get_outputUnits(short index, BSTR *pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_outputUnits);
	CheckJavaException(FALSE, _T("get_outputUnits 0"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_outputUnits,index);
		CheckJavaException(FALSE, _T("get_outputUnits 1"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}
/* 
::MessageBox(NULL, "VT_ARRAY|VT_R8", "Find type x", MB_OK);	
::MessageBox(NULL, "VT_VARIANT | VT_ARRAY", "Find type x", MB_OK);	
::MessageBox(NULL, "other type", "Find type x", MB_OK);	
   sprintf(testStr, "matrix size = %d, %d", xrows, xcols);
::MessageBox(NULL, testStr, "Find  x size", MB_OK);	
sprintf(testStr, "matrix value = %f, i=%d,j= %d", val,i,j);
::MessageBox(NULL, testStr, "Find type x", MB_OK);	
   sprintf(testStr, "y matrix size = %d, %d", yrows, ycols);
::MessageBox(NULL, testStr, "Find  y size", MB_OK);	
sprintf(testStr, "matrix value = %f, i=%d,j= %d", val,i,j);
::MessageBox(NULL, testStr, "Find type y", MB_OK);	

*/

STDMETHODIMP CNolPredictor::setVariableValueAtTimeByName(BSTR Name, double val, BSTR Time)
{
  	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setVariableValueAtTimeByName", "(Ljava/lang/String;DLjava/lang/String;)V");
	CheckJavaException(FALSE, _T("setVariableValueAtTimeByName 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setVariableValueAtTimeByName method", "loading", MB_OK);	
		return S_OK;
	}
	jstring jname = convertString(Name);
	jstring jtime = convertString(Time);
	env->CallVoidMethod(m_processor, mid, jname, val, jtime);
	CheckJavaException(FALSE, _T("setVariableValueAtTimeByName 2"));
	env->DeleteLocalRef(jname);
	env->DeleteLocalRef(jtime);

	return S_OK;
}

STDMETHODIMP CNolPredictor::setVariableValueAtTimeByTag(BSTR Tag, double val, BSTR Time)
{

 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
    JNIEnv *env;
	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "setVariableValueAtTimeByTag", "(Ljava/lang/String;DLjava/lang/String;)V");
	CheckJavaException(FALSE, _T("setVariableValueAtTimeByTag 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlinePredictorAPI setVariableValueAtTimeByTag method", "loading", MB_OK);	
		return S_OK; 
	}
	jstring jtag = convertString(Tag);
	jstring jtime = convertString(Time);
	env->CallVoidMethod(m_processor, mid, jtag, val, jtime);
	CheckJavaException(FALSE, _T("setVariableValueAtTimeByTag 2"));
	env->DeleteLocalRef(jtag);
	env->DeleteLocalRef(jtime);

	return S_OK;
}

STDMETHODIMP CNolPredictor::getMaxValueByName(BSTR name,double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getMaxValueByName 0"));
	mid =env->GetMethodID(cls,"getMaxValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMaxValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMaxValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMaxValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getMaxValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getMaxValueByTag 0"));
	mid =env->GetMethodID(cls,"getMaxValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMaxValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMaxValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMaxValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getMinValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getMinValueByName 0"));
	mid =env->GetMethodID(cls,"getMinValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMinValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMinValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMinValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolPredictor::getMinValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getMinValueByTag 0"));
	mid =env->GetMethodID(cls,"getMinValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMinValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMinValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMinValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getMeanValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getMeanValueByName 0"));
	mid =env->GetMethodID(cls,"getMeanValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMeanValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMeanValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMeanValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getMeanValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getMeanValueByTag 0"));
	mid =env->GetMethodID(cls,"getMeanValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMeanValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMeanValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMeanValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getMedianValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getMedianValueByName 0"));
	mid =env->GetMethodID(cls,"getMedianValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMedianValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMedianValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMedianValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getMedianValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getMedianValueByTag 0"));
	mid =env->GetMethodID(cls,"getMedianValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getMedianValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getMedianValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getMedianValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
	return S_OK;
}

STDMETHODIMP CNolPredictor::getSumValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getSumValueByName 0"));
	mid =env->GetMethodID(cls,"getSumValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getSumValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getSumValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getSumValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getSumValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getSumValueByTag 0"));
	mid =env->GetMethodID(cls,"getSumValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getSumValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getSumValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getSumValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getSTDValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getSTDValueByName 0"));
	mid =env->GetMethodID(cls,"getSTDValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getSTDValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getSTDValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getSTDValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getSTDValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getSTDValueByTag 0"));
	mid =env->GetMethodID(cls,"getSTDValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getSTDValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getSTDValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getSTDValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getVarianceValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getVarianceValueByName 0"));
	mid =env->GetMethodID(cls,"getVarianceValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getVarianceValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getVarianceValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getVarianceValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getVarianceValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getVarianceValueByTag 0"));
	mid =env->GetMethodID(cls,"getVarianceValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getVarianceValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getVarianceValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getVarianceValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getKurtValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getKurtValueByName 0"));
	mid =env->GetMethodID(cls,"getKurtValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getKurtValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getKurtValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getKurtValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getKurtValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getKurtValueByTag 0"));
	mid =env->GetMethodID(cls,"getKurtValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getKurtValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getKurtValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getKurtValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getSkewValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getSkewValueByName 0"));
	mid =env->GetMethodID(cls,"getSkewValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getSkewValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getSkewValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getSkewValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getSkewValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getSkewValueByTag 0"));
	mid =env->GetMethodID(cls,"getSkewValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getSkewValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getSkewValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getSkewValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getRangeValueByName(BSTR name, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getRangeValueByName 0"));
	mid =env->GetMethodID(cls,"getRangeValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getRangeValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getRangeValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getRangeValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::getRangeValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getRangeValueByTag 0"));
	mid =env->GetMethodID(cls,"getRangeValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getRangeValueByTag 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlinePredictorAPI getRangeValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_processor,mid,jname);
 	CheckJavaException(TRUE, _T("getRangeValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolPredictor::clearDataBuffer()
{
    jmethodID mid;
    JNIEnv *env;

	env = getJavaEnvironment();
    mid = env->GetMethodID(cls, "clearDataBuffer", "()V");
	CheckJavaException(FALSE, _T("clearDataBuffer 1"));
	env->CallVoidMethod(m_processor, mid);
	CheckJavaException(FALSE, _T("clearDataBuffer 2"));
	return S_OK;
}
