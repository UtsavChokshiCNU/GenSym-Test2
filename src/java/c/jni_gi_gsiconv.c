/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      jni_gi_gsiconv.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               1-MAR-1997   M.D.Gribble
 +
 + Description:  This file contains various utility and conversion
 +		 functions for converting gsi items to Java
 +               objects and primitive types
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


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - GsiItems to Java Objects Converters
 %
 % Description:
 %   
 %		This function group converts or creats Java objects from GsiItem data
 %		structures
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




/*
 *	set the history keeping spec and values for a java item
 *   from the gsi object to which it maps
 */
void  set_java_history_from_gsi_history(JNIEnv *env, gsi_item *arg ,  jobject java_g2proxy)
{
  gsi_int   history_count = gsi_history_count_of(arg);
  gsi_int   history_type, max_count, max_age, min_interval;
  gsi_item  *values;
  double   *timestamps;
  jobjectArray jobject_array; /* holds the history values */
  jdoubleArray jdouble_array; /* holds the time stamps    */
  jobject java_array ;

  jobject obj;
  char * java_class_name=NULL;
  int j;
  int do_class_test = 1;
  jclass clazz = objectClassInfo->clazz;
  
  int history_set_ok = 1;
  
  jclass history_class; /* modification for efficient history handling by g2itemproxy*/
  
  gsi_int context = gsi_current_context();
  
  /* vars end */
  
  if (history_count > 0) {
    gsi_extract_history(arg,(void **)&values,&timestamps,&history_type);
    gsi_extract_history_spec(arg,&max_count,&max_age,&min_interval);
    
    if (fulldebug)
      {
	printf("*B* Function  set_java_history_from_gsi_history>>\n" );
	
	printf(" Total of %d values in history whose spec (%d)(%d) permits them\n", 
	       history_count, 
	       history_type, 
	       gsi_history_type_of(arg));
	
	printf(" at intervals of %d milliseconds or greater and allows for ",min_interval);
	if (max_count) {
	  printf("%d historical values",max_count);
	  if (max_age) {
	    printf(" no more than %d seconds old.  \n",max_age); }
	  else {
	    printf(".  "); } } 
	else {
	  printf("historical values no more than %d seconds old.  \n",max_age); }
	printf("\nCurrent contents of history are...\n");
      }   
    
    
    
    jobject_array = (*env)->NewObjectArray(env, 
					   history_count, 
					   clazz, 
					   NULL); 
    java_array = (jobject)jobject_array;
    
    /* 
       this is done because the call to <gsi_extract_history> 
       did not seem to work - check next version/build
       */
    if (java_array)
      {
	history_type = gsi_history_type_of (arg);
	
	switch (history_type){
	  
	case GSI_INTEGER_TAG:{
	  
	  history_class = integerClassInfo->clazz;
	  
	  for (j=0; j<history_count ; j++) 
	    {
	      obj = jgi_getJavaInteger(env, (jint)values[j]);
		
	      (*env)->SetObjectArrayElement(env, jobject_array, j, obj );
	      
	    }
	}break;
	
	case	GSI_SYMBOL_TAG:{
	  
	  history_class = symbolClassInfo->clazz;
	  
	  for (j=0; j<history_count ; j++) 
	    {
	      if(values[j])
		{
		  obj = java_intern_from_gsi_symbol (env,(gsi_symbol) values[j], noneSymbol);
		  }
		  else
		 {
			obj = noneSymbol;
		  }

		  (*env)->SetObjectArrayElement(env, jobject_array, j, obj );

	    }
	}break;		
	
	case	GSI_STRING_TAG:	{
	  
	  history_class = stringClassInfo->clazz;
	  
	  for (j=0; j<history_count ; j++) 
	    {
	      if (values[j])
		{	
		  obj = jgi_NewString(env,(gsi_char *)values[j]);

		}
		else
		{
		obj = jgi_NewString(env,(gsi_char *)values[j]);
		}
		  (*env)->SetObjectArrayElement(env, jobject_array, j, obj );

	    }
	}break;	   
	
	case	GSI_LOGICAL_TAG:{
	  long b = 0;
	  
	  gsi_int *log_array = (gsi_int *)values;
	  
	  history_class = booleanClassInfo->booleanType_clazz; 
	  
	  for (j=0; j<history_count ; j++) 
	    {
	     		
		  b = (long )log_array[j];

		  if (b > 0) 
		    obj = booleanClassInfo->Boolean_TRUE; 
		  else 
		    obj = booleanClassInfo->Boolean_FALSE;
		  
		  (*env)->SetObjectArrayElement(env, jobject_array, j, obj );
		
	      
	    }
	  
	}break;		
	
	case	GSI_FLOAT64_TAG:{
	  double *dbl_array = (double *)values;
	  history_class = doubleClassInfo->doubleType_clazz; 
	  for (j=0; j<history_count ; j++) 
	    {
	      
	 		obj = (*env)->NewObject(env , 
					doubleClassInfo->clazz, 
					doubleClassInfo->init_MethodID, 
					dbl_array[j]);
		
		(*env)->SetObjectArrayElement(env, jobject_array, j, obj );
		
	     
	    }
	}break;	
	
	case	GSI_QUANTITY_TAG:{
	  history_class = numberClassInfo->clazz;
	  fprintf(stderr, "\n got GSI_QUANTITY_TAG");
	  for (j=0; j<history_count ; j++) 
	    {
	       
	      if (values[j])
		{
		  obj = create_java_object_from_gsiitem (env , 
							 values[j], 
							 NULL, 
							 JNI_FALSE, 
							 JNI_FALSE );
		  
		  (*env)->SetObjectArrayElement(env, jobject_array, j, obj );
		  
		}
	    }
	}break;		  
	
	default:{
	  fprintf(stderr, "\n Error setting history - TAG [%d] not recognised \n" ,history_type);
	  history_set_ok = 0;
	}
	} /* end switch on history type */
	
	
	/* create a java double array to hold the float time stamps from G2 */
	
	if ( history_set_ok == 1 )
	  {
	    jdouble_array			= (*env)->NewDoubleArray(env, history_count);  

	    (*env)->SetDoubleArrayRegion(env, jdouble_array, 0, history_count, timestamps);
	    
	    (*env)->CallVoidMethod( env, java_g2proxy,
				    g2ItemProxyClassInfo->setHistory_MethodID, 
				    jdouble_array ,
				    jobject_array,
				    max_count,
				    max_age,		
				    min_interval,
				    history_class);

	  }
	else
	  {
	    fprintf(stderr, "\n Error setting history invalid data \n");
	  }
      }	 
    else
      {
	fprintf(stderr, "\n Error setting history invalid data (java_array)\n");
      }
    
  } /* end if history_count */
  
  
} /*  end set_java_history_from_gsi_history */




