/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      jni_gi_utils.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               10-Jan-1997   M.D.Gribble
 +
 + Description:  This file contains various utility and conversion
 +				 functions for use with the java_gsi.c
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
#ifndef WIN32
#  include <sys/time.h>
#endif

#include "jni_gi.h"
extern int incompleteStubConversion;


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

#define MAX_INTEGER_IN_CACHE 151
#define MAX_INTEGER_CACHE_SIZE MAX_INTEGER_IN_CACHE*2


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


jobject JavaIntergerCache[MAX_INTEGER_CACHE_SIZE];

/** 
 * The following functions serve a Java Integer Cache
 */

/** Init the Integer Cache Store */
void jgi_initIntegerCacheStore() {
  int i = 0;
  for (i= 0; i < MAX_INTEGER_IN_CACHE*2; i++) {
    JavaIntergerCache[i] = NULL;
  }
}

/** 
 * Return a Java Integer for a given jint
 * Read from the cache if within bounds and has already been referenced.
 */
jobject  jgi_getJavaInteger(JNIEnv *env, jint val) {
  int inrange = JNI_FALSE;
  jobject integerObj;

  if (val < MAX_INTEGER_IN_CACHE && val > -MAX_INTEGER_IN_CACHE) {
    if (JavaIntergerCache[MAX_INTEGER_IN_CACHE + val] != NULL) {
      return JavaIntergerCache[MAX_INTEGER_IN_CACHE + val];
    }
    inrange = JNI_TRUE;
  }
  
  integerObj = (*env)->NewObject(env , 
				 integerClassInfo->clazz, 
				 integerClassInfo->init_MethodID, 
				 val);
  if (inrange) {
    integerObj = (*env)->NewGlobalRef(env, integerObj);
    JavaIntergerCache[MAX_INTEGER_IN_CACHE + val] = integerObj;
  }
  return integerObj;
}

/**
  * The following functions are to be used to transform any string before passing
  * to GSI. These will return a newly allocated strings (null terminated short[]).
  * The original string is NOT RECLAIMED.
  * The caller is free to reclaim the return value.
  */


unsigned short* jgi_str2unicode (char* string) 
{
  int string_length = 0;
  unsigned short* unicode_string = (unsigned short*)NULL;
  int i;

  if (string) string_length =  strlen (string);

    unicode_string = (unsigned short*)malloc ((string_length+1)*sizeof(short));
    for (i=0;i<string_length;i++) {
      unicode_string[i] = (short)string[i];
    }
    unicode_string[string_length] = (short)NULL;
    
  return unicode_string;
}



char* jgi_unicode2str (unsigned short* unicode_string) 
{
  /*  static xint wstrlen (unsigned short*);*/
  int string_length = jgi_wstrlen (unicode_string);
  char* string = (char*)NULL;
  int i;

    string = (char*)malloc ((string_length+1)*sizeof(char));
    for (i=0;i<string_length;i++)
      string[i] = (char)unicode_string[i];
    string[string_length] = (char)NULL;

  return string;
}

int jgi_wstrlen (unsigned short* unicode_string) 
{
  int i=0;

  if (!unicode_string) return 0;

  for (;;) {
    if (*(unicode_string++) == 0)
      return i;
    i+=1;
  }
}

void jgi_printStr(gsi_char *str)
{

  if (!str) return;

#ifdef GSI_USE_WIDE_STRING_API
  {
    char *str_utf =  jgi_unicode2str(str);
    printf("%s", str_utf);
    free(str_utf);
  }
#else
  printf("%s",str);
#endif

}
  


jstring jgi_NewString(JNIEnv *env, gsi_char *str)
{
  if (!str) return NULL;

#ifdef GSI_USE_WIDE_STRING_API
  { int len = jgi_wstrlen(str);
    int i;
    for (i=0; i<len; i++)
      {
	/* Frig as G2 sends 8232 when in GSI WIDE string mode for a \n ! */
	/* printf("%d ", str[i]); */
	if (str[i] == 8232)
	  str[i] = 10;
      }
     
  return (*env)->NewString(env, str, len);
  }
#else
  return (*env)->NewStringUTF(env, str);
#endif
}



