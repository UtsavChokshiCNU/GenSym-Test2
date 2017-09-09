package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class FloatConstant extends Constant implements RuntimeConstants
{
  private float value;

  FloatConstant(float value) {
    this.value = value;
  }

  FloatConstant() {}

  public float getValue() {
    return value;
  }
    
  @Override
  public byte getType() {
    return CONSTANT_FLOAT;
  }

  @Override
  public int hashCode() {
    return Float.floatToIntBits(value) ^ CONSTANT_FLOAT;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof IntegerConstant)
      && (value == ((FloatConstant)c).value);
  }

  @Override
  public String stringRep() {
    return "" + value;
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeFloat(value);
  }

  @Override
  void read(ConstantParser cp) throws ClassException {
    value = cp.readFloat();
  }

}
