/*****************************************************************************
* vartypes.c
*
* Authors: John Valente, Allan Scott
*  
*****************************************************************************/
#include "shared.h"
#include "dprintf.h"


#define VARTYPE_BITMASK      31   /* 0001 1111 */

#define NAME_FOR_NONEXISTENT_VARTYPE "NO_VARTYPE"
#define NAME_FOR_NONEXISTENT_JAVA_TYPE "NO_JAVA_TYPE"


#define JAVA_BOOLEAN     0
#define JAVA_SHORT       1
#define JAVA_INT         2
#define JAVA_FLOAT       3
#define JAVA_DOUBLE      4
#define JAVA_DATE        5
#define JAVA_STRING      6
#define JAVA_VARIANT     7
#define JAVA_IDISP       8
#define JAVA_UNKNOWN     9
#define JAVA_CURRENCY   10
#define JAVA_BYTE       11
#define JAVA_DECIMAL    12
#define JAVA_LONG       13
#define JAVA_COLOR      14
#define JAVA_VECTOR     15
#define JAVA_OBJECT     16
#define JAVA_VOID       17

#define JAVA_ARRAY         18
#define JAVA_VARIANT_ARRAY 19
#define JAVA_BOOLEAN_SA    20
#define JAVA_SHORT_SA      21
#define JAVA_INT_SA        22
#define JAVA_FLOAT_SA      23
#define JAVA_DOUBLE_SA     24
#define JAVA_DATE_SA       25
#define JAVA_STRING_SA     26
#define JAVA_VARIANT_SA    27
#define JAVA_IDISP_SA      28
#define JAVA_UNKNOWN_SA    29
#define JAVA_CURRENCY_SA   30
#define JAVA_BYTE_SA       31

#define JAVA_BOOLEAN_RP    32
#define JAVA_SHORT_RP      33
#define JAVA_INT_RP        34
#define JAVA_FLOAT_RP      35
#define JAVA_DOUBLE_RP     36
#define JAVA_DATE_RP       37
#define JAVA_STRING_RP     38
#define JAVA_VARIANT_RP    39
#define JAVA_IDISP_RP      40
#define JAVA_UNKNOWN_RP    41
#define JAVA_CURRENCY_RP   42
#define JAVA_BYTE_RP       43
#define JAVA_SA_RP         44
#define JAVA_SHORT_SA_RP   45
#define JAVA_INT_SA_RP     46
#define JAVA_FLOAT_SA_RP   47
#define JAVA_DOUBLE_SA_RP  48
#define JAVA_DATE_SA_RP    49
#define JAVA_STRING_SA_RP  50
#define JAVA_BOOLEAN_SA_RP 51
#define JAVA_VARIANT_SA_RP 52
#define JAVA_BYTE_SA_RP    53

typedef struct _VARTYPE_INFO_ 
{
    int  vtype_verify;
    int  java_type;
    char *name_for_type;
    char *wtypes_comment;
    jobject (*jvar_from_var)(JNIEnv*, VARIANT, jobject, int);
} VARTYPE_INFO;

typedef struct _JAVA_TYPE_INFO_ 
{
    int  jtype_verify;
    char *class_string;
    char *cast_string;
    char *java_type_string;
    char *jni_string;
    char *default_value_string;
    char *constructor_sig;
    jmethodID variant_constructor;
    jmethodID var_get_value_method;
    jclass java_class;
    jmethodID ref_get_value_method;
    jmethodID ref_set_value_method;
    jmethodID constructor;
} JAVA_TYPE_INFO;

typedef union _ALL_TYPES_UNION
{
  SHORT iVal;
  LONG lVal;
  FLOAT fltVal;
  DOUBLE dblVal;
  CY cyVal;
  DATE date;
  BSTR bstrVal;
  IDispatch *pdispVal;
  SCODE scode;
  VARIANT_BOOL boolVal;
  VARIANT varVal;
  IUnknown *punkVal;
  BYTE bVal;
  SAFEARRAY *parray;
} ALL_TYPES_UNION;

typedef struct _TEMP_REF
{
  ALL_TYPES_UNION out;
  ALL_TYPES_UNION in;
  int inVartype;
  int arrayLocked;
  int arrayInVariantRef;
  jobject pJavaRefParameter;
} TEMP_REF;

static jobject default_jvariant_from_unsupported_variant(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent);
static jobject short_jvariant_from_I2_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject int_jvariant_from_I4_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject float_jvariant_from_R4_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject double_jvariant_from_R8_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject date_jvariant_from_DATE_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject string_jvariant_from_BSTR_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject disp_jvariant_from_DISPATCH_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject boolean_jvariant_from_BOOL_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject byte_jvariant_from_UI1_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject short_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject int_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject float_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject double_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject date_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject string_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject boolean_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject variant_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject byte_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject short_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject int_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject float_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject double_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject date_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject string_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject boolean_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject variant_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);
static jobject byte_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent);


