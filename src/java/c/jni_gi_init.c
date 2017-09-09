/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      jni_gi_init.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               14-Feb-1997   J.Postokyo/M.D.Gribble
 +
 + Description:  This file cointains initialiszation routines
 +				 for the GSI java JNI interface
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
 +   Section:      FUNCTION GROUP - Window Management Functions
 +      AFUNCTION		1111111 Conditionally Defined
 +
 +      
 + External Interface:
 +
 +
 +
 + Dependencies:
 +     Many functions in this file depend on the structure and format
 +	   of GSI data structures and Java data structures
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

#include "jni_gi.h"



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

#define MAKE_JAVA_AND_GSI_SYMBOL(ENV, JavaSymbolVar, G2_sym_name) { \
  gsi_symbol gsisym;\
  JavaSymbolVar = java_intern_symbol(ENV, G2_sym_name);\
  JavaSymbolVar = (*env)->NewGlobalRef(ENV, JavaSymbolVar);\
  /* Make a gsi_symbol for our new symbol so we can do comparisons on symbol user data */\
  gsisym = gsi_make_symbol (G2_sym_name);\
  gsi_set_symbol_user_data (gsisym, JavaSymbolVar);\
  }


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

 /* For pre lookup class information */


/* REMOVE ONLY FOR DEBUGABBLE G2 */
int errno;

struct JGInterfaceClassInfo_Struct jGInterfaceClassInfo_Struct;
JGInterfaceClassInfo registeredJGInterface = &jGInterfaceClassInfo_Struct;

struct RemoteRPCThreadClassInfo_Struct remoteRPCThreadClassInfo_Struct;
RemoteRPCThreadClassInfo remoteRPCThreadClassInfo = &remoteRPCThreadClassInfo_Struct;

struct ClassClassInfo_Struct classClassInfo_Struct;
ClassClassInfo classClassInfo = &classClassInfo_Struct;

struct SequenceClassInfo_Struct sequenceClassInfo_Struct;
SequenceClassInfo sequenceClassInfo = &sequenceClassInfo_Struct;


struct G2ItemProxyClassInfo_Struct g2ItemProxyClassInfo_Struct;
G2ItemProxyClassInfo g2ItemProxyClassInfo = &g2ItemProxyClassInfo_Struct;

struct ItemImplClassInfo_Struct itemImplClassInfo_Struct;
ItemImplClassInfo itemImplClassInfo = &itemImplClassInfo_Struct;

struct ItemDataClassInfo_Struct itemDataClassInfo_Struct;
ItemDataClassInfo itemDataClassInfo = &itemDataClassInfo_Struct;

struct ItemClassInfo_Struct itemClassInfo_Struct;
ItemClassInfo itemClassInfo = &itemClassInfo_Struct;

struct SymbolClassInfo_Struct symbolClassInfo_Struct;
SymbolClassInfo symbolClassInfo = &symbolClassInfo_Struct;


struct StructureClassInfo_Struct structureClassInfo_Struct;
StructureClassInfo structureClassInfo = &structureClassInfo_Struct;


struct ObjectClassInfo_Struct objectClassInfo_Struct;
ObjectClassInfo objectClassInfo = &objectClassInfo_Struct;

struct NumberClassInfo_Struct numberClassInfo_Struct;
NumberClassInfo numberClassInfo = &numberClassInfo_Struct;


struct IntegerClassInfo_Struct integerClassInfo_Struct;
IntegerClassInfo integerClassInfo = &integerClassInfo_Struct;

struct LongClassInfo_Struct longClassInfo_Struct;
LongClassInfo longClassInfo = &longClassInfo_Struct;

struct ShortClassInfo_Struct shortClassInfo_Struct;
ShortClassInfo shortClassInfo = &shortClassInfo_Struct;

struct ByteClassInfo_Struct byteClassInfo_Struct;
ByteClassInfo byteClassInfo = &byteClassInfo_Struct;

struct CharacterClassInfo_Struct CharacterClassInfo_Struct;
CharacterClassInfo characterClassInfo = &CharacterClassInfo_Struct;

struct DoubleClassInfo_Struct doubleClassInfo_Struct;
DoubleClassInfo doubleClassInfo = &doubleClassInfo_Struct;

struct FloatClassInfo_Struct floatClassInfo_Struct;
FloatClassInfo floatClassInfo = &floatClassInfo_Struct;

struct BooleanClassInfo_Struct booleanClassInfo_Struct;
BooleanClassInfo booleanClassInfo = &booleanClassInfo_Struct;


struct StringClassInfo_Struct stringClassInfo_Struct;
StringClassInfo stringClassInfo = &stringClassInfo_Struct;

struct EnumerationClassInfo_Struct enumerationClassInfo_Struct;
EnumerationClassInfo enumerationClassInfo = &enumerationClassInfo_Struct;

struct ThrowableClassInfo_Struct throwableClassInfo_Struct;
ThrowableClassInfo throwableClassInfo = &throwableClassInfo_Struct;

struct DebugUtilClassInfo_Struct debugUtilClassInfo_Struct;
DebugUtilClassInfo debugUtilClassInfo = &debugUtilClassInfo_Struct;

struct G2CommunicationExceptionClassInfo_Struct g2CommunicationExceptionClassInfo_Struct;
G2CommunicationExceptionClassInfo g2CommunicationExceptionClassInfo 
                 = &g2CommunicationExceptionClassInfo_Struct;

struct VectorClassInfo_Struct vectorClassInfo_Struct;
VectorClassInfo vectorClassInfo = &vectorClassInfo_Struct;

struct PropertyClassInfo_Struct propertyClassInfo_Struct;
PropertyClassInfo propertyClassInfo = &propertyClassInfo_Struct;



jobject nameSymbol;
jobject namesSymbol;
jobject noneSymbol;
jobject emptySymbol;
jobject classSymbol;
jobject valueSymbol;
jobject itemSymbol;
jobject integerSymbol;
jobject truthValueSymbol;
jobject symbolSymbol;
jobject textSymbol;
jobject floatSymbol;
jobject valueSymbol;
jobject itemOrValueSymbol;
jobject quantitySymbol;
jobject hiddenG2ArraySymbol;
jobject elementTypeSymbol;
jobject lastRecordedValueSymbol;
jobject g2ListSequenceSymbol;
jobject G2JavaShortClassSymbol;
jobject G2JavaByteClassSymbol;
jobject G2JavaLongClassSymbol;
jobject G2JavaCharClassSymbol;
jobject G2JavaIntClassSymbol;
jobject G2JavaFloatClassSymbol;
jobject G2JavaIntTypeArrayClassSymbol;
jobject G2JavaBooleanTypeArrayClassSymbol;
jobject G2JavaSymbolArrayClassSymbol;
jobject G2JavaStringArrayClassSymbol;
jobject G2JavaDoubleTypeArrayClassSymbol;
jobject G2JavaNumberArrayClassSymbol;
jobject G2JavaObjectArrayClassSymbol;

ContextData *contextDataLookup;
int contextDataLookup_Size = -1;

