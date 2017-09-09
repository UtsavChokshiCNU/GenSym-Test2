/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      jni_gi_javaconv.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               1-MAR-1997   M.D.Gribble
 +
 + Description:  This file contains various utility and conversion
 +		 functions for converting Java types and objects
 +               to gsi items
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

#define CHECK_INT_FITS_INTO_G2_INTEGER(VALUE,CLASS) \
    if (VALUE > MAX_G2_INTEGER || VALUE < MIN_G2_INTEGER) \
      {\
	char *msg = (char*)malloc(132);\
	sprintf(msg, "Java tried to send a %s(=%d) that does not fit into a 30 bit G2 Integer",CLASS,VALUE);\
	THROW_G2COMS_EXCEPTION(env, msg);\
	free(msg);\
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





/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Java Objects to GsiItems Converters
 %
 % Description:
 %   
 %		This function group converts or creates GsiItems data structures 
 %              from Java Objects
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
 *   set the history keeping spec and values for a gsi item
 *   from the java object to which it maps
 */
void  set_gsi_history_from_java_history(JNIEnv *env, gsi_item arg ,  jobject java_g2proxy)
{
  gsi_int   history_count, max_count, max_age, min_interval, history_type;
  
  void *values; 
  int historyTagOk = 1;
  double   *timestamps;
  int      i;
  gsi_int context = gsi_current_context();
  int *free_indies_array; 
  
  gsi_int array_count;
  /*************************WARNING*************************************** 
   * jobject_array indexed by actual value NOT #defined variable         *
   * Changes to HistorySpec.java may need to be managed here as well     *
   **********************************************************************/
  jobjectArray jvalues_array;
  
  jobjectArray jobject_array; /* holds the history values */
  jdoubleArray jdouble_array; /* holds the time stamps */
  
  jobject element;
  
  jclass javaHistoryClass ;
  
  jclass clazz = objectClassInfo->clazz;
  /* vars end */
  
  if (fulldebug)printf("in set_gsi_history_from_java_history \n");
  
  jobject_array = (jobjectArray)
    (*env)->CallObjectMethod( env, java_g2proxy,
			      g2ItemProxyClassInfo->getHistory_MethodID
			      );
  
  if (jobject_array)
    {
      /*
	  array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)jobject_array));
      */
      /*************************WARNING************************************ 
       * jobject_array indexed by actual value NOT #defined variable       *
       * Changes to HistorySpec.java may need to be managed here as well   *
       ********************************************************************/
      /* History_count is the first element in the returned array*/
      history_count =   (*env)->CallIntMethod(env,
			   (*env)->GetObjectArrayElement(
				   env , jobject_array,(jsize) 0),  
				   integerClassInfo->intValue_MethodID);	
      
      /*************************WARNING************************************ 
       * jobject_array indexed by actual value NOT #defined variable       *
       * Changes to HistorySpec.java may need to be managed here as well   *
       ********************************************************************/
      /*max_count is the second element in the returned arra */
      max_count =	(*env)->CallIntMethod(env,
			   (*env)->GetObjectArrayElement(env , jobject_array,(jsize) 1), 
			   integerClassInfo->intValue_MethodID);
      
      /*************************WARNING************************************ 
       * jobject_array indexed by actual value NOT #defined variable       *
       * Changes to HistorySpec.java may need to be managed here as well   *
       ********************************************************************/
      /*max_age of history is the third element of the returned array*/
      max_age =		(*env)->CallIntMethod(env,
			    (*env)->GetObjectArrayElement(env , jobject_array,(jsize) 2), 
			    integerClassInfo->intValue_MethodID);
      
      /*************************WARNING************************************ 
       * jobject_array indexed by actual value NOT #defined variable      *
       * Changes to HistorySpec.java may need to be managed here as well  *
       ********************************************************************/
      /*min_interval between history is the fourth element of the returned array*/
      min_interval =	(*env)->CallIntMethod(env,
			     (*env)->GetObjectArrayElement(env , jobject_array,(jsize) 3), 
			     integerClassInfo->intValue_MethodID);
      
      /*************************WARNING************************************* 
       * jobject_array indexed by actual value NOT #defined variable       *
       * Changes to HistorySpec.java may need to be managed here as well   *
       ********************************************************************/
      /*the type of history is returned in the fifth element of the array*/
      javaHistoryClass = (*env)->GetObjectArrayElement(env , jobject_array,(jsize) 4);
      
      /*************************WARNING************************************* 
       * jobject_array indexed by actual value NOT #defined variable       *
       * Changes to HistorySpec.java may need to be managed here as well   *
       ********************************************************************/
      /*time_stamps are held as date objects injava and returned here as an array
	at the sixth element of the array*/ 
      jdouble_array = (*env)->GetObjectArrayElement(env , jobject_array,(jsize) 5);
      
      /*
	array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)jdouble_array));
	*/
      
      array_count = history_count;
      
      if (fulldebug)printf(" Okay we have %d time stamps from Java  \n",history_count);
      
      /* add time to an array to go back to G2 */
      
      timestamps = (double *)malloc(array_count*sizeof(double));
      
      for (i = 0 ; i < history_count;i++)
	{
	  timestamps[i] = (*env)->CallDoubleMethod(env,
				 (*env)->GetObjectArrayElement(env ,jdouble_array ,(jsize) i), 
				 doubleClassInfo->doubleValue_MethodID);

	}


      /*************************WARNING************************************ 
       * jobject_array indexed by actual value NOT #defined variable      *
       * Changes to HistorySpec.java may need to be managed here as well  *
       *******************************************************************/
      /* now get the historical data values returned as an array of objects at the 
	 seventh element of the array*/
      jvalues_array = (*env)->GetObjectArrayElement(env , jobject_array,(jsize) 6);
      
      if (jvalues_array)
	{	
	  
	    array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)jvalues_array));

	  
	  /* decode history_class to history_type*/
	  if ((*env)->IsAssignableFrom (env, javaHistoryClass, integerClassInfo->clazz))  {
   	    gsi_int *int_array =  (gsi_int *)malloc(sizeof(int) * history_count);
	    history_type = GSI_INTEGER_TAG;
	

  
	    if (int_array)
	      {
		for (i=0; i<history_count ; i++) 
		  {

		    int_array[i] =	(*env)->CallIntMethod(env,
					    (*env)->GetObjectArrayElement(env , jvalues_array,(jsize) i), 
					    integerClassInfo->intValue_MethodID);

		  }
		values = (void *) int_array;
	      }
	    else
	      {
		fprintf(stderr, "\n Memory exhausted \n");
		historyTagOk = 0;
	      }
	  } else if ((*env)->IsAssignableFrom (env, javaHistoryClass, symbolClassInfo->clazz))  {
	    gsi_symbol *sym_array = (gsi_symbol *)malloc(history_count * sizeof(gsi_symbol));
	    gsi_char *str;
	    jstring vobj;
	    history_type = GSI_SYMBOL_TAG;

	    if (sym_array) 
	      {
		
		for (i = 0; i < history_count; i++)
		  {
		    /* Get the String representing the Java String */
		    vobj = (jstring)(*env)->CallObjectMethod(env,
							     (*env)->GetObjectArrayElement(env, jvalues_array, (jsize)i),
							     symbolClassInfo->getPrintValue_MethodID);
		    
		    if (vobj) 
		      {						   
			str = jgi_GetStringChars(env, (jstring)vobj);
			if(str)
			  {
			    sym_array[i] = gsi_make_symbol(str);
			    if (fulldebug) 
			      {
				printf("Element [%i]=", i);
				jgi_printStr(str);
				printf("\n");
			      }
			    free((char *)str);
			  }
		      }
		    else
		      sym_array[i] = gsi_make_symbol(null_str);
		  }
		values = (void *) sym_array;
	      }
	    else
	      {
		fprintf (stderr, "Memory exhausted .");
		fflush  (stderr);
		historyTagOk = 0;
	      }
	    /*getPrintValue_MethodID*/
	    
	  }				 
	  else if ((*env)->IsAssignableFrom (env, javaHistoryClass, stringClassInfo->clazz))  {
	    gsi_char **str_array = (gsi_char **)malloc(history_count * sizeof(gsi_char *));
	    jstring vobj;
	    free_indies_array = (int *)malloc(history_count * sizeof(int));
	    history_type = GSI_STRING_TAG;
	    if (str_array) 
	      {
		for (i = 0; i < history_count; i++)
		  {
		    /* Get the String representing the Java String */
		    vobj = (*env)->GetObjectArrayElement(env, jvalues_array, (jsize)i);
		    if (vobj) 
		      {						   
			str_array[i] = jgi_GetStringChars(env, vobj);
			free_indies_array[i] = TRUE;
			if (fulldebug) 
			  {
			    printf("Element [%i]=", i);
			    jgi_printStr(str_array[i]);
			    printf("\n");
			  }
		      }
		    else 
		      {
			free_indies_array[i] = FALSE;
			str_array[i] = null_str;
		      }
		  }
		values = (void *) str_array;
	      }
	    else
	      {
		fprintf (stderr, "Memory exhausted .");
		fflush  (stderr);
		historyTagOk = 0;
	      }
	  }
	  else if ((*env)->IsAssignableFrom (env, javaHistoryClass, booleanClassInfo->booleanType_clazz))  {
	    gsi_int *bool_array = (gsi_int*)malloc(history_count * sizeof(gsi_int));	
	    history_type = GSI_LOGICAL_TAG;
	    if (bool_array)
	      {
		for (i = 0; i < history_count; i++) {
		  element = (*env)->GetObjectArrayElement(env, jvalues_array, i);
		  if ((*env)->IsInstanceOf(env, element, booleanClassInfo->clazz))
		    bool_array[i] = ((*env)->CallBooleanMethod(env,
							       element,
							       booleanClassInfo->booleanValue_MethodID) 
				     ? 1000 : -1000);
		  else
		    bool_array[i] = 0;
		  
		  
		  if (fulldebug) {
		    printf("=== bool_array[%d]=%d\n",i,bool_array[i]);
		  }
		}
		
		values = (void *) bool_array;
		
	      }
	    else
	      {
		fprintf(stderr, "\n Memory exhausted \n");
		historyTagOk = 0;
	      }
	    
	    /*booleanValue_MethodID	*/
	  }
	  else if ((*env)->IsAssignableFrom (env, javaHistoryClass,doubleClassInfo->doubleType_clazz))  {
	    double *dbl_array = (double*)malloc(history_count * sizeof(double));
	    history_type = GSI_FLOAT64_TAG;
	    if (dbl_array)
	      {
		for (i = 0; i < history_count; i++) 
		  {
		    element = (*env)->GetObjectArrayElement(env, jvalues_array, i);
		    if ((*env)->IsInstanceOf(env, element, doubleClassInfo->clazz))
			{
		      dbl_array[i] = (*env)->CallDoubleMethod(env,
							      element,
							      doubleClassInfo->doubleValue_MethodID);
			}
			else
			{
				dbl_array[i] = 0.0;
			}
		  }
		values = (void *) dbl_array;
	      }
	    else
	      {
		fprintf(stderr, "\n Memory exhausted \n");
		historyTagOk = 0;
	      }	
	  }
	    
	  else if ((*env)->IsAssignableFrom (env, javaHistoryClass, numberClassInfo->clazz))  {
	    
	    gsi_item *elements = gsi_make_array(history_count);
	    history_type = GSI_QUANTITY_TAG;
	    if (elements)
	      {
		for (i = 0; i < history_count; i++) 
		  {
		    element = (*env)->GetObjectArrayElement(env, jvalues_array, i);
		    
		    if (element) 
		      convert_java_object_to_gsiitem (env, element, &(elements[i]), context);
		    else 
		      {
			elements[i] = gsi_make_item();
			gsi_set_int(elements[i], 0);
		      }
		    
		  }
		values = (void *) elements;
	      }
	    else
	      {
		fprintf(stderr, "\n Memory exhausted \n");
		historyTagOk = 0;
	      }	
	  }
	  else {
	    fprintf(stderr, "\n Error setting history - TAG not recognised \n");
	    historyTagOk = 0;
	  }
	  
	  if ( historyTagOk == 1 ){
	    /* call to gsi to set the history keeping spec */
	    /* & values in the G2 obj to be returned       */
	    
	    
	    if (fulldebug)
	      {
		printf("\n** Function  set_gsi_history_from_java_history total size(%d)>>\n",array_count);
		printf("there are %d values currently in history whose spec (%d) permits them",history_count, history_type);
		printf(" at intervals of %d milliseconds or greater and allows for ",min_interval);
		if (max_count) {
		  printf("%d historical values",max_count);
		  if (max_age) {
		    printf(" no more than %d seconds old.  \n",max_age); }
		  else {
		    printf(". "); } } 
		else {
		  printf("historical values no more than %d seconds old.  \n",max_age); }
	      }
	    
	    
	    gsi_set_history(arg,
				values,
				timestamps,  
				history_count,
				history_type, /*pass the jclass*/
				max_count,
				max_age,	
				min_interval);
	    
	    /* take out my own trash */
	    if (history_type  == GSI_STRING_TAG && free_indies_array)
	      {
		char **str_array = (char **)values;
		/* We have to clear up string arrays */
		for (i = 0; i<history_count; i++)
		  {
		    if (free_indies_array[i])
		      free((char *)str_array[i]);
		  }
		free((char *)free_indies_array);
	      }
	    
	    /* We dont free mixed type history arrays, as gsi_set_history does
	       not copy these...They will be reclaimed after they have been sent by GSI
	       else where */
	    if (history_type != VALUE_TAG && history_type !=  QUANTITY_TAG)
	    {
	      if (values) free((char *)values);
	    }
		
	  }
	  else
	    {
	      fprintf(stderr, "\n Failed to set gsi history form java object \n");
	    }
	}
      else 
	{
	  if (fulldebug) {printf(" HAVE a history problem from Java  \n"); fflush(stdout);}	
	}
      
      if(timestamps) free((char *)timestamps);
      
    }  /* end of if jobr-array */
  else if (fulldebug) {printf(" HAVE no history from Java  \n"); fflush(stdout);}
  
  
} /* end  set_gsi_history_from_java_history */




