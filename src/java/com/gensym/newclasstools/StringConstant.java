package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class StringConstant extends Constant implements RuntimeConstants
{
  private UTF8Constant string;
  private int index;

  StringConstant(String string) {
    this.string = new UTF8Constant(string);
  }

  StringConstant() {}

  public String getString() {
    return string.getString();
  }
    
  @Override
  public byte getType() {
    return CONSTANT_STRING;
  }

  @Override
  public int hashCode() {
    return string.hashCode() ^ CONSTANT_STRING;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof StringConstant)
      && (string.equals(((StringConstant)c).string));
  }

  @Override
  public String stringRep() {
    return string.getString();
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeShort(cp.getIndex(string));
  }

  @Override
  public void addSubsidiaryConstants(ConstantPool cp) {
    cp.getIndex(string);
  }

  @Override
  void read(ConstantParser cp) {
    index = cp.readU2();
  }

  @Override
  void finishReading(ConstantPool cp) {
    string = (UTF8Constant)cp.getConstant(index);
  }

}
