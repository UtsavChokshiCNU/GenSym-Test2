package com.gensym.cbu.odieeventfilterlanguage;

import java.util.Date;

public class OrBlock extends EventFilterBlock
{
  public OrBlock()
  {
    super();
    properlyConfigured = true;
  }

  @Override
  public String booleanExpression()
  {
    return " || ";
  }
}



















