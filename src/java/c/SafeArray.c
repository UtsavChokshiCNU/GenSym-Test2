/*****************************************************************************
* SafeArray.c
*
* Author: Stephen Flores
*
* Notes:
*   09-27-1999: Since ActiveX safe arrays do not have the reference count
*               feature that that COM objects, we must handle all of the
*               special cases where a safe array could be destroyed.
*               We do not want the array to be destroyed more that once
*               because this cause a memory corruption that will cause a crash
*               in the OLE DLL later on. Next we want Java clean up our safe
*               arrays for us and not have special Java code to have to delete
*               the safe array at the correct time.
*
*               To avoid destroying the same safe array in multiple
*               finalizers, we have a count of how many Java wrappers
*               reference the same safe array and only destroy when the count
*               is zero.
*
*               To avoid destroying a safe array passing in during an event
*               we have a flag to tell us if the safe array is safe to
*               destroy. We check this flag in the finalizer. Also for later
*               on when we can return safe arrays from events, we have
*               methods that let the Java user set this flag.
*               
*               To avoid having a safe array destroyed by a finalizer that
*               has be put in an element in a variant safe array. We copy
*               the safe array.
*
*               To avoid haveing a safe array destroyed by a control when is
*               passed by reference or passed in a variant that is then
*               passed by reference, we lock the safe array before
*               IDispatch.Invoke and unlock after.
*
*****************************************************************************/

#include "shared.h"
#include "dprintf.h"

#define CLAIM_NOW TRUE
#define NOT_CLAIMED FALSE

#define OK_TO_DELETE TRUE
#define NOT_OUR_ARRAY FALSE

typedef struct _SAFEARRAYHOLDER {
  SAFEARRAY *pSA;
  int arrayType;
  int totalElements;
  int refCount;
  int oursToDelete;
} SAFEARRAYHOLDER;

typedef struct _SAHANDLEINFO {
  struct _SAHANDLEINFO *pPrev;
  struct _SAHANDLEINFO *pNext;
  SAFEARRAYHOLDER *pHolder;
  int isClaimed;
  long handle;
} SAHANDLEINFO;

static jboolean LocalSafeArrayInit(JNIEnv *env, jclass pSafeArrayClass);
static SAHANDLEINFO *getSAHandleInfoForJavaSafeArray(JNIEnv *env,
    jobject pJavaSafeArray);
static SAFEARRAYHOLDER *getNativeSafeArrayForJavaSafeArray(JNIEnv *env,
    jobject pJavaSafeArray);
static long getHandleFromJavaSafeArray(JNIEnv *env, jobject pJavaSafeArray);
static SAHANDLEINFO *getSafeArrayHandleInfo(JNIEnv *env, int handle);
static SAFEARRAYHOLDER *getSafeArrayHolderByHandle(JNIEnv *env, int handle);
static long allocSafeArrayHolder(JNIEnv *env, SAFEARRAY *pSA, int arrayType,
    int isClaimed, int oursToDelete);
static void freeSafeArrayHandleInfo(SAHANDLEINFO *pSAHolder);
static int setUpStaticDataIfNeeded(JNIEnv *env);
static SAFEARRAY *lockSafeArrayGetStartIndexAndUBound(JNIEnv *env,
    jobject pJavaSafeArray, jintArray pJAIndexes, jint nElements,
    int *pStartIndex, int *pUBound, int *pArrayType);
static SAFEARRAYHOLDER *getSafeArrayHolderAndLockSafeArray(JNIEnv *env,
    jobject pJavaSafeArray);
static int getStartIndexAndUBound(JNIEnv *env, SAFEARRAYHOLDER *pSAHolder,
    jintArray pJAIndexes, int n, int *pUBound);
static int getStartIndex(JNIEnv *env, SAFEARRAY *pSA, int totalElements,
                         jintArray pJAIndexes);
static void putElementsAndUnlockSafeArray(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound, int arrayType);
static jobject getJavaArrayFromSafeArrayAndUnlock(JNIEnv *env, SAFEARRAY *pSA,
    int startIndex, int uBound, int arrayType);
static void putIntElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getIntArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putShortElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getShortArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putFloatElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getFloatArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putDoubleElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getDoubleArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putDateElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getDateArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putStringElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getStringArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putBooleanElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getBooleanArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putVariantElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getVariantArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);
static void putByteElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound);
static jobject getByteArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound);