/* jgi_GetStringChars() copies the string given to us from JNI and null
   terminates it.  The resulting string as a GSI string (type: gsi_char *).

   This has two implementations based on whether we're compiling using the GSI
   wide string API.  NB: at present (at least as of 3/11/04), in practice, and
   since at least Javalink's 1.0 release, the wide string API has been used
   exclusively in the shipping product.

   If we're using the wide string API, we get a UTF-8 string from Java;
   otherwise, we get a Unicode (wide) string.  We assume here that Java's
   Unicode wide string elements are of the same type, ultimately, as GSI's,
   i.e., unsigned short, i.e., 2 bytes per character.  Note that while UTF-8
   strings are always terminated with the `\0' character, Unicode strings are
   not. (A unicode string from JNI is sometimes NUL terminated by accident, but
   not always!).  This distinction is not currently relied on, however, as we
   always use the JNI API's for getting the length of the Java string, and we
   always add on a final nul termination character at the appropriate place at
   the end of the data.

   In the case of the wide string API this function feels that G2 needs the
   Unicode line separator character U+2028 (decimal 8232) for one of the
   traditional "ASCII" line break character or character sequences, i.e., either
   CRLF or CR or LF, when using the wide string API.  It therefore converts any
   such character sequences accordingly.  (It does not do the equivalent for the
   non-wide-string API, possibly because it will be handled in later G2
   transcoding, possibly because that mode is not really used, so nobody cared
   to do that. I am not quite sure. -mhd, 3/11/04)

   Note that this now (as of 3/11/04) uses Release/GetStringCritical() for wide
   strings where it used to use Release/GetStringChars(). The new functions were
   first defined in Java 2, Version 1.2. This is OK, since at least that level
   of Java is now required for Javalink.

   Note: as elsewhere in this facility we ignore memory allocation failure
   errors, both in the case of calling the JNI Get functions and in the case of
   calling malloc().

   NOTE: in the case where the wide string API is used (always at present) this
   code assumes that both gsi_char (GSI's primitive character type) and jchar
   (Java/JNI's primitive character type) are equivalent to unsigned char.  If
   that were not the case, this code could break.

   unicode_strdup_handling_linebreaks() is currently a subfunction of
   jgi_GetStringChars(), though it may have more general use.  It malloc's a new
   unicode string (i.e., unsigned short * array, of the length given by len + 1,
   and fills it with the contents of str, except that it converts CR's, LF's,
   and CRLF sequences into U+2028 (Unicode's line separator character), and then
   nul-terminates the string and returns it.  Note that it's possible for the
   resulting string to be of length less than len+1, i.e., nul-terminated at an
   earlier index than len, i.e., in the case where 2-char CRLF sequences were
   converted into single U+2028 characters. (The amount of space "wasted" is
   negligeable, so nothing fancy is done to keep from wasting it.) */

unsigned short *unicode_strdup_handling_linebreaks(unsigned short *str, int len)
{
  int i, n;
  unsigned short *sstr, *sstr_back, *str_cpy, *sstr_cpy;

  sstr_back = str;		/* trailing lead pointer for str */
  sstr = str;			/* leading lead pointer for str */
    
  str_cpy = (unsigned short *)malloc(sizeof(unsigned short) * (len + 1));
  sstr_cpy = str_cpy;		/* lead pointer for str_cpy */
  n = 0;
  for (i = 0; i < len; i++) {
    if (*sstr >= ' ') {
      n++;			/* skip past non-control char. */
      sstr++;
      continue;
    }
    if ((*sstr == '\r') && (sstr[1] == '\n')) {
      /* CRLF: skip CR, let LF get handled by the following statement. */
      sstr++;
      i++;
    }
    if ((*sstr == '\n') || (*sstr == '\r')) {
      /*  LF, CR, or CRLF */
      memcpy(sstr_cpy, sstr_back, n * sizeof(unsigned short));
      sstr_cpy = sstr_cpy + n;
      n = 0;
      sstr++;
      sstr_back = sstr;
      *sstr_cpy = 0x2028;
      sstr_cpy++;
    } else {
      n++;
      sstr++;
    }
  }
  if (n > 0) {
    memcpy(sstr_cpy, sstr_back, n * sizeof(unsigned short));
    sstr_cpy = sstr_cpy + n;
  }
  *sstr_cpy = 0;		/* Nul terminate */
  return str_cpy;
}


gsi_char *jgi_GetStringChars(JNIEnv *env, jstring jstr)
#ifdef GSI_USE_WIDE_STRING_API
{
  gsi_char *str, *str_cpy;
  int len;

  len = (*env)->GetStringLength(env, jstr);  
  str = (gsi_char *)(*env)->GetStringCritical(env, jstr, NULL);
  str_cpy = unicode_strdup_handling_linebreaks(str, len);
  (*env)->ReleaseStringCritical(env, jstr, str);
  return str_cpy;
}
#else
{
  int i;
  int len = (*env)->GetStringUTFLength(env, jstr);
  gsi_char *str = (gsi_char *)(*env)->GetStringUTFChars(env, jstr, NULL);
  gsi_char *str_cpy = (gsi_char *)malloc(sizeof(gsi_char *) * (len + 1));
  for (i=0; i<len; i++)
    str_cpy[i] = str[i];
  str_cpy[len] = 0;
  (*env)->ReleaseStringUTFChars(env, jstr, str );
  return str_cpy;
}
#endif