static JAVA_TYPE_INFO jtype_info[] = 
{
    { JAVA_BOOLEAN, "NotAClass",
      "Boolean", "boolean", "Z", "false"
    },
    { JAVA_SHORT, "NotAClass",
      "Short", "short", "S", "-1"
    },
    { JAVA_INT, "NotAClass",
      "Int", "int", "I",  "-1"
    },
    { JAVA_FLOAT, "NotAClass",
      "Float", "float", "F", "(float) -1"
    },
    { JAVA_DOUBLE, "NotAClass",
      "Double", "double", "D", "-1.0"
    },
    { JAVA_DATE, "java/util/Date",
      "Date", "Date", "Ljava/util/Date;", "null", "(J)V"
    },
    { JAVA_STRING, "java/lang/String",
      "String", "String", "Ljava/lang/String;", "null"
    },
    { JAVA_VARIANT, "com/gensym/com/Variant",
      "Variant", "Variant", "Lcom/gensym/com/Variant;", "null"
    },
    { JAVA_IDISP, "com/gensym/com/ActiveXDispatchable",
      "ActiveXDispatchable", "ActiveXDispatchable", "Lcom/gensym/com/ActiveXDispatchable;",
      "null"
    },
    { JAVA_UNKNOWN, "java/lang/Object",
      /* not yet implemented */
      "Generic", "Object", "Ljava/lang/Object;", "null"
    },
    { JAVA_CURRENCY, "java/lang/Object",
      /* not yet implemented */
      "Generic", "Object", "Ljava/lang/Object;", "null"
    },
    { JAVA_BYTE, "NotAClass",
      "Byte", "byte", "B", "-1"
    },
    { JAVA_DECIMAL, "java/lang/Object",
      /* not yet implemented */
      "Generic", "Object", "Ljava/lang/Object;", "null"
    },
    { JAVA_LONG, "NotAClass",
      "Long", "long", "J", "-1"
    },
    { JAVA_COLOR, "java/awt/Color",
      "Color", "Color", "Ljava/awt/Color;", "null"
    },
    { JAVA_VECTOR, "java/util/Vector",
      "Vector", "Vector", "Ljava/util/Vector;", "null"
    },
    { JAVA_OBJECT, "java/lang/Object",
      "Generic", "Object", "Ljava/lang/Object;", "null"
    },
    { JAVA_VOID, "NotAClass",
      "void", "void", "", "null"
    },
    { JAVA_ARRAY, "NotAClass",
      /* not yet implemented */
      "Generic array", "Object[]", "[Ljava/lang/Object;", "null"
    },
    { JAVA_VARIANT_ARRAY, "NotAClass",
      "Variant parameter array", "Variant[]",
      "[Lcom/gensym/com/Variant;", "null"
    },
    { JAVA_BOOLEAN_SA, "com/gensym/com/BooleanSafeArray",
      "BooleanSafeArray", "BooleanSafeArray",
      "Lcom/gensym/com/BooleanSafeArray;", "null", "(I)V"
    },
    { JAVA_SHORT_SA, "com/gensym/com/ShortSafeArray",
      "ShortSafeArray", "ShortSafeArray",
      "Lcom/gensym/com/ShortSafeArray;", "null", "(I)V"
    },
    { JAVA_INT_SA, "com/gensym/com/IntSafeArray",
      "IntSafeArray", "IntSafeArray",
      "Lcom/gensym/com/IntSafeArray;", "null", "(I)V"
    },
    { JAVA_FLOAT_SA, "com/gensym/com/FloatSafeArray",
      "FloatSafeArray", "FloatSafeArray",
      "Lcom/gensym/com/FloatSafeArray;", "null", "(I)V"
    },
    { JAVA_DOUBLE_SA, "com/gensym/com/DoubleSafeArray",
      "DoubleSafeArray", "DoubleSafeArray",
      "Lcom/gensym/com/DoubleSafeArray;", "null", "(I)V"
    },
    { JAVA_DATE_SA, "com/gensym/com/DateSafeArray",
      "DateSafeArray", "DateSafeArray",
      "Lcom/gensym/com/DateSafeArray;", "null", "(I)V"
    },
    { JAVA_STRING_SA, "com/gensym/com/StringSafeArray",
      "StringSafeArray", "StringSafeArray",
      "Lcom/gensym/com/StringSafeArray;", "null", "(I)V"
    },
    { JAVA_VARIANT_SA, "com/gensym/com/VariantSafeArray",
      "VariantSafeArray", "VariantSafeArray",
      "Lcom/gensym/com/VariantSafeArray;", "null", "(I)V"
    },
    { JAVA_IDISP_SA, "java/lang/Object",
      /* not yet implemented */
      "Generic safe array", "Object", "Ljava/lang/Object;", "null", "(I)V"
    },
    { JAVA_UNKNOWN_SA, "java/lang/Object",
      /* not yet implemented */
      "Generic safe array", "Object", "Ljava/lang/Object;", "null", "(I)V"
    },
    { JAVA_CURRENCY_SA, "java/lang/Object",
      /* not yet implemented */
      "Generic safe array", "Object", "Ljava/lang/Object;", "null", "(I)V"
    },
    { JAVA_BYTE_SA, "com/gensym/com/ByteSafeArray",
      "ByteSafeArray", "ByteSafeArray",
      "Lcom/gensym/com/ByteSafeArray;", "null", "(I)V"
    },
    { JAVA_BOOLEAN_RP, "com/gensym/com/BooleanRefParameter",
      "BooleanRefParameter", "BooleanRefParameter",
      "Lcom/gensym/com/BooleanRefParameter;", "null", "(Z)V"
    },
    { JAVA_SHORT_RP, "com/gensym/com/ShortRefParameter",
      "ShortRefParameter", "ShortRefParameter",
      "Lcom/gensym/com/ShortRefParameter;", "null", "(S)V"
    },
    { JAVA_INT_RP, "com/gensym/com/IntRefParameter",
      "IntRefParameter", "IntRefParameter",
      "Lcom/gensym/com/IntRefParameter;", "null", "(I)V"
    },
    { JAVA_FLOAT_RP, "com/gensym/com/FloatRefParameter",
      "FloatRefParameter", "FloatRefParameter",
      "Lcom/gensym/com/FloatRefParameter;", "null", "(F)V"
    },
    { JAVA_DOUBLE_RP, "com/gensym/com/DoubleRefParameter",
      "DoubleRefParameter", "DoubleRefParameter",
      "Lcom/gensym/com/DoubleRefParameter;", "null", "(D)V"
    },
    { JAVA_DATE_RP, "com/gensym/com/DateRefParameter",
      "DateRefParameter", "DateRefParameter",
      "Lcom/gensym/com/DateRefParameter;", "null",
      "(Ljava/util/Date;)V"
    },
    { JAVA_STRING_RP, "com/gensym/com/StringRefParameter",
      "StringRefParameter", "StringRefParameter",
      "Lcom/gensym/com/StringRefParameter;", "null",
      "(Ljava/lang/String;)V"
    },
    { JAVA_VARIANT_RP, "com/gensym/com/VariantRefParameter",
      "VariantRefParameter", "VariantRefParameter",
      "Lcom/gensym/com/VariantRefParameter;", "null",
      "(Lcom/gensym/com/Variant;)V"
    },
    { JAVA_IDISP_RP, "com/gensym/com/ActiveXDispatchableRefParameter",
      "ActiveXDispatchableRefParameter",
      "ActiveXDispatchableRefParameter",
      "Lcom/gensym/com/ActiveXDispatchableRefParameter;", "null",
      "(ILcom/gensym/com/ActiveXProxy;)V"
    },
    { JAVA_UNKNOWN_RP, "java/lang/Object",
      /* not yet implemented */
      "Generic reference parameter",
      "Object", "Ljava/lang/Object;", "null",
    },
    { JAVA_CURRENCY_RP, "java/lang/Object",
      /* not yet implemented */
      "Generic reference parameter", "Object", "Ljava/lang/Object;", "null"
    },
    { JAVA_BYTE_RP, "com/gensym/com/ByteRefParameter",
      "ByteRefParameter", "ByteRefParameter",
      "Lcom/gensym/com/ByteRefParameter;", "null", "(B)V"
    },
    { JAVA_SA_RP, "com/gensym/com/SARefParameter",
      "SARefParameter", "SARefParameter",
      "Lcom/gensym/com/SARefParameter;", "null",
      "(Lcom/gensym/com/SafeArray;)V"
    },
    { JAVA_SHORT_SA_RP, "com/gensym/com/ShortSARefParameter",
      "ShortSARefParameter", "ShortSARefParameter",
      "Lcom/gensym/com/ShortSARefParameter;", "null",
      "(Lcom/gensym/com/ShortSafeArray;)V"
    },
    { JAVA_INT_SA_RP, "com/gensym/com/IntSARefParameter",
      "IntSARefParameter", "IntSARefParameter",
      "Lcom/gensym/com/IntSARefParameter;", "null",
      "(Lcom/gensym/com/IntSafeArray;)V"
    },
    { JAVA_FLOAT_SA_RP, "com/gensym/com/FloatSARefParameter",
      "FloatSARefParameter", "FloatSARefParameter",
      "Lcom/gensym/com/FloatSARefParameter;", "null",
      "(Lcom/gensym/com/FloatSafeArray;)V"
    },
    { JAVA_DOUBLE_SA_RP, "com/gensym/com/DoubleSARefParameter",
      "DoubleSARefParameter", "DoubleSARefParameter",
      "Lcom/gensym/com/DoubleSARefParameter;", "null",
      "(Lcom/gensym/com/DoubleSafeArray;)V"
    },
    { JAVA_DATE_SA_RP, "com/gensym/com/DateSARefParameter",
      "DateSARefParameter", "DateSARefParameter",
      "Lcom/gensym/com/DateSARefParameter;", "null",
      "(Lcom/gensym/com/DateSafeArray;)V"
    },
    { JAVA_STRING_SA_RP, "com/gensym/com/StringSARefParameter",
      "StringSARefParameter", "StringSARefParameter",
      "Lcom/gensym/com/StringSARefParameter;", "null",
      "(Lcom/gensym/com/StringSafeArray;)V"
    },
    { JAVA_BOOLEAN_SA_RP, "com/gensym/com/BooleanSARefParameter",
      "BooleanSARefParameter", "BooleanSARefParameter",
      "Lcom/gensym/com/BooleanSARefParameter;", "null",
      "(Lcom/gensym/com/BooleanSafeArray;)V"
    },
    { JAVA_VARIANT_SA_RP, "com/gensym/com/VariantSARefParameter",
      "VariantSARefParameter", "VariantSARefParameter",
      "Lcom/gensym/com/VariantSARefParameter;", "null",
      "(Lcom/gensym/com/VariantSafeArray;)V"
    },
    { JAVA_BYTE_SA_RP, "com/gensym/com/ByteSARefParameter",
      "ByteSARefParameter", "ByteSARefParameter",
      "Lcom/gensym/com/ByteSARefParameter;", "null",
      "(Lcom/gensym/com/ByteSafeArray;)V"
    },
};

#define NUMBER_OF_JAVA_TYPES (sizeof (jtype_info) / sizeof (JAVA_TYPE_INFO))