static jclass gpJavaSafeArrayClass = (jclass) NULL;
static jmethodID gGetHandleMethodID = (jmethodID) NULL;
static jclass gpShortSAClass = (jclass) NULL;
static jmethodID gShortSAConstructorID = (jmethodID) NULL;
static jclass gpIntSAClass = (jclass) NULL;
static jmethodID gIntSAConstructorID = (jmethodID) NULL;
static jclass gpFloatSAClass = (jclass) NULL;
static jmethodID gFloatSAConstructorID = (jmethodID) NULL;
static jclass gpDoubleSAClass = (jclass) NULL;
static jmethodID gDoubleSAConstructorID = (jmethodID) NULL;
static jclass gpDateSAClass = (jclass) NULL;
static jmethodID gDateSAConstructorID = (jmethodID) NULL;
static jclass gpStringSAClass = (jclass) NULL;
static jmethodID gStringSAConstructorID = (jmethodID) NULL;
static jclass gpBooleanSAClass = (jclass) NULL;
static jmethodID gBooleanSAConstructorID = (jmethodID) NULL;
static jclass gpVariantSAClass = (jclass) NULL;
static jmethodID gVariantSAConstructorID = (jmethodID) NULL;
static jclass gpByteSAClass = (jclass) NULL;
static jmethodID gByteSAConstructorID = (jmethodID) NULL;

static int gInitDone = FALSE;

static SAHANDLEINFO *gpHandleList = NULL;

static int InitSafeArrayAPI(JNIEnv *env) {
  jclass pTempSafeArrayClass = NULL;
   
  if (gInitDone)
    return TRUE;

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/SafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for SafeArray");
    return FALSE;
  }

  gpJavaSafeArrayClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpJavaSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gGetHandleMethodID = (*env)->GetMethodID(env, gpJavaSafeArrayClass,
                       "getHandle", "()I");
  if (gGetHandleMethodID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get method ID for getHandle");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/ShortSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for ShortSafeArray");
    return FALSE;
  }

  gpShortSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpShortSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gShortSAConstructorID = (*env)->GetMethodID(env, gpShortSAClass,
                             "<init>", "(IB)V");
  if (gShortSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for ShortSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/IntSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for IntSafeArray");
    return FALSE;
  }

  gpIntSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpIntSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gIntSAConstructorID = (*env)->GetMethodID(env, gpIntSAClass,
                             "<init>", "(IB)V");
  if (gIntSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for IntSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/FloatSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for FloatSafeArray");
    return FALSE;
  }

  gpFloatSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpFloatSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gFloatSAConstructorID = (*env)->GetMethodID(env, gpFloatSAClass,
                             "<init>", "(IB)V");
  if (gFloatSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for FloatSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/DoubleSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for DoubleSafeArray");
    return FALSE;
  }

  gpDoubleSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpDoubleSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gDoubleSAConstructorID = (*env)->GetMethodID(env, gpDoubleSAClass,
                             "<init>", "(IB)V");
  if (gDoubleSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for DoubleSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/DateSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for DateSafeArray");
    return FALSE;
  }

  gpDateSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpDateSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gDateSAConstructorID = (*env)->GetMethodID(env, gpDateSAClass,
                             "<init>", "(IB)V");
  if (gDateSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for DateSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/StringSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for StringSafeArray");
    return FALSE;
  }

  gpStringSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpStringSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class StringSafeArray");
    return FALSE;
  }
    
  gStringSAConstructorID = (*env)->GetMethodID(env, gpStringSAClass,
                             "<init>", "(IB)V");
  if (gStringSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for StringSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/BooleanSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for BooleanSafeArray");
    return FALSE;
  }

  gpBooleanSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpBooleanSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gBooleanSAConstructorID = (*env)->GetMethodID(env, gpBooleanSAClass,
                             "<init>", "(IB)V");
  if (gBooleanSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for BooleanSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/VariantSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for VariantSafeArray");
    return FALSE;
  }

  gpVariantSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpVariantSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gVariantSAConstructorID = (*env)->GetMethodID(env, gpVariantSAClass,
                             "<init>", "(IB)V");
  if (gVariantSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for VariantSafeArray");
    return FALSE;
  }

  pTempSafeArrayClass = (*env)->FindClass(env, "com/gensym/com/ByteSafeArray");
  if (pTempSafeArrayClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get class for ByteSafeArray");
    return FALSE;
  }

  gpByteSAClass = (*env)->NewGlobalRef(env, pTempSafeArrayClass);
  if (gpByteSAClass == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get global ref for class SafeArray");
    return FALSE;
  }
    
  gByteSAConstructorID = (*env)->GetMethodID(env, gpByteSAClass,
                             "<init>", "(IB)V");
  if (gByteSAConstructorID == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not get constructor ID for ByteSafeArray");
    return FALSE;
  }

  gInitDone = TRUE;
  return TRUE;
}

