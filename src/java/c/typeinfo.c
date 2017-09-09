/**********************************************************************
 * typeinfo.c
 *
 * Authors: John Valente, Allan Scott
 *
 **********************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include "shared.h"
#include "dprintf.h"


#ifdef WIN32

#include <olectl.h>
#include <direct.h>
#include <time.h>


#define CHAR_IS_ALLOWED(x) (isupper(x) || islower(x) || isdigit(x) || ((x) == '_'))

#define WISUPPER(c) (((c) >= (unsigned short)'A') && ((c) <= (unsigned short)'Z'))
#define WISLOWER(c) (((c) >= (unsigned short)'a') && ((c) <= (unsigned short)'z'))
#define WISDIGIT(c) (((c) >= (unsigned short)'0') && ((c) <= (unsigned short)'9'))
#define WCHAR_IS_ALLOWED(x) (WISUPPER(x) || WISLOWER(x) || WISDIGIT(x) || \
  ((x) == (unsigned short)'_'))

#define DEFAULT_EMIT_PACKAGE "com.gensym.tests"

/* These may not be the right names for these constants */
#define LOCATION_UNKNOWN    -1
#define LOCATION_REQUIRED   10
#define LOCATION_VECTOR     20
#define LOCATION_OPTIONAL   30
#define LOCATION_VOID       50

#define FILE_TYPE_DEFAULT      0
#define FILE_TYPE_EVENT        1
#define FILE_TYPE_LISTENER     2

/* Bitflags for beanify() */
#define USE_JAVAC           0x0001
#define EMIT_EXCEPTIONS     0x0002
#define USE_VERSIONS        0x0004

/* If a method in a dispatch interface has N optional methods we emit
   N extra methods for convenience. MAX_OPTIONAL_TO_EMIT limits this
   to an amount that does not fill up the Bean Box method browser. */
#define MAX_OPTIONALS_TO_EMIT   6

static IDispatch *theIDispatchPointer = NULL;
static FILE *gfp = NULL;
static char gfp_iterations = '0';

/* Now the top level list */
LIBRARY_INFO *libraries_head = NULL;
LIBRARY_INFO *libraries_tail = NULL;

static char saveCurrentDir[256];
static char *user_chosen_emit_package = NULL;

static BOOL useJavac = TRUE;
static BOOL emitExceptions = TRUE;
static BOOL useVersions = FALSE;

void collect_type_information(JNIEnv *, LIBRARY_INFO *,int, ITypeInfo *); 

/*****************************************************************************
 * typelib_output
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void cdecl typelib_output(JNIEnv *env, LPSTR lpFormat, ...) 
{
    char buf[512];
    va_list args;

    va_start(args, lpFormat);
    vsprintf(buf, lpFormat, args);
    va_end(args);
    if (gfp) {
        fprintf(gfp, "%s", buf);
    } else {
        jprintf(env, DERROR, "Could not write message to file");
        jprintf(env, DERROR, "%s", buf);
    }
}

/*****************************************************************************
 * initialize_lib_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_lib_info(LIBRARY_INFO *node) {
    memset(node, 0, sizeof (LIBRARY_INFO));
    node->classes_head = NULL;
    node->classes_tail = NULL;
    node->event_sources_head = NULL;
    node->event_sources_tail = NULL;
    node->libid = NULL;
    node->partialLibrary = FALSE;
    node->next = NULL;
}

/*****************************************************************************
 * initialize_class_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_class_info(CLASS_INFO *node) {
    memset(node, 0, sizeof (CLASS_INFO));
    node->methods_head = NULL;
    node->methods_tail = NULL;
    node->fields_head = NULL;
    node->fields_tail = NULL;
    node->beanInfo = NULL;
    node->pTypeInfo = NULL;
    node->isCreatable = FALSE;
    node->isInsertable = FALSE;
    node->isInterface = FALSE;
    node->hasBeenEmitted = FALSE;
    node->next = NULL;
    node->isLicensed = FALSE;
    node->license = NULL;
}

/*****************************************************************************
 * initialize_field_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_field_info(FIELD_INFO *node) {
  memset(node, 0, sizeof (FIELD_INFO));
  node->field_name = NULL;
  node->int_value = -1;
  node->isStatic = TRUE;
  node->vtype = NULL;
}


/*****************************************************************************
 * initialize_method_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_method_info(METHOD_INFO *node) {
  memset(node, 0, sizeof (METHOD_INFO));
  node->method_name = NULL;
  node->vtype = NULL;
  node->paramVtypes = NULL;
}

/*****************************************************************************
 * initialize_vtype_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_vtype_info(VTYPE_INFO *node) {
    memset(node, 0, sizeof (VTYPE_INFO));
    node->vtype = 0;
    node->className = NULL;
    node->descriptor = NULL;
    node->createLocation = LOCATION_UNKNOWN;
}


/*****************************************************************************
 * initialize_bean_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_bean_info(BEAN_INFO *node) {
    memset(node, 0, sizeof (BEAN_INFO));
    node->beanInfoName = NULL;
    node->beanInfoFileName = NULL;
    node->events_head = NULL;
    node->events_tail = NULL;
    node->methods_head = NULL;
    node->methods_tail = NULL;
    node->properties_head = NULL;    
    node->properties_tail = NULL;    
}

/*****************************************************************************
 * initialize_method_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_method_descriptor(METHOD_DESCRIPTOR *node) {
    memset(node, 0, sizeof (METHOD_DESCRIPTOR));
    node->isExpert = FALSE;
    node->isHidden = FALSE;
    node->next = NULL;
}

/*****************************************************************************
 * initialize_event_set_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_event_set_descriptor(EVENT_SET_DESCRIPTOR *node) {
    memset(node, 0, sizeof (EVENT_SET_DESCRIPTOR));
    node->type = NULL;
    node->isDefault = FALSE;
    node->next = NULL;
}

/*****************************************************************************
 * initialize_property_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void initialize_property_descriptor(PROPERTY_DESCRIPTOR *node) {
    memset(node, 0, sizeof (PROPERTY_DESCRIPTOR));
    node->isExpert = FALSE;
    node->isHidden = FALSE;
    node->isBindable = FALSE;
    node->cMethods = 0;
    node->methods = NULL;
    node->next = NULL;
}

/*****************************************************************************
 * make_classname_from_wide_string
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *make_classname_from_wide_string (JNIEnv *env, BSTR wstring)
{
    short i, j, len;
    char *classname = NULL;
    int uppercase_next = 0;
    
    if (wstring == NULL) {
        classname = malloc(sizeof ("NoName"));
        strcpy(classname, "NoName");
        return classname;
    }
    
    jprintf(env, PROGRESS, "ActiveX classname = %ls", wstring);
    
    len = wcslen(wstring);
    classname = (char *) malloc ((1 + len) * sizeof(char));
    
    /* replace illegal chars with an x, and drop periods but
    make sure the next char is upper case */
    for (i = 0, j = 0; i < len; i++) {
        if (WCHAR_IS_ALLOWED(wstring[i])) {
            if (uppercase_next && WISLOWER(wstring[i])) {
                classname[j++] = toupper(wstring[i]);
            } else {
                classname[j++] = (char) wstring[i];
            }
        } else if (wstring[i] == (unsigned short) '.') {
            uppercase_next = 1;
            continue;
        } else {
            classname[j++] = 'x';
        }

        uppercase_next = 0;
    }
    
    classname[j] = 0;
    
    jprintf(env, PROGRESS, "Java classname = %s", classname);
    
    return classname;
}


/*****************************************************************************
 * get_progid_and_mangle_into_java_class
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
char *get_progid_and_mangle_into_java_class(JNIEnv *env, const GUID *clsid)
{
  unsigned short *progid;
  HRESULT hr;
    
  hr = ProgIDFromCLSID(clsid, &progid);
  if (FAILED(hr)) {
    return NULL;
  }

  return make_classname_from_wide_string(env, progid);
}


/*****************************************************************************
 * make_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
char *make_descriptor(char *packageName,
                      char *className)
{
  char *emitPackage;
  char *buf;
  int length, i;

  if (className == NULL)
    return className;

  if (user_chosen_emit_package)
    emitPackage = user_chosen_emit_package;
  else emitPackage = DEFAULT_EMIT_PACKAGE;


  length = strlen(emitPackage) +  
           strlen(packageName) +
           strlen(className) + 5;

  buf = malloc(sizeof(char) * length);


  buf[0] = 'L';
  buf[1] = 0;

  strcat(buf,emitPackage);
  strcat(buf,"/");
  strcat(buf,packageName);
  strcat(buf,"/");
  strcat(buf,className);
  strcat(buf,";");

  for (i=0; i< length; i++)
  {
    if (buf[i] == '.')
      buf[i] = '/';
  }

  return buf;
}

/*****************************************************************************
 * make_full_package_classname
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
char *make_full_package_classname(char *packageName,
                                         char *className)
{ 
  char *emitPackage;
  char *buf;

  if (className == NULL)
    return className;
  
  if (user_chosen_emit_package)
      emitPackage = user_chosen_emit_package;
  else emitPackage = DEFAULT_EMIT_PACKAGE;


  buf = malloc(sizeof(char) * (strlen(emitPackage) + 
                               strlen(packageName) +
                               strlen(className) + 3));

  buf[0] = 0;

  strcat(buf,emitPackage);
  strcat(buf,".");
  strcat(buf,packageName);
  strcat(buf,".");
  strcat(buf,className);

  return buf;

}
                              


/*****************************************************************************
 * make_packagename
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *make_packagename(BSTR bstrName, 
                              unsigned short majorVersion,
                              unsigned short minorVersion) 
{
  char *buf;
  char versionBuf[16];
  short len, i, j, versionLen;
  int totalLen;

  /* First create the version buffer */
  if (useVersions)
    sprintf(versionBuf,"%d%d", majorVersion, minorVersion);  
  else
    sprintf(versionBuf,"");

  versionLen = strlen(versionBuf);

  /* then create a buffer large enough for the
   * name and the version numbers
   */
  len = wcslen(bstrName);
  totalLen = (int) (len + versionLen);

  buf = malloc((sizeof(char)) * (totalLen + 1));

  for (i =0; i <len; i++) {
    if (WISUPPER(bstrName[i]))
      buf[i] = tolower(bstrName[i]);
    else
      buf[i] = (char) bstrName[i];
  }
  
  for(j = 0;j < versionLen; j++, i++) {
    buf[i] = versionBuf[j];
  }
  
  buf[totalLen] = 0;

  return buf;
}


/*****************************************************************************
 * make_filename
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *make_filename(char *packagename, char *classname, BOOL isSource,
                                                               int fileType)
{
    short i, j, clen, plen, len, extraLen;
    char *filename;

    if (packagename && classname) {
      clen = strlen(classname);
      plen = strlen(packagename);
      len = clen + plen;
      if (fileType == FILE_TYPE_LISTENER)
        extraLen = 18;
      else if (fileType == FILE_TYPE_EVENT)
        extraLen = 15;
      else extraLen = 10;
      
      filename = (char *) malloc ((extraLen + len) * sizeof(char));
      
      i = 0;
      filename[i++] = '.';
      filename[i++] = '\\';
      for (j=0; j<plen; j++)
        filename[i++] = packagename[j];

      filename[i++] = '\\';

      for (j=0; j<clen; j++)
        if (CHAR_IS_ALLOWED(classname[j]))
          filename[i++] = (char) classname[j];
        else
          filename[i++] = '_';

        if (fileType == FILE_TYPE_LISTENER) {
          filename[i++] = 'L';
          filename[i++] = 'i';
          filename[i++] = 's';
          filename[i++] = 't';
          filename[i++] = 'e';
          filename[i++] = 'n';
          filename[i++] = 'e';
          filename[i++] = 'r';
        } 
        else if (fileType == FILE_TYPE_EVENT) 
        {
          filename[i++] = 'E';
          filename[i++] = 'v';
          filename[i++] = 'e';
          filename[i++] = 'n';
          filename[i++] = 't';
        }

        filename[i++] = '.';

        if (isSource) {
          filename[i++] = 'j';
          filename[i++] = 'a';
          filename[i++] = 'v';
          filename[i++] = 'a';
        }
        else {
          filename[i++] = 'c';
          filename[i++] = 'l';
          filename[i++] = 'a';
          filename[i++] = 's';
          filename[i++] = 's';
        }

        filename[i++] = 0;
    } else {
      filename = (char *)malloc(sizeof ("NoName.java"));
      if (isSource)
        strcpy(filename, "NoName.java");
      else
        strcpy(filename, "NoName.class");
    }

    return filename;
}


/*****************************************************************************
 * make_beaninfo_name
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *make_beaninfo_name(char *className)
{
  short len;
  char *beanInfoName;

  if (className) 
  {
    len = strlen(className);
    len += 8;
    beanInfoName = (char *) malloc ((1 + len) * sizeof(char));
    beanInfoName[0] = 0;
    strcat(beanInfoName, className);
    strcat(beanInfoName, "BeanInfo");
    return beanInfoName;
  }
  else {
    beanInfoName = (char *)malloc(sizeof ("NoNameBeanInfo"));
    strcpy(beanInfoName, "NoNameBeanInfo");
    return beanInfoName;
  }
}


/*****************************************************************************
 * open_file_for_emitting
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *open_file_for_emitting (JNIEnv *env, char * filename)
{
    if (!filename)  {    
      gfp = NULL;
      return NULL;
    }
    
    gfp = fopen((const char *) filename, "w");
    if (gfp) {
      jprintf(env, PROGRESS, "Writing java class to %s", filename);
    } else {
      AlertBox("Could not create file %s", filename);
    }
    return filename;
}


/*****************************************************************************
 * isDuplicateMethod
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL isDuplicateMethod(long memid, INVOKEKIND invkind, METHOD_INFO *temp) 
{
    BOOL isDuplicate = FALSE;
    
    while (temp && !isDuplicate) {
	isDuplicate = ((memid == temp->memid) && (invkind == temp->invkind));
	temp = temp->next;
    }
    return isDuplicate;
}


/*****************************************************************************
 * print_invokekind
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *print_invokekind(INVOKEKIND invokekind)
{
  char *type_string;

  switch (invokekind) {
    case INVOKE_FUNC:
	type_string = "method";
	break;
    case INVOKE_PROPERTYGET:
	type_string = "property get";
	break;
    case INVOKE_PROPERTYPUT:
	type_string = "property put";
	break;
    case INVOKE_PROPERTYPUTREF:
	type_string = "property put by reference";
	break;
    default:
	type_string = "error";
    }

    return type_string;
}


/*****************************************************************************
 * isDuplicateNamedMethod
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL isDuplicateNamedMethod(unsigned short *methname,                                    
                                   long memid,
                                   INVOKEKIND invkind,
                                   BOOL *sameInAllWays,
                                   METHOD_INFO *temp) 
{
    BOOL foundDuplicateName = FALSE;
    
    *sameInAllWays = FALSE;

    while (temp && !foundDuplicateName) {
      foundDuplicateName = (!_wcsicmp(methname, temp->method_name)  && 
                            ((invkind == -1) || (invkind == temp->invkind)));

      if (memid == temp->memid) { 
        *sameInAllWays = TRUE;
      }
      temp = temp->next;
    }
    return foundDuplicateName;
}


/*****************************************************************************
 * print_invokekind_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *print_invokekind_info(FUNCDESC *pFuncDesc)
{
    INVOKEKIND invokekind = pFuncDesc->invkind;
 
    return print_invokekind(invokekind);
    
}

/*****************************************************************************
 * print_funkind_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *print_funkind_info(FUNCDESC *pFuncDesc)
{
    char *type_string;
    FUNCKIND funkind = pFuncDesc->funckind;
 
    switch (funkind) {
    case FUNC_VIRTUAL:
	type_string = "virtual";
	break;
    case FUNC_PUREVIRTUAL:
	type_string = "pure virtual";
	break;
    case FUNC_NONVIRTUAL:
	type_string = "nonvirtual";
	break;
    case FUNC_STATIC:
	type_string = "static";
	break;
    case FUNC_DISPATCH:
	type_string = "dispatch";
	/* Don't output anything */
	break;
    default:
	type_string = "error";
    }

    return type_string;
}


/*****************************************************************************
 * print_callconvention_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *print_callconvention_info(FUNCDESC *pFuncDesc)
{
    char *type_string;
    CALLCONV callconvention = pFuncDesc->callconv;

    switch (callconvention) {
    case CC_CDECL:   /* 1 */
	type_string = "cdecl";
	break;
    case CC_PASCAL:   /* CC_CDECL+1  == CC_MSCPASCAL*/
	type_string = "PASCAL";
	break;
    case CC_MACPASCAL:   /* CC_PASCAL+1 */
	type_string = "MACPASCAL";
	break;
    case CC_STDCALL:   /* CC_MACPASCAL+1 */
	type_string = "__stdcall";
	break;
    case CC_SYSCALL:   /* CC_STDCALL+2 */
	type_string = "SYSCALL";
	break;
    case CC_MPWCDECL:   /* CC_SYSCALL+1 */
	type_string = "MPWCDECL";
	break;
    case CC_MPWPASCAL:   /* CC_MPWCDECL+1 */
	type_string = "MPWPASCAL";
	break;
    case CC_MAX:   /* CC_MPWPASCAL+1 */
	type_string = "MAX";
	break;
	/*
	  case CC_RESERVED:   == CC_STDCALL+1  (apparently not defined)
	  type_string = "RESERVED";
	  break;
	  */
    default:
	type_string = "error";
    }
 
    return type_string;
}

