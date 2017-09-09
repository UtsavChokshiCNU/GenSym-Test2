package com.gensym.jgi;

import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.util.*;


/** 
 * A G2JavaStubClassReflectionProvider provides data for
 * G2 when it wishes to create stubs that represent Java Classes.
 */
public interface G2JavaStubClassReflectionProvider {

  /**
   * Return information enabling G2 to build G2 stubs
   * that allow access to a named Java class methods and constructors
   *
   *	       
   *@exception ClassNotFoundException The java class could not be found
   *@exception G2StubCreationException An error occured whil creating the G2 stub information
   */
  public Structure getG2StubDetailsForJavaClass(String className, 
						Class theClass, 
						Symbol G2ClassName, 
						boolean recurse,
						boolean forBeanWrapper)
       throws 
  ClassNotFoundException, G2StubCreationException;

  /**                
   * Return a sequence containing the names of the java classes that clazz is dependant on, including
   * dependant hierarchy and method parameters.
   */
  public Sequence findDependentClasses(String class_name, Class clazz, boolean recurse)
       throws
  ClassNotFoundException, G2StubCreationException;


}
