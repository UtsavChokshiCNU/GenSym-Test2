/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SorterSupport.java
 *
 */

package com.gensym.util;

import java.text.Collator;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.Hashtable;

/**
 *  This class provides comparison methods for com.gensym.util.Sorter.  It
 *  contains default comparison methods for String, Character, Integer,
 *  Float, char, int, and float.
 */

import com.gensym.message.Resource;

public class SorterSupport{

  public static final int EQUAL = 0;
  public static final int LESS_THAN = -1;
  public static final int GREATER_THAN = 1;

  private static Hashtable methodTable; 

  private static final Class thisClass = com.gensym.util.SorterSupport.class;

  private static final Resource i18n = Resource.getBundle("com/gensym/util/Messages");
  static{
    try{
      methodTable = new Hashtable();
      Class[] args = new Class[2];//re-use this array to reduce garbage

      Class stringClass = java.lang.String.class;
      args[0] = stringClass;  
      args[1] = stringClass;
      methodTable.put(java.lang.String.class, thisClass.getMethod("compare", args));
      Class charClass = java.lang.Character.class;
      args[0] = charClass;  
      args[1] = charClass;
      methodTable.put(java.lang.Character.class,thisClass.getMethod("compare", args));
      methodTable.put(Character.TYPE, thisClass.getMethod("compare", args));
      Class integerClass = java.lang.Integer.class;
      args[0] = integerClass;  
      args[1] = integerClass;      
      methodTable.put(java.lang.Integer.class, thisClass.getMethod("compare", args));
      methodTable.put(Integer.TYPE, thisClass.getMethod("compare", args));
      Class floatClass = java.lang.Float.class;
      args[0] = floatClass;  
      args[1] = floatClass;
      methodTable.put(java.lang.Float.class,thisClass.getMethod("compare", args));
      methodTable.put(Float.TYPE, thisClass.getMethod("compare", args));
    
    } catch(NoSuchMethodException ex){
      throw new UnexpectedException(ex);
    } catch(RuntimeException ex){
      throw new UnexpectedException(ex);
    }
  }

  /** Returns the comparison method for the specified class.
    * If a comparison method has not been registered for the specified class,
    * a search is performed up the heirachy tree.  
    * If no method is found, null is returned.
    */
  public static Method getDefaultCompareMethod(Class clazz){
    Class classOfInterest;
    if (clazz.isArray())
      classOfInterest = clazz.getComponentType();
    else
      classOfInterest = clazz;

    Method compareMethod = (Method)methodTable.get(classOfInterest);
    while (compareMethod == null){
      classOfInterest = classOfInterest.getSuperclass();
      if (classOfInterest == null){
    	  break;
      }
      compareMethod = (Method)methodTable.get(classOfInterest);
    }
    return compareMethod;
  } 

  /* Comparison method must be public and static, and take two parameters
     of the class for which the method is registered for. */
  static boolean verifyMethod(Method compareMethod, Class clazz, boolean exactClass){
    int modifiers = compareMethod.getModifiers();
    if (!((Modifier.isPublic(modifiers)) && (Modifier.isStatic(modifiers))))
      return false;
    Class returnType = compareMethod.getReturnType();
    if (!((returnType == java.lang.Integer.class) || (returnType == Integer.TYPE)))
      return false;
    Class[] parameters = compareMethod.getParameterTypes();
    if (parameters.length != 2){
    	return false;
    }
    if (exactClass){
      if ((parameters[0] == clazz) && (parameters[1] == clazz)){
    	  return true;
      }
    }
    else 
      if ((parameters[0].isAssignableFrom(clazz)) && 
	  (parameters[1].isAssignableFrom(clazz))) return true;
    return false;
  }

  /** Sets the comparison method for the given class.
    * The comparison method must be both static and public, and take two
    * parameters of the type <code>clazz</code>.
    */
  public static void setDefaultCompareMethod(Class clazz, Method compareMethod){
    if (compareMethod == null) 
      throw new IllegalArgumentException(i18n.getString("nullComparisonMethod"));
    if (!(verifyMethod(compareMethod, clazz, true)))
      throw new IllegalArgumentException(i18n.getString("illegalComparisonMethodForClass"));
    methodTable.put(clazz, compareMethod);
  }

  /** Compares two Strings using the Collator for the default Locale */
  public static int compare(String s1, String s2){
    return Collator.getInstance().compare(s1, s2);
  }

  public static int compare(Character char1, Character char2){
    char c1 = char1.charValue();
    char c2 = char2.charValue();
    if (c1 == c2){
    	return EQUAL;
    }
    if (c1 < c2){
    	return LESS_THAN;
    }
    return GREATER_THAN;
  }

  public static int compare(Integer int1, Integer int2){
    int i1 = int1.intValue();
    int i2 = int2.intValue();
    if (i1 == i2){
    	return EQUAL;
    }
    if (i1 < i2){
    	return LESS_THAN;
    }
    return GREATER_THAN;
  }

  public static int compare(Float float1, Float float2){
    float f1 = float1.floatValue();
    float f2 = float2.floatValue();
    if (Float.compare(f1, f2) == 0) 
    	return EQUAL;
    if (f1 < f2) 
    	return LESS_THAN;
    return GREATER_THAN;
  }
}