/*****************************************************************************
 * emit_fields
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void emit_fields(JNIEnv *env, FIELD_INFO *node)
{
  unsigned short *field_name;
  int field_number;
  VTYPE_INFO *vtinfo;
  VARTYPE vtype;
  TYPEKIND typekind;
  BOOL isStatic; 
  char *type_string;

  for (field_number=0; node; field_number++, node=node->next) {

      field_name = node->field_name;
      vtinfo = node->vtype;
      vtype = vtinfo->vtype;
      typekind = vtinfo->typekind;
      isStatic = node->isStatic;

      type_string = vartype_string_for_java_type(env, vtype);
      
      if (isStatic)
        typelib_output(env, "  public static final %s %ls = ",type_string, field_name);
      else typelib_output(env, "  public final %s %ls = ",type_string, field_name);
      typelib_output(env, "%d;\n\n", node->int_value);
  }
}

/*****************************************************************************
 * emit_methods
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void emit_methods(JNIEnv *env, METHOD_INFO *node)
{
    unsigned short *method_name;
    int method_number, j;
    short i,  cParams; 
    unsigned short varTypeInfo;
    char *type_string;
    char *default_value_string;
    char *invoke_type_string;
    char *arg_type_strings[50];
    VTYPE_INFO ** paramVtypes;
    INVOKEKIND invkind;
    VARTYPE vtype;
    char *variant_type = NULL;
   
    for (method_number=0; node; method_number++, node=node->next) {
      BOOL voidReturn = FALSE;
      VTYPE_INFO *vtinfo;
      TYPEKIND typekind;

      cParams = node->cParams;
      method_name = node->method_name;
      invkind = node->invkind;
      vtinfo = node->vtype;
      vtype = vtinfo->vtype;
      typekind = vtinfo->typekind;
      paramVtypes = node->paramVtypes; 

      if (DISPATCH_PROPERTYPUTREF == invkind) {
           typelib_output(env, "    // Currently unimplemented reference put: 0x%x\n\n",
               node->memid);         
           continue;
       }


      if (typekind == TKIND_ENUM) 
        if (vtinfo->className)
          typelib_output(env, "    // Enumeration type = %s\n", vtinfo->className);

      if (typekind == TKIND_COCLASS || typekind == TKIND_DISPATCH) {
          if (typekind == TKIND_DISPATCH)
            typelib_output(env, "    //  DISPATCH type\n");
          else
            typelib_output(env, "    //  CO_CLASS type\n");
        
          if (vtinfo->className == NULL) {
            type_string = "Variant";
            variant_type = "IDispatch";
          }
          else {
            type_string = vtinfo->className;
          }
      }
      else {
  
        type_string = vartype_string_for_java_type(env, vtype);
        voidReturn = !strcmp(type_string, VOID_TYPE_STRING);
        if (!voidReturn)
          variant_type = vartype_string_for_java_get_method(env, vtype);
      }

      typelib_output(env, "  public %s ",type_string);

      switch (invkind) {
      case DISPATCH_PROPERTYGET: {
           typelib_output(env, "getAx%ls", method_name);
           invoke_type_string = "AX_PROPERTYGET";
           break;
      }
      case DISPATCH_PROPERTYPUT: {
           typelib_output(env, "setAx%ls", method_name);
           invoke_type_string = "AX_PROPERTYSET";
           /*
           type_string = VOID_TYPE_STRING;
           */
           break;
      }
      default: {
           typelib_output(env, "%ls", method_name);
           invoke_type_string = "AX_INVOKE";
           break;
            }
      }
 
      typelib_output(env, " (");
      if (cParams > 0)
      for (i=0; i<cParams; i++) {
          char *type_string;
          TYPEKIND tkind;
          VTYPE_INFO *vtinfo;
        
          varTypeInfo = paramVtypes[i]->vtype;
          vtinfo = paramVtypes[i]; 
          tkind = paramVtypes[i]->typekind;
          
          if (tkind == TKIND_COCLASS || tkind == TKIND_DISPATCH) {
            if (vtinfo->className == NULL) 
              type_string = "Variant";
            else type_string = vtinfo->className;
          }
          else {
            type_string = vartype_string_for_java_type(env, varTypeInfo);
          }          
          arg_type_strings[i] = type_string;
          typelib_output(env,type_string); 
          typelib_output(env, " param%d", i + 1);
          if ((i + 1) < cParams)
            typelib_output(env, ", ");
      }
      typelib_output(env, ")\n");
      
      if(! emitExceptions)
        typelib_output(env,"  {\n");
      else typelib_output(env, "    throws ActiveXException {\n"); 

      typelib_output(env, "    // memid = 0x%x\n\n", node->memid);

      typelib_output(env, "    ParameterVector args = new ParameterVector(%d);\n", cParams);
      for (j=1; j<=cParams; j++) {
        typelib_output(env, "    args.addParameter(param%d);\n", j);
      }
      
      if (! emitExceptions) 
        {
          typelib_output(env, "   try {\n");
        }

      if (voidReturn) {

        
        if (invkind == DISPATCH_PROPERTYGET ||
            invkind == DISPATCH_PROPERTYPUT 
            && FALSE) {
          typelib_output(env,
            "    axInvoke(\"%ls\", %s, true, args);\n",
            method_name, invoke_type_string);
        }
        else {
          typelib_output(env,
            "    axInvoke(0x%x, %s, true, args);\n",
            node->memid, invoke_type_string);
        }

      }
      else {
        typelib_output(env, "    Variant vResult = ");
        
        if ((invkind == DISPATCH_PROPERTYGET ||
            invkind == DISPATCH_PROPERTYPUT)
            && FALSE) {
          typelib_output(env,  
            "axInvoke(\"%ls\", %s, false, args);\n",
            method_name, invoke_type_string);
        }
        else {
          typelib_output(env,
            "axInvoke(0x%x, %s, false, args);\n",
            node->memid, invoke_type_string);
        }
        
        if (strcmp("Variant",type_string) == 0)  {
              typelib_output(env, "    return vResult;\n");
        }
        else {
          typelib_output(env, "    %s result = ", type_string);
        
          if (typekind == TKIND_COCLASS || typekind == TKIND_DISPATCH) { 
            typelib_output(env, "new %s(vResult.getActiveXDispatchableValue());\n", type_string);
          }
          else 
          {
            typelib_output(env, "vResult.get%sValue();\n", variant_type);
          }
          
          typelib_output(env, "    return result;\n");
        }
      }

      if (! emitExceptions) 
      {
        typelib_output(env, "   }\n   catch (ActiveXException e)  {\n");
        typelib_output(env, "    message(AX_ERROR,\"Method invoke failed \" + e);\n"); 
        
        default_value_string = default_value_string_for_java_type(env, vtype);
        
        if (! voidReturn)
          typelib_output(env, "    return %s;\n", default_value_string);

        typelib_output(env, "   }\n"); 
      }

      typelib_output(env, "  }\n\n");            
   }
}


/*****************************************************************************
 * method_for_property_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static METHOD_INFO * method_for_property_descriptor
   (PROPERTY_DESCRIPTOR *property_descriptor, INVOKEKIND kind, short argNumber)     
 {
     unsigned short *get_method_name = NULL;
     short cMethods, i, cParams;
     METHOD_INFO **methods;
     METHOD_INFO *method_info;
     METHOD_INFO *result;
     INVOKEKIND invkind;
          
     cMethods = property_descriptor->cMethods;
     methods = property_descriptor->methods;

     result = NULL;

     for (i = 0; i < cMethods; i++)
     {
        method_info = methods[i];
        
        if (method_info) /* Should not be necessary to check this */ 
        {
          cParams = method_info->cParams;
          invkind = method_info->invkind;
        
          if ((invkind == kind) &&
            (cParams == argNumber))
          {
            result = method_info;
            break;
          }
        }
     }

     return result;
 }

/*****************************************************************************
 * vtype_equal
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOLEAN vtype_equal(VTYPE_INFO *vtype1, VTYPE_INFO *vtype2)
{
    if ((vtype1->vtype == vtype2->vtype) &&
        (vtype1->typekind == vtype2->typekind) &&
        ((vtype1->className && vtype2->className) ?
            (strcmp(vtype1->className, vtype2->className) == 0)
            : TRUE))
          return TRUE;
          else return FALSE;
}

/*****************************************************************************
 * get_methods_for_property_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void get_methods_for_property_descriptor
   (PROPERTY_DESCRIPTOR *property_descriptor,
    METHOD_INFO **pGet_method,
    METHOD_INFO **pSet_method)
 {
   METHOD_INFO *get_method;
   METHOD_INFO *set_method;
   VTYPE_INFO *returnType = NULL;
   VTYPE_INFO *argumentType = NULL;

   get_method =
          method_for_property_descriptor(property_descriptor,
                                         INVOKE_PROPERTYGET,
                                         0);
   set_method =
          method_for_property_descriptor(property_descriptor,
                                         INVOKE_PROPERTYPUT,
                                         1);

   /** Check that the methods involve the same types, because
   * in ActiveX the put methods do not have to involve the same
   * types as the get methods.  In JavaBeans the return value
   * of the get method has to be same as the first argument to
   * the set method.
   */

   if (get_method)
      returnType = get_method->vtype;

   if (set_method)
      argumentType = set_method->paramVtypes[0];

   (*pGet_method) = get_method;
   (*pSet_method) = set_method;

   if (returnType && argumentType)
   {
      if (! vtype_equal(returnType, argumentType))
          (*pSet_method) = NULL; /* Make is read only in the case that 
                                 the types are not compatable */
   }
 }

 /*****************************************************************************
 * name_for_property_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static unsigned short * name_for_property_descriptor
   (PROPERTY_DESCRIPTOR *property_descriptor)
 {
   return property_descriptor->methods[0]->method_name;
 }


 /*****************************************************************************
 * emit_event_listeners
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void emit_event_listeners(JNIEnv *env, 
                                  EVENT_SET_DESCRIPTOR *event_descriptor,
                                  CLASS_INFO *parent)
 {
   CLASS_INFO *last_class_info = NULL;
   CLASS_INFO *class_info;
   
   while (event_descriptor)
   {
     class_info = event_descriptor->class_info;
     
     if (last_class_info && 
         (! strcmp(last_class_info->className,class_info->className)))
     {
       event_descriptor = event_descriptor->next;
       continue;
     }
      
     last_class_info = class_info;

     typelib_output(env, "  public void add%sListener (%sListener l)\n",
                         class_info->className,
                         class_info->className);
     typelib_output(env, "  {\n");
     typelib_output(env, "    try {\n");
     typelib_output(env, "    addActiveXEventListener(l, %sBeanInfo.class);\n",
                                 parent->className);
     typelib_output(env, "    } catch (ActiveXException e) {\n");
     typelib_output(env, "        message(ERROR, \"addActiveXListener failed\" + e);\n");
     typelib_output(env, "    }\n"); 

     typelib_output(env, "  }\n\n");


     typelib_output(env, "  public void remove%sListener (%sListener l)\n",
                         class_info->className,
                         class_info->className);

     typelib_output(env, "  {\n");

     typelib_output(env, "    try {\n");
     typelib_output(env, "      removeActiveXEventListener(l, %sBeanInfo.class);\n",
                                 parent->className);
     typelib_output(env, "    } catch (ActiveXException e) {\n");
     typelib_output(env, "        message(ERROR, \"removeActiveXListener failed\" + e);\n");
     typelib_output(env, "    }\n");

     typelib_output(env, "  }\n\n");

     event_descriptor = event_descriptor->next;
   }

 }

 /*****************************************************************************
 * emit_one_guid
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void emit_one_guid(JNIEnv *env, const GUID *cclsid)
 {
   if (cclsid) {
        typelib_output(env, "    new Guid(0x%x, 0x%x, ",
        cclsid->Data1, cclsid->Data2);
        typelib_output(env, "0x%x,\n             ",
        cclsid->Data3);
        typelib_output(env, "(short) 0x%x, (short) 0x%x, (short) 0x%x, (short) 0x%x,\n",
        cclsid->Data4[0], cclsid->Data4[1], cclsid->Data4[2],
        cclsid->Data4[3]);
        typelib_output(env, "             (short) 0x%x, (short) ",
        cclsid->Data4[4]);
        typelib_output(env, "0x%x, (short) 0x%x, (short) 0x%x)", 
        cclsid->Data4[5], cclsid->Data4[6], cclsid->Data4[7]);
      } else {
        typelib_output(env, "    new Guid()");
      }
 }

/*****************************************************************************
 * emit_one_beaninfo
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void emit_one_beaninfo(JNIEnv *env, 
                              BEAN_INFO *node,
                              CLASS_INFO *parent)                              
{
  char *beanInfoName;
  char *beanInfoFileName;
  char *packagename;
  char *className;
  PROPERTY_DESCRIPTOR *property_descriptor;
  METHOD_DESCRIPTOR *method_descriptor;
  EVENT_SET_DESCRIPTOR *event_descriptor;
  short i, cParams;
  VTYPE_INFO **paramVtypes;
  unsigned short *property_name;
  METHOD_INFO *get_method;
  METHOD_INFO *set_method;
  unsigned short *get_method_name;
  unsigned short *set_method_name;
  
  beanInfoName = node->beanInfoName;
  beanInfoFileName = node->beanInfoFileName;
  packagename = parent->library->packageName;
  className = parent->className;

  if (beanInfoName == NULL) {
    jprintf(env, DERROR, "Unable to open BeanInfo file for emitting");
    return;
  }

  if (beanInfoFileName == NULL) {
    jprintf(env, DERROR, "Unable to open BeanInfo file for emitting");
    return;
  }

  open_file_for_emitting(env, beanInfoFileName);

  if (gfp) {

    if (user_chosen_emit_package) {
      typelib_output(env, "package %s.%s;\n\n", 
        user_chosen_emit_package,
        packagename);
    } else {
      typelib_output(env, "package %s.%s;\n\n", 
        DEFAULT_EMIT_PACKAGE,
        packagename);
    }
    typelib_output(env, "import com.gensym.com.*;\n\n");
    
    typelib_output(env, "import java.awt.Color;\n");
    typelib_output(env, "import java.util.Vector;\n");
    typelib_output(env, "import java.util.Date;\n\n");
    
    typelib_output(env, "import java.beans.PropertyDescriptor;\n");
    typelib_output(env, "import java.beans.MethodDescriptor;\n");

    typelib_output(env, "public class %s extends com.gensym.com.ActiveXBeanInfo\n", beanInfoName);
    typelib_output(env, "{\n");

    property_descriptor = node->properties_head;
    method_descriptor = node->methods_head;
    event_descriptor = node->events_head;

    typelib_output(env, "  {\n");
    typelib_output(env, "    setup_properties();\n");
    typelib_output(env, "    setup_methods();\n");
    typelib_output(env, "    setup_events();\n");
    typelib_output(env, "  }\n\n");

    typelib_output(env, "  private void setup_properties() throws ExceptionInInitializerError \n");
    typelib_output(env, "  {\n");
    
    if ((property_descriptor != NULL)) {
      typelib_output(env, "   try {\n");
      typelib_output(env, "    Class beanClass = ");
    
      typelib_output(env, "%s.%s.%s.class;\n\n", 
        (user_chosen_emit_package ? user_chosen_emit_package : DEFAULT_EMIT_PACKAGE),
        packagename,
        className);

      typelib_output(env, "    PropertyDescriptor propertyDescriptor;\n");
      
      typelib_output(env, "    propertyDescriptor =\n");
      typelib_output(env, 
        "         new PropertyDescriptor(\"background\", beanClass, \"getBackground\", \"setBackground\");\n");
      typelib_output(env, "    addPropertyDescriptor(propertyDescriptor);\n");

      typelib_output(env, "    propertyDescriptor =\n");
      typelib_output(env, 
        "         new PropertyDescriptor(\"activateOnLoad\", beanClass, \"getActivateOnLoad\", \"setActivateOnLoad\");\n");
      typelib_output(env, "    addPropertyDescriptor(propertyDescriptor);\n");


      while(property_descriptor != NULL)
      {

        property_name = name_for_property_descriptor(property_descriptor);

        if (! property_name)
        {
          property_descriptor = property_descriptor->next;
          continue;
        }

        /** Need to get the method_infos for these
        * then compare the type names of the first argument
        * of the setter against the return argument of the getter
        * Eliminate those that are not the same.. because the
        * Java Beans restriction on properties is commonly followed
        * but is not required in ActiveX.
        */

        get_methods_for_property_descriptor(property_descriptor,
                                            &get_method,
                                            &set_method);

        if (get_method)
          get_method_name = get_method->method_name;
        else get_method_name = NULL;
        
        if (set_method)
          set_method_name = set_method->method_name;
        else set_method_name = NULL;


        if ((!get_method_name) && (!set_method_name))
        {
          property_descriptor = property_descriptor->next;
          continue;
        }


        typelib_output(env, "    propertyDescriptor =\n");

        if (!get_method_name)
          typelib_output(env, 
            "         new PropertyDescriptor(\"ax%ls\", beanClass, null, \"setAx%ls\");\n",
                       property_name, set_method_name);
        else if (! set_method_name) 
          typelib_output(env, 
            "         new PropertyDescriptor(\"ax%ls\", beanClass, \"getAx%ls\", null);\n",
                       property_name, get_method_name);
        else typelib_output(env, 
            "         new PropertyDescriptor(\"ax%ls\", beanClass, \"getAx%ls\", \"setAx%ls\");\n",
                       property_name, get_method_name, set_method_name);
        
        /*
        typelib_output(env, "         new PropertyDescriptor(\"ax%ls\", beanClass);\n",
          property_descriptor->methods[0]->method_name);

        */

        if (property_descriptor->isExpert)
          typelib_output(env, "    propertyDescriptor.setExpert(true);\n");

        if (property_descriptor->isHidden)
          typelib_output(env, "    propertyDescriptor.setHidden(true);\n");

        if (property_descriptor->isBindable)
          typelib_output(env, "    propertyDescriptor.setBound(true);\n");


        typelib_output(env, "    addPropertyDescriptor(propertyDescriptor);\n");
        
        property_descriptor = property_descriptor->next;
      } 

      typelib_output(env, "   }\n");
      typelib_output(env, "   catch (Exception e) {\n");
      typelib_output(env, "     e.printStackTrace();\n");
      typelib_output(env, "     throw new ExceptionInInitializerError(e.toString());\n");
      typelib_output(env, "   }\n"); 
      }
      typelib_output(env, "  }\n\n");

      typelib_output(env, "  private void setup_methods() throws ExceptionInInitializerError \n");
      typelib_output(env, "  {\n");

      if (method_descriptor != NULL)
      {
        typelib_output(env, "    MethodDescriptor methodDescriptor;\n");
      
        typelib_output(env, "   try {\n");
        typelib_output(env, "    Class beanClass = ");
    
        typelib_output(env, "%s.%s.%s.class;\n\n", 
        (user_chosen_emit_package ? user_chosen_emit_package : DEFAULT_EMIT_PACKAGE),
        packagename,
        className);

        while(method_descriptor != NULL)
        {
          INVOKEKIND invkind;

          invkind = method_descriptor->method->invkind;
        
          if (DISPATCH_PROPERTYPUTREF == invkind) 
          {
            method_descriptor = method_descriptor->next;
            continue;
          }

          typelib_output(env, "    methodDescriptor =\n");
        
          switch (invkind) {
          case DISPATCH_PROPERTYGET: {
            typelib_output(env, "         new MethodDescriptor(beanClass.getMethod(\"getAx%ls\", \n",
              method_descriptor->method->method_name);
            break;
                                     }

          case DISPATCH_PROPERTYPUT: {
            typelib_output(env, "         new MethodDescriptor(beanClass.getMethod(\"setAx%ls\", \n",
              method_descriptor->method->method_name);
            break;
                                     }
          default: {
            typelib_output(env, "         new MethodDescriptor(beanClass.getMethod(\"%ls\", \n",
              method_descriptor->method->method_name);
                   }
          }
        
          typelib_output(env, "              new Class[] {\n");

          cParams = method_descriptor->method->cParams;
          paramVtypes = method_descriptor->method->paramVtypes;
        

          if (cParams > 0)
            for (i=0; i<cParams; i++) {
            char *type_string;
            TYPEKIND tkind;
            VTYPE_INFO *vtinfo;
            unsigned short varTypeInfo;
            
            varTypeInfo = paramVtypes[i]->vtype;
            vtinfo = paramVtypes[i]; 
            tkind = paramVtypes[i]->typekind;

            if (tkind == TKIND_COCLASS || tkind == TKIND_DISPATCH) {
            if (vtinfo->className == NULL) 
              type_string = "Variant";
            else type_string = vtinfo->className;
            }
            else {
              type_string = vartype_string_for_java_type(env, varTypeInfo);
            }          

            if (i == (cParams - 1))
                typelib_output(env, 
                "                           %s.class\n", type_string);
            else typelib_output(env,
                "                           %s.class,\n", type_string);

          }

        
          typelib_output(env, "              }));\n");

          if (method_descriptor->isExpert)
          typelib_output(env, "    methodDescriptor.setExpert(true);\n");
          
        if (method_descriptor->isHidden)
          typelib_output(env, "    methodDescriptor.setHidden(true);\n");
        
        typelib_output(env, "    addMethodDescriptor(methodDescriptor);\n");
        
        method_descriptor = method_descriptor->next;
      } 

      typelib_output(env, "   }\n");
      typelib_output(env, "   catch (Exception e) {\n");
      typelib_output(env, "     e.printStackTrace();\n");
      typelib_output(env, "     throw new ExceptionInInitializerError(e.toString());\n");
      typelib_output(env, "   }\n"); 
    }
    typelib_output(env, "  }\n");


    typelib_output(env, "  private void setup_events() throws ExceptionInInitializerError \n");
    typelib_output(env, "  {\n");

    if ((event_descriptor)) {
      CLASS_INFO *class_info;
      METHOD_INFO * method;
      unsigned short *last_method_name = NULL;

      typelib_output(env, "    ActiveXEventSetDescriptor eventSetDescriptor;\n");

      typelib_output(env, "   try {\n");
      typelib_output(env, "    Class listenerType;\n");
      typelib_output(env, "    Class beanClass = ");
    
      typelib_output(env, "%s.%s.%s.class;\n\n", 
        (user_chosen_emit_package ? user_chosen_emit_package : DEFAULT_EMIT_PACKAGE),
        packagename,
        className);

      while(event_descriptor)
      {
        class_info = event_descriptor->class_info;
       
        typelib_output(env, "  listenerType = %s.%s.%sListener.class;\n\n", 
        (user_chosen_emit_package ? user_chosen_emit_package : DEFAULT_EMIT_PACKAGE),
        class_info->library->packageName,
        class_info->className);

        typelib_output(env, "  eventSetDescriptor = new ActiveXEventSetDescriptor(\n");
        typelib_output(env, "     beanClass,\n");
        
        emit_one_guid(env, class_info->cclsid);
        typelib_output(env, ",\n");

        typelib_output(env, "     \"%s\",\n", class_info->className);
        typelib_output(env, "     listenerType,\n");
        typelib_output(env, "     new String[] {\n");

        /* A list of method names */

        method = class_info->methods_head;
        while (method)
        {
          if ((last_method_name != NULL) &&
              (wcscmp(last_method_name, method->method_name) == 0))
          {
          }
          else {
              if (! (method->next)) {
                typelib_output(env, "     \"%ls\"\n", method->method_name);    
              break;
              } else typelib_output(env, "     \"%ls\",\n", method->method_name);    
          }
          last_method_name = method->method_name;
          method = method->next;          
        }
                
        typelib_output(env, "                  },\n");

        /* A list of DISPID's to associate with the method names */
        typelib_output(env, "     new int[] {\n");
        
        method = class_info->methods_head;
        last_method_name = NULL;
        while (method)
        {
          if ((last_method_name != NULL) &&
              (wcscmp(last_method_name, method->method_name) == 0))
          {
          }
          else {
              if (! (method->next)) {
                typelib_output(env, "     0x%x\n", method->memid);
              break;
              } else typelib_output(env, "     0x%x,\n", method->memid);    
          }
          last_method_name = method->method_name;
          method = method->next;          
        }

        typelib_output(env, "                  },\n");
           
        typelib_output(env, "     \"add%sListener\",\n", class_info->className);
        typelib_output(env, "     \"remove%sListener\");\n\n", class_info->className);

        typelib_output(env, "  addEventSetDescriptor(eventSetDescriptor);\n\n");  
        
        event_descriptor = event_descriptor->next;
      }

      typelib_output(env, "   }\n");
      typelib_output(env, "   catch (Exception e) {\n");
      typelib_output(env, "     e.printStackTrace();\n");
      typelib_output(env, "     throw new ExceptionInInitializerError(e.toString());\n");
      typelib_output(env, "   }\n"); 
    }

    typelib_output(env, "  }\n");

    typelib_output(env, "}\n");
    
    fclose(gfp);
    gfp = NULL;
  }
}

 
/*****************************************************************************
 * emit_one_class
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void emit_one_class(JNIEnv *env, CLASS_INFO *node,
                          int count, BSTR bstrName, 
                          BSTR bstrDocString, BSTR bstrHelpFile) 
{
    long hr;
    unsigned short numFunctions, numProperties;
    int type_info_number;

    ITypeInfo *pTypeInfo;
    TYPEATTR *pTypeAttr;
    TYPEKIND typekind;
    const GUID *cclsid;
    char *classname;
    char *packagename;
    char *filename;
    BSTR bstrName2, bstrDocString2, bstrHelpFile2;
    BOOL is_insertable = node->isInsertable;
    BOOL is_control = node->isControl;
    BOOL is_creatable = node->isCreatable;
    BOOL is_interface = node->isInterface;
    BOOL is_licensed = node->isLicensed;

    pTypeInfo = node->pTypeInfo; 
    type_info_number = node->containing_type_info;

    /*
    hr = pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr);
    if (FAILED(hr) || !pTypeAttr) {
      jprintf(env, DERROR, "Could not get type attributes for type library");
      return;
    }
    */

    bstrName2 = node->bstrName;
    bstrDocString2 = node->bstrDocString;
    bstrHelpFile2 = node->bstrHelpFile; 
    cclsid = node->cclsid;
    classname = node->className;
    packagename = node->library->packageName;
    filename = node->sourceFileName;

    if (classname == NULL) {
      jprintf(env, DERROR, "Unable to open file for emitting");
      return;
    }

    if (filename == NULL) {
      jprintf(env, DERROR, "Unable to open file for emitting");
      return;
    }
    
    if (node->beanInfo)
      emit_one_beaninfo(env, node->beanInfo, node);

    open_file_for_emitting(env, filename);

    if (gfp) {
      
      if (user_chosen_emit_package) {
        typelib_output(env, "package %s.%s;\n\n", 
                                     user_chosen_emit_package,
                                     packagename);
      } else {
        typelib_output(env, "package %s.%s;\n\n", 
                             DEFAULT_EMIT_PACKAGE,
                             packagename);
      }
      typelib_output(env, "import com.gensym.com.*;\n");
      typelib_output(env, "import java.awt.Color;\n\n");
      typelib_output(env, "import java.util.Date;\n");
      typelib_output(env, "import java.util.Vector;\n\n\n");
      
      if (is_interface) {
          typelib_output(env, "public interface %s\n", classname);
          typelib_output(env, "{\n\n");
      }
      else {
      
        typelib_output(env, "public class %s extends com.gensym.com.", classname);
      
        if (is_creatable) {
          typelib_output(env, "ActiveXDefaultComponentImpl\n");
          typelib_output(env, "{\n");
          typelib_output(env, "  private boolean hasBeenAdded = false;\n\n\n");      
        }
        else {
          typelib_output(env, "ActiveXDispatchableImpl\n");
          typelib_output(env, "{\n");
        }
      }
 
      if (is_interface)
        typelib_output(env, "  public static final Guid classID =\n");      
      else typelib_output(env, "  private static Guid classID =\n");      
    
      emit_one_guid(env, cclsid);
      typelib_output(env, ";\n\n");
  
      if (is_creatable) {      
       
       if (is_licensed) 
       {
         typelib_output(env, "  protected License license");
         if (node->license)
           typelib_output(env, " = new License(\"%ls\")", node->license);      
         typelib_output(env, ";\n\n");
       }
       
       if (is_insertable || is_control)
          typelib_output(env, "  public %s () {}\n\n\n", classname);
        else {
          typelib_output(env,  "  public %s () {\n", classname);
          typelib_output(env,  "    initializeProxy();\n");
          typelib_output(env,  "  }\n\n\n");
        }
        typelib_output(env, "  public synchronized void addNotify () {\n");
        typelib_output(env, "    super.addNotify();\n");
        typelib_output(env, "\n");
        typelib_output(env, "    setVisible(true);\n");
        typelib_output(env, "    hasBeenAdded = true;\n\n");
        typelib_output(env, "    if ((hWnd == null) || (hWnd.handleToPeer == Hwnd.NO_HWND)) {\n");
        typelib_output(env, "      message(AX_ERROR, \"Failed to obtain HWND for \" + this);\n");
        typelib_output(env, "    } else if (classID.isNullGuid()) {\n");
        typelib_output(env, "      message(AX_ERROR, \"Failed to obtain CLSID for \" + this);\n");
        typelib_output(env, "    } else {\n");
        typelib_output(env, "      message(AX_PROGRESS, \"HWND for \" + this + \" = \" + hWnd);\n");
        typelib_output(env, "      initializeProxy();\n");
        typelib_output(env,"     }\n");
        typelib_output(env, "  }\n");
        typelib_output(env, "\n\n");           
        
        typelib_output(env, "  public synchronized void initializeProxy () {\n");
        typelib_output(env, "      if (axProxy == null) {\n");
        typelib_output(env, "        try {\n");
        typelib_output(env, "          axProxy = new ActiveXProxy(hWnd, ");
        if (is_insertable && (! is_control)) {
          typelib_output(env, "new ActiveXModes(classID");
        } else {
          typelib_output(env, "new ActiveXModes(classID, AX_NOT_INSERTABLE");
        }
        if (is_licensed)
        {
          typelib_output(env, ", license),\n");
        }
        else typelib_output(env,"),\n");
        typelib_output(env, "                                     this);\n");
        typelib_output(env, "          axDispatch = new ActiveXDispatchableImpl(AX_NO_DISPATCH, axProxy);\n");
        typelib_output(env, "        } catch(ActiveXException e) {\n");    
        typelib_output(env, "           message(AX_ERROR, \"Failed to create Proxy\" + e);\n");
        typelib_output(env, "           }\n");
        typelib_output(env, "        message(AX_DATA_DUMPS, \"made new ActiveXProxy! = \" + axProxy);\n");
        typelib_output(env, "        message(AX_PROGRESS, \"AddNotify: Inserted object  \" + axProxy);\n");
        typelib_output(env, "      }\n");
        typelib_output(env," }\n");
        typelib_output(env, "\n\n");           
      }
      
      if (! is_interface) {
        typelib_output(env, "  public %s (ActiveXDispatchable axDispatch) throws ActiveXCastException\n", classname);
        typelib_output(env, "  {\n");
        typelib_output(env, "       super(axDispatch);\n");
        typelib_output(env, "       axProxy.checkCast(getDispatchPointer(), classID);\n");
        typelib_output(env, "  }\n\n");

        typelib_output(env, "  public static Guid getStaticClassID ()\n");
        typelib_output(env, "  {\n");
        typelib_output(env, "      return classID;\n");
        typelib_output(env, "  }\n\n");

        typelib_output(env, "  public Guid getClassID ()\n");
        typelib_output(env, "  {\n");
        typelib_output(env, "      return classID;\n");
        typelib_output(env, "  }\n\n");
      }

      if (bstrName)
        typelib_output(env, "    // Library name is: %ls\n", bstrName);
      if (bstrDocString)
        typelib_output(env, "    // DocString is: %ls\n", bstrDocString);
      if (bstrHelpFile)
        typelib_output(env, "    // Help file is: %ls\n", bstrHelpFile);
      if (count == 1) {
        typelib_output(env, "    // There is 1 TypeInfo in the library\n\n");
      } else {
        typelib_output(env, "    // There are %d TypeInfos in the library\n\n", count);
      }
      
      hr = pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr);
      if (FAILED(hr) || !pTypeAttr) {
        jprintf(env, DERROR, "Could not get type attributes for type library");
        return;
      }
    
      typekind = pTypeAttr->typekind;
     
      
      typelib_output(env, "/* Type info #%d\n", type_info_number);
      if (typekind == TKIND_ENUM) {
        typelib_output(env, "    An enumeration type.\n");  
      }
      if (typekind == TKIND_DISPATCH) {
        typelib_output(env, "    A set of methods and properties that ");
        typelib_output(env, "are accessible through IDispatch::Invoke.\n");
      }
      if (typekind == TKIND_COCLASS) {
        typelib_output(env, "    A set of implemented component object interfaces.\n");
      }
      if (bstrName2)
        typelib_output(env, "    Type info name is: %ls\n", bstrName2);
      if (bstrDocString2)
        typelib_output(env, "    Doc string is: %ls\n", bstrDocString2);
      if (bstrHelpFile2)
        typelib_output(env, "    Help file is: %ls\n", bstrHelpFile2);

      if ((typekind == TKIND_COCLASS || typekind == TKIND_DISPATCH)) {
        numFunctions = pTypeAttr->cFuncs;
        numProperties = pTypeAttr->cVars;        
        if (numFunctions == 0) {
          typelib_output(env, "    Type Info contains zero functions.\n");
        } else {
          typelib_output(env, "    Type Info contains %d functions.\n",
            numFunctions);
        }
        if (numProperties == 0) {
          typelib_output(env, "    Type Info contains zero properties.\n");
        } else {
          typelib_output(env, "    Type Info contains %d properties.\n",
            numProperties);
        }
      }
     typelib_output(env, " */\n\n");

    if (node->fields_head) {
        emit_fields(env, node->fields_head);
    }
      
    if (node->methods_head) {
      emit_methods(env,node->methods_head);
    } else {
      if (! is_interface)
        typelib_output(env, "  // No methods found\n\n");
    }

    if (node->beanInfo) {
      if (node->beanInfo->events_head) {
        emit_event_listeners(env, node->beanInfo->events_head, node);
      } else {
        if (! is_interface)
          typelib_output(env, "  // No event listeners found\n\n");
      }
    }

    if (! is_interface) {
      typelib_output(env, "public String toString() {\n");
      typelib_output(env, "    return \"<%s, super = \" + super.toString() + \">\";\n",classname);
      typelib_output(env, "}\n\n");
    }

    if (pTypeAttr)
      pTypeInfo->lpVtbl->ReleaseTypeAttr(pTypeInfo, pTypeAttr);

    typelib_output(env, "\n}\n\n");

    node->hasBeenEmitted = TRUE;
    fclose(gfp);
    gfp = NULL;
    }
}

