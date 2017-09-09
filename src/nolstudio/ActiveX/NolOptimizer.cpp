// NolOptimizer.cpp : Implementation of CNolOptimizer

#include "stdafx.h"
#include "NolOnline.h"
#include "NolOptimizer.h"

STDMETHODIMP CNolOptimizer::get_optimizationName(BSTR * pVal)
{
	*pVal = m_optimizationName; 
	return S_OK;
}

STDMETHODIMP CNolOptimizer::put_optimizationName(BSTR newVal)
{
	m_optimizationName = newVal;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_optimizationComment(BSTR * pVal)
{
	*pVal = m_optimizationComment; 
	return S_OK;
}

STDMETHODIMP CNolOptimizer::put_optimizationComment(BSTR newVal)
{
	m_optimizationComment = newVal;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_optimizationFullPath(BSTR * pVal)
{
	*pVal = m_optimizationFullPath; 
	return S_OK;
}

STDMETHODIMP CNolOptimizer::put_optimizationFullPath(BSTR newVal)
{
	USES_CONVERSION;
//	::MessageBox(NULL, W2A(newVal), "CNolOptimizer::put_optimizationFullPath 0", MB_OK);	

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char fullFileName[_MAX_FNAME + _MAX_EXT + 1] ;
	char fullDirName[_MAX_DRIVE + _MAX_DIR + 1];

	_splitpath(W2A(newVal), drive, dir, fname, ext );

	sprintf(fullFileName, "%s%s", fname, ext);
	sprintf(fullDirName, "%s%s", drive, dir);

	put_optimizationFileName(T2BSTR(fullFileName));
	put_optimizationFilePath(T2BSTR(fullDirName));

	m_isLoaded = FALSE;
	m_optimizationFullPath = newVal;
	loadOptimization(m_optimizationFileName,m_optimizationFilePath);
	if(m_loadOnRun){
		put_Valid(TRUE);
	}
	put_Caption(newVal);

	FireOnChanged(DISPID_VALID);
	FireOnChanged(DISPID_CAPTION);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::loadOptimization(BSTR file,BSTR directory)
{
	if(m_isLoaded) 
		return S_OK;
	jmethodID mid;
	jstring jfile;
	jstring jdir;
	jstring jresult;
	JNIEnv *env;

	env = getJavaEnvironment();
	jdir = convertString(directory);
 	CheckJavaException(TRUE, _T("loadOptimization 1"));
	jfile = convertString(file);
 	CheckJavaException(TRUE, _T("loadOptimization 2"));

	mid =env->GetMethodID(cls,"loadOptimization","(Ljava/lang/String;Ljava/lang/String;)V");
	CheckJavaException(TRUE, _T("loadOptimization 3"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI loadOptimization method", "loading", MB_OK);	
        return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid,jfile,jdir);
	CheckJavaException(TRUE, _T("loadOptimization 4"));

	mid =env->GetMethodID(cls,"getName","()Ljava/lang/String;");
	CheckJavaException(TRUE, _T("loadOptimization 5"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getName method", "loading", MB_OK);	
        return S_OK;
    }
	jresult = (jstring)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("loadOptimization 6"));
	m_optimizationName = convertString(jresult);
 	CheckJavaException(TRUE, _T("loadOptimization 7"));

	mid =env->GetMethodID(cls,"getComment","()Ljava/lang/String;");
	CheckJavaException(TRUE, _T("loadOptimization 8"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getComment method", "loading", MB_OK);	
        return S_OK;
    }
	jresult = (jstring)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("loadOptimization 9"));
	m_optimizationComment = convertString(jresult);

	mid =env->GetMethodID(cls,"getVariableNames","(I)[Ljava/lang/String;");
	CheckJavaException(TRUE, _T("loadOptimization 10"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getVariableNames method", "loading", MB_OK);	
        return S_OK;
    }	
	m_outputNames = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,0));
	CheckJavaException(TRUE, _T("loadOptimization 11"));
	m_manipulatedNames = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,1));
	CheckJavaException(TRUE, _T("loadOptimization 12"));
	m_exogenousNames = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,2));
	CheckJavaException(TRUE, _T("loadOptimization 13"));
	m_stateNames = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,3));
	CheckJavaException(TRUE, _T("loadOptimization 14"));

	mid =env->GetMethodID(cls,"getVariableTags","(I)[Ljava/lang/String;");
	CheckJavaException(TRUE, _T("loadOptimization 15"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getVariableTags method", "loading", MB_OK);	
        return S_OK;
    }	
	m_outputTags = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,0));
	CheckJavaException(TRUE, _T("loadOptimization 16"));
	m_manipulatedTags = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,1));
	CheckJavaException(TRUE, _T("loadOptimization 17"));
	m_exogenousTags = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,2));
	CheckJavaException(TRUE, _T("loadOptimization 18"));
	m_stateTags = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,3));
	CheckJavaException(TRUE, _T("loadOptimization 19"));


	mid =env->GetMethodID(cls,"getVariableUnits","(I)[Ljava/lang/String;");
	CheckJavaException(TRUE, _T("loadOptimization 20"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getVariableTags method", "loading", MB_OK);	
        return S_OK;
    }	
	m_outputUnits = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,0));
	CheckJavaException(TRUE, _T("loadOptimization 21"));
	m_manipulatedUnits = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,1));
	CheckJavaException(TRUE, _T("loadOptimization 22"));
	m_exogenousUnits = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,2));
	CheckJavaException(TRUE, _T("loadOptimization 23"));
	m_stateUnits = (jobjectArray)env->NewGlobalRef(env->CallObjectMethod(m_optimizer,mid,3));
	CheckJavaException(TRUE, _T("loadOptimization 24"));

	m_isLoaded = TRUE;

	env->DeleteLocalRef(jfile);
	env->DeleteLocalRef(jdir);
	env->DeleteLocalRef(jfile);
	env->DeleteLocalRef(jresult);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_optimizationFileName(BSTR * pVal)
{
	*pVal = m_optimizationFileName;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::put_optimizationFileName(BSTR newVal)
{
	m_optimizationFileName = newVal;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_optimizationFilePath(BSTR * pVal)
{
	*pVal = m_optimizationFilePath;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::put_optimizationFilePath(BSTR newVal)
{
	m_optimizationFilePath = newVal;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_outputNames(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_outputNames);
	CheckJavaException(TRUE, _T("get_outputNames 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_outputNames,index);
		CheckJavaException(TRUE, _T("get_outputNames 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}


STDMETHODIMP CNolOptimizer::get_manipulatedNames(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_manipulatedNames);
	CheckJavaException(TRUE, _T("get_manipulatedNames 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_manipulatedNames,index);
		CheckJavaException(TRUE, _T("get_manipulatedNames 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_exogenousNames(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_exogenousNames);
	CheckJavaException(TRUE, _T("get_exogenousNames 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_exogenousNames,index);
		CheckJavaException(TRUE, _T("get_exogenousNames 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_stateNames(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_stateNames);
	CheckJavaException(TRUE, _T("get_stateNames 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_stateNames,index);
		CheckJavaException(TRUE, _T("get_stateNames 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::calculate()
{
	jmethodID mid;
	JNIEnv *env;
	env = getJavaEnvironment();
	mid =env->GetMethodID(cls,"calculate","()V");
	CheckJavaException(TRUE, _T("calculate 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI calculate method", "loading", MB_OK);	
       return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("calculate 2"));
	return S_OK;
}


STDMETHODIMP CNolOptimizer::get_outputTags(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_outputTags);
	CheckJavaException(TRUE, _T("get_outputTags 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_outputTags,index);
		CheckJavaException(TRUE, _T("get_outputTags 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_manipulatedTags(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_manipulatedTags);
	CheckJavaException(TRUE, _T("get_manipulatedTags 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_manipulatedTags,index);
		CheckJavaException(TRUE, _T("get_manipulatedTags 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_exogenousTags(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_exogenousTags);
	CheckJavaException(TRUE, _T("get_exogenousTags 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_exogenousTags,index);
		CheckJavaException(TRUE, _T("get_exogenousTags 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_stateTags(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_stateTags);
	CheckJavaException(TRUE, _T("get_stateTags 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_stateTags,index);
		CheckJavaException(TRUE, _T("get_stateTags 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getBoundsByName(BSTR name, VARIANT * bounds)
{
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();
	jboolean	isCopy;
	SAFEARRAY *sa;

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	jname = convertString(name);
	CheckJavaException(TRUE, _T("getBoundsByName 0"));
	mid =env->GetMethodID(cls,"getBoundsByName","(Ljava/lang/String;)[D");
	CheckJavaException(TRUE, _T("getBoundsByName 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getBoundsByName method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid,jname);
	CheckJavaException(TRUE, _T("getBoundsByName 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getBoundsByName 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getBoundsByName 4"));
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}
	vaResult.parray = sa;
	*bounds = vaResult;

	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	env->DeleteLocalRef(jname);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::setBoundsByName(BSTR name, VARIANT value)
{
	jmethodID mid;
	jdouble* jvalueElems;
	jdoubleArray jvalueArray;
	jstring jname;
	JNIEnv *env;
	jboolean	isCopy;
	env = getJavaEnvironment();
	SAFEARRAY *sa;
	jname = convertString(name);
	CheckJavaException(TRUE, _T("setBoundsByName 0"));
	if(value.vt == (VT_ARRAY|VT_R8)) {
		sa = value.parray;
	}else if (value.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = value.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
 		::MessageBox(NULL, "Can not find array in variant.", "Running", MB_OK);	
		return S_OK;
	}
	jvalueArray = env->NewDoubleArray(m_numberOfBounds);
	CheckJavaException(TRUE, _T("setBoundsByName 1"));
	jvalueElems = env->GetDoubleArrayElements(jvalueArray,&isCopy);
	CheckJavaException(TRUE, _T("setBoundsByName 2"));
	double va;
	for(long i=0;i<m_numberOfBounds;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		jvalueElems[i] = va;
	}
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jvalueArray, jvalueElems, 0);
	mid =env->GetMethodID(cls,"setBoundsByName","(Ljava/lang/String;[D)V");
	CheckJavaException(TRUE, _T("setBoundsByName 3"));
    if (mid == 0) {
 		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setBoundsByName method", "loading", MB_OK);	
       return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid,jname,jvalueArray);
	CheckJavaException(TRUE, _T("setBoundsByName 4"));

	env->DeleteLocalRef(jname);
	env->DeleteLocalRef(jvalueArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getBoundsByTag(BSTR tag, VARIANT * bounds)
{
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	jstring jtag;
	JNIEnv *env;
	SAFEARRAY *sa;
	jboolean	isCopy;
	env = getJavaEnvironment();

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	jtag = convertString(tag);
	CheckJavaException(TRUE, _T("getBoundsByTag 0"));
	mid =env->GetMethodID(cls,"getBoundsByTag","(Ljava/lang/String;)[D");
	CheckJavaException(TRUE, _T("getBoundsByTag 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getBoundsByTag method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid,jtag);
	CheckJavaException(TRUE, _T("getBoundsByTag 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getBoundsByTag 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getBoundsByTag 4"));
	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}

	vaResult.parray = sa;
	*bounds = vaResult;
	
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	env->DeleteLocalRef(jtag);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::setBoundsByTag(BSTR tag, VARIANT value)
{
	jmethodID mid;
	jdouble* jvalueElems;
	jdoubleArray jvalueArray;
	jstring jtag;
	JNIEnv *env;
	jboolean	isCopy;
	env = getJavaEnvironment();
	SAFEARRAY *sa;
	jtag = convertString(tag);
	CheckJavaException(TRUE, _T("setBoundsByTag 1"));
	if(value.vt == (VT_ARRAY|VT_R8)) {
		sa = value.parray;
	}else if (value.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = value.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
 		::MessageBox(NULL, "Can not find array in variant.", "Running", MB_OK);	
		return S_OK;
	}
	jvalueArray = env->NewDoubleArray(m_numberOfBounds);
	CheckJavaException(TRUE, _T("setBoundsByTag 2"));
	jvalueElems = env->GetDoubleArrayElements(jvalueArray,&isCopy);
	CheckJavaException(TRUE, _T("setBoundsByTag 3"));
	double va;
	for(long i=0;i<m_numberOfBounds;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		jvalueElems[i] = va;
	}
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jvalueArray, jvalueElems, 0);
	mid =env->GetMethodID(cls,"setBoundsByTag","(Ljava/lang/String;[D)V");
	CheckJavaException(TRUE, _T("setBoundsByTag 4"));
    if (mid == 0) {
 		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setBoundsByTag method", "loading", MB_OK);	
        return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid,jtag,jvalueArray);
	CheckJavaException(TRUE, _T("setBoundsByTag 5"));

	env->DeleteLocalRef(jtag);
	env->DeleteLocalRef(jvalueArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getValueByName(BSTR name, double * pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getValueByName 0"));
	mid =env->GetMethodID(cls,"getValueByName","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getValueByName 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	
	return S_OK;
}

STDMETHODIMP CNolOptimizer::setValueByName(BSTR name, double value)
{
	jmethodID mid;
	jdouble jvalue;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("setValueByName 0"));
	jvalue = value;
	mid =env->GetMethodID(cls,"setValueByName","(Ljava/lang/String;D)V");
 	CheckJavaException(TRUE, _T("setValueByName 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setValueByName method", "loading", MB_OK);	
       return S_OK; 
    }
	env->CallVoidMethod(m_optimizer,mid,jname,jvalue);
 	CheckJavaException(TRUE, _T("setValueByName 1"));
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getValueByTag(BSTR tag, double * pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jtag;

	JNIEnv *env;
	env = getJavaEnvironment();
	jtag = convertString(tag);
	mid =env->GetMethodID(cls,"getValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getValueByTag 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getValueByTag method", "loading", MB_OK);	
        return S_OK; //Should be NaN or infinity. gchen 7.6.99
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jtag);
 	CheckJavaException(TRUE, _T("getValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	env->DeleteLocalRef(jtag);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::setValueByTag(BSTR tag, double value)
{
	jmethodID mid;
	jdouble jvalue;
	jstring jtag;
	JNIEnv *env;
	env = getJavaEnvironment();

	jtag = convertString(tag);
	jvalue = value;
	mid =env->GetMethodID(cls,"setValueByTag","(Ljava/lang/String;D)V");
 	CheckJavaException(TRUE, _T("setValueByTag 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	env->CallVoidMethod(m_optimizer,mid,jtag,jvalue);
 	CheckJavaException(TRUE, _T("setValueByTag 2"));
	env->DeleteLocalRef(jtag);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getValues(short type, VARIANT * pVal)
{
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	jint jtype = type;
	jboolean	isCopy;
	JNIEnv *env;
	SAFEARRAY *sa;
	env = getJavaEnvironment();

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);
	
	mid =env->GetMethodID(cls,"getValues","(I)[D");
 	CheckJavaException(TRUE, _T("getValues 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getValues method", "loading", MB_OK);	
        return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid,jtype);
 	CheckJavaException(TRUE, _T("getValues 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
 	CheckJavaException(TRUE, _T("getValues 3"));
	jint n = env->GetArrayLength(jresultArray);
 	CheckJavaException(TRUE, _T("getValues 4"));

	sa = SafeArrayCreateVector(VT_R8, 0, (unsigned int)n); 
	if (sa == NULL) {
		::MessageBox(NULL, "Can't create new array", "Running", MB_OK);	
		return E_OUTOFMEMORY;
	}
	for (long i = 0; i < n; i++) {
		SafeArrayPutElement(sa, &i, (void*)(&jvalueElems[i]));
	}
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jresultArray, jvalueElems, 0);
	vaResult.parray = sa;
	*pVal = vaResult;
	env->DeleteLocalRef(jresultArray);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::setValues(short type, VARIANT values)
{
	jmethodID mid;
	jdouble* jvalueElems;
	jdoubleArray jvalueArray;
	jint jtype = type;
	JNIEnv *env;
	jboolean	isCopy;
	SAFEARRAY *sa;
	env = getJavaEnvironment();

	if(values.vt == (VT_ARRAY|VT_R8)) {
		sa = values.parray;
	}else if (values.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = values.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
		::MessageBox(NULL, "Can't create new array.", "Running", MB_OK);	
		return S_OK;
	}
	short n = 0;
	getNumberOfVariables(type,&n);
	jvalueArray = env->NewDoubleArray(n);
	CheckJavaException(TRUE, _T("setValues 1"));
	jvalueElems = env->GetDoubleArrayElements(jvalueArray,&isCopy);
	CheckJavaException(TRUE, _T("setValues 2"));

	double va;
	for(long i=0;i<n;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		jvalueElems[i] = va;
	}
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jvalueArray, jvalueElems, 0);
	mid =env->GetMethodID(cls,"setValues","(I[D)V");
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setValues method", "loading", MB_OK);	
        return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid,jtype,jvalueArray);
	env->DeleteLocalRef(jvalueArray);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getWeightsByName(BSTR name, VARIANT * pVal)
{
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	jstring jname;
	JNIEnv *env;
	SAFEARRAY *sa;
	jboolean isCopy;
	env = getJavaEnvironment();

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	jname = convertString(name);
 	CheckJavaException(TRUE, _T("getWeightsByName 0"));
	mid =env->GetMethodID(cls,"getWeightsByName","(Ljava/lang/String;)[D");
 	CheckJavaException(TRUE, _T("getWeightsByName 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getWeightsByName method", "loading", MB_OK);	
        return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getWeightsByName 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
 	CheckJavaException(TRUE, _T("getWeightsByName 3"));
	jint n = env->GetArrayLength(jresultArray);
 	CheckJavaException(TRUE, _T("getWeightsByName 4"));
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
	env->DeleteLocalRef(jname);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::setWeightsByName(BSTR name, VARIANT values)
{
	jmethodID mid;
	jdouble* jvalueElems;
	jdoubleArray jvalueArray;
	jstring jname;
	JNIEnv *env;
	SAFEARRAY *sa;
	jboolean	isCopy;
	env = getJavaEnvironment();
	jname = convertString(name);
 	CheckJavaException(TRUE, _T("setWeightsByName 0"));
	if(values.vt == (VT_ARRAY|VT_R8)) {
		sa = values.parray;
	}else if (values.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = values.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
 		::MessageBox(NULL, "Can not find array in variant.", "Running", MB_OK);	
		return S_OK;
	}
	jvalueArray = env->NewDoubleArray(m_numberOfWeights);
 	CheckJavaException(TRUE, _T("setWeightsByName 1"));
	jvalueElems = env->GetDoubleArrayElements(jvalueArray,&isCopy);
 	CheckJavaException(TRUE, _T("setWeightsByName 2"));
	double va;
	for(long i=0;i<m_numberOfWeights;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		jvalueElems[i] = va;
	}
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jvalueArray, jvalueElems, 0);
	mid =env->GetMethodID(cls,"setWeightsByName","(Ljava/lang/String;[D)V");
 	CheckJavaException(TRUE, _T("setWeightsByName 3"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setWeightsByName method", "loading", MB_OK);	
        return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid,jname,jvalueArray);
 	CheckJavaException(TRUE, _T("setWeightsByName 4"));
	env->DeleteLocalRef(jname);
	env->DeleteLocalRef(jvalueArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getWeightsByTag(BSTR tag, VARIANT * pVal)
{
	VARIANT vaResult;
	jmethodID mid;
	jdoubleArray jresultArray;
	jdouble* jvalueElems;
	jstring jtag;
	JNIEnv *env;
	SAFEARRAY *sa;
	jboolean isCopy;
	env = getJavaEnvironment();

	VariantInit(&vaResult);
	vaResult.vt = (VT_ARRAY|VT_R8);

	jtag = convertString(tag);
 	CheckJavaException(TRUE, _T("getWeightsByTag 0"));
	mid =env->GetMethodID(cls,"getWeightsByTag","(Ljava/lang/String;)[D");
 	CheckJavaException(TRUE, _T("getWeightsByTag 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getWeightsByTag method", "loading", MB_OK);	
        return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid,jtag);
 	CheckJavaException(TRUE, _T("getWeightsByTag 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
 	CheckJavaException(TRUE, _T("getWeightsByTag 3"));
	jint n = env->GetArrayLength(jresultArray);
 	CheckJavaException(TRUE, _T("getWeightsByTag 4"));

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
	env->DeleteLocalRef(jtag);
	env->DeleteLocalRef(jresultArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::setWeightsByTag(BSTR tag, VARIANT values)
{
	jmethodID mid;
	jdouble* jvalueElems;
	jdoubleArray jvalueArray;
	jstring jtag;
	JNIEnv *env;
	SAFEARRAY *sa;
	jboolean isCopy;
	env = getJavaEnvironment();

	jtag = convertString(tag);
 	CheckJavaException(TRUE, _T("setWeightsByTag 0"));
	if(values.vt == (VT_ARRAY|VT_R8)) {
		sa = values.parray;
	}else if (values.vt == (VT_BYREF|VT_VARIANT)){
		VARIANT *vat;
		vat = values.pvarVal;
		if(vat->vt == (VT_ARRAY|VT_R8)) {
			sa = vat->parray;
		}
	}else{
 		::MessageBox(NULL, "Can not find array in variant.", "Running", MB_OK);	
		return S_OK;
	}
	jvalueArray = env->NewDoubleArray(m_numberOfWeights);
 	CheckJavaException(TRUE, _T("setWeightsByTag 1"));
	jvalueElems = env->GetDoubleArrayElements(jvalueArray,&isCopy);
 	CheckJavaException(TRUE, _T("setWeightsByTag 2"));
	double va;
	for(long i=0;i<m_numberOfWeights;i++){
		SafeArrayGetElement(sa, &i, (void*)(&va));
		jvalueElems[i] = va;
	}
	if (isCopy == JNI_TRUE)
		env->ReleaseDoubleArrayElements(jvalueArray, jvalueElems, 0);
	mid =env->GetMethodID(cls,"setWeightsByTag","(Ljava/lang/String;[D)V");
 	CheckJavaException(TRUE, _T("setWeightsByTag 3"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI setWeightsByTag method", "loading", MB_OK);	
        return S_OK;
    }
	env->CallVoidMethod(m_optimizer,mid,jtag,jvalueArray);
 	CheckJavaException(TRUE, _T("setWeightsByTag 4"));
	env->DeleteLocalRef(jtag);
	env->DeleteLocalRef(jvalueArray);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getNumberOfVariables(short type, short * pVal)
{
	if(!m_isLoaded){
		*pVal = 0;
		return S_OK;
	}
	jmethodID mid;
	jint jnumber;
	short number;
	JNIEnv *env;
	env = getJavaEnvironment();

	mid =env->GetMethodID(cls,"getNumberOfVariables","(I)I");
	CheckJavaException(TRUE, _T("getNumberOfVariables 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getNumberOfVariables method", "loading", MB_OK);	
        return S_OK;
    }
	jnumber = (jint)env->CallIntMethod(m_optimizer,mid,type);
	CheckJavaException(TRUE, _T("getNumberOfVariables 2"));

	number = (short)jnumber;
	*pVal = number;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_loadOnRun(BOOL *pVal)
{
	*pVal = m_loadOnRun;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::put_loadOnRun(BOOL newVal)
{
	if(m_isLoaded){
		m_loadOnRun = newVal;
		if(m_loadOnRun){
			put_Valid(TRUE);
		}else{
			put_Valid(FALSE);
		}
		return S_OK;
	}
	m_loadOnRun = FALSE;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::calculateOptimization(short *pVal)
{
	if(!m_isLoaded){
		*pVal = 0;
		return S_OK;
	}
	jmethodID mid;
	JNIEnv *env;
	env = getJavaEnvironment();
	mid =env->GetMethodID(cls,"optimize","()I");
	CheckJavaException(TRUE, _T("calculateOpt 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI calculate method", "loading", MB_OK);	
       return S_OK;
    }
	jint jnumber = (jint)env->CallIntMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("calculateOpt 2"));
	short number = (short)jnumber;
	*pVal = number;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::trainOutputModel(VARIANT input, VARIANT output, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
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
	mid = env->GetMethodID(cls, "getNumberOfOutputModelInputs", "()I");
	CheckJavaException(FALSE, _T("trainModel"));
	jninputs = (jint)env->CallIntMethod(m_optimizer,mid);
	CheckJavaException(FALSE, _T("trainModel"));

	mid = env->GetMethodID(cls, "getNumberOfOutputModelOutputs", "()I");
	CheckJavaException(FALSE, _T("trainModel"));
	jnoutputs = (jint)env->CallIntMethod(m_optimizer,mid);
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
    
	mid = env->GetMethodID(cls, "trainOutputModel", "(Ljava/util/Vector;Lcom/gensym/math/matrix/Matrix;Lcom/gensym/math/matrix/Matrix;DZZZ)V");
	CheckJavaException(FALSE, _T("trainModel"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI trainOutputModel method", "loading", MB_OK);	
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
	env->CallVoidMethod(m_optimizer, mid, NULL, inputMatrix,outputMatrix, jtimeinMili, jautoStop, jnewTraining,display);
	CheckJavaException(FALSE, _T("trainModel 3"));
	env->DeleteLocalRef(inputMatrix);
	env->DeleteLocalRef(outputMatrix);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::trainStateModel(VARIANT input, VARIANT output, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
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
	mid = env->GetMethodID(cls, "getNumberOfStateModelInputs", "()I");
	CheckJavaException(FALSE, _T("trainModel"));
	jninputs = (jint)env->CallIntMethod(m_optimizer,mid);
	CheckJavaException(FALSE, _T("trainModel"));

	mid = env->GetMethodID(cls, "getNumberOfStateModelOutputs", "()I");
	CheckJavaException(FALSE, _T("trainModel"));
	jnoutputs = (jint)env->CallIntMethod(m_optimizer,mid);
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
    
	mid = env->GetMethodID(cls, "trainStateModel", "(Ljava/util/Vector;Lcom/gensym/math/matrix/Matrix;Lcom/gensym/math/matrix/Matrix;DZZZ)V");
	CheckJavaException(FALSE, _T("trainModel"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI trainStateModel method", "loading", MB_OK);	
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
	env->CallVoidMethod(m_optimizer, mid, NULL, inputMatrix,outputMatrix, jtimeinMili, jautoStop, jnewTraining,display);
	CheckJavaException(FALSE, _T("trainModel 3"));
	env->DeleteLocalRef(inputMatrix);
	env->DeleteLocalRef(outputMatrix);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::trainOutputModelFromFile(BSTR inputFileName, BSTR outputFileName, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
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
    mid = env->GetMethodID(cls, "trainOutputModelFromFile", "(Ljava/util/Vector;Ljava/lang/String;Ljava/lang/String;DZZZ)V");
	CheckJavaException(FALSE, _T("trainOutputModelFromFile 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI trainOutputModelFromFile method", "loading", MB_OK);	
		return S_OK;
	}
//::MessageBox(NULL, "start calling trainModelFromFile", "trainModelFromFile", MB_OK);	
	env->CallVoidMethod(m_optimizer, mid, NULL, jinputFileName,joutputFileName, jtimeinMili, jautoStop, jnewTraining,jdisplay);
	CheckJavaException(TRUE, _T("trainOutputModelFromFile 2"));
	env->DeleteLocalRef(jinputFileName);
	env->DeleteLocalRef(joutputFileName);
	return S_OK;

}

STDMETHODIMP CNolOptimizer::trainStateModelFromFile(BSTR inputFileName, BSTR outputFileName, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
{
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
    mid = env->GetMethodID(cls, "trainStateModelFromFile", "(Ljava/util/Vector;Ljava/lang/String;Ljava/lang/String;DZZZ)V");
	CheckJavaException(FALSE, _T("trainStateModelFromFile 1"));
	if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI trainStateModelFromFile method", "loading", MB_OK);	
		return S_OK;
	}
//::MessageBox(NULL, "start calling trainModelFromFile", "trainModelFromFile", MB_OK);	
	env->CallVoidMethod(m_optimizer, mid, NULL, jinputFileName,joutputFileName, jtimeinMili, jautoStop, jnewTraining,jdisplay);
	CheckJavaException(TRUE, _T("trainStateModelFromFile 2"));
	env->DeleteLocalRef(jinputFileName);
	env->DeleteLocalRef(joutputFileName);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::trainModelFromFiles(VARIANT dataFileNames, double timeInMinute, VARIANT_BOOL autoStop, VARIANT_BOOL newTraining, VARIANT_BOOL display)
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
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI trainModelFromFile method", "loading", MB_OK);	
		return S_OK;
	}
	env->CallVoidMethod(m_optimizer, mid, NULL, jfileNames,jtimeinMili, jautoStop, jnewTraining,jdisplay);
	CheckJavaException(FALSE, _T("trainModelFromFile 2"));
	env->DeleteLocalRef(jfileNames);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getOutputModelRate(double *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
	jdouble jresult;
	JNIEnv *env;
	env = getJavaEnvironment();

	mid =env->GetMethodID(cls,"getOutputModelRate","()D");
 	CheckJavaException(TRUE, _T("getOutputModelRate 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getModelRate method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid);
 	CheckJavaException(TRUE, _T("getOutputModelRate 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getOutputTestRmse(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getOutputTestRmse","()[D");
	CheckJavaException(TRUE, _T("getOutputTestRmse 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getOutputTestRmse method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getOutputTestRmse 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getOutputTestRmse 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getOutputTestRmse 4"));
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

STDMETHODIMP CNolOptimizer::getOutputTrainingRmse(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getOutputTrainingRmse","()[D");
	CheckJavaException(TRUE, _T("getOutputTrainingRmse 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getOutputTrainingRmse method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getOutputTrainingRmse 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getOutputTrainingRmse 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getOutputTrainingRmse 4"));
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

STDMETHODIMP CNolOptimizer::getOutputTestCorr(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getOutputTestCorr","()[D");
	CheckJavaException(TRUE, _T("getOutputTestCorr 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getOutputTestCorr method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getOutputTestCorr 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getOutputTestCorr 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getOutputTestCorr 4"));
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

STDMETHODIMP CNolOptimizer::getOutputTrainingCorr(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getOutputTrainingCorr","()[D");
	CheckJavaException(TRUE, _T("getOutputTrainingCorr 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getOutputTrainingCorr method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getOutputTrainingCorr 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getOutputTrainingCorr 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getOutputTrainingCorr 4"));
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

STDMETHODIMP CNolOptimizer::getStateModelRate(double *pVal)
{
 	if(!m_isLoaded){
		return S_OK;
	}
	jmethodID mid;
	jdouble jresult;
	JNIEnv *env;
	env = getJavaEnvironment();

	mid =env->GetMethodID(cls,"getStateModelRate","()D");
 	CheckJavaException(TRUE, _T("getStateModelRate 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getStateModelRate method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid);
 	CheckJavaException(TRUE, _T("getStateModelRate 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getStateTestRmse(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getStateTestRmse","()[D");
	CheckJavaException(TRUE, _T("getStateTestRmse 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getStateTestRmse method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getStateTestRmse 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getStateTestRmse 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getStateTestRmse 4"));
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

STDMETHODIMP CNolOptimizer::getStateTrainingRmse(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getStateTrainingRmse","()[D");
	CheckJavaException(TRUE, _T("getStateTrainingRmse 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getStateTrainingRmse method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getStateTrainingRmse 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getStateTrainingRmse 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getStateTrainingRmse 4"));
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

STDMETHODIMP CNolOptimizer::getStateTestCorr(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getStateTestCorr","()[D");
	CheckJavaException(TRUE, _T("getStateTestCorr 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getStateTestCorr method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getStateTestCorr 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getStateTestCorr 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getStateTestCorr 4"));
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

STDMETHODIMP CNolOptimizer::getStateTrainingCorr(VARIANT *pVal)
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

	mid =env->GetMethodID(cls,"getStateTrainingCorr","()[D");
	CheckJavaException(TRUE, _T("getStateTrainingCorr 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getStateTrainingCorr method", "loading", MB_OK);	
       return S_OK;
    }
	jresultArray = (jdoubleArray)env->CallObjectMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getStateTrainingCorr 2"));
	jvalueElems = env->GetDoubleArrayElements(jresultArray,&isCopy);
	CheckJavaException(TRUE, _T("getStateTrainingCorr 3"));
	jint n = env->GetArrayLength(jresultArray);
	CheckJavaException(TRUE, _T("getStateTrainingCorr 4"));
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


STDMETHODIMP CNolOptimizer::get_outputUnits(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_outputUnits);
	CheckJavaException(TRUE, _T("get_outputUnits 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_outputUnits,index);
		CheckJavaException(TRUE, _T("get_outputUnits 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}


STDMETHODIMP CNolOptimizer::get_manipulatedUnits(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_manipulatedUnits);
	CheckJavaException(TRUE, _T("get_manipulatedUnits 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_manipulatedUnits,index);
		CheckJavaException(TRUE, _T("get_manipulatedUnits 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_exogenousUnits(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_exogenousUnits);
	CheckJavaException(TRUE, _T("get_exogenousUnits 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_exogenousUnits,index);
		CheckJavaException(TRUE, _T("get_exogenousUnits 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}

STDMETHODIMP CNolOptimizer::get_stateUnits(short index, BSTR * pVal)
{
	if(!m_isLoaded){
		BSTR str = '\0';
		*pVal = str;
		return S_OK;
	}
	JNIEnv *env;
	env = getJavaEnvironment();
	jint sz = env->GetArrayLength(m_stateUnits);
	CheckJavaException(TRUE, _T("get_stateUnits 1"));
	if(index < sz){
		jstring jresult = (jstring)env->GetObjectArrayElement(m_stateUnits,index);
		CheckJavaException(TRUE, _T("get_stateUnits 2"));
		*pVal = convertString(jresult);
		env->DeleteLocalRef(jresult);
	}
	return S_OK;
}


STDMETHODIMP CNolOptimizer::getMaxValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMaxValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMaxValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMaxValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMaxValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMaxValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMinValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMinValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMinValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMinValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMinValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMinValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);


	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMeanValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMeanValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMeanValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);


	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMeanValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMeanValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMeanValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);


	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMedianValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMedianValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMedianValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getMedianValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getMedianValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getMedianValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);


	return S_OK;
}

STDMETHODIMP CNolOptimizer::getSumValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getSumValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getSumValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);


	return S_OK;
}

STDMETHODIMP CNolOptimizer::getSumValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getSumValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getSumValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);


	return S_OK;
}

STDMETHODIMP CNolOptimizer::getSTDValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getSTDValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getSTDValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getSTDValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getSTDValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getSTDValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getVarianceValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getVarianceValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getVarianceValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getVarianceValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getVarianceValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getVarianceValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getKurtValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getKurtValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getKurtValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getKurtValueByTag(BSTR tag, double *pVal)
{
	jmethodID mid;
	jdouble jresult;
	jstring jname;
	JNIEnv *env;
	env = getJavaEnvironment();

	jname = convertString(tag);
 	CheckJavaException(TRUE, _T("getKurtValueByTag 0"));
	mid =env->GetMethodID(cls,"getKurtValueByTag","(Ljava/lang/String;)D");
 	CheckJavaException(TRUE, _T("getKurtValueByTag( 1"));
	if (mid == 0) {
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getKurtValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getKurtValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getSkewValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getSkewValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getSkewValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getSkewValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getSkewValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getSkewValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);

	return S_OK;
}

STDMETHODIMP CNolOptimizer::getRangeValueByName(BSTR name, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getRangeValueByName method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getRangeValueByName 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getRangeValueByTag(BSTR tag, double *pVal)
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
	   ::MessageBox(NULL, "Can't find OnlineOptimizerAPI getRangeValueByTag method", "loading", MB_OK);	
        return S_OK; 
    }
	jresult = env->CallDoubleMethod(m_optimizer,mid,jname);
 	CheckJavaException(TRUE, _T("getRangeValueByTag 2"));
	double dbtest = jresult;
	*pVal = dbtest;
	
	env->DeleteLocalRef(jname);
	return S_OK;
}

STDMETHODIMP CNolOptimizer::getNumberOfVariablesReachHardbound(short *pVal)
{
	if(!m_isLoaded){
		*pVal = 0;
		return S_OK;
	}
	jmethodID mid;
	jint jnumber;
	short number;
	JNIEnv *env;
	env = getJavaEnvironment();

	mid =env->GetMethodID(cls,"getNumberOfVariableNameAtHardBound","()I");
	CheckJavaException(TRUE, _T("getNumberOfVariableNameAtHardBound 1"));
    if (mid == 0) {
		::MessageBox(NULL, "Can't find OnlineOptimizerAPI getNumberOfVariableNameAtHardBound method", "loading", MB_OK);	
        return S_OK;
    }
	jnumber = (jint)env->CallIntMethod(m_optimizer,mid);
	CheckJavaException(TRUE, _T("getNumberOfVariableNameAtHardBound 2"));

	number = (short)jnumber;
	*pVal = number;
	return S_OK;
}
