package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class MethodRefConstant extends RefConstant implements RuntimeConstants
{

  private static final boolean trace = false;

  MethodRefConstant (Type myClass, String methodName, Type returnType, 
		     Type[] argumentTypes)
  {
    super(myClass);
    if (trace)
      System.out.println("creating MethodRefConstant: for method " + methodName + ": " + argumentTypes.length + " argument Types specified");
    methodOrFieldConstant =
      new NameAndTypeConstant(methodName, returnType, argumentTypes);
    if (trace)
      System.out.println("Just created " + this);
  }

  MethodRefConstant() {}

  @Override
  public byte getType() {
    return CONSTANT_METHOD_REF;
  }

  public Type getReturnType() {
    return methodOrFieldConstant.getReturnType();
  }

  public Type[] getArgumentTypes() {
    return methodOrFieldConstant.getArgumentTypes();
  }

  @Override
  public String stringRep() {
    return "Method " + getName() + " with Argument types " + getArgumentTypes() + " and Return type " + getReturnType() + " in class " + getMyClass();
  }

}