/*****************************************************************************
 * emit_one_event_class
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void emit_one_event_class(JNIEnv *env, EVENT_SET_DESCRIPTOR *event_descriptor) 
 {
   CLASS_INFO *class_info;
   char *classname;
   char *filename;
   char *packagename;

   class_info = event_descriptor->class_info;
   classname = class_info->className;
   packagename = class_info->library->packageName;
   filename = class_info->eventSourceFileName;

   if (classname == NULL) {
     jprintf(env, DERROR, "Unable to open file for emitting");
     return;
   }

   if (filename == NULL) {
     jprintf(env, DERROR, "Unable to open file for emitting");
     return;
    }

   open_file_for_emitting(env, filename);

   if (gfp) {
      
     if (user_chosen_emit_package) {
       typelib_output(env, "package %s.%s;\n\n", 
         user_chosen_emit_package,
         packagename);
     } else {
       typelib_output(env, "package %s.%s;\n\n", 
         DEFAULT_EMIT_PACKAGE,
         packagename);
     }

     typelib_output(env, "import com.gensym.com.*;\n");
     typelib_output(env, "import java.util.Vector;\n\n");

     typelib_output(env, "public class %sEvent extends ActiveXEvent\n",
                          classname);
     typelib_output(env, "{\n\n");

     typelib_output(env, "  public %sEvent(Object source, String eventName, Variant[] arguments)\n",
                            classname);
     typelib_output(env, "  {\n");     
     typelib_output(env, "    super(source, eventName, arguments);\n");     
     typelib_output(env, "  }\n\n");     

     typelib_output(env, "}\n");     
     fclose(gfp);
     gfp = NULL;

     class_info->hasBeenEmittedAsEvent = TRUE;
   }
 }


 /*****************************************************************************
 * emit_methods_as_listener_stubs
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

  static void emit_methods_as_listener_stubs
    (JNIEnv *env, METHOD_INFO *node, char *eventClassName)
  {
    unsigned short *method_name;
    while (node)
    {
      method_name = node->method_name;
      typelib_output(env, "  public void %ls (%sEvent e);\n\n",
                          method_name, eventClassName);
     
      node = node->next;
    }

  }

/*****************************************************************************
 * emit_one_event_listener
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void emit_one_event_listener(JNIEnv *env, EVENT_SET_DESCRIPTOR *event_descriptor) 
 {
   CLASS_INFO *class_info;
   char *classname;
   char *filename;
   char *packagename;

   class_info = event_descriptor->class_info;
   classname = class_info->className;
   packagename = class_info->library->packageName;
   filename = class_info->listenerSourceFileName;

   if (classname == NULL) {
     jprintf(env, DERROR, "Unable to open file for emitting");
     return;
   }

   if (filename == NULL) {
     jprintf(env, DERROR, "Unable to open file for emitting");
     return;
    }

   open_file_for_emitting(env, filename);

   if (gfp) {
      
     if (user_chosen_emit_package) {
       typelib_output(env, "package %s.%s;\n\n", 
         user_chosen_emit_package,
         packagename);
     } else {
       typelib_output(env, "package %s.%s;\n\n", 
         DEFAULT_EMIT_PACKAGE,
         packagename);
     }

     typelib_output(env, "import com.gensym.com.*;\n");
     typelib_output(env, "public interface %sListener extends ActiveXEventListener\n",
                          classname);
     typelib_output(env, "{\n\n");

     if (class_info->methods_head) {
      emit_methods_as_listener_stubs(env,class_info->methods_head,classname);
     } 

     typelib_output(env, "}\n");     
     fclose(gfp);
     gfp = NULL;

     class_info->hasBeenEmittedAsListener = TRUE;
   }

 }


/*****************************************************************************
 * emit_one_library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void emit_one_library(JNIEnv *env, LIBRARY_INFO *libInfo) 
 {
   CLASS_INFO *node;
   int i, count, j, len;
   BSTR bstrName, bstrDocString, bstrHelpFile;
   char *packageName;
   char *subDirName;
   EVENT_SET_DESCRIPTOR *event_sources;

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
     emit_one_class(env, node, count, 
                    bstrName, bstrDocString, bstrHelpFile);
   }

   event_sources = libInfo->event_sources_head;
   while(event_sources)
   {
      emit_one_event_listener(env, event_sources);
      emit_one_event_class(env, event_sources);
      event_sources = event_sources->next;
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
 static void emit_everything(JNIEnv *env)
 {
   LIBRARY_INFO *node;
   int i;

   node = libraries_head;
   for (i=0; node; i++, node=node->next) {
      emit_one_library(env,node);
   }
 }


 /*****************************************************************************
 * reclaim_one_vtype
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications: 
 *****************************************************************************/
