package com.gensym.types;

public class LongType extends QuantityType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -4435534077968262075L;

  public LongType ()
  {}

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Long)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("Long");
  }

}
