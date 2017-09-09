package com.gensym.types;

public class FloatType extends QuantityType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 5291450859510456945L;

  public FloatType ()
  {}

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Double)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out , int indent)
  {
    out.print("Float");
  }
  
}
