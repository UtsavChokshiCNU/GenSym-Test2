package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class UTF8Constant extends Constant implements RuntimeConstants
{
  private String string;

  UTF8Constant(String string) {
    this.string = string;
  }

  UTF8Constant() {}

  public String getString() {
    return string;
  }
    
  @Override
  public byte getType() {
    return CONSTANT_UTF8;
  }

  @Override
  public int hashCode() {
    return string.hashCode() ^ CONSTANT_UTF8;
  }

  @Override
  public boolean equals(Object c) {
    return (c instanceof UTF8Constant)
      && (string.equals(((UTF8Constant)c).string));
  }

  @Override
  public String stringRep() {
    return string;
  }

  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeUTF(string);
  }

  @Override
  void read(ConstantParser cp) throws ClassException {
    int length = cp.readU2();
    string = cp.readUTFString(length);
  }

}
