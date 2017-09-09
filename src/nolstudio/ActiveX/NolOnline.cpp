// NolOnline.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f NolOnlineps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "NolOnline.h"
#include "jni.h"
#include "jvm.h"

#include "NolOnline_i.c"
#include "NolPredictor.h"
#include "NolPredictorProp.h"
#include "NolOptimizer.h"
#include "NolOptimizerProp.h"
#include "ConfigData.h"

CComModule _Module;
static JavaVM *jvm = NULL;	// gchen 7-23-99
static JNIEnv *env = NULL;	// gchen 7-23-99
//Added by Cage 2009/9/25
static HINSTANCE s_hInstance = NULL;//The instance of current module
//end of add
#define PATH_SEPARATOR ';'

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_NolPredictor, CNolPredictor)
OBJECT_ENTRY(CLSID_NolPredictorProp, CNolPredictorProp)
OBJECT_ENTRY(CLSID_NolOptimizer, CNolOptimizer)
OBJECT_ENTRY(CLSID_NolOptimizerProp, CNolOptimizerProp)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{  
	s_hInstance = hInstance;
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_NOLONLINELib);
        DisableThreadLibraryCalls(hInstance);
	}
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
// registers object, typelib and all interfaces in typelib

STDAPI DllRegisterServer(void)
{
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}






