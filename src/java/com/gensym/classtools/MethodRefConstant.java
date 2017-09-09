package com.gensym.classtools;

import java.io.DataOutputStream;
import java.io.IOException;

class MethodRefConstant extends Constant
{  
  private boolean constructor = false;
  private static final boolean trace = false;
	
  public MethodRefConstant(ConstantPool pool, String className, String methodName, String descriptorName)
       throws ClassException
  {
    super(CONSTANT_METHOD_REF);
    init2(pool,className,methodName,descriptorName);
  }

  MethodRefConstant(ConstantPool pool,int descriptor_index, int name_and_type_index) {
    super(CONSTANT_METHOD_REF);
    init1(pool,descriptor_index,name_and_type_index);
  }

  protected MethodRefConstant() {
    super(CONSTANT_METHOD_REF);
  }

  protected MethodRefConstant(int type) {
    super(type);
  }
	
  //**************** Protected Initialization methods  ************************

  protected void init1(ConstantPool pool, int descriptor_index, int name_and_type_index) {
    constantPool = pool;
    rawData1 = descriptor_index;
    rawData2 = name_and_type_index;
  }

  protected void init2(final ConstantPool pool, final String className, final String methodName, final String descriptorName)
       throws ClassException
  {
	  String methodNameLocal = methodName;
    // Enforce constructor naming convention
    if (className.equals(methodNameLocal)) {
    	methodNameLocal = "<init>";
      constructor = true;
    }
    constantPool = pool;
    rawData1 = constantPool.add(new ClassConstant(constantPool,className),true);
    rawData2 = constantPool.add(new NameAndTypeConstant(constantPool,methodNameLocal,descriptorName),true);	
  }

  public boolean isConstructor() {
    return constructor;
  }

  public int getClassWhere() {
    return rawData1;
  }

  void emitAsMethodInfo(DataOutputStream out) throws IOException {
    Constant c = constantPool.getPool(rawData2);
    if (trace)
      System.out.println("Emitting as MethodInfo " + c.rawData1 + " " + c.rawData2);
    out.writeShort(c.rawData1);
    out.writeShort(c.rawData2);
  }

  @Override

  public Object clone(boolean clonePool) {
    if (cloneInProgress != null)
      return cloneInProgress;
    Constant clone = new MethodRefConstant();		
    return cloneWork(clone,clonePool);
  }
}
