package com.gensym.cbu.odieeventfilterlanguage;

import java.util.Date;

public class NotBlock extends EventFilterBlock
{
  public NotBlock ()
  {
    super();
    properlyConfigured = true;
  }

  @Override
  public String booleanExpression()
  {
    return "!";
  }
}



