int convert_primitive_java_value_to_gsiitem (JNIEnv *env,
					      jvalue java_value,
					      char *signature,
					      gsi_item gsiitem )
					      
{
int java_item_status = JAVA_ITEM_OK;

  if (convdebug) {printf("Function convert_primitive_java_value_to_gsiitem \n"); fflush (stdout);}
 

  switch (signature[0]) {
  case JAVA_BOOLEAN_SIGNATURE_CHAR:
    gsi_set_log (gsiitem, (gsi_int)((java_value.z) == 1L ? 1000 : -1000));

    if (fulldebug) printf ("  Packing Logical : %s.\n", (java_value.z ? "TRUE" : "FALSE"));
    break;
  case JAVA_CHAR_SIGNATURE_CHAR: {
    gsi_char str[2];
    str[0] = (gsi_char)java_value.c;
    str[1] = (gsi_char)0;
    gsi_set_str (gsiitem, str);

    if (fulldebug) printf ("  Packing char : %c.\n", java_value.c);
    break;
  }
  case JAVA_BYTE_SIGNATURE_CHAR:
    gsi_set_int (gsiitem, (gsi_int)java_value.b);
    if (fulldebug) printf ("  Packing byte : %d.\n", java_value.b);
    break;
  case JAVA_SHORT_SIGNATURE_CHAR:
    gsi_set_int (gsiitem, (gsi_int)java_value.s);
    if (fulldebug) printf ("  Packing short : %d.\n", java_value.s);
    break;
  case JAVA_INT_SIGNATURE_CHAR:
    gsi_set_int (gsiitem, (gsi_int)java_value.i);
     if (fulldebug) printf ("  Packing int : %d.\n", java_value.i);
    break;
  case JAVA_LONG_SIGNATURE_CHAR:
    gsi_set_int (gsiitem, (gsi_int)java_value.j);
     if (fulldebug) printf ("  Packing long : %d.\n", java_value.l);
    break;
  case JAVA_FLOAT_SIGNATURE_CHAR:
    gsi_set_flt (gsiitem, (double)java_value.f);
    if (fulldebug) printf ("  Packing float : %f.\n", java_value.f);
    break;
  case JAVA_DOUBLE_SIGNATURE_CHAR:
    gsi_set_flt (gsiitem, (double)java_value.d);
    if (fulldebug) printf ("  Packing double : %f.\n", java_value.d);
    break;
  default:
    java_item_status = JAVA_ITEM_BAD;
  }

  return java_item_status;
}

gsi_item get_g2javatype_gsiitem(JNIEnv *env,
			 gsi_item parent_gsiitem,
			 gsi_symbol g2_type_classname) {

  gsi_attr *gsi_attributes_array;
  gsi_item val_gsi_item = gsi_make_item();
  gsi_set_type (parent_gsiitem, GSI_NULL_TAG);
  gsi_set_class_name (parent_gsiitem, g2_type_classname);
  gsi_attributes_array = gsi_make_attrs (1);
  gsi_set_attr_name (*gsi_attributes_array, g2_javatype_class_val_attr_gsisymbol);
  gsi_set_item_of_attr (*gsi_attributes_array, val_gsi_item);
  gsi_set_attrs (parent_gsiitem, gsi_attributes_array, 1);
  return val_gsi_item;
}

