
#ifndef _JVM_H
#define _JVM_H
	JavaVM* getJVM(void);
	JNIEnv* getJavaEnvironment(void);
	void releaseEnvironment(void);
	jstring convertString(BSTR); 
	BSTR convertString(jstring); 
	BOOL CheckJavaException(BOOL,char *); 
#endif
