package com.gensym.types;

public class IntegerType extends QuantityType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -4435534077968262074L;

  public IntegerType ()
  {}

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Integer)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("Integer");
  }

}