/*****************************************************************************
 * java_intern_from_gsi_symbol
 *
 *   Description: 
 *
 * Convert a gsi symbol to an interned Java Symbol. Utilise user_data of 
 * gsi_symbol's to contain preinterned symbol of same name
 *     
 *   Input Arguments:
 *     env : The JNI environment
 *     gsisymbool : The gsi_symbol to intern
 *
 *	
 *   Returns:
 *     the Java Symbol object
 *   Modifications:
 *****************************************************************************/
jobject java_intern_from_gsi_symbol(JNIEnv *env, gsi_symbol gsisymbol, jobject def)
{
  jobject java_symbol;

  if (!gsisymbol)
    {
      if (!def)
	return noneSymbol;
      else
	return def;
    }

  /* Cant do anything special without GSI_USE_NEW_SYMBOL_API on */
#ifdef GSI_USE_NEW_SYMBOL_API
  {
  /* Check for any user data, we may have already interned
     this symbol */
  symbol_user_data_type symbol_user_data = gsi_symbol_user_data (gsisymbol);

  if (symbol_user_data)
    return (jobject)symbol_user_data;
  

  /* We have not interned this symbol before, so intern it first and store it
     as this symbol internal user data, for future "fast" lookup
   */

  java_symbol = java_intern_symbol(env, gsi_symbol_name (gsisymbol));

  /* Need the JNI object reference to be permanent */
  java_symbol = (*env)->NewGlobalRef(env, java_symbol);

  gsi_set_symbol_user_data (gsisymbol, java_symbol);

  return java_symbol;
  }
#else

  java_symbol = java_intern_symbol(env, gsisymbol);

  return java_symbol;

#endif

}
  
/*****************************************************************************
 * isSameSymbol
 *
 *   Description: 
 *
 * Compare one symbol against another. Symbols objects can not be compared
 * directly (using isSameObject) as deserialised Symbols will not have
 * will be new Symbol objects. However Symbol.equals will return true
 * if two Symbols are the same by value but not the same Object refernces.
 *     
 *   Input Arguments:
 *     java_object        The java_object to call the method on
 *     method_id          The methodId of the method to call
 *     return_signature   The return_signture of the method
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
jboolean isSameSymbol (JNIEnv *env,
		       jobject symbol1,
		       jobject symbol2) {

   if ((*env)->IsSameObject(env, symbol1, symbol2)) return JNI_TRUE;

   /* Because of Symbols being created from serialization the above may fail
      to return true for the same symbols */
   return (*env)->CallBooleanMethod (env,
				     symbol1,
				     symbolClassInfo->equals_MethodID,
				     symbol2);

}

