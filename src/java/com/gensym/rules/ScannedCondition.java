package com.gensym.rules;

import com.gensym.classtools.*;
import java.lang.reflect.*;
import java.util.EventObject;

public class ScannedCondition extends Condition
{

  public ScannedCondition(String bindingName, String className)
  {
    super(bindingName,className,null);
  }

  @Override
  boolean canChain()
  {
    return false;
  }

  @Override
  Expression makeKeyBuilderExpression(Variable eventVariable)
  {
    return null;
  }

  @Override
  String getOrMakeKey()
  {
    return null;
  }

  @Override
  public String toString()
  {
    return "<ScannedCondition binding="+bindingName+
      " class="+className+">";
  }
}