/* 
 * Create a java array containing the data from a corresponding
 * gsi item or list element data. Pass back the java array, and
 * G2 element-type symbol.
 */
jobject create_java_array_from_gsi_array (JNIEnv *env , 
					  gsi_item gsiitem, 		 
					  jclass *java_class,
					  jobject *element_type,
					  jboolean *is_proxy)
{
  
 gsi_int element_count = gsi_element_count_of (gsiitem);
 gsi_int item_type= gsi_type_of(gsiitem) ;
 jobject java_array;
 jobject obj;
 gsi_symbol class_symbol;
 jobject java_class_symbol;
 int i;
 int do_class_test = 1;
 jclass clazz;
 jobjectArray jobject_array;
 
 
 /* ARRAY conversion from G2 to Java is as follows, 
    All G2 array types (and subclasses) are converted to their equivalent Java alternatives
    (including subclasses)

    G2-ARRAY    -> Object[]
    ITEM-ARRY   -> Item[]
    VALUE-ARRY  -> Object[]
    SYMBOL-ARRAY -> Symbol[]
    TEXT-ARRAY  ->  String[]
    TRUTHVALUE-ARRAY -> boolean[]
    QUANTITY-ARRAY -> Number[]
    FLOAT-ARRAY -> double[]
    INTEGER-ARRAY -> int[]

    THE FOLLOWING HAS BEEN DISABLED (MDG 4/JUL/98)
     There is also checks for class conversion directly to Java Fundamental types
     (G2_RAW_XXXXXXXX are MACRO names)

     G2-ARRAY    -> G2_RAW_JAVA_OBJECTARRAY_CLASSNAME -> Object[]
     SYMBOL-ARRAY -> G2_RAW_JAVA_SYMBOLARRAY_CLASSNAME -> Symbol[]
     TEXT-ARRAY  -> G2_RAW_JAVA_STRINGARRAY_CLASSNAME -> String[]
     TRUTHVALUE-ARRAY -> G2_RAW_BOOLEANTYPEARRAY_CLASSNAME -> boolean[]
     QUANTITY-ARRAY -> G2_RAW_NUMBERARRAY_CLASSNAME -> Number[]
     FLOAT-ARRAY -> G2_RAW_DOUBLETYPEARRAY_CLASSNAME -> double[]
     INTEGER-ARRAY -> G2_RAW_INTTYPEARRAY_CLASSNAME -> int[]
     (*is_proxy is set FALSE in these cases...i.e. these will be the actual
     types returned to Java)
    
   */

 /* We assume that gsiitem is an array type */
 if (fulldebug)
   {
     printf("Function create_java_object_from_gsi_array %d  @ %d\n" , 
	  item_type , gsi_handle_of (gsiitem));
     printf("Registration is %lx", gsi_registration_of_item (gsiitem));
   }
 
 
 *is_proxy = JNI_TRUE;  /* default */
 if (java_class) *java_class = NULL; /* Saftey Net */

 class_symbol = gsi_class_name_of(gsiitem);
 java_class_symbol = java_intern_from_gsi_symbol (env, class_symbol, noneSymbol); 


 switch (item_type) {
  case GSI_INTEGER_ARRAY_TAG:
	{
	  /* build a new Java int[]*/
	  gsi_int *data_values;
	  jint *jdata_values;
	  jintArray jint_array;
	  /* Not Currently supported (Raw array conversion when by-copy) 
	  if (!isSameSymbol(env,java_class_symbol,G2JavaIntTypeArrayClassSymbol)) {
	      *is_proxy = JNI_TRUE;
	    } else {
	      *is_proxy = JNI_FALSE;
	    }
	    */
	  /* The gsi item is a Basic Integer type map to java int[] */
	  if (java_class) *java_class = integerClassInfo->intTypeArray_clazz;
	  jint_array = (*env)->NewIntArray(env, element_count);  
	  java_array = (jobject)jint_array;
	  *element_type = integerSymbol;
	
	  data_values = gsi_int_array_of (gsiitem);
	  jdata_values = (jint *)malloc(sizeof(jint) * element_count);
	  /* we used to just blast array data in, but we can't be back in the
             face of 64-bit gsi_int's.  So we have to do it slowly.
             Benchmarking determines this is negligible, considering all the
             other overhead of data processing between GSI and java. */
	  if (data_values && jdata_values) {
	    for (i=0; i<element_count; i++)
	      jdata_values[i] =  data_values[i];

	    (*env)->SetIntArrayRegion(env, jint_array, 0, element_count, jdata_values);
	  }
	  if (jdata_values) {
	    free((char *)jdata_values);
	  }
	}break;

 case GSI_LOGICAL_ARRAY_TAG:
   {		/* build a new boolean[]*/
 
	  gsi_int *data_values;
	  jboolean *jdata_values;
	  jbooleanArray jbool_array;
	  /* Not Currently supported (Raw array conversion when by-copy) 
	  if (!isSameSymbol(env,java_class_symbol,G2JavaBooleanTypeArrayClassSymbol)) {
	    *is_proxy = JNI_TRUE;
	  } else {
	    *is_proxy = JNI_FALSE;
	  } */
	  /* The gsi item is a Basic boolean type map to java boolean[] */
              
	  if (java_class) *java_class = booleanClassInfo->booleanTypeArray_clazz;
	  jbool_array = (*env)->NewBooleanArray(env, element_count); 
	  java_array = (jarray)jbool_array;
	  *element_type = truthValueSymbol; 
	
	  data_values = gsi_log_array_of (gsiitem);
	  jdata_values = (jboolean *)malloc(sizeof(jboolean) * element_count);
	  if (data_values && jdata_values)
	    {
	      for (i=0; i<element_count; i++)
		jdata_values[i] =  (data_values[i] > 0);
		  
	      (*env)->SetBooleanArrayRegion(env, 
					    jbool_array, 
					    0, 
					    element_count, 
					    jdata_values);
	      
	    }

	    
	  if (jdata_values)
	    free((char *)jdata_values);


   }break;
  
 case GSI_SYMBOL_ARRAY_TAG:		
   {
     /* build a new symbol array object*/
     gsi_symbol *data_values ;
     gsi_symbol data_value;
     jobjectArray jobject_array;

          /* Not Currently supported (Raw array conversion when by-copy) 
	    if (!isSameSymbol(env,java_class_symbol,G2JavaSymbolArrayClassSymbol)) {
	      *is_proxy = JNI_TRUE;	      
	    } else {
	      *is_proxy = JNI_FALSE;
	    } */

	  /* The gsi item is a Symbol-Array type map to java Symbol[] */
	      
	  if (java_class) *java_class = symbolClassInfo->symbolArray_clazz; 
	  jobject_array = (*env)->NewObjectArray(env, 
						 element_count, 
						 symbolClassInfo->clazz, 
						 NULL);   

	  java_array = (jobject)jobject_array;
	  *element_type = symbolSymbol;
	
	  data_values = gsi_sym_array_of (gsiitem);
    			
	  /* populate the 'array' with the data passed in */
	  if (data_values)
	  for (i=0; i<element_count ; i++) 
	    {
	      data_value = data_values[i];

	      if (data_value)
		{
		  /* if (fulldebug)   printf("\nelement %d %s\n", i,data_value); */
				
		  obj = java_intern_from_gsi_symbol (env, data_value, noneSymbol);
				
		  (*env)->SetObjectArrayElement(env, jobject_array, i, obj );
		}

	    }

	 
   }break;
   
 case GSI_STRING_ARRAY_TAG:
   {
     /* build a new symbol array object*/
     gsi_char **data_values ;
     gsi_char *data_value;
     jobjectArray jobject_array;

     /* Not Currently supported (Raw array conversion when by-copy) 
     if (!isSameSymbol(env,java_class_symbol,G2JavaStringArrayClassSymbol)) {
       *is_proxy = JNI_TRUE;
     } else {
       *is_proxy = JNI_FALSE;
     } */
     /* The gsi item is a String-Array type map to java String[] */
     
     if (java_class) *java_class = stringClassInfo->stringArray_clazz;
     jobject_array = (*env)->NewObjectArray(env, 
					    element_count, 
					    stringClassInfo->clazz, 
					    NULL);
    
     java_array = (jobject)jobject_array;
     *element_type = textSymbol;

     data_values = gsi_str_array_of (gsiitem);
				
     /* populate the 'array' with the data passed in	*/
     if (data_values)
       for (i=0; i<element_count ; i++) 
	    {
	      data_value = data_values[i];

	      if (data_value)
		{
		  /* if (fulldebug)   printf("\nelement %d %s\n", i,data_value); */
	  
		  obj = jgi_NewString(env, data_value);

				
		  (*env)->SetObjectArrayElement(env, jobject_array, i, obj );
		}

	    }


   }  break;
  
  
 case GSI_FLOAT64_ARRAY_TAG:
   {
     /* build a new double Array object*/

	
     double *data_values ;
     
     jdoubleArray jdouble_array;

     /* Not Currently supported (Raw array conversion when by-copy) 
     if (!isSameSymbol(env,java_class_symbol,G2JavaDoubleTypeArrayClassSymbol)) {
	 *is_proxy = JNI_TRUE;
       } else {
	 *is_proxy = JNI_FALSE;
       }
     */
     /* The gsi item is a Basic FLOAT ARRAY type map to java double[] */
	 
     if (java_class) *java_class = doubleClassInfo->doubleTypeArray_clazz;
     jdouble_array = (*env)->NewDoubleArray(env, element_count);  

     java_array = (jobject)jdouble_array;
     *element_type = floatSymbol;
	  
     data_values = (double *)gsi_flt_array_of (gsiitem);
     if (data_values)
       (*env)->SetDoubleArrayRegion(env, jdouble_array, 0, element_count, data_values); 

   }break;


 case GSI_QUANTITY_ARRAY_TAG:
   /* Not Currently supported (Raw array conversion when by-copy) 
   if ( !isSameSymbol(env,java_class_symbol,G2JavaNumberArrayClassSymbol)) {
       *is_proxy = JNI_TRUE;
     } else {
       *is_proxy = JNI_FALSE;
     }
     */   
   if (java_class) *java_class = numberClassInfo->numberArray_clazz;
   jobject_array = NULL;
   *element_type = quantitySymbol;
   clazz = numberClassInfo->clazz;
 
   do_class_test = 0;
   
 case GSI_VALUE_ARRAY_TAG:
   if (do_class_test) 
     {

       *is_proxy = JNI_TRUE;

       if (java_class) *java_class = objectClassInfo->objectArray_clazz;
       jobject_array = NULL;
       *element_type = valueSymbol;
       clazz = objectClassInfo->clazz;

       do_class_test = 0;
     }

 case GSI_ITEM_OR_VALUE_ARRAY_TAG:
   if (do_class_test) 
     {
       /* Not Currently supported (Raw array conversion when by-copy) 
       if (isSameSymbol(env,java_class_symbol,G2JavaObjectArrayClassSymbol)) {
	   *is_proxy = JNI_TRUE;
	 } else {
	   *is_proxy = JNI_FALSE;
	 }
	 */
       if (java_class) *java_class = objectClassInfo->objectArray_clazz;
       jobject_array = NULL;
       *element_type = itemOrValueSymbol;
       clazz = objectClassInfo->clazz;
       do_class_test = 0;
     }

 case GSI_ITEM_ARRAY_TAG:
   if (do_class_test)
     {

       *is_proxy = JNI_TRUE;

       if (java_class) *java_class = objectClassInfo->objectArray_clazz;
       jobject_array = NULL;
       *element_type = itemSymbol;
       clazz = objectClassInfo->clazz;

     }
   
   {
     gsi_item data_value;
     gsi_item * data_values = NULL;
     jclass return_clazz;

    
     if (!jobject_array)
       {
	 jobject_array = (*env)->NewObjectArray(env, 
						element_count, 
						clazz, 
						NULL); 
	 java_array = (jobject)jobject_array;
       }
	
    
     data_values = (gsi_item *) gsi_elements_of(gsiitem);

     /* printf("Array count is %d \n", element_count ); */
				
     /* populate the 'array' with the data passed in	*/
     if (data_values)
       for (i=0; i<element_count ; i++) 
	    {
	      data_value = (gsi_item *)data_values[i];

	      if (data_value)
		{
		  if (fulldebug)
		    printf("Processing element (%d)  %d, int of %d\n %d" , i , 
			   gsi_type_of(data_value), gsi_int_of(data_value), 
			   (gsi_is_item(data_value)) );
		
		  obj = create_java_object_from_gsiitem (env , 
							 data_value, 
							 &return_clazz, 
							 JNI_FALSE, 
							 JNI_FALSE );
		  
				
		  (*env)->SetObjectArrayElement(env, jobject_array, i, obj );
		}

	    }


 
   }	break;
	
 default:{
     fprintf(stderr, "\n Error in ARRAY or LIST TAG not recognised \n");
     return NULL;
   }
  } /* switch */


 return java_array;
}



