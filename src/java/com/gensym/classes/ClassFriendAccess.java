/*
 *   Copyright (C) 1986-2017 Gensym Corporation.
 *   All Rights Reserved.
 *
 *      ClassFriendAccess.java
 *
 *   Description: Class for accessing package private data for generation
 *
 *        Author: Gensym Corp.
 *
 *       Version: 1.0
 *
 *          Date: Thu Dec 04 14:14:12 EST 1997
 *
 */

package com.gensym.classes;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.core.DebugUtil;
import java.util.Hashtable;
import java.util.Locale;
import java.lang.reflect.Field;

/**
 * This class extends access to package private data to the
 * Stub generation and loading classes.
 *
 * @author vkp 12/04/97
 * @version 1.0
 */
public final class ClassFriendAccess implements com.gensym.jgi.download.ClassFriendAccessor {

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.classes.access",
			   ClassFriendAccess.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.classes.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  private final Hashtable inhPathTable       = new Hashtable (151);
  private final Hashtable staticAttrTable    = new Hashtable (11);
  private final Hashtable externalInterfaces = new Hashtable (11);

  /**
   * registers the <code>Class</code> as having been loaded.
   * The class-specific data in the interface is read and stored.
   * It is then possible to access information regarding this
   * class.
   * @see #getClassInheritancePath
   * @see #getDirectSuperiorClasses
   * @param clazz the <code>Class</code> to register
   * @return a boolean specifying whether all superior interfaces of
   * this class had already been registered.
   */
  @Override
  public final boolean register (Symbol className_, Class clazz) {
    String fieldName = "";
    try {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "registerClass", clazz);
      if (inhPathTable.get (className_) != null)
	return true;
      
//       fieldName = "classInheritancePath";
//       Field f = clazz.getField (fieldName);
//       Symbol[] inheritancePath = (Symbol[]) f.get (null);
      Symbol[] inheritancePath = G2__ClassTable.getClassInheritancePath(className_);
      
//       fieldName = "staticAttributes";
//       f = clazz.getField (fieldName);
//       Symbol[] staticAttributes = (Symbol[]) f.get (null);
      Symbol[] staticAttributes = G2__ClassTable.getStaticAttributes (className_);
      
      register (className_, inheritancePath, staticAttributes);
      Class[] superiorClasses = clazz.getInterfaces ();
      boolean ok = true;
      for (int i=0; i<superiorClasses.length; i++)
	ok &= register1 (superiorClasses[i]);
      return ok;
    } catch (IllegalAccessException iae) {
      Trace.exception (iae, null);
      System.exit (0);		// I know what I'm doing-vkp, 12/7/97
      return true;
    } catch (/*NoSuchField*/Exception nsfe) {
      //Trace.exception (nsfe, null);
      externalInterfaces.put (clazz, clazz);
      return true;
    }
  }

  /**
   * Private method used to determine if there was any recursion
   * in class registration.
   * @param clazz the <code>Class</code> to register
   * @return a boolean specifying whether the class had already been registered.
   */
  private boolean register1 (Class clazz) throws IllegalAccessException {
    /* This is a test. Repeat. This is only a test.
       If this were a real fix, this method would go away */
    if (true)
      return true;
    try {
      Symbol className_ = (Symbol)clazz.getField ("g2ClassName").get(null);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "registerClass1", className_, inhPathTable.get (className_));
      if (inhPathTable.get (className_) != null)
	return true;
      else {
	register (className_, clazz);
	return false;
      }
    } catch (NoSuchFieldException nsfe) {
      //Trace.exception (nsfe, "Exception in register1 for " + clazz);
      externalInterfaces.put (clazz, clazz);
    }
    return false;
  }
   
  /**
   * registers the information for the G2 class named by className.
   * @param className a symbol naming a G2 class
   * @param inheritancePath the linearized inheritance path for className
   * @param staticAttributes the list of attributes defined at className
   */
  @Override
  public void register (Symbol className,
			Symbol[] inheritancePath,
			Symbol[] staticAttributes) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "registerClassInternal", className);
    inhPathTable.put (className, inheritancePath);
    staticAttrTable.put (className, staticAttributes);
  }

  /**
   * Returns the list of static attributes defined for the class
   * @param g2ClassName a Symbol naming a G2 class
   * @return a Sequence of symbols naming the static attributes of g2ClassName
   */
  @Override
  public final Sequence getStaticAttributes (Symbol g2ClassName) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "getStaticAttrList", g2ClassName);
    Symbol[] classInheritancePath = (Symbol[]) inhPathTable.get (g2ClassName);

    Sequence attributes = new Sequence (5);
    for (int i=0; i<classInheritancePath.length; i++) {
      Symbol supClassName = classInheritancePath[i];
      Symbol[] classAttributes = (Symbol[]) staticAttrTable.get (supClassName);
      for (int j=0; j<classAttributes.length; j++) {
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "staticAttrCollect",
		    classAttributes[j], supClassName);
	attributes.addElement (classAttributes[j]);
      }
    }
    return attributes;
  }

  
  /**
   * Returns the linearized inheritance path of the class
   * @param g2ClassName a Symbol naming a G2 class
   * @return a Symbol array containg the names of the classes in the inheritance path
   */
  @Override
  public final Symbol[] getClassInheritancePath (Symbol g2ClassName) {
    return (Symbol[]) inhPathTable.get (g2ClassName);
  }

  private final Sequence directSuperiors = new Sequence (3);
  private final Sequence classInhList    = new Sequence (3);

  /**
   * Returns the direct superior classes of the class
   * @param g2ClassName a Symbol naming a G2 class
   * @return a Symbol array containing the names of the direct parent of g2ClassName
   */
  @Override
  public final synchronized Symbol[] getDirectSuperiorClasses (Symbol g2ClassName) {
    Symbol[] classInhPath = (Symbol[]) inhPathTable.get (g2ClassName);
    for (int i=1; i<classInhPath.length; i++) {
      Symbol superClassName = classInhPath[i];
      if (!classInInheritancePathOfCurrentSuperiors (superClassName)) {
	directSuperiors.addElement (superClassName);
	classInhList.addElement (inhPathTable.get (superClassName));
      }
    }
    int numSuperiors = directSuperiors.size ();
    Symbol[] superiors = new Symbol [numSuperiors];
    directSuperiors.copyInto (superiors);
    directSuperiors.removeAllElements ();
    classInhList.removeAllElements ();
    return superiors;
  }

  /**
   * Determines if className is already present in the inheritance path of
   * all the classes that have been collected so far as established parents.
   */
  private boolean classInInheritancePathOfCurrentSuperiors (Symbol className) {
    for (int i=0; i<classInhList.size (); i++) {
      Symbol[] inhPath = (Symbol[]) classInhList.elementAt (i);
      for (int j=0; j<inhPath.length; j++)
	if (className.equals (inhPath[j]))
	  return true;
    }
    return false;
  }

}
