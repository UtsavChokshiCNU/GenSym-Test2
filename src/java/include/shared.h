#ifndef _SHARED_H_
#define _SHARED_H_

#include "jni.h"

#ifdef WIN32

#include <windows.h>
#include <ole2ver.h> /*  for version numbers in rmm and rup */
#include <olectl.h> 
#include <ocidl.h>

#define CONTAINAPI __declspec( dllexport )

#define NUMBER_OF_DAYS_BETWEEN_DEC30_1899_AND_JAN_1_1970 25569
#define NUMBER_OF_MILLISECONDS_IN_ONE_DAY 86400000

#ifdef BOOL
#  undef BOOL
#endif

#ifndef LEAVE_BOOL_ALONE
#  define BOOL jint
#endif

#define TRUTH_VALUE jint

#define DEFAULT_OBJ_WIDTH   400
#define DEFAULT_OBJ_HEIGHT  300

/* Controls whether Beta restrictions are used.  
   These are hardcoded - instead they should be controlled by the build-system */
/* #define BETA_RESTRICTIONS   1  */   /* Stubbed out for full releases */                                        
#define BETA_RESTRICTIONS_LENGTH   2 /* in months from build date */
#define BETA_RESTRICTIONS_START_DAY     2
#define BETA_RESTRICTIONS_START_MONTH   9
#define BETA_RESTRICTIONS_START_YEAR    1998


/*  flags for File functions */
#define FILE_PROMPT_FOR_SAVE        0x0001
#define FILE_DONT_PROMPT_FOR_SAVE   0x0000
#define FILE_UPDATE_CAPTION         0x0002
#define FILE_DONT_UPDATE_CAPTION    0x0000
#define FILE_SAVE                   0x0000
#define FILE_SAVE_AS                0x0004

/* moved here from xcontain.h */
#define OLEUI_CCHPATHMAX                256


#define IS_NULL_GUID(idx) (IsEqualIID(idx, &GUID_NULL))

/* In place activation constants */
#define JAVA_BORDER_SIZE             0 /* Percentage of size to always devote to a Java border */
#define CLIP_BORDER_SIZE             0 /* Percentage of size for clipping rectangle */
#define EXCEL_BORDER_SIZE           10 /* Percentage of size for clipping rectangle */

#define VOID_TYPE_STRING "void"

#define OBJECT_MAGIC MAKEFOURCC('N','E','R','D')
#define EVENT_LISTENER_MAGIC MAKEFOURCC('N','A','F','F')

typedef struct _CONTAINEROBJECT *PCOMOBJ;

typedef struct _EVENT_LISTENER { /*  IDispatch interface for an event listener */
    IDispatchVtbl FAR *lpVtbl;   /*  pointer to generic vtbl for event IDispatch */
    PCOMOBJ pData;               /*  pointer to the object's data */
    DWORD dwMagic;               /*  magic number */
    IID *iid;                    /*  IID of the interface being listened to */ 
    jobject jiid;                /*  Global Ref to Guid object */ 
    DWORD dwConn;                /*  Connection identifier for disconnecting */
    struct _EVENT_LISTENER *next;  /*  next EVENT_LISTENER in linked list */
} EVENT_LISTENER;