/**
 * Convert any list data held in a GSI item into a sequence 
 * of Objects of the relavant list type 
 */
jobject create_java_sequence_from_gsi_list (JNIEnv *env ,
					    gsi_item gsiitem,
					    jobject *element_type)
{
  
 gsi_int element_count = gsi_element_count_of (gsiitem);
 jstring js;
 gsi_int item_type= gsi_type_of(gsiitem) ;
 jobject obj;
 jobject sequence;
 jobject element_data;
 
 int i;
 
 /* We assume that gsiitem is an array or list tag type */
 if (fulldebug) {printf("Function create_java_object_from_gsi_list %d  @ %d\n" , 
			item_type ,  gsi_handle_of (gsiitem)); fflush(stdout);}
	  
 sequence = (*env)->NewObject(env , 
			      sequenceClassInfo->clazz ,
			      sequenceClassInfo->init_MethodID, 
			      element_count);

 element_data = ( *env )->GetObjectField(env , 
					 sequence , 
					 sequenceClassInfo->elementData_FieldID);

 switch (item_type) {
  case GSI_INTEGER_LIST_TAG:		
	{
	  /* build a new IntegerList object*/
	  gsi_int *data_values ;
	  int data_value ;

	  data_values = gsi_int_list_of (gsiitem);
	  *element_type = integerSymbol;
		
	   /* populate the 'list' with the data passed in */	
	  for (i=0; i<element_count ; i++) {
	    data_value = data_values[i];
	    obj = jgi_getJavaInteger(env, (jint)data_value);
	    
	    (*env)->SetObjectArrayElement(env, element_data, (jsize)i, obj);
	    if (fulldebug) {printf("create_java_sequence_from_gsi_list: Deleting local ref for integer tag\n"); fflush(stdout);}
	    (*env)->DeleteLocalRef(env,obj);
	  }
	}break;

 case GSI_LOGICAL_LIST_TAG:
   {		/* build a new truth value List object*/
     gsi_int *data_values ;
     int data_value ;

     *element_type = truthValueSymbol;

     /* decide if we are dealing with an array or a list of g2 ints */
     data_values = gsi_log_list_of (gsiitem);
 
     for (i=0; i<element_count ; i++) 
       {
	 data_value = data_values[i];
				
	 if (fulldebug) {printf(">>[%d](%d)\n",i, data_value); fflush(stdout);}
				
	 /*build a java object corresponding to the gsi item ie an integer*/
	 if (data_value > 0) 
	   obj = booleanClassInfo->Boolean_TRUE; 
	 else 
	   obj = booleanClassInfo->Boolean_FALSE;
	 
	 (*env)->SetObjectArrayElement(env, element_data, (jsize)i, obj);
       }
   }break;
  

 case GSI_SYMBOL_LIST_TAG:			
   {
     /* build a new symbollist object*/
     gsi_symbol *data_values ;
     gsi_symbol data_value ;
        
     *element_type = symbolSymbol;
     data_values = gsi_sym_list_of (gsiitem);
		
     /* populate the 'list' with the data passed in		*/
     for (i=0; i<element_count ; i++) 
       {
	 data_value = data_values[i];

	 if (fulldebug) 
	   {
	     printf("\nelement %d ", i);
	     jgi_printStr(gsi_symbol_name(data_value));
	     printf("\n");
	   }
		
	 obj = java_intern_from_gsi_symbol (env, data_value, noneSymbol);

	 (*env)->SetObjectArrayElement(env, element_data, (jsize)i, obj);		
       }
   }break;
   

 case GSI_STRING_LIST_TAG:
   {
     /* build a new StringList object*/
		
     gsi_char **data_values ;
     gsi_char *data_value ;
       
     *element_type = textSymbol;
     data_values =  gsi_str_list_of (gsiitem);

     /* populate the 'list' with the data passed in		*/
     for (i=0; i<element_count ; i++) 
       {
	 data_value = data_values[i];

	 if (fulldebug) 
	   {
	     printf("\nelement %d ", i);
	     jgi_printStr(data_value);
	     printf("\n");
	   }

	 js =   jgi_NewString(env, data_value);

	 (*env)->SetObjectArrayElement(env, element_data, (jsize)i, js);
	 if (fulldebug) {printf("create_java_sequence_from_gsi_list: Deleting local ref for stringlist tag\n"); fflush(stdout);}
	 (*env)->DeleteLocalRef(env,js);
       }
   }  break;
  
  

 case GSI_FLOAT64_LIST_TAG:
   {
     /* build a new FloatList object*/
     double *data_values ;
     double data_value ;

     *element_type = floatSymbol;
     data_values = (double *)gsi_flt_list_of (gsiitem);
			
     /* populate the 'list' with the data passed in		*/
     for (i=0; i<element_count ; i++) 
       {
	 data_value =data_values[i];
			 
	 if (fulldebug) 	
	   printf("\nelement %d %f\n", i,data_value);

	 /*build a java object corresponding to the gsi item ie an integer*/

	 obj = (*env)->NewObject(env , 
				 doubleClassInfo->clazz, 
				 doubleClassInfo->init_MethodID, 
				 data_value);
			
	 (*env)->SetObjectArrayElement(env, element_data, (jsize)i, obj);
	 if (fulldebug) {printf("create_java_sequence_from_gsi_list: Deleting local ref for float list tag\n"); fflush(stdout);}
	 (*env)->DeleteLocalRef(env,obj);
       }

   }break;



 case GSI_QUANTITY_LIST_TAG:
 case GSI_VALUE_LIST_TAG:	
 case GSI_ITEM_OR_VALUE_LIST_TAG:
 case GSI_ITEM_LIST_TAG:
   {
     gsi_item data_value;
     gsi_item * data_values = NULL;
     jclass clazz;

     switch(item_type) {
     case GSI_QUANTITY_LIST_TAG:       *element_type = quantitySymbol; break;
     case GSI_VALUE_LIST_TAG:	       *element_type = valueSymbol; break;
     case GSI_ITEM_OR_VALUE_LIST_TAG:  *element_type = itemOrValueSymbol; break;
     case GSI_ITEM_LIST_TAG:           *element_type = itemSymbol; break;
     }
     
     data_values = (gsi_item *) gsi_elements_of(gsiitem);
		
     if (data_values)	
     for (i=0; i< element_count ; i++) 
       {
		
	 data_value = data_values[i];
  
	 if (fulldebug)
	   printf("Processing element (%d)  %d, int of %d\n %d" , i , 
		  gsi_type_of(data_value), gsi_int_of(data_value), 
		  (gsi_is_item(data_value)) );
		
	 obj = create_java_object_from_gsiitem (env , 
						data_value, 
						&clazz, 
						JNI_FALSE, 
						JNI_FALSE );
	 
	 (*env)->SetObjectArrayElement(env, element_data, (jsize)i, obj);
	 if (gsi_is_item(data_value)) {
	   if (fulldebug) {printf("create_java_sequence_from_gsi_list: Deleting local ref for item list tag\n"); fflush(stdout);}
	   (*env)->DeleteLocalRef(env,obj);
	 }
       }
   }	break;
	
 default:{
     fprintf(stderr, "\n Error in ARRAY or LIST TAG not recognised \n");
     return NULL;
   }
 } /* switch */

  /* We must set the Sequence Size */
 (*env)->SetIntField(env, 
		     sequence, 
		     sequenceClassInfo->elementCount_FieldID, 
		     element_count);

 return sequence;
}



