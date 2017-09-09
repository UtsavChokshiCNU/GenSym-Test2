package com.gensym.dispatcher;

public class AndCondition extends CompoundCondition
{
  Condition condition1, condition2;

  public AndCondition(Condition condition1,
		      Condition condition2)
  {
    this.condition1 = condition1;
    this.condition2 = condition2;
  }
  
  @Override
  public boolean isSatisfied(DispatchTable table)
       throws IllegalAccessException
  {
    //System.out.println(condition1 + "<--cond1 Satis="+ condition1.isSatisfied(table));
    //System.out.println(condition2 + "<--cond2 Satis="+ condition2.isSatisfied(table));
    return condition1.isSatisfied(table)&&
      condition2.isSatisfied(table);
  }

  @Override
  public String toString()
  {
    return "(" + condition1 + " &&\n" + condition2 + ")";
  }
}
