package com.gensym.classtools;

import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Vector;

class FieldRefConstant extends Constant
{
  private static final boolean trace = false;

  public FieldRefConstant(ConstantPool pool,String className,String name,String descriptor) 
       throws ClassException
  {
    super(CONSTANT_FIELD_REF);
    constantPool = pool;
    rawData1 = constantPool.add(new ClassConstant(constantPool,className),true);
    rawData2 = constantPool.add(new NameAndTypeConstant(constantPool,name,descriptor),true);
    constantPool.add(this,true);
  }

  public FieldRefConstant(ConstantPool pool,int class_index, int name_and_type_index) {
    super(CONSTANT_FIELD_REF);
    constantPool = pool;
    rawData1 = class_index;
    rawData2 = name_and_type_index;
  }

  protected FieldRefConstant() {
    super(CONSTANT_FIELD_REF);
  }

  @Override

  public String getFieldName() {
    return ((NameAndTypeConstant) constantPool.getPool(rawData2)).getName();
  }

  void emitAsFieldInfo(DataOutputStream out) throws IOException {
    Constant c = constantPool.getPool(rawData2);
    if (trace)
      System.out.println("Emitting as FieldInfo " + c.rawData1 + " " + c.rawData2);
    out.writeShort(c.rawData1);
    out.writeShort(c.rawData2);
  }
	
  @Override
	
  public Object clone(boolean clonePool) {
    if (cloneInProgress != null)
      return cloneInProgress;
    FieldRefConstant clone = new FieldRefConstant();
    return cloneWork(clone,clonePool);
  }
}