static VARTYPE_INFO vtype_info[] = 
{
    { VT_EMPTY, JAVA_VOID, "VT_EMPTY", "nothing",
      default_jvariant_from_unsupported_variant
    }, 
    { VT_NULL, JAVA_VOID, "VT_NULL", "SQL style Null",
      default_jvariant_from_unsupported_variant
    }, 
    { VT_I2, JAVA_SHORT, "VT_I2", "2 byte signed int",
      short_jvariant_from_I2_variant
    },
    { VT_I4, JAVA_INT, "VT_I4", "4 byte signed int",
      int_jvariant_from_I4_variant
    },
    { VT_R4, JAVA_FLOAT, "VT_R4", "4 byte real",
      float_jvariant_from_R4_variant
    },
    { VT_R8, JAVA_DOUBLE, "VT_R8", "8 byte real",
      double_jvariant_from_R8_variant
    },
    { VT_CY, JAVA_OBJECT, "VT_CY", "currency",
      default_jvariant_from_unsupported_variant
    },
    { VT_DATE, JAVA_DATE, "VT_DATE", "date",
      date_jvariant_from_DATE_variant
    },
    { VT_BSTR, JAVA_STRING, "VT_BSTR", "OLE Automation string",
      string_jvariant_from_BSTR_variant
    },
    { VT_DISPATCH, JAVA_IDISP, "VT_DISPATCH", "IDispatch *",
      disp_jvariant_from_DISPATCH_variant
    },
    { VT_ERROR, JAVA_INT, "VT_ERROR", "SCODE",
      default_jvariant_from_unsupported_variant
    },
    { VT_BOOL, JAVA_BOOLEAN, "VT_BOOL", "True=-1, False=0",
      boolean_jvariant_from_BOOL_variant
    },
    { VT_VARIANT, JAVA_VARIANT, "VT_VARIANT", "Variant Parameter"
    },
    { VT_UNKNOWN, JAVA_OBJECT, "VT_UNKNOWN", "IUnknown *",
      default_jvariant_from_unsupported_variant
    },
    { 14, JAVA_OBJECT, "VT_DECIMAL", "not allowed"
    },
    { 15, JAVA_OBJECT, "UNDEFINED_VARTYPE", "not listed"
    },
    { VT_I1, JAVA_BYTE, "VT_I1", "not allowed, change to UI1 in java"
    },
    { VT_UI1, JAVA_BYTE, "VT_UI1", "unsigned char",
      byte_jvariant_from_UI1_variant
    },
    { VT_UI2, JAVA_SHORT, "VT_UI2", "IDispatch.GetTypeInfo parameter type"
    },
    { VT_UI4, JAVA_INT, "VT_UI4", "IUnknown parameter type"
    },
    { 20, JAVA_OBJECT, "VT_I8", "not allowed"
    },
    { 21, JAVA_OBJECT, "VT_UI8", "not allowed"
    },
    { VT_INT, JAVA_INT, "VT_INT", "not allowed, change to I4 in java"
    },
    { VT_UINT, JAVA_INT, "VT_UINT", "IDispatch.GetTypeInfo parameter type"
    },
    { VT_VOID, JAVA_VOID, "VT_VOID", "Return type"
    },
    { VT_HRESULT, JAVA_INT, "VT_HRESULT", "not allowed, change to I4 in java"
    },
    { VT_PTR, JAVA_OBJECT, "VT_PTR", "IUnknown parameter type, not supported"
    },
    { VT_SAFEARRAY, JAVA_VARIANT,
      "SAFEARRAY", "return value: generic safe array in a variant"
    },
    /* This is for methods that have the vararg attribute. This exact type
       cannot be in a variant, so we set the type of the last parameter of
       a vararg type method to VT_ARRAY to signal the emit code to output
       an array of Variants as the last parameter. */
    { VT_ARRAY, JAVA_VARIANT_ARRAY,
      "Variant[]", "vararg"
    },
    /* These are types of arrays that can be in a OLE variant. */
    { VT_ARRAY | VT_I2, JAVA_SHORT_SA,
      "VT_ARRAY | VT_I2", "2 byte signed int array",
      short_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_I4, JAVA_INT_SA,
      "VT_ARRAY | VT_I4", "4 byte signed int array",
      int_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_R4, JAVA_FLOAT_SA,
      "VT_ARRAY | VT_R4", "4 byte real array",
      float_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_R8, JAVA_DOUBLE_SA,
      "VT_ARRAY | VT_R8", "8 byte real array",
      double_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_CY, JAVA_CURRENCY_SA,
      "VT_ARRAY | VT_CY", "currency array",
      default_jvariant_from_unsupported_variant
    },
    { VT_ARRAY | VT_DATE, JAVA_DATE_SA,
      "VT_ARRAY | VT_DATE", "date array",
      date_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_BSTR, JAVA_STRING_SA,
      "VT_ARRAY | VT_BSTR", "OLE Automation string array",
      string_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_DISPATCH, JAVA_IDISP_SA,
      "VT_ARRAY | VT_DISPATCH", "IDispatch * array",
      default_jvariant_from_unsupported_variant
    },
    { VT_ARRAY | VT_ERROR, JAVA_INT_SA,
      "VT_ARRAY | VT_ERROR", "SCODE array",
      int_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_BOOL, JAVA_BOOLEAN_SA,
      "VT_ARRAY | VT_BOOL", "bool array",
      boolean_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_VARIANT, JAVA_VARIANT_SA,
      "VT_ARRAY | VT_VARIANT", "SAFEARRAY of VARIANTS",
      variant_SA_jvariant_from_VARIANT
    },
    { VT_ARRAY | VT_UNKNOWN, JAVA_UNKNOWN_SA,
      "VT_ARRAY | VT_UNKNOWN", "IUnknown * array",
      default_jvariant_from_unsupported_variant
    },
    { VT_ARRAY | VT_UI1, JAVA_BYTE_SA,
      "VT_ARRAY | VT_UI1", "unsigned char array",
      byte_SA_jvariant_from_VARIANT
    },
    /* These are types of references that can be in a OLE variant. */
    { VT_BYREF | VT_I2, JAVA_SHORT_RP,
      "VT_BYREF | VT_I2", "2 byte signed int reference",
      short_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_I4, JAVA_INT_RP,
      "VT_BYREF | VT_I4", "4 byte signed int reference",
      int_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_R4, JAVA_FLOAT_RP,
      "VT_BYREF | VT_R4", "4 byte real reference",
      float_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_R8, JAVA_DOUBLE_RP,
      "VT_BYREF | VT_R8", "8 byte real reference",
      double_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_CY, JAVA_CURRENCY_RP,
      "VT_BYREF | VT_CY", "currency reference",
      default_jvariant_from_unsupported_variant
    },
    { VT_BYREF | VT_DATE, JAVA_DATE_RP,
      "VT_BYREF | VT_DATE", "date reference",
      date_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_BSTR, JAVA_STRING_RP,
      "VT_BYREF | VT_BSTR", "OLE Automation string reference",
      string_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_DISPATCH, JAVA_IDISP_RP,
      "VT_BYREF | VT_DISPATCH", "IDispatch * reference",
      /* dispatchable_RP_jvariant_from_VARIANT */
      default_jvariant_from_unsupported_variant
    },
    { VT_BYREF | VT_ERROR, JAVA_INT_RP,
      "VT_BYREF | VT_ERROR", "SCODE reference",
      int_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_BOOL, JAVA_BOOLEAN_RP,
      "VT_BYREF | VT_BOOL", "bool reference",
      boolean_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_VARIANT, JAVA_VARIANT_RP,
      "VT_BYREF | VT_VARIANT", "VARIANT reference",
      variant_RP_jvariant_from_VARIANT
    },
    { VT_BYREF | VT_UNKNOWN, JAVA_UNKNOWN_RP,
      "VT_BYREF | VT_UNKNOWN", "IUnknown * reference",
      default_jvariant_from_unsupported_variant
    },
    { VT_BYREF | VT_UI1, JAVA_BYTE_RP,
      "VT_BYREF | VT_UI1", "unsigned char reference",
      byte_RP_jvariant_from_VARIANT
    },
    { VT_BYREF| VT_ARRAY | VT_I2, JAVA_SHORT_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_I2",
      "pointer to a pointer to a 2 byte signed int array"
    },
    { VT_BYREF| VT_ARRAY | VT_I4, JAVA_INT_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_I4",
      "pointer to a pointer to a 4 byte signed int array"
    },
    { VT_BYREF| VT_ARRAY | VT_R4, JAVA_FLOAT_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_R4",
      "pointer to a pointer to a 4 byte real number array"
    },
    { VT_BYREF| VT_ARRAY | VT_R8, JAVA_DOUBLE_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_R8",
      "pointer to a pointer to a 8 byte real number array"
    },
    { VT_BYREF| VT_ARRAY | VT_DATE, JAVA_DATE_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_DATE",
      "pointer to a pointer to a DATE array"
    },
    { VT_BYREF| VT_ARRAY | VT_BSTR, JAVA_STRING_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_BSTR",
      "pointer to a pointer to a BSTR array"
    },
    { VT_BYREF| VT_ARRAY | VT_BOOL, JAVA_BOOLEAN_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_BOOL",
      "pointer to a pointer to a boolean array"
    },
    { VT_BYREF| VT_ARRAY | VT_VARIANT, JAVA_VARIANT_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_VARIANT",
      "pointer to a pointer to a variant array"
    },
    { VT_BYREF| VT_ARRAY | VT_UI1, JAVA_BYTE_SA_RP,
      "VT_BYREF | VT_ARRAY | VT_UI1",
      "pointer to a pointer to a unsigned char array"
    },
};

#define MAX_NUMBER_OF_VTYPES (sizeof (vtype_info) / sizeof (VARTYPE_INFO))

static int init_done = FALSE;
static jmethodID variant_default_constructor = (jmethodID) NULL;