static void reclaim_one_vtype(JNIEnv *env, VTYPE_INFO *vtypeInfo)
{
  char *className;
  char *fullPackageClassName;

  className = vtypeInfo->className;

  if (className)
    free(className);

  fullPackageClassName = vtypeInfo->descriptor;

  if(fullPackageClassName)
    free(fullPackageClassName);
}

 /*****************************************************************************
 * reclaim_one_method
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void reclaim_one_method(JNIEnv *env, METHOD_INFO *methodInfo)
{
  unsigned short * methodName;
  short cParams;
  VTYPE_INFO * vtype;
  VTYPE_INFO ** paramVtypes;
  short i;

  methodName = methodInfo->method_name;
  if (methodName)
      free(methodName);

  cParams = methodInfo->cParams;
  if (cParams > 0)
  {
    paramVtypes = methodInfo->paramVtypes;
    if (paramVtypes)
    {
      for (i = 0; i < cParams; i++)
      {
        vtype = paramVtypes[i];
        if (vtype)
          reclaim_one_vtype(env, vtype);
      }

      /* The paramVtypes array is allocated with one malloc */
      free(paramVtypes);
    }
  }
}


 /*****************************************************************************
 * reclaim_one_class
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void reclaim_one_class(JNIEnv *env, CLASS_INFO *classInfo)
{
  METHOD_INFO *node;
  METHOD_INFO *nextNode;
  BSTR bstrName;
  BSTR bstrDocString;
  BSTR bstrHelpFile;

  bstrName = classInfo->bstrName;
  if (bstrName != NULL)
    SysFreeString(bstrName);

  bstrDocString = classInfo->bstrDocString;
  if (bstrDocString != NULL)
    SysFreeString(bstrDocString);

  bstrHelpFile = classInfo->bstrHelpFile;
  if (bstrHelpFile != NULL)
    SysFreeString(bstrHelpFile);

  node = classInfo->methods_head;
  while (node != NULL) 
  {
    reclaim_one_method(env,node);
    nextNode = node->next;
    free(node);
    node = nextNode;
  }
}


 /*****************************************************************************
 * reclaim_one_library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void reclaim_one_library(JNIEnv *env, LIBRARY_INFO *libInfo)
{
  CLASS_INFO *node;
  CLASS_INFO *nextNode;

  node = libInfo->classes_head;
  while (node != NULL)
  {
    reclaim_one_class(env,node);
    nextNode = node->next;
    free(node);
    node = nextNode;
  }
}

 /*****************************************************************************
 * reclaim_everything
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void reclaim_everything(JNIEnv *env)
{
  LIBRARY_INFO *node;
  LIBRARY_INFO *nextNode;

  node = libraries_head;
  while (node != NULL)
  {
    reclaim_one_library(env,node);
    nextNode = node->next;
    free(node);
    node = nextNode;
  }

  libraries_head = NULL;
  libraries_tail = NULL;
}

 /*****************************************************************************
 * collect_library_information_1
 *
 *   Description: Abstracted from collect_library_information so that info
 *     can be collected without having to create a LIBRARY_INFO structure
 *   Input Arguments:
 *   Returns:
 *   Notes: 
 *     -----
 *   Modifications:
 *****************************************************************************/

 HRESULT collect_library_information_1(JNIEnv *env,
                                    ITypeLib *pTlib,
                                    BSTR *pBstrName,
                                    BSTR *pBstrDocString,
                                    BSTR *pBstrHelpFile,
                                    const GUID ** pLibid,
                                    int *pTypeCount,
                                    unsigned short *pMajorVersion,
                                    unsigned short *pMinorVersion) {

  HRESULT hr;
  TLIBATTR FAR *pLibAttr;
  
  hr = pTlib->lpVtbl->GetDocumentation(pTlib,-1,pBstrName,pBstrDocString,NULL,
    pBstrHelpFile);

  if (FAILED(hr)) {
      jprintf(env, DERROR, "Failed to get documentation for type library");
      return hr;
  }

  hr = pTlib->lpVtbl->GetLibAttr(pTlib,&pLibAttr);

  if (FAILED(hr))
    return hr;

  if (pLibid)
    (* pLibid) = copy_guid(&(pLibAttr->guid));

  if (pMajorVersion)
    (* pMajorVersion) = pLibAttr->wMajorVerNum;

  if (pMinorVersion)
    (* pMinorVersion) = pLibAttr->wMinorVerNum;

  pTlib->lpVtbl->ReleaseTLibAttr(pTlib, pLibAttr);

  (*pTypeCount) = pTlib->lpVtbl->GetTypeInfoCount(pTlib);
  
  return hr;
}



 /*****************************************************************************
 * collect_library_information
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

HRESULT collect_library_information(JNIEnv *env,
                                    ITypeLib *pTlib,
                                    LIBRARY_INFO *libInfo)                            
{        
  HRESULT hr =
    collect_library_information_1(env,pTlib,
    &(libInfo->bstrName),
    &(libInfo->bstrDocString),
    &(libInfo->bstrHelpFile),
    &(libInfo->libid),
    &(libInfo->typeCount),
    &(libInfo->majorVersion),
    &(libInfo->minorVersion));

  /* Calculate the name of the package to be used for
     this library 
   */
  libInfo->packageName = 
    make_packagename(libInfo->bstrName,
                     libInfo->majorVersion,
                     libInfo->minorVersion);
  return hr;
}

 /*****************************************************************************
 * collect_library_details
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

static void collect_library_details(JNIEnv *env, ITypeLib *pTlib, 
                                    LIBRARY_INFO *libInfo)
{
  int i, count;
  HRESULT hr;
  ITypeInfo *pTypeInfo;

  count = libInfo->typeCount;

  for (i=0; i<count; i++) {
    hr = pTlib->lpVtbl->GetTypeInfo(pTlib, i, &pTypeInfo);
    if (SUCCEEDED(hr)) {
      jprintf(env, PROGRESS, "Reading typeinfo #%d", i);
      collect_type_information(env, libInfo, i, pTypeInfo);
    } else {
      jprintf(env, DERROR, "Failed to get type info #%d.  HR = 0x%x", i, hr);
    }
  }
}

 /*****************************************************************************
 * get_reference_type
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

static HRESULT get_reference_type(JNIEnv *env, ITypeInfo *pTypeInfo,
                                  TYPEDESC *tdesc, ITypeInfo ** ppRefTypeInfo)
{
  HRESULT hr = E_FAIL;
  HREFTYPE href = tdesc->hreftype;
  struct FARSTRUCT tagTYPEDESC FAR *lptdesc;
  struct FARSTRUCT tagARRAYDESC FAR *lpadesc;
  TYPEDESC derivedTDesc;

  switch (tdesc->vt) {
    case VT_USERDEFINED: {
      hr = pTypeInfo->lpVtbl->GetRefTypeInfo(pTypeInfo,href,ppRefTypeInfo);
      break;
    }
    case VT_PTR: {
      lptdesc = tdesc->lptdesc;
      jprintf(env,DETAIL,"Type of VT_PTR: %d\n", lptdesc->vt);
      hr = get_reference_type(env,pTypeInfo,lptdesc,ppRefTypeInfo);
      break;
    }
    case VT_SAFEARRAY: {
      lpadesc = tdesc->lpadesc;
      derivedTDesc = lpadesc->tdescElem;
      jprintf(env,DETAIL,"Type of VT_SAFEARRAY: %d\n", derivedTDesc.vt);
      jprintf(env,DETAIL,"Dimensions of VT_SAFEARRAY: %d\n", lpadesc->cDims);
      hr = get_reference_type(env,pTypeInfo,&derivedTDesc,ppRefTypeInfo);
      break;
    }
  }

  return hr;
}

/*****************************************************************************
 * get_vtype_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void get_vtype_info (JNIEnv *env, 
                            LIBRARY_INFO *libInfo,
                            ITypeInfo  *pTypeInfo, 
                            TYPEDESC *pTDesc,
                            VTYPE_INFO ** vtypeInfo)
{  
  HRESULT hr;
  ITypeInfo *pRefTypeInfo;
  unsigned short vartype;
                               
  (*vtypeInfo) = (VTYPE_INFO *) malloc(sizeof(VTYPE_INFO));
  initialize_vtype_info(*vtypeInfo);
  (*vtypeInfo)->vtype = pTDesc->vt;
  (*vtypeInfo)->createLocation = LOCATION_REQUIRED;

  hr = get_reference_type(env, pTypeInfo,pTDesc,&pRefTypeInfo);

  if (FAILED(hr)) {
    /* If we get here and we do not have a pointer or an array we
       can assume we have a specific primative type. */
    if (pTDesc->vt != VT_PTR && pTDesc->vt != VT_SAFEARRAY)
      return;

    vartype = 0;

    if (pTDesc->vt == VT_PTR) {
      /* This a pointer to a type, OR with the VT_BYREF flag.
         and move down a level of description.*/
      vartype = vartype | VT_BYREF;
      pTDesc = pTDesc->lptdesc;
    }

    if (pTDesc->vt == VT_SAFEARRAY) {
      /* This a pointer to a type, OR with the VT_BYREF flag.
         and move down a level of description.*/
      vartype = vartype | VT_ARRAY;
      pTDesc = pTDesc->lptdesc;
    }
    

    /* We should now be down to a primitive type */
    vartype = vartype | pTDesc->vt;

    /* Check to make sure we go a primative type. */
    switch (vartype & 0xFF) {
    case VT_I2:
    case VT_I4:
    case VT_R4:
    case VT_R8:
    case VT_CY:
    case VT_DATE:
    case VT_BSTR:
    case VT_DISPATCH:
    case VT_ERROR:
    case VT_BOOL:
    case VT_VARIANT:
    case VT_UNKNOWN:
    case VT_UI1:
      (*vtypeInfo)->vtype = vartype;
    }

    return;
  }

  if (! FAILED(hr)) {
    TYPEATTR *typeAttr;
    ITypeLib *containingTypeLib;
    int position;
    BSTR bstrName; 
    TYPEKIND tkind;

    hr = pRefTypeInfo->lpVtbl->GetTypeAttr(pRefTypeInfo, &typeAttr);

    tkind = typeAttr->typekind;
    (*vtypeInfo)->typekind = tkind;
    
    hr = pRefTypeInfo->lpVtbl->GetDocumentation(pRefTypeInfo,-1,&bstrName,NULL,NULL,
        NULL);

    switch(tkind) {
    case TKIND_DISPATCH:
      jprintf(env,PROGRESS,"A dispatchable interface");
      (*vtypeInfo)->className = make_classname_from_wide_string(env,bstrName);
      (*vtypeInfo)->descriptor =
        make_descriptor(libInfo->packageName, (*vtypeInfo)->className);
      break;
    case TKIND_COCLASS:
      (*vtypeInfo)->className = make_classname_from_wide_string(env,bstrName);
      (*vtypeInfo)->descriptor =
        make_descriptor(libInfo->packageName, (*vtypeInfo)->className);
      break;
    case TKIND_ENUM:
      jprintf(env,PROGRESS,"An enumeration");
      (*vtypeInfo)->className = make_classname_from_wide_string(env,bstrName);
      (*vtypeInfo)->vtype = VT_I4;
      (*vtypeInfo)->descriptor =
        make_descriptor(libInfo->packageName, (*vtypeInfo)->className);
      break;
    case TKIND_INTERFACE:
      jprintf(env,PROGRESS,"A vanilla interface");
      break;
    case TKIND_RECORD:
      jprintf(env,PROGRESS,"A record of type %ws with vtype %d", bstrName,
        pTDesc->vt);
      break;
    case TKIND_MODULE:
      jprintf(env,PROGRESS,"A module");
      break;
    case TKIND_ALIAS:
      jprintf(env,PROGRESS,"An alias");
      break;
    case TKIND_UNION:
      jprintf(env,PROGRESS,"A union");
      break;
    }
    if (! FAILED(hr)) 
    {
      if (!(tkind == TKIND_DISPATCH))
      {
        if (bstrName)
          SysFreeString(bstrName);
      }
    }
    
    if (tkind == TKIND_COCLASS || tkind == TKIND_DISPATCH) {
      hr = pRefTypeInfo->lpVtbl->GetContainingTypeLib(pRefTypeInfo,&containingTypeLib,
                                                      &position);   
      if (containingTypeLib) {
        const GUID *libid;
        int typeCount;
        BOOLEAN looking = TRUE;
        CLASS_INFO *type; 
 
        collect_library_information_1(env,
          containingTypeLib,
          NULL,
          NULL,
          NULL,
          &libid,
          &typeCount,
          NULL,
          NULL);
      
        if (IsEqualGUID(libInfo->libid,libid)) {
          /* Is from this library do nothing */
        } 
        else {
          LIBRARY_INFO *node;
          BOOLEAN looking2 = TRUE;
          /* iterate over all libraries to see if we have the library already
          * if the library is there already, check to see if the type has been
          * collected
          * if then library is not there then add a new library, and collect 
          * the missing type information 
          */
          jprintf(env, DERROR,"Found  a class from another library");
          print_iid_info(env, DERROR, "This libid ", libInfo->libid);
          print_iid_info(env, DERROR, "That libid ", libid);

          node = libraries_head;
          while (node && looking) {
             if (IsEqualGUID(node->libid,libid)) {
                type = node->classes_head;
                looking = FALSE;
                break;
             }
             node = node->next;
          }
          if (looking) {
            node = (LIBRARY_INFO *) malloc(sizeof(LIBRARY_INFO));
            initialize_lib_info(node);
            collect_library_information(env,containingTypeLib,node);
            node->partialLibrary = TRUE;

            if (! libraries_tail) {
              libraries_head = node;
              libraries_tail = node;
            } else {
              libraries_tail->next = node;
              libraries_tail = node;
            }
            collect_library_details(env,containingTypeLib,node);
          } 
          (*vtypeInfo)->descriptor 
            = make_descriptor(node->packageName, (*vtypeInfo)->className);
          (*vtypeInfo)->className 
            = make_full_package_classname(node->packageName,
                                          (*vtypeInfo)->className);
          
        } 
      }
      
    if (typeAttr)
      pRefTypeInfo->lpVtbl->ReleaseTypeAttr(pRefTypeInfo,typeAttr);

    }        

    jprintf(env,PROGRESS,"\n");
  }
}

/*****************************************************************************
 * trace_type_details
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
	
static void trace_type_details (JNIEnv *env, ITypeInfo  *pTypeInfo, TYPEDESC *pTDesc)
{  
  HRESULT hr;
  ITypeInfo *pRefTypeInfo;
                                
  jprintf(env,DETAIL,"Type = %d",pTDesc->vt);
  hr = get_reference_type(env, pTypeInfo,pTDesc,&pRefTypeInfo);
  if (! FAILED(hr)) {
    BSTR bstrName;
    BSTR bstrDocString;
    BSTR bstrHelpFile;
    TYPEATTR *typeAttr;
    ITypeLib *containingTypeLib;
    int position;
    
    
    hr = pRefTypeInfo->lpVtbl->GetDocumentation
      (pRefTypeInfo, -1, &bstrName, &bstrDocString, NULL, &bstrHelpFile);
    
    if (bstrName)
      jprintf(env,PROGRESS,"Type info name is: %ls", bstrName);
    if (bstrDocString)
      jprintf(env,PROGRESS,"Doc string is: %ls", bstrDocString);
    if (bstrHelpFile)
      jprintf(env,PROGRESS,"Help file is: %ls", bstrHelpFile);
    
    hr = pRefTypeInfo->lpVtbl->GetTypeAttr(pRefTypeInfo, &typeAttr);
    
    switch(typeAttr->typekind) {
    case TKIND_DISPATCH:
      jprintf(env,PROGRESS,"A dispatchable interface");
      break;
    case TKIND_COCLASS:
      jprintf(env,PROGRESS,"A creatable class");
      break;
    case TKIND_ENUM:
      jprintf(env,PROGRESS,"An enumeration");
      break;
    case TKIND_INTERFACE:
      jprintf(env,PROGRESS,"A vanilla interface");
      break;
    case TKIND_RECORD:
      jprintf(env,PROGRESS,"A record");
      break;
    case TKIND_MODULE:
      jprintf(env,PROGRESS,"A module");
      break;
    case TKIND_ALIAS:
      jprintf(env,PROGRESS,"An alias");
      break;
    case TKIND_UNION:
      jprintf(env,PROGRESS,"A union");
      break;
    }
    
    hr = pRefTypeInfo->lpVtbl->GetContainingTypeLib(pRefTypeInfo,&containingTypeLib, &position);
    
    if (containingTypeLib) {
      BSTR bstrName;
      BSTR bstrDocString;
      BSTR bstrHelpFile;
        
      hr = containingTypeLib->lpVtbl->GetDocumentation(containingTypeLib,-1,&bstrName,
        &bstrDocString,NULL,
        &bstrHelpFile);
        
      if (bstrName)
        jprintf(env,PROGRESS,"Type lib name is: %ls", bstrName);
      if (bstrDocString)
        jprintf(env,PROGRESS,"Doc string is: %ls", bstrDocString);
      if (bstrHelpFile)
        jprintf(env,PROGRESS,"Help file is: %ls", bstrHelpFile);
        
    }
  }        
  jprintf(env,PROGRESS,"");
}

/*****************************************************************************
 * collect_member_field_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: 
 *     -----
 *   Modifications:
 *****************************************************************************/
static void collect_member_field_info(JNIEnv *env, ITypeInfo *pTypeInfo, short index,
					 int type_info_number, CLASS_INFO *pTypeStruct)

{
  FIELD_INFO *node;
  long hr;
  unsigned short *localName, *temp; 
  unsigned short iteration = (unsigned short) '0';
  long memid;
  BOOL first;  
  BOOL previousUSCORE;
  BOOL previousUPPER;
  BSTR bstrName;
  VARDESC *pVarDesc;
  VTYPE_INFO ** vtype = (VTYPE_INFO **) malloc(sizeof(VTYPE_INFO *));
    
  hr = pTypeInfo->lpVtbl->GetVarDesc(pTypeInfo, index, &pVarDesc);
  if (FAILED(hr)) {
    if (hr == TYPE_E_ELEMENTNOTFOUND)
      jprintf(env, DERROR, "GetVarDesc(%d): Element not found (0x%x)", index, hr);
    else
      jprintf(env, DERROR, "GetVarDesc(%d) failed, returning 0x%x", index, hr);
    return;
    }

  memid = pVarDesc->memid;

  get_vtype_info(env,pTypeStruct->library,
        pTypeInfo,
        &(pVarDesc->elemdescVar.tdesc),
        vtype);

  /* Duplicate checking here */

  node = (FIELD_INFO *) malloc(sizeof(FIELD_INFO));
  initialize_field_info(node);

  node->vtype = *vtype;
  node->containing_type_info = type_info_number;
  node->memid = memid;
  node->int_value = pVarDesc->lpvarValue->iVal;
  node->next = NULL;

  /* Now the naming conventions */

   hr = pTypeInfo->lpVtbl->GetDocumentation
	(pTypeInfo, memid, &bstrName, NULL, NULL, NULL);
    if (FAILED(hr) || (!bstrName)) {
      jprintf(env, DERROR, "Could not obtain name docstring for vardesc");
      node->field_name = L"NONAME";
    } else {
      localName = (unsigned short *) malloc((2 * wcslen(bstrName)) *
        sizeof(unsigned short));
      temp = localName;
      
      /* Convert the new name to uppercase */

      first = TRUE;
      previousUPPER = FALSE;
      previousUSCORE = FALSE;
      while (iteration = *bstrName++) 
      {
        if (WISUPPER(iteration)) {
          if ((! previousUSCORE) &&
              (!first) && 
              ((! previousUPPER) || 
                 WISLOWER(*bstrName))
              ) { 
            (*temp++) = '_';
          }
          previousUPPER = TRUE;
          *temp++ = iteration;
        } 
        else {
          if (WISLOWER(iteration))
            *temp++ = iteration + ((unsigned short) 'A' - ((unsigned short) 'a'));
          else (*temp++) = iteration;
        }
        if (iteration == ((unsigned short) '_'))
          previousUSCORE = TRUE;
        else previousUSCORE = FALSE;
        if (first)
          first = FALSE;
      }                            
      *temp = 0;        
      
      pTypeInfo->lpVtbl->ReleaseVarDesc(pTypeInfo, pVarDesc);
   }

    node->field_name = localName;

    if (!pTypeStruct->fields_tail) {
      pTypeStruct->fields_head = node;
      pTypeStruct->fields_tail = node;
    } else {
      pTypeStruct->fields_tail->next = node;
      pTypeStruct->fields_tail = node;
    }
}

