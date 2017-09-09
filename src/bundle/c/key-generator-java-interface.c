#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "key.h"

extern void keystruct_to_key (char* code, LICENSE_KEY *kstruct);

extern void randomize_seed();

JNIEXPORT jstring JNICALL Java_KeyData_getKey1
  (JNIEnv *env, jobject keyclass, 
	jint syntaxVersion, jint family_id, jint bundle_id, 
	jint os_id, jbyteArray componentArray)
{
	/* For showing that the basic JNI linking occurred
		and we go to this side of the fence
	unsigned char keystring[30] = "aaaaa-bbbbb-ccccc-ddddd-eeeee";
	printf("\nArrived in C land.\n"); */

	unsigned char keystring[30];
	jbyte buffer[NUMBER_OF_COMPONENTS];
	int i;
	LICENSE_KEY str;

	randomize_seed();

	/*  This is for making a dummy just to show that
	for(i=0; i<NUMBER_OF_COMPONENTS; i++)
        str.components[i]=0;
	str.installer_version = 1;
	str.system_id = 1;
	str.family_id = 1;
	str.bundle_id = 1;
	str.components[2] = 1;
	str.components[3] = 1;
	str.components[4] = 1;
	str.components[5] = 1; */
	

	/*str = (LICENSE_KEY*) malloc( sizeof(LICENSE_KEY) ); */
	
	str.installer_version = syntaxVersion;
	str.family_id = family_id;
	str.bundle_id = bundle_id;
	str.system_id = os_id;

	(*env)->GetIntArrayRegion(env, componentArray, 0, NUMBER_OF_COMPONENTS, buffer);
	for (i=0; i<NUMBER_OF_COMPONENTS; i++) {
		str.components[i] = buffer[i];
	}

	keystruct_to_key(keystring, &str);
	return (*env)->NewStringUTF(env, keystring);
}