static jmethodID date_getTime_method = (jmethodID) NULL;

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
static VARTYPE_INFO *get_vartype_info(unsigned short vartype)
{
  int i;

  for (i = 0; i < MAX_NUMBER_OF_VTYPES; i++) {
    if (vtype_info[i].vtype_verify == vartype)
      return &vtype_info[i];
  }

  return NULL;
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
static int java_type_from_vartype(unsigned short vartype)
{
  VARTYPE_INFO *pVartypeInfo = NULL;

  pVartypeInfo = get_vartype_info(vartype);
  if (pVartypeInfo != NULL)
      return pVartypeInfo->java_type;

  return JAVA_OBJECT;
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
static void init_vartype_api(JNIEnv *env) 
{
  int i;
  char signature[80];
  char name[80];
  jclass temp_class;
  
  if (init_done)
    return;
  
  if (jtype_info[JAVA_VARIANT].java_class == NULL) {
    temp_class = (*env)->FindClass(env,
      jtype_info[JAVA_VARIANT].class_string);
    if (temp_class == NULL) {
      (*env)->ExceptionClear(env);
      jprintf(env, DERROR,
        "System Error: could not obtain class for Variant");
      return;
    }
    
    jtype_info[JAVA_VARIANT].java_class = (*env)->NewGlobalRef(env,
      temp_class);
  }
  
  if (jtype_info[JAVA_VARIANT].java_class == NULL) {
    (*env)->ExceptionClear(env);
    return;
  }
  
  for (i = 0; i < NUMBER_OF_JAVA_TYPES; i++) {
    /* get a variant constructor that takes this class */
    sprintf(signature, "(%s)V", jtype_info[i].jni_string);
    jtype_info[i].variant_constructor = (*env)->GetMethodID(env,
      jtype_info[JAVA_VARIANT].java_class,
      "<init>", signature);
    
    /* there is not a Variant constructor for every type */
    if (jtype_info[i].variant_constructor == NULL) {
      (*env)->ExceptionClear(env);
    }
    
    /* init the Variant get value method ID */
    sprintf(name, "get%sValue", jtype_info[i].cast_string);
    sprintf(signature, "()%s", jtype_info[i].jni_string);
    jtype_info[i].var_get_value_method  =
      (*env)->GetMethodID(env, jtype_info[JAVA_VARIANT].java_class,
      name, signature);
    
    /* there is not a Variant get value method for every type */
    if (jtype_info[i].var_get_value_method == NULL) {
      (*env)->ExceptionClear(env);
    }
    
    /* not every type is a class */
    if (strcmp(jtype_info[i].class_string, "NotAClass") == 0)
      continue;
    
    /* We already got the Variant class */
    if (i != JAVA_VARIANT) {
      /* get a global class pointer */
      temp_class = (*env)->FindClass(env,
        jtype_info[i].class_string);
      if (temp_class == NULL) {
        (*env)->ExceptionClear(env);
        jprintf(env, DERROR, "Error: could not obtain class for %s",
          jtype_info[i].class_string);
        continue;
      }
      
      jtype_info[i].java_class = (*env)->NewGlobalRef(env, temp_class);
      if (jtype_info[i].java_class == NULL) {
        (*env)->ExceptionClear(env);
        continue;
      }
    }
    
    /* Get the constructor we need for this class. */
    if (jtype_info[i].constructor_sig != NULL) {
      jtype_info[i].constructor = (*env)->GetMethodID(env,
        jtype_info[i].java_class, "<init>",
        jtype_info[i].constructor_sig);
      if (jtype_info[i].constructor == NULL) {
        (*env)->ExceptionClear(env);
        continue;
      }
    }
  } /* end of for every java type */
  
  /* The variant constructor used for ActiveXDispatchable we need
  takes an int and an ActiveXProxy, which does not fit the generic case. */
  jtype_info[JAVA_IDISP].variant_constructor = (*env)->GetMethodID(env,
    jtype_info[JAVA_VARIANT].java_class, "<init>",
    "(ILcom/gensym/com/ActiveXProxy;)V");
  if (jtype_info[i].variant_constructor == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not variant constructor for ActiveXDispatchable");
  }
  
  if (variant_default_constructor == NULL) {
    variant_default_constructor = (*env)->GetMethodID(env,
      jtype_info[JAVA_VARIANT].java_class, "<init>", "()V");
  }
  
  if (jtype_info[JAVA_DATE].java_class != NULL) {
    date_getTime_method =
      (*env)->GetMethodID(env, jtype_info[JAVA_DATE].java_class,
      "getTime", "()J");
    if (date_getTime_method == NULL) {
      (*env)->ExceptionClear(env);
      jprintf(env, DERROR,
        "Error: could not obtain method id for getTime");
      return;
    }
  }
  
  init_done = TRUE;
}

/*****************************************************************************
* jni_string_for_java_type
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
char *jni_string_for_java_type (JNIEnv *env, unsigned short vtype)
{
  char *answer = NULL;
  
  answer = jtype_info[java_type_from_vartype(vtype)].jni_string;
  if (answer) {
    return answer;
  }

  jprintf(env, DERROR, "Error: could not get vartype for %d", vtype);
  return "Ljava/lang/Object;";
}

/*****************************************************************************
* vartype_string_for_java_type
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
char *vartype_string_for_java_type (JNIEnv *env, unsigned short vtype)
{
  char *answer = NULL;
  char *temp = NULL;

  answer = jtype_info[java_type_from_vartype(vtype)].java_type_string;
  if (answer) {
    return answer;
  }

  jprintf(env, DERROR, "Error: could not get vartype for %d", vtype);
  return "Object";
}


/*****************************************************************************
* vartype_string_for_java_get_method
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
char *vartype_string_for_java_get_method (JNIEnv *env, unsigned short vtype)
{
  char *answer = NULL;
  
  answer = jtype_info[java_type_from_vartype(vtype)].cast_string;
  if (answer) {
    return answer;
  }

  jprintf(env, DERROR, "Error: could not get vartype for cast for %d", vtype);
  return "Object";
}

/*****************************************************************************
* default_value_string_for_java_type
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
char *default_value_string_for_java_type (JNIEnv *env, unsigned short vtype)
{
  char *answer = NULL;
  
  answer = jtype_info[java_type_from_vartype(vtype)].default_value_string;
  if (answer) {
    return answer;
  }

  jprintf(env, DERROR, "Error: could not get vartype for %d", vtype);
  return "null";
}


/*****************************************************************************
* name_of_vartype
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     This function is really intended for development-only.
*     The string returned better not be reclaimed.
*     -----
*   Modifications:
*****************************************************************************/
static char *name_of_vartype (unsigned short vtype)
{
  VARTYPE_INFO *pVartypeInfo = NULL;

  pVartypeInfo = get_vartype_info(vtype);
  if (pVartypeInfo != NULL)
    return pVartypeInfo->name_for_type;

  return "can't find type";
}

/*****************************************************************************
* name_of_java_type
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     This function is really intended for development-only.
*     The string returned better not be reclaimed.
*     -----
*   Modifications:
*****************************************************************************/
static char *name_of_java_type (unsigned short jtype)
{
  if (jtype >= NUMBER_OF_JAVA_TYPES) {
    dprintf(DERROR, "Error: could not get java type for %d", jtype);
    return NAME_FOR_NONEXISTENT_JAVA_TYPE;
  }
  
  return jtype_info[jtype].cast_string;
}

static jobject CreateShortRefParameter(JNIEnv *env, int value) {
  return (*env)->NewObject(env, jtype_info[JAVA_SHORT_RP].java_class,
    jtype_info[JAVA_SHORT_RP].constructor, value);
}

static jobject CreateIntRefParameter(JNIEnv *env, long value) {
  return (*env)->NewObject(env, jtype_info[JAVA_INT_RP].java_class,
    jtype_info[JAVA_INT_RP].constructor, value);
}

static jobject CreateFloatRefParameter(JNIEnv *env, float value) {
  return (*env)->NewObject(env, jtype_info[JAVA_FLOAT_RP].java_class,
    jtype_info[JAVA_FLOAT_RP].constructor, value);
}

static jobject CreateDoubleRefParameter(JNIEnv *env, double value) {
  return (*env)->NewObject(env, jtype_info[JAVA_DOUBLE_RP].java_class,
    jtype_info[JAVA_DOUBLE_RP].constructor, value);
}

static jobject CreateDateRefParameter(JNIEnv *env, DATE value) {
  jobject pJdate = NULL;

  pJdate = jdate_from_DATE(env, value);
  return (*env)->NewObject(env, jtype_info[JAVA_DATE_RP].java_class,
    jtype_info[JAVA_DATE_RP].constructor, pJdate);
}

static jobject CreateStringRefParameter(JNIEnv *env, BSTR value) {
  jstring pstring = NULL;

  pstring = BSTR_to_jstring(env, value);
  return (*env)->NewObject(env, jtype_info[JAVA_STRING_RP].java_class,
    jtype_info[JAVA_STRING_RP].constructor, value);
}

static jobject CreateBooleanRefParameter(JNIEnv *env, VARIANT_BOOL value) {
  return (*env)->NewObject(env, jtype_info[JAVA_BOOLEAN_RP].java_class,
    jtype_info[JAVA_BOOLEAN_RP].constructor, value);
}

static jobject CreateVariantRefParameter(JNIEnv *env, VARIANT value, jobject proxy,
                                         int isEvent) {
  jobject pJvariant = NULL;

  pJvariant = make_jobject_from_variant (env, value, proxy, isEvent);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT_RP].java_class,
    jtype_info[JAVA_VARIANT_RP].constructor, pJvariant);
}

static jobject CreateByteRefParameter(JNIEnv *env, BYTE value) {
  return (*env)->NewObject(env, jtype_info[JAVA_BYTE_RP].java_class,
    jtype_info[JAVA_BYTE_RP].constructor, value);
}

/*****************************************************************************
* default_jvariant_from_unsupported_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject default_jvariant_from_unsupported_variant(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_VOID].variant_constructor;
  jprintf(env, DETAIL, "unsupported type = %d", var_source.vt);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor);
}

/*****************************************************************************
* short_jvariant_from_I2_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject short_jvariant_from_I2_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_SHORT].variant_constructor;
  jprintf(env, DETAIL, "value_result = %d", var_source.iVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, var_source.iVal);
}

/*****************************************************************************
* int_jvariant_from_I4_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject int_jvariant_from_I4_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_INT].variant_constructor;
  jprintf(env, DETAIL, "value_result = %d", var_source.lVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, var_source.lVal);
}

/*****************************************************************************
* float_jvariant_from_R4_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject float_jvariant_from_R4_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_FLOAT].variant_constructor;
  jprintf(env, DETAIL, "value_result = %f", (double)var_source.fltVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, var_source.fltVal);
}

/*****************************************************************************
* double_jvariant_from_R8_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject double_jvariant_from_R8_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_DOUBLE].variant_constructor;
  jprintf(env, DETAIL, "value_result = %f", var_source.dblVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, var_source.dblVal);
}

/*****************************************************************************
* date_value
*
*   Description: Takes as input an ActiveX date and produces as output
*     a Java time. An ActiveX date is the number of days since Dec 30, 1899.
*     A Java time is the number of milliseconds since Jan 1, 1970.
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jlong date_value (JNIEnv *env, double days_since_1899)
{
  double days_since_1970;
  double ms_since_1970;
  jlong jlong_result;
  
  days_since_1970 = days_since_1899 -
    (double)NUMBER_OF_DAYS_BETWEEN_DEC30_1899_AND_JAN_1_1970;
  ms_since_1970 = days_since_1970 *
    (double)NUMBER_OF_MILLISECONDS_IN_ONE_DAY;
  jlong_result = (jlong)ms_since_1970;
  
  jprintf(env, DUMP, "days since 1899 = %f; days since 1970 = %f",
    days_since_1899, days_since_1970);
  jprintf(env, DUMP, "ms_since_1970 = %f as a jlong: %I64i",
    ms_since_1970, jlong_result);
  
  return jlong_result;
}

/*****************************************************************************
* jdate_from_DATE
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
jobject jdate_from_DATE(JNIEnv *env, DATE date)
{
  init_vartype_api(env);

  if (jtype_info[JAVA_DATE].java_class == NULL) {
    jprintf(env, ERROR, "The date class was not found, can't convert DATE");
    return NULL;
  }

  return (*env)->NewObject(env, jtype_info[JAVA_DATE].java_class,
    jtype_info[JAVA_DATE].constructor, date_value(env, date));
}

/*****************************************************************************
* date_jvariant_from_DATE_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject date_jvariant_from_DATE_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;
  jobject temp_date = NULL;

  temp_date = jdate_from_DATE(env, var_source.date);
  if (temp_date == NULL)
    return NULL;

  constructor = jtype_info[JAVA_DATE].variant_constructor;
  jprintf(env, DETAIL, "value_result = %f", (double)var_source.date);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, temp_date);
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
static DATE DATE_from_jmilliseconds(JNIEnv *env, jlong milliseconds_since_1970) {
  return (DATE)milliseconds_since_1970 /
    (DATE)NUMBER_OF_MILLISECONDS_IN_ONE_DAY +
    (DATE)NUMBER_OF_DAYS_BETWEEN_DEC30_1899_AND_JAN_1_1970;
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
DATE DATE_from_jdate(JNIEnv *env, jobject pdate)
{
  jlong milliseconds_since_1970 = 0;
  
  init_vartype_api(env);

  milliseconds_since_1970 = (*env)->CallLongMethod(env, pdate,
                              date_getTime_method);
  return DATE_from_jmilliseconds(env, milliseconds_since_1970);
}

/*****************************************************************************
* create_jdate_array
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
jobjectArray create_jdate_array(JNIEnv *env, int size)
{
  init_vartype_api(env);
  return (*env)->NewObjectArray(env, (jsize)size,
    jtype_info[JAVA_DATE].java_class, NULL);
}

/*****************************************************************************
* create_jstring_array
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
jobjectArray create_jstring_array(JNIEnv *env, int size)
{
  init_vartype_api(env);
  return (*env)->NewObjectArray(env, (jsize)size,
    jtype_info[JAVA_STRING].java_class, NULL);
}

/*****************************************************************************
* create_jvariant_array
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
jobjectArray create_jvariant_array(JNIEnv *env, int size)
{
  init_vartype_api(env);
  return (*env)->NewObjectArray(env, (jsize)size,
    jtype_info[JAVA_VARIANT].java_class, NULL);
}

/*****************************************************************************
* string_jvariant_from_BSTR_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject string_jvariant_from_BSTR_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_STRING].variant_constructor;
  jprintf(env, DETAIL, "value_result = %ws", var_source.bstrVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, BSTR_to_jstring(env, var_source.bstrVal));
}

/*****************************************************************************
* disp_jvariant_from_DISPATCH_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject disp_jvariant_from_DISPATCH_variant(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jmethodID constructor;

  /* oleObject will be null when we create safe array of variants or when
     we are forwarding an event parameter arrays that have dispatch pointers
     in them. */
  if (oleObject == NULL)
    return NULL;

  constructor = jtype_info[JAVA_IDISP].variant_constructor;

  if (var_source.pdispVal != NULL) {
    jprintf(env, DETAIL, "value_result = %d", (jint) (var_source.pdispVal));
    jprintf(env, DETAIL, "VTABLE = %x\n\n",
      (jint) (var_source.pdispVal->lpVtbl));
    jprintf(env, DETAIL, "oleObject = %d", (jint) (oleObject));

    /* Only during an event do we need to add a reference here, because of the
       rule of passing out interface pointers in COM. The ActiveX method passing
       out or returning an interface pointer should have added a reference. */
    if (isEvent)
      var_source.pdispVal->lpVtbl->AddRef(var_source.pdispVal);

    return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
      constructor, var_source.pdispVal, oleObject);
  }

  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, 0, oleObject); 
}