/*****************************************************************************
 * call_java_method
 *
 *   Description: 
 *
 *   Call the specified java method (from a given ID) utilising the correct
 *   JNI CallMethod function so as return the correct type as given by
 *   return_signature
 *     
 *   Input Arguments:
 *     java_object        The java_object to call the method on
 *     method_id          The methodId of the method to call
 *     return_signature   The return_signture of the method
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
 jvalue call_java_method(JNIEnv *env,
			 jobject java_object,
			 jmethodID method_id,
			 char *return_signature,
			 jvalue *java_args_ptr)
{
jvalue java_value; 
 
  switch (return_signature[0]) {
  case JAVA_CLASS_SIGNATURE_CHAR:
    java_value.l = (*env)->CallObjectMethodA(env,
				       java_object,
				       method_id,
				       java_args_ptr);
    break;

  case JAVA_BOOLEAN_SIGNATURE_CHAR:
    java_value.z = (*env)->CallBooleanMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;

  case JAVA_BYTE_SIGNATURE_CHAR:
    java_value.b = (*env)->CallByteMethodA(env,
				       java_object,
				       method_id,
				       java_args_ptr);  
    break;
  case JAVA_CHAR_SIGNATURE_CHAR:
    java_value.c = (*env)->CallCharMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;
  case JAVA_SHORT_SIGNATURE_CHAR:
    java_value.s = (*env)->CallShortMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;
  case JAVA_INT_SIGNATURE_CHAR:
   java_value.i = (*env)->CallIntMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;
  case JAVA_LONG_SIGNATURE_CHAR:
    java_value.j = (*env)->CallLongMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;
  case JAVA_FLOAT_SIGNATURE_CHAR:
    java_value.f = (*env)->CallFloatMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;
  case JAVA_DOUBLE_SIGNATURE_CHAR:
    java_value.d = (*env)->CallDoubleMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;

  case JAVA_VOID_SIGNATURE_CHAR:
    (*env)->CallVoidMethodA(env, 
					  java_object, 
					  method_id, 
					  java_args_ptr);
    break;
  default:
    fprintf(stderr, "Could not find Method to call for return_signature %c in call_java_method",
	   return_signature[0]);

  }

  return java_value;
}


/*****************************************************************************
 * invoke_declared_java_method
 *
 *   Description: 
 *     invoke a variable argument java method with values from gsi argument array
 *     as a result of an RPC call from G2 over a particualr connection
 *     
 *   Input Arguments:

 *     gsi_item arg_array[] gsi item data
 *     cnt			:	number of gsi items passed
 *	
 *   Returns:
 *     character method signarure
 *   Modifications:
 *****************************************************************************/
 void  invoke_declared_java_method( JNIEnv *env, 
			   jobject connection,
			   jobject G2_RPD_name,
			   jboolean non_connection_specific,
			   gsi_item args[],
			   gsi_int cnt,
			   gsi_int call_index,
			   gsi_int context)
{
  int i;
  jobject java_arg_object;
  jclass java_arg_class;
  jobjectArray jargs_classes_array = NULL;
  jobjectArray jargs_array = (*env)->NewObjectArray(env, 
					 cnt, 
					 objectClassInfo->clazz, 
					 NULL); 

  if (fundebug) { printf("Function  invoke_java_declared_method \n"); fflush(stdout);}

  /* 
   * We will need a class array of the parameters so we can look up the method later if needed
   */
  jargs_classes_array = (*env)->NewObjectArray(env, 
					       cnt, 
					       classClassInfo->clazz, 
					       NULL);


  if (fulldebug) { printf("invoke_java_declared_method setting up args\n"); fflush(stdout);}

  for (i=0; i<cnt; i++)
    { 
      java_arg_object = create_java_object_from_gsiitem(env , 
				      args[i],
				      (&java_arg_class),
				      JNI_TRUE,
				      JNI_FALSE);

      /* The JNI_TRUE above ensures that we convert primitive types to Java
       * primitive types so we can lookup Java methods that have int, boolean,
       * double, etc... This means, that we can not lookup methods with
       * Integer, Boolean, Double, etc...
       */

      (*env)->SetObjectArrayElement(env, jargs_array, i, java_arg_object);
      (*env)->SetObjectArrayElement(env, jargs_classes_array, i, java_arg_class);
      
    }

  /* We can now call the invoke method using the JGI registered class
   * which will lookup the method_name using the classes_array as a signature
   */
  if (fundebug) { printf("Invoking method %lx with call index %lx\n",G2_RPD_name,call_index); fflush(stdout);}

  (*env)->CallVoidMethod(env, 
			 JREF(registeredJGInterface), 
			 registeredJGInterface->invokeMethod_MethodID,
			 connection,
			 G2_RPD_name,
			 non_connection_specific,
			 jargs_array,
			 jargs_classes_array,
			 (jlong)call_index,
			 incompleteStubConversion,
			 (jint)context);

  incompleteStubConversion = 0;		 
			 
  if (fundebug) { printf("Exiting invoke_java_declared_method\n"); fflush(stdout);}
}

/*****************************************************************************
 * invoke_java_method
 *
 *   Description: 
 *     invoke a variable argument java method with values from gsi argument array
 *     
 *   Input Arguments:

 *     gsi_item arg_array[] gsi item data
 *     cnt			:	number of gsi items passed
 *	
 *   Returns:
 *     character method signarure
 *   Modifications:
 *****************************************************************************/
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
			   gsi_int context)
{
  int i;
  jobject java_arg_object;
  jclass java_arg_class;
  jobjectArray jargs_classes_array = NULL;
  jobjectArray jargs_array = (*env)->NewObjectArray(env, 
					 cnt, 
					 objectClassInfo->clazz, 
					 NULL); 

  if (fundebug) { printf("Function  invoke_java_method \n"); fflush(stdout);}

  for (i=0; i<cnt; i++)
    { 
      java_arg_object = create_java_object_from_gsiitem(env , 
				      args[i],
				      (!java_method_object ? &java_arg_class : NULL),
				      JNI_TRUE,
				      JNI_FALSE);

      /* The JNI_TRUE above ensures that we convert primitive types to Java
       * primitive types so we can lookup Java methods that have int, boolean,
       * double, etc... This means, that we can not lookup methods with
       * Integer, Boolean, Double, etc...
       */

      (*env)->SetObjectArrayElement(env, jargs_array, i, java_arg_object);
      
    }


    /* We can now call the invoke method use the JGI registered class */
    (*env)->CallVoidMethod(env, 
			   JREF(registeredJGInterface), 
			   registeredJGInterface->invokeMethodObject_MethodID,
			   java_object,
			   java_method_object,
			   jargs_array,
			   (jint)call_index,
			   force_return_value,
			   run_in_own_thread,
			   run_in_queued_thread,
			   incompleteStubConversion,
			   (jint)context);

  incompleteStubConversion = 0;
  		 
			 
}  




