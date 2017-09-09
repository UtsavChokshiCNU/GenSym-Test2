package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public abstract class RefConstant extends Constant implements RuntimeConstants
{
  private ClassConstant classConstant;
  private int classIndex;

  protected NameAndTypeConstant methodOrFieldConstant;
  private int methodOrFieldIndex;
 
  // externalized form of methodOrFieldConstant depends on subclass.

  protected RefConstant (Type myClass) {
    classConstant = new ClassConstant(myClass);
  }

  RefConstant() {}

  public Type getMyClass() {
    return classConstant.getMyClass();
  }

  public String getName() {
    return methodOrFieldConstant.getName();
  }

  // Other accessors defined in subclass.

  @Override
  public int hashCode() {
    return getType() ^ classConstant.hashCode() ^ methodOrFieldConstant.hashCode();
  }

  @Override
  public boolean equals(Object c) {
    if (c instanceof RefConstant) {
      RefConstant rc = (RefConstant)c;
      return getType() == rc.getType() &&
	classConstant.equals(rc.classConstant) &&
	methodOrFieldConstant.equals(rc.methodOrFieldConstant);
    } else {
      return false;
    }
  }

  // StringRep in subclasses.

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeShort(cp.getIndex(classConstant));
    out.writeShort(cp.getIndex(methodOrFieldConstant));
  }

  @Override
  public void addSubsidiaryConstants(ConstantPool cp) {
    cp.getIndex(classConstant);
    cp.getIndex(methodOrFieldConstant);
  }
  
  // This works for all refconstants; difference is in finishReading;
  @Override
  void read(ConstantParser cp) {
    classIndex = cp.readU2();
    methodOrFieldIndex = cp.readU2();
  }

  @Override
  void finishReading(ConstantPool cp) throws ClassException {
    classConstant = (ClassConstant)cp.getConstant(classIndex);
    methodOrFieldConstant = (NameAndTypeConstant)cp.getConstant(methodOrFieldIndex);
  }
}

