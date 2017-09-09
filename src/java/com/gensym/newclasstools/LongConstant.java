package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class LongConstant extends Constant implements RuntimeConstants
{
  private long value;

  LongConstant(long value) {
    this.value = value;
  }

  LongConstant() {}

  public long getValue() {
    return value;
  }
    
  @Override
  public byte getType() {
    return CONSTANT_LONG;
  }

  @Override
  public int hashCode() {
    return ((int) (value ^ (value >>> 32))) ^ CONSTANT_LONG;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof LongConstant)
      && (value == ((LongConstant)c).value);
  }

  @Override
  public String stringRep() {
    return "" + value;
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeLong(value);
  }

  @Override
  void read(ConstantParser cp) throws ClassException {
    value = cp.readLong();
  }

}