/*****************************************************************************
 * void return_gsi_values_from_java_method_call
 *   Description: 
 *     Convert a java return value into a gsi data value and return it
 *	   back to G2 refernced by a previous call_index
 *	   This function should be used inconjunction with 
 *     execute_java_method_from_gsi_args
 *     
 *   Input Arguments:
 *	   java_method_return_value: The raw long value retunred from calling a
 *                                   java method via execute_java_dynamic_method
 *	   java_method             : The name of the kava method called
 *	   call_handle		   : The call handle to return back to G2 via
 *				     gsi_rpc_return_values
 *         error                   : set JNI_TRUE to indicate an error has occured
 *                                   this function will inform G2 and stop g2 waiting
 *                                   for a return value
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void return_gsi_values_from_java_method_call (JNIEnv *env,
					      jvalue java_method_return_value,
					      jboolean force_return_value,
					      char *return_signature,
					      gsi_int call_handle,
					      jboolean error,
					      jobject error_symbol,
					      jstring error_text,
					      gsi_int context)
{
  gsi_item *transient_gsi_items = NULL;
  jobject exception;
  gsi_item return_gsiitem = NULL;
   int multi_return = 0;   //Used to specify the  multiple values return
   jclass joclass;     // MultipleValuesHolder class definition
   jobject mvh;     //MultipleValuesHolder class instance;
   jmethodID mid;     // MultipleValuesHolder size method id
   jmethodID gmid;     // MultipleValuesHolder get method id
   int argc;      //Amount of values for return
   jobject value;     // Value from MultipleValuesHolder

  if (fundebug) { printf("Function return_gsi_values_from_java_method_call (Error is %d call handle is %lx)\n", error, call_handle); fflush(stdout);}

  /* We want to talk back to G2 if we have a call_handle (for a return value) 
     or we have an error to report. 
   */
  if ((call_handle != 0 && call_handle != -1) || error)
    {
      int bad_args = JNI_FALSE;

      /* Are we returning after an error */
      if (!error)
	{
	  transient_gsi_items = gsi_make_array (1);

	  /* Are we a void function or 
	   * return to a void G2 RPC (no return values) 
	   * (only if we are not forced to return a value)
	   */
	  if ((return_signature[0] == JAVA_VOID_SIGNATURE_CHAR) ||
	      (!java_method_return_value.l && !force_return_value))
	    {
	    
	      if (fundebug) { printf("return_gsi_values_from_java_method_call sending no return values \n"); fflush(stdout);}

	    /* Must pass back 0 arguments to release the calling procedure */
	        
	    gsi_rpc_return_values (
				    transient_gsi_items, 
				    0, 
				    (call_identifier_type)call_handle, 
				    context);

	    } 
	  else 
	    {

	     
	      /* If we are not sending back a object signature it must be a primitive type */
	      if (return_signature[0] != JAVA_CLASS_SIGNATURE_CHAR)
	        {
		  return_gsiitem = gsi_make_item ();
		  bad_args = convert_primitive_java_value_to_gsiitem (env, 
								      java_method_return_value, 
								      return_signature, 
								      return_gsiitem);
		}		  
	      else if (java_method_return_value.l == NULL)
		{
		  /* A null item indicates a void return, but we still must return something to 
		   * the waiting RPC, - return 0
		   */
		  return_gsiitem = gsi_make_item ();
		  gsi_set_int (return_gsiitem , 0);
		}
	      else
		{
     joclass = (*env)->FindClass(env, "com/gensym/jgi/MultipleValuesHolder");
     //Check for MultipleValues return
     if ((*env)->IsInstanceOf(env, java_method_return_value.l, joclass) == JNI_TRUE) {
      multi_return = 1;
      mvh = java_method_return_value.l; // MultipleValuesHolder instance
      mid = (*env)->GetMethodID(env, joclass, "size", "()I");
      gmid = (*env)->GetMethodID(env, joclass, "get", "(I)Ljava/lang/Object;");
      argc = (*env)->CallIntMethod(env, mvh, mid);
      if (argc > 0) {
       int i = 0;
       gsi_reclaim_array (transient_gsi_items); //Reclaim previously created array
       transient_gsi_items = gsi_make_array(argc); //Creating new array
       for (i = 0; i < argc; i++) {
        return_gsiitem = gsi_make_item();
        value = (*env)->CallObjectMethod(env, mvh, gmid, i);
        convert_java_object_to_gsiitem(env,
              value,
               &return_gsiitem,
               context);
        transient_gsi_items[i] = return_gsiitem;
       };
      }
     } else {// Single value return
		  bad_args = convert_java_object_to_gsiitem(env,
							  (jobject)java_method_return_value.l, 
							  &return_gsiitem,
							  context);
		  /* printf("return val ref is %lx \n", java_method_return_value.l); */
		}
   }


	      /* Check for any exceptions during the conversion process*/
	      if ((exception = (*env)->ExceptionOccurred(env)) || bad_args == JAVA_ITEM_BAD)
		{
		  gsi_item *error_transient_gsi_items = gsi_make_array (2);
		  gsi_char *errmsg;
		  gsi_item gsierror_sym = gsi_make_item ();
		  gsi_item gsierror_str;
		  error_transient_gsi_items[0] = gsierror_sym;

		  if (fundebug) { printf("return_gsi_values_from_java_method_call: Error During Java to GSI conversion after java invoke \n"); fflush(stdout);}
		 
		  /* Send error symbol first */
		  errmsg = (gsi_char *)jgi_str2unicode("RPC-JAVA-DATA-CONVERSION-ERROR");
		  gsi_set_sym (gsierror_sym, gsi_make_symbol (errmsg));
		  free((char *)errmsg);

		  /* then error text */
		  if (bad_args == JAVA_ITEM_BAD)
		    { 
		      errmsg = (gsi_char *)jgi_str2unicode("Error in  Null or bad GsiItem during Java-to-GSI Conversion\n");
		      gsierror_str = gsi_make_item ();
		      error_transient_gsi_items[1] = gsierror_str;
		      gsi_set_str (gsierror_str, errmsg);
		      free((char *)errmsg);
		      
		    } 
		  else 
		    {
		      
		      /* get the exception text that occured */
		      jstring message = (*env)->CallObjectMethod(env,
						 exception,
						 throwableClassInfo->toString_MethodID);

		      if (message) 
			convert_java_object_to_gsiitem(env,
						      message, 
						      &gsierror_str,
						       context);
		      else
			{
			  errmsg = (gsi_char *)jgi_str2unicode("Exception During Java-to-GSI Conversion\n");
			  gsierror_str = gsi_make_item ();
			  gsi_set_str (gsierror_str, errmsg);
			  free((char *)errmsg);
			}
		    }
	    
		  error_transient_gsi_items[1] = gsierror_str;

		  if (fulldebug)
		    (*env)->ExceptionDescribe(env);

		  gsi_rpc_return_error_values (
						error_transient_gsi_items, 
						2, 
						(call_identifier_type)call_handle, 
						context);

		  (*env)->ExceptionClear(env); /* Clean up after exception*/

		  gsi_reclaim_array (error_transient_gsi_items);
		  gsi_reclaim_item (gsierror_sym);
		  gsi_reclaim_item (gsierror_str);
		}
	      else
		{
		  if (fundebug) 
		    {
		      printf("return_gsi_values_from_java_method_call: Sending a gsi item to G2\n");
#ifdef GSI_USE_WIDE_STRING_API
		      if (fulldebug) {
			printf("details in unicode !");
#else
			gsirtl_display_item_or_value(return_gsiitem, 0, 0 );
#endif
		      }
		      fflush(stdout);
		    }

	       
     //Multiple values return
     if (multi_return == 1) {
      /* A null item indicates a void return, but we still must return something to
       * the waiting RPC, - return 0
       */
      if (argc == 0) {
       return_gsiitem = gsi_make_item ();
       gsi_set_int (return_gsiitem , 0);
		  transient_gsi_items[0] = return_gsiitem;
      }
      gsi_rpc_return_values (transient_gsi_items,
         argc,
         (call_identifier_type)call_handle,
         context);
     } else {
      // Single value return
      transient_gsi_items[0] = return_gsiitem;

		  gsi_rpc_return_values (transient_gsi_items, 
					  1, 
					  (call_identifier_type)call_handle, 
					  context);
     }
	      

		  /* Must cleanup recursively */
		  gsirtl_free_i_or_v_contents(*transient_gsi_items);
		}
						

	    } /* if not void... */

	} else
	  { 
	    if (fundebug) {printf("return_gsi_values_from_java_method_call: Did not call Java Method successfully \n"); fflush(stdout);}

	   jgi_reportG2LogBookErrorMessage (env, error_symbol, error_text, call_handle, context);

	  }

      if (transient_gsi_items) gsi_reclaim_array (transient_gsi_items);
      if (return_gsiitem) gsi_reclaim_item (return_gsiitem);
    } else {
      if (fundebug) {
	printf("return_gsi_values_from_java_method_call: call_handle 0 or -1, and no error.\n");
	fflush(stdout);
      }
    }
  if (fundebug) { printf("Exiting return_gsi_values_from_java_method_call\n"); fflush(stdout);}
}


