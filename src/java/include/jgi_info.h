/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      jgi_info.h
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               10-Feb-1997   M.D.Gribble
 +
 + Description:  This file contains the definitions and macros for the
 +				 JGI interface preloaded java classes
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


#include "jni.h"
#include "com_gensym_jgi_JGInterface.h"
#include "jgi_gsi_options.h"
#include "gsi_main.h"



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


struct  JGInterfaceClassInfo_Struct {

	jobject JavaReference;				   /* Global reference to the Java object */

	jclass clazz;
	
	/* Method IDs for fast lookup of methods          */
	jmethodID G2InitializeConnection_MethodID;
        jmethodID registerIncomingConnection_MethodID;
        jmethodID G2isPaused_MethodID;
	jmethodID G2isResumed_MethodID;
        jmethodID G2isReset_MethodID;
	jmethodID G2isStarted_MethodID;
	jmethodID G2ConnectionClosed_MethodID;
	jmethodID receiveMessage_MethodID;
	jmethodID writeCallback_MethodID;
	jmethodID readCallback_MethodID;
        jmethodID setData_MethodID;
        jmethodID getData_MethodID;
        jmethodID receiveRegistration_MethodID;
        jmethodID invokeMethod_MethodID;
        jmethodID invokeMethodObject_MethodID;
        jmethodID getHandleForObject_MethodID;
        jmethodID getJavaObjectForJavaProxy_MethodID;
        jmethodID getG2ClassForJavaProxy_MethodID;
        jmethodID communicationError_MethodID;
        jmethodID getG2ItemInfo_MethodID;
        jmethodID setCurrentContext_MethodID;

	/* Field IDs */
	

};

typedef struct JGInterfaceClassInfo_Struct *JGInterfaceClassInfo;


#define JREF(x)		(x)->JavaReference


/* G2Connection context instance record structure */
struct ContextData_Struct {

	jobject JavaReference;				   /* Global reference to the Java object */

	jclass clazz;
	
	/* Method IDs for fast lookup of methods          */
	/* These are looked up on a per instance basis as */
	/* the user may have been subclassed G2Gateway    */
	jmethodID G2InitializeConnection_MethodID;
	jmethodID G2isPaused_MethodID;
	jmethodID G2isResumed_MethodID;
	jmethodID G2ConnectionClosed_MethodID;
	jmethodID receiveMessage_MethodID;
	jmethodID writeCallback_MethodID;
	jmethodID readCallback_MethodID;
        jmethodID createStub_MethodID;
        jmethodID invalidateStub_MethodID;

	int   context;					   /* The GSI context */
        jstring  remoteInitString;
        jboolean receiveRegistrations;
        jboolean authorizedforjlp;
        jboolean authorizedforjl;
};

typedef struct ContextData_Struct *ContextData;


struct RemoteRPCThreadClassInfo_Struct {

	jclass clazz;
        jclass deferredStubClass;

	/* Method IDs for fast lookup of methods */
        jmethodID signalReturnError_MethodID;
        jmethodID signalReturnValue_MethodID;

	/* Field IDs for fast lookup of fields */
	jfieldID retnvalue_FieldID;
        jfieldID incompleteConversion_FieldID;

};

typedef struct RemoteRPCThreadClassInfo_Struct *RemoteRPCThreadClassInfo;


struct ClassClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
        jmethodID getName_MethodID;
	
	
	/* Field IDs for fast lookup of fields */
	

};

typedef struct ClassClassInfo_Struct *ClassClassInfo;


struct SequenceClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	jmethodID size_MethodID;
        jmethodID print_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;
        jfieldID elementCount_FieldID;

};

