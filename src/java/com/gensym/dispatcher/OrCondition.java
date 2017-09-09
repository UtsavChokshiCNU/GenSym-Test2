package com.gensym.dispatcher;

public class OrCondition extends CompoundCondition
{
  Condition condition1, condition2;

  public OrCondition(Condition condition1,
		     Condition condition2)
  {
    this.condition1 = condition1;
    this.condition2 = condition2;
  }
  
  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    return condition1.isSatisfied(table) ||
      condition2.isSatisfied(table);
  }

  @Override
  public String toString()
  {
    return "(" + condition1 + " ||\n" + condition2 + ")";
  }
  
}
