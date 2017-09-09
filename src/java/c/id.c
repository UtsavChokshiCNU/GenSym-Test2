#include <id.h>
#include <jni.h>
#include <stdio.h>

char buffer[50];
extern long g2ext_nsleep( char* );


/*
 * Class:     com_gensym_tests_GetMachineID
 * Method:    getLocalMachineID
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_gensym_ntw_GetMachineID_getLocalMachineID
  (JNIEnv *env, jobject object) {

  long int dummy;

  dummy = g2ext_nsleep ( (char *) buffer );

  return (*env)->NewStringUTF(env, buffer);

}