/*****************************************************************************
* boolean_jvariant_from_BOOL_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject boolean_jvariant_from_BOOL_variant(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_BOOLEAN].variant_constructor;
  jprintf(env, DETAIL, "value_result = %d", var_source.boolVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, (var_source.boolVal == VARIANT_TRUE ? JNI_TRUE : JNI_FALSE));
}

/*****************************************************************************
* byte_jvariant_from_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject byte_jvariant_from_UI1_variant(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jmethodID constructor;

  constructor = jtype_info[JAVA_BYTE].variant_constructor;
  jprintf(env, DETAIL, "value_result = %d", var_source.bVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, var_source.bVal);
}

/*****************************************************************************
* short_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject short_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_SHORT_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateShortSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* int_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject int_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_INT_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateIntSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* float_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject float_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_FLOAT_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateFloatSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* double_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject double_SA_jvariant_from_VARIANT(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_DOUBLE_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateDoubleSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* date_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject date_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_DATE_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateDateSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* string_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject string_SA_jvariant_from_VARIANT(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_STRING_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateStringSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* boolean_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject boolean_SA_jvariant_from_VARIANT(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_BOOLEAN_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateBooleanSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* variant_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject variant_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_VARIANT_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateVariantSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* byte_SA_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject byte_SA_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jSafeArray = NULL;
  jmethodID constructor;
  SAFEARRAY *pSA = NULL;

  constructor = jtype_info[JAVA_BYTE_SA].variant_constructor;

  /* We do not own the safe array during an event. */
  /* Currently during an event we do not wait for results of the Java
     listener method. So we must make a copy. When we change the
     code to wait for the listener to complete, we can just create
     an SafeArray Java wrapper that does not own the native array. */
  if (isEvent)
    SafeArrayCopy(var_source.parray, &pSA);
  else
    pSA = var_source.parray;

  jSafeArray = CreateByteSafeArray(env, pSA, TRUE);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jSafeArray);
}

/*****************************************************************************
* short_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject short_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_SHORT_RP].variant_constructor;

  jRefParameter = CreateShortRefParameter(env, *var_source.piVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* int_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject int_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_INT_RP].variant_constructor;

  jRefParameter = CreateIntRefParameter(env, *var_source.plVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* float_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject float_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_FLOAT_RP].variant_constructor;

  jRefParameter = CreateFloatRefParameter(env, *var_source.pfltVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* double_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject double_RP_jvariant_from_VARIANT(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_DOUBLE_RP].variant_constructor;

  jRefParameter = CreateDoubleRefParameter(env, *var_source.pdblVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* date_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject date_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_DATE_RP].variant_constructor;

  jRefParameter = CreateDateRefParameter(env, *var_source.pdate);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* string_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject string_RP_jvariant_from_VARIANT(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_STRING_RP].variant_constructor;

  jRefParameter = CreateStringRefParameter(env, *var_source.pbstrVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* boolean_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject boolean_RP_jvariant_from_VARIANT(JNIEnv *env,
  VARIANT var_source, jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_BOOLEAN_RP].variant_constructor;

  jRefParameter = CreateBooleanRefParameter(env, *var_source.pboolVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* variant_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject variant_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_VARIANT_RP].variant_constructor;

  jRefParameter = CreateVariantRefParameter(env, *var_source.pvarVal,
                    oleObject, isEvent);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* byte_RP_jvariant_from_VARIANT
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
static jobject byte_RP_jvariant_from_VARIANT(JNIEnv *env, VARIANT var_source,
                               jobject oleObject, int isEvent)
{
  jobject jRefParameter = NULL;
  jmethodID constructor;

  constructor = jtype_info[JAVA_BYTE_RP].variant_constructor;

  jRefParameter = CreateByteRefParameter(env, *var_source.pbVal);
  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
    constructor, jRefParameter);
}

/*****************************************************************************
* make_jobject_from_variant
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
jobject make_jobject_from_variant (JNIEnv *env, VARIANT var_source, 
                                   jobject oleObject, int isEvent)
{
  jobject result = NULL;
  jmethodID constructor = NULL;
  int i = 0;
    
  init_vartype_api(env);

  if (var_source.vt == VT_EMPTY) {
    jprintf(env, DETAIL, "void result");
    result = (*env)->NewObject(env,
      jtype_info[JAVA_VARIANT].java_class,
      variant_default_constructor);
    return result;
  }

  /* find the java Variant constructor based on the vartype */
  for (i = 0; i < MAX_NUMBER_OF_VTYPES; i++) {
    if (vtype_info[i].vtype_verify == var_source.vt) {
      if (vtype_info[i].jvar_from_var != NULL) {
        result = vtype_info[i].jvar_from_var(env, var_source, oleObject, isEvent);
      }

      break;
    }
  }
  
  if (result != NULL)
    return result;

  jprintf(env, DERROR, "unrecognized vartype: %d", var_source.vt);
  jprintf(env,DETAIL,
    "unrecognized vartype: %s", name_of_vartype(var_source.vt));

  return (*env)->NewObject(env, jtype_info[JAVA_VARIANT].java_class,
           variant_default_constructor);
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
static short get_short_value(JNIEnv *env, jobject newValue)
{
  if (jtype_info[JAVA_SHORT].var_get_value_method == NULL) {
    jprintf(env, DERROR,
      "Error: could not obtain method id for getShortValue");
    return -1;
  }

  return (short)(*env)->CallShortMethod(env, newValue,
    jtype_info[JAVA_SHORT].var_get_value_method);
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
static long get_int_value(JNIEnv *env, jobject newValue)
{
  if (jtype_info[JAVA_INT].var_get_value_method == NULL) {
    jprintf(env, DERROR, "Error: could not obtain method id for getIntValue");
    return -1;
  }

  return (long)(*env)->CallIntMethod(env, newValue,
    jtype_info[JAVA_INT].var_get_value_method);
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
static float get_float_value(JNIEnv *env, jobject newValue)
{
  if (jtype_info[JAVA_FLOAT].var_get_value_method == NULL) {
    jprintf(env, DERROR,
      "Error: could not obtain method id for getFloatValue");
    return (float) 0.0;
  }

  return (float)(*env)->CallFloatMethod(env, newValue,
    jtype_info[JAVA_FLOAT].var_get_value_method);
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
static double get_double_value(JNIEnv *env, jobject newValue)
{
  if (jtype_info[JAVA_DOUBLE].var_get_value_method == NULL) {
    jprintf(env, DERROR,
      "Error: could not obtain method id for getFloatValue");
    return (double) 0.0;
  }

  return (double)(*env)->CallDoubleMethod(env, newValue,
    jtype_info[JAVA_DOUBLE].var_get_value_method);
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
static DATE get_date_value(JNIEnv *env, jobject newValue)
{
  static jmethodID mid = NULL;
  jlong milliseconds_since_1970 = 0;
  
  if (mid == NULL) {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_VARIANT].java_class,
      "getDateSecondsValue", "()J");
  }
  
  if (mid == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not obtain method id for getDateSecondsValue");
    return (DATE)-1;
  }

  milliseconds_since_1970 = (*env)->CallLongMethod(env, newValue, mid);
  return DATE_from_jmilliseconds(env, milliseconds_since_1970);
}


/*****************************************************************************
* 
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*    SysAllocString
*     -----
*   Modifications:
*****************************************************************************/
static BSTR get_string_value(JNIEnv *env, jobject newValue)
{
  jstring java_string;

  if (jtype_info[JAVA_STRING].var_get_value_method == NULL) {
    jprintf(env, DERROR,
      "Error: could not obtain method id for getStringValue");
    return SysAllocString(L"");
  }
  
  java_string = (*env)->CallObjectMethod(env, newValue,
    jtype_info[JAVA_STRING].var_get_value_method);
  return java_to_BSTR(env, java_string);
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
static IDispatch* get_dispatch_pointer_value(JNIEnv *env, jobject newValue,
    jobject proxy)
{
  jmethodID mid = NULL;

  if (proxy == NULL)
  {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_VARIANT].java_class,
            "getDispatchPointer", "()I");
    if (mid == NULL) {
      (*env)->ExceptionClear(env);
      jprintf(env, DERROR,
        "Error: could not obtain method id for getDispatchPointer");
      return 0;
    }
  }
  else
  {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_VARIANT].java_class,
            "getDispatchPointer", "(Lcom/gensym/com/ActiveXProxy;)I");
    if (mid == NULL) {
      (*env)->ExceptionClear(env);
      jprintf(env, DERROR,
        "Error: could not obtain method id for getDispatchPointer");
      return 0;
    }
  }
  
  return (IDispatch*)(*env)->CallIntMethod(env, newValue, mid, proxy);
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
static VARIANT_BOOL get_boolean_value(JNIEnv *env, jobject newValue)
{
  if (jtype_info[JAVA_BOOLEAN].var_get_value_method == NULL) {
    jprintf(env, DERROR,
      "Error: could not obtain method id for getBooleanValue");
    return VARIANT_FALSE;
  }

  /* Make sure we return variant true (-1),
     so that bitwise not of true = false. */
  if ((*env)->CallBooleanMethod(env, newValue,
    jtype_info[JAVA_BOOLEAN].var_get_value_method)) {
    return VARIANT_TRUE;
  }
  
  return VARIANT_FALSE;
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
static BYTE get_byte_value(JNIEnv *env, jobject newValue)
{
  if (jtype_info[JAVA_BYTE].var_get_value_method == NULL) {
    jprintf(env, DERROR,
      "Error: could not obtain method id for getByteValue");
    return 0;
  }

  return (BYTE)((*env)->CallByteMethod(env, newValue,
    jtype_info[JAVA_BYTE].var_get_value_method));
}

/*****************************************************************************
* 
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*    SysAllocString
*     -----
*   Modifications:
*****************************************************************************/
static SAFEARRAY* get_SA_value(JNIEnv *env, jobject newValue, int isEvent)
{
  static jmethodID mid = NULL;
  
  if (mid == NULL) {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_VARIANT].java_class,
          "getSafeArrayValue", "()Lcom/gensym/com/SafeArray;");
  }
  
  if (mid == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env, DERROR,
      "Error: could not obtain method id for getSafeArray");
    return NULL;
  }
  
  /* If we are converting a Java safe array as a return value from
     an event, we want to give up ownership. */
  return NativeSAFromJavaSA(env,
    (*env)->CallObjectMethod(env, newValue, mid), isEvent);
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
static short get_short_ref_value(JNIEnv *env, jobject newValue,
   jobject *ppJavaRef)
{
  if (jtype_info[JAVA_SHORT_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getShortRefParameter");
    return -1;
  }

  if (jtype_info[JAVA_SHORT_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_SHORT_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_SHORT_RP].java_class, "getShort", "()S");
  }
  
  if (jtype_info[JAVA_SHORT_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getShort");
    return -1;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_SHORT_RP].var_get_value_method);
  
  return (short)(*env)->CallShortMethod(env, *ppJavaRef,
                     jtype_info[JAVA_SHORT_RP].ref_get_value_method);
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
static long get_int_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  if (jtype_info[JAVA_INT_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getIntRefParameter");
    return -1;
  }

  if (jtype_info[JAVA_INT_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_INT_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_INT_RP].java_class, "getInt", "()I");
  }
  
  if (jtype_info[JAVA_INT_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getInt");
    return -1;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_INT_RP].var_get_value_method);

  return (long)(*env)->CallIntMethod(env, *ppJavaRef,
                    jtype_info[JAVA_INT_RP].ref_get_value_method);
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
static float get_float_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  if (jtype_info[JAVA_FLOAT_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getFloatRefParameter");
    return -1.0;
  }

  if (jtype_info[JAVA_FLOAT_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_FLOAT_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_FLOAT_RP].java_class, "getFloat", "()F");
  }
  
  if (jtype_info[JAVA_FLOAT_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getFloat");
    return -1.0;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_FLOAT_RP].var_get_value_method);

  return (float)(*env)->CallFloatMethod(env, *ppJavaRef,
                      jtype_info[JAVA_FLOAT_RP].ref_get_value_method);
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
static double get_double_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  if (jtype_info[JAVA_DOUBLE_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getDoubleRefParameter");
    return -1.0;
  }

  if (jtype_info[JAVA_DOUBLE_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_DOUBLE_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_DOUBLE_RP].java_class, "getDouble", "()D");
  }
  
  if (jtype_info[JAVA_DOUBLE_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getDouble");
    return -1.0;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_DOUBLE_RP].var_get_value_method);

  return (double)(*env)->CallDoubleMethod(env, *ppJavaRef,
                      jtype_info[JAVA_DOUBLE_RP].ref_get_value_method);
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
static DATE get_date_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  jlong milliseconds_since_1970 = 0;

  if (jtype_info[JAVA_DATE_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getDateRefParameter");
    return 0.0;
  }

  if (jtype_info[JAVA_DATE_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_DATE_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_DATE_RP].java_class, "getDateSecondsValue", "()J");
  }
  
  if (jtype_info[JAVA_DATE_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for "
      "getDateSecondsValue");
    return 0.0;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_DATE_RP].var_get_value_method);

  milliseconds_since_1970 = (*env)->CallLongMethod(env, *ppJavaRef,
    jtype_info[JAVA_DATE_RP].ref_get_value_method);
  return DATE_from_jmilliseconds(env, milliseconds_since_1970);
}