JNIEXPORT jint JNICALL Java_com_gensym_com_SafeArray_create
    (JNIEnv *env, jobject pJavaSafeArray, jshort arrayType,
    jintArray pJALBounds, jintArray pJAUBounds) {
  int nBounds = 0;
  jint *pLBounds = NULL;
  jint *pUBounds = NULL;
  int i = 0;
  SAFEARRAYBOUND *pBounds = NULL;
  SAFEARRAY *pSA = NULL;
  long holderHandle = 0;

  if (!InitSafeArrayAPI(env))
    return 0;

  nBounds = (int)(*env)->GetArrayLength(env, pJALBounds);
  if (nBounds == 0) {
    jprintf(env, DERROR,
      "Error: could not get number of bounds");
    return 0;
  }

  pLBounds = (*env)->GetIntArrayElements(env, pJALBounds, 0);
  if (pLBounds == NULL) {
    jprintf(env, DERROR,
      "Error: could not get lower array bounds");
    return 0;
  }

  pUBounds = (*env)->GetIntArrayElements(env, pJAUBounds, 0);
  if (pLBounds == NULL) {
    jprintf(env, DERROR,
      "Error: could not get upper array bounds");
    (*env)->ReleaseIntArrayElements(env, pJALBounds, pLBounds, 0);
    return 0;
  }

  pBounds = malloc(sizeof (SAFEARRAYBOUND) * nBounds);
  if (pBounds == NULL) {
    jprintf(env, DERROR,
      "Error: could alloc safe array bounds");
    (*env)->ReleaseIntArrayElements(env, pJALBounds, pLBounds, 0);
    (*env)->ReleaseIntArrayElements(env, pJAUBounds, pUBounds, 0);
    return 0;
  }

  for (i = 0; i < nBounds; i++) {
    pBounds[i].cElements = (unsigned long)(pUBounds[i] - pLBounds[i] + 1);
    pBounds[i].lLbound = (long)pLBounds[i];
  }

  /* we do not need the java ints any more */
  (*env)->ReleaseIntArrayElements(env, pJALBounds, pLBounds, 0);
  (*env)->ReleaseIntArrayElements(env, pJAUBounds, pUBounds, 0);

  pSA = SafeArrayCreate((VARTYPE)arrayType, (UINT)nBounds, pBounds);

  /* we do not need the bounds any more, SafeArrayCreate makes a copy. */
  free(pBounds);
  if (pSA == NULL) {
    jprintf(env, DERROR,
      "Error: could alloc safe array");
    return 0;
  }


  /* Since we are returning this handle to a SafeArray constructor
     claim the holder now. */
  holderHandle = allocSafeArrayHolder(env, pSA, arrayType, CLAIM_NOW,
                                      OK_TO_DELETE);
  if (holderHandle == 0) {
    SafeArrayDestroy(pSA);
    return 0;
  }

  return (jint)holderHandle;
}

JNIEXPORT jboolean JNICALL Java_com_gensym_com_SafeArray_claimHandle
    (JNIEnv *env, jclass pSafeArrayClass, jint handle) {
  SAHANDLEINFO *pSAHandleInfo = NULL;

  pSAHandleInfo = getSafeArrayHandleInfo(env, handle);
  if (pSAHandleInfo == NULL || pSAHandleInfo->isClaimed)
    return JNI_FALSE;

  pSAHandleInfo->isClaimed = CLAIM_NOW;

  return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_gensym_com_SafeArray_isOwner
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return JNI_FALSE;

  if (pSAHolder->oursToDelete)
    return JNI_TRUE;

  return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_com_gensym_com_SafeArray_isValid
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return JNI_FALSE;

  /* Lock the elements of the array. */
  if (FAILED(SafeArrayLock(pSAHolder->pSA))) {
    jprintf(env, DERROR, "Error: could not lock safe array to test validity.");
    return JNI_FALSE;
  }

  SafeArrayUnlock(pSAHolder->pSA);

  return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_com_gensym_com_SafeArray_isSameNativeArray
    (JNIEnv *env, jobject pJavaSafeArray, jobject pJavaSafeArrayComp) {
  SAFEARRAYHOLDER *pSAHolder = NULL;
  SAFEARRAYHOLDER *pSAHolderComp = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return JNI_FALSE;

  pSAHolderComp = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArrayComp);
  if (pSAHolderComp == NULL)
    return JNI_FALSE;

  if (pSAHolder->pSA != pSAHolderComp->pSA)
    return JNI_FALSE;

  return JNI_TRUE;
}

JNIEXPORT jint JNICALL Java_com_gensym_com_SafeArray_copy
    (JNIEnv *env, jobject pJavaSafeArray){
  SAFEARRAYHOLDER *pSAHolder = NULL;
  long holderHandle = 0;
  SAFEARRAY *pNewArray = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return 0;

  if (SafeArrayCopy(pSAHolder->pSA, &pNewArray) != S_OK)
    return 0;

  /* Since we are returning this handle to a SafeArray constructor
     claim the holder now. */
  holderHandle = allocSafeArrayHolder(env, pNewArray, pSAHolder->arrayType,
                 CLAIM_NOW, OK_TO_DELETE);
  if (holderHandle == 0) {
    SafeArrayDestroy(pNewArray);
    return 0;
  }

  return (jint)holderHandle;
}

JNIEXPORT void JNICALL Java_com_gensym_com_SafeArray_nativeFinalize
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAHANDLEINFO *pSAHandleInfo = NULL;

  pSAHandleInfo = getSAHandleInfoForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHandleInfo == NULL)
    return;

  /* since were are called in the finalizer, if we can't destroy the
     safe array, we must still free the holder */
  pSAHandleInfo->pHolder->refCount--;
  if (pSAHandleInfo->pHolder->refCount == 0) {
    if (pSAHandleInfo->pHolder->oursToDelete)
      SafeArrayDestroy(pSAHandleInfo->pHolder->pSA);

    free(pSAHandleInfo->pHolder);
  }

  freeSafeArrayHandleInfo(pSAHandleInfo);
}