typedef struct SequenceClassInfo_Struct *SequenceClassInfo;


 struct G2ItemProxyClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;

	jmethodID doprint_MethodID;
	jmethodID getHandle_MethodID;
	jmethodID setHandle_MethodID;
	jmethodID getClassName_MethodID;
	jmethodID setClassName_MethodID;
	jmethodID getName_MethodID;
	jmethodID setName_MethodID;
	jmethodID getValue_MethodID;
	jmethodID setValue_MethodID;

        /* History */
	jmethodID getHistory_MethodID;
	jmethodID setHistory_MethodID;
	jmethodID getValueAtTime_MethodID;

	
	/* Field IDs for fast lookup of fields */
	jfieldID attributes_FieldID;
	jfieldID classname_FieldID;
	jfieldID handle_FieldID;
};

typedef struct G2ItemProxyClassInfo_Struct *G2ItemProxyClassInfo;

struct ItemImplClassInfo_Struct {

	jclass clazz;

	jfieldID handle_FieldID;
        jfieldID data_FieldID;
};

typedef struct ItemImplClassInfo_Struct *ItemImplClassInfo;

struct ItemDataClassInfo_Struct {
  
        jclass clazz;
  
        jfieldID itemIsValid_FieldID;
};

typedef struct ItemDataClassInfo_Struct *ItemDataClassInfo;

struct ItemClassInfo_Struct {

	jclass clazz;

	jfieldID handle_FieldID;
};

typedef struct ItemClassInfo_Struct *ItemClassInfo;



struct SymbolClassInfo_Struct {

	jclass clazz;
        jclass symbolArray_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID intern_MethodID;
	jmethodID getPrintValue_MethodID;
        jmethodID equals_MethodID;
	/* Field IDs for fast lookup of fields */


};

typedef struct SymbolClassInfo_Struct *SymbolClassInfo;


struct StructureClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "([Lcom/gensym/util/Symbol;[Ljava/lang/Object;)" */

	jmethodID getAttributeNames_MethodID;
	jmethodID getAttributeValues_MethodID;
	jmethodID getAttributeCount_MethodID;
	jmethodID getAttributes_MethodID;
	
	/* Field IDs for fast lookup of fields */


};

typedef struct StructureClassInfo_Struct *StructureClassInfo;


struct ObjectClassInfo_Struct {

	jclass clazz;
        jclass objectArray_clazz;

	/* Method IDs for fast lookup of methods */
	
	
	/* Field IDs for fast lookup of fields */


};

typedef struct ObjectClassInfo_Struct *ObjectClassInfo;

struct NumberClassInfo_Struct {

	jclass clazz;
        jclass numberArray_clazz;

	/* Method IDs for fast lookup of methods */
	
	
	/* Field IDs for fast lookup of fields */


};

typedef struct NumberClassInfo_Struct *NumberClassInfo;




struct IntegerClassInfo_Struct {

	jclass clazz;
        jclass intTypeArray_clazz;
        jclass intType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */
	jmethodID intValue_MethodID	;
        jmethodID parseInt_MethodID;
	/* Field IDs for fast lookup of fields */


};

typedef struct IntegerClassInfo_Struct *IntegerClassInfo;

struct LongClassInfo_Struct {

	jclass clazz;
        jclass longTypeArray_clazz;
        jclass longType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */
	jmethodID intValue_MethodID	;
        jmethodID parseLong_MethodID;
        jmethodID toString_MethodID;
	/* Field IDs for fast lookup of fields */


};

typedef struct LongClassInfo_Struct *LongClassInfo;

struct ShortClassInfo_Struct {

	jclass clazz;
        jclass shortTypeArray_clazz;
        jclass shortType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */
	jmethodID intValue_MethodID	;
	/* Field IDs for fast lookup of fields */


};

typedef struct ShortClassInfo_Struct *ShortClassInfo;


struct ByteClassInfo_Struct {

	jclass clazz;
        jclass byteTypeArray_clazz;
        jclass byteType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */
	jmethodID intValue_MethodID	;
	/* Field IDs for fast lookup of fields */


};

typedef struct ByteClassInfo_Struct *ByteClassInfo;


struct CharacterClassInfo_Struct {

