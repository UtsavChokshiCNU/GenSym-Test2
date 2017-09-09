package com.gensym.classtools;

import java.util.Vector;

public class MethodRef extends Atom {
  MethodRefConstant constant;
  String className;
  String methodName;
  String descriptor;

  private boolean constructor = false;
  private static final boolean trace = false;

  public MethodRef(String className, String methodName, String descriptor)
       throws ClassException
  {
    initA(className,methodName,descriptor);
  }

  private void initA(String className, String methodName, String descriptor) 
       throws ClassException
  {
    this.className = className;
    this.methodName = methodName;
    this.descriptor = descriptor;
    expressionType = Type.parseType(descriptor);
  }


  public int getWhere() throws ClassException {
    if (constant == null) 
      throw new ClassException("Attempt to retrieve constantPool index for MethodRef which has not yet generated a constant");
    return constant.getWhere();
  }

  public String getMethodName() {
    return methodName;
  }

  public String getDescriptor() {
    return descriptor;
  }

  public String getClassName() {
    return className;
  }

  public InterfaceMethodRef cloneAsInterfaceMethodRef() throws ClassException {
    return new InterfaceMethodRef(className,methodName,descriptor);
	
  }

  @Override
  public boolean isConstantExpression() {
    return false;
  }


  @Override
  public void generateConstants(ConstantPool cp) throws ClassException {
    constant = (MethodRefConstant)
      cp.getPool(cp.add(new MethodRefConstant(cp,className,methodName,descriptor),
			true));
  }
}
