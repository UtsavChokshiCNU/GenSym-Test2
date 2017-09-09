package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class IntegerConstant extends Constant implements RuntimeConstants
{
  private int value;

  IntegerConstant(int value) {
    this.value = value;
  }

  IntegerConstant() {}

  public int getValue() {
    return value;
  }
    
  @Override
  public byte getType() {
    return CONSTANT_INTEGER;
  }

  @Override
  public int hashCode() {
    return value ^ CONSTANT_INTEGER;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof IntegerConstant)
      && (value == ((IntegerConstant)c).value);
  }

  @Override
  public String stringRep() {
    return "" + value;
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeInt(value);
  }

  @Override
  void read(ConstantParser cp) throws ClassException {
    value = cp.readInt();
  }

}
