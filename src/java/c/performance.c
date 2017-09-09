#include <stdio.h>
#include "shared.h"
#include "dprintf.h"
#include <string.h>


#ifdef WIN32

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_com_tests_TestPerformance_start_1up
  (JNIEnv *env, jclass pThis)
{
  Java_com_gensym_com_ActiveXProxy_start_1up(env, pThis);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_empty_1c_1method
  (JNIEnv *env, jobject pThis) 
{}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_integer_1method
  (JNIEnv *env, jobject pThis, jint myint) 
{}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_double_1method
  (JNIEnv *env, jobject pThis, jdouble mydouble) 
{}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_string_1method
  (JNIEnv *env, jobject pThis, jstring mystring) 
{}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_variant_1method
  (JNIEnv *env, jobject pThis, jobject pVariant) 
{}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_vector_1method
  (JNIEnv *env, jobject pThis, jobject pVector) 
{}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_variant_1get_1class_1method
  (JNIEnv *env, jobject pThis, jobject pVariant) 
{
    jclass variant_class = NULL;

    variant_class = (*env)->GetObjectClass(env, pVariant);
    
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_variant_1get_1variant_1value
  (JNIEnv *env, jobject pThis, jobject pVariant) 
{
  VARIANT variant;

  init_variant_from_jobject(env, pVariant, &variant, NULL, FALSE);
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_callback_1cost
  (JNIEnv *env, jobject pThis, jobject pVariant, jint times) 
{
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_vector_1get_1values
  (JNIEnv *env, jobject pThis, jobject pVector) 
{
    create_dispparams(env, pVector, pThis);  
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_convert_1string
  (JNIEnv *env, jobject pThis, jstring pString) 
{
  BSTR myBstr = java_to_BSTR(env, pString);
  /* there is no free here on purpose, this will leak BSTR's */
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_convert_1string_1no_1sysalloc
  (JNIEnv *env, jobject pThis, jstring pString) 
{
  WCHAR* unicode_string = java_to_unicode_string(env, pString);
  free(unicode_string);
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_tests_TestPerformance_convert_1string_1then_1free
  (JNIEnv *env, jobject pThis, jstring pString) 
{
  BSTR myBstr = java_to_BSTR(env, pString);
  SysFreeString(myBstr);
}

#endif /* WIN32 */



