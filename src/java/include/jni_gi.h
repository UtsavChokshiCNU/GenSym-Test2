/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      jni_gi.h
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               1-Jan-1997  M.D.Gribble
 +
 + Description:  This file contains the general H definitions for the
 +				 native interface between Java JNI and GSI
 +               
 +               
 + 
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following: 
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES 
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      DECLARATION FUNCTIONS
 +
 +      
 + External Interface:
 +
 + Dependencies:
 +      This file has no external dependencies.
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include <stdarg.h>
#include <stdio.h>



/*#include "native.h"*/
#include "jni.h"

#include "jgi_gsi_options.h"
/*#include "jgi_locks.h"*/
#include "jgi_info.h" 
#include "gsi_misc.h"


#include "com_gensym_jgi_JGInterface.h"
#include "com_gensym_jgi_GsiLoopThread.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section. 
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


#define TCPIP_PORT_NUMBER  0

#define JAVA_ITEM_OK		0
#define JAVA_ITEM_BAD		1
#define JAVA_ITEM_VOID		2
#define JAVA_ITEM_BAD_ALREADY_THREW 3

#define JAVA_G2ITEMPROXY_SIGNATURE             "Lcom/gensym/util/G2ItemProxy;"
#define JAVA_STRUCTURE_SIGNATURE               "Lcom/gensym/util/Structure;"
#define JAVA_SEQUENCE_SIGNATURE                "Lcom/gensym/util/Sequence;"
#define JAVA_SYMBOL_SIGNATURE                  "Lcom/gensym/util/Symbol;"
#define JAVA_DOWNLOAD_SIGNATURE                "Lcom/gensym/util/DownLoad;"
#define JAVA_LANGOBJECT_SIGNATURE              "Ljava/lang/Object;"

#define JAVA_FLOATLIST_SIGNATURE		"Lcom/gensym/util/FloatList;"
#define JAVA_G2LIST_SIGNATURE			"Lcom/gensym/util/G2List;"
#define JAVA_INTEGERLIST_SIGNATURE		"Lcom/gensym/util/IntegerList;"
#define JAVA_ITEMLIST_SIGNATURE			"Lcom/gensym/util/ItemList;"
#define JAVA_QUANTITYLIST_SIGNATURE		"Lcom/gensym/util/QuantityList;"
#define JAVA_SEQUENCELIST_SIGNATURE		"Lcom/gensym/util/SequenceList;"
#define JAVA_STRUCTURELIST_SIGNATURE	        "Lcom/gensym/util/StructureList;"
#define JAVA_SYMBOLLIST_SIGNATURE		"Lcom/gensym/util/SymbolList;"
#define JAVA_TEXTLIST_SIGNATURE			"Lcom/gensym/util/TextList;"
#define JAVA_TRUTHVALUELIST_SIGNATURE	        "Lcom/gensym/util/TruthValueList;"
#define JAVA_VALUELIST_SIGNATURE		"Lcom/gensym/util/ValueList;"

#define JAVA_FLOATARRAY_SIGNATURE		"Lcom/gensym/util/FloatArray;"
#define JAVA_G2ARRAY_SIGNATURE			"Lcom/gensym/util/G2Array;"
#define JAVA_INTEGERARRAY_SIGNATURE		"Lcom/gensym/util/IntegerArray;"
#define JAVA_ITEMARRAY_SIGNATURE			"Lcom/gensym/util/ItemArray;"
#define JAVA_QUANTITYARRAY_SIGNATURE		"Lcom/gensym/util/QuantityArray;"
#define JAVA_SYMBOLARRAY_SIGNATURE		"Lcom/gensym/util/SymbolArray;"
#define JAVA_TEXTARRAY_SIGNATURE			"Lcom/gensym/util/TextArray;"
#define JAVA_TRUTHVALUEARRAY_SIGNATURE	        "Lcom/gensym/util/TruthValueArray;"
#define JAVA_VALUEARRAY_SIGNATURE		"Lcom/gensym/util/ValueArray;"

#define JAVA_doubleARRAY_SIGNATURE		"[D"
#define JAVA_intARRAY_SIGNATURE		        "[I"
#define JAVA_ObjectARRAY_SIGNATURE		"[Ljava/lang/Object;"
#define JAVA_NumberARRAY_SIGNATURE		"[Ljava/lang/Number;"
#define JAVA_SymbolARRAY_SIGNATURE		"[Lcom/gensym/util/Symbol;"
#define JAVA_StringARRAY_SIGNATURE		"[Ljava/lang/String;"
#define JAVA_booleanARRAY_SIGNATURE	        "[Z"