	jclass clazz;
        jclass characterTypeArray_clazz;
        jclass characterType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */
	jmethodID charValue_MethodID	;
	/* Field IDs for fast lookup of fields */


};

typedef struct CharacterClassInfo_Struct *CharacterClassInfo;


struct DoubleClassInfo_Struct {

	jclass clazz;
        jclass doubleTypeArray_clazz;
        jclass doubleType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(D)" */
	jmethodID doubleValue_MethodID;
	/* Field IDs for fast lookup of fields */


};

typedef struct DoubleClassInfo_Struct *DoubleClassInfo;


struct FloatClassInfo_Struct {

	jclass clazz;
        jclass floatType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(F)" */
        jmethodID initd_MethodID; /* for  "(D)" */
	jmethodID doubleValue_MethodID;
	/* Field IDs for fast lookup of fields */


};

typedef struct FloatClassInfo_Struct *FloatClassInfo;


struct BooleanClassInfo_Struct {

	jclass clazz;
        jclass booleanTypeArray_clazz;
        jclass booleanType_clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(Z)" */
	jmethodID booleanValue_MethodID;

	/* Field IDs for fast lookup of fields */

        /* values */
        jobject Boolean_TRUE;
        jobject Boolean_FALSE;

};

typedef struct BooleanClassInfo_Struct *BooleanClassInfo;


 
struct StringClassInfo_Struct {

	jclass clazz;
        jclass stringArray_clazz;

	/* Method IDs for fast lookup of methods */
	
	/* Field IDs for fast lookup of fields */


};

typedef struct StringClassInfo_Struct *StringClassInfo;


 
struct EnumerationClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID nextElement_MethodID;

	/* Field IDs for fast lookup of fields */


};

typedef struct EnumerationClassInfo_Struct *EnumerationClassInfo;


struct VectorClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	jmethodID size_MethodID;
	jmethodID addElement_MethodID;

	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct VectorClassInfo_Struct *VectorClassInfo;


struct PropertyClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;

	/* Field IDs for fast lookup of fields */
	jfieldID key_FieldID;
	jfieldID value_FieldID;
};

typedef struct PropertyClassInfo_Struct *PropertyClassInfo;



struct G2ListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */

	jmethodID setItemAttribute_MethodID	;
	jmethodID doprint_MethodID	;
	jmethodID getAttributes_MethodID	;
	jmethodID getHandle_MethodID	;
	jmethodID getClassName_MethodID	;

	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;
	jfieldID attributes_FieldID;
	jfieldID classname_FieldID;
	jfieldID handle_FieldID;

};

typedef struct G2ListClassInfo_Struct *G2ListClassInfo;



struct ItemListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct ItemListClassInfo_Struct *ItemListClassInfo;


struct ValueListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct ValueListClassInfo_Struct *ValueListClassInfo;


struct QuantityListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct QuantityListClassInfo_Struct *QuantityListClassInfo;


struct FloatListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct FloatListClassInfo_Struct *FloatListClassInfo;

struct IntegerListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct IntegerListClassInfo_Struct *IntegerListClassInfo;

struct SymbolListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct SymbolListClassInfo_Struct *SymbolListClassInfo;



struct TextListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct TextListClassInfo_Struct *TextListClassInfo;


struct TruthValueListClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct TruthValueListClassInfo_Struct *TruthValueListClassInfo;



struct G2ArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;  /* for  "(I)" */

	jmethodID setItemAttribute_MethodID	;
	jmethodID doprint_MethodID	;
	jmethodID getAttributes_MethodID	;
	jmethodID getHandle_MethodID	;
	jmethodID getClassName_MethodID	;
        jmethodID getContents_MethodID ;

	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;
	jfieldID attributes_FieldID;
	jfieldID classname_FieldID;
	jfieldID handle_FieldID;

};

typedef struct G2ArrayClassInfo_Struct *G2ArrayClassInfo;



struct ItemArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;
};

