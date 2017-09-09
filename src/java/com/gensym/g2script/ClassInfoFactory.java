package com.gensym.g2script;

import com.gensym.classtools.ClassInfo;

public interface ClassInfoFactory
{
  public ClassInfo generateClassInfo(String className);

  public Class getClassForName(String className)
       throws ClassNotFoundException;

  public String getJavaNameForG2ClassName(String name);
       
  /** return the default implementation class if any,
    may return null which will cause a compile time error
    */
  public String getImplementationClassName(String interfaceName);

  /** Denote an interface as being special 
   * regarding the fact that it would like to have fields, yet 
   * can only have Java Beans style properties
   */
  public boolean interfaceHasImplicitProperties(String qualifiedName);

  /** Returned name MUST be the name of a method on the interface
   *  for further introspection.
   */
  public String getImplicitPropertyGetter(String interfaceName, 
					  String g2AttributeName);

  public String getImplicitPropertySetter(String interfaceName, 
					  String g2AttributeName);

  public boolean allowGlobalNameReferences();
}

