package com.gensym.g2script;

public class ArrayType extends Type
{
  Type simpleType;
  int rank;

  ArrayType (Type type, int rank)
  {
    simpleType = type;
    this.rank = rank;
  }

  @Override
  public Type getComponentType()
       throws ClassNotFoundException
  {
    return simpleType;
  }

}