#define JAVA_VOID_SIGNATURE    "V"
#define JAVA_BOOLEAN_SIGNATURE "Z"
#define JAVA_CHAR_SIGNATURE    "C"
#define JAVA_BYTE_SIGNATURE    "B"
#define JAVA_SHORT_SIGNATURE   "S"
#define JAVA_INT_SIGNATURE     "I"
#define JAVA_LONG_SIGNATURE    "J"
#define JAVA_FLOAT_SIGNATURE   "F"
#define JAVA_DOUBLE_SIGNATURE  "D"
#define JAVA_CLASS_SIGNATURE   "L"

#define JAVA_VOID_SIGNATURE_CHAR    'V'
#define JAVA_BOOLEAN_SIGNATURE_CHAR 'Z'
#define JAVA_CHAR_SIGNATURE_CHAR    'C'
#define JAVA_BYTE_SIGNATURE_CHAR    'B'
#define JAVA_SHORT_SIGNATURE_CHAR   'S'
#define JAVA_INT_SIGNATURE_CHAR     'I'
#define JAVA_LONG_SIGNATURE_CHAR    'J'
#define JAVA_FLOAT_SIGNATURE_CHAR   'F'
#define JAVA_DOUBLE_SIGNATURE_CHAR  'D'
#define JAVA_CLASS_SIGNATURE_CHAR   'L'

#define G2_FLOATARRAY_CLASSNAME		"FLOAT-ARRAY"
#define G2_G2ARRAY_CLASSNAME		"G2-ARRAY"
#define G2_INTEGERARRAY_CLASSNAME	"INTEGER-ARRAY"
#define G2_ITEMARRAY_CLASSNAME		"ITEM-ARRAY"
#define G2_QUANTITYARRAY_CLASSNAME	"QUANTITY-ARRAY"
#define G2_SEQUENCEARRAY_CLASSNAME	"SEQUENCE-ARRAY"
#define G2_STRUCTUREARRAY_CLASSNAME	"STRUCTURE-ARRAY"
#define G2_SYMBOLARRAY_CLASSNAME	"SYMBOL-ARRAY"
#define G2_TEXTARRAY_CLASSNAME		"TEXT-ARRAY"
#define G2_TRUTHVALUEARRAY_CLASSNAME	"TRUTH-VALUE-ARRAY"
#define G2_VALUEARRAY_CLASSNAME		"VALUE-ARRAY"

#define G2_RAW_JAVA_DOUBLETYPEARRAY_CLASSNAME	"JAVA.LANG.DOUBLE.TYPE[]"
#define G2_RAW_JAVA_FLOATTYPEARRAY_CLASSNAME    "JAVA.LANG.FLOAT.TYPE[]"
#define G2_RAW_JAVA_OBJECTARRAY_CLASSNAME	"JAVA.LANG.OBJECT.TYPE[]"
#define G2_RAW_JAVA_INTTYPEARRAY_CLASSNAME	"JAVA.LANG.INTEGER.TYPE[]"
#define G2_RAW_JAVA_NUMBERARRAY_CLASSNAME	"JAVA.LANG.NUMBER.TYPE[]"
#define G2_RAW_JAVA_SYMBOLARRAY_CLASSNAME	"COM.GENSYM.UTIL.SYMBOL[]"
#define G2_RAW_JAVA_STRINGARRAY_CLASSNAME	"JAVA.LANG.STRING[]"
#define G2_RAW_JAVA_BOOLEANTYPEARRAY_CLASSNAME	"JAVA.LANG.BOOLEAN.TYPE[]"
#define G2_RAW_JAVA_BYTEARRAY_CLASSNAME         "JAVA.LANG.BYTE.TYPE[]"
#define G2_RAW_JAVA_SHORTARRAY_CLASSNAME        "JAVA.LANG.SHORT.TYPE[]"
#define G2_RAW_JAVA_CHARACTERARRAY_CLASSNAME    "JAVA.LANG.CHARACTER.TYPE[]"
#define G2_RAW_JAVA_LONGARRAY_CLASSNAME         "JAVA.LANG.LONG.TYPE[]"
#define G2_RAW_JAVA_FLOATARRAY_CLASSNAME        "JAVA.LANG.FLOAT.TYPE[]"


/* Special G2 Classes created to represent Java types */
#define G2_JAVALONG_CLASSNAME           "JAVA.LANG.LONG.TYPE"
#define G2_JAVASHORT_CLASSNAME          "JAVA.LANG.SHORT.TYPE"
#define G2_JAVABYTE_CLASSNAME           "JAVA.LANG.BYTE.TYPE"
#define G2_JAVACHAR_CLASSNAME           "JAVA.LANG.CHARACTER.TYPE"
#define G2_JAVAINT_CLASSNAME            "JAVA.LANG.INTEGER.TYPE"
#define G2_JAVAFLOAT_CLASSNAME          "JAVA.LANG.FLOAT.TYPE"
/* the value attribute name for these types */
#define G2_JAVATYPE_CLASS_VAL_ATTR      "VAL"

#define G2_JAVAPROXY_CLASSNAME          "JGI-JAVA-PROXY"