int convert_simple_java_object_to_gsiitem (JNIEnv *env ,
					    jobject obj, 
					    jboolean set_class,
					    jobject array_element_type,
					    gsi_item gsiitem,
					    gsi_int context)
{
  int java_item_status = JAVA_ITEM_OK;

  /* Note parent_java_obj is used to further distinguish return Tag types */

  if (convdebug) {printf("Function convert_simple_java_object_to_gsiitem \n"); fflush (stdout);}

  if ((*env)->IsInstanceOf (env, obj, integerClassInfo->clazz))  {

    int v = (*env)->CallIntMethod(env,
				  obj, 
				  integerClassInfo->intValue_MethodID);

    if (v > MAX_G2_INTEGER || v < MIN_G2_INTEGER) {
      char *msg = (char*)malloc(132);
      sprintf(msg, "Java tried to send an int (=%d) that does not fit into a 30 bit G2 Integer",v);
      THROW_G2COMS_EXCEPTION(env, msg);
      free(msg);
      java_item_status = JAVA_ITEM_BAD_ALREADY_THREW;
      if (fulldebug) printf ("  Received too-big integer %d, packing MAX_G2_INTEGER (%d) instead.\n", v, MAX_G2_INTEGER);
      gsi_set_int (gsiitem, (gsi_int)MAX_G2_INTEGER);
    } else {
      gsi_set_int (gsiitem, (gsi_int)v);
      if (fulldebug) printf ("  Packing Integer to INTEGER %d.\n", v);
    }
  } else if ((*env)->IsInstanceOf (env, obj, longClassInfo->clazz))  {
    gsi_item val_gsi_item = get_g2javatype_gsiitem(env, gsiitem, g2_javalong_classname_gsisymbol);
    jstring v = (*env)->CallObjectMethod(env,
					 obj, 
					 longClassInfo->toString_MethodID);
    gsi_char *vstr = jgi_GetStringChars(env, v); 

    gsi_set_str(val_gsi_item, vstr);
    if (vstr) free((char*) vstr);
    if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: deleting local ref to v for long class info\n");fflush(stdout);}
    (*env)->DeleteLocalRef(env, v);
    if (fulldebug) 
      {
#ifdef GSI_USE_WIDE_STRING_API	
	char *str_utf = jgi_unicode2str(vstr);
#else
	char *str_utf = vstr;
#endif
	printf ("  Packing long to %s : %s.\n", G2_JAVALONG_CLASSNAME, str_utf);
	
#ifdef GSI_USE_WIDE_STRING_API
	if (str_utf) free(str_utf);
#endif
      }
    
  } else if ((*env)->IsInstanceOf (env, obj, shortClassInfo->clazz))  {
    /* gsi_item val_gsi_item = get_g2javatype_gsiitem(env, gsiitem, g2_javashort_classname_gsisymbol); */
    int v = (*env)->CallIntMethod(env,
				  obj, 
				  shortClassInfo->intValue_MethodID);
    
    gsi_set_int (gsiitem, (gsi_int)v);

    if (fulldebug) printf ("  Packing Short to %s %d.\n", G2_JAVASHORT_CLASSNAME, v);

  } else if ((*env)->IsInstanceOf (env, obj, byteClassInfo->clazz))  {
    /* gsi_item val_gsi_item = get_g2javatype_gsiitem(env, gsiitem, g2_javabyte_classname_gsisymbol); */
    int v = (*env)->CallIntMethod(env,
				  obj, 
				  byteClassInfo->intValue_MethodID);
    gsi_set_int (gsiitem, (gsi_int)v);

    if (fulldebug) printf ("  Packing Byte to %s %d.\n", G2_JAVABYTE_CLASSNAME, v);

  } else if ((*env)->IsInstanceOf (env, obj, characterClassInfo->clazz))  {
    /* gsi_item val_gsi_item = get_g2javatype_gsiitem(env, gsiitem, g2_javachar_classname_gsisymbol); */
    jchar v = (*env)->CallCharMethod(env,
				  obj, 
				  characterClassInfo->charValue_MethodID);
    gsi_char gv[2];
    gv[0] = (gsi_char)v;
    gv[1] = 0;
    gsi_set_str (gsiitem, gv);

    if (fulldebug) printf ("  Packing Char to %s %c.\n", G2_JAVACHAR_CLASSNAME, v);
     
     
  } else if ((*env)->IsInstanceOf(env, obj, doubleClassInfo->clazz)) {

    double v = (*env)->CallDoubleMethod(env,
				  obj, 
				  doubleClassInfo->doubleValue_MethodID);
    gsi_set_flt (gsiitem, v);
    if (fulldebug) printf ("  Packing double to FLOAT %f.\n", v);


  } else if ((*env)->IsInstanceOf(env, obj, floatClassInfo->clazz)) {
    /* gsi_item val_gsi_item = get_g2javatype_gsiitem(env, gsiitem, g2_javafloat_classname_gsisymbol); */
    double v = (*env)->CallDoubleMethod(env,
				  obj, 
				  floatClassInfo->doubleValue_MethodID);
    gsi_set_flt(gsiitem, v);
    if (fulldebug) printf ("  Packing Float to %s %f.\n", G2_JAVAFLOAT_CLASSNAME, v);

  } else if ((*env)->IsInstanceOf(env, obj, stringClassInfo->clazz)) {


    gsi_char *v = jgi_GetStringChars(env, obj); 

    gsi_set_str(gsiitem, v);

    if (fulldebug && v) 
      {
#ifdef GSI_USE_WIDE_STRING_API
	char *str = jgi_unicode2str(v);
#else
	char *str = v;
#endif
	printf ("  Packing String : %s, length %d.\n", str, (*env)->JNI_GETSTRINGLENGTH(env, obj));
#ifdef GSI_USE_WIDE_STRING_API
	if (str) free(str);
#endif
      }

    if (v) free((char *)v);
  
  } else if ((*env)->IsInstanceOf(env, obj, symbolClassInfo->clazz)) {
   
    jstring vobj = (jstring)(*env)->CallObjectMethod(env,
				  obj, 
				  symbolClassInfo->getPrintValue_MethodID);


    gsi_char *str = jgi_GetStringChars(env, (jstring)vobj);
   
    if (str)
      gsi_set_sym (gsiitem, gsi_make_symbol (str));
    else
      gsi_set_sym (gsiitem, null_str);

    if (fulldebug) 
      {
#ifdef GSI_USE_WIDE_STRING_API	
	char *str_utf = jgi_unicode2str(str);
#else
	char *str_utf = str;
#endif
	printf ("  Packing Symbol to SYMBOL : %s.\n", str_utf);
	
#ifdef GSI_USE_WIDE_STRING_API
	if (str_utf) free(str_utf);
#endif
      }

    if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: deleting local ref to vobj for symbol class info\n");fflush(stdout);}
    (*env)->DeleteLocalRef(env, vobj);

    if (str) free((char *)str);

  } else if ((*env)->IsInstanceOf (env, obj, characterClassInfo->characterTypeArray_clazz)) {

    jchar *native_array = (*env)->GetCharArrayElements(env, (jcharArray)obj, NULL);
    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_set_usv (gsiitem, (unsigned short *)native_array, array_count );
    
    /* Must inform the VM that we have finished with the array */
    (*env)->ReleaseCharArrayElements(env, (jarray)obj, native_array, JNI_ABORT );
    
    if (fulldebug) printf ("  Packing char[]  to G2 USV\n");
 
  } else if ((*env)->IsInstanceOf(env, obj, booleanClassInfo->clazz)) {

    jboolean v = (*env)->CallBooleanMethod(env,
				  obj, 
				  booleanClassInfo->booleanValue_MethodID);

    gsi_set_log (gsiitem, (gsi_int)(v == 1L ? 1000 : -1000));
    if (fulldebug) printf ("  Packing Boolean to TRUTH-VALUE : %s.\n", (v ? "TRUE" : "FALSE"));

  } else if ((*env)->IsInstanceOf (env, obj, integerClassInfo->intTypeArray_clazz)) {

    jint *native_array = (*env)->GetIntArrayElements(env, (jintArray)obj, NULL);
    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_int *gsi_array = (gsi_int *)malloc(sizeof(gsi_int) * array_count);
    int i;

    /* before 64-bit platforms, we got away with setting the array contents
       directly, without copying carefully first.  Benchmarking shows this
       copying is negligible considering all the other processing. */
    for (i = 0; i < array_count; i++)
      gsi_array[i] = native_array[i];
    
    gsi_set_int_array (gsiitem, gsi_array, array_count );
    if (set_class) gsi_set_class_name (gsiitem, g2_integerarray_classname_gsisymbol);
    
    /* Must inform the VM that we have finished with the array */
    (*env)->ReleaseIntArrayElements(env, (jarray)obj, native_array, JNI_ABORT );
    if (gsi_array) free((char *)gsi_array);
    
    if (fulldebug) printf ("  Packing integer[]  to G2 INTEGER-ARRAY\n");

  } else if ((*env)->IsInstanceOf (env, obj, booleanClassInfo->booleanTypeArray_clazz)) {

    jboolean *native_array = (*env)->GetBooleanArrayElements(env, (jbooleanArray)obj, NULL);
    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_int *gsi_array = (gsi_int *)malloc(sizeof(gsi_int) * array_count);
    int i;
   
    for (i=0; i<array_count; i++)
      gsi_array[i] = (native_array[i] ? 1000 : -1000);

    gsi_set_log_array (gsiitem, gsi_array, array_count );
    if (set_class) gsi_set_class_name (gsiitem, g2_truthvaluearray_classname_gsisymbol);
    
    /* Must inform the VM that we have finished with the array */
    (*env)->ReleaseBooleanArrayElements(env, (jarray)obj, native_array, JNI_ABORT );
    if (gsi_array) free((char *)gsi_array);
    
    if (fulldebug) printf ("  Packing boolean[]  to G2 BOOLEAN-ARRAY\n");

  } else if ((*env)->IsInstanceOf (env, obj, doubleClassInfo->doubleTypeArray_clazz)) {

    jdouble *native_array = (*env)->GetDoubleArrayElements(env, (jdoubleArray)obj, NULL);
    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_set_flt_array (gsiitem, (double *)native_array, array_count );
    if (set_class) gsi_set_class_name (gsiitem, g2_floatarray_classname_gsisymbol);
    
    /* Must inform the VM that we have finished with the array */
    (*env)->ReleaseDoubleArrayElements(env, (jarray)obj, native_array, JNI_ABORT );
    
    if (fulldebug) printf ("  Packing integer[]  to G2 FLOAT-ARRAY\n");

  } else if ((*env)->IsInstanceOf (env, obj, symbolClassInfo->symbolArray_clazz)) {

    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_symbol *sym_array = (gsi_symbol*)malloc(array_count * sizeof(gsi_symbol));
    gsi_char *str;
    jobject elem;
    jstring vobj;
    int i;

    if (array_count > 0 && !sym_array) 
      {
          fprintf (stderr, "Error in convert_simple_java_gsiitem_to_gsiitem : Cant Malloc !!!!.");
	  fflush  (stderr);
	  return JAVA_ITEM_BAD;
      }

    
    if (fulldebug) printf ("  Packing Symbol[] to G2 SYMBOL-ARRAY \n");

    for (i = 0; i < array_count; i++)
      {
	/* Get the String representing the Symbol */
	elem = (jobject)((*env)->GetObjectArrayElement(env, obj, (jsize)i));
	vobj = (jstring)(*env)->CallObjectMethod(env,
						 elem, 
						 symbolClassInfo->getPrintValue_MethodID);
	if (vobj)
	  {
	    str = jgi_GetStringChars(env, (jstring)vobj);

	    if (str) 
	      {
		sym_array[i] = gsi_make_symbol (str);
		if (fulldebug)
		  {
		    printf("Element[%d]=",i);
		    jgi_printStr(str);
		    printf("\n");
		  }

		free((char *)str);
	      } else
		sym_array[i] = gsi_make_symbol (null_str);
	    if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: Deleting local ref for symbol array tag\n"); fflush(stdout);}
	    (*env)->DeleteLocalRef(env,vobj);
	  }
	else 
	  {
	    /* Safty net for null object in array */
	    sym_array[i] = gsi_make_symbol (null_str);
	  }
	if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: Deleting 2nd local ref for symbol array\n"); fflush(stdout);}
	(*env)->DeleteLocalRef(env,elem);

      }


    gsi_set_sym_array (gsiitem, sym_array, array_count );


    if (sym_array) free(sym_array);
    if (set_class) gsi_set_class_name (gsiitem, g2_symbolarray_classname_gsisymbol);

  } else if ((*env)->IsInstanceOf (env, obj, stringClassInfo->stringArray_clazz)) {

    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_char **str_array = (gsi_char **)malloc(array_count * sizeof(gsi_char *));
    jstring vobj;
    int i;

    if (array_count > 0)
      {

	if (!str_array) 
	  {
	    fprintf (stderr, "Error in convert_simple_java_gsiitem_to_gsiitem : Cant Malloc !!!!.");
	    fflush  (stderr);
	    return JAVA_ITEM_BAD;
	  }

	for (i = 0; i < array_count; i++)
	  {
	    /* Get the String representing the Java String */
	    vobj = (*env)->GetObjectArrayElement(env, obj, (jsize)i);
	    if (vobj) 
	      {
	   
		str_array[i] = jgi_GetStringChars(env, vobj);


		if (fulldebug) 
		  {
		    printf("Element [%i]=", i);
		    jgi_printStr(str_array[i]);
		    printf("\n");
		  }
		if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: Deleting local ref for string array\n"); fflush(stdout);}
		(*env)->DeleteLocalRef(env,vobj);
	      }
	    else
	      str_array[i] = null_str;

	  }
      }

    if (fulldebug) printf ("  Packing String[] to G2 TEXT-ARRAY \n");

    gsi_set_str_array (gsiitem, str_array, array_count );

    /* Free chars fetched from VM*/
    for (i = 0; i < array_count; i++)
      {
	vobj = (*env)->GetObjectArrayElement(env, obj, (jsize)i);
	if (vobj && str_array[i]) {
	  free(str_array[i]);
	  if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: Deleting 2nd local ref for string array\n"); fflush(stdout);}
	  (*env)->DeleteLocalRef(env,vobj);
	}
      }

    if (str_array) free(str_array);
    if (set_class) gsi_set_class_name (gsiitem, g2_textarray_classname_gsisymbol);

  } else if ((*env)->IsInstanceOf (env, obj, numberClassInfo->numberArray_clazz)) {

    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_item *elements = gsi_make_array (array_count);
    jobject vobj;
    int i;

    if (array_count > 0)
      {
	if (!elements) 
	  {
	    fprintf (stderr, "Error in convert_simple_java_gsiitem_to_gsiitem : Cant Make Items !!!!.");
	    fflush  (stderr);
	    return JAVA_ITEM_BAD;
	  }

	for (i = 0; i < array_count; i++)
	  {

	    vobj = (*env)->GetObjectArrayElement(env, obj, (jsize)i);
	    if (vobj)
	      {
		convert_java_object_to_gsiitem (env, vobj, &(elements[i]), context);
		if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: Deleting local ref for number array tag\n"); fflush(stdout);}
		(*env)->DeleteLocalRef(env,vobj);
	      } 
	    else
	      {
		elements[i] = gsi_make_item ();
		gsi_set_int (elements[i], 0);
	      }

	  }
      }

    if (fulldebug) printf ("  Packing Number[] to G2 QUANTITY-ARRAY \n");

    gsi_set_elements (gsiitem, elements, array_count, GSI_QUANTITY_ARRAY_TAG );
    
    if (set_class) gsi_set_class_name (gsiitem, g2_quantityarray_classname_gsisymbol);

  } else if ((*env)->IsInstanceOf (env, obj, objectClassInfo->objectArray_clazz)) {

    gsi_int array_count = (gsi_int)((*env)->GetArrayLength(env, (jarray)obj));
    gsi_item *elements = gsi_make_array (array_count);
    jobject vobj;
    int i;

    if (array_count > 0 )
      {
	if (!elements) 
	  {
	    fprintf (stderr, "Error in convert_simple_java_gsiitem_to_gsiitem : Cant Make Items !!!!.");
	    fflush  (stderr);
	    return JAVA_ITEM_BAD;
	  }
	
	for (i = 0; i < array_count; i++)
	  {

	    vobj = (*env)->GetObjectArrayElement(env, obj, (jsize)i);
	    if (vobj)
	      {
		convert_java_object_to_gsiitem (env, vobj, &(elements[i]), context);
		if (fulldebug) {printf("convert_simple_java_object_to_gsiitem: Deleting local ref for object array tag\n"); fflush(stdout);}
		(*env)->DeleteLocalRef(env,vobj);
	      }
	    else 
	      {
		elements[i] = gsi_make_item ();
		gsi_set_sym(elements[i], none_str);
	      }    

	  }
      }
    
    /* We now need to distinguish what type of complex array we are sending back */
    /* element_type (if avail) will help us out here */
    if (!array_element_type) {
	if (fulldebug) printf ("  Packing Object[] to G2 G2-ARRAY \n");

	gsi_set_elements (gsiitem, elements, array_count, GSI_ITEM_OR_VALUE_ARRAY_TAG );

	gsi_set_class_name (gsiitem, g2_g2array_classname_gsisymbol);
    } else {

      /* Possible element types
	 ItemArray means send back ITEM-ARRAY and GSI_ITEM_ARRAY_TAG
	 ValueArray means send back VALUE-ARRAY and GSI_VALUE_ARRAY_TAG
	 G2Array means send back G2-ARRAY and GSI_ITEM_OR_VALE_ARRAY_TAG
       */

      if (isSameSymbol(env, array_element_type, valueSymbol)) {
	if (fulldebug) printf ("  Packing Object[] to G2 VALUE-ARRAY \n");

	gsi_set_elements (gsiitem, elements, array_count, GSI_VALUE_ARRAY_TAG );

	if (set_class) gsi_set_class_name (gsiitem, g2_valuearray_classname_gsisymbol);

      } else if (isSameSymbol(env, array_element_type, itemSymbol)) {

	if (fulldebug) printf ("  Packing Object[] to G2 ITEM-ARRAY \n");

	gsi_set_elements (gsiitem, elements, array_count, GSI_ITEM_ARRAY_TAG );

	if (set_class) gsi_set_class_name (gsiitem, g2_itemarray_classname_gsisymbol);

      } else {
       
	/* Assume G2-ARRAY */
	
	if (fulldebug) printf ("  Packing Object[] to G2 G2-ARRAY \n");

	gsi_set_elements (gsiitem, elements, array_count, GSI_ITEM_OR_VALUE_ARRAY_TAG );

	if (set_class) gsi_set_class_name (gsiitem, g2_g2array_classname_gsisymbol);
      }  
    }

    
  } else {
    if (fulldebug)
      {
	printf("convert_simple_java_gsiitem_to_gsiitem : Did not identify class of object.");
	fflush  (stdout);
      }
    return JAVA_ITEM_BAD;
  }

  if (fulldebug) fflush (stdout);

  if (convdebug) {printf ("Exiting convert_simple_java_object_to_gsiitem\n"); fflush (stdout);}
  return java_item_status;
}
	
