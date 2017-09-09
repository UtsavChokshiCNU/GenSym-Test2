package com.gensym.g2script;

import com.gensym.classtools.Access;
import com.gensym.classtools.RuntimeConstants;
import java.util.Vector;

public class UncompiledClass
{
  // all classnames are fully qualfied
  String name;
  boolean isInterface = false;
  Type   superClass;        // only one of these two is set;
  Type[] superInterfaces;   //
  Vector implementedInterfaces = new Vector();
  Access access;
  Vector uncompiledFields = new Vector();
  Vector uncompiledConstructors = new Vector();
  Vector uncompiledMethods = new Vector();
  
  UncompiledClass(String name, Type superClass, Access access)
  {
    this.name = name;
    this.superClass = superClass;
    this.access = access;
  }

  public UncompiledClass(String qualifiedName, Class superClass)
  {
    this.name = qualifiedName;
    this.superClass = Type.forName(null,superClass.getName()); 
    this.access = new Access(RuntimeConstants.ACC_PUBLIC);
  }

  public String getName()
  {
    return name;
  }

  void addImplementedInterface(Type type)
  {
    implementedInterfaces.addElement(type);
  }

  void addField(UncompiledField uncompiledField)
  {
    uncompiledFields.addElement(uncompiledField);
  }
}
  