typedef struct ItemArrayClassInfo_Struct *ItemArrayClassInfo;


struct ValueArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct ValueArrayClassInfo_Struct *ValueArrayClassInfo;


struct QuantityArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct QuantityArrayClassInfo_Struct *QuantityArrayClassInfo;


struct FloatArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct FloatArrayClassInfo_Struct *FloatArrayClassInfo;

struct IntegerArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct IntegerArrayClassInfo_Struct *IntegerArrayClassInfo;






struct SymbolArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct SymbolArrayClassInfo_Struct *SymbolArrayClassInfo;



struct TextArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct TextArrayClassInfo_Struct *TextArrayClassInfo;


struct TruthValueArrayClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID init_MethodID;
	
	/* Field IDs for fast lookup of fields */
	jfieldID elementData_FieldID;


};

typedef struct TruthValueArrayClassInfo_Struct *TruthValueArrayClassInfo;



struct ThrowableClassInfo_Struct {

	jclass generalclazz;

	/* Method IDs for fast lookup of methods */
	jmethodID toString_MethodID;

	/* Field IDs for fast lookup of fields */

};

typedef struct ThrowableClassInfo_Struct *ThrowableClassInfo;

struct DebugUtilClassInfo_Struct {

        jclass clazz;

        jmethodID getStackTrace_MethodID;

};

typedef struct DebugUtilClassInfo_Struct *DebugUtilClassInfo;


struct G2CommunicationExceptionClassInfo_Struct {

	jclass clazz;

	/* Method IDs for fast lookup of methods */
	jmethodID toString_MethodID;

	/* Field IDs for fast lookup of fields */


};

typedef struct G2CommunicationExceptionClassInfo_Struct *G2CommunicationExceptionClassInfo;


struct JavaMethodCallInfo_Struct {

	jobject	java_object; 
	jobject java_method;
        jstring java_method_name;
        jobject G2_RPD_name;
        jboolean force_return_value;
        jboolean run_in_own_thread;
        jboolean run_in_queued_thread;

};

typedef struct JavaMethodCallInfo_Struct *JavaMethodCallInfo;




extern RemoteRPCThreadClassInfo	   remoteRPCThreadClassInfo;
extern ClassClassInfo	           classClassInfo;
extern SequenceClassInfo	   sequenceClassInfo;
extern G2ItemProxyClassInfo	   g2ItemProxyClassInfo;
extern ItemImplClassInfo           itemImplClassInfo;
extern ItemDataClassInfo           itemDataClassInfo;
extern ItemClassInfo               itemClassInfo;
extern SymbolClassInfo		   symbolClassInfo;
extern StructureClassInfo	   structureClassInfo;
extern ObjectClassInfo		   objectClassInfo;
extern NumberClassInfo             numberClassInfo;
extern IntegerClassInfo		   integerClassInfo;
extern LongClassInfo		   longClassInfo;
extern ShortClassInfo		   shortClassInfo;
extern ByteClassInfo		   byteClassInfo;
extern CharacterClassInfo	   characterClassInfo;
extern DoubleClassInfo		   doubleClassInfo;
extern FloatClassInfo		   floatClassInfo;
extern BooleanClassInfo		   booleanClassInfo;
extern StringClassInfo		   stringClassInfo;
extern EnumerationClassInfo        enumerationClassInfo;
extern VectorClassInfo             vectorClassInfo;
extern PropertyClassInfo           propertyClassInfo;
extern JGInterfaceClassInfo	   registeredJGInterface;
extern ThrowableClassInfo	   throwableClassInfo;
extern DebugUtilClassInfo	   debugUtilClassInfo;
extern G2CommunicationExceptionClassInfo        g2CommunicationExceptionClassInfo;
extern G2ListClassInfo		   g2ListClassInfo;
extern ItemListClassInfo            itemListClassInfo;
extern ValueListClassInfo           valueListClassInfo;
extern QuantityListClassInfo        quantityListClassInfo;
extern IntegerListClassInfo         integerListClassInfo;
extern FloatListClassInfo           floatListClassInfo;
extern SymbolListClassInfo          symbolListClassInfo;
extern TruthValueListClassInfo      truthValueListClassInfo;
extern TextListClassInfo            textListClassInfo;