/* Attributes of JAVAPROXY */
#define G2_JAVAPROXY_HANDLE_ATTR        "HANDLE"
#define G2_JAVAPROXY_CLASSNAME_ATTR     "JAVA-CLASSNAME"

#define NOT_SIMPLE_ITEM 0
#define IS_SIMPLE_ITEM 1


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/* None as this file is included by multiple C file */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DECLARATIONS
 %
 % Description:  Declarations of function prototypes and externs
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/



/* Forward reference */

/* externs */
extern int test;
extern int debug;
extern int fundebug;
extern int convdebug;
extern int fulldebug;




/* from jgi_utils.c */

void jgi_initIntegerCacheStore();

jobject  jgi_getJavaInteger(JNIEnv *env, jint i);

jvalue call_java_method(JNIEnv *env,
			 jobject java_object,
			 jmethodID methodID,
			 char *return_signature,
			 jvalue *java_args_ptr);

void return_gsi_values_from_java_method_call(
				   JNIEnv *env, 
				   jvalue return_val,
				   jboolean force_return_value,
				   char *return_signature,
				   gsi_int call_handle,
				   jboolean error,
				   jobject error_symbol,
				   jstring error_text,
				   gsi_int context);

void  invoke_declared_java_method( JNIEnv *env, 
			   jobject conneciton,
			   jobject G2_RPD_name,
			   jboolean non_connection_specific,
			   gsi_item args[],
			   gsi_int cnt,
			   gsi_int call_index,
			   gsi_int context);

void  invoke_java_method( JNIEnv *env,  
			   jobject java_object, 
			   jobject G2_RPD_name,
			   jobject java_method_object,
			   gsi_item args[],
			   gsi_int cnt,
			   jboolean force_return_value,
			   jboolean run_in_own_thread,
			   jboolean run_in_queued_thread,
			   gsi_int call_index,
			   gsi_int context);

extern int get_gsiitems_from_java_objects();

unsigned short* jgi_str2unicode (char* string);
char* jgi_unicode2str (unsigned short* unicode_string);
int jgi_wstrlen (unsigned short* unicode_string);
void jgi_printStr(gsi_char *);
jstring jgi_NewString(JNIEnv *env, gsi_char *str);
gsi_char * jgi_GetStringChars(JNIEnv *env, jstring jstr);

jobject java_intern_from_gsi_symbol(JNIEnv *env, gsi_symbol gsisymbol, jobject def);
void jgi_reportG2LogBookErrorMessage(JNIEnv *env, 
			      jobject error_symbol, 
			      jobject error_text,
			      gsi_int call_handle,
			      gsi_int context);

jboolean isSameSymbol (JNIEnv *env,
		       jobject symbol1,
		       jobject symbol2);

void return_java_values (JNIEnv *env,
			 jobjectArray itemsArray,
			 jobjectArray itemAttributes,
			 jobjectArray itemValues,
			 jintArray    itemStatuses,
			 gsi_int context);

void return_java_value_and_attrs (JNIEnv *env,
				 jobject javaitem,
				 jobject atts,
				 jobject javavalue,
				 jint    javastatus,
				 gsi_int context);

/* from jni_gi_javaconv.c */
int convert_java_object_to_gsiitem(
					JNIEnv *env,
					jobject java_gsiitem,
					gsi_item *gsiitem,      /* gsi_item wil be created here */
					gsi_int context);

int get_gsiitems_from_java_objects(JNIEnv *env, 
				    jarray java_gsiitems_array,
				    gsi_item *gsi_items_array,
				    int numargs,
				    gsi_int context);

int convert_primitive_java_value_to_gsiitem (JNIEnv *env,
					      jvalue java_value,
					      char *signature,
					      gsi_item gsiitem );

int setup_gsiitem_from_simple_java_object (JNIEnv *env ,
					   jobject obj, 
					   gsi_item gsiitem,
					   gsi_int context);

gsi_attr * update_gsiitem_attributes(JNIEnv *env,
		       gsi_item gsiitem,
		       jobject attributesStruct,
		       gsi_int context);


/* From jni_gi_gsiconv.c */
jobject create_java_sequence_from_gsiitems(JNIEnv*, gsi_item*, int);
jobject create_java_object_from_complex_gsiitem (JNIEnv*, gsi_item, jclass*);
jobject create_java_object_from_gsiitem(JNIEnv *,gsi_item, jclass*, jboolean, jboolean);

/* jni_gi_init.c */
void construct_pre_lookup_class_information();
void construct_pre_lookup_symbol_gsi_information(JNIEnv *env);

/* jni_gi_rpc.c */
void jgi_define_predeclared_rpcs();

/* jni_gi.c */
jboolean jgi_check_and_return_g2_exception
  (JNIEnv *env, jint context);
ContextData jgi_get_context_object
  (JNIEnv *env, gsi_int context);
void jgi_describeJavaObject (JNIEnv *env, jobject jobj);