/** Public accessor to convert_simple_java_object_to_gsiitem */
int setup_gsiitem_from_simple_java_object (JNIEnv *env ,
					   jobject obj, 
					   gsi_item gsiitem,
					   gsi_int context) {
  return convert_simple_java_object_to_gsiitem(env, obj, JNI_FALSE, NULL, gsiitem, context);
}
    

/* *
 * Fill the a gsiitem with list element contained in a java Sequence.
 * The actual type of list data is determined by looking at the element_type symbol
 */
void get_list_data_from_java_list_object(JNIEnv *env, 
					 jobject sequence, 
					 jobject element_type,
					 gsi_item gsiitem, 
					 gsi_int context)
{

  if (convdebug) {printf("Function get_list_data_from_java_list_object \n"); fflush (stdout);}

  if (!element_type)
    fprintf(stderr, "JavaLink Warning : ELEMENT-TYPE attribute not set during attempt to update G2-LIST-SEQUENCE attribute \n");

  if (sequence && element_type) {
  
    jobjectArray jobject_array = (*env)->GetObjectField(env, 
							sequence, 
							sequenceClassInfo->elementData_FieldID);
    gsi_int array_count = (gsi_int)(*env)->CallIntMethod(env, 
					      sequence, 
					      sequenceClassInfo->size_MethodID);
    jobject element;
    int i;

    if (jobject_array) {

      if (isSameSymbol(env, element_type, integerSymbol)) {

	gsi_int *gsi_int_array = (gsi_int*)malloc(array_count * sizeof(gsi_int));

	for (i = 0; i < array_count; i++) {
	  element = (*env)->GetObjectArrayElement(env, jobject_array, i);
	  if ((*env)->IsInstanceOf(env, element, integerClassInfo->clazz))
	    gsi_int_array[i] = (*env)->CallIntMethod(env,
						     element,
						     integerClassInfo->intValue_MethodID);
	  else
	    gsi_int_array[i] = 0;
	  if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting local ref for integer type\n"); fflush(stdout);}
	  (*env)->DeleteLocalRef(env,element);
	}

	gsi_set_int_list (gsiitem, gsi_int_array, array_count );

	free(gsi_int_array);

      } else if (isSameSymbol(env, element_type, floatSymbol)) {

	double *dbl_array = (double*)malloc(array_count * sizeof(double));

	for (i = 0; i < array_count; i++) {
	  element = (*env)->GetObjectArrayElement(env, jobject_array, i);

	  if ((*env)->IsInstanceOf(env, element, doubleClassInfo->clazz))
	    dbl_array[i] = (*env)->CallDoubleMethod(env,
						 element,
						 doubleClassInfo->doubleValue_MethodID);
	  else
	    dbl_array[i] = 0.0;
	  if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting local ref for float type\n"); fflush(stdout);}
	  (*env)->DeleteLocalRef(env,element);
	}

	gsi_set_flt_list (gsiitem, dbl_array, array_count );

	free(dbl_array);


      } else if (isSameSymbol(env, element_type, truthValueSymbol)) {

	gsi_int *gsi_int_array = (gsi_int*)malloc(array_count * sizeof(gsi_int));

	for (i = 0; i < array_count; i++) {
	  element = (*env)->GetObjectArrayElement(env, jobject_array, i);
	  if ((*env)->IsInstanceOf(env, element, booleanClassInfo->clazz))
	    gsi_int_array[i] = ((*env)->CallBooleanMethod(env,
						     element,
						     booleanClassInfo->booleanValue_MethodID) 
				? 1000 : -1000);
	  else
	    gsi_int_array[i] = 0;
	  if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting local ref for truth value type\n"); fflush(stdout);}
	  (*env)->DeleteLocalRef(env,element);
	}

	gsi_set_log_list (gsiitem, gsi_int_array, array_count );

	free(gsi_int_array);

       } else if (isSameSymbol(env, element_type, symbolSymbol)) {

	gsi_symbol *sym_array = (gsi_symbol*)malloc(array_count * sizeof(gsi_symbol));
	
	gsi_char *str = NULL;

	for (i = 0; i < array_count; i++) {
	  element = (*env)->GetObjectArrayElement(env, jobject_array, i);
	  if ((*env)->IsInstanceOf(env, element, symbolClassInfo->clazz)) {
	    jstring vobj = (jstring)(*env)->CallObjectMethod(env,
							     element, 
							     symbolClassInfo->getPrintValue_MethodID);
	   
	    sym_array[i] = NULL; 

	    if (vobj)
	      {

		str = jgi_GetStringChars(env, (jstring)vobj);

		if (str)
		  {
		    sym_array[i] = gsi_make_symbol (str);
		    
		    free((char *)str);
		  }
		else
		  sym_array[i] = gsi_make_symbol (null_str);

		if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting local ref for symbol type\n"); fflush(stdout);}
		(*env)->DeleteLocalRef(env,vobj);

	      } else
		sym_array[i] = gsi_make_symbol (null_str);

	  }
	  if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting 2nd local ref for symbol type\n"); fflush(stdout);}
	  (*env)->DeleteLocalRef(env,element);
	}

	gsi_set_sym_list (gsiitem, sym_array, array_count );


	if (sym_array) free((char *)sym_array);

       } else if (isSameSymbol(env, element_type, textSymbol)) {

	gsi_char **str_array = (gsi_char**)malloc(array_count * sizeof(gsi_char *));
        gsi_char *str;

	for (i = 0; i < array_count; i++) {
	  element = (*env)->GetObjectArrayElement(env, jobject_array, i);
	  if ((*env)->IsInstanceOf(env, element, stringClassInfo->clazz)) {
	   
	    str = jgi_GetStringChars(env, element);

	   
	    if (str) {
	      str_array[i] = str;
	    }

	  } else
	    str_array[i] = null_str;

	  if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting local ref for Text type\n"); fflush(stdout);}
	  (*env)->DeleteLocalRef(env,element);
	}

	/* str_array will be copied here */
	gsi_set_str_list (gsiitem, str_array, array_count );

	/* Release the strings grabbed from JNI */
	for (i = 0; i< array_count; i++)
	  {
	    element = (*env)->GetObjectArrayElement(env, jobject_array, i);
	   
	    if ((*env)->IsInstanceOf(env, element, stringClassInfo->clazz) && str_array[i]) {

		free((char *)str_array[i]);


	      }

	    if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting 2nd local ref for text type\n"); fflush(stdout);}
	    (*env)->DeleteLocalRef(env,element);
	  }


	if (str_array) free((char *)str_array);

       } else {
	 
	 /* Assume ITEM-LIST, VALUE-LIST, QUANTITY-LIST or G2-LIST
	    Vector contents are of differing objects 
	  */
	 gsi_item *gsiitems_array = gsi_make_array (array_count);

	     
	 for (i = 0; i < array_count; i++) {
	   element = (*env)->GetObjectArrayElement(env, jobject_array, i);
	   convert_java_object_to_gsiitem (env, element, &(gsiitems_array[i]), context);
	   if (fulldebug) {printf("get_list_data_from_java_list_object: Deleting local ref for else clause: item, value, quantity, or g2 list\n"); fflush(stdout);}
	   (*env)->DeleteLocalRef(env,element);

	 }

	 /* Find out which tag to send back */
	 if (isSameSymbol(env, element_type, quantitySymbol))
	  gsi_set_elements (gsiitem, gsiitems_array, array_count, QUANTITY_LIST_TAG );
	else if (isSameSymbol(env, element_type, valueSymbol))
	  gsi_set_elements (gsiitem, gsiitems_array, array_count, VALUE_LIST_TAG );
	else if (isSameSymbol(env, element_type, itemSymbol))
	  gsi_set_elements (gsiitem, gsiitems_array, array_count, ITEM_LIST_TAG );
	else /* assume G2-LIST */
	  gsi_set_elements (gsiitem, gsiitems_array, array_count, ITEM_OR_VALUE_LIST_TAG );
	  

	/* Must release gsiitems created --- done when parent gsiitem is released */

       }
      if (fulldebug) {printf("get_list_data_from_java_list_object: deleting ref for jobject_array\n"); fflush (stdout);}
      (*env)->DeleteLocalRef(env,jobject_array);
    }
  }
  if (convdebug) {printf("Exiting Function get_list_data_from_java_list_object \n"); fflush (stdout);}
}
	  

