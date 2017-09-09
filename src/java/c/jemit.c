/**********************************************************************
 * jemit.c
 *
 * Author: Allan Scott
 *
 **********************************************************************/
#include "shared.h"
#include "dprintf.h"


#ifdef WIN32

#include <olectl.h>
#include <direct.h>

static jclass javaClass = NULL;
static jmethodID constructor = NULL;
static jmethodID toFile = NULL;
static jmethodID addShortField = NULL;
static jmethodID addMethod = NULL;

#define ACC_PUBLIC         0x0001
#define ACC_PRIVATE        0x0002
#define ACC_PROTECTED      0x0004
#define ACC_STATIC         0x0008
#define ACC_FINAL          0x0010
#define ACC_SYNCHRONIZED   0x0020
#define ACC_VOLATILE       0x0040
#define ACC_TRANSIENT      0x0080
#define ACC_NATIVE         0x0100
#define ACC_INTERFACE      0x0200
#define ACC_ABSTRACT       0x0400
#define ACC_SUPER          0x0020

#define AX_INVOKE          0
#define AX_PROPERTYGET     1
#define AX_PROPERTYSET     2



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
void set_up_method_pointers (JNIEnv *env) 
{ 
  BOOL revalidate = FALSE;
  if (!javaClass) {
  javaClass = (*env)->FindClass(env, "com/gensym/com/JavaClass");
  javaClass = (*env)->NewGlobalRef(env, javaClass);
  revalidate = TRUE; 
  }

  if (revalidate && javaClass) {
    constructor = (*env)->GetMethodID(env, javaClass, "<init>",
"(Lcom/gensym/com/Guid;Ljava/lang/String;ZZZLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    toFile = (*env)->GetMethodID(env, javaClass, 
                                 "toFile", "(Ljava/lang/String;Z)V");
    addShortField = (*env)->GetMethodID(env, javaClass,
                                        "addField",
                                        "(ILjava/lang/String;S)V");
    addMethod = (*env)->GetMethodID(env, javaClass,
                                        "addMethod",
                                         "(IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
  }
}


/*****************************************************************************
 * jemit_fields
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void jemit_fields(JNIEnv *env, FIELD_INFO *node, jobject jclass)
{
  unsigned short *field_name;
  int field_number;
  VTYPE_INFO *vtinfo;
  VARTYPE vtype;
  TYPEKIND typekind;
  BOOL isStatic; 
  //char *type_string;
  int access = ACC_PUBLIC | ACC_FINAL;

  jstring fieldName;

  for (field_number=0; node; field_number++, node=node->next) {

      field_name = node->field_name;
      vtinfo = node->vtype;
      vtype = vtinfo->vtype;
      typekind = vtinfo->typekind;
      isStatic = node->isStatic;

      //type_string = vartype_string_for_java_type(env, vtype);

      fieldName = wstring_to_jstring(env, field_name);     

      if (isStatic)
        access |= ACC_STATIC;

      (*env)->CallVoidMethod(env, jclass, addShortField,
        (jint) access,
        fieldName,
        (jshort) node->int_value);           
    }
}




/*****************************************************************************
 * jemit_methods
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void jemit_methods(JNIEnv *env, METHOD_INFO *node, jobject jclass)
{
    unsigned short *method_name;
    int method_number;
    short i,  cParams; 
    unsigned short varTypeInfo;
    char *type_string;
    char *arg_type_strings[50];
    char *descr;
    VTYPE_INFO ** paramVtypes;
    INVOKEKIND invkind;
    VARTYPE vtype;
    char *variant_type = NULL;
   
    for (method_number=0; node; method_number++, node=node->next) {
      BOOL voidReturn = FALSE;
      VTYPE_INFO *vtinfo;
      TYPEKIND typekind;
      int descriptorLength;

      jint access;
      jint memid;
      jstring methodName;
      jstring descriptor;
      jstring variantType;
      jint dispatchKind;

      invkind = node->invkind;
      if (DISPATCH_PROPERTYPUTREF == invkind) {
        continue;
      }

      cParams = node->cParams;
      method_name = node->method_name;
      vtinfo = node->vtype;
      vtype = vtinfo->vtype;
      typekind = vtinfo->typekind;
      paramVtypes = node->paramVtypes; 

      // Calculate access
      access = ACC_PUBLIC;

      // Calculate memid
      memid = node->memid;

      // Calculate methodName
      methodName = wstring_to_jstring(env, method_name);

      // Calculate dispatchKind

      switch (invkind) {
      case DISPATCH_PROPERTYGET: {
        dispatchKind = AX_PROPERTYGET;
        break;   }
      case DISPATCH_PROPERTYPUT: {
        dispatchKind = AX_PROPERTYSET;
        break;                                      }
      default: {
        dispatchKind = AX_INVOKE; 
        break;
               }
      }

      // Calculate the Descriptor      

      if (typekind == TKIND_COCLASS || typekind == TKIND_DISPATCH) {
        if (vtinfo->descriptor == NULL) {
          type_string = "Lcom/gensym/com/Variant;";
          variant_type = "Lcom/gensym/com/ActiveXDispatchable;";
        }
        else {
          type_string = vtinfo->descriptor;
          variant_type = vartype_string_for_java_get_method(env, vtype);          
        }
      }
      else {
        type_string = jni_string_for_java_type(env, vtype);
        variant_type = vartype_string_for_java_get_method(env, vtype);
      }

      descriptorLength = 3;
      if (cParams > 0)
      for (i=0; i<cParams; i++) {
          char *type_string;
          TYPEKIND tkind;
          VTYPE_INFO *vtinfo;
        
          varTypeInfo = paramVtypes[i]->vtype;
          vtinfo = paramVtypes[i]; 
          tkind = paramVtypes[i]->typekind;
          
          if (tkind == TKIND_COCLASS || tkind == TKIND_DISPATCH) {
            if (vtinfo->descriptor == NULL) 
              type_string = "Lcom/gensym/com/Variant;";
            else type_string = vtinfo->descriptor;
          }
          else {
            type_string = jni_string_for_java_type(env, varTypeInfo);
          }          

          descriptorLength += strlen(type_string);
          arg_type_strings[i] = type_string;
      }

      descriptorLength += strlen(type_string);

      descr = malloc(sizeof(char) * descriptorLength);

      descr[0] = '(';
      for (i=0; i<cParams; i++) {
          strcat(descr, arg_type_strings[i]);
      }
      strcat(descr, ")");
      strcat(descr, type_string);

      descriptor = c_to_java_string(env, descr);

      // Calculate variantName
      variantType = c_to_java_string(env, variant_type);

      (*env)->CallVoidMethod(env, jclass, addMethod,
                             access, memid, methodName,
                             descriptor, variantType,
                             dispatchKind);
    }
}


/*****************************************************************************
 * jemit_one_class
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void jemit_one_class(JNIEnv *env, CLASS_INFO *node,
                          int count, BSTR bstrName, 
                          BSTR bstrDocString, BSTR bstrHelpFile) 
{
    const GUID *cclsid;
    char *classname;
    char *packagename;
    char *filename;
    BSTR bstrName2, bstrDocString2, bstrHelpFile2, bstrLibName;
    BOOL is_insertable = node->isInsertable;
    BOOL is_creatable = node->isCreatable;
    BOOL is_interface = node->isInterface;

    /* Local variables used to store data to be sent to Java */
    jobject guid;
    jstring className;
    jstring packageName;
    jstring fileName;
    jstring docName;
    jstring docString;
    jstring docLibName; 
    jobject jclass;

    /* Calculate intermediate data */
    bstrLibName = node->library->bstrName;
    bstrName2 = node->bstrName;
    bstrDocString2 = node->bstrDocString;
    bstrHelpFile2 = node->bstrHelpFile; 
    cclsid = node->cclsid;
    classname = node->className;
    packagename = node->library->packageName;
    filename = node->classFileName;

    if (classname == NULL) {
      jprintf(env, DERROR, "Unable to complete emit, missing classname");
      return;
    }

    /* Calculate data to be sent to Java */
    guid = create_guid(env, (GUID *) cclsid);
    className = c_to_java_string(env, classname);

    packageName = 
      c_to_java_string(env,
       make_full_package_classname(packagename, classname));
   
    docName = wstring_to_jstring(env, bstrName2);
    docString = wstring_to_jstring(env, bstrName2);
    docLibName = wstring_to_jstring(env, bstrLibName);
    fileName = c_to_java_string(env, filename);

    jclass = (*env)->NewObject
      (env, javaClass, constructor,
       guid, packageName,
       is_creatable, is_insertable,
       is_interface,
       docName, docString, docLibName);
       
    if (node->fields_head) {
        jemit_fields(env, node->fields_head, jclass);
    }
     
    if (node->methods_head) {
      jemit_methods(env,node->methods_head, jclass);
    } 
   
    (*env)->CallVoidMethod(env, jclass, toFile,
                           fileName, JNI_TRUE);

    node->hasBeenEmitted = TRUE;
}