/*****************************************************************************
 * collect_member_variable_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void collect_member_variable_info(JNIEnv *env, ITypeInfo *pTypeInfo,
                                         short index, int type_info_number,
                                         CLASS_INFO *pTypeStruct)
{
    METHOD_INFO *getNode; 
    METHOD_INFO *setNode;
    METHOD_INFO *head;
    METHOD_INFO *tail;
    long hr;
    unsigned short *localName, *temp; 
    unsigned short iteration = (unsigned short) '0';
    long memid;
    BOOL isDuplicate;
    BOOL isSameInAllWays;
    BOOL readOnly = FALSE;
    BSTR bstrName;
    VARDESC *pVarDesc;
    VTYPE_INFO *vtype;
    PROPERTY_DESCRIPTOR *property_descriptor = NULL;

    hr = pTypeInfo->lpVtbl->GetVarDesc(pTypeInfo, index, &pVarDesc);
    if (FAILED(hr)) {
	if (hr == TYPE_E_ELEMENTNOTFOUND)
	    jprintf(env, DERROR, "GetVarDesc(%d): Element not found (0x%x)", index, hr);
	else
	    jprintf(env, DERROR, "GetVarDesc(%d) failed, returning 0x%x", index, hr);
	return;
    }

    memid = pVarDesc->memid;
    head = pTypeStruct->methods_head;
    tail = pTypeStruct->methods_tail;
    
    if (pTypeStruct->beanInfo) {
      VARFLAGS varFlags;

      property_descriptor = malloc(sizeof(PROPERTY_DESCRIPTOR));
      initialize_property_descriptor(property_descriptor);

      varFlags = pVarDesc->wVarFlags;

      if ((varFlags & VARFLAG_FREADONLY) != 0)
         readOnly = TRUE; 

      if ((varFlags & VARFLAG_FRESTRICTED) != 0)
        property_descriptor->isExpert = TRUE;

      if ((varFlags & VARFLAG_FHIDDEN) != 0) 
      {
        property_descriptor->isHidden = TRUE;
      }
        
      if (((varFlags & VARFLAG_FBINDABLE) != 0) &&
        ((varFlags & VARFLAG_FDISPLAYBIND) != 0)) 
      {
        property_descriptor->isBindable = TRUE;
      }
    }

    get_vtype_info(env,pTypeStruct->library,
        pTypeInfo,
        &(pVarDesc->elemdescVar.tdesc),
        &vtype);
    
    if ((isDuplicateMethod(memid,DISPATCH_PROPERTYGET,head)) && 
         isDuplicateMethod(memid,DISPATCH_PROPERTYPUT,head)) { 
      return;
    }
 
    getNode = (METHOD_INFO *) malloc(sizeof(METHOD_INFO));
    initialize_method_info(getNode);
    getNode->cParams = 0;
    getNode->vtype = vtype;
    getNode->containing_type_info = type_info_number;
    getNode->memid = memid;
    getNode->paramVtypes = NULL; 
    getNode->invkind = DISPATCH_PROPERTYGET;

    if (readOnly) {
        getNode->next = NULL;
    }
    else {
      setNode = (METHOD_INFO *) malloc(sizeof(METHOD_INFO));
      initialize_method_info(setNode);
      getNode->next = setNode;
      
      setNode->cParams = 1;
      setNode->vtype = (VTYPE_INFO *) malloc(sizeof(VTYPE_INFO));
      initialize_vtype_info(setNode->vtype);
      setNode->vtype->vtype = VT_VOID;
      setNode->vtype->createLocation = LOCATION_VOID;
      setNode->containing_type_info = type_info_number;
      setNode->memid = memid;
      setNode->paramVtypes = (VTYPE_INFO **) malloc(sizeof(VTYPE_INFO *));
      setNode->paramVtypes[0] = vtype;
      setNode->invkind = DISPATCH_PROPERTYPUT;
      setNode->next = NULL;
    }
    hr = pTypeInfo->lpVtbl->GetDocumentation
	(pTypeInfo, memid, &bstrName, NULL, NULL, NULL);
    if (FAILED(hr) || (!bstrName)) {
      jprintf(env, DERROR, "Could not obtain name docstring for vardesc");
      getNode->method_name = L"NoName";
      setNode->method_name = L"NoName";
    } else {
      localName = (unsigned short *) malloc((3 + wcslen(bstrName)) *
        sizeof(unsigned short));
      temp = localName;
      while (*temp++ = *bstrName++);
      *(temp+1) = 0;

      if ((localName[0] <= (unsigned short) 'a') && 
        (localName[0] >= (unsigned short) 'z')) {
        localName[0] = localName[0] + ((unsigned short) 'A' - (unsigned short) 'a');
      }

      /* Perhaps change _Value to _value. */
      if ((localName[0] == (unsigned short) '_') &&
        (localName[1] <= (unsigned short) 'Z') && 
        (localName[1] >= (unsigned short) 'A')) {
        localName[1] = localName[1] + ((unsigned short) 'a' - (unsigned short) 'A');
      } 
      

      /* Determine the name of the getMethod & setMethods together */
      isDuplicate = isDuplicateNamedMethod(localName,memid,-1,
                                           &isSameInAllWays,head);
      if (isDuplicate) {
        if (isSameInAllWays) {
          return;
        }
        *(temp-1) = '_';
        while (isDuplicate) {
          iteration = (iteration == (unsigned short) '9') ? (unsigned short) 'a'
            : iteration++;
          *(temp) = iteration;
          isDuplicate = isDuplicateNamedMethod(localName,memid,-1,
                                               &isSameInAllWays,head);
        }
      } else {
        /* zero out extra allocated memory, just to be sure */
        *(temp) = 0;
      }

    getNode->method_name = localName;
    
    if (! readOnly)
    {
      /* need another copy because we do not want to free the same
         memory twice */
      setNode->method_name = malloc((wcslen(localName) + 1) * sizeof (OLECHAR));
      wcscpy(setNode->method_name, localName);
    }

    pTypeInfo->lpVtbl->ReleaseVarDesc(pTypeInfo, pVarDesc);
    }

    if (!pTypeStruct->methods_tail) {
      if (readOnly)
      { 
        pTypeStruct->methods_head = getNode;
        pTypeStruct->methods_tail = getNode;  
      }
      else {
        pTypeStruct->methods_head = getNode;
        pTypeStruct->methods_tail = setNode;
      }
    } else {
      if (readOnly) {
        pTypeStruct->methods_tail->next = getNode;
        pTypeStruct->methods_tail = getNode;
      }
      else {
        pTypeStruct->methods_tail->next = getNode;
        pTypeStruct->methods_tail = setNode;    
      }
    }
   
   if(property_descriptor)
   {
     property_descriptor->methods = malloc(sizeof(METHOD_INFO *) * 2);
     if (readOnly)
       property_descriptor->cMethods = 1;
     else property_descriptor->cMethods = 2;
     property_descriptor->methods[0] = getNode;
     if (! readOnly)
       property_descriptor->methods[1] = setNode;
     if (pTypeStruct->beanInfo->properties_tail)
     {
      pTypeStruct->beanInfo->properties_tail->next = property_descriptor;
      pTypeStruct->beanInfo->properties_tail = property_descriptor;
     }
     else {
        pTypeStruct->beanInfo->properties_head = property_descriptor;
        pTypeStruct->beanInfo->properties_tail = property_descriptor;
     }
   }

}
   



/*****************************************************************************
 * collect_single_function_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: 
 *    From Automation Programmer's Reference, p 171:
 *   "The cParams field specifies the total number of required and optional 
 *    parameters.  
 *    The cParamsOpt field specifies the form of optional parameters accepted
 *    by the function, as follows:
 *      - A value of 0 specifies that no optional arguments are supported.
 *      - A value of -1 specifies that the method's last parameter is a
 *        pointer to a safe array of variants.  Any number of variant
 *        arguments greater than cParams - 1 must be packaged by the caller 
 *        into a safe array and passed as the final parameter.  This array
 *        of optional parameters must be freed by the caller after control
 *        is returned from the call.
 *      - Any other number indicates that the last n parameters of the 
 *        function are variants and do not need to be specified by the caller
 *        explicitly.  The parameters left unspecified should be filled
 *        in by the compiler or interpreter as variants of type VT_ERROR
 *        with the value DISP_E_PARAMNOTFOUND."
 *   What I understand from that is that the number of required parameters
 *   is equal to cParams - cParamsOpt, unless cParamsOpt == -1, in which
 *   case the number of required parameters = cParams - 1.
 *
 *   I think the right thing to do is to emit n+1 different methods
 *   for a function with n optional parameters, and emit the code
 *   to fill in the unused optional parameters.  For example:
 *       public Variant foo() {
 *         Vector args = new Vector(1);
 *         args.addElement(newVariant());  / default constructor is error case
 *         return oleObject.comInvoke(iDispatch, 0xfffffda6, args);
 *       }
 *         
 *       public Variant foo(int param1) {
 *         Vector args = new Vector(1);
 *         args.addElement(newVariant(param1));
 *                                                 
 *         return oleObject.comInvoke(iDispatch, 0xfffffda6, args);
 *       }
 *    Unlike C, Java allows methods to have the same name if they have different
 *    argument lists, so this solution is possible.
 *     -----
 *   Modifications:
 *****************************************************************************/
static METHOD_INFO *collect_single_function_info (JNIEnv *env,
						  ITypeInfo *pTypeInfo,
						  CLASS_INFO *pTypeStruct,
						  short cParamsReq,
						  ELEMDESC *elemdescParam,
						  BOOL has_optional_safearray)
{
    short i;
    VTYPE_INFO **paramVtypes;
    METHOD_INFO *node;
    
    paramVtypes = (VTYPE_INFO **) malloc(cParamsReq * sizeof(VTYPE_INFO *));
    node = (METHOD_INFO *) malloc(sizeof(METHOD_INFO));
    initialize_method_info(node);
    node->cParams = cParamsReq;
    node->next = NULL;
    
    if (has_optional_safearray) {
        for (i=0; i < (cParamsReq - 1); i++) {
            get_vtype_info(env, pTypeStruct->library,
                pTypeInfo, &(elemdescParam[i].tdesc),
                &(paramVtypes[i]));
        }
        paramVtypes[i] = (VTYPE_INFO *) malloc(sizeof(VTYPE_INFO));
        initialize_vtype_info(paramVtypes[i]);
        paramVtypes[i]->vtype = VT_ARRAY; /* == Variant[] */    
        paramVtypes[i]->createLocation = LOCATION_VECTOR;
    } else {
        for (i=0; i<cParamsReq; i++) {          
            get_vtype_info(env, pTypeStruct->library,
                pTypeInfo, &(elemdescParam[i].tdesc),
                &(paramVtypes[i]));
            paramVtypes[i]->createLocation = LOCATION_OPTIONAL;
        }
    }
    
    node->paramVtypes = paramVtypes;   
    return node;
}
 

 /*****************************************************************************
 * find_matching_property_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: 
 *     -----
 *   Modifications:
 *****************************************************************************/

 static PROPERTY_DESCRIPTOR * find_matching_property_descriptor
   (CLASS_INFO *pTypeStruct, METHOD_DESCRIPTOR *method_descriptor)
 {
    PROPERTY_DESCRIPTOR *property_descriptor;
    BOOL foundP;
    unsigned short *property_name;
    unsigned short *method_name;

    foundP = FALSE;

    property_descriptor = pTypeStruct->beanInfo->properties_head;

    method_name = method_descriptor->method->method_name;
    
    while(property_descriptor && (! foundP))
    {
     property_name = property_descriptor->methods[0]->method_name;       

     if (wcscmp(property_name, method_name) == 0) 
     {
        foundP = TRUE;
        break;
     }
     property_descriptor = property_descriptor->next;
    }
    if (foundP)
      return property_descriptor;
    else return NULL;
 }

 /*****************************************************************************
 * add_property_descriptor_for_method_descriptor
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: 
 *     -----
 *   Modifications:
 *****************************************************************************/

 static void add_property_descriptor_for_method_descriptor
   (CLASS_INFO *pTypeStruct,
   METHOD_INFO *node,
   METHOD_DESCRIPTOR *method_descriptor,
   FUNCFLAGS funcFlags)
 {
   PROPERTY_DESCRIPTOR *property_descriptor = NULL;

   if ((node->invkind == INVOKE_PROPERTYGET) || (node->invkind == INVOKE_PROPERTYPUT))
    {
     /* Check to see if the property of the same name exists already */

     property_descriptor = 
       find_matching_property_descriptor(pTypeStruct, method_descriptor);

     if (property_descriptor)  {
          if (property_descriptor->cMethods == 1) {
              property_descriptor->cMethods = 2;
              property_descriptor->methods[1] = node;
          }
          else {
              METHOD_INFO ** oldMethods;
              int i;

              oldMethods = property_descriptor->methods;
              
              property_descriptor->methods = malloc(sizeof(METHOD_INFO) 
                        * (property_descriptor->cMethods + 1));

              for(i=0; i<property_descriptor->cMethods; i++)
              {
                property_descriptor->methods[i] = oldMethods[i];
              }
              property_descriptor->methods[property_descriptor->cMethods] = node;
             
              property_descriptor->cMethods +=1;
              free(oldMethods);
          }
     }
     else {  /* If it does not exist already then add another property descriptor */
         
      property_descriptor = malloc(sizeof(PROPERTY_DESCRIPTOR));
      initialize_property_descriptor(property_descriptor);
      property_descriptor->methods = malloc(sizeof(METHOD_INFO *) * 2);
      property_descriptor->methods[0] = node;
      property_descriptor->cMethods = 1;
      property_descriptor->isExpert = method_descriptor->isExpert;
      property_descriptor->isHidden = method_descriptor->isHidden;
      
      if (((funcFlags & FUNCFLAG_FBINDABLE) != 0) &&
        ((funcFlags & FUNCFLAG_FDISPLAYBIND) != 0)) 
      {
        property_descriptor->isBindable = TRUE;
      }


     if (pTypeStruct->beanInfo->properties_tail)
     {
       pTypeStruct->beanInfo->properties_tail->next = property_descriptor;
       pTypeStruct->beanInfo->properties_tail = property_descriptor;
     }
     else {
       pTypeStruct->beanInfo->properties_head = property_descriptor;
       pTypeStruct->beanInfo->properties_tail = property_descriptor;
     }
    }
   }
 }


/*****************************************************************************
 * collect_member_function_info
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: 
 *     -----
 *   Modifications:
 *****************************************************************************/
static void collect_member_function_info(JNIEnv *env, ITypeInfo *pTypeInfo, short index,
					 int type_info_number, CLASS_INFO *pTypeStruct)
{
    METHOD_INFO *node;
    METHOD_INFO *head;
    long hr;
    unsigned short *local_name, *temp;
    unsigned short iteration = (unsigned short) '0';
    short cParamsOpt, cParams;
    long memid;
    BOOL isDuplicate;
    BOOL isSameInAllWays;
    WCHAR *wName;
    BSTR originalName;
    FUNCDESC *pFuncDesc;
    INVOKEKIND invkind;
    VTYPE_INFO **returnVtype;
    METHOD_DESCRIPTOR *method_descriptor = NULL;
    FUNCFLAGS funcFlags;
    
    hr = pTypeInfo->lpVtbl->GetFuncDesc(pTypeInfo, index,
        &pFuncDesc);
    if (FAILED(hr)) {
        if (hr == TYPE_E_ELEMENTNOTFOUND)
            jprintf(env, DERROR, "GetFuncDesc(%d): Element not found (0x%x)", index, hr);
        else
            jprintf(env, DERROR, "GetFuncDesc(%d) failed, returning 0x%x", index, hr);
        return;
    }
    memid = pFuncDesc->memid;
    invkind = pFuncDesc->invkind;
    funcFlags = pFuncDesc->wFuncFlags;
    
    head = pTypeStruct->methods_head;
    if (isDuplicateMethod(memid,invkind,head)) {
        pTypeInfo->lpVtbl->ReleaseFuncDesc(pTypeInfo, pFuncDesc);
        return;
    }
    
    hr = pTypeInfo->lpVtbl->GetDocumentation
        (pTypeInfo, memid, &originalName, NULL, NULL, NULL);
    
    if (FAILED(hr) || (!originalName)) {
        jprintf(env, DERROR, "Could not obtain name docstring for funcdesc");
        local_name = malloc(sizeof (L"no_name"));
        wcscpy(local_name, L"no_name");
    } else {
        /* using wcslen here is wrong.  Need to use some get_length_of_bstr thingie */
        local_name = (unsigned short *) malloc((3 + wcslen(originalName)) *
            sizeof(unsigned short));
        wName = originalName;
        temp = local_name;
        while (*temp++ = *wName++);
        *(temp+1) = 0;
        
        if ((local_name[0] <= (unsigned short) 'a') &&
            (local_name[0] >= (unsigned short) 'z')) {
            local_name[0] = local_name[0] + ((unsigned short) 'A' - (unsigned short) 'a');
        }
        isDuplicate = isDuplicateNamedMethod(local_name,memid,invkind,&isSameInAllWays,head);
        if (isDuplicate) {
            if (isSameInAllWays) {
                pTypeInfo->lpVtbl->ReleaseFuncDesc(pTypeInfo, pFuncDesc);
                return;
            }
            *(temp-1) = '_';
            while (isDuplicate) {
                iteration = (iteration == (unsigned short) '9') ? (unsigned short) 'a'
                    : iteration + 1;
                *(temp) = iteration;
                isDuplicate = isDuplicateNamedMethod(local_name,memid,invkind,&isSameInAllWays,head);
            }
        } else {
            /* zero out extra allocated memory, just to be sure */
            *(temp) = 0;
        }
    }
    jprintf(env, PROGRESS, "method %ls (really %ls) comes from typeinfo #%d",
        local_name, originalName, type_info_number);
    
    returnVtype = (VTYPE_INFO **) malloc(sizeof(VTYPE_INFO *));
    get_vtype_info(env, pTypeStruct->library, 
        pTypeInfo, &(pFuncDesc->elemdescFunc.tdesc),
        returnVtype);

    cParamsOpt = pFuncDesc->cParamsOpt;
    cParams = pFuncDesc->cParams;
    
    if (cParamsOpt == -1) {
        node = collect_single_function_info(env, pTypeInfo, pTypeStruct, cParams,
            pFuncDesc->lprgelemdescParam, TRUE);
        node->method_name = local_name;
        
        node->vtype = *returnVtype;
        node->containing_type_info = type_info_number;
        node->memid = memid;
        node->invkind = invkind;
        
        jprintf(env, DETAIL,
            "Adding method with safearray optionals: %d",
            node->method_name);
        
        if (!(pTypeStruct->methods_tail)) {
            pTypeStruct->methods_head = node;
            pTypeStruct->methods_tail = node;
        } else {
            pTypeStruct->methods_tail->next = node;
            pTypeStruct->methods_tail = node;
        }
        
        
        if (pTypeStruct->beanInfo)
        {       
            method_descriptor = malloc(sizeof(METHOD_DESCRIPTOR));
            initialize_method_descriptor(method_descriptor);
            
            if((funcFlags & FUNCFLAG_FRESTRICTED) != 0)
                method_descriptor->isExpert = TRUE;
            
            if ((funcFlags & FUNCFLAG_FHIDDEN) != 0) {
                method_descriptor->isHidden = TRUE;
            }
        }
        
        if (method_descriptor)
        {
            method_descriptor->method = node;
            
            add_property_descriptor_for_method_descriptor(
                pTypeStruct, node, method_descriptor, funcFlags);
            
            if (pTypeStruct->beanInfo->methods_tail)
            {
                pTypeStruct->beanInfo->methods_tail->next = method_descriptor;
                pTypeStruct->beanInfo->methods_tail = method_descriptor;
            }
            else {
                pTypeStruct->beanInfo->methods_head = method_descriptor;
                pTypeStruct->beanInfo->methods_tail = method_descriptor;
            }
        }
    } else {
        short j;

        jprintf(env, DETAIL,
            "Adding method without safearray optionals, and cParams: %d",
            cParams);
        
        /* We always want to output at least the method with all of
           the optional parameters. The rest are for convenience and we
           want to limit those because it would be too verbose. */
        for (j = (cParams - cParamsOpt); j <= cParams; j++) {
            if (j == (MAX_OPTIONALS_TO_EMIT + 1))
                j = cParams;

            node = collect_single_function_info(env, pTypeInfo, pTypeStruct,
                j, pFuncDesc->lprgelemdescParam, FALSE);

            /* Each node needs it own copy of the method name. */
            node->method_name = malloc((wcslen(local_name) + 1) *
                                  sizeof (OLECHAR));
            wcscpy(node->method_name, local_name);
            node->vtype = *returnVtype;
            node->containing_type_info = type_info_number;
            node->memid = memid;
            node->invkind = invkind;
            
            if (!(pTypeStruct->methods_tail)) {
                pTypeStruct->methods_head = node;
                pTypeStruct->methods_tail = node;
            } else {
                pTypeStruct->methods_tail->next = node;
                pTypeStruct->methods_tail = node;
            }
            
            if (pTypeStruct->beanInfo)
            {       
                method_descriptor = malloc(sizeof(METHOD_DESCRIPTOR));
                initialize_method_descriptor(method_descriptor);
                
                if((funcFlags & FUNCFLAG_FRESTRICTED) != 0)
                    method_descriptor->isExpert = TRUE;
                
                if ((funcFlags & FUNCFLAG_FHIDDEN) != 0)
                {
                    method_descriptor->isHidden = TRUE;
                }
            }  
            
            if (method_descriptor)
            {
                method_descriptor->method = node;
                
                add_property_descriptor_for_method_descriptor(
                    pTypeStruct, node, method_descriptor, funcFlags);
                
                if (pTypeStruct->beanInfo->methods_tail)
                {
                    pTypeStruct->beanInfo->methods_tail->next = method_descriptor;
                    pTypeStruct->beanInfo->methods_tail = method_descriptor;
                }
                else {
                    pTypeStruct->beanInfo->methods_head = method_descriptor;
                    pTypeStruct->beanInfo->methods_tail = method_descriptor;
                }
            }
        }
        
        free(local_name);
        pTypeInfo->lpVtbl->ReleaseFuncDesc(pTypeInfo, pFuncDesc);
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
unsigned int get_index_in_containing_lib(ITypeInfo *pTypeInfo) {
  HRESULT hr;
  unsigned int i;
  ITypeLib *pTempLib = NULL;

  hr = pTypeInfo->lpVtbl->GetContainingTypeLib(pTypeInfo,&pTempLib,&i);
  if (pTempLib)
    pTempLib->lpVtbl->Release(pTempLib);
  return i;
}

/*****************************************************************************
 * collect_event_source_information
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

static void collect_event_source_information(JNIEnv *env, int type_info_number, 
                                             ITypeInfo *pTypeInfo,
                                             TYPEATTR *pTypeAttr,
                                             int typekind, 
                                             CLASS_INFO *class_info_node)                                             
{
  HRESULT hr;
  EVENT_SET_DESCRIPTOR *event_descriptor;
  BSTR bstrName, bstrDocString, bstrHelpFile; 
  static GUID *cclsid;   
  ITypeLib *containingTypeLib;
  int position;
  LIBRARY_INFO *libInfo = class_info_node->library;
  
  if (typekind == TKIND_DISPATCH) 
  {
    hr = pTypeInfo->lpVtbl->GetDocumentation
      (pTypeInfo, -1, &bstrName, &bstrDocString, NULL, &bstrHelpFile);
    if (FAILED(hr)) {
      jprintf(env, DERROR, "Could not get doc for type");
      return;  
    }
    cclsid = &(pTypeAttr->guid);
    
    /** Check the library that this interface refers to 
    *  If it is this library then just add to the
    *  list of EVENT_SET_DESCRIPTORS for this library
    *  If it is another library and it exists then just
    *  add to the list of EVENT_SET_DESCRIPTORS for that
    *  library
    *  If this is the first time that library has been
    *  found then collect info on that library
    */    
    hr = pTypeInfo->lpVtbl->GetContainingTypeLib(pTypeInfo,&containingTypeLib,
                                                      &position);   
      if (containingTypeLib) {
        const GUID *libid;
        int typeCount;
        BOOLEAN looking = TRUE;
        BOOLEAN looking2 = TRUE;
        BOOLEAN looking3 = TRUE;
        LIBRARY_INFO *node;
        EVENT_SET_DESCRIPTOR *event_source;
 
        collect_library_information_1(env,
          containingTypeLib,
          NULL,
          NULL,
          NULL,
          &libid,
          &typeCount,
          NULL,
          NULL);
      
        if (IsEqualGUID(libInfo->libid,libid)) {
          looking  = FALSE;
          node = libInfo;
        } 
        else {
          /* iterate over all libraries to see if we have the library already
          * if the library is there already, check to see if the type has been
          * collected
          * if then library is not there then add a new library, and collect 
          * the missing type information 
          */
          jprintf(env, DERROR,"Found  a class from another library");
          print_iid_info(env, DERROR, "This libid ", libInfo->libid);
          print_iid_info(env, DERROR, "That libid ", libid);

          node = libraries_head;
          while (node && looking) {
             if (IsEqualGUID(node->libid,libid)) {
                looking = FALSE;
                break;
             }
             node = node->next;
          }
        }
        if (looking) {
          node = (LIBRARY_INFO *) malloc(sizeof(LIBRARY_INFO));
          initialize_lib_info(node);
          collect_library_information(env,containingTypeLib,node);
          node->partialLibrary = TRUE;

          if (! libraries_tail) {
            libraries_head = node;
            libraries_tail = node;
          } else {
            libraries_tail->next = node;
            libraries_tail = node;
          }
          collect_library_details(env,containingTypeLib,node);
        } 
               
        /* Check to see if this EVENT_SET_DESCRIPTOR has been
        * added yet 
        */

        event_source = node->event_sources_head;
        while (event_source && looking2)
        {
          if (IsEqualGUID(event_source->type, cclsid)) 
          {
              looking2 = FALSE;
          }
          event_source = event_source->next;
        }

        if (looking2)
        {
          event_descriptor = 
            (EVENT_SET_DESCRIPTOR *) malloc(sizeof(EVENT_SET_DESCRIPTOR));
          initialize_event_set_descriptor(event_descriptor);
          event_descriptor->type = cclsid;

          if (! node->event_sources_tail) {
            node->event_sources_tail = event_descriptor;
            node->event_sources_head = event_descriptor;
          }
          else {
            node->event_sources_tail->next = event_descriptor;
            node->event_sources_tail = event_descriptor;
          }
        }
        else {
          event_descriptor = event_source;
          }

        //Now add this event descriptor to this CLASS_INFO

        event_source = class_info_node->beanInfo->events_head;
        while (event_source && looking3)
        {
          if (IsEqualGUID(event_source->type, cclsid)) 
          {
              looking3 = FALSE;
          }
          event_source = event_source->next;
        }

        if (looking3) 
        {
          if (! class_info_node->beanInfo->events_tail) {
            class_info_node->beanInfo->events_tail = event_descriptor;
            class_info_node->beanInfo->events_head = event_descriptor;
          }
          else {
            class_info_node->beanInfo->events_tail->next = event_descriptor;
            class_info_node->beanInfo->events_tail = event_descriptor;
          }
        }
      }
    } 
  }