/**
 * Create a gsiitem from a java_sequence.
 */
int convert_java_sequence_to_gsiitem( JNIEnv *env, 
				      jobject obj,
				      gsi_item *gsiitem_ptr,   /* gsi_item will be created here */
				      gsi_int context) {   

  int java_item_status = JAVA_ITEM_OK;
  jobject Sequence = obj;
  jarray ElmtArray = (*env)->GetObjectField(env, obj, sequenceClassInfo->elementData_FieldID);
  int SeqElmtCount = (*env)->CallIntMethod(env, obj, sequenceClassInfo->size_MethodID);
  jobject seqvalue;
  gsi_item *gsi_seq_elements = NULL, *current_gsi_item;
  int i;
  gsi_item gsiitem = gsi_make_item ();
  *gsiitem_ptr = gsiitem;
  
  if (convdebug) {printf("Function convert_java_sequence_to_gsiitem \n"); fflush (stdout);}

  if (fulldebug) printf ("  Packing a sequence of length %d for G2.\n", SeqElmtCount);

  /* should be (and is) reclaimed at end of recursion by gsirtl _free */
  gsi_seq_elements = gsi_make_array (SeqElmtCount);  

  if (fulldebug) printf ("  gsi_seq_elements = %lx\n", gsi_seq_elements);

  current_gsi_item = gsi_seq_elements;
      
  for (i=0; i<SeqElmtCount; i++) {
    if (fulldebug) printf ("    Packing Sequence Item# %d.\n", i);
    seqvalue = (*env)->GetObjectArrayElement(env, ElmtArray, i);
    convert_java_object_to_gsiitem (env, seqvalue, current_gsi_item, context);
    current_gsi_item++;
    if (fulldebug) {printf("convert_java_sequence_to_gsiitem: Deleting local ref for generic seq item\n"); fflush(stdout);}
    (*env)->DeleteLocalRef(env, seqvalue);
  }
      
  gsi_set_elements (gsiitem, gsi_seq_elements, (gsi_int)SeqElmtCount, GSI_SEQUENCE_TAG);

  if (fulldebug) {printf("convert_java_sequence_to_gsiitem: Deleting local ref for ElmtArray\n"); fflush(stdout);}
  (*env)->DeleteLocalRef(env, ElmtArray);

  if (convdebug) {printf("Exiting Function convert_java_sequence_to_gsiitem \n"); fflush (stdout);}  

  return JAVA_ITEM_OK;
}  