JNIEXPORT jboolean JNICALL Java_com_gensym_com_SafeArray_destroy
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAHANDLEINFO *pSAHandleInfo = NULL;

  pSAHandleInfo = getSAHandleInfoForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHandleInfo == NULL)
    return JNI_TRUE;

  if (pSAHandleInfo->pHolder->refCount == 1) {
    /* if the safe array is locked do not destroy the holder */
    if (SafeArrayDestroy(pSAHandleInfo->pHolder->pSA) == DISP_E_ARRAYISLOCKED)
      return JNI_FALSE;

    pSAHandleInfo->pHolder->refCount--;
    free(pSAHandleInfo->pHolder);
  }

  freeSafeArrayHandleInfo(pSAHandleInfo);

  return JNI_TRUE;
}

JNIEXPORT jint JNICALL Java_com_gensym_com_SafeArray_getDimensions
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return 0;

  return (jint)SafeArrayGetDim(pSAHolder->pSA);
}

JNIEXPORT jint JNICALL Java_com_gensym_com_SafeArray_getLBound
(JNIEnv *env, jobject pJavaSafeArray, jint dimension) {
  SAFEARRAYHOLDER *pSAHolder = NULL;
  long lBound = 0;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return 0;

  SafeArrayGetLBound(pSAHolder->pSA, (UINT)dimension, &lBound);
  return (jint)lBound;
}

JNIEXPORT jint JNICALL Java_com_gensym_com_SafeArray_getUBound
    (JNIEnv *env, jobject pJavaSafeArray, jint dimension) {
  SAFEARRAYHOLDER *pSAHolder = NULL;
  long uBound = 0;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return 0;

  SafeArrayGetUBound(pSAHolder->pSA, (UINT)dimension, &uBound);
  return (jint)uBound;
}

JNIEXPORT void JNICALL Java_com_gensym_com_SafeArray_putElements
    (JNIEnv *env, jobject pJavaSafeArray, jintArray pJAIndexes,
    jobject pJavaElements) {
  int nElements = 0;
  SAFEARRAY *pSA = NULL;
  int startIndex = 0;
  int uBound = 0;
  int arrayType = 0;

  nElements = (int)(*env)->GetArrayLength(env, pJavaElements);
  if (nElements == 0) {
    jprintf(env, DERROR,
      "Error: could not get number of new elements");
    return;
  }

  pSA = lockSafeArrayGetStartIndexAndUBound(env, pJavaSafeArray,
          pJAIndexes, nElements, &startIndex, &uBound, &arrayType);
  if (pSA == NULL)
    return;

  putElementsAndUnlockSafeArray(env, pSA, pJavaElements, startIndex,
    uBound, arrayType);
}

JNIEXPORT jobject JNICALL Java_com_gensym_com_SafeArray_getElements
    (JNIEnv *env, jobject pJavaSafeArray, jintArray pJAIndexes,
    jint nElements) {
  SAFEARRAY *pSA = NULL;
  int startIndex = 0;
  int uBound = 0;
  int arrayType = 0;
  jobject pJavaArray = NULL;

  pSA = lockSafeArrayGetStartIndexAndUBound(env, pJavaSafeArray,
        pJAIndexes, (int)nElements, &startIndex, &uBound, &arrayType);
  if (pSA == NULL)
    return NULL;

  return getJavaArrayFromSafeArrayAndUnlock(env, pSA, startIndex,
    uBound, arrayType);
}

JNIEXPORT jobject JNICALL Java_com_gensym_com_SafeArray_getAllElements
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getSafeArrayHolderAndLockSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return NULL;

  return getJavaArrayFromSafeArrayAndUnlock(env, pSAHolder->pSA, 0,
    pSAHolder->totalElements - 1, pSAHolder->arrayType);
}

JNIEXPORT void JNICALL Java_com_gensym_com_SafeArray_lock
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return;

  SafeArrayLock(pSAHolder->pSA);
}

JNIEXPORT void JNICALL Java_com_gensym_com_SafeArray_unlock
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return;

  SafeArrayUnlock(pSAHolder->pSA);
}

JNIEXPORT void JNICALL Java_com_gensym_com_SafeArray_takeOwnership
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return;

  pSAHolder->oursToDelete = TRUE;
}

JNIEXPORT void JNICALL Java_com_gensym_com_SafeArray_giveUpOwnership
    (JNIEnv *env, jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return;

  pSAHolder->oursToDelete = FALSE;
}

static SAFEARRAYHOLDER *getNativeSafeArrayForJavaSafeArray(JNIEnv *env,
    jobject pJavaSafeArray) {
  SAHANDLEINFO *pSAHandleInfo = NULL;

  pSAHandleInfo = getSAHandleInfoForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHandleInfo == NULL)
    return NULL;

  return pSAHandleInfo->pHolder;
}
       