/**
 * Directly convert any "specific" G2 classes to Java Classes.
 */
jobject convert_java_object_from_known_g2_classes (JNIEnv *env, 
						   gsi_item gsiitem,
						   jobject java_class_symbol,
						   jclass *java_class)
{

  /* Check for proxy classes */

  if (java_class_symbol) {
	  

      if (isSameSymbol(env,java_class_symbol,G2JavaShortClassSymbol)) {

	/* we want the val attribute - WARNING WE ASSUME 1 attribute, the value */
	gsi_attr *atts = gsi_attrs_of(gsiitem); 
	gsi_int val = gsi_int_of(atts[0]);

	  if (java_class) *java_class = shortClassInfo->shortType_clazz;
	  if (fulldebug) {printf("\nUnpacked short is %d \n",(val & 0xffff) ); fflush(stdout);}
	  return (*env)->NewObject(env , 
				   shortClassInfo->clazz, 
				   shortClassInfo->init_MethodID, 
				   (jshort)(val & 0xffff)); /* 16 bits */
	    
	   

      } else if (isSameSymbol(env,java_class_symbol,G2JavaByteClassSymbol)) {

	/* we want the val attribute - WARNING WE ASSUME 1 attribute, the value */
	gsi_attr *atts = gsi_attrs_of(gsiitem);
 
	if (java_class) *java_class = byteClassInfo->byteType_clazz;
	if (fulldebug) {printf("\nUnpacked byte is %d \n", (gsi_int_of(atts[0]) & 0xff) ); fflush(stdout);}
	return (*env)->NewObject(env , 
				 byteClassInfo->clazz, 
				 byteClassInfo->init_MethodID, 
				 gsi_int_of(atts[0]));  /* 8 bits */

      } else if (isSameSymbol(env,java_class_symbol,G2JavaFloatClassSymbol)) {

	/* we want the val attribute - WARNING WE ASSUME 1 attribute, the value */
	gsi_attr *atts = gsi_attrs_of(gsiitem);
 
	if (java_class) *java_class = floatClassInfo->floatType_clazz;
	if (fulldebug) {printf("\nUnpacked float is %f \n", (gsi_flt_of(atts[0])) ); fflush(stdout);}
	return (*env)->NewObject(env , 
				 floatClassInfo->clazz, 
				 floatClassInfo->initd_MethodID, 
				 gsi_flt_of(atts[0]));  /* a double */    
	    
	    
      } else if (isSameSymbol(env,java_class_symbol,G2JavaLongClassSymbol)) { 

	/* we want the val attribute - WARNING WE ASSUME 1 att of a String */
	jlong lval = 0L;
	gsi_attr *atts = gsi_attrs_of(gsiitem); 
	gsi_char *val = gsi_str_of(atts[0]);
	if (val == NULL) return NULL;
	if (java_class) *java_class = longClassInfo->longType_clazz;
	lval = (*env)->CallStaticLongMethod(env,
					    longClassInfo->clazz,
					    longClassInfo->parseLong_MethodID,
					    jgi_NewString(env,val));
	{ /*  we need to see parse errors, direct exception reporting is here, 
	      as jni is clearing the exception after other JAVA calls */
	  gsi_int context = gsi_current_context();
	  jgi_check_and_return_g2_exception(env, (gsi_int)context);
	}
	if (fulldebug) {printf("\nUnpacked long is %u\n", lval ); fflush(stdout);}
	return (*env)->NewObject(env , 
				 longClassInfo->clazz, 
				 longClassInfo->init_MethodID, 
				 lval);
	    
      } else if (isSameSymbol(env,java_class_symbol,G2JavaIntClassSymbol)) { 

	/* we want the val attribute - WARNING WE ASSUME 1 att of a String */
	int ival;
	gsi_attr *atts = gsi_attrs_of(gsiitem); 
	gsi_char *val = gsi_str_of(atts[0]);
	if (val == NULL) return NULL;
	if (java_class) *java_class = integerClassInfo->intType_clazz;
	ival = (*env)->CallStaticIntMethod(env,
					    integerClassInfo->clazz,
					    integerClassInfo->parseInt_MethodID,
					    jgi_NewString(env, val));
	{ /*  we need to see parse errors, direct exception reporting is here, 
	      as jni is clearing the exception after other JAVA calls */
	  gsi_int context = gsi_current_context();
	  jgi_check_and_return_g2_exception(env, (gsi_int)context);
	}
	if (fulldebug) {printf("\nUnpacked Int %d\n", ival ); fflush(stdout);}

	return (*env)->NewObject(env , 
				 integerClassInfo->clazz, 
				 integerClassInfo->init_MethodID, 
				 ival);
	    

      } else if (isSameSymbol(env,java_class_symbol,G2JavaCharClassSymbol)) {

	/* we want the val attribute - WARNING WE ASSUME 1 attribute, the value */
	gsi_attr *atts = gsi_attrs_of(gsiitem); 
	gsi_char *val = gsi_str_of(atts[0]);
	if (java_class) *java_class = characterClassInfo->characterType_clazz;
	if (fulldebug) {printf("\nUnpacked char is %c \n", (val ? (jchar)val[0] : '\0') ); fflush(stdout);}
	return (*env)->NewObject(env , 
				 characterClassInfo->clazz, 
				 characterClassInfo->init_MethodID, 
				 (val ? (jchar)val[0] : '\0')); 
      }
  }
      
  return NULL;
}