/** 
 *Copies the attributes of the java item to a gsi item 
 **/
gsi_attr *update_gsiitem_attributes(JNIEnv *env,
				    gsi_item gsiitem,
				    jobject attributesStruct,
				    gsi_int context) {

      jobject currAttribute, currAttrName, currAttrNameJstr, currAttrValue;
      jobject attributes, attributesVector;
      jobject *gsiAttributeNames, *gsiAttributeValues;
      jobject arrayAttr = NULL, elementTypeAttr = NULL;
      jobject listAttr = NULL, valueAttr = NULL;
      gsi_attr *gsi_attributes_array = NULL, *current_gsi_attr;
      gsi_char* attrnamestr;
      int i, numAttrbs, numGSIAttrbs;
      gsi_item gsiitem_attr;
      jboolean got_class = JNI_FALSE;
      jboolean filled_in_array = JNI_FALSE;
      jboolean filled_in_list = JNI_FALSE;
      jboolean warned = JNI_FALSE;

      if (convdebug) {printf("Function update_gsiitem_attributes \n"); fflush (stdout);}

      /* jgi_describeJavaObject (env, attributesStruct); */

      if (!attributesStruct) {
	if (fulldebug) fprintf(stderr, "Error in  convert_java_object_to_gsiitem \
Could not get attributes STructure from G2ItemProxy \n");
      }
      else {
	/* Get the vector containing the attributes */
	attributesVector = (*env)->CallObjectMethod(env, 
						    attributesStruct, 
						    structureClassInfo->getAttributes_MethodID);
	if (!attributesVector) {
	  fprintf(stderr, "Error in convert_java_object_to_gsiitem \
Could not get attributes Vector from Structure \n");
	} 
	else {
	    /* Get the array of Properties - the contents of the Structure */
	  attributes = (*env)->GetObjectField (env,
					       attributesVector,
					       vectorClassInfo->elementData_FieldID);
	}

	if (!attributes) {
	  fprintf(stderr, "Error in  convert_java_object_to_gsiitem \n Could \
not get attributes array from Vector elementData \n");
	}
						  
	/* get the number of attributes */
	numAttrbs = (*env)->CallIntMethod (env, 
					   attributesStruct, 
					   structureClassInfo->getAttributeCount_MethodID);     
	if (fulldebug) { 
	    printf ("of %d attributes before name and value check.\n", numAttrbs);
	    fflush (stdout); 
	}
      
	gsiAttributeNames = (jobject *)malloc(numAttrbs * sizeof(jobject));
	gsiAttributeValues = (jobject *)malloc(numAttrbs * sizeof(jobject));
	got_class = JNI_FALSE;
	filled_in_array = JNI_FALSE;
	filled_in_list = JNI_FALSE;
	arrayAttr = NULL;
	listAttr = NULL;
	elementTypeAttr = NULL;
	valueAttr = NULL;
	numGSIAttrbs = 0;
	  
	/* We have to do two parses of the array, to find out the number of 
	   attributes will send back to GSI.
	   Attributes that we extract are classSymbol, hiddenG2ArraySymbol, elementTypeSymbol
	   all because GSI does not export/import all attributes */

	  
	for (i=0; i<numAttrbs; i++) {
	      
	  /* RS6000 gets conniptions if we have too big arrays. */
	  if (i > 100000) {
	    if (!warned) {
	      warned = JNI_TRUE;
	      printf("WARNING:  Javalink local references approaching 100000 when converting GSI items.  This may cause problems on some platforms!\n");
	    }
	  }

	  /* attribute will be a Property */
	  currAttribute = (*env)->GetObjectArrayElement(env, attributes, i);
	  /* Attribute name from Property.key */
	  currAttrName = (*env)->GetObjectField(env, 
						currAttribute, 
						propertyClassInfo->key_FieldID);
		

	  /* Attribute value from Property.value */
	  currAttrValue = (*env)->GetObjectField(env, 
						 currAttribute,
						 propertyClassInfo->value_FieldID);

	    
	  /* Check for Class Name, needs to be specfically set on a gsi_item */
	  if (!got_class && isSameSymbol(env, currAttrName, classSymbol)) {
	    jstring vobj = (jstring)(*env)->CallObjectMethod(env,
							     currAttrValue, 
							     symbolClassInfo->getPrintValue_MethodID);

	    gsi_char *str = jgi_GetStringChars(env, (jstring)vobj);
	    
	    if (fulldebug) {printf("update_gsiitem_attributes: Deleting local ref for string vobj (%lx)\n",vobj); fflush(stdout);}
	    (*env)->DeleteLocalRef(env, vobj);

	    if (str) {
		gsi_set_class_name (gsiitem, gsi_make_symbol (str));
		free((char *)str);
	    }
	    got_class = JNI_TRUE;


	  } else if (!arrayAttr && isSameSymbol(env, currAttrName, hiddenG2ArraySymbol)) {

	    /* We have got an array for this Item, record  */
	    arrayAttr = currAttrValue;

	  } else if (!elementTypeAttr && isSameSymbol(env, currAttrName, elementTypeSymbol)) {

	    elementTypeAttr = currAttrValue;

	  } else if (!listAttr && isSameSymbol(env, currAttrName, g2ListSequenceSymbol)) {

	    /* We have got list data for this Item, record */
	    listAttr = currAttrValue; 

	  } else if (!valueAttr && isSameSymbol(env, currAttrName, lastRecordedValueSymbol)) {

	    valueAttr = currAttrValue;
	    
	  } else {

	    /* We will send this to GSI */
	    /* key will be a symbol, get its String value */
	    currAttrNameJstr = (*env)->CallObjectMethod(env, 
							currAttrName, 
							symbolClassInfo->getPrintValue_MethodID);

	    gsiAttributeNames[numGSIAttrbs] = currAttrNameJstr;
	    gsiAttributeValues[numGSIAttrbs] = currAttrValue;
	    numGSIAttrbs++;
	  }

	  if (fulldebug) {printf("update_gsiitem_attributes: Deleting local refs for currAttribute (%lx) and currAttrName (%lx)\n",currAttribute,currAttrName); fflush(stdout);}
	  (*env)->DeleteLocalRef(env, currAttribute);
	  (*env)->DeleteLocalRef(env, currAttrName);
	}

	if (valueAttr) {
	  /* value has to be specfically set, its not a gsi attribute */
	  convert_simple_java_object_to_gsiitem(env, valueAttr, JNI_TRUE, NULL, gsiitem, context);
		      
	  /* Set any history */
	  /* set_gsi_history_from_java_history (env, gsiitem, obj); */
	  if (fulldebug) {printf("update_gsiitem_attributes: Deleting local ref for valueAttr (%lx)\n",valueAttr); fflush(stdout);}
	  (*env)->DeleteLocalRef(env, valueAttr);
	}

	/* Fill in the array component of the GSI item, if available */
	if (!filled_in_array && arrayAttr) {
	  convert_simple_java_object_to_gsiitem (env, 
						 arrayAttr, 
						 JNI_FALSE,  /* We will set the class name */
						 elementTypeAttr, 
						 gsiitem, 
						 context);
	  filled_in_array = JNI_TRUE;
	  filled_in_list = JNI_TRUE;  /* can not have list and array element */
	  if (fulldebug) {printf("update_gsiitem_attributes: Deleting local ref for arrayAttr (%lx)\n",arrayAttr); fflush(stdout);}
	  (*env)->DeleteLocalRef(env, arrayAttr);
	} 
	   
	if (!filled_in_list && listAttr) {
	  get_list_data_from_java_list_object(env, 
					      listAttr, 
					      elementTypeAttr,
					      gsiitem, 
					      context);
	  filled_in_list = JNI_TRUE;
	  filled_in_array = JNI_TRUE; /* can not have list and array elements */
	  if (fulldebug) {printf("update_gsiitem_attributes: Deleting local ref for listAttr (%lx)\n",listAttr); fflush(stdout);}
	  (*env)->DeleteLocalRef(env, listAttr);
	} 


	/* Loop again this time creating GSI attributes as required */
	/* We did the above loop, just so we can allocate the correct number of GSI attributes */
	if (numGSIAttrbs > 0) {
	  gsi_attributes_array = gsi_make_attrs ((gsi_int)numGSIAttrbs);
	} else
	  gsi_attributes_array = NULL;
	/*printf("Number of attrbs is %d \n", numGSIAttrbs);*/

	current_gsi_attr     = gsi_attributes_array;

	for (i=0; i<numGSIAttrbs; i++) {
	  
	  attrnamestr = jgi_GetStringChars(env, gsiAttributeNames[i]);
	  if (fulldebug) { 
	    /* Need non unicode chars */                         
	    printf ("    Packing attr#%1d named ", i);
	    jgi_printStr(attrnamestr);
	    printf("\n");
	    fflush (stdout);          
	  }

	  gsi_set_attr_name (*current_gsi_attr, gsi_make_symbol (attrnamestr));
			
	  convert_java_object_to_gsiitem (env, gsiAttributeValues[i], &gsiitem_attr, context);
	  gsi_set_item_of_attr (*current_gsi_attr, gsiitem_attr);
	  current_gsi_attr++;
	      
	  if (fulldebug) {printf("update_gsiitem_attributes 2nd pass: Deleting local refs for name and value of element %d\n",i); fflush(stdout);}
	  (*env)->DeleteLocalRef(env, gsiAttributeValues[i]);
	  (*env)->DeleteLocalRef(env, gsiAttributeNames[i]);
	  if (attrnamestr) free((char *)attrnamestr);
	}
	
	if (numGSIAttrbs > 0)
	  gsi_set_attrs (gsiitem, gsi_attributes_array, numGSIAttrbs);

	free((char *)gsiAttributeValues);
	free((char *)gsiAttributeNames);
	
      } /* !attributeStruct */

      
      if (fulldebug) {printf("update_gsiitem_attributes: Deleting local refs for attributes and vector %d\n",i); fflush(stdout);}
      (*env)->DeleteLocalRef(env, attributesVector);
      (*env)->DeleteLocalRef(env, attributes);
      if (convdebug) {printf("Exiting Function update_gsiitem_attributes \n"); fflush (stdout);}
      return gsi_attributes_array;
} /* update_gsiitem_attributes */