/*****************************************************************************
* 
*
*   Description: 
*   Input Arguments:
*   Returns:
*   Notes:
*    SysAllocString
*     -----
*   Modifications:
*****************************************************************************/
static BSTR get_string_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  static jmethodID mid = NULL;
  jstring java_string;

  if (jtype_info[JAVA_STRING_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getStringRefParameter");
    return NULL;
  }

  if (jtype_info[JAVA_STRING_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_STRING_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_STRING_RP].java_class, "getString",
      "()Ljava/lang/String;");
  }
  
  if (jtype_info[JAVA_STRING_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getString");
    return NULL;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_STRING_RP].var_get_value_method);

  java_string = (*env)->CallObjectMethod(env, *ppJavaRef,
                 jtype_info[JAVA_STRING_RP].ref_get_value_method);
  return java_to_BSTR(env, java_string);
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
static IDispatch* get_dispatch_pointer_ref_value(JNIEnv *env, jobject newValue,
    jobject proxy, jobject *ppJavaRef)
{
  jmethodID mid = NULL;

  if (jtype_info[JAVA_IDISP_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for "
      "getActiveXDispatchableRefParameter");
    return NULL;
  }

  if (proxy == NULL)
  {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_IDISP_RP].java_class,
            "getDispatchPointer", "()I");
    if (mid == NULL) {
      jprintf(env, DERROR,
        "Error: could not obtain method id for getDispatchPointer");
      return NULL;
    }
  }
  else
  {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_IDISP_RP].java_class,
            "getDispatchPointer", "(Lcom/gensym/com/ActiveXProxy;)I");
    if (mid == NULL) {
      jprintf(env, DERROR,
        "Error: could not obtain method id for getDispatchPointer");
      return NULL;
    }
  }
  
  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_IDISP_RP].var_get_value_method);

  return (IDispatch*)(*env)->CallIntMethod(env, *ppJavaRef, mid, proxy);
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
static VARIANT_BOOL get_boolean_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  static jmethodID mid = NULL;

  if (jtype_info[JAVA_BOOLEAN_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getBooleanRefParameter");
    return VARIANT_FALSE;
  }

  if (jtype_info[JAVA_BOOLEAN_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_BOOLEAN_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_BOOLEAN_RP].java_class, "getBoolean", "()Z");
  }
  
  if (jtype_info[JAVA_BOOLEAN_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getBoolean");
    return VARIANT_FALSE;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_BOOLEAN_RP].var_get_value_method);

  /* Make sure we return variant true (-1),
     so that bitwise not of true = false. */
  if ((*env)->CallBooleanMethod(env, *ppJavaRef,
      jtype_info[JAVA_BOOLEAN_RP].ref_get_value_method)) {
    return VARIANT_TRUE;
  }
  
  return VARIANT_FALSE;
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
static VARIANT get_variant_ref_value(JNIEnv *env, jobject newValue,
    jobject proxy, jobject *ppJavaRef, int isEvent)
{
  jobject pJavaVariant;
  VARIANT tempVar;

  VariantInit(&tempVar);

  if (jtype_info[JAVA_VARIANT_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getVariantRefParameter");
    return tempVar;
  }

  if (jtype_info[JAVA_VARIANT_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_VARIANT_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_VARIANT_RP].java_class, "getVariant",
      "()Lcom/gensym/com/Variant;");
  }
  
  if (jtype_info[JAVA_VARIANT_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getVariant");
    return tempVar;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_VARIANT_RP].var_get_value_method);

  pJavaVariant = (*env)->CallObjectMethod(env, *ppJavaRef,
                  jtype_info[JAVA_VARIANT_RP].ref_get_value_method);
  init_variant_from_jobject(env, pJavaVariant, &tempVar, proxy, isEvent);
  return tempVar;
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
static BYTE get_byte_ref_value(JNIEnv *env, jobject newValue,
  jobject *ppJavaRef)
{
  if (jtype_info[JAVA_BYTE_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getByteRefParameter");
    return 0;
  }

  if (jtype_info[JAVA_BYTE_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_BYTE_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_BYTE_RP].java_class, "getByte", "()B");
  }
  
  if (jtype_info[JAVA_BYTE_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getByte");
    return 0;
  }

  *ppJavaRef = (*env)->CallObjectMethod(env, newValue,
              jtype_info[JAVA_BYTE_RP].var_get_value_method);

  return (BYTE)(*env)->CallByteMethod(env, *ppJavaRef,
                      jtype_info[JAVA_BYTE_RP].ref_get_value_method);
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
static SAFEARRAY* get_SA_ref_value(JNIEnv *env, jobject newValue,
                                   jobject *ppJavaRef, int isEvent)
{
  jobject java_SA;

  if (jtype_info[JAVA_SA_RP].var_get_value_method == NULL) {
    jprintf(env,DERROR,
      "Error: could not obtain method id for getSARefParameter");
    return NULL;
  }

  if (jtype_info[JAVA_SA_RP].ref_get_value_method == NULL) {
    jtype_info[JAVA_SA_RP].ref_get_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_SA_RP].java_class, "getSafeArray",
      "()Lcom/gensym/com/SafeArray;");
  }
  
  if (jtype_info[JAVA_SA_RP].ref_get_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for getSafeArray");
    return NULL;
  }


  *ppJavaRef = (*env)->CallObjectMethod(env, newValue, 
              jtype_info[JAVA_SA_RP].var_get_value_method);

  java_SA = (*env)->CallObjectMethod(env, *ppJavaRef,
                 jtype_info[JAVA_SA_RP].ref_get_value_method);

  /* If we are converting a Java safe array as a return value from
     an event, we want to give up ownership. */
  return NativeSAFromJavaSA(env, java_SA, isEvent);
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
static short get_vartype(JNIEnv *env, jobject newValue)
{
  static jmethodID mid = NULL;
  
  if (mid == NULL) {
    mid = (*env)->GetMethodID(env, jtype_info[JAVA_VARIANT].java_class,
      "getVartype", "()S");
  }
  
  if (mid == NULL) {
    jprintf(env, DERROR, "Error: could not obtain method id for getVartype");
    return VT_EMPTY;
  }

  return (short)(*env)->CallShortMethod(env, newValue, mid);
}

/*****************************************************************************
* make_variant_from_jobject
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
VARIANTARG *make_variant_from_jobject(JNIEnv *env, jobject object, int isEvent) 
{
  VARIANTARG *pvarg = NULL;
  
  if (env == NULL) {
    jprintf(env, DERROR, "Error: could not call Java method because I don't have a ");
    jprintf(env, DERROR, "pointer to the VM.");
    return NULL;
  }
  
  pvarg = (VARIANTARG*) malloc(sizeof(VARIANTARG));
  if (pvarg == NULL) {
    jprintf(env, DETAIL, "Warning: could not allocate variantarg");
    return NULL;
  }

  init_variant_from_jobject(env, object, (VARIANT*)pvarg, NULL, isEvent);
  if (pvarg->vt == VT_EMPTY)
  {
    free(pvarg);
    return NULL;
  }

  return pvarg;
}  

/*****************************************************************************
* init_variant_from_jobject
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
void init_variant_from_jobject(JNIEnv *env, jobject object, VARIANT* pVariant,
                               jobject proxy, int isEvent) 
{
  jshort vartype;
  TEMP_REF *pTempRef = NULL;
  
  init_vartype_api(env);

  VariantInit(pVariant);

  vartype = get_vartype(env, object);
  jprintf(env, DETAIL, "Base vartype = %d", vartype & (jshort)0x00FF);

  if (vartype & VT_BYREF) {
    jprintf(env, DETAIL, "Variant is a reference to the base type");
    pTempRef = calloc(1, sizeof (TEMP_REF));
    if (pTempRef == NULL) {
      jprintf(env, DERROR, "Can't alloc temp ref out of memory.");
      return;
    }

    pTempRef->inVartype = vartype;
    pVariant->byref = pTempRef;
  }

  pVariant->vt = vartype;

  if (vartype & VT_ARRAY) {
    jprintf(env, DETAIL, "Variant is a safe array of the base type");

    if (vartype & VT_BYREF) {
      *pVariant->pparray = get_SA_ref_value(env, object,
                           &pTempRef->pJavaRefParameter, isEvent);

      /* Lock the array in case the control tries to destroy it.
         We will unlock on the way back. */
      if (*pVariant->pparray != NULL) {
        SafeArrayLock(*pVariant->pparray);
        pTempRef->arrayLocked = TRUE;
      }

      return;
    } else {
       pVariant->parray = get_SA_value(env, object, isEvent);
       if (pVariant->parray == NULL)
           pVariant->vt = VT_NULL;

      return;
    }
  }

  switch (vartype) {
  case VT_I2:
    pVariant->iVal = get_short_value(env, object);
    break;
    
  case VT_I4:
    pVariant->lVal = get_int_value(env, object);
    break;
    
  case VT_R4:
    pVariant->fltVal = get_float_value(env, object);
    break;
    
  case VT_R8:
    pVariant->dblVal = get_double_value(env, object);
    break;
    
  case VT_DATE: 
    pVariant->date = get_date_value(env, object);
    break;
    
  case VT_BSTR:
    pVariant->bstrVal = get_string_value(env, object);
    break;

  case VT_DISPATCH:
    pVariant->pdispVal = get_dispatch_pointer_value(env, object, proxy);
    break;

  case VT_ERROR:
    pVariant->scode = get_int_value(env, object);
    break;
    
  case VT_BOOL: 
    pVariant->boolVal = get_boolean_value(env, object);
    break;
    
  case VT_UI1:
    pVariant->bVal = get_byte_value(env, object);
    break;
    
  case VT_I2 | VT_BYREF:
    *pVariant->piVal = get_short_ref_value(env, object,
                        &pTempRef->pJavaRefParameter);
    break;
    
  case VT_I4 | VT_BYREF:
    *pVariant->plVal = get_int_ref_value(env, object,
                        &pTempRef->pJavaRefParameter);
    break;
    
  case VT_R4 | VT_BYREF:
    *pVariant->pfltVal = get_float_ref_value(env, object,
                          &pTempRef->pJavaRefParameter);
    break;
    
  case VT_R8 | VT_BYREF:
    *pVariant->pdblVal = get_double_ref_value(env, object,
                          &pTempRef->pJavaRefParameter);
    break;
    
  case VT_DATE | VT_BYREF: 
    *pVariant->pdate = get_date_ref_value(env, object,
                        &pTempRef->pJavaRefParameter);
    break;
    
  case VT_BSTR | VT_BYREF:
    *pVariant->pbstrVal = get_string_ref_value(env, object,
                           &pTempRef->pJavaRefParameter);
    break;

  case VT_DISPATCH | VT_BYREF:
    *pVariant->ppdispVal = get_dispatch_pointer_ref_value(env, object, proxy,
                            &pTempRef->pJavaRefParameter);
    break;

  case VT_BOOL | VT_BYREF: 
    *pVariant->pboolVal = get_boolean_ref_value(env, object,
                           &pTempRef->pJavaRefParameter);
    break;
    
  case VT_VARIANT | VT_BYREF: 
    *pVariant->pvarVal = get_variant_ref_value(env, object, proxy,
                          &pTempRef->pJavaRefParameter, isEvent);

    /* We do not want the array destroyed if the control call Variant Clear on
       our variant. We will unlock the array on the way out. */
    if (pVariant->pvarVal->vt & VT_ARRAY) {
      SafeArrayLock(pVariant->pvarVal->parray);
      pTempRef->arrayLocked = TRUE;
      pTempRef->arrayInVariantRef = TRUE;
    }

    break;
    
  case VT_UI1 | VT_BYREF:
    *pVariant->pbVal = get_byte_ref_value(env, object,
                        &pTempRef->pJavaRefParameter);
    break;
    
  default: 
    pVariant->vt = VT_EMPTY;

    jprintf(env, DERROR, "Unhandled vartype(A): %d", vartype);
    break;
  }

  /* If this was a reference parameter, save the input for later
     comparison. */
  if (vartype & VT_BYREF) {
    pTempRef->in = pTempRef->out;
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
static void set_short_ref_value(JNIEnv *env, VARIANT variant,
                                jobject pJavaRef)
{
  if (jtype_info[JAVA_SHORT_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_SHORT_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_SHORT_RP].java_class, "setShort", "(S)V");
  }
  
  if (jtype_info[JAVA_SHORT_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setShort");
    return;
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_SHORT_RP].ref_set_value_method,
    *variant.piVal);
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
static void set_int_ref_value(JNIEnv *env, VARIANT variant, jobject pJavaRef)
{
  if (jtype_info[JAVA_INT_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_INT_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_INT_RP].java_class, "setInt", "(I)V");
  }
  
  if (jtype_info[JAVA_INT_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setInt");
    return;
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_INT_RP].ref_set_value_method,
    *variant.plVal);
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
static void set_float_ref_value(JNIEnv *env, VARIANT variant,
                                jobject pJavaRef)
{
  if (jtype_info[JAVA_FLOAT_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_FLOAT_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_FLOAT_RP].java_class, "setFloat", "(F)V");
  }
  
  if (jtype_info[JAVA_FLOAT_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setFloat");
    return;
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_FLOAT_RP].ref_set_value_method,
    *variant.pfltVal);
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
static void set_double_ref_value(JNIEnv *env, VARIANT variant,
                                 jobject pJavaRef)
{
  if (jtype_info[JAVA_DOUBLE_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_DOUBLE_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_DOUBLE_RP].java_class, "setDouble", "(D)V");
  }
  
  if (jtype_info[JAVA_DOUBLE_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setDouble");
    return;
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_DOUBLE_RP].ref_set_value_method,
    *variant.pdblVal);
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
static void set_date_ref_value(JNIEnv *env, VARIANT variant,
                                jobject pJavaRef)
{
  jobject pJavaDate;

  if (jtype_info[JAVA_DATE_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_DATE_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_DATE_RP].java_class, "setDate",
      "(Ljava/util/Date;)V");
  }
  
  if (jtype_info[JAVA_DATE_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setDate");
    return;
  }

  pJavaDate = jdate_from_DATE(env, *variant.pdate);

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_DATE_RP].ref_set_value_method,
    pJavaDate);
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
static void set_string_ref_value(JNIEnv *env, VARIANT variant,
                                jobject pJavaRef)
{
  jstring pJavaString;

  if (jtype_info[JAVA_STRING_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_STRING_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_STRING_RP].java_class, "setString",
      "(Ljava/lang/String;)V");
  }
  
  if (jtype_info[JAVA_STRING_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setString");
    return;
  }

  pJavaString = BSTR_to_jstring(env, *variant.pbstrVal);

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_STRING_RP].ref_set_value_method,
    pJavaString);
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
static void set_dispatch_pointer_ref_value(JNIEnv *env, VARIANT variant,
                                           jobject proxy, jobject pJavaRef)
{
  if (jtype_info[JAVA_IDISP_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_IDISP_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_IDISP_RP].java_class, "setActiveXDispatchable",
      "(ILcom/gensym/com/ActiveXProxy;)V");
  }
  
  if (jtype_info[JAVA_IDISP_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for "
      "setActiveXDispatchable");
    return;
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_IDISP_RP].ref_set_value_method,
    *variant.ppdispVal, proxy);
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
static void set_boolean_ref_value(JNIEnv *env, VARIANT variant,
                                  jobject pJavaRef)
{
  jboolean boolVal = JNI_FALSE;

  if (jtype_info[JAVA_BOOLEAN_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_BOOLEAN_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_BOOLEAN_RP].java_class, "setBoolean", "(Z)V");
  }
  
  if (jtype_info[JAVA_BOOLEAN_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setBoolean");
    return;
  }

  if (*variant.pboolVal)
    boolVal = JNI_TRUE;

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_BOOLEAN_RP].ref_set_value_method,
    boolVal);
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
static void set_variant_ref_value(JNIEnv *env, VARIANT variant, jobject proxy,
                                jobject pJavaRef, int isEvent)
{
  jobject pJavaVariant;

  if (jtype_info[JAVA_VARIANT_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_VARIANT_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_VARIANT_RP].java_class, "setVariant",
      "(Lcom/gensym/com/Variant;)V");
  }
  
  if (jtype_info[JAVA_VARIANT_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setVariant");
    return;
  }

  pJavaVariant = make_jobject_from_variant(env, *variant.pvarVal, proxy, isEvent);

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_VARIANT_RP].ref_set_value_method,
    pJavaVariant);
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
static void set_byte_ref_value(JNIEnv *env, VARIANT variant,
                                jobject pJavaRef)
{
  if (jtype_info[JAVA_BYTE_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_BYTE_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_BYTE_RP].java_class, "setByte", "(B)V");
  }
  
  if (jtype_info[JAVA_BYTE_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setByte");
    return;
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_BYTE_RP].ref_set_value_method,
    *variant.pbVal);
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
static void set_SA_ref_value(JNIEnv *env, VARIANT variant,
                                jobject pJavaRef)
{
  jobject pJavaSafeArray = NULL;

  if (jtype_info[JAVA_SA_RP].ref_set_value_method == NULL) {
    jtype_info[JAVA_SA_RP].ref_set_value_method = (*env)->GetMethodID(env,
      jtype_info[JAVA_SA_RP].java_class, "setSafeArray",
      "(Lcom/gensym/com/SafeArray;)V");
  }
  
  if (jtype_info[JAVA_SA_RP].ref_set_value_method == NULL) {
    (*env)->ExceptionClear(env);
    jprintf(env,DERROR, "Error: could not obtain method id for setSafeArray");
    return;
  }

  /* Since this is only called for out parameters, the arrays will be owned
     by the DLL so the caller will get the automatic destroy feature. */
  switch (variant.vt & 0xff) {
  case VT_I2:
    pJavaSafeArray = CreateShortSafeArray(env, *variant.pparray, OWNED_BY_DLL);
    break;

  case VT_I4:
    pJavaSafeArray = CreateIntSafeArray(env, *variant.pparray, OWNED_BY_DLL);
    break;

  case VT_R4:
    pJavaSafeArray = CreateFloatSafeArray(env, *variant.pparray, OWNED_BY_DLL);
    break;

  case VT_R8:
    pJavaSafeArray = CreateDoubleSafeArray(env, *variant.pparray,
                                           OWNED_BY_DLL);
    break;

  case VT_DATE:
    pJavaSafeArray = CreateDateSafeArray(env, *variant.pparray, OWNED_BY_DLL);
    break;

  case VT_BSTR:
    pJavaSafeArray = CreateStringSafeArray(env, *variant.pparray,
                                           OWNED_BY_DLL);
    break;

  case VT_BOOL:
    pJavaSafeArray = CreateBooleanSafeArray(env, *variant.pparray,
                                            OWNED_BY_DLL);
    break;

  case VT_VARIANT:
    pJavaSafeArray = CreateVariantSafeArray(env, *variant.pparray,
                                            OWNED_BY_DLL);
    break;

  case VT_UI1:
    pJavaSafeArray = CreateByteSafeArray(env, *variant.pparray, OWNED_BY_DLL);
  }

  (*env)->CallVoidMethod(env, pJavaRef,
    jtype_info[JAVA_SA_RP].ref_set_value_method,
    pJavaSafeArray);
}