/*****************************************************************************
 * void jgi_reportG2LogBookErrorMessage
 *   Description: 
 *     Returns an error message to the G2 logbook
 *    
 *     
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void jgi_reportG2LogBookErrorMessage(JNIEnv *env, 
			      jobject error_symbol, 
			      jobject error_text,
			      gsi_int call_handle, /* if the error is the result of an RPC call */
			      gsi_int context)
{

    gsi_item *transient_gsi_items = gsi_make_array (2);
    gsi_item value;

    if (transient_gsi_items)
      {

	    
	if (error_symbol != NULL)
	  convert_java_object_to_gsiitem(env,
					      error_symbol, 
					      transient_gsi_items,
					      context);
	else
	  {
	    /* Have no error symbol send a NONE string */
	    gsi_symbol nonesym = gsi_make_symbol (none_str);
	    *transient_gsi_items = gsi_make_item ();
	    gsi_set_sym (*transient_gsi_items, nonesym);
	  }

	value = &(transient_gsi_items[1]);
	convert_java_object_to_gsiitem(env,
					      error_text, 
					      value,
					      context); 

	gsi_rpc_return_error_values (
				      transient_gsi_items, 
				      2, 
				      (call_identifier_type)call_handle,
				      context);

	gsi_reclaim_items (transient_gsi_items);
      }
}

