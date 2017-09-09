package com.gensym.classtools;

class Utf8Constant extends Constant {

  public Utf8Constant(String s) {
    super(CONSTANT_UTF8);
    stringData = s;
  }

  public Utf8Constant(ConstantPool pool,String s) {
    super(CONSTANT_UTF8);
    constantPool = pool;
    stringData = s;
   }
}
