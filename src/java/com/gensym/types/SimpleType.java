package com.gensym.types;

public abstract class SimpleType extends G2Type
{

  static final long serialVersionUID = 8692978614594257945L;

  @Override
  public boolean includes(Object o)
  {
    return false;
  }

  @Override
  public String toString()
  {
    String className = getClass().getName();
    int index = className.lastIndexOf('.');
    return "<G2 "+((index == -1) ? className : className.substring(index+1))+">";
  }
}