/**
 * Create a gsiitem representing a com.gensym.classes.Item (Java Proxy for a G2 object)
 */
int convert_java_g2proxy_to_gsiitem  (JNIEnv *env, 
				      jobject obj,
				      gsi_item *gsiitem_ptr,   /* gsi_item will be created here */
				      gsi_int context) {

  int java_item_status = JAVA_ITEM_OK;
  gsi_item gsiitem;

  int handle = (*env)->GetIntField(env, obj, itemImplClassInfo->handle_FieldID);
  if (convdebug) {printf("Function convert_java_g2proxy_to_gsiitem \n"); fflush (stdout);}
  
  if (fulldebug) {
    printf ("Unpacking **NEW** item stub with handle = %d\n", handle);
    fflush (stdout);
  }
  
#ifdef CHECK_FOR_ITEM_VALIDITY
  fprintf (stdout, "Checking item validity\n");
  fflush (stdout);

  if (1) {
    jobject data = (*env)->GetObjectField (env, obj, itemImplClassInfo->data_FieldID);
    jboolean itemIsValid = (*env)->GetBooleanField (env, data, itemDataClassInfo->itemIsValid_FieldID);
    fprintf (stdout, "Packing item with handle = %2d, object = %lx, data = %lx, valid = %d\n",
	     handle, obj, data, itemIsValid);
    fflush (stdout);
  }
#endif

  if (handle > 0) {
    /* The handle translates from a "per connection" handle to a 
       pre created registration object */

    *gsiitem_ptr = gsi_registration_of_handle (handle, context);
    if (fulldebug)  printf("Got registration %lx for handle %d context %lx\n", *gsiitem_ptr, handle, context);
    if (*gsiitem_ptr == NULL)
      printf ("Sending NULL item\n");
  }
  else {

    /* Much more do do here as we are a copy */

    gsiitem = gsi_make_item ();
    *gsiitem_ptr = gsiitem;
  
    /* GsiItem is a GSI_NULL_TAG ! GSI knows that gisitem is an object by */
    /* the fact that the classname is set ! */
    gsi_set_type (gsiitem, GSI_NULL_TAG);


    /* Now the attributes */
    {
      jobject attributesStruct;

      attributesStruct = (*env)->CallObjectMethod (env,
						   JREF(registeredJGInterface), 
						   registeredJGInterface->getG2ItemInfo_MethodID,
						   obj);

      update_gsiitem_attributes(env, gsiitem, attributesStruct, context);


      if (fulldebug) {printf("convert_java_g2proxy_to_gsiitem: deleting local ref to attributes Struct\n"); fflush (stdout);}
      (*env)->DeleteLocalRef(env, attributesStruct);
    }

  } /* else handle */

  if (convdebug) {printf("Exiting Function convert_java_g2proxy_to_gsiitem \n"); fflush (stdout);} 
     
  return java_item_status;
  
} 


/**
 * Create a gsiitem from a java Sequence.
 */
int convert_java_structure_to_gsiitem (JNIEnv *env, 
				       jobject obj,
				       gsi_item *gsiitem_ptr,   /* gsi_item will be created here */
				       gsi_int context) {

  int java_item_status = JAVA_ITEM_OK;
  jobject currAttrName, currAttrNameJstr, currAttrValue;
  jobject attributesVector, attributes, currAttribute;
  gsi_attr *gsi_attributes_array = NULL, *current_gsi_attr;
  gsi_char* attrnamestr;
  int i, numAttrbs;
  gsi_item gsiitem;
  gsi_item gsiitem_attr;
      
  if (convdebug) {printf("Function convert_java_structure_to_gsiitem \n"); fflush (stdout);}
      
  if (fulldebug) { printf ("  Packing a structure..."); fflush (stdout); }

  /* Create our gsiitem */
  gsiitem = gsi_make_item ();
  *gsiitem_ptr = gsiitem;


  /* Get the vector containing the attributes from the structure */
  attributesVector = (*env)->CallObjectMethod(env, 
					      obj, 
					      structureClassInfo->getAttributes_MethodID);

  if (!attributesVector) {
    fprintf(stderr, "Error in convert_java_object_to_gsiitem \
Could not get attributes Vector from Structure \n");
  }

  /* Get the array of Properties - the contents of the Structure */
  attributes = (*env)->GetObjectField(env,
				      attributesVector,
				      vectorClassInfo->elementData_FieldID);

  if (!attributes) {
    fprintf(stderr, "Error in  convert_java_object_to_gsiitem Could \
not get attributes array from Vector elementData \n");
  }
						   

  /* get the number of attributes */
  numAttrbs = (*env)->CallIntMethod(env, 
				    obj, 
				    structureClassInfo->getAttributeCount_MethodID);
      
  if (fulldebug) { 
    printf ("of %d attributes before name and value check.\n", numAttrbs);
    fflush (stdout); 
  }


  gsi_attributes_array = gsi_make_attrs ((gsi_int)numAttrbs);
  current_gsi_attr     = gsi_attributes_array;
      
  for (i=0; i<numAttrbs; i++) 
    {
	      
      /* attribute will be a Property */
      currAttribute = (*env)->GetObjectArrayElement(env, attributes, i);
      /* Attribute name from Property.key */
      currAttrName = (*env)->GetObjectField(env, 
					    currAttribute, 
					    propertyClassInfo->key_FieldID);

      /* key will be a symbol, get its String value */
      currAttrNameJstr = (*env)->CallObjectMethod(env, 
						  currAttrName, 
						  symbolClassInfo->getPrintValue_MethodID);

      /* Attribute value from Property.value */
      currAttrValue = (*env)->GetObjectField(env, 
					     currAttribute,
					     propertyClassInfo->value_FieldID);


      attrnamestr = jgi_GetStringChars(env, currAttrNameJstr);
      if (fulldebug) { 
	/* Need non unicode chars */
	printf ("    Packing attr#%1d named ", i); 
	jgi_printStr(attrnamestr);
	printf("\n");
	fflush (stdout); 

      }

      gsi_set_attr_name (*current_gsi_attr, gsi_make_symbol (attrnamestr));
      convert_java_object_to_gsiitem (env, currAttrValue, &gsiitem_attr, context);
      gsi_set_item_of_attr (*current_gsi_attr, gsiitem_attr);

      if (fulldebug) {printf("convert_java_structure_to_gsiitem: deleting local ref to currAttribute\n");fflush(stdout);}
      (*env)->DeleteLocalRef(env, currAttribute);
      if (fulldebug) {printf("convert_java_structure_to_gsiitem: deleting local ref to currAttrValue\n");fflush(stdout);}
      (*env)->DeleteLocalRef(env, currAttrValue);
      if (fulldebug) {printf("convert_java_structure_to_gsiitem: deleting local ref to currAttrName\n");fflush(stdout);}
      (*env)->DeleteLocalRef(env, currAttrName);
      if (fulldebug) {printf("convert_java_structure_to_gsiitem: deleting local ref to currAttrNameJstr\n");fflush(stdout);}
      (*env)->DeleteLocalRef(env, currAttrNameJstr);

      current_gsi_attr++;
      if (attrnamestr) free((char *)attrnamestr);             
    }

  gsi_set_attrs (gsiitem, gsi_attributes_array, numAttrbs);
  gsi_set_type (gsiitem, GSI_STRUCTURE_TAG);

  if (fulldebug) {printf("convert_java_structure_to_gsiitem: deleting local ref to attributes and vector\n");fflush(stdout);}
  (*env)->DeleteLocalRef(env, attributesVector);
  (*env)->DeleteLocalRef(env, attributes);

  if (convdebug) {printf("Exiting Function convert_java_structure_to_gsiitem \n"); fflush (stdout);}

  return java_item_status;
}