gsi_char *null_str;
gsi_char *none_str;
gsi_char *empty_str;
gsi_char *window_str;
gsi_char *popup_str;
gsi_char *g2_floatarray_classname;
gsi_char *g2_g2array_classname;
gsi_char *g2_integerarray_classname;
gsi_char *g2_itemarray_classname;
gsi_char *g2_quantityarray_classname;
gsi_char *g2_sequencearray_classname;
gsi_char *g2_structurearray_classname;
gsi_char *g2_symbolarray_classname;
gsi_char *g2_textarray_classname;
gsi_char *g2_truthvaluearray_classname;
gsi_char *g2_valuearray_classname;
gsi_char *g2_javaproxy_classname_attr;
gsi_char *g2_javatype_class_val_attr;
gsi_char *g2_javashort_classname;
gsi_char *g2_javabyte_classname;
gsi_char *g2_javalong_classname;
gsi_char *g2_javachar_classname;
gsi_char *g2_javaint_classname;
gsi_char *g2_javafloat_classname;
gsi_char *g2_raw_java_inttypearray_classname;
gsi_char *g2_raw_java_booleantypearray_classname;
gsi_char *g2_raw_java_symbolarray_classname;
gsi_char *g2_raw_java_stringarray_classname;
gsi_char *g2_raw_java_doubletypearray_classname;
gsi_char *g2_raw_java_numberarray_classname;
gsi_char *g2_raw_java_objectarray_classname;
gsi_symbol window_gsisymbol;
gsi_symbol popup_gsisymbol;
gsi_symbol g2_floatarray_classname_gsisymbol;   
gsi_symbol g2_g2array_classname_gsisymbol;       
gsi_symbol g2_integerarray_classname_gsisymbol;
gsi_symbol g2_itemarray_classname_gsisymbol;    
gsi_symbol g2_quantityarray_classname_gsisymbol; 
gsi_symbol g2_sequencearray_classname_gsisymbol; 
gsi_symbol g2_structurearray_classname_gsisymbol;
gsi_symbol g2_symbolarray_classname_gsisymbol;   
gsi_symbol g2_textarray_classname_gsisymbol;    
gsi_symbol g2_truthvaluearray_classname_gsisymbol;
gsi_symbol g2_valuearray_classname_gsisymbol;    
gsi_symbol g2_javaproxy_classname_attr_gsisymbol;
gsi_symbol g2_javatype_class_val_attr_gsisymbol;
gsi_symbol g2_javalong_classname_gsisymbol;
gsi_symbol g2_javashort_classname_gsisymbol;
gsi_symbol g2_javabyte_classname_gsisymbol;
gsi_symbol g2_javachar_classname_gsisymbol;
gsi_symbol g2_javafloat_classname_gsisymbol;



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - JAVA CLASS INFO LOOKUP FUNCTIONS
 %
 % Description:
 %   
 %		Functions to pre lookup Java classes, methods and fields using JNI
 %   
 % Notes:
 %   
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/





