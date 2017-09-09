package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class InterfaceMethodRefConstant extends RefConstant implements RuntimeConstants
{

  InterfaceMethodRefConstant (Type myClass, String methodName, Type returnType, 
		     Type[] argumentTypes)
  {
    super(myClass);
    methodOrFieldConstant =
      new NameAndTypeConstant(methodName, returnType, argumentTypes);
  }

  InterfaceMethodRefConstant() {}

  @Override
  public byte getType() {
    return CONSTANT_INTERFACE_METHOD_REF;
  }

  public Type getReturnType() {
    return methodOrFieldConstant.getReturnType();
  }

  public Type[] getArgumentTypes() {
    return methodOrFieldConstant.getArgumentTypes();
  }

  @Override
  public String stringRep() {
    return "Interface Method " + getName() + " with Arument types " + getArgumentTypes() + " and Return type " + getReturnType() + " in class " + getMyClass();
  }

}