static long getHandleFromJavaSafeArray(JNIEnv *env, jobject pJavaSafeArray) {
  if (!gInitDone)
    return 0;

  if (pJavaSafeArray == NULL)
    return 0;

  return (long)(*env)->CallIntMethod(env, pJavaSafeArray, gGetHandleMethodID);
}

static SAFEARRAYHOLDER *getSafeArrayHolder(JNIEnv *env, SAFEARRAY *pSA) {
  SAHANDLEINFO *pCurrentHandleInfo = NULL;

  if (pSA == NULL)
    return NULL;

  pCurrentHandleInfo = gpHandleList;
  for (; pCurrentHandleInfo != NULL; pCurrentHandleInfo = pCurrentHandleInfo->pNext) {
    if (pCurrentHandleInfo->pHolder->pSA == pSA)
      return pCurrentHandleInfo->pHolder;
  }

  return NULL;
}

static SAHANDLEINFO *getSAHandleInfoForJavaSafeArray(JNIEnv *env,
    jobject pJavaSafeArray) {
  long arrayHandle;

  arrayHandle = getHandleFromJavaSafeArray(env, pJavaSafeArray);
  return getSafeArrayHandleInfo(env, arrayHandle);
}
       
static SAHANDLEINFO *getSafeArrayHandleInfo(JNIEnv *env, int handle) {
  SAHANDLEINFO *pCurrentHandleInfo = NULL;

  if (handle == 0)
    return NULL;

  pCurrentHandleInfo = gpHandleList;
  for (; pCurrentHandleInfo != NULL; pCurrentHandleInfo = pCurrentHandleInfo->pNext) {
    if (pCurrentHandleInfo->handle == handle)
      return pCurrentHandleInfo;
  }

  jprintf(env, DERROR,
      "Error: could not find safe array handle");
  return NULL;
}

static long allocSafeArrayHolder(JNIEnv *env, SAFEARRAY *pSA,
    int arrayType, int isClaimed, int oursToDelete) {
  SAHANDLEINFO *pSAHandleInfo = NULL;
  SAFEARRAYHOLDER *pSAHolder = NULL;
  int i;

  pSAHandleInfo = malloc(sizeof (SAHANDLEINFO));
  if (pSAHandleInfo == NULL) {
    jprintf(env, DERROR,
      "Error: could alloc safe handle info");
    return 0;
  }

  /* Search the other handles before we add this one. */
  pSAHolder = getSafeArrayHolder(env, pSA);

  pSAHandleInfo->handle = (long)pSAHandleInfo;

  /* Add this handle to the list of handles */
  pSAHandleInfo->pPrev = NULL;
  pSAHandleInfo->pNext = gpHandleList;
  gpHandleList = pSAHandleInfo;

  /* special case if the list is empty */
  if (pSAHandleInfo->pNext != NULL)
    pSAHandleInfo->pNext->pPrev = pSAHandleInfo;

  pSAHandleInfo->isClaimed = isClaimed;

  if (pSAHolder != NULL) {
    /* We already have a holder to this safe array just up the ref count. */
    pSAHolder->refCount++;
    pSAHandleInfo->pHolder = pSAHolder;
    return pSAHandleInfo->handle;
  }

  /* we need a new holder for this safe array */
  pSAHolder = malloc(sizeof (SAFEARRAYHOLDER));
  if (pSAHolder == NULL) {
    free(pSAHandleInfo);
    jprintf(env, DERROR,
      "Error: could alloc safe array holder");
    return 0;
  }

  pSAHolder->pSA = pSA;
  pSAHolder->arrayType = arrayType;
  pSAHolder->totalElements = 0;
  pSAHolder->refCount = 1;
  pSAHolder->oursToDelete = oursToDelete;
  pSAHolder->totalElements = pSA->rgsabound[0].cElements;
  for (i = 1; i < pSA->cDims; i++) {
    (pSAHolder->totalElements) *= pSA->rgsabound[i].cElements;
  }

  pSAHandleInfo->pHolder = pSAHolder;
  return pSAHandleInfo->handle;
}

static void freeSafeArrayHandleInfo(SAHANDLEINFO *pSAHandleInfo) {
  /* special case if at the beginning of the list */
  if (pSAHandleInfo->pPrev == NULL)
    gpHandleList = pSAHandleInfo->pNext;
  else
    pSAHandleInfo->pPrev->pNext = pSAHandleInfo->pNext;

  /* special case if at the end of the list */
  if (pSAHandleInfo->pNext != NULL)
    pSAHandleInfo->pNext->pPrev = pSAHandleInfo->pPrev;

  free(pSAHandleInfo);
}