extern G2ArrayClassInfo		     g2ArrayClassInfo;
extern ItemArrayClassInfo            itemArrayClassInfo;
extern ValueArrayClassInfo           valueArrayClassInfo;
extern QuantityArrayClassInfo        quantityArrayClassInfo;
extern IntegerArrayClassInfo         integerArrayClassInfo;
extern FloatArrayClassInfo           floatArrayClassInfo;
extern SymbolArrayClassInfo          symbolArrayClassInfo;
extern TruthValueArrayClassInfo      truthValueArrayClassInfo;
extern TextArrayClassInfo            textArrayClassInfo;


extern ContextData					*contextDataLookup;
extern int							contextDataLookup_Size;

/* Predeclared Java Symbols*/
extern jobject			    nameSymbol;
extern jobject                      namesSymbol;
extern jobject                      noneSymbol;
extern jobject                      lastRecordedValueSymbol;
extern jobject                      classSymbol;
extern jobject                      valueSymbol;
extern jobject                      itemSymbol;
extern jobject                      integerSymbol;
extern jobject                      truthValueSymbol;
extern jobject                      symbolSymbol;
extern jobject                      textSymbol;
extern jobject                      floatSymbol;
extern jobject                      valueSymbol;
extern jobject                      itemOrValueSymbol;
extern jobject                      quantitySymbol;
extern jobject                      hiddenG2ArraySymbol;
extern jobject                      elementTypeSymbol;
extern jobject                      g2ListSequenceSymbol;
extern jobject			    G2JavaShortClassSymbol;
extern jobject			    G2JavaByteClassSymbol;
extern jobject			    G2JavaLongClassSymbol;
extern jobject			    G2JavaCharClassSymbol;
extern jobject                      G2JavaIntClassSymbol;
extern jobject                      G2JavaFloatClassSymbol;
extern jobject			    G2JavaIntTypeArrayClassSymbol;
extern jobject			    G2JavaBooleanTypeArrayClassSymbol;
extern jobject			    G2JavaSymbolArrayClassSymbol;
extern jobject			    G2JavaStringArrayClassSymbol;
extern jobject			    G2JavaDoubleTypeArrayClassSymbol;
extern jobject			    G2JavaNumberArrayClassSymbol;
extern jobject			    G2JavaObjectArrayClassSymbol;

extern gsi_symbol  window_gsisymbol;
extern gsi_symbol  popup_gsisymbol;
extern gsi_symbol  g2_floatarray_classname_gsisymbol;
extern gsi_symbol  g2_g2array_classname_gsisymbol;
extern gsi_symbol  g2_integerarray_classname_gsisymbol;
extern gsi_symbol  g2_itemarray_classname_gsisymbol;
extern gsi_symbol  g2_quantityarray_classname_gsisymbol;
extern gsi_symbol  g2_sequencearray_classname_gsisymbol;
extern gsi_symbol  g2_structurearray_classname_gsisymbol;
extern gsi_symbol  g2_symbolarray_classname_gsisymbol; 
extern gsi_symbol  g2_textarray_classname_gsisymbol; 
extern gsi_symbol  g2_truthvaluearray_classname_gsisymbol;
extern gsi_symbol  g2_valuearray_classname_gsisymbol;
extern gsi_symbol  g2_javaproxy_classname_attr_gsisymbol;
extern gsi_symbol  g2_javatype_class_val_attr_gsisymbol;
extern gsi_symbol  g2_javalong_classname_gsisymbol;
extern gsi_symbol  g2_javashort_classname_gsisymbol;
extern gsi_symbol  g2_javabyte_classname_gsisymbol;
extern gsi_symbol  g2_javachar_classname_gsisymbol;
extern gsi_symbol  g2_javafloat_classname_gsisymbol;