/* load pre lookup class information*/
void construct_pre_lookup_class_information( JNIEnv *env, jobject jgi_interface, jobject gsi_interface) {
  jfieldID fieldid;

  if (fundebug) {printf("Function construct_pre_lookup_class_information \n"); fflush(stdout);}



        /*Throwable*/

        if (fulldebug) printf("Loading Throwable class info \n");

        throwableClassInfo->generalclazz = 
	  (*env)->FindClass (env, "java/lang/Throwable");

	if (!throwableClassInfo->generalclazz)
	  (*env)->FatalError(env, "Could not Find Throwable Class !");

	throwableClassInfo->generalclazz = 
	  (*env)->NewGlobalRef(env,throwableClassInfo->generalclazz);

	if (fulldebug) printf("throwableClassInfo->generalclazz is %lx \n", throwableClassInfo->generalclazz);

	throwableClassInfo->toString_MethodID =
	   (*env)->GetMethodID(env,
			       throwableClassInfo->generalclazz, 
			       "toString",
			       "()Ljava/lang/String;");
	if (fulldebug) 
	  printf ("throwableClassInfo->toString_MethodID = %lx\n", throwableClassInfo->toString_MethodID);

	 PRINT_EXCEPTION(env);

	 /* DebugUtil*/

	 debugUtilClassInfo->clazz =
	      (*env)->FindClass (env, "com/gensym/core/DebugUtil");

	 if (!debugUtilClassInfo->clazz)
	   (*env)->FatalError(env, "Could not Find DebugUtil Class !");

	 debugUtilClassInfo->clazz =
	   (*env)->NewGlobalRef(env, debugUtilClassInfo->clazz);

	 if (fulldebug)
           printf("debugUtilClassInfo->clazz is %lx \n",
		  debugUtilClassInfo->clazz);

	 debugUtilClassInfo->getStackTrace_MethodID =
	   (*env)->GetStaticMethodID(env,
				     debugUtilClassInfo->clazz,
				     "getStackTrace",
				     "(Ljava/lang/Throwable;)Ljava/lang/String;");
	 if (fulldebug)
	   printf ("debugUtilClassInfo->getStackTrace_MethodID = %lx\n",
		   debugUtilClassInfo->getStackTrace_MethodID);
	 
	 PRINT_EXCEPTION(env);

        /*G2CommunicationException*/

        if (fulldebug) printf("Loading G2CommunicationException class info \n");

        g2CommunicationExceptionClassInfo->clazz = 
	  (*env)->FindClass (env, "com/gensym/jgi/G2CommunicationException");

	if (!g2CommunicationExceptionClassInfo->clazz)
	  (*env)->FatalError(env, "Could not Find G2CommunicationException Class !");

	g2CommunicationExceptionClassInfo->clazz = 
	  (*env)->NewGlobalRef(env,g2CommunicationExceptionClassInfo->clazz);

	if (fulldebug) printf("G2CommunicationExceptionClassInfo->clazz is %lx \n", 
			      g2CommunicationExceptionClassInfo->clazz);

	g2CommunicationExceptionClassInfo->toString_MethodID =
	   (*env)->GetMethodID(env,
			       g2CommunicationExceptionClassInfo->clazz, 
			       "toString",
			       "()Ljava/lang/String;");
	if (fulldebug) 
	  printf ("g2CommunicationExceptionClassInfo->toString_MethodID = %lx\n", g2CommunicationExceptionClassInfo->toString_MethodID);

	 PRINT_EXCEPTION(env);



       /* JGInterface*/

        if (fulldebug) printf("Loading JGInterface class info \n");

        registeredJGInterface->clazz = 
	  (*env)->FindClass (env, "com/gensym/jgi/JGInterface");

	if (!registeredJGInterface->clazz)
	  (*env)->FatalError(env, "Could not Find JGInterface Class !");

	registeredJGInterface->clazz = 
	  (*env)->NewGlobalRef(env,registeredJGInterface->clazz);

	if (fulldebug) printf("registeredJGInterface->clazz is %lx \n", registeredJGInterface->clazz);
	/* jgi_describeJavaObject (env, registeredJGInterface->clazz); */
	/* jgi_describeJavaObject (env,jgi_interface); */

        /* We want to refer to the JGInterface outside this function
           so we have to create a global reference to it             */
        JREF(registeredJGInterface) = (*env)->NewGlobalRef(env, jgi_interface);

        registeredJGInterface->G2InitializeConnection_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "G2InitializeConnection",	       
			       "(Lcom/gensym/jgi/G2Connection;ILjava/lang/String;)V");
	if (fulldebug)
	  printf ("registeredJGInterface->G2InitializeConnection_MethodID = %lx\n",
		  registeredJGInterface->G2InitializeConnection_MethodID);

	 PRINT_EXCEPTION(env);

        registeredJGInterface->registerIncomingConnection_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "registerIncomingConnection",
			       "(ILjava/lang/String;Ljava/lang/String;)V");
	if (fulldebug)
	  printf ("registeredJGInterface->registerIncomingConnection_MethodID = %lx\n",
		  registeredJGInterface->registerIncomingConnection_MethodID);

	 PRINT_EXCEPTION(env);

	 registeredJGInterface->G2isPaused_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "G2isPaused",
			       "(Lcom/gensym/jgi/G2Connection;I)V");
	 if (fulldebug)
	  printf ("registeredJGInterface->G2isPaused_MethodID = %lx\n",
		  registeredJGInterface->G2isPaused_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->G2isResumed_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "G2isResumed",
			       "(Lcom/gensym/jgi/G2Connection;I)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->G2isResumed_MethodID = %lx\n",
		  registeredJGInterface->G2isResumed_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->G2isReset_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "G2isReset",
			       "(Lcom/gensym/jgi/G2Connection;I)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->G2isReset_MethodID = %lx\n",
		   registeredJGInterface->G2isReset_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->G2isStarted_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "G2isStarted",
			       "(Lcom/gensym/jgi/G2Connection;I)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->G2isStarted_MethodID = %lx\n",
		   registeredJGInterface->G2isStarted_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->G2ConnectionClosed_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "G2ConnectionClosed",
			       "(Lcom/gensym/jgi/G2Connection;I)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->G2ConnectionClosed_MethodID = %lx\n",
		   registeredJGInterface->G2ConnectionClosed_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->receiveMessage_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "receiveMessage",
			       "(Lcom/gensym/jgi/G2Connection;ILjava/lang/String;)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->receiveMessage_MethodID = %lx\n",
		   registeredJGInterface->receiveMessage_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->writeCallback_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "writeCallback",
			       "(Lcom/gensym/jgi/G2Connection;IZ)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->writeCallback_MethodID = %lx\n",
		   registeredJGInterface->writeCallback_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->readCallback_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "readCallback",
			       "(Lcom/gensym/jgi/G2Connection;IZ)V");

	 if (fulldebug)
	   printf ("registeredJGInterface->readCallback_MethodID = %lx\n",
		   registeredJGInterface->readCallback_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->setData_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "setData",
			       "(Lcom/gensym/jgi/G2Connection;I[Lcom/gensym/classes/Item;Z)V");

	 if (fulldebug)
	   printf ("registeredJGInterface->setDate_MethodID = %lx\n",
		   registeredJGInterface->setData_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->getData_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "getData",
			       "(Lcom/gensym/jgi/G2Connection;I[Lcom/gensym/classes/Item;Z)V");

	 if (fulldebug)
	   printf ("registeredJGInterface->getData_MethodID = %lx\n",
		   registeredJGInterface->getData_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->receiveRegistration_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "receiveRegistration",
			       "(Lcom/gensym/jgi/G2Connection;ILcom/gensym/classes/Item;[Ljava/lang/Object;Z)V");

	 if (fulldebug)
	   printf ("registeredJGInterface->getData_MethodID = %lx\n",
		   registeredJGInterface->getData_MethodID);
	 PRINT_EXCEPTION(env);


	 registeredJGInterface->invokeMethod_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "invokeMethod",
			       "(Lcom/gensym/jgi/G2Connection;Lcom/gensym/util/Symbol;Z[Ljava/lang/Object;[Ljava/lang/Class;JZI)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->invokeMethod_MethodID = %lx\n",
		   registeredJGInterface->invokeMethod_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->invokeMethodObject_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "invokeMethod",
			       "(Ljava/lang/Object;Ljava/lang/reflect/Method;[Ljava/lang/Object;JZZZZI)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->invokeMethodObject_MethodID = %lx\n",
		   registeredJGInterface->invokeMethodObject_MethodID);
	 PRINT_EXCEPTION(env);


	 registeredJGInterface->communicationError_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "communicationError",
			       "(IILjava/lang/String;Ljava/lang/String;)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->communicationError_MethodID = %lx\n",
		   registeredJGInterface->communicationError_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->getG2ItemInfo_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "getG2ItemInfo",
			       "(Lcom/gensym/classes/ImplAccess;)Lcom/gensym/util/Structure;");
	 if (fulldebug)
	   printf ("registeredJGInterface->getG2ItemInfo_MethodID = %lx\n",
		   registeredJGInterface->getG2ItemInfo_MethodID);
	 PRINT_EXCEPTION(env);

	 registeredJGInterface->setCurrentContext_MethodID =
	   (*env)->GetMethodID(env,
			       registeredJGInterface->clazz, 
			       "setCurrentContext",
			       "(I)V");
	 if (fulldebug)
	   printf ("registeredJGInterface->setCurrentContext_MethodID = %lx\n",
		   registeredJGInterface->setCurrentContext_MethodID);
	 PRINT_EXCEPTION(env);

	 /* Class*/

	if (fulldebug) printf("Loading Class class info \n");

	 classClassInfo->clazz = 
	   (*env)->FindClass (env, "java/lang/Class");
 
	 if (!classClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find java/lang/Class");
	 PRINT_EXCEPTION(env);

	 classClassInfo->clazz = 
	   (*env)->NewGlobalRef(env,classClassInfo->clazz); 

	 if (fulldebug) printf("classClassInfo->clazz is %lx \n", classClassInfo->clazz );

	 classClassInfo->getName_MethodID =
	   (*env)->GetMethodID(env,
			       classClassInfo->clazz, 
			       "getName",
			       "()Ljava/lang/String;");
	 if (fulldebug)
	   printf ("classClassInfo->getName_MethodID = %lx\n",
		   classClassInfo->getName_MethodID);
	 PRINT_EXCEPTION(env);
	 
	 
	 /*end of Class*/



	/*Sequence*/

	if (fulldebug) printf("Loading Sequence class info \n");

	 sequenceClassInfo->clazz = 
	   (*env)->FindClass (env, "com/gensym/util/Sequence");
 
	 if (!sequenceClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/util/Sequence");
	 PRINT_EXCEPTION(env);

	 sequenceClassInfo->clazz = 
	   (*env)->NewGlobalRef(env,sequenceClassInfo->clazz); 

	 if (fulldebug) printf("sequenceClassInfo->clazz is %lx \n",  sequenceClassInfo->clazz );

	 sequenceClassInfo->init_MethodID =
	   (*env)->GetMethodID(env,
			       sequenceClassInfo->clazz, 
			       "<init>",
			       "(I)V");
	 if (fulldebug)
	   printf ("sequenceClassInfo->init_MethodID = %lx\n",
		   sequenceClassInfo->init_MethodID);
	 PRINT_EXCEPTION(env);
	 

	 sequenceClassInfo->size_MethodID=
	   (*env)->GetMethodID(env,
			      sequenceClassInfo->clazz, 
			      "size",
			      "()I");

	 PRINT_EXCEPTION(env);

	 sequenceClassInfo->print_MethodID=
	   (*env)->GetMethodID(env,
			      sequenceClassInfo->clazz, 
			      "print",
			      "()Ljava/lang/String;");

	 PRINT_EXCEPTION(env);
	 
	 sequenceClassInfo->elementData_FieldID=
	   (*env)->GetFieldID(env,
			      sequenceClassInfo->clazz, 
			      "elementData",
			      "[Ljava/lang/Object;");

	 PRINT_EXCEPTION(env);

	 sequenceClassInfo->elementCount_FieldID=
	   (*env)->GetFieldID(env,
			      sequenceClassInfo->clazz, 
			      "elementCount",
			      "I");

	 PRINT_EXCEPTION(env);


	 

	 
	 /*end of sequence*/



	 /* ItemImpl*/


	itemImplClassInfo->clazz = 
	  (*env)->FindClass (env, "com/gensym/classes/G2__BaseImpl");
	 if (!itemImplClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/classes/ItemImpl");
	 PRINT_EXCEPTION(env);

	itemImplClassInfo->clazz = (*env)->NewGlobalRef(env, itemImplClassInfo->clazz);

	if (fulldebug)
	  printf("itemImplClassInfo->clazz is %lx \n",  itemImplClassInfo->clazz);

	itemImplClassInfo->handle_FieldID =
	  (*env)->GetFieldID(env,
			     itemImplClassInfo->clazz, 
			     "handle",
			     "I");
	if (fulldebug)
	  printf ("itemImplClassInfo->handle_FieldID = %lx\n",
		 itemImplClassInfo->handle_FieldID);
	PRINT_EXCEPTION(env);

	itemImplClassInfo->data_FieldID = 
	  (*env)->GetFieldID(env,
			     itemImplClassInfo->clazz, 
			     "data",
			     "Lcom/gensym/classes/ItemData;");
	if (fulldebug)
	  printf ("itemImplClassInfo->data_FieldID = %lx\n",
		  itemImplClassInfo->data_FieldID);
	PRINT_EXCEPTION(env);

	itemDataClassInfo->clazz =
	  (*env)->FindClass (env, "com/gensym/classes/ItemData");
	if (!itemDataClassInfo->clazz)
	  THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/classes/ItemData");
	PRINT_EXCEPTION(env);

	itemDataClassInfo->clazz = (*env)->NewGlobalRef(env, itemDataClassInfo->clazz);
	
	itemDataClassInfo->itemIsValid_FieldID = 
	  (*env)->GetFieldID(env,
			     itemDataClassInfo->clazz,
			     "itemIsValid",
			     "Z");
	if (fulldebug)
	  printf ("itemDataClassInfo->itemIsValid_FieldID = %lx\n",
		  itemDataClassInfo->itemIsValid_FieldID);
	PRINT_EXCEPTION(env);

	itemClassInfo->clazz = 
	  (*env)->FindClass (env, "com/gensym/classes/Item");
	PRINT_EXCEPTION(env);

	itemClassInfo->clazz = (*env)->NewGlobalRef(env, itemClassInfo->clazz);

	/* Symbol*/


	if (fulldebug) printf("Loading Symbol class info \n");

	symbolClassInfo->clazz   = 
		 (*env)->FindClass (env, "com/gensym/util/Symbol");

	if (!symbolClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/util/Symbol");


	PRINT_EXCEPTION(env);

	symbolClassInfo->clazz = (*env)->NewGlobalRef(env, symbolClassInfo->clazz );

	if (fulldebug) printf("Loading Symbol[] class info \n");

	symbolClassInfo->symbolArray_clazz   = 
		 (*env)->FindClass (env, "[Lcom/gensym/util/Symbol;");

	if (!symbolClassInfo->symbolArray_clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/util/Symbol[]");


	PRINT_EXCEPTION(env);

	symbolClassInfo->symbolArray_clazz = 
	  (*env)->NewGlobalRef(env, symbolClassInfo->symbolArray_clazz );

	symbolClassInfo->intern_MethodID=
		(*env)->GetStaticMethodID(env,
				  symbolClassInfo->clazz, 
				  "intern",
				  "(Ljava/lang/String;)Lcom/gensym/util/Symbol;");

	PRINT_EXCEPTION(env);


	symbolClassInfo->getPrintValue_MethodID=
		(*env)->GetMethodID(env,
				  symbolClassInfo->clazz, 
				  "getPrintValue",
				  "()Ljava/lang/String;");

	PRINT_EXCEPTION(env);

	symbolClassInfo->equals_MethodID=
	   (*env)->GetMethodID(env,
			       symbolClassInfo->clazz, 
			       "equals",
			       "(Ljava/lang/Object;)Z");

	PRINT_EXCEPTION(env);


	/* end of symbol*/


	/* Structure*/

	if (fulldebug) printf("Loading Structure class info \n");

	structureClassInfo->clazz = 
		(*env)->FindClass( env, "com/gensym/util/Structure");

	if (!structureClassInfo->clazz)
	  THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/util/Structure");

	PRINT_EXCEPTION(env);

	structureClassInfo->clazz = (*env)->NewGlobalRef(env, structureClassInfo->clazz );

	structureClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  structureClassInfo->clazz, 
			  "<init>",
			  "([Lcom/gensym/util/Symbol;[Ljava/lang/Object;I)V");
	PRINT_EXCEPTION(env);

	/* The next two are not used. Consider removing them -vkp, 3/6/98*/
	structureClassInfo->getAttributeNames_MethodID=
		(*env)->GetMethodID(env,
				 structureClassInfo->clazz, 
				 "getAttributeNames",
				 "()Ljava/util/Enumeration;");

	PRINT_EXCEPTION(env);

							 	
	structureClassInfo->getAttributeValues_MethodID=
		(*env)->GetMethodID(env,
				 structureClassInfo->clazz, 
				 "getAttributeNames",
				 "()Ljava/util/Enumeration;");

	PRINT_EXCEPTION(env);


	structureClassInfo->getAttributeCount_MethodID=
		(*env)->GetMethodID(env,
				 structureClassInfo->clazz, 
				 "getAttributeCount",
				 "()I"); 

	PRINT_EXCEPTION(env);

	structureClassInfo->getAttributes_MethodID=
		(*env)->GetMethodID(env,
				 structureClassInfo->clazz, 
				 "getAttributes",
				 "()Ljava/util/Vector;"); 

	PRINT_EXCEPTION(env);



	/* end of structure*/



	 /*Object*/

	if (fulldebug) printf("Loading Object class info \n");

	objectClassInfo->clazz   = 
		(*env)->FindClass (env, "java/lang/Object");

	if (!objectClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find  java/lang/Object");
	
	PRINT_EXCEPTION(env);

	objectClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, objectClassInfo->clazz );

	
	if (fulldebug) printf("Loading Object[] class info \n");

	objectClassInfo->objectArray_clazz   = 
		(*env)->FindClass (env, "[Ljava/lang/Object;");

	if (!objectClassInfo->objectArray_clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find [java/lang/Object (Object[])");

	PRINT_EXCEPTION(env);

	objectClassInfo->objectArray_clazz = 
	  (*env)->NewGlobalRef(env, objectClassInfo->objectArray_clazz );
	
	 /* end of object*/

	/*Number*/

	if (fulldebug) printf("Loading Number class info \n");

	numberClassInfo->clazz   = 
		(*env)->FindClass (env, "java/lang/Number");

	if (!numberClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find  java/lang/Number");

	PRINT_EXCEPTION(env);

	numberClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, numberClassInfo->clazz );

	
	if (fulldebug) printf("Loading Number[] class info \n");

	numberClassInfo->numberArray_clazz   = 
		(*env)->FindClass (env, "[Ljava/lang/Number;");

	if (!numberClassInfo->numberArray_clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find  java/lang/Number[]");


	PRINT_EXCEPTION(env);

	numberClassInfo->numberArray_clazz = 
	  (*env)->NewGlobalRef(env, numberClassInfo->numberArray_clazz );
	
	/* end of Number*/


	/* Integer*/

	if (fulldebug) printf("Loading Integer class info \n");

	integerClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Integer");

	PRINT_EXCEPTION(env);

	integerClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, integerClassInfo->clazz ); 

	fieldid = (*env)->GetStaticFieldID(env, 
					   integerClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	integerClassInfo->intType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       integerClassInfo->clazz, 
					       fieldid);


	PRINT_EXCEPTION(env);

	integerClassInfo->intType_clazz = 
	  (*env)->NewGlobalRef(env, integerClassInfo->intType_clazz ); 


	if (fulldebug) printf("Loading int[] class info \n");

	integerClassInfo->intTypeArray_clazz  = 
	  (*env)->FindClass (env, "[I");  /* int[] NOT Integer[]*/


	PRINT_EXCEPTION(env);

	integerClassInfo->intTypeArray_clazz = 
	  (*env)->NewGlobalRef(env, integerClassInfo->intTypeArray_clazz );

  	integerClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  integerClassInfo->clazz, 
			  "<init>",
			  "(I)V");

	PRINT_EXCEPTION(env);

	integerClassInfo->intValue_MethodID=
		(*env)->GetMethodID(env,
			  integerClassInfo->clazz, 
			  "intValue",
			  "()I");

	PRINT_EXCEPTION(env);

	integerClassInfo->parseInt_MethodID=
	  (*env)->GetStaticMethodID(env,
			      integerClassInfo->clazz, 
			      "parseInt",
			      "(Ljava/lang/String;)I");

	PRINT_EXCEPTION(env);

	/* end of Integer*/

	/* long*/

	if (fulldebug) printf("Loading long class info \n");

	longClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Long");

	PRINT_EXCEPTION(env);

	longClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, longClassInfo->clazz ); 

	fieldid = (*env)->GetStaticFieldID(env, 
					   longClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	longClassInfo->longType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       longClassInfo->clazz, 
					       fieldid);


	PRINT_EXCEPTION(env);

	longClassInfo->longType_clazz = 
	  (*env)->NewGlobalRef(env, longClassInfo->longType_clazz ); 

  	longClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  longClassInfo->clazz, 
			  "<init>",
			  "(J)V");

	PRINT_EXCEPTION(env);

	longClassInfo->intValue_MethodID=
		(*env)->GetMethodID(env,
			  longClassInfo->clazz, 
			  "intValue",
			  "()I");

	PRINT_EXCEPTION(env);

	longClassInfo->parseLong_MethodID=
	        (*env)->GetStaticMethodID(env,
				    longClassInfo->clazz,
				    "parseLong",
				    "(Ljava/lang/String;)J");

	PRINT_EXCEPTION(env);

	longClassInfo->toString_MethodID=
	  (*env)->GetMethodID(env,
			      longClassInfo->clazz,
			      "toString",
			      "()Ljava/lang/String;");

	PRINT_EXCEPTION(env)

	/* end of Long*/


	/* Byte*/

	if (fulldebug) printf("Loading  Byte class info \n");

	byteClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Byte");

	PRINT_EXCEPTION(env);

	byteClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, byteClassInfo->clazz ); 

	fieldid = (*env)->GetStaticFieldID(env, 
					   byteClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	byteClassInfo->byteType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       byteClassInfo->clazz, 
					       fieldid);


	PRINT_EXCEPTION(env);

	byteClassInfo->byteType_clazz = 
	  (*env)->NewGlobalRef(env, byteClassInfo->byteType_clazz ); 

  	byteClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  byteClassInfo->clazz, 
			  "<init>",
			  "(B)V");

	PRINT_EXCEPTION(env);

	byteClassInfo->intValue_MethodID=
		(*env)->GetMethodID(env,
			  byteClassInfo->clazz, 
			  "intValue",
			  "()I");

	PRINT_EXCEPTION(env);


	/* end of Byte*/

	/* Short*/

	if (fulldebug) printf("Loading Short class info \n");

	shortClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Short");

	PRINT_EXCEPTION(env);

	shortClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, shortClassInfo->clazz ); 

	fieldid = (*env)->GetStaticFieldID(env, 
					   shortClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	shortClassInfo->shortType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       shortClassInfo->clazz, 
					       fieldid);


	PRINT_EXCEPTION(env);

	shortClassInfo->shortType_clazz = 
	  (*env)->NewGlobalRef(env, shortClassInfo->shortType_clazz ); 

  	shortClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  shortClassInfo->clazz, 
			  "<init>",
			  "(S)V");

	PRINT_EXCEPTION(env);

	shortClassInfo->intValue_MethodID=
		(*env)->GetMethodID(env,
			  shortClassInfo->clazz, 
			  "intValue",
			  "()I");

	PRINT_EXCEPTION(env);


	/* end of Short*/

	/* Character*/

	if (fulldebug) printf("Loading Character class info \n");

	characterClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Character");

	PRINT_EXCEPTION(env);

	characterClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, characterClassInfo->clazz ); 

	fieldid = (*env)->GetStaticFieldID(env, 
					   characterClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	characterClassInfo->characterType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       characterClassInfo->clazz, 
					       fieldid);


	PRINT_EXCEPTION(env);

	characterClassInfo->characterType_clazz = 
	  (*env)->NewGlobalRef(env, characterClassInfo->characterType_clazz ); 


  	characterClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  characterClassInfo->clazz, 
			  "<init>",
			  "(C)V");

	PRINT_EXCEPTION(env);

	characterClassInfo->charValue_MethodID=
		(*env)->GetMethodID(env,
			  characterClassInfo->clazz, 
			  "charValue",
			  "()C");

	PRINT_EXCEPTION(env);

	if (fulldebug) printf("Loading char[] class info \n");

	characterClassInfo->characterTypeArray_clazz  = 
		(*env)->FindClass (env, "[C");


	PRINT_EXCEPTION(env);

	characterClassInfo->characterTypeArray_clazz  = 
	  (*env)->NewGlobalRef(env, characterClassInfo->characterTypeArray_clazz );


	/* end of Character*/

	/* Boolean*/

	if (fulldebug) printf("Loading Boolean class info \n");

	booleanClassInfo->clazz  = 
		(*env)->FindClass (env, "java/lang/Boolean");


	PRINT_EXCEPTION(env);

	booleanClassInfo->clazz  = (*env)->NewGlobalRef(env, booleanClassInfo->clazz );

	fieldid = (*env)->GetStaticFieldID(env, 
					   booleanClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	booleanClassInfo->booleanType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       booleanClassInfo->clazz, 
					       fieldid);



	PRINT_EXCEPTION(env);

	booleanClassInfo->booleanType_clazz  = 
	  (*env)->NewGlobalRef(env, 
			       booleanClassInfo->booleanType_clazz );


	if (fulldebug) printf("Loading boolean[] class info \n");

	booleanClassInfo->booleanTypeArray_clazz  = 
		(*env)->FindClass (env, "[Z");


	PRINT_EXCEPTION(env);

	booleanClassInfo->booleanTypeArray_clazz  = 
	  (*env)->NewGlobalRef(env, booleanClassInfo->booleanTypeArray_clazz );
	

  	booleanClassInfo->init_MethodID=
		(*env)->GetMethodID(env,
			  booleanClassInfo->clazz, 
			  "<init>",
			  "(Z)V");

	PRINT_EXCEPTION(env);


	booleanClassInfo->booleanValue_MethodID=
		(*env)->GetMethodID(env,
			  booleanClassInfo->clazz, 
			  "booleanValue",
			  "()Z");

	PRINT_EXCEPTION(env);


	booleanClassInfo->Boolean_TRUE = 
	         (*env)->NewObject(env , 
				   booleanClassInfo->clazz, 
				   booleanClassInfo->init_MethodID, 
				   JNI_TRUE );

	booleanClassInfo->Boolean_TRUE = (*env)->NewGlobalRef(env, booleanClassInfo->Boolean_TRUE );

	booleanClassInfo->Boolean_FALSE = 
	         (*env)->NewObject(env , 
				   booleanClassInfo->clazz, 
				   booleanClassInfo->init_MethodID, 
				   JNI_FALSE );

	booleanClassInfo->Boolean_FALSE = (*env)->NewGlobalRef(env, booleanClassInfo->Boolean_FALSE );

	/* end of boolean*/



	/* Double*/

	if (fulldebug) printf("Loading Double class info \n");

	doubleClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Double");


	PRINT_EXCEPTION(env);

	doubleClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, doubleClassInfo->clazz );


	fieldid = (*env)->GetStaticFieldID(env, 
					   doubleClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	doubleClassInfo->doubleType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       doubleClassInfo->clazz, 
					       fieldid);


	PRINT_EXCEPTION(env);

	doubleClassInfo->doubleType_clazz = 
	  (*env)->NewGlobalRef(env, doubleClassInfo->doubleType_clazz );

	if (fulldebug) printf("Loading double[] class info \n");

	doubleClassInfo->doubleTypeArray_clazz  = 
	  (*env)->FindClass (env, "[D");   /* The double[] NOT Double[]*/


	PRINT_EXCEPTION(env);

	doubleClassInfo->doubleTypeArray_clazz = 
	  (*env)->NewGlobalRef(env, doubleClassInfo->doubleTypeArray_clazz );

  	doubleClassInfo->init_MethodID=
			(*env)->GetMethodID(env,
			  doubleClassInfo->clazz, 
			  "<init>",
			  "(D)V");

	PRINT_EXCEPTION(env);


	doubleClassInfo->doubleValue_MethodID=
		(*env)->GetMethodID(env,
			  doubleClassInfo->clazz, 
			  "doubleValue",
			  "()D");

	PRINT_EXCEPTION(env);


	/* end of double*/

	/* Float*/

	if (fulldebug) printf("Loading Float class info \n");

	floatClassInfo->clazz  = 
		  (*env)->FindClass (env, "java/lang/Float");


	PRINT_EXCEPTION(env);

	floatClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, floatClassInfo->clazz );

	fieldid = (*env)->GetStaticFieldID(env, 
					   floatClassInfo->clazz, 
					   "TYPE", 
					   "Ljava/lang/Class;");

	floatClassInfo->floatType_clazz  = 
		  (*env)->GetStaticObjectField(env, 
					       floatClassInfo->clazz, 
					       fieldid);

	PRINT_EXCEPTION(env);

	floatClassInfo->floatType_clazz = 
	  (*env)->NewGlobalRef(env, floatClassInfo->floatType_clazz );


	PRINT_EXCEPTION(env);

  	floatClassInfo->initd_MethodID=
			(*env)->GetMethodID(env,
			  floatClassInfo->clazz, 
			  "<init>",
			  "(D)V");

	PRINT_EXCEPTION(env);


  	floatClassInfo->init_MethodID=
			(*env)->GetMethodID(env,
			  floatClassInfo->clazz, 
			  "<init>",
			  "(F)V");

	PRINT_EXCEPTION(env);


	floatClassInfo->doubleValue_MethodID=
		(*env)->GetMethodID(env,
			  floatClassInfo->clazz, 
			  "doubleValue",
			  "()D");

	PRINT_EXCEPTION(env);


	/* end of Float*/



	/* String*/

	if (fulldebug) printf("Loading String class info \n");

	stringClassInfo->clazz  = 
		(*env)->FindClass (env, "java/lang/String");


	PRINT_EXCEPTION(env);

	stringClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, stringClassInfo->clazz );

	if (fulldebug) printf("Loading String[] class info \n");

	stringClassInfo->stringArray_clazz  = 
		(*env)->FindClass (env, "[Ljava/lang/String;");

	if (!stringClassInfo->stringArray_clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find [java/lang/String (String[])");

	PRINT_EXCEPTION(env);

	stringClassInfo->stringArray_clazz = 
	  (*env)->NewGlobalRef(env, stringClassInfo->stringArray_clazz );

	/* end of string*/


	/* Enumeration*/

	if (fulldebug) printf("Loading Enumeration class info \n");

	enumerationClassInfo->clazz  = 
		(*env)->FindClass (env, "java/util/Enumeration");

	PRINT_EXCEPTION(env);

	enumerationClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, enumerationClassInfo->clazz );

   	enumerationClassInfo->nextElement_MethodID=
		(*env)->GetMethodID(env,
			  enumerationClassInfo->clazz, 
			  "nextElement",
			  "()Ljava/lang/Object;");

	PRINT_EXCEPTION(env);


	/* end of enumeration*/


	/* Vector*/
	if (fulldebug) printf("Loading Vector class info \n");

	 vectorClassInfo->clazz = 
	   (*env)->FindClass (env, "java/util/Vector");
 	 if (!vectorClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find java/util/Vector");
	 PRINT_EXCEPTION(env);

	  vectorClassInfo->clazz = 
	   (*env)->NewGlobalRef(env,vectorClassInfo->clazz); 

	 if (fulldebug) printf("vectorClassInfo->clazz is %lx \n",  vectorClassInfo->clazz );

	 vectorClassInfo->init_MethodID =
	   (*env)->GetMethodID(env,
			       vectorClassInfo->clazz, 
			       "<init>",
			       "(I)V");

	 if (!vectorClassInfo->init_MethodID)
	   {
	     THROW_GENERAL_EXCEPTION(env, "Cant Find Vector init  method");
	     PRINT_EXCEPTION(env);
	   }

	 vectorClassInfo->size_MethodID=
	   (*env)->GetMethodID(env,
			      vectorClassInfo->clazz, 
			      "size",
			      "()I");

	 PRINT_EXCEPTION(env);

	 vectorClassInfo->addElement_MethodID=
	   (*env)->GetMethodID(env,
			      vectorClassInfo->clazz, 
			      "addElement",
			      "(Ljava/lang/Object;)V");

	 PRINT_EXCEPTION(env);
	 
	 vectorClassInfo->elementData_FieldID=
	   (*env)->GetFieldID(env,
			      vectorClassInfo->clazz, 
			      "elementData",
			      "[Ljava/lang/Object;");

	 PRINT_EXCEPTION(env);

	 /* end Vector*/


	/* Property*/
	if (fulldebug) printf("Loading Property class info \n");

	 propertyClassInfo->clazz = 
	   (*env)->FindClass (env, "com/gensym/util/Property");
 	 if (!vectorClassInfo->clazz)
	   THROW_GENERAL_EXCEPTION(env, "Cant Find com/gensym/util/Property");
	 PRINT_EXCEPTION(env);

	  propertyClassInfo->clazz = 
	   (*env)->NewGlobalRef(env,propertyClassInfo->clazz); 

	 if (fulldebug) printf("propertyClassInfo->clazz is %lx \n",  propertyClassInfo->clazz );

	 propertyClassInfo->init_MethodID =
	   (*env)->GetMethodID(env,
			       propertyClassInfo->clazz, 
			       "<init>",
			       "(Lcom/gensym/util/Symbol;Ljava/lang/Object;)V");

	 if (!propertyClassInfo->init_MethodID)
	   {
	     THROW_GENERAL_EXCEPTION(env, "Cant Find Property init  method");
	     PRINT_EXCEPTION(env);
	   }

	 propertyClassInfo->key_FieldID=
	   (*env)->GetFieldID(env,
			      propertyClassInfo->clazz, 
			      "key",
			      "Lcom/gensym/util/Symbol;");

	 PRINT_EXCEPTION(env);

         propertyClassInfo->value_FieldID=
	   (*env)->GetFieldID(env,
			      propertyClassInfo->clazz, 
			      "value",
			      "Ljava/lang/Object;");

	 PRINT_EXCEPTION(env);

	 /* end Property*/
	 

  
	/* Record information about RemoteRPCThreadData */

	if (fulldebug) printf("Loading RemoteRPCThreadData class info \n");

	remoteRPCThreadClassInfo->clazz = 
	  (*env)->FindClass(env, "com/gensym/jgi/G2RemoteRPCThreadData");
    
	if (!remoteRPCThreadClassInfo->clazz)
	  THROW_GENERAL_EXCEPTION(env, "Cant Find class com/gensym/jgi/G2RemoteRPCThreadData");
   
	PRINT_EXCEPTION(env);

	remoteRPCThreadClassInfo->clazz = 
	  (*env)->NewGlobalRef(env, remoteRPCThreadClassInfo->clazz );

	remoteRPCThreadClassInfo->deferredStubClass = 
	  (*env)->FindClass(env, "com/gensym/classes/DeferredStub");
    
	if (!remoteRPCThreadClassInfo->deferredStubClass)
	  THROW_GENERAL_EXCEPTION(env, "Cant Find class com/gensym/classes/DeferredStub");
   
	PRINT_EXCEPTION(env);

	remoteRPCThreadClassInfo->deferredStubClass = 
	  (*env)->NewGlobalRef(env, remoteRPCThreadClassInfo->deferredStubClass );

	PRINT_EXCEPTION(env);

	remoteRPCThreadClassInfo->retnvalue_FieldID = 
	  (*env)->GetFieldID(env,
		       remoteRPCThreadClassInfo->clazz,
		       "retnvalue",
		       "Ljava/lang/Object;");

	PRINT_EXCEPTION(env);

	remoteRPCThreadClassInfo->incompleteConversion_FieldID = 
	  (*env)->GetFieldID(env,
		       remoteRPCThreadClassInfo->clazz,
		       "threadHasIncompleteConversionData",
		       "Z");

	PRINT_EXCEPTION(env);

	remoteRPCThreadClassInfo->signalReturnError_MethodID =
	  (*env)->GetMethodID(env,
		      remoteRPCThreadClassInfo->clazz, 
		      "signalReturnError",
		      "(Lcom/gensym/util/Symbol;Ljava/lang/String;)V");

	PRINT_EXCEPTION(env);

	remoteRPCThreadClassInfo->signalReturnValue_MethodID =
	  (*env)->GetMethodID(env,
		      remoteRPCThreadClassInfo->clazz, 
		      "signalReturnValue",
		      "(Ljava/lang/Object;Z)V");

	PRINT_EXCEPTION(env);

	if (fulldebug) printf("Loading predefined symbols class info \n");

	create_global_java_symbol(env, nameSymbol,              "NAME");
	create_global_java_symbol(env, namesSymbol,             "NAMES");
	create_global_java_symbol(env, valueSymbol,             "VALUE");
	create_global_java_symbol(env, itemSymbol,              "ITEM");
	create_global_java_symbol(env, hiddenG2ArraySymbol,     "$G2-ARRAY");
	create_global_java_symbol(env, elementTypeSymbol,       "ELEMENT-TYPE");
	create_global_java_symbol(env, lastRecordedValueSymbol, "LAST-RECORDED-VALUE");
	create_global_java_symbol(env, classSymbol,             "CLASS");
	create_global_java_symbol(env, integerSymbol,           "INTEGER");
	create_global_java_symbol(env, truthValueSymbol,        "TRUTH-VALUE");
	create_global_java_symbol(env, textSymbol,              "TEXT");
	create_global_java_symbol(env, floatSymbol,             "FLOAT");
	create_global_java_symbol(env, itemOrValueSymbol,       "ITEM-OR-VALUE");
	create_global_java_symbol(env, quantitySymbol,          "QUANTITY");
	create_global_java_symbol(env, symbolSymbol,            "SYMBOL");
	create_global_java_symbol(env, g2ListSequenceSymbol,    "G2-LIST-SEQUENCE");

#ifdef GSI_USE_WIDE_STRING_API
  null_str = jgi_str2unicode("NULL");
  none_str = jgi_str2unicode("NONE");
  empty_str = jgi_str2unicode("");
  window_str = jgi_str2unicode("WINDOW");
  popup_str = jgi_str2unicode("POPUP");
  g2_javatype_class_val_attr  = jgi_str2unicode(G2_JAVATYPE_CLASS_VAL_ATTR);
  g2_javaproxy_classname_attr = jgi_str2unicode(G2_JAVAPROXY_CLASSNAME_ATTR);
  g2_javashort_classname     = jgi_str2unicode(G2_JAVASHORT_CLASSNAME);
  g2_javabyte_classname      = jgi_str2unicode(G2_JAVABYTE_CLASSNAME);
  g2_javalong_classname      = jgi_str2unicode(G2_JAVALONG_CLASSNAME);
  g2_javachar_classname      = jgi_str2unicode(G2_JAVACHAR_CLASSNAME);
  g2_javaint_classname       = jgi_str2unicode(G2_JAVAINT_CLASSNAME);
  g2_javafloat_classname     = jgi_str2unicode(G2_JAVAFLOAT_CLASSNAME);
  g2_raw_java_inttypearray_classname = jgi_str2unicode(G2_RAW_JAVA_INTTYPEARRAY_CLASSNAME);
  g2_raw_java_booleantypearray_classname = jgi_str2unicode(G2_RAW_JAVA_BOOLEANTYPEARRAY_CLASSNAME);
  g2_raw_java_symbolarray_classname  = jgi_str2unicode(G2_RAW_JAVA_SYMBOLARRAY_CLASSNAME);
  g2_raw_java_stringarray_classname = jgi_str2unicode(G2_RAW_JAVA_STRINGARRAY_CLASSNAME);
  g2_raw_java_doubletypearray_classname = jgi_str2unicode(G2_RAW_JAVA_DOUBLETYPEARRAY_CLASSNAME);
  g2_raw_java_numberarray_classname = jgi_str2unicode(G2_RAW_JAVA_NUMBERARRAY_CLASSNAME);
  g2_raw_java_objectarray_classname = jgi_str2unicode(G2_RAW_JAVA_OBJECTARRAY_CLASSNAME);
#else
  null_str = "NULL";
  none_str = "NONE";
  empty_str = "";
  window_str = "WINDOW";
  popup_sr = "POPUP";
  g2_javatype_class_val_attr = G2_JAVATYPE_CLASS_VAL_ATTR;
  g2_javaproxy_classname_attr = G2_JAVAPROXY_CLASSNAME_ATTR;
  g2_javashort_classname     = G2_JAVASHORT_CLASSNAME;
  g2_javabyte_classname      = G2_JAVABYTE_CLASSNAME;
  g2_javalong_classname      = G2_JAVALONG_CLASSNAME;
  g2_javachar_classname      = G2_JAVACHAR_CLASSNAME;
  g2_javaint_classname       = G2_JAVAINT_CLASSNAME;
  g2_javafloat_classname     = G2_JAVAFLOAT_CLASSNAME;
  g2_raw_java_inttypearray_classname = G2_RAW_JAVA_INTTYPEARRAY_CLASSNAME;
  g2_raw_java_booleantypearray_classname = G2_RAW_JAVA_BOOLEANTYPEARRAY_CLASSNAME;
  g2_raw_java_symbolarray_classname      = G2_RAW_JAVA_SYMBOLARRAY_CLASSNAME;
  g2_raw_java_stringarray_classname = G2_RAW_JAVA_STRINGARRAY_CLASSNAME;
  g2_raw_java_doubletypearray_classname = G2_RAW_JAVA_DOUBLETYPEARRAYARRAY_CLASSNAME;
  g2_raw_java_numberarray_classname = G2_RAW_JAVA_NUMBERARRAY_CLASSNAME;
  g2_raw_java_objectarray_classname = G2_RAW_JAVA_OBJECTARRAY_CLASSNAME;

#endif

    jgi_initIntegerCacheStore();

    if (fundebug) {printf("Exited Function construct_pre_lookup_class_information \n"); fflush(stdout);}

}

void construct_pre_lookup_symbol_gsi_information(JNIEnv *env) {

  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaShortClassSymbol, g2_javashort_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaShortClassSymbol, g2_javashort_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaByteClassSymbol, g2_javabyte_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaLongClassSymbol, g2_javalong_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaCharClassSymbol, g2_javachar_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaIntClassSymbol, g2_javaint_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaFloatClassSymbol, g2_javafloat_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaIntTypeArrayClassSymbol,g2_raw_java_inttypearray_classname );
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaBooleanTypeArrayClassSymbol,g2_raw_java_booleantypearray_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaSymbolArrayClassSymbol,g2_raw_java_symbolarray_classname );
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaStringArrayClassSymbol,  g2_raw_java_stringarray_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaDoubleTypeArrayClassSymbol, g2_raw_java_doubletypearray_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaNumberArrayClassSymbol, g2_raw_java_numberarray_classname);
  MAKE_JAVA_AND_GSI_SYMBOL(env, G2JavaObjectArrayClassSymbol, g2_raw_java_objectarray_classname);
	
  window_gsisymbol                      = gsi_make_symbol(window_str);
  popup_gsisymbol                       = gsi_make_symbol(popup_str);
  g2_floatarray_classname_gsisymbol     = gsi_make_symbol(g2_floatarray_classname);
  g2_g2array_classname_gsisymbol        = gsi_make_symbol(g2_g2array_classname);
  g2_integerarray_classname_gsisymbol   = gsi_make_symbol(g2_integerarray_classname);
  g2_itemarray_classname_gsisymbol      = gsi_make_symbol(g2_itemarray_classname);
  g2_quantityarray_classname_gsisymbol  = gsi_make_symbol(g2_quantityarray_classname);
  g2_sequencearray_classname_gsisymbol  = gsi_make_symbol(g2_sequencearray_classname);
  g2_structurearray_classname_gsisymbol = gsi_make_symbol(g2_structurearray_classname);
  g2_symbolarray_classname_gsisymbol    = gsi_make_symbol(g2_symbolarray_classname);
  g2_textarray_classname_gsisymbol      = gsi_make_symbol(g2_textarray_classname);
  g2_truthvaluearray_classname_gsisymbol = gsi_make_symbol(g2_truthvaluearray_classname);
  g2_valuearray_classname_gsisymbol     = gsi_make_symbol(g2_valuearray_classname);
  g2_javaproxy_classname_attr_gsisymbol  = gsi_make_symbol(g2_javaproxy_classname_attr);
  g2_javatype_class_val_attr_gsisymbol  = gsi_make_symbol(g2_javatype_class_val_attr);
  g2_javalong_classname_gsisymbol       = gsi_make_symbol(g2_javalong_classname);
  g2_javashort_classname_gsisymbol      = gsi_make_symbol(g2_javashort_classname);
  g2_javabyte_classname_gsisymbol       = gsi_make_symbol(g2_javabyte_classname);
  g2_javachar_classname_gsisymbol       = gsi_make_symbol(g2_javachar_classname);
  g2_javafloat_classname_gsisymbol      = gsi_make_symbol(g2_javafloat_classname);
}
