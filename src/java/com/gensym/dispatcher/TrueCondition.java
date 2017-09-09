package com.gensym.dispatcher;

public class TrueCondition extends Condition
{

  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    return true;
  }

  @Override
  public String toString() {
    return "true";
  }
}