typedef struct _CONTAINEROBJECT {
    DWORD dwMagic;                  /*  magic number */
    JNIEnv *env;                    /*  cached Env  */
    LONG lRef;                      /*  reference count */
    LPOLEOBJECT pComInfo;            /*  pointer to its OLE info */
    IUnknown *pUnk;              /*  IUnknown used when IOLEOBJECT unavailable */
    LPSTORAGE mp_Storage;           /*  pointer to its storage object */
    WCHAR szStorageName[32];         /*  its storage name (OLE1 etc) */
    CLSID *clsid;
    BOOL insertable;
    BOOL bIsExcel;
    HWND hwnd;                      /*  Cached Hwnd for use by IOleInPlace/Site/Frame/UIWindow */
    HWND createdHwnd;               /*  Hwnd that will need to be deleted when the object is */
    LPRECT rect;                    /*  Cached Rectangle for use by IOleInPlaceSite */    
    IOleInPlaceObject * pIOleIPObject;
    /*  InPlaceObject pointer setup by IOleInPlaceSite OnInPlaceActivate() */
    IOleInPlaceActiveObject * pIOleIPActiveObject;
    /*  InPlaceActiveObject pointer setup by IOleInPlaceSite/Frame/UIWindow */
    IDispatch * pIDispatch;
    OLEMISC oleMisc;  /* misc characteristics of the object */
    LCID locale;                /*  ambient locale */
    int rgbBack;                /*  ambient background color */
    int rgbFore;                /*  ambient foreground color */
    unsigned int font;          /*  ambient font             */
    BOOL designMode;            /*  is this design mode?     */
    LPDATAOBJECT pDataObj;
    DWORD unadviseID;
    struct _ObjIUnknown {           /*  IUnknown interface */
        IUnknownVtbl FAR * lpVtbl;  /*  pointer to generic vtbl for IUnknown */
        PCOMOBJ pData;              /*  pointer to the object's data */
    } ObjIUnknown;
    struct _ObjIClientSite {        /*  IClientSite interface */
        IOleClientSiteVtbl FAR * lpVtbl;  /*  pointer to generic vtbl for IClientSite */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIClientSite;
    struct _ObjIAdviseSink {        /*  IAdviseSink interface */
        IAdviseSinkVtbl FAR * lpVtbl; /*  pointer to generic vtbl for IAdviseSink */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIAdviseSink;
    struct _ObjIDataObject {        /*  IDataObject interface */
        IDataObjectVtbl FAR * lpVtbl; /*  pointer to generic vtbl for IDataObject */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIDataObject;
    struct _ObjIInPlaceSite {        /*  IOleInPlaceSite interface */
        IOleInPlaceSiteExVtbl FAR * lpVtbl; /*  pointer to generic vtbl for IDataObject */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIInPlaceSite;
    struct _ObjIInPlaceFrame {        /*  IOleInPlaceFrame interface */
        IOleInPlaceFrameVtbl FAR * lpVtbl; /*  pointer to generic vtbl for IDataObject */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIInPlaceFrame;
    struct _ObjIInPlaceUIWindow {        /*  IOleInPlaceUIWindow interface */
        IOleInPlaceUIWindowVtbl FAR * lpVtbl; /*  pointer to generic vtbl for IDataObject */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIInPlaceUIWindow;
    struct _ObjIProperyNotifySink {        /*  IPropertyNotifySink interface */
        IPropertyNotifySinkVtbl FAR * lpVtbl; /*  pointer to generic vtbl for */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjIPropertyNotifySink;
    struct _ObjISimpleFrameSite {        /*  ISimpleFrameSite interface */
        ISimpleFrameSiteVtbl FAR * lpVtbl; /*  pointer to generic vtbl for */
        PCOMOBJ pData;            /*  pointer to the object's data */
    } ObjISimpleFrameSite;
    struct _ObjIDispatchAmbient {   /*  IDispatch interface for ambient properties */
        IDispatchVtbl FAR * lpVtbl; /*  pointer to generic vtbl for */
        PCOMOBJ pData;              /*  pointer to the object's data */
    } ObjIDispatchAmbient;
  EVENT_LISTENER *event_listeners_head;
  EVENT_LISTENER *event_listeners_tail;
	short sOpenInWindow;
  PCOMOBJ next;

} COMOBJ;


typedef struct _VTYPE_INFO {
    unsigned short vtype;
    char *className;
    char *descriptor;
    TYPEKIND typekind;
    int createLocation;
} VTYPE_INFO;

typedef struct _FIELD_INFO {
    unsigned short *field_name;
    BOOL isStatic;
    long memid; 
    VTYPE_INFO *vtype;
    short containing_type_info;
    int int_value;
    struct _FIELD_INFO *next;
} FIELD_INFO;

typedef struct _METHOD_INFO {
    unsigned short *method_name;
    short cParams;
    long memid; 
    VTYPE_INFO *vtype;
    short containing_type_info;
    VTYPE_INFO **paramVtypes;
    INVOKEKIND invkind;
    struct _METHOD_INFO *next;
} METHOD_INFO;

typedef struct _EVENT_SET_DESCRIPTOR {
  const GUID *type;
  struct _CLASS_INFO *class_info;
  BOOL isDefault;
  struct _EVENT_SET_DESCRIPTOR *next;
} EVENT_SET_DESCRIPTOR;

typedef struct _METHOD_DESCRIPTOR {   
    METHOD_INFO *method;
    BOOL isExpert;
    BOOL isHidden;
    struct _METHOD_DESCRIPTOR *next;
} METHOD_DESCRIPTOR;

typedef struct _PROPERTY_DESCRIPTOR {   
    METHOD_INFO **methods;
    int cMethods;
    BOOL isExpert;
    BOOL isHidden;
    BOOL isBindable;
    struct _PROPERTY_DESCRIPTOR *next;  
} PROPERTY_DESCRIPTOR;

typedef struct _BEAN_INFO {   
  char *beanInfoName;
  char *beanInfoFileName;
  EVENT_SET_DESCRIPTOR *events_head;
  EVENT_SET_DESCRIPTOR *events_tail;
  METHOD_DESCRIPTOR *methods_head;
  METHOD_DESCRIPTOR *methods_tail;
  PROPERTY_DESCRIPTOR *properties_head;
  PROPERTY_DESCRIPTOR *properties_tail;
} BEAN_INFO;

typedef struct _CLASS_INFO {
    const GUID *cclsid;
    char *className;
    char *sourceFileName;
    char *classFileName;
    char *listenerSourceFileName;
    char *listenerClassFileName;
    char *eventSourceFileName;
    char *eventClassFileName;
    BEAN_INFO *beanInfo;
    FIELD_INFO *fields_head;
    FIELD_INFO *fields_tail;
    METHOD_INFO *methods_head;
    METHOD_INFO *methods_tail;
    ITypeInfo *pTypeInfo; 
    short containing_type_info; 
    BOOL isCreatable;  
    BOOL isInsertable;
    BOOL isControl;
    BOOL isInterface;
    BOOL hasBeenEmitted;
    BOOL hasBeenEmittedAsListener;
    BOOL hasBeenEmittedAsEvent;
    BOOL isLicensed;
    BSTR license;
    BSTR  bstrName;
    BSTR  bstrDocString;
    BSTR  bstrHelpFile;
    struct _LIBRARY_INFO *library;
    struct _CLASS_INFO *next;
} CLASS_INFO;

typedef struct _LIBRARY_INFO {
    const GUID *libid;
    char *packageName;
    unsigned short majorVersion;
    unsigned short minorVersion;
    CLASS_INFO *classes_head;
    CLASS_INFO *classes_tail;
    EVENT_SET_DESCRIPTOR *event_sources_head;
    EVENT_SET_DESCRIPTOR *event_sources_tail;
    int typeCount;
    BSTR  bstrName;
    BSTR  bstrDocString;
    BSTR  bstrHelpFile;
    BOOL partialLibrary;
    struct _LIBRARY_INFO *next;
} LIBRARY_INFO;


CONTAINAPI extern UINT cdecl AlertBox(LPSTR lpFormat, ...);
CONTAINAPI void C_setDebugLevel(JNIEnv *, short);
CONTAINAPI void set_up_container_callbacks(void *, void *, void *, long);
CONTAINAPI WCHAR *ascii_to_unicode(char *);
CONTAINAPI char *unicode_to_ascii(wchar_t *);
CONTAINAPI char *unicode_to_ascii_identifier(wchar_t *);
CONTAINAPI char *java_to_c_string(JNIEnv *, jstring);
CONTAINAPI WCHAR *java_to_unicode_string(JNIEnv *, jstring);
CONTAINAPI BSTR java_to_BSTR(JNIEnv *env, jstring str);
CONTAINAPI jstring c_to_java_string(JNIEnv *, char *);
CONTAINAPI jstring wstring_to_jstring (JNIEnv *, WCHAR *);
CONTAINAPI jstring BSTR_to_jstring (JNIEnv *, BSTR);
CONTAINAPI void excel_dispatch_stuff(JNIEnv *, PCOMOBJ);
CONTAINAPI int excel_version();
CONTAINAPI TRUTH_VALUE PromptToSave();
CONTAINAPI void container_setup(JNIEnv *, char *, long);
CONTAINAPI CLSID *get_clsid_from_user(long);
CONTAINAPI PCOMOBJ insert_object_from_file(JNIEnv *, WCHAR *);
CONTAINAPI jint bucket_GetDC(jint);
CONTAINAPI TRUTH_VALUE is_clipboard_format_available();
CONTAINAPI jint open_file(char *);
CONTAINAPI TRUTH_VALUE save();
CONTAINAPI TRUTH_VALUE save_as();
CONTAINAPI jint paste_object(jint);
CONTAINAPI void setDirty(jboolean);
CONTAINAPI void SetClipBorder(LPRECT,int);
CONTAINAPI void bucket_dispatch_exe_stuff();
CONTAINAPI char *jni_string_for_java_type (JNIEnv *env, unsigned short vtype);
CONTAINAPI char *vartype_string_for_java_type(JNIEnv *, unsigned short);
CONTAINAPI char *vartype_string_for_java_get_method(JNIEnv *, unsigned short);
CONTAINAPI char *default_value_string_for_java_type(JNIEnv *, unsigned short);
CONTAINAPI jobject make_jobject_from_variant(JNIEnv *, VARIANT, jobject, int);
CONTAINAPI jobject jdate_from_DATE(JNIEnv *env, DATE date);
CONTAINAPI DATE DATE_from_jdate(JNIEnv *env, jobject pdate);
CONTAINAPI jobjectArray create_jdate_array(JNIEnv *env, int size);
CONTAINAPI jobjectArray create_jstring_array(JNIEnv *env, int size);
CONTAINAPI jobjectArray create_jvariant_array(JNIEnv *env, int size);
CONTAINAPI void init_variant_from_jobject(JNIEnv *env, jobject object,
    VARIANT* pVariant, jobject proxy, int isEvent);
CONTAINAPI void CopyAndFreeNativeRefParameter(JNIEnv *env, VARIANT variant,
    jobject proxy);
CONTAINAPI void CopyOutJavaRefParameter(JNIEnv *env, VARIANT variant, jobject jvariant,
    jobject proxy);
CONTAINAPI SAFEARRAY *NativeSAFromJavaSA(JNIEnv *env, jobject pSafeArray, int newOwner);

/* constants for the functions that create Java safe array classes */
#define OWNED_BY_DLL TRUE
#define OWNED_BY_CONTROL FALSE
CONTAINAPI jobject CreateShortSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateIntSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateFloatSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateDoubleSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateDateSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateStringSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateBooleanSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateVariantSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI jobject CreateByteSafeArray(JNIEnv *env, SAFEARRAY *pSA, int ownedByDLL);
CONTAINAPI DISPPARAMS *create_dispparams(JNIEnv *, jobject, jobject);
CONTAINAPI void update_cell(JNIEnv *, PCOMOBJ, int, int, int);
CONTAINAPI CLSID *get_typelib_libid(JNIEnv * env, const struct _GUID *);
CONTAINAPI PCOMOBJ insert_object_from_clsid(JNIEnv *, CLSID *, TRUTH_VALUE, BSTR);
CONTAINAPI CLSID *get_clsid_and_details_from_user (JNIEnv *, long, int *, char *);

CONTAINAPI LIBRARY_INFO *libraries_head;
CONTAINAPI LIBRARY_INFO *libraries_tail;
CONTAINAPI char *make_full_package_classname(char *,char *);

CONTAINAPI void jemit_everything(JNIEnv *);

CONTAINAPI GUID *copy_guid (GUID *);
CONTAINAPI jobject create_guid (JNIEnv *,GUID *);
CONTAINAPI void set_value_from_java_variant(JNIEnv *, LPDISPATCH, 
					    DISPID, DISPPARAMS *,
					    jobject);
CONTAINAPI HRESULT resizeInPlaceObject(JNIEnv *,PCOMOBJ,
                                       IOleInPlaceObject *,
                                       LPRECT,
                                       LPRECT,
                                       BOOLEAN);
CONTAINAPI HRESULT forward_event(LPDISPATCH,
                                 DISPID,  
                                 DISPPARAMS FAR*,
                                 VARIANT FAR*,  
                                 EXCEPINFO FAR*,
                                 unsigned int FAR*);

CONTAINAPI HRESULT client_forward_event(PCOMOBJ,
                                        jstring,
                                        jint,
                                        jstring,
                                        jobject);

/*CONTAINAPI JNIEnv * get_this_VM();*/

CONTAINAPI void initialize_event_listener(EVENT_LISTENER *, PCOMOBJ);
                                        
CONTAINAPI CLSID *make_guid_from_java_guid(JNIEnv *, jobject);

CONTAINAPI char *create_error_report(HRESULT hr);

                                     
JNIEXPORT jint JNICALL Java_com_gensym_com_NativeMethodBroker_getRatio
  (JNIEnv *, jclass, jint);
JNIEXPORT jobject JNICALL Java_com_gensym_com_NativeMethodBroker_browse_1default_1library
  (JNIEnv *, jclass);
JNIEXPORT void JNICALL Java_com_gensym_com_ActiveXProxy_start_1up
  (JNIEnv *, jclass);

#else  /* WIN32 */

#define CONTAINAPI
#define WCHAR int
#define LPDISPATCH void *
#define LPOLESTR int *
#define HRESULT int
#define UINT unsigned int
#define cdecl
#define LPSTR char *


typedef struct {
    int cArgs;
    int cNamedArgs;
    void *rgvarg;
    void *rgdispidNamedArgs;
} DISPPARAMS;

#endif  /* WIN32 */


#endif  /* _SHARED_H_ */