/**
 * Create a new java object that reflects the contents of a given GsiItem 
 * which is a complex type, such as objects, lists, arrays, sequences and strutures 
 */
jobject create_java_object_from_complex_gsiitem (JNIEnv *env , 
						 gsi_item gsiitem, 
						 jclass *java_class)
{
  gsi_symbol name_symbol = NULL, class_symbol = NULL;
  int total_attr_cnt, sequence_element_cnt, struct_count;
  gsi_int item_type = gsi_type_of(gsiitem);
  gsi_attr *struct_items;		  
  gsi_item *sequence_values;
  jarray attrnames, attrvalues;
  jobject java_name_symbol, java_class_symbol, attributes;
  jobject java_g2proxy = NULL;
  gsi_int handle;
  int start_pos = 0;
  jobject array_contents;
  jobject element_type;
  jobject list_sequence;
  jobject value_attr;
  jobject obj = NULL;
  gsi_registration itemreg;
  
  if (convdebug) printf("Function create_java_object_from_complex_gsiitem \n");

  if (fulldebug) printf ("Item Tag = %d.\n", item_type);

  switch (item_type)
    {
    case GSI_SEQUENCE_TAG: {
      sequence_element_cnt = gsi_element_count_of (gsiitem);
      if (fulldebug) printf ("# of elements in sequence = %d\n", sequence_element_cnt);

      sequence_values = (gsi_item*)(gsi_elements_of (gsiitem));
      obj = create_java_sequence_from_gsiitems (env , sequence_values, sequence_element_cnt);
      if (java_class) *java_class = sequenceClassInfo->clazz;
     
      return obj;
    }
     case GSI_STRUCTURE_TAG: {
      if (java_class) *java_class = structureClassInfo->clazz;
      break;
    }   
    default: 
      {
      handle = gsi_handle_of (gsiitem);
      if (handle != 0) {
	  gsi_registration regn;
	  regn = gsi_registration_of (handle, gsi_current_context ());
	  class_symbol =  gsi_class_name_of(regn);  
      }
      else {
	class_symbol =  gsi_class_name_of(gsiitem);
      }


      /* Get the G2 class Name for this gsiitem as a java Symbol */
      java_class_symbol = java_intern_from_gsi_symbol (env, class_symbol, noneSymbol);

      if (handle == 0) {
	/* Check for any known G2 classes if we are a by-copy */
	obj = convert_java_object_from_known_g2_classes (env, 
							 gsiitem, 
							 java_class_symbol, 
							 java_class);
      }

      if (obj)
	return obj;
      
      /* Check for array types */
      array_contents = NULL;
      element_type = NULL;
      if (is_array_type(item_type)) {

	  jboolean is_proxy = JNI_FALSE;
	  array_contents =  create_java_array_from_gsi_array( env , 
							      gsiitem, 
							      java_class,
							      &element_type,
							      &is_proxy);

	  /* The array may have been converted to a raw Java Array type (only for by-copy case)*/
	  /* in which case, we must finish here and return the generated object */
	  if (!is_proxy && handle == 0)
	    return array_contents;
	 
	}

      /* Check for list types */
      list_sequence = NULL;
      if (is_list_type(item_type)) {
	
      	  list_sequence = create_java_sequence_from_gsi_list( env , 
							      gsiitem,
							      &element_type);

      }

      /* If the G2 object is a variable-or-parameter then it will */
      /* have a value, that represents the LAST-RECORDED-VALUE    */
      /* attribute in the G2 object */

      value_attr = NULL;
      if (is_simple_value_type (item_type)) {
      
	jclass clazz;

	value_attr = create_java_object_from_gsiitem (env ,
						      gsiitem,
						      &clazz,
						      JNI_FALSE,
						      JNI_TRUE);

	/* Note the JNI_TRUE in the above call, is to stop an endless loop
	 * in that this gsiitem is an item, but also has a value Tag
	 * create_java_object_from_gsiitem would recall this proc if
	 * we didnot tell it to ignore complex item checking, as we are only intersted in 
	 * the value part
	 */

	if (value_attr)  {
	  /* Any History */
	  /* set_java_history_from_gsi_history(env, gsiitem, java_g2proxy); */
	}
      }

      /* printf("registration is %lx %lx\n", gsi_registration_of_item(gsiitem), gsiitem); */
      

      if (fulldebug) 
	{
	  char *class_str_utf;
	  gsi_char *class_str = gsi_symbol_name(class_symbol);  
#ifdef GSI_USE_WIDE_STRING_API
	  class_str_utf = (class_str ? jgi_unicode2str(class_str) : NULL);
#else
	  class_str_utf = (class_str ? class_str : NULL);
#endif
	  printf ("USING >>>NEW<<< ITEM CLASS MAPPING...");
	  printf ("  item is of class: %s and Tag = %d\n", (class_str_utf ? class_str_utf : "NO CLASS NAME"),
		  gsi_type_of (gsiitem));
	  printf ("    just for kicks: handle = %d\n", handle);
	  printf ("    Registration from item = %lx\n", gsi_registration_of_item (gsiitem));
	  printf ("    Registration from handle = %lx\n",
		  gsi_registration_of (handle, gsi_current_context ()));

#ifdef GSI_USE_WIDE_STRING_API
	    if (class_str_utf)
	      free((char *)class_str_utf);
#endif
	}
      
      if (fulldebug) {printf ("Will create ITEM later!\n"); fflush (stdout);}
      break;
    }
    
    } /* switch */
  
    struct_items = gsi_attrs_of(gsiitem);
    struct_count = gsi_attr_count_of(gsiitem);

    total_attr_cnt = struct_count;

    /* We need to add other attributes, if structure is destined for a G2 Item attributes */

    /* Bug HQ-5025755 "Javalink doesn't handle registered items right when receiving data" */
    itemreg = gsi_registration_of_item(gsiitem);
    if (itemreg == NULL) {
      name_symbol = gsi_name_of(gsiitem);
    } else {
      name_symbol = gsi_name_of(itemreg);
    }
    if (item_type != GSI_STRUCTURE_TAG) {
      if (name_symbol)       total_attr_cnt++;
      if (java_class_symbol) total_attr_cnt++;
      if (array_contents)    total_attr_cnt += 2; /* 1 for elements + 1 for element-type */
      else if (list_sequence) total_attr_cnt += 2; /* 1 for list + 1 for element-type */
      if (value_attr)        total_attr_cnt++;
    }

    if (fulldebug) {printf("About to create arrays for attrname and attrvalues \n"); fflush(stdout);}
    
    attrnames = (*env)->NewObjectArray(env, (jsize)total_attr_cnt, symbolClassInfo->clazz, NULL );
    attrvalues = (*env)->NewObjectArray(env, (jsize)total_attr_cnt, objectClassInfo->clazz, NULL );

    if (fulldebug) {printf("After created arrays for attrnames and attrvalues \n"); fflush(stdout);}

    if ((attrnames == NULL) || (attrvalues == NULL))
      return NULL;

    if (fulldebug) {
      printf("After created arrays for attrnames and attrvalues \n");
      printf("Found %d attributes before adding item attributes \n", struct_count );
    }

    /* Add known attributes to the Structure, but only if we are going to be an Item */
    start_pos = 0;
    if (item_type != GSI_STRUCTURE_TAG) {

      if (name_symbol) {
	java_name_symbol = java_intern_from_gsi_symbol (env, name_symbol , noneSymbol);
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, namesSymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, java_name_symbol);
	start_pos++;
      }

      /* We must add the G2 CLASS NAME to the Item's attributes, so that its all set up */
      /* just in case it is sent back to G2 */
      if (java_class_symbol) {
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, classSymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, java_class_symbol);
	start_pos++;
      }

      if (value_attr) {
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, lastRecordedValueSymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, value_attr);
	start_pos++;
      }

      /* Add the array contents as the hidden array symbol */
      if (array_contents) {
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, hiddenG2ArraySymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, array_contents);
	if (fulldebug) {printf("create_java_object_from_complex_gsiitem:  Deleting array_contents.\n");fflush(stdout);}
	(*env)->DeleteLocalRef(env,array_contents);
	start_pos++;
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, elementTypeSymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, element_type);
	start_pos++;
      }
      else if (list_sequence) {
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, g2ListSequenceSymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, list_sequence);
	if (fulldebug) {printf("create_java_object_from_complex_gsiitem:  Deleting list_seq.\n");fflush(stdout);}
	(*env)->DeleteLocalRef(env,list_sequence);
	start_pos++;
	(*env)->SetObjectArrayElement(env, attrnames, start_pos, elementTypeSymbol);
	(*env)->SetObjectArrayElement(env, attrvalues, start_pos, element_type);
	start_pos++;
      }

    }
        
    /** NOTE IT IS ASSUMED THAT, ITEMIMPL WILL RECORD THE CLASS NAME **/
    
    if (struct_count > 0)
    {
      gsi_attr *gsi_attributes = struct_items;
      gsi_item *gsi_attribute_item;
      gsi_symbol gsi_attribute_name;
      jobject  attribute_value, attribute_name;
      int       i = 0;
      jclass    clazz;
      
      for (i = 0; i<struct_count ; i++)
	{
	  gsi_attribute_item = gsi_item_of_attr(gsi_attributes[i]);
	  gsi_attribute_name = gsi_attr_name_of(gsi_attributes[i]);
	  
	  
	  if (!gsi_attribute_name)
	    fprintf (stderr, "Error in attribute name (%lX)  NULL POINTER!\n", 
		     gsi_attribute_name);
	  else
	    {

	      attribute_name  = java_intern_from_gsi_symbol (env, gsi_attribute_name, noneSymbol);
	      if (fulldebug)
		{
#ifdef GSI_USE_WIDE_STRING_API
		  char *gsi_attribute_name_utf = 
		    jgi_unicode2str(gsi_symbol_name(gsi_attribute_name));
		  if (gsi_attribute_name_utf) 
		    {
		      printf("Attribute %d name %s item type %d \n", 
				i, 
			        gsi_attribute_name_utf, 
			        gsi_type_of(gsi_attribute_item) );
		      free((char *)gsi_attribute_name_utf);
		    }
#else
		  printf("Attribute %d name %s item type %d \n", 
				i, 
			        gsi_attribute_name, 
			        gsi_type_of(gsi_symbol_name(gsi_attribute_item)) );
#endif
		}

	  
	      /* All item and values get wrapped as Java Objects for attribute values */
	      if (gsi_attribute_item)
		attribute_value = create_java_object_from_gsiitem 
		  (env ,gsi_attribute_item, &clazz, JNI_FALSE, JNI_FALSE);
	  
	      (*env)->SetObjectArrayElement(env, attrnames, i+start_pos, attribute_name);
	      (*env)->SetObjectArrayElement(env, attrvalues, i+start_pos, attribute_value);

	    }
	 
	}
    }

    if (fulldebug)
      {fprintf (stdout, "Creating new Structure.\n"); fflush (stdout);}

    attributes = (*env)->NewObject(env, 
				 structureClassInfo->clazz, 
				 structureClassInfo->init_MethodID, 
				 attrnames, 
				 attrvalues,
				 (jint)total_attr_cnt);

    if (fulldebug)
      jgi_describeJavaObject (env, attributes);

    if (item_type == GSI_STRUCTURE_TAG)
      return attributes;

    if (fulldebug)
      {fprintf (stdout, "Handling item creation.\n"); fflush (stdout);}

 
      {      

	/* If we are here GSI has passed an item, by copy or handle */

	ContextData context_data = jgi_get_context_object(env, gsi_current_context());
	if (fulldebug)
	  fprintf (stdout, "Context Data = %lx (%lx)\n", context_data, JREF(context_data)); fflush (stdout);

	if (context_data) {
	  java_g2proxy = (*env)->CallObjectMethod(env,
				       JREF(context_data),
				       context_data->createStub_MethodID,
				       java_class_symbol,
				       handle,
				       JREF(context_data),
				       attributes,
				       incompleteStubConversion);
	 
	  if (java_class) *java_class = (*env)->GetObjectClass(env, java_g2proxy);

	  if ((*env)->IsInstanceOf (env, java_g2proxy, remoteRPCThreadClassInfo->deferredStubClass)) {
	    /*printf ("This item was not created properly. A deferred stub was received.\n");*/
	    /*fflush (stdout);*/
	    incompleteStubConversion = 1;
	  }
	  if (fulldebug)
	    { printf ("Finished creating stub for java! = %lx\n", java_g2proxy);
	      if (java_g2proxy) {
		jgi_describeJavaObject (env, java_g2proxy);
		fflush (stdout);}
	    }
	} else {
	  fprintf (stderr, "Cannot find context_data. Quitting!");
	  exit (1);
	}
      }

    if (convdebug)
      {
	printf ("Exiting create_java_object_from_complex_gsiitem.\n \n"); fflush (stdout);
      }
    
    return java_g2proxy;
}