/*****************************************************************************
 * collect_typeinfo_members
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/

static void collect_typeinfo_members(JNIEnv *env, int type_info_number, 
                                       ITypeInfo *pTypeInfo,
                                       TYPEATTR *pTypeAttr,
                                       int typekind, 
                                       CLASS_INFO *node)
{
    HRESULT hr;    
    unsigned short cimpltypes;
    short i;
    unsigned short numFunctions, numVars;
    BOOL collectImplTypes;
        
    cimpltypes = pTypeAttr->cImplTypes;

    collectImplTypes = FALSE;
    if (typekind == TKIND_ENUM) {   
      numVars = pTypeAttr->cVars;
      if (numVars > 0) {
        for (i=0; i<numVars; i++) {
          collect_member_field_info(env, pTypeInfo, i, type_info_number, node);
        }
      }
      collectImplTypes = TRUE;
    }

    if ((typekind == TKIND_COCLASS) ||
      (typekind == TKIND_DISPATCH))  {   
      numFunctions = pTypeAttr->cFuncs;
      numVars = pTypeAttr->cVars;

      if (typekind == TKIND_DISPATCH)
        jprintf(env, PROGRESS,
        "Collect member info for Dispatch interface, Funcs = %d, Props = %d",
        numFunctions, numVars);
      else jprintf(env, PROGRESS, 
        "Collect member info for COCLASS Funcs = %d, Props = %d",
        numFunctions, numVars);

      if (numFunctions > 0) {
        for (i=0; i<numFunctions; i++) {
          collect_member_function_info(env, pTypeInfo, i, type_info_number, node);
        }
      }

      if (numVars > 0) {
        for (i=0; i<numVars; i++) {
          collect_member_variable_info(env, pTypeInfo, i, type_info_number, node);
        }
      }
      collectImplTypes = TRUE;
    }
     
    if (collectImplTypes) {
      /* Collect members for all the implemented IDispatch, default interfaces */
      if (cimpltypes > 0) {
        int implTypeFlags;

        for (i=0; i<cimpltypes; i++) {
          hr = pTypeInfo->lpVtbl->GetImplTypeFlags(pTypeInfo,i,&implTypeFlags);
          
          if (FAILED(hr)) {
            jprintf(env, PROGRESS, "Found no impl flags");
            continue;
          }
          /* Do not emit restricted or vtable types */
          if((implTypeFlags & IMPLTYPEFLAG_FRESTRICTED) ||
            (implTypeFlags & IMPLTYPEFLAG_FDEFAULTVTABLE)) {
            jprintf(env, PROGRESS, "Implemented Interface is restricted or vtable");
            continue;
          }
         
          
          /* For source types need to add to a list of event sources for
          this class
          */
          

          /* For default types need to add members to this class */
          if ((implTypeFlags & IMPLTYPEFLAG_FDEFAULT) ||
              (implTypeFlags & IMPLTYPEFLAG_FSOURCE)) {  
            HREFTYPE href;
            ITypeInfo FAR *pNewTypeInfo;
            TYPEATTR *pNewTypeAttr;
          
            jprintf(env, PROGRESS, "Implemented Interface is default");
              
            hr = pTypeInfo->lpVtbl->GetRefTypeOfImplType(pTypeInfo,i,&href);
            if (FAILED(hr)) {
              jprintf(env, PROGRESS, "Cannot get ref type of impl type %d",i);
              continue;
            }

            hr = pTypeInfo->lpVtbl->GetRefTypeInfo(pTypeInfo,href,&pNewTypeInfo);
            if (FAILED(hr)) {
              jprintf(env, PROGRESS, "Cannot get type info of impl type %d",i);
              continue;
            }

            hr = pNewTypeInfo->lpVtbl->GetTypeAttr(pNewTypeInfo,&pNewTypeAttr);
            if (FAILED(hr)) {
              jprintf(env, PROGRESS, "Cannot get type Attr of impl type %d",i);
              continue;
            }
          
            if (implTypeFlags & IMPLTYPEFLAG_FSOURCE) {       
              collect_event_source_information(env,get_index_in_containing_lib(pNewTypeInfo), 
                                               pNewTypeInfo,
                                               pNewTypeAttr,
                                               pNewTypeAttr->typekind,
                                               node);                                                
            }
            else {
              jprintf(env,DETAIL, "Collect typeinfo member of implemented interface %d",i);
              collect_typeinfo_members(env, get_index_in_containing_lib(pNewTypeInfo),
                                    pNewTypeInfo,
                                    pNewTypeAttr,
                                    pNewTypeAttr->typekind,
                                    node);
              }
          }   
            /* Need to check that this interface itself is due to be emitted or
             emitted already */
        }
      }
    }
    return;
}
 

/*****************************************************************************
 * is_insertable
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
 static void is_insertable_or_control (GUID *clsid, CLASS_INFO *pType)
{
  long     key_status;
  unsigned short *clsid_name;
  char    *subkey_name = NULL;
  HKEY     class_id_key_handle;
  HKEY     class_id_key_handle2;
  HRESULT  hr;

  pType->isInsertable = FALSE;
  pType->isControl = FALSE;

  key_status = 
    RegOpenKeyEx
    (HKEY_CLASSES_ROOT,   /* handle of top-level key. always open */
    "CLSID",   /* name of subkey to open */
    0,                  /* ulOptions is reserved; must be unsigned long zero */
    KEY_READ,            /* security access mask */
    &class_id_key_handle); /* receives address of handle of open key */

  if (key_status != ERROR_SUCCESS) 
    return;

  hr = StringFromCLSID(clsid, &clsid_name);

  if (FAILED(hr))
    return;

  if (! clsid_name)
    return;

  subkey_name = unicode_to_ascii(clsid_name);

  /* Free the string allocated by StringFromCLSID */
  CoTaskMemFree(clsid_name);

  key_status = 
    RegOpenKeyEx
    (class_id_key_handle,
    subkey_name,         /* name of subkey to open */
    0,                  /* ulOptions is reserved; must be unsigned long zero */
    KEY_READ,            /* security access mask */
    &class_id_key_handle2); /* receives address of handle of open key */

  free(subkey_name);

  RegCloseKey(class_id_key_handle);
  class_id_key_handle = class_id_key_handle2;
  class_id_key_handle2 = 0;

  if (key_status != ERROR_SUCCESS) 
    return;

  key_status = 
    RegOpenKeyEx
    (class_id_key_handle,
    "Insertable",       /* name of subkey to open */
    0,                  /* ulOptions is reserved; must be unsigned long zero */
    KEY_READ,           /* security access mask */
    &class_id_key_handle2); /* receives address of handle of open key */

  if (key_status == ERROR_SUCCESS)
    pType->isInsertable = TRUE;

  RegCloseKey(class_id_key_handle2);

  key_status = 
    RegOpenKeyEx
    (class_id_key_handle,   /* handle of top-level key. always open */
    "Control",             /* name of subkey to open */
    0,                  /* ulOptions is reserved; must be unsigned long zero */
    KEY_READ,            /* security access mask */
    &class_id_key_handle2); /* receives address of handle of open key */

  if (key_status == ERROR_SUCCESS)
    pType->isControl = TRUE;

  RegCloseKey(class_id_key_handle);
  RegCloseKey(class_id_key_handle2);

  return;
}

/*****************************************************************************
 * collect_license_if_any
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes: In ActiveX licensing consists of either a verified license (
 *   development) or a runtime license key.  Components that require
 *   licensing will provide an IClassFactory2 interface.  
 *   At emit time BeanXporter will get the IClassFactory2 interface for
 *   the component.  If the component provides a runtime license key,
 *   that key will be emitted as a license object in the Java class that
 *   is emitted.
 *   At creation time BeanXporter will check to see whether the component
 *   can be created without a license key, if so BeanXporter will use 
 *   CoCreateInstance.  If a license key is required BeanXporter will use 
 *   the one passed in from the Java code.
 *   See create_object_from_license() in xcontain.c for the implementation of
 *   the licensed create.
 *     -----
 *   Modifications:
 *****************************************************************************/
static void collect_license_if_any(JNIEnv *env, CLASS_INFO *class_info)
{
  HRESULT hr;
  IClassFactory2 *pClassFactory = NULL;
  LICINFO licenseInfo;
  BOOL fRuntimeKeyAvail;
  BOOL fLicVerified;
  BSTR licenseKey = NULL;
  
  jprintf(env, DETAIL, "collect license if necessary");
  
  /* Required to make sure that I can call CoGetClassObject.
  It only makes sense to call this once per thread, so
  this call will probably need to be moved out of here
  */
  OleInitialize(NULL);
  
  /* Get IClassFactory2 */
  hr = CoGetClassObject(  
    class_info->cclsid,  //CLSID associated with the class object
    CLSCTX_INPROC_SERVER |
    CLSCTX_LOCAL_SERVER,  //Context for running executable code
    NULL,                    //Pointer to machine on which the object is to 
    // be instantiated
    &IID_IClassFactory2,      //Reference to the identifier of the interface
    (LPVOID *) &pClassFactory      //Address of output variable that receives the 
    // interface pointer requested in riid);
    );
  
  jprintf(env, DETAIL, "after CoGetClassObject");
  
  if (FAILED(hr))
  {
    jprintf(env, DETAIL, "Failed to get IClassFactory2, reason = 0x%x",
      hr);
    return;
  }
  
  if (pClassFactory == NULL)
  {
    jprintf(env, DETAIL, "Failed to get IClassFactory2");
    return;
  }
  
  jprintf(env, DETAIL, "Found an IClassFactory2\n");
  
  hr = pClassFactory->lpVtbl->GetLicInfo(pClassFactory, &licenseInfo);
  
  if (FAILED(hr))
  {
    pClassFactory->lpVtbl->Release(pClassFactory);
    jprintf(env, DETAIL, "Failed to get License Info");
    return;
  }
  
  fRuntimeKeyAvail = licenseInfo.fRuntimeKeyAvail;
  fLicVerified = licenseInfo.fLicVerified;
  
  jprintf(env, DETAIL, "License key available = %s\n", (fRuntimeKeyAvail ? "TRUE" : "FALSE"));
  jprintf(env, DETAIL, "License verified = %s\n", (fLicVerified ? "TRUE" : "FALSE"));
  
  if(fRuntimeKeyAvail)
  {
    hr = pClassFactory->lpVtbl->RequestLicKey(pClassFactory, 0, &licenseKey);
    
    if (FAILED(hr))
    {
      pClassFactory->lpVtbl->Release(pClassFactory);
      jprintf(env, DETAIL, "Failed to get License Key");
      return;
    }
    
    if (licenseKey)
    {
      class_info->license = licenseKey;
    }   
  }
  pClassFactory->lpVtbl->Release(pClassFactory);
}


/*****************************************************************************
 * collect_type_information
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
void collect_type_information(JNIEnv *env, LIBRARY_INFO *libInfo,
                                     int type_info_number, ITypeInfo *pTypeInfo) 
{
    long hr;
    TYPEATTR *pTypeAttr;
    TYPEKIND typekind;
    CLASS_INFO *node = NULL;
    BSTR bstrName, bstrDocString, bstrHelpFile; 
    static GUID *cclsid; 
    
    hr = pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr);
    if (FAILED(hr) || !pTypeAttr) {
      jprintf(env, DERROR, "Could not get type attributes for type library");
      return;
    }
    typekind = pTypeAttr->typekind;

    if (typekind == TKIND_COCLASS || typekind == TKIND_DISPATCH ||
        typekind == TKIND_ENUM) {
      hr = pTypeInfo->lpVtbl->GetDocumentation
        (pTypeInfo, -1, &bstrName, &bstrDocString, NULL, &bstrHelpFile);
      if (FAILED(hr)) {
        jprintf(env, DERROR, "Could not get doc for type");
        return;  
      }
      cclsid = &(pTypeAttr->guid);
      node = (CLASS_INFO *) malloc(sizeof(CLASS_INFO));
      initialize_class_info(node);   
      node->library = libInfo;
      node->cclsid = cclsid;
      node->pTypeInfo = pTypeInfo;
      node->containing_type_info = type_info_number;
      node->bstrName = bstrName;
      node->bstrDocString = bstrDocString;
      node->bstrHelpFile = bstrHelpFile;
      switch (typekind) {
      case TKIND_COCLASS: {
        node->className = make_classname_from_wide_string(env,bstrName);
        node->sourceFileName = make_filename(libInfo->packageName, 
                                             node->className, TRUE, 
                                             FILE_TYPE_DEFAULT); 
        node->classFileName = make_filename(libInfo->packageName, 
                                             node->className, FALSE, 
                                             FILE_TYPE_DEFAULT);

        node->beanInfo = malloc(sizeof(BEAN_INFO));
        initialize_bean_info(node->beanInfo);

        node->beanInfo->beanInfoName = make_beaninfo_name(node->className);
        node->beanInfo->beanInfoFileName = make_filename(libInfo->packageName, 
                                             node->beanInfo->beanInfoName, TRUE,
                                             FILE_TYPE_DEFAULT);
        
        /* Check if it actually is insertable here */
        /* node->isInsertable = is_insertable(cclsid); */

        is_insertable_or_control(cclsid, node);
        
        if ((pTypeAttr->wTypeFlags & TYPEFLAG_FLICENSED) != 0)
        {
          node->isLicensed = TRUE;
          collect_license_if_any(env, node);
        }
        

        node->isCreatable = TRUE;
        break;
                          }
      case TKIND_DISPATCH: {
        node->className = make_classname_from_wide_string(env, bstrName);        
        node->sourceFileName = make_filename(libInfo->packageName, 
          node->className, TRUE, FILE_TYPE_DEFAULT); 
        node->classFileName = make_filename(libInfo->packageName, 
                                             node->className, FALSE, 
                                             FILE_TYPE_DEFAULT); 
        break;
                           }

      case TKIND_ENUM: {
        node->className = make_classname_from_wide_string(env, bstrName);
        node->sourceFileName = make_filename(libInfo->packageName, 
                                             node->className, TRUE, 
                                             FILE_TYPE_DEFAULT); 
        node->classFileName = make_filename(libInfo->packageName, 
                                             node->className, FALSE, 
                                             FILE_TYPE_DEFAULT); 
        node->isInterface = TRUE;  
        break;
                           }
      }
        if (node) {
          if (!(libInfo->classes_tail)) {
            libInfo->classes_head = node;
            libInfo->classes_tail = node;
          } else {
            libInfo->classes_tail->next = node;
            libInfo->classes_tail = node;
          }
        }

        collect_typeinfo_members(env, type_info_number, pTypeInfo,
          pTypeAttr, typekind, node);
    }
}