/*****************************************************************************
 * void return_java_values
 *   Description: 
 *    Return an array of Variables back to G2 using gsi_return_values, their
 *    values and status are also specified in corresponding array parameters
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void return_java_values (JNIEnv *env,
			 jobjectArray itemsArray,
			 jobjectArray itemAttributesArray,
			 jobjectArray itemValues,
			 jintArray    itemStatuses,
			 gsi_int context)
{
  gsi_int numItems = (itemsArray == NULL ? 0 : 
		      (gsi_int)((*env)->GetArrayLength(env, itemsArray)));
  gsi_int numValues = (itemValues == NULL ? 0 : 
		       (gsi_int)((*env)->GetArrayLength(env, itemValues)));
  int i = 0;
  int y = 0;

  if (fundebug) {
    printf ("Function return_java_values, num Items %d, num values %d \n", numItems, numValues );
    fflush(stdout);
  }

  if (numItems >0 && (numItems >= numValues)) {   
    gsi_registered_item *items = gsi_make_registered_items(numItems);
    jint    *javaStatuses;
    
    if (itemStatuses != NULL)
      javaStatuses = (*env)->GetIntArrayElements(env, itemStatuses, NULL);

    for (i=0; i<numItems; i++) {
      jobject javaitem =(jobject)(*env)->GetObjectArrayElement(env, itemsArray, (jsize)i);
      jobject javavalue = (itemValues == NULL ? NULL :
			   (jobject)(*env)->GetObjectArrayElement(env, itemValues, (jsize)i));
      jobject atts = (itemAttributesArray == NULL ? NULL :
		      (jobject)(*env)->GetObjectArrayElement(env, itemAttributesArray, (jsize)i));
      jint javastatus;
      gsi_registered_item item = items[i];
      gsi_item itemsgsiitem = NULL;
      gsi_item reggsiitem = gsi_item_of_registered_item(item);
      if (itemStatuses != NULL) 
	javastatus = javaStatuses[i];
      
      convert_java_object_to_gsiitem(env,
				     javaitem, 
				     &itemsgsiitem,
				     context);
     
      if (atts != NULL) {
	gsi_set_class_name(reggsiitem,gsi_class_name_of(itemsgsiitem));
	gsi_set_type(reggsiitem, GSI_NULL_TAG ); 
	update_gsiitem_attributes(env, 
				  reggsiitem, 
				  atts, 
				  context);
      }

      
      gsi_set_handle(item, gsi_handle_of(itemsgsiitem));

      /* printf("Handle of %d \n" , gsi_handle_of(itemsgsiitem)); */
    
      if (javavalue != NULL)
	setup_gsiitem_from_simple_java_object (env,
					       javavalue, 
					       reggsiitem,
					       context); 

      if (itemStatuses != NULL)
	gsi_set_status (item, (gsi_int)javastatus);
      
    }
    gsi_return_values(items, i, context);
    for (y = 0; y < i; y++) {
      gsi_registered_item item = items[y];
      gsi_item reggsiitem = gsi_item_of_registered_item(item);
      gsirtl_free_i_or_v_contents(reggsiitem);
    }
    gsi_reclaim_registered_items(items);

    /* Must inform the VM that we have finished with the status array */
    if (itemStatuses != NULL)
      (*env)->ReleaseIntArrayElements(env, itemStatuses, javaStatuses, JNI_ABORT );
  }
}