static SAFEARRAY *lockSafeArrayGetStartIndexAndUBound(JNIEnv *env,
    jobject pJavaSafeArray, jintArray pJAIndexes, jint n,
    int *pStartIndex, int *pUBound, int *pArrayType) {
  SAFEARRAYHOLDER *pSAHolder = NULL;

  pSAHolder = getSafeArrayHolderAndLockSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return NULL;

  *pStartIndex = getStartIndexAndUBound(env, pSAHolder, pJAIndexes, (int)n,
                  pUBound);
  if (*pStartIndex < 0) {
    SafeArrayUnlock(pSAHolder->pSA);
    return NULL;
  }

  *pArrayType = pSAHolder->arrayType;
  return pSAHolder->pSA;
}

static SAFEARRAYHOLDER *getSafeArrayHolderAndLockSafeArray(JNIEnv *env,
    jobject pJavaSafeArray) {
  SAFEARRAYHOLDER *pSAHolder = NULL;
  void *pData = NULL;  

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pJavaSafeArray);
  if (pSAHolder == NULL)
    return NULL;

  /* Lock the elements of the array. */
  if (FAILED(SafeArrayLock(pSAHolder->pSA))) {
    jprintf(env, DERROR, "Error: could not lock safe array");
    return NULL;
  }

  return pSAHolder;
}

static int getStartIndexAndUBound(JNIEnv *env, SAFEARRAYHOLDER *pSAHolder,
    jintArray pJAIndexes, int n, int *pUBound) {
  int startIndex = 0;

  startIndex = getStartIndex(env, pSAHolder->pSA, pSAHolder->totalElements,
                 pJAIndexes);
  if (startIndex < 0)
    return -1;

  *pUBound = startIndex + n - 1;
  if (*pUBound >= pSAHolder->totalElements) {
    jprintf(env, DERROR,
      "Error: array out of bounds");
    return -1;
  }

  return startIndex;
}

static int getStartIndex(JNIEnv *env, SAFEARRAY *pSA, int totalElements,
                         jintArray pJAIndexes) {
  unsigned short numberOfIndexes = 0;
  jint *pIndexes = NULL;
  int i = 0;
  int startIndex = 0;
  int bound = 0;
  int dimMultiplier = 1;

  /* The number of indexes must less than or equal to the number of
     dimensions */
  numberOfIndexes = (unsigned short)(*env)->GetArrayLength(env, pJAIndexes);
  if (numberOfIndexes > pSA->cDims) {
    jprintf(env, DERROR, "Error: too many indexes");
    return -1;
  }

  pIndexes = (*env)->GetIntArrayElements(env, pJAIndexes, 0);
  if (pIndexes == NULL) {
    jprintf(env, DERROR, "Error: could not get indexes");
    return -1;
  }

  /* Since we will access the array as a flat array, we need to find
     out what the start index is.
     SafeArrays are in stored in column-major order, which is
     the same ordering scheme used by Visual Basic and FORTRAN,
     but different from C and Pascal. Column-major order is when
     the left-most dimension changes first. But the bounds structures
     are stored in the safe array structure with the right most dimension
     at zero, this contrary to the ActiveX reference doc which say the the
     bounds array starts with the left most dimension first, but the order
     of bounds was varified by looking at a 3 dimensional safe array created
     by Visual Basic 6.0 and passed to an ActiveX test control in the VC++
     debugger. */
  for (i = 0; i < numberOfIndexes; i++) {
    bound = pSA->cDims - i - 1;
    startIndex += (pIndexes[i] - pSA->rgsabound[bound].lLbound) * dimMultiplier;
    dimMultiplier *= pSA->rgsabound[bound].cElements;
  }

  (*env)->ReleaseIntArrayElements(env, pJAIndexes, pIndexes, 0);
  
  if (startIndex < 0 || startIndex >= totalElements) {
    jprintf(env, DERROR,
      "Error: invalid indexes were received");
    return -1;
  }
 
  return startIndex;
}

static void putElementsAndUnlockSafeArray(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound, int arrayType) {
  switch (arrayType) {
  case VT_I2:
    putShortElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_I4:
    putIntElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_R4:
    putFloatElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_R8:
    putDoubleElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_DATE:
    putDateElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_BSTR:
    putStringElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_BOOL:
    putBooleanElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_VARIANT:
    putVariantElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  case VT_UI1:
    putByteElements(env, pSA, pJavaElements, startIndex, uBound);
    break;

  default:
    jprintf(env, DERROR, "Error: unsupported arrayType");
  }

  SafeArrayUnlock(pSA);
}

static jobject getJavaArrayFromSafeArrayAndUnlock(JNIEnv *env, SAFEARRAY *pSA,
    int startIndex, int uBound, int arrayType) {
  jobject pJavaArray = NULL;

  switch (arrayType) {
  case VT_I2:
    pJavaArray = getShortArray(env, pSA, startIndex, uBound);
    break;

  case VT_I4:
    pJavaArray = getIntArray(env, pSA, startIndex, uBound);
    break;

  case VT_R4:
    pJavaArray = getFloatArray(env, pSA, startIndex, uBound);
    break;

  case VT_R8:
    pJavaArray = getDoubleArray(env, pSA, startIndex, uBound);
    break;

  case VT_DATE:
    pJavaArray = getDateArray(env, pSA, startIndex, uBound);
    break;

  case VT_BSTR:
    pJavaArray = getStringArray(env, pSA, startIndex, uBound);
    break;

  case VT_BOOL:
    pJavaArray = getBooleanArray(env, pSA, startIndex, uBound);
    break;

  case VT_VARIANT:
    pJavaArray = getVariantArray(env, pSA, startIndex, uBound);
    break;

  case VT_UI1:
    pJavaArray = getByteArray(env, pSA, startIndex, uBound);
    break;

  default:
    jprintf(env, DERROR, "Error: unsupported arrayType");
  }

  SafeArrayUnlock(pSA);
  return pJavaArray;
}

