package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class FieldRefConstant extends RefConstant implements RuntimeConstants
{

  FieldRefConstant (Type myClass, String fieldName, Type fieldType) {
    super(myClass);
    methodOrFieldConstant = new NameAndTypeConstant(fieldName, fieldType);
  }

  FieldRefConstant() {}

  @Override
  public byte getType() {
    return CONSTANT_FIELD_REF;
  }

  public Type getFieldType() {
    return methodOrFieldConstant.getFieldType();
  }

  @Override
  public String stringRep() {
    return "Field " + getName() + " of type " + getFieldType() + " in class " + getMyClass();
  }

}