/*****************************************************************************
 * void return_java_attrs
 *   Description: 
 *    Returns a value to a registered GSI Variable and sets one or more of its
 *    attributes
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/
void return_java_value_and_attrs (JNIEnv *env,
				 jobject javaitem,
				 jobject atts,
				 jobject javavalue,
				 jint    javastatus,
				 gsi_int context) 
{

 

    gsi_registered_item *items = gsi_make_registered_items(1);
    gsi_registered_item item = items[0];
    gsi_item itemsgsiitem = NULL;
    gsi_item reggsiitem = gsi_item_of_registered_item(item);
    gsi_attr *gsiAttrs = NULL;

    if (fundebug) {
      printf ("Function return_java_value_and_attrs \n" );
      fflush(stdout);
    }

    convert_java_object_to_gsiitem(env,
				   javaitem, 
				   &itemsgsiitem,
				   context);
    if (atts != NULL)
      gsiAttrs = update_gsiitem_attributes(env, 
					   reggsiitem, 
					   atts, 
					   context);

    gsi_set_handle(item, gsi_handle_of(itemsgsiitem));

    gsi_set_status (item, (gsi_int)javastatus);

    /* printf("Handle of %d \n" , gsi_handle_of(env, itemsgsiitem)); */

    if (javavalue != NULL)
      setup_gsiitem_from_simple_java_object (env,
					     javavalue, 
					     reggsiitem,
					     context); 
      
    gsi_return_attrs(
		      item, 
		      gsiAttrs, 
		      gsi_attr_count_of(gsiAttrs), 
		      context);
    gsirtl_free_i_or_v_contents(reggsiitem);
    gsi_reclaim_registered_items(items);

}


/*****************************************************************************
 * void jgi_describeJavaObject
 *   Description: 
 *     Prints out the result of the toString method on stdout
 *     followed by a carriage return.
 *    
 *     
 *
 *	
 *   Returns:
 *     nothing
 *   Modifications:
 *****************************************************************************/

void jgi_describeJavaObject (JNIEnv *env, jobject jobj) {

  jclass objClass = (*env)->FindClass (env, "java/lang/Object");
  jmethodID toString_MethodID;
  jstring objString;

  if (!objClass) {
    fprintf (stderr, "WARNING: jgi_describeJavaObject got null class for item.");
    return;
  }
  toString_MethodID = (*env)->GetMethodID(env, objClass, "toString", "()Ljava/lang/String;");
  objString = (*env)->CallObjectMethod (env,
					jobj,
					toString_MethodID);
  if (objString) {
    int lengthObjectString = (*env)->GetStringUTFLength (env, objString);
    const char* string = (*env)->GetStringUTFChars (env, objString, FALSE);

    fprintf (stdout, "%s\n", string);
    fflush (stdout);
    (*env)->ReleaseStringUTFChars (env, objString, string);
  }

}

/******************
 * Profile Info
 */
#define profileSize 10000
int profile[profileSize];
int calls[profileSize];
char* descriptions[profileSize];

void initProfile() {
  int i;
  for (i = 0; i< profileSize; i++) {
    profile[i] = 0;
    calls[i] = 0;
  }
}

void addTime(int pos, int tme, char* description) {

  profile[pos] = tme + profile[pos];
  calls[pos] = calls[pos] + 1;
  descriptions[pos] = description;
}

void printProfile() {
  int i;
  for (i = 0; i < profileSize; i++) {
    if (profile[i] > 0)
      printf("%d:%d * %d (%s)\n", i, profile[i], calls[i], descriptions[i]);
  }
  printf("\n");
}


#ifdef WIN32
int jgi_get_timestamp () {
  return 0;
}
#else
int jgi_get_timestamp () {

  struct timeval tv;
  struct timezone tzp;
  static int base_sec;
  int retn;

  retn = gettimeofday (&tv, &tzp);
  if (base_sec == 0)
    base_sec = tv.tv_sec;
  return (tv.tv_sec - base_sec)*1000000 + tv.tv_usec;
}
#endif