/*****************************************************************************
 * jemit_one_library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void jemit_one_library(JNIEnv *env, LIBRARY_INFO *libInfo) 
 {
   CLASS_INFO *node;
   int i, count, j, len;
   BSTR bstrName, bstrDocString, bstrHelpFile;
   char *packageName;
   char *subDirName;
   node = libInfo->classes_head;

   count = libInfo->typeCount;
   bstrName = libInfo->bstrName;
   bstrDocString = libInfo->bstrDocString; 
   bstrHelpFile = libInfo->bstrHelpFile; 

   packageName = libInfo->packageName;
   len = strlen(packageName);
   subDirName = malloc(sizeof(char) * (len + 2));
   
   subDirName[0] = '\\';
   for (j = 0, i = 0; i < len; i++) 
    subDirName[j++] = packageName[i];
   subDirName[j++] = 0;
   _mkdir(subDirName);
   

   for (i=0; node; i++, node=node->next) {
     jemit_one_class(env, node, count, 
                    bstrName, bstrDocString, bstrHelpFile);
   }
 }


/*****************************************************************************
 * emit_everything
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 void jemit_everything(JNIEnv *env)
 {
   LIBRARY_INFO *node;
   int i;

   set_up_method_pointers(env);
   node = libraries_head;
   for (i=0; node; i++, node=node->next) {
      jemit_one_library(env,node);
   }
 }









#endif /* WIN32 */