static void putShortElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  short *pNativeElements = NULL;

  pNativeElements = (short*)pSA->pvData;
  (*env)->GetShortArrayRegion(env, pJavaElements, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
}

static jobject getShortArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jshortArray pJavaArray = NULL;
  short *pNativeElements = NULL;

  pJavaArray = (*env)->NewShortArray(env, (jsize)(uBound - startIndex + 1));
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (short*)pSA->pvData;
  (*env)->SetShortArrayRegion(env, pJavaArray, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
  return (jobject)pJavaArray;
}

static void putIntElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  long *pNativeElements = NULL;

  pNativeElements = (long*)pSA->pvData;
  (*env)->GetIntArrayRegion(env, pJavaElements, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
}

static jobject getIntArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jintArray pJavaArray = NULL;
  long *pNativeElements = NULL;

  pJavaArray = (*env)->NewIntArray(env, (jsize)(uBound - startIndex + 1));
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (long*)pSA->pvData;
  (*env)->SetIntArrayRegion(env, pJavaArray, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
  return (jobject)pJavaArray;
}

static void putFloatElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  float *pNativeElements = NULL;

  pNativeElements = (float*)pSA->pvData;
  (*env)->GetFloatArrayRegion(env, pJavaElements, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
}

static jobject getFloatArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jfloatArray pJavaArray = NULL;
  float *pNativeElements = NULL;

  pJavaArray = (*env)->NewFloatArray(env, (jsize)(uBound - startIndex + 1));
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (float*)pSA->pvData;
  (*env)->SetFloatArrayRegion(env, pJavaArray, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
  return (jobject)pJavaArray;
}

static void putDoubleElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  double *pNativeElements = NULL;

  pNativeElements = (double*)pSA->pvData;
  (*env)->GetDoubleArrayRegion(env, pJavaElements, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
}

static jobject getDoubleArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jdoubleArray pJavaArray = NULL;
  double *pNativeElements = NULL;

  pJavaArray = (*env)->NewDoubleArray(env, (jsize)(uBound - startIndex + 1));
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (double*)pSA->pvData;
  (*env)->SetDoubleArrayRegion(env, pJavaArray, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
  return (jobject)pJavaArray;
}

static void putDateElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  DATE *pNativeElements = NULL;
  jobject jDate = NULL;
  int i = 0;

  pNativeElements = (DATE*)pSA->pvData;
  for (i = 0; i <= uBound - startIndex; i++) {
    pNativeElements[startIndex + i] = DATE_from_jdate(env,
      (*env)->GetObjectArrayElement(env, pJavaElements, i));
  }
}

static jobject getDateArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jobjectArray pJavaArray = NULL;
  DATE *pNativeElements = NULL;
  int i = 0;

  pJavaArray = create_jdate_array(env, uBound - startIndex + 1);
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (DATE*)pSA->pvData;
  for (i = 0; i <= uBound - startIndex; i++) {
    (*env)->SetObjectArrayElement(env, pJavaArray, i,
      jdate_from_DATE(env, pNativeElements[startIndex + i]));
  }

  return (jobject)pJavaArray;
}

static void putStringElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  BSTR *pNativeElements = NULL;
  jobject jDate = NULL;
  int i = 0;

  pNativeElements = (BSTR*)pSA->pvData;
  for (i = 0; i <= uBound - startIndex; i++) {
    if (pNativeElements[startIndex + i] != NULL)
      SysFreeString(pNativeElements[startIndex + i]);

    pNativeElements[startIndex + i] = java_to_BSTR(env,
        (*env)->GetObjectArrayElement(env, pJavaElements, i));
  }
}

static jobject getStringArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jobjectArray pJavaArray = NULL;
  BSTR *pNativeElements = NULL;
  int i = 0;

  pJavaArray = create_jstring_array(env, uBound - startIndex + 1);
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (BSTR*)pSA->pvData;
  for (i = 0; i <= uBound - startIndex; i++) {
    (*env)->SetObjectArrayElement(env, pJavaArray, i,
      BSTR_to_jstring(env, pNativeElements[startIndex + i]));
  }

  return (jobject)pJavaArray;
}

static void putBooleanElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  short *pNativeElements = NULL;
  int i = 0;
  jboolean tempBool = 0;

  pNativeElements = (short*)pSA->pvData;
  for (i = 0 ; i <= uBound - startIndex; i++) {
    (*env)->GetBooleanArrayRegion(env, pJavaElements, i, 1,
      &tempBool);
    if (tempBool)
      pNativeElements[startIndex + i] = VARIANT_TRUE;
    else
      pNativeElements[startIndex + i] = VARIANT_FALSE;
  }
}