extern gsi_char *null_str;
extern gsi_char *none_str;
extern gsi_char *empty_str;
extern gsi_char *g2_floatarray_classname;
extern gsi_char *g2_g2array_classname;
extern gsi_char *g2_integerarray_classname;
extern gsi_char *g2_itemarray_classname;
extern gsi_char *g2_quantityarray_classname;
extern gsi_char *g2_sequencearray_classname;
extern gsi_char *g2_structurearray_classname;
extern gsi_char *g2_symbolarray_classname;
extern gsi_char *g2_textarray_classname;
extern gsi_char *g2_truthvaluearray_classname;
extern gsi_char *g2_valuearray_classname;
extern gsi_char *g2_javaproxy_classname_attr;
extern gsi_char *g2_javatype_class_val_attr;
extern gsi_char *g2_javashort_classname;
extern gsi_char *g2_javabyte_classname;
extern gsi_char *g2_javalong_classname;
extern gsi_char *g2_javachar_classname;
extern gsi_char *g2_javaint_classname;
extern gsi_char *g2_javafloat_classname;
extern gsi_char *g2_raw_java_inttypearray_classname;
extern gsi_char *g2_raw_java_booleantypearray_classname;
extern gsi_char *g2_raw_java_symbolarray_classname;
extern gsi_char *g2_raw_java_stringarray_classname;
extern gsi_char *g2_raw_java_doubletypearray_classname;
extern gsi_char *g2_raw_java_numberarray_classname;
extern gsi_char *g2_raw_java_objectarray_classname;

extern JNIEnv *gsiRunLoopThreadEnv;


#define PRINT_EXCEPTION(env) if ((*env)->ExceptionOccurred(env)) (*env)->ExceptionDescribe(env);
#define FULLDEBUG_PRINT_EXCEPTION(env) if (fulldebug && (*env)->ExceptionOccurred(env)) (*env)->ExceptionDescribe(env);
#define THROW_GENERAL_EXCEPTION(env, msg) (*env)->ThrowNew(env, throwableClassInfo->generalclazz, msg);
#define THROW_G2COMS_EXCEPTION(env, msg) \
     (*env)->ThrowNew(env, g2CommunicationExceptionClassInfo->clazz, msg);


#define interning_signature "(Ljava/lang/String;)Lcom/gensym/util/Symbol;"

#ifdef GSI_USE_WIDE_STRING_API
#define JNI_GETSTRINGCHARS GetStringChars
#define JNI_RELEASESTRINGCHARS ReleaseStringChars
#define JNI_GETSTRINGLENGTH GetStringLength
#else
#define JNI_GETSTRINGCHARS GetStringUTFChars
#define JNI_RELEASESTRINGCHARS ReleaseStringUTFChars
#define JNI_GETSTRINGLENGTH GetStringUTFLength
#endif


#define java_intern_symbol(ENV, STRING_TO_INTERN) \
		(*ENV)->CallStaticObjectMethod(ENV, \
					symbolClassInfo->clazz, \
					symbolClassInfo->intern_MethodID, \
					jgi_NewString(ENV, STRING_TO_INTERN))

#define java_intern_symbol_utf(ENV, STRING_TO_INTERN) \
		(*ENV)->CallStaticObjectMethod(ENV, \
					symbolClassInfo->clazz, \
					symbolClassInfo->intern_MethodID, \
					(*ENV)->NewStringUTF(ENV, STRING_TO_INTERN))


/* Until we get exception passing to G2, just use message board for now */
#define jgsi_return_error_message jgsi_return_message 

#define create_global_java_symbol(ENV, VARIABLE, SYMBOL) \
	VARIABLE = java_intern_symbol_utf (ENV, SYMBOL); \
	VARIABLE = (*ENV)->NewGlobalRef(ENV, VARIABLE); \
	PRINT_EXCEPTION(ENV)