/*****************************************************************************
 * synchronize_event_sources
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void synchronize_event_sources(JNIEnv *env)
{
  /* Iterate over each LIBRARY_INFO,  
     For each EVENT_DESCRIPTOR in that library
     find the matching CLASS_INFO in the CLASS_INFO list
     and hookup
  */
  LIBRARY_INFO *library_node;
  EVENT_SET_DESCRIPTOR *event_node;
  CLASS_INFO *class_node;

  library_node = libraries_head;

  while(library_node)
  {
    event_node = library_node->event_sources_head;
    while(event_node) {
        class_node = library_node->classes_head;
        while(class_node) {

          if (IsEqualGUID(class_node->cclsid, event_node->type))
          {
            event_node->class_info = class_node;
            class_node->listenerSourceFileName =
                  make_filename(class_node->library->packageName,
                                         class_node->className, 
                                         TRUE, FILE_TYPE_LISTENER);
            class_node->listenerClassFileName =
                  make_filename(class_node->library->packageName,
                                         class_node->className, FALSE, 
                                         FILE_TYPE_LISTENER);
            class_node->eventSourceFileName =
                  make_filename(class_node->library->packageName,
                                         class_node->className, 
                                         TRUE, FILE_TYPE_EVENT);
            class_node->eventClassFileName =
                  make_filename(class_node->library->packageName,
                                         class_node->className, FALSE, 
                                         FILE_TYPE_EVENT);

          }
          class_node = class_node->next;
        }
     event_node = event_node->next;
    }
    library_node = library_node->next;
  }
}

/*****************************************************************************
 * read_type_library_and_emit_all_classes
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void read_type_library_and_emit_all_classes(JNIEnv *env, ITypeLib *pTlib)
{
  long hr;
  LIBRARY_INFO *libInfo;
  LIBRARY_INFO *node;
  const GUID *libid;
  BOOL alreadyCollected = FALSE;


  /* Create a new LIBRARY_INFO */
  libInfo = (LIBRARY_INFO *) malloc(sizeof(LIBRARY_INFO));
  initialize_lib_info(libInfo);
  
  hr = collect_library_information(env,pTlib,libInfo);
  
 
  if (FAILED(hr)) {
    jprintf(env, DERROR, "Failed to collect information on type library");
    return;
  }

  libid = libInfo->libid;
  
  /* If the info for the library has already been collected 
     then just return
  */
  node = libraries_head;
  while (node) {
    if (IsEqualGUID(node->libid,libid)) {
      alreadyCollected = TRUE;
      break;
    }
    node = node->next;
  }

  if (! alreadyCollected) {
    if (! libraries_tail) {
      libraries_head = libInfo;
      libraries_tail = libInfo;
    } else {
      libraries_tail->next = libInfo;
      libraries_tail = libInfo;
    }

    collect_library_details(env,pTlib,libInfo);
  }
  
  synchronize_event_sources(env);

  emit_everything(env);
  if (!useJavac)
    jemit_everything(env);
    
       
  pTlib->lpVtbl->Release(pTlib);
} 


/*****************************************************************************
 * read_type_library_and_emit_one_class
 *
 *   Description: Emit only the required file containing the methods and 
 *                properties of a single GUID
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void read_type_library_and_emit_one_class(JNIEnv *env, ITypeLib *pTlib,
                                                 const GUID *clsid)
{
    long hr;
    unsigned int i;
    ITypeInfo *pTypeInfo;
    LIBRARY_INFO *libInfo;
    LIBRARY_INFO *node;
    CLASS_INFO *classNode;
    const GUID *libid;
    BOOL alreadyCollected = FALSE;

    /* Create a new LIBRARY_INFO */
    libInfo = (LIBRARY_INFO *) malloc(sizeof(LIBRARY_INFO));
    initialize_lib_info(libInfo);
    
    hr = collect_library_information(env,pTlib,libInfo);
    if (FAILED(hr)) {
      jprintf(env, DERROR, "Failed to collect information on type library");
      return;
    }

    libid = libInfo->libid;

    /* Check to see if library has already been collected
    */
    node = libraries_head;
    while (node) {
      if (IsEqualGUID(node->libid,libid)) {
        classNode = node->classes_head;
        while(classNode) {
            if (IsEqualGUID(classNode->cclsid,clsid)) {
                alreadyCollected = TRUE;
                break;
            }
          classNode = classNode->next;
        }
        break;
      }
      node = node->next;
    }

    if (! alreadyCollected) {
      hr = pTlib->lpVtbl->GetTypeInfoOfGuid(pTlib, clsid, &pTypeInfo);
      if (SUCCEEDED(hr)) {
        i = get_index_in_containing_lib(pTypeInfo);
        collect_type_information(env, libInfo, i, pTypeInfo);
      } else {
        jprintf(env, DERROR, "Failed to get type info HR = 0x%x", hr);
      }
    }
   
    synchronize_event_sources(env);

    emit_everything(env); 
    if (!useJavac)
      jemit_everything(env);
    
    pTlib->lpVtbl->Release(pTlib);
}


/*****************************************************************************
 * get_zeroth_value_from_hkey
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
        long RegEnumValue( 
        HKEY hKey,  / handle of key to query 
        unsigned long dwIndex,  / index of value to query 
        LPTSTR lpValueName, / address of buffer for value string 
        LPunsigned long lpcbValueName, / address for size of value buffer 
        LPunsigned long lpReserved, / reserved 
        LPunsigned long lpType, / address of buffer for type code 
        LPBYTE lpData, / address of buffer for value data 
        LPunsigned long lpcbData / address for size of data buffer 
      ); 
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *get_zeroth_value_from_hkey(HKEY hkey)
{
    long key_status;
    char *lpValueName;
    char *buffer_for_class_id;
    unsigned long size_of_name_buffer = 128;
    unsigned long size_of_data_buffer = 128;

    lpValueName = (char *) malloc(size_of_name_buffer * sizeof(char));
    buffer_for_class_id = (char *) malloc(size_of_data_buffer * sizeof(char));
    key_status = RegEnumValue(hkey, 0, lpValueName, &size_of_name_buffer, NULL,
      NULL, buffer_for_class_id, &size_of_data_buffer);
    if (key_status == ERROR_MORE_DATA) {
      free(lpValueName);
      free(buffer_for_class_id);
      lpValueName = (char *) malloc(size_of_name_buffer * sizeof(char));
      buffer_for_class_id = (char *) malloc(size_of_data_buffer *
                             sizeof(char));
      key_status = RegEnumValue
        (hkey, 0, lpValueName, &size_of_name_buffer, NULL,
        NULL, buffer_for_class_id, &size_of_data_buffer);
    }

    free(lpValueName);
    if (key_status == ERROR_SUCCESS) {
      return buffer_for_class_id;
    } else {
      free(buffer_for_class_id);
      return NULL;
    }
}




/*****************************************************************************
 * get_subkey_data_value
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static char *get_subkey_data_value (JNIEnv *env, HKEY desired_class_id_key_handle,
				    char *subkeyname)
{
    long     key_status;
    char    *buffer_for_class_id;
    unsigned long    class_id_key_index = 0;
    unsigned long    buffer_size = 50;
    unsigned long    cbValueName = 50;
    HKEY     subkey_handle;

    key_status = RegOpenKeyEx
	(desired_class_id_key_handle, subkeyname,
	 0, KEY_READ, &subkey_handle);
    if (key_status != ERROR_SUCCESS) {
	jprintf(env, DUMP, "Failed to open \"%s\" subkey.  Status = 0x%x", 
		subkeyname, key_status);
	return (char *) NULL;
    }

    buffer_for_class_id = get_zeroth_value_from_hkey(subkey_handle);

    if (!buffer_for_class_id) {
	jprintf(env, DERROR, "Failed to open %s key #0.  Status = 0x%x", 
		subkeyname, key_status);
    }

    RegCloseKey(subkey_handle);

    return buffer_for_class_id;
}


/*****************************************************************************
 * get_typelib_libid
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 * StringFromCLSID
 * StringFromIID
 * StringFromGUID2
 * CLSIDFromString
 * IIDFromString
 *     -----
 *   Modifications:
 *****************************************************************************/
static GUID *get_typelib_libid(JNIEnv *env, const GUID *desired_clsid)
{
    long     hr;
    long     key_status;
    char    *ascii_for_desired_clsid;
    HKEY     class_id_key_handle;
    HKEY     desired_class_id_key_handle;
    GUID    *return_clsid;
    unsigned short   *name_for_desired_clsid;
    unsigned long     class_id_key_index = 0;
    unsigned long     buffer_size = 50;

    key_status = 
	RegOpenKeyEx
	(HKEY_CLASSES_ROOT,   /* handle of top-level key. always open */
	 /* HKEY_CLASSES_ROOT is not truly a top-level key; it actually
	    is a link to HKEY_LOCAL_MACHINE\Software\Classes.  It is 
	    provided for backwards compatibility with Win16. */
	 "CLSID",   /* name of subkey to open */
	 0,          /* ulOptions is reserved; must be unsigned long zero */
	 KEY_READ,            /* security access mask */
	 &class_id_key_handle); /* receives address of handle of open key */

    if (key_status != ERROR_SUCCESS) {
	jprintf(env, DERROR,
          "Failed to open \"CLSID\" key.  Status = 0x%x", key_status);
	return (GUID *) &GUID_NULL;
    }

    hr = StringFromCLSID(desired_clsid, &name_for_desired_clsid);
    if (FAILED(hr)) return (GUID *) &GUID_NULL;

    ascii_for_desired_clsid = unicode_to_ascii(name_for_desired_clsid);
    CoTaskMemFree(name_for_desired_clsid);

    key_status = RegOpenKeyEx
	(class_id_key_handle, ascii_for_desired_clsid,
	 0, KEY_READ, &desired_class_id_key_handle);
    RegCloseKey(class_id_key_handle);
    if (key_status != ERROR_SUCCESS) {
	jprintf(env, DERROR, "Failed to open key %s.  Status = 0x%x",
		ascii_for_desired_clsid, key_status);
	return (GUID *) &GUID_NULL;
    }
    
    free(ascii_for_desired_clsid);
    ascii_for_desired_clsid = get_subkey_data_value(env,
                                desired_class_id_key_handle,
						    "TypeLib");
    RegCloseKey(desired_class_id_key_handle);
    return_clsid = (GUID *) malloc(sizeof(GUID));
    name_for_desired_clsid = ascii_to_unicode(ascii_for_desired_clsid);
    free(ascii_for_desired_clsid);

    hr = CLSIDFromString((LPOLESTR) name_for_desired_clsid, return_clsid);
    free(name_for_desired_clsid);

    print_iid_info(env, PROGRESS, "Returning libid ", return_clsid);

    return return_clsid;
}



/*****************************************************************************
 * get_filename_from_typelib
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
unsigned short *get_filename_from_typelib(JNIEnv *env, GUID *libid)
{
    long  hr;
    long     key_status;
    unsigned short   *name_for_libid = NULL;
    char    *buffer_for_class_id;
    char    *ascii_for_libid;
    char    version[16], next_version[16];
    int      vn = 0;
    unsigned long    class_id_key_index = 0;
    unsigned long    buffer_size = 50;
    HKEY     class_id_key_handle;
    HKEY     desired_class_id_key_handle;
    HKEY     typelib_key_handle;
    WORD     langID;
    char buf[10];

    key_status = 
      RegOpenKeyEx
      (HKEY_CLASSES_ROOT,   /* handle of top-level key. always open */
                            /* HKEY_CLASSES_ROOT is not truly a top-level key;
                               it actually is a link to
                               HKEY_LOCAL_MACHINE\Software\Classes.  It is 
                               provided for backwards compatibility with
                               Win16. */
     "TypeLib",   /* name of subkey to open */
     0,                 /* ulOptions is reserved; must be unsigned long zero */
     KEY_READ,            /* security access mask */
     &class_id_key_handle); /* receives address of handle of open key */
    
    if (key_status != ERROR_SUCCESS) {
      jprintf(env, DERROR,
        "Failed to open \"TypeLib\" toplevel key.  Status = 0x%x", key_status);
      return NULL;
    }

    hr = StringFromCLSID(libid, &name_for_libid);
    if (FAILED(hr))
        return NULL;

    ascii_for_libid = unicode_to_ascii(name_for_libid);

    /* StringFromCLSID allocated the string in name_for_libid */
    CoTaskMemFree(name_for_libid);
    name_for_libid = NULL;

    key_status = RegOpenKeyEx
      (class_id_key_handle, ascii_for_libid,
      0, KEY_READ, &desired_class_id_key_handle);
    if (key_status != ERROR_SUCCESS) {
      jprintf(env, DERROR, "Failed to open key %s.  Status = 0x%x",
        ascii_for_libid, key_status);
      free(ascii_for_libid);
      return NULL;
    }

    free(ascii_for_libid);

    key_status = RegEnumKey
      (desired_class_id_key_handle, vn, version, sizeof (version));
    if (key_status != ERROR_SUCCESS) {
      jprintf(env, DERROR,
        "Failed to get zeroth value of typelib key.  Status = 0x%x", 
        key_status);
      return NULL;
    }

    /* The versions may not be in ascending order, so we must keep track of
       the highest version as we loop through them. */
    next_version[0] = 0;
    while (key_status == ERROR_SUCCESS) {
      if (strcmp(next_version, version) > 0)
        strcpy(version, next_version);

      key_status = RegEnumKey
        (desired_class_id_key_handle, ++vn, next_version,
        sizeof (next_version));
    } 

    key_status = RegOpenKeyEx
      (desired_class_id_key_handle, version,
      0, KEY_READ, &typelib_key_handle);
    if (key_status != ERROR_SUCCESS) {
      jprintf(env, DERROR, "Failed to open \"%s\" key.  Status = 0x%x", 
        version, key_status);
      return NULL;
    } else {
      jprintf(env, DUMP, "Opened version \"%s\" of type library.", version);
    }

    /* The next entry is the lower 16 bits of the LCID (aka LANGID). 
     * This can vary significantly  0 == language neutral,  
     * 9 == basic English, 409 == American English, etc
     * The primary LANGID is the last hex digit of the LANGID.
     * So I try the following in order:
     * GetUserDefaultLangID()
     * Primary LangID of user LangID
     * GetSystemDefaultLangID()
     * Primary LangID of system LangID
     * "0" - language neutral
     * "9" - Basic english
     * "409" - American English
     */

    langID = GetUserDefaultLangID();
    sprintf(buf,"%x",langID);

    RegCloseKey(desired_class_id_key_handle);
    key_status = RegOpenKeyEx
      (typelib_key_handle, buf,
      0, KEY_READ, &desired_class_id_key_handle);

    if (key_status != ERROR_SUCCESS) {

      langID = PRIMARYLANGID(langID);
      sprintf(buf,"%x",langID);

      key_status = RegOpenKeyEx
      (typelib_key_handle, buf,
      0, KEY_READ, &desired_class_id_key_handle);

    if (key_status != ERROR_SUCCESS) {
       
       langID = GetSystemDefaultLangID();
       sprintf(buf,"%x",langID);   
       
       key_status = RegOpenKeyEx
         (typelib_key_handle, buf,
         0, KEY_READ, &desired_class_id_key_handle);

       if (key_status != ERROR_SUCCESS) {

         langID = GetSystemDefaultLangID();
         sprintf(buf,"%x",langID);   

         key_status = RegOpenKeyEx
         (typelib_key_handle, buf,
         0, KEY_READ, &desired_class_id_key_handle);

         if (key_status != ERROR_SUCCESS) {

          langID = PRIMARYLANGID(langID);

          sprintf(buf,"%x",langID);   

          key_status = RegOpenKeyEx
            (typelib_key_handle, buf,
            0, KEY_READ, &desired_class_id_key_handle);

         if (key_status != ERROR_SUCCESS) {

            key_status = RegOpenKeyEx
              (typelib_key_handle, "0",
              0, KEY_READ, &desired_class_id_key_handle);

            if (key_status != ERROR_SUCCESS) {
                key_status = RegOpenKeyEx
                  (typelib_key_handle, "9",
                  0, KEY_READ, &desired_class_id_key_handle);

                if (key_status != ERROR_SUCCESS) {
                  key_status = RegOpenKeyEx
                  (typelib_key_handle, "409",
                  0, KEY_READ, &desired_class_id_key_handle);

                  if (key_status != ERROR_SUCCESS) {
                      jprintf(env, DERROR, "Failed to open langid key.  Status = 0x%x", 
                          version, key_status);
                  }
                }
              }
            }
          }
         }
       }
    }

    RegCloseKey(typelib_key_handle);
    key_status = RegOpenKeyEx
      (desired_class_id_key_handle, "win32",
      0, KEY_READ, &typelib_key_handle);
    RegCloseKey(desired_class_id_key_handle);
    if (key_status != ERROR_SUCCESS) {
      jprintf(env, DERROR,
        "Failed to open \"win32\" key.  Status = 0x%x", key_status);
      return NULL;
    }

    buffer_for_class_id = get_zeroth_value_from_hkey(typelib_key_handle);

    RegCloseKey(typelib_key_handle);
    RegCloseKey(class_id_key_handle);

    name_for_libid = ascii_to_unicode(buffer_for_class_id);
    free(buffer_for_class_id);
    
    jprintf(env, DETAIL, "Returning %ls", name_for_libid);
    
    return name_for_libid;
} 

/*****************************************************************************
 * register_control_or_library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void register_control_or_library (char *clsid, HKEY desired_class_id_key_handle,
			      JNIEnv *env, jobject pThis, jmethodID mid, BOOL libraryOnly)
{
    char *libidString = NULL;
    char *progid = NULL;
    jstring jl, jp, jc;
    WCHAR * libName;
    WCHAR * libFileName;
    HRESULT hr;
    GUID libid;

    if (! mid)
        return;  

    jprintf(env, DUMP, "Inside register control: class id = %s", clsid); 
    libidString = get_subkey_data_value(env, desired_class_id_key_handle,
                    "TypeLib");
    
    if (!libidString)
      return;

    libName = ascii_to_unicode(libidString);

    hr = CLSIDFromString(libName, &libid);
    free(libName);      
    if (FAILED(hr))
    {
      jprintf(env, DUMP, "CLSIDFromString failed:", libidString); 
      return;      
    }
    
    libFileName = get_filename_from_typelib(env, &libid);

    if (! libFileName)
    {
      jprintf(env, DUMP, "Failed to get LibraryPath");
      return;
    }
      
    if (libraryOnly) {
      ITypeLib *pTypeLib;
      LIBRARY_INFO *node;
      BSTR bstrDocString;
      
      hr = LoadTypeLib(libFileName, &pTypeLib);

      if (FAILED(hr)) {
        jprintf(env, DUMP, "Failed to load type library %s", libFileName);         
        return;  
      }
              
      node = (LIBRARY_INFO *) malloc(sizeof(LIBRARY_INFO));
      initialize_lib_info(node);
      collect_library_information(env,pTypeLib,node);
      bstrDocString = node->bstrDocString;
                
      if (bstrDocString) {
        jp = wstring_to_jstring(env, (WCHAR *) bstrDocString);
        jc = NULL;
        jl = wstring_to_jstring(env, libFileName);
                   
        (*env)->CallVoidMethod(env, pThis, mid, jp, jc, jl);  
      }
    }
    else {
      if (libidString) {
        progid = get_subkey_data_value(env, desired_class_id_key_handle,
                "ProgID");
      }

      if (progid) {
        if (mid) {
          jp = c_to_java_string(env, progid);
          jc = c_to_java_string(env, clsid);
          jl = wstring_to_jstring(env, libFileName);
          /*
          jprintf(env, DUMP,
            "About to call method.  env = 0x%x, pThis = 0x%x, methodid = 0x%x",
          env, pThis, mid);
          jprintf(env, DUMP, "progid = %s, clsid = %s, libid = %s",
          progid, clsid, libid);
          */
          (*env)->CallVoidMethod(env, pThis, mid, jp, jc, jl);
        }
        jprintf(env, DUMP, "  Name:  %s", progid);
        jprintf(env, DUMP, "  CLSID: %s", clsid);
        jprintf(env, DUMP, "  LIBID: %s", libidString);
        jprintf(env, DUMP, "  ");

        free(progid);
      }
    }

    free(libidString);
    free(libFileName);
    jprintf(env, DUMP, "Finished register control");
}


