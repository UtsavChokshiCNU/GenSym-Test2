package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class DoubleConstant extends Constant implements RuntimeConstants
{
  private double value;

  DoubleConstant(double value) {
    this.value = value;
  }

  DoubleConstant() {}

  public double getValue() {
    return value;
  }
    
  @Override
  public byte getType() {
    return CONSTANT_DOUBLE;
  }

  @Override
  public int hashCode() {
    long aslong = Double.doubleToLongBits(value);
    return ((int) (aslong ^ (aslong >>> 32))) ^ CONSTANT_DOUBLE;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof DoubleConstant)
      && (value == ((DoubleConstant)c).value);
  }

  @Override
  public String stringRep() {
    return "" + value;
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeDouble(value);
  }

  @Override
  void read(ConstantParser cp) throws ClassException {
    value = cp.readDouble();
  }

}
