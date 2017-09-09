package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class ClassConstant extends Constant implements RuntimeConstants
{
  private Type myClass;
  private UTF8Constant nameConstant;
  private int nameIndex;

  ClassConstant(Type myClass) {
    this.myClass = myClass;
    nameConstant = new UTF8Constant(myClass.getInternalizedClassName());
  }

  ClassConstant(String className) {
    this(Type.makeType(className));
  }

  ClassConstant() {}

  public Type getMyClass() {
    return myClass;
  }
    
  @Override
  public byte getType() {
    return CONSTANT_CLASS;
  }

  @Override
  public int hashCode() {
    return myClass.hashCode() ^ CONSTANT_CLASS;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof ClassConstant)
      && (myClass == ((ClassConstant)c).myClass);
  }

  @Override
  public String stringRep() {
    return myClass.getClassName();
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeShort(cp.getIndex(nameConstant));
  }

  @Override
  void addSubsidiaryConstants(ConstantPool cp) {
    cp.getIndex(nameConstant);
  }

  @Override
  void read(ConstantParser cp) {
    nameIndex = cp.readU2();
  }

  @Override
  void finishReading(ConstantPool cp) {
    nameConstant = (UTF8Constant)cp.getConstant(nameIndex);
    myClass = Type.makeType(Type.externalize(nameConstant.getString()));
  }

}