/*****************************************************************************
 * browse_type_library_by_name
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static jobject JNICALL browse_type_library_by_name
  (JNIEnv *env, GUID *clsid, unsigned short *library_name)
{
    IProvideClassInfo *pPCI = (IProvideClassInfo *) NULL;
    IDispatch *pDispatch = (IDispatch *) NULL;
    ITypeLib *pTypeLib;
    long hr;

    hr = LoadTypeLib(library_name, &pTypeLib);
    if (SUCCEEDED(hr)) {
	jprintf(env, DETAIL, "Loaded type library");
    } else {
	jprintf(env, DERROR, "Failed to load type library %ls", library_name);
	if (hr == TYPE_E_CANTLOADLIBRARY) {
	    jprintf(env, DERROR, "(TYPE_E_CANTLOADLIBRARY)");
	} else {
	    jprintf(env, DERROR, "HR = 0x%x", hr);
	}
	jprintf(env, DERROR, "Unable to extract type information from %ls.",
		library_name);
	return (jobject) NULL;
    }

    read_type_library_and_emit_all_classes(env, pTypeLib); 
    jprintf(env, PROGRESS, "Done browsing library %ls", library_name);
    return (jobject) NULL;
}


/*****************************************************************************
 * browse_type_library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static jobject JNICALL browse_type_library
  (JNIEnv *env, GUID *clsid, GUID *libid)
{
    IProvideClassInfo *pPCI = (IProvideClassInfo *) NULL;
    IDispatch *pDispatch = (IDispatch *) NULL;
    unsigned short *type_lib_file;

    print_iid_info(env,ERROR,"LIBID before this",libid);
    type_lib_file = get_filename_from_typelib(env, libid);
    if (type_lib_file) {
	return browse_type_library_by_name(env, clsid, type_lib_file);
    } else {
	jprintf(env, DERROR, "Failed to get filename from typelib");
	return (jobject) NULL;
    }
}

/*****************************************************************************
 * add_file_to_files_list
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void add_file_to_files_list(JNIEnv *env, jobject pThis, jmethodID mid, 
                                   char *className, BOOL isCreatable)
{
  jboolean isBean;
  jstring filePath;

  if (mid && env) {
 
    if (isCreatable) 
    {
      isBean = JNI_TRUE;
    }
    else isBean = JNI_FALSE;

    filePath = c_to_java_string(env, className);
    (*env)->CallVoidMethod(env, pThis, mid, filePath, isBean);
  }
}


/*****************************************************************************
 * beanify
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void beanify (JNIEnv *env, unsigned short *clsid_string,
                           unsigned short *libraryName)
{
    GUID clsid;
    long hr;

    if (clsid_string) {
      jprintf(env, PROGRESS, "beanifying class %ls", clsid_string);
        jprintf(env, PROGRESS, "library %ls", libraryName);
    }
    else jprintf(env, PROGRESS, "beanifying library %ls", libraryName);
  
    if (clsid_string) {
    hr = CLSIDFromString((LPOLESTR) clsid_string, &clsid);
    if (FAILED(hr)) {
	jprintf(env, DERROR, "clsid from string failed on %ls.  Code = 0x%x",
		clsid_string, hr);
	return;
    }
      browse_type_library_by_name(env, &clsid, libraryName);
    }
    else {
      browse_type_library_by_name(env, NULL, libraryName );
    }
}

/*****************************************************************************
 * set_current_dir
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL set_current_dir(JNIEnv *env, jstring dirpath)  
{
  LPSTR lpszCurDir;
  BOOL result;
  
  lpszCurDir = (LPSTR) java_to_c_string(env,dirpath);
	  
  GetCurrentDirectory(256,(LPSTR) saveCurrentDir);
  result = SetCurrentDirectory(lpszCurDir);
  free(lpszCurDir);
  return result;
}

/*****************************************************************************
 * reset_current_dir
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static BOOL reset_current_dir()
{
    return SetCurrentDirectory((LPSTR) saveCurrentDir);
}

/*****************************************************************************
 * set_emit_package
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void set_emit_package(JNIEnv *env, jstring packageString)
{
   if (user_chosen_emit_package != NULL)
       free(user_chosen_emit_package);

   user_chosen_emit_package = java_to_c_string(env, packageString);
}

/*****************************************************************************
 * set_emit_flags
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
static void set_emit_flags(jint flags) 
{
    if ((flags & USE_JAVAC) != 0)
        useJavac = TRUE;
    else useJavac = FALSE;

    if ((flags & EMIT_EXCEPTIONS) != 0) {
        emitExceptions = TRUE;
    }
    else 
    {
      emitExceptions = FALSE;
    }

    if ((flags & USE_VERSIONS) != 0) {
        useVersions = TRUE;
    }
    else {
      useVersions = FALSE;
    }
}






/*****************************************************************************
 * excel_version
 *
 *   Description: Sneaky name, it actually checks for licensing in a feeble
 *                way.
 *   
 *   Input Arguments:
 *   Returns: 7 if failed, 8 if succeeded
 *   Notes: 
 *     -----
 *   Modifications:
 *****************************************************************************/

static int get_range(char ch) 
{
  if ((ch >= '0') && (ch <= '9'))
      return (int) (ch - '0');

  if ((ch >= 'a') && (ch <= 'f'))
      return (int) 10 + (ch - 'a');

  return -1;
}   


int excel_version()  
{
  struct tm * ref;
  time_t tp;
  int major_ref, minor_ref, aux_ref;
  int major_cmp, minor_cmp, aux_cmp;
 
  time(&tp);
  ref = localtime(&tp);

  major_ref = ref->tm_mon + 1;  /* 1 = January */
  minor_ref = ref->tm_mday;  /* 1 -> 31 */
  aux_ref = (ref->tm_year + 1900);   /* 4 Digit Year */

  /* Decoding the gsc stamp */

  major_cmp = BETA_RESTRICTIONS_START_MONTH;
    
  minor_cmp = BETA_RESTRICTIONS_START_DAY;

  aux_cmp = BETA_RESTRICTIONS_START_YEAR;

  //printf("Month = %d, Day = %d, Year = %d\n", major_ref, minor_ref,
                                              // aux_ref);
  //printf("Month = %d, Day = %d, Year = %d\n", major_cmp, minor_cmp,
                                              // aux_cmp);

  if (
      (
       (major_ref <= (major_cmp + BETA_RESTRICTIONS_LENGTH)) &&
       (aux_cmp == aux_ref)
      ) ||
      (
       (aux_cmp == (aux_ref + 1)) &&
       ((major_ref + (12 - major_cmp)) <= BETA_RESTRICTIONS_LENGTH)
      )
     )
  {
    return 8;
  }
  else return 7;
}




/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_collect_info_about_controls
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_com_NativeMethodBroker_collect_1info
  (JNIEnv *env, jclass proxy, jobject pThis, jboolean detailed)
{
    long     key_status;
    int      nSubkey;
    char    *subkey_name = NULL;
    char    *buffer_for_class_name = NULL;
    unsigned long    class_id_key_index = 0;
    unsigned long    initial_buffer_size = 512;
    BOOL     done;
    HKEY     class_id_key_handle;
    HKEY     desired_class_id_key_handle;
    PFILETIME pFiletime;
    jclass classPointer;
    jmethodID mid = NULL;
    unsigned long    subkey_length;
    unsigned long    value_name_max_buffer_size = 512;


    key_status = 
	RegOpenKeyEx
	(HKEY_CLASSES_ROOT,   /* handle of top-level key. always open */
	 "CLSID",   /* name of subkey to open */
	 0,            /* ulOptions is reserved; must be unsigned long zero */
	 KEY_READ,            /* security access mask */
	 &class_id_key_handle); /* receives address of handle of open key */

    if (key_status != ERROR_SUCCESS) {
	jprintf(env, DERROR,
          "Failed to open \"CLSID\" key.  Status = 0x%x", key_status);
	return;
    }

    if (env && pThis) {
	classPointer = (*env)->GetObjectClass(env, pThis);

	mid = (*env)->GetMethodID
	    (env, classPointer,
	     "addActiveXInfoToList",
	     "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (mid == NULL) {
	    jprintf(env, DERROR, "Error: could not obtain method id");
	}
    }

    done = FALSE;
    pFiletime = (PFILETIME) malloc(sizeof(FILETIME));
    subkey_name = (char *) malloc(initial_buffer_size * sizeof(char));

    for (nSubkey=0; !done; nSubkey++) {
	subkey_length = value_name_max_buffer_size;
	subkey_name[0] = 0;

	key_status = RegEnumKey
	    (class_id_key_handle, // handle of key to enumerate 
	     nSubkey, // index of subkey to enumerate 
	     subkey_name, // address of buffer for subkey name 
	     subkey_length); // size of subkey buffer 
	if (key_status == ERROR_SUCCESS) {
	    key_status = RegOpenKeyEx
		(class_id_key_handle, subkey_name, 0,
		 KEY_ENUMERATE_SUB_KEYS | KEY_EXECUTE |
		 KEY_QUERY_VALUE, &desired_class_id_key_handle);
	    if (key_status == ERROR_SUCCESS) {
              if (detailed == JNI_TRUE)
                register_control_or_library(subkey_name,
                                            desired_class_id_key_handle,
                                            env, pThis, mid, FALSE);
              else
                register_control_or_library(subkey_name,
                                            desired_class_id_key_handle,
                                            env, pThis, mid, TRUE);

              RegCloseKey(desired_class_id_key_handle);
	    } else {
		jprintf(env, DERROR, "Failed to open key #%d.  Status = 0x%x",
			nSubkey, key_status);
		done = TRUE;
	    }
	} else {
	    jprintf(env, DUMP,
                 "Failed to obtain name for key #%d.  Status = 0x%x",
		    nSubkey, key_status);
	    done = TRUE;
	}
    }

    RegCloseKey(class_id_key_handle);
    if (subkey_name)
        free(subkey_name);
    if (pFiletime)
        free(pFiletime);
}

/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_beanify
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL Java_com_gensym_com_NativeMethodBroker_beanify
  (JNIEnv *env, jclass pThis, jstring clsid_jstring, jstring libid_jstring,
   jstring emit_package, jstring emit_directory, jint flags)
{
    unsigned short *clsid_string, *libid_string;

    set_emit_package(env, emit_package);
    set_current_dir(env, emit_directory);
    set_emit_flags(flags);

    if (clsid_jstring) {
      clsid_string = java_to_unicode_string(env, clsid_jstring);
    }
    else clsid_string = NULL;
    libid_string = java_to_unicode_string(env, libid_jstring);
    
    beanify(env, clsid_string, libid_string);
    reset_current_dir();
}


/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_beanify_1from_1progid
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jboolean JNICALL Java_com_gensym_com_NativeMethodBroker_beanify_1from_1progid
  (JNIEnv *env, jclass pThis, jstring progid_jstring,
   jstring emit_package, jstring emit_directory, jint flags)
{
    char *progid_string;
    char *clsid_string;
    char *libid_string;
    WCHAR *libid_wstring;
    WCHAR *libFileName;
    long     key_status;
    char    *subkey_name = NULL;
    HKEY     key_handle;
    HKEY     key_handle2;
    GUID    libid;
    HRESULT hr;

    if (progid_jstring) {
      progid_string = java_to_c_string(env, progid_jstring);
    }
    else {
        jprintf(env, DERROR, "Empty progid passed to beanify()");
        return JNI_FALSE;
    }
    
    key_status = 
      RegOpenKeyEx
      (HKEY_CLASSES_ROOT,   
      progid_string,   
      0,               
      KEY_READ,        
      &key_handle); 
    free(progid_string);

    if (key_status != ERROR_SUCCESS) 
      return FALSE;

    clsid_string = get_subkey_data_value(env, key_handle, "CLSID");

    RegCloseKey(key_handle);
    key_status = 
      RegOpenKeyEx
      (HKEY_CLASSES_ROOT,  
      "CLSID",   
      0,         
      KEY_READ,  
      &key_handle);

    if (key_status != ERROR_SUCCESS) 
      return FALSE;

    key_status = 
      RegOpenKeyEx
      (key_handle,   
      clsid_string,
      0,           
      KEY_READ,    
      &key_handle2);
    free(clsid_string);

    if (key_status != ERROR_SUCCESS) 
      return FALSE;

    libid_string = 
      get_subkey_data_value(env, key_handle2, "TypeLib");

    RegCloseKey(key_handle2);
    RegCloseKey(key_handle);
    if (libid_string == NULL)
      return FALSE;

    libid_wstring = ascii_to_unicode(libid_string);    
    free(libid_string);
    
    hr = CLSIDFromString(libid_wstring, &libid);
    free(libid_wstring);
    
    if (FAILED(hr)){
      return FALSE;
    }

    libFileName = get_filename_from_typelib(env, &libid);
    
    if (! libFileName)
      return FALSE;

    set_emit_package(env, emit_package);
    set_current_dir(env, emit_directory);
    set_emit_flags(flags);

    beanify(env, NULL, libFileName);
    free(libFileName);
    reset_current_dir();
    return TRUE;
}

/*****************************************************************************
 * Java_com_gensym_com_BeanXporter_set_1current_1dir
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jboolean JNICALL Java_com_gensym_com_BeanXporter_set_1current_1dir
        (JNIEnv *env, jclass pThis, jstring dir)
{
    BOOL result = set_current_dir(env, dir);
    if (result)
      return JNI_TRUE;
    else return JNI_FALSE;
}


/*****************************************************************************
 * Java_com_gensym_com_BeanXporter_reset_1current_1dir
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jboolean JNICALL Java_com_gensym_com_BeanXporter_reset_1current_1dir
      (JNIEnv *env, jclass pThis)
{
    BOOL result = reset_current_dir();
    if (result)
      return JNI_TRUE;
    else return JNI_FALSE;
}


/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_collect_1
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT void JNICALL
 Java_com_gensym_com_NativeMethodBroker_collect_1emitted_1files_1info
  (JNIEnv *env, jclass proxy, jobject pThis)
{
  jclass classPointer;
  jmethodID mid = NULL;
  LIBRARY_INFO *libNode;
  CLASS_INFO *classNode;
  char * className;
  
  if (env && pThis) {
    classPointer = (*env)->GetObjectClass(env, pThis);
    
    mid = (*env)->GetMethodID
      (env, classPointer,
	     "addFileToFilesList",
           "(Ljava/lang/String;Z)V");
    if (mid == NULL) {
      jprintf(env, DERROR, "Error: could not obtain method id");
    }

    libNode = libraries_head;
    while(libNode) {
        classNode = libNode->classes_head;
        while(classNode) {
          if (classNode->hasBeenEmitted) {
            className = classNode->sourceFileName;
            add_file_to_files_list(env, pThis, mid, 
              className, classNode->isCreatable);
            if (classNode->beanInfo) {
              add_file_to_files_list(env, pThis, mid,
                classNode->beanInfo->beanInfoFileName,
                FALSE);
            }
          }
          if (classNode->hasBeenEmittedAsListener) {
            add_file_to_files_list(env, pThis, mid, 
              classNode->listenerSourceFileName, FALSE);
          }
          if (classNode->hasBeenEmittedAsEvent) {
            add_file_to_files_list(env, pThis, mid, 
              classNode->eventSourceFileName, FALSE);
          }
          classNode = classNode->next;
        }
      libNode = libNode->next;
    }
  }
  /* Consider making this a separate native function */

  reclaim_everything(env);
    
}

/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_beanify_1object
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jobject JNICALL Java_com_gensym_com_NativeMethodBroker_beanify_1object
  (JNIEnv *env, jclass pThis, jint pObj_address)
{
    PCOMOBJ pObj;
    long hr;
    int index;
    GUID *libid;
    IProvideClassInfo *pPCI = (IProvideClassInfo *) NULL;
    IDispatch *pDispatch = (IDispatch *) NULL;
    ITypeLib *pTypeLib;
    ITypeInfo *pTypeInfo;

    if (!pObj_address) {
	return (jobject) NULL;
    }

    pObj = (PCOMOBJ) pObj_address;
    jprintf(env, DETAIL, "ok, let's start. pObj = 0x%x", pObj_address);
    hr = pObj->pComInfo->lpVtbl->QueryInterface(pObj->pComInfo,
						&IID_IProvideClassInfo,
						&pPCI);
    if ((SUCCEEDED(hr))) {
	jprintf(env, PROGRESS, "This object DOES provide IProvideClassInfo");
	hr = pPCI->lpVtbl->GetClassInfo(pPCI, &pTypeInfo);
  if (SUCCEEDED(hr)) {
	    jprintf(env, PROGRESS, "Got class info");
	    hr = pTypeInfo->lpVtbl->GetContainingTypeLib(pTypeInfo, &pTypeLib,
							 &index);
	    if (SUCCEEDED(hr)) {
    read_type_library_and_emit_one_class(env, pTypeLib, pObj->clsid);
		jprintf(env, PROGRESS, 
                        "Finished beanifying object from its IProvideClassInfo");
	    } else {
		jprintf(env, DERROR, "Failed to get containing type library");
	    }
	} else {
	    jprintf(env, DERROR, "Failed to get class info");
	}
	pPCI->lpVtbl->Release(pPCI);
    } else {
	libid = get_typelib_libid(env, pObj->clsid);
	if (IS_NULL_GUID(libid)) {
	    jprintf(env, DERROR, "This object does not provide type information.");
	} else {
	    browse_type_library(env, NULL, libid);
	}
    }

    return (jobject) NULL;
}


/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_browse_1type_1library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jobject JNICALL Java_com_gensym_com_NativeMethodBroker_browse_1type_1library
  (JNIEnv *env, jclass pThis, jstring libname)
{
    unsigned short *wlibname;

    wlibname = java_to_unicode_string(env, libname);
    return browse_type_library_by_name(env, NULL, wlibname);
}


/*****************************************************************************
 * Java_com_gensym_com_NativeMethodBroker_browse_1default_1library
 *
 *   Description: 
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     -----
 *   Modifications:
 *****************************************************************************/
JNIEXPORT jobject JNICALL Java_com_gensym_com_NativeMethodBroker_browse_1default_1library
 (JNIEnv *env, jclass pThis)
{
    return browse_type_library_by_name
	(env, NULL, L"C:\\WINNT\\System32\\Msacal70.ocx");
    /* ("j:\\Public\\Books\\InsideCOM\\CODE\\CHAP11\\Server.tlb"); */
}

#endif /* WIN32 */