//---------------------------------------------------------------------------
//
// Get a handle to the java VM, which was created upon DLL Process attachment
// by Brian O. Bush, May 19, 1999
//
//---------------------------------------------------------------------------
/*
JavaVM* getJVM(void){
	
	if(jvm != NULL)  return jvm;
	jsize bufLen = 1;
	jsize nVms;
	JavaVM *vmBuf;

	// Try to get the created Java VM from another component
	jint res = JNI_GetCreatedJavaVMs( &vmBuf,bufLen,&nVms);
	if(res == 0){
		if(nVms >0){
			jvm = vmBuf;
			res = jvm->AttachCurrentThread((void **)&env, NULL);
			if (res < 0) 
			{
				::MessageBox(NULL, "Thread attach failed in getting Java Environment", "Fatal Error", MB_OK);
			}
			return jvm;
		}
	}
	JavaVMInitArgs vm_args;
	JavaVMOption options[1];

	char classpath[1024];
	char *nolvar;  
	nolvar = getenv( "NOLSTUDIO_HOME" );
	if( nolvar == NULL ){
		::MessageBox(NULL, "NOLSTUDIO_HOME is not defined!", "loading", MB_OK);	
		return FALSE;
	}
	sprintf(classpath, "%s%s%c%s%s%c%s%s%c%s%s%c%s%s%c%s%s%c%s%s%c%s%s",
			"-Djava.class.path=.;",nolvar, PATH_SEPARATOR,
			nolvar, "\\jre\\lib\\jaws.jar",PATH_SEPARATOR,
			nolvar, "\\jre\\lib\\i18n.jar",PATH_SEPARATOR,
			nolvar, "\\jre\\lib\\plugprov.jar",PATH_SEPARATOR,
			nolvar, "\\jre\\lib\\rt.jar",PATH_SEPARATOR,
			nolvar, "\\nolstudio\\NolStudioData.jar",PATH_SEPARATOR,
			nolvar, "\\nolstudio\\NolStudioDeploy.jar",PATH_SEPARATOR,
			nolvar, "\\nolstudio\\NolStudioMath.jar");

	options[0].optionString = classpath;
	
//::MessageBox(NULL, classpath, "loading", MB_OK);	
	vm_args.version = JNI_VERSION_1_2;
	vm_args.options = options;
	vm_args.nOptions = 1;
	vm_args.ignoreUnrecognized = JNI_FALSE;

// Note that in JDK 1.2, there is no longer any need to call 
   JNI_GetDefaultJavaVMInitArgs. 
//
	res = JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);
	if (res  == JNI_ERR) {
		::MessageBox(NULL, "Can't create Java VM", "loading", MB_OK);	
		return NULL;
	}
	return jvm;
}
*/
JavaVM* getJVM(void){
	
	if(jvm != NULL)  return jvm;
	jsize bufLen = 1;
	jsize nVms;
	JavaVM *vmBuf;

	char modulePath[MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char fullFilePath[MAX_PATH];
    
	typedef jint (JNICALL *JNICREATEPROC)(JavaVM **,  void  **,  void  *);
	typedef jint (JNICALL *JNIGETCREATEDJAVAVMS)(JavaVM **, jsize, jsize *);
	typedef jint (JNICALL *JNIGETDEFAULTJAVAVMINITARGS)(void *);

	//Get the current module file(NolOnline.dll) path.
	GetModuleFileName(s_hInstance,modulePath,MAX_PATH);
	_splitpath(modulePath, drive, dir, fname, ext );

	char *nolvar;
	nolvar = getenv("NOLSTUDIO_HOME");
	if( nolvar == NULL ){
		::MessageBox(NULL, "NOLSTUDIO_HOME is not defined!", "loading", MB_OK);	
		return FALSE;
	}

	sprintf(fullFilePath, "%s%s%s", drive, dir, "classPath.cfg");
	CConfigData cfg(fullFilePath);
	if (!cfg.ReadFile())
	{
		::MessageBox(NULL, "Can't find classpath cfg file", "loading", MB_OK);
		return NULL;
	}

    int iKeyNum = cfg.GetNumKeys();
	if (iKeyNum == 0)
	{
		//set the default value to class path.
		cfg.SetValue("Path", "jvmdll", "\\jre\\bin\\server\\jvm.dll");
		cfg.SetValue("Path", "javaws", "\\jre\\lib\\javaws.jar");
		cfg.SetValue("Path", "plugin", "\\jre\\lib\\plugin.jar");
		cfg.SetValue("Path", "rt", "\\jre\\lib\\rt.jar");
		cfg.SetValue("Path","NolStudioData", "\\nolstudio\\NolStudioData.jar");
		cfg.SetValue("Path","NolStudioDeploy", "\\nolstudio\\NolStudioDeploy.jar");
		cfg.SetValue("Path","NolStudioMath", "\\nolstudio\\NolStudioMath.jar");
		cfg.SetValue("Path","javalink", "\\javalink\\classes\\javalink.jar");
		cfg.WriteFile();
	}

 	string strJvmDll,strPathJaws, strPathPlugin, strPathRt, strPathNolStudioData,
		strPathNolStudioDeploy, strPathNolStudioMath, strPathJavalink;
	cfg.GetValue("Path","jvmdll", strJvmDll);
    cfg.GetValue("Path","javaws", strPathJaws);
	cfg.GetValue("Path","plugin", strPathPlugin);
	cfg.GetValue("Path","rt", strPathRt);
	cfg.GetValue("Path","NolStudioData", strPathNolStudioData);
	cfg.GetValue("Path","NolStudioDeploy", strPathNolStudioDeploy);
	cfg.GetValue("Path","NolStudioMath", strPathNolStudioMath);
	cfg.GetValue("Path","javalink", strPathJavalink);

	sprintf(fullFilePath, "%s%s", nolvar, strJvmDll.c_str());

	//load jvm.dll
     HINSTANCE jvmDll = LoadLibrary(fullFilePath);
     if  (jvmDll == NULL)
     {
		 ::MessageBox(NULL, "load jvm.dll error", "load", MB_OK);
         return  NULL;
	 }
		
	JNICREATEPROC jvmCreateProc = (JNICREATEPROC)GetProcAddress(jvmDll, "JNI_CreateJavaVM");
    JNIGETCREATEDJAVAVMS jvmGetCreatedJavaVms = (JNIGETCREATEDJAVAVMS)GetProcAddress(jvmDll, "JNI_GetCreatedJavaVMs");
	JNIGETDEFAULTJAVAVMINITARGS jvmGetDefaultJavaArgs = (JNIGETDEFAULTJAVAVMINITARGS)GetProcAddress(jvmDll, "JNI_GetDefaultJavaVMInitArgs");
	if  (jvmCreateProc == NULL || jvmGetCreatedJavaVms == NULL || jvmGetCreatedJavaVms == NULL)
	{
        FreeLibrary(jvmDll);
		return  NULL ;
    }

/* Try to get the created Java VM from another component*/
	jint res = (jvmGetCreatedJavaVms)(&vmBuf,bufLen,&nVms);
	if(res == 0){
		if(nVms >0){
			jvm = vmBuf;
			res = jvm->AttachCurrentThread((void **)&env, NULL);
			if (res < 0) 
			{
				::MessageBox(NULL, "Thread attach failed in getting Java Environment", "Fatal Error", MB_OK);
			}
			FreeLibrary(jvmDll);
			return jvm;
		}
	}
	JavaVMInitArgs vm_args;
	JavaVMOption options[1];

	char classpath[2048]; 

	sprintf(classpath, "%s%s%c%s%s%c%s%s%c%s%s%c%s%s%c%s%s%c%s%s%c%s%s",
 		"-Djava.class.path=.;",nolvar, PATH_SEPARATOR,
 		nolvar, strPathJaws.c_str(),PATH_SEPARATOR,
 		nolvar, strPathPlugin.c_str(),PATH_SEPARATOR,
		nolvar, strPathRt.c_str(),PATH_SEPARATOR,
 		nolvar, strPathNolStudioData.c_str(),PATH_SEPARATOR,
 		nolvar, strPathNolStudioDeploy.c_str(),PATH_SEPARATOR,
 		nolvar, strPathNolStudioMath.c_str(),PATH_SEPARATOR,
 		nolvar, strPathJavalink.c_str()
 		);

    options[0].optionString = classpath;
	vm_args.version = JNI_VERSION_1_2;
	vm_args.options = options;
	vm_args.nOptions = 1;
	vm_args.ignoreUnrecognized = JNI_TRUE;

/* Note that in JDK 1.2, there is no longer any need to call 
   JNI_GetDefaultJavaVMInitArgs. 
*/
	//res = (jvmGetDefaultJavaArgs)(&vm_args);
	res = (jvmCreateProc)(&jvm, (void **)&env, &vm_args);
	if (res  == JNI_ERR) {
		::MessageBox(NULL, "Can't create Java VM", "loading", MB_OK);	
		FreeLibrary(jvmDll);
		return NULL;
	}
	FreeLibrary(jvmDll);
	return jvm;
}
//---------------------------------------------------------------------------
//
// Get a handle to the java Environment
// by Brian O. Bush, May 19, 1999
//
//---------------------------------------------------------------------------

JNIEnv* getJavaEnvironment(void) 
{
	JavaVM *jvm1;
	jvm1 = getJVM();
	return env;
}


//---------------------------------------------------------------------------
//
// Detach current thread, used when ending a method that used a jvm environment
// by Brian O. Bush, May 19, 1999
//
//---------------------------------------------------------------------------

void releaseEnvironment(void) 
{
	if(jvm != NULL){
		jvm->DetachCurrentThread();
		jvm->DestroyJavaVM();
		jvm = NULL;
	}
}

/* convert a BSTR to a jstring */
jstring convertString(BSTR BString) 
{
	return env->NewString((jchar*)BString,(jsize)SysStringLen(BString));
}

/* convert a jstring to a BSTR */
BSTR convertString(jstring JString) 
{
	const jchar* tempstring;
	jboolean iscopy;
	BSTR BString;
	jsize size = env->GetStringLength(JString);
 	CheckJavaException(FALSE, _T("convertString 1"));
	tempstring = env->GetStringChars(JString, &iscopy);
 	CheckJavaException(FALSE, _T("convertString 2"));
	BString = SysAllocStringLen((OLECHAR*) tempstring, (unsigned int)size);  // basically builds a BSTR
	if(iscopy == JNI_TRUE) 
	{
		env->ReleaseStringChars(JString, tempstring);
	 	CheckJavaException(FALSE, _T("convertString 3"));
	}
	return BString;
}

BOOL CheckJavaException(BOOL verbose, char * inforString) 
{   
	// check to see if an exception occurred?
	jthrowable throwObj = env->ExceptionOccurred();
	if(throwObj != NULL) 
	{  
		jclass excls = env->GetObjectClass(throwObj);
		if (excls == 0) {
			::MessageBox(NULL, "Can't find Exception class", "Exception Occurred", MB_OK);	
			env->ExceptionClear();
			env->DeleteLocalRef(throwObj);
			return TRUE;
		}
		if(verbose) 
		{
			env->ExceptionClear();
			jmethodID mid = env->GetMethodID(excls, "toString", "()Ljava/lang/String;");
			if (mid == 0) {
				::MessageBox(NULL,"Can't find method toString.","Exception Occurred", MB_OK);
				return TRUE; // however we cannot get the message method
			}
			jstring msg = (jstring) env->CallObjectMethod(throwObj, mid, NULL);
			jboolean isCopy;
			const char* cmesg = env->GetStringUTFChars(msg, &isCopy);
			::MessageBox(NULL, cmesg, "Exception Occurred", MB_OK);	
			::MessageBox(NULL, inforString, "Exception Occurred", MB_OK);	
			env->DeleteLocalRef(throwObj);
			return TRUE;
		}
		env->ExceptionClear();
		env->DeleteLocalRef(throwObj);
		return TRUE;
	}
	else return FALSE;
}
