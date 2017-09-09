package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class InterfaceInfo extends Info
{ 
  private ClassConstant classConstant;
 
  public InterfaceInfo(ClassConstant classConstant) throws ClassException {
    super(new UTF8Constant(classConstant.getMyClass().getClassName()));
    this.classConstant = classConstant;
  }
  
  public InterfaceInfo(Type interfaceType) throws ClassException {
    super(new UTF8Constant(interfaceType.getClassName()));
    classConstant = new ClassConstant(interfaceType);
  }
  
  public boolean equals(InterfaceInfo infce) 
  {
    return super.equals(infce);
  }
  
  @Override
  public String toString() {
    return "<InterfaceInfo, name=" + getName() + ">";
  }
  
  public static void toStdout(Vector interfaces) {
    System.out.println("Interfaces");
    System.out.println("----------");
		Info.toStdout(interfaces);
  }

  @Override
  void emit(DataOutputStream out, ConstantPool cp)
       throws IOException, ClassException
  {
    out.writeShort(cp.getIndex(classConstant));
  }
}
