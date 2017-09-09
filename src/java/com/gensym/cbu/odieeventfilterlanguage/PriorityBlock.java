package com.gensym.cbu.odieeventfilterlanguage;

import java.util.Date;

public class PriorityBlock extends EventFilterBlock
{
  int priority = 50;

  public PriorityBlock()
  {
    super();
    properlyConfigured = true;
  }

  public int getPriority()
  {
    return priority;
  }

  public void setPriority(int priority)
  {
    this.priority = priority;
    if (priority > 0) 
      properlyConfigured = true;
    else
      properlyConfigured = false;
  }

  @Override
  public String booleanExpression()
  {
    return "(";
  }
}



















