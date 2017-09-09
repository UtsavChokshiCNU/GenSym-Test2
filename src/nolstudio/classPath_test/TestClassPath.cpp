// TestClassPath.cpp: implementation of the CTestClassPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "classPath_test.h"
#include "TestClassPath.h"
#include "jni.h"
#include"..\ActiveX\ConfigData.cpp"
// #include"..\ActiveX\NolPredictor.cpp"
// #include"..\ActiveX\NolOptimizer.cpp"
// #include "..\ActiveX\NolOnline.cpp"

//#include "..\ActiveX\jvm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CComModule _Module;
static JavaVM *jvm = NULL;	// gchen 7-23-99
static JNIEnv *env = NULL;	// gchen 7-23-99
//Added by Cage 2009/9/25
static HINSTANCE s_hInstance = NULL;//The instance of current module
//end of add
#define PATH_SEPARATOR ';'


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

CPPUNIT_TEST_SUITE_REGISTRATION(CTestClassPath);


CTestClassPath::CTestClassPath()
{
}

CTestClassPath::~CTestClassPath()
{

}

void CTestClassPath::test_getJVM()
{
	getJVM();
}