/*****************************************************************************
* CopyAndFreeNativeRefParameter
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
void CopyAndFreeNativeRefParameter(JNIEnv *env, VARIANT variant, jobject proxy) 
{
  TEMP_REF *pTempRef;
  jobject pJavaRef;

  pTempRef = (TEMP_REF*)variant.byref;
  pJavaRef = pTempRef->pJavaRefParameter;

  /* Only set the ref value if there was a change, but not if the caller
     changed the variant type. */
  if (memcmp(&pTempRef->out, &pTempRef->in, sizeof(pTempRef->out)) != 0 &&
      variant.vt == pTempRef->inVartype) {
    switch (pTempRef->inVartype) {
    case VT_I2 | VT_BYREF:
      set_short_ref_value(env, variant, pJavaRef);
      break;
      
    case VT_I4 | VT_BYREF:
      set_int_ref_value(env, variant, pJavaRef);
      break;
      
    case VT_R4 | VT_BYREF:
      set_float_ref_value(env, variant, pJavaRef);
      break;
      
    case VT_R8 | VT_BYREF:
      set_double_ref_value(env, variant, pJavaRef);
      break;
      
    case VT_DATE | VT_BYREF: 
      set_date_ref_value(env, variant, pJavaRef);
      break;
      
    case VT_BSTR | VT_BYREF:
      set_string_ref_value(env, variant, pJavaRef);
      if (*variant.pbstrVal != NULL)
        SysFreeString(*variant.pbstrVal);
      break;
      
    case VT_DISPATCH | VT_BYREF:
      set_dispatch_pointer_ref_value(env, variant, proxy, pJavaRef);
      break;
      
    case VT_BOOL | VT_BYREF: 
      set_boolean_ref_value(env, variant, pJavaRef);
      break;
      
    case VT_VARIANT | VT_BYREF: 
      /* This function is not used for events */
      set_variant_ref_value(env, variant, proxy, pJavaRef, FALSE);
      break;
      
    case VT_UI1 | VT_BYREF:
      set_byte_ref_value(env, variant, pJavaRef);
      break;

    default:
      if (pTempRef->inVartype & VT_ARRAY) {
        set_SA_ref_value(env, variant, pJavaRef);
      }
    }
  }

  /* We lock safe arrays that are passed by reference and and safe arrays in
     variants passed by reference on the way in so the control can not delete
     them, so new we must unlock them here so they can be deleted by the
     caller. */
  if (pTempRef->arrayLocked) {
    if (pTempRef->arrayInVariantRef)
      SafeArrayUnlock(pTempRef->in.varVal.parray);
    else
      SafeArrayUnlock(pTempRef->in.parray);
  }

  free(pTempRef);
}