jobject create_java_sequence_from_gsiitems (JNIEnv *env,
					     gsi_item  *sequence_values,
					     int sequence_element_cnt)
{

  jarray element_data;
  int i;
  gsi_item *sequence_value;
  jobject obj;
  gsi_int type;
  jobject sequence;
  jclass clazz;

  if (convdebug) { printf ("Entering create_java_sequence_from_gsiitems.\n"); fflush (stdout);}
  
  sequence = (*env)->NewObject(env , 
			       sequenceClassInfo->clazz ,
			       sequenceClassInfo->init_MethodID, 
			       sequence_element_cnt);

  element_data = ( *env )->GetObjectField(env , sequence , sequenceClassInfo->elementData_FieldID);
 
  for (i=0; i<sequence_element_cnt; i++) {
    sequence_value = sequence_values[i];
    type = gsi_type_of(sequence_value);

    if (fulldebug) 
      printf ("  Sequence item # %d => Tag = %d (Simple = %d).\n", 
	      i, type, is_simple_value_type(type));

    obj = create_java_object_from_gsiitem (env ,
					   sequence_value, 
					   &clazz, 
					   JNI_FALSE,
					   JNI_FALSE);

    (*env)->SetObjectArrayElement(env, element_data, i, obj );
    if (type != GSI_LOGICAL_TAG && type != GSI_SYMBOL_TAG && type != GSI_INTEGER_TAG) {
      if (fulldebug) {printf("create_java_sequence_from_gsiitems: Deleting local ref for %lx (unless simple tag).  Item type is %d\n", obj,gsi_type_of(sequence_value)); fflush(stdout);}
      (*env)->DeleteLocalRef(env, obj);
    }
  }

  /* We must set the Sequence Size */
  (*env)->SetIntField(env, sequence, sequenceClassInfo->elementCount_FieldID, sequence_element_cnt);
                                              
  /* (*env)->CallVoidMethod(env, 
 		 sequence,
  		 sequenceClassInfo->print_MethodID ); */
  

  if (fulldebug) {printf("create_java_sequence_from_gsiitems: Deleting local ref for element_data\n"); fflush(stdout);}  
  (*env)->DeleteLocalRef(env, element_data);

  if (convdebug){ printf ("Exiting create_java_sequence_from_gsiitems.\n"); fflush (stdout);}

  return sequence;
}