/**
 * Convert a registered java object to a gsiitem representing a preloaded G2 stub
 * represening the java object
 */
int convert_java_builtin_to_gsiitem (JNIEnv *env, 
					 jobject obj,
					 gsi_item *gsiitem_ptr,   /* gsi_item will be created here */
				         gsi_int context) {
  
  int java_item_status = JAVA_ITEM_OK;
  gsi_item gsiitem;

  if (convdebug) {printf("Function convert_java_g2wrapper_to_gsiitem \n"); fflush (stdout);}
  if (fulldebug) printf ("Checking for a Wrapped primitive Java type.\n");

  gsiitem = gsi_make_item ();
  *gsiitem_ptr = gsiitem;
  return java_item_status = convert_simple_java_object_to_gsiitem (env, obj, JNI_TRUE, NULL, gsiitem, context);

  /* following code disabled */
  if (0 && java_item_status != JAVA_ITEM_OK)
    /* Not a Simple item, Its not a Java Object that we map
     * therefore create a Java Proxy for it
     */
    {
      jclass obj_class = (*env)->GetObjectClass(env, obj);

      /* Get handle for object*/
      gsi_int handle = 
	(gsi_int)(*env)->CallIntMethod(env, 
				       JREF(registeredJGInterface),
				       registeredJGInterface->getHandleForObject_MethodID,
				       obj);

      /* See if there a G2 class name registered for this java proxy*/
      jobject g2_classname_jsym = 
	(*env)->CallObjectMethod(env,
				 JREF(registeredJGInterface),
				 registeredJGInterface->getG2ClassForJavaProxy_MethodID,
				 obj_class,
				 context);

      /* Get the actual Java class name*/
      jstring java_classname_jstr  = 
	(*env)->CallObjectMethod(env,
				 obj_class,
				 classClassInfo->getName_MethodID);

      gsi_attr *gsi_attributes_array = gsi_make_attrs_with_items (1);
      gsi_char *java_classname;
      gsi_char *g2_classname;
	     

      /* GsiItem is a GSI_NULL_TAG ! GSI knows that gisitem is an object by */
      /* the fact that the classname is set ! */
      gsi_set_type (gsiitem, GSI_NULL_TAG);
	   
      /* The handle - the value, as JAVA-PROXY is actually a INTEGER-PARAMETER */
      gsi_set_int (gsiitem, handle);

      if (gsi_attributes_array) {            

	  gsi_set_attr_name (gsi_attributes_array[0], g2_javaproxy_classname_attr_gsisymbol);
	  java_classname = jgi_GetStringChars(env, java_classname_jstr);
	  if (java_classname) {
		   gsi_set_str (gsi_attributes_array[0], java_classname);
		   gsi_set_attrs (gsiitem, gsi_attributes_array, 1);
		   free((char *)java_classname);
	  }
      }

      /* We are passing back a JAVAPROXY */
      if (g2_classname_jsym) {
	jstring g2_classname_jstr = 
	  (jstring)(*env)->CallObjectMethod(env,
					    g2_classname_jsym,
					    symbolClassInfo->getPrintValue_MethodID);

	g2_classname = jgi_GetStringChars(env, g2_classname_jstr);

	if (g2_classname) {
	  gsi_set_class_name (gsiitem, gsi_make_symbol (g2_classname));
	  free((char *)g2_classname);
	}
      }
             
      java_item_status = JAVA_ITEM_OK;
    }

  if (convdebug) {printf("Exiting Function convert_java_g2wrapper_to_gsiitem \n"); fflush (stdout);}

  return java_item_status;
}

/**
 * Generic convert any java object to gsiitem entry point.
 */
int convert_java_object_to_gsiitem (JNIEnv *env, 
					 jobject obj,
					 gsi_item *gsiitem_ptr,   /* gsi_item will be created here */
				         gsi_int context) {
  int java_item_status = JAVA_ITEM_OK;
  jclass object_class;
  gsi_item gsiitem;

  if (convdebug) {printf("Function convert_java_object_to_gsiitem \n"); fflush (stdout);}
  
  if (obj == NULL) {
    if (fulldebug) fprintf(stderr, "Received NULL java_object in convert_java_object_to_gsiitem \n\
Can not convert this to a specific gsiitem, sending a GSI_NULL_TAG \n");
    gsiitem = gsi_make_item ();
    *gsiitem_ptr = gsiitem;
    gsi_set_type (gsiitem, GSI_NULL_TAG);
    return JAVA_ITEM_OK;   
    /* Sending NULL's back is actually quite valid in cases where slots are none in G2 */
    /* of course if G2 does not expect none then a G2 error will be generated          */
  }

  object_class = (*env)->GetObjectClass(env, obj);

  /* jgi_describeJavaObject (env, obj); */

  if ((*env)->IsInstanceOf(env, obj, sequenceClassInfo->clazz)) {
      java_item_status =  convert_java_sequence_to_gsiitem(env, obj, gsiitem_ptr, context);
  }
  else if ((*env)->IsAssignableFrom(env, object_class, itemImplClassInfo->clazz)) {
      java_item_status =  convert_java_g2proxy_to_gsiitem(env, obj, gsiitem_ptr, context);
  }
  else if ((*env)->IsInstanceOf(env, obj, structureClassInfo->clazz )){
    java_item_status =  convert_java_structure_to_gsiitem(env, obj, gsiitem_ptr, context);
  }
  else {
    java_item_status =  convert_java_builtin_to_gsiitem(env, obj, gsiitem_ptr, context); 

  }

  if (fulldebug) {printf("convert_java_object_to_gsiitem: Deleting local ref for object class\n"); fflush(stdout);}
  (*env)->DeleteLocalRef(env, object_class);

  if (convdebug) {printf("Exiting  convert_java_object_to_gsiitem \n"); fflush (stdout);}
  return java_item_status;
}



int get_gsiitems_from_java_objects (JNIEnv *env, 
				    jarray java_gsiitems_array,
				    gsi_item *gsi_items_array,
				    int size_of_array,
				    gsi_int context)
{
  jobject java_gsiitem;
  int bad_args = FALSE;
  int have_bad_args = FALSE;
  int already_threw = FALSE;
  int i;

  if (convdebug) printf ("Function get_gsiitems_from_java_objects with %d items... Unpacking... \n", size_of_array);

  for (i= 0; i<size_of_array; i++)
    {
      if (fulldebug) {
	printf (" [%d] ", i); 
	printf ("java_gsiitems is at : %lx  \n", java_gsiitems_array); 
	fflush (stdout);
      }

      java_gsiitem = (*env)->GetObjectArrayElement(env, java_gsiitems_array, i);
      
      if (fulldebug){ printf ("I%1d = %d : ", i, java_gsiitem); fflush (stdout);}


      if (1) /* Used to be a non-null check. Allow nulls to go through... -vkp, 11/1/97*/
	{
	  if (fulldebug) {
	    printf ("  >>  %d , %d call to convert!\n", java_gsiitem, gsi_items_array);
	    fflush (stdout);
	  }
	  bad_args = convert_java_object_to_gsiitem(env,
						    java_gsiitem, 
						    gsi_items_array,
						    context);
	  (gsi_items_array)++;
			
	  if (bad_args == JAVA_ITEM_BAD || bad_args == JAVA_ITEM_BAD_ALREADY_THREW) 
	    {
	      if (fulldebug) fprintf(stderr, 
		      "Error get_gsiitems_from_java_objects Null or bad Java argument number %d \n", i);
	     
	      if (bad_args == JAVA_ITEM_BAD_ALREADY_THREW)
		already_threw = JAVA_ITEM_BAD_ALREADY_THREW;
	      have_bad_args = TRUE;
	    }
	}
      else
	{
	  if (fulldebug) fprintf(stderr, 
		      "Error get_gsiitems_from_java_objects Null Java argument number %d \n", i);
	  have_bad_args = TRUE;
	}

      if (fulldebug) {printf("get_gsiitems_from_java_objects: Deleting local ref for item.\n"); fflush(stdout);}
      (*env)->DeleteLocalRef(env,java_gsiitem);
    }


  
  if (convdebug) printf ("Done.\nExiting get_gsiitems_from_java_objects...\n");
  return already_threw || have_bad_args;

}