/*****************************************************************************
* CopyOutJavaRefParameter
*
*   Description: 
*   Input Arguments:
*   Returns: 
*   Notes:
*     -----
*   Modifications:
*****************************************************************************/
void CopyOutJavaRefParameter(JNIEnv *env, VARIANT variant, jobject jvariant,
    jobject proxy)
{
  BSTR bstrVal;
  jobject pJavaRef;
  IDispatch* pDispatch;
  VARIANT temp_variant;

  switch (variant.vt) {
  case VT_I2 | VT_BYREF:
    *variant.piVal = get_short_ref_value(env, jvariant, &pJavaRef);
    break;
    
  case VT_I4 | VT_BYREF:
    *variant.plVal = get_int_ref_value(env, jvariant, &pJavaRef);
    break;
    
  case VT_R4 | VT_BYREF:
    *variant.pfltVal = get_float_ref_value(env, jvariant, &pJavaRef);
    break;
    
  case VT_R8 | VT_BYREF:
    *variant.pdblVal = get_double_ref_value(env, jvariant, &pJavaRef);
    break;
    
  case VT_DATE | VT_BYREF: 
    *variant.pdate = get_date_ref_value(env, jvariant, &pJavaRef);
    break;
    
  case VT_BSTR | VT_BYREF:
    bstrVal = get_string_ref_value(env, jvariant, &pJavaRef);
    if (*variant.pbstrVal != NULL)
       SysFreeString(*variant.pbstrVal);

    *variant.pbstrVal = bstrVal;
    break;

  case VT_DISPATCH | VT_BYREF:
    pDispatch = get_dispatch_pointer_ref_value(env, jvariant,
                           proxy, &pJavaRef);
    if (pDispatch != *variant.ppdispVal) {
      pDispatch->lpVtbl->AddRef(pDispatch);
      (*variant.ppdispVal)->lpVtbl->Release(*variant.ppdispVal);
      *variant.ppdispVal = pDispatch;
    }
    break;

  case VT_BOOL | VT_BYREF: 
    *variant.pboolVal = get_boolean_ref_value(env, jvariant, &pJavaRef);
    break;
    
  case VT_VARIANT | VT_BYREF: 
    /* This function is only used by events. */
    temp_variant = get_variant_ref_value(env, jvariant, proxy, &pJavaRef, TRUE);

    if (memcmp(&temp_variant, variant.pvarVal, sizeof (VARIANT)) != 0) {
      VariantClear(variant.pvarVal);
      *variant.pvarVal = temp_variant;
    }

    break;
    
  case VT_UI1 | VT_BYREF:
    *variant.pbVal = get_byte_ref_value(env, jvariant, &pJavaRef);
    break;
  }
}
