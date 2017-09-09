package com.gensym.g2export;

import java.util.Hashtable;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.util.G2ClassTranslator;
import com.gensym.g2export.G2__Base;
import com.gensym.fida.ClassReference;
import com.gensym.fida.BasicClassReference;
import com.gensym.message.Trace;

/**
 * The G2ClassManager allows runtime lookup of G2 class related Definitional information
 */
public class G2ClassManager {

  private static Hashtable classLoaderTable = new Hashtable();
  private static Hashtable classNameForG2ClassNameTable = new Hashtable();

  public static String getClassForG2ClassName(Symbol g2ClassName) 
  {
    return (String)classNameForG2ClassNameTable.get(g2ClassName.toString());
  }

  public static String getClassForG2ClassName(String g2ClassName) 
  {
    return (String)classNameForG2ClassNameTable.get(g2ClassName);
  }

  private static Class classDefImplClass = null;
  private static Method classDefSetMethod = null;

  public static ClassReference getClassReferenceForG2ClassName(String g2ClassName)
  {
    String className = (String)classNameForG2ClassNameTable.get(g2ClassName);
    if (className == null)
      return null;
    else {
      try {
	// Can not refer to a ClassDefinition, as it may not exist during a BOOT_STRAP
	// i.e. we have not event downloaded g2export classes from G2 yet
	if (classDefImplClass == null) {
	  classDefImplClass = Class.forName("com.gensym.g2export.ClassDefinitionImpl");
	  classDefSetMethod = classDefImplClass.getMethod("setExportedClassName",
						      new Class[] {String.class});
	}
	ClassReference classDef = (ClassReference)classDefImplClass.newInstance();
	classDefSetMethod.invoke(classDef, new java.lang.Object[] {className});
	return classDef;
      } catch (Exception e) {
	Trace.exception(e);
	throw new RuntimeException("In G2ClassManager::getClassReferneceForG2ClassName " + e.toString());
      }
    }
  }

  // Return here so that we call it from an Interface static var.
  public static boolean recordG2ClassNameForClass(Symbol g2ClassName, String className) {
    //System.out.println("ClassManager::recordG2ClassName " + g2ClassName + " " + className);
    String g2ClassNameStr = g2ClassName.toString();
  
    if (classNameForG2ClassNameTable.get(g2ClassNameStr) == null) {
      classNameForG2ClassNameTable.put(g2ClassNameStr, className);
    }
    return true;
  }

  public static void recordG2ClassNameForClass(Class clazz) {
    Symbol g2ClassName = null;
    if (G2__Base.class.isAssignableFrom(clazz)) {
      try {
	String fieldName = "g2ClassName";
	Field f = clazz.getField (fieldName);
	g2ClassName = (Symbol) f.get (null);
      } catch (NoSuchFieldException e) {
	throw new UnexpectedException(e, "While trying to read g2ClassName field from " + clazz);
      } catch (IllegalAccessException e) {
	throw new UnexpectedException(e, "While trying to read g2ClassName field from " + clazz);
      }
    } else {
      g2ClassName = G2ClassTranslator.createG2ClassNameFromJavaClassName(clazz.getName());
    }
    recordG2ClassNameForClass(g2ClassName, clazz.getName());
  }


}