static jobject getBooleanArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jbooleanArray pJavaArray = NULL;
  short *pNativeElements = NULL;
  int i = 0;
  jboolean tempBool = 0;
  

  pJavaArray = (*env)->NewBooleanArray(env, (jsize)(uBound - startIndex + 1));
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (short*)pSA->pvData;
  for (i = 0 ; i <= uBound - startIndex; i++) {
    if (pNativeElements[startIndex + i])
      tempBool = JNI_TRUE;
    else
      tempBool = JNI_FALSE;

    (*env)->SetBooleanArrayRegion(env, pJavaArray, i, 1,
      &tempBool);
  }

  return (jobject)pJavaArray;
}

static void putVariantElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  VARIANT *pNativeElements = NULL;
  int i = 0;
  VARIANT tempVariant;

  pNativeElements = (VARIANT*)pSA->pvData;
  for (i = 0; i <= uBound - startIndex; i++) {
    VariantClear(&pNativeElements[startIndex + i]);

    init_variant_from_jobject(env,
      (*env)->GetObjectArrayElement(env, pJavaElements, i),
      &tempVariant, NULL, FALSE);

    /* Treat Java safe arrays like strings make a copy for the caller
       to own. */
    if (tempVariant.vt & VT_ARRAY)
      SafeArrayCopy(tempVariant.parray, &tempVariant.parray);

    pNativeElements[startIndex + i] = tempVariant;
  }
}

static jobject getVariantArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jobjectArray pJavaArray = NULL;
  VARIANT *pNativeElements = NULL;
  int i = 0;
  VARIANT tempVariant;

  pJavaArray = create_jvariant_array(env, uBound - startIndex + 1);
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (VARIANT*)pSA->pvData;
  for (i = 0; i <= uBound - startIndex; i++) {
    tempVariant = pNativeElements[startIndex + i];

    /* Treat Java safe arrays like strings make a copy for the variant
       safe array to own. */
    if (tempVariant.vt & VT_ARRAY)
      SafeArrayCopy(tempVariant.parray, &tempVariant.parray);

    (*env)->SetObjectArrayElement(env, pJavaArray, i,
      make_jobject_from_variant(env, tempVariant, NULL,
      FALSE));
  }

  return (jobject)pJavaArray;
}

static void putByteElements(JNIEnv *env, SAFEARRAY *pSA,
    jobject pJavaElements, int startIndex, int uBound) {
  signed char *pNativeElements = NULL;

  pNativeElements = (signed char*)pSA->pvData;
  (*env)->GetByteArrayRegion(env, pJavaElements, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
}

static jobject getByteArray(JNIEnv *env, SAFEARRAY *pSA, int startIndex,
    int uBound) {
  jbyteArray pJavaArray = NULL;
  signed char *pNativeElements = NULL;

  pJavaArray = (*env)->NewByteArray(env, (jsize)(uBound - startIndex + 1));
  if (pJavaArray == NULL) {
    SafeArrayUnlock(pSA);
    jprintf(env, DERROR, "Error: could not create new java array");
    return NULL;
  }

  pNativeElements = (signed char*)pSA->pvData;
  (*env)->SetByteArrayRegion(env, pJavaArray, 0, uBound - startIndex + 1,
    &pNativeElements[startIndex]);
  return (jobject)pJavaArray;
}

SAFEARRAY *NativeSAFromJavaSA(JNIEnv *env, jobject pSafeArray, int newOwner) {
  SAFEARRAYHOLDER* pSAHolder = NULL;

  pSAHolder = getNativeSafeArrayForJavaSafeArray(env, pSafeArray);
  if (pSAHolder == NULL)
    return NULL;

  /* If there is going to be a new owner of the array then we can own it any
     more. */
  if (newOwner)
    pSAHolder->oursToDelete = NOT_OUR_ARRAY;

  return pSAHolder->pSA;
}

jobject CreateShortSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpShortSAClass, gShortSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_I2, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateIntSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpIntSAClass, gIntSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_I4, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateFloatSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpFloatSAClass, gFloatSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_R4, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateDoubleSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpDoubleSAClass, gDoubleSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_R8, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateDateSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpDateSAClass, gDateSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_DATE, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateStringSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpStringSAClass, gStringSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_BSTR, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateBooleanSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpBooleanSAClass, gBooleanSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_BOOL, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateVariantSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpVariantSAClass, gVariantSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_VARIANT, NOT_CLAIMED, ownedByDLL), 0);
}

jobject CreateByteSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL) {
  if (!InitSafeArrayAPI(env))
    return NULL;

  return (*env)->NewObject(env, gpByteSAClass, gByteSAConstructorID,
    allocSafeArrayHolder(env, pSA, VT_UI1, NOT_CLAIMED, ownedByDLL), 0);
}
