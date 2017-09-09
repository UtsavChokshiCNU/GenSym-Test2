/*****************************************************************************
* autojava.c
*
* Authors: John Valente, Allan Scott
*  
*****************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "shared.h"
#include "dprintf.h"


#ifdef WIN32


#define ERRSTRM stdout
#define NOASSERT

#if !defined( _DBGTRACE)
#define _DEBUGLEVEL 2
#else
#define _DEBUGLEVEL _DBGTRACE
#endif

#define NO_CLIENT_SITE 0  /* Needs to be synchronized with ActiveXProxy.java */

#define IS_IDENTIFIER_CHAR(c) (((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z'))||((c>='0')&&(c<='9'))||(c=='_'))

static HWND ghwndMain = NULL;

static short __iDebugLevel = 1;

static char *gszAppName;

static jclass guid_class = NULL;
static jmethodID guid_constructor = NULL;

static jclass axmodes_class = NULL;
static jmethodID axmodes_constructor = NULL;

static jclass nativeMethodBroker_class = NULL;
static jmethodID traceln_method = NULL;

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
void cdecl dprintf (short messagePriority, LPSTR lpFormat, ...) 
{
  /* Now just a stub function inside of JavaContainer */
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Should endeavor to call this only once, but since it performs
 *     non-null checks, it will be pretty quick to run.
 *     -----
 *   Modifications:
 *****************************************************************************/
static void get_traceln_method(JNIEnv *env)
{
  if (nativeMethodBroker_class == NULL) {
    nativeMethodBroker_class = (*env)->FindClass(env,
                               "com/gensym/com/NativeMethodBroker");
    nativeMethodBroker_class = (*env)->NewGlobalRef(env, nativeMethodBroker_class);
  }
  
  if (nativeMethodBroker_class) {
    if (traceln_method == NULL) {
      traceln_method = (*env)->GetStaticMethodID(env, nativeMethodBroker_class,
                       "traceln", "(ILjava/lang/String;)V");
    }
  }
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
void cdecl jprintf (JNIEnv * env, short messagePriority, LPSTR lpFormat, ...) 
{
    char buf[256];
    va_list args;
    jstring message;
    
    buf[0] = -1;

#ifdef VC_DEBUG
    /* This will allow messages to show up in the VC++ debug window. */
    /*  format the string */
    va_start(args, lpFormat);
    vsprintf(buf, lpFormat, args);
    va_end(args);
    OutputDebugStringA(buf);
    OutputDebugStringA("\n");
#endif

    if (__iDebugLevel >= messagePriority) {
        if (buf[0] == -1) {
            /*  format the string */
            va_start(args, lpFormat);
            vsprintf(buf, lpFormat, args);
            va_end(args);
        }

        if (env == NULL) {
            fprintf(ERRSTRM, "com.gensym.com: c: %s\n", buf);
            fflush(ERRSTRM);
        }
        else {
            get_traceln_method(env);
            if (traceln_method == NULL) {
                fprintf(ERRSTRM, "com.gensym.com: c: %s\n", buf);
                fflush(ERRSTRM);
                return;
            }

            message = c_to_java_string(env, buf);
            (*env)->CallStaticVoidMethod(env, 
                 nativeMethodBroker_class, traceln_method,
                 (jint) messagePriority,
                 message);
        }
    }
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
char * create_error_report(HRESULT hr)
{
  switch (hr)
  {
    case E_ABORT:
        return "Abort";
    case E_FAIL:
      return "Unspecified failure";
    case E_ACCESSDENIED:
      return "Permission to use object denied";
    case E_NOTIMPL:
      return "Unimplemented error returned by object";
    case E_OUTOFMEMORY:
      return "Out of memory";
    case E_INVALIDARG:
      return "One or more arguments are invalid";
    case E_NOINTERFACE:
      return "No such interface supported";
    case E_POINTER:
      return "Invalid pointer";
    case E_HANDLE:
      return "Invalid handle";
    case CO_E_SERVER_EXEC_FAILURE:
      return "Cannot launch server";
    case REGDB_E_CLASSNOTREG:
      return "Component incorrectly registered";
    case CLASS_E_NOTLICENSED:
      return "Component is not licensed";
  default:
    { 
      char *buf = malloc(sizeof(char) * 50);
      buf[0] = 0;
      sprintf(buf, "Unexpected error: 0x%x", hr);
      return buf;
    }
  }
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
short DebugLevel()
{
    return __iDebugLevel;
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
void C_setDebugLevel(JNIEnv * env, short newDebugLevel)
{
    __iDebugLevel = newDebugLevel;
	jprintf(env, PROGRESS, "Setting debug level to %d", newDebugLevel);
}



/*****************************************************************************
 * 
 *
 *   Description: 
 *     Show a message box with assertion failure info in it
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void __AssertMsg(LPSTR exp, LPSTR file, int line)
{
    char buf[256];
    int i;

    sprintf(buf, 
             "Exp: %s\n  File: %s, Line %d",
             (LPSTR)exp,
             (LPSTR)file,
             line);
#ifdef VC_DEBUG
    /* This will allow messages to show up in the VC++ debug window. */
    /*  format the string */
    OutputDebugStringA("ASSERTION FAILED: ");
    OutputDebugStringA(buf);
	OutputDebugStringA("\n");
#endif
    fprintf(ERRSTRM, "ASSERTION FAILED: %s\n", buf);
    fflush(ERRSTRM);
    i = MessageBox(ghwndMain,
                   buf,
                   "Assertion failure", 
                   MB_OK | MB_ICONEXCLAMATION);
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *      Show a message box
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
UINT cdecl AlertBox(LPSTR lpFormat, ...) 
{
    char buf[256];
    va_list args;

    va_start(args, lpFormat);
    vsprintf(buf, lpFormat, args);
	va_end(args);

    /*  MessageBeep(MB_ICONEXCLAMATION); */
    return (UINT) MessageBox(NULL, 
			     buf, 
			     "BeanXporter Alert",
			     MB_OK|MB_ICONEXCLAMATION);
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
void print_iid_info(JNIEnv * env, short debug_level, char *intro_string, 
		    const struct _GUID *iid)
{
    jprintf(env, debug_level, "%s %08x-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
	    intro_string, iid->Data1, iid->Data2, iid->Data3, 
	    iid->Data4[0], iid->Data4[1], iid->Data4[2], iid->Data4[3],
	    iid->Data4[4], iid->Data4[5], iid->Data4[6], iid->Data4[7]);
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
char *unicode_to_ascii(WCHAR *unicode)
{
    char *ascii;
    int len, i;

    /* Return empty string in case of NULL argument */
    if (unicode == NULL) {
        ascii = malloc(sizeof(char));
        ascii[0] = 0;
        return ascii;
    }

    /* include the zero terminator */
    len = wcslen(unicode) + 1;
    ascii = (char *) malloc(len * sizeof(char));

    /* convert the whole string including the zero terminator */
    for (i=0; i<len; i++) {
         ascii[i] = (char) unicode[i];
    }

    return ascii;
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
char *unicode_to_ascii_identifier(WCHAR *unicode)
{
    char *ascii;
    int len, i, j;
    WCHAR c;
    
    len = wcslen(unicode);
    ascii = (char *) malloc((len + 1) * sizeof(char));
    dprintf(DETAIL, "making string of length %d", len);
    
    for (i=0; i<len; i++) {
        c = unicode[i];
        /* if (IS_IDENTIFIER_CHAR(c)) { */
        if (((c>='a')&&(c<='z'))||
            ((c>='A')&&(c<='Z'))||
            ((c>='0')&&(c<='9'))||
            (c=='_')) {
            ascii[j++] = (char) c;
        } else {
            dprintf(DUMP, "nope, %d ain't no identfier char", c);
        }
    }

    ascii[j] = 0;
    
    return ascii;
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
WCHAR *ascii_to_unicode(char *ascii)
{
    WCHAR *unicode;
    int len, i;

    /* include the zero terminator */
    len = strlen(ascii) + 1;
    unicode = (WCHAR *) malloc(len * sizeof(WCHAR));

    /* convert the whole string including the zero terminator */
    for (i=0; i<len; i++)
        unicode[i] = (WCHAR) ascii[i];

    return unicode;
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
char *java_to_c_string(JNIEnv *env, jstring jstr)
{
    int utf_string_length;
    const char* utf_chars;
    char* c_string;
    int i;

    if (env == NULL) {
        jprintf(env, DERROR,
            "Error: could not convert java string to C string because");
        jprintf(env, DERROR, "I don't have a pointer to the VM.");
        return NULL;
    }

    utf_string_length = (int)(*env)->GetStringUTFLength(env, jstr);
    utf_chars = (*env)->GetStringUTFChars(env, jstr, NULL);

    /* utf strings do not have a zero terminator, but C strings do */
    c_string = malloc((utf_string_length + 1) * sizeof(char));

    if (c_string != NULL)
    {
        for (i = 0; i < utf_string_length; i++)
            c_string[i] = (char)utf_chars[i];

        c_string[utf_string_length] = 0;
    }

    (*env)->ReleaseStringUTFChars(env, jstr, utf_chars);

    return c_string;
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
jstring c_to_java_string(JNIEnv *env, char *str)
{
    if (env == NULL) {
        jprintf(env, DERROR,
            "Error: could not convert UTF string to java string because");
        jprintf(env, DERROR, "I don't have a pointer to the VM.");
        return NULL;
    }

    return (*env)->NewStringUTF(env, str);
}


/*****************************************************************************
 * wstring_to_jstring
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
jstring wstring_to_jstring (JNIEnv *env, WCHAR *wstring)
{
    if (env == NULL) {
        jprintf(env, DERROR,
            "Error: could not convert unicode string to java string because");
        jprintf(env, DERROR, "I don't have a pointer to the VM.");
        return NULL;
    }

    if (wstring == NULL)
      return NULL;

    return (*env)->NewString(env, (jchar*)wstring, (jsize)wcslen(wstring));
}



/*****************************************************************************
 * BSTR_to_jstring
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
jstring BSTR_to_jstring (JNIEnv *env, BSTR bstring)
{
    if (env == NULL) {
        jprintf(env, DERROR,
            "Error: could not convert unicode string to java string because");
        jprintf(env, DERROR, "I don't have a pointer to the VM.");
        return NULL;
    }

    if (bstring == NULL)
      return NULL;

    return (*env)->NewString(env, (jchar*)bstring, (jsize)SysStringLen(bstring));
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
WCHAR *java_to_unicode_string(JNIEnv *env, jstring str)
{
    int java_string_length;
    const jchar* java_chars;
    WCHAR* unicode_string;
    int i;

    if (env == NULL) {
        jprintf(env, DERROR,
            "Error: could not convert java string to unicode string because");
        jprintf(env, DERROR, "I don't have a pointer to the VM.");
        return NULL;
    }

    java_string_length = (int)(*env)->GetStringLength(env, str);
    java_chars = (*env)->GetStringChars(env, str, NULL);

    /* java strings do not have a zero terminator, but C unicode strings do */
    unicode_string = malloc((java_string_length + 1) * sizeof(WCHAR));

    if (unicode_string != NULL)
    {
        for (i = 0; i < java_string_length; i++)
            unicode_string[i] = (WCHAR)java_chars[i];

        unicode_string[java_string_length] = 0;
    }

    (*env)->ReleaseStringChars(env, str, java_chars);

    return unicode_string;
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
BSTR java_to_BSTR(JNIEnv *env, jstring str) {
    jsize java_string_length;
    const jchar* java_chars;
    BSTR bstring;

    if (str == NULL)
      return NULL;

    if (env == NULL) {
        jprintf(env, DERROR,
            "Error: could not convert java string to BSTR because");
        jprintf(env, DERROR, "I don't have a pointer to the VM.");
        return NULL;
    }

    java_string_length = (*env)->GetStringLength(env, str);
    java_chars = (*env)->GetStringChars(env, str, NULL);

    bstring = SysAllocStringLen((OLECHAR*)java_chars,
                                (unsigned int)java_string_length);

    (*env)->ReleaseStringChars(env, str, java_chars);

    return bstring;
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
void client_force_redraw(PCOMOBJ pObj)
{
    jclass nativeMethodInterfacePointer = NULL;
    jmethodID mid;
    JNIEnv *env;
    
    env = pObj->env;
    
    if (pObj->pIOleIPObject) 
        return;

    setDirty(TRUE);
    dprintf(PROGRESS, "Calling into java for force redraw");
    
    if (env == NULL) {
        dprintf(DERROR, "Error: could not call Java method because I don't have a ");
        dprintf(DERROR, "pointer to the VM.");
        return;
    }
    
    nativeMethodInterfacePointer = (*env)->FindClass
        (env, "com/gensym/com/NativeMethodBroker");
    if (nativeMethodInterfacePointer == NULL) {
        dprintf(DERROR, "Error: could not call Java method because I don't have a ");
        dprintf(DERROR, "pointer to the nativeMethodInterfacePointer class.\n");
        return;
    }
    
    /* Call redrawObject method of NativeMethodBroker*/
    mid = (*env)->GetStaticMethodID(env, nativeMethodInterfacePointer,
        "redrawObject", "(I)V");
    if (mid == NULL) {
        dprintf(DERROR, "Error: could not obtain method id for redrawObject");
        return;
    }

    (*env)->CallStaticVoidMethod(env, nativeMethodInterfacePointer, mid, (jint) pObj);   
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
HRESULT client_forward_event(PCOMOBJ pObj, 
                          jobject iid,
                          jint dispid,
                          jstring eventName,
                          jobject arguments)
{
  jclass nativeMethodInterfacePointer = NULL;
  jmethodID mid;
  JNIEnv *env;

  setDirty(TRUE);

  env = pObj->env;
  
  if (env == NULL) {
	dprintf(DERROR, "Error: could not call Java method because I don't have a ");
	dprintf(DERROR, "pointer to the VM.");
	return E_FAIL;
  }
    
  jprintf(env, PROGRESS, "Calling into java for event forwarding");

  nativeMethodInterfacePointer = (*env)->FindClass
                                 (env, "com/gensym/com/NativeMethodBroker");
  if (nativeMethodInterfacePointer == NULL) {
	jprintf(env, DERROR, "Error: could not call Java method because I don't have a ");
	jprintf(env, DERROR, "pointer to the nativeMethodInterfacePointer class.\n");
    return E_FAIL;
  }
   
  /* Call redrawObject method of NativeMethodBroker*/
  mid = (*env)->GetStaticMethodID(env, nativeMethodInterfacePointer,
        "forwardActiveXEvent", 
        "(ILcom/gensym/com/Guid;ILjava/lang/String;[Lcom/gensym/com/Variant;)V");
  if (mid == NULL) {
	jprintf(env, DERROR, "Error: could not obtain method id for forwardActiveXEvent");
    return E_FAIL;
  }

  (*env)->CallStaticVoidMethod(env, nativeMethodInterfacePointer, mid,
                                (jint) pObj,
                                iid,
                                dispid,
                                eventName,
                                arguments);
  
  return NOERROR;
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
void client_set_open_in_window(PCOMOBJ pObj, short fShow)
{
    dprintf(PROGRESS, "Setting open in window to %d", fShow);
    /* Maintain active state in iActive flag */
    pObj->sOpenInWindow = fShow;    
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Should endeavor to call this only once, but since it performs
 *     non-null checks, it will be pretty quick to run.
 *     -----
 *   Modifications:
 *****************************************************************************/
static void get_guid_constructor(JNIEnv *env)
{
    if (!guid_class) {
	guid_class = (*env)->FindClass(env, "com/gensym/com/Guid");
	guid_class = (*env)->NewGlobalRef(env, guid_class);
    }

    if (guid_class) {
	if (!guid_constructor) {
	    guid_constructor = (*env)->GetMethodID(env, guid_class,
						   "<init>",
						   "(IIISSSSSSSS)V");
	}
    }
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
jobject create_guid(JNIEnv *env, CLSID *cclsid)
{
  jobject result;

  jprintf(env, PROGRESS, "Calling into java for guid");
  if (cclsid)
    print_iid_info(env, PROGRESS, "cclsid = ", cclsid);

  if (!env) {
    jprintf(env, DERROR, "Error: could not call Java method because I don't have a ");
    jprintf(env, DERROR, "pointer to the VM.");
    return NULL;
  }

  get_guid_constructor(env);
  if (guid_constructor == NULL) {
    jprintf(env, DERROR, "Error: could not call Java method because I don't have a ");
    jprintf(env, DERROR, "pointer to the Guid constructor.\n");
    return NULL;
  }
  result = (*env)->NewObject
    (env, guid_class, guid_constructor,
     cclsid->Data1, cclsid->Data2, cclsid->Data3, 
     cclsid->Data4[0], cclsid->Data4[1], cclsid->Data4[2], cclsid->Data4[3], 
     cclsid->Data4[4], cclsid->Data4[5], cclsid->Data4[6], cclsid->Data4[7]);
 
  return result;
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     Should endeavor to call this only once, but since it performs
 *     non-null checks, it will be pretty quick to run.
 *     -----
 *   Modifications:
 *****************************************************************************/
static void get_axmodes_constructor(JNIEnv *env)
{
  if (!axmodes_class) {
    axmodes_class = (*env)->FindClass(env, "com/gensym/com/ActiveXModes");
    axmodes_class = (*env)->NewGlobalRef(env, axmodes_class);
  }
  
  if (axmodes_class) {
    if (!axmodes_constructor) {
      axmodes_constructor = (*env)->GetMethodID(env, axmodes_class,
						"<init>",
						"(Lcom/gensym/com/Guid;ILjava/lang/String;Ljava/lang/String;)V");
    }
  }
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
static jobject create_axmodes(JNIEnv *env,
			      jclass native_interface_class, 
			      CLSID *clsid,
			      int dwFlags,
			      char * szFile) 
{
  jobject result;
  jstring fileName = NULL;
  
  if (szFile != NULL)
    fileName = c_to_java_string(env,szFile);

  jprintf(env, PROGRESS, "Calling into java for ActiveXModes");

  if (!env) {
    jprintf(env, DERROR, "Error: could not call Java method because I don't have a ");
    jprintf(env, DERROR, "pointer to the VM.");
    return NULL;
  }
			
  get_axmodes_constructor(env);
  if (axmodes_constructor == NULL) {
    jprintf(env, DERROR, "Error: could not call Java method because I don't have a ");
    jprintf(env, DERROR, "pointer to the ActiveXModes constructor.\n");
    return NULL;
  }
	
  result = (*env)->NewObject
    (env, axmodes_class, axmodes_constructor, create_guid(env, clsid), 
     dwFlags, fileName, NULL);

  return result;
		
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
CLSID *make_guid_from_java_guid(JNIEnv *env, jobject java_clsid)
{
    jclass guidClass;
    jfieldID field1, field2, field3, field40, field41, field42,
	field43, field44, field45, field46, field47;

    guidClass = (*env)->GetObjectClass(env, java_clsid);
    if (!guidClass) return (CLSID *) &GUID_NULL;

    field1  = (*env)->GetFieldID (env, guidClass, "d1", "I");
    field2  = (*env)->GetFieldID (env, guidClass, "d2", "I");
    field3  = (*env)->GetFieldID (env, guidClass, "d3", "I");
    field40 = (*env)->GetFieldID (env, guidClass, "d40", "S");
    field41 = (*env)->GetFieldID (env, guidClass, "d41", "S");
    field42 = (*env)->GetFieldID (env, guidClass, "d42", "S");
    field43 = (*env)->GetFieldID (env, guidClass, "d43", "S");
    field44 = (*env)->GetFieldID (env, guidClass, "d44", "S");
    field45 = (*env)->GetFieldID (env, guidClass, "d45", "S");
    field46 = (*env)->GetFieldID (env, guidClass, "d46", "S");
    field47 = (*env)->GetFieldID (env, guidClass, "d47", "S");

    if (field1 && field2 && field3 && field40 && field41 && field42 &&
	field43 && field44 && field45 && field46 && field47) 
    {
	CLSID *result;

	result = (CLSID *) malloc(sizeof(CLSID));
	memset(result, 0, sizeof(CLSID));

	result->Data1 = (DWORD) (*env)->GetIntField (env, java_clsid, field1);
	result->Data2 = (WORD) (*env)->GetIntField (env, java_clsid, field2);
	result->Data3 = (WORD) (*env)->GetIntField (env, java_clsid, field3);
	result->Data4[0] = (BYTE) (*env)->GetShortField (env, java_clsid, field40);
	result->Data4[1] = (BYTE) (*env)->GetShortField (env, java_clsid, field41);
	result->Data4[2] = (BYTE) (*env)->GetShortField (env, java_clsid, field42);
	result->Data4[3] = (BYTE) (*env)->GetShortField (env, java_clsid, field43);
	result->Data4[4] = (BYTE) (*env)->GetShortField (env, java_clsid, field44);
	result->Data4[5] = (BYTE) (*env)->GetShortField (env, java_clsid, field45);
	result->Data4[6] = (BYTE) (*env)->GetShortField (env, java_clsid, field46);
	result->Data4[7] = (BYTE) (*env)->GetShortField (env, java_clsid, field47);

	print_iid_info(env, PROGRESS, "Converting back now", result);
	return result;
    } else {
	jprintf(env, DERROR, "Could not obtain all fields of GUID.");
	return (CLSID *) &GUID_NULL;
    }
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     It would be nice to assure that Java and C debug levels are in synch
 *     by doing something like:
 *       switch (newDebugLevel) {
 *          case NativeMethodBroker.ERROR:
 *            __iDebugLevel = ERROR;
 *          ...
 *     but that would probably be kind of expensive.  For now, I just 
 *     count on Java debug levels being equal to C debug levels.  Duh.
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
Java_com_gensym_com_NativeMethodBroker_set_1trace_1level
    (JNIEnv *env, jobject this, jshort newDebugLevel)
{
    C_setDebugLevel(env, (short) newDebugLevel);
    jprintf(env, DETAIL, "trace level now = %d", DebugLevel());
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
Java_com_gensym_com_NativeMethodBroker_containerSetup
  (JNIEnv *env, jclass pThis, jstring external_name, jint external_appInstance)
{
    char *external_gszname;

#ifdef BETA_RESTRICTIONS
  if (excel_version() != 8)
  {
    AlertBox("This 1 month trial version of BeanXporter is no longer valid.\n\nPlease visit http://www.gensym.com/java for infomation on the\nlatest version of BeanXporter");
    exit(-1);
  }
#endif
    jprintf(env, DUMP, "doing container setup");
    external_gszname = java_to_c_string(env, external_name);
    container_setup(env, external_gszname, external_appInstance);
    jprintf(env, DUMP, "finished doing container setup");
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
JNIEXPORT jobject JNICALL
Java_com_gensym_com_ActiveXGenericComponent_prompt_1for_1insert_1object
    (JNIEnv *env, jclass pThis, jint hWnd_address)
{
  CLSID *clsid;
  char szFile[OLEUI_CCHPATHMAX];  /* now defined in shared.h */
  int dwFlags;
    
  clsid = get_clsid_and_details_from_user(env, hWnd_address,&dwFlags,szFile);

  if (clsid) {
    print_iid_info(env, PROGRESS, "original clsid = ", clsid);
    jprintf(env, PROGRESS, "flags = %d", dwFlags);

    return create_axmodes(env, pThis, clsid, dwFlags, szFile); 
  } else {
      return create_axmodes(env, pThis, (CLSID *)&GUID_NULL,
			    dwFlags, szFile);
  }
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
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_insert_1object_1from_1clsid_1with_1license
    (JNIEnv *env, jclass pThis, jobject java_clsid, jint hWnd_address, 
     jstring license)
{
    CLSID *clsid;

    clsid = make_guid_from_java_guid(env, java_clsid);
    if (IS_NULL_GUID(clsid)) {
      /* I feel like this function should not be called with an invalid GUID, and
       * that instead the caller should verify first.  That's why that jprintf has
       * debug priority 1, meaning an error occurred.
       */
      jprintf(env, DERROR, "insert_object_from_clsid received null clsid");
      return NO_CLIENT_SITE;
    } else {
      if (license) 
      {
        BSTR license_bstr;
        PCOMOBJ pobj;

        license_bstr = java_to_BSTR(env, license);
        pobj = insert_object_from_clsid(env, clsid, TRUE, license_bstr);
        SysFreeString(license_bstr);
        return (jint)pobj;
      }
      else  {
         return (jint) insert_object_from_clsid(env, clsid, 
                           TRUE,NULL);
      }
    }
}

/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: deprecated. Now use insert_object_from_clsid_with_license
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_insert_1object_1from_1clsid
    (JNIEnv *env, jclass pThis, jobject java_clsid, jint hWnd_address)
{
    return Java_com_gensym_com_ActiveXProxy_insert_1object_1from_1clsid_1with_1license(
      env, pThis, java_clsid, hWnd_address, NULL);
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
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_instantiate_1uninsertable_1object_1with_1license
  (JNIEnv *env, jclass pThis, jobject java_clsid, jstring license)
{
  CLSID *clsid;

  clsid = make_guid_from_java_guid(env, java_clsid);
  if (IS_NULL_GUID(clsid)) {
  /* I feel like this function should not be called with an invalid GUID, and
  * that instead the caller should verify first.  That's why that jprintf has
  * debug priority ERROR.
   */
    jprintf(env, DERROR, "instantiate_uninsertable_object received null clsid");
    return NO_CLIENT_SITE;
  } else {
    if (license)
    {
        BSTR license_bstr;
        PCOMOBJ pobj;

        license_bstr = java_to_BSTR(env, license);
        pobj = insert_object_from_clsid(env, clsid, FALSE, license_bstr);
        SysFreeString(license_bstr);
        return (jint)pobj;
    }
    else {
      return (jint) insert_object_from_clsid(env, clsid, FALSE,
                      NULL);
    }
  }
  return NO_CLIENT_SITE;
}


/*****************************************************************************
 * 
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: deprecated.  Now use instantiate_uninsertable_object_with_license
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_instantiate_1uninsertable_1object
  (JNIEnv *env, jclass pThis, jobject java_clsid)
{
  return Java_com_gensym_com_ActiveXProxy_instantiate_1uninsertable_1object_1with_1license(
      env, pThis, java_clsid,  NULL);
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
JNIEXPORT jint JNICALL
Java_com_gensym_com_ActiveXProxy_insert_1object_1from_1file
    (JNIEnv *env, jclass pThis, jstring file)
{
  WCHAR *pFileName;
  PCOMOBJ pobj;
  
  pFileName = java_to_unicode_string(env, file);
  pobj = insert_object_from_file(env, pFileName);
  free(pFileName);
  return (jint)pobj;
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
JNIEXPORT jint JNICALL
Java_com_gensym_com_NativeMethodBroker_get_1IDispatch
    (JNIEnv *env, jclass pThis, jint pObj_address)
{
    LPDISPATCH pdisp = (LPDISPATCH) 0;
    LPVIEWOBJECT2 pview = (LPVIEWOBJECT2) 0;
    LPVIEWOBJECT pview1 = (LPVIEWOBJECT) 0;
    HRESULT hr;
    PCOMOBJ pObj;
    LPUNKNOWN pUnk = NULL;
    
    pObj = (PCOMOBJ) pObj_address;
    if (!pObj) {
        jprintf(env, DERROR, "Error: received null pObj");
        return (jint) NULL;
    }
    
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);

    if (pObj->pIDispatch != NULL)
        return (jint)pObj->pIDispatch;

    if (pObj->pComInfo) {
        pUnk = (LPUNKNOWN) pObj->pComInfo;
    }
    else {
        pUnk = pObj->pUnk;
    }
    
    if (!pUnk) {
        jprintf(env, DERROR, "Error: received null pUnknown");
        return (jint) NULL;
    }
    
    jprintf(env, DETAIL, "************************************************************");
    jprintf(env, DETAIL, "************************************************************");
    jprintf(env, DETAIL, "************************************************************");
    hr = pUnk->lpVtbl->QueryInterface(pUnk, &IID_IViewObject2,
        (void FAR* FAR*)&pview);
    if (FAILED(hr)) {
        if (pview) {
            pview->lpVtbl->Release(pview);
            jprintf(env, PROGRESS, "This object seems to support IViewObject2,");
            jprintf(env, PROGRESS, "although queryinterface failed");
        } else {
            jprintf(env, PROGRESS, "This object does *not* support IViewObject2");
        }
    } else {
        jprintf(env, PROGRESS, "This object SUPPORTS IViewObject2");
        pview->lpVtbl->Release(pview);
    }
    
    hr = pUnk->lpVtbl->QueryInterface(pUnk, &IID_IViewObject,
        (void FAR* FAR*)&pview1);
    if (FAILED(hr)) {
        if (pview1) {
            pview1->lpVtbl->Release(pview1);
            jprintf(env, PROGRESS, "This object seems to support IViewObject,");
            jprintf(env, PROGRESS, "although queryinterface failed");
        } else {
            jprintf(env, PROGRESS, "This object does *not* support IViewObject");
        }
    } else {
        jprintf(env, PROGRESS, "This object SUPPORTS IViewObject");
        pview1->lpVtbl->Release(pview1);
    }
    
    
    hr = pUnk->lpVtbl->QueryInterface(pUnk, &IID_IDispatch, (void FAR* FAR*)&pdisp);
    if (FAILED(hr)) {
        jprintf(env, PROGRESS, "This object does *not* support IDispatch");
        return (jint) NULL;
    } else {
        jprintf(env, PROGRESS, "This object SUPPORTS IDispatch: %x", (long) pdisp);
    }
    
    pObj->pIDispatch = pdisp;
    return (jint) pdisp;
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
JNIEXPORT jboolean JNICALL
Java_com_gensym_com_ActiveXProxy_is_1open_1in_1window
  (JNIEnv *env, jobject pThis, jint pObj_address) 
{
    PCOMOBJ pObj = (PCOMOBJ) pObj_address;
    ASSERT(pObj->dwMagic == OBJECT_MAGIC);

    if (pObj->sOpenInWindow == TRUE) {
        return JNI_TRUE;
    }

    return JNI_FALSE;
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
JNIEXPORT jobject JNICALL
Java_com_gensym_com_ActiveXProxy_get_1clsid
    (JNIEnv *env, jobject pThis, 
    jint pObj_address, jint hIDispatch)
{
  long hr;
  IDispatch *pIDispatch;
  CLSID *clsid;
  ITypeInfo FAR *pTypeInfo;
  TYPEATTR FAR * pTypeAttr;

  PCOMOBJ pObj = (PCOMOBJ) pObj_address;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  if (pObj->sOpenInWindow != TRUE) {
    jprintf(env, DERROR, "Cannot invoke method on an inactive object");
    return (jobject) NULL;
  }
  pIDispatch = (LPDISPATCH) hIDispatch;

  hr = pIDispatch->lpVtbl->GetTypeInfo(pIDispatch, 0, LOCALE_USER_DEFAULT, &pTypeInfo);

  if (FAILED(hr) || (! pTypeInfo)) {
    jprintf(env, DERROR, "get_clsid failed to get typeinfo");
    return (jobject) NULL;
  }

  hr = pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr);
  if (FAILED(hr)) {
    jprintf(env, DERROR, "get_clsid failed to get typeattr");
    return (jobject) NULL;
  }

  clsid = &(pTypeAttr->guid);

  if (! clsid) {
      return (jobject) NULL;
  }

  return create_guid(env, clsid);
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
JNIEXPORT jboolean JNICALL
Java_com_gensym_com_ActiveXProxy_check_1cast
    (JNIEnv *env, jobject pThis, 
    jint pObj_address, jint hIDispatch,
    jobject java_clsid)
{
  long hr;
  IDispatch *pIDispatch;
  CLSID *clsid;
  ITypeInfo FAR *pTypeInfo;
  TYPEATTR FAR * pTypeAttr;
  CLSID *clsid2;

  PCOMOBJ pObj = (PCOMOBJ) pObj_address;
  ASSERT(pObj->dwMagic == OBJECT_MAGIC);

  if (pObj->sOpenInWindow != TRUE) {
    jprintf(env, DERROR, "Cannot invoke method on an inactive object");
    return JNI_FALSE;
  }
  pIDispatch = (LPDISPATCH) hIDispatch;

  if (! pIDispatch)
  {
    jprintf(env, DERROR, "Null dispatch pointer passed to check_cast");
    return JNI_FALSE;
  }

  clsid = make_guid_from_java_guid(env, java_clsid);
  
  print_iid_info(env, DERROR, "CLSID to compare = ", clsid);

  if (IS_NULL_GUID(clsid)) {
    jprintf(env, DERROR, "check_cast received null clsid");
    return JNI_FALSE;
  }

  hr = pIDispatch->lpVtbl->GetTypeInfo(pIDispatch, 0, LOCALE_USER_DEFAULT, &pTypeInfo);

  if (FAILED(hr) || (! pTypeInfo)) {
    jprintf(env, DERROR, "check_cast failed to get typeinfo");
    return JNI_FALSE;
  }

  hr = pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr);
  if (FAILED(hr)) {
    jprintf(env, DERROR, "check_cast failed to get typeattr");
    return JNI_FALSE;
  }

  clsid2 = &(pTypeAttr->guid);

  if (! clsid2) {
      return JNI_FALSE;
  }

  print_iid_info(env, DERROR, "CLSID found = ", clsid2);

  /* Too strict, what about subclass relationships? */
  if (IsEqualGUID(clsid2, clsid)) 
      return JNI_TRUE;
  else return JNI_FALSE;
}

void start_up_debug_window(HINSTANCE ghAppInstance) {}


#else /* WIN32 */

JNIEXPORT jint JNICALL Java_com_gensym_com_ActiveXProxy_get_1IDispatch(JNIEnv *env, jobject pThis, jint pObj_address) {}
JNIEXPORT jobject JNICALL Java_com_gensym_com_ActiveXProxy_com_1Invoke(JNIEnv *env, jobject pThis, jint pIDispatch, jint memid, jobject args) {}
void start_up_debug_window(int ghAppInstance) {}

#endif /* WIN32 */