jobject create_java_object_from_gsiitem (JNIEnv *env , 
					 gsi_item gsiitem, 
					 jclass *java_class,
					 jboolean use_primitive_types,
					 jboolean is_simple_type)
{
  jobject obj = NULL;
  gsi_int item_type = gsi_type_of(gsiitem);
  /* Set use_primitive_types if class entries for primitive types are required 
   * G2 INTEGER -> int rather than Integer
   * G2 FLOAT -> double rather than Double
   * G2 TRUTH-VALUE -> boolean rather than Boolean
   */

  /* Set is_simple_type true if you want to ignore complex checking 
   * this could occur when a item gsiitem type, has a value part which
   * only needs converting by checking its basic tags
   */

  if (convdebug) {printf("Function create_java_object_from_gsiitem \n "); fflush (stdout);}

  if (fulldebug) {
    printf ("  creating java object for item with type tag = %d.\n", item_type);
    fflush (stdout);
  }

  /* When a Gsi Item is an ITEM it may not have GSI_ITEM_TAG set as type !   */
  /* we therefore check for the item specfically before the type case below  */
  if ( !is_simple_type &&
       (gsi_is_item(gsiitem) || 
	is_array_type(item_type) || 
	is_list_type(item_type) || 
        is_compound_value_type(item_type)  || 
	(gsi_handle_of(gsiitem) >0))) 
    {

      /* we must now create a Java GsiObjects that reflects */
      /* information from the gsi_item data structure */    

      obj = create_java_object_from_complex_gsiitem (env ,
						     gsiitem, 
						     java_class);
      if (fulldebug) {printf("Unpacked Complex gsiitem->Java (%lx)\n", obj); fflush(stdout);}
    }
  else
    switch (item_type) 
    {
    case GSI_INTEGER_TAG: {

      obj = jgi_getJavaInteger(env, (jint)gsi_int_of(gsiitem) );

      if (use_primitive_types)
	{ if (java_class) *java_class = integerClassInfo->intType_clazz; }
      else
	{ if (java_class) *java_class = integerClassInfo->clazz; }
      
      if (fulldebug) {printf("\nUnpacked gsi_int to Integer %d \n",gsi_int_of(gsiitem)); fflush(stdout);}

      break;
    }
    case GSI_FLOAT64_TAG: {
      
      obj = (*env)->NewObject(env , 
			      doubleClassInfo->clazz, 
			      doubleClassInfo->init_MethodID, 
			      gsi_flt_of(gsiitem));

      if (use_primitive_types)
	{ if (java_class) *java_class = doubleClassInfo->doubleType_clazz; }
      else
	{ if (java_class) *java_class = doubleClassInfo->clazz; }
      
      if (fulldebug) {printf("\nUnpacked gsi_flt to Double is %f \n", gsi_flt_of(gsiitem)); fflush(stdout);}
      break;
    }

    case GSI_UNSIGNED_SHORT_VECTOR_TAG: {
      
      gsi_int usv_size = gsi_usv_length_of(gsiitem);
      unsigned short *data_values = gsi_usv_of(gsiitem);

      /* The gsi item is a UNSIGNED_SHORT_VECTOR map to java char[] */
      if (java_class) *java_class = characterClassInfo->characterTypeArray_clazz;
      obj = (*env)->NewCharArray(env, usv_size);  

      if (data_values)
	    /* vvvwommmmmmm....fast Copy */
	    (*env)->SetCharArrayRegion(env, obj, 0, usv_size, data_values);

      if (fulldebug) {
	int i;
	unsigned short element;
	printf("\nUnpacked usv to char[] \n");
	for (i = 0; i < usv_size; i++)
	  {
	    element = data_values[i];
	    printf("char[%d] = %x%x%x%x \n",
		   i, element>>12,(element>>8)&0xf,
		   (element>>4)&0xf,element&0xf);
	  }
      }
      break;
    }
			      
    case  GSI_SYMBOL_TAG:  {
      gsi_symbol sym = gsi_sym_of(gsiitem);

      obj = java_intern_from_gsi_symbol (env, sym, noneSymbol);


      if (java_class) *java_class = symbolClassInfo->clazz;
     
      if (fulldebug) 
	{
#ifdef GSI_USE_WIDE_STRING_API
	  char *sym_str = jgi_unicode2str(gsi_symbol_name(sym));
	  if (sym) {
	    printf("\nUnpacked gsi_symbol and interned Symbol is %s \n", sym_str);
	    free((char *)sym_str);
	  }
#else
	  printf("\nUnpacked gsi_symbol and interned Symbol is %s \n", gsi_symbol_name(sym));
#endif
	}
      break;
    }
    case GSI_STRING_TAG: {
      gsi_char *str = gsi_str_of(gsiitem);

      obj = jgi_NewString(env, str);

      if (java_class) *java_class = stringClassInfo->clazz;

      if (fulldebug) 
	{
#ifdef GSI_USE_WIDE_STRING_API
	  char *str_str = jgi_unicode2str(gsi_str_of(gsiitem));
	  if (str_str) {
	    printf("\nUnpacked wide gsi_str to String is %s \n", str_str);
	    free((char *)str_str);
	  }
#else
	  printf("\nUnpacked gsi_str to String is %s \n", str);
#endif
	}
      break;
    }
    case GSI_LOGICAL_TAG: {
      long b = (long)gsi_log_of(gsiitem);
      if (b > 0) 
	obj = booleanClassInfo->Boolean_TRUE; 
      else 
	obj = booleanClassInfo->Boolean_FALSE;

      if (use_primitive_types)
	{ if (java_class) *java_class = booleanClassInfo->booleanType_clazz; }
      else
	{ if (java_class) *java_class = booleanClassInfo->clazz; }
        
      if (fulldebug) {printf("\nUnpacked GsiLog is %d \n", b); fflush(stdout);}
      break;
    }
    case GSI_NULL_TAG:

      /* Ignore nulls*/

      if (fulldebug) {printf("\nUnpacked GSI_NULL_TAG ignoring \n"); fflush(stdout);}
 
       break;
       
    default:
      fprintf(stderr, "\n Error in create_java_object_from_gsiitem Unknown Arg type \n");
      *java_class = NULL;
    } /* end switch */
    
    if (convdebug) { printf ("Exiting create_java_object_from_gsiitem.\n \n"); fflush (stdout);}

    return obj;

} /* end create_java_gsi_object_from_gsiitem */
