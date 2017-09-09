package com.gensym.dispatcher;

public class NotCondition extends CompoundCondition
{
  Condition condition;

  public NotCondition(Condition condition)
  {
    this.condition = condition;
  }
  
  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    return !condition.isSatisfied(table);
  }

  @Override
  public String toString()
  {
    return "(!" + condition + ")";
  }
}